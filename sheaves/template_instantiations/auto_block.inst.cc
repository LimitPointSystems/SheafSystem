
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

// Instantiations for class auto_block.

#include "auto_block.impl.h"



using namespace sheaf; // workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

// Instantiate with primitive types for general purpose use.

//==============================================================================
// auto_block<bool, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<bool>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<bool, sheaf::un_block_initialization_policy<bool> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <bool, sheaf::un_block_initialization_policy<bool> >(const sheaf::auto_block<bool, sheaf::un_block_initialization_policy<bool> >& xblk1,
                                                                             const sheaf::auto_block<bool, sheaf::un_block_initialization_policy<bool> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <bool, sheaf::un_block_initialization_policy<bool> >(ostream& xos,
                                                                                 const sheaf::auto_block<bool, sheaf::un_block_initialization_policy<bool> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<bool, sheaf::un_block_initialization_policy<bool> >(const sheaf::auto_block<bool, sheaf::un_block_initialization_policy<bool> >& xblk,
                                                                            bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<bool>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<bool, sheaf::zero_block_initialization_policy<bool> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <bool, sheaf::zero_block_initialization_policy<bool> >(const sheaf::auto_block<bool, sheaf::zero_block_initialization_policy<bool> >& xblk1,
									       const sheaf::auto_block<bool, sheaf::zero_block_initialization_policy<bool> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <bool, sheaf::zero_block_initialization_policy<bool> >(ostream& xos,
										   const sheaf::auto_block<bool, sheaf::zero_block_initialization_policy<bool> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<bool, sheaf::zero_block_initialization_policy<bool> >(const sheaf::auto_block<bool, sheaf::zero_block_initialization_policy<bool> >& xblk,
									      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<bool>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<bool, sheaf::invalid_block_initialization_policy<bool> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <bool, sheaf::invalid_block_initialization_policy<bool> >(const sheaf::auto_block<bool, sheaf::invalid_block_initialization_policy<bool> >& xblk1,
                                                                                  const sheaf::auto_block<bool, sheaf::invalid_block_initialization_policy<bool> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <bool, sheaf::invalid_block_initialization_policy<bool> >(ostream& xos,
                                                                                      const sheaf::auto_block<bool, sheaf::invalid_block_initialization_policy<bool> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<bool, sheaf::invalid_block_initialization_policy<bool> >(const sheaf::auto_block<bool, sheaf::invalid_block_initialization_policy<bool> >& xblk,
                                                                                 bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<char, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<char>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<char, sheaf::un_block_initialization_policy<char> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <char, sheaf::un_block_initialization_policy<char> >(const sheaf::auto_block<char, sheaf::un_block_initialization_policy<char> >& xblk1,
									     const sheaf::auto_block<char, sheaf::un_block_initialization_policy<char> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <char, sheaf::un_block_initialization_policy<char> >(ostream& xos,
										 const sheaf::auto_block<char, sheaf::un_block_initialization_policy<char> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<char, sheaf::un_block_initialization_policy<char> >(const sheaf::auto_block<char, sheaf::un_block_initialization_policy<char> >& xblk,
									    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<char>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<char, sheaf::invalid_block_initialization_policy<char> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <char, sheaf::invalid_block_initialization_policy<char> >(const sheaf::auto_block<char, sheaf::invalid_block_initialization_policy<char> >& xblk1,
										  const sheaf::auto_block<char, sheaf::invalid_block_initialization_policy<char> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <char, sheaf::invalid_block_initialization_policy<char> >(ostream& xos,
										      const sheaf::auto_block<char, sheaf::invalid_block_initialization_policy<char> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<char, sheaf::invalid_block_initialization_policy<char> >(const sheaf::auto_block<char, sheaf::invalid_block_initialization_policy<char> >& xblk,
										 bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<char>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<char, sheaf::zero_block_initialization_policy<char> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <char, sheaf::zero_block_initialization_policy<char> >(const sheaf::auto_block<char, sheaf::zero_block_initialization_policy<char> >& xblk1,
									       const sheaf::auto_block<char, sheaf::zero_block_initialization_policy<char> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <char, sheaf::zero_block_initialization_policy<char> >(ostream& xos,
										   const sheaf::auto_block<char, sheaf::zero_block_initialization_policy<char> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<char, sheaf::zero_block_initialization_policy<char> >(const sheaf::auto_block<char, sheaf::zero_block_initialization_policy<char> >& xblk,
									      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<signed char, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<signed char>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<signed char, sheaf::un_block_initialization_policy<signed char> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <signed char, sheaf::un_block_initialization_policy<signed char> >(const sheaf::auto_block<signed char, sheaf::un_block_initialization_policy<signed char> >& xblk1,
											   const sheaf::auto_block<signed char, sheaf::un_block_initialization_policy<signed char> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <signed char, sheaf::un_block_initialization_policy<signed char> >(ostream& xos,
											       const sheaf::auto_block<signed char, sheaf::un_block_initialization_policy<signed char> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<signed char, sheaf::un_block_initialization_policy<signed char> >(const sheaf::auto_block<signed char, sheaf::un_block_initialization_policy<signed char> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<signed char>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<signed char, sheaf::invalid_block_initialization_policy<signed char> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <signed char, sheaf::invalid_block_initialization_policy<signed char> >(const sheaf::auto_block<signed char, sheaf::invalid_block_initialization_policy<signed char> >& xblk1,
												const sheaf::auto_block<signed char, sheaf::invalid_block_initialization_policy<signed char> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <signed char, sheaf::invalid_block_initialization_policy<signed char> >(ostream& xos,
												    const sheaf::auto_block<signed char, sheaf::invalid_block_initialization_policy<signed char> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<signed char, sheaf::invalid_block_initialization_policy<signed char> >(const sheaf::auto_block<signed char, sheaf::invalid_block_initialization_policy<signed char> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<signed char>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<signed char, sheaf::zero_block_initialization_policy<signed char> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <signed char, sheaf::zero_block_initialization_policy<signed char> >(const sheaf::auto_block<signed char, sheaf::zero_block_initialization_policy<signed char> >& xblk1,
											     const sheaf::auto_block<signed char, sheaf::zero_block_initialization_policy<signed char> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <signed char, sheaf::zero_block_initialization_policy<signed char> >(ostream& xos,
												 const sheaf::auto_block<signed char, sheaf::zero_block_initialization_policy<signed char> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<signed char, sheaf::zero_block_initialization_policy<signed char> >(const sheaf::auto_block<signed char, sheaf::zero_block_initialization_policy<signed char> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<short int, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<short int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<short int, sheaf::un_block_initialization_policy<short int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC bool 
sheaf::operator == <short int, sheaf::un_block_initialization_policy<short int> >(const sheaf::auto_block<short int, sheaf::un_block_initialization_policy<short int> >& xblk1,
										  const sheaf::auto_block<short int, sheaf::un_block_initialization_policy<short int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <short int, sheaf::un_block_initialization_policy<short int> >(ostream& xos,
											   const sheaf::auto_block<short int, sheaf::un_block_initialization_policy<short int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<short int, sheaf::un_block_initialization_policy<short int> >(const sheaf::auto_block<short int, sheaf::un_block_initialization_policy<short int> >& xblk,
										      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<short int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<short int, sheaf::invalid_block_initialization_policy<short int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <short int, sheaf::invalid_block_initialization_policy<short int> >(const sheaf::auto_block<short int, sheaf::invalid_block_initialization_policy<short int> >& xblk1,
											    const sheaf::auto_block<short int, sheaf::invalid_block_initialization_policy<short int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <short int, sheaf::invalid_block_initialization_policy<short int> >(ostream& xos,
												const sheaf::auto_block<short int, sheaf::invalid_block_initialization_policy<short int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<short int, sheaf::invalid_block_initialization_policy<short int> >(const sheaf::auto_block<short int, sheaf::invalid_block_initialization_policy<short int> >& xblk,
											   bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<short int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<short int, sheaf::zero_block_initialization_policy<short int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <short int, sheaf::zero_block_initialization_policy<short int> >(const sheaf::auto_block<short int, sheaf::zero_block_initialization_policy<short int> >& xblk1,
											 const sheaf::auto_block<short int, sheaf::zero_block_initialization_policy<short int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <short int, sheaf::zero_block_initialization_policy<short int> >(ostream& xos,
											     const sheaf::auto_block<short int, sheaf::zero_block_initialization_policy<short int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<short int, sheaf::zero_block_initialization_policy<short int> >(const sheaf::auto_block<short int, sheaf::zero_block_initialization_policy<short int> >& xblk,
											bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<int, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<int, sheaf::un_block_initialization_policy<int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <int, sheaf::un_block_initialization_policy<int> >(const sheaf::auto_block<int, sheaf::un_block_initialization_policy<int> >& xblk1,
									   const sheaf::auto_block<int, sheaf::un_block_initialization_policy<int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <int, sheaf::un_block_initialization_policy<int> >(ostream& xos,
									       const sheaf::auto_block<int, sheaf::un_block_initialization_policy<int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<int, sheaf::un_block_initialization_policy<int> >(const sheaf::auto_block<int, sheaf::un_block_initialization_policy<int> >& xblk,
									  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<int, sheaf::invalid_block_initialization_policy<int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <int, sheaf::invalid_block_initialization_policy<int> >(const sheaf::auto_block<int, sheaf::invalid_block_initialization_policy<int> >& xblk1,
										const sheaf::auto_block<int, sheaf::invalid_block_initialization_policy<int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <int, sheaf::invalid_block_initialization_policy<int> >(ostream& xos,
										    const sheaf::auto_block<int, sheaf::invalid_block_initialization_policy<int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<int, sheaf::invalid_block_initialization_policy<int> >(const sheaf::auto_block<int, sheaf::invalid_block_initialization_policy<int> >& xblk,
									       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<int, sheaf::zero_block_initialization_policy<int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <int, sheaf::zero_block_initialization_policy<int> >(const sheaf::auto_block<int, sheaf::zero_block_initialization_policy<int> >& xblk1,
									     const sheaf::auto_block<int, sheaf::zero_block_initialization_policy<int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <int, sheaf::zero_block_initialization_policy<int> >(ostream& xos,
										 const sheaf::auto_block<int, sheaf::zero_block_initialization_policy<int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<int, sheaf::zero_block_initialization_policy<int> >(const sheaf::auto_block<int, sheaf::zero_block_initialization_policy<int> >& xblk,
									    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<long int, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<long int, sheaf::un_block_initialization_policy<long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long int, sheaf::un_block_initialization_policy<long int> >(const sheaf::auto_block<long int, sheaf::un_block_initialization_policy<long int> >& xblk1,
										     const sheaf::auto_block<long int, sheaf::un_block_initialization_policy<long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long int, sheaf::un_block_initialization_policy<long int> >(ostream& xos,
											 const sheaf::auto_block<long int, sheaf::un_block_initialization_policy<long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long int, sheaf::un_block_initialization_policy<long int> >(const sheaf::auto_block<long int, sheaf::un_block_initialization_policy<long int> >& xblk,
										    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<long int, sheaf::invalid_block_initialization_policy<long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long int, sheaf::invalid_block_initialization_policy<long int> >(const sheaf::auto_block<long int, sheaf::invalid_block_initialization_policy<long int> >& xblk1,
											  const sheaf::auto_block<long int, sheaf::invalid_block_initialization_policy<long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long int, sheaf::invalid_block_initialization_policy<long int> >(ostream& xos,
											      const sheaf::auto_block<long int, sheaf::invalid_block_initialization_policy<long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long int, sheaf::invalid_block_initialization_policy<long int> >(const sheaf::auto_block<long int, sheaf::invalid_block_initialization_policy<long int> >& xblk,
											 bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<long int, sheaf::zero_block_initialization_policy<long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long int, sheaf::zero_block_initialization_policy<long int> >(const sheaf::auto_block<long int, sheaf::zero_block_initialization_policy<long int> >& xblk1,
										       const sheaf::auto_block<long int, sheaf::zero_block_initialization_policy<long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long int, sheaf::zero_block_initialization_policy<long int> >(ostream& xos,
											   const sheaf::auto_block<long int, sheaf::zero_block_initialization_policy<long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long int, sheaf::zero_block_initialization_policy<long int> >(const sheaf::auto_block<long int, sheaf::zero_block_initialization_policy<long int> >& xblk,
										      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<long long int, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<long long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<long long int, sheaf::un_block_initialization_policy<long long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long long int, sheaf::un_block_initialization_policy<long long int> >(const sheaf::auto_block<long long int, sheaf::un_block_initialization_policy<long long int> >& xblk1,
											       const sheaf::auto_block<long long int, sheaf::un_block_initialization_policy<long long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long long int, sheaf::un_block_initialization_policy<long long int> >(ostream& xos,
												   const sheaf::auto_block<long long int, sheaf::un_block_initialization_policy<long long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long long int, sheaf::un_block_initialization_policy<long long int> >(const sheaf::auto_block<long long int, sheaf::un_block_initialization_policy<long long int> >& xblk,
											      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<long long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<long long int, sheaf::invalid_block_initialization_policy<long long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long long int, sheaf::invalid_block_initialization_policy<long long int> >(const sheaf::auto_block<long long int, sheaf::invalid_block_initialization_policy<long long int> >& xblk1,
												    const sheaf::auto_block<long long int, sheaf::invalid_block_initialization_policy<long long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long long int, sheaf::invalid_block_initialization_policy<long long int> >(ostream& xos,
													const sheaf::auto_block<long long int, sheaf::invalid_block_initialization_policy<long long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long long int, sheaf::invalid_block_initialization_policy<long long int> >(const sheaf::auto_block<long long int, sheaf::invalid_block_initialization_policy<long long int> >& xblk
												   , bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<long long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<long long int, sheaf::zero_block_initialization_policy<long long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long long int, sheaf::zero_block_initialization_policy<long long int> >(const sheaf::auto_block<long long int, sheaf::zero_block_initialization_policy<long long int> >& xblk1,
												 const sheaf::auto_block<long long int, sheaf::zero_block_initialization_policy<long long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long long int, sheaf::zero_block_initialization_policy<long long int> >(ostream& xos,
												     const sheaf::auto_block<long long int, sheaf::zero_block_initialization_policy<long long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long long int, sheaf::zero_block_initialization_policy<long long int> >(const sheaf::auto_block<long long int, sheaf::zero_block_initialization_policy<long long int> >& xblk,
												bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<unsigned char, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<unsigned char>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned char, sheaf::un_block_initialization_policy<unsigned char> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned char, sheaf::un_block_initialization_policy<unsigned char> >(const sheaf::auto_block<unsigned char, sheaf::un_block_initialization_policy<unsigned char> >& xblk1,
											       const sheaf::auto_block<unsigned char, sheaf::un_block_initialization_policy<unsigned char> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned char, sheaf::un_block_initialization_policy<unsigned char> >(ostream& xos,
												   const sheaf::auto_block<unsigned char, sheaf::un_block_initialization_policy<unsigned char> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned char, sheaf::un_block_initialization_policy<unsigned char> >(const sheaf::auto_block<unsigned char, sheaf::un_block_initialization_policy<unsigned char> >& xblk,
											      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<unsigned char>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned char, sheaf::invalid_block_initialization_policy<unsigned char> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned char, sheaf::invalid_block_initialization_policy<unsigned char> >(const sheaf::auto_block<unsigned char, sheaf::invalid_block_initialization_policy<unsigned char> >& xblk1,
												    const sheaf::auto_block<unsigned char, sheaf::invalid_block_initialization_policy<unsigned char> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned char, sheaf::invalid_block_initialization_policy<unsigned char> >(ostream& xos,
													const sheaf::auto_block<unsigned char, sheaf::invalid_block_initialization_policy<unsigned char> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned char, sheaf::invalid_block_initialization_policy<unsigned char> >(const sheaf::auto_block<unsigned char, sheaf::invalid_block_initialization_policy<unsigned char> >& xblk,
												   bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<unsigned char>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned char, sheaf::zero_block_initialization_policy<unsigned char> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned char, sheaf::zero_block_initialization_policy<unsigned char> >(const sheaf::auto_block<unsigned char, sheaf::zero_block_initialization_policy<unsigned char> >& xblk1,
												 const sheaf::auto_block<unsigned char, sheaf::zero_block_initialization_policy<unsigned char> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned char, sheaf::zero_block_initialization_policy<unsigned char> >(ostream& xos,
												     const sheaf::auto_block<unsigned char, sheaf::zero_block_initialization_policy<unsigned char> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned char, sheaf::zero_block_initialization_policy<unsigned char> >(const sheaf::auto_block<unsigned char, sheaf::zero_block_initialization_policy<unsigned char> >& xblk,
												bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<unsigned short int, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<unsigned short int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned short int, sheaf::un_block_initialization_policy<unsigned short int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned short int, sheaf::un_block_initialization_policy<unsigned short int> >(const sheaf::auto_block<unsigned short int, sheaf::un_block_initialization_policy<unsigned short int> >& xblk1,
													 const sheaf::auto_block<unsigned short int, sheaf::un_block_initialization_policy<unsigned short int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned short int, sheaf::un_block_initialization_policy<unsigned short int> >(ostream& xos,
													     const sheaf::auto_block<unsigned short int, sheaf::un_block_initialization_policy<unsigned short int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned short int, sheaf::un_block_initialization_policy<unsigned short int> >(const sheaf::auto_block<unsigned short int, sheaf::un_block_initialization_policy<unsigned short int> >& xblk,
													bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<unsigned short int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned short int, sheaf::invalid_block_initialization_policy<unsigned short int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned short int, sheaf::invalid_block_initialization_policy<unsigned short int> >(const sheaf::auto_block<unsigned short int, sheaf::invalid_block_initialization_policy<unsigned short int> >& xblk1,
													      const sheaf::auto_block<unsigned short int, sheaf::invalid_block_initialization_policy<unsigned short int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned short int, sheaf::invalid_block_initialization_policy<unsigned short int> >(ostream& xos,
														  const sheaf::auto_block<unsigned short int, sheaf::invalid_block_initialization_policy<unsigned short int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned short int, sheaf::invalid_block_initialization_policy<unsigned short int> >(const sheaf::auto_block<unsigned short int, sheaf::invalid_block_initialization_policy<unsigned short int> >& xblk,
													     bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<unsigned short int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned short int, sheaf::zero_block_initialization_policy<unsigned short int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned short int, sheaf::zero_block_initialization_policy<unsigned short int> >(const sheaf::auto_block<unsigned short int, sheaf::zero_block_initialization_policy<unsigned short int> >& xblk1,
													   const sheaf::auto_block<unsigned short int, sheaf::zero_block_initialization_policy<unsigned short int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned short int, sheaf::zero_block_initialization_policy<unsigned short int> >(ostream& xos,
													       const sheaf::auto_block<unsigned short int, sheaf::zero_block_initialization_policy<unsigned short int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned short int, sheaf::zero_block_initialization_policy<unsigned short int> >(const sheaf::auto_block<unsigned short int, sheaf::zero_block_initialization_policy<unsigned short int> >& xblk,
													  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<unsigned int, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<unsigned int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned int, sheaf::un_block_initialization_policy<unsigned int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned int, sheaf::un_block_initialization_policy<unsigned int> >(const sheaf::auto_block<unsigned int, sheaf::un_block_initialization_policy<unsigned int> >& xblk1,
											     const sheaf::auto_block<unsigned int, sheaf::un_block_initialization_policy<unsigned int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned int, sheaf::un_block_initialization_policy<unsigned int> >(ostream& xos,
												 const sheaf::auto_block<unsigned int, sheaf::un_block_initialization_policy<unsigned int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned int, sheaf::un_block_initialization_policy<unsigned int> >(const sheaf::auto_block<unsigned int, sheaf::un_block_initialization_policy<unsigned int> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<unsigned int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned int, sheaf::invalid_block_initialization_policy<unsigned int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned int, sheaf::invalid_block_initialization_policy<unsigned int> >(const sheaf::auto_block<unsigned int, sheaf::invalid_block_initialization_policy<unsigned int> >& xblk1,
												  const sheaf::auto_block<unsigned int, sheaf::invalid_block_initialization_policy<unsigned int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned int, sheaf::invalid_block_initialization_policy<unsigned int> >(ostream& xos,
												      const sheaf::auto_block<unsigned int, sheaf::invalid_block_initialization_policy<unsigned int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned int, sheaf::invalid_block_initialization_policy<unsigned int> >(const sheaf::auto_block<unsigned int, sheaf::invalid_block_initialization_policy<unsigned int> >& xblk,
												 bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<unsigned int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned int, sheaf::zero_block_initialization_policy<unsigned int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned int, sheaf::zero_block_initialization_policy<unsigned int> >(const sheaf::auto_block<unsigned int, sheaf::zero_block_initialization_policy<unsigned int> >& xblk1,
											       const sheaf::auto_block<unsigned int, sheaf::zero_block_initialization_policy<unsigned int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned int, sheaf::zero_block_initialization_policy<unsigned int> >(ostream& xos,
												   const sheaf::auto_block<unsigned int, sheaf::zero_block_initialization_policy<unsigned int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned int, sheaf::zero_block_initialization_policy<unsigned int> >(const sheaf::auto_block<unsigned int, sheaf::zero_block_initialization_policy<unsigned int> >& xblk,
											      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<unsigned long int, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<unsigned long int>;

template class 
SHEAF_DLL_SPEC sheaf::auto_block<unsigned long int, sheaf::un_block_initialization_policy<unsigned long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned long int, sheaf::un_block_initialization_policy<unsigned long int> >(const sheaf::auto_block<unsigned long int, sheaf::un_block_initialization_policy<unsigned long int> >& xblk1,
												       const sheaf::auto_block<unsigned long int, sheaf::un_block_initialization_policy<unsigned long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned long int, sheaf::un_block_initialization_policy<unsigned long int> >(ostream& xos,
													   const sheaf::auto_block<unsigned long int, sheaf::un_block_initialization_policy<unsigned long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long int, sheaf::un_block_initialization_policy<unsigned long int> >(const sheaf::auto_block<unsigned long int, sheaf::un_block_initialization_policy<unsigned long int> >& xblk,
												      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<unsigned long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned long int, sheaf::invalid_block_initialization_policy<unsigned long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned long int, sheaf::invalid_block_initialization_policy<unsigned long int> >(const sheaf::auto_block<unsigned long int, sheaf::invalid_block_initialization_policy<unsigned long int> >& xblk1,
													    const sheaf::auto_block<unsigned long int, sheaf::invalid_block_initialization_policy<unsigned long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned long int, sheaf::invalid_block_initialization_policy<unsigned long int> >(ostream& xos,
														const sheaf::auto_block<unsigned long int, sheaf::invalid_block_initialization_policy<unsigned long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long int, sheaf::invalid_block_initialization_policy<unsigned long int> >(const sheaf::auto_block<unsigned long int, sheaf::invalid_block_initialization_policy<unsigned long int> >& xblk,
													   bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<unsigned long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned long int, sheaf::zero_block_initialization_policy<unsigned long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned long int, sheaf::zero_block_initialization_policy<unsigned long int> >(const sheaf::auto_block<unsigned long int, sheaf::zero_block_initialization_policy<unsigned long int> >& xblk1,
													 const sheaf::auto_block<unsigned long int, sheaf::zero_block_initialization_policy<unsigned long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned long int, sheaf::zero_block_initialization_policy<unsigned long int> >(ostream& xos,
													     const sheaf::auto_block<unsigned long int, sheaf::zero_block_initialization_policy<unsigned long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long int, sheaf::zero_block_initialization_policy<unsigned long int> >(const sheaf::auto_block<unsigned long int, sheaf::zero_block_initialization_policy<unsigned long int> >& xblk,
													bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<unsigned long long int, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<unsigned long long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned long long int, sheaf::un_block_initialization_policy<unsigned long long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned long long int, sheaf::un_block_initialization_policy<unsigned long long int> >(const sheaf::auto_block<unsigned long long int, sheaf::un_block_initialization_policy<unsigned long long int> >& xblk1,
														 const sheaf::auto_block<unsigned long long int, sheaf::un_block_initialization_policy<unsigned long long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned long long int, sheaf::un_block_initialization_policy<unsigned long long int> >(ostream& xos,
														     const sheaf::auto_block<unsigned long long int, sheaf::un_block_initialization_policy<unsigned long long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long long int, sheaf::un_block_initialization_policy<unsigned long long int> >(const sheaf::auto_block<unsigned long long int, sheaf::un_block_initialization_policy<unsigned long long int> >& xblk,
														bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<unsigned long long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned long long int, sheaf::invalid_block_initialization_policy<unsigned long long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned long long int, sheaf::invalid_block_initialization_policy<unsigned long long int> >(const sheaf::auto_block<unsigned long long int, sheaf::invalid_block_initialization_policy<unsigned long long int> >& xblk1,
														      const sheaf::auto_block<unsigned long long int, sheaf::invalid_block_initialization_policy<unsigned long long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned long long int, sheaf::invalid_block_initialization_policy<unsigned long long int> >(ostream& xos,
															  const sheaf::auto_block<unsigned long long int, sheaf::invalid_block_initialization_policy<unsigned long long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long long int, sheaf::invalid_block_initialization_policy<unsigned long long int> >(const sheaf::auto_block<unsigned long long int, sheaf::invalid_block_initialization_policy<unsigned long long int> >& xblk,
														     bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<unsigned long long int>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<unsigned long long int, sheaf::zero_block_initialization_policy<unsigned long long int> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <unsigned long long int, sheaf::zero_block_initialization_policy<unsigned long long int> >(const sheaf::auto_block<unsigned long long int, sheaf::zero_block_initialization_policy<unsigned long long int> >& xblk1,
														   const sheaf::auto_block<unsigned long long int, sheaf::zero_block_initialization_policy<unsigned long long int> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <unsigned long long int, sheaf::zero_block_initialization_policy<unsigned long long int> >(ostream& xos,
														       const sheaf::auto_block<unsigned long long int, sheaf::zero_block_initialization_policy<unsigned long long int> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long long int, sheaf::zero_block_initialization_policy<unsigned long long int> >(const sheaf::auto_block<unsigned long long int, sheaf::zero_block_initialization_policy<unsigned long long int> >& xblk,
														  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<float, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<float>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<float, sheaf::un_block_initialization_policy<float> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <float, sheaf::un_block_initialization_policy<float> >(const sheaf::auto_block<float, sheaf::un_block_initialization_policy<float> >& xblk1,
									       const sheaf::auto_block<float, sheaf::un_block_initialization_policy<float> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <float, sheaf::un_block_initialization_policy<float> >(ostream& xos,
										   const sheaf::auto_block<float, sheaf::un_block_initialization_policy<float> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<float, sheaf::un_block_initialization_policy<float> >(const sheaf::auto_block<float, sheaf::un_block_initialization_policy<float> >& xblk,
									      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<float, sheaf::invalid_block_initialization_policy<float> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <float, sheaf::invalid_block_initialization_policy<float> >(const sheaf::auto_block<float, sheaf::invalid_block_initialization_policy<float> >& xblk1,
										    const sheaf::auto_block<float, sheaf::invalid_block_initialization_policy<float> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <float, sheaf::invalid_block_initialization_policy<float> >(ostream& xos,
											const sheaf::auto_block<float, sheaf::invalid_block_initialization_policy<float> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<float, sheaf::invalid_block_initialization_policy<float> >(const sheaf::auto_block<float, sheaf::invalid_block_initialization_policy<float> >& xblk,
										   bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<float>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<float, sheaf::zero_block_initialization_policy<float> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <float, sheaf::zero_block_initialization_policy<float> >(const sheaf::auto_block<float, sheaf::zero_block_initialization_policy<float> >& xblk1,
										 const sheaf::auto_block<float, sheaf::zero_block_initialization_policy<float> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <float, sheaf::zero_block_initialization_policy<float> >(ostream& xos,
										     const sheaf::auto_block<float, sheaf::zero_block_initialization_policy<float> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<float, sheaf::zero_block_initialization_policy<float> >(const sheaf::auto_block<float, sheaf::zero_block_initialization_policy<float> >& xblk,
										bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<double, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<double>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<double, sheaf::un_block_initialization_policy<double> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <double, sheaf::un_block_initialization_policy<double> >(const sheaf::auto_block<double, sheaf::un_block_initialization_policy<double> >& xblk1,
										 const sheaf::auto_block<double, sheaf::un_block_initialization_policy<double> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <double, sheaf::un_block_initialization_policy<double> >(ostream& xos,
										     const sheaf::auto_block<double, sheaf::un_block_initialization_policy<double> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<double, sheaf::un_block_initialization_policy<double> >(const sheaf::auto_block<double, sheaf::un_block_initialization_policy<double> >& xblk,
										bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<double, sheaf::invalid_block_initialization_policy<double> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <double, sheaf::invalid_block_initialization_policy<double> >(const sheaf::auto_block<double, sheaf::invalid_block_initialization_policy<double> >& xblk1,
										      const sheaf::auto_block<double, sheaf::invalid_block_initialization_policy<double> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <double, sheaf::invalid_block_initialization_policy<double> >(ostream& xos,
											  const sheaf::auto_block<double, sheaf::invalid_block_initialization_policy<double> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<double, sheaf::invalid_block_initialization_policy<double> >(const sheaf::auto_block<double, sheaf::invalid_block_initialization_policy<double> >& xblk,
										     bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<double>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<double, sheaf::zero_block_initialization_policy<double> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <double, sheaf::zero_block_initialization_policy<double> >(const sheaf::auto_block<double, sheaf::zero_block_initialization_policy<double> >& xblk1,
										   const sheaf::auto_block<double, sheaf::zero_block_initialization_policy<double> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <double, sheaf::zero_block_initialization_policy<double> >(ostream& xos,
										       const sheaf::auto_block<double, sheaf::zero_block_initialization_policy<double> >& xblk);

template 
SHEAF_DLL_SPEC
size_t sheaf::deep_size<double, sheaf::zero_block_initialization_policy<double> >(const sheaf::auto_block<double, sheaf::zero_block_initialization_policy<double> >& xblk,
										  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<double*, S>
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<double*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<double*, sheaf::un_block_initialization_policy<double*> >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <double*, sheaf::un_block_initialization_policy<double*> >(const sheaf::auto_block<double*, sheaf::un_block_initialization_policy<double*> >& xblk1,
                                                                                   const sheaf::auto_block<double*, sheaf::un_block_initialization_policy<double*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <double*, sheaf::un_block_initialization_policy<double*> >(ostream& xos,
                                                                                       const sheaf::auto_block<double*, sheaf::un_block_initialization_policy<double*> >& xblk);

// There are two signatures for deep_size, one for auto_block<T> and one for auto_block<T*>.
// To get the right template for deep_size(const auto_block<double*>, bool), the parameter is double, not double*.

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<double, sheaf::un_block_initialization_policy<double*> >(const sheaf::auto_block<double*, sheaf::un_block_initialization_policy<double*> >& xblk,
                                                                                 bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<double*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<double*, sheaf::zero_block_initialization_policy<double*> >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <double*, sheaf::zero_block_initialization_policy<double*> >(const sheaf::auto_block<double*, sheaf::zero_block_initialization_policy<double*> >& xblk1,
                                                                                     const sheaf::auto_block<double*, sheaf::zero_block_initialization_policy<double*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <double*, sheaf::zero_block_initialization_policy<double*> >(ostream& xos,
                                                                                         const sheaf::auto_block<double*, sheaf::zero_block_initialization_policy<double*> >& xblk);

// There are two signatures for deep_size, one for auto_block<T> and one for auto_block<T*>.
// To get the right template for deep_size(const auto_block<double*>, bool), the parameter is double, not double*.

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<double, sheaf::zero_block_initialization_policy<double*> >(const sheaf::auto_block<double*, sheaf::zero_block_initialization_policy<double*> >& xblk,
                                                                                   bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<double*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<double*, sheaf::invalid_block_initialization_policy<double*> >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <double*, sheaf::invalid_block_initialization_policy<double*> >(const sheaf::auto_block<double*, sheaf::invalid_block_initialization_policy<double*> >& xblk1,
                                                                                        const sheaf::auto_block<double*, sheaf::invalid_block_initialization_policy<double*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <double*, sheaf::invalid_block_initialization_policy<double*> >(ostream& xos,
                                                                                            const sheaf::auto_block<double*, sheaf::invalid_block_initialization_policy<double*> >& xblk);

// There are two signatures for deep_size, one for auto_block<T> and one for auto_block<T*>.
// To get the right template for deep_size(const auto_block<double*>, bool), the parameter is double, not double*.

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<double, sheaf::invalid_block_initialization_policy<double*> >(const sheaf::auto_block<double*, sheaf::invalid_block_initialization_policy<double*> >& xblk,
                                                                                      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<long double, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<long double>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<long double, sheaf::un_block_initialization_policy<long double> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long double, sheaf::un_block_initialization_policy<long double> >(const sheaf::auto_block<long double, sheaf::un_block_initialization_policy<long double> >& xblk1,
											   const sheaf::auto_block<long double, sheaf::un_block_initialization_policy<long double> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long double, sheaf::un_block_initialization_policy<long double> >(ostream& xos,
											       const sheaf::auto_block<long double, sheaf::un_block_initialization_policy<long double> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long double, sheaf::un_block_initialization_policy<long double> >(const sheaf::auto_block<long double, sheaf::un_block_initialization_policy<long double> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<long double>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<long double, sheaf::invalid_block_initialization_policy<long double> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long double, sheaf::invalid_block_initialization_policy<long double> >(const sheaf::auto_block<long double, sheaf::invalid_block_initialization_policy<long double> >& xblk1,
												const sheaf::auto_block<long double, sheaf::invalid_block_initialization_policy<long double> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long double, sheaf::invalid_block_initialization_policy<long double> >(ostream& xos,
												    const sheaf::auto_block<long double, sheaf::invalid_block_initialization_policy<long double> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long double, sheaf::invalid_block_initialization_policy<long double> >(const sheaf::auto_block<long double, sheaf::invalid_block_initialization_policy<long double> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<long double>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<long double, sheaf::zero_block_initialization_policy<long double> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <long double, sheaf::zero_block_initialization_policy<long double> >(const sheaf::auto_block<long double, sheaf::zero_block_initialization_policy<long double> >& xblk1,
											     const sheaf::auto_block<long double, sheaf::zero_block_initialization_policy<long double> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <long double, sheaf::zero_block_initialization_policy<long double> >(ostream& xos,
												 const sheaf::auto_block<long double, sheaf::zero_block_initialization_policy<long double> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long double, sheaf::zero_block_initialization_policy<long double> >(const sheaf::auto_block<long double, sheaf::zero_block_initialization_policy<long double> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
//==============================================================================


//==============================================================================
// auto_block<string, S>
//==============================================================================

#include "std_string.h"

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<std::string>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<std::string, sheaf::un_block_initialization_policy<std::string> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <std::string, sheaf::un_block_initialization_policy<std::string> >(const sheaf::auto_block<std::string, sheaf::un_block_initialization_policy<std::string> >& xblk1,
                                                                                           const sheaf::auto_block<std::string, sheaf::un_block_initialization_policy<std::string> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <std::string, sheaf::un_block_initialization_policy<std::string> >(ostream& xos,
                                                                                               const sheaf::auto_block<std::string, sheaf::un_block_initialization_policy<std::string> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<std::string, sheaf::un_block_initialization_policy<std::string> >(const sheaf::auto_block<std::string, sheaf::un_block_initialization_policy<std::string> >& xblk,
                                                                                          bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<string*, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::un_block_initialization_policy<std::string*>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<std::string*, sheaf::un_block_initialization_policy<std::string*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <std::string*, sheaf::un_block_initialization_policy<std::string*> >(const sheaf::auto_block<std::string*, sheaf::un_block_initialization_policy<std::string*> >& xblk1,
                                                                                             const sheaf::auto_block<std::string*, sheaf::un_block_initialization_policy<std::string*> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <std::string*, sheaf::un_block_initialization_policy<std::string*> >(ostream& xos,
                                                                                                 const sheaf::auto_block<std::string*, sheaf::un_block_initialization_policy<std::string*> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<std::string, sheaf::un_block_initialization_policy<std::string*> > (const sheaf::auto_block<std::string*, sheaf::un_block_initialization_policy<std::string*> >& xblk, 
                                                                                            bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::zero_block_initialization_policy<std::string*>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<std::string*, sheaf::zero_block_initialization_policy<std::string*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <std::string*, sheaf::zero_block_initialization_policy<std::string*> >(const sheaf::auto_block<std::string*, sheaf::zero_block_initialization_policy<std::string*> >& xblk1,
                                                                                               const sheaf::auto_block<std::string*, sheaf::zero_block_initialization_policy<std::string*> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <std::string*, sheaf::zero_block_initialization_policy<std::string*> >(ostream& xos,
                                                                                                   const sheaf::auto_block<std::string*, sheaf::zero_block_initialization_policy<std::string*> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<std::string, sheaf::zero_block_initialization_policy<std::string*> > (const sheaf::auto_block<std::string*, sheaf::zero_block_initialization_policy<std::string*> >& xblk, 
                                                                                              bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::invalid_block_initialization_policy<std::string*>;

template class 
SHEAF_DLL_SPEC 
sheaf::auto_block<std::string*, sheaf::invalid_block_initialization_policy<std::string*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <std::string*, sheaf::invalid_block_initialization_policy<std::string*> >(const sheaf::auto_block<std::string*, sheaf::invalid_block_initialization_policy<std::string*> >& xblk1,
                                                                                                  const sheaf::auto_block<std::string*, sheaf::invalid_block_initialization_policy<std::string*> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <std::string*, sheaf::invalid_block_initialization_policy<std::string*> >(ostream& xos,
                                                                                                      const sheaf::auto_block<std::string*, sheaf::invalid_block_initialization_policy<std::string*> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<std::string, sheaf::invalid_block_initialization_policy<std::string*> > (const sheaf::auto_block<std::string*, sheaf::invalid_block_initialization_policy<std::string*> >& xblk, 
                                                                                                 bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<poset_state_handle*, un_block_initialization_policy>
//==============================================================================

#include "poset_state_handle.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::poset_state_handle* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::poset_state_handle*, sheaf::un_block_initialization_policy<sheaf::poset_state_handle* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::poset_state_handle*, sheaf::un_block_initialization_policy<sheaf::poset_state_handle* > >(const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::un_block_initialization_policy<sheaf::poset_state_handle* > >& xblk1,
															  const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::un_block_initialization_policy<sheaf::poset_state_handle* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::poset_state_handle*, sheaf::un_block_initialization_policy<sheaf::poset_state_handle* > >(ostream& xos,
															      const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::un_block_initialization_policy<sheaf::poset_state_handle* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::poset_state_handle, sheaf::un_block_initialization_policy<sheaf::poset_state_handle* > >(const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::un_block_initialization_policy<sheaf::poset_state_handle* > >& xblk,
															bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<poset_state_handle*, zero_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::poset_state_handle* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::poset_state_handle*, sheaf::zero_block_initialization_policy<sheaf::poset_state_handle* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::poset_state_handle*, sheaf::zero_block_initialization_policy<sheaf::poset_state_handle* > >(const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::zero_block_initialization_policy<sheaf::poset_state_handle* > >& xblk1,
															    const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::zero_block_initialization_policy<sheaf::poset_state_handle* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::poset_state_handle*, sheaf::zero_block_initialization_policy<sheaf::poset_state_handle* > >(ostream& xos,
																const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::zero_block_initialization_policy<sheaf::poset_state_handle* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::poset_state_handle, sheaf::zero_block_initialization_policy<sheaf::poset_state_handle* > >(const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::zero_block_initialization_policy<sheaf::poset_state_handle* > >& xblk,
															  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<poset_state_handle*, invalid_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::poset_state_handle* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::poset_state_handle*, sheaf::invalid_block_initialization_policy<sheaf::poset_state_handle* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::poset_state_handle*, sheaf::invalid_block_initialization_policy<sheaf::poset_state_handle* > >(const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::invalid_block_initialization_policy<sheaf::poset_state_handle* > >& xblk1,
															       const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::invalid_block_initialization_policy<sheaf::poset_state_handle* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::poset_state_handle*, sheaf::invalid_block_initialization_policy<sheaf::poset_state_handle* > >(ostream& xos,
																   const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::invalid_block_initialization_policy<sheaf::poset_state_handle* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::poset_state_handle, sheaf::invalid_block_initialization_policy<sheaf::poset_state_handle* > >(const sheaf::auto_block<sheaf::poset_state_handle*, sheaf::invalid_block_initialization_policy<sheaf::poset_state_handle* > >& xblk,
															     bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<sheaf::arg_list, S>
//==============================================================================

#include "arg_list.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::arg_list>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::arg_list, sheaf::un_block_initialization_policy<sheaf::arg_list> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == <sheaf::arg_list, sheaf::un_block_initialization_policy<sheaf::arg_list> >(const sheaf::auto_block<sheaf::arg_list, sheaf::un_block_initialization_policy<sheaf::arg_list> >& xblk1,
//                                                                                                    const sheaf::auto_block<sheaf::arg_list, sheaf::un_block_initialization_policy<sheaf::arg_list> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::arg_list, sheaf::un_block_initialization_policy<sheaf::arg_list> >(ostream& xos,
                                                                                                       const sheaf::auto_block<sheaf::arg_list, sheaf::un_block_initialization_policy<sheaf::arg_list> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::arg_list, sheaf::un_block_initialization_policy<sheaf::arg_list> >(const sheaf::auto_block<sheaf::arg_list, sheaf::un_block_initialization_policy<sheaf::arg_list> >& xblk,
//                                                                                                   bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<sheaf::arg_list::arg_type, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::arg_list::arg_type>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::arg_list::arg_type, sheaf::un_block_initialization_policy<sheaf::arg_list::arg_type> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::arg_list::arg_type, sheaf::un_block_initialization_policy<sheaf::arg_list::arg_type> >(const sheaf::auto_block<sheaf::arg_list::arg_type, sheaf::un_block_initialization_policy<sheaf::arg_list::arg_type> >& xblk1,
                                                                                                                       const sheaf::auto_block<sheaf::arg_list::arg_type, sheaf::un_block_initialization_policy<sheaf::arg_list::arg_type> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::arg_list::arg_type, sheaf::un_block_initialization_policy<sheaf::arg_list::arg_type> >(ostream& xos,
                                                                                                                           const sheaf::auto_block<sheaf::arg_list::arg_type, sheaf::un_block_initialization_policy<sheaf::arg_list::arg_type> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::arg_list::arg_type, sheaf::un_block_initialization_policy<sheaf::arg_list::arg_type> >(const sheaf::auto_block<sheaf::arg_list::arg_type, sheaf::un_block_initialization_policy<sheaf::arg_list::arg_type> >& xblk,
                                                                                                                      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<sheaf::primitive_attributes, S>
//==============================================================================

#include "primitive_attributes.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::primitive_attributes>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::primitive_attributes, sheaf::un_block_initialization_policy<sheaf::primitive_attributes> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == <sheaf::primitive_attributes, sheaf::un_block_initialization_policy<sheaf::primitive_attributes> >(const sheaf::auto_block<sheaf::primitive_attributes, sheaf::un_block_initialization_policy<sheaf::primitive_attributes> >& xblk1,
//                                                                                                                            const sheaf::auto_block<sheaf::primitive_attributes, sheaf::un_block_initialization_policy<sheaf::primitive_attributes> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::primitive_attributes, sheaf::un_block_initialization_policy<sheaf::primitive_attributes> >(ostream& xos,
                                                                                                                               const sheaf::auto_block<sheaf::primitive_attributes, sheaf::un_block_initialization_policy<sheaf::primitive_attributes> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::primitive_attributes, sheaf::un_block_initialization_policy<sheaf::primitive_attributes> >(const sheaf::auto_block<sheaf::primitive_attributes, sheaf::un_block_initialization_policy<sheaf::primitive_attributes > >& xblk,
//                                                                                                                           bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<sheaf::poset_path, S>
//==============================================================================

#include "poset_path.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::poset_path>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::poset_path, sheaf::un_block_initialization_policy<sheaf::poset_path> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::poset_path, sheaf::un_block_initialization_policy<sheaf::poset_path> >(const sheaf::auto_block<sheaf::poset_path, sheaf::un_block_initialization_policy<sheaf::poset_path> >& xblk1,
                                                                                                       const sheaf::auto_block<sheaf::poset_path, sheaf::un_block_initialization_policy<sheaf::poset_path> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::poset_path, sheaf::un_block_initialization_policy<sheaf::poset_path> >(ostream& xos,
                                                                                                           const sheaf::auto_block<sheaf::poset_path, sheaf::un_block_initialization_policy<sheaf::poset_path> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::poset_path, sheaf::un_block_initialization_policy<sheaf::poset_path> >(const sheaf::auto_block<sheaf::poset_path, sheaf::un_block_initialization_policy<sheaf::poset_path> >& xblk,
                                                                                                      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<sheaf::schema_descriptor, S>
//==============================================================================

#include "schema_descriptor.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::schema_descriptor>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::schema_descriptor, sheaf::un_block_initialization_policy<sheaf::schema_descriptor> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::schema_descriptor, sheaf::un_block_initialization_policy<sheaf::schema_descriptor> >(const sheaf::auto_block<sheaf::schema_descriptor, sheaf::un_block_initialization_policy<sheaf::schema_descriptor> >& xblk1,
                                                                                                                     const sheaf::auto_block<sheaf::schema_descriptor, sheaf::un_block_initialization_policy<sheaf::schema_descriptor> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::schema_descriptor, sheaf::un_block_initialization_policy<sheaf::schema_descriptor> >(ostream& xos,
                                                                                                                         const sheaf::auto_block<sheaf::schema_descriptor, sheaf::un_block_initialization_policy<sheaf::schema_descriptor> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::schema_descriptor, sheaf::un_block_initialization_policy<sheaf::schema_descriptor> >(const sheaf::auto_block<sheaf::schema_descriptor, sheaf::un_block_initialization_policy<sheaf::schema_descriptor> >& xblk,
                                                                                                                    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<sheaf::subposet, S>
//==============================================================================

#include "subposet.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::subposet>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::subposet, sheaf::un_block_initialization_policy<sheaf::subposet> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == <sheaf::subposet, sheaf::un_block_initialization_policy<sheaf::subposet> >(const sheaf::auto_block<sheaf::subposet, sheaf::un_block_initialization_policy<sheaf::subposet> >& xblk1,
//                                                                                                    const sheaf::auto_block<sheaf::subposet, sheaf::un_block_initialization_policy<sheaf::subposet> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::subposet, sheaf::un_block_initialization_policy<sheaf::subposet> >(ostream& xos,
                                                                                                       const sheaf::auto_block<sheaf::subposet, sheaf::un_block_initialization_policy<sheaf::subposet> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::subposet, sheaf::un_block_initialization_policy<sheaf::subposet> >(const sheaf::auto_block<sheaf::subposet, sheaf::un_block_initialization_policy<sheaf::subposet> >& xblk,
                                                                                                  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<subposet_state*, un_block_initialization_policy>
//==============================================================================

#include "subposet_state.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::subposet_state* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::subposet_state*, sheaf::un_block_initialization_policy<sheaf::subposet_state* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::subposet_state*, sheaf::un_block_initialization_policy<sheaf::subposet_state* > >(const sheaf::auto_block<sheaf::subposet_state*, sheaf::un_block_initialization_policy<sheaf::subposet_state* > >& xblk1,
														  const sheaf::auto_block<sheaf::subposet_state*, sheaf::un_block_initialization_policy<sheaf::subposet_state* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::subposet_state*, sheaf::un_block_initialization_policy<sheaf::subposet_state* > >(ostream& xos,
														      const sheaf::auto_block<sheaf::subposet_state*, sheaf::un_block_initialization_policy<sheaf::subposet_state* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::subposet_state, sheaf::un_block_initialization_policy<sheaf::subposet_state* > >(const sheaf::auto_block<sheaf::subposet_state*, sheaf::un_block_initialization_policy<sheaf::subposet_state* > >& xblk,
														bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<subposet_state*, zero_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::subposet_state* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::subposet_state*, sheaf::zero_block_initialization_policy<sheaf::subposet_state* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::subposet_state*, sheaf::zero_block_initialization_policy<sheaf::subposet_state* > >(const sheaf::auto_block<sheaf::subposet_state*, sheaf::zero_block_initialization_policy<sheaf::subposet_state* > >& xblk1,
														    const sheaf::auto_block<sheaf::subposet_state*, sheaf::zero_block_initialization_policy<sheaf::subposet_state* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::subposet_state*, sheaf::zero_block_initialization_policy<sheaf::subposet_state* > >(ostream& xos,
															const sheaf::auto_block<sheaf::subposet_state*, sheaf::zero_block_initialization_policy<sheaf::subposet_state* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::subposet_state, sheaf::zero_block_initialization_policy<sheaf::subposet_state* > >(const sheaf::auto_block<sheaf::subposet_state*, sheaf::zero_block_initialization_policy<sheaf::subposet_state* > >& xblk,
														  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<subposet_state*, invalid_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::subposet_state* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::subposet_state*, sheaf::invalid_block_initialization_policy<sheaf::subposet_state* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::subposet_state*, sheaf::invalid_block_initialization_policy<sheaf::subposet_state* > >(const sheaf::auto_block<sheaf::subposet_state*, sheaf::invalid_block_initialization_policy<sheaf::subposet_state* > >& xblk1,
                                                                           const sheaf::auto_block<sheaf::subposet_state*, sheaf::invalid_block_initialization_policy<sheaf::subposet_state* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::subposet_state*, sheaf::invalid_block_initialization_policy<sheaf::subposet_state* > >(ostream& xos,
                                                                               const sheaf::auto_block<sheaf::subposet_state*, sheaf::invalid_block_initialization_policy<sheaf::subposet_state* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::subposet_state, sheaf::invalid_block_initialization_policy<sheaf::subposet_state* > >(const sheaf::auto_block<sheaf::subposet_state*, sheaf::invalid_block_initialization_policy<sheaf::subposet_state* > >& xblk,
                                                                          bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<block<double>, S>
//==============================================================================

#include "block.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<double> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<double>, sheaf::un_block_initialization_policy<sheaf::block<double> > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<double>, sheaf::un_block_initialization_policy<sheaf::block<double> > >(const sheaf::auto_block<sheaf::block<double>, sheaf::un_block_initialization_policy<sheaf::block<double> > >& xblk1,
                                                                                                              const sheaf::auto_block<sheaf::block<double>, sheaf::un_block_initialization_policy<sheaf::block<double> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<double>, sheaf::un_block_initialization_policy<sheaf::block<double> > >(ostream& xos,
                                                                                                                  const sheaf::auto_block<sheaf::block<double>, sheaf::un_block_initialization_policy<sheaf::block<double> > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::block<double>, sheaf::un_block_initialization_policy<sheaf::block<double> > >(const sheaf::auto_block<sheaf::block<double>, sheaf::un_block_initialization_policy<sheaf::block<double> > >& xblk,
                                                                                                             bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::block<double> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<double>, sheaf::zero_block_initialization_policy<sheaf::block<double> > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<double>, sheaf::zero_block_initialization_policy<sheaf::block<double> > >(const sheaf::auto_block<sheaf::block<double>, sheaf::zero_block_initialization_policy<sheaf::block<double> > >& xblk1,
                                                                                                                const sheaf::auto_block<sheaf::block<double>, sheaf::zero_block_initialization_policy<sheaf::block<double> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<double>, sheaf::zero_block_initialization_policy<sheaf::block<double> > >(ostream& xos,
                                                                                                                    const sheaf::auto_block<sheaf::block<double>, sheaf::zero_block_initialization_policy<sheaf::block<double> > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::block<double>, sheaf::zero_block_initialization_policy<sheaf::block<double> > >(const sheaf::auto_block<sheaf::block<double>, sheaf::zero_block_initialization_policy<sheaf::block<double> > >& xblk,
                                                                                                               bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::block<double> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<double>, sheaf::invalid_block_initialization_policy<sheaf::block<double> > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<double>, sheaf::invalid_block_initialization_policy<sheaf::block<double> > >(const sheaf::auto_block<sheaf::block<double>, sheaf::invalid_block_initialization_policy<sheaf::block<double> > >& xblk1,
                                                                                                                   const sheaf::auto_block<sheaf::block<double>, sheaf::invalid_block_initialization_policy<sheaf::block<double> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<double>, sheaf::invalid_block_initialization_policy<sheaf::block<double> > >(ostream& xos,
                                                                                                                       const sheaf::auto_block<sheaf::block<double>, sheaf::invalid_block_initialization_policy<sheaf::block<double> > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::block<double>, sheaf::invalid_block_initialization_policy<sheaf::block<double> > >(const sheaf::auto_block<sheaf::block<double>, sheaf::invalid_block_initialization_policy<sheaf::block<double> > >& xblk,
                                                                                                                  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<block<double>*, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<double>* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<double>*, sheaf::un_block_initialization_policy<sheaf::block<double>* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<double>*, sheaf::un_block_initialization_policy<sheaf::block<double>* > >(const sheaf::auto_block<sheaf::block<double>*, sheaf::un_block_initialization_policy<sheaf::block<double>* > >& xblk1,
                                                                                                                const sheaf::auto_block<sheaf::block<double>*, sheaf::un_block_initialization_policy<sheaf::block<double>* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<double>*, sheaf::un_block_initialization_policy<sheaf::block<double>* > >(ostream& xos,
                                                                                                                    const sheaf::auto_block<sheaf::block<double>*, sheaf::un_block_initialization_policy<sheaf::block<double>* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::block<double>, sheaf::un_block_initialization_policy<sheaf::block<double>* > >(const sheaf::auto_block<sheaf::block<double>*, sheaf::un_block_initialization_policy<sheaf::block<double>* > >& xblk,
                                                                                                               bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::block<double>* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<double>*, sheaf::zero_block_initialization_policy<sheaf::block<double>* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<double>*, sheaf::zero_block_initialization_policy<sheaf::block<double>* > >(const sheaf::auto_block<sheaf::block<double>*, sheaf::zero_block_initialization_policy<sheaf::block<double>* > >& xblk1,
                                                                                                                  const sheaf::auto_block<sheaf::block<double>*, sheaf::zero_block_initialization_policy<sheaf::block<double>* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<double>*, sheaf::zero_block_initialization_policy<sheaf::block<double>* > >(ostream& xos,
                                                                                                                      const sheaf::auto_block<sheaf::block<double>*, sheaf::zero_block_initialization_policy<sheaf::block<double>* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::block<double>, sheaf::zero_block_initialization_policy<sheaf::block<double>* > >(const sheaf::auto_block<sheaf::block<double>*, sheaf::zero_block_initialization_policy<sheaf::block<double>* > >& xblk,
                                                                                                                 bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::block<double>* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<double>*, sheaf::invalid_block_initialization_policy<sheaf::block<double>* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<double>*, sheaf::invalid_block_initialization_policy<sheaf::block<double>* > >(const sheaf::auto_block<sheaf::block<double>*, sheaf::invalid_block_initialization_policy<sheaf::block<double>* > >& xblk1,
                                                                                                                     const sheaf::auto_block<sheaf::block<double>*, sheaf::invalid_block_initialization_policy<sheaf::block<double>* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<double>*, sheaf::invalid_block_initialization_policy<sheaf::block<double>* > >(ostream& xos,
                                                                                                                         const sheaf::auto_block<sheaf::block<double>*, sheaf::invalid_block_initialization_policy<sheaf::block<double>* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::block<double>, sheaf::invalid_block_initialization_policy<sheaf::block<double>* > >(const sheaf::auto_block<sheaf::block<double>*, sheaf::invalid_block_initialization_policy<sheaf::block<double>* > >& xblk,
                                                                                                                    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<block<int>*, S>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<int>* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<int>*, sheaf::un_block_initialization_policy<sheaf::block<int>* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<int>*, sheaf::un_block_initialization_policy<sheaf::block<int>* > >(const sheaf::auto_block<sheaf::block<int>*, sheaf::un_block_initialization_policy<sheaf::block<int>* > >& xblk1,
                                                                                                          const sheaf::auto_block<sheaf::block<int>*, sheaf::un_block_initialization_policy<sheaf::block<int>* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<int>*, sheaf::un_block_initialization_policy<sheaf::block<int>* > >(ostream& xos,
                                                                                                              const sheaf::auto_block<sheaf::block<int>*, sheaf::un_block_initialization_policy<sheaf::block<int>* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::block<int>, sheaf::un_block_initialization_policy<sheaf::block<int>* > >(const sheaf::auto_block<sheaf::block<int>*, sheaf::un_block_initialization_policy<sheaf::block<int>* > >& xblk,
                                                                                                         bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::block<int>* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<int>*, sheaf::zero_block_initialization_policy<sheaf::block<int>* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<int>*, sheaf::zero_block_initialization_policy<sheaf::block<int>* > >(const sheaf::auto_block<sheaf::block<int>*, sheaf::zero_block_initialization_policy<sheaf::block<int>* > >& xblk1,
                                                                                                            const sheaf::auto_block<sheaf::block<int>*, sheaf::zero_block_initialization_policy<sheaf::block<int>* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<int>*, sheaf::zero_block_initialization_policy<sheaf::block<int>* > >(ostream& xos,
                                                                                                                const sheaf::auto_block<sheaf::block<int>*, sheaf::zero_block_initialization_policy<sheaf::block<int>* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::block<int>, sheaf::zero_block_initialization_policy<sheaf::block<int>* > >(const sheaf::auto_block<sheaf::block<int>*, sheaf::zero_block_initialization_policy<sheaf::block<int>* > >& xblk,
                                                                                                           bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::block<int>* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<int>*, sheaf::invalid_block_initialization_policy<sheaf::block<int>* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<int>*, sheaf::invalid_block_initialization_policy<sheaf::block<int>* > >(const sheaf::auto_block<sheaf::block<int>*, sheaf::invalid_block_initialization_policy<sheaf::block<int>* > >& xblk1,
                                                                                                               const sheaf::auto_block<sheaf::block<int>*, sheaf::invalid_block_initialization_policy<sheaf::block<int>* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<int>*, sheaf::invalid_block_initialization_policy<sheaf::block<int>* > >(ostream& xos,
                                                                                                                   const sheaf::auto_block<sheaf::block<int>*, sheaf::invalid_block_initialization_policy<sheaf::block<int>* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::block<int>, sheaf::invalid_block_initialization_policy<sheaf::block<int>* > >(const sheaf::auto_block<sheaf::block<int>*, sheaf::invalid_block_initialization_policy<sheaf::block<int>* > >& xblk,
                                                                                                              bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<scoped_index, un_block_initialization_policy>
//==============================================================================

#include "scoped_index.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::scoped_index >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::scoped_index, sheaf::un_block_initialization_policy<sheaf::scoped_index > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::scoped_index, sheaf::un_block_initialization_policy<sheaf::scoped_index > >(const sheaf::auto_block<sheaf::scoped_index, sheaf::un_block_initialization_policy<sheaf::scoped_index > >& xblk1,
                                                                                                            const sheaf::auto_block<sheaf::scoped_index, sheaf::un_block_initialization_policy<sheaf::scoped_index > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::scoped_index, sheaf::un_block_initialization_policy<sheaf::scoped_index > >(ostream& xos,
                                                                                                                const sheaf::auto_block<sheaf::scoped_index, sheaf::un_block_initialization_policy<sheaf::scoped_index > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::scoped_index, sheaf::un_block_initialization_policy<sheaf::scoped_index > >(const sheaf::auto_block<sheaf::scoped_index, sheaf::un_block_initialization_policy<sheaf::scoped_index > >& xblk,
                                                                                                           bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<scoped_index, zero_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::scoped_index >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::scoped_index, sheaf::zero_block_initialization_policy<sheaf::scoped_index > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::scoped_index, sheaf::zero_block_initialization_policy<sheaf::scoped_index > >(const sheaf::auto_block<sheaf::scoped_index, sheaf::zero_block_initialization_policy<sheaf::scoped_index > >& xblk1,
                                                                                                              const sheaf::auto_block<sheaf::scoped_index, sheaf::zero_block_initialization_policy<sheaf::scoped_index > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::scoped_index, sheaf::zero_block_initialization_policy<sheaf::scoped_index > >(ostream& xos,
                                                                                                                  const sheaf::auto_block<sheaf::scoped_index, sheaf::zero_block_initialization_policy<sheaf::scoped_index > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::scoped_index, sheaf::zero_block_initialization_policy<sheaf::scoped_index > >(const sheaf::auto_block<sheaf::scoped_index, sheaf::zero_block_initialization_policy<sheaf::scoped_index > >& xblk,
                                                                                                             bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<scoped_index, invalid_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::scoped_index >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::scoped_index, sheaf::invalid_block_initialization_policy<sheaf::scoped_index > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::scoped_index, sheaf::invalid_block_initialization_policy<sheaf::scoped_index > >(const sheaf::auto_block<sheaf::scoped_index, sheaf::invalid_block_initialization_policy<sheaf::scoped_index > >& xblk1,
                                                                                                                 const sheaf::auto_block<sheaf::scoped_index, sheaf::invalid_block_initialization_policy<sheaf::scoped_index > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::scoped_index, sheaf::invalid_block_initialization_policy<sheaf::scoped_index > >(ostream& xos,
                                                                                                                     const sheaf::auto_block<sheaf::scoped_index, sheaf::invalid_block_initialization_policy<sheaf::scoped_index > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::scoped_index, sheaf::invalid_block_initialization_policy<sheaf::scoped_index > >(const sheaf::auto_block<sheaf::scoped_index, sheaf::invalid_block_initialization_policy<sheaf::scoped_index > >& xblk,
                                                                                                                bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<list<sheaf::scoped_index>, un_block_initialization_policy>
//==============================================================================

#include "std_list.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<std::list<sheaf::scoped_index> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<std::list<sheaf::scoped_index>, sheaf::un_block_initialization_policy<std::list<sheaf::scoped_index> > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <std::list<sheaf::scoped_index>, sheaf::un_block_initialization_policy<std::list<sheaf::scoped_index> > >(const sheaf::auto_block<std::list<sheaf::scoped_index>, sheaf::un_block_initialization_policy<std::list<sheaf::scoped_index> > >& xblk1,
																  const sheaf::auto_block<std::list<sheaf::scoped_index>, sheaf::un_block_initialization_policy<std::list<sheaf::scoped_index> > >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << <std::list<sheaf::scoped_index>, sheaf::un_block_initialization_policy<std::list<sheaf::scoped_index> > >(ostream& xos,
//                                                                                const sheaf::auto_block<std::list<sheaf::scoped_index>, sheaf::un_block_initialization_policy<std::list<sheaf::scoped_index> > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<std::list<sheaf::scoped_index>, sheaf::un_block_initialization_policy<std::list<sheaf::scoped_index> > >(const sheaf::auto_block<std::list<sheaf::scoped_index>, sheaf::un_block_initialization_policy<std::list<sheaf::scoped_index> > >& xblk,
																 bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<primitive_value, un_block_initialization_policy>
//==============================================================================

#include "primitive_value.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::primitive_value >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::primitive_value, sheaf::un_block_initialization_policy<sheaf::primitive_value > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::primitive_value, sheaf::un_block_initialization_policy<sheaf::primitive_value > >(const sheaf::auto_block<sheaf::primitive_value, sheaf::un_block_initialization_policy<sheaf::primitive_value > >& xblk1,
                                                                                                                  const sheaf::auto_block<sheaf::primitive_value, sheaf::un_block_initialization_policy<sheaf::primitive_value > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::primitive_value, sheaf::un_block_initialization_policy<sheaf::primitive_value > >(ostream& xos,
                                                                                                                      const sheaf::auto_block<sheaf::primitive_value, sheaf::un_block_initialization_policy<sheaf::primitive_value > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::primitive_value, sheaf::un_block_initialization_policy<sheaf::primitive_value > >(const sheaf::auto_block<sheaf::primitive_value, sheaf::un_block_initialization_policy<sheaf::primitive_value > >& xblk,
                                                                                                                 bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<primitive_value, zero_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::primitive_value >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::primitive_value, sheaf::zero_block_initialization_policy<sheaf::primitive_value > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::primitive_value, sheaf::zero_block_initialization_policy<sheaf::primitive_value > >(const sheaf::auto_block<sheaf::primitive_value, sheaf::zero_block_initialization_policy<sheaf::primitive_value > >& xblk1,
                                                                                                                    const sheaf::auto_block<sheaf::primitive_value, sheaf::zero_block_initialization_policy<sheaf::primitive_value > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::primitive_value, sheaf::zero_block_initialization_policy<sheaf::primitive_value > >(ostream& xos,
                                                                                                                        const sheaf::auto_block<sheaf::primitive_value, sheaf::zero_block_initialization_policy<sheaf::primitive_value > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::primitive_value, sheaf::zero_block_initialization_policy<sheaf::primitive_value > >(const sheaf::auto_block<sheaf::primitive_value, sheaf::zero_block_initialization_policy<sheaf::primitive_value > >& xblk,
                                                                                                                   bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<primitive_value, invalid_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::primitive_value >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::primitive_value, sheaf::invalid_block_initialization_policy<sheaf::primitive_value > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::primitive_value, sheaf::invalid_block_initialization_policy<sheaf::primitive_value > >(const sheaf::auto_block<sheaf::primitive_value, sheaf::invalid_block_initialization_policy<sheaf::primitive_value > >& xblk1,
                                                                                                                       const sheaf::auto_block<sheaf::primitive_value, sheaf::invalid_block_initialization_policy<sheaf::primitive_value > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::primitive_value, sheaf::invalid_block_initialization_policy<sheaf::primitive_value > >(ostream& xos,
                                                                                                                           const sheaf::auto_block<sheaf::primitive_value, sheaf::invalid_block_initialization_policy<sheaf::primitive_value > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::primitive_value, sheaf::invalid_block_initialization_policy<sheaf::primitive_value > >(const sheaf::auto_block<sheaf::primitive_value, sheaf::invalid_block_initialization_policy<sheaf::primitive_value > >& xblk,
                                                                                                                      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<explicit_index_space_state*, un_block_initialization_policy>
//==============================================================================

#include "explicit_index_space_state.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::explicit_index_space_state* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::un_block_initialization_policy<sheaf::explicit_index_space_state* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::explicit_index_space_state*, sheaf::un_block_initialization_policy<sheaf::explicit_index_space_state* > >(const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::un_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk1,
																	  const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::un_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::explicit_index_space_state*, sheaf::un_block_initialization_policy<sheaf::explicit_index_space_state* > >(ostream& xos,
																	      const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::un_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::explicit_index_space_state, sheaf::un_block_initialization_policy<sheaf::explicit_index_space_state* > >(const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::un_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk,
																	bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<explicit_index_space_state*, zero_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::explicit_index_space_state* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::zero_block_initialization_policy<sheaf::explicit_index_space_state* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::explicit_index_space_state*, sheaf::zero_block_initialization_policy<sheaf::explicit_index_space_state* > >(const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::zero_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk1,
																	    const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::zero_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::explicit_index_space_state*, sheaf::zero_block_initialization_policy<sheaf::explicit_index_space_state* > >(ostream& xos,
																		const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::zero_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::explicit_index_space_state, sheaf::zero_block_initialization_policy<sheaf::explicit_index_space_state* > >(const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::zero_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk,
																	  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<explicit_index_space_state*, invalid_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::explicit_index_space_state* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::invalid_block_initialization_policy<sheaf::explicit_index_space_state* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::explicit_index_space_state*, sheaf::invalid_block_initialization_policy<sheaf::explicit_index_space_state* > >(const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::invalid_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk1,
																	       const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::invalid_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::explicit_index_space_state*, sheaf::invalid_block_initialization_policy<sheaf::explicit_index_space_state* > >(ostream& xos,
																		   const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::invalid_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::explicit_index_space_state, sheaf::invalid_block_initialization_policy<sheaf::explicit_index_space_state* > >(const sheaf::auto_block<sheaf::explicit_index_space_state*, sheaf::invalid_block_initialization_policy<sheaf::explicit_index_space_state* > >& xblk,
																	     bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<index_space_handle*, un_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::index_space_handle* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::index_space_handle*, sheaf::un_block_initialization_policy<sheaf::index_space_handle* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::index_space_handle*, sheaf::un_block_initialization_policy<sheaf::index_space_handle* > >(const sheaf::auto_block<sheaf::index_space_handle*, sheaf::un_block_initialization_policy<sheaf::index_space_handle* > >& xblk1,
															  const sheaf::auto_block<sheaf::index_space_handle*, sheaf::un_block_initialization_policy<sheaf::index_space_handle* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::index_space_handle*, sheaf::un_block_initialization_policy<sheaf::index_space_handle* > >(ostream& xos,
															      const sheaf::auto_block<sheaf::index_space_handle*, sheaf::un_block_initialization_policy<sheaf::index_space_handle* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::index_space_handle, sheaf::un_block_initialization_policy<sheaf::index_space_handle* > >(const sheaf::auto_block<sheaf::index_space_handle*, sheaf::un_block_initialization_policy<sheaf::index_space_handle* > >& xblk,
															bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<index_space_handle*, zero_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::index_space_handle* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::index_space_handle* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::index_space_handle* > >(const sheaf::auto_block<sheaf::index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::index_space_handle* > >& xblk1,
															    const sheaf::auto_block<sheaf::index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::index_space_handle* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::index_space_handle* > >(ostream& xos,
																const sheaf::auto_block<sheaf::index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::index_space_handle* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::index_space_handle, sheaf::zero_block_initialization_policy<sheaf::index_space_handle* > >(const sheaf::auto_block<sheaf::index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::index_space_handle* > >& xblk,
															  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<index_space_handle*, invalid_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::index_space_handle* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::index_space_handle* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::index_space_handle* > >(const sheaf::auto_block<sheaf::index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::index_space_handle* > >& xblk1,
															       const sheaf::auto_block<sheaf::index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::index_space_handle* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::index_space_handle* > >(ostream& xos,
																   const sheaf::auto_block<sheaf::index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::index_space_handle* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::index_space_handle, sheaf::invalid_block_initialization_policy<sheaf::index_space_handle* > >(const sheaf::auto_block<sheaf::index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::index_space_handle* > >& xblk,
															     bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<mutable_index_space_handle*, un_block_initialization_policy>
//==============================================================================

#include "mutable_index_space_handle.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::mutable_index_space_handle* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::un_block_initialization_policy<sheaf::mutable_index_space_handle* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::mutable_index_space_handle*, sheaf::un_block_initialization_policy<sheaf::mutable_index_space_handle* > >(const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::un_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk1,
																	  const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::un_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::mutable_index_space_handle*, sheaf::un_block_initialization_policy<sheaf::mutable_index_space_handle* > >(ostream& xos,
																	      const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::un_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::mutable_index_space_handle, sheaf::un_block_initialization_policy<sheaf::mutable_index_space_handle* > >(const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::un_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk,
																	bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<mutable_index_space_handle*, zero_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::mutable_index_space_handle* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::mutable_index_space_handle* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::mutable_index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::mutable_index_space_handle* > >(const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk1,
																	    const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::mutable_index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::mutable_index_space_handle* > >(ostream& xos,
																		const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::mutable_index_space_handle, sheaf::zero_block_initialization_policy<sheaf::mutable_index_space_handle* > >(const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::zero_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk,
																	  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<mutable_index_space_handle*, invalid_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::mutable_index_space_handle* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::mutable_index_space_handle* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::mutable_index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::mutable_index_space_handle* > >(const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk1,
																	       const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::mutable_index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::mutable_index_space_handle* > >(ostream& xos,
																		   const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::mutable_index_space_handle, sheaf::invalid_block_initialization_policy<sheaf::mutable_index_space_handle* > >(const sheaf::auto_block<sheaf::mutable_index_space_handle*, sheaf::invalid_block_initialization_policy<sheaf::mutable_index_space_handle* > >& xblk,
																	     bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<poset_dof_map*, un_block_initialization_policy>
//==============================================================================

#include "poset_dof_map.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::poset_dof_map* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::poset_dof_map*, sheaf::un_block_initialization_policy<sheaf::poset_dof_map* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::poset_dof_map*, sheaf::un_block_initialization_policy<sheaf::poset_dof_map* > >(const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::un_block_initialization_policy<sheaf::poset_dof_map* > >& xblk1,
														const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::un_block_initialization_policy<sheaf::poset_dof_map* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::poset_dof_map*, sheaf::un_block_initialization_policy<sheaf::poset_dof_map* > >(ostream& xos,
														    const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::un_block_initialization_policy<sheaf::poset_dof_map* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::poset_dof_map, sheaf::un_block_initialization_policy<sheaf::poset_dof_map* > >(const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::un_block_initialization_policy<sheaf::poset_dof_map* > >& xblk,
													      bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<poset_dof_map*, zero_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<sheaf::poset_dof_map* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::poset_dof_map*, sheaf::zero_block_initialization_policy<sheaf::poset_dof_map* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::poset_dof_map*, sheaf::zero_block_initialization_policy<sheaf::poset_dof_map* > >(const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::zero_block_initialization_policy<sheaf::poset_dof_map* > >& xblk1,
														  const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::zero_block_initialization_policy<sheaf::poset_dof_map* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::poset_dof_map*, sheaf::zero_block_initialization_policy<sheaf::poset_dof_map* > >(ostream& xos,
														      const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::zero_block_initialization_policy<sheaf::poset_dof_map* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::poset_dof_map, sheaf::zero_block_initialization_policy<sheaf::poset_dof_map* > >(const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::zero_block_initialization_policy<sheaf::poset_dof_map* > >& xblk,
														bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<poset_dof_map*, invalid_block_initialization_policy>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<sheaf::poset_dof_map* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::poset_dof_map*, sheaf::invalid_block_initialization_policy<sheaf::poset_dof_map* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::poset_dof_map*, sheaf::invalid_block_initialization_policy<sheaf::poset_dof_map* > >(const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::invalid_block_initialization_policy<sheaf::poset_dof_map* > >& xblk1,
														     const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::invalid_block_initialization_policy<sheaf::poset_dof_map* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::poset_dof_map*, sheaf::invalid_block_initialization_policy<sheaf::poset_dof_map* > >(ostream& xos,
															 const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::invalid_block_initialization_policy<sheaf::poset_dof_map* > >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<sheaf::poset_dof_map, sheaf::invalid_block_initialization_policy<sheaf::poset_dof_map* > >(const sheaf::auto_block<sheaf::poset_dof_map*, sheaf::invalid_block_initialization_policy<sheaf::poset_dof_map* > >& xblk,
														   bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<set<int>, un_block_initialization_policy>
//==============================================================================

#include "std_set.h"

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<std::set<int> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<std::set<int>, sheaf::un_block_initialization_policy<std::set<int> > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <std::set<int>, sheaf::un_block_initialization_policy<std::set<int> > >(const sheaf::auto_block<std::set<int>, sheaf::un_block_initialization_policy<std::set<int> > >& xblk1,
                                                                                                const sheaf::auto_block<std::set<int>, sheaf::un_block_initialization_policy<std::set<int> > >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << <std::set<int>, sheaf::un_block_initialization_policy<std::set<int> > >(ostream& xos,
//                                                                                                     const sheaf::auto_block<std::set<int>, sheaf::un_block_initialization_policy<std::set<int> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<std::set<int>, sheaf::un_block_initialization_policy<std::set<int> > >(const sheaf::auto_block<std::set<int>, sheaf::un_block_initialization_policy<std::set<int> > >& xblk,
//                                                                                                bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
//==============================================================================
