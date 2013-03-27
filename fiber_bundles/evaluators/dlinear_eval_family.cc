// $RCSfile: dlinear_eval_family.cc,v $ $Revision: 1.30 $ $Date: 2013/03/13 00:58:42 $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class dlinear_eval_family


#include "assert_contract.h"
#include "base_space_member.h"
#include "bilinear_2d.h"
#include "constant_point.h"
#include "dlinear_eval_family.h"
#include "factory.h"
#include "fiber_bundles_namespace.h"
#include "int_set.h"
#include "linear_1d.h"
#include "linear_2d.h"
#include "linear_3d.h"
#include "namespace_poset.h"
#include "sheaf.h"
#include "trilinear_3d.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
fiber_bundle::dlinear_eval_family::
dlinear_eval_family(const dlinear_eval_family& xother)
    : eval_family(xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}



///
fiber_bundle::dlinear_eval_family*
fiber_bundle::dlinear_eval_family::
clone() const
{
  dlinear_eval_family* result;

  // Preconditions:

  // Body:

  result = new dlinear_eval_family(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
fiber_bundle::dlinear_eval_family::
~dlinear_eval_family()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}


///
bool
fiber_bundle::dlinear_eval_family::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && eval_family::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
fiber_bundle::dlinear_eval_family::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const dlinear_eval_family*>(xother) != 0;

  // Postconditions:

  return result;

}



// DLINEAR_FAMILY FACET


///
fiber_bundle::dlinear_eval_family::
dlinear_eval_family(const namespace_poset& xname_space)
{

  // Preconditions:

  require(xname_space.state_is_read_accessible());
  require(xname_space.contains_poset(base_space_member::prototypes_poset_name()));

  // Body:

  initialize(xname_space);

  // Postconditions:

  ensure(invariant());
}

///
const string&
fiber_bundle::dlinear_eval_family::
class_name() const
{
  // Preconditions:

  // Body:

  const string& result = static_class_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const string&
fiber_bundle::dlinear_eval_family::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("dlinear");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
void
fiber_bundle::dlinear_eval_family::
initialize(const namespace_poset& xname_space)
{

  // Preconditions:

  require(!is_initialized());
  require(xname_space.state_is_read_accessible());
  require(xname_space.contains_poset(base_space_member::prototypes_poset_name()));


  // Body:

  eval_family::initialize(xname_space);

  // The type codes used here must be the same as those used
  // in fiber_bundles_namespace::make_base_space_member_prototypes().

  poset* lhost = &xname_space.member_poset<poset>(base_space_member::prototypes_poset_name(), false);
  lhost->get_read_access();

  // Allocate enough storage for the members.

  initialize_members(lhost->member_index_ub().pod());

  // Get the type id of each member of the family and
  // and create the appropriate entry in _members.

  /// @issue Should the compound types be represented separately?
  /// Evaluator_family is supposed to support the notion of a map
  /// from a local cell to an evaluator on that local cell.
  /// The compound cell types, e.g. triangle_nodes and triangle_complex,
  /// are exactly the same type of local cell as triangle. They probably
  /// should have the same cell type id and not appear separately in
  /// this table.

  base_space_member lmbr;
  lmbr.attach_to_state(lhost, "point");
  _members.force_item(lmbr.type_id(), new constant_point);

  lmbr.attach_to_state(lhost, "segment");
  _members.force_item(lmbr.type_id(), new linear_1d);

  lmbr.attach_to_state(lhost, "segment_complex");
  _members.force_item(lmbr.type_id(), new linear_1d);

  lmbr.attach_to_state(lhost, "triangle");
  _members.force_item(lmbr.type_id(), new linear_2d);

  lmbr.attach_to_state(lhost, "triangle_nodes");
  _members.force_item(lmbr.type_id(), new linear_2d);

  lmbr.attach_to_state(lhost, "triangle_complex");
  _members.force_item(lmbr.type_id(), new linear_2d);

  lmbr.attach_to_state(lhost, "quad");
  _members.force_item(lmbr.type_id(), new bilinear_2d);

  lmbr.attach_to_state(lhost, "quad_nodes");
  _members.force_item(lmbr.type_id(), new bilinear_2d);

  lmbr.attach_to_state(lhost, "quad_complex");
  _members.force_item(lmbr.type_id(), new bilinear_2d);

  lmbr.attach_to_state(lhost, "hex");
  _members.force_item(lmbr.type_id(), new trilinear_3d);

  lmbr.attach_to_state(lhost, "hex_nodes");
  _members.force_item(lmbr.type_id(), new trilinear_3d);

  lmbr.attach_to_state(lhost, "hex_complex");
  _members.force_item(lmbr.type_id(), new trilinear_3d);

  lmbr.attach_to_state(lhost, "structured_block_1d");
  _members.force_item(lmbr.type_id(), new linear_1d);

  lmbr.attach_to_state(lhost, "structured_block_2d");
  _members.force_item(lmbr.type_id(), new bilinear_2d);

  lmbr.attach_to_state(lhost, "structured_block_3d");
  _members.force_item(lmbr.type_id(), new trilinear_3d);

  lmbr.attach_to_state(lhost, "tetra");
  _members.force_item(lmbr.type_id(), new linear_3d);

  lmbr.attach_to_state(lhost, "tetra_nodes");
  _members.force_item(lmbr.type_id(), new linear_3d);

  lmbr.attach_to_state(lhost, "tetra_complex");
  _members.force_item(lmbr.type_id(), new linear_3d);

  lmbr.detach_from_state();
  lhost->release_access();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());

  // Exit:

  return;
}

///
bool
fiber_bundle::dlinear_eval_family::
dofs_are_values() const
{
  return true;
}

///
bool
fiber_bundle::dlinear_eval_family::
extrema_are_dofs() const
{
  return true;
}


// ===========================================================
// PRIVATE MEMBERS
// ===========================================================

///
fiber_bundle::dlinear_eval_family::
dlinear_eval_family()
{

  // Preconditions:

  // Body:

  // Nothing to do; base class does it all.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}
