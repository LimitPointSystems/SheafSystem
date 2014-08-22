
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

// Implementation for class template primitive_traits.

#include "ComLimitPoint/sheaf/primitive_traits.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "hdf5.h"

// Definitions of primitive_traits::hdf_type given here to encapsulate hdf.
/// @issue The return type is declared int to encapsulate hdf, but the
/// actual type for these type ids is hid_t, which is currently (hdf1.8.0 beta)
/// typdef'd to int. This is unlikely to change, but if it does, it could errors.

int sheaf::primitive_traits<bool>::hdf_type()
{
  return H5T_NATIVE_B8; /// @issue HDF doesn't support bool!
}

int sheaf::primitive_traits<char>::hdf_type()
{
  return H5T_NATIVE_CHAR;
}

int sheaf::primitive_traits<signed char>::hdf_type()
{
  return H5T_NATIVE_SCHAR;
}

int sheaf::primitive_traits<short int>::hdf_type()
{
  return H5T_NATIVE_SHORT;
}

int sheaf::primitive_traits<int>::hdf_type()
{
  return H5T_NATIVE_INT;
}

int sheaf::primitive_traits<long int>::hdf_type()
{
  return H5T_NATIVE_LONG;
}

int sheaf::primitive_traits<long long int>::hdf_type()
{
  return H5T_NATIVE_LLONG;
}

int sheaf::primitive_traits<unsigned char>::hdf_type()
{
  return H5T_NATIVE_UCHAR;
}

int sheaf::primitive_traits<unsigned short int>::hdf_type()
{
  return H5T_NATIVE_USHORT;
}

int sheaf::primitive_traits<unsigned int>::hdf_type()
{
  return H5T_NATIVE_UINT;
}

int sheaf::primitive_traits<unsigned long int>::hdf_type()
{
  return H5T_NATIVE_ULONG;
}

int sheaf::primitive_traits<unsigned long long int>::hdf_type()
{
  return H5T_NATIVE_ULLONG;
}

int sheaf::primitive_traits<float>::hdf_type()
{
  return H5T_NATIVE_FLOAT;
}

int sheaf::primitive_traits<double>::hdf_type()
{
  return H5T_NATIVE_DOUBLE;
}

int sheaf::primitive_traits<long double>::hdf_type()
{
  return H5T_NATIVE_LDOUBLE;
}

int sheaf::primitive_traits<sheaf::void_star>::hdf_type()
{
  int result = -1;
  if(sizeof(void*) == sizeof(unsigned int))
  {
    result = H5T_NATIVE_UINT;
  }
  else if(sizeof(void*) == sizeof(unsigned long))
  {
    result = H5T_NATIVE_ULONG;
  }
  else if(sizeof(void*) == sizeof(unsigned long long))
  {
    result =  H5T_NATIVE_ULLONG;
  }
  else
  {
    post_fatal_error_message("Unable to match sheaf primitive void_star with HDF type.");
  }

  return result;
}

int sheaf::primitive_traits<sheaf::c_string>::hdf_type()
{
  return H5T_C_S1;
}

int sheaf::primitive_traits<sheaf::namespace_relative_member_index_pod_type>::hdf_type()
{
  // The sheaf type is a struct with this type as the type of its members.
  // See file_data_type_map::create_internal_hdf_types().

  return H5T_NATIVE_INT;
}

int sheaf::primitive_traits<sheaf::namespace_relative_subposet_index_pod_type>::hdf_type()
{
  // The sheaf type is a struct with this type as the type of its members.
  // See file_data_type_map::create_internal_hdf_types().

  return H5T_NATIVE_INT;
}

int sheaf::primitive_traits<void>::hdf_type()
{
  // The sheaf type is a struct with this type as the type of its members.
  // See file_data_type_map::create_internal_hdf_types().

  return -1;
}




