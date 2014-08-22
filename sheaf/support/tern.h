
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

// Interface for class tern

#ifndef COM_LIMITPOINT_SHEAF_TERN_H
#define COM_LIMITPOINT_SHEAF_TERN_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

namespace sheaf
{
  
///
/// A three state "bool". Does not provide the operations
/// of ternary logic and is intended for use mostly as a convenient,
/// three-way input argument.
/// Can not be used as a base class since it
/// does not have a virtual destructor.
///
class SHEAF_DLL_SPEC tern
{

public:

  // =============================================================================
  // TERN FACET
  // =============================================================================

  ///
  /// Default constructor.
  ///
  tern();

  ///
  /// Copy constructor.
  ///
  tern(const tern& xother);

  //   ///
  ///   /// Conversion from boolean.
  //   ///
  //   tern(const bool& xother);

  ///
  /// Destructor.
  ///
  ~tern();

  ///
  /// Assignment operator
  ///
  tern& operator=(const tern& xother);

  //   ///
  ///   /// Assignment operator
  //   ///
  //   tern& operator=(const bool& xother);

  ///
  /// Conversion to bool.
  ///
  operator bool() const;

  ///
  /// True if thi has value true.
  ///
  bool is_true() const;

  ///
  /// True if this has value false.
  ///
  bool is_false() const;

  ///
  /// True if this is neither true nor false.
  ///
  bool is_neither() const;

  ///
  /// The three possible values.
  ///
  enum state_type
  {
    TRUE, FALSE, NEITHER
  };

  ///
  /// Creates instance with state xstate.
  ///
  tern(state_type xstate);

private:

  ///
  /// The current state.
  ///
  state_type _state;



};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
 
} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_TERN_H
