
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

// Include file for some libSheaf specific extensions to assert.h

// @issue These macros are not named with any unique prefix to avoid name clashes.

#ifndef ASSERT_CONTRACT_H
#define ASSERT_CONTRACT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif


namespace sheaf
{
  ///
  /// Tests condition xcond and throws exception if false;
  /// exception message includes xmsg, file name xfile, and line number xline.
  ///
  SHEAF_DLL_SPEC void check_contract(bool xcond, const char* xmsg, const char* xfile, int xline);  
 
  ///
  /// Tests condition xcond for index xi and throws exception if false;
  /// exception message includes xcond_msg, xi_msg, file name xfile, and line number xline.
  ///
  SHEAF_DLL_SPEC void check_contract(bool xcond, 
				     const char* xcond_msg, 
				     int xi, 
				     const char* xi_msg, 
				     const char* xfile, 
				     int xline);  
 
  ///
  /// Throws exception for existential quantification failure.
  ///
  SHEAF_DLL_SPEC void post_there_exists_failed(const char* xcond_msg, 
					       int xi, 
					       const char* xi_msg, 
					       int xmin, 
					       int xub, 
					       const char* xfile, 
					       int xline);  
 
  ///
  /// Throws exception for attempt to invoke is_abstract or not implemented.
  ///
  SHEAF_DLL_SPEC void post_unimplemented(const char* xcond_msg, const char* xfile, int xline);    

} // end namespace sheaf

#ifndef NDEBUG
// ===========================================================
// CONTRACTS ON
// ===========================================================

/// @issue Implementing contracts with macros creates the potential
/// for unresolvable name clashes; try to choose names to avoid obvious clashes.

// Assert condition x.

#define dbc_assert(x) sheaf::check_contract((x), #x, __FILE__, __LINE__)

// Assert condition x for case specified by int xi.

#define dbc_assert_for_i(x, xi) sheaf::check_contract((x), #x, (xi), #xi, __FILE__, __LINE__)

// "Universal" quantification of condition xcondition
// for int interval [xi_min, xi_ub). Xcondition should depend on int xi,

#define dbc_assert_for_all(xi, xi_min, xi_ub, xcondition) \
{ for(int xi = (xi_min); xi < (xi_ub); ++xi) dbc_assert_for_i((xcondition), xi); }

// "Universal" quantification of condition xcondition
// for values specified by xinit, xtest, and xincrement.
// Xcondition should depend on variable declared in xinit.

#define dbc_assert_for_range(xinit, xtest, xincrement, xcondition) \
{ xinit; while(xtest) { dbc_assert(xcondition); xincrement; } }

// "Universal" quatification of condition xcondition
// for values specified by xinit, xtest, xincrement, and xfinalize.
// Xcondition should depend on variable declared in xinit.

#define dbc_assert_for_iterator(xinit, xtest, xincrement, xcondition, xfinalize) \
{ xinit; while(xtest) { dbc_assert(xcondition); xincrement; } xfinalize; }

// "Existential" quantification of condition xcondition
// for int interval [xi_min, xi_ub).
// Xcondition should depend on int xi,

#define dbc_assert_there_exists(xi, xi_min, xi_ub, xcondition) \
{ \
  for(int xi = (xi_min); xi < (xi_ub) && !(xcondition); ++xi) \
  { \
    if(xi == ((xi_ub)-1)) \
    { \
      sheaf::post_there_exists_failed(#xcondition, xi, #xi, (xi_min), (xi_ub), __FILE__, __LINE__); \
    } \
  } \
}

// General assertion.

#define assertion(x) dbc_assert(x)

// "Old" variable declaration x; 

#define define_old_variable(x) x

// Arbitrary code fragment x.

#define if_contract(x) x

// Precondition clause.

#define require(x) dbc_assert(x)
#define require_for_all(i, i_min, i_ub, condition)  dbc_assert_for_all(i, i_min, i_ub, condition)
#define require_for_range(init, test, increment, condition)  dbc_assert_for_range(init, test, increment, condition)
#define require_for_iterator(init, test, increment, condition, finalize) dbc_assert_for_iterator(init, test, increment, condition, finalize);
#define require_there_exists(i, i_min, i_ub, condition)  dbc_assert_there_exists(i, i_min, i_ub, condition)

// Postcondition clause.

#define ensure(x) dbc_assert(x)
#define ensure_for_all(i, i_min, i_ub, condition)  dbc_assert_for_all(i, i_min, i_ub, condition)
#define ensure_for_range(init, test, increment, condition)  dbc_assert_for_range(init, test, increment, condition)
#define ensure_for_iterator(init, test, increment, condition, finalize) dbc_assert_for_iterator(init, test, increment, condition, finalize);
#define ensure_there_exists(i, i_min, i_ub, condition)  dbc_assert_there_exists(i, i_min, i_ub, condition)

// Invariant clauses.

#define invariance(x) dbc_assert(x)
#define invariance_for_all(i, i_min, i_ub, condition)  dbc_assert_for_all(i, i_min, i_ub, condition)
#define invariance_for_range(init, test, increment, condition)  dbc_assert_for_range(init, test, increment, condition)
#define invariance_for_iterator(init, test, increment, condition, finalize) dbc_assert_for_iterator(init, test, increment, condition, finalize);
#define invariance_there_exists(i, i_min, i_ub, condition)  dbc_assert_there_exists(i, i_min, i_ub, condition)

// ===========================================================
// END CONTRACTS ON
// ===========================================================
#else
// ===========================================================
// CONTRACTS OFF
// ===========================================================

#define assertion(x)
#define define_old_variable(x)
#define if_contract(x)
#define require(x)
#define require_for_all(i, i_min, i_ub, condition)
#define require_for_range(init, test, increment, condition)
#define require_for_iterator(init, test, increment, condition, finalize)
#define require_there_exists(i, i_min, i_ub, condition)
#define ensure(x)
#define ensure_for_all(i, i_min, i_ub, condition)
#define ensure_for_range(init, test, increment, condition)
#define ensure_for_iterator(init, test, increment, condition, finalize)
#define ensure_there_exists(i, i_min, i_ub, condition)
#define invariance(x)
#define invariance_for_all(i, i_min, i_ub, condition)
#define invariance_for_range(init, test, increment, condition)
#define invariance_for_iterator(init, test, increment, condition, finalize)
#define invariance_there_exists(i, i_min, i_ub, condition)

// ===========================================================
// END CONTRACTS OFF
// ===========================================================
#endif // NDEBUG

// Indicates that function is "conceptually abstract" and intended
// to be implemented in descendants, but a stub has been implemented
// in the current class in order to define the contract. Equivalent
// to the "is deferred" syntax in Eiffel.

#define is_abstract() sheaf::post_unimplemented("is abstract", __FILE__, __LINE__)

// Indicates that function is not implemented.

#define not_implemented() sheaf::post_unimplemented("not implemented", __FILE__, __LINE__)

// Some macros for inserting "comment" assertions
// These allow construction of assertions that aren't executable,
// or that we don't want executed because they are redundant.
// These nevertheless look just like assertions and can be extracted
// by any tool that we build to extract assertions (e.g. an equivalent
// of the Eiffel short tool.)

#define unexecutable(x) true
#define precondition_of(x) true
#define postcondition_of(x) true

// Every function should have as a postcondition exactly one of
//     ensure(is_basic_query());
// or
//     ensure(is_derived_query());
// or
//     ensure(invariant());
// See "Design by Contract, by Example", by Richard Mitchell
// and Jim McKim for the definitions of basic and derived queries.
// As used here, the term query refers to a function that does not
// change the state of the object, but merely returns a value, and
// therefore cannot affect the value of invariant().

#define is_basic_query true
#define is_derived_query true


#endif // ifndef ASSERT_CONTRACT_H
