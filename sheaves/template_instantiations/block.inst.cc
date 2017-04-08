
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

// Explicit instantiations for class block.

#include "block.impl.h"

#include "arg_list.h"
#include "deep_size.h"
#include "poset_path.h"
#include "poset_state_handle.h"
#include "primitive_value.h"
#include "schema_descriptor.h"
#include "subposet.h"

using namespace std;
using namespace sheaf; // workaround for MS C++ bug.

// =============================================================================
// EXPLICIT INSTANTIATIONS
// =============================================================================

// Instantiate with primitive types for general purpose use.

//==============================================================================
// block<bool>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<bool>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <bool>(const sheaf::block<bool>& xblk1, const sheaf::block<bool>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <bool>(ostream& xos, const sheaf::block<bool>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<bool>(const sheaf::block<bool>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<char>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<char>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <char>(const sheaf::block<char>& xblk1, const sheaf::block<char>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <char>(ostream& xos, const sheaf::block<char>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<char>(const sheaf::block<char>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<signed char>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<signed char>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <signed char>(const sheaf::block<signed char>& xblk1, const sheaf::block<signed char>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <signed char>(ostream& xos, const sheaf::block<signed char>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<signed char>(const sheaf::block<signed char>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// block<short int>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<short int>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <short int>(const sheaf::block<short int>& xblk1, const sheaf::block<short int>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <short int>(ostream& xos, const sheaf::block<short int>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<short int>(const sheaf::block<short int>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<int>
//==============================================================================


template class 
SHEAF_DLL_SPEC 
sheaf::block<int>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <int>(const sheaf::block<int>& xblk1, const sheaf::block<int>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <int>(ostream& xos, const sheaf::block<int>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<int>(const sheaf::block<int>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<long int>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<long int>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long int>(const sheaf::block<long int>& xblk1, const sheaf::block<long int>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long int>(ostream& xos, const sheaf::block<long int>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long int>(const sheaf::block<long int>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<long long int>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<long long int>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long long int>(const sheaf::block<long long int>& xblk1, const sheaf::block<long long int>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long long int>(ostream& xos, const sheaf::block<long long int>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long long int>(const sheaf::block<long long int>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<unsigned char>
//==============================================================================


template class 
SHEAF_DLL_SPEC 
sheaf::block<unsigned char>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned char>(const sheaf::block<unsigned char>& xblk1, const sheaf::block<unsigned char>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned char>(ostream& xos, const sheaf::block<unsigned char>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned char>(const sheaf::block<unsigned char>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<unsigned short int>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<unsigned short int>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned short int>(const sheaf::block<unsigned short int>& xblk1, const sheaf::block<unsigned short int>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned short int>(ostream& xos, const sheaf::block<unsigned short int>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned short int>(const sheaf::block<unsigned short int>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<unsigned int>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<unsigned int>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned int>(const sheaf::block<unsigned int>& xblk1, const sheaf::block<unsigned int>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned int>(ostream& xos, const sheaf::block<unsigned int>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned int>(const sheaf::block<unsigned int>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block< unsigned long int>
//==============================================================================


template class 
SHEAF_DLL_SPEC 
sheaf::block<unsigned long int>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned long int>(const sheaf::block<unsigned long int>& xblk1, const sheaf::block<unsigned long int>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned long int>(ostream& xos, const sheaf::block<unsigned long int>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long int>(const sheaf::block<unsigned long int>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<unsigned long long int>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<unsigned long long int>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned long long int>(const sheaf::block<unsigned long long int>& xblk1, const sheaf::block<unsigned long long int>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned long long int>(ostream& xos, const sheaf::block<unsigned long long int>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long long int>(const sheaf::block<unsigned long long int>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<float>
//==============================================================================


template class 
SHEAF_DLL_SPEC 
sheaf::block<float>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <float>(const sheaf::block<float>& xblk1, const sheaf::block<float>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <float>(ostream& xos, const sheaf::block<float>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<float>(const sheaf::block<float>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<double>
//==============================================================================


template class 
SHEAF_DLL_SPEC 
sheaf::block<double>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <double>(const sheaf::block<double>& xblk1, const sheaf::block<double>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <double>(ostream& xos, const sheaf::block<double>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<double>(const sheaf::block<double>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<long double>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<long double>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long double>(const sheaf::block<long double>& xblk1, const sheaf::block<long double>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long double>(ostream& xos, const sheaf::block<long double>& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<long double>(const sheaf::block<long double>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// block<int*>
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::block<int*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template
SHEAF_DLL_SPEC
bool sheaf::operator == <int*>(const sheaf::block<int*>& xblk1, const sheaf::block<int*>& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <int*>(ostream& xos, const sheaf::block<int*>& xblk);

// There are two signatures for deep_size, one for block<T> and one for block<T*>.
// To get the right template for deep_size(const block<int*>, bool), the parameter is int, not int*.

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<int>(const sheaf::block<int*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// block<double*>
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::block<double*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template
SHEAF_DLL_SPEC
bool sheaf::operator == <double*>(const sheaf::block<double*>& xblk1, const sheaf::block<double*>& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <double*>(ostream& xos, const sheaf::block<double*>& xblk);

// There are two signatures for deep_size, one for block<T> and one for block<T*>.
// To get the right template for deep_size(const block<double*>, bool), the parameter is double, not double*.

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<double>(const sheaf::block<double*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// block<arg_list::arg_type>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<sheaf::arg_list::arg_type>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::arg_list::arg_type>(const sheaf::block<sheaf::arg_list::arg_type>& xblk1, const sheaf::block<sheaf::arg_list::arg_type>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::arg_list::arg_type>(ostream& xos, const sheaf::block<sheaf::arg_list::arg_type>& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<arg_list::arg_type>(const sheaf::block<arg_list::arg_type>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// block<block<int>* >
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<sheaf::block<int>* >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::block<int>*>(const sheaf::block<sheaf::block<int>*>& xblk1, const sheaf::block<sheaf::block<int>*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<int>* >(ostream& xos, const sheaf::block<sheaf::block<int>* >& xblk);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// block<block<double> >
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<sheaf::block<double> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::block<double> >(const sheaf::block<sheaf::block<double> >& xblk1, const sheaf::block<sheaf::block<double> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<double> >(ostream& xos, const sheaf::block<sheaf::block<double> >& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<block<double> >(const sheaf::block<block<double> >& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// block<block<double>* >
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<sheaf::block<double>* >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::block<double>*>(const sheaf::block<sheaf::block<double>*>& xblk1, const sheaf::block<sheaf::block<double>*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<double>* >(ostream& xos, const sheaf::block<sheaf::block<double>* >& xblk);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// block<string>
//==============================================================================

#include "std_string.h"

template class 
SHEAF_DLL_SPEC 
sheaf::block<string>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <std::string>(const sheaf::block<std::string>& xblk1, const sheaf::block<std::string>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <std::string>(ostream& xos, const sheaf::block<std::string>& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<std::string>(const sheaf::block<std::string>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// block<std::string*>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<std::string*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <std::string*>(const sheaf::block<std::string*>& xblk1, const sheaf::block<std::string*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <std::string*>(ostream& xos, const sheaf::block<std::string*>& xblk);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// block<subposet_state*>
//==============================================================================

#include "subposet_state.h"

template class 
SHEAF_DLL_SPEC 
sheaf::block<sheaf::subposet_state*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::subposet_state*>(const sheaf::block<sheaf::subposet_state*>& xblk1, const sheaf::block<sheaf::subposet_state*>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::subposet_state*>(ostream& xos, const sheaf::block<sheaf::subposet_state*>& xblk);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::subposet_state>(const sheaf::block<sheaf::subposet_state*>& xblk, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// block<poset_dof_map*>
//==============================================================================

#include "poset_dof_map.h"

template class 
SHEAF_DLL_SPEC 
sheaf::block<sheaf::poset_dof_map*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::poset_dof_map*>(const sheaf::block<sheaf::poset_dof_map*>& xblk1, const sheaf::block<sheaf::poset_dof_map*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::poset_dof_map*>(ostream& xos, const block<sheaf::poset_dof_map*>& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::poset_dof_map>(const sheaf::block<sheaf::poset_dof_map*>& xblk, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// block<explicit_index_space_state*>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<sheaf::explicit_index_space_state*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::explicit_index_space_state*>(const sheaf::block<sheaf::explicit_index_space_state*>& xblk1, const block<sheaf::explicit_index_space_state*>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::explicit_index_space_state*>(ostream& xos, const sheaf::block<sheaf::explicit_index_space_state*>& xblk);

// $$SCRIBBLE: For some reason, the template instantiation for deep_size is causing an undefined reference.  It is looking for
// a deep size template instantiation for explicit_index_space_state eventhough there is an deep_size for explicit_index_space_state implemented.
// template 
// SHEAF_DLL_SPEC
// size_t sheaf::deep_size<sheaf::explicit_index_space_state>(const sheaf::block<sheaf::explicit_index_space_state*>& xblk, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// block<index_space_handle*>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<sheaf::index_space_handle*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::index_space_handle*>(ostream& xos, const sheaf::block<sheaf::index_space_handle*>& xblk);

template 
SHEAF_DLL_SPEC
bool sheaf::operator==<sheaf::index_space_handle*>(const sheaf::block<sheaf::index_space_handle*>& xblk1, const sheaf::block<sheaf::index_space_handle*>& xblk2);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<sheaf::index_space_handle>(const sheaf::block<sheaf::index_space_handle*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// block<scattered_insertion_index_space_handle*>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<sheaf::scattered_insertion_index_space_handle*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::scattered_insertion_index_space_handle*>(const sheaf::block<sheaf::scattered_insertion_index_space_handle*>& xblk1, const sheaf::block<sheaf::scattered_insertion_index_space_handle*>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::scattered_insertion_index_space_handle*>(ostream& xos, const sheaf::block<sheaf::scattered_insertion_index_space_handle*>& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<sheaf::scattered_insertion_index_space_handle>(const sheaf::block<sheaf::scattered_insertion_index_space_handle*>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// block<poset_path>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<sheaf::poset_path>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::poset_path>(const sheaf::block<sheaf::poset_path>& xblk1, const sheaf::block<sheaf::poset_path>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::poset_path>(ostream& xos, const sheaf::block<sheaf::poset_path>& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<poset_path>(const sheaf::block<poset_path>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// block<poset_state_handle*>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<sheaf::poset_state_handle*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::poset_state_handle*>(const sheaf::block<sheaf::poset_state_handle*>& xblk1, const sheaf::block<sheaf::poset_state_handle*>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::poset_state_handle*>(ostream& xos, const sheaf::block<sheaf::poset_state_handle*>& xblk);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// block<scoped_index>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<sheaf::scoped_index>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::scoped_index>(const sheaf::block<sheaf::scoped_index>& xblk1, const sheaf::block<sheaf::scoped_index>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::scoped_index>(ostream& xos, const sheaf::block<sheaf::scoped_index>& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<scoped_index>(const sheaf::block<scoped_index>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// block<schema_descriptor>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<sheaf::schema_descriptor>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::schema_descriptor>(const sheaf::block<sheaf::schema_descriptor>& xblk1, const sheaf::block<sheaf::schema_descriptor>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::schema_descriptor>(ostream& xos, const sheaf::block<sheaf::schema_descriptor>& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<schema_descriptor>(const sheaf::block<schema_descriptor>& xblk, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// block<subposet>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<sheaf::subposet>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::subposet>(ostream& xos, const sheaf::block<sheaf::subposet>& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<subposet>(const sheaf::block<subposet>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// block<list<sheaf::scoped_index> >
//==============================================================================

#include "std_list.h"
typedef list<sheaf::scoped_index> list_type;

template class 
SHEAF_DLL_SPEC
sheaf::block<list_type>;

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<list_type>(const sheaf::block<list_type>& xblk, bool xinclude_shallow);

//==============================================================================
// block<set<int> >
//==============================================================================

#include "std_set.h"
typedef set<int> set_type;

template class 
SHEAF_DLL_SPEC
sheaf::block<set_type>;

// template 
// SHEAF_DLL_SPEC
// size_t sheaf::deep_size<set_type>(const sheaf::block<set_type>& xblk, bool xinclude_shallow);

//==============================================================================
// block<primitive_value>
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::block<sheaf::primitive_value>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
bool sheaf::operator == <sheaf::primitive_value>(const sheaf::block<sheaf::primitive_value>& xblk1, const sheaf::block<sheaf::primitive_value>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <sheaf::primitive_value>(ostream& xos, const sheaf::block<sheaf::primitive_value>& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<primitive_value>(const sheaf::block<primitive_value>& xblk, bool xinclude_shallow);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
//==============================================================================
//==============================================================================
