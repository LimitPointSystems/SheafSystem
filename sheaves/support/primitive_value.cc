// $RCSfile: primitive_value.cc,v $ $Revision: 1.25 $ $Date: 2013/01/12 17:17:46 $
//
// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
 
//
// Implementation for class primitive_value

#include "primitive_value.h"

#include "assert_contract.h"
#include "block.impl.h"
#include "poset_path.h"
#include "primitive_traits.h"
#include "std_cstring.h"
#include "std_sstream.h"

using namespace sheaf;

namespace
{

///
/// Converts x to a string for stream insertion.
///
template <typename T>
string to_string(const sheaf::primitive_buffer_type& x)
{
  stringstream lstr;
  lstr << reinterpret_cast<const T&>(x);
  return lstr.str();
};

// Specialization for void.

template <>
string to_string<void>(const sheaf::primitive_buffer_type& x)
{
  return "<undefined>";
};

///
/// Type of function to_string.
///
typedef string (*to_string_type)(const sheaf::primitive_buffer_type& x);

to_string_type to_string_function(sheaf::primitive_type xid)
{
  // Preconditions:

  //    require(is_primitive_index(xid));

  if(xid == sheaf::NOT_A_PRIMITIVE_TYPE)
  {
    xid = sheaf::PRIMITIVE_TYPE_END;
  }

  static const to_string_type lfcn_ptrs[] =
    {
      0,
      0,
      to_string<bool>,
      to_string<char>,

      to_string<signed char>,
      to_string<short int>,
      to_string<int>,
      to_string<long int>,
      to_string<long long int>,

      to_string<unsigned char>,
      to_string<unsigned short int>,
      to_string<unsigned int>,
      to_string<unsigned long int>,
      to_string<unsigned long long int>,

      to_string<float>,
      to_string<double>,
      to_string<long double>,

      to_string<void*>,
      to_string<char*>,

      to_string<sheaf::namespace_relative_member_index_pod_type>,
      to_string<sheaf::namespace_relative_subposet_index_pod_type>,
      to_string<void>
    };

  return lfcn_ptrs[xid];
};


///
/// Converts this from a string.
///
template <typename T>
bool from_string(const std::string& x, sheaf::primitive_buffer_type& b)
{
  stringstream lstr(x);
  lstr >> reinterpret_cast<T&>(b);
  return !lstr.fail();
};

// Specialization for C_STRING

template <>
bool from_string<char*>(const std::string& x, sheaf::primitive_buffer_type& b)
{
  // For c_string values, assume the entire string x is the value.

  b.c_string_primitive = strdup(x.c_str());

  return true;
};

// Specialization for void

template <>
bool from_string<void>(const std::string& x, sheaf::primitive_buffer_type& b)
{
  for(int i=0; i<sizeof(b); ++i)
  {
    reinterpret_cast<char*>(&b)[i] = 0;
  }
  return true;
};

///
/// Type of function from_string.
///
typedef bool (*from_string_type)(const string& x, sheaf::primitive_buffer_type& b);

from_string_type from_string_function(sheaf::primitive_type xid)
{
  // Preconditions:

  //    require(is_primitive_index(xid));

  if(xid == sheaf::NOT_A_PRIMITIVE_TYPE)
  {
    xid = sheaf::PRIMITIVE_TYPE_END;
  }

  static const from_string_type lfcn_ptrs[] =
    {
      0,
      0,
      from_string<bool>,
      from_string<char>,

      from_string<signed char>,
      from_string<short int>,
      from_string<int>,
      from_string<long int>,
      from_string<long long int>,

      from_string<unsigned char>,
      from_string<unsigned short int>,
      from_string<unsigned int>,
      from_string<unsigned long int>,
      from_string<unsigned long long int>,

      from_string<float>,
      from_string<double>,
      from_string<long double>,

      from_string<void*>,
      from_string<char*>,

      from_string<sheaf::namespace_relative_member_index_pod_type>,
      from_string<sheaf::namespace_relative_subposet_index_pod_type>,
      from_string<void>
    };

  return lfcn_ptrs[xid];
};

}

// ===========================================================
// STATIC FUNCTIONS
// ===========================================================

///
const sheaf::primitive_value&
sheaf::primitive_value::
prototype(pod_index_type xid)
{
  // Preconditions:

  //  require(is_primitive_index(xid));

  // Body:

  xid = is_primitive_index(xid) ? xid : PRIMITIVE_TYPE_END;

  static const block<primitive_value>& lprototypes = make_prototypes();
  primitive_value& result = lprototypes[xid];

  // Postconditions:

  //  ensure(result.id() == xid);
  ensure(static_cast<pod_index_type>(result.id()) == 
	 (is_primitive_index(xid) ? xid : static_cast<pod_index_type>(NOT_A_PRIMITIVE_TYPE)));
  ensure(unexecutable("result.value == default value for type associated with id"));

  // Exit:

  return result;
}

// ===========================================================
// CONSTRUCTORS
// ===========================================================

// ///
// primitive_value::
// primitive_value()
// {
//   _id = INT;
//   _value.int_primitive = primitive_traits<int>::default_value();
// }

///
sheaf::primitive_value::
primitive_value()
{
  _id = primitive_traits<void>::id();
  _value = primitive_traits<void>::default_value();
}

///
sheaf::primitive_value::
primitive_value(const primitive_value& x)
{
  (*this) = x;
}

///
sheaf::primitive_value::
primitive_value(primitive_type xid)
{
  // Preconditions:

  require(is_primitive_index(xid));

  // Body:

  (*this) = prototype(xid);

  // Postconditions:

  ensure(id() == xid);

  // Next postcondition is unexecutable because primitve_buffer_type::operator==
  // doesn't exist and it isn't immediately clear how to define it.
  // What we mean here is that the member of value() associated with id() is
  // equal to the corresponding member in default_value(), but we can't define
  // this in the context of primitive_buffer type alone. The only thing we can do
  // is compare all the bytes, but for most members, some of the bytes will be undefined.

  ensure(unexecutable("value() == primitive_attributes::default_value(xid)"));

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(pod_index_type xid, void* xvalue_ptr)
{
  // Preconditions:

  require(is_primitive_index(xid));
  require(xvalue_ptr != 0);

  // Body:

  (*this) = prototype(xid);
  _value = *reinterpret_cast<primitive_buffer_type*>(xvalue_ptr);

  // Postconditions:

  ensure(id() == xid);

  // Next postcondition is unexecutable because primitve_buffer_type::operator==
  // doesn't exist and it isn't immediately clear how to define it.

  ensure(unexecutable("value() == *reinterpret_cast<primitive_buffer_type*>(xvalue_ptr)"));

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const void* x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<void*>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const char* x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<char*>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

// Template specializations

///
sheaf::primitive_value::
primitive_value(const string& x)
{

  // Id:

  (*this) = x.c_str();

  // Postconditions:

  ensure(id() == primitive_traits<char *>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const scoped_index& x)
{

  // Id:

  (*this) = x.pod();

  // Postconditions:

  ensure(id() == primitive_traits<pod_index_type>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const namespace_relative_member_index& x)
{

  // Id:

  (*this) = x.pod();

  // Postconditions:

  ensure(id() == primitive_traits<namespace_relative_member_index_pod_type>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const namespace_relative_subposet_index& x)
{

  // Id:

  (*this) = x.pod();

  // Postconditions:

  ensure(id() == primitive_traits<namespace_relative_subposet_index_pod_type>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const bool& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<bool>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const char& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<char>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const signed char& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<signed char>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const short int& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<short int>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const int& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<int>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const long int& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<long int>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const long long int& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<long long int>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const unsigned char& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<unsigned char>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const unsigned short int& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<unsigned short int>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const unsigned int& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<unsigned int>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const unsigned long int& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<unsigned long int>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const unsigned long long int& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<unsigned long long int>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const float& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<float>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const double& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<double>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const long double& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<long double>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const namespace_relative_member_index_pod_type& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<namespace_relative_member_index_pod_type>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

///
sheaf::primitive_value::
primitive_value(const namespace_relative_subposet_index_pod_type& x)
{

  // Id:

  (*this) = x;

  // Postconditions:

  ensure(id() == primitive_traits<namespace_relative_subposet_index_pod_type>::id());
  //ensure((*this) == x);

  // Exit:

  return;
}

// ===========================================================
// ASSIGNMENT OPERATORS
// ===========================================================

///
sheaf::primitive_value&
sheaf::primitive_value::
operator=(const primitive_value& x)
{
  _id = x._id;
  _value = x._value;

  return *this;
}


///
sheaf::primitive_value&
sheaf::primitive_value::
operator=(void* x)
{
  _id = primitive_traits<void*>::id();
  _value.void_star_primitive = const_cast<void*>(x);
  return *this;
}

///
sheaf::primitive_value&
sheaf::primitive_value::
operator=(const void* x)
{
  _id = primitive_traits<void*>::id();
  _value.void_star_primitive = const_cast<void*>(x);
  return *this;
}

///
sheaf::primitive_value&
sheaf::primitive_value::
operator=(char* x)
{
  _id = primitive_traits<char*>::id();
  _value.c_string_primitive = strdup(x);
  return *this;
}

///
sheaf::primitive_value&
sheaf::primitive_value::
operator=(const char* x)
{
  _id = primitive_traits<char*>::id();
  _value.c_string_primitive = strdup(x);
  return *this;
}


template <typename T>
sheaf::primitive_value&
sheaf::primitive_value::
operator=(const T& x)
{
  _id = primitive_traits<T>::id();
  *reinterpret_cast<T*>(&_value) = x;
  return *this;
};

// Specialization for string.

namespace sheaf
{


// template <>
// SHEAF_DLL_SPEC
// sheaf::primitive_value&
// sheaf::primitive_value::
// operator=(const char* x)
// {
//   _id = primitive_traits<char*>::id();
//   _value.c_string_primitive = strdup(x);
//   return *this;
// }
  
template <>
SHEAF_DLL_SPEC
sheaf::primitive_value& 
sheaf::primitive_value::
operator=(const string& x)
{
  _id = primitive_traits<c_string>::id();
  string s(x);
  _value.c_string_primitive = strdup(s.c_str());
  return *this;
}

// Specialization for scoped_index.

template <>
SHEAF_DLL_SPEC
sheaf::primitive_value& 
sheaf::primitive_value::
operator=(const scoped_index& x)
{
  (*this) = x.pod();
  return *this;
}

// Specialization for namespace_relative_member_index.

template <>
SHEAF_DLL_SPEC
sheaf::primitive_value& 
sheaf::primitive_value::
operator=(const namespace_relative_member_index& x)
{
  (*this) = x.pod();
  return *this;
}

// Specialization for namespace_relative_subposet_index.

template <>
SHEAF_DLL_SPEC
sheaf::primitive_value& 
sheaf::primitive_value::
operator=(const namespace_relative_subposet_index& x)
{
  (*this) = x.pod();
  return *this;
}

// Specialization for poset_path.

template <>
SHEAF_DLL_SPEC
sheaf::primitive_value& 
sheaf::primitive_value::
operator=(const poset_path& x)
{
  _id = primitive_traits<c_string>::id();
  _value.c_string_primitive = strdup(x.path().c_str());
  return *this;
}

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

// Explict instantiations for assignment from primitive.

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const bool& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const char& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const signed char& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const short int& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const int& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const long int& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const long long int& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const unsigned char& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const unsigned short int& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const unsigned int& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const unsigned long int& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const unsigned long long int& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const float& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const double& x);

template 
SHEAF_DLL_SPEC 
sheaf::primitive_value& sheaf::primitive_value::operator=(const long double& x);

#endif // DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template
SHEAF_DLL_SPEC 
sheaf::primitive_value&
sheaf::primitive_value::operator=<sheaf::namespace_relative_member_index_pod_type>(const sheaf::namespace_relative_member_index_pod_type& x);

template
SHEAF_DLL_SPEC 
sheaf::primitive_value&
sheaf::primitive_value::operator=<sheaf::namespace_relative_subposet_index_pod_type>(const sheaf::namespace_relative_subposet_index_pod_type& x);

} // namespace sheaf

// ===========================================================
// CONVERSION TO PRIMITIVE
// ===========================================================

sheaf::primitive_value::
operator bool() const
{
  return _value.bool_primitive;
}

sheaf::primitive_value::
operator char() const
{
  return _value.char_primitive;
}

sheaf::primitive_value::
operator signed char() const
{
  return _value.signed_char_primitive;
}

sheaf::primitive_value::
operator short int() const
{
  return _value.short_int_primitive;
}

sheaf::primitive_value::
operator int() const
{
  return _value.int_primitive;
}

sheaf::primitive_value::
operator long int() const
{
  return _value.long_int_primitive;
}

sheaf::primitive_value::
operator long long int() const
{
  return _value.long_long_int_primitive;
}

sheaf::primitive_value::
operator unsigned char() const
{
  return _value.unsigned_char_primitive;
}

sheaf::primitive_value::
operator unsigned short int() const
{
  return _value.unsigned_short_int_primitive;
}

sheaf::primitive_value::
operator unsigned int() const
{
  return _value.unsigned_int_primitive;
}

sheaf::primitive_value::
operator unsigned long int() const
{
  return _value.unsigned_long_int_primitive;
}

sheaf::primitive_value::
operator unsigned long long int() const
{
  return _value.unsigned_long_long_int_primitive;
}

sheaf::primitive_value::
operator float() const
{
  return _value.float_primitive;
}

sheaf::primitive_value::
operator double() const
{
  return _value.double_primitive;
}

sheaf::primitive_value::
operator long double() const
{
  return _value.long_double_primitive;
}

sheaf::primitive_value::
operator void*() const
{
  return _value.void_star_primitive;
}

sheaf::primitive_value::
operator char*() const
{
  return _value.c_string_primitive;
}

sheaf::primitive_value::
operator namespace_relative_member_index_pod_type() const
{
  return _value.namespace_relative_member_index_primitive;
}

sheaf::primitive_value::
operator namespace_relative_subposet_index_pod_type() const
{
  return _value.namespace_relative_subposet_index_primitive;
}

// ===========================================================
// DESTRUCTOR FACET
// ===========================================================

sheaf::primitive_value::
~primitive_value()
{
  // Nothing to do.
  return;
}

// ===========================================================
// SUPPORT FOR STREAMS FACET
// ===========================================================

///
std::string
sheaf::primitive_value::
to_string() const
{
  return (*to_string_function(_id))(_value);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS

///
bool
sheaf::primitive_value::
from_string(const string& x)
{
  return (*from_string_function(_id))(x, _value);
}

#endif // ifndef DOXYGEN_SHOULD_SKIP_THIS



// ===========================================================
// PRIVATE MEMBER FUNCTIONS
// ===========================================================

///
sheaf::block<sheaf::primitive_value>&
sheaf::primitive_value::
make_prototypes()
{

  static block<primitive_value> result(PRIMITIVE_TYPE_END+1);

  // Preconditions:

  if(result.ct() == 0)
  {
    result[0]                      = primitive_value();
    result[1]                      = primitive_value();
    result[BOOL]                   = primitive_traits<bool>::default_value();
    result[CHAR]                   = primitive_traits<char>::default_value();

    result[SIGNED_CHAR]            = primitive_traits<signed char>::default_value();
    result[SHORT_INT]              = primitive_traits<short int>::default_value();
    result[INT]                    = primitive_traits<int>::default_value();
    result[LONG_INT]               = primitive_traits<long int>::default_value();
    result[LONG_LONG_INT]          = primitive_traits<long long int>::default_value();

    result[UNSIGNED_CHAR]          = primitive_traits<unsigned char>::default_value();
    result[UNSIGNED_SHORT_INT]     = primitive_traits<unsigned short int>::default_value();
    result[UNSIGNED_INT]           = primitive_traits<unsigned int>::default_value();
    result[UNSIGNED_LONG_INT]      = primitive_traits<unsigned long int>::default_value();
    result[UNSIGNED_LONG_LONG_INT] = primitive_traits<unsigned long long int>::default_value();

    result[FLOAT]                  = primitive_traits<float>::default_value();
    result[DOUBLE]                 = primitive_traits<double>::default_value();
    result[LONG_DOUBLE]            = primitive_traits<long double>::default_value();

    result[VOID_STAR]              = primitive_traits<void_star>::default_value();
    result[C_STRING]               = primitive_traits<c_string>::default_value();

    result[NAMESPACE_RELATIVE_MEMBER_INDEX] =
      primitive_traits<namespace_relative_member_index_pod_type>::default_value();

    result[NAMESPACE_RELATIVE_SUBPOSET_INDEX] =
      primitive_traits<namespace_relative_subposet_index_pod_type>::default_value();

    result[PRIMITIVE_TYPE_END]     = primitive_value();

    result.set_ct(PRIMITIVE_TYPE_END+1);
  }

  return result;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

bool
sheaf::
operator==(const primitive_value& xpv1, const primitive_value& xpv2)
{
  bool result;
  
  // Preconditions:

  // Body:

  result = (xpv1._id == xpv2._id);

  if(result)
  {
    switch(xpv1._id)
    {
      case BOOL:
	result = result && xpv1._value.bool_primitive == xpv2._value.bool_primitive;
	break;
      case CHAR:
	result = result && xpv1._value.char_primitive == xpv2._value.char_primitive;
	break;
      case SIGNED_CHAR:
	result = result && xpv1._value.signed_char_primitive == xpv2._value.signed_char_primitive;
	break;
      case SHORT_INT:
	result = result && xpv1._value.short_int_primitive == xpv2._value.short_int_primitive;
	break;
      case INT:
	result = result && xpv1._value.int_primitive == xpv2._value.int_primitive;
	break;
      case LONG_INT:
	result = result && xpv1._value.long_int_primitive == xpv2._value.long_int_primitive;
	break;
      case LONG_LONG_INT:
	result = result && xpv1._value.long_long_int_primitive == xpv2._value.long_long_int_primitive;
	break;
      case UNSIGNED_CHAR:
	result = result && xpv1._value.unsigned_char_primitive == xpv2._value.unsigned_char_primitive;
	break;
      case UNSIGNED_SHORT_INT:
	result = result && xpv1._value.unsigned_short_int_primitive == xpv2._value.unsigned_short_int_primitive;
	break;
      case UNSIGNED_INT:
	result = result && xpv1._value.unsigned_int_primitive == xpv2._value.unsigned_int_primitive;
	break;
      case UNSIGNED_LONG_INT:
	result = result && xpv1._value.unsigned_long_int_primitive == xpv2._value.unsigned_long_int_primitive;
	break;
      case UNSIGNED_LONG_LONG_INT:
	result = result && xpv1._value.unsigned_long_long_int_primitive == xpv2._value.unsigned_long_long_int_primitive;
	break;
      case FLOAT:
	result = result && xpv1._value.float_primitive == xpv2._value.float_primitive;
	break;
      case DOUBLE:
	result = result && xpv1._value.double_primitive == xpv2._value.double_primitive;
	break;
      case LONG_DOUBLE:
	result = result && xpv1._value.long_double_primitive == xpv2._value.long_double_primitive;
	break;
      case VOID_STAR:
	result = result && xpv1._value.void_star_primitive == xpv2._value.void_star_primitive;
	break;
      case C_STRING:
	result = result && xpv1._value.c_string_primitive == xpv2._value.c_string_primitive;
	break;
      case NAMESPACE_RELATIVE_MEMBER_INDEX:
	result = result && xpv1._value.namespace_relative_member_index_primitive == xpv2._value.namespace_relative_member_index_primitive;
	break;
      case NAMESPACE_RELATIVE_SUBPOSET_INDEX:
	result = result && xpv1._value.namespace_relative_subposet_index_primitive == xpv2._value.namespace_relative_subposet_index_primitive;
	break;
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::
operator==(const primitive_value& xpv, const void* xval)
{
  return (void*)(xpv) == xval;
}

bool
sheaf::
operator==(const void* xval, const primitive_value& xpv)
{
  return xval == (void*)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const char* xval)
{
  return strcmp(xpv.value().c_string_primitive, xval) == 0;
}

bool
sheaf::
operator==(const char* xval, const primitive_value& xpv)
{
  return strcmp(xval, xpv.value().c_string_primitive) == 0;
}

bool
sheaf::
operator==(const primitive_value& xpv, const string& xval)
{
  return xpv.value().c_string_primitive == xval;
}

bool
sheaf::
operator==(const string& xval, const primitive_value& xpv)
{
  return xval == xpv.value().c_string_primitive;
}

bool
sheaf::
operator==(const primitive_value& xpv, const scoped_index& xval)
{
  return (scoped_index&)(xpv) == xval;
}

bool
sheaf::
operator==(const scoped_index& xval, const primitive_value& xpv)
{
  return xval == (scoped_index&)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const namespace_relative_member_index& xval)
{
  return (namespace_relative_member_index&)(xpv) == xval;
}

bool
sheaf::
operator==(const namespace_relative_member_index& xval, const primitive_value& xpv)
{
  return xval == (namespace_relative_member_index&)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const namespace_relative_subposet_index& xval)
{
  return (namespace_relative_subposet_index&)(xpv) == xval;
}

bool
sheaf::
operator==(const namespace_relative_subposet_index& xval, const primitive_value& xpv)
{
  return xval == (namespace_relative_subposet_index&)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const bool& xval)
{
  return (bool)(xpv) == xval;
}

bool
sheaf::
operator==(const bool& xval, const primitive_value& xpv)
{
  return xval == (bool)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const char& xval)
{
  return (char)(xpv) == xval;
}

bool
sheaf::
operator==(const char& xval, const primitive_value& xpv)
{
  return xval == (char)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const signed char& xval)
{
  return (signed char)(xpv) == xval;
}

bool
sheaf::
operator==(const signed char& xval, const primitive_value& xpv)
{
  return xval == (signed char)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const short int& xval)
{
  return (short int)(xpv) == xval;
}

bool
sheaf::
operator==(const short int& xval, const primitive_value& xpv)
{
  return xval == (short int)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const int& xval)
{
  return (int)(xpv) == xval;
}

bool
sheaf::
operator==(const int& xval, const primitive_value& xpv)
{
  return xval == (int)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const long int& xval)
{
  return (long int)(xpv) == xval;
}

bool
sheaf::
operator==(const long int& xval, const primitive_value& xpv)
{
  return xval == (long int)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const long long int& xval)
{
  return (long long int)(xpv) == xval;
}

bool
sheaf::
operator==(const long long int& xval, const primitive_value& xpv)
{
  return xval == (long long int)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const unsigned char& xval)
{
  return (unsigned char)(xpv) == xval;
}

bool
sheaf::
operator==(const unsigned char& xval, const primitive_value& xpv)
{
  return xval == (unsigned char)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const unsigned short int& xval)
{
  return (unsigned short int)(xpv) == xval;
}

bool
sheaf::
operator==(const unsigned short int& xval, const primitive_value& xpv)
{
  return xval == (unsigned short int)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const unsigned int& xval)
{
  return (unsigned int)(xpv) == xval;
}

bool
sheaf::
operator==(const unsigned int& xval, const primitive_value& xpv)
{
  return xval == (unsigned int)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const unsigned long int& xval)
{
  return (unsigned long int)(xpv) == xval;
}

bool
sheaf::
operator==(const unsigned long int& xval, const primitive_value& xpv)
{
  return xval == (unsigned long int)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const unsigned long long& xval)
{
  return (unsigned long long)(xpv) == xval;
}

bool
sheaf::
operator==(const unsigned long long& xval, const primitive_value& xpv)
{
  return xval == (unsigned long long)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const float& xval)
{
  return (float)(xpv) == xval;
}

bool
sheaf::
operator==(const float& xval, const primitive_value& xpv)
{
  return xval == (float)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const double& xval)
{
  return (double)(xpv) == xval;
}

bool
sheaf::
operator==(const double& xval, const primitive_value& xpv)
{
  return xval == (double)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const long double& xval)
{
  return (long double)(xpv) == xval;
}

bool
sheaf::
operator==(const long double& xval, const primitive_value& xpv)
{
  return xval == (long double)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const namespace_relative_member_index_pod_type& xval)
{
  return (namespace_relative_member_index_pod_type)(xpv) == xval;
}

bool
sheaf::
operator==(const namespace_relative_member_index_pod_type& xval, const primitive_value& xpv)
{
  return xval == (namespace_relative_member_index_pod_type)(xpv);
}

bool
sheaf::
operator==(const primitive_value& xpv, const namespace_relative_subposet_index_pod_type& xval)
{
  return (namespace_relative_subposet_index_pod_type)(xpv) == xval;
}

bool
sheaf::
operator==(const namespace_relative_subposet_index_pod_type& xval, const primitive_value& xpv)
{
  return xval == (namespace_relative_subposet_index_pod_type)(xpv);
}


ostream&
sheaf::
operator << (ostream& xos, const primitive_value& xpv)
{
  xos << xpv.to_string();
  return xos;
}


size_t
sheaf::
deep_size(const primitive_value& xpv, bool xinclude_shallow)
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
