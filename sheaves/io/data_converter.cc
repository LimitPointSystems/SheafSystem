
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

// Implementation for class data_converter

 

#include "data_converter.h"

#include "assert_contract.h"
#include "error_message.h"
#include "primitive_attributes.h"
#include "sheaf_file.h"
#include "std_iostream.h"

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS


// Virtual constructor
///
sheaf::data_converter*
sheaf::data_converter::
clone() const
{
  data_converter* result;

  // Preconditions:

  // Body:

  result = new data_converter();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


// Destructor
///
sheaf::data_converter::
~data_converter()
{

  // Preconditions:

  // Body:

  // HDF types closed by data_type_map, which created/opened them.

  // Delete the result buffer

  if(_result != 0)
  {
    delete [] static_cast<char*>(_result);
  }

  _result = 0;

  // Close the transfer property list

  H5Pclose(_transfer_plist);

  /// @issue H5Pclose seems to always return failure.

  //   if(H5Pclose(_transfer_plist) < 0);
  //   {
  //     // Close failed.

  //     post_fatal_error_message("can't close transfer property list");
  //   }

  // Postconditions:

  // Exit:

  return;
}


// Class invariant
///
bool
sheaf::data_converter::
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

    result = result && (_result != 0);
    result = result && (result_size() == max_size());

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
sheaf::data_converter::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const data_converter*>(other) != 0;

  // Postconditions:

  return result;

}



// DATA_CONVERTER INTERFACE

///
sheaf::data_converter::
data_converter(hid_t xexternal_type,
               hid_t xinternal_type,
               int xinternal_index)
{

  // Preconditions:

  require(is_primitive_index(xinternal_index));

  // Initialize the properties of the external type.

  _external_type = xexternal_type;
  _external_size = H5Tget_size(_external_type);

  // Initialize the properties of the internal type.

  _internal_type = xinternal_type;
  _internal_index = xinternal_index;
  _internal_size = H5Tget_size(_internal_type);
  primitive_descriptor lprim_desc = primitive_attributes::descriptor(_internal_index);

  // sheaf and hdf must agree on size of internal type.

  if(!is_string_type() && lprim_desc.size != _internal_size)
  {
    post_fatal_error_message("fatal conflict between HDF internal type and sheaf primitive type");
  }

  _internal_alignment = lprim_desc.alignment;

  // Create the result buffer

  _result_size   = max_size();
  _result = new char[_result_size];

  // Create the transfer property list.

  _transfer_plist = H5Pcreate(H5P_DATASET_XFER);
  if(_transfer_plist < 0)
  {
    post_fatal_error_message("Unable to create transfer property list.");
  }

  // Determine whether conversion is needed.

  htri_t ltri = H5Tequal(_internal_type, _external_type);
  if(ltri > 0)
  {
    // Types are equal, no conversion required.

    _conversion_required = false;
  }
  else if(ltri == 0)
  {
    // Types are not equal, conversion required.

    _conversion_required = true;
  }
  else
  {
    // Error determining equality.

    post_fatal_error_message("error while checking for type equality");
  }

  // Postconditions:

  ensure(invariant());
}


///
void
sheaf::data_converter::
externalize(const void* xint_buf,
            size_t xint_buf_ub,
            void* xext_buf,
            size_t xext_buf_ub,
            int xitem_ct)
{
  // Preconditions:

  require(xitem_ct > 0);
  require(xint_buf != 0);
  require(is_string_type() ? xint_buf_ub >= xitem_ct*sizeof(char*) : xint_buf_ub >= xitem_ct*internal_size());
  require(xext_buf != 0);
  require(is_string_type() ? xext_buf_ub >= string_length_total(xint_buf, xitem_ct) : xext_buf_ub >= xitem_ct*max_size());
  require(is_string_type() ? external_size() == 1 : !internal_size_greater());


  // Body:

  if(is_string_type())
  {
    char** lint_buf = reinterpret_cast<char**>(const_cast<void*>(xint_buf));
    char* lext_buf = reinterpret_cast<char*>(xext_buf);

    for(int i=0; i<xitem_ct; i++)
    {
      // Get the length of the string; includes terminator

      size_t lstrlen = string_length(lint_buf[i]);

      // Copy the string to the external buffer;
      // Assumes !internal_size_greater

      (void) memcpy(lext_buf, lint_buf[i], lstrlen);
      externalize(lext_buf, lstrlen, lstrlen);

      // Move the external buffer pointer past the string.
      // Assumes external_size() == 1;

      lext_buf += lstrlen;
    }
  }
  else
  {
    // Copy the data to the external buffer and
    // then convert it to external format.

    (void) memcpy(xext_buf, xint_buf, xitem_ct*_internal_size);
    externalize(xext_buf, xext_buf_ub, xitem_ct);
  }

  /// @todo finish implementation ; deal with error status

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::data_converter::
externalize(void* xext_buf, size_t xext_buf_ub, int xitem_ct)
{
  // Preconditions:

  require(xitem_ct > 0);
  require(xext_buf != 0);
  require(xext_buf_ub >= xitem_ct*max_size());

  // Body:

  /// @issue we need to make this routine inlineable.

  // Convert the data, if required.

  if(conversion_required())
  {
    herr_t lerr = H5Tconvert(_internal_type, _external_type, xitem_ct, xext_buf, 0, _transfer_plist);
  }

  /// @todo finish implementation ; deal with error status

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::data_converter::
externalize(const void* xint_buf, size_t xint_buf_ub)
{
  // Preconditions:

  require(xint_buf != 0);
  require(xint_buf_ub >= internal_size());
  require(result_size() >= max_size());

  // Body:

  /// @issue we need to make this routine inlineable.

  // Copy input buffer to result buffer.

  (void) memcpy(_result, xint_buf, _internal_size);

  // Convert the data, if required.

  if(conversion_required())
  {
    herr_t lerr = H5Tconvert(_internal_type, _external_type, 1, _result, 0, _transfer_plist);
  }

  /// @todo finish implementation ; deal with error status

  // Postconditions:

  // Exit

  return;
}

 

///
size_t
sheaf::data_converter::
string_length(const char* xbuf)
{
  size_t result;

  // Preconditions:

  require(xbuf != 0);

  // Body:

  result = strlen(xbuf)+1;

  /// @todo extend to other types of terminated strings.

  // Postconditions:

  ensure(result > 0);

  // Exit

  return result;
}

 

///
size_t
sheaf::data_converter::
string_length_total(const void* xbuf, int xitem_ct) const
{
  size_t result = 0;

  // Preconditions:

  require(is_string_type());

  // Body:

  char** lbuf = reinterpret_cast<char**>(const_cast<void*>(xbuf));

  // Add up the length of the strings in xbuf

  for(int i=0; i<xitem_ct; i++)
  {
    result += string_length(lbuf[i]);
  }

  // Postconditions:

  ensure(result > 0);

  // Exit

  return result;
}

///
void
sheaf::data_converter::
internalize(const void* xext_buf,
            size_t xext_buf_ub,
            void* xint_buf,
            size_t xint_buf_ub,
            int xitem_ct)
{
  // Preconditions:

  require(xitem_ct > 0);
  require(xext_buf != 0);
  require(is_string_type() ? true : xext_buf_ub >= xitem_ct*external_size());
  require(xint_buf != 0);
  require(is_string_type() ? xint_buf_ub >= xitem_ct*internal_size() : xint_buf_ub >= xitem_ct*max_size());
  require(is_string_type() ? external_size() == 1 : !external_size_greater());

  // Body:

  /// @issue we need to make this routine inlineable.

  // Copy input buffer to output buffer.
  //
  // Note:
  // To be useful, the converted, internalized data
  // must be properly aligned for the internal type.
  // But there is no way to ensure that the space in
  // the external buffer is properly aligned, so even
  // if we convert in place, we'll have to copy the
  // result to another buffer sooner or later.
  // The assumption here is that xint_buf is
  // properly aligned for the internal type.
  //
  // Note: The C++ standard ensures that char array is
  // allocated with most restrictive alignment, so
  // _result will match any alignment.

  if(is_string_type())
  {
    char* lext_buf = reinterpret_cast<char*>(const_cast<void*>(xext_buf));
    char** lint_buf = reinterpret_cast<char**>(xint_buf);

    for(int i=0; i<xitem_ct; i++)
    {
      // Get the length of the string

      size_t lstrlen = string_length(lext_buf);

      // Allocate the internal string;
      // assumes internal_size() == 1
      /// @error where does this string get deleted?

      char* lstring = new char[lstrlen];

      // Copy the data to the internal string and
      // then convert it to internal format.
      // Assumes external_size() == 1.

      (void) strncpy(lstring, lext_buf, lstrlen);
      internalize(lstring, lstrlen, lstrlen);

      // Make the internal buffer point at the internal string.

      lint_buf[i] = lstring;

      // Move the external buffer pointer to the next string.
      // Assumes external_size() == 1.

      lext_buf += lstrlen;
    }
  }
  else
  {
    // Copy the data to the internal buffer and
    // then convert it to internal format.

    (void) memcpy(xint_buf, xext_buf, xitem_ct*_external_size);
    internalize(xint_buf, xint_buf_ub, xitem_ct);
  }


  /// @todo finish implementation; handle error return

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::data_converter::
internalize(void* xbuf, size_t xbuf_ub, int xitem_ct)
{
  // Preconditions:

  require(xitem_ct > 0);
  require(xbuf != 0);
  require(xbuf_ub >= xitem_ct*max_size());

  // Body:

  /// @issue we need to make this routine inlineable.

  // Convert the data in place, if required.

  if(conversion_required())
  {
    herr_t lerr = H5Tconvert(_external_type, _internal_type, xitem_ct, xbuf, 0, _transfer_plist);
  }

  /// @todo finish implementation; handle error return

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::data_converter::
internalize(void* xbuf, size_t xbuf_ub)
{
  // Preconditions:

  require(xbuf != 0);
  require(xbuf_ub >= external_size());
  require(result_size() >= max_size());


  // Body:

  /// @issue we need to make this routine inlineable.


  (void) memcpy(_result, xbuf, _external_size);

  // Convert the data, if required.

  if(conversion_required())
  {
    herr_t lerr = H5Tconvert(_external_type, _internal_type, 1, _result, 0, _transfer_plist);
  }

  /// @todo finish implementation; handle error return

  // Postconditions:

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS

// Default constructor
// Private to prevent default construction

sheaf::data_converter::
data_converter()
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
sheaf::data_converter::
data_converter(const data_converter& xother)
{

  // Preconditions:


  // Body:

  data_converter& lother = const_cast<data_converter&>(xother);
 
  _external_type = lother.external_type();
  _external_size = lother.external_size();

  _internal_type = lother.internal_type();
  _internal_index = lother.internal_index();
  _internal_size = lother.internal_size();
  _internal_alignment = lother.internal_alignment();

  _result_size = lother.result_size();
  _result = new char[_result_size];

  _transfer_plist = H5Pcreate(H5P_DATASET_XFER);

  // Determine whether conversion is needed.

  htri_t ltri = H5Tequal(_internal_type, _external_type);
  if(ltri > 0)
  {
    // Types are equal, no conversion required.

    _conversion_required = false;
  }
  else if(ltri == 0)
  {
    // Types are not equal, conversion required.

    _conversion_required = true;
  }
  else
  {
    // Error determining equality.

    post_fatal_error_message("error while checking for type equality");
  }

  // Postconditions:

  ensure(invariant());
}
