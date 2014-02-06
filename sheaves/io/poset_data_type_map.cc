
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

// Implementation for class poset_data_type_map

#include "poset_data_type_map.h"

#include "assert_contract.h"
#include "data_converter.h"

// ===========================================================
// ANY FACET
// ===========================================================

///
sheaf::poset_data_type_map*
sheaf::poset_data_type_map::
clone() const
{
  poset_data_type_map* result;

  // Preconditions:

  // Body:

  result = new poset_data_type_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
bool
sheaf::poset_data_type_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && data_type_map::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    result = result && ((0 <= _toc_index) && (_toc_index < PRIMITIVE_TYPE_END));
    result = result && ((0 <= _dof_tuple_id_index) && (_dof_tuple_id_index < PRIMITIVE_TYPE_END));
    result = result && ((0 <= _offset_index) && (_offset_index < PRIMITIVE_TYPE_END));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::poset_data_type_map::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const poset_data_type_map*>(other) != 0;

  // Postconditions:

  return result;

}



// ===========================================================
// POSET_DATA_TYPE_MAP FACET
// ===========================================================


///
sheaf::poset_data_type_map::
poset_data_type_map(const data_type_map& xprim_map)
    : data_type_map(xprim_map)
{

  // Preconditions:

  // Body:

  // Use default values for member record types.

  _toc_index          = CHAR;
  _dof_tuple_id_index = INT;
  _offset_index       = SIZE_TYPE;

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

///
sheaf::poset_data_type_map::
poset_data_type_map(const poset_data_type_map& xother)
    : data_type_map(xother)
{

  // Preconditions:

  // Body:

  _toc_index = xother._toc_index;
  _dof_tuple_id_index = xother._dof_tuple_id_index;
  _offset_index = xother._offset_index;

  // Postconditions:

  ensure(invariant());
}



///
sheaf::poset_data_type_map::
~poset_data_type_map()
{

  // Preconditions:

  // Body:

  // Do nothing.
  // All the data converters and HDF objects are owned
  // by the file data type map; it will delete them.

  // Postconditions:

  // Exit:

  return;
}


///
void
sheaf::poset_data_type_map::
// put_member_record_type_aliases(const scoped_index& xtoc_index,
//                                const scoped_index& xdof_tuple_id_index,
//                                const scoped_index& xoffset_index)
put_member_record_type_aliases(int xtoc_index,
                               int xdof_tuple_id_index,
                               int xoffset_index)
{

  // Preconditions:

  require(is_primitive_index(xtoc_index));
  require(is_primitive_index(xdof_tuple_id_index));
  require(is_primitive_index(xoffset_index));

  // Body:

  _toc_index          = xtoc_index;
  _dof_tuple_id_index = xdof_tuple_id_index;
  _offset_index       = xoffset_index;

  // Postconditions:

  ensure(invariant());
}




// PRIVATE MEMBER FUNCTIONS

sheaf::poset_data_type_map::
poset_data_type_map()
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}
