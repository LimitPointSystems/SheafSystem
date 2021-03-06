
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
/// Interface for class st2_e3.

#ifndef ST2_E3_H
#define ST2_E3_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ST2_H
#include "SheafSystem/st2.h"
#endif

#ifndef SYMMETRIC_MATRIX_3X3_H
#include "SheafSystem/symmetric_matrix_3x3.h"
#endif

#ifndef E3_H
#include "SheafSystem/e3.h"
#endif

namespace fiber_bundle
{

class gl3_lite;

//==============================================================================
// CLASS ST2_E3_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class st2_e3.
///
template <typename T>
class st2_e3_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef st2_e3_row_dofs_type<T> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef symmetric_matrix_3x3<T> matrix_type;

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
  /// (const version).
  ///
  const T& operator[] (int xindex) const;

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (non const version). 
  ///
  operator typename st2_e3_row_dofs_type<T>::matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const typename st2_e3_row_dofs_type<T>::matrix_type& () const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  st2_e3_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  st2_e3_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The xx, xy, xz, yy, yz, zz dofs.
  ///
  /// components[0] => xx
  /// components[1] => xy
  /// components[2] => xz
  /// components[3] => yy
  /// components[4] => yz
  /// components[5] => zz
  ///
  T components[6];

protected:
private:

};


//==============================================================================
// CLASS ST2_E3_LITE
//==============================================================================

class e3_lite;

///
/// A symmetric tensor of degree 2 over a Euclidean vector space of dimension 3
/// (volatile version).
///
class SHEAF_DLL_SPEC st2_e3_lite : public st2_lite
{
  //============================================================================
  /// @name ST2_E3 FACET OF CLASS ST2_E3_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef st2_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef st2_e3_row_dofs_type<double>::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  st2_e3_lite();

  ///
  /// Copy constructor.
  ///
  st2_e3_lite(const st2_e3_lite& xother);

  ///
  /// Assignment operator.
  ///
  st2_e3_lite& operator=(const st2_e3_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~st2_e3_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  st2_e3_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  st2_e3_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with matrix type xmatrix.
  ///
  st2_e3_lite(const matrix_type& xmatrix);

  ///
  /// Assignment (from a matrix type) operator.
  ///
  st2_e3_lite& operator=(const matrix_type& xmatrix);

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
  /// Conversion (cast) operator to convert to the associated row dofs typey
  /// (const version). 
  ///
  operator const row_dofs_type& () const;

  ///
  /// Creates a new instance with row dofs xx, xy, xz, yy, yz, zz.
  ///
  st2_e3_lite(const value_type& xx, const value_type& xy, const value_type& xz,
              const value_type& yy, const value_type& yz, const value_type& zz);


  using st2_lite::put_components;
  
  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(const value_type& xx_comp,
                              const value_type& xy_comp,
                              const value_type& xz_comp,
                              const value_type& yy_comp,
                              const value_type& yz_comp,
                              const value_type& zz_comp);

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (ST2) FACET OF CLASS ST2_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS ST2_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ST2_E3_LITE
  //============================================================================
  //@{

public:

  ///
  /// Type of underlying vector space.
  ///
  typedef e3_lite vector_space_type;

  ///
  /// Dimension of the underlying vector space.
  ///
  virtual int dd() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ST2_E3_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST2_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST2_E3_LITE
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
  virtual st2_e3_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual st2_e3_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ST2_E3_LITE
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
// CLASS ST2_E3
//==============================================================================

///@issue Is this class named correctly, is the underlying vector space
///       really E3 or just R3?

///
/// A symmetric tensor of degree 2 over a Euclidean vector space of dimension 3
/// (persistent version).
///
class SHEAF_DLL_SPEC st2_e3 : public st2
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS ST2_E3
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
  /// The host with path standard_host_path<st2_e3>(xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name ST2_E3 FACET OF CLASS ST2_E3
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef st2_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef st2_e3_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e3 vector_space_type;

  ///
  /// Default constructor.
  ///
  st2_e3();

  ///
  /// Creates a new handle attached to a new jim state in xhost.
  ///
  st2_e3(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  st2_e3(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  st2_e3& operator=(const row_dofs_type& xrdt);

  ///
  /// Creates a new st2_e3 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  st2_e3(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new st2_e3 handle attached to the member state with id xid
  /// in xhost.
  ///
  st2_e3(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new st2_e3 handle attached to the member state with name xname
  /// in xhost.
  ///
  st2_e3(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new st2_e3 handle attached to the same state as xother.
  ///
  explicit st2_e3(abstract_poset_member* xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual st2_e3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  st2_e3& operator=(const st2_e3& xother);

  ///
  /// Destructor.
  ///
  ~st2_e3();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;


  using st2::put_components;
  
  ///
  /// Sets values of the components to the given arguments.
  ///
  virtual void put_components(
    dof_type xx_comp, dof_type xy_comp, dof_type xz_comp,
    dof_type yy_comp, dof_type yz_comp, dof_type zz_comp);

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
  /// @name ST2 FACET OF CLASS ST2_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS ST2_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS ST2_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS ST2_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}



  //============================================================================
  /// @name TUPLE FACET OF CLASS ST2_E3
  //============================================================================
  //@{

public:

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

protected:
private:

  //@}


  //===========================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST2_E3
  //===========================================================================
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
  virtual st2_e3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline st2_e3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<st2_e3*>(st2::clone(xnew_state, xauto_access));
  }


protected:
private:

  //@}


  //===========================================================================
  /// @name ANY FACET OF CLASS ST2_E3
  //===========================================================================
  //@{

public:

  ///
  /// True if other conforms to current.
  ///
  bool is_ancestor_of(const any* other) const;

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
/// Insert st2_e3_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
std::ostream& operator<<(std::ostream& xos, const st2_e3_row_dofs_type<T>& xrdt);

//==============================================================================
// VD FACET
//==============================================================================

namespace vd_algebra
{

/// @hack Need to move this to vd.h.

///
/// Transform the basis and components of xv by xtransform.
///
SHEAF_DLL_SPEC void transform_basis_by(st2_e3_lite& xv, const gl3_lite& xtransform, bool is_contravariant);
  
} // namespace vd_algebra

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
SHEAF_DLL_SPEC void determinant(const st2_e3& x0, vd_value_type& xresult, bool xauto_access);

///
/// The determinant of a symmetric tensor
/// (auto-allocated version for persistent types).
///
SHEAF_DLL_SPEC vd_value_type determinant(const st2_e3& x0, bool xauto_access);

///
/// The determinant of a symmetric tensor
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void determinant(const st2_e3_lite& x0, vd_value_type& xresult);

///
/// The determinant of a symmetric tensor
/// (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC vd_value_type determinant(const st2_e3_lite& x0);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

// ===========================================================
// TEMPLATE SPECIALIZATIONS
// ===========================================================

///
/// Computes the principal axes basis for xlite. Returns the diagonalization in
/// xresult and the transform in xtransform (pre-allocated).
/// Specialization for st2_e3_lite.
///
template <> SHEAF_DLL_SPEC void to_principal_axes(const st2_e3_lite& xlite, gl3_lite& xtransform, st2_e3_lite& xresult);
  
} // namespace st2_algebra

} // namespace fiber_bundle

#endif // ifndef ST2_E3_H
