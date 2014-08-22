
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
/// Implementation for class sec_atp_space.

#include "ComLimitPoint/fiber_bundle/sec_atp_space.h"

#include "ComLimitPoint/sheaf/abstract_poset_member.impl.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_member.impl.h"
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_poset.h"
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#include "ComLimitPoint/sheaf/namespace_poset.impl.h"
#include "ComLimitPoint/sheaf/namespace_poset_member.h"
#include "ComLimitPoint/sheaf/poset_handle_factory.h"
#include "ComLimitPoint/fiber_bundle/sec_at1.h"
#include "ComLimitPoint/fiber_bundle/sec_at1_space.h"
#include "ComLimitPoint/fiber_bundle/sec_atp.h"
#include "ComLimitPoint/fiber_bundle/sec_tuple_space.impl.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_member.impl.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_poset.h"
#include "ComLimitPoint/fiber_bundle/atp.h"
#include "ComLimitPoint/fiber_bundle/atp_space.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// SEC_ATP_SPACE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_atp_space&
fiber_bundle::sec_atp_space::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path,
          const poset_path& xvector_space_path, 
          bool xauto_access)
{
  // cout << endl << "Entering sec_atp_space::new_table." << endl;

  // Preconditions:


  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
  require(fiber_space_conforms<fiber_type::host_type>(xns, xschema_path, xauto_access));

  require(xns.path_is_auto_read_accessible<vector_space_type::host_type>(xvector_space_path, xauto_access));

  require(same_vector_fiber_space(xns, xschema_path, xvector_space_path, xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef sec_atp_space table_type;

  table_type& result = *(new table_type());

  // Create a handle of the right type for the schema member.

  schema_type lschema(xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Get the section scalar space path from the section vector space.

  poset_path lscalar_space_path = 
    xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access);

  // Create the table dof map.

  array_poset_dof_map& lmap = *(new array_poset_dof_map(&lschema, true));

  // The table dofs are mostly the same as the fiber schema,
  // so just copy them from the fiber schema.
  // Can't use copy constructor because schema objects are different.

  array_poset_dof_map& lfiber_map = lschema.fiber_space().table_dof_map();
  lmap.copy_dof_tuple(lfiber_map);

  // Replace the fiber scalar space path with the section scalar space path.

  lmap.put_dof("scalar_space_path", lscalar_space_path);

  // Replace the fiber vector space path with the section vector space path.

  lmap.put_dof("vector_space_path", xvector_space_path);
  
  // Create the state.

  result.new_state(xns, xpath, lschema, lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
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

  // cout << "Leaving sec_atp_space::new_table." << endl;
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



