
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
/// Interface for class base_space_member.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_BASE_SPACE_MEMBER_H
#define COM_LIMITPOINT_FIBER_BUNDLE_BASE_SPACE_MEMBER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_TOTAL_POSET_MEMBER_H
#include "ComLimitPoint/sheaf/total_poset_member.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ARRAY_POSET_DOF_MAP_H
#include "ComLimitPoint/sheaf/array_poset_dof_map.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_FIBER_BUNDLE_NAMESPACE_H
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_NAMESPACE_RELATIVE_MEMBER_INDEX_H
#include "ComLimitPoint/sheaf/namespace_relative_member_index.h"
#endif

namespace sheaf
{
  class poset;
}

namespace fiber_bundle
{

class base_space_poset;

using namespace sheaf;


///
/// The type of row dof tuple for base_space_member.
///
class SHEAF_DLL_SPEC base_space_member_row_dof_tuple_type
{
public:

  ///
  /// The base space dimension.
  ///
  int db;

  ///
  /// The cell type id.
  ///
  int type_id;

  ///
  /// The cell type name.
  ///
  const char* type_name;

  ///
  /// The refinement depth.
  ///
  int refinement_depth;

  ///
  /// The local cell type id.
  ///
  int local_cell_type_id;

  ///
  /// The local cell type name.
  ///
  const char* local_cell_type_name;

  ///
  /// The number of local cells.
  ///
  size_type size;

  ///
  /// The upper bound on the x direction index for structured blocks
  ///
  size_type i_size;

  ///
  /// The upper bound on the y direction index for structured blocks
  ///
  size_type j_size;

  ///
  /// The upper bound on the z direction index for structured blocks
  ///
  size_type k_size;

protected:

private:

};

 
///
/// A client handle for a member of a base space poset.
///
class SHEAF_DLL_SPEC base_space_member : public total_poset_member
{

  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of namespace for this type of member.
  ///
  typedef fiber_bundles_namespace namespace_type;

  ///
  /// The type of host poset for this type of member.
  ///
  typedef base_space_poset host_type;

  ///
  /// The path of the schema required by this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// The path of the schema required by this.
  ///
  virtual const poset_path& schema_path() const;

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// The name of the prototypes poset.
  ///
  static const std::string& prototypes_poset_name();

  ///
  /// True, if xhost_path does not exist or is a path
  /// to a poset of type F::host_type.
  ///
  template <typename F>
  SHEAF_DLL_SPEC
  static bool standard_host_is_available(namespace_type& xns, const std::string& xhost_path, bool xauto_access);

  ///
  /// Creates a new host poset for members of this type.
  /// The poset is created in namespace xns with path xhost_path and schema specified by xschema_path.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path, 
			     int xmax_db,
			     bool xauto_access);

  ///
  /// The host with path xhost_path.
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns,
				  const poset_path& xhost_path,
				  int xmax_db,
				  bool xauto_access);
  

protected:

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of rowe dof tuple for this.
  ///
  typedef base_space_member_row_dof_tuple_type row_dof_tuple_type;
  
  ///
  /// Default constructor; creates a new, unattached base_space_member handle.
  ///
  base_space_member();

  ///
  /// Copy constructor; creates a new base_space_member handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit base_space_member(const abstract_poset_member& xother,
                             bool xnew_jem = false,
			     bool xauto_access = true);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~base_space_member();

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a new handle attached to a new jim (join-irreducible member)
  /// state in xhost. ("explicit"  prevents interpretation as implicit
  /// conversion from poset* to base_space_member&)
  ///
  explicit base_space_member(poset* xhost,
                             array_poset_dof_map* xdof_map = 0,
                             bool xcopy_dof_map = false,
                             bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim
  /// state in xhost using the prototype with name xprototype_name.
  /// If xcopy_dof_map or if xhost does not already contain a copy 
  /// of the prototype dof map, create a copy of the dof map,
  /// otherwise just refer to an existing copy.
  ///.
  ///
  base_space_member(base_space_poset* xhost,
                    const std::string& xprototype_name,
                    bool xcopy_dof_map,
                    bool xauto_access);

  ///
  /// Creates a new handle attached to a new jim state in xhost
  /// and initializes it for use as a prototype with type_name xtype_name, 
  /// dimension xdb, and local cell prototype xlocal_cell_name.
  ///
  base_space_member(base_space_poset* xhost,
                    const std::string& xtype_name,
                    int xdb,
                    const std::string& xlocal_cell_name,
                    bool xauto_access);

  ///
  /// Creates a new jrm (join reducible member) attached to a new member state
  /// in xhost The jrm created is the join of the members with the indices
  /// given in xexpansion.
  ///
  base_space_member(poset* xhost,
                    scoped_index* xexpansion,
                    int xexpansion_ct,
                    const tern& xnew_jem,
                    bool xauto_access);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new base_space_member handle attached to the member state
  /// with hub id xhub_id in xhost
  ///
  base_space_member(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new base_space_member handle attached to the member state
  /// with id xid in xhost
  ///
  base_space_member(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new base_space_member handle attached to the member state
  /// with name xname in xhost
  ///
  base_space_member(const poset* xhost, const std::string& xname);

  ///
  /// Creates a new base_space_member handle attached to the member state
  /// with specified by xpath in namespace xnamespace.
  ///
  base_space_member(const namespace_poset* xnamespace, const poset_path& xpath, bool xauto_access);

  ///
  /// Creates a new base_space_member handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  base_space_member(const namespace_poset* xnamespace,
                    const pod_index_type xposet_id,
                    const pod_index_type xmember_id);

  ///
  /// Creates a new base_space_member handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  base_space_member(const namespace_poset* xnamespace,
                    const scoped_index& xposet_id,
                    const scoped_index& xmember_id);

  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS" FACET

  // FEATURES:

  ///
  /// The path of the prototype for this.
  ///
  poset_path prototype_path() const;

  ///
  /// The path of the prototype with id xid in namespace xnamespace.
  /// A convenience function for looking up prototype names.
  ///
  static poset_path prototype_path(const namespace_poset* xnamespace,
                                   const namespace_relative_member_index& xid);

  ///
  /// True if base space member prototypes poset in
  /// the current name space contains a member with name xname.
  ///
  static bool prototype_exists(const std::string& xname, bool xauto_access);

  ///
  /// The row dof tuple for this.
  ///
  row_dof_tuple_type* row_dof_tuple(bool xrequire_write_access = false);

  ///
  /// @deprecated Use scoped_index new_row_dof_map(poset_state_handle&...).
  /// Creates a new row dof map and initializes it
  /// from the prototype with name xprototype_name.
  ///
  static array_poset_dof_map* new_row_dof_map(const poset* xhost, const std::string& xprototype_name);

  ///
  /// Creates a new row dof map and initializes it
  /// from the prototype with name xprototype_name.
  ///
  static const scoped_index& new_row_dof_map(poset_state_handle& xhost,
					     const std::string& xprototype_name,
					     bool xauto_access = true);

protected:

private:

  //@}


  // ===========================================================
  /// @name ROW DOFS FACET
  // ===========================================================
  //@{

public:

  ///
  /// The base space dimension.
  ///
  int db() const;

  ///
  /// The cell type id of this.
  /// The id of the prototype of this in the
  /// "cell_types" id space of the prototypes poset.
  ///
  const pod_index_type& type_id() const;

  ///
  /// The cell type name.
  ///
  const char* type_name() const;

  ///
  /// The refinement depth.
  ///
  int refinement_depth() const;

  ///
  /// Sets the refinement depth to xdepth.
  ///
  void put_refinement_depth(int xdepth);

  ///
  /// The local cell type id.
  ///
  pod_index_type local_cell_type_id() const;

  ///
  /// The local cell type name.
  ///
  const char* local_cell_type_name() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name CELLULAR SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of cells (jims) of each dimension in the down set of this.
  ///
  void d_cells_ct(block<size_type>& xresult, bool xauto_access) const;

  ///
  /// The cellular space psuedo-complement of this, auto-allocated.
  /// The cellular space psuedo-complement is the smallest lattice
  /// member m for which this->l_join(m) == 1. It is also the lattice
  /// member equivalent to the closure of the complement of the member
  /// of the underlying topological space equivalent to this.
  /// Note that the lattice psuedo-complement satisfies this.l_meet(m) == 0
  /// but does not satisfy this.l_join(m) == 1, while the cellular
  /// psuedo-complement satisfies this.l_join(m) == 1 but does not
  /// satisfy this.l_meet(m) == 0. (This and m meet at their boundary.)
  ///
  base_space_member* c_not(bool xauto_access);

  ///
  /// The cellular space psuedo-complement of this, pre-allocated.
  ///
  void c_not_pa(base_space_member& result, bool xauto_access);

  ///
  /// The cellular space difference of this and xother, auto-allocated.
  /// The cellular space difference is defined to be the
  /// smallest lattice member m for which xother.l_join(m) == this.
  /// Note that xother.l_meet(m) != 0 because m and xother
  /// meet at their boundary.
  ///
  base_space_member* c_minus(base_space_member& xother,
                             bool xnew_jem,
                             bool xauto_access);

  ///
  /// The cellular space difference of this and xother, pre-allocated.
  ///
  void c_minus(base_space_member& xother,
               base_space_member& result,
               bool xnew_jem,
               bool xauto_access);

protected:

private:

  //@}


  // ===========================================================
  /// @name COM_LIMITPOINT_SHEAF_TOTAL_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name ABSTRACT_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline base_space_member* clone(bool xnew_state, bool xauto_access = true) const
  {
    return reinterpret_cast<base_space_member*>(total_poset_member::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  // ===========================================================
  /// @name DEGREE OF FREEDOM (DOF) TUPLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The map from client_ids to dof values for this poset member (mutable version)
  ///
  virtual array_poset_dof_map& dof_map(bool xrequire_write_access = false);

  ///
  /// The map from client_ids to dof values for this poset member (const version)
  ///
  virtual const array_poset_dof_map& dof_map(bool xrequire_write_access = false) const;

  ///
  /// True if xdof_map conforms to (is derived from) the type of
  /// dof map required by this handle.
  ///
  virtual bool dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ORDERING RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The largest member which is join-equivalent to this
  ///
  inline base_space_member* greatest_jem() const
  {
    return reinterpret_cast<base_space_member*>(total_poset_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline base_space_member* least_jem() const
  {
    return reinterpret_cast<base_space_member*>(total_poset_member::least_jem());
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// poset join of this with other, auto-, pre-, and self-allocated versions
  /// the poset join is the least upper bound in the poset
  ///
  inline base_space_member* p_join(abstract_poset_member* other) const
  {
    return reinterpret_cast<base_space_member*>(total_poset_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline base_space_member* p_meet(abstract_poset_member* other)
  {
    return reinterpret_cast<base_space_member*>(total_poset_member::p_meet(other));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name LATTICE ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// lattice join of this with other, auto-, pre-, and self-allocated versions
  /// the lattice join is the least upper bound in the lattice generated by the
  /// jims in the poset
  ///
  inline base_space_member* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return reinterpret_cast<base_space_member*>(total_poset_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline base_space_member* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return reinterpret_cast<base_space_member*>(total_poset_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline base_space_member* l_not(bool xnew_jem = true) const
  {
    return reinterpret_cast<base_space_member*>(total_poset_member::l_not(xnew_jem));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET_COMPONENT FACET
  // ===========================================================
  //@{

public:

  /// @todo implement the following. Requires support in the io subsystem.

  //   ///
  //   /// The namespace of host()
  //   ///
  //   virtual fiber_bundles_namespace* name_space();

  //   ///
  //   /// True if other conforms to name_space().
  //   ///
  //   virtual bool namespace_is_ancestor_of(namespace_poset* other);

  //   ///
  //   /// The poset which this is a handle to a member of.
  //   ///
  //   virtual base_space_poset* host();

  ///
  /// The poset which this is a handle to a member of.
  ///
  poset* host() const;

  ///
  /// True if other conforms to host
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* other) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================

public:

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual base_space_member* clone() const;

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual base_space_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  base_space_member& operator=(const base_space_member& xother);

protected:

private:

  //@}
};

} // namespace fiber_bundle

#endif // COM_LIMITPOINT_FIBER_BUNDLE_BASE_SPACE_MEMBER_H
