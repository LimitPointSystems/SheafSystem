
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
/// Interface for class t4_e2.


#ifndef COM_LIMITPOINT_FIBER_BUNDLE_T4_E2_H
#define COM_LIMITPOINT_FIBER_BUNDLE_T4_E2_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_T4_H
#include "ComLimitPoint/fiber_bundle/t4.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_E2_H
#include "ComLimitPoint/fiber_bundle/e2.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS T4_E2_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class t4_e2.
///
template <typename T>
class t4_e2_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef t4_e2_row_dofs_type<T> row_dofs_type;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
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
  t4_e2_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  t4_e2_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The dofs are in the following order:
  ///
  ///   components[ 0] => xxxx
  ///   components[ 1] => xxxy
  ///   components[ 2] => xxyx
  ///   components[ 3] => xxyy
  ///
  ///   components[ 4] => xyxx
  ///   components[ 5] => xyxy
  ///   components[ 6] => xyyx
  ///   components[ 7] => xyyy
  ///

  ///   components[ 8] => yxxx
  ///   components[ 9] => yxxy
  ///   components[10] => yxyx
  ///   components[11] => yxyy
  ///
  ///   components[12] => yyxx
  ///   components[13] => yyxy
  ///   components[14] => yyyx
  ///   components[15] => yyyy
  
  T components[16];

protected:
private:

};

//==============================================================================
// CLASS T4_E2_LITE
//==============================================================================

class e2_lite;
class st4_e2_lite;

///
/// A tensor of degree 4 over a Euclidean vector space of dimension 2
/// (volatile version).
///
class SHEAF_DLL_SPEC t4_e2_lite : public t4_lite
{

  //============================================================================
  /// @name T4_E2 FACET OF CLASS T4_E2_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef t4_e2_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  t4_e2_lite();

  ///
  /// Copy constructor.
  ///
  t4_e2_lite(const t4_e2_lite& xother);

  ///
  /// Assignment operator.
  ///
  t4_e2_lite& operator=(const t4_e2_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~t4_e2_lite();

  ///
  /// Copy constructor (from a symmetric type).
  ///
  t4_e2_lite(const st4_e2_lite& xother);

  ///
  /// Assignment (from a symmetric type) operator.
  ///
  t4_e2_lite& operator=(const st4_e2_lite& xother);

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  t4_e2_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  t4_e2_lite& operator=(const row_dofs_type& xrow_dofs);

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
  /// @name T4 FACET OF CLASS T4_E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS T4_E2_LITE
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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS T4_E2_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T4_E2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T4_E2_LITE
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
  virtual t4_e2_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual t4_e2_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T4_E2_LITE
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
// CLASS T4_E2
//==============================================================================

///
/// A tensor of degree 4 over a Euclidean vector space of dimension 2
/// (persistent version).
///
class SHEAF_DLL_SPEC t4_e2 : public t4
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS T4_E2
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
  /// The host with path standard_host_path<t4_e2>(xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name T4_E2 FACET OF CLASS T4_E2
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  ///  The type of the row dofs.
  ///
  typedef t4_e2_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef t4_e2_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e2 vector_space_type;

  ///
  /// Default constructor.
  ///
  t4_e2();

  ///
  /// Copy constructor.
  ///
  t4_e2(const t4_e2& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual t4_e2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  t4_e2& operator=(const t4_e2& xother);

  ///
  /// Destructor.
  ///
  virtual ~t4_e2();

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
  t4_e2(poset* xhost, bool xauto_access = true);

  ///@issue Why do we have "poset* xhost" instead of 
  ///       "poset_state_handle* xhost" above?

  ///
  /// New handle/new state constructor.
  ///
  t4_e2(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  t4_e2& operator=(const row_dofs_type& xrdt);

  ///
  /// Creates a new handle attached to
  /// the member state with hub id xhub_id in xhost.
  ///
  t4_e2(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new handle attached to
  /// the member state with id xid in xhost.
  ///
  t4_e2(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  t4_e2(const poset* xhost, const std::string& xname);

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
  /// @name T4 FACET OF CLASS T4_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS T4_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}



  //============================================================================
  /// @name VD FACET OF CLASS T4_E2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS T4_E2
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T4_E2
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
  virtual t4_e2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline t4_e2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<t4_e2*>(t4::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T4_E2
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

///
/// Insert t4_e2_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
std::ostream& operator<<(std::ostream& xos, const t4_e2_row_dofs_type<T>& xrdt);

class st4_e2;
class st4_e2_lite;

namespace tp_algebra
{

///
/// The symmetric part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void sym(const t4_e2_lite& x0, st4_e2_lite& xresult);

///
/// The symmetric part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void sym(const t4_e2& x0, st4_e2& xresult, bool xauto_access);

} // namespace tp_algebra

} // namespace fiber_bundle


#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_T4_E2_H
