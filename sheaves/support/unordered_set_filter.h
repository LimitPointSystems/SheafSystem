
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
/// Interface and implementation for class unordered_set_filter

#ifndef UNORDERED_SET_FILTER_H
#define UNORDERED_SET_FILTER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_UNORDERED_SET_H
#include "std_unordered_set.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif
 
namespace sheaf
{
  
///
/// Hash set implementation of filter concept.
///
class SHEAF_DLL_SPEC unordered_set_filter
{
public:

  ///
  /// Creates an instance for unordered_set xfilter.
  ///
  unordered_set_filter(const std::unordered_set<pod_index_type>& xfilter)
    : _filter(xfilter)
  {};
  
  ///
  /// The filter.
  ///
  const std::unordered_set<pod_index_type>& filter() const
  {
    return _filter;
  };

  ///
  /// True if and only if filter() contains xmbr_index.
  ///
  bool operator()(pod_index_type xmbr_index) const
  {
    return _filter.find(xmbr_index) != _filter.end();
  };

private:

  const std::unordered_set<pod_index_type>& _filter;
};

} // end namespace sheaf

#endif // ifndef UNORDERED_SET_FILTER_H
