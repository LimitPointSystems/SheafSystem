// $RCSfile: implicit_crg_range.cc,v $ $Revision: 1.25 $ $Date: 2013/03/13 00:59:06 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class implicit_crg_range.

#include "implicit_crg_range.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "factory.h"
#include "index_space_collection.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "interval_index_space_state.h"
#include "poset_state_handle.h"
#include "singleton_index_space_state.h"
#include "std_iomanip.h"
#include "std_sstream.h"
#include "block.h"
#include "block.impl.h"

// ===========================================================
// IMPLICIT_CRG_RANGE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::implicit_crg_range::
implicit_crg_range()
{
  _id_spaces = 0;

  _id_spaces_initialized = false;
  _local_id_space_initialized = false;
  _range_member_id_space_initialized = false;
  _private_data_initialized = false;
  _dof_tuple_ids_initialized = false;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());
}

sheaf::implicit_crg_range::
~implicit_crg_range()
{
  // Preconditions:

  // Body:

  // Release the explicit lower cover handles.

  explicit_cover_map_type::iterator le_itr;

  for(le_itr = _explicit_lower_cover_map.begin();
      le_itr != _explicit_lower_cover_map.end();
      ++le_itr)
  {
    _id_spaces->release_id_space(*le_itr->second);
  }

  // Release the explicit upper cover handles.

  for(le_itr = _explicit_upper_cover_map.begin();
      le_itr != _explicit_upper_cover_map.end();
      ++le_itr)
  {
    _id_spaces->release_id_space(*le_itr->second);
  }

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// RANGE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::pod_index_type
sheaf::implicit_crg_range::
begin() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.offset();
}

void
sheaf::implicit_crg_range::
begin(scoped_index& result) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  result.put(hub_id_space(), begin());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::implicit_crg_range::
implicit_begin() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.offset()+1;
}

void
sheaf::implicit_crg_range::
implicit_begin(scoped_index& result) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  result.put(hub_id_space(), implicit_begin());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::implicit_crg_range::
end() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.offset() + _local_id_space.end();
}

void
sheaf::implicit_crg_range::
end(scoped_index& result) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  result.put(hub_id_space(), end());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::implicit_crg_range::
range_member() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return begin();
}

void
sheaf::implicit_crg_range::
range_member(scoped_index& result) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  begin(result);

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

bool
sheaf::implicit_crg_range::
is_range_member(pod_index_type xindex) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return (_local_id_space.offset() == xindex);
}

bool
sheaf::implicit_crg_range::
is_range_member(const scoped_index& xindex) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return is_range_member(xindex.hub_pod());
}

sheaf::size_type
sheaf::implicit_crg_range::
size() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.ct();
}

bool
sheaf::implicit_crg_range::
contains_member(pod_index_type xindex) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.contains_hub(xindex);
}

bool
sheaf::implicit_crg_range::
contains_member(const scoped_index& xindex) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return contains_member(xindex.hub_pod());
}

const sheaf::index_space_family&
sheaf::implicit_crg_range::
id_spaces() const
{
  // Preconditions:

  require(id_spaces_initialized());

  // Body:

  return *_id_spaces;
}

const sheaf::hub_index_space_handle&
sheaf::implicit_crg_range::
hub_id_space() const
{
  // Preconditions:

  require(id_spaces_initialized());

  // Body:

  return _id_spaces->hub_id_space();
}

void
sheaf::implicit_crg_range::
initialize_id_spaces(index_space_family& xid_spaces)
{
  // Preconditions:

  // Body:

  _id_spaces = &xid_spaces;
  _id_spaces_initialized = true;

  // Postconditions:

  ensure(id_spaces_initialized());

  // Exit:

  return;
}

bool
sheaf::implicit_crg_range::
id_spaces_initialized() const
{
  return _id_spaces_initialized;
}

// PROTECTED DATA MEMBERS

sheaf::index_space_collection*
sheaf::implicit_crg_range::
collection(pod_index_type xid)
{
  // Preconditions:

  require(id_spaces().contains(xid));

  // Body:

  index_space_collection* result = _id_spaces->collection(xid);

  // Posconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// LOCAL ID SPACE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

string
sheaf::implicit_crg_range::
local_id_space_name(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  string result(poset_path::make_reserved_name("", xindex, "_local_ids"));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::primary_index_space_handle&
sheaf::implicit_crg_range::
local_id_space() const
{
  // Preconditions:

  require(local_id_space_initialized());

  // Body:

  return _local_id_space;
}

void
sheaf::implicit_crg_range::
initialize_local_id_space(const index_space_handle& xlocal_id_space)
{
  // Preconditions:

  // Body:

  // Initialize the local id space.

  _local_id_space.attach_to(xlocal_id_space);
  _local_id_space_initialized = true;

  // Initialize the range member id space.

  initialize_range_member_id_space();

  // Postconditions:

  ensure(local_id_space_initialized());
  ensure(range_member_id_space_initialized());

  // Exit:

  return;
}

bool
sheaf::implicit_crg_range::
local_id_space_initialized() const
{
  return _local_id_space_initialized;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// RANGE MEMBER ID SPACE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

string
sheaf::implicit_crg_range::
range_member_id_space_name(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  string result(poset_path::make_reserved_name("", xindex, "_range_member"));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::singleton_index_space_handle&
sheaf::implicit_crg_range::
range_member_id_space() const
{
  // Preconditions:

  require(range_member_id_space_initialized());

  // Body:

  return _range_member_id_space;
}

void
sheaf::implicit_crg_range::
initialize_range_member_id_space()
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());

  // Body:

  arg_list largs =
    singleton_index_space_state::make_arg_list(range_member());

  pod_index_type lspace_id =
    _id_spaces->new_secondary_state(range_member_id_space_name(range_member()),
				    "singleton_index_space_state",
				    largs, false);

  _range_member_id_space.attach_to(id_spaces(), lspace_id);

  _range_member_id_space_initialized = true;

  // Postconditions:

  ensure(range_member_id_space_initialized());

  // Exit:

  return;
}

bool
sheaf::implicit_crg_range::
range_member_id_space_initialized() const
{
  return _range_member_id_space_initialized;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// COVER_SET FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
sheaf::implicit_crg_range::
cover_is_explicit(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  // A cover set is explicit if there is a entry for it
  // in the appropriate explicit cover map (all entries are non-null).
  // Note that a cover set can be both implicit and explicit at the same time.

  const explicit_cover_map_type* lmap = explicit_cover_map(xlower);
  return lmap->find(xmbr_index) != lmap->end();
}

bool
sheaf::implicit_crg_range::
cover_is_explicit(bool xlower, const scoped_index& xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  bool result = cover_is_explicit(xlower, xmbr_index.hub_pod());

  return result;
}

/// @todo Remove.

// // $$SCRIBBLE: implicit-cover-reorganization
// // Implemented abstract cover set functions.

// sheaf::cover_set_iterator
// sheaf::implicit_crg_range::
// cover_iterator(bool xlower, pod_index_type xmbr_index) const
// {
//   cover_set_iterator result;

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* lcover = explicit_cover_set(xlower, xmbr_index);
//   if(lcover != 0)
//   {
//     // Member is explicit.

//     result = lcover->iterator();
//   }
//   else
//   {
//     // Member is implicit.

//     result = implicit_cover_iterator(xlower, xmbr_index);
//   }

//   // Postconditions:

//   ensure(cover_is_explicit(xlower, xmbr_index) != result.is_implicit());

//   // Exit:

//   return result;
// }

// sheaf::cover_set_iterator
// sheaf::implicit_crg_range::
// cover_iterator(bool xlower, const scoped_index& xmbr_index) const
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   return cover_iterator(xlower, xmbr_index.hub_pod());
// }

// bool
// sheaf::implicit_crg_range::
// cover_contains_iterator(bool xlower,
// 			pod_index_type xmbr_index,
// 			const cover_set_iterator& xitr) const
// {
//   bool result;

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* lcover = explicit_cover_set(xlower, xmbr_index);
//   if(lcover != 0)
//   {
//     // Member is explicit.

//     result = lcover->contains_iterator(xitr);
//   }
//   else
//   {
//     // Member is implicit.

//     result = implicit_cover_contains_iterator(xlower, xmbr_index, xitr);
//   }

//   // Postconditions:

//   // Exit:

//   return result;
// }

// bool
// sheaf::implicit_crg_range::
// cover_contains_iterator(bool xlower,
// 			const scoped_index& xmbr_index,
// 			const cover_set_iterator& xitr) const
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   return cover_contains_iterator(xlower, xmbr_index.hub_pod(), xitr);
// }

// bool
// sheaf::implicit_crg_range::
// cover_is_empty(bool xlower, pod_index_type xmbr_index) const
// {
//   bool result;

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* lcover = explicit_cover_set(xlower, xmbr_index);
//   if(lcover != 0)
//   {
//     // Member is explicit.

//     result = lcover->is_empty();
//   }
//   else
//   {
//     // Member is implicit.

//     result = implicit_cover_is_empty(xlower, xmbr_index);
//   }

//   // Postconditions:

//   // Exit:

//   return result;
// }

// bool
// sheaf::implicit_crg_range::
// cover_is_empty(bool xlower, const scoped_index& xmbr_index) const
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   return cover_is_empty(xlower, xmbr_index.hub_pod());
// }

// bool
// sheaf::implicit_crg_range::
// cover_is_singleton(bool xlower, pod_index_type xmbr_index) const
// {
//   bool result;

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* lcover = explicit_cover_set(xlower, xmbr_index);
//   if(lcover != 0)
//   {
//     // Member is explicit.

//     result = lcover->is_singleton();
//   }
//   else
//   {
//     // Member is implicit.

//     result = implicit_cover_is_singleton(xlower, xmbr_index);
//   }

//   // Postconditions:

//   // Exit:

//   return result;
// }

// bool
// sheaf::implicit_crg_range::
// cover_is_singleton(bool xlower, const scoped_index& xmbr_index) const
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   return cover_is_singleton(xlower, xmbr_index.hub_pod());
// }

// sheaf::size_type
// sheaf::implicit_crg_range::
// cover_size(bool xlower, pod_index_type xmbr_index) const
// {
//   size_type result;

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* lcover = explicit_cover_set(xlower, xmbr_index);
//   if(lcover != 0)
//   {
//     // Member is explicit.

//     result = lcover->size();
//   }
//   else
//   {
//     // Member is implicit.

//     result = implicit_cover_size(xlower, xmbr_index);
//   }

//   // Postconditions:

//   // Exit:

//   return result;
// }

// sheaf::size_type
// sheaf::implicit_crg_range::
// cover_size(bool xlower, const scoped_index& xmbr_index) const
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   return cover_size(xlower, xmbr_index.hub_pod());
// }

// bool
// sheaf::implicit_crg_range::
// cover_contains_member(bool xlower,
// 		      pod_index_type xmbr_index,
// 		      pod_index_type xother_index) const
// {
//   bool result;

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* lcover = explicit_cover_set(xlower, xmbr_index);
//   if(lcover != 0)
//   {
//     // Member is explicit.

//     result = lcover->contains_member(xother_index);
//   }
//   else
//   {
//     // Member is implicit.

//     result = implicit_cover_contains_member(xlower, xmbr_index, xother_index);
//   }

//   // Postconditions:

//   // Exit:

//   return result;
// }

// bool
// sheaf::implicit_crg_range::
// cover_contains_member(bool xlower,
// 		      const scoped_index& xmbr_index,
// 		      const scoped_index& xother_index) const
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   return cover_contains_member(xlower,
// 			       xmbr_index.hub_pod(),
// 			       xother_index.hub_pod());
// }

// sheaf::pod_index_type
// sheaf::implicit_crg_range::
// first_cover_member(bool xlower, pod_index_type xmbr_index) const
// {
//   pod_index_type result;

//   // Preconditions:

//   require(!cover_is_empty(xlower, xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* lcover = explicit_cover_set(xlower, xmbr_index);
//   if(lcover != 0)
//   {
//     // Member is explicit.

//     result = lcover->first_member();
//   }
//   else
//   {
//     // Member is implicit.

//     result = implicit_first_cover_member(xlower, xmbr_index);
//   }

//   // Postconditions:

//   // Exit:

//   return result;
// }

// PROTECTED DATA MEMBERS

const sheaf::index_space_handle&
sheaf::implicit_crg_range::
cover_id_space(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  const index_space_handle* result;

  // Check for an explicit cover id space.

  explicit_cover_map_type::const_iterator litr =
    explicit_cover_map(xlower)->find(xmbr_index);

  if(litr != explicit_cover_map(xlower)->end())
  {
    // There is an explicit cover id space, return it.

    result = litr->second;
  }
  else
  {
    // There is no explicit cover id space, get the implicit cover map.

    result = &implicit_cover_id_space(xlower, xmbr_index);
  }

  // Postconditions:

  // Exit:

  return *result;
}

sheaf::mutable_index_space_handle&
sheaf::implicit_crg_range::
force_explicit_cover(bool xlower, pod_index_type xmbr_index, bool xinitialize)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  mutable_index_space_handle* result;
  
  explicit_cover_map_type::const_iterator litr =
    explicit_cover_map(xlower)->find(xmbr_index);

  if(litr != explicit_cover_map(xlower)->end())
  {
    // There is already an explicit cover id space, return it.
    
    result = litr->second;
  }
  else
  {
    // There is no explicit cover id space, create it.

    result = &new_explicit_cover(xlower, xmbr_index, xinitialize);
  }
      

  // Postconditions:

  // Exit:

  return *result;
}

const sheaf::index_space_handle&
sheaf::implicit_crg_range::
implicit_cover_id_space(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  index_space_handle* result = 0; // Silence the compiler.

  is_abstract();

  // Postconditions:

  // Exit:

  return *result;
}

sheaf::interval_index_space_handle&
sheaf::implicit_crg_range::
new_explicit_cover(bool xlower, pod_index_type xmbr_index, bool xinitialize)
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(!cover_is_explicit(xlower, xmbr_index));

  // Body:

  /// @todo Could remove the need to store explicit covers in the private data
  ///       if this id space is persistent.

  pod_index_type lspace_id =
    _id_spaces->new_secondary_state(poset_crg_state::cover_name(xlower, xmbr_index),
				    "interval_index_space_state",
				    interval_index_space_state::make_arg_list(true),
				    false);

  interval_index_space_handle& result =
    _id_spaces->get_id_space<interval_index_space_handle>(lspace_id);

  if(xinitialize)
  {
    // Initialize the id space to the implicit members.

    initialize_explicit_cover(xlower, xmbr_index, result);
  }
  
  // Insert explicit covre into the map.

  (*explicit_cover_map(xlower))[xmbr_index] = &result;

  // Postconditions:

  ensure(cover_is_explicit(xlower, xmbr_index));
  ensure(result.name() == poset_crg_state::cover_name(xlower, xmbr_index));

  // Exit:

  return result;
}

void
sheaf::implicit_crg_range::
initialize_explicit_cover(bool xlower,
			  pod_index_type xmbr_index,
			  interval_index_space_handle& xcover) const
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(!cover_is_explicit(xlower, xmbr_index));

  // Body:

  define_old_variable(size_type old_cover_ct = cover_id_space(xlower, xmbr_index).ct());

  is_abstract();

  // Postconditions:

  ensure(cover_id_space(xlower, xmbr_index).ct() == old_cover_ct);

  // Exit:

  return;
}

/// @todo Remove.

// // $$SCRIBBLE: implicit-cover-reorganization
// // Added explicit cover set functions.

// sheaf::explicit_cover_set_adapter*
// sheaf::implicit_crg_range::
// explicit_cover_set(bool xlower, pod_index_type xmbr_index) const
// {
//   // Preconditions:

//   require(hub_id_space().contains(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* result = 0;

//   const explicit_cover_map_type* lmap = explicit_cover_map(xlower);

//   // Maps are indexed by internal (poset) id space:

//   explicit_cover_map_type::const_iterator litr = lmap->find(xmbr_index);
//   if(litr != lmap->end())
//   {
//     // Member is explict.

//     result = litr->second;

//     // All entries should be non-null.

//     assertion(result != 0);
//   }

//   // Postconditions:

//   ensure((result != 0) == cover_is_explicit(xlower, xmbr_index));

//   // Exit:

//   return result;
// }

// sheaf::explicit_cover_set_adapter*
// sheaf::implicit_crg_range::
// explicit_cover_set(bool xlower, const scoped_index& xmbr_index) const
// {
//   // Preconditions:

//   require(hub_id_space().contains(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* result = explicit_cover_set(xlower, xmbr_index.hub_pod());
  
//   // Postconditions:

//   ensure((result != 0) == cover_is_explicit(xlower, xmbr_index));

//   // Exit:

//   return result;
// }

// sheaf::explicit_cover_set_adapter*
// sheaf::implicit_crg_range::
// force_explicit_cover_set(bool xlower, pod_index_type xmbr_index, bool xinitialize)
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* result = explicit_cover_set(xlower, xmbr_index);
//   if(result == 0)
//   {
//     // Cover is implicit and immutable;
//     // create an explicit cover to replace it.

//     result = new list_cover_set_adapter();
//     if(xinitialize)
//     {
//       (*result) = cover_iterator(xlower, xmbr_index);
//     }

//     (*explicit_cover_map(xlower))[xmbr_index] = result;
//   }

//   // Postconditions:

//   ensure(result != 0);
//   ensure(cover_is_explicit(xlower, xmbr_index));

//   return result;
// }

// sheaf::explicit_cover_set_adapter*
// sheaf::implicit_crg_range::
// force_explicit_cover_set(bool xlower, const scoped_index& xmbr_index, bool xinitialize)
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   explicit_cover_set_adapter* result = 
//     force_explicit_cover_set(xlower, xmbr_index.hub_pod(), xinitialize);

//   // Postconditions:

//   ensure(cover_is_explicit(xlower, xmbr_index));

//   return result;
// }

// // $$SCRIBBLE: implicit-cover-reorganization
// // Added implicit functions.

// sheaf::cover_set_iterator
// sheaf::implicit_crg_range::
// implicit_cover_iterator(bool xlower, pod_index_type xmbr_index) const
// {
//   cover_set_iterator result; // Just to silence the compiler warnings.

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   is_abstract();

//   // Postconditions:

//   // Exit:

//   return result;
// }

// bool
// sheaf::implicit_crg_range::
// implicit_cover_contains_iterator(bool xlower,
// 				 pod_index_type xmbr_index,
// 				 const cover_set_iterator& xitr) const
// {
//   bool result = false; // Just to silence the compiler warnings.

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   is_abstract();

//   // Postconditions:

//   // Exit:

//   return result;
// }

// bool
// sheaf::implicit_crg_range::
// implicit_cover_is_empty(bool xlower, pod_index_type xmbr_index) const
// {
//   bool result = false; // Just to silence the compiler warnings.

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   is_abstract();

//   // Postconditions:

//   // Exit:

//   return result;
// }

// bool
// sheaf::implicit_crg_range::
// implicit_cover_is_singleton(bool xlower, pod_index_type xmbr_index) const
// {
//   bool result = false; // Just to silence the compiler warnings.

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   is_abstract();

//   // Postconditions:

//   // Exit:

//   return result;
// }

// sheaf::size_type
// sheaf::implicit_crg_range::
// implicit_cover_size(bool xlower, pod_index_type xmbr_index) const
// {
//   size_type result = 0; // Just to silence the compiler warnings.

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   is_abstract();

//   // Postconditions:

//   // Exit:

//   return result;
// }

// bool
// sheaf::implicit_crg_range::
// implicit_cover_contains_member(bool xlower,
// 			       pod_index_type xmbr_index,
// 			       pod_index_type xother_index) const
// {
//   bool result = false; // Just to silence the compiler warnings.

//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   is_abstract();

//   // Postconditions:

//   // Exit:

//   return result;
// }

// sheaf::pod_index_type
// sheaf::implicit_crg_range::
// implicit_first_cover_member(bool xlower, pod_index_type xmbr_index) const
// {
//   scoped_index result; // Just to silence the compiler warnings.

//   // Preconditions:

//   require(!cover_is_empty(xlower, xmbr_index));

//   // Body:

//   is_abstract();

//   // Postconditions:

//   // Exit:

//   return result;
// }

// PRIVATE DATA MEMBERS


// ===========================================================
// DOF_TUPLE_ID FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
sheaf::implicit_crg_range::
is_jim(pod_index_type xmbr_index) const
{
  bool result = false; // Just to silence the compiler warnings.

  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::implicit_crg_range::
is_jim(const scoped_index& xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  return is_jim(xmbr_index.hub_pod());
}

const sheaf::scoped_index&
sheaf::implicit_crg_range::
dof_tuple_id(const scoped_index& xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  return dof_tuple_id(xmbr_index.hub_pod());
}

sheaf::block<sheaf::scoped_index>&
sheaf::implicit_crg_range::
dof_tuple_ids()
{
  return _dof_tuple_ids;
}

const sheaf::block<sheaf::scoped_index>&
sheaf::implicit_crg_range::
dof_tuple_ids() const
{
  return _dof_tuple_ids;
}

void
sheaf::implicit_crg_range::
initialize_dof_tuple_ids(const block<scoped_index>& xdof_tuple_ids)
{
  // Preconditions:


  // Body:

  _dof_tuple_ids.reserve(xdof_tuple_ids.ct());
  _dof_tuple_ids.set_ct(xdof_tuple_ids.ct());

  for(int i=0; i<xdof_tuple_ids.ct(); ++i)
  {
    _dof_tuple_ids[i] = xdof_tuple_ids[i];
  }

  _dof_tuple_ids_initialized = true;

  // Postconditions:

  ensure(dof_tuple_ids_initialized());
  ensure(dof_tuple_ids().ct() == xdof_tuple_ids.ct());
  ensure_for_all(i, 0, xdof_tuple_ids.ct(), dof_tuple_ids()[i] == xdof_tuple_ids[i]);

  // Exit:

  return;
}

bool
sheaf::implicit_crg_range::
dof_tuple_ids_initialized() const
{
  return _dof_tuple_ids_initialized;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
sheaf::implicit_crg_range::
clean_cover(bool xlower, pod_index_type xmbr_index)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  explicit_cover_map_type::const_iterator litr =
    explicit_cover_map(xlower)->find(xmbr_index);

  if(litr != explicit_cover_map(xlower)->end())
  {
    // Cover id space is explicit, remove dangling members.

    mutable_index_space_handle* lcover = litr->second;

    index_space_iterator& litr = lcover->get_iterator();
    while(!litr.is_done())
    {
      pod_index_type lid = litr.hub_pod();

      if(!hub_id_space().contains(lid))
      {
	// The member is dangling remove it.

	litr.next();
	lcover->remove(lid, false);
      }
      else
      {
	// The member is valid, continue.

	litr.next();
      }
    }
    lcover->release_iterator(litr);

    // Update the id space extrema.

    lcover->update_extrema();
  }

  // Posconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// PRIVATE_DATA FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// $$SCRIBBLE: implicit-cover-reorganization
// Implemented private data function is insert cover information.

sheaf::size_type
sheaf::implicit_crg_range::
private_data_size() const
{
  // Preconditions:

  // Body:

  // Initialize to the implicit private data size.

  size_type result = implicit_private_data_size();

  // Add explicit member upper and lower cover sizes.

  result += 2;

  explicit_cover_map_type::const_iterator litr;

  // Count explicit upper covers.

  for(litr = _explicit_upper_cover_map.begin(); litr != _explicit_upper_cover_map.end(); ++litr)
  {
    // Add the member id, size of cover and cover members.

    result += (2+ litr->second->ct());
  }

  // Count explicit lower covers.

  for(litr = _explicit_lower_cover_map.begin(); litr != _explicit_lower_cover_map.end(); ++litr)
  {
    // Add the member id, size of cover and cover members.

    result += (2+ litr->second->ct());
  }

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::implicit_crg_range::
get_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  xdata.reserve(private_data_size());

  // Insert implicit private data.

  get_implicit_private_data(xdata);

  // Insert explicit private data.

  explicit_cover_map_type::const_iterator litr;

  // Insert explicit upper covers.

  xdata.push_back(_explicit_upper_cover_map.size());

  for(litr = _explicit_upper_cover_map.begin(); litr != _explicit_upper_cover_map.end(); ++litr)
  {
    // The private data has the member id, size of cover and cover members.

    xdata.push_back(litr->first);
    xdata.push_back(litr->second->ct());

    index_space_iterator& lcover_itr = litr->second->get_iterator();
    while(!lcover_itr.is_done())
    {
      xdata.push_back(lcover_itr.hub_pod());

      lcover_itr.next();
    }
    litr->second->release_iterator(lcover_itr);
  }

  // Insert explicit lower covers.

  xdata.push_back(_explicit_lower_cover_map.size());

  for(litr = _explicit_lower_cover_map.begin(); litr != _explicit_lower_cover_map.end(); ++litr)
  {
    // The private data has the member id, size of cover and cover members.

    xdata.push_back(litr->first);
    xdata.push_back(litr->second->ct());

   index_space_iterator& lcover_itr = litr->second->get_iterator();
    while(!lcover_itr.is_done())
    {
      xdata.push_back(lcover_itr.hub_pod());

      lcover_itr.next();
    }
    litr->second->release_iterator(lcover_itr);
  }

  // Postconditions:

  ensure(xdata.ct() == private_data_size());

  // Exit:

  return;
}

void
sheaf::implicit_crg_range::
put_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  require(xdata.ct() >= private_data_size());

  // Body:

  // Read the implicit private data.

  put_implicit_private_data(xdata);

  // Read the explicit private data.

  pod_index_type idx = implicit_private_data_size();
  size_type lmember_ct;
  pod_index_type lmember_id;
  size_type lcover_ct;
  interval_index_space_handle* lcover;

  // Read upper cover.

  lmember_ct = xdata[idx];
  for(pod_index_type i = 0; i < lmember_ct; ++i)
  {
    // Read member id.

    lmember_id = xdata[++idx];

    // Read cover.

    lcover_ct = xdata[++idx];
    lcover = &new_explicit_cover(UPPER, lmember_id, false);

    for(pod_index_type j = 0; j < lcover_ct; ++j)
    {
      lcover->push_back(xdata[++idx]);
    }

    // Insert cover into the map.

    _explicit_upper_cover_map[lmember_id] = lcover;
  }

  // Read lower cover.

  lmember_ct = xdata[++idx];
  for(pod_index_type i = 0; i < lmember_ct; ++i)
  {
    // Read member id.

    lmember_id = xdata[++idx];

    // Read cover.

    lcover_ct = xdata[++idx];
    lcover =  &new_explicit_cover(UPPER, lmember_id, false);

    for(pod_index_type j = 0; j < lcover_ct; ++j)
    {
      lcover->push_back(xdata[++idx]);
    }

    // Insert cover into the map.

    _explicit_lower_cover_map[lmember_id] = lcover;
  }

  // Mark private data as initialized.

  _private_data_initialized = true;

  // Postconditions:

  ensure(private_data_initialized());

  // Exit:

  return;
}

bool
sheaf::implicit_crg_range::
private_data_initialized() const
{
  return _private_data_initialized;
}

// PROTECTED DATA MEMBERS

sheaf::size_type
sheaf::implicit_crg_range::
implicit_private_data_size() const
{
  size_type result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::implicit_crg_range::
get_implicit_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(xdata.ct() == implicit_private_data_size());

  // Exit:

  return;
}

void
sheaf::implicit_crg_range::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  require(xdata.ct() >= implicit_private_data_size());

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// FINIALIZE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
sheaf::implicit_crg_range::
finalize(poset_state_handle& xhost)
{
  // Preconditions:

  require(xhost.state_is_read_accessible());

  // Body:

  // Have enough information to determine jims() membership.

  for(pod_index_type i=begin(); i<end(); ++i)
  {
    if(is_jim(i))
    {
      xhost.jims().insert_member(i);
    }
  }

  _is_finalized = true;

  // Postconditions:

  ensure(is_initialized());

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::factory<sheaf::implicit_crg_range>&
sheaf::implicit_crg_range::
range_factory()
{
  static factory<implicit_crg_range> result;

  return result;
}

sheaf::implicit_crg_range*
sheaf::implicit_crg_range::
new_range(const string& xname)
{
  // Preconditions:

  require(range_factory().contains_prototype(xname));

  // Body:

  implicit_crg_range* result = range_factory().new_instance(xname);

  // Postconditions:

  ensure(result != 0);
  ensure(result->class_name() == xname);

  // Exit:

  return result;
}

void
sheaf::implicit_crg_range::
initialize(const namespace_poset& xnamespace)
{
  // Preconditions:


  // Body:

  _id_spaces_initialized = true;
  _local_id_space_initialized = true;
  _range_member_id_space_initialized = true;
  _private_data_initialized = true;
  _dof_tuple_ids_initialized = true;
  _is_finalized = true;

  // Postconditions:

  ensure(is_initialized());

  // Exit:

  return;
}

bool
sheaf::implicit_crg_range::
is_initialized() const
{
  bool result =
    _id_spaces_initialized &&
    _local_id_space_initialized &&
    _range_member_id_space_initialized &&
    _private_data_initialized &&
    _dof_tuple_ids_initialized &&
    _is_finalized;

  return result;
}

const string&
sheaf::implicit_crg_range::
class_name() const
{
  static const string result("implicit_crg_range");
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
sheaf::implicit_crg_range::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const implicit_crg_range*>(other) != 0;

  // Postconditions:

  return result;
}

sheaf::implicit_crg_range*
sheaf::implicit_crg_range::
clone() const
{
  implicit_crg_range* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
sheaf::implicit_crg_range::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    invariance(local_id_space_initialized() ? begin() == local_id_space().offset() : true);
    invariance(local_id_space_initialized() ? implicit_begin() == local_id_space().offset()+1 : true);
    invariance(local_id_space_initialized() ? end() == local_id_space().offset() + local_id_space().end() : true);
    invariance(local_id_space_initialized() ? range_member() == begin() : true);
    invariance(range_member_id_space_initialized() ? range_member() == range_member_id_space().hub_id() : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

ostream& sheaf::operator << (ostream& os, const implicit_crg_range& m)
{

  os << "range begin: " << m.begin()
  << "  range end: " << m.end()
  << "  range size: " << m.size()
  << endl;

  return os;
}

size_t
sheaf::deep_size(const implicit_crg_range& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add the deep size of the data members.

  if(xp._dof_tuple_ids_initialized)
    result += deep_size(xp._dof_tuple_ids, false);

  if(xp._private_data_initialized)
    result += xp.private_data_size();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
