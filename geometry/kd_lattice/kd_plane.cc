

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_plane

#include "kd_plane.h"

#include "assert_contract.h"
#include "d_cells_cohort.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "kd_edge.h"
#include "kd_lattice.h"
#include "sec_e3.h"
#include "schema_descriptor.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"
#include "wsv_block.h"
	
using namespace geometry; // Workaround for MS C++ bug.

// ===========================================================
// KD_PLANE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
geometry::kd_plane::
standard_schema_path()
{

  // Preconditions:

  // Body:


  static const poset_path result(fiber_bundles_namespace::standard_fiber_space_schema_poset_name(),
                                 "kd_plane_schema");

  // Postconditions:

  // Exit

  return result;
}

const sheaf::poset_path&
geometry::kd_plane::
schema_path() const
{
  // Preconditions:

  // Body:

  const poset_path& result = standard_schema_path();

  // Postconditions:

  // Exit

  return result;
}

void
geometry::kd_plane::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_path().poset_name(), false));
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string ldof_specs;
  ldof_specs += "alignment INT false";
  ldof_specs += "distance DOUBLE false";

  string lmember_name(standard_schema_path().member_name());
  poset_path lparent = standard_schema_path();
  lparent.put_member_name("tuple_schema");
  
  schema_poset_member lschema(xns, lmember_name, lparent, ldof_specs, false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path(), false));

  // Exit:

  return;
}

geometry::kd_plane::
kd_plane()
{  
  // Preconditions:
    
  // Body:  

  _row_dofs.alignment = NOT_AXIS_ALIGNED;
  _row_dofs.distance = 0.0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_valid());

  // Exit:

  return; 
}

geometry::kd_plane::
kd_plane(kd_alignment xalign, vd_value_type xdist)
{
  
  // Preconditions:

    
  // Body:

  _row_dofs.alignment = xalign;
  _row_dofs.distance = xdist;

  // Postconditions:

  ensure(invariant());
  ensure(alignment() == xalign);
  ensure(distance() == xdist);

  // Exit:

  return; 
}

geometry::kd_plane::
kd_plane(const kd_plane& xother)
{
  
  // Preconditions:

    
  // Body:

  _row_dofs.alignment = xother._row_dofs.alignment;
  _row_dofs.distance = xother._row_dofs.distance;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::kd_plane::
~kd_plane()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

void
geometry::kd_plane::
put(int xalign, vd_value_type xdist)
{
  // cout << endl << "Entering kd_plane::put." << endl;

  // Preconditions:


  // Body:

  _row_dofs.alignment = geometry::alignment(xalign);
  _row_dofs.distance = xdist;

  // Postconditions:

  ensure(alignment() == geometry::alignment(xalign));
  ensure(distance() == xdist);

  // Exit:

  // cout << "Leaving kd_plane::put." << endl;
  return;
}

kd_alignment
geometry::kd_plane::
alignment() const
{
  static const kd_alignment result[NOT_AXIS_ALIGNED+1] = 
    {
      X_AXIS_ALIGNED, Y_AXIS_ALIGNED, Z_AXIS_ALIGNED, NOT_AXIS_ALIGNED
    };
  
  return result[_row_dofs.alignment];
}

void
geometry::kd_plane::
put_alignment(int xalign)
{
  // cout << endl << "Entering kd_plane::put_alignment." << endl;

  // Preconditions:


  // Body:

  _row_dofs.alignment = geometry::alignment(xalign);

  // Postconditions:

  ensure(alignment() == geometry::alignment(xalign));

  // Exit:

  // cout << "Leaving kd_plane::put_alignment." << endl;
  return;
}


int
geometry::kd_plane::
int_alignment() const
{
  return _row_dofs.alignment;
}

geometry::vd_value_type
geometry::kd_plane::
distance() const
{
  return _row_dofs.distance;
}

void
geometry::kd_plane::
put_distance(vd_value_type xdist)
{
  // cout << endl << "Entering kd_plane::put_distance." << endl;

  // Preconditions:


  // Body:

  _row_dofs.distance = xdist;

  // Postconditions:

  ensure(distance() == xdist);

  // Exit:

  // cout << "Leaving kd_plane::put_distance." << endl;
  return;
}

const kd_plane::row_dofs_type&
geometry::kd_plane::
row_dofs() const
{
  return _row_dofs;
}

bool
geometry::kd_plane::
operator<(const kd_plane& xother) const
{
  // cout << endl << "Entering kd_plane::operator<." << endl;

  // Preconditions:


  // Body:

  bool result =
    (_row_dofs.alignment < xother._row_dofs.alignment) ||
    ((_row_dofs.alignment == xother._row_dofs.alignment) && 
     (_row_dofs.distance < xother._row_dofs.distance));
    

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_plane::operator<." << endl;
  return result;
}

bool
geometry::kd_plane::
is_valid() const
{
  // cout << endl << "Entering kd_plane::is_valid." << endl;

  // Preconditions:


  // Body:

  bool result = (_row_dofs.alignment != NOT_AXIS_ALIGNED);

  // Postconditions:

  ensure( result == (alignment() != NOT_AXIS_ALIGNED));
  
  // Exit:

  // cout << "Leaving kd_plane::is_valid." << endl;
  return result;
}

bool
geometry::kd_plane::
contains_line(const list<e3_lite>& xline) const
{
  // cout << endl << "Entering kd_plane::contains_line." << endl;

  // Preconditions:

  require(!xline.empty());

  // Body:

  bool result = true;
  
  list<e3_lite>::const_iterator litr = xline.begin();
  while(litr != xline.end())
  {
    if((*litr)[_row_dofs.alignment] != _row_dofs.distance)
    {
      result = false;
      break;
    }
    ++litr;
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_plane::contains_line." << endl;
  return result;
}

void
geometry::kd_plane::
local_axes(int& xu_id, int& xv_id, bool xright_hand) const
{
  // cout << endl << "Entering kd_plane::local_axes." << endl;

  // Preconditions:
  
  // Body:

  int lw_id = _row_dofs.alignment;
  local_axes(_row_dofs.alignment, xu_id, xv_id, xright_hand);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_plane::local_axes." << endl;
  return;
}

void
geometry::kd_plane::
local_axes(int xalignment, int& xu_id, int& xv_id, bool xright_hand)
{
  // cout << endl << "Entering kd_plane::local_axes." << endl;

  // Preconditions:
  
  // Body:

  if(xright_hand)
  {
    xu_id = (xalignment+1) % 3;
    xv_id = (xalignment+2) % 3;
  }
  else
  {
    xu_id = (xalignment+2) % 3;
    xv_id = (xalignment+1) % 3;
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_plane::local_axes." << endl;
  return;
}

geometry::kd_alignment
geometry::kd_plane::
intersection_alignment(const kd_plane& xother) const
{
  // cout << endl << "Entering kd_plane::intersection_alignment." << endl;

  // Preconditions:


  // Body:

  static const kd_alignment lresult[NOT_AXIS_ALIGNED] = {X_AXIS_ALIGNED, Y_AXIS_ALIGNED, Z_AXIS_ALIGNED};
  
  kd_alignment result = lresult[intersection_int_alignment(xother)];
  

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_plane::intersection_alignment." << endl;
  return result;
}

geometry::kd_plane::on_code_type
geometry::kd_plane::
on_code(const e3_lite& xpt, const e3_lite& xtolerance) const
{
  // cout << endl << "Entering kd_plane::on_code." << endl;

  // Preconditions:


  // Body:

  int lalignment = _row_dofs.alignment;
  vd_value_type lpt_dist = xpt[lalignment];
  
  on_code_type result = 
    (lpt_dist == _row_dofs.distance) ? ON : (lpt_dist < _row_dofs.distance) ? BACK : FRONT;
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_plane::on_code." << endl;
  return result;
}

geometry::kd_plane::on_code_type
geometry::kd_plane::
on_code(int xi)
{
  // cout << endl << "Entering kd_plane::on_code." << endl;

  // Preconditions:


  // Body:

  on_code_type result;
  switch(xi)
  {
    case BACK:
      result = BACK;
      break;
    case FRONT:
      result = FRONT;
      break;
    case ON:
      result = ON;
      break;
    default:
      result = NOT_AN_ON_CODE;
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_plane::on_code." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_plane::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_plane*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_plane*
geometry::kd_plane::
clone() const
{
  kd_plane* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_plane();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
geometry::kd_plane::
operator==(const kd_plane& xother) const
{
  
  // Preconditions:

    
  // Body:
  
  bool result = 
    (_row_dofs.alignment == xother._row_dofs.alignment) &&
    (_row_dofs.distance == xother._row_dofs.distance);
  
  // Postconditions:

  ensure(result == ((alignment() == xother.alignment()) && (distance() == xother.distance())));

  // Exit
  
  return result;
}

geometry::kd_plane&
geometry::kd_plane::
operator=(const kd_plane& xother)
{
  
  // Preconditions:

    
  // Body:
  
  _row_dofs.alignment = xother._row_dofs.alignment;
  _row_dofs.distance = xother._row_dofs.distance;
  
  // Postconditions:

  ensure((*this) == xother);

  // Exit
  
  return *this;
}

geometry::kd_plane&
geometry::kd_plane::
operator=(const any& xother)
{
  
  // Preconditions:

  require(is_ancestor_of(&xother));
    
  // Body:
  
  const kd_plane& lother = reinterpret_cast<const kd_plane&>(xother);
  operator=(lother);

  // Postconditions:

  ensure((*this) == reinterpret_cast<const kd_plane&>(xother));

  // Exit
  
  return *this;
}

bool
geometry::kd_plane::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, const geometry::kd_plane& xn)
{
  // Preconditions:

  // Body:

  xos << xn.alignment() << "  " << xn.distance();

  // Postconditions:

  // Exit:

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const geometry::kd_plane::on_code_type& xn)
{
  // Preconditions:

  // Body:

  switch(xn)
  {
    case kd_plane::BACK:
      xos << "BACK";
      break;
    case kd_plane::FRONT:
      xos << "FRONT";
      break;
    case kd_plane::ON:
      xos << "ON";
      break;
    default:
      xos << "NOT_AN_ON_CODE";
  }
      
  // Postconditions:

  // Exit:

  return xos;
}

size_t
geometry::
deep_size(const kd_plane& xn, bool xinclude_shallow)
{
  size_t result = 0;

  // Preconditions:

  // Body:

  not_implemented();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

bool
geometry::
a_eql(const kd_plane& xp0, const kd_plane& xp1, const e3_lite& xtolerance)
{
  //  cout << endl << "Entering geometry::a_eql(const kd_plane&, const kd_plane&)." << endl;

  // Preconditions:


  // Body:

  //   cout << xp0 << endl;
  //   cout << xp1 << endl;
  //   cout << xtolerance << endl;

  bool result = 
    (xp0.alignment() == xp1.alignment()) && 
    sheaf::a_eql(xp0.distance(), xp1.distance(), xtolerance[xp0.alignment()]);

  //  cout << boolalpha << result << noboolalpha << endl;

  // Postconditions:

  ensure(result == ((xp0.alignment() == xp1.alignment()) && 
		    sheaf::a_eql(xp0.distance(), xp1.distance(), xtolerance[xp0.alignment()])));

  // Exit:

  //  cout << "Leaving geometry::a_eql(const kd_plane&, const kd_plane&)." << endl;
  return result;
}

bool
geometry::
r_eql(const kd_plane& xp0, const kd_plane& xp1, const e3_lite& xtolerance)
{
  cout << endl << "Entering geometry::r_eql(const kd_plane&, const kd_plane&)." << endl;

  // Preconditions:


  // Body:

  cout << xp0 << endl;
  cout << xp1 << endl;
  cout << xtolerance << endl;

  bool result = 
    (xp0.alignment() == xp1.alignment()) && 
    sheaf::r_eql(xp0.distance(), xp1.distance(), xtolerance[xp0.alignment()]);

  cout << boolalpha << result << noboolalpha << endl;

  // Postconditions:

  ensure(result == ((xp0.alignment() == xp1.alignment()) && 
		    sheaf::r_eql(xp0.distance(), xp1.distance(), xtolerance[xp0.alignment()])));

  // Exit:

  cout << "Leaving geometry::r_eql(const kd_plane&, const kd_plane&)." << endl;
  return result;
}

bool
geometry::
c_eql(const kd_plane& xp0, const kd_plane& xp1, const e3_lite& xtolerance)
{
  cout << endl << "Entering geometry::c_eql(const kd_plane&, const kd_plane&)." << endl;

  // Preconditions:


  // Body:

  cout << xp0 << endl;
  cout << xp1 << endl;
  cout << xtolerance << endl;

  bool result = 
    (xp0.alignment() == xp1.alignment()) && 
    sheaf::c_eql(xp0.distance(), xp1.distance(), xtolerance[xp0.alignment()]);

  cout << boolalpha << result << noboolalpha << endl;

  // Postconditions:

  ensure(result == ((xp0.alignment() == xp1.alignment()) && 
		    sheaf::c_eql(xp0.distance(), xp1.distance(), xtolerance[xp0.alignment()])));

  // Exit:

  cout << "Leaving geometry::c_eql(const kd_plane&, const kd_plane&)." << endl;
  return result;
}

bool
geometry::
a_eql(const e3_lite& xp0, const kd_plane& xp1, const e3_lite& xtolerance)
{
  // cout << endl << "Entering geometry::a_eql(const e3_lite&, const kd_plane&)." << endl;

  // Preconditions:


  // Body:

  int lalignment = xp1.int_alignment();
  bool result = sheaf::a_eql(xp0[lalignment], xp1.distance(), xtolerance[lalignment]);

  // Postconditions:

  ensure(result == sheaf::a_eql(xp0[xp1.alignment()], xp1.distance(), xtolerance[xp1.alignment()]));

  // Exit:

  // cout << "Leaving geometry::a_eql(const e3_lite&, const kd_plane&)." << endl;
  return result;
}

bool
geometry::
r_eql(const e3_lite& xp0, const kd_plane& xp1, const e3_lite& xtolerance)
{
  // cout << endl << "Entering geometry::r_eql(const e3_lite&, const kd_plane&)." << endl;

  // Preconditions:


  // Body:

  int lalignment = xp1.int_alignment();
  bool result = sheaf::r_eql(xp0[lalignment], xp1.distance(), xtolerance[lalignment]);

  // Postconditions:

  ensure(result == sheaf::r_eql(xp0[xp1.alignment()], xp1.distance(), xtolerance[xp1.alignment()]));

  // Exit:

  // cout << "Leaving geometry::r_eql(const e3_lite&, const kd_plane&)." << endl;
  return result;
}

bool
geometry::
c_eql(const e3_lite& xp0, const kd_plane& xp1, const e3_lite& xtolerance)
{
  // cout << endl << "Entering geometry::c_eql(const e3_lite&, const kd_plane&)." << endl;

  // Preconditions:


  // Body:

  int lalignment = xp1.int_alignment();
  bool result = sheaf::c_eql(xp0[lalignment], xp1.distance(), xtolerance[lalignment]);

  // Postconditions:

  ensure(result == sheaf::c_eql(xp0[xp1.alignment()], xp1.distance(), xtolerance[xp1.alignment()]));

  // Exit:

  // cout << "Leaving geometry::c_eql(const e3_lite&, const kd_plane&)." << endl;
  return result;
}

