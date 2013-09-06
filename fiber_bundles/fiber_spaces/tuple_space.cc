
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class tuple_space.

#include "tuple_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "tuple.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// TUPLE_SPACE FACET
//==============================================================================

///
const string&
fiber_bundle::tuple_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = tuple::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::tuple_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = tuple::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

fiber_bundle::tuple_space&
fiber_bundle::tuple_space::
new_table(namespace_type& xns, const poset_path& xpath, const poset_path& xschema_path, int xfactor_ct, bool xauto_access)
{
  // cout << endl << "Entering tuple_space::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(xfactor_ct > 0);

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef tuple_space table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("factor_ct", xfactor_ct);
  
  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  tuple_space& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == xfactor_ct);

  // Exit:

  // cout << "Leaving tuple_space::new_table." << endl;
  return result;
}

int
fiber_bundle::tuple_space::
factor_ct() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  int result = sheaf::table_dofs(*this).factor_ct;
  

  // Postconditions:


  // Exit:

  return result;
}

int
fiber_bundle::tuple_space::
factor_ct(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  int result = factor_ct();
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::tuple_space::
tuple_space()
  : poset(new tuple, new tuple)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(poset::poset()));
}

fiber_bundle::tuple_space::
~tuple_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::tuple_space::
tuple_space(tuple* xtop, tuple* xbottom)
  : poset(xtop, xbottom)
{
  // Preconditions:

  require(xtop != 0);
  require(xbottom != 0);
  
  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::poset_state_handle(xtop, xbottom)));
  
  // Exit:

  return;
}

// ===========================================================
// POSET FACET
// ===========================================================
 
bool
fiber_bundle::tuple_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  tuple_space* lproto = new tuple_space;
  poset_type ltype    = lproto->type_id();

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return result;
}

//==============================================================================
// POSET_STATE_HANDLE FACET
//==============================================================================



sheaf::poset_type
fiber_bundle::tuple_space::
type_id() const
{
  return TUPLE_SPACE_ID;
}





///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::tuple_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "tuple_space";

  // Postconditions:

  // Exit:

  return result;
}


//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::tuple_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const tuple_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::tuple_space*
fiber_bundle::tuple_space::
clone() const
{
  tuple_space* result;

  // Preconditions:

  // Body:

  result = new tuple_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::tuple_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(poset::invariant());

    /// @todo finish tuple_space::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}



