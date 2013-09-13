
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
/// Interface for class at0.

#ifndef AT0_H
#define AT0_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ATP_H
#include "atp.h"
#endif

namespace fiber_bundle
{

  class at0_space;
  

//==============================================================================
// CLASS AT0_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class at0.
///
template <typename T>
class at0_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef at0_row_dofs_type<T> row_dofs_type;

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

  // The value of the row dof (non-const version).

  T& component();

  // The value of the row dof (const version).

  const T& component() const;

  // Set the value of the row dof.

  void put_component(const T& xcomp);

  ///
  /// Creates a new instance of the same type as this.
  ///
  at0_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  at0_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The components (row_dofs), only one in this case.
  ///
  T components[1];


protected:
private:

};

//==============================================================================
// CLASS AT0_LITE
//==============================================================================

///
/// Antisymetric tensor of degree 0
/// (volatile version).
///
class SHEAF_DLL_SPEC at0_lite : public atp_lite
{
  //===========================================================================
  /// @name AT0 FACET OF CLASS AT0_LITE
  //===========================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef at0_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  at0_lite();

  ///
  /// Copy constructor.
  ///
  at0_lite(const at0_lite& xother);

  ///
  /// Assignment operator.
  ///
  at0_lite& operator=(const at0_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~at0_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  at0_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  at0_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with value xcomp.
  ///
  at0_lite(const value_type& xcomp);

  ///
  /// Assignment operator.
  ///
  at0_lite& operator=(const value_type& xcomp);

  ///
  /// Equality operator.
  ///
  bool operator==(const vd_value_type& xother) const;
  
  ///
  /// Conversion (cast) operator to convert to the associated value type
  /// (non const version). 
  ///
  operator value_type ();

  ///
  /// Conversion (cast) operator to convert to the associated value type
  /// (non const version). 
  ///
  operator value_type () const;

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

  using atp_lite::component;
  using atp_lite::put_component;

  ///
  /// Set value of (the only) component to xcomp.
  ///
  virtual void put_component(value_type xcomp);

  ///
  /// Value of (the only) component.
  ///
  value_type component() const;

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS AT0_LITE
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 0};  

  ///
  /// Degree of this as an antisymmetric tensor space.
  ///
  virtual int p() const;

protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS AT0_LITE
  //============================================================================
  //@{

public:

  ///
  /// Degree of this as an antisymmetric tensor space.
  ///
  virtual int dd() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS AT0_LITE
  //============================================================================
  //@{

public:

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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS AT0_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT0_LITE
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
  virtual at0_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual at0_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS AT0_LITE
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
// CLASS AT0
//==============================================================================

class tp_space;

///
/// A scalar viewed as an antisymmetric tensor of degree 0.
/// As the degree is 0 there is nothing to be symmetric or antisymmetric with
/// respect to.  Thus, this could have equivalently been the symmetric tensor
/// with degree=0.  The convention is to choose antisymmetric.
///
class SHEAF_DLL_SPEC at0 : public atp
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS AT0
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef at0_space host_type;

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
  /// The poset is created in namespace xns with path xhost_path and
  /// schema specified by xschema_path.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path,
			     bool xauto_access);

  ///
  /// The host with path standard_host_path(xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name AT0 FACET OF CLASS AT0
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef at0_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef at0_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef at0 vector_space_type;

  ///
  /// Default constructor.
  ///
  at0();

  ///
  /// Creates a new at0 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  at0(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new at0 handle attached to the member state with id xid
  /// in xhost.
  ///
  at0(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new at0 handle attached to the member state with name xname
  /// in xhost.
  ///
  at0(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new at0 handle attached to the same state as xother.
  ///
  explicit at0(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  at0(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  at0(poset_state_handle& xhost,
      const row_dofs_type& xrdt,
      bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  at0& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual at0& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  at0& operator=(const at0& xother);

  ///
  /// Destructor
  ///
  ~at0();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

  ///
  /// The value of this as a POD ("plain old data") type.
  ///
  virtual value_type value() const;

  ///
  /// Sets value to xvalue.
  ///
  void put_value(value_type xvalue);

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
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS AT0
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS AT0
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS AT0
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS AT0
  //============================================================================
  //@{

public:

  using atp::factor_ct;
  
  ///
  ///  Number of factors (components) in tuple.
  ///
  virtual int factor_ct() const;
 

protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT0
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
  inline at0* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<at0*>(atp::clone(xnew_state, xauto_access));
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
  /// @name ANY FACET OF CLASS AT0
  //============================================================================
  //@{

public:

  ///
  /// True if other conforms to current.
  ///
  bool is_ancestor_of(const any* xother) const;
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual at0* clone() const;

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
/// Insert at0_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const at0_row_dofs_type<T>& xrdt);

} // namespace fiber_bundle

#endif // ifndef AT0_H
