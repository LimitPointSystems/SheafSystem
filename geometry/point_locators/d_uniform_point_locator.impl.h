
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
/// Implementation for class d_uniform_point_locator

#ifndef COM_LIMITPOINT_GEOMETRY_D_UNIFORM_POINT_LOCATOR_IMPL_H
#define COM_LIMITPOINT_GEOMETRY_D_UNIFORM_POINT_LOCATOR_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_GEOMETRY_D_UNIFORM_POINT_LOCATOR_H
#include "ComLimitPoint/geometry/d_uniform_point_locator.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ASSERT_CONTRACT_H
#include "ComLimitPoint/sheaf/assert_contract.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_CHART_POINT_1D_H
#include "ComLimitPoint/fiber_bundle/chart_point_1d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_CHART_POINT_2D_H
#include "ComLimitPoint/fiber_bundle/chart_point_2d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_CHART_POINT_3D_H
#include "ComLimitPoint/fiber_bundle/chart_point_3d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_AT1_SPACE_H
#include "ComLimitPoint/fiber_bundle/sec_at1_space.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ED_H
#include "ComLimitPoint/fiber_bundle/sec_ed.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_STRUCTURED_BLOCK_1D_H
#include "ComLimitPoint/fiber_bundle/structured_block_1d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_STRUCTURED_BLOCK_2D_H
#include "ComLimitPoint/fiber_bundle/structured_block_2d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_STRUCTURED_BLOCK_3D_H
#include "ComLimitPoint/fiber_bundle/structured_block_3d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_UNIFORM_1D_H
#include "ComLimitPoint/fiber_bundle/uniform_1d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_UNIFORM_2D_H
#include "ComLimitPoint/fiber_bundle/uniform_2d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_UNIFORM_3D_H
#include "ComLimitPoint/fiber_bundle/uniform_3d.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{

// ===========================================================
// D_UNIFORM_POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
d_uniform_point_locator<DC, DB>::
~d_uniform_point_locator()
{
  // Preconditions:

  // Body:

  _block->detach_from_state();
  delete _block;

  delete _block_pt;

  delete _evaluator;


  // Postconditions:

  // Exit:

  return;
}

template <int DC, int DB>
bool
d_uniform_point_locator<DC, DB>::
invariant() const
{
  bool result = true;


  return result;
}


// PROTECTED MEMBER FUNCTIONS

template <int DC, int DB>
sec_vd_value_type
d_uniform_point_locator<DC, DB>::
clip_component(sec_vd_value_type xcomp, sec_vd_value_type xupper_bound)
{
  sec_vd_value_type result = xcomp;

  if(xcomp == xupper_bound)
  {
    // The coordinate to be inverted matches the domain upper bound;
    // make sure it is strictly less than the bound.

    result = xcomp*(1.0 - std::numeric_limits<sec_vd_value_type>::epsilon());
  }

  return result;
}


// ===========================================================
// POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
void
d_uniform_point_locator<DC, DB>::
update()
{
  // Preconditions:

  require(this->coordinates().state_is_read_accessible());

  // Body:

  this->update_domain();

  _dofs = reinterpret_cast<sec_vd_dof_type*>(coordinates().dof_map().dof_tuple());
  _dof_ct = coordinates().dof_map().dof_ct();

  // Postconditions:


  // Exit:

  return;
}

template <int DC, int DB>
void
d_uniform_point_locator<DC, DB>::
point_at_value(const sec_vd_value_type* xvalue,
               size_type xvalue_ub,
               chart_point& xresult)
{
  require(xvalue != 0);
  require(xvalue_ub >= this->dc());
  require(xresult.db() >= this->db());

  // Body:

  // Clip the value against the upper bound to make sure
  // point on boundary is considered inside.
  // Also initialize _block_pt.

  /// @issue does clipping make sense here?
  /// We've already expanded the domain slightly in update_domain(),
  /// why do we need to clip as well?

  for(int i=0; i<DC; ++i)
  {
    _clipped_value[i] = clip_component(xvalue[i], ub()[i]);
  }

  _block_pt->put_local_coords_zero();
  _block_pt->put_chart_id(_block->index());

  _evaluator->coord_at_value(_dofs,
                             _dof_ct,
                             _clipped_value,
                             DC,
                             _block_pt->local_coords(),
                             _block_pt->db());

  // If the local coordinates are in the "standard" domain of the
  // evaluator, then we have a valid chart point.  Otherwise, just
  // return a chard id of "NOT_AN_INDEX".

  if(_evaluator->in_standard_domain(_block_pt->local_coords(), _block_pt->db()))
  {
    // Local coordinates are in the standard domain of the evaluator.
    // Block point is valid; result is refinement.

    _block->refine_point_pa(*_block_pt, xresult);
  }
  else
  {
    // No valid point at the given value.

    xresult.invalidate();
  }

  // Postconditions:

  ensure(unexecutable(xresult.is_valid() ?
                      xresult.chart() contains xvalue at xresult.local_coord() :
                      no chart contains xvalue));


  // Exit:

  return;
}

template <int DC, int DB>
void
d_uniform_point_locator<DC, DB>::
all_points_at_value(const sec_vd_value_type* xvalue,
                    size_type xvalue_ub,
                    block<chart_point_3d>& xresult)
{
  require(xvalue != 0);
  require(xvalue_ub >= this->dc());
  require(this->db() <= 3);

  // Body:

  define_old_variable(int old_xresult_ct = xresult.ct());

  // Clip the value against the upper bound to make sure
  // point on boundary is considered inside.
  // Also initialize _block_pt.

  /// @issue does clipping make sense here?
  /// We've already expanded the domain slightly in update_domain(),
  /// why do we need to clip as well?

  for(int i=0; i<DC; ++i)
  {
    _clipped_value[i] = clip_component(xvalue[i], ub()[i]);
  }

  _block_pt->put_local_coords_zero();
  _block_pt->put_chart_id(_block->index());

  _evaluator->coord_at_value(_dofs,
                             _dof_ct,
                             _clipped_value,
                             DC,
                             _block_pt->local_coords(),
                             _block_pt->db());

  // If the local coordinates are in the "standard" domain of the
  // evaluator, then we have a valid chart point.  Otherwise, just
  // return a chard id of "NOT_AN_INDEX".

  if(_evaluator->in_standard_domain(_block_pt->local_coords(), _block_pt->db()))
  {
    // Local coordinates are in the standard domain of the evaluator.
    // Block point is valid; result is refinement.

    _block->refine_point_pa(*_block_pt, xresult);
  }
  else
  {
    // No valid point at the given value; do nothing
  }

  // Postconditions:

  ensure(xresult.ct() >= old_xresult_ct);
  ensure_for_all(i, old_xresult_ct, xresult.ct(), xresult[i].is_valid());


  // Exit:

  return;
}

template <int DB, int DC>
void
d_uniform_point_locator<DB, DC>::
branch_points_at_value(const sec_vd_value_type* xvalue,
                       size_type xvalue_ub,
                       block<branch_point_pair>& xresult)
{
  require(xvalue != 0);
  require(xvalue_ub >= this->dc());
  require(this->dc() <= 3);

  // Body:

  define_old_variable(int old_xresult_ct = xresult.ct());

  branch_point_pair lbranch_pt;
  scoped_index& lbranch_id = lbranch_pt.first;
  chart_point_3d& lpt = lbranch_pt.second;

  lbranch_id = coordinates().index();
  point_at_value(xvalue, xvalue_ub, lpt);

  xresult.push_back(lbranch_pt);

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

#endif // COM_LIMITPOINT_GEOMETRY_D_UNIFORM_POINT_LOCATOR_IMPL_H
