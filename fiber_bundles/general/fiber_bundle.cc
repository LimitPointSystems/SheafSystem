// $RCSfile: fiber_bundle.cc,v $ $Revision: 1.17 $ $Date: 2013/01/12 17:17:07 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#include "fiber_bundle.h"

#include "assert_contract.h"
#include "block.impl.h"
#include "error_message.h"
#include "poset_path.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

///
sheaf::poset_path
fiber_bundle::
standard_section_space_path(const poset_path& xfiber_path,
                            const poset_path& xbase_path)
{
  poset_path result;

  // Preconditions:


  // Body:

  result.put_poset_name(xfiber_path.poset_name() + "_on_" + xbase_path.poset_name());

  // Postconditions:

  ensure(!result.empty());
  ensure(!result.full());

  // Exit:

  return result;
}

///
sheaf::poset_path
fiber_bundle::
standard_section_space_schema_path(const poset_path& xsection_space_path)
{
  poset_path result;

  // Preconditions:


  // Body:

  result.put_member_name(xsection_space_path.poset_name() + "_schema");
  result.put_poset_name(result.member_name() + "_host");

  // Postconditions:

  ensure(!result.empty());
  ensure( result.full());

  // Exit:

  return result;
}


