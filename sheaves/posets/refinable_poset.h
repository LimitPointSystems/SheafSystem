
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

/// @file
/// Interface for class refinable_poset.

#ifndef REFINABLE_POSET_H
#define REFINABLE_POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

namespace sheaf
{
  
class namespace_poset;

///
/// A client handle for a partially order set that can be refined,
/// that is, a jim can be converted to a jrm by expanding its down set.
///
class SHEAF_DLL_SPEC refinable_poset : public poset
{

  friend class abstract_poset_member;
  friend class block_poset_builder;
  friend class namespace_poset;
  friend class poset_component;
  friend class poset_orderer;
  friend class poset_traverser;
  friend class storage_agent;

  // ===========================================================
  /// @name REFINABLE_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a new poset in namespace xns with path xpath
  /// and schema specified by xschema_path.
  ///
  static refinable_poset& new_table(namespace_type& xhost, 
				    const poset_path& xpath, 
				    const poset_path& xschema_path,
				    bool xauto_access);

  ///
  /// Set the current level to xversion
  ///
  void put_version(int xversion);

  ///
  /// The coarsest common refinement of all versions.
  ///
  subposet& coarsest_common_refinement();

  ///
  /// The coarsest common refinement of all versions.
  ///
  const subposet& coarsest_common_refinement() const;

  ///
  /// The jims of the coarsest common refinement.
  ///
  subposet& coarsest_common_refinement_jims();

  ///
  /// The jims of the coarsest common refinement.
  ///
  const subposet& coarsest_common_refinement_jims() const;

  ///
  /// Create a new version and allow editing of jims and jim order relation.
  ///
  virtual void begin_refine_mode(bool xauto_access = true);

  ///
  /// Prevent editing of jims and jim order relation;
  /// synonym for end_jim_edit_mode(xensure_lattice_invariant, xauto_access);
  ///
  virtual void end_refine_mode(bool xensure_lattice_invariant = true,
                               bool xauto_access = true);

protected:

  ///
  /// Default constructor; creates a new refinable_poset handle not attached to any state.
  ///
  refinable_poset();

  ///
  /// Destructor
  ///
  virtual ~refinable_poset();

  ///
  /// Copy constructor; disabled.
  ///
  refinable_poset(const refinable_poset& xother) { };

  ///
  /// Assignment operator; disabled.
  ///
  refinable_poset& operator=(const poset_state_handle& xother)
  {
    return const_cast<refinable_poset&>(*this);
  };

private:

  ///
  /// Creates a new version with id xversion.
  ///
  void new_version(int xversion);

  //@}


  // ===========================================================
  /// @name POSET FACET
  // ===========================================================
  //@{

public:

protected:

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}


  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  // Need to redefine the protected new_member.
  // Need to put using declaration here as opposed to with
  // redeclaration so it won't make the inherited public
  // new_member functions protected.

  /// @hack Using declaration confuses swig into trying to wrap
  /// protected new_member. Can't seem to get swig to ignore
  /// protected member, so don't use using declaration, override
  /// public new_member as well, but just forward to inherited version.

  //  using poset::new_member;

  ///
  /// Create a disconnected member with is_jim == xis_jim and
  /// the dof tuple identified by xdof_tuple_id.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by these routines using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member(bool xis_jim, pod_index_type xdof_tuple_id);

  ///
  /// Create a disconnected member with is_jim == xis_jim and
  /// the dof tuple identified by xdof_tuple_id.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  void new_member(bool xis_jim, const scoped_index& xdof_tuple_id, scoped_index& result)
  {
    poset::new_member(xis_jim, xdof_tuple_id, result);
  }

  ///
  /// Create a disconnected member with is_jim == xis_jim.
  /// If xdof_map != 0, the new member uses it for dof storage,
  /// otherwise it creates an instance of array_poset_dof_map.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  pod_index_type new_member(bool xis_jim, poset_dof_map* xdof_map = 0, bool xcopy_dof_map = false)
  {
    return poset::new_member(xis_jim, xdof_map, xcopy_dof_map);
  };

  ///
  /// Create a disconnected member with is_jim == xis_jim.
  /// If xdof_map != 0, the new member uses it for dof storage,
  /// otherwise it creates an instance of array_poset_dof_map.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  void new_member(bool xis_jim, poset_dof_map* xdof_map,
		  bool xcopy_dof_map, scoped_index& result)
  {
    poset::new_member(xis_jim, xdof_map, xcopy_dof_map, result);
  }

  // Need to redefine the protected new_member_interval.
  // Need to put using declaration here as opposed to with
  // redeclaration so it won't make the inherited public
  // new_member_interval functions protected.

  /// @hack Using declaration confuses swig into trying to wrap
  /// protected new_member_interval. Can't seem to get swig to ignore
  /// protected member, so don't use using declaration, override
  /// public new_member_interval as well, but just forward to inherited version.

  //  using poset::new_member_interval;

  ///
  /// Create a disconnected member interval of type xinterval_type with size xsize,
  /// dof tuple ids xdof_tuple_ids, and interval type specific private data xdata.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member_interval(const std::string& xinterval_type,
					     size_type xsize,
					     const block<pod_index_type>& xdof_tuple_ids,
					     const block<pod_index_type>& xdata)
  {
    return poset::new_member_interval(xinterval_type, xsize, xdof_tuple_ids, xdata);
  };

  ///
  /// Create a disconnected member interval of type xinterval_type with size xsize,
  /// dof tuple ids xdof_tuple_ids, and interval type specific private data xdata.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  void new_member_interval(const std::string& xinterval_type, size_type xsize,
			   const block<pod_index_type>& xdof_tuple_ids,
			   const block<pod_index_type>& xdata,
			   scoped_index& result)
  {
    poset::new_member_interval(xinterval_type, xsize, xdof_tuple_ids, xdata, result);
  }

protected:

  // see description of using declaration hack above.

  ///
  /// Create a disconnected member with index xindex, is_jim == xis_jim and
  /// the dof tuple identified by xdof_tuple_id.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual void new_member(const scoped_index& xindex, 
			  bool xis_jim, 
			  const scoped_index& xdof_tuple_id);

  ///
  /// Create a disconnected member with index xindex and is_jim == xis_jim.
  /// If xdof_map != 0, the new member uses it for dof storage,
  /// otherwise it creates an instance of array_poset_dof_map.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  void new_member(const scoped_index& xindex, 
		  bool xis_jim, 
		  poset_dof_map* xdof_map = 0, 
		  bool xcopy_dof_map = false)
  {
    poset::new_member(xindex.hub_pod(), xis_jim, xdof_map, xcopy_dof_map);
  };

  // Using declaration for new_member_interval in public scope above.

  ///
  /// Create a disconnected member interval of type xinterval_type with size xsize.
  ///
  /// WARNING: this routine leaves the new member interval is a partially
  /// constructed state (see postconditions) and is intended primarily
  /// for use by the i/o subsystem.
  ///
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member_interval(const std::string& xinterval_type, size_type xsize);

  ///
  /// Create a disconnected member interval beginning at index xindex,
  /// of type xinterval_type, and with size xsize.
  ///
  /// WARNING: this routine leaves the new member interval is a partially
  /// constructed state (see postconditions) and is intended primarily
  /// for use by the i/o subsystem.
  ///
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual void new_member_interval(const scoped_index& xindex,
				   const std::string& xinterval_type, 
				   size_type xsize);

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual refinable_poset* clone() const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};
 
} // namespace sheaf

#endif // REFINABLE_POSET_H
