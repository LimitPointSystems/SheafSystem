

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class st3.

#ifndef ST3_H
#define ST3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STP_H
#include "stp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS ST3_LITE
//==============================================================================

///
/// A symmetric rank 3 tensor over an abstract vector space.
/// (volatile version).
///
class SHEAF_DLL_SPEC st3_lite : public stp_lite
{
  //===========================================================================
  /// @name ST3 FACET OF CLASS ST3_LITE
  //===========================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  st3_lite();

  ///
  /// Copy constructor.
  ///
  st3_lite(const st3_lite& xother);

  ///
  /// Assignment operator.
  ///
  st3_lite& operator=(const st3_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~st3_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  st3_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  st3_lite& operator=(const row_dofs_type& xrow_dofs);


  using stp_lite::component;
  using stp_lite::put_component;
  
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


  //===========================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS ST3_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ST3_LITE
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
  /// Degree of this as a symmetric tensor space.
  ///
  virtual int p() const;

protected:
private:

  //@}


  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ST3_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST3_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST3_LITE
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
  virtual st3_lite* clone() const;

protected:
private:

  //@}


  //===========================================================================
  /// @name ANY FACET OF CLASS ST3_LITE
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
// CLASS ST3
//==============================================================================

///
/// A symmetric rank 3 tensor over an abstract vector space
/// (persistent version).
///
class SHEAF_DLL_SPEC st3 : public stp
{

  //============================================================================
  /// @name ST3 FACET OF CLASS ST3
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef st3_lite volatile_type;

  ///
  /// Default constructor.
  ///
  st3();

  ///
  /// Creates a new st3 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  st3(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new st3 handle attached to the member state with id xid
  /// in xhost.
  ///
  st3(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new st3 handle attached to the member state with name xname
  /// in xhost.
  ///
  st3(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new st3 handle attached to the same state as xother.
  ///
  explicit st3(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  st3(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual st3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  st3& operator=(const st3& xother);

  ///
  /// Destructor.
  ///
  ~st3();

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
  /// @name STP FACET OF CLASS ST3
  //============================================================================
  //@{

public:
protected:
private:

  //@}



  //============================================================================
  /// @name TP FACET OF CLASS ST3
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
  /// @name VD FACET OF CLASS ST3
  //============================================================================
  //@{

public:

  using stp::component;
  using stp::put_component;

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
  void put_component(int xi, int xj, int xk, value_type xvalue,
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
  /// @name TUPLE FACET OF CLASS ST3
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ST3
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
  virtual st3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline st3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<st3*>(stp::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ST3
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

#endif // ifndef ST3_H