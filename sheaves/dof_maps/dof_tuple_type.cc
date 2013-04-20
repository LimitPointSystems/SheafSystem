
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Definitions for class dof_tuple_type

#include "dof_tuple_type.h"

#include "assert_contract.h"
#include "error_message.h"

// =============================================================================
// DOF TUPLE TYPES FACET
// =============================================================================

///
const string&
sheaf::
dof_tuple_type_to_name(dof_tuple_type xdt)
{
  // Preconditions:

  // Body:

  static const string names[NOT_A_DOF_TUPLE_TYPE+1] =
    {
      "NAMESPACE_POSET_DOF_TUPLE_ID",
      "PRIMITIVES_POSET_DOF_TUPLE_ID",
      "ARRAY_POSET_DOF_TUPLE_ID",
      "ARRAY_SECTION_DOF_TUPLE_ID",
      "SPARSE_SECTOPM_DOF_TUPLE_ID",
      "NOT_A_DOF_TUPLE_TYPE"
    };

  const string& result = names[xdt];

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
sheaf::dof_tuple_type
sheaf::dof_tuple_type_from_name(const string& xname)
{
  dof_tuple_type result;

  // Preconditions:


  // Body:

  /// @hack The following if block is crude, but there doesn't seem to be
  /// any substantially better way to do it. The language doesn't support
  /// iteration over enums and integral values, except compile-time constants,
  /// can not be converted to enums, so searching an array of names is as
  /// at least as clumsy as this construction. STL maps would be clumsy to initialize.

  if(xname == "NAMESPACE_POSET_DOF_TUPLE_ID")
  {
    result = NAMESPACE_POSET_DOF_TUPLE_ID;
  }
  else if(xname == "PRIMITIVES_POSET_DOF_TUPLE_ID")
  {
    result = PRIMITIVES_POSET_DOF_TUPLE_ID;
  }
  else if( xname == "ARRAY_POSET_DOF_TUPLE_ID")
  {
    result = ARRAY_POSET_DOF_TUPLE_ID;
  }
  else if( xname == "ARRAY_SECTION_DOF_TUPLE_ID")
  {
    result = ARRAY_SECTION_DOF_TUPLE_ID;
  }
  else if( xname == "SPARSE_SECTION_DOF_TUPLE_ID")
  {
    result = SPARSE_SECTION_DOF_TUPLE_ID;
  }
  else
  {
    result = NOT_A_DOF_TUPLE_TYPE;
  }

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::dof_tuple_type
sheaf::
dof_tuple_type_id(int xi)
{
  dof_tuple_type result;

  // Preconditions:

  // Body:

  static const dof_tuple_type ltype_ids[] =
    {
      NAMESPACE_POSET_DOF_TUPLE_ID,
      PRIMITIVES_POSET_DOF_TUPLE_ID,
      ARRAY_POSET_DOF_TUPLE_ID,
      ARRAY_SECTION_DOF_TUPLE_ID,
      SPARSE_SECTION_DOF_TUPLE_ID,
      NOT_A_DOF_TUPLE_TYPE // must be last
    }
    ;

  if((0 <= xi) && (xi < NOT_A_DOF_TUPLE_TYPE))
  {
    result = ltype_ids[xi];
  }
  else
  {
    result = NOT_A_DOF_TUPLE_TYPE;
  }

  // Postconditions:

  // Exit

  return result;
}



///
ostream&
sheaf::
operator<<(ostream& os, dof_tuple_type xdt)
{
  // Preconditions:


  // Body:

  os << dof_tuple_type_to_name(xdt);

  // Postconditions:


  // Exit:

  return os;
}

///
istream&
sheaf::
operator>>(istream& is, dof_tuple_type& xdt)
{
  // Preconditions:


  // Body:

  string ltmp;
  is >> ltmp;
  xdt = dof_tuple_type_from_name(ltmp);

  // Postconditions:


  // Exit:

  return is;
}

