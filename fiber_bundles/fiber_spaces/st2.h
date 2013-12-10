
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
/// Interface for class st2.

#ifndef ST2_H
#define ST2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STP_H
#include "stp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS ST2_LITE
//==============================================================================

///
/// A general symmetric tensor of degree 2 over an abstract vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC st2_lite : public stp_lite
{
  //===========================================================================
  /// @name ST2 FACET OF CLASS ST2_LITE
  //===========================================================================
  //@{

public:

  ///
  /// The type of component in the fiber;
  /// the scalar type in the fiber vector space.
  ///
  typedef vd_value_type value_type;

  ///
  /// Default constructor.
  ///
  st2_lite();

  ///
  /// Copy constructor.
  ///
  st2_lite(const st2_lite& xother);

  ///
  /// Assignment operator.
  ///
  st2_lite& operator=(const st2_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~st2_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  st2_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  st2_lite& operator=(const row_dofs_type& xrow_dofs);

  using stp_lite::component;
  using stp_lite::put_component;

  ///
  /// The value of the component in a specified row and column.
  ///
  virtual value_type component(int xrow, int xcolumn) const;

  ///
  /// Sets value of a component in a specified row and column.
  ///
  virtual void put_component(int xrow, int xcolumn, value_type xcomp);

  ///
  /// The index into linear storage of the component
  /// in a specified row and column.
  ///
  virtual int index_for_row_column(int xrow, int xcolumn) const;

protected:
private:

  //@}


  //===========================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS ST2_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ST2_LITE
  //===========================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 2};  
  
  ///
  /// Degree of this as an antisymmetric tensor space.
  ///
  virtual int p() const;

protected:
private:

  //@}


  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ST2_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST2_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST2_LITE
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  ///
  virtual st2_lite* clone() const;

protected:
private:

  //@}


  //===========================================================================
  /// @name ANY FACET OF CLASS ST2_LITE
  //===========================================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any_lite& xother) const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;


protected:
private:

  //@}
};

//==============================================================================
// CLASS ST2
//==============================================================================

///
/// A general symmetric tensor of degree 2 over an abstract vector space
/// (persistent version).
///
class SHEAF_DLL_SPEC st2 : public stp
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS ST2
  // ===========================================================
  //@{

public:

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and table attribute vector_space_path specified by xvector_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path,
			     const poset_path& xvector_space_path,
			     bool xauto_access);

protected:

private:

  //@}


  //===========================================================================
  /// @name ST2 FACET OF CLASS ST2
  //===========================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef st2_lite volatile_type;

  ///
  /// Default constructor.
  ///
  st2();

  ///
  /// Creates a new st2 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  st2(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new st2 handle attached to the member state with id xid
  /// in xhost.
  ///
  st2(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new st2 handle attached to the member state with name xname
  /// in xhost.
  ///
  st2(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new st2 handle attached to the same state as xother.
  ///
  explicit st2(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  st2(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual st2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  st2& operator=(const st2& xother);

  ///
  /// Destructor.
  ///
  ~st2();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;


  using stp::component;
  using stp::put_component;

  ///
  /// The component with row index xrow and column index xcolumn.
  ///
  value_type component(int xrow, int xcolumn) const;

  ///
  /// The component with row index xrow and column index xcolumn.
  ///
  value_type component(int xrow, int xcolumn, bool xauto_access) const;

  ///
  /// Sets the component with row index xrow and column index xcolumn to xvalue.
  ///
  void put_component(int xrow, int xcolumn, value_type xvalue);

  ///
  /// Sets the component with row index xrow and column index xcolumn to xvalue.
  ///
  void put_component(int xrow, int xcolumn, value_type xvalue,
                     bool xauto_access);

  ///
  /// Returns index into linear storage of the component
  /// in a specified row and column.
  ///
  virtual int index_for_row_column(int xrow, int xcolumn) const;


protected:
private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS ST2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ST2
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 2};  
  
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ST2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST2
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual st2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline st2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<st2*>(stp::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ST2
  //============================================================================
  //@{

public:


  ///
  /// True if other conforms to current.
  ///
  bool is_ancestor_of(const any* xother) const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;


protected:
private:

  //@}
};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

//==============================================================================
// ST2 FACET
//==============================================================================

///
/// Namespace containing the 2d symmetric tensor algrebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace st2_algebra
{

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// The trace of a symmetric tensor
/// (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void trace(const st2& x0, vd_value_type& xresult, bool xauto_access);

///
/// The trace of a symmetric tensor
/// (auto-allocated version for persistent types).
///
SHEAF_DLL_SPEC vd_value_type trace(const st2& x0, bool xauto_access);

///
/// The trace of a symmetric tensor
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void trace(const st2_lite& x0, vd_value_type& xresult);

///
/// The trace of a symmetric tensor
/// (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC vd_value_type trace(const st2_lite& x0);

///
/// The determinant of a symmetric tensor
/// (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void determinant(const st2& x0, vd_value_type& xresult, bool xauto_access);

///
/// The determinant of a symmetric tensor
/// (auto-allocated version for persistent types).
///
SHEAF_DLL_SPEC vd_value_type determinant(const st2& x0, bool xauto_access);

///
/// The determinant of a symmetric tensor
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void determinant(const st2_lite& x0, vd_value_type& xresult);

///
/// The determinant of a symmetric tensor
/// (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC vd_value_type determinant(const st2_lite& x0);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

//==============================================================================
//==============================================================================

///
/// Computes the principal axes basis for xlite. Returns the diagonalization in
/// the auto-allocated result and the transform in the pre-allocated xtransform.
///
template <typename T, typename GLN>
T* to_principal_axes(const T& xlite, GLN& xtransform);

///
/// Computes the principal axes basis for xlite. Returns the diagonalization in
/// xresult and the transform in xtransform (pre-allocated).
///
template <typename T, typename GLN>
void to_principal_axes(const T& xlite, GLN& xtransform, T& xresult);

///
/// Computes the principal axes basis for xlite and an associated positive
/// definite tensor xpd_lite, and transforms both into the basis of xlite.
/// The matrix of xlite transforms to the diagonal matrix of the eigenvalues
/// of xlite, and the matrix of the associated positive definite
/// tensor xpd_lite becomes the identity matrix.
///
template <typename T, typename GLN>
void
to_principal_axes(const T& xlite, const T& xpd_lite,
                  GLN& xtransform, T& xresult);

} // namespace st2_algebra

} // namespace fiber_bundle

#endif // ifndef ST2_H
