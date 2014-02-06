
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

// Interface for class data_converter

#ifndef DATA_CONVERTER_H
#define DATA_CONVERTER_H

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

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
  
///
/// Function object to convert between
/// internal and external data formats.
///
class SHEAF_DLL_SPEC data_converter : public any
{

public:

  // CANONICAL MEMBERS

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual data_converter* clone() const;

  ///
  /// Destructor
  ///
  virtual ~data_converter();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // DATA_CONVERTER INTERFACE

  ///
  /// Creates a converter between the internal hdf type
  /// specified by xinternal_type and the external type
  /// specified by xexternal_type_name. If xcreate_ext_type,
  /// assumes that the external type does not already exist in
  /// the file and attempts to create it, otherwise attempts
  /// to open it.
  ///
  data_converter(hid_t xexternal_type,
                 hid_t xinternal_type,
                 //                  const scoped_index& xinternal_index);
                 int xinternal_index);

  
  
  ///
  /// True if internal and external types are not identical.
  ///
  inline bool conversion_required() const
  {
    return _conversion_required;
  } ;

  
  
  ///
  /// The external type identifier
  ///
  inline hid_t external_type() const
  {
    return _external_type;
  } ;

  
  
  ///
  /// The size in bytes of the external type.
  ///
  inline size_t external_size() const
  {
    return _external_size;
  };

  // INTERFACE FOR SIMPLE TYPES

  ///
  /// Copy xitem_ct data items from xint_buf to xext_buf and
  /// then convert them from internal to external format.
  ///
  void externalize(const void* xint_buf,
                   size_t xint_buf_ub,
                   void* xext_buf,
                   size_t xext_buf_ub,
                   int xitem_ct);

  ///
  /// Convert xitem_ct data items in xext_buf
  /// from internal to external format.
  ///
  void externalize(void* xext_buf,
                   size_t xext_buf_ub,
                   int xitem_ct);

  ///
  /// Copy one data item from xint_buf to result() and
  /// then convert it from internal to external format.
  ///
  void externalize(const void* xint_buf,
                   size_t xint_buf_ub);

  
  
  ///
  /// The HDF type identifier for the internal type.
  ///
  inline hid_t internal_type() const
  {
    return _internal_type;
  } ;

  
  
  ///
  /// The primitives poset member index for the internal type.
  ///
  inline hid_t internal_index() const
  {
    return _internal_index;
  } ;

  
  
  ///
  /// The size in bytes of the internal type.
  ///
  inline size_t internal_size() const
  {
    return _internal_size;
  };

  
  
  ///
  /// The alignment of the internal type.
  ///
  inline size_t internal_alignment() const
  {
    return _internal_alignment;
  };

  ///
  /// Convert xitem_ct data items in xext_buf from external
  /// to internal format and place the result in xint_buf.
  ///
  void internalize(const void* xext_buf,
                   size_t xext_buf_ub,
                   void* xint_buf,
                   size_t xint_buf_ub,
                   int xitem_ct);

  ///
  /// Convert xitem_ct data items in xbuf
  /// from external to internal format and
  /// leave the result in xbuf.
  ///
  void internalize(void* xbuf, size_t xbuf_ub, int xitem_ct);

  ///
  /// Convert one data item from xbuf from external
  /// to internal format and leave the result in result().
  ///
  void internalize(void* xbuf, size_t xbuf_ub);

  
  
  ///
  /// True if the internal size is greater than the external size
  ///
  inline bool internal_size_greater() const
  {
    return _internal_size > _external_size;
  };

  
  
  ///
  /// True if the external size is greater than the internal size
  ///
  inline bool external_size_greater() const
  {
    return _external_size > _internal_size;
  };

  
  
  ///
  /// The maximum of internal_size() and external_size().
  ///
  inline size_t max_size() const
  {
    return _internal_size > _external_size ? _internal_size : _external_size;
  } ;

  
  
  ///
  /// The result of the conversion
  ///
  inline void* result() const
  {
    return _result;
  };

  
  
  ///
  /// The allocated size of the result buffer.
  ///
  inline size_t result_size() const
  {
    return _result_size;
  } ;

  
  
  ///
  /// True if this is a converter for a naemspace_relative_member_index type.
  ///
  inline bool is_namespace_relative_member_index_type() const
  {
    return _internal_index == NAMESPACE_RELATIVE_MEMBER_INDEX;
  };

  
  
  ///
  /// True if this is a converter for a namespace_relative_subposet_index type.
  ///
  inline bool is_namespace_relative_subposet_index_type() const
  {
    return _internal_index == NAMESPACE_RELATIVE_SUBPOSET_INDEX;
  };

  
  
  ///
  /// True if this is a converter for a string type.
  ///
  inline bool is_string_type() const
  {
    return _internal_index == C_STRING;
  };

  ///
  /// The number of characters in the string, including the terminator.
  ///
  static size_t string_length(const char* xbuf);

  ///
  /// The total number of characters, including the terminators
  /// in all the strings in the array of strings xbuf.
  ///
  size_t string_length_total(const void* xbuf, int xitem_ct) const;


private:

  ///
  /// Default constructor;
  /// private to prevent default construction
  ///
  data_converter();

  ///
  /// Copy constructor;
  /// private to prevent copy construction.
  ///
  data_converter(const data_converter& xother);

  ///
  /// The external type.
  ///
  hid_t _external_type;

  ///
  /// The size in bytes of the external type.
  ///
  size_t _external_size;

  ///
  /// The internal type.
  ///
  hid_t _internal_type;

  ///
  /// The size of the internal type in bytes.
  ///
  size_t _internal_size;


  ///
  /// The primitive index for the internal type.
  ///
  int _internal_index;

  ///
  /// The alignment of the interal type.
  ///
  size_t _internal_alignment;

  ///
  /// The result buffer.
  ///
  void* _result;

  ///
  /// The size of the result bufferin bytes.
  ///
  size_t _result_size;

  ///
  /// Dataset transfer property list;
  /// required by conversion routine H5Tconvert,
  /// but apparently not used.
  ///
  hid_t _transfer_plist;

  ///
  /// True if internal and external types are not identical
  ///
  bool _conversion_required;

};

} // namespace sheaf
 
#endif // ifndef DATA_CONVERTER_H






