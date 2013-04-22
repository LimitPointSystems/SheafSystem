

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class section_space_schema_jims_index_space_state

#include "section_space_schema_jims_index_space_state.h"
#include "assert_contract.h"
#include "arg_list.h"
#include "ij_product_structure.h"
#include "index_space_family.h"
#include "section_space_schema_jims_index_space_handle.h"
#include "section_space_schema_jims_index_space_iterator.h"
#include "deep_size.h"
#include "hub_index_space_handle.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::section_space_schema_jims_index_space_state::
make_arg_list(const index_space_handle& xbase_space_id_space,
	      const index_space_handle& xfiber_schema_id_space,
	      const ij_product_structure& xsection_space_schema_product_structure)
{
  // Preconditions:

  // Body:

  arg_list result = explicit_index_space_state::make_arg_list();
  result << "base_space_id_space" << &xbase_space_id_space
	 << "fiber_schema_id_space" << &xfiber_schema_id_space
	 << "section_space_schema_product_structure" << &xsection_space_schema_product_structure;

  // Postconditions:

  ensure(result.contains_arg("base_space_id_space"));
  ensure((void *) result.value("base_space_id_space") == &xbase_space_id_space);
  ensure(result.contains_arg("fiber_schema_id_space"));
  ensure((void *) result.value("fiber_schema_id_space") == &xfiber_schema_id_space);
  ensure(result.contains_arg("section_space_schema_product_structure"));
  ensure((void *) result.value("section_space_schema_product_structure") == &xsection_space_schema_product_structure);

  // Exit:

  return result;
}

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_jims_index_space_state::
base_space() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *_base_space;
}

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_jims_index_space_state::
fiber_schema() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *_fiber_schema;
}

const sheaf::ij_product_structure&
fiber_bundle::section_space_schema_jims_index_space_state::
section_space_schema_product_structure() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *_section_space_schema_product;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::section_space_schema_jims_index_space_state::
section_space_schema_jims_index_space_state()
  : explicit_index_space_state(),
    _base_space(0),
    _fiber_schema(0),
    _section_space_schema_product(0)
{
  // Preconditions:
    
  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return; 
}

fiber_bundle::section_space_schema_jims_index_space_state::
section_space_schema_jims_index_space_state(const arg_list& xargs)
  : explicit_index_space_state(xargs)
{
  // Preconditions:
    
  require(precondition_of(explicit_index_space_state::explicit_index_space_state(xargs)));
  require(xargs.contains_arg("base_space_id_space"));
  require(xargs.contains_arg("fiber_schema_id_space"));
  require(xargs.contains_arg("section_space_schema_product_structure"));

  // Body:

  // Initialize data members from input arguments.

  _base_space =
    &reinterpret_cast<const index_space_handle*>
    ((void *) xargs.value("base_space_id_space"))->get_id_space();

  _fiber_schema =
    &reinterpret_cast<const index_space_handle*>
    ((void *) xargs.value("fiber_schema_id_space"))->get_id_space();

  _section_space_schema_product =
    reinterpret_cast<const ij_product_structure*>
    ((void *) xargs.value("section_space_schema_product_structure"))->clone();

  // Initialize the product structure.

  _product =
    new ij_product_structure(_base_space->end(), _fiber_schema->end());

  // Initialize the count and extrema.

  _begin = 0;
  _end   = _base_space->end()*_fiber_schema->end();
  _ct    = _base_space->ct()*_fiber_schema->ct();

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(explicit_index_space_state::explicit_index_space_state(xargs)));
  ensure(base_space() == *reinterpret_cast<const index_space_handle*>((void *) xargs.value("base_space_id_space")));
  ensure(fiber_schema() == *reinterpret_cast<const index_space_handle*>((void *) xargs.value("fiber_schema_id_space")));
  //ensure(section_space_schema_product_structure() == *(reinterpret_cast<const ij_product_structure*>((void*) xargs.value("section_space_schema_product_structure"))));

  // Exit:

  return; 
}

fiber_bundle::section_space_schema_jims_index_space_state::
~section_space_schema_jims_index_space_state()
{  
  // Preconditions:
    
  // Body:

  if(_base_space != 0)
  {
    _base_space->release_id_space();
  }

  if(_fiber_schema != 0)
  {
    _fiber_schema->release_id_space();
  }
  
  if(_section_space_schema_product != 0)
  {
    delete _section_space_schema_product;
  }
  
  // Postconditions:

  // Exit:

  return; 
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION SPACE SCHEMA INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_jims_index_space_state::
put_factors(const index_space_handle& xbase_space_id_space,
	    const index_space_handle& xfiber_schema_id_space,
	    const ij_product_structure& xsection_space_schema_product)
{
  // Preconditions:
    
  // Body:

  // Initialize data members from input arguments.

  _base_space = &xbase_space_id_space.get_id_space();

  _fiber_schema = &xfiber_schema_id_space.get_id_space();

  _section_space_schema_product = xsection_space_schema_product.clone();

  // Update the data members.

  update();

  // Postconditions:

  ensure(invariant());
  ensure(is_consistent());

  // Exit:

  return;
}

bool
fiber_bundle::section_space_schema_jims_index_space_state::
is_consistent() const
{
  // Preconditions:

  // Body:

  bool result =
    (_ct == _base_space->ct()*_fiber_schema->ct()) &&
    (_product->ub(0) == _base_space->end()) &&
    (_product->ub(1) == _fiber_schema->end());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_jims_index_space_state::
update()
{
  // Preconditions:

  // Body:

  // Update the product structure.

  product_structure().put_ubs(_base_space->end(), _fiber_schema->end());

  // Update the count and end.

  _end = _base_space->end()*_fiber_schema->end();
  _ct  = _base_space->ct()*_fiber_schema->ct();

  // Postconditions:

  ensure(is_consistent());

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
fiber_bundle::section_space_schema_jims_index_space_state::
operator==(const explicit_index_space_state& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const section_space_schema_jims_index_space_state& lother =
    dynamic_cast<const section_space_schema_jims_index_space_state&>(xother);

  bool result = explicit_index_space_state::operator==(xother);
  result = result && (*_base_space == *lother._base_space);
  result = result && (*_fiber_schema == *lother._fiber_schema);
  result = result && (*_section_space_schema_product ==
		      *lother._section_space_schema_product);

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_jims_index_space_state::
deep_size(bool xinclude_shallow) const
{
  // Preconditions:

  // Body:

  size_type result = fiber_bundle::deep_size(*this, xinclude_shallow);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::section_space_schema_jims_index_space_state&
fiber_bundle::section_space_schema_jims_index_space_state::
operator=(const explicit_index_space_state& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const section_space_schema_jims_index_space_state& lother =
    dynamic_cast<const section_space_schema_jims_index_space_state&>(xother);

  _base_space = &lother._base_space->get_id_space();
  _fiber_schema = &lother._fiber_schema->get_id_space();
  _section_space_schema_product = lother._section_space_schema_product->clone();

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

bool
fiber_bundle::section_space_schema_jims_index_space_state::
contains(pod_type xid) const
{
  // Preconditions:

  // Body:

  // Compute the tuple ids in the jims id space.

  pod_type lbase_id, lfiber_id;
  product_structure().tuple(xid, lbase_id, lfiber_id);

  // Only contains xid if the tuple values are in the
  // base space and fiber schema id spaces.

  bool result =
    _base_space->contains(lbase_id) && _fiber_schema->contains(lfiber_id);
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_jims_index_space_state::
contains_unglued_hub(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  // Compute the tuple ids in the hub id space.

  pod_type lbase_hub_id, lfiber_hub_id;
  _section_space_schema_product->tuple(xhub_id, lbase_hub_id, lfiber_hub_id);

  // Only contains xid if the tuple values are in the
  // base space and fiber schema id spaces.

  bool result =
    _base_space->contains_unglued_hub(lbase_hub_id) &&
    _fiber_schema->contains_unglued_hub(lfiber_hub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
fiber_bundle::section_space_schema_jims_index_space_state::
pod(pod_type xhub_id) const
{
  // Preconditions:

  // Body:

  pod_type result;

  // Compute the tuple ids in the hub id space.

  pod_type lbase_hub_id, lfiber_hub_id;
  _section_space_schema_product->tuple(xhub_id, lbase_hub_id, lfiber_hub_id);

  // Map into the jims id space.

  pod_type lbase_id = _base_space->pod(lbase_hub_id);
  pod_type lfiber_id = _fiber_schema->pod(lfiber_hub_id);

  // Compute the ordinal in the this id space.

  if(is_valid(lbase_id) && is_valid(lfiber_id))
  {
    product_structure().ordinal(lbase_id, lfiber_id, result);
  }
  else
  {
    result = invalid_pod_index();
  }
  
  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit

  return result;
}

sheaf::explicit_index_space_state::pod_type
fiber_bundle::section_space_schema_jims_index_space_state::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  // Body:

  pod_type result;

  // Compute the tuple ids in the jims id space.

  pod_type lbase_id, lfiber_id;
  product_structure().tuple(xid, lbase_id, lfiber_id);

  // Map tuple ids into the hub id space.

  pod_type lbase_hub_id = _base_space->hub_pod(lbase_id);
  pod_type lfiber_hub_id = _fiber_schema->hub_pod(lfiber_id);

  // Compute the ordinal id in the hub id space.

  if(is_valid(lbase_hub_id) && is_valid(lfiber_hub_id))
  {
    _section_space_schema_product->ordinal(lbase_hub_id, lfiber_hub_id, result);
  }
  else
  {
    result = invalid_pod_index();
  }

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

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
fiber_bundle::section_space_schema_jims_index_space_state::
new_product_structure(const abstract_product_structure& xproduct)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(has_product_structure());

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_jims_index_space_state::
delete_product_structure()
{
  // Preconditions:

  // Body:

  not_implemented();
  
  // Postconditions:

  ensure(!has_product_structure());

  // Exit:

  return;
}

const sheaf::ij_product_structure&
fiber_bundle::section_space_schema_jims_index_space_state::
product_structure() const
{
  // Preconditions:

  require(has_product_structure());

  // Body:

  const ij_product_structure& result =
    reinterpret_cast<ij_product_structure&>(*_product);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::ij_product_structure&
fiber_bundle::section_space_schema_jims_index_space_state::
product_structure()
{
  // Preconditions:

  require(has_product_structure());

  // Body:

  ij_product_structure& result =
    reinterpret_cast<ij_product_structure&>(*_product);

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

sheaf::size_type
fiber_bundle::section_space_schema_jims_index_space_state::
handle_pool_ct()
{
  // Preconditions:

  // Body:

  size_type result = handles().ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_jims_index_space_state::
handle_pool_deep_size()
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(handles(), true);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::section_space_schema_jims_index_space_state::
get_id_space() const
{
  // Preconditions:

  // Body:

  section_space_schema_jims_index_space_handle& result = handles().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_jims_index_space_state::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(allocated_id_space(xid_space));

  // Body:

  // Detach the handle.

  xid_space.detach();

  // Release the handle to the pool.

  handles().release(reinterpret_cast<section_space_schema_jims_index_space_handle&>(xid_space));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::section_space_schema_jims_index_space_state::
allocated_id_space(const index_space_handle& xid_space) const
{
  // Preconditions:

  // Body:

  const section_space_schema_jims_index_space_handle* lid_space =
    dynamic_cast<const section_space_schema_jims_index_space_handle*>(&xid_space);

  bool result = (lid_space != 0) && handles().allocated(*lid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<fiber_bundle::section_space_schema_jims_index_space_handle>&
fiber_bundle::section_space_schema_jims_index_space_state::
handles()
{
  // Preconditions:

  // Body:

  static list_pool<section_space_schema_jims_index_space_handle> result;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}


// ===========================================================
// ITERATOR POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
fiber_bundle::section_space_schema_jims_index_space_state::
iterator_pool_ct()
{
  // Preconditions:

  // Body:

  size_type result = iterators().ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_jims_index_space_state::
iterator_pool_deep_size()
{
  // Preconditions:

  // Body:

  size_type result = sheaf::deep_size(iterators(), true);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::section_space_schema_jims_index_space_state::
get_iterator() const
{
  // Preconditions:

  // Body:

  section_space_schema_jims_index_space_iterator& result = iterators().get();
  attach(result);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_jims_index_space_state::
release_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(allocated_iterator(xitr));

  // Body:

  // Detach the iterator.

  xitr.detach();

  // Release the iterator to the pool.

  iterators().release(reinterpret_cast<section_space_schema_jims_index_space_iterator&>(xitr));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::section_space_schema_jims_index_space_state::
allocated_iterator(const index_space_iterator& xitr) const
{
  // Preconditions:

  // Body:

  const section_space_schema_jims_index_space_iterator* litr =
    dynamic_cast<const section_space_schema_jims_index_space_iterator*>(&xitr);

  bool result = (litr != 0) && iterators().allocated(*litr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

sheaf::list_pool<fiber_bundle::section_space_schema_jims_index_space_iterator>&
fiber_bundle::section_space_schema_jims_index_space_state::
iterators()
{
  // Preconditions:

  // Body:

  static list_pool<section_space_schema_jims_index_space_iterator> result;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::section_space_schema_jims_index_space_state::
class_name() const
{
  static const string result("section_space_schema_jims_index_space_state");
  return result;
}

fiber_bundle::section_space_schema_jims_index_space_state*
fiber_bundle::section_space_schema_jims_index_space_state::
clone(const arg_list& xargs) const
{
  // Preconditions:

  // Body:

  section_space_schema_jims_index_space_state* result = new section_space_schema_jims_index_space_state(xargs);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_jims_index_space_state::
make_prototype()
{
  // Preconditions:

  // Body:

  section_space_schema_jims_index_space_state* lproto = new section_space_schema_jims_index_space_state();

  id_space_factory().insert_prototype(lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_jims_index_space_state::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const section_space_schema_jims_index_space_state*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_jims_index_space_state::
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

    invariance(!has_product_structure() || (product_structure().ub(0) == base_space().end()));
    invariance(!has_product_structure() || (product_structure().ub(1) == fiber_schema().end()));

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
fiber_bundle::
deep_size(const section_space_schema_jims_index_space_state& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Add contribution from _section_space_schema_product.

  result += deep_size(xn.section_space_schema_product_structure(), false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
