
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

// Implementation for class poset_path

#include "poset_path.h"

#include "assert_contract.h"
#include "namespace_poset.h"
#include "primitive_value.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "std_sstream.h"

using namespace sheaf;
using namespace std;

//#define DIAGNOSTIC_OUTPUT

///
sheaf::poset_path::
poset_path()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(empty());

  // Exit:

  return;
}

///
sheaf::poset_path::
poset_path(const poset_path& xposet_path)
{

  // Preconditions:

  // Body:

  *this = xposet_path;

  // Postconditions:

  ensure(*this == xposet_path);

  // Exit:

  return;
}

///
sheaf::poset_path::
poset_path(const std::string& xposet_name, const std::string& xmember_name)
{
  // Preconditions:

  require(!xposet_name.empty());
  require(is_valid_path(xposet_name + delimiter() + xmember_name));

  // Body:

  *this = xposet_name + delimiter() + xmember_name;

  // Postconditions:

  ensure(poset_name() == xposet_name);
  ensure(member_name() == xmember_name);

  // Exit:

  return;
}

///
sheaf::poset_path::
~poset_path()
{

  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

///
sheaf::poset_path::
poset_path(const std::string& xpath)
{
  // Preconditions:

  require(is_valid_path(xpath));

  // Body:

  *this = xpath;

  // Postconditions:

  ensure(*this == xpath);

  // Exit:

  return;
}

///
sheaf::poset_path::
poset_path(const char* xpath)
{
  // Preconditions:

  require(xpath != 0);
  require(is_valid_path(xpath));

  // Body:

  *this = xpath;


  // Postconditions:

  ensure((*this) == xpath);
}

///
sheaf::poset_path::
poset_path(const primitive_value& xpath)
{
  // Preconditions:

  require(xpath.id() == C_STRING);
  require(is_valid_path(xpath.value().c_string_primitive));

  // Body:

  *this = xpath;


  // Postconditions:

  ensure((*this) == xpath);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// $$SCRIBBLE kabuch: Warning: member `operator sheaf::primitive_value' of class `poset_path' cannot be found

///
sheaf::poset_path::
operator sheaf::primitive_value() const
{
  // Preconditions:

  // Body:
  
  primitive_value result = path().c_str();

  // Postconditions:

  ensure(result.id() == C_STRING);
  ensure(string(result) == path());
  
  // Exit:

  return result;
}
#endif // ifndef DOXYGEN_SHOULD_SKIP_THIS

///
sheaf::poset_path&
sheaf::poset_path::
operator=(const poset_path& xposet_path)
{
  // Preconditions:

  // Body:

  _poset_name = xposet_path._poset_name;
  _member_name = xposet_path._member_name;


  // Postconditions:

  ensure(*this == xposet_path);

  // Exit:

  return *this;
}


///
sheaf::poset_path&
sheaf::poset_path::
operator=(const std::string& xpath)
{
  // Preconditions:

  require(is_valid_path(xpath));

  // Body:

  string ldelimiter;
  parse_path(xpath, _poset_name, ldelimiter, _member_name);

  // Postconditions:

  ensure(*this == xpath);

  // Exit:

  return *this;
}

///
sheaf::poset_path&
sheaf::poset_path::
operator=(const char* cpath)
{
  // Preconditions:

  require(cpath != 0);
  require(is_valid_path(cpath));

  // Body:

  string ldelimiter;
  parse_path(cpath, _poset_name, ldelimiter, _member_name);

  // Postconditions:

  ensure(*this == cpath);

  // Exit:

  return *this;
}

///
sheaf::poset_path&
sheaf::poset_path::
operator=(const primitive_value& xposet_path)
{
  // Preconditions:

  // Body:

  *this = xposet_path.value().c_string_primitive;

  // Postconditions:

  ensure(*this == xposet_path);

  // Exit:

  return *this;
}

///
bool
sheaf::poset_path::
empty() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _poset_name.empty() && _member_name.empty();

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::poset_path::
full() const
{
  bool result;

  // Preconditions:

  // Body:

  result = !_poset_name.empty() && !_member_name.empty();

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::poset_path::
is_valid_name(const std::string& xname)
{
  bool result;

  // Preconditions:

  // Body:

  //  result = (!xname.empty() && contains_legal_characters(xname, name_legal_characters()));
  result = (!xname.empty() && (xname.find_first_not_of(name_legal_characters()) == string::npos));
  
  // Postconditions:

  //  ensure(result == (!xname.empty() && contains_legal_characters(xname, name_legal_characters())));
  ensure(result == (!xname.empty() && (xname.find_first_not_of(name_legal_characters()) == string::npos)));
  
  // Exit

  return result;
}

///
bool
sheaf::poset_path::
is_valid_path(const std::string& xpath)
{

  // Preconditions:

  // Body:

  bool result = (xpath.find_first_not_of(path_legal_characters()) == string::npos);

  if(result)
  {
    string lposet_name, ldelimiter, lmember_name;
    parse_path(xpath, lposet_name, ldelimiter, lmember_name);
    result =
      lposet_name.empty() ? (ldelimiter.empty() && lmember_name.empty()) : true;
  }  

  // Postconditions:

  ensure(result == ((xpath.find_first_not_of(path_legal_characters()) == string::npos) && 
                    (!poset_name(xpath).empty() || (delimiter(xpath).empty() && member_name(xpath).empty()))));

  // Exit

  return result;
}

///
bool
sheaf::poset_path::
operator==(const poset_path& xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result =
    (_poset_name == xother._poset_name) && (_member_name == xother._member_name);

  // Postconditions:

  return result;
}


///
bool
sheaf::poset_path::
operator==(const std::string& xother) const
{
  bool result;

  // Preconditions:

  // Body:

  string lposet_name, ldelimiter, lmember_name;
  parse_path(xother, lposet_name, ldelimiter, lmember_name);
  result =
    (_poset_name == lposet_name) && (_member_name == lmember_name);


  // Postconditions:

  return result;
}


///
bool
sheaf::poset_path::
operator==(const char* xother) const
{
  bool result;

  // Preconditions:

  require(xother != 0);

  // Body:

  string lother(xother);
  result = operator==(lother);

  // Postconditions:

  return result;
}


///
std::string
sheaf::poset_path::
path() const
{
  // Preconditions:

  // Body:

  string result = _poset_name;
  if(!_member_name.empty())
  {
    result += delimiter() + _member_name;
  }

  // Postconditions:

  //ensure(is_valid_path(result));

  return result;
}


///
std::string
sheaf::poset_path::
poset_name() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _poset_name;
}

///
void
sheaf::poset_path::
put_poset_name(const std::string& xname)
{
  // Preconditions:

  require(is_valid_name(xname));

  // Body:

  _poset_name = xname;

  // Postconditions:

  ensure(poset_name() == xname);

  // Exit:

  return;
}

///
std::string
sheaf::poset_path::
member_name() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  return _member_name;

}

///
void
sheaf::poset_path::
put_member_name(const std::string& xname)
{
  // Preconditions:

  require(is_valid_name(xname));

  // Body:

  _member_name = xname;

  // Postconditions:

  ensure(member_name() == xname);

  // Exit:

  return;
}

const std::string&
sheaf::poset_path::
name_legal_characters()
{
  // cout << endl << "Entering poset_path::name_legal_characters." << endl;

  // Preconditions:


  // Body:

  // @hack temporarily allow characters other than [A-Za-z0-9_] in
  // poset and poset member names, until we get a chance to purge all
  // the offending names in the standard name spaces and examples.

  static const string result("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_ -,.=+()*:?");

  // Postconditions:

  ensure(result == "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_ -,.=+()*:?");

  // Exit:

  // cout << "Leaving poset_path::name_legal_characters." << endl;
  return result;
}

 
char
sheaf::poset_path::
delimiter()
{
  // cout << endl << "Entering poset_path::delimiter." << endl;

  // Preconditions:


  // Body:

  char result = '/';

  // Postconditions:

  ensure(result == '/');

  // Exit:

  // cout << "Leaving poset_path::delimiter." << endl;
  return result;
}

const std::string&
sheaf::poset_path::
path_legal_characters()
{
  // cout << endl << "Entering poset_path::path_legal_characters." << endl;

  // Preconditions:


  // Body:

  static const string result(name_legal_characters() + delimiter());

  // Postconditions:

  ensure(result == (name_legal_characters() + delimiter()));
  
  // Exit:

  // cout << "Leaving poset_path::path_legal_characters." << endl;
  return result;
}

std::string
sheaf::poset_path::
poset_name(const std::string& xpath)
{
  // cout << endl << "Entering poset_path::poset_name." << endl;

  // Preconditions:


  // Body:

  string result, ldelim, lmbr_name;
  
  parse_path(xpath, result, ldelim, lmbr_name);

  // Postconditions:


  // Exit:

  // cout << "Leaving poset_path::poset_name." << endl;
  return result;
}

std::string
sheaf::poset_path::
delimiter(const std::string& xpath)
{
  // cout << endl << "Entering poset_path::delimiter." << endl;

  // Preconditions:


  // Body:

  string lposet_name, result, lmbr_name;
  
  parse_path(xpath, lposet_name, result, lmbr_name);

  // Postconditions:


  // Exit:

  // cout << "Leaving poset_path::delimiter." << endl;
  return result;
}


std::string
sheaf::poset_path::
member_name(const std::string& xpath)
{
  // cout << endl << "Entering poset_path::member_name." << endl;

  // Preconditions:


  // Body:

  string lposet_name, ldelim, result;
  
  parse_path(xpath, lposet_name, ldelim, result);

  // Postconditions:

  ensure(delimiter(xpath).empty() ? result.empty() : true);
  
  // Exit:

  // cout << "Leaving poset_path::member_name." << endl;
  return result;
}


///
void
sheaf::poset_path::
to_stream(ostream& xos) const
{
  xos << *this;
}

///
std::string
sheaf::poset_path::
make_name(const std::string& xprefix, int xindex, const std::string& xsuffix)
{
  string result;

  // Preconditions:


  // Body:

  stringstream lname_stream;
  lname_stream << xprefix << xindex << xsuffix;
  lname_stream >> result;

  // Postconditions:

  ensure(!result.empty());
  ensure(!xprefix.empty() ? result.find(xprefix) == 0 : true);
  ensure(!xsuffix.empty() ?
         (result.find(xsuffix) + xsuffix.size()) == result.size() : true);

  // Exit:

  return result;
}

///
std::string
sheaf::poset_path::
make_reserved_name(const std::string& xprefix, const size_t& xindex, const std::string& xsuffix)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(postcondition_of(make_name(reserved_prefix()+xprefix, xindex, xsuffix)));

  // Exit:

  return make_name(reserved_prefix()+xprefix, xindex, xsuffix);
}

///
std::string
sheaf::poset_path::
block_name(const size_t& xindex)
{
  string result;

  // Preconditions:

  require(index_traits<size_t>::is_valid(xindex));

  // Body:

  result = make_name(block_prefix(), xindex, "");

  // Postconditions:

  ensure(!result.empty());
  ensure(result.find(block_prefix()) == 0);

  // Exit:

  return result;
}



///
std::string
sheaf::poset_path::
block_name(const std::string& xneighborhood_name)
{
  string result;

  // Preconditions:

  require(xneighborhood_name.find(neighborhood_prefix()) != string::npos);

  // Body:

  result = xneighborhood_name.substr(neighborhood_prefix().size());

  // Postconditions:

  ensure(!result.empty());
  ensure(result.find(block_prefix()) == 0);

  // Exit:

  return result;
}



///
std::string
sheaf::poset_path::
block_neighborhood_name(const size_t& xindex)
{
  string result;

  // Preconditions:

  require(index_traits<size_t>::is_valid(xindex));

  // Body:

  result = neighborhood_prefix() + block_name(xindex);

  // Postconditions:

  ensure(!result.empty());
  ensure(result.find(neighborhood_prefix()) == 0);

  // Exit:

  return result;
}



///
std::string
sheaf::poset_path::
block_neighborhood_name(const std::string& xblock_name)
{
  string result;

  // Preconditions:

  ensure(xblock_name.find(block_prefix()) == 0);

  // Body:

  result = neighborhood_prefix() + xblock_name;

  // Postconditions:

  ensure(!result.empty());
  ensure(result.find(neighborhood_prefix()) == 0);

  // Exit:

  return result;
}

///
size_t
sheaf::poset_path::
block_id(const std::string& xname)
{
  size_t result;

  // Preconditions:

  require(xname.find(block_prefix()) != string::npos);

  // Body:

  stringstream lname_stream;
  string lblock_prefix = block_prefix();
  lname_stream << xname.substr(xname.find(lblock_prefix) + lblock_prefix.size());
  lname_stream >> result;

  // Postconditions:

  // Exit:

  return result;
}


///
std::string
sheaf::poset_path::
reserved_prefix()
{

  // Preconditions:


  // Body:

  string result("__");

  // Postconditions:


  // Exit:

  return result;
}



///
std::string
sheaf::poset_path::
boundary_prefix()
{

  // Preconditions:


  // Body:

  string result(reserved_prefix() + "bdy_of_");

  // Postconditions:


  // Exit:

  return result;
}

///
std::string
sheaf::poset_path::
boundary_name(const std::string& xmbr_name)
{
  string result;

  // Preconditions:

  // Body:

  result = boundary_prefix() + xmbr_name;

  // Postconditions:

  ensure(!result.empty());
  ensure(result.find(boundary_prefix()) == 0);

  // Exit:

  return result;
}

///
std::string
sheaf::poset_path::
block_prefix()
{

  // Preconditions:


  // Body:

  string result(reserved_prefix() + "block_");

  // Postconditions:


  // Exit:

  return result;
}



///
std::string
sheaf::poset_path::
neighborhood_prefix()
{

  // Preconditions:


  // Body:

  string result(reserved_prefix() + "neighborhood_of_");

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::namespace_poset*
sheaf::poset_path::
current_namespace() const
{
  namespace_poset* result;

  // Preconditions:

  // Body:

  result = namespace_poset::current_namespace();

  // Postconditions:

  ensure(result == namespace_poset::current_namespace());

  // Exit:

  return result;
}


///
bool
sheaf::poset_path::
state_exists(bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(current_namespace() != 0);
  require(xauto_access || current_namespace()->state_is_read_accessible());

  // Body:

  result = !_poset_name.empty();
  if(result)
  {
    if(!_member_name.empty())
    {
      result = current_namespace()->contains_poset_member(*this, xauto_access);
    }
    else
    {
      result = current_namespace()->contains_poset(*this, xauto_access);
    }
  }

  // Postconditions:


  // Exit:

  return result;
}


///
bool
sheaf::poset_path::
poset_exists(bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(current_namespace() != 0);
  require(xauto_access || current_namespace()->state_is_read_accessible());

  // Body:

  result = !empty() && state_exists(xauto_access);

  // Postconditions:


  // Exit:

  return result;
}



///
bool
sheaf::poset_path::
member_exists(bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(current_namespace() != 0);
  require(xauto_access || current_namespace()->state_is_read_accessible());

  // Body:

  result = full() && state_exists(xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

///
bool
sheaf::poset_path::
state_is_read_accessible(bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(current_namespace() != 0);
  require(xauto_access || current_namespace()->state_is_read_accessible());
  require(state_exists(xauto_access));

  // Body:

  result =
    current_namespace()->member_poset(*this, xauto_access).state_is_read_accessible();

  // Postconditions:


  // Exit:

  return result;
}

///
bool
sheaf::poset_path::
state_is_read_write_accessible(bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(current_namespace() != 0);
  require(xauto_access || current_namespace()->state_is_read_accessible());
  require(state_exists(xauto_access));

  // Body:

  result =
    current_namespace()->member_poset(*this, xauto_access).state_is_read_write_accessible();

  // Postconditions:


  // Exit:

  return result;
}

///
bool
sheaf::poset_path::
conforms_to(const poset_path& xother, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(current_namespace() != 0);
  require(xauto_access || current_namespace()->state_is_read_accessible());
  require(state_exists(xauto_access));
  require(xauto_access || state_is_read_accessible(xauto_access));
  require(xother.state_exists(xauto_access));
  require(xauto_access || xother.state_is_read_accessible(xauto_access));

  // Body:

  result = poset_name() == xother.poset_name();

  if(result)
  {

    schema_poset_member lthis_schema(current_namespace(), *this, xauto_access);
    schema_poset_member lother_schema(current_namespace(), *this, xauto_access);

    if(xauto_access)
    {
      lthis_schema.get_read_access();
    }

    result = lthis_schema.conforms_to(lother_schema);

    if(xauto_access)
    {
      lthis_schema.release_access();
    }

    lthis_schema.detach_from_state();
    lother_schema.detach_from_state();
  }

  // Postconditions:


  // Exit:

  return result;
}

///
bool
sheaf::poset_path::
conforms_to(const namespace_poset& xns, const poset_path& xother, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));
  require(xns.contains_path(*this, xauto_access));
  require(xns.member_poset(*this, xauto_access).state_is_auto_read_accessible(xauto_access));
  require(xns.contains_path(xother, xauto_access));
  require(xns.member_poset(xother, xauto_access).state_is_auto_read_accessible(xauto_access));

  // Body:

  result = schema_poset_member::conforms_to(xns, *this, xother, xauto_access);

  // Postconditions:


  // Exit:

  return result;
}


// ===========================================================
// PRIVATE MEMBER FUNCTIONS
// ===========================================================

// bool
// sheaf::poset_path::
// contains_legal_characters(const std::string& xname, const std::string& xlegal_chars)
// {
//   bool result;

//   // Preconditions:

//   // Body:

//   string::size_type lindex = xname.find_first_not_of(xlegal_chars);

// #ifdef DIAGNOSTIC_OUTPUT
//   if(lindex != string::npos)
//   {
//     cout << "poset_path::contains_name_legal_characters illegal char in name:" << xname
//     << " position: " << lindex
//     << " char '" << xname[lindex] << "'"
//     << endl;
//   }
// #endif

//   result = (lindex == string::npos);

//   // Postconditions:

//   ensure(result == (xname.find_first_not_of(xlegal_chars) == string::npos));

//   // Exit

//   return result;
// }

///
void
sheaf::poset_path::
parse_path(const std::string& xpath,
           std::string& xposet_name,
           std::string& xdelimiter,
           std::string& xmember_name)
{

  // Preconditions:

  // Body:

  xposet_name.clear();
  xmember_name.clear();

  string::const_iterator itr = xpath.begin();
  while((itr != xpath.end()))
  {
    char c = *itr;
    ++itr;
    if(c == delimiter())
    {
      xdelimiter = c;
      break;
    }
    else
    {
      xposet_name.push_back(c);
    }
  }

  while((itr != xpath.end()))
  {
    xmember_name.push_back(*itr);
    ++itr;
  }

  // Postconditions:

  ensure(xdelimiter.empty() ? xmember_name.empty() : true);

  // Exit

  return;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

std::ostream& 
sheaf::
operator << (std::ostream& xos, const poset_path& xpp)
{
  xos << xpp.path();

  return xos;
}

bool
sheaf::
operator==(const poset_path& xpath, const primitive_value& xprim)
{
  require(xprim.id() == C_STRING);
  return xpath.path() == xprim.value().c_string_primitive;
}

bool
sheaf::
operator==(const primitive_value& xprim, const poset_path& xpath)
{
  require(xprim.id() == C_STRING);
  return xpath.path() == xprim.value().c_string_primitive;
}

size_t
sheaf::
deep_size(const poset_path& xpath, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}

