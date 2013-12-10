
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

// Implementation for class array_section_dof_map

#include "array_section_dof_map.h"

#include "assert_contract.h"
#include "discretization_iterator.h"
#include "error_message.h"
#include "dof_map_factory.h"
#include "postorder_iterator.h"
#include "sec_rep_space.h"
#include "primitive_type.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT
#define BOUNDS_CHECK

// PUBLIC MEMBER FUNCTIONS

///
const std::string&
fiber_bundle::array_section_dof_map::
class_name() const
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
fiber_bundle::array_section_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("array_section_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "array_section_dof_map");

  // Exit:

  return result;
}

// CANONICAL MEMBERS

///
fiber_bundle::array_section_dof_map::
array_section_dof_map()
    : section_dof_map()
{

  // Preconditions:


  // Body:

  _local_ct = 0;
  _fiber_dof_ct = 0;
  _dofs = 0;
  _this_owns_dofs = false;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());


  // Exit

  return;
}

///
fiber_bundle::array_section_dof_map*
fiber_bundle::array_section_dof_map::
clone() const
{
  array_section_dof_map* result;

  // Preconditions:


  // Body:

  result = new array_section_dof_map();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(array_section_dof_map()));

  // Exit:

  return result;
}


///
fiber_bundle::array_section_dof_map::
array_section_dof_map(const array_section_dof_map& xother)
    : section_dof_map(xother)
{

  // Preconditions:


  // Body:

  _local_ct = 0;
  _fiber_dof_ct = 0;
  _dofs = 0;
  _this_owns_dofs = false;

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
fiber_bundle::array_section_dof_map*
fiber_bundle::array_section_dof_map::
copy() const
{
  array_section_dof_map* result;

  // Preconditions:


  // Body:

  result = new array_section_dof_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(array_section_dof_map(*this)));

  // Exit:

  return result;
}


///
fiber_bundle::array_section_dof_map&
fiber_bundle::array_section_dof_map::
operator=(const array_section_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  section_dof_map::operator=(xother);

  if(_dofs != 0)
  {
    delete[] _dofs;
  }

  if(xother._dofs != 0)
  {
    // Copy the counts

    _fiber_dof_ct = xother._fiber_dof_ct;
    _local_ct = xother._local_ct;

    // Allocate and copy the dof storage

    _this_owns_dofs = xother._this_owns_dofs;

    if(_this_owns_dofs)
    {
      _dofs = new char[dof_tuple_ub()];
      memcpy(_dofs, xother._dofs, dof_tuple_ub());
    }
    else
    {
      _dofs = xother._dofs;
    }
  }
  else
  {
    _fiber_dof_ct = 0;
    _local_ct = 0;

    _dofs = 0;
    _this_owns_dofs = false;
  }

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}


///
fiber_bundle::array_section_dof_map::
~array_section_dof_map()
{
  // Preconditions:


  // Body:

  if(_this_owns_dofs)
    delete[] _dofs;

  // Postconditions:

  // Exit:

  return;
}


///
bool
fiber_bundle::array_section_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  /// @todo implement array_section_dof_map::invariant() const

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// MAP FACET
// ===========================================================

fiber_bundle::array_section_dof_map::
array_section_dof_map(sec_rep_space* xhost, void* xdofs, size_t xdofs_ub)
  : section_dof_map(xhost, xhost->base().index().pod(), xhost->version())
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xdofs != 0 ? xdofs_ub >= xhost->schema().row_dof_tuple_ub(): true);
  require(unexecutable("if xdofs != 0 it points to buffer of length xdofs_ub"));

  // Body:

  init_dofs(xdofs, xdofs_ub);

  // Postconditions:

  ensure(_local_ct > 0);
  ensure(dof_ct() == schema().row_dof_ct());
  ensure(dof_tuple_ub() == schema().row_dof_tuple_ub());
  ensure(_dofs != 0);
  ensure(xdofs != 0 ? _dofs == xdofs : true);

}

fiber_bundle::array_section_dof_map::
array_section_dof_map(sec_rep_space* xhost,
                      pod_index_type xbase_id,
                      int xversion,
                      void* xdofs,
                      size_t xdofs_ub)
    : section_dof_map(xhost, xbase_id, xversion)
{

  // Preconditions:

  require(precondition_of(sec_dof_map::sec_dof_map(xhost, xbase_id, xversion)));
  require(unexecutable("if xdofs != 0 it points to buffer of length xdofs_ub"));
  /// @todo make the following executable.
  require(unexecutable("if xdofs != 0 xdofs_ub is large enough"));

  // Body:

  init_dofs(xdofs, xdofs_ub);

  // Private "postconditions"

  assertion(_local_ct > 0);
  assertion(_dofs != 0);
  assertion(xdofs != 0 ? _dofs == xdofs : true);

  // Postconditions:

  ensure(postcondition_of(sec_dof_map::sec_dof_map(xhost, xbase_id, xversion)));
  ensure(is_initialized());
  ensure(dof_tuple() != 0);
  ensure(xdofs != 0 ? dof_tuple() == xdofs : true);

}

fiber_bundle::array_section_dof_map::
array_section_dof_map(sec_rep_space* xhost,
                      const scoped_index& xbase_id,
                      int xversion,
                      void* xdofs,
                      size_t xdofs_ub)
  : section_dof_map(xhost, xbase_id.hub_pod(), xversion)
{

  // Preconditions:

  require(precondition_of(sec_dof_map::sec_dof_map(xhost, xbase_id, xversion)));
  require(unexecutable("if xdofs != 0 it points to buffer of length xdofs_ub"));
  /// @todo make the following executable.
  require(unexecutable("if xdofs != 0 xdofs_ub is large enough"));

  // Body:

  init_dofs(xdofs, xdofs_ub);

  // Private "postconditions"

  assertion(_local_ct > 0);
  assertion(_dofs != 0);
  assertion(xdofs != 0 ? _dofs == xdofs : true);

  // Postconditions:

  ensure(postcondition_of(sec_dof_map::sec_dof_map(xhost, xbase_id, xversion)));
  ensure(is_initialized());
  ensure(dof_tuple() != 0);
  ensure(xdofs != 0 ? dof_tuple() == xdofs : true);

}

 

// ===========================================================
//  NEW DOF ACCESS FACET
// ===========================================================

bool
fiber_bundle::array_section_dof_map::
dof_in_bounds(pod_index_type xdof_id, bool xis_table_dofs) const
{
  // Preconditions:


  // Body:

  size_type loffset = schema().offset(xdof_id, xis_table_dofs);
  size_type lsize = schema().size(xdof_id, xis_table_dofs);
  size_type lub = loffset + lsize;

  bool result = (lub <= _dof_tuple_ub);

#ifdef DIAGNOSTIC_OUTPUT
  cout << " xdof_id: " << xdof_id
       << " offset: " << loffset
       << " size: " << lsize
       << " ub: " << lub
       << " dofs ub: " << _dof_tuple_ub
       << " result: " << boolalpha << result << noboolalpha
       << endl;
#endif  

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::array_section_dof_map::
dof_in_bounds(pod_index_type xdisc_id, pod_index_type xfiber_id, bool xis_table_dofs) const
{
  // Preconditions:


  // Body:

  size_type loffset = schema().offset(xdisc_id, xfiber_id, xis_table_dofs);
  size_type lsize = schema().size(xdisc_id, xfiber_id, xis_table_dofs);
  size_type lub = loffset + lsize;  

  bool result = (lub <= _dof_tuple_ub);
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << " xdisc_id: " << xdisc_id
       << " xfiber_id: " << xfiber_id
       << " offset: " << loffset
       << " size: " << lsize
       << " ub: " << lub
       << " dofs ub: " << _dof_tuple_ub
       << " result: " << boolalpha << result << noboolalpha
       << endl;
#endif  

  // Postconditions:


  // Exit:

  return result;
}
 
///
void
fiber_bundle::array_section_dof_map::
get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));

#ifdef BOUNDS_CHECK
  require(dof_in_bounds(xdof_id, is_table_dof_map()));
#endif

  // Body:

  
  memcpy(xdof, dof_ptr(xdof_id, is_table_dof_map()), schema().size(xdof_id, is_table_dof_map()));

  // Postconditions:

  // Exit

  return;
}


///
void
fiber_bundle::array_section_dof_map::
put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));

#ifdef BOUNDS_CHECK
  require(dof_in_bounds(xdof_id, is_table_dof_map()));
#endif

  // Body:

  memcpy(dof_ptr(xdof_id, is_table_dof_map()), xdof, schema().size(xdof_id, is_table_dof_map()));


  // Postconditions:

  ensure(unexecutable(internal storage holds dof referred to by xdof_id and xis_poset_id));

  // Exit

  return;
}



void
fiber_bundle::array_section_dof_map::
get_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id));

#ifdef BOUNDS_CHECK
  require(dof_in_bounds(xdisc_id, xfiber_dof_id, is_table_dof_map()));
#endif
  
  
  // Body:

  memcpy(xdof, 
	 dof_ptr(xdisc_id, xfiber_dof_id, is_table_dof_map()),
	 schema().size(xdisc_id, xfiber_dof_id, is_table_dof_map()));
  
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_section_dof_map::
put_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id));

#ifdef BOUNDS_CHECK
  require(dof_in_bounds(xdisc_id, xfiber_dof_id, is_table_dof_map()));
#endif
  
  
  // Body:

  memcpy(dof_ptr(xdisc_id, xfiber_dof_id, is_table_dof_map()), 
	 xdof,
	 schema().size(xdisc_id, xfiber_dof_id, is_table_dof_map()));
  
  
  // Postconditions:


  // Exit:

  return;
}

bool
fiber_bundle::array_section_dof_map::
fiber_in_bounds(pod_index_type xdisc_id, bool xis_table_dofs) const
{
  // Preconditions:


  // Body:

  size_type loffset = schema().offset(xdisc_id, 0, xis_table_dofs);
  size_type lsize = schema().fiber_size();
  size_type lub = loffset + lsize;  

  bool result = (lub <= _dof_tuple_ub);

#ifdef DIAGNOSTIC_OUTPUT
  cout << " xdisc_id: " << xdisc_id
       << " offset: " << loffset
       << " size: " << lsize
       << " ub: " << lub
       << " dofs ub: " << _dof_tuple_ub
       << " result: " << boolalpha << result << noboolalpha
       << endl;
#endif  

  // Postconditions:


  // Exit:

  return result;
}

void
fiber_bundle::array_section_dof_map::
reserve_fiber(pod_index_type xdisc_id)
{
  // Preconditions:

  // The following precondition seems reasonable, but it is
  // not actually necessary and it triggers an update of the
  // schema row cache, which can be a performance problem.
  // ensure(schema().discretization_id_space().contains(xdisc_id));
  
  // Body:

  size_t ltuple_size = schema().fiber_schema().row_dof_tuple_ub();

  size_t ldof_tuple_ub = (xdisc_id+1)*ltuple_size;

  reserve(ldof_tuple_ub);

#ifdef DIAGNOSTIC_OUTPUT
  cout << " xdisc_id: " << xdisc_id
       << " ltuple_size: " << ltuple_size
       << " ldof_tuple_ub: " << ldof_tuple_ub
       << " dof_tuple_ub: " << dof_tuple_ub()
       << endl;
#endif

  // Postconditions:

  ensure(dof_tuple_ub() >= (xdisc_id+1)*schema().fiber_schema().row_dof_tuple_ub());
  
  // Exit:

  return;
}

void
fiber_bundle::array_section_dof_map::
get_fiber(pod_index_type xdisc_id, void* xfiber, size_type xfiber_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());

#ifdef BOUNDS_CHECK
  require(fiber_in_bounds(xdisc_id, is_table_dof_map()));
#endif
  
  
  // Body:

  memcpy(xfiber, dof_ptr(xdisc_id, 0, is_table_dof_map()), schema().fiber_size());  
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_section_dof_map::
put_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());

#ifdef BOUNDS_CHECK
  require(fiber_in_bounds(xdisc_id, is_table_dof_map()));
#endif
  
  
  // Body:

  memcpy(dof_ptr(xdisc_id, 0, is_table_dof_map()), xfiber, schema().fiber_size());  
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_section_dof_map::
force_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  
  // Body:

  reserve_fiber(xdisc_id);
  
  memcpy(dof_ptr(xdisc_id, 0, is_table_dof_map()), xfiber, schema().fiber_size());  
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_section_dof_map::
get_component(pod_index_type xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));
  
  
  // Body:

  char* lcomponent = reinterpret_cast<char*>(xcomponent);
  char* ldof = reinterpret_cast<char*>(dof_ptr(0, xfiber_dof_id, is_table_dof_map()));
  size_type ldof_size = schema().size(0, xfiber_dof_id, false);
  size_type lfiber_size = schema().fiber_size();
  size_type ldisc_ct = schema().discretization_ct();
  
  for(pod_index_type i=0; i<ldisc_ct; ++i)
  {
    memcpy(lcomponent, ldof, ldof_size);
    lcomponent += ldof_size;
    ldof += lfiber_size;
  }
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_section_dof_map::
put_component(pod_index_type xfiber_dof_id, const void* xcomponent, size_type xcomponent_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));
  
  
  // Body:

  const char* lcomponent = reinterpret_cast<const char*>(xcomponent);
  char* ldof = reinterpret_cast<char*>(dof_ptr(0, xfiber_dof_id, is_table_dof_map()));
  size_type ldof_size = schema().size(0, xfiber_dof_id, false);
  size_type lfiber_size = schema().fiber_size();
  size_type ldisc_ct = schema().discretization_ct();
  
  for(pod_index_type i=0; i<ldisc_ct; ++i)
  {
    memcpy(ldof, lcomponent, ldof_size);
    lcomponent += ldof_size;
    ldof += lfiber_size;
  }
  
  // Postconditions:


  // Exit:

  return;
}

  
// ===========================================================
//  END NEW DOF ACCESS FACET
// ===========================================================

///
void*
fiber_bundle::array_section_dof_map::
dof_tuple()
{
  void* result;

  // Preconditions:

  // Body:

  result = _dofs;

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

///
const void*
fiber_bundle::array_section_dof_map::
dof_tuple() const
{
  const void* result;

  // Preconditions:

  // Body:

  result = _dofs;

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

///
void
fiber_bundle::array_section_dof_map::
get_dof_tuple(void* xbuf, size_t xbuflen) const
{
  // Preconditions:

  require(xbuf != 0);
  require(dof_tuple_ub() <= xbuflen);

  // Body:

  memcpy(xbuf, static_cast<void*>(_dofs), dof_tuple_ub());

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(dof tuple copied to xbuf));

  // Exit

  return;
}


///
void
fiber_bundle::array_section_dof_map::
put_dof_tuple(const void* xbuf, size_t xbuflen)
{
  // Preconditions:

  require(xbuf != 0);
  require(dof_tuple_ub() <= xbuflen);

  // Body:

  memcpy(static_cast<void*>(_dofs), xbuf, dof_tuple_ub());

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(xbuf copied to dof tuple));

  // Exit

  return ;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::array_section_dof_map::
init_dofs(void* xdofs, size_t xdofs_ub)
{

  // Preconditions:

  require(xdofs != 0 ? xdofs_ub >= schema().row_dof_tuple_ub(): true);
  require(unexecutable("if xdofs != 0 it points to buffer of length xdofs_ub"));

  // Body:

  _fiber_dof_ct = schema().fiber_schema().row_dof_ct();
  _local_ct = host()->multiplicity();

  // Initialize dof storage

  _dofs = static_cast<char*>(xdofs);

  if(_dofs == 0)
  {
    _dofs = new char[_dof_tuple_ub];
    _this_owns_dofs = true;
  }
  else
  {
    _this_owns_dofs = false;
  }

  // Postconditions:

  ensure(_local_ct > 0);
  ensure(_dofs != 0);
  ensure(xdofs != 0 ? _dofs == xdofs : true);

  // Exit:

  return;
}

///
void
fiber_bundle::array_section_dof_map::
allocate_dofs()
{
  // Preconditions:


  // Body:

  init_dofs(0,0);

  // Postconditions:


  // Exit:

  return;
}

bool
fiber_bundle::array_section_dof_map::
make_prototype()
{
  bool result = false;

  // Preconditions:


  // Body:

  dof_tuple_type ltype = ARRAY_SECTION_DOF_TUPLE_ID;

  poset_dof_map* lproto = new array_section_dof_map;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:


  // Exit:

  return result;
}


///
void
fiber_bundle::array_section_dof_map::
reserve(size_t xdof_tuple_ub)
{

  // Preconditions:

  require(_dofs != 0);
  require(_this_owns_dofs);

  // Body:

  define_old_variable(int old_dof_tuple_ub = _dof_tuple_ub);

  if(xdof_tuple_ub > _dof_tuple_ub)
  {
    size_t new_ub = _dof_tuple_ub*2;
    if(new_ub < xdof_tuple_ub)
    {
      new_ub = xdof_tuple_ub;
    }

    // Allocate a new dofs array

    char* new_dofs = new char[new_ub];

    // Copy the old contents to the new array
    // and delete the old array.

    memcpy(new_dofs, _dofs, _dof_tuple_ub);
    delete [] _dofs;

    // Update base and bound.

    _dofs = new_dofs;
    _dof_tuple_ub   = new_ub;
  }

  // Postconditions:

  ensure(invariant());
  ensure(_dof_tuple_ub >= old_dof_tuple_ub);
  ensure(_dof_tuple_ub >= xdof_tuple_ub);

  // Exit:

  return;
}
