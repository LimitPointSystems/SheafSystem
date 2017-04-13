
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
/// Implementation for class index_space_handle

#include "SheafSystem/abstract_product_structure.h"
#include "SheafSystem/index_space_handle.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/scoped_index.h"
#include "SheafSystem/std_iomanip.h"

// ===========================================================
// INDEX_SPACE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_handle::
~index_space_handle()
{  
  // Preconditions:

  // Body:

  // nothing to do.
  
  // Postconditions:

  // Exit:

  return; 
}

sheaf::index_space_handle&
sheaf::index_space_handle::
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

bool
sheaf::index_space_handle::
operator==(const index_space_handle& xother) const
{
  // Preconditions:

  // Body:

  bool result = (is_attached() == xother.is_attached());
  if(result && is_attached())
  {
    result = result && (&id_spaces() == &xother.id_spaces());
    result = result && (index() == xother.index());
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle*
sheaf::index_space_handle::
clone() const
{
  index_space_handle* result;
  
  // Preconditions:

  // Body:
  
  result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);
  
  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

sheaf::index_space_handle::
index_space_handle()
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  // Can't call invariant because it calls pure virtual functions.
  //ensure(invariant());

  // Exit:

  return; 
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::index_space_handle::
id_spaces() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const index_space_family* result = 0;

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

sheaf::index_space_family&
sheaf::index_space_handle::
id_spaces()
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_family* result = 0;

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

const sheaf::hub_index_space_handle&
sheaf::index_space_handle::
hub_id_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const hub_index_space_handle& result = id_spaces().hub_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::index_space_handle::
ct() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  size_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
is_empty() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = (ct() == 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_handle::
begin() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_handle::
end() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
is_gathered() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = (begin() == 0) && (end() == ct());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
contains(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
contains(const scoped_index& xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = contains_hub(xid.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
contains_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = contains_unglued_hub(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
contains_unglued_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
contains_glued_hub(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
contains(pod_type xid, const scoped_index& xhub_id) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = contains(xid, xhub_id.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
contains(pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_handle::
pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_handle::
pod(const scoped_index& xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = pod(xid.hub_pod());

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_handle::
hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = unglued_hub_pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_handle::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_handle::
glued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(!is_valid(result) || contains_glued_hub(result));

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
is_persistent() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRODUCT STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::index_space_handle::
new_product_structure(const abstract_product_structure& xproduct)
{
  // Preconditions:

  require(is_attached());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(has_product_structure());

  // Exit:

  return;
}

void
sheaf::index_space_handle::
delete_product_structure()
{
  // Preconditions:

  require(is_attached());

  // Body:

  is_abstract();
  
  // Postconditions:

  ensure(!has_product_structure());

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
sheaf::index_space_handle::
product_structure() const
{
  // Preconditions:

  require(is_attached());
  require(has_product_structure());

  // Body:

  const abstract_product_structure* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

sheaf::abstract_product_structure&
sheaf::index_space_handle::
product_structure()
{
  // Preconditions:

  require(is_attached());
  require(has_product_structure());

  // Body:

  abstract_product_structure* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *result;
}

bool
sheaf::index_space_handle::
has_product_structure() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_collection&
sheaf::index_space_handle::
host() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_collection* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);
  
  // Exit:

  return *result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_handle::
index() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(id_spaces().contains(result));

  // Exit:

  return result;
}

std::string
sheaf::index_space_handle::
name() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  std::string result = id_spaces().name(index());

  // Postconditions:

  ensure(result.empty() || id_spaces().contains(result));

  // Exit:

  return result;
}

void
sheaf::index_space_handle::
put_name(const std::string& xname)
{
  // Preconditions:

  require(!xname.empty());
  require(!id_spaces().contains(xname));

  // Body:

  id_spaces().put_name(index(), xname);

  // Postconditions:

  ensure(id_spaces().contains(xname));
  ensure(id_spaces().name(index()) == xname);

  // Exit:

  return;
}

bool
sheaf::index_space_handle::
is_attached() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::index_space_handle::
attach_to(const index_space_family& xid_spaces, pod_type xindex)
{
  // Preconditions:

  require(xid_spaces.contains(xindex));
  require(conforms_to_state(xid_spaces, xindex));

  // Body:

  const index_space_collection* lhost = xid_spaces.collection(xindex);
  attach_to(*lhost, lhost->local_scope(xindex));

  // Postconditions:

  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

void
sheaf::index_space_handle::
attach_to(const index_space_family& xid_spaces, const std::string& xname)
{
  // Preconditions:

  require(!xname.empty());
  require(xid_spaces.contains(xname));
  require(conforms_to_state(xid_spaces, xname));

  // Body:

  attach_to(xid_spaces, xid_spaces.index(xname));

  // Postconditions:

  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(name() == xname);

  // Exit:

  return;
}

void
sheaf::index_space_handle::
attach_to(pod_type xindex)
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xindex));
  require(conforms_to_state(xindex));

  // Body:

  define_old_variable(const index_space_family& old_id_spaces = id_spaces());

  is_abstract();

  // Postconditions:

  ensure(is_attached());
  ensure(&id_spaces() == &old_id_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

void
sheaf::index_space_handle::
attach_to(const std::string& xname)
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xname));
  require(conforms_to_state(xname));

  // Body:

  define_old_variable(const index_space_family& old_id_spaces = id_spaces());

  attach_to(id_spaces().index(xname));

  // Postconditions:

  ensure(is_attached());
  ensure(&id_spaces() == &old_id_spaces);
  ensure(name() == xname);

  // Exit:

  return;
}

void
sheaf::index_space_handle::
attach_to(const index_space_handle& xother)
{
  // Preconditions:

  require(xother.is_attached() ? conforms_to_state(xother) : true);

  // Body:

  if(xother.is_attached())
  {
    // xother is attached; attach this to the state of xother.

    if(is_attached() && (host() == xother.host()))
    {
      attach_to(xother.index());
    }
    else
    {
      attach_to(xother.id_spaces(), xother.index());
    }
  }
  else
  {
    // xother is not attached; detach this.

    detach();
  }

  // Postconditions:

  ensure(is_attached() == xother.is_attached());
  ensure(is_attached() ? &host() == &xother.host() : true);
  ensure(is_attached() ? index() == xother.index() : true);

  // Exit:

  return;
}

void
sheaf::index_space_handle::
attach_to(const index_space_collection& xhost, pod_type xlocal_id)
{
  // Preconditions:

  require(xhost.contains(xlocal_id));
  require(conforms_to_state(xhost, xlocal_id));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_attached());
  ensure(&host() == &xhost);
  ensure(index() == xhost.family_scope(xlocal_id));

  // Exit:

  return;
}

void
sheaf::index_space_handle::
detach()
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

bool
sheaf::index_space_handle::
conforms_to_state(const index_space_family& xid_spaces,
		  pod_type xindex) const
{
  // Preconditions:

  require(xid_spaces.contains(xindex));

  // Body:

  const index_space_collection* lhost = xid_spaces.collection(xindex);
  bool result = conforms_to_state(*lhost, lhost->local_scope(xindex));
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
conforms_to_state(const index_space_family& xid_spaces,
		  const std::string& xname) const
{
  // Preconditions:

  require(xid_spaces.contains(xname));

  // Body:

  bool result = conforms_to_state(xid_spaces, xid_spaces.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
conforms_to_state(pod_type xindex) const
{
  // Preconditions:

  require(id_spaces().contains(xindex));

  // Body:

  bool result = conforms_to_state(id_spaces(), xindex);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
conforms_to_state(const std::string& xname) const
{
  // Preconditions:

  require(id_spaces().contains(xname));

  // Body:

  bool result = conforms_to_state(id_spaces(), xname);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
conforms_to_state(const index_space_handle& xother) const
{
  // Preconditions:

  // Body:

  // Any handle can conform to an unattached state.

  bool result = !xother.is_attached();

  if(!result)
  {
    // xother is attached to a state; check to see if this handle
    // conforms to the state of xother.

    if(is_attached() && (host() == xother.host()))
    {
      result = conforms_to_state(xother.index());
    }
    else
    {
      result = conforms_to_state(xother.id_spaces(), xother.index());
    }
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result = false;

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_handle&
sheaf::index_space_handle::
get_id_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_handle* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result->is_attached());

  // Exit:

  return *result;
}

void
sheaf::index_space_handle::
release_id_space() const
{
  // Preconditions:

  require(is_attached());
  require(allocated_id_space());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_handle::
allocated_id_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ITERATOR POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_iterator&
sheaf::index_space_handle::
get_iterator() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_iterator* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result->is_attached());

  // Exit:

  return *result;
}

void
sheaf::index_space_handle::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(is_attached());
  require(allocated_iterator(xitr));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_handle::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

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
sheaf::index_space_handle::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const index_space_handle*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::index_space_handle::
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

    invariance(is_attached() ? is_valid(index()) : true);
    invariance(is_attached() ? id_spaces().contains(index()) : true);
      
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
operator << (std::ostream& xos, const index_space_handle& xi)
{
  // Preconditions:

  // Body:

  using namespace std;

  if(xi.is_attached())
  {
    xos << "index_space:"
	<< " index = " << xi.index()
	<< " name = \'" << xi.name() << "\'"
	<< endl;

    xos << "ct:         " << xi.ct() << endl;
    xos << "begin:      " << xi.begin() << endl;
    xos << "end:        " << xi.end() << endl;
    xos << "persistent: " << boolalpha << xi.is_persistent() << noboolalpha << endl;

    xos << "ids:        ";
    index_space_iterator& litr = xi.get_iterator();
    while(!litr.is_done())
    {
      xos << setw(10) << litr.pod();
      litr.next();
    }
    xos << endl;
  
    xos << "hub ids:    ";
    litr.reset();
    while(!litr.is_done())
    {
      xos << setw(10) << litr.hub_pod();
      litr.next();
    }
    xos << endl;
    xi.release_iterator(litr);
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
 
size_t
sheaf::
deep_size(const index_space_handle& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
