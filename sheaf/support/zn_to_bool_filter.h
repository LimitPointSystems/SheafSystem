
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
/// Interface and implementation for class zn_to_bool_filter

#ifndef COM_LIMITPOINT_SHEAF_ZN_TO_BOOL_FILTER_H
#define COM_LIMITPOINT_SHEAF_ZN_TO_BOOL_FILTER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ZN_TO_BOOL_H
#include "ComLimitPoint/sheaf/zn_to_bool.h"
#endif

//$$SCRIBBLE: jebutler const correctness visited

namespace sheaf
{
  
///
/// Zn_to_bool implementation of filter concept.
///
class SHEAF_DLL_SPEC zn_to_bool_filter
{
public:

  ///
  /// Creates an instance for unordered_set xfilter.
  ///
  zn_to_bool_filter(const zn_to_bool& xfilter)
    : _filter(xfilter)
  {};
  
  ///
  /// The filter.
  ///
  const zn_to_bool& filter() const
  {
    return _filter;
  };

  ///
  /// True if and only if filter() contains xmbr_index.
  ///
  bool operator()(pod_index_type xmbr_index) const
  {
    return _filter[xmbr_index];
  };
  
private:

  const zn_to_bool& _filter;
};
  
} // end namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_ZN_TO_BOOL_FILTER_H
