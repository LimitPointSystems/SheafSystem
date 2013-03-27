// $RCSfile: standard_member_index.h,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:43 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Declarations for standard_member_index facet of namespace sheaf.

#ifndef STANDARD_MEMBER_INDEX_H
#define STANDARD_MEMBER_INDEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_CLIMITS_H
#include "std_climits.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

///
/// Ids for standard poset members.
///
enum standard_member_index
{
  STANDARD_MEMBER_INDEX_BEGIN = 0, // Must be same as first std id.
  BOTTOM_INDEX = 0,
  TOP_INDEX, // 1
  STANDARD_MEMBER_INDEX_END, // Must be one more than last std id.
  NOT_A_STANDARD_MEMBER_INDEX = INT_MAX
};

///
/// Prefix increment operator for standard_member_index.
///
SHEAF_DLL_SPEC standard_member_index& operator++(standard_member_index& x);

///
/// The name of the enumerator xpt.
///
SHEAF_DLL_SPEC const string& standard_member_index_to_name(standard_member_index xpt);

///
/// The enumerator with name xname.
///
SHEAF_DLL_SPEC standard_member_index standard_member_index_from_name(const string& xname);

///
/// The enumerator corresponding to primitive index xindex.
///
SHEAF_DLL_SPEC standard_member_index standard_member_index_from_index(pod_index_type xindex);

///
/// True if xindex is a valid primitive index.
///
SHEAF_DLL_SPEC bool is_standard_member_index(pod_index_type xindex);

} // namespace sheaf

#endif // ifndef STANDARD_MEMBER_INDEX_H






