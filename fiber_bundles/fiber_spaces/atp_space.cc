
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

// Implementation for class atp_space.

#include "atp_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at1_space.h"
#include "atp.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// ATP_SPACE FACET public member functions
//==============================================================================

///
const string&
fiber_bundle::atp_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = atp::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::atp_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = atp::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

int
fiber_bundle::atp_space::
d(const namespace_poset& xns, int xp, const poset_path& xvector_space_path, bool xauto_access)
{
  // Preconditions:

  require(xp >= 0);
  
  require(xns.path_is_auto_read_accessible<vector_space_type>(xvector_space_path, xauto_access));
 
  // Body:

  int ldd = xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).d();  

  atp_space ltmp;
  int result = ltmp.d(xp, ldd);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

fiber_bundle::atp_space&
fiber_bundle::atp_space::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path,
          int xp,
          const poset_path& xvector_space_path, 
          bool xauto_access)
{
  // cout << endl << "Entering atp_space::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(xp >= 0);

  require(xns.path_is_auto_read_accessible<vector_space_type>(xvector_space_path, xauto_access));

  require(d(xns, xschema_path, xauto_access) == d(xns, xp, xvector_space_path, xauto_access));   

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef atp_space table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Get the dimension (== number of row dofs) defined by the schema.

  int ld = lschema.row_dof_ct();

  // Get the dimension of the domain vector space.

  int ldd = xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).d();

  // Get the scalar space path from the domain vector space.

  poset_path lscalar_space_path = xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access);
  
  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("factor_ct", ld);
  lmap->put_dof("d", ld);
  lmap->put_dof("scalar_space_path", lscalar_space_path);
  lmap->put_dof("p", xp);
  lmap->put_dof("dd", ldd);
  lmap->put_dof("vector_space_path", xvector_space_path);
  
  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  atp_space& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == d(xns, xschema_path, xauto_access));
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access) );
  ensure(result.p(true) == xp);
  ensure(result.dd(true) == xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).d());
  ensure(result.vector_space_path(true) == xvector_space_path );

  // Exit:

  // cout << "Leaving atp_space::new_table." << endl;
  return result;
} 

bool
fiber_bundle::atp_space::
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
fiber_bundle::atp_space::
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
fiber_bundle::atp_space::
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
fiber_bundle::atp_space::
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
fiber_bundle::atp_space::
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
fiber_bundle::atp_space::
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
fiber_bundle::atp_space::
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
fiber_bundle::atp_space::
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

// ===========================================================
// ATP_SPACE FACET protected member functions
// ===========================================================
 
fiber_bundle::atp_space::
atp_space()
  : tp_space(new atp, new atp)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(tp_space::tp_space()));
}

fiber_bundle::atp_space::
~atp_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::atp_space::
atp_space(atp* xtop, atp* xbottom)
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

// ===========================================================
// TP_SPACE FACET public member functions
// ===========================================================

int
fiber_bundle::atp_space::
d(int xp, int xdd) const
{
  return static_cast<int>(binomial_coefficient(xdd, xp));
}

///
fiber_bundle::tensor_variance
fiber_bundle::atp_space::
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
fiber_bundle::atp_space::
covariant_subposet_ct() const
{
  return 1;
}
 

// ===========================================================
// POSET FACET
// =========================================================== 

bool
fiber_bundle::atp_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  atp_space* lproto = new atp_space;
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
fiber_bundle::atp_space::
type_id() const
{
  return ATP_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::atp_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "atp_space";

  // Postconditions:

  // Exit:

  return result;
}

//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::atp_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const atp_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::atp_space*
fiber_bundle::atp_space::
clone() const
{
  atp_space* result;

  // Preconditions:

  // Body:

  result = new atp_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::atp_space::
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



