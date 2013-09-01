

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class met_e1

#ifndef MET_E1_H
#define MET_E1_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef MET_ED_H
#include "met_ed.h"
#endif

#ifndef E1_H
#include "e1.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS MET_E1_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class met_e1.
///
template <typename T>
class met_e1_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef met_e1_row_dofs_type<T> row_dofs_type;

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
  met_e1_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  met_e1_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The components (row_dofs).
  ///
  T components[1];

protected:
private:

};


//==============================================================================
// CLASS MET_E1_LITE
//==============================================================================

///
/// A metric tensor over a 1 dimensional Euclidean vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC met_e1_lite : public met_ed_lite
{
  //============================================================================
  /// @name EUCLIDEAN METRIC 1D (MET_E1) FACET OF CLASS MET_E1_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef met_e1_row_dofs_type<double> row_dofs_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e1_lite vector_space_type;

  ///
  /// Default constructor.
  ///
  met_e1_lite();

  ///
  /// Copy constructor.
  ///
  met_e1_lite(const met_e1_lite& xother);

  ///
  /// Assignment operator.
  ///
  met_e1_lite& operator=(const met_e1_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~met_e1_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  met_e1_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  met_e1_lite& operator=(const row_dofs_type& xrow_dofs);

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
  /// Creates a new instance with component xx_comp.
  ///
  met_e1_lite(const value_type& xx_comp);

  using met_ed_lite::component;
  using met_ed_lite::put_component;

  ///
  /// Value of xx component (const version).
  ///
  value_type component() const;

  ///
  /// Set value of component.
  ///
  void put_component(const value_type& x_comp);

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name EUCLIDEAN METRIC (MET_ED) FACET OF CLASS MET_E1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name METRIC TENSOR (MET) FACET OF CLASS MET_E1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS MET_E1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS MET_E1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS MET_E1_LITE
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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS MET_E1_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS MET_E1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS MET_E1_LITE
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
  virtual met_e1_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual met_e1_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS MET_E1_LITE
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
// CLASS MET_E1
//==============================================================================

///
/// A metric tensor over a 1 dimensional Euclidean vector space.
///
class SHEAF_DLL_SPEC met_e1 : public met_ed
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS MET_E1
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
  /// @name MET_E1 FACET OF CLASS MET_E1
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef met_e1_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef met_e1_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e1 vector_space_type;

  ///
  /// Default constructor.
  ///
  met_e1();

  // New handle/old state constructors.

  ///
  /// Creates a new met_e1 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  met_e1(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new met_e1 handle attached to the member state with id xid
  /// in xhost.
  ///
  met_e1(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new met_e1 handle attached to the member state with name xname
  /// in xhost.
  ///
  met_e1(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new met_e1 handle attached to the same state as xother.
  ///
  explicit met_e1(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  met_e1(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  met_e1(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  met_e1& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual met_e1& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  met_e1& operator=(const met_e1& xother);

  ///
  /// Destructor.
  ///
  ~met_e1();

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

  //============================================================================
  /// @name MET_ED FACET OF CLASS MET_E1
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name MET FACET OF CLASS MET_E1
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS MET_E1
  //============================================================================

  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS MET_E1
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS MET_E1
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS MET_E1
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS MET_E1
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS MET_E1
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
  virtual met_e1* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline met_e1* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<met_e1*>(met_ed::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS MET_E1
  //============================================================================
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
/// Insert met_e1_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const met_e1_row_dofs_type<T>& xrdt);

namespace met_algebra
{

///
/// Raise covector (pre-allocated version for persistent type).
///
SHEAF_DLL_SPEC void raise(const met_e1& xmetric, const e1& xcovector, e1& xresult,
			  bool xauto_access);

///
/// Lower vector (pre-allocated version for persistent type).
///
SHEAF_DLL_SPEC void lower(const met_e1& xmetric, const e1& xvector, e1& xresult,
			  bool xauto_access);

///
/// Raise covector (pre-allocated version for volatile type).
///
SHEAF_DLL_SPEC void raise(const met_e1_lite& xmetric, const e1_lite& xcovector,
			 e1_lite& xresult);

///
/// Raise covector (auto-allocated version for volatile type).
///
SHEAF_DLL_SPEC e1_lite* raise(const met_e1_lite& xmetric, const e1_lite& xcovector);

///
/// Lower vector (pre-allocated version for volatile type).
///
SHEAF_DLL_SPEC void lower(const met_e1_lite& xmetric, const e1_lite& xvector,
			 e1_lite& xresult);

///
/// Lower vector (auto-allocated version for volatile type).
///
SHEAF_DLL_SPEC e1_lite* lower(const met_e1_lite& xmetric, const e1_lite& xvector);

} // namespace met_algebra

} // namespace fiber_bundle

#endif // ifndef MET_E1_H
