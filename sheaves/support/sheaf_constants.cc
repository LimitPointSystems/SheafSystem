// $RCSfile: sheaf_constants.cc,v $ $Revision: 1.24 $ $Date: 2013/01/12 17:17:47 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Definitions for class sheaf_constants

#include "sheaf_constants.h"

// =============================================================================
// POSET TYPES FACET
// =============================================================================

sheaf::sheaf_constants::poset_type
sheaf::sheaf_constants::
poset_type_id(int xi)
{
  return sheaf::poset_type_id(xi);
}

// =============================================================================
// DOF TUPLE TYPES FACET
// =============================================================================

const string&
sheaf::sheaf_constants::
dof_tuple_type_to_name(dof_tuple_type xdt)
{
  return sheaf::dof_tuple_type_to_name(xdt);
}

sheaf::sheaf_constants::dof_tuple_type
sheaf::sheaf_constants::
dof_tuple_type_from_name(const string& xname)
{
  return sheaf::dof_tuple_type_from_name(xname);
}

sheaf::sheaf_constants::dof_tuple_type
sheaf::sheaf_constants::
dof_tuple_type_id(int xi)
{
  return sheaf::dof_tuple_type_id(xi);
}



// =============================================================================
// VERSION IDENTIFIERS FACET
// =============================================================================


///
const int
sheaf::sheaf_constants::
NOT_A_VERSION()
{
  return -1;
}

///
const int
sheaf::sheaf_constants::
COARSEST_COMMON_REFINEMENT_VERSION()
{
  return -2;
}

///
const int
sheaf::sheaf_constants::
CURRENT_HOST_VERSION()
{
  return -3;
}

///
const int
sheaf::sheaf_constants::
CURRENT_MEMBER_VERSION()
{
  return -4;
}


// =============================================================================
// STANDARD POSET MEMBERS FACET
// =============================================================================

///
const scoped_index
sheaf::sheaf_constants::
BOTTOM_INDEX()
{
  static const scoped_index result(0);
  return result;
}

///
const scoped_index
sheaf::sheaf_constants::
TOP_INDEX()
{
  static const scoped_index result(1);
  return result;
}


// =============================================================================
// STANDARD NAMESPACE_POSET MEMBERS FACET
// =============================================================================

///
const scoped_index
sheaf::sheaf_constants::
PRIMITIVES_SCHEMA_INDEX()
{
  static const scoped_index result(2);
  return result;
}

///
const scoped_index
sheaf::sheaf_constants::
NAMESPACE_SCHEMA_INDEX()
{
  static const scoped_index result(3);
  return result;
}

///
const scoped_index
sheaf::sheaf_constants::
PRIMITIVES_INDEX()
{
  static const scoped_index result(4);
  return result;
}

///
const scoped_index
sheaf::sheaf_constants::
SCHEMA_DEFINITIONS_INDEX()
{
  static const scoped_index result(5);
  return result;
}



// =============================================================================
// STANDARD SUBPOSETS FACET
// =============================================================================

///
const scoped_index
sheaf::sheaf_constants::
JIMS_INDEX()
{
  static const scoped_index result(0);
  return result;
}

///
const scoped_index
sheaf::sheaf_constants::
WHOLE_INDEX()
{
  static const scoped_index result(1);
  return result;
}

///
const scoped_index
sheaf::sheaf_constants::
RESIDENT_INDEX()
{
  static const scoped_index result(2);
  return result;
}

///
const scoped_index
sheaf::sheaf_constants::
TOC_INDEX()
{
  static const scoped_index result(-2);
  return result;
}



// =============================================================================
// STANDARD DOF TUPLES FACET
// =============================================================================

///
const scoped_index
sheaf::sheaf_constants::
EMPTY_DOF_TUPLE_INDEX()
{
  static const scoped_index result(0);
  return result;
}


// =============================================================================
// PRIMITIVE TYPES FACET
// =============================================================================

string
sheaf::sheaf_constants::
primitive_type_to_name(primitive_type xpt)
{
  return primitive_attributes::name(xpt);
}

sheaf::sheaf_constants::primitive_type
sheaf::sheaf_constants::
primitive_type_from_name(const string& xname)
{
  return primitive_attributes::id(xname);
}

sheaf::sheaf_constants::primitive_type
sheaf::sheaf_constants::
primitive_type_from_index(int xindex)
{
  return primitive_attributes::id(xindex);
}

bool
sheaf::sheaf_constants::
is_primitive_index(int xindex)
{
  return sheaf::is_primitive_index(xindex);
}

// =============================================================================
// PRIMITIVE DESCRIPTORS FACET
// =============================================================================

sheaf::sheaf_constants::primitive_descriptor
sheaf::sheaf_constants::
primitive_description(int xindex)
{
  return primitive_description(xindex);
}

size_t
sheaf::sheaf_constants::
max_primitive_size()
{
  return sizeof(primitive_buffer_type);
}

size_t
sheaf::sheaf_constants::
align(const size_t xoffset, const size_t xalignment)
{
  return sheaf::align(xoffset, xalignment);
}



// ===========================================================
// UTILITY FUNCTIONS
// ===========================================================

void
sheaf::sheaf_constants::
check_lps_script_has_run()
{
  sheaf::check_lps_script_has_run();
}


