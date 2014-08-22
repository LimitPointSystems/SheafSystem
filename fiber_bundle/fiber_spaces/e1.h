
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
/// Interface for class e1.


#ifndef COM_LIMITPOINT_FIBER_BUNDLE_E1_H
#define COM_LIMITPOINT_FIBER_BUNDLE_E1_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_ED_H
#include "ComLimitPoint/fiber_bundle/ed.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS E1_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class e1.
///
template <typename T>
class e1_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef e1_row_dofs_type<T> row_dofs_type;

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
  e1_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  e1_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The components (row_dofs).
  ///
  T components[1];

protected:
private:

};


//==============================================================================
// CLASS E1_LITE
//==============================================================================

///
/// Euclidean vector space of dimension 1
/// (volatile version).
///
class SHEAF_DLL_SPEC e1_lite : public ed_lite
{
  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (E1) FACET OF CLASS E1_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef e1_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  e1_lite();

  ///
  /// Copy constructor.
  ///
  e1_lite(const e1_lite& xother);

  ///
  /// Assignment operator.
  ///
  e1_lite& operator=(const e1_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~e1_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  e1_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  e1_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with component x_comp.
  ///
  e1_lite(const value_type& x_comp);

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

  using ed_lite::component;
  using ed_lite::put_component;

  ///
  /// Set value of (the only) component to x_comp.
  ///
  virtual void put_component(value_type x_comp);

  ///
  /// Value of (the only) component.
  ///
  virtual value_type component() const;

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (AT1) FACET OF CLASS E1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS E1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS E1_LITE
  //============================================================================
  //@{

public:

  ///
  /// Dimension of the underlying vector space.
  ///
  virtual int dd() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS E1_LITE
  //============================================================================
  //@{

public:

  ///
  /// True if this has the same components as xother.
  ///
  bool operator==(const e1_lite& xother) const;

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

  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS E1_LITE
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
  virtual e1_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual e1_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS E1_LITE
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
// CLASS E1
//==============================================================================

class tp_space;
class tp;
class atp;
class stp;

///
/// Euclidean vector space of dimension 1 (persistent version).
///
class SHEAF_DLL_SPEC e1 : public ed
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS E1
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
  /// The host with path standard_host_path<e1>(xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (E1) FACET OF CLASS E1
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef e1_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef e1_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e1 vector_space_type;

  ///
  /// Default constructor.
  ///
  e1();

  ///
  /// Creates a new e1 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  e1(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new e1 handle attached to the member state with id xid
  /// in xhost.
  ///
  e1(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new e1 handle attached to the member state with name xname
  /// in xhost.
  ///
  e1(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new e1 handle attached to the same state as xother.
  ///
  explicit e1(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  e1(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  e1(poset_state_handle& xhost,
     const row_dofs_type& xrdt,
     bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  e1& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual e1& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  e1& operator=(const e1& xother);

  ///
  /// Destructor
  ///
  ~e1();

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
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E1
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (AT1) FACET OF CLASS E1
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS E1
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS E1
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS E1
  //===========================================================================
  //@{

public:

  using ed::component;  
  using ed::put_component;

  ///
  /// Get value of component xindex.
  ///
  virtual dof_type component() const;

  ///
  /// Set value of component.
  ///
  virtual void put_component(dof_type xcomp);

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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E1
  //===========================================================================
  //@{

public:

  //@todo: Reword comments.
  ///
  /// Static constructor for general tensors 
  /// of degree xp over this vector space.
  ///
  static tp* new_tp(tp_space& xvector_space, int xp);

  ///
  /// Static constructor for antisymmetric tensors 
  /// of degree xp over this vector space.
  ///
  static atp* new_atp(tp_space& xvector_space, int xp);

  ///
  /// Static constructor for symmetric tensors 
  /// of degree xp over this vector space.
  ///
  static stp* new_stp(tp_space& xvector_space, int xp);

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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS E1
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
  virtual e1* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline e1* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<e1*>(ed::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS E1
  //============================================================================
  //@{

public:

  ///
  /// True if other conforms to current.
  ///
  bool is_ancestor_of(const any* other) const;

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
/// Insert e1_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
std::ostream& operator<<(std::ostream& xos, const e1_row_dofs_type<T>& xrdt);


} // namespace fiber_bundle

#endif // ifndefCOM_LIMITPOINT_FIBER_BUNDLE_E1_H
