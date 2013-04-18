// $RCSfile: member_record.cc,v $ $Revision: 1.46 $ $Date: 2013/03/13 00:59:04 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class member_record

#include "member_record.h"

#include "array_poset_dof_map.h"
#include "assert_contract.h"
#include "data_converter.h"
#include "dof_tuple_record_set.h"
#include "error_message.h"
#include "index_equivalence_iterator.h"
#include "index_space_iterator.h"
#include "implicit_crg_interval.h"
#include "member_record_set.h"
#include "namespace_poset.h"
#include "namespace_poset_dof_map.h"
#include "poset_bounds.h"
#include "poset_dof_iterator.h"
#include "primitives_poset_dof_map.h"
#include "record_queue.h"
#include "standard_dof_tuple_index.h"

//#define DIAGNOSTIC_OUTPUT
// #undef DIAGNOSTIC_OUTPUT

// ===========================================================
// MEMBER_RECORD FACET
// ===========================================================

///
sheaf::member_record::
member_record(member_record_set& xhost)
  : variable_length_record(xhost.scaffold()), _host(xhost), _eqv_itr(0)
{

  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  // Initialize member-independent offsets.

  _end_offset = 0;

  // Neither buffer is initialized.

  put_is_internal(false);
  put_is_external(false);

  // Initialize dof tuple ids to arbitrary size large enough
  // to avoid several small auto reallocations.

  _dof_tuple_ids.reserve(32);
  _dof_tuple_ids.set_ct(0);

  // Initialize the subposet_ids field in the internal buffer.

  int lsp_ub = scaffold().subposets().size();
  _subposet_ids.reserve(lsp_ub);
  _subposet_ids.set_ct(0);

  // Initialize equivalent ids to arbitrary size large enough
  // to avoid several small auto reallocations.

  _eqv_ids.reserve(32);
  _eqv_ids.set_ct(0);

  // Initialize name buffer to arbitrary size large enough
  // to avoid several small auto reallocations.

  _names.reserve(32);
  _names.set_ct(0);

  // Make sure _mbr_id and _ext_id have 
  // internal and extrnal scope, repsectivly.

  _mbr_id.put_scope(scaffold().structure().member_hub_id_space(false));
  _ext_id.put_scope(scaffold().member_id_space());

  // Postconditions:

  ensure(invariant());

  ensure(!(external_index().is_valid()));

  ensure(&(host()) == &xhost);
  ensure(buf() == 0);
  ensure(buf_ub() == 0);
  ensure(!is_internal());
  ensure(!is_external());

  // Exit:

  return;
}

///
sheaf::member_record::
member_record(const member_record& xother)
  : variable_length_record(xother), _host(xother._host), _eqv_itr(0)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}

///
sheaf::member_record::
~member_record()
{

  // Preconditions:

  // Body:

  if(_eqv_itr != 0)
    delete _eqv_itr;

  // Postconditions:

  // Exit:

  return;
}



///
sheaf::implicit_crg_interval*
sheaf::member_record::
interval() const
{
  return _interval;
}



///
bool
sheaf::member_record::
is_resident() const
{
  return _is_resident;
}


///
sheaf::member_record_set&
sheaf::member_record::
host()
{
  // Preconditions:

  // Body:

  member_record_set& result = _host;

  // Postconditions:

  // Exit:

  return result;
}


///
const sheaf::member_record_set&
sheaf::member_record::
host() const
{
  // Preconditions:

  // Body:

  member_record_set& result = _host;

  // Postconditions:

  // Exit:

  return result;
}

// ===========================================================
// EQUIVALENCE ITERATOR FACET
// ===========================================================

void
sheaf::member_record::
new_equivalence_iterator()
{
  // Preconditions:

  require(!has_equivalence_iterator());
  require(scaffold().structure().state_is_read_accessible());

  // Body:

  _eqv_itr = new index_equivalence_iterator(scaffold().structure().member_id_spaces(false),
					    true, false);

  // Postconditions:

  ensure(has_equivalence_iterator());

  // Exit:

  return;
}

void
sheaf::member_record::
delete_equivalence_iterator()
{
  // Precondtions:

  require(has_equivalence_iterator());

  // Body:

  delete _eqv_itr;
  _eqv_itr = 0;

  // Postconditions:

  ensure(!has_equivalence_iterator());

  // Exit:

  return;
}

bool
sheaf::member_record::
has_equivalence_iterator() const
{
  return (_eqv_itr != 0);
}

sheaf::index_equivalence_iterator&
sheaf::member_record::
equivalence_iterator(const scoped_index& xrep_id)
{
  // Preconditions:

  require(has_equivalence_iterator());
  require(scaffold().structure().contains_member(xrep_id, true));

  // Body:

  index_equivalence_iterator& result = *_eqv_itr;
  result.put_rep_id(xrep_id);
  result.reset();

  // Postconditions:

  ensure(result.rep_id() == xrep_id.hub_pod());

  // Exit:

  return result;
}

// ===========================================================
// EXTERNAL SIZE FACET
// ===========================================================
 
///
sheaf::size_type
sheaf::member_record::
external_size(const scoped_index& xmbr_id)
{

  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::external_size: member: " << xmbr_id << endl;
#endif

  // Map xmbr_id into internal and external scope.

  xmbr_id >> _mbr_id;
  xmbr_id >> _ext_id;

  // Initialize poset and interval variables.

  _poset = &scaffold().structure();
  _interval = _poset->crg().implicit_member(xmbr_id.hub_pod());

  _toc.reset();

  size_type result = 0;  
  result += private_data_external_size();
  result += dof_tuple_ids_external_size();
  result += lower_cover_external_size();
  result += upper_cover_external_size();
  result += subposet_ids_external_size();
  result += eqv_ids_external_size();
  result += toc_external_size();

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() 
       << "  size: " << result
       << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::size_type
sheaf::member_record::
private_data_external_size()
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "sheaf::member_record::private_data_external_size " << endl;
#endif

  size_type result;  

  if(_interval != 0)
  {
    // This is an implicit member.

    if(_interval->is_interval_member(_mbr_id.pod()))
    {
      // This is the interval member itself;
      // get the private data.

      result = _interval->private_data_size();
    }
    else
    {
      // This is one of the other members in the interval;
      // doesn't have private data.

      result = 0;
    }
  }
  else
  {
    // This is an explicit member; no private data.

    result = 0;
  }

  if(result > 0)
  {
    // Add room for the ct field.

    ++result;
  }  
  
  _toc[HAS_PRIVATE_DATA] = (result > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() 
       << "  size: " << result
       << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::size_type
sheaf::member_record::
dof_tuple_ids_external_size()
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::dof_tuple_ids_external_size " << endl;
#endif

  size_type result;

  if(_interval != 0)
  {
    // This member is in an implicit interval.

    if(_interval->is_interval_member(_mbr_id.pod()))
    {
      // This is the interval member itself

      result = _interval->dof_tuple_ids().ct();
    }
    else
    {
      result = 0;
    }
  }
  else 
  {
    // This is an explicit member.

    if(_poset->is_jim(_mbr_id, false))
    {
      // Member is a jim in some version; it has a dof tuple.

      result = 1;
    }
    else
    {
      // Member is a jrm - doesn't have a dof tuple.

      result = 0;
    }
  }
  
  if(result > 0)
  {
    // Add room for the ct field.

    ++result;
  }
  
  _toc[HAS_DOF_TUPLE_IDS] = (result > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() 
       << "  size: " << result
       << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::size_type
sheaf::member_record::
lower_cover_external_size()
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::lower_cover_external_size " << endl;
#endif

  poset_crg_state& lcrg = _poset->crg();

  // Lower_cover:

  pod_index_type lmbr_id = _mbr_id.hub_pod();

  size_type result;
  if(lcrg.cover_is_explicit(LOWER, lmbr_id))
  {
    // Lover cover for this member is explicit;
    // must be written to the file.

    result = lcrg.cover_ct(LOWER, lmbr_id);
  }
  else
  {
    // Lover cover for this member is implicit.

    result = 0;
  }

  if(result > 0)
  {
    // Add room for the ct field.

    ++result;
  }
  
  _toc[HAS_LOWER_COVER] = (result > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() 
       << "  size: " << result
       << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::size_type
sheaf::member_record::
upper_cover_external_size()
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::upper_cover_external_size " << endl;
#endif

  poset_crg_state& lcrg = _poset->crg();

  // Upper_cover:

  pod_index_type lmbr_id = _mbr_id.hub_pod();

  size_type result;
  if(lcrg.cover_is_explicit(UPPER, lmbr_id))
  {
    // Upper cover for this member is explicit;
    // must be written to the file.

    result = lcrg.cover_ct(UPPER, lmbr_id);
  }
  else
  {
    // Upper cover for this member is implicit.

    result = 0;
  }

  if(result > 0)
  {
    // Add room for the ct field.

    ++result;
  }
  
  _toc[HAS_UPPER_COVER] = (result > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() 
       << "  size: " << result
       << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::size_type
sheaf::member_record::
subposet_ids_external_size()
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::subposet_ids_external_size " << endl;
#endif

  // Iterate over all the subposets except the standard ones;
  // whole doesn't need to be stored and jims is in the toc.

  int lsp_min = _poset->standard_subposet_ct();
  int lsp_ub = scaffold().subposets().size();

  bool lhas_toc_subposet_ids = false;
  size_type result = 0;

  for(int i = lsp_min; i<lsp_ub; i++)
  {
    subposet* lsp = scaffold().subposets()[i];

    if( lsp->contains_member(_mbr_id) )
    {
      int lsp_bit = i - lsp_min + SUBPOSET_BITS_BEGIN;
      if(lsp_bit < SUBPOSET_BITS_END)
      {
        // This subposet is in the toc.

	lhas_toc_subposet_ids = true;
      }
      else
      {
        // Out of room in the toc.
        // Put subposet id into buffer to be
        // written explicitly into record.

        ++result;
      }
    }
  }

  if(result > 0)
  {
    // Add room for the ct field.

    ++result;
  }
  
  _toc[HAS_TOC_SUBPOSET_IDS] = lhas_toc_subposet_ids;
  _toc[HAS_SUBPOSET_IDS] = (result > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() 
       << "  size: " << result
       << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::size_type
sheaf::member_record::
eqv_ids_external_size()
{
  // Preconditions:

  require(has_equivalence_iterator());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::eqv_ids_external_size " << endl;
#endif

  size_type result = 0;

  // Iterate over the equivalence class of xmbr_id,
  // transferring to internal buffer.

  result += (2*equivalence_iterator(_mbr_id).ct());

  if(result > 0)
  {
    // Add room for the ct field.

    ++result;
  }
  
  _toc[HAS_EQV_IDS] = (result > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() 
       << "  size: " << result
       << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::size_type
sheaf::member_record::
toc_external_size()
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::toc_external_size" << endl;
#endif

  // Set bits so that if we have to write the toc,
  // some bit will be turned on. Note that this is
  // not quite the same definition of the bits as
  // when we actually write the toc.

  _toc[IS_JIM]         = (_interval == 0) && _poset->is_jim(_mbr_id);
  _toc[HAS_NAMES]      = _poset->member_name_ct(_mbr_id, false) > 0;
  _toc[IS_INTERVAL]       = (_interval != 0) && (_interval->is_interval_member(_mbr_id.pod()));


  // HAS_DOF_TUPLE _IDS, HAS_LOWER_COVER, HAS_UPPER_COVER, HAS_SUBPOSET_IDS, 
  // and HAS_EQV_IDS flags already set in their respective _external_size routines.

  size_type result = _toc.any() ? 1 : 0;


#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() 
       << "  size: " << result
       << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// WRITE FACET
// ===========================================================

///
void
sheaf::member_record::
externalize(const scoped_index& xmbr_id, hvl_t* xhdf_buffer)
{

  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::externalize: member: " << xmbr_id << endl;
#endif

  // Map xmbr_id into internal and external scope.

  xmbr_id >> _mbr_id;
  xmbr_id >> _ext_id;

  // Initialize poset and interval variables.

  _poset = &scaffold().structure();
  _interval = _poset->crg().implicit_member(xmbr_id.hub_pod());

  // Initialize the internal buffer from the member
  // with internal id xmbr_id.

  transfer_member_to_internal_buffer(xmbr_id);

  // Convert the internal buffer to external form
  // and place the result in the external buffer.

  convert_internal_buffer_to_external_buffer();

  // Transfer the external buffer to HDF

  transfer_external_buffer_to_HDF(xhdf_buffer);

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_member_to_internal_buffer(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  clear_internal_buffer();

  // Toc:

  transfer_member_to_toc(xmbr_id);

  // Dof tuple id:

  if(_toc[IS_INTERVAL])
  {
    transfer_interval_to_private_data(xmbr_id);
    transfer_interval_to_dof_tuple_ids(xmbr_id);
    transfer_interval_to_class_names(xmbr_id);
  }
  else
  {
    transfer_member_to_dof_tuple_ids(xmbr_id);
  }

  // Lower_cover:

  transfer_member_to_lower_cover(xmbr_id);

  // Upper_cover:

  transfer_member_to_upper_cover(xmbr_id);

  // Subposet ids:

  transfer_member_to_subposet_ids(xmbr_id);

  // Equivalent ids:

  transfer_member_to_eqv_ids(xmbr_id);

  // Names:

  transfer_member_to_names(xmbr_id);


#ifdef DIAGNOSTIC_OUTPUT
  cout << "leaving member_record::transfer_member_to_internal_buffer " << endl;
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif

  // Now the internal buffer is initialized;

  put_is_internal(true);

  // Postconditions:

  ensure(is_internal());

  // Exit

  return;
}

///
void
sheaf::member_record::
clear_internal_buffer()
{
  // Preconditions:


  // Body:

  _toc.reset();
  _private_data.clear();
  _dof_tuple_ids.clear();
  _lower_cover.clear();
  _upper_cover.clear();
  _subposet_ids.clear();
  _eqv_ids.clear();
  _names.clear();

  // Postconditions:

  ensure(_toc.none());
  ensure(_private_data.ct() == 0);
  ensure(_dof_tuple_ids.ct() == 0);
  ensure(_lower_cover.ct() == 0);
  ensure(_upper_cover.ct() == 0);
  ensure(_subposet_ids.ct() == 0);
  ensure(_eqv_ids.ct() == 0);
  ensure(_names.ct() == 0);

  // Exit:

  return;
}

///
void
sheaf::member_record::
transfer_member_to_toc(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(_toc.none());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_member_to_toc " << endl;
#endif

  // Make some convenient local variables

  _toc[IS_JIM]         = _poset->is_jim(xmbr_id);
  _toc[HAS_NAMES]      = _poset->member_name_ct(_mbr_id, false) > 0;

  _toc[IS_INTERVAL]       = (_interval != 0);

  // HAS_DOF_TUPLE_IDS, HAS_LOWER_COVER, HAS_UPPER_COVER, HAS_SUBPOSET_IDS, 
  // and HAS_EQV_IDS flags set in transfer_*_to_dof_tuple_ids, transfer_member_to_links,
  // transfer_member_to_subposet_ids, and transfer_member_to_eqv_ids,
  // respectively.

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_interval_to_private_data(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(scaffold().structure().crg().implicit_member(xmbr_id.hub_pod()) != 0);
  require(_private_data.ct() == 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_interval_to_private_data " << endl;
#endif

  // Make some convenient local variables

  if(_interval->is_interval_member(xmbr_id))
  {
    // This is the interval member itself;
    // get the private data.

    _interval->get_private_data(_private_data);
  }
  else
  {
    // This is one of the other members in the interval;
    // doesn't have private data.
    // Do nothing.
  }

  _toc[HAS_PRIVATE_DATA] = (_private_data.ct() > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\t_private_data ct: " << _private_data.ct() << "  ids: ";
  for(int i=0; i<_private_data.ct(); i++)
  {
    cout << setw(6) << _private_data[i];
  }
  cout << endl;
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif


  // Postconditions:

  // Exit

  return;
}

void
sheaf::member_record::
transfer_member_to_dof_tuple_ids(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(scaffold().structure().crg().implicit_member(xmbr_id.hub_pod()) == 0);
  require(_dof_tuple_ids.ct() == 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_member_to_dof_tuple_id " << endl;
#endif

  if(_poset->is_jim(xmbr_id, false))
  {
    // Member is a jim in some version; it has a dof tuple.

    scoped_index ldof_tuple_id;
    pod_index_type lext_dof_tuple_id;

    // Restriction to BOTTOM:
    // If the schema is restricted to BOTTOM, then the
    // dof tuple is empty. As with the empty set and the null
    // vector, we treat the empty dof tuple as unique. So all
    // members of a poset on the BOTTOM schema share the same
    // dof tuple, which contains no dofs. The dof tuple id for
    // the empty dof tuple is 0. This structure is the same for
    // both internal and external posets.

    bool ldof_tuple_is_empty =
      (scaffold().external_schema().index() == BOTTOM_INDEX);

    if(ldof_tuple_is_empty)
    {
      // Dof tuple is empty; use the unique empty dof tuple id.

      ldof_tuple_id = _poset->dof_tuple_id(EMPTY_DOF_TUPLE_INDEX, false);
    }
    else
    {
      // External dof tuple is not empty;
      // use the member's dof tuple id.

      _poset->member_dof_tuple_id(xmbr_id, ldof_tuple_id, false);
    }

    // Get the external dof tuple id, if one has been assigned.

    lext_dof_tuple_id =
      scaffold().dof_tuple_id_space().pod(ldof_tuple_id);

    if(!is_valid(lext_dof_tuple_id))
    {
      // This is the first time we've encountered this dof tuple;
      // get an external id for it. External id will be the offset of
      // the beginning of the tuple in the dataset.

      lext_dof_tuple_id =
	host().dof_tuple_records().compute_ext_id(ldof_tuple_id);

      // If there's something to write, put it on the write queue.

      if(!ldof_tuple_is_empty)
      {
        host().dof_tuple_records().queue().enqueue(lext_dof_tuple_id);
      }

      // Save the dof tuple type and class name to be written in the
      // respective maps; maps must not already contain an entry for
      // lext_dof_tuple_id.

      assertion(scaffold().dof_tuple_types().find(lext_dof_tuple_id) ==
             scaffold().dof_tuple_types().end());

      const poset_dof_map& ldof_map = _poset->row_dof_map(ldof_tuple_id);
      
      dof_tuple_type ltype_id = ldof_map.type_id();

      typedef poset_scaffold::dof_tuple_types_type::value_type types_value_type;
      types_value_type ltypes_value(lext_dof_tuple_id, ltype_id);

      scaffold().dof_tuple_types().insert(ltypes_value);

      assertion(scaffold().dof_tuple_class_names().find(lext_dof_tuple_id) ==
             scaffold().dof_tuple_class_names().end());

      string lclass_name = ldof_map.class_name();

      typedef poset_scaffold::dof_tuple_class_names_type::value_type names_value_type;
      names_value_type lnames_value(lext_dof_tuple_id, lclass_name);

      scaffold().dof_tuple_class_names().insert(lnames_value);
    }

    // Save the external id in the internal buffer.

    _dof_tuple_ids.push_back(lext_dof_tuple_id);
  }
  else
  {
    // Member is a jrm - doesn't have a dof tuple; do nothing.
  }

  _toc[HAS_DOF_TUPLE_IDS] = (_dof_tuple_ids.ct() > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\t_dof_tuple_ids ct: " << _dof_tuple_ids.ct() << "  ids : ";
  for(int i=0; i<_dof_tuple_ids.ct(); i++)
  {
    cout << setw(6) << _dof_tuple_ids[i];
  }
  cout << endl;
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif

  // Postconditions:

  // Exit

  return;
}

void
sheaf::member_record::
transfer_interval_to_dof_tuple_ids(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(scaffold().structure().crg().implicit_member(xmbr_id.hub_pod()) != 0);
  require(_dof_tuple_ids.ct() == 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_interval_to_dof_tuple_id " << endl;
#endif

  // Make some convenient local variables

  interval_index_space_handle& ldof_tuple_space =
    scaffold().dof_tuple_id_space();

  if(_interval->is_interval_member(xmbr_id))
  {
    // This is the interval member itself.

    for(int i=0; i< _interval->dof_tuple_ids().ct(); ++i)
    {
      scoped_index ldof_tuple_id = scaffold().structure().dof_tuple_id(_interval->dof_tuple_ids()[i], false);

      // Get the external dof tuple id, if one has been assigned.

      pod_index_type lext_dof_tuple_id = ldof_tuple_space.pod(ldof_tuple_id);

      if(!is_valid(lext_dof_tuple_id))
      {
        // This is the first time we've encountered this dof tuple;
        // get an external id for it. External id will be the offset of
        // the beginning of the tuple in the dataset.

	lext_dof_tuple_id =
	  host().dof_tuple_records().compute_ext_id(ldof_tuple_id);

        // Put the dof tuple id on the write queue.

        host().dof_tuple_records().queue().enqueue(lext_dof_tuple_id);

        // Save the dof tuple type and class name to be written in the
        // respective maps; maps must not already contain an entry for
        // lext_dof_tuple_id.

        assertion(scaffold().dof_tuple_types().find(lext_dof_tuple_id) ==
               scaffold().dof_tuple_types().end());

	const poset_dof_map& ldof_map = _poset->row_dof_map(ldof_tuple_id);

        dof_tuple_type ltype_id = ldof_map.type_id();

        typedef poset_scaffold::dof_tuple_types_type::value_type types_value_type;
        types_value_type ltypes_value(lext_dof_tuple_id, ltype_id);

        scaffold().dof_tuple_types().insert(ltypes_value);

        assertion(scaffold().dof_tuple_class_names().find(lext_dof_tuple_id) ==
               scaffold().dof_tuple_class_names().end());

        string lclass_name = ldof_map.class_name();

        typedef poset_scaffold::dof_tuple_class_names_type::value_type names_value_type;
        names_value_type lnames_value(lext_dof_tuple_id, lclass_name);

        scaffold().dof_tuple_class_names().insert(lnames_value);
      }

      // Save the external id in the internal buffer.

      _dof_tuple_ids.push_back(lext_dof_tuple_id);
    }
  }
  else
  {
    // This is one of the other members in the interval;
    // dof tuple has already been written out.
    // Do nothing.
  }

  _toc[HAS_DOF_TUPLE_IDS] = (_dof_tuple_ids.ct() > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\t_dof_tuple_ids ct: " << _dof_tuple_ids.ct() << "  ids: ";
  for(int i=0; i<_dof_tuple_ids.ct(); i++)
  {
    cout << setw(6) << _dof_tuple_ids[i];
  }
  cout << endl;
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif


  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_member_to_lower_cover(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(_lower_cover.ct() == 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_member_to_lower_cover " << endl;
#endif

  // Lower_cover:

  pod_index_type lmbr_id = xmbr_id.hub_pod();

  if(_poset->crg().cover_is_explicit(LOWER, lmbr_id))
  {
    // Lover cover for this member is explicit;
    // must be written to the file.

    index_space_iterator& itr = _poset->get_cover_id_space_iterator(LOWER, lmbr_id);
    while(!itr.is_done())
    {
      _lower_cover.push_back(itr.hub_pod());
      itr.next();
    }
    _poset->release_cover_id_space_iterator(itr);
  }
  else
  {
    // Lover cover for this member is implicit; do nothing.
  }

  _toc[HAS_LOWER_COVER] = (_lower_cover.ct() > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\t_lower_cover ct: " << _lower_cover.ct() << "  ids: ";
  for(int i=0; i<_lower_cover.ct(); i++)
  {
    cout << setw(6) << _lower_cover[i];
  }
  cout << endl;
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_member_to_upper_cover(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(_upper_cover.ct() == 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_member_to_upper_cover " << endl;
#endif

  // Upper_cover:

  pod_index_type lmbr_id = xmbr_id.hub_pod();

  if(_poset->crg().cover_is_explicit(UPPER, lmbr_id) && 
     (lmbr_id != BOTTOM_INDEX))
  {
    // Every explicit upper cover except bottom must be written to disk.

    index_space_iterator& itr = _poset->get_cover_id_space_iterator(UPPER, lmbr_id);
    while(!itr.is_done())

    {
      _upper_cover.push_back(itr.hub_pod());
      itr.next();
    }
    _poset->release_cover_id_space_iterator(itr);
  }
  else
  {
    // Either Upper cover for this member is implicit or
    // this member is bottom; do nothing.

    // Upper cover of bottom is not written to disk, it is
    // reconstructed on read, see transfer_lower_cover_to_member.
  }

  _toc[HAS_UPPER_COVER] = (_upper_cover.ct() > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\t_upper_cover ct: " << _upper_cover.ct() << "  ids: ";
  for(int i=0; i<_upper_cover.ct(); i++)
  {
    cout << setw(6) << _upper_cover[i];
  }
  cout << endl;
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_member_to_subposet_ids(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(_subposet_ids.ct() == 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_member_to_subposet_ids " << endl;
#endif

  // Transfer ids:

  // Iterate over all the subposets except the standard ones;
  // whole doesn't need to be stored and jims is in the toc.

  int lsp_min = _poset->standard_subposet_ct();
  int lsp_ub = scaffold().subposets().size();

  bool lhas_toc_subposet_ids = false;

  for(pod_index_type i = lsp_min; i<lsp_ub; i++)
  {
    subposet* lsp = scaffold().subposets()[i];

    if( lsp->contains_member(xmbr_id) )
    {
      int lsp_bit = i - lsp_min + SUBPOSET_BITS_BEGIN;
      if(lsp_bit < SUBPOSET_BITS_END)
      {
        // Haven't used all the subposet bits in the toc yet.

#ifdef DIAGNOSTIC_OUTPUT
        cout << "\tsetting bit " << lsp_bit
        << "  subposet id " << lsp->index()
        << "  name: " << lsp->name() << endl;
#endif

        _toc[lsp_bit] = true;
	lhas_toc_subposet_ids = true;
      }
      else
      {
        // Out of room in the toc.
        // Put subposet id into buffer to be
        // written explicitly into record

        _subposet_ids.push_back(i);
      }
    }
  }

  _toc[HAS_TOC_SUBPOSET_IDS] = lhas_toc_subposet_ids;
  _toc[HAS_SUBPOSET_IDS] = (_subposet_ids.ct() > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\t_subposet_ids ct: " << _subposet_ids.ct() << "  ids: ";
  for(int i=0; i<_subposet_ids.ct(); i++)
  {
    cout << setw(6) << _subposet_ids[i];
  }
  cout << endl;
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_member_to_eqv_ids(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(_eqv_ids.ct() == 0);
  require(has_equivalence_iterator());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_member_to_eqv_ids " << endl;
#endif

  // Transfer ids:

  // Iterate over the equivalence class of xmbr_id,
  // transferring to internal buffer.
  // Invariant of index_space_family ensures internal id
  // is always the representative of its equivalence class.

  scoped_index lrep_id(xmbr_id.hub_id());
  index_equivalence_iterator& litr = equivalence_iterator(lrep_id);
  while(!litr.is_done())
  {
    index_equivalence_iterator::member_type litem = litr.item();

    _eqv_ids.push_back(litem.first);
    _eqv_ids.push_back(litem.second);

    litr.next();
  }

  _toc[HAS_EQV_IDS] = (_eqv_ids.ct() > 0);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\t_eqv_ids ct: " << _eqv_ids.ct() << "  ids: ";
  for(int i=0; i<_eqv_ids.ct(); i++)
  {
    cout << setw(6) << _eqv_ids[i];
  }
  cout << endl;
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_member_to_names(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(_names.ct() == 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_member_to_names " << endl;
#endif

  const scoped_index& lext_id = scaffold().member_ext_id(xmbr_id);

  assertion(lext_id.is_valid());

  // Put all of its names in the name map.

  _poset->all_member_names(xmbr_id, _names);
  for(int i=0; i<_names.ct();i++)
  {
    scaffold().member_name_map().put_entry(lext_id.pod(), _names[i], false);
  }

  _names.set_ct(0);

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_interval_to_class_names(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(_toc[IS_INTERVAL]);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_interval_to_class_names" 
       << "  mbr id: " << xmbr_id
       << endl;
#endif

  if(_interval->is_interval_member(xmbr_id))
  {
    // This is the interval member itself.

    typedef poset_scaffold::member_class_names_type map_type;
    typedef map_type::mapped_type mapped_type;
    mapped_type lmapped;

    lmapped.first  = _interval->class_name();
    lmapped.second = _interval->size();

#ifdef DIAGNOSTIC_OUTPUT
    cout << "\tclass name: " << lmapped.first
	 << "  size: " << lmapped.second
	 << "  int id: " << xmbr_id.pod()
	 << endl;
#endif
    
    scaffold().member_class_names()[xmbr_id.hub_pod()] = lmapped;
  }


  // Postconditions:

  // Exit

  return;
}

void
sheaf::member_record::
convert_internal_buffer_to_external_buffer()
{
  // Preconditions:

  // Body:

  // Initialize the external buffer from the internal buffer.

  initialize_external_buffer();

  // Externalize all the data fields.

  size_t lnext_field_offset = 0;

  externalize_toc(lnext_field_offset);

  externalize_private_data_ct(lnext_field_offset);
  externalize_private_data(lnext_field_offset);

  externalize_dof_tuple_ids_ct(lnext_field_offset);
  externalize_dof_tuple_ids(lnext_field_offset);

  externalize_lower_cover_ct(lnext_field_offset);
  externalize_lower_cover(lnext_field_offset);

  externalize_upper_cover_ct(lnext_field_offset);
  externalize_upper_cover(lnext_field_offset);

  externalize_subposet_ids_ct(lnext_field_offset);
  externalize_subposet_ids(lnext_field_offset);

  externalize_eqv_ids(lnext_field_offset);

  // Now the external buffer is valid.

  put_is_external(true);

  // Postconditions:

  ensure(is_external());

  // Exit

  return;
}

///
void
sheaf::member_record::
initialize_external_buffer()
{
  // Preconditions:


  // Body:

  // Determine the size of the external buffer.

  _end_offset = 0;

  // Space for toc

  _end_offset += 1;

  // Space for private_data_ct.

  _end_offset += _toc[HAS_PRIVATE_DATA] ? 1 : 0;

  // Space for private data.

  _end_offset += _private_data.ct();

  // Space for dof_tuple_ids_ct.

  _end_offset += _toc[HAS_DOF_TUPLE_IDS] ? 1 : 0;

  // Space for dof tuple ids.

  _end_offset += _dof_tuple_ids.ct();

  // Space for lower_cover_ct

  _end_offset += _toc[HAS_LOWER_COVER] ? 1 : 0;

  // Space for lower_cover

  _end_offset += _lower_cover.ct();

  // Space for upper_cover_ct

  _end_offset += _toc[HAS_UPPER_COVER] ? 1 : 0;

  // Space for upper_cover

  _end_offset += _upper_cover.ct();

  // Space for subposet ids count.

  _end_offset += _toc[HAS_SUBPOSET_IDS] ? 1 : 0;

  // Space for subposet ids.

  _end_offset += _subposet_ids.ct();

  // Space for equivalent ids

  _end_offset += _eqv_ids.ct()  ;

  // Allocate the external buffer.
  // Buffer will be deleted in member_record_set::delete_external_buffers.
  /// @issue per member heap allocation is expensive.

  void* lbuf = new pod_index_type[_end_offset];

  put_buf(lbuf, _end_offset);

  // Buffer will not be deleted in destructor for this.

  put_delete_buffer(false);

  // The external buffer is allocated but not initialized.

  put_is_external(false);

  // Postconditions:

  ensure(!is_external());
  ensure(buf() != 0);

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_toc(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_internal());
  require(!type_map().toc_converter()->internal_size_greater());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif
  

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  /// @issue portability. Standard guarantees that rep of signed and
  /// unsigned ints is the same for the values they share. So the following
  /// cast, and possible subsequent conversion to some other signed rep,
  /// and recast to unsigned in internalize_toc will work as long as the
  /// toc stays within the shared values. But there's no portable way
  /// to ensure that, since we don't know what rep is being used.
  /// So we avoid the first and last bits, one or the other is the most
  /// likely to cause trouble, at least in 2's complement rep, depending
  /// on which endian the rep is.

  int_buf()[xnext_field_offset++] = static_cast<int>(_toc.to_ulong());

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + 1);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_private_data_ct(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_internal());
  require(!type_map().dof_tuple_id_converter()->internal_size_greater());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  // Put the dof tuple id ct and the dof tuple ids in the buffer.

  if(_toc[HAS_PRIVATE_DATA])
  {
    int_buf()[xnext_field_offset++] = _private_data.ct();
  }

  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_private_data(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_internal());
  require(!type_map().dof_tuple_id_converter()->internal_size_greater());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tprivate_data: " << _private_data << endl;
#endif

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  // Put the dof tuple id ct and the dof tuple ids in the buffer.

  if(_toc[HAS_PRIVATE_DATA])
  {
    int lct = _private_data.ct();
    for(int i=0; i<lct; ++i)
    {
      int_buf()[xnext_field_offset++] = _private_data[i];
    }
  }

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _private_data.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_dof_tuple_ids_ct(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_internal());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  // Put the dof tuple id ct and the dof tuple ids in the buffer.

  if(_toc[HAS_DOF_TUPLE_IDS])
  {
    int_buf()[xnext_field_offset++] = _dof_tuple_ids.ct();
  }

  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_dof_tuple_ids(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_internal());
  require(!type_map().dof_tuple_id_converter()->internal_size_greater());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tdof_tuple_ids: " << _dof_tuple_ids << endl;
#endif

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  // Put the dof tuple id ct and the dof tuple ids in the buffer.

  if(_toc[HAS_DOF_TUPLE_IDS])
  {
    int lct = _dof_tuple_ids.ct();
    for(int i=0; i<lct; ++i)
    {
      int_buf()[xnext_field_offset++] = _dof_tuple_ids[i];
    }
  }

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _dof_tuple_ids.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_lower_cover_ct(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_internal());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_LOWER_COVER])
  {
    int_buf()[xnext_field_offset++] = _lower_cover.ct();
  }


  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_lower_cover(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_internal());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tlower_cover: " << _lower_cover << endl;
#endif

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_LOWER_COVER])
  {
    int_type lct = _lower_cover.ct();
    for(int_type i=0; i<lct; ++i)
    {
      int_buf()[xnext_field_offset++] = _lower_cover[i];
    }
  }

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _lower_cover.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_upper_cover_ct(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_internal());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_UPPER_COVER])
  {
    int_buf()[xnext_field_offset++] = _upper_cover.ct();
  }


  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_upper_cover(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_internal());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tupper_cover: " << _upper_cover << endl;
#endif

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_UPPER_COVER])
  {
    int_type lct = _upper_cover.ct();
    for(int_type i=0; i<lct; ++i)
    {
      int_buf()[xnext_field_offset++] = _upper_cover[i];
    }
  }

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _upper_cover.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_subposet_ids_ct(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_internal());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_SUBPOSET_IDS])
  {
    int_buf()[xnext_field_offset++] = _subposet_ids.ct();
  }


  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_subposet_ids(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_internal());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tsubposet_ids: " << _subposet_ids << endl;
#endif

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_SUBPOSET_IDS])
  {
    int_type lids_ct = _subposet_ids.ct();
    for(int_type i=0; i<lids_ct; ++i)
    {
      int_buf()[xnext_field_offset++] = _subposet_ids[i];
    }
  }


  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _subposet_ids.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
externalize_eqv_ids(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_internal());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\teqv_ids: " << _eqv_ids << endl;
#endif

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_EQV_IDS])
  {
    int_type lct = _eqv_ids.ct();
    for(int_type i=0; i<lct; ++i)
    {
      int_buf()[xnext_field_offset++] = _eqv_ids[i];
    }
  }

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _eqv_ids.ct());
  ensure(xnext_field_offset == buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
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
sheaf::member_record::
internalize(hvl_t* xhdf_buffer, const scoped_index& xmbr_id)
{

  // Preconditions:

  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::internalize: member: " << xmbr_id << endl;
#endif

  // Map xmbr_id into internal and external scope.

  xmbr_id >> _mbr_id;
  xmbr_id >> _ext_id;

  // Initialize poset and interval variables.

  _poset = &scaffold().structure();
  _interval = _poset->crg().implicit_member(xmbr_id.hub_pod());

  // Initialize the external buffer from the HDF buffer.

  transfer_HDF_to_external_buffer(xhdf_buffer);

  // Convert the external buffer to internal format
  // and place the result in the internal buffer

  convert_external_buffer_to_internal_buffer();

  // Transfer the internal buffer to the member.

  transfer_internal_buffer_to_member(xmbr_id);

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_HDF_to_external_buffer(hvl_t* xbuf)
{
  // Preconditions:

  require(xbuf != 0);

  // Body:

  put_buf(xbuf->p, xbuf->len);
  _end_offset = xbuf->len;

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
sheaf::member_record::
convert_external_buffer_to_internal_buffer()
{
  // Preconditions:

  // Body:

  size_t lnext_field_offset = 0;

  // Internalize all the data fields.

  internalize_toc(lnext_field_offset);

  internalize_private_data_ct(lnext_field_offset);
  internalize_private_data(lnext_field_offset);

  internalize_dof_tuple_ids_ct(lnext_field_offset);
  internalize_dof_tuple_ids(lnext_field_offset);

  internalize_lower_cover_ct(lnext_field_offset);
  internalize_lower_cover(lnext_field_offset);

  internalize_upper_cover_ct(lnext_field_offset);
  internalize_upper_cover(lnext_field_offset);

  internalize_subposet_ids_ct(lnext_field_offset);
  internalize_subposet_ids(lnext_field_offset);

  internalize_eqv_ids(lnext_field_offset);

  // Now the internal buffer is valid.

  put_is_internal(true);

  // Postconditions:

  ensure(is_internal());

  // Exit

  return;
}


///
void
sheaf::member_record::
internalize_toc(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_external());
  require(!type_map().toc_converter()->external_size_greater());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  _toc = toc_type(static_cast<unsigned long long>(int_buf()[xnext_field_offset++]));

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + 1);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}


///
void
sheaf::member_record::
internalize_private_data_ct(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_external());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_PRIVATE_DATA])
  {
    pod_index_type lprivate_data_ct = int_buf()[xnext_field_offset++];
    _private_data.reserve(lprivate_data_ct);
    _private_data.set_ct(lprivate_data_ct);
  }
  else
  {
    _private_data.set_ct(0);
  }

  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
internalize_private_data(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_external());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_PRIVATE_DATA])
  {
    int_type lct = _private_data.ct();
    for(int i=0; i<lct; ++i)
    {
      _private_data[i] = int_buf()[xnext_field_offset++];
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tprivate_data: " << _private_data << endl;
#endif

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _private_data.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
internalize_dof_tuple_ids_ct(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_external());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_DOF_TUPLE_IDS])
  {
    pod_index_type ldof_tuple_ids_ct = int_buf()[xnext_field_offset++];
    _dof_tuple_ids.reserve(ldof_tuple_ids_ct);
    _dof_tuple_ids.set_ct(ldof_tuple_ids_ct);
  }
  else
  {
    _dof_tuple_ids.set_ct(0);
  }

  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
internalize_dof_tuple_ids(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_external());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_DOF_TUPLE_IDS])
  {
    int_type lct = _dof_tuple_ids.ct();
    for(int i=0; i<lct; ++i)
    {
      _dof_tuple_ids[i] = int_buf()[xnext_field_offset++];
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tdof_tuple_ids: " << _dof_tuple_ids << endl;
#endif

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _dof_tuple_ids.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
internalize_lower_cover_ct(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_external());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_LOWER_COVER])
  {
    int llower_cover_ct = int_buf()[xnext_field_offset++];
    _lower_cover.reserve(llower_cover_ct);
    _lower_cover.set_ct(llower_cover_ct);
  }
  else
  {
    _lower_cover.set_ct(0);
  }

  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}


///
void
sheaf::member_record::
internalize_lower_cover(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_external());
  require(unexecutable(_lower_cover_ct is internal));

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_LOWER_COVER])
  {
    int_type lct = _lower_cover.ct();
    for(int_type i=0; i<lct; ++i)
    {
      _lower_cover[i] = int_buf()[xnext_field_offset++];
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tlower_cover: " << _lower_cover << endl;
#endif

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _lower_cover.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}


///
void
sheaf::member_record::
internalize_upper_cover_ct(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_external());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_UPPER_COVER])
  {
    int lupper_cover_ct = int_buf()[xnext_field_offset++];
    _upper_cover.reserve(lupper_cover_ct);
    _upper_cover.set_ct(lupper_cover_ct);
  }
  else
  {
    _upper_cover.set_ct(0);
  }

  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}


///
void
sheaf::member_record::
internalize_upper_cover(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_external());
  require(unexecutable(_upper_cover_ct is internal));

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_UPPER_COVER])
  {
    int_type lct = _upper_cover.ct();
    for(int_type i=0; i<lct; ++i)
    {
      _upper_cover[i] = int_buf()[xnext_field_offset++];
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tupper_cover: " << _upper_cover << endl;
#endif

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _upper_cover.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}


///
void
sheaf::member_record::
internalize_subposet_ids_ct(size_t& xnext_field_offset)
{

  // Preconditions:

  require(is_external());
  require(xnext_field_offset <= buf_ub());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_SUBPOSET_IDS])
  {
    int lsubposet_ids_ct = int_buf()[xnext_field_offset++];
    _subposet_ids.reserve(lsubposet_ids_ct);
    _subposet_ids.set_ct(lsubposet_ids_ct);
  }
  else
  {
    _subposet_ids.set_ct(0);
  }


  // Postconditions:

  ensure(xnext_field_offset >= old_xnext_field_offset);
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}



///
void
sheaf::member_record::
internalize_subposet_ids(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_external());
  require(xnext_field_offset <= buf_ub());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_SUBPOSET_IDS])
  {
    size_t lids_ct = _subposet_ids.ct();
    for(size_t i=0; i< lids_ct; ++i)
    {
      _subposet_ids[i] = int_buf()[xnext_field_offset++];
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tsubposet_ids: " << _subposet_ids << endl;
#endif

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _subposet_ids.ct());
  ensure(xnext_field_offset <= buf_ub());

  // Exit

  return;
}



///
void
sheaf::member_record::
internalize_eqv_ids(size_t& xnext_field_offset)
{
  // Preconditions:

  require(is_external());
  require(xnext_field_offset <= buf_ub());

  // Body:

  define_old_variable(size_t old_xnext_field_offset = xnext_field_offset);

  if(_toc[HAS_EQV_IDS])
  {
    // Compute the count.

    size_t lct = _end_offset - xnext_field_offset;

    _eqv_ids.reserve(lct);
    _eqv_ids.set_ct(lct);
    for(size_t i=0; i<lct; ++i)
    {
      _eqv_ids[i] = int_buf()[xnext_field_offset++];
    }
  }
  else
  {
    _eqv_ids.set_ct(0);
  }


#ifdef DIAGNOSTIC_OUTPUT
  cout << "\teqv_ids: " << _eqv_ids << endl;
#endif

  // Postconditions:

  ensure(xnext_field_offset == old_xnext_field_offset + _eqv_ids.ct());
  ensure(xnext_field_offset == buf_ub());

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_internal_buffer_to_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

  // Transfer toc.

  transfer_toc_to_member(xmbr_id);

  if(_toc[IS_INTERVAL])
  {
    if(xmbr_id.pod() >= _poset->standard_member_ct())
    {
      // Transfer private data, id map data, and dof tuple ids.

      transfer_private_data_to_interval(xmbr_id);

      transfer_dof_tuple_ids_to_interval(xmbr_id);

      if(_interval->is_interval_member(xmbr_id))
      {
	// Finalize the initialization.

	_interval->finalize(*_poset);
      }
    }
    else
    {
      // The interval is a standard member.  Nothing to do, it has
      // already been initialized.
    }
  }
  else
  {
    // Just transfer dof tuple ids.

    transfer_dof_tuple_ids_to_member(xmbr_id);
  }

  // Transfer equivalent ids.

  transfer_eqv_ids_to_member(xmbr_id);

  // Transfer subposet ids;
  // must process subposets ids before lower cover
  // so we can test for lower bound.

  transfer_subposet_ids_to_member(xmbr_id);

  // Transfer the upper cover.

  transfer_upper_cover_to_member(xmbr_id);

  // Transfer the lower cover.

  poset_bounds& lrow_bounds  = scaffold().row_bounds();

  if(lrow_bounds.bounded_below() &&
     _poset->bound_contains_member(lrow_bounds, false, xmbr_id))
  {
    // The current member is on the lower bound.
    // Truncate descent by not transferring links.
    // Member will be linked to bottom by ensure_lattice_invariant() const
    // called from end_jim_edit_mode().
    // Links are still external, so leave member not resident

    _is_resident = false;
  }
  else
  {
    // The current member is above the lower bound.
    // Transfer lower cover into member and continue descent.

    transfer_lower_cover_to_member(xmbr_id);
    _is_resident = true;
  }

  // Names.

  transfer_names_to_member(xmbr_id);

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_toc_to_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_toc_to_member" << endl;
  cout << "\ttoc: " << _toc << " = " << _toc.to_ulong() << endl;
#endif

  // Is_jim and Dof tuple id:

  if( xmbr_id.pod() >= _poset->standard_member_ct() )
  {
    // The current member is not a standard member;
    // process _toc.is_jim() and _dof_tuple_id.

    if(_toc[IS_JIM])
    {
      // The current member is a jim;
      // insert it in the jims subposet.

      _poset->jims().insert_member(xmbr_id);
    }
    else
    {
      // The current member is a jrm.

      // Note that a member in memory with down set on disk is a jim
      // until its down set is read in and it becomes a jrm.

      // Make sure the current member is a jrm,
      // remove it from the jims subposet;
      // won't hurt if it isn't in it.

      _poset->jims().remove_member(xmbr_id);
    }
  }
  else
  {
    // The current member is a standard member and
    // it's jim status is already set; do nothing.
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_private_data_to_interval(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(scaffold().structure().crg().implicit_member(xmbr_id.hub_pod()) != 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_private_data_to_interval " << endl;
  cout << "\txmbr_id: " << xmbr_id << endl;
  cout << "\t_private_data ct: " << _private_data.ct() << "  ids: ";
  for(int i=0; i<_private_data.ct(); i++)
  {
    cout << setw(6) << _private_data[i];
  }
  cout << endl;
#endif

  if(_interval->is_interval_member(xmbr_id))
  {
    _interval->put_private_data(_private_data);
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_dof_tuple_ids_to_interval(const scoped_index& xmbr_id)
{
  // Preconditions:

  require(scaffold().structure().crg().implicit_member(xmbr_id.hub_pod()) != 0);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_dof_tuple_id_to_interval " << endl;
#endif

  // Get some convenient references

  interval_index_space_handle& ldof_tuple_space =
    scaffold().dof_tuple_id_space();

  pod_index_type lint_dof_tuple_pod;

  // Dof tuple ids.

  int ldof_tuple_ct = _dof_tuple_ids.ct();

  if(_interval->is_interval_member(xmbr_id))
  {
    // Translate external ids to internal ids.

    block<pod_index_type> ldof_tuple_ids;
    ldof_tuple_ids.reserve(ldof_tuple_ct);
    ldof_tuple_ids.set_ct(ldof_tuple_ct);

    for(int i=0; i<_dof_tuple_ids.ct(); ++i)
    {
      pod_index_type lext_dof_tuple_id = _dof_tuple_ids[i];

      scoped_index ldof_tuple_id(ldof_tuple_space, lext_dof_tuple_id);

      if(!ldof_tuple_id.in_scope())
      {
        // This is the first time we've encountered this dof tuple id,
        // create the dof tuple.

        ldof_tuple_id = new_row_dof_tuple(lext_dof_tuple_id);

        // Put it in the map and in the read queue.

        ldof_tuple_space.insert(lext_dof_tuple_id, ldof_tuple_id);

        host().dof_tuple_records().queue().enqueue(lext_dof_tuple_id);
      }

      // Put the internal dof tuple id back into _dof_tuple_ids.

      ldof_tuple_ids[i] = ldof_tuple_id.hub_pod();
    }

    // Initialize the dof tuple ids in the interval.

    _interval->initialize_dof_tuple_ids(ldof_tuple_ids);
  }


  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::member_record::
transfer_dof_tuple_ids_to_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_dof_tuple_ids_to_member " << endl;
#endif

  // Get some convenient references

  interval_index_space_handle& ldof_tuple_space =
    scaffold().dof_tuple_id_space();

  if( xmbr_id.pod() >= _poset->standard_member_ct() )
  {
    // The current member is not a standard member.

    // A member can have a dof tuple whether or not it is considered
    // a jim in the current version. _dof_tuple_id contains the
    // external dof tuple id in internal format.

    if(_dof_tuple_ids.ct() > 0)
    {
      // This member has a dof tuple; get the scoped id.

      scoped_index ldof_tuple_id(ldof_tuple_space, _dof_tuple_ids[0]);

      if(!ldof_tuple_id.in_scope())
      {
        // This is the first time we've encountered this dof tuple id,
        // create the dof tuple.

	ldof_tuple_id = new_row_dof_tuple(_dof_tuple_ids[0]);

        if(scaffold().external_schema().index() == BOTTOM_INDEX)
        {
          // External dof tuple is empty.
          // Don't put emtpy id in read queue - nothing to read.

          if( scaffold().structure().schema().index()  == BOTTOM_INDEX)
          {
            // Internal dof tuple is also empty.
            // Every member should share the unique empty dof map.
            // Since external dof tuple ids all == empty id
            // putting empty id in the map will ensure shared map.

	    ldof_tuple_space.insert(_dof_tuple_ids[0], ldof_tuple_id);
          }
          else
          {
            // Internal dof map is not empty.
            // Every member should have its own dof map.
            // Don't put empty id in map; empty id will
            // always be treated as not previously seen
            // and a new dof map will be created.
          }
        }
        else
        {
          // External dof tuple is not empty.
          // Put it in the map and in the read queue.

          /// @error if internal dof map is empty, why read the
          /// external dof map?

	  ldof_tuple_space.insert(_dof_tuple_ids[0], ldof_tuple_id);

#ifdef DIAGNOSTIC_OUTPUT
          cout << "\tqueuing dof tuple id: " << ldof_tuple_id << endl;
#endif

          host().dof_tuple_records().queue().enqueue(_dof_tuple_ids[0]);
        }
      }

      // Set the dof tuple into the member.

      _poset->put_member_dof_tuple_id(xmbr_id, ldof_tuple_id, false);

#ifdef DIAGNOSTIC_OUTPUT
      cout << "\tsetting dof tuple id for member: " << xmbr_id.hub_pod()
	   << "  to " << ldof_tuple_id.hub_pod()
	   << endl;
#endif
    }
  }
  else
  {
    // The current member is a standard member
    // and it's dof tuple id is already set;
    // do nothing.
  }



  // Postconditions:

  // Exit

  return;
}

const sheaf::scoped_index&
sheaf::member_record::
new_row_dof_tuple(pod_index_type xext_dof_tuple_pod)
{
  // Preconditions:

  require(scaffold().structure().state_is_read_write_accessible());
  require(scaffold().dof_tuple_types().find(xext_dof_tuple_pod) !=
          scaffold().dof_tuple_types().end());
  require(scaffold().dof_tuple_class_names().find(xext_dof_tuple_pod) !=
          scaffold().dof_tuple_class_names().end());
  require(scaffold().dof_tuple_schema_ids().find(xext_dof_tuple_pod) !=
          scaffold().dof_tuple_schema_ids().end());
  require(scaffold().dof_tuple_schema_versions().find(xext_dof_tuple_pod) !=
          scaffold().dof_tuple_schema_versions().end());


  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::new_row_dof_tuple " << endl;
#endif

  define_old_variable(int old_row_dof_tuple_ct = scaffold().structure().row_dof_tuple_ct());

  //  poset_state_handle* lposet = &(scaffold().structure());

  // Get the dof tuple type.
  // The dof tuple type map was populated when the dof_tuple_types record
  // in the attributes record set was read. It must contain an entry for xext_dof_tuple_pod.

  dof_tuple_type ltype_id = scaffold().dof_tuple_types().find(xext_dof_tuple_pod)->second;

  // Get the dof tuple class names.

  string lclass_name =
    scaffold().dof_tuple_class_names().find(xext_dof_tuple_pod)->second;

  // Get the dof tuple schema internal id.

  pod_index_type lschema_int_id =
    scaffold().dof_tuple_schema_int_id(xext_dof_tuple_pod);

  // Get the dof tuple schema version

  int lschema_ver = scaffold().dof_tuple_schema_version(xext_dof_tuple_pod);


#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tclass name= " << lclass_name
       << "  schema id= " << lschema_int_id
       << "  schema version= " << lschema_ver
       << endl;
#endif

  /// @hack The external dof tuple can only initialize the internal dof tuple
  /// on the meet of the external and internal schema. We can't currently
  /// afford to compute the meet, so we only deal with two special cases:
  /// (1) internal >= external and (2) internal <= external.

  /// @hack If internal > external, there is the additional issue of whether
  /// to create the internal tuple as a total section and only partially
  /// initialize it or create it as a partial section. For the namespace we
  /// want to do the former and for section spaces we typically want to do
  /// the latter. We don't currently have any mechanism for the client to
  /// specify which to do, so we always create the partial section.
  /// See also dof_tuple_record_set::populate_internal_dof_map where we use this.
  /// We patch this up for namespace_poset in storage_agent::begin_read_transaction.

  schema_poset_member& lposet_schema = _poset->schema();
  pod_index_type ltuple_schema_id;
  if(lposet_schema.ge(lschema_int_id))
  {
    // External schema is less than internal schema,
    // use external schema.

    ltuple_schema_id = lschema_int_id;
  }
  else if(lposet_schema.le(lschema_int_id))
  {
    // Internal schema is less than external schema;
    // use internal schema.

    ltuple_schema_id = lposet_schema.index();
  }
  else
  {
    // Internal and external schema are incomparable;
    // We can't handle this case currently.

    post_fatal_error_message("Incomparable internal and external schema not supported.");
  }

  // Create a dof map of the proper type and initialize it..

  poset_dof_map* lmap = poset_dof_map::new_dof_map(lclass_name, ltype_id);
  lmap->init_row_dof_map(_poset, ltuple_schema_id, lschema_ver);

  // Must have created a dof tuple by now.

  assertion(lmap != 0);

  // Insert the dof tuple in the poset state.

  scaffold().structure().state_obj()->table()->put_row_dof_tuple(lmap);

  const scoped_index& result = lmap->index();

  // Postconditions:

  ensure(scaffold().structure().row_dof_tuple_ct() == old_row_dof_tuple_ct+1);
  ensure(scaffold().structure().contains_row_dof_tuple(result));

  // Exit

  return result;
}


///
void
sheaf::member_record::
transfer_lower_cover_to_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_lower_cover_to_member" << endl;
  cout << "\tmbr: " << xmbr_id << "  lower_cover ct: " << _lower_cover.ct() << endl;
#endif

  if(_lower_cover.ct() > 0)
  {
    pod_index_type lmbr_id = xmbr_id.hub_pod();

    // This record specifies an explicit cover set;
    // it should replace any temporary or implicit lower
    // cover the member already has.

    // Get some convenient references

    poset_crg_state& lcrg = _poset->crg();
    pod_index_type lint_lesser;

    // Force the cover set for xmbr_id to be explicit and empty.

    _poset->crg().clear_cover(LOWER, lmbr_id);

    // Transfer the lower cover from the record into the member.

    for(int i=0; i<_lower_cover.ct(); i++)
    {
      // Get the internal id of the lesser end of link;

      lint_lesser = _lower_cover[i];

      if(!lcrg.contains_member(lint_lesser))
      {
	// The lesser member has not yet been created;
	// create it and enter it into the index map.

	new_member(lint_lesser);
      }

      _poset->crg().insert_cover_member(lint_lesser, LOWER, lmbr_id);

#ifdef DIAGNOSTIC_OUTPUT
      cout << "\tinserted: " << lint_lesser  << " in lower cover of: " << xmbr_id << endl;
#endif

      if(lint_lesser == BOTTOM_INDEX)
      {
	// Add xmbr_id to the upper cover of bottom.

	_poset->crg().insert_cover_member(lmbr_id, UPPER, BOTTOM_INDEX);
      }

    } // end for
  } // end if

  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::member_record::
transfer_upper_cover_to_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_upper_cover_to_member" << endl;
  cout << "\tmbr: " << xmbr_id << "  upper_cover ct: " << _upper_cover.ct() << endl;
#endif

  if(_upper_cover.ct() > 0)
  {
    pod_index_type lmbr_id = xmbr_id.hub_pod();

    // This record specifies an explicit cover set;
    // it should replace any temporary or implicit upper
    // cover the member already has.

    // Force the cover set for xmbr_id to be explicit and empty.

    _poset->crg().clear_cover(UPPER, lmbr_id);

    // Transfer the upper cover from the record into the member.

    for(int i=0; i<_upper_cover.ct(); i++)
    {
      // Insert the internal id in the cover.

      _poset->crg().insert_cover_member(_upper_cover[i], UPPER, lmbr_id);

#ifdef DIAGNOSTIC_OUTPUT
      cout << "\tinserted: " << _upper_cover[i]  << " in upper cover of: " << xmbr_id << endl;
#endif

    } // end for
  } // end if

  // Postconditions:

  // Exit

  return;
}

void
sheaf::member_record::
new_member(pod_index_type xmbr_id)
{
  // Preconditions:

  require(scaffold().structure().in_jim_edit_mode());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tmember_record::new_member id: " << xmbr_id << endl;
#endif

  define_old_variable(int old_member_ct = scaffold().structure().member_ct());

  // Get the member class name and parameters.

  typedef poset_scaffold::member_class_names_type class_names_type;
  typedef class_names_type::const_iterator itr_type;

  class_names_type& lclass_names = scaffold().member_class_names();
  itr_type litr = lclass_names.find(xmbr_id);

  if(litr != lclass_names.end())
  {
    // Member is a interval member, create the proper type.

#ifdef DIAGNOSTIC_OUTPUT
    cout << "\tcreating interval member" << endl
	 << "\tmbr_id= " << xmbr_id
	 << "\tclass name= " << litr->second.first
	 << "\tsize: " << litr->second.second
	 << endl;
#endif

    _poset->new_member_interval(xmbr_id, litr->second.first, litr->second.second);
  }
  else
  {
    // Member is an ordinary, explicit member, no member object.
    // Create it as a jrm; will make it into a jim, if needed,
    // when we process its member record.

#ifdef DIAGNOSTIC_OUTPUT
    cout << "\tcreating ordinary member" << endl;
#endif

    _poset->new_member(xmbr_id, false, 0, false);
  }

  // Postconditions:

  ensure(scaffold().structure().member_ct() > old_member_ct);
  ensure(scaffold().structure().contains_member(xmbr_id));

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_subposet_ids_to_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_subposet_ids_to_member" << endl;
#endif

  // Get some convenient references

  int lsp_min = _poset->standard_subposet_ct();

  // Transfer ids stored as bits in toc.

  for(int i=SUBPOSET_BITS_BEGIN; i< SUBPOSET_BITS_END; ++i)
  {
    if(_toc[i])
    {
      pod_index_type lsp_id = i - SUBPOSET_BITS_BEGIN + lsp_min;

      subposet* lsp = scaffold().subposets()[lsp_id];

#ifdef DIAGNOSTIC_OUTPUT
      cout << "\tgetting bit " << i
      << "  subposet id " << lsp->index()
      << "  name: " << lsp->name() << endl;
#endif

      lsp->insert_member(xmbr_id);
    }
  }

  // Transfer ids stored explicit in record:

  for(int i = 0; i<_subposet_ids.ct(); i++)
  {

#ifdef DIAGNOSTIC_OUTPUT
    cout << "\ti: " << i << " sp_id: " << _subposet_ids[i] << endl;
#endif

    subposet* lsp = scaffold().subposets()[_subposet_ids[i]];
    lsp->insert_member(xmbr_id);
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_eqv_ids_to_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "member_record::transfer_eqv_ids_to_member" << endl;
#endif

  // Transfer ids:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "\tmbr: " << xmbr_id
  << " eqv_ids.ct: " << _eqv_ids.ct() << endl;
#endif


  for(int i = 0; i<_eqv_ids.ct(); i+=2)
  {
    mutable_index_space_handle* lid_space = scaffold().id_spaces()[_eqv_ids[i]];
    pod_index_type lext_id = _eqv_ids[i+1];
    pod_index_type lint_id = xmbr_id.hub_pod();

    /// @hack the following relatively expensive test
    /// on every id of every member of every poset
    /// appears to be necessary only because of
    /// the entries for the standard members in the
    /// member id space of the namespace poset.

    /// @todo deal with this more efficiently somehow.

    /// @issue There is no way to be sure if the id map is open.  Most id maps
    /// are initially open because that are created in id_space_names_record.
    /// However, members_poset_id map is closed for posets that have standard
    /// members due to calls to namespace_poset::insert_poset().  This is
    /// inefficient and needs addressed.

      if(!lid_space->contains(lext_id, lint_id))
    {
      // Map does not contain the entry; enter it now.

#ifdef DIAGNOSTIC_OUTPUT
      cout << "\ti: " << i
      << "  internal id: " << lint_id
      << "  external id: " << lext_id
      << " ... making entry in map."
      << endl;
#endif

      lid_space->insert(lext_id, lint_id);
    }
    else
    {
      // Map already contains the entry; do nothing.

#ifdef DIAGNOSTIC_OUTPUT
      cout << "\ti: " << i
      << "  internal id: " << lint_id
      << "  external id: " << lext_id
      << " ... entry already exists, skipping."
      << endl;
#endif

    }
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_record::
transfer_names_to_member(const scoped_index& xmbr_id)
{
  // Preconditions:

  // Body:

  const scoped_index& lext_id = scaffold().member_ext_id(xmbr_id);

  assertion(lext_id.is_valid());

#ifdef DIAGNOSTIC_OUTPUT
  cout << "names for member ext id: " << lext_id << " int id: " << xmbr_id << ":" << endl;
#endif

  // Set its names, if it has any.

  typedef poset_scaffold::member_name_map_type member_name_map_type;
  typedef member_name_map_type::name_list_type name_list_type;
  typedef member_name_map_type::const_name_iterator itr_type;
  
  member_name_map_type& lname_map = scaffold().member_name_map();
  name_list_type lname_list = lname_map.all_names(lext_id.pod());

  for(itr_type lname_itr = lname_list.begin(); lname_itr != lname_list.end(); ++lname_itr)
  {

#ifdef DIAGNOSTIC_OUTPUT
    cout << "\t" << *lname_itr << endl;
#endif

    if(!_poset->member_has_name(xmbr_id, *lname_itr))
    {
      _poset->put_member_name(xmbr_id, *lname_itr, false, false);
    }
  }

  // Postconditions:

  // Exit

  return;
}




// ===========================================================
// ANY FACET
// ===========================================================


///
sheaf::member_record*
sheaf::member_record::
clone() const
{
  member_record* result;

  // Preconditions:

  // Body:

  result = new member_record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
bool
sheaf::member_record::
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
sheaf::member_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const member_record*>(other) != 0;

  // Postconditions:

  return result;

}

