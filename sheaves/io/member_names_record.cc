
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

// Implementation for class member_names_record

#include "member_names_record.h"

#include "assert_contract.h"
#include "std_sstream.h"

using namespace std;

// =============================================================================
// ANY FACET
// =============================================================================

///
sheaf::member_names_record*
sheaf::member_names_record::
clone() const
{
  member_names_record* result;

  // Preconditions:

  // Body:

  result = new member_names_record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
bool
sheaf::member_names_record::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && attributes_record::invariant();

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
sheaf::member_names_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const member_names_record*>(other) != 0;

  // Postconditions:

  return result;

}


// =============================================================================
// MEMBER_NAMES_RECORD FACET
// =============================================================================

///
sheaf::member_names_record::
member_names_record(poset_scaffold& xscaffold)
    : attributes_record(xscaffold)
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
sheaf::member_names_record::
member_names_record(const member_names_record& xother)
    : attributes_record(xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}



///
sheaf::member_names_record::
~member_names_record()
{

  // Preconditions:

  // Body:

  // Nothing specific to do.
  /// @issue can we just not define this function?

  // Postconditions:

  // Exit:

  return;
}

// =============================================================================
// PROTECTED MEMBER FUNCTIONS
// =============================================================================


///
void
sheaf::member_names_record::
transfer_internal_buffer_to_poset()
{
  // Preconditions:

  require(is_internal());
  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

  // Initialize the stream.

  stringstream lstream(_str_buf);

  // Skip the header line:

  lstream.ignore(numeric_limits<streamsize>::max(), '\n');

  // Transfer the names into the scaffold name map.

  poset_scaffold::member_name_map_type& lname_map = scaffold().member_name_map();
  record_index::pod_type lmbr_id_pod;
  string lname;
  while(lstream >> lmbr_id_pod)
  {
    // Skip the space before the name

    lstream.ignore();

    // The name is the rest of the line,
    // including possible leading or embedded white space.

    getline(lstream, lname);

    // Put the result in the map.

    lname_map.put_entry(lmbr_id_pod, lname, false);
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::member_names_record::
transfer_poset_to_internal_buffer()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  stringstream lstream;

  lstream << "Member names:" << endl;


  poset_scaffold::member_name_map_type& lname_map = scaffold().member_name_map();
  poset_scaffold::member_name_map_type::const_iterator itr;

  for(itr  = lname_map.begin();
      itr != lname_map.end();
      itr++)
  {
    const poset_scaffold::member_name_map_type::name_list_type& lnames = itr->second;
    poset_scaffold::member_name_map_type::const_name_iterator lname_itr = lnames.begin();
    while(lname_itr != lnames.end())
    {
      lstream << itr->first << " " << *lname_itr << endl;
      ++lname_itr;
    }
  }

  // Have to copy stringstream to string
  // because can't get C string from stringstream.
  // Could use strstream, but that's error-prone and not portable.

  _str_buf = lstream.str();

  put_is_internal(true);
  put_is_external(false);

  // Postconditions:

  ensure(is_internal());
  ensure(!is_external());

  // Exit

  return;
}




