

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
/// Interface for class st4.

#ifndef ST4_H
#define ST4_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STP_H
#include "stp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS ST4_LITE
//==============================================================================

///
/// A symmetric rank 4 tensor over an abstract vector space.
/// (volatile version).
///
class SHEAF_DLL_SPEC st4_lite : public stp_lite
{
  //===========================================================================
  /// @name ST4 FACET OF CLASS ST4_LITE
  //===========================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  st4_lite();

  ///
  /// Copy constructor.
  ///
  st4_lite(const st4_lite& xother);

  ///
  /// Assignment operator.
  ///
  st4_lite& operator=(const st4_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~st4_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  st4_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  st4_lite& operator=(const row_dofs_type& xrow_dofs);


  using stp_lite::component;
  using stp_lite::put_component;
  
  ///
  /// The component with indices xi, xj, xk, xl.
  ///
  virtual value_type component(int xi, int xj, int xk, int xl) const;

  ///
  /// Sets the component with indices xi, xj, xk, xl to xvalue.
  ///
  virtual void put_component(int xi, int xj, int xk, int xl, value_type xvalue);

  ///
  /// The index into linear storage of the component
  /// for specified indices xi, xj, xk, xl.
  ///
  virtual int index_for_ijkl(int xi, int xj, int xk, int xl) const;


protected:
private:

  //@}


  //===========================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS ST4_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ST4_LITE
  //===========================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 4};  

  ///
  /// Degree of this as a symmetric tensor space.
  ///
  virtual int p() const;

protected:
private:

  //@}


  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ST4_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST4_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST4_LITE
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
  virtual st4_lite* clone() const;

protected:
private:

  //@}


  //===========================================================================
  /// @name ANY FACET OF CLASS ST4_LITE
  //===========================================================================
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
// CLASS ST4
//==============================================================================

///
/// A symmetric rank 4 tensor over an abstract vector space
/// (persistent version).
///
class SHEAF_DLL_SPEC st4 : public stp
{

  //============================================================================
  /// @name ST4 FACET OF CLASS ST4
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef st4_lite volatile_type;

  ///
  /// Default constructor.
  ///
  st4();

  ///
  /// Creates a new st4 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  st4(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new st4 handle attached to the member state with id xid
  /// in xhost.
  ///
  st4(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new st4 handle attached to the member state with name xname
  /// in xhost.
  ///
  st4(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new st4 handle attached to the same state as xother.
  ///
  explicit st4(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  st4(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual st4& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  st4& operator=(const st4& xother);

  ///
  /// Destructor.
  ///
  ~st4();

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
  /// @name STP FACET OF CLASS ST4
  //============================================================================
  //@{

public:
protected:
private:

  //@}



  //============================================================================
  /// @name TP FACET OF CLASS ST4
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 4};  

protected:
private:

  //@}



  //============================================================================
  /// @name VD FACET OF CLASS ST4
  //============================================================================
  //@{

public:

  using stp::component;
  using stp::put_component;

  ///
  /// The component with indices xi, xj, xk, xl.
  ///
  virtual value_type component(int xi, int xj, int xk, int xl) const;

  ///
  /// The component with indices xi, xj, xk, xl.
  ///
  value_type component(int xi, int xj, int xk, int xl, bool xauto_access) const;

  ///
  /// Sets the component with indices xi, xj, xk, xl to xvalue.
  ///
  virtual void put_component(int xi, int xj, int xk, int xl, value_type xvalue);

  ///
  /// Sets the component with indices xi, xj, xk, xl to xvalue.
  ///
  void put_component(int xi, int xj, int xk, int xl, value_type xvalue,
                     bool xauto_access);

  ///
  /// The index into linear storage of the component
  /// for specified indices xi, xj, xk, xl.
  ///
  virtual int index_for_ijkl(int xi, int xj, int xk, int xl) const;

protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS ST4
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST4
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
  virtual st4* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline st4* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<st4*>(stp::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ST4
  //============================================================================
  //@{

public:

  ///
  /// True if other conforms to current.
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

} // namespace fiber_bundle

#endif // ifndef ST4_H
