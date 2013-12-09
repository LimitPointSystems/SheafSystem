
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

// Implementation for class stop_watch

#include "report.h"

#include "assert_contract.h"
#include "namespace_poset.h"
#include "std_fstream.h"
#include "std_iostream.h"
#include "std_iomanip.h"

using namespace std;

// ===========================================================
// ANY FACET
// ===========================================================

 

bool
sheaf::report::
invariant() const
{
  bool result = true;

  invariance(watch().invariant());
  invariance(watch().lap_ct() == names().ct());
  invariance(name_space() != 0 ? watch().lap_ct() == memory().ct() : true);

  // Exit

  return result;
}

// ===========================================================
// STOP_WATCH FACET
// ===========================================================

sheaf::report::
report()
{

  // Preconditions:

  // Body:

  _name_space = 0;
  reset();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::report::
report(const namespace_poset* xname_space)
{

  // Preconditions:

  require(xname_space != 0 ? xname_space->state_is_read_accessible() : true);

  // Body:

  _name_space = xname_space;
  reset();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::report::
~report()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::report::
start(const std::string& xtitle)
{
  // Preconditions:

  // Body:

  _title = xtitle;
  _watch.start();

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::report::
reset()
{
  // Preconditions:


  // Body:

  _title = "";
  _watch.reset();
  _names.clear();
  _memory.clear();
  for (int i=0; i<3; i++)
    _memory_parts[i].clear();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

void
sheaf::report::
point(const std::string& xname)
{
  // Preconditions:

  // Body:

  _watch.mark_lap();
  _names.push_back(xname);
  size_t lmemory_parts[4];
  
  if(_name_space != 0)
  {
    _memory.push_back(deep_size(*_name_space, true, lmemory_parts));
    for (int i=0; i<4; i++)
      _memory_parts[i].push_back(lmemory_parts[i]);
  }

  // Postconditions:

  ensure(invariant());
  
  // Exit:

  return;
}

void
sheaf::report::
write(const std::string& xfile_name) const
{
  // Preconditions:

  // Body:

  ofstream lofs(xfile_name.c_str());

  lofs << "Point,Time (sec),";
  if(_name_space != 0)
  {
    lofs << "Memory (bytes),";
    lofs << "Cover Relation Graph,";
    lofs << "ID Spaces,";
    lofs << "Subposets,";
    lofs << "DOF Tuples,";
  }
  lofs << endl;
  
  for(size_t i=0; i<_watch.lap_ct(); i++)
  {
    lofs << _names[i] << "," << _watch.lap_time(i) << ",";
    if(_name_space != 0)
    {
      lofs << _memory[i] << ",";
      lofs << _memory_parts[0][i] << ",";
      lofs << _memory_parts[1][i] << ",";
      lofs << _memory_parts[2][i] << ",";
      lofs << _memory_parts[3][i] << ",";
    }
    lofs << endl;
  }
  
  lofs << "Total," << _watch.cumulative_time() << ",";
  if(_name_space != 0)
  {
    size_t lmemory_parts[4];
    lofs << deep_size(*_name_space, true, lmemory_parts) << ",";
    lofs << lmemory_parts[0] << ",";
    lofs << lmemory_parts[1] << ",";
    lofs << lmemory_parts[2] << ",";
    lofs << lmemory_parts[3] << ",";
  }
  lofs << endl;

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

std::ostream &
sheaf::
operator << (std::ostream &xos, report& xreport)
{
  size_t lcol1 = 30;
  size_t lcol2 = 20;
  size_t lcol3 = 20;
  size_t lcol4 = 24;
  size_t lcol5 = 20;
  size_t lcol6 = 20;
  size_t lcol7 = 20;

  // Write report name.

  xos << "Report: " << xreport.title() << endl << endl;

  // Write table headers.

  xos << setw(lcol1) << "Point" << setw(lcol2) << "Time (sec)";
  if(xreport.name_space() != 0) 
  {
    xos << setw(lcol3) << "Memory (bytes)";
    xos << setw(lcol4) << "Cover Relation Graph";
    xos << setw(lcol5) << "ID Spaces";
    xos << setw(lcol6) << "Subposets";
    xos << setw(lcol7) << "DOF Tuples";
  }
  xos << endl;

  // Write header separator.

  size_t ltotal = lcol1 + lcol2;
  if(xreport.name_space() != 0)
    ltotal += lcol3 + lcol4 + lcol5 + lcol6 + lcol7;

  for(size_t i=0; i<ltotal; i++)
  {
    xos << "-";
  }
  xos << endl;

  // Write points.

  stop_watch lwatch = xreport.watch();

  for(size_t i=0; i<lwatch.lap_ct(); ++i)
  {
    xos << setw(lcol1) << xreport.names()[i]
	<< setw(lcol2) << lwatch.lap_time(i);

    if(xreport.name_space() != 0)
    {
      xos << setw(lcol3) << xreport.memory()[i];
      xos << setw(lcol4) << xreport.memory_part(0)[i];
      xos << setw(lcol5) << xreport.memory_part(1)[i];
      xos << setw(lcol6) << xreport.memory_part(2)[i];
      xos << setw(lcol7) << xreport.memory_part(3)[i];
    }
    xos << endl;
  }

  // Write total.

  xos << endl;
  xos << setw(lcol1) << "Total" << setw(lcol2) << lwatch.cumulative_time();
  if(xreport.name_space() != 0) 
  {
    size_t lmemory_parts[4];
    xos << setw(lcol3) << deep_size(*xreport.name_space(), true, lmemory_parts);
    xos << setw(lcol4) << lmemory_parts[0];
    xos << setw(lcol5) << lmemory_parts[1];
    xos << setw(lcol6) << lmemory_parts[2];
    xos << setw(lcol7) << lmemory_parts[3];
  }
  xos << endl;

  return xos;
}
