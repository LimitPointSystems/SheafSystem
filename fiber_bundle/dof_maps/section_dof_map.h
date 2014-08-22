
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

// Interface for class section_dof_map;
// map from sec_rep_space client dof id to dof value

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SECTION_DOF_MAP_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SECTION_DOF_MAP_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_DOF_MAP_H
#include "ComLimitPoint/sheaf/poset_dof_map.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_REP_SPACE_H
#include "ComLimitPoint/fiber_bundle/sec_rep_space.h"
#endif

namespace sheaf
{
class poset_state_handle;
}

namespace fiber_bundle
{

using namespace sheaf;


///
/// The abstract map from section dof ids
/// to section dof values of heterogeneous type.
///
class SHEAF_DLL_SPEC section_dof_map : public poset_dof_map
{
  friend class sec_rep_space_member;

public:

  ///
  /// The name of the actual (possibly derived) class of this instance.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();

  // CANONICAL MEMBERS

  ///
  /// Assignment operator
  ///
  section_dof_map& operator=(const section_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~section_dof_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // MAP INTERFACE

  ///
  /// The poset which hosts member()
  ///
  virtual sec_rep_space* host() const;

  ///
  /// The schema on which this is allocated (mutable version).
  ///
  virtual section_space_schema_member& schema();

  ///
  /// The schema on which this is allocated (const version).
  ///
  virtual const section_space_schema_member& schema() const;
  
  using poset_dof_map::get_dof;
  using poset_dof_map::put_dof;

  // ===========================================================
  //  NEW DOF ACCESS FACET
  // ===========================================================


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
  /// Copies the dof referred to by xdisc_id, xfiber_dof_id into xdof.
  ///
  virtual void get_dof(pod_index_type xdisc_id, 
		       pod_index_type xfiber_dof_id, 
		       void* xdof, 
		       size_type xdof_size) const = 0;

  /// @hack: get_dof(pod_index_type, pod_index_type, void*, size_type) const 
  /// has an implicit 0-th argument const section_dof_map*.
  /// When called on a non-const section_dof_map, a conversion is required
  /// on the implicit first argument. This triggers the C++ argument
  /// matching rules, which conclude there is an ambiguity with the old signature
  /// get_dof(const scoped_index&, bool, void*, size_t), even though
  /// the explicit arguments in the call appear to be an exact match.
  /// The following signature can be removed when the conflicting old signature is removed.

  void get_dof(pod_index_type xdisc_id, 
	       pod_index_type xfiber_dof_id, 
	       void* xdof, 
	       size_type xdof_size)
  {
    const section_dof_map* lthis = this;
    lthis->get_dof(xdisc_id, xfiber_dof_id, xdof, xdof_size);
  };
 
  ///
  /// Copies the dof referred to by xdisc_id, xfiber_dof_id into xdof.
  ///
  void get_dof(const scoped_index& xdisc_id, 
	       const scoped_index& xfiber_dof_id, 
	       void* xdof, 
	       size_type xdof_size) const;
 
  /// @hack: get_dof(const scoped_index&, const scoped_index&, void*, size_type) const 
  /// has an implicit 0-th argument const section_dof_map*.
  /// When called on a non-const section_dof_map, a conversion is required
  /// on the implicit first argument. This triggers the C++ argument
  /// matching rules, which conclude there is an ambiguity with the old signature
  /// get_dof(const scoped_index&, bool, void*, size_t), even though
  /// the explicit arguments in the call appear to be an exact match.
  /// This signature can be removed when the conflicting old signature is removed.

  void get_dof(const scoped_index& xdisc_id, 
	       const scoped_index& xfiber_dof_id, 
	       void* xdof, 
	       size_type xdof_size)
  {
    const section_dof_map* lthis = this;
    lthis->get_dof(xdisc_id, xfiber_dof_id, xdof, xdof_size);
  };

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  virtual void put_dof(pod_index_type xdisc_id, 
		       pod_index_type xfiber_dof_id, 
		       const void* xdof, 
		       size_type xdof_size) = 0;

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  void put_dof(const scoped_index& xdisc_id, 
	       const scoped_index& xfiber_dof_id, 
	       const void* xdof, 
	       size_type xdof_size);

  ///
  /// True if and only if the fiber asociated with discretization id xdisc_id
  /// is within the current capacity of the dofs storage.
  ///
  virtual bool fiber_in_bounds(pod_index_type xdisc_id, bool xis_table_dofs) const;
 
  ///
  /// Sets xfiber to the fiber referred to by discretization id xdisc_id.
  ///
  virtual void get_fiber(pod_index_type xdisc_id, void* xfiber, size_type xfiber_size) const;

  ///
  /// Sets xfiber to the fiber referred to by discretization id xdisc_id.
  ///
  void get_fiber(const scoped_index& xdisc_id, void* xfiber, size_type xfiber_size) const;

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  virtual void put_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size) = 0;

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  void put_fiber(const scoped_index& xdisc_id, const void* xfiber, size_type xfiber_size);

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber;
  /// allocates additional memory if necessary.
  ///
  virtual void force_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size);

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber;
  /// allocates additional memory if necessary.
  ///
  void force_fiber(const scoped_index& xdisc_id, const void* xfiber, size_type xfiber_size);
 
  ///
  /// Sets xcomponent to the component referred to by fiber id xfiber_dof_id.
  ///
  virtual void get_component(pod_index_type xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const = 0;

  ///
  /// Sets xcomponent to the component referred to by fiber id xfiber_dof_id.
  ///
  void get_component(const scoped_index& xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const;

  ///
  /// Sets the component referred to by fiber id xfiber_dof_id to xcomponent.
  ///
  virtual void put_component(pod_index_type xfiber_dof_id, const void* xcomponent, size_type xcomponent_size) = 0;

  ///
  /// Sets the component referred to by fiber id xfiber_dof_id to xcomponent.
  ///
  void put_component(const scoped_index& xfiber_dof_id, const void* xcomponent, size_type xcomponent_size);
  
  
  
  // ===========================================================
  //  END NEW DOF ACCESS FACET
  // ===========================================================

  // ===========================================================
  // I/O SUPPORT FACET
  // ===========================================================

  ///
  /// True if this dof map type supports dof tuple transfer optimization.
  //// @hack dof tuple transfer hack.
  ////
  virtual bool supports_xfr_opt() const;

protected:

  // CANONICAL MEMBERS

  ///
  /// Default constructor
  ///
  section_dof_map();

  ///
  /// Copy constructor
  ///
  section_dof_map(const section_dof_map& xother);

  // MAP INTERFACE

  ///
  /// Creates a map for a (possibly partial) section of xhost defined
  /// on version xversion of the base space member identified by xbase_id.
  ///
  section_dof_map(sec_rep_space* xhost,
                  pod_index_type xbase_id,
                  int xversion);

private:


};

} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_SECTION_DOF_MAP_H
