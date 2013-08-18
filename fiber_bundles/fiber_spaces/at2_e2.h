

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for at2_e2 facet function templates.

#ifndef AT2_E2_H
#define AT2_E2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef AT2_H
#include "at2.h"
#endif

#ifndef ANTISYMMETRIC_MATRIX_2X2_H
#include "antisymmetric_matrix_2x2.h"
#endif

#ifndef E2_H
#include "e2.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS AT2_E2_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class at2_e2.
///
template <typename T>
class at2_e2_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef at2_e2_row_dofs_type<T> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef antisymmetric_matrix_2x2<T> matrix_type;

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
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (non const version). 
  ///
  operator typename at2_e2_row_dofs_type<T>::matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const typename at2_e2_row_dofs_type<T>::matrix_type& () const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  at2_e2_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  at2_e2_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  //
  // The antisymmetrix matrix is actually
  //               0  xy
  //             -xy   0
  // So we only need to store the xy component.

  ///
  /// The xy dof.
  ///
  /// components[0] => xy
  ///
  T components[1];

protected:
private:

};

//==============================================================================
// CLASS AT2_E2_LITE
//==============================================================================

class e2_lite;

///
/// An antisymmetric rank 2 tensor over a Euclidean vector space of dimension 2
/// (volatile version).
///
class SHEAF_DLL_SPEC at2_e2_lite : public at2_lite
{
  //============================================================================
  /// @name AT2_E2 FACET OF CLASS AT2_E2_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef at2_e2_row_dofs_type<double> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef at2_e2_row_dofs_type<double>::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  at2_e2_lite();

  ///
  /// Copy constructor.
  ///
  at2_e2_lite(const at2_e2_lite& xother);

  ///
  /// Assignment operator.
  ///
  at2_e2_lite& operator=(const at2_e2_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~at2_e2_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  at2_e2_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  at2_e2_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with matrix type xmatrix.
  ///
  at2_e2_lite(const matrix_type& xmatrix);

  ///
  /// Assignment (from a matrix type) operator.
  ///
  at2_e2_lite& operator=(const matrix_type& xmatrix);

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
  /// Creates a new instance with component xy.
  ///
  at2_e2_lite(const value_type& xy);

  using at2_lite::component;
  using at2_lite::put_component;
  
  ///
  /// Set value of the xy component to xy_comp.
  ///
  virtual void put_component(value_type xy);

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (AT2) FACET OF CLASS AT2_E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS AT2_E2_LITE
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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS AT2_E2_LITE
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
  /// @name TUPLE FACET OF CLASS AT2_E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT2_E2_LITE
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
  virtual at2_e2_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual at2_e2_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS AT2_E2_LITE
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
// CLASS AT2_E2
//==============================================================================

///
/// An antisymmetric rank 2 tensor over a Euclidean vector space of dimension 2
/// (persistent version).
///
class SHEAF_DLL_SPEC at2_e2 : public at2
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS AT2_E2
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
  /// Manual, shallow factory method; creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and table attribute vector_space_path specified by xvector_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path,
			     const poset_path& xvector_space_path,
			     bool xauto_access);

  ///
  /// Auto, deep factory method; creates a new host poset and any prerequisite posets
  /// for members of this type. The poset is created in namespace xns with the 
  /// standard_host_path for this class and xsuffix, schema specified by standard_schema_path(), 
  /// and standard paths for prerequisites. Returns the path of the new host poset.
  ///
  static host_type& new_host(namespace_type& xns, const string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name AT2_E2 FACET OF CLASS AT2_E2
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef at2_e2_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef at2_e2_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e2 vector_space_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef at2_e2_row_dofs_type<double>::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  at2_e2();

  ///
  /// Creates a new at2_e2 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  at2_e2(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new at2_e2 handle attached to the member state with id xid
  /// in xhost.
  ///
  at2_e2(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new at2_e2 handle attached to the member state with name xname
  /// in xhost.
  ///
  at2_e2(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new at2_e2 handle attached to the same state as xother.
  ///
  explicit at2_e2(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  at2_e2(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  at2_e2(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  at2_e2& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual at2_e2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  at2_e2& operator=(const at2_e2& xother);

  ///
  /// Destructor
  ///
  ~at2_e2();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

  ///
  /// Sets values of the components to the given arguments.
  ///
  virtual void put_components(dof_type xy_comp);

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
  /// @name AT2 FACET OF CLASS AT2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ATP FACET OF CLASS AT2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS AT2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS AT2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS AT2_E2
  //============================================================================
  //@{

public:

  ///@todo: Reword these comments.
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


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT2_E2
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
  virtual at2_e2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline at2_e2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<at2_e2*>(at2::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS AT2_E2
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
/// Insert at2_e2_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const at2_e2_row_dofs_type<T>& xrdt);

//==============================================================================

class at0;
class at0_lite;
class e2;
class e2_lite;

namespace atp_algebra
{

///
/// The interior (hook) product of two antisymmetric tensors
/// (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void hook(const e2& x0, const e2& x1, at0& xresult, bool xauto_access);

///
/// The interior (hook) product of two antisymmetric tensors
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void hook(const e2_lite& x0, const e2_lite& x1, at0_lite& xresult);

///
/// The interior (hook) product of two antisymmetric tensors
/// (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void hook(const at2_e2& x0, const e2& x1, e2& xresult, bool xauto_access);

///
/// The interior (hook) product of two antisymmetric tensors
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void hook(const at2_e2_lite& x0, const e2_lite& x1, e2_lite& xresult);

///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version persistent types).
///
SHEAF_DLL_SPEC void star(const at2_e2& x0, at0& xresult, bool xauto_access);

///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void star(const at2_e2_lite& x0, at0_lite& xresult);

///
/// The Hodge star operator for antisymmetric tensors
/// (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC at0_lite* star(const at2_e2_lite& x0);

///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version persistent types).
///
SHEAF_DLL_SPEC void star(const at0& x0, at2_e2& xresult, bool xauto_access);

///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void star(const at0_lite& x0, at2_e2_lite& xresult);

///
/// The Hodge star operator for antisymmetric tensors
/// (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC at2_e2_lite* star(const at0_lite& x0);

///@issue Do these functions belong in e2?

///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version persistent types).
///
SHEAF_DLL_SPEC void star(const e2& x0, e2& xresult, bool xauto_access);

///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void star(const e2_lite& x0, e2_lite& xresult);

///
/// The Hodge star operator for antisymmetric tensors
/// (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC e2_lite* star(const e2_lite& x0);

///
/// The exterior (wedge) product of two antisymmetric tensors
/// (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void wedge(const e2& x0, const e2& x1, at2_e2& xresult, bool xauto_access);

///
/// The exterior (wedge) product of two antisymmetric tensors
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void wedge(const e2_lite& x0, const e2_lite& x1, at2_e2_lite& xresult);

} // namespace atp_algebra

} // namespace fiber_bundle


#endif // ifndef AT2_E2_H
