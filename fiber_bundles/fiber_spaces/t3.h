
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
/// Interface for class t3.


#ifndef T3_H
#define T3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TP_H
#include "tp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS T3_LITE
//==============================================================================

///
/// A tensor of degree 3 over an abstract vector space (volatile version).
///
class SHEAF_DLL_SPEC t3_lite : public tp_lite
{

  //============================================================================
  /// @name T3 FACET OF CLASS T3_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  t3_lite();

  ///
  /// Copy constructor.
  ///
  t3_lite(const t3_lite& xother);

  ///
  /// Assignment operator.
  ///
  t3_lite& operator=(const t3_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~t3_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  t3_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  t3_lite& operator=(const row_dofs_type& xrow_dofs);

protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS T3_LITE
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 3};  
  
  /// The degree of the tensor; 
  /// the sum of the contravariant and covariant degrees.
  ///
  virtual int p() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS T3_LITE
  //============================================================================
  //@{

public:

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

  using tp_lite::component;
  using tp_lite::put_component;

  ///
  /// The component with indices xi, xj, xk.
  ///
  virtual value_type component(int xi, int xj, int xk) const;

  ///
  /// Sets the component with indices xi, xj, xk to xvalue.
  ///
  virtual void put_component(int xi, int xj, int xk, value_type xvalue);

  ///
  /// The index into linear storage of the component
  /// for specified indices xi, xj, xk.
  ///
  virtual int index_for_ijk(int xi, int xj, int xk) const;


protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T3_LITE
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
  virtual t3_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T3_LITE
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
// CLASS T3
//==============================================================================

///
/// A tensor of degree 3 over an abstract vector space (persistent version).
///
class SHEAF_DLL_SPEC t3 : public tp
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS T2
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

protected:

private:

  //@}
 

  //============================================================================
  /// @name T3 FACET OF CLASS T3
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef t3_lite volatile_type;

  ///
  /// Default constructor.
  ///
  t3();

  ///
  /// Copy constructor.
  ///
  t3(const t3& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual t3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  t3& operator=(const t3& xother);

  ///
  /// Destructor.
  ///
  virtual ~t3();

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
  t3(poset* xhost, bool xauto_access = true);

  ///
  /// Creates a new handle attached to
  /// the member state with hub id xhub_id in xhost.
  ///
  t3(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new handle attached to
  /// the member state with id xid in xhost.
  ///
  t3(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  t3(const poset* xhost, const std::string& xname);

protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS T3
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 3};  
  
protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS T3
  //============================================================================
  //@{

public:

  using tp::component;
  using tp::put_component;

  ///
  /// The component with indices xi, xj, xk.
  ///
  virtual value_type component(int xi, int xj, int xk) const;

  ///
  /// The component with indices xi, xj, xk.
  ///
  value_type component(int xi, int xj, int xk, bool xauto_access) const;

  ///
  /// Sets the component with indices xi, xj, xk to xvalue.
  ///
  virtual void put_component(int xi, int xj, int xk, value_type xvalue);

  ///
  /// Sets the component with indices xi, xj, xk to xvalue.
  ///
  void put_component(int xi, int xj, int xk, value_type xvalue, bool xauto_access);

  ///
  /// The index into linear storage of the component
  /// for specified indices xi, xj, xk.
  ///
  virtual int index_for_ijk(int xi, int xj, int xk) const;

protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS T3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T3
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
  /// Make a new handle, no state instance of current.
  ///
  virtual t3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline t3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<t3*>(tp::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T3
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

class at1;
class at1_lite;
class at2;
class at2_lite;
class at3;
class at3_lite;

class st2;
class st2_lite;
class st3;
class st3_lite;

class t2;
class t2_lite;

//==============================================================================
// TP FACET
//==============================================================================

namespace tp_algebra
{

///
/// Contraction on contravariant index xp and covariant index xq
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void contract(const t3_lite& x0, int xp, int xq, at1_lite& xresult);

///
/// Contraction on contravariant index xp and covariant index xq
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void contract(const t3& x0, int xp, int xq, at1& xresult,
			     bool xauto_access);

//==============================================================================

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void alt(const t3_lite& x0, t3_lite& xresult);

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void alt(const t3_lite& x0, at3_lite& xresult);

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void alt(const t3& x0, at3& xresult, bool xauto_access);


//==============================================================================
///
/// The symmetric part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void sym(const t3_lite& x0, t3_lite& xresult);

///
/// The symmetric part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void sym(const t3_lite& x0, st3_lite& xresult);

///
/// The symmetric part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void sym(const t3& x0, st3& xresult, bool xauto_access);

//==============================================================================
///
/// Tensor product
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void tensor(const t2_lite& x0, const at1_lite& x1, t3_lite& xresult);

///
/// Tensor product
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void tensor(const t2& x0, const at1& x1, t3& xresult, bool xauto_access);

///
/// Tensor product
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void tensor(const at1_lite& x0, const t2_lite& x1, t3_lite& xresult);

///
/// Tensor product
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void tensor(const at1& x0, const t2& x1, t3& xresult, bool xauto_access);

//==============================================================================

///
/// Tensor product
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void tensor(const at2_lite& x0, const at1_lite& x1, t3_lite& xresult);

///
/// Tensor product
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void tensor(const at2& x0, const at1& x1, t3& xresult, bool xauto_access);

///
/// Tensor product
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void tensor(const at1_lite& x0, const at2_lite& x1, t3_lite& xresult);

///
/// Tensor product
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void tensor(const at1& x0, const at2& x1, t3& xresult, bool xauto_access);

//========================================================================

///
/// Tensor product
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void tensor(const st2_lite& x0, const at1_lite& x1, t3_lite& xresult);

///
/// Tensor product
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void tensor(const st2& x0, const at1& x1, t3& xresult, bool xauto_access);

///
/// Tensor product
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void tensor(const at1_lite& x0, const st2_lite& x1, t3_lite& xresult);

///
/// Tensor product
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void tensor(const at1& x0, const st2& x1, t3& xresult, bool xauto_access);

//==============================================================================

} // namespace tp_algebra


} // end namespace fiber_bundle


#endif // ifndef T3_H
