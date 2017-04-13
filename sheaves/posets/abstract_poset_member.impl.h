
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
/// Implementation for abstract_poset_member facet function templates.


#ifndef ABSTRACT_POSET_MEMBER_IMPL_H
#define ABSTRACT_POSET_MEMBER_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ABSTRACT_POSET_MEMBER_H
#include "SheafSystem/abstract_poset_member.h"
#endif

namespace sheaf
{

// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

template <typename T>
typename T::table_dofs_type&
table_dofs(T& x0)
{
  // Preconditions:

  require(precondition_of(x0.table_dofs()));
    
  // Body:
  
  typename T::table_dofs_type& result = 
    *reinterpret_cast<typename T::table_dofs_type*>(x0.table_dofs());

  // Postconditions:

  ensure(postcondition_of(x0.table_dofs()));
    
  // Exit:

  return result;
};

template <typename T>
const typename T::table_dofs_type&
table_dofs(const T& x0)
{
  // Preconditions:

  require(precondition_of(x0.table_dofs()));
    
  // Body:

  const typename T::table_dofs_type& result = 
    *reinterpret_cast<const typename T::table_dofs_type*>(x0.table_dofs());

  // Postconditions:

  ensure(postcondition_of(x0.table_dofs()));
    
  // Exit:

  return result;
};

template <typename T>
typename T::table_dofs_type&
table_dofs(T& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(x0.table_dofs(xauto_access)));
    
  // Body:

  typename T::table_dofs_type& result = 
    *reinterpret_cast<typename T::table_dofs_type*>(x0.table_dofs(xauto_access));

  // Postconditions:

  ensure(postcondition_of(x0.table_dofs(xauto_access)));
    
  // Exit:

  return result;
};

template <typename T>
const typename T::table_dofs_type&
table_dofs(const T& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(x0.table_dofs(xauto_access)));
    
  // Body:

  const typename T::table_dofs_type& result = 
    *reinterpret_cast<const typename T::table_dofs_type*>(x0.table_dofs(xauto_access));
  
  // Postconditions:

  ensure(postcondition_of(x0.table_dofs(xauto_access)));
    
  // Exit:

  return result;
};

template <typename T>
typename T::row_dofs_type&
row_dofs(T& x0)
{
  // Preconditions:

  require(precondition_of(x0.row_dofs()));
    
  // Body:

  typename T::row_dofs_type& result = 
    *reinterpret_cast<typename T::row_dofs_type*>(x0.row_dofs());

  // Postconditions:

  ensure(postcondition_of(x0.row_dofs()));
    
  // Exit:

  return result;
};

template <typename T>
const typename T::row_dofs_type&
row_dofs(const T& x0)
{
  // Preconditions:

  require(precondition_of(x0.row_dofs()));
    
  // Body:

  const typename T::row_dofs_type& result = 
    *reinterpret_cast<const typename T::row_dofs_type*>(x0.row_dofs());

  // Postconditions:

  ensure(postcondition_of(x0.row_dofs()));
    
  // Exit:

  return result;
};

template <typename T>
typename T::row_dofs_type&
row_dofs(T& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(x0.row_dofs(xauto_access)));
    
  // Body:

  typename T::row_dofs_type& result = 
    *reinterpret_cast<typename T::row_dofs_type*>(x0.row_dofs(xauto_access));

  // Postconditions:

  ensure(postcondition_of(x0.row_dofs(xauto_access)));
    
  // Exit:

  return result;
};

template <typename T>
const typename T::row_dofs_type&
row_dofs(const T& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(x0.row_dofs(xauto_access)));
    
  // Body:

  const typename T::row_dofs_type& result = 
    *reinterpret_cast<const typename T::row_dofs_type*>(x0.row_dofs(xauto_access));

  // Postconditions:

  ensure(postcondition_of(x0.row_dofs(xauto_access)));
    
  // Exit:

  return result;
};
  
} // namespace sheaf

#endif // ifndef ABSTRACT_POSET_MEMBER_IMPL_H
