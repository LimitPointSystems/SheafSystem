

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class tuple.

#ifndef TUPLE_H
#define TUPLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_LITE_H
#include "any_lite.h"
#endif

#ifndef ARG_LIST_H
#include "arg_list.h"
#endif

#ifndef ARRAY_POSET_DOF_MAP_H
#include "array_poset_dof_map.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef TOTAL_POSET_MEMBER_H
#include "total_poset_member.h"
#endif

#ifndef TUPLE_TABLE_DOFS_TYPE_H
#include "tuple_table_dofs_type.h"
#endif
 

// #ifndef POSET_H
// #include "poset.h"
// #endif

// #ifndef STD_VECTOR_H
// #include "std_vector.h"
// #endif

namespace sheaf
{
  class namespace_poset;
  class poset;
  class schema_descriptor;
  template <class T> class wsv_block;
}

namespace fiber_bundle
{

using namespace sheaf;
class tuple_space;

//==============================================================================
// CLASS TUPLE_LITE
//==============================================================================

///
/// A member of a Cartesian product space; a tuple of attributes
/// (volatile version).
///
class SHEAF_DLL_SPEC tuple_lite : public any_lite
{
  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS TUPLE_LITE
  //============================================================================
  //@{

public:

  ///
  /// The type of the table dofs.
  ///
  typedef tuple_table_dofs_type table_dofs_type;

  ///
  /// Default constructor.
  ///
  tuple_lite();

  ///
  /// Copy constructor.
  ///
  tuple_lite(const tuple_lite& xother);

  ///
  /// Assignment operator.
  ///
  tuple_lite& operator=(const tuple_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~tuple_lite();

  ///
  /// Number of factors (components) in tuple.
  ///
  virtual int factor_ct() const = 0;

protected:
private:

  //@}


  //============================================================================
  /// @name  ABSTRACT POSET MEMBER FACET OF CLASS TUPLE_LITE
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
  virtual tuple_lite* clone() const;

  ///
  /// The table dofs.
  ///
  table_dofs_type table_dofs() const;

protected:
private:

  //@}


  //============================================================================
  /// @name  ANY FACET OF CLASS TUPLE_LITE
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
// CLASS TUPLE
//==============================================================================

///
/// A member of a Cartesian product space; a tuple of attributes
/// (persistent version).
///
class SHEAF_DLL_SPEC tuple : public total_poset_member
{

  //============================================================================
  /// @name  CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS TUPLE
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of host poset.
  ///
  typedef tuple_space host_type;

  ///
  /// The type of the table dofs.
  ///
  typedef tuple_table_dofs_type table_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef tuple_lite volatile_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// Default constructor.
  ///
  tuple();

  // New handle/old state constructors.

  ///
  /// Creates a new tuple handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  tuple(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new tuple handle attached to the member state with id xid
  /// in xhost.
  ///
  tuple(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new tuple handle attached to the member state with name xname
  /// in xhost.
  ///
  tuple(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new tuple handle attached to the same state as xother.
  ///
  explicit tuple(const abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  tuple(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual tuple& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  tuple& operator=(const tuple& xother);

  ///
  /// Destructor.
  ///
  virtual ~tuple();

  ///
  /// Number of factors (components) in tuple.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {FACTOR_CT = 0};  

  ///
  /// Number of factors (components) in tuple.
  ///
  virtual int factor_ct() const;

  ///
  /// Number of factors (components) in tuple.
  ///
  int factor_ct(bool xauto_access) const;

  ///
  /// The map from client_ids to dof values for this poset member (mutable version)
  ///
  virtual array_poset_dof_map& dof_map(bool xrequire_write_access = false);

  ///
  /// The map from client_ids to dof values for this poset member (const mutable)
  ///
  virtual const array_poset_dof_map& dof_map(bool xrequire_write_access = false) const;

  ///
  /// True if xdof_map conforms to (is derived from) the type of
  /// dof map required by this handle.
  ///
  virtual bool dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const;

protected:
private:

  //@}


  //============================================================================
  /// @name  ABSTRACT POSET MEMBER FACET OF CLASS TUPLE
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
  inline tuple* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<tuple*>(total_poset_member::clone(xnew_state,
                               xauto_access));
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
  /// @name  ANY FACET OF CLASS TUPLE
  //============================================================================
  //@{

public:

  ///
  /// True if other conforms to current.
  ///
  bool is_ancestor_of(const any* other) const;
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual tuple* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
};

} // namespace fiber_bundle

#endif // ifndef TUPLE_H
