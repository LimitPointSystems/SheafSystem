

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class primitives_poset_schema

#ifndef PRIMITIVES_POSET_SCHEMA_H
#define PRIMITIVES_POSET_SCHEMA_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

#ifndef POSET_MEMBER_H
#include "poset_member.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

namespace sheaf
{

class namespace_poset;
class subposet;
  
///
/// The schema poset for the primitives.
///
class SHEAF_DLL_SPEC primitives_poset_schema : public poset_state_handle
{

  friend class namespace_poset;
  friend class primitives_poset;

  // ===========================================================
  /// @name PRIMITIVES_POSET_SCHEMA FACET
  // ===========================================================
  //@{

public:

  ///
  /// The standard name for an instance of this class.
  ///
  static const string& standard_name();

protected:

private:

  ///
  /// Creates an unattached handle
  ///
  primitives_poset_schema();

  ///
  /// Destructor
  ///
  ~primitives_poset_schema();

  ///
  /// Handle for subposet which identifies table dofs.
  ///
  subposet* _table_dof_subposet;

  ///
  /// Handle for subposet which idnetifies row dofs.
  ///
  subposet* _row_dof_subposet;

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
  /// True if xdof_map conforms to (i.e. is derived from) the type of
  /// row dof map required by this poset
  ///
  virtual bool row_dof_map_conforms(const poset_dof_map* xdof_map) const;

  ///
  /// Get read access to the state associated with this.
  ///
  virtual void get_read_access() const;

  ///
  /// Get read write access to the state associated with this.  If
  /// release_read_only_access is requested, read only access will be
  /// released then read_write_access will be requested, finally the
  /// same level of read_access as before will be requested.
  ///
  virtual void get_read_write_access(bool xrelease_read_only_access = false);

  ///
  /// Release access. If xall is true, release all levels of access.
  /// Otherwise, release one level of access.
  ///
  virtual void release_access(bool xall = false) const;

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;

protected:

  ///
  /// Initializes the predefined members of the poset.
  ///
  virtual void initialize_standard_members();

  ///
  /// Creates the subposets common to every poset (i.e._whole and _jims) plus
  /// those required of a schema poset (table_dofs and row_dofs)
  ///
  virtual void initialize_standard_subposets(const string& xname);

  ///
  /// Prepare this for use as a schema
  /// All members will be schematized; argument xall_members is ignored.
  /// It is present only for conformance with poset_state_handle::schematize.
  ///
  virtual void schematize(subposet* xtable_dof_subposet,
                          subposet* xrow_dof_subposet,
                          bool xall_members = true);

  ///
  /// Release all access to posets this depends on,
  /// then detach and delete the state.
  ///
  virtual void terminate_access();

private:

  using poset_state_handle::new_state;

  ///
  /// Creates a new primitives poset, not in any namespace.
  ///
  void new_state();

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Class invariant
  ///
  bool invariant() const;

protected:

private:

  ///
  /// Make a new instance of the same type as this
  ///
  virtual primitives_poset_schema* clone() const;

  //@}
};

} // namespace sheaf

#endif // ifndef PRIMITIVES_POSET_SCHEMA_H
