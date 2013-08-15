

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class e4.

#ifndef E4_H
#define E4_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ED_H
#include "ed.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS E4_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class e4.
///
template <typename T>
class e4_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef e4_row_dofs_type<T> row_dofs_type;

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
  e4_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  e4_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The components (row_dofs).
  ///
  T components[4];

protected:
private:

};

//==============================================================================
// CLASS E4_LITE
//==============================================================================

///
/// Euclidean vector space of dimension 4
/// (volatile version).
///
class SHEAF_DLL_SPEC e4_lite : public ed_lite
{
  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (E4) FACET OF CLASS E4_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef e4_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  e4_lite();

  ///
  /// Copy constructor.
  ///
  e4_lite(const e4_lite& xother);

  ///
  /// Assignment operator.
  ///
  e4_lite& operator=(const e4_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~e4_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  e4_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  e4_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with components x0, x1, x2, x3.
  ///
  e4_lite(const value_type& x0,
          const value_type& x1,
          const value_type& x2,
          const value_type& x3);

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

  using ed_lite::put_components;

  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(const value_type& x0,
                              const value_type& x1,
                              const value_type& x2,
                              const value_type& x3);


protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E4_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (AT1) FACET OF CLASS E4_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS E4_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS E4_LITE
  //============================================================================
  //@{

public:

  ///
  /// Type of underlying vector space.
  ///
  typedef e4_lite vector_space_type;

  ///
  /// Dimension of the underlying vector space.
  ///
  virtual int dd() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS E4_LITE
  //============================================================================
  //@{

public:

  ///
  /// True if this has the same components as xother.
  ///
  bool operator==(const e4_lite& xother) const;

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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E4_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS E4_LITE
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
  virtual e4_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual e4_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS E4_LITE
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
// CLASS E4
//==============================================================================

class tp_space;
class tp;
class atp;
class stp;

///
/// Euclidean vector space of dimension 4
/// (persistent version).
///
class SHEAF_DLL_SPEC e4 : public ed
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS E4
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
  /// @name EUCLIDEAN VECTOR ALGEBRA (E4) FACET OF CLASS E4
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef e4_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef e4_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e4 vector_space_type;

  ///
  /// Default constructor.
  ///
  e4();

  // New handle/old state constructors.

  ///
  /// Creates a new e4 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  e4(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new e4 handle attached to the member state with id xid
  /// in xhost.
  ///
  e4(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new e4 handle attached to the member state with name xname
  /// in xhost.
  ///
  e4(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new e4 handle attached to the same state as xother.
  ///
  explicit e4(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  e4(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  e4(poset_state_handle& xhost,
     const row_dofs_type& xrdt,
     bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  e4& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual e4& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  e4& operator=(const e4& xother);

  ///
  /// Destructor
  ///
  ~e4();

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
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E4
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (AT1) FACET OF CLASS E4
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS E4
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS E4
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS E4
  //===========================================================================
  //@{

public:

  using ed::put_components;

  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(dof_type x0,
                              dof_type x1,
                              dof_type x2,
                              dof_type x3);

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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E4
  //===========================================================================
  //@{

public:

  //@todo: Reword comments.
  ///
  /// Static prototype for general tensors 
  /// of degree xp over this vector space.
  ///
  static tp* new_tp(tp_space& xvector_space, int xp);

  ///
  /// Static prototype for antisymmetric tensors 
  /// of degree xp over this vector space.
  ///
  static atp* new_atp(tp_space& xvector_space, int xp);

  ///
  /// Static prototype for symmetric tensors 
  /// of degree xp over this vector space.
  ///
  static stp* new_stp(tp_space& xvector_space, int xp);


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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS E4
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
  virtual e4* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline e4* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<e4*>(ed::clone(xnew_state, xauto_access));
  }

protected:
public:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS E4
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
/// Insert e4_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const e4_row_dofs_type<T>& xrdt);


//==============================================================================
// TP FACET
//==============================================================================

// Forward declarations needed for specialization:

class at0_lite;
class at2_e4_lite;
class at3_e4_lite;
class st2_e4_lite;
class st3_e4_lite;
class st4_e4_lite;
class t2_e4_lite;
class t3_e4_lite;
class t4_e4_lite;

class at0;
class at2_e4;
class at3_e4;
class st2_e4;
class st3_e4;
class st4_e4;
class t2_e4;
class t3_e4;
class t4_e4;


///
/// Specialization for degree 0 tensors over e4_lite.
///
template<> class tensor_traits<0, e4_lite>
{
public:
  ///
  /// Type of general tensor of degree 0 over e4_lite.
  ///
  typedef at0_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 0 over e4_lite.
  ///
  typedef at0_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 0 over e4_lite.
  ///
  typedef at0_lite stp_type;
};
  
///
/// Specialization for degree 1 tensors over e4_lite.
///
template<> class tensor_traits<1, e4_lite>
{
public:
  ///
  /// Type of general tensor of degree 1 over e4_lite.
  ///
  typedef e4_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 1 over e4_lite.
  ///
  typedef e4_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 1 over e4_lite.
  ///
  typedef e4_lite stp_type;
};
  
///
/// Specialization for degree 2 tensors over e4_lite.
///
template<> class tensor_traits<2, e4_lite>
{
public:
  ///
  /// Type of general tensor of degree 2 over e4_lite.
  ///
  typedef t2_e4_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 2 over e4_lite.
  ///
  typedef at2_e4_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 2 over e4_lite.
  ///
  typedef st2_e4_lite stp_type;
};
  
///
/// Specialization for degree 3 tensors over e4_lite.
///
template<> class tensor_traits<3, e4_lite>
{
public:
  ///
  /// Type of general tensor of degree 3 over e4_lite.
  ///
  typedef t3_e4_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 3 over e4_lite.
  ///
  typedef at3_e4_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 3 over e4_lite.
  ///
  typedef st3_e4_lite stp_type;
};
  
///
/// Specialization for degree 4 tensors over e4_lite.
///
template<> class tensor_traits<4, e4_lite>
{
public:
  ///
  /// Type of general tensor of degree 4 over e4_lite.
  ///
  typedef t4_e4_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 4 over e4_lite.
  ///
  typedef void atp_type;

  ///
  /// Type of symmetric tensor of degree 4 over e4_lite.
  ///
  typedef st4_e4_lite stp_type;
};

//==============================================================================

///
/// Specialization for degree 0 tensors over e4.
///
template<> class tensor_traits<0, e4>
{
public:
  ///
  /// Type of general tensor of degree 0 over e4.
  ///
  typedef at0 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 0 over e4.
  ///
  typedef at0 atp_type;

  ///
  /// Type of symmetric tensor of degree 0 over e4.
  ///
  typedef at0 stp_type;
};
  
///
/// Specialization for degree 1 tensors over e4.
///
template<> class tensor_traits<1, e4>
{
public:
  ///
  /// Type of general tensor of degree 1 over e4.
  ///
  typedef e4 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 1 over e4.
  ///
  typedef e4 atp_type;

  ///
  /// Type of symmetric tensor of degree 1 over e4.
  ///
  typedef e4 stp_type;
};
  
///
/// Specialization for degree 2 tensors over e4.
///
template<> class tensor_traits<2, e4>
{
public:
  ///
  /// Type of general tensor of degree 2 over e4.
  ///
  typedef t2_e4 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 2 over e4.
  ///
  typedef at2_e4 atp_type;

  ///
  /// Type of symmetric tensor of degree 2 over e4.
  ///
  typedef st2_e4 stp_type;
};
  
///
/// Specialization for degree 3 tensors over e4.
///
template<> class tensor_traits<3, e4>
{
public:
  ///
  /// Type of general tensor of degree 3 over e4.
  ///
  typedef t3_e4 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 3 over e4.
  ///
  typedef at3_e4 atp_type;

  ///
  /// Type of symmetric tensor of degree 3 over e4.
  ///
  typedef st3_e4 stp_type;
};
  
///
/// Specialization for degree 4 tensors over e4.
///
template<> class tensor_traits<4, e4>
{
public:
  ///
  /// Type of general tensor of degree 4 over e4.
  ///
  typedef t4_e4 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 4 over e4.
  ///
  typedef void atp_type;

  ///
  /// Type of symmetric tensor of degree 4 over e4.
  ///
  typedef st4_e4 stp_type;
};


} // namespace fiber_bundle

 
#endif // ifndef E4_H
