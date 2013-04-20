

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class t2.


#ifndef T2_H
#define T2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TP_H
#include "tp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS T2_LITE
//==============================================================================

///
/// A tensor of degree 2 over an abstract vector space (volatile version).
///
class SHEAF_DLL_SPEC t2_lite : public tp_lite
{

  //============================================================================
  /// @name T2 FACET OF CLASS T2_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  t2_lite();

  ///
  /// Copy constructor.
  ///
  t2_lite(const t2_lite& xother);

  ///
  /// Assignment operator.
  ///
  t2_lite& operator=(const t2_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~t2_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  t2_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  t2_lite& operator=(const row_dofs_type& xrow_dofs);


  using tp_lite:: component;
  using tp_lite:: put_component;
  
  ///
  /// The value of the component in a specified row and column.
  ///
  value_type component(int xrow, int xcolumn) const;

  ///
  /// Sets value of a component in a specified row and column.
  ///
  void put_component(int xrow, int xcolumn, value_type xcomp);

  ///
  /// The index into linear storage of the component
  /// in a specified row and column.
  ///
  virtual int index_for_row_column(int xrow, int xcolumn) const;


protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS T2_LITE
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 2};  
  
  ///
  /// The degree of the tensor; 
  /// the sum of the contravariant and covariant degrees.
  ///
  virtual int p() const;


protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS T2_LITE
  //============================================================================
  //@{

public:

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T2_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T2_LITE
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
  virtual t2_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T2_LITE
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
// CLASS T2
//==============================================================================

///
/// A tensor of degree 2 over an abstract vector space (persistent version).
///
class SHEAF_DLL_SPEC t2 : public tp
{

  //============================================================================
  /// @name T2 FACET OF CLASS T2
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 2};  

  ///
  /// The associated volatile type.
  ///
  typedef t2_lite volatile_type;

  ///
  /// Default constructor.
  ///
  t2();

  ///
  /// Copy constructor.
  ///
  t2(const t2& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual t2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  t2& operator=(const t2& xother);

  ///
  /// Destructor
  ///
  virtual ~t2();

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
  t2(poset* xhost, bool xauto_access = true);

  ///
  /// Creates a new handle attached to
  /// the member state with hub id xhub_id in xhost.
  ///
  t2(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new handle attached to
  /// the member state with id xid in xhost.
  ///
  t2(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  t2(const poset* xhost, const string& xname);

  ///
  /// The index into linear storage of the component
  /// in a specified row and column.
  ///
  virtual int index_for_row_column(int xrow, int xcolumn) const;


protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS T2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS T2
  //============================================================================
  //@{

public:

  using tp::component;
  using tp::put_component;

  ///
  /// The component with row index xrow and column index xcolumn.
  ///
  value_type component(int xrow, int xcolumn) const;

  ///
  /// The component with row index xrow and column index xcolumn.
  ///
  value_type component(int xrow, int xcolumn, bool xauto_access) const;

  ///
  /// Sets the component with row index xrow and column index xcolumn to xvalue.
  ///
  void put_component(int xrow, int xcolumn, value_type xvalue);

  ///
  /// Sets the component with row index xrow and column index xcolumn to xvalue.
  ///
  void put_component(int xrow, int xcolumn, value_type xvalue, bool xauto_access);

protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS T2
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
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS T2
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
  virtual t2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline t2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<t2*>(tp::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS T2
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

class at0;
class at0_lite;
class at1;
class at1_lite;
class at2;
class at2_lite;
class st2;
class st2_lite;

//==============================================================================
// TP FACET
//==============================================================================

namespace tp_algebra
{

///
/// Contraction on contravariant index xp and covariant index xq
/// (pre-allocated version for volatime types).
/// The arguments xp and xq are indices into the "variance type" bitset.
/// This implies that xp != xp (for t2 there only 2 choices xp=0, xq=1
/// and xp=1, xq=0).
///
SHEAF_DLL_SPEC void contract(const t2_lite& x0, int xp, int xq, at0_lite& xresult);

///
/// Contraction on contravariant index xp and covariant index xq
/// (pre-allocated, access control version for persistent types).
/// The arguments xp and xq are indices into the "variance type" bitset.
/// This implies that xp != xp (for t2 there only 2 choices xp=0, xq=1
/// and xp=1, xq=0). 
///
SHEAF_DLL_SPEC void contract(const t2& x0, int xp, int xq, at0& xresult,
			     bool xauto_access);

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void alt(const t2_lite& x0, at2_lite& xresult);

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void alt(const t2& x0, at2& xresult, bool xauto_access);

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void alt(const t2_lite& x0, t2_lite& xresult);

///
/// The symmetric part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void sym(const t2_lite& x0, st2_lite& xresult);

///
/// The symmetric part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void sym(const t2& x0, st2& xresult, bool xauto_access);

///
/// The symmetric part of tensor x0
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void sym(const t2_lite& x0, t2_lite& xresult);

///
/// The symmetric part of tensor x0
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void sym(const t2& x0, t2& xresult, bool xauto_access);

///
/// Tensor product
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void tensor(const at1_lite& x0, const at1_lite& x1, t2_lite& xresult);

///
/// Tensor product
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void tensor(const at1& x0, const at1& x1, t2& xresult, bool xauto_access);

} // namespace tp_algebra

} // namespace fiber_bundle

#endif // ifndef T2_H
