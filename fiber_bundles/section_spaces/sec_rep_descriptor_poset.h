

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_rep_descriptor_poset

#ifndef SEC_REP_DESCRIPTOR_POSET_H
#define SEC_REP_DESCRIPTOR_POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

#ifndef SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE_H
#include "sec_rep_descriptor_table_dofs_type.h"
#endif

namespace sheaf
{
  class namespace_poset;
}

namespace fiber_bundle
{

using namespace sheaf;

class base_space_poset;
class sec_rep_descriptor;

///
/// The poset for sec_rep_descriptors.
///
class SHEAF_DLL_SPEC sec_rep_descriptor_poset : public poset
{
  friend class sheaf::namespace_poset; // Qualification needed by g++ 4.2.2
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name SEC_REP_DESCRIPTOR_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this poset.
  ///
  typedef sec_rep_descriptor member_type;
  
  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef sec_rep_descriptor_table_dofs_type table_dofs_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(const poset_path& xprototypes_path);

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// The name of the standard sec_rep_descriptor poset.
  ///
  static const string& standard_poset_name();

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// Creates a new handle attached to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  sec_rep_descriptor_poset(namespace_poset& xhost,
			   const string& xname,
			   const arg_list& xargs,
			   const poset_path& xschema_path,
			   bool xauto_access);

  ///
  /// The base space members prototypes poset.
  ///
  const base_space_poset& prototypes() const;

  ///
  /// The base space members prototypes poset.
  ///
  base_space_poset& prototypes();

protected:

  ///
  /// Creates an unattached handle
  ///
  sec_rep_descriptor_poset();

  ///
  /// Destructor
  ///
  virtual ~sec_rep_descriptor_poset();

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  sec_rep_descriptor_poset& operator=(const poset_state_handle& xother);

  ///
  /// Base space members prototypes poset.
  ///
  base_space_poset* _prototypes;  

  ///
  /// Initializes xarg to satisfy class invariants.
  ///
  virtual void initialize_arg_list(const namespace_poset& xns,
				   const string& xname,
				   arg_list& xargs,
				   const poset_path& xschema_path,
				   bool xauto_access);

  ///
  /// Creates prototype for this class and enters in in factory.
  ///
  static bool make_prototype();

private:

  //@}


  // ===========================================================
  /// @name POSET FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
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
  /// Attaches this external poset to a new poset state with schema
  /// given by xschema and table dofs by xdof_map.
  /// Intended for use by i/o subsystem.
  ///
  virtual void new_state(const schema_poset_member& xschema,
                         array_poset_dof_map& xdof_map);

  ///
  /// Initializes the handle data members that depend on the
  /// table dofs and are required to get access when this handle
  /// is used to create a new state. Intended to be called only
  /// from new_state.
  ///
  virtual void initialize_handle_data_members(const namespace_poset& xns);

  ///
  /// Initializes the handle data members when this handle
  /// is attached to a state.
  ///
  virtual void attach_handle_data_members();

  ///
  /// Release all access to posets this depends on,
  /// then detach and delete the state.
  ///
  virtual void terminate_access();

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual sec_rep_descriptor_poset* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};

} // namespace fiber_bundle

#endif // SEC_REP_DESCRIPTOR_POSET_H
