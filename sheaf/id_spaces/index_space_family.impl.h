
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Implementation for member function templates in class index_space_family.

#ifndef COM_LIMITPOINT_SHEAF_INDEX_SPACE_FAMILY_IMPL_H
#define COM_LIMITPOINT_SHEAF_INDEX_SPACE_FAMILY_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_INDEX_SPACE_FAMILY_H
#include "ComLimitPoint/sheaf/index_space_family.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ASSERT_CONTRACT_H
#include "ComLimitPoint/sheaf/assert_contract.h"
#endif

// ===========================================================
// PRODUCT STRUCTURE FACET
// ===========================================================

template<typename T>
const T&
sheaf::index_space_family::
product_structure(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));
  require(has_product_structure(xname));
  require(product_structure_conforms_to<T>(xname));

  // Body:

  const T& result = reinterpret_cast<const T&>(product_structure(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

template<typename T>
const T&
sheaf::index_space_family::
product_structure(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));
  require(has_product_structure(xspace_id));
  require(product_structure_conforms_to<T>(xspace_id));

  // Body:

  const T& result = reinterpret_cast<const T&>(product_structure(xspace_id));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

template<typename T>
T&
sheaf::index_space_family::
product_structure(const std::string& xname)
{
  // Preconditions:

  require(contains(xname));
  require(has_product_structure(xname));
  require(product_structure_conforms_to<T>(xname));

  // Body:

  T& result = reinterpret_cast<T&>(product_structure(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

template<typename T>
T&
sheaf::index_space_family::
product_structure(pod_type xspace_id)
{
  // Preconditions:

  require(contains(xspace_id));
  require(has_product_structure(xspace_id));
  require(product_structure_conforms_to<T>(xspace_id));

  // Body:

  T& result = reinterpret_cast<T&>(product_structure(xspace_id));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

template<typename T>
bool
sheaf::index_space_family::
product_structure_conforms_to(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));
  require(has_product_structure(xname));

  // Body:

  bool result = (dynamic_cast<const T*>(&product_structure(xname)) != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

template<typename T>
bool
sheaf::index_space_family::
product_structure_conforms_to(pod_type xspace_id) const
{
  // Preconditions:

  require(contains(xspace_id));
  require(has_product_structure(xspace_id));

  // Body:

  bool result = (dynamic_cast<const T*>(&product_structure(xspace_id)) != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// ===========================================================
// HANDLE POOL FACET
// ===========================================================

template<typename T>
T&
sheaf::index_space_family::
get_id_space(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));
  require(handle_conforms_to_state<T>(xname));

  // Body:

  T& result = reinterpret_cast<T&>(get_id_space(xname));

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
};

template<typename T>
T&
sheaf::index_space_family::
get_id_space(pod_type xid) const
{
  // Preconditions:

  require(contains(xid));
  require(handle_conforms_to_state<T>(xid));

  // Body:

  T& result = reinterpret_cast<T&>(get_id_space(xid));

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
};

template<typename T>
bool
sheaf::index_space_family::
handle_conforms_to_state(const std::string& xname) const
{
  // Preconditions:

  require(contains(xname));

  // Body:

  index_space_handle& lhandle = get_id_space(xname);

  bool result = (dynamic_cast<const T*>(&lhandle) != 0);

  release_id_space(lhandle);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
};

template<typename T>
bool
sheaf::index_space_family::
handle_conforms_to_state(pod_type xid) const
{
  // Preconditions:

  require(contains(xid));

  // Body:

  index_space_handle& lhandle = get_id_space(xid);

  bool result = (dynamic_cast<const T*>(&lhandle) != 0);

  release_id_space(lhandle);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
};

#endif // ifndef INDEX_SPACE_FAMILY_IMPL_H
