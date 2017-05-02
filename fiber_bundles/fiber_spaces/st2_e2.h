
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
/// Interface for class st2_e2.

#ifndef ST2_E2_H
#define ST2_E2_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ST2_H
#include "SheafSystem/st2.h"
#endif

#ifndef SYMMETRIC_MATRIX_2X2_H
#include "SheafSystem/symmetric_matrix_2x2.h"
#endif

#ifndef E2_H
#include "SheafSystem/e2.h"
#endif

namespace fiber_bundle
{

class gl2_lite;

//==============================================================================
// CLASS ST2_E2_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class st2_e2.
///
template <typename T>
class st2_e2_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef st2_e2_row_dofs_type<T> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef symmetric_matrix_2x2<T> matrix_type;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
  ///
  /// The dimension of the row dof components.
  ///
  static int d();

  ///
  /// Value of xindex-th component (row dof)
  /// (non const version).
  ///
  T& operator[] (int xindex);

  ///
  /// Value of xindex-th component (row dof)
  /// (const version)
  ///
  const T& operator[] (int xindex) const;

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (non const version). 
  ///
  operator typename st2_e2_row_dofs_type<T>::matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const typename st2_e2_row_dofs_type<T>::matrix_type& () const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  st2_e2_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  st2_e2_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// Assignment to array of type dof_type.
  ///
  //st2_e2_row_dofs_type<T>& operator=(const dof_type* xcomponents);
 
  ///
  /// The xx, xy and yy dofs.
  ///
  /// components[0] => xx
  /// components[1] => xy
  /// components[2] => yy
  ///
  T components[3];

protected:
private:

};


//==============================================================================
// CLASS ST2_E2_LITE
//==============================================================================

class e2_lite;

///
/// A symmetric tensor of degree 2 over a Euclidean vector space of dimension 2
/// (volatile version).
///
class SHEAF_DLL_SPEC st2_e2_lite : public st2_lite
{
  //============================================================================
  /// @name ST2_E2 FACET OF CLASS ST2_E2_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef st2_e2_row_dofs_type<double> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef row_dofs_type::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  st2_e2_lite();

  ///
  /// Copy constructor.
  ///
  st2_e2_lite(const st2_e2_lite& xother);

  ///
  /// Assignment operator.
  ///
  st2_e2_lite& operator=(const st2_e2_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~st2_e2_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  st2_e2_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  st2_e2_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with matrix type xmatrix.
  ///
  st2_e2_lite(const matrix_type& xmatrix);

  ///
  /// Assignment (from a matrix type) operator.
  ///
  st2_e2_lite& operator=(const matrix_type& xmatrix);

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (non const version). 
  ///
  operator matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const matrix_type& () const;

  ///
  /// Conversion (cast) operator to convert to the associated row dofs type
  /// (non const version). 
  ///
  operator row_dofs_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated row dofs type
  /// (const version). 
  ///
  operator const row_dofs_type& () const;

  ///
  /// Creates a new instance with components xx, xy, yy.
  ///
  st2_e2_lite(const value_type& xx_comp,
              const value_type& xy_comp,
              const value_type& yy_comp);

  using st2_lite::put_components;

  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(const value_type& xx_comp,
                              const value_type& xy_comp,
                              const value_type& yy_comp);

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (ST2) FACET OF CLASS ST2_E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS ST2_E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ST2_E2_LITE
  //============================================================================
  //@{

public:

  ///
  /// Type of underlying vector space.
  ///
  typedef e2_lite vector_space_type;

  ///
  /// Dimension of the underlying vector space.
  ///
  virtual int dd() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ST2_E2_LITE
  //============================================================================
  //@{

public:

  ///
  /// Prototype for general tensors 
  /// of degree xp over this vector space.
  ///
  virtual const tp_lite& tp_prototype(int xp) const;

  ///
  /// Prototype for antisymmetric tensors 
  /// of degree xp over this vector space.
  ///
  virtual const atp_lite& atp_prototype(int xp) const;

  ///
  /// Prototype for symmetric tensors 
  /// of degree xp over this vector space.
  ///
  virtual const stp_lite& stp_prototype(int xp) const;

protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST2_E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST2_E2_LITE
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
  virtual st2_e2_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual st2_e2_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ST2_E2_LITE
  //============================================================================
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

  ///
  /// The row dofs for this instance (mutable version).
  ///
  virtual void* row_dofs();

  ///
  /// The row dofs for this instance (const version).
  ///
  virtual const void* row_dofs() const;

protected:
private:

  //@}
};

//==============================================================================
// CLASS ST2_E2
//==============================================================================

///
/// A symmetric tensor of degree 2 over a Euclidean vector space of dimension 2
/// (persistent version).
///
class SHEAF_DLL_SPEC st2_e2 : public st2
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS ST2_E2
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

  ///
  /// The host with path standard_host_path<st2_e2>(xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name ST2_E2 FACET OF CLASS ST2_E2
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef st2_e2_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef st2_e2_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e2 vector_space_type;

  ///
  /// Virtual constructor for general tensors 
  /// of degree xp over vector space xvector_space.
  ///
  virtual tp* new_tp(int xp, bool xauto_access) const;

  ///
  /// Virtual constructor for antisymmetric tensors 
  /// of degree xp over vector space xvector_space.
  ///
  virtual atp* new_atp(int xp, bool xauto_access) const;

  ///
  /// Virtual constructor for symmetric tensors 
  /// of degree xp over vector space xvector_space.
  ///
  virtual stp* new_stp(int xp, bool xauto_access) const;

  ///
  /// Default constructor.
  ///
  st2_e2();

  ///
  /// Creates a new st2_e2 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  st2_e2(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new st2_e2 handle attached to the member state with id xid
  /// in xhost.
  ///
  st2_e2(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new st2_e2 handle attached to the member state with name xname
  /// in xhost.
  ///
  st2_e2(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new st2_e2 handle attached to the same state as xother.
  ///
  explicit st2_e2(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  st2_e2(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  st2_e2(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  st2_e2& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual st2_e2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  st2_e2& operator=(const st2_e2& xother);

  ///
  /// Destructor.
  ///
  ~st2_e2();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;


protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS ST2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS ST2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ST2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ST2_E2
  //============================================================================
  //@{

public:

  using st2::put_components;
  
  ///
  /// Sets values of the components to the given arguments
  ///
  virtual void put_components(dof_type xx_comp,
                              dof_type xy_comp,
                              dof_type yy_comp);

  ///
  /// Conversion (cast) operator to convert to the associated row dofs type
  /// (non const version). 
  ///
  operator row_dofs_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated row dofs type
  /// (const version). 
  ///
  operator const row_dofs_type& () const;

protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST2_E2
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
  virtual st2_e2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline st2_e2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<st2_e2*>(st2::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ST2_E2
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


///
/// Insert st2_e2_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
std::ostream& operator<<(std::ostream& xos, const st2_e2_row_dofs_type<T>& xrdt);


//==============================================================================
// ST2 FACET
//==============================================================================

namespace st2_algebra
{

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// The determinant of a symmetric tensor
/// (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void determinant(const st2_e2& x0, vd_value_type& xresult, bool xauto_access);

///
/// The determinant of a symmetric tensor
/// (auto-allocated version for persistent types).
///
SHEAF_DLL_SPEC vd_value_type determinant(const st2_e2& x0, bool xauto_access);

///
/// The determinant of a symmetric tensor
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void determinant(const st2_e2_lite& x0, vd_value_type& xresult);

///
/// The determinant of a symmetric tensor
/// (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC vd_value_type determinant(const st2_e2_lite& x0);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

// ===========================================================
// TEMPLATE SPECIALIZATIONS
// ===========================================================

///
/// Computes the principal axes basis for xlite. Returns the diagonalization in
/// xresult and the transform in xtransform (pre-allocated).
/// Specialization for st2_e2_lite.
///
template <> SHEAF_DLL_SPEC void to_principal_axes(const st2_e2_lite& xlite, gl2_lite& xtransform, st2_e2_lite& xresult);

///
/// Computes the principal axes basis for xlite and an associated positive
/// definite tensor xpd_lite, and transforms both into the basis of xlite.
/// The matrix of xlite transforms to the diagonal matrix of the eigenvalues
/// of xlite, and the matrix of the associated positive definite
/// tensor xpd_lite becomes the identity matrix.
/// Specialization for st2_e2_lite.
///
template <> SHEAF_DLL_SPEC void to_principal_axes(const st2_e2_lite& xlite, const st2_e2_lite& xpd_lite, gl2_lite& xtransform, st2_e2_lite& xresult);
  
} // namespace st2_algebra

} // namespace fiber_bundle

#endif // ifndef ST2_E2_H
