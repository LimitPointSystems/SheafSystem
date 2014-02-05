
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
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

/// @file
/// Implementation for class ed

#include "ed.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS ED_LITE
//==============================================================================

//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (ED) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::ed_lite::
ed_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::ed_lite::
ed_lite(const ed_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::ed_lite&
fiber_bundle::ed_lite::
operator=(const ed_lite& xother)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::ed_lite::
~ed_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::ed_lite::
ed_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::ed_lite&
fiber_bundle::ed_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  vd_lite::operator=(xrow_dofs);
  
  // Postconditions:

  postcondition_of(vd_lite::operator=(xrow_dofs));

  // Exit:

  return *this;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// AT1 FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::ed_lite::
class_name() const
{
  // Preconditions:

  // Body:

  const string& result = static_class_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const std::string&
fiber_bundle::ed_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("ed_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::ed_lite*
fiber_bundle::ed_lite::
clone() const
{
  ed_lite* result = 0;

  // Preconditions:

  // Body:

  result = new ed_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::ed_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const ed_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::ed_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(at1_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS ED
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS ED
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::ed::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "ed_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::ed::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              at1::standard_schema_path(),
                              "",
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::ed::host_type&
fiber_bundle::ed::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xscalar_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering ed::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  
  require(xns.path_is_auto_read_accessible(xscalar_space_path, xauto_access));
  require(xns.contains_poset<scalar_type::host_type>(xscalar_space_path, xauto_access));

  // Body:

  host_type& result = 
    host_type::new_table(xns, xhost_path, xschema_path, xscalar_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));
  ensure(result.scalar_space_path(true) == xscalar_space_path );
  ensure(result.p(true) == 1);
  ensure(result.dd(true) == result.d(true));
  ensure(result.vector_space_path(true) == xhost_path );

  // Exit:

  // cout << "Leaving ed::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (ED) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::ed::
ed()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::ed::
ed(const poset_state_handle* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

fiber_bundle::ed::
ed(const poset_state_handle* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

fiber_bundle::ed::
ed(const poset_state_handle* xhost, const std::string& xname)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());
  require(xhost->contains_member(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(invariant());
  // ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());

}

fiber_bundle::ed::
ed(abstract_poset_member* xother)
{

  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));

}

fiber_bundle::ed::
ed(poset_state_handle* xhost, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(xhost, 0, false, xauto_access)));

  // Body:

  new_jim_state(xhost, 0, false, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, 0, false, xauto_access)));

  // Exit:

  return;
}

///
fiber_bundle::ed&
fiber_bundle::ed::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));
  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

///
fiber_bundle::ed&
fiber_bundle::ed::
operator=(const ed& xother)
{
  // Preconditions:

  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

fiber_bundle::ed::
~ed()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::ed::volatile_type&
fiber_bundle::ed::
lite_prototype() const
{
  // Preconditions:

  // Body:

  static const volatile_type result;

  // Postconditions:

  // Exit:

  return result;
}

///
fiber_bundle::ed::volatile_type*
fiber_bundle::ed::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::ed::
class_name() const
{
  // Preconditions:

  // Body:

  const string& result = static_class_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const std::string&
fiber_bundle::ed::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("ed");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::ed*
fiber_bundle::ed::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  ed* result = new ed();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::ed::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const ed*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::ed::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(at1::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

fiber_bundle::vd_value_type
fiber_bundle::ed_algebra::
dot(const ed& x0, const ed& x1, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(x0.is_same_type(&x1));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
  }

  vd_value_type result = 0;

  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    result += x0.component(i) * x1.component(i);
  }

  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
  }

  // Postconditions:

  ensure(unexecutable(\
    "result == sum(i, 0, x0.d(), x0.component(i) * x1.component(i)"));

  // Exit:

  return result;
}

fiber_bundle::vd_value_type
fiber_bundle::ed_algebra::
length(const ed& x0, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  vd_value_type result = 0;

  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    vd_value_type x = x0.component(i);
    result += x * x;
  }

  result = sqrt(result);

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  ensure(result >= 0.0);
  ensure(unexecutable("result == sqrt(sum(i, 0, x0.d(), x0.component(i)**2)"));

  // Exit:

  return result;
}

void
fiber_bundle::ed_algebra::
put_length(ed& x0, const vd_value_type& xlength, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_write_accessible(xauto_access));
  ensure(xlength >= 0.0);

  // Body:

  if(xauto_access)
  {
    x0.get_read_write_access(true);
  }

  ///@issue Do we just want to do nothing if the length of the
  ///       vector is zero?

  vd_value_type len = length(x0, false);

  vd_value_type lscale = (len != 0.0) ?  (xlength / len) : 0.0;

  // We could call vd::scale_by here but this is more efficient.

  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    x0.put_component(i, lscale*x0.component(i));
  }

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  ensure(unexecutable("length(x0, xauto_access) == xlength"));

  // Exit:

  return;
}

void
fiber_bundle::ed_algebra::
normalize(const ed& x0, ed& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.is_same_type(&xresult));
  require(x0.is_p_form(xauto_access) == xresult.is_p_form(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  ///@issue Do we just want to do nothing if the length of the
  ///       vector is zero?

  vd_value_type len = length(x0, false);

  vd_value_type lscale = (len != 0.0) ?  (1.0 / len) : 0.0;

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, lscale*x0.component(i));
  }

  if(x0.is_p_form(false))
  {
    xresult.put_is_p_form(false);
  }
  else
  {
    xresult.put_is_p_vector(false);
  }

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_p_form(false) == x0.is_p_form(false));
  ensure(unexecutable("length(xresult, xauto_access) == 1.0"));

  // Exit:

  return;
}

fiber_bundle::vd_value_type
fiber_bundle::ed_algebra::
dot(const ed_lite& x0, const ed_lite& x1)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  vd_value_type result = 0;

  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    result += x0.component(i) * x1.component(i);
  }

  // Postconditions:

  ensure(unexecutable("result == sum(i, 0, x0.d(), x0.component(i)*x1.component(i)"));

  // Exit:

  return result;
}

fiber_bundle::vd_value_type
fiber_bundle::ed_algebra::
length(const ed_lite& x0)
{
  // Preconditions:

  // Body:

  vd_value_type result = 0;

  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    vd_value_type x = x0.component(i);
    result += x * x;
  }

  result = sqrt(result);

  // Postconditions:

  ensure(result >= 0.0);
  ensure(unexecutable("result == sqrt(sum(i, 0, x0.d(), x0.component(i)**2)"));

  // Exit:

  return result;
}

void
fiber_bundle::ed_algebra::
put_length(ed_lite& x0, const vd_value_type& xlength)
{
  // Preconditions:

  require(xlength >= 0.0);

  // Body:

  ///@issue Do we just want to do nothing if the length of the
  ///       vector is zero?

  vd_value_type len = length(x0);

  vd_value_type lscale = (len != 0.0) ?  (xlength / len) : 0.0;

  //$$SCRIBBLE: We could call vd_lite::scale_by here but this
  //            is more efficient.

  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    x0.put_component(i, lscale*x0.component(i));
  }

  // Postconditions:

  ensure(unexecutable("length(x0) == xlength"));

  // Exit:

  return;
}

void
fiber_bundle::ed_algebra::
normalize(const ed_lite& x0, ed_lite& xresult)
{
  // Preconditions:

  require(x0.is_same_type(xresult));

  // Body:

  ///@issue Do we just want to do nothing if the length of the
  ///       vector is zero?

  vd_value_type len = length(x0);

  vd_value_type lscale = (len != 0.0) ?  (1.0 / len) : 0.0;


  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, lscale*x0.component(i));
  }

  // Postconditions:

  ensure(unexecutable("length(xresult) == 1.0"));

  // Exit:

  return;
}

