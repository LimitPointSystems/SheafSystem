
// $RCSfile: any.h,v $ $Revision: 1.22 $ $Date: 2013/01/12 17:17:45 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class any
//


#ifndef ANY_H
#define ANY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

namespace sheaf
{
  
///
/// Abstract base class with useful features for all objects.
///
class SHEAF_DLL_SPEC any
{

public:

  // GENERIC OBJECT INTERFACE

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// True if other is the same type as this
  ///
  bool is_same_type(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual any* clone() const;

  ///
  /// Destructor.
  ///
  virtual ~any();


  // CONTROLLABLE INVARIANT INTERFACE

  ///
  /// Class invariant, intended to be redefined in each descendant.
  /// See below for template for invariant in derived classes.
  ///
  virtual bool invariant() const;

  ///
  /// True if invariant checking is enabled.
  ///
  inline bool invariant_check() const
  {
    return _disable_invariance_check_request_depth == 0;
  };

  ///
  /// Enable invariant checking.
  ///
  inline void enable_invariant_check() const
  {
    --_disable_invariance_check_request_depth;
  };

  ///
  /// Disable invariant check.
  /// Intended for preventing recursive calls to invariant
  /// and for suppressing invariant checking during multi-phase initialization.
  ///
  inline void disable_invariant_check() const
  {
    ++_disable_invariance_check_request_depth;
  };

  ///
  /// Number of times disable_invariant_check has been called
  /// without matching call to enable_invariant_check.
  ///
  inline int disable_invariance_check_request_depth() const
  {
    return _disable_invariance_check_request_depth;
  };

protected:

  ///
  /// default constructor
  ///
  any();


private:

  ///
  /// Number of times disable_invariant_check has been called
  /// without matching call to enable_invariant_check.
  ///
  mutable int _disable_invariance_check_request_depth;
};

} // namespace sheaf

#endif // ifndef ANY_H

