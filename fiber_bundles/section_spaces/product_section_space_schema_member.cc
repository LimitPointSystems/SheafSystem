
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
/// Implementation for class product_section_space_schema_member.

#include "product_section_space_schema_member.impl.h"

#include "assert_contract.h"
#include "array_index_space_state.h"
#include "ij_product_structure.h"
#include "namespace_poset.h"
#include "postorder_itr.h"
#include "preorder_itr.h"
#include "product_section_dof_iterator.h"
#include "product_section_space_schema_poset.h"
#include "sec_rep_descriptor.h"
#include "section_space_schema_jims_index_space_handle.h"
#include "section_space_schema_jims_index_space_state.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// PRODUCT_SECTION_SPACE_SCHEMA_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member()
    : section_space_schema_member()
{
  // Preconditions:

  // Body:

  // Nothing to do; base class does it all.

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
  ensure(!is_factorable());

  // Exit:
}

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(const product_section_space_schema_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

fiber_bundle::product_section_space_schema_member&
fiber_bundle::product_section_space_schema_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

fiber_bundle::product_section_space_schema_member&
fiber_bundle::product_section_space_schema_member::
operator=(const product_section_space_schema_member& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  //Body:

  not_implemented();

  //Postconditions:

  ensure(invariant());

  //Exit:

  return *this;
}

fiber_bundle::product_section_space_schema_member::
~product_section_space_schema_member()
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(poset* xhost,
				    array_poset_dof_map* xdof_map,
				    bool xcopy_dof_map,
				    bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_map, xcopy_dof_map, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(same args)));

  // Exit:

  return;
}


fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(poset* xhost,
				    const scoped_index& xdof_tuple_id,
				    bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_tuple_id, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(same args)));

  // Exit:

  return;
}

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(poset* xhost,
				    scoped_index* xexpansion,
				    int xexpansion_ct,
				    const tern& xnew_jem,
				    bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jrm_state(same args)));

  // Body:

  new_jrm_state(xhost, xexpansion, xexpansion_ct, xnew_jem, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jrm_state(same args)));

  // Exit:

  return;
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                   pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                   const scoped_index& xid)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                   const std::string& xname)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());
  require(xhost->contains_member(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());
}


fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                   pod_index_type xbase_space_id,
                                   pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xbase_space_id, xfiber_schema_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit

  return;
}

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                   const scoped_index& xbase_space_id,
                                   const scoped_index& xfiber_schema_id)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost,
		  xbase_space_id.hub_pod(),
		  xfiber_schema_id.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit

  return;
}

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(const product_section_space_schema_poset* xhost,
                                   const poset_path& xbase_path,
                                   const poset_path& xfiber_schema_path)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xbase_path, xfiber_schema_path);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit

  return;
}

fiber_bundle::product_section_space_schema_member::
product_section_space_schema_member(const namespace_poset& xns,
                                   const poset_path& xpath,
                                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(&xns, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::product_section_space_schema_member::
update_row_cache_without_disc_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible()); 
  require(is_factorable());

  // Body:

  base_space_poset& lbase_host = host()->base_space();
  const subposet& leval_sp = evaluation();
  const subposet& ldisc_sp = discretization();
  const subposet& ljims_sp = lbase_host.jims();

  // Get the disc ct from the id space.

  _discretization_ct = _discretization_id_space->ct();  

  // Try to get evaluation_ct from eval id space.

  string leval_id_space_name = intersection_id_space_name(leval_sp, _base_space_id);
  if(lbase_host.member_id_spaces(false).contains(leval_id_space_name))
  {
    _evaluation_ct = lbase_host.member_id_spaces(false).ct(leval_id_space_name);
  }
  else
  {
    _evaluation_ct = 0;

    unordered_set_postorder_itr itr(_base_space, DOWN, NOT_STRICT);
    while(!itr.is_done())
    {
      pod_index_type lindex = itr.index().pod();

      if(leval_sp.contains_member(lindex))
      {
	_evaluation_ct++;
      }

      itr.next();
    }
  }
  
  // Get db from the base space.

  _db = lbase_host.db(_base_space.index());
  
  // Postconditions:

  // Exit

  return;
}

void
fiber_bundle::product_section_space_schema_member::
update_row_cache_with_disc_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(host()->base_space().state_is_read_write_accessible());

  // Body:

  base_space_poset& lbase_host = host()->base_space();
  const subposet& leval_sp = evaluation();
  const subposet& ldisc_sp = discretization();
  const subposet& ljims_sp = lbase_host.jims();

  // Traverse the down set; count the eval and disc members and find
  // the maximum dimension and client id.

  _db = 0;
  _evaluation_ct = 0;
  _discretization_ct = 0;

  // This schema is either new or changed, so we need
  // to (re)build the sequence id space.

  // Refiners extend client id space; so we need to maintain same order.
  // Do this in two steps:

  // First: find the disc members in the down set of the base and
  // store their client ids in a set, which will keep them
  // sorted in order.

  set<scoped_index::pod_type> ltop_seq_ids;
  const index_space_handle& ltop_space = ldisc_sp.id_space();

  unordered_set_postorder_itr itr(_base_space, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    const scoped_index& lindex = itr.index();

    if(ljims_sp.contains_member(lindex))
    {
      int ldb = lbase_host.member_dof_tuple(lindex)->db;

      _db = (ldb > _db) ? ldb : _db;
    }

    if(leval_sp.contains_member(lindex))
    {
      _evaluation_ct++;
    }

    if(ldisc_sp.contains_member(lindex))
    {
      _discretization_ct++;
      ltop_seq_ids.insert(ltop_space.pod(lindex));
    }

    itr.next();
  }

  // Second: iterate over the set and define the new seq id space.
  // The new space will contain a subset of the members in the
  // original client id space in the same relative order as the original.

  assertion(dynamic_cast<scattered_insertion_index_space_handle*>(_discretization_id_space) != 0);

  scattered_insertion_index_space_handle* ldisc_id_space =
    reinterpret_cast<scattered_insertion_index_space_handle*>(_discretization_id_space);

  ldisc_id_space->clear();
  ldisc_id_space->reserve(_discretization_ct);

  set<pod_index_type>::iterator lseq_id_itr;
  for(lseq_id_itr = ltop_seq_ids.begin();
      lseq_id_itr != ltop_seq_ids.end();
      ++lseq_id_itr)
  {
    ldisc_id_space->push_back(ltop_space.hub_pod(*lseq_id_itr));
  }

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::product_section_space_schema_member::
update_row_dof_id_space() const
{
  // Preconditions:

  require(is_factorable());

  // Body:

  const index_space_handle& lfiber_schema_id_space =
    fiber_schema().row_dof_id_space();

  if(_host->member_id_spaces(false).contains(row_dof_subposet_name()))
  {
    // Row dof id space already exists, set the factors.

    _row_dof_id_space =
      &_host->member_id_spaces(false).get_id_space(row_dof_subposet_name());

    reinterpret_cast<section_space_schema_jims_index_space_handle*>
      (_row_dof_id_space)->put_factors(*_discretization_id_space,
				       lfiber_schema_id_space,
				       host()->product_structure());
  }
  else
  {
    // Create the row dof id space.

    arg_list largs =
      section_space_schema_jims_index_space_state::
      make_arg_list(*_discretization_id_space,
		    lfiber_schema_id_space,
		    host()->product_structure());

    pod_index_type lspace_id =
      _host->new_member_id_space(row_dof_subposet_name(),
				 "section_space_schema_jims_index_space_state",
				 largs, false, false);

    _row_dof_id_space =
      &_host->member_id_spaces(false).get_id_space(lspace_id);
  }
  
  // Postconditions:

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION_SPACE_SCHEMA_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SCHEMA_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

/// @todo Remove.
// sheaf::primitive_type
// fiber_bundle::product_section_space_schema_member::
// dof_tuple_type(bool xis_table_dof) const
// {
//   primitive_type result = NOT_A_PRIMITIVE_TYPE;

//   // Preconditions:

//   require(state_is_read_accessible());
//   /// @todo Remove.
// //   require(is_schematized(false));

//   // Body:

//   result = fiber_schema().dof_tuple_type(xis_table_dof);

//   // Postconditions:

//   ensure(xis_table_dof ? result == NOT_A_PRIMITIVE_TYPE : true);

//   // Exit

//   return result;
// }

// bool
// fiber_bundle::product_section_space_schema_member::
// is_dof(bool xin_table_dofs) const
// {
//   bool result;

//   // Preconditions:

//   require(state_is_read_accessible());
//   require(host()->is_schematized(false));


//   // Body:

//   if(xin_table_dofs)
//   {
//     // Table dofs:

//     // Table dofs are {base.bottom()} x {fiber schema table dofs}.

//     result = (_base_space_id == BOTTOM_INDEX) && fiber_schema().is_table_dof();
//   }
//   else
//   {
//     // Row dofs:

//     result = host()->discretization().contains_member(_base_space_id) && fiber_schema().is_row_dof();
//   }

//   // Postconditions:

//   // Exit

//   return result;
// }

// size_t
// fiber_bundle::product_section_space_schema_member::
// size() const
// {
//   size_t result;

//   // Preconditions:

//   require(state_is_read_accessible());
//   require(fiber_schema().is_jim());

//   // Body:

//   result = fiber_schema().size();

//   // Postconditions:

//   // Exit

//   return result;
// }

// size_t
// fiber_bundle::product_section_space_schema_member::
// alignment() const
// {
//   size_t result;

//   // Preconditions:

//   require(state_is_read_accessible());
//   require(fiber_schema().is_jim());

//   // Body:

//   result = fiber_schema().alignment();

//   // Postconditions:

//   // Exit

//   return result;
// }

// sheaf::primitive_type
// fiber_bundle::product_section_space_schema_member::
// type() const
// {
//   sheaf::primitive_type result;

//   // Preconditions:

//   require(state_is_read_accessible());
//   require(fiber_schema().is_jim());

//   // Body:

//   result = fiber_schema().type();

//   // Postconditions:

//   ensure(is_primitive_index(result));

//   // Exit

//   return result;
// }

sheaf::poset_dof_iterator*
fiber_bundle::product_section_space_schema_member::
dof_iterator(bool xis_table_dofs, int xversion) const
{
  poset_dof_iterator* result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));
  require(has_version(xversion));


  // Body:

  result = new product_section_dof_iterator(*this, xis_table_dofs, xversion);

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::dof_descriptor_array*
fiber_bundle::product_section_space_schema_member::
dof_descriptors(bool xis_table_dof) const
{
  dof_descriptor_array* result = 0;

  // Preconditions:

  require(state_is_read_accessible());

  // Dof descriptors not defined for row dofs.

  require(xis_table_dof);

  // Body:

  result = schema_poset_member::dof_descriptors(xis_table_dof);

  // Postconditions:

  ensure(unexecutable(result != 0 implies it points to a buffer of length table_dof_ct()+1));

  // Exit

  return result;
}

void
fiber_bundle::product_section_space_schema_member::
update_row_cache(bool xupdate_id_space) const
{
  // Preconditions:

  // Body:

  if(is_factorable())
  {
    // This member is factorable.  Create the product structure.

    base_space_poset& lbase_host = host()->base_space();

    // Declare an enum for determining what needs updated.

    enum update_type
    {
      only_row_cache,        // Update only the row cache counts.
      only_row_dof_id_space, // Update the row cache counts and row dof id space.
      all_id_spaces          // Update the row cache counts, discretization id space, and row dof id space.
    };
  
    update_type lupdate = xupdate_id_space ? all_id_spaces : only_row_cache;

    /// @error getting write access here violates policy.
    /// @todo add auto access

    lbase_host.get_read_write_access(true);

    // Release old discretization handle if one was set.

    if(_discretization_id_space != 0)
    {
      _discretization_id_space->release_id_space(*_discretization_id_space);
    }

    /// @todo replace this look up by something more efficient.
    /// This is just a temporary, exploratory implementation.

    string ldisc_id_space_name =
      intersection_id_space_name(discretization(), _base_space_id);

    // Assign the discretization id space.

    if(lbase_host.member_id_spaces(false).contains(ldisc_id_space_name))
    {
      _discretization_id_space =
	&lbase_host.member_id_spaces(false).get_id_space(ldisc_id_space_name);

      if((lupdate == all_id_spaces) &&
	 (*_discretization_id_space == discretization().id_space()))
      {
	// The user requested that all the id spaces be update but since
	// the this member's discretization id space is the same as the
	// discretization id space of the host, only update the row id space.

	lupdate = only_row_dof_id_space;
      }
    }
    else
    {
      // Create the discretization id space.

      arg_list largs = array_index_space_state::make_arg_list(0);

      pod_index_type lspace_id =
	lbase_host.new_member_id_space(ldisc_id_space_name,
				       "array_index_space_state",
				       largs, false, false);

      _discretization_id_space =
	&lbase_host.member_id_spaces(false).get_id_space(lspace_id);

      if(lupdate == only_row_cache)
      {
	// The discretization id space was created, update the discretization
	// id space and the row dof id space.

	lupdate = all_id_spaces;
      }
    }

    // Make sure a row dof id space is created.

    if((lupdate == only_row_cache) &&
       !_host->member_id_spaces(false).contains(row_dof_subposet_name()))
    {
      lupdate = only_row_dof_id_space;
    }

    // Update the row cache and any id spaces needed.

    switch(lupdate)
    {
      case only_row_cache:
	update_row_cache_without_disc_id_space();
	break;

      case only_row_dof_id_space:
	update_row_cache_without_disc_id_space();
	update_row_dof_id_space();
	break;

      case all_id_spaces:
	update_row_cache_with_disc_id_space();
	update_row_dof_id_space();
	break;
    }

    lbase_host.release_access();

    // Update row values.

    _row_dof_ct          = _row_dof_id_space->ct();

    _row_dof_tuple_ub    = _discretization_ct*fiber_schema().row_dof_tuple_ub();

    _row_dof_descriptors = 0;

    _row_cache_index = index();
    _row_cache_version = version();
  }
  else
  {
    // Just another schema member.

    schema_poset_member::update_row_cache();
  }

  // Postconditions:

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NEW DOF ACCESS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
fiber_bundle::product_section_space_schema_member::
size(pod_index_type xdof_id, bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  size_type result;

  if(is_factorable())
  {
    pod_index_type lfiber_dof_id = xdof_id;

    if(!xis_table_dofs)
    {
      pod_index_type ldisc_id;
      row_dof_id_space().product_structure<ij_product_structure>().
	tuple(xdof_id, ldisc_id, lfiber_dof_id);
    }
  
    result = fiber_schema().size(lfiber_dof_id, xis_table_dofs);
  }
  else
  {
    schema_poset_member::size(xdof_id, xis_table_dofs);
  }

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::product_section_space_schema_member::
size(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  size_type result = fiber_schema().size(xfiber_dof_id, xis_table_dof);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::product_section_space_schema_member::
size(const scoped_index& xdisc_id,
     const scoped_index& xfiber_dof_id,
     bool xis_table_dof,
     bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  size_type result = fiber_schema().size(xfiber_dof_id, xis_table_dof, xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::product_section_space_schema_member::
alignment(pod_index_type xdof_id, bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  size_type result;

  if(is_factorable())
  {
    pod_index_type lfiber_dof_id = xdof_id;

    if(!xis_table_dofs)
    {
      pod_index_type ldisc_id;
      row_dof_id_space().product_structure<ij_product_structure>().
	tuple(xdof_id, ldisc_id, lfiber_dof_id);
    }
  
    result = fiber_schema().alignment(lfiber_dof_id, xis_table_dofs);
  }
  else
  {
    result = alignment(xdof_id, xis_table_dofs);
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::product_section_space_schema_member::
alignment(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  size_type result = fiber_schema().alignment(xfiber_dof_id, xis_table_dof);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::product_section_space_schema_member::
alignment(const scoped_index& xdisc_id,
	  const scoped_index& xfiber_dof_id,
	  bool xis_table_dof,
	  bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  size_type result =
    fiber_schema().alignment(xfiber_dof_id, xis_table_dof, xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::primitive_type
fiber_bundle::product_section_space_schema_member::
type(pod_index_type xdof_id, bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xis_table_dofs ? fiber_schema_id_space(xis_table_dofs).contains(xdof_id) : true);
  
  // Body:

  primitive_type result;

  if(is_factorable())
  {
    pod_index_type lfiber_dof_id = xdof_id;

    if(!xis_table_dofs)
    {
      pod_index_type ldisc_id;
      row_dof_id_space().product_structure<ij_product_structure>().
	tuple(xdof_id, ldisc_id, lfiber_dof_id);
    }
  
    result = fiber_schema().type(lfiber_dof_id, xis_table_dofs);
  }
  else
  {
    result = schema_poset_member::type(xdof_id, xis_table_dofs);
  }

  // Postconditions:


  // Exit:

  return result;
}

sheaf::primitive_type
fiber_bundle::product_section_space_schema_member::
type(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  primitive_type result = fiber_schema().type(xfiber_dof_id, xis_table_dof);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::primitive_type
fiber_bundle::product_section_space_schema_member::
type(const scoped_index& xdisc_id,
     const scoped_index& xfiber_dof_id,
     bool xis_table_dof,
     bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  primitive_type result =
    fiber_schema().type(xfiber_dof_id, xis_table_dof, xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::product_section_space_schema_member::
offset(pod_index_type xdof_id, bool xis_table_dof) const
{
  size_type result;
  
  // Preconditions:

  require(state_is_read_accessible());
  require(xis_table_dof ? fiber_schema_id_space(xis_table_dof).contains(xdof_id) : true);

  // Body:

  if(!is_factorable())
  {
    result = schema_poset_member::offset(xdof_id, xis_table_dof);
  }
  else if(xis_table_dof)
  {
    result = fiber_schema().offset(xdof_id, true);
  }
  else
  {
    pod_index_type lfiber_dof_id, ldisc_id;
    row_dof_id_space().product_structure<ij_product_structure>().
      tuple(xdof_id, ldisc_id, lfiber_dof_id);

    result = offset(ldisc_id, lfiber_dof_id, false);
  }
  

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::product_section_space_schema_member::
offset(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  size_type result;

  if(xis_table_dof)
  {
    result = fiber_schema().offset(xfiber_dof_id, true);
  }
  else
  {
    result = fiber_size()*xdisc_id + fiber_schema().offset(xfiber_dof_id, false);
  }

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::product_section_space_schema_member::
offset(const scoped_index& xdisc_id,
       const scoped_index& xfiber_dof_id,
       bool xis_table_dof,
       bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_factorable());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  pod_index_type ldisc_id = _discretization_id_space->pod(xdisc_id);
  pod_index_type lfiber_dof_id =
    fiber_schema_id_space(xis_table_dof).pod(xfiber_dof_id);
  
  size_type result = offset(ldisc_id, lfiber_dof_id, xis_table_dof);

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_iterator*
fiber_bundle::product_section_space_schema_member::
get_decomposition(pod_index_type xindex) const
{
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->base_space().includes_subposet(xindex));

  // Body:

  zn_to_bool* ldecomp = new zn_to_bool();

  subposet ldecomp_sp(&host()->base_space(), xindex);

  index_iterator litr = ldecomp_sp.indexed_member_iterator();
  while(!litr.is_done())
  {
    pod_index_type lschema_mbr_id;
    host()->ordinal(litr.index().pod(), fiber_schema_id(), lschema_mbr_id);

    ldecomp->force(lschema_mbr_id, true);

    litr.next();
  }

  ldecomp_sp.detach_from_state();

  index_iterator* result = new index_iterator(ldecomp,
					      host()->member_hub_id_space(false),
					      true);

  // Postconditions:

  // Exit:

  return result;
}

/// @todo Remove.
/// @todo Review.

// sheaf::pod_index_type
// fiber_bundle::product_section_space_schema_member::
// get_int_id(pod_index_type xext_id, const std::string& xid_space_name) const
// {
//   // Preconditions:

//   require(state_is_read_accessible());
//   require(precondition_of(host()->base_space().get_ext_id(index(), xid_space_name)));

//   // Body:

//   /// @hack product subposet hack, ver 2.
//   /// Section space schema member external ids are really base space external ids.

//   pod_index_type lbase_id =
//     host()->base_space().get_int_id(xext_id, xid_space_name, false);

//   pod_index_type result;
//   host()->ordinal(lbase_id, fiber_schema_id(), result);

//   // Postconditions:

//   ensure(host()->contains_member(result));

//   // Exit:

//   return result;
// }

void
fiber_bundle::product_section_space_schema_member::
get_ext_ids(const std::string& xid_space_name,
            pod_index_type& xschema_poset_ext_id,
            pod_index_type& xschema_member_ext_id,
            pod_index_type& xbase_space_ext_id,
            pod_index_type& xfiber_schema_ext_id,
            pod_index_type& xlocal_schema_ext_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->member_id_spaces(false).contains(xid_space_name));
  require(host()->base_space().member_id_spaces(false).contains(xid_space_name));
  require(host()->base_space().member_id_spaces(false).contains_hub(xid_space_name, base_space_id()));
  require(host()->fiber_schema().member_id_spaces(false).contains(xid_space_name));
  require(host()->fiber_schema().member_id_spaces(false).contains_hub(xid_space_name, fiber_schema_id()));

  // Body:

  // Get the external id for the schema poset (this->host()).

  xschema_poset_ext_id =
    name_space()->get_ext_id(host()->index(), xid_space_name, false);

  // Schema member external id is undefined.

  xschema_member_ext_id = invalid_pod_index();

  // Get the external id for the base space component.

  xbase_space_ext_id =
    host()->base_space().get_ext_id(base_space_id(), xid_space_name, false);

  // Get the external id for the fiber schema component.

  xfiber_schema_ext_id =
    host()->fiber_schema().get_ext_id(fiber_schema_id(), xid_space_name, false);

  // Local schema id is undefined.

  xlocal_schema_ext_id = invalid_pod_index();

  // Postconditions:


  // Exit:

  return;
}

sheaf::schema_poset_member&
fiber_bundle::product_section_space_schema_member::
ext_data_type_schema()
{
  return fiber_schema();
}

size_t
fiber_bundle::product_section_space_schema_member::
ext_data_type_ct(bool xis_table_schema) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // For product schema members,
  // the external data type is the entire schema.

  size_t result = xis_table_schema ? 1 : discretization_ct();

  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEGREE OF FREEDOM (DOF) TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::primitives_poset_dof_map&
fiber_bundle::product_section_space_schema_member::
dof_map(bool xrequire_write_access)
{

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  primitives_poset_dof_map& result =
    fiber_schema().dof_map(xrequire_write_access);

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::primitives_poset_dof_map&
fiber_bundle::product_section_space_schema_member::
dof_map(bool xrequire_write_access) const
{

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  const primitives_poset_dof_map& result =
    fiber_schema().dof_map(xrequire_write_access);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HOST POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::product_section_space_schema_member::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const product_section_space_schema_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::product_section_space_schema_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const product_section_space_schema_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::product_section_space_schema_member*
fiber_bundle::product_section_space_schema_member::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  product_section_space_schema_member *result =
    new product_section_space_schema_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;
}

bool
fiber_bundle::product_section_space_schema_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && schema_poset_member::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    /// @issue what are the invariants for this class
    /// @todo implement product_section_space_schema_member::invariant() const

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
