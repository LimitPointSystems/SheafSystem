
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
/// Implementation for class explicit_index_space_state

#include "explicit_index_space_state.h"

#include "abstract_product_structure.h"
#include "assert_contract.h"
#include "arg_list.h"
#include "explicit_index_space_interval.h"
#include "explicit_index_space_iterator.h"
#include "factory_2.h"
#include "hub_index_space_handle.h"
#include "index_space_collection.h"
#include "index_space_family.h"
#include "scoped_index.h"
#include "std_iomanip.h"

// ===========================================================
// EXPLICIT_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
sheaf::explicit_index_space_state::
make_arg_list()
{
  // Preconditions:

  // Body:

  arg_list result;

  // Postconditions:

  ensure(result.empty());

  // Exit:

  return result;
} 

sheaf::explicit_index_space_state::
~explicit_index_space_state()
{  
  // Preconditions:
    
  // Body:
  
  if(_product != 0)
  {
    delete _product;
  }

  // Postconditions:

  // Exit:

  return; 
}

bool
sheaf::explicit_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = (_host == xother._host);
  result = result && (_index == xother._index);
  result = result && (_ct == xother._ct);
  result = result && (_begin == xother._begin);
  result = result && (_end == xother._end);
  result = result && (_is_persistent == xother._is_persistent);
  result = result && ((_product == 0) == (xother._product == 0));

  if(result && (_product != 0))
  {
    result = result && (*_product == *xother._product);
  }

  // Postconditions:

  // Exit

  return result;
}

const sheaf::index_space_collection&
sheaf::explicit_index_space_state::
host() const
{
  // Preconditions:

  // Body:

  const index_space_collection& result = *_host;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection&
sheaf::explicit_index_space_state::
host()
{
  // Preconditions:

  // Body:

  index_space_collection& result = *_host;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::explicit_index_space_state::
index() const
{
  // Preconditions:

  // Body:

  pod_type result = _index;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::explicit_index_space_state::
explicit_index_space_state()
  : _host(0),
    _index(invalid_pod_index()),
    _ct(0),
    _begin(invalid_pod_index()),
    _end(invalid_pod_index()),
    _is_persistent(false),
    _product(0)
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

sheaf::explicit_index_space_state::
explicit_index_space_state(const arg_list& xargs)
  : _ct(0),
    _begin(invalid_pod_index()),
    _end(invalid_pod_index()),
    _product(0)
{
  // Preconditions:

  require(xargs.contains_arg("host"));
  require(xargs.contains_arg("index"));
  require(xargs.contains_arg("is_persistent"));

  // Body:

  _host          = reinterpret_cast<index_space_collection*>((void *) xargs.value("host"));
  _index         = xargs.value("index");
  _is_persistent = xargs.value("is_persistent");

  /// @todo Add product structure to arguments?

  // Postconditions:

  ensure(invariant());
  ensure(&host() == (void*) xargs.value("host"));
  ensure(index() == xargs.value("index"));
  ensure(is_persistent() == xargs.value("is_persistent"));
  ensure(is_empty());

  // Exit:

  return;
}


sheaf::explicit_index_space_state&
sheaf::explicit_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:

  _host          = xother._host;
  _index         = xother._index;
  _ct            = xother._ct;
  _begin         = xother._begin;
  _end           = xother._end;
  _is_persistent = xother._is_persistent;
  _product       = (xother._product != 0) ? xother._product->clone() : 0;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

///////////////////////////////////////////////////////////////
// BEGIN NEW SPACE

void
sheaf::explicit_index_space_state::
new_state(index_space_family& xid_spaces,
	  const string& xname,
	  bool xis_persistent)
{
  // Preconditions:

  require(!xname.empty());
  require(!xid_spaces.contains(xname));

  // Body:

  // Reserve the next explicit index space id.

  pod_type result = xid_spaces.reserve_next_explicit_id();

  // Construct an explicit index space at id, result.

  new_state(xid_spaces, result, xname, xis_persistent);

  // Postconditions:

  ensure(invariant());

  ensure(&id_spaces() == &xid_spaces);
  ensure(is_persistent() == xis_persistent);
  ensure(xid_spaces.name(index()) == xname);

  ensure(xid_spaces.contains(index()));
  ensure(xid_spaces.contains(xname));

  // Exit:

  return;
}

void
sheaf::explicit_index_space_state::
new_state(index_space_family& xid_spaces,
	  pod_type xid,
	  const string& xname,
	  bool xis_persistent)
{
  // Preconditions:

  require(!xid_spaces.contains(xid));
  require(xid_spaces.is_explicit_interval(xid));
  require(!xname.empty());
  require(!xid_spaces.contains(xname));

  // Body:

  pod_type result = xid;

  // Get the explicit interval.

  explicit_index_space_interval* lexplicit_interval =
    reinterpret_cast<explicit_index_space_interval*>(xid_spaces.collection(result));

  // Set the data members.

  _host = lexplicit_interval;
  _is_persistent = xis_persistent;
  _index = xid;
  
  // Insert state into the explicit interval.

  lexplicit_interval->insert(*this);

  // Insert the name.

  xid_spaces.put_name(xid, xname);

  // Postconditions:

  ensure(invariant());

  ensure(&id_spaces() == &xid_spaces);
  ensure(index() == xid);
  ensure(is_persistent() == xis_persistent);
  ensure(xid_spaces.name(index()) == xname);

  ensure(xid_spaces.contains(index()));
  ensure(xid_spaces.contains(xname));

  // Exit:

  return;
}  

// END NEW SPACE
///////////////////////////////////////////////////////////////

sheaf::size_type
sheaf::explicit_index_space_state::
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

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::explicit_index_space_state::
id_spaces() const
{
  // Preconditions:

  // Body:

  const index_space_family& result = _host->id_spaces();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family&
sheaf::explicit_index_space_state::
id_spaces()
{
  // Preconditions:

  // Body:

  index_space_family& result = _host->id_spaces();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::hub_index_space_handle&
sheaf::explicit_index_space_state::
hub_id_space() const
{
  // Preconditions:

  // Body:

  const hub_index_space_handle& result = id_spaces().hub_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::explicit_index_space_state::
ct() const
{
  // Preconditions:

  // Body:

  size_type result = _ct;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
is_empty() const
{
  // Preconditions:

  // Body:

  bool result = (_ct == 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::explicit_index_space_state::
begin() const
{
  // Preconditions:

  // Body:

  pod_type result = _begin;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::explicit_index_space_state::
end() const
{
  // Preconditions:

  // Body:

  pod_type result = _end;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
is_gathered() const
{
  // Preconditions:

  // Body:

  bool result = (begin() == 0) && (end() == ct());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
contains(const scoped_index& xid) const
{
  // Preconditions:

  // Body:

  bool result = contains_hub(xid.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
contains_hub(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = contains_unglued_hub(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
contains_unglued_hub(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
contains_glued_hub(pod_type xid) const
{
  // Preconditions:

  // Body:

  bool result =
   contains_unglued_hub(hub_id_space().unglued_hub_pod(xid));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
contains(pod_type xid, const scoped_index& xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = contains(xid, xhub_id.hub_pod());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
contains(pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = (contains(xid) && (hub_pod(xid) == xhub_id));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::explicit_index_space_state::
pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::explicit_index_space_state::
pod(const scoped_index& xid) const
{
  // Preconditions:

  // Body:

  pod_type result = pod(xid.hub_pod());

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::explicit_index_space_state::
hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = unglued_hub_pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(result));

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::explicit_index_space_state::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

  // Exit:

  return result;
}

sheaf::explicit_index_space_state::pod_type
sheaf::explicit_index_space_state::
glued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result =
    hub_id_space().glued_hub_pod(unglued_hub_pod(xid));

  // Postconditions:

  ensure(!is_valid(result) || contains_glued_hub(result));

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
is_persistent() const
{
  // Preconditions:

  // Body:

  bool result = _is_persistent;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::explicit_index_space_state::
invalidate_extrema()
{
  // Preconditions:

  // Body:

  _begin = invalid_pod_index();
  _end   = invalid_pod_index();

  // Posconditions:

  ensure(!is_valid(begin()));
  ensure(!is_valid(end()));

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRODUCT STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::explicit_index_space_state::
new_product_structure(const abstract_product_structure& xproduct)
{
  // Preconditions:

  // Body:

  _product = xproduct.clone();

  // Postconditions:

  ensure(has_product_structure());

  // Exit:

  return;
}

void
sheaf::explicit_index_space_state::
delete_product_structure()
{
  // Preconditions:

  // Body:

  if(_product != 0)
  {
    delete _product;
    _product = 0;
  }
  
  // Postconditions:

  ensure(!has_product_structure());

  // Exit:

  return;
}

const sheaf::abstract_product_structure&
sheaf::explicit_index_space_state::
product_structure() const
{
  // Preconditions:

  require(has_product_structure());

  // Body:

  const abstract_product_structure& result = *_product;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::abstract_product_structure&
sheaf::explicit_index_space_state::
product_structure()
{
  // Preconditions:

  require(has_product_structure());

  // Body:

  abstract_product_structure& result = *_product;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
has_product_structure() const
{
  // Preconditions:

  // Body:

  bool result = (_product != 0);

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
sheaf::explicit_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  index_space_handle* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result->is_attached());

  // Exit:

  return *result;
}

void
sheaf::explicit_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::explicit_index_space_state::
attach(explicit_index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  // This function is const because it does not change this
  // object.  It only passes it to the handle.  However, the
  // handle wants a mutable version of this object because
  // it may export mutation functions to the user.  These mutation
  // function only depend on the constness of the handle.

  xid_space.attach_to(const_cast<explicit_index_space_state*>(this));

  // Postconditions:

  ensure(xid_space.is_attached());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ITERATOR POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_iterator&
sheaf::explicit_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  index_space_iterator* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result->is_attached());

  // Exit:

  return *result;
}

void
sheaf::explicit_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::explicit_index_space_state::
attach(explicit_index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  // This function is const because it does not change this
  // object.  It only passes it to the iterator.  However, the
  // iterator wants a mutable version of this object because
  // it may export mutation functions to the user.  These mutation
  // function only depend on the constness of the iterator.

  xitr.attach_to(const_cast<explicit_index_space_state*>(this));

  // Postconditions:

  ensure(xitr.is_attached());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
sheaf::explicit_index_space_state::
class_name() const
{
  static const string result("explicit_index_space_state");
  return result;
}

sheaf::factory_2<sheaf::explicit_index_space_state>&
sheaf::explicit_index_space_state::
id_space_factory()
{
  // Preconditions:

  // Body:

  static factory_2<explicit_index_space_state> result;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::explicit_index_space_state*
sheaf::explicit_index_space_state::
clone(const arg_list& xargs) const
{
  // Preconditions:

  // Body:

  explicit_index_space_state* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

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
sheaf::explicit_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const explicit_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_state::
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

    invariance(is_empty() ? !is_valid(begin()) : contains(begin()));
    invariance(begin() <= end());
      
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
deep_size(const explicit_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add contributions for the product structure.

  if(xn.has_product_structure())
  {
    /// @issue The product structure should have deep_size functions
    /// to deal with the covariant types but since the current product
    /// structure only has data members that are size_t we can use
    /// size_of.

    result += sizeof(xn.product_structure());
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

ostream& 
sheaf::
operator << (ostream& xos, const explicit_index_space_state& xe)
{
  // Preconditions:

  // Body:

  xos << "class name: " << xe.class_name() << endl;
  xos << "index:      " << xe.index() << endl;
  xos << "ct:         " << xe.ct() << endl;
  xos << "begin:      " << xe.begin() << endl;
  xos << "end:        " << xe.end() << endl;
  xos << "persistent: " << boolalpha << xe.is_persistent() << noboolalpha << endl;

  xos << "ids:  ";
  index_space_iterator& litr = xe.get_iterator();
  while(!litr.is_done())
  {
    xos << setw(10) << litr.pod();
    litr.next();
  }
  xos << endl;
  
  xos << "hub ids: ";
  litr.reset();
  while(!litr.is_done())
  {
    xos << setw(10) << litr.hub_pod();
    litr.next();
  }
  xos << endl;
  xe.release_iterator(litr);

  // Postconditions:

  // Exit:

  return xos;
}
