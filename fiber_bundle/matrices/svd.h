
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

/// @file
/// Interface for svd.

#ifndef SVD_H
#define SVD_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

//$$TODO: 1. Make this a class.
//        2. Use matrices for arguments.

namespace  fiber_bundle
{

  //public:

///
/// Perform single value decomposition.
///
SHEAF_DLL_SPEC bool svd_decompose(double* xa, double* xs, double* xv,
                                  int xnrows, int xncols);

// SHEAF_DLL_SPEC bool svd_decompose(vector<e3_lite>& xa, e3_lite& xs, vector<e3_lite>& xv,
//                                   int xnrows);

  //private:

///
/// Householder reduction to bidiagonal form.
/// Convenience function.
///
SHEAF_DLL_SPEC bool svd_reduce(double* xa, double* xw, double* xv,
                               int nrows, int ncols,
                               double* ltemp, double& lnorm);

///
/// Diagonalization of the bidiagonal form.
/// Convenience function.
///
SHEAF_DLL_SPEC bool svd_diagonalize(double* xa, double* xw, double* xv,
                                    int nrows, int ncols,
                                    double* xtemp, double lnorm);

///
/// Convert xa to have the same sign as xb.
///
SHEAF_DLL_SPEC double same_sign(double xa, double xb);

///
/// Pthagorean theorem calculation. 
///
SHEAF_DLL_SPEC double svd_pythag(double xa, double xb);


} // end namespace  fiber_bundle

#endif // ifndef SVD_H
