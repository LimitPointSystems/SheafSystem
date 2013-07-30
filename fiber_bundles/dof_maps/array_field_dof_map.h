
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

// Interface for class array_field_dof_map;
// This representation uses contiguous storage with
// the fiber index varying most rapidly

#ifndef ARRAY_FIELD_DOF_MAP_H
#define ARRAY_FIELD_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef FIELD_DOF_MAP_H
#include "field_dof_map.h"
#endif

namespace sheaf
{
class dof_map_factory;
}

namespace fiber_bundle
{

class sec_rep_space;


///
/// A contiguous tuple, contiguous fiber representation
/// of the abstract map from section_space_schema_member ids
/// to section dof values of homogeneous type double.
///
class SHEAF_DLL_SPEC array_field_dof_map : public field_dof_map
{

public:

  ///
  /// The name of the actual (possibly derived) class of this instance.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  // ===========================================================
  // CANONICAL FACET
  // ===========================================================

  ///
  /// Default constructor
  ///
  array_field_dof_map();

  ///
  /// Virtual default constructor.
  ///
  virtual array_field_dof_map* clone() const;

  ///
  /// Copy constructor
  ///
  array_field_dof_map(const array_field_dof_map& xother);

  ///
  /// Virtual copy constructor.
  ///
  virtual array_field_dof_map* copy() const;

  ///
  /// Assignment operator
  ///
  array_field_dof_map& operator=(const array_field_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~array_field_dof_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // ===========================================================
  // MAP FACET
  // ===========================================================

  ///
  /// Creates a dof map for a member of sec_rep_space xhost.
  /// If xdofs is non zero, it will be used for dof storage,
  /// otherwise storage will be allocated
  ///
  array_field_dof_map(const sec_rep_space* xhost, void* xdofs = 0, size_t xdofs_ub = 0);

  

  ///
  /// An identifer for the type of dof tuple this is.
  ///
  virtual dof_tuple_type type_id() const
  {
    return ARRAY_FIELD_DOF_TUPLE_ID;
  };

  using field_dof_map::get_dof;
  using field_dof_map::put_dof;

  // ===========================================================
  /// @name NEW DOF ACCESS FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Copies the dof referred to by xdof_id into xdof.
  ///
  virtual void get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const;

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  virtual void put_dof(pod_index_type xdof_id, bool xis_poset_id, const void* xdof, size_type xdof_size);

  ///
  /// Copies the dof referred to by xdisc_id, xfiber_dof_id into xdof.
  ///
  virtual void get_dof(pod_index_type xdisc_id, 
		       pod_index_type xfiber_dof_id, 
		       void* xdof, 
		       size_type xdof_size) const;

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  virtual void put_dof(pod_index_type xdisc_id, 
		       pod_index_type xfiber_dof_id, 
		       const void* xdof, 
		       size_type xdof_size);
 
  ///
  /// Sets xfiber to the fiber referred to by discretization id xdisc_id.
  ///
  virtual void get_fiber(pod_index_type xdisc_id, void* xfiber, size_type xfiber_size) const;

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  virtual void put_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size);
 
  ///
  /// Sets xcomponent to the component referred to by fiber id xfiber_dof_id.
  ///
  virtual void get_component(pod_index_type xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const;

  ///
  /// Sets the component referred to by fiber id xfiber_dof_id to xcomponent.
  ///
  virtual void put_component(pod_index_type xfiber_dof_id, const void* xcomponent, size_type xcomponent_size);
  
protected:

private:

  ///
  /// Pointer to dof referred to be xdof_id.
  //
  sec_vd_dof_type* dof_ptr(pod_index_type xdof_id) const
  {
    return reinterpret_cast<sec_vd_dof_type*>(_dofs) + xdof_id;
  }

  ///
  /// Pointer to dof referred to be xdisc_id, xfiber_dof_id.
  //
  void* dof_ptr(pod_index_type xdisc_id, pod_index_type xfiber_dof_id) const
  {
    return _dofs + schema().offset(xdisc_id, xfiber_dof_id);
  }
    
  //@}

public:
 
  ///
  /// Copies the value of the dof referred to by the xid and xis_poset_id into
  /// the buffer of length xbuf_len bytes starting at xbuf.
  ///
  virtual void get_dof(const scoped_index& xid, bool xis_poset_id, void *xbuf, size_t xbuf_len) const;

  ///
  /// Copies the value of the dof referred to by the xid and xis_poset_id from
  /// the buffer of length xbuf_len bytes starting at xbuf.
  ///
  virtual void put_dof(const scoped_index& xid, bool xis_poset_id, const void *xbuf, size_t xbuf_len);

  ///
  /// Copies the values of the dofs referred to by the xclient_id_ct client
  /// ids in xclient_ids into the buffer of length xbuf_len bytes starting at
  /// xbuf.
  ///
  virtual void get_dofs(const client_index* xclient_ids, int xclient_id_ct, void* xbuf, size_t xbuf_len) const;

  ///
  /// Copies the values of the dofs referred to by the xclient_id_ct client
  /// ids in xclient_ids from the buffer of length xbuf_len bytes starting at
  /// xbuf into internal storage.
  ///
  virtual void put_dofs(const client_index* xclient_ids, int xclient_id_ct, const void* xbuf, size_t xbuf_len);

  ///
  /// Copies the value of the dof referred to by the ids xbase_id, xfiber_id,
  /// and xmult_id into the buffer of length xbuf_len bytes starting at xbuf.
  /// If xis_poset_id is true, ids are interpretted as poset member ids,
  /// otherwise they are interpretted as client ids.
  ///
  virtual void get_dof(const scoped_index& xbase_id,
		       const scoped_index& xfiber_id,
		       const scoped_index& xmult_id,
                       bool xis_poset_id, void* xbuf, size_t xbuf_len) const;

  ///
  /// Copies the value of the dof referred to by the  ids in xbase_id, xfiber_id,
  /// and xmult_id from the buffer of length xbuf_len bytes starting at xbuf.
  /// If xis_poset_id is true, ids are interpretted as poset member ids,
  /// otherwise they are interpretted as client ids.
  ///
  virtual void put_dof(const scoped_index& xbase_id,
		       const scoped_index& xfiber_id,
		       const scoped_index& xmult_id,
                       bool xis_poset_id, const void* xbuf, size_t xbuf_len);

  ///
  /// Copies the values of the dofs referred to by the  client ids in
  /// xclient_base_ids x xclient_fiber_ids into
  /// the buffer of length xbuf_len bytes starting at xbuf.
  ///
  virtual void get_dofs(const client_index* xclient_base_ids, int xclient_base_id_ct,
                        const client_index* xclient_fiber_ids, int xclient_fiber_id_ct,
                        void* xbuf, size_t xbuf_len) const;

  ///
  /// Copies the values of the dofs referred to by the  client ids in
  /// xclient_base_ids x xclient_fiber_ids from
  /// the buffer of length xbuf_len bytes starting at xbuf.
  ///
  virtual void put_dofs(const client_index* xclient_base_ids, int xclient_base_id_ct,
                        const client_index* xclient_fiber_ids, int xclient_fiber_id_ct,
                        const void* xbuf, size_t xbuf_len);

  ///
  /// Copys the dofs associated with the discretization member
  /// identified by xdisc_id into the buffer of length xbuf_len
  /// bytes starting at xbuf.
  /// If xis_poset_id is true, ids are interpretted as poset member ids,
  /// otherwise they are interpretted as client ids.
  ///
  virtual void get_discretization_dofs(const scoped_index& xdisc_id,
                                       bool xis_poset_id,
                                       void* xbuf,
                                       size_t xbuf_len) const;
  ///
  /// Copys the dofs associated with the discretization member
  /// identified by xdisc_id from the buffer of length xbuf_len
  /// bytes starting at xbuf into internal storage.
  /// If xis_poset_id is true, ids are interpretted as poset member ids,
  /// otherwise they are interpretted as client ids.
  ///
  virtual void put_discretization_dofs(const scoped_index& xdisc_id,
                                       bool xis_poset_id,
                                       const void* xbuf,
                                       size_t xbuf_len);
  ///
  /// Copys the dofs associated with the fiber component identified by xcomp_id
  /// from internal storage into buffer xbuf of length xbuf_len bytes.
  ///
  /// If xdisc_ids is not void, only the dofs associated with the
  /// discretization members identified by the xdisc_id_ct ids in xdisc_ids
  /// are transferred.
  ///
  virtual void get_component_dofs(void* xbuf,
                                  size_t xbuf_len,
                                  const scoped_index& xcomp_id,
                                  const scoped_index* xdisc_ids = 0,
                                  size_type xdisc_ids_ct = 0) const;

  ///
  /// Copys the dofs associated with the fiber component identified by xcomp_id
  /// from buffer xbuf of length xbuf_len bytes into internal storage.
  ///
  /// If xdisc_ids is not void, only the dofs associated with the
  /// discretization members identified by the xdisc_id_ct ids in xdisc_ids
  /// are transferred.
  ///
  virtual void put_component_dofs(const void* xbuf,
                                  size_t xbuf_len,
                                  const scoped_index& xcomp_id,
                                  const scoped_index* xdisc_ids = 0,
                                  size_type xdisc_ids_ct = 0);

  ///
  /// Copys the dofs associated with the fiber component identified by xcomp_id
  /// from internal storage into buffer xbuf of length xbuf_len bytes.
  /// Xcomp_client_id_map is used to convert xcomp_id from a client id to
  /// a poset member id.
  ///
  /// If xdisc_ids is not void, only the dofs associated with the
  /// discretization members identified by the xdisc_id_ct ids in xdisc_ids
  /// are transferred. Xdisc_client_id_map is used to convert the ids in
  /// xdisc_ids from client ids to poset member ids.
  ///
  virtual void get_component_dofs(void* xbuf,
                                  size_t xbuf_len,
                                  const client_index& xcomp_id,
                                  const id_map* xcomp_client_id_map,
                                  const client_index* xdisc_ids = 0,
                                  size_type xdisc_ids_ct = 0,
                                  const id_map* xdisc_client_id_map = 0) const;

  ///
  /// Copys the dofs associated with the fiber component identified by xcomp_id
  /// from buffer xbuf of length xbuf_len bytes into internal storage.
  /// Xcomp_client_id_map is used to convert xcomp_id from a client id to
  /// a poset member id.
  ///
  /// If xdisc_ids is not void, only the dofs associated with the
  /// discretization members identified by the xdisc_id_ct ids in xdisc_ids
  /// are transferred. Xdisc_client_id_map is used to convert the ids in
  /// xdisc_ids from client ids to poset member ids.
  ///
  virtual void put_component_dofs(const void* xbuf,
                                  size_t xbuf_len,
                                  const client_index& xcomp_id,
                                  const id_map* xcomp_client_id_map,
                                  const client_index* xdisc_ids = 0,
                                  size_type xdisc_ids_ct = 0,
                                  const id_map* xdisc_client_id_map = 0);
  ///
  /// The dof tuple (mutable version).
  ///
  virtual void* dof_tuple();

  ///
  /// The dof tuple (const version).
  ///
  virtual const void* dof_tuple() const;

  ///
  /// Copies the entire dof tuple from internal storage into xbuf.
  ///
  virtual void get_dof_tuple(void* xbuf, size_t xbuflen) const;

  ///
  /// Copies the entire dof tuple from xbuf into internal storage
  ///
  virtual void put_dof_tuple(const void* xbuf, size_t xbuflen);


protected:

  ///
  /// Allocates dof storage.
  ///
  virtual void allocate_dofs();

private:

  ///
  /// The number of members in the discretization
  ///
  int _disc_ct;

  ///
  /// The number of jims in the fiber
  ///
  int _fiber_ct;

  ///
  /// The number of dofs associated with each (disc member, fiber jim) pair.
  ///
  int _local_ct;

  ///
  /// _fiber_ct*_local_ct
  ///
  int _fiber_tuple_size;

  ///
  /// Storage for the dofs
  ///
  double* _dofs;

  ///
  /// True if this allocated _dofs and hence should delete it
  ///
  bool _this_owns_dofs;

  ///
  /// True if prototype for this class has been entered in factory.
  /// Intended to force creation of prototype at initialization.
  ///
  static bool _has_prototype;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  ///
  /// Ensures that _dofs has enough capacity that xindex is a valid index.
  ///
  void reserve(int xindex);
};

} // namespace fiber_bundle

#endif // ifndef ARRAY_FIELD_DOF_MAP_H
