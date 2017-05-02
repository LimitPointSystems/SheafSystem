
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

// Implementation for class array_sec_vd_dof_map

#include "SheafSystem/array_sec_vd_dof_map.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/discretization_iterator.h"
#include "SheafSystem/dof_map_factory.h"
#include "SheafSystem/id_map.h"
#include "SheafSystem/postorder_iterator.h"
#include "SheafSystem/sec_rep_space.h"
#include "SheafSystem/primitive_type.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// PUBLIC MEMBER FUNCTIONS

///
const std::string&
fiber_bundle::array_sec_vd_dof_map::
class_name()
{
  // Preconditions:

  // Body:

  const string& result = static_class_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const std::string&
fiber_bundle::array_sec_vd_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("array_sec_vd_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "array_sec_vd_dof_map");

  // Exit:

  return result;
}

// CANONICAL MEMBERS

///
fiber_bundle::array_sec_vd_dof_map::
array_sec_vd_dof_map()
    : array_section_dof_map()
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());


  // Exit

  return;
}

///
fiber_bundle::array_sec_vd_dof_map*
fiber_bundle::array_sec_vd_dof_map::
clone() const
{
  array_sec_vd_dof_map* result;

  // Preconditions:


  // Body:

  result = new array_sec_vd_dof_map();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(array_sec_vd_dof_map()));

  // Exit:

  return result;
}


///
fiber_bundle::array_sec_vd_dof_map::
array_sec_vd_dof_map(const array_sec_vd_dof_map& xother)
    : array_section_dof_map(xother)
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
fiber_bundle::array_sec_vd_dof_map*
fiber_bundle::array_sec_vd_dof_map::
copy() const
{
  array_sec_vd_dof_map* result;

  // Preconditions:


  // Body:

  result = new array_sec_vd_dof_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(array_sec_vd_dof_map(*this)));

  // Exit:

  return result;
}


///
fiber_bundle::array_sec_vd_dof_map&
fiber_bundle::array_sec_vd_dof_map::
operator=(const array_sec_vd_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  array_section_dof_map::operator=(xother);

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}


///
fiber_bundle::array_sec_vd_dof_map::
~array_sec_vd_dof_map()
{
  // Preconditions:


  // Body:

  // Postconditions:

  // Exit:

  return;
}


///
bool
fiber_bundle::array_sec_vd_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  /// @todo implement array_sec_vd_dof_map::invariant()

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// MAP FACET
// ===========================================================

///
fiber_bundle::array_sec_vd_dof_map::
array_sec_vd_dof_map(sec_rep_space* xhost, void* xdofs, size_t xdofs_ub)
  : array_section_dof_map(xhost, xdofs, xdofs_ub)
{

  // Preconditions:

  require(precondition_of(array_section_dof_map(xhost, xdofs, xdofs_ub)));

  // Body:


  // Postconditions:

  require(postcondition_of(array_section_dof_map(xhost, xdofs, xdofs_ub)));

}

///
fiber_bundle::array_sec_vd_dof_map::
array_sec_vd_dof_map(sec_rep_space* xhost,
                      const scoped_index& xbase_id,
                      int xversion,
                      void* xdofs,
                      size_t xdofs_ub)
  : array_section_dof_map(xhost, xbase_id, xversion, xdofs, xdofs_ub)
{

  // Preconditions:

  require(precondition_of(array_section_dof_map(xhost, xbase_id, xversion, xdofs, xdofs_ub)));

  // Body:

  // Postconditions:

  ensure(postcondition_of(array_section_dof_map(xhost, xbase_id, xversion, xdofs, xdofs_ub)));

}

// ===========================================================
//  NEW DOF ACCESS FACET
// ===========================================================
 
///
void
fiber_bundle::array_sec_vd_dof_map::
get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space().contains_range_id(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id));

  // Body:

  *reinterpret_cast<sec_vd_dof_type*>(xdof) = *dof_ptr(xdof_id);
  
  
  // Postconditions:

  // Exit

  return;
}


///
void
fiber_bundle::array_sec_vd_dof_map::
put_dof(pod_index_type xdof_id, bool xis_poset_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space().contains_range_id(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id));

  // Body:

  *dof_ptr(xdof_id) = *reinterpret_cast<sec_vd_dof_type*>(xdof);

  // Postconditions:

  ensure(unexecutable(internal storage holds dof referred to by xdof_id and xis_poset_id));

  // Exit

  return;
}

 
void
fiber_bundle::array_sec_vd_dof_map::
get_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains_range_id(xdisc_id));
  require(schema().fiber_id_space().contains_range_id(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id));
  
  
  // Body:

  pod_index_type ldof_id;
  row_dof_id_space().simple(xdisc_id, xfiber_id, ldof_id);

  *reinterpret_cast<sec_vd_dof_type*>(xdof) = *dof_ptr(ldof_id);
  
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_sec_vd_dof_map::
put_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains_range_id(xdisc_id));
  require(schema().fiber_id_space().contains_range_id(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id));
  
  
  // Body:

  pod_index_type ldof_id;
  row_dof_id_space().simple(xdisc_id, xfiber_id, ldof_id);

  *dof_ptr(ldof_id) = *reinterpret_cast<sec_vd_dof_type*>(xdof);
  
  
  // Postconditions:


  // Exit:

  return;
}

  
// ===========================================================
//  END NEW DOF ACCESS FACET
// ===========================================================
 




bool
fiber_bundle::array_sec_vd_dof_map::
_has_prototype = make_prototype();

///
bool
fiber_bundle::array_sec_vd_dof_map::
make_prototype()
{
  bool result = false;

  // Preconditions:


  // Body:

  dof_tuple_type ltype = ARRAY_SECTION_DOF_TUPLE_ID;

  poset_dof_map* lproto = new array_sec_vd_dof_map;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:


  // Exit:

  return result;
}


