
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
SHEAF_DLL_SPEC
std::ostream&
operator << (std::ostream &os, const rc_any& rc);
 
} // namespace sheaf

#endif // ifndef RC_ANY_H






