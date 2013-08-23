
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
/// Implementation for class d_array_point_locator

#ifndef D_ARRAY_POINT_LOCATOR_IMPL_H
#define D_ARRAY_POINT_LOCATOR_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef D_ARRAY_POINT_LOCATOR_H
#include "d_array_point_locator.h"
#endif

#ifndef D_BIN_POINT_LOCATOR_IMPL_H
#include "d_bin_point_locator.impl.h"
#endif

namespace geometry
{

// ===========================================================
// D_BIN_POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
const typename d_array_point_locator<DC, DB>::box_list_type&
d_array_point_locator<DC, DB>::
box_list(sec_vd_value_type* xpt, size_type xpt_ub) const
{
  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= this->dc());
  require(this->domain_contains(xpt, xpt_ub));

  // Body:

  d_bin_coordinates<DC, DB> lcoord;
  relative_position_pa(xpt, xpt_ub, lcoord);

  const box_list_type& result = _bins[bin_id(lcoord)];

  // Postconditions:

  // Exit:

  return result;
}

template <int DC, int DB>
bool
d_array_point_locator<DC, DB>::
contains_box(d_bounding_box<DC, DB>* xbox) const
{
  bool result = true;

  // Preconditions:

  require(xbox != 0);

  // Body:

  // Xbox has been inserted in this if and only if it has bin inserted in
  // every bin that it overlaps. So all we have to check is one bin;
  // the one containg the lower bound is convenient.

  box_list_type& llist = _bins[bin_id(xbox->lb())];
  typename box_list_type::const_iterator itr = llist.begin();
  while((itr != llist.end()) && (*itr != xbox))
  {
    ++itr;
  }

  result = (itr != llist.end());

  // Postconditions:


  // Exit:

  return result;
}




template <int DC, int DB>
void
d_array_point_locator<DC, DB>::
clear()
{
  // Preconditions:

  // Body:

  for(size_type i=0; i<_bins.ct(); i++)
  {
    _bins[i].clear();
  }

  this->_box_ct = 0;

  // Postconditions:

  ensure(this->is_empty());

  // Exit:

  return;
}

// ===========================================================
// D_ARRAY_POINT_LOCATOR FACET
// ===========================================================

template <int DC, int DB>
d_array_point_locator<DC, DB>::
d_array_point_locator(sec_ed& xcoords, const block<size_type>& xbin_ub, bool xpopulate, size_type xeval_capacity)
    : d_bin_point_locator<DC, DB>::d_bin_point_locator(xcoords)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().df() == DC);
  require(xbin_ub.ct() >= DC);
  require_for_all(i, 0, xbin_ub.ct(), xbin_ub[i] > 0);

  // Body:

  for(int i=0; i<DC; i++)
  {
    this->_bin_ub[i] = xbin_ub[i];
  }

  this->update(xpopulate, xeval_capacity);

  // Postconditions:


  // Exit:

  return;
}

template <int DC, int DB>
d_array_point_locator<DC, DB>::
d_array_point_locator(sec_ed& xcoords, bool xpopulate, size_type xeval_capacity)
    : d_bin_point_locator<DC, DB>::d_bin_point_locator(xcoords)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().df() == DC);

  // Body:

  // Set _bin_ub to the dc()-th root of the number of evaluation members.

  double leval_ct = static_cast<double>(xcoords.schema().evaluation_ct());
  size_type lbin_ub =
    static_cast<size_type>(exp(log(leval_ct)/static_cast<double>(DC)));

  // Make sure ub is at least 1.

  lbin_ub = (lbin_ub > 1) ? lbin_ub : 1;


  for(int i=0; i<DC; i++)
  {
    this->_bin_ub[i] = lbin_ub;
  }

  this->update(xpopulate, xeval_capacity);

  // Postconditions:


  // Exit:

  return;
}


template <int DC, int DB>
d_array_point_locator<DC, DB>::
~d_array_point_locator()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

template <int DC, int DB>
size_type
d_array_point_locator<DC, DB>::
size() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = _bins.ct();

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

template <int DC, int DB>
size_type
d_array_point_locator<DC, DB>::
capacity() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = _bins.ub();

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}


template <int DC, int DB>
void
d_array_point_locator<DC, DB>::
to_stream(ostream& xos) const
{
  // Preconditions:

  // Body:

  xos << "lb =";
  for(int i=0; i<this->dc(); i++)
  {
    xos << " " << this->lb()[i];
  }
  xos << endl;

  xos << "ub =";
  for(int i=0; i<this->dc(); i++)
  {
    xos << " " << this->ub()[i];
  }
  xos << endl;

  xos << "bin ct: " << this->_bins.ct() << endl;
  xos << "bins: " << endl;
  for(size_type i=0; i<this->_bins.ct(); ++i)
  {
    xos << "bin " << i << endl;
    xos << this->_bins[i] << endl;
  }

  // Postconditions:

  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS


template <int DC, int DB>
void
d_array_point_locator<DC, DB>::
update_bins()
{
  // Preconditions:

  require(this->is_empty());

  // Body:

  // Compute the bin size.

  for(int i=0; i<DC; i++)
  {
    this->_bin_size[i] = (this->_ub[i] - this->_lb[i])/this->_bin_ub[i];
  }

  // Compute the reciprocal of the smallest bin size.
  // Used for efficiency in relative_position_pa().

  sec_vd_value_type lcoord_ub = d_bin_coordinates<DC, DB>::ub();
  for(int i=0; i<DC; i++)
  {
    this->_one_over_min_bin_size[i] = 1.0/this->_bin_size[i];
  }

  // Reset the size of the bin array.

  size_type lbin_ct = 1;
  for(int i=0; i<DC; i++)
  {
    lbin_ct *= this->_bin_ub[i];
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

template <int DC, int DB>
size_type
d_array_point_locator<DC, DB>::
bin_id(size_type xi, size_type xj) const
{
  return (xi*this->_bin_ub[1] + xj);
};

template <int DC, int DB>
size_type
d_array_point_locator<DC, DB>::
bin_id(size_type xi, size_type xj, size_type xk) const
{
  return (xi*this->_bin_ub[1] + xj)*this->_bin_ub[2] + xk;
};


// ===========================================================
// POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
bool
d_array_point_locator<DC, DB>::
invariant() const
{
  bool result = true;

  invariance(size() > 0);
  invariance(capacity() > 0);


  return result;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template <int DC, int DB>
ostream&
operator<<(ostream& xos, const d_array_point_locator<DC, DB>& xpl)
{
  // Preconditions:

  // Body:

  xpl.to_stream(xos);

  // Postconditions:

  // Exit:

  return xos;
}

template <int DC, int DB>
ostream&
operator<<(ostream& xos, const slist<const d_bounding_box<DC, DB>*>& xbl)
{
  // Preconditions:

  // Body:

  typedef slist<const d_bounding_box<DC, DB>*> list_type;

  for(typename list_type::const_iterator i = xbl.begin(); i != xbl.end(); ++i)
  {
    xos << **i << endl;
  }

  // Postconditions:

  // Exit:

  return xos;
}
 
} // namespace geometry

#endif // D_ARRAY_POINT_LOCATOR_IMPL_H
