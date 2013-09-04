

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class poset.

#ifndef POSET_H
#define POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

namespace sheaf
{

class namespace_poset; 

///
/// A client handle for a mutable partially ordered set.
///
class SHEAF_DLL_SPEC poset : public poset_state_handle
{

  friend class abstract_poset_member;
  friend class namespace_poset;
  friend class poset_component;
  friend class poset_orderer;
  friend class poset_traverser;
  friend class storage_agent;

  // ===========================================================
  /// @name POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of namespace for this type of member.
  ///
  typedef namespace_poset namespace_type;

  ///
  /// Creates a new poset in namespace xns with path xpath
  /// and schema specified by xschema_path.
  ///
  static poset& new_table(namespace_type& xhost, 
                          const poset_path& xpath, 
                          const poset_path& xschema_path,
                          bool xauto_access);

protected:

  ///
  /// Default constructor; creates a new poset handle not attached to any state.
  ///
  poset();

  ///
  /// Destructor
  ///
  virtual ~poset();

  ///
  /// Covariant constructor
  ///
  poset(abstract_poset_member* xtop, abstract_poset_member* xbottom);

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  poset(const poset& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  poset& operator=(const poset_state_handle& xother);

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by name xname, xschema_path, and
  /// table dofs not initialized.
  ///
  void new_state(namespace_poset& xhost,
                 const string& xname,
                 const poset_path& xschema_path,
                 bool xauto_access);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs not initialized.
  ///
  void new_state(namespace_poset* xhost,
                 const poset_path& xschema_path,
                 const string& xname,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xtable_dofs.
  ///
  void new_state(namespace_poset* xhost,
                 const poset_path& xschema_path,
                 const string& xname,
                 void* xtable_dofs,
                 size_t xtable_dofs_ub,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state with schema given by
  /// the member specified by path xschema_path in namespace xhost,
  /// and with name xname, and table dofs xdof_tuple.
  ///
  ///
  void new_state(namespace_poset* xhost,
                 const poset_path& xschema_path,
                 const string& xname,
                 array_poset_dof_map* xdof_tuple,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema xschema,  name xname, and uninitialized table dofs.
  ///
  void new_state(namespace_poset* xhost,
                 const abstract_poset_member* xschema,
                 const string& xname,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema xschema,  name xname, and table dofs initialized by xtable_dofs.
  ///
  void new_state(namespace_poset* xhost,
                 const abstract_poset_member* xschema,
                 const string& xname,
                 void* xtable_dofs,
                 size_t xtable_dofs_ub,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state with schema xschema,
  /// name xname and table dofs xdof_tuple
  ///
  ///
  virtual void new_state(namespace_poset* xhost,
			 const abstract_poset_member* xschema,
			 const string& xname,
			 array_poset_dof_map* xdof_tuple,
			 bool xauto_access = true);

private:

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
  /// Allow editing of jims and jim order relation.
  ///
  virtual void begin_jim_edit_mode(bool xauto_access = true);

  ///
  /// Prevent editing of jims and jim order relation.
  ///
  virtual void end_jim_edit_mode(bool xensure_lattice_invariant = true,
                                 bool xauto_access = true);

protected:

  // The using declaration is placed here as opposed to being at the beginning
  // of the public "new_state" methods because putting it in the public section
  // makes the following new_state method public also.

  using poset_state_handle::new_state;

  ///
  /// Creates a new poset state with path xpath, schema xschema and table dof map xdof_map,
  /// attaches this to the state.
  ///
  virtual void new_state(const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map);

  ///
  /// @deprecated Use new_state(const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map).
  /// Creates a new poset state with schema xschema and table dof map xdof_map
  /// and attaches this to the state. Assumes the associated namespace member has
  /// already been created and initialized. Intended for use by i/o subsystem.
  ///
  virtual void new_state(const schema_poset_member& xschema, array_poset_dof_map& xdof_map);

private:

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
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual poset* clone() const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};

} // namespace sheaf

#endif // POSET_H

