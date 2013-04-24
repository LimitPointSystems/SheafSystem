
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class tuple_space.

#include "tuple_space.h"

#include "abstract_poset_member.impl.h"
#include "arg_list.h"
#include "assert_contract.h"
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

sheaf::arg_list
fiber_bundle::tuple_space::
make_arg_list(int xfactor_ct)
{
  // Preconditions:


  // Body:

  arg_list result;
  result << "factor_ct" <<  xfactor_ct;
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "tuple_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(result.value("factor_ct") == xfactor_ct);
  ensure(unexecutable("result.conforms_to(schema of this class)"));
  
  // Exit:

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
tuple_space(const tuple_space& xother)
  : poset(new tuple, new tuple)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
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

//==============================================================================
// NEW HANDLE, NEW STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::tuple_space::
tuple_space(namespace_poset& xhost,
	    const string& xname,
	    const arg_list& xargs,
	    const poset_path& xschema_path,
	    bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_state(same args)));

  require(xargs.value("factor_ct").value().int_primitive >= 0);

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::tuple_space::
tuple_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : poset(new tuple, new tuple)
{
  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));
  require(xhost.contains_member(xindex, xauto_access));

  if(xauto_access)
  {
    xhost.get_read_access();
  }
  
  require(xhost.is_jim(xindex));

  // Body:

  attach_to_state(&xhost, xindex);

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(host() == &xhost);
  ensure(index() == xindex);
}

fiber_bundle::tuple_space::
tuple_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : poset(new tuple, new tuple)
{
  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));
  require(xhost.contains_member(xindex, xauto_access));

  if(xauto_access)
  {
    xhost.get_read_access();
  }
  
  require(xhost.is_jim(xindex));

  // Body:

  attach_to_state(&xhost, xindex.hub_pod());

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(host() == &xhost);
  ensure(index() ==~ xindex);
}

fiber_bundle::tuple_space::
tuple_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : poset(new tuple, new tuple)
{
  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));
  require(xhost.contains_member(xname));

  // Body:


  if(xauto_access)
  {
    xhost.get_read_access();
  }

  attach_to_state(&xhost, xname);

  // Postconditions:

  ensure(host() == &xhost);
  ensure(name() == xname);

  if(xauto_access)
  {
    xhost.release_access();
  }
}



fiber_bundle::tuple_space::
tuple_space(const namespace_poset_member& xmbr, bool xauto_access)
  : poset(new tuple, new tuple)
{
  // Preconditions:

  require(xmbr.state_is_auto_read_accessible(xauto_access));

  // Body:


  if(xauto_access)
  {
    xmbr.get_read_access();
  }

  attach_to_state(&xmbr);

  if(xauto_access)
  {
    xmbr.release_access();
  }

  // Postconditions:

  ensure(index() ==~ xmbr.index());
}

// ===========================================================
// POSET FACET
// ===========================================================
 
///
void
fiber_bundle::tuple_space::
new_state(namespace_poset& xhost,
          const string& xname,
          const arg_list& xargs,
          const poset_path& xschema_path,
          bool xauto_access)
{

  // Preconditions:

  require(xhost.state_is_auto_read_write_accessible(xauto_access));
  require(xschema_path.full());
  require(xschema_path.poset_name() == standard_schema_poset_name());
  require(xhost.contains_poset_member(xschema_path, xauto_access));
  require(xhost.member_poset(xschema_path, xauto_access).state_is_auto_read_accessible(xauto_access));
  require(schema_poset_member::conforms_to(xhost, xschema_path, standard_schema_path(), xauto_access));

  require(xargs.conforms_to(xhost, xschema_path, true, xauto_access));

  // Body:
    
  // Set any class specific args in arg list.

  arg_list largs(xargs);
  initialize_arg_list(xhost, xname, largs, xschema_path, xauto_access);

  // Create the new state.

  poset::new_state(&xhost, xschema_path, xname, largs, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state(xhost, xschema_path, xname, xargs, xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::tuple_space::
initialize_arg_list(const namespace_poset& xns,
		    const string& xname,
		    arg_list& xargs,
		    const poset_path& xschema_path,
		    bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));

  require(xschema_path.full());
  require(xns.member_poset(xschema_path, xauto_access).state_is_auto_read_accessible(xauto_access));
  require(xschema_path.conforms_to(xns, standard_schema_path(), xauto_access));

  require(xargs.conforms_to(xns, standard_schema_path(), true, xauto_access));
  
  // Body:

  xargs.value("factor_ct") = schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access);

  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "tuple_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:


  // Exit:

  return;
}

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


fiber_bundle::tuple_space&
fiber_bundle::tuple_space::
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



