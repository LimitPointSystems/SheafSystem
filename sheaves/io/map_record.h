
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

// Interface for class map_record

#ifndef MAP_RECORD_H
#define MAP_RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef VARIABLE_LENGTH_RECORD_H
#include "variable_length_record.h"
#endif

namespace sheaf
{

class member_record_set;
class interval_index_map;
  
///
/// A record buffer for transferring file id map data
/// for the member record data set between the kernel 
/// and the i/o subsystem.
///
///
class SHEAF_DLL_SPEC map_record : public variable_length_record
{
  // ===========================================================
  // MAP_RECORD FACET
  // ===========================================================

public:

  ///
  /// Creates an instance in record set xhost
  /// for reading or writing member data.
  ///
  map_record(member_record_set& xhost);

  ///
  /// Copy constructor
  ///
  map_record(const map_record& xother);

  ///
  /// Destructor
  ///
  virtual ~map_record();

protected:

  // Default constructor.
  // Default construction prohibited because scaffold must be initialized
  // inline map_record() {} ;

private:

  // ===========================================================
  // WRITE FACET
  // ===========================================================

public:

  ///
  /// Converts the record from internal to external form
  ///
  void externalize(hvl_t* xhdf_buffer, const interval_index_map& xmap);

private:

  ///
  /// Gathers data from the map into the internal buffer.
  ///
  void transfer_map_to_internal_buffer();

  ///
  /// Converts the internal buffer to external form
  /// and places the result in the external buffer.
  ///
  void convert_internal_buffer_to_external_buffer(const interval_index_map& xmap);

  ///
  /// Initializes the external buffer from the internal buffer.
  ///
  virtual void initialize_external_buffer(const interval_index_map& xmap);

  ///
  /// Converts the map data from internal to external format.
  ////
  void externalize_map_data(size_t& xnext_field_offset, const interval_index_map& xmap);

  ///
  /// Initializes the HDF buffer xbuf from the external buffer.
  ///
  void transfer_external_buffer_to_HDF(hvl_t* xbuf);

  // ===========================================================
  // READ FACET
  // ===========================================================

public:

  ///
  /// Converts the record from external to internal form
  ///
  void internalize(hvl_t* xhdf_buffer, interval_index_map& xmap);

private:

  ///
  /// Initializes the external buffer from xbuf.
  ///
  void transfer_HDF_to_external_buffer(hvl_t* xbuf);

  ///
  /// Converts the external buffer to internal form
  /// and places the result in the internal buffer.
  ///
  void convert_external_buffer_to_internal_buffer(interval_index_map& xmap);

  ///
  /// Converts the map data from external to internal format.
  ////
  void internalize_map_data(size_t& xnext_field_offset, interval_index_map& xmap);

  ///
  /// Initializes the map from the internal buffer.
  ///
  void transfer_internal_buffer_to_map();

  // ===========================================================
  // VARIABLE_LENGTH_RECORD FACET
  // ===========================================================

  

  ///
  /// Pointer to record item beginning at offset xoffset
  ///
  inline int* int_buf() const
  {
    return reinterpret_cast<pod_index_type*>(buf());
  };

  // ===========================================================
  // RECORD FACET
  // ===========================================================

  // ===========================================================
  // ANY FACET
  // ===========================================================

public:

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual map_record* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

};
 
} // namespace sheaf

#endif // ifndef MAP_RECORD_H






