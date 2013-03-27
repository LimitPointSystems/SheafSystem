
// $RCSfile: tuple_space.h,v $ $Revision: 1.11 $ $Date: 2013/03/13 00:58:45 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class tuple_space.

#ifndef TUPLE_SPACE_H
#define TUPLE_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

#ifndef TUPLE_TABLE_DOFS_TYPE_H
#include "tuple_table_dofs_type.h"
#endif
 

namespace sheaf
{
  class arg_list;
  class namespace_poset;
}

namespace fiber_bundle
{

  using namespace sheaf;  

  class tuple;
  
///
/// A Cartesian product space.
///
class SHEAF_DLL_SPEC tuple_space : public poset
{
  friend class fiber_bundles_namespace; // For initialize_prototypes.

  // ===========================================================
  /// @name TUPLE_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef tuple member_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();
  
  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef tuple_table_dofs_type table_dofs_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(int xfactor_ct);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

  ///
  /// The number of factors in this product.
  ///
  int factor_ct() const;

  ///
  /// The number of factors in this product; auto access signature.
  ///
  int factor_ct(bool xauto_access) const;
  

protected:

  ///
  /// Default constructor;
  /// creates a new tuple_space handle not attached to any state.
  ///
  tuple_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  tuple_space(const tuple_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~tuple_space();

  ///
  /// Covariant constructor
  ///
  tuple_space(tuple* xtop, tuple* xbottom);

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  tuple_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the tuple_space with
  /// index xindex in namespace xhost.
  ///
  tuple_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the tuple_space with
  /// index xindex in namespace xhost.
  ///
  tuple_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the tuple_space with
  /// name xname in namespace xhost.
  ///
  tuple_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the tuple_space associated
  /// with namespace member xmbr.
  ///
  tuple_space(const namespace_poset_member& xmbr, bool xauto_access);

private:

  //@}

  // ===========================================================
  /// @name POSET FACET
  // ===========================================================
  //@{

public:

protected:

  using poset::new_state;
 
  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  void new_state(namespace_poset& xhost,
                 const string& xname,
                 const arg_list& xargs,
                 const poset_path& xschema_path,
                 bool xauto_access);

  ///
  /// Initializes xarg to satisfy class invariants.
  ///
  virtual void initialize_arg_list(const namespace_poset& xns, 
				   const string& xname,
				   arg_list& xargs,
				   const poset_path& xschema_path,
				   bool xauto_access);

private:

  ///
  /// True if prototype for this class has been entered in factory.
  /// Intended to force creation of prototype at initialization.
  ///
  static bool _has_prototype;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}
 
  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  ///
  /// Assignment operator; attaches this to the same state as xother.
  /// @issue This is probably the wrong signature for operator=,
  /// see thread Misc/Language/covariance in C++/covariance and operator=
  /// in the discusion forum. But it is consistent with all the
  /// other derivatives of poset_state_handle and it will soon be refactored
  /// out of existence any way.
  ///
  tuple_space& operator=(const poset_state_handle& xother);

  //@}
 
  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual tuple_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // TUPLE_SPACE_H
