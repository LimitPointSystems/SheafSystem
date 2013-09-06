
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class at1_space.

#include "at1_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0_space.h"
#include "at1.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// AT1_SPACE FACET public member functions
//==============================================================================

///
const string&
fiber_bundle::at1_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = at1::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::at1_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = at1::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

fiber_bundle::at1_space&
fiber_bundle::at1_space::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path, 
          const poset_path& xscalar_space_path, 
          bool xauto_access)
{
  // cout << endl << "Entering at1_space::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(xns.path_is_auto_read_accessible<scalar_space_type>(xscalar_space_path, xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef at1_space table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Get the dimension (== number of row dofs) defined by the schema.

  int ld = lschema.row_dof_ct();

  // Get the dimension of the domain vector space.
  // For AT1, the tensor space and the domain vector space are the same thing.

  int ldd = ld;

  // The tensor degree is 1

  int lp = 1;
  
  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("factor_ct", ld);
  lmap->put_dof("d", ld);
  lmap->put_dof("scalar_space_path", xscalar_space_path);
  lmap->put_dof("p", lp);
  lmap->put_dof("dd", ldd);
  lmap->put_dof("vector_space_path", xpath);
  
  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  at1_space& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));
  ensure(result.scalar_space_path(true) == xscalar_space_path);
  ensure(result.p(true) == 1);
  ensure(result.dd(true) == result.d(true));
  ensure(result.vector_space_path(true) == xpath );

  // Exit:

  // cout << "Leaving at1_space::new_table." << endl;
  return result;
} 

// ===========================================================
// AT1_SPACE FACET protected member functions
// ===========================================================
 
fiber_bundle::at1_space::
at1_space()
  : atp_space(new at1, new at1)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(atp_space::atp_space()));
}



fiber_bundle::at1_space::
at1_space(const at1_space& xother)
  : atp_space(new at1, new at1)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::at1_space::
~at1_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::at1_space::
at1_space(at1* xtop, at1* xbottom)
  : atp_space(xtop, xbottom)
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
// TP_SPACE FACET public member functions
// ===========================================================


// ===========================================================
// TP_SPACE FACET protected member functions
// ===========================================================
 

// ===========================================================
// POSET FACET
// =========================================================== 

bool
fiber_bundle::at1_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  at1_space* lproto = new at1_space;
  poset_type ltype = lproto->type_id();

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
fiber_bundle::at1_space::
type_id() const
{
  return AT1_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::at1_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "at1_space";

  // Postconditions:

  // Exit:

  return result;
}

///
sheaf::pod_index_type
fiber_bundle::at1_space::
prereq_id(int xi) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(name_space()->state_is_read_accessible());

  // Body:

  pod_index_type result;

  switch(xi)
  {
    case 0:

      // The first prerequisite is always the schema.

      result = schema().host()->index().pod();
      break;

    case 1:
	
	// The vector space over which this tensor space is built.

      result = name_space()->member_id(scalar_space_path().poset_name(), false);
      break;

    default:

      // No other prerequisites.

      result = invalid_pod_index();
      break;
  }

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::at1_space&
fiber_bundle::at1_space::
operator=(const poset_state_handle& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  poset_state_handle::operator=(xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return *this;
}

//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::at1_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const at1_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::at1_space*
fiber_bundle::at1_space::
clone() const
{
  at1_space* result;

  // Preconditions:

  // Body:

  result = new at1_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::at1_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(atp_space::invariant());

    invariance(state_is_read_accessible() ? p() == 1 : true);
    invariance(state_is_read_accessible() ? vector_space_path().poset_name() == name() : true);
    
    enable_invariant_check();
  }

  return result;
}


