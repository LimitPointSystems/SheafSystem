
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class at0_space.

#include "at0_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// AT0_SPACE FACET public member functions
//==============================================================================

///
const string&
fiber_bundle::at0_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = at0::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::at0_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = at0::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

sheaf::arg_list
fiber_bundle::at0_space::
make_arg_list()
{
  // Preconditions:


  // Body:

  sheaf::arg_list result = atp_space::make_arg_list(0, "");

  result.value("d") = 1;
  result.value("dd") = 1;

  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "at0_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("dd") == 1);
  ensure(result.value("p") == 0);
  ensure(result.value("d") == 1);
  
  // Exit:

  return result;
}

// ===========================================================
// AT0_SPACE FACET protected member functions
// ===========================================================
 
fiber_bundle::at0_space::
at0_space()
  : atp_space(new at0, new at0)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(atp_space::atp_space()));
}



fiber_bundle::at0_space::
at0_space(const at0_space& xother)
  : atp_space(new at0, new at0)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::at0_space::
~at0_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::at0_space::
at0_space(at0* xtop, at0* xbottom)
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

//==============================================================================
// NEW HANDLE, NEW STATE CONSTRUCTORS
//==============================================================================



fiber_bundle::at0_space::
at0_space(namespace_poset& xhost,
	    const string& xname,
	    const arg_list& xargs,
	    const poset_path& xschema_path,
	    bool xauto_access)
  : atp_space(new at0, new at0)
{

  // Preconditions:

  require(precondition_of(at0_space::new_state(same args)));

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(at0_space::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================


fiber_bundle::at0_space::
at0_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : atp_space(new at0, new at0)
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

fiber_bundle::at0_space::
at0_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : atp_space(new at0, new at0)
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

fiber_bundle::at0_space::
at0_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : atp_space(new at0, new at0)
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



fiber_bundle::at0_space::
at0_space(const namespace_poset_member& xmbr, bool xauto_access)
  : atp_space(new at0, new at0)
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
// TP_SPACE FACET public member functions
// ===========================================================


// ===========================================================
// TP_SPACE FACET protected member functions
// ===========================================================
 

sheaf::size_type
fiber_bundle::at0_space::
covariant_subposet_ct() const
{
  return 0;
}

// ===========================================================
// VD_SPACE FACET
// ===========================================================
 

bool
fiber_bundle::at0_space::
is_vector(pod_index_type xmbr_id, bool xauto_access) const
{

  ///
  /// At0 is a special case; scalars can be considered a vector space
  /// over themselves, but even so a scalar is simultaneously a vector and a covector.
  /// This is because covectors transform inversely to vectors, but
  /// by definition the only transform for scalars is the identity transform,
  /// which is its own inverse.

  bool result = true;

  // Postconditions:

  ensure(result);
  
  // Exit:

  return result;
}

void
fiber_bundle::at0_space::
put_is_vector(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  // Body:

  // Do nothing.

  // Postconditions:

  ensure(is_vector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

bool
fiber_bundle::at0_space::
is_covector(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  // Body:

  bool result = true;

  // Postconditions:

  ensure(result);

  // Exit:

  return result;
}

void
fiber_bundle::at0_space::
put_is_covector(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  // Body:

  // Do nothing.

  // Postconditions:

  ensure(is_covector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

// ===========================================================
// POSET FACET
// =========================================================== 

void
fiber_bundle::at0_space::
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
  
  require(xargs.conforms_to(xns, xschema_path, true, xauto_access));

  // Body:

  // Can't let atp and tp initialize args because
  // this is its own vector ans scalar space.
  // jump to vd_space, then set remaining args directly.
  // Set args for vd_space (d, scalar_space_path).

  xargs.value("factor_ct") = static_cast<int>(1);
  xargs.value("d") = static_cast<int>(1);
  xargs.value("scalar_space_path") = xname;
  xargs.value("p") = static_cast<int>(0);
  xargs.value("dd") = xargs.value("d");
  xargs.value("vector_space_path") = xname;

  // Done.
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "at0_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(xargs.value("vector_space_path") == xname);
  ensure(xargs.value("dd") == static_cast<int>(1));
  ensure(xargs.value("p") == static_cast<int>(0));
  ensure(xargs.value("scalar_space_path") == xname);
  ensure(xargs.value("d") == static_cast<int>(1));
  ensure(xargs.value("factor_ct") == static_cast<int>(1));

  // Exit:

  return;
}

bool
fiber_bundle::at0_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  at0_space* lproto = new at0_space;
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
fiber_bundle::at0_space::
type_id() const
{
  return AT0_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::at0_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "at0_space";

  // Postconditions:

  // Exit:

  return result;
}

///
sheaf::pod_index_type
fiber_bundle::at0_space::
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

    default:

      // No other prerequisites.

      result = invalid_pod_index();
      break;
  }

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::at0_space&
fiber_bundle::at0_space::
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
fiber_bundle::at0_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const at0_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::at0_space*
fiber_bundle::at0_space::
clone() const
{
  at0_space* result;

  // Preconditions:

  // Body:

  result = new at0_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::at0_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(atp_space::invariant());

    invariance(state_is_read_accessible() ? dd() == d() : true);
    invariance(state_is_read_accessible() ? vector_space_path().poset_name() == name() : true);
    invariance(state_is_read_accessible() ? p() == 0 : true);
    invariance(state_is_read_accessible() ? scalar_space_path().poset_name() == name() : true);
    invariance(state_is_read_accessible() ? d() == 1 : true);
    invariance(state_is_read_accessible() ? factor_ct() == d() : true);
    
    enable_invariant_check();
  }

  return result;
}


