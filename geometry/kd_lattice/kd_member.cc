

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_member

#include "kd_member.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "base_space_member.h"
#include "cohort.h"
#include "e3.h"
#include "geometry_namespace.h"
#include "kd_lattice.h"
#include "sec_e3.h"
#include "tolerance_comparison.h"
#include "wsv_block.h"

using namespace geometry; // Workaround for MS C++ bug.

// ===========================================================
// KD_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_member::
~kd_member()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

const geometry::kd_lattice&
geometry::kd_member::
host() const
{
  return *_host;
}

const sheaf::scoped_index&
geometry::kd_member::
id() const
{
  return _id;
}

void
geometry::kd_member::
put_id(const scoped_index& xid)
{
  // Preconditions:


  // Body:

  _id = xid;

  // Postconditions:

  ensure(id() == xid);
  
  // Exit:

  return;
}

string
geometry::kd_member::
name() const
{
  // cout << endl << "Entering kd_member::name." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());

  // Body:

  string result = name(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::name." << endl;
  return result;
}

string
geometry::kd_member::
name(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_member::name." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  
  // Body:

  string result = xhost.base_space().member_name(xid);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::name." << endl;
  return result;
}

int
geometry::kd_member::
type_id() const
{
  // cout << endl << "Entering kd_member::type_id." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require(host().base_space().is_jim(id(), false));

  // Body:

  int result = type_id(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::type_id." << endl;
  return result;
}

int
geometry::kd_member::
type_id(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_member::type_id." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().is_jim(xid, false));
  
  // Body:

  int result = kd_member::row_dofs(xhost, xid).type_id;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::type_id." << endl;
  return result;
}

string
geometry::kd_member::
type_name() const
{
  // cout << endl << "Entering kd_member::type_name." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require(host().base_space().is_jim(id(), false));

  // Body:

  string result = type_name(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::type_name." << endl;
  return result;
}

string
geometry::kd_member::
type_name(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_member::type_name." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().is_jim(xid, false));
  
  // Body:

  string result(kd_member::row_dofs(xhost, xid).type_name);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::type_name." << endl;
  return result;
}

geometry::kd_alignment
geometry::kd_member::
alignment() const
{
  // cout << endl << "Entering kd_member::alignment." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require(host().base_space().is_jim(id(), false));

  // Body:

  kd_alignment result = alignment(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::alignment." << endl;
  return result;
}

geometry::kd_alignment
geometry::kd_member::
alignment(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_member::alignment." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().is_jim(xid, false));
  
  // Body:

  kd_alignment result = geometry::alignment(kd_member::row_dofs(xhost, xid).alignment);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::alignment." << endl;
  return result;
}

int
geometry::kd_member::
int_alignment() const
{
  // cout << endl << "Entering kd_member::alignment." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require(host().base_space().is_jim(id(), false));

  // Body:

  int result = int_alignment(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::alignment." << endl;
  return result;
}

int
geometry::kd_member::
int_alignment(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_member::alignment." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().is_jim(xid, false));
  
  // Body:

  int result = kd_member::row_dofs(xhost, xid).alignment;

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::alignment." << endl;
  return result;
}

bool
geometry::kd_member::
is_leaf() const
{
  // cout << endl << "Entering kd_member::is_leaf." << endl;

  // Preconditions:


  // Body:

  bool result = is_leaf(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::is_leaf." << endl;
  return result;
}

bool
geometry::kd_member::
is_leaf(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_member::is_leaf." << endl;

  // Preconditions:


  // Body:

  bool result = xhost.leaves().contains(xid);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::is_leaf." << endl;
  return result;
}

bool
geometry::kd_member::
is_jim() const
{
  // cout << endl << "Entering kd_member::is_jim." << endl;

  // Preconditions:


  // Body:

  bool result = is_jim(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::is_jim." << endl;
  return result;
}

bool
geometry::kd_member::
is_jim(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_member::is_jim." << endl;

  // Preconditions:


  // Body:

  bool result = xhost.base_space().jims().contains_member(xid);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::is_jim." << endl;
  return result;
}


// void
// geometry::kd_member::
// coord_bounds(e3_lite& xlb, e3_lite& xub) const
// {
//   // Preconditions:

//   require(host().base_space().state_is_read_accessible());
//   require(host().coords().state_is_read_accessible());

//   // Body:

//   is_abstract();
  
//   // Postconditions:


//   // Exit:

//   return;
// }

// bool
// geometry::kd_member::
// in_bounds(const kd_plane& xp) const
// {
//   // Preconditions:

//   require(host().base_space().state_is_read_accessible());
//   require(host().coords().state_is_read_accessible());

//   // Body:
  
//   is_abstract();

//   bool result = false; // Just to suppress compiler warning.
  
//   // Postconditions:


//   // Exit:

//   return result;
// }

// void
// geometry::kd_member::
// refine(const kd_plane& xp, scoped_index xnew_ids[])
// {
//   // Preconditions:

//   require(host().base_space().state_is_read_accessible());
//   require(host().coords().state_is_read_write_accessible());
//   require(in_bounds(xp));
//   require(host().base_space().is_jim(id()));
  
//   // Body:

//   is_abstract();
  
//   // Postconditions:


//   // Exit:

//   return;
// }


const sheaf::poset_path&
geometry::kd_member::
standard_schema_path()
{

  // Preconditions:

  // Body:


  static const poset_path result(fiber_bundles_namespace::standard_base_space_schema_poset_name(),
                                 "kd_member_schema");

  // Postconditions:

  // Exit

  return result;
}

const sheaf::poset_path&
geometry::kd_member::
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
geometry::kd_member::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_path().poset_name(), false));
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string ldof_specs = "alignment INT false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
			      base_space_member::standard_schema_path(),
                              ldof_specs,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path(), false));

  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

geometry::kd_member::
kd_member()
{
  
  // Preconditions:

    
  // Body:
  
  _host = 0;
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::kd_member::
kd_member(kd_lattice& xhost)
{
  
  // Preconditions:

    
  // Body:
  
  _host = &xhost;
  
  // Postconditions:

  ensure(&host() == &xhost);
  ensure(!id().is_valid());

  // Exit:

  return; 
}

geometry::kd_member::
kd_member(kd_lattice& xhost, const scoped_index& xid)
{
  
  // Preconditions:

    
  // Body:
  
  _host = &xhost;
  _id = xid;
  
  // Postconditions:

  ensure(&host() == &xhost);
  ensure(id() == xid);

  // Exit:

  return; 
}

geometry::kd_member::
kd_member(const kd_member& xother)
{
  
  // Preconditions:

    
  // Body:

  (*this) = xother;
  
  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xother.host());
  ensure(id() == xother.id());
  
  // Exit:

  return; 
}


void
geometry::kd_member::
coord_bounds(const kd_lattice& xhost, const scoped_index& xid0, const scoped_index& xid1, e3_lite& xlb, e3_lite& xub)
{
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.coords().state_is_read_accessible());

  // Body:

  // Get vertex coordinates; use results as buffer
  
  xhost.coords().get_fiber(xid0, xlb, false);
  xhost.coords().get_fiber(xid1, xub, false);

  // Sort into lower and upper bounds:

  double lbuf;
  for(int i=0;i<3; ++i)
  {
    if(xlb[i] > xub[i])
    {
      lbuf = xlb[i];
      xlb[i] = xub[i];
      xub[i] = lbuf;
    }
  }
  
  // Postconditions:


  // Exit:

  return;
}

geometry::kd_member_row_dofs_type&
geometry::kd_member::
row_dofs()
{
  // cout << endl << "Entering kd_member::row_dofs." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_write_accessible());
  require(host().base_space().is_jim(id(), false));

  // Body:

  kd_member_row_dofs_type& result = row_dofs(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::row_dofs." << endl;
  return result;
}

geometry::kd_member_row_dofs_type&
geometry::kd_member::
row_dofs(kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_member::row_dofs." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_write_accessible());
  require(xhost.base_space().is_jim(xid, false));
  
  // Body:

  kd_member_row_dofs_type& result = 
    *reinterpret_cast<kd_member_row_dofs_type*>(xhost.base_space().member_dof_tuple(xid, false));

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::row_dofs." << endl;
  return result;
}

const geometry::kd_member_row_dofs_type&
geometry::kd_member::
row_dofs() const
{
  // cout << endl << "Entering kd_member::row_dofs." << endl;

  // Preconditions:

  require(host().base_space().state_is_read_accessible());
  require(host().base_space().is_jim(id(), false));

  // Body:

  const kd_member_row_dofs_type& result = row_dofs(*_host, _id);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::row_dofs." << endl;
  return result;
}

const geometry::kd_member_row_dofs_type&
geometry::kd_member::
row_dofs(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_member::row_dofs." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.base_space().is_jim(xid, false));
  
  // Body:

  const kd_member_row_dofs_type& result = 
    *reinterpret_cast<kd_member_row_dofs_type*>(xhost.base_space().member_dof_tuple(xid, false));

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_member::row_dofs." << endl;
  return result;
}


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_member::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_member*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_member*
geometry::kd_member::
clone() const
{
  kd_member* result = 0;
  
  // Preconditions:

  // Body:
  
  is_abstract();
  
  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
geometry::kd_member::
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

geometry::kd_member&
geometry::kd_member::
operator=(const kd_member& xother)
{
  
  // Preconditions:

    
  // Body:
  
  _host = xother._host;
  _id = xother._id;

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xother.host());
  ensure(id() == xother.id());

  // Exit
  
  return *this;
}

geometry::kd_member&
geometry::kd_member::
operator=(const any& xother)
{
  
  // Preconditions:

  require(is_ancestor_of(&xother));
    
  // Body:

  const kd_member& lother = reinterpret_cast<const kd_member&>(xother);
  
  operator=(lother);

  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
// ostream& 
// geometry::
// operator << (ostream& xos, const kd_member& xn)
// {
//   // Preconditions:

//   require(xn.host().coords().state_is_read_accessible());

//   // Body:

//   xos << "  name: " << xn.name();
//   xos << "  top id: " << xn.id();
//   xos << "  type: " << xn.type_name();
//   xos << boolalpha;
//   xos << "  is_jim: " << xn.is_jim();
//   xos << "  is_leaf: " << xn.is_leaf();
//   xos << noboolalpha;
//   xos << "  lb: " << xn.coord_lower_bound();
//   xos << "  ub: " << xn.coord_upper_bound();
//   xos << endl;
  
//   xos << "\tlower cover:";
//   const base_space_poset& lbase = xn.host().base_space();
//   cover_set_iterator litr = lbase.cover_iterator(LOWER, xn.id());
//   while(!litr.is_done())
//   {
//     xos << "   " << lbase.member_name(litr.item());
//     litr.next();
//   }
//   xos << endl;
  

//   // Postconditions:

//   // Exit:

//   return xos;
// }

size_t
geometry::
deep_size(const geometry::kd_member& xn, bool xinclude_shallow)
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
