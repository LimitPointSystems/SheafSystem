

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Interface for class t4_e3.


#ifndef T4_E3_H
#define T4_E3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef T4_H
#include "t4.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS T4_E3_ROW_DOFS_TYPE
//==============================================================================

///
/// Row dofs type for class t4_e3.
///
template <typename T>
class t4_e3_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef t4_e3_row_dofs_type<T> row_dofs_type;

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
  /// Creates a new instance of the same type as this.
  ///
  t4_e3_row_dofs_type<T>* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  t4_e3_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

  ///
  /// The dofs are in the following order:
  ///
  ///   components[ 0] => xxxx
  ///   components[ 1] => xxxy
  ///   components[ 2] => xxxz
  ///   components[ 3] => xxyx
  ///   components[ 4] => xxyy
  ///   components[ 5] => xxyz
  ///   components[ 6] => xxzx
  ///   components[ 7] => xxzy
  ///   components[ 8] => xxzz
  ///
  ///   components[ 9] => xyxx
  ///   components[10] => xyxy
  ///   components[11] => xyxz
  ///   components[12] => xyyx
  ///   components[13] => xyyy
  ///   components[14] => xyyz
  ///   components[15] => xyzx
  ///   components[16] => xyzy
  ///   components[17] => xyzz
  ///
  ///   components[18] => xzxx
  ///   components[19] => xzxy
  ///   components[20] => xzxz
  ///   components[21] => xzyx
  ///   components[22] => xzyy
  ///   components[23] => xzyz
  ///   components[24] => xzzx
  ///   components[25] => xzzy
  ///   components[26] => xzzz

  ///   components[27] => yxxx
  ///   components[28] => yxxy
  ///   components[29] => yxxz
  ///   components[30] => yxyx
  ///   components[31] => yxyy
  ///   components[32] => yxyz
  ///   components[33] => yxzx
  ///   components[34] => yxzy
  ///   components[35] => yxzz
  ///
  ///   components[36] => yyxx
  ///   components[37] => yyxy
  ///   components[38] => yyxz
  ///   components[39] => yyyx
  ///   components[40] => yyyy
  ///   components[41] => yyyz
  ///   components[42] => yyzx
  ///   components[43] => yyzy
  ///   components[44] => yyzz
  
  ///   components[45] => yzxx
  ///   components[46] => yzxy
  ///   components[47] => yzxz
  ///   components[48] => yzyx
  ///   components[49] => yzyy
  ///   components[50] => yzyz
  ///   components[51] => yzzx
  ///   components[52] => yzzy
  ///   components[53] => yzzz

  ///   components[54] => zxxx
  ///   components[55] => zxxy
  ///   components[56] => zxxz
  ///   components[57] => zxyx
  ///   components[58] => zxyy
  ///   components[59] => zxyz
  ///   components[60] => zxzx
  ///   components[61] => zxzy
  ///   components[62] => zxzz
  ///
  ///   components[63] => zyxx
  ///   components[64] => zyxy
  ///   components[65] => zyxz
  ///   components[66] => zyyx
  ///   components[67] => zyyy
  ///   components[68] => zyyz
  ///   components[69] => zyzx
  ///   components[70] => zyzy
  ///   components[71] => zyzz
  ///
  ///   components[72] => zzxx
  ///   components[73] => zzxy
  ///   components[74] => zzxz
  ///   components[75] => zzyx
  ///   components[76] => zzyy
  ///   components[77] => zzyz
  ///   components[78] => zzzx
  ///   components[79] => zzzy
  ///   components[80] => zzzz
  ///
  ///
  T components[81];

protected:
private:

};

//==============================================================================
// CLASS T4_E3_LITE
//==============================================================================

class e3_lite;
class st4_e3_lite;

///
/// A tensor of degree 4 over a Euclidean vector space of dimension 3
/// (volatile version).
///
class SHEAF_DLL_SPEC t4_e3_lite : public t4_lite
{

  //============================================================================
  /// @name T4_E3 FACET OF CLASS T4_E3_LITE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the row dofs.
  ///
  typedef t4_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  t4_e3_lite();

  ///
  /// Copy constructor.
  ///
  t4_e3_lite(const t4_e3_lite& xother);

  ///
  /// Assignment operator.
  ///
  t4_e3_lite& operator=(const t4_e3_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~t4_e3_lite();

 ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  t4_e3_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from a row dofs type) operator.
  ///
  t4_e3_lite& operator=(const row_dofs_type& xrow_dofs);

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
  /// @name T4 FACET OF CLASS T4_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS T4_E3_LITE
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
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS T4_E3_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T4_E3_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T4_E3_LITE
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
  virtual t4_e3_lite* clone() const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this;
  /// synonym for clone(), intended for use only in certain templates.
  ///
  virtual t4_e3_lite* clone(bool xnew_state, bool xauto_access) const
  {
    return clone();
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T4_E3_LITE
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
// CLASS T4_E3
//==============================================================================

///
/// A tensor of degree 4 over a Euclidean vector space of dimension 3
/// (persistent version).
///
class SHEAF_DLL_SPEC t4_e3 : public t4
{

  //============================================================================
  /// @name T4_E3 FACET OF CLASS T4_E3
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  ///  The type of the row dofs.
  ///
  typedef t4_e3_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef t4_e3_lite volatile_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef e3 vector_space_type;

  ///
  /// Default constructor.
  ///
  t4_e3();

  ///
  /// Copy constructor.
  ///
  t4_e3(const t4_e3& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual t4_e3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  t4_e3& operator=(const t4_e3& xother);

  ///
  /// Destructor.
  ///
  virtual ~t4_e3();

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
  t4_e3(poset* xhost, bool xauto_access = true);

  ///@issue Why do we have "poset* xhost" instead of 
  ///       "poset_state_handle* xhost" above?

  ///
  /// New handle/new state constructor.
  ///
  t4_e3(poset_state_handle& xhost,
         const row_dofs_type& xrdt,
         bool xauto_access = true);

  ///
  /// Assignment to an instance of the associated row dofs type.
  ///
  t4_e3& operator=(const row_dofs_type& xrdt);

  ///
  /// Creates a new handle attached to
  /// the member state with hub id xhub_id in xhost.
  ///
  t4_e3(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new handle attached to
  /// the member state with id xid in xhost.
  ///
  t4_e3(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  t4_e3(const poset* xhost, const string& xname);

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
  /// @name T4 FACET OF CLASS T4_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS T4_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS T4_E3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS T4_E3
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T4_E3
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
  /// Make a new handle, no state instance of current.
  ///
  virtual t4_e3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline t4_e3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<t4_e3*>(t4::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T4_E3
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
/// Insert t4_e3_row_dofs_type@<T@>& xrdt into ostream& xos.
///
template <typename T>
ostream& operator<<(ostream& xos, const t4_e3_row_dofs_type<T>& xrdt);


class st4_e3;
class st4_e3_lite;

// No alt versions here because at4_e3 is 0. 

namespace tp_algebra
{

///
/// The symmetric part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void sym(const t4_e3_lite& x0, st4_e3_lite& xresult);

///
/// The symmetric part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void sym(const t4_e3& x0, st4_e3& xresult, bool xauto_access);

} // namespace tp_algebra

} // end namespace fiber_bundle


#endif // ifndef T4_E3_H
