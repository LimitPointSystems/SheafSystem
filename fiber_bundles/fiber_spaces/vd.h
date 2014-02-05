
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Interface for class vd.

#ifndef VD_H
#define VD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef PRIMITIVE_TYPE_H
#include "primitive_type.h"
#endif

#ifndef TUPLE_H
#include "tuple.h"
#endif

#ifndef STD_CMATH_H
#include "std_cmath.h"
#endif

#ifndef VD_TABLE_DOFS_TYPE_H
#include "vd_table_dofs_type.h"
#endif
 
namespace fiber_bundle
{
  //
  // Forward declarations
  //

  class at0;
  class vd_space;  

//==============================================================================
// CLASS VD_ROW_DOFS_TYPE
//==============================================================================
 
///
/// Row dofs type for class vd.
///
template <typename T>
class vd_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef vd_row_dofs_type<T> row_dofs_type;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
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
  row_dofs_type* clone() const;
};


//==============================================================================
// CLASS VD_LITE
//==============================================================================

class tp_lite;
class atp_lite;
class stp_lite;

///
/// Abstract vector space over dof_type
/// (volatile version).
///
class SHEAF_DLL_SPEC vd_lite : public tuple_lite
{
  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS VD_LITE
  //============================================================================
  //@{

public:

  ///
  /// The type of the degrees of freedom.
  ///
  typedef vd_dof_type dof_type;

  ///
  /// The type of component in the fiber;
  /// the scalar type in the fiber vector space.
  ///
  typedef vd_value_type value_type;

  ///
  /// The type of the table dofs.
  ///
  typedef vd_table_dofs_type table_dofs_type;

  ///
  /// The type of the row dofs.
  ///
  typedef vd_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  vd_lite();

  ///
  /// Copy constructor.
  ///
  vd_lite(const vd_lite& xother);

  ///
  /// Copy assignment operator.
  ///
  vd_lite& operator=(const vd_lite& xother);

  ///
  /// True if this has the same components as xother.
  ///
  bool operator==(const vd_lite& xother) const;

  ///
  /// Destructor.
  ///
  virtual ~vd_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  vd_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Row_dofs_type assignment operator.
  ///
  vd_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

  ///
  /// The xindex-th component.
  ///
  value_type component(int xindex) const;

  ///
  /// Set the xindex-th component to xcomp.
  ///
  void put_component(int xindex, value_type xcomp);

  ///
  /// The values of all the components (preallocated version).
  ///
  virtual void components(dof_type xresult[], int comps_dimension) const;

  ///
  /// Set values of all the components to the values in xcomps.
  ///
  virtual void put_components(const dof_type xcomps[], int xcomps_dimension);

  ///
  /// Value_type assignment operator; sets all components to xvalue.
  ///
  vd_lite& operator=(const value_type& xvalue);

  ///
  /// Equality comparison to scalar; true if and only if all components == xvalue.
  /// Especially useful for comparison to 0.0.
  ///
  bool operator==(const value_type& xvalue) const;

  ///
  /// The value of the component corresponding to xindex
  /// (non const version).
  ///
  virtual value_type& operator[] (int xindex);

  ///
  /// The value of the component corresponding to xindex
  /// (const version).
  ///
  virtual const value_type& operator[] (int xindex) const;

  ///
  /// Static prototype for general tensors 
  /// of degree xp over this vector space.
  ///
  static const tp_lite& static_tp_prototype(int xp);

  ///
  /// Virtual constructor for general tensors 
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS VD_LITE
  //============================================================================
  //@{

public:

  ///
  /// Number of factors (components) in tuple.
  ///
  virtual int factor_ct() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  ///
  virtual vd_lite* clone() const;

  ///
  /// The table dofs.
  ///
  table_dofs_type table_dofs() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS VD_LITE
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

protected:
private:

  //@}
};


//==============================================================================
// CLASS VD
//==============================================================================


///
/// Abstract vector space over dof_type.
///
class SHEAF_DLL_SPEC vd : public tuple
{
  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef vd_space host_type;

  ///
  /// The type of scalar.
  ///
  typedef at0 scalar_type;

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

protected:

private:

  //@}
 
  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS VD
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the table dofs.
  ///
  typedef vd_table_dofs_type table_dofs_type;

  ///
  /// The type of the row dofs.
  ///
  typedef vd_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef vd_lite volatile_type;

  ///
  /// The POD ("plain old data") type of scalar in the vector space of this.
  ///
  typedef vd_value_type value_type;

  ///
  /// The type of the degrees of freedom.
  /// Note that although dof_type == value_type in this implementation,
  /// in prinicple they are different roles and are not necessarily the
  //  same type.
  ///
  typedef vd_dof_type dof_type;

  ///
  /// The sheaf primitive type of the degrees of freedom.
  ///
  //static const primitive_type sheaf_dof_type;

  ///
  /// Default constructor.
  ///
  vd();

  ///@todo Implement copy constructor.

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual vd& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  vd& operator=(const vd& xother);

  ///
  /// Destructor.
  ///
  virtual ~vd();

  ///
  /// Constructs a new jim state in xhost and attaches this to it.
  ///
  vd(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Creates a new vd handle attached to the member state with hub id xhub_id
  /// in xhost.
  ///
  vd(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new vd handle attached to the member state with id xid
  /// in xhost.
  ///
  vd(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new vd handle attached to the member state with name xname
  /// in xhost.
  ///
  vd(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new vd handle attached to the same state as xother.
  ///
  explicit vd(const abstract_poset_member* xother);

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

  ///
  /// Dimension of this as a vector space; auto-access version.
  ///
  virtual int d(bool xauto_access) const;

  ///
  /// The path of the underlying scalar space.
  ///
  poset_path scalar_space_path() const;

  ///
  /// The path of the underlying scalar space; auto-access version.
  ///
  poset_path scalar_space_path(bool xauto_access) const;
  
  ///
  /// The value of the xi-th component.
  ///
  virtual value_type component(int xindex) const;

  ///
  /// The value of the xindex-th component.
  ///
  value_type component(int xindex, bool xauto_access) const;

  ///
  /// Sets the value of the xindex-th component to xvalue.
  ///
  virtual void put_component(int xindex, value_type xvalue);

  ///
  /// Sets the value of the xindex-th component to xvalue.
  ///
  void put_component(int xindex, value_type xvalue, bool xauto_access);

  ///
  /// The values of all the components (pre-allocated version).
  ///
  void components(dof_type comps[], int comps_dimension) const;

  ///
  /// Sets values of all the components to the values in comps.
  ///
  void put_components(const dof_type comps[], int comps_dimension);

  ///
  /// The value of the row dof corresponding to xindex
  /// (non const version).
  ///
  dof_type& operator[] (int xindex);

  ///
  /// The value of the row dof corresponding to xindex.
  /// (const version)
  ///
  const dof_type& operator[] (int xindex) const;

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

  ///
  /// True if and only if this is a vector (as opposed to a covector).
  ///
  virtual bool is_vector(bool xauto_access) const;

  ///
  /// Sets is_vector true.
  ///
  virtual void put_is_vector(bool xauto_access);

  ///
  /// True if and only if this is a covector.
  ///
  virtual bool is_covector(bool xauto_access) const;;

  ///
  /// Sets is_covector true.
  ///
  virtual void put_is_covector(bool xauto_access);

protected:
private:

  //@}

  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS VD
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline vd* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<vd*>(tuple::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}

  // ===========================================================
  /// @name POSET_COMPONENT FACET
  // ===========================================================
  //@{

public:

  ///
  /// The poset this is a member of.
  ///
  host_type* host() const;

  ///
  /// True if other conforms to host.
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* other) const;

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS VD
  //============================================================================
  //@{

public:

  ///
  /// True if other conforms to current.
  ///
  bool is_ancestor_of(const any* other) const;
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual vd* clone() const;

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

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert vd_lite& x0 into ostream& xos.
///
SHEAF_DLL_SPEC std::ostream& operator<<(std::ostream& xos, const vd_lite& x0);

///
/// Insert vd& x0 into ostream& xos.
///
SHEAF_DLL_SPEC std::ostream& operator<<(std::ostream& xos, const vd& x0);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

// ===========================================================
// TENSOR TRAITS
// ===========================================================

 

// Forward declarations needed for specialization:

class at2_lite;
class at3_lite;
class atp_lite;
class st2_lite;
class st3_lite;
class st4_lite;
class stp_lite;
class t2_lite;
class t3_lite;
class t4_lite;
class tp_lite;

///
/// Tensor types of degree P over VECTOR_TYPE.
/// No generic implementation defined, 
/// must be specialized for every supported
/// combination of VECTOR_TYPE and P.
///
template <int P, typename VECTOR_TYPE> class tensor_traits;

///
/// Tensor types of degree 0 over vd_lite; full specialization.
///
template <>
class tensor_traits<0, vd_lite>
{
public:
  ///
  /// Type of general tensor of degree 0 over vd_lite.
  ///
  typedef at0 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 0 over vd_lite.
  ///
  typedef at0 atp_type;

  ///
  /// Type of symmetric tensor of degree 0 over vd_lite.
  ///
  typedef at0 stp_type;
};

///
/// Tensor types of degree 1 over vd_lite; full specialization.
///
template <>
class tensor_traits<1, vd_lite>
{
public:
  ///
  /// Type of general tensor of degree 1 over vd_lite.
  ///
  typedef vd_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 1 over vd_lite.
  ///
  typedef vd_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 1 over vd_lite.
  ///
  typedef vd_lite stp_type;
};

///
/// Tensor types of degree 2 over vd_lite; full specialization.
///
template <>
class tensor_traits<2, vd_lite>
{
public:
  ///
  /// Type of general tensor of degree 2 over vd_lite.
  ///
  typedef t2_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 2 over vd_lite.
  ///
  typedef at2_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 2 over vd_lite.
  ///
  typedef st2_lite stp_type;
};

///
/// Tensor types of degree 3 over vd_lite; full specialization.
///
template <>
class tensor_traits<3, vd_lite>
{
public:
  ///
  /// Type of general tensor of degree 3 over vd_lite.
  ///
  typedef t3_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 3 over vd_lite.
  ///
  typedef at3_lite atp_type;

  ///
  /// Type of symmetric tensor of degree 3 over vd_lite.
  ///
  typedef st3_lite stp_type;
};

///
/// Tensor types of degree 4 over vd_lite; full specialization.
///
template <>
class tensor_traits<4, vd_lite>
{
public:
  ///
  /// Type of general tensor of degree 4 over vd_lite.
  ///
  typedef t4_lite tp_type;

  ///
  /// Type of antisymmetric tensor of degree 4 over vd_lite.
  ///
  typedef void atp_type;

  ///
  /// Type of symmetric tensor of degree 4 over vd_lite.
  ///
  typedef st4_lite stp_type;
};


// ===========================================================
// VECTOR ALGEBRA
// ===========================================================

///
/// Namespace containing the vector algrebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace vd_algebra
{

// ===========================================================
// VECTOR ALGEBRA: ADDITION
// ===========================================================
 
///
/// x0 add x1 (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void add(const vd& x0, const vd& x1, vd& xresult, bool xauto_access);

///
/// x0 add x1 (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void add(const vd_lite& x0, const vd_lite& x1, vd_lite& xresult);

///
/// Weighted sum x0*(1-xt) + x1*xt (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void add(const vd_lite& x0, const vd_lite& x1, vd_value_type xt, vd_lite& xresult);

///
/// x0 add x1 (auto-allocated version for volatile types).
///
template <typename T>
T* add(const T& x0, const T& x1);

///
/// x0 add x1 (self-allocated version for persistent types);
/// synonym for add(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC void add_equal(vd& xresult, const vd& xother, bool xauto_access);

///
/// x0 add x1 (self-allocated version for volatile types).
///
template <typename T>
void add_equal(T& xresult, const T& xother);

///
/// x0 + x1 (auto-allocated for volatile types);
/// synonym for add(x0, x1).
///
template <typename T>
T* operator+(const T& x0, const T& x1);

///
/// x0 += x1 (self-allocated for volatile types);
/// synonym for add_equal(x0, x1).
///
template <typename T>
T& operator+=(T& xresult, const T& xother);


// ===========================================================
// VECTOR ALGEBRA: SUBTRACTION
// ===========================================================

///
/// x0 subtract x1 (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void subtract(const vd& x0, const vd& x1, vd& xresult, bool xauto_access);

///
/// x0 subtract x1 (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void subtract(const vd_lite& x0, const vd_lite& x1, vd_lite& xresult);

///
/// x0 subtract x1 (auto-allocated version volatile types).
///
template <typename T>
T* subtract(const T& x0, const T& x1);

///
/// x0 subtract_equal x1 (self-allocated version for persistent types);
/// synonym for subtract(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC void subtract_equal(vd& xresult, const vd& xother, bool xauto_access);

///
/// x0 subtract_equal x1 (self-allocated version for volatile types).
///
template <typename T>
void subtract_equal(T& xresult, const T& xother);

///
/// x0 - x1 (auto-allocated for volatile types);
/// synonym for subtract(x0, x1).
///
template <typename T>
T* operator-(const T& x0, const T& x1);

///
/// x0 -= x1 (self-allocated for volatile types);
/// synonym for subtract_equal(x0, x1).
///
template <typename T>
T& operator-=(T& xresult, const T& xother);


// ===========================================================
// VECTOR ALGEBRA: SCALAR MULTIPLICATION
// ===========================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Vector x0 multiplied by scalar x1 (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void multiply(const vd& x0, const vd_value_type& x1, vd& xresult, bool xauto_access);

///
/// Vector xv multiplied by scalar x1 (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void multiply(const vd_lite& x0, const vd_value_type& x1, vd_lite& xresult);

///
/// Vector x0 multiplied by scalar x1 (auto-allocated version for volatile types).
///
template <typename T>
T* multiply(const T& x0, const vd_value_type& x1);

///
/// Vector x0 multiplied by scalar x1 (self-allocated version for persistent types);
/// synonym for multiply(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC void multiply_equal(vd& xresult, const vd_value_type& xother, bool xauto_access);

///
/// Vector x0 multiplied by scalar x1 (self-allocated version for volatile types).
///
template <typename T>
void multiply_equal(T& xresult, const vd_value_type& xother);

///
/// Vector x0 * scalar x1 (auto-allocated for volatile types);
/// synonym for multiply(x0, x1).
///
template <typename T>
T* operator*(const T& x0, const vd_value_type& x1);

///
/// Vector x0 *= scalar x1 (self-allocated for volatile types);
/// synonym for multiply_equal(x0, x1).
///
template <typename T>
T& operator*=(T& xresult, const vd_value_type& x1);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

// ===========================================================
// VECTOR ALGEBRA: SCALAR DIVISION
// ===========================================================

///
/// Vector x0 divided by scalar x1 (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void divide(const vd& x0, const vd_value_type& x1, vd& xresult,
			   bool xauto_access);

///
/// Vector xv divided by scalar x1 (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void divide(const vd_lite& x0, const vd_value_type& x1, vd_lite& xresult);

///
/// Vector x0 divided by scalar x1 (auto-allocated version for volatile types).
///
template <typename T>
T* divide(const T& x0, const vd_value_type& x1);

///
/// Vector x0 divided by scalar x1 (self-allocated version for persistent types);
/// synonym for divide(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC void divide_equal(vd& xresult, const vd_value_type& xother, bool xauto_access);

///
/// Vector x0 divided by scalar x1 (self-allocated version for volatile types).
///
template <typename T>
void divide_equal(T& xresult, const vd_value_type& x1);

///
/// Vector x0 / scalar x1 (auto-allocated for volatile types);
/// synonym for divide(x0, x1).
///
template <typename T>
T* operator/(const T& x0, const vd_value_type& x1);

///
/// Vector x0 /= scalar x1 (self-allocated for volatile types);
/// synonym for divide_equal(x0, x1).
///
template <typename T>
T& operator/=(T& xresult, const vd_value_type& x1);


#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

// ===========================================================
// VECTOR ALGEBRA: COMPONENT EXTREMA
// ===========================================================

///
/// Maximum component of x0, pre-allocated version.
///
SHEAF_DLL_SPEC void max(const vd& x0, vd_value_type& xresult, bool xauto_access);

///
/// Maximum component of x0, auto-allocated version.
///
SHEAF_DLL_SPEC vd_value_type max(const vd& x0, bool xauto_access);

///
/// Minimum component of x0, pre-allocated version.
///
///
SHEAF_DLL_SPEC void min(const vd& x0, vd_value_type& xresult, bool xauto_access);

///
/// Minimum component of x0, auto-allocated version.
///
SHEAF_DLL_SPEC vd_value_type min(const vd& x0, bool xauto_access);

///
/// Maximum component of x0, pre-allocated version.
///
SHEAF_DLL_SPEC void max(const vd_lite& x0, vd_value_type& xresult);

///
/// Maximum component of x0, auto-allocated version.
///
SHEAF_DLL_SPEC vd_value_type max(const vd_lite& x0);

///
/// Minimum component of x0, pre-allocated version.
///
SHEAF_DLL_SPEC void min(const vd_lite& x0, vd_value_type& xresult);

///
/// Minimum component of x0, auto-allocated version.
///
SHEAF_DLL_SPEC vd_value_type min(const vd_lite& x0);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

// ===========================================================
// VECTOR ALGEBRA: CONTRACTION
// ===========================================================

// Bishop and Goldberg's "natural pairing" makes for a
// nice theoretical development, but in use it's clumsy nomenclature.
// Koenderink calls the "natural pairing" operation "contract",
// because, once you have the general contraction operator defined,
// you can think of the "natural pairing" of vector v and a covector c
// as contracting the tensor vc on its 2 indices to form a scalar.
// But you need the special case vector on covector in order to define
// tensors in the first place, which is why B&G
// introduce it as the "natural pairing".
//
// Furthermore, the "natural pairing" is just another name for the
// action of covector c as a map of vectors to reals. The action as
// a map notion generalizes to the fundamental definition of all
// tensor types. Every tensor type of degree p is a map that takes
// p vectors and/or covectors as arguments and produces a scalar.
// Since we can always form the tensor product of these p arguments,
// we can think of the general tensor map action as contraction.
//
// So we'll follow Koenderink and name the map actions "contract"
// for all tensors.

///
/// Contraction of vector xvector on covector xcovector
/// (auto_allocated for volatile types).
///
SHEAF_DLL_SPEC vd_value_type contract(const vd_lite& xvector, const vd_lite& xcovector);

///
/// Contraction of vector xvector on covector xcovector
/// (auto_allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC vd_value_type contract(const vd& xvector, const vd& xcovector,
				      bool xauto_access);

// ===========================================================
// VECTOR ALGEBRA: TOLERANCE COMPARISON
// ===========================================================

///
/// Absolute equality comparison of vd_lite x0 to vd_lite x1 using tolerance double_tolerance.
///
SHEAF_DLL_SPEC bool a_eql(const vd_lite& x0, const vd_lite& x1);
  
///
/// Absolute equality comparison of vd_lite x0 to vd_lite x1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC bool a_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance);
  
///
/// Absolute equality comparison of vd_lite x0 to vd_lite x1 using vd_lite tolerance xtolerance.
///
SHEAF_DLL_SPEC bool a_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance);

///
/// Relative equality comparison of vd_lite x0 to vd_lite x1 using tolerance double_tolerance.
///
SHEAF_DLL_SPEC bool r_eql(const vd_lite& x0, const vd_lite& x1);
  
///
/// Relative equality comparison of vd_lite x0 to vd_lite x1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC bool r_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance);
  
///
/// Relative equality comparison of vd_lite x0 to vd_lite x1 using vd_lite tolerance xtolerance.
///
SHEAF_DLL_SPEC bool r_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance);
  
///
/// Combined equality equality comparison of vd_lite x0 to vd_lite x1 using tolerance double_tolerance.
///
SHEAF_DLL_SPEC bool c_eql(const vd_lite& x0, const vd_lite& x1);
  
///
/// Combined equality equality comparison of vd_lite x0 to vd_lite x1 using tolerance xtolerance.
///
SHEAF_DLL_SPEC bool c_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance);
  
///
/// Combined equality equality comparison of vd_lite x0 to vd_lite x1 using vd_lite tolerance xtolerance.
///
SHEAF_DLL_SPEC bool c_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance);


// ===========================================================
// MISCELLANEOUS
// ===========================================================

///@issue Where should we put these functions?

// Putting these functions in the fiber_bundle namespace
// for convenience.

///
/// Factorial of xi.
///
SHEAF_DLL_SPEC unsigned int factorial(unsigned int xi);

///
/// Binomial coefficient (xi, xj).
///
SHEAF_DLL_SPEC unsigned int binomial_coefficient(unsigned int xi, unsigned int xj);

//==============================================================================
  
} // namespace vd_algebra

} // namespace fiber_bundle

#endif // ifndef VD_H
