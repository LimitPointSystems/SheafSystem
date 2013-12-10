
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

/// @file
/// Implementation for class sec_ed_invertible


#include "sec_ed_invertible.h"

#include "array_cylindrical_point_locator.h"
#include "assert_contract.h"
#include "chart_point.h"
#include "chart_point_3d.h"
#include "d_array_point_locator.h"
#include "db0_point_locator.h"
#include "d_tree_point_locator.h"
#include "d_uniform_point_locator.h"
#include "namespace_poset.h"
#include "poset.h"
#include "poset_path.h"
#include "sec_at0.h"
#include "sec_at1_space.h"
#include "sec_rep_descriptor.h"
#include "sec_rep_space.h"
#include "section_eval_iterator.h"
#include "section_evaluator.h"
#include "sheaf.h"

using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

// ===========================================================
// SEC_ED_INVERTIBLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::sec_ed_invertible::
sec_ed_invertible()
    : _inverter(0)
{

  // Preconditions:

  // Body:



  // Postconditions:

  ensure(invariant());
  ensure(!is_invertible());

}

geometry::sec_ed_invertible::
sec_ed_invertible(const sec_ed& xother)
    : _inverter(0)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));
  ensure(!is_invertible());

  // Exit:

  return;
}

geometry::sec_ed_invertible::
sec_ed_invertible(sec_rep_space* xhost, const scoped_index& xindex)
    : _inverter(0)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xindex);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
  ensure(!is_invertible());

}

geometry::sec_ed_invertible::
sec_ed_invertible(sec_rep_space* xhost, const std::string& xname)
    : _inverter(0)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
  ensure(!is_invertible());
}


geometry::sec_ed_invertible::
sec_ed_invertible(namespace_poset* xnamespace,
                  const poset_path& xpath,
                  bool xauto_access)
    : _inverter(0)
{

  // Preconditions:

  require(precondition_of(attach_to_state(xnamespace, xpath, xauto_access)));

  // Body:

  attach_to_state(xnamespace, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xnamespace, xpath, xauto_access)));
  ensure(!is_invertible());

  // Exit:

  return;
}

///
geometry::sec_ed_invertible&
geometry::sec_ed_invertible::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));
  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

///
geometry::sec_ed_invertible&
geometry::sec_ed_invertible::
operator=(const sec_ed_invertible& xother)
{
  // Preconditions:

  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

///
geometry::sec_ed_invertible&
geometry::sec_ed_invertible::
operator=(const ed& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}

///
geometry::sec_ed_invertible&
geometry::sec_ed_invertible::
operator=(const ed_lite& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}


geometry::sec_ed_invertible::
~sec_ed_invertible()
{
  // Preconditions:

  // Body:

  if(_inverter != 0)
  {
    delete _inverter;
  }

  return;
}

bool
geometry::sec_ed_invertible::
is_uniform() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = schema().rep().name() == "vertex_block_uniform";

  // Postconditions:


  // Exit:

  return result;
}

bool&
geometry::sec_ed_invertible::
use_d_array_point_locator()
{

  // Preconditions:


  // Body:

  static bool result = true;

  // Postconditions:


  // Exit:

  return result;
}

void
geometry::sec_ed_invertible::
initialize_point_locator(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  if(xauto_access)
  {
    get_read_access();
  }

  require(!is_invertible());
  require((1 <= schema(xauto_access).df()) && (schema(xauto_access).df() <= 3));

  // Body:

  if(is_uniform())
  {
    initialize_d_uniform_point_locator(false);
  }
  else if(use_d_array_point_locator())
  {
    initialize_d_array_point_locator(false);
  }
  else
  {
    initialize_d_tree_point_locator(false);
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_invertible());

  // Exit:

  return;
}

void
geometry::sec_ed_invertible::
initialize_d_array_point_locator(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!is_invertible());
  require((1 <= schema().df()) && (schema().df() <= 3));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  switch(schema().df())
  {
  case 1:
    switch(schema().db())
    {
    case 0:
      _inverter = new geometry::db0_point_locator<1>(*this);
      break;
    default:
      _inverter = new geometry::d_array_point_locator<1, 1>(*this);
      break;
    }
    break;
  case 2:
    switch(schema().db())
    {
    case 0:
      _inverter = new geometry::db0_point_locator<2>(*this);
      break;
    default:
      _inverter = new geometry::d_array_point_locator<2, 2>(*this);
      break;
    }
    break;
  case 3:
    switch(schema().db())
    {
    case 0:
      _inverter = new geometry::db0_point_locator<3>(*this);
      break;
    case 2:
      _inverter = new geometry::array_cylindrical_point_locator(*this);
      break;
    default:
      _inverter = new geometry::d_array_point_locator<3, 3>(*this);
      break;
    }

    break;
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_invertible());

  // Exit:

  return;
}

void
geometry::sec_ed_invertible::
initialize_d_array_point_locator(const block<size_type>& xbin_ub, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!is_invertible());
  require((1 <= schema().df()) && (schema().df() <= 3));
  require(xbin_ub.ct() >= schema().df());
  require_for_all(i, 0, xbin_ub.ct(), xbin_ub[i] > 0);

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  switch(schema().df())
  {
  case 1:
    switch(schema().db())
    {
    case 0:
      _inverter = new geometry::db0_point_locator<1>(*this, xbin_ub);
      break;
    default:
      _inverter = new geometry::d_array_point_locator<1, 1>(*this, xbin_ub);
      break;
    }
    break;
  case 2:
    switch(schema().db())
    {
    case 0:
      _inverter = new geometry::db0_point_locator<2>(*this, xbin_ub);
      break;
    default:
      _inverter = new geometry::d_array_point_locator<2, 2>(*this, xbin_ub);
      break;
    }
    break;

  case 3:
    switch(schema().db())
    {
    case 0:
      _inverter = new geometry::db0_point_locator<3>(*this, xbin_ub);
      break;
    default:
      _inverter = new geometry::d_array_point_locator<3, 3>(*this, xbin_ub);
      break;
    }
    break;
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_invertible());

  // Exit:

  return;
}

void
geometry::sec_ed_invertible::
initialize_d_tree_point_locator(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!is_invertible());
  require((1 <= schema().df()) && (schema().df() <= 3));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  switch(schema().df())
  {
  case 1:
    _inverter = new geometry::d_tree_point_locator<1, 1>(*this);
    break;

  case 2:
    _inverter = new geometry::d_tree_point_locator<2, 2>(*this);
    break;

  case 3:
    _inverter = new geometry::d_tree_point_locator<3, 3>(*this);
    break;
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_invertible());

  // Exit:

  return;
}

void
geometry::sec_ed_invertible::
initialize_d_tree_point_locator(size_type xdepth, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!is_invertible());
  require((1 <= schema().df()) && (schema().df() <= 3));
  require(xdepth > 0);

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  switch(schema().df())
  {
  case 1:
    _inverter = new geometry::d_tree_point_locator<1, 1>(*this, xdepth);
    break;

  case 2:
    _inverter = new geometry::d_tree_point_locator<2, 2>(*this, xdepth);
    break;

  case 3:
    _inverter = new geometry::d_tree_point_locator<3, 3>(*this, xdepth);
    break;
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_invertible());

  // Exit:

  return;
}

void
geometry::sec_ed_invertible::
initialize_d_uniform_point_locator(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!is_invertible());
  require((1 <= schema().df()) && (schema().df() <= 3));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  switch(schema().df())
  {
  case 1:
    _inverter = new geometry::d_uniform_point_locator<1, 1>(*this);
    break;

  case 2:
    _inverter = new geometry::d_uniform_point_locator<2, 2>(*this);
    break;

  case 3:
    _inverter = new geometry::d_uniform_point_locator<3, 3>(*this);
    break;
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}

void
geometry::sec_ed_invertible::
update_inversion()
{
  // Preconditions:

  require(is_invertible());

  // Body:

  _inverter->update();

  // Postconditions:


  // Exit:

  return;
}

bool
geometry::sec_ed_invertible::
is_invertible() const
{
  bool result;

  // Preconditions:


  // Body:

  /// @error this implementation of is_invertible can not
  /// detect or deal with the case in which inversion fails.

  result = (_inverter != 0);

  // Postconditions:


  // Exit:

  return result;
}

const geometry::point_locator&
geometry::sec_ed_invertible::
inverter() const
{

  // Preconditions:

  require(is_invertible());

  // Body:

  const geometry::point_locator& result = *_inverter;

  // Postconditions:


  // Exit:

  return result;
}


fiber_bundle::chart_point*
geometry::sec_ed_invertible::
point_at_value(const ed& xr)
{
  chart_point* result;

  // Preconditions:

  require(xr.state_is_read_accessible());
  require(xr.d() == schema().df());

  // Body:

  // Make a new chart point to return as the result.

  result = chart_point::new_chart_point(schema().db());

  point_at_value_pa(xr, *result);

  // Postconditions:

  ensure(invariant());
  ensure(result != 0);

  // Exit:

  return result;
}


void
geometry::sec_ed_invertible::
point_at_value_pa(const ed& xr, chart_point& xresult)
{
  // Preconditions:

  require(xr.state_is_read_accessible());
  require(xr.d() == schema().df());

  // Body:

  const sec_vd_dof_type* lr_dofs =
    reinterpret_cast<const sec_vd_dof_type*>(xr.dof_map().dof_tuple());

  point_at_value_ua(lr_dofs, xr.d(), xresult);

  // Postconditions:

  ensure(unexecutable(xresult.is_valid() ?
                      xresult.chart() contains xvalue at xresult.local_coord() :
                      no chart contains xvalue));

  // Exit:

  return;
}


void
geometry::sec_ed_invertible::
point_at_value_ua(const sec_vd_dof_type* xvalue,
                  size_type xvalue_ub,
                  chart_point& xresult)
{
  // Preconditions:

  require(xvalue != 0);
  require(xvalue_ub >= schema().df());
  require(xresult.db() >= schema().db());
  require(is_invertible());

  // Body:

  _inverter->point_at_value(xvalue, xvalue_ub, xresult);

  // Postconditions:

  ensure(unexecutable(xresult.is_valid() ?
                      xresult.chart() contains xvalue at xresult.local_coord() :
                      no chart contains xvalue));

  // Exit:
}


void
geometry::sec_ed_invertible::
all_points_at_value_ua(const sec_vd_value_type* xvalue,
                       size_type xvalue_ub,
                       block<chart_point_3d>& xresult)
{
  // Preconditions:

  require(xvalue != 0);
  require(xvalue_ub >= schema().df());
  require(schema().db() <= 3);
  require(is_invertible());

  define_old_variable(int old_xresult_ct = xresult.ct());

  // Body:

  _inverter->all_points_at_value(xvalue, xvalue_ub, xresult);

  // Postconditions:

  ensure(xresult.ct() >= old_xresult_ct);
  ensure_for_all(i, old_xresult_ct, xresult.ct(), xresult[i].is_valid());

  // Exit:
}


void
geometry::sec_ed_invertible::
branch_points_at_value_ua(const sec_vd_value_type* xvalue,
                          size_type xvalue_ub,
                          block<branch_point_pair>& xresult)
{
  // Preconditions:

  require(xvalue != 0);
  require(xvalue_ub >= schema().df());
  require(schema().db() <= 3);
  require(is_invertible());

  define_old_variable(int old_xresult_ct = xresult.ct());

  // Body:

  _inverter->branch_points_at_value(xvalue, xvalue_ub, xresult);

  // Postconditions:

  ensure(xresult.ct() >= old_xresult_ct);
  ensure_for_all(i, old_xresult_ct, xresult.ct(),
                 host()->contains_member(xresult[i].first, true));
  ensure_for_all(i, old_xresult_ct, xresult.ct(), xresult[i].second.is_valid());

  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

void
geometry::sec_ed_invertible::
attach_handle_data_members()
{
  // Preconditions:


  // Body:

  sec_ed::attach_handle_data_members();

  if(_inverter != 0)
  {
    delete _inverter;
    _inverter = 0;
  }

  // Postconditions:

  ensure(!is_invertible());

  // Exit:

  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::sec_ed_invertible*
geometry::sec_ed_invertible::
clone() const
{
  // Preconditions:


  // Body:

  sec_ed_invertible *result = new sec_ed_invertible();

  // Postconditions:

  ensure(result != 0);

  return result;

}

bool
geometry::sec_ed_invertible::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of xother.

  bool result = dynamic_cast<const sec_ed_invertible*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
geometry::sec_ed_invertible::
invariant() const
{
  bool result = true;

  // Body:

  if (invariant_check())
  {
    // Must satisfy base class invariant

    invariance(sec_ed::invariant());

    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}
