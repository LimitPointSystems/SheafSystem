
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

// Interface for class array_section_dof_map;
// map from client dof id to dof value.
// The section_dof_map interface assumes dofs
// are indexed by (base id, fiber id) pairs.
// This representation uses contiguous storage with
// the fiber index varying most rapidly

#ifndef ARRAY_SECTION_DOF_MAP_H
#define ARRAY_SECTION_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_DOF_MAP_H
#include "section_dof_map.h"
#endif

namespace fiber_bundle
{

class sec_rep_space;

///
/// A contiguous tuple, contiguous fiber representation
/// of the abstract map from section dof ids
/// to section dof values of heterogeneous type.
///
class SHEAF_DLL_SPEC array_section_dof_map : public section_dof_map
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
  array_section_dof_map();

  ///
  /// Virtual default constructor.
  ///
  virtual array_section_dof_map* clone() const;

  ///
  /// Copy constructor
  ///
  array_section_dof_map(const array_section_dof_map& xother);

  ///
  /// Virtual copy constructor.
  ///
  virtual array_section_dof_map* copy() const;

  ///
  /// Assignment operator
  ///
  array_section_dof_map& operator=(const array_section_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~array_section_dof_map();

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
  array_section_dof_map(sec_rep_space* xhost, void* xdofs = 0, size_t xdofs_ub = 0);

  ///
  /// Creates a dof map for a (possibly partial) section of sec_rep_space xhost
  /// on version xversion of the base space member identified by xbase_id.
  /// If xdofs is non zero, it will be used for dof storage,
  /// otherwise storage will be allocated
  ///
  array_section_dof_map(sec_rep_space* xhost,
                        pod_index_type xbase_id,
                        int xversion,
                        void* xdofs = 0,
                        size_t xdofs_ub = 0);

  ///
  /// Creates a dof map for a (possibly partial) section of sec_rep_space xhost
  /// on version xversion of the base space member identified by xbase_id.
  /// If xdofs is non zero, it will be used for dof storage,
  /// otherwise storage will be allocated
  ///
  array_section_dof_map(sec_rep_space* xhost,
                        const scoped_index& xbase_id,
                        int xversion,
                        void* xdofs = 0,
                        size_t xdofs_ub = 0);  

  ///
  /// An identifer for the type of dof tuple this is.
  ///
  virtual dof_tuple_type type_id() const
  {
    return ARRAY_SECTION_DOF_TUPLE_ID;
  };

  using section_dof_map::get_dof;
  using section_dof_map::put_dof;

  // ===========================================================
  /// @name NEW DOF ACCESS FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if the dof asociated with id xdof_id
  /// is within the current capacity of the dofs storage.
  ///
  virtual bool dof_in_bounds(pod_index_type xdof_id, bool xis_table_dofs) const;

  ///
  /// True if and only if the dof asociated with 
  /// discretization id xdisc_id and fiber dof id xfiber_id
  /// is within the current capacity of the dofs storage.
  ///
  virtual bool dof_in_bounds(pod_index_type xdisc_id, pod_index_type xfiber_id, bool xis_table_dofs) const;
 
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
  /// True if and only if the fiber asociated with discretization id xdisc_id
  /// is within the current capacity of the dofs storage.
  ///
  virtual bool fiber_in_bounds(pod_index_type xdisc_id, bool xis_table_dofs) const;

  ///
  /// Ensures this has the capacity to store the fiber with discretization id xdisc_id.
  ///
  void reserve_fiber(pod_index_type xdisc_id);
 
  ///
  /// Sets xfiber to the fiber referred to by discretization id xdisc_id.
  ///
  virtual void get_fiber(pod_index_type xdisc_id, void* xfiber, size_type xfiber_size) const;

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  virtual void put_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size);

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber;
  /// allocates memory if necessary.
  ///
  virtual void force_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size);
 
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
  void* dof_ptr(pod_index_type xdof_id, bool xis_table_dofs) const
  {
    return _dofs + schema().offset(xdof_id, xis_table_dofs);
  }

  ///
  /// Pointer to dof referred to be xdisc_id, xfiber_dof_id.
  //
  void* dof_ptr(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dofs) const
  {
    return _dofs + schema().offset(xdisc_id, xfiber_dof_id, xis_table_dofs);
  }
  
    
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


protected:

  ///
  /// Allocates dof storage.
  ///
  virtual void allocate_dofs();

private:

  ///
  /// The number of dofs in the fiber.
  ///
  int _fiber_dof_ct;

  ///
  /// The number of dofs associated with each (disc member, fiber jim) pair.
  ///
  int _local_ct;

  
  // Needed for fiber_bundle::array_section_dof_map::copy_dof(const scoped_index&, const scoped_index&,
  //                                                          const scoped_index&, bool, void*, size_t, bool) const

  ///
  /// The descriptor of the dof transferred
  /// in the preceeding call to copy_dof.
  ///
  mutable dof_descriptor_array::dof_descriptor* _xfr_desc;

  ///
  /// Storage for the dofs.
  ///
  char* _dofs;

  ///
  /// True if this allocated _dofs and hence should delete it.
  ///
  bool _this_owns_dofs;

  ///
  /// Initializes dof storage.
  ///
  void init_dofs(void* xdofs, size_t xdofs_ub);

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  ///
  /// Ensures that dof_tuple_ub() is at least xdof_tuple_ub.
  ///
  void reserve(size_t xdof_tuple_ub);
};

} // namespace fiber_bundle

#endif // ifndef ARRAY_SECTION_DOF_MAP_H
