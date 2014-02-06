
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

// Declarations for dof_tuple_type facet of namespace sheaf.

#ifndef DOF_TUPLE_TYPE_H
#define DOF_TUPLE_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

// =============================================================================
// DOF TUPLE TYPES FACET
// =============================================================================

///
/// Identifiers for dof tuple types.
///
enum dof_tuple_type
{
  NAMESPACE_POSET_DOF_TUPLE_ID,
  PRIMITIVES_POSET_DOF_TUPLE_ID,
  ARRAY_POSET_DOF_TUPLE_ID,
  ARRAY_SECTION_DOF_TUPLE_ID,
  SPARSE_SECTION_DOF_TUPLE_ID,
  NOT_A_DOF_TUPLE_TYPE // must be last
  // If you add a type id,
  // don't forget to
  // update dof_tuple_type_id()
};

///
/// The name of the enumerator xdt.
///
SHEAF_DLL_SPEC
const std::string& dof_tuple_type_to_name(dof_tuple_type xdt);

///
/// The enumerator with name xname.
///
SHEAF_DLL_SPEC
dof_tuple_type dof_tuple_type_from_name(const std::string& xname);

///
/// The dof tuple type associated with int xi;
/// converts int to dof tuple type.
///
SHEAF_DLL_SPEC
dof_tuple_type dof_tuple_type_id(int xi);

///
/// Insert dof_tuple_type xdt into ostream& os.
///
SHEAF_DLL_SPEC
std::ostream & operator << (std::ostream& os, dof_tuple_type xdt);

///
/// Extract dof_tuple_type xdt from istream& is.
///
SHEAF_DLL_SPEC
std::istream & operator >> (std::istream& is, dof_tuple_type& xdt);

} //namespace sheaf

#endif // ifndef DOF_TUPLE_TYPE_H
