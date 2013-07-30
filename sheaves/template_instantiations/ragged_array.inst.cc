
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

// Explicit instantiation for class template RAGGED_ARRAY.

#include "ragged_array.impl.h"

using namespace sheaf; // workaround for MS C++ bug.

// Instantiate with primitive types for general purpose use.

// Bool

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<bool>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <bool>(ostream& xos, const sheaf::ragged_array<bool>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<bool>(const sheaf::ragged_array<bool>& xblk, bool xinclude_shallow);

// char

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<char>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <char>(ostream& xos, const sheaf::ragged_array<char>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<char>(const sheaf::ragged_array<char>& xblk, bool xinclude_shallow);

// signed char

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<signed char>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <signed char>(ostream& xos, const sheaf::ragged_array<signed char>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<signed char>(const sheaf::ragged_array<signed char>& xblk, bool xinclude_shallow);

// short int

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<short int>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <short int>(ostream& xos, const sheaf::ragged_array<short int>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<short int>(const sheaf::ragged_array<short int>& xblk, bool xinclude_shallow);

// int

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<int>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <int>(ostream& xos, const sheaf::ragged_array<int>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<int>(const sheaf::ragged_array<int>& xblk, bool xinclude_shallow);

// long int

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<long int>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <long int>(ostream& xos, const sheaf::ragged_array<long int>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long>(const sheaf::ragged_array<long int>& xblk, bool xinclude_shallow);

// long long int

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<long long int>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <long long int>(ostream& xos, const sheaf::ragged_array<long long int>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long long int>(const sheaf::ragged_array<long long int>& xblk, bool xinclude_shallow);

// unsigned char

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<unsigned char>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <unsigned char>(ostream& xos, const sheaf::ragged_array<unsigned char>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned char>(const sheaf::ragged_array<unsigned char>& xblk, bool xinclude_shallow);

// unsigned short int

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<unsigned short int>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <unsigned short int>(ostream& xos, const sheaf::ragged_array<unsigned short int>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned short int>(const sheaf::ragged_array<unsigned short int>& xblk, bool xinclude_shallow);

// unsigned int

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<unsigned int>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <unsigned int>(ostream& xos, const sheaf::ragged_array<unsigned int>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned int>(const sheaf::ragged_array<unsigned int>& xblk, bool xinclude_shallow);

// unsigned long int

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<unsigned long int>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <unsigned long int>(ostream& xos, const sheaf::ragged_array<unsigned long int>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long int>(const sheaf::ragged_array<unsigned long int>& xblk, bool xinclude_shallow);

// unsigned long long int

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<unsigned long long int>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <unsigned long long int>(ostream& xos, const sheaf::ragged_array<unsigned long long int>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<unsigned long long int>(const sheaf::ragged_array<unsigned long long int>& xblk, bool xinclude_shallow);

// float

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<float>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <float>(ostream& xos, const sheaf::ragged_array<float>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<float>(const sheaf::ragged_array<float>& xblk, bool xinclude_shallow);

// double

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<double>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <double>(ostream& xos, const sheaf::ragged_array<double>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<double>(const sheaf::ragged_array<double>& xblk, bool xinclude_shallow);

// long double

template class 
SHEAF_DLL_SPEC
sheaf::ragged_array<long double>;

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <long double>(ostream& xos, const sheaf::ragged_array<long double>& xrga);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<long double>(const sheaf::ragged_array<long double>& xblk, bool xinclude_shallow);


#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
