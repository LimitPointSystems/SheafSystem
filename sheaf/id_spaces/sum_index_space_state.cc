
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Implementation for class sum_index_space_state

#include "ComLimitPoint/sheaf/sum_index_space_state.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/deep_size.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/scoped_index.h"
#include "std_limits.h"

using namespace std;

// ===========================================================
// SUM_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

sheaf::sum_index_space_state::
sum_index_space_state()
  : explicit_index_space_state()
{
  // Preconditions:
    
  // Body:
  
  // Initialize the sum to term map so that 
  // anything before first term maps to invalid
  // and anything above last term maps to invalid.

  _sum_to_term_map[0] = invalid_pod_index();
  _sum_to_term_map[std::numeric_limits<pod_type>::max()] = invalid_pod_index();

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return; 
}

sheaf::sum_index_space_state::
~sum_index_space_state()
{  
  // Preconditions:
    
  // Body:

  // Release the terms

  for(pod_type i = 0; i < _terms.ub(); ++i)
  {
    if(_terms[i] != 0)
    {
      id_spaces().release_id_space(*_terms[i]);
    }
  }

  // Postconditions:

  // Exit:

  return; 
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SUM INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::sum_index_space_state::
equivalence_class(pod_type xhub_id, equivalence_class_type& result) const
{
  // Preconditions:

  require(contains_hub(xhub_id));

  // Body:

  result.clear();

  // Find the representative member.

  pod_type lrep_id = rep(xhub_id);

  // Equivalence class always contains the representative itself,
  // but we don't store that, so insert it as first member.

  result.push_back(lrep_id);

  // Insert the rest of the equivalence class, may be empty.

  typedef rem_inv_type::const_iterator itr_type;
  pair<itr_type, itr_type> lrange = _rem_inv.equal_range(lrep_id);

  for(itr_type litr = lrange.first; litr != lrange.second; ++litr)
  {
    result.push_back(litr->second);
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return;
}

sheaf::size_type
sheaf::sum_index_space_state::
equivalence_ct(pod_type xhub_id) const
{
  // Preconditions:

  require(contains_hub(xhub_id));

  // Body:

  // Find the representative member.

  pod_type lrep_id = rep(xhub_id);

  // Get the equivalence count; add one for the rep itself.

  size_type result = _rem_inv.count(lrep_id) + 1;

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

bool
sheaf::sum_index_space_state::
contains_rep(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  is_abstract();

  bool result = true; // Just to silence compiler warnings.

  // Postconditions:

  ensure(result ? contains_hub(xhub_id) : true);
  
  // Exit:

  return result;
}

bool
sheaf::sum_index_space_state::
contains_unique_rep(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  // A rep is "unique" if it is the only member of its equivalence class.
  // _rem_inv contains the inverse of the reflexive reduction of the rem function.
  // So _rem_inv contains an entry for sum id s if and only if s is the rep
  // for an equivalence class that contains more that just s itself.
  // Thus s is unique if s is a rep and _rem_inv does not contain an entry for s.

  bool result = contains_rep(xhub_id) && (_rem_inv.find(xhub_id) == _rem_inv.end());

  // Postconditions:

  ensure(result ? contains_hub(xhub_id) : true);  
  ensure(result ? contains_rep(xhub_id) : true);

  // Exit:

  return result;
}

sheaf::sum_index_space_state::pod_type
sheaf::sum_index_space_state::
rep(pod_type xhub_id) const
{
  // Preconditions:

  require(contains_hub(xhub_id));
  
  // Body:
  
  is_abstract();
  
  pod_type result = 0; // Just to silence compiler warnings.

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return true;
}

sheaf::sum_index_space_state::pod_type
sheaf::sum_index_space_state::
host_rep(pod_type xhub_id) const
{
  // Preconditions:

  require(contains_hub(xhub_id));
  
  // Body:

  is_abstract();

  pod_type result = 0; // Just to silence compiler warnings.

  // Postconditions:

  ensure(contains(result));
  
  // Exit:

  return result;
}

sheaf::sum_index_space_state::pod_type
sheaf::sum_index_space_state::
term_id_begin() const
{
  // Preconditions:

  // Body:

  is_abstract();
  
  pod_type result = 0;  // Just to silence compiler warnings.

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_state::pod_type
sheaf::sum_index_space_state::
term_id_end() const
{
  // Preconditions:

  // Body:

  is_abstract();
  
  pod_type result = 0;  // Just to silence compiler warnings.

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::sum_index_space_state::
contains_term_id(pod_type xi) const
{
  // Preconditions:

  // Body:

  is_abstract();
  
  bool result = true;  // Just to silence compiler warnings.

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::sum_index_space_state::
term(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  const index_space_handle& result = *_terms[xi];

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::sum_index_space_state::
term_of(pod_type xid) const
{
  // Preconditions:

  require(contains(xid));

  // Body:

  const index_space_handle& result = term(term_id(pod(xid)));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::sum_index_space_state::
term_of(const scoped_index& xid) const
{
  // Preconditions:

  require(xid.in_scope());
  require(contains(xid));

  // Body:

  const index_space_handle& result = term_of(xid.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::sum_index_space_state::
last_term() const
{
  // Preconditions:

  require(!is_empty());

  // Body:

  // _terms.ct() is not maintained in gluable_sum_index_space_state, 
  // so can't use _terms.back().

  const index_space_handle& result = *_terms[term_id_end() - 1];

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_state::pod_type
sheaf::sum_index_space_state::
term_begin(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  pod_type result = _term_begin[xi];

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_state::pod_type
sheaf::sum_index_space_state::
term_end(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  pod_type result = _term_end[xi];

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_state::pod_type
sheaf::sum_index_space_state::
term_hub_begin(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  pod_type result = hub_pod(term_begin(xi));  

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::sum_index_space_state::pod_type
sheaf::sum_index_space_state::
term_hub_end(pod_type xi) const
{
  // Preconditions:

  require(contains_term_id(xi));

  // Body:

  pod_type result = hub_pod(term_end(xi));

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

sheaf::sum_index_space_state::pod_type
sheaf::sum_index_space_state::
term_id(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = _sum_to_term_map.upper_bound(xid)->second;

  // Postconditions:

  ensure(!is_valid(result) || contains_term_id(result));

  // Exit:

  return result;
}

void
sheaf::sum_index_space_state::
binary(pod_type xindex, pod_type& xterm_id, pod_type& xlocal_id) const
{
  // Preconditions:

  require(contains_hub(xindex));
  
  // Body:

  xterm_id  = _sum_to_term_map.upper_bound(xindex)->second;
  xlocal_id = xindex - _term_begin[xterm_id];
  
  // Postconditions:

  ensure(contains_term_id(xterm_id));
  ensure(term(xterm_id).contains(xlocal_id));

  // Exit:

  return;
}

void
sheaf::sum_index_space_state::
simple(pod_type xterm_id, pod_type xlocal_id, pod_type& xindex) const
{
  // Preconditions:

  require(contains_term_id(xterm_id));
  require(term(xterm_id).contains(xlocal_id));
  
  // Body:

  xindex = _term_begin[xterm_id] + xlocal_id;
  
  // Postconditions:

  ensure(contains_hub(xindex));

  // Exit:

  return;
}

void
sheaf::sum_index_space_state::
clear()
{
  // Preconditions:

  // Body:

  // Release the terms

  for(pod_type i = 0; i < _terms.ub(); ++i)
  {
    if(_terms[i] != 0)
    {
      id_spaces().release_id_space(*_terms[i]);
    }
  }

  // Clear the data structures

  _rem_inv.clear();
  _terms.clear();
  _term_begin.clear();
  _term_end.clear();
  _sum_to_term_map.clear();
  _ct = 0;

  invalidate_extrema();

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::sum_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const sum_index_space_state& lother =
    dynamic_cast<const sum_index_space_state&>(xother);

  bool result = explicit_index_space_state::operator==(xother);
  /// @error Since we still support tr1 unordered_maps the comparison
  ///        operator may not be supported.  See COM-374.
//   result = result && (_rem_inv == lother._rem_inv);
  result = result && (_terms == lother._terms);
  result = result && (_term_begin == lother._term_begin);
  result = result && (_term_end == lother._term_end);
  result = result && (_sum_to_term_map == lother._sum_to_term_map);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::sum_index_space_state::
deep_size(bool xinclude_shallow) const
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(*this, xinclude_shallow);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::sum_index_space_state&
sheaf::sum_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const sum_index_space_state& lother =
    dynamic_cast<const sum_index_space_state&>(xother);

  _rem_inv         = lother._rem_inv;
  _terms           = lother._terms;
  _term_begin      = lother._term_begin;
  _term_end        = lother._term_end;
  _sum_to_term_map = lother._sum_to_term_map;

  (void) explicit_index_space_state::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
sheaf::sum_index_space_state::
class_name() const
{
  static const std::string result("sum_index_space_state");
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::sum_index_space_state::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const sum_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::sum_index_space_state::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(explicit_index_space_state::invariant());

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
deep_size(const sum_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add any contributions from the parent class.

  const explicit_index_space_state& ixn = static_cast<const explicit_index_space_state&>(xn);
  result += deep_size(ixn, false);

  // Add memory associated in member _rem_inv.

  typedef no_deep_size_policy<sum_index_space_state::rem_inv_type> rem_inv_policy_type;
  result += deep_size<pod_index_type, pod_index_type, rem_inv_policy_type>(xn._rem_inv, false);

  // Add memory associated in member _terms

  /// @todo Call deep_size on _terms.  The current deep size for auto block
  /// calls deep size on the dereferenced pointers.  Since the handles are
  /// not allocated on the terms, the deep size of the handles should not
  /// be included.

  // Add memory associated in member _term_begin.

  result += deep_size(xn._term_begin, false);

  // Add memory associated in member _term_end.

  result += deep_size(xn._term_end, false);

  // Add memory associated in member _sum_to_term_map.

  typedef no_deep_size_policy<sum_index_space_state::sum_to_term_type> sum_to_term_policy_type;
  result += deep_size<pod_index_type, pod_index_type, sum_to_term_policy_type>(xn._sum_to_term_map, false);  

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
