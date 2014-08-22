
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

// Interface for class primitive_attributes

#ifndef COM_LIMITPOINT_SHEAF_PRIMITIVE_ATTRIBUTES_H
#define COM_LIMITPOINT_SHEAF_PRIMITIVE_ATTRIBUTES_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_PRIMITIVE_TYPE_H
#include "ComLimitPoint/sheaf/primitive_type.h"
#endif

namespace sheaf
{

template <typename T>
class block;
  
///
/// Abstract object wrapper for an instance of a primitive type.
///
class SHEAF_DLL_SPEC primitive_attributes
{
public:

  ///
  /// The prototype for the primitive value
  /// of the type associated with xid.
  ///
  static const primitive_attributes& prototype(pod_index_type xid);

  ///
  /// Type id of the primitive type with name or alias xname.
  ///
  static primitive_type id(const std::string& xname);

  ///
  /// Converts pod_index_type xid to primitive_type.
  ///
  static primitive_type id(pod_index_type xid)
  {
    return prototype(xid).id();
  };

  ///
  /// Size of the primitive type with id xid.
  ///
  static size_type size(pod_index_type xid)
  {
    return prototype(xid).size();
  };

  ///
  /// Alignment of the primitive type with id xid.
  ///
  static size_type alignment(pod_index_type xid)
  {
    return prototype(xid).alignment();
  };

  ///
  /// The name of primitive type with id xid.
  ///
  static const std::string& name(pod_index_type xid)
  {
    return prototype(xid).name();
  };

  ///
  /// Other names for the primitive type with id xid
  ///
  static const std::string& aliases(pod_index_type xid)
  {
    return prototype(xid).aliases();
  };

  ///
  /// The name in the hdf file of primitive type with id xid.
  ///
  static const std::string& hdf_type_name(pod_index_type xid)
  {
    return prototype(xid).hdf_type_name();
  };

  ///
  /// The hdf type of primitive type with id xid.
  ///
  static int hdf_type(pod_index_type xid)
  {
    return prototype(xid).hdf_type();
  };

  ///
  /// The default value for the primitive type associated with this.
  ///
  static primitive_buffer_type default_value(pod_index_type xid)
  {
    return prototype(xid).default_value();
  };

  ///
  /// Primitive descriptor for the primitive type with id xid.
  ///
  static primitive_descriptor descriptor(pod_index_type xid)
  {
    return prototype(xid); // Return invokes conversion function
  };

  // ===========================================================
  // CONSTRUCTORS
  // ===========================================================

  ///
  /// Default constructor.
  ///
  primitive_attributes();

  ///
  /// Copy constructor.
  ///
  primitive_attributes(const primitive_attributes& xother);

  ///
  /// Creates a new primitive value
  /// of the type associated with xid and default value.
  ///
  primitive_attributes(primitive_type xid);

  ///
  /// Conversion from pointer;
  /// creates a new primitive value of type VOID_STAR with value x.
  ///
  primitive_attributes(const void* x);

  ///
  /// Conversion from C string;
  /// creates a new primitive value of type C_STRING with value x.
  ///
  primitive_attributes(const char* x);

  ///
  /// Conversion from type T;
  /// creates a new primitive value of type T with value x.
  ///
  template <typename T>
  primitive_attributes(const T& x);

  ///
  /// Copy assignment operator.
  ///
  primitive_attributes& operator=(const primitive_attributes&);

  ///
  /// Destructor; not virtual, this can not be a base class.
  ///
  ~primitive_attributes();


  // ===========================================================
  // ATTRIBUTES
  // ===========================================================

  ///
  /// The id for the primitive type associated with this.
  ///
  primitive_type id() const
  {
    return _id;
  };

  ///
  /// The size of the primitive type associated with this.
  ///
  size_type size() const
  {
    return _size;
  };

  ///
  /// The alignment for the primitive type associated with this.
  ///
  size_type alignment() const
  {
    return _alignment;
  };

  ///
  /// The name of the primitive type associated with this.
  ///
  const std::string& name() const
  {
    return *_name;
  };

  ///
  /// Other names for the primitive type associated with this.
  ///
  const std::string& aliases() const
  {
    return *_aliases;
  };

  ///
  /// The name in the hdf file of the primitive type associated with this.
  ///
  const std::string& hdf_type_name() const
  {
    return *_hdf_type_name;
  };

  ///
  /// The hdf type of the primitive type associated with this.
  ///
  int hdf_type() const
  {
    return _hdf_type;
  };

  ///
  /// The default value for the primitive type associated with this.
  ///
  primitive_buffer_type default_value() const
  {
    return _default_value;
  };

  ///
  /// Conversion to primitive_descriptor
  ///
  operator primitive_descriptor() const;

private:

  ///
  /// The id for the primitive type associated with this.
  ///
  primitive_type _id;

  ///
  /// The size of the primitive type associated with this.
  ///
  size_type _size;

  ///
  /// The alignment for the primitive type associated with this.
  ///
  size_type _alignment;

  ///
  /// The name of the primitive type associated with this.
  ///
  const std::string* _name;

  ///
  /// Other names for the primitive type associated with this.
  ///
  const std::string* _aliases;

  ///
  /// The name in the hdf file of the primitive type associated with this.
  ///
  const std::string* _hdf_type_name;

  ///
  /// The hdf type used to represent the primitive type associated with this.
  ///
  int _hdf_type;

  ///
  /// The default value for the primitive type associated with this.
  ///
  primitive_buffer_type _default_value;

  ///
  /// Initializes prototypes for specific primitive types.
  ///
  static block<primitive_attributes>& make_prototypes();
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_PRIMITIVE_ATTRIBUTES_H
