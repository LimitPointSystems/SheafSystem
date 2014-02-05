
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

// Interface for class rc_ptr

#ifndef RC_PTR_IMPL_H
#define RC_PTR_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef RC_PTR_H
#include "rc_ptr.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

namespace sheaf
{
  
template <typename T>
rc_ptr<T>::
rc_ptr(T* xtarget)
{
  // Preconditions:

  // Body:

  define_old_variable(size_type old_xtarget_ref_ct = (xtarget != 0) ? xtarget->ref_ct() : 0);

  _target = xtarget;

  if(_target != 0)
  {
    _target->add_reference();
  }

  // Postconditions:

  ensure((xtarget != 0) ? xtarget->ref_ct() == old_xtarget_ref_ct+1 : true);

  // Exit:

  return;
};


template <typename T>
rc_ptr<T>::
rc_ptr(const rc_ptr& xother)
{
  // Preconditions:

  // Body:

  define_old_variable(int old_target_ref_ct = target_ref_ct(xother));

  _target = xother._target;

  if(_target != 0)
  {
    _target->add_reference();
  }

  // Postconditions:

  ensure((*this) == xother);
  ensure(( (*this) != 0 ) ? target_ref_ct(*this) == old_target_ref_ct+1 : true);
};


template <typename T>
rc_ptr<T>::
~rc_ptr()
{
  if(_target != 0)
    _target->remove_reference();
}


template <typename T>
bool
rc_ptr<T>::
operator!() const
{
  return _target == 0;
}

template <typename T>
template <typename U>
bool
rc_ptr<T>::
operator==(const rc_ptr<U>& xother) const
{
  return _target == xother._target;
}

template <typename T>
template <typename U>
bool
rc_ptr<T>::
operator!=(const rc_ptr<U>& xother) const
{
  return _target != xother._target;
}

template <typename T>
rc_ptr<T>&
rc_ptr<T>::
operator=(const rc_ptr& xother)
{
  // Preconditions:

  // Body:

  define_old_variable(bool old_same_target = same_target(*this, xother));
  define_old_variable(int old_this_target_ref_ct = target_ref_ct(*this));
  define_old_variable(T* old_this_target = _target);
  define_old_variable(int old_xother_target_ref_ct = target_ref_ct(xother));

  if(_target != xother._target)
  {
    if(_target != 0)
    {
      _target->remove_reference();
    }

    _target = xother._target;

    if(_target != 0)
    {
      _target->add_reference();
    }
  }

  // Postconditions:

  ensure((*this) == xother);

  ensure(old_same_target ?
         target_ref_ct(*this) == old_this_target_ref_ct :
         true);

  ensure((!old_same_target && (xother != 0)) ?
         target_ref_ct(xother) == old_xother_target_ref_ct + 1:
         true);

  ensure((!old_same_target && (old_this_target_ref_ct > 1)) ?
         old_this_target->ref_ct() == old_this_target_ref_ct - 1 :
         true);

  return *this;
}

template <typename T>
rc_ptr<T>&
rc_ptr<T>::
operator=(T* xtarget)
{
  // Preconditions:

  // Body:

  define_old_variable(bool old_same_target = (_target == xtarget));
  define_old_variable(size_type old_this_target_ref_ct = target_ref_ct(*this));
  define_old_variable(T* old_this_target = _target);
  define_old_variable(size_type old_xtarget_ref_ct = (xtarget != 0) ? xtarget->ref_ct() : 0);

  if(_target != xtarget)
  {
    if(_target != 0)
    {
      _target->remove_reference();
    }

    _target = xtarget;

    if(_target != 0)
    {
      _target->add_reference();
    }
  }

  // Postconditions:

  ensure(*this == xtarget);

  ensure(old_same_target ?
         target_ref_ct(*this) == old_this_target_ref_ct :
         true);

  ensure((!old_same_target && (xtarget != 0)) ?
         target_ref_ct(*this) == old_xtarget_ref_ct + 1 :
         true);

  ensure((!old_same_target) && (old_this_target_ref_ct > 1) ?
         old_this_target->ref_ct() == old_this_target_ref_ct - 1 :
         true);

  return *this;
}


///
template <typename T>
T*
rc_ptr<T>::
operator->() const
{
  // Preconditions:

  require((*this) != 0);

  return _target;
};

template <typename T>
T&
rc_ptr<T>::
operator*() const
{
  // Preconditions:

  require((*this) != 0);

  return *_target;
}

} // namespace sheaf

#endif // ifndef RC_PTR_IMPL_H






