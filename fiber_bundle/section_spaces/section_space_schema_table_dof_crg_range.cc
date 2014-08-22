
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
/// Implementation for class section_space_schema_table_dof_crg_range

#include "ComLimitPoint/fiber_bundle/section_space_schema_table_dof_crg_range.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/factory.h"
#include "ComLimitPoint/fiber_bundle/cover_set_iterator.h"
#include "ComLimitPoint/sheaf/ij_product_structure.h"
#include "ComLimitPoint/sheaf/index_space_iterator.h"
#include "ComLimitPoint/fiber_bundle/product_section_space_schema_crg_range.h"
#include "ComLimitPoint/fiber_bundle/product_section_space_schema_poset.h"

// ===========================================================
// SECTION_SPACE_SCHEMA_TABLE_DOF_CRG_RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::section_space_schema_table_dof_crg_range::
section_space_schema_table_dof_crg_range()
  : _product_range(0)
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

fiber_bundle::section_space_schema_table_dof_crg_range::
~section_space_schema_table_dof_crg_range()
{  
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  // Exit:

  return; 
}

bool
fiber_bundle::section_space_schema_table_dof_crg_range::
product_range_initialized() const
{
  // Preconditions:

  // Body:

  bool result = (_product_range != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_table_dof_crg_range::
initialize_product_range(product_section_space_schema_crg_range& xproduct_range)
{
  // Preconditions:

  require(!product_range_initialized());

  // Body:

  _product_range = &xproduct_range;

  // Postconditions:

  ensure(product_range_initialized());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION_SPACE_SCHEMA_CRG_RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_table_dof_crg_range::
contains_member(pod_index_type xbase_space_id,
		pod_index_type xfiber_schema_id) const
{
  // Preconditions:

  // Body:

  bool result =
    xbase_space_id == BOTTOM_INDEX &&
    _fiber_schema->table_dof_subposet().id_space().contains_hub(xfiber_schema_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_table_dof_crg_range::
tuple(pod_index_type xindex,
      pod_index_type& xbase_space_id,
      pod_index_type& xfiber_schema_id) const
{
  // Preconditions:

  require(local_id_space().contains_hub(xindex));

  // Body:

  pod_index_type lpod = _local_id_space.pod(xindex);

  xbase_space_id = BOTTOM_INDEX;
  xfiber_schema_id =
    _fiber_schema->table_dof_subposet().id_space().hub_pod(lpod);

  // Postconditions:

  ensure(contains_member(xbase_space_id, xfiber_schema_id));

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_table_dof_crg_range::
ordinal(pod_index_type xbase_space_id,
	pod_index_type xfiber_schema_id,
	pod_index_type& xindex) const
{
  // Preconditions:

  require(contains_member(xbase_space_id, xfiber_schema_id));

  // Body:

  xindex = _fiber_schema->table_dof_subposet().id_space().pod(xfiber_schema_id);
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
fiber_bundle::section_space_schema_table_dof_crg_range::
get_size(const product_section_space_schema_poset& xhost, size_type& result)
{
  // Preconditions:

  require(xhost.state_is_read_accessible());

  // Body:

  result = xhost.fiber_schema().table_dof_subposet().id_space().ct();

  // Postconditions:

  // Exit:

  return;
}

sheaf::cover_set_iterator
fiber_bundle::section_space_schema_table_dof_crg_range::
atoms() const
{
  // Preconditions:

  // Body:

  list_cover_set* lcover = new list_cover_set(0);
  lcover->put_is_implicit(true);


  index_space_iterator& litr =
    _fiber_schema->table_dof_subposet().id_space().get_iterator();
  while(!litr.is_done())
  {
    lcover->push_back(_local_id_space.hub_pod(litr.pod()));

    litr.next();
  }
  _fiber_schema->table_dof_subposet().id_space().release_iterator(litr);

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
fiber_bundle::section_space_schema_table_dof_crg_range::
implicit_cover_iterator(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  list_cover_set* lcover = new list_cover_set(0);
  lcover->put_is_implicit(true);

  if(xlower)
  {
    lcover->push_back(BOTTOM_INDEX);
  }
  else
  {
    pod_index_type lbase_space_id, lfiber_schema_id, lid;
    tuple(xmbr_index, lbase_space_id, lfiber_schema_id);

    cover_set_iterator litr = _base_space->cover_iterator(false, BOTTOM_INDEX);
    while(!litr.is_done())
    {
      _product_range->ordinal(litr.item(), lfiber_schema_id, lid);
      lcover->push_back(lid);

      litr.next();
    }
  }

  cover_set_iterator result(lcover);

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_table_dof_crg_range::
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
fiber_bundle::section_space_schema_table_dof_crg_range::
implicit_cover_size(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  size_type result;

  if(xlower)
  {
    result = 1;
  }
  else
  {
    result = _base_space->cover_ct(false, BOTTOM_INDEX);
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_table_dof_crg_range::
implicit_cover_contains_member(bool xlower,
			       pod_index_type xmbr_index,
			       pod_index_type xother_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  // Factor xmbr_index.

  bool result;

  if(xlower)
  {
    result = (xother_index == BOTTOM_INDEX);
  }
  else
  {
    pod_index_type lbase_space_id, lfiber_schema_id;
    tuple(xmbr_index, lbase_space_id, lfiber_schema_id);

    if(_product_range->contains_member(xother_index))
    {
      // In the product range, factor xother_index.

      pod_index_type lother_base_space_id, lother_fiber_schema_id;
      _product_range->tuple(xother_index, lother_base_space_id, lother_fiber_schema_id);

      result = (lother_base_space_id == BOTTOM_INDEX) && (lother_fiber_schema_id == lfiber_schema_id);
    }
    else
    {
      // Not in the product range, cover does not contain the member.

      result = false;
    }
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_table_dof_crg_range::
implicit_first_cover_member(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(!cover_is_empty(xlower, xmbr_index));

  // Body:

  pod_index_type result;

  if(_fiber_schema->is_atom(_local_id_space.pod(xmbr_index)))
  {
    result = BOTTOM_INDEX;
  }
  else
  {
    result = _base_space->first_cover_member(false, BOTTOM_INDEX);
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
fiber_bundle::section_space_schema_table_dof_crg_range::
is_jim(pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  // All members are jims.
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return true;
}

const sheaf::scoped_index&
fiber_bundle::section_space_schema_table_dof_crg_range::
dof_tuple_id(pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type lfiber_schema_id =
    _fiber_schema->table_dof_subposet().id_space().hub_pod(_local_id_space.pod(xmbr_index));

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
fiber_bundle::section_space_schema_table_dof_crg_range::
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
fiber_bundle::section_space_schema_table_dof_crg_range::
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
fiber_bundle::section_space_schema_table_dof_crg_range::
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
fiber_bundle::section_space_schema_table_dof_crg_range::
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

  // Initialize the product crg range.

  initialize_product_range(lhost.product_range());

  // Put atoms in upper cover of bottom.

  /// @hack this same call is made in poset_crg_state::new_member_range,
  /// where it fails silectly because the vertex range is empty.
  /// This protocol is way too arcane and we need to find some better way.

  xhost.append_cover(atoms(), UPPER, BOTTOM_INDEX);

  implicit_crg_range::finalize(xhost);

  // Set the range of the host to this.

  lhost.put_table_dof_range(*this);

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
fiber_bundle::section_space_schema_table_dof_crg_range::
is_initialized() const
{
  // Preconditions:

  // Body:

  bool result =
    implicit_crg_range::is_initialized() &&
    product_range_initialized();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const std::string&
fiber_bundle::section_space_schema_table_dof_crg_range::
class_name() const
{
  // Preconditions:

  // Body:

  static const string result("section_space_schema_table_dof_crg_range");

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_table_dof_crg_range::
make_prototype()
{
  // Preconditions:

  // Body:

  section_space_schema_table_dof_crg_range* lproto =
    new section_space_schema_table_dof_crg_range();

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
fiber_bundle::section_space_schema_table_dof_crg_range::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const section_space_schema_table_dof_crg_range*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::section_space_schema_table_dof_crg_range*
fiber_bundle::section_space_schema_table_dof_crg_range::
clone() const
{
  // Preconditions:

  // Body:
  
  section_space_schema_table_dof_crg_range* result =
    new section_space_schema_table_dof_crg_range();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
fiber_bundle::section_space_schema_table_dof_crg_range::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(implicit_crg_range::invariant());

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
 
