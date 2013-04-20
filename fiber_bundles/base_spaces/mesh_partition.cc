
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class mesh_partition

#include "mesh_partition.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "error_message.h"
#include "hash_index_space_state.h"
#include "id_block.h"
#include "index_iterator.h"
#include "preorder_iterator.h"
#include "std_set.h"
#include "std_sstream.h"
#include "tern.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

// =============================================================================
// MESH_PARTITION FACET
// =============================================================================

///
fiber_bundle::mesh_partition::
mesh_partition()
{

  // Preconditions:


  // Body:

  _part_ct = 0;
  _mesh = 0;

  //$$SCRIBBLE: Adding a nonempty string to keep
  //            invariant() from blowing an assertion.

  _name = "unknown";

  // Postconditions:

  ensure(!name().empty());
  ensure(invariant());
  ensure(part_ct() == 0);

  // Exit:

  return;
}


///
fiber_bundle::mesh_partition::
mesh_partition(const mesh_partition& xother)
{

  // Preconditions:

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
fiber_bundle::mesh_partition::
~mesh_partition()
{
  // Preconditions:


  // Body:

  _parts.detach_from_state();

  // Postconditions:

  // Exit:

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

///
fiber_bundle::mesh_partition::
mesh_partition(const base_space_poset& xmesh, const string& xname)
{
  // Preconditions:

  require(is_valid_name(xname));
  require(xmesh.includes_subposet(xname) ?
          xmesh.state_is_read_accessible() :
          xmesh.state_is_read_write_accessible());

  // Body:

  bool old_xmesh_includes_mesh_partition_xname = xmesh.includes_subposet(xname);

  _mesh = const_cast<base_space_poset*>(&xmesh);
  _name = xname;


  initialize_parts_set();

  _part_ct = (old_xmesh_includes_mesh_partition_xname ? _parts.member_ct() : 0);

  // Postconditions:

  ensure(mesh().is_same_state(&xmesh));
  ensure(name() == xname);
  ensure(xmesh.includes_subposet(xname));
  ensure(part_ct() == (old_xmesh_includes_mesh_partition_xname ? parts().member_ct() : 0));


  return;
}


///
const string&
fiber_bundle::mesh_partition::
name() const
{
  return _name;
}


///
const fiber_bundle::base_space_poset&
fiber_bundle::mesh_partition::
mesh() const
{
  return *_mesh;
}

///
const sheaf::subposet&
fiber_bundle::mesh_partition::
parts() const
{
  return _parts;
}

///
int
fiber_bundle::mesh_partition::
part_ct() const
{
  return _part_ct;
}


///
string
fiber_bundle::mesh_partition::
part_name(const scoped_index& xp_id) const
{
  // Preconditions:


  // Body:

  stringstream lstream;
  lstream << _name << "::part_" << xp_id;

  // Postconditions:


  // Exit:

  return lstream.str();
}


///
void
fiber_bundle::mesh_partition::
part(const scoped_index& xp_id, id_block& xresult) const
{
  // Preconditions:

  require(mesh().state_is_read_accessible());
  require(mesh().contains_member(part_name(xp_id)));
  require(xresult.is_member_hub_id_space());

  // Body:

  xresult.set_ct(0);
  xresult.reserve(1024); // Arbitrary, avoids many small reallocations.

  mesh_partition* cthis = const_cast<mesh_partition*>(this);
  base_space_member lpart(cthis->_mesh, part_name(xp_id));
  preorder_iterator litr(static_cast<abstract_poset_member&>(lpart), cthis->_mesh->elements(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    xresult.push_back(litr.index());

    litr.truncate();
  }

  lpart.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

///
const sheaf::scoped_index&
fiber_bundle::mesh_partition::
put_part(const scoped_index& xp_id, id_block& xzones)
{
  // Preconditions:

  require(mesh().state_is_read_write_accessible());
  require(!mesh().contains_member(part_name(xp_id)));
  require(xzones.is_member_hub_id_space());

  require_for_all(i, 0, xzones.ct(), mesh().contains_member(xzones[i]));

  // Body:

  base_space_member lpart(_mesh, xzones.base(), xzones.ct(), tern::TRUE, false);

  lpart.put_name(part_name(xp_id), true, false);
  const scoped_index& result = lpart.index();
  _parts.insert_member(result);

  _parts.id_space().insert(xp_id, result);

  lpart.detach_from_state();

  // Postconditions:

  ensure(mesh().contains_member(result));
  ensure(mesh().member_name(result) == part_name(xp_id));
  ensure(parts().contains_member(result));

  // Exit:

  return result;
}


///
sheaf::pod_index_type
fiber_bundle::mesh_partition::
part_id(const string& xname) const
{
  // Preconditions:


  // Body:

  string::size_type lidx1;

  lidx1 = xname.find("::part_") + 7;
  string lpart_id_str(xname.substr(lidx1));

  stringstream lstream(lpart_id_str);

  pod_index_type result;

  lstream >> result;

  // Postconditions:


  // Exit:

  return result;
}


///
bool
fiber_bundle::mesh_partition::
is_valid_name(const string& xname)
{
  bool result;

  // Preconditions:


  // Body:

  result = (xname.find(name_prefix()) == 0);

  // Postconditions:


  // Exit:

  return result;
}

///
string
fiber_bundle::mesh_partition::
name_prefix()
{

  // Preconditions:


  // Body:

  string result(poset_path::reserved_prefix() + "p_");

  // Postconditions:


  // Exit:

  return result;
}

// =============================================================================
// ANY FACET
// =============================================================================

///
bool
fiber_bundle::mesh_partition::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const mesh_partition*>(other) != 0;

  // Postconditions:

  return result;
}

///
fiber_bundle::mesh_partition*
fiber_bundle::mesh_partition::
clone() const
{
  mesh_partition* result;

  // Preconditions:

  // Body:

  result = new mesh_partition();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
fiber_bundle::mesh_partition&
fiber_bundle::mesh_partition::
operator=(const mesh_partition& xother)
{

  // Preconditions:


  // Body:

  _name         = xother._name;
  _mesh         = xother._mesh;
  _parts        = xother._parts;
  _part_ct      = xother._part_ct;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
fiber_bundle::mesh_partition::
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

    invariance(part_ct() >= 0);
    invariance(!name().empty());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}



// =============================================================================
// PRIVATE MEMBER FUNCTIONS FACET
// =============================================================================

///
void
fiber_bundle::mesh_partition::
initialize_parts_set()
{
  // Preconditions:

  require(mesh().includes_subposet(name()) ?
          mesh().state_is_read_accessible() :
          mesh().state_is_read_write_accessible());

  // Body:

  if(mesh().includes_subposet(_name))
  {
    // Parts set already exists; just attach to it.

    _parts.attach_to_state(_mesh, _name);
  }
  else
  {
    // Parts set doesn't exist yet; create it.

    _parts.new_state(_mesh, true, false);
    _parts.put_name(_name, true, false);
    _parts.new_id_space("hash_index_space_state",
			hash_index_space_state::make_arg_list(0));
  }


  // Postconditions:

  ensure(mesh().includes_subposet(name()));
  ensure(parts().has_id_space());

  // Exit:

  return;
}

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

