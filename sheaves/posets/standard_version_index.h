// $RCSfile: standard_version_index.h,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:43 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Declarations for standard_version_index facet of namespace sheaf.

#ifndef STANDARD_VERSION_INDEX_H
#define STANDARD_VERSION_INDEX_H

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
/// Ids for standard poset versions.
///
enum standard_version_index
{
  STANDARD_VERSION_INDEX_BEGIN = -4, // Must be same a first std id.
  CURRENT_MEMBER_VERSION = -4,
  CURRENT_HOST_VERSION, // -3
  COARSEST_COMMON_REFINEMENT_VERSION, // -2
  STANDARD_VERSION_INDEX_END, // Must be one more than last std id.
  NOT_A_STANDARD_VERSION_INDEX = INT_MAX
};

///
/// Prefix increment operator for standard_version_index.
///
SHEAF_DLL_SPEC standard_version_index& operator++(standard_version_index& x);

///
/// The name of the enumerator xpt.
///
SHEAF_DLL_SPEC const string& standard_version_index_to_name(standard_version_index xpt);

///
/// The enumerator with name xname.
///
SHEAF_DLL_SPEC standard_version_index standard_version_index_from_name(const string& xname);

///
/// The enumerator corresponding to primitive index xindex.
///
SHEAF_DLL_SPEC standard_version_index standard_version_index_from_index(pod_index_type xindex);

///
/// True if xindex is a valid primitive index.
///
SHEAF_DLL_SPEC bool is_standard_version_index(pod_index_type xindex);

} // namespace sheaf

#endif // ifndef STANDARD_VERSION_INDEX_H






