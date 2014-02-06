
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
/// Implementation for class d_bounding_box

#ifndef D_BOUNDING_BOX_IMPL_H
#define D_BOUNDING_BOX_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef D_BOUNDING_BOX_H
#include "d_bounding_box.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

namespace geometry
{
  
// ============================================================================
// CANONICAL FACET
// ============================================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
d_bounding_box<DC, DB>::
d_bounding_box()
{
  // Bounds initialized by default.

  _member_id.invalidate();

  _dofs_index = 0;
  _dof_ct = 0;
  _evaluator = 0;

  // Postconditions:

  ensure(invariant());
  ensure(lb() == 0);
  ensure(ub() == 0);

  ensure(!member_id().is_valid());

  ensure(evaluator() == 0);
  ensure(dofs_index() == 0);
  ensure(dof_ct() == 0);

}

template <int DC, int DB>
d_bounding_box<DC, DB>::
d_bounding_box(const d_bounding_box<DC, DB>& xbox)
{
  // Preconditions:

  // Body:

  (*this) = xbox;

  // Postconditions:

  ensure(invariant());
  ensure(lb() == xbox.lb());
  ensure(ub() == xbox.ub());
  ensure(member_id() == xbox.member_id());
  ensure(evaluator() == xbox.evaluator());
  ensure(dofs_index() == xbox.dofs_index());
  ensure(dof_ct() == xbox.dof_ct());
}

template <int DC, int DB>
d_bounding_box<DC, DB>&
d_bounding_box<DC, DB>::
operator=(const d_bounding_box<DC, DB>& xbox)
{
  // Preconditions:

  // Body:

  if(this != &xbox)
  {
    _lb = xbox._lb;
    _ub = xbox._ub;
    _member_id = xbox._member_id;
    _evaluator = xbox._evaluator;
    _dofs_index = xbox._dofs_index;
    _dof_ct = xbox._dof_ct;
  }

  // Postconditions:

  ensure(invariant());
  ensure(lb() == xbox.lb());
  ensure(ub() == xbox.ub());
  ensure(member_id()     == xbox.member_id());
  ensure(evaluator()     == xbox.evaluator());
  ensure(dofs_index()    == xbox.dofs_index());
  ensure(dof_ct()        == xbox.dof_ct());

  return *this;
}

template <int DC, int DB>
d_bounding_box<DC, DB>::
~d_bounding_box()
{
  // Nothing to do.
}


template <int DC, int DB>
bool
d_bounding_box<DC, DB>::
invariant() const
{

  bool result = true;

  return result;
}

template <int DC, int DB>
bool
d_bounding_box<DC, DB>::
operator==(const d_bounding_box<DC, DB>& xbox) const
{
  // Preconditions:

  // Body:

  bool result = true;

  if(this != &xbox)
  {
    result = result && (_lb == xbox._lb);
    result = result && (_ub == xbox._ub);
    result = result && (_member_id  == xbox._member_id);
    result = result && (_evaluator  == xbox._evaluator);
    result = result && (_dofs_index == xbox._dofs_index);
    result = result && (_dof_ct     == xbox._dof_ct);
  }

  // Postconditions:

  ensure(invariant());

  return result;
}


// ============================================================================
// D_BOUNDING_BOX FACET
// ============================================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
bool
d_bounding_box<DC, DB>::
contains_point(const d_bin_coordinates<DC, DB>& xpt) const
{
  // Preconditions:

  // Body:

  bool result = ((_lb <= xpt) && (xpt <= _ub));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

template <int DC, int DB>
void
d_bounding_box<DC, DB>::
to_stream(std::ostream& xos) const
{
  // Preconditions:

  // Body:

  using namespace std;

  xos << "d_bounding_box: " << endl
  << "  lower_bounds: " << lb() << endl
  << "  upper_bounds: " << ub() << endl
  << "  member_id:    " << member_id() << endl
  << "  dofs_index:   " << dofs_index() << endl
  << "  dof_ct:       " << dof_ct() << endl;


  // Postconditions:

  ensure(invariant());

}

template <int DC, int DB>
const d_bin_coordinates<DC, DB>&
d_bounding_box<DC, DB>::
lb() const
{
  return _lb;
}

template <int DC, int DB>
void
d_bounding_box<DC, DB>::
put_lb(const d_bin_coordinates<DC, DB>& xlb)
{
  // Preconditions:

  // Body:

  _lb = xlb;

  // Postconditions:

  ensure(lb() == xlb);

  // Exit:

  return;
}

template <int DC, int DB>
const d_bin_coordinates<DC, DB>&
d_bounding_box<DC, DB>::
ub() const
{
  return _ub;
}

template <int DC, int DB>
void
d_bounding_box<DC, DB>::
put_ub(const d_bin_coordinates<DC, DB>& xub)
{
  // Preconditions:

  // Body:

  _ub = xub;

  // Postconditions:

  ensure(ub() == xub);

  // Exit:

  return;
}

template <int DC, int DB>
const scoped_index&
d_bounding_box<DC, DB>::
member_id() const
{
  // Preconditions:

  // Body:

  const scoped_index& result = _member_id;

  // Postconditions:

  return result;
}

template <int DC, int DB>
void
d_bounding_box<DC, DB>::
put_member_id(const scoped_index& xid)
{
  // Preconditions:

  // Body:

  _member_id = xid;

  // Postconditions:

  ensure(member_id() == xid);

}

template <int DC, int DB>
const scoped_index&
d_bounding_box<DC, DB>::
branch_id() const
{
  // Preconditions:

  // Body:

  const scoped_index& result = _branch_id;

  // Postconditions:

  return result;
}

template <int DC, int DB>
void
d_bounding_box<DC, DB>::
put_branch_id(const scoped_index& xid)
{
  // Preconditions:

  // Body:

  _branch_id = xid;

  // Postconditions:

  ensure(branch_id() == xid);

}

template <int DC, int DB>
section_evaluator*
d_bounding_box<DC, DB>::
evaluator() const
{
  // Preconditions:

  // Body:

  section_evaluator* result = _evaluator;

  // Postconditions:

  return result;
}

template <int DC, int DB>
void
d_bounding_box<DC, DB>::
put_evaluator(section_evaluator* xevaluator)
{
  // Preconditions:

  // Body:

  _evaluator = xevaluator;

  // Postconditions:

  ensure(evaluator() == xevaluator);

}

template <int DC, int DB>
size_type
d_bounding_box<DC, DB>::
dofs_index() const
{
  // Preconditions:

  // Body:

  size_type result = _dofs_index;

  // Postconditions:

  return result;
}

template <int DC, int DB>
void
d_bounding_box<DC, DB>::
put_dofs_index(size_type xindex)
{
  // Preconditions:

  // Body:

  _dofs_index = xindex;

  // Postconditions:

  ensure(dofs_index() == xindex);

}

template <int DC, int DB>
size_type
d_bounding_box<DC, DB>::
dof_ct() const
{
  // Preconditions:

  // Body:

  size_type result = _dof_ct;

  // Postconditions:

  return result;
}

template <int DC, int DB>
void
d_bounding_box<DC, DB>::
put_dof_ct(size_type xct)
{
  // Preconditions:

  // Body:

  _dof_ct = xct;

  // Postconditions:

  ensure(dof_ct() == xct);

}

template <int DC, int DB>
void
d_bounding_box<DC, DB>::
size_pa(d_bin_coordinates<DC, DB>& xresult) const
{
  // Preconditions:

  // Body:

  xresult = _ub;
  xresult -= _lb;

  // Postconditions:

  // Exit:

  return;
}


template <int DC, int DB>
int
d_bounding_box<DC, DB>::
dc()
{
  int result;

  // Preconditions:


  // Body:

  result = DC;

  // Postconditions:

  ensure(result == DC);

  // Exit:

  return result;
}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template <int DC, int DB>
std::ostream&
operator<<(std::ostream& xos, const d_bounding_box<DC, DB>& xbox)
{
  xbox.to_stream(xos);
  return xos;
}
 
} // namespace geometry

#endif // D_BOUNDING_BOX_IMPL_H

