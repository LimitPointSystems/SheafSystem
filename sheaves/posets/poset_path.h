
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

// Interface for class poset_path

#ifndef POSET_PATH_H
#define POSET_PATH_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif


namespace sheaf
{
 
  class namespace_poset;
  class primitive_value;
  
 
///
///  A path defined by a poset name
///  and a member name separated by a forward slash ('/').
///  For example: "cell_definitions/triangle".
///
class SHEAF_DLL_SPEC poset_path
{

public:

  ///
  /// Default constructor.
  ///
  poset_path();

  ///
  /// Copy constructor
  ///
  poset_path(const poset_path& xposet_path);

  ///
  /// Creates an instance with poset_name() == xposet_name and
  /// member_name() == xmember_name.
  ///
  poset_path(const string& xposet_name, const string& xmember_name);

  ///
  /// Destructor
  ///
  ~poset_path();

  ///
  /// Conversion from string.
  ///
  poset_path(const string& xpath);

  ///
  /// Conversion from C string.
  ///
  poset_path(const char* xpath);

  ///
  /// Conversion from primitive_value.
  ///
  poset_path(const primitive_value& xpath);

  ///
  /// Conversion to primitive_value.
  ///
  operator primitive_value() const;

  ///
  /// Assignment from poset_path.
  ///
  poset_path& operator=(const poset_path& xposet_path);

  ///
  /// Assignment from string.
  ///
  poset_path& operator=(const string& xpath);

  ///
  /// Assignment from C string.
  ///
  poset_path& operator=(const char* cpath);

  ///
  /// Assignment from primitive_value.
  ///
  poset_path& operator=(const primitive_value& xpath);

  ///
  /// True if both poset name and member name are empty.
  ///
  bool empty() const;

  ///
  /// True if both poset name and member name are not empty.
  ///
  bool full() const;

  ///
  /// True if xname is not empty and contains
  /// only name legal characters.
  ///
  static bool is_valid_name(const string& xname);

  ///
  /// True if xpath is empty, or if not empty, contains
  /// only legal characters and contains just a poset name, or
  /// contains a poset name and delimiter(), or contains
  /// contains a poset name, a delimiter(), and a member name.
  ///
  static bool is_valid_path(const string& xpath);

  ///
  /// True if this specifies the same poset and member as xother
  ///
  bool operator==(const poset_path& xother) const;

  ///
  /// True if this specifies the same poset and member as xother
  ///
  bool operator==(const string& xother) const;

  ///
  /// True if this specifies the same poset and member as xother
  ///
  bool operator==(const char* xother) const;

  ///
  /// The full path as a string.
  ///
  string path() const;

  ///
  /// The poset name part of the path.
  ///
  string poset_name() const;

  ///
  /// Sets poset_name() to xname.
  ///
  void put_poset_name(const string& xname);

  ///
  ///  The member name part of the path.
  ///
  string member_name() const;

  ///
  /// Sets member_name() to xname.
  ///
  void put_member_name(const string& xname);

  ///
  /// The characters a name is allowed to contain.
  ///
  static const string& name_legal_characters();

  ///
  /// The path delimiter; used to separate poset name from member name.
  ///
  static char delimiter();

  ///
  /// The characters a path is allowed to contain.
  ///
  static const string& path_legal_characters();

  ///
  /// Extracts poset name from xpath.
  ///
  static string poset_name(const string& xpath);

  ///
  /// Extracts delimiter from xpath.
  ///
  static string delimiter(const string& xpath);

  ///
  /// Extracts member name from xpath.
  ///
  static string member_name(const string& xpath);

  ///
  ///  Write instance information to an ostream (default = stdout).
  ///
  void to_stream(ostream& xos = cout) const;

  ///
  /// Creates a string xprefix_xindex_xsuffix.
  ///
  static string make_name(const string& xprefix, int xindex, const string& xsuffix);

  ///
  /// Creates a string reserved_prefix()_xprefix_xindex_xsuffix.
  ///
  static string make_reserved_name(const string& xprefix, const size_t& xindex, const string& xsuffix);

  ///
  /// Creates the standard name for the block with index xindex.
  ///
  static string block_name(const size_t& xindex);

  ///
  /// Creates the standard block name associated with
  /// the neighborhood with name xneighborhood_name.
  ///
  static string block_name(const string& xneighborhood_name);

  ///
  /// Creates the standard name for the neighborhood of the block with index xindex.
  ///
  static string block_neighborhood_name(const size_t& xindex);

  ///
  /// Creates the standard neighborhood name associated with
  /// the block with name xblock_name.
  ///
  static string block_neighborhood_name(const string& xblock_name);

  ///
  /// Extracts the index from a block name or block neighborhood name.
  ///
  static size_t block_id(const string& xname);

  ///
  /// Prefix for identifying member names reserved by the sheaf system.
  ///
  static string reserved_prefix();

  ///
  /// Prefix for identifying boundary members.
  ///
  static string boundary_prefix();

  ///
  /// Creates the standard boundary name associated with
  /// the member with name xmbr_name.
  ///
  static string boundary_name(const string& xmbr_name);

  ///
  /// Prefix for identifying blocks.
  ///
  static string block_prefix();

  ///
  /// Prefix for identifying neighborhoods.
  ///
  static string neighborhood_prefix();

  ///
  /// @deprecated Use namespace_poset::current_namespace() instead.
  /// The current working namespace; the root for this path.
  /// Synonym for namespace_poset::current_workspace().
  ///
  namespace_poset* current_namespace() const;

  ///
  /// @deprecated Use namespace_poset::current_namespace()->contains_path(*this) instead.
  /// True if the state this refers to exists
  /// in the current name space.
  ///
  bool state_exists(bool xauto_access) const;

  ///
  /// @deprecated Use namespace_poset::current_namespace()->contains_poset(*this) instead.
  /// True if this refers to a poset and
  /// the poset exists in the current name space.
  ///
  bool poset_exists(bool xauto_access) const;

  ///
  /// @deprecated Use namespace_poset::current_namespace()->contains_poset_member(*this) instead.
  /// True if this refers to a poset member and
  /// the member exists in the current name space.
  ///
  bool member_exists(bool xauto_access) const;

  ///
  /// @deprecated Use namespace_poset::current_namespace()->poset_state_is_read_accessible(*this) instead.
  /// True if the state this refers to is read accessible.
  ///
  bool state_is_read_accessible(bool xauto_access) const;

  ///
  /// @deprecated Use namespace_poset::current_namespace()->poset_state_is_read_write_accessible(*this) instead.
  /// True if the state this refers to is read-write accessible.
  ///
  bool state_is_read_write_accessible(bool xauto_access) const;

  ///
  /// True if the schema member this refers to conforms to
  /// the schema member xother refers to in the current namespace.
  ///
  bool conforms_to(const poset_path& xother, bool xauto_access) const;

  ///
  /// True if the schema member this refers to conforms to
  /// the schema member xother refers to in name space xns.
  ///
  bool conforms_to(const namespace_poset& xns, const poset_path& xother, bool xauto_access) const;


private:

  ///
  /// The poset name.
  ///
  string _poset_name;

  ///
  /// The member name.
  ///
  string _member_name;

//   ///
//   /// True if xname contains only path legal characters.
//   ///
//   static bool contains_legal_characters(const string& xname, const string& xlegal_chars);

  ///
  /// Extracts poset name, delimiter, and member names from xpath.
  ///
  static void parse_path(const string& xpath, 
                         string& xposet_name, 
                         string& xdelimiter, 
                         string& xmember_name);


};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// Insert poset_path& pp into ostream& os.
///
SHEAF_DLL_SPEC
ostream & operator << (ostream& os, const poset_path& pp);

///
/// True if and only if xpath.path() == xprim.value().c_string_primitive.
///
SHEAF_DLL_SPEC
bool operator==(const poset_path& xpath, const primitive_value& xprim);

///
/// True if and only if xpath.path() == xprim.value().c_string_primitive.
///
SHEAF_DLL_SPEC
bool operator==(const primitive_value& xprim, const poset_path& xpath);

///
/// The deep size of the referenced object of type poset_path.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const poset_path& xpath, bool xinclude_shallow = true);
 
 
} // namespace sheaf

#endif // ifndef POSET_PATH_H
