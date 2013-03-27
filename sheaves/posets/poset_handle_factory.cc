// $RCSfile: poset_handle_factory.cc,v $ $Revision: 1.15 $ $Date: 2013/01/12 17:17:42 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

 

// Implementation for class poset_handle_factory

#include "poset_handle_factory.h"

#include "assert_contract.h"
#include "error_message.h"
#include "namespace_poset.h"
#include "poset.h"
#include "poset_type.h"
#include "primitives_poset.h"
#include "primitives_poset_schema.h"
#include "refinable_poset.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

// ===========================================================
// POSET_HANDLE_FACTORY FACET
// ===========================================================

///
sheaf::poset_handle_factory::
poset_handle_factory()
{

  // Preconditions:


  // Body:

  // Initialize the sheaf prototypes map.

  _sheaf_prototypes_map.reserve(NOT_A_POSET_TYPE);
  _sheaf_prototypes_map.set_ct(NOT_A_POSET_TYPE);
  _sheaf_prototypes_map.assign(0);

  // Prototypes are created in the private make_prototype routines of each
  // descendant of class poset_state_handle.

  // Postconditions:


  // Exit:

  return;
}


///
sheaf::poset_handle_factory::
~poset_handle_factory()
{

  // Preconditions:


  // Body:

  // Delete all the prototypes.

  prototypes_map_type::iterator itr = _prototypes_map.begin();
  while(itr != _prototypes_map.end())
  {
    delete itr->second;
    ++itr;
  }
  _prototypes_map.clear();

  // Don't need to delete the entries in _sheaf_prototypes_map
  // because they are all duplicates that have just been deleted.

  // Postconditions:

  ensure(unexecutable("All prototypes have been deleted."));

  // Exit:

  return;
}

///
sheaf::poset_state_handle*
sheaf::poset_handle_factory::
new_poset_handle(const string& xclient_class_name,
                 poset_type xsheaf_base_class_id)
{
  poset_state_handle* result = 0;

  // Preconditions:

  require(contains_prototype(xclient_class_name) ||
          contains_prototype(xsheaf_base_class_id));

  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  cout << SOURCE_CODE_LOCATION
  << " class name= " << xclient_class_name
  << " class id= " << xsheaf_base_class_id
  << endl;
#endif

  prototypes_map_type::iterator itr = _prototypes_map.find(xclient_class_name);
  if( itr != _prototypes_map.end())
  {
    // Found a prototype; clone it.

    result = itr->second->clone();
  }
  else
  {
    // No client prototype; clone sheaf base class

    result = _sheaf_prototypes_map[xsheaf_base_class_id]->clone();
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "result class: " << result->class_name() << endl;
#endif

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_attached());

  // Can't ensure the following because type_id() requires read access.

  // ensure(result->class_name() == xclass_name ||
  //  result->type_id() == xsheaf_base_class_id);

  // Exit:

  return result;
}

///
void
sheaf::poset_handle_factory::
insert_prototype(const poset_state_handle* xprototype)
{
  // Preconditions:

  require(xprototype != 0);
  require(!xprototype->is_attached());

  // Body:

  // If the map already contains a prototype for the
  // given class name, this insert will do nothing.
  // For this reason, the postcondition does not ensure
  // the prototype == xprototype.

  prototypes_map_type::value_type lval(xprototype->class_name(), const_cast<poset_state_handle*>(xprototype));
  _prototypes_map.insert(lval);

  // Postconditions:

  ensure(contains_prototype(xprototype->class_name()));

  // Exit:

  return;
}

///
void
sheaf::poset_handle_factory::
delete_prototype(const string& xclass_name)
{
  // Preconditions:

  // Body:

  if(!xclass_name.empty())
  {
    prototypes_map_type::iterator itr = _prototypes_map.find(xclass_name);
    if(itr != _prototypes_map.end())
    {
      poset_state_handle* lproto = itr->second;
      _prototypes_map.erase(itr);

      assertion(!lproto->is_attached());

      delete lproto;
    }
  }

  // Postconditions:

  ensure(!contains_prototype(xclass_name));

  // Exit:

  return;
}

 

///
bool
sheaf::poset_handle_factory::
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
}

 

///
bool
sheaf::poset_handle_factory::
contains_prototype(poset_type xtype_id) const
{
  bool result;

  // Preconditions:


  // Body:

  result = (_sheaf_prototypes_map[xtype_id] != 0);

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
// PRIVATE MEMBER FUNCTIONS
// ===========================================================


///
void
sheaf::poset_handle_factory::
insert_prototype(poset_type xtype_id, const poset_state_handle* xprototype)
{
  // Preconditions:

  require(xprototype != 0);
  require(!xprototype->is_attached());

  // Body:

   _sheaf_prototypes_map[xtype_id] = const_cast<poset_state_handle*>(xprototype);

  // Postconditions:

  ensure(contains_prototype(xtype_id));

  // Exit:

  return;
}



// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

