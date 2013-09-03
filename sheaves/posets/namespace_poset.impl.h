

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for member function templates in class namespace_poset.

#ifndef NAMESPACE_POSET_IMPL_H
#define NAMESPACE_POSET_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef NAMESPACE_POSET_H
#include "namespace_poset.h"
#endif

#ifndef ARG_LIST_H
#include "arg_list.h"
#endif

#ifndef ARRAY_POSET_DOF_MAP_H
#include "array_poset_dof_map.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef NAMESPACE_POSET_MEMBER_H
#include "namespace_poset_member.h"
#endif
 
#ifndef POSET_PATH_H
#include "poset_path.h"
#endif
   
// ===========================================================
// NAMESPACE_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// POSET FACTORY METHOD FACET
// ===========================================================

// PUBLIC FUNCTIONS

template<typename P>
P&
sheaf::namespace_poset::
member_poset(pod_index_type xhub_id, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xhub_id, xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(is_jim(xhub_id));

  // Body:

  namespace_poset_dof_map& ldof_map =
    row_dof_map(member_dof_tuple_id(xhub_id, false));

  P& result = dynamic_cast<P&>(*ldof_map.poset_pointer());

  if(xauto_access)
  {
    release_access();
  }

  return result;
}

template<typename P>
P&
sheaf::namespace_poset::
member_poset(const scoped_index& xid, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xid, xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(is_jim(xid));

  // Body:

  P& result = member_poset<P>(xid.hub_pod(), false);

  if(xauto_access)
  {
    release_access();
  }

  return result;
}

template<typename P>
P&
sheaf::namespace_poset::
member_poset(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  require(contains_poset<P>(xpath, xauto_access));
  
  // Body:

  P& result = dynamic_cast<P&>(member_poset(xpath, xauto_access));

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// POSET FACTORY METHOD QUERY FACET
// ===========================================================

// PUBLIC FUNCTIONS

template<typename P>
bool
sheaf::namespace_poset::
contains_poset(pod_index_type xhub_id, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  if(xauto_access)
  {
    get_read_access();
  }

  // Body:

  bool result = contains_member(xhub_id, false) && is_jim(xhub_id);
  if(result)
  {
    result = (dynamic_cast<P*>(&member_poset(xhub_id, xauto_access)) != 0);
  }

  // Postconditions:

  if(xauto_access)
  {
    release_access();
  }

  // Exit

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
contains_poset(const scoped_index& xid, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  if(xauto_access)
  {
    get_read_access();
  }

  // Body:

  return contains_poset<P>(xid.hub_pod(), xauto_access);
}

template<typename P>
bool
sheaf::namespace_poset::
contains_poset(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  bool result = contains_poset(xpath, xauto_access);
  if(result)
  {
    result = (dynamic_cast<P*>(&member_poset(xpath, xauto_access)) != 0);
  }

  // Postconditions:
  
  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
contains_path(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:


  // Body:

  bool result = contains_path(xpath, xauto_access);
  if(result)
  {
    result = (dynamic_cast<P*>(&member_poset(xpath, xauto_access)) != 0);
  }

  // Postconditions:
  
  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
path_is_auto_read_accessible(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = 
    contains_path<P>(xpath, xauto_access) &&
    member_poset(xpath, xauto_access).state_is_auto_read_accessible(xauto_access);  

  // Postconditions:

  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
path_is_available(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = !contains_path(xpath, xauto_access) || contains_path<P>(xpath, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = 
    contains_path<P>(xpath, xauto_access) &&
    member_poset(xpath, xauto_access).state_is_auto_read_write_accessible(xauto_access);  

  // Postconditions:

  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
path_is_auto_read_available(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = !contains_path(xpath, xauto_access);
  
  if(!result)
  {
    P* lhost = dynamic_cast<P*>(&member_poset(xpath, xauto_access));
    result = (lhost != 0) && lhost->state_is_auto_read_accessible(xauto_access);  
  }

  // Postconditions:

  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
path_is_auto_read_write_available(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = !contains_path(xpath, xauto_access);
  
  if(!result)
  {
    P* lhost = dynamic_cast<P*>(&member_poset(xpath, xauto_access));
    result = (lhost != 0) && lhost->state_is_auto_read_write_accessible(xauto_access);  
  }

  // Postconditions:

  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible(const string& xname, const arg_list& xargs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = xargs.contains_arg(xname);
  if(result)
  {
    primitive_value lval = xargs.value(xname);
    result = (lval.id() == C_STRING);
    if(result)
    {
      poset_path lpath(lval);
      result = !lpath.empty();
      if(result)
      {
	result = path_is_auto_read_accessible<P>(lpath, xauto_access);
      }
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible(const string& xname, const arg_list& xargs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = xargs.contains_arg(xname);
  if(result)
  {
    primitive_value lval = xargs.value(xname);
    result = (lval.id() == C_STRING);
    if(result)
    {
      poset_path lpath(lval);
      result = !lpath.empty();
      if(result)
      {
	result = path_is_auto_read_write_accessible<P>(lpath, xauto_access);
      }
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
arg_is_auto_read_available(const string& xname, const arg_list& xargs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = xargs.contains_arg(xname);
  if(result)
  {
    primitive_value lval = xargs.value(xname);
    result = (lval.id() == C_STRING);
    if(result)
    {
      poset_path lpath(lval);
      result = !lpath.empty();
      if(result)
      {
	result = path_is_auto_read_available<P>(lpath, xauto_access);
      }
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

template<typename P>
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available(const string& xname, const arg_list& xargs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = xargs.contains_arg(xname);
  if(result)
  {
    primitive_value lval = xargs.value(xname);
    result = (lval.id() == C_STRING);
    if(result)
    {
      poset_path lpath(lval);
      result = !lpath.empty();
      if(result)
      {
	result = path_is_auto_read_write_available<P>(lpath, xauto_access);
      }
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// GLOBAL ATTRIBUTES FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// SCHEMA FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// MEMBERSHIP FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// DEBUGGING FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


#endif // ifndef NAMESPACE_POSET_IMPL_H
