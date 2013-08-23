
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

// Interface for class primitive_value

#ifndef PRIMITIVE_VALUE_H
#define PRIMITIVE_VALUE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef PRIMITIVE_TYPE_H
#include "primitive_type.h"
#endif

#ifndef NAMESPACE_RELATIVE_MEMBER_INDEX_H
#include "namespace_relative_member_index.h"
#endif

#ifndef NAMESPACE_RELATIVE_SUBPOSET_INDEX_H
#include "namespace_relative_subposet_index.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

namespace sheaf
{

template <typename T>
class block;
 
 
///
/// Abstract object wrapper for an instance of a primitive type.
///
class SHEAF_DLL_SPEC primitive_value
{
  friend SHEAF_DLL_SPEC bool operator==(const primitive_value& xpv1, const primitive_value& xpv2);

public:

  ///
  /// The prototype for the primitive value
  /// of the type associated with xid.
  ///
  static const primitive_value& prototype(pod_index_type xid);

  // ===========================================================
  // CONSTRUCTORS
  // ===========================================================

  ///
  /// Default constructor.
  ///
  primitive_value();

  ///
  /// Copy constructor.
  ///
  primitive_value(const primitive_value& xother);

  ///
  /// Creates a new primitive value
  /// of the type associated with xid and default value.
  ///
  primitive_value(primitive_type xid);

  ///
  /// Creates a new primitive value
  /// of the type associated with xid and 
  /// value pointed to by xvalue_ptr.
  ///
  primitive_value(pod_index_type xid, void* xvalue_ptr);

  ///
  /// Conversion from pointer;
  /// creates a new primitive value of type VOID_STAR with value x.
  ///
  primitive_value(const void* x);

  ///
  /// Conversion from C string;
  /// creates a new primitive value of type C_STRING with value x.
  ///
  primitive_value(const char* x);

  ///
  /// Conversion from string;
  /// creates a new primitive value of type C_STRING with value x.
  ///
  primitive_value(const string& x);

  ///
  /// Conversion from scoped_index;
  /// creates a new primitive value of type POD_INDEX_TYPE with value x.
  ///
  primitive_value(const scoped_index& x);

  ///
  /// Conversion from namespace_relative_member_index;
  /// creates a new primitive value of type NAMESPACE_RELATIVE_MEMBER_INDEX with value x.
  ///
  primitive_value(const namespace_relative_member_index& x);

  ///
  /// Conversion from namespace_relative_subposet_index;
  /// creates a new primitive value of type NAMESPACE_RELATIVE_SUBPOSET_INDEX with value x.
  ///
  primitive_value(const namespace_relative_subposet_index& x);

  ///
  /// Conversion from bool;
  /// creates a new primitive value of type BOOL with value x.
  ///
  primitive_value(const bool& x);

  ///
  /// Conversion from char;
  /// creates a new primitive value of type CHAR with value x.
  ///
  primitive_value(const char& x);

  ///
  /// Conversion from signed char;
  /// creates a new primitive value of type SIGNED_CHAR with value x.
  ///
  primitive_value(const signed char& x);

  ///
  /// Conversion from short int;
  /// creates a new primitive value of type SHORT_INT with value x.
  ///
  primitive_value(const short int& x);

  ///
  /// Conversion from int;
  /// creates a new primitive value of type INT with value x.
  ///
  primitive_value(const int& x);

  ///
  /// Conversion from long int;
  /// creates a new primitive value of type LONG_INT with value x.
  ///
  primitive_value(const long int& x);

  ///
  /// Conversion from long long int;
  /// creates a new primitive value of type LONG_LONG_INT with value x.
  ///
  primitive_value(const long long int& x);

  ///
  /// Conversion from unsigned char;
  /// creates a new primitive value of type UNSIGNED_CHAR with value x.
  ///
  primitive_value(const unsigned char& x);

  ///
  /// Conversion from unsigned short int;
  /// creates a new primitive value of type UNSIGNED_SHORT_INT with value x.
  ///
  primitive_value(const unsigned short int& x);

  ///
  /// Conversion from unsigned int;
  /// creates a new primitive value of type UNSIGNED_INT with value x.
  ///
  primitive_value(const unsigned int& x);

  ///
  /// Conversion from unsigned long int;
  /// creates a new primitive value of type UNSIGNED_LONG_INT with value x.
  ///
  primitive_value(const unsigned long int& x);

  ///
  /// Conversion from unsigned long long int;
  /// creates a new primitive value of type UNSIGNED_LONG_LONG_INT with value x.
  ///
  primitive_value(const unsigned long long int& x);

  ///
  /// Conversion from float;
  /// creates a new primitive value of type FLOAT with value x.
  ///
  primitive_value(const float& x);

  ///
  /// Conversion from double;
  /// creates a new primitive value of type DOUBLE with value x.
  ///
  primitive_value(const double& x);

  ///
  /// Conversion from long double;
  /// creates a new primitive value of type LONG_DOUBLE with value x.
  ///
  primitive_value(const long double& x);

  ///
  /// Conversion from namespace_relative_member_index_pod_type;
  /// creates a new primitive value of type NAMESPACE_RELATIVE_MEMBER_INDEX_POD_TYPE with value x.
  ///
  primitive_value(const namespace_relative_member_index_pod_type& x);

  ///
  /// Conversion from namespace_relative_subposet_index_pod_type;
  /// creates a new primitive value of type NAMESPACE_RELATIVE_SUBPOSET_INDEX_POD_TYPE with value x.
  ///
  primitive_value(const namespace_relative_subposet_index_pod_type& x);

  // ===========================================================
  // ASSIGNMENT OPERATORS
  // ===========================================================

  ///
  /// Copy assignment.
  ///
  primitive_value& operator=(const primitive_value& x);

  ///
  /// Assignment from pointer.
  ///
  primitive_value& operator=(void* x);

  ///
  /// Assignment from pointer.
  ///
  primitive_value& operator=(const void* x);

  ///
  /// Assignment from C string.
  ///
  primitive_value& operator=(char* x);

  ///
  /// Assignment from C string.
  ///
  primitive_value& operator=(const char* x);

  ///
  /// Assignment from primitive of type T
  ///
  template <typename T>
  primitive_value& operator=(const T& x);

  // ===========================================================
  // CONVERSION TO PRIMITIVE
  // ===========================================================

  //   ///
  //   /// Conversion to primitive of type T.
  //   ///
  //   template <typename T>
  //   operator T() const;

  ///
  /// Conversion to bool.
  ///
  operator bool() const;

  ///
  /// Conversion to char.
  ///
  operator char() const;

  ///
  /// Conversion to signed char.
  ///
  operator signed char() const;

  ///
  /// Conversion to short int.
  ///
  operator short int() const;

  ///
  /// Conversion to int.
  ///
  operator int() const;

  ///
  /// Conversion to long int.
  ///
  operator long int() const;

  ///
  /// Conversion to long long int.
  ///
  operator long long int() const;

  ///
  /// Conversion to unsigned char.
  ///
  operator unsigned char() const;

  ///
  /// Conversion to unsigned short int.
  ///
  operator unsigned short int() const;

  ///
  /// Conversion to unsigned int.
  ///
  operator unsigned int() const;

  ///
  /// Conversion to unsigned long int.
  ///
  operator unsigned long int() const;

  ///
  /// Conversion to unsigned long long int.
  ///
  operator unsigned long long int() const;

  ///
  /// Conversion to float.
  ///
  operator float() const;

  ///
  /// Conversion to double.
  ///
  operator double() const;

  ///
  /// Conversion to long double.
  ///
  operator long double() const;

  ///
  /// Conversion to void*.
  ///
  operator void*() const;

  ///
  /// Conversion to char*.
  ///
  operator char*() const;

  ///
  /// Conversion to namespace_relative_member_index_pod_type.
  ///
  operator namespace_relative_member_index_pod_type() const;

  ///
  /// Conversion to namespace_relative_subposet_index_pod_type.
  ///
  operator namespace_relative_subposet_index_pod_type() const;

  // No conversion to string operator; 
  // creates ambiguity in conversion to string!
  

  // ===========================================================
  // DESTRUCTOR
  // ===========================================================

  ///
  /// Destructor
  ///
  ~primitive_value();

  // ===========================================================
  // VALUE
  // ===========================================================

  ///
  /// The value of this.
  ///
  primitive_buffer_type& value()
  {
    return _value;
  };

  ///
  /// The value of this, const version.
  ///
  const primitive_buffer_type& value() const
  {
    return _value;
  };

  ///
  /// Type id of the primitive type.
  ///
  primitive_type& id()
  {
    return _id;
  };

  ///
  /// Type id of the primitive type, const version.
  ///
  const primitive_type& id() const
  {
    return _id;
  };

  // ===========================================================
  // SUPPORT FOR STREAMS
  // ===========================================================

  ///
  /// Converts this to a string (for stream insertion).
  ///
  std::string to_string() const;

  ///
  /// Converts this from a string (from stream extraction);
  /// returns true if operation successful, false otherwise.
  ///
  bool from_string(const std::string& x);

private:

  ///
  /// The value of this.
  ///
  primitive_buffer_type _value;

  ///
  /// Type id of the primitive type.
  ///
  primitive_type _id;

  ///
  /// Initializes prototypes for specific primitive types.
  ///
  static block<primitive_value>& make_prototypes();
};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Comparison of xpv1 to xpv2.
///
SHEAF_DLL_SPEC 
bool
operator==(const primitive_value& xpv1, const primitive_value& xpv2);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const void* xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const void* xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const char* xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const char* xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const string& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const string& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const scoped_index& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const scoped_index& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const namespace_relative_member_index& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const namespace_relative_member_index& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const namespace_relative_subposet_index& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const namespace_relative_subposet_index& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const bool& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const bool& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const char& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const char& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const signed char& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const signed char& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const short int& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const short int& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const int& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const int& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const long int& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const long int& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const long long int& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const long long int& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const unsigned char& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const unsigned char& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const unsigned short int& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const unsigned short int& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const unsigned int& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const unsigned int& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const unsigned long int& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const unsigned long int& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const unsigned long long& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const unsigned long long& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const float& xval); 

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const float& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const double& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const double& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const long double& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const long double& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const namespace_relative_member_index_pod_type& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const namespace_relative_member_index_pod_type& xval, const primitive_value& xpv);

///
/// Comparison of xpv to xval.
///
SHEAF_DLL_SPEC
bool
operator==(const primitive_value& xpv, const namespace_relative_subposet_index_pod_type& xval);

///
/// Comparison of xval to xpv.
///
SHEAF_DLL_SPEC
bool
operator==(const namespace_relative_subposet_index_pod_type& xval, const primitive_value& xpv);

///
/// Inserts primitive_value xpv into ostream xos.
///
SHEAF_DLL_SPEC
ostream&
operator<<(ostream& xos, const primitive_value& xpv);

///
/// The deep size of the referenced object of type primitive_value.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const primitive_value& xpv, bool xinclude_shallow = true);
 


} // namespace sheaf

#endif // ifndef PRIMITIVE_VALUE_H
