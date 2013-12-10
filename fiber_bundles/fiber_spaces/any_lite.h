
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
/// Interface for class any_lite.

#ifndef ANY_LITE_H
#define ANY_LITE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

//==============================================================================
// CLASS ANY_LITE
//==============================================================================

///
/// Abstract base class with useful features for all volatile objects.
///
class SHEAF_DLL_SPEC any_lite
{

  //============================================================================
  /// @name ANY FACET
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef any_lite volatile_type;

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const = 0;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual any_lite* clone() const;

  ///
  /// Destructor.
  ///
  virtual ~any_lite();

  ///
  /// True if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any_lite& xother) const;

  ///
  /// True if other is the same type as this.
  ///
  bool is_same_type(const any_lite& xother) const;

protected:

  ///
  /// Default constructor.
  ///
  any_lite();


private:

  //@}


  //============================================================================
  /// @name CONTROLLABLE INVARIANT INTERFACE
  //============================================================================
  //@{

public:

  ///
  /// Class invariant, intended to be redefined in each descendant.
  ///
  bool invariant() const;

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

private:

  ///
  /// Number of times disable_invariant_check has been called
  /// without matching call to enable_invariant_check.
  ///
  mutable int _disable_invariance_check_request_depth;

  //@}


  //============================================================================
  /// @name DOF ACCESS FACET
  //============================================================================
  //@{
 
public:

  ///
  /// The row dofs for this instance (mutable version).
  ///
  virtual void* row_dofs();

  ///
  /// The row dofs for this instance (const version).
  ///
  virtual const void* row_dofs() const;

protected:

private:

  //@}
};


} // namespace fiber_bundle

#endif // ifndef ANY_LITE_H
