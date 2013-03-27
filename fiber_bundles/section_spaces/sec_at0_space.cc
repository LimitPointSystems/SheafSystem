
// $RCSfile: sec_at0_space.cc,v $ $Revision: 1.14 $ $Date: 2013/03/18 02:53:24 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_at0_space.

#include "sec_at0_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "sec_at0.h"
#include "section_space_schema_poset.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// SEC_AT0_SPACE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::sec_at0_space::
make_arg_list()
{
  // Preconditions:

  // Body:

  sheaf::arg_list result = sec_atp_space::make_arg_list(0, "");

  result.value("d") = 1;
  result.value("dd") = 1;

  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_at0_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("dd") == 1);
  ensure(result.value("p") == 0);
  ensure(result.value("d") == 1);
  
  // Exit:

  return result;
}

sheaf::arg_list
fiber_bundle::sec_at0_space::
make_arg_list(const poset_path& xvector_space_path)
{
  // Preconditions:


  // Body:

  sheaf::arg_list result = sec_atp_space::make_arg_list(0, xvector_space_path);

  result.value("d") = 1;
  result.value("dd") = 1;

  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_at0_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("dd") == 1);
  ensure(result.value("p") == 0);
  ensure(result.value("d") == 1);
  
  // Exit:

  return result;
}

sheaf::arg_list
fiber_bundle::sec_at0_space::
make_arg_list(int xp, const poset_path& xvector_space_path)
{
  // Preconditions:

  require(xp == 0);

  // Body:

  sheaf::arg_list result = sec_atp_space::make_arg_list(xp, xvector_space_path);

  result.value("d") = 1;
  result.value("dd") = 1;

  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_at0_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("dd") == 1);
  ensure(result.value("p") == 0);
  ensure(result.value("d") == 1);
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_at0_space::
sec_at0_space()
  : sec_atp_space(new sec_at0, new sec_at0)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(sec_atp_space::sec_atp_space()));
}

fiber_bundle::sec_at0_space::
sec_at0_space(const sec_at0_space& xother)
  : sec_atp_space(new sec_at0, new sec_at0)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::sec_at0_space::
~sec_at0_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_at0_space::
sec_at0_space(sec_at0* xtop, sec_at0* xbottom)
  : sec_atp_space(xtop, xbottom)
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

fiber_bundle::sec_at0_space::
sec_at0_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access)
  : sec_atp_space(new sec_at0, new sec_at0)
{

  // Preconditions:

  require(precondition_of(sec_at0_space::new_state(same args)));

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(sec_at0_space::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::sec_at0_space::
sec_at0_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : sec_atp_space(new sec_at0, new sec_at0)
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

fiber_bundle::sec_at0_space::
sec_at0_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : sec_atp_space(new sec_at0, new sec_at0)
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

fiber_bundle::sec_at0_space::
sec_at0_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : sec_atp_space(new sec_at0, new sec_at0)
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

fiber_bundle::sec_at0_space::
sec_at0_space(const namespace_poset_member& xmbr, bool xauto_access)
  : sec_atp_space(new sec_at0, new sec_at0)
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
// SEC_ATP_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_TP_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_VD_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_at0_space::
is_vector(pod_index_type xmbr_id, bool xauto_access) const
{
  
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
fiber_bundle::sec_at0_space::
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
fiber_bundle::sec_at0_space::
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
fiber_bundle::sec_at0_space::
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

// PROTECTED MEMBER FUNCTIONS

sheaf::size_type
fiber_bundle::sec_at0_space::
covariant_subposet_ct() const
{
  return 0;
}
 
// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_TUPLE_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_REP_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::sec_at0_space::
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
  ///        product_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xargs.conforms_to(xns, xschema_path, true, xauto_access));

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
  cout << "sec_at0_space::make_arg_list:result: " << result << endl;
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

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::sec_at0_space::
_has_prototype = make_prototype();


bool
fiber_bundle::sec_at0_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  sec_at0_space* lproto = new sec_at0_space;
  poset_type ltype      = lproto->type_id();

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
fiber_bundle::sec_at0_space::
type_id() const
{
  return SEC_AT0_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::sec_at0_space::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_at0_space";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::sec_at0_space::
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

fiber_bundle::sec_at0_space&
fiber_bundle::sec_at0_space::
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
fiber_bundle::sec_at0_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_at0_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_at0_space*
fiber_bundle::sec_at0_space::
clone() const
{
  sec_at0_space* result;

  // Preconditions:

  // Body:

  result = new sec_at0_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::sec_at0_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(sec_atp_space::invariant());

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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



