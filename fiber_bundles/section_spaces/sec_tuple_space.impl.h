// $RCSfile: class.h,v $ $Revision: 1.2 $ $Date: 2010/06/25 20:44:19 $

// $Name:  $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class sec_tuple_space.impl

#ifndef SEC_TUPLE_SPACE_IMPL_H
#define SEC_TUPLE_SPACE_IMPL_H

#ifndef SEC_TUPLE_SPACE_H
#include "SheafSystem/sec_tuple_space.h"
#endif

#ifndef NAMESPACE_POSET_H
#include "SheafSystem/namespace_poset.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_POSET_H
#include "SheafSystem/section_space_schema_poset.h"
#endif

using namespace fiber_bundle; // Workaround for MS C++ bug.

template <typename F>
bool
fiber_bundle::sec_tuple_space::
fiber_space_conforms(const namespace_poset& xns, const poset_path& xsection_schema_path, bool xauto_access)
{
  // cout << endl << "Entering sec_tuple_space::fiber_schema_conforms." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));
  
  require(!xsection_schema_path.empty());
  require(xns.path_is_auto_read_accessible<section_space_schema_poset>(xsection_schema_path, xauto_access));

  // Body:

  // Get the schema poset.

  section_space_schema_poset& lschema_host = xns.member_poset<section_space_schema_poset>(xsection_schema_path, xauto_access);

  // Fiber space conforms if it is can be downcast to type F. This also ensures the schema conforms
  // to F::standard_schema_path, since that is a precondition of the fiber space factory methods.

  bool result = (dynamic_cast<F*>(&lschema_host.fiber_space()) != 0);

  // Postconditions:


  // Exit:

  // cout << "Leaving sec_tuple_space::fiber_schema_conforms." << endl;
  return result;
}


#endif // ifndef SEC_TUPLE_SPACE_IMPL_H
