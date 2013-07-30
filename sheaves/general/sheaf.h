
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

#ifndef SHEAF_H
#define SHEAF_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_CSTDDEF_H
#include "std_cstddef.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

///
/// Namespace for the sheaves component of the sheaf system.
///
namespace sheaf
{
///
/// The preferred integer type.
///
typedef int int_type;

///
/// A signed integral type used to represent the difference of
/// two indices or iterators.
///
typedef long difference_type;

///
/// An unsigned integral type used to represent sizes and capacities.
///
typedef unsigned long size_type;

///
/// Synonym for void*.
///
typedef void* void_star;

///
/// Synonym for char*.
///
typedef char* c_string;

///
/// Selector for lower cover.
///
const bool LOWER = true;

///
/// Selector for upper cover.
///
const bool UPPER = false;

///
/// Iteration directions
///
const bool DOWN = true;

///
/// Iteration directions
///
const bool UP = false;

///
/// Iteration marker reset control
///
const bool RESET = true;

///
/// Iteration marker reset control
///
const bool NO_RESET = false;

///
/// Iteration strictness control
///
const bool STRICT = true;

///
/// Iteration strictness control
///
const bool NOT_STRICT = false;

///
/// Size of reserved term in top id space.
///
const size_type RESERVED_TERM_SIZE = 128;

///
/// Size of the explicit id space intervals.
///
const size_type EXPLICIT_INTERVAL_SIZE = 128;

// =============================================================================
// MISC FACET
// =============================================================================

///
/// Function to test for whether the LPS script has been executed.
///
/// Checks to see if the environment variable LPS_SCRIPT_HAS_RUN
/// has been set.  If not, the calling program is forced to exit
/// with a fatal error message; otherwise this method does nothing.
///
SHEAF_DLL_SPEC void check_lps_script_has_run();

///
/// Method to strip any command line down to it's rightmost delimited element                .
/// Used in unit test routines.
///
SHEAF_DLL_SPEC string filename_from_cmdline(string xargv);

///
/// The CVS branch tag this file is part of.
///
const string RELEASE_TAG = "$Name: HEAD $";

///
/// Returns the CVS branch tag for this codebase.                .
/// 
///
SHEAF_DLL_SPEC string get_release_tag();

///
/// True if isunordered(x1, x2) or x1 == x2.
///
SHEAF_DLL_SPEC bool isunordered_or_equals(float x1, float x2);

///
/// True if isunordered(x1, x2) or x1 == x2.
///
SHEAF_DLL_SPEC bool isunordered_or_equals(double x1, double x2);

///
/// True if isunordered(x1, x2) or x1 == x2.
///
SHEAF_DLL_SPEC bool isunordered_or_equals(long double x1, long double x2);
  

} // namespace sheaf


#endif // ifndef SHEAF_H
