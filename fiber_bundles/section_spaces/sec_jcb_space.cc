


//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for class sec_jcb_space.

#include "sec_jcb_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "sec_jcb.h"
#include "section_space_schema_poset.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// SEC_JCB_SPACE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::sec_jcb_space::
make_arg_list(const poset_path& xdomain_path, const poset_path& xrange_path)
{
  // Preconditions:

  // Body:

  // Order has to conform to order in schema,
  // which has to conform to order in dof id space of top.

  arg_list result;
  result << "factor_ct" << -1
	 << "d" << -1
	 << "scalar_space_path" << ""
	 << "dd" << -1
	 << "domain_path" << xdomain_path
	 << "range_path" << xrange_path
	 << "dr" << -1;
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_jcb_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(result.value("range_path") == xrange_path);
  ensure(result.value("domain_path") == xdomain_path);
  ensure(unexecutable("result.conforms_to(schema of this class)"));

  // Exit:

  return result;
}

//==============================================================================
// TABLE DOFS
//==============================================================================

int
fiber_bundle::sec_jcb_space::
d(int xdd, int xdr)
{
  return xdd*xdr;
}

int
fiber_bundle::sec_jcb_space::
dd() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  int result = sheaf::table_dofs(*this).dd;

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::sec_jcb_space::
dd(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  int result = sheaf::table_dofs(*this).dd;
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_jcb_space::
domain_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(sheaf::table_dofs(*this).domain_path);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_jcb_space::
domain_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).domain_path);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

int
fiber_bundle::sec_jcb_space::
dr() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  int result = sheaf::table_dofs(*this).dr;

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::sec_jcb_space::
dr(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  int result = sheaf::table_dofs(*this).dr;
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_jcb_space::
range_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(sheaf::table_dofs(*this).range_path);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_jcb_space::
range_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).range_path);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_jcb_space::
sec_jcb_space()
  : sec_vd_space(new sec_jcb, new sec_jcb)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(sec_vd_space::sec_vd_space()));
}

fiber_bundle::sec_jcb_space::
sec_jcb_space(const sec_jcb_space& xother)
  : sec_vd_space(new sec_jcb, new sec_jcb)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::sec_jcb_space::
~sec_jcb_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_jcb_space::
sec_jcb_space(sec_jcb* xtop, sec_jcb* xbottom)
  : sec_vd_space(xtop, xbottom)
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

fiber_bundle::sec_jcb_space::
sec_jcb_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access)
  : sec_vd_space(new sec_jcb, new sec_jcb)
{

  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));

  require(!xhost.contains_poset(xname, xauto_access));

  require(xhost.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(xargs.conforms_to(xhost, xschema_path, true, xauto_access));

  require(xhost.path_is_auto_read_accessible(xargs.value("domain_path"), xauto_access));
  require(xhost.path_is_auto_read_accessible(xargs.value("range_path"), xauto_access));

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(sec_jcb_space::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::sec_jcb_space::
sec_jcb_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : sec_vd_space(new sec_jcb, new sec_jcb)
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

fiber_bundle::sec_jcb_space::
sec_jcb_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : sec_vd_space(new sec_jcb, new sec_jcb)
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

fiber_bundle::sec_jcb_space::
sec_jcb_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : sec_vd_space(new sec_jcb, new sec_jcb)
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

fiber_bundle::sec_jcb_space::
sec_jcb_space(const namespace_poset_member& xmbr, bool xauto_access)
  : sec_vd_space(new sec_jcb, new sec_jcb)
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
fiber_bundle::sec_jcb_space::
initialize_arg_list(const namespace_poset& xns, 
		    const string& xname,
		    arg_list& xargs, 
		    const poset_path& xschema_path,
		    bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));

  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(xargs.conforms_to(xns, xschema_path, true, xauto_access));

  require(xns.path_is_auto_read_accessible(poset_path(xargs.value("domain_path")), xauto_access));
  require(xns.path_is_auto_read_accessible(poset_path(xargs.value("range_path")), xauto_access));
  
  // Body:

  poset_path ldomain_path(xargs.value("domain_path"));
  poset_path lrange_path(xargs.value("range_path"));
  
  // Set args required by parent.

  xargs.value("scalar_space_path") = scalar_space_path(xns, ldomain_path, xauto_access);

  // Initialize inherited args (factor_ct, d).

  sec_vd_space::initialize_arg_list(xns, xname, xargs, xschema_path, xauto_access);

  // Initialize args defined in this class; domain_path and range_path already set.

  xargs.value("dd") = d(xns, ldomain_path, xauto_access);
  xargs.value("dr") = d(xns, lrange_path, xauto_access);

  // Done.
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_jcb_space::initialize_arg_list:xargs: " << result << endl;
#endif

  // Postconditions:

  ensure(xargs.value("dr") == d(xns, xargs.value("range_path"), xauto_access));
  ensure(xargs.value("dd") == d(xns, xargs.value("domain_path"), xauto_access));
  ensure(xargs.value("scalar_space_path") == scalar_space_path(xns, xargs.value("domain_path"), xauto_access));
  ensure(xargs.value("d") == d(xargs.value("dd"), xargs.value("dr")));
  ensure(xargs.value("factor_ct") == xargs.value("d"));
  
  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::sec_jcb_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  sec_jcb_space* lproto = new sec_jcb_space;
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
fiber_bundle::sec_jcb_space::
type_id() const
{
  return SEC_JCB_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::sec_jcb_space::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_jcb_space";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::sec_jcb_space::
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

      // The domain vector space.

      result = name_space()->member_id(domain_path().poset_name(), false);
      break;

    case 2:
	
      // The range vector space.

      result = name_space()->member_id(range_path().poset_name(), false);
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

fiber_bundle::sec_jcb_space&
fiber_bundle::sec_jcb_space::
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
fiber_bundle::sec_jcb_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_jcb_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_jcb_space*
fiber_bundle::sec_jcb_space::
clone() const
{
  sec_jcb_space* result;

  // Preconditions:

  // Body:

  result = new sec_jcb_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::sec_jcb_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(sec_vd_space::invariant());

    invariance(state_is_read_accessible() ? factor_ct() == d() : true);

    enable_invariant_check();
  }

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



