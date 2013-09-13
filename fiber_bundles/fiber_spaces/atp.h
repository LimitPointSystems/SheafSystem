
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
/// Interface for class atp.

#ifndef ATP_H
#define ATP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TP_H
#include "tp.h"
#endif

namespace fiber_bundle
{
  class atp_space;
  
//==============================================================================
// CLASS ATP_LITE
//==============================================================================

///
/// An antisymmetric tensor of degree p over an abstract vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC atp_lite : public tp_lite
{
  //============================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS ATP_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  atp_lite();

  ///
  /// Copy constructor.
  ///
  atp_lite(const atp_lite& xother);

  ///
  /// Assignment operator.
  ///
  atp_lite& operator=(const atp_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~atp_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  atp_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  atp_lite& operator=(const row_dofs_type& xrow_dofs);


protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ATP_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ATP_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ATP_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ATP_LITE
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
  virtual atp_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ATP_LITE
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
// CLASS ATP
//==============================================================================

///
/// An antisymmetric tensor of degree p.
///
class SHEAF_DLL_SPEC atp : public tp
{
  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef atp_space host_type;

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
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS ATP
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef atp_lite volatile_type;

  ///
  /// Default constructor.
  ///
  atp();

  ///
  /// Creates a new atp handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  atp(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new atp handle attached to the member state with id xid
  /// in xhost.
  ///
  atp(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new atp handle attached to the member state with name xname
  /// in xhost.
  ///
  atp(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new atp handle attached to the same state as xother.
  ///
  explicit atp(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  atp(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual atp& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  atp& operator=(const atp& xother);

  ///
  /// Destructor.
  ///
  virtual ~atp();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

  ///
  /// True if this is a p-form;
  /// synonym for is_covariant(xauto_access).
  ///
  bool is_p_form(bool xauto_access) const;

  ///
  /// Sets is_p_form to true;
  /// synonym for put_is_covariant(xauto_access).
  ///
  void put_is_p_form(bool xauto_access);

  ///
  /// True if this is a p-vector;
  /// synonym for is_contravariant(xauto_access).
  ///
  bool is_p_vector(bool xauto_access) const;

  ///
  /// Sets is_p_vector to true;
  /// synonym for put_is_contravariant(xauto_access).
  ///
  void put_is_p_vector(bool xauto_access);

protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS ATP
  //============================================================================
  //@{

public:
  
protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS ATP
  //============================================================================
  //@{

public:
protected:
private:

  //@}

  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ATP
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
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline atp* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<atp*>(tp::clone(xnew_state, xauto_access));
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
  /// @name ANY FACET OF CLASS ATP
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to current.
  ///
  bool is_ancestor_of(const any* xother) const;
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual atp* clone() const;

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

//==============================================================================
// ATP FACET:
//==============================================================================

///
/// Namespace containing the antisymmetric tensor algrebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace atp_algebra
{

///
/// The interior (hook) product of two antisymmetric tensors
/// (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void hook(const atp& x0, const atp& x1, atp& xresult, bool xauto_access);

///
/// The interior (hook) product of two antisymmetric tensors
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void hook(const atp_lite& x0, const atp_lite& x1, atp_lite& xresult);

#ifndef SWIG

///
/// The interior (hook) product of two antisymmetric tensors
/// (auto-allocated version for volatile types).
///
template <typename T0, typename T1>
typename tensor_traits<static_cast<int>(T0::P) - static_cast<int>(T1::P), typename T0::vector_space_type>::atp_type*
hook(const T0& x0, const T1& x1);

///
/// The interior (hook) product of two antisymmetric tensors
/// (auto-allocated version for persistent types).
///
template <typename T0, typename T1>
typename tensor_traits<static_cast<int>(T0::P) - static_cast<int>(T1::P), typename T0::vector_space_type>::atp_type*
hook(const T0& x0, const T1& x1, bool xauto_access);

#endif

///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version persistent types).
///
SHEAF_DLL_SPEC void star(const atp& x0, atp& xresult, bool xauto_access);

///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void star(const atp_lite& x0, atp_lite& xresult);

///
/// The Hodge star operator for antisymmetric tensors
/// (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC atp_lite* star(const atp_lite& x0);

///
/// The exterior (wedge) product of two antisymmetric tensors
/// (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void wedge(const atp& x0, const atp& x1, atp& xresult, bool xauto_access);

///
/// The exterior (wedge) product of two antisymmetric tensors
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void wedge(const atp_lite& x0, const atp_lite& x1, atp_lite& xresult);

#ifndef SWIG

///
/// The exterior (wedge) product of two antisymmetric tensors
/// (auto-allocated version for volatile types).
///
template <typename T0, typename T1>
typename tensor_traits<static_cast<int>(T0::P) + static_cast<int>(T1::P), typename T0::vector_space_type>::atp_type*
wedge(const T0& x0, const T1& x1);

///
/// The exterior (wedge) product of two antisymmetric tensors
/// (auto-allocated version for persistent types).
///
template <typename T0, typename T1>
typename tensor_traits<static_cast<int>(T0::P) + static_cast<int>(T1::P), typename T0::vector_space_type>::atp_type*
wedge(const T0& x0, const T1& x1, bool xauto_access);

#endif

} // namespace atp_algebra

} // namespace fiber_bundle


#endif // ifndef ATP_H
