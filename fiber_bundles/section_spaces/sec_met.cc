
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
/// Implementation for class sec_met.

#include "SheafSystem/sec_met.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/binary_section_space_schema_member.impl.h"
#include "SheafSystem/binary_section_space_schema_poset.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_at0_space.h"
#include "SheafSystem/sec_stp_space.h"
#include "SheafSystem/sec_tuple_space.impl.h"
#include "SheafSystem/section_space_schema_member.impl.h"
#include "SheafSystem/section_space_schema_poset.h"
#include "SheafSystem/stp.h"
#include "SheafSystem/stp_space.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_MET
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS SEC_ST2
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_met::host_type&
fiber_bundle::sec_met::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xscalar_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_met::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
  require(host_type::fiber_space_conforms<fiber_type::host_type>(xns, xschema_path, xauto_access));

  require(xns.path_is_auto_read_accessible<scalar_type::host_type>(xscalar_space_path, xauto_access));

  require(host_type::same_scalar_fiber_space(xns, xschema_path, xscalar_space_path, xauto_access));

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xscalar_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.d(true) == result.dd(true));
  ensure(result.scalar_space_path(true) == xscalar_space_path);
  ensure(result.p(true) == result.schema(true).fiber_space<fiber_type::host_type>().p(xauto_access));
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.vector_space_path(true) == xhost_path);

  // Exit:

  // cout << "Leaving sec_met::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// MET FACET OF CLASS SEC_MET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_met::
sec_met()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

fiber_bundle::sec_met::
sec_met(const sec_rep_space* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_met::
sec_met(const sec_rep_space* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_met::
sec_met(const sec_rep_space* xhost, const std::string& xname)
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
  //ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());
  ensure(!is_restricted());

}


fiber_bundle::sec_met::
sec_met(const namespace_poset* xnamespace,
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


fiber_bundle::sec_met::
sec_met(const sec_rep_space_member* xother)
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

fiber_bundle::sec_met::
sec_met(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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

fiber_bundle::sec_met&
fiber_bundle::sec_met::
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

fiber_bundle::sec_met&
fiber_bundle::sec_met::
operator=(const sec_met& xother)
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

fiber_bundle::sec_met&
fiber_bundle::sec_met::
operator=(const met& xfiber)
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

fiber_bundle::sec_met&
fiber_bundle::sec_met::
operator=(const met_lite& xfiber)
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

fiber_bundle::sec_met::
~sec_met()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_met::fiber_type&
fiber_bundle::sec_met::
fiber_prototype() const
{
  // Preconditions:

  // Body:

  static const fiber_type result;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET OF CLASS SEC_MET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// STP FACET OF CLASS SEC_MET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS SEC_MET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_MET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_MET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_MET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::sec_met::
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
fiber_bundle::sec_met::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_met");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_met*
fiber_bundle::sec_met::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_met *result = new sec_met();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_MET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_met::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const met*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_met::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_met*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_met::
invariant() const
{

  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(sec_st2::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//##############################################################################
//##############################################################################

// fiber_bundle::sec_met::scalar_type*
// fiber_bundle::sec_met::
// comp2(int row, int col)
// {

//   // Preconditions:

//   require(0 <= row && row <= dd());
//   require(0 <= col && col <= dd());

//   // Body:

//   int index = index_for_row_column(row, col);
//   scalar_type* result = comp(index);

//   // Postconditions:

//   ensure(result != 0);
//   ensure(invariant());
//   ensure(result->invariant());

//   return result;

// }


// void
// fiber_bundle::sec_met::
// set_comp2(int row, int col, scalar_type* new_comp)
// {

//   // Preconditions:

//   require(0 <= row && row <= dd());
//   require(0 <= col && col <= dd());
//   require(new_comp != 0);

//   // Body:

//   int index = index_for_row_column(row, col);
//   set_comp(index, new_comp);

//   // Postconditions:

//   ensure(comp(index) == new_comp);
//   ensure(invariant());

// }

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

#include "SheafSystem/error_message.h"
#include "SheafSystem/sec_e1.h"
#include "SheafSystem/sec_e2.h"
#include "SheafSystem/sec_e3.h"
#include "SheafSystem/sec_met_e1.h"
#include "SheafSystem/sec_met_e2.h"
#include "SheafSystem/sec_met_e3.h"

void
fiber_bundle::sec_met_algebra::
lower(const sec_met& xmetric, const sec_ed& xvector, sec_ed& xresult,
      bool xauto_access)
{
  // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xmetric.is_covariant(0, xauto_access));
  require(xvector.is_contravariant(0, xauto_access)); // !is_dual;

  // Body:

  const sec_met_e1* met_e1_xmetric = dynamic_cast<const sec_met_e1*>(&xmetric);
  const sec_met_e2* met_e2_xmetric = dynamic_cast<const sec_met_e2*>(&xmetric);
  const sec_met_e3* met_e3_xmetric = dynamic_cast<const sec_met_e3*>(&xmetric);

  const sec_e1* e1_xvector = dynamic_cast<const sec_e1*>(&xvector);
  const sec_e2* e2_xvector = dynamic_cast<const sec_e2*>(&xvector);
  const sec_e3* e3_xvector = dynamic_cast<const sec_e3*>(&xvector);

  sec_e1* e1_xresult = dynamic_cast<sec_e1*>(&xresult);
  sec_e2* e2_xresult = dynamic_cast<sec_e2*>(&xresult);
  sec_e3* e3_xresult = dynamic_cast<sec_e3*>(&xresult);

  if(met_e1_xmetric &&  e1_xvector && e1_xresult)
  {
    lower(*met_e1_xmetric, *e1_xvector, *e1_xresult, xauto_access);
  }
  else if(met_e2_xmetric &&  e2_xvector && e2_xresult)
  {
    lower(*met_e2_xmetric, *e2_xvector, *e2_xresult, xauto_access);
  }
  else if(met_e3_xmetric &&  e3_xvector && e3_xresult)
  {
    lower(*met_e3_xmetric, *e3_xvector, *e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to lower(...)");
  }

  // Postconditions:

  ensure(xresult.is_covariant(0, xauto_access));     //  is_dual

  // Exit:

  return;
}

void
fiber_bundle::sec_met_algebra::
raise(const sec_met& xmetric, const sec_ed& xcovector, sec_ed& xresult,
      bool xauto_access)
{
  // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xmetric.is_contravariant(0, xauto_access));
  require(xcovector.is_covariant(0, xauto_access));   //  is_dual;

  // Body:

  const sec_met_e1* met_e1_xmetric = dynamic_cast<const sec_met_e1*>(&xmetric);
  const sec_met_e2* met_e2_xmetric = dynamic_cast<const sec_met_e2*>(&xmetric);
  const sec_met_e3* met_e3_xmetric = dynamic_cast<const sec_met_e3*>(&xmetric);

  const sec_e1* e1_xcovector = dynamic_cast<const sec_e1*>(&xcovector);
  const sec_e2* e2_xcovector = dynamic_cast<const sec_e2*>(&xcovector);
  const sec_e3* e3_xcovector = dynamic_cast<const sec_e3*>(&xcovector);

  sec_e1* e1_xresult = dynamic_cast<sec_e1*>(&xresult);
  sec_e2* e2_xresult = dynamic_cast<sec_e2*>(&xresult);
  sec_e3* e3_xresult = dynamic_cast<sec_e3*>(&xresult);

  if(met_e1_xmetric &&  e1_xcovector && e1_xresult)
  {
    lower(*met_e1_xmetric, *e1_xcovector, *e1_xresult, xauto_access);
  }
  else if(met_e2_xmetric &&  e2_xcovector && e2_xresult)
  {
    lower(*met_e2_xmetric, *e2_xcovector, *e2_xresult, xauto_access);
  }
  else if(met_e3_xmetric &&  e3_xcovector && e3_xresult)
  {
    lower(*met_e3_xmetric, *e3_xcovector, *e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to lower(...)");
  }

  // Postconditions:

  ensure(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Exit:

  return;
}

