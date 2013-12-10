
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

/// @file
/// Implementation for class sec_tp.

#include "sec_tp.h"

#include "assert_contract.h"
#include "binary_section_space_schema_member.impl.h"
#include "binary_section_space_schema_poset.h"
#include "fiber_bundles_namespace.h"
#include "section_space_schema_member.impl.h"
#include "section_space_schema_poset.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_tuple_space.impl.h"
#include "tp.h"
#include "tp_space.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_TP
//==============================================================================
// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_tp::host_type&
fiber_bundle::sec_tp::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_tp::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
  require(host_type::fiber_space_conforms<fiber_type::host_type>(xns, xschema_path, xauto_access));

  require(xns.path_is_auto_read_accessible<vector_space_type::host_type>(xvector_space_path, xauto_access));

  require(host_type::same_vector_fiber_space(xns, xschema_path, xvector_space_path, xauto_access));

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.scalar_space_path(true) == 
         xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access));
  ensure(result.p(true) == result.schema(true).fiber_space<fiber_type::host_type>().p(xauto_access));
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving sec_tp::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// TP FACET OF CLASS SEC_TP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_tp::
sec_tp()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::sec_tp::
sec_tp(const sec_rep_space* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_tp::
sec_tp(const sec_rep_space* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_tp::
sec_tp(const sec_rep_space* xhost, const std::string& xname)
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
  ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());
  ensure(!is_restricted());

}

fiber_bundle::sec_tp::
sec_tp(const namespace_poset* xnamespace,
       const poset_path& xpath,
       bool xauto_access)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::sec_tp::
sec_tp(sec_rep_space_member* xother)
{
  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));
  ensure(is_same_restriction(xother));

}

fiber_bundle::sec_tp::
sec_tp(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(xhost, xdof_map, false, xauto_access)));

  // Body:

  new_jim_state(xhost, xdof_map, false, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, xdof_map, false, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_tp::
sec_tp(sec_rep_space* xhost,
       abstract_poset_member& xbase_mbr,
       int xbase_version, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access)));

  // Body:

  new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_tp&
fiber_bundle::sec_tp::
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

fiber_bundle::sec_tp&
fiber_bundle::sec_tp::
operator=(const sec_tp& xother)
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

fiber_bundle::sec_tp&
fiber_bundle::sec_tp::
operator=(const tp& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}

fiber_bundle::sec_tp&
fiber_bundle::sec_tp::
operator=(const tp_lite& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}

fiber_bundle::sec_tp::
~sec_tp()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

const fiber_bundle::sec_tp::fiber_type&
fiber_bundle::sec_tp::
fiber_prototype() const
{
  // Preconditions:

  // Body:

  static const fiber_type result;

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::sec_tp::
p() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->p();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::sec_tp::
p(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  int result = host()->p(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::sec_tp::
dd() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->dd();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::sec_tp::
dd(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  int result = host()->dd(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_tp::
vector_space_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(host()->vector_space_path());

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_tp::
vector_space_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  poset_path result(host()->vector_space_path(xauto_access));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_tp_space& 
fiber_bundle::sec_tp::
vector_space() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(name_space()->state_is_read_accessible());

  // Body:

  poset_state_handle& lpsh = name_space()->member_poset(vector_space_path(), false);

  sec_tp_space& result = reinterpret_cast<host_type&>(lpsh);

  // Postconditions:

  // Exit:

  return result;

}

fiber_bundle::sec_tp_space&
fiber_bundle::sec_tp::
vector_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(name_space()->state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    name_space()->get_read_access();
    get_read_access();
  }

  sec_tp_space& result = vector_space();

  if(xauto_access)
  {
    release_access();
    name_space()->release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

const std::string
fiber_bundle::sec_tp::
create_tensor_space_name(const std::string& xvector_space_name, const std::string& xname)
{
 // Preconditions:

  // Body:

  const string result = xvector_space_name + "_" + xname;   

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::sec_tp::
variance(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  tensor_variance result = host()->variance(_index, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::sec_tp::
variance(int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  bool result = host()->variance(_index, xi, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::sec_tp::
put_variance(const tensor_variance& xvariance, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  host()->put_variance(_index, xvariance, xauto_access);
  
  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_tp::
put_variance(int xi, bool xvariance, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  host()->put_variance(_index, xi, xvariance, xauto_access);
  
  // Postconditions:

  // Exit:

  return;
}

bool
fiber_bundle::sec_tp::
is_covariant(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  bool result = host()->is_covariant(_index, xauto_access);

  // Postconditions:
  
  // Exit:

  return result;
}

bool
fiber_bundle::sec_tp::
is_covariant(int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  bool result = host()->is_covariant(_index, xi, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::sec_tp::
put_is_covariant(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  host()->put_is_covariant(_index, xauto_access);

  // Postconditions:

  ensure(is_covariant(xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::sec_tp::
put_is_covariant(int xi, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  host()->put_is_covariant(_index, xi, xauto_access);

  // Postconditions:

  ensure(is_covariant(xi, xauto_access));
  
  // Exit:

  return;
}

bool
fiber_bundle::sec_tp::
is_contravariant(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  bool result = host()->is_contravariant(_index, xauto_access);

  // Postconditions:
  
  // Can not ensure result == !is_covariant because at0 is both co- and contra-vairant.

  // Exit:

  return result;
}

bool
fiber_bundle::sec_tp::
is_contravariant(int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  bool result = host()->is_contravariant(_index, xi, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::sec_tp::
put_is_contravariant(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  host()->put_is_contravariant(_index, xauto_access);

  // Postconditions:
  
  ensure(is_contravariant(xauto_access));

  // Exit:

  return;
}

void
fiber_bundle::sec_tp::
put_is_contravariant(int xi, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  host()->put_is_contravariant(_index, xi, xauto_access);

  // Postconditions:

  ensure(is_contravariant(xi, xauto_access));
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_TP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_TP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_TP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::sec_tp::
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
fiber_bundle::sec_tp::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_tp");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_tp*
fiber_bundle::sec_tp::
clone() const
{
  // Preconditions:

  // Body:

  sec_tp* result = 0;

  // Create new handle of the current class.

  result = new sec_tp();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_tp::host_type*
fiber_bundle::sec_tp::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::sec_tp::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_TP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_tp::
fiber_is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const tp*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_tp::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_tp*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_tp::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(sec_vd::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance(is_attached() ? (p() >= 0) : true);

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

#include "error_message.h"
#include "sec_at0.h"
#include "sec_at1.h"
#include "sec_at2.h"
#include "sec_at3_e3.h"
#include "sec_atp.h"
#include "sec_st2.h"
#include "sec_st3.h"
#include "sec_st3_e3.h"
#include "sec_st4_e2.h"
#include "sec_st4_e3.h"
#include "sec_stp.h"
#include "sec_t2.h"
#include "sec_t3.h"
#include "sec_t3_e3.h"
#include "sec_t4_e2.h"
#include "sec_t4_e3.h"

void
fiber_bundle::sec_tp_algebra::
alt(const sec_tp& x0, sec_atp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // Body:

  // Downcast implementation of multi dispatching.

  const sec_t2* t2_x0  = dynamic_cast<const sec_t2*>(&x0);
  const sec_t3* t3_x0  = dynamic_cast<const sec_t3*>(&x0);
  const sec_t3_e3* t3_e3_x0 = dynamic_cast<const sec_t3_e3*>(&x0);

  sec_at2* at2_xresult = dynamic_cast<sec_at2*>(&xresult);
  sec_t2* t2_xresult = dynamic_cast<sec_t2*>(&xresult);
  sec_at3_e3* at3_e3_xresult = dynamic_cast<sec_at3_e3*>(&xresult);
  sec_at3* at3_xresult = dynamic_cast<sec_at3*>(&xresult);
  sec_t3* t3_xresult = dynamic_cast<sec_t3*>(&xresult);

  if(t2_x0 && at2_xresult)
  {
    alt(*t2_x0, *at2_xresult, xauto_access);
  }
  else if(t2_x0 && t2_xresult)
  {
    alt(*t2_x0, *t2_xresult, xauto_access);
  }
  else if(t3_e3_x0 && at3_e3_xresult)
  {
    alt(*t3_e3_x0, *at3_e3_xresult, xauto_access);
  }
  else if(t3_x0 && t3_xresult)
  {
    alt(*t3_x0, *t3_xresult, xauto_access);
  }
  else if(t3_x0 && at3_xresult)
  {
    alt(*t3_x0, *at3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to tensor(...)");
  } 

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_tp_algebra::
sym(const sec_tp& x0, sec_stp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // Body:

  // Downcast implementation of multi dispatching.

  const sec_t2* t2_x0  = dynamic_cast<const sec_t2*>(&x0);
  const sec_t3* t3_x0  = dynamic_cast<const sec_t3*>(&x0);
  const sec_t3_e3* t3_e3_x0 = dynamic_cast<const sec_t3_e3*>(&x0);
  const sec_t4_e2* t4_e2_x0 = dynamic_cast<const sec_t4_e2*>(&x0);
  const sec_t4_e3* t4_e3_x0 = dynamic_cast<const sec_t4_e3*>(&x0);

  sec_st2* st2_xresult = dynamic_cast<sec_st2*>(&xresult);
  sec_st3* st3_xresult = dynamic_cast<sec_st3*>(&xresult);
  sec_st3_e3* st3_e3_xresult = dynamic_cast<sec_st3_e3*>(&xresult);
  sec_t2* t2_xresult = dynamic_cast<sec_t2*>(&xresult);
  sec_t3* t3_xresult = dynamic_cast<sec_t3*>(&xresult);
  sec_st4_e2* st4_e2_xresult = dynamic_cast<sec_st4_e2*>(&xresult);
  sec_st4_e3* st4_e3_xresult = dynamic_cast<sec_st4_e3*>(&xresult);

  if(t2_x0 && st2_xresult)
  {
    sym(*t2_x0, *st2_xresult, xauto_access);
  }
  else if(t2_x0 && t2_xresult)
  {
    sym(*t2_x0, *t2_xresult, xauto_access);
  }
  else if(t3_e3_x0 && st3_e3_xresult)
  {
    sym(*t3_e3_x0, *st3_e3_xresult, xauto_access);
  }
  else if(t3_x0 && t3_xresult)
  {
    sym(*t3_x0, *t3_xresult, xauto_access);
  }
  else if(t3_x0 && st3_xresult)
  {
    sym(*t3_x0, *st3_xresult, xauto_access);
  }
  else if(t4_e2_x0 && st4_e2_xresult)
  {
    sym(*t4_e2_x0, *st4_e2_xresult, xauto_access);
  }
  else if(t4_e3_x0 && st4_e3_xresult)
  {
    sym(*t4_e3_x0, *st4_e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to tensor(...)");
  } 

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_tp_algebra::
contract(const sec_tp& x0, int xp, int xq, sec_tp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xp != xq);
  require(xp >= 0 && xp < x0.p(xauto_access));
  require(xq >= 0 && xq < x0.p(xauto_access));
  require(x0.is_contravariant(xp, xauto_access) != \
    x0.is_contravariant(xq, xauto_access));

  // Body:

  // Downcast implementation of multi dispatching.

  const sec_t2* t2_x0  = dynamic_cast<const sec_t2*>(&x0);
  const sec_t3* t3_x0  = dynamic_cast<const sec_t3*>(&x0);

  sec_at0* at0_xresult = dynamic_cast<sec_at0*>(&xresult);
  sec_at1* at1_xresult = dynamic_cast<sec_at1*>(&xresult);

  if(t2_x0 && at0_xresult)
  {
    contract(*t2_x0, xp, xq, *at0_xresult, xauto_access);
  }
  else if(t3_x0 && at1_xresult)
  {
    contract(*t3_x0, xp, xq, *at1_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to tensor(...)");
  } 

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::sec_tp_algebra::
tensor(const sec_tp& x0, const sec_tp& x1, sec_tp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(xresult.dd(xauto_access) == x0.dd(xauto_access));

  // Body:

  // Downcast implementation of multi dispatch.
    
  const sec_at1* at1_x0 = dynamic_cast<const sec_at1*>(&x0);
  const sec_at2* at2_x0 = dynamic_cast<const sec_at2*>(&x0);
  const sec_st2* st2_x0 = dynamic_cast<const sec_st2*>(&x0);
  const sec_t2*  t2_x0  = dynamic_cast<const sec_t2*>(&x0);

  const sec_at1* at1_x1 = dynamic_cast<const sec_at1*>(&x1);
  const sec_at2* at2_x1 = dynamic_cast<const sec_at2*>(&x1);
  const sec_st2* st2_x1 = dynamic_cast<const sec_st2*>(&x1);
  const sec_t2*  t2_x1  = dynamic_cast<const sec_t2*>(&x1);

  sec_t2* t2_xresult = dynamic_cast<sec_t2*>(&xresult);
  sec_t3* t3_xresult = dynamic_cast<sec_t3*>(&xresult);

  if(at1_x0 && at1_x1 && t2_xresult)
  {
    tensor(*at1_x0, *at1_x1, *t2_xresult, xauto_access);
  }
  else if(t2_x0 && at1_x1 && t3_xresult)
  {
  tensor(*t2_x0, *at1_x1, *t3_xresult, xauto_access);
  }
  else if(at1_x0 && t2_x1 && t3_xresult)
  {
    tensor(*at1_x0, *t2_x1, *t3_xresult, xauto_access);
  }
  else if(at2_x0 && at1_x1 && t3_xresult)
  {
    tensor(*at2_x0, *at1_x1, *t3_xresult, xauto_access);
  }
  else if(at1_x0 && at2_x1 && t3_xresult)
  {
    tensor(*at1_x0, *at2_x1, *t3_xresult, xauto_access);
  }
  else if(st2_x0 && at1_x1 && t3_xresult)
  {
    tensor(*st2_x0, *at1_x1, *t3_xresult, xauto_access);
  }
  else if(at1_x0 && st2_x1 && t3_xresult)
  {
    tensor(*at1_x0, *st2_x1, *t3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to tensor(...)");
  } 
  
  // Postconditions:

  // Exit:

  return;
}

