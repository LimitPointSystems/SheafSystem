// $RCSfile: set_filter.h,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:47 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Interface and implementation for class set_filter

#ifndef SET_FILTER_H
#define SET_FILTER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

namespace sheaf
{
  
///
/// Set implementation of filter concept.
///
class SHEAF_DLL_SPEC set_filter
{
public:

  ///
  /// Creates an instance for hash_set xfilter.
  ///
  set_filter(const set<pod_index_type>& xfilter)
    : _filter(xfilter)
  {};
  
  ///
  /// The filter.
  ///
  const set<pod_index_type>& filter() const
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

  const set<pod_index_type>& _filter;
};

} // end namespace sheaf

#endif // ifndef SET_FILTER_H
