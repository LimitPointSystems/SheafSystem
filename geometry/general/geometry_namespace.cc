
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

// Implementation for class geometry_namespace

#include "geometry_namespace.h"

#include "assert_contract.h"
#include "at0.h"
#include "base_space_member.h"
#include "base_space_member_prototype.h"
#include "error_message.h"
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "poset_path.h"
#include "sec_rep_descriptor.h"
#include "sec_rep_descriptor_poset.h"
#include "std_iostream.h"
#include "wsv_block.h"

//#define DIAGNOSTIC_OUTPUT

using namespace geometry; // Workaround for MSVC++ bug.

// =============================================================================
// GEOMETRY_NAMESPACE FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS


geometry::geometry_namespace::
geometry_namespace(const string& xname)
{
  // Preconditions:

  require(precondition_of(new_state(xname)));

  // Body:

  // Create the state.

  new_state(xname);

  // Postconditions:

  ensure(postcondition_of(new_state(xname)));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

geometry::geometry_namespace::
geometry_namespace()
{

  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}


geometry::geometry_namespace::
geometry_namespace(const geometry_namespace& xother)
    : fiber_bundles_namespace(xother)
{

  // Preconditions:

  require(precondition_of(fiber_bundles_namespace(xother)));

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(fiber_bundles_namespace(xother)));

  // Exit:

  return;
}

///
geometry::geometry_namespace::
~geometry_namespace()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
// FIBER_BUNDLES_NAMESPACE FACET
// ===========================================================

void
geometry::geometry_namespace::
make_base_space_member_prototypes(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  fiber_bundles_namespace::make_base_space_member_prototypes(xspace);
  
  make_line_prototype(xspace);
  make_plane_prototype(xspace);
  make_surface_prototype(xspace);
  make_line_web_prototype(xspace);
  make_polygon_prototype(xspace);
 // make_kd_lattice_prototypes(xspace);

  // Postconditions:


  // Exit:

  return;
}

void
geometry::geometry_namespace::
make_line_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lblk(xspace, "line", 1, "", false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("line"));

  // Exit:

  return;
}

void
geometry::geometry_namespace::
make_plane_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lblk(xspace, "plane", 2, "", false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("plane"));

  // Exit:

  return;
}

void
geometry::geometry_namespace::
make_surface_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lblk(xspace, "surface", 2, "", false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("surface"));

  // Exit:

  return;
}

void
geometry::geometry_namespace::
make_line_web_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lblk(xspace, "line_web", 2, "", false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("line_web"));

  // Exit:

  return;
}

void
geometry::geometry_namespace::
make_polygon_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lblk(xspace, "polygon", 2, "", false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("polygon"));

  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

///
bool
geometry::geometry_namespace::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const geometry_namespace*>(other) != 0;

  // Postconditions:

  return result;
}

///
geometry::geometry_namespace*
geometry::geometry_namespace::
clone() const
{
  geometry_namespace* result;

  // Preconditions:

  // Body:

  result = new geometry_namespace();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
geometry::geometry_namespace&
geometry::geometry_namespace::
operator=(const geometry_namespace& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
geometry::geometry_namespace::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(fiber_bundles_namespace::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

