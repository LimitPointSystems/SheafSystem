

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class at2.

#ifndef AT2_H
#define AT2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ATP_H
#include "atp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS AT2_LITE
//==============================================================================

///
/// A general antisymmetric tensor of degree 2 over an abstract vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC at2_lite : public atp_lite
{
  //===========================================================================
  /// @name AT2 FACET OF CLASS AT2_LITE
  //===========================================================================
  //@{

public:

  ///
  /// The type of component in the fiber;
  /// the scalar type in the fiber vector space.
  ///
  typedef vd_value_type value_type;

  ///
  /// Default constructor.
  ///
  at2_lite();

  ///
  /// Copy constructor.
  ///
  at2_lite(const at2_lite& xother);

  ///
  /// Assignment operator.
  ///
  at2_lite& operator=(const at2_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~at2_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  at2_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  at2_lite& operator=(const row_dofs_type& xrow_dofs);


  using atp_lite::component;
  using atp_lite::put_component;
  
  ///
  /// The value of the component in a specified row and column.
  ///
  virtual value_type component(int xrow, int xcolumn) const;

  ///
  /// Sets value of a component in a specified row and column.
  ///
  virtual void put_component(int xrow, int xcolumn, value_type xcomp);

  ///
  /// The index into linear storage of the component
  /// in a specified row and column.
  ///
  virtual int index_for_row_column(int xrow, int xcolumn) const;

protected:
private:

  //@}


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS AT2_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS AT2_LITE
  //===========================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 2};  
  
  ///
  /// Degree of this as an antisymmetric tensor space.
  ///
  virtual int p() const;

protected:
private:

  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS AT2_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS AT2_LITE
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT2_LITE
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
  virtual at2_lite* clone() const;

protected:
private:

  //@}


  //===========================================================================
  /// @name ANY FACET OF CLASS AT2_LITE
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
// CLASS AT2
//==============================================================================

class tp_space;

///
/// A general antisymmetric tensor of degree 2 over an abstract vector space.
///
class SHEAF_DLL_SPEC at2 : public atp
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS AT2
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
  /// @name AT2 FACET OF CLASS AT2
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef at2_lite volatile_type;

  ///
  /// Default constructor.
  ///
  at2();

  ///
  /// Creates a new at2 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  at2(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new at2 handle attached to the member state with id xid
  /// in xhost.
  ///
  at2(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new at2 handle attached to the member state with name xname
  /// in xhost.
  ///
  at2(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new at2 handle attached to the same state as xother.
  ///
  explicit at2(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  at2(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual at2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  at2& operator=(const at2& xother);

  ///
  /// Destructor.
  ///
  ~at2();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

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
  void put_component(int xrow, int xcolumn, value_type xvalue,
                      bool xauto_access);

  ///
  /// The index into linear storage of the component
  /// in a specified row and column.
  ///
  virtual int index_for_row_column(int xrow, int xcolumn) const;

//   ///
//   /// The index into linear storage of the component
//   /// with specified xi and xj.
//   ///
//   virtual int index_for_ij(int xi, int xj) const;


protected:
private:

  //@}


  //============================================================================
  /// @name ATP FACET OF CLASS AT2
  //============================================================================
  //@{

public:
protected:
private:


  //@}


  //============================================================================
  /// @name TP FACET OF CLASS AT2
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 2};  
  
protected:
private:


  //@}


  //============================================================================
  /// @name VD FACET OF CLASS AT2
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS AT2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT2
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
  virtual at2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline at2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<at2*>(atp::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS AT2
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

} // namespace fiber_bundle

#endif // ifndef AT2_H


