
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

 

// Implementation for class NAMESPACE_RELATIVE_SUBPOSET_INDEX

// Implementation is mostly inline in namespace_relative_subposet_index.h

#include "namespace_relative_subposet_index.h"

///
ostream&
sheaf::operator<<(ostream& xos, const namespace_relative_subposet_index& xindex)
{
  // Preconditions:

  // Body:

  xos << xindex.poset_id << " " << xindex.subposet_id;

  // Postconditions:

  // Exit:

  return xos;
}

///
istream&
sheaf::operator>>(istream& xis, namespace_relative_subposet_index& xindex)
{
  // Preconditions:

  // Body:

  scoped_index lposet_id, lsubposet_id;

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
    // Converted poset and subposet id successfully; set result.

    xindex.poset_id = lposet_id;
    xindex.subposet_id = lsubposet_id;
  }
  else
  {
    // Couldn't read poset and/or subposet id, set fail bit..

    xis.setstate(ios_base::failbit);
  }

  // Postconditions:

  // Exit:

  return xis;
}

