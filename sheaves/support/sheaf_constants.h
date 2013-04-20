
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Declarations for namespace sheaf_constants

#ifndef SHEAF_CONSTANTS_H
#define SHEAF_CONSTANTS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef DOF_TUPLE_TYPE_H
#include "dof_tuple_type.h"
#endif

#ifndef POSET_TYPE_H
#include "poset_type.h"
#endif

#ifndef PRIMITIVE_TYPE_H
#include "primitive_type.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef STANDARD_VERSION_INDEX_H
#include "standard_version_index.h"
#endif

#ifndef STD_CSTDDEF_H
#include "std_cstddef.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
  
///
/// OBSOLETE: use sheaf::poset_type, sheaf::dof_tuple_type, etc.
/// Retained only because swig wraps only class members.
///
/// Type declarations and constant definitions used throughout the sheaf system.
///
class SHEAF_DLL_SPEC sheaf_constants
{

public:

  // =============================================================================
  // POSET TYPES FACET
  // =============================================================================

  ///
  /// Identifiers for poset types.
  ///
  typedef poset_type poset_type;

  ///
  /// The poset type associated with int xi;
  /// converts int to poset type.
  ///
  static poset_type poset_type_id(int xi);

  // =============================================================================
  // DOF TUPLE TYPES FACET
  // =============================================================================

  ///
  /// Identifiers for dof tuple types.
  ///
  typedef dof_tuple_type dof_tuple_type;

  ///
  /// The name of the enumerator xdt.
  ///
  static const string& dof_tuple_type_to_name(dof_tuple_type xdt);

  ///
  /// The enumerator with name xname.
  ///
  static dof_tuple_type dof_tuple_type_from_name(const string& xname);

  ///
  /// The dof tuple type associated with int xi;
  /// converts int to dof tuple type.
  ///
  static dof_tuple_type dof_tuple_type_id(int xi);

  // =============================================================================
  // VERSION IDENTIFIERS FACET
  // =============================================================================

  ///
  /// The void version.
  ///
  static const int NOT_A_VERSION();

  ///
  /// The version of the coarsest common refinement
  /// of all other versions.
  ///
  static const int COARSEST_COMMON_REFINEMENT_VERSION();

  ///
  /// An alias for the current version of a poset.
  ///
  static const int CURRENT_HOST_VERSION();

  ///
  /// An alias for the current version of a member.
  ///
  static const int CURRENT_MEMBER_VERSION();

  // =============================================================================
  // STANDARD POSET MEMBERS FACET
  // =============================================================================

  ///
  /// The index of the bottom member of a poset
  ///
  static const scoped_index BOTTOM_INDEX();

  ///
  /// The index of the top member of a poset
  ///
  static const scoped_index TOP_INDEX();

  // =============================================================================
  // STANDARD NAMESPACE_POSET MEMBERS FACET
  // =============================================================================

  ///
  /// Index of primitives schema poset.
  ///
  static const scoped_index PRIMITIVES_SCHEMA_INDEX();

  ///
  /// Index of namespace schema poset.
  ///
  static const scoped_index NAMESPACE_SCHEMA_INDEX();

  ///
  /// Index of primitives poset.
  ///
  static const scoped_index PRIMITIVES_INDEX();

  ///
  /// Index of schema definitions jrm.
  ///
  static const scoped_index SCHEMA_DEFINITIONS_INDEX();

  // =============================================================================
  // STANDARD SUBPOSETS FACET
  // =============================================================================

  ///
  /// The index of the jims subposet of a poset.
  ///
  static const scoped_index JIMS_INDEX();

  ///
  /// The index of the whole subposet; the top of the powerset of a poset
  ///
  static const scoped_index WHOLE_INDEX();

  ///
  /// The index of the resident subposet of a poset.
  ///
  static const scoped_index RESIDENT_INDEX();
  ///
  /// Alias for the table of contents subposet.
  ///
  static const scoped_index TOC_INDEX();

  // =============================================================================
  // STANDARD DOF TUPLES FACET
  // =============================================================================

  ///
  /// The index of the (unique) empty dof map,
  /// i.e. the dof map with dof_ct() == 0.
  ///
  /// Note on restriction to BOTTOM:
  /// If the schema is restricted to BOTTOM, then the
  /// dof tuple is empty. As with the empty set and the null
  /// vector, we treat the empty dof tuple as unique. So all
  /// members of a poset on the BOTTOM schema share the same
  /// dof tuple, which contains no dofs. The dof tuple id for
  /// the empty dof tuple is 0. This structure is the same for
  /// both internal and external posets.
  ///
  static const scoped_index EMPTY_DOF_TUPLE_INDEX();

  /// @issue does the above really belong here?


  // =============================================================================
  // PRIMITIVE TYPES FACET
  // =============================================================================

  ///
  /// Type ids for primitives
  ///
  typedef primitive_type primitive_type;

  ///
  /// The name of the enumerator xpt.
  ///
  static string primitive_type_to_name(primitive_type xpt);

  ///
  /// The enumerator with name xname.
  ///
  static primitive_type primitive_type_from_name(const string& xname);

  ///
  /// The enumerator corresponding to primitive index xindex.
  ///
  static primitive_type primitive_type_from_index(int xindex);

  ///
  /// True if xindex is a valid primitive index.
  ///
  static bool is_primitive_index(int xindex);

  // =============================================================================
  // PRIMITIVE DESCRIPTORS FACET
  // =============================================================================

  typedef primitive_descriptor primitive_descriptor;

  ///
  /// A descriptor for the primitive with index xindex.
  ///
  static primitive_descriptor primitive_description(int xindex);

  ///
  /// The size of the largest primitive.
  ///
  static size_t max_primitive_size();

  ///
  /// Smallest offset greater than or equal to xoffset that has alignment xalignment.
  ///
  static size_t align(const size_t xoffset, const size_t xalignment);

  // =============================================================================
  // UTILITY METHODS FACET
  // =============================================================================

  ///
  /// Function to test for whether the LPS script has been executed.
  ///
  /// Checks to see if the environment variable LPS_SCRIPT_HAS_RUN
  /// has been set.  If not, the calling program is forced to exit
  /// with a fatal error message; otherwise this method does nothing.
  ///
  static void check_lps_script_has_run();

};

} // namespace sheaf


#endif // ifndef SHEAF_CONSTANTS_H
