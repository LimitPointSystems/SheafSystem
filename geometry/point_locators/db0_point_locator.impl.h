
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
/// Implementation for class template db0_point_locator

#ifndef DB0_POINT_LOCATOR_IMPL_H
#define DB0_POINT_LOCATOR_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef DB0_POINT_LOCATOR_H
#include "SheafSystem/db0_point_locator.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
#endif

#ifndef BLOCK_H
#include "SheafSystem/block.h"
#endif

#ifndef CHART_POINT_3D_H
#include "SheafSystem/chart_point_3d.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "SheafSystem/error_message.h"
#endif

#ifndef PREORDER_ITERATOR_H
#include "SheafSystem/preorder_iterator.h"
#endif

#ifndef SEC_AT1_SPACE_H
#include "SheafSystem/sec_at1_space.h"
#endif

#ifndef SEC_ED_H
#include "SheafSystem/sec_ed.h"
#endif

#ifndef SEC_REP_DESCRIPTOR_H
#include "SheafSystem/sec_rep_descriptor.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_POSET_H
#include "SheafSystem/section_space_schema_poset.h"
#endif

#ifndef STD_CMATH_H
#include "SheafSystem/std_cmath.h"
#endif

#ifndef STD_IOMANIP_H
#include "SheafSystem/std_iomanip.h"
#endif

#ifndef STD_LIMITS_H
#include "SheafSystem/std_limits.h"
#endif


//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{
  
// ===========================================================
// DB0_POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template<int DC>
db0_point_locator<DC>::
db0_point_locator(sec_ed& xcoords, const block<size_type>& xbin_ub)
    : point_locator(xcoords)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().df() == DC);
  require(xcoords.schema().rep().name() == "vertex_vertex_constant");
  require(xbin_ub.ct() >= DC);
  require_for_all(i, 0, xbin_ub.ct(), xbin_ub[i] > 0);

  // Body:

  _bin_ub.reserve(DC);
  _bin_ub.set_ct(DC);

  _bin_size.reserve(DC);
  _bin_size.set_ct(DC);

  _one_over_min_bin_size.reserve(DC);
  _one_over_min_bin_size.set_ct(DC);

  for(int i=0; i<DC; i++)
  {
    _bin_ub[i] = xbin_ub[i];
  }

  update();

  // Postconditions:


  // Exit:

  return;
}

template<int DC>
db0_point_locator<DC>::
db0_point_locator(sec_ed& xcoords, int xavg_occupancy)
    : point_locator(xcoords)
{
  // Preconditions:

  require(precondition_of(point_locator(xcoords)));
  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().rep().name() == "vertex_vertex_constant");
  require(xavg_occupancy > 0);

  // Body:

  _bin_ub.reserve(DC);
  _bin_ub.set_ct(DC);

  _bin_size.reserve(DC);
  _bin_size.set_ct(DC);

  _one_over_min_bin_size.reserve(DC);
  _one_over_min_bin_size.set_ct(DC);

  // Set _bin_ub to the dc()-th root of the number of disc members.

  double ldisc_ct = static_cast<double>(xcoords.schema().discretization_ct());
  size_type lbin_ub = static_cast<size_type>(exp(log(ldisc_ct/xavg_occupancy)
                      / static_cast<double>(DC)));

  // Make sure ub is at least 1.

  lbin_ub = (lbin_ub > 1) ? lbin_ub : 1;


  for(int i=0; i<DC; i++)
  {
    _bin_ub[i] = lbin_ub;
  }

  update();

  // Postconditions:


  // Exit:

  return;
}

template<int DC>
db0_point_locator<DC>::
~db0_point_locator()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

template<int DC>
const block<size_type>&
db0_point_locator<DC>::
bin_ub() const
{
  // Preconditions:


  // Body:

  const block<size_type>& result = _bin_ub;

  // Postconditions:

  ensure_for_all(i, 0, dc(), result[i] > 0);

  // Exit:

  return result;
}

template<int DC>
const block<sec_vd_value_type>&
db0_point_locator<DC>::
bin_size() const
{

  // Preconditions:


  // Body:

  const block<sec_vd_value_type>& result  = _bin_size;

  // Postconditions:


  // Exit:

  return result;
}


template<int DC>
bool
db0_point_locator<DC>::
is_empty() const
{
  bool result;

  // Preconditions:


  // Body:

  result = true;
  for(int i=0; result && (i<_bins.ct()); ++i)
  {
    result = _bins[i].empty();
  }


  // Postconditions:

  // Exit:

  return result;
}


template<int DC>
void
db0_point_locator<DC>::
relative_position(const sec_vd_value_type xpt[],
                  bin_coord_type xresult[]) const
{
  // Preconditions:

  require(xpt != 0);

  // Body:

  for(int i=0; i<DC; i++)
  {

#ifdef DIAGNOSTIC_OUTPUT
    cout << "xpt: " << xpt[i] << endl;
#endif

    sec_vd_value_type ltmp = (xpt[i] - _lb[i])*_one_over_min_bin_size[i];

    xresult[i] = static_cast<bin_coord_type>(floor(ltmp));

#ifdef DIAGNOSTIC_OUTPUT

    int lprecision = cout.precision();
    cout << "tmp: " << scientific << setprecision(15) << ltmp;
    cout.unsetf(ios_base::floatfield);
    cout << setprecision(lprecision);
    cout  << " result: " << xresult[i] << endl;
#endif

  }

  // Postconditions:

  // Exit:

  return;
}



template<int DC>
void
db0_point_locator<DC>::
clear()
{
  // Preconditions:

  // Body:

  for(int i=0; i<_bins.ct(); ++i)
  {
    _bins[i].clear();
  }

  // Postconditions:

  ensure(is_empty());

  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

template<int DC>
void
db0_point_locator<DC>::
update_bins()
{
  // Preconditions:

  require(is_empty());

  // Body:

  // Compute the bin size.

#ifdef DIAGNOSTIC_OUTPUT

  cout << "bin_ub: ";
  for(int i=0; i<DC; i++)
  {
    cout << setw(6) << _bin_ub[i];
  }
  cout << endl;
#endif

  _bin_diag = 0.0;
  for(int i=0; i<DC; i++)
  {
    _bin_size[i] = (this->_ub[i] - this->_lb[i])/_bin_ub[i];
    _bin_diag += _bin_size[i]*_bin_size[i];
  }
  _bin_diag = sqrt(_bin_diag);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "bin_size: ";
  for(int i=0; i<DC; i++)
  {
    cout << setw(12) << _bin_size[i];
  }
  cout << endl;
#endif

  // Compute the reciprocal of the smallest bin size.
  // Used for efficiency in relative_position_pa().

  for(int i=0; i<DC; i++)
  {
    _one_over_min_bin_size[i] = 1.0/_bin_size[i];
  }


#ifdef DIAGNOSTIC_OUTPUT
  cout << "one_over_bin_size: ";
  for(int i=0; i<DC; i++)
  {
    cout << setw(12) << _one_over_min_bin_size[i];
  }
  cout << endl;
#endif

  // Reset the size of the bin array.

  int lbin_ct = 1;
  for(int i=0; i<DC; i++)
  {
    lbin_ct *= _bin_ub[i];
  }

  _bins.reserve(lbin_ct);
  _bins.set_ct(lbin_ct);

  /// @issue block.reserve doesn't reallocate if capacity is already large enough;
  /// so storage will never shrink.

  /// @todo provide mechanism in block for reclaiming storage.

  // Postconditions:

  // Exit:

  return;
}

template<int DC>
void
db0_point_locator<DC>::
find_closest_bin(const bin_coord_type xpt_pos[], bin_coord_type xbin_pos[])
{
  // Preconditions:


  // Body:

  // Clip the point coords againt the bin bounds.

  for(int i=0; i<DC; ++i)
  {
    bin_coord_type lpt_coord = xpt_pos[i];

    if(lpt_coord < 0)
    {
      xbin_pos[i] = 0;
    }
    else if(lpt_coord >= _bin_ub[i])
    {
      xbin_pos[i] = _bin_ub[i] - 1;
    }
    else
    {
      xbin_pos[i] = lpt_coord;
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  print_coords(cout, xbin_pos, "closest_bin: ");
#endif

  // Postconditions:

  ensure_for_all(i, 0, DC, (0 <= xbin_pos[i]) && (xbin_pos[i] < _bin_ub[i]));

  // Exit:

  return;
}


template<int DC>
void
db0_point_locator<DC>::
initialize_search_region(const sec_vd_value_type xvalue[])
{
#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << endl;
  post_information_message("entering initialize_search_region");
#endif

  // Preconditions:


  // Body:

  // Convert the query point to bin coordinates.

  bin_coord_type lpt_pos[DC];
  relative_position(xvalue, lpt_pos);

#ifdef DIAGNOSTIC_OUTPUT

  print_value(cout, xvalue, "query point: ");
  print_coords(cout, lpt_pos, "rel coords: ");
#endif

  // Find the closest bin.

  bin_coord_type lbin_pos[DC];
  find_closest_bin(lpt_pos, lbin_pos);

  // Set the initial search radius to include the closest bin.

  _search_radius = max_bin_distance(xvalue, lbin_pos);

  // Compute the search region as the box proscribing the search sphere.

  compute_search_region(xvalue);

  // Put all the bins on the search queue.

  initialize_search_q();

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("leaving initialize_search_region");
  cout << endl << endl;
#endif

  return;
}


template<int DC>
void
db0_point_locator<DC>::
expand_search_region(const sec_vd_value_type xvalue[])
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering expand_search_region.");
#endif

  // Preconditions:

  // Body:

  // Save the old search region

  bin_coord_type old_lb[DC];
  bin_coord_type old_ub[DC];

  for(int c=0; c<DC; ++c)
  {
    old_lb[c] = _search_region_lb[c];
    old_ub[c] = _search_region_ub[c];
  }

  // Expand the search sphere and update the search region.

  _search_radius += _bin_diag;

  compute_search_region(xvalue);

  // Put the new bins in the search region on the search queue.

  update_search_q(old_lb, old_ub);


  // Postconditions:

  ensure_for_all(i, 0, DC, (0 <= _search_region_lb[i]) &&
                 (_search_region_lb[i] <= _bin_ub[i]));

  ensure_for_all(i, 0, DC, (0 <= _search_region_ub[i]) &&
                 (_search_region_ub[i] <= _bin_ub[i]));

  ensure_for_all(i, 0, DC, _search_region_lb[i] <= _search_region_ub[i]);


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leavinging expand_search_region.");
#endif

  return;
}


template<int DC>
void
db0_point_locator<DC>::
compute_search_region(const sec_vd_value_type xvalue[])
{
  // Preconditions:


  // Body:

  // Create a search box enclosing search sphere.

  sec_vd_value_type lvalue_lb[DC];
  sec_vd_value_type lvalue_ub[DC];
  for(int i=0; i<DC; ++i)
  {
    lvalue_lb[i] = xvalue[i] - _search_radius;
    lvalue_ub[i] = xvalue[i] + _search_radius;
  }

  relative_position(lvalue_lb, _search_region_lb);
  relative_position(lvalue_ub, _search_region_ub);


#ifdef DIAGNOSTIC_OUTPUT

  print_value(cout, xvalue, "query point: ");
  cout << "search_radius: " << _search_radius << endl;
  print_coords(cout, _search_region_lb, "search region lb: ");
  print_coords(cout, _search_region_ub, "search region ub: ");
#endif

  // _search_region_ub is now the bin coords of the (virtual) bin
  // that actually contains lvalue_ub.
  // We want _ub to be an upper bound, not a max; add 1.

  for(int i=0; i<DC; ++i)
  {
    _search_region_ub[i] += 1;
  }

#ifdef DIAGNOSTIC_OUTPUT
  print_coords(cout, _search_region_lb, "search region lb: ");
  print_coords(cout, _search_region_ub, "search region ub: ");
#endif

  // The search region is the intersection of
  // the search box with the source domain.

  for(int i=0; i<DC; ++i)
  {
    // The lb of the intersection is the max of the lbs

    _search_region_lb[i] = _search_region_lb[i] > 0 ? _search_region_lb[i] : 0;

    // The ub of the intersection is the min of the ubs

    _search_region_ub[i] =
      _search_region_ub[i] < _bin_ub[i] ? _search_region_ub[i] : _bin_ub[i];
  }

#ifdef DIAGNOSTIC_OUTPUT
  print_coords(cout, _search_region_lb, "search region lb: ");
  print_coords(cout, _search_region_ub, "search region ub: ");
#endif

  // Postconditions:

  ensure_for_all(i, 0, DC, (0 <= _search_region_lb[i]) &&
                 (_search_region_lb[i] <= _bin_ub[i]));

  ensure_for_all(i, 0, DC, (0 <= _search_region_ub[i]) &&
                 (_search_region_ub[i] <= _bin_ub[i]));

  ensure_for_all(i, 0, DC, _search_region_lb[i] <= _search_region_ub[i]);


  // Exit:

  return;
}


template<int DC>
sec_vd_value_type
db0_point_locator<DC>::
vertex_distance_sq(const sec_vd_value_type xglobal_coords[],
                   const vertex_type& xvertex_entry)
{
  sec_vd_value_type result;

  // Preconditions:


  // Body:

  // Compute the squared distance from the query point to the vertex.

  result = 0.0;
  for(int i=0; i<DC; ++i)
  {
    sec_vd_dof_type ldif = xglobal_coords[i] - xvertex_entry.coords[i];
    result += ldif*ldif;
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "vertex= " << setw(4) << xvertex_entry.disc_id
  << "  branch= " << setw(4) << xvertex_entry.branch_id
  << "  distance squared= " << result << endl;
#endif

  // Postconditions:

  ensure(result >= 0.0);

  // Exit:

  return result;
}

template<int DC>
void
db0_point_locator<DC>::
find_closest_vertex(const sec_vd_value_type* xvalue,
                    sec_vd_value_type& xclosest_dist_sq,
                    chart_point& xresult)
{
  // Preconditions:


  // Body:

  // Iterate over the bins in the search queue.

  while(!_search_q.empty())
  {
    int i = _search_q.front();
    _search_q.pop();

#ifdef DIAGNOSTIC_OUTPUT

    cout << "searching bin= " << setw(4) << i << endl;
#endif

    find_closest_vertex_in_bin(i, xvalue, xresult, xclosest_dist_sq);
  }

  // Postconditions:

  // Exit:

  return ;
}


template<int DC>
void
db0_point_locator<DC>::
find_closest_vertex_in_bin(int xbin_id,
                           const sec_vd_value_type* xvalue,
                           chart_point& xresult,
                           sec_vd_value_type& xclosest_dist_sq)
{
  // Preconditions:


  // Body:

  // Iterate over the vertices in this bin.

  const vertex_list_type& lvertex_list = _bins[xbin_id];
  typename vertex_list_type::const_iterator iter;

  for(iter = lvertex_list.begin(); iter != lvertex_list.end(); ++iter)
  {
    // Compute the distance from the query point to the vertex.

    sec_vd_value_type lvertex_dist_sq = vertex_distance_sq(xvalue, *iter);

    if(lvertex_dist_sq < xclosest_dist_sq)
    {
      // This vertex is closer than previous one;
      // it becomes the closest vertex.

      xclosest_dist_sq = lvertex_dist_sq;
      xresult.put_chart_id(iter->disc_id);

#ifdef DIAGNOSTIC_OUTPUT

      cout << "vertex= " << iter->disc_id << " is closest" << endl;
#endif

    }

  } // end for vertex list

  // Postconditions:

  // Exit:

  return;
}

template<int DC>
void
db0_point_locator<DC>::
print_bins(std::ostream& xos, const std::string& xmsg) const
{
  // Preconditions:


  // Body:

  using namespace std;

  xos << endl << xmsg << endl;

  xos << "_bins.ub()= " << _bins.ub()
  << " _bins.ct()= " << _bins.ct()
  << endl;

  for(int i=0; i<_bins.ct(); ++i)
  {
    cout << "bin: " << setw(4) << i << " vertices: " << endl;

    const vertex_list_type& lverts = _bins[i];

    for(typename vertex_list_type::const_iterator lv_itr = lverts.begin();
        lv_itr != lverts.end();
        ++lv_itr)
    {
      cout << setw(6) << lv_itr->disc_id
	   << setw(6) << lv_itr->branch_id;
      
      for(int lc=0; lc<DC; ++lc)
      {
	cout << setw(16) << lv_itr->coords[lc];
      }
      cout << endl;
    }
    cout << endl;
  }

  // Postconditions:


  // Exit:

  return;
}

template<int DC>
void
db0_point_locator<DC>::
print_queue(std::ostream& xos, const std::string& xmsg) const
{
  // Preconditions:


  // Body:

  using namespace std;

  xos << endl << xmsg << endl;

  // Type queue has no iterator, must access via front and pop,
  // so we have to copy the queue to print it out.

  queue<int> ltmp(_search_q);

  while(!ltmp.empty())
  {
    xos << setw(6) << ltmp.front();
    ltmp.pop();
  }
  xos << endl;

  // Postconditions:


  // Exit:

  return;
}

template<int DC>
void
db0_point_locator<DC>::
print_value(std::ostream& xos,
            const sec_vd_value_type xvalue[],
            const std::string& xmsg) const
{
  // Preconditions:


  // Body:

  using namespace std;

  xos << xmsg;

  for(int i=0; i<DC; ++i)
  {
    cout << setw(12) << xvalue[i];
  }
  xos << endl;

  // Postconditions:


  // Exit:

  return;
}

template<int DC>
void
db0_point_locator<DC>::
print_coords(std::ostream& xos,
             const bin_coord_type xcoords[],
             const std::string& xmsg) const
{
  // Preconditions:


  // Body:

  using namespace std;

  xos << xmsg;

  for(int i=0; i<DC; ++i)
  {
    cout << setw(6) << xcoords[i];
  }
  xos << endl;

  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template<int DC>
bool
db0_point_locator<DC>::
invariant() const
{
  bool result = true;

  invariance(coordinates().schema().df() == dc());
  invariance(coordinates().schema().rep().name() == "vertex_vertex_constant");


  return result;
}

template<int DC>
void
db0_point_locator<DC>::
update()
{
  // Preconditions:

  require(coordinates().state_is_read_accessible());

  // Body:

  // Update the domain.

  this->update_domain();

  // Update the bin parameters.

  update_bins();

#ifdef DIAGNOSTIC_OUTPUT

  print_bins(cout, "Before initializing bins:");
#endif

  // Iterate over the branches.
  /// @hack the multisection hack.

  vertex_type lvertex_entry;

  sec_vd lbranch;
  preorder_iterator lbranch_itr(coordinates(), "jims", DOWN, NOT_STRICT);
  while(!lbranch_itr.is_done())
  {
    // Get a handle to this branch.

    scoped_index lbranch_id = lbranch_itr.index();
    lbranch.attach_to_state(coordinates().host(), lbranch_id);

    // Sort the vertices into the bins.

    size_type ldisc_ct = lbranch.schema().discretization_ct();

    scoped_index lindex(lbranch.schema().discretization_id_space());
    lvertex_entry.disc_id =
      coordinates().schema().host()->base_space().member_id(false);

    for(pod_index_type ldisc_id=0; ldisc_id<ldisc_ct; ++ldisc_id)
    {
      lindex = ldisc_id;

      lindex >> lvertex_entry.disc_id;

      lvertex_entry.branch_id = lbranch_id;

      // Get the value at vertex

      lbranch.get_fiber(ldisc_id, lvertex_entry.coords,
			DC*sizeof(sec_vd_dof_type));

      // Get its bin coordinates.

      bin_coord_type lrel_pos[DC];
      relative_position(lvertex_entry.coords, lrel_pos);

      // Insert the vertex in the bin.

      int lbin_id = bin_id(lrel_pos);

      _bins[lbin_id].push_front(lvertex_entry);
    }

    // Move on to the next branch.

    lbranch_itr.truncate();
  }

  // Clean up.

  lbranch.detach_from_state();

#ifdef DIAGNOSTIC_OUTPUT

  print_bins(cout, "After initializing bins:");
#endif

  // Postconditions:


  // Exit:

  return;
}

template<int DC>
void
db0_point_locator<DC>::
point_at_value(const sec_vd_value_type* xvalue,
               size_type xvalue_ub,
               chart_point& xresult)
{
  require(xvalue != 0);
  require(xvalue_ub >= dc());
  require(xresult.db() >= db());
  require(coordinates().schema().discretization_ct() > 0);

  // Body:

  // Compute the initial search region and
  // put its bins on the search queue.

  initialize_search_region(xvalue);

  // Initialize the chart id to invalid.
  // If the inversion succeeds, it will be set to valid.

  xresult.invalidate();

  // Initialize distance (squared) to "infinity".

  sec_vd_value_type lclosest_dist_sq = std::numeric_limits<sec_vd_value_type>::max();

  // Keep expanding the search region until we find the closest point
  // or we've searched the entire structure. We should always find a
  // point unless the search structure is empty.

  do
  {
    // Find the closest vertex, if any, within the search region.

    find_closest_vertex(xvalue, lclosest_dist_sq, xresult);

    if(sqrt(lclosest_dist_sq) > _search_radius)
    {
      // Either we haven't found a vertex or we've found one outside
      // the search radius, so there may be a closer one in some
      // bin we haven't searched yet.

      expand_search_region(xvalue);
    }
  }
  while(!_search_q.empty());

  // Since precondition ensures there is at least one vertex,
  // we must have found it by now.

  assertion(xresult.is_valid());

#ifdef DIAGNOSTIC_OUTPUT

  cout << " chart pt: " << xresult << endl;
#endif

  // Postconditions:

  ensure(xresult.is_valid());

  // Exit:

  return;
}

template<int DC>
void
db0_point_locator<DC>::
all_points_at_value(const sec_vd_value_type* xvalue,
                    size_type xvalue_ub,
                    block<chart_point_3d>& xresult)
{
  require(xvalue != 0);
  require(xvalue_ub >= dc());
  require(db() <= 3);

  // Body:

  // There can be only one.

  xresult.set_ct(1);
  point_at_value(xvalue, xvalue_ub, xresult[0]);

  // Postconditions:

  ensure_for_all(i, 0, xresult.ct(), xresult[i].is_valid());


  // Exit:

  return;
}

template<int DC>
void
db0_point_locator<DC>::
branch_points_at_value(const sec_vd_value_type* xvalue,
                       size_type xvalue_ub,
                       block<branch_point_pair>& xresult)
{
  require(xvalue != 0);
  require(xvalue_ub >= dc());
  require(db() <= 3);

  // Body:

  define_old_variable(int old_xresult_ct = xresult.ct());

  // There can be only one.

  xresult.set_ct(1);
  xresult[0].first = coordinates().index();
  point_at_value(xvalue, xvalue_ub, xresult[0].second);

  // Postconditions:

  ensure(xresult.ct() == old_xresult_ct + 1);
  ensure_for_all(i, old_xresult_ct, xresult.ct(),
                 coordinates().host()->contains_member(xresult[i].first, false));
  ensure_for_all(i, old_xresult_ct, xresult.ct(), xresult[i].second.is_valid());


  // Exit:

  return;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace geometry

#endif // DB0_POINT_LOCATOR_IMPL_H
