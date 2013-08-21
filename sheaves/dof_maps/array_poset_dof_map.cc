
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class array_poset_dof_map

#include "array_poset_dof_map.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "error_message.h"
#include "dof_descriptor_array.h"
#include "dof_map_factory.h"
#include "poset_state_handle.h"
#include "std_string.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

#define BOUNDS_CHECK

// PUBLIC MEMBER FUNCTIONS

///
const string&
sheaf::array_poset_dof_map::
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
const string&
sheaf::array_poset_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("array_poset_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "array_poset_dof_map");

  // Exit:

  return result;
}

// CANONICAL MEMBERS

///
sheaf::array_poset_dof_map::
array_poset_dof_map()
    : poset_dof_map()
{

  // Preconditions:


  // Body:

  _dofs = 0;
  _dof_descriptors = 0;
  _this_owns_dofs = false;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}

///
sheaf::array_poset_dof_map*
sheaf::array_poset_dof_map::
clone() const
{
  array_poset_dof_map* result;

  // Preconditions:


  // Body:

  result = new array_poset_dof_map();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(array_poset_dof_map()));

  // Exit:

  return result;
}


///
sheaf::array_poset_dof_map::
array_poset_dof_map(const array_poset_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  _dofs = 0;
  _dof_descriptors = 0;
  _this_owns_dofs = false;

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
sheaf::array_poset_dof_map*
sheaf::array_poset_dof_map::
copy() const
{
  array_poset_dof_map* result;

  // Preconditions:


  // Body:

  result = new array_poset_dof_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(array_poset_dof_map(*this)));

  // Exit:

  return result;
}


///
sheaf::array_poset_dof_map&
sheaf::array_poset_dof_map::
operator=(const array_poset_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  poset_dof_map::operator=(xother);

  if(_dof_descriptors != 0)
    _dof_descriptors->remove_reference();

  if((_dofs != 0) && _this_owns_dofs)
    delete[] _dofs;

  if(xother._dofs != 0)
  {
    // Allocate and copy dof offsets

    _dof_descriptors = xother._dof_descriptors;
    _dof_descriptors->add_reference();


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
    _dofs = 0;
    _dof_descriptors = 0;
    _this_owns_dofs = false;
  }

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}


///
sheaf::array_poset_dof_map::
~array_poset_dof_map()
{

  // Preconditions:


  // Body:


  if(_dof_descriptors != 0)
    _dof_descriptors->remove_reference();

  if(_this_owns_dofs)
    delete[] _dofs;

  /// @error what about dofs that are char*?
  /// We need to delete the strings they point to.

  /// @issue most string dofs a re allocated using strdup,
  /// which uses malloc, not new, so must be freed rather than deleted.


  // Postconditions:

}


///
bool
sheaf::array_poset_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && poset_dof_map::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    // Last offset is upper bound on _dofs

    result = result && ( _dof_descriptors != 0 ? dof_tuple_ub() == (*_dof_descriptors)[dof_ct()].offset : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// OTHER CONSTRUCTORS

///
sheaf::array_poset_dof_map::
array_poset_dof_map(const poset_state_handle* xhost,
                    bool xis_table_dof_map,
                    void* xdofs,
                    size_t xdofs_ub)
    : poset_dof_map(xhost, xis_table_dof_map)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require((xdofs != 0) ? xdofs_ub >= xhost->schema().dof_tuple_ub(xis_table_dof_map): true);
  require(unexecutable("if xdofs != 0 it points to buffer of length xdofs_ub"));

  // Body:

  // Get the dof offsets from the dofs subposet in the schema,
  // via the host. Increment the reference count

  _dof_descriptors = schema().dof_descriptors(xis_table_dof_map);
  _dof_descriptors->add_reference();

  // Initialize dof storage

  init_dofs(xdofs);

  // Postconditions:

  ensure(dof_ct() == schema().dof_ct(is_table_dof_map()));
  ensure((dof_tuple() != 0) == (dof_ct() != 0));
  ensure(((dof_ct() != 0) && (xdofs != 0)) ? dof_tuple() == xdofs : true);
}

///
sheaf::array_poset_dof_map::
array_poset_dof_map(const schema_poset_member* xschema, bool xis_table_dof_map)
    : poset_dof_map(xschema, xis_table_dof_map)
{

  // Preconditions:

  require(xschema != 0);
  require(xschema->state_is_read_accessible());

  // Body:

  // Get the dof offsets from the dofs subposet in the schema,
  // increment the reference count

  _dof_descriptors = xschema->dof_descriptors(xis_table_dof_map);
  _dof_descriptors->add_reference();

  // Initialize dof storage

  init_dofs(0);

  // Postconditions:

  ensure(dof_ct() == xschema->dof_ct(is_table_dof_map()));
  ensure((dof_tuple() != 0) == (dof_ct() != 0));
}

// ===========================================================
// MAP FACET
// ===========================================================

 

///
sheaf::dof_tuple_type
sheaf::array_poset_dof_map::
type_id() const
{
  dof_tuple_type result;

  // Preconditions:

  // Body:

  result = ARRAY_POSET_DOF_TUPLE_ID;

  // Postconditions:

  ensure(result == ARRAY_POSET_DOF_TUPLE_ID);

  // Exit:

  return result;
}

 

// ===========================================================
//  NEW DOF ACCESS FACET
// ===========================================================


void
sheaf::array_poset_dof_map::
get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));

  // Body:

  dof_descriptor_array::dof_descriptor& ldesc = (*_dof_descriptors)[xdof_id];

  // Compute a pointer to the beginning of
  // the current dof in the dof tuple.

  char* ldof = _dofs+ldesc.offset;

  // Copy the dof into result.

#ifdef BOUNDS_CHECK
  dof_in_bounds(xdof_id);
#endif
  
  memcpy(xdof, ldof, ldesc.size);  

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::array_poset_dof_map::
put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));
  
  // Body:

  dof_descriptor_array::dof_descriptor& ldesc = (*_dof_descriptors)[xdof_id];

  // Compute a pointer to the beginning of
  // the current dof in the dof tuple.

  char* ldof = _dofs+ldesc.offset;

  // Copy the xdof into the dof.

#ifdef BOUNDS_CHECK
  dof_in_bounds(xdof_id);
#endif
  
  memcpy(ldof, xdof, ldesc.size);  

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
//  END NEW DOF ACCESS FACET
// ===========================================================

///
void*
sheaf::array_poset_dof_map::
dof_tuple()
{
  void* result;

  // Preconditions:

  // Body:

  result = _dofs;

  // Postconditions:

  ensure(invariant());
  ensure((result != 0) == (dof_ct() != 0));

  // Exit

  return result;
}

///
const void*
sheaf::array_poset_dof_map::
dof_tuple() const
{
  const void* result;

  // Preconditions:

  // Body:

  result = _dofs;

  // Postconditions:

  ensure(invariant());
  ensure((result != 0) == (dof_ct() != 0));

  // Exit

  return result;
}

///
void
sheaf::array_poset_dof_map::
get_dof_tuple(void* xbuf, size_t xbuflen) const
{
  // Preconditions:

  require(dof_ct() > 0);
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
sheaf::array_poset_dof_map::
put_dof_tuple(const void* xbuf, size_t xbuflen)
{
  // Preconditions:

  require(dof_ct() > 0);
  require(xbuf != 0);
  require(dof_tuple_ub() <= xbuflen);

  // Body:

  memcpy(static_cast<void*>(_dofs), xbuf, dof_tuple_ub());

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(xbuf copied to dof tuple));

  // Exit

  return;
}

///
char*
sheaf::array_poset_dof_map::
dof_ptr(const schema_poset_member& xschema_mbr)
{
  char* result;

  // Preconditions:

  require(schema().contains_row_dof(xschema_mbr));

  // Body:

  result = dof_ptr(client_id_space().pod(xschema_mbr.index()));

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

///
char*
sheaf::array_poset_dof_map::
dof_ptr(int xclient_id)
{
  char* result;

  // Preconditions:

  require(dof_ct() > 0);
  require((0 <= xclient_id) && (xclient_id < dof_ct()));

  // Body:

  size_t ldof_offset = (*_dof_descriptors)[xclient_id].offset;
  result = _dofs+ldof_offset;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

///
void
sheaf::array_poset_dof_map::
init_dofs(void* xdofs)
{
  // Preconditions:

  // Body:

  if(dof_ct() > 0)
  {
    if(xdofs == 0)
    {
      _dofs = new char[dof_tuple_ub()];
      _this_owns_dofs = true;
    }
    else
    {
      _dofs = static_cast<char*>(xdofs);
      _this_owns_dofs = false;
    }
  }
  else
  {
    _this_owns_dofs = false;
    _dofs = 0;
  }

  // Postconditions:

  ensure((dof_ct() != 0) == (_dofs != 0));
  ensure(unexecutable(size of _dofs array == dof_tuple_ub()));

  // Exit

  return;
}

///
void
sheaf::array_poset_dof_map::
allocate_dofs()
{
  // Preconditions:


  // Body:

  // Get the dof offsets from the dofs subposet in the schema,
  // via the host. Increment the reference count

  _dof_descriptors = schema().dof_descriptors(false);
  _dof_descriptors->add_reference();

  init_dofs(0);

  // Postconditions:


  // Exit:

  return;
}

bool
sheaf::array_poset_dof_map::
dof_in_bounds(pod_index_type xdof_id) const
{
  // Preconditions:


  // Body:

  dof_descriptor_array::dof_descriptor& ldesc = (*_dof_descriptors)[xdof_id];
  size_type loffset = ldesc.offset;
  size_type lsize = ldesc.size;
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

  if(!result)
  {
    post_fatal_error_message("dof_in_bounds check failed");
  }
  
  // Postconditions:


  // Exit:

  return result;
}

///
bool
sheaf::array_poset_dof_map::
make_prototype()
{
  bool result = false;

  // Preconditions:


  // Body:

  dof_tuple_type ltype = ARRAY_POSET_DOF_TUPLE_ID;

  poset_dof_map* lproto = new array_poset_dof_map;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:


  // Exit:

  return result;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

