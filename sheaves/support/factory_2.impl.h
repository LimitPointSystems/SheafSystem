
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

/// @file
/// Implementation for template class factory_2.

#ifndef FACTORY_2_IMPL_H
#define FACTORY_2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FACTORY_2_H
#include "factory_2.h"
#endif

#ifndef ARG_LIST_H
#include "arg_list.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef NAMESPACE_POSET_H
#include "namespace_poset.h"
#endif

#ifndef RC_PTR_H
#include "rc_ptr.h"
#endif

namespace sheaf
{
  
// ===========================================================
// FACTORY_2 FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T, typename R>
factory_2<T, R>::
factory_2()
{
  // Preconditions:

  // Body:

  // Exit:

  return;
};

template <typename T, typename R>
factory_2<T, R>::
~factory_2()
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

// template <typename T, typename R>
// R
// factory_2<T, R>::
// new_instance(const string& xclient_class_name)
// {
//   // Preconditions:

//   require(contains_prototype(xclient_class_name));

//   // Body:

//   R result = _prototypes_map.find(xclient_class_name)->second->clone();

//   // Postconditions:

//   ensure(result != 0);
//   ensure(unexecutable("result is default constructed"));

//   // Exit:

//   return result;
// };

template <typename T, typename R>
R
factory_2<T, R>::
new_instance(const string& xclient_class_name, const arg_list& xargs)
{
  // Preconditions:

  require(contains_prototype(xclient_class_name));

  // Body:

  R result = _prototypes_map.find(xclient_class_name)->second->clone(xargs);

  // Postconditions:

  ensure(result != 0);
  ensure(unexecutable("result is constructed with args, xargs"));

  // Exit:

  return result;
};

template <typename T, typename R>
void
factory_2<T, R>::
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

  cout << "in factory_2<T, R>::insert_prototype lclass_name = "
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

template <typename T, typename R>
void
factory_2<T, R>::
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

template <typename T, typename R>
bool
factory_2<T, R>::
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

template <typename T, typename R>
factory_2<T, R>::
factory_2(const factory_2& xother) {};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template <typename T, typename R>
ostream& operator << (ostream& xos, const factory_2<T, R>& xf)
{
  // Preconditions:

  // Body:

  typename factory_2<T, R>::prototypes_map_type::const_iterator litr;

  for(litr = xf._prototypes_map.begin(); litr != xf._prototypes_map.end(); ++litr)
  {
    xos << " class: " << litr->first << endl;
  }

  // Postconditions:

  // Exit:

  return xos;
};

} // namespace sheaf

#endif // ifndef FACTORY_2_IMPL_H
