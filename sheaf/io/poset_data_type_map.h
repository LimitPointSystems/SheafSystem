
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

// Interface for class poset_data_type_map

#ifndef COM_LIMITPOINT_SHEAF_POSET_DATA_TYPE_MAP_H
#define COM_LIMITPOINT_SHEAF_POSET_DATA_TYPE_MAP_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DATA_TYPE_MAP_H
#include "ComLimitPoint/sheaf/data_type_map.h"
#endif

//#ifndef COM_LIMITPOINT_SHEAF_NAME_MULTIMAP_H
//#include "ComLimitPoint/sheaf/name_multimap.h"
//#endif

#ifndef COM_LIMITPOINT_SHEAF_RECORD_INDEX_H
#include "ComLimitPoint/sheaf/record_index.h"
#endif

#ifndef STD_UNORDERED_MAP_H
#include "std_unordered_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef STD_VECTOR_H
#include "std_vector.h"
#endif

namespace sheaf
{

class subposet;
 
///
/// A poset specific collection of data converters,
/// various buffers and other data used while
/// transferring posets between internal and external
/// representations.
///
class SHEAF_DLL_SPEC poset_data_type_map : public data_type_map
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
  virtual poset_data_type_map* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // ===========================================================
  // POSET_DATA_TYPE_MAP FACET
  // ===========================================================

  ///
  /// Create an instance with primitive type converters
  /// from xprim_map and default member record types.
  ///
  poset_data_type_map(const data_type_map& xprim_map);

  ///
  /// Copy constructor
  ///
  ///
  poset_data_type_map(const poset_data_type_map& xother);

  ///
  /// Destructor
  ///
  virtual ~poset_data_type_map();

  ///
  /// The data converter for implementation type toc
  ///
  inline data_converter* toc_converter() const
  {
    return _converters[_toc_index];
  };

  ///
  /// The data converter for implementation type dof_tuple_id
  ///
  inline data_converter* dof_tuple_id_converter() const
  {
    return _converters[_dof_tuple_id_index];
  };

  ///
  /// The data converter for implementation type offset
  ///
  inline data_converter* offset_converter() const
  {
    return _converters[_offset_index];
  };


  ///
  /// Sets the member record specific data types
  /// These features are logically members of class member_record,
  /// but are placed here so they will only be initialized once per poset,
  /// rather than once per member record.
  ///
  //   void put_member_record_type_aliases(const scoped_index& xtoc_index,
  //                                       const scoped_index& xdof_tuple_id_index,
  //                                       const scoped_index& xoffset_index);
  void put_member_record_type_aliases(int xtoc_index,
                                      int xdof_tuple_id_index,
                                      int xoffset_index);

private:

  // Default constructor; private to prevent default construction.

  poset_data_type_map();

  // Type indices for member_record fields

  //   scoped_index _toc_index;
  //   scoped_index _dof_tuple_id_index;
  //   scoped_index _offset_index;

  int _toc_index;
  int _dof_tuple_id_index;
  int _offset_index;

};
  
} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_POSET_DATA_TYPE_MAP_H






