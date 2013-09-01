

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class ed.

#ifndef ED_H
#define ED_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef AT1_H
#include "at1.h"
#include "tp_space.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS ED_LITE
//==============================================================================

///
/// Euclidean vector space of dimension d 
/// (volatile version).
///
class SHEAF_DLL_SPEC ed_lite : public at1_lite
{
  //============================================================================
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS ED_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  ed_lite();

  ///
  /// Copy constructor.
  ///
  ed_lite(const ed_lite& xother);

  ///
  /// Assignment operator.
  ///
  ed_lite& operator=(const ed_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~ed_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  ed_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  ed_lite& operator=(const row_dofs_type& xrow_dofs);

protected:
private:
  
  //@}


  //============================================================================
  /// @name AT1 FACET OF CLASS ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ED_LITE
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
  virtual ed_lite* clone() const;

protected:
private:


  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ED_LITE
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
// CLASS ED
//==============================================================================

///
/// Euclidean vector space of dimension d
/// (peresistent version).
///
class SHEAF_DLL_SPEC ed : public at1
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS ED
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
  /// @name EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS ED
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef ed_lite volatile_type;

  ///
  /// Default constructor.
  ///
  ed();

  ///
  /// Creates a new ed handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  ed(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new ed handle attached to the member state with id xid
  /// in xhost.
  ///
  ed(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new ed handle attached to the member state with name xname
  /// in xhost.
  ///
  ed(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new ed handle attached to the same state as xother.
  ///
  explicit ed(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  ed(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual ed& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  ed& operator=(const ed& xother);

  ///
  /// Destructor.
  ///
  ~ed();

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


  //===========================================================================
  /// @name EXTERIOR ALGEBRA (ATP) FACET OF CLASS ED
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS ED
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS ED
  //===========================================================================
  //@{

public:
protected:
private:

  //@}


  //===========================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ED
  //===========================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS ED
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
  virtual ed* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline ed* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<ed*>(at1::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS ED
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

///
/// Namespace containing the Euclidean vector algebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace ed_algebra
{

///
/// The Euclidean "dot" product of x0 with x1
/// (version for persistent types).
///
SHEAF_DLL_SPEC vd_value_type dot(const ed& x0, const ed& x1, bool xauto_access);

///
/// The Euclidean length (magnitude) of x0
/// (version for persistent types).
///
SHEAF_DLL_SPEC vd_value_type length(const ed& x0, bool xauto_access);

///
/// Set the Euclidean length (magnitude) of x0 to xlength.
/// (version for persistent types).
///
SHEAF_DLL_SPEC void put_length(ed& x0, const vd_value_type& xlength, bool xauto_access);

///
/// Normalize x0 (convert to a unit vector)
/// (pre_allocated version for persistent types).
///
SHEAF_DLL_SPEC void normalize(const ed& x0, ed& xresult, bool xauto_access);

///
/// Normalize x0 (convert to a unit vector) in place (for persistent types).
///
template <typename T>
void normalize(T& x0, bool xauto_access);

///
/// The Euclidean "dot" product of x0 with x1
/// (version for volatile types).
///
SHEAF_DLL_SPEC vd_value_type dot(const ed_lite& x0, const ed_lite& x1);

///
/// The Euclidean length (magnitude) of x0
/// (version for volatile types).
///
SHEAF_DLL_SPEC vd_value_type length(const ed_lite& x0);

///
/// Set the Euclidean length (magnitude) of x0 to xlength.
/// (version for volatile types).
///
SHEAF_DLL_SPEC void put_length(ed_lite& x0, const vd_value_type& xlength);

///
/// Normalize x0 (convert to a unit vector)
/// (pre_allocated version for volatile types).
///
SHEAF_DLL_SPEC void normalize(const ed_lite& x0, ed_lite& xresult);

///
/// The Euclidean "dot" product of x0 with x1 (for volatile types).
///
template <typename T>
vd_value_type operator*(const T& x0, const T& x1);

///
/// Normalize x0 (convert to a unit vector) in place (for volatile types).
///
template <typename T>
void normalize(T& x0);
  
} // namespace ed_algebra
  
} // namespace fiber_bundle

#endif // ifndef ED_H
