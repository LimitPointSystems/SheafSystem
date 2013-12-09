
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

// Implementation for class schema_descriptor

#include "schema_descriptor.h"
#include "assert_contract.h"
#include "std_string.h"

using namespace std;

// ===========================================================
// ANY FACET
// ===========================================================


///
bool
sheaf::schema_descriptor::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const schema_descriptor*>(other) != 0;

  // Postconditions:

  return result;
}

///
sheaf::schema_descriptor*
sheaf::schema_descriptor::
clone() const
{
  schema_descriptor* result;

  // Preconditions:

  // Body:

  result = new schema_descriptor();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}



///
bool
sheaf::schema_descriptor::
operator==(const schema_descriptor& xother) const
{
  bool result;

  // Preconditions:


  // Body:

  result =
    (name == xother.name) &&
    (type == xother.type) &&
    (is_table_dof == xother.is_table_dof);

  // Postconditions:


  // Exit:

  return result;
}

///
bool
sheaf::schema_descriptor::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:



    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}



// ===========================================================
// SCHEMA_DESCRIPTOR FACET
// ===========================================================

///
sheaf::schema_descriptor::
schema_descriptor()
{

  // Preconditions:


  // Body:

  type = NOT_A_PRIMITIVE_TYPE;
  is_table_dof = false;

  // Postconditions:

  ensure(invariant());
  ensure(name.empty());
  ensure(type == NOT_A_PRIMITIVE_TYPE);
  ensure(!is_table_dof);

  // Exit:

  return;
}


///
sheaf::schema_descriptor::
schema_descriptor(const schema_descriptor& xother)
{

  // Preconditions:


  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());
  ensure(*this == xother);

  // Exit:

  return;
}

///
sheaf::schema_descriptor::
schema_descriptor(const std::string& xname, primitive_type xtype, bool xis_table_dof)
{
  // Preconditions:


  // Body:

  name = xname;
  type = xtype;
  is_table_dof = xis_table_dof;

  // Postconditions:

  ensure(name == xname);
  ensure(type == xtype);
  ensure(is_table_dof == xis_table_dof);

  // Exit:

  return;
}


///
sheaf::schema_descriptor::
~schema_descriptor()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

///
std::ostream&
sheaf::operator<<(std::ostream& os, const schema_descriptor& xsd)
{
  // Preconditions:


  // Body:

  os << " " << xsd.name
  << " " << xsd.type
  << " " << boolalpha << xsd.is_table_dof << noboolalpha;

  // Postconditions:


  // Exit:

  return os;
}


///
std::istream&
sheaf::operator>>(std::istream& is, schema_descriptor& xsd)
{
  // Preconditions:


  // Body:

  if(is)
  {
    is >> xsd.name;
    if(is)
    {
      is >> xsd.type;
      if(is)
      {
        is >> boolalpha >> xsd.is_table_dof >> noboolalpha;
      }
    }
  }

  // Postconditions:

  // Exit:

  return is;
}

size_t
sheaf::
deep_size(const schema_descriptor& xsd, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}

