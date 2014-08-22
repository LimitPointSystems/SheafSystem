
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

// Declaration of pod_types facet of namespace sheaf..

#ifndef COM_LIMITPOINT_SHEAF_POD_TYPES_H
#define COM_LIMITPOINT_SHEAF_POD_TYPES_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_H
#include "ComLimitPoint/sheaf/sheaf.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace sheaf
{

// =============================================================================
// POD TYPES FACET
// =============================================================================

// POD (Plain Old Data) types associated with sheaf primitives of class type.

// If you change pod_index_type, review primitive_type::not_a_primitive_type

///
/// The plain old data index type.
///
typedef int_type pod_index_type;

///
/// The invalid pod index value.
///
SHEAF_DLL_SPEC pod_index_type invalid_pod_index();

///
/// True if an only if xpod_index is valid.
///
SHEAF_DLL_SPEC bool is_valid(pod_index_type xpod_index);

///
/// The maximum pod index value.
///
SHEAF_DLL_SPEC pod_index_type max_pod_index();

///
/// The minimum pod index value.
///
SHEAF_DLL_SPEC pod_index_type min_pod_index();

///
/// POD type for scoped_index
///
typedef pod_index_type scoped_index_pod_type;

///
/// POD type for namespace_relative_member_index.
///
struct SHEAF_DLL_SPEC namespace_relative_member_index_pod_type
{
  pod_index_type poset_id;
  pod_index_type member_id;

  bool operator==(const namespace_relative_member_index_pod_type& xother) const;

  bool is_valid();
};

///
/// The invalid namespace_relative_member_index_pod_type value.
///
SHEAF_DLL_SPEC namespace_relative_member_index_pod_type invalid_namespace_relative_member_index_pod();

///
/// Inserts namespace_relative_member_index_pod_type xpod into ostream xos
///
SHEAF_DLL_SPEC 
std::ostream&
operator<<(std::ostream& xos, const namespace_relative_member_index_pod_type& xpod);

///
/// Extracts namespace_relative_member_index_pod_type xpod from istream xis
///
SHEAF_DLL_SPEC 
std::istream&
operator>>(std::istream& xis, namespace_relative_member_index_pod_type& xindex);

///
/// POD type associated with namespace_relative_subposet_index.
///
struct SHEAF_DLL_SPEC namespace_relative_subposet_index_pod_type
{
  pod_index_type poset_id;
  pod_index_type subposet_id;

  bool operator==(const namespace_relative_subposet_index_pod_type& xother) const;

  bool is_valid();
};

///
/// The invalid namespace_relative_subposet_index_pod_type value.
///
SHEAF_DLL_SPEC namespace_relative_subposet_index_pod_type invalid_namespace_relative_subposet_index_pod();

///
/// Inserts namespace_relative_subposet_index_pod_type xpod into ostream xos
///
SHEAF_DLL_SPEC 
std::ostream&
operator<<(std::ostream& xos, const namespace_relative_subposet_index_pod_type& xpod);

///
/// Extracts namespace_relative_subposet_index_pod_type xpod from istream xis
///
SHEAF_DLL_SPEC 
std::istream&
operator>>(std::istream& xis, namespace_relative_subposet_index_pod_type& xindex);

} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_POD_TYPES_H
