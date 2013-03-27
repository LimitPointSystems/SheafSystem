// $RCSfile: dof_tuple_record_set.cc,v $ $Revision: 1.48 $ $Date: 2013/01/12 17:17:35 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class dof_tuple_record_set

#include "dof_tuple_record_set.h"

#include "assert_contract.h"
#include "data_converter.h"
#include "error_message.h"
#include "poset_bounds.h"
#include "poset_dof_iterator.h"
#include "poset_scaffold.h"
#include "preorder_member_iterator.h"
#include "primitive_value.h"
#include "sheaf_file.h"
#include "std_iostream.h"
#include "std_strstream.h"
#include "std_string.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

namespace
{
  //
  // The rank of the dataspace for the data set.
  //
  const int DATASPACE_RANK = 1;
}


// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS


// Copy constructor
///
sheaf::dof_tuple_record_set::
dof_tuple_record_set(const dof_tuple_record_set& xother)
    : record_set(xother),
    _record_is_full(xother._record_is_full)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}



// Virtual constructor
///
sheaf::dof_tuple_record_set*
sheaf::dof_tuple_record_set::
clone() const
{
  dof_tuple_record_set* result = 0;

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


// Destructor
///
sheaf::dof_tuple_record_set::
~dof_tuple_record_set()
{

  // Preconditions:

  // Body:

  delete [] _ext_dataspace_dims;

  if(_hdf_int_selection != 0)
  {
    delete [] _hdf_int_selection;
  }

  if(_hdf_ext_selection != 0)
  {
    delete [] _hdf_ext_selection;
  }

  delete [] _hdf_scratch_buf;

  if(_hdf_buf != 0)
  {
    delete [] static_cast<char*>(_hdf_buf);
  }


  // Postconditions:

  // Exit:

  return;
}


///
bool
sheaf::dof_tuple_record_set::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && record_set::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Scratch buffer must be parge enough to hold any fixed length dof.

    invariance(_hdf_scratch_buf_ub >= type_map().max_size());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::dof_tuple_record_set::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const dof_tuple_record_set*>(other) != 0;

  // Postconditions:

  return result;

}



// DOF_TUPLE_RECORD_SET INTERFACE



// NEW HANDLE, NEW STATE CONSTRUCTORS


///
sheaf::dof_tuple_record_set::
dof_tuple_record_set(const sheaf_file& xfile,
                     size_t xrecord_size,
                     int xrecord_buffer_ub,
                     const poset_scaffold& xscaffold)
    : record_set(xfile, xrecord_buffer_ub, xscaffold),
    _record_is_full(xrecord_buffer_ub) // Initialized to false by default
{

  // Preconditions:

  require(xfile.is_open());
  require(xrecord_buffer_ub > 0);

  // Body:

  _ext_dataspace_rank = DATASPACE_RANK;
  _ext_dataspace_dims = new hsize_t[DATASPACE_RANK];

  // _name has been initialized to poset name in record_set;
  // add members dataset suffix to it.

  _name  += ".dof_tuples";
  _alias += ".dof_tuples";

  // Create the HDF selection buffers

  _hdf_selection_ub = _record_buffer_ub;
  _hdf_int_selection  = _hdf_selection_ub > 0 ? new hsize_t[_hdf_selection_ub][DATASPACE_RANK] : 0;
  _hdf_ext_selection  = _hdf_selection_ub > 0 ? new hsize_t[_hdf_selection_ub][DATASPACE_RANK] : 0;
  _hdf_selection_ct = 0;

  // Initialize the HDF data buffer to null.
  // Will be allocated after opening the data set.
  // May reset _record_size; see open().

  _record_size = xrecord_size;
  //  _record_dof_ct = 0;
  _hdf_buf_ub = 0;
  _hdf_buf = 0;

  // Create the scratch buffer.

  _hdf_scratch_buf_ub = type_map().max_size();
  _hdf_scratch_buf = new char[_hdf_scratch_buf_ub];

  // Create the internal dataspace to describe the HDF record buffer.

  hsize_t linit_dims[DATASPACE_RANK];
  linit_dims[0] = _record_buffer_ub;

  _int_dataspace_hdf_id = H5Screate_simple(DATASPACE_RANK, linit_dims, NULL);
  if(_int_dataspace_hdf_id < 0)
  {
    post_fatal_error_message("can't create interior data space");
  }

  // Postconditions:

  ensure(invariant());
  ensure(name() == xscaffold.structure().name()+".dof_tuples");
  ensure(!is_open());
  ensure(record_buffer_ub() == xrecord_buffer_ub);
  ensure(record_buffer_ct() == 0);
}

///
void
sheaf::dof_tuple_record_set::
open()
{
  // Preconditions:

  require(file().is_open());

  // Body:

  // Open the record set.

  record_set::open();

  // The HDF dataset is a rank 1 array of data elements.
  // A record is one data element, so the record size must be
  // the same as the size of the HDF data type.
  // If this is a new file, the data type size has been set
  // from _record_size in create_dataset and the following will not change
  // the value of _record_size. If this is an existing file, the following
  // will reset _record_size to the value from the file.

  _record_size = H5Tget_size(_int_data_type_hdf_id);
  if(_record_size == 0)
  {
    post_fatal_error_message("Unable to get record size.");
  }

  // Create the HDF data buffer.

  _hdf_buf_ub = _record_buffer_ub*_record_size;
  _hdf_buf = _hdf_buf_ub > 0 ? new char[_hdf_buf_ub] : 0;

  // Postconditions:

  ensure(invariant());
  ensure(is_open());

  // Exit

  return;
}

///
void
sheaf::dof_tuple_record_set::
internalize()
{

  // Preconditions:

  require(is_open());
  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "internalizing record set " << name() << endl;
#endif

  // This is a read operation.

  _writing = false;

  // Translate the column bounds for the external dof tuple
  // from external ids to internal ids. Can not be done when read
  // because subposet maps are not populated until members are read.

  scaffold().translate_dof_tuple_col_bounds();

  // Read all the dof tuples in the queue.

  read_records();

  // Now that all the dof tuples have been created,
  // we can schematize the table and row dof subposet.

  schematize();

  // Postconditions:

  ensure(is_open());

  // Exit

  return;
}


///
void
sheaf::dof_tuple_record_set::
read_records()
{

  // Preconditions:

  require(is_open());
  require(scaffold().structure().state_is_read_write_accessible());

  // See below for a discussion of the following precondition:

  require(unexecutable("all tuple schema are comparable to column bounds decomposition"));

  // Body:

  // Get a handle to the schema poset.

  poset_state_handle* lschema_poset = scaffold().structure().schema().host();

  _hdf_selection_ct = 0;
  reset_record_buffer_ct();

  _next_record_pod = 0;

  while(!_record_queue.is_empty())
  {
    // Get the next member off the queue

    pod_index_type ldof_tuple_ext_pod = _record_queue.dequeue();

    // Gather the dofs for this dof tuple from the file into the buffer.
    // Because the dof tuple may contains variable length dofs,
    // we must traverse the dofs in the order they were written,
    // it's the only way we can tell which dof is which. This means
    // we must traverse the dofs using the decomposition and schema
    // they were written with. This means we have to iterate over the
    // external column bounds and within each domain we must iterate
    // over the dofs in the external schema and version.

    // On the other hand, the dof map has already been allocated
    // in member_record::new_row_dof_tuple and we only want to
    // transfer from the external dof tuple to the internal dof tuple
    // the dofs indicated by the schema of the internal dof tuple.
    // We can do this by transferring the enitre external dof tuple
    // into a temporary dof map, then iterating over the internal
    // dof map, transferring the dofs we need.

    const scoped_index& ltuple_id = scaffold().dof_tuple_ext_id(ldof_tuple_ext_pod);
    poset_dof_map& lint_dof_map = scaffold().structure().row_dof_map(ltuple_id);

    pod_index_type lext_dof_tuple_schema_int_id =
      scaffold().dof_tuple_schema_int_id(ldof_tuple_ext_pod);

    // Get the external dof tuple schema version

    int lext_dof_tuple_schema_ver =
      scaffold().dof_tuple_schema_version(ldof_tuple_ext_pod);

    // Create and initialize the temporary dof map for the external dof tuple.
    // Ensure its the right type by cloning the internal dof map.

    poset_dof_map& lext_dof_map = *lint_dof_map.clone();
    lext_dof_map.init_row_dof_map(lint_dof_map.host(),
                                  lext_dof_tuple_schema_int_id,
                                  lext_dof_tuple_schema_ver);

    schema_poset_member& lext_dof_map_schema = lext_dof_map.schema();

    // Get the external column bounds.

    poset_bounds* lext_col_bounds =
      new poset_bounds(scaffold().dof_tuple_col_bound(ldof_tuple_ext_pod));

    // Get an iterator for the column decomposition.

    /// @hack Product subposet hack, version 2.
    /// We need to get the col bounds iterator from a schema member,
    /// not just a poset, because for section space schema we need
    /// to know the fiber id.

    index_iterator* lcol_itr =
      lext_dof_map_schema.bound_iterator(*lext_col_bounds, true);

    // Iterate over the members ("domains") of the col decomposition.

    while(!lcol_itr->is_done())
    {
      // We need to read the dofs in each domain in exactly the same order
      // we wrote them, so we need a schema handle attached to the actual
      // schema used to write each domain. The actual schema was the lesser
      // of the dof tuple schema and the domain schema.

      attach_transfer_schema(lext_dof_map_schema, lcol_itr->index());

      schema_poset_member& lxfr_schema = scaffold().transfer_schema();

      // Get the offset for the current domain.
      //
      // Since the dof tuples in general have variable length dofs, we can not
      // compute the offset from the schema, we have to store it in a map.
      // The map must be keyed by unique, persistent ids for the dof tuple and
      // domain schema member; which means their external ids. But we don't
      // currently directly support external ids for product posets (i.e.
      // section_space_schema_posets).

      /// @hack the product subposet hack, ver 2.
      /// Make the schema get us a suitable key for the offset map.

      pod_index_type ldomain_key =
        lxfr_schema.get_ext_id(scaffold().file_id_space_name());

      // Now lookup the offset in the domain offset map.

      pod_index_type ldom_ext_pod =
        scaffold().dof_tuple_domain_offset(ldof_tuple_ext_pod, ldomain_key);

      // Get a pointer to the corresponding location in the record buffer.

      char* lbuf = get_first_record(ldom_ext_pod);

      size_t lbuf_remainder = _record_size - (ldom_ext_pod % _record_size);

      // Internalize all the dofs in the domain.

      internalize_all_dofs(lxfr_schema, lext_dof_map, lbuf, lbuf_remainder);

      lcol_itr->next();

    } // while(!lcol_itr->is_done())

    delete lcol_itr;
    delete lext_col_bounds;

    // Now we're finished reading the external dofs.
    // Populate the internal dof map from the external dof map.

    populate_internal_dof_map(lext_dof_map, lint_dof_map);


    // We're finished with the external dof map; delete it.

    delete &lext_dof_map;

  } // while(!_record_queue.is_empty())


  // Postconditions:

  ensure(is_open());

  // Exit

  return;
}

///
void
sheaf::dof_tuple_record_set::
externalize()
{
  // Preconditions:

  require(is_open());
  require(scaffold().structure().state_is_read_accessible());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "externalizing record set " << name() << endl;
#endif

  // This is a write operation

  _writing = true;

  // Initialize the record buffer.

  _hdf_selection_ct = 0;
  reset_record_buffer_ct();

  _next_record_pod = 0;

  pod_index_type lext_pod;

  // Externalize and write the record set.

  while(!_record_queue.is_empty())
  {
    // Get the next dof_tuple off the queue

    lext_pod = _record_queue.dequeue();

    const scoped_index& ltuple_id = scaffold().dof_tuple_ext_id(lext_pod);

    // Iterate over the column ("domain") decomposition.

    /// @hack Product subposet hack, version 2.
    /// Have to have a schema member to get bound iterator;
    /// use the external schema, it isn't modfied by previous
    /// bounds iterations and should always have the right
    /// fiber component for section space schema.

    poset_bounds& lcol_bnd = scaffold().col_bounds();
    index_iterator* lcol_itr =
      scaffold().external_schema().bound_iterator(lcol_bnd, true);

    while(!lcol_itr->is_done())
    {
      externalize_one_domain(ltuple_id, lcol_itr->index());

      lcol_itr->next();
    }
    delete lcol_itr;

    // Store the schema version in the scaffold;
    // map should not already have an entry for lext_pod.

    assertion(scaffold().dof_tuple_schema_versions().find(lext_pod) ==
           scaffold().dof_tuple_schema_versions().end());

    poset_dof_map& ldof_map = scaffold().structure().row_dof_map(ltuple_id);

    pair<pod_index_type, int> lmap_pair(lext_pod, ldof_map.schema().version());
    scaffold().dof_tuple_schema_versions().insert(lmap_pair);

    // Store the schema and columns bounds in the scaffold:

    // What we really want when we read the dof tuples is:
    // 1) The actual schema used to write each domain =
    //    {min(col bound, internal tuple schema) for each domain}
    //    Used to read the domains in the same order as written.
    //    This set is not necessarily describable using the current
    //    machinery so we have to write the requested column bounds instead.
    //    We can then recover the actual schema from the col blunds and the
    //    tuple schema
    // 2) The actual dof tuple schema, which is the join of the actual domain schema.
    //    Used to instantiate a temporary external dof tuple into which
    //    we can read the dofs in the same order they were written.
    //    If the domain decomposition contains a single member, then the
    //    actual tuple schema = min(internal tuple schema, col bound).
    //    If not, we assume the column bounds form a decomposition, i.e.
    //    the join of the bounds is the schema of the host and hence
    //    the join of the actual domain schema must be the internal schema.

    // Compute the actual external tuple schema id and store it in the scaffold:

    // Compute the schema id.

    schema_poset_member& lint_tuple_schema = ldof_map.schema();
    scoped_index lactual_tuple_schema_int_id = lint_tuple_schema.index();
    if(lcol_bnd.ub_is_singleton())
    {
      // Actual tuple schema is min of internal and col bound.

      if(lint_tuple_schema.ge(lcol_bnd.ub_id()))
      {
        lactual_tuple_schema_int_id = lcol_bnd.ub_id();
      }
      else
      {
        lactual_tuple_schema_int_id = lint_tuple_schema.index();
      }
    }
    else
    {
      // Actual tuple schema is internal schema.

      lactual_tuple_schema_int_id = lint_tuple_schema.index();
    }

    /// @hack product subposet hack, ver 2.
    /// Not all posets support external ids directly;
    /// let the schema give us a suitable key.

    pod_index_type lactual_tuple_schema_ext_pod =
      lint_tuple_schema.host()->get_ext_id(lactual_tuple_schema_int_id,
                                           scaffold().file_id_space_name(),
                                           false);

    // Map should not already have an entry for lext_pod.

    assertion(scaffold().dof_tuple_schema_ids().find(lext_pod) ==
           scaffold().dof_tuple_schema_ids().end());

    // Insert the actual tuple schema id in the map.

    pair<pod_index_type, pod_index_type>
    lid_pair(lext_pod, lactual_tuple_schema_ext_pod);
    scaffold().dof_tuple_schema_ids().insert(lid_pair);

    // Store the column bounds in the bounds map, if it is not already there.

    scaffold().put_dof_tuple_col_bound(lext_pod);

  } // end while(!_record_queue.is_empty())

  // Flush the cache.

  _hdf_selection_ct = 0;
  for(int i=0; i<_record_buffer_ub; i++)
  {
    if(_record_is_full[i])
    {
      _hdf_int_selection[_hdf_selection_ct][0] = i;
      _hdf_ext_selection[_hdf_selection_ct][0] = _hdf_buf_record_map.external_id(i);
      _hdf_selection_ct++;
      _record_is_full.put(i, false);
    }
  }

  if(_hdf_selection_ct > 0)
  {
    write_selection();
    _hdf_selection_ct = 0;

    _next_record_pod = 0;
  }

  // Adjust the next external id.
  // If this was a partial write and is to be followed by another write,
  // the next write must begin on a new record, otherwise it will overwrite
  // the part of the external record that has already been written with
  // what ever junk is in the first part of the internal record. Advance
  // the next external id to the nearest start of record. Doesn't change
  // anything if already at start of record..

  lext_pod = scaffold().dof_tuple_scratch_id();
  lext_pod = advance_to_start_of_record(lext_pod);
  scaffold().put_dof_tuple_scratch_id(lext_pod);

  // Postconditions:

  ensure(is_open());
  ensure(_hdf_selection_ct == 0);
  ensure(_next_record_pod == 0);
  ensure((scaffold().dof_tuple_scratch_id() % record_size()) == 0);

  // Exit

  return;
}

void
sheaf::dof_tuple_record_set::
externalize_domain(const scoped_index& xtuple_id,
                   const scoped_index& xschema_id)
{
  // Preconditions:

  require(is_open());
  require(scaffold().structure().state_is_read_accessible());
  require(xtuple_id.same_scope(scaffold().dof_tuple_id_space()));

  // Body:

  // This is a write operation

  _writing = true;

  // Initialize the record buffer.

  _hdf_selection_ct = 0;
  reset_record_buffer_ct();

  _next_record_pod = 0;

  // Externalize the domain.

  externalize_one_domain(xtuple_id, xschema_id);

  // Store the schema version in the scaffold; if its not already there.

  if(scaffold().dof_tuple_schema_versions().find(xtuple_id.pod()) ==
     scaffold().dof_tuple_schema_versions().end())
  {
    poset_dof_map& ldof_map = scaffold().structure().row_dof_map(xtuple_id);

    pair<pod_index_type, int> lmap_pair(xtuple_id.pod(),
					ldof_map.schema().version());
    scaffold().dof_tuple_schema_versions().insert(lmap_pair);
  }

  // Store the schema id in the scaffold, if it's not already there.

  if(scaffold().dof_tuple_schema_ids().find(xtuple_id.pod()) ==
      scaffold().dof_tuple_schema_ids().end())
  {
    poset_dof_map& ldof_map = scaffold().structure().row_dof_map(xtuple_id);

    /// @hack product subposet hack, ver 2.
    /// Not all posets support external ids directly;
    /// let the schema give us a suitable key.

    pod_index_type lschema_ext_pod =
      ldof_map.schema().get_ext_id(scaffold().file_id_space_name());

    pair<pod_index_type, pod_index_type>
      lid_pair(xtuple_id.pod(), lschema_ext_pod);
    scaffold().dof_tuple_schema_ids().insert(lid_pair);
  }

  // Store the column bounds in the bounds map, if it is not already there.

  scaffold().put_dof_tuple_col_bound(xtuple_id.pod());

  // Flush the cache.

  _hdf_selection_ct = 0;
  for(int i=0; i<_record_buffer_ub; i++)
  {
    if(_record_is_full[i])
    {
      _hdf_int_selection[_hdf_selection_ct][0] = i;
      _hdf_ext_selection[_hdf_selection_ct][0] = _hdf_buf_record_map.external_id(i);
      _hdf_selection_ct++;
      _record_is_full.put(i, false);
    }
  }

  if(_hdf_selection_ct > 0)
  {
    write_selection();
    _hdf_selection_ct = 0;

    _next_record_pod = 0;
  }

  // Adjust the next external id.
  // If this was a partial write and is to be followed by another write,
  // the next write must begin on a new record, otherwise it will overwrite
  // the part of the external record that has already been written with
  // what ever junk is in the first part of the internal record. Advance
  // the next external id to the nearest start of record. Doesn't change
  // anything if already at start of record..

  pod_index_type lext_pod;
  lext_pod = scaffold().dof_tuple_scratch_id();
  lext_pod = advance_to_start_of_record(lext_pod);
  scaffold().put_dof_tuple_scratch_id(lext_pod);

  // Postconditions:

  ensure(is_open());
  ensure(_hdf_selection_ct == 0);
  ensure(_next_record_pod == 0);
  ensure((scaffold().dof_tuple_scratch_id() % record_size()) == 0);

  // Postconditions:

  // Exit

  return;
}

///
sheaf::size_type
sheaf::dof_tuple_record_set::
record_size() const
{
  size_type result;

  // Preconditions:

  // Body:

  result = _record_size;

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::record_queue&
sheaf::dof_tuple_record_set::
queue()
{
  // Preconditions:

  // Body:

  record_queue& result = _record_queue;

  // Postconditions:

  // Exit

  return result;
}



///
const sheaf::record_queue&
sheaf::dof_tuple_record_set::
queue() const
{
  // Preconditions:

  // Body:

  const record_queue& result = _record_queue;

  // Postconditions:

  // Exit

  return result;
}

sheaf::pod_index_type
sheaf::dof_tuple_record_set::
compute_ext_id(const scoped_index& xtuple_id)
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());
  require(scaffold().structure().contains_row_dof_tuple(xtuple_id));

  // Body:

  // The current scratch id fo the external dof tuple id space is the
  // external id to use.

  interval_index_space_handle& ldof_tuple_space = scaffold().dof_tuple_id_space();
  pod_index_type result = scaffold().dof_tuple_scratch_id();

  // Insert the result into the external dof tuple id space.

  ldof_tuple_space.insert(result, xtuple_id.hub_pod());

  // Compute the next external id.

  pod_index_type lnext_ext_id = result;

  // Get the dof map.

  poset_dof_map& lint_dof_map = scaffold().structure().row_dof_map(xtuple_id);

  schema_poset_member& lint_dof_map_schema = lint_dof_map.schema();

  // Iterate over the domains in the column decomposition,
  // computing a cumulative offset.

  /// @hack Product subposet hack, version 2.
  /// Have to have a schema member to get bound iterator;
  /// use the external schema, it isn't modfied by previous
  /// bounds iterations and should always have the right
  /// fiber component for section space schema.

  index_iterator* lcol_itr =
    scaffold().external_schema().bound_iterator(scaffold().col_bounds(), true);

  while(!lcol_itr->is_done())
  {
    // Get the transfer schema for the current domain.

    attach_transfer_schema(lint_dof_map_schema, lcol_itr->index());

    schema_poset_member& lxfr_schema = scaffold().transfer_schema();

    /// @hack product subposet hack, ver 2.
    /// Not all posets have external ids; let schema give us a pseudo id.

    pod_index_type litem_ext_id =
      lxfr_schema.get_ext_id(scaffold().file_id_space_name());

    // Enter the offset of the current domain into the map.

    poset_scaffold::dof_tuple_domain_offsets_type::key_type
      lkey(result, litem_ext_id);
    poset_scaffold::dof_tuple_domain_offsets_type::value_type lval(lkey, lnext_ext_id);

    scaffold().dof_tuple_domain_offsets().insert(lval);

#ifdef DIAGNOSTIC_OUTPUT
    cout << "dof_tuple_record_set::compute_next_ext_id: offsets:" << endl;
    cout << "xtuple_id= " << xtuple_id
	 << " lcol_itr->item= " << lcol_itr->item()
	 << " litem_ext_id= " << litem_ext_id
	 << " lnext_ext_id= " << lnext_ext_id
	 << endl;
#endif

    // Get the external size of the current domain.

    lnext_ext_id += compute_ext_domain_size(lint_dof_map, lxfr_schema);

    if(!scaffold().col_bounds().ub_is_singleton())
    {
      // Dof tuple is domain decomposed. Domains can not share
      // records or they will over-write each other.
      // Advance the offset to the beginning of the next record.

      lnext_ext_id = advance_to_start_of_record(lnext_ext_id);
    }

    // Move on to the next domain.

    lcol_itr->next();

  } // end while(!lcol_itr->is_done())

  delete lcol_itr;

  // Set the scratch id of the external dof tuple map to the next external id.

  scaffold().put_dof_tuple_scratch_id(lnext_ext_id);

  // Postconditions:

  // Exit

  return result;
}


///
sheaf::size_type
sheaf::dof_tuple_record_set::
compute_ext_domain_size(const poset_dof_map& xdof_map, const schema_poset_member& xfr_schema) const
{
  size_type result = 0;

  // Preconditions:

  // Body:

  result = xfr_schema.ext_data_type_ct(false)*_record_size;

  // Postconditions:

  // Exit

  return result;
}



///
hid_t
sheaf::dof_tuple_record_set::
create_dataset()
{
  hid_t result;

  // Preconditions:

  require(file().mode() == sheaf_file::READ_WRITE);

  // Body:

  // Create an extendible dataspace.

  // Initial guess at dimensions

  /// @hack need sequence ids, not client ids.
  /// The intent is for the external data space to be compact,
  /// that is, sequential starting at 0. We are currently using
  /// client ids as external dof ids and client ids are not in
  /// general compact. So also the comment in externalize.

  /// @issue the following hack refers to code that has been removed,
  /// but the issue remians: what if dof_ct == 0.
  /// @hack if dof_ct == 0, we should just not write the dataset.
  /// But it turns out to be quite complicated to do and
  /// it doesn't occur often enough to be worth the trouble,
  /// so just force an extent of 1.

  // Set initial dataset extent to 1 record;
  // will extend to actual size on first write; see write_selection();

  hsize_t linit_dims[DATASPACE_RANK];
  linit_dims[0] = 1;

  // Maximum dimensions.

  hsize_t lmax_dims[DATASPACE_RANK];
  lmax_dims[0] = H5S_UNLIMITED;

  _ext_dataspace_hdf_id = H5Screate_simple(DATASPACE_RANK, linit_dims, lmax_dims);
  if(_ext_dataspace_hdf_id < 0)
  {
    post_fatal_error_message("can't create data space");
  }

  // We'll need a chunked dataset.
  // Create the chunk dimensions.
  // A chunk is the unit of i/o, make it the same size as the record buffer.

  hsize_t lchunk_dims[DATASPACE_RANK];
  lchunk_dims[0] = _record_buffer_ub;

  // Create the property list for the chunked dataset

  hid_t lparms  = H5Pcreate(H5P_DATASET_CREATE);
  herr_t status = H5Pset_chunk( lparms, DATASPACE_RANK, lchunk_dims);
  if(status < 0)
  {
    post_fatal_error_message("can't set chunk size");
  }

  // Create the dataset with the internal data type.
  // External data type will be set in record_set::open by querying the dataset.

  //  result = H5Dcreate(file().hdf_id(),
  result = H5Dcreate1(file().hdf_id(),
                     name().c_str(),
                     _int_data_type_hdf_id,
                     _ext_dataspace_hdf_id,
                     lparms);
  if(result <0)
  {
    post_fatal_error_message("unable to create dataset.");
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}



///
void
sheaf::dof_tuple_record_set::
read_selection()
{
  // Preconditions:

  require(is_open());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "selection:" << endl;
  cout << setw(6) << "i" << setw(6) << "int" << setw(6) << "ext" << endl;
  for(int i= 0; i<_hdf_selection_ct; i++)
  {
    cout << setw(6) << i
	 << setw(6) << _hdf_int_selection[i][0]
	 << setw(6) << _hdf_ext_selection[i][0]
	 << endl;
  }
  cout << endl;
#endif


  // Set the selection for the internal data space.
  // The following cast is FM taken from HDF source. H5S_point_add immediately
  // casts arg to hsize_t*, which it thinks is pointing at the first element
  // in the array.

  //  const hsize_t** lselect = reinterpret_cast<const hsize_t**>(_hdf_int_selection);
  const hsize_t* lselect = &(_hdf_int_selection[0][0]);
  herr_t status = 
    H5Sselect_elements(_int_dataspace_hdf_id, H5S_SELECT_SET, _hdf_selection_ct, lselect);
  if(status < 0)
  {
    post_fatal_error_message("can't set dof tuple record write selection fro internal dataspace");
  }

  // Set the external selection.
  // The following cast is FM taken from HDF source. H5S_point_add immediately
  // casts arg to hsize_t*, which it thinks is pointing at the first element
  // in the array.

  //  lselect = reinterpret_cast<const hsize_t**>(_hdf_ext_selection);
  lselect = &(_hdf_ext_selection[0][0]);
  status = H5Sselect_elements(_ext_dataspace_hdf_id, H5S_SELECT_SET, _hdf_selection_ct, lselect);
  if(status < 0)
  {
    post_fatal_error_message("can't set dof tuple record read selection");
  }

  // Read the selected records

  status = H5Dread(_hdf_id, _int_data_type_hdf_id, _int_dataspace_hdf_id,
                   _ext_dataspace_hdf_id, H5P_DEFAULT, _hdf_buf);
  if(status < 0)
  {
    post_fatal_error_message("can't read dof tuple record selection");
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "in dof_tuple_record_set::read_selection: buffer is:";
  cout << setbase(16);
  cout << setfill('0');
  for(size_t i=0; i<_hdf_buf_ub; i++)
  {
    if((i % _record_size) == 0)
    {
      cout << endl;
    }
    cout << setw(2) << int(reinterpret_cast<unsigned char*>(_hdf_buf)[i]) << " ";
  }
  cout << endl << endl;
  cout << setbase(10) << setfill(' ');
#endif

  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::dof_tuple_record_set::
write_selection()
{
  // Preconditions:

  require(is_open());
  require(_hdf_selection_ct > 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "writing poset: " << scaffold().structure().name() << "  int_selection:" << endl;
  for(int i= 0; i<_hdf_selection_ct; i++)
  {
    cout << i << " " << _hdf_int_selection[i][0] << endl;
  }
  cout << endl;
#endif

  // Set the selection for the internal data space.
  // The following cast is FM taken from HDF source. H5S_point_add immediately
  // casts arg to hsize_t*, which it thinks is pointing at the first element
  // in the array.

  //  const hsize_t** lselect = reinterpret_cast<const hsize_t**>(_hdf_int_selection);
  const hsize_t* lselect = &(_hdf_int_selection[0][0]);
  herr_t status = H5Sselect_elements(_int_dataspace_hdf_id, H5S_SELECT_SET, _hdf_selection_ct, lselect);
  if(status < 0)
  {
    post_fatal_error_message("can't set dof tuple record write selection for internal dataspace");
  }

  // Extend the dataset to include the external selection.

  /// @issue if writing to existing dataset, don't always need to extend selection.

#ifdef DIAGNOSTIC_OUTPUT
  cout << "dataspace extent:";
  for(int i=0; i<ext_dataspace_rank(); i++)
  {
    cout << " " << _ext_dataspace_dims[i];
  }
  cout << endl;
#endif

  // Get size of dofs currently queued for output.

  size_t lq_size = scaffold().dof_tuple_scratch_id();

  // Find record number that contains lq_size.

  hsize_t ldims[DATASPACE_RANK];
  ldims[0] = ((lq_size + _record_size - 1)/_record_size);

  // Extend the data set.

  extend_dataset(ldims, DATASPACE_RANK);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "ext_selection:" << endl;
  for(int i= 0; i<_hdf_selection_ct; i++)
  {
    cout << i << " " << _hdf_ext_selection[i][0] << endl;
  }
  cout << endl;
#endif

  // Set the external selection.
  // The following cast is FM taken from HDF source. H5S_point_add immediately
  // casts arg to hsize_t*, which it thinks is pointing at the first element
  // in the array.

  //  lselect = reinterpret_cast<const hsize_t**>(_hdf_ext_selection);
  lselect = &(_hdf_ext_selection[0][0]);
  status = H5Sselect_elements(_ext_dataspace_hdf_id, H5S_SELECT_SET, _hdf_selection_ct, lselect);
  if(status < 0)
  {
    post_fatal_error_message("can't set dof tuple record write selection");
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "in dof_tuple_record_set::write_selection: buffer is:";
  cout << setbase(16);
  cout << setfill('0');
  for(size_t i=0; i<_hdf_buf_ub; i++)
  {
    if((i % _record_size) == 0)
    {
      cout << endl;
    }
    cout << setw(2) << int(reinterpret_cast<unsigned char*>(_hdf_buf)[i]) << " ";
  }
  cout << endl << endl;
  cout << setbase(10) << setfill(' ');
#endif

  // Write the selected records

  status = H5Dwrite(_hdf_id, _int_data_type_hdf_id, _int_dataspace_hdf_id,
                    _ext_dataspace_hdf_id, H5P_DEFAULT, _hdf_buf);
  if(status < 0)
  {
    post_fatal_error_message("can't write dof tuple record selection");
  }

  // Postconditions:

  // Exit

  return;
}


// PROTECTED MEMBER FUNCTIONS

void
sheaf::dof_tuple_record_set::
schematize()
{
  // Preconditions:

  // Body:

  // Attach the dof subposet handles in the poset.

  poset_state_handle& lposet = scaffold().structure();

  string ltable_dof_sp_name = schema_poset_member::table_dof_subposet_name("top");
  if(lposet.includes_subposet(ltable_dof_sp_name))
  {
    lposet.table_dof_subposet().attach_to_state(&lposet, ltable_dof_sp_name);

    if(!lposet.table_dof_subposet().has_id_space())
    {
      lposet.initialize_dof_id_space(lposet.table_dof_subposet());
    }
    
  }

  string lrow_dof_sp_name = schema_poset_member::row_dof_subposet_name("top");
  if(lposet.includes_subposet(lrow_dof_sp_name))
  {
    lposet.row_dof_subposet().attach_to_state(&lposet, lrow_dof_sp_name);

    if(!lposet.row_dof_subposet().has_id_space())
    {
      lposet.initialize_dof_id_space(lposet.row_dof_subposet());
    }
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::dof_tuple_record_set::
externalize_all_dofs(schema_poset_member& xxfr_schema,
                     const poset_dof_map& xint_dof_map,
                     char*& xbuf,
                     size_t& xbuf_remainder)
{
  // Preconditions:

  require(xbuf_remainder == _record_size); // The tranparency hack.

  // Body:

  //  char* lbuf = const_cast<char*&>(xbuf);
  char* lbuf = xbuf;
  int ldof_tuple_type;
  int lrecord_dof_index = 0;
  dof_descriptor_array& ldof_descriptors = *xxfr_schema.ext_data_type_schema().dof_descriptors(false);


  if(xint_dof_map.supports_xfr_opt() &&
      xxfr_schema.is_same_state(&xint_dof_map.schema()) &&
      (xxfr_schema.version() == xint_dof_map.schema().version()) &&
      is_primitive_index(ldof_tuple_type = xxfr_schema.row_dof_tuple_type()))
  {
    // Section dof tuple and same schema and version and homogeneous dof tuple.
    // Don't need to gather/scatter, more efficient to just iterate over sequence id.

    // post_information_message("iterating over sequence id");

    data_converter* dc = type_map()[ldof_tuple_type];

    bool lis_nrmi_type = dc->is_namespace_relative_member_index_type();
    bool lis_nrsi_type = dc->is_namespace_relative_subposet_index_type();
    bool lid_needs_conversion = lis_nrmi_type || lis_nrsi_type;

    int ldof_ct = xxfr_schema.row_dof_ct();


    for(int i=0; i<ldof_ct; ++i)
    {
      if(xbuf_remainder == 0)
      {
        lbuf = get_next_record(xbuf);
        lrecord_dof_index = 0;
        xbuf = lbuf;
        xbuf_remainder = _record_size;
      }

      // Gather the dof to the hdf buffer.

      xint_dof_map.get_dof(i, xbuf, xbuf_remainder);

      if(lid_needs_conversion)
      {
        // This is a namespace relative index type;
        // need to convert internal id to external id.

        if(lis_nrmi_type)
        {
          // This is a member index type.

          scaffold().convert_member_id_to_record_id(xbuf);
        }
        else
        {
          // Must be a subposet index type.

          scaffold().convert_subposet_id_to_record_id(xbuf);
        }
      }

      // Move on to the next dof.

      ++lrecord_dof_index;
      size_t loffset = ldof_descriptors[lrecord_dof_index].offset;
      xbuf  = lbuf + loffset;
      xbuf_remainder = _record_size - loffset;
    }

  }
  else
  {
    // Different schema or version or inhomogeneous dof tuple;
    // use iterator to gather/scatter.

    // post_information_message("iterating over schema");

    poset_dof_iterator* lxfr_itr = xxfr_schema.row_dof_iterator();
    while(!lxfr_itr->is_done())
    {
      if(xbuf_remainder == 0)
      {
        lbuf = get_next_record(xbuf);
        lrecord_dof_index = 0;
        xbuf = lbuf;
        xbuf_remainder = _record_size;
      }

#ifdef DIAGNOSTIC_OUTPUT
      cout << "dof: " << lxfr_itr->item().name();
      cout << "  xbuf: " << static_cast<void*>(xbuf)
      << "  xbuf_remainder: " << xbuf_remainder
      << endl;
#endif

      // Gather dof to the hdf buffer.

      xint_dof_map.get_dof(lxfr_itr->index(), xbuf, xbuf_remainder);

      // If this is a namespace relative index type;
      // need to convert internal id to external id.

      data_converter* dc = type_map()[lxfr_itr->item().type()];
      if(dc->is_namespace_relative_member_index_type())
      {
        scaffold().convert_member_id_to_record_id(xbuf);
      }
      else if(dc->is_namespace_relative_subposet_index_type())
      {
        scaffold().convert_subposet_id_to_record_id(xbuf);
      }

      // Move on to the next dof.

      ++lrecord_dof_index;
      size_t loffset = ldof_descriptors[lrecord_dof_index].offset;
       xbuf  = lbuf + loffset;
      xbuf_remainder = _record_size - loffset;

      lxfr_itr->next();
    }
    delete lxfr_itr;
  }


  // Postconditions:


  // Exit:

  return;
}


///
void
sheaf::dof_tuple_record_set::
internalize_all_dofs(schema_poset_member& xxfr_schema,
                     poset_dof_map& xext_dof_map,
                     char* xbuf,
                     size_t xbuf_remainder)
{
  // Preconditions:

  require(xbuf_remainder == _record_size); // The tranparency hack.

  // Body:

  char* lbuf = xbuf;
  int ldof_tuple_type;
  int lrecord_dof_index = 0;
  dof_descriptor_array& ldof_descriptors = *xxfr_schema.ext_data_type_schema().dof_descriptors(false);

  if(xext_dof_map.supports_xfr_opt() &&
      xxfr_schema.is_same_state(&xext_dof_map.schema()) &&
      (xxfr_schema.version() == xext_dof_map.schema().version()) &&
      is_primitive_index(ldof_tuple_type = xxfr_schema.row_dof_tuple_type()))
  {
    // Section dof tuple and same schema and version and homogeneous dof tuple.
    // Don't need to gather/scatter, more efficient to just iterate over sequence id.


#ifdef DIAGNOSTIC_OUTPUT
    post_information_message("iterating over sequence id");
    primitive_value lprim(primitive_value::prototype(ldof_tuple_type));
#endif

    data_converter* dc = type_map()[ldof_tuple_type];
    int ldof_ct = xxfr_schema.row_dof_ct();


    for(pod_index_type i=0; i<ldof_ct; ++i)
    {
      if(xbuf_remainder == 0)
      {
        lbuf = get_next_record(xbuf);
        lrecord_dof_index = 0;
        xbuf = lbuf;
        xbuf_remainder = _record_size;
      }

      // Convert internal id to external id, if needed.

      if(dc->is_namespace_relative_member_index_type())
      {
        scaffold().convert_record_id_to_member_id(xbuf);
      }
      else if(dc->is_namespace_relative_subposet_index_type())
      {
        scaffold().convert_record_id_to_subposet_id(xbuf);
      }

      // Copy the dof into the dof tuple.

      xext_dof_map.put_dof(i, xbuf, xbuf_remainder);

#ifdef DIAGNOSTIC_OUTPUT
      lprim.value() = *reinterpret_cast<primitive_buffer_type*>(xbuf);
      cout << "   " << lprim.to_string();
#endif

      // Move on to the next dof.

      ++lrecord_dof_index;
      size_t loffset = ldof_descriptors[lrecord_dof_index].offset;
      xbuf  = lbuf + loffset;
      xbuf_remainder = _record_size - loffset;
    }

#ifdef DIAGNOSTIC_OUTPUT
      cout << endl;
#endif

  }
  else
  {
    // Different schema or version or inhomogeneous dof tuple;
    // use iterator to gather/scatter.

#ifdef DIAGNOSTIC_OUTPUT
    post_information_message("iterating over schema");
#endif

    poset_dof_iterator* xfr_itr =
      xxfr_schema.row_dof_iterator(xext_dof_map.version());

    while(!xfr_itr->is_done())
    {
      if(xbuf_remainder == 0)
      {
        lbuf = get_next_record(xbuf);
        lrecord_dof_index = 0;
        xbuf = lbuf;
        xbuf_remainder = _record_size;
      }

      // Convert internal id to external id, if needed.

      data_converter* dc = type_map()[xfr_itr->item().type()];
      if(dc->is_namespace_relative_member_index_type())
      {
        scaffold().convert_record_id_to_member_id(xbuf);
      }
      else if(dc->is_namespace_relative_subposet_index_type())
      {
        scaffold().convert_record_id_to_subposet_id(xbuf);
      }

      // Copy the dof into the dof tuple.

      xext_dof_map.put_dof(xfr_itr->index(), xbuf, xbuf_remainder);
      
#ifdef DIAGNOSTIC_OUTPUT
      primitive_value lprim(xfr_itr->item().type(), xbuf);
      cout << "   " << lprim.to_string();
#endif

      // Move on to the next dof.

      ++lrecord_dof_index;
      size_t loffset = ldof_descriptors[lrecord_dof_index].offset;
      xbuf  = lbuf + loffset;
      xbuf_remainder = _record_size - loffset;
      xfr_itr->next();
    }
    delete xfr_itr;

#ifdef DIAGNOSTIC_OUTPUT
      cout << endl;
#endif
  }


  // Postconditions:


  // Exit:

  return;
}

///
void
sheaf::dof_tuple_record_set::
populate_internal_dof_map(const poset_dof_map& xext_dof_map, poset_dof_map& xint_dof_map)
{
  // Preconditions:


  // Body:

  /// @hack sparse_field_dof_map doesn't currently support dof_tuple function.

  if(xext_dof_map.supports_xfr_opt() &&
      xint_dof_map.schema().is_same_state(&xext_dof_map.schema()) &&
      (xint_dof_map.schema().version() == xext_dof_map.schema().version()))
  {
    // Section dof tuple amd same schema and version;
    // don't need to gather/scatter, more efficient to just copy

    // post_information_message("copying dof tuple");

    xint_dof_map.put_dof_tuple(xext_dof_map.dof_tuple(), xext_dof_map.dof_tuple_ub());
  }
  else
  {
    // Different schema or version or sparse_field_dof_map;
    // use iterator to gather/scatter.

    // post_information_message("iterating over schema");

    poset_dof_iterator* lint_dof_itr = xint_dof_map.schema().row_dof_iterator();
    while(!lint_dof_itr->is_done())
    {
      primitive_buffer_type pbuf;
      scoped_index ldof_id = lint_dof_itr->index();

      xext_dof_map.get_dof(ldof_id, &pbuf, sizeof(pbuf));
      xint_dof_map.put_dof(ldof_id, &pbuf, sizeof(pbuf));

      lint_dof_itr->next();
    }
    delete lint_dof_itr;
  }

  // Postconditions:


  // Exit:

  return;
}


///
char*
sheaf::dof_tuple_record_set::
get_next_record(char* xbuf)
{
  char* result;

  // Preconditions:

  // This routine doesn't deal with initial case xbuf == _hdf_buf.

  require(_hdf_buf < xbuf);
  require(xbuf <= (_hdf_buf + _hdf_buf_ub));
  require( ((xbuf - _hdf_buf) % _record_size) == 0 );

  // Body:

  // This routine gets called when a buffer record has been used up;
  // xbuf is always pointing 1 byte past the end of the current record.

  int lcur_int_rec_id = (xbuf - 1 - _hdf_buf)/_record_size;

  // Translate the internal buffer pointer to an external record id.

  int lcur_ext_rec_id = _hdf_buf_record_map.external_id(lcur_int_rec_id);

  // Because a dof tuple is written into contiguous storage in the dataset,
  // the record we want is the next external record.

  int lnext_ext_rec_id = lcur_ext_rec_id + 1;

  // Get the internal id of the record;
  // brings the record into the buffer if it is not already there.

  int lnext_int_rec_id = get_internal_record(lnext_ext_rec_id);

  // Now the record is in memory and we have its internal id.

  result = _hdf_buf + lnext_int_rec_id*_record_size;

  // Postconditions:

  ensure(result >= _hdf_buf);
  ensure(result < (_hdf_buf + _hdf_buf_ub));
  require( ((result - _hdf_buf) % _record_size) == 0 );

  // Exit

  return result;
}


///
char*
sheaf::dof_tuple_record_set::
get_first_record(pod_index_type xext_pod)
{
  char* result;

  // Preconditions:

  // Body:

  // Translate the external dataset offset to an external record id.

  pod_index_type lext_rec_pod = xext_pod/_record_size;
  size_t lrec_rel_offset = xext_pod % _record_size;

  // Get the internal id of the record;
  // brings the record into the buffer if it is not already there.

  pod_index_type lint_rec_pod = get_internal_record(lext_rec_pod);

  // Now record is in memory and we have its internal id.

  result = _hdf_buf + lint_rec_pod*_record_size + lrec_rel_offset;

  // Postconditions:

  ensure(result >= _hdf_buf);
  ensure(result < _hdf_buf + _hdf_buf_ub);

  // Exit

  return result;
}

///
sheaf::pod_index_type
sheaf::dof_tuple_record_set::
get_internal_record(pod_index_type xext_rec_pod)
{
  pod_index_type result;

  // Preconditions:

  // Body:

  // Translate external record id to internal record id, if it exists.

  pod_index_type lint_rec_pod = _hdf_buf_record_map.internal_id(xext_rec_pod);

  if(!is_valid(lint_rec_pod))
  {
    // Record is not in memory; deal with it.

    /// @issue cache maintenance policy.
    /// Policy used here is that _next_record_pod repeatedly cycles
    /// through records in the cache. Since we should be accessing
    /// the records mostly sequentially, this policy is a crude
    /// approximation to least-recently-used.

    lint_rec_pod = _next_record_pod;
    ++_next_record_pod;
    pod_index_type lpod = _next_record_pod % _record_buffer_ub;
    _next_record_pod = lpod;

    if(_writing)
    {
      // This is a write operation.

      if(_record_is_full[lint_rec_pod])
      {
        // Internal record is full; write it out.

        // Get the external id of internal record;
        // must be in the record buffer index map

        assertion(_hdf_buf_record_map.contains_internal_id(lint_rec_pod));
        pod_index_type lext_rec_pod =
	  _hdf_buf_record_map.external_id(lint_rec_pod);

        _hdf_int_selection[0][0] = lint_rec_pod;
        _hdf_ext_selection[0][0] = lext_rec_pod;
        _hdf_selection_ct = 1;

        write_selection();

        _hdf_selection_ct = 0;
      }
    }
    else
    {
      // This is a read operation.

      _hdf_int_selection[0][0] = lint_rec_pod;
      _hdf_ext_selection[0][0] = xext_rec_pod;
      _hdf_selection_ct = 1;

      read_selection();

      _hdf_selection_ct = 0;
    }

    // Update the record buffer index map.

    _hdf_buf_record_map.remove_internal_id(lint_rec_pod);
    _hdf_buf_record_map.put_ids(lint_rec_pod, xext_rec_pod);

    // Internal record is now either full or allocated to be filled;
    // mark it as full.

    _record_is_full.put(lint_rec_pod, true);
  }

  // Now record is in memory and we have its internal id.

  result = lint_rec_pod;

  // Postconditions:

  ensure(result >= 0);
  ensure(result < record_buffer_ub());

  // Exit

  return result;
}


///
sheaf::pod_index_type
sheaf::dof_tuple_record_set::
advance_to_start_of_record(pod_index_type xoffset)
{
  return ((xoffset + _record_size - 1)/_record_size)*_record_size;
}

void
sheaf::dof_tuple_record_set::
externalize_one_domain(const scoped_index& xtuple_id,
                       const scoped_index& xschema_id)
{
  // Preconditions:

  require(is_open());
  require(scaffold().structure().state_is_read_accessible());
  require(xtuple_id.same_scope(scaffold().dof_tuple_id_space()));

  // Body:

  // Get the dof map.

  poset_dof_map& lint_dof_map = scaffold().structure().row_dof_map(xtuple_id);
  schema_poset_member& lint_dof_map_schema = lint_dof_map.schema();

  // Set the transfer schema for this domain.

  attach_transfer_schema(lint_dof_map_schema, xschema_id);
  schema_poset_member& lxfr_schema = scaffold().transfer_schema();

  // Get the external id for the transfer schema.

  /// @hack the product subposet hack, ver 2.
  /// Not all posets have external ids; let the schema give us a pseudo-id.

  pod_index_type lxfr_schema_ext_pod =
    lxfr_schema.get_ext_id(scaffold().file_id_space_name());

  // Get the offset for this domain.

  poset_scaffold::dof_tuple_domain_offsets_type::key_type
    lkey(xtuple_id.pod(), lxfr_schema_ext_pod);
  poset_scaffold::dof_tuple_domain_offsets_type::iterator loffsets_itr =
    scaffold().dof_tuple_domain_offsets().find(lkey);

  assertion(loffsets_itr != scaffold().dof_tuple_domain_offsets().end());

  pod_index_type ldom_ext_pod = loffsets_itr->second;

  // Get a pointer to the corresponding location in the record buffer.

  char* lbuf = get_first_record(ldom_ext_pod);
  size_t lbuf_remainder =
    _record_size - (static_cast<size_t>(ldom_ext_pod) % _record_size);

  assertion(lbuf_remainder == _record_size); // The transparency hack.

  // Externalize all the dofs in the domain.

  externalize_all_dofs(lxfr_schema, lint_dof_map, lbuf, lbuf_remainder);

  // Just to be tidy, clear the remainder of the record.

  for(size_t i=0; i<lbuf_remainder; i++)
  {
    *lbuf++ = 0;
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::dof_tuple_record_set::
attach_transfer_schema(schema_poset_member& xdof_map_schema,
                       const scoped_index& xdomain_schema_id)
{
  // Preconditions:

  require(scaffold().transfer_schema().is_attached());

  // Body:

  // The transfer schema should be the lesser of the
  // domain schema and the dof map schema and
  // use the same version as the dof map.

  schema_poset_member& lxfr_schema = scaffold().transfer_schema();
  if(xdof_map_schema.le(xdomain_schema_id))
  {
    lxfr_schema.attach_to_state(xdof_map_schema.index());
  }
  else
  {
    lxfr_schema.attach_to_state(xdomain_schema_id);
  }
  lxfr_schema.put_version(xdof_map_schema.version());

  // Postconditions:

  // Exit:

  return;
}

///
void
sheaf::dof_tuple_record_set::
create_int_data_type()
{
  // Preconditions:

  require(file().is_open());

  // Body:

  // The io system attempts to use the sheaf table metaphor to map the
  // dof tuples to a file structure. For simple cases, this leads one
  // to think of the dof tuple data set as a table, i.e. a single index
  // array of records, which the record type defined by the dof tuple schema.
  // The record type would be implemented by an HDF compund type with one
  // data member for each dof defined by the schema.
  // For ordinary posets we can us this simple approach, but two issues
  // spoil this simple picture for section spaces:
  //
  // 1) A typical section schema would contain 1000's of data members,
  //    which would likely break the compound data type mechanism,
  //    or at least be very inefficient.
  // 2) We want to support partial sections, which means the
  //    record type would be different for different records.
  //
  // So for section spaces we need some smaller data type that can serve
  // as a least common denominator for partial sections. A suitable candidate
  // is the fiber schema. Currently we only support partial sections as
  // restrictions of the base space, so all sections, partial or total,
  // share the same fiber schema.
  //
  // So for ordinary posets the record type is the defined by the schema
  // and for section spaces the record type is defined by the fiber schema.
  // This polymorphism is encapsulated by the virtual function
  // schema_poset_member::ext_data_type_dof_iterator().
  //
  // One further optimization is possible, for either ordinary posets or
  // section spaces. If all the dofs are the same primitive type, then
  // we can use that type as the record type and dispense with the
  // compound data type altogether.
  //
  // Note that the HDF type for character strings is H5T_C_S1 with
  // H5T_VARIABLE set. Using this type, we can treat strings almost
  // as if they were fixed length types, except for garbage collection.
  // See file_data_type_map::create_internal_hdf_types()

  schema_poset_member& ldt_schema =
    scaffold().external_schema().ext_data_type_schema();
  int ldof_tuple_type = ldt_schema.row_dof_tuple_type();

  if(is_primitive_index(ldof_tuple_type))
  {
    // The dof tuple is homogeneous.

    size_t lrecord_dof_ct = ldt_schema.row_dof_ct();

    if(lrecord_dof_ct == 1)
    {
      // Single dof per record, can use predefined type.
      // Copy the type so we can handle all types the same in record_set::close().

      _int_data_type_hdf_id = H5Tcopy(type_map()[ldof_tuple_type]->internal_type());
      if(_int_data_type_hdf_id < 0)
      {
        post_fatal_error_message("Can't create internal data type");
      }
    }
    else
    {
      // Multiple dofs per record, but all same type; use array type.

      hsize_t larray_dims = lrecord_dof_ct;
      _int_data_type_hdf_id =
	//        H5Tarray_create(type_map()[ldof_tuple_type]->internal_type(),
        H5Tarray_create1(type_map()[ldof_tuple_type]->internal_type(),
                        1,
                        &larray_dims,
                        NULL);
      if(_int_data_type_hdf_id < 0)
      {
        post_fatal_error_message("Can't create internal data type");
      }
    }
  }
  else
  {
    // The dof tuple is inhomogeneous; need to construct a compound type.

    // Note that this data type is used to describe the internal memory layout
    // of the record buffer. On write, this same data type is used for the
    // layout on disk, so the internal and external are the same.
    // But on read, the external data type is whatever is in the file,
    // which may have been written on some other hw platform and hence may
    // be different than the internal laayout. HDF will do the translation.

    poset_dof_iterator* ldof_itr = ldt_schema.row_dof_iterator();

    dof_descriptor_array& ldof_descriptors = *ldt_schema.dof_descriptors(false);
    ldof_descriptors.add_reference();

    size_t ldt_size = ldt_schema.row_dof_tuple_ub();

    // Create a transient compound data type;
    // no need to share the data type, so it doesn't have to be named.

    _int_data_type_hdf_id = H5Tcreate(H5T_COMPOUND, ldt_size);
    if(_int_data_type_hdf_id < 0)
    {
      post_fatal_error_message("Can't create internal data type");
    }

    size_t lseq_id = 0;
    while(!ldof_itr->is_done())
    {
      dof_descriptor_array::dof_descriptor ldesc = ldof_descriptors[lseq_id];
      data_converter* ldof_dc = type_map()[ldesc.type];

      string ldof_name = ldof_itr->item().name();
      size_t loffset   = ldesc.offset;
      hid_t lhdf_type  = ldof_dc->internal_type();

#ifdef DIAGNOSTIC_OUTPUT
      cout << "create_int_data_type: "
      << "  dof_name: " << ldof_name
      << "  offset: " << loffset
      << endl;
#endif

      herr_t lstatus =
        H5Tinsert(_int_data_type_hdf_id, ldof_name.c_str(), loffset, lhdf_type);
      if(lstatus <0)
      {
        post_fatal_error_message("Unable to insert member in HDF5 compound data type.");
      }

      ldof_itr->next();
      ++lseq_id;
    }

    // Clean up.

    ldof_descriptors.remove_reference();
    delete ldof_itr;
  }

  // Set the record size.

  _record_size = H5Tget_size(_int_data_type_hdf_id);

  // Postconditions:

  ensure(int_data_type_hdf_id() >= 0);

  // Exit:

  return;
}
