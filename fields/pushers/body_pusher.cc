
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
/// Implementation for class body_pusher.

#include "ComLimitPoint/fields/body_pusher.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_member.h"
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_member.h"
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_poset.h"
#include "ComLimitPoint/fiber_bundle/discretization_context.h"
#include "ComLimitPoint/sheaf/index_iterator.h"
#include "ComLimitPoint/sheaf/poset_joiner.h"
#include "ComLimitPoint/sheaf/postorder_itr.h"
#include "ComLimitPoint/fields/property_disc_iterator.h"
#include "ComLimitPoint/geometry/sec_ed_invertible.h"
#include "ComLimitPoint/fiber_bundle/sec_rep_descriptor.h"
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#include "ComLimitPoint/sheaf/tern.h"

using namespace std;
using namespace unordered;
using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT 1


// =============================================================================
// BODY_PUSHER FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::body_pusher::
body_pusher(const geometry::sec_ed_invertible& xdomain_coord, const sec_ed& xrange_coord,
            bool xauto_access)
{
  // Preconditions:

  require(xauto_access || xdomain_coord.state_is_read_accessible());
  require(xauto_access || xrange_coord.state_is_read_accessible());
  require(same_fiber(xdomain_coord, xrange_coord, xauto_access));

  // Body:

  define_old_variable(int old_domain_coord_access_request_depth = xdomain_coord.access_request_depth());
  define_old_variable(int old_range_coord_access_request_depth = xrange_coord.access_request_depth());

  if(xauto_access)
  {
    xdomain_coord.get_read_access();
    xrange_coord.get_read_access();
  }

  _domain = &xdomain_coord.schema().host()->base_space();
  _domain_coord = xdomain_coord.clone();
  _domain_coord->attach_to_state(&xdomain_coord);
  _range = &xrange_coord.schema().host()->base_space();
  _range_coord.attach_to_state(&xrange_coord);

  _push_name = true;

  define_old_variable(int old_range_access_request_depth = range().access_request_depth());

  // Create a temporary section space schema with eval == elements and
  // disc == vertices.

  string lschema_name =
    poset_path::make_name(poset_path::reserved_prefix() + _range->name(),
                          xrange_coord.index().pod(),
                          "body_pusher_schema" );

  string lschema_poset_name =
    sec_rep_space_member::standard_schema_poset_name(lschema_name);
  
  poset_path lschema_path(lschema_poset_name, lschema_name);

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(*_range->name_space());

  if(!lns.contains_poset_member(lschema_path, true))
  {
    // Schema doesn't exist; create it.
    
    poset_path lrep_path;
    lrep_path.put_poset_name("sec_rep_descriptors");
    
    if(xrange_coord.schema().rep().name() == "vertex_vertex_constant")
    {
      /// @hack iterator looks for evaluation subposet by name and
      /// we don't currently support multiple names for a subposet.
      /// So make sure name is "__vertices".
      
      /// @todo we can remove this when subposets support multiple names.
      
      lrep_path.put_member_name("vertex_vertex_constant");
    }
    else
    {
      lrep_path.put_member_name("vertex_element_dlinear");
    }

      binary_section_space_schema_poset& lhost =
	binary_section_space_schema_poset::new_table(lns,
						     lschema_path.poset_name(),
						     binary_section_space_schema_poset::standard_schema_path(),
						     xrange_coord.schema().base_space().path(true),
						     xdomain_coord.schema().fiber_space().path(true),
						     lrep_path,
						     true);

      _body_schema = new binary_section_space_schema_member(&lhost, xrange_coord.schema().base_space().path(true),
							    lhost.fiber_space().schema(true).path(true));
      _body_schema->put_name(lschema_path.member_name(), true, true);
  }
  else
  {
    _body_schema = new binary_section_space_schema_member(lns, lschema_path, true);
  }
  
  // Pull the discretization points from the range back to the domain.
  
  pull_back_range_disc();

  // Postconditions:

  ensure(invariant());
  ensure(domain().is_same_state(xdomain_coord.schema().base_space().host()));
  ensure(range().is_same_state(xrange_coord.schema().base_space().host()));
  ensure(push_name());
  ensure(name_prefix().empty());
  ensure(name_suffix().empty());

  ensure(range().access_request_depth() == old_range_access_request_depth );

  if(xauto_access)
  {
    xdomain_coord.release_access();
    xrange_coord.release_access();
  }

  ensure(xdomain_coord.access_request_depth() == old_domain_coord_access_request_depth);
  ensure(xrange_coord.access_request_depth() == old_range_coord_access_request_depth);

  // Exit:
}

const fiber_bundle::base_space_poset&
fields::body_pusher::
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
fields::body_pusher::
domain_coord() const
{
  // Preconditions:

  // Body:

  const geometry::sec_ed_invertible& result = *_domain_coord;

  // Postconditions:

  // Exit

  return result;

}

const fiber_bundle::base_space_poset&
fields::body_pusher::
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
fields::body_pusher::
range_coord() const
{
  // Preconditions:

  // Body:

  const sec_ed& result = _range_coord;

  // Postconditions:

  // Exit

  return result;

}

fiber_bundle::base_space_member*
fields::body_pusher::
push(const base_space_member& xinput, bool xcompute_upper_bound, bool xauto_access)
{
  base_space_member* result = 0;

  // Preconditions:

  require(xauto_access || domain_coord().state_is_read_accessible());
  require(domain().contains_member(&xinput, xauto_access));
  require(xauto_access || range_coord().state_is_read_accessible());
  require(xauto_access || range().state_is_read_write_accessible());


  // Body:

  result = xinput.clone();
  push_pa(xinput, *result, xcompute_upper_bound, xauto_access);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(push_pa));

  // Exit

  return result;
}

void
fields::body_pusher::
push_pa(const base_space_member& xinput,
        base_space_member& result,
        bool xcompute_upper_bound,
        bool xauto_access)
{
#ifdef DIAGNOSTIC_OUTPUT
  cout << endl
  << "body_pusher::push_pa"
  << endl
  << endl;
#endif

  // Preconditions:

  require(xauto_access || domain_coord().state_is_read_accessible());
  require(domain().contains_member(&xinput, xauto_access));
  require(xauto_access || range().state_is_read_write_accessible());
  require(xauto_access || range_coord().state_is_read_accessible());

  // Body:

  define_old_variable(int old_domain_coord_access_request_depth = domain_coord().access_request_depth());
  define_old_variable(int old_range_coord_access_request_depth = range_coord().access_request_depth());
  define_old_variable(int old_range_access_request_depth = range().access_request_depth());


  if(xauto_access)
  {
    _domain_coord->get_read_access();
    _range->get_read_write_access(true);
    _range_coord.get_read_access();
  }

  // Allocate a set to contain the range vertices which have
  // a pullback in xinput.

  unordered_set<scoped_index> lvertices;

  // Iterate over the down set of the input;
  // process all the pullbacks contained in each element.

  unordered_set_postorder_itr litr(xinput, _domain->elements(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    // Insert all the range vertex pullbacks contained in this element
    // into the result vertices subposet.

    pb_map_range_type litr_range = _pb_map.equal_range(pb_type(litr.index()));
    for(pb_map_itr_type lpb_itr = litr_range.first;
        lpb_itr != litr_range.second;
        ++lpb_itr)
    {
      lvertices.insert(lpb_itr->disc_id);
    }

    // Move to the next member of the down set of xinput.

    litr.next();
  }

  // The range vertex list now contains all range vertices with pullbacks
  // contained in the input, if there are any.

  // Allocate a set to contain upper bound of zones in the result.

  unordered_set<scoped_index> lelements;

  // Create the element iterator using the top of the range.  The
  // iterator must be initialized so that the anchor can be set within
  // the loop.

  unordered_set_postorder_itr lelem_itr(_range->top(),
				   &_range->elements(),
				   sheaf::UP);

  for(unordered_set<scoped_index>::const_iterator lvertex_itr = lvertices.begin();
      lvertex_itr != lvertices.end();
      ++lvertex_itr)
  {
    // Reinitialize the iterator to the next vertex.

    lelem_itr.put_anchor(*lvertex_itr);
    lelem_itr.reset();

    while(!lelem_itr.is_done())
    {
      // Add the zone to the result.

      lelements.insert(lelem_itr.index());

      // Move to the next member in the upset of the vertex.

      lelem_itr.next();
    }
  }

  // Allocate a subposet to contain the elements in the result.

  block<scoped_index> lelement_ids;
  bool lhas_zones = false;

  // Reset the element iterator to descend down and only return at the
  // verticies.

  lelem_itr.put_filter(_range->vertices());
  lelem_itr.put_descending(sheaf::DOWN);

  // Loop over the elements of the upper bound and insert them into
  // the result subposet.

  for(unordered_set<scoped_index>::const_iterator lub_elem_itr = lelements.begin();
      lub_elem_itr != lelements.end();
      ++lub_elem_itr)
  {
    bool lis_lb = true;

    if(!xcompute_upper_bound)
    {
      // Determine if the element is in the lower bound.

      lelem_itr.put_anchor(*lub_elem_itr);
      lelem_itr.reset();

      while(!lelem_itr.is_done())
      {
	if(lvertices.find(lelem_itr.index()) == lvertices.end())
	{
	  // Vertex is not in the set of verticies, element is not
	  // part of the lower bound.

	  lis_lb = false;
	  break;
	}

	// Move to the next vertex in the element.

	lelem_itr.next();
      }  
    }
    
    if(xcompute_upper_bound || lis_lb)
    {
      // Insert the element into the result subposet.

      lelement_ids.push_back(*lub_elem_itr);
      lhas_zones = true;
    }
  } 

  if(lhas_zones)
  {
    /// @issue should join produce new jem or not?
    /// If not, must relax name postcondition to has_name.

    poset_joiner ljoiner(_range);
    ljoiner.join(lelement_ids.base(), lelement_ids.ct(), tern::TRUE, result);

    if(push_name() && !xinput.name().empty())
    {
      result.put_name(name_prefix() + xinput.name() + name_suffix(), false, false);
    }
  }

  // Postconditions:

  ensure(result.is_attached() ? range().is_same_state(result.host()) : true);
  ensure((result.is_attached() && !xinput.name().empty() && push_name()) ?
         result.name() == name_prefix() + xinput.name() + name_suffix() :
         true);

  if(xauto_access)
  {
    _range_coord.release_access();
    _range->release_access();
    _domain_coord->release_access();
  }

  ensure(domain_coord().access_request_depth() == old_domain_coord_access_request_depth);
  ensure(range_coord().access_request_depth() == old_range_coord_access_request_depth);
  ensure(range().access_request_depth() == old_range_access_request_depth );

  // Exit

  return;
}

sheaf::subposet*
fields::body_pusher::
push(const subposet& xinput, bool xcompute_upper_bound, bool xauto_access)
{
  subposet* result = 0;

  // Preconditions:

  require(precondition_of(push_pa(xinput, *result, xcompute_upper_bound, xauto_access)));

  if(xauto_access)
  {
    domain_coord().get_read_access();
    range_coord().get_read_access();

    _range->get_read_write_access(true);
  }

  require(!xinput.name().empty());

  // Body:

  result = xinput.clone();

  // Get the destination subposet.

  string lresult_name(name_prefix() + xinput.name() + name_suffix());
  if(range().includes_subposet(lresult_name))
  {
    // Already exists, just attach to it.

    result->attach_to_state(_range, lresult_name);
  }
  else
  {
    // Doesn't already exist, create it.

    result->new_state(_range, false, false);
    result->put_name(lresult_name, false, false);
  }

  push_pa(xinput, *result, xcompute_upper_bound, xauto_access);

  // Postconditions:

  if(xauto_access)
  {
    domain_coord().release_access();
    range_coord().release_access();
    range().release_access();
  }

  ensure(result != 0);
  ensure(postcondition_of(push_pa(xinput, *result, xcompute_upper_bound, xauto_access)));

  // Exit

  return result;
}

void
fields::body_pusher::
push_pa(const subposet& xinput,
        subposet& result,
        bool xcompute_upper_bound,
        bool xauto_access)
{
  // Preconditions:

  require(xauto_access || domain_coord().state_is_read_accessible());
  require(domain().includes_subposet(&xinput, xauto_access));
  require(xauto_access || range_coord().state_is_read_accessible());
  require(xauto_access || range().state_is_read_write_accessible());
  require(range().includes_subposet(&result, xauto_access));

  if(xauto_access)
  {
    domain_coord().get_read_access();
    range_coord().get_read_access();

    _range->get_read_write_access(true);
  }

  // Body:

  base_space_member lsrc_body(_domain->top()); // Any member of domain will do.
  base_space_member ldst_body;

  index_iterator litr = xinput.indexed_member_iterator();
  while(!litr.is_done())
  {
    lsrc_body.attach_to_state(litr.index());

    push_pa(lsrc_body, ldst_body, xcompute_upper_bound, false);
    if(ldst_body.is_attached())
    {
      result.insert_member(ldst_body.index());
      ldst_body.detach_from_state();
    }
    litr.next();
  }

  // Clean up.

  lsrc_body.detach_from_state();

  if(xauto_access)
  {
    domain_coord().release_access();
    range_coord().release_access();
    range().release_access();
  }

  // Postconditions:

  // Exit

  return;
}

const bool&
fields::body_pusher::
push_name() const
{
  return _push_name;
}

std::string&
fields::body_pusher::
name_prefix()
{
  return _name_prefix;
}

std::string&
fields::body_pusher::
name_suffix()
{
  return _name_suffix;
}

bool
fields::body_pusher::
same_fiber(const sec_ed& xcoord1, const sec_ed& xcoord2, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || xcoord1.state_is_read_accessible());
  require(xauto_access || xcoord2.state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xcoord1.get_read_access();
    xcoord2.get_read_access();
  }


  result =
    xcoord1.schema().fiber_schema().is_same_state(&xcoord2.schema().fiber_schema())
    && (xcoord1.schema().df() == xcoord2.schema().df());

  // Postconditions:

  ensure(result ==
         (xcoord1.schema().fiber_schema().is_same_state(&xcoord2.schema().fiber_schema())
          && (xcoord1.schema().df() == xcoord2.schema().df())));

  if(xauto_access)
  {
    xcoord1.release_access();
    xcoord2.release_access();
  }

  // Exit:

  return result;
}

void
fields::body_pusher::
pull_back_range_disc()
{
  // Preconditions:

  require(_range_coord.state_is_read_accessible());

  // Body:

  int ldf = _range_coord.schema().df();
  pb_type lpb;
  block<chart_point_3d> ldomain_pts(32); // Arbitrary size.

  _body_schema->get_read_access();

  if(!_domain_coord->is_invertible())
  {
    // Initialize inversion using defaults.

    _domain_coord->initialize_point_locator(false);
  }

  // Iterate over the property disc.

  property_disc_iterator* litr =
    property_disc_iterator::new_property_disc_iterator(_range_coord.schema(),
						       *_body_schema);
  while(!litr->is_done())
  {
    // Get the conext for all the property disc members associated
    // with the current iteration.

    litr->get_prop_disc_values(_range_coord);

    // Iterate over all the property disc members.

    const block<discretization_context>& lprop_mbrs =
      litr->property_discretization_members();
    size_type lct = lprop_mbrs.ct();
    for(size_type i=0; i<lct; ++i)
    {
      // Get the context for this disc member.

      discretization_context& lcontext = lprop_mbrs[i];

      // Get all the domain chart points that correspond to the
      // global coordinates of this range disc pt.

      ldomain_pts.set_ct(0);
      _domain_coord->all_points_at_value_ua(lcontext.values, ldf, ldomain_pts);

      // Store the domain chart points in the pullback map.

      lpb.disc_id = lcontext.disc_id;
      for(size_type i=0; i<ldomain_pts.ct(); ++i)
      {
        lpb.domain_pt = ldomain_pts[i];
        _pb_map.insert(lpb);
      }
    }

    litr->next();
  }

  delete litr;
  _body_schema->release_access();

  // Postconditions:


  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

fields::body_pusher::
body_pusher()
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return;
}

// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::body_pusher::
body_pusher(const body_pusher& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fields::body_pusher::
~body_pusher()
{
  // Preconditions:

  //  require(range().name_space()->in_jim_edit_mode());

  // Body:

  _range_coord.detach_from_state();
  _body_schema->detach_from_state();

  delete _body_schema;

  // Postconditions:

  // Exit:
}


bool
fields::body_pusher::
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

