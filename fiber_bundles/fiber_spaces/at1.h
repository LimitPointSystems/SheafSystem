

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class at1.

#ifndef AT1_H
#define AT1_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ATP_H
#include "atp.h"
#endif

namespace fiber_bundle
{
  class at1_space;
  
//==============================================================================
// CLASS AT1_LITE
//==============================================================================

///
/// A general antisymmetric tensor of degree 1 over an abstract vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC at1_lite : public atp_lite
{
  //============================================================================
  /// @name AT1 FACET OF CLASS AT1_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  at1_lite();

  ///
  /// Copy constructor.
  ///
  at1_lite(const at1_lite& xother);

  ///
  /// Assignment operator.
  ///
  at1_lite& operator=(const at1_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~at1_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  at1_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  at1_lite& operator=(const row_dofs_type& xrow_dofs);


protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS AT1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS AT1_LITE
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 1};  
  
  ///
  /// Degree of this as an antisymmetric tensor space.
  ///
  virtual int p() const;


protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS AT1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS AT1_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT1_LITE
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
  virtual at1_lite* clone() const;

protected:
private:

  //@}

  //============================================================================
  /// @name ANY FACET OF CLASS AT1_LITE
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
// CLASS AT1
//==============================================================================

///
/// A general antisymmetric tensor of degree 1 over an abstract vector space
/// (persistent version).
///
class SHEAF_DLL_SPEC at1 : public atp
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS AT1
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef at1_space host_type;

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// Manual, shallow factory method; creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and table attribute scalar_space_path specified by xscalar_space_path.
  ///
  static host_type&  new_host(namespace_type& xns, 
			      const poset_path& xhost_path, 
			      const poset_path& xschema_path,
			      const poset_path& xscalar_space_path,
			      bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name AT1 FACET OF CLASS AT1
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The associated volatile type.
  ///
  typedef at1_lite volatile_type;

  ///
  /// Default constructor.
  ///
  at1();

  ///
  /// Creates a new at1 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  at1(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new at1 handle attached to the member state with id xid
  /// in xhost.
  ///
  at1(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new at1 handle attached to the member state with name xname
  /// in xhost.
  ///
  at1(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new at1 handle attached to the same state as xother.
  ///
  explicit at1(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  at1(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual at1& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  at1& operator=(const at1& xother);

  ///
  /// Destructor.
  ///
  virtual ~at1();

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
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS AT1
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS AT1
  //============================================================================
  //@{

public:

  ///
  /// The tensor degree (static version)
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {P = 1};  
  
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS AT1
  //============================================================================
  //@{

public:
protected:
private:

  //@}

  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS AT1
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
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline at1* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<at1*>(atp::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  // ===========================================================
  /// @name POSET_COMPONENT FACET
  // ===========================================================
  //@{

public:

  ///
  /// The poset this is a member of.
  ///
  host_type* host() const;

  ///
  /// True if other conforms to host.
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* other) const;

protected:

private:

  //@}

  //============================================================================
  /// @name ANY FACET OF CLASS AT1
  //============================================================================
  //@{

public:

  ///
  /// True if other conforms to current.
  ///
  bool is_ancestor_of(const any* xother) const;
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual at1* clone() const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;

protected:
private:

  //@}
};

} // namespace fiber_bundle

#endif // ifndef AT1_H
