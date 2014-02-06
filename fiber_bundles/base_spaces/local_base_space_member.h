
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
/// Interface for class local_base_space_member.

#ifndef LOCAL_BASE_SPACE_MEMBER_H
#define LOCAL_BASE_SPACE_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_MEMBER_H
#include "base_space_member.h"
#endif

#ifndef ARRAY_POSET_DOF_MAP_H
#include "array_poset_dof_map.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

class chart_point;

///
/// A client handle for a member of a base space poset.
///
class SHEAF_DLL_SPEC local_base_space_member : public base_space_member
{
  // ===========================================================
  /// @name LOCAL_BASE_SPACE_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The point in the direct refinement of this which is
  /// the same as xpt; auto-allocated version.
  ///
  chart_point* refine_point(const chart_point& xpt) const;

  ///
  /// The point in the direct refinement of this which is
  /// the same as xpt; pre-allocated version
  ///
  virtual void refine_point_pa(const chart_point& xpt, chart_point& result) const = 0;

  ///
  /// The point in this which is the same as xpt in
  /// the direct refinement of this; auto-allocated version
  ///
  chart_point* unrefine_point(const chart_point& xpt) const;

  ///
  /// The point in this which is the same as xpt in
  /// the direct refinement of this; pre-allocated version
  ///
  virtual void unrefine_point_pa(const chart_point& xpt, chart_point& result) const = 0;

  ///
  /// Inserts the standard refinement of this into its lower cover
  /// and changes this from a jim to a jrm.
  ///
  virtual void refine() = 0;

  ///
  /// Removes the standard refinement of this from its lower cover
  /// and changes this from a jrm to a jim.
  ///
  virtual void unrefine() = 0;

  ///
  /// Inserts the standard simplex refinement of this
  /// into its lower cover and changes this from a jim to a jrm.
  ///
  virtual void simplify() = 0;

  ///
  /// Removes the standard simplex refinement of this
  /// from its lower cover and changes this from a jrm to a jim.
  ///
  virtual void unsimplify() = 0;

protected:

  ///
  /// Default constructor; creates a new, unattached local_base_space_member handle.
  ///
  local_base_space_member();

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
  virtual local_base_space_member* clone() const = 0;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline local_base_space_member* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<local_base_space_member*>(base_space_member::clone(xnew_state, xauto_access));
  }

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
  inline local_base_space_member* greatest_jem() const
  {
    return static_cast<local_base_space_member*>(base_space_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline local_base_space_member* least_jem() const
  {
    return static_cast<local_base_space_member*>(base_space_member::least_jem());
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
  inline local_base_space_member* p_join(abstract_poset_member* other) const
  {
    return static_cast<local_base_space_member*>(base_space_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline local_base_space_member* p_meet(abstract_poset_member* other)
  {
    return static_cast<local_base_space_member*>(base_space_member::p_meet(other));
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
  inline local_base_space_member* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<local_base_space_member*>(base_space_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline local_base_space_member* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<local_base_space_member*>(base_space_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline local_base_space_member* l_not(bool xnew_jem = true) const
  {
    return static_cast<local_base_space_member*>(base_space_member::l_not(xnew_jem));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET_COMPONENT FACET
  // ===========================================================
  //@{

public:

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
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual local_base_space_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  local_base_space_member& operator=(const local_base_space_member& xother);

protected:

private:

  //@}
};
 
} // namespace fiber_bundle

#endif // LOCAL_BASE_SPACE_MEMBER_H
