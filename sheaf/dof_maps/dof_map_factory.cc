
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

// Implementation for class dof_map_factory

#include "ComLimitPoint/sheaf/dof_map_factory.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/poset_dof_map.h"

using namespace std;

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

// ===========================================================
// DOF_MAP_FACTORY FACET
// ===========================================================

///
sheaf::dof_map_factory::
~dof_map_factory()
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
sheaf::poset_dof_map*
sheaf::dof_map_factory::
new_dof_map(const std::string& xclient_class_name, dof_tuple_type xsheaf_base_class_id)
{
  poset_dof_map* result = 0;

  // Preconditions:

  require(contains_prototype(xclient_class_name) ||
          contains_prototype(xsheaf_base_class_id));

  // Body:

  if(!xclient_class_name.empty())
  {
    // Class name given.

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
  }
  else
  {
    // Class name not given; clone sheaf base class

    result = _sheaf_prototypes_map[xsheaf_base_class_id]->clone();
  }

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_initialized());

  // Exit:

  return result;
}

///
void
sheaf::dof_map_factory::
insert_prototype(const poset_dof_map* xprototype)
{
  // Preconditions:

  require(xprototype != 0);
  require(!xprototype->is_initialized());

  // Body:

  // If the map already contains a prototype for the
  // given class name, this insert will do nothing.
  // For this reason, the postcondition does not ensure
  // the prototype == xprototype.

  string lclass_name = xprototype->class_name();

#ifdef DIAGNOSTIC_OUTPUT

  cout << "in dof_map_factory::insert_prototype lclass_name = "
  << lclass_name
  << endl;
#endif

  prototypes_map_type::value_type lval(lclass_name, const_cast<poset_dof_map*>(xprototype));
  _prototypes_map.insert(lval);

  // Postconditions:

  ensure(contains_prototype(xprototype->class_name()));

  // Exit:

  return;
}

///
void
sheaf::dof_map_factory::
insert_prototype(dof_tuple_type xtype_id, const poset_dof_map* xprototype)
{
  // Preconditions:

  require(xprototype != 0);
  require(!xprototype->is_initialized());

  // Body:

   _sheaf_prototypes_map[xtype_id] =  const_cast<poset_dof_map*>(xprototype);

  // Postconditions:

  ensure(contains_prototype(xtype_id));

  // Exit:

  return;
}

///
void
sheaf::dof_map_factory::
delete_prototype(const std::string& xclass_name)
{
  // Preconditions:

  // Body:

  if(!xclass_name.empty())
  {
    prototypes_map_type::iterator itr = _prototypes_map.find(xclass_name);
    if(itr != _prototypes_map.end())
    {
      poset_dof_map* lproto = itr->second;
      _prototypes_map.erase(itr);

      assertion(!lproto->is_initialized());

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
sheaf::dof_map_factory::
contains_prototype(const std::string& xclass_name) const
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
sheaf::dof_map_factory::
contains_prototype(dof_tuple_type xtype_id) const
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
sheaf::dof_map_factory::
dof_map_factory()
{

  // Preconditions:


  // Body:

  // Initialize the sheaf prototypes map.

  _sheaf_prototypes_map.reserve(NOT_A_DOF_TUPLE_TYPE);
  _sheaf_prototypes_map.set_ct(NOT_A_DOF_TUPLE_TYPE);
  _sheaf_prototypes_map.assign(0);

  // Prototypes are created in the private make_prototype routines of each
  // descendant of class poset_dof_map..

  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

