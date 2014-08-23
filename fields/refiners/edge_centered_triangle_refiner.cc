
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
/// Implementation for class edge_centered_triangle_refiner

#include "ComLimitPoint/fields/edge_centered_triangle_refiner.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fields/field_refinement_buffer.h"
#include "ComLimitPoint/sheaf/wsv_block.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1

// ===========================================================
// EDGE_CENTERED_TRIANGLE_REFINER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::edge_centered_triangle_refiner::
edge_centered_triangle_refiner(const field_refinement_policy& xpolicy)
    : edge_centered_polygon_refiner(xpolicy)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(&policy() == &xpolicy);

  return;
}


fields::edge_centered_triangle_refiner::
edge_centered_triangle_refiner(const edge_centered_triangle_refiner& xother)
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

fields::edge_centered_triangle_refiner::
edge_centered_triangle_refiner()
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return;
}

void
fields::edge_centered_triangle_refiner::
modify_crg(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  require(xbuffer.base_space != 0);
  require(xbuffer.base_space->in_jim_edit_mode());

  // Body:

  // The vertices of the edge-centered subdivision are original vertices
  // and the center of each edge:
  //
  //          4
  //         * *
  //        *   *
  //       *     *
  //      5+++++++3
  //     * +     + *
  //    *   +   +   *
  //   *     + +     *
  //  0*******1*******2
  //
  // There is one triangle for in the center plus one for each edge center.
  // If we start with and edge center and traverse the boundary in the
  // CCW direction, the connectivity of each edge-centered triangle is
  // given by 3 consecutive vertices at this refinement depth. If the boundary
  // contains additional vertices from adjacent, more highly refined triangles,
  // these appear between the desired vertices and should appear in the lower
  // cover of the new triangle which contains them.

  make_new_vertices(xbuffer);

  make_new_zones(xbuffer);

  // Create the new triangle in the center of the original.

  base_space_poset* lbase = xbuffer.base_space;
  scoped_index lzone_id = xbuffer.zone_id;
  int lzone_depth = lbase->refinement_depth(lzone_id);
  int lnew_depth  = lzone_depth + 1;

  scoped_index lnew_tri = lbase->member_id(create_zone(*lbase, lnew_depth), false);
  _refined_zone_ids.push_back(lnew_tri);

  // Create the upper cover of the new triangle.

  lbase->new_link(lzone_id, lnew_tri);

  // Create the lower cover.

  lbase->new_link(lnew_tri, _vertex_ids[1]);
  lbase->new_link(lnew_tri, _vertex_ids[3]);
  lbase->new_link(lnew_tri, _vertex_ids[5]);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "triangle: " << setw(6) << lnew_tri;
  cout << "  lower cover: ";
  cover_set_state& lnew_tri_cvr = lbase->lower_cover(lnew_tri);
  copy(lnew_tri_cvr.begin(),
       lnew_tri_cvr.end(),
       ostream_iterator<scoped_index>(cout, " "));
  cout << endl << endl;
#endif

  // Postconditions:

  ensure(_refined_zone_ids.ct() == refined_zone_ct());

  // Exit:

  return;
}

sheaf::size_type
fields::edge_centered_triangle_refiner::
unrefined_vertex_ct() const
{

  // Preconditions:


  // Body:

  static size_type result = 3;

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fields::edge_centered_triangle_refiner::
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
fields::edge_centered_triangle_refiner::
is_zone_centered_refiner() const
{
  bool result;

  // Preconditions:


  // Body:

  result = false;

  // Postconditions:


  // Exit:

  return result;
}

const sheaf::block<sheaf::size_type>&
fields::edge_centered_triangle_refiner::
first_vertex_index() const
{

  // Preconditions:


  // Body:

  // The vertices of the edge-centered subdivision are original vertices
  // and the center of each edge:
  //
  //          4
  //         * *
  //        *   *
  //       *     *
  //      5+++++++3
  //     * +     + *
  //    *   +   +   *
  //   *     + +     *
  //  0*******1*******2
  //
  // There is one triangle for in the center plus one for each edge center.
  // The edge centers are the first vertex of each refined zone,
  // and the first entry is duplicated at the end

  static const wsv_block<size_type> result("1 3 5 1");

  // Postconditions:

  ensure(result.ct() > 1);

  // Exit:

  return result;
}


// PRIVATE MEMBERS

//const sheaf::size_type
//fields::edge_centered_triangle_refiner::
//REFINED_ZONE_CT;


// ===========================================================
// LOCAL_FIELD_REFINER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fields::edge_centered_triangle_refiner::
zone_type_name() const
{
  // Preconditions:


  // Body:

  static const string result("triangle_nodes");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const fiber_bundle::chart_point_coord_type*
fields::edge_centered_triangle_refiner::
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
        0.5,  0.0,  0.0,  0.0,  0.5,  0.5
      },
      {-0.5, -0.5,  0.5,  0.5,  0.0,  0.0},
      { 0.0,  0.5,  0.5, -0.5, -0.5,  0.5},
      { 0.0, -0.5,  0.5,  0.5,  0.5,  0.0}
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

fields::edge_centered_triangle_refiner*
fields::edge_centered_triangle_refiner::
clone() const
{
  edge_centered_triangle_refiner* result;

  // Preconditions:

  // Body:

  result = new edge_centered_triangle_refiner();

  // Postconditions:

  ensure(result != 0);
  ensure(invariant());
  
  ensure(result->invariant());
  ensure(is_same_type(result));

  return result;
}

fields::edge_centered_triangle_refiner&
fields::edge_centered_triangle_refiner::
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
fields::edge_centered_triangle_refiner&
fields::edge_centered_triangle_refiner::
operator=(const edge_centered_triangle_refiner& xother)
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

fields::edge_centered_triangle_refiner::
~edge_centered_triangle_refiner()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}


bool
fields::edge_centered_triangle_refiner::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && local_field_refiner::invariant();

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
fields::edge_centered_triangle_refiner::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const edge_centered_triangle_refiner*>(xother) != 0;

  // Postconditions:

  return result;

}

