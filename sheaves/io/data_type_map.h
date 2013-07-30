
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

// Interface for class data_type_map

#ifndef DATA_TYPE_MAP_H
#define DATA_TYPE_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef PRIMITIVE_TYPE_H
#include "primitive_type.h"
#endif

#ifndef STD_HDF5_H
#include "std_hdf5.h"
#endif

namespace sheaf
{

class data_converter;
class sheaf_file;  

///
/// A collection of data converters that map data types
/// between internal and external representations.
///
class SHEAF_DLL_SPEC data_type_map : public any
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
  virtual data_type_map* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // ===========================================================
  // DATA_TYPE_MAP FACET
  // ===========================================================

  ///
  /// Destructor
  ///
  virtual ~data_type_map();

  ///
  /// The hdf file this type map is associated with.
  ///
  inline hid_t file() const
  {
    return _file;
  } ;

  ///
  /// The data converter for the type with index xi
  ///
  data_converter* operator[] (int xi) const;


  ///
  /// The data converter for primitive type xpt
  ///
  inline data_converter* converter(primitive_type xpt) const
  {
    return _converters[xpt];
  };

  ///
  /// The internal size of the largest fixed length type.
  ///
  inline size_t max_internal_size() const
  {
    return _max_internal_size;
  };

  ///
  /// The external size of the largest fixed length type.
  ///
  inline size_t max_external_size() const
  {
    return _max_external_size;
  };

  ///
  /// The maximum size, internal or external, of any fixed length type.
  ///
  inline size_t max_size() const
  {
    return _max_internal_size > _max_external_size ? _max_internal_size : _max_external_size;
  }

protected:


  ///
  /// Default constructor.
  ///
  data_type_map();

  ///
  /// Copy constructor.
  ///
  ///
  data_type_map(const data_type_map& xother);

  ///
  /// The hdf file handle.
  ///
  hid_t _file;

  ///
  /// The internal size of the largest fixed length type.
  ///
  size_t _max_internal_size;

  ///
  /// The external size of the largest fixed length type.
  ///
  size_t _max_external_size;

  ///
  /// Table of converters, one for each type defined in the file.
  ///
  data_converter* _converters[PRIMITIVE_TYPE_END];
};
  
} // namespace sheaf

#endif // ifndef DATA_TYPE_MAP_H






