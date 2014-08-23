
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
/// Implementation for class barycentric_quad_refiner

#include "ComLimitPoint/fields/barycentric_quad_refiner.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/sheaf/wsv_block.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1

// ===========================================================
// BARYCENTRIC_QUAD_REFINER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::barycentric_quad_refiner::
barycentric_quad_refiner(const field_refinement_policy& xpolicy)
    : edge_centered_polygon_refiner(xpolicy)
{
  // Preconditions:

  // Body:

  reserve_vertex_buffers();

  // Postconditions:

  ensure(invariant());
  ensure(&policy() == &xpolicy);

  return;
}


fields::barycentric_quad_refiner::
barycentric_quad_refiner(const barycentric_quad_refiner& xother)
    : edge_centered_polygon_refiner(xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return;
}


// PROTECTED MEMBERS FUNCTIONS

fields::barycentric_quad_refiner::
barycentric_quad_refiner()
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return;
}

sheaf::size_type
fields::barycentric_quad_refiner::
unrefined_vertex_ct() const
{

  // Preconditions:


  // Body:

  static size_type result = 4;

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fields::barycentric_quad_refiner::
refined_zone_ct() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = REFINED_ZONE_CT;

  // Postconditions:

  ensure(result > 1);

  // Exit:

  return result;
}

bool
fields::barycentric_quad_refiner::
is_zone_centered_refiner() const
{
  bool result;

  // Preconditions:


  // Body:

  result = true;

  // Postconditions:


  // Exit:

  return result;
}

const sheaf::block<sheaf::size_type>&
fields::barycentric_quad_refiner::
first_vertex_index() const
{

  // Preconditions:


  // Body:

  // The vertices of the barycentric subdivision are original vertices,
  // the center of each edge, and the center of the zone:
  //
  //  6*******5*******4
  //  *       +       *
  //  *       +       *
  //  *       +       *
  //  7+++++++C+++++++3
  //  *       +       *
  //  *       +       *
  //  *       +       *
  //  0*******1*******2
  //
  // The edge centers are the first vertex of each refined zone,
  // and the first entry is duplicated at the end

  static const wsv_block<size_type> result("1 3 5 7 1");

  // Postconditions:

  ensure(result.ct() > 1);

  // Exit:

  return result;
}


// ===========================================================
// LOCAL_FIELD_REFINER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fields::barycentric_quad_refiner::
zone_type_name() const
{
  // Preconditions:


  // Body:

  static const string result("quad_nodes");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const fiber_bundle::chart_point_coord_type*
fields::barycentric_quad_refiner::
local_coordinates_map(size_type xi) const
{
  // Preconditions:

  require(xi < refined_zone_ct());

  // Body:

  // Affine transformation u'[i] = T[i][j]*u[j] + T[i][db];
  // with sum convention over  0 <= j < db.

  // Specifically:
  //
  // u' = a*u +b*v + c;
  // v' = d*u _e*v + f.
  //
  // map = {a, b, c, d, e, f}
  // One such map for each refined zone.

  // 6 = db*(db+1)

  static const chart_point_coord_type lmap[REFINED_ZONE_CT][6] =
    {
      {
        0.5,  0.0,  0.5,  0.0,  0.5, -0.5
      },
      {  0.0, -0.5,  0.5,  0.5,  0.0,  0.5 },
      { -0.5,  0.0, -0.5,  0.0, -0.5,  0.5 },
      {  0.0,  0.5, -0.5, -0.5,  0.0, -0.5 }
    };


  const chart_point_coord_type* result = lmap[xi];

  // Postconditions:

  // Exit:

  return result;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::barycentric_quad_refiner*
fields::barycentric_quad_refiner::
clone() const
{
  barycentric_quad_refiner* result;

  // Preconditions:

  // Body:

  result = new barycentric_quad_refiner();

  // Postconditions:

  ensure(result != 0);
  //  ensure(invariant());
  ensure(result->invariant());
  ensure(is_same_type(result));

  return result;
}

fields::barycentric_quad_refiner&
fields::barycentric_quad_refiner::
operator=(const local_field_refiner& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return *this;
}

///
fields::barycentric_quad_refiner&
fields::barycentric_quad_refiner::
operator=(const barycentric_quad_refiner& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fields::barycentric_quad_refiner::
~barycentric_quad_refiner()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

bool
fields::barycentric_quad_refiner::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && edge_centered_polygon_refiner::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  return result;
}

bool
fields::barycentric_quad_refiner::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const barycentric_quad_refiner*>(xother) != 0;

  // Postconditions:

  return result;

}


// PRIVATE MEMBERS

//const sheaf::size_type
//fields::barycentric_quad_refiner::
//REFINED_ZONE_CT;
