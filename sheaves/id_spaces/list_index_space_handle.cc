
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
/// Implementation for class list_index_space_handle

#include "SheafSystem/list_index_space_handle.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/list_index_space_state.h"

// ===========================================================
// SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::list_index_space_handle
sheaf::list_index_space_handle::
new_space(index_space_family& xid_spaces,
	  const std::string& xname,
	  bool xis_persistent)
{
  // Preconditions:

  require(!xname.empty());
  require(!xid_spaces.contains(xname));
  // Body:

  list_index_space_handle result =
    list_index_space_state::new_space(xid_spaces,
				      xname,
				      xis_persistent);

  // Postconditions:

  ensure(&result.id_spaces() == &xid_spaces);
  ensure(xid_spaces.contains(xname));
  ensure(result.conforms_to_state(xname));

  ensure(result.is_persistent() == xis_persistent);
  ensure(result.name() == xname);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// LIST_INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::list_index_space_handle::
list_index_space_handle()
  : scattered_insertion_index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::list_index_space_handle::
list_index_space_handle(const list_index_space_handle& xother)
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

sheaf::list_index_space_handle::
list_index_space_handle(const index_space_family& xid_spaces,
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

sheaf::list_index_space_handle::
list_index_space_handle(const index_space_family& xid_spaces,
			const std::string& xname)
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

sheaf::list_index_space_handle&
sheaf::list_index_space_handle::
operator=(const list_index_space_handle& xother)
{
  // Preconditions:

  require(xother.is_attached() ? conforms_to_state(xother) : true);

  // Body:

  attach_to(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::list_index_space_handle::
~list_index_space_handle()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

void
sheaf::list_index_space_handle::
reverse(bool xupdate_extrema)
{
  // Preconditions:

  // Body:

  state().reverse(xupdate_extrema);

  // Postconditions:

  // Exit:

  return;
}

sheaf::list_index_space_handle::pod_type
sheaf::list_index_space_handle::
front() const
{
  return state().front();
}

sheaf::list_index_space_handle::pod_type
sheaf::list_index_space_handle::
back() const
{
  return state().back();
}

void
sheaf::list_index_space_handle::
push_front(pod_type xhub_id)
{
  // cout << endl << "Entering list_index_space_handle::push_front." << endl;

  // Preconditions:

  require(!contains_unglued_hub(xhub_id));
  
  // Body:

  define_old_variable(size_type old_ct = ct());
  define_old_variable(pod_type old_begin = begin());
  define_old_variable(pod_type old_end = end());

  state().push_front(xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(unglued_hub_pod(0) == xhub_id);
  ensure(ct() == old_ct + 1);
  ensure(begin() == 0);
  ensure(ct() > 1 ? end() == old_end+1 : end() == 1);
  
  // Exit:

  // cout << "Leaving list_index_space_handle::push_front." << endl;
  return;
}

void
sheaf::list_index_space_handle::
replace_range_id(pod_type xold_range_id, pod_type xnew_range_id)
{
  // cout << endl << "Entering list_index_space_handle::replace_range_id." << endl;

  // Preconditions:

  require((xnew_range_id != xold_range_id) ? !contains_unglued_hub(xnew_range_id) : true);
  
  // Body:

  define_old_variable(bool old_contains_xold_range_id = contains_unglued_hub(xold_range_id));
  define_old_variable(pod_type old_domain_id = pod(xold_range_id));


  state().replace_range_id(xold_range_id, xnew_range_id);

  // Postconditions:

  ensure(invariant());

  ensure(old_contains_xold_range_id ? contains_unglued_hub(xnew_range_id) : true);
  ensure((xnew_range_id != xold_range_id) ? !contains_unglued_hub(xold_range_id) : true);
  ensure(old_contains_xold_range_id ? pod(xnew_range_id) == old_domain_id : true);
  
  // Exit:

  // cout << "Leaving list_index_space_handle::replace_range_id." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::list_index_space_handle::
list_index_space_handle(list_index_space_state& xstate)
{
  // Preconditions:

  // Body:

  attach_to(&xstate);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&state() == &xstate);

  // Exit:

  return;
}

sheaf::list_index_space_state&
sheaf::list_index_space_handle::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  list_index_space_state& result =
    reinterpret_cast<list_index_space_state&>(*_state);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::list_index_space_state&
sheaf::list_index_space_handle::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const list_index_space_state& result =
    reinterpret_cast<const list_index_space_state&>(*_state);

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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// MAP REPRESENTATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::list_index_space_handle::to_range_type&
sheaf::list_index_space_handle::
to_range()
{
  return state().to_range();
}

const sheaf::list_index_space_handle::to_range_type&
sheaf::list_index_space_handle::
to_range() const
{
  return state().to_range();
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
// INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::list_index_space_handle&
sheaf::list_index_space_handle::
operator=(const index_space_handle& xother)
{
  // Preconditions:

  require(xother.is_attached() ? conforms_to_state(xother) : true);

  // Body:

  attach_to(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

sheaf::list_index_space_handle*
sheaf::list_index_space_handle::
clone() const
{
  // Preconditions:

  // Body:
  
  list_index_space_handle* result = new list_index_space_handle(*this);

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
sheaf::list_index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result =
    (dynamic_cast<list_index_space_state*>(state(xhost, xlocal_id)) != 0);
  
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
sheaf::list_index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const list_index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::list_index_space_handle::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(scattered_insertion_index_space_handle::invariant());

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

 
std::ostream& 
sheaf::
operator << (std::ostream& xos, const list_index_space_handle& xi)
{
  // Preconditions:

  // Body:

  using namespace std;

  if(xi.is_attached())
  {
    // Output the raw list.

    xos << "list: ";
    typedef list_index_space_state::to_range_type to_range_type;
    for(to_range_type::const_iterator i = xi.state().to_range().begin(); i != xi.state().to_range().end(); ++i)
    {
      xos << "  " << *i;
    }
    xos << endl << endl;

    // Output the usual id space info.

    xos << static_cast<const index_space_handle&>(xi);
  }
  else
  {
    xos << "index_space: index = -1 name = \'\'"
	<< endl;
  }
  
  // Postconditions:

  // Exit:

  return xos;
}


 

