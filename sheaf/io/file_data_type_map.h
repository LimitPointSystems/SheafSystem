
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

// Interface for class file_data_type_map

#ifndef COM_LIMITPOINT_SHEAF_FILE_DATA_TYPE_MAP_H
#define COM_LIMITPOINT_SHEAF_FILE_DATA_TYPE_MAP_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DATA_TYPE_MAP_H
#include "ComLimitPoint/sheaf/data_type_map.h"
#endif

namespace sheaf
{
  
///
/// A collection of data converters that map data types
/// between internal and external representations associated
/// with a specific file.
///
class SHEAF_DLL_SPEC file_data_type_map : public data_type_map
{


public:

  // ===========================================================
  // ANY FACET
  // ===========================================================

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual file_data_type_map* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // ===========================================================
  // FILE_DATA_TYPE_MAP FACET
  // ===========================================================

  ///
  /// Creates an instance for xfile.
  ///
  file_data_type_map(hid_t xfile, bool xcreate_ext_types);

  ///
  /// Copy constructor
  ///
  ///
  file_data_type_map(const file_data_type_map& xother);

  ///
  /// Destructor
  ///
  virtual ~file_data_type_map();

protected:

  // Default constructor;
  // protected to prevent default construction

  file_data_type_map();

private:

  //   ///
  ///   /// The xi-th HDF external type name.
  //   ///
  //   static string external_hdf_type_name(int xi);

  //   ///
  ///   /// The xi-th HDF internal type for the default type map.
  //   ///
  //   static hid_t predefined_internal_hdf_type(int xi);

  ///
  /// Creates internal HDF types which are not predefined
  /// and enters them in xinternal_hdf_types.
  ///
  void create_internal_hdf_types(hid_t* xinternal_hdf_types, size_t xinternal_hdf_types_ub);

  ///
  /// Closes the internal HDF types.
  ///
  void close_internal_hdf_types();

  ///
  /// Creates external HDF types and enters them in xexternal_hdf_types.
  ///
  void create_external_hdf_types(const hid_t* xinternal_hdf_types,
                                 size_t xinternal_hdf_types_ub,
                                 hid_t* xexternal_hdf_types,
                                 size_t xexternal_hdf_types_ub);

  ///
  /// Gets the external HDF types from the file and enters them in xexternal_hdf_types.
  ///
  void open_external_hdf_types(hid_t* xexternal_hdf_types, size_t xexternal_hdf_types_ub);

  ///
  /// Closes the external HDF types.
  ///
  void close_external_hdf_types();

};
  
} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_FILE_DATA_TYPE_MAP_H






