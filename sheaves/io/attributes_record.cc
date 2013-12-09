
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

// Implementation for class attributes_record

#include "attributes_record.h"

#include "assert_contract.h"
#include "namespace_poset.h"
#include "poset.h"

using namespace std;

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

// Copy constructor
///
sheaf::attributes_record::
attributes_record(const attributes_record& xother)
    : variable_length_record(xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}



// Virtual constructor
///
sheaf::attributes_record*
sheaf::attributes_record::
clone() const
{
  attributes_record* result = 0;

  // Preconditions:

  // Body:

  is_abstract();


  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


// Destructor
///
sheaf::attributes_record::
~attributes_record()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}


// Class invariant
///
bool
sheaf::attributes_record::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(variable_length_record::invariant());

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

// Conformance test
///
bool
sheaf::attributes_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const attributes_record*>(other) != 0;

  // Postconditions:

  return result;

}



// ATTRIBUTES_RECORD INTERFACE


///
sheaf::attributes_record::
attributes_record(poset_scaffold& xscaffold)
    : variable_length_record(xscaffold)
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
void
sheaf::attributes_record::
internalize(hdf_buf_type* xhdf_buffer)
{

  // Preconditions:

  require(!scaffold().structure().is_external() ? scaffold().structure().state_is_read_write_accessible() : true);

  // Body:

  // Initialize the external buffer from the HDF buffer.

  transfer_HDF_to_external_buffer(xhdf_buffer);

  // Convert the external buffer to internal format
  // and place the result in the internal buffer

  convert_external_buffer_to_internal_buffer();

  // Transfer the internal buffer to the poset scaffold.

  transfer_internal_buffer_to_poset();

  // Postconditions:

  ensure(is_internal());

  // Exit

  return ;
}


///
void
sheaf::attributes_record::
externalize(hdf_buf_type* xhdf_buffer)
{

  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  // Initialize the internal buffer.

  transfer_poset_to_internal_buffer();

  // Convert the internal buffer to external form
  // and place the result in the external buffer.

  convert_internal_buffer_to_external_buffer();

  // Transfer the external buffer to HDF

  transfer_external_buffer_to_HDF(xhdf_buffer);

  // Postconditions:

  ensure(is_external());

  // Exit

  return;
}



///
void
sheaf::attributes_record::
transfer_HDF_to_external_buffer(hdf_buf_type* xbuf)
{
  // Preconditions:

  require(xbuf != 0);

  // Body:

  /// @hack the hdf type H5T_C_S1 with len set to H5T_VARIABLE hides the
  /// hdf variable length data type hvl_t, so this class doesn't quite fit the
  /// structure provided by base class variable_length_record. Make it work anyway.
  /// See also attributes_record_set::create_dataset.

  put_buf(*xbuf, strlen(*xbuf));

  put_is_external(true);
  put_is_internal(false);

  // Postconditions:

  ensure(buf() == *xbuf);
  ensure(buf_ub() == strlen(*xbuf));
  ensure(is_external());
  ensure(!is_internal());

  // Exit

  return;
}


///
void
sheaf::attributes_record::
transfer_external_buffer_to_HDF(hdf_buf_type* xbuf)
{
  // Preconditions:

  require(xbuf != 0);
  require(is_external());

  // Body:

  /// @hack the hdf type H5T_C_S1 with len set to H5T_VARIABLE hides the
  /// hdf variable length data type hvl_t, so this class doesn't quite fit the
  /// structure provided by base class variable_length_record. Make it work anyway.
  /// See also attributes_record_set::create_dataset.

  *xbuf = reinterpret_cast<hdf_buf_type>(buf());

  // Postconditions:

  ensure(*xbuf == buf());

  // Exit

  return;
}


///
void
sheaf::attributes_record::
transfer_internal_buffer_to_poset()
{
  // Preconditions:

  require(is_internal());
  require(!scaffold().structure().is_external() ?
          scaffold().structure().state_is_read_write_accessible() :
          true);
  require(scaffold().name_space()->state_is_read_accessible());


  // Body:

  is_abstract();

  // Postconditions:

  ensure(scaffold().internal_schema().is_attached());
  ensure(scaffold().transfer_schema().is_attached());
  ensure(scaffold().external_schema().is_attached());

  // Exit

  return;
}



///
void
sheaf::attributes_record::
transfer_poset_to_internal_buffer()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_internal());
  ensure(!is_external());

  // Exit

  return;
}

///
void
sheaf::attributes_record::
convert_external_buffer_to_internal_buffer()
{
  // Preconditions:

  require(is_external());

  // Body:


  _str_buf.append(static_cast<char *>(buf()), buf_ub());

  put_is_internal(true);

  // Postconditions:

  ensure(invariant());
  ensure(is_internal());

  // Exit

  return;
}


///
void
sheaf::attributes_record::
convert_internal_buffer_to_external_buffer()
{
  // Preconditions:

  require(is_internal());

  // Body:

  // "External" buffer is C string of internal buffer.

  put_buf(_str_buf.c_str(), _str_buf.size());
  put_delete_buffer(false);
  put_is_external(true);

  // Postconditions:

  ensure(invariant());
  ensure(is_external());

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS
