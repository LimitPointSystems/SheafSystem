
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class material_decomposition

#include "material_decomposition.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "error_message.h"
#include "hash_index_space_state.h"
#include "id_block.h"
#include "index_iterator.h"
#include "preorder_iterator.h"
#include "std_set.h"
#include "std_sstream.h"
#include "stl_scoped_index.h"
#include "tern.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

// =============================================================================
// MATERIAL_DECOMPOSITION FACET
// =============================================================================

///
fiber_bundle::material_decomposition::
material_decomposition()
{

  // Preconditions:


  // Body:

  _material_ct = 0;
  _mesh = 0;

  //$$SCRIBBLE: Adding a nonempty string to keep
  //            invariant() from blowing an assertion.

  _name = "unknown";


  // Postconditions:

  ensure(!name().empty());
  ensure(invariant());
  ensure(material_ct() == 0);

  // Exit:

  return;
}


///
fiber_bundle::material_decomposition::
material_decomposition(const material_decomposition& xother)
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
fiber_bundle::material_decomposition::
~material_decomposition()
{
  // Preconditions:


  // Body:

  _materials.detach_from_state();
  _mixed_materials.detach_from_state();
  _pure_materials.detach_from_state();

  // Postconditions:

  // Exit:

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

///
fiber_bundle::material_decomposition::
material_decomposition(const base_space_poset& xmesh, const string& xname)
{
  // Preconditions:

  require(is_valid_name(xname));
  require(xmesh.includes_subposet(xname) ?
          xmesh.state_is_read_accessible() :
          xmesh.state_is_read_write_accessible());

  // Body:

  bool old_xmesh_includes_material_decomposition_xname = xmesh.includes_subposet(xname);

  _mesh = const_cast<base_space_poset*>(&xmesh);
  _name = xname;


  initialize_materials_set();
  initialize_mixed_materials_set();
  initialize_pure_materials_set();

  _material_ct = (old_xmesh_includes_material_decomposition_xname ? _materials.member_ct() : 0);

  // Postconditions:

  ensure(mesh().is_same_state(&xmesh));
  ensure(name() == xname);
  ensure(xmesh.includes_subposet(xname));
  ensure(material_ct() == (old_xmesh_includes_material_decomposition_xname ? materials().member_ct() : 0));


  return;
}


///
const string&
fiber_bundle::material_decomposition::
name() const
{
  return _name;
}


///
const fiber_bundle::base_space_poset&
fiber_bundle::material_decomposition::
mesh() const
{
  return *_mesh;
}

///
const sheaf::subposet&
fiber_bundle::material_decomposition::
materials() const
{
  return _materials;
}

///
int
fiber_bundle::material_decomposition::
material_ct() const
{
  return _material_ct;
}


///
string
fiber_bundle::material_decomposition::
material_name(const scoped_index& xp_id) const
{
  // Preconditions:


  // Body:

  stringstream lstream;
  lstream << _name << "::material_" << xp_id;

  // Postconditions:


  // Exit:

  return lstream.str();
}


///
void
fiber_bundle::material_decomposition::
material(const scoped_index& xp_id, id_block& xresult) const
{
  // Preconditions:

  require(mesh().state_is_read_accessible());
  require(mesh().contains_member(material_name(xp_id)));
  require(xresult.is_member_hub_id_space());

  // Body:

  xresult.set_ct(0);
  xresult.reserve(1024); // Arbitrary, avoids many small reallocations.

  material_decomposition* cthis = const_cast<material_decomposition*>(this);
  base_space_member lmaterial(cthis->_mesh, material_name(xp_id));
  preorder_iterator litr(static_cast<abstract_poset_member&>(lmaterial), cthis->_mesh->elements(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    xresult.push_back(litr.index());

    litr.truncate();
  }

  lmaterial.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}


///
const sheaf::scoped_index&
fiber_bundle::material_decomposition::
put_material(const scoped_index& xp_id, id_block& xzones)
{
  // Preconditions:

  require(mesh().state_is_read_write_accessible());
  require(!mesh().contains_member(material_name(xp_id)));
  require(xzones.is_member_hub_id_space());

  require_for_all(i, 0, xzones.ct(), mesh().contains_member(xzones[i]));

  // Body:

  base_space_member lmaterial(_mesh, xzones.base(), xzones.ct(), tern::TRUE, false);

  lmaterial.put_name(material_name(xp_id), true, false);
  const scoped_index& result = lmaterial.index();
  _materials.insert_member(result);

  _materials.id_space().insert(xp_id, result);

  lmaterial.detach_from_state();

  // Postconditions:

  ensure(mesh().contains_member(result));
  ensure(mesh().member_name(result) == material_name(xp_id));
  ensure(materials().contains_member(result));

  // Exit:

  return result;
}


///
sheaf::pod_index_type
fiber_bundle::material_decomposition::
material_id(const string& xname) const
{
  // Preconditions:


  // Body:

  string::size_type lidx1;

  lidx1 = xname.find("::material_") + 7;
  string lmaterial_id_str(xname.substr(lidx1));

  stringstream lstream(lmaterial_id_str);

  pod_index_type result;
  lstream >> result;

  // Postconditions:


  // Exit:

  return result;
}


///
const sheaf::subposet&
fiber_bundle::material_decomposition::
mixed_materials() const
{
  return _mixed_materials;
}

///
const sheaf::subposet&
fiber_bundle::material_decomposition::
pure_materials() const
{
  return _pure_materials;
}

///
bool
fiber_bundle::material_decomposition::
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
fiber_bundle::material_decomposition::
name_prefix()
{

  // Preconditions:


  // Body:

  string result(poset_path::reserved_prefix() + "md_");

  // Postconditions:


  // Exit:

  return result;
}

///
void
fiber_bundle::material_decomposition::
compute_mixed_materials()
{
  // Preconditions:

  require(mesh().state_is_read_write_accessible());

  // Body:

  // Compute coarsest common refinement (CCR) of materials:
  // Let Z be the set of zones and z1, z2 be members of Z.
  // Define z1 ~ z2 iff z1 and z2 have the same upper cover.
  // then ~ is an equivalence relation and the CCR is the quotient Z/~.
  // That is, ~ partitions Z into equivalence classes and each member of
  // the CCR corresponds to one of these equivalence classes.
  // So we have to find the equivalence classes (distinct upper covers)
  // and then sort the zones into them.

  /// @issue the following implementation is a simple first cut, but
  /// there are several efficiency issues associated with it. Explicitly
  /// constructing the equivalence classes in separate storage uses too much
  /// memory. Constructing the ccr members by explicit joins uses too much time
  /// for at least 2 reasons: (1) each join is going to initialize subposets,
  /// making the performance ccr.ct()*zones.ct() and (2) each join is going
  /// to examine the entire down set (e.g. edges and vertices) which is
  /// not necessary.

  /// @todo reimplement using traversal and direct link editing.

  // Allocate a map from upper covers to equivalence classes.

  typedef map<set< stl_scoped_index<> >, block<scoped_index> > ec_map_type;
  ec_map_type lec_map;

  // Iterate over the zones and construct the equivalence classes.

  base_space_member lzone(_mesh, TOP_INDEX);

  subposet& lzones_sp = _mesh->elements();
  index_iterator lzones_itr = lzones_sp.indexed_member_iterator();
  while(!lzones_itr.is_done())
  {
    lzone.attach_to_state(lzones_itr.index());

    // Create a set containing the upper cover of the current zone.
    /// @hack initializing iterator for every zone makes this algorithm O(n**2).

    set< stl_scoped_index<> > lup_set;
    preorder_iterator lup_itr(lzone, &_materials, sheaf::UP);
    while(!lup_itr.is_done())
    {
      lup_set.insert(lup_itr.index());
      lup_itr.truncate();
    }

    // Insert the current zone into the associated equivalence class.

    lec_map[lup_set].push_back(lzones_itr.index());

    lzones_itr.next();
  }
  lzone.detach_from_state();
  lzones_sp.detach_from_state();

  // Now create the members of the ccr by joining the members
  // of each equivalence class.

  base_space_member lccr_mbr(_mesh->top()); // Any member will do.

  int lccr_ct = 0;
  ec_map_type::iterator lec_itr = lec_map.begin();
  while(lec_itr != lec_map.end())
  {
    block<scoped_index>& lec = lec_itr->second;
    lccr_mbr.new_jrm_state(lec.base(), lec.ct(), tern::FALSE, false);
    if(lec_itr->first.size() == 1)
    {
      // This is a pure material

      // Give it a name..

      stringstream lstream;
      lstream << _name
	      << "::pure_material_"
	      << _materials.id_space().pod(*(lec_itr->first.begin()));
      lccr_mbr.put_name(lstream.str(), true, false);

      // Put it in the pure materials set.

      _pure_materials.insert_member(lccr_mbr.index());
    }
    else
    {
      // This is a mixed material

      // Give it a name..

      stringstream lstream;
      lstream << _name << "::mixed_material";

      ec_map_type::key_type::const_iterator lmat_itr = lec_itr->first.begin();
      while(lmat_itr != lec_itr->first.end())
      {
        lstream << "_" << _materials.id_space().pod(*lmat_itr);
        ++lmat_itr;
      }
      lccr_mbr.put_name(lstream.str(), true, false);

      // Put it in the mixed materials set.

      _mixed_materials.insert_member(lccr_mbr.index());
    }

    ++lec_itr;
  }
  lccr_mbr.detach_from_state();

  // Create the mixed materials member.

  poset_member* lmixed = _mixed_materials.l_join(true);
  lmixed->put_name(mixed_materials_name(), true, false);
  lmixed->detach_from_state();

  // Postconditions:


  // Exit:

  return;
}


// =============================================================================
// ANY FACET
// =============================================================================

///
bool
fiber_bundle::material_decomposition::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const material_decomposition*>(other) != 0;

  // Postconditions:

  return result;
}

///
fiber_bundle::material_decomposition*
fiber_bundle::material_decomposition::
clone() const
{
  material_decomposition* result;

  // Preconditions:

  // Body:

  result = new material_decomposition();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
fiber_bundle::material_decomposition&
fiber_bundle::material_decomposition::
operator=(const material_decomposition& xother)
{

  // Preconditions:


  // Body:

  _name         = xother._name;
  _mesh         = xother._mesh;
  _materials        = xother._materials;
  _material_ct      = xother._material_ct;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
fiber_bundle::material_decomposition::
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

    invariance(material_ct() >= 0);
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
fiber_bundle::material_decomposition::
initialize_materials_set()
{
  // Preconditions:

  require(mesh().includes_subposet(name()) ?
          mesh().state_is_read_accessible() :
          mesh().state_is_read_write_accessible());

  // Body:

  if(mesh().includes_subposet(_name))
  {
    // Materials set already exists; just attach to it.

    _materials.attach_to_state(_mesh, _name);
  }
  else
  {
    // Materials set doesn't exist yet; create it.

    _materials.new_state(_mesh, true, false);
    _materials.put_name(_name, true, false);
    _materials.new_id_space("hash_index_space_state",
			    hash_index_space_state::make_arg_list(0));
  }


  // Postconditions:

  ensure(mesh().includes_subposet(name()));
  ensure(materials().has_id_space());

  // Exit:

  return;
}

///
string
fiber_bundle::material_decomposition::
mixed_materials_name()
{
  string result;

  // Preconditions:

  // Body:

  result = _name + "::mixed_materials";

  // Postconditions:


  // Exit:

  return result;
}


///
void
fiber_bundle::material_decomposition::
initialize_mixed_materials_set()
{
  // Preconditions:

  require(mesh().includes_subposet(name()) ?
          mesh().state_is_read_accessible() :
          mesh().state_is_read_write_accessible());

  // Body:

  string lname = mixed_materials_name();

  if(mesh().includes_subposet(lname))
  {
    // Materials set already exists; just attach to it.

    _materials.attach_to_state(_mesh, lname);
  }
  else
  {
    // Materials set doesn't exist yet; create it.

    _mixed_materials.new_state(_mesh, true, false);
    _mixed_materials.put_name(lname, true, false);
    _mixed_materials.new_id_space("hash_index_space_state",
				  hash_index_space_state::make_arg_list(0));
  }


  // Postconditions:

  ensure(mesh().includes_subposet(name()));
  ensure(materials().has_id_space());

  // Exit:

  return;
}

///
string
fiber_bundle::material_decomposition::
pure_materials_name()
{
  string result;

  // Preconditions:

  // Body:

  result = _name + "::pure_materials";

  // Postconditions:


  // Exit:

  return result;
}


///
void
fiber_bundle::material_decomposition::
initialize_pure_materials_set()
{
  // Preconditions:

  require(mesh().includes_subposet(name()) ?
          mesh().state_is_read_accessible() :
          mesh().state_is_read_write_accessible());

  // Body:

  string lname = pure_materials_name();

  if(mesh().includes_subposet(lname))
  {
    // Materials set already exists; just attach to it.

    _materials.attach_to_state(_mesh, lname);
  }
  else
  {
    // Materials set doesn't exist yet; create it.

    _pure_materials.new_state(_mesh, true, false);
    _pure_materials.put_name(lname, true, false);
    _pure_materials.new_id_space("hash_index_space_state",
				 hash_index_space_state::make_arg_list(0));
  }


  // Postconditions:

  ensure(mesh().includes_subposet(name()));
  ensure(materials().has_id_space());

  // Exit:

  return;
}

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

