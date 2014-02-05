
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
/// Interface for class Structured_block_3d

#ifndef STRUCTURED_BLOCK_3D_H
#define STRUCTURED_BLOCK_3D_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STRUCTURED_BLOCK_H
#include "structured_block.h"
#endif

#ifndef STRUCTURED_BLOCK_3D_CRG_INTERVAL_H
#include "structured_block_3d_crg_interval.h"
#endif

#ifndef CHART_POINT_3D_H
#include "chart_point_3d.h"
#endif

namespace fiber_bundle
{

///
/// A homogeneous collection of connected hexahedra
/// arranged in an i_size() x j_size() x k_size() array.
///
class SHEAF_DLL_SPEC structured_block_3d : public structured_block
{

  friend class structured_block_3d_crg_interval;

  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The path of the prototype required by this class.
  ///
  static const poset_path& static_prototype_path();

  ///
  /// Creates a new host poset for members of this type.
  /// The poset is created in namespace xns with path xhost_path and schema specified by xschema_path.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path, 
			     bool xauto_access);

  ///
  /// Finds or creates a host poset and any prerequisite posets
  /// for members of this type. The poset is created in namespace xns with path xhost_path
  /// and schema specified by standard_schema_path().
  ///
  static host_type& standard_host(namespace_type& xns, const poset_path& xhost_path, bool xauto_access);

protected:

private:

  //@}


  // ===========================================================
  /// @name STRUCTURED_BLOCK_3D FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached structured_block_3d handle.
  ///
  structured_block_3d();

  ///
  /// Copy constructor; creates a new structured_block_3d handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit structured_block_3d(const abstract_poset_member& xother,
                               bool xnew_jem = false);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~structured_block_3d();

  // NEW HANDLE, NEW STATE CONSTRUCTORS:

  ///
  /// Creates a new handle attached to a new state in xhost, with
  /// upper bound for index 0 == xi_size, upper bound for
  /// index 1 == xj_size, and upper bound for index 2 == xk_size.
  ///
  structured_block_3d(poset* xhost,
                      const size_type& xi_size,
                      const size_type& xj_size,
                      const size_type& xk_size,
                      bool xauto_access = true);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS:

  ///
  /// Creates a new structured_block_3d handle attached to the member state
  /// with hub id xhub_id in xhost.
  ///
  structured_block_3d(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new structured_block_3d handle attached to the member state
  /// with id xid in xhost
  ///
  structured_block_3d(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new structured_block_3d handle attached to the member state
  /// with name xname in xhost
  ///
  structured_block_3d(const poset* xhost, const std::string& xname);

  ///
  /// Creates a new structured_block_3d handle attached to the member state
  /// specified by xpath in namespace xnamespace.
  ///
  structured_block_3d(const namespace_poset* xnamespace,
                      const poset_path& xpath,
                      bool xauto_access = true);

  ///
  /// Creates a new structured_block_3d handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  structured_block_3d(const namespace_poset* xnamespace,
                      const scoped_index& xposet_id,
                      const scoped_index& xmember_id);

  ///
  /// Creates a new structured_block_3d handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  structured_block_3d(const namespace_poset* xnamespace,
                      pod_index_type xposet_id,
                      pod_index_type xmember_id);


  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS":

  ///
  /// Creates a new structured_block_1d state in host() with
  /// i_size() == xi_size, j_size() == xj_size, k_size() == xk_size
  /// and attaches this to it. Synonym for new_state(host(), xi_size, xj_size)
  ///
  void new_state(const size_type& xi_size,
                 const size_type& xj_size,
                 const size_type& xk_size,
                 bool xauto_access = true);

  ///
  /// Creates a new structured_block_1d state in host() with
  /// i_size() == xi_size, j_size() == xj_size, k_size() == xk_size
  /// and attaches this to it. Synonym for new_state(host(), xi_size, xj_size)
  ///
  void new_state(poset* xhost,
                 const size_type& xi_size,
                 const size_type& xj_size,
                 const size_type& xk_size,
                 bool xauto_access = true);


  // FEATURES:

  ///
  /// The dimension of this block; static const version.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {DB = 3};  

  ///
  /// The number of local cells (zones) in the i direction.
  /// The number of vertices in the i direction is i_size() + 1.
  ///
  size_type i_size() const;

  ///
  /// The number of local cells (zones) in the j direction.
  /// The number of vertices in the j direction is j_size() + 1.
  ///
  size_type j_size() const;

  ///
  /// The number of local cells (zones) in the i direction.
  /// The number of vertices in the i direction is i_size() + 1.
  ///
  size_type k_size() const;

protected:

//   ///
//   /// The type of row dof tuple for this.
//   ///
//   struct SHEAF_DLL_SPEC row_dof_tuple_type
//   {
//     ///
//     /// The base space dimension.
//     ///
//     int db;

//     ///
//     /// The cell type id.
//     ///
//     int type_id;

//     ///
//     /// The cell type name.
//     ///
//     const char* type_name;

//     ///
//     /// The refinement depth.
//     ///
//     int refinement_depth;

//     ///
//     /// The local cell type id.
//     ///
//     int local_cell_type_id;

//     ///
//     /// The local cell type name.
//     ///
//     const char * local_cell_type_name;

//     ///
//     /// The number of local cell instances in this block.
//     ///
//     size_type size;

//     ///
//     /// The upper bound for index 0.
//     ///
//     size_type i_size;

//     ///
//     /// The upper bound for index 1.
//     ///
//     size_type j_size;

//     ///
//     /// The upper bound for index 2.
//     ///
//     size_type k_size;
//   };

//   ///
//   /// The row dof tuple for this.
//   ///
//   inline row_dof_tuple_type* row_dof_tuple()
//   {
//     return reinterpret_cast<row_dof_tuple_type*>(dof_map().dof_tuple());
//   };

  using structured_block::new_row_dof_map;

  ///
  /// Creates a new row dof map and initializes it.
  ///
  static scoped_index
  new_row_dof_map(poset_state_handle& xhost,
                  size_type xi_size,
                  size_type xj_size,
                  size_type xk_size,
                  bool xauto_access);

private:

  ///
  /// Computes an offset from i, j, k using the usual array index formula.
  ///
  inline pod_index_type offset(pod_index_type i,
			       pod_index_type j,
			       pod_index_type k) const
  {
    return (i *= j_size()) += j;
  };

  //@}


  // ===========================================================
  /// @name STRUCTURED_BLOCK FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name LOCAL_BASE_SPACE_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The point in the direct refinement of this which is
  /// the same as xpt in this; auto-allocated version.
  ///
  chart_point_3d* refine_point(const chart_point& xpt) const
  {
    return reinterpret_cast<chart_point_3d*>(structured_block::refine_point(xpt));
  };

  ///
  /// The point in the direct refinement of this which is
  /// the same as xpt in this; pre-allocated version
  ///
  virtual void refine_point_pa(const chart_point& xpt, chart_point& result) const;

  ///
  /// All chart points in the direct refinement of this which are
  /// the same as xpt in this; pre-allocated version.
  /// Note that if xpt lies on a zone boundary in the direct refinement,
  /// it lies in more than one zone.
  ///
  virtual void refine_point_pa(const chart_point& xpt,
                               block<chart_point_3d>& result) const;

  ///
  /// The point in this which is the same as xpt in
  /// the direct refinement of this; auto-allocated version
  ///
  chart_point_3d* unrefine_point(const chart_point& xpt) const
  {
    return reinterpret_cast<chart_point_3d*>(structured_block::refine_point(xpt));
  };

  ///
  /// The point in this which is the same as xpt in
  /// the direct refinement of this; pre-allocated version
  ///
  virtual void unrefine_point_pa(const chart_point& xpt, chart_point& result) const;

  ///
  /// Inserts the standard refinement of this into its lower cover
  /// and changes this from a jim to a jrm.
  ///
  virtual void refine();

  ///
  /// Removes the standard refinement of this from its lower cover
  /// and changes this from a jrm to a jim.
  ///
  virtual void unrefine();

  ///
  /// Inserts the standard simplex refinement of this
  /// into its lower cover and changes this from a jim to a jrm.
  ///
  virtual void simplify();

  ///
  /// Removes the standard simplex refinement of this
  /// from its lower cover and changes this from a jrm to a jim.
  ///
  virtual void unsimplify();

protected:

private:

  //@}


  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK FACET
  // ===========================================================
  //@{

public:

  ///
  /// The path of the local cell prototype required by this class.
  ///
  static const poset_path& static_local_cell_prototype_path();

protected:

  ///
  /// The implicit interval member for this block.
  ///
  virtual const structured_block_3d_crg_interval& interval() const;

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_MEMBER FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name TOTAL_POSET_MEMBER FACET
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
  /// Make a new handle, no state instance of current
  ///
  virtual structured_block_3d* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline structured_block_3d* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<structured_block_3d*>(structured_block::clone(xnew_state, xauto_access));
  };

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
  inline structured_block_3d* greatest_jem() const
  {
    return static_cast<structured_block_3d*>(base_space_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline structured_block_3d* least_jem() const
  {
    return static_cast<structured_block_3d*>(base_space_member::least_jem());
  };


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// poset join of this with other, auto-, pre-, and self-allocated versions
  /// the poset join is the least upper bound in the poset
  ///
  inline structured_block_3d* p_join(abstract_poset_member* other) const
  {
    return static_cast<structured_block_3d*>(base_space_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline structured_block_3d* p_meet(abstract_poset_member* other)
  {
    return static_cast<structured_block_3d*>(base_space_member::p_meet(other));
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
  inline structured_block_3d* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<structured_block_3d*>(base_space_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline structured_block_3d* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<structured_block_3d*>(base_space_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline structured_block_3d* l_not(bool xnew_jem = true) const
  {
    return static_cast<structured_block_3d*>(base_space_member::l_not(xnew_jem));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

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
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual structured_block_3d& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  structured_block_3d& operator=(const structured_block_3d& xother);

protected:

private:

  //@}
 };
  
} // namespace fiber_bundle

#endif // STRUCTURED_BLOCK_3D_H
