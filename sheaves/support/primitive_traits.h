

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class xxx

#ifndef PRIMITIVE_TRAITS_H
#define PRIMITIVE_TRAITS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef PRIMITIVE_TYPE_H
#include "primitive_type.h"
#endif

namespace sheaf
{
  
///
/// Traits for primitive type T.
///
template <typename T>
struct SHEAF_DLL_SPEC primitive_traits
{

  ///
  /// The primitive T.
  ///
  typedef T type;

  ///
  /// The primitive type id for T.
  ///
  static primitive_type id();

  ///
  /// The size of T in bytes.
  ///
  static size_type size();

  ///
  /// The alignment for T in bytes.
  ///
  static size_type alignment();

  ///
  /// The name of T.
  ///
  static string name();

  ///
  /// Other names for T.
  ///
  static string aliases();

  ///
  /// The name of T in the hdf file.
  ///
  static string hdf_type_name();

  ///
  /// The hdf type used to represent T in the hdf file.
  ///
  static int hdf_type();

  ///
  /// The default value for instances of type T.
  ///
  static T default_value();

};

// Template specializations.
// All functions defined inline, except hdf_type which is
// defined in primitive_traits.cc to encapsulate hdf.


template<>
struct SHEAF_DLL_SPEC primitive_traits<bool>
{
  typedef bool type;
  static primitive_type id()
  {
    return BOOL;
  };
  static size_type size()
  {
    return sizeof(bool);
  };


  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      bool prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("BOOL");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_BOOL");
    return result;
  };
  static int hdf_type();
  static bool default_value()
  {
    return false;
  };

};

template<>
struct SHEAF_DLL_SPEC primitive_traits<char>
{
  typedef char type;
  static primitive_type id()
  {
    return CHAR;
  };
  static size_type size()
  {
    return sizeof(char);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      char prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("CHAR");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_CHAR");
    return result;
  };
  static int hdf_type();
  static char default_value()
  {
    return '\0';
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<signed char>
{
  typedef signed char type;
  static primitive_type id()
  {
    return SIGNED_CHAR;
  };
  static size_type size()
  {
    return sizeof(signed char);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      signed char prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("SIGNED_CHAR");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_SIGNED_CHAR");
    return result;
  };
  static int hdf_type();
  static signed char default_value()
  {
    return '\0';
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<short int>
{
  typedef short int type;
  static primitive_type id()
  {
    return SHORT_INT;
  };
  static size_type size()
  {
    return sizeof(short int);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      short int prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("SHORT_INT");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_SHORT_INT");
    return result;
  };
  static int hdf_type();
  static short int default_value()
  {
    return 0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<int>
{
  typedef int type;
  static primitive_type id()
  {
    return INT;
  };
  static size_type size()
  {
    return sizeof(int);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      int prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("INT");
    return result;
  };
  static const string& aliases()
  {
    static const string result("INT_TYPE POD_INDEX_TYPE");
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_INT");
    return result;
  };
  static int hdf_type();
  static int default_value()
  {
    return 0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<long int>
{
  typedef long int type;
  static primitive_type id()
  {
    return LONG_INT;
  };
  static size_type size()
  {
    return sizeof(long int);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      long int prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("LONG_INT");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_LONG_INT");
    return result;
  };
  static int hdf_type();
  static long int default_value()
  {
    return 0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<long long int>
{
  typedef long long int type;
  static primitive_type id()
  {
    return LONG_LONG_INT;
  };
  static size_type size()
  {
    return sizeof(long long int);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      long long int prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("LONG_LONG_INT");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_LONG_LONG_INT");
    return result;
  };
  static int hdf_type();
  static long long int default_value()
  {
    return 0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<unsigned char>
{
  typedef unsigned char type;
  static primitive_type id()
  {
    return UNSIGNED_CHAR;
  };
  static size_type size()
  {
    return sizeof(unsigned char);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      unsigned char prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("UNSIGNED_CHAR");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_UNSIGNED_CHAR");
    return result;
  };
  static int hdf_type();
  static unsigned char default_value()
  {
    return '\0';
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<unsigned short int>
{
  typedef short int type;
  static primitive_type id()
  {
    return UNSIGNED_SHORT_INT;
  };
  static size_type size()
  {
    return sizeof(unsigned short int);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      unsigned short int prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("UNSIGNED_SHORT_INT");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_UNSIGNED_SHORT_INT");
    return result;
  };
  static int hdf_type();
  static unsigned short int default_value()
  {
    return 0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<unsigned int>
{
  typedef int type;
  static primitive_type id()
  {
    return UNSIGNED_INT;
  };
  static size_type size()
  {
    return sizeof(unsigned int);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      unsigned int prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("UNSIGNED_INT");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_UNSIGNED_INT");
    return result;
  };
  static int hdf_type();
  static unsigned int default_value()
  {
    return 0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<unsigned long int>
{
  typedef long int type;
  static primitive_type id()
  {
    return UNSIGNED_LONG_INT;
  };
  static size_type size()
  {
    return sizeof(unsigned long int);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      unsigned long int prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("UNSIGNED_LONG_INT");
    return result;
  };
  static const string& aliases()
  {
    static const string result("SIZE_TYPE");
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_UNSIGNED_LONG_INT");
    return result;
  };
  static int hdf_type();
  static unsigned long int default_value()
  {
    return 0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<unsigned long long int>
{
  typedef long long int type;
  static primitive_type id()
  {
    return UNSIGNED_LONG_LONG_INT;
  };
  static size_type size()
  {
    return sizeof(unsigned long long int);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      unsigned long long int prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("UNSIGNED_LONG_LONG_INT");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_UNSIGNED_LONG_LONG_INT");
    return result;
  };
  static int hdf_type();
  static unsigned long long int default_value()
  {
    return 0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<float>
{
  typedef float type;
  static primitive_type id()
  {
    return FLOAT;
  };
  static size_type size()
  {
    return sizeof(float);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      float prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("FLOAT");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_FLOAT");
    return result;
  };
  static int hdf_type();
  static float default_value()
  {
    return 0.0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<double>
{
  typedef double type;
  static primitive_type id()
  {
    return DOUBLE;
  };
  static size_type size()
  {
    return sizeof(double);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      double prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("DOUBLE");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_DOUBLE");
    return result;
  };
  static int hdf_type();
  static double default_value()
  {
    return 0.0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<long double>
{
  typedef long double type;
  static primitive_type id()
  {
    return LONG_DOUBLE;
  };
  static size_type size()
  {
    return sizeof(long double);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      long double prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("LONG_DOUBLE");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_LONG_DOUBLE");
    return result;
  };
  static int hdf_type();
  static long double default_value()
  {
    return 0.0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<void_star>
{
  typedef void_star type;
  static primitive_type id()
  {
    return VOID_STAR;
  };
  static size_type size()
  {
    return sizeof(void_star);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      void_star prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("VOID_STAR");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_VOID_STAR");
    return result;
  };
  static int hdf_type();
  static void_star default_value()
  {
    return 0;
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<c_string>
{
  typedef c_string type;
  static primitive_type id()
  {
    return C_STRING;
  };
  static size_type size()
  {
    return sizeof(c_string);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      c_string prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("C_STRING");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_C_STRING");
    return result;
  };
  static int hdf_type();
  static c_string default_value()
  {
    return strdup("");
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<char const*>
{
  typedef char const*  type;
  static primitive_type id()
  {
    return C_STRING;
  };
  static size_type size()
  {
    return sizeof(c_string);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      char const* prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("C_STRING");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_C_STRING");
    return result;
  };
  static int hdf_type();
  static char const* default_value()
  {
    return strdup("");
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<namespace_relative_member_index_pod_type>
{
  typedef namespace_relative_member_index_pod_type type;
  static primitive_type id()
  {
    return NAMESPACE_RELATIVE_MEMBER_INDEX;
  };
  static size_type size()
  {
    return sizeof(namespace_relative_member_index_pod_type);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      namespace_relative_member_index_pod_type prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("NAMESPACE_RELATIVE_MEMBER_INDEX");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_NAMESPACE_RELATIVE_MEMBER_INDEX");
    return result;
  };
  static int hdf_type();
  static namespace_relative_member_index_pod_type default_value()
  {
    return invalid_namespace_relative_member_index_pod();
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<namespace_relative_subposet_index_pod_type>
{
  typedef namespace_relative_subposet_index_pod_type type;
  static primitive_type id()
  {
    return NAMESPACE_RELATIVE_SUBPOSET_INDEX;
  };
  static size_type size()
  {
    return sizeof(namespace_relative_subposet_index_pod_type);
  };
  static size_type alignment()
  {
    struct alignment_type
    {
      char pad;
      namespace_relative_subposet_index_pod_type prim;
    };
    return offsetof(alignment_type, prim);
  };
  static const string& name()
  {
    static const string result("NAMESPACE_RELATIVE_SUBPOSET_INDEX");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result("SHF_PRIMITIVE_NAMESPACE_RELATIVE_SUBPOSET_INDEX");
    return result;
  };
  static int hdf_type();
  static namespace_relative_subposet_index_pod_type default_value()
  {
    return invalid_namespace_relative_subposet_index_pod();
  };
};

template<>
struct SHEAF_DLL_SPEC primitive_traits<void>
{
  typedef void type;
  static primitive_type id()
  {
    return NOT_A_PRIMITIVE_TYPE;
  };
  static size_type size()
  {
    return 0;
  };
  static size_type alignment()
  {
    return 0;
  };
  static const string& name()
  {
    static const string result("NOT_A_PRIMITIVE_TYPE");
    return result;
  };
  static const string& aliases()
  {
    static const string result;
    return result;
  };
  static const string& hdf_type_name()
  {
    static const string result;
    return result;
  };
  static int hdf_type();
  static primitive_buffer_type default_value()
  {
    primitive_buffer_type lbuf;
    for(int i=0; i<sizeof(lbuf); ++i)
    {
      reinterpret_cast<char*>(&lbuf)[i] = 0;
    }
    return lbuf;
  };
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

} // namespace sheaf


#endif // ifndef PRIMITIVE_TRAITS_H
