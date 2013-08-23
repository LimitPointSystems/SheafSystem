
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

/// @file
/// Interface for class structured_block_1d.

#ifndef STRUCTURED_BLOCK_1D_H
#define STRUCTURED_BLOCK_1D_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STRUCTURED_BLOCK_H
#include "structured_block.h"
#endif

#ifndef STRUCTURED_BLOCK_1D_CRG_INTERVAL_H
#include "structured_block_1d_crg_interval.h"
#endif

#ifndef CHART_POINT_1D_H
#include "chart_point_1d.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

///
/// A homogeneous collection of connected segments
/// arranged in an i_size() array.
///
class SHEAF_DLL_SPEC structured_block_1d : public structured_block
{

  friend class structured_block_1d_crg_interval;

  // ===========================================================
  /// @name STRUCTURED_BLOCK_1D FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached structured_block_1d handle.
  ///
  structured_block_1d();

  ///
  /// Copy constructor; creates a new structured_block_1d handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit structured_block_1d(const abstract_poset_member& xother,
                               bool xnew_jem = false);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~structured_block_1d();

  // NEW HANDLE, NEW STATE CONSTRUCTORS:

  ///
  /// Creates a new handle attached to a new state in xhost with
  /// i_size() == xi_size.
  ///
  structured_block_1d(poset* xhost,
                      const size_type& xi_size,
                      bool xauto_access);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS:

  ///
  /// Creates a new structured_block_1d handle attached to the member state
  /// with hub id xhub_id in xhost.
  ///
  structured_block_1d(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new structured_block_1d handle attached to the member state
  /// with id xid in xhost
  ///
  structured_block_1d(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new structured_block_1d handle attached to the member state
  /// with name xname in xhost
  ///
  structured_block_1d(const poset* xhost, const string& xname);

  ///
  /// Creates a new structured_block_1d handle attached to the member state
  /// specified by xpath in namespace xnamespace.
  ///
  structured_block_1d(const namespace_poset* xnamespace,
                      const poset_path& xpath,
                      bool xauto_access = true);

  ///
  /// Creates a new structured_block_1d handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  structured_block_1d(const namespace_poset* xnamespace,
                      pod_index_type xposet_id,
                      pod_index_type xmember_id);

  ///
  /// Creates a new structured_block_1d handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  structured_block_1d(const namespace_poset* xnamespace,
                      const scoped_index& xposet_id,
                      const scoped_index& xmember_id);


  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS":

  ///
  /// Creates a new structured_block_1d state in host() with
  /// i_size() == xi_size and attaches this to it.
  /// Synonym for new_state(host(), xi_size).
  ///
  void new_state(const size_type& xi_size, bool xauto_access = true);

  ///
  /// Creates a new structured_block_1d state in xhost with
  /// i_size() == xi_size and attaches this to it.
  ///
  void new_state(poset* xhost, const size_type& xi_size, bool xauto_access = true);

  // FEATURES:

  ///
  /// The dimension of this block; static const version.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {DB = 1};  

  ///
  /// The number of local cells (zones) in the i direction.
  /// The number of vertices in the i direction is i_size() + 1.
  ///
  size_type i_size() const;

protected:

  ///
  /// The type of row dof tuple for this.
  ///
  struct SHEAF_DLL_SPEC row_dof_tuple_type
  {
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
    const char * local_cell_type_name;

    ///
    /// The number of local cell instances in this block.
    ///
    size_type size;

    ///
    /// The upper bound for index_0.
    ///
    size_type i_size;
  };

  ///
  /// The row dof tuple for this.
  ///
  inline row_dof_tuple_type* row_dof_tuple()
  {
    return reinterpret_cast<row_dof_tuple_type*>(dof_map().dof_tuple());
  };

  ///
  /// Initializes handle data members when attaching
  /// to a different member of the same host.
  ///
  virtual void attach_handle_data_members();

  using structured_block::new_row_dof_map;

  ///
  /// Creates a new row dof map and initializes it.
  ///
  static scoped_index new_row_dof_map(poset_state_handle& xhost,
				      size_type xi_size,
				      bool xauto_access);

private:

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
  chart_point_1d* refine_point(const chart_point& xpt) const
  {
    return reinterpret_cast<chart_point_1d*>(structured_block::refine_point(xpt));
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
  chart_point_1d* unrefine_point(const chart_point& xpt) const
  {
    return reinterpret_cast<chart_point_1d*>(structured_block::refine_point(xpt));
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
  /// The implicit interval member for this block.
  ///
  virtual const structured_block_1d_crg_interval& interval() const;

  ///
  /// The path of the local cell prototype required by this class.
  ///
  static const poset_path& static_local_cell_prototype_path();

protected:

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_MEMBER FACET
  // ===========================================================
  //@{

public:

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
  /// The path of the prototype required by this class.
  ///
  static const poset_path& static_prototype_path();

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
  virtual structured_block_1d* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline structured_block_1d* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<structured_block_1d*>(structured_block::clone(xnew_state, xauto_access));
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
  inline structured_block_1d* greatest_jem() const
  {
    return static_cast<structured_block_1d*>(base_space_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline structured_block_1d* least_jem() const
  {
    return static_cast<structured_block_1d*>(base_space_member::least_jem());
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
  inline structured_block_1d* p_join(abstract_poset_member* other) const
  {
    return static_cast<structured_block_1d*>(base_space_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline structured_block_1d* p_meet(abstract_poset_member* other)
  {
    return static_cast<structured_block_1d*>(base_space_member::p_meet(other));
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
  inline structured_block_1d* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<structured_block_1d*>(base_space_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline structured_block_1d* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<structured_block_1d*>(base_space_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline structured_block_1d* l_not(bool xnew_jem = true) const
  {
    return static_cast<structured_block_1d*>(base_space_member::l_not(xnew_jem));
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
  virtual structured_block_1d& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  structured_block_1d& operator=(const structured_block_1d& xother);

protected:

private:

  //@}
};

} // namespace fiber_bundle

#endif // STRUCTURED_BLOCK_1D_H
