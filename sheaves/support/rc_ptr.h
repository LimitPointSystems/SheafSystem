
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class rc_ptr

#ifndef RC_PTR_H
#define RC_PTR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

namespace sheaf
{
  
///
/// Reference-counted pointer to object of type T.
/// T must be an implementation of concept class rc_any.
///
template<typename T>
class rc_ptr
{

  // The following set of arcane definitions allow an rc_ptr
  // to behave as one expects a pointer to in comparisons.
  // See A. Alexandrescu "Modern C++ Design", Ch 7, section 8.

  ///
  /// True if and only if the target of lhs is rhs.
  ///
  inline friend bool operator==(const rc_ptr& lhs, const T* rhs)
  {
    return lhs._target == rhs;
  };

  ///
  /// True if and only if lhs is the target of rhs.
  ///
  inline friend bool operator==(const T* lhs, const rc_ptr& rhs)
  {
    return lhs == rhs._target;
  };

  ///
  /// True if and only if the target of lhs is not rhs.
  ///
  inline friend bool operator!=(const rc_ptr& lhs, const T* rhs)
  {
    return lhs._target != rhs;
  };

  ///
  /// True if and only if lhs is not the target of rhs.
  ///
  inline friend bool operator!=(const T* lhs, const rc_ptr& rhs)
  {
    return lhs != rhs._target;
  };

  ///
  /// True if and only if the target of lhs is rhs.
  ///
  template <typename U>
  inline friend bool operator==(const rc_ptr& lhs, const U* rhs)
  {
    return lhs._target == rhs;
  };

  ///
  /// True if and only if lhs is the target of rhs.
  ///
  template <typename U>
  inline friend bool operator==(const U* lhs, const rc_ptr& rhs)
  {
    return lhs == rhs._target;
  };

  ///
  /// True if and only if the target of lhs is not rhs.
  ///
  template <typename U>
  inline friend bool operator!=(const rc_ptr& lhs, const U* rhs)
  {
    return lhs._target != rhs;
  };

  ///
  /// True if and only if lhs is not the target of rhs.
  ///
  template <typename U>
  inline friend bool operator!=(const U* lhs, const rc_ptr& rhs)
  {
    return lhs != rhs._target;
  };

  // The next two defintions are convenient for stating contracts.

  ///
  /// True if xp1 and xp2 point to the same target.
  ///
  inline friend bool same_target(const rc_ptr<T>& xp1, const rc_ptr<T>& xp2)
  {
    return xp1._target == xp2._target;
  };

  ///
  /// The reference count of the target of xp
  ///
  inline friend size_type target_ref_ct(const rc_ptr<T>& xp)
  {
    return xp != 0 ? xp->ref_ct() : 0;
  };

public:

  ///
  /// Creates a handle for xtarget.
  ///
  rc_ptr(T* xtarget = 0);

  ///
  /// Copy constructor.
  ///
  rc_ptr(const rc_ptr& xother);

  ///
  /// Destructor.
  ///
  ~rc_ptr();

  ///
  /// Comparison of _target to null;
  /// enables if(!rc_ptr) syntax.
  ///
  bool operator!() const;

  ///
  /// Equality comparison; enables comparison to rc_ptrs of other types.
  ///
  template <typename U>
  bool operator==(const rc_ptr<U>& xother) const;

  ///
  /// Not-equality comparison; enables comparison to rc_ptrs of other types.
  ///
  template <typename U>
  bool operator!=(const rc_ptr<U>& xother) const;

  ///
  /// Assignment from rc_ptr.
  ///
  rc_ptr& operator=(const rc_ptr& xother);

  ///
  /// Assignment from T*.
  ///
  rc_ptr& operator=(T* xtarget);

  ///
  /// A pointer to the target.
  ///
  T* operator->() const;

  ///
  /// A reference to the target.
  ///
  T& operator*() const;

private:

  ///
  /// The target of this.
  ///
  T* _target;

};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef RC_PTR_H






