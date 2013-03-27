// $RCSfile: stop_watch.h,v $ $Revision: 1.11 $ $Date: 2013/01/12 17:17:47 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class stop_watch

#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_CTIME_H
#include "std_ctime.h"
#endif

#ifndef STD_VECTOR_H
#include "std_vector.h"
#endif

namespace sheaf
{
  
///
/// A clock for timing intervals.
///
class SHEAF_DLL_SPEC stop_watch
{

public:

  // ===========================================================
  // ANY FACET
  // ===========================================================

  // Default memberwise assignment operator

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;
  

  // ===========================================================
  // STOP_WATCH FACET
  // ===========================================================

  ///
  /// Default constructor
  ///
  ///
  stop_watch();

  // Default memberwise copy constructor

  ///
  /// Destructor
  ///
  virtual ~stop_watch();

  ///
  /// The unit of time to return.
  ///
  enum time_unit
  {
    CPU_TIME,
    MILLISECONDS,
    SECONDS
  };

  ///
  /// Marks the start of an interval.
  ///
  void start();

  ///
  /// Marks the end of an interval.
  ///
  void stop();

  ///
  /// The length of the current interval.
  ///
  double time(time_unit xunit = SECONDS) const;

  ///
  /// The accumulated time in seconds between start()'s
  /// and stop()'s since the last reset().
  ///
  double cumulative_time() const;

  ///
  /// Marks the end of the current lap.
  ///
  void mark_lap();

  ///
  /// The length in seconds of the xi-th lap.
  ///
  double lap_time(int i) const;

  ///
  /// The number of laps that have be marked.
  ///
  size_t lap_ct() const;

  ///
  /// Clears the lap times and sets lap_ct() to 0.
  ///
  void reset();


private:

  ///
  /// The start time for the current interval.
  ///
  clock_t _start_time;

  ///
  /// The stop time for the current interval.
  ///
  clock_t _stop_time;

  ///
  /// The accumulated time in seconds between start()'s
  /// and stop()'s since the last reset().
  ///
  double _cumulative_time;

  ///
  /// The lap times.
  ///
  vector<double> _lap_times;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts lap times for stop_watch xsw into ostream xos.
///
SHEAF_DLL_SPEC
ostream & operator << (ostream &os, stop_watch& xsw);
 
} // namespace sheaf

#endif // ifndef STOP_WATCH_H
