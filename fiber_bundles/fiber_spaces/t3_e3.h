

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class t3_e3.


#ifndef T3_E3_H
#define T3_E3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef T3_H
#include "t3.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS T3_E3_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class t3_e3.
///
template <typename T>
class t3_e3_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef t3_e3_row_dofs_type<T> row_dofs_type;

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
  /// Creates a new instance of the same type as this.
  ///
  t3_e3_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  t3_e3_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The dofs in the following order:
  ///
  ///   components[ 0] => xxx
  ///   components[ 1] => xxy
  ///   components[ 2] => xxz
  ///   components[ 3] => xyx
  ///   components[ 4] => xyy
  ///   components[ 5] => xyz
  ///   components[ 6] => xzx
  ///   components[ 7] => xzy
  ///   components[ 8] => xzz
  ///
  ///   components[ 9] => yxx
  ///   components[10] => yxy
  ///   components[11] => yxz
  ///   components[12] => yyx
  ///   components[13] => yyy
  ///   components[14] => yyz
  ///   components[15] => yzx
  ///   components[16] => yzy
  ///   components[17] => yzz
  ///
  ///   components[18] => zxx
  ///   components[19] => zxy
  ///   components[20] => zxz
  ///   components[21] => zyx
  ///   components[22] => zyy
  ///   components[23] => zyz
  ///   components[24] => zzx
  ///   components[25] => zzy
  ///   components[26] => zzz
  ///
  ///
  T components[27];

protected:
private:

};

//==============================================================================
// CLASS T3_E3_LITE
//==============================================================================

class at3_e3_lite;
class e3_lite;
class st3_e3_lite;

///
/// A tensor of degree 3 over a Euclidean vector space of dimension 3
/// (volatile version).
///
class SHEAF_DLL_SPEC t3_e3_lite : public t3_lite
{

  //============================================================================
  /// @name T3_E3 FACET OF CLASS T3_E3_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef t3_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  t3_e3_lite();

  ///
  /// Copy constructor.
  ///
  t3_e3_lite(const t3_e3_lite& xother);

  ///
  /// Assignment operator.
  ///
  t3_e3_lite& operator=(const t3_e3_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~t3_e3_lite();

  ///
  /// Copy constructor (from a antisymmetric type).
  ///
  t3_e3_lite(const at3_e3_lite& xother);

  ///
  /// Assignment (from a antisymmetric type) operator.
  ///
  t3_e3_lite& operator=(const at3_e3_lite& xother);

  ///
  /// Copy constructor (from a symmetric type).
  ///
  t3_e3_lite(const st3_e3_lite& xother);

  ///
  /// Assignment (from a symmetric type) operator.
  ///
  t3_e3_lite& operator=(const st3_e3_lite& xother);

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  t3_e3_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  t3_e3_lite& operator=(const row_dofs_type& xrow_dofs);

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

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name T3 FACET OF CLASS T3_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS T3_E3_LITE
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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS T3_E3_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T3_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T3_E3_LITE
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
  virtual t3_e3_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual t3_e3_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T3_E3_LITE
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
// CLASS T3_E3
//==============================================================================

class tp_space;

///
/// A tensor of degree 3 over a Euclidean vector space of dimension 3
/// (persistent version).
///
class SHEAF_DLL_SPEC t3_e3 : public t3
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS T3_E3
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
  /// @name T3_E3 FACET OF CLASS T3_E3
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  ///  The type of the row dofs.
  ///
  typedef t3_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef t3_e3_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e3 vector_space_type;

  ///
  /// Default constructor.
  ///
  t3_e3();

  ///
  /// Copy constructor.
  ///
  t3_e3(const t3_e3& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual t3_e3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  t3_e3& operator=(const t3_e3& xother);

  ///
  /// Destructor.
  ///
  virtual ~t3_e3();

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
  t3_e3(poset* xhost, bool xauto_access = true);

  ///@issue Why do we have "poset* xhost" instead of 
  ///       "poset_state_handle* xhost" above?

  ///
  /// New handle/new state constructor.
  ///
  t3_e3(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  t3_e3& operator=(const row_dofs_type& xrdt);

  ///
  /// Creates a new handle attached to
  /// the member state with hub id xhub_id in xhost.
  ///
  t3_e3(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new handle attached to
  /// the member state with id xid in xhost.
  ///
  t3_e3(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  t3_e3(const poset* xhost, const string& xname);

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
  /// @name T3 FACET OF CLASS T3_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS T3_E3
  //============================================================================

  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS T3_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS T3_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}



  //============================================================================
  /// @name VD FACET OF CLASS T3_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS T3_E3
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T3_E3
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
  virtual t3_e3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline t3_e3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<t3_e3*>(t3::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T3_E3
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
  virtual bool is_ancestor_of(const any* other) const;

protected:
private:

  //@}
};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// Insert t3_e3_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const t3_e3_row_dofs_type<T>& xrdt);


class at3_e3;
class at3_e3_lite;
class st3_e3;
class st3_e3_lite;

namespace tp_algebra
{

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void alt(const t3_e3_lite& x0, at3_e3_lite& xresult);

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void alt(const t3_e3& x0, at3_e3& xresult, bool xauto_access);

///
/// The symmetric part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void sym(const t3_e3_lite& x0, st3_e3_lite& xresult);

///
/// The symmetric part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void sym(const t3_e3& x0, st3_e3& xresult, bool xauto_access);

} // namespace tp_algebra

} // namespace fiber_bundle


#endif // ifndef T3_E3_H
