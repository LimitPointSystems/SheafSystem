
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

// Interface for class factory

#ifndef FACTORY_IMPL_H
#define FACTORY_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FACTORY_H
#include "factory.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef NAMESPACE_POSET_H
#include "namespace_poset.h"
#endif

namespace sheaf
{
  
// ===========================================================
// FACTORY FACET
// ===========================================================

template <typename T>
factory<T>::
factory()
{
  // Preconditions:

  // Body:

  // Exit:

  return;
};

template <typename T>
factory<T>::
~factory()
{

  // Preconditions:


  // Body:

  // Delete all the prototypes.

  typename prototypes_map_type::iterator itr = _prototypes_map.begin();
  while(itr != _prototypes_map.end())
  {
    delete itr->second;
    ++itr;
  }
  _prototypes_map.clear();

  // Postconditions:

  ensure(unexecutable("All prototypes have been deleted."));

  // Exit:

  return;
};

template <typename T>
T*
factory<T>::
new_instance(const string& xclient_class_name)
{
  T* result = 0;

  // Preconditions:

  require(contains_prototype(xclient_class_name));

  // Body:

  result = _prototypes_map.find(xclient_class_name)->second->clone();

  // Postconditions:

  ensure(result != 0);
  ensure(unexecutable("result is default constructed"));

  // Exit:

  return result;
};

template <typename T>
template <typename S>
T*
factory<T>::
new_instance(const string& xclient_class_name, S& xarg)
{
  T* result = 0;

  // Preconditions:

  require(contains_prototype(xclient_class_name));

  // Body:

  result = new_instance(xclient_class_name);
  result->initialize(xarg);

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_initialized());

  // Exit:

  return result;
};


template <typename T>
void
factory<T>::
insert_prototype(T* xprototype)
{
  // Preconditions:

  require(xprototype != 0);

  // Body:

  // If the map already contains a prototype for the
  // given class name, this insert will do nothing.
  // For this reason, the postcondition does not ensure
  // the prototype == xprototype.

  // string lclass_name = typeid(*xprototype).name();
  string lclass_name = xprototype->class_name();

#ifdef DIAGNOSTIC_OUTPUT

  cout << "in factory<T>::insert_prototype lclass_name = "
  << lclass_name
  << endl;
#endif

  typename prototypes_map_type::value_type lval(lclass_name, xprototype);
  _prototypes_map.insert(lval);

  // Postconditions:

  ensure(contains_prototype(xprototype->class_name()));

  // Exit:

  return;
};

template <typename T>
void
factory<T>::
delete_prototype(const string& xclass_name)
{
  // Preconditions:

  // Body:

  if(!xclass_name.empty())
  {
    typename prototypes_map_type::iterator itr = _prototypes_map.find(xclass_name);
    if(itr != _prototypes_map.end())
    {
      T* lproto = itr->second;
      _prototypes_map.erase(itr);

      delete lproto;
    }
  }

  // Postconditions:

  ensure(!contains_prototype(xclass_name));

  // Exit:

  return;
};

template <typename T>
bool
factory<T>::
contains_prototype(const string& xclass_name) const
{
  bool result;

  // Preconditions:

  // Body:

  result =
    !xclass_name.empty() &&
    (_prototypes_map.find(xclass_name) != _prototypes_map.end());

  // Postconditions:


  // Exit:

  return result;
};

// =============================================================================
// PRIVATE MEMBER FUNCTIONS
// =============================================================================

template <typename T>
factory<T>::
factory(const factory& xother)
{}
;

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template <typename T>
ostream& operator << (ostream& xos, const factory<T>& xf)
{
  // Preconditions:


  // Body:

  typename factory<T>::prototypes_map_type::const_iterator litr;

  for(litr = xf._prototypes_map.begin(); litr != xf._prototypes_map.end(); ++litr)
  {
    xos << " class: " << litr->first << endl;
  }

  // Postconditions:


  // Exit:

  return xos;
};

} // namespace sheaf

#endif // ifndef FACTORY_IMPL_H
