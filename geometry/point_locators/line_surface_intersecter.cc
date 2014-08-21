
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
/// Implementation for class line_surface_intersecter

#include "line_surface_intersecter.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"
#include "e3.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_poset.h"

using namespace std;
using namespace geometry;  // Workaround for MSVC++ bug
using namespace fiber_bundle::vd_algebra;
using namespace fiber_bundle::ed_algebra;
using namespace fiber_bundle::e3_algebra;

//#define DIAGNOSTIC_OUTPUT

// ===========================================================
// LINE_SURFACE_INTERSECTER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::line_surface_intersecter::
line_surface_intersecter(sec_e3& xcoords, const block<size_type>& xbin_ubs)
{
  
  // Preconditions:

  // Body:

  _coords = &xcoords;

  _coords->get_read_access();

  _host = &(_coords->schema().host()->base_space());
  _surface_id_space = &_host->blocks().id_space();
  _eval_id_space = &_coords->schema().evaluation().id_space();
  _locator = new d_array_point_locator<3, 2>(*_coords, xbin_ubs);
  
  _coords->release_access();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::line_surface_intersecter::
line_surface_intersecter(const line_surface_intersecter& xother)
{
  
  // Preconditions:

    
  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::line_surface_intersecter::
~line_surface_intersecter()
{  
  // Preconditions:

    
  // Body:  
  
  delete _locator;
  
  // Postconditions:

  // Exit:

  return; 
}

const fiber_bundle::sec_e3&
geometry::line_surface_intersecter::
coords() const
{
  return *_coords;
}

void
geometry::line_surface_intersecter::
intersect(const e3_lite& xp0, const e3_lite& xp1, intersection_set_type& xresult) const
{
  //cout << "Entering line_surface_intersecter::intersect:" << endl;
//   cerr << endl;
//   cerr << "Entering line_surface_intersecter::intersect:" << endl;

//   cout << "    xp0 = " << xp0 << endl;
//   cout << "    xp1 = " << xp1 << endl;
//   cout << "  _locator->lb() " << _locator->lb() << endl;
//   cout << "  _locator->ub() " << _locator->ub() << endl;
//   cout << endl;

  // Preconditions:

  /// @hack Only z-axis aligned lines.

  require(unexecutable("temporarily only implemented for lines parallel to z axis"));
  require(xp0[0] == xp1[0]);
  require(xp0[1] == xp1[1]);
  require(xp0[0] <= _locator->ub()[0]);
  require(xp0[1] <= _locator->ub()[1]);
  require(xp0[0] >= _locator->lb()[0]);
  require(xp0[1] >= _locator->lb()[1]);

  // Body:

  //  cout << "xp0: " << xp0 << endl;
  //  cout << "xp1: " << xp1 << endl;

  xresult.clear();

  d_bounding_box<3, 2> lbox;  
  d_bin_coordinates<3, 2> rel_pos;

  // Get the bounds for this eval member and put them in the bounding box.
  // Must convert from the global coordinate system to search
  // structure-relative coordinates.

  sec_vd_value_type gbl_pos[3];
  gbl_pos[0] = xp0[0];
  gbl_pos[1] = xp0[1];

  gbl_pos[2] = 0.0; // Doesn't matter what value this is.

  _locator->relative_position_pa(gbl_pos, 3, rel_pos);
  rel_pos[2] = 0;

//   cerr << "  lower bound: lbox.put_lb(rel_pos)" << endl;
//   cerr << "    gbl_pos[0], rel_pos[0] = " << gbl_pos[0] << " : " << rel_pos[0] << endl;
//   cerr << "    gbl_pos[1], rel_pos[1] = " << gbl_pos[1] << " : " << rel_pos[1] << endl;
//   cerr << "    gbl_pos[2], rel_pos[2] = " << gbl_pos[2] << " : " << rel_pos[2] << endl;
//   cerr << endl;

  lbox.put_lb(rel_pos);

  _locator->relative_position_pa(gbl_pos, 3, rel_pos);
  rel_pos[2] = (_locator->bin_ub()[2])-1;

//   cerr << "  upper bound: lbox.put_ub(rel_pos)" << endl;
//   cerr << "    gbl_pos[0], rel_pos[0] = " << gbl_pos[0] << " : " << rel_pos[0] << endl;
//   cerr << "    gbl_pos[1], rel_pos[1] = " << gbl_pos[1] << " : " << rel_pos[1] << endl;
//   cerr << "    gbl_pos[2], rel_pos[2] = " << gbl_pos[2] << " : " << rel_pos[2] << endl;
//   cerr << endl;

  lbox.put_ub(rel_pos);

  box_set_type lboxes;

  // Get intersection candidates.
    
  _locator->box_list(&lbox, lboxes);

  // Check each candidate for intersection.

  e3_lite lintersection;
  box_set_type::iterator lbox_itr = lboxes.begin();
  while(lbox_itr != lboxes.end())
  {
    //    cout << "Testing for intersection with triangle " << (*lbox_itr)->member_id().hub_pod() << endl;

    if(intersect(xp0, xp1, **lbox_itr, lintersection))
    {
      // Found an intersection;
      // insert the result.

      //      cout << "found intersection" << endl;
      
      /// @hack Only z-axis aligned lines.

      /// @issue: Subsequent intersections at the same z will not be entered.
      // This is the behavior we want for an intersection on an edge between
      // two triangles in the same surface, but not what we want if two
      // surfaces happen to overlap at the intersection point.

      intersection_set_type::value_type lval(lintersection[2],(*lbox_itr)->branch_id().pod());
      xresult.insert(lval);
    }
    
    ++lbox_itr;
  }
  
  // Postconditions:


  // Exit:

//   //cout << "Leaving line_surface_intersecter::intersect:" << endl;
//   cerr << "Leaving line_surface_intersecter::intersect:" << endl;
//   cerr << endl;

  return;
}


// PROTECTED MEMBER FUNCTIONS


geometry::line_surface_intersecter::
line_surface_intersecter()
{
  
  // Preconditions:

    
  // Body:
  
  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

bool
geometry::line_surface_intersecter::
intersect(const e3_lite& xpp, const e3_lite& xpq, const d_bounding_box<3, 2>& xbox, e3_lite& xr) const
{
  // Preconditions:


  // Body:

  // Line-triangle intersection from Christer Erickson,
  // "Real Time Collision Detection", Section 5.3.4

  // Get the coordinates of the vertices of the triangle

  sec_vd_dof_type* ldofs = _locator->gathered_dofs().base() + xbox.dofs_index();
  
  vd_value_type ax = ldofs[0], ay = ldofs[1], az = ldofs[2];
  e3_lite a(ax, ay, az);

  vd_value_type bx = ldofs[3], by = ldofs[4], bz = ldofs[5];
  e3_lite b(bx, by, bz);

  vd_value_type cx = ldofs[6], cy = ldofs[7], cz = ldofs[8];
  e3_lite c(cx, cy, cz);

  //   cout << "a: " << a << endl;
  //   cout << "b: " << b << endl;
  //   cout << "c: " << c << endl;
  
  
  // Create vectors for edges

  e3_lite pq(xpq);
  pq -= xpp;

  e3_lite pa(a);
  pa -= xpp;

  e3_lite pb(b);
  pb -= xpp;

  e3_lite pc(c);
  pc -= xpp;

  // Test if pq is inside edges bc, ca, and ab. Done by testing
  // that the signed tetrahedral volumes, computed using scalar triple
  // products, are all the same sign. Same sign means either all three
  // are <= 0 or all three are >= 0.

  e3_lite m;
  cross(pq, pc, m);
  
  vd_value_type u = dot(pb, m);

  //  cout << "u: " << u << endl;  

  vd_value_type v = -dot(pa, m);

  //  cout << "v: " << v << endl;

  bool same_sign = ((u < 0) == (v < 0)) || (u == 0) || (v == 0);

  //  cout << "same_sign: " << boolalpha << same_sign << noboolalpha << endl;
  
  if(!same_sign) return false;
  
  e3_lite n;
  cross(pb, pa, n);
  vd_value_type w = dot(pq, n);

  //  cout << "w: " << w << endl;

  same_sign = ((u < 0) == (w < 0)) || (u == 0) || (w == 0);

  //  cout << "same_sign: " << boolalpha << same_sign << noboolalpha << endl;

  if(!same_sign) return false;

  // If all three are zero, the line is parallel to the triangle;
  // we can't compute an intersection point.

  bool all_zero = (u == 0) && (v == 0) && (w == 0) ;
  
  if(all_zero) return false;  

  // Found an intersection.
  
  // Compute the barycentric coordinates of the intersection.

  vd_value_type denom = 1.0/(u + v + w);
  u *= denom;
  v *= denom;
  w *= denom;
  
  // Compute the intersection point from the barycentric coordinates.

  xr[0] = u*ax + v*bx + w*cx;
  xr[1] = u*ay + v*by + w*cy;
  xr[2] = u*az + v*bz + w*cz;  

  // Postconditions:


  // Exit:

  return true;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::line_surface_intersecter::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const line_surface_intersecter*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::line_surface_intersecter*
geometry::line_surface_intersecter::
clone() const
{
  line_surface_intersecter* result;
  
  // Preconditions:

  // Body:
  
  result = new line_surface_intersecter();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::line_surface_intersecter&
geometry::line_surface_intersecter::
operator=(const line_surface_intersecter& xother)
{
  
  // Preconditions:

    
  // Body:
  
  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

bool
geometry::line_surface_intersecter::
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
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
std::ostream&
geometry::
operator<<(std::ostream& xos, const line_surface_intersecter& xp)
{
  // Preconditions:


  // Body:

  xos << *(xp._host) << endl;

  xos << *(xp._coords->host()) << endl;
  
  xos << *(xp._locator) << endl;

  // Postconditions:


  // Exit:

  return xos;
}
