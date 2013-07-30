
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//



// Implementation for class sheaf_file

#include "sheaf_file.h"

#include "assert_contract.h"
#include "file_data_type_map.h"
#include "error_message.h"

namespace
{
  //
  // Value representing failure for HDF routine.
  // Most HDF routines return "a negative value" for failure.
  //
  const int HDF_FAIL = -1;
}


// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

// Default constructor
///
sheaf::sheaf_file::
sheaf_file()
{

  // Preconditions:


  // Body:

  // _name empty by default

  _hdf_id   = HDF_FAIL;
  _mode     = NONE;
  _type_map = 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


// Copy constructor
///
sheaf::sheaf_file::
sheaf_file(const sheaf_file& xother)
{
  // Preconditions:

  // Body:

  _name     = xother._name;
  _hdf_id   = xother._hdf_id;
  _mode     = xother._mode;
  _type_map = xother._type_map;

  // Postconditions:

  ensure(invariant());
}



// Virtual constructor
///
sheaf::sheaf_file*
sheaf::sheaf_file::
clone() const
{
  sheaf_file* result;

  // Preconditions:

  // Body:

  result = new sheaf_file();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


// Destructor
///
sheaf::sheaf_file::
~sheaf_file()
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
sheaf::sheaf_file::
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

    // is_open implies type_map_defined

    result = result && (is_open() == type_map_defined());

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
sheaf::sheaf_file::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const sheaf_file*>(other) != 0;

  // Postconditions:

  return result;

}



// SHEAF_FILE INTERFACE


///
void
sheaf::sheaf_file::
open(const string &xname, access_mode xmode, bool xclobber)
{
  // Preconditions:

  require(!is_open());
  require(!xname.empty());

  // Body:

  // Save the name

  _name = xname;

  switch(xmode)
  {
  case READ_ONLY:

    // Open the file with read-only access.

    _hdf_id = H5Fopen(_name.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    if(_hdf_id >= 0)
    {
      // File creation succeeded.
      // Store the mode.

      _mode = READ_ONLY;

      // Create the type map.
      // Since the file already exists,
      // do not create external types.

      _type_map = new file_data_type_map(_hdf_id, false);
    }
    else
    {
      // File creation failed.

      //      H5Eprint(stderr);
      H5Eprint1(stderr);
      post_fatal_error_message("unable to open file in READ_ONLY mode");
    }
    break;

  case READ_WRITE:

    // Open the file with read-write access.

    if(xclobber)
    {
      // Delete ("truncate") the file if it already exists.

      _hdf_id = H5Fcreate(_name.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
      if(_hdf_id >= 0)
      {
        // File creation succeeded.
        // Store the mode.

        _mode = READ_WRITE;

        // Create the type map.
        // Since the file is new,
        // force creation of the external types.

        _type_map = new file_data_type_map(_hdf_id, true);
      }
      else
      {
        // File creation failed.

	//        H5Eprint(stderr);
        H5Eprint1(stderr);
        post_fatal_error_message("unable to open file in READ_WRITE mode");
      }
    }
    else
    {
      post_fatal_error_message("no clobber not yet implemented");
    }
    break;

  default:

    // Unrecognized access mode.
    // Should be unreachable.

    post_fatal_error_message("unrecognized access mode");
    break;
  }

  // Postconditions:

  ensure(invariant());
  ensure(name() == xname);
  ensure(mode() == xmode);
  ensure(is_open());

  // Exit

  return;
}



///
bool
sheaf::sheaf_file::
is_open() const
{
  bool result = false;

  // Preconditions:

  // Body:

  result = (_mode != NONE);

  // Postconditions:

  ensure(result == (mode() != NONE));

  // Exit

  return result;
}



///
sheaf::sheaf_file::access_mode
sheaf::sheaf_file::
mode() const
{
  access_mode result;

  // Preconditions:

  // Body:

  result = _mode;

  // Postconditions:

  // Exit

  return result;
}


///
void
sheaf::sheaf_file::
close()
{
  // Preconditions:

  require(is_open());

  // Body:

  // Delete the type map that was created when we opened the file.
  // Closes various HDF objects which must be closed for the file
  // to be closed.

  delete _type_map;

  // Close the file.
  // If any HDF objects that reference the file are still open,
  // HDF will close access to the file but silently leave the file open.

  herr_t lstatus = H5Fclose(_hdf_id);

  if(lstatus < 0)
  {
    post_fatal_error_message("failed to close file");
  }

  _mode = NONE;

  // Postconditions:

  ensure(!is_open());

  // Exit

  return;
}




///
sheaf::data_type_map&
sheaf::sheaf_file::
type_map()
{
  // Preconditions:

  require(is_open());

  // Body:

  data_type_map& result = *_type_map;

  // Postconditions:

  // Exit

  return result;
}

///
const sheaf::data_type_map&
sheaf::sheaf_file::
type_map() const
{
  // Preconditions:

  require(is_open());

  // Body:

  data_type_map& result = *_type_map;

  // Postconditions:

  // Exit

  return result;
}




///
bool
sheaf::sheaf_file::
type_map_defined() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _type_map != 0;

  // Postconditions:

  // Exit

  return result;
}





hid_t
sheaf::sheaf_file::
hdf_id() const
{
  hid_t result;

  // Preconditions:

  require(is_open());

  // Body:

  result = _hdf_id;

  // Postconditions:

  // Exit

  return result;
}
