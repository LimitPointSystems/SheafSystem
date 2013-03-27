
// $RCSfile: sec_at1_space.cc,v $ $Revision: 1.14 $ $Date: 2013/03/18 02:53:24 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_at1_space.

#include "sec_at1_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "sec_at1.h"
#include "section_space_schema_poset.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// SEC_AT1_SPACE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::sec_at1_space::
make_arg_list(const poset_path& xscalar_space_path)
{
  // Preconditions:


  // Body:

  sheaf::arg_list result = sec_atp_space::make_arg_list(1, "");
  result.value("d") = 0;
  result.value("scalar_space_path") = xscalar_space_path;

  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_at1_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.contains_arg("factor_ct"));
  ensure(result.contains_arg("d"));
  ensure(result.contains_arg("scalar_space_path"));
  ensure(result.value("scalar_space_path") == xscalar_space_path);
  ensure(result.contains_arg("p"));
  ensure(result.value("p") == 1);
  ensure(result.contains_arg("dd"));
  ensure(result.contains_arg("vector_space_path"));
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_at1_space::
sec_at1_space()
  : sec_atp_space(new sec_at1, new sec_at1)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(sec_atp_space::sec_atp_space()));
}

fiber_bundle::sec_at1_space::
sec_at1_space(const sec_at1_space& xother)
  : sec_atp_space(new sec_at1, new sec_at1)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::sec_at1_space::
~sec_at1_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_at1_space::
sec_at1_space(sec_at1* xtop, sec_at1* xbottom)
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

fiber_bundle::sec_at1_space::
sec_at1_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access)
  : sec_atp_space(new sec_at1, new sec_at1)
{

  // Preconditions:

  require(precondition_of(sec_atp_space::new_state(same args)));

  require(int(xargs.value("d")) >= 0);

  require(xhost.path_is_auto_read_accessible(xargs.value("scalar_space_path"), xauto_access));

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(sec_atp_space::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::sec_at1_space::
sec_at1_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : sec_atp_space(new sec_at1, new sec_at1)
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

fiber_bundle::sec_at1_space::
sec_at1_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : sec_atp_space(new sec_at1, new sec_at1)
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

fiber_bundle::sec_at1_space::
sec_at1_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : sec_atp_space(new sec_at1, new sec_at1)
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

fiber_bundle::sec_at1_space::
sec_at1_space(const namespace_poset_member& xmbr, bool xauto_access)
  : sec_atp_space(new sec_at1, new sec_at1)
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

void
fiber_bundle::sec_at1_space::
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

  require(xns.path_is_auto_read_accessible(xargs.value("scalar_space_path"), xauto_access));

  // Body:

  // Can't let atp and tp initialize args because this is the vector space;
  // jump to sec_vd_space, then set remaining args directly.
  // Args for sec_vd_space (d, scalar_space_path) already set.

  sec_vd_space::initialize_arg_list(xns, xname, xargs, xschema_path, xauto_access);

  xargs.value("p") = static_cast<int>(1);
  xargs.value("dd") = xargs.value("d");
  xargs.value("vector_space_path") = xname; 


  // Done.
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_at1_space::initialize_arg_list:xargs: " << xargs << endl;
#endif

  // Postconditions:

  ensure(xargs.value("vector_space_path") == xname);
  ensure(xargs.value("dd") == xargs.value("d"));
  ensure(xargs.value("p") == static_cast<int>(1));
  ensure(xargs.value("factor_ct") == xargs.value("d"));

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::sec_at1_space::
_has_prototype = make_prototype();


bool
fiber_bundle::sec_at1_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  sec_at1_space* lproto = new sec_at1_space;
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
fiber_bundle::sec_at1_space::
type_id() const
{
  return SEC_AT1_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::sec_at1_space::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_at1_space";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::sec_at1_space::
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

fiber_bundle::sec_at1_space&
fiber_bundle::sec_at1_space::
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
fiber_bundle::sec_at1_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_at1_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_at1_space*
fiber_bundle::sec_at1_space::
clone() const
{
  sec_at1_space* result;

  // Preconditions:

  // Body:

  result = new sec_at1_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::sec_at1_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(sec_atp_space::invariant());

    invariance(state_is_read_accessible() ? p() == 1 : true);
    invariance(state_is_read_accessible() ? vector_space_path().poset_name() == name() : true);

    enable_invariant_check();
  }

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



