
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
/// Interface for class tp

#ifndef TP_H
#define TP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef VD_H
#include "vd.h"
#endif

#ifndef TENSOR_VARIANCE_H
#include "tensor_variance.h"
#endif

#ifndef TP_TABLE_DOFS_TYPE_H
#include "tp_table_dofs_type.h"
#endif
 
 
namespace fiber_bundle
{
  //
  // Forward declarations
  //

  class tp_space;
  class at1;

//==============================================================================
// CLASS TP_LITE
//==============================================================================

///
/// A general tensor of degree p over an abstract vector space
/// (volatile version). Volatile version does not support tensor
/// type ("variance"); see further comments in class tp.
///
class SHEAF_DLL_SPEC tp_lite : public vd_lite
{
  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS TP_LITE
  //============================================================================
  //@{

public:

  ///
  /// The type of the table dofs.
  ///
  typedef tp_table_dofs_type table_dofs_type;

  ///
  /// Type of underlying vector space.
  /// @issue we may need to move this up to vd
  ///
  typedef vd_lite vector_space_type;

  ///
  /// The degree of this tensor space.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = -1};  

  ///
  /// Default constructor.
  ///
  tp_lite();

  ///
  /// Copy constructor.
  ///
  tp_lite(const tp_lite& xother);

  ///
  /// Assignment operator.
  ///
  tp_lite& operator=(const tp_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~tp_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  tp_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  tp_lite& operator=(const row_dofs_type& xrow_dofs);

  /// The degree of the tensor; 
  /// the sum of the contravariant and covariant degrees.
  ///
  virtual int p() const;

  ///
  /// Dimension of the underlying vector space.
  ///
  virtual int dd() const;

  ///
  /// Index of the underlying vector space.
  ///
  virtual pod_index_type vector_space_index() const;

  ///
  /// The table dofs.
  ///
  table_dofs_type table_dofs() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS TP_LITE
  //============================================================================
  //@{

public:

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS TP_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS TP_LITE
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
  virtual tp_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS TP_LITE
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
// CLASS TP
//==============================================================================

///
/// A general tensor of "degree" p and given "variance" over an abstract vector space.
///
/// The notion of tensor "degree" and "variance" are not the standard properties
/// described in most texts, although they are closely related to those properties.
/// They are introduced in this and related classes because they more directly
/// describe the software implementation than the standard terms.
/// 
/// We define the "degree" of the tensor as the sum of the contravariant degree 
/// and the covariant degree. Each tensor type forms a vector space, but the 
/// dimension of the vector space depends only on degree, not on the co- or
/// contravariance of the indices. Hence all tensor types of a given
/// degree form vector spaces of the same dimension. Since the computer
/// representation depends on the vector space properties, it is convenient
/// to represent all tensor types of a given degree with a single sheaf/C++ type 
/// and to let the tensor types coexist in a single poset using subposets
/// to keep them sorted out. This minimizes storage requirements for both
/// fibers and sections. It also simplifies the raising and lowering operators 
/// since they then work entirely within a single poset.
///
/// We define the "variance" of a tensor as an ordered specification of the
/// co- or contra-variance of each index. See class tensor_variance for a full
/// discussion.
///
class SHEAF_DLL_SPEC tp : public vd
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS TP
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef tp_space host_type;

  ///
  /// The type of the underlying vector space.
  ///
  typedef at1 vector_space_type;

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
			     int xp,
			     const poset_path& xvector_space_path,
			     bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS TP
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The associated volatile type.
  ///
  typedef tp_lite volatile_type;

  ///
  /// The type of the table dofs.
  ///
  typedef tp_table_dofs_type table_dofs_type;

  ///
  /// Default constructor.
  ///
  tp();

  ///
  /// Creates a new tp handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  tp(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new tp handle attached to the member state with id xid
  /// in xhost.
  ///
  tp(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new tp handle attached to the member state with name xname
  /// in xhost.
  ///
  tp(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new tp handle attached to the same state as xother.
  ///
  explicit tp(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  tp(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual tp& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  tp& operator=(const tp& xother);

  ///
  /// Destructor.
  ///
  virtual ~tp();

  ///
  /// The degree of this tensor space.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = -1};  

  ///
  /// The degree of the tensors in host(); 
  /// the sum of the contravariant and covariant degrees.
  ///
  virtual int p() const;

  ///
  /// The degree of the tensors in host()
  /// (auto-access version).
  ///
  int p(bool xauto_access) const;

  ///
  /// Dimension of the underlying vector space.
  ///
  virtual int dd() const;

  ///
  /// Dimension of the underlying vector space (auto-access version).
  ///
  virtual int dd(bool xauto_access) const;

  ///
  /// The path of the underlying vector space.
  ///
  poset_path vector_space_path() const;

  ///
  /// The path of the underlying vector space, auto access version.
  ///
  poset_path vector_space_path(bool xauto_access) const;

  ///
  /// The underlying vector space.
  ///
  virtual tp_space& vector_space() const;

  ///
  /// The underlying vector space, auto access version.
  ///
  virtual tp_space& vector_space(bool xauto_access) const;

  ///
  ///  Create a standard tensor space name.
  ///
  static const std::string create_tensor_space_name(const std::string& xvector_space_name, const std::string& xname);

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

  ///
  /// The variance.
  ///
  virtual tensor_variance variance(bool xauto_access) const;

  ///
  /// The variance of the xi-th tensor index position;
  /// true if covariant, false if contravariant.
  ///
  virtual bool variance(int xi, bool xauto_access) const;

  ///
  /// Sets the variance to xvariance.
  ///
  void put_variance(const tensor_variance& xvariance, bool xauto_access);

  ///
  /// Sets the variance of the xi-th index to xvariance.
  ///
  void put_variance(int xi, bool xvariance, bool xauto_access);
    
  ///
  /// True if and only if all tensor index positions are covariant.
  ///
  virtual bool is_covariant(bool xauto_access) const;
    
  ///
  /// True if and only if the xi-th tensor index position is covariant.
  ///
  virtual bool is_covariant(int xi, bool xauto_access) const;
   
  ///
  /// Sets all tensor index positions to covariant.
  ///
  virtual void put_is_covariant(bool xauto_access);
  
  ///
  /// Sets the variance of the xi-th tensor index position to covariant.
  ///
  void put_is_covariant(int xi, bool xauto_access);
 
  ///
  /// True if and only if all tensor index positions are contravariant.
  ///
  virtual bool is_contravariant(bool xauto_access) const;
 
  ///
  /// True if and only if the xi-th tensor index position is contravariant.
  ///
  virtual bool is_contravariant(int xi, bool xauto_access) const;
   
  ///
  /// Sets all tensor index positions to contravariant.
  ///
  virtual void put_is_contravariant(bool xauto_access);  
  
  ///
  /// Sets the variance of the xi-th tensor index position to contravariant.
  ///
  void put_is_contravariant(int xi, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS TP
  //============================================================================
  //@{

public:

//   ///
//   /// True if this is a covector, false if it is a vector.
//   ///
//   virtual bool is_dual(bool xauto_access) const;

//   ///
//   /// Set the duality of this to that of xother if
//   /// xis_opposite is false and to the opposite of
//   /// xother if xis_opposite is true. 
//   ///
//   virtual void put_is_dual(const vd& xother, bool xis_opposite, bool xauto_access);

protected:
private:

  //@}

  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS TP
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
  inline tp* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<tp*>(vd::clone(xnew_state, xauto_access));
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
  /// @name ANY FACET OF CLASS TP
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
  virtual tp* clone() const;

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
/// Insert tp_lite::table_dofs_type& xt into ostream& xos.
///
SHEAF_DLL_SPEC std::ostream& operator<<(std::ostream& xos, tp_lite::table_dofs_type& xt);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

//==============================================================================
// TP FACET
//==============================================================================

///
/// Namespace containing the general tensor algrebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace tp_algebra
{

///
/// Contraction on contravariant index xp and covariant index xq
/// (pre-allocated version for volatile types).
/// The arguments xp and xq are indices into the "variance type" bitset.
/// This implies that xp != xq.
/// 
SHEAF_DLL_SPEC void contract(const tp_lite& x0, int xp, int xq, tp_lite& xresult);

///
/// Contraction on contravariant index xp and covariant index xq
/// (pre-allocated, access control version for persistent types).
/// The arguments xp and xq are indices into the "variance type" bitset.
/// This implies that xp != xq. 
///
SHEAF_DLL_SPEC void contract(const tp& x0, int xp, int xq, tp& xresult,
			    bool xauto_access);

//==============================================================================

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void alt(const tp_lite& x0, tp_lite& xresult);

///
/// The alternating (antisymmetric) part of tensor x0
/// (auto-allocated version for volatile types).
///
template <typename T0>
typename tensor_traits<T0::P, typename T0::vector_space_type>::atp_type*
alt(const T0& x0);

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void alt(const tp& x0, tp& xresult, bool xauto_access);

///
/// The symmetric part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void sym(const tp_lite& x0, tp_lite& xresult);

///
/// The symmetric part of tensor x0
/// (auto-allocated version for volatile types).
///
template <typename T0>
typename tensor_traits<T0::P, typename T0::vector_space_type>::stp_type*
sym(const T0& x0);

///
/// The symmetric part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void sym(const tp& x0, tp& xresult, bool xauto_access);

///
/// The symmetric part of tensor x0
/// (auto-allocated version for persistent types).
///
template <typename T0>
typename tensor_traits<T0::P, typename T0::vector_space_type>::stp_type*
sym(const T0& x0, bool xauto_access);

//==============================================================================

///
/// Tensor product
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void tensor(const tp_lite& x0, const tp_lite& x1, tp_lite& xresult);

///
/// Tensor product
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void tensor(const tp& x0, const tp& x1, tp& xresult, bool xauto_access);

///
/// Tensor product
/// (auto-allocated version for volatile types).
///
template <typename T0, typename T1>
typename tensor_traits<T0::P + T1::P, typename T0::vector_space_type>::tp_type*
tensor(const T0& x0, const T1& x1);

///
/// Tensor product
/// (auto-allocated version for persistent types).
///
template <typename T0, typename T1>
typename tensor_traits<T0::P + T1::P, typename T0::vector_space_type>::tp_type*
tensor(const T0& x0, const T1& x1, bool xauto_access);


//==============================================================================
  
} // namespace tp_algebra

} // namespace fiber_bundle


#endif // ifndef TP_H
