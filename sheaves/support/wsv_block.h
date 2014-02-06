
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

// Interface for class wsv_block

#ifndef WSV_BLOCK_H
#define WSV_BLOCK_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
  
///
/// Whitespace-separated-value block; A block of objects of type T
/// that can be conveniently initialized by a whitespace-separated list.
///
template <typename T>
class SHEAF_DLL_SPEC wsv_block : public block<T>
{

public:

  ///
  /// Default constructor
  ///
  ///
  wsv_block();

  ///
  /// Copy constructor
  ///
  ///
  wsv_block(const wsv_block& xother);

  ///
  /// Destructor
  ///
  ~wsv_block();

  ///
  /// Creates an instance initialized from whitespace-separated list xlist.
  ///
  wsv_block(const char* xlist);

  ///
  /// Creates an instance initialized from whitespace-separated list xlist.
  ///
  wsv_block(const std::string& xlist);

  using block<T>::operator=;

  ///
  /// Sets the contents of this to the contents of
  /// whitespace-separated list xlist.
  ///
  wsv_block& operator=(const wsv_block& xother);

  ///
  /// Sets the contents of this to the contents of
  /// whitespace-separated list xlist.
  ///
  wsv_block& operator=(const std::string& xlist);

  ///
  /// Sets the contents of this to the contents of
  /// whitespace-separated list xlist.
  ///
  wsv_block& operator=(const char* xlist);

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  using block<T>::push_back;

  ///
  /// Appends xother to the back of this.
  ///
  void push_back(const wsv_block& xother);

};


//=============================================================================
// MEMBER FUNCTION SPECIALIZATIONS
//=============================================================================

// Specialization for T == bool:

//$$SCRIBBLE: This specialization requires that all lower
//            case is used in xlist; eg: "true false" as
//            opposed to  "TRUE FALSE"". This limitation
//            could be eliminated with a "bool to_bool(string)"
//            function.

template <>
SHEAF_DLL_SPEC
wsv_block<bool>&
wsv_block<bool>::
operator=(const std::string& xlist);

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // namespace sheaf

#endif // ifndef WSV_BLOCK_H
