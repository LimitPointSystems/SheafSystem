
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

// Declarations relating to sheaf system primitive types.

#ifndef PRIMITIVE_TYPE_H
#define PRIMITIVE_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_CLIMITS_H
#include "std_climits.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

// =============================================================================
// PRIMITIVE TYPES FACET
// =============================================================================

///
/// Type ids for sheaf primitives.
///
enum primitive_type
{
  // Ids for primitive types.

  // Start at 2 to keep enum and primitives poset member index in sync.

  PRIMITIVE_TYPE_BEGIN = 2,

  BOOL = 2, // Must be same as BEGIN.
  CHAR, // 3

  SIGNED_CHAR, // 4
  SHORT_INT, // 5
  INT, // 6
  INT_TYPE = 6, // typedef for int
  POD_INDEX_TYPE = 6, // typdef for int
  LONG_INT, // 7
  LONG_LONG_INT, // 8

  UNSIGNED_CHAR, // 9
  UNSIGNED_SHORT_INT, // 10
  UNSIGNED_INT, // 11
  UNSIGNED_LONG_INT, // 12
  SIZE_TYPE = 12, // typedef for unsigned long
  UNSIGNED_LONG_LONG_INT, // 13

  FLOAT, // 14
  DOUBLE, // 15
  LONG_DOUBLE, // 16

  VOID_STAR, // 17
  C_STRING, // 18

  NAMESPACE_RELATIVE_MEMBER_INDEX, // 19
  NAMESPACE_RELATIVE_SUBPOSET_INDEX, // 20
  PRIMITIVE_TYPE_END, // Must follow last type id.


  // Don't forget to update the functions below
  // and primitive_buffer_type if you change this enum.

  NOT_A_PRIMITIVE_TYPE = INT_MAX
};

///
/// Prefix increment operator for primitive_type.
///
primitive_type& operator++(primitive_type& x);

///
/// True if xindex is a valid primitive index.
///
SHEAF_DLL_SPEC 
bool is_primitive_index(pod_index_type xindex);

///
/// Insert primitive_type xpt into ostream& os.
///
SHEAF_DLL_SPEC
std::ostream & operator << (std::ostream& os, const primitive_type& xpt);

///
/// Extract primitive_type xpt from istream& is.
///
SHEAF_DLL_SPEC
std::istream & operator >> (std::istream& is, primitive_type& xpt);


// =============================================================================
// PRIMITIVE DESCRIPTORS FACET
// =============================================================================

struct SHEAF_DLL_SPEC primitive_descriptor
{
  size_t size;
  size_t alignment;
  pod_index_type index;
};

///
/// Insert primitive_descriptor into ostream& os.
///
SHEAF_DLL_SPEC
std::ostream & operator << (std::ostream& os, const primitive_descriptor& xpd);


///
/// Smallest offset greater than or equal to xoffset that has alignment xalignment.
///
inline size_t align(const size_t xoffset, const size_t xalignment)
{
  // Note: the C++ standard, section 5.3.4 paragraph 10, states
  // allocation routines are assumed to return memory properly aligned
  // for any object type, and that in particular, the beginning
  // address of a char array is so aligned, so that char arrays
  // can be used to store any type of object.
  // Since the base of the array is thus aligned, we can properly
  // align any object within the array by properly aligning the
  // offset from the base of the array. This approach avoids
  // the need for implementation dependent conversion of pointers to
  // integer types to do arithmetic on the pointer.
  //
  // Explanation of the expression used here:
  // Let o = xoffset, a = xalignment.
  // The expression being evaluated is: ((o+a-1)/a)*a
  // Various cases:
  // o = 0 => ((0+a-1)/a)*a = 0*a = 0
  // o = 1 => ((1+a-1)/a)*a = 1*a = a
  // 1 < o <= a => ((a+a-1)/a)*a = 1*a = a
  // na < o <= (n+1)a => (((n+1)a + a - 1)/a)*a = (n+1)*a
  return ((xoffset + xalignment - 1)/xalignment)*xalignment;
};

// =============================================================================
// PRIMITIVE_BUFFER_TYPE FACET
// =============================================================================

///
/// Type of buffer large enough to hold any primitive type.
///
union primitive_buffer_type
{
  bool bool_primitive;
  char char_primitive;

  signed char signed_char_primitive;
  short int short_int_primitive;
  int int_primitive;
  long int long_int_primitive;
  long long int long_long_int_primitive;

  unsigned char unsigned_char_primitive;
  unsigned short int unsigned_short_int_primitive;
  unsigned int unsigned_int_primitive;
  unsigned long int unsigned_long_int_primitive;
  unsigned long long int unsigned_long_long_int_primitive;

  float float_primitive;
  double double_primitive;
  long double long_double_primitive;

  void_star void_star_primitive;
  c_string c_string_primitive;

  namespace_relative_member_index_pod_type namespace_relative_member_index_primitive;
  namespace_relative_subposet_index_pod_type namespace_relative_subposet_index_primitive;

  int_type int_type_primitive;
  pod_index_type pod_index_type_primitive;
  size_type size_type_primitive;
};

} // end namespace sheaf

#endif // ifndef PRIMITIVE_TYPE_H
