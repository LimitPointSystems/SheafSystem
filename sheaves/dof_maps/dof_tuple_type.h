
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
const string& dof_tuple_type_to_name(dof_tuple_type xdt);

///
/// The enumerator with name xname.
///
SHEAF_DLL_SPEC
dof_tuple_type dof_tuple_type_from_name(const string& xname);

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
ostream & operator << (ostream& os, dof_tuple_type xdt);


///
/// Extract dof_tuple_type xdt from istream& is.
///
SHEAF_DLL_SPEC
istream & operator >> (istream& is, dof_tuple_type& xdt);
//};

} //namespace sheaf

#endif // ifndef DOF_TUPLE_TYPE_H
