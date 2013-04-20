
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Instantiations for class deep_size templated functions.

#include "deep_size.impl.h"

#include "crg_interval.h"
#include "scoped_index.h"

using namespace sheaf; // workaround for MS C++ bug.

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

// =============================================================================
// EXPLICIT INSTANTIATIONS FOR DEEP_SIZE FACET
// =============================================================================

// hash_multimap

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<hash_multimap<sheaf::pod_index_type, sheaf::pod_index_type> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, sheaf::pod_index_type, sheaf::no_deep_size_policy<hash_multimap<sheaf::pod_index_type, sheaf::pod_index_type> > >(const hash_multimap<sheaf::pod_index_type, sheaf::pod_index_type>& xp, bool xinclude_shallow);

// hash_map

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<hash_map<sheaf::pod_index_type, sheaf::scoped_index> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, sheaf::scoped_index, sheaf::no_deep_size_policy<hash_map<sheaf::pod_index_type, sheaf::scoped_index> > >(const hash_map<sheaf::pod_index_type, sheaf::scoped_index>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<hash_map<const char*, sheaf::pod_index_type, hash_cstr, key_test> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<const char*, sheaf::pod_index_type, sheaf::no_deep_size_policy<hash_map<const char*, sheaf::pod_index_type, hash_cstr, key_test> >, hash_cstr, key_test>(const hash_map<const char*, sheaf::pod_index_type, hash_cstr, key_test>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::value_ptr_deep_size_policy<hash_map<sheaf::pod_index_type, string*> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, string*, sheaf::value_ptr_deep_size_policy<hash_map<sheaf::pod_index_type, string*> > >(const hash_map<sheaf::pod_index_type, string*>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<hash_map<sheaf::pod_index_type, sheaf::pod_index_type> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, sheaf::pod_index_type, sheaf::no_deep_size_policy<hash_map<sheaf::pod_index_type, sheaf::pod_index_type> > >(const hash_map<sheaf::pod_index_type, sheaf::pod_index_type>& xp, bool xinclude_shallow);

// map

template class 
SHEAF_DLL_SPEC 
sheaf::key_deep_size_policy<map<string, sheaf::pod_index_type> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<string, sheaf::pod_index_type, sheaf::key_deep_size_policy<map<string, sheaf::pod_index_type> > >(const map<string, sheaf::pod_index_type>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::key_deep_size_policy<map<string, sheaf::scoped_index> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<string, sheaf::scoped_index, sheaf::key_deep_size_policy<map<string, sheaf::scoped_index> > >(const map<string, sheaf::scoped_index>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::value_deep_size_policy<map<sheaf::pod_index_type, list<string> > >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, list<string>, sheaf::value_deep_size_policy<map<sheaf::pod_index_type, list<string> > > >(const map<sheaf::pod_index_type, list<string> >& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::value_deep_size_policy<map<sheaf::scoped_index, list<string> > >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::scoped_index, list<string>, sheaf::value_deep_size_policy<map<sheaf::scoped_index, list<string> > > >(const map<sheaf::scoped_index, list<string> >& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<map<sheaf::pod_index_type, sheaf::pod_index_type> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, sheaf::pod_index_type, sheaf::no_deep_size_policy<map<sheaf::pod_index_type, sheaf::pod_index_type> > >(const map<sheaf::pod_index_type, sheaf::pod_index_type>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<map<sheaf::pod_index_type, bool> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, bool, sheaf::no_deep_size_policy<map<sheaf::pod_index_type, bool> > >(const map<sheaf::pod_index_type, bool>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::value_ptr_deep_size_policy<map<sheaf::pod_index_type, sheaf::crg_interval*> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, sheaf::crg_interval*, sheaf::value_ptr_deep_size_policy<map<sheaf::pod_index_type, sheaf::crg_interval*> > >(const map<sheaf::pod_index_type, sheaf::crg_interval*>& xp, bool xinclude_shallow);

// list

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type>(const list<sheaf::pod_index_type>& xp, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::scoped_index>(const list<sheaf::scoped_index>& xp, bool xinclude_shallow);

// primitives


template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<bool>(const bool& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<char>(const char& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<signed char>(const signed char& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<short int>(const short int& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<int>(const int& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long int>(const long int& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long long int>(const long long int& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned char>(const unsigned char& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned short int>(const unsigned short int& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned int>(const unsigned int& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long int>(const unsigned long int& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long long int>(const unsigned long long int& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<float>(const float& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<double>(const double& xvalue, bool xinclude_shallow);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<double*>(const double*& xvalue, bool xinclude_shallow);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long double>(const long double& xvalue, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS