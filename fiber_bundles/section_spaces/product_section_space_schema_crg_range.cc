
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
/// Implementation for class product_section_space_schema_crg_range

#include "SheafSystem/product_section_space_schema_crg_range.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/factory.h"
#include "SheafSystem/cover_set_iterator.h"
#include "SheafSystem/ij_product_structure.h"
#include "SheafSystem/product_section_space_schema_poset.h"
#include "SheafSystem/section_space_schema_table_dof_crg_range.h"

// ===========================================================
// PRODUCT_SECTION_SPACE_SCHEMA_CRG_RANGE FACET
// ==========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::product_section_space_schema_crg_range::
product_section_space_schema_crg_range()
  : _base_id_space(0),
    _fiber_id_space(0),
    _table_dof_range(0)
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

fiber_bundle::product_section_space_schema_crg_range::
~product_section_space_schema_crg_range()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

const sheaf::ij_product_structure&
fiber_bundle::product_section_space_schema_crg_range::
product_structure() const
{
  // Preconditions:

  require(product_structure_initialized());

  // Body:

  const ij_product_structure& result =
    _local_id_space.product_structure<ij_product_structure>();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::product_section_space_schema_crg_range::
gathered_id_spaces_initialized() const
{
  // Preconditions:

  // Body:

  bool result = (_base_id_space != 0) && (_fiber_id_space != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::product_section_space_schema_crg_range::
product_structure_initialized() const
{
  // Preconditions:

  // Body:

  bool result = _local_id_space.has_product_structure();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::product_section_space_schema_crg_range::
table_dof_range_initialized() const
{
  // Preconditions:

  // Body:

  bool result = (_table_dof_range != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::product_section_space_schema_crg_range::
update_gathered_id_spaces()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  base_space().update_gathered_member_id_space(false);
  fiber_schema().update_gathered_member_id_space(false);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::product_section_space_schema_crg_range::
update_product_structure()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  _local_id_space.product_structure<ij_product_structure>().
    put_ubs(_base_id_space->ct(), _fiber_id_space->ct());

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::product_section_space_schema_crg_range::
initialize_gathered_id_spaces()
{
  // Preconditions:

  require(!gathered_id_spaces_initialized());
  require(base_space_initialized());
  require(fiber_schema_initialized());

  // Body:

  _base_id_space = gathered_id_space(base_space());
  _fiber_id_space = gathered_id_space(fiber_schema());

  // Postconditions:

  ensure(gathered_id_spaces_initialized());

  // Exit:

  return;
}

void
fiber_bundle::product_section_space_schema_crg_range::
initialize_product_structure()
{
  // Preconditions:

  require(!product_structure_initialized());
  require(local_id_space_initialized());
  require(base_space_initialized());
  require(fiber_schema_initialized());
  require(gathered_id_spaces_initialized());

  // Body:

  ij_product_structure lproduct(_base_id_space->ct(),
				_fiber_id_space->ct());
  _local_id_space.new_product_structure(lproduct);

  // Postconditions:

  ensure(product_structure_initialized());

  // Exit:

  return;
}

void
fiber_bundle::product_section_space_schema_crg_range::
initialize_table_dof_range(section_space_schema_table_dof_crg_range& xtable_dof_range)
{
  // Preconditions:

  require(!table_dof_range_initialized());

  // Body:

  _table_dof_range = &xtable_dof_range;

  // Postconditions:

  ensure(table_dof_range_initialized());

  // Exit:

  return;
}

const sheaf::index_space_handle*
fiber_bundle::product_section_space_schema_crg_range::
gathered_id_space(poset_state_handle& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_accessible());

  // Body:

  const index_space_handle* result;

  if(xhost.has_gathered_member_id_space(false))
  {
    // A gathered member id space has already been created.

    assertion(xhost.gathered_member_id_space_excludes_bottom(true));

    result = &xhost.gathered_member_id_space(false);
  }
  else
  {
    // Create a gathered member id space.

    // Need read/write access

    xhost.get_read_write_access(true);
    result = &xhost.new_gathered_member_id_space(true, false);
    xhost.release_access();
  }

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION_SPACE_SCHEMA_CRG_RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::product_section_space_schema_crg_range::
contains_member(pod_index_type xbase_space_id,
		pod_index_type xfiber_schema_id) const
{
  // Preconditions:

  // Body:

  bool result =
    _base_id_space->contains_hub(xbase_space_id) &&
    _fiber_id_space->contains_hub(xfiber_schema_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::product_section_space_schema_crg_range::
tuple(pod_index_type xindex,
      pod_index_type& xbase_space_id,
      pod_index_type& xfiber_schema_id) const
{
  // Preconditions:

  require(local_id_space().contains_hub(xindex));

  // Body:

  pod_index_type lpod = _local_id_space.pod(xindex);

  product_structure().tuple(lpod, xbase_space_id, xfiber_schema_id);

  xbase_space_id = _base_id_space->hub_pod(xbase_space_id);
  xfiber_schema_id = _fiber_id_space->hub_pod(xfiber_schema_id);

  // Postconditions:

  ensure(contains_member(xbase_space_id, xfiber_schema_id));

  // Exit:

  return;
}

void
fiber_bundle::product_section_space_schema_crg_range::
ordinal(pod_index_type xbase_space_id,
	pod_index_type xfiber_schema_id,
	pod_index_type& xindex) const
{
  // Preconditions:

  require(contains_member(xbase_space_id, xfiber_schema_id));

  // Body:

  product_structure().ordinal(_base_id_space->pod(xbase_space_id),
			      _fiber_id_space->pod(xfiber_schema_id),
			      xindex);
  xindex = _local_id_space.hub_pod(xindex);

  // Postconditions:

  ensure(local_id_space().contains_hub(xindex));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// IMPLICIT_CRG_RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::product_section_space_schema_crg_range::
get_size(const product_section_space_schema_poset& xhost, size_type& result)
{
  // Preconditions:

  require(xhost.state_is_read_accessible());

  // Body:

  result =
    (xhost.base_space().member_hub_id_space(false).ct()-1) *
    (xhost.fiber_schema().member_hub_id_space(false).ct()-1);

  // Postconditions:

  // Exit:

  return;
}

sheaf::cover_set_iterator
fiber_bundle::product_section_space_schema_crg_range::
atoms() const
{
  // Preconditions:

  // Body:

  list_cover_set* lcover = new list_cover_set(0);
  lcover->put_is_implicit(true);

  pod_index_type lid;
  cover_set_iterator lbase_itr = _base_space->cover_iterator(false, BOTTOM_INDEX);
  cover_set_iterator lfiber_itr = _fiber_schema->cover_iterator(false, BOTTOM_INDEX);
  while(!lbase_itr.is_done())
  {
    lfiber_itr.reset();

    while(!lfiber_itr.is_done())
    {
      if(!_fiber_schema->table_dof_subposet().contains_member(lfiber_itr.item()))
      {
	// fiber schema atom is not a table dof.
	// add member base space atom x fiber schema atom.

	ordinal(lbase_itr.item(), lfiber_itr.item(), lid);
	lcover->push_back(lid);
      }
      
      lfiber_itr.next();
    }

    lbase_itr.next();
  }

  cover_set_iterator result(lcover);

  // Postconditions:

  // Exit:

  return result;
}
  

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COVER SET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::cover_set_iterator
fiber_bundle::product_section_space_schema_crg_range::
implicit_cover_iterator(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  list_cover_set* lcover = new list_cover_set(0);
  lcover->put_is_implicit(true);

  pod_index_type lbase_space_id, lfiber_schema_id, lid;

  tuple(xmbr_index, lbase_space_id, lfiber_schema_id);

  if(xlower &&
     (_base_space->is_atom(lbase_space_id) &&
      _fiber_schema->is_atom(lfiber_schema_id)))
  {
    if(_fiber_schema->table_dof_subposet().contains_member(lfiber_schema_id))
    {
      // Lower cover of (base space atom, fiber schema table dof id) =
      // (base space bottom, fiber schema table dof id)

      _table_dof_range->ordinal(BOTTOM_INDEX, lfiber_schema_id, lid);
      lcover->push_back(lid);
    }
    else
    {
      // Lower cover of (base space atom, fiber schema row dof id) = BOTTOM_INDEX.

      lcover->push_back(BOTTOM_INDEX);
    }
  }
  else
  {
    // base_space.cover_iterator(xlower, lbase_space_id) x lfiber_schema_id.

    cover_set_iterator lbase_itr = _base_space->cover_iterator(xlower, lbase_space_id);
    while(!lbase_itr.is_done())
    {
      if(lbase_itr.item() != BOTTOM_INDEX)
      {
	ordinal(lbase_itr.item(), lfiber_schema_id, lid);
      
	lcover->push_back(lid);
      }
      
      lbase_itr.next();
    }

    // base_space_id x fiber_schema.cover_iterator(xlower, lfiber_schema_id).

    cover_set_iterator lfiber_itr = _fiber_schema->cover_iterator(xlower, lfiber_schema_id);
    while(!lfiber_itr.is_done())
    {
      if(lfiber_itr.item() != BOTTOM_INDEX)
      {
	ordinal(lbase_space_id, lfiber_itr.item(), lid);

	lcover->push_back(lid);
      }
      
      lfiber_itr.next();
    }
  }

  cover_set_iterator result(lcover);

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::product_section_space_schema_crg_range::
implicit_cover_is_empty(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  // The cover is never empty.

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return false;
}

sheaf::size_type
fiber_bundle::product_section_space_schema_crg_range::
implicit_cover_size(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lbase_space_id, lfiber_schema_id;

  tuple(xmbr_index, lbase_space_id, lfiber_schema_id);

  size_type result = 0;
  
  // Deal with special cases.

  if(xlower &&
     _base_space->is_atom(lbase_space_id) &&
     _fiber_schema->is_atom(lfiber_schema_id))
  {
    // Product of base space atom and fiber schema atom.

    result = 1;
  }
  else
  {
    result =
      _base_space->cover_ct(xlower, lbase_space_id) +
      _fiber_schema->cover_ct(xlower, lfiber_schema_id);
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::product_section_space_schema_crg_range::
implicit_cover_contains_member(bool xlower,
			       pod_index_type xmbr_index,
			       pod_index_type xother_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  // Factor xmbr_index.

  pod_index_type lbase_space_id, lfiber_schema_id;

  tuple(xmbr_index, lbase_space_id, lfiber_schema_id);

  bool result;

  if(xlower &&
     (_base_space->is_atom(lbase_space_id) &&
      _fiber_schema->is_atom(lfiber_schema_id)))
  {
    if(_fiber_schema->table_dof_subposet().contains_member(lfiber_schema_id))
    {
      // Lower cover of (base space atom, fiber schema table dof id) =
      // (base space bottom, fiber schema table dof id)

      pod_index_type lother_base_space_id, lother_fiber_schema_id;
      _table_dof_range->tuple(xother_index, lother_base_space_id, lother_fiber_schema_id);

      result = (lother_base_space_id == BOTTOM_INDEX) && (lother_fiber_schema_id == lfiber_schema_id);
    }
    else
    {
      // xmbr_index is an atom, the lower cover is bottom.

      result = (xother_index == BOTTOM_INDEX);
    }
  }
  else
  {
    // Factor xother_index.

    pod_index_type lother_base_space_id, lother_fiber_schema_id;

    tuple(xother_index, lother_base_space_id, lother_fiber_schema_id);

    // True if one of two conditions are true;
    // (1) The other base space member is in the cover of the base space member
    //     and the fiber schema members are the same.
    // (2) The other fiber schema member is in the cover of the fiber schema member
    //     and the base space members are the same.

    result =
      (_base_space->cover_contains_member(xlower, lbase_space_id, lother_base_space_id) &&
       (lfiber_schema_id == lother_fiber_schema_id)) ||
      (_fiber_schema->cover_contains_member(xlower, lfiber_schema_id, lother_fiber_schema_id) &&
       (lbase_space_id == lother_base_space_id));
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::product_section_space_schema_crg_range::
implicit_first_cover_member(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(!cover_is_empty(xlower, xmbr_index));

  // Body:

  pod_index_type result = invalid_pod_index();

  pod_index_type lbase_space_id, lfiber_schema_id;

  tuple(xmbr_index, lbase_space_id, lfiber_schema_id);

  if(xlower && _base_space->is_atom(lbase_space_id))
  {
    // The base space component is an atom.

    if(_fiber_schema->table_dof_subposet().contains_member(lfiber_schema_id))
    {
      // The fiber schema is a table dof, the lower cover is
      // (base space bottom, fiber schema table dof)

      _table_dof_range->ordinal(BOTTOM_INDEX, lfiber_schema_id, result);
    }
    else if(_fiber_schema->is_atom(lfiber_schema_id))
    {
      // The fiber schema component is an atom, the lower cover is bottom.

      result = BOTTOM_INDEX;
    }
    else
    {
      // The first member is the first member in the fiber schema's
      // lower cover.

      ordinal(lbase_space_id,
	      _fiber_schema->first_cover_member(xlower, lfiber_schema_id),
	      result);
    }
  }
  else
  {
    ordinal(_base_space->first_cover_member(xlower, lbase_space_id),
	    lfiber_schema_id, result);
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DOF_TUPLE_ID FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::product_section_space_schema_crg_range::
is_jim(pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lbase_space_id, lfiber_schema_id;

  tuple(xmbr_index, lbase_space_id, lfiber_schema_id);

  bool result =
    _base_space->is_jim(lbase_space_id) &&
    _fiber_schema->is_jim(lfiber_schema_id);
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::scoped_index&
fiber_bundle::product_section_space_schema_crg_range::
dof_tuple_id(pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lbase_space_id, lfiber_schema_id;

  tuple(xmbr_index, lbase_space_id, lfiber_schema_id);

  const scoped_index& result = _fiber_schema->dof_tuple_id(lfiber_schema_id);

  // Postconditions:

  ensure(result.is_valid());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRIVATE_DATA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::size_type
fiber_bundle::product_section_space_schema_crg_range::
implicit_private_data_size() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return 0;
}

void
fiber_bundle::product_section_space_schema_crg_range::
get_implicit_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  // nothing to do.

  // Postconditions:

  ensure(xdata.ct() == implicit_private_data_size());

  // Exit:

  return;
}

void
fiber_bundle::product_section_space_schema_crg_range::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  require(xdata.ct() >= implicit_private_data_size());

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FINIALIZE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::product_section_space_schema_crg_range::
finalize(poset_state_handle& xhost)
{
  // Preconditions:

  require(dynamic_cast<product_section_space_schema_poset*>(&xhost) != 0);
  require(xhost.state_is_read_accessible());

  // Body:

  product_section_space_schema_poset& lhost =
    reinterpret_cast<product_section_space_schema_poset&>(xhost);

  // Initialize base space.

  initialize_base_space(lhost.base_space());

  // Initialize fiber schema.

  initialize_fiber_schema(lhost.fiber_schema());

  // Initialize the gathered hub id spaces.

  initialize_gathered_id_spaces();

  // Initialize the product structure.

  initialize_product_structure();

  // Initialize the table dof crg range.

  initialize_table_dof_range(lhost.table_dof_range());

  // Put atoms in upper cover of bottom.

  /// @hack this same call is made in poset_crg_state::new_member_range,
  /// where it fails silectly because the vertex range is empty.
  /// This protocol is way too arcane and we need to find some better way.

  xhost.append_cover(atoms(), UPPER, BOTTOM_INDEX);

  implicit_crg_range::finalize(xhost);

  // Set the range of the host to this.

  lhost.put_product_range(*this);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::product_section_space_schema_crg_range::
is_initialized() const
{
  // Preconditions:

  // Body:

  bool result =
    implicit_crg_range::is_initialized() &&
    base_space_initialized() &&
    fiber_schema_initialized() &&
    product_structure_initialized() &&
    table_dof_range_initialized();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const std::string&
fiber_bundle::product_section_space_schema_crg_range::
class_name() const
{
  // Preconditions:

  // Body:

  static const string result("product_section_space_schema_crg_range");

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::product_section_space_schema_crg_range::
make_prototype()
{
  // Preconditions:

  // Body:

  product_section_space_schema_crg_range* lproto =
    new product_section_space_schema_crg_range();

  range_factory().insert_prototype(lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::product_section_space_schema_crg_range::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const product_section_space_schema_crg_range*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::product_section_space_schema_crg_range*
fiber_bundle::product_section_space_schema_crg_range::
clone() const
{
  product_section_space_schema_crg_range* result;
  
  // Preconditions:

  // Body:
  
  result = new product_section_space_schema_crg_range();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
fiber_bundle::product_section_space_schema_crg_range::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(section_space_schema_crg_range::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
