// $RCSfile: section_evaluator.cc,v $ $Revision: 1.40 $ $Date: 2013/03/20 21:56:05 $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class section_evaluator

#include "section_evaluator.h"

#include "assert_contract.h"
#include "block.h"
#include "sec_vd.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SECTION_EVALUATOR FACET
// ===========================================================

///
fiber_bundle::section_evaluator::
section_evaluator(const section_evaluator& xother)
{
  // Preconditions:

  // Body:

  // No action required.

  // Postconditions:

  ensure(invariant());

  return;
}

///
fiber_bundle::section_evaluator::
~section_evaluator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

///
fiber_bundle::section_evaluator::
section_evaluator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

// ===========================================================
// DOMAIN FACET
// ===========================================================

///
int
fiber_bundle::section_evaluator::
db() const
{
  int result = -1;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result >= -1);

  // Exit:

  return result;
}


///
void
fiber_bundle::section_evaluator::
local_coordinates(pod_index_type xindex,
                  coord_type xresult[],
                  size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}


///
void
fiber_bundle::section_evaluator::
local_coordinates(pod_index_type xindex, block<coord_type>& xresult) const
{
  // Preconditions:

  require(precondition_of(local_coordinates(xindex, xresult.base(), xresult.ub())));

  // Body:

  local_coordinates(xindex, xresult.base(), xresult.ub());
  xresult.set_ct(db());

  // Postconditions:

  ensure(postcondition_of(local_coordinates(xindex, xresult.base(), xresult.ub())));
  ensure(xresult.ct() == db());

  // Exit:

  return;
}

///
void
fiber_bundle::section_evaluator::
center(coord_type xresult[], size_type xresult_ub) const
{
  // Preconditions:

  require(xresult != 0);
  require(xresult_ub >= db());

  // Body:

  // The following implementation is correct for the box-like base spaces,
  // but not for the simplex base space. It must be overridden in those classes.

  for(size_type i=0; i<db(); ++i)
  {
    xresult[i] = 0.0;
  }

  // Postconditions:


  // Exit:

  return;
}

///
void
fiber_bundle::section_evaluator::
center(block<coord_type>& xresult) const
{
  // Preconditions:

  require(precondition_of(center(xresult.base(), xresult.ub())));

  // Body:

  center(xresult.base(), xresult.ub());
  xresult.set_ct(db());

  // Postconditions:

  ensure(postcondition_of(center(xresult.base(), xresult.ub())));
  ensure(xresult.ct() == db());

  // Exit:

  return;
}

///
bool
fiber_bundle::section_evaluator::
in_standard_domain(const dof_type xlocal_coords[],
		   size_type xlocal_coords_ub) const
{
  bool result = true;

  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());

  return result;
}

///
bool
fiber_bundle::section_evaluator::
in_standard_domain(const block<dof_type>& xlocal_coords) const
{
  bool result;

  // Preconditions:

  require(precondition_of(in_standard_domain(xlocal_coords.base(), xlocal_coords.ct())));

  // Body:

  result = in_standard_domain(xlocal_coords.base(), xlocal_coords.ct());

  // Postconditions:

  ensure(postcondition_of(in_standard_domain(xlocal_coords.base(), xlocal_coords.ct())));

  // Exit:

  return result;
}

// ===========================================================
// EVALUATION FACET
// ===========================================================

///
sheaf::size_type
fiber_bundle::section_evaluator::
dof_ct() const
{
  int result = 0;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

bool
fiber_bundle::section_evaluator::
df_is_variable() const
{
  // Preconditions:


  // Body:

  bool result = (df() == 0);

  // Postconditions:

  ensure(result == (df() == 0));

  // Exit:

  return result;
}

int
fiber_bundle::section_evaluator::
df() const
{
  // Preconditions:


  // Body:


  // Assume the fiber dimension is variable;
  // redefine in descendants with fixed fiber dimension.

  int result = 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

///
fiber_bundle::sec_vd_dof_type
fiber_bundle::section_evaluator::
value_at_coord(const block<dof_type>& xdofs,
               const block<dof_type>& xlocal_coords) const
{
  dof_type result;

  // Preconditions:

  require(df_is_variable());
  require(precondition_of(value_at_coord(xdofs.base(), xdofs.ct(), xlocal_coords.base(), xlocal_coords.ct());));

  // Body:

  result = value_at_coord(xdofs.base(),
                          xdofs.ct(),
                          xlocal_coords.base(),
                          xlocal_coords.ct());

  // Postconditions:

  ensure(postcondition_of(value_at_coord(xdofs.base(), xdofs.ct(), xlocal_coords.base(), xlocal_coords.ct());));

  // Exit:

  return result;
}

///
fiber_bundle::section_evaluator::dof_type
fiber_bundle::section_evaluator::
value_at_coord(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(df_is_variable());
  require(xdofs != 0);
  require(xdofs_ub >= dof_ct());
  require(unexecutable(xdofs must be interleaved));
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  dof_type result;
  value_at_coord(xdofs, xdofs_ub, xlocal_coords, xlocal_coords_ub, &result, 1);

  // Postconditions:

  ensure(invariant());

  return result;

}

///
void
fiber_bundle::section_evaluator::
value_at_coord(const block<dof_type>& xdofs,
               const block<dof_type>& xlocal_coords,
               block<dof_type>& xresult) const
{
  // Preconditions:

  require(precondition_of(value_at_coord(xdofs.base(),
                                         xdofs.ct(),
                                         xlocal_coords.base(),
                                         xlocal_coords.ct(),
                                         xresult.base(),
                                         xresult.ct());));

  // Body:

  value_at_coord(xdofs.base(),
                 xdofs.ct(),
                 xlocal_coords.base(),
                 xlocal_coords.ct(),
                 xresult.base(),
                 xresult.ct());

  // Postconditions:

  ensure(postcondition_of(value_at_coord(xdofs.base(),
                                         xdofs.ct(),
                                         xlocal_coords.base(),
                                         xlocal_coords.ct(),
                                         xresult.base(),
                                         xresult.ct());));

  // Exit:

  return;
}

void
fiber_bundle::section_evaluator::
coord_at_value(const dof_type xdofs[],
	       size_type xdofs_ub,
	       const dof_type xvalue[],
	       size_type xvalue_ub,
	       dof_type xlocal_coords[],
	       size_type xlocal_coords_ub) const
{
  // Preconditions:

  /// @todo Add preconditions.

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());
}

///
void
fiber_bundle::section_evaluator::
coord_at_value(const block<dof_type>& xdofs,
               const block<dof_type>& xvalue,
               block<dof_type>& xlocal_coords) const
{
  // Preconditions:

  require(precondition_of(coord_at_value(xdofs.base(),
                                         xdofs.ct(),
                                         xvalue.base(),
                                         xvalue.ct(),
                                         xlocal_coords.base(),
                                         xlocal_coords.ub())));

  // Body:

  coord_at_value(xdofs.base(),
                 xdofs.ct(),
                 xvalue.base(),
                 xvalue.ct(),
                 xlocal_coords.base(),
                 xlocal_coords.ub());

  xlocal_coords.set_ct(db());


  // Postconditions:

  ensure(postcondition_of(coord_at_value(xdofs.base(),
                                         xdofs.ct(),
                                         xvalue.base(),
                                         xvalue.ub(),
                                         xlocal_coords.base(),
                                         xlocal_coords.ub())));
  ensure(xlocal_coords.ct() == db());

  // Exit:

  return;
}

///
fiber_bundle::section_evaluator::dof_type
fiber_bundle::section_evaluator::
min(const dof_type xdofs[], size_type xdofs_ub) const
{
  // Preconditions:

  require(df_is_variable());
  require(xdofs != 0);
  require(xdofs_ub > 0);

  // Body:

  //cout << "section_evaluator::min()" << endl;

  dof_type result = xdofs[0];

  for(int i=1; i<xdofs_ub; ++i)
  {
    dof_type x = xdofs[i];
    if(x < result)
      result = x;
  }

  // Postconditions:

  return result;
}

///
fiber_bundle::section_evaluator::dof_type
fiber_bundle::section_evaluator::
min(const block<dof_type>& xdofs) const
{
  // Preconditions:

  require(precondition_of(min(xdofs.base(), xdofs.ct())));

  // Body:

  dof_type result = min(xdofs.base(), xdofs.ct());

  // Postconditions:

  ensure(postcondition_of(min(xdofs.base(), xdofs.ct())));

  // Exit:

  return result;
}

///
void
fiber_bundle::section_evaluator::
min(const dof_type xdofs[],
    size_type xdofs_ub,
    dof_type xresult[],
    size_type xresult_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub > 0);
  require(xresult != 0);
  require(xresult_ub > 0);

  // Body:

  // Here we assume that xresult_ub is the number of components
  // and that the components are interleaved in xdofs (ie; x,y,z,...).

  for(int j=0; j<xresult_ub; ++j)
  {
    xresult[j] = xdofs[j];
  }

  for(int i=0; i<xdofs_ub; i+=xresult_ub)
  {
    for(int j=0; j<xresult_ub; ++j)
    {
      dof_type x = xdofs[i+j];

      if(x < xresult[j])
        xresult[j] = x;
    }
  }

  // Postconditions:

}

///
void
fiber_bundle::section_evaluator::
min(const block<dof_type>& xdofs, block<dof_type>& xresult) const
{
  // Preconditions:

  require(precondition_of(min(xdofs.base(), xdofs.ct(), xresult.base(), xresult.ct())));

  // Body:

  min(xdofs.base(), xdofs.ct(), xresult.base(), xresult.ct());

  // Postconditions:

  ensure(postcondition_of(min(xdofs.base(), xdofs.ct(), xresult.base(), xresult.ct())));
  ensure(xresult.ct() == xresult.ct());

  // Exit:

  return;
}

///
fiber_bundle::section_evaluator::dof_type
fiber_bundle::section_evaluator::
max(const dof_type xdofs[], size_type xdofs_ub) const
{
  // Preconditions:

  require(df_is_variable());
  require(xdofs != 0);
  require(xdofs_ub > 0);

  // Body:

  dof_type result = xdofs[0];

  for(int i=1; i<xdofs_ub; ++i)
  {
    dof_type x = xdofs[i];
    if(x > result)
      result = x;
  }

  // Postconditions:

  return result;
}

///
fiber_bundle::section_evaluator::dof_type
fiber_bundle::section_evaluator::
max(const block<dof_type>& xdofs) const
{
  // Preconditions:

  require(precondition_of(max(xdofs.base(), xdofs.ct())));

  // Body:

  dof_type result = max(xdofs.base(), xdofs.ct());

  // Postconditions:

  ensure(postcondition_of(max(xdofs.base(), xdofs.ct())));

  // Exit:

  return result;
}

///
void
fiber_bundle::section_evaluator::
max(const dof_type xdofs[],
    size_type xdofs_ub,
    dof_type xresult[],
    size_type xresult_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub > 0);
  require(xresult != 0);
  require(xresult_ub > 0);

  // Body:

  // Here we assume that xresult_ub is the number of components
  // and that the components are interleaved in xdofs (ie; x,y,z,...).

  for(int j=0; j<xresult_ub; ++j)
  {
    xresult[j] = xdofs[j];
  }

  for(int i=0; i<xdofs_ub; i+=xresult_ub)
  {
    for(int j=0; j<xresult_ub; ++j)
    {
      dof_type x = xdofs[i+j];

      if(x > xresult[j])
        xresult[j] = x;
    }
  }

  // Postconditions:

}

///
void
fiber_bundle::section_evaluator::
max(const block<dof_type>& xdofs, block<dof_type>& xresult) const
{
  // Preconditions:

  require(precondition_of(max(xdofs.base(), xdofs.ct(), xresult.base(), xresult.ct())));

  // Body:

  max(xdofs.base(), xdofs.ct(), xresult.base(), xresult.ct());

  // Postconditions:

  ensure(postcondition_of(max(xdofs.base(), xdofs.ct(), xresult.base(), xresult.ct())));

  // Exit:

  return;
}

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::section_evaluator*
fiber_bundle::section_evaluator::
clone() const
{
  section_evaluator* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
fiber_bundle::section_evaluator&
fiber_bundle::section_evaluator::
operator=(const section_evaluator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
fiber_bundle::section_evaluator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  return result;
}

///
bool
fiber_bundle::section_evaluator::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const section_evaluator*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
fiber_bundle::
deep_size(const section_evaluator& xe, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}


