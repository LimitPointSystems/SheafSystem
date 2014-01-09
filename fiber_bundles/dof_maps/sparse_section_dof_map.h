
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

// Interface for class sparse_section_dof_map;
// map from client dof id to dof value.
// The section_dof_map interface assumes dofs
// are indexed by (base id, fiber id) pairs.
// This representation uses contiguous storage with
// the fiber index varying most rapidly

#ifndef SPARSE_SECTION_DOF_MAP_H
#define SPARSE_SECTION_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_DOF_MAP_H
#include "section_dof_map.h"
#endif

#ifndef STD_UNORDERED_MAP_H
#include "std_unordered_map.h"
#endif

namespace fiber_bundle
{

class sec_rep_space;

///
/// A discontiguous tuple, discontiguous fiber representation
/// of the abstract map from section dof ids
/// to section dof values of type sec_vd_dof_type.
/// This class assumes most of the dofs have some given
/// value (0.0 by default) and only stores dofs with a
/// non-default value.
///
class SHEAF_DLL_SPEC sparse_section_dof_map : public section_dof_map
{

  friend class fiber_bundles_namespace;

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
  /// Default constructor
  ///
  sparse_section_dof_map();

  ///
  /// Copy constructor
  ///
  sparse_section_dof_map(const sparse_section_dof_map& xother);

  ///
  /// Creates a dof map for a member of sec_rep_space xhost.
  ///
  sparse_section_dof_map(sec_rep_space* xhost, double xdefault_value = 0.0);

  ///
  /// Virtual default constructor.
  ///
  virtual sparse_section_dof_map* clone() const;

  ///
  /// Virtual copy constructor.
  ///
  virtual sparse_section_dof_map* copy() const;

  ///
  /// Assignment operator
  ///
  sparse_section_dof_map& operator=(const sparse_section_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~sparse_section_dof_map();

  ///
  /// The default value; the value for dofs that are not stored in _val_map.
  ///
  inline double default_value()
  {
    return _def_val;
  };

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // ===========================================================
  // MAP FACET
  // ===========================================================

  ///
  /// An identifer for the type of dof tuple this is.
  ///
  virtual dof_tuple_type type_id() const
  {
    return SPARSE_SECTION_DOF_TUPLE_ID;
  };

  using section_dof_map::get_dof;
  using section_dof_map::put_dof;

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
  virtual void put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size);

  /// @hack new_ prefix added to temporarily prevent
  /// ambiguity with old signature get_dof(const scoped_index&, bool, void*, size_t);
  /// remove when old signature removed.
 
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

  //@}

public:

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

/*   /// */
/*   /// Copies the values of the dofs referred to by the  client ids in */
/*   /// xclient_base_ids x xclient_fiber_ids to or from */
/*   /// the buffer of length xbuf_len bytes starting at xbuf. */
/*   /// */
/*   void copy_dofs(client_index* xclient_base_ids, int xclient_base_id_ct, */
/*                  client_index* xclient_fiber_ids, int xclient_fiber_id_ct, */
/*                  void* xbuf, size_t xbuf_len, bool to_client); */

  ///
  /// Allocates dof storage.
  ///
  virtual void allocate_dofs();

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

};

} // namespace fiber_bundle

#endif // ifndef SPARSE_SECTION_DOF_MAP_H
