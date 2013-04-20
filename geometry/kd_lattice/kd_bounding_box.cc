

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_bounding_box

#include "kd_bounding_box.h"

#include "assert_contract.h"
#include "kd_zone.h"
#include "tolerance_comparison.h"

using namespace geometry; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;

// ===========================================================
// KD_BOUNDING_BOX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_bounding_box::
kd_bounding_box()
  : _lb(0.0), _ub(0.0)
{
  
  // Preconditions:

    
  // Body:
  
  // Necessary to initialize _lb and _ub to something,
  // otherwise uninitialized value may be NaN, which 
  // can't be compared for equality to anything, even
  // iself. Hence it blows assertions, for instance when
  // a block of bounding boxes reallocates and copies
  // the old block to the new.

  // Postconditions:

  ensure(lb() == 0.0);
  ensure(ub() == 0.0);
  
  // Exit:

  return; 
}

geometry::kd_bounding_box::
kd_bounding_box(const e3_lite& xlb, const e3_lite& xub)
  : _lb(xlb), _ub(xub)
{
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

geometry::kd_bounding_box::
~kd_bounding_box()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

fiber_bundle::e3_lite&
geometry::kd_bounding_box::
lb()
{
  return _lb;
}

const fiber_bundle::e3_lite&
geometry::kd_bounding_box::
lb() const
{
  return _lb;
}

fiber_bundle::e3_lite&
geometry::kd_bounding_box::
ub()
{
  return _ub;
}

const fiber_bundle::e3_lite&
geometry::kd_bounding_box::
ub() const
{
  return _ub;
}

fiber_bundle::e3_lite
geometry::kd_bounding_box::
size() const
{
  // cout << endl << "Entering kd_bounding_box::size." << endl;

  // Preconditions:


  // Body:

  e3_lite result;
  subtract(_ub, _lb, result);

  // Postconditions:

  ensure_for_all(i, 0, 3, result[i] >= 0.0);
  
  // Exit:

  // cout << "Leaving kd_bounding_box::size." << endl;
  return result;
}

geometry::kd_bounding_box&
geometry::kd_bounding_box::
operator=(const kd_bounding_box& xother)
{
  // cout << endl << "Entering kd_bounding_box::operator==." << endl;

  // Preconditions:


  // Body:

  _lb = xother._lb;
  _ub = xother._ub;
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::operator==." << endl;
  return *this;
}

bool
geometry::kd_bounding_box::
operator==(const kd_bounding_box& xother) const
{
  // cout << endl << "Entering kd_bounding_box::operator==." << endl;

  // Preconditions:


  // Body:

  bool result = (_lb == xother._lb) && (_ub == xother._ub);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::operator==." << endl;
  return result;
}

bool
geometry::kd_bounding_box::
contains(const kd_bounding_box& xbox) const
{
  // cout << endl << "Entering kd_bounding_box::contains." << endl;

  // Preconditions:


  // Body:

  bool result = 
    (_lb[0] <= xbox._lb[0]) && (xbox._ub[0] <= _ub[0]) &&
    (_lb[1] <= xbox._lb[1]) && (xbox._ub[1] <= _ub[1]) &&
    (_lb[2] <= xbox._lb[2]) && (xbox._ub[2] <= _ub[2]);
  

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::contains." << endl;
  return result;
}

bool
geometry::kd_bounding_box::
contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_bounding_box::contains_point." << endl;

  // Preconditions:


  // Body:

  bool result = 
    (_lb[0] <= xpt[0]) && (xpt[0] <= _ub[0]) &&
    (_lb[1] <= xpt[1]) && (xpt[1] <= _ub[1]) &&
    (_lb[2] <= xpt[2]) && (xpt[2] <= _ub[2]);
  

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::contains_point." << endl;
  return result;
}

bool
geometry::kd_bounding_box::
interior_contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_bounding_box::interior_contains_point." << endl;

  // Preconditions:


  // Body:

  //   using sheaf::c_lt;
  //   using sheaf::c_gt;
  
  //   bool result = 
  //     c_gt(xpt[0], _lb[0], xtolerance[0]) && c_lt(xpt[0], _ub[0], xtolerance[0]) &&
  //     c_gt(xpt[1], _lb[1], xtolerance[1]) && c_lt(xpt[1], _ub[1], xtolerance[1]) &&
  //     c_gt(xpt[2], _lb[2], xtolerance[2]) && c_lt(xpt[2], _ub[2], xtolerance[2]);

  bool result = 
    (_lb[0] < xpt[0]) && (xpt[0] < _ub[0]) &&
    (_lb[1] < xpt[1]) && (xpt[1] < _ub[1]) &&
    (_lb[2] < xpt[2]) && (xpt[2] < _ub[2]);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::interior_contains_point." << endl;
  return result;
}

bool
geometry::kd_bounding_box::
boundary_contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_bounding_box::boundary_contains_point." << endl;

  // Preconditions:


  // Body:

  bool result = 
    (_lb[0] == xpt[0]) || (xpt[0] == _ub[0]) ||
    (_lb[1] == xpt[1]) || (xpt[1] == _ub[1]) ||
    (_lb[2] == xpt[2]) || (xpt[2] == _ub[2]);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::boundary_contains_point." << endl;
  return result;
}
 
bool
geometry::kd_bounding_box::
contains_line(const pt_list& xline) const
{
  // cout << endl << "Entering kd_bounding_box::contains_line." << endl;

  // Preconditions:

  
  // Body:

  bool result = true;

  for(pt_list::const_iterator p = xline.begin(); p != xline.end(); ++p)
  {
    if(!contains_point(*p))
    {
      result = false;
      break;
    }
  }  

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::contains_line." << endl;
  return result;
}


geometry::kd_bounding_box::out_code_2d_type
geometry::kd_bounding_box::
out_code_2d_from_int(int xcode)
{
  // Preconditions:

  // Body:

  out_code_2d_type result;
  
  switch(xcode)
  {
    case INSIDE:
      result = INSIDE;
      break;
    case LEFT:
      result = LEFT;
      break;
    case RIGHT:
      result = RIGHT;
      break;
    case BOTTOM:
      result = BOTTOM;
      break;
    case TOP:
      result = TOP;
      break;
    case CLIPPED:
      result = CLIPPED;
      break;
    default:
      result = NOT_AN_OUT_CODE_2D;
      break;
  }
  
      
  // Postconditions:

  // Exit:

  return result;
}

int
geometry::kd_bounding_box::
out_code_2d(const e3_lite& xpt, int xu, int xv) const
{
  // cout << endl << "Entering kd_bounding_box::out_code_2d." << endl;
  // cout << *this << endl;
  // cout << "xpt:" << xpt << "  xu:" << setw(3) << xu  << "  xv:" << setw(3) << xv << endl;

  // Preconditions:

  // Body:

  const vd_value_type& lptu = xpt[xu];
  const vd_value_type& lptv = xpt[xv];

  int result = INSIDE;
  
  if(lptu <= _lb[xu])
  {
    result |= LEFT;
  }
  else if(lptu >= _ub[xu])
  {
    result |= RIGHT;
  }

  if(lptv <= _lb[xv])
  {
    result |= BOTTOM;
  }
  else if(lptv >= _ub[xv])
  {
    result |= TOP;
  }

  // Postconditions:

  // Exit:

  // cout << "result: " << parse_out_code_2d(result) << endl;
  // cout << "Leaving kd_bounding_box::out_code_2d." << endl;
  return result;
}

int
geometry::kd_bounding_box::
out_code_2d(double xpu, double xpv, int xu, int xv, int xhistory) const
{
  // cout << endl << "Entering kd_bounding_box::out_code_2d." << endl;
  // cout << *this << endl;
  // cout << setprecision(18) << scientific;
  // cout << "xpu:" << setw(27) << xpu  << " xpv:" << setw(27) << xpv;
  // cout << "  xu:" << setw(3) << xu  << "  xv:" << setw(3) << xv << endl;
  // cout << setprecision(6) << fixed;

  // Preconditions:


  // Body:

  int result = INSIDE;
  
  if(!(xhistory & LEFT) && (xpu <= _lb[xu]))
  {
    result |= LEFT;
  }
  else if(!(xhistory & RIGHT) && (xpu >= _ub[xu]))
  {
    result |= RIGHT;
  }
  else if(!(xhistory & BOTTOM) && (xpv <= _lb[xv]))
  {
    result |= BOTTOM;
  }
  else if(!(xhistory & TOP) && (xpv >= _ub[xv]))
  {
    result |= TOP;
  }

  // Postconditions:

  // Exit:

  // cout << "Leaving kd_bounding_box::out_code_2d." << endl;
  return result;
}

int
geometry::kd_bounding_box::
clip_2d(const e3_lite& xp0, e3_lite& xp1, int xu, int xv) const
{
  // cout << endl << "Entering kd_bounding_box::clip_2d." << endl;
  // cout << "bounding box: " << *this << endl;
  // cout << "xp0: " << xp0 << "  xp1: " << xp1 << endl;
  // cout << "xu: " << xu << "  xv: " << xv << endl;

  // Preconditions:

  require(contains_point(xp0));
  
  // Body:

  // $$SCRIBBLE: this routine will clip a segment arbitrarily close
  // to a corner of the bounding box. That cause no trouble here,
  // but will result in outside part of the segment cutting across
  // the corner of some other face arbitrarily close to the corner,
  // making a short segment and a skinny triangle. This causes
  // trouble later on. One place to apply vertex welding is right
  // here, by forcing such near misses into the corner.

  int lhistory = 0;

  const vd_value_type& lx0 = xp0[xu];
  const vd_value_type& ly0 = xp0[xv];


  int lcode0 = INSIDE;

  // cout << "xp0  " << lx0 << "  " << ly0 << "  " << out_code_2d_from_int(lcode0) << endl;

  vd_value_type& lx1 = xp1[xu];
  vd_value_type& ly1 = xp1[xv];

  int lprev_code1 = INSIDE;
  int lcode1 = out_code_2d(lx1, ly1, xu, xv, lhistory);

  while(lcode1 != INSIDE)
  {
    // cout << "xp1  " << lx1 << "  " << ly1 << "  " << parse_out_code_2d(lcode1) << endl;
  
    // xp1 is out of bounds; find where it intersects the boundary.

    const vd_value_type& lxmin = _lb[xu];
    const vd_value_type& lxmax = _ub[xu];
    const vd_value_type& lymin = _lb[xv];
    const vd_value_type& lymax = _ub[xv];
      
    if(lcode1 & LEFT)
    {
      if(lx1 < lxmin)
      {  
        // xp1 is strictly left of the rectangle; 
        // move it to the left bondary

        ly1 = ly0 + (ly1 - ly0)*(lxmin - lx0)/(lx1 - lx0);
        lx1 = lxmin;
        lhistory |= CLIPPED;
      }      
      lhistory |= LEFT;
    }
    else if(lcode1 & RIGHT)
    {
      if(lx1 > lxmax)
      {
        // xp1 is strictly right of the rectangle;
        // move it to the right bondary

        ly1 = ly0 + (ly1 - ly0)*(lxmax - lx0)/(lx1 - lx0);
        lx1 = lxmax;
        lhistory |= CLIPPED;
      }
      lhistory |= RIGHT;
    }
    else if(lcode1 & BOTTOM)
    {
      if(ly1 < lymin)
      {
        // xp1 is below rectangle;
        // move it to the bottom bondary

        lx1 = lx0 + (lx1 - lx0)*(lymin - ly0)/(ly1 - ly0);
        ly1 = lymin;
        lhistory |= CLIPPED;
      }      
      lhistory |= BOTTOM;
    }
    else if(lcode1 & TOP)
    {
      if(ly1 > lymax)
      {
        // xp1 is above rectangle;
        // move it to the top bondary

        lx1 = lx0 + (lx1 - lx0)*(lymax - ly0)/(ly1 - ly0);
        ly1 = lymax;
        lhistory |= CLIPPED;
      }
      lhistory |= TOP;
    }

    // Recompute the out code.

    lprev_code1 = lcode1;
    lcode1 = out_code_2d(lx1, ly1, xu, xv, lhistory);
  }

  int result = lprev_code1 | (lhistory & kd_bounding_box::CLIPPED);
  
  // cout << "result  " << xp1 << "  " << parse_out_code_2d(result) << endl;
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::clip_2d." << endl;
  return result;
}

int
geometry::kd_bounding_box::
out_code_3d(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_bounding_box::out_code_3d." << endl;

  // Preconditions:


  // Body:

  int result = INSIDE_3D;
  
  if(xpt[0] < _lb[0])
  {
    result |= OUTSIDE_FACE2;
  }
  else if(xpt[0] > _ub[0])
  {
    result |= OUTSIDE_FACE3;
  }

  if(xpt[1] < _lb[1])
  {
    result |= OUTSIDE_FACE4;
  }
  else if(xpt[1] > _ub[1])
  {
    result |= OUTSIDE_FACE5;
  }
  
  if(xpt[2] < _lb[2])
  {
    result |= OUTSIDE_FACE0;
  }
  else if(xpt[2] > _ub[2])
  {
    result |= OUTSIDE_FACE1;
  }


  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::out_code_3d." << endl;
  return result;
}

int
geometry::kd_bounding_box::
in_code_3d(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_bounding_box::out_code_3d." << endl;

  // Preconditions:


  // Body:

  int result = STRICT_INSIDE_3D;
  
  if(xpt[0] <= _lb[0])
  {
    result |= FACE2;
  }
  else if(xpt[0] >= _ub[0])
  {
    result |= FACE3;
  }

  if(xpt[1] <= _lb[1])
  {
    result |= FACE4;
  }
  else if(xpt[1] >= _ub[1])
  {
    result |= FACE5;
  }
  
  if(xpt[2] <= _lb[2])
  {
    result |= FACE0;
  }
  else if(xpt[2] >= _ub[2])
  {
    result |= FACE1;
  }


  // Postconditions:


  // Exit:

  // cout << "Leaving kd_bounding_box::out_code_3d." << endl;
  return result;
}

int
geometry::kd_bounding_box::
local_vertex_id(int xin_code_3d)
{
  // cout << endl << "Entering kd_bounding_box::local_vertex_id." << endl;

  // Preconditions:


  // Body:

  int result;
  
  switch(xin_code_3d)
  {
    case VERTEX0:
      result = 0;
      break;
    case VERTEX1:
      result = 1;
      break;
    case VERTEX2:
      result = 2;
      break;
    case VERTEX3:
      result = 3;
      break;
    case VERTEX4:
      result = 4;
      break;
    case VERTEX5:
      result = 5;
      break;
    case VERTEX6:
      result = 6;
      break;
    case VERTEX7:
      result = 7;
      break;
    default:
      result = invalid_pod_index();
      break;
  }    

  // Postconditions:

  ensure(((0 <= result) && (result < kd_zone::VERTEX_CT)) || !is_valid(result));
  
  // Exit:

  // cout << "Leaving kd_bounding_box::local_vertex_id." << endl;
  return result;
}

int
geometry::kd_bounding_box::
local_edge_id(int xin_code_3d)
{
  // cout << endl << "Entering kd_bounding_box::local_edge_id." << endl;

  // Preconditions:


  // Body:

  int result;
  
  switch(xin_code_3d)
  {
    case EDGE0:
      result = 0;
      break;
    case EDGE1:
      result = 1;
      break;
    case EDGE2:
      result = 2;
      break;
    case EDGE3:
      result = 3;
      break;
    case EDGE4:
      result = 4;
      break;
    case EDGE5:
      result = 5;
      break;
    case EDGE6:
      result = 6;
      break;
    case EDGE7:
      result = 7;
      break;
    case EDGE8:
      result = 8;
      break;
    case EDGE9:
      result = 9;
      break;
    case EDGE10:
      result = 10;
      break;
    case EDGE11:
      result = 11;
      break;
    default:
      result = invalid_pod_index();
      break;
  }    

  // Postconditions:

  ensure(((0 <= result) && (result < kd_zone::EDGE_CT)) || !is_valid(result));
  
  // Exit:

  // cout << "Leaving kd_bounding_box::local_edge_id." << endl;
  return result;
}

int
geometry::kd_bounding_box::
local_face_id(int xin_code_3d)
{
  // cout << endl << "Entering kd_bounding_box::local_face_id." << endl;

  // Preconditions:


  // Body:

  int result;
  
  if(xin_code_3d & FACE0)
  {
    result = 0;
  }
  else if(xin_code_3d & FACE1)
  {
    result = 1;
  }
  else if(xin_code_3d & FACE2)
  {
    result = 2;
  }
  else if(xin_code_3d & FACE3)
  {
    result = 3;
  }
  else if(xin_code_3d & FACE4)
  {
    result = 4;
  }
  else if(xin_code_3d & FACE5)
  {
    result = 5;
  }
  else
  {
    result = invalid_pod_index();
  }

  // Postconditions:

  ensure(((0 <= result) && (result < kd_zone::FACE_CT)) || !is_valid(result));
  
  // Exit:

  // cout << "Leaving kd_bounding_box::local_face_id." << endl;
  return result;
}

void
geometry::kd_bounding_box::
local_cell_id(int xin_code_3d, int& xlocal_cell_id, int& xd)
{
  // cout << endl << "Entering kd_bounding_box::local_cell_id." << endl;

  // Preconditions:


  // Body:

  switch(xin_code_3d)
  {
    case VERTEX0:
      xlocal_cell_id = 0;
      xd = 0;
      break;
    case VERTEX1:
      xlocal_cell_id = 1;
      xd = 0;
      break;
    case VERTEX2:
      xlocal_cell_id = 2;
      xd = 0;
      break;
    case VERTEX3:
      xlocal_cell_id = 3;
      xd = 0;
      break;
    case VERTEX4:
      xlocal_cell_id = 4;
      xd = 0;
      break;
    case VERTEX5:
      xlocal_cell_id = 5;
      xd = 0;
      break;
    case VERTEX6:
      xlocal_cell_id = 6;
      xd = 0;
      break;
    case VERTEX7:
      xlocal_cell_id = 7;
      xd = 0;
      break;
    case EDGE0:
      xlocal_cell_id = 0;
      xd = 1;
      break;
    case EDGE1:
      xlocal_cell_id = 1;
      xd = 1;
      break;
    case EDGE2:
      xlocal_cell_id = 2;
      xd = 1;
      break;
    case EDGE3:
      xlocal_cell_id = 3;
      xd = 1;
      break;
    case EDGE4:
      xlocal_cell_id = 4;
      xd = 1;
      break;
    case EDGE5:
      xlocal_cell_id = 5;
      xd = 1;
      break;
    case EDGE6:
      xlocal_cell_id = 6;
      xd = 1;
      break;
    case EDGE7:
      xlocal_cell_id = 7;
      xd = 1;
      break;
    case EDGE8:
      xlocal_cell_id = 8;
      xd = 1;
      break;
    case EDGE9:
      xlocal_cell_id = 9;
      xd = 1;
      break;
    case EDGE10:
      xlocal_cell_id = 10;
      xd = 1;
      break;
    case EDGE11:
      xlocal_cell_id = 11;
      xd = 1;
      break;
    case FACE0:
      xlocal_cell_id = 0;
      xd = 2;
      break;
    case FACE1:
      xlocal_cell_id = 1;
      xd = 2;
      break;
    case FACE2:
      xlocal_cell_id = 2;
      xd = 2;
      break;
    case FACE3:
      xlocal_cell_id = 3;
      xd = 2;
      break;
    case FACE4:
      xlocal_cell_id = 4;
      xd = 2;
      break;
    case FACE5:
      xlocal_cell_id = 5;
      xd = 2;
      break;
    default:
      xlocal_cell_id = invalid_pod_index();
      xd = invalid_pod_index();
      break;
  }    

  // Postconditions:

  ensure(((0 <= xd) && (xd < 3)) || !is_valid(xd));
  ensure(is_valid(xlocal_cell_id) == is_valid(xd));
  ensure((xd == 0) ? (0 <= xlocal_cell_id) && (xlocal_cell_id < kd_zone::VERTEX_CT) : true);
  ensure((xd == 1) ? (0 <= xlocal_cell_id) && (xlocal_cell_id < kd_zone::EDGE_CT) : true);
  ensure((xd == 2) ? (0 <= xlocal_cell_id) && (xlocal_cell_id < kd_zone::FACE_CT) : true);
  
  // Exit:

  // cout << "Leaving kd_bounding_box::local_cell_id." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS


// PRIVATE MEMBER FUNCTIONS




// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
ostream& 
geometry::
operator << (ostream& xos, const kd_bounding_box& xb)
{
  // Preconditions:

  // Body:

  xos << "lb: " << xb.lb() << "  ub: " << xb.ub();

  // Postconditions:

  // Exit:

  return xos;
}

ostream& 
geometry::
operator << (ostream& xos, const kd_bounding_box::out_code_2d_type& xn)
{
  // Preconditions:

  // Body:

  switch(xn)
  {
    case kd_bounding_box::INSIDE:
      xos << "INSIDE";
      break;
    case kd_bounding_box::LEFT:
      xos << "LEFT";
      break;
    case kd_bounding_box::RIGHT:
      xos << "RIGHT";
      break;
    case kd_bounding_box::BOTTOM:
      xos << "BOTTOM";
      break;
    case kd_bounding_box::TOP:
      xos << "TOP";
      break;
    case kd_bounding_box::CLIPPED:
      xos << "CLIPPED";
      break;
    default:
      xos << "NOT_AN_OUT_CODE";
      break;
  }
  
      
  // Postconditions:

  // Exit:

  return xos;
}

list<geometry::kd_bounding_box::out_code_2d_type>
geometry::parse_out_code_2d(int xcode)
{
  list<kd_bounding_box::out_code_2d_type> result;
  
  if(xcode & kd_bounding_box::LEFT)
  {
    result.push_back(kd_bounding_box::LEFT);
  }

  if(xcode & kd_bounding_box::RIGHT)
  {
    result.push_back(kd_bounding_box::RIGHT);
  }

  if(xcode & kd_bounding_box::TOP)
  {
    result.push_back(kd_bounding_box::TOP);
  }

  if(xcode & kd_bounding_box::BOTTOM)
  {
    result.push_back(kd_bounding_box::BOTTOM);
  }

  if(xcode & kd_bounding_box::CLIPPED)
  {
    result.push_back(kd_bounding_box::CLIPPED);
  }

  if(xcode & kd_bounding_box::NOT_AN_OUT_CODE_2D)
  {
    result.push_back(kd_bounding_box::NOT_AN_OUT_CODE_2D);
  }

  if(result.empty())
  {
    result.push_back(kd_bounding_box::INSIDE);
  }

  

  return result;
}

ostream& 
geometry::
operator << (ostream& xos, const list<kd_bounding_box::out_code_2d_type>& xn)
{
  // Preconditions:

  // Body:

  
  for(list<kd_bounding_box::out_code_2d_type>::const_iterator i=xn.begin(); i!=xn.end(); ++i)
  {
    xos << " " << *i;
  }
      
  // Postconditions:

  // Exit:

  return xos;
}


size_t
geometry::
deep_size(const kd_bounding_box& xn, bool xinclude_shallow)
{
  size_t result = 0;

  // Preconditions:

  // Body:

  not_implemented();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

