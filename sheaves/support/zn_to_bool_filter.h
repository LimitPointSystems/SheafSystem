

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Interface and implementation for class zn_to_bool_filter

#ifndef ZN_TO_BOOL_FILTER_H
#define ZN_TO_BOOL_FILTER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
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
  /// Creates an instance for hash_set xfilter.
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

#endif // ifndef ZN_TO_BOOL_FILTER_H
