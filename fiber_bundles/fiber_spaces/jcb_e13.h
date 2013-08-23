
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
/// Interface for class jcb_e13

#ifndef JCB_E13_H
#define JCB_E13_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef JCB_ED_H
#include "jcb_ed.h"
#endif

#ifndef GENERAL_MATRIX_3X1_H
#include "general_matrix_3x1.h"
#endif

#ifndef E1_H
#include "e1.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif

namespace fiber_bundle
{
  class e1;
  class e3;
  
//==============================================================================
// CLASS JCB_E13_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class jcb_e13.
///
template <typename T>
class jcb_e13_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef jcb_e13_row_dofs_type<T> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef general_matrix_3x1<T> matrix_type;

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
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (non const version). 
  ///
  operator typename jcb_e13_row_dofs_type<T>::matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const typename jcb_e13_row_dofs_type<T>::matrix_type& () const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  jcb_e13_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  jcb_e13_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The dofs in the following order:
  ///   components[0] => dx/du
  ///   components[1] => dy/du
  ///   components[2] => dz/du
  ///
  T components[3];

protected:
private:

};


//==============================================================================
// CLASS JCB_E13_LITE
//==============================================================================

///
/// Jacobian of a map from a 1 dimensional domain (u) to
/// a 3 dimensional Euclidean space (x, y, z)
/// (volatile version).
///
class SHEAF_DLL_SPEC jcb_e13_lite : public jcb_ed_lite
{
  //============================================================================
  /// @name JCB_E13 FACET OF CLASS JCB_E13_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef jcb_e13_row_dofs_type<double> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef jcb_e13_row_dofs_type<double>::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  jcb_e13_lite();

  ///
  /// Copy constructor.
  ///
  jcb_e13_lite(const jcb_e13_lite& xother);

  ///
  /// Assignment operator.
  ///
  jcb_e13_lite& operator=(const jcb_e13_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~jcb_e13_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  jcb_e13_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  jcb_e13_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with matrix type xmatrix.
  ///
  jcb_e13_lite(const matrix_type& xmatrix);

  ///
  /// Assignment (from a matrix type) operator.
  ///
  jcb_e13_lite& operator=(const matrix_type& xmatrix);

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (non const version). 
  ///
  operator matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const matrix_type& () const;

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

  ///
  /// Creates a new instance with components dxdu, dydu, dzdu.
  ///
  jcb_e13_lite(const value_type& dxdu,
               const value_type& dydu,
               const value_type& dzdu);

  using jcb_ed_lite::put_components;
  
  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(const value_type& dxdu,
                              const value_type& dydu,
                              const value_type& dzdu);

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name JCB_ED FACET OF CLASS JCB_E13_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name JACOBIAN (JCB) FACET OF CLASS JCB_E13_LITE
  //============================================================================
  //@{

public:

  ///
  /// Type of underlying domain vector space.
  ///
  typedef e1_lite domain_space_type;

  ///
  /// Type of underlying range vector space.
  ///
  typedef e3_lite range_space_type;

  ///
  /// Dimension of the domain.
  ///
  virtual int dd() const;

  ///
  ///  Dimension of the range.
  ///
  virtual int dr() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS JCB_E13_LITE
  //============================================================================
  //@{

public:

//   ///
//   /// Virtual constructor for general tensors 
//   /// of degree xp over this vector space.
//   ///
//   virtual tp_lite* new_tp_lite(int xp) const;

//   ///
//   /// Virtual constructor for antisymmetric tensors 
//   /// of degree xp over this vector space.
//   ///
//   virtual atp_lite* new_atp_lite(int xp) const;

//   ///
//   /// Virtual constructor for symmetric tensors 
//   /// of degree xp over this vector space.
//   ///
//   virtual stp_lite* new_stp_lite(int xp) const;

//   virtual const tp_lite& tp_prototype(int xp) const;
//   virtual const atp_lite& atp_prototype(int xp) const;
//   virtual const stp_lite& stp_prototype(int xp) const;

protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS JCB_E13_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB_E13_LITE
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
  virtual jcb_e13_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual jcb_e13_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS JCB_E13_LITE
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
// CLASS JCB_E13
//==============================================================================

///@issue Is there really anything Euclidean about this class?

///
/// Jacobian of a map from a 1 dimensional domain (u) to
/// a 3 dimensional Euclidean space (x, y, z).
///
class SHEAF_DLL_SPEC jcb_e13 : public jcb_ed
{
  //============================================================================
  /// @name JCB_E13 FACET OF CLASS JCB_E13
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of domain vector space.
  ///
  typedef e1 domain_type;

  ///
  /// The type of range vector space.
  ///
  typedef e3 range_type;

  ///
  /// The type of the row dofs.
  ///
  typedef jcb_e13_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef jcb_e13_lite volatile_type;

  ///
  /// Default constructor.
  ///
  jcb_e13();

  ///
  /// Creates a new jcb_e13 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  jcb_e13(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new jcb_e13 handle attached to the member state with id
  /// xid in xhost.
  ///
  jcb_e13(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new jcb_e13 handle attached to the member state with name xname
  /// in xhost.
  ///
  jcb_e13(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new jcb_e13 handle attached to the same state as xother.
  ///
  explicit jcb_e13(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  jcb_e13(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  jcb_e13(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  jcb_e13& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual jcb_e13& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  jcb_e13& operator=(const jcb_e13& xother);

  ///
  /// Destructor.
  ///
  ~jcb_e13();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

  //============================================================================
  // ROW DOF RELATED MEMBER FUNCTIONS
  //============================================================================

  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(dof_type dxdu_comp,
                              dof_type dydu_comp,
                              dof_type dzdu_comp);

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
  /// @name JCB_ED FACET OF CLASS JCB_E13
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name JCB FACET OF CLASS JCB_E13
  //============================================================================
  //@{

public:
  ///
  /// Type of underlying domain vector space.
  ///
  typedef e1 domain_space_type;

  ///
  /// Type of underlying range vector space.
  ///
  typedef e3 range_space_type;

protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS JCB_E13
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS JCB_E13
  //============================================================================
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

protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB_E13
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
  /// Make a new handle, no state instance of current
  ///
  virtual jcb_e13* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline jcb_e13* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<jcb_e13*>(jcb_ed::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS JCB_E13
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
/// Insert jcb_e13_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const jcb_e13_row_dofs_type<T>& xrdt);


class e1;
class e3;
class e1_lite;
class e3_lite;

//==============================================================================
// JCB FACET
//==============================================================================

namespace jcb_algebra
{

#ifndef DOXYGEN_SKIP_UNKNOWN

///
/// Push vector forward (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void push(const jcb_e13& xjcb,
			 const e1& xvector,
			 e3& xresult,
			 bool xauto_access);

///
/// Push vector forward (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void push(const jcb_e13_lite& xjcb,
			 const e1_lite& xvector,
			 e3_lite& xresult);

///
/// Push vector forward (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC e3_lite* push(const jcb_e13_lite& xjcb,
			     const e1_lite& xvector);

#endif // ifndef DOXYGEN_SKIP_UNKNOWN

///
/// Pull covector back (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void pull(const jcb_e13& xjcb,
			 const e3& xcovector,
			 e1& xresult,
			 bool xauto_access);

///
/// Pull covector back (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void pull(const jcb_e13_lite& xjcb,
			 const e3_lite& xcovector,
			 e1_lite& xresult);

///
/// Pull covector back (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC e1_lite* pull(const jcb_e13_lite& xjcb,
			     const e3_lite& xcovector);

} // namespace jcb_algebra

} // namespace fiber_bundle


#endif // ifndef JCB_E13_H
