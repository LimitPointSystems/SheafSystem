
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

// Implementation for class dof_tuple_domain_offsets_record

#include "SheafSystem/dof_tuple_domain_offsets_record.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_sstream.h"

using namespace std;

// =============================================================================
// ANY FACET
// =============================================================================

///
sheaf::dof_tuple_domain_offsets_record*
sheaf::dof_tuple_domain_offsets_record::
clone() const
{
  dof_tuple_domain_offsets_record* result;

  // Preconditions:

  // Body:

  result = new dof_tuple_domain_offsets_record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
bool
sheaf::dof_tuple_domain_offsets_record::
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
sheaf::dof_tuple_domain_offsets_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const dof_tuple_domain_offsets_record*>(other) != 0;

  // Postconditions:

  return result;

}


// =============================================================================
// DOF_TUPLE_DOMAIN_OFFSETS_RECORD FACET
// =============================================================================

///
sheaf::dof_tuple_domain_offsets_record::
dof_tuple_domain_offsets_record(poset_scaffold& xscaffold)
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
sheaf::dof_tuple_domain_offsets_record::
dof_tuple_domain_offsets_record(const dof_tuple_domain_offsets_record& xother)
    : attributes_record(xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}



///
sheaf::dof_tuple_domain_offsets_record::
~dof_tuple_domain_offsets_record()
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
sheaf::dof_tuple_domain_offsets_record::
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

  // Transfer the domain offsets into the scaffold name map.

  record_index::pod_type ldomain_offset[3];
  while(lstream >> ldomain_offset[0])
  {
    // Read remaining domain offset.

    lstream >> ldomain_offset[1];
    lstream >> ldomain_offset[2];

    // Create the key of the domain offset map.

    typedef poset_scaffold::dof_tuple_domain_offsets_type::key_type key_type;
    key_type lkey(ldomain_offset[0], ldomain_offset[1]);

    // Create the domain offset map value.

    typedef poset_scaffold::dof_tuple_domain_offsets_type::value_type value_type;
    value_type lval(lkey, ldomain_offset[2]);

    scaffold().dof_tuple_domain_offsets().insert(lval);
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::dof_tuple_domain_offsets_record::
transfer_poset_to_internal_buffer()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  stringstream lstream;

  lstream << "Dof tuple domain offsets:" << endl;

  poset_scaffold::dof_tuple_domain_offsets_type::iterator itr;

  for(itr  = scaffold().dof_tuple_domain_offsets().begin();
      itr != scaffold().dof_tuple_domain_offsets().end();
      itr++)
  {
    lstream << itr->first.first << " "
	    << itr->first.second << " "
	    << itr->second << endl;
  }

  // Have to copy stringstream to string
  // because can't get C string from stringstream.
  // Could use stringstream, but that's error-prone and not portable.

  _str_buf = lstream.str();

  put_is_internal(true);
  put_is_external(false);

  // Postconditions:

  ensure(is_internal());
  ensure(!is_external());

  // Exit

  return;
}




