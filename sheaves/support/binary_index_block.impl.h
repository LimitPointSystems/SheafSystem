
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

// Interface for class binary_index_block

#ifndef BINARY_INDEX_BLOCK_IMPL_H
#define BINARY_INDEX_BLOCK_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BINARY_INDEX_BLOCK_H
#include "binary_index_block.h"
#endif

#ifndef BLOCK_IMPL_H
#include "block.impl.h"
#endif

namespace sheaf
{
  
// ===========================================================
// ANY FACET
// ===========================================================

template <typename T>
binary_index_block<T>&
binary_index_block<T>::
operator=(const binary_index_block& xother)
{
  // Preconditions:


  // Body:

  block<T>::operator=(xother);

  // Postconditions:


  // Exit:

  return *this;
};

template <typename T>
bool
binary_index_block<T>::
invariant() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  bool result = block<T>::invariant();

  result = result && ( _i_ub >= 0 );
  result = result && ( _i_ct >= 0 );
  result = result && ( _i_ct <= _i_ub );
  result = result && ((_i_ub > 0) == (this->_base != 0));

  result = result && ( _j_ub >= 0 );
  result = result && ( _j_ct >= 0 );
  result = result && ( _j_ct <= _j_ub );
  result = result && ((_j_ub > 0) == (this->_base != 0));

  // Return:

  return result;
}

// ===========================================================
// BLOCK FACET
// ===========================================================

template <typename T>
void
binary_index_block<T>::
push_back(const binary_index_block& xother)
{
  // Preconditions:

  // Body:

  define_old_variable(int old_ct = this->ct());


  for(int i=0; i<xother.ct(); ++i)
  {
    push_back(xother.item(i));
  }

  // Postconditions:

  ensure(this->ct() == old_ct + xother.ct());
  ensure_for_all(i, 0, xother.ct(), ((*this)[i + old_ct] == xother[i]) );

  // Exit:

  return;
}

// ===========================================================
// BINARY_INDEX_BLOCK FACET
// ===========================================================

template <typename T>
binary_index_block<T>::
binary_index_block(int xi_ub, int xj_ub)
{
  // Preconditions:

  require(xi_ub >= 0);
  require(xj_ub >= 0);

  // Body:

  this->_base = 0;

  _i_ub = xi_ub;
  _j_ub = xj_ub;
  this->_ub = xi_ub*xj_ub;

  _i_ct = 0;
  _j_ct = 0;
  this->_ct = 0;

  reserve(xi_ub, xj_ub);

  // Postconditions:

  ensure(invariant());

  ensure(i_ub( )>= xi_ub);
  ensure(j_ub( )>= xj_ub);
  ensure(this->ub() >= xi_ub*xj_ub);
  ensure((xi_ub*xj_ub > 0) == (this->base() != 0));

  ensure(i_ct() == 0);
  ensure(j_ct() == 0);
  ensure(this->ct() == 0);

  // Exit:

  return;
};

template <typename T>
binary_index_block<T>::
binary_index_block(const binary_index_block& xother)
    : block<T>(xother)
{
  // Preconditions:

  require(precondition_of(block_xother));

  // Body:


  // Postconditions:

  ensure(postcondition_of(block(xother)));

  // Exit:

  return;
};


template <typename T>
binary_index_block<T>::
~binary_index_block()
{}

///
template <typename T>
binary_index_block<T>::
binary_index_block(int xi_ub, int xi_ct, int xj_ub, int xj_ct, const T *xitems)
{

  // Preconditions:

  require(xi_ub >= 0);
  require((0 <= xi_ct) && (xi_ct <= xi_ub));
  require((xi_ct > 0) == (xitems != 0));
  require(xj_ub >= 0);
  require((0 <= xj_ct) && (xj_ct <= xj_ub));
  require((xj_ct > 0) == (xitems != 0));
  require(unexecutable(xitems != 0 implies xitems points to array of length >= xi_ct*xj_ct));

  // Body:

  this->_base = 0;
  this->_ct   = 0;
  this->_ub   = 0;
  _i_ub   = 0;
  _j_ub   = 0;
  reserve(xi_ub, xj_ub);

  for(int i = 0; i < xi_ct*xj_ct; ++i)
  {
    this->_base[i] = xitems[i];
  }
  _i_ct = xi_ct;
  _j_ct = xj_ct;
  this->_ct = _i_ct*_j_ct;

  // Postconditions:

  ensure(invariant());
  ensure(i_ub() >= xi_ub);
  ensure(j_ub() >= xj_ub);
  ensure((xi_ub*xj_ub > 0) == (this->base() != 0));
  ensure(i_ct() == xi_ct);
  ensure(j_ct() == xj_ct);
  ensure(this->ct() == i_ct()*j_ct());
}

///
template <typename T>
int
binary_index_block<T>::
i_ub() const
{
  // Preconditions:

  // Body:

  int result = _i_ub;

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);

  // Return:

  return result;
}


///
template <typename T>
int
binary_index_block<T>::
j_ub() const
{
  // Preconditions:

  // Body:

  int result = _j_ub;

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);

  // Return:

  return result;
}

///
template <typename T>
int
binary_index_block<T>::
i_ct() const
{
  // Preconditions:

  // Body:

  int result = _i_ct;

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);

  // Return:

  return result;
}

///
template <typename T>
int
binary_index_block<T>::
j_ct() const
{
  // Preconditions:

  // Body:

  int result = _j_ct;

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);

  // Return:

  return result;
}

///
template <typename T>
T &
binary_index_block<T>::
item(int xi, int xj)
{

  // Preconditions:

  require(xi >= 0 && xi < i_ub());
  require(xj >= 0 && xj < j_ub());

  // Body:

  int index = xj + xi*j_ub();
  T & result = *(this->_base+index);

  // Postconditions:

  ensure(invariant());

  // Return:

  return result;
}

///
template <typename T>
const T &
binary_index_block<T>::
item(int xi, int xj) const
{

  // Preconditions:

  require(xi >= 0 && xi < i_ub());
  require(xj >= 0 && xj < j_ub());

  // Body:

  int index = xj + xi*j_ub();
  T & result = *(this->_base+index);

  // Postconditions:

  ensure(invariant());

  // Return:

  return result;
}

///
template <typename T>
T *
binary_index_block<T>::
operator [](int xi) const
{

  // Preconditions:

  require(xi >= 0 && xi < i_ub());

  // Body:

  int index = xi*_j_ub;
  T* result = this->_base+index;

  // Postconditions:

  ensure(invariant());

  // Return:

  return result;
}

///
template <typename T>
void
binary_index_block<T>::
force_item(int xi, int xj, const T& xitem)
{

  // Preconditions:

  require(0 <= xi);
  require(0 <= xj);

  // Body:

  if(xi >= _i_ub || xj >= _j_ub)
  {
    ///@todo Fix the logic here.

    int new_i_ub = _i_ub*2 > xi ? _i_ub*2 : xi + 1;
    int new_j_ub = _j_ub*2 > xj ? _j_ub*2 : xj + 1;

    /// @error
    /// we haven't guarded against overflow, nor have we ensured that an
    /// int is the proper thing to use to compute memory sizes.

    reserve(new_i_ub, new_j_ub);
  }

  put_item(xi, xj, xitem);

  // Postconditions:

  ensure(invariant());
  ensure(item(xi, xj)==xitem);
}

///
template <typename T>
void
binary_index_block<T>::
reserve(int xi_ub, int xj_ub)
{

  // Preconditions:

  require(xi_ub >= 0);
  require(xj_ub >= 0);

  // Body:

  define_old_variable(int old_i_ct = _i_ct);
  define_old_variable(int old_i_ub = _i_ub);
  define_old_variable(int old_j_ct = _j_ct);
  define_old_variable(int old_j_ub = _j_ub);

  reserve(xi_ub*xj_ub);

  if(xi_ub > _i_ub)
  {
    _i_ub = xi_ub;
  }

  if(xj_ub > _j_ub)
  {
    _j_ub = xj_ub;
  }

  // Postconditions:

  ensure(invariant());
  ensure(i_ct() == old_i_ct);
  ensure(i_ub() >= old_i_ub);
  ensure(i_ub() >= xi_ub);
  ensure((i_ub() > 0) == (this->base() != 0));
  ensure(j_ct() == old_j_ct);
  ensure(j_ub() >= old_j_ub);
  ensure(j_ub() >= xj_ub);
  ensure((j_ub() > 0) == (this->base() != 0));
  ensure(this->ub() >= xi_ub*xj_ub);
  ensure(this->ub() == i_ub()*j_ub());
}

///
template <typename T>
void
binary_index_block<T>::
set_ct(int xi_ct, int xj_ct)
{

  // Preconditions:

  require(0 <= xi_ct && xi_ct <= i_ub());
  require(0 <= xj_ct && xj_ct <= j_ub());

  // Body:

  _i_ct = xi_ct;
  _j_ct = xj_ct;
  set_ct(xi_ct*xj_ct);

  // Postconditions:

  ensure(i_ct() == xi_ct);
  ensure(j_ct() == xj_ct);
}

///
template <typename T>
void
binary_index_block<T>::
put_item(int xi, int xj, const T& xitem)
{

  // Preconditions:

  require(0 <= xi && xi < i_ub());
  require(0 <= xj && xj < j_ub());

  // Body:

  int index = xj + xi*j_ub();
  *(this->_base+index) = xitem;

  // Postconditions:

  ensure(invariant());
  ensure(item(xi, xj)==xitem);
}


///
template <typename T>
void
binary_index_block<T>::
assign(const T& xitem)
{
  // Preconditions:

  // Body:

  define_old_variable(int old_ct = i_ct()*j_ct());

  for(int i=0; i<i_ct()*j_ct(); i++)
  {
    this->_base[i] = xitem;
  }

  // Postconditions:

  ensure(invariant());
  ensure(i_ct()*j_ct() == old_ct);
  ensure_for_all(i, 0, i_ct()*j_ct(), item(i) == xitem);

}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
template <typename T>
std::ostream&
operator << (std::ostream& xos, const binary_index_block<T>& xblk)
{
  for(int i=0; i<xblk.i_ct(); ++i)
  {
    for(int j=0; j<xblk.j_ct(); ++j)
    {
      xos << "  " << xblk.item(i,j);
    }
    xos << '\n';
  }

  return xos;
}
 
} // namespace sheaf

#endif // ifndef BINARY_INDEX_BLOCK_IMPL_H
