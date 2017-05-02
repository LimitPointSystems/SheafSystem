
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

// Implementation for class id_space_names_record

#include "SheafSystem/id_space_names_record.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/index_space_family_iterator.h"
#include "SheafSystem/index_space_interval.h"
#include "SheafSystem/scattered_insertion_index_space_handle.h"
#include "SheafSystem/scattered_insertion_index_space_state.h"
#include "SheafSystem/std_sstream.h"

using namespace std;

// =============================================================================
// ANY FACET
// =============================================================================


sheaf::id_space_names_record*
sheaf::id_space_names_record::
clone() const
{
  id_space_names_record* result;

  // Preconditions:

  // Body:

  result = new id_space_names_record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


bool
sheaf::id_space_names_record::
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

bool
sheaf::id_space_names_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const id_space_names_record*>(other) != 0;

  // Postconditions:

  return result;

}

// =============================================================================
// ID_SPACE_NAMES_RECORD FACET
// =============================================================================

sheaf::id_space_names_record::
id_space_names_record(poset_scaffold& xscaffold)
    : attributes_record(xscaffold)
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::id_space_names_record::
id_space_names_record(const id_space_names_record& xother)
    : attributes_record(xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}

sheaf::id_space_names_record::
~id_space_names_record()
{

  // Preconditions:

  // Body:

  // Nothing specific to do.

  // Postconditions:

  // Exit:

  return;
}

// =============================================================================
// PROTECTED MEMBER FUNCTIONS
// =============================================================================

void
sheaf::id_space_names_record::
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

  // Transfer the names to the poset.

  // It is essential that the names be assigned to id spaces
  // in the same order they appear in the file because the
  // id equivalences in the member records use these id_space values.

  // In particular, it is important to create the id spaces before
  // initialize the member index map, otherwise the file id space
  // will be created out of order.

  /// @issue Reading in the map class name from the file.  Should we
  /// allow this or should we assume that all maps are hash_index_maps.
  /// The only issue is that array_index_map that are not dense are
  /// inefficient.

  poset_state_handle& lposet = scaffold().structure();
  size_type lid_space_ext_id;
  string lid_space_class_name, lid_space_name;

  while(lstream >> lid_space_ext_id)
  {
    // Skip the space before the class name.

    lstream.ignore();

    // Get the class name.

    lstream >> lid_space_class_name;

    // Skip the space before the name

    lstream.ignore();

    // The name is the rest of the line,
    // including possible leading or embedded white space.

    getline(lstream, lid_space_name);

    if(!lposet.member_id_spaces(false).contains(lid_space_name))
    {
      // Create an id space with that name.

      lposet.member_id_spaces(false).new_state(lid_space_name, lid_space_class_name);

      if(lposet.includes_subposet(lid_space_name))
      {
        // A subposet with same name exists, assume this is the
        // id space for the subposet. Attach the subposet to it.

        subposet lsp(&lposet, lid_space_name);
        if(!lsp.has_id_space())
        {
          lsp.attach_id_space();
        }
      } 
    }

    /// @hack Require that the id space is mutable.  See COM-475.

    scattered_insertion_index_space_handle* lid_space =
      &lposet.member_id_spaces(false).get_id_space<scattered_insertion_index_space_handle>(lid_space_name);

    scaffold().id_spaces().force_item(lid_space_ext_id, lid_space);
  }

  // Now we can initialize the member id space.

  scaffold().initialize_member_id_space();

  // Postconditions:

  // Exit

  return;
}

void
sheaf::id_space_names_record::
transfer_poset_to_internal_buffer()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  stringstream lstream;

  lstream << "Id space names:" << endl;

  // Put the names for the persistent, mutsable id spaces in the file.

  poset_state_handle& lposet = scaffold().structure();
  index_space_family_iterator litr(lposet.member_id_spaces(false), true);
  while(!litr.is_done())
  {
    /// @hack Require that the id space is mutable.  See COM-475.

    assertion(lposet.member_id_spaces(false).handle_conforms_to_state<scattered_insertion_index_space_handle>(litr.index()));

    scattered_insertion_index_space_handle& lid_space =
      lposet.member_id_spaces(false).get_id_space<scattered_insertion_index_space_handle>(litr.index());

    lstream << lid_space.index()
	    << " " << lid_space.state().class_name()
	    << " " << lid_space.name()
	    << endl;

    lid_space.release_id_space();

    litr.next();
  }

  // Have to copy stringstream to string
  // because can't get C string from stringstream.

  _str_buf = lstream.str();

  put_is_internal(true);
  put_is_external(false);

  // Postconditions:

  ensure(is_internal());
  ensure(!is_external());

  // Exit

  return;
}



