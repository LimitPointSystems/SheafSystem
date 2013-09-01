

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class stp.

#ifndef STP_H
#define STP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TP_H
#include "tp.h"
#endif

namespace fiber_bundle
{
  class stp_space;
  
//==============================================================================
// CLASS STP_LITE
//==============================================================================

///
/// A symmetric tensor of degree p over an abstract vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC stp_lite : public tp_lite
{
  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS STP_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  stp_lite();

  ///
  /// Copy constructor.
  ///
  stp_lite(const stp_lite& xother);

  ///
  /// Assignment operator.
  ///
  stp_lite& operator=(const stp_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~stp_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  stp_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  stp_lite& operator=(const row_dofs_type& xrow_dofs);

protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS STP_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS STP_LITE
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
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS STP_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS STP_LITE
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
  virtual stp_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS STP_LITE
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
// CLASS STP
//==============================================================================


///
/// A symmetric tensor of degree p over an abstract vector space.
///
class SHEAF_DLL_SPEC stp : public tp
{
  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef stp_space host_type;

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
			     int xp,
			     const poset_path& xvector_space_path,
			     bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS STP
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef stp_lite volatile_type;

  ///
  /// Default constructor.
  ///
  stp();

  ///
  /// Creates a new stp handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  stp(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new stp handle attached to the member state with id xid
  /// in xhost.
  ///
  stp(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new stp handle attached to the member state with name xname
  /// in xhost.
  ///
  stp(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new stp handle attached to the same state as xother.
  ///
  explicit stp(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  stp(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual stp& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  stp& operator=(const stp& xother);

  ///
  /// Destructor.
  ///
  ~stp();

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
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS STP
  //============================================================================
  //@{

public:
  
protected:

private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS STP
  //============================================================================
  //@{

public:
protected:
private:

  //@}

  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS STP
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
  inline stp* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<stp*>(tp::clone(xnew_state, xauto_access));
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
  /// @name ANY FACET OF CLASS STP
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to current.
  ///
  bool is_ancestor_of(const any* xother) const;
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual stp* clone() const;

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

//$$SCRIBBLE: Currently all symmetric_product functions are
//            "not_implemented()" because the only meaningful
//            results would be like Sym(st2 (X) st2) = st4.
//            But we have not yet implemented any st4 classes.

///
/// Namespace containing the symmetric tensor algrebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace stp_algebra
{

///
/// 
/// Symmetric product
/// (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void symmetric_product(const stp_lite& x0, const stp_lite& x1,
				      stp_lite& xresult);

///
/// 
/// Symmetric product
/// (pre-allocated, access control version for persistent types).
///
SHEAF_DLL_SPEC void symmetric_product(const stp& x0, const stp& x1, stp& xresult,
				      bool xauto_access);

///
/// The symmetric product of two general tensors
/// (auto-allocated version for volatile types).
///
template <typename T0, typename T1>
typename tensor_traits<T0::P + T1::P, typename T0::vector_space_type>::tp_type*
symmetric_product(const T0& x0, const T1& x1);

///
/// The symmetric product of two general tensors
/// (auto-allocated version for persistent types).
///
template <typename T0, typename T1>
typename tensor_traits<T0::P + T1::P, typename T0::vector_space_type>::tp_type*
symmetric_product(const T0& x0, const T1& x1, bool xauto_access);

} // namespace stp_algebra

} // namespace fiber_bundle

#endif // ifndef STP_H
