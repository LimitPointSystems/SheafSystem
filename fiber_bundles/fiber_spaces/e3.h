
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class e3.

#ifndef E3_H
#define E3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ED_H
#include "ed.h"
#endif

namespace fiber_bundle
{

class atp;
class stp;
class tp;


//==============================================================================
// CLASS E3_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class e3.
///
template <typename T>
class e3_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef e3_row_dofs_type<T> row_dofs_type;

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
  e3_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  e3_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The components (row_dofs).
  ///
  T components[3];

protected:
private:

};

//==============================================================================
// CLASS E3_LITE
//==============================================================================

///
/// Euclidean vector space of dimension 3
/// (volatile version).
///
class SHEAF_DLL_SPEC e3_lite : public ed_lite
{
  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (E3) FACET OF CLASS E3_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef e3_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  e3_lite();

  ///
  /// Copy constructor.
  ///
  e3_lite(const e3_lite& xother);

  ///
  /// Copy assignment operator.
  ///
  e3_lite& operator=(const e3_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~e3_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  e3_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Row_dofs_type assignment operator.
  ///
  e3_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with all components == x value.
  ///
  explicit e3_lite(const value_type& xvalue);

  ///
  /// Creates a new instance with components x_comp, y_comp, z_comp.
  ///
  e3_lite(const value_type& x_comp,
          const value_type& y_comp,
          const value_type& z_comp);

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
  virtual void put_components(const value_type& x_comp,
                              const value_type& y_comp,
                              const value_type& z_comp);


protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (AT1) FACET OF CLASS E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS E3_LITE
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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS E3_LITE
  //============================================================================
  //@{

public:

  ///
  /// True if this has the same components as xother.
  ///
  bool operator==(const e3_lite& xother) const;
 
  ///
  /// Value_type assignment operator; sets all components to xvalue.
  ///
  e3_lite& operator=(const value_type& xvalue);

  ///
  /// Equality comparison to scalar; true if and only if all components == xvalue.
  /// Especially useful for comparison to 0.0.
  ///
  bool operator==(const value_type& xvalue) const;

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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E3_LITE
  //============================================================================
  //@{

public:

  ///
  /// Cartesian order less than comparison.
  ///
  bool c_lt(const e3_lite& xother) const;

  ///
  /// Cartesian order less than or equal comparison.
  ///
  bool c_le(const e3_lite& xother) const;

  ///
  /// Cartesian order greater than comparison.
  ///
  bool c_gt(const e3_lite& xother) const;

  ///
  /// Cartesian order greater than or equal comparison.
  ///
  bool c_ge(const e3_lite& xother) const;

  ///
  /// Dictionary (lexicographic) order less than comparison.
  ///
  bool d_lt(const e3_lite& xother) const;

  ///
  /// Dictionary (lexicographic) order less than or equal comparison.
  ///
  bool d_le(const e3_lite& xother) const;

  ///
  /// Dictionary (lexicographic) order greater than comparison.
  ///
  bool d_gt(const e3_lite& xother) const;

  ///
  /// Dictionary (lexicographic) order greater than or equal comparison.
  ///
  bool d_ge(const e3_lite& xother) const;
  
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS E3_LITE
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
  virtual e3_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual e3_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}



  //============================================================================
  /// @name ANY FACET OF CLASS E3_LITE
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
// CLASS E3
//==============================================================================

class tp_space;

///
/// Euclidean vector space of dimension 3
/// (persistent version).
///
class SHEAF_DLL_SPEC e3 : public ed
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS E3
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
  /// and table attribute scalar_space_path specified by xscalar_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path,
			     const poset_path& xscalar_space_path,
			     bool xauto_access);

  ///
  /// The host with path standard_host_path<e3>(xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (E3) FACET OF CLASS E3
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef e3_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef e3_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e3 vector_space_type;

  ///
  /// Default constructor.
  ///
  e3();

  // New handle/old state constructors.

  ///
  /// Creates a new e3 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  e3(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new e3 handle attached to the member state with id xid
  /// in xhost.
  ///
  e3(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new e3 handle attached to the member state with name xname
  /// in xhost.
  ///
  e3(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new e3 handle attached to the same state as xother.
  ///
  explicit e3(abstract_poset_member* xother);

  ///
  /// Creates a new e3 handle attached to a new jim state in xhost.
  ///
  e3(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Creates a new e3 handle attached to a new jim state in xhost,
  /// initialized with the dofs in xrdt.
  ///
  e3(poset_state_handle& xhost,
     const row_dofs_type& xrdt,
     bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  e3& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual e3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  e3& operator=(const e3& xother);

  ///
  /// Destructor.
  ///
  ~e3();

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
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (AT1) FACET OF CLASS E3
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS E3
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS E3
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS E3
  //===========================================================================
  //@{

public:

  using ed::put_components;

  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(dof_type x_comp,
                              dof_type y_comp,
                              dof_type z_comp);

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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E3
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS E3
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
  virtual e3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline e3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<e3*>(ed::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS E3
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
/// Insert e3_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const e3_row_dofs_type<T>& xrdt);

///
/// The deep size of the referenced object of type e3_lite.
/// if xinclude_shallow, add the sizeof x0 to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const e3_lite& x0, bool xinclude_shallow = true);

//==============================================================================
// E3 FACET:
//==============================================================================

///
/// Namespace containing the 3D Euclidean vector algebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace e3_algebra
{

///
/// The 3D Euclidean vector "cross" product of x0 with x1
/// (pre-allocated version).
///
void SHEAF_DLL_SPEC cross(const e3& x0, const e3& x1, e3& xresult, bool xauto_access);

///
/// The 3D Euclidean vector "cross" product of xresult with xother
/// (self-allocated version).
///
void SHEAF_DLL_SPEC cross_equal(e3& xresult, const e3& xother, bool xauto_access);

///
/// The 3D Euclidean vector "cross" product of x0 with x1
/// (auto-allocated version).
///
SHEAF_DLL_SPEC e3_lite* cross(const e3_lite& x0, const e3_lite& x1);

///
/// The 3D Euclidean vector "cross" product of x0 with x1
/// (pre-allocated version).
///
void SHEAF_DLL_SPEC cross(const e3_lite& x0, const e3_lite& x1, e3_lite& xresult);

///
/// The 3D Euclidean vector "cross" product of xresult with xother
/// (self-allocated version).
///
void SHEAF_DLL_SPEC cross_equal(e3_lite& xresult, const e3_lite& xother);

///
/// The 3D Euclidean vector "cross" product of x0 with x1
/// (auto-allocated version).
///
SHEAF_DLL_SPEC e3_lite* operator^(const e3_lite& x0, const e3_lite& x1);

///
/// The 3D Euclidean vector "cross" product of xresult with xother
/// (pre-allocated version).
///
SHEAF_DLL_SPEC e3_lite& operator^=(e3_lite& xresult, const e3_lite& xother);
  
} // namespace e3_algebra

//==============================================================================
// TP FACET
//==============================================================================

// Forward declarations needed for specialization:

class at0_lite;
class at2_e3_lite;
class at3_e3_lite;
class st2_e3_lite;
class st3_e3_lite;
class st4_e3_lite;
class t2_e3_lite;
class t3_e3_lite;
class t4_e3_lite;

class at0;
class at2_e3;
class at3_e3;
class st2_e3;
class st3_e3;
class st4_e3;
class t2_e3;
class t3_e3;
class t4_e3;


///
/// Specialization for degree 0 tensors over e3_lite.
///
template<> class tensor_traits<0, e3_lite>
{
public:
  ///
  /// Type of general tensor of degree 0 over e3_lite.
  ///
  typedef at0_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 0 over e3_lite.
  ///
  typedef at0_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 0 over e3_lite.
  ///
  typedef at0_lite stp_type;
};
  
///
/// Specialization for degree 1 tensors over e3_lite.
///
template<> class tensor_traits<1, e3_lite>
{
public:
  ///
  /// Type of general tensor of degree 1 over e3_lite.
  ///
  typedef e3_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 1 over e3_lite.
  ///
  typedef e3_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 1 over e3_lite.
  ///
  typedef e3_lite stp_type;
};
  
///
/// Specialization for degree 2 tensors over e3_lite.
///
template<> class tensor_traits<2, e3_lite>
{
public:
  ///
  /// Type of general tensor of degree 2 over e3_lite.
  ///
  typedef t2_e3_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 2 over e3_lite.
  ///
  typedef at2_e3_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 2 over e3_lite.
  ///
  typedef st2_e3_lite stp_type;
};
  
///
/// Specialization for degree 3 tensors over e3_lite.
///
template<> class tensor_traits<3, e3_lite>
{
public:
  ///
  /// Type of general tensor of degree 3 over e3_lite.
  ///
  typedef t3_e3_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 3 over e3_lite.
  ///
  typedef at3_e3_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 3 over e3_lite.
  ///
  typedef st3_e3_lite stp_type;
};
  
///
/// Specialization for degree 4 tensors over e3_lite.
///
template<> class tensor_traits<4, e3_lite>
{
public:
  ///
  /// Type of general tensor of degree 4 over e3_lite.
  ///
  typedef t4_e3_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 4 over e3_lite.
  ///
  typedef void atp_type;

  ///
  /// Type of symmetric tensor of degree 4 over e3_lite.
  ///
  typedef st4_e3_lite stp_type;
};

///
/// Specialization for degree 0 tensors over e3.
///
template<> class tensor_traits<0, e3>
{
public:
  ///
  /// Type of general tensor of degree 0 over e3.
  ///
  typedef at0 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 0 over e3.
  ///
  typedef at0 atp_type;

  ///
  /// Type of symmetric tensor of degree 0 over e3.
  ///
  typedef at0 stp_type;
};
  
///
/// Specialization for degree 1 tensors over e3.
///
template<> class tensor_traits<1, e3>
{
public:
  ///
  /// Type of general tensor of degree 1 over e3.
  ///
  typedef e3 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 1 over e3.
  ///
  typedef e3 atp_type;

  ///
  /// Type of symmetric tensor of degree 1 over e3.
  ///
  typedef e3 stp_type;
};
  
///
/// Specialization for degree 2 tensors over e3.
///
template<> class tensor_traits<2, e3>
{
public:
  ///
  /// Type of general tensor of degree 2 over e3.
  ///
  typedef t2_e3 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 2 over e3.
  ///
  typedef at2_e3 atp_type;

  ///
  /// Type of symmetric tensor of degree 2 over e3.
  ///
  typedef st2_e3 stp_type;
};
  
///
/// Specialization for degree 3 tensors over e3.
///
template<> class tensor_traits<3, e3>
{
public:
  ///
  /// Type of general tensor of degree 3 over e3.
  ///
  typedef t3_e3 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 3 over e3.
  ///
  typedef at3_e3 atp_type;

  ///
  /// Type of symmetric tensor of degree 3 over e3.
  ///
  typedef st3_e3 stp_type;
};
  
///
/// Specialization for degree 4 tensors over e3.
///
template<> class tensor_traits<4, e3>
{
public:
  ///
  /// Type of general tensor of degree 4 over e3.
  ///
  typedef t4_e3 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 4 over e3.
  ///
  typedef void atp_type;

  ///
  /// Type of symmetric tensor of degree 4 over e3.
  ///
  typedef st4_e3 stp_type;
};


class gl3_lite;

//==============================================================================
// VD FACET
//==============================================================================

namespace vd_algebra
{

//@hack Need to move this to vd.h.

///
/// Transform the basis and components of xv by xtransform.
///
SHEAF_DLL_SPEC void transform_basis_by(e3_lite& xv, const gl3_lite& xtransform,
				       bool is_contravariant = true);

///
/// Weighted sum x0*(1-xt) + x1*xt (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void add(const e3_lite& x0, const e3_lite& x1, vd_value_type xt, e3_lite& xresult);

// ===========================================================
// VECTOR ALGEBRA: TOLERANCE COMPARISON
// ===========================================================

///
/// Absolute equality comparison of e3_lite x0 to e3_lite x1 using tolerance double_tolerance.
///
SHEAF_DLL_SPEC bool a_eql(const e3_lite& x0, const e3_lite& x1);
  
///
/// Absolute equality comparison of e3_lite x0 to e3_lite x1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC bool a_eql(const e3_lite& x0, const e3_lite& x1, double xtolerance);
  
///
/// Absolute equality comparison of e3_lite x0 to e3_lite x1 using tolerance e3_lite xtolerance.
///
SHEAF_DLL_SPEC bool a_eql(const e3_lite& x0, const e3_lite& x1, const e3_lite& xtolerance);

///
/// Relative equality comparison of e3_lite x0 to e3_lite x1 using tolerance double_tolerance.
///
SHEAF_DLL_SPEC bool r_eql(const e3_lite& x0, const e3_lite& x1);
  
///
/// Relative equality comparison of e3_lite x0 to e3_lite x1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC bool r_eql(const e3_lite& x0, const e3_lite& x1, double xtolerance);
  
///
/// Relative equality comparison of e3_lite x0 to e3_lite x1 using tolerance e3_lite xtolerance.
///
SHEAF_DLL_SPEC bool r_eql(const e3_lite& x0, const e3_lite& x1, const e3_lite& xtolerance);
  
///
/// Combined equality equality comparison of e3_lite x0 to e3_lite x1 using tolerance double_tolerance.
///
SHEAF_DLL_SPEC bool c_eql(const e3_lite& x0, const e3_lite& x1);
  
///
/// Combined equality equality comparison of e3_lite x0 to e3_lite x1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC bool c_eql(const e3_lite& x0, const e3_lite& x1, double xtolerance);
  
///
/// Combined equality equality comparison of e3_lite x0 to e3_lite x1 using tolerance e3_lite xtolerance.
///
SHEAF_DLL_SPEC bool c_eql(const e3_lite& x0, const e3_lite& x1, const e3_lite& xtolerance);
  
} // namespace vd_algebra

} // namespace fiber_bundle

#endif // ifndef E3_H
