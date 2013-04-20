


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_atp_space.

#include "sec_atp_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "sec_atp.h"
#include "section_space_schema_poset.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// SEC_ATP_SPACE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::sec_atp_space::
make_arg_list(int xp, const poset_path& xvector_space_path)
{
  // Preconditions:

  // Body:

  // $$SCRIBBLE: dmb I don't think we need this routine; it's the same as sec_tp_space.

  sheaf::arg_list result = sec_tp_space::make_arg_list(xp, xvector_space_path);
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_atp_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("p") == xp);
  ensure(result.value("vector_space_path") == xvector_space_path);
  
  // Exit:

  return result;
}

bool
fiber_bundle::sec_atp_space::
is_p_form(pod_index_type xmbr_id, bool xauto_access) const
{

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));

  // Body:

  bool result = is_covariant(xmbr_id, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::sec_atp_space::
is_p_form(const scoped_index& xmbr_id, bool xauto_access) const
{

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));

  // Body:

  return is_p_form(xmbr_id.hub_pod(), xauto_access);
}

void
fiber_bundle::sec_atp_space::
put_is_p_form(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));

  // Body:

  put_is_covariant(xmbr_id, xauto_access);

  // Postconditions:

  ensure(is_p_form(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::sec_atp_space::
put_is_p_form(const scoped_index& xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));

  // Body:

  put_is_p_form(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_p_form(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

bool
fiber_bundle::sec_atp_space::
is_p_vector(pod_index_type xmbr_id, bool xauto_access) const
{

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));

  // Body:

  bool result = is_contravariant(xmbr_id, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::sec_atp_space::
is_p_vector(const scoped_index& xmbr_id, bool xauto_access) const
{

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));

  // Body:

  return is_p_vector(xmbr_id.hub_pod(), xauto_access);
}

void
fiber_bundle::sec_atp_space::
put_is_p_vector(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));

  // Body:

  put_is_contravariant(xmbr_id, xauto_access);

  // Postconditions:

  ensure(is_p_vector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::sec_atp_space::
put_is_p_vector(const scoped_index& xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));

  // Body:

  put_is_p_vector(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_p_vector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_atp_space::
sec_atp_space()
  : sec_tp_space(new sec_atp, new sec_atp)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(sec_tp_space::sec_tp_space()));
}

fiber_bundle::sec_atp_space::
sec_atp_space(const sec_atp_space& xother)
  : sec_tp_space(new sec_atp, new sec_atp)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::sec_atp_space::
~sec_atp_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_atp_space::
sec_atp_space(sec_atp* xtop, sec_atp* xbottom)
  : sec_tp_space(xtop, xbottom)
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

fiber_bundle::sec_atp_space::
sec_atp_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access)
  : sec_tp_space(new sec_atp, new sec_atp)
{

  // Preconditions:

  require(precondition_of(sec_tp_space::new_state(same args)));

  require(int(xargs.value("p")) >= 0);

  require(xhost.path_is_auto_read_accessible(xargs.value("vector_space_path"), xauto_access));

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(sec_tp_space::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::sec_atp_space::
sec_atp_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : sec_tp_space(new sec_atp, new sec_atp)
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

fiber_bundle::sec_atp_space::
sec_atp_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : sec_tp_space(new sec_atp, new sec_atp)
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

fiber_bundle::sec_atp_space::
sec_atp_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : sec_tp_space(new sec_atp, new sec_atp)
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

fiber_bundle::sec_atp_space::
sec_atp_space(const namespace_poset_member& xmbr, bool xauto_access)
  : sec_tp_space(new sec_atp, new sec_atp)
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
// SEC_TP_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::sec_atp_space::
d(int xp, int xdd) const
{
  return static_cast<int>(binomial_coefficient(xdd, xp));
}

fiber_bundle::tensor_variance
fiber_bundle::sec_atp_space::
round_variance(const tensor_variance& xvariance) const
{
  // Preconditions:
  
  // Body:

  tensor_variance result(xvariance);
  result.purify();

  // Postconditions:

  ensure(result.is_pure());
  ensure_for_all(i, 0, result.p(), result.variance(i) == xvariance.variance(0));

  // Exit:

  return xvariance;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::size_type
fiber_bundle::sec_atp_space::
covariant_subposet_ct() const
{
  return 1;
}
 
// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_VD_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

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

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::sec_atp_space::
_has_prototype = make_prototype();


bool
fiber_bundle::sec_atp_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  sec_atp_space* lproto = new sec_atp_space;
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
fiber_bundle::sec_atp_space::
type_id() const
{
  return SEC_ATP_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::sec_atp_space::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_atp_space";

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::sec_atp_space&
fiber_bundle::sec_atp_space::
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
fiber_bundle::sec_atp_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_atp_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_atp_space*
fiber_bundle::sec_atp_space::
clone() const
{
  sec_atp_space* result;

  // Preconditions:

  // Body:

  result = new sec_atp_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::sec_atp_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(sec_tp_space::invariant());

    enable_invariant_check();
  }

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



