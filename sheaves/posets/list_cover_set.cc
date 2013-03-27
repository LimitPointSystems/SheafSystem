// $RCSfile: list_cover_set.cc,v $ $Revision: 1.22 $ $Date: 2013/01/12 17:17:41 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class list_cover_set

#include "list_cover_set.h"

#include "assert_contract.h"
#include "deep_size.h"
#include "subposet.h"
#include "index_iterator.h"
#include "block.h"
#include "std_algorithm.h"
#include "std_sstream.h"

using namespace sheaf;

// ===========================================================
// LIST_COVER_SET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::list_cover_set::
list_cover_set()
{
  // Preconditions:

  // Body:

  // Initialize ref ct > 0 so
  // won't be deleted automatically if
  // passed to rc_ptr.

  _ref_ct = 1;

  _is_implicit = false;

  // Postconditions:

  ensure(ref_ct() == 1);
  ensure(!is_implicit());
}

sheaf::list_cover_set::
list_cover_set(size_type xref_ct)
{
  // Preconditions:

  // Body:

  _ref_ct = xref_ct;
  _is_implicit = false;

  // Postconditions:

  ensure(ref_ct() == xref_ct);
  ensure(!is_implicit());
}

sheaf::list_cover_set::
list_cover_set(const list_cover_set& xother)
    : list<pod_index_type>(xother)
{
  // Preconditions:

  // Body:

  _ref_ct = 0;

  _is_implicit = xother._is_implicit;

  // Postconditions:

  ensure(ref_ct() == 0);

  // Exit:

  return;
}

sheaf::list_cover_set::
~list_cover_set()
{
  // Preconditions:

  // Body:

  // Postconditions:
}

int
sheaf::list_cover_set::
member_ct() const
{
  int result;

  // Preconditions:

  // Body:

  result = size();

  // Postconditions:

  ensure(result == size());

  // Exit:

  return result;
}

void
sheaf::list_cover_set::
insert_member(pod_index_type xmbr)
{
  // Preconditions:

  require(!contains_member(xmbr));

  // Body:

  push_back(xmbr);

  // Postconditions:

  ensure(back() == xmbr);

  // Exit:

  return;
}

void
sheaf::list_cover_set::
insert_member(const scoped_index& xmbr)
{
  // Preconditions:

  require(!contains_member(xmbr));

  // Body:

  push_back(xmbr.hub_pod());

  // Postconditions:

  ensure(back() == xmbr.hub_pod());

  // Exit:

  return;
}

void
sheaf::list_cover_set::
remove_member(pod_index_type xmbr)
{
  // Preconditions:

  // Body:

  list_cover_set::iterator itr = find(begin(), end(), xmbr);
  if( itr != end() )
  {
    erase(itr);
  }
  

  // Postconditions:

  ensure(!contains_member(xmbr));

  // Exit:

  return;
}

void
sheaf::list_cover_set::
remove_member(const scoped_index& xmbr)
{
  // Preconditions:

  // Body:

  remove_member(xmbr.hub_pod());

  // Postconditions:

  ensure(!contains_member(xmbr));

  // Exit:

  return;
}

sheaf::list_cover_set::hint*
sheaf::list_cover_set::
new_hint()
{
  hint* result;

  // Preconditions:

  // Body:

  result = new hint(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(&(result->host()) == this);
  ensure(result->itr() == begin());

  // Exit:

  return result;
}

void
sheaf::list_cover_set::
remove_member(pod_index_type xmbr, const hint* xhint)
{
  // Preconditions:

  require(xhint != 0);
  require((&const_cast<hint*>(xhint)->host()) == this);

  // Body:

  list_cover_set::iterator itr = find(const_cast<hint*>(xhint)->itr(), end(), xmbr);
  if( itr == end() )
  {
    itr = find(begin(), const_cast<hint*>(xhint)->itr(), xmbr);
  }

  if( itr != end() )
  {
    const_cast<hint*>(xhint)->itr() = itr++;
    erase(const_cast<hint*>(xhint)->itr());
    const_cast<hint*>(xhint)->itr() = itr;
  }

  // Postconditions:

  ensure(!contains_member(xmbr));

  // Exit
}

void
sheaf::list_cover_set::
replace_member(pod_index_type xold_mbr, pod_index_type xnew_mbr)
{
  // Preconditions:

  define_old_variable(bool old_contains_old_mbr = contains_member(xold_mbr));

  // Body:

  list_cover_set::iterator itr = find(begin(), end(), xold_mbr);
  if( itr != end() )
  {
    *itr = xnew_mbr;
  }


  // Postconditions:

  ensure(!contains_member(xold_mbr));
  ensure(old_contains_old_mbr ? contains_member(xnew_mbr) : true);

  // Exit:

  return;
}

void
sheaf::list_cover_set::
replace_member(const scoped_index& xold_mbr, const scoped_index& xnew_mbr)
{
  // Preconditions:

  require(xold_mbr.same_id_space_family(xnew_mbr));

  define_old_variable(bool old_contains_old_mbr = contains_member(xold_mbr));

  // Body:

  replace_member(xold_mbr.hub_pod(), xnew_mbr.hub_pod());

  // Postconditions:

  ensure(!contains_member(xold_mbr));
  ensure(old_contains_old_mbr ? contains_member(xnew_mbr) : true);

  // Exit:

  return;
}

void
sheaf::list_cover_set::
remove_member(const scoped_index& xmbr, const hint* xhint)
{
  // Preconditions:

  require(xhint != 0);
  require((&const_cast<hint*>(xhint)->host()) == this);

  // Body:

  remove_member(xmbr.hub_pod(), xhint);

  // Postconditions:

  ensure(!contains_member(xmbr));

  // Exit
}

bool
sheaf::list_cover_set::
contains_member(pod_index_type xindex) const
{
  
  bool result;

  // Preconditions:

  // Body:

  result = (find(begin(), end(), xindex) != end());

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::list_cover_set::
contains_member(const scoped_index& xindex) const
{
  return contains_member(xindex.hub_pod());
}

bool
sheaf::list_cover_set::
is_singleton() const
{
  bool result;

  // Preconditions:

  // Body:

  // Could just evaluate size() == 1, but
  // performance of size() is O(size()) while
  // the following is O(1).

  result = ( !empty() && (++(begin()) == end()) );

  // Postconditions:

  // Exit:

  return result;
}


bool
sheaf::list_cover_set::
is_multiple() const
{
  bool result;

  // Preconditions:

  // Body:

  // Could just evaluate size() > 1, but
  // performance of size() is O(size()) while
  // the following is O(1).

  result = ( !empty() && (++(begin()) != end()) );

  // Postconditions:

  // Exit:

  return result;
}

 

bool
sheaf::list_cover_set::
set_equals(const list_cover_set* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = ( size() == xother->size() );

   
  list_cover_set::const_iterator itr = begin();
  while(result && (itr != end()))
  {
    result = xother->contains_member(*itr);
    itr++;
  }

  // Postconditions:

  // Exit

  return result;
} 

sheaf::list_cover_set*
sheaf::list_cover_set::
set_intersection(const list_cover_set* xother) const
{
  list_cover_set* result;

  // Preconditions:

  require(xother != 0);

  // Body:

  result = new list_cover_set;
  set_intersection_pa(xother, result);

  // Postconditions:

  ensure(result != 0);
  ensure(unexecutable(result contains intersection of xother and this));

  // Exit

  return result;
}

void
sheaf::list_cover_set::
set_intersection_pa(const list_cover_set* xother, list_cover_set* xresult) const
{

  // Preconditions:

  require(xother != 0);
  require(xresult != 0);
  require(xresult->empty());

  // Body:
   
  list_cover_set::const_iterator itr = begin();

  while(itr != end())
  {
    pod_index_type lmbr = *itr;
    if(xother->contains_member(lmbr))
    {
      xresult->insert_member(lmbr);
    }
    itr++;
  }

  // Postconditions:

  ensure(unexecutable(xresult contains intersection of xother and this));

  // Exit

  return;
}

void
sheaf::list_cover_set::
set_intersection_sa(const list_cover_set* xother)
{
  // Preconditions:

  require(xother != 0);

  // Body:
   
  list_cover_set::iterator itr = begin();
  list_cover_set::iterator erase_itr;

  while(itr != end())
  {

    // Erase will invalidate itr,
    // need to increment it first.

    erase_itr = itr;
    itr++;

    if(!xother->contains_member(*erase_itr))
    {
      // Current member is not in other;
      // erase it
      erase(erase_itr);
    }
  }

  // Postconditions:

  ensure(unexecutable(this contains intersection of xother and old this));

  // Exit

  return;
}

void
sheaf::list_cover_set::
to_stream(ostream& os) const
{
  os << *this;
}

string
sheaf::list_cover_set::
to_string() const
{
  ostringstream oss;
  oss << *this;
  return oss.str();
}

void
sheaf::list_cover_set::
add_reference()
{
  // Preconditions:

  // Body:

  define_old_variable(size_type old_ref_ct = _ref_ct);

  ++_ref_ct;

  // Postconditions:

  ensure(ref_ct() == old_ref_ct + 1);

  // Exit:

  return;
}

void
sheaf::list_cover_set::
remove_reference()
{
  // Preconditions:

  require(ref_ct() > 0);

  // Body:

  define_old_variable(size_type old_ref_ct = _ref_ct);

  --_ref_ct;

  if(_ref_ct == 0)
  {
    delete this;
  }

  // Postconditions:

  ensure((old_ref_ct == 1) || (ref_ct() == old_ref_ct - 1));

  // Exit:

  return;
}

bool
sheaf::list_cover_set::
is_shared() const
{
  return _ref_ct > 1;
}

sheaf::list_cover_set::size_type
sheaf::list_cover_set::
ref_ct() const
{
  return _ref_ct;
}

bool
sheaf::list_cover_set::
is_implicit() const
{
  return _is_implicit;
}

void
sheaf::list_cover_set::
put_is_implicit(bool xis_implicit)
{
  // Preconditions:

  // Body:

  _is_implicit = xis_implicit;

  // Postconditions:

  ensure(is_implicit() == xis_implicit);
  
  // Exit:

  return;
}


sheaf::list_cover_set::hint::
~hint()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

sheaf::list_cover_set::hint::
hint(const list_cover_set& xhost)
  : _host(const_cast<list_cover_set&>(xhost)),
    _itr(const_cast<list_cover_set&>(xhost).begin())
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(&(host()) == &xhost);
  ensure(itr() == xhost.begin());

  // Exit:

  return;
}

sheaf::list_cover_set&
sheaf::list_cover_set::hint::
host()
{
  // Preconditions:

  // Body:

  list_cover_set& result = _host;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::list_cover_set::iterator&
sheaf::list_cover_set::hint::
itr()
{
  // Preconditions:

  // Body:

  list_cover_set::iterator& result = _itr;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

ostream & 
sheaf::
operator << (ostream &xos, const list_cover_set& xc)
{
  copy(xc.begin(), xc.end(), ostream_iterator<pod_index_type>(xos, " "));

  return xos;
}

size_t 
sheaf::
deep_size(const list_cover_set& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add any contributions from the parent class.

  typedef list<pod_index_type> parent_type;
  list_cover_set& lxp = const_cast<list_cover_set&>(xp);
  parent_type& ixp = static_cast<parent_type&>(lxp);
  result += deep_size(ixp, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

