
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
/// Interface for class st3_e3

#ifndef ST3_E3_H
#define ST3_E3_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ST3_H
#include "SheafSystem/st3.h"
#endif

#ifndef E3_H
#include "SheafSystem/e3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS ST3_E3_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class st3_e3.
///
template <typename T>
class SHEAF_DLL_SPEC st3_e3_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef st3_e3_row_dofs_type<T> row_dofs_type;

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
  st3_e3_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  st3_e3_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The components.
  ///
  T components[10];

protected:
private:

};


//==============================================================================
// CLASS ST3_E3_LITE
//==============================================================================

class e3_lite;

///
/// A symmetric rank 3 tensor over a Euclidean vector space of dimension 3.
/// (volatile version).
///
class SHEAF_DLL_SPEC st3_e3_lite : public st3_lite
{
  //============================================================================
  /// @name ST3_E3 FACET OF CLASS ST3_E3_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef st3_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  st3_e3_lite();

  ///
  /// Copy constructor.
  ///
  st3_e3_lite(const st3_e3_lite& xother);

  ///
  /// Assignment operator.
  ///
  st3_e3_lite& operator=(const st3_e3_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~st3_e3_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  st3_e3_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  st3_e3_lite& operator=(const row_dofs_type& xrow_dofs);

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

//   ///
//   /// Creates a new instance with component xcomp.
//   ///
//   st3_e3_lite(const value_type& xcomp);


//   using st3_lite::put_components;

//   ///
//   /// Set the value of the component to xcomp.
//   ///
//   virtual void put_components(const value_type& xcomp);

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (ST3) FACET OF CLASS ST3_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS ST3_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ST3_E3_LITE
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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ST3_E3_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST3_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST3_E3_LITE
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
  virtual st3_e3_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual st3_e3_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ST3_E3_LITE
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
// CLASS ST3_E3
//==============================================================================

///
/// A symmetric rank 3 tensor over a 3D Euclidean vector space
/// (persistent version).
///
class SHEAF_DLL_SPEC st3_e3 : public st3
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS ST3_E3
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
  /// The host with path standard_host_path<st3_e3>(xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name ST3_E3 FACET OF CLASS ST3_E3
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef st3_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef st3_e3_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e3 vector_space_type;

  ///
  /// Default constructor.
  ///
  st3_e3();

  ///
  /// Creates a new st3_e3 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  st3_e3(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new st3_e3 handle attached to the member state with id xid
  /// in xhost.
  ///
  st3_e3(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new st3_e3 handle attached to the member state with name xname
  /// in xhost.
  ///
  st3_e3(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new st3_e3 handle attached to the same state as xother.
  ///
  explicit st3_e3(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  st3_e3(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  st3_e3(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  st3_e3& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual st3_e3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  st3_e3& operator=(const st3_e3& xother);

  ///
  /// Destructor.
  ///
  ~st3_e3();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;


  //============================================================================
  // Row dof tuple related member functions
  //============================================================================

  using st3::put_components;
  
  ///
  /// Sets the value of the component to xcomp.
  ///
  virtual void put_components(dof_type xcomp);

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
  /// @name ST3 FACET OF CLASS ST3_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS ST3_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS ST3_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS ST3_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS ST3_E3
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST3_E3
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
  virtual st3_e3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline st3_e3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<st3_e3*>(st3::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ST3_E3
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to current.
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
/// Insert st3_e3_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
SHEAF_DLL_SPEC
std::ostream& operator<<(std::ostream& xos, const st3_e3_row_dofs_type<T>& xrdt);


} // namespace fiber_bundle

#endif // ifndef ST3_E3_H
