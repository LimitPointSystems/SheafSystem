// $RCSfile: class.h,v $ $Revision: 1.2 $ $Date: 2010/06/25 20:44:19 $

// $Name:  $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation of template member functions for class sec_tuple

#ifndef SEC_TUPLE_IMPL_H
#define SEC_TUPLE_IMPL_H

#ifndef SEC_TUPLE_H
#include "sec_tuple.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_NAMESPACE_POSET_H
#include "ComLimitPoint/sheaf/namespace_poset.h"
#endif
 
#ifndef BINARY_SECTION_SPACE_SCHEMA_MEMBER_H
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_member.h"
#endif

#ifndef BINARY_SECTION_SPACE_SCHEMA_POSET_H
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_poset.h"
#endif

using namespace fiber_bundle; // Workaround for MS C++ bug.

template <typename S>
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path(const poset_path& xbase_path,
                   const poset_path& xrep_path, 
                   const std::string& xsection_suffix, 
                   const std::string& xfiber_suffix)
{
  // Preconditions:

  require(xbase_path.full());
  require(xrep_path.empty() || xrep_path.full());
  require(xsection_suffix.empty() || poset_path::is_valid_name(xsection_suffix));
  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));
  
  // Body:

  typedef typename S::fiber_type fiber_type;

  poset_path lstd_fiber_path(fiber_type::template standard_host_path<fiber_type>(xfiber_suffix));
  poset_path lrep_path = !xrep_path.empty() ? xrep_path : S::standard_rep_path();
  
  std::string lposet_name(lstd_fiber_path.poset_name());
  lposet_name += "_on_";
  lposet_name += xbase_path.poset_name();
  lposet_name += "_";
  lposet_name += xbase_path.member_name();
  lposet_name += "_";
  lposet_name += lrep_path.member_name();
  lposet_name += xsection_suffix;
  
  poset_path result(lposet_name, "");

  // Postconditions:

  ensure(!result.empty());
  ensure(!result.full());
  
  // Exit:

  return result;
}

template <typename S>
bool
fiber_bundle::sec_tuple::
standard_host_is_available(const namespace_poset& xns,
                           const poset_path& xbase_path,
                           const poset_path& xrep_path, 
                           const std::string& xsection_suffix, 
                           const std::string& xfiber_suffix,
                           bool xauto_access)
{
  // Preconditions:

  xns.state_is_auto_read_accessible(xauto_access);
  require(xbase_path.full());
  require(xrep_path.empty() || xrep_path.full());
  require(xsection_suffix.empty() || poset_path::is_valid_name(xsection_suffix));
  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));
  
  // Body:

  typedef typename S::host_type host_type;
  
  poset_path lstd_path(S::template standard_host_path<S>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));

  bool result = xns.path_is_available<host_type>(lstd_path, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;
}


#endif // ifndef SEC_TUPLE_IMPL_H
