
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

// Interface for class plot

#ifndef COM_LIMITPOINT_SHEAF_PLOT_H
#define COM_LIMITPOINT_SHEAF_PLOT_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef STD_FSTREAM_H
#include "std_fstream.h"
#endif

namespace sheaf
{
  
///
/// A class for constructing files to be read by gnuplot.
///
class SHEAF_DLL_SPEC plot
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
  // PLOT FACET
  // ===========================================================

  ///
  /// Type of curve to fit.
  ///
  enum plot_type
  {
    QUADRATIC,
    LINEAR,
    CONSTANT
  };   

  ///
  /// Constructor
  ///
  plot(const char* xdriver,
       const char** xcurve_labels,
       int xnum_curves = 1,
       const char* xxlabel = "",
       const char* xylabel = "",
       const plot_type* xtypes = 0);

  // Default memberwise copy constructor

  ///
  /// Destructor
  ///
  virtual ~plot();

  ///
  /// An empty array for point data
  ///
  double* create_point();

  ///
  /// Add a data point
  ///
  void add_point(double* xpoint);

private:

  ///
  /// The data file stream
  ///
  std::ofstream* _data_file;

  ///
  /// The number of curves
  ///
  int _num_curves;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_STOP_WATCH_H
