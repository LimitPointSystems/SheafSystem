//

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class dof_descriptor_array

#include "dof_descriptor_array.h"

#include "assert_contract.h"
#include "primitive_attributes.h"
#include "std_string.h"

// ===========================================================
// DOF_DESCRIPTOR_ARRAY FACET
// ===========================================================

sheaf::dof_descriptor_array::
dof_descriptor_array(size_type xdof_ct)
{
  // Preconditions:

  require(xdof_ct >= 0);

  // Body:

  _ub = xdof_ct+1;
  _descriptors = new dof_descriptor[_ub];
  _ref_ct = 0;

  // Postconditions:

  ensure(ub() == xdof_ct + 1);

  // Exit:

  return;
}

sheaf::dof_descriptor_array::
~dof_descriptor_array()
{
  // Preconditions:

  // Body:

  delete [] _descriptors;

  // Postconditions:

  // Exit:

  return;
}

sheaf::dof_descriptor_array:: dof_descriptor&
sheaf::dof_descriptor_array::
operator[](int xid) const
{
  // Preconditions:

  require( (0 <= xid) && (xid < ub()) );

  return _descriptors[xid];
}

void
sheaf::dof_descriptor_array::
add_reference()
{
  _ref_ct++;
}

void
sheaf::dof_descriptor_array::
remove_reference()
{
  if(--_ref_ct == 0)
    delete this;
}

sheaf::size_type
sheaf::dof_descriptor_array::
ub() const
{
  size_type result = _ub;

  // Postconditions:

  ensure(result >= 1);

  return result;
}

sheaf::size_type
sheaf::dof_descriptor_array::
dof_ct() const
{
  size_type result = _ub - 1;

  // Postconditions:

  ensure(result >= 0);

  return result;
}

sheaf::size_type
sheaf::dof_descriptor_array::
size() const
{
  return _descriptors[_ub - 1].offset;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

ostream& sheaf::
operator << (ostream &os, const dof_descriptor_array& p)
{
  os << "p.ub() = " << p.ub() << endl;
  
  for(int i=0; i<p.ub(); ++i)
  {
    os << "  " << p[i];
  }
  
  return os;
}

ostream& sheaf::
operator << (ostream &os, const dof_descriptor_array::dof_descriptor& p)
{
  os << "{"  << primitive_attributes::name(p.type)
  << ", " << p.size
  << ", " << p.alignment
  << ", " << p.offset
  << "}";

  return os;
}

size_t
sheaf::
deep_size(const dof_descriptor_array& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add the memory allocated for _descriptors.

  dof_descriptor_array& lxp = const_cast<dof_descriptor_array&>(xp);
  result += lxp.ub()*sizeof(dof_descriptor_array::dof_descriptor);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
