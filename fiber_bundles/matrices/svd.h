

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for svd.

#ifndef SVD_H
#define SVD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
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
