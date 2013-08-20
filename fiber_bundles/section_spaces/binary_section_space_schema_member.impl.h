

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for section_space_schema_member facet function templates.

#ifndef BINARY_SECTION_SPACE_SCHEMA_MEMBER_IMPL_H
#define BINARY_SECTION_SPACE_SCHEMA_MEMBER_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BINARY_SECTION_SPACE_SCHEMA_MEMBER_H
#include "binary_section_space_schema_member.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef BINARY_SECTION_SPACE_SCHEMA_POSET_H
#include "binary_section_space_schema_poset.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef SEC_REP_DESCRIPTOR_POSET_H
#include "sec_rep_descriptor_poset.h"
#endif

#ifndef TUPLE_H
#include "tuple.h"
#endif

template <typename S>
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path(const poset_path& xbase_path, const poset_path& xrep_path, const string& xfiber_suffix)
{
  // cout << endl << "Entering binary_section_space_schema_member::standard_host_path." << endl;

  // Preconditions:

  require(xbase_path.full());
  require(xrep_path.empty() || xrep_path.full());
  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));

  // Body:
  
  typedef typename S::fiber_type fiber_type;

  poset_path lrep_path = !xrep_path.empty() ? xrep_path : S::standard_rep_path();
  
  
  string lposet_name(fiber_type::static_class_name());
  lposet_name += "_on_";
  lposet_name += xbase_path.poset_name();
  lposet_name += "_";
  lposet_name += lrep_path.member_name();
  lposet_name += "_schema";

  sheaf::poset_path result(lposet_name, "");


  // Postconditions:

  ensure(!result.full());

  // Exit:

  // cout << "Leaving binary_section_space_schema_member::standard_host_path." << endl;
  return result;
}

template <typename S>
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path(const poset_path& xbase_path, const poset_path& xrep_path, const string& xfiber_suffix)
{
  // cout << endl << "Entering binary_section_space_schema_member::standard_path." << endl;

  // Preconditions:

  require(xbase_path.full());
  require(xrep_path.empty() || xrep_path.full());
  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));

  // Body:

  typedef typename S::fiber_type fiber_type;

  poset_path result(standard_host_path<S>(xbase_path, xrep_path, xfiber_suffix));

  string lmember_name(fiber_type::static_class_name());
  lmember_name += "_on_";
  lmember_name += xbase_path.member_name();
  lmember_name += "_schema";

  result.put_member_name(lmember_name);
  
  // Postconditions:

  ensure(result.full());

  // Exit:

  // cout << "Leaving binary_section_space_schema_member::standard_path." << endl;
  return result;
}



template <typename S>
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available(namespace_poset& xns, 
                           const poset_path& xbase_path,
                           const poset_path& xrep_path,
                           const string& xfiber_suffix,
                           bool xauto_access)
{
  // cout << endl << "Entering binary_section_space_schema_member::standard_host." << endl;

  // Preconditions:


  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xbase_path.full());
  require(xns.path_is_auto_read_accessible<base_space_poset>(xbase_path, xauto_access));

  require(xrep_path.empty() || xrep_path.full());
  require(xrep_path.empty() || xns.path_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));

  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));

  // Body:

  poset_path lstd_path(standard_host_path<S>(xbase_path, xrep_path, xfiber_suffix));

  bool result = xns.path_is_available<host_type>(lstd_path, xauto_access);

  // Postconditions:


  // Exit:

  // cout << "Leaving binary_section_space_schema_member::standard_host." << endl;
  return result;
}

template <typename S>
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host(namespace_type& xns, 
              const poset_path& xbase_path,
              const poset_path& xrep_path,
              const string& xfiber_suffix,
              bool xauto_access)
{
  // cout << endl << "Entering binary_section_space_schema_member::standard_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));  

  require(xbase_path.full());
  require(xns.path_is_auto_read_accessible<base_space_poset>(xbase_path, xauto_access));

  require(xrep_path.empty() || xrep_path.full());
  require(xrep_path.empty() || xns.path_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));

  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));
  require(S::fiber_type::template standard_host_is_available<typename S::fiber_type>(xns, xfiber_suffix, xauto_access));

  require(standard_host_is_available<S>(xns, xbase_path, xrep_path, xfiber_suffix, xauto_access));

  // Body:

  typedef typename S::fiber_type fiber_type;
  typedef typename S::fiber_type::host_type fiber_host_type;
  
  poset_path lstd_path(standard_host_path<S>(xbase_path, xrep_path, xfiber_suffix));

  host_type* lresult_ptr;
  
  if(xns.contains_path(lstd_path, xauto_access))
  {
    // Host already exists, just return it.

    lresult_ptr = &xns.member_poset<host_type>(lstd_path, xauto_access);  
  }
  else
  {
    // Host does already exist, we will have to create it.

    // First, make sure the standard fiber space exists.

    fiber_host_type& lfiber_space = fiber_type::standard_host(xns, xfiber_suffix, xauto_access);
    poset_path lfiber_path = lfiber_space.path(xauto_access);
    
    // Now create the host with the standard schema.
  
    poset_path lstd_schema_path(host_type::standard_schema_path());

    lresult_ptr = &new_host(xns, lstd_path, lstd_schema_path, xbase_path, lfiber_path, xrep_path, xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  //  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path<S>(xbase_path, xrep_path, xfiber_suffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == host_type::standard_schema_path());

  ensure(result.base_space_path(true).poset_name() == xbase_path.poset_name());
  ensure(result.fiber_space_path(true) == S::fiber_type::template standard_host_path<typename S::fiber_type>(xfiber_suffix));
  ensure(result.rep_path(true) == xrep_path);

  // Exit:

  // cout << "Leaving binary_section_space_schema_member::standard_host." << endl;
  return result;
}

template <typename S>
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member(namespace_type& xns, 
                const poset_path& xbase_path,
                const poset_path& xrep_path,
                const string& xfiber_suffix,
                bool xauto_access)
{
  // cout << endl << "Entering binary_section_space_schema_member::standard_host." << endl;

  // Preconditions:

  require(precondition_of(standard_host<S>(xns, xbase_path, xrep_path, xfiber_suffix, xauto_access)));

  // Body:

  // Find or create the standard host.

  host_type& lhost = standard_host<S>(xns, xbase_path, xrep_path, xfiber_suffix, xauto_access);

  // All members of the schema exist implicitly, but a member can't 
  // be accessed by path unless we explicitly give it a name..

  poset_path result(standard_member_path<S>(xbase_path, xrep_path, xfiber_suffix));
  if(!lhost.contains_member(result.member_name()))
  {  
    binary_section_space_schema_member lmbr(&lhost, xbase_path, lhost.fiber_space().schema(xauto_access).name(xauto_access));
    lmbr.put_name(result.member_name(), true, true);
  }

  // Postconditions:

  ensure(postcondition_of(standard_host<S>(xns, xbase_path, xrep_path, xfiber_suffix, xauto_access)));

  ensure(result == standard_member_path<S>(xbase_path, xrep_path, xfiber_suffix));  
  ensure(xns.contains_path(result, xauto_access));

  // Exit:

  // cout << "Leaving binary_section_space_schema_member::standard_host." << endl;
  return result;
}

#endif // ifndef BINARY_SECTION_SPACE_SCHEMA_MEMBER_IMPL_H
