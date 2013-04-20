

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class rc_any

#ifndef RC_ANY_H
#define RC_ANY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace sheaf
{
  
///
/// Base class for reference counting
///
class SHEAF_DLL_SPEC rc_any : public any
{
  // ===========================================================
  /// @name RC_ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  rc_any();

  ///
  /// Constructor
  ///
  rc_any(const rc_any& xother);

  ///
  /// Assignment operator
  ///
  rc_any& operator=(const rc_any& xother);

  ///
  /// Destructor
  ///
  ~rc_any();

  ///
  /// Increment the reference count
  ///
  void add_reference();

  ///
  /// Decrement the reference count.  Delete this object if
  /// the reference count is zero.
  ///
  void remove_reference();

  ///
  /// True if the reference count is greater than one.
  ///
  bool is_shared() const;

  ///
  /// Return the reference count
  ///
  size_type ref_ct() const;

protected:

  ///
  /// Reference count
  ///
  size_type _ref_ct;

private:

  //@}
};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert rc_any rc into ostream os.
///
SHEAF_DLL_SPEC ostream & operator << (ostream &os, const rc_any& rc);
 
} // namespace sheaf

#endif // ifndef RC_ANY_H






