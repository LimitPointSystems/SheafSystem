

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class poset_scaffold

#ifndef POSET_SCAFFOLD_H
#define POSET_SCAFFOLD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef ARG_LIST_H
#include "arg_list.h"
#endif

#ifndef AUTO_BLOCK_H
#include "auto_block.h"
#endif

#ifndef INTERVAL_INDEX_SPACE_HANDLE_H
#include "interval_index_space_handle.h"
#endif

#ifndef NAME_MULTIMAP_H
#include "name_multimap.h"
#endif

#ifndef RECORD_MAP_H
#include "record_map.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

#ifndef POSET_DATA_TYPE_MAP_H
#include "poset_data_type_map.h"
#endif

#ifndef RECORD_QUEUE_H
#include "record_queue.h"
#endif

#ifndef SCHEMA_POSET_MEMBER_H
#include "schema_poset_member.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef STD_VECTOR_H
#include "std_vector.h"
#endif

#ifndef STORAGE_AGENT_H
#include "storage_agent.h"
#endif

namespace sheaf
{

class poset_bounds;
class subposet;  
class namespace_poset;

///
/// A poset specific collection of data converters,
/// various buffers and other data used while
/// transferring posets between internal and external
/// representations.
///
class SHEAF_DLL_SPEC poset_scaffold : public any
{

  // ===========================================================
  /// @name POSET_SCAFFOLD FACET
  // ===========================================================
  //@{

public:

  ///
  /// Copy constructor
  ///
  poset_scaffold(const poset_scaffold& xother);

  ///
  /// Destructor
  ///
  virtual ~poset_scaffold();

  ///
  /// Create an instance with primitive type converters from xtype_map
  /// and default member record types.
  ///
  poset_scaffold(const poset_state_handle& xposet,
		 const storage_agent::transaction& xtrans,
		 data_type_map& xtype_map,
		 const string& xfile_id_space_name,
		 bool xis_write_transaction);

  ///
  /// The handle for the poset being transferred.
  /// (Name chosen to void name conflict with class poset.)
  /// (mutable version)
  ///
  poset_state_handle& structure();

  ///
  /// The handle for the poset being transferred.
  /// (Name chosen to void name conflict with class poset.)
  /// (const version)
  ///
  const poset_state_handle& structure() const;

  ///
  /// The powerset for the poset being transferred. (mutable version)
  ///
  poset_powerset_state& powerset();

  ///
  /// The powerset for the poset being transferred. (const version).
  ///
  const poset_powerset_state& powerset() const;

  ///
  /// The table state for the poset being transferred. (mutable version)
  ///
  poset_table_state& table();  

  ///
  /// The table state for the poset being transferred. (const version)
  ///
  const poset_table_state& table() const;  

  ///
  /// True is this is a write transaction.
  ///
  bool is_write_transaction() const;

  ///
  /// The bounds for the rows in this transaction (mutable version).
  ///
  poset_bounds& row_bounds();

  ///
  /// The bounds for the rows in this transaction (const version).
  ///
  const poset_bounds& row_bounds() const;

  ///
  /// The bounds for the columns in this transaction (mutable version).
  ///
  poset_bounds& col_bounds();

  ///
  /// The bounds for the columns in this transaction (const version).
  ///
  const poset_bounds& col_bounds() const;

  ///
  /// The bounds for the table of contents in this transaction.
  ///
  const poset_bounds& toc_bounds() const;

  ///
  /// Replaces toc_bounds() with the bounds specified in
  /// descriptor xdesc.
  ///
  void update_toc_bounds(const poset_bounds_descriptor& xdesc);

  ///
  /// If row bounds lower bound is an alias for the toc bounds,
  /// substitutes the toc bounds into the row bounds.
  ///
  void evaluate_toc_alias();

  ///
  /// The resident subposet for structure() (mutable version).
  ///
  subposet& resident();

  ///
  /// The resident subposet for structure() (const version).
  ///
  const subposet& resident() const;

  ///
  /// The name space of this poset.
  ///
  namespace_poset* name_space() const;

  ///
  /// True if the poset being transferred is the name space poset.
  ///
  bool structure_is_namespace() const;

  ///
  /// The name space index of this poset.
  ///
  scoped_index index() const;

  ///
  /// The name of this poset.
  ///
  string name() const;

  ///
  /// The schema of the poset in internal namespace (mutable version).
  ///
  schema_poset_member& internal_schema();

  ///
  /// The schema of the poset in internal namespace (const version).
  ///
  const schema_poset_member& internal_schema() const;

  ///
  /// The schema for the restriction that is being read or written (mutable version)
  ///
  schema_poset_member& transfer_schema();

  ///
  /// The schema for the restriction that is being read or written (const version)
  ///
  const schema_poset_member& transfer_schema() const;

  ///
  /// The schema of the poset in external namespace (mutable version).
  ///
  schema_poset_member& external_schema();

  ///
  /// The schema of the poset in external namespace (const version).
  ///
  const schema_poset_member& external_schema() const;

  ///
  /// Data type map for this poset (mutable version)
  ///
  poset_data_type_map& type_map();

  ///
  /// Data type map for this poset (const version)
  ///
  const poset_data_type_map& type_map() const;

  ///
  /// The name of the id space used for the member index map.
  ///
  const string& file_id_space_name() const;

  ///
  /// True if poset has more than one version (mutable version).
  ///
  bool& is_versioned();

  ///
  /// True if poset has more than one version (const version).
  ///
  const bool& is_versioned() const;

  ///
  /// Initialize internal, transfer, and
  /// external schema for read transactions.
  ///
  void initialize_schema_for_read(schema_poset_member* xext_schema,
                                  int xschema_version);

  ///
  /// Initialize internal, transfer, and
  /// external schema for read transactions.
  ///
  void initialize_transfer_schema_for_read(const scoped_index& xindex);

  ///
  /// Inserts xid, xname pair into char buffer xbuf.
  ///
  void insert_id_name_pair(pod_index_type xid, const string& xname, block<char>& xbuf);

  ///
  /// Extracts xid, xname pair from char buffer xbuf.
  ///
  void extract_id_name_pair(pod_index_type& xid, string& xname, char*& xbuf);

protected:

private:

  /// @todo replace the next several features with a transaction object.

  ///
  /// The handle for this poset
  ///
  poset_state_handle& _structure;

  ///
  /// True is this is a write transaction.
  ///
  bool _is_write_transaction;

  ///
  /// The bounds for the rows in this transaction.
  ///
  poset_bounds* _row_bounds;

  ///
  /// The bounds for the columns in this transaction.
  ///
  poset_bounds* _col_bounds;

  ///
  /// The bounds for the table of contents in this transaction.
  ///
  poset_bounds* _toc_bounds;

  ///
  /// The resident subposet for structure().
  ///
  subposet _resident;

  ///
  /// The schema of the poset in internal namespace.
  ///
  schema_poset_member* _internal_schema;

  ///
  /// The part of the schema (restriction) of the poset which is
  /// to be transferred between the internal and external namespace.
  ///
  schema_poset_member* _transfer_schema;

  ///
  /// The schema of the poset in external namespace.
  ///
  schema_poset_member* _external_schema;

  ///
  /// Initialize internal, transfer, and
  /// external schema for write transactions.
  ///
  void initialize_schema_for_write();

  ///
  /// Type map for this poset
  ///
  poset_data_type_map _type_map;

  ///
  /// The name of the id space used for the external index maps.
  ///
  string _file_id_space_name;

  ///
  /// True if poset has more than one version.
  ///
  bool _is_versioned;

  //@}


  // ===========================================================
  /// @name MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Type for member index space.
  ///
  typedef interval_index_space_handle member_index_space_type;

  ///
  /// Type for member name map
  ///
  typedef name_multimap<pod_index_type> member_name_map_type;

  // The following features are logically members
  // of class member_record, but are placed here so they
  // will only be initialized once per poset, rather than
  // once per member record.

  ///
  /// Sets the member record specific data types
  ///
  void put_member_record_type_aliases(int xtoc_index,
                                      int xdof_tuple_id_index,
                                      int xoffset_index);

  ///
  /// Initializes member_id_space().
  ///
  void initialize_member_id_space();

  ///
  /// True if member_id_space() has been initialized.
  ///
  bool member_id_space_initialized() const;

  ///
  /// An id in the member external id space with pod mapped from xid.
  ///
  scoped_index member_ext_id(const scoped_index& xid) const;

  ///
  /// An id in the member external id space with pod xid.
  ///
  scoped_index member_ext_id(pod_index_type xid) const;

  ///
  /// External to internal member index space for structure() (mutable version).
  ///
  member_index_space_type& member_id_space();

  ///
  /// External to internal member index space for structure() (const version).
  ///
  const member_index_space_type& member_id_space() const;

  ///
  /// External index to member name map (mutable version).
  ///
  member_name_map_type& member_name_map();

  ///
  /// External index to member name map (const version).
  ///
  const member_name_map_type& member_name_map() const;

  ///
  /// Type of member class names map.
  ///
  typedef hash_map<pod_index_type, pair<string, size_type> > member_class_names_type;

  ///
  /// Member class names (mutable version).
  ///
  member_class_names_type& member_class_names();

  ///
  /// Member class names (const version).
  ///
  const member_class_names_type& member_class_names() const;

  ///
  /// Converts namespace relative member id at location xbuf
  /// to namespace relative record id at location xbuf.
  ///
  void convert_member_id_to_record_id(void *buf);

  ///
  /// Converts namespace relative record id at location xbuf
  /// to namespace relative member id at location xbuf.
  ///
  void convert_record_id_to_member_id(void *buf);

protected:

private:

  ///
  /// Internal to external member index space.
  ///
  member_index_space_type _member_id_space;

  ///
  /// External record index to member name map
  ///
  member_name_map_type _member_name_map;

  ///
  /// Member class names.
  ///
  member_class_names_type _member_class_names;

  //@}


  // ===========================================================
  /// @name SUBPOSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// Type for subposet index space.
  ///
  typedef interval_index_space_handle subposet_index_space_type;

  ///
  /// Initializes subposet_id_space().
  ///
  void initialize_subposet_id_space();

  ///
  /// True if subposet_id_space has been initialized.
  ///
  bool subposet_id_space_initialized() const;

  ///
  /// An id in the subposet external id space with pod mapped from xid.
  ///
  scoped_index subposet_ext_id(const scoped_index& xid) const;

  ///
  /// An id in the subposet external id space with pod xid.
  ///
  scoped_index subposet_ext_id(pod_index_type xid) const;

  ///
  /// External to internal subposet index map for powerset() (mutable version).
  ///
  subposet_index_space_type& subposet_id_space();

  ///
  /// External to internal subposet index space for powerset() (const version).
  ///
  const subposet_index_space_type& subposet_id_space() const;

  ///
  /// Buffer for subposet handles (mutable version).
  ///
  vector<subposet*>& subposets();

  ///
  /// Buffer for subposet handles (const version).
  ///
  const vector<subposet*>& subposets() const;

  ///
  /// Converts namespace relative subposet id at location xbuf
  /// to namespace relative record id at location xbuf.
  ///
  void convert_subposet_id_to_record_id(void* xbuf);

  ///
  /// Converts namespace relative record id at location xbuf
  /// to namespace relative subposet id at location xbuf.
  ///
  void convert_record_id_to_subposet_id(void* xbuf);

protected:

private:

  ///
  /// Internal to external subposet index space
  ///
  subposet_index_space_type _subposet_id_space;

  ///
  /// Buffer for subposet handles
  ///
  vector<subposet*> _subposets;

  ///
  /// Initializes subposet index space and handle buffer.
  ///
  void initialize_subposets();

  //@}


  // ===========================================================
  /// @name DOF_TUPLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Type for dof tuple index space.
  ///
  typedef interval_index_space_handle dof_tuple_index_space_type;

  ///
  /// Initializes dof_tuple_id_space().
  ///
  void initialize_dof_tuple_id_space();

  ///
  /// True if dof_tuple_id_space() has been initialized.
  ///
  bool dof_tuple_id_space_initialized() const;

  ///
  /// An id in the dof tuple external id space with pod mapped from xid.
  ///
  scoped_index dof_tuple_ext_id(const scoped_index& xid) const;

  ///
  /// An id in the dof tuple external id space with pod xid.
  ///
  scoped_index dof_tuple_ext_id(pod_index_type xid) const;

  ///
  /// External to internal dof_tuple index space for table() (mutable version).
  ///
  dof_tuple_index_space_type& dof_tuple_id_space();

  ///
  /// External to internal dof_tuple index space for table() (const version).
  ///
  const dof_tuple_index_space_type& dof_tuple_id_space() const;

  ///
  /// The scratch id for the dof tuple id space.
  ///
  pod_index_type dof_tuple_scratch_id() const;

  ///
  /// Set the scratch id for the dof tuple id space.
  ///
  void put_dof_tuple_scratch_id(pod_index_type xid);

  ///
  /// Type of dof tuple types map.
  ///
  typedef hash_map<pod_index_type, dof_tuple_type> dof_tuple_types_type;

  ///
  /// Dof tuple type ids (mutable version).
  ///
  dof_tuple_types_type& dof_tuple_types();

  ///
  /// Dof tuple type ids (const version).
  ///
  const dof_tuple_types_type& dof_tuple_types() const;

  ///
  /// Type of dof tuple class names map.
  ///
  typedef hash_map<pod_index_type, string> dof_tuple_class_names_type;

  ///
  /// Dof tuple class names (mutable version).
  ///
  dof_tuple_class_names_type& dof_tuple_class_names();

  ///
  /// Dof tuple class names (const version).
  ///
  const dof_tuple_class_names_type& dof_tuple_class_names() const;

  ///
  /// Type of dof tuple versions map.
  ///
  typedef hash_map<pod_index_type, int> dof_tuple_schema_versions_type;

  ///
  /// Dof tuple schema versions (mutable version).
  ///
  dof_tuple_schema_versions_type& dof_tuple_schema_versions();

  ///
  /// Dof tuple schema versions (const version).
  ///
  const dof_tuple_schema_versions_type& dof_tuple_schema_versions() const;

  ///
  /// True if dof_tuple_schema_versions() contains an entry for
  /// external dof tuple id xdof_tuple_ext_id .
  ///
  bool dof_tuple_schema_versions_contains(pod_index_type xdof_tuple_ext_id) const;

  ///
  /// The external schema version for the dof tuple
  /// with external id xdof_tuple_ext_id.
  ///
  int dof_tuple_schema_version(pod_index_type xext_id) const;

  ///
  /// Type of dof tuple schema ids map.
  ///
  typedef hash_map<pod_index_type, pod_index_type> dof_tuple_schema_ids_type;

  ///
  /// Dof tuple schema ids (mutable version).
  ///
  dof_tuple_schema_ids_type& dof_tuple_schema_ids();

  ///
  /// Dof tuple schema ids (const version).
  ///
  const dof_tuple_schema_ids_type& dof_tuple_schema_ids() const;

  ///
  /// True if dof_tuple_schema_ids() contains an entry for
  /// external dof tuple id xdof_tuple_ext_id .
  ///
  bool dof_tuple_schema_ids_contains(pod_index_type xdof_tuple_ext_id) const;

  ///
  /// The external schema id for the dof tuple with external id xdof_tuple_ext_id.
  ///
  pod_index_type dof_tuple_schema_id(pod_index_type xdof_tuple_ext_id) const;

  ///
  /// The internal schema id for the dof tuple with external id xdof_tuple_ext_id.
  ///
  pod_index_type dof_tuple_schema_int_id(pod_index_type xdof_tuple_ext_id) const;

  ///
  /// Type of dof tuple col bounds map.
  ///
  typedef hash_map<pod_index_type, poset_bounds_descriptor>
    dof_tuple_col_bounds_type;

  ///
  /// Dof tuple col bounds map (mutable version).
  ///
  dof_tuple_col_bounds_type& dof_tuple_col_bounds();

  ///
  /// Dof tuple col bounds map (const version).
  ///
  const dof_tuple_col_bounds_type& dof_tuple_col_bounds() const;

  ///
  /// True if dof_tuple_col_bounds() contains an entry for
  /// external dof tuple id xdof_tuple_ext_id .
  ///
  bool dof_tuple_col_bounds_contains(pod_index_type xdof_tuple_ext_id) const;

  ///
  /// A descriptor for the column bound for
  /// the dof tuple with external id xdof_tuple_ext_id.
  ///
  const poset_bounds_descriptor& dof_tuple_col_bound(pod_index_type xdof_tuple_ext_id) const;

  ///
  /// Insets the descriptor for the column bound for
  /// the dof tuple with external id xdof_tuple_ext_id
  /// into the map.
  ///
  void put_dof_tuple_col_bound(pod_index_type xdof_tuple_ext_id);

  ///
  /// Translate the dof tuple column bounds from external ids to internal ids.
  ///
  void translate_dof_tuple_col_bounds();

  // Note: dof_tuple_domain_offsets uses map rather than hash_map
  // because there is no default hash function for pairs.
  // Best case performance is not as good as hash_map, but
  // should be adequate.

  ///
  /// Type of dof tuple domain offsets map.
  ///
  typedef map<pair<pod_index_type, pod_index_type>, pod_index_type>
    dof_tuple_domain_offsets_type;

  ///
  /// Dof tuple domain offsets accessor (mutable version).
  ///
  dof_tuple_domain_offsets_type& dof_tuple_domain_offsets();

  ///
  /// Dof tuple domain offsets accessor (const version).
  ///
  const dof_tuple_domain_offsets_type& dof_tuple_domain_offsets() const;

  ///
  /// True of dof_tuple_domain_offsets() contains an entry
  /// for pair (xdof_tuple_ext_id, xdomain_key).
  ///
  bool dof_tuple_domain_offsets_contains(pod_index_type xdof_tuple_ext_id,
                                         pod_index_type xdomain_key) const;
  ///
  /// The offset for domain xdomain_key in tuple xdof_tuple_ext_id.
  ///
  pod_index_type dof_tuple_domain_offset(pod_index_type xdof_tuple_ext_id,
					 pod_index_type xdomain_key) const;

protected:

private:

  ///
  /// Internal to external dof_tuple index space
  ///
  dof_tuple_index_space_type _dof_tuple_id_space;

  ///
  /// The scatch id for the dof tuple id space.
  ///
  pod_index_type _dof_tuple_scratch_id;

  ///
  /// Dof tuple type ids.
  ///
  dof_tuple_types_type _dof_tuple_types;

  ///
  /// Dof tuple class names.
  ///
  dof_tuple_class_names_type _dof_tuple_class_names;

  ///
  /// Dof tuple schema versions.
  ///
  dof_tuple_schema_versions_type _dof_tuple_schema_versions;

  ///
  /// Dof tuple schema ids.
  ///
  dof_tuple_schema_ids_type _dof_tuple_schema_ids;

  ///
  /// Dof tuple column bounds.
  ///
  dof_tuple_col_bounds_type _dof_tuple_col_bounds;

  ///
  /// Dof tuple domain offsets.
  ///
  dof_tuple_domain_offsets_type _dof_tuple_domain_offsets;

  //@}


  // ===========================================================
  /// @name ID_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The initialization type of the id space block.
  ///
  typedef zero_block_initialization_policy<mutable_index_space_handle*> init_type;

  ///
  /// The type of the id space block.
  ///
  typedef auto_block<mutable_index_space_handle*, init_type> id_spaces_type;

  ///
  /// Buffer for id spaces (mutable version).
  ///
  id_spaces_type& id_spaces();

  ///
  /// Buffer for id spaces (const version).
  ///
  const id_spaces_type& id_spaces() const;

protected:

private:

  ///
  /// Buffer for id spaces.
  ///
  id_spaces_type _id_spaces;

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual poset_scaffold* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

protected:

private:

  //@}

};

} // namespace sheaf

#endif // ifndef POSET_SCAFFOLD_H







