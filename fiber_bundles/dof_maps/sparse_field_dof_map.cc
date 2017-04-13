
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

// Implementation for class sparse_field_dof_map

#include "SheafSystem/sparse_field_dof_map.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/discretization_iterator.h"
#include "SheafSystem/dof_map_factory.h"
#include "SheafSystem/sec_rep_space.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// PUBLIC MEMBER FUNCTIONS

 

///
const std::string&
fiber_bundle::sparse_field_dof_map::
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
fiber_bundle::sparse_field_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sparse_field_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "sparse_field_dof_map");

  // Exit:

  return result;
}

// ===========================================================
// CANONICAL FACET
// ===========================================================

///
fiber_bundle::sparse_field_dof_map::
sparse_field_dof_map()
    : field_dof_map()
{

  // Preconditions:


  // Body:

  /// @error doesn't initialize _schema.

  _def_val = 0.0;

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
fiber_bundle::sparse_field_dof_map*
fiber_bundle::sparse_field_dof_map::
clone() const
{
  sparse_field_dof_map* result;

  // Preconditions:


  // Body:

  result = new sparse_field_dof_map();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(sparse_field_dof_map()));

  // Exit:

  return result;
}


///
fiber_bundle::sparse_field_dof_map::
sparse_field_dof_map(const sparse_field_dof_map& xother)
    : field_dof_map(xother)
{

  // Preconditions:


  // Body:

  _def_val = 0.0;

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
fiber_bundle::sparse_field_dof_map*
fiber_bundle::sparse_field_dof_map::
copy() const
{
  sparse_field_dof_map* result;

  // Preconditions:


  // Body:

  result = new sparse_field_dof_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(sparse_field_dof_map(*this)));

  // Exit:

  return result;
}

///
fiber_bundle::sparse_field_dof_map&
fiber_bundle::sparse_field_dof_map::
operator=(const sparse_field_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  field_dof_map::operator=(xother);


  _val_map.clear();
  _val_map = xother._val_map;

  _def_val = xother._def_val;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}


///
fiber_bundle::sparse_field_dof_map::
~sparse_field_dof_map()
{

  // Preconditions:


  // Body:

  // Postconditions:

}


///
bool
fiber_bundle::sparse_field_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  /// @todo finish sparse_field_dof_map::invariant() const

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// MAP FACET
// ===========================================================

///
fiber_bundle::sparse_field_dof_map::
sparse_field_dof_map(const sec_rep_space* xhost, double xdefault_value)
    : field_dof_map(xhost)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());

  // Body:

  // Initialize counts


  _def_val = xdefault_value;


  // Postconditions:

  ensure(invariant());
  ensure(default_value() == xdefault_value);

}

 

///
void
fiber_bundle::sparse_field_dof_map::
get_dof(const scoped_index& xid, bool xis_poset_id, void* xbuf, size_t xbuf_len) const
{
  // Preconditions:

  require(xis_poset_id ? schema().contains_row_dof(xid) : true);
  require(xbuf != 0);
  require(xbuf_len >= sizeof(double));
  require(unexecutable("xbuf is properly aligned for double"));
  require(xis_poset_id ? xid.in_scope() : true);

  /// @hack We're assuming multiplicity == 1 below.

  require(host()->multiplicity() == 1);

  // Body:

  // Dofs are hashed on internal ids;
  // convert to internal ids.

  pod_index_type lid;

  if(xis_poset_id)
  {
    lid = xid.hub_pod();
  }
  else
  {
    /// @hack assume multiplicity = 1.

    int lfiber_dof_ct = schema().fiber_schema().row_dof_ct();

    scoped_index lbase_id(&schema().disc_seq_id_map());
    lbase_id = xid.pod() / lfiber_dof_ct;

    scoped_index lfiber_id(&schema().fiber_schema().row_dof_client_id_map());
    lfiber_id = xid.pod() % lfiber_dof_ct;

    lid = schema().host()->get_index_from_components(lbase_id, lfiber_id).hub_pod();
  }

  double* lbuf = reinterpret_cast<double*>(xbuf);

   
  val_map_type::const_iterator itr = _val_map.find(lid);

  if(itr != _val_map.end())
  {
    *lbuf = itr->second;
  }
  else
  {
    *lbuf = _def_val;
  }


  // Postconditions:

  // Exit

  return;
}


///
void
fiber_bundle::sparse_field_dof_map::
put_dof(const scoped_index& xid, bool xis_poset_id, const void* xbuf, size_t xbuf_len)
{
  // Preconditions:

  require(xis_poset_id ? schema().contains_row_dof(xid) : true);
  require(xbuf != 0);
  require(xbuf_len >= sizeof(double));
  require(unexecutable("xbuf is properly aligned for double"));
  require(xis_poset_id ? xid.in_scope() : true);

  /// @hack We're assuming multiplicity == 1 below.

  require(host()->multiplicity() == 1);

  // Body:

  // Dofs are hashed on internal ids;
  // convert to internal ids.

  pod_index_type lid;

  if(xis_poset_id)
  {
    lid = xid.hub_pod();
  }
  else
  {
    /// @hack assume multiplicity = 1.

    int lfiber_dof_ct = schema().fiber_schema().row_dof_ct();

    scoped_index lbase_id(&schema().disc_seq_id_map());
    lbase_id = xid.pod() / lfiber_dof_ct;

    scoped_index lfiber_id(&schema().fiber_schema().row_dof_client_id_map());
    lfiber_id = xid.pod() % lfiber_dof_ct;

    lid = schema().host()->get_index_from_components(lbase_id, lfiber_id).hub_pod();
  }

  const double* lbuf = reinterpret_cast<const double*>(xbuf);

  if(*lbuf != _def_val)
  {
    // Insert the value in the map;
    // updates entry if one already exists.

    _val_map[lid] = *lbuf;
  }
  else
  {
    // Value is default,
    // make sure it's not in the map

    _val_map.erase(lid);
  }

  // Postconditions:

  // Exit

  return;
}



///
void
fiber_bundle::sparse_field_dof_map::
get_dofs(const client_index* xclient_ids, int xclient_id_ct,
         void* xbuf, size_t xbuf_len) const
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
fiber_bundle::sparse_field_dof_map::
put_dofs(const client_index* xclient_ids, int xclient_id_ct,
         const void* xbuf, size_t xbuf_len)
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
fiber_bundle::sparse_field_dof_map::
get_dof(const scoped_index& xbase_id,
        const scoped_index& xfiber_id,
        const scoped_index& xmult_id,
        bool xis_poset_id,
        void* xbuf,
        size_t xbuf_len) const
{
  // Preconditions:

  require(xis_poset_id ? schema().contains_row_dof(xbase_id, xfiber_id) : true);
  require(unexecutable("if !xis_poset_id xbase_idand xfiber_id are valid client ids"));
  require(unexecutable(0 <= xmult_id && xmult_id < multiplicity));
  require(xbuf != 0);
  require(xbuf_len >= sizeof(double));

  // Body:

  scoped_index lbase_id, lfiber_id; // Unscoped.

  if(xis_poset_id)
  {
    lbase_id  = xbase_id.hub_pod();
    lfiber_id = xfiber_id.hub_pod();
  }
  else
  {
    lbase_id  = schema().discretization().id_map()->poset_id(xbase_id);
    lfiber_id = schema().fiber_schema().row_dof_client_id_map().poset_id(xfiber_id);
  }

  scoped_index l_id =
    schema().host()->get_index_from_components(lbase_id, lfiber_id);

  get_dof(l_id, true, xbuf, xbuf_len);

  // Postconditions:

  // Exit

  return;
}


///
void
fiber_bundle::sparse_field_dof_map::
put_dof(const scoped_index& xbase_id,
        const scoped_index& xfiber_id,
        const scoped_index& xmult_id,
        bool xis_poset_id,
        const void* xbuf,
        size_t xbuf_len)
{
  // Preconditions:

  require(xis_poset_id ? schema().contains_row_dof(xbase_id, xfiber_id) : true);
  require(unexecutable("if !xis_poset_id xbase_idand xfiber_id are valid client ids"));
  require(unexecutable(0 <= xmult_id && xmult_id < multiplicity));
  require(xbuf != 0);
  require(xbuf_len >= sizeof(double));

  // Body:

  scoped_index lbase_id, lfiber_id; // Unscoped.

  if(xis_poset_id)
  {
    lbase_id  = xbase_id.hub_pod();
    lfiber_id = xfiber_id.hub_pod();
  }
  else
  {
    lbase_id  = schema().discretization().id_map()->poset_id(xbase_id);
    lfiber_id = schema().fiber_schema().row_dof_client_id_map().poset_id(xfiber_id);
  }

  scoped_index l_id =
    schema().host()->get_index_from_components(lbase_id, lfiber_id);

  put_dof(l_id, true, xbuf, xbuf_len);

  // Postconditions:

  ensure(unexecutable(internal storage holds dof referred to by xids));

  // Exit

  return;
}

///
void
fiber_bundle::sparse_field_dof_map::
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

  sparse_field_dof_map* cthis = const_cast<sparse_field_dof_map*>(this);
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
fiber_bundle::sparse_field_dof_map::
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
fiber_bundle::sparse_field_dof_map::
get_discretization_dofs(const scoped_index& xdisc_id,
                        bool xis_poset_id,
                        void* xbuf,
                        size_t xbuf_len) const
{
  // Preconditions:

  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(xbuf_len >= schema().fiber_schema().row_dof_tuple_ub());

  // Body:

  scoped_index ldisc_id; // Unscoped.

  if(xis_poset_id)
  {
    ldisc_id  = xdisc_id.hub_pod();
  }
  else
  {
    ldisc_id  = schema().discretization().id_map()->poset_id(xdisc_id);
  }

  char* lbuf = reinterpret_cast<char*>(xbuf);

  poset_dof_iterator* itr = schema().fiber_schema().row_dof_iterator();
  while(!itr->is_done())
  {
    scoped_index lpid =
      schema().host()->get_index_from_components(ldisc_id, itr->index());

    get_dof(lpid, true, lbuf, xbuf_len);
    lbuf += sizeof(double);
    xbuf_len -= sizeof(double);
    itr->next();
  }

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::sparse_field_dof_map::
put_discretization_dofs(const scoped_index& xdisc_id,
                        bool xis_poset_id,
                        const void* xbuf,
                        size_t xbuf_len)
{
  // Preconditions:

  require(xbuf != 0);
  require(unexecutable(xbuf points to buffer of length xbuf_len));
  require(xbuf_len >= schema().fiber_schema().row_dof_tuple_ub());

  // Body:

  scoped_index ldisc_id; // Unscoped.

  if(xis_poset_id)
  {
    ldisc_id  = xdisc_id.hub_pod();
  }
  else
  {
    ldisc_id  = schema().discretization().id_map()->poset_id(xdisc_id);
  }

  const char* lbuf = reinterpret_cast<const char*>(xbuf);

  poset_dof_iterator* itr = schema().fiber_schema().row_dof_iterator();
  while(!itr->is_done())
  {
    scoped_index lpid =
      schema().host()->get_index_from_components(ldisc_id, itr->index());

    put_dof(lpid, true, lbuf, xbuf_len);
    lbuf += sizeof(double);
    xbuf_len -= sizeof(double);
    itr->next();
  }

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::sparse_field_dof_map::
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

  char* lbuf = reinterpret_cast<char*>(xbuf);

  if(xdisc_ids != 0)
  {
    // Client has specified which dofs to get.

    for(size_t i=0; i<xdisc_ids_ct; i++)
    {
      get_dof(xdisc_ids[i],
              xcomp_id,
              scoped_index::ZERO(),
              true,
              lbuf,
              xbuf_len);

      lbuf += sizeof(double);
      xbuf_len -= sizeof(double);
    }
  }
  else
  {
    // Transfer all the dofs in the component.

    discretization_iterator ditr(schema());
    while(!ditr.is_done())
    {
      get_dof(ditr.discretization_member_index(),
              xcomp_id,
              scoped_index::ZERO(),
              true,
              lbuf,
              xbuf_len);

      lbuf += sizeof(double);
      xbuf_len -= sizeof(double);
      ditr.next();
    }
  }

  // Postconditions:

  // Exit

  return;
}


///
void
fiber_bundle::sparse_field_dof_map::
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

  const char* lbuf = reinterpret_cast<const char*>(xbuf);

  if(xdisc_ids != 0)
  {
    // Client has specified which dofs to get.

    for(size_t i=0; i<xdisc_ids_ct; i++)
    {
      put_dof(xdisc_ids[i],
              xcomp_id,
              scoped_index::ZERO(),
              true,
              lbuf,
              xbuf_len);

      lbuf += sizeof(double);
      xbuf_len -= sizeof(double);
    }
  }
  else
  {
    // Transfer all the dofs in the component.

    discretization_iterator ditr(schema());
    while(!ditr.is_done())
    {
      put_dof(ditr.discretization_member_index(),
              xcomp_id,
              scoped_index::ZERO(),
              true,
              lbuf,
              xbuf_len);

      lbuf += sizeof(double);
      xbuf_len -= sizeof(double);
      ditr.next();
    }
  }

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::sparse_field_dof_map::
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

  /// @error not dealing with scoped ids.
  /// @todo fix sparse_field_dof_map::copy_component_dofs to use scoped ids.

  not_implemented();

  //   scoped_index lcomp_id(xcomp_client_id_map->poset_id(xcomp_id));

  //   char* lbuf = reinterpret_cast<char*>(xbuf);

  //   if(xdisc_ids != 0)
  //   {
  //     // Client has specified which dofs to get.

  //     for(size_t i=0; i<xdisc_ids_ct; i++)
  //     {
  //       scoped_index ldisc_id(xdisc_client_id_map->poset_id(xdisc_ids[i]));

  //       get_dof(ldisc_id,
  //               lcomp_id,
  //               scoped_index::ZERO(),
  //               true,
  //               lbuf,
  //               xbuf_len);

  //       lbuf += sizeof(double);
  //       xbuf_len -= sizeof(double);
  //     }
  //   }
  //   else
  //   {
  //     // Transfer all the dofs in the component.

  //     discretization_iterator ditr(schema());
  //     while(!ditr.is_done())
  //     {
  //       scoped_index ldisc_id = ditr.discretization_member_index();

  //       get_dof(ldisc_id,
  //               lcomp_id,
  //               scoped_index::ZERO(),
  //               true,
  //               lbuf,
  //               xbuf_len);

  //       lbuf += sizeof(double);
  //       xbuf_len -= sizeof(double);
  //       ditr.next();
  //     }
  //   }

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::sparse_field_dof_map::
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

  /// @error not dealing with scoped ids.
  /// @todo fix sparse_field_dof_map::copy_component_dofs to use scoped ids.

  not_implemented();

  //   scoped_index lcomp_id(xcomp_client_id_map->poset_id(xcomp_id));

  //   char* lbuf = reinterpret_cast<char*>(xbuf);

  //   if(xdisc_ids != 0)
  //   {
  //     // Client has specified which dofs to get.

  //     for(size_t i=0; i<xdisc_ids_ct; i++)
  //     {
  //       scoped_index ldisc_id(xdisc_client_id_map->poset_id(xdisc_ids[i]));

  //       put_dof(ldisc_id,
  //               lcomp_id,
  //               scoped_index::ZERO(),
  //               true,
  //               lbuf,
  //               xbuf_len);

  //       lbuf += sizeof(double);
  //       xbuf_len -= sizeof(double);
  //     }
  //   }
  //   else
  //   {
  //     // Transfer all the dofs in the component.

  //     discretization_iterator ditr(schema());
  //     while(!ditr.is_done())
  //     {
  //       scoped_index ldisc_id = ditr.discretization_member_index();

  //       put_dof(ldisc_id,
  //               lcomp_id,
  //               scoped_index::ZERO(),
  //               true,
  //               lbuf,
  //               xbuf_len);

  //       lbuf += sizeof(double);
  //       xbuf_len -= sizeof(double);
  //       ditr.next();
  //     }
  //   }

  // Postconditions:

  // Exit

  return;
}

///
void*
fiber_bundle::sparse_field_dof_map::
dof_tuple()
{
  void* result = 0;

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

///
const void*
fiber_bundle::sparse_field_dof_map::
dof_tuple() const
{
 const  void* result = 0;

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

///
void
fiber_bundle::sparse_field_dof_map::
get_dof_tuple(void* xbuf, size_t xbuf_len) const
{
  // Preconditions:

  require(xbuf != 0);
  require(dof_tuple_ub() <= xbuf_len);

  // Body:

  double* lbuf = reinterpret_cast<double*>(xbuf);
  size_t lbuf_len = xbuf_len/sizeof(double);

  section_dof_iterator* itr = schema().row_dof_iterator();
  while(!itr->is_done())
  {
    get_dof(itr->index(), true, lbuf++, lbuf_len--);

    itr->next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(dof tuple copied to xbuf));

  // Exit

  return;
}


///
void
fiber_bundle::sparse_field_dof_map::
put_dof_tuple(const void* xbuf, size_t xbuf_len)
{
  // Preconditions:

  require(xbuf != 0);
  require(dof_tuple_ub() <= xbuf_len);

  // Body:

  /// @hack cast away constness because put_dof doesn't support it.

  double* lbuf = reinterpret_cast<double*>(const_cast<void*>(xbuf));
  size_t lbuf_len = xbuf_len/sizeof(double);

  section_dof_iterator* itr = schema().row_dof_iterator();
  while(!itr->is_done())
  {
    put_dof(itr->index(), true, lbuf++, lbuf_len--);

    itr->next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(xbuf copied to dof tuple));

  // Exit

  return ;
}

 

///
bool
fiber_bundle::sparse_field_dof_map::
supports_xfr_opt() const
{
  /// @hack dof tuple transfer hack.
  return false;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::sparse_field_dof_map::
allocate_dofs()
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


bool
fiber_bundle::sparse_field_dof_map::
_has_prototype = make_prototype();

///
bool
fiber_bundle::sparse_field_dof_map::
make_prototype()
{
  bool result = false;

  // Preconditions:


  // Body:

  dof_tuple_type ltype =
    SPARSE_FIELD_DOF_TUPLE_ID;

  poset_dof_map* lproto = new sparse_field_dof_map;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:


  // Exit:

  return result;
}
