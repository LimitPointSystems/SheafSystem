

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_vertex

#include "kd_vertex.h"
#include "array_section_dof_map.h"
#include "assert_contract.h"
#include "cohort.h"
#include "d_cells_cohort.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "kd_edge.h"
#include "kd_lattice.h"
#include "sec_e3.h"
#include "vertex_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.

// ===========================================================
// KD_VERTEX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
geometry::kd_vertex::
prototype_name()
{
  // cout << endl << "Entering kd_zone::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string result("kd_vertex");

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_zone::prototype_name." << endl;
  return result;
}

geometry::kd_vertex::
kd_vertex(kd_lattice& xhost)
  : kd_member(xhost)
{
  // cout << "Entering kd_vertex(kd_lattice& xhost)." << endl;
  
  // Preconditions:

  require(host().base_space().in_jim_edit_mode());
    
  // Body:

  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());

  _id = new_vertex(xhost);

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(host().vertices().contains(id()));
  ensure(host().vertices().ct() == old_vertices_ct + 1);

  // Exit:

  // cout << "Leaving kd_vertex(kd_lattice& xhost)." << endl;
  return; 
}

sheaf::scoped_index
geometry::kd_vertex::
new_vertex(kd_lattice& xhost)
{
  // cout << "Entering kd_vertex::new_vertex(kd_lattice& xhost)." << endl;
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
    
  // Body:

  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());

  // Create the vertex.

  scoped_index result = xhost.vertices().new_member();

  // Set the alignment dof.

  row_dofs(xhost, result).alignment = NOT_AXIS_ALIGNED;

  // Add the vertex to the edge points cohort.

  xhost.edge_points().insert_member(result);

  // Postconditions:

  ensure(xhost.vertices().contains(result));
  ensure(xhost.vertices().ct() == old_vertices_ct + 1);
  ensure(xhost.edge_points().contains(result));

  // Exit:

  // cout << "Leaving kd_vertex::new_vertex(kd_lattice& xhost)." << endl;
  return result; 
}

geometry::kd_vertex::
kd_vertex(kd_lattice& xhost, const e3_lite& xcoords)
  : kd_member(xhost)
{
  // cout << endl << "Entering kd_vertex(kd_lattice& xhost, const e3_lite& xcoords)." << endl;
  
  // Preconditions:

  require(host().base_space().in_jim_edit_mode());
  require(host().coords().state_is_read_write_accessible());
    
  // Body:

  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());

  _id = new_vertex(xhost, xcoords);

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(host().vertices().contains(id()));
  ensure(host().vertices().ct() == old_vertices_ct + 1);
  ensure(coords() == xcoords);
  
  // Exit:

  // cout << "Leaving kd_vertex(kd_lattice& xhost, const e3_lite& xcoords)." << endl;
  return; 
}

sheaf::scoped_index
geometry::kd_vertex::
new_vertex(kd_lattice& xhost, const e3_lite& xcoords)
{
  // cout << endl << "Entering kd_vertex::new_vertex(kd_lattice& xhost, const e3_lite& xcoords)." << endl;
  
  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.coords().state_is_read_write_accessible());
    
  // Body:

  define_old_variable(size_type old_vertices_ct = xhost.vertices().ct());

  // Create the vertex.

  scoped_index result = new_vertex(xhost);

  // Set the coordinates for the vertex.

  kd_vertex::put_coords(xhost, result, xcoords);

  // Postconditions:

  ensure(xhost.vertices().contains(result));
  ensure(xhost.vertices().ct() == old_vertices_ct + 1);
  ensure(coords(xhost, result) == xcoords);
  

  // Exit:

  // cout << "Leaving kd_vertex::new_vertex(kd_lattice& xhost, const e3_lite& xcoords)." << endl;
  return result; 
}

geometry::kd_vertex::
kd_vertex(kd_lattice& xhost, const scoped_index& xid)
  : kd_member(xhost, xid)
{
  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(id() == xid);

  // Exit:

  return; 
}

geometry::kd_vertex::
kd_vertex(const kd_vertex& xother)
  : kd_member(xother)
{
  
  // Preconditions:

    
  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::kd_vertex::
~kd_vertex()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

fiber_bundle::e3_lite
geometry::kd_vertex::
coords() const
{
  // Preconditions:

  require(host().coords().state_is_read_accessible());
  
  // Body:

  e3_lite result(coords(*_host, _id));

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::e3_lite
geometry::kd_vertex::
coords(const kd_lattice& xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  
  // Body:

  e3_lite result;
  xhost.coords().get_fiber(xid, result, false);

  // Postconditions:


  // Exit:

  return result;
}

void
geometry::kd_vertex::
coords(e3_lite& xcoords) const
{
  // Preconditions:

  require(host().coords().state_is_read_accessible());
  
  // Body:

  coords(*_host, _id, xcoords);

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_vertex::
coords(const kd_lattice& xhost, const scoped_index& xid, e3_lite& xcoords)
{
  // Preconditions:

  require(xhost.coords().state_is_read_accessible());
  require(xhost.vertices().contains(xid));
  
  // Body:

  xhost.coords().get_fiber(xid, xcoords, false);

  // Postconditions:


  // Exit:

  return;
}

void
geometry::kd_vertex::
put_coords(const e3_lite& xcoords)
{
  // cout << endl << "Entering kd_vertex::put_coords(const e3_lite&)." << endl;

  // Preconditions:

  require(host().coords().state_is_read_write_accessible());

  // Body:

  put_coords(*_host, _id, xcoords);

  // Postconditions:

  ensure(coords() == xcoords);

  // Exit:

  // cout << "Leaving kd_vertex::put_coords(const e3_lite&)." << endl;
  return;
}

void
geometry::kd_vertex::
put_coords(kd_lattice& xhost, const scoped_index& xid, const e3_lite& xcoords)
{
  // cout << endl << "Entering kd_vertex::put_coords(kd_lattice&, const scoped_index&, const e3_lite&)." << endl;

  // Preconditions:

  require(xhost.coords().state_is_read_write_accessible());
  require(xhost.vertices().contains(xid));

  // Body:

  xhost.coords().force_fiber(xid, xcoords, false);
  
  // Postconditions:

  ensure(coords(xhost, xid) == xcoords);

  // Exit:

  // cout << "Leaving kd_vertex::put_coords(kd_lattice&, const scoped_index&, const e3_lite&)." << endl;
  return;
}

bool
geometry::kd_vertex::
contains_point(const e3_lite& xpt) const
{
  // cout << endl << "Entering kd_vertex::contains_point." << endl;

  // Preconditions:

  require(host().coords().state_is_read_accessible());

  // Body:


  bool result = contains_point(*_host, _id, xpt);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_vertex::contains_point." << endl;
  return result;
}

bool
geometry::kd_vertex::
contains_point(const kd_lattice& xhost, const scoped_index& xid, const e3_lite& xpt)
{
  // cout << endl << "Entering kd_vertex::contains_point." << endl;

  // Preconditions:

  require(xhost.vertices().contains(xid));
  require(xhost.coords().state_is_read_accessible());

  // Body:

  e3_lite lcoords;
  coords(xhost, xid, lcoords);

  bool result = (xpt == lcoords);
  
  // Postconditions:

  ensure(result == (xpt == coords(xhost, xid)));
  
  // Exit:

  // cout << "Leaving kd_vertex::contains_point." << endl;
  return result;
}

void
geometry::kd_vertex::
replace_point(const scoped_index& xpt_id)
{
  // cout << endl << "Entering kd_vertex::replace_point." << endl;

  // Preconditions:

  require(precondition_of(replace_point(host(), id(), xpt_id)));
  
  // Body:

  replace_point(*_host, _id, xpt_id);
  
  // Postconditions:

  ensure(postcondition_of(replace_point(host(), id(), xpt_id)));

  // Exit:

  // cout << "Leaving kd_vertex::replace_point." << endl;
  return;
}

void
geometry::kd_vertex::
replace_point(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id)
{
  // cout << endl << "Entering kd_vertex::replace_point." << endl;

  // Preconditions:

  require(xhost.vertices().contains(xid));
  require(xhost.points().contains(xpt_id));
  require(xhost.base_space().in_jim_edit_mode());
  
  // Body:

  base_space_poset& lbase = xhost.base_space();
   
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(UPPER, xpt_id);
  while(!litr.is_done())
  {
    lbase.replace_cover_member(xpt_id, xid, LOWER, litr.hub_pod());
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);

  lbase.clear_cover(UPPER, xpt_id);

  // Only thing in the lower cover of xpt_id is bottom;
  // we never remove a point from the upper cover of bottom
  // because it's too expensive; just recycle the point.

  xhost.points().delete_member(xpt_id);

  // $$SCRIBBLE: need a cohort that includes both points and vertices

  // Postconditions:

  ensure(!xhost.points().is_active(xpt_id));
  
  // Exit:

  // cout << "Leaving kd_vertex::replace_point." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

geometry::kd_vertex::
kd_vertex()
{
  
  // Preconditions:

    
  // Body:  

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_vertex::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_vertex*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_vertex*
geometry::kd_vertex::
clone() const
{
  kd_vertex* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_vertex();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_vertex&
geometry::kd_vertex::
operator=(const kd_vertex& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_vertex&
geometry::kd_vertex::
operator=(const any& xother)
{
  
  // Preconditions:

  require(is_ancestor_of(&xother));
    
  // Body:
  
  kd_member::operator=(xother);

  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

bool
geometry::kd_vertex::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(kd_member::invariant());

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
operator << (ostream& xos, const kd_vertex& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());
  

  // Body:

  xos << "vertex " << xn.host().vertices().id_space().pod(xn.id());
  xos << "  top id: " << xn.id();
  xos << "  name: " << xn.name();
  xos << "  type: " << xn.type_name();
  xos << boolalpha;
  xos << "  is_jim: " << xn.is_jim();
  xos << "  is_leaf: " << xn.is_leaf();
  xos << noboolalpha;
  xos << "  coordinates: " << xn.coords();
  xos << endl;

  // Postconditions:

  // Exit:

  return xos;
}

size_t
geometry::
deep_size(const kd_vertex& xn, bool xinclude_shallow)
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
