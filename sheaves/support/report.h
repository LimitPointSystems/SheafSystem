
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

// Interface for class report

#ifndef REPORT_H
#define REPORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef STOP_WATCH_H
#include "stop_watch.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
  
class namespace_poset;

///
/// A report generating class.
///
class SHEAF_DLL_SPEC report
{

public:

  // ===========================================================
  // ANY FACET
  // ===========================================================

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  // ===========================================================
  // REPORT FACET
  // ===========================================================

  ///
  /// Default constructor
  ///
  report();  

  ///
  /// Namespace constructor
  ///
  report(const namespace_poset* xname_space);

  ///
  /// Destructor
  ///
  virtual ~report();

  ///
  /// Starts a new report with title, xtitle.
  ///
  void start(const string& xname);

  ///
  /// Reset the report.
  ///
  void reset();

  ///
  /// Mark a point named, xname, in the report.
  ///
  void point(const string& xname);

  ///
  /// Write the report to a comma separated value file.
  ///
  void write(const string& xfile_name) const;  

  ///
  /// Namespace for the report.
  ///
  inline const namespace_poset* name_space() const
  {
    return _name_space;
  };

  ///
  /// Title of the report.
  ///
  inline string title() const
  {
    return _title;
  };

  ///
  /// Stop watch used to time the report points.
  ///
  inline stop_watch watch() const
  {
    return _watch;
  };
  
  ///
  /// Names of the report points.
  ///
  inline block<string> names() const
  {
    return _names;
  };

  ///
  /// Deep size of the namespace poset for each point.
  ///
  inline block<size_t> memory() const
  {
    return _memory;
  }
  
  ///
  /// Deep size of the namespace for each component for each point.
  ///
  inline block<size_t> memory_part(int lpart) const
  {
    return _memory_parts[lpart];
  }

private:

  ///
  /// Namespace for the report.
  ///
  const namespace_poset* _name_space;

  ///
  /// Title of the report.
  ///
  string _title;

  ///
  /// Stop watch used to time the report points.
  ///
  stop_watch _watch;

  ///
  /// Names of the report points.
  ///
  block<string> _names;

  ///
  /// Deep size of the namespace for each point.
  ///
  block<size_t> _memory;

  ///
  /// Deep size of the namespace for each component for each point.
  ///
  block<size_t> _memory_parts[4];

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts the report xreport into ostream xos.
///
SHEAF_DLL_SPEC
ostream & operator << (ostream &os, report& xreport);
 
} // namespace sheaf

#endif // ifndef STOP_WATCH_H
