
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

// Instantiations for class deep_size templated functions.

#include "ComLimitPoint/sheaf/deep_size.impl.h"

#include "ComLimitPoint/sheaf/crg_interval.h"
#include "ComLimitPoint/sheaf/scoped_index.h"

using namespace std;
using namespace unordered;
using namespace sheaf; // workaround for MS C++ bug.

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

// =============================================================================
// EXPLICIT INSTANTIATIONS FOR DEEP_SIZE FACET
// =============================================================================

// unordered_multimap

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<unordered_multimap<sheaf::pod_index_type, sheaf::pod_index_type> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, sheaf::pod_index_type, sheaf::no_deep_size_policy<unordered_multimap<sheaf::pod_index_type, sheaf::pod_index_type> > >(const unordered_multimap<sheaf::pod_index_type, sheaf::pod_index_type>& xp, bool xinclude_shallow);

// unordered_map

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<unordered_map<sheaf::pod_index_type, sheaf::scoped_index> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, sheaf::scoped_index, sheaf::no_deep_size_policy<unordered_map<sheaf::pod_index_type, sheaf::scoped_index> > >(const unordered_map<sheaf::pod_index_type, sheaf::scoped_index>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<unordered_map<const char*, sheaf::pod_index_type, hash_cstr, key_test> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<const char*, sheaf::pod_index_type, sheaf::no_deep_size_policy<unordered_map<const char*, sheaf::pod_index_type, hash_cstr, key_test> >, hash_cstr, key_test>(const unordered_map<const char*, sheaf::pod_index_type, hash_cstr, key_test>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::value_ptr_deep_size_policy<unordered_map<sheaf::pod_index_type, string*> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, string*, sheaf::value_ptr_deep_size_policy<unordered_map<sheaf::pod_index_type, string*> > >(const unordered_map<sheaf::pod_index_type, string*>& xp, bool xinclude_shallow);

template class 
SHEAF_DLL_SPEC 
sheaf::no_deep_size_policy<unordered_map<sheaf::pod_index_type, sheaf::pod_index_type> >;

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::pod_index_type, sheaf::pod_index_type, sheaf::no_deep_size_policy<unordered_map<sheaf::pod_index_type, sheaf::pod_index_type> > >(const unordered_map<sheaf::pod_index_type, sheaf::pod_index_type>& xp, bool xinclude_shallow);

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
