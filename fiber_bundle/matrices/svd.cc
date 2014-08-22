
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
/// Implementation for svd.


//$$TODO: See svd.h.

#include "svd.h"

#include "std_algorithm.h"
#include "std_cmath.h"
#include "std_iostream.h"

using namespace std;

// SVD-decomposition A = U*S*V', where U,V orthogonal and S diagonal.
// On completion A is replaced by U. Also, V and not V' (the transpose)
// is returned.
 
bool
fiber_bundle::
svd_decompose(double* xa, double* xw, double* xv, int nrows, int ncols)
{
  // Preconditions:

  // Body:

  // Return true on success; otherwise return false;
  //bool result = false;

  double* ltemp = new double[ncols];
  double lnorm;
  
  // Householder reduction to bidiagonal form.

  svd_reduce(xa, xw, xv, nrows, ncols, ltemp, lnorm);

  // Diagonalization of the bidiagonal form.

  svd_diagonalize(xa, xw, xv, nrows, ncols, ltemp, lnorm);

  delete [] ltemp;

  //============================================================================

//   // Sort the results into decending order.

//   for(int i=0; i<n-1; ++i)
//   {
//     double largest = xw[i];
//     int index = i;
//     for(int j=i+1; j<n; ++j)
//     {
//       if(xw[j] > largest) 
//       {
//         largest = xw[j];
//         index = j;
//       }            
//     }

//     if(index != i)  // Need to swap rows and columns.
//     {
//       swap_cols(xa, i, index);  // Swap columns in a.
//       swap_rows(xv, i, index);  // Swap rows in v.
//       swap (xw, i, index);        // Swap elements in w.
//     }
//   }

  //============================================================================

  // Postconditions:

  //ensure(???);

  // Exit:

  return true;
}

bool
fiber_bundle::
svd_reduce(double* xa, double* xw, double* xv, int nrows, int ncols,
           double* ltemp, double& lnorm)
{
  // Preconditions:

  // Body:

  // Householder reduction to bidiagonal form.

  lnorm = 0.0;

  double g = 0.0;
  double lscale = 0.0;

  int l;
  for(int i=0; i<ncols; ++i)
  {
    l = i+2; // l = i+1 ???
    ltemp[i] = lscale*g;

    g = 0.0;
    lscale = 0.0;

    double s = 0.0;

    if(i<nrows)
    {
      for(int k=i; k<nrows; ++k)
      {
        lscale += abs(xa[k*ncols+i]);
      }

      if(lscale != 0.0)
      {
        for(int k=i; k<nrows; ++k)
        {
          int ki = k*ncols+i;
          xa[ki] /= lscale;
          s += xa[ki]*xa[ki];
        }

        double f = xa[i*ncols+i];

        g = -same_sign(sqrt(s), f);
        double h = f*g-s;
        xa[i*ncols+i] = f-g;

        for(int j=l-1; j<ncols; ++j)
        {
          s = 0.0;
          for(int k=i; k<nrows; ++k)
          {
            s += xa[k*ncols+i] * xa[k*ncols+j];
          }

          f = s/h;

          for(int k=i; k<nrows; ++k)
          {
            xa[k*ncols+j] += f*xa[k*ncols+i];
          }
        }

        for(int k=i; k<nrows; ++k)
        {
          xa[k*ncols+i] *= lscale;
        }
      }
    }

    xw[i] = lscale*g;
    g = 0.0;
    s = 0.0;
    lscale = 0.0;

    if(((i+1)<=nrows) && ((i+1)!=ncols))
    {
      for(int k=l-1; k<ncols; ++k)
      {
        lscale += abs(xa[i*ncols+k]);
      }

      if(lscale != 0.0)
      {
        for(int k=l-1; k<ncols; ++k)
        {
          xa[i*ncols+k] /= lscale;
          s += xa[i*ncols+k]*xa[i*ncols+k];
        }

        double f = xa[i*ncols+l-1];
        g = -same_sign(sqrt(s),f);
        double h = f*g-s;
        xa[i*ncols+l-1] = f-g;

        for(int k=l-1; k<ncols; ++k)
        {
          ltemp[k] = xa[i*ncols+k]/h;
        }

        for(int j=l-1; j<nrows; ++j)
        {
          s = 0.0;
          for(int k=l-1; k<ncols; ++k)
          {
            s += xa[j*ncols+k]*xa[i*ncols+k];
          }

          for(int k=l-1; k<ncols; ++k)
          {
            xa[j*ncols+k] += s*ltemp[k];
          }
        }

        for(int k=l-1; k<ncols; ++k)
        {
          xa[i*ncols+k] *= lscale;
        }
      }
    }

    lnorm = max(lnorm, (abs(xw[i]) + abs(ltemp[i])));
  }

  // Accumulation of right-hand transformations.

  for(int i=ncols-1; i>=0; i--)
  {
    if(i<ncols-1)
    {
      if(g != 0.0)
      {
        for(int j=l; j<ncols; ++j)
        {
          xv[j*ncols+i] = (xa[i*ncols+j]/xa[i*ncols+l])/g;
        }

        for(int j=l; j<ncols; ++j)
        {
          double s = 0.0;
          for(int k=l; k<ncols; ++k)
          {
            s += xa[i*ncols+k]*xv[k*ncols+j];
          }

          for(int k=l; k<ncols; ++k)
          {
            xv[k*ncols+j] += s*xv[k*ncols+i];
          }
        }
      }

      for(int j=l; j<ncols; ++j)
      {
        xv[i*ncols+j] = xv[j*ncols+i] = 0.0;
      }
    }

    xv[i*ncols+i] = 1.0;
    g = ltemp[i];
    l = i;
  }

  // Accumulation of left-hand transformations.

  for(int i=min(nrows, ncols)-1; i>=0; i--)
  {
    l = i+1;
    g = xw[i];

    for(int j=l; j<ncols; ++j)
    {
      xa[i*ncols+j] = 0.0;
    }

    if(g != 0.0)
    {
      g = 1.0/g;

      for(int j=l; j<ncols; ++j)
      {
        double s = 0.0;
        for(int k=l; k<nrows; ++k)
        {
          s += xa[k*ncols+i]*xa[k*ncols+j];
        }

        double f = (s/xa[i*ncols+i])*g;

        for(int k=i; k<nrows; ++k)
        {
          xa[k*ncols+j] += f*xa[k*ncols+i];
        }
      }

      for(int j=i; j<nrows; ++j)
      {
        xa[j*ncols+i] *= g;
      }
    }

    else
    {
      for(int j=i; j<nrows; ++j)
      {
        xa[j*ncols+i] = 0.0;
      }
    }

    ++xa[i*ncols+i];
  }

  // Postconditions:

  //ensure(???);

  // Exit:

  return true;
}

bool
fiber_bundle::
svd_diagonalize(double* xa, double* xw, double* xv, int nrows, int ncols,
                double* ltemp, double lnorm)
{
  // Preconditions:

  // Body:

  // Diagonalization of the bidiagonal form.

  static const int MAX_ITERATIONS = 30;

  // Loop over singular values.

  for(int k=ncols-1; k>=0; k--)
  {
    //int nm;

    // Loop over allowed iterations.

    for(int iterations=0; iterations<MAX_ITERATIONS; ++iterations)
    {
      bool ltest = true;

      int l;
      int p;
      for(l=k; l>=0; l--)
      {
        p = l-1;

        if(abs(ltemp[l])+lnorm == lnorm)
        {
          ltest = false;
          break;
        }

        if(abs(xw[p])+lnorm == lnorm)
        {
          break;
        }
      }

      // Cancellation of ltemp[l] if l>0.

      if(ltest)
      {
        double c = 0.0;
        double s = 1.0;

        for(int i=l; i<k+1; ++i)
        {
          double f = s*ltemp[i];
          ltemp[i] = c*ltemp[i];

          if((abs(f) + lnorm) == lnorm)
          {
            break;
          }

          double g = xw[i];
          double h = svd_pythag(f, g);
          xw[i] = h;
          h = 1.0/h;

          c =  g*h;
          s = -f*h;

          for(int j=0; j<nrows; ++j)
          {
            int jp = j*ncols+p;
            int ji  = j*ncols+i;
            double y = xa[jp];
            double z = xa[ji];
            xa[jp] = y*c+z*s;
            xa[ji] = z*c-y*s;
          }
        }
      }

      double z = xw[k];

      // Convergence.

      // Make singular values nonnegative.

      if(l==k)
      {
        if(z<0.0)
        {
          xw[k] = -z;

          for(int j=0; j<ncols; ++j)
          {
            int jk = j*ncols+k;
            xv[jk] = -xv[jk];
          }
        }

        break;
      }

      if(iterations >= MAX_ITERATIONS)
      {
        //$$TODO: Use error_message here.
        cerr << "Error: No convergence in " << MAX_ITERATIONS
             << " svd iterations." << endl;
        return false;
      }

      // Shift from bottom 2-by-2 minor.

      int kk = k-1;

      double x = xw[l];
      double y = xw[kk];
      double g = ltemp[kk];
      double h = ltemp[k];

      double f = ((y-z)*(y+z) + (g-h)*(g+h))/(2.0*h*y);
      g = svd_pythag(f, 1.0);
      f = ((x-z)*(x+z)+h*((y/(f+same_sign(g,f)))-h))/x;

      // Next QR transformation.

      double lsin = 1.0;
      double lcos = 1.0;

      for(int j=l; j<=kk; ++j)
      {
        int i = j+1;

        g = ltemp[i];
        h = g*lsin;
        g = g*lcos;

        z = svd_pythag(f, h);
        ltemp[j] = z;

        lcos = f/z;
        lsin = h/z;

        f = x*lcos + g*lsin;
        g = g*lcos - x*lsin;

        y = xw[i];
        h = y*lsin;
        y = y*lcos;

        for(int n=0; n<ncols; ++n)
        {
          int ni = n*ncols+i;
          int nj = n*ncols+j;
          x = xv[nj];
          z = xv[ni];
          xv[nj] = x*lcos + z*lsin;
          xv[ni] = z*lcos - x*lsin;
        }

        z = svd_pythag(f, h);
        xw[j] = z;

        // Rotation can be arbitrary if z = 0;

        if(z != 0.0)
        {
          z = 1.0/z;
          lcos = f*z;
          lsin = h*z;
        }

        f = g*lcos + y*lsin;
        x = y*lcos - g*lsin;

        for(int m=0; m<nrows; ++m)
        {
          int mi = m*ncols+i;
          int mj = m*ncols+j;
          y = xa[mj];
          z = xa[mi];
          xa[mj] = y*lcos + z*lsin;
          xa[mi] = z*lcos - y*lsin;
        }
      }

      ltemp[l] = 0.0;
      ltemp[k] = f;
      xw[k] = x;
    }
  }

  // Postconditions:

  //ensure(???);

  // Exit:

  return true;
}

double
fiber_bundle::
same_sign(double xa, double xb)
{
  // Preconditions:

  // Body:

  double result;
  if(xb >= 0.0)
  {
    result = abs(xa);
  }
  else
  {
    result = -abs(xa);
  }

  // Postconditions:

  //ensure(???);

  // Exit:

  return result;
}

double
fiber_bundle::
svd_pythag(double xa, double xb)
{
  // Preconditions:

  // Body:

  double labs_a = abs(xa);
  double labs_b = abs(xb);

  double result;

  if(labs_a > labs_b)
  {
    double lratio = labs_b/labs_a;
    double lratio2 = lratio*lratio;
    result = labs_a*sqrt(1.0+lratio2);
  }
  else if(labs_b > 0.0)
  {
    double lratio = labs_a/labs_b;
    double lratio2 = lratio*lratio;
    result = labs_b*sqrt(1.0+lratio2);
  }
  else
  {
    result = 0.0;
  }

  // Postconditions:

  //ensure(???);

  // Exit:

  return result;
}
