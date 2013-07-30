
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Implementation for class member_record_set

#include "member_record_set.h"

#include "assert_contract.h"
#include "biorder_itr.h"
#include "data_converter.h"
#include "error_message.h"
#include "implicit_crg_interval.h"
#include "index_space_iterator.h"
#include "interval_index_space_state.h"
#include "preorder_itr.h"
#include "sheaf_file.h"
#include "std_hash_set.h"
#include "std_string.h"
#include "std_strstream.h"
#include "std_iostream.h"
#include "std_strstream.h"

//#define DIAGNOSTIC_OUTPUT
// #undef DIAGNOSTIC_OUTPUT

namespace
{
  //
  // The rank of the dataspace for the data set.
  //
  const int DATASPACE_RANK = 1;
}

  

// =============================================================================
// ANY FACET
// =============================================================================

///
sheaf::member_record_set*
sheaf::member_record_set::
clone() const
{
  member_record_set* result;

  // Preconditions:

  // Body:

  result = new member_record_set(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
bool
sheaf::member_record_set::
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

    result = result && (is_open() ? _ext_dataspace_rank == DATASPACE_RANK : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::member_record_set::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const member_record_set*>(other) != 0;

  // Postconditions:

  return result;

}


// =============================================================================
// MEMBER_RECORD_SET FACET
// =============================================================================

///
sheaf::member_record_set::
member_record_set(const sheaf_file& xfile,
                  int xrecord_buffer_ub,
                  const poset_scaffold& xscaffold,
                  const dof_tuple_record_set& xdof_tuple_records)
  : record_set(xfile, xrecord_buffer_ub, xscaffold),
    _record(*this),
    _scaffold(const_cast<poset_scaffold&>(xscaffold)),
    _dof_tuple_records(const_cast<dof_tuple_record_set&>(xdof_tuple_records)),
    _id_space_record(*this)
{

  // Preconditions:

  require(xfile.is_open());
  require(xrecord_buffer_ub > 0);
  require(scaffold().structure().state_is_read_accessible());

  // Body:

  _record_id_space.attach_to(xscaffold.member_id_space());

  // Construct the interval id space.

  poset_state_handle& lposet = _scaffold.structure();

  strstream linterval_id_space_str;
  linterval_id_space_str << _record_id_space.name() << "_interval";
  linterval_id_space_str >> _interval_id_space_name;

  arg_list largs = interval_index_space_state::make_arg_list(true);

  pod_index_type lid =
    lposet.member_id_spaces(false).new_secondary_state(_interval_id_space_name,
						       "interval_index_space_state",
						       largs,
						       false);

  _interval_id_space.attach_to(lposet.member_id_spaces(false), lid);
  _interval_id_space.put_merge_mode(false);

  // _name has been initialized to poset name in record_set;
  // add members dataset suffix to it.

  _name  += ".members";
  _alias += ".members";

  _ext_dataspace_rank = DATASPACE_RANK;
  _ext_dataspace_dims = new hsize_t[DATASPACE_RANK];

  // Create and initialize the HDF record buffer

  _hdf_bufs = new hvl_t[record_buffer_ub()];
  for(size_t i=0; i<record_buffer_ub(); i++)
  {
    hvl_t* ltmp = _hdf_bufs+i;
    ltmp->p = 0;
    ltmp->len = 0;
  }

  // Create the selection buffer

  _hdf_selection  = new hsize_t[record_buffer_ub()][DATASPACE_RANK];

  // Postconditions:

  ensure(invariant());
  ensure(name() == xscaffold.structure().name() + ".members");
  ensure(!is_open());
  ensure(record_buffer_ub() == xrecord_buffer_ub);
  ensure(record_buffer_is_empty());
}

///
sheaf::member_record_set::
member_record_set(const member_record_set& xother)
    : record_set(xother),
      _record(xother._record),
      _scaffold(xother._scaffold),
      _dof_tuple_records(xother._dof_tuple_records),
      _id_space_record(xother._id_space_record),
      _record_id_space(xother._record_id_space),
      _interval_id_space_name(xother._interval_id_space_name),
      _interval_id_space(xother._interval_id_space)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}

///
sheaf::member_record_set::
~member_record_set()
{
  // Preconditions:

  // Body:

  delete [] _ext_dataspace_dims;
  delete [] _hdf_selection;
  delete [] _hdf_bufs;

  /// @hack storage_agent::begin_read_transation() releases access to the
  /// poset.  When the member_record_set local variable goes out of scope
  /// it no longer has access. Read access is only needed because writing
  /// a poset forces delete_member_id_space to only require read access
  /// when it should require read-write access.

  _scaffold.structure().get_read_access();
  _scaffold.structure().member_id_spaces(false).delete_secondary_state(_interval_id_space_name);
  _scaffold.structure().release_access();

  // Postconditions:

  // Exit:

  return;
}

///
void
sheaf::member_record_set::
internalize(pod_index_type xmax_row_int_id)
{

  // Preconditions:

  require(is_open());
  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << endl << "member_record_set::internalize: internalizing record set " << name() << endl;
#endif

  poset_state_handle& lposet = scaffold().structure();

  // Initialize the dof tuple id id space.

  _scaffold.initialize_dof_tuple_id_space();

  // Read the file id and interval id spaces.

  read_id_space_record(_record_id_space, record_id_space_record());
  read_id_space_record(_interval_id_space, interval_id_space_record());

  // Allocate ids in file scope and internal scope.

  record_index lext_id(_record_id_space);
  scoped_index linterval_id(lposet.member_id(false));

  // Get a handle to the max row member.

  abstract_poset_member& lmax_row_mbr = *lposet.top().clone();
  lmax_row_mbr.attach_to_state(&lposet, xmax_row_int_id);

  // Get a handle to the resident subposet.

  subposet& lresident_sp = scaffold().resident();

  // Put the poset in jim edit mode.

  lposet.begin_jim_edit_mode(false);

  // The size of the upper cover of bottom == #atoms == O(#jims)
  // and hence can be quite large. For efficiency we never write 
  // it to the file and reconstruct it when we read the file,
  // see member_record::transfer_lower_cover_to_member.
  // Remove any existing links so we won't have duplicates.

  lposet.bottom().clear_cover(UPPER);

  // Traverse the down-set of the poset in depth-first preorder,
  // internalizing and building the lower cover in front of the traversal.

  // $$SCRIBBLE: implicit-cover-reorganization
  // Only read interval members.

//   typedef set_preorder_itr itr_type;

//   itr_type litr(lmax_row_mbr, DOWN, NOT_STRICT);
//   while(!litr.is_done())
//   {

// #ifdef DIAGNOSTIC_OUTPUT
//     cout << "member_record_set::internalize: internalizing member: " << litr.index() 
// 	 << "  is_resident= " << boolalpha << lresident_sp.contains_member(litr.index()) << noboolalpha
// 	 << endl;
// #endif

//     if(!lresident_sp.contains_member(litr.index()))
//     {
//       // Lower cover of the member is still external.

//       // $$SCRIBBLE: what is the proper condition here?
//       // We need to be able to treat a interval as a jrm with its implicit down set
//       // or as a non-resident jim, without a down set. See the truncation and
//       // link handling logic in member_record::transfer_internal_buffer_to_member.

//       //     if(lposet.is_jrm(xmbr_id) && lposet.is_atom(xmbr_id))
//       //     {
//       //       // Member has been temporarily linked to the bottom,
//       //       // delete the link.

//       ///       /// @issue this could be an expensive operation.
//       ///       /// The upper cover of bottom can get very large and
//       ///       /// with the list rep for list_cover_set, delete
//       ///       /// requires a linear search of the cover set .

//       ///       /// @todo optimize the upper cover of bottom.

//       //       lposet.delete_link(xmbr_id, BOTTOM_INDEX);
//       //     }
      
//       if(must_read_interval_member(litr.index(), linterval_id))
//       {
// 	read_member(linterval_id, lext_id);
//       }  
      
//       read_member(litr.index(), lext_id);

//     } // end if not resident

//     litr.next();
//   } // end down set iteration

  typedef set_preorder_itr itr_type;

  itr_type litr(lmax_row_mbr, DOWN, NOT_STRICT);

  scoped_index lmbr_id(lmax_row_mbr.hub_id());

  while(!litr.is_done())
  {

#ifdef DIAGNOSTIC_OUTPUT
    cout << "member_record_set::internalize: internalizing member: " << litr.index() 
	 << "  is_resident= " << boolalpha << lresident_sp.contains_member(litr.index()) << noboolalpha
	 << endl;
#endif

    pod_index_type lhub_pod = litr.index().hub_pod();
    pod_index_type linterval_begin = _interval_id_space.interval_begin(lhub_pod);

    if(!lresident_sp.contains_member(lhub_pod))
    {
      // Lower cover of the member is still external.

      if(is_valid(linterval_begin))
      {
	// Member is implicit.

	if(lhub_pod == linterval_begin)
	{
	  // The member is the interval member, read it.

	  read_member(litr.index(), lext_id);

	  // Read explicit members in the down set of the interval.

	  set<pod_index_type> ldown_set;
	  implicit_crg_interval* linterval = lmax_row_mbr.host()->crg().implicit_member(lhub_pod);
	  lmax_row_mbr.host()->crg().explicit_down_set_members(*linterval, ldown_set);

	  set<pod_index_type>::const_iterator litr;
	  for(litr = ldown_set.begin(); litr != ldown_set.end(); ++litr)
	  {
	    if(!lresident_sp.contains_member(*litr) == 0)
	    {
	      // The explicit member has not been read, read it.

	      lmbr_id = *litr;

	      read_member(lmbr_id, lext_id);
	    }
	  }
	}
	else
	{
	  // Do not read members that are not the interval member.
	}

	// Do not iterate the downset of a interval.

	litr.truncate();
      }
      else
      {
	// Member is explicit, read it and continue.

	read_member(litr.index(), lext_id);

	litr.next();
      }
    }
    else
    {
      // The member has already been read.

      if(is_valid(linterval_begin))
      {
	// Do not iterate the downset of a interval.

	litr.truncate();
      }
      else
      {
	// Continue iterating.

	litr.next();
      }
    }
  } // end down set iteration

  // Clean up the upper covers.

  clean_upper_covers();

  // Finished with edit mode.

  lposet.end_jim_edit_mode(true, false);

  // Postconditions:

  ensure(is_open());

  // Exit

  return;
}

void
sheaf::member_record_set::
internalize(const scoped_index& xmax_row_int_id)
{
  // Preconditions:

  require(is_open());
  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

  internalize(xmax_row_int_id.hub_pod());
  
  // Postconditions:

  ensure(is_open());

  // Exit

  return;
}

void
sheaf::member_record_set::
externalize(pod_index_type xmax_row_int_id)
{
  // Preconditions:

  require(is_open());
  require(scaffold().structure().state_is_read_accessible());
  require(!record().has_equivalence_iterator());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << endl << "externalizing record set " << name() << endl;
#endif

  // Initialize the record buffer.

  reset_record_buffer_ct();

  // Get a handle to the max row member.

  // $$SCRIBBLE: need some less verbose method of creating an iterator
  // given an index. Some sort of virtual member handle constructor
  // e.g. abstract_poset_member* psh::new_member(scoped_index) might be useful.

  poset_state_handle& lposet = scaffold().structure();
  abstract_poset_member* lmax_row_mbr = lposet.top().clone();
  lmax_row_mbr->attach_to_state(&lposet, xmax_row_int_id);
  lmax_row_mbr->put_version(COARSEST_COMMON_REFINEMENT_VERSION);

  // Make the equivalence iterator.

  _record.new_equivalence_iterator();

  // Create the record and interval id spacess.

  make_idorder_file_id_spaces(*lmax_row_mbr);

  // Write the file id and interval id spaces.

  write_id_space_record(_record_id_space, record_id_space_record());
  write_id_space_record(_interval_id_space, interval_id_space_record());

  // Now traverse the down-set, externalizing the members. 
  // Whenever the record buffer is full, and when we're done,
  // write out the record buffer.

  record_index lext_id(_record_id_space);

  index_space_iterator& litr = _record_id_space.get_iterator();

  while(!litr.is_done())
  {
    // Get the external id.

    lext_id = litr.pod();

    assertion(lmax_row_mbr->host()->contains_member(lext_id));

    // This member has an explicit record in the file;
    // get the HDF buffer for this record

    assertion(record_buffer_ct() < record_buffer_ub());
    hvl_t* lhdf_buf = _hdf_bufs+record_buffer_ct();

    // Attach the transfer record to the member
    // and the HDF buffer and externalize it.

    _record.externalize(lext_id, lhdf_buf);

    // Enter the record id in the HDF selection

    assertion(record_buffer_ct() < record_buffer_ub());

    _hdf_selection[record_buffer_ct()][0] = lext_id.pod();

    // Increment the number of active records.

    inc_record_buffer_ct();

    // If the record buffer is full, write the selection to disk.

    if(record_buffer_is_full())
    {
      write_record_buffer();
    }
    
    litr.next();
  }

  _record_id_space.release_iterator(litr);

  // If the record buffer is not empty,
  // write the selection to disk.

  if(!record_buffer_is_empty())
  {
    write_record_buffer();
  }

  // Destroy the equivalence iterator.

  _record.delete_equivalence_iterator();

  // Delete row member.

  lmax_row_mbr->detach_from_state();
  delete lmax_row_mbr;

  // Postconditions:

  ensure(is_open());
  ensure(!record().has_equivalence_iterator());

  // Exit

  return;
}

void
sheaf::member_record_set::
externalize(const scoped_index& xmax_row_int_id)
{
  // Preconditions:

  require(is_open());
  require(scaffold().structure().state_is_read_accessible());
  require(!record().has_equivalence_iterator());

  // Body:

  externalize(xmax_row_int_id.hub_pod());

  // Postconditions:

  ensure(is_open());
  ensure(!record().has_equivalence_iterator());

  // Exit

  return;
}

sheaf::dof_tuple_record_set&
sheaf::member_record_set::
dof_tuple_records()
{
  return _dof_tuple_records;
}

const sheaf::member_record&
sheaf::member_record_set::
record() const
{
  return _record;
}

///
sheaf::pod_index_type
sheaf::member_record_set::
first_member_record()
{
  static const pod_index_type result = interval_id_space_record() + 1;
  return result;
}

// =============================================================================
// PROTECTED MEMBER FUNCTIONS
// =============================================================================

///
hid_t
sheaf::member_record_set::
create_dataset()
{
  hid_t result;

  // Preconditions:

  require(file().mode() == sheaf_file::READ_WRITE);

  // Body:

  // Create an extendible dataspace.
  /// @issue extendible dataspaces are probably not needed for all posets

  // Set the initial dimension.

  hsize_t linit_dims[DATASPACE_RANK];
  linit_dims[0] = _record_buffer_ub;

  // Maximum dimension.
  // We'll only extend along the first index.

  hsize_t lmax_dims[DATASPACE_RANK];
  lmax_dims[0] = H5S_UNLIMITED;

  _ext_dataspace_hdf_id = H5Screate_simple(DATASPACE_RANK, linit_dims, lmax_dims);
  if(_ext_dataspace_hdf_id < 0)
  {
    post_fatal_error_message("can't create exterior dataspace");
  }

  // We'll need a chunked dataset.
  // Create the chunk dimension.

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
    post_fatal_error_message("Unable to create dataset.");
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

///
void
sheaf::member_record_set::
create_int_data_type()
{
  // Preconditions:

  require(file().is_open());

  // Body:

  // Data type is variable length int.

  _int_data_type_hdf_id =
    H5Tvlen_create(type_map().converter(POD_INDEX_TYPE)->internal_type());

  if(_int_data_type_hdf_id < 0)
  {
    post_fatal_error_message("Can't create internal data type");
  }

  // Postconditions:

  ensure(int_data_type_hdf_id() >= 0);

  // Exit:

  return;
}

///
void
sheaf::member_record_set::
read_record(const record_index& xext_id)
{
  // Preconditions:

  // Body:

  /// @hack crudely adapted from read_records
  /// to read a single record at a time.

  // Make some convenient local variables.

  scoped_index lmbr_id(_record_id_space.hub_id_space());

  // Enter the record id in the HDF selection

  _hdf_selection[record_buffer_ct()][0] = xext_id.pod();

  // Increment the number of active records in the buffer.

  inc_record_buffer_ct();

  // Read the selection.

  read_selection();

  // Internalize the records in the record buffer.

  for(int i=0; i<record_buffer_ct(); i++)
  {

    // Get the internal member id for this record.

    lmbr_id = _record_id_space.hub_pod(_hdf_selection[i][0]);

    // Get the HDF buffer for this record

    assertion(i < record_buffer_ub());
    hvl_t* lhdf_buf = _hdf_bufs+i;

#ifdef DIAGNOSTIC_OUTPUT
    cout << "member_record_set::read_record: record: " << _hdf_selection[i][0] 
	 << " member id: " << lmbr_id 
	 << " buf len: " << lhdf_buf->len
	 << endl;
#endif

    // Attach the transfer record to the member
    // and the HDF buffer and internalize it.

    assertion(lhdf_buf->len > 0);
    
    _record.internalize(lhdf_buf, lmbr_id);
  }

  // Reclaim the storage allocated by HDF.

  delete_hdf_buffers();

  // Reset the number of active records.

  reset_record_buffer_ct();

  // Postconditions:

  // Exit

  return;
}



///
void
sheaf::member_record_set::
read_selection()
{
  // Preconditions:

  require(is_open());

  // Body:

  // Create the interior dataspace to describe the HDF record buffer.
  // Have to create the interior dataspace on each write to match
  // the size of the dataspace to the selection.

  make_internal_dataspace();

  // Set the selection.
  // The following cast is FM taken from HDF source. H5S_point_add immediately
  // casts arg to hsize_t*, which it thinks is pointing at the first element
  // in the array.

  //  const hsize_t** lselect = reinterpret_cast<const hsize_t**>(_hdf_selection);
  const hsize_t* lselect = &(_hdf_selection[0][0]);

  herr_t status = H5Sselect_elements(_ext_dataspace_hdf_id, H5S_SELECT_SET, record_buffer_ct(), lselect);
  if(status < 0)
  {
    post_fatal_error_message("can't set member record read selection");
  }

  // Read the selected records

  status = H5Dread(_hdf_id, _int_data_type_hdf_id, _int_dataspace_hdf_id,
                   _ext_dataspace_hdf_id, H5P_DEFAULT, _hdf_bufs);
  if(status < 0)
  {
    post_fatal_error_message("can't read member record selection");
  }

  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::member_record_set::
write_selection()
{
  // Preconditions:

  require(is_open());

  // Body:

  // Create the interior dataspace to describe the HDF record buffer.
  // Have to create the interior dataspace on each write to match
  // the size of the dataspace to the selection.

  make_internal_dataspace();

  // Extend the dataset to include the selection;

  hsize_t ldims[DATASPACE_RANK];

  ldims[0] = scaffold().member_id_space().end();

  extend_dataset(ldims, DATASPACE_RANK);

  // Set the selection.
  // The following cast is FM taken from HDF source. H5S_point_add immediately
  // casts arg to hsize_t*, which it thinks is pointing at the first element
  // in the array.

  //  const hsize_t** lselect = reinterpret_cast<const hsize_t**>(_hdf_selection);
  const hsize_t* lselect = &(_hdf_selection[0][0]);

  herr_t status = H5Sselect_elements(_ext_dataspace_hdf_id, H5S_SELECT_SET, _record_buffer_ct, lselect);
  if(status < 0)
  {
    post_fatal_error_message("can't set member record write selection");
  }

  // Write the selected records

  status = H5Dwrite(_hdf_id, _ext_data_type_hdf_id, _int_dataspace_hdf_id,
                    _ext_dataspace_hdf_id, H5P_DEFAULT, _hdf_bufs);
  if(status < 0)
  {
    post_fatal_error_message("can't write member record selection");
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record_set::
make_internal_dataspace()
{
  // Preconditions:

  require(is_open());

  // Body:

  // Create the interior dataspace to describe the HDF record buffer.
  // Have to create the interior dataspace on each write to match
  // the size of the dataspace to the selection.

  if(_int_dataspace_hdf_id >= 0)
  {
    H5Sclose(_int_dataspace_hdf_id);
  }

  hsize_t linit_dims[DATASPACE_RANK];
  linit_dims[0] = _record_buffer_ct;

  _int_dataspace_hdf_id = H5Screate_simple(DATASPACE_RANK, linit_dims, NULL);
  if(_int_dataspace_hdf_id < 0)
  {
    post_fatal_error_message("can't create interior data space");
  }

  // Postconditions:

  ensure(_int_dataspace_hdf_id >= 0);

  // Exit

  return;
}


// =============================================================================
// PRIVATE MEMBER FUNCTIONS
// =============================================================================

///
void
sheaf::member_record_set::
delete_external_buffers()
{
  // Preconditions:

  // Body:

  for(size_t i=0; i<record_buffer_ct(); i++)
  {
    hvl_t* ltmp = _hdf_bufs+i;
    if(ltmp->p != 0)
    {
      delete [] reinterpret_cast<int*>(ltmp->p);
      ltmp->p = 0;
      ltmp->len = 0;
    }
  }

  // Postconditions:

  ensure_for_all(i, 0, record_buffer_ct(), (_hdf_bufs[i].p == 0));
  ensure_for_all(i, 0, record_buffer_ct(), (_hdf_bufs[i].len == 0));

  // Exit:

  return;
}


///
void
sheaf::member_record_set::
delete_hdf_buffers()
{
  // Preconditions:

  // Body:

  herr_t status =
    H5Dvlen_reclaim(_int_data_type_hdf_id, _int_dataspace_hdf_id,
                    H5P_DEFAULT, _hdf_bufs);
  if(status < 0)
  {
    post_fatal_error_message("can't delete hdf buffers");
  }

  // Tracing and inspecting the source of HDF (as of ver 1.4.2 at least)
  // suggests that it the above call deallocates the variable length
  // buffers the read operation allocated, but only zeroes the hvl_t p and len
  // members for certain compound VL types, not for simple VL types.
  // So zero it out directly:

  hvl_t* lbuf = _hdf_bufs;
  hvl_t* lbuf_ub = lbuf+record_buffer_ct();
  while(lbuf < lbuf_ub)
  {
    lbuf->p = 0;
    lbuf->len = 0;
    lbuf++;
  }

  // Postconditions:

  ensure_for_all(i, 0, record_buffer_ct(), (_hdf_bufs[i].p == 0));
  ensure_for_all(i, 0, record_buffer_ct(), (_hdf_bufs[i].len == 0));

  // Exit:

  return;
}




///
void
sheaf::member_record_set::
write_record_buffer()
{
  // Preconditions:

  require(!record_buffer_is_empty());

  // Body:


#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record_set::write_record_buffer" << endl;
  cout << "\twriting member_record buffer for dataset " << name() << endl;
#endif

  write_selection();
  delete_external_buffers();
  reset_record_buffer_ct();

  // Postconditions:

  ensure(record_buffer_is_empty());

  // Exit:

  return;
}

void
sheaf::member_record_set::
clean_upper_covers()
{
  // Preconditions:


  // Body:

  // If we read the down set of anything 
  // other than the top of the poset, the upper covers may 
  // contain dangling links to members that weren't read.
  // Search all explicit upper covers, deleting dangling links.

  poset_state_handle& lposet = scaffold().structure();
  poset_crg_state& lcrg = lposet.crg();
  
  index_iterator litr = lposet.member_iterator();
  while(!litr.is_done())
  {
    // Clean up the upper cover.

    lcrg.clean_cover(UPPER, litr.index());
    litr.next();
  }
    
  // Postconditions:


  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::member_record_set::
record_id_space_record()
{
  static const pod_index_type result = 0;
  return result;
}

///
sheaf::pod_index_type
sheaf::member_record_set::
interval_id_space_record()
{
  static const pod_index_type result = 1;
  return result;
}

///
void
sheaf::member_record_set::
write_id_space_record(const interval_index_space_handle& xid_space, pod_index_type xrecord_id)
{
  // Preconditions:


  // Body:

  // Get the HDF buffer for this record

  assertion(record_buffer_ct() < record_buffer_ub());
  hvl_t* lhdf_buf = _hdf_bufs+record_buffer_ct();

  // Attach the transfer record to the member
  // and the HDF buffer and externalize it.

  _id_space_record.externalize(lhdf_buf, xid_space);

  // Enter the record id in the HDF selection

  assertion(record_buffer_ct() < record_buffer_ub());

  _hdf_selection[record_buffer_ct()][0] = xrecord_id;

  // Increment the number of active records.

  inc_record_buffer_ct();

  // Postconditions:


  // Exit:

  return;
}

///
void
sheaf::member_record_set::
read_id_space_record(interval_index_space_handle& xid_space, pod_index_type xrecord_id)
{
  // Preconditions:

  // Body:

  /// @hack crudely adapted from read_record
  /// to read the id space record.

  // Enter the record id in the HDF selection

  _hdf_selection[record_buffer_ct()][0] = xrecord_id;

  // Increment the number of active records in the buffer.

  inc_record_buffer_ct();

  // Read the selection.

  read_selection();

  // Internalize the records in the record buffer.

  for(int i=0; i<record_buffer_ct(); i++)
  {
    // Get the HDF buffer for this record

    assertion(i < record_buffer_ub());
    hvl_t* lhdf_buf = _hdf_bufs+i;

#ifdef DIAGNOSTIC_OUTPUT
    cout << "member_record_set::read_id_space_record: record: " << _hdf_selection[i][0] 
	 << " buf len: " << lhdf_buf->len
	 << endl;
#endif

    // Attach the transfer record to the member
    // and the HDF buffer and internalize it.

    _id_space_record.internalize(lhdf_buf, xid_space);
  }

  // Reclaim the storage allocated by HDF.

  delete_hdf_buffers();

  // Reset the number of active records.

  reset_record_buffer_ct();

  // Postconditions:

  // Exit

  return;
}


void
sheaf::member_record_set::
read_member(const scoped_index& xindex, record_index& xext_id)
{
  // Preconditions:


  // Body:

  xindex >> xext_id;

  if(xext_id.is_valid())
  {
    // Member has an explicit record; read it.

    read_record(xext_id);

    if(_record.is_resident())
    {
      // The member is now fully resident; mark it so.

      scaffold().resident().insert_member(xindex);	
    }
  }
  else
  {
    // Member doesn't have an explicit record;
    // must be an implicit member created as
    // part of a interval; just mark it resident.

    scaffold().resident().insert_member(xindex);
  }

  // Postconditions:


  // Exit:

  return;
}

///
void
sheaf::member_record_set::
make_idorder_file_id_spaces(const abstract_poset_member& xmbr)
{
  // Preconditions:

  require(record().has_equivalence_iterator());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "make_id_order_file_id_spaces for " << xmbr.host()->name() << endl;
#endif

  // Initialize the file id space, leaving room for the
  // id space itself in the first record.

  pod_index_type lext_id_pod = first_member_record();

  // Initialize the interval id space.

  _interval_id_space.clear();

  set<pod_index_type> ldown_set;
  preorder_itr<zn_to_bool> lpreitr(xmbr, WHOLE_INDEX, DOWN, NOT_STRICT);
  while(!lpreitr.is_done())
  {
    pod_index_type lhub_pod = lpreitr.index().hub_pod();
    implicit_crg_interval* linterval = xmbr.host()->crg().implicit_member(lhub_pod);

    if(linterval != 0)
    {
      if(lhub_pod == linterval->interval_member())
      {
	// Add the interval member to the down set.

	ldown_set.insert(lhub_pod);

	// Add the explicit members in the down set of the interval.

	xmbr.host()->crg().explicit_down_set_members(*linterval, ldown_set);
      }
      else
      {
	// Do nothing.
	// Don't include members that are not the interval member in the down set.
      }

      // Do not visit the down set of the interval members.

      lpreitr.truncate();
    }
    else
    {
      // Insert the explicit member.

      ldown_set.insert(lhub_pod);

      lpreitr.next();
    }
  }

  // If the poset has not had any members created in it, then
  // it contains only bottom and top and there is not link
  // between them, so the preceding iteration doesn't get 
  // bottom. Make sure bottom is in the downset.
  // This ensures bottom is in the record_id_space, which is required
  // by attributes_record_set::write_toc_bounds_attribute.

  ldown_set.insert(BOTTOM_INDEX);

  // Traverse the down-set of the poset in internal id order,
  // building the record and interval id_spaces.

  set<pod_index_type>::iterator litr = ldown_set.begin();

  while(litr != ldown_set.end())
  {
    size_type lsize = _record.external_size(xmbr.hub_id(*litr));
    if(lsize > 0)
    {  
      _record_id_space.insert(lext_id_pod, *litr);
      lext_id_pod++;
    }

    implicit_crg_interval* linterval = _record.interval();

    if(linterval != 0)
    {
      assertion(*litr == linterval->interval_member());

      // This is the first member of an implicit interval.
      // Make an entry in the interval map so we can map members
      // in the interval back to the implicit interval member
      // that represents them. This works by putting a single
      // entry into the map for the implicit interval member
      // then using the interval_begin query on the map. See
      // function must_read_interval_member. This technique only
      // uses the interval of the map, not the domain, so it 
      // doesn't actually matter what we put in for the domain.
      
      pod_index_type lbegin = linterval->begin();
      pod_index_type lend = linterval->end();

      // The impliciot interval is a half open interval [lbegin, lend)
      // but the interval map stores closed intervals, so decrement lend.

      --lend;
      
#ifdef DIAGNOSTIC_OUTPUT
      cout << "inserting interval map interval: "
	   << "  " << lbegin
	   << "  " << lend
	   << "  " << lbegin
	   << "  " << lend
	   << endl;
#endif    
    
      _interval_id_space.insert_interval(lbegin, lend, lbegin, lend);
    }    
      
#ifdef DIAGNOSTIC_OUTPUT
    cout << "id: " << lint_id << "  linterval:" << linterval;
    if(linterval != 0)
    {
      cout  << "  interval_member: " << linterval->interval_member();
    }
    cout << endl;
#endif    
    
    ++litr;
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << xmbr.host()->name() << "  file id space:" << endl;
  _record_id_space.print_map_rep(cout);
  cout << _record_id_space << endl;
  cout << endl << "interval id space:" << endl;
  _interval_id_space.print_map_rep(cout);
  cout << _interval_id_space << endl;
#endif  

  // Postconditions:


  // Exit:

  return;
}
