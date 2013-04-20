

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class mutable_index_space_handle

#include "mutable_index_space_handle.h"
#include "assert_contract.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "mutable_index_space_state.h"
#include "scoped_index.h"

// ===========================================================
// MUTABLE_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::mutable_index_space_handle::
mutable_index_space_handle()
  : explicit_index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::mutable_index_space_handle::
mutable_index_space_handle(const mutable_index_space_handle& xother)
{
  // Preconditions:
    
  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return; 
}

sheaf::mutable_index_space_handle::
mutable_index_space_handle(const index_space_family& xid_spaces,
			   pod_type xindex)
{
  // Preconditions:

  require(xid_spaces.contains(xindex));
  require(conforms_to_state(xid_spaces, xindex));

  // Body:

  attach_to(xid_spaces, xindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

sheaf::mutable_index_space_handle::
mutable_index_space_handle(const index_space_family& xid_spaces,
			   const string& xname)
{
  // Preconditions:

  require(xid_spaces.contains(xname));
  require(conforms_to_state(xid_spaces, xname));

  // Body:

  attach_to(xid_spaces, xname);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(name() == xname);

  // Exit:

  return;
}

sheaf::mutable_index_space_handle&
sheaf::mutable_index_space_handle::
operator=(const mutable_index_space_handle& xother)
{
  // Preconditions:
    
  // Body:
  
  (void) explicit_index_space_handle::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

sheaf::mutable_index_space_handle::
~mutable_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

sheaf::mutable_index_space_state&
sheaf::mutable_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  mutable_index_space_state& result =
    reinterpret_cast<mutable_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::mutable_index_space_state&
sheaf::mutable_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const mutable_index_space_state& result =
    reinterpret_cast<const mutable_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MUTABLE INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::mutable_index_space_handle::
insert(pod_type xid, const scoped_index& xhub_id)
{
  // Preconditions:

  require(is_attached());
  require(xhub_id.in_scope());
  require(precondition_of(insert(xid, xhub_id.hub_pod())));

  // Body:

  insert(xid, xhub_id.hub_pod());

  // Postconditions:

  ensure(postcondition_of(insert(xid, xhub_id.hub_pod())));

  // Exit:

  return;
}

void
sheaf::mutable_index_space_handle::
insert(pod_type xid, pod_type xhub_id)
{
  // Preconditions:

  require(is_attached());
  require(is_valid(xid));
  require(is_valid(xhub_id));
  require(!contains(xid));
  require(!contains_hub(xhub_id));
  require(hub_id_space().contains(xhub_id));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());

  state().insert(xid, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(contains(xid, xhub_id));
  ensure(ct() == old_ct + 1);
  ensure(ct() > 1 ? begin() <= old_begin : true);
  ensure(begin() <= xid);
  ensure(ct() > 1 ? end() >= old_end : true);
  ensure(end() > xid);

  // Exit:

  return;
}

void
sheaf::mutable_index_space_handle::
push_back(const scoped_index& xhub_id)
{
  // Preconditions:

  require(is_attached());
  require(xhub_id.in_scope());
  require(precondition_of(push_back(xhub_id.hub_pod())));

  // Body:

  push_back(xhub_id.hub_pod());

  // Postconditions:

  ensure(postcondition_of(push_back(xhub_id.hub_pod())));

  // Exit:

  return;
}

void
sheaf::mutable_index_space_handle::
push_back(pod_type xhub_id)
{
  // Preconditions:

  require(is_attached());

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());

  pod_type old_next_id = next_id();

  state().push_back(xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(contains(old_next_id, xhub_id));
  ensure(ct() == old_ct + 1);
  ensure(ct() > 1 ? begin() <= old_begin : true);
  ensure(end() == old_next_id+1);

  // Exit:

  return;
}

void
sheaf::mutable_index_space_handle::
push(index_space_iterator& xitr, const scoped_index& xhub_id)
{
  // Preconditions:

  require(is_attached());
  require(xhub_id.is_scoped());
  require(precondition_of(push(xitr, xhub_id.pod())));

  // Body:

  push(xitr, xhub_id.pod());
  
  // Postconditions:

  ensure(postcondition_of(push(xitr, xhub_id.pod())));

  // Exit:

  return;
}

void
sheaf::mutable_index_space_handle::
push(index_space_iterator& xitr, pod_type xhub_id)
{
  // Preconditions:

  require(is_attached());
  require(!xitr.is_done());
  require(allocated_iterator(xitr));
  require(is_valid(xhub_id));
  require(!contains_hub(xhub_id));
  require(hub_id_space().contains(xhub_id));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());
  define_old_variable(pod_type old_itr_hub_id = xitr.hub_pod());
  define_old_variable(pod_type old_itr_id = xitr.pod());

  state().push(xitr, xhub_id);
  
  // Postconditions:

  ensure(invariant());
  ensure(contains(old_itr_id, xhub_id));
  ensure(ct() == old_ct + 1);
  ensure(ct() > 1 ? begin() == old_begin : true);
  ensure(ct() > 1 ? end() == old_end + 1 : true);
  ensure(xitr.pod() == old_itr_id+1);
  ensure(xitr.hub_pod() == old_itr_hub_id);

  // Exit:

  return;
}

sheaf::mutable_index_space_handle::pod_type
sheaf::mutable_index_space_handle::
next_id() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = state().next_id();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::mutable_index_space_handle::
remove(const scoped_index& xid, bool xupdate_extrema)
{
  // Preconditions:

  require(is_attached());
  require(xid.in_scope());
  require(precondition_of(remove_hub(xid.hub_pod(), xupdate_extrema)));

  // Body:

  size_type result = remove_hub(xid.hub_pod(), xupdate_extrema);
  
  // Postconditions:

  ensure(postcondition_of(remove_hub(xid.hub_pod(), xupdate_extrema)));

  // Exit

  return result;
}

sheaf::size_type
sheaf::mutable_index_space_handle::
remove(pod_type xid, bool xupdate_extrema)
{
  // Preconditions:

  require(is_attached());

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());

  size_type result = state().remove(xid, xupdate_extrema);
  
  // Postconditions:

  ensure(!contains(xid));
  ensure((result != 0) ? ct() == old_ct - 1 : ct() == old_ct);
  ensure((result == 0) || xupdate_extrema || begin() == old_begin);
  ensure((result == 0) || xupdate_extrema || end() == old_end);
  ensure((result != 0) && xupdate_extrema && is_empty() ? !is_valid(begin()) : true);
  ensure((result != 0) && xupdate_extrema && is_empty() ? !is_valid(end()) : true);
  ensure((result != 0) && xupdate_extrema && !is_empty() ? begin() >= old_begin : true);
  ensure((result != 0) && xupdate_extrema && !is_empty() ? end() <= old_end : true);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::mutable_index_space_handle::
remove_hub(pod_type xhub_id, bool xupdate_extrema)
{
  // Preconditions:

  require(is_attached());

  // Body:

  define_old_variable(pod_type old_id = pod(xhub_id));
  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());

  pod_type result = state().remove_hub(xhub_id, xupdate_extrema);
  
  // Postconditions:

  ensure(!contains_hub(xhub_id));
  ensure((result != 0) ? ct() == old_ct - 1 : ct() == old_ct);
  ensure((result == 0) || xupdate_extrema || begin() == old_begin);
  ensure((result == 0) || xupdate_extrema || end() == old_end);
  ensure((result != 0) && xupdate_extrema && is_empty() ? !is_valid(begin()) : true);
  ensure((result != 0) && xupdate_extrema && is_empty() ? !is_valid(end()) : true);
  ensure((result != 0) && xupdate_extrema && !is_empty() ? begin() >= old_begin : true);
  ensure((result != 0) && xupdate_extrema && !is_empty() ? end() <= old_end : true);

  // Exit:

  return result;
}

void
sheaf::mutable_index_space_handle::
remove(index_space_iterator& xitr, bool xupdate_extrema)
{
  // Preconditions:

  require(is_attached());
  require(!xitr.is_done());
  require(contains(xitr.pod()));

  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());
  define_old_variable(pod_type old_itr_id = xitr.pod());
  define_old_variable(pod_type old_itr_hub_id = xitr.hub_pod());

  state().remove(xitr, xupdate_extrema);

  // Postconditions:

  ensure(!contains(old_itr_id));
  ensure(!contains(old_itr_hub_id));
  ensure(ct() == old_ct - 1);
  ensure(xupdate_extrema || begin() == old_begin);
  ensure(xupdate_extrema || end() == old_end);
  ensure(xupdate_extrema && is_empty() ? !is_valid(begin()) : true);
  ensure(xupdate_extrema && is_empty() ? !is_valid(end()) : true);
  ensure(xupdate_extrema && !is_empty() ? begin() >= old_begin : true);
  ensure(xupdate_extrema && !is_empty() ? end() <= old_end : true);
  ensure(xitr.is_done() || xitr.pod() > old_itr_id);

  // Exit:

  return;
}

void
sheaf::mutable_index_space_handle::
gather()
{
  // Preconditions:

  require(is_attached());

  // Body:

  state().gather();

  // Postconditions:

  ensure(invariant());
  ensure(is_gathered());

  // Exit:

  return;
}

void
sheaf::mutable_index_space_handle::
update_extrema()
{
  // Preconditions:

  require(is_attached());

  // Body:

  state().update_extrema();

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return;
}

void
sheaf::mutable_index_space_handle::
clear()
{
  // Preconditions:

  require(is_attached());

  // Body:

  state().clear();
  
  // Postconditions:

  ensure(invariant());
  ensure(is_empty());
  
  // Exit:

  return;
}

void
sheaf::mutable_index_space_handle::
reserve(size_type xcapacity)
{
  // Preconditions:

  require(is_attached());

  // Body:

  state().reserve(xcapacity);

  // Postconditions:

  ensure(invariant());
  ensure(capacity() >= xcapacity);

  // Exit:

  return;
}

sheaf::size_type
sheaf::mutable_index_space_handle::
capacity() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  size_type result = state().capacity();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::mutable_index_space_handle*
sheaf::mutable_index_space_handle::
clone() const
{
  // Preconditions:

  // Body:
  
  mutable_index_space_handle* result = new mutable_index_space_handle(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::mutable_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result =
    (dynamic_cast<mutable_index_space_state*>(state(xhost, xlocal_id)) != 0);
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::mutable_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const mutable_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::mutable_index_space_handle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(explicit_index_space_handle::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

size_t
sheaf::
deep_size(const mutable_index_space_handle& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

