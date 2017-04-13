
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

// Implementation for class template AUTO_BLOCK.

#ifndef AUTO_BLOCK_IMPL_H
#define AUTO_BLOCK_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef AUTO_BLOCK_H
#include "SheafSystem/auto_block.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
#endif

#ifndef DEEP_SIZE_H
#include "SheafSystem/deep_size.h"
#endif

#ifndef INDEX_TRAITS_H
#include "SheafSystem/index_traits.h"
#endif

namespace sheaf
{
  
// ===========================================================
// UN_BLOCK_INITIALIZATION_POLICY
// ===========================================================

///
template <typename T>
void
un_block_initialization_policy<T>::
initialize(T* xbegin, T* xend)
{
  // Do nothing.
}

///
template <typename T>
void
un_block_initialization_policy<T>::
initialize(T& xvalue)
{
  // Do nothing.
}

// ===========================================================
// INVALID_BLOCK_INITIALIZATION_POLICY
// ===========================================================

///
template <typename T>
void
invalid_block_initialization_policy<T>::
initialize(T* xbegin, T* xend)
{
  for(T* i=xbegin; i<xend; ++i)
  {
    *i = index_traits<T>::invalid();
  }
}

///
template <typename T>
void
invalid_block_initialization_policy<T>::
initialize(T& xvalue)
{
  xvalue = index_traits<T>::invalid();
}

// ===========================================================
// ZERO_BLOCK_INITIALIZATION_POLICY
// ===========================================================

///
template <typename T>
void
zero_block_initialization_policy<T>::
initialize(T* xbegin, T* xend)
{
  for(T* i=xbegin; i<xend; ++i)
  {
    *i = 0;
  }
}

///
template <typename T>
void
zero_block_initialization_policy<T>::
initialize(T& xvalue)
{
  xvalue = 0;
}



///
template <typename T, typename S>
T *
auto_block<T, S>::
base() const
{
  // Preconditions:

  // Body:

  pointer_type result = _base;

  // Postconditions:

  ensure(invariant());
  ensure((result != 0) == (ub() > 0));

  // Return:

  return result;
}

///
template <typename T, typename S>
typename auto_block<T, S>::size_type
auto_block<T, S>::
ct() const
{
  // Preconditions:

  // Body:

  size_type result = _ct;

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);

  // Return:

  return result;
}

///
template <typename T, typename S>
bool
auto_block<T, S>::
invariant() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  bool result = true;

  result = result && ( _ub >= 0 );
  result = result && ( _ct >= 0 );
  result = result && ( _ct <= _ub );
  result = result && ((_ub > 0) == (_base != 0));

  // Return:

  return result;
}

///
template <typename T, typename S>
T &
auto_block<T, S>::
item(index_type xindex) const
{

  // Preconditions:

  require(xindex >= 0 && xindex < ub());

  // Body:

  T & result = *(_base+xindex);

  // Postconditions:

  ensure(invariant());

  // Return:

  return result;
}

///
template <typename T, typename S>
T &
auto_block<T, S>::
operator [](index_type xindex) const
{

  // Preconditions:

  require(xindex >= 0 && xindex < ub());

  // Body:

  T & result = *(_base+xindex);

  // Postconditions:

  ensure(invariant());

  // Return:

  return result;
}

///
template <typename T, typename S>
typename auto_block<T, S>::index_type
auto_block<T, S>::
ub() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Return:

  return _ub;
}


///
template <typename T, typename S>
auto_block<T, S>::
auto_block(index_type xub)
{

  // Preconditions:

  require(xub >= 0);

  // Body:

  _base = 0;
  _ct   = 0;
  _ub   = 0;
  reserve(xub);

  // Postconditions:

  ensure(invariant());
  ensure(ub() >= xub);
  ensure((xub > 0) == (base() != 0));
  ensure(ct() == 0);
}

///
template <typename T, typename S>
auto_block<T, S>::
auto_block(index_type xub, size_type xct, const T *xitems)
{

  // Preconditions:

  require(xub >= 0);
  require((0 <= xct) && (xct <= xub));
  require((xct > 0) == (xitems != 0));
  require(unexecutable("xitems != 0 implies xitems points to array of length >= xct"));

  // Body:

  _base = 0;
  _ct   = 0;
  _ub   = 0;
  reserve(xub);

  for(index_type i = 0; i < xct; ++i)
  {
    _base[i] = xitems[i];
  }
  _ct = xct;

  // Postconditions:

  ensure(invariant());
  ensure(ub() >= xub);
  ensure((xub > 0) == (base() != 0));
  ensure(ct() == xct);
  // Unexecutable because would require T::operator==
  ensure_for_all(i, 0, ct(), unexecutable(item(i) == xitems[i]));
}

///
template <typename T, typename S>
auto_block<T, S>::
auto_block(const auto_block& xother)
{

  // Preconditions:

  // Body:

  _base = 0;
  _ct   = 0;
  _ub   = 0;

  *this = xother;

  // Postconditions:

  ensure(invariant());
  // ensure((*this) == xother);
}

///
template <typename T, typename S>
auto_block<T, S>&
auto_block<T, S>::
operator=(const auto_block& xother)
{

  // Preconditions:

  // Body:

  reserve(xother.ub());
  _ct = xother._ct;

  for(index_type i=0; i<_ct; ++i)
  {
    _base[i] = xother._base[i];
  }

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(*this == xother));

  // Return:

  return *this;
}

///
template <typename T, typename S>
auto_block<T, S>::
~auto_block()
{
  // Preconditions:

  // Body:

  delete [] _base;

  // Postconditions:
}

template <typename T, typename S>
void
auto_block<T, S>::
force_item(index_type xindex, const_reference_type xitem)
{

  // Preconditions:

  require(0 <= xindex);

  // Body:

  if (xindex >= _ub)
  {
    index_type new_ub = _ub*2 > xindex ? _ub*2 : xindex + 1;

    /// @error we haven't guarded against overflow.

    reserve(new_ub);
  }

  set_item(xindex, xitem);

  // Postconditions:

  ensure(invariant());

  /// @issue unexecutable  because it requires T to define operator==.

  ensure(unexecutable(item(xindex) == xitem));
}

///
template <typename T, typename S>
void
auto_block<T, S>::
reserve(index_type xub)
{

  // Preconditions:

  require(xub >= 0);

  // Body:

  define_old_variable(size_type old_ct = _ct);

  index_type old_ub = _ub;

  if(xub > _ub)
  {
    // Allocate a new base array

    pointer_type newbase = new T[xub];

    // Copy the old contents to the new base
    // and delete the old base.

    if(_base != 0)
    {
      for (index_type i = 0; i < _ub; ++i)
      {
        newbase[i] = _base[i];
      }

      delete [] _base;
    }

    // Update base and bound.

    _base = newbase;
    _ub   = xub;

    // Enforce the initialization policy.

    initialization_policy::initialize(_base+old_ub, _base+_ub);
  }

  // Postconditions:

  ensure(invariant());
  ensure(ct() == old_ct);
  ensure(ub() >= old_ub);
  ensure(ub() >= xub);
  ensure((ub() > 0) == (base() != 0));
}

///
template <typename T, typename S>
void
auto_block<T, S>::
set_ct(size_type xct)
{

  // Preconditions:

  require(0 <= xct && xct <= ub());

  // Body:

  _ct = xct;

  // Postconditions:

  ensure(ct() == xct);
}

///
template <typename T, typename S>
void
auto_block<T, S>::
set_item(index_type xindex, const_reference_type xitem)
{

  // Preconditions:

  require(0 <= xindex && xindex < ub());

  // Body:

  *(_base+xindex) = xitem;

  // Postconditions:

  ensure(invariant());

  /// @issue unexecutable  because it requires T to define operator==.

  ensure(unexecutable(item(xindex)==xitem));
}

///
template <typename T, typename S>
void
auto_block<T, S>::
assign(const_reference_type xitem)
{
  // Preconditions:

  // Body:

  define_old_variable(size_type old_ct = ct());

  for(index_type i=0; i<_ct; i++)
  {
    _base[i] = xitem;
  }

  // Postconditions:

  ensure(invariant());
  ensure(ct() == old_ct);

  /// @issue unexecutable  because it requires T to define operator==.

  ensure(unexecutable(ensure_for_all(i, 0, ct(), item(i) == xitem)));

}

///
template <typename T, typename S>
void
auto_block<T, S>::
assign(index_type xbegin, index_type xend, const_reference_type xitem)
{
  // Preconditions:

  require(xbegin >= 0);
  require(xend >= xbegin);

  // Body:

  reserve(xend);
  if(_ct < xend)
  {
    set_ct(xend);
  }

  for(index_type i=xbegin; i<xend; i++)
  {
    _base[i] = xitem;
  }

  // Postconditions:

  ensure(invariant());
  ensure(ct() >= xend);

  /// @issue unexecutable  because it requires T to define operator==.

  ensure(unexecutable(ensure_for_all(i, xbegin, xend, item(i) == xitem)));

}

///
template <typename T, typename S>
typename auto_block<T, S>:: reference_type
auto_block<T, S>::
back() const
{
  // Preconditions:

  require(ct() > 0);

  // Body:

  reference_type result = item(ct() - 1);

  // Postconditions:

  /// @issue unexecutable  because it requires T to define operator==.

  ensure(unexecutable(result == item(ct() - 1)));

  // Exit

  return result;
}

///
template <typename T, typename S>
void
auto_block<T, S>::
push_back(const_reference_type item)
{
  // Preconditions:

  // Body:

  force_item(_ct, item);
  set_ct(_ct+1);

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(ct() == old ct()+1));

  /// @issue unexecutable  because it requires T to define operator==.

  ensure(unexecutable(back() == item));

  // Exit

  return;
}

template <typename T, typename S>
void
auto_block<T, S>::
push_back(const auto_block& xother)
{
  // Preconditions:

  // Body:

  define_old_variable(size_type old_ct = this->ct());


  for(index_type i=0; i<xother.ct(); ++i)
  {
    push_back(xother[i]);
  }

  // Postconditions:

  ensure(this->ct() == old_ct + xother.ct());
  //  ensure_for_all(i, 0, xother.ct(), ((*this)[i + old_ct] == xother[i]) );

  // Exit:

  return;
}

///
template <typename T, typename S>
void
auto_block<T, S>::
pop_back()
{
  // Preconditions:

  require(ct() > 0);

  // Body:

  define_old_variable( size_type old_ct = ct() );

  set_ct(_ct-1);
  initialization_policy::initialize(_base[_ct]);

  // Postconditions:

  ensure(invariant());
  ensure(ct() == old_ct-1);

  // Exit

  return;
}

///
template <typename T, typename S>
void
auto_block<T, S>::
clear()
{
  // Preconditions:

  // Body:

  set_ct(0);
  initialization_policy::initialize(_base, _base+_ub);

  // Postconditions:

  ensure(invariant());
  ensure(ct() == 0);

  // Exit

  return;
}

///
template <typename T, typename S>
void
auto_block<T, S>::
initialize(index_type xindex)
{
  // Preconditions:

  require(0 <= xindex && xindex < ub());

  // Body:

  initialization_policy::initialize(_base[xindex]);

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
template <typename T, typename S>
void
auto_block<T, S>::
initialize(index_type xbegin, index_type xend)
{
  // Preconditions:

  require(0 <= xbegin);
  require(xbegin <= xend);
  require(xend <= ub());

  // Body:

  initialization_policy::initialize(_base+xbegin, _base+xend);

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template <typename T, typename S>
bool
operator==(const auto_block<T, S>& xblk1, const auto_block<T, S>& xblk2)
{
  bool result;

  // Preconditions:

  // Body:

  result = (xblk1.ub() >= xblk2.ub());
  result = result && (xblk1.ct() == xblk2.ct());

  for(sheaf::pod_index_type i=0; result && (i<xblk1.ct()); ++i)
  {
    result = (xblk1[i] == xblk2[i]);
  }

  // Postconditions:

  // Return:

  return result;
}

template <typename T, typename S>
std::ostream&
operator << (std::ostream& xos, const auto_block<T, S>& xblk)
{
  //for(auto_block::index_type i=0; i<xblk.ct(); ++i)
  for(long int i=0; i<xblk.ct(); ++i)
  {
    xos << "  " << xblk[i];
  }

  return xos;
}

template <typename T, typename S>
size_t
deep_size(const auto_block<T, S>& xblk, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xblk) : 0;

  for(int i=0; i<xblk.ub(); ++i)
  {
    result += deep_size(xblk[i], true);
  }

  // Postconditions:

  ensure(result >= 0);

  return result;
}

template <typename T, typename S>
size_t
deep_size(const auto_block<T*, S>& xblk, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xblk) : 0;

  result += xblk.ub()*sizeof(T*);

  for(int i=0; i<xblk.ub(); ++i)
  {
    if(xblk[i] != 0)
    {
      result += deep_size(*xblk[i], true);
    }
  }

  // Postconditions:

  ensure(result >= 0);

  return result;
}

} // namespace sheaf

#endif // AUTO_BLOCK_IMPL_H
