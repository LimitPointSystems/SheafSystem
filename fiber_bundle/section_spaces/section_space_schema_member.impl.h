

//
// Copyright (c) 2014 Limit Point Systems, Inc.
//

// Implementation for section_space_schema_member facet function templates.

#ifndef SECTION_SPACE_SCHEMA_MEMBER_IMPL_H
#define SECTION_SPACE_SCHEMA_MEMBER_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ASSERT_CONTRACT_H
#include "ComLimitPoint/sheaf/assert_contract.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_MEMBER_H
#include "ComLimitPoint/fiber_bundle/section_space_schema_member.h"
#endif

template <typename F>
F& 
fiber_bundle::section_space_schema_member::
fiber_space()
{
  // Preconditions:

  require(dynamic_cast<F*>(&fiber_space()) != 0);
  
  // Body:

  F& result = dynamic_cast<F&>(fiber_space());
  
  // Postconditions:

  // Exit:

  return result;
}

template <typename F>
const F& 
fiber_bundle::section_space_schema_member::
fiber_space() const
{
  // Preconditions:

  require(dynamic_cast<F*>(&fiber_space()) != 0);
  
  // Body:

  const F& result = dynamic_cast<F&>(fiber_space());
  
  // Postconditions:

  // Exit:

  return result;
}


#endif // ifndef SECTION_SPACE_SCHEMA_MEMBER_IMPL_H
