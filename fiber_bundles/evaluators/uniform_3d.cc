
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class uniform_3d

#include "uniform_3d.h"
#include "assert_contract.h"
#include "std_limits.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// UNIFORM_3D FACET
// ===========================================================

///
fiber_bundle::uniform_3d::
uniform_3d()
{
  // Preconditions:

  // Body:

  _basis_values = _basis_value_buffer;
  _basis_deriv_values = _basis_deriv_value_buffer;
  _jacobian_values = _jacobian_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}


///
fiber_bundle::uniform_3d::
uniform_3d(const uniform_3d& xother)
{
  // Preconditions:

  // Body:

  _basis_values = _basis_value_buffer;
  _basis_deriv_values = _basis_deriv_value_buffer;
  _jacobian_values = _jacobian_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}


///
fiber_bundle::uniform_3d::
~uniform_3d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
int
fiber_bundle::uniform_3d::
dl() const
{
  int result;

  // Preconditions:


  // Body:

  result = DL;

  // Postconditions:

  ensure(result == 8);

  // Exit:

  return result;
}

///
void
fiber_bundle::uniform_3d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{

  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= 3);

  // Body:

  // Interpolate the field value at the global coordinates.

  dof_type u = xlocal_coord[0];
  dof_type v = xlocal_coord[1];
  dof_type w = xlocal_coord[2];

  _basis_values[0] = 0.125*(1.0 - u)*(1.0 - v)*(1.0 - w);
  _basis_values[1] = 0.125*(1.0 + u)*(1.0 - v)*(1.0 - w);
  _basis_values[2] = 0.125*(1.0 + u)*(1.0 + v)*(1.0 - w);
  _basis_values[3] = 0.125*(1.0 - u)*(1.0 + v)*(1.0 - w);

  _basis_values[4] = 0.125*(1.0 - u)*(1.0 - v)*(1.0 + w);
  _basis_values[5] = 0.125*(1.0 + u)*(1.0 - v)*(1.0 + w);
  _basis_values[6] = 0.125*(1.0 + u)*(1.0 + v)*(1.0 + w);
  _basis_values[7] = 0.125*(1.0 - u)*(1.0 + v)*(1.0 + w);

  // Postconditions:

  ensure(invariant());

}

///
void
fiber_bundle::uniform_3d::
basis_derivs_at_coord(const dof_type xlocal_coords[],
                      size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());
  require(basis_deriv_values() != 0);

  // Body:

  // Evaluate the derivatives of the interpolation functions.
  // The derivatives are interleaved (N,r[0], N,s[0], N,t[0],
  //  N,r[1], N,s[1], N,t[1], ...).

  double r = xlocal_coords[0];
  double s = xlocal_coords[1];
  double t = xlocal_coords[2];

  double rp = 1.0 + r;
  double rm = 1.0 - r;
  double sp = 1.0 + s;
  double sm = 1.0 - s;
  double tp = 1.0 + t;
  double tm = 1.0 - t;

  double rmxsm = rm * sm;
  double rpxsm = rp * sm;
  double rpxsp = rp * sp;
  double rmxsp = rm * sp;

  double rmxtm = rm * tm;
  double rpxtm = rp * tm;
  double rpxtp = rp * tp;
  double rmxtp = rm * tp;

  double smxtm = sm * tm;
  double spxtm = sp * tm;
  double spxtp = sp * tp;
  double smxtp = sm * tp;

  // Derivative with respect to r.

  _basis_deriv_value_buffer[ 0] = -smxtm;
  _basis_deriv_value_buffer[ 3] =  smxtm;
  _basis_deriv_value_buffer[ 6] =  spxtm;
  _basis_deriv_value_buffer[ 9] = -spxtm;
  _basis_deriv_value_buffer[12] = -smxtp;
  _basis_deriv_value_buffer[15] =  smxtp;
  _basis_deriv_value_buffer[18] =  spxtp;
  _basis_deriv_value_buffer[21] = -spxtp;

  // Derivative with respect to s.

  _basis_deriv_value_buffer[ 1] = -rmxtm;
  _basis_deriv_value_buffer[ 4] = -rpxtm;
  _basis_deriv_value_buffer[ 7] =  rpxtm;
  _basis_deriv_value_buffer[10] =  rmxtm;
  _basis_deriv_value_buffer[13] = -rmxtp;
  _basis_deriv_value_buffer[16] = -rpxtp;
  _basis_deriv_value_buffer[19] =  rpxtp;
  _basis_deriv_value_buffer[22] =  rmxtp;

  // Derivative with respect to t.

  _basis_deriv_value_buffer[ 2] = -rmxsm;
  _basis_deriv_value_buffer[ 5] = -rpxsm;
  _basis_deriv_value_buffer[ 8] = -rpxsp;
  _basis_deriv_value_buffer[11] = -rmxsp;
  _basis_deriv_value_buffer[14] =  rmxsm;
  _basis_deriv_value_buffer[17] =  rpxsm;
  _basis_deriv_value_buffer[20] =  rpxsp;
  _basis_deriv_value_buffer[23] =  rmxsp;

  for(int i=0; i<24; i++)
  {
    _basis_deriv_value_buffer[i] *= 0.125;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// ===========================================================
// INTEGRABLE_SECTION_EVALUATOR FACET
// ===========================================================

///
fiber_bundle::section_evaluator::value_type
fiber_bundle::uniform_3d::
jacobian_determinant(const dof_type xcoord_dofs[],
                     size_type xcoord_dofs_ub,
                     size_type xdf,
                     const coord_type xlocal_coords[],
                     size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= db()*dl());
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());
  //require(jacobian_values() != 0);

  // Body:

  not_implemented();

  ///@todo Implement.

  value_type result = 0.0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
fiber_bundle::section_evaluator::value_type
fiber_bundle::uniform_3d::
volume(const dof_type xcoord_dofs[], size_type xcoord_dofs_ub, size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xdf == 2 || xdf == 2 || xdf == 3);

  // Body:

  ///@todo Implement.

  not_implemented();

  value_type result = 0.0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}


///
void
fiber_bundle::uniform_3d::
integrate(const dof_type xcoord_dofs[],
          size_type xcoord_dofs_ub,
          size_type xdf,
          const dof_type xintegrands[],
          size_type xintegrands_ub,
          value_type xresult_integrals[],
          size_type xresult_integrals_ub)
{
  ///@todo Get these correct.

  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xintegrands != 0);
  require(xintegrands_ub >= dl());
  require(xresult_integrals != 0);
  require(xresult_integrals_ub > 0);

  // Body:

  not_implemented();

  ///@todo Implement.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::uniform_3d::
integrate(const dof_type xcoord_dofs[],
          size_type xcoord_dofs_ub,
          size_type xdf,
          const dof_type xintegrand,
          value_type xresult_integrals[],
          size_type xresult_integrals_ub)
{
  ///@todo Get these correct.

  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xresult_integrals != 0);
  require(xresult_integrals_ub >= dl());

  // Body:

  not_implemented();

  ///@todo Implement.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::uniform_3d::
gauss_point(pod_index_type xindex,
            coord_type xresult[],
            size_type xresult_ub)
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  not_implemented();

  ///@todo Implement.

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));
  ensure(invariant());

  // Exit:

  return;
}

// ===========================================================
// DIFFERENTIABLE_SECTION_EVALUATOR FACET
// ===========================================================

///
void
fiber_bundle::uniform_3d::
dxi_local(size_type xlocal_coord_index,
          const dof_type xsource_dofs[],
          size_type xsource_dofs_ub,
          dof_type xresult_dofs[],
          size_type xresult_dofs_ub) const
{
  // Preconditions:

  require(xlocal_coord_index < db());
  require(xsource_dofs != 0);
  require(xsource_dofs_ub >= 24);
  require(xresult_dofs != 0);
  //require(xresult_dofs_ub >= dof_ct());

  // Body:

  ///@todo implement.

  not_implemented();

  //   if(xlocal_coord_index == 0)
  //   {
  //     dof_type d_minus = 0.5 * (xsource_dofs[1] - xsource_dofs[0]);
  //     dof_type d_plus =  0.5 * (xsource_dofs[2] - xsource_dofs[3]);

  //     xresult_dofs[0] = d_minus;
  //     xresult_dofs[1] = d_minus;

  //     xresult_dofs[2] = d_plus;
  //     xresult_dofs[3] = d_plus;
  //   }
  //   else if(xlocal_coord_index == 1)
  //   {
  //     dof_type d_minus = 0.5 * (xsource_dofs[3] - xsource_dofs[0]);
  //     dof_type d_plus =  0.5 * (xsource_dofs[2] - xsource_dofs[1]);

  //     xresult_dofs[0] = d_minus;
  //     xresult_dofs[3] = d_minus;

  //     xresult_dofs[1] = d_plus;
  //     xresult_dofs[2] = d_plus;
  //   }
  //   else
  //   {
  //     dof_type d_minus = 0.5 * (xsource_dofs[3] - xsource_dofs[0]);
  //     dof_type d_plus =  0.5 * (xsource_dofs[2] - xsource_dofs[1]);

  //     xresult_dofs[0] = d_minus;
  //     xresult_dofs[3] = d_minus;

  //     xresult_dofs[1] = d_plus;
  //     xresult_dofs[2] = d_plus;
  //   }


  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::uniform_3d::
jacobian(const dof_type xcoord_dofs[],
         size_type xcoord_dofs_ub,
         size_type xdf,
         const dof_type xlocal_coords[],
         size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= db()*dl());
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());
  require(jacobian_values() != 0);

  // Body:

  not_implemented();

  ///@todo Implement.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// ===========================================================
// DOMAIN FACET
// ===========================================================

///
int
fiber_bundle::uniform_3d::
db() const
{
  int result;

  // Preconditions:


  // Body:

  result = 3;

  // Postconditions:

  ensure(result == 3);

  // Exit:

  return result;
}


///
void
fiber_bundle::uniform_3d::
local_coordinates(pod_index_type xindex,
                  coord_type xresult[],
                  size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[8][3] =
    {
      {
        -1.0, -1.0, -1.0
      },
      { 1.0, -1.0, -1.0},
      { 1.0,  1.0, -1.0},
      {-1.0,  1.0, -1.0},
      {-1.0, -1.0,  1.0},
      { 1.0, -1.0,  1.0},
      { 1.0,  1.0,  1.0},
      {-1.0,  1.0,  1.0}
    } ;

  xresult[0] = lcoords[xindex][0];
  xresult[1] = lcoords[xindex][1];
  xresult[2] = lcoords[xindex][2];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
bool
fiber_bundle::uniform_3d::
in_standard_domain(const dof_type xlocal_coords[],
                   size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 3);

  // Body:

  dof_type u = xlocal_coords[0];
  dof_type v = xlocal_coords[1];
  dof_type w = xlocal_coords[2];

  // "Extend" the bounds by the dof type epsilon (attempting
  // to ensure that the boundary is included in the domain).

  dof_type one = 1.0 + 1000.0*numeric_limits<dof_type>::epsilon();

  bool result =
    (u >= -one) && (u <= one) &&
    (v >= -one) && (v <= one) &&
    (w >= -one) && (w <= one);

  // Postconditions:

  // Exit:

  return result;

}

// ===========================================================
// EVALUATION FACET
// ===========================================================

///
void
fiber_bundle::uniform_3d::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= 24);
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= 3);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 3);

  // Body:

  // The dofs are assumed to be interleaved (x0, y0, z0, x1, y1, z0, ...).

  dof_type x0 = xdofs[0];
  dof_type y0 = xdofs[1];
  dof_type z0 = xdofs[2];

  //   dof_type x1 = xdofs[3];
  //   dof_type y1 = xdofs[4];
  //   dof_type z1 = xdofs[5];

  //   dof_type x2 = xdofs[6];
  //   dof_type y2 = xdofs[7];
  //   dof_type z2 = xdofs[8];

  //   dof_type x3 = xdofs[9];
  //   dof_type y3 = xdofs[10];
  //   dof_type z3 = xdofs[11];

  //   dof_type x4 = xdofs[12];
  //   dof_type y4 = xdofs[13];
  //   dof_type z4 = xdofs[14];

  //   dof_type x5 = xdofs[15];
  //   dof_type y5 = xdofs[16];
  //   dof_type z5 = xdofs[17];

  dof_type x6 = xdofs[18];
  dof_type y6 = xdofs[19];
  dof_type z6 = xdofs[20];

  //   dof_type x7 = xdofs[21];
  //   dof_type y7 = xdofs[22];
  //   dof_type z7 = xdofs[23];

  dof_type x_global = xglobal_coords[0];
  dof_type y_global = xglobal_coords[1];
  dof_type z_global = xglobal_coords[2];

  // Solve for u.

  double xlength = x6 - x0;

  xlocal_coords[0] = (2.0*x_global - (x0 + x6)) / xlength;

  // Solve for v.

  double ylength = y6 - y0;

  xlocal_coords[1] = (2.0*y_global - (y0 + y6)) / ylength;

  // Solve for v.

  double zlength = z6 - z0;

  xlocal_coords[2] = (2.0*z_global - (z0 + z6)) / zlength;

  // Postconditions:

  ensure(invariant());

}

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::uniform_3d*
fiber_bundle::uniform_3d::
clone() const
{
  uniform_3d* result;

  // Preconditions:

  // Body:

  result = new uniform_3d();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}


///
fiber_bundle::uniform_3d&
fiber_bundle::uniform_3d::
operator=(const section_evaluator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return *this;
}

///
fiber_bundle::uniform_3d&
fiber_bundle::uniform_3d::
operator=(const uniform_3d& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

///
bool
fiber_bundle::uniform_3d::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && linear_fcn_space::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance(basis_values() != 0);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  return result;
}

///
bool
fiber_bundle::uniform_3d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const uniform_3d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================




