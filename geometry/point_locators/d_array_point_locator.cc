
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
/// Explicit instantiation for class d_array_point_locator


#include "d_array_point_locator.impl.h"

using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

// ============================================================================
/// @name SPECIALIZATIONS
// ============================================================================
//@{

template <>
void
geometry::d_array_point_locator<1, 1>::
insert_box(d_bounding_box<1, 1>* xbox)
{
  // Preconditions:

  require(xbox != 0);

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type iub = xbox->ub()[0];

  for(size_type i=ilb; i<=iub; ++i)
  {
    _bins[i].push_front(xbox);
  }

  _box_ct++;


  // Postconditions:

  ensure(contains_box(xbox));
  ensure(box_ct() == old_box_ct + 1);

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<2, 2>::
insert_box(d_bounding_box<2, 2>* xbox)
{
  // Preconditions:

  require(xbox != 0);

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      _bins[bin_id(i, j)].push_front(xbox);
    }
  }

  _box_ct++;


  // Postconditions:

  ensure(contains_box(xbox));
  ensure(box_ct() == old_box_ct + 1);

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 1>::
insert_box(d_bounding_box<3, 1>* xbox)
{
  // Preconditions:

  require(xbox != 0);

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type klb = xbox->lb()[2];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];
  size_type kub = xbox->ub()[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
        _bins[bin_id(i, j, k)].push_front(xbox);
      }
    }
  }

  _box_ct++;


  // Postconditions:

  ensure(contains_box(xbox));
  ensure(box_ct() == old_box_ct + 1);

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 2>::
insert_box(d_bounding_box<3, 2>* xbox)
{
  // Preconditions:

  require(xbox != 0);

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type klb = xbox->lb()[2];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];
  size_type kub = xbox->ub()[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
        _bins[bin_id(i, j, k)].push_front(xbox);
      }
    }
  }

  _box_ct++;


  // Postconditions:

  ensure(contains_box(xbox));
  ensure(box_ct() == old_box_ct + 1);

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 3>::
insert_box(d_bounding_box<3, 3>* xbox)
{
  // Preconditions:

  require(xbox != 0);

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type klb = xbox->lb()[2];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];
  size_type kub = xbox->ub()[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
        _bins[bin_id(i, j, k)].push_front(xbox);
      }
    }
  }

  _box_ct++;


  // Postconditions:

  ensure(contains_box(xbox));
  ensure(box_ct() == old_box_ct + 1);

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<1, 1>::
box_list(const section_evaluator& xeval, 
	 sec_vd_value_type* xdofs, 
	 size_type xdofs_ub, 
	 box_list_type& xresult) const
{
  const int DC = 1;
  const int DB = 1;

  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= DC*xeval.dof_ct());
  require(unexecutable("this->domain_contains(xeval, xdofs)"));

  // Body:

  // Get the bounds for this eval member.
  // Must convert from the global coordinate system to search
  // structure-relative coordinates.

  sec_vd_value_type gbl_pos[DC];

  xeval.min(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> llb;
  this->relative_position_pa(gbl_pos, DC, llb);

  xeval.max(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> lub;
  this->relative_position_pa(gbl_pos, DC, lub);

  size_type ilb = llb[0];
  size_type iub = lub[0];

  for(size_type i=ilb; i<=iub; ++i)
  {
    const box_list_type& lbox_list = _bins[i];
    xresult.push_front(lbox_list.begin(), lbox_list.end());
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<2, 2>::
box_list(const section_evaluator& xeval, 
	 sec_vd_value_type* xdofs, 
	 size_type xdofs_ub, 
	 box_list_type& xresult) const
{
  const int DC = 2;
  const int DB = 2;

  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= DC*xeval.dof_ct());
  require(unexecutable("this->domain_contains(xeval, xdofs)"));

  // Body:

  // Get the bounds for this eval member.
  // Must convert from the global coordinate system to search
  // structure-relative coordinates.

  sec_vd_value_type gbl_pos[DC];

  xeval.min(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> llb;
  this->relative_position_pa(gbl_pos, DC, llb);

  xeval.max(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> lub;
  this->relative_position_pa(gbl_pos, DC, lub);

  size_type ilb = llb[0];
  size_type jlb = llb[1];
  size_type iub = lub[0];
  size_type jub = lub[1];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      const box_list_type& lbox_list = _bins[bin_id(i, j)];
      xresult.push_front(lbox_list.begin(), lbox_list.end());
    }
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 1>::
box_list(const section_evaluator& xeval, 
	 sec_vd_value_type* xdofs, 
	 size_type xdofs_ub, 
	 box_list_type& xresult) const
{
  const int DC = 3;
  const int DB = 1;

  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= DC*xeval.dof_ct());
  require(unexecutable("this->domain_contains(xeval, xdofs)"));

  // Body:

  // Get the bounds for this eval member.
  // Must convert from the global coordinate system to search
  // structure-relative coordinates.

  sec_vd_value_type gbl_pos[DC];

  xeval.min(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> llb;
  this->relative_position_pa(gbl_pos, DC, llb);

  xeval.max(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> lub;
  this->relative_position_pa(gbl_pos, DC, lub);

  size_type ilb = llb[0];
  size_type jlb = llb[1];
  size_type klb = llb[2];
  size_type iub = lub[0];
  size_type jub = lub[1];
  size_type kub = lub[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
	const box_list_type& lbox_list = _bins[bin_id(i, j, k)];
	xresult.push_front(lbox_list.begin(), lbox_list.end());
      }
    }
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 2>::
box_list(const section_evaluator& xeval, 
	 sec_vd_value_type* xdofs, 
	 size_type xdofs_ub, 
	 box_list_type& xresult) const
{
  const int DC = 3;
  const int DB = 2;

  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= DC*xeval.dof_ct());
  require(unexecutable("this->domain_contains(xeval, xdofs)"));

  // Body:

  // Get the bounds for this eval member.
  // Must convert from the global coordinate system to search
  // structure-relative coordinates.

  sec_vd_value_type gbl_pos[DC];

  xeval.min(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> llb;
  this->relative_position_pa(gbl_pos, DC, llb);

  xeval.max(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> lub;
  this->relative_position_pa(gbl_pos, DC, lub);

  size_type ilb = llb[0];
  size_type jlb = llb[1];
  size_type klb = llb[2];
  size_type iub = lub[0];
  size_type jub = lub[1];
  size_type kub = lub[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
	const box_list_type& lbox_list = _bins[bin_id(i, j, k)];
	xresult.push_front(lbox_list.begin(), lbox_list.end());
      }
    }
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 3>::
box_list(const section_evaluator& xeval, 
	 sec_vd_value_type* xdofs, 
	 size_type xdofs_ub, 
	 box_list_type& xresult) const
{
  const int DC = 3;
  const int DB = 3;

  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= DC*xeval.dof_ct());
  require(unexecutable("this->domain_contains(xeval, xdofs)"));

  // Body:

  // Get the bounds for this eval member.
  // Must convert from the global coordinate system to search
  // structure-relative coordinates.

  sec_vd_value_type gbl_pos[DC];

  xeval.min(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> llb;
  this->relative_position_pa(gbl_pos, DC, llb);

  xeval.max(xdofs, xdofs_ub, gbl_pos, DC);
  d_bin_coordinates<DC, DB> lub;
  this->relative_position_pa(gbl_pos, DC, lub);


  size_type ilb = llb[0];
  size_type jlb = llb[1];
  size_type klb = llb[2];
  size_type iub = lub[0];
  size_type jub = lub[1];
  size_type kub = lub[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
	const box_list_type& lbox_list = _bins[bin_id(i, j, k)];
	xresult.push_front(lbox_list.begin(), lbox_list.end());
      }
    }
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<1, 1>::
box_list(d_bounding_box<1, 1>* xbox, box_set_type& xresult) const
{
  const int DC = 1;
  const int DB = 1;

  // Preconditions:


  // Body:

  size_type ilb = xbox->lb()[0];
  size_type iub = xbox->ub()[0];

  for(size_type i=ilb; i<=iub; ++i)
  {
    const box_list_type& lbox_list = _bins[i];
    xresult.insert(lbox_list.begin(), lbox_list.end());
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<2, 2>::
box_list(d_bounding_box<2, 2>* xbox, box_set_type& xresult) const
{
  // Preconditions:


  // Body:

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      const box_list_type& lbox_list = _bins[bin_id(i, j)];
      xresult.insert(lbox_list.begin(), lbox_list.end());
    }
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 1>::
box_list(d_bounding_box<3, 1>* xbox, box_set_type& xresult) const
{
  // Preconditions:


  // Body:

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type klb = xbox->lb()[2];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];
  size_type kub = xbox->ub()[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
	const box_list_type& lbox_list = _bins[bin_id(i, j, k)];
	xresult.insert(lbox_list.begin(), lbox_list.end());
      }
    }
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 2>::
box_list(d_bounding_box<3, 2>* xbox, box_set_type& xresult) const
{
  // Preconditions:


  // Body:

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type klb = xbox->lb()[2];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];
  size_type kub = xbox->ub()[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
	const box_list_type& lbox_list = _bins[bin_id(i, j, k)];
	xresult.insert(lbox_list.begin(), lbox_list.end());
      }
    }
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 3>::
box_list(d_bounding_box<3, 3>* xbox, box_set_type& xresult) const
{
  // Preconditions:


  // Body:

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type klb = xbox->lb()[2];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];
  size_type kub = xbox->ub()[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
	const box_list_type& lbox_list = _bins[bin_id(i, j, k)];
	xresult.insert(lbox_list.begin(), lbox_list.end());
      }
    }
  }

  // Postconditions:

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<1, 1>::
remove_box(d_bounding_box<1, 1>* xbox)
{
  // Preconditions:

  require(xbox != 0);
  require(contains_box(xbox));

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type iub = xbox->ub()[0];

  for(size_type i=ilb; i<=iub; ++i)
  {
    _bins[i].remove(xbox);
  }

  _box_ct--;

  // Postconditions:

  ensure(!contains_box(xbox));
  ensure(box_ct() == old_box_ct - 1);

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<2, 2>::
remove_box(d_bounding_box<2, 2>* xbox)
{
  // Preconditions:

  require(xbox != 0);
  require(contains_box(xbox));

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      _bins[bin_id(i, j)].remove(xbox);
    }
  }

  _box_ct--;

  // Postconditions:

  ensure(!contains_box(xbox));
  ensure(box_ct() == old_box_ct - 1);

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 1>::
remove_box(d_bounding_box<3, 1>* xbox)
{
  // Preconditions:

  require(xbox != 0);
  require(contains_box(xbox));

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type klb = xbox->lb()[2];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];
  size_type kub = xbox->ub()[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
        _bins[bin_id(i, j, k)].remove(xbox);
      }
    }
  }

  _box_ct--;

  // Postconditions:

  ensure(!contains_box(xbox));
  ensure(box_ct() == old_box_ct - 1);

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 2>::
remove_box(d_bounding_box<3, 2>* xbox)
{
  // Preconditions:

  require(xbox != 0);
  require(contains_box(xbox));

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type klb = xbox->lb()[2];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];
  size_type kub = xbox->ub()[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
        _bins[bin_id(i, j, k)].remove(xbox);
      }
    }
  }

  _box_ct--;

  // Postconditions:

  ensure(!contains_box(xbox));
  ensure(box_ct() == old_box_ct - 1);

  // Exit:

  return;
}

template <>
void
geometry::d_array_point_locator<3, 3>::
remove_box(d_bounding_box<3, 3>* xbox)
{
  // Preconditions:

  require(xbox != 0);
  require(contains_box(xbox));

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type klb = xbox->lb()[2];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];
  size_type kub = xbox->ub()[2];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      for(size_type k=klb; k<=kub; ++k)
      {
        _bins[bin_id(i, j, k)].remove(xbox);
      }
    }
  }

  _box_ct--;

  // Postconditions:

  ensure(!contains_box(xbox));
  ensure(box_ct() == old_box_ct - 1);

  // Exit:

  return;
}

//==============================================================================
// SPECIALIZATIONS
//==============================================================================

template <>
size_type
d_array_point_locator<1, 1>::
bin_id(const d_bin_coordinates<1, 1>& xcoord) const
{
  return xcoord[0];
};

template <>
size_type
d_array_point_locator<2, 2>::
bin_id(const d_bin_coordinates<2, 2>& xcoord) const
{
  return (xcoord[0]*_bin_ub[1] + xcoord[1]);
};

template <>
size_type
d_array_point_locator<3, 1>::
bin_id(const d_bin_coordinates<3, 1>& xcoord) const
{
  return (xcoord[0]*_bin_ub[1] + xcoord[1])*_bin_ub[2] + xcoord[2];
};

template <>
size_type
d_array_point_locator<3, 2>::
bin_id(const d_bin_coordinates<3, 2>& xcoord) const
{
  return (xcoord[0]*_bin_ub[1] + xcoord[1])*_bin_ub[2] + xcoord[2];
};

template <>
size_type
d_array_point_locator<3, 3>::
bin_id(const d_bin_coordinates<3, 3>& xcoord) const
{
  return (xcoord[0]*_bin_ub[1] + xcoord[1])*_bin_ub[2] + xcoord[2];
};

template <>
size_type
d_array_point_locator<1, 1>::
bin_id(const block<size_type>& xid) const
{
  return xid[0];
};

template <>
size_type
d_array_point_locator<2, 2>::
bin_id(const block<size_type>& xid) const
{
  return (xid[0]*_bin_ub[1] + xid[1]);
};

template <>
size_type
d_array_point_locator<3, 1>::
bin_id(const block<size_type>& xid) const
{
  return (xid[0]*_bin_ub[1] + xid[1])*_bin_ub[2] + xid[2];
};

template <>
size_type
d_array_point_locator<3, 2>::
bin_id(const block<size_type>& xid) const
{
  return (xid[0]*_bin_ub[1] + xid[1])*_bin_ub[2] + xid[2];
};

template <>
size_type
d_array_point_locator<3, 3>::
bin_id(const block<size_type>& xid) const
{
  return (xid[0]*_bin_ub[1] + xid[1])*_bin_ub[2] + xid[2];
};


//@}
