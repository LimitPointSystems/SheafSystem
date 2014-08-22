
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
/// Specializationss for class db0_point_locator

#include "ComLimitPoint/geometry/db0_point_locator.impl.h"

#include "ComLimitPoint/sheaf/block.impl.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_poset.h"

using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

// ============================================================================
/// @name SPECIALIZATIONS
// ============================================================================
//@{

template<>
int
geometry::db0_point_locator<1>::
bin_id(const bin_coord_type xcoord[]) const
{
  return (xcoord[0]);
};

template<>
int
geometry::db0_point_locator<2>::
bin_id(const bin_coord_type xcoord[]) const
{
  return (xcoord[0]*_bin_ub[1] + xcoord[1]);
};

template<>
int
geometry::db0_point_locator<3>::
bin_id(const bin_coord_type xcoord[]) const
{
  return (xcoord[0]*_bin_ub[1] + xcoord[1])*_bin_ub[2] + xcoord[2];
};

template<>
void
geometry::db0_point_locator<3>::
print_bins(std::ostream& xos, const std::string& xmsg) const
{
  // Preconditions:


  // Body:

  xos << endl << xmsg << endl;

  xos << "_bins.ub()= " << _bins.ub()
  << " _bins.ct()= " << _bins.ct()
  << endl;

  int l = 0;
  for(int i=0; i<_bin_ub[0]; ++i)
  {
    for(int j=0; j<_bin_ub[1]; ++j)
    {
      for(int k=0; k<_bin_ub[2]; ++k)
      {
        cout << "bin: " << setw(3) << l++;

        cout << setw(3) << i;
        cout << setw(3) << j;
        cout << setw(3) << k;

        cout << setw(16) << i*_bin_size[0] + _lb[0];
        cout << setw(16) << j*_bin_size[1] + _lb[1];
        cout << setw(16) << k*_bin_size[2] + _lb[2];
        cout << endl;

        cout << " vertices: " << endl;

        const vertex_list_type& lverts = _bins[i];

        for(vertex_list_type::const_iterator lv_itr = lverts.begin();
            lv_itr != lverts.end();
            ++lv_itr)
        {
          cout << setw(6) << lv_itr->disc_id
          << setw(6) << lv_itr->branch_id
          << setw(16) << lv_itr->coords[0]
          << setw(16) << lv_itr->coords[1]
          << setw(16) << lv_itr->coords[2]
          << endl;

        }
        cout << endl;
      }
    }
  }

  // Postconditions:


  // Exit:

  return;
}

template<>
fiber_bundle::sec_vd_value_type
geometry::db0_point_locator<1>::
max_bin_distance(const sec_vd_value_type xpt[],
                 const bin_coord_type xbin_pos[]) const
{
  sec_vd_value_type result;

  // Preconditions:


  // Body:

  // vertex 0: i

  sec_vd_value_type x = xbin_pos[0]*_bin_size[0] + _lb[0];
  sec_vd_value_type delx = xpt[0] - x;
  sec_vd_value_type dist = abs(delx);
  result = dist;

  // vertex 1: i+1

  x +=_bin_size[0];
  delx = xpt[0] - x;
  dist = abs(delx);

  result = dist > result ? dist : result;

  // Postconditions:

  ensure(result >= 0.0);

  // Exit:

  return result;
}


template<>
fiber_bundle::sec_vd_value_type
geometry::db0_point_locator<2>::
max_bin_distance(const sec_vd_value_type xpt[],
                 const bin_coord_type xbin_pos[]) const
{
  sec_vd_value_type result;

  // Preconditions:


  // Body:

  sec_vd_value_type del[2][2];
  for(int i=0; i< 2; ++i)
  {
    sec_vd_value_type x = xbin_pos[i]*_bin_size[i] + _lb[i];
    sec_vd_value_type deli0 = xpt[0] - x;
    del[i][0] = deli0*deli0;

    sec_vd_value_type deli1 = deli0 - _bin_size[i];
    del[i][1] = deli1*deli1;
  }

  result = -numeric_limits<sec_vd_value_type>::max();

  for(int i=0; i<2; ++i)
  {
    for(int j=0; j<2; ++j)
    {
      sec_vd_value_type dist = del[0][i] + del[1][j];
      if(dist > result)
        result = dist;
    }
  }

  result = sqrt(result);

  // Postconditions:

  ensure(result >= 0.0);

  // Exit:

  return result;
}


template<>
fiber_bundle::sec_vd_value_type
geometry::db0_point_locator<3>::
max_bin_distance(const sec_vd_value_type xpt[],
                 const bin_coord_type xbin_pos[]) const
{
  sec_vd_value_type result;

  // Preconditions:


  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  cout << "bin: "
  << setw(3) << xbin_pos[0]
  << setw(3) << xbin_pos[1]
  << setw(3) << xbin_pos[2]
  << endl;
#endif

  sec_vd_value_type del[3][2];
  for(int i=0; i< 3; ++i)
  {
    sec_vd_value_type x = xbin_pos[i]*_bin_size[i] + _lb[i];
    sec_vd_value_type deli0 = xpt[i] - x;
    del[i][0] = deli0*deli0;

    sec_vd_value_type deli1 = deli0 - _bin_size[i];
    del[i][1] = deli1*deli1;

#ifdef DIAGNOSTIC_OUTPUT

    cout << "c: " << i
    << " del[c][0]: " << del[i][0]
    << " del[c][1]: " << del[i][1] << endl;
#endif

  }

  result = -numeric_limits<sec_vd_value_type>::max();

  for(int i=0; i<2; ++i)
  {
    for(int j=0; j<2; ++j)
    {
      for(int k=0; k<2; ++k)
      {
        sec_vd_value_type dist = del[0][i] + del[1][j] + del[2][k];
        if(dist > result)
          result = dist;

#ifdef DIAGNOSTIC_OUTPUT

        cout << "corner: " << setw(2) << i << setw(2) << j << setw(2) << k
        << " dist:" << setw(16) << dist
        << " result:" << setw(16) << result
        << endl;
#endif

      }
    }
  }

  result = sqrt(result);

  // Postconditions:

  ensure(result >= 0.0);

  // Exit:

  return result;
}

////////////////////////////////////////////////////////////////////

template<>
void
db0_point_locator<1>::
initialize_search_q()
{
  // Preconditions:


  // Body:

  // Iterate over the bins in the search region.

  for(int i=_search_region_lb[0]; i<_search_region_ub[0]; ++i)
  {
    _search_q.push(i);
  }

#ifdef DIAGNOSTIC_OUTPUT
  print_queue(cout, "search_q: ");
#endif

  // Postconditions:

  // Exit:

  return ;
}

template<>
void
db0_point_locator<2>::
initialize_search_q()
{
  // Preconditions:


  // Body:

  bin_coord_type lbin_coord[2];
  bin_coord_type& i = lbin_coord[0];
  bin_coord_type& j = lbin_coord[1];


  // Iterate over the bins in the search region.

  for(i=_search_region_lb[0]; i<_search_region_ub[0]; ++i)
  {
    for(j=_search_region_lb[1]; j<_search_region_ub[1]; ++j)
    {
      _search_q.push(bin_id(lbin_coord));
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  print_queue(cout, "search_q: ");
#endif

  // Postconditions:

  // Exit:

  return ;
}

template<>
void
db0_point_locator<3>::
initialize_search_q()
{
  // Preconditions:


  // Body:

  bin_coord_type lbin_coord[3];
  bin_coord_type& i = lbin_coord[0];
  bin_coord_type& j = lbin_coord[1];
  bin_coord_type& k = lbin_coord[2];

  // Iterate over the bins in the search region.

  for(i=_search_region_lb[0]; i<_search_region_ub[0]; ++i)
  {
    for(j=_search_region_lb[1]; j<_search_region_ub[1]; ++j)
    {
      for(k=_search_region_lb[2]; k<_search_region_ub[2]; ++k)
      {
        _search_q.push(bin_id(lbin_coord));
      }
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  print_queue(cout, "search_q: ");
#endif

  // Postconditions:

  // Exit:

  return ;
}

template<>
void
db0_point_locator<1>::
update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[])
{
  // Preconditions:

  for(int i=_search_region_lb[0]; i<_search_region_ub[0];)
  {
    bool new_i = (i < xold_lb[0]) || (i >= xold_ub[0]);
    if(new_i)
    {
      // This is a new i; put the bin in the q.

      _search_q.push(bin_id(&i));
      i = i + 1;
    }
    else
    {
      // Skip to the end of the old i range.

      i = xold_ub[0];
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  print_queue(cout, "search_q: ");
#endif

  // Postconditions:

  // Exit:

  return;
}


template<>
void
db0_point_locator<2>::
update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[])
{
  // Preconditions:

  bin_coord_type lbin_coord[2];
  bin_coord_type& i = lbin_coord[0];
  bin_coord_type& j = lbin_coord[1];

  for(j=_search_region_lb[1]; j<_search_region_ub[1]; ++j)
  {
    bool new_j = (j < xold_lb[1]) || (j >= xold_ub[1]);
    for(i=_search_region_lb[0]; i<_search_region_ub[0];)
    {
      bool new_i = (i < xold_lb[0]) || (i >= xold_ub[0]);
      if(new_j || new_i)
      {
        _search_q.push(bin_id(lbin_coord));
        i = i+1;
      }
      else
      {
        i = xold_ub[0];
      }
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  print_queue(cout, "search_q: ");
#endif

  // Postconditions:

  // Exit:

  return;
}

template<>
void
db0_point_locator<3>::
update_search_q(bin_coord_type xold_lb[], bin_coord_type xold_ub[])
{
  // Preconditions:

  bin_coord_type lbin_coord[3];
  bin_coord_type& i = lbin_coord[0];
  bin_coord_type& j = lbin_coord[1];
  bin_coord_type& k = lbin_coord[2];

  for(k=_search_region_lb[2]; k<_search_region_ub[2]; ++k)
  {
    bool new_k = (k < xold_lb[2]) || (k >= xold_ub[2]);
    for(j=_search_region_lb[1]; j<_search_region_ub[1]; ++j)
    {
      bool new_j = (j < xold_lb[1]) || (j >= xold_ub[1]);
      for(i=_search_region_lb[0]; i<_search_region_ub[0];)
      {
        bool new_i = (i < xold_lb[0]) || (i >= xold_ub[0]);
        if(new_k || new_j || new_i)
        {
          _search_q.push(bin_id(lbin_coord));
          i = i+1;
        }
        else
        {
          i = xold_ub[0];
        }
      }
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  print_queue(cout, "search_q: ");
#endif

  // Postconditions:

  // Exit:

  return;
}


//@}


