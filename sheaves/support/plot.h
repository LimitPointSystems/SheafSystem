// $RCSfile: plot.h,v $ $Revision: 1.12 $ $Date: 2013/01/12 17:17:46 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class plot

#ifndef PLOT_H
#define PLOT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
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
  ofstream* _data_file;

  ///
  /// The number of curves
  ///
  int _num_curves;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef STOP_WATCH_H
