

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class t2_e2.


#ifndef T2_E2_H
#define T2_E2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef T2_H
#include "t2.h"
#endif

#ifndef GENERAL_MATRIX_2X2_H
#include "general_matrix_2x2.h"
#endif

#ifndef E2_H
#include "e2.h"

#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS T2_E2_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class t2_e2.
///
template <typename T>
class SHEAF_DLL_SPEC t2_e2_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef t2_e2_row_dofs_type<T> row_dofs_type;

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
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (non const version). 
  ///
  operator typename t2_e2_row_dofs_type<T>::matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const typename t2_e2_row_dofs_type<T>::matrix_type& () const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  t2_e2_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  t2_e2_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The xx, xy, yx and yy dofs.
  ///
  /// components[0] => xx
  /// components[1] => xy
  /// components[2] => yx
  /// components[3] => yy
  ///
  T components[4];

protected:
private:

};


//==============================================================================
// CLASS T2_E2_LITE
//==============================================================================

class at2_e2_lite;
class e2_lite;
class st2_e2_lite;

///
/// A tensor of degree 2 over a Euclidean vector space of dimension 2
/// (volatile version).
///
class SHEAF_DLL_SPEC t2_e2_lite : public t2_lite
{

  //============================================================================
  /// @name T2_E2 FACET OF CLASS T2_E2_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef t2_e2_row_dofs_type<double> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef t2_e2_row_dofs_type<double>::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  t2_e2_lite();

  ///
  /// Copy constructor.
  ///
  t2_e2_lite(const t2_e2_lite& xother);

  ///
  /// Assignment operator.
  ///
  t2_e2_lite& operator=(const t2_e2_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~t2_e2_lite();

  ///
  /// Copy constructor (from a antisymmetric type).
  ///
  t2_e2_lite(const at2_e2_lite& xother);

  ///
  /// Assignment (from a antisymmetric type) operator.
  ///
  t2_e2_lite& operator=(const at2_e2_lite& xother);

  ///
  /// Copy constructor (from a symmetric type).
  ///
  t2_e2_lite(const st2_e2_lite& xother);

  ///
  /// Assignment (from a symmetric type) operator.
  ///
  t2_e2_lite& operator=(const st2_e2_lite& xother);

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  ///
  t2_e2_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  t2_e2_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with matrix type xmatrix.
  ///
  t2_e2_lite(const matrix_type& xmatrix);

  ///
  /// Assignment (from a matrix type) operator.
  ///
  t2_e2_lite& operator=(const matrix_type& xmatrix);

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
  /// Creates a new instance with components xx_comp, xy_comp, yx_comp, yy_comp.
  ///
  ///
  t2_e2_lite(const value_type& xx_comp,
              const value_type& xy_comp,
              const value_type& yx_comp,
              const value_type& yy_comp);

  using t2_lite::put_components;
  
  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(value_type xx_comp,
                              value_type xy_comp,
                              value_type yx_comp,
                              value_type yy_comp);

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name T2 FACET OF CLASS T2_E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS T2_E2_LITE
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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS T2_E2_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T2_E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T2_E2_LITE
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
  virtual t2_e2_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual t2_e2_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T2_E2_LITE
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
// CLASS T2_E2
//==============================================================================

class tp;
class atp;
class stp;

///
/// A tensor of degree 2 over a Euclidean vector space of dimension 2
/// (persistent version).
///
class SHEAF_DLL_SPEC t2_e2 : public t2
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS T2_E2
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
  /// The host with path standard_host_path(static_class_name(), xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name T2_E2 FACET OF CLASS T2_E2
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef t2_e2_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef t2_e2_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e2 vector_space_type;

  ///
  /// Default constructor.
  ///
  t2_e2();

  ///
  /// Copy constructor.
  ///
  t2_e2(const t2_e2& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual t2_e2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  t2_e2& operator=(const t2_e2& xother);

  ///
  /// Destructor.
  ///
  virtual ~t2_e2();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

  ///
  /// Creates a new handle attached to a new state in xhost.
  ///
  t2_e2(poset* xhost, bool xauto_access = true);

  ///
  /// Creates a new handle attached to
  /// the member state with hub id xhub_id in xhost.
  ///
  t2_e2(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new handle attached to
  /// the member state with id xid in xhost.
  ///
  t2_e2(const poset* xhost, const scoped_index& xid);

  ///@issue Why do we have "poset* xhost" instead of 
  ///       "poset_state_handle* xhost" above?

  ///
  /// New handle/new state constructor.
  ///
  t2_e2(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  t2_e2& operator=(const row_dofs_type& xrdt);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  t2_e2(const poset* xhost, const string& xname);

  using t2::put_components;
  
  ///
  /// Sets values of the components to the given arguments.
  ///
  virtual void put_components(dof_type xx_comp, dof_type xy_comp,
                              dof_type yx_comp, dof_type yy_comp);

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

  //============================================================================
  /// @name T2 FACET OF CLASS T2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS T2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}



  //============================================================================
  /// @name VD FACET OF CLASS T2_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS T2_E2
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


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T2_E2
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
  /// Make a new handle, no state instance of current
  ///
  virtual t2_e2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline t2_e2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<t2_e2*>(t2::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T2_E2
  //============================================================================
  //@{

public:

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

protected:
private:

  //@}
};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// Insert t2_e2_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const t2_e2_row_dofs_type<T>& xrdt);


} // namespace fiber_bundle

#endif // ifndef T2_E2_H
