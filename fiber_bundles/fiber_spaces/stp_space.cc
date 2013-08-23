
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Implementation for class stp_space.

#include "stp_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "stp.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// STP_SPACE FACET public member functions
//==============================================================================

///
const string&
fiber_bundle::stp_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = stp::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::stp_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = stp::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

sheaf::arg_list
fiber_bundle::stp_space::
make_arg_list(int xp, const poset_path& xvector_space_path)
{
  // Preconditions:


  // Body:

  // $$SCRIBBLE: dmb I don't think we need this routine; it's the same as tp_space.

  sheaf::arg_list result = tp_space::make_arg_list(xp, xvector_space_path);

  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "stp_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("p") == xp);
  ensure(result.value("vector_space_path") == xvector_space_path);
  
  // Exit:

  return result;
}

// ===========================================================
// STP_SPACE FACET protected member functions
// ===========================================================
 
fiber_bundle::stp_space::
stp_space()
  : tp_space(new stp, new stp)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(tp_space::tp_space()));
}



fiber_bundle::stp_space::
stp_space(const stp_space& xother)
  : tp_space(new stp, new stp)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::stp_space::
~stp_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::stp_space::
stp_space(stp* xtop, stp* xbottom)
  : tp_space(xtop, xbottom)
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

fiber_bundle::stp_space::
stp_space(namespace_poset& xhost,
	    const string& xname,
	    const arg_list& xargs,
	    const poset_path& xschema_path,
	    bool xauto_access)
  : tp_space(new stp, new stp)
{

  // Preconditions:

  require(precondition_of(stp_space::new_state(same args)));

  require(int(xargs.value("p")) >= 0);

  require(!poset_path(xargs.value("vector_space_path")).empty());
  require(xhost.contains_poset(poset_path(xargs.value("vector_space_path")), xauto_access));
  require(xhost.member_poset(poset_path(xargs.value("vector_space_path")), xauto_access).state_is_auto_read_accessible(xauto_access));

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(stp_space::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::stp_space::
stp_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : tp_space(new stp, new stp)
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

fiber_bundle::stp_space::
stp_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : tp_space(new stp, new stp)
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

fiber_bundle::stp_space::
stp_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : tp_space(new stp, new stp)
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



fiber_bundle::stp_space::
stp_space(const namespace_poset_member& xmbr, bool xauto_access)
  : tp_space(new stp, new stp)
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

int
fiber_bundle::stp_space::
d(int xp, int xdd) const
{
  return static_cast<int>(binomial_coefficient(xdd+xp-1, xp));
}

///
fiber_bundle::tensor_variance
fiber_bundle::stp_space::
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


// ===========================================================
// TP_SPACE FACET protected member functions
// ===========================================================

sheaf::size_type
fiber_bundle::stp_space::
covariant_subposet_ct() const
{
  return 1;
}
 

// ===========================================================
// POSET FACET
// =========================================================== 

bool
fiber_bundle::stp_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  stp_space* lproto = new stp_space;
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
fiber_bundle::stp_space::
type_id() const
{
  return STP_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::stp_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "stp_space";

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::stp_space&
fiber_bundle::stp_space::
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
fiber_bundle::stp_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const stp_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::stp_space*
fiber_bundle::stp_space::
clone() const
{
  stp_space* result;

  // Preconditions:

  // Body:

  result = new stp_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::stp_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(tp_space::invariant());
    
    enable_invariant_check();
  }

  return result;
}


