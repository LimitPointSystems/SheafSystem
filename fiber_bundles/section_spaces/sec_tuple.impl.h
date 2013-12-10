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

#ifndef NAMESPACE_POSET_H
#include "namespace_poset.h"
#endif
 
#ifndef BINARY_SECTION_SPACE_SCHEMA_MEMBER_H
#include "binary_section_space_schema_member.h"
#endif

#ifndef BINARY_SECTION_SPACE_SCHEMA_POSET_H
#include "binary_section_space_schema_poset.h"
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

// template <typename S>
// bool
// fiber_bundle::sec_tuple::
// standard_fiber_host_is_auto_read_accessible(xns, const std::string& xfiber_suffix, bool xauto_access)
// {
//   // Preconditions:

//   xns.state_is_auto_read_accessible(xauto_access);
//   require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));
  
//   // Body:

//   typedef typename S:fiber_type fiber_type;
  
//   poset_path lstd_path(fiber_type::standard_host_path<fiber_type>(xfiber_suffix));

//   bool result = xns.path_is_available<fiber_type::host_type>(lstd_path, xauto_access);
  
//   // Postconditions:

//   // Exit:

//   return result;
// }

// template <typename S>
// sheaf::poset_path
// fiber_bundle::sec_tuple::
// standard_schema_path(const poset_path& xbase_path, const poset_path& xrep_path, const std::string& xfiber_suffix)
// {
//   // Preconditions:

//   require(xbase_path.full());
//   require(rep_path.full());
//   require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));
  
//   // Body:

//   typedef typename S::fiber_type fiber_type;

// //   poset_path lstd_fiber_path(fiber_type::standard_host_path(fiber_type::static_class_name(), xfiber_suffix));
  
// //   string lposet_name(lstd_fiber_path.poset_name());
// //   lposet_name += "_on_";
// //   lposet_name += xbase_path.poset_name();
// //   lposet_name += "_";
// //   lposet_name += xrep_path.member_name();
// //   lposet_name += "_schema";

// //   string lmember_name(lstd_fiber_path.poset_name());
// //   lmember_name += "_on_";
// //   lmamber_name += xbase_space.member_name();
  
// //   poset_path result(lposet_name, lmember_name);


//   poset_path lstd_fiber_path(fiber_type::standard_host_path<fiber_type>(xfiber_suffix));
//   poset_path result(schema_type::standard_host_path(xbase_path, lstd_fiber_path, xrep_path));

//   // Postconditions:

//   ensure(result.full());
  
//   // Exit:

//   return result;
// }

// template <typename S>
// bool
// fiber_bundle::sec_tuple::
// standard_schema_host_is_available(xns,
//                                   const poset_path& xbase_path,
//                                   const poset_path& xrep_path, 
//                                   const std::string& xfiber_suffix,
//                                   bool xauto_access)
// {
//   // Preconditions:

//   xns.state_is_auto_read_accessible(xauto_access);
//   require(xbase_path.full());
//   require(rep_path.full());
//   require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));
  
//   // Body:

//   typedef typename S::schema_type::host_type schema_host_type;
  

//   poset_path lstd_path(S::standard_schema_path<S>(xbase_path, xrep_path, xfiber_suffix));

//   bool result = !xns.contains_path(lstd_path, xauto_access) || xns.contains_path<schema_host_type>(lstd_path, xauto_access);

//   // Postconditions:

//   // Exit:

//   return result;
// }


#endif // ifndef SEC_TUPLE_IMPL_H
