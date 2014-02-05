
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

// Implementation for class plot

#include "plot.h"

#include "assert_contract.h"
#include "std_iostream.h"
#include "std_sstream.h"
#include "std_string.h"

using namespace std;

// ===========================================================
// ANY FACET
// ===========================================================

 

///
bool
sheaf::plot::
invariant() const
{
  bool result = true;

  // Exit

  return result;
}



// ===========================================================
// PLOT FACET
// ===========================================================

///
sheaf::plot::
plot(const char* xdriver,
     const char** xcurve_labels,
     int xnum_curves,
     const char* xxlabel,
     const char* xylabel,
     const plot_type* xtypes)
{

  // Preconditions:

  require(xnum_curves > 0);
  require(unexecutable("length of xcurve_labels == xnum_curves"));
  require(unexecutable("xtypes == 0 || size of xtypes == xnum_curves"));

  // Body:

  // Set the class variables

  _num_curves = xnum_curves;

  // Determine the plot types.  If no input types are given, treat all
  // plot types as quadratic.

  bool lhas_quadratic = false;
  plot_type* ltypes = new plot_type[_num_curves];
  for(int i = 0; i < _num_curves; i++)
  {
    if(xtypes == 0)
    {
      ltypes[i] = QUADRATIC;
      lhas_quadratic = true;
    }
    else
    {
      ltypes[i] = xtypes[i];
      if(ltypes[i] == QUADRATIC)
	lhas_quadratic = true;
    }
  }

  // Write file.

  stringstream ldata_file_name_stream;
  ldata_file_name_stream << xdriver << ".dat";

  string ldata_file_name;
  ldata_file_name_stream >> ldata_file_name;

  _data_file = new ofstream(ldata_file_name.c_str());

  // Create the gnuplot file

  stringstream lplot_file_name_stream;
  lplot_file_name_stream << xdriver << ".gnu";

  string lplot_file_name;
  lplot_file_name_stream >> lplot_file_name;

  ofstream lplot_file(lplot_file_name.c_str());

  lplot_file << "set xlabel \"" << xxlabel << "\"" << endl;
  lplot_file << "set ylabel \"" << xylabel << "\"" << endl;
  lplot_file << "set key bottom horizontal outside box" << endl;
  lplot_file << "set title \"" << xdriver << "\"" << endl;
  lplot_file << "FIT_LIMIT = 1e-6" << endl << endl;

  // Create the functions

  lplot_file << "set fit logfile \"" << xdriver
  << ".fit\" noerrorvariables" << endl;

  for(int i = 0; i < _num_curves; i++)
  {
    switch(ltypes[i])
    {
      case QUADRATIC:
	lplot_file << "f" << i << "(x) = a" << i << "*x**2 + b"
		   << i << "*x + c" << i << endl;

	lplot_file << "fit f" << i << "(x) \"" << ldata_file_name
		   << "\" using 1:" << i+2 << " via a" << i << ", b" << i
		   << ", c" << i << endl;
	break;

      case LINEAR:
	lplot_file << "f" << i << "(x) = a" << i << "*x + b" << i << endl;

	lplot_file << "fit f" << i << "(x) \"" << ldata_file_name
		   << "\" using 1:" << i+2 << " via a" << i << ", b" << i << endl;
	break;

      case CONSTANT:
	lplot_file << "f" << i << "(x) = a" << i << endl;

	lplot_file << "fit f" << i << "(x) \"" << ldata_file_name
		   << "\" using 1:" << i+2 << " via a" << i << endl;
	break;
    }
  }

  // Plot the data

  lplot_file << endl << "plot ";

  for(int i = 0; i < _num_curves; i++)
  {
    lplot_file << "\"" << ldata_file_name << "\" u 1:" << i+2
	       << " t \"" << xcurve_labels[i] << "\" with points, f"
	       << i << "(x)";

    if(i+1 < _num_curves)
      lplot_file << ", ";
  }

  lplot_file << endl << endl;

  // Save image

  lplot_file << "set terminal png size 800,600" << endl;
  lplot_file << "set output \"" << xdriver << ".png\"" << endl;
  lplot_file << "replot" << endl << endl;

  // Save pdf

  lplot_file << "set terminal pdf" << endl;
  lplot_file << "set output \"" << xdriver << ".pdf\"" << endl;
  lplot_file << "replot" << endl << endl;

  // Save report html file

  lplot_file << "set print \"" << xdriver << ".html\"" << endl;
  lplot_file << "print \"<html><title>" << xdriver << "</title><body>\"" << endl;
  lplot_file << "print \"<img src=\\\"" << xdriver << ".png\\\""
	     << ">\"" << endl;
  lplot_file << "print \"<br><br>\"" << endl << endl;

  for(int i = 0; i < _num_curves; i++)
  {
    switch(ltypes[i])
    {
      case QUADRATIC:
	lplot_file << "if(a" << i
		   << ">1e-6) print \"<font size=-1 color=red>\"; else "
		   << "print \"<font size=-1>\"" << endl;

	lplot_file << "print \"f" << i << "(x) = (\", a" << i
		   << ", \")*x^2 + (\", b" << i << ", \")*x + (\", c"
		   << i << ", \")<br></font>\"" << endl << endl;

	break;

      case LINEAR:
	lplot_file << "print \"<font size=-1>\"" << endl;

	lplot_file << "print \"f" << i << "(x) = (\", a"
		   << i << ", \")*x + (\", b"
		   << i << ", \")<br></font>\"" << endl << endl;

	break;

      case CONSTANT:
	lplot_file << "print \"<font size=-1>\"" << endl;

	lplot_file << "print \"f" << i << "(x) = (\", a"
		   << i << ", \")<br></font>\"" << endl << endl;

	break;
    }
  }

  lplot_file << "print \"</body></html>\"" << endl << endl;

  // Test for quadratic behavior

  if(lhas_quadratic)
  {
    lplot_file << "set print" << endl;
    lplot_file << "if(";
    for(int i = 0; i < _num_curves; i++)
    {
      if(ltypes[i] == QUADRATIC)
      {
	lplot_file << "a" << i << ">1e-6";

	if(i+1 < _num_curves)
	  lplot_file << " || ";
      }
    }
    
    lplot_file << ") print \"\\nWARNING: Quadratic behavior!\"" << endl;
  }

  // Clean up.

  delete [] ltypes;
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
sheaf::plot::
~plot()
{

  // Preconditions:


  // Body:

  delete _data_file;

  // Postconditions:

  // Exit:

  return;
}

///
double*
sheaf::plot::
create_point()
{
  // Preconditions:

  // Body:

  double* result = new double[_num_curves+1];

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable("length of result == _num_curves+1"));

  // Exit:

  return result;
}

///
void
sheaf::plot::
add_point(double* xpoint)
{
  // Preconditions:

  require(unexecutable("length of xpoint == _num_curves+1"));

  // Body:

  for(int i = 0; i < _num_curves+1; i++)
  {
    *_data_file << xpoint[i] << " ";
  }

  *_data_file << endl;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

