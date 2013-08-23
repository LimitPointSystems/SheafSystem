
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

// Implementation for class data_type_map

 

#include "data_type_map.h"
#include "assert_contract.h"
#include "sheaf_file.h"

#include "data_converter.h"

// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS


///
sheaf::data_type_map*
sheaf::data_type_map::
clone() const
{
  data_type_map* result;

  // Preconditions:

  // Body:

  result = new data_type_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
bool
sheaf::data_type_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::data_type_map::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const data_type_map*>(other) != 0;

  // Postconditions:

  return result;

}



// ===========================================================
// DATA_TYPE_MAP FACET
// ===========================================================

///
sheaf::data_type_map::
~data_type_map()
{

  // Preconditions:

  // Body:

  // Do nothing.
  // All the data converters and HDF objects are deleted in
  // descendant file_data_type_map.

  // Postconditions:

  // Exit:

  return;
}

///
sheaf::data_converter*
sheaf::data_type_map::
operator[](int xi) const
{
  data_converter* result;

  // Preconditions:

  require(is_primitive_index(xi));

  // Body:

  result = _converters[xi];

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

// ===========================================================
// PROTECTED MEMBER FUNCTIONS
// ===========================================================

sheaf::data_type_map::
data_type_map()
{

  // Preconditions:


  // Body:

  _file = -1;
  _max_internal_size = 0;
  _max_external_size = 0;

  // Postconditions:

  // Exit:

  return;
}

///
sheaf::data_type_map::
data_type_map(const data_type_map& xother)
{

  // Preconditions:

  // Body:

  for(int i=PRIMITIVE_TYPE_BEGIN; i<PRIMITIVE_TYPE_END; i++)
  {
    _converters[i] = xother._converters[i]; ///@issue need reference counting here.
  }

  _file = xother._file;
  _max_internal_size = xother._max_internal_size;
  _max_external_size = xother._max_external_size;

  // Postconditions:

  ensure(invariant());
}

