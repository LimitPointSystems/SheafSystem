//

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

 

//
// Implementation for class primitive_attributes

#include "primitive_attributes.h"

#include "assert_contract.h"
#include "block.impl.h"
#include "namespace_relative_member_index.h"
#include "namespace_relative_subposet_index.h"
#include "primitive_traits.h"
#include "std_map.h"
#include "std_sstream.h"

using namespace sheaf;

namespace
{
///
/// The type of the name to id map.
///
typedef map<string, sheaf::primitive_type> map_type;

///
/// Initializes the name to id map.
///
map_type& make_name_to_id_map()
{
  // Preconditions:


  // Body:

  static map_type result;

  if(result.empty())
  {
    for(sheaf::primitive_type i=sheaf::PRIMITIVE_TYPE_BEGIN; i<sheaf::PRIMITIVE_TYPE_END; ++i)
    {
      const sheaf::primitive_attributes& lprim = sheaf::primitive_attributes::prototype(i);
      result[lprim.name()] = i;
      stringstream lstrm(lprim.aliases());
      string lalias;
      while(lstrm >> lalias)
      {
        result[lalias] = i;
        lalias.clear();
      }
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "name to id map: " << endl;
  for(map_type::const_iterator litr = result.begin(); litr != result.end(); ++litr)
  {
    cout << litr->first << "  " << litr->second << endl;
  }
#endif

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
};
}

// ===========================================================
// STATIC FUNCTIONS
// ===========================================================

///
const sheaf::primitive_attributes&
sheaf::primitive_attributes::
prototype(pod_index_type xid)
{
  // Preconditions:

  //  require(is_primitive_index(xid));

  // Body:

  xid = is_primitive_index(xid) ? xid : PRIMITIVE_TYPE_END;

  static const block<primitive_attributes>& lprototypes = make_prototypes();
  primitive_attributes& result = lprototypes[xid];

  // Postconditions:

  ensure(static_cast<pod_index_type>(result.id()) == 
	 (is_primitive_index(xid) ? xid : static_cast<pod_index_type>(NOT_A_PRIMITIVE_TYPE)));

  // Exit:

  return result;
}

///
sheaf::primitive_type
sheaf::primitive_attributes::
id(const string& xtype_name)
{
  // Preconditions:

  require(!xtype_name.empty());

  // Body:

  static const map_type& lmap = make_name_to_id_map();

  primitive_type result = NOT_A_PRIMITIVE_TYPE;

  map_type::const_iterator litr = lmap.find(xtype_name);
  if(litr != lmap.end())
  {
    result = litr->second;
  }

  // Postconditions:

  // Exit:

  return result;
}



// ===========================================================
// CONSTRUCTORS
// ===========================================================

///
sheaf::primitive_attributes::
primitive_attributes()
{
  _id            = primitive_traits<void>::id();
  _size          = primitive_traits<void>::size();
  _alignment     = primitive_traits<void>::alignment();
  _name          = &primitive_traits<void>::name();
  _aliases       = &primitive_traits<void>::aliases();
  _hdf_type_name = &primitive_traits<void>::hdf_type_name();
  _hdf_type      = primitive_traits<void>::hdf_type();
}

///
sheaf::primitive_attributes::
primitive_attributes(const primitive_attributes& x)
{
  (*this) = x;
}

///
sheaf::primitive_attributes::
primitive_attributes(primitive_type xid)
{
  // Preconditions:

  require(is_primitive_index(xid));

  // Body:

  (*this) = prototype(xid);

  // Postconditions:

  ensure(id() == xid);

  // Exit:

  return;
}

///
sheaf::primitive_attributes::
primitive_attributes(const void* x)
{
  // Preconditions:

  // Body;

  _id = primitive_traits<void*>::id();
  _size = primitive_traits<void*>::size();
  _alignment = primitive_traits<void*>::alignment();
  _name = &primitive_traits<void*>::name();
  _aliases = &primitive_traits<void*>::aliases();
  _hdf_type_name = &primitive_traits<void*>::hdf_type_name();
  _hdf_type = primitive_traits<void*>::hdf_type();

  // Postconditions:

  ensure(id() == primitive_traits<void*>::id());

  // Exit:

  return;
}

///
sheaf::primitive_attributes::
primitive_attributes(const char* x)
{
  // Preconditions:

  // Body:

  _id = primitive_traits<char*>::id();
  _size = primitive_traits<char*>::size();
  _alignment = primitive_traits<char*>::alignment();
  _name = &primitive_traits<char*>::name();
  _aliases = &primitive_traits<char*>::aliases();
  _hdf_type_name = &primitive_traits<char*>::hdf_type_name();
  _hdf_type = primitive_traits<char*>::hdf_type();

  // Postconditions:

  ensure(id() == primitive_traits<char*>::id());

  // Exit:

  return;
}

///
template <typename T>
sheaf::primitive_attributes::
primitive_attributes(const T& x)
{
  // Preconditions:

  // Body:

  _id = primitive_traits<T>::id();
  _size = primitive_traits<T>::size();
  _alignment = primitive_traits<T>::alignment();
  _name = &primitive_traits<T>::name();
  _aliases = &primitive_traits<T>::aliases();
  _hdf_type_name = &primitive_traits<T>::hdf_type_name();
  _hdf_type = primitive_traits<T>::hdf_type();

  // Postconditions:

  ensure(id() == primitive_traits<T>::id());

  // Exit:

  return;
}

// Template specializations
namespace sheaf
{
  
///
template <>
sheaf::primitive_attributes::
primitive_attributes(const string& x)
{
  // Preconditions:

  // Body:

  (*this) = prototype(C_STRING);

  // Postconditions:

  ensure(id() == primitive_traits<char *>::id());

  // Exit:

  return;
}

///
template <>
sheaf::primitive_attributes::
primitive_attributes(const scoped_index& x)
{
  // Preconditions:

  // Body:

  (*this) = prototype(POD_INDEX_TYPE);

  // Postconditions:

  ensure(id() == primitive_traits<pod_index_type>::id());

  // Exit:

  return;
}

///
template <>
sheaf::primitive_attributes::
primitive_attributes(const namespace_relative_member_index& x)
{
  // Preconditions:

  // Body:

  (*this) = prototype(NAMESPACE_RELATIVE_MEMBER_INDEX);

  // Postconditions:

  ensure(id() == primitive_traits<namespace_relative_member_index_pod_type>::id());

  // Exit:

  return;
}

///
template <>
sheaf::primitive_attributes::
primitive_attributes(const namespace_relative_subposet_index& x)
{
  // Preconditions:

  // Body:

  (*this) = prototype(NAMESPACE_RELATIVE_SUBPOSET_INDEX);

  // Postconditions:

  ensure(id() == primitive_traits<namespace_relative_subposet_index_pod_type>::id());

  // Exit:

  return;
}
} // namespace sheaf

// Explicit instantiations.

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template sheaf::primitive_attributes::primitive_attributes(const bool& x);
template sheaf::primitive_attributes::primitive_attributes(const char& x);

template sheaf::primitive_attributes::primitive_attributes(const signed char& x);
template sheaf::primitive_attributes::primitive_attributes(const short int& x);
template sheaf::primitive_attributes::primitive_attributes(const int& x);
template sheaf::primitive_attributes::primitive_attributes(const long int& x);
template sheaf::primitive_attributes::primitive_attributes(const long long int& x);

template sheaf::primitive_attributes::primitive_attributes(const unsigned char& x);
template sheaf::primitive_attributes::primitive_attributes(const unsigned short int& x);
template sheaf::primitive_attributes::primitive_attributes(const unsigned int& x);
template sheaf::primitive_attributes::primitive_attributes(const unsigned long int& x);
template sheaf::primitive_attributes::primitive_attributes(const unsigned long long int& x);

template sheaf::primitive_attributes::primitive_attributes(const float& x);
template sheaf::primitive_attributes::primitive_attributes(const double& x);
template sheaf::primitive_attributes::primitive_attributes(const long double& x);

template sheaf::primitive_attributes::primitive_attributes(void* const& x);
template sheaf::primitive_attributes::primitive_attributes(char* const& x);
#endif // ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// $$SCRIBBLE doxygen - Warning: no matching class member found for
template
sheaf::primitive_attributes::primitive_attributes(const sheaf::namespace_relative_member_index_pod_type& x);

template
sheaf::primitive_attributes::primitive_attributes(const sheaf::namespace_relative_subposet_index_pod_type& x);
#endif // DOXYGEN_SHOULD_SKIP_THIS

///
sheaf::primitive_attributes&
sheaf::primitive_attributes::
operator=(const primitive_attributes& x)
{
  // Preconditions:


  // Body:

  if(&x != this)
  {
    _id            = x._id;
    _size          = x._size;
    _alignment     = x._alignment;
    _name          = x._name;
    _aliases       = x._aliases;
    _hdf_type_name = x._hdf_type_name;
    _hdf_type      = x._hdf_type;
  }

  // Postconditions:


  // Exit:

  return *this;
}


sheaf::primitive_attributes::
~primitive_attributes()
{
  // Nothing to do.
  return;
}

sheaf::primitive_attributes::
operator primitive_descriptor() const
{
  primitive_descriptor result;

  result.size = _size;
  result.alignment = _alignment;
  result.index = _id;

  return result;
}

// ===========================================================
// PRIVATE MEMBER FUNCTIONS
// ===========================================================

///
sheaf::block<sheaf::primitive_attributes>&
sheaf::primitive_attributes::
make_prototypes()
{
  static block<primitive_attributes> result(PRIMITIVE_TYPE_END+1);

  namespace_relative_member_index_pod_type x;
  namespace_relative_subposet_index_pod_type y;

  if(result.ct() == 0)
  {
    result[0]                      = primitive_attributes();
    result[1]                      = primitive_attributes();
    result[BOOL]                   = primitive_attributes(static_cast<bool>(0));
    result[CHAR]                   = primitive_attributes(static_cast<char>(0));

    result[SIGNED_CHAR]            = primitive_attributes(static_cast<signed char>(0));
    result[SHORT_INT]              = primitive_attributes(static_cast<short int>(0));
    result[INT]                    = primitive_attributes(static_cast<int>(0));
    result[LONG_INT]               = primitive_attributes(static_cast<long int>(0));
    result[LONG_LONG_INT]          = primitive_attributes(static_cast<long long int>(0));

    result[UNSIGNED_CHAR]          = primitive_attributes(static_cast<unsigned char>(0));
    result[UNSIGNED_SHORT_INT]     = primitive_attributes(static_cast<unsigned short int>(0));
    result[UNSIGNED_INT]           = primitive_attributes(static_cast<unsigned int>(0));
    result[UNSIGNED_LONG_INT]      = primitive_attributes(static_cast<unsigned long int>(0));
    result[UNSIGNED_LONG_LONG_INT] = primitive_attributes(static_cast<unsigned long long int>(0));

    result[FLOAT]                  = primitive_attributes(static_cast<float>(0));
    result[DOUBLE]                 = primitive_attributes(static_cast<double>(0));
    result[LONG_DOUBLE]            = primitive_attributes(static_cast<long double>(0));

    result[VOID_STAR]              = primitive_attributes(static_cast<void_star>(0));
    result[C_STRING]               = primitive_attributes(static_cast<c_string>(0));

    result[NAMESPACE_RELATIVE_MEMBER_INDEX] = primitive_attributes(x);

    result[NAMESPACE_RELATIVE_SUBPOSET_INDEX] = primitive_attributes(y);
    result[PRIMITIVE_TYPE_END]     = primitive_attributes();

    result.set_ct(PRIMITIVE_TYPE_END+1);
  }

  return result;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

