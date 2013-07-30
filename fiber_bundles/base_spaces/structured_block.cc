

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for class structured_block.

#include "assert_contract.h"
#include "block.impl.h"
#include "chart_point_3d.h"
#include "namespace_poset.h"
#include "poset_path.h"
#include "preorder_iterator.h"
#include "quad_connectivity.h"
#include "schema_descriptor.h"
#include "schema_poset_member.h"
#include "structured_block.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// STRUCTURED_BLOCK FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::poset_path&
fiber_bundle::structured_block::
standard_schema_path()
{

  // Preconditions:

  // Body:

  static const poset_path result(standard_schema_poset_name(),
                                 "structured_block_schema");

  // Postconditions:

  // Exit

  return result;
}

const sheaf::poset_path&
fiber_bundle::structured_block::
schema_path() const
{
  // Preconditions:

  // Body:

  const poset_path& result = standard_schema_path();

  // Postconditions:

  // Exit

  return result;
}


void
fiber_bundle::structured_block::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  // Structured_block schema does not introduce any new dofs.

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              homogeneous_block::standard_schema_path(),
                              "",
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path(), false));

  // Exit:

  return;
}

fiber_bundle::structured_block::
structured_block()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(! is_attached() );
}

fiber_bundle::structured_block::
~structured_block()
{

  // Preconditions:

  // Body:

  // Exit

  return;
}

// PROTECTED DATA MEMBERS

void
fiber_bundle::structured_block::
init_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Have just attached to a new or different host.
  // Initialize the handle data members for the different host.

  // Get the elements client id map.
  // d_cells_name(xdb, xdb) returns "_elements" no matter what xdb is.

  /// @error need reference counting

  subposet lsp(host(), base_space_poset::d_cells_name(2, 2));
  _elements_id_space = &lsp.id_space();
  lsp.detach_from_state();

  // Postconditions:

  ensure(unexecutable(data members created but not attached));

  // Exit

  return;
}

void
fiber_bundle::structured_block::
refine_coordinate(chart_point_coord_type& xcoord,
                  scoped_index::pod_type& xchart_id,
                  size_type xchart_id_ub) const
{
  // Preconditions:

  static const chart_point_coord_type ONE =
    1.0 + 1000.0*numeric_limits<chart_point_coord_type>::epsilon();

  require((-ONE <= xcoord) && (xcoord <= ONE));

  // Body:

  /// @todo precompute 0.5*xchart_id_ub and save it somewhere.

  chart_point_coord_type lcoord = (xcoord + 1.0)*0.5*xchart_id_ub;

  // Integer part is sequence id of refined chart id component,
  // fractional part is refined local coord component.

  chart_point_coord_type lref_chart;
  xcoord = (modf(lcoord, &lref_chart)*2.0) - 1.0;

  xchart_id = static_cast<scoped_index::pod_type>(lref_chart);

  // If lcoord in on boundary between two charts,
  // modf returns lower bound of greater chart.
  // This is acceptable unless lcoord in on the
  // upper bound of the domain, in which case
  // there is no greater chart and we want the
  // upper bound of the lesser chart.

  if(xchart_id == xchart_id_ub)
  {
    xchart_id--;
    xcoord = 1.0;
  }

  // Postconditions:

  ensure((xchart_id >= 0) && (xchart_id < xchart_id_ub));
  ensure((-ONE <= xcoord) && (xcoord <= ONE));

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// LOCAL_BASE_SPACE_MEMBER FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::chart_point*
fiber_bundle::structured_block::
refine_point(const chart_point& xpt) const
{
  chart_point* result;

  // Preconditions:

  require(precondition_of(refine_point_pa(xpt, *result)));

  // Body:

  result = const_cast<chart_point&>(xpt).clone();
  refine_point_pa(xpt, *result);

  // Postconditions:

  ensure(postcondition_of(refine_point_pa(xpt, *result)));

  // Exit:

  return result;
}

void
fiber_bundle::structured_block::
refine_point_pa(const chart_point& xpt, chart_point& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  require(xpt.chart_id() == index().pod());

  // One is tempted to require xpt.db() == db(), but the implementations
  // of this routine don't actually need it and in practice allowing xpt.db() > db()
  // enables preallocating chart points before one knows the exact dimension.

  require(xpt.db() >= db());
  require(result.db() >= db());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(covers(result.chart_id()));

  // Exit:

  return;
}

void
fiber_bundle::structured_block::
refine_point_pa(const chart_point& xpt, block<chart_point_3d>& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  require(xpt.chart_id() == index().pod());

  // One is tempted to require xpt.db() == db(), but the implementations
  // of this routine don't actually need it and in practice allowing xpt.db() > db()
  // enables preallocating chart points before one knows the exact dimension.

  require(xpt.db() >= db());
  require(db() <= 3);

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::chart_point*
fiber_bundle::structured_block::
unrefine_point(const chart_point& xpt) const
{
  chart_point* result;

  // Preconditions:

  require(precondition_of(unrefine_point_pa(xpt, *result)));

  // Body:

  result = const_cast<chart_point&>(xpt).clone();
  unrefine_point_pa(xpt, *result);

  // Postconditions:

  ensure(postcondition_of(unrefine_point_pa(xpt, *result)));

  // Exit:

  return result;
}

void
fiber_bundle::structured_block::
unrefine_point_pa(const chart_point& xpt, chart_point& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  /// @issue the following precondition attempts to require that
  /// xpt is a direct refinement of this. But covers() fails to correctly
  /// capture this requirement because there may be jrms between this
  /// and its direct refinement.

  // require(covers(xpt.chart_id()));

  // One is tempted to require xpt.db() == db(), but the implementations
  // of this routine don't actually need it and in practice allowing xpt.db() > db()
  // enables preallocating chart points before one knows the exact dimension.

  require(xpt.db() >= db());
  require(result.db() >= db());

  // Body:

  is_abstract();

  // Postcondition:

  ensure(result.chart_id() == index().pod());

  // Exit:

  return;
}

void
fiber_bundle::structured_block::
refine()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(!is_jim());

  // Exit:

  return;
}


void
fiber_bundle::structured_block::
unrefine()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!is_jim());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_jim());

  // Exit:

  return;
}

void
fiber_bundle::structured_block::
simplify()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(!is_jim());

  // Exit:

  return;
}


void
fiber_bundle::structured_block::
unsimplify()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!is_jim());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_jim());

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// HOMOGENEOUS_BLOCK FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// BASE_SPACE_MEMBER FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// TOTAL_POSET_MEMBER FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ABSTRACT_POSET_MEMBER FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::structured_block*
fiber_bundle::structured_block::
clone() const
{
  structured_block* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::structured_block::
invariant() const
{
  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(homogeneous_block::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    invariance(state_is_read_accessible() ? is_jim(false) : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return true;
}

bool
fiber_bundle::structured_block::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const structured_block*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::structured_block&
fiber_bundle::structured_block::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

fiber_bundle::structured_block&
fiber_bundle::structured_block::
operator=(const structured_block& xother)
{
  
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body

  not_implemented();
  
  // Postconditions

  ensure(invariant());
  
  // Exit

  return *this;
  
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

size_t
fiber_bundle::
deep_size(const structured_block& x0, bool xinclude_shallow)
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

