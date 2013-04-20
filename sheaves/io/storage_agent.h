//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class storage_agent

#ifndef STORAGE_AGENT_H
#define STORAGE_AGENT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POSET_BOUNDS_DESCRIPTOR_H
#include "poset_bounds_descriptor.h"
#endif

#ifndef RECORD_MAP_H
#include "record_map.h"
#endif

#ifndef SHEAF_FILE_H
#include "sheaf_file.h"
#endif

#ifndef STD_CTIME_H
#include "std_ctime.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef STD_VECTOR_H
#include "std_vector.h"
#endif

namespace sheaf
{

class data_type_aliases_record;
class member_names_record;
class member_record;
class namespace_poset;
class poset;
class poset_data_type_map;
class poset_general_record;
class poset_scaffold;
class abstract_poset_member;
class subposet_names_record;
class poset_state_handle;

///
/// Agent responsible for importing and exporting posets from
/// an external name space which resides on disk.
///
class SHEAF_DLL_SPEC storage_agent : public any
{

  friend class poset_scaffold;
  friend class dof_tuple_record_set;

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor
  ///
  ///
  storage_agent();

  ///
  /// Copy constructor
  ///
  ///
  storage_agent(const storage_agent& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual storage_agent* clone() const;

  ///
  /// Destructor
  ///
  virtual ~storage_agent();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // ===========================================================
  // STORAGE_AGENT FACET
  // ===========================================================

  ///
  /// Creates a storage_agent attached to the file with name xfile_name.
  /// Locks the file against deletion, but does not prevent access to the
  /// file by other processes.
  ///
  storage_agent(const string& xfile_name,
                sheaf_file::access_mode xmode = sheaf_file::READ_WRITE,
                bool xclobber = true,
                bool xenable_error_report = false);

  ///
  /// The file this is attached to.
  ///

  sheaf_file& file();
  
  ///
  /// The file this is attached to.
  ///

  const sheaf_file& file() const;

  ///
  /// True if file is open.
  ///
  bool file_is_read_accessible() const;

  ///
  /// True if file is open with READ_ONLY access.
  ///
  bool file_is_read_only_accessible() const;

  ///
  /// True if file is open with READ_WRITE.
  ///
  bool file_is_read_write_accessible() const;

  ///
  /// The name of the id spaces associated with this file in each poset.
  ///
  const string& file_id_space_name() const;

  ///
  /// Reset the start time.  Set the start time to the CPU time when this
  /// function is called.
  ///
  void reset_time();

  ///
  /// Return the CPU time between when reset_time() was last called and when
  /// this function is called.
  ///
  clock_t time() const;


  // CONSTANTS FOR ACCESS ROUTINE ARGUMENTS

  ///
  /// Value to indicate transaction should be committed.
  ///
  static const bool COMMIT;

  ///
  /// Value to indicate transaction should not be committed.
  ///
  static const bool ABORT;

  ///
  /// Value to indicate read access should be retained.
  ///
  static const bool RETAIN_READ;

  ///
  /// Value to indicate read access should not be retained.
  ///
  static const bool RELEASE_ALL;



  // ===========================================================
  // NAMESPACE_POSET FACET
  // ===========================================================

  ///
  /// Reads the namespace xns and all the posets in it.
  ///
  void read_entire(namespace_poset& xns);

  ///
  /// Reads all members of the namespace that have not already been read.
  ///
  void read_remainder(namespace_poset& xns);

  ///
  /// Reads the namespace xns.
  ///
  void read(namespace_poset& xns);

  ///
  /// Writes the namespace xns.
  ///
  void write(namespace_poset& xns);

  ///
  /// Writes the namespace xns and all the posets in it.
  /// Rewrites any posets that have already been written.
  ///
  void write_entire(namespace_poset& xns);

  ///
  /// Writes all the posets in namespace xns that have not already been written.
  ///
  void write_remainder(const namespace_poset& xns);


  // ===========================================================
  // GENERAL POSET FACET
  // ===========================================================

  ///
  /// Reads the portion of poset xposet specified by the row bounds
  /// xrow_bounds and the column bounds xcol_bounds.
  ///
  void read(poset_state_handle& xposet,
            const poset_bounds_descriptor& xrow_bounds =
              poset_bounds_descriptor::BOTTOM_TOP,
            const poset_bounds_descriptor& xcol_bounds =
              poset_bounds_descriptor::BOTTOM_TOP);

  ///
  /// Reads the table of contents portion of poset xposet.
  ///
  void read_toc(poset_state_handle& xposet);

  ///
  /// Reads the index of poset xposet; that is, it does not read the dof tuples.
  ///
  void read_index(poset_state_handle& xposet);

  ///
  /// Reads poset xposet using the row decomposition identified by index xdecomp_id.
  ///
  void read_row_decomposition(poset_state_handle& xposet,
			      const scoped_index& xdecomp_id);

  ///
  /// Executes an independent write-only transaction for the portion of poset xposet
  /// defined by the down sets of max_row_member_index and max_col_member_index.
  /// If xdownset_filter !=0, deletes the members of the downset of the upper bound,
  /// filtered by xdownset_filter.
  ///
  void write(poset_state_handle& xposet,
             const poset_bounds_descriptor& xrow_bounds = poset_bounds_descriptor::BOTTOM_TOP,
             const poset_bounds_descriptor& xcol_bounds = poset_bounds_descriptor::BOTTOM_TOP,
             bool xretain_read_access = false);

  ///
  /// Writes the portion of poset xposet between the lower bound
  /// specified by the subposet with index xtoc_id and upper bound
  /// top. Registers xtoc_id as lower bounds of the table of the contents.
  ///
  void write_toc(poset_state_handle& xposet, const scoped_index& xtoc_id);

  ///
  /// Writes poset xposet using the row decomposition identified by index xdecomp_id.
  ///
  void write_row_decomposition(poset_state_handle& xposet,
                               const scoped_index& xdecomp_id);

  ///
  /// Writes the member identified by xrow_id in poset xposet using
  /// the column decomposition identified by index xdecomp_id.
  ///
  void write_col_decomposition(poset_state_handle& xposet,
                               const scoped_index& xrow_id,
                               const scoped_index& xdecomp_id);

  // ===========================================================
  // DOF_TUPLE FACET
  // ===========================================================

  ///
  /// Writes the portion of the dof tuple of member xmbr
  /// which is in the downset of the schema member identified
  /// by xcol_ub_id, which must be a member of column decomposition xdecomp_id.
  ///
  void write_dof_tuple(const abstract_poset_member& xmbr,
                       const scoped_index& xcol_ub_id,
                       const scoped_index& xdecomp_id);

  ///
  /// Commits the dof tuple transaction associated with xmbr.
  ///
  void commit_dof_tuple_transaction(const abstract_poset_member& xmbr,
                                    const scoped_index& xcol_ub_id,
                                    const scoped_index& xdecomp_id);

  // ===========================================================
  // TRANSACTION FACET
  // ===========================================================

  ///
  /// Begins an independent read transaction for the namespace xposet.
  ///
  void begin_read_transaction(namespace_poset& xns);

  ///
  /// Begins an independent read transaction for the portion of poset xposet
  /// defined by the down sets of max_row_member_index and max_col_member_index.
  ///
  void begin_read_transaction(poset_state_handle& xposet,
                              const poset_bounds_descriptor& xrow_bounds =
                                poset_bounds_descriptor::BOTTOM_TOP,
                              const poset_bounds_descriptor& xcol_bounds =
                                poset_bounds_descriptor::BOTTOM_TOP);

  ///
  /// Begins an independent read-write transaction for the portion of poset xposet
  /// defined by the down sets of max_row_member_index and max_col_member_index.
  /// Initialize the uncommited (internal) copy from the committed (external)
  /// copy of the poset state.
  ///
  void begin_read_write_transaction(poset_state_handle& xposet,
                                    const poset_bounds_descriptor& xrow_bounds =
                                      poset_bounds_descriptor::BOTTOM_TOP,
                                    const poset_bounds_descriptor& xcol_bounds =
                                      poset_bounds_descriptor::BOTTOM_TOP);

  ///
  /// Begins an independent write transaction for the namespace xns.
  ///
  void begin_write_transaction(namespace_poset& xns);

  ///
  /// Begins an independent write-only transaction for the portion of poset xposet
  /// defined by the down sets of max_row_member_index and max_col_member_index.
  ///
  void begin_write_transaction(const poset_state_handle& xposet,
                               const poset_bounds_descriptor& xrow_bounds =
                                 poset_bounds_descriptor::BOTTOM_TOP,
                               const poset_bounds_descriptor& xcol_bounds =
                                 poset_bounds_descriptor::BOTTOM_TOP);

  ///
  /// Commits the uncommitted state, but does not end the transaction
  /// or release read access.
  ///
  void commit_transaction(poset_state_handle& xposet);

  ///
  /// Ends an independent access transaction
  ///
  void end_transaction(poset_state_handle& xposet, bool xcommit = true);

  // ===========================================================
  // BUFFER SIZE CONTROL FACET
  // ===========================================================

  ///
  /// The number of records allocated in a
  /// member record buffer during a transaction
  ///
  int member_record_buffer_ub() const;

  ///
  /// Sets the number of records allocated in a
  /// member record buffer during a transaction.
  ///
  void put_member_record_buffer_ub(int xub);

  ///
  /// OBSOLETE: no longer used. The number of bytes in a dof tuple record
  /// The dof tuple records are now automatically sized as follows.
  /// For ordinary posets, each record holds an entire dof tuple.
  /// For section spaces, each record holds an instance of the fiber type.
  ///
  size_t dof_tuple_record_size() const;

  ///
  /// OBSOLETE: no longer used. Sets the number of bytes in a dof_tuple record.
  ///
  void put_dof_tuple_record_size(size_t xsize);

  ///
  /// The number of records allocated in a
  /// dof_tuple record buffer during a transaction.
  /// Equal to the HDF chunk size.
  ///
  int dof_tuple_record_buffer_ub() const;

  ///
  /// Sets the number of records allocated in a
  /// dof_tuple record buffer during a transaction
  /// and hence the HDF chunk size.
  ///
  void put_dof_tuple_record_buffer_ub(int xub);


  // ===========================================================
  // TRANSACTION STATUS FACET
  // ===========================================================

  ///
  /// The number of active transactions.
  ///
  int transaction_ct() const;

  ///
  /// True if either a read or write transaction is active
  /// for poset with index xindex.
  ///
  bool transaction_is_active(pod_index_type xindex) const;

  ///
  /// True if either a read or write transaction is active
  /// for poset xposet.
  ///
  bool transaction_is_active(const poset_state_handle& xposet) const;

  ///
  /// True if there is an active read transaction for poset xposet
  ///
  bool read_transaction_is_active(const poset_state_handle& xposet) const;

  ///
  /// True if there is an active write transaction involving
  /// the poset with name space index xindex.
  ///
  bool write_transaction_is_active(const poset_state_handle& xposet) const;

  ///
  /// True if both a read-write transaction is active.
  ///
  bool read_write_transaction_is_active(poset_state_handle& xposet) const;

  ///
  /// True if uncommitted state is consistent with committed state.
  ///
  bool state_is_consistent(const poset_state_handle& xposet) const;


  ///
  /// Type of access associated with a transaction.
  ///
  enum transaction_type
  {
    READ,
    WRITE,
    READ_WRITE
  };

  ///
  /// A transaction entity.
  ///
  class SHEAF_DLL_SPEC transaction
  {
  public:

    ///
    /// The index of the target poset of the transaction.
    ///
    pod_index_type target;

    ///
    /// True if read transaction.
    ///
    mutable bool is_read_transaction;

    ///
    /// True if write transaction.
    ///
    mutable bool is_write_transaction;

    ///
    /// Bounds for the rows accessed in this transaction.
    ///
    mutable poset_bounds_descriptor row_bounds;

    ///
    /// Bounds for the columns accessed in this transaction.
    ///
    mutable poset_bounds_descriptor col_bounds;

    ///
    /// True if this.target < xother.target.
    ///
    bool operator<(const transaction& xother) const;

    ///
    /// Destructor
    ///
    ~transaction();

    ///
    /// Default constructor.
    ///
    transaction();

    ///
    /// Default constructor.
    ///
    transaction(pod_index_type xindex);

    ///
    /// Constructor.
    ///
    transaction(transaction_type xtype,
                const poset_state_handle& xposet,
                const poset_bounds_descriptor& xrow_bounds =
                  poset_bounds_descriptor::BOTTOM_TOP,
                const poset_bounds_descriptor& xcol_bounds =
                  poset_bounds_descriptor::BOTTOM_TOP);

  };

protected:

  ///
  /// Sets the state_is_consistent flag for xposet to true
  ///
  void put_state_is_consistent(poset_state_handle& xposet);

  // ROUTINES TO SUPPORT INDEPENDENT ACCESS

  ///
  /// Reads all posets that xposet depends on.
  ///
  void read_prerequisites(const poset_state_handle& xposet,
                          const poset_bounds_descriptor& xcol_bounds);

  ///
  /// Writes all posets that xposet depends on.
  ///
  void write_prerequisites(const poset_scaffold& xscaffold);

  ///
  /// Initializes the subposet and dof tuple index spaces for poset xposet.
  ///
  void initialize_poset_id_spaces_for_write(poset_state_handle& xposet);

  ///
  /// Ensures that the namespace and its standard posets have
  /// an empty index space for members and no index space for dof tuples.
  ///
  void initialize_namespace_id_spaces_for_read(namespace_poset& xposet);

  ///
  /// Ensures that the namespace and its standard posets have
  /// an empty index space for members and no index space for
  /// dof tuples.
  ///
  void initialize_namespace_id_spaces_for_write(namespace_poset& xposet);

  ///
  /// Clears all dof tuple index spaces.
  ///
  void clear_all_id_spaces(namespace_poset& xns);


private:

  ///
  /// The number of records allocated in the
  /// member record buffer.
  ///
  int _member_record_buffer_ub;

  ///
  /// The number of bytes in a dof_tuple record.
  ///
  size_t _dof_tuple_record_size;

  ///
  /// The number of records allocated in the
  /// dof_tuple record buffer.
  ///
  int _dof_tuple_record_buffer_ub;

  ///
  /// The file this is attached to.
  ///
  sheaf_file _file;

  ///
  /// The name of the id spaces associated with this file in each poset.
  ///
  string _file_id_space_name;

  ///
  /// The set of active transactions.
  /// @hack until this set is shared between processes,
  /// we do not actually have any real transaction control.
  ///
  set<transaction> _active_transactions;

  ///
  /// The start time.  Set to the value of clock() when the constructor is
  /// called or when the reset_time() function is called.
  ///
  clock_t _start_time;

  ///
  /// Returns the active transaction involving poset xposet.
  /// If there is no active transaction, !result.target.is_valid().
  ///
  const transaction& active_transaction(const poset_state_handle& xposet);

  ///
  /// Enters xtransaction in the set of active transactions
  ///
  void put_active_transaction(transaction& xtransaction);

  ///
  /// Removes the active transaction involving poset xposet,
  /// if one exists.
  ///
  void remove_active_transaction(const poset_state_handle& xposet);
    
};
  
} // namespace sheaf

#endif // ifndef STORAGE_AGENT_H







