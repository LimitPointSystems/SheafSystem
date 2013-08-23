
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
/// Implementation for class point_locator


#include "point_locator.h"

#include "assert_contract.h"
#include "chart_point_3d.h"
#include "error_message.h"
#include "preorder_iterator.h"
#include "sec_at1_space.h"
#include "sec_ed.h"
#include "std_iostream.h"

using namespace geometry; // Workaround for MS C++ bug.
using namespace fiber_bundle::sec_vd_algebra;

//#define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// CANONICAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::point_locator::
invariant() const
{
  bool result = true;

  invariance(dc() == coordinates().schema().df());

  return result;
}


geometry::point_locator::
~point_locator()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


// ===========================================================
// POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_ed&
geometry::point_locator::
coordinates() const
{
  // Preconditions:


  // Body:

  sec_ed& result = _coordinates;

  // Postconditions:


  // Exit:

  return result;
}

const sheaf::block<fiber_bundle::sec_vd_value_type>&
geometry::point_locator::
lb() const
{
  // Preconditions:


  // Body:

  const block<sec_vd_value_type>& result = _lb;

  // Postconditions:

  // Exit:

  return result;
}


const sheaf::block<fiber_bundle::sec_vd_value_type>&
geometry::point_locator::
ub() const
{
  // Preconditions:


  // Body:

  const block<sec_vd_value_type>& result = _ub;

  // Postconditions:

  // Exit:

  return result;
}

int
geometry::point_locator::
dc() const
{
  int result;

  // Preconditions:

  // Body:

  result = _dc;

  // Postconditions:


  // Exit:

  return result;
}

int
geometry::point_locator::
db() const
{
  int result;

  // Preconditions:

  // Body:

  result = _db;

  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::point_locator::
domain_contains(sec_vd_value_type* xpt, size_type xpt_ub) const
{
  bool result = true;

  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= dc());

  // Body:

  for(int i=0; i<dc(); i++)
  {
    result = result && ((_lb[i] <= xpt[i]) && (xpt[i] <= _ub[i]));
  }

  // Postconditions:

  ensure_for_all(i, 0, dc(),
                 result ? ((lb()[i] <= xpt[i]) && (xpt[i] <= ub()[i])) : true);

  // Exit:

  return result;
}


void
geometry::point_locator::
update()
{
  // Preconditions:

  require(coordinates().state_is_read_accessible());

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
geometry::point_locator::
point_at_value(const sec_vd_value_type* xvalue,
               size_type xvalue_ub,
               chart_point& xresult)
{
  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
geometry::point_locator::
all_points_at_value(const sec_vd_value_type* xvalue,
                    size_type xvalue_ub,
                    block<chart_point_3d>& xresult)
{
  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure_for_all(i, 0, xresult.ct(), xresult[i].is_valid());

  // Exit:

  return;
}

void
geometry::point_locator::
branch_points_at_value(const sec_vd_value_type* xvalue,
                       size_type xvalue_ub,
                       block<branch_point_pair>& xresult)
{
  // Preconditions:


  // Body:

  define_old_variable(int old_xresult_ct = xresult.ct());

  is_abstract();

  // Postconditions:

  ensure(xresult.ct() >= old_xresult_ct);
  ensure_for_all(i, old_xresult_ct, xresult.ct(),
                 coordinates().host()->contains_member(xresult[i].first, false));
  ensure_for_all(i, old_xresult_ct, xresult.ct(), xresult[i].second.is_valid());

  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

geometry::point_locator::
point_locator()
    : _coordinates(*(new sec_ed())) // Should never be called.
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;

}


geometry::point_locator::
point_locator(sec_ed& xcoords)
    : _coordinates(xcoords)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().db() <= xcoords.schema().df());

  // Body:

  // Set the dimension.

  _dc = coordinates().schema().df();
  _db = coordinates().schema().db();

  _lb.reserve(_dc);
  _lb.set_ct(_dc);
  _lb.assign(numeric_limits<sec_vd_value_type>::max());


  _ub.reserve(_dc);
  _ub.set_ct(_dc);
  _ub.assign(-numeric_limits<sec_vd_value_type>::max());

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::sec_vd_value_type
geometry::point_locator::
slightly_greater_than(sec_vd_value_type x)
{
  sec_vd_value_type result;

  // Preconditions:


  // Body:

  sec_vd_value_type a_little =
    static_cast<sec_vd_value_type>(10.0)*numeric_limits<sec_vd_value_type>::epsilon();

  if(x == static_cast<sec_vd_value_type>(0.0))
  {
    result = a_little;
  }
  else if(x < static_cast<sec_vd_value_type>(0.0))
  {
    result = x*(static_cast<sec_vd_value_type>(1.0) - a_little);
  }
  else
  {
    result = x*(static_cast<sec_vd_value_type>(1.0) + a_little);
  }

  // Postconditions:

  ensure(result > x);

  // Exit:

  return result;
}

fiber_bundle::sec_vd_value_type
geometry::point_locator::
slightly_less_than(sec_vd_value_type x)
{
  sec_vd_value_type result;

  // Preconditions:


  // Body:

  sec_vd_value_type a_little =
    static_cast<sec_vd_value_type>(10.0)*numeric_limits<sec_vd_value_type>::epsilon();

  if(x == static_cast<sec_vd_value_type>(0.0))
  {
    result = -a_little;
  }
  else if(x < static_cast<sec_vd_value_type>(0.0))
  {
    result = x*(static_cast<sec_vd_value_type>(1.0) + a_little);
  }
  else
  {
    result = x*(static_cast<sec_vd_value_type>(1.0) - a_little);
  }

  // Postconditions:

  ensure(result < x);

  // Exit:

  return result;
}

void
geometry::point_locator::
update_domain()
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("entering update_domain");
#endif

  // Preconditions:

  require(coordinates().state_is_read_accessible());

  // Body:

  // Get the minimum and maximum values of the coordinates.

  block<sec_vd_value_type> llb(_lb);
  block<sec_vd_value_type> lub(_ub);

  /// @hack the multisection hack.
  /// Iterate over the branches.

  sec_vd lbranch;
  preorder_iterator lbranch_itr(_coordinates, "jims", DOWN, NOT_STRICT);
  while(!lbranch_itr.is_done())
  {
    lbranch.attach_to_state(_coordinates.host(), lbranch_itr.index());

    //lbranch.extrema_pa(llb.base(), llb.ub(), lub.base(), lub.ub());
    extrema(lbranch, llb.base(), llb.ub(), lub.base(), lub.ub());

    lbranch.detach_from_state();

    for(int i=0; i<_dc; ++i)
    {
      if(llb[i] < _lb[i])
      {
        _lb[i] = llb[i];
      }

      if(lub[i] > _ub[i])
      {
        _ub[i] = lub[i];
      }
    }

    // Move on to the next branch.

    lbranch_itr.truncate();
  }

  // Ensure that domain strictly contains the data bounds.
  // This avoids numerical precision problems near the boundaries.

  for(int i=0; i<_dc; ++i)
  {
    _lb[i] = slightly_less_than(_lb[i]);
    _ub[i] = slightly_greater_than(_ub[i]);
  }


#ifdef DIAGNOSTIC_OUTPUT
  cout << "_lb: " << _lb << endl;
  cout << "_ub: " << _ub << endl;
  post_information_message("leaving update_domain");
#endif

  // Postconditions:

  // Exit:

  return;
}


// PRIVATE MEMBER FUNCTIONS

geometry::point_locator::
point_locator(const point_locator& xother)
    : _coordinates(xother._coordinates)
{
  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:


  // Exit:

  return;
}

geometry::point_locator&
geometry::point_locator::
operator=(const point_locator& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:


  // Exit:

  return *this;
}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
