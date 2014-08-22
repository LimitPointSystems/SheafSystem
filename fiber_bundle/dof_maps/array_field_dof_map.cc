
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

// Implementation for class array_field_dof_map

#include "ComLimitPoint/fiber_bundle/array_field_dof_map.h"
#include "ComLimitPoint/sheaf/assert_contract.h"

#include "ComLimitPoint/fiber_bundle/dof_map_factory.h"
#include "ComLimitPoint/fiber_bundle/discretization_iterator.h"
#include "ComLimitPoint/fiber_bundle/sec_rep_space.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// PUBLIC MEMBER FUNCTIONS

///
const std::string&
fiber_bundle::array_field_dof_map::
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
fiber_bundle::array_field_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("array_field_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "array_field_dof_map");

  // Exit:

  return result;
}

// ===========================================================
// CANONICAL FACET
// ===========================================================

///
fiber_bundle::array_field_dof_map::
array_field_dof_map()
    : field_dof_map()
{

  // Preconditions:


  // Body:

  /// @error doesn't initialize _schema.

  _disc_ct = 0;
  _fiber_ct = 0;
  _local_ct = 0;
  _fiber_tuple_size = 0;
  _dofs = 0;
  _this_owns_dofs = false;

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
fiber_bundle::array_field_dof_map*
fiber_bundle::array_field_dof_map::
clone() const
{
  array_field_dof_map* result;

  // Preconditions:


  // Body:

  result = new array_field_dof_map();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(array_field_dof_map()));

  // Exit:

  return result;
}



///
fiber_bundle::array_field_dof_map::
array_field_dof_map(const array_field_dof_map& xother)
    : field_dof_map(xother)
{

  // Preconditions:


  // Body:

  _disc_ct = 0;
  _fiber_ct = 0;
  _local_ct = 0;
  _fiber_tuple_size = 0;
  _dofs = 0;
  _this_owns_dofs = false;

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
fiber_bundle::array_field_dof_map*
fiber_bundle::array_field_dof_map::
copy() const
{
  array_field_dof_map* result;

  // Preconditions:


  // Body:

  result = new array_field_dof_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(array_field_dof_map(*this)));

  // Exit:

  return result;
}

///
fiber_bundle::array_field_dof_map&
fiber_bundle::array_field_dof_map::
operator=(const array_field_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  field_dof_map::operator=(xother);

  if(_dofs != 0)
    delete[] _dofs;

  if(xother._dofs != 0)
  {
    // Use same cts and offsets as xother

    _disc_ct = xother._disc_ct;
    _fiber_ct = xother._fiber_ct;
    _local_ct = xother._local_ct;
    _fiber_tuple_size = xother._fiber_tuple_size;

    // Allocate and copy the dof storage

    _this_owns_dofs = xother._this_owns_dofs;

    if(_this_owns_dofs)
    {
      /// @error isn't dof_tuyple_ub the byte count?
      _dofs = new double[dof_tuple_ub()];
      memcpy(_dofs, xother._dofs, dof_tuple_ub());
    }
    else
    {
      _dofs = xother._dofs;
    }
  }
  else
  {
    _disc_ct = 0;
    _fiber_ct = 0;
    _local_ct = 0;
    _fiber_tuple_size = 0;
    _dofs = 0;
    _this_owns_dofs = false;
  }

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}


///
fiber_bundle::array_field_dof_map::
~array_field_dof_map()
{

  // Preconditions:


  // Body:

  if(_this_owns_dofs)
    delete[] _dofs;


  // Postconditions:

}


///
bool
fiber_bundle::array_field_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && (_fiber_tuple_size == _fiber_ct*_local_ct);

  /// @todo finish array_field_dof_map::invariant() const

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// MAP FACET
// ===========================================================

///
fiber_bundle::array_field_dof_map::
array_field_dof_map(const sec_rep_space* xhost, void* xdofs, size_t xdofs_ub)
    : field_dof_map(xhost)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xdofs != 0 ? xdofs_ub >= xhost->schema().row_dof_tuple_ub(): true);
  require(unexecutable("if xdofs != 0 it points to buffer of length xdofs_ub"));

  // Body:

  // Initialize counts


  _disc_ct = xhost->discretization().member_ct();
  _fiber_ct = xhost->df();
  _local_ct = xhost->multiplicity();
  _fiber_tuple_size = _fiber_ct*_local_ct;


  // Initialize dof storage

  _dofs = static_cast<double*>(xdofs);

  if(_dofs == 0)
  {
    /// @error isn't dof_tuple_ub the byte count?
    _dofs = new double[dof_tuple_ub()];
    _this_owns_dofs = true;
  }
  else
  {
    _this_owns_dofs = false;
  }

  // Postconditions:

  ensure(invariant());
  ensure(_disc_ct > 0);
  ensure(_fiber_ct > 0);
  ensure(_local_ct > 0);
  ensure(dof_ct() == _disc_ct*_fiber_ct*_local_ct);
  ensure(dof_tuple_ub() <= xhost->schema().row_dof_tuple_ub());
  ensure(_dofs != 0);
  ensure(xdofs != 0 ? _dofs == xdofs : true);

}

 

// ===========================================================
//  NEW DOF ACCESS FACET
// ===========================================================
 
///
void
fiber_bundle::array_field_dof_map::
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
fiber_bundle::array_field_dof_map::
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
fiber_bundle::array_field_dof_map::
get_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains_range_id(xdisc_id));
  require(schema().fiber_id_space().contains_range_id(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id));
  
  
  // Body:

  memcpy(xdof, dof_ptr(xdisc_id, xfiber_dof_id), sizeof(sec_vd_dof_type));
  
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_field_dof_map::
put_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains_range_id(xdisc_id));
  require(schema().fiber_id_space().contains_range_id(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id));
  
  
  // Body:

  memcpy(dof_ptr(xdisc_id, xfiber_dof_id), xdof, sizeof(sec_vd_dof_type));
  
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_field_dof_map::
get_fiber(pod_index_type xdisc_id, void* xfiber, size_type xfiber_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains_range_id(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  
  // Body:

  memcpy(xfiber, dof_ptr(xdisc_id, 0), schema().fiber_size());
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_field_dof_map::
put_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains_range_id(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  
  // Body:

  memcpy(dof_ptr(xdisc_id, 0), xfiber, schema().fiber_size());
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::array_field_dof_map::
get_component(pod_index_type xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_id_space().contains_range_id(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));
  
  
  // Body:

  char* lcomponent = reinterpret_cast<char*>(xcomponent);
  char* ldof = dof_ptr(0, xfiber_dof_id);
  size_type ldof_size = schema().size(0, xfiber_dof_id);
  size_type lfiber_size = schema().fiber_size();
  
  for(pod_index_type i=0; i<_discretization_ct; ++i)
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
fiber_bundle::array_field_dof_map::
put_component(pod_index_type xfiber_dof_id, const void* xcomponent, size_type xcomponent_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_id_space().contains_range_id(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));
  
  
  // Body:

  char* lcomponent = reinterpret_cast<char*>(xcomponent);
  char* ldof = dof_ptr(0, xfiber_dof_id);
  size_type ldof_size = schema().size(0, xfiber_dof_id);
  size_type lfiber_size = schema().fiber_size();
  
  for(pod_index_type i=0; i<_discretization_ct; ++i)
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
void
fiber_bundle::array_field_dof_map::
get_dof(const scoped_index& xid, bool xis_poset_id, void* xbuf, size_t xbuf_len) const
{
  // Preconditions:

  require(xis_poset_id ? schema().contains_row_dof(xid) : true);
  require(xbuf != 0);
  require(unexecutable("xbuf_len is large enough to contain the requested dof"));
  require(unexecutable("xbuf is properly aligned for the type of dof"));

  // Body:

  array_field_dof_map* cthis = const_cast<array_field_dof_map*>(this);
  cthis->copy_dof(xid, xis_poset_id, xbuf, xbuf_len, true);

  // Postconditions:

  // Exit

  return;
}


///
void
fiber_bundle::array_field_dof_map::
put_dof(const scoped_index& xid, bool xis_poset_id, const void* xbuf, size_t xbuf_len)
{
  // Preconditions:

  require(xis_poset_id ? schema().contains_row_dof(xid) : true);

  require(xbuf != 0);
  require(unexecutable("xbuf_len is large enough to contain the requested dof"));
  require(unexecutable("xbuf is properly aligned for the type of dof"));

  /// @todo make the precondition below executable.
  require(unexecutable("xbuf must be aligned for the given data type"));

  // Body:

  copy_dof(xid, xis_poset_id, const_cast<void*>(xbuf), xbuf_len, false);

  // Postconditions:

  ensure(unexecutable(internal storage holds dof referred to by xid and xis_poset_id));

  // Exit

  return;
}



///
void
fiber_bundle::array_field_dof_map::
get_dofs(const client_index* xclient_ids, int xclient_id_ct, void* xbuf, size_t xbuf_len) const
{
  // Preconditions:

  require(xclient_ids != 0);
  require(xclient_id_ct > 0);
  require(unexecutable(xclient_ids points to buffer of length xclient_id_ct));
  require(unexecutable(xclient_ids are valid client ids));
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable(xbuf_len is large enough to hold the dofs referred to by xclient_ids));
  /// @todo make the precondition below executable.
  require(unexecutable("xbuf must be aligned for all data types"));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(unexecutable(xbuf holds dofs referred to by xclient_ids));

  // Exit

  return;
}


///
void
fiber_bundle::array_field_dof_map::
put_dofs(const client_index* xclient_ids, int xclient_id_ct, const void* xbuf, size_t xbuf_len)
{
  // Preconditions:

  require(xclient_ids != 0);
  require(xclient_id_ct > 0);
  require(unexecutable(xclient_ids points to buffer of length xclient_id_ct));
  require(unexecutable(xclient_ids are valid client ids));
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable(xbuf_len is large enough to hold the dofs referred to by xclient_ids));
  /// @todo make the precondition below executable.
  require(unexecutable("xbuf must be aligned for all data types"));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(unexecutable(internal storage holds dofs referred to by xclient_ids));

  // Exit

  return;
}

 

///
void
fiber_bundle::array_field_dof_map::
get_dof(const scoped_index& xbase_id,
	const scoped_index& xfiber_id,
	const scoped_index& xmult_id,
        bool xis_poset_id, void* xbuf, size_t xbuf_len) const
{
  // Preconditions:

  require(unexecutable(xbase_id is a valid client id));
  require(unexecutable(xfiber_id is a valid client id));
  require(unexecutable(0 <= xmult_id && xmult_id < multiplicity));
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable(xbuf_len is large enough to hold the dofs referred to by client ids));

  // Body:

  array_field_dof_map* cthis = const_cast<array_field_dof_map*>(this);
  cthis->copy_dof(xbase_id, xfiber_id, xmult_id, xis_poset_id, xbuf, xbuf_len, true);

  // Postconditions:

  ensure(unexecutable(xbuf holds dof referred to by xids));

  // Exit

  return;
}


///
void
fiber_bundle::array_field_dof_map::
put_dof(const scoped_index& xbase_id,
	const scoped_index& xfiber_id,
	const scoped_index& xmult_id,
        bool xis_poset_id, const void* xbuf, size_t xbuf_len)
{
  // Preconditions:

  require(unexecutable(xbase_id is a valid client id));
  require(unexecutable(xfiber_id is a valid client id));
  require(unexecutable(0 <= xmult_id && xmult_id < multiplicity));
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable(xbuf_len is large enough to hold the dofs referred to by client ids));

  // Body:

  copy_dof(xbase_id, xfiber_id, xmult_id, xis_poset_id, const_cast<void*>(xbuf), xbuf_len, false);

  // Postconditions:

  ensure(unexecutable(internal storage holds dof referred to by xids));

  // Exit

  return;
}

///
void
fiber_bundle::array_field_dof_map::
get_dofs(const client_index* xclient_base_ids, int xclient_base_id_ct,
         const client_index* xclient_fiber_ids, int xclient_fiber_id_ct,
         void* xbuf, size_t xbuf_len) const
{
  // Preconditions:

  require(xclient_base_ids != 0);
  require(xclient_base_id_ct > 0);
  require(unexecutable(xclient_base_ids points to buffer of length xclient_base_id_ct));
  require(unexecutable(xclient_base_ids are valid client ids));
  require(xclient_fiber_ids != 0);
  require(xclient_fiber_id_ct > 0);
  require(unexecutable(xclient_fiber_ids points to buffer of length xclient_fiber_id_ct));
  require(unexecutable(xclient_fiber_ids are valid client ids));
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable(xbuf_len is large enough to hold the dofs referred to by client ids));

  // Body:

  array_field_dof_map* cthis = const_cast<array_field_dof_map*>(this);
  cthis->copy_dofs(xclient_base_ids, xclient_base_id_ct, xclient_fiber_ids,
            xclient_fiber_id_ct, xbuf, xbuf_len, true);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(xbuf holds dofs referred to by xclient_ids));

  // Exit

  return;
}


///
void
fiber_bundle::array_field_dof_map::
put_dofs(const client_index* xclient_base_ids, int xclient_base_id_ct,
         const client_index* xclient_fiber_ids, int xclient_fiber_id_ct,
         const void* xbuf, size_t xbuf_len)
{
  // Preconditions:

  require(xclient_base_ids != 0);
  require(xclient_base_id_ct > 0);
  require(unexecutable(xclient_base_ids points to buffer of length xclient_base_id_ct));
  require(unexecutable(xclient_base_ids are valid client ids));
  require(xclient_fiber_ids != 0);
  require(xclient_fiber_id_ct > 0);
  require(unexecutable(xclient_fiber_ids points to buffer of length xclient_fiber_id_ct));
  require(unexecutable(xclient_fiber_ids are valid client ids));
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable(xbuf_len is large enough to hold the dofs referred to by xclient_ids));

  // Body:

  copy_dofs(xclient_base_ids, xclient_base_id_ct, xclient_fiber_ids,
            xclient_fiber_id_ct, const_cast<void*>(xbuf), xbuf_len, false);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(internal storage holds dofs referred to by xclient_ids));

  // Exit

  return;
}

///
void
fiber_bundle::array_field_dof_map::
get_discretization_dofs(const scoped_index& xdisc_id,
                        bool xis_poset_id,
                        void* xbuf,
                        size_t xbuf_len) const
{
  // Preconditions:

  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(xbuf_len >= schema().fiber_schema().row_dof_tuple_ub());
  require(xis_poset_id ? xdisc_id.in_scope() : true);

  // Body:

  scoped_index::pod_type ldisc_id;
  if(xis_poset_id)
  {
    ldisc_id  = schema().disc_seq_id_map().client_id(xdisc_id.hub_pod());
  }
  else
  {
    ldisc_id = xdisc_id;
  }


  size_t ltuple_size = schema().fiber_schema().row_dof_tuple_ub();

  char* ldof_base = reinterpret_cast<char*>(_dofs) + ldisc_id*ltuple_size;

  memcpy(xbuf, ldof_base, ltuple_size);

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::array_field_dof_map::
put_discretization_dofs(const scoped_index& xdisc_id,
                        bool xis_poset_id,
                        const void* xbuf,
                        size_t xbuf_len)
{
  // Preconditions:

  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(xbuf_len >= schema().fiber_schema().row_dof_tuple_ub());
  require(xis_poset_id ? xdisc_id.in_scope() : true);

  // Body:

  scoped_index::pod_type ldisc_id;
  if(xis_poset_id)
  {
    ldisc_id  = schema().disc_seq_id_map().client_id(xdisc_id.hub_pod());
  }
  else
  {
    ldisc_id = xdisc_id;
  }

  size_t lfiber_dof_ct = schema().fiber_schema().row_dof_ct();
  size_t ltuple_size = sizeof(double)*lfiber_dof_ct;

  size_t lindex = ldisc_id*lfiber_dof_ct;

  reserve(lindex);

  char* ldof_base = reinterpret_cast<char*>(_dofs) + lindex*sizeof(double);

  memcpy(ldof_base, xbuf, ltuple_size);

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::array_field_dof_map::
get_component_dofs(void* xbuf,
                   size_t xbuf_len,
                   const scoped_index& xcomp_id,
                   const scoped_index* xdisc_ids,
                   size_type xdisc_ids_ct) const
{
  // Preconditions:

  require(is_initialized());
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable("xbuf_len is large enough for the requested dofs"));
  require(schema().fiber_schema().contains_row_dof(xcomp_id));
  require(xdisc_ids == 0 ? xdisc_ids_ct == 0 : true);
  require_for_all(i, 0, xdisc_ids_ct, schema().discretization().contains_member(xdisc_ids[i]));

  // Body:

  copy_component_dofs(xbuf,
                      xbuf_len,
                      xcomp_id,
                      xdisc_ids,
                      xdisc_ids_ct,
                      true);

  // Postconditions:

  // Exit

  return;
}


///
void
fiber_bundle::array_field_dof_map::
put_component_dofs(const void* xbuf,
                   size_t xbuf_len,
                   const scoped_index& xcomp_id,
                   const scoped_index* xdisc_ids,
                   size_type xdisc_ids_ct)
{
  // Preconditions:

  require(is_initialized());
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable("xbuf_len is large enough for the requested dofs"));
  require(schema().fiber_schema().contains_row_dof(xcomp_id));
  require(xdisc_ids == 0 ? xdisc_ids_ct == 0 : true);
  require_for_all(i, 0, xdisc_ids_ct, schema().discretization().contains_member(xdisc_ids[i]));

  // Body:

  copy_component_dofs(const_cast<void*>(xbuf),
                      xbuf_len,
                      xcomp_id,
                      xdisc_ids,
                      xdisc_ids_ct,
                      false);

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::array_field_dof_map::
get_component_dofs(void* xbuf,
                   size_t xbuf_len,
                   const client_index& xcomp_id,
                   const id_map* xcomp_client_id_map,
                   const client_index* xdisc_ids,
                   size_type xdisc_ids_ct,
                   const id_map* xdisc_client_id_map) const
{
  // Preconditions:

  require(is_initialized());
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable("xbuf_len is large enough for the requested dofs"));
  require(xcomp_client_id_map != 0);
  require(schema().fiber_schema().contains_row_dof(scoped_index(xcomp_id, xcomp_client_id_map)));
  require(xdisc_ids == 0 ? xdisc_ids_ct == 0 : true);
  require(xdisc_ids_ct != 0 ? xdisc_client_id_map != 0 : true);
  require_for_all(i, 0, xdisc_ids_ct, schema().discretization().contains_member(scoped_index(xdisc_ids[i], xdisc_client_id_map)));


  // Body:

  copy_component_dofs(xbuf,
                      xbuf_len,
                      xcomp_id,
                      xcomp_client_id_map,
                      xdisc_ids,
                      xdisc_ids_ct,
                      xdisc_client_id_map,
                      true);

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::array_field_dof_map::
put_component_dofs(const void* xbuf,
                   size_t xbuf_len,
                   const client_index& xcomp_id,
                   const id_map* xcomp_client_id_map,
                   const client_index* xdisc_ids,
                   size_type xdisc_ids_ct,
                   const id_map* xdisc_client_id_map)
{
  // Preconditions:

  require(is_initialized());
  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(unexecutable("xbuf_len is large enough for the requested dofs"));
  require(xcomp_client_id_map != 0);
  require(schema().fiber_schema().contains_row_dof(scoped_index(xcomp_id, xcomp_client_id_map)));
  require(xdisc_ids == 0 ? xdisc_ids_ct == 0 : true);
  require(xdisc_ids_ct != 0 ? xdisc_client_id_map != 0 : true);
  require_for_all(i, 0, xdisc_ids_ct, schema().discretization().contains_member(scoped_index(xdisc_ids[i], xdisc_client_id_map)));


  // Body:

  copy_component_dofs(const_cast<void*>(xbuf),
                      xbuf_len,
                      xcomp_id,
                      xcomp_client_id_map,
                      xdisc_ids,
                      xdisc_ids_ct,
                      xdisc_client_id_map,
                      false);

  // Postconditions:

  // Exit

  return;
}

///
void*
fiber_bundle::array_field_dof_map::
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
fiber_bundle::array_field_dof_map::
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
fiber_bundle::array_field_dof_map::
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
fiber_bundle::array_field_dof_map::
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
fiber_bundle::array_field_dof_map::
allocate_dofs()
{

  // Preconditions:

  // Body:

  _local_ct = host()->multiplicity();

  // Initialize dof storage
  /// @error isn't dof_tuyple_ub the byte count?

  _dofs = new double[_dof_tuple_ub];
  _this_owns_dofs = true;


  // Postconditions:

  // Exit:

  return;
}

bool
fiber_bundle::array_field_dof_map::
_has_prototype = make_prototype();

///
bool
fiber_bundle::array_field_dof_map::
make_prototype()
{
  bool result = false;

  // Preconditions:


  // Body:

  dof_tuple_type ltype = ARRAY_FIELD_DOF_TUPLE_ID;

  poset_dof_map* lproto = new array_field_dof_map;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:


  // Exit:

  return result;
}

///
void
fiber_bundle::array_field_dof_map::
reserve(int xindex)
{

  // Preconditions:

  require(xindex >= 0);
  require(_dofs != 0);
  require(_this_owns_dofs);

  // Body:

  define_old_variable(int old_dof_tuple_ub = _dof_tuple_ub);

  if(xindex >= _dof_tuple_ub)
  {
    size_t new_ub = _dof_tuple_ub*2;
    if(new_ub <= xindex)
      new_ub = xindex + 1;

    // Allocate a new dofs array

    double* new_dofs = new double[new_ub];

    // Copy the old contents to the new array
    // and delete the old array.

    memcpy(new_dofs, _dofs, sizeof(double)*_dof_tuple_ub);
    delete [] _dofs;

    // Update base and bound.

    _dofs = new_dofs;
    _dof_tuple_ub   = new_ub;
  }

  // Postconditions:

  ensure(invariant());
  ensure(_dof_tuple_ub >= old_dof_tuple_ub);
  ensure(_dof_tuple_ub > xindex);

  // Exit:

  return;
}
