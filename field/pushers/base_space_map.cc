
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Implementation for class base_space_map.
/// A map from one sec_rep_space to another.

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "base_space_map.h"
#include "base_space_map_push_action.h"
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_member.h"
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_poset.h"
#include "ComLimitPoint/sheaf/block.impl.h"
#include "constant_base_space_map_push_action.h"
#include "copy_base_space_map_push_action.h"
#include "ComLimitPoint/fiber_bundle/discretization_context.h"
#include "ComLimitPoint/fiber_bundle/discretization_iterator.h"
#include "discretization_pusher.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/eval_iterator.h"
#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "ComLimitPoint/sheaf/postorder_iterator.h"
#include "ComLimitPoint/sheaf/preorder_iterator.h"
#include "property_disc_iterator.h"
#include "ComLimitPoint/geometry/sec_ed_invertible.h"
#include "ComLimitPoint/fiber_bundle/sec_vd_space.h"
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#include "std_utility.h"
#include "field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT 1

namespace fields
{

void print_debug_info(scoped_index xeval_client_id,
                      sec_vd& xoutput,
                      pullback_map::iterator& xitr,
                      block< block<sec_vd_dof_type>* >& xout_dofs)
{
  cout << "eval id: " << setw(5) << xeval_client_id;
  index_space_handle& lmap = xoutput.schema().discretization().id_space();
  cout << "  disc_id: " << setw(5) << lmap.pod(xitr->disc_id);
  cout << " domain point:";
  int ldb = xitr->domain_pt.db();
  for(size_type j=0; j<ldb; ++j)
  {
    cout << setw(12) << setprecision(3) << xitr->domain_pt.local_coord(j);
  }
  cout << setw(5) << xitr->domain_pt.chart_id();
  cout << " out dofs:";

  for(int i=0; i<xout_dofs.ct(); ++i)
  {
    for(size_type j=0; j<xout_dofs[i]->ct(); ++j)
    {
      cout << setw(12) << setprecision(3) << (*xout_dofs[i])[j];
    }
    cout << endl;
  }
}

} // namespace fields


// =============================================================================
// BASE_SPACE_MAP FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::base_space_map::
base_space_map(const sec_ed& xdomain_coord, const sec_ed& xrange_coord, bool xauto_access)
  : _coord_branch_id_space(0)
{
  // Preconditions:

  require(xauto_access || xdomain_coord.state_is_read_accessible());
  require(xauto_access || xrange_coord.state_is_read_accessible());

  require(same_fiber(xdomain_coord, xrange_coord, xauto_access));

  define_old_variable(int old_xdomain_coord_access_request_depth =
                        xdomain_coord.access_request_depth());
  define_old_variable(int old_xrange_coord_access_request_depth =
                        xrange_coord.access_request_depth());

  if(xauto_access)
  {
    xdomain_coord.get_read_access();
    xrange_coord.get_read_access();
  }

  // Currently only support binary schema, not ternary schema;
  // see push and discretizaion_pusher.

  require(dynamic_cast<const binary_section_space_schema_member*>
    (&(xrange_coord.schema())));

  // Body:

  _domain = &xdomain_coord.schema().host()->base_space();
  _range = &xrange_coord.schema().host()->base_space();

  _domain_coords.attach_to_state(&xdomain_coord);
  _range_coords.attach_to_state(&xrange_coord);

  // Perform common initialization.

  initialize();

  // Postconditions:

  ensure(invariant());
  ensure(domain().is_same_state(&xdomain_coord.schema().host()->base_space()));
  ensure(range().is_same_state(&xrange_coord.schema().host()->base_space()));

  if(xauto_access)
  {
    xdomain_coord.release_access();
    xrange_coord.release_access();
  }

  ensure(xdomain_coord.access_request_depth() == old_xdomain_coord_access_request_depth);
  ensure(xrange_coord.access_request_depth() == old_xrange_coord_access_request_depth);

  // Exit:
}

fields::base_space_map::
base_space_map(const base_space_map& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fields::base_space_map::
~base_space_map()
{
  // Preconditions:

  // Body:

  _domain_coords.detach_from_state();
  _range_coords.detach_from_state();

  delete _default_overlap_action;
  delete _default_extension_action;

  if(_coord_branch_id_space != 0)
  {
    _coord_branch_id_space->release_id_space();
  }

  for(int i = 0; i < _prop_branch_id_spaces.ub(); i++)
  {
    if(_prop_branch_id_spaces[i] != 0)
    {
      _prop_branch_id_spaces[i]->release_id_space();
    }
  }
  
  // Postconditions:

  // Exit:
}


const fiber_bundle::base_space_poset&
fields::base_space_map::
domain() const
{
  // Preconditions:

  // Body:

  const base_space_poset& result = *_domain;

  // Postconditions:

  // Exit

  return result;
}

const geometry::sec_ed_invertible&
fields::base_space_map::
domain_coords() const
{
  // Preconditions:

  // Body:

  const geometry::sec_ed_invertible& result = _domain_coords;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::base_space_poset&
fields::base_space_map::
range() const
{
  // Preconditions:

  // Body:

  const base_space_poset& result = *_range;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::sec_ed&
fields::base_space_map::
range_coords() const
{
  // Preconditions:

  // Body:

  const sec_ed& result = _range_coords;

  // Postconditions:

  // Exit

  return result;
}

void
fields::base_space_map::
push(const sec_vd& xinput, sec_vd& xoutput, bool xauto_access)
{
  // Preconditions:

  /// @todo improve this precondition.

  require(precondition_of(push(block, block, bool)));

  // Body:

  block<sec_vd*> linputs(1);
  linputs.push_back(&const_cast<sec_vd&>(xinput));
  //linputs.push_back(&xinput);

  block<sec_vd*> loutputs(1);
  loutputs.push_back(&xoutput);

  push(linputs, loutputs, xauto_access);

  // Postconditions:


  // Exit:

  return;
}


void
fields::base_space_map::
push(const block<sec_vd*>& xinputs, block<sec_vd*>& xoutputs, bool xauto_access)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering push:");
#endif

  // Preconditions:

  require(xinputs.ct() > 0);
  require(xoutputs.ct() == xinputs.ct());


  require_for_all(i, 0, xinputs.ct(),
                  xauto_access || xinputs[i]->state_is_read_accessible());
  require_for_all(i, 0, xoutputs.ct(),
                  xauto_access || xoutputs[i]->state_is_read_write_accessible());

  require(xauto_access || domain_coords().state_is_read_accessible());
  require(xauto_access || range_coords().state_is_read_accessible());

  require_for_all(i, 1, xoutputs.ct(),
                  same_base(*xoutputs[i], *xoutputs[0], xauto_access));
  require_for_all(i, 1, xoutputs.ct(),
                  same_rep(*xoutputs[i], *xoutputs[0], xauto_access));

  require(unexecutable("all multisection inputs must be defined on the same decomposition"));

  define_old_variable(int old_domain_coord_access_request_depth =
                        domain_coords().access_request_depth());
  define_old_variable(int old_range_coord_access_request_depth =
                        range_coords().access_request_depth());


  if(xauto_access)
  {
    for(int i=0; i<xinputs.ct(); ++i)
    {
      xinputs[i]->get_read_access();
      xoutputs[i]->get_read_write_access(true);
    }

    domain_coords().get_read_access();
    range_coords().get_read_access();
  }

  require_for_all(i, 0, xinputs.ct(),
                  domain().contains_member(&xinputs[i]->schema().base_space(), xauto_access));
  require_for_all(i, 0, xoutputs.ct(),
                  range().contains_member(&xoutputs[i]->schema().base_space(), xauto_access));

  // Body:

  set_control_section(xinputs);

  sec_vd& linput = *xinputs[_control_section];
  sec_vd& loutput = *xoutputs[_control_section];

  set_branch_id_spaces(xinputs);

  // Allocate the dof buffers.

  make_dof_buffers(xinputs, xoutputs);

  // Allocate the branch pullback maps and
  // populate the chart to branch map.

  make_maps(linput);

  // Populate the branch pullback maps.

  pull_back_output_disc(linput, loutput.schema());

  // Define the part of the dst that overlaps the src.

  define_overlap(xinputs, xoutputs);

  // Define the part of the dst that does not overlap the src.

  define_extension(xoutputs);

  // Clean up.

  clear_maps();
  clear_dof_buffers();

  if(xauto_access)
  {
    range_coords().release_access();
    domain_coords().release_access();

    for(int i=0; i<xinputs.ct(); ++i)
    {
      xoutputs[i]->release_access();
      xinputs[i]->release_access();
    }
  }

  // Postconditions:

  ensure(domain_coords().access_request_depth() == old_domain_coord_access_request_depth);
  ensure(range_coords().access_request_depth() == old_range_coord_access_request_depth);

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving push:");
#endif

  // Exit

  return;
}


bool
fields::base_space_map::
same_base(const sec_vd& xsec1, const sec_vd& xsec2, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || xsec1.state_is_read_accessible());
  require(xauto_access || xsec2.state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xsec1.get_read_access();
    xsec2.get_read_access();
  }

  result = xsec1.schema().base_space().is_same_state(&xsec2.schema().base_space());

  if(xauto_access)
  {
    xsec1.release_access();
    xsec2.release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}


bool
fields::base_space_map::
same_rep(const sec_vd& xsec1, const sec_vd& xsec2, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || xsec1.state_is_read_accessible());
  require(xauto_access || xsec2.state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xsec1.get_read_access();
    xsec2.get_read_access();
  }

  result = xsec1.schema().rep().is_same_state(&xsec2.schema().rep());

  if(xauto_access)
  {
    xsec1.release_access();
    xsec2.release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
fields::base_space_map::
same_fiber(const sec_vd& xsec1, const sec_vd& xsec2, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || xsec1.state_is_read_accessible());
  require(xauto_access || xsec2.state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xsec1.get_read_access();
    xsec2.get_read_access();
  }

  result =
    xsec1.schema().fiber_schema().is_same_state(&xsec2.schema().fiber_schema())
    && (xsec1.schema().df() == xsec2.schema().df());

  if(xauto_access)
  {
    xsec1.release_access();
    xsec2.release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

fields::base_space_map_push_action&
fields::base_space_map::
overlap_action() const
{
  return *_overlap_action;
}

fields::base_space_map_push_action&
fields::base_space_map::
default_overlap_action() const
{
  return *_default_overlap_action;
}

fields::base_space_map_push_action&
fields::base_space_map::
extension_action() const
{
  return *_extension_action;
}

fields::base_space_map_push_action&
fields::base_space_map::
default_extension_action() const
{
  return *_default_extension_action;
}


void
fields::base_space_map::
put_overlap_action(base_space_map_push_action& xoverlap_action)
{
  // Preconditions:


  // Body:

  _overlap_action = &xoverlap_action;

  // Postconditions:

  ensure(&overlap_action() == &xoverlap_action);

  // Exit:

  return;
}

void
fields::base_space_map::
put_extension_action(base_space_map_push_action& xextension_action)
{
  // Preconditions:


  // Body:

  _extension_action = &xextension_action;

  // Postconditions:

  ensure(&extension_action() == &xextension_action);

  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

fields::base_space_map::
base_space_map()
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return;
}


// PRIVATE MEMBER FUNCTIONS

void
fields::base_space_map::
pull_back_output_disc(const sec_vd& xinput, section_space_schema_member& xoutput_schema)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering pull_back_output");
#endif

  // Preconditions:

  require(domain_coords().state_is_read_accessible());
  require(range_coords().state_is_read_accessible());

  // Body:

  // Allocate some useful local variables.

  pb_type lpb;
  set< stl_scoped_index<> > lbranches;
  int lpb_case = (domain_coords().is_jim() ? 0 : 2) + (xinput.is_jim() ? 0 : 1);

  if(!_domain_coords.is_invertible())
  {
    // Initialize inversion using defaults.

    _domain_coords.initialize_point_locator(false);
  }

  // Iterate over the property disc.

  property_disc_iterator* ldisc_itr =
    property_disc_iterator::new_property_disc_iterator(_range_coords.schema(),
        xoutput_schema);
  while(!ldisc_itr->is_done())
  {
    // Get the context for all the property disc members associated
    // with the current iteration.

    ldisc_itr->get_prop_disc_values(_range_coords);

    // Iterate over all the property disc members.

    const block<discretization_context>& lprop_mbrs =
      ldisc_itr->property_discretization_members();
    size_type lct = lprop_mbrs.ct();
    for(size_type i=0; i<lct; ++i)
    {
      // Get the context for this disc member and pull it back to domain.

      discretization_context& lcontext = lprop_mbrs[i];

      switch(lpb_case)
      {
      case 0:
        pull_back_output_disc_mono_mono(lcontext, lpb);
        break;
      case 1:
        pull_back_output_disc_mono_multi(lcontext, lpb, lbranches);
        break;
      case 2:
        pull_back_output_disc_multi_mono(lcontext, lpb);
        break;
      case 3:
        pull_back_output_disc_multi_multi(lcontext, lpb);
        break;
      }
    }

    ldisc_itr->next();
  }

  delete ldisc_itr;

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving pull_back_output_disc:");
#endif

  return;
}

void
fields::base_space_map::
pull_back_output_disc_mono_mono(const discretization_context& xcontext, pb_type& xpb)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering pull_back_output_disc_mono_mono:");
#endif

  // Preconditions:

  // Body:

  xpb.disc_id = xcontext.disc_id;

  // Invert the domain global coordinates to get the pull back of
  // the output discretization point into domain local coordinates.

  _domain_coords.point_at_value_ua(xcontext.values,
                                   xcontext.values_ub,
                                   xpb.domain_pt);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "inserting pullback entry: " << xpb << endl;
#endif

  _pb_maps[_first_branch.pod()]->insert(xpb);

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving pull_back_output_disc_mono_mono:");
#endif

  return;
}

void
fields::base_space_map::
pull_back_output_disc_mono_multi(const discretization_context& xcontext,
                                 pb_type& xpb,
                                 std::set< stl_scoped_index<> >& xbranches)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering pull_back_output_disc_mono_multi:");
#endif

  // Preconditions:

  // Body:

  xpb.disc_id = xcontext.disc_id;

  // Invert the domain global coordinates to get the pull back of
  // the output discretization point into domain local coordinates.

  _chart_pts.set_ct(0);

  _domain_coords.all_points_at_value_ua(xcontext.values,
                                        xcontext.values_ub,
                                        _chart_pts);

  if(_chart_pts.ct() > 0)
  {
    // This output disc point has one or more pullbacks to the domain.

    // Sort pullbacks into maps by branch so that there is
    // exactly one chart point for each disc id in each branch
    // that contains the disc point.

    // Clear the set of branches containing the current disc id.

    xbranches.clear();

    // Iterate over all the chart points for this disc id.

    for(int i=0; i<_chart_pts.ct(); ++i)
    {

#ifdef DIAGNOSTIC_OUTPUT
      cout << "i: " << i << " chart pt[i]: " << _chart_pts[i] << endl;
#endif
      // Iterate over all the branches containing the current chart.

      typedef chart_to_branch_map_type::iterator map_itr_type;
      typedef pair<map_itr_type, map_itr_type> map_range_type;

      map_range_type lrange =
        _chart_to_branch_map.equal_range(_chart_pts[i].chart_id());

      map_itr_type lmap_itr = lrange.first;
      while(lmap_itr != lrange.second)
      {
        scoped_index lbranch_id = lmap_itr->second;
        if(xbranches.find(lbranch_id) == xbranches.end())
        {
          // We have not yet stored a chart point
          // for this disc id in this branch pullback map.
          // Insert the pullback in the pullback map.

          xpb.domain_pt = _chart_pts[i];

#ifdef DIAGNOSTIC_OUTPUT

          cout << "inserting pullback entry: " << xpb << endl;
#endif

          scoped_index lbranch_id = lmap_itr->second;

          _pb_maps[lbranch_id.pod()]->insert(xpb);

          // Add this branch to the set of branches for this disc.

          xbranches.insert(lbranch_id);
        }
        else
        {
          // We already have a chart point for this disc id in this branch
          // and we only want one. Ignore this chart point.

#ifdef DIAGNOSTIC_OUTPUT
          cout << "Ignoring chart pt." << endl;
#endif

        }
        ++lmap_itr;
      } // end while branches
    } // end for chart pts
  } // end if chart pts
  else
  {
    // This output disc point has no pullbacks to the domain.
    // Enter it as an invalid chart point in the map for branch 0.

    xpb.domain_pt.invalidate();

    _pb_maps[_first_branch.pod()]->insert(xpb);
  }

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Leaving pull_back_output_disc_mono_multi:");
#endif

  return;
}

void
fields::base_space_map::
pull_back_output_disc_multi_mono(const discretization_context& xcontext, pb_type& xpb)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering pull_back_output_disc_multi_mono:");
#endif

  // Preconditions:

  // Body:

  xpb.disc_id = xcontext.disc_id;

  // Invert the domain global coordinates to get the pull back of
  // the output discretization point into domain local coordinates.

  _branch_pts.set_ct(0);

  _domain_coords.branch_points_at_value_ua(xcontext.values,
      xcontext.values_ub,
      _branch_pts);

  if(_branch_pts.ct() > 0)
  {
    // This output disc point has one or more pullbacks to the domain.
    // Iterate over all the chart points for this disc id.

    for(int i=0; i<_branch_pts.ct(); ++i)
    {
      xpb.domain_pt = _branch_pts[i].second;

      _pb_maps[_first_branch.pod()]->insert(xpb);

#ifdef DIAGNOSTIC_OUTPUT

      cout << "inserted pullback entry: " << xpb << endl;
#endif

    }
  }
  else
  {
    // This output disc point has no pullbacks to the domain.
    // Enter it as an invalid chart point in the map for branch 0.

#ifdef DIAGNOSTIC_OUTPUT
    cout << "no pullback for disc id " << xpb.disc_id
    <<" with coords:"
    << setw(18) << xcontext.values[0]
    << setw(18) << xcontext.values[1]
    << setw(18) << xcontext.values[2]
    << endl;
#endif

    xpb.domain_pt.invalidate();

    _pb_maps[_first_branch.pod()]->insert(xpb);
  }

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving pull_back_output_disc_multi_mono:");
#endif

  return;
}

void
fields::base_space_map::
pull_back_output_disc_multi_multi(const discretization_context& xcontext, pb_type& xpb)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering pull_back_output_disc_multi_mono:");
#endif

  // Preconditions:

  require(_domain_coords.state_is_read_accessible());
  require(_range_coords.state_is_read_accessible());

  // Body:

  xpb.disc_id = xcontext.disc_id;

  // Invert the domain global coordinates to get the pull back of
  // the output discretization point into domain local coordinates.

  _branch_pts.set_ct(0);

  _domain_coords.branch_points_at_value_ua(xcontext.values,
      xcontext.values_ub,
      _branch_pts);

  if(_branch_pts.ct() > 0)
  {
    // This output disc point has one or more pullbacks to the domain.
    // Iterate over all the chart points for this disc id.

    for(int i=0; i<_branch_pts.ct(); ++i)
    {

      xpb.domain_pt = _branch_pts[i].second;

      pod_index_type lseq_id =
	_coord_branch_id_space->pod(_branch_pts[i].first);

      pod_index_type lbranch_id =
	_control_branch_id_space->hub_pod(lseq_id);

      _pb_maps[lbranch_id]->insert(xpb);

#ifdef DIAGNOSTIC_OUTPUT

      cout << "inserting pullback entry: " << xpb
      << " in branch " << lbranch_id
      << endl;
#endif

    }
  }
  else
  {
    // This output disc point has no pullbacks to the domain.
    // Enter it as an invalid chart point in the map for branch 0.

#ifdef DIAGNOSTIC_OUTPUT
    cout << "no pullback for disc id " << xpb.disc_id
    <<" with coords:"
    << setw(18) << xcontext.values[0]
    << setw(18) << xcontext.values[1]
    << setw(18) << xcontext.values[2]
    << endl;
#endif

    xpb.domain_pt.invalidate();

    _pb_maps[_first_branch.pod()]->insert(xpb);
  }

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Leaving pull_back_output_disc_multi_mono:");
#endif

  return;
}

void
fields::base_space_map::
set_control_section(const block<sec_vd*>& xinputs)
{
  // Preconditions:

  require(xinputs.ct() > 0);
  require_for_all(i, 0, xinputs.ct(), xinputs[i]->state_is_read_accessible());

  // Body:

  _control_section = 0;
  for(int i=0; i<xinputs.ct(); ++i)
  {
    if(xinputs[i]->is_multisection(false))
    {
      _control_section = i;
      break;
    }
  }


  // Postconditions:

  ensure((0 <= _control_section) && (_control_section < xinputs.ct()));

  // Exit:

  return;
}

void
fields::base_space_map::
set_branch_id_spaces(const block<sec_vd*>& xinputs)
{
  // Preconditions:

  require(xinputs.ct() > 0);
  require_for_all(i, 0, xinputs.ct(), xinputs[i]->state_is_read_accessible());

  // Body:

  // Release old handles.

  if(_coord_branch_id_space != 0)
  {
    _coord_branch_id_space->release_id_space();
  }

  for(int i=0; i<_prop_branch_id_spaces.ub(); ++i)
  {
    if(_prop_branch_id_spaces[i] != 0)
    {
      _prop_branch_id_spaces[i]->release_id_space();
    }
  }

  // Get new handles.

  if(_domain_coords.is_multisection(false))
  {
    _coord_branch_id_space = &_domain_coords.get_branch_id_space(false);
  }
  else
  {
    _coord_branch_id_space = 0;
  }

  _prop_branch_id_spaces.reserve(xinputs.ct());
  _prop_branch_id_spaces.set_ct(0);
  for(int i=0; i<xinputs.ct(); ++i)
  {
    if(xinputs[i]->is_multisection(false))
    {
      _prop_branch_id_spaces.push_back(&xinputs[i]->get_branch_id_space(false));
    }
    else
    {
      _prop_branch_id_spaces.push_back(0);
    }
  }

  _control_branch_id_space = _prop_branch_id_spaces[_control_section];

  // Postconditions:

  ensure(_prop_branch_id_spaces.ct() == xinputs.ct());

  // Exit:

  return;
}

void
fields::base_space_map::
make_maps(sec_vd& xinput)
{
  // Preconditions:


  // Body:

  /// @todo rename this function to indicate all that it does.

  // Allocate the branch pullback maps and
  // populate the chart to branch map.

  _pb_maps.reserve(_domain->member_index_ub().pod());

  _pb_maps.set_ct(_pb_maps.ub());
  _pb_maps.assign(0);

  /// @hack the multisection hack.
  /// Initialize an iterator for the evaluation members (charts)
  /// contained in each branch. Will be reset to each branch in loop bleow.

  preorder_iterator leval_itr(xinput.schema().base_space(),
                              xinput.schema().evaluation(),
			      DOWN, NOT_STRICT);
  leval_itr.force_is_done();
  leval_itr.put_visit_once(false);

  // Iterate over the branches.

  sec_vd lbranch;
  preorder_iterator lbranch_itr(xinput, "jims", DOWN, NOT_STRICT);
  _first_branch = lbranch_itr.index();
  while(!lbranch_itr.is_done())
  {
    scoped_index lbranch_id = lbranch_itr.index();

    // Allocate the pullback map for this

    _pb_maps[lbranch_id.pod()] = new pb_map_type;

    // Re-anchor the eval itr to this branch.

    lbranch.attach_to_state(xinput.host(), lbranch_id);
    leval_itr.put_anchor(lbranch.schema().base_space_id());
    lbranch.detach_from_state();

    leval_itr.reset(false);

    // Iterate over the eval members in this branch,
    // populating the chart to branch map.

    while(!leval_itr.is_done())
    {
      chart_to_branch_map_type::value_type lval(leval_itr.index().hub_pod(), lbranch_id);
      _chart_to_branch_map.insert(lval);
      leval_itr.truncate();
    }

    // Move on to the next branch.

    lbranch_itr.truncate();
  }

  // Postconditions:


  // Exit:

  return;
}

void
fields::base_space_map::
clear_maps()
{
  // Preconditions:


  // Body:

  // Deallocate the pullback maps.

  for(int i=0; i<_pb_maps.ct(); ++i)
  {
    pb_map_type*& lpb_map = _pb_maps[i];

    if(lpb_map != 0)
    {
      delete lpb_map;
      lpb_map = 0;
    }
  }

  // Clear the first brnach id.

  _first_branch.invalidate();

  // Clear the chart to branch map.

  _chart_to_branch_map.clear();

  // Postconditions:


  // Exit:

  return;
}

void
fields::base_space_map::
make_dof_buffers(const block<sec_vd*>& xinputs, block<sec_vd*>& xoutputs)
{
  // Preconditions:

  require(xinputs.ct() == xoutputs.ct());

  // Body:

  int lct = xinputs.ct();

  _in_dofs.reserve(lct);
  _in_dofs.set_ct(0);

  _out_dofs.reserve(lct);
  _out_dofs.set_ct(0);

  for(int i=0; i<lct; ++i)
  {
    _in_dofs.push_back(new block<sec_vd_dof_type>(xinputs[i]->schema().df()));
    _out_dofs.push_back(new block<sec_vd_dof_type>(xoutputs[i]->schema().df()));
  }

  // Postconditions:


  // Exit:

  return;
}

void
fields::base_space_map::
clear_dof_buffers()
{
  // Preconditions:


  // Body:

  for(int i=0; i<_in_dofs.ct(); ++i)
  {
    delete _in_dofs[i];
    delete _out_dofs[i];
  }

  _in_dofs.set_ct(0);
  _out_dofs.set_ct(0);

  // Postconditions:


  // Exit:

  return;
}

void
fields::base_space_map::
define_overlap(const block<sec_vd*>& xinputs, block<sec_vd*>& xoutputs)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering define_overlap:");
#endif

  // Preconditions:

  require(xinputs.ct() > 0);
  require(xoutputs.ct() == xinputs.ct());

  require_for_all(i, 0, xinputs.ct(), xinputs[i]->state_is_read_accessible());
  require_for_all(i, 0, xoutputs.ct(), xoutputs[i]->state_is_read_write_accessible());

  require(unexecutable("all multisection inputs must be defined on the same decomposition"));
  require_for_all(i, 0, xinputs.ct(),
                  xinputs[i]->is_multisection(false) ?
                  xinputs[i]->has_branch_id_space(false) : true);

  // Body:

  // Do whatever preprocessing the overlap action wants.

  _overlap_action->initialize(xoutputs);

  // Save copies of the inputs so we can temporarily
  // replace any multisection inputs in the branch loop below.

  block<sec_vd*> linputs(xinputs.ct());
  for(int i=0; i<xinputs.ct(); ++i)
  {
    linputs.push_back(xinputs[i]->clone(false, false));
  }

  assertion(linputs.ct() == xinputs.ct());

  sec_vd* lcontrol_section = xinputs[_control_section];
  sec_vd* lcontrol_branch = linputs[_control_section];

  // Create an eval iterator for use on each branch of xinput.

  /// @hack the multisection hack.
  /// Create with visit_once = false so we don't have to
  /// reset the O(member_ub) visited bit vector for each branch.

  eval_iterator leval_itr(lcontrol_section->schema(), false);
  leval_itr.force_is_done();

  // Iterate over the branches of xinput.
  // The branches of xinput are the maximal jims in its down set.
  // If xinput is not a multi-section, xinput itself is its only branch.

  preorder_iterator lbranch_itr(*lcontrol_section, "jims", DOWN, NOT_STRICT);
  while(!lbranch_itr.is_done())
  {
    scoped_index branch_index = lbranch_itr.index();

    // Attach a handle to the current branch of each multisection.

    for(int i=0; i<linputs.ct(); ++i)
    {
      if(xinputs[i]->is_multisection(false))
      {
        pod_index_type lseq_id = _control_branch_id_space->pod(branch_index);

	scoped_index lposet_id(lseq_id, *_prop_branch_id_spaces[i]);

        linputs[i]->attach_to_state(lposet_id);
      }
    }

    // Iterate over the evaluation members of the input;
    // process all the pullbacks contained in each eval member.

    // Reanchor the eval itr to this branch without resetting bit vector.

    leval_itr.put_schema_anchor(lcontrol_branch->schema().index());
    leval_itr.reset(false);

    while(!leval_itr.is_done())
    {
      push_eval_mbr(leval_itr, linputs, xoutputs);
      leval_itr.next();
    }

    // Don't need to go deeper.

    lbranch_itr.truncate();
  }


  // Do whatever postprocessing the overlap action wants.

  _overlap_action->finalize(xoutputs);

  // Clean up.

  for(int i=0; i<linputs.ct(); ++i)
  {
    linputs[i]->detach_from_state();
    delete linputs[i];
  }

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Leaving define_overlap:");
#endif

  return;
}

void
fields::base_space_map::
push_eval_mbr(const eval_iterator& xeval_itr,
              const block<sec_vd*>& xinputs,
              block<sec_vd*>& xoutputs)
{
  // Preconditions:

  require_for_all(i, 0, xinputs.ct(), xinputs[i]->state_is_read_accessible());
  require_for_all(i, 0, xinputs.ct(), xinputs[i]->is_jim(false));

  require_for_all(i, 0, xoutputs.ct(), xoutputs[i]->state_is_read_write_accessible());
  require_for_all(i, 0, xinputs.ct(), xoutputs[i]->is_jim(false));

  // Body:

  // Try to get the list of pullbacks for this eval member in this branch.

  pb_map_range_type litr_range =
    _pb_maps[xinputs[_control_section]->index().pod()]->
    equal_range(pb_type(xeval_itr.index()));

  if(litr_range.first != litr_range.second)
  {
    // The iterator range is not empty.
    // This eval member contains pullback points in its base space.
    // We will evaluate the input field for each pullback,
    // but first we'll need to gather the input dofs.

    //$$SCRIBBLE: We need to do this cast here because gather_dofs is not const.

    eval_iterator& leval_itr = const_cast<eval_iterator&>(xeval_itr);

    for(int i=0; i<xinputs.ct(); ++i)
    {
      _in_dofs[i]->set_ct(0);

      leval_itr.gather_dofs(*xinputs[i], *_in_dofs[i]);
      //xeval_itr.gather_dofs(*xinputs[i], *_in_dofs[i]);
    }

    // Get the evaluator for this eval member.

    const section_evaluator& levaluator = xeval_itr.evaluator();

    // Iterate over the  pullback points, evaluating
    // the input at each point.

    for(pb_map_itr_type itr = litr_range.first; itr != litr_range.second; ++itr)
    {
      // Evaluate each input at the pullback point.

      for(int i=0; i<xinputs.ct(); ++i)
      {
        _out_dofs[i]->set_ct(_out_dofs[i]->ub());
        levaluator.value_at_coord(_in_dofs[i]->base(),
                                  _in_dofs[i]->ct(),
                                  itr->domain_pt.local_coords(),
                                  _domain_db,
                                  _out_dofs[i]->base(),
                                  _out_dofs[i]->ct());
      }


      // Let the overlap action do what ever it wants.

      (*_overlap_action)(itr, xoutputs, _out_dofs);


#ifdef DIAGNOSTIC_OUTPUT

      print_debug_info(xeval_itr.range_id(), *xoutputs[_control_section], itr, _out_dofs);
#endif

      // Scatter the dofs into the outputs.

      for(int i=0; i<xoutputs.ct(); ++i)
      {
	xoutputs[i]->put_fiber(itr->disc_id,
			       _out_dofs[i]->base(),
			       _out_dofs[i]->ct()*sizeof(sec_vd_dof_type),
			       false);
      }

    }

  }
  else
  {
    // This eval member does not contain any pullback points;
    // do nothing, just skip it.
  }

  // Postconditions:


  // Exit:

  return;
}

void
fields::base_space_map::
define_extension(block<sec_vd*>& xoutputs)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering define_extension:");
#endif

  // Preconditions:


  // Body:

  // Have evaluated the result for all discretization members that
  // have pullbacks. Still have to process the members that do not
  // have pullbacks.

  // Do whatever preprocessing the extension action wants.

  _extension_action->initialize(xoutputs);

  // Iterate over the disc members in the extension.
  // These are all in the pullback list of chart id NOT_AN_INDEX for branch 0.

  pb_map_type* lpb_map = _pb_maps[_first_branch.pod()];

  pb_map_range_type litr_range = lpb_map->equal_range(invalid_pod_index());

  for(pb_map_itr_type itr = litr_range.first; itr != litr_range.second; ++itr)
  {
    // There is no value of the input associated with this
    // discretization member, so define the dofs by extension.

    (*_extension_action)(itr, xoutputs, _out_dofs);


#ifdef DIAGNOSTIC_OUTPUT

    print_debug_info(NOT_AN_INDEX, *xoutputs[_control_section], itr, _out_dofs);
#endif

    // Scatter the dofs into the result.

    for(int i=0; i<xoutputs.ct(); ++i)
    {
      xoutputs[i]->put_fiber(itr->disc_id,
			     _out_dofs[i]->base(),
			     _out_dofs[i]->ct()*sizeof(sec_vd_dof_type),
			     false);
    }

  }

  // Do whatever postprocessing the extension action wants.

  _extension_action->finalize(xoutputs);

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving define_extension:");
#endif

  return;
}

void
fields::base_space_map::
initialize()
{
  // Preconditions:

  require(domain().state_is_read_accessible());

  // Body:

  _domain_db = _domain->max_db();

  // Initialize the push actions.

  _default_overlap_action = new copy_base_space_map_push_action();
  _overlap_action = _default_overlap_action;

  _default_extension_action = new constant_base_space_map_push_action();
  _extension_action = _default_extension_action;


  // Allocate the pullback map buffer.

  _pb_maps.reserve(_domain->member_index_ub().pod());

  _pb_maps.set_ct(_pb_maps.ub());
  _pb_maps.assign(0);

  _first_branch.invalidate();

  // Initialize point buffers to avoid many small reallocations.

  _chart_pts.reserve(32);
  _branch_pts.reserve(32);

  // Postconditions:


  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::base_space_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(any::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================


