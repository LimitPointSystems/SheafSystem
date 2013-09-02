
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class section_pusher
/// A map from one sec_rep_space to another.

#include "assert_contract.h"
#include "arg_list.h"
#include "binary_section_space_schema_member.h"
#include "block.impl.h"
#include "constant_push_action.h"
#include "copy_push_action.h"
#include "discretization_context.h"
#include "discretization_iterator.h"
#include "discretization_pusher.h"
#include "error_message.h"
#include "eval_iterator.h"
#include "field_vd.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.h"
#include "postorder_iterator.h"
#include "preorder_iterator.h"
#include "property_disc_iterator.h"
#include "sec_at1_space.h"
#include "sec_ed_invertible.h"
#include "sec_rep_descriptor.h"
#include "sec_vd_space.h"
#include "section_evaluator.h"
#include "section_pusher.h"
#include "section_pusher_push_action.h"
#include "stl_scoped_index.h"
#include "field_vd.h"

using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1

namespace fields
{

void print_debug_info(scoped_index xeval_client_id,
                      sec_rep_space& xrange,
                      pullback_map::iterator& xitr,
                      block<sec_vd_dof_type>& xdst_dofs)
{
  cout << "eval id: " << setw(5) << xeval_client_id;
  index_space_handle& lspace = xrange.schema().discretization().id_space();
  cout << "  disc_id: " << setw(5) << lspace.pod(xitr->disc_id);
  cout << " source point:";
  int ldb = xitr->domain_pt.db();
  for(size_type j=0; j<ldb; ++j)
  {
    cout << setw(12) << setprecision(3) << xitr->domain_pt.local_coord(j);
  }
  cout << setw(5) << xitr->domain_pt.chart_id();
  cout << " dst value:";
  int ldf = xdst_dofs.ct();
  for(size_type j=0; j<ldf; ++j)
  {
    cout << setw(12) << setprecision(3) << xdst_dofs[j];
  }
  cout << endl;
};

} // namespace fields

// =============================================================================
// SECTION_PUSHER FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::section_pusher::
section_pusher(const field_vd& xsrc, const field_vd& xdst, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || xsrc.state_is_read_accessible());
  require(xauto_access || xdst.state_is_read_accessible());

  define_old_variable(int old_xsrc_access_request_depth = xsrc.access_request_depth());
  define_old_variable(int old_xdst_access_request_depth = xdst.access_request_depth());

  if(xauto_access)
  {
    xsrc.get_read_access();
    xdst.get_read_access();
  }

  require(same_fiber(*xsrc.property().host(), *xdst.property().host()));
  require(same_fiber(*xsrc.coordinates().host(), *xdst.coordinates().host()));

  // Currently only support binary schema, not ternary schema;
  // see push_pa and discretizaion_pusher.

  require(dynamic_cast<binary_section_space_schema_member*>(&(xdst.coordinates().schema())));
  require(dynamic_cast<binary_section_space_schema_member*>(&(xdst.property().schema())));

  // Body:

  _domain = xsrc.property().host();
  _range = xdst.property().host();

  _domain_coords.attach_to_state(&xsrc.coordinates());
  _range_coords.attach_to_state(&xdst.coordinates());

  // Perform common initialization.

  initialize();

  // Postconditions:

  ensure(invariant());
  ensure(domain().is_same_state(xsrc.property().host()));
  ensure(range().is_same_state(xdst.property().host()));

  if(xauto_access)
  {
    xsrc.release_access();
    xdst.release_access();
  }

  ensure(xsrc.access_request_depth() == old_xsrc_access_request_depth);
  ensure(xdst.access_request_depth() == old_xdst_access_request_depth);

  // Exit:

  return;
}

// fields::section_pusher::
// section_pusher(const field_vd& xsrc, const sec_ed& xdst_coords,
//                bool xauto_access)
// {
//   // Preconditions:

//   require(xauto_access || xsrc.state_is_read_accessible());
//   require(xauto_access || xdst_coords.state_is_read_accessible());
//   require(xauto_access || xdst_coords.name_space()->state_is_read_accessible());

//   define_old_variable(int old_xsrc_access_request_depth = xsrc.access_request_depth());
//   define_old_variable(int old_xdst_coords_access_request_depth = xdst_coords.access_request_depth());

//   if(xauto_access)
//   {
//     xsrc.get_read_access();
//     xdst_coords.get_read_access();
//     xdst_coords.name_space()->get_read_access();
//   }

//   require(!xsrc.name_space().contains_poset(sec_rep_space_member::standard_section_space_name(xsrc.property().schema().fiber_space().name(),
//           xdst_coords.schema().base_space().host()->name()), false));

//   require(same_fiber(*xsrc.coordinates().host(), *xdst_coords.host()));

//   // Currently only support binary schema, not ternary schema;
//   // see push_pa and discretizaion_pusher.

//   require(dynamic_cast<const binary_section_space_schema_member*>(&(xdst_coords.schema())));

//   // Body:

//   // Get the domain.

//   _domain = xsrc.property().host();

//   _domain_coords.attach_to_state(&xsrc.coordinates());
//   _range_coords.attach_to_state(&xdst_coords);

//   section_space_schema_member& ldomain_schema = _domain->schema();

//   // Create the range.

//   string lrange_prop_fiber_name = ldomain_schema.fiber_space().name();
//   string lrange_base_name = xdst_coords.schema().base_space().host()->name();
//   string lrange_name =
//     sec_rep_space_member::standard_section_space_name(lrange_prop_fiber_name,
// 						      lrange_base_name);

//   fiber_bundles_namespace* lns = dynamic_cast<fiber_bundles_namespace*>(xdst_coords.name_space());

//   poset_path lsssp(ldomain_schema.fiber_space().path().poset_name() + 
// 		   "_on_" + 
// 		   xdst_coords.schema().base_space().path().poset_name() +
// 		   "_" +
// 		   ldomain_schema.rep().path().member_name() +
// 		   "_schema",
// 		   ldomain_schema.fiber_space().path().poset_name() + 
// 		   "_on_" + 
// 		   xdst_coords.schema().base_space().path().member_name());

//   poset_path lrange_schema_path =
//     lns->new_section_space_schema(lsssp,
// 				  ldomain_schema.rep().path(),
// 				  xdst_coords.schema().base_space().path(),
// 				  ldomain_schema.fiber_space().path(),
// 				  true);

//   arg_list largs;
//   largs << "factor_ct" << -1
// 	<< "d" << -1
// 	<< "scalar_space_path" << ""
// 	<< "p" << -1
// 	<< "dd" << -1
// 	<<"vector_space_path" << "";

//   _range =
//     &lns->clone_section_space(_domain->path(), lrange_name, largs, lrange_schema_path, true);

//   _range->get_read_access();

//   // Perform common initialization.

//   initialize();

//   // Postconditions:

//   ensure(invariant());
//   ensure(domain().is_same_state(xsrc.property().host()));
//   ensure(same_fiber(range(), domain()));

//   _range->release_access();

//   if(xauto_access)
//   {
//     xdst_coords.name_space()->release_access();
//     xdst_coords.release_access();
//     xsrc.release_access();
//   }

//   ensure(xsrc.access_request_depth() == old_xsrc_access_request_depth);
//   ensure(xdst_coords.access_request_depth() == old_xdst_coords_access_request_depth);

//   // Exit:

//   return;
// }


fields::section_pusher::
section_pusher(const sec_rep_space& xdomain,
               const sec_rep_space& xrange,
               const sec_ed& xdomain_coord,
               const sec_ed& xrange_coord,
               bool xauto_access)
{
  // Preconditions:

  require(xauto_access || xdomain.state_is_read_accessible());
  require(xauto_access || xdomain_coord.state_is_read_accessible());

  require(xauto_access || xrange.state_is_read_accessible());
  require(xauto_access || xrange_coord.state_is_read_accessible());

  define_old_variable(int old_xdomain_access_request_depth =
                        xdomain.access_request_depth());
  define_old_variable(int old_xdomain_coord_access_request_depth =
                        xdomain_coord.access_request_depth());
  define_old_variable(int old_xrange_access_request_depth =
                        xrange.access_request_depth());
  define_old_variable(int old_xrange_coord_access_request_depth =
                        xrange_coord.access_request_depth());

  if(xauto_access)
  {
    xdomain.get_read_access();
    xdomain_coord.get_read_access();
    xrange.get_read_access();
    xrange_coord.get_read_access();
  }

  require(same_base(xdomain_coord, xdomain));
  require(same_base(xrange_coord, xrange));

  require(same_fiber(xdomain, xrange));
  require(same_fiber(*xdomain_coord.host(), *xrange_coord.host()));

  // Currently only support binary schema, not ternary schema;
  // see push_pa and discretizaion_pusher.

  require(dynamic_cast<const binary_section_space_schema_member*>(&(xrange.schema())));
  require(dynamic_cast<const binary_section_space_schema_member*>(&(xrange_coord.schema())));

  // Body:

  /// @issue Either _domain and _range should be const pointers or this
  ///        constructor should pass in non-const referrences.

  _domain = const_cast<sec_rep_space*>(&xdomain);
  _range = const_cast<sec_rep_space*>(&xrange);

  _domain_coords.attach_to_state(&xdomain_coord);
  _range_coords.attach_to_state(&xrange_coord);

  // Perform common initialization.

  initialize();

  // Postconditions:

  ensure(invariant());
  ensure(domain().is_same_state(&xdomain));
  ensure(range().is_same_state(&xrange));

  if(xauto_access)
  {
    xdomain.release_access();
    xdomain_coord.release_access();
    xrange.release_access();
    xrange_coord.release_access();
  }

  ensure(xdomain.access_request_depth() == old_xdomain_access_request_depth);
  ensure(xdomain_coord.access_request_depth() == old_xdomain_coord_access_request_depth);
  ensure(xrange.access_request_depth() == old_xrange_access_request_depth);
  ensure(xrange_coord.access_request_depth() == old_xrange_coord_access_request_depth);

  // Exit:
}

const fiber_bundle::sec_rep_space&
fields::section_pusher::
domain() const
{
  // Preconditions:

  // Body:

  const sec_rep_space& result = *_domain;

  // Postconditions:

  // Exit

  return result;
}

const geometry::sec_ed_invertible&
fields::section_pusher::
domain_coords() const
{
  // Preconditions:

  // Body:

  const geometry::sec_ed_invertible& result = _domain_coords;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::sec_rep_space&
fields::section_pusher::
range() const
{
  // Preconditions:

  // Body:

  const sec_rep_space& result = *_range;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::sec_ed&
fields::section_pusher::
range_coords() const
{
  // Preconditions:

  // Body:

  const sec_ed& result = _range_coords;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_vd*
fields::section_pusher::
push(const sec_vd& xinput, bool xauto_access)
{
  sec_vd* result = 0;

  // Preconditions:

  require(precondition_of(push_pa(xinput, result, xauto_access)));
  require(xauto_access || range().in_jim_edit_mode());

  /// @hack the "pointer bug", see bleow.

  require(xauto_access || range().name_space()->state_is_read_accessible());

  // Body:

  result = xinput.clone();

  /// @hack the "pointer bug".
  /// We need to make a new state for the result,
  /// but we must ensure that the host the state is made with
  /// is persistent, to avoid the "pointer bug", otherwise
  /// we will get a segv if the host gets deleted.
  /// _range is not persisent, so get the corresponding pointer
  /// from the name space.

  sec_rep_space& lrange_host =
    dynamic_cast<sec_rep_space&>(_range->name_space()->member_poset(_range->index()));

  result->new_jim_state(&lrange_host, 0, false, xauto_access);
  push_pa(xinput, *result, xauto_access);

  // Postconditions:

  ensure(result != 0);
  ensure(range().contains_member(result, xauto_access));
  ensure(postcondition_of(push_pa));

  // Exit

  return result;
}

void
fields::section_pusher::
push_pa(const sec_vd& xinput, sec_vd& xresult, bool xauto_access)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering push_pa:");
#endif

  // Preconditions:

  require(xauto_access || xinput.state_is_read_accessible());
  require(xauto_access || xresult.state_is_read_write_accessible());

  require(domain().contains_member(&xinput, xauto_access));
  require(range().contains_member(&xresult, xauto_access));

  require(xauto_access || domain_coords().state_is_read_accessible());
  require(xauto_access || range_coords().state_is_read_accessible());

  define_old_variable(int old_xinput_access_request_depth =
                        xinput.access_request_depth());
  define_old_variable(int old_result_access_request_depth =
                        xresult.access_request_depth());
  define_old_variable(int old_domain_coord_access_request_depth =
                        domain_coords().access_request_depth());
  define_old_variable(int old_range_coord_access_request_depth =
                        range_coords().access_request_depth());


  if(xauto_access)
  {
    xinput.get_read_access();
    xresult.get_read_write_access(true);
    domain_coords().get_read_access();
    range_coords().get_read_access();
  }

  // Body:

  // Allocate the branch pullback maps and
  // populate the chart to branch map.

  make_maps(xinput);

  // Populate the branch pullback maps.

  if(domain_coords().is_jim())
  {
    // The source coordinates is a monosection.

    if(xinput.is_jim())
    {
      // The source property is monosection.

      pull_back_range_disc_mono_mono();
    }
    else
    {
      // The source property is a multisection.

      pull_back_range_disc_mono_multi();
    }
  }
  else
  {
    // The source coordinates is a multisection.

    if(xinput.is_jim())
    {
      // The source property is monosection.

      pull_back_range_disc_multi_mono();
    }
    else
    {
      // The source property is a multisection.

      post_fatal_error_message("Source coordinate multisection with source property multisection not supported");
    }
  }

  // Define the part of the dst that overlaps the src.

  define_overlap(xinput, xresult);

  // Define the part of the dst that does not overlap the src.

  define_extension(xresult);

  // Clean up.

  clear_maps();

  if(xauto_access)
  {
    range_coords().release_access();
    domain_coords().release_access();
    xresult.release_access();
    xinput.release_access();
  }

  // Postconditions:

  ensure(xinput.access_request_depth() == old_xinput_access_request_depth);
  ensure(xresult.access_request_depth() == old_result_access_request_depth);
  ensure(domain_coords().access_request_depth() == old_domain_coord_access_request_depth);
  ensure(range_coords().access_request_depth() == old_range_coord_access_request_depth);

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving push_pa:");
#endif

  // Exit

  return;
}


bool
fields::section_pusher::
same_base(const sec_ed& xcoord, const sec_rep_space& xspace) const
{
  bool result;

  // Preconditions:

  require(xcoord.state_is_read_accessible());
  require(xspace.state_is_read_accessible());

  // Body:

  result = xcoord.schema().base_space().is_same_state(&xspace.schema().base_space());

  // Postconditions:

  ensure(result == xcoord.schema().base_space().is_same_state(&xspace.schema().base_space()));

  // Exit:

  return result;
}


bool
fields::section_pusher::
same_discretization(const sec_ed& xcoord, const sec_rep_space& xspace) const
{
  bool result;

  // Preconditions:

  require(xcoord.state_is_read_accessible());
  require(xspace.state_is_read_accessible());

  // Body:

  result = xcoord.schema().discretization().is_same_state(&xspace.schema().discretization());

  // Postconditions:

  ensure(result == xcoord.schema().discretization().is_same_state(&xspace.schema().discretization()));

  // Exit:

  return result;
}

bool
fields::section_pusher::
same_fiber(const sec_rep_space& xspace1, const sec_rep_space& xspace2) const
{
  bool result;

  // Preconditions:

  require(xspace1.state_is_read_accessible());
  require(xspace2.state_is_read_accessible());

  // Body:

  result =
    xspace1.schema().fiber_schema().is_same_state(&xspace2.schema().fiber_schema())
    && (xspace1.schema().df() == xspace2.schema().df());

  // Postconditions:

  ensure(result ==
         (xspace1.schema().fiber_schema().is_same_state(&xspace2.schema().fiber_schema())
          && (xspace1.schema().df() == xspace2.schema().df())));

  // Exit:

  return result;
}

fields::section_pusher_push_action&
fields::section_pusher::
overlap_action() const
{
  return *_overlap_action;
}

fields::section_pusher_push_action&
fields::section_pusher::
default_overlap_action() const
{
  return *_default_overlap_action;
}

fields::section_pusher_push_action&
fields::section_pusher::
extension_action() const
{
  return *_extension_action;
}

fields::section_pusher_push_action&
fields::section_pusher::
default_extension_action() const
{
  return *_default_extension_action;
}


void
fields::section_pusher::
put_overlap_action(section_pusher_push_action& xoverlap_action)
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
fields::section_pusher::
put_extension_action(section_pusher_push_action& xextension_action)
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

fields::section_pusher::
section_pusher()
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
fields::section_pusher::
make_range_monovalent_subposet(bool xis_ext)
{
  // Preconditions:

  require(domain().state_is_read_accessible());
  require(range().state_is_read_accessible());
  require(range().schema().base_space().state_is_read_write_accessible());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(unexecutable(corresponding members of monovalent subposet in domain and range have same client id));

  // Exit:
}


void
fields::section_pusher::
pull_back_range_disc_mono_mono()
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering pull_back_range_disc_mono_mono:");
#endif

  // Preconditions:

  require(_domain_coords.state_is_read_accessible());
  require(_range_coords.state_is_read_accessible());

  // Body:


  if(!_domain_coords.is_invertible())
  {
    // Initialize inversion using defaults.

    _domain_coords.initialize_point_locator(false);
  }

  // Allocate some useful local variables.

  pb_type lpb;

  // Iterate over the property disc.

  property_disc_iterator* ldisc_itr =
    property_disc_iterator::new_property_disc_iterator(_range_coords.schema(),
        _range->schema());
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
      // Get the context for this disc member.

      discretization_context& lcontext = lprop_mbrs[i];

      lpb.disc_id = lcontext.disc_id;

      // Invert the domain global coordinates to get the pull back of
      // the range discretization point into domain local coordinates.

      _domain_coords.point_at_value_ua(lcontext.values,
                                       lcontext.values_ub,
                                       lpb.domain_pt);

#ifdef DIAGNOSTIC_OUTPUT

      cout << "inserting pullback entry: " << lpb << endl;
#endif

      // _pb_maps index using internal id space.

      _pb_maps[_first_branch.pod()]->insert(lpb);
    }

    ldisc_itr->next();
  }

  delete ldisc_itr;

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving pull_back_range_disc_mono_mono:");
#endif

  return;
}

void
fields::section_pusher::
pull_back_range_disc_mono_multi()
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering pull_back_range_disc_mono_multi:");
#endif

  // Preconditions:

  require(_domain_coords.state_is_read_accessible());
  require(_range_coords.state_is_read_accessible());

  // Body:


  if(!_domain_coords.is_invertible())
  {
    // Initialize inversion using defaults.

    _domain_coords.initialize_point_locator(false);
  }

  // Allocate some useful local variables.

  pb_type lpb;
  block<chart_point_3d> ldomain_pts(32); // Arbitrary size.
  set< stl_scoped_index<> > lbranches;

  // Iterate over the property disc.

  property_disc_iterator* ldisc_itr =
    property_disc_iterator::new_property_disc_iterator(_range_coords.schema(),
						       _range->schema());
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
      // Get the context for this disc member.

      discretization_context& lcontext = lprop_mbrs[i];

      lpb.disc_id = lcontext.disc_id;

      // Invert the domain global coordinates to get the pull back of
      // the range discretization point into domain local coordinates.

      ldomain_pts.set_ct(0);
      _domain_coords.all_points_at_value_ua(lcontext.values,
                                            lcontext.values_ub,
                                            ldomain_pts);

      if(ldomain_pts.ct() > 0)
      {
        // This range disc point has one or more pullbacks to the source.

        // Sort pullbacks into maps by branch so that there is
        // exactly one chart point for each disc id in each branch
        // that contains the disc point.

        // Clear the set of branches containing the current disc id.

        lbranches.clear();

        // Iterate over all the chart points for this disc id.

        for(int i=0; i<ldomain_pts.ct(); ++i)
        {

#ifdef DIAGNOSTIC_OUTPUT
          cout << "i: " << i << " chart pt[i]: " << ldomain_pts[i] << endl;
#endif
          // Iterate over all the branches containing the current chart.

          typedef chart_to_branch_map_type::iterator map_itr_type;
          typedef pair<map_itr_type, map_itr_type> map_range_type;

          map_range_type lrange =
            _chart_to_branch_map.equal_range(ldomain_pts[i].chart_id());

          map_itr_type lmap_itr = lrange.first;
          while(lmap_itr != lrange.second)
          {
            scoped_index lbranch_id = lmap_itr->second;
            if(lbranches.find(lbranch_id) == lbranches.end())
            {
              // We have not yet stored a chart point
              // for this disc id in this branch pullback map.
              // Insert the pullback in the pullback map.

              lpb.domain_pt = ldomain_pts[i];

#ifdef DIAGNOSTIC_OUTPUT

              cout << "inserting pullback entry: " << lpb << endl;
#endif

              scoped_index lbranch_id = lmap_itr->second;

              _pb_maps[lbranch_id.pod()]->insert(lpb);

              // Add this branch to the set of branches for this disc.

              lbranches.insert(lbranch_id);
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
        } // end for domain pts
      } // end if domain pts
      else
      {
        // This range disc point has no pullbacks to the source.
        // Enter it as an invalid chart point in the map for branch 0.

        lpb.domain_pt.invalidate();

        _pb_maps[_first_branch.pod()]->insert(lpb);
      }
    } // end for current disc members

    ldisc_itr->next();
  } // end while disc itr

  delete ldisc_itr;

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving pull_back_range_disc_mono_multi:");
#endif

  return;
}

void
fields::section_pusher::
pull_back_range_disc_multi_mono()
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering pull_back_range_disc_multi_mono:");
#endif

  // Preconditions:

  require(_domain_coords.state_is_read_accessible());
  require(_range_coords.state_is_read_accessible());

  // Body:


  if(!_domain_coords.is_invertible())
  {
    // Initialize inversion using defaults.

    _domain_coords.initialize_point_locator(false);
  }

  // Allocate some useful local variables.

  pb_type lpb;
  block<branch_point_pair> ldomain_pts(32); // Arbitrary size.

  // Iterate over the property disc.

  property_disc_iterator* ldisc_itr =
    property_disc_iterator::new_property_disc_iterator(_range_coords.schema(),
						       _range->schema());
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
      // Get the context for this disc member.

      discretization_context& lcontext = lprop_mbrs[i];

      lpb.disc_id = lcontext.disc_id;

      // Invert the domain global coordinates to get the pull back of
      // the range discretization point into domain local coordinates.

      ldomain_pts.set_ct(0);
      _domain_coords.branch_points_at_value_ua(lcontext.values,
          lcontext.values_ub,
          ldomain_pts);

      if(ldomain_pts.ct() > 0)
      {
        // This range disc point has one or more pullbacks to the source.
        // Iterate over all the chart points for this disc id.

        for(int i=0; i<ldomain_pts.ct(); ++i)
        {

#ifdef DIAGNOSTIC_OUTPUT
          cout << "i: " << i
          << " branch id: " << ldomain_pts[i].first
          << " chart pt[i]: " << ldomain_pts[i].second
          << endl;
#endif

          lpb.domain_pt = ldomain_pts[i].second;

#ifdef DIAGNOSTIC_OUTPUT

          cout << "inserting pullback entry: " << lpb << endl;
#endif

          _pb_maps[_first_branch.pod()]->insert(lpb);
        }
      }
      else
      {
        // This range disc point has no pullbacks to the source.
        // Enter it as an invalid chart point in the map for branch 0.

        lpb.domain_pt.invalidate();

        _pb_maps[_first_branch.pod()]->insert(lpb);
      }
    }

    ldisc_itr->next();
  }

  delete ldisc_itr;

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving pull_back_range_disc_multi_mono:");
#endif

  return;
}

void
fields::section_pusher::
make_maps(const sec_vd& xinput)
{
  // Preconditions:


  // Body:

  /// @todo rename this function to indicate all that it does.

  // Allocate the branch pullback maps and
  // populate the chart to branch map.

  // Use poset internal id space to index _pd_maps.

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

  assertion(_first_branch.is_hub_scope());

  while(!lbranch_itr.is_done())
  {
    const scoped_index& lbranch_id = lbranch_itr.index();

    // Allocate the pullback map for this;
    // use poset internal scope.

    assertion(lbranch_id.is_hub_scope());

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
fields::section_pusher::
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
fields::section_pusher::
define_overlap(const sec_vd& xinput, sec_vd& xresult)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering define_overlap:");
#endif

  // Preconditions:


  // Body:

  // Do whatever preprocessing the overlap action wants.

  _overlap_action->initialize(xresult);

  // Create an eval iterator for use on each branch of xinput.

  /// @hack the multisection hack.
  /// Create with visit_once = false so we don't have to
  /// reset the O(member_ub) visited bit vector for each branch.

  eval_iterator leval_itr(xinput.schema(), false);
  leval_itr.force_is_done();

  // Iterate over the branches of xinput.
  // The branches of xinput are the maximal jims in its down set.
  // If xinput is not a multi-section, xinput itself is its only branch.

  sec_vd lbranch;
  preorder_iterator lbranch_itr(xinput, "jims", DOWN, NOT_STRICT);
  while(!lbranch_itr.is_done())
  {
    scoped_index branch_index = lbranch_itr.index();

    // Attach a handle to the current branch.

    lbranch.attach_to_state(xinput.host(), branch_index);

    // Iterate over the evaluation members of the input;
    // process all the pullbacks contained in each eval member.

    // Reanchor the eval itr to this branch without resetting bit vector.

    leval_itr.put_schema_anchor(lbranch.schema().index());
    leval_itr.reset(false);

    while(!leval_itr.is_done())
    {
      push_eval_mbr(leval_itr, lbranch, xresult);
      leval_itr.next();
    }

    // Don't need to go deeper.

    lbranch_itr.truncate();
  }

  // Do whatever postprocessing the overlap action wants.

  _overlap_action->finalize(xresult);

  // Clean up.

  lbranch.detach_from_state();

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving define_overlap:");
#endif

  return;
}

void
fields::section_pusher::
push_eval_mbr(const eval_iterator& xeval_itr, const sec_vd& xinput,
              sec_vd& xresult)
{
  // Preconditions:


  // Body:

  // Try to get the list of pullbacks for this eval member in this branch.

  pb_map_range_type litr_range =
    _pb_maps[xinput.index().pod()]->equal_range(pb_type(xeval_itr.index()));
  
  if(litr_range.first != litr_range.second)
  {
    // The iterator range is not empty.
    // This eval member contains pullback points in its base space.
    // We will evaluate the input field for each pullback,
    // but first we'll need to gather the input dofs.

    _src_dofs.set_ct(0);

    eval_iterator& leval_itr = const_cast<eval_iterator&>(xeval_itr);
    leval_itr.gather_dofs(xinput, _src_dofs);
    //xeval_itr.gather_dofs(xinput, _src_dofs);

    // Get the evaluator for this eval member.

    const section_evaluator& levaluator = xeval_itr.evaluator();

    // Iterate over the  pullback points, evaluating
    // the input at each point.

    for(pb_map_itr_type itr = litr_range.first; itr != litr_range.second; ++itr)
    {
      // Evaluate the input at the pullback point.

      levaluator.value_at_coord(_src_dofs.base(),
                                _src_dofs.ct(),
                                itr->domain_pt.local_coords(),
                                _src_db,
                                _dst_dofs.base(),
                                _dst_dofs.ct());

      // Let the overlap action do what ever it wants.

      (*_overlap_action)(itr, xresult, _dst_dofs);


#ifdef DIAGNOSTIC_OUTPUT

      print_debug_info(xeval_itr.client_id(), range(), itr, _dst_dofs);
#endif

      // Scatter the dofs into the result.

      xresult.put_fiber(itr->disc_id, _dst_dofs.base(),
			_dst_dofs.ub()*sizeof(sec_vd_dof_type), false);
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
fields::section_pusher::
define_extension(sec_vd& xresult)
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

  _extension_action->initialize(xresult);

  // Iterate over the disc members in the extension.
  // These are all in the pullback list of chart id that are invalid for branch 0.

  pb_map_type* lpb_map = _pb_maps[_first_branch.pod()];

  pb_map_range_type litr_range =
    lpb_map->equal_range(pb_type(invalid_pod_index()));

  for(pb_map_itr_type itr = litr_range.first; itr != litr_range.second; ++itr)
  {
    // There is no value of the input associated with this
    // discretization member, so define the dofs by extension.

    (*_extension_action)(itr, xresult, _dst_dofs);


#ifdef DIAGNOSTIC_OUTPUT

    print_debug_info(invalid_pod_index(), range(), itr, _dst_dofs);
#endif

    // Scatter the dofs into the result.

    xresult.put_fiber(itr->disc_id, _dst_dofs.base(),
		      _dst_dofs.ub()*sizeof(sec_vd_dof_type), false);
  }

  // Do whatever postprocessing the extension action wants.

  _extension_action->finalize(xresult);

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving define_extension:");
#endif

  return;
}

void
fields::section_pusher::
initialize()
{
  // Preconditions:

  require(domain().state_is_read_accessible());

  // Body:

  // Initialize some useful buffers.

  _prop_df = _domain->schema().df();
  _src_db = _domain->schema().db();

  _src_value.reserve(_prop_df);
  _src_value.set_ct(_prop_df);

  _dst_dofs.reserve(_prop_df);
  _dst_dofs.set_ct(_prop_df);

  // Initialize the push actions.

  _default_overlap_action = new copy_push_action(_prop_df);
  _overlap_action = _default_overlap_action;

  _default_extension_action = new constant_push_action(_prop_df, 0.0);
  _extension_action = _default_extension_action;


  // Allocate the pullback map buffer.

  _pb_maps.reserve(_domain->member_index_ub().pod());

  _pb_maps.set_ct(_pb_maps.ub());
  _pb_maps.assign(0);

  _first_branch.invalidate();

  // Postconditions:


  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::section_pusher::
section_pusher(const section_pusher& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fields::section_pusher::
~section_pusher()
{
  // Preconditions:

  // Body:

  _domain_coords.detach_from_state();
  _range_coords.detach_from_state();

  // Postconditions:

  // Exit:
}

bool
fields::section_pusher::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(any::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    // The domain and range fiber type and dimension should the same.
    /// @hack unexecutable because we may not have required access.

    invariance(unexecutable(same_fiber(domain(), range())));

    // Currently only support binary schema, not ternary schema.
    /// @hack unexecutable because we may not have required access.

    invariance(unexecutable(dynamic_cast<binary_section_space_schema_member*>(&(range().schema())) != 0));

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


