
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
/// Interface for class jcb_e33

#ifndef JCB_E33_H
#define JCB_E33_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef JCB_ED_H
#include "jcb_ed.h"
#endif

#ifndef GENERAL_MATRIX_3X3_H
#include "general_matrix_3x3.h"
#endif

namespace fiber_bundle
{
  class e3;
  
//==============================================================================
// CLASS JCB_E33_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class jcb_e33.
///
template <typename T>
class jcb_e33_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef jcb_e33_row_dofs_type<T> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef general_matrix_3x3<T> matrix_type;

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
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (non const version). 
  ///
  operator typename jcb_e33_row_dofs_type<T>::matrix_type& ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const typename jcb_e33_row_dofs_type<T>::matrix_type& () const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  jcb_e33_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  jcb_e33_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The dofs in the following order:
  ///   components[0] => dx/du
  ///   components[1] => dx/dv
  ///   components[2] => dx/dw
  ///   components[3] => dy/du
  ///   components[4] => dy/dv
  ///   components[5] => dy/dw
  ///   components[6] => dz/du
  ///   components[7] => dz/dv
  ///   components[8] => dz/dw
  ///
  T components[9];

protected:
private:

};


//==============================================================================
// CLASS JCB_E33_LITE
//==============================================================================

///
/// Jacobian of a map from a 3 dimensional domain (u, v, w) to
/// a 3 dimensional Euclidean space (x, y, z)
/// (volatile version).
///
class SHEAF_DLL_SPEC jcb_e33_lite : public jcb_ed_lite
{
  //============================================================================
  /// @name JCB_E33 FACET OF CLASS JCB_E33_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef jcb_e33_row_dofs_type<double> row_dofs_type;

  ///
  /// The type of the associated matrix.
  ///
  typedef jcb_e33_row_dofs_type<double>::matrix_type matrix_type;

  ///
  /// Default constructor.
  ///
  jcb_e33_lite();

  ///
  /// Copy constructor.
  ///
  jcb_e33_lite(const jcb_e33_lite& xother);

  ///
  /// Assignment operator.
  ///
  jcb_e33_lite& operator=(const jcb_e33_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~jcb_e33_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  jcb_e33_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  jcb_e33_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Creates a new instance with matrix type xmatrix.
  ///
  jcb_e33_lite(const matrix_type& xmatrix);

  ///
  /// Assignment (from a matrix type) operator.
  ///
  jcb_e33_lite& operator=(const matrix_type& xmatrix);

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
  /// Creates a new instance with components
  /// dxdu, dxdv, dxdw, dydu, dydv, dydw, dzdu, dzdv, dzdw.
  ///
  jcb_e33_lite(const value_type& dxdu,
               const value_type& dxdv,
               const value_type& dxdw,
               const value_type& dydu,
               const value_type& dydv,
               const value_type& dydw,
               const value_type& dzdu,
               const value_type& dzdv,
               const value_type& dzdw);

  using jcb_ed_lite::put_components;
  
  ///
  /// Set values of the components to the given arguments.
  ///
  virtual void put_components(const value_type& dxdu,
                              const value_type& dxdv,
                              const value_type& dxdw,
                              const value_type& dydu,
                              const value_type& dydv,
                              const value_type& dydw,
                              const value_type& dzdu,
                              const value_type& dzdv,
                              const value_type& dzdw);

protected:

  ///
  /// Row_dofs_type.
  ///
  row_dofs_type _row_dofs;

private:

  //@}


  //============================================================================
  /// @name JCB_ED FACET OF CLASS JCB_E33_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name JACOBIAN (JCB) FACET OF CLASS JCB_E33_LITE
  //============================================================================
  //@{

public:

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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS JCB_E33_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS JCB_E33_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB_E33_LITE
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
  virtual jcb_e33_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual jcb_e33_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS JCB_E33_LITE
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
// CLASS JCB_E33
//==============================================================================

///@issue is there really anything Euclidean about this class?

///
/// Jacobian of a map from a 3 dimensional domain (u, v, w) to
/// a 3 dimensional Euclidean space (x, y, z).
///
class SHEAF_DLL_SPEC jcb_e33 : public jcb_ed
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS JCB
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
  /// and table attributes domain_path, range_path, and scalar_space_path specified by
  /// xdomain_path and xrange_path, respectively.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path,
			     const poset_path& xdomain_path,
			     const poset_path& xrange_path,
			     bool xauto_access);

  ///
  /// The host with path standard_host_path<jcb_e33>(xsuffix).
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name JCB_E33 FACET OF CLASS JCB_E33
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of domain vector space.
  ///
  typedef e3 domain_type;

  ///
  /// The type of range vector space.
  ///
  typedef e3 range_type;

  ///
  /// The type of the row dofs.
  ///
  typedef jcb_e33_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef jcb_e33_lite volatile_type;

  ///
  /// Default constructor.
  ///
  jcb_e33();

  ///
  /// Creates a new jcb_e33 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  jcb_e33(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new jcb_e33 handle attached to the member state with id
  /// xid in xhost.
  ///
  jcb_e33(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new jcb_e33 handle attached to the member state with name xname
  /// in xhost.
  ///
  jcb_e33(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new jcb_e33 handle attached to the same state as xother.
  ///
  explicit jcb_e33(abstract_poset_member* xother);

  ///
  /// Creates a new handle attached to a new jim
  /// (join-irreducible member) state in xhost.
  ///
  jcb_e33(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// New handle/new state constructor.
  ///
  jcb_e33(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  jcb_e33& operator=(const row_dofs_type& xrdt);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual jcb_e33& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  jcb_e33& operator=(const jcb_e33& xother);

  ///
  /// Destructor.
  ///
  ~jcb_e33();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

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
  /// @name JCB FACET OF CLASS JCB_E33
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS JCB_E33
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS JCB_E33
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB_E33
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
  virtual jcb_e33* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline jcb_e33* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<jcb_e33*>(jcb_ed::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}



  //============================================================================
  /// @name ANY FACET OF CLASS JCB_E33
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
/// Insert jcb_e33_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
SHEAF_DLL_SPEC
std::ostream& operator<<(std::ostream& xos, const jcb_e33_row_dofs_type<T>& xrdt);


class e3;
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
SHEAF_DLL_SPEC void push(const jcb_e33& xjcb,
			 const e3& xvector,
			 e3& xresult,
			 bool xauto_access);

///
/// Push vector forward (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void push(const jcb_e33_lite& xjcb,
			 const e3_lite& xvector,
			 e3_lite& xresult);

///
/// Push vector forward (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC e3_lite* push(const jcb_e33_lite& xjcb, const e3_lite& xvector);

#endif // ifndef DOXYGEN_SKIP_UNKNOWN

///
/// Pull covector back (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void pull(const jcb_e33& xjcb,
			 const e3& xcovector,
			 e3& xresult,
			 bool xauto_access);

///
/// Pull covector back (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void pull(const jcb_e33_lite& xjcb,
			 const e3_lite& xcovector,
			 e3_lite& xresult);

///
/// Pull covector back (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC e3_lite* pull(const jcb_e33_lite& xjcb, const e3_lite& xcovector);

} // namespace jcb_algebra

} // namespace fiber_bundle


#endif // ifndef JCB_E33_H
