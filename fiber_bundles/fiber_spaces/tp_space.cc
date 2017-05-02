
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

// Implementation for class tp_space.

#include "SheafSystem/tp_space.h"

#include "SheafSystem/abstract_poset_member.impl.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/namespace_poset.impl.h"
#include "SheafSystem/namespace_poset_member.h"
#include "SheafSystem/poset_handle_factory.h"
#include "SheafSystem/tp.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// TP_SPACE FACET public member functions
//==============================================================================

const std::string&
fiber_bundle::tp_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = tp::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::poset_path&
fiber_bundle::tp_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = tp::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

int
fiber_bundle::tp_space::
d(const namespace_poset& xns, const poset_path& xschema_path, bool xauto_access)
{
  // Preconditions:

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
 
  // Body:

  int result = schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access);

  // Postconditions:

  ensure(result == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));

  // Exit:

  return result;
}

int
fiber_bundle::tp_space::
d(const namespace_poset& xns, int xp, const poset_path& xvector_space_path, bool xauto_access)
{
  // Preconditions:

  require(xp >= 0);
  
  require(xns.path_is_auto_read_accessible<vector_space_type>(xvector_space_path, xauto_access));
 
  // Body:

  int ldd = xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).d();  

  tp_space ltmp;
  int result = ltmp.d(xp, ldd);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

fiber_bundle::tp_space&
fiber_bundle::tp_space::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path, 
          int xp,
          const poset_path& xvector_space_path, 
          bool xauto_access)
{
  // cout << endl << "Entering tp_space::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(xns.path_is_auto_read_accessible<vector_space_type>(xvector_space_path, xauto_access));

  require(d(xns, xschema_path, xauto_access) == d(xns, xp, xvector_space_path, xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef tp_space table_type;

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

  tp_space& result = *ltable;

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

  // cout << "Leaving tp_space::new_table." << endl;
  return result;
} 

int
fiber_bundle::tp_space::
d(int xp, int xdd) const
{
  return static_cast<int>(pow(static_cast<double>(xdd), xp));
}

int
fiber_bundle::tp_space::
p(int xd, int xdd) const
{
  // cout << endl << "Entering tp_space::p." << endl;

  // Preconditions:

  require(xd > 0);
  require(xdd > 0);
  
  // Body:

  int lp = 0;
  int lpd = 1;
  while(lpd < xd)
  {
    lp++;
    lpd  = d(lp, xdd);
  }

  int result = (lpd == xd) ? lp : -1;

  // Postconditions:

  ensure(unexecutable("result < 0 implies schema dimension inconsistent with vector space dimension"));

  // Exit:

  // cout << "Leaving tp_space::p." << endl;
  return result;
}


int
fiber_bundle::tp_space::
p() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  int result = sheaf::table_dofs(*this).p;  

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::tp_space::
p(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  int result = sheaf::table_dofs(*this).p;
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::tp_space::
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
fiber_bundle::tp_space::
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
fiber_bundle::tp_space::
vector_space_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(sheaf::table_dofs(*this).vector_space_path);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::tp_space::
vector_space_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).vector_space_path);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::tp_space::
variance(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  int lp = p();
  tensor_variance result(lp);

  for(int i=0; i<lp; ++i)
  {
    result.put_variance(i, is_covariant(xmbr_id, i, false));
  }
  
  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::tp_space::
variance(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_variance_subposets(xauto_access));
  
  // Body:

  return variance(xmbr_id.hub_pod(), xauto_access);
}

bool
fiber_bundle::tp_space::
variance(pod_index_type xmbr_id, int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  bool result = is_covariant(xmbr_id, xi, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::tp_space::
variance(const scoped_index& xmbr_id, int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  return variance(xmbr_id.hub_pod(), xi, xauto_access);
}

void
fiber_bundle::tp_space::
put_variance(pod_index_type xmbr_id, const tensor_variance& xvariance, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(xvariance.p() == p(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }
  
  int lct = covariant_subposet_ct();
  
  for(int i=0; i<lct; ++i)
  {
    put_variance(xmbr_id, i, xvariance.variance(i), false);
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(variance(xmbr_id, xauto_access) == round_variance(xvariance));
  
  // Exit:

  return;
}

void
fiber_bundle::tp_space::
put_variance(const scoped_index& xmbr_id, const tensor_variance& xvariance, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(xvariance.p() == p(xauto_access));
  
  // Body:

  put_variance(xmbr_id.hub_pod(), xvariance, xauto_access);

  // Postconditions:

  ensure(variance(xmbr_id, xauto_access) == round_variance(xvariance));
  
  // Exit:

  return;
}

void
fiber_bundle::tp_space::
put_variance(pod_index_type xmbr_id, int xi, bool xvariance, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  if(xvariance)
  {
    put_is_covariant(xmbr_id, xi, xauto_access);
  }
  else
  {
    put_is_contravariant(xmbr_id, xi, xauto_access);
  }
  
  // Postconditions:

  ensure(variance(xmbr_id, xi, xauto_access) == xvariance);
  
  // Exit:

  return;
}

void
fiber_bundle::tp_space::
put_variance(const scoped_index& xmbr_id, int xi, bool xvariance, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  put_variance(xmbr_id.hub_pod(), xi, xvariance, xauto_access);
  
  // Postconditions:

  ensure(variance(xmbr_id, xi, xauto_access) == xvariance);
  
  // Exit:

  return;
}

fiber_bundle::tensor_variance
fiber_bundle::tp_space::
round_variance(const tensor_variance& xvariance) const
{
  // Preconditions:
  
  // Body:

  // Postconditions:

  // Exit:

  return xvariance;
}

bool
fiber_bundle::tp_space::
is_covariant(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result = true;
  int lp = covariant_subposet_ct();
  for(int i=0; i<lp && result; ++i)
  {
    subposet lsp(this, covariant_subposet_name(i));
    bool result = lsp.contains_member(xmbr_id);
    lsp.detach_from_state();
  }  

  // The above implementation returns the correct result for p == 0.

  assertion(p() == 0 ? result : true);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  
  // Exit:

  return result;
}

bool
fiber_bundle::tp_space::
is_covariant(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  return is_covariant(xmbr_id.hub_pod(), xauto_access);
}

bool
fiber_bundle::tp_space::
is_covariant(pod_index_type xmbr_id, int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  require(contains_variance_subposets(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  // Since precondition ensures xi >= 0 and xi < p; p can not be 0.
  // So covaraint_subposet_ct() is either p or 1. If only 1,
  // then we have either an stp or an atp and setting the variance
  // of any index is equivalent to setting them all.

  int lxi = (covariant_subposet_ct() > 1) ? xi : 0;

  /// @issue Access by name lookup is not terribly efficient,
  /// but it will have to do until we get id spaces for subposets working
  /// or devise some other mechanism.

  subposet lsp(this, covariant_subposet_name(lxi));
  bool result = lsp.contains_member(xmbr_id);
  lsp.detach_from_state();

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::tp_space::
is_covariant(const scoped_index& xmbr_id, int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  require(contains_variance_subposets(xauto_access));
  
  // Body:

  return is_covariant(xmbr_id.hub_pod(), xi, xauto_access);
}

void
fiber_bundle::tp_space::
put_is_covariant(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  int lp = covariant_subposet_ct();
  for(int i=0; i<lp; ++i)
  {
    subposet lcovariant(this, covariant_subposet_name(i));
    lcovariant.insert_member(xmbr_id);
    lcovariant.detach_from_state();
  }  

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_covariant(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::tp_space::
put_is_covariant(const scoped_index& xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  put_is_covariant(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_covariant(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::tp_space::
put_is_covariant(pod_index_type xmbr_id, int xi, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  // Since precondition ensures xi >= 0 and xi < p; p can not be 0.
  // So covaraint_subposet_ct() is either p or 1. If only 1,
  // then we have either an stp or an atp and setting the variance
  // of any index is equivalent to setting them all.

  int lxi = (covariant_subposet_ct() > 1) ? xi : 0;

  // $$SCRIBBLE: access by name lookup is not terribly efficient,
  // but it will have to do until we get id spaces for subposets working
  // or devise some other mechanism.

  subposet lsp(this, covariant_subposet_name(lxi));
  lsp.insert_member(xmbr_id);
  lsp.detach_from_state();

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:

  ensure(is_covariant(xmbr_id, xi, xauto_access));

  // Exit:

  return;
}

void
fiber_bundle::tp_space::
put_is_covariant(const scoped_index& xmbr_id, int xi, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));

  // Body:

  put_is_covariant(xmbr_id.hub_pod(), xi, xauto_access);
  
  // Postconditions:

  ensure(is_covariant(xmbr_id, xi, xauto_access));

  // Exit:

  return;
}

bool
fiber_bundle::tp_space::
is_contravariant(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  bool result = true;
  int lp = covariant_subposet_ct();
  for(int i=0; i<lp && result; ++i)
  {
    subposet lsp(this, covariant_subposet_name(i));
    bool result = !lsp.contains_member(xmbr_id);
    lsp.detach_from_state();
  }  

  // The above implementation returns the correct result for p == 0.

  assertion(p() == 0 ? result : true);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Can not ensure result == !is_covariant because at0 is both co- and contra-variant.
  
  // Exit:

  return result;
}

bool
fiber_bundle::tp_space::
is_contravariant(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  return is_contravariant(xmbr_id.hub_pod(), xauto_access);
}

bool
fiber_bundle::tp_space::
is_contravariant(pod_index_type xmbr_id, int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  bool result = !is_covariant(xmbr_id, xi, xauto_access);

  // Postconditions:

  // Can ensure result == !is_covariant because although 
  // at0 is both co- and contra-variant, at0::p() == 0 so this
  // function can not be invoked. But to be consistent,
  // let's just not ensure it.

  //  ensure(result == !is_covariant(xmbr_id, xi, xauto_access));
  
  // Exit:

  return result;
}

bool
fiber_bundle::tp_space::
is_contravariant(const scoped_index& xmbr_id, int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  return is_contravariant(xmbr_id.hub_pod(), xi, xauto_access);
}

void
fiber_bundle::tp_space::
put_is_contravariant(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  int lp = covariant_subposet_ct();
  for(int i=0; i<lp; ++i)
  {
    subposet lcovariant(this, covariant_subposet_name(i));
    lcovariant.remove_member(xmbr_id);
    lcovariant.detach_from_state();
  }  

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_contravariant(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::tp_space::
put_is_contravariant(const scoped_index& xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  
  // Body:

  put_is_contravariant(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_contravariant(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::tp_space::
put_is_contravariant(pod_index_type xmbr_id, int xi, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  // Since precondition ensures xi >= 0 and xi < p; p can not be 0.
  // So covaraint_subposet_ct() is either p or 1. If only 1,
  // then we have either an stp or an atp and setting the variance
  // of any index is equivalent to setting them all.

  int lxi = (covariant_subposet_ct() > 1) ? xi : 0;
  
  // $$SCRIBBLE: access by name lookup is not terribly efficient,
  // but it will have to do until we get id spaces for subposets working
  // or devise some other mechanism.

  subposet lsp(this, covariant_subposet_name(lxi));
  lsp.remove_member(xmbr_id);
  lsp.detach_from_state();

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:

  ensure(is_contravariant(xmbr_id, xi, xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::tp_space::
put_is_contravariant(const scoped_index& xmbr_id, int xi, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));

  // Body:

  put_is_contravariant(xmbr_id.hub_pod(), xi, xauto_access);
  
  // Postconditions:

  ensure(is_contravariant(xmbr_id, xi, xauto_access));
  
  // Exit:

  return;
}

// ===========================================================
// TP_SPACE FACET protected member functions
// ===========================================================
 

fiber_bundle::tp_space::
tp_space()
  : vd_space(new tp, new tp)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(vd_space::vd_space()));
}

fiber_bundle::tp_space::
~tp_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::tp_space::
tp_space(tp* xtop, tp* xbottom)
  : vd_space(xtop, xbottom)
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

sheaf::size_type
fiber_bundle::tp_space::
covariant_subposet_ct() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  size_type result = p();
  
  // Postconditions:
  
  // Exit:

  return result;
}

// ===========================================================
// POSET FACET
// =========================================================== 

bool
fiber_bundle::tp_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  tp_space* lproto = new tp_space;
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
fiber_bundle::tp_space::
type_id() const
{
  return TP_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::tp_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "tp_space";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::tp_space::
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

      result = name_space()->member_id(vector_space_path().poset_name(), false);
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

//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::tp_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const tp_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::tp_space*
fiber_bundle::tp_space::
clone() const
{
  tp_space* result;

  // Preconditions:

  // Body:

  result = new tp_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::tp_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(vd_space::invariant());

    invariance(state_is_read_accessible() ? factor_ct() == d() : true);
    
    enable_invariant_check();
  }

  return result;
}



