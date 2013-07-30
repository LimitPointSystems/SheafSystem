
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

 

// Implementation for class stop_watch

#include "stop_watch.h"

#include "assert_contract.h"
#include "std_iostream.h"

// ===========================================================
// ANY FACET
// ===========================================================

 

bool
sheaf::stop_watch::
invariant() const
{
  bool result = true;

  invariance(_start_time <= _stop_time);

  // Exit

  return result;
}

// ===========================================================
// STOP_WATCH FACET
// ===========================================================

sheaf::stop_watch::
stop_watch()
{

  // Preconditions:

  // Body:

  reset();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::stop_watch::
~stop_watch()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::stop_watch::
start()
{
  // Preconditions:

  // Body:

  _start_time = clock();

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::stop_watch::
stop()
{
  // Preconditions:

  // Body:

  _stop_time = clock();

  _cumulative_time += time();

  // Postconditions:

  // Exit:

  return;
}

double
sheaf::stop_watch::
time(time_unit xunit) const
{
  double result;

  // Preconditions:

  // Body:

  double ldiff = (double) (_stop_time - _start_time);

  switch(xunit)
  {
    case CPU_TIME:
      result = ldiff;
      break;
      
    case MILLISECONDS:
      result = (ldiff / CLOCKS_PER_SEC) * 1000.0;
      break;
      
    default:
      result = ldiff / CLOCKS_PER_SEC;
      break;
  }

  // Postconditions:


  // Exit:

  return result;
}

///
double
sheaf::stop_watch::
cumulative_time() const
{
  // Preconditions:


  // Body:

  // Postconditions:


  // Exit:

  return _cumulative_time;
}


///
void
sheaf::stop_watch::
mark_lap()
{
  // Preconditions:

  // Body:

  stop();
  _lap_times.push_back(time());
  _start_time = _stop_time;

  // Postconditions:


  // Exit:

  return;
}

///
double
sheaf::stop_watch::
lap_time(int xi) const
{
  double result;

  // Preconditions:

  require((0 <= xi) && (xi <= lap_ct()));

  // Body:

  result = _lap_times[xi];

  // Postconditions:


  // Exit:

  return result;
}


///
size_t
sheaf::stop_watch::
lap_ct() const
{
  size_t result;

  // Preconditions:


  // Body:

  result = _lap_times.size();

  // Postconditions:

  // Exit:

  return result;
}

///
void
sheaf::stop_watch::
reset()
{
  // Preconditions:


  // Body:

  _start_time = 0;
  _stop_time = 0;
  _cumulative_time = 0;
  _lap_times.clear();

  // Postconditions:

  ensure(time() == 0);
  ensure(lap_ct() == 0);

  // Exit:

  return;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

///
ostream & sheaf::operator << (ostream &xos, stop_watch& xsw)
{
  xos << " lap times: ";

  for(size_t i=0; i<xsw.lap_ct(); ++i)
  {
    xos << " " << xsw.lap_time(i);
    if((i % 10 == 9) || (i == (xsw.lap_ct() - 1)))
    {
      xos << endl;
    }
  }

  return xos;
}
