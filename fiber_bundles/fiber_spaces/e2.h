

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class e2

#ifndef E2_H
#define E2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ED_H
#include "ed.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS E2_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class e2.
///
template <typename T>
class e2_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef e2_row_dofs_type<T> row_dofs_type;

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
  e2_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  e2_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The components (row_dofs).
  ///
  T components[2];

protected:
private:

};


//==============================================================================
// CLASS E2_LITE
//==============================================================================

///
/// Euclidean vector space of dimension 2
/// (volatile version).
///
class SHEAF_DLL_SPEC e2_lite : public ed_lite
{

  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (E2) FACET OF CLASS E2_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef e2_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  e2_lite();

  ///
  /// Copy constructor.
  ///
  e2_lite(const e2_lite& xother);

  ///
  /// Assignment operator.
  ///
  e2_lite& operator=(const e2_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~e2_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  e2_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  e2_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with components x_comp, y_comp.
  ///
  e2_lite(const value_type& x_comp, const value_type& y_comp);

  using ed_lite::put_components;

  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(const value_type& x_comp,
                              const value_type& y_comp);

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
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (AT1) FACET OF CLASS E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS E2_LITE
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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS E2_LITE
  //============================================================================
  //@{

public:

  ///
  /// True if this has the same components as xother.
  ///
  bool operator==(const e2_lite& xother) const;

  ///
  /// Static prototype for general tensors 
  /// of degree xp over this vector space.
  ///
  static const tp_lite& static_tp_prototype(int xp);

  ///
  /// Prototype for general tensors 
  /// of degree xp over this vector space.
  ///
  virtual const tp_lite& tp_prototype(int xp) const;

  ///
  /// Static prototype for antisymmetric tensors 
  /// of degree xp over this vector space.
  ///
  static const atp_lite& static_atp_prototype(int xp);

  ///
  /// Prototype for antisymmetric tensors 
  /// of degree xp over this vector space.
  ///
  virtual const atp_lite& atp_prototype(int xp) const;

  ///
  /// Static prototype for symmetric tensors 
  /// of degree xp over this vector space.
  ///
  static const stp_lite& static_stp_prototype(int xp);

  ///
  /// Prototype for symmetric tensors 
  /// of degree xp over this vector space.
  ///
  virtual const stp_lite& stp_prototype(int xp) const;

protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS E2_LITE
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
  virtual e2_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual e2_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS E2_LITE
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
// CLASS E2
//==============================================================================

class tp_space;
class tp;
class atp;
class stp;

///
/// Euclidean vector space of dimension 2
/// (persistent version).
///
class SHEAF_DLL_SPEC e2 : public ed
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS E2
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
  /// and table attribute scalar_space_path specified by xscalar_space_path.
  ///
  static void new_host(namespace_type& xns, 
                       const poset_path& xhost_path, 
                       const poset_path& xschema_path,
                       const poset_path& xscalar_space_path,
                       bool xauto_access);

  ///
  /// Auto, deep factory method; creates a new host poset and any prerequisite posets
  /// for members of this type. The poset is created in namespace xns with the 
  /// standard_host_path for this class and xsuffix, schema specified by standard_schema_path(), 
  /// and standard paths for prerequisites. Returns the path of the new host poset.
  ///
  static poset_path new_host(namespace_type& xns, const string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (E2) FACET OF CLASS E2
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef e2_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef e2_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e2 vector_space_type;

  ///
  /// Default constructor.
  ///
  e2();

  // New handle/old state constructors.

  ///
  /// Creates a new e2 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  e2(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new e2 handle attached to the member state with id xid
  /// in xhost.
  ///
  e2(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new e2 handle attached to the member state with name xname
  /// in xhost.
  ///
  e2(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new e2 handle attached to the same state as xother.
  ///
  explicit e2(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor
  ///
  e2(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  e2(poset_state_handle& xhost,
     const row_dofs_type& xrdt,
     bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  e2& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual e2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  e2& operator=(const e2& xother);

  ///
  /// Destructor.
  ///
  ~e2();

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
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (AT1) FACET OF CLASS E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS E2
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS E2
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS E2
  //===========================================================================
  //@{

public:

  using ed::put_components;

  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(dof_type x_comp, dof_type y_comp);

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


  //===========================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E2
  //===========================================================================
  //@{

public:

  ///
  /// Static constructor for general tensors 
  /// of degree xp over vector space xvector_space.
  ///
  static tp* new_tp(tp_space& xvector_space, int xp);

  ///
  /// Static constructor for antisymmetric tensors 
  /// of degree xp over vector space xvector_space.
  ///
  static atp* new_atp(tp_space& xvector_space, int xp);

  ///
  /// Static constructor for symmetric tensors 
  /// of degree xp over vector space xvector_space.
  ///
  static stp* new_stp(tp_space& xvector_space, int xp);


  ///@todo: Reword these comments.
  ///
  /// Virtual constructor for general tensors 
  /// of degree xp over this vector space.
  ///
  virtual tp* new_tp(int xp, bool xauto_access) const;

  ///
  /// Virtual constructor for antisymmetric tensors 
  /// of degree xp over this vector space.
  ///
  virtual atp* new_atp(int xp, bool xauto_access) const;

  ///
  /// Virtual constructor for symmetric tensors 
  /// of degree xp over this vector space.
  ///
  virtual stp* new_stp(int xp, bool xauto_access) const;

protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS E2
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
  virtual e2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline e2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<e2*>(ed::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS E2
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
/// Insert e2_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const e2_row_dofs_type<T>& xrdt);

///
/// Namespace containing the 2D Euclidean vector algebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace e2_algebra
{

///
/// The perp-dot pseudo cross product of x0 with x1
/// (version for persistent types).
///
SHEAF_DLL_SPEC vd_value_type perp_dot(const e2_lite& x0, const e2_lite& x1);

} // namespace e2_algebra

//==============================================================================
// TP FACET
//==============================================================================

// Forward declarations needed for specialization:

class at0_lite;
class at2_e2_lite;
class at3_e2_lite;
class st2_e2_lite;
class st3_e2_lite;
class st4_e2_lite;
class t2_e2_lite;
class t3_e2_lite;
class t4_e2_lite;

class at0;
class at2_e2;
class at3_e2;
class st2_e2;
class st3_e2;
class st4_e2;
class t2_e2;
class t3_e2;
class t4_e2;

///
/// Specialization for degree 0 tensors over e2_lite.
///
template<> class tensor_traits<0, e2_lite>
{
public:
  ///
  /// Type of general tensor of degree 0 over e2_lite.
  ///
  typedef at0_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 0 over e2_lite.
  ///
  typedef at0_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 0 over e2_lite.
  ///
  typedef at0_lite stp_type;
};
  
///
/// Specialization for degree 1 tensors over e2_lite.
///
template<> class tensor_traits<1, e2_lite>
{
public:
  ///
  /// Type of general tensor of degree 1 over e2_lite.
  ///
  typedef e2_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 1 over e2_lite.
  ///
  typedef e2_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 1 over e2_lite.
  ///
  typedef e2_lite stp_type;
};
  
///
/// Specialization for degree 2 tensors over e2_lite.
///
template<> class tensor_traits<2, e2_lite>
{
public:
  ///
  /// Type of general tensor of degree 2 over e2_lite.
  ///
  typedef t2_e2_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 2 over e2_lite.
  ///
  typedef at2_e2_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 2 over e2_lite.
  ///
  typedef st2_e2_lite stp_type;
};
  
///
/// Specialization for degree 3 tensors over e2_lite.
///
template<> class tensor_traits<3, e2_lite>
{
public:
  ///
  /// Type of general tensor of degree 3 over e2_lite.
  ///
  typedef t3_e2_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 3 over e2_lite.
  ///
  typedef at3_e2_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 3 over e2_lite.
  ///
  typedef st3_e2_lite stp_type;
};
  
///
/// Specialization for degree 4 tensors over e2_lite.
///
template<> class tensor_traits<4, e2_lite>
{
public:
  ///
  /// Type of general tensor of degree 4 over e2_lite.
  ///
  typedef t4_e2_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 4 over e2_lite.
  ///
  typedef void atp_type;

  ///
  /// Type of symmetric tensor of degree 4 over e2_lite.
  ///
  typedef st4_e2_lite stp_type;
};

//==============================================================================

///
/// Specialization for degree 0 tensors over e2.
///
template<> class tensor_traits<0, e2>
{
public:
  ///
  /// Type of general tensor of degree 0 over e2.
  ///
  typedef at0 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 0 over e2.
  ///
  typedef at0 atp_type;

  ///
  /// Type of symmetric tensor of degree 0 over e2.
  ///
  typedef at0 stp_type;
};
  
///
/// Specialization for degree 1 tensors over e2.
///
template<> class tensor_traits<1, e2>
{
public:
  ///
  /// Type of general tensor of degree 1 over e2.
  ///
  typedef e2 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 1 over e2.
  ///
  typedef e2 atp_type;

  ///
  /// Type of symmetric tensor of degree 1 over e2.
  ///
  typedef e2 stp_type;
};
  
///
/// Specialization for degree 2 tensors over e2.
///
template<> class tensor_traits<2, e2>
{
public:
  ///
  /// Type of general tensor of degree 2 over e2.
  ///
  typedef t2_e2 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 2 over e2.
  ///
  typedef at2_e2 atp_type;

  ///
  /// Type of symmetric tensor of degree 2 over e2.
  ///
  typedef st2_e2 stp_type;
};
  
///
/// Specialization for degree 3 tensors over e2.
///
template<> class tensor_traits<3, e2>
{
public:
  ///
  /// Type of general tensor of degree 3 over e2.
  ///
  typedef t3_e2 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 3 over e2.
  ///
  typedef at3_e2 atp_type;

  ///
  /// Type of symmetric tensor of degree 3 over e2.
  ///
  typedef st3_e2 stp_type;
};
  
///
/// Specialization for degree 4 tensors over e2.
///
template<> class tensor_traits<4, e2>
{
public:
  ///
  /// Type of general tensor of degree 4 over e2.
  ///
  typedef t4_e2 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 4 over e2.
  ///
  typedef void atp_type;

  ///
  /// Type of symmetric tensor of degree 4 over e2.
  ///
  typedef st4_e2 stp_type;
};

} // namespace fiber_bundle

#endif // ifndef E2_H
