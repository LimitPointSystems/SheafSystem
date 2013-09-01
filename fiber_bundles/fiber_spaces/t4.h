

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class t4.


#ifndef T4_H
#define T4_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TP_H
#include "tp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS T4_LITE
//==============================================================================

///
/// A tensor of degree 4 over an abstract vector space (volatile version).
///
class SHEAF_DLL_SPEC t4_lite : public tp_lite
{

  //============================================================================
  /// @name T4 FACET OF CLASS T4_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  t4_lite();

  ///
  /// Copy constructor.
  ///
  t4_lite(const t4_lite& xother);

  ///
  /// Assignment operator.
  ///
  t4_lite& operator=(const t4_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~t4_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  t4_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  t4_lite& operator=(const row_dofs_type& xrow_dofs);

protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS T4_LITE
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 4};  
  
  /// The degree of the tensor; 
  /// the sum of the contravariant and covariant degrees.
  ///
  virtual int p() const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS T4_LITE
  //============================================================================
  //@{

public:

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

  using tp_lite::component;
  using tp_lite::put_component;

  ///
  /// The component with indices xi, xj, xk, xl.
  ///
  virtual value_type component(int xi, int xj, int xk, int xl) const;

  ///
  /// Sets the component with indices xi, xj, xk, xl to xvalue.
  ///
  virtual void put_component(int xi, int xj, int xk, int xl,
                             value_type xvalue);

  ///
  /// The index into linear storage of the component
  /// for specified indices xi, xj, xk, xl.
  ///
  virtual int index_for_ijkl(int xi, int xj, int xk, int xl) const;


protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T4_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T4_LITE
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
  virtual t4_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T4_LITE
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

protected:
private:

  //@}
};

//==============================================================================
// CLASS T4
//==============================================================================

///
/// A tensor of degree 4 over an abstract vector space (persistent version).
///
class SHEAF_DLL_SPEC t4 : public tp
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS T4
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

protected:

private:

  //@}
 

  //============================================================================
  /// @name T4 FACET OF CLASS T4
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef t4_lite volatile_type;

  ///
  /// Default constructor.
  ///
  t4();

  ///
  /// Copy constructor.
  ///
  t4(const t4& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual t4& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  t4& operator=(const t4& xother);

  ///
  /// Destructor.
  ///
  virtual ~t4();

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
  t4(poset* xhost, bool xauto_access = true);

  ///
  /// Creates a new handle attached to
  /// the member state with hub id xhub_id in xhost.
  ///
  t4(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new handle attached to
  /// the member state with id xid in xhost.
  ///
  t4(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  t4(const poset* xhost, const string& xname);

protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS T4
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
  /// @name VD FACET OF CLASS T4
  //============================================================================
  //@{

public:

  using tp::component;
  using tp::put_component;

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
  void put_component(int xi, int xj, int xk, int xl, value_type xvalue, bool xauto_access);

  ///
  /// The index into linear storage of the component
  /// for specified indices xi, xj, xk, xl.
  ///
  virtual int index_for_ijkl(int xi, int xj, int xk, int xl) const;

protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS T4
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T4
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
  virtual t4* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline t4* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<t4*>(tp::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T4
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

} // namespace fiber_bundle

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================


#endif // ifndef T4_H
