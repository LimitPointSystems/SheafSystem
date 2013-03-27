
// $RCSfile: met_e3.h,v $ $Revision: 1.36 $ $Date: 2013/03/13 00:58:44 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class met_e3.

#ifndef MET_E3_H
#define MET_E3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef MET_ED_H
#include "met_ed.h"
#endif

#ifndef SYMMETRIC_MATRIX_3X3_H
#include "symmetric_matrix_3x3.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS MET_E3_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class met_e3.
///
template <typename T>
class met_e3_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef met_e3_row_dofs_type<T> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef symmetric_matrix_3x3<T> matrix_type;

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
  operator typename met_e3_row_dofs_type<T>::matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const typename met_e3_row_dofs_type<T>::matrix_type& () const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  met_e3_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  met_e3_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The xx, xy and yy dofs.
  ///
  /// components[0] => xx
  /// components[1] => xy
  /// components[2] => xz
  /// components[3] => yy
  /// components[4] => yz
  /// components[5] => zz
  ///
  ///
  T components[6];

protected:
private:

};


//==============================================================================
// CLASS MET_E3_LITE
//==============================================================================

///
/// A metric tensor over a 1 dimensional Euclidean vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC met_e3_lite : public met_ed_lite
{
  //============================================================================
  /// @name EUCLIDEAN METRIC 3D (MET_E3) FACET OF CLASS MET_E3_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef met_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e3_lite vector_space_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef met_e3_row_dofs_type<double>::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  met_e3_lite();

  ///
  /// Copy constructor.
  ///
  met_e3_lite(const met_e3_lite& xother);

  ///
  /// Assignment operator.
  ///
  met_e3_lite& operator=(const met_e3_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~met_e3_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  met_e3_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  met_e3_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with matrix type xmatrix.
  ///
  met_e3_lite(const matrix_type& xmatrix);

  ///
  /// Assignment (from a matrix type) operator.
  ///
  met_e3_lite& operator=(const matrix_type& xmatrix);

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
  /// Creates a new instance with row dofs
  /// xx_comp, xy_comp, xz_comp, yy_comp, yz_comp, zz_comp.
  ///
  met_e3_lite(const value_type& xx_comp,
              const value_type& xy_comp,
              const value_type& xz_comp,
              const value_type& yy_comp,
              const value_type& yz_comp,
              const value_type& zz_comp);

  using met_ed_lite::put_components;
  
  ////
  //// Set values of the components to the given arguments.
  ////
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
  /// @name EUCLIDEAN METRIC (MET_ED) FACET OF CLASS MET_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //@}


  //============================================================================
  /// @name METRIC TENSOR (MET) FACET OF CLASS MET_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS MET_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS MET_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS MET_E3_LITE
  //============================================================================
  //@{

public:

  ///
  /// Dimension of the underlying vector space.
  ///
  virtual int dd() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS MET_E3_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS MET_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS MET_E3_LITE
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
  virtual met_e3_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual met_e3_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS MET_E3_LITE
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
// CLASS MET_E3
//==============================================================================

///
/// A metric tensor over a 3 dimensional Euclidean vector space
/// (persistent version).
///
class SHEAF_DLL_SPEC met_e3 : public met_ed
{

  //============================================================================
  /// @name MET_E3 FACET OF CLASS MET_E3
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef met_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef met_e3_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e3 vector_space_type;

  ///
  /// Default constructor.
  ///
  met_e3();

  // New handle/old state constructors.

  ///
  /// Creates a new met_e3 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  met_e3(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new met_e3 handle attached to the member state with id xid
  /// in xhost.
  ///
  met_e3(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new met_e3 handle attached to the member state with name xname
  /// in xhost.
  ///
  met_e3(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new met_e3 handle attached to the same state as xother.
  ///
  explicit met_e3(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  met_e3(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  met_e3(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  met_e3& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual met_e3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  met_e3& operator=(const met_e3& xother);

  ///
  /// Destructor.
  ///
  ~met_e3();

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
  /// @name MET_ED FACET OF CLASS MET_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}



  //============================================================================
  /// @name MET FACET OF CLASS MET_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS MET_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS MET_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS MET_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS MET_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS MET_E3
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS MET_E3
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
  virtual met_e3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline met_e3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<met_e3*>(met_ed::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}



  //============================================================================
  /// @name ANY FACET OF CLASS MET_E3
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
/// Insert met_e3_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const met_e3_row_dofs_type<T>& xrdt);

namespace met_algebra
{

///
/// Raise covector (pre-allocated version for persistent type).
///
SHEAF_DLL_SPEC void raise(const met_e3& xmetric, const e3& xcovector, e3& xresult,
			  bool xauto_access);

///
/// Lower vector (pre-allocated version for persistent type).
///
SHEAF_DLL_SPEC void lower(const met_e3& xmetric, const e3& xvector, e3& xresult,
			  bool xauto_access);

///
/// Raise covector (pre-allocated version for volatile type).
///
SHEAF_DLL_SPEC void raise(const met_e3_lite& xmetric, const e3_lite& xcovector,
			  e3_lite& xresult);

///
/// Raise covector (auto-allocated version for volatile type).
///
SHEAF_DLL_SPEC e3_lite* raise(const met_e3_lite& xmetric, const e3_lite& xcovector);

///
/// Lower vector (pre-allocated version for volatile type).
///
SHEAF_DLL_SPEC void lower(const met_e3_lite& xmetric, const e3_lite& xvector,
			  e3_lite& xresult);

///
/// Lower vector (auto-allocated version for volatile type).
///
SHEAF_DLL_SPEC e3_lite* lower(const met_e3_lite& xmetric, const e3_lite& xvector);

} // namespace met_algebra

} // namespace fiber_bundle


#endif // ifndef MET_E3_H
