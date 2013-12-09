
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

// Definitions for class sheaf_constants

#include "sheaf.h"

#include "error_message.h"
#include "std_cstdlib.h"
#include "std_cmath.h"
#include "std_iostream.h"

using namespace std;

// =============================================================================
// MISC FACET
// =============================================================================

///
void
sheaf::
check_lps_script_has_run()
{
  // Check to see if the environment variable LPS_SCRIPT_HAS_RUN
  // has been set.  If not, exit with a fatal error message;
  // otherwise do nothing.

  if(getenv("LPS_SCRIPT_HAS_RUN") == 0)
  {
    post_fatal_error_message("LPS script has not been executed.");
  }
}

///
std::string
sheaf::
filename_from_cmdline(std::string xargv)
{
  string result;
  // Look for backslashes no matter the OS
  string key = "\\";

  // Find any backslashes in the filename and convert them to slashes
  string::size_type bslash = xargv.rfind(key);
  if (bslash!=string::npos)
    xargv.replace (bslash,key.length(),"/");

  // find the rightmost slash in the filename
  string::size_type slash = xargv.rfind('/');

  // There weren't any path delimiters; return argv.
  if (slash == string::npos)
  {
    result = xargv;  
  }
  else   // Return the undelimited string value of argv.
  {
   result = xargv.substr(slash+1);
  }

  return result;
}

///
std::string
sheaf::
get_release_tag()
{
  // Expansion of the CVS keyword "<dollars>Name<dollars>" looks like this:
  // <dollars><'Name'><colon><space><tag name><space><dollars>
  // Start reading at position 7, and read all but the last two positions.

  string result = RELEASE_TAG.substr(7,RELEASE_TAG.length()-9);

  if (result.empty())
  {
     // If there are no characters in the result, then we are dealing with the head.
     return "HEAD";
  }
  else
  {
    return result;
  }
}

bool
sheaf::
isunordered_or_equals(float x1, float x2)
{
  // Preconditions:

  // Body:

  // isunordered not available in Visual C++ 2008
  // != condition instead.
  //  bool result = std::isunordered(x1, x2) || (x1 == x2);

  bool result = (x1 != x1) || (x2 != x2) || (x1 == x2);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::
isunordered_or_equals(double x1, double x2)
{
  // Preconditions:

  // Body:

  // isunordered not available in Visual C++ 2008
  // != condition instead.
  //  bool result = std::isunordered(x1, x2) || (x1 == x2);

  bool result = (x1 != x1) || (x2 != x2) || (x1 == x2);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::
isunordered_or_equals(long double x1, long double x2)
{
  // Preconditions:

  // Body:

  // isunordered not available in Visual C++ 2008
  // != condition instead.
  //  bool result = std::isunordered(x1, x2) || (x1 == x2);

  bool result = (x1 != x1) || (x2 != x2) || (x1 == x2);

  // Postconditions:

  // Exit:

  return result;
}
