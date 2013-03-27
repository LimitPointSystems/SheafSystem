
// $RCSfile: jcb_e23.h,v $ $Revision: 1.39 $ $Date: 2013/03/13 00:58:44 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class jcb_e23.

#ifndef JCB_E23_H
#define JCB_E23_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef JCB_ED_H
#include "jcb_ed.h"
#endif

#ifndef GENERAL_MATRIX_3X2_H
#include "general_matrix_3x2.h"
#endif

namespace fiber_bundle
{
  class e2;
  class e3;
  
//==============================================================================
// CLASS JCB_E23_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class jcb_e23.
///
template <typename T>
class jcb_e23_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef jcb_e23_row_dofs_type<T> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef general_matrix_3x2<T> matrix_type;

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
  operator typename jcb_e23_row_dofs_type<T>::matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const typename jcb_e23_row_dofs_type<T>::matrix_type& () const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  jcb_e23_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  jcb_e23_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The dofs in the following order:
  ///   components[0] => dx/du
  ///   components[1] => dx/dv
  ///   components[2] => dy/du
  ///   components[3] => dy/dv
  ///   components[4] => dz/du
  ///   components[5] => dz/dv
  ///
  T components[6];

protected:
private:

};


//==============================================================================
// CLASS JCB_E23_LITE
//==============================================================================

///
/// Jacobian of a map from a 2 dimensional domain (u, v) to
/// a 3 dimensional Euclidean space (x, y, z)
/// (volatile version).
///
class SHEAF_DLL_SPEC jcb_e23_lite : public jcb_ed_lite
{
  //============================================================================
  /// @name JCB_E23 FACET OF CLASS JCB_E23_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef jcb_e23_row_dofs_type<double> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef jcb_e23_row_dofs_type<double>::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  jcb_e23_lite();

  ///
  /// Copy constructor.
  ///
  jcb_e23_lite(const jcb_e23_lite& xother);

  ///
  /// Assignment operator.
  ///
  jcb_e23_lite& operator=(const jcb_e23_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~jcb_e23_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  jcb_e23_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  jcb_e23_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with matrix type xmatrix.
  ///
  jcb_e23_lite(const matrix_type& xmatrix);

  ///
  /// Assignment (from a matrix type) operator.
  ///
  jcb_e23_lite& operator=(const matrix_type& xmatrix);

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
  /// Creates a new instance with components
  /// dxdu, dxdv, dydu, dydv, dzdu, dzdv.
  ///
  jcb_e23_lite(const value_type& dxdu, const value_type& dxdv,
               const value_type& dydu, const value_type& dydv,
               const value_type& dzdu, const value_type& dzdv);

  using jcb_ed_lite::put_components;
  
  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(const value_type& dxdu, const value_type& dxdv,
                              const value_type& dydu, const value_type& dydv,
                              const value_type& dzdu, const value_type& dzdv);

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name JCB_ED FACET OF CLASS JCB_E23_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name JACOBIAN (JCB) FACET OF CLASS JCB_E23_LITE
  //============================================================================
  //@{

public:

  ///
  /// Dimension of the domain.
  ///
  virtual int dd() const;

  ///
  ///  Dimension of the range.
  ///
  virtual int dr() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS JCB_E23_LITE
  //============================================================================
  //@{

public:

//   ///
//   /// Virtual constructor for general tensors 
//   /// of degree xp over this vector space.
//   ///
//   virtual tp_lite* new_tp_lite(int xp) const;

//   ///
//   /// Virtual constructor for antisymmetric tensors 
//   /// of degree xp over this vector space.
//   ///
//   virtual atp_lite* new_atp_lite(int xp) const;

//   ///
//   /// Virtual constructor for symmetric tensors 
//   /// of degree xp over this vector space.
//   ///
//   virtual stp_lite* new_stp_lite(int xp) const;

//   virtual const tp_lite& tp_prototype(int xp) const;
//   virtual const atp_lite& atp_prototype(int xp) const;
//   virtual const stp_lite& stp_prototype(int xp) const;


protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS JCB_E23_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB_E23_LITE
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
  virtual jcb_e23_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual jcb_e23_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS JCB_E23_LITE
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
// CLASS JCB_E23
//==============================================================================


///@issue Is there really anything Euclidean about this class?

///
/// Jacobian of a map from a 2 dimensional domain (u, v) to
/// a 3 dimensional Euclidean space (x, y, z).
///
class SHEAF_DLL_SPEC jcb_e23 : public jcb_ed
{
  //============================================================================
  /// @name JCB_E23 FACET OF CLASS JCB_E23
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of domain vector space.
  ///
  typedef e2 domain_type;

  ///
  /// The type of range vector space.
  ///
  typedef e3 range_type;

  ///
  /// The type of the row dofs.
  ///
  typedef jcb_e23_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef jcb_e23_lite volatile_type;

  ///
  /// Default constructor.
  ///
  jcb_e23();

  /// New handle/old state constructors.

  ///
  /// Creates a new jcb_e23 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  jcb_e23(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new jcb_e23 handle attached to the member state with id
  /// xid in xhost.
  ///
  jcb_e23(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new jcb_e23 handle attached to the member state with name xname
  /// in xhost.
  ///
  jcb_e23(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new jcb_e23 handle attached to the same state as xother.
  ///
  explicit jcb_e23(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  jcb_e23(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  jcb_e23(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  jcb_e23& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual jcb_e23& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  jcb_e23& operator=(const jcb_e23& xother);

  ///
  /// Destructor.
  ///
  ~jcb_e23();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

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
  /// @name JCB_ED FACET OF CLASS JCB_E23
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name JCB FACET OF CLASS JCB_E23
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS JCB_E23
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS JCB_E23
  //============================================================================
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

protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB_E23
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
  virtual jcb_e23* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline jcb_e23* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<jcb_e23*>(jcb_ed::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS JCB_E23
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to current.
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
/// Insert jcb_e23_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const jcb_e23_row_dofs_type<T>& xrdt);


class e2;
class e2_lite;
class e3;
class e3_lite;
class st2_e2_lite;

//==============================================================================
// JCB FACET
//==============================================================================

namespace jcb_algebra
{

#ifndef DOXYGEN_SKIP_UNKNOWN

///
/// Push vector forward (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void push(const jcb_e23& xjcb,
			 const e2& xvector,
			 e3& xresult,
			 bool xauto_access);

///
/// Push vector forward (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void push(const jcb_e23_lite& xjcb,
			 const e2_lite& xvector,
			 e3_lite& xresult);

///
/// Push vector forward (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC e3_lite* push(const jcb_e23_lite& xjcb, const e2_lite& xvector);

#endif // ifndef DOXYGEN_SKIP_UNKNOWN

///
/// Pull covector back (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void pull(const jcb_e23& xjcb,
			 const e3& xcovector,
			 e2& xresult,
			 bool xauto_access);

///
/// Pull covector back (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void pull(const jcb_e23_lite& xjcb,
			 const e3_lite& xcovector,
			 e2_lite& xresult);

///
/// Pull covector back (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC e2_lite* pull(const jcb_e23_lite& xjcb, const e3_lite& xcovector);


//==============================================================================

///
/// Compute surface metric.
///
SHEAF_DLL_SPEC void metric(const jcb_e23_lite& xjcb, st2_e2_lite& xresult);


///
/// Transpose of xjcb times xother_jcb, symmetric part.
///
SHEAF_DLL_SPEC void symmetric_dot_push(const jcb_e23_lite& xjcb,
				       const jcb_e23_lite& xother_jcb,
				       st2_e2_lite&  xresult);

} // namespace jcb_algebra

} // namespace fiber_bundle


#endif // ifndef JCB_E23_H
