
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

// Interface for class UNSTRUCTURED_BLOCK

#ifndef UNSTRUCTURED_BLOCK_H
#define UNSTRUCTURED_BLOCK_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef HOMOGENEOUS_BLOCK_H
#include "SheafSystem/homogeneous_block.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

class unstructured_block_builder;

///
/// OBSOLETE: use zone_nodes_block or point_block_*d.
/// A client handle for a base space member which represents
/// a "unstructured" homogeneous collection of local cells.
/// $$HACK: unstructured_block hack; must use unstructured_block::new_host
// to create the host poset for instances of this class.
///
class SHEAF_DLL_SPEC unstructured_block : public homogeneous_block
{

  friend class unstructured_block_builder;

public:

  // ===========================================================
  // HOST FACTORY FACET
  // ===========================================================

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
  

  // ===========================================================
  // ANY FACET
  // ===========================================================

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
  virtual unstructured_block& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  unstructured_block& operator=(const unstructured_block& xother);

  // ===========================================================
  // ABSTRACT POSET MEMBER FACET
  // ===========================================================

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual unstructured_block* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline unstructured_block* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<unstructured_block*>(homogeneous_block::clone(xnew_state, xauto_access));
  }

  // ===========================================================
  // ORDERING RELATION FACET
  // ===========================================================

  ///
  /// The largest member which is join-equivalent to this
  ///
  inline unstructured_block* greatest_jem() const
  {
    return static_cast<unstructured_block*>(homogeneous_block::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline unstructured_block* least_jem() const
  {
    return static_cast<unstructured_block*>(homogeneous_block::least_jem());
  };


  // ===========================================================
  // POSET ALGEBRA FACET
  // ===========================================================

  ///
  /// poset join of this with other, auto-, pre-, and self-allocated versions
  /// the poset join is the least upper bound in the poset
  ///
  inline unstructured_block* p_join(abstract_poset_member* other) const
  {
    return static_cast<unstructured_block*>(homogeneous_block::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline unstructured_block* p_meet(abstract_poset_member* other)
  {
    return static_cast<unstructured_block*>(homogeneous_block::p_meet(other));
  };


  // ===========================================================
  // LATTICE ALGEBRA FACET
  // ===========================================================

  ///
  /// lattice join of this with other, auto-, pre-, and self-allocated versions
  /// the lattice join is the least upper bound in the lattice generated by the
  /// jims in the poset
  ///
  inline unstructured_block* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<unstructured_block*>(homogeneous_block::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline unstructured_block* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<unstructured_block*>(homogeneous_block::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline unstructured_block* l_not(bool xnew_jem = true) const
  {
    return static_cast<unstructured_block*>(homogeneous_block::l_not(xnew_jem));
  };


  // ===========================================================
  // UNSTRUCTURED_BLOCK FACET
  // ===========================================================

  ///
  /// The dimension of this block; static const version.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {DB = -1};  

  // ===========================================================
  // CANONICAL CONSTRUCTORS
  // ===========================================================

  ///
  /// Default constructor; creates a new, unattached unstructured_block handle.
  ///
  unstructured_block();

  ///
  /// Copy constructor; creates a new unstructured_block handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit unstructured_block(const abstract_poset_member& xother,
                              bool xnew_jem = false);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~unstructured_block();

  // ===========================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  // ===========================================================

  ///
  /// Creates a new handle attached to a new jim state in xhost
  /// with local cell prototype specified by xlocal_cell_prototype_path.
  /// Xis_prototype_name is present only to distinguish
  /// the signature of this constructor from the existing state
  /// constructor below and is ignored
  ///
  //*/
  unstructured_block(poset* xhost,
                     const std::string& xlocal_cell_prototype_name,
                     bool xis_prototype_name,
                     bool xauto_access);

  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// (created from xlocal_cell_prototype_path) and glued together with the
  /// atomic equivalences ("element connectivity") in xids.
  ///
  unstructured_block(poset* xhost,
                     const poset_path& xlocal_cell_prototype_path,
                     const scoped_index* xids,
                     int xub,
                     bool xauto_access);


  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// glued together with the atomic equivalences ("element connectivity") in xids.
  ///
  unstructured_block(poset* xhost,
                     const base_space_member& xlocal_cell_prototype,
                     const scoped_index* xids,
                     int xub,
                     bool xauto_access);

  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// (created from xlocal_cell_prototype_path) and glued together with the
  /// atomic equivalences ("element connectivity") in xids.
  ///
  unstructured_block(poset* xhost,
                     const poset_path& xlocal_cell_prototype_path,
                     const pod_index_type* xids,
                     int xub,
                     bool xauto_access);


  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// glued together with the atomic equivalences ("element connectivity") in xids.
  ///
  unstructured_block(poset* xhost,
                     const base_space_member& xlocal_cell_prototype,
                     const pod_index_type* xids,
                     int xub,
                     bool xauto_access);

  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// (created from xlocal_cell_prototype_path) and glued together with the
  /// atomic equivalences ("element connectivity") generated for the one-dimensional
  /// case with xi_size segments.
  ///
  unstructured_block(poset* xhost,
                     const poset_path& xlocal_cell_prototype_path,
                     const size_type& xi_size,
                     bool xauto_access = true);


  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// glued together with the atomic equivalences ("element connectivity")
  /// generated for the one-dimensional case with xi_size segments.
  ///
  unstructured_block(poset* xhost,
                     const base_space_member& xlocal_cell_prototype,
                     const size_type& xi_size,
                     bool xauto_access = true);

  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// (created from xlocal_cell_prototype_path) and glued together with the
  /// atomic equivalences ("element connectivity") generated for the two-dimensional
  /// case with xi_size by xj_size edge segments.
  ///
  unstructured_block(poset* xhost,
                     const poset_path& xlocal_cell_prototype_path,
                     const size_type& xi_size,
                     const size_type& xj_size,
                     bool xauto_access = true);


  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// glued together with the atomic equivalences ("element connectivity")
  /// generated for the two-dimensional case with xi_size by xj_size
  /// edge segments.
  ///
  unstructured_block(poset* xhost,
                     const base_space_member& xlocal_cell_prototype,
                     const size_type& xi_size,
                     const size_type& xj_size,
                     bool xauto_access = true);

  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// (created from xlocal_cell_prototype_path) and glued together with the
  /// atomic equivalences ("element connectivity") generated for the three-dimensional
  /// case with xi_size by xj_size by xk_size edge segments.
  ///
  unstructured_block(poset* xhost,
                     const poset_path& xlocal_cell_prototype_path,
                     const size_type& xi_size,
                     const size_type& xj_size,
                     const size_type& xk_size,
                     bool xauto_access = true);


  ///
  /// Creates a new block poset member attached to a new member state in xhost.
  /// The block consists of copies of the down set of xlocal_cell_prototype
  /// glued together with the atomic equivalences ("element connectivity")
  /// generated for the three-dimensional case with xi_size by xj_size by
  /// xk_size edge segments.
  ///
  unstructured_block(poset* xhost,
                     const base_space_member& xlocal_cell_prototype,
                     const size_type& xi_size,
                     const size_type& xj_size,
                     const size_type& xk_size,
                     bool xauto_access = true);


  // ===========================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  // ===========================================================

  ///
  /// Creates a new unstructured_block handle attached to the member state
  /// with index xindex in xhost
  ///
  unstructured_block(const poset* xhost, scoped_index xindex);

  ///
  /// Creates a new unstructured_block handle attached to the member state
  /// with name xname in xhost
  ///
  unstructured_block(const poset* xhost, const std::string& xname);

  ///
  /// Creates a new unstructured_block handle attached to the member state
  /// specifiec by path xpath in namespace xnamespace.
  ///
  unstructured_block(const namespace_poset* xnamespace,
                     const poset_path& xpath,
                     bool xauto_access = true);

  ///
  /// Creates a new unstructured_block handle attached to the member state
  /// with specified by xposet_id, xmember_id in namespace xnamespace.
  ///
  unstructured_block(const namespace_poset* xnamespace,
                     const scoped_index& xposet_id,
                     const scoped_index& xmember_id);

  // ===========================================================
  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"
  // ===========================================================

  ///
  /// Creates a new unrefined (jim) unstructured block state
  /// in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const std::string& xlocal_cell_prototype_name,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in host() and attaches this to it.
  ///
  virtual void new_state(const poset_path& xlocal_cell_prototype_path,
                         const scoped_index* ids,
                         int xub,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(const base_space_member& xlocal_cell_prototype,
                         const scoped_index* ids,
                         int xub,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const poset_path& xlocal_cell_prototype_path,
                         const scoped_index* ids,
                         int xub,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const base_space_member& xlocal_cell_prototype,
                         const scoped_index* ids,
                         int xub,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in host() and attaches this to it.
  ///
  virtual void new_state(const poset_path& xlocal_cell_prototype_path,
                         const pod_index_type* ids,
                         int xub,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(const base_space_member& xlocal_cell_prototype,
                         const pod_index_type* ids,
                         int xub,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const poset_path& xlocal_cell_prototype_path,
                         const pod_index_type* ids,
                         int xub,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const base_space_member& xlocal_cell_prototype,
                         const pod_index_type* ids,
                         int xub,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in host() and attaches this to it.
  ///
  virtual void new_state(const poset_path& xlocal_cell_prototype_path,
                         const size_type& xi_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(const base_space_member& xlocal_cell_prototype,
                         const size_type& xi_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const poset_path& xlocal_cell_prototype_path,
                         const size_type& xi_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const base_space_member& xlocal_cell_prototype,
                         const size_type& xi_size,
                         bool xauto_access);


  ///
  /// Creates a new unstructured block state in host() and attaches this to it.
  ///
  virtual void new_state(const poset_path& xlocal_cell_prototype_path,
                         const size_type& xi_size,
                         const size_type& xj_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(const base_space_member& xlocal_cell_prototype,
                         const size_type& xi_size,
                         const size_type& xj_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const poset_path& xlocal_cell_prototype_path,
                         const size_type& xi_size,
                         const size_type& xj_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const base_space_member& xlocal_cell_prototype,
                         const size_type& xi_size,
                         const size_type& xj_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in host() and attaches this to it.
  ///
  virtual void new_state(const poset_path& xlocal_cell_prototype_path,
                         const size_type& xi_size,
                         const size_type& xj_size,
                         const size_type& xk_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(const base_space_member& xlocal_cell_prototype,
                         const size_type& xi_size,
                         const size_type& xj_size,
                         const size_type& xk_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const poset_path& xlocal_cell_prototype_path,
                         const size_type& xi_size,
                         const size_type& xj_size,
                         const size_type& xk_size,
                         bool xauto_access);

  ///
  /// Creates a new unstructured block state in xhost and attaches this to it.
  ///
  virtual void new_state(poset* xhost,
                         const base_space_member& xlocal_cell_prototype,
                         const size_type& xi_size,
                         const size_type& xj_size,
                         const size_type& xk_size,
                         bool xauto_access);

  // ===========================================================
  // ROW DOFS
  // ===========================================================

  // ===========================================================
  // OTHER FEATURES
  // ===========================================================

  ///
  /// Refines this (which must be an atom) into copies of the down set
  /// of the cell specified by xlocal_cell_prototype_path glued together
  /// with the atomic equivalences ("element connectivity") in xids.
  ///
  void refine(const poset_path& xlocal_cell_prototype_path,
              const scoped_index* ids,
              int xub,
              bool xauto_access);

  ///
  /// Refines this (which must be an atom) into copies of the down set
  /// of the cell xlocal_cell_prototype glued together
  /// with the atomic equivalences ("element connectivity") in xids.
  ///
  void refine(const base_space_member& xlocal_cell_prototype,
              const scoped_index* ids,
              int xub,
              bool xauto_access);

  ///
  /// True if host created with unstructured_block::new_host.
  /// $$HACK: unstructured_block hack; checks for persistent subposets.
  ///
  static bool host_created_with_new_host(const poset_state_handle& xhost);
  
  ///
  /// Make the standard subposets created by base_space_poset persistent
  ///
  static void make_standard_subposets_persistent(poset_state_handle& xhost);

protected:

private:

};
 
} // namespace fiber_bundle

#endif // UNSTRUCTURED_BLOCK_H
