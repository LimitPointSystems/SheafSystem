
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

// Implementation for class file_data_type_map

#include "file_data_type_map.h"

#include "assert_contract.h"
#include "data_converter.h"
#include "namespace_relative_member_index.h"
#include "namespace_relative_subposet_index.h"
#include "primitive_attributes.h"
#include "sheaf_file.h"

using namespace std;

// ===========================================================
// ANY FACET
// ===========================================================

///
sheaf::file_data_type_map*
sheaf::file_data_type_map::
clone() const
{
  file_data_type_map* result;

  // Preconditions:

  // Body:

  result = new file_data_type_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}




///
bool
sheaf::file_data_type_map::
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

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::file_data_type_map::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const file_data_type_map*>(other) != 0;

  // Postconditions:

  return result;

}



// ===========================================================
// FILE_DATA_TYPE_MAP FACET
// ===========================================================


///
sheaf::file_data_type_map::
file_data_type_map(hid_t xfile, bool xcreate_ext_types)
{

  // Preconditions:

  // Body:

  _file = xfile;

  // Some of the internal HDF types are not predefined; must create them.

  hid_t linternal_hdf_types[PRIMITIVE_TYPE_END];
  create_internal_hdf_types(linternal_hdf_types, PRIMITIVE_TYPE_END);

  // Get the external hdf types.

  hid_t lexternal_hdf_types[PRIMITIVE_TYPE_END];
  if(xcreate_ext_types)
  {
    // Must create the external types.

    create_external_hdf_types(linternal_hdf_types,
                              PRIMITIVE_TYPE_END,
                              lexternal_hdf_types,
                              PRIMITIVE_TYPE_END);
  }
  else
  {
    // External types are already in the file.

    open_external_hdf_types(lexternal_hdf_types, PRIMITIVE_TYPE_END);
  }

  // Create a data converter for each type.

  _max_internal_size = 0;
  _max_external_size = 0;

  for(int i=PRIMITIVE_TYPE_BEGIN; i<PRIMITIVE_TYPE_END; i++)
  {
    _converters[i] =
      new data_converter(lexternal_hdf_types[i], linternal_hdf_types[i], i);

    size_t lsize = _converters[i]->internal_size();
    _max_internal_size = lsize  > _max_internal_size ? lsize : _max_internal_size;

    lsize = _converters[i]->external_size();
    _max_external_size = lsize  > _max_external_size ? lsize : _max_external_size;
  }

  // Postconditions:

  ensure(invariant());
  ensure(max_internal_size() > 0);
  ensure(max_external_size() > 0);

  // Exit:

  return;
}

///
sheaf::file_data_type_map::
file_data_type_map(const file_data_type_map& xother)
    : data_type_map(xother)
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());
}



///
sheaf::file_data_type_map::
~file_data_type_map()
{

  // Preconditions:

  // Body:

  // Terminate access to the hdf types.

  close_internal_hdf_types();
  close_external_hdf_types();

  // Delete the converters.

  for(int i=PRIMITIVE_TYPE_BEGIN; i<PRIMITIVE_TYPE_END; i++)
  {
    delete _converters[i];
  }

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
// PROTECTED MEMBER FUNCTIONS
// ===========================================================

sheaf::file_data_type_map::
file_data_type_map()
{

  // Preconditions:


  // Body:

  // Postconditions:

  // Exit:

  return;
}


// ===========================================================
// PRIVATE MEMBER FUNCTIONS
// ===========================================================

// ///
// const char*
// sheaf::file_data_type_map::
// external_hdf_type_name(int xi)
// {
//   const char* result;

//   // Preconditions:


//   // Body:

//   static const char* EXTERNAL_HDF_TYPE_NAMES[PRIMITIVE_TYPE_END] =
//     {
//       "__not_a_type_name", // placeholder top member
//       "__not_a_type_name", // placeholder bottom member
//       "SHF_PRIMITIVE_SIZE_T",
//       "SHF_PRIMITIVE_INT",
//       "SHF_PRIMITIVE_DOUBLE",
//       "SHF_PRIMITIVE_CHAR_PTR",
//       "SHF_PRIMITIVE_VOID_PTR",
//       "SHF_PRIMITIVE_POSET_MEMBER_INDEX",
//       "SHF_PRIMITIVE_SUBPOSET_INDEX",
//       "SHF_PRIMITIVE_CLIENT_ID",
//       "SHF_PRIMITIVE_CHAR",
//       "SHF_PRIMITIVE_USHORT",
//       "SHF_PRIMITIVE_NAMESPACE_RELATIVE_MEMBER_INDEX",
//       "SHF_PRIMITIVE_NAMESPACE_RELATIVE_SUBPOSET_INDEX"
//     };

//   result = EXTERNAL_HDF_TYPE_NAMES[xi];

//   // Postconditions:

//   ensure(result != 0);

//   // Exit:

//   return result;
// }

// ///
// hid_t
// sheaf::file_data_type_map::
// predefined_internal_hdf_type(int xi)
// {
//   hid_t result;

//   // Preconditions:


//   // Body:

//   static const hid_t PREDEFINED_INTERNAL_HDF_TYPES[PRIMITIVE_TYPE_END] =
//     {
//       0,                  // placeholder for top member
//       0,                  // placeholder for bottom member
//       H5T_NATIVE_ULONG,   // size_t
//       H5T_NATIVE_INT,     // int
//       H5T_NATIVE_DOUBLE,  // double
//       H5T_C_S1,           // char_ptr; treated specially, see Notes 1 and 3 below.
//       H5T_NATIVE_ULONG,   // void_ptr
//       H5T_NATIVE_INT,     // scoped_index
//       H5T_NATIVE_INT,     // subposet_index; treated specially, see Note 2 below.
//       H5T_NATIVE_INT,     // client_id
//       H5T_C_S1,           // char; see Note 3 below.
//       H5T_NATIVE_USHORT,  // ushort
//       H5T_NATIVE_INT,     // namespace_relative_member_index; treated specially, see Note 2 below.
//       H5T_NATIVE_INT      // namespace_relative_subposet_index; treated specially, see Note 2 below.

//       // Note 1: this is the type of an individual char,
//       // see class data_converter for how it is used.

//       // Note 2: the sheaf_primitive type is a struct
//       // with this type as the type of its members.
//       // See create_internal_hdf_types(). Since the
//       // internal member ids are converted to record ids
//       // in the file, this type must be the same as the
//       // type used by record_index_converter for record ids.
//       // See classes dof_tuple_record and table_dof_tuple_record
//       // for usage.

//       // Note 3: This system uses the null padding option
//       // instead of the default null termination. See  routine
//       // create_internal_hdf_types. See also HDF User's Guide/Datatypes/Section 3.6
//       // for a discussion of how HDF treats character data.
//     };


//   result = PREDEFINED_INTERNAL_HDF_TYPES[xi];

//   // Postconditions:


//   // Exit:

//   return result;
// }

///
void
sheaf::file_data_type_map::
create_internal_hdf_types(hid_t* xinternal_hdf_types, size_t xinternal_hdf_types_ub)
{
  // Preconditions:

  require(xinternal_hdf_types != 0);
  require(xinternal_hdf_types_ub >= PRIMITIVE_TYPE_END);

  // Body:

  // Set all the predefined types

  for(int i=PRIMITIVE_TYPE_BEGIN; i<PRIMITIVE_TYPE_END; i++)
  {
    xinternal_hdf_types[i] = primitive_attributes::hdf_type(i);
  }

  hid_t lhdf_id, lmbr_type;
  herr_t lstatus;

  // Create char_ptr type.
  // Data type for char_ptr is special variable length C string.

  lhdf_id = H5Tcopy(H5T_C_S1);
  if(lhdf_id < 0)
  {
    post_fatal_error_message("Unable to copy H5T_C_S1 datatype.");
  }

  lstatus = H5Tset_size(lhdf_id, H5T_VARIABLE);
  if(lstatus < 0)
  {
    post_fatal_error_message("Unable to set char_ptr datatype padding.");
  }

  xinternal_hdf_types[C_STRING] = lhdf_id;

  //   // Create char type; same as char_ptr type.

  //   lsheaf_id = CHAR;
  //   lhdf_id = H5Tcopy(H5T_C_S1);
  //   if(lhdf_id < 0)
  //   {
  //     post_fatal_error_message("Unable to copy H5T_C_S1 datatype.");
  //   }

  //   lstatus = H5Tset_strpad(lhdf_id, H5T_STR_NULLPAD);
  //   if(lstatus < 0)
  //   {
  //     post_fatal_error_message("Unable to set char datatype padding.");
  //   }
  //   xinternal_hdf_types[lsheaf_id] = lhdf_id;


  // Create namespace_relative_member_index_type

  typedef namespace_relative_member_index::pod_type nrmi_type;

  lhdf_id = H5Tcreate (H5T_COMPOUND, sizeof(nrmi_type));
  if(lhdf_id < 0)
  {
    post_fatal_error_message("unable to create internal HDF type");
  }

  lmbr_type = primitive_attributes::hdf_type(NAMESPACE_RELATIVE_MEMBER_INDEX);

  lstatus = H5Tinsert (lhdf_id, "poset_id", HOFFSET(nrmi_type, poset_id), lmbr_type);
  if(lstatus < 0)
  {
    post_fatal_error_message("unable to insert member in compound data type");
  }

  lstatus = H5Tinsert (lhdf_id, "member_id", HOFFSET(nrmi_type, member_id), lmbr_type);
  if(lstatus < 0)
  {
    post_fatal_error_message("unable to insert member in compound data type");
  }

  xinternal_hdf_types[NAMESPACE_RELATIVE_MEMBER_INDEX] = lhdf_id;

  // Create namespace_relative_subposet_index_type

  typedef namespace_relative_subposet_index::pod_type nrsi_type;

  lhdf_id = H5Tcreate (H5T_COMPOUND, sizeof(nrsi_type));
  if(lhdf_id < 0)
  {
    post_fatal_error_message("unable to create internal HDF type");
  }

  lmbr_type = primitive_attributes::hdf_type(NAMESPACE_RELATIVE_SUBPOSET_INDEX);

  lstatus = H5Tinsert (lhdf_id, "poset_id", HOFFSET(nrsi_type, poset_id), lmbr_type);
  if(lstatus < 0)
  {
    post_fatal_error_message("unable to insert member in compound data type");
  }

  lstatus = H5Tinsert (lhdf_id, "subposet_id", HOFFSET(nrsi_type, subposet_id), lmbr_type);
  if(lstatus < 0)
  {
    post_fatal_error_message("unable to insert member in compound data type");
  }

  xinternal_hdf_types[NAMESPACE_RELATIVE_SUBPOSET_INDEX] = lhdf_id;

  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::file_data_type_map::
close_internal_hdf_types()
{
  // Preconditions:

  require(unexecutable("converters are valid."));

  // Body:

  // Only close the types we created, not the predefined types.

  static const int lcloseable_internal_types[3] =
    {
      C_STRING,
      NAMESPACE_RELATIVE_MEMBER_INDEX,
      NAMESPACE_RELATIVE_SUBPOSET_INDEX
    };

  for(int i= 0; i<3; i++)
  {
    // Attempt to close the type.

    if(H5Tclose(_converters[lcloseable_internal_types[i]]->internal_type()) < 0)
    {
      // Close failed.

      post_fatal_error_message("Unable to close internal HDF datatype.");
    }
  }

  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::file_data_type_map::
create_external_hdf_types(const hid_t* xinternal_hdf_types,
                          size_t xinternal_hdf_types_ub,
                          hid_t* xexternal_hdf_types,
                          size_t xexternal_hdf_types_ub)
{
  // Preconditions:

  require(xinternal_hdf_types != 0);
  require(xinternal_hdf_types_ub >= PRIMITIVE_TYPE_END);
  require(xexternal_hdf_types != 0);
  require(xexternal_hdf_types_ub >= PRIMITIVE_TYPE_END);

  // Body:

  for(int i=PRIMITIVE_TYPE_BEGIN; i<PRIMITIVE_TYPE_END; i++)
  {
    // Attempt to create the external type

    hid_t lhdf_id = H5Tcopy(xinternal_hdf_types[i]);
    if(lhdf_id < 0)
    {
      post_fatal_error_message("can't create external type");
    }

    // Commit external type to file.

    string lhdf_name = primitive_attributes::hdf_type_name(i);
    //    herr_t lstatus = H5Tcommit(_file, lhdf_name.c_str(), lhdf_id);
    herr_t lstatus = H5Tcommit1(_file, lhdf_name.c_str(), lhdf_id);
    if(lstatus < 0)
    {
      post_fatal_error_message("can't commit external data type to file");
    }

    xexternal_hdf_types[i] = lhdf_id;
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::file_data_type_map::
open_external_hdf_types(hid_t* xexternal_hdf_types, size_t xexternal_hdf_types_ub)
{
  // Preconditions:

  require(xexternal_hdf_types != 0);
  require(xexternal_hdf_types_ub >= PRIMITIVE_TYPE_END);

  // Body:

  hid_t lhdf_id;

  for(int i=PRIMITIVE_TYPE_BEGIN; i<PRIMITIVE_TYPE_END; i++)
  {
    // Attempt to open the external type

    string lhdf_name = primitive_attributes::prototype(i).hdf_type_name();
    //    lhdf_id = H5Topen(_file, lhdf_name.c_str());
    lhdf_id = H5Topen1(_file, lhdf_name.c_str());
    if(lhdf_id < 0)
    {
      post_fatal_error_message("external type doesn't exist");
    }

    xexternal_hdf_types[i] = lhdf_id;
  }

  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::file_data_type_map::
close_external_hdf_types()
{
  // Preconditions:

  require(unexecutable("converters are valid."));

  // Body:

  for(int i=PRIMITIVE_TYPE_BEGIN; i<PRIMITIVE_TYPE_END; i++)
  {
    // Attempt to close the external type

    if(H5Tclose(_converters[i]->external_type()) < 0)
    {
      // Close failed.

      post_fatal_error_message("can't close external type");
    }
  }

  // Postconditions:

  // Exit

  return;
}

