


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_tuple_space.

#ifndef SEC_TUPLE_SPACE_H
#define SEC_TUPLE_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_REP_SPACE_H
#include "sec_rep_space.h"
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

class sec_tuple;
class tuple;
class fiber_bundles_namespace;
  

///
/// A Cartesian product section space.
///
class SHEAF_DLL_SPEC sec_tuple_space : public sec_rep_space
{
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name SEC_TUPLE_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of namespace for this type of member.
  ///
  typedef fiber_bundles_namespace namespace_type;

  ///
  /// The type of member associated with this space.
  ///
  typedef sec_tuple member_type;

  ///
  /// The fiber type.
  ///
  typedef tuple fiber_type;

  ///
  /// The scalar type definition.
  ///
  typedef sec_tuple scalar_type;

  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef tuple_table_dofs_type table_dofs_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(int xfactor_ct);

  ///
  /// Creates a new sec_tuple_space in namespace xns with path xpath
  /// and schema specified by xschema_path.
  ///
  static void new_table(namespace_type& xhost, 
                        const poset_path& xpath, 
                        const poset_path& xschema_path,
                        bool xauto_access);
  
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
  /// creates a new sec_tuple_space handle not attached to any state.
  ///
  sec_tuple_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  sec_tuple_space(const sec_tuple_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~sec_tuple_space();

  ///
  /// Covariant constructor
  ///
  sec_tuple_space(sec_tuple* xtop, sec_tuple* xbottom);

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  sec_tuple_space(namespace_poset& xhost,
		  const string& xname,
		  const arg_list& xargs,
		  const poset_path& xschema_path,
		  bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the sec_tuple_space with
  /// index xindex in namespace xhost.
  ///
  sec_tuple_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_tuple_space with
  /// index xindex in namespace xhost.
  ///
  sec_tuple_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_tuple_space with
  /// name xname in namespace xhost.
  ///
  sec_tuple_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_tuple_space associated
  /// with namespace member xmbr.
  ///
  sec_tuple_space(const namespace_poset_member& xmbr, bool xauto_access);

private:

  //@}


  // ===========================================================
  /// @name SEC_REP_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

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
  sec_tuple_space& operator=(const poset_state_handle& xother);

protected:

private:

  //@}

 
  // ===========================================================
  /// @name READ_WRITE_MONITOR_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

private:

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
  virtual sec_tuple_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
 
};


} // namespace fiber_bundle


#endif // SEC_TUPLE_SPACE_H
