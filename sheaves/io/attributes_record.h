
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

// Interface for class attributes_record

#ifndef ATTRIBUTES_RECORD_H
#define ATTRIBUTES_RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef VARIABLE_LENGTH_RECORD_H
#include "variable_length_record.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
  
///
/// An abstract wrapper/adapter for attributes records.
/// Intended for transferring data between the kernel and
/// the i/o subsystem.
///
class SHEAF_DLL_SPEC attributes_record : public variable_length_record
{
public:

  ///
  /// The type of hdf buffer.
  ///
  typedef char* hdf_buf_type;


  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  attributes_record(const attributes_record& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual attributes_record* clone() const;

  ///
  /// Destructor
  ///
  virtual ~attributes_record();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // ATTRIBUTES_RECORD INTERFACE

  ///
  /// Creates an instance with type map xtype_map
  ///
  attributes_record(poset_scaffold& xscaffold);

  ///
  /// Converts the record from external to internal form
  ///
  void internalize(hdf_buf_type* xhdf_buffer);

  ///
  /// Converts the record from internal to external form
  ///
  void externalize(hdf_buf_type* xhdf_buffer);

protected:

  ///
  /// Initializes the external buffer from xbuf.
  ///
  void transfer_HDF_to_external_buffer(hdf_buf_type* xbuf);

  ///
  /// Initializes the HDF buffer xbuf from the external buffer.
  ///
  void transfer_external_buffer_to_HDF(hdf_buf_type* xbuf);

  ///
  /// Initializes scaffold from the internal buffer.
  ///
  virtual void transfer_internal_buffer_to_poset() = 0;

  ///
  /// Initializes the internal buffer from the scaffold.
  ///
  virtual void transfer_poset_to_internal_buffer() = 0;

  ///
  /// Converts the external buffer to internal form
  /// and places the result in the internal buffer.
  ///
  void convert_external_buffer_to_internal_buffer();

  ///
  /// Converts the internal buffer to external form
  /// and places the result in the external buffer.
  ///
  void convert_internal_buffer_to_external_buffer();

  ///
  /// The internal/external buffer
  ///
  string _str_buf;

};
  
} // namespace sheaf


#endif // ifndef ATTRIBUTES_RECORD_SET
