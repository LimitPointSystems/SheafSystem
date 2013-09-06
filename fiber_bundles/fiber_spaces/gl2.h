

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class gl2

#ifndef GL2_H
#define GL2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef GLN_H
#include "gln.h"
#endif

#ifndef GENERAL_MATRIX_2X2_H
#include "general_matrix_2x2.h"
#endif


namespace fiber_bundle
{

  class e2;

//==============================================================================
// CLASS GL2_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class gl2.
///
template <typename T>
class gl2_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef gl2_row_dofs_type<T> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef general_matrix_2x2<T> matrix_type;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();
  
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
  /// Conversion (cast) operator to convert to the associated
  /// basis transformation matrixmatrix type (non const version). 
  ///
  operator typename gl2_row_dofs_type<T>::matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated 
  /// basis transformation matrixmatrix type const version).
  ///
  operator const typename gl2_row_dofs_type<T>::matrix_type& () const;

  ///
  /// The associated basis transformation matrix (non const version).
  ///
  matrix_type& basis_matrix();

  ///
  /// The associated basis transformation matrix (const version).
  ///
  const matrix_type& basis_matrix() const;

  ///
  /// The associated component transformation matrix (non const version).
  ///
  matrix_type& component_matrix();

  ///
  /// The associated component transformation matrix (const version).
  ///
  const matrix_type& component_matrix() const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  gl2_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  gl2_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The dofs in the following order:
  ///
  ///   Basis transformation matrix elements:
  ///
  ///     components[0] => bxx
  ///     components[1] => bxy
  ///     components[2] => byx
  ///     components[3] => byy
  ///
  ///   Component transformation matrix elements:
  ///
  ///     components[4] => cxx
  ///     components[5] => cxy
  ///     components[6] => cyx
  ///     components[7] => cyy
  ///
  T components[8];

protected:
private:

};


//==============================================================================
// CLASS GL2_LITE
//==============================================================================

///
/// The mathematical group GL(2, R).
/// The group of all invertible, linear transformations
/// on the R2, the 2 dimension vector space over the reals.
/// Equivalent to the set of all invertible 2x2 real matrices
/// (volatile version).
///
class SHEAF_DLL_SPEC gl2_lite : public gln_lite
{
  //============================================================================
  /// @name GL2 FACET OF CLASS GL2_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef gl2_row_dofs_type<double> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef gl2_row_dofs_type<double>::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  gl2_lite();

  ///
  /// Copy constructor.
  ///
  gl2_lite(const gl2_lite& xother);

  ///
  /// Assignment operator.
  ///
  gl2_lite& operator=(const gl2_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~gl2_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  ///
  gl2_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  gl2_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with matrix type xmatrix.
  ///
  gl2_lite(const matrix_type& xmatrix);

  ///
  /// Assignment (from a matrix type) operator.
  ///
  gl2_lite& operator=(const matrix_type& xmatrix);

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
  /// The associated basis transformation matrix (non const version).
  ///
  matrix_type& basis_matrix();

  ///
  /// The associated basis transformation matrix (const version).
  ///
  const matrix_type& basis_matrix() const;

  ///
  /// The associated component transformation matrix (non const version).
  ///
  matrix_type& component_matrix();

  ///
  /// The associated component transformation matrix (const version).
  ///
  const matrix_type& component_matrix() const;

  ///
  /// Set this transform to rescale the x and y axes by
  /// xscale and yscale, respectively.
  ///
  void rescale(const value_type& xscale, const value_type& yscale);

  ///
  /// Set this transform to a rotation about
  /// the z-axis by angle xangle, in radians.
  ///
  /// Note: this routine constructs the basis transformation
  /// matrix, not the component transformation matrix. More
  /// specifically:
  ///
  /// Let the old basis be f-hat, considered as a row of vectors
  /// with f-hat[i] the i-th basis vector. Similary, let e-hat be the
  /// new basis. Then this matrix is defined such that the i-th column,
  /// lm.[*][i] contains the components of e-hat[i] with respect to f-hat.
  /// Since a basis is a row of vectors, basis transformation corresponds
  /// to the matrix equation: e-hat = f-hat*this.
  ///
  void rotate_z(const value_type& xangle);

  ///
  /// The components of the new basis vectors w.r.t.
  /// the old basis, pre-allocated version.
  ///
  void basis(value_type xb0[], value_type xb1[]) const;

  ///
  /// Set this transformation to transform to the basis
  /// specified by component vectors xb0, xb1, where
  /// xbi gives the components of new basis vector i w.r.t.
  /// the old basis.
  ///
  void put_basis(const value_type xb0[],
                 const value_type xb1[]);

  ///
  /// Copies the row dofs of this into xmatrix.
  ///
  void get_matrix(row_dofs_type& xmatrix) const;

  ///
  /// Updates the component matrix part of xmatrix to be
  /// the inverse of the basis part and then copies 
  /// xmatrix into the row_dofs_of this.
  ///
  void put_matrix(row_dofs_type& xmatrix);


protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name GLN FACET OF CLASS GL2_LITE
  //============================================================================
  //@{

public:

  using gln_lite::n;
  
  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  virtual int n() const;

protected:
private:

  //@}


  //============================================================================
  /// @name GROUP FACET OF CLASS GL2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS GL2_LITE
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();
  
  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  ///
  virtual gl2_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual gl2_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS GL2_LITE
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
// CLASS GL2
//==============================================================================

///
/// The mathematical group GL(2, R).
/// The group of all invertible, linear transformations
/// on the R2, the 2 dimension vector space over the reals.
/// Equivalent to the set of all invertible 2x2 real matrices.
///

class SHEAF_DLL_SPEC gl2 : public gln
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS GL2
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
  /// The host with path standard_host_path<gl2>(xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const string& xsuffix, bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name GL2 FACET OF CLASS GL2
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef gl2_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef gl2_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e2 vector_space_type;

  ///
  /// Default constructor.
  ///
  gl2();

  ///
  /// Copy constructor.
  ///
  gl2(const gl2& xother, bool xnew_jem);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual gl2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  gl2& operator=(const gl2& xother);

  ///
  /// Destructor.
  ///
  virtual ~gl2();

  ///
  /// Creates a new handle attached to a new jim state in xhost.
  ///
  gl2(poset* xhost, bool xauto_access = true);

  ///@issue Why do we have "poset* xhost" instead of 
  ///        "poset_state_handle* xhost" above?

  ///
  /// New handle/new state constructor.
  ///
  gl2(poset_state_handle& xhost,
     const row_dofs_type& xrdt,
     bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  gl2& operator=(const row_dofs_type& xrdt);

  ///
  /// Creates a new handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  gl2(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new handle attached to the member state with id xid
  /// in xhost.
  ///
  gl2(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  gl2(const poset* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the same state as xother.
  ///
  explicit gl2(gl2* xother);

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
  /// Copies row dof tuple into xmatrix.
  ///
  void get_matrix(row_dofs_type& xmatrix) const;

  ///
  /// Updates the component matrix part of xmatrix to be
  /// the inverse of the basis part and then copies 
  /// xmatrix into the row_dofs_of this.
  ///
  void put_matrix(row_dofs_type& xmatrix);


  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;


  //============================================================================
  /// @name GLN FACET OF CLASS GL2
  //============================================================================
  //@{

public:
protected:
private:

  //@}



  //============================================================================
  /// @name GROUP FACET OF CLASS GL2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS GL2
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual gl2* clone() const;

  

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline gl2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<gl2*>(gln::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}



  //============================================================================
  /// @name ANY FACET OF CLASS GL2
  //============================================================================
  //@{

public:

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

protected:
private:

  //@}
};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// Insert gl2_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const gl2_row_dofs_type<T>& xrdt);

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert gl2_lite& xlite into ostream& xos.
///
SHEAF_DLL_SPEC ostream& operator<<(ostream& xos, const gl2_lite& xlite);

///
/// Insert gl2& xpersistent into ostream& xos.
///
SHEAF_DLL_SPEC ostream& operator<<(ostream& xos, const gl2& xpersistent);


///
/// Inverse (pre-allocated version for volatile type).
///
SHEAF_DLL_SPEC void inverse(const gl2_lite& xlite, gl2_lite& xresult);

///
/// Inverse (pre-allocated version for persistent type).
///
SHEAF_DLL_SPEC void inverse(const gl2& xgl, gl2& xresult);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN


} // namespace fiber_bundle


#endif // ifndef GL2_H
