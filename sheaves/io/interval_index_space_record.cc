
//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

// Implementation for class interval_index_space_record

#include "interval_index_space_record.h"

#include "assert_contract.h"
#include "error_message.h"
#include "member_record_set.h"
#include "interval_index_space_iterator.h"

//#define DIAGNOSTIC_OUTPUT
// #undef DIAGNOSTIC_OUTPUT

// ===========================================================
// INTERVAL_INDEX_SPACE_RECORD FACET
// ===========================================================

///
sheaf::interval_index_space_record::
interval_index_space_record(member_record_set& xhost)
  : variable_length_record(xhost.scaffold())
{

  // Preconditions:

  // Body:

  // Neither buffer is initialized.

  put_is_internal(false);
  put_is_external(false);

  // Postconditions:

  ensure(invariant());
  ensure(buf() == 0);
  ensure(buf_ub() == 0);
  ensure(!is_internal());
  ensure(!is_external());

  // Exit:

  return;
}

///
sheaf::interval_index_space_record::
interval_index_space_record(const interval_index_space_record& xother)
  : variable_length_record(xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}

///
sheaf::interval_index_space_record::
~interval_index_space_record()
{

  // Preconditions:

  // Body:

  // Nothing specific to do.
  /// @issue can we just not define this function?

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
// WRITE FACET
// ===========================================================

///
void
sheaf::interval_index_space_record::
externalize(hvl_t* xhdf_buffer, const interval_index_space_handle& xid_space)
{

  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "interval_index_space_record::externalize:" << endl;
#endif

  // Initialize the internal buffer from the id space.

  transfer_id_space_to_internal_buffer();

  // Convert the internal buffer to external form
  // and place the result in the external buffer.

  convert_internal_buffer_to_external_buffer(xid_space);

  // Transfer the external buffer to HDF

  transfer_external_buffer_to_HDF(xhdf_buffer);

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::interval_index_space_record::
transfer_id_space_to_internal_buffer()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  // Nothing to do; internal buffer is the id space itself.

  // Now the internal buffer is initialized;

  put_is_internal(true);

  // Postconditions:

  ensure(is_internal());

  // Exit

  return;
}

void
sheaf::interval_index_space_record::
convert_internal_buffer_to_external_buffer(const interval_index_space_handle& xid_space)
{
  // Preconditions:

  // Body:

  // Initialize the external buffer from the internal buffer.

  initialize_external_buffer(xid_space);

  // Externalize all the data fields.

  size_t lnext_field_offset = 0;

  externalize_id_space_data(lnext_field_offset, xid_space);

  // Now the external buffer is valid.

  put_is_external(true);

  // Postconditions:

  ensure(is_external());

  // Exit

  return;
}

///
void
sheaf::interval_index_space_record::
initialize_external_buffer(const interval_index_space_handle& xid_space)
{
  // Preconditions:


  // Body:

  // Determine the size of the external buffer.

  size_type lend_offset = 0;

  interval_index_space_iterator& litr = 
    dynamic_cast<interval_index_space_iterator&>(xid_space.get_iterator());
  while(!litr.is_done())
  {
    lend_offset += 4;    
    litr.next_interval();
  }
  xid_space.release_iterator(litr);

  // Allocate the external buffer.
  // Buffer will be deleted in member_record_set::delete_external_buffers.

  void* lbuf = lend_offset > 0 ? new pod_index_type[lend_offset] : 0;

  put_buf(lbuf, lend_offset);

  // Buffer will not be deleted in destructor for this.

  put_delete_buffer(false);

  // The external buffer is allocated but not initialized.

  put_is_external(false);

  // Postconditions:

  ensure(!is_external());

  // Exit

  return;
}

///
void
sheaf::interval_index_space_record::
externalize_id_space_data(size_t& xnext_field_offset, const interval_index_space_handle& xid_space)
{

  // Preconditions:

  require(is_internal());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

#ifdef DIAGNOSTIC_OUTPUT
  cout << scaffold().structure().name()
       << " file_id_space: " << endl;  
  xid_space.print_map_rep(cout);
  cout << xid_space << endl;
#endif

  interval_index_space_iterator& litr = 
    dynamic_cast<interval_index_space_iterator&>(xid_space.get_iterator());
  while(!litr.is_done())
  {
    int_buf()[xnext_field_offset++] = litr.interval_begin();
    int_buf()[xnext_field_offset++] = litr.interval_end();
    int_buf()[xnext_field_offset++] = xid_space.hub_pod(litr.interval_begin());
    int_buf()[xnext_field_offset++] = xid_space.hub_pod(litr.interval_end());
    litr.next_interval();

#ifdef DIAGNOSTIC_OUTPUT
    pod_index_type* lbuf = int_buf() + old_xnext_field_offset;    
    cout << setw(12) << lbuf[0]
	 << setw(12) << lbuf[1]
	 << setw(12) << lbuf[2]
	 << setw(12) << lbuf[3]
	 << endl;
#endif

  }
  xid_space.release_iterator(litr);

  // Postconditions:

  ensure(xnext_field_offset == buf_ub());

  // Exit

  return;
}

///
void
sheaf::interval_index_space_record::
transfer_external_buffer_to_HDF(hvl_t* xbuf)
{
  // Preconditions:

  require(xbuf != 0);
  require(is_external());

  // Body:

  xbuf->p = buf();
  xbuf->len = buf_ub();

  // Postconditions:

  ensure(xbuf->p == buf());
  ensure(xbuf->len == buf_ub());

  // Exit

  return;
}

// ===========================================================
// READ FACET
// ===========================================================

///
void
sheaf::interval_index_space_record::
internalize(hvl_t* xhdf_buffer, interval_index_space_handle& xid_space)
{

  // Preconditions:

  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "interval_index_space_record::internalize:" << endl;
#endif

  // Initialize the external buffer from the HDF buffer.

  transfer_HDF_to_external_buffer(xhdf_buffer);

  // Convert the external buffer to internal format
  // and place the result in the internal buffer

  convert_external_buffer_to_internal_buffer(xid_space);

  // Transfer the internal buffer to the member.

  transfer_internal_buffer_to_id_space();

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::interval_index_space_record::
transfer_HDF_to_external_buffer(hvl_t* xbuf)
{
  // Preconditions:

  require(xbuf != 0);

  // Body:

  put_buf(xbuf->p, xbuf->len);

  put_is_external(true);
  put_is_internal(false);

  // Postconditions:

  ensure(buf() == xbuf->p);
  ensure(buf_ub() == xbuf->len);
  ensure(is_external());
  ensure(!is_internal());

  // Exit

  return;
}

///
void
sheaf::interval_index_space_record::
convert_external_buffer_to_internal_buffer(interval_index_space_handle& xid_space)
{
  // Preconditions:

  // Body:

  size_t lnext_field_offset = 0;

  // Internalize all the data fields.

  internalize_id_space_data(lnext_field_offset, xid_space);

  // Now the internal buffer is valid.

  put_is_internal(true);

  // Postconditions:

  ensure(is_internal());

  // Exit

  return;
}

///
void
sheaf::interval_index_space_record::
internalize_id_space_data(size_t& xnext_field_offset, interval_index_space_handle& xid_space)
{

  // Preconditions:

  require(is_external());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  pod_index_type* lbuf = int_buf();
  while(xnext_field_offset < buf_ub())
  {

#ifdef DIAGNOSTIC_OUTPUT
    cout << setw(12) << lbuf[0]
	 << setw(12) << lbuf[1]
	 << setw(12) << lbuf[2]
	 << setw(12) << lbuf[3]
	 << endl;
#endif
    
    xid_space.insert_interval(lbuf[0], lbuf[1], lbuf[2], lbuf[3]);
    xnext_field_offset += 4;
    lbuf += 4;
  }
  

#ifdef DIAGNOSTIC_OUTPUT
  cout << scaffold().structure().name()
       << " file_id_space: " << endl;
  xid_space.print_map_rep(cout);
  cout << xid_space << endl;
#endif

  // Postconditions:

  ensure(xnext_field_offset == buf_ub());

  // Exit

  return;
}

///
void
sheaf::interval_index_space_record::
transfer_internal_buffer_to_id_space()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

  // Nothing to do; the internal buffer is the id space itself;

  // Postconditions:

  // Exit

  return;
}

// ===========================================================
// ANY FACET
// ===========================================================

///
sheaf::interval_index_space_record*
sheaf::interval_index_space_record::
clone() const
{
  interval_index_space_record* result;

  // Preconditions:

  // Body:

  result = new interval_index_space_record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
bool
sheaf::interval_index_space_record::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && variable_length_record::invariant();

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
sheaf::interval_index_space_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const interval_index_space_record*>(other) != 0;

  // Postconditions:

  return result;

}


