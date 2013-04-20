

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class base_space_member.

#include "base_space_member.h"

#include "assert_contract.h"
#include "arg_list.h"
#include "base_space_member_prototype.h"
#include "base_space_poset.h"
#include "fiber_bundles_namespace.h"
#include "poset_path.h"
#include "preorder_iterator.h"
#include "tern.h"
#include "wsv_block.h"

using namespace fiber_bundle;

// ===========================================================
// BASE_SPACE_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::base_space_member::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result =
    fiber_bundles_namespace::standard_base_space_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::poset_path&
fiber_bundle::base_space_member::
standard_schema_path()
{

  // Preconditions:

  // Body:

  static const poset_path result(standard_schema_poset_name(),
                                 "base_space_member_schema");

  // Postconditions:

  // Exit

  return result;
}


const sheaf::poset_path&
fiber_bundle::base_space_member::
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
fiber_bundle::base_space_member::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string ldof_specs = "max_db INT true";
  ldof_specs       += " db INT false";
  ldof_specs       += " type_id INT false";
  ldof_specs       += " type_name C_STRING false";
  ldof_specs       += " refinement_depth INT false";


  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              poset_path(standard_schema_poset_name(), "bottom"),
                              ldof_specs,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path(), false));

  // Exit:

  return;
}

const string&
fiber_bundle::base_space_member::
prototypes_poset_name()
{

  // Preconditions:

  // Body:

  static const string& result =
    fiber_bundles_namespace::standard_base_space_member_prototypes_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit

  return result;
}

fiber_bundle::base_space_member::
base_space_member()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(! is_attached() );
}


fiber_bundle::base_space_member::
base_space_member(const abstract_poset_member& xother,
		  bool xnew_jem,
		  bool xauto_access)
{

  // Preconditions:

  require(xnew_jem ? xother.is_attached() : true);

  // Body:

  if(xnew_jem)
  {
    new_jem_state(const_cast<abstract_poset_member*>(&xother), true, xauto_access);
  }
  else
  {
    attach_to_state(&xother);
  }

  // postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

fiber_bundle::base_space_member::
~base_space_member()
{

  // Preconditions:

  // Body:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

fiber_bundle::base_space_member::
base_space_member(poset* xhost,
                  array_poset_dof_map* xdof_map,
                  bool xcopy_dof_map,
                  bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_map, xcopy_dof_map, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(same args)));

  // Exit:

  return;
}


fiber_bundle::base_space_member::
base_space_member(poset* xhost,
                  const string& xprototype_name,
                  bool xis_prototype_name,
                  bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);
  require(xauto_access ? xhost->is_attached() : xhost->in_jim_edit_mode());
  require(xauto_access || xhost->name_space()->member_poset(prototypes_poset_name(), true).state_is_read_accessible());
  require(!xprototype_name.empty());
  require(xhost->name_space()->contains_poset_member(poset_path(prototypes_poset_name(), xprototype_name), true));


  // Body:

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode(true);
    xhost->name_space()->member_poset(prototypes_poset_name(), true).get_read_access();
  }

  array_poset_dof_map* lmap = new_row_dof_map(xhost, xprototype_name);
  new_jim_state(xhost, lmap, false, false);

  if(xauto_access)
  {
    xhost->name_space()->member_poset(prototypes_poset_name(), true).release_access();
    xhost->end_jim_edit_mode(true, true);
  }

  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::base_space_member::
base_space_member(poset* xhost,
                  const scoped_index& xdof_tuple_id,
                  bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_tuple_id, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(same args)));

  // Exit:

  return;
}

fiber_bundle::base_space_member::
base_space_member(poset* xhost,
                  scoped_index* xexpansion,
                  int xexpansion_ct,
                  const tern& xnew_jem,
                  bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jrm_state(same args)));

  // Body:

  new_jrm_state(xhost, xexpansion, xexpansion_ct, xnew_jem, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jrm_state(same args)));

  // Exit:

  return;
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

fiber_bundle::base_space_member::
base_space_member(const poset* xhost, pod_index_type xhub_id)
{

  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xhub_id)));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xhub_id)));
}

fiber_bundle::base_space_member::
base_space_member(const poset* xhost, const scoped_index& xid)
{

  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xid)));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xid)));
}

fiber_bundle::base_space_member::
base_space_member(const poset* xhost, const string& xname)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}

fiber_bundle::base_space_member::
base_space_member(const namespace_poset* xnamespace, const poset_path& xpath)
{

  // Preconditions:

  /// @error how do we require that the host schema conforms to SCHEMA_PATH?

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xpath);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::base_space_member::
base_space_member(const namespace_poset* xnamespace,
                  pod_index_type xposet_id,
                  pod_index_type xmember_id)
{

  // Preconditions:

  /// @error how do we require that the host schema conforms to SCHEMA_PATH?

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xposet_id, xmember_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::base_space_member::
base_space_member(const namespace_poset* xnamespace,
                  const scoped_index& xposet_id,
                  const scoped_index& xmember_id)
{

  // Preconditions:

  /// @error how do we require that the host schema conforms to SCHEMA_PATH?

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace,
		  xposet_id.hub_pod(),
		  xmember_id.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

// EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

// FEATURES

sheaf::poset_path
fiber_bundle::base_space_member::
prototype_path(const namespace_poset* xnamespace,
               const namespace_relative_member_index& xid)
{
  // Preconditions:

  require(xnamespace->state_is_read_accessible());
  require(xnamespace->contains_poset_member(xid.poset_id, xid.member_id));

  // Body:

  /// @error we need read access to the prototypes poset here,
  /// but how do we require it? How do we avoid requesting it?

  base_space_member lproto(xnamespace, xid.poset_id, xid.member_id);
  lproto.get_read_access();

  poset_path result(lproto.path());

  lproto.release_access();
  lproto.detach_from_state();

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::base_space_member::
prototype_exists(const string& xname, bool xauto_access)
{
  bool result;

  // Preconditions:


  // Body:

  poset_path lproto_path(prototypes_poset_name(), xname);

  result = lproto_path.member_exists(xauto_access);

  // Postconditions:


  // Exit:

  return result;
}


fiber_bundle::base_space_member::row_dof_tuple_type*
fiber_bundle::base_space_member::
row_dof_tuple(bool xrequire_write_access)
{
  row_dof_tuple_type* result;

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() : state_is_read_accessible());
  require(is_jim(false));

  // Body:

  result =
    reinterpret_cast<row_dof_tuple_type*>(dof_map().dof_tuple());

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}


fiber_bundle::base_space_member::row_dof_tuple_type*
fiber_bundle::base_space_member::
row_dof_tuple(poset_state_handle* xhost,
              pod_index_type xhub_id,
              bool xrequire_write_access)
{
  row_dof_tuple_type* result;

  // Preconditions:

  require(xhost != 0);
  require(xrequire_write_access ?
          xhost->state_is_read_write_accessible() :
          xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));
  require(xhost->is_jim(xhub_id, false));

  // Body:

  poset_dof_map& ldof_map = xhost->member_dof_map(xhub_id, xrequire_write_access);
  result = reinterpret_cast<row_dof_tuple_type*>(ldof_map.dof_tuple());

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

fiber_bundle::base_space_member::row_dof_tuple_type*
fiber_bundle::base_space_member::
row_dof_tuple(poset_state_handle* xhost,
              const scoped_index& xid,
              bool xrequire_write_access)
{
  row_dof_tuple_type* result;

  // Preconditions:

  require(xhost != 0);
  require(xrequire_write_access ?
          xhost->state_is_read_write_accessible() :
          xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));
  require(xhost->is_jim(xid, false));

  // Body:

  result = row_dof_tuple(xhost, xid.hub_pod(), xrequire_write_access);

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

sheaf::array_poset_dof_map*
fiber_bundle::base_space_member::
new_row_dof_map(const poset* xhost, const string& xprototype_name)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->name_space()->member_poset(prototypes_poset_name(), true).state_is_read_accessible());
  require(!xprototype_name.empty());
  require(xhost->name_space()->member_poset(prototypes_poset_name(), true).contains_member(xprototype_name));


  // Body:

  /// @todo replace with call to base_space_poset::new_row_dof_map(xprototype_name)
  /// when host signature is changed to base_space_poset.

  // Create the dof map.

  array_poset_dof_map* result = new array_poset_dof_map(xhost, false);
  result->put_defaults();

  // Get a handle for the prototype.

  poset_path lproto_path(prototypes_poset_name(), xprototype_name);
  base_space_member_prototype lproto(xhost->name_space(), lproto_path, true);

  // Initialize the dofs.

  row_dof_tuple_type& ltuple =
    *reinterpret_cast<row_dof_tuple_type*>(result->dof_tuple());

  ltuple.db               = lproto.db();
  ltuple.type_id          = lproto.type_id();
  ltuple.type_name        = strdup(lproto.type_name());
  ltuple.refinement_depth = lproto.refinement_depth();

  lproto.detach_from_state();

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

const sheaf::scoped_index&
fiber_bundle::base_space_member::
new_row_dof_map(poset_state_handle& xhost, const string& xprototype_name, bool xauto_access)
{
  // Preconditions:

  require(xhost.state_is_auto_read_write_accessible(xauto_access));
  require(xhost.name_space()->member_poset(prototypes_poset_name(), true).state_is_auto_read_accessible(xauto_access));
  require(!xprototype_name.empty());
  require(xhost.name_space()->member_poset(prototypes_poset_name(), true).contains_member(xprototype_name));


  // Body:

  if(xauto_access)
  {
    xhost.get_read_write_access();
    xhost.name_space()->get_read_access();
    xhost.name_space()->member_poset(prototypes_poset_name(), false).get_read_access();
  }

  define_old_variable(int old_xhost_row_dof_tuple_ct = xhost.row_dof_tuple_ct());

  // Create the dof map and set dofs to defaults.

  const scoped_index& result = xhost.new_row_dof_map();
  row_dof_tuple_type* ltuple =
    reinterpret_cast<row_dof_tuple_type*>(xhost.row_dof_map(result, true).dof_tuple());

  // Get the prototype.

  poset_path lproto_path(prototypes_poset_name(), xprototype_name);
  base_space_member_prototype lproto(xhost.name_space(), lproto_path, false);

  // Copy its dofs.

  ltuple->db               = lproto.db();
  ltuple->type_id          = lproto.type_id();
  ltuple->type_name        = strdup(lproto.type_name());
  ltuple->refinement_depth = lproto.refinement_depth();

  // Release the prototype.

  lproto.detach_from_state();

  if(xauto_access)
  {
    xhost.name_space()->member_poset(prototypes_poset_name(), false).release_access();
    xhost.name_space()->release_access();
    xhost.release_access();
  }

  // Postconditions

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ROW DOFS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::base_space_member::
db() const
{
  int result = -1;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(is_jim(false))
  {
    // Dimension is a dof.

    base_space_member* cthis = const_cast<base_space_member*>(this);
    result = cthis->row_dof_tuple()->db;
  }
  else
  {
    // Dimension is max dimension of maximal jims in downset.

    preorder_iterator itr(*this, "jims", DOWN, NOT_STRICT);
    while(!itr.is_done())
    {
      pod_index_type ldof_tuple_id =
	host()->member_dof_tuple_id(itr.index().hub_pod(), false);

      array_poset_dof_map& lmap =
        reinterpret_cast<array_poset_dof_map&>(host()->row_dof_map(ldof_tuple_id));

      int lmbr_dim =
        reinterpret_cast<row_dof_tuple_type*>(lmap.dof_tuple())->db;

      result = lmbr_dim > result ? lmbr_dim : result;

      // Only need to look at the maximal jims.

      itr.truncate();
    }
  }

  // Postconditions:

  ensure(result >= -1);
  ensure( (result == -1) == is_jem(&(host()->bottom())) );

  // Exit

  return result;
}

const sheaf::pod_index_type&
fiber_bundle::base_space_member::
type_id() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(false));

  // Body:

  base_space_member* cthis = const_cast<base_space_member*>(this);
  const pod_index_type& result = cthis->row_dof_tuple()->type_id;

  // Postconditions:

  // Exit

  return result;
}

const char*
fiber_bundle::base_space_member::
type_name() const
{

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(false));

  // Body:

  base_space_member* cthis = const_cast<base_space_member*>(this);
  const char* result = cthis->row_dof_tuple(false)->type_name;

  // Postconditions:


  // Exit:

  return result;
}

int
fiber_bundle::base_space_member::
refinement_depth() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(false));

  // Body:

  base_space_member* cthis = const_cast<base_space_member*>(this);
  int result = cthis->row_dof_tuple()->refinement_depth;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::base_space_member::
put_refinement_depth(int xdepth)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim(false));

  // Body:

  row_dof_tuple()->refinement_depth = xdepth;

  // Postconditions:

  ensure(refinement_depth() == xdepth);

  // Exit:

  return;
}

sheaf::poset_path
fiber_bundle::base_space_member::
prototype_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  /// @todo make schema conformance precondition executable.

  // Body:

  poset_path result(prototypes_poset_name(), type_name());

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// CELLULAR SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::base_space_member::
d_cells_ct(block<size_type>& xresult, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  int lmax_db = lhost->max_db();
  xresult.reserve(lmax_db);
  xresult.set_ct(lmax_db);
  xresult.assign(0);

  preorder_iterator litr(*this, lhost->jims(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    int lmbr_db = lhost->db(litr.index());
    xresult[lmbr_db]++;
    litr.next(lmbr_db == 0);
  }

  // Postconditions:

  /// @todo enable when base_space_member::host is type base_space_poset.

  ensure(unexecutable(xresult.ct() == host()->max_db()));

  // Exit:

  return;
}

fiber_bundle::base_space_member*
fiber_bundle::base_space_member::
c_not(bool xauto_access)
{
  base_space_member* result;

  // Preconditions:

  require(is_attached());
  require(xauto_access || state_is_read_write_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_write_access();
  }

  result = clone();
  c_not_pa(*result, false);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(c_not_pa(result, false)));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_member::
c_not_pa(base_space_member& result, bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(xauto_access || state_is_read_write_accessible());

  if(xauto_access)
  {
    get_read_write_access();
  }

  require(host()->includes_subposet("__elements"));

  // Body:

  // Find all the zones that are not contained in this:
  // make a copy of all zones and removes those contained in this.

  subposet lall_zones(host(), "__elements");
  subposet lother_zones(lall_zones, true);

  preorder_iterator litr(*this, host()->jims(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    lother_zones.remove_member(litr.index());

    // Zones are maximal jimes, so if we've
    // already found one, no need to go deeper.

    litr.truncate();
  }

  if(!lother_zones.is_empty())
  {
    // Join them to form the result.

    lother_zones.l_join_pa(&result, false);
  }
  else
  {
    // Complement is empty; result is bottom.

    result.attach_to_state(&host()->bottom());
  }

  // Clean up.

  lother_zones.delete_state();
  lall_zones.detach_from_state();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable(this->join(&result)->is_same_state(&host()->top())));

  // Exit:

  return;
}

fiber_bundle::base_space_member*
fiber_bundle::base_space_member::
c_minus(base_space_member& xother, bool xnew_jem, bool xauto_access)
{
  base_space_member* result;

  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(in_same_space(&xother));

  // Body:

  if(xauto_access)
  {
    get_read_write_access();
  }

  result = clone();
  c_minus(xother, *result, xnew_jem, false);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(c_not_pa(xother, result, false)));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_member::
c_minus(base_space_member& xother,
        base_space_member& result,
        bool xnew_jem,
        bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(in_same_space(&xother));

  if(xauto_access)
  {
    get_read_write_access();
  }

  require(host()->includes_subposet("__elements", xauto_access));

  // Body:

  // Find all the zones in this.

  subposet lzones(host());

  preorder_iterator litr(*this, "__elements", DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    lzones.insert_member(litr.index());
    litr.truncate();
  }

  // Reset the iterator to iterate over xother.
  // Turn off visit_once so we don't have to
  // pay the cost of resetting the visited bit vector.

  litr.put_anchor(xother.index());
  litr.put_visit_once(false);
  litr.reset(false);

  while(!litr.is_done())
  {
    lzones.remove_member(litr.index());
    litr.truncate();
  }

  lzones.l_join_pa(&result, xnew_jem);

  // Clean up.

  lzones.delete_state();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable(this->join(&result)->is_same_state(&host()->top())));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// TOTAL_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ABSTRACT_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEGREE OF FREEDOM (DOF) TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::array_poset_dof_map&
fiber_bundle::base_space_member::
dof_map(bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  array_poset_dof_map& result =
    reinterpret_cast<array_poset_dof_map&>(total_poset_member::dof_map());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::array_poset_dof_map&
fiber_bundle::base_space_member::
dof_map(bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  const array_poset_dof_map& result =
    reinterpret_cast<const array_poset_dof_map&>(total_poset_member::dof_map());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::base_space_member::
dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  // This handle requires xdof_map to be of type array_poset_dof_map.

  result = dynamic_cast<const array_poset_dof_map*>(xdof_map) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::poset*
fiber_bundle::base_space_member::
host() const
{
  poset* result;

  // Preconditions:

  // Body:

  result = reinterpret_cast<poset*>(total_poset_member::host());

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::base_space_member::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  require(xother != 0);

  // Body:

  result = dynamic_cast<const poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::base_space_member::
invariant() const
{
  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(total_poset_member::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    /// @issue what are the invariants for this class
    /// @todo implement base_space_member::invariant() const

    /// @issue how do we enforce the invariance(nae space is fiber bundles)?

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return true;
}

bool
fiber_bundle::base_space_member::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const base_space_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::base_space_member*
fiber_bundle::base_space_member::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  base_space_member *result = new base_space_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

fiber_bundle::base_space_member&
fiber_bundle::base_space_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

fiber_bundle::base_space_member&
fiber_bundle::base_space_member::
operator=(const base_space_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

