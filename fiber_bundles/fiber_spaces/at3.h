
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
/// Interface for class at3.

#ifndef AT3_H
#define AT3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ATP_H
#include "atp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS AT3_LITE
//==============================================================================

///
/// An antisymmetric rank 3 tensor over an abstract vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC at3_lite : public atp_lite
{
  //===========================================================================
  /// @name AT3 FACET OF CLASS AT3_LITE
  //===========================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  at3_lite();

  ///
  /// Copy constructor.
  ///
  at3_lite(const at3_lite& xother);

  ///
  /// Assignment operator.
  ///
  at3_lite& operator=(const at3_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~at3_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  at3_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  at3_lite& operator=(const row_dofs_type& xrow_dofs);


  using atp_lite::component;
  using atp_lite::put_component;
  
  ///
  /// The value of component with indices xi, xj, xk.
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


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS AT3_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS AT3_LITE
  //===========================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 3};  

  ///
  /// Degree of this as an antisymmetric tensor space.
  ///
  virtual int p() const;

protected:
private:

  //@}


  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS AT3_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS AT3_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT3_LITE
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
  virtual at3_lite* clone() const;

protected:
private:

  //@}


  //===========================================================================
  /// @name ANY FACET OF CLASS AT3_LITE
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
// CLASS AT3
//==============================================================================

///
/// An antisymmetric rank 3 tensor over an abstract vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC at3 : public atp
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS AT1
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

protected:

private:

  //@}


  //============================================================================
  /// @name AT3 FACET OF CLASS AT3
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef at3_lite volatile_type;

  ///
  /// Default constructor.
  ///
  at3();

  ///
  /// Creates a new at3 handle attached to the member state with hub id
  /// xhub id in xhost.
  ///
  at3(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new at3 handle attached to the member state with id xid
  /// in xhost.
  ///
  at3(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new at3 handle attached to the member state with name xname
  /// in xhost.
  ///
  at3(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new at3 handle attached to the same state as xother.
  ///
  explicit at3(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  at3(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual at3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  at3& operator=(const at3& xother);

  ///
  /// Destructor.
  ///
  ~at3();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

  using atp::component;
  using atp::put_component;

  ///
  /// The value of component with indices xi, xj, xk.
  ///
  virtual value_type component(int xi, int xj, int xk) const;

  ///
  /// The value of component with indices xi, xj, xk.
  ///
  virtual value_type component(int xi, int xj, int xk, bool xauto_access) const;

  ///
  /// Sets the component with indices xi, xj, xk to xvalue.
  ///
  virtual void put_component(int xi, int xj, int xk, value_type xvalue);

  ///
  /// Sets the component with indices xi, xj, xk to xvalue.
  ///
  virtual void put_component(int xi, int xj, int xk, value_type xvalue,
                             bool xauto_access);

  ///
  /// The index into linear storage of the component
  /// for specified indices xi, xj, xk.
  ///
  virtual int index_for_ijk(int xi, int xj, int xk) const;

protected:
private:

  //@}


  //============================================================================
  /// @name ATP FACET OF CLASS AT3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS AT3
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
  /// @name VD FACET OF CLASS AT3
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS AT3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT3
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
  virtual at3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline at3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<at3*>(atp::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS AT3
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

#endif // ifndef AT3_H
