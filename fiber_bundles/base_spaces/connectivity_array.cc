
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class connectivity_array.

#include "connectivity_array.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


///
fiber_bundle::connectivity_array::
connectivity_array(const connectivity_array& xother)
    : ragged_array<scoped_index>(xother)
{
  // Preconditions:

  // Body:

  _types.reserve(row_ct());

  for(index_type i=0; i<row_ct(); i++)
  {
    _types[i] = xother._types[i];
  }

  // Postconditions:

  ensure(invariant());
  ensure(row_ct() == xother.row_ct());
  ensure_for_all(i, 0, row_ct(), col_ct(i) == xother.col_ct(i));
  ensure_for_all(i, 0, value_ct(), values()[i] == xother.values()[i]);
  ensure_for_all(i, 0, row_ct(), type(i) == xother.type(i));

  // Exit
}


///
fiber_bundle::connectivity_array*
fiber_bundle::connectivity_array::
clone() const
{
  connectivity_array* result;

  // Preconditions:

  // Body:

  result = new connectivity_array(*this);

  // Postconditions:

  //ensure(invariant());
  ensure(result->row_ct() == row_ct());
  ensure_for_all(i, 0, row_ct(), result->col_ct(i) == col_ct(i));
  ensure_for_all(i, 0, value_ct(), result->values()[i] == values()[i]);
  ensure_for_all(i, 0, row_ct(), result->type(i) == type(i));

  // Exit

  return result;
}

///
fiber_bundle::connectivity_array::
~connectivity_array()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

///
bool
fiber_bundle::connectivity_array::
invariant() const
{
  // Preconditions:

  // Body:

  invariance(ragged_array<scoped_index>::invariant());

  // Postconditions:

  // Exit

  return true;
}

///
bool
fiber_bundle::connectivity_array::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  require(xother != 0);

  // Body:

  result = dynamic_cast<const connectivity_array*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

///
fiber_bundle::connectivity_array::
connectivity_array(index_type* xcol_cts,
                   index_type xcol_cts_ub)
    : ragged_array<scoped_index>(xcol_cts, xcol_cts_ub)
{
  // Preconditions:

  require(xcol_cts != 0);

  // Body:

  _types.reserve(xcol_cts_ub);

  // Postconditions:

  ensure(invariant());
  ensure(row_ct() == xcol_cts_ub);
  ensure_for_all(i, 0, row_ct(), col_ct(i) == xcol_cts[i]);

  // Exit

  return;
}

///
fiber_bundle::connectivity_array::
connectivity_array(index_type xrow_ct, index_type xvalue_ct)
    : ragged_array<scoped_index>(xrow_ct, xvalue_ct)
{
  // Preconditions:

  require(xrow_ct > 0);
  require(xvalue_ct > 0);

  // Body:

  _types.reserve(xrow_ct);

  // Postconditions:

  ensure(invariant());
  ensure(row_ct() == xrow_ct);
  ensure(value_ct() == xvalue_ct);
  ensure_for_all(i, 0, row_ct()-1, col_ct(i) == (value_ct()/row_ct()));
  ensure(col_ct(row_ct()-1) == ((value_ct()/row_ct()) + (value_ct() % row_ct())));

  // Exit

  return;
}

///
sheaf::scoped_index*
fiber_bundle::connectivity_array::
types() const
{
  scoped_index* result;

  // Preconditions:

  // Body:

  result = _types.base();

  // Postconditions:

  ensure(result !=0);
  ensure(unexecutable(result contains row_ct() entries));

  // Exit

  return result;
}

///
sheaf::scoped_index
fiber_bundle::connectivity_array::
type(index_type xrow_index) const
{
  // Preconditions:

  require(xrow_index < row_ct());

  // Body:

  scoped_index result = _types[xrow_index];

  // Postconditions:

  // Exit

  return result;
}

