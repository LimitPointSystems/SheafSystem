
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//



// Implementation for class storage_agent

#include "storage_agent.h"
#include "assert_contract.h"

#include "array_poset_dof_map.h"
#include "attributes_record_set.h"
#include "dof_tuple_record_set.h"
#include "error_message.h"
#include "interval_index_space_state.h"
#include "member_names_record.h"
#include "member_record.h"
#include "member_record_set.h"
#include "namespace_poset.h"
#include "namespace_poset_member.h"
#include "poset.h"
#include "poset_bounds.h"
#include "poset_bounds_descriptor.h"
#include "poset_data_type_map.h"
#include "poset_general_record.h"
#include "poset_handle_factory.h"
#include "poset_state_handle.h"
#include "postorder_itr.h"
#include "preorder_itr.h"
#include "schema_poset_member.h"
#include "subposet_names_record.h"
#include "total_poset_member.h"

#include "index_equivalence_iterator.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

namespace
{
  //
  // The default number of records allocated in a
  // member record buffer during a transaction.
  //
  const int DEFAULT_MEMBER_RECORD_BUFFER_UB = 1000;

  //
  // OBSOLETE: no longer used. The default number of bytes in a dof_tuple record.
  //
  const size_t DEFAULT_DOF_TUPLE_RECORD_SIZE = 1024;  

  //
  // The default number of records allocated in a
  // dof_tuple record buffer during a transaction.
  //
  const int DEFAULT_DOF_TUPLE_RECORD_BUFFER_UB = 4;
}



// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
sheaf::storage_agent::
storage_agent()
{

  // Preconditions:


  // Body:

  _member_record_buffer_ub    = DEFAULT_MEMBER_RECORD_BUFFER_UB;
  _dof_tuple_record_size      = DEFAULT_DOF_TUPLE_RECORD_SIZE;
  _dof_tuple_record_buffer_ub = DEFAULT_DOF_TUPLE_RECORD_BUFFER_UB;

  // Reset the start time.

  reset_time();

  // Postconditions:

  ensure(invariant());
  ensure(transaction_ct() == 0);
  ensure(member_record_buffer_ub() == DEFAULT_MEMBER_RECORD_BUFFER_UB);
  ensure(dof_tuple_record_size() == DEFAULT_DOF_TUPLE_RECORD_SIZE);
  ensure(dof_tuple_record_buffer_ub() == DEFAULT_DOF_TUPLE_RECORD_BUFFER_UB);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
sheaf::storage_agent::
storage_agent(const storage_agent& xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // postconditions:

  ensure(invariant());
}



///
sheaf::storage_agent*
sheaf::storage_agent::
clone() const
{
  storage_agent* result =0;
  // Initialized only to silence compiler warnings
  // until implemented.

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
sheaf::storage_agent::
~storage_agent()
{

  // Preconditions:

  // Body:

  // Close the file if it is open

  if(_file.is_open())
  {
    _file.close();
  }

  // Postconditions:

  // Exit:

  return;
}


///
bool
sheaf::storage_agent::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  ///@todo finish storage_agent::invariant

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::storage_agent::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const storage_agent*>(other) != 0;

  // Postconditions:

  return result;

}



// STORAGE_AGENT INTERFACE



///
sheaf::storage_agent::
storage_agent(const string& xfile_name,
              sheaf_file::access_mode xmode,
              bool xclobber,
              bool xenable_error_report)
{

  // Preconditions:

  require(!xfile_name.empty());
  require(xfile_name.substr(xfile_name.size() - 4) == ".hdf");

  // Body:

  _member_record_buffer_ub    = DEFAULT_MEMBER_RECORD_BUFFER_UB;
  _dof_tuple_record_size      = DEFAULT_DOF_TUPLE_RECORD_SIZE;
  _dof_tuple_record_buffer_ub = DEFAULT_DOF_TUPLE_RECORD_BUFFER_UB;

  if(xenable_error_report)
  {
    // Turn on the standard HDF error reporting.

    H5Eset_auto1(reinterpret_cast<herr_t (*)(void*)>(H5Eprint), stderr);
  }
  else
  {
    // Turn off HDF error reporting.

    H5Eset_auto1(NULL, NULL);
  }

  // Open the file.

  _file.open(xfile_name, xmode, xclobber);

  // Set the file id space name.

  string::size_type lpos = xfile_name.find_last_of('/');
  lpos = (lpos == string::npos) ? 0 : lpos+1;
  string lname = xfile_name.substr(lpos);

  _file_id_space_name = poset_path::reserved_prefix() + lname;

  // Reset the start time.

  reset_time();

  // Postconditions:

  ensure(invariant());
  ensure(transaction_ct() == 0);
  ensure(member_record_buffer_ub() == DEFAULT_MEMBER_RECORD_BUFFER_UB);
  ensure(dof_tuple_record_size()   == DEFAULT_DOF_TUPLE_RECORD_SIZE);
  ensure(dof_tuple_record_buffer_ub() == DEFAULT_DOF_TUPLE_RECORD_BUFFER_UB);
  ensure(file().is_open());
}

sheaf::sheaf_file&
sheaf::storage_agent::
file()
{
  return _file;
}



///
const sheaf::sheaf_file&
sheaf::storage_agent::
file() const
{
  return _file;
}



///
bool
sheaf::storage_agent::
file_is_read_accessible() const
{
  bool result;

  // Preconditions:

  // Body:

  result = file().is_open();

  // Postconditions:

  ensure(result == file().is_open());

  // Exit

  return result;
}



///
bool
sheaf::storage_agent::
file_is_read_only_accessible() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (file().mode() == sheaf_file::READ_ONLY);

  // Postconditions:

  ensure(result == (file().mode() == sheaf_file::READ_ONLY));

  // Exit

  return result;
}



///
bool
sheaf::storage_agent::
file_is_read_write_accessible() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (file().mode() == sheaf_file::READ_WRITE);

  // Postconditions:

  ensure(result == (file().mode() == sheaf_file::READ_WRITE));

  // Exit

  return result;
}

const string&
sheaf::storage_agent::
file_id_space_name() const
{
  return _file_id_space_name;
}

void
sheaf::storage_agent::
reset_time()
{
  // Preconditions:

  // Body:

  _start_time = clock();

  // Postconditions:

  // Exit:
}



///
clock_t
sheaf::storage_agent::
time() const
{
  // Preconditions:

  // Body:

  clock_t result = clock() - _start_time;

  // Postconditions:

  // Exit:

  return result;
}


// CONSTANTS FOR ACCESS ROUTINE ARGUMENTS

const bool sheaf::storage_agent::COMMIT = true;
const bool sheaf::storage_agent::ABORT = false;
const bool sheaf::storage_agent::RETAIN_READ = true;
const bool sheaf::storage_agent::RELEASE_ALL = false;


// ===========================================================
// NAMESPACE_POSET FACET
// ===========================================================

///
void
sheaf::storage_agent::
read_entire(namespace_poset& xns)
{

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!transaction_is_active(xns));

  // Body:

  define_old_variable(int old_access_request_depth = xns.access_request_depth());

  // Read the namespace itself

  read(xns);

  // Read all the posets in it that have not already been read.

  read_remainder(xns);

  // Postconditions:

  ensure(!transaction_is_active(xns));
  ensure(xns.access_request_depth() == old_access_request_depth);
  ensure(unexecutable("for all members m of xns: !m.is_external()"));

  // Exit

  return;
}


///
void
sheaf::storage_agent::
read_remainder(namespace_poset& xns)
{

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!transaction_is_active(xns));

  // Body:

  define_old_variable(int old_access_request_depth = xns.access_request_depth());

  // Read all the posets in the namespace that have not already been read.

  zn_to_bool_postorder_itr itr(xns.top(), "jims", DOWN, NOT_STRICT);
  while(!itr.is_done())
  {

#ifdef DIAGNOSTIC_OUTPUT
    cout << "testing is_external for poset " << xns.member_name(itr.index()) << endl;
#endif

    poset_state_handle& p = xns.member_poset(itr.index());
    if(p.is_external())
    {
      read(p);
    }
    itr.next();
  }

  // Postconditions:

  ensure(!transaction_is_active(xns));
  ensure(xns.access_request_depth() == old_access_request_depth);
  ensure(unexecutable("for all members m of xns: !m.is_external()"));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
read(namespace_poset& xns)
{

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!transaction_is_active(xns));

  // Body:

  define_old_variable(int old_access_request_depth = xns.access_request_depth());

  begin_read_transaction(xns);
  end_transaction(xns, ABORT);

#ifdef DIAGNOSTIC_OUTPUT
  cout << static_cast<poset_state_handle&>(xns) << endl;
#endif

  // Postconditions:

  ensure(!transaction_is_active(xns));
  ensure(xns.access_request_depth() == old_access_request_depth);

  // Exit

  return;
}

///
void
sheaf::storage_agent::
write(namespace_poset& xns)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xns.is_attached());
  require(xns.state_is_read_write_accessible());
  require(!xns.index().is_valid());
  require(!transaction_is_active(xns));

  // Body:

  initialize_namespace_id_spaces_for_write(xns);

  // Begin the transaction.

  begin_write_transaction(xns);

  // Commit and end the transaction

  end_transaction(xns, COMMIT);

  // Postconditions:

  ensure(state_is_consistent(xns));
  ensure(!transaction_is_active(xns));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
write_entire(namespace_poset& xns)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xns.is_attached());
  require(xns.state_is_read_write_accessible());
  require(!transaction_is_active(xns));
  require(unexecutable("for all members m of xns( !transaction_is_active(m))"));

  // Body:

  // Write the name space itself

  write(xns);

  // Write all the posets in it.

  write_remainder(xns);

  // Postconditions:

  ensure(state_is_consistent(xns));
  ensure(!transaction_is_active(xns));
  ensure(unexecutable("for all members m of xns(state_is_consistent(m))"));
  ensure(unexecutable("for all members m of xns( !transaction_is_active(m))"));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
write_remainder(const namespace_poset& xns)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xns.is_attached());
  require(xns.state_is_read_accessible());

  /// @todo make the following executable

  require(unexecutable("xns itself has already been written"));
  require(unexecutable("for all members p of xns(!p.is_external())"));
  require(!transaction_is_active(xns));
  require(unexecutable("for all members p of xns(!transaction_is_active(p))"));

  // Body:

  // Write all the posets in the namespace that
  // have not been written since the last time hey were changed.

  zn_to_bool_postorder_itr itr(xns.top(), "jims", DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    poset_state_handle& p = xns.member_poset(itr.index());

    assertion(!p.is_external());

    p.get_read_access();
    if(!state_is_consistent(p))
    {
      write(p);
    }
    p.release_access();

    itr.next();
  }

  // Postconditions:

  ensure(state_is_consistent(xns));
  ensure(!transaction_is_active(xns));
  ensure(unexecutable("for all members m of xns(state_is_consistent(m))"));
  ensure(unexecutable("for all members m of xns(!transaction_is_active(m))"));

  // Exit

  return;
}


// ===========================================================
// GENERAL POSET FACET
// ===========================================================

///
void
sheaf::storage_agent::
read(poset_state_handle& xposet,
     const poset_bounds_descriptor& xrow_bounds,
     const poset_bounds_descriptor& xcol_bounds)
{

  // Preconditions:

  /// require(xposet.is_external()); /// @todo relax this requirement
  require(!transaction_is_active(xposet));

  // Body:

  int old_access_request_depth = xposet.is_external() ? 0 : xposet.access_request_depth();

  begin_read_transaction(xposet, xrow_bounds, xcol_bounds);
  end_transaction(xposet, ABORT);

  // Postconditions:

  ensure(!xposet.is_external());
  ensure(xposet.access_request_depth() == old_access_request_depth);

  // Exit

  return;
}

///
void
sheaf::storage_agent::
read_toc(poset_state_handle& xposet)
{

  // Preconditions:

  require(xposet.is_external());
  require(!transaction_is_active(xposet));

  // Body:

  poset_bounds_descriptor lrow_bounds(poset_bounds_descriptor::SUBPOSET_MEMBER,
                                      TOC_INDEX,
                                      TOP_INDEX);

  read(xposet, lrow_bounds);

  // Postconditions:

  ensure(!xposet.is_external());
  ensure(xposet.access_request_depth() == 0);

  // Exit

  return;
}

///
void
sheaf::storage_agent::
read_index(poset_state_handle& xposet)
{

  // Preconditions:

  require(xposet.is_external());
  require(!transaction_is_active(xposet));

  // Body:

  read(xposet,
       poset_bounds_descriptor::BOTTOM_TOP,
       poset_bounds_descriptor::BOTTOM_BOTTOM);

  // Postconditions:

  ensure(!xposet.is_external());
  ensure(xposet.access_request_depth() == 0);

  // Exit

  return;
}

///
void
sheaf::storage_agent::
read_row_decomposition(poset_state_handle& xposet,
		       const scoped_index& xdecomp_id)
{

  // Preconditions:

  /// @todo make the following executable.
  /// @issue may want to introduce a state machine to coordinate
  /// multiple partial read/write transactions.

  require(unexecutable("Have already read the table of contents"));
  require(!transaction_is_active(xposet));

  // Body:

  int old_access_request_depth = xposet.is_external() ? 0 : xposet.access_request_depth();

  poset_bounds_descriptor lrow_bounds(poset_bounds_descriptor::MEMBER_SUBPOSET,
                                      BOTTOM_INDEX,
                                      xdecomp_id.hub_pod());

  read(xposet, lrow_bounds);

  // Postconditions:

  ensure(!xposet.is_external());
  ensure(xposet.access_request_depth() == old_access_request_depth);

  // Exit

  return;
}

///
void
sheaf::storage_agent::
write(poset_state_handle& xposet,
      const poset_bounds_descriptor& xrow_bounds,
      const poset_bounds_descriptor& xcol_bounds,
      bool xretain_read_access)
{

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << SOURCE_CODE_LOCATION;
  cout << "writing poset " << xposet.name() << " index: " << xposet.index() << endl;
#endif

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xposet.is_attached());
  require(xposet.state_is_read_accessible());
  require(xposet.index().is_valid());
  require(!transaction_is_active(xposet));
  require(xcol_bounds.ub_member_is_not_top() ?
          xposet.schema().ge(xcol_bounds.ub_id()) :
          true);

  /// @hack the product subposet hack, version 2.
  /// See poset_scaffold::dof_tuple_schema_int_id
  /// for the origin of the following requirement.

  require(unexecutable("if xposet is a section space, col bound is base space decomposition or same fiber as xposet"));


  // Body:

  // Begin the transaction.

  begin_write_transaction(xposet, xrow_bounds, xcol_bounds);

  if(xretain_read_access)
  {
    // Commit the transaction.

    commit_transaction(xposet);

    // Release write access but not read access.

    active_transaction(xposet).is_write_transaction = false;
  }
  else
  {
    // Commit and end the transaction

    end_transaction(xposet, COMMIT);
  }

  // Postconditions:

  ensure(state_is_consistent(xposet));
  ensure(!write_transaction_is_active(xposet));
  ensure(read_transaction_is_active(xposet) == xretain_read_access);

  // Exit

  return;
}

///
void
sheaf::storage_agent::
write_toc(poset_state_handle& xposet, const scoped_index& xtoc_id)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xposet.is_attached());
  require(xposet.state_is_read_accessible());
  require(!transaction_is_active(xposet));
  require(xposet.includes_subposet(xtoc_id));

  // Body:

  poset_bounds_descriptor lrow_bounds(poset_bounds_descriptor::SUBPOSET_MEMBER,
                                      xtoc_id.hub_pod(),
                                      TOP_INDEX);

  write(xposet, lrow_bounds);

  // Postconditions:

  ensure(state_is_consistent(xposet));
  ensure(!transaction_is_active(xposet));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
write_row_decomposition(poset_state_handle& xposet,
			const scoped_index& xdecomp_id)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xposet.is_attached());
  require(xposet.state_is_read_accessible());
  require(!transaction_is_active(xposet));
  require(xposet.includes_subposet(xdecomp_id));

  // Body:

  poset_bounds_descriptor lrow_bounds(poset_bounds_descriptor::MEMBER_SUBPOSET,
                                      BOTTOM_INDEX,
                                      xdecomp_id.hub_pod());

  write(xposet, lrow_bounds);

  // Postconditions:

  ensure(state_is_consistent(xposet));
  ensure(!transaction_is_active(xposet));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
write_col_decomposition(poset_state_handle& xposet,
			const scoped_index& xrow_id,
                        const scoped_index& xdecomp_id)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xposet.is_attached());
  require(xposet.state_is_read_accessible());
  require(!transaction_is_active(xposet));

  /// @hack the product subposet hack.
  /// Following precondition can not be enforced because
  /// xdecomp_id may be subposet of base space, not schema itself
  ///
  /// require(xposet.schema().host()->includes_subposet(xdecomp_id));

  // Body:

  poset_bounds_descriptor lrow_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                      xrow_id,
                                      xrow_id);

  poset_bounds_descriptor lcol_bounds(poset_bounds_descriptor::MEMBER_SUBPOSET,
                                      BOTTOM_INDEX,
                                      xdecomp_id.hub_pod());

  write(xposet, lrow_bounds, lcol_bounds);

  // Postconditions:

  // ensure(state_is_consistent(xposet));
  ensure(!transaction_is_active(xposet));

  // Exit

  return;
}

// ===========================================================
// DOF_TUPLE FACET
// ===========================================================

///
void
sheaf::storage_agent::
write_dof_tuple(const abstract_poset_member& xmbr,
                const scoped_index& xcol_ub_id,
                const scoped_index& xdecomp_id)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xmbr.state_is_read_accessible());
  require(!transaction_is_active(*(xmbr.host())));

  /// @hack the product subposet hack.
  /// Following precondition can not be enforced because
  /// xdecomp_id may be subposet of base space, not schema itself
  ///
  /// require(xposet.schema().host()->includes_subposet(xdecomp_id));

  // Body:

  poset_bounds_descriptor lrow_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                      xmbr.index(),
                                      xmbr.index());

  poset_bounds_descriptor lcol_bounds(poset_bounds_descriptor::MEMBER_SUBPOSET,
                                      BOTTOM_INDEX,
                                      xdecomp_id.hub_pod());

  begin_write_transaction(*(xmbr.host()), lrow_bounds, lcol_bounds);

  commit_dof_tuple_transaction(xmbr, xcol_ub_id, xdecomp_id);

  remove_active_transaction(*(xmbr.host()));

  // Postconditions:

  // ensure(state_is_consistent(xposet));
  ensure(!transaction_is_active(*(xmbr.host())));

  // Exit

  return;
}

void
sheaf::storage_agent::
commit_dof_tuple_transaction(const abstract_poset_member& xmbr,
                             const scoped_index& xcol_ub_id,
                             const scoped_index& xdecomp_id)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(write_transaction_is_active(*(xmbr.host())));
  require(xmbr.state_is_read_write_accessible());

  // Body:

  poset_state_handle& lposet = *(xmbr.host());

  // Get the transaction description.

  const transaction& ltrans = active_transaction(lposet);

  // Initialize the member and dof tuple index spaces.
  // The index spaces maintain the association between
  // internal and external index spaces.

  initialize_poset_id_spaces_for_write(lposet);

  // Create the poset scaffold.
  // The scaffold buffers various data from when it
  // is computed until when it is used or written.

  poset_scaffold lscaffold(lposet,
                           ltrans,
                           file().type_map(),
                           _file_id_space_name,
                           true);

  // Write the posets on which this poset depends.

  write_prerequisites(lscaffold);

  // Write this dof tuple.

  // Open the dof tuple record set.

  dof_tuple_record_set ldof_tuple_records(file(), dof_tuple_record_size(), dof_tuple_record_buffer_ub(), lscaffold);
  ldof_tuple_records.open();

  lscaffold.evaluate_toc_alias();


  scoped_index lint_dof_tuple_id;
  xmbr.dof_tuple_id(lint_dof_tuple_id, false);

  // Get the external dof tuple id, if one has been assigned.

  scoped_index lext_dof_tuple_id =
    lscaffold.dof_tuple_ext_id(lint_dof_tuple_id);

  if(!lext_dof_tuple_id.is_valid())
  {
    // This is the first time we've encountered this dof tuple;
    // get an external id for it. External id will be the offset of
    // the beginning of the tuple in the dataset.

    lext_dof_tuple_id = ldof_tuple_records.compute_ext_id(lint_dof_tuple_id);

    // Save the dof tuple type and class name to be written in the
    // respective map; map must not already contain an entry for lext_dof_tuple_id.

    assertion(lscaffold.dof_tuple_types().find(lext_dof_tuple_id.pod()) ==
           lscaffold.dof_tuple_types().end());

    dof_tuple_type ltype_id = xmbr.dof_map().type_id();
    pair<pod_index_type, dof_tuple_type>
      lmap_pair(lext_dof_tuple_id.pod(), ltype_id);

    lscaffold.dof_tuple_types().insert(lmap_pair);

    assertion(lscaffold.dof_tuple_class_names().find(lext_dof_tuple_id.pod()) ==
           lscaffold.dof_tuple_class_names().end());

    string lclass_name = xmbr.dof_map().class_name();
    pair<pod_index_type, string> lname_map_pair(lext_dof_tuple_id.pod(), lclass_name);

    lscaffold.dof_tuple_class_names().insert(lname_map_pair);
  }

  ldof_tuple_records.externalize_domain(lext_dof_tuple_id, xcol_ub_id);

  // Close the record set.

  ldof_tuple_records.close();

  // Postconditions:

  ensure(write_transaction_is_active(lposet));

  // Exit

  return;
}

// ===========================================================
// TRANSACTION FACET
// ===========================================================

///
void
sheaf::storage_agent::
begin_read_transaction(namespace_poset& xns)
{

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!transaction_is_active(xns));

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << SOURCE_CODE_LOCATION;
  cout << "reading poset " << xns.name() << endl;
#endif

  define_old_variable(int old_access_request_depth = xns.access_request_depth());

  // Want to read all the rows and whatever columns are in the file.
  // Enter xns in the set of active read transactions

  transaction ltrans(READ, xns);
  put_active_transaction(ltrans);

  // Clear the namespace, except for the standard members
  // bottom, top, primitives, primitives schema, and primitive definitions members.
  // Also deletes all non-standard id spaces.

  xns.clear();

  // Initialize index spaces for members, subposets, and dof tuples
  // in name space and its standard posets.

  initialize_namespace_id_spaces_for_read(xns);

  // Create the poset scaffold.
  // The scaffold buffers various data from when it
  // is read until it can be used to build the poset.

  poset_scaffold lscaffold(xns,
                           ltrans,
                           file().type_map(),
                           _file_id_space_name,
                           false);

  // Read this poset

  // Open and read the general attributes record set.
  // Gets the external schema which is needed to instantiate
  // the dof tuple record set.

  attributes_record_set lattributes_records(file(), lscaffold);
  lattributes_records.open();
  lattributes_records.internalize();

  // The poset and its subposets have been created;
  // now we can attach the bounds objects.

  lscaffold.evaluate_toc_alias();

  // Open the other record sets.

  dof_tuple_record_set ldof_tuple_records(file(), dof_tuple_record_size(), dof_tuple_record_buffer_ub(), lscaffold);
  ldof_tuple_records.open();

  member_record_set lmember_records(file(), member_record_buffer_ub(), lscaffold, ldof_tuple_records);
  lmember_records.open();

  // Read and convert the other record sets to internal form.

  lmember_records.internalize(lscaffold.row_bounds().ub_id());
  ldof_tuple_records.internalize();

  // Close the record sets.

  lmember_records.close();
  ldof_tuple_records.close();
  lattributes_records.close();

  //
  // Reset the namespace name from whatever the client
  // chose initially to the name in the file.
  //
  string lns_name = lattributes_records.poset_name();
  xns.put_name(lns_name);

  // The non-standard dof tuples all have void pointers in them.
  // Allocate external handles instead.

  namespace_poset_member lns_mbr(xns.top());
  zn_to_bool_postorder_itr itr(lns_mbr, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    lns_mbr.attach_to_state(&xns, itr.index());

    if(lns_mbr.is_jim() && lns_mbr.index().pod() >= xns.standard_member_ct())
    {
      // The current member is not a standard member;
      // create an external handle for it.
      // Handle pointer is inserted in namespace dof tuple by
      // attach_to_state.
      // Do not delete the handle!

      poset_state_handle* lmbr_poset =
        poset_state_handle::new_poset_handle(lns_mbr.poset_class(), lns_mbr.poset_type_id());

      lmbr_poset->attach_to_state(&lns_mbr);

      /// @hack all the non-standard members are restricted to
      /// schema member io; see member_record::new_row_dof_tuple.
      /// Patch this up by extending the schema to top.

      lns_mbr.dof_map().extend_to_top();
    }

    itr.next();
  }

  
  lns_mbr.detach_from_state();

  // Postconditions:

  ensure(read_transaction_is_active(xns));
  ensure(xns.access_request_depth() == old_access_request_depth);

  // Exit

  return;
}

///
void
sheaf::storage_agent::
begin_read_transaction(poset_state_handle& xposet,
                       const poset_bounds_descriptor& xrow_bounds,
                       const poset_bounds_descriptor& xcol_bounds)
{

  // Preconditions:

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << SOURCE_CODE_LOCATION;
  cout << "reading poset: " << xposet.name()  << " index: " << xposet.index() << endl;
#endif

  require(!transaction_is_active(xposet));

  // Body:

  int old_access_request_depth =
    xposet.is_external() ? 0 : xposet.access_request_depth();

  // Enter xposet in the set of active read transactions

  transaction ltrans(READ, xposet, xrow_bounds, xcol_bounds);
  put_active_transaction(ltrans);

  // Read all the posets this poset depends on.

  read_prerequisites(xposet, xcol_bounds);

  // Read this poset:

  // Deal with the "pointer bug":
  // Make sure we use the handle that is held by the namespace for all operations.
  // Ensures that states, members, and subposets don't hold pointers to
  // handles that will later disappear.

  poset_state_handle& lposet = xposet.name_space()->member_poset(xposet.index());

  // Create the poset scaffold.
  // The scaffold buffers various data from when it
  // is read until it can be used to build the poset.

  poset_scaffold lscaffold(lposet,
                           ltrans,
                           file().type_map(),
                           _file_id_space_name,
                           false);

  // Open and read the general attributes record set.
  // Gets the external schema and instantiates the poset state;
  // see poset_general_record::transfer_internal_buffer_to_poset.

#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << SOURCE_CODE_LOCATION;
  cout << "opening record sets for poset " << lposet.name() << endl;
#endif

  attributes_record_set lattributes_records(file(), lscaffold);
  lattributes_records.open();
  lattributes_records.internalize();

  // The poset and its subposets have been created;
  // now we can attach the bounds objects.

  lscaffold.evaluate_toc_alias();

  // Open the other record sets.

  dof_tuple_record_set ldof_tuple_records(file(),
                                          dof_tuple_record_size(),
                                          dof_tuple_record_buffer_ub(),
                                          lscaffold);
  ldof_tuple_records.open();

  member_record_set lmember_records(file(),
                                    member_record_buffer_ub(),
                                    lscaffold,
                                    ldof_tuple_records);
  lmember_records.open();

  // Read and convert the other record sets to internal form.

  index_iterator* lrow_itr = lposet.bound_iterator(lscaffold.row_bounds(), true);

  while(!lrow_itr->is_done())
  {
    lmember_records.internalize(lrow_itr->index());

    ldof_tuple_records.internalize();
    lrow_itr->next();
  }
  delete lrow_itr;

  // Finished with the bounds; detach them.

  // Close the record sets.

  lmember_records.close();
  ldof_tuple_records.close();
  lattributes_records.close();

#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << SOURCE_CODE_LOCATION;
  cout << "closed record sets for poset " << lposet.name() << endl;
#endif

  // Tranfser member names from scaffold to poset.
  // Have to do this after member_names_record in attribute record set
  // has been internlized and after all members have been internalized.

  lscaffold.put_member_names_to_poset();

  // Make sure client handle is attached to
  // new state created by read.

  if(xposet.is_external())
  {
    xposet.attach_to_state(&lposet);
  }

  // Release any access acquired by the read process.
  /// @todo this will have to be changed when reads supported for !is_external.
  /// @error should release access to prerequisites acquired in read_prerequisites.

  while(lposet.access_request_depth() > old_access_request_depth)
  {
    lposet.release_access();
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << lposet << endl;
#endif

  // Postconditions:

  ensure(!xposet.is_external());
  ensure(xposet.access_request_depth() == old_access_request_depth);
  ensure(read_transaction_is_active(xposet));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
begin_read_write_transaction(poset_state_handle& xposet,
                             const poset_bounds_descriptor& xrow_bounds,
                             const poset_bounds_descriptor& xcol_bounds)
{

  // Preconditions:

  require(!transaction_is_active(xposet));

  // Body:

  begin_read_transaction(xposet, xrow_bounds, xcol_bounds);

  // Mark transaction as write transaction;

  //   // have to remove, modify, and reinsert the transaction.

  //   transaction ltrans(active_transaction(xposet));
  //   remove_active_transaction(xposet);
  //   ltrans.is_write_transaction = true;
  //   put_active_transaction(ltrans);

  active_transaction(xposet).is_write_transaction = true;


  // Postconditions:

  ensure(read_transaction_is_active(xposet));
  ensure(write_transaction_is_active(xposet));

  // Exit

  return;
}

void
sheaf::storage_agent::
begin_write_transaction(namespace_poset& xns)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xns.state_is_read_write_accessible());
  require(!transaction_is_active(xns));

  // Body:

  // Enter xns in the set of active write transactions

  poset_bounds_descriptor lcol_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                      BOTTOM_INDEX,
                                      IO_INDEX);

  transaction ltrans(WRITE, xns, poset_bounds_descriptor::BOTTOM_TOP, lcol_bounds);
  put_active_transaction(ltrans);

  // Postconditions:

  ensure(write_transaction_is_active(xns));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
begin_write_transaction(const poset_state_handle& xposet,
                        const poset_bounds_descriptor& xrow_bounds,
                        const poset_bounds_descriptor& xcol_bounds)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(xposet.is_attached());
  require(xposet.state_is_read_accessible());
  require(!transaction_is_active(xposet));
  require(xcol_bounds.ub_member_is_not_top() ?
          xposet.schema().ge(xcol_bounds.ub_id()) :
          true);

  // Body:

  // Enter xposet in the set of active write transactions

  transaction ltrans(WRITE, xposet, xrow_bounds, xcol_bounds);
  put_active_transaction(ltrans);

  // Postconditions:

  ensure(write_transaction_is_active(xposet));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
commit_transaction(poset_state_handle& xposet)
{

  // Preconditions:

  require(file_is_read_write_accessible());
  require(write_transaction_is_active(xposet));

  /// @issue Should really be read-write accessible so that the new
  ///        id space functions can require write access.  However,
  ///        writing only requires read access in general.

  require(xposet.state_is_read_accessible());

  // Body:

  // Get the transaction description.

  const transaction& ltrans = active_transaction(xposet);

  // Initialize the member and dof tuple index spaces.
  // The index spaces maintain the association between
  // internal and external index spaces.

  initialize_poset_id_spaces_for_write(xposet);

  // Create the poset scaffold.
  // The scaffold buffers various data from when it
  // is computed until when it is used or written.

  poset_scaffold lscaffold(xposet,
                           ltrans,
                           file().type_map(),
                           _file_id_space_name,
                           true);

  // Write the posets on which this poset depends.

  write_prerequisites(lscaffold);

  // Write this poset

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << SOURCE_CODE_LOCATION;
  cout << "opening record sets for poset " << xposet.name() << endl;
#endif

  // Transfeer member names from poset to scaffold.
  // Have to do this before attributes records are externalized,
  // but now is a good a time as any.

  lscaffold.get_member_names_from_poset();

  // Open all the record sets.

  dof_tuple_record_set ldof_tuple_records(file(),
                                          dof_tuple_record_size(),
                                          dof_tuple_record_buffer_ub(),
                                          lscaffold);
  ldof_tuple_records.open();


  member_record_set lmember_records(file(),
                                    member_record_buffer_ub(),
                                    lscaffold,
                                    ldof_tuple_records);
  lmember_records.open();
  //  lmember_records.initialize_external_ids();

  attributes_record_set lattributes_records(file(), lscaffold);
  lattributes_records.open();

  // Write the record sets.

  lscaffold.evaluate_toc_alias();

  index_iterator* lrow_itr = xposet.bound_iterator(lscaffold.row_bounds(), true);

  while(!lrow_itr->is_done())
  {
    lmember_records.externalize(lrow_itr->index());

    ldof_tuple_records.externalize();

    lrow_itr->next();
  }
  delete lrow_itr;

  lattributes_records.externalize();

  // Close the record sets.

  lmember_records.close();
  ldof_tuple_records.close();
  lattributes_records.close();

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << SOURCE_CODE_LOCATION;
  cout << "closed record sets for poset " << xposet.name() << endl;
#endif

  // Now the state is consistent.

  put_state_is_consistent(xposet);

  // Postconditions:

  ensure(write_transaction_is_active(xposet));
  ensure(state_is_consistent(xposet));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
end_transaction(poset_state_handle& xposet, bool xcommit)
{

  // Preconditions:

  require(transaction_is_active(xposet));
  require(xcommit ? file_is_read_write_accessible() : true);
  require(xcommit ? write_transaction_is_active(xposet) : true);

  // Body:

  define_old_variable(int old_access_request_depth = xposet.access_request_depth());

  if(xcommit)
    commit_transaction(xposet);

  // Remove the xposet from the set of active transactions

  remove_active_transaction(xposet);

  // Postconditions:

  ensure(!transaction_is_active(xposet));
  ensure( xcommit ? state_is_consistent(xposet) : true );
  ensure(xposet.access_request_depth() == old_access_request_depth);

  // Exit

  return;
}


// ===========================================================
// BUFFER SIZE CONTROL FACET
// ===========================================================



///
int
sheaf::storage_agent::
member_record_buffer_ub() const
{
  return _member_record_buffer_ub;
}


///
void
sheaf::storage_agent::
put_member_record_buffer_ub(int xub)
{
  // Preconditions:

  require(xub > 0);

  // Body:

  _member_record_buffer_ub = xub;

  // Postconditions:

  ensure(member_record_buffer_ub() == xub);

  // Exit

  return;
}

///
size_t
sheaf::storage_agent::
dof_tuple_record_size() const
{
  return _dof_tuple_record_size;
}

///
void
sheaf::storage_agent::
put_dof_tuple_record_size(size_t xsize)
{
  // Preconditions:

  // Body:

  _dof_tuple_record_size = xsize;

  // Postconditions:

  ensure(dof_tuple_record_size() == xsize);

  // Exit

  return;
}

///
int
sheaf::storage_agent::
dof_tuple_record_buffer_ub() const
{
  return _dof_tuple_record_buffer_ub;
}

///
void
sheaf::storage_agent::
put_dof_tuple_record_buffer_ub(int xub)
{
  // Preconditions:

  require(xub > 0);

  // Body:

  _dof_tuple_record_buffer_ub = xub;

  // Postconditions:

  ensure(dof_tuple_record_buffer_ub() == xub);

  // Exit

  return;
}

// TRANSACTION STATUS FACET

///
int
sheaf::storage_agent::
transaction_ct() const
{
  int result;

  // Preconditions:

  // Body:

  result = _active_transactions.size();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}



///
bool
sheaf::storage_agent::
transaction_is_active(pod_index_type xindex) const
{
  bool result;

  // Preconditions:

  // Body:

  transaction ltrans(xindex);
  set<transaction>::const_iterator itr = _active_transactions.find(ltrans);

  result = itr != _active_transactions.end();

  // Postconditions:

  // Exit

  return result;
}



///
bool
sheaf::storage_agent::
transaction_is_active(const poset_state_handle& xposet) const
{
  bool result;

  // Preconditions:

  // Body:

  transaction ltrans(READ, xposet); // type doesn't matter here.
  set<transaction>::const_iterator itr = _active_transactions.find(ltrans);

  result = itr != _active_transactions.end();

  // Postconditions:

  // Exit

  return result;
}



///
bool
sheaf::storage_agent::
read_transaction_is_active(const poset_state_handle& xposet) const
{
  bool result;

  // Preconditions:

  // Body:

  transaction ltrans(READ, xposet); // type doesn't matter here.
  set<transaction>::const_iterator itr = _active_transactions.find(ltrans);

  result = (itr != _active_transactions.end()) && itr->is_read_transaction;

  // Postconditions:

  // Exit

  return result;
}



///
bool
sheaf::storage_agent::
write_transaction_is_active(const poset_state_handle& xposet) const
{
  bool result;

  // Preconditions:

  // Body:

  transaction ltrans(WRITE, xposet); // type doesn't actually matter here.
  set<transaction>::const_iterator itr = _active_transactions.find(ltrans);

  result = (itr != _active_transactions.end()) && itr->is_write_transaction;

  // Postconditions:

  // Exit

  return result;
}



///
bool
sheaf::storage_agent::
read_write_transaction_is_active(poset_state_handle& xposet) const
{
  bool result;

  // Preconditions:

  // Body:


  result = read_transaction_is_active(xposet) &&
           write_transaction_is_active(xposet);

  // Postconditions:

  // Exit

  return result;
}



///
bool
sheaf::storage_agent::
state_is_consistent(const poset_state_handle& xposet) const
{
  bool result;

  // Preconditions:

  require(xposet.is_attached() ? xposet.state_is_read_accessible() : true);

  // Body:

  // The definition of this condition is:
  // internal state exists and
  // external state exists and
  // internal hasn't been modified since external was written.

  // internal state exists = xposet.is_attached();
  // external state exists = member index space exists
  // not modified = !xposet.state_is_modified()
  //
  // Note that is_attached() is a precondition for evaluating the
  // other two conditions.

  /// @hack use of member index space as test for external state
  /// is a temporary implementation. Need more formal support for this test.
  /// In order for this hack to work, we clear the index spaces in
  /// write(namespace_poset&). Furthermore, since this routine is typically
  /// called before any attempt to write a poset, the call to member_id_space
  /// below actually creates the index space.
  /// @todo replace with some better mechanism.

  result = xposet.is_attached();

  result =
    result &&
    xposet.member_id_spaces(false).contains(_file_id_space_name) &&
    !xposet.member_id_spaces(false).is_empty(_file_id_space_name);

  result =
    result &&
    xposet.subposet_id_spaces(false).contains(_file_id_space_name) &&
    !xposet.subposet_id_spaces(false).is_empty(_file_id_space_name);

  result =
    result &&
    xposet.dof_tuple_id_spaces(false).contains(_file_id_space_name);

  result = result && !xposet.state_is_modified();

  // Postconditions:

  // Exit

  return result;
}


// PROTECTED MEMBER FUNCTIONS

void
sheaf::storage_agent::
put_state_is_consistent(poset_state_handle& xposet)
{
  // Preconditions:

  require(xposet.is_attached());

  // Body:

  xposet.clear_state_is_modified();

  // Postconditions:

  // Exit

  return;
}

// ROUTINES TO SUPPORT INDEPENDENT ACCESS

///
void
sheaf::storage_agent::
read_prerequisites(const poset_state_handle& xposet,
                   const poset_bounds_descriptor& xcol_bounds)
{

  // Preconditions:

  require(xposet.name_space()->state_is_read_write_accessible());

  // Body:

  namespace_poset* lns = xposet.name_space();

  // Read the posets on which this poset depends:
  // Get a handle to the name space member for xposet.

  namespace_poset_member lname_space_mbr(xposet.name_space(), xposet.index());

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Inspecting prerequisites of poset " << lname_space_mbr.name() << endl;
#endif

  // Read  prerequisites.

  for(int i=0; i<PREREQ_IDS_UB; ++i)
  {
    pod_index_type lprereq_id = lname_space_mbr.poset_prereq_id(i);

#ifdef DIAGNOSTIC_OUTPUT
      cout << "\tprereq_id = " << lprereq_id << endl;
#endif

    if(is_valid(lprereq_id))
    {
      // Get the poset associated with the member; has to be non-null

      poset_state_handle& lposet = lns->member_poset(lprereq_id);

      if(lposet.is_external())
      {
        // Prerequisite has not been read in; read it.

        begin_read_transaction(lposet);
      }

      // We'll need read access to the
      // prerequisite to read the poset.
      // Released in table_dof_tuple_record::release_prerequisites()
      // after we've actually created the poset state.

      lposet.get_read_access();

#ifdef DIAGNOSTIC_OUTPUT
	cout << "prereq name: " << lposet.name() << endl;
#endif

      // lposet is handle from namespace - do not detach or delete it!
    }
  }

  // Clean up

  lname_space_mbr.detach_from_state();

  // Postconditions:

  ensure(unexecutable(all prerequisites have been internalized));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
write_prerequisites(const poset_scaffold& xscaffold)
{

  // Preconditions:

  require(!xscaffold.structure().is_external());
  require(xscaffold.name_space()->state_is_read_accessible());

  // Body:

  // Make sure the posets on which this poset depends have been written to the file:

  namespace_poset* lns = xscaffold.name_space();
  if(xscaffold.structure_is_namespace())
  {
    // This poset is the namespace.
    // It's prerequisite is the namespace schema poset.

    if(!state_is_consistent(lns->namespace_schema()))
    {
      write(lns->namespace_schema());
    }
  }
  else
  {
    // This poset is an ordinary poset.

    // Prerequisites are represented by the name space order.
    // Get a handle to the name space member for xposet.

    namespace_poset_member lname_space_mbr(lns, xscaffold.index());

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Inspecting prerequisites of poset " << lname_space_mbr.name() << endl;
#endif

    for(int i=0; i<PREREQ_IDS_UB; ++i)
    {
      pod_index_type lprereq_id = lname_space_mbr.poset_prereq_id(i);

#ifdef DIAGNOSTIC_OUTPUT
      cout << "\tprereq_id = " << lprereq_id << endl;
#endif

      if(is_valid(lprereq_id))
      {
        // Get the poset associated with the member

        poset_state_handle& lposet = lns->member_poset(lprereq_id);

	lposet.get_read_access();

#ifdef DIAGNOSTIC_OUTPUT
	cout << "prereq name: " << lposet.name() << endl;
#endif

        if(!state_is_consistent(lposet))
        {
          // Prerequisite has been modified since last written to file; write it out.
          // Note that this writes the entire prerequisite poset out, not just some part
          // of it. In particular, it will write out an entire schema, not just the
          // down set of the schema member of the poset that triggered this write.

          write(lposet);

          /// @issue if we retain read access in the main write, do we need
          /// to retain read access to all the prerequisites?
        }

	lposet.release_access();

        // lposet is handle from namespace - do not detach or delete it!
      }
    }

    // Clean up

    lname_space_mbr.detach_from_state();
  }


  // Postconditions:

  /// @issue we can't actually ensure the following if we've released read access.

  ensure(unexecutable("for all prerequisites p: state_is_consistent(p)"));

  // Exit

  return;
}

void
sheaf::storage_agent::
initialize_poset_id_spaces_for_write(poset_state_handle& xposet)
{
  // Preconditions:

  /// @issue Should really be read-write accessible so that the new
  ///        id space functions can require write access.  However,
  ///        writing only requires read access in general.

  require(xposet.state_is_read_accessible());

  // Body:

  // Make sure the member id space exists.
  // Don't clear the id space or initialize scratch ids;
  // may need entries from previous partial read or write.

  if(!xposet.member_id_spaces(false).contains(_file_id_space_name))
  {
    // Doesn't exist; create it.

    arg_list largs = interval_index_space_state::make_arg_list(true);

    xposet.member_id_spaces(false).new_secondary_state(_file_id_space_name,
						       "interval_index_space_state",
						       largs, false);
  }

  // Get a subposet index id space for this poset; create it if needed or
  // clear the id space; entries get reconstructed on each read or write.

  if(!xposet.subposet_id_spaces(false).contains(_file_id_space_name))
  {
    // Doesn't exist; create it.

    arg_list largs = interval_index_space_state::make_arg_list(true);

    xposet.subposet_id_spaces(false).
      new_secondary_state(_file_id_space_name,
			  "interval_index_space_state",
			  largs, false);
  }
  else
  {
    mutable_index_space_handle& lid_space =
      xposet.subposet_id_spaces(false).
      get_id_space<mutable_index_space_handle>(_file_id_space_name);
    lid_space.clear();
    lid_space.release_id_space();
  }

  // Get a dof tuple index id space for this poset; create it if needed.
  // Don't clear the id space, may need entries from previous partial read or write.

  if(!xposet.dof_tuple_id_spaces(false).contains(_file_id_space_name))
  {
    // Doesn't exist; create it.

    arg_list largs = interval_index_space_state::make_arg_list(true);

    xposet.dof_tuple_id_spaces(false).
      new_secondary_state(_file_id_space_name,
			  "interval_index_space_state",
			  largs, false);
  }

  // Postconditions:

  ensure(xposet.member_id_spaces(false).contains(file_id_space_name()));
  ensure(xposet.subposet_id_spaces(false).contains(file_id_space_name()));
  ensure(xposet.dof_tuple_id_spaces(false).contains(file_id_space_name()));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
clear_all_id_spaces(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  /// @error preconditions don't accurately reflect access control

  // Body:

  // Clear the member file id spaces for the name space
  // and every poset in it.

  mutable_index_space_handle lid_space;

  zn_to_bool_postorder_itr itr0(xns.top(), "jims", DOWN, NOT_STRICT);
  while(!itr0.is_done())
  {
    poset_state_handle& lmbr_poset = xns.member_poset(itr0.index());
    if(!lmbr_poset.is_external())
    {
      lmbr_poset.get_read_write_access(true);
      if(lmbr_poset.member_id_spaces(false).contains(_file_id_space_name))
      {
	lid_space.attach_to(lmbr_poset.member_id_spaces(false), _file_id_space_name);
	lid_space.clear();
      }

      poset_powerset_state& lmbr_powerset = lmbr_poset.powerset();
      if(lmbr_poset.subposet_id_spaces(false).contains(_file_id_space_name))
      {
	lid_space.attach_to(lmbr_poset.subposet_id_spaces(false), _file_id_space_name);
	lid_space.clear();
      }

      poset_table_state& lmbr_table = lmbr_poset.table();
      if(lmbr_poset.dof_tuple_id_spaces(false).contains(_file_id_space_name))
      {
	lid_space.attach_to(lmbr_poset.dof_tuple_id_spaces(false), _file_id_space_name);
	lid_space.clear();
      }
      
      lmbr_poset.release_access();
    }

    itr0.next();
  }

  if(xns.member_id_spaces(false).contains(_file_id_space_name))
  {
    lid_space.attach_to(xns.member_id_spaces(false), _file_id_space_name);
    lid_space.clear();
  }

  if(xns.subposet_id_spaces(false).contains(_file_id_space_name))
  {
    lid_space.attach_to(xns.subposet_id_spaces(false), _file_id_space_name);
    lid_space.clear();
  }

  if(xns.dof_tuple_id_spaces(false).contains(_file_id_space_name))
  {
    lid_space.attach_to(xns.dof_tuple_id_spaces(false), _file_id_space_name);
    lid_space.clear();
  }

  // Postconditions:


  // Exit:

  return;
}

///
void
sheaf::storage_agent::
initialize_namespace_id_spaces_for_read(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Clear all the index spaces.
  // Will clear all the file id spaces too, but there shouldn't be any
  // at this point.

  clear_all_id_spaces(xns);

  // Index spaces for the namespace poset itself will be
  // initialized when the namespace is read.

  // Initialize the subposet, dof_tuple and member index spaces
  // for the standard posets. These posets will not be read in
  // but the spaces need to exist for consistency.

  pod_index_type lfirst_member = member_record_set::first_member_record();

  arg_list largs = interval_index_space_state::make_arg_list(true);
  interval_index_space_handle lid_space;

  // Initialize primitives space.

  pod_index_type lid =
    xns.primitives().member_id_spaces(false).
    new_secondary_state(_file_id_space_name,
			"interval_index_space_state",
			largs, false);

  // Reserve 0-th record for id space,
  // then assign record ids sequentially.

  lid_space.attach_to(xns.primitives().member_id_spaces(false), lid);

  pod_index_type lprim_ct = xns.primitives().standard_member_ct();
  lid_space.insert_interval(lfirst_member, lfirst_member+lprim_ct, 0, lprim_ct);

  // Initialize primitives schema space.

  lid = xns.primitives_schema().member_id_spaces(false).
    new_secondary_state(_file_id_space_name,
			"interval_index_space_state",
			largs, false);

  // Reserve 0-th record for id space,
  // then assign record ids sequentially.

  lid_space.attach_to(xns.primitives_schema().member_id_spaces(false), lid);

  pod_index_type lprim_schema_ct =
    xns.primitives_schema().standard_member_ct();
  lid_space.insert_interval(lfirst_member, lfirst_member+lprim_schema_ct,
			    0, lprim_schema_ct);

  // Initialize namespaces schema space.

  lid = xns.namespace_schema().member_id_spaces(false).
    new_secondary_state(_file_id_space_name,
			"interval_index_space_state",
			largs, false);

  // Reserve 0-th record for id space,
  // then assign record ids sequentially.

  lid_space.attach_to(xns.namespace_schema().member_id_spaces(false), lid);

  pod_index_type lnamespace_schema_ct =
    xns.namespace_schema().standard_member_ct();
  lid_space.insert_interval(lfirst_member, lfirst_member+lnamespace_schema_ct,
			    0, lnamespace_schema_ct);
  
  // Postconditions:


  // Exit:

  return;
}

///
void
sheaf::storage_agent::
initialize_namespace_id_spaces_for_write(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Clear all the file id spaces.
  // Necessary because non-existent or empty file id space
  // used by state_is_consistent
  // to determine if external state exists.

  clear_all_id_spaces(xns);

  // The id spaces will be recreated and populated as needed
  // when the posets are written.

  // Postconditions:


  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

///
/// The reserved, standard external name for the namespace in the file
///
const string _name_space_ext_name("__name_space");

///
bool
sheaf::storage_agent::transaction::
operator<(const transaction& xother) const
{
  return (target < xother.target);
}

///
sheaf::storage_agent::transaction::
~transaction()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

///
sheaf::storage_agent::transaction::
transaction()
  : row_bounds(poset_bounds_descriptor::BOTTOM_TOP),
    col_bounds(poset_bounds_descriptor::BOTTOM_TOP)
{
  // Preconditions:

  // Body:

  target = invalid_pod_index();

  is_read_transaction  = false;
  is_write_transaction = false;

  // Postconditions:

  ensure(!is_valid(target));
  ensure(!is_read_transaction);
  ensure(!is_write_transaction);
  ensure(row_bounds == poset_bounds_descriptor::BOTTOM_TOP);
  ensure(col_bounds == poset_bounds_descriptor::BOTTOM_TOP);

  // Exit

  return;
}

///
sheaf::storage_agent::transaction::
transaction(pod_index_type xindex)
  : row_bounds(poset_bounds_descriptor::BOTTOM_TOP),
    col_bounds(poset_bounds_descriptor::BOTTOM_TOP)
{
  // Preconditions:

  // Body:

  target = xindex;
  is_read_transaction  = false;
  is_write_transaction = false;

  // Postconditions:

  ensure(target == xindex);
  ensure(!is_read_transaction);
  ensure(!is_write_transaction);
  ensure(row_bounds == poset_bounds_descriptor::BOTTOM_TOP);
  ensure(col_bounds == poset_bounds_descriptor::BOTTOM_TOP);

  // Exit

  return;
}

///
sheaf::storage_agent::transaction::
transaction(transaction_type xtype,
            const poset_state_handle& xposet,
            const poset_bounds_descriptor& xrow_bounds,
            const poset_bounds_descriptor& xcol_bounds)
    : row_bounds(xrow_bounds),
    col_bounds(xcol_bounds)
{
  // Preconditions:

  // Body:

  target = xposet.index().pod();
  switch(xtype)
  {
  case READ:
    is_read_transaction  = true;
    is_write_transaction = false;
    break;

  case WRITE:
    is_read_transaction  = false;
    is_write_transaction = true;
    break;

  case READ_WRITE:
    is_read_transaction  = false;
    is_write_transaction = true;
    break;
  }

  // Postconditions:

  ensure(target == xposet.index().pod());
  ensure(is_read_transaction  == ((xtype == READ) || (xtype == READ_WRITE)));
  ensure(is_write_transaction == ((xtype == WRITE) || (xtype == READ_WRITE)));
  ensure(row_bounds == xrow_bounds);
  ensure(col_bounds == xcol_bounds);

  // Exit

  return;
}


///
const sheaf::storage_agent::transaction&
sheaf::storage_agent::
active_transaction(const poset_state_handle& xposet)
{
  // Preconditions:

  require(transaction_is_active(xposet));

  // Body:

  transaction ltrans(READ, xposet); // type doesn't matter
  set<transaction>::iterator itr = _active_transactions.find(ltrans);

  const transaction& result = *itr;

  // Postconditions:

  // Exit

  return result;
}


///
void
sheaf::storage_agent::
put_active_transaction(transaction& xtransaction)
{
  // Preconditions:

  require(!transaction_is_active(xtransaction.target));

  // Body:

  _active_transactions.insert(xtransaction);

  // Postconditions:

  ensure(transaction_is_active(xtransaction.target));

  // Exit

  return;
}

///
void
sheaf::storage_agent::
remove_active_transaction(const poset_state_handle& xposet)
{
  transaction result;

  // Preconditions:

  // Body:

  transaction ltrans(READ, xposet); // Type doesn't matter.
  (void)_active_transactions.erase(ltrans);

  // Postconditions:

  ensure(!transaction_is_active(xposet));

  // Exit

  return;
}






