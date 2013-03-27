// $RCSfile: pod_types.cc,v $ $Revision: 1.11 $ $Date: 2013/01/12 17:17:46 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

 

// Definitions for pod_types facet of namespace sheaf.

#include "pod_types.h"

#include "std_limits.h"


// =============================================================================
// POD TYPES FACET
// =============================================================================

sheaf::pod_index_type
sheaf::invalid_pod_index()
{
  return numeric_limits<sheaf::pod_index_type>::max();
}

bool
sheaf::is_valid(sheaf::pod_index_type xpod_index)
{
  return xpod_index != invalid_pod_index();
}

sheaf::pod_index_type
sheaf::max_pod_index()
{
  return numeric_limits<sheaf::pod_index_type>::max() - 1;
}

sheaf::pod_index_type
sheaf::min_pod_index()
{
  return numeric_limits<sheaf::pod_index_type>::min();
}

sheaf::namespace_relative_member_index_pod_type
sheaf::invalid_namespace_relative_member_index_pod()
{
  sheaf::namespace_relative_member_index_pod_type result;
  result.poset_id = invalid_pod_index();
  result.member_id = invalid_pod_index();
  return result;
}

 

bool
sheaf::namespace_relative_member_index_pod_type::
operator==(const namespace_relative_member_index_pod_type& xother) const
{
  return (poset_id == xother.poset_id) && (member_id == xother.member_id);
};

bool
sheaf::namespace_relative_member_index_pod_type::
is_valid()
{
  return (sheaf::is_valid(poset_id) && sheaf::is_valid(member_id));
}

sheaf::namespace_relative_subposet_index_pod_type
sheaf::invalid_namespace_relative_subposet_index_pod()
{
  sheaf::namespace_relative_subposet_index_pod_type result;
  result.poset_id = invalid_pod_index();
  result.subposet_id = invalid_pod_index();
  return result;
}

 

bool
sheaf::namespace_relative_subposet_index_pod_type::
operator==(const sheaf::namespace_relative_subposet_index_pod_type& xother) const
{
  return (poset_id == xother.poset_id) && (subposet_id == xother.subposet_id);
};

bool
sheaf::namespace_relative_subposet_index_pod_type::
is_valid()
{
  return (sheaf::is_valid(poset_id) && sheaf::is_valid(subposet_id));
}

ostream&
sheaf::operator<<(ostream& xos, const namespace_relative_member_index_pod_type& xpod)
{
  xos << xpod.poset_id << " " << xpod.member_id ;
  return xos;
}

istream&
sheaf::operator>>(istream& xis, namespace_relative_member_index_pod_type& xpod)
{
  // Preconditions:

  // Body:

  pod_index_type lposet_id, lmember_id;

  // Extract "poset_id member_id", checking each step so
  // when we return the stream state properly represents any failure.
  // In particular, the stream state should properly distinguish
  // a syntax or conversion failure from an end-of-file.
  //
  // Note that skipws may or may not be set, so we explicitly
  // skip white space to make sure it is dealt with properly.
  //
  // Also note that this operator does not modify xindex unless
  // the extraction succeeeds.

  if((xis >> ws >> lposet_id) && (xis >> ws >> lmember_id))
  {
    // Converted poset and member id successfully; set result.

    xpod.poset_id = lposet_id;
    xpod.member_id = lmember_id;
  }
  else
  {
    // Couldn't read poset and/or member id, set fail bit..

    xis.setstate(ios_base::failbit);
  }

  // Postconditions:

  // Exit:

  return xis;
}

ostream&
sheaf::operator<<(ostream& xos, const namespace_relative_subposet_index_pod_type& xpod)
{
  xos << xpod.poset_id << " " << xpod.subposet_id ;
  return xos;
}

istream&
sheaf::operator>>(istream& xis, namespace_relative_subposet_index_pod_type& xpod)
{
  // Preconditions:

  // Body:

  pod_index_type lposet_id;
  pod_index_type lsubposet_id;

  // Extract "poset_id subposet_id", checking each step so
  // when we return the stream state properly represents any failure.
  // In particular, the stream state should properly distinguish
  // a syntax or conversion failure from an end-of-file.
  //
  // Note that skipws may or may not be set, so we explicitly
  // skip white space to make sure it is dealt with properly.
  //
  // Also note that this operator does not modify xindex unless
  // the extraction succeeeds.

  if((xis >> ws >> lposet_id) && (xis >> ws >> lsubposet_id))
  {
    // Converted poset and member id successfully; set result.

    xpod.poset_id = lposet_id;
    xpod.subposet_id = lsubposet_id;
  }
  else
  {
    // Couldn't read poset and/or member id, set fail bit..

    xis.setstate(ios_base::failbit);
  }

  // Postconditions:

  // Exit:

  return xis;
}
