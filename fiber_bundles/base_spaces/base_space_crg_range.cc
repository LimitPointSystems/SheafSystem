// $RCSfile: base_space_crg_range.cc,v $ $Revision: 1.17 $ $Date: 2013/03/13 00:58:40 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class base_space_crg_range.

#include "base_space_crg_range.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "list_index_space_state.h"
#include "index_space_iterator.h"
#include "scoped_index.h"
#include "std_iomanip.h"
#include "std_string.h"
#include "std_strstream.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// BASE_SAPCE_CRG_RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::base_space_crg_range::
base_space_crg_range()
{
  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}

fiber_bundle::base_space_crg_range::
~base_space_crg_range()
{
  // Nothing to do.
}

void
fiber_bundle::base_space_crg_range::
cells_begin(scoped_index& result) const
{
  // Preconditions:

  // Body:

  result.put(hub_id_space(), cells_begin());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

void
fiber_bundle::base_space_crg_range::
cells_end(scoped_index& result) const
{
  // Preconditions:

  // Body:

  result.put(hub_id_space(), cells_end());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

int
fiber_bundle::base_space_crg_range::
db(pod_index_type xmbr_id) const
{
  // Preconditions:

  require(contains_member(xmbr_id));

  // Body:

  is_abstract();

  int result = -1; // Just to silence compiler warnings.

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::base_space_crg_range::
db(const scoped_index& xmbr_id) const
{
  // Preconditions:

  require(contains_member(xmbr_id));

  // Body:

  return db(xmbr_id.hub_pod());
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// BLOCK VERTICES TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::base_space_crg_range::
block_vertices_initialized() const
{
  return _block_vertices_id_space.is_attached();
}

const sheaf::index_space_handle&
fiber_bundle::base_space_crg_range::
block_vertices_id_space() const
{
  // Preconditions:

  require(block_vertices_initialized());

  // Body:

  const index_space_handle& result = _block_vertices_id_space;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_crg_range::
get_block_vertices_id_space_iterator() const
{
  // Preconditions:

  require(block_vertices_initialized());

  // Body:

  index_space_iterator& result = _block_vertices_id_space.get_iterator();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::base_space_crg_range::
release_block_vertices_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(block_vertices_initialized());
  require(allocated_block_vertices_id_space_iterator(xitr));

  // Body:

  _block_vertices_id_space.release_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::base_space_crg_range::
allocated_block_vertices_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(block_vertices_initialized());

  // Body:

  bool result = _block_vertices_id_space.allocated_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

string
fiber_bundle::base_space_crg_range::
block_vertices_name() const
{
  // Preconditions:

  // Body:

  string result;

  strstream lstr;
  lstr << poset_path::reserved_prefix()
       << "block_vertices_"
       << range_member();

  lstr >> result;

  // Postconditions:

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DOF TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::base_space_crg_range::
is_initialized() const
{
  bool result =
    implicit_crg_range::is_initialized() &&
    block_vertices_initialized();

  return result;
}

const string&
fiber_bundle::base_space_crg_range::
class_name() const
{
  static const string result("base_space_crg_range");
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::base_space_crg_range::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const base_space_crg_range*>(other) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::base_space_crg_range::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(implicit_crg_range::invariant());

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
// NON-MEMBER FUNCTIONS
// ===========================================================

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
fiber_bundle::
deep_size(const base_space_crg_range& xr, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}

