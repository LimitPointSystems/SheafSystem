
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class namespace_poset_dof_map

#include "namespace_poset_dof_map.h"

#include "assert_contract.h"
#include "error_message.h"
#include "dof_map_factory.h"
#include "index_space_iterator.h"
#include "namespace_poset.h"
#include "namespace_poset_schema.h"
#include "poset_type.h"
#include "primitive_type.h"
#include "std_string.h"

// PUBLIC MEMBER FUNCTIONS

 

///
const string&
sheaf::namespace_poset_dof_map::
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
sheaf::namespace_poset_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("namespace_poset_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "namespace_poset_dof_map");

  // Exit:

  return result;
}

// CANONICAL MEMBERS

///
sheaf::namespace_poset_dof_map::
namespace_poset_dof_map()
    : poset_dof_map()
{

  // Preconditions:


  // Body:

  _dof_ct = NAMESPACE_SCHEMA_DOF_CT;
  _dof_tuple_ub = sizeof(_dofs);
  _dofs.pointer = 0;
  _dofs.type_id = NOT_A_POSET_TYPE;
  _dofs.class_name = 0;

  for(int i=0; i<PREREQ_IDS_UB; ++i)
  {
    _dofs.prereq_ids[i] = sheaf::invalid_pod_index();
  }

  _storage_map.reserve(NAMESPACE_SCHEMA_DOF_CT);
  for(pod_index_type i = 0; i < NAMESPACE_SCHEMA_DOF_CT; ++i)
  {
    _storage_map[i] = i;
  }

  // Postconditions:

  ensure(!is_initialized());
  ensure(host() == 0);

  ensure(!index().is_valid());

  ensure(is_table_dof_map() == false);
  ensure(dof_ct() == NAMESPACE_SCHEMA_DOF_CT);
  ensure(ref_ct() == 0);
  //ensure(client_id_space() != 0);
  ensure(poset_pointer() == 0);
  ensure(poset_type_id() == NOT_A_POSET_TYPE);
  ensure(poset_class() == 0);

  ensure_for_all(i, 1, PREREQ_IDS_UB, !(is_valid(poset_prereq_id(i))));
}


///
sheaf::namespace_poset_dof_map*
sheaf::namespace_poset_dof_map::
clone() const
{
  namespace_poset_dof_map* result;

  // Preconditions:


  // Body:

  result = new namespace_poset_dof_map();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(namespace_poset_dof_map()));

  // Exit:

  return result;
}



///
sheaf::namespace_poset_dof_map::
namespace_poset_dof_map(const namespace_poset_dof_map& xother)
    :poset_dof_map(xother)
{
  // Preconditions:

  // Body:

  _dofs = xother._dofs;
  _storage_map = xother._storage_map;
  
  // Postconditions:

  /// @todo finish postconditions

}

///
sheaf::namespace_poset_dof_map*
sheaf::namespace_poset_dof_map::
copy() const
{
  namespace_poset_dof_map* result;

  // Preconditions:


  // Body:

  result = new namespace_poset_dof_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(namespace_poset_dof_map(*this)));

  // Exit:

  return result;
}


///
sheaf::namespace_poset_dof_map&
sheaf::namespace_poset_dof_map::
operator=(const namespace_poset_dof_map& xother)
{
  // Preconditions:

  require(xother.is_initialized());

  // Body:

  poset_dof_map::operator=(xother);

  _dofs = xother._dofs;

  // Postconditions:

  // Exit

  return *this;
}


///
sheaf::namespace_poset_dof_map::
~namespace_poset_dof_map()
{
  // Preconditions:

  // Body:

  // Postconditions:

}


///
bool
sheaf::namespace_poset_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && poset_dof_map::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    // The following is not true when reading the restricted tuples from a file.
    // result = result && (dof_ct() == namespace_poset_schema::DOF_CT);

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// OTHER CONSTRUCTORS

///
sheaf::namespace_poset_dof_map::
namespace_poset_dof_map(const namespace_poset* xhost)
    : poset_dof_map(xhost, false)
{

  // Preconditions:

  // Body:

  // Namespace_poset_dof_map features:

  _dofs.pointer = 0;
  _dofs.type_id = NOT_A_POSET_TYPE;
  _dofs.class_name = 0;

  for(int i=0; i<PREREQ_IDS_UB; ++i)
  {
    _dofs.prereq_ids[i] = sheaf::invalid_pod_index();
  }

  _storage_map.reserve(NAMESPACE_SCHEMA_DOF_CT);
  for(pod_index_type i = 0; i < NAMESPACE_SCHEMA_DOF_CT; ++i)
  {
    _storage_map[i] = i;
  }

  // Postconditions:

  ensure(host() == xhost);

  ensure(!index().is_valid());

  ensure(dof_ct() == NAMESPACE_SCHEMA_DOF_CT);
  ensure(ref_ct() == 0);
  ensure(client_id_space().is_attached());
  ensure(poset_pointer() == 0);
  ensure(poset_type_id() == NOT_A_POSET_TYPE);
  ensure(poset_class() == 0);

  ensure_for_all(i, 1, PREREQ_IDS_UB, !(is_valid(poset_prereq_id(i))));

  // Exit:

  return;
}

// MAP INTERFACE

// ===========================================================
//  NEW DOF ACCESS FACET
// ===========================================================

///
void
sheaf::namespace_poset_dof_map::
get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(unexecutable("xdof must be aligned for the given data type"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));

  // Body:

  // Map from the schema id to the storage id.

  pod_index_type lstorage_id = _storage_map[xdof_id];

  switch (lstorage_id)
  {
  case 0: // pointer dof is primitive type void*
    *reinterpret_cast<poset_state_handle**>(xdof) = _dofs.pointer;
    break;
  case 1: // type_id dof is primitive type int
    *reinterpret_cast<int*>(xdof) = _dofs.type_id;
    break;
  case 2: // class dof is primitive type char*
    *reinterpret_cast<const char**>(xdof) = _dofs.class_name;
    break;
  case 3: // prereq_ids[0] is primitive type int
    *reinterpret_cast<int*>(xdof) = _dofs.prereq_ids[0];
    break;
  case 4: // prereq_ids[1] is primitive type int
    *reinterpret_cast<int*>(xdof) = _dofs.prereq_ids[1];
    break;
  case 5: // prereq_ids[2] is primitive type int
    *reinterpret_cast<int*>(xdof) = _dofs.prereq_ids[2];
    break;
  case 6: // prereq_ids[3] is primitive type int
    *reinterpret_cast<int*>(xdof) = _dofs.prereq_ids[3];
    break;
  case 7: // prereq_ids[4] is primitive type int
    *reinterpret_cast<int*>(xdof) = _dofs.prereq_ids[4];
    break;
  default:
    post_fatal_error_message("invalid dof id in call to namespace_poset_dof_map::get_dof");
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::namespace_poset_dof_map::
put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(unexecutable("xdof must be aligned for the given data type"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));

  // Body:

  // Map from the schema id to the storage id.

  pod_index_type lstorage_id = _storage_map[xdof_id];

  /// @issue xdof should be const but the compiler does not like the reinterpret_cast to
  ///        const poset_state_handle** and const char**

  switch (lstorage_id)
  {
    case 0: // pointer dof is primitive type void*
      _dofs.pointer = *reinterpret_cast<poset_state_handle**>(const_cast<void*>(xdof));
      break;
    case 1: // type_id dof is primitive type int
      _dofs.type_id = *reinterpret_cast<int*>(const_cast<void*>(xdof));
      break;
    case 2: // class dof is primitive type char*
      _dofs.class_name = *reinterpret_cast<char**>(const_cast<void*>(xdof));
      break;
    case 3: // prereq_ids[0] is primitive type int
      _dofs.prereq_ids[0] = *reinterpret_cast<int*>(const_cast<void*>(xdof));
      break;
    case 4: // prereq_ids[1] is primitive type int
      _dofs.prereq_ids[1] = *reinterpret_cast<int*>(const_cast<void*>(xdof));
      break;
    case 5: // prereq_ids[2] is primitive type int
      _dofs.prereq_ids[2] = *reinterpret_cast<int*>(const_cast<void*>(xdof));
      break;
    case 6: // prereq_ids[3] is primitive type int
      _dofs.prereq_ids[3] = *reinterpret_cast<int*>(const_cast<void*>(xdof));
      break;
    case 7: // prereq_ids[4] is primitive type int
      _dofs.prereq_ids[4] = *reinterpret_cast<int*>(const_cast<void*>(xdof));
      break;
    default:
      post_fatal_error_message("invalid dof id in call to namespace_poset_dof_map::put_dof");
  }

  // Postconditions:

  // Exit

  return;
}

// ===========================================================
//  END NEW DOF ACCESS FACET
// ===========================================================

///
void*
sheaf::namespace_poset_dof_map::
dof_tuple()
{
  void* result;

  // Preconditions:

  // Body:

  result = &_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

///
const void*
sheaf::namespace_poset_dof_map::
dof_tuple() const
{
  const void* result;

  // Preconditions:

  // Body:

  result = &_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

///
void
sheaf::namespace_poset_dof_map::
get_dof_tuple(void* xbuf, size_t xbuflen) const
{
  // Preconditions:

  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of size xbuflen));
  require(xbuflen >= sizeof(void*));

  // Body:

  *reinterpret_cast<dof_struct*>(xbuf) = _dofs;

  // Postconditions:

  ensure(unexecutable(dof tuple copied to xbuf));

  // Exit

  return;
}


///
void
sheaf::namespace_poset_dof_map::
put_dof_tuple(const void* xbuf, size_t xbuflen)
{
  // Preconditions:

  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of size xbuflen));
  require(xbuflen >= sizeof(void*));

  // Body:

  _dofs = *reinterpret_cast<const dof_struct*>(xbuf);

  // Postconditions:

  ensure(unexecutable(xbuf copied to dof tuple));

  // Exit

  return;
}


///
sheaf::poset_state_handle*
sheaf::namespace_poset_dof_map::
poset_pointer() const
{
  poset_state_handle* result;

  // Preconditions:

  // Body:

  result = _dofs.pointer;

  // Postconditions:

  // Exit

  return result;
}


///
sheaf::poset_type
sheaf::namespace_poset_dof_map::
poset_type_id() const
{
  poset_type result;

  // Preconditions:

  // Body:

  result = sheaf::poset_type_id(_dofs.type_id);

  // Postconditions:

  // Exit

  return result;
}


///
const char*
sheaf::namespace_poset_dof_map::
poset_class() const
{
  const char* result;

  // Preconditions:

  // Body:

  result = _dofs.class_name;

  // Postconditions:

  // Exit

  return result;
}

///
int
sheaf::namespace_poset_dof_map::
poset_prereq_id(int xi) const
{
  int result;

  // Preconditions:

  require((0 <= xi) && (xi < PREREQ_IDS_UB));

  // Body:

  if(_dofs.prereq_ids[xi] == sheaf::invalid_pod_index())
  {
    result = invalid_pod_index();
  }
  else
  {
    result = _dofs.prereq_ids[xi];
  }

  // Postconditions:

  // Exit:

  return result;
}



// PROTECTED MEMBER FUNCTIONS

 
///
void
sheaf::namespace_poset_dof_map::
extend_to_top()
{
  // Preconditions:


  // Body:

  _schema->attach_to_state(TOP_INDEX);

  _dof_ct       = _schema->row_dof_ct();
  _dof_tuple_ub = _schema->row_dof_tuple_ub();

  _storage_map.clear();
  for(pod_index_type i = 0; i < NAMESPACE_SCHEMA_DOF_CT; ++i)
  {
    _storage_map[i] = i;
  }

  // Postconditions:


  // Exit:

  return;
}

///
void
sheaf::namespace_poset_dof_map::
put_poset_pointer(const poset_state_handle* xposet)
{
  // Preconditions:

  // Body:

  _dofs.pointer = const_cast<poset_state_handle*>(xposet);

  // Postconditions:

  ensure(poset_pointer() == xposet);

  // Exit

  return;
}


///
void
sheaf::namespace_poset_dof_map::
put_poset_type_id(poset_type xtype_id)
{
  // Preconditions:

  // Body:

  _dofs.type_id = xtype_id;

  // Postconditions:

  ensure(poset_type_id() == xtype_id);

  // Exit

  return;
}

///
void
sheaf::namespace_poset_dof_map::
put_poset_class(const char* xclass)
{
  // Preconditions:

  // Body:

  _dofs.class_name = xclass;

  // Postconditions:

  ensure(poset_class() == xclass);

  // Exit

  return;
}

///
void
sheaf::namespace_poset_dof_map::
put_poset_prereq_id(int xi, int xid)
{
  // Preconditions:

  require((0 <= xi) && (xi < PREREQ_IDS_UB));


  // Body:

  if(is_valid(xid))
  {
    _dofs.prereq_ids[xi] = xid;
  }
  else
  {
    _dofs.prereq_ids[xi] = sheaf::invalid_pod_index();
  }

  // Postconditions:

  ensure(poset_prereq_id(xi) == xid);

  // Exit:

  return;
}

///
void
sheaf::namespace_poset_dof_map::
allocate_dofs()
{
  // Preconditions:


  // Body:

  _dofs.pointer = 0;
  _dofs.type_id = NOT_A_POSET_TYPE;
  _dofs.class_name = 0;

  _storage_map.clear();

  const index_space_handle& lstorage_id_space =
    _host->top().schema().dof_id_space(_is_table_dof_map);

  index_space_iterator& litr =
    schema().dof_id_space(_is_table_dof_map).get_iterator();

  while(!litr.is_done())
  {
    pod_index_type lstorage_id =
      lstorage_id_space.pod(litr.hub_pod());

    _storage_map[litr.pod()] = lstorage_id;

    litr.next();
  }

  schema().dof_id_space(_is_table_dof_map).release_iterator(litr);

  // Postconditions:


  // Exit:

  return;
}



// PRIVATE MEMBERS

///
bool
sheaf::namespace_poset_dof_map::
make_prototype()
{
  // Preconditions:


  // Body:

  dof_tuple_type ltype = NAMESPACE_POSET_DOF_TUPLE_ID;

  poset_dof_map* lproto = new namespace_poset_dof_map;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:


  // Exit:

  return true;
}

