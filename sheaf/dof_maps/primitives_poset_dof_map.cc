
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

// Implementation for class primitives_poset_dof_map

#include "ComLimitPoint/sheaf/primitives_poset_dof_map.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/dof_map_factory.h"
#include "ComLimitPoint/sheaf/primitive_traits.h"
#include "ComLimitPoint/sheaf/primitives_poset.h"
#include "ComLimitPoint/sheaf/primitives_poset_schema.h"
#include "std_string.h"

using namespace std;

// PUBLIC MEMBER FUNCTIONS

const std::string&
sheaf::primitives_poset_dof_map::
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

const std::string&
sheaf::primitives_poset_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("primitives_poset_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "primitives_poset_dof_map");

  // Exit:

  return result;
}

// CANONICAL MEMBERS

sheaf::primitives_poset_dof_map::
primitives_poset_dof_map()
{

  // Preconditions:


  // Body:

  _dof_ct = PRIMITIVES_SCHEMA_DOF_CT;
  _dof_tuple_ub = sizeof(primitive_descriptor);
  _dofs.size = 0;
  _dofs.alignment = 0;
  _dofs.index = NOT_A_PRIMITIVE_TYPE;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());
  ensure(host() == 0);

  ensure(!index().is_valid());

  ensure(!is_table_dof_map());
  ensure(dof_ct() == PRIMITIVES_SCHEMA_DOF_CT);
  ensure(dof_tuple_ub() == sizeof(primitive_descriptor));
  ensure(ref_ct() == 0);

}

sheaf::primitives_poset_dof_map*
sheaf::primitives_poset_dof_map::
clone() const
{
  primitives_poset_dof_map* result;

  // Preconditions:


  // Body:

  result = new primitives_poset_dof_map();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(primitives_poset_dof_map()));

  // Exit:

  return result;
}



sheaf::primitives_poset_dof_map::
primitives_poset_dof_map(const primitives_poset_dof_map& xother)
    :poset_dof_map()
{
  // Preconditions:

  require(xother.is_initialized());

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(host() == xother.host());
  ensure(index() == xother.index());
  ensure(schema().is_same_state(&xother.schema()));
  ensure(is_table_dof_map() == xother.is_table_dof_map());
  ensure(dof_ct() == xother.dof_ct());
  ensure(dof_tuple_ub() == xother.dof_tuple_ub());
  ensure(ref_ct() == 0);

}

sheaf::primitives_poset_dof_map*
sheaf::primitives_poset_dof_map::
copy() const
{
  primitives_poset_dof_map* result;

  // Preconditions:


  // Body:

  result = new primitives_poset_dof_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(primitives_poset_dof_map(*this)));

  // Exit:

  return result;
}


sheaf::primitives_poset_dof_map&
sheaf::primitives_poset_dof_map::
operator=(const primitives_poset_dof_map& xother)
{
  // Preconditions:

  // Body:

  require(xother.is_initialized());

  // Body:

  // Can't call poset_dof_map::operator= because it
  // deletes the schema then clones xother schema.
  // This class just keeps a pointer to the schema
  // handle in the poset.

  _host             = xother._host;
  _index            = xother._index;
  _schema           = xother._schema;
  _is_table_dof_map = xother._is_table_dof_map;
  _dof_ct           = xother._dof_ct;
  _dof_tuple_ub     = xother._dof_tuple_ub;
  _ref_ct           = 0;

  _dofs             = xother._dofs;

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(host() == xother.host());
  ensure(index() == xother.index());
  ensure(schema().is_same_state(&xother.schema()));
  ensure(is_table_dof_map() == xother.is_table_dof_map());
  ensure(dof_ct() == xother.dof_ct());
  ensure(dof_tuple_ub() == xother.dof_tuple_ub());
  ensure(ref_ct() == 0);


  // Exit

  return *this;
}


sheaf::primitives_poset_dof_map::
~primitives_poset_dof_map()
{
  // Preconditions:

  // Body:

  // The poset_dof_map dtor will delete the schema
  // if it is not null. _schema in this class is a
  // pointer to the schema in the host state, so we can't
  // let it be deleted.

  _schema = 0;

  // Postconditions:

}

bool
sheaf::primitives_poset_dof_map::
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

    result = result && (is_initialized() ? &(schema()) == &(host()->state_obj()->table()->schema()) : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// OTHER CONSTRUCTORS

sheaf::primitives_poset_dof_map::
primitives_poset_dof_map(const poset_state_handle* xhost, int xprimitive_index)
    : poset_dof_map()
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(is_primitive_index(xprimitive_index));

  // Body:

  // The bootstrap problem: the schema for this is the primitives_poset_schema
  // and creating it requires creating these dof maps first.
  //
  // When this constructor is called, the schema handle in primitives_poset_schema
  // has been created but not attached. So we can save a pointer to it, which will
  // be a valid schema handle once the host constructor is finished.

  // Note: must call default poset_dof_map constructor above,
  // because poset_dof_map::poset_dof_map(schema_poset_member* xschema, ...)
  // uses xschema to get _dof_ct and _dof_tuple_ub.

  // Initialize poset_dof_map members:

  _host = const_cast<poset_state_handle*>(xhost);

  _index.invalidate();
  _index.put_scope(_host->dof_tuple_hub_id_space(false));

  // Save a pointer to the host schema. Make sure to get
  // the one in the state, in case the one in the handle xhost
  // changes. Have to be careful about deleting this, see the dtor.

  _schema = &(xhost->state_obj()->table()->schema());

  _is_table_dof_map = false;

  // Initialize the schema properties without reference to the schema.

  _dof_ct = PRIMITIVES_SCHEMA_DOF_CT;
  _dof_tuple_ub = sizeof(primitive_descriptor);

  _ref_ct = 0;

  // Initialize dofs to the specified primitive dofs

  _dofs = primitive_attributes::descriptor(xprimitive_index);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(host() == xhost);
  ensure(!index().is_valid());
  ensure(index().same_scope(host()->dof_tuple_hub_id_space(false)));
  ensure(!is_table_dof_map());
  ensure(dof_ct() == PRIMITIVES_SCHEMA_DOF_CT);
  ensure(dof_tuple_ub() == sizeof(primitive_descriptor));

  // Exit:

  return;
}


void
sheaf::primitives_poset_dof_map::
init_row_dof_map(const poset_state_handle* xhost,
                 pod_index_type xschema_mbr_id,
                 int xschema_version)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->schema().index() == xschema_mbr_id);
  require(xhost->schema().host()->version() == xschema_version);

  // Body:

  // Initialize poset_dof_map members:

  _host = const_cast<poset_state_handle*>(xhost);

  _index.invalidate();
  _index.put_scope(_host->dof_tuple_hub_id_space(false));

  /// @hack schema id and version ignored for this class.

  // Save a pointer to the host schema. Make sure to get
  // the one in the state, in case the one in the handle xhost
  // changes. Have to be careful about deleting this, see the dtor.

  _schema = &(xhost->state_obj()->table()->schema());

  _is_table_dof_map = false;

  // Initialize the schema properties without reference to the schema.

  _dof_ct = PRIMITIVES_SCHEMA_DOF_CT;
  _dof_tuple_ub = sizeof(primitive_descriptor);

  _ref_ct = 0;

  // Don't need to allocate _dofs; it's already allocated.

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(host() == xhost);
  ensure(!index().is_valid());
  ensure(index().same_scope(host()->dof_tuple_hub_id_space(false)));
  ensure(!is_table_dof_map());
  ensure(dof_ct() == PRIMITIVES_SCHEMA_DOF_CT);
  ensure(dof_tuple_ub() == sizeof(primitive_descriptor));

  // Exit:

  return;
}



// MAP INTERFACE

// ===========================================================
//  NEW DOF ACCESS FACET
// ===========================================================

void
sheaf::primitives_poset_dof_map::
get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_id == 0 ? xdof_size >= primitive_traits<size_type>::size() : true);
  require(xdof_id == 1 ? xdof_size >= primitive_traits<size_type>::size() : true);
  require(xdof_id == 2 ? xdof_size >= primitive_traits<pod_index_type>::size() : true);

  // Body:

  switch (xdof_id)
  {
  case 0: // size dof is primitive type size_type
    memcpy(xdof, &(_dofs.size), primitive_traits<size_type>::size());
    break;
  case 1: // alignment dof is primitive type size_type
    memcpy(xdof, &(_dofs.alignment), primitive_traits<size_type>::size());
    break;
  case 2: // index dof is primtive type pod_index_type
    memcpy(xdof, &(_dofs.index), primitive_traits<pod_index_type>::size());
    break;
  default:
    post_fatal_error_message("invalid xdof_id in call to primitives_poset_dof_map::get_dof");
  }

  // Postconditions:

  ensure(unexecutable(xdof holds dofs referred to by xdof_id and xis_poset_id));

  // Exit

  return;
}

void
sheaf::primitives_poset_dof_map::
put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_id == 0 ? xdof_size >= primitive_traits<size_type>::size() : true);
  require(xdof_id == 1 ? xdof_size >= primitive_traits<size_type>::size() : true);
  require(xdof_id == 2 ? xdof_size >= primitive_traits<pod_index_type>::size() : true);
  

  // Body:

  switch (xdof_id)
  {
  case 0: // size dof is primitive type size_type
    memcpy(&(_dofs.size), xdof, primitive_traits<size_type>::size());
    break;
  case 1: // alignment dof is primitive type size_type
    memcpy(&(_dofs.alignment), xdof, primitive_traits<size_type>::size());
    break;
  case 2: // index dof is primtive type pod_index_type
    memcpy(&(_dofs.index), xdof, primitive_traits<pod_index_type>::size());
    break;
  default:
    post_fatal_error_message("invalid xdof_id in call to primitives_poset_dof_map::put_dof");
  }

  // Postconditions:

  ensure(unexecutable(_dofs holds dofs referred to by xdof_id and xis_poset_id));

  // Exit

  return;
}
 
// ===========================================================
//  END NEW DOF ACCESS FACET
// ===========================================================

void*
sheaf::primitives_poset_dof_map::
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

const void*
sheaf::primitives_poset_dof_map::
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

void
sheaf::primitives_poset_dof_map::
get_dof_tuple(void* xbuf, size_t xbuflen) const
{
  // Preconditions:

  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of size xbuflen));
  require(xbuflen >= sizeof(primitive_descriptor));
  require(unexecutable("xbuf id properly aligned for primitive_descriptor"));

  // Body:

  *static_cast<primitive_descriptor*>(xbuf) = _dofs;

  // Postconditions:

  ensure(unexecutable(dof tuple copied to xbuf));

  // Exit

  return;
}


void
sheaf::primitives_poset_dof_map::
put_dof_tuple(const void* xbuf, size_t xbuflen)
{
  // Preconditions:

  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of size xbuflen));
  require(xbuflen >= sizeof(primitive_descriptor));
  require(unexecutable("xbuf id properly aligned for primitive_descriptor"));

  // Body:

  _dofs = *static_cast<const primitive_descriptor*>(xbuf);

  // Postconditions:

  ensure(unexecutable(xbuf copied to dof tuple));

  // Exit

  return;
}

size_t
sheaf::primitives_poset_dof_map::
size() const
{
  return _dofs.size;
}

void
sheaf::primitives_poset_dof_map::
put_size(size_t xsize)
{
  // Preconditions:

  // Body:

  _dofs.size = xsize;

  // Postconditions:

  ensure(size() == xsize);

  // Exit:

  return;
}

size_t
sheaf::primitives_poset_dof_map::
alignment() const
{
  return _dofs.alignment;
}

void
sheaf::primitives_poset_dof_map::
put_alignment(size_t xalignment)
{
  // Preconditions:

  // Body:

  _dofs.alignment = xalignment;

  // Postconditions:

  ensure(alignment() == xalignment);

  // Exit:

  return;
}

sheaf::primitive_type
sheaf::primitives_poset_dof_map::
type() const
{
  return primitive_attributes::id(_dofs.index);
}

void
sheaf::primitives_poset_dof_map::
put_type(int xtype)
{
  // Preconditions:

  // Body:

  _dofs.index = xtype;

  // Postconditions:

  ensure(type() == xtype);

  // Exit:

  return;
}

// PRIVATE STATIC MEMBERS

void
sheaf::primitives_poset_dof_map::
put_host(const poset_state_handle* xhost)
{
  // Preconditions:

  // Redefined in this class to relax preconditions
  // which can not be satisfied in the bootstrap.

  require(xhost->state_is_read_accessible());

  // Body:

  _host = const_cast<poset_state_handle*>(xhost);

  // Schema of this must be same as schema of
  // host to prevent dangling pointer if other
  // schema handle goes away.

  _schema = &(xhost->state_obj()->table()->schema());

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);

  // Exit

  return;
}

bool
sheaf::primitives_poset_dof_map::
make_prototype()
{
  // Preconditions:


  // Body:

  dof_tuple_type ltype = PRIMITIVES_POSET_DOF_TUPLE_ID;

  poset_dof_map* lproto = new primitives_poset_dof_map;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:


  // Exit:

  return true;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

