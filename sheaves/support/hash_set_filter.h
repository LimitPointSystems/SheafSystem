// $RCSfile: hash_set_filter.h,v $ $Revision: 1.11 $ $Date: 2013/01/12 17:17:46 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//



/// @file
/// Interface and implementation for class hash_set_filter

#ifndef HASH_SET_FILTER_H
#define HASH_SET_FILTER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_HASH_SET_H
#include "std_hash_set.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif
 
namespace sheaf
{
  
///
/// Hash set implementation of filter concept.
///
class SHEAF_DLL_SPEC hash_set_filter
{
public:

  ///
  /// Creates an instance for hash_set xfilter.
  ///
  hash_set_filter(const hash_set<pod_index_type>& xfilter)
    : _filter(xfilter)
  {};
  
  ///
  /// The filter.
  ///
  const hash_set<pod_index_type>& filter() const
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

  const hash_set<pod_index_type>& _filter;
};

} // end namespace sheaf

#endif // ifndef HASH_SET_FILTER_H
