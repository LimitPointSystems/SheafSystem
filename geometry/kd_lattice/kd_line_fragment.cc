

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_line_fragment

#include "kd_line_fragment.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "e2.h"
#include "e3.h"
#include "error_message.h"
#include "jim_cohort.h"
#include "kd_face.h"
#include "kd_lattice.h"
#include "kd_point.h"
#include "kd_segment.h"
#include "kd_triangle.h"
#include "kd_truncation.h"
#include "kd_truncation_pair.h"
#include "kd_zone_cohort.h"
#include "sec_e3.h"
#include "std_iostream.h"
#include "std_iomanip.h"
#include "std_sstream.h"
#include "subcohort.h"
#include "tolerance_comparison.h"

using namespace geometry; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;
using namespace fiber_bundle::ed_algebra;
using namespace fiber_bundle::e2_algebra;
using namespace fiber_bundle::e3_algebra;

namespace
{

//
// Signed area of triangle abc.
//
double SignedArea2D(const e2_lite& a, const e2_lite& b, const e2_lite& c)
{
  // cout << endl << "Entering kd_line_fragment.cc:SignedArea2D." << endl;
  
  e2_lite le0(b);
  le0 -= a;
    
  e2_lite le1(c);
  le1 -= a;

  double result = perp_dot(le0, le1);

  // cout << scientific << setprecision(18);
  // cout << "result: " << setw(27) << result << endl;
  // cout << fixed << setprecision(6);

  // cout << "Leavinging kd_line_fragment.cc:SignedArea2D." << endl << endl;
  return result;
};
  
//
// True if the triangle abc is counterclockwise.
//
bool TriangleIsCCW(const e2_lite& a, const e2_lite& b, const e2_lite& c)
{
  // cout << endl << "Entering kd_line_fragment.cc:TriangleIsCCW." << endl;

  e2_lite u(b);
  u -= a;
    
  e2_lite v(c);
  v -= a;

  double u0v1 = u[0]*v[1];
  double u1v0 = u[1]*v[0];
    
  // c_gt ensure collinear or close is not CCW.
  // $$SCRIBBLE: we're probably going to need a
  // specific tolerance here.

  bool result = sheaf::c_gt(u0v1, u1v0);
  
  // cout << "u: " << u << endl;
  // cout << "v: " << v << endl;
  
  // cout << scientific << setprecision(18);
  // cout << "  u0v1: " << setw(27) << u0v1;
  // cout << "  u1v0: " << setw(27) << u1v0;
  // cout << "  result: " << boolalpha << result << noboolalpha << endl;
  // cout << fixed << setprecision(6);

  // cout << "Leaving kd_line_fragment.cc:TriangleIsCCW." << endl << endl;
  return result;
};
  
//
// True if the triangle abc is counterclockwise or collinear.
//
bool TriangleIsNotCW(const e2_lite& a, const e2_lite& b, const e2_lite& c)
{
  // cout << endl << "Entering kd_line_fragment.cc:TriangleIsNotCW." << endl;

  e2_lite u(b);
  u -= a;
    
  e2_lite v(c);
  v -= a;

  double u0v1 = u[0]*v[1];
  double u1v0 = u[1]*v[0];
    
  // c_gt ensure collinear or close is not CCW.
  // $$SCRIBBLE: we're probably going to need a
  // specific tolerance here.

  bool result = sheaf::c_gte(u0v1, u1v0);
  
  // cout << "u: " << u << endl;
  // cout << "v: " << v << endl;
  
  // cout << scientific << setprecision(18);
  // cout << "  u0v1: " << setw(27) << u0v1;
  // cout << "  u1v0: " << setw(27) << u1v0;
  // cout << "  result: " << boolalpha << result << noboolalpha << endl;
  // cout << fixed << setprecision(6);

  // cout << "Leaving kd_line_fragment.cc:TriangleIsNotCW." << endl << endl;
  return result;
};
  
//
// True if the triangle abc is counterclockwise or collinear.
//
bool TriangleIsCW(const e2_lite& a, const e2_lite& b, const e2_lite& c)
{
  // cout << endl << "Entering kd_line_fragment.cc:TriangleIsCW." << endl;

  e2_lite u(b);
  u -= a;
    
  e2_lite v(c);
  v -= a;

  double u0v1 = u[0]*v[1];
  double u1v0 = u[1]*v[0];
    
  // c_gt ensure collinear or close is not CW.
  // $$SCRIBBLE: we're probably going to need a
  // specific tolerance here.

  bool result = sheaf::c_lt(u0v1, u1v0);
  
  // cout << "u: " << u << endl;
  // cout << "v: " << v << endl;
  
  // cout << scientific << setprecision(18);
  // cout << "  u0v1: " << setw(27) << u0v1;
  // cout << "  u1v0: " << setw(27) << u1v0;
  // cout << "  result: " << boolalpha << result << noboolalpha << endl;
  // cout << fixed << setprecision(6);

  // cout << "Leaving kd_line_fragment.cc:TriangleIsCW." << endl << endl;
  return result;
};
  
//
// True if the triangle abc is collinear.
//
bool TriangleIsCollinear(const e2_lite& a, const e2_lite& b, const e2_lite& c)
{
  // cout << endl << "Entering kd_line_fragment.cc:TriangleIsCollinear." << endl;

  e2_lite u(b);
  u -= a;
    
  e2_lite v(c);
  v -= a;

  double u0v1 = u[0]*v[1];
  double u1v0 = u[1]*v[0];

  // $$SCRIBBLE: we can modify this do distinguish between
  // truly collinear, a < b < c along the straight line, and
  // contralinear, folded back on itself a,c < b along the lines,
  // by  u = b - a, and v = c - b, then if perp_dot(u,v) == 0
  // and dot(u, v) > 0 implies collinear and < 0 implies contralinear.
    
  // $$SCRIBBLE: we're probably going to need a
  // specific tolerance here.

  bool result = sheaf::c_eql(u0v1, u1v0);

  // cout << "u: " << u << endl;
  // cout << "v: " << v << endl;
  // cout << scientific << setprecision(18);
  // cout << "u0v1: " << setw(27) << u0v1;
  // cout << "  u1v0: " << setw(27) << u1v0;
  // cout << "  result: " << boolalpha << result << noboolalpha << endl;
  // cout << fixed << setprecision(6);

  // cout << "Leaving kd_line_fragment.cc:TriangleIsCollinear." << endl << endl;
  return result;
};
  

// Compute barycentric coordinates (u, v, w) for 
// point p with respect to triangle (a, b, c)
void Barycentric(const e2_lite& p, const e2_lite& a, const e2_lite& b, const e2_lite& c, double& u, double& v, double& w)
{
  // cout << endl << "Entering kd_line_fragment.cc:Barycentric." << endl;
  
  // Preconditions:
  
  require(!TriangleIsCollinear(a, b, c));

  // Body:

  double labc_area = SignedArea2D(a, b, c);
  
  u = SignedArea2D(p, b, c)/labc_area;
  v = SignedArea2D(p, c, a)/labc_area;
  w = SignedArea2D(p, a, b)/labc_area;

  // cout << scientific << setprecision(18);
  // cout << "u: " << setw(27) << u;
  // cout << "  v: " << setw(27) << v;
  // cout << "  w: " << setw(27) << w;
  // cout << endl;
  // cout << fixed << setprecision(6);

  // Postconditions:

  ensure(c_eql(w, 1.0 - u - v));

  // Exit:

  // cout << "Leaving kd_line_fragment.cc:Barycentric." << endl << endl;
  return;
} 

// Test if point p is contained in triangle (a, b, c)
bool TestPointTriangle(const e2_lite& p, const e2_lite& a, const e2_lite& b, const e2_lite& c)
{
  // cout << endl << "Entering kd_line_fragment.cc:TestPointTriangle." << endl;

  double u, v, w;
  Barycentric(p, a, b, c, u, v, w);

  //  bool result = ( (v >= 0.0) && (w >= 0.0) && ((v + w) <= 1.0) );
  bool result = 
    c_gte(v, 0.0, 0.01) && 
    c_gte(w, 0.0, 0.01 ) && 
    c_lte((v + w), 1.0, 0.01);
  
  // cout << "  result: " << boolalpha << result << noboolalpha << endl;

  // cout << "Leaving kd_line_fragment.cc:TestPointTriangle." << endl << endl;
  return result;
}

typedef id_list::iterator seg_itr;
typedef frag_list::iterator frag_itr;
  
//
// Map from tp id to fragment..
//
typedef hash_multimap<pod_index_type, frag_itr> frag_map;
typedef frag_map::iterator frag_map_itr;
typedef pair<frag_map_itr, frag_map_itr> frag_range;

//
// Map from tp id to truncation description.
///
typedef map<scoped_index, kd_truncation> id2t_map;
typedef id2t_map::iterator id2t_map_itr;
typedef id2t_map::value_type id2t_map_val;
typedef pair<id2t_map_itr, bool> id2t_map_result;

//
// Map fromt surface pair to fragment.
//
typedef map<kd_truncation_pair, frag_itr> tr_map;
typedef tr_map::iterator tr_map_itr;
typedef tr_map::value_type tr_map_val;

//
// Stream insertion for frag map value type.
//  
  ostream & operator << (ostream &xos, const frag_map::value_type& xn)
{
  xos << setw(6) << xn.first << "   " << *(xn.second);
    
  return xos;
};

//
// Stream insertion for frag map.
//  
ostream & operator << (ostream &xos, const frag_map& xn)
{
  for(frag_map::const_iterator s=xn.begin(); s!=xn.end(); ++s)
  {
    xos << *s << endl;
  }
    
  return xos;
};

//
// Finds entry (xkey, xf) in xmap.
//
frag_map_itr find_entry(pod_index_type xkey, frag_itr& xf, frag_map& xmap)
{
  // cout << endl << "Entering kd_line_fragment.cc:find_entry." << endl;

  // Preconditions:

  require(!xf->pt_ids.empty());
  
  // Body:

  frag_map_itr result = xmap.end();

  // cout << "xf: " << *xf << endl;
  
  frag_range lrange = xmap.equal_range(xkey);
  for(frag_map_itr s=lrange.first; s!=lrange.second; ++s)
  {
    // cout << "s->second: " << *(s->second) << endl;
    
    if(s->second == xf)
    {
      result = s;
      break;
    }
  }

  //   if(result == xmap.end())
  //   {
  //     cout << "result: end" << endl;
  //   }
  //   else
  //   {
  //     cout << "result: " << *(result->second) << endl;
  //   }
  
  
  // Postconditions:

  ensure((result == xmap.end()) || ((result->first == xkey) && (result->second == xf)));
  
  // Exit:

  // cout << "Leaving kd_line_fragment.cc:find_entry." << endl << endl;
  return result;
  
}  

//
// Removes entry (xold_pod, xf) and inserts entry (xnew_pod, xf) in xmap.
//
void update_entry(pod_index_type xold_pod, pod_index_type xnew_pod, frag_itr& xf, frag_map& xmap)
{
  // cout << endl << "Entering kd_line_fragment.cc:remove_entries." << endl;

  // Preconditions:

  
  // Body:



  // cout << "xf: " << *xf << endl;

  frag_map_itr lfm;

  lfm = find_entry(xold_pod, xf, xmap);
  if(lfm != xmap.end())
  {
    xmap.erase(lfm);
  }

  xmap.insert(frag_map::value_type(xnew_pod, xf));

  // Postconditions:

  ensure(find_entry(xold_pod, xf, xmap) == xmap.end());
  ensure(find_entry(xnew_pod, xf, xmap) != xmap.end());
  
  // Exit:

  // cout << "Leaving kd_line_fragment.cc:remove_entries." << endl << endl;
  return;
  
}  

//
// Remove entry (xf->front_pod(), xf) from xmap.
//
void remove_front_entry(frag_itr& xf, frag_map& xmap)
{
  // cout << endl << "Entering kd_line_fragment.cc:remove_front_entry." << endl;

  // Preconditions:

  
  // Body:

  // cout << "  xf: " << *xf << endl;

  frag_map_itr lfm;

  lfm = find_entry(xf->front_pod(), xf, xmap);
  if(lfm != xmap.end())
  {
    // cout << "erasing entry: " << *lfm << endl;
    
    xmap.erase(lfm);
  }

  // cout << xmap << endl;

  // Postconditions:

  ensure(find_entry(xf->front_pod(), xf, xmap) == xmap.end());
  
  // Exit:

  // cout << "Leaving kd_line_fragment.cc:remove_front_entry." << endl << endl;
  return;
  
}  


//
// Remove entries (xfront_pod, xf) and (xback_pod, xf) from xmap.
//
void remove_entries(pod_index_type xfront_pod, pod_index_type xback_pod, frag_itr& xf, frag_map& xmap)
{
  // cout << endl << "Entering kd_line_fragment.cc:remove_entries." << endl;

  // Preconditions:

  
  // Body:

  // cout << xfront_pod << "  " << xback_pod << "  xf: " << *xf << endl;

  frag_map_itr lfm;

  lfm = find_entry(xfront_pod, xf, xmap);
  if(lfm != xmap.end())
  {
    // cout << "erasing entry: " << *lfm << endl;
    
    xmap.erase(lfm);
  }

  lfm = find_entry(xback_pod, xf, xmap);
  if(lfm != xmap.end())
  {
    // cout << "erasing entry: " << *lfm << endl;

    xmap.erase(lfm);
  }  

  // Postconditions:

  ensure(find_entry(xfront_pod, xf, xmap) == xmap.end());
  ensure(find_entry(xback_pod, xf, xmap) == xmap.end());
  
  // Exit:

  // cout << "Leaving kd_line_fragment.cc:remove_entries." << endl << endl;
  return;
  
}  


//
// Remove entries (xf.front_pod(), xf) and (xf.back_pod(), xf) from xmap.
//
void remove_entries(frag_itr& xf, frag_map& xmap)
{
  // cout << endl << "Entering kd_line_fragment.cc:remove_entries." << endl;
  // cout << "frag: " << *xf << endl;
  // cout << "frag map: " << endl << xmap << endl;
  
  // Preconditions:

  require(!xf->pt_ids.empty());

  // The following isn't strictly necessary,
  // but we're supposed to be removing entries
  // before we close them and this is a
  // convenient trap.

  assertion(!xf->is_closed());
  
  // Body:

  remove_entries(xf->front_pod(), xf->back_pod(), xf, xmap);
  
  // Postconditions:

  ensure(find_entry(xf->front_pod(),xf, xmap) == xmap.end());
  ensure(find_entry(xf->back_pod(), xf, xmap) == xmap.end());
  
  // Exit:

  // cout << "Leaving kd_line_fragment.cc:remove_entries." << endl << endl;
  return;
  
}  

//
// Updates map xmap after xif is front extended.
//
void update_map_front(pod_index_type xold_front_pod, frag_itr& xfrag, frag_map& xmap)
{
  if(xfrag->is_closed())
  {
    // Remove xif from the map.

    remove_entries(xold_front_pod, xfrag->back_pod(), xfrag, xmap);
  }
  else
  {
    // Update the entry for xif front.

    update_entry(xold_front_pod, xfrag->front_pod(), xfrag, xmap);
  }

  return;
}

//
// Updates map xmap after xif is back extended.
//
void update_map_back(pod_index_type xold_back_pod, frag_itr& xfrag, frag_map& xmap)
{
  if(xfrag->is_closed())
  {
    // Remove xif from the map.

    remove_entries(xfrag->front_pod(), xold_back_pod, xfrag, xmap);
  }
  else
  {
    // Update the entry for xif front.

    update_entry(xold_back_pod, xfrag->back_pod(), xfrag, xmap);
  }

  return;
}


//
// Extends a fragment from the truncation fragment list...
//
frag_itr extend_truncation_fragment(kd_lattice& xhost, 
                                    frag_list& xifrags, 
                                    frag_itr& xtf, 
                                    frag_map& xifrag_map)
{
  // cout << endl << "Entering kd_line_fragment.cc:extend_trunction_fragemnt." << endl;
  
  // Preconditions:


  // Body.

  frag_itr result;

  // Xtf is a fragment from the truncation frag list;
  // try to find a input frag that extends it.

  // Try to find a match in the input fragments.

  frag_map_itr lfm = xifrag_map.find(xtf->back_pod());
  if(lfm != xifrag_map.end())
  {
    // Found a match between the back of the truncation fragment
    // and an input fragment, extend the input fragment with the
    // truncation fragment.

    frag_itr lf = lfm->second;

    if(xtf->back_pod() == lf->front_pod())
    {
      // Attach the fwd dir of xtf to the front of lf

      pod_index_type lold_front_pod = lf->front_pod();

      lf->insert_front(*xtf, true);

      // Update the map to reflect change in lf.

      update_map_front(lold_front_pod, lf, xifrag_map);
    }
    else
    {
      // Attach the rev direction of xtf to the back of lf.

      pod_index_type lold_back_pod = lf->back_pod();

      lf->insert_back(*xtf, false);

      // Update the map to reflect change in lf.

      update_map_back(lold_back_pod, lf, xifrag_map);
    }

    result = lf;
  }
  else
  {
    result = xifrags.end();
  }
  
  // Postconditions:
  
  // Exit:
    
  // cout << "Leaving kd_line_fragment.cc:extend_truncation_fragemnt." << endl << endl;
  return result;
}


//
// Searches xmap for a frag that matches xkey and is in the same surface.
//
frag_map_itr find_frag_same_surface(kd_lattice& xhost, pod_index_type xkey, frag_itr& xfrag, frag_map& xmap)
{
  // cout << endl << "Entering kd_line_fragment.cc:find_frag_same_surface." << endl;

  frag_map_itr result = xmap.end();

  frag_range lrange = xmap.equal_range(xkey);
  for(frag_map_itr s=lrange.first; s!=lrange.second; ++s)
  {
    if(s->second != xfrag)
    {  
      if(s->second->surface_id == xfrag->surface_id)
      {
        result = s;
        break;
      }
    }    
  }
    
  // cout << "Leaving kd_line_fragment.cc:find_frag_same_surface." << endl << endl;
  return result;
};

//
// Searches xmap for a frag that matches xfrag.back() and is in 
// the same truncating surface on the same side of a truncated surface.
//
frag_map_itr find_frag_back_same_side(kd_lattice& xhost, frag_itr& xfrag, frag_map& xmap)
{
  // cout << endl << "Entering kd_line_fragment.cc:find_frag_back_same_side." << endl;

  frag_map_itr result = xmap.end();

  frag_range lrange = xmap.equal_range(xfrag->back().pod());
  for(frag_map_itr s=lrange.first; s!=lrange.second; ++s)
  {
    if(s->second != xfrag)
    {  
      if(s->second->surface_id == xfrag->surface_id)
      {
        if(xhost.truncation_mid_points().contains(xfrag->back().pod()))
        {
          // cout << "frag back is truncation mid point" << endl;
          
          // Back of xfrag and front of other form a truncation line.
          // Make sure we stay on the same side of the truncated surface.
          // We stay on the same side if we keep turning the same direction;
          // which means the normals are in the same direction.
          
          e3_lite lfrag_normal;
          xfrag->normal(xhost, --(--(--(xfrag->pt_ids.end()))), lfrag_normal);

          e3_lite lother_normal;
          if(xfrag->back().pod() == s->second->front().pod())
          {
            // Forward direction of candidate matches xfrag.

            // Don't want to match same truncation segment.
            
            if(xfrag->before_back().pod() == s->second->after_front().pod())
            {
              continue;
            }

            // cout << "Forward direction of candidate matches xfrag" << endl;            
            
            s->second->normal(xhost, s->second->pt_ids.begin(), lother_normal);
          }
          else
          {
            assertion(xfrag->back().pod() == s->second->back().pod());

            // Reverse direction of candidate matches xfrag.

            // cout << "Reverse direction of candidate matches xfrag" << endl;

            // Don't want to match same truncation segment.
            
            if(xfrag->before_back().pod() == s->second->before_back().pod())
            {
              continue;
            }

            s->second->normal(xhost,  --(--(--(s->second->pt_ids.end()))), lother_normal);

            // Let a be the next o last segment in !forward! order
            // and b be the last segment, We've just computed a x b,
            // but we want -b x -a == - a x b, so reverse the normal.

            lother_normal *= -1.0;
          }

          if(dot(lfrag_normal, lother_normal) > 0.0)
          {
            // cout << "found match" << endl;
            
            result = s;
            break;
          }
        }
        else
        { 
          // Not a truncation line,
          // just accept same surface.

          // cout << "Not a truncation line," << endl;          
          // cout << "found match" << endl;
         
          result = s;
          break;
        }
      }
    }
  }
    
  // cout << "Leaving kd_line_fragment.cc:find_frag_back_same_side." << endl << endl;
  return result;
};

//
// Searches xmap for a frag that matches xfrag.back() and is in 
// the same truncating surface on the same side of a truncated surface.
//
frag_map_itr find_frag_front_same_side(kd_lattice& xhost, frag_itr& xfrag, frag_map& xmap)
{
  // cout << endl << "Entering kd_line_fragment.cc:find_frag_front_same_side." << endl;

  frag_map_itr result = xmap.end();

  frag_range lrange = xmap.equal_range(xfrag->front().pod());
  for(frag_map_itr s=lrange.first; s!=lrange.second; ++s)
  {
    if(s->second != xfrag)
    {  
      if(s->second->surface_id == xfrag->surface_id)
      {
        if(xhost.truncation_mid_points().contains(xfrag->front().pod()))
        {
          // cout << "frag back is truncation mid point" << endl;

          // Back of xfrag and front of other form a truncation line.
          // Make sure we stay on the same side of the truncated surface.
          // We stay on the same side if we keep turning the same direction;
          // which means the normals are in the same direction.
          
          e3_lite lfrag_normal;
          xfrag->normal(xhost, xfrag->pt_ids.begin(), lfrag_normal);

          e3_lite lother_normal;
          if(xfrag->front().pod() == s->second->back().pod())
          {
            // Forward direction of candidate matches xfrag.
            
            // cout << "Forward direction of candidate matches xfrag" << endl;            

            // Don't want to match same truncation segment.
            
            if(xfrag->after_front().pod() == s->second->before_back().pod())
            {
              continue;
            }

            s->second->normal(xhost,  --(--(--(s->second->pt_ids.end()))), lother_normal);
          }
          else
          {
            assertion(xfrag->front().pod() == s->second->front().pod());

            // Reverse direction of candidate matches xfrag.

            // cout << "Reverse direction of candidate matches xfrag" << endl;            

            // Don't want to match same truncation segment.
            
            if(xfrag->after_front().pod() == s->second->after_front().pod())
            {
              continue;
            }

            s->second->normal(xhost, s->second->pt_ids.begin(), lother_normal);

            // Let a be the first segment in !forward! order
            // and b be the second segment, We've just computed a x b,
            // but we want -b x -a == - a x b, so reverse the normal.

            lother_normal *= -1.0;
          }

          if(dot(lfrag_normal, lother_normal) > 0.0)
          {
            // cout << "found match" << endl;

            result = s;
            break;
          }
        }
        else
        { 
          // Not a truncation line,
          // just accept same surface.
         
          // cout << "Not a truncation line," << endl;          
          // cout << "found match" << endl;

          result = s;
          break;
        }
      }
    }
  }
    
  // cout << "Leaving kd_line_fragment.cc:find_frag_front_same_side." << endl << endl;
  return result;
};


//
// Extends an input fragment at the back, if possible, with fragments from
// the same surface. Does not extend past a truncation point. 
//
bool extend_input_fragment_back_same_surface_truncate(kd_lattice& xhost, frag_list& xifrags, frag_itr& xif, frag_map& xifrag_map)
{
  // cout << endl << "Entering kd_line_fragment.cc:extend_input_fragemnt_back." << endl;
  
  // Preconditions:

  // Body.

  bool result;

  if(xif->is_closed())
  {
    // Can't follow this fragment any further;
    // try to find another one.

    // cout << "closed, can't extend" << endl;
    result = false;
  }
  else if(xhost.truncation_points().contains(xif->pt_ids.back()))
  {
    // Can't follow this fragment any further;
    // try to find another one.

    // cout << "truncation point, can't extend" << endl;
    result = false;
  }
  else if(xhost.truncation_mid_points().contains(xif->pt_ids.back()))
  {
    // Can't follow this fragment any further;
    // try to find another one.

    // cout << "truncation mid point, can't extend." << endl;
    result = false;
  }
  else
  {
    // Try to match the back of the input fragment with another input fragment..

    frag_map_itr lfm = find_frag_same_surface(xhost, xif->back_pod(), xif, xifrag_map);
    if(lfm != xifrag_map.end())
    {
      // Found a match between the back of the input fragment
      // and another input fragment in the same surface; append the match.

      frag_itr lf = lfm->second;

      // Once we're finished with lf we want
      // to remove it from both the map and the list.
      // But splice will empty lf.pt_ids,
      // so we have to remove lf from the map first,
      // then splice, then remove from list.

      remove_entries(lf, xifrag_map);

      if(lf->back_pod() == xif->back_pod())
      {
        // Attach the fragment in the reverse direction.

        lf->pt_ids.reverse();
      }
    
      pod_index_type lold_back_pod = xif->back_pod();

      xif->splice_back(*lf);
    
      xifrags.erase(lf);

      // Update the map to reflect change in xif.

      update_map_back(lold_back_pod, xif, xifrag_map);      

      result = true;
    }  
    else
    {
      result = false;
    }
  }
  
  
  // Postconditions:
  
  // Exit:
    
  // cout << "Leaving kd_line_fragment.cc:extend_input_fragemnt_back." << endl << endl;
  return result;
}

//
// Extends an input fragment at the back, if possible, with fragments from
// the same truncating surface on the same side of a truncated surface. 
// Extends past a truncation point. 
//
bool extend_input_fragment_back_same_side(kd_lattice& xhost, frag_list& xifrags, frag_itr& xif, frag_map& xifrag_map)
{
  // cout << endl << "Entering kd_line_fragment.cc:extend_input_fragemnt_back." << endl;
  
  // Preconditions:

  // Body.

  bool result;

  if(xif->is_closed())
  {
    // Can't follow this fragment any further;
    // try to find another one.

    // cout << "closed, can't extend" << endl;
    result = false;
  }
  else
  {
    // Try to match the back of the input fragment with another input fragment..

    frag_map_itr lfm = find_frag_back_same_side(xhost, xif, xifrag_map);
    if(lfm != xifrag_map.end())
    {
      // Found a match between the back of the input fragment
      // and another input fragment in the same surface; append the match.

      frag_itr lf = lfm->second;

      // Once we're finished with lf we want
      // to remove it from both the map and the list.
      // But splice will empty lf.pt_ids,
      // so we have to remove lf from the map first,
      // then splice, then remove from list.

      remove_entries(lf, xifrag_map);

      if(lf->back_pod() == xif->back_pod())
      {
        // Attach the fragment in the reverse direction.

        lf->pt_ids.reverse();
      }
    
      pod_index_type lold_back_pod = xif->back_pod();

      xif->splice_back(*lf);
    
      xifrags.erase(lf);

      // Update the map to reflect change in xif.

      update_map_back(lold_back_pod, xif, xifrag_map);      

      result = true;
    }  
    else
    {
      result = false;
    }
  }
  
  
  // Postconditions:
  
  // Exit:
    
  // cout << "Leaving kd_line_fragment.cc:extend_input_fragemnt_back." << endl << endl;
  return result;
}


//
// Searches xmap for a frag that matches xfrag.back() and is in any surface;
// if xmatch_rev, allow match with reverse fragment, otherwise do not.
//
frag_map_itr find_frag_any_surface(kd_lattice& xhost, frag_itr& xfrag, frag_map& xmap, bool xmatch_rev)
{
  // cout << endl << "Entering kd_line_fragment.cc:find_frag_any_surface." << endl;

  // Preconditions:

  require(xhost.faces().contains(xfrag->container_id));
  
  // Body:

  frag_range lrange = xmap.equal_range(xfrag->back().pod());

  int lct = 0;
  list<frag_map_itr> litr_list;
  for(frag_map_itr s=lrange.first; s!=lrange.second; ++s)
  {
    if(xmatch_rev || !s->second->is_reverse_of(*xfrag))
    {
      litr_list.push_back(s);
      lct++;
    }
  }

  frag_map_itr result;

  if(lct == 0)
  {
    // cout << "failed to find a frag." << endl;
    
    result = xmap.end();
  }
  else if(lct == 1)
  {
    // cout << "found only one frag" << endl;
    
    result = litr_list.front();

    // cout << "result: " << *result->second << endl;
  }
  else
  {
    // More than one candidate.
    // We're trying to construct counterclockwise
    // oriented polygons, so we want to follow the candidate
    // that is most counterclockwise. We do this 
    // by setting up a right handed local coordinate frame (u,v,w)
    // with the u-axis pointing opposite the last segment of xfrag,
    // then computing the standard polar angle in the uv plane for each
    // candidate and taking the one with the greatest angle.

    // $$SCRIBBLE. this algorithm is neither efficient
    // nor robust. It will fail when two candidate
    // segments are nearly parallel. We need to replace
    // it with a robust implementation of orient2D.

    // cout << "found multiple candidates" << endl;

    int lu, lv, lw;
    kd_face::local_axes(xhost, xfrag->container_id, lu, lv);
    lw = kd_face::int_alignment(xhost, xfrag->container_id);
    
    // cout << "local axes: " << setw(3) << lu << setw(3) << lv << setw(3) << lw << endl;
    
    // u-hat opposite the last segment of xfrag.

    id_list::const_iterator lbefore_back_itr = --(--xfrag->pt_ids.end());
    e3_lite lu_hat;
    xfrag->segment(xhost, lbefore_back_itr, lu_hat);
    lu_hat *= -1.0;
    normalize(lu_hat);

    // v-hat is "u-perp": counter-clockwise perpendicular to u-hat.

    e3_lite lv_hat;
    lv_hat[lu] = -lu_hat[lv];
    lv_hat[lv] =  lu_hat[lu];
    lv_hat[lw] =  lu_hat[lw];

    vd_value_type ltheta, ltheta_max = -numeric_limits<vd_value_type>::max();
    const vd_value_type TWO_PI = 8.0*atan(1.0);
    
    e3_lite lother_front_seg;
    for(list<frag_map_itr>::iterator lfml = litr_list.begin(); lfml != litr_list.end(); ++lfml)
    {
      frag_map_itr lfm = *lfml;

      // Get first segment as a vector.

      lfm->second->segment(xhost, lfm->second->pt_ids.begin(), lother_front_seg);

      // Compute its polar angle.
      // Note that atan2 returns -pi < result <= pi, 
      // while we want 0 < ltheta <= 2*pi so max
      // correctly identifies most counter-clockwise
      // candidate. So if theta < 0, add 2*PI.

      vd_value_type lu_comp = dot(lother_front_seg, lu_hat);
      vd_value_type lv_comp = dot(lother_front_seg, lv_hat);

      ltheta = atan2(lv_comp, lu_comp);

      if(ltheta < 0.0)
      {
        ltheta += TWO_PI;
      }

      // cout << "theta: " << ltheta << " theta max: " << ltheta_max << endl;
      if(ltheta > ltheta_max)
      {
        ltheta_max = ltheta;
        result = *lfml;
      }
      // cout << "theta: " << ltheta << " theta max: " << ltheta_max << endl;
    }
    // cout << "result: " << *result->second << endl;
  }
  
  // cout << "Leaving kd_line_fragment.cc:find_frag_any_surface." << endl << endl;
  return result;
};

//
// Extends an input fragment at the back, if possible, with fragment from any surface.
// Does not extend past a truncation point.
//
bool extend_input_fragment_back_any_surface(kd_lattice& xhost, frag_list& xifrags, frag_itr& xif, frag_map& xifrag_map, bool xmatch_rev)
{
  // cout << endl << "Entering kd_line_fragment.cc:extend_input_fragment_back_any_surface." << endl;
  
  // Preconditions:

  // Body.

  bool result;

  if(xif->is_closed())
  {
    // Can't follow this fragment any further;
    // try to find another one.

    // cout << "closed, can't extend" << endl;
    result = false;
  }
  else
  {
    // Try to match the back of the input fragment with another input fragment..

    frag_map_itr lfm = find_frag_any_surface(xhost, xif, xifrag_map, xmatch_rev);
    if(lfm != xifrag_map.end())
    {
      // Found a match between the back of the input fragment
      // and another input fragment; append the match.

      frag_itr lf = lfm->second;

      // Once we're finished with lf we want
      // to remove it from both the map and the list.
      // But splice will empty lf.pt_ids,
      // so we have to remove lf from the map first,
      // then splice, then remove from list.

      remove_front_entry(lf, xifrag_map);
      xif->splice_back(*lf);
      xifrags.erase(lf);

      // If the frag is now closed, it can no longer
      // extend anything, so remove it from the map.
      // In addition, a closed fragment will be spliced
      // from the cfrags list to the ofrags list,
      // which will leave the entry in the map empty.

      if(xif->is_closed())
      {
        remove_front_entry(xif, xifrag_map);
      }

      result = true;
    }  
    else
    {
      result = false;
    }
  }
  
  
  // Postconditions:
  
  // Exit:
    
  // cout << "Leaving kd_line_fragment.cc:extend_input_fragment_back_any_surface." << endl << endl;
  return result;
}

//
// Extends an input fragment at the back, if possible, with fragment from any surface.
// Does not extend past a truncation point.
//
bool extend_output_fragment(kd_lattice& xhost, frag_list& xifrags, frag_itr& xif, frag_map& xifrag_map, frag_list& xofrags)
{
  // cout << endl << "Entering kd_line_fragment.cc:extend_output_fragment." << endl;
  // cout << "frag: " << *xif << endl;
  
  // Preconditions:

  // Body.

  bool result = false;

  // Search output list for frag with front matches back of xif.

  for(frag_itr lof = xofrags.begin(); lof != xofrags.end(); ++lof)
  {
    if(xif->back().pod() == lof->front().pod())
    {
      // Found a matching ofrag.

      // cout << "Found ofrag matching back: " << *lof << endl;

      // Copy the ifrag to the front of the ofrag.

      lof->pt_ids.insert(lof->pt_ids.begin(), xif->pt_ids.begin(), --xif->pt_ids.end());

      // Copy the rev ifrag to the back of the ofrag.

      lof->pt_ids.insert(lof->pt_ids.end(), ++xif->pt_ids.rbegin(), xif->pt_ids.rend());

      // cout << "Extended front and back of ofrag. result: " << *lof << endl;

      // Xif is the first of a fwd rev pair.
      // the rev has to be ahead in the list.
      // Find it and remove it.

      frag_itr lrev = xif;
      ++lrev;
      while(lrev != xifrags.end())
      {
        if(lrev->is_reverse_of(*xif))
        {      
          // Remove the rev from the map.

          remove_entries(lrev, xifrag_map);
      
          // Remove the rev from the ifrag list.
          // Don't care about invalidating itr.

          xifrags.erase(lrev);

          // cout << "removed reverse" << endl;
          
          break;
        }
        ++lrev;
      }
      
      // Remove the ifrag from the map.

      remove_entries(xif, xifrag_map);
      
      // Remove the ifrag from the ifrag list.

      xifrags.erase(xif++);

      // cout << "removed forward" << endl;

      result = true;
      
      break;
    }
  }
  
  if(!result)
  {
    // Search output list for frag with back matches front.

    for(frag_itr lof = xofrags.begin(); lof != xofrags.end(); ++lof)
    {
      if(xif->front().pod() == lof->back().pod())
      {
        // Found a matching ofrag.

        // cout << "Found ofrag matching front: " << *lof << endl;

        // Copy the ifrag to the back of the ofrag.

        lof->pt_ids.insert(lof->pt_ids.end(), ++xif->pt_ids.begin(), xif->pt_ids.end());

        // Copy the rev ifrag to the front of the ofrag.

        lof->pt_ids.insert(lof->pt_ids.begin(), xif->pt_ids.rbegin(), --xif->pt_ids.rend());
      
        // cout << "Extended back and front of ofrag. result: " << *lof << endl;

        // Xif is the first of a fwd rev pair.
        // the rev has to be ahead in the list.
        // Find it and remove it.

        frag_itr lrev = xif;
        ++lrev;
        while(lrev != xifrags.end())
        {
          if(lrev->is_reverse_of(*xif))
          {      
            // Remove the rev from the map.

            remove_entries(lrev, xifrag_map);
      
            // Remove the rev from the ifrag list.
            // Don't care about invalidating itr.

            xifrags.erase(lrev);
            
            // cout << "removed reverse" << endl;

            break;
          }
          ++lrev;
        }

        // Remove the ifrag from the map.

        remove_entries(xif, xifrag_map);
      
        // Remove the ifrag from the ifrag list.

        xifrags.erase(xif++);

        // cout << "removed forward" << endl;

        result = true;
      
        break;
      }
    }
  }
  
  // Postconditions:
  
  // Exit:
    
  // cout << "Leaving kd_line_fragment.cc:extend_output_fragment." << endl << endl;
  return result;
}

//
// Moves fragment xif from the input list to the output list.
//
bool output_fragment(frag_itr& xif, frag_list& xifrags, frag_list& xofrags)
{

  bool result;
  
  if(xif->is_closed())
  {  
    kd_line_fragment lfrag;
    xofrags.push_back(lfrag);
    kd_line_fragment& lof = xofrags.back();
    lof.surface_id = xif->surface_id;
    lof.container_id = xif->container_id;
    lof.pt_ids.splice(lof.pt_ids.end(), xif->pt_ids, xif->pt_ids.begin(), xif->pt_ids.end());

    assertion(xif->pt_ids.empty());
  
    xifrags.erase(xif++);

    result = true;
  }
  else
  {
    result = false;
  }
  
  return result;
}



//
// Extends an input fragment at the front, if possible..
//
bool extend_input_fragment_front_same_surface_truncate(kd_lattice& xhost, frag_list& xifrags, frag_itr& xif, frag_map& xifrag_map)
{
  // cout << endl << "Entering kd_line_fragment.cc:extend_input_fragment_front_same_surface_truncate." << endl;
  
  // Preconditions:

  // Body.

  bool result;

  if(xif->is_closed())
  {
    // Can't follow this fragment any further;
    // try to find another one.

    // cout << "closed, can't extend" << endl;
    result = false;
  }
  else if(xhost.truncation_points().contains(xif->pt_ids.front()))
  {
    // Can't follow this fragment any further;
    // try to find another one.

    // cout << "truncation point, can't extend" << endl;
    result = false;
  }
  else if(xhost.truncation_mid_points().contains(xif->pt_ids.front()))
  {
    // Can't follow this fragment any further;
    // try to find another one.

    // cout << "truncation mid point, can't extend." << endl;
    result = false;
  }
  else
  {
    // Try to match the front of the input fragment with another input fragment..

    frag_map_itr lfm = find_frag_same_surface(xhost, xif->front_pod(), xif, xifrag_map);
    if(lfm != xifrag_map.end())
    {
      // Found a match between the front of the input fragment
      // and another input fragment in the same surface; append the match.

      frag_itr lf = lfm->second;

      // Once we're finished with lf we want
      // to remove it from both the map and the list.
      // But splice will empty lf.pt_ids,
      // so we have to remove lf from the map first,
      // then splice, then remove from list.

      remove_entries(lf, xifrag_map);

      if(lf->front_pod() == xif->front_pod())
      {
        // Attach the fragment in the reverse direction.

        lf->pt_ids.reverse();
      }
    
      pod_index_type lold_front_pod = xif->front_pod();

      xif->splice_front(*lf);
    
      xifrags.erase(lf);

      // Update the map to reflect change in xif.

      update_map_front(lold_front_pod, xif, xifrag_map);

      result = true;
    }
    else
    {
      result = false;
    }
  }
  
  
  // Postconditions:
  
  // Exit:
    
  // cout << "Leaving kd_line_fragment.cc:extend_input_fragment_front_same_surface_truncate." << endl << endl;
  return result;
}

//
// Extends an input fragment at the front, if possible..
//
bool extend_input_fragment_front_same_side(kd_lattice& xhost, frag_list& xifrags, frag_itr& xif, frag_map& xifrag_map)
{
  // cout << endl << "Entering kd_line_fragment.cc:extend_input_fragment_front_same_side." << endl;
  
  // Preconditions:

  // Body.

  bool result;

  if(xif->is_closed())
  {
    // Can't follow this fragment any further;
    // try to find another one.

    // cout << "closed, can't extend" << endl;
    result = false;
  }
  else
  {
    // Try to match the front of the input fragment with another input fragment..

    frag_map_itr lfm = find_frag_front_same_side(xhost, xif, xifrag_map);
    if(lfm != xifrag_map.end())
    {
      // Found a match between the front of the input fragment
      // and another input fragment in the same surface; append the match.

      frag_itr lf = lfm->second;

      // Once we're finished with lf we want
      // to remove it from both the map and the list.
      // But splice will empty lf.pt_ids,
      // so we have to remove lf from the map first,
      // then splice, then remove from list.

      remove_entries(lf, xifrag_map);

      if(lf->front_pod() == xif->front_pod())
      {
        // Attach the fragment in the reverse direction.

        lf->pt_ids.reverse();
      }
    
      pod_index_type lold_front_pod = xif->front_pod();

      xif->splice_front(*lf);
    
      xifrags.erase(lf);

      // Update the map to reflect change in xif.

      update_map_front(lold_front_pod, xif, xifrag_map);

      result = true;
    }
    else
    {
      result = false;
    }
  }
  
  
  // Postconditions:
  
  // Exit:
    
  // cout << "Leaving kd_line_fragment.cc:extend_input_fragment_front_same_side." << endl << endl;
  return result;
}

//
// Make the truncation fragments associated with
// the truncation points for fragment xif.
//
void make_tfrags(kd_lattice& xhost, 
                 frag_itr& xif,
                 const kd_line_fragment& xfrag_prototype,
                 frag_list& xtfrags,
                 scoped_index& xmid_pt_id,
                 frag_itr& xtff,
                 frag_itr& xtfb)
{
  // cout << endl << "Entering kd_line_fragment.cc:make_tfrags." << endl;

  scoped_index lf_pt_id(xif->pt_ids.front());
  scoped_index lb_pt_id(xif->pt_ids.back());
  

  xhost.coords().get_read_write_access();

  // Get the tp coordinates.

  e3_lite lf_pt;
  xhost.coords().get_fiber(lf_pt_id, lf_pt, false);

  e3_lite lb_pt;
  xhost.coords().get_fiber(lb_pt_id, lb_pt, false);
  
  // Get the midpoint.

  e3_lite lmid_pt;
  if(!xmid_pt_id.is_valid())
  {
    // Create the midpoint.

    xmid_pt_id = xhost.truncation_mid_points().new_member();
    
    lmid_pt = lf_pt;
    lmid_pt += lb_pt;
    lmid_pt *= 0.5;  

    // cout << "created midpoint: " << xmid_pt_id.pod() << endl;
  }
  else
  {
    // Get its coordinates

    xhost.coords().get_fiber(xmid_pt_id, lmid_pt, false);

    // Existing midpoint has weight 2 in average.

    lmid_pt *= 2.0;
    lmid_pt += lf_pt;
    lmid_pt += lb_pt;
    lmid_pt *= 0.25;  

    // Now the mid point is also a reversal point.

    xhost.truncation_reversal_points().insert_member(xmid_pt_id);

    // cout << "updated midpoint: " << xmid_pt_id.pod() << endl;
  }

  xhost.coords().force_fiber(xmid_pt_id, lmid_pt, false);
  
  xhost.coords().release_access();  

  // Create the front truncation fragment.

  xtfrags.push_back(xfrag_prototype);
  xtff = --xtfrags.end();

  xtff->pt_ids.push_back(xmid_pt_id);
  xtff->pt_ids.push_back(lf_pt_id);

  // cout << "inserted front tfrag " << *xtff << endl;  

  // Create the back truncation fragment.

  xtfrags.push_back(xfrag_prototype);
  xtfb = --xtfrags.end();

  xtfb->pt_ids.push_back(xmid_pt_id);
  xtfb->pt_ids.push_back(lb_pt_id);

  // cout << "inserted back tfrag " << *xtfb << endl;

  // cout << "Leaving kd_line_fragment.cc:make_tfrags." << endl << endl;
  return;
}

//
// Closes input fragment xif using truncation fragments xtff, xtfb.
//
void close_input_fragment(frag_itr& xif, frag_map& xifrag_map, frag_itr& xtff, frag_itr& xtfb)
{
  // Close the fragment with the tfrags;
  // first extend front and upate map,
  // then extend back and update map.
  // Back update erases map entry
  // because frag is closed.

  pod_index_type lold_front_pod = xif->front_pod();
  pod_index_type lold_back_pod  = xif->back_pod();

  xif->pt_ids.push_front(xtff->pt_ids.front());
  update_map_front(lold_front_pod, xif, xifrag_map);
  
  xif->pt_ids.push_back(xtfb->pt_ids.front());
  update_map_back(lold_back_pod, xif, xifrag_map);

  // cout << "closed fragment: " << *xif << endl;
}                                 

//
// Finds truncation fragments xtff and xtfb that connect the front and back of xif.
//
bool find_truncation_frags(frag_itr& xif, frag_list& xfrags, frag_itr& xtff, frag_itr& xtfb)
{
  // cout << endl << "Entering kd_line_fragment.cc:find_truncation_frags." << endl;
  
  bool result = false;
  xtff = xfrags.end();
  xtfb = xfrags.end();
  for(frag_itr ff = xfrags.begin(); ff != xfrags.end(); ++ff)
  {
    if(ff->back_pod() == xif->front_pod())
    {
      for(frag_itr fb = xfrags.begin(); fb != xfrags.end(); ++fb)
      {
        if((fb->back_pod() == xif->back_pod()) && (fb->front_pod() == ff->front_pod()))
        {
          xtff = ff;
          xtfb = fb;
          result = true;
          break;
        }
      }
    }
    if(result)
    {
      break;
    }      
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "truncation frag for tps: " << xif->front_pod() << " " << xif->back_pod() << " = " << endl;

  if(xtff != xfrags.end())
  {
    cout << "xtff: " << *xtff << endl;
  }
  else
  {
    cout << "xtff failed" << endl;
  }

  if(xtfb != xfrags.end())
  {
    cout << "xtfb: " << *xtfb << endl;
  }
  else
  {
    cout << "xtfb failed" << endl;
  }
#endif

  // cout << "Leaving kd_line_fragment.cc:find_truncation_frags." << endl << endl;
  return result;
}

//
// Finds truncation fragments xtff and xtfb connected to a mutually truncating reversal point(mtrp).
//
bool find_mtrp_truncation_frags(const kd_lattice& xhost, 
                                id2t_map xid2t_map, 
                                frag_list& xtfrags, 
                                list<frag_itr>& xtf0_list, 
                                list<frag_itr>& xtf1_list, 
                                id_list& xsurface_id_list)
{
  // cout << endl << "Entering kd_line_fragment.cc:find_mtrp_truncation_frags." << endl;  

  bool result = false;
  xtf0_list.clear();
  xtf1_list.clear();
  xsurface_id_list.clear();
  bool lfirst = true;

  

  // Search the id to truncation map for type MUTUALLY_TRUNCATING.
  // There may be multiple instances, we're only interested in
  // instances that connect to normal truncation points, but there
  // may be more than one of those too.

  for(id2t_map_itr m = xid2t_map.begin(); m != xid2t_map.end(); ++m)
  {
    if(m->second.type() == kd_truncation::MUTUALLY_TRUNCATING)
    {
      // Found a mutually truncating reversal point.

      // cout << "Found a mutually truncating reversal point." << endl;
      // cout << "Point: " << m->first.pod() << endl;
      // cout << "Coords: " << kd_point::coords(xhost, m->first) << endl;
      // cout << "Truncation: " << m->second << endl;

      frag_itr lfrags[2];
      scoped_index lsurface_ids[2];
      int lfrags_ct = 0;

      for(frag_itr f0 = xtfrags.begin(); f0 != xtfrags.end(); ++f0)
      {
        if(f0->pt_ids.back() == m->first)
        {
          // Found a tfrag that ends at the mtrp;
          // find the other end of it.
  
          // cout << "Found a tfrag that ends at the mtrp;" << endl;
          
          for(frag_itr f1 = xtfrags.begin(); f1 != xtfrags.end(); ++f1)
          {
            if((f1 != f0) && (f1->pt_ids.front() == f0->pt_ids.front()))
            {
              // Found the other end; check its truncation type.

              // cout << "Found the other end; check its truncation type." << endl;              

              id2t_map_itr f1m = xid2t_map.find(f1->pt_ids.back());
              
              assertion(f1m != xid2t_map.end());

              kd_truncation& lf1_trunc = f1m->second;

              // cout << "other end: " << f1->pt_ids.back().pod() << "  " << kd_point::coords(xhost, f1->pt_ids.back()) << endl;
              // cout << "other end trunc type: " << lf1_trunc << endl;
              
              if(lf1_trunc.type() == kd_truncation::NORMAL_TRUNCATION)
              {
                // The other end is a normal truncation;
                // not another mtrp or mutually truncated, etc.
                // This is the case we're looking for.                
                
                lfrags[lfrags_ct] = f0;
                lsurface_ids[lfrags_ct] = lf1_trunc.truncating();
                
                // cout << "saving this fragment: " << endl;
                // cout << "frag ct: " << lfrags_ct << endl;
                // cout << "frag: " << *(lfrags[lfrags_ct]) << endl;
                // cout << "surface_id: " << lsurface_ids[lfrags_ct] << endl;

                lfrags_ct++;
                
                
                break; // out of itertion over f1
              }
            }
            
          } // end iteration over f1
          
          if(lfrags_ct == 2)
          {
            // Found both fragments, we're done looking.
            // Break out of the search loop.

            // cout << "found both fragments; breaking out of search loop." << endl;

            break; // Out of iteration over f0
          }

        } // end if found trfrag that ends at MTRP

      } // end iteration over f0
      
      if(lfrags_ct == 2)
      {
        // Found two fragments; store in result

        xtf0_list.push_back(lfrags[0]);
        xtf1_list.push_back(lfrags[1]);

        assertion(lsurface_ids[0] == lsurface_ids[1]);
        
        xsurface_id_list.push_back(lsurface_ids[1]);

        result = true;

        // cout << "Found two fragments; store in result" << endl;
        // cout << "frag ct: " << lfrags_ct << endl;
        // cout << "xtf0.back: " << *xtf0_list.back() << endl;
        // cout << "xtf1.back: " << *xtf1_list.back() << endl;
        // cout << "surface_id.back: " << xsurface_id_list.back() << endl;
        
      }
      else if(lfrags_ct == 1)
      {
        // Found at most one fragment;
        // this is not the case we're looking.
        // Perhaps MTRP is still under construction
        // Do nothing.

        // cout << "Found only fragment; ignoring" << endl;
        // cout << "frag ct: " << lfrags_ct << endl;
        // cout << "xtf0.back: " << *(lfrags[0]) << endl;
      }

    }// end if MTRP
    
  } // end iteration over map.

  // Postconditions:

  ensure(result ? !xsurface_id_list.empty() : true);
  ensure(xtf0_list.size() == xsurface_id_list.size());
  ensure(xtf1_list.size() == xsurface_id_list.size());

  // cout << "Leaving kd_line_fragment.cc:find_mtrp_truncation_frags." << endl << endl;
  return result;
}
// bool find_mtrp_truncation_frags(const kd_lattice& xhost, 
//                                 id2t_map xid2t_map, 
//                                 frag_list& xtfrags, 
//                                 list<frag_itr>& xtf0_list, 
//                                 list<frag_itr>& xtf1_list, 
//                                 id_list& xsurface_id_list)
// {
//   // cout << endl << "Entering kd_line_fragment.cc:find_mtrp_truncation_frags." << endl;  

//   bool result = false;
//   xtf0_list.clear();
//   xtf1_list.clear();
//   xsurface_id_list.clear();
//   bool lfirst = true;

//   // Search the id to truncation map for type MUTUALLY_TRUNCATING.
//   // There may be multiple instances, we're only interested in
//   // instances that connect to normal truncation points, but there
//   // may be more than one of those too.

//   for(id2t_map_itr m = xid2t_map.begin(); m != xid2t_map.end(); ++m)
//   {
//     if(m->second.type() == kd_truncation::MUTUALLY_TRUNCATING)
//     {
//       // Found a mutually truncating reversal point.

//       cout << "Found a mutually truncating reversal point." << endl;
//       cout << "Point: " << m->first.pod() << endl;
//       cout << "Coords: " << kd_point::coords(xhost, m->first) << endl;
//       cout << "Truncation: " << m->second << endl;

//       for(frag_itr f0 = xtfrags.begin(); f0 != xtfrags.end(); ++f0)
//       {
//         if(f0->pt_ids.back() == m->first)
//         {
//           // Found a tfrag that ends at the mtrp;
//           // find the other end of it.
  
//           cout << "Found a tfrag that ends at the mtrp;" << endl;
          
//           for(frag_itr f1 = xtfrags.begin(); f1 != xtfrags.end(); ++f1)
//           {
//             if((f1 != f0) && (f1->pt_ids.front() == f0->pt_ids.front()))
//             {
//               // Found the other end; check its truncation type.

//               cout << "Found the other end; check its truncation type." << endl;              

//               id2t_map_itr f1m = xid2t_map.find(f1->pt_ids.back());
              
//               assertion(f1m != xid2t_map.end());

//               kd_truncation& lf1_trunc = f1m->second;

//               cout << "other end: " << f1->pt_ids.back().pod() << "  " << kd_point::coords(xhost, f1->pt_ids.back()) << endl;
//               cout << "other end trunc type: " << lf1_trunc << endl;
              
//               if(lf1_trunc.type() == kd_truncation::NORMAL_TRUNCATION)
//               {
//                 // The other end is a normal truncation;
//                 // not another mtrp or mutually truncated, etc.
//                 // This is the case we're looking for.

//                 if(lfirst)
//                 {
//                   xtf0_list.push_back(f0);
//                   lfirst = false;

//                   cout << "push back on xtf0: " << *f0 << endl;
//                 }
//                 else
//                 {
//                   xtf1_list.push_back(f0);
//                   xsurface_id_list.push_back(lf1_trunc.truncating());
//                   result = true;
//                   cout << "push back on xtf1: " << *f0 << endl;
//                   cout << "push back on xsurface_id_list: " << xsurface_id_list.back() << endl;
//                 }
                
//                 break; // out of itertion over f1
//               }
//             }
//           } // end iteration over f1
          
//           if(result)
//           {
//             // Reset for the next iteration
//             // of the map loop.

//             lfirst = true;
//             break; // out of iteration over f0
//           }
//         }
//       } // end iteration over f0
      
//     }
//   }

//   // Postconditions:

//   ensure(result ? !xsurface_id_list.empty() : true);
//   ensure(xtf0_list.size() == xsurface_id_list.size());
//   ensure(xtf1_list.size() == xsurface_id_list.size());

//   // cout << "Leaving kd_line_fragment.cc:find_mtrp_truncation_frags." << endl << endl;
//   return result;
// }

//
// Find the truncation points in the input fragment list.
//
void build_id_to_truncation_map(kd_lattice& xhost, frag_list& xifrags, id2t_map& xid2t_map)
{
  // cout << endl << "Entering kd_line_fragment::build_id_to_truncation_map." << endl;

  xhost.coords().get_read_access();

  for(frag_itr f = xifrags.begin(); f != xifrags.end(); ++f)
  {  
    for(id_list::iterator p = f->pt_ids.begin(); p != f->pt_ids.end(); ++p)
    {
      if(xhost.truncation_points().contains(*p))
      {
        if(xid2t_map.find(*p) == xid2t_map.end())
        {
          kd_truncation ltrunc(xhost, *p);
          
          xid2t_map.insert(id2t_map_val(*p, ltrunc));
        }
      }
    }
  }

  xhost.coords().release_access();
  
  // cout << "Leaving kd_line_fragment::build_id_to_truncation_map." << endl << endl;
  return;
}

//
// Phase 1, maximally extend all the remaining open 
// input fragments, this will include any input
// fragments that don't include a truncation point.
//
void assemble_fragments_phase_1(kd_lattice& xhost, frag_list& xifrags, frag_map& xifrag_map, frag_list& xofrags)
{
  // cout << endl << "Entering kd_line_fragment.cc:assemble_fragments_phase_1." << endl;
  // cout << "input fragments: " << endl << xifrags << endl;

  frag_itr lif = xifrags.begin();
  while(lif != xifrags.end())
  {
    // cout << "fragment: " << *lif << endl;

    if(output_fragment(lif, xifrags, xofrags))
    {
      // Moved closed fragment to output list; move to the next frag.
      // Note that lif is incremented in output_fragment, 
      // so we don't do it here.

      // cout << "moved closed fragment to output list, try another" << endl;
    }
    else if(extend_input_fragment_back_same_surface_truncate(xhost, xifrags, lif, xifrag_map))
    {
      // Succeeded, keep going with this input frag,

      // cout << "extended back of input fragment" << endl;
    }
    else if(extend_input_fragment_front_same_surface_truncate(xhost, xifrags, lif, xifrag_map))
    {
      // Succeeded, keep going with this input frag.

      // cout << "extended front of input fragment" << endl;
    }
    else
    {
      // Closed or can't extend further; move to the next.

      // cout << "couoldn't extend this input frag any further, moving on" << endl;
        
      ++lif;
    }

  } // end while over xifrags

  // cout << "input fragments: " << endl << xifrags << endl;
  // cout << "Leaving kd_line_fragment.cc:assemble_fragments_phase_1." << endl;
  return;
}

//
// Phase 2, find input fragments that begin and end in truncation points
// and create the truncation fragments.
//
void assemble_fragments_phase_2(kd_lattice& xhost,
                                 const kd_line_fragment& xfrag_prototype,
                                 id2t_map& xid2t_map,
                                 frag_list& xifrags, 
                                 frag_map& xifrag_map,
                                 frag_list& xtfrags,
                                 frag_list& xofrags)
{
  // cout << endl << "Entering kd_line_fragment::assemble_fragments_phase_2." << endl;
  // cout << "zone: " << xfrag_prototype.container_id.pod() << endl;
  // cout << "frag list: " << endl << xifrags << endl;

  tr_map ltr_map;  

  frag_itr ltff, ltfb;
  bool lis_reversal;
  bool lis_truncated;
  list<frag_itr> lspans;
  
  frag_itr f = xifrags.begin(); 
  while(f != xifrags.end())
  {
    // cout << "=========== ASSEMBLE_FRAGMENTS_PHASE_2 BEGIN INPUT FRAGMENT =======================================" << endl;
    
    // cout << "input fragment: " << *f << endl;
    
    if(f->spans_truncation(xhost, xid2t_map, lis_reversal, lis_truncated))
    {
      // Tps at ends of f define a truncation pair.

      // cout << "found truncated input fragemnt" << endl;

      // There are nine possible truncation pair types formed by 
      // {NORMAL_TRUNCATION, MUTUALLY_TRUNCATED, MUTUALLY_TRUNCATING}
      // paired with itself. All of these pairs are closed by simple
      // independent truncation paths except the normal-normal-reversed
      // case, which requires the two complementary reversal pairs
      // share a common midpoint. See kd_truncation::is_reverse for
      // definition of reversal.
      // In particular, a truncation pair with one end
      // mutually truncating is not a reversal pair, 
      // even though the mutually truncating end is a 
      // reversal point, since the truncation relationship
      // does not change along the path defined by the pair
      // and it does not require finding the complementary
      // reversal pair. 

      // Check if the truncation frgments have already been generated.

      if(!find_truncation_frags(f, xtfrags, ltff, ltfb))
      {
        // At least one end doesn't exist; create the tfrags.

        if(lis_reversal)
        {
          // This is a reversal pair.

          // cout << "this is a reversal pair" << endl;

          // Get the truncation description for the front
          // so we know which surfaces are involved.

          id2t_map_itr lf_entry = xid2t_map.find(f->pt_ids.front());
          assertion(lf_entry != xid2t_map.end());
          const kd_truncation& lf_trunc = lf_entry->second;

          // cout << "truncation: " << lf_trunc << endl;

          // Try to find a tfrag for the same pair of surfaces;
          // this will be the frgment for the complementary
          // reversal pair, if it exists.

          kd_truncation_pair lf_pair(lf_trunc.truncated(), lf_trunc.truncating());
          tr_map_itr lother_frag = ltr_map.find(lf_pair);
          if(lother_frag == ltr_map.end())
          {
            // Matching fragment doesn't exist yet.
            // Create a truncation fragment for these tps
            // and put it in the map.

            // cout << "couldn't find matching reverse truncated input frag; storing this in map" << endl;

            scoped_index lmid_pt_id;
            make_tfrags(xhost, f, xfrag_prototype, xtfrags, lmid_pt_id, ltff, ltfb);

            ltr_map.insert(tr_map_val(lf_pair, ltff));
            ltr_map.insert(tr_map_val(lf_pair.transpose(), ltff));
          }
          else
          {
            // Matching fragment already exists.

            // cout << "found matching reverse truncated input frag: " << endl;
            // cout << "truncation pair: " << lother_frag->first <<endl;
            // cout << "fragment: " << *lother_frag->second << endl;

            // Get its midpoint.

            scoped_index& lmid_pt_id = lother_frag->second->pt_ids.front();

            // Create the truncation fragment from this fragment, 
            // updating the midpoint from its reversal partner..

            make_tfrags(xhost, f, xfrag_prototype, xtfrags, lmid_pt_id, ltff, ltfb);

            // cout << "front tfrag: " << *ltff << endl;
            // cout << "back tfrag: " << *ltfb << endl;

            // Close the fragment with the tfrags.

            close_input_fragment(f, xifrag_map, ltff, ltfb);

            // Move the input fragment to the output list;
            // erases and advances f.

            output_fragment(f, xifrags, xofrags);
          }
        }
        else if(lis_truncated)
        {  
          // This is a non-reversal fragment.

          // cout << "this is not a reversal pair" << endl;

          scoped_index lmid_pt_id;
          make_tfrags(xhost, f, xfrag_prototype, xtfrags, lmid_pt_id, ltff, ltfb);

          // cout << "front tfrag: " << *ltff << endl;
          // cout << "back tfrag: " << *ltfb << endl;

          // Close the fragment with the tfrags.

          close_input_fragment(f, xifrag_map, ltff, ltfb);

          // Move the input fragment to the output list;
          // erases and advances f.

          output_fragment(f, xifrags, xofrags);
        }
        else
        {
          // This is a truncating surface side of the truncation
          // and the truncation has not yet been created.
          // This includes the case of fragment that end in
          // truncation points but don't actually span a truncation.
          // The only way we can differentiate these from ones that 
          // do span a truncation is that the latter will have
          // matching tfrags generated by the truncated side of
          // the truncation.So save it for later and move on.

          lspans.push_back(f++);
        }
      }
      else
      {
        // Truncation fragments already exist.

        assertion((ltff != xtfrags.end()) && (ltfb != xtfrags.end()));

        // cout << "front tfrag: " << *ltff << endl;
        // cout << "back tfrag: " << *ltfb << endl;

        // Close the fragment with the tfrags.

        close_input_fragment(f, xifrag_map, ltff, ltfb);

        // Move the input fragment to the output list;
        // erases and advances f.

        output_fragment(f, xifrags, xofrags);
      }
    }
    else
    {
      // Fragment does not span a truncation;
      // just move on.

      // cout << "Fragment does not span a truncation;" << endl;
      
      ++f;  
    }
    

    // cout << "=========== ASSEMBLE_FRAGMENTS_PHASE_2 END INPUT FRAGMENT =======================================" << endl;
  }
  
  // Now we've found and generated all the truncation fragments, but
  // we may not have closed all the truncating side fragments. So go back
  // though the ones we saved, trying to find truncation fragments to
  // close them with.

  for(list<frag_itr>::iterator ls = lspans.begin(); ls != lspans.end(); ++ls)
  {
    if(find_truncation_frags(*ls, xtfrags, ltff, ltfb))
    {
      // Found the closing tfrags.

      assertion((ltff != xtfrags.end()) && (ltfb != xtfrags.end()));

      // cout << "front tfrag: " << *ltff << endl;
      // cout << "back tfrag: " << *ltfb << endl;

      // Close the fragment with the tfrags.

      close_input_fragment(*ls, xifrag_map, ltff, ltfb);

      // Move the input fragment to the output list;
      // erases and advances the iterator ls points to; 
      // but we don't care about it.

      output_fragment(*ls, xifrags, xofrags);
    }
  }  
  
  // Exit:

  // cout << endl << "truncation frag list: " << endl << xtfrags << endl;
  // cout << endl << "input frag list: " << endl << xifrags << endl;
  
  // cout << "Leaving kd_line_fragment::assemble_fragments_phase_2." << endl;
  return;  
}

//
// Phase 3, maximally extend all input fragments that contain a truncation point.
// For each truncation fragment, find all input fragments it can extend,
// when no input fragments can be found, erase the truncation fragment.
//
void assemble_fragments_phase_3(kd_lattice& xhost,
                                const kd_line_fragment& xfrag_prototype,
                                id2t_map xid2t_map,
                                frag_list& xifrags, 
                                frag_map& xifrag_map, 
                                frag_list& xtfrags,
                                frag_list& xofrags)
{
  // cout << endl << "Entering kd_line_fragment.cc:assemble_fragments_phase_3." << endl;
  // cout << "zone: " << xfrag_prototype.container_id.pod() << endl;
  // cout << "input fragments: " << endl << xifrags << endl;

  // This algorithm fails in the case of a mutually truncating reversal point (MRTP).
  // In that case, two truncation fragments have the same back and should connect
  // to each other through the implied, degenerate "input" fragment from the MRTP
  // to itself. Since this "input" fragment doesn't exist, we have to create the
  // connection directly. This problem occurs only if  a single MTRP is connected
  // to two nornal truncation points. A pair of connected mutually truncating points 
  // corresponds to a reversal line and does not have this problem. There may
  // however be more than one such MRTP in a zone, so we look for as many as
  // we can find.

  typedef list<frag_itr> fi_list;
  typedef fi_list::iterator fi_list_itr;
  fi_list ltff_list, ltfb_list;

  frag_itr ltff, ltfb;
  
  id_list lsurf_id_list;

  // Look for MTRPs connected to normal tps.

  if(find_mtrp_truncation_frags(xhost, xid2t_map, xtfrags, ltff_list, ltfb_list, lsurf_id_list))
  {
    // Found at least one; create the fragment for each.

    fi_list_itr ltff_itr = ltff_list.begin();
    fi_list_itr ltfb_itr = ltfb_list.begin();
    
    for(id_list::iterator ls = lsurf_id_list.begin(); ls != lsurf_id_list.end(); ++ls, ++ltff_itr, ++ltfb_itr)
    {
      xifrags.push_back(xfrag_prototype);
      frag_itr ltf = --xifrags.end();

      ltf->container_id.put_pod(TOP_INDEX);
      ltf->surface_id = *ls;

      ltff = *ltff_itr;
      ltfb = *ltfb_itr;
      
      ltf->pt_ids.push_back(ltff->pt_ids.front());
      ltf->pt_ids.push_back(ltff->pt_ids.back());
      ltf->pt_ids.push_back(ltfb->pt_ids.front());
      xifrag_map.insert(frag_map::value_type(ltf->front_pod(), ltf));
      xifrag_map.insert(frag_map::value_type(ltf->back_pod(), ltf));

      // cout << "created MTRP fragment: " << *ltf << endl;
    }
  }

  // Now the main act; maximally extend all input fragments that contain a truncation point.
  // For each truncation fragment, find all input fragments it can extend,
  // when no input fragments can be found, erase the truncation fragment.

  while(!xtfrags.empty())
  {
    frag_itr ltf = xtfrags.begin();

    // cout << "truncation fragment: " << *ltf << endl;

    frag_itr lif = extend_truncation_fragment(xhost, xifrags, ltf, xifrag_map);
    while(lif != xifrags.end())
    {
      // cout << "fragment: " << *lif << endl;

      if(output_fragment(lif, xifrags, xofrags))
      {
        // Moved closed fragment to output list;
        // try to find another input frag for this trunc frag.
        // Note that lif is incremented in output_fragment, 
        // but we just over-write it here anyway..

        // cout << "moved closed fragment to output list, try another" << endl;
        
        lif = extend_truncation_fragment(xhost, xifrags, ltf, xifrag_map);
      }
      else if(extend_input_fragment_back_same_surface_truncate(xhost, xifrags, lif, xifrag_map))
      {
        // Succeeded, keep going with this input frag,

        // cout << "extended back of input fragment" << endl;
      }
      else if(extend_input_fragment_front_same_surface_truncate(xhost, xifrags, lif, xifrag_map))
      {
        // Succeeded, keep going with this input frag.

        // cout << "extended front of input fragment" << endl;
      }
      else
      {
        // Closed or can't extend further;
        // try to find another input frag for this trunc frag.

        // cout << "couldn't extend this input frag any further, try another" << endl;
        
        lif = extend_truncation_fragment(xhost, xifrags, ltf, xifrag_map);
      }
      
    } // end while over xifrags
    
    // Found all the extensions to the current truncation frag.
    // Erase it from the list and try the next one.

    xtfrags.pop_front();
  }

  // cout << "input fragments: " << endl << xifrags << endl;
  // cout << "Leaving kd_line_fragment.cc:assemble_fragments_phase_3." << endl;
  return;
}

//
// Phase 4, all input fragments are now either closed or the back is a 
// a line end or a truncation mid point. We can combine open fragments
// the same surface that share a truncation point or truncation mid point.
//
void assemble_fragments_phase_4(kd_lattice& xhost, frag_list& xifrags, frag_map& xifrag_map, frag_list& xofrags)
{
  // cout << endl << "Entering kd_line_fragment.cc:assemble_fragments_phase_4." << endl;
  // cout << "input fragments: " << endl << xifrags << endl;

  frag_itr lif = xifrags.begin();
  while(lif != xifrags.end())
  {
    // cout << "fragment: " << *lif << endl;
    
    if(output_fragment(lif, xifrags, xofrags))
    {
      // Moved closed fragment to output list; move to the next frag
      // Note that lif is incremented in output_fragment, 
      // so we don't do it here.

      // cout << "moved closed fragment to output list, try another" << endl;
    }
    else if(extend_input_fragment_back_same_side(xhost, xifrags, lif, xifrag_map))
    {
      // Succeeded, keep going with this input frag,

      // cout << "extended back of input fragment" << endl;
    }
    else if(extend_input_fragment_front_same_side(xhost, xifrags, lif, xifrag_map))
    {
      // Succeeded, keep going with this input frag.

      // cout << "extended front of input fragment" << endl;
    }
    else
    {
      // Closed or can't extend further; move to the next.

      // cout << "couoldn't extend this input frag any further, moving on" << endl;
        
      ++lif;
    }

  } // end while over xifrags

  // cout << "input fragments: " << endl << xifrags << endl;
  // cout << "Leaving kd_line_fragment.cc:assemble_fragments_phase_4." << endl;
  return;
}

//
// Phase 5, all input fragments are now either closed or the back is a 
// a line end. We can close fragments that span multiple faces.
//
void assemble_fragments_phase_5(kd_lattice& xhost, frag_list& xifrags, frag_list& xofrags)
{
  // cout << endl << "Entering kd_)line_fragment.cc:assemble_fragments_phase_5." << endl;
  // cout << "input fragments: " << endl << xifrags << endl;


  frag_itr lif = xifrags.begin();
  while(lif != xifrags.end())
  {
    // cout << "fragment: " << *lif << endl;

    if(output_fragment(lif, xifrags, xofrags))
    {
      // Moved closed fragment to output list; move to next frag.
      // Note that lif is incremented in output_fragment, 
      // so we don't do it here.

      // cout << "moved closed fragment to output list, try another" << endl;
    }
    else if(lif->spans_multiple_faces())
    {
      // Close the fragment and output it.
      // Note that lif is incremented in output_fragment, 
      // so we don't do it here.

      // cout << "closing and moving to output list" << endl;

      lif->pt_ids.push_back(lif->pt_ids.front());
      output_fragment(lif, xifrags, xofrags);
    }
    else
    {
      // The fragment can not be closed; erase it.

      // cout << "can't be closed, erasing" << endl;

      xifrags.erase(lif++);
    }
  } // end while over xifrags

  // cout << "input fragments: " << endl << xifrags << endl;
  // cout << "Leaving kd_line_fragment.cc:assemble_fragments_phase_5." << endl;
  return;
}

//
// Finds mutually truncating points and labels them as reversal points.
//
void label_mtrps(kd_lattice& xhost, id2t_map xid2t_map)
{
  // cout << endl << "Entering kd_line_fragment.cc:label_mtrps." << endl;  


  // Search the id to truncation map for type MUTUALLY_TRUNCATING.
  // All such points a truncation reversal points.

  for(id2t_map_itr m = xid2t_map.begin(); m != xid2t_map.end(); ++m)
  {
    if(m->second.type() == kd_truncation::MUTUALLY_TRUNCATING)
    {
      // Found a mutually truncating reversal point.
      
      xhost.truncation_reversal_points().insert_member(m->first);

      // cout << "inserted: " << m->first.pod() << " in truncation reversal points" << endl;
    }
  }

  // Postconditions:


  // cout << "Leaving kd_line_fragment.cc:label_mtrps." << endl << endl;
  return;
}

//
// Assembles the input fragments in xifrags using the
// truncation fragments in xtfrags.
//
void assemble_fragments(kd_lattice& xhost,
                        const kd_line_fragment& xfrag_prototype,
                        frag_list& xifrags, 
                        frag_map& xifrag_map, 
                        frag_list& xtfrags,
                        frag_list& xofrags)
{
  // cout << endl << "Entering kd_line_fragment.cc:assemble_fragments." << endl;
  // cout << "zone: " << xfrag_prototype.container_id.pod() << endl;
  // cout << "input fragments: " << endl << xifrags << endl;

  // Preconditions:


  // Body:

  scoped_index lzone_id(xfrag_prototype.container_id);

  // Find all the truncation points and map them to
  // truncation description objects.

  id2t_map lid2t_map;

  build_id_to_truncation_map(xhost, xifrags, lid2t_map);
  
  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  // cout << "zone: " << lzone_id.pod() << " assembly phase 1" << endl;
  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

  // First, maximally extend all the remaining open 
  // input fragments, this will include any input
  // fragments that don't include a truncation point.

  assemble_fragments_phase_1(xhost, xifrags, xifrag_map, xofrags);

  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  // cout << "zone: " << lzone_id.pod() << " assembly phase 2" << endl;
  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

  // Second, find input fragments that begin and end in truncation points
  // and create the truncation fragments.

  assemble_fragments_phase_2(xhost, xfrag_prototype, lid2t_map, xifrags, xifrag_map, xtfrags, xofrags);

  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  // cout << "zone: " << lzone_id.pod() << " assembly phase 3" << endl;
  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

  // Third, maximally extend all input fragments that contain a truncation point.
  // For each truncation fragment, find all input fragments it can extend,
  // when no input fragments can be found, erase the truncation fragment.

  assemble_fragments_phase_3(xhost, xfrag_prototype, lid2t_map, xifrags, xifrag_map, xtfrags, xofrags);  

  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  // cout << "zone: " << lzone_id.pod() << " assembly phase 4" << endl;
  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

  // Fourth, all input fragments are now either closed or the back is a 
  // a line end or a truncation mid point. We can combine open fragments
  // the same surface that share a truncation point or truncation mid point.

  assemble_fragments_phase_4(xhost, xifrags, xifrag_map, xofrags);  

  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  // cout << "zone: " << lzone_id.pod() << " assembly phase 5" << endl;
  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

  // Fifth, all input fragments are now either closed or the back is a 
  // a line end. We can close fragments that span multiple faces.

  assemble_fragments_phase_5(xhost, xifrags, xofrags);

  // Finally, make sure the mutally truncating points
  // are labelled as reversal points.

  label_mtrps(xhost, lid2t_map);

  // Exit:

  // cout << "Leaving kd_line_fragment.cc:assemble_fragments." << endl;
  return;
}

  
} // end unnamed namespace.


// ===========================================================
// KD_LINE_FRAGMENT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

kd_line_fragment::
kd_line_fragment()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(pt_ids.empty());
  ensure(!container_id.is_valid());

  // Exit:

  return;
}

kd_line_fragment::
kd_line_fragment(const scoped_index& xcontainer_id)
  : container_id(xcontainer_id)
{
  // Preconditions:


  // Body:

  // Postconditions:

  ensure(pt_ids.empty());
  ensure(container_id == xcontainer_id);
  
  // Exit:

  return;
}

kd_line_fragment::
~kd_line_fragment()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:


  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// POINT IDS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS
 
bool
geometry::kd_line_fragment::
is_closed() const
{
  // cout << endl << "Entering kd_line_fragment::is_closed." << endl;

  // Preconditions:

  require(!pt_ids.empty());

  // Body:

  bool result = pt_ids.front() == pt_ids.back();
  
  // Postconditions:


  // Exit

  // cout << "Leaving kd_line_fragment::is_closed." << endl;
  return result;
}

bool
geometry::kd_line_fragment::
is_reverse_of(const kd_line_fragment& xother) const
{
  // cout << endl << "Entering kd_line_fragment::is_reverse_of." << endl;

  // Preconditions:


  // Body:


  id_list::const_iterator lthis_itr = pt_ids.begin();
  id_list::const_reverse_iterator lother_itr = xother.pt_ids.rbegin();
  
  bool result = true;
  while((lthis_itr != pt_ids.end()) && (lother_itr != xother.pt_ids.rend()))
  {
    if(*lthis_itr != *lother_itr)
    {
      result = false;
      break;
    }
    
    lthis_itr++;
    lother_itr++;
  }

  // Postconditions:


  // Exit:

  // cout << "result " << boolalpha << result << noboolalpha << endl;
  
  // cout << "Leaving kd_line_fragment::is_reverse_of." << endl;
  return result;
}


bool
geometry::kd_line_fragment::
spans_truncation(const kd_lattice& xhost, 
                 map<scoped_index, kd_truncation>& xid2t_map, 
                 bool& xis_reversal, 
                 bool& xis_truncated) const
{
  // cout << endl << "Entering kd_line_fragment::spans_truncation." << endl;
  // cout << "for fragment: " << *this << endl;
  
  // Preconditions:

  require(!pt_ids.empty());
  require(++pt_ids.begin() != pt_ids.end());

  // Body:

  xis_reversal = false;
  xis_truncated = false;
  bool result  = false;
  if(xhost.truncation_points().contains(pt_ids.front()) && xhost.truncation_points().contains(pt_ids.back()) )
  {
    // Both are truncation points.

    id2t_map_itr ltpmf, ltpmb;
    ltpmf = xid2t_map.find(pt_ids.front());
    ltpmb = xid2t_map.find(pt_ids.back());
      
    assertion(ltpmf != xid2t_map.end());
    assertion(ltpmb != xid2t_map.end());

    kd_truncation& ltdf = ltpmf->second;
    kd_truncation& ltdb = ltpmb->second;

    // cout << "front truncation: " << endl << ltdf << endl;
    // cout << "back truncation:  " << endl << ltdb << endl;

    if(ltdf.has_same_surfaces(ltdb))
    {
      // The fragment connects the same surfaces at each end;
      // spans and may define a truncation.
      // Note that this unfortunately includes the case in which
      // the fragment spans two truncation points between the
      // same two surfaces but doesn't actually span a truncation,
      // it is just a fragment in the truncating surface that
      // connects two branches of the truncated surface. The
      // only way we can differentiate a truncating fragment that 
      // connects two truncated branches from a truncating fragment
      // that spans a truncation is that the latter will have a
      // matching truncated fragment that defines the truncation.
      // We find that in assemble_fragments_phase_2.

      result = true;

      if((ltdf.is_truncated(surface_id)) && (ltdb.is_truncated(surface_id)))
      {
        // Spans and defines a truncation.

        xis_truncated = true;
      }
      else if(ltdf.is_reverse(ltdb))
      {
        // Spans and defines a truncation reversal.

        xis_reversal = true;
      }      
    }      
  }
  
  // Postconditions:


  // Exit:

  // cout<< boolalpha;
  // cout << "result: " << result;
  // cout << "  xis_reversal: " << xis_reversal;
  // cout << "  xis_truncated: " << xis_truncated;
  // cout << noboolalpha << endl;
  // cout << "Leaving kd_line_fragment::spans_truncation." << endl;
  return result;
}

void
geometry::kd_line_fragment::
insert_front(const kd_line_fragment& xother_frag, bool xfwd)
{
  // cout << endl << "Entering kd_line_fragment::insert_front." << endl;

  // Preconditions:

  require(xfwd ? front_pod() == xother_frag.back_pod() : front_pod() == xother_frag.front_pod());

  // Body:

  // cout << "this: " << *this << endl;  
  // cout << "inserting " << xother_frag << " in " << (xfwd ? "fwd" : "rev") << " direction" << endl;

  if(xfwd)
  {
    // Attach the fragment in the forwards direction.

    pt_ids.insert(pt_ids.begin(), xother_frag.pt_ids.begin(), --xother_frag.pt_ids.end());
  }
  else
  {
    // Attach the fragment in the reverse direction.

    pt_ids.insert(pt_ids.begin(), xother_frag.pt_ids.rbegin(), --xother_frag.pt_ids.rend());
  }

  update_container_id(xother_frag.container_id);
  
  // cout << "result: " << *this << endl;

  // Postconditions:

  ensure(xfwd ? front_pod() == xother_frag.front_pod() : front_pod() == xother_frag.back_pod());
  
  // Exit:

  // cout << "Leaving kd_line_fragment::insert_front." << endl;
  return;
}

void
geometry::kd_line_fragment::
insert_back(const kd_line_fragment& xother_frag, bool xfwd)
{
  // cout << endl << "Entering kd_line_fragment::insert_back." << endl;

  // Preconditions:

  require(xfwd ? back_pod() == xother_frag.front_pod() : back_pod() == xother_frag.back_pod());

  // Body:

  // cout << "this: " << *this << endl;
  // cout << "inserting " << xother_frag << " in " << (xfwd ? "fwd" : "rev") << " direction" << endl;

  if(xfwd)
  {
    // Attach the fragment in the forwards direction.

    pt_ids.insert(pt_ids.end(), ++xother_frag.pt_ids.begin(), xother_frag.pt_ids.end());
  }
  else
  {
    // Attach the fragment in the reverse direction.

    pt_ids.insert(pt_ids.end(), ++xother_frag.pt_ids.rbegin(), xother_frag.pt_ids.rend());
  }

  update_container_id(xother_frag.container_id);
  
  // cout << "result: " << *this << endl;

  // Postconditions:

  ensure(xfwd ? back_pod() == xother_frag.back_pod() : back_pod() == xother_frag.front_pod());
  
  // Exit:

  // cout << "Leaving kd_line_fragment::insert_back." << endl;
  return;
}

void
geometry::kd_line_fragment::
splice_front(kd_line_fragment& xother_frag)
{
  // cout << endl << "Entering kd_line_fragment::splice_front." << endl;

  // Preconditions:

  require(front_pod() == xother_frag.back_pod());

  define_old_variable(pod_index_type old_xother_frag_front_pod = xother_frag.front_pod());

  // Body:

  // cout << "this: " << *this << endl;
  // cout << "splicing " << xother_frag << endl;

  // Attach the fragment in the forwards direction.

  pt_ids.splice(pt_ids.begin(), xother_frag.pt_ids, xother_frag.pt_ids.begin(), --xother_frag.pt_ids.end());

  update_container_id(xother_frag.container_id);
  
  // cout << "result: " << *this << endl;

  // Postconditions:

  ensure(front_pod() == old_xother_frag_front_pod);
  
  // Exit:

  // cout << "Leaving kd_line_fragment::splice_front." << endl;
  return;
}

void
geometry::kd_line_fragment::
splice_back(kd_line_fragment& xother_frag)
{
  // cout << endl << "Entering kd_line_fragment::splice_back." << endl;

  // Preconditions:

  require(back_pod() == xother_frag.front_pod());

  define_old_variable(pod_index_type old_xother_frag_back_pod = xother_frag.back_pod());
  

  // Body:

  // cout << "this: " << *this << endl;
  // cout << "other: " << xother_frag << endl;
  
  // cout << "this: " << *this << endl;
  // cout << "splicing " << xother_frag << endl;

  // Attach the fragment in the forwards direction.

  pt_ids.splice(pt_ids.end(), xother_frag.pt_ids, ++xother_frag.pt_ids.begin(), xother_frag.pt_ids.end());


  update_container_id(xother_frag.container_id);
  
  // cout << "result: " << *this << endl;

  // Postconditions:

  ensure(back_pod() == old_xother_frag_back_pod);
  
  // Exit:

  // cout << "Leaving kd_line_fragment::splice_back." << endl;
  return;
}

void
geometry::kd_line_fragment::
segment(const kd_lattice& xhost, id_list::const_iterator xpt_id_itr, e3_lite& xresult) const
{
  // cout << endl << "Entering kd_line_fragment::segment." << endl;

  // Preconditions:

  require(++id_list::const_iterator(xpt_id_itr) != pt_ids.end());
  //  require(unexecutable("++xpt_id_itr != pt_ids.end()"));
  require(xhost.coords().state_is_read_accessible());
  
  // Body:

  const scoped_index& lpt0_id = *xpt_id_itr;
  const scoped_index& lpt1_id = *(++xpt_id_itr);
  
  xhost.coords().get_fiber(lpt1_id, xresult, false);
  
  e3_lite lpt0;
  xhost.coords().get_fiber(lpt0_id, lpt0, false);
  
  xresult -= lpt0;

  // cout << "pt0_id: " << lpt0_id.pod();
  // cout << " pt1_id: " << lpt1_id.pod();
  // cout << "  seg: "  << xresult << endl;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line_fragment::segment." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS


// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// COORDINATES FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
geometry::kd_line_fragment::
coords(const kd_lattice& xhost, pt_list& xresult) const
{
  // cout << endl << "Entering kd_line_fragment::coords." << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_accessible());

  // Body:

  e3_lite lpt;
  for(id_list::const_iterator i = pt_ids.begin(); i != pt_ids.end(); ++i)
  {
    xhost.coords().get_fiber(*i, lpt, false);
    xresult.push_back(lpt);
  }

  // Postconditions:

  ensure(xresult.size() == pt_ids.size());
  
  // Exit:

  // cout << "Leaving kd_line_fragment::coords." << endl;
  return;
}

void
geometry::kd_line_fragment::
coords(const kd_lattice& xhost, int xu, int xv, list<e2_lite>& xresult) const
{
  // cout << endl << "Entering kd_line_fragment::coords." << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_accessible());

  // Body:

  e3_lite lpt_3d;
  e2_lite lpt_2d;
  for(id_list::const_iterator i = pt_ids.begin(); i != pt_ids.end(); ++i)
  {
    xhost.coords().get_fiber(*i, lpt_3d, false);

    lpt_2d[0] = lpt_3d[xu];
    lpt_2d[1] = lpt_3d[xv];
    
    xresult.push_back(lpt_2d);
  }

  // Postconditions:

  ensure(xresult.size() == pt_ids.size());
  
  // Exit:

  // cout << "Leaving kd_line_fragment::coords." << endl;
  return;
}

void
geometry::kd_line_fragment::
normal(const kd_lattice& xhost, id_list::const_iterator xpt_itr, e3_lite& xresult) const
{
  // cout << endl << "Entering kd_line_fragment::normal." << endl;
  // cout << "fragment: " << *this << endl;
  // cout << "itr: " << ((xpt_itr != pt_ids.end()) ? xpt_itr->pod() : invalid_pod_index()) << endl;
  
  // Preconditions:

  // How do we implement these without modifying xpt_itr?

  require(unexecutable("++xpt_itr != pt_ids.end()"));
  require(unexecutable("++(++xpt_itr) != pt_ids.end()"));

  // Body:

  e3_lite lpta;
  xhost.coords().get_fiber(*xpt_itr, lpta, false);
 
  ++xpt_itr;
  assertion(xpt_itr != pt_ids.end());
  
  e3_lite lptb;
  xhost.coords().get_fiber(*xpt_itr, lptb, false);
 
  ++xpt_itr;
  assertion(xpt_itr != pt_ids.end());

  e3_lite lptc;
  xhost.coords().get_fiber(*xpt_itr, lptc, false);
  
  e3_lite lab(lptb);
  lab -= lpta;
  
  e3_lite lac(lptc);
  lac -= lpta;
  
  cross(lab, lac, xresult);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line_fragment::normal." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
// CONTAINER ID FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
geometry::kd_line_fragment::
update_container_id(const scoped_index& xcontainer_id)
{
  // cout << endl << "Entering kd_line_fragment::update_container_id." << endl;

  // Preconditions:

  require(container_id.is_valid()); // not created by default constructor
  require(xcontainer_id.is_valid());

  define_old_variable(scoped_index old_container_id = container_id);
  
  // Body:

  if(xcontainer_id != container_id)
  {
    // This fragment spans multiple tree nodes;
    // mark it by setting container id to something
    // that can not be a container id, top will do.

    /// @issue To be meaningful, the container id 
    /// should be updated to the p_join of the current
    /// container_id and xcontainer_id, then it really
    /// is the id of the container. But there's no practical
    /// way to compute the p_join at this point.
    /// The method used here supports the spans_multiple_faces
    /// query, but linking triangles in triangulate().

    container_id.put_pod(TOP_INDEX);
  }

  // Postconditions:

  ensure((xcontainer_id == old_container_id) ? (container_id == old_container_id) : spans_multiple_faces());
  
  // Exit:

  // cout << "Leaving kd_line_fragment::update_container_id." << endl;
  return;
}

bool
geometry::kd_line_fragment::
spans_multiple_faces() const
{
  // cout << endl << "Entering kd_line_fragment::spans_multiple_faces." << endl;

  // Preconditions:


  // Body:

  bool result = (container_id.pod() == TOP_INDEX);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line_fragment::spans_multiple_faces." << endl;
  return result;
}

bool
geometry::kd_line_fragment::
is_star_shaped(kd_lattice& xhost, int xu, int xv) const
{
  // cout << endl << "Entering kd_line_fragment::is_star_shaped." << endl;

  // Preconditions:

  require(is_closed());
  require(pt_ids.size() >= 3);

  // Body:

  // Get the points in the xu, xv plane.

  list<e2_lite> lpts;
  coords(xhost, xu, xv, lpts);

  // Compute the centroid.

  int lpt_ct = 0;
  e2_lite lctr(0.0, 0.0);
  for(list<e2_lite>::iterator lp = ++lpts.begin(); lp != lpts.end(); ++lp, ++lpt_ct)
  {
    lctr += *lp;
  }
  lctr[0] /= lpt_ct;
  lctr[1] /= lpt_ct;
  
  
  bool result = true;

  list<e2_lite>::iterator lprev = lpts.begin();
  for (list<e2_lite>::iterator lp = ++lpts.begin(); lp != lpts.end(); ++lp, ++lprev)
  {
    if(TriangleIsCW(lctr, *lprev, *lp))
    {
      result = false;
      break;
    }
  }

//   id_list::const_iterator lid, lprev_id, lnext_id;
//   list<e2_lite>::iterator lpt, lprev_pt, lnext_pt;
  
//   lprev_id = pt_ids.begin();
//   lid      = ++pt_ids.begin();
//   lnext_id = ++(++pt_ids.begin());

//   lprev_pt = lpts.begin();
//   lpt      = ++lpts.begin();
//   lnext_pt = ++(++lpts.begin());

//   while(lnext_id != pt_ids.end())
//   {
//     if(TriangleIsCW(*lprev_pt, *lpt, *lnext_pt))
//     {
//       result = false;
//       break;
//     }
//     ++lprev_id;
//     ++lid;
//     ++lnext_id;
//     ++lprev_pt;
//     ++lpt;
//     ++lnext_pt;
//   }  

  // Postconditions:


  // Exit:

  // cout << "result: " << boolalpha << result << noboolalpha << endl;
  // cout << "Leaving kd_line_fragment::is_star_shaped." << endl;
  return result;
}

bool
geometry::kd_line_fragment::
is_convex(kd_lattice& xhost, int xu, int xv) const
{
  // cout << endl << "Entering kd_line_fragment::is_convex." << endl;

  // Preconditions:

  require(is_closed());
  require(pt_ids.size() >= 3);

  // Body:

  // Get the points in the xu, xv plane.

  list<e2_lite> lpts;
  coords(xhost, xu, xv, lpts);

  id_list::const_iterator lid, lprev_id, lnext_id;
  list<e2_lite>::iterator lpt, lprev_pt, lnext_pt;
  
  lprev_id = pt_ids.begin();
  lid      = ++pt_ids.begin();
  lnext_id = ++(++pt_ids.begin());

  lprev_pt = lpts.begin();
  lpt      = ++lpts.begin();
  lnext_pt = ++(++lpts.begin());

  bool result = true;
  while(lnext_id != pt_ids.end())
  {
    if(TriangleIsCW(*lprev_pt, *lpt, *lnext_pt))
    {
      result = false;
      break;
    }
    ++lprev_id;
    ++lid;
    ++lnext_id;
    ++lprev_pt;
    ++lpt;
    ++lnext_pt;
  }  

  // Postconditions:


  // Exit:

  // cout << "result: " << boolalpha << result << noboolalpha << endl;
  // cout << "Leaving kd_line_fragment::is_convex." << endl;
  return result;
}


void
geometry::kd_line_fragment::
triangulate(kd_lattice& xhost, int xu, int xv) const
{
  // cout << endl << "Entering kd_line_fragment::triangulate." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.surfaces().contains(surface_id));
  require(xhost.zones().contains(container_id) || xhost.faces().contains(container_id));
  require(xhost.leaves().contains(container_id));
  
  // Body:

  if(is_closed() && pt_ids.size() >= 3)
  {
    if(is_star_shaped(xhost, xu, xv))
    {
      triangulate_centroid(xhost);
    }
    else
    {
      triangulate_ear_clip(xhost, xu, xv);
    }
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line_fragment::triangulate." << endl;
  return;
}

void
geometry::kd_line_fragment::
triangulate_centroid(kd_lattice& xhost) const
{
  // cout << endl << "Entering kd_line_fragment::triangulate_centroid." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.surfaces().contains(surface_id));
  require(xhost.zones().contains(container_id) || xhost.faces().contains(container_id));
  require(xhost.leaves().contains(container_id));
  require(is_closed());
  require(pt_ids.size() >= 3);
  
  // Body:

  // Polygon has at least two segments,
  // we can triangulate it.    

  base_space_poset& lbase = xhost.base_space();
  sec_e3& lcoords = xhost.coords();

  e3_lite lpt, lctr;
  scoped_index lpt_id, lctr_id, lseg1_id, lseg2_id, ltri_id;
  id_list::const_iterator j, lv0, lv1;

  // Create a centroid for the current polygon.

  lctr_id = xhost.centroids().new_member();

  lctr = 0.0;
  int lv_ct = 0;
  j = pt_ids.begin();
      
  // First vertex: id, coords.

  lv1 = j;

  lcoords.get_fiber(*lv1, lpt, false);
  lctr += lpt;
  ++lv_ct;
      
  ++j;

  while(j != pt_ids.end())
  {
    // First vertex of this segment is
    // second vertex of previous segment.

    lv0 = lv1;
        
    // Second vertex: id, coords.

    lv1 = j;        

    // Accumulate average for centroid,
    // but don't count the last point if it
    // is the same as the first.

    if(*lv1 != pt_ids.front())
    {
      lcoords.get_fiber(*lv1, lpt, false);
      lctr += lpt;
      ++lv_ct;
    }        

    // cout << "  " << lv1->internal_pod();
        
    // Create the triangle.

    ltri_id = kd_triangle::new_triangle(xhost, *lv0, *lv1, lctr_id);
        
    // Link it to the container.

    lbase.new_link(container_id, ltri_id);

    // Link it to surface as well.

    lbase.new_link(surface_id, ltri_id);

    // Next.

    ++j;
  } // j != pt_ids.end()

  // cout << endl;
      
  // Normalize the center position.

  // cout << "vertex ct: " << lv_ct << endl;

  lctr /= lv_ct;
  lcoords.force_fiber(lctr_id, lctr, false);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line_fragment::triangulate_centroid." << endl;
  return;
}

void
geometry::kd_line_fragment::
triangulate_ear_clip(kd_lattice& xhost, int xu, int xv) const
{
  // cout << endl << "Entering kd_line_fragment::triangulate_ear_clip." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.surfaces().contains(surface_id));
  require(xhost.zones().contains(container_id) || xhost.faces().contains(container_id));
  require(xhost.leaves().contains(container_id));
  require(is_closed());
  require(pt_ids.size() >= 3);
  
  // Body:

  // Polygon has at least two segments,
  // we can triangulate it.
    
  base_space_poset& lbase = xhost.base_space();
  scoped_index ltri_id;

  // $$SCRIBBLE: vectors used to make it easy to follow Ericson's example.
  // It would be more efficient if we reimplmented using just lists,
  // better yet, implement a circular list class. Of course, it's
  // an O(n*n) algorithm, so I guess the copies don't matter much.

  vector<e2_lite> v;
  vector<scoped_index> lv_ids;
  vector<int> prev, next, visited;
  
  
  e3_lite lpt_3d;
  e2_lite lpt_2d;


  // Copy the list to an array while getting coordinates

  v.clear();
  lv_ids.clear();    
  int lsize = 0;

  for(id_list::const_iterator i = pt_ids.begin(); i != pt_ids.end(); ++i)
  {
    xhost.coords().get_fiber(*i, lpt_3d, false);

    lpt_2d[0] = lpt_3d[xu];
    lpt_2d[1] = lpt_3d[xv];
    
    v.push_back(lpt_2d);
    lv_ids.push_back(*i);
    ++lsize;
  }

  --lsize;  // last == first not used below.
    

  // Set up previous and next links to effectively form a circular double-linked vertex list

  prev.clear();
  next.clear();
  visited.clear();
  for (int i = 0; i < lsize; i++) 
  {
    prev.push_back(i - 1);
    next.push_back(i + 1);
    visited.push_back(false);
  }
  prev[0] = lsize - 1;
  next[lsize - 1] = 0;

  // Start at vertex 0 and keep removing vertices 
  // until just a triangle left

  int n = lsize;
  int i = 0;    

  while (n > 3) 
  {
    // cout << "n: " << n;
    // cout << "  vertices: ";
    // cout << setw(6) << lv_ids[prev[i]].pod();
    // cout << setw(6) << lv_ids[i].pod();
    // cout << setw(6) << lv_ids[next[i]].pod();
    // cout << endl;
      
    visited[i] = true;

    // Test if current vertex, v[i], is an ear

    //      int isEar = 1;
    bool isEar = true;

    // An ear must be convex (here counterclockwise)

    // cout << "  Test TriangleIsCCW for vertices: ";
    // cout << setw(6) << lv_ids[prev[i]].pod();
    // cout << setw(6) << lv_ids[i].pod();
    // cout << setw(6) << lv_ids[next[i]].pod();

    if (TriangleIsCCW(v[prev[i]], v[i], v[next[i]])) 
    {
      // Loop over all vertices not part of the tentative ear

      // cout << " result = true" << endl;

      int k = next[next[i]];
        
      do 
      {
        // If vertex k is inside the ear triangle, then this is not an ear

        // cout << "  Test Point In Triangle for point: ";
        // cout << setw(6) << lv_ids[k].pod();
        // cout << "  triangle: ";
        // cout << setw(6) << lv_ids[prev[i]].pod();
        // cout << setw(6) << lv_ids[i].pod();
        // cout << setw(6) << lv_ids[next[i]].pod();

        // If v[i] is a duplicated point in an internal edge;
        // we don't want to consider its duplicate to be
        // inside the triangle and hence make it not an ear.

        bool lsame_point = (lv_ids[k] == lv_ids[prev[i]]) || (lv_ids[k] == lv_ids[i]) || (lv_ids[k] == lv_ids[next[i]]);
          
        if(!lsame_point && TestPointTriangle(v[k], v[prev[i]], v[i], v[next[i]]))
        {
          // isEar = 0;
          isEar = false;
          // cout << "  result = true" << endl;
          break;
        }
        // cout << "  result = false" << endl;
          
        k = next[k];
      } 
      while (k != prev[i]);
    }
    else 
    {
      // The `ear' triangle is clockwise so v[i] is not an ear

      // cout << " result = false" << endl;
      isEar = false;
    }

    // If current vertex v[i] is an ear, delete it and visit the previous vertex

    if(isEar) 
    {
      // Triangle (v[i], v[prev[i]], v[next[i]]) is an ear

      // Create the triangle.

      // cout << "triangle: ";
      // cout << setw(6) << lv_ids[prev[i]].pod();
      // cout << setw(6) << lv_ids[i].pod();
      // cout << setw(6) << lv_ids[next[i]].pod();
      // cout << endl;

      ltri_id = kd_triangle::new_triangle(xhost, lv_ids[prev[i]], lv_ids[i], lv_ids[next[i]]);
        
      // Link it to the container.

      /// @issue It would seem obvious to use the container_id
        /// in the fragment for this purpose. But there's no
        /// practical way to keep the fragment container id
        /// referring to the actual container. See issue in
        /// update_container_id.

        lbase.new_link(container_id, ltri_id);

        // Link it to surface as well.

        lbase.new_link(surface_id, ltri_id);

        // Delete vertex v[i] by redirecting next and previous links
        // of neighboring verts past it. Decrement vertex count

        next[prev[i]] = next[i];
        prev[next[i]] = prev[i];
        n--;

        // reset the visited vector.

        for(int lvi = 0; lvi < lsize; lvi++) 
        {
          visited[lvi] = false;
        }

        // Visit the previous vertex next

        i = prev[i];
    }
    else 
    {
      // Current vertex is not an ear; visit the next vertex

      i = next[i];

      if(visited[i])
      {
        post_warning_message("Unable to fully triangulate; giving up.");
        break;
      }
    }
  } // end while n > 3

  if(n == 3)
  {  
    // Create the remaining triangle.

    // cout << "last triangle: ";
    // cout << setw(6) << lv_ids[prev[i]].pod();
    // cout << setw(6) << lv_ids[i].pod();
    // cout << setw(6) << lv_ids[next[i]].pod();
    // cout << endl;

    ltri_id = kd_triangle::new_triangle(xhost, lv_ids[prev[i]], lv_ids[i], lv_ids[next[i]]);
        
    // Link it to the container.

    lbase.new_link(container_id, ltri_id);

    // Link it to surface as well.

    lbase.new_link(surface_id, ltri_id);
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line_fragment::triangulate_ear_clip." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
// ===========================================================
// FRAG_LIST FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
geometry::kd_line_fragment::
append(const scoped_index& xv0_id, 
       const scoped_index& xv1_id, 
       const scoped_index& xsurface_id, 
       const scoped_index& xcontainer_id,
       frag_list& xfrags)
{
  // cout << endl << "Entering kd_line_fragment::append." << endl;
  // cout << "xv0_id: " << xv0_id.pod() << "  xv1_id: " << xv1_id.pod() << endl;
  // cout << "xfrags before: " << endl << xfrags << endl;
  
  // Preconditions:

  // Body:

  if(xfrags.empty() ||
     (xfrags.back().back_pod() != xv0_id.pod()) ||
     (xfrags.back().surface_id != xsurface_id))
  {
    kd_line_fragment lfrag(xcontainer_id);
    xfrags.push_back(lfrag);
    xfrags.back().surface_id = xsurface_id;
    xfrags.back().pt_ids.push_back(xv0_id);
    xfrags.back().pt_ids.push_back(xv1_id);
  }
  else
  {
    xfrags.back().pt_ids.push_back(xv1_id);
    xfrags.back().update_container_id(xcontainer_id);
  }

  // cout << "xfrags after: " << endl << xfrags << endl;

  // Postconditions:

  ensure(!xfrags.empty());
  ensure(xfrags.back().before_back() == xv0_id);
  ensure(xfrags.back().back() == xv1_id);
  
  // Exit:

  // cout << "Leaving kd_line_fragment::append." << endl;
  return;
}

 
void
geometry::kd_line_fragment::
assemble(kd_lattice& xhost, const kd_line_fragment& xfrag_prototype, frag_list& xifrags, frag_list& xofrags)
{
  // cout << endl << "Entering kd_line_fragment::assemble." << endl;
  // cout << "zone: " << xfrag_prototype.container_id.pod() << endl;
  // cout << "frag list: " << endl << xifrags << endl;

  // Preconditions:


  // Body:

  xofrags.clear();

  // Move any fragments that are already closed 
  // directly to the output list.
  // output_fragment increments f if it succeeds,
  // so we only increment if it fails.

  for(frag_itr f = xifrags.begin(); f != xifrags.end();)
  {
    if(!output_fragment(f, xifrags, xofrags))
    {
      ++f;
    }
  }

  // Enter the open input fragments in a frag map.
  
  frag_map lifrag_map;
  
  for(frag_itr f = xifrags.begin(); f != xifrags.end(); ++f)
  {
    lifrag_map.insert(frag_map::value_type(f->front_pod(), f));
    lifrag_map.insert(frag_map::value_type(f->back_pod(), f));
  }

  using ::operator<<;
  
  // cout << "ifrag map: " << endl;
  // cout << lifrag_map << endl;

  // Need a list and map for truncation fragments.

  frag_list ltfrags;

  // Assemble the truncation fragments and input fragments into maximal length fragments.

  assemble_fragments(xhost, xfrag_prototype, xifrags, lifrag_map, ltfrags, xofrags);

  // Postconditions:


  // Exit:

  // cout << endl << "frag list: " << endl << xifrags << endl;

  // cout << "Leaving kd_line_fragment::assemble." << endl;
  return;
}
 
void
geometry::kd_line_fragment::
assemble(kd_lattice& xhost, frag_list& xifrags, frag_list& xofrags)
{
  // cout << endl << "Entering kd_line_fragment::assemble." << endl;
  // cout << "frag list: " << endl << xifrags << endl;

  // Preconditions:


  // Body:

  xofrags.clear();

  // Move any fragments that are already closed 
  // directly to the output list.

  for(frag_itr f = xifrags.begin(); f != xifrags.end(); ++f)
  {
    output_fragment(f, xifrags, xofrags);
  }

  // Enter the open input fragments in a frag map.
  
  frag_map lifrag_map;
  
  for(frag_itr f = xifrags.begin(); f != xifrags.end(); ++f)
  {
    lifrag_map.insert(frag_map::value_type(f->front_pod(), f));
    lifrag_map.insert(frag_map::value_type(f->back_pod(), f));
  }

  using ::operator<<;
  
  // cout << "ifrag map: " << endl;
  // cout << lifrag_map << endl;

  // $$SCRIBBLE: ERROR
  // Phase 4 assembles lines without looking for truncation points
  // to block extension. This is what we want for implicit lines
  // computed from plane-surface intersections. It does respect
  // surface boundaries, so it won't combine lines from different
  // surfaces, e.g. across a truncation line. However, it will
  // combine lines across a self-truncation, and which branches
  // combines will be effectively random. Not clear what to do 
  // about this.

  assemble_fragments_phase_4(xhost, xifrags, lifrag_map, xofrags);

  // Any remaining input fragments can not be closed,
  // but are still part of the output.

  xofrags.splice(xofrags.end(), xifrags);
  
  // Postconditions:


  // Exit:

  // cout << endl << "ifrag list: " << endl << xifrags << endl;
  // cout << endl << "ofrag list: " << endl << xofrags << endl;

  // cout << "Leaving kd_line_fragment::assemble." << endl;
  return;
}
 
void
geometry::kd_line_fragment::
assemble(kd_lattice& xhost, frag_list& xefrags, frag_list& xcfrags, frag_list& xofrags)
{
  // cout << "/////////////////////////////////////////////////////////////////////////////////////////////" << endl;  
  // cout << endl << "Entering kd_line_fragment::assemble." << endl;
  // cout << "edge frag list: " << endl << xefrags << endl;
  // cout << "contents frag list: " << endl << xcfrags << endl;

  // Preconditions:

  // Phase 2 assembly requires marking efrags with invalid surface id.

  require_for_range(frag_itr f=xefrags.begin(), f!=xefrags.end(), ++f, !f->surface_id.is_valid());
  require_for_range(frag_itr f=xcfrags.begin(), f!=xcfrags.end(), ++f, f->surface_id.is_valid());
  
  // Body:

  using ::operator<<; // So frag_map insertion operators are visible.

  xofrags.clear();

  // Phase 0: Move any fragments that are already 
  // closed directly to the output list.

  for(frag_itr f = xefrags.begin(); f != xefrags.end(); ++f)
  {
    output_fragment(f, xefrags, xofrags);
  }

  for(frag_itr f = xcfrags.begin(); f != xcfrags.end(); ++f)
  {
    output_fragment(f, xcfrags, xofrags);
  }

  // cout << endl << "===== Phase 1: Maximally extend contents fragments within themselves: =====" << endl << endl;

  // Enter the open input fragments into a frag map.
  
  frag_map lfrag_map;
  
  for(frag_itr f = xcfrags.begin(); f != xcfrags.end(); ++f)
  {
    lfrag_map.insert(frag_map::value_type(f->front_pod(), f));
    lfrag_map.insert(frag_map::value_type(f->back_pod(), f));
  }

  // cout << "frag map: " << endl;
  // cout << lfrag_map << endl;

  assemble_fragments_phase_1(xhost, xcfrags, lfrag_map, xofrags);

  // cout << endl << "===== Phase 2: Extend contents and edge frags jointly. =====" << endl << endl;
  
  // Phase2: Make reverse copies of the contents fragments and
  // combine fwd cfrags, rev cfrags, and efrags in a single
  // frag list, then assemble the entire set.

  // Make reverse copies.

  frag_list lrev_cfrags(xcfrags);
  for(frag_itr lf = lrev_cfrags.begin(); lf != lrev_cfrags.end(); ++ lf)
  {
    lf->pt_ids.reverse();
  }
  
  // Combine the fwd and rev copies in a single list.

  xcfrags.splice(xcfrags.end(), lrev_cfrags);

  // Combine the efrags with the cfrags;
  // this puts the efrags before all the cfrags.
  // This ensure the polygons, and hence the triangles
  // will all be properly oriented, since we start
  // with the efrags, which are properly oreinted, and
  // grow the fragments mantaining orientation.

  xcfrags.splice(xcfrags.begin(), xefrags);

  // cout << "combined frag list: " << endl << xcfrags << endl;

  // The combined list now contains the cfrags in both directions
  // and the efrags. Make a map containing only a front entry for each
  // frag in the list.

  lfrag_map.clear();
  for(frag_itr f = xcfrags.begin(); f != xcfrags.end(); ++f)
  {
    lfrag_map.insert(frag_map::value_type(f->front_pod(), f));
  }

  // cout << "frag map: " << endl;
  // cout << lfrag_map << endl;

  // Now maximally extend all the cfrags in the forward direction.. 
  
  frag_itr lif = xcfrags.begin();
  while(lif != xcfrags.end())
  {
    // cout << "fragment: " << *lif << endl;

    if(output_fragment(lif, xcfrags, xofrags))
    {
      // Moved closed fragment to output list; move to the next frag.
      // Note that lif is incremented in output_fragment, 
      // so we don't do it here.

      // cout << "moved closed fragment to output list, try another" << endl;
    }
    else if(extend_input_fragment_back_any_surface(xhost, xcfrags, lif, lfrag_map, false))
    {
      // Succeeded, keep going with this input frag.

      // cout << "extended back of input fragment" << endl;
      // cout << "fragment: " << *lif << endl;
      // cout << "frag map: " << endl;
      // cout << lfrag_map << endl;
    }
    else
    {
      // Closed or can't extend further; move to the next.

      // cout << "couldn't extend this input frag any further, moving on" << endl;
        
      ++lif;
    }

  } // end phase 2 while over xcfrags

  // cout << endl << "===== Phase 3: internal boundaries. =====" << endl << endl;
  
  // Phase 3: All the cfrags the were closed to start with or
  // that connected to two edges of the face are now closed. 
  // That leaves the internal boundaries, fragments that are completely
  // disconnected from the edges (completely internal") or that only
  // to the edges at one end ("partially internal").
  // All completely internal boundaries are still in the input
  // as fwd/rev pairs. A partial internal boundary may or may not
  // have extend to a closed fragment, depending on the order
  // the frags occurred it. If not, it is also still in the input
  // as a fwd/rev pair.

  // $$SCRIBBLE: what we need to do is reimplement phase 2 so it
  // correctly picks up all the partial internal boundaries.
  // Instead of immediately outputing a closed fragment we need
  // to check if it can be further extended by an internal
  // boundary. In doing so, we look for extensions that 
  // start at the front of the closed segment and are
  // more inside than its own first segment

  // Hack: just try to patch up. the output list.

  lif = xcfrags.begin();
  while(lif != xcfrags.end())
  {
    // cout << "fragment: " << *lif << endl;

    if(output_fragment(lif, xcfrags, xofrags))
    {
      // Moved closed fragment to output list; move to the next frag.
      // Note that lif is incremented in output_fragment, 
      // so we don't do it here.

      // cout << "moved closed fragment to output list, try another" << endl;
    }
    else if(extend_output_fragment(xhost, xcfrags, lif, lfrag_map, xofrags))
    {
      // Succeeded, lif already incremented.

      // cout << "extended outpt fragment with internal fragment" << endl;
    }
    else if(extend_input_fragment_back_any_surface(xhost, xcfrags, lif, lfrag_map, true))
    {
      // Succeeded, keep going with this input frag.

      // cout << "extended back of input fragment" << endl;
    }
    else
    {
      // Closed or can't extend further; move to the next.

      // cout << "couldn't extend this input frag any further, moving on" << endl;
        
      ++lif;
    }

  } // end phase 3 while over xcfrags

  // cout << endl << "===== Finished. =====" << endl << endl;
  
  // Postconditions:


  // Exit:

  // cout << endl << "efrag list: " << endl << xefrags << endl;
  // cout << endl << "cfrag list: " << endl << xcfrags << endl;
  // cout << endl << "ofrag list: " << endl << xofrags << endl;

  // cout << "Leaving kd_line_fragment::assemble." << endl;
  // cout << "/////////////////////////////////////////////////////////////////////////////////////////////" << endl;
  return;
}


//
// Triangulates the convext polygons xfragments using the centroid method..
//
void 
geometry::kd_line_fragment::
triangulate(kd_lattice& xhost, const frag_list& xfragments, const scoped_index& xcontainer_id)
{
  // cout << endl << "Entering kd_line_fragment::triangulate." << endl;

  // cout << xfragments << endl;
  

  // Preconditions:

  // Body:

  // $$SCRIBBLE: ERROR How do we handle 0-area loops associated
  // with internal boundaries when called from kd_face::triangulate?
  // Test area of triangles? Look for repeated vertices in a fragment?
  // Detect it while assembling fragment and mark the fragment?

  e3_lite lpt, lctr;
  scoped_index lpt_id, lctr_id, lseg1_id, lseg2_id, ltri_id;

  base_space_poset& lbase = xhost.base_space();
  sec_e3& lcoords = xhost.coords();
  lcoords.get_read_write_access();

  id_list::const_iterator j, lv0, lv1, lv_first;
  int lv_ct;
  

  for(frag_list::const_iterator i = xfragments.begin(); i != xfragments.end(); ++i)
  {
    // Count the number items in the polygon.

    size_type lpolygon_size = i->pt_ids.size();

    // cout << "polygon: " << i->pt_ids  << "  size:" << lpolygon_size << endl;
    
    if(i->is_closed() && (lpolygon_size >= 3))
    {
      // Polygon has at least two segments,
      // we can triangulate it.
    
      // Create a centroid for the current polygon.

      lctr_id = xhost.centroids().new_member();

      lctr = 0.0;
      lv_ct = 0;
      j = i->pt_ids.begin();
      
      // First vertex: id, coords.

      lv1 = j;

      lcoords.get_fiber(*lv1, lpt, false);
      lctr += lpt;
      ++lv_ct;
      
      ++j;

      while(j != i->pt_ids.end())
      {
        // First vertex of this segment is
        // second vertex of previous segment.

        lv0 = lv1;
        
        // Second vertex: id, coords.

        lv1 = j;        

        // Accumulate average for centroid,
        // but don't count the last point if it
        // is the same as the first.

        if(*lv1 != i->pt_ids.front())
        {
          lcoords.get_fiber(*lv1, lpt, false);
          lctr += lpt;
          ++lv_ct;
        }        

        // cout << "  " << lv1->internal_pod();
        
        // Create the triangle.

        ltri_id = kd_triangle::new_triangle(xhost, *lv0, *lv1, lctr_id);
        
        // Link it to the container.

        /// @issue It would seem obvious to use the container_id
        /// in the fragment for this purpose. But there's no
        /// practical way to keep the fragment container id
        /// referring to the actual container. See issue in
        /// update_container_id.

        lbase.new_link(xcontainer_id, ltri_id);

        // Link it to surface as well.

        lbase.new_link(i->surface_id, ltri_id);

        // Next.

        ++j;
      } // j != i->pt_ids.end()

      // cout << endl;
      
      // Normalize the center position.

      // cout << "vertex ct: " << lv_ct << endl;

      lctr /= lv_ct;
      lcoords.force_fiber(lctr_id, lctr, false);

    } // end if closed
    else
    {
      // cout << "polygon not closed or size < 3; ignoring it." << endl;
    }
    
  } // end iteration over fragments.

  // Postconditions:

  // Exit:

  // cout << "Leaving kd_line_fragment::triangulate." << endl << endl;
  return;
}

//
// Triangulates the non-convex polygons in xfragments using the ear-clipping method..
//
void 
geometry::kd_line_fragment::
triangulate_non_convex(kd_lattice& xhost, const frag_list& xfrags, const scoped_index& xcontainer_id, int xu, int xv)
{
  // cout << endl << "Entering kd_line_fragment::triangulate_non_convex." << endl;
  // cout << xfrags << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require_for_range(frag_list::const_iterator lf = xfrags.begin(), lf != xfrags.end(), ++lf, lf->is_closed());
  
  // Body:

  base_space_poset& lbase = xhost.base_space();
  scoped_index ltri_id;

  // $$SCRIBBLE: vectors used to make it easy to follow Ericson's example.
  // It would be more efficient if we reimplmented using just lists,
  // better yet, implement a circular list class. Of course, it's
  // an O(n*n) algorithm, so I guess the copies don't matter much.

  vector<e2_lite> v;
  vector<scoped_index> lv_ids;
  vector<int> prev, next, visited;
  
  
  e3_lite lpt_3d;
  e2_lite lpt_2d;

  for(frag_list::const_iterator lf = xfrags.begin(); lf != xfrags.end(); ++lf)
  {
    // cout << "frag: " << *lf << endl;
    
    // void Triangulate(Point v[], int n)
    // {

    // Copy the list to an array while getting coordinates

    v.clear();
    lv_ids.clear();    
    int lsize = 0;

    for(id_list::const_iterator i = lf->pt_ids.begin(); i != lf->pt_ids.end(); ++i)
    {
      xhost.coords().get_fiber(*i, lpt_3d, false);

      lpt_2d[0] = lpt_3d[xu];
      lpt_2d[1] = lpt_3d[xv];
    
      v.push_back(lpt_2d);
      lv_ids.push_back(*i);
      ++lsize;
    }

    --lsize;  // last == first not used below.
    

    // Set up previous and next links to effectively form a circular double-linked vertex list

    prev.clear();
    next.clear();
    visited.clear();
    for (int i = 0; i < lsize; i++) 
    {
      prev.push_back(i - 1);
      next.push_back(i + 1);
      visited.push_back(false);
    }
    prev[0] = lsize - 1;
    next[lsize - 1] = 0;

    // Start at vertex 0 and keep removing vertices 
    // until just a triangle left

    int n = lsize;
    int i = 0;    

    while (n > 3) 
    {
      // cout << "n: " << n;
      // cout << "  vertices: ";
      // cout << setw(6) << lv_ids[prev[i]].pod();
      // cout << setw(6) << lv_ids[i].pod();
      // cout << setw(6) << lv_ids[next[i]].pod();
      // cout << endl;
      
      visited[i] = true;

      // Test if current vertex, v[i], is an ear

      //      int isEar = 1;
      bool isEar = true;

      // An ear must be convex (here counterclockwise)

      // cout << "  Test TriangleIsCCW for vertices: ";
      // cout << setw(6) << lv_ids[prev[i]].pod();
      // cout << setw(6) << lv_ids[i].pod();
      // cout << setw(6) << lv_ids[next[i]].pod();

      if (TriangleIsCCW(v[prev[i]], v[i], v[next[i]])) 
      {
        // Loop over all vertices not part of the tentative ear

        // cout << " result = true" << endl;

        int k = next[next[i]];
        
        do 
        {
          // If vertex k is inside the ear triangle, then this is not an ear

          // cout << "  Test Point In Triangle for point: ";
          // cout << setw(6) << lv_ids[k].pod();
          // cout << "  triangle: ";
          // cout << setw(6) << lv_ids[prev[i]].pod();
          // cout << setw(6) << lv_ids[i].pod();
          // cout << setw(6) << lv_ids[next[i]].pod();

          // If v[i] is a duplicated point in an internal edge;
          // we don't want to consider its duplicate to be
          // inside the triangle and hence make it not an ear.

          bool lsame_point = (lv_ids[k] == lv_ids[prev[i]]) || (lv_ids[k] == lv_ids[i]) || (lv_ids[k] == lv_ids[next[i]]);
          
          if(!lsame_point && TestPointTriangle(v[k], v[prev[i]], v[i], v[next[i]]))
          {
            // isEar = 0;
            isEar = false;
            // cout << "  result = true" << endl;
            break;
          }
          // cout << "  result = false" << endl;
          
          k = next[k];
        } 
        while (k != prev[i]);
      }
      else 
      {
        // The `ear' triangle is clockwise so v[i] is not an ear

        // cout << " result = false" << endl;
        isEar = false;
      }

      // If current vertex v[i] is an ear, delete it and visit the previous vertex

      if(isEar) 
      {
        // Triangle (v[i], v[prev[i]], v[next[i]]) is an ear

        // Create the triangle.

        // cout << "triangle: ";
        // cout << setw(6) << lv_ids[prev[i]].pod();
        // cout << setw(6) << lv_ids[i].pod();
        // cout << setw(6) << lv_ids[next[i]].pod();
        // cout << endl;

        ltri_id = kd_triangle::new_triangle(xhost, lv_ids[prev[i]], lv_ids[i], lv_ids[next[i]]);
        
        // Link it to the container.

        /// @issue It would seem obvious to use the container_id
        /// in the fragment for this purpose. But there's no
        /// practical way to keep the fragment container id
        /// referring to the actual container. See issue in
        /// update_container_id.

        lbase.new_link(xcontainer_id, ltri_id);

        // Link it to surface as well.

        lbase.new_link(lf->surface_id, ltri_id);

        // Delete vertex v[i] by redirecting next and previous links
        // of neighboring verts past it. Decrement vertex count

        next[prev[i]] = next[i];
        prev[next[i]] = prev[i];
        n--;

        // reset the visited vector.

        for(int lvi = 0; lvi < lsize; lvi++) 
        {
          visited[lvi] = false;
        }

        // Visit the previous vertex next

        i = prev[i];
      }
      else 
      {
        // Current vertex is not an ear; visit the next vertex

        i = next[i];

        if(visited[i])
        {
          post_warning_message("Unable to fully triangulate; giving up.");
          break;
        }
      }
    } // end while n > 3

    if(n == 3)
    {  
      // Create the remaining triangle.

      // cout << "last triangle: ";
      // cout << setw(6) << lv_ids[prev[i]].pod();
      // cout << setw(6) << lv_ids[i].pod();
      // cout << setw(6) << lv_ids[next[i]].pod();
      // cout << endl;

      ltri_id = kd_triangle::new_triangle(xhost, lv_ids[prev[i]], lv_ids[i], lv_ids[next[i]]);
        
      // Link it to the container.

      lbase.new_link(xcontainer_id, ltri_id);

      // Link it to surface as well.

      lbase.new_link(lf->surface_id, ltri_id);
    }
    

  } // end for all fragments
  
  //}

  // cout << "Leaving kd_line_fragment::triangulate_non_convex." << endl << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, const kd_line_fragment& xn)
{
  // Preconditions:

  // Body:

  xos << "container_id: " << setw(12) << xn.container_id.pod();
  xos << "  surface_id: " << setw(12) << xn.surface_id.pod();
  xos << "  pt_ids: " << xn.pt_ids;
  
  // Postconditions:

  // Exit:

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const frag_list& xl)
{
  // Preconditions:

  // Body:

  
  if(!xl.empty())
  {
    frag_list::const_iterator i = xl.begin();
    xos << *i;
    ++i;
    while(i != xl.end())
    {
      xos << endl << *i;
      ++i;
    }
  }
  
  // Postconditions:

  // Exit:

  return xos;
}
