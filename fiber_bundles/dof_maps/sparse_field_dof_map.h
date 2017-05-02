
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

// $$SCRIBBLE: remove this class from build.

// Interface for class sparse_field_dof_map;
// This representation uses contiguous storage with
// the fiber index varying most rapidly

#ifndef SPARSE_FIELD_DOF_MAP_H
#define SPARSE_FIELD_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef FIELD_DOF_MAP_H
#include "SheafSystem/field_dof_map.h"
#endif

namespace sheaf
{
class dof_map_factory;
}

namespace fiber_bundle
{

class sec_rep_space;


///
/// OBSOLETE: Use array_sec_vd_dof_map or sparse_section_dof_map.
/// A representation of the abstract map from section_space_schema_member ids
/// to section dof values of homogeneous type double optimized for
/// the case in which most dofs have the same value.
///
class SHEAF_DLL_SPEC sparse_field_dof_map : public field_dof_map
{

public:

  ///
  /// The name of the actual (possibly derived) class of this instance.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();

  // ===========================================================
  // CANONICAL FACET
  // ===========================================================

  ///
  /// Default constructor.
  ///
  sparse_field_dof_map();

  ///
  /// Virtual default constructor.
  ///
  virtual sparse_field_dof_map* clone() const;

  ///
  /// Copy constructor
  ///
  sparse_field_dof_map(const sparse_field_dof_map& xother);

  ///
  /// Virtual copy constructor.
  ///
  virtual sparse_field_dof_map* copy() const;

  ///
  /// Assignment operator
  ///
  sparse_field_dof_map& operator=(const sparse_field_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~sparse_field_dof_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // ===========================================================
  // MAP FACET
  // ===========================================================

  ///
  /// Creates a dof map for a member of sec_rep_space xhost.
  ///
  sparse_field_dof_map(const sec_rep_space* xhost, double xdefault_value = 0.0);

  

  ///
  /// An identifer for the type of dof tuple this is.
  ///
  virtual dof_tuple_type type_id() const
  {
    return SPARSE_FIELD_DOF_TUPLE_ID;
  };

  ///
  /// The default value; the value for dofs that are not stored in _val_map.
  ///
  inline double default_value() const
  {
    return _def_val;
  };

  using field_dof_map::get_dof;
  using field_dof_map::put_dof;

  ///
  /// Copies the value of the dof referred to by the xid and xis_poset_id into
  /// the buffer of length xbuf_len bytes starting at xbuf.
  ///
  virtual void get_dof(const scoped_index& xid, bool xis_poset_id,
                       void *xbuf, size_t xbuf_len) const;

  ///
  /// Copies the value of the dof referred to by the xid and xis_poset_id from
  /// the buffer of length xbuf_len bytes starting at xbuf.
  ///
  virtual void put_dof(const scoped_index& xid, bool xis_poset_id,
                       const void *xbuf, size_t xbuf_len);

  ///
  /// Copies the values of the dofs referred to by the xclient_id_ct client
  /// ids in xclient_ids into the buffer of length xbuf_len bytes starting at
  /// xbuf.
  ///
  virtual void get_dofs(const client_index* xclient_ids, int xclient_id_ct,
                        void* xbuf, size_t xbuf_len) const;

  ///
  /// Copies the values of the dofs referred to by the xclient_id_ct client
  /// ids in xclient_ids from the buffer of length xbuf_len bytes starting at
  /// xbuf into internal storage.
  ///
  virtual void put_dofs(const client_index* xclient_ids, int xclient_id_ct,
                        const void* xbuf, size_t xbuf_len);

  ///
  /// Copies the value of the dof referred to by the ids xbase_id, xfiber_id,
  /// and xmult_id into the buffer of length xbuf_len bytes starting at xbuf.
  /// If xis_poset_id is true, ids are interpretted as poset member ids,
  /// otherwise they are interpretted as client ids.
  ///
  virtual void get_dof(const scoped_index& xbase_id,
                       const scoped_index& xfiber_id,
                       const scoped_index& xmult_id,
                       bool xis_poset_id,
                       void* xbuf, size_t xbuf_len) const;

  ///
  /// Copies the value of the dof referred to by the  ids in xbase_id, xfiber_id,
  /// and xmult_id from the buffer of length xbuf_len bytes starting at xbuf.
  /// If xis_poset_id is true, ids are interpretted as poset member ids,
  /// otherwise they are interpretted as client ids.
  ///
  virtual void put_dof(const scoped_index& xbase_id,
                       const scoped_index& xfiber_id,
                       const scoped_index& xmult_id,
                       bool xis_poset_id,
                       const void* xbuf, size_t xbuf_len);

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


  // ===========================================================
  // I/O SUPPORT FACET
  // ===========================================================

  ///
  /// True if this dof map type supports dof tuple transfer optimization.
  //// @hack dof tuple transfer hack.
  ////
  virtual bool supports_xfr_opt() const;

protected:

  ///
  /// Allocates dof storage.
  ///
  virtual void allocate_dofs();

private:

  ///
  /// Type of value map.
  ///
  typedef unordered::unordered_map<pod_index_type, double> val_map_type;

  ///
  /// Map from id to value.
  ///
  val_map_type _val_map;

  ///
  /// The default value; the value for dofs that are not stored in _val_map.
  ///
  double _def_val;

  ///
  /// True if prototype for this class has been entered in factory.
  /// Intended to force creation of prototype at initialization.
  ///
  static bool _has_prototype;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

};

} // namespace fiber_bundle

#endif // ifndef SPARSE_FIELD_DOF_MAP_H
