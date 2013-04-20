


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_stp_space.

#include "sec_stp_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "sec_stp.h"
#include "section_space_schema_poset.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// SEC_STP_SPACE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::sec_stp_space::
make_arg_list(int xp, const poset_path& xvector_space_path)
{
  // Preconditions:

  // Body:

  // $$SCRIBBLE: dmb I don't think we need this routine; it's the same as sec_tp_space.

  sheaf::arg_list result = sec_tp_space::make_arg_list(xp, xvector_space_path);
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_stp_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("p") == xp);
  ensure(result.value("vector_space_path") == xvector_space_path);
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_stp_space::
sec_stp_space()
  : sec_tp_space(new sec_stp, new sec_stp)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(sec_tp_space::sec_tp_space()));
}

fiber_bundle::sec_stp_space::
sec_stp_space(const sec_stp_space& xother)
  : sec_tp_space(new sec_stp, new sec_stp)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}

fiber_bundle::sec_stp_space::
~sec_stp_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_stp_space::
sec_stp_space(sec_stp* xtop, sec_stp* xbottom)
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

fiber_bundle::sec_stp_space::
sec_stp_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access)
  : sec_tp_space(new sec_stp, new sec_stp)
{

  // Preconditions:

  require(precondition_of(sec_stp_space::new_state(same args)));

  require(int(xargs.value("p")) >= 0);

  require(xhost.path_is_auto_read_accessible(xargs.value("vector_space_path"), xauto_access));

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(sec_stp_space::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::sec_stp_space::
sec_stp_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : sec_tp_space(new sec_stp, new sec_stp)
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

fiber_bundle::sec_stp_space::
sec_stp_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : sec_tp_space(new sec_stp, new sec_stp)
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

fiber_bundle::sec_stp_space::
sec_stp_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : sec_tp_space(new sec_stp, new sec_stp)
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

fiber_bundle::sec_stp_space::
sec_stp_space(const namespace_poset_member& xmbr, bool xauto_access)
  : sec_tp_space(new sec_stp, new sec_stp)
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
fiber_bundle::sec_stp_space::
d(int xp, int xdd) const
{
  return static_cast<int>(binomial_coefficient(xdd+xp-1, xp));
}

fiber_bundle::tensor_variance
fiber_bundle::sec_stp_space::
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
fiber_bundle::sec_stp_space::
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
fiber_bundle::sec_stp_space::
_has_prototype = make_prototype();


bool
fiber_bundle::sec_stp_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  sec_stp_space* lproto = new sec_stp_space;
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
fiber_bundle::sec_stp_space::
type_id() const
{
  return SEC_STP_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::sec_stp_space::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_stp_space";

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::sec_stp_space&
fiber_bundle::sec_stp_space::
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
fiber_bundle::sec_stp_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_stp_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_stp_space*
fiber_bundle::sec_stp_space::
clone() const
{
  sec_stp_space* result;

  // Preconditions:

  // Body:

  result = new sec_stp_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::sec_stp_space::
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



