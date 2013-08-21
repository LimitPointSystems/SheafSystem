


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_tuple_space.

#include "sec_tuple_space.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "section_space_schema_member.impl.h"
#include "section_space_schema_poset.h"
#include "sec_tuple.h"
#include "tuple.h"
#include "tuple_space.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// SEC_TUPLE_SPACE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::sec_tuple_space::
make_arg_list(int xfactor_ct)
{
  // Preconditions:

  // Body:

  arg_list result;
  result << "factor_ct" <<  xfactor_ct;
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_tuple_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(result.value("factor_ct") == xfactor_ct);
  ensure(unexecutable("result.conforms_to(schema of this class)"));
  
  // Exit:

  return result;
}

bool
fiber_bundle::sec_tuple_space::
fiber_schema_conforms(const namespace_poset& xns, 
                      const poset_path& xsection_schema_path, 
                      const poset_path& xfiber_schema_path, 
                      bool xauto_access)
{
  // cout << endl << "Entering sec_tuple_space::fiber_schema_conforms." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));
  
  require(!xsection_schema_path.empty());
  require(xns.path_is_auto_read_accessible(xsection_schema_path, xauto_access));
  
  require(xfiber_schema_path.full());
  require(xns.path_is_auto_read_accessible(xfiber_schema_path, xauto_access));

  // Body:

  section_space_schema_poset& lschema_host = xns.member_poset<section_space_schema_poset>(xsection_schema_path, xauto_access);

  bool result = lschema_host.fiber_space().schema(xauto_access).conforms_to(xfiber_schema_path);

  // Postconditions:


  // Exit:

  // cout << "Leaving sec_tuple_space::fiber_schema_conforms." << endl;
  return result;
}


fiber_bundle::sec_tuple_space&
fiber_bundle::sec_tuple_space::
new_table(namespace_type& xns, const poset_path& xpath, const poset_path& xschema_path, bool xauto_access)
{
  // cout << endl << "Entering sec_tuple_space::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));
  
  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
  require(fiber_space_conforms<fiber_type::host_type>(xns, xschema_path, xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef sec_tuple_space table_type;

  table_type& result = *(new table_type());

  // Create a handle of the right type for the schema member.

  schema_type lschema(xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Create the table dof map.

  array_poset_dof_map& lmap = *(new array_poset_dof_map(&lschema, true));

  // The table dofs are the samae as the fiber schema,
  // so just copy them from the fiber schema.
  // Can't use copy constructor because schema objects are different.

  array_poset_dof_map& lfiber_map = lschema.fiber_space().table_dof_map();
  lmap.copy_dof_tuple(lfiber_map);
  
  // Create the state.

  result.new_state(xns, xpath, lschema, lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  // Postconditions:

  //  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));

  // Exit:

  // cout << "Leaving sec_tuple_space::new_table." << endl;
  return result;
}

//==============================================================================
// TABLE DOFS
//==============================================================================

int
fiber_bundle::sec_tuple_space::
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
fiber_bundle::sec_tuple_space::
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

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_tuple_space::
sec_tuple_space()
  : sec_rep_space(new sec_tuple, new sec_tuple)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(sec_rep_space::sec_rep_space()));
}

fiber_bundle::sec_tuple_space::
sec_tuple_space(const sec_tuple_space& xother)
  : sec_rep_space(new sec_tuple, new sec_tuple)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::sec_tuple_space::
~sec_tuple_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_tuple_space::
sec_tuple_space(sec_tuple* xtop, sec_tuple* xbottom)
  : sec_rep_space(xtop, xbottom)
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

fiber_bundle::sec_tuple_space::
sec_tuple_space(namespace_poset& xhost,
		const string& xname,
		const arg_list& xargs,
		const poset_path& xschema_path,
		bool xauto_access)
  : sec_rep_space(new sec_tuple, new sec_tuple)
{

  // Preconditions:

  require(precondition_of(sec_rep_space::new_state(same args)));

  require(xargs.value("factor_ct").value().int_primitive >= 0);

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(sec_rep_space::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::sec_tuple_space::
sec_tuple_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : sec_rep_space(new sec_tuple, new sec_tuple)
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

fiber_bundle::sec_tuple_space::
sec_tuple_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : sec_rep_space(new sec_tuple, new sec_tuple)
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

fiber_bundle::sec_tuple_space::
sec_tuple_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : sec_rep_space(new sec_tuple, new sec_tuple)
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

fiber_bundle::sec_tuple_space::
sec_tuple_space(const namespace_poset_member& xmbr, bool xauto_access)
  : sec_rep_space(new sec_tuple, new sec_tuple)
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

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_REP_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::sec_tuple_space::
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

  /// @error arg_list attaches to a schema_poset_member however 
  ///        binary_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xargs.conforms_to(xns, xschema_path, true, xauto_access));
  
  // Body:

  poset_path lfiber_schema_path =
    fiber_schema(xauto_access).path(xauto_access);

  xargs.value("factor_ct") =
    schema_poset_member::row_dof_ct(xns, lfiber_schema_path, xauto_access);

  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_tuple_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:


  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::sec_tuple_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  sec_tuple_space* lproto = new sec_tuple_space;
  poset_type ltype        = lproto->type_id();

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return result;
}


//==============================================================================
// POSET_STATE_HANDLE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_type
fiber_bundle::sec_tuple_space::
type_id() const
{
  return SEC_TUPLE_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::sec_tuple_space::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_tuple_space";

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::sec_tuple_space&
fiber_bundle::sec_tuple_space::
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// READ_WRITE_MONITOR_HANDLE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_tuple_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_tuple_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_tuple_space*
fiber_bundle::sec_tuple_space::
clone() const
{
  sec_tuple_space* result;

  // Preconditions:

  // Body:

  result = new sec_tuple_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::sec_tuple_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(sec_rep_space::invariant());

    /// @todo finish sec_tuple_space::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



