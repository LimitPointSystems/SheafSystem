
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class table_dof_tuple_record

#include "table_dof_tuple_record.h"

#include "arg_list.h"
#include "array_poset_dof_map.h"
#include "assert_contract.h"
#include "namespace_poset.h"
#include "namespace_poset_member.h"
#include "primitive_type.h"
#include "std_limits.h"
#include "std_sstream.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

// =============================================================================
// ANY FACET
// =============================================================================


///
sheaf::table_dof_tuple_record*
sheaf::table_dof_tuple_record::
clone() const
{
  table_dof_tuple_record* result = 0;

  // Preconditions:

  // Body:

  result = new table_dof_tuple_record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


// Class invariant
///
bool
sheaf::table_dof_tuple_record::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && attributes_record::invariant();

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

// Conformance test
///
bool
sheaf::table_dof_tuple_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const table_dof_tuple_record*>(other) != 0;

  // Postconditions:

  return result;

}



// =============================================================================
// TABLE_DOF_TUPLE_RECORD FACET
// =============================================================================

///
sheaf::table_dof_tuple_record::
table_dof_tuple_record(const table_dof_tuple_record& xother)
    : attributes_record(xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}


///
sheaf::table_dof_tuple_record::
table_dof_tuple_record(poset_scaffold& xscaffold)
    : attributes_record(xscaffold)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(&(scaffold()) == &xscaffold);

  // Exit

  return;
}

///
sheaf::table_dof_tuple_record::
~table_dof_tuple_record()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}


// =============================================================================
// PROTECTED MEMBER FUNCTIONS
// =============================================================================

///
void
sheaf::table_dof_tuple_record::
transfer_internal_buffer_to_poset()
{
  // Preconditions:

  require(!scaffold().structure().is_external() ? scaffold().structure().state_is_read_write_accessible() : true);

  // Body:

  // Copy the string buffer to a stream.

  stringstream lstream(_str_buf);

  // Ignore the "table_dof_tuple" header line.

  lstream.ignore(numeric_limits<streamsize>::max(), '\n');

  // Get the dof tuple in arg list form.

  arg_list largs;
  lstream >> largs;

  // Transfer the arg list to the dof tuple:

  poset_state_handle& lposet = scaffold().structure();

  if(lposet.is_external())
  {
    // Poset handle of the right type has already been created
    // in storage_agent::begin_read_transaction(namespace_poset&)
    // but the poset state has not been created because we need the
    // table dofs, if there are any.

    // Create the table dof tuple, need one even if it is empty.
    // Don't increment its ref_ct because we won't keep a reference here.

    array_poset_dof_map* ldof_tuple =
      new array_poset_dof_map(&(scaffold().internal_schema()), true);

    if(scaffold().internal_schema().table_dof_ct() > 0)
    {
      // Table dof tuple is not empty.
      // Convert any external ids to internal ids.
      // $$SCRIBBLE: this conversion is probalby no longer needed;
      // remove if possible, see scribble below.

      for(int i=0; i<largs.ct(); ++i)
      {
        arg_list::arg_type& largi = largs.arg(i);
        if(largi.type() == NAMESPACE_RELATIVE_MEMBER_INDEX)
        {
          scaffold().convert_record_id_to_member_id(&largi.value);
        }
        else if(largi.type() == NAMESPACE_RELATIVE_SUBPOSET_INDEX)
        {
          scaffold().convert_record_id_to_subposet_id(&largi.value);
        }
      }

      // Put dofs into dof tuple.

      ldof_tuple->put_dof_tuple(largs);
    }

    // Create the state.
    // $$SCRIBBLE: above conversion from record->internal ids
    // should be eliminated and new_state should take arg_list instead of dof tuple.
    // See other usage of new_state in namespace_poset::new_member_poset.

    lposet.new_state(scaffold().internal_schema(), *ldof_tuple);

    // We previously got read access to the schema and other prerequisites in
    // storage_agent::read_prerequisites in order to build the poset.
    // Release that level now in order to remain proper.

    release_prerequisites(lposet);

    // Get read write access.

    lposet.get_read_write_access();
    
  }
  

  // Poset is guaranteed to have a state now.

  // Postconditions:


  // Exit:

  return;
}

///
void
sheaf::table_dof_tuple_record::
transfer_poset_to_internal_buffer()
{
  // Preconditions:


  // Body:

  arg_list largs;
  scaffold().structure().table_dof_map().get_dof_tuple(largs);

  // Convert any external ids to internal ids.

  for(int i=0; i<largs.ct(); ++i)
  {
    arg_list::arg_type& largi = largs.arg(i);
    if(largi.type() == NAMESPACE_RELATIVE_MEMBER_INDEX)
    {
      scaffold().convert_member_id_to_record_id(&largi.value);
    }
    else if(largi.type() == NAMESPACE_RELATIVE_SUBPOSET_INDEX)
    {
      scaffold().convert_subposet_id_to_record_id(&largi.value);
    }
  }

  stringstream lstream;
  lstream << "Table_dof_tuple:" << endl << largs;

  // Have to copy stringstream to string
  // because can't get C string from stringstream.
  // Could use strstream, but that's error-prone and not portable.

  _str_buf = lstream.str();

  put_is_internal(true);
  put_is_external(false);

  // Postconditions:

  ensure(is_internal());
  ensure(!is_external());

  // Exit:

  return;
}

// =============================================================================
// PRIVATE MEMBER FUNCTIONS
// =============================================================================



///
void
sheaf::table_dof_tuple_record::
release_prerequisites(poset_state_handle& xposet)
{

  // Preconditions:

  require(xposet.name_space()->state_is_read_accessible());

  // Body:

  namespace_poset* lns = xposet.name_space();

  // Release the level of access to the posets on which this poset depends,
  // acquired in storage_agent::read_prequisties

  // Prerequisite ids are available from xposet or from associated
  // name space member. Latter doesn't require read access to xposet.
  // Get a handle to the name space member for xposet.

  namespace_poset_member lname_space_mbr(xposet);

  for(int i=0; i<PREREQ_IDS_UB; ++i)
  {
    pod_index_type lprereq_id = lname_space_mbr.poset_prereq_id(i);

    if(is_valid(lprereq_id))
    {
      // Release the access.

      lns->member_poset(lprereq_id).release_access();
    }
  }

  // Clean up

  lname_space_mbr.detach_from_state();

  // Postconditions:

  ensure(unexecutable(all prerequisites have been release));

  // Exit

  return;
}



