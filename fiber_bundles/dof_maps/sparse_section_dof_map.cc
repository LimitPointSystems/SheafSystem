
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Implementation for class sparse_section_dof_map

#include "sparse_section_dof_map.h"

#include "assert_contract.h"
#include "dof_map_factory.h"
#include "ij_product_structure.h"
#include "index_space_iterator.h"
#include "primitive_type.h"
#include "sec_rep_space.h"
#include "sec_vd.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// PUBLIC MEMBER FUNCTIONS

///
const string&
fiber_bundle::sparse_section_dof_map::
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
fiber_bundle::sparse_section_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sparse_section_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "sparse_section_dof_map");

  // Exit:

  return result;
}

// CANONICAL MEMBERS

///
fiber_bundle::sparse_section_dof_map::
sparse_section_dof_map()
    : section_dof_map()
{

  // Preconditions:


  // Body:

  _def_val = 0.0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());


  // Exit

  return;
}

///
fiber_bundle::sparse_section_dof_map::
sparse_section_dof_map(const sparse_section_dof_map& xother)
    : section_dof_map(xother)
{

  // Preconditions:


  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

fiber_bundle::sparse_section_dof_map::
sparse_section_dof_map(sec_rep_space* xhost, sec_vd_dof_type xdefault_value)
    : section_dof_map(xhost, xhost->base().index(), xhost->version())
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());

  // Body:

  _def_val = xdefault_value;
  
  // Postconditions:

  ensure(default_value() == xdefault_value);

}

///
fiber_bundle::sparse_section_dof_map*
fiber_bundle::sparse_section_dof_map::
clone() const
{
  sparse_section_dof_map* result;

  // Preconditions:


  // Body:

  result = new sparse_section_dof_map();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(sparse_section_dof_map()));

  // Exit:

  return result;
}


///
fiber_bundle::sparse_section_dof_map*
fiber_bundle::sparse_section_dof_map::
copy() const
{
  sparse_section_dof_map* result;

  // Preconditions:


  // Body:

  result = new sparse_section_dof_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(sparse_section_dof_map(*this)));

  // Exit:

  return result;
}


///
fiber_bundle::sparse_section_dof_map&
fiber_bundle::sparse_section_dof_map::
operator=(const sparse_section_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  section_dof_map::operator=(xother);

  _val_map.clear();
  _val_map = xother._val_map;

  _def_val = xother._def_val;


  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}


///
fiber_bundle::sparse_section_dof_map::
~sparse_section_dof_map()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


///
bool
fiber_bundle::sparse_section_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  /// @todo implement sparse_section_dof_map::invariant()

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// MAP FACET
// ===========================================================


// ===========================================================
//  NEW DOF ACCESS FACET
// ===========================================================
 
///
void
fiber_bundle::sparse_section_dof_map::
get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));

  // Body:

  sec_vd_dof_type& ldof = *reinterpret_cast<sec_vd_dof_type*>(xdof);
  
  val_map_type::const_iterator itr = _val_map.find(xdof_id);

  if(itr != _val_map.end())
  {
    ldof = itr->second;
  }
  else
  {
    ldof = _def_val;
  }
  
  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::sparse_section_dof_map::
put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));

  // Body:

  const sec_vd_dof_type& ldof =
    *reinterpret_cast<const sec_vd_dof_type*>(xdof);

  if(ldof != _def_val)
  {
    // Insert the value in the map;
    // updates entry if one already exists.

    _val_map[xdof_id] = ldof;
  }
  else
  {
    // Value is default,
    // make sure it's not in the map

    _val_map.erase(xdof_id);
  }

  // Postconditions:

  
  // Exit

  return;
}

 
void
fiber_bundle::sparse_section_dof_map::
get_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id, false));
  
  // Body:

  pod_index_type ldof_id;
  schema().row_dof_id_space().product_structure<ij_product_structure>().
    ordinal(xdisc_id, xfiber_dof_id, ldof_id);
  
  get_dof(ldof_id, xdof, xdof_size);
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::sparse_section_dof_map::
put_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id, false));
  
  
  // Body:

  pod_index_type ldof_id;
  schema().row_dof_id_space().product_structure<ij_product_structure>().
    ordinal(xdisc_id, xfiber_dof_id, ldof_id);
  
  put_dof(ldof_id, xdof, xdof_size);
  
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::sparse_section_dof_map::
get_fiber(pod_index_type xdisc_id, void* xfiber, size_type xfiber_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  
  // Body:

  sec_vd_dof_type* lfiber = reinterpret_cast<sec_vd_dof_type*>(xfiber);

  const ij_product_structure& lproduct =
    schema().row_dof_id_space().product_structure<ij_product_structure>();

  pod_index_type ldof_id;
  pod_index_type lub = schema().fiber_schema_id_space(false).end();
  
  for(pod_index_type i=0; i<lub; ++i, ++lfiber)
  {
    lproduct.ordinal(xdisc_id, i, ldof_id);
    get_dof(ldof_id, lfiber, sizeof(sec_vd_dof_type));
  }
  
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::sparse_section_dof_map::
put_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  
  // Body:

  const sec_vd_dof_type* lfiber =
    reinterpret_cast<const sec_vd_dof_type*>(xfiber);

  const ij_product_structure& lproduct =
    schema().row_dof_id_space().product_structure<ij_product_structure>();

  pod_index_type ldof_id;
  pod_index_type lub = schema().fiber_schema_id_space(false).end();
  
  for(pod_index_type i=0; i<lub; ++i, ++lfiber)
  {
    lproduct.ordinal(xdisc_id, i, ldof_id);
    put_dof(ldof_id, lfiber, sizeof(sec_vd_dof_type));
  }
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::sparse_section_dof_map::
get_component(pod_index_type xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));
  
  
  // Body:

  sec_vd_dof_type* lcomponent = reinterpret_cast<sec_vd_dof_type*>(xcomponent);

  const ij_product_structure& lproduct =
    schema().row_dof_id_space().product_structure<ij_product_structure>();

  pod_index_type ldof_id;
  size_type ldisc_ct = schema().discretization_ct();
  
  for(pod_index_type i=0; i<ldisc_ct; ++i, ++lcomponent)
  {
    lproduct.ordinal(i, xfiber_dof_id, ldof_id);
    get_dof(ldof_id, lcomponent, sizeof(sec_vd_dof_type));
  }

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::sparse_section_dof_map::
put_component(pod_index_type xfiber_dof_id, const void* xcomponent, size_type xcomponent_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));
  
  
  // Body:

  const sec_vd_dof_type* lcomponent =
    reinterpret_cast<const sec_vd_dof_type*>(xcomponent);

  const ij_product_structure& lproduct =
    schema().row_dof_id_space().product_structure<ij_product_structure>();

  pod_index_type ldof_id;
  size_type ldisc_ct = schema().discretization_ct();
  
  for(pod_index_type i=0; i<ldisc_ct; ++i, ++lcomponent)
  {
    lproduct.ordinal(i, xfiber_dof_id, ldof_id);
    put_dof(ldof_id, lcomponent, sizeof(sec_vd_dof_type));
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
fiber_bundle::sparse_section_dof_map::
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
fiber_bundle::sparse_section_dof_map::
dof_tuple() const
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
void
fiber_bundle::sparse_section_dof_map::
get_dof_tuple(void* xbuf, size_t xbuf_len) const
{
  // Preconditions:

  require(xbuf != 0);
  require(dof_tuple_ub() <= xbuf_len);

  // Body:

  double* lbuf = reinterpret_cast<double*>(xbuf);
  size_t lbuf_len = xbuf_len/sizeof(double);

  index_space_iterator& itr = schema().row_dof_id_space().get_iterator();
  while(!itr.is_done())
  {
    get_dof(itr.pod(), lbuf++, lbuf_len--);

    itr.next();
  }
  schema().row_dof_id_space().release_iterator(itr);
  

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(dof tuple copied to xbuf));

  // Exit

  return;
}


///
void
fiber_bundle::sparse_section_dof_map::
put_dof_tuple(const void* xbuf, size_t xbuf_len)
{
  // Preconditions:

  require(xbuf != 0);
  require(dof_tuple_ub() <= xbuf_len);

  // Body:

  /// @hack cast away constness because put_dof doesn't support it.

  double* lbuf = reinterpret_cast<double*>(const_cast<void*>(xbuf));
  size_t lbuf_len = xbuf_len/sizeof(double);

  index_space_iterator& itr = schema().row_dof_id_space().get_iterator();
  while(!itr.is_done())
  {
    put_dof(itr.pod(), lbuf++, lbuf_len--);

    itr.next();
  }
  schema().row_dof_id_space().release_iterator(itr);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(xbuf copied to dof tuple));

  // Exit

  return ;
}

///
bool
fiber_bundle::sparse_section_dof_map::
supports_xfr_opt() const
{
  /// @hack dof tuple transfer hack.
  return false;
}

// PROTECTED MEMBER FUNCTIONS



// void
// fiber_bundle::sparse_section_dof_map::
// copy_dofs(client_index* xclient_base_ids,
//           int xclient_base_id_ct,
//           client_index* xclient_fiber_ids,
//           int xclient_fiber_id_ct,
//           void* xbuf,
//           size_t xbuf_len,
//           bool to_client)
// {
//   // Preconditions:

//   // Body:

//   double* lbuf = static_cast<double*>(xbuf);
//   size_t lbuf_len = xbuf_len/sizeof(double);

//   scoped_index lbid, lfid, l_id; // Unscoped.

//   for(int b=0; b<xclient_base_id_ct; b++)
//   {
//     lbid = schema().discretization().client_id_map()->range_id(xclient_base_ids[b]);

//     for(int f=0; f<xclient_fiber_id_ct; f++)
//     {
//       lfid = schema().fiber_schema().row_dof_client_id_map().range_id(xclient_fiber_ids[f]);

//       l_id = schema().host()->get_index_from_components(lbid, lfid);

//       if(to_client)
//       {
//         get_dof(l_id, true, lbuf++, lbuf_len--);
//       }
//       else
//       {
//         put_dof(l_id, true, lbuf++, lbuf_len--);
//       }
//     }
//   }

//   // Postconditions:

//   ensure(invariant());

//   // Exit

//   return;
// }

///
void
fiber_bundle::sparse_section_dof_map::
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
fiber_bundle::sparse_section_dof_map::
make_prototype()
{
  bool result = false;

  // Preconditions:


  // Body:

  // $$SCRIBBLE: need to define SPARSE_SECTION_DOF_TUPLE_ID

  dof_tuple_type ltype = SPARSE_SECTION_DOF_TUPLE_ID;

  poset_dof_map* lproto = new sparse_section_dof_map;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:


  // Exit:

  return result;
}
