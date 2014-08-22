
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

// Implementation for class template ragged_array.

#ifndef COM_LIMITPOINT_SHEAF_RAGGED_ARRAY_IMPL_H
#define COM_LIMITPOINT_SHEAF_RAGGED_ARRAY_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_RAGGED_ARRAY_H
#include "ComLimitPoint/sheaf/ragged_array.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ASSERT_CONTRACT_H
#include "ComLimitPoint/sheaf/assert_contract.h"
#endif

namespace sheaf
{
  
// =============================================================================
// RAGGED_ARRAY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
ragged_array<T>::
ragged_array(size_t xct)
{
  // Preconditions:

  // Body:

  // Create one row with col count 0.

  _col_cts.reserve(1);
  _col_cts.push_back(0);

  _row_ptrs.reserve(1);
  _row_ptrs.push_back(0);

  // Reserve space for xct values.

  _values.reserve(xct);
  _values.set_ct(0);

  // Postconditions:

  ensure(row_ct() == 1);
  ensure(col_ct(0) == 0);
  ensure(value_ct() == 0);

  // Exit:

  return;
};

template <typename T>
ragged_array<T>::
ragged_array(const ragged_array& xother)
{
  // Preconditions:

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
};

template <typename T>
ragged_array<T>::
ragged_array(const index_type* xcol_cts,
             index_type xcol_cts_ub)
{
  // Preconditions:

  require(xcol_cts != 0);

  // Body:

  initialize(xcol_cts, xcol_cts_ub);

  // Postconditions:

  ensure(invariant());
  ensure(row_ct() == xcol_cts_ub);
  ensure_for_all(i, 0, row_ct(), col_ct(i) == xcol_cts[i]);

  // Exit

  return;
};

template <typename T>
ragged_array<T>::
ragged_array(index_type xrow_ct, index_type xvalue_ct)
{
  // Preconditions:

  require(xrow_ct > 0);
  require(xvalue_ct > 0);

  // Body:

  _col_cts.reserve(xrow_ct);
  _col_cts.set_ct(xrow_ct);

  _row_ptrs.reserve(xrow_ct);
  _row_ptrs.set_ct(xrow_ct);

  _values.reserve(xvalue_ct);
  _values.set_ct(xvalue_ct);

  // Default column counts are uniform,
  // except possibly for last one.

  index_type lcol_ct = xvalue_ct/xrow_ct;
  _col_cts.assign(lcol_ct);
  _col_cts.back() = lcol_ct + (xvalue_ct % xrow_ct);

  for(index_type i=0; i<xrow_ct; i++)
  {
    _row_ptrs[i] = i*lcol_ct;
  }

  // Postconditions:

  ensure(invariant());
  ensure(row_ct() == xrow_ct);
  ensure(value_ct() == xvalue_ct);
  ensure_for_all(i, 0, row_ct()-1, col_ct(i) == (value_ct()/row_ct()));
  ensure(col_ct(row_ct()-1) == ((value_ct()/row_ct()) + (value_ct() % row_ct())));

  // Exit

  return;
}

template <typename T>
ragged_array<T>::
~ragged_array()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit

  return;
};

template <typename T>
ragged_array<T>&
ragged_array<T>::
operator=(const ragged_array& xother)
{
  // Preconditions:

  // Body:

  initialize(xother._col_cts.base(), xother._col_cts.ct());

  for(index_type i=0; i<value_ct(); i++)
  {
    _values[i] = xother._values[i];
  }

  // Postconditions:

  ensure(invariant());
  ensure(row_ct() == xother.row_ct());
  ensure_for_all(i, 0, row_ct(), col_ct(i) == xother.col_ct(i));
  ensure_for_all(i, 0, value_ct(), values()[i] == xother.values()[i]);

  // Exit:

  return *this;
};

template <typename T>
bool
ragged_array<T>::
operator==(const ragged_array& xother) const
{
  // Preconditions:

  // Body:

  bool result = (row_ct() == xother.row_ct());

  for(index_type i=0; result && i<row_ct(); i++)
  {
    result = (col_ct(i) == xother.col_ct(i));
  }

  for(index_type i=0; result && i<value_ct(); i++)
  {
    result = (_values[i] == xother._values[i]);
  }

  // Postconditions:

  // Exit:

  return result;
};

template <typename T>
typename ragged_array<T>::index_type
ragged_array<T>::
row_ct() const
{
  index_type result;

  // Preconditions:

  // Body:

  result = _col_cts.ct();

  // Postconditions:

  // Exit

  return result;
};

template <typename T>
typename ragged_array<T>::index_type
ragged_array<T>::
col_ct(const index_type xrow_index) const
{
  index_type result;

  // Preconditions:

  require(xrow_index < row_ct());

  // Body:

  result = _col_cts[xrow_index];

  // Postconditions:

  // Exit

  return result;
}

template <typename T>
typename ragged_array<T>::index_type*
ragged_array<T>::
col_cts() const
{
  index_type* result;

  // Preconditions:

  // Body:

  result = _col_cts.base();

  // Postconditions:

  ensure(result != 0);
  ensure(unexecutable(result contains at least row_ct() entries));

  // Exit

  return result;
};

template <typename T>
T*
ragged_array<T>::
values() const
{
  T* result;

  // Preconditions:

  // Body:
  
  result = _values.base();

  // Postconditions:

  //$$ISSUE: result is ==0 when using the default constructor!!!
  //ensure(result != 0);
  ensure(unexecutable(result contains value_ct() entries));

  // Exit

  return result;
};

template <typename T>
typename ragged_array<T>::index_type
ragged_array<T>::
value_ct() const
{
  index_type result;

  // Preconditions:

  // Body:

  result = _values.ct();

  // Postconditions:

  // Exit

  return result;
};

template <typename T>
T*
ragged_array<T>::
row(const index_type xrow_index) const
{
  T* result;

  // Preconditions:

  require(xrow_index < row_ct());

  // Body:

  result = _values.base() + _row_ptrs[xrow_index];

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
};

template <typename T>
T*
ragged_array<T>::
operator[](const index_type xrow_index) const
{
  T* result;

  // Preconditions:

  require(xrow_index < row_ct());

  // Body:

  result = _values.base() + _row_ptrs[xrow_index];

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
};

template <typename T>
void
ragged_array<T>::
reset_rows()
{
  // Preconditions:

  // Body:

  // Initialize the row pointers.

  index_type loffset = 0;
  for(index_type i = 0; i < row_ct(); i++)
  {
    _row_ptrs[i] = loffset;
    loffset += _col_cts[i];
  }

  _values.reserve(loffset);
  _values.set_ct(loffset);

  // Postconditions:

  ensure(value_ct() == sum_col_cts());

  // Exit

  return;
};

template <typename T>
void
ragged_array<T>::
reset_rows(const index_type* xcol_cts, const index_type xcol_cts_ub)
{
  // Preconditions:

  require(xcol_cts != 0);

  // Body:

  initialize(xcol_cts, xcol_cts_ub);

  // Postconditions:

  ensure(invariant());
  ensure(row_ct() == xcol_cts_ub);
  ensure_for_all(i, 0, row_ct(), col_ct(i) == xcol_cts[i]);
  ensure(value_ct() == sum_col_cts());

  // Exit

  return;
};

template <typename T>
typename ragged_array<T>::index_type
ragged_array<T>::
sum_col_cts() const
{
  index_type result = 0;

  // Preconditions:

  // Body:

  result = sum_col_cts(_col_cts.base(), _col_cts.ct());

  // Postconditions:

  // Exit

  return result;
};

template <typename T>
typename ragged_array<T>::index_type
ragged_array<T>::
sum_col_cts(const index_type* xcol_cts, const index_type xcol_cts_ub) const
{
  index_type result = 0;

  // Preconditions:

  require(xcol_cts != 0);

  // Body:

  for(index_type i=0; i<xcol_cts_ub; i++)
  {
    result += xcol_cts[i];
  }

  // Postconditions:

  // Exit

  return result;
};

template <typename T>
void
ragged_array<T>::
initialize_push_back(index_type xrow_ct, index_type xvalue_ct)
{
  // Preconditions:

  // Body:

  // Reserve space for xrow_ct rows.

  _col_cts.reserve(xrow_ct);
  _row_ptrs.reserve(xrow_ct);

  // Create one row with col count 0;
  // becomes back_row().

  _col_cts.set_ct(0);
  _col_cts.push_back(0);

  _row_ptrs.set_ct(0);
  _row_ptrs.push_back(0);

  // Reserve space for xct values.

  _values.reserve(xvalue_ct);
  _values.set_ct(0);

  // Postconditions:

  ensure(back_row() == 0);
  ensure(col_ct(back_row()) == 0);
  ensure(value_ct() == 0);

  // Exit:

  return;
}

template <typename T>
typename ragged_array<T>::index_type
ragged_array<T>::
back_row() const
{
  // Preconditions:

  // Body:

  index_type result = row_ct() - 1;

  // Postconditions:

  ensure(result == (row_ct() - 1));

  // Exit:

  return result;
}

template <typename T>
void
ragged_array<T>::
new_back_row()
{
  // Preconditions:

  // Body:

  define_old_variable(size_t old_value_ct = value_ct());
  define_old_variable(size_t old_col_ct = col_ct(back_row()));
  define_old_variable(index_type old_back_row = back_row());

  _row_ptrs.push_back(_row_ptrs.back() + _col_cts.back());
  _col_cts.push_back(0);

  // Postconditions:

  ensure(back_row() == old_back_row + 1);
  ensure(col_ct(back_row()) == 0);
  ensure(value_ct() == old_value_ct);

  // Exit:

  return;
}

template <typename T>
void
ragged_array<T>::
push_back(const T& xvalue)
{
  // Preconditions:

  // Body:

  define_old_variable(size_t old_value_ct = value_ct());
  define_old_variable(size_t old_col_ct = col_ct(back_row()));
  define_old_variable(index_type old_back_row = back_row());

  _values.push_back(xvalue);
  _col_cts.back()++;

  // Postconditions:

  ensure(back_row() == old_back_row);
  ensure(col_ct(back_row()) == old_col_ct + 1);
  ensure(value_ct() == old_value_ct + 1);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

template <typename T>
void
ragged_array<T>::
initialize(const index_type* xcol_cts,
           index_type xcol_cts_ub)
{
  // Preconditions:

  require(xcol_cts != 0);

  // Body:

  // Allocate column counts and row pointers.

  _col_cts.reserve(xcol_cts_ub);
  _col_cts.set_ct(0);

  _row_ptrs.reserve(xcol_cts_ub);
  _row_ptrs.set_ct(0);

  // Initialize column counts and row pointers
  // while adding up the number of values.

  size_t lvalue_ct = 0;
  for(index_type i = 0; i < xcol_cts_ub; i++)
  {
    _col_cts.push_back(xcol_cts[i]);
    _row_ptrs.push_back(lvalue_ct);
    lvalue_ct += xcol_cts[i];
  }

  // Allocate values.

  _values.reserve(lvalue_ct);
  _values.set_ct(lvalue_ct);

  // Postconditions:

  ensure(invariant());
  ensure(row_ct() == xcol_cts_ub);
  ensure_for_all(i, 0, row_ct(), col_ct(i) == xcol_cts[i]);

  // Exit

  return;
};

// PRIVATE MEMBER FUNCTIONS


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
ragged_array<T>*
ragged_array<T>::
clone() const
{
  ragged_array* result;

  // Preconditions:

  // Body:

  result = new ragged_array(*this);

  // Postconditions:

  ensure(result->row_ct() == row_ct());
  ensure_for_all(i, 0, row_ct(), result->col_ct(i) == col_ct(i));
  ensure_for_all(i, 0, value_ct(), result->values()[i] == values()[i]);

  // Exit

  return result;
};


template <typename T>
bool
ragged_array<T>::
invariant() const
{
  // Preconditions:

  // Body:

  /// @issue values() == 0 when using the default constructor.
  //invariance(values() != 0);
  invariance(col_cts() != 0);
  invariance(sum_col_cts() == value_ct());

  // Postconditions:

  // Exit

  return true;
};

template <typename T>
bool
ragged_array<T>::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  require(xother != 0);

  // Body:

  result = dynamic_cast<const ragged_array<T>*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
};

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template <typename T>
std::ostream&
operator << (std::ostream& xos, const ragged_array<T>& xra)
{
  for(size_type i=0; i<xra.row_ct(); ++i)
  {
    for(size_type j=0; j< xra.col_ct(i); ++j)
    {
      xos << "  " << xra[i][j];
    }
    xos << std::endl;
  }

  return xos;
}

template <typename T>
size_t
deep_size(const ragged_array<T>& xra, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xra) : 0;

  // Add memory associated in member _values.

  result += deep_size(xra._values, false);

  // Add memory associated in member _col_cts.

  result += deep_size(xra._col_cts, false);

  // Add memory associated in member _row_ptrs.

  result += deep_size(xra._row_ptrs, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_RAGGED_ARRAY_IMPL_H






