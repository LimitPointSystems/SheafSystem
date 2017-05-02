
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

// Interface for class variable_length_record

#ifndef VARIABLE_LENGTH_RECORD_H
#define VARIABLE_LENGTH_RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef RECORD_H
#include "SheafSystem/record.h"
#endif

namespace sheaf 
{
  
///
/// The general variable length record wrapper/adapter for transferring
/// data between the kernel and the i/o subsystem.
///
///
class SHEAF_DLL_SPEC variable_length_record : public record
{
public:

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  variable_length_record(const variable_length_record& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual variable_length_record* clone() const;

  ///
  /// Destructor
  ///
  virtual ~variable_length_record();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // VARIABLE_LENGTH_RECORD INTERFACE

  ///
  /// Creates an instance with type map xtype_map
  ///
  variable_length_record(const poset_scaffold& xscaffold);

  ///
  /// The buffer.
  ///
  void* buf() const;

  ///
  /// The size of the buffer, in bytes.
  ///
  size_t buf_ub() const;

protected:

  // Default constructor.
  // Default construction prohibited because scaffold must be initialized
  //  inline variable_length_record() {} ;

  ///
  /// Sets the buffer to xbuf.
  ///
  ///
  void put_buf(const void* xbuf, size_t xub);

  ///
  /// True if this allocated the buffer and the dtor should delete it.
  ///
  inline bool delete_buffer()
  {
    return _delete_buffer;
  };

  ///
  /// Sets delete_buffer to value xval.
  ///
  inline void put_delete_buffer(bool xval)
  {
    _delete_buffer = xval;
  };

  

  ///
  /// Pointer to record item beginning at offset xoffset
  ///
  inline void* item(size_t xoffset) const
  {
    return reinterpret_cast<char*>(_buf) + xoffset;
  };

  

  ///
  /// True if the internal buffer has been initialized.
  ///
  inline bool is_internal() const
  {
    return _is_internal;
  };

  ///
  /// Sets is_internal to xis_internal
  ///
  inline void put_is_internal(bool xis_internal)
  {
    _is_internal = xis_internal;
  };

  

  ///
  /// True if the external buffer has been initialized.
  ///
  inline bool is_external() const
  {
    return _is_external;
  };

  ///
  /// Sets is_external to xis_external
  ///
  inline void put_is_external(bool xis_external)
  {
    _is_external = xis_external;
  };


private:

  // The buffer for this record

  void*  _buf;

  // The length of the buffer, in bytes.

  size_t _buf_ub;

  // True if this allocated the buffer and the dtor should delet it.

  bool _delete_buffer;

  // True if the internal buffer has been initialized.

  bool _is_internal;

  // True if the external buffer has been initialized;

  bool _is_external;

};

} // namespace sheaf

#endif // ifndef VARIABLE_LENGTH_RECORD_H







