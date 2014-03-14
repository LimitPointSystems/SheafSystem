
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
/// Implementation for class sec_vd.

#include "sec_vd.h"

#include "array_section_dof_map.h"
#include "assert_contract.h"
#include "at0.h"
#include "binary_section_space_schema_member.impl.h"
#include "binary_section_space_schema_poset.h"
#include "chart_point.h"
#include "eval_family.h"
#include "eval_iterator.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "namespace_poset.h"
#include "sec_at0.h"
#include "sec_tuple_space.impl.h"
#include "sec_vd_space.h"
#include "section_evaluator.h"
#include "section_space_schema_member.impl.h"
#include "section_space_schema_poset.h"
#include "vd.h"
#include "vd_space.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_VD
//==============================================================================
// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_vd::host_type&
fiber_bundle::sec_vd::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xscalar_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_vd::new_host." << endl;

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
  ensure(result.scalar_space_path(true) == xscalar_space_path);

  // Exit:

  // cout << "Leaving sec_vd::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
//==============================================================================
// VD FACET OF CLASS SEC_VD
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_vd::
sec_vd()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_vd::
sec_vd(const sec_rep_space* xhost, pod_index_type xhub_id)
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

fiber_bundle::sec_vd::
sec_vd(const sec_rep_space* xhost, const scoped_index& xid)
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

fiber_bundle::sec_vd::
sec_vd(const sec_rep_space* xhost, const std::string& xname)
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

fiber_bundle::sec_vd::
sec_vd(const namespace_poset* xnamespace,
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


fiber_bundle::sec_vd::
sec_vd(sec_rep_space_member* xother)
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

fiber_bundle::sec_vd::
sec_vd(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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

fiber_bundle::sec_vd::
sec_vd(sec_rep_space* xhost,
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

fiber_bundle::sec_vd&
fiber_bundle::sec_vd::
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

fiber_bundle::sec_vd&
fiber_bundle::sec_vd::
operator=(const sec_vd& xother)
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

fiber_bundle::sec_vd&
fiber_bundle::sec_vd::
operator=(const vd& xfiber)
{
  // Preconditions:

  require(is_attached());
  require(state_is_read_write_accessible());
  //require(); @todo: Complete.

  // Body:

  /// @todo Implement like the assignment operator for vd_lite once
  /// a virtual copy constructor is available.

  void* lrow_dofs = const_cast<void*>(xfiber.row_dofs());
  dof_type* lxfiber_dptr = static_cast<dof_type*>(lrow_dofs);
  size_type  lfiber_size = xfiber.d()*sizeof(dof_type);
  size_type ldisc_ct = discretization_ct();
  for(size_type i=0; i<ldisc_ct; ++i)
  {
    put_fiber(i, lxfiber_dptr, lfiber_size);
  }

  // Postconditions:

  //ensure(); @todo: Complete.

  // Exit:

  return *this;
}

fiber_bundle::sec_vd&
fiber_bundle::sec_vd::
operator=(const vd_lite& xfiber)
{
  // Preconditions:

  // Body:

  index_space_iterator& ldisc_itr =
    schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    put_fiber(ldisc_itr.pod(), xfiber);

    ldisc_itr.next();
  }
  schema().discretization_id_space().release_iterator(ldisc_itr);

  // Postconditions:

  // Exit:

  return *this;
}

fiber_bundle::sec_vd::
~sec_vd()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

bool
fiber_bundle::sec_vd::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const vd*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

const fiber_bundle::sec_vd::fiber_type&
fiber_bundle::sec_vd::
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
fiber_bundle::sec_vd::
d() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->d();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::sec_vd::
d(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  int result = host()->d(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_vd::
scalar_space_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(host()->scalar_space_path());

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_vd::
scalar_space_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  poset_path result(host()->scalar_space_path(xauto_access));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

bool
fiber_bundle::sec_vd::
is_vector(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  bool result = host()->is_vector(_index, xauto_access);

  // Postconditions:
  
  // Exit:

  return result;
}

void
fiber_bundle::sec_vd::
put_is_vector(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  host()->put_is_vector(_index, xauto_access);

  // Postconditions:

  ensure(is_vector(xauto_access));
  
  // Exit:

  return;
}

bool
fiber_bundle::sec_vd::
is_covector(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  bool result = host()->is_covector(_index, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::sec_vd::
put_is_covector(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  host()->put_is_covector(_index, xauto_access);

  // Postconditions:
  
  ensure(is_covector(xauto_access));

  // Exit:

  return;
}

fiber_bundle::sec_vd::scalar_type*
fiber_bundle::sec_vd::
comp(int i) const
{
  // Preconditions:

  require(0 <= i && i < df());

  // Body:

  scalar_type* result = 0;

  not_implemented();

  // Postconditions:

  ensure(result != 0);
  ensure(invariant());
  ensure(result->invariant());

  // Exit:

  return result;

}

void
fiber_bundle::sec_vd::
set_comp(int i, scalar_type* component)
{

  // Preconditions:

  require(0 <= i && i < df());
  require(component != 0);

  // Body:

  // Place component into the component storage.

  not_implemented();

  // Postconditions:

  //ensure(comp(i) == component);
  ensure(invariant());

}


fiber_bundle::vd*
fiber_bundle::sec_vd::
value_at_point(const chart_point& xpt, bool xauto_access) const
{
  vd* result;

  // Preconditions:

  require(precondition_of(fiber_prototype().clone()));
  require(precondition_of(value_at_point_pa(xpt, fiber_prototype().clone(), xauto_access)));

  // Body:

  result = fiber_prototype().clone();
  value_at_point_pa(xpt, *result, xauto_access);

  // Postconditions:

  ensure(postcondition_of(fiber_prototype().clone()));
  ensure(postcondition_of(value_at_point_pa(xpt, fiber_prototype().clone(), xauto_access)));

  // Exit:

  return result;
}

void
fiber_bundle::sec_vd::
value_at_point_pa(const chart_point& xpt, vd& result, bool xauto_access) const
{
  // Preconditions:

  require(!xauto_access ? result.state_is_read_accessible() : true);

  if(xauto_access)
  {
    result.get_read_access();
  }

  require(precondition_of(value_at_point_ua(xptr, result.row_dof_tuple(), xauto_access)));

  // Body:

  dof_type* ldofs = reinterpret_cast<dof_type*>(result.dof_map().dof_tuple());

  value_at_point_ua(xpt, ldofs, result.d());

  // Postconditions:

  ensure(postcondition_of(value_at_point_ua(xptr, result.row_dof_tuple(), xauto_access)));

  if(xauto_access)
  {
    result.release_access();
  }

  // Exit:

  return;
}

void
fiber_bundle::sec_vd::
value_at_point_ua(const chart_point& xpt,
                  value_type* xresult,
                  size_type xresult_ub,
                  bool xauto_access) const
{
  // Preconditions:

  require(!xauto_access ? state_is_read_accessible() : true);

  if(xauto_access)
  {
    get_read_access();
  }

  require(xpt.is_valid());

  require(schema().evaluation().contains_member(xpt.chart_id()));

  /// @hack the preceding needs to be replaced with the following.
  /// require(unexecutable(xpt.chart_id() is mappable to a member of schema().evaluation()));

  require(unexecutable("@hack not more than 32 dofs per eval member"));
  require(xresult != 0);
  require(xresult_ub >= schema().df());


  // Body:

  // Gather the dofs for xpt.chart_id().

  /// @hack assume discretization members are lower cover.

  sec_vd_dof_type lgathered_dofs[32];
  sec_vd_dof_type* ldofs = lgathered_dofs;
  size_type ldofs_ct = 0;
  int ldf = schema().df();

  poset_state_handle* lbase_host = base().host();

  typedef base_space_member::row_dof_tuple_type tuple_type;
  tuple_type* lchart_tuple =
    reinterpret_cast<tuple_type*>(lbase_host->member_dof_map(xpt.chart_id()).dof_tuple());

  int lchart_depth = lchart_tuple->refinement_depth;

  index_space_iterator& litr =
    lbase_host->get_cover_id_space_iterator(LOWER, xpt.chart_id());
  scoped_index ldisc_id(lbase_host->member_hub_id_space(false));
  while(!litr.is_done())
  {
    ldisc_id = litr.hub_pod();

    assertion(schema().discretization().contains_member(ldisc_id));

    tuple_type* ltuple =
      reinterpret_cast<tuple_type*>(lbase_host->member_dof_map(ldisc_id).dof_tuple());

    if(ltuple->refinement_depth <= lchart_depth)
    {
      // This is a disc mbr for this chart.

      get_fiber(ldisc_id, ldofs, ldf*sizeof(dof_type), false);

      ldofs += ldf;
      ldofs_ct += ldf;

      assertion(ldofs_ct < 32);
    }
    else
    {
      // This is a discretization member for some more refined chart
      // adjacent to this chart; ignore it.
    }
    litr.next();
  }

  lbase_host->release_cover_id_space_iterator(litr);

  //   cout << endl;

  // Get the evaluator for xpt.chart_id().

  sec_rep_descriptor& lrep = schema().host()->rep();
  eval_family* leval_family = lrep.evaluators();
  section_evaluator* leval = leval_family->member(*base().host(), xpt.chart_id());

  // Evaluate the field at xpt.local_coords()

  leval->value_at_coord(lgathered_dofs,
                        ldofs_ct,
                        xpt.local_coords(),
                        xpt.db(),
                        xresult,
                        ldf);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(unexecutable("for 0 <= i < schema.df(), xresult[i] = i-th component of value"));


  // Exit:

  return;
}

int
fiber_bundle::sec_vd::
dof_packet_ub()
{

  // Preconditions:


  // Body:

  static const int result = 10000;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;

}

void
fiber_bundle::sec_vd::
dof_tuple(dof_type* xbuf, int xbuflen) const
{

  // Preconditions:

  require(xbuflen >= dof_ct());

  // Body:

  // implementation is same as in sec_tuple

  sec_tuple::dof_tuple(reinterpret_cast<void*>(xbuf), xbuflen*  sizeof(dof_type));

  // Postconditions:
  ensure(invariant());
  ensure(unexecutable(xbuf contains copy of dof tuple));

}


fiber_bundle::sec_vd*
fiber_bundle::sec_vd::
deep_copy(bool xauto_access)
{
  sec_vd* result;

  // Preconditions:

  require(xauto_access || host()->in_jim_edit_mode());

  // Body:

  result = clone(true, xauto_access);
  deep_copy(*result, xauto_access);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

void
fiber_bundle::sec_vd::
deep_copy(sec_vd& xother, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || xother.state_is_read_write_accessible());
  require(xauto_access || state_is_read_accessible());

  if(xauto_access)
  {
    xother.get_read_write_access(true);
    get_read_access();
  }

  require(same_schema(&xother));

  // Body:

  sec_vd::fiber_type::volatile_type* lfiber =
    fiber_prototype().lite_prototype().clone();

  const index_space_handle& ldisc_id_space = schema().discretization_id_space();
  index_space_iterator& ldisc_itr = ldisc_id_space.get_iterator();
  scoped_index ldisc_id(ldisc_id_space);
  while(!ldisc_itr.is_done())
  {
    ldisc_id = ldisc_itr.pod();
    
    get_fiber(ldisc_id.pod(), *lfiber);
    xother.put_fiber(ldisc_id, *lfiber, false);

    ldisc_itr.next();
  }
  ldisc_id_space.release_iterator(ldisc_itr);
  delete lfiber;

  if(xauto_access)
  {
    release_access();
    xother.release_access();
  }

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_tuple::scalar_type*
fiber_bundle::sec_vd::
new_comp()
{
  scalar_type* result;

  // Preconditions:

  // Body:

  // Create an unattached handle.

  result = new scalar_type;

  // Postconditions:

  /// @hack this causes trouble in fields.t: ensure(invariant());
  ensure(result != 0);
  ensure(!result->is_attached());
  ensure(unexecutable(result conforms to scalar_type));

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


//=============================================================================
// MULTISECTION FACET
//=============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_vd*
fiber_bundle::sec_vd::
unify(bool xauto_access)
{
  sec_vd* result;

  // Preconditions:

  require(is_multisection(xauto_access));
  require(xauto_access || host()->in_jim_edit_mode());

  // Body:

  result = clone(true, xauto_access);
  unify(*result, xauto_access);

  // Postconditions:

  ensure(!result->is_multisection(xauto_access));

  // Exit:

  return result;
}

void
fiber_bundle::sec_vd::
unify(sec_vd& xresult, bool xauto_access)
{
  // Preconditions:

  require(is_multisection(xauto_access));

  require(xresult.in_same_space(this));
  require(!xresult.is_multisection(xauto_access));
  require(xauto_access || xresult.state_is_read_write_accessible());

  // Body:

  if(xauto_access)
  {
    xresult.get_read_write_access(true); // Implies read access to this.
  }

  sec_vd lbranch;

  int ldf = schema().df();
  sec_vd_dof_type* ldofs = new sec_vd_dof_type[ldf];

  // Iterate over the poset ids of the branches.

  index_space_iterator& lbranch_itr = get_branch_id_space_iterator(false);

  while(!lbranch_itr.is_done())
  {
    lbranch.attach_to_state(_host, lbranch_itr.hub_pod());

    // Iterate over disc seq ids of this branch.

    const index_space_handle& ldisc_id_space = lbranch.schema().discretization_id_space();
    index_space_iterator& ldisc_itr = ldisc_id_space.get_iterator();
    scoped_index ldisc_id(ldisc_id_space);
    while(!ldisc_itr.is_done())
    {
      ldisc_id = ldisc_itr.pod();

      lbranch.get_fiber(ldisc_id.pod(), ldofs,
			ldf*sizeof(sec_vd_dof_type));
      xresult.put_fiber(ldisc_id, ldofs,
			ldf*sizeof(sec_vd_dof_type), false);

      ldisc_itr.next();
    }
    ldisc_id_space.release_iterator(ldisc_itr);
    lbranch_itr.next();
  }
  release_branch_id_space_iterator(lbranch_itr, false);
  lbranch.detach_from_state();

  delete[] ldofs;

  if(xauto_access)
  {
    xresult.release_access();
  }

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NEW DOF ACCESS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::sec_vd::
get_fiber(pod_index_type xdisc_id, vd_lite& xfiber) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  /// @hack: need virtual size_type any_lite::row_dofs_size().
  require(xfiber.d()*sizeof(dof_type) >= schema().fiber_size());

    
  // Body:

  dof_map(false).get_fiber(xdisc_id, xfiber.row_dofs(), xfiber.d()*sizeof(dof_type));

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_vd::
get_fiber(const scoped_index& xdisc_id, vd_lite& xfiber, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(schema(xauto_access).discretization_id_space(xauto_access).contains(xdisc_id));
  /// @hack: need virtual size_type any_lite::row_dofs_size().
  require(xfiber.d()*sizeof(dof_type) >= schema().fiber_size());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  dof_map(false).get_fiber(xdisc_id, xfiber.row_dofs(), xfiber.d()*sizeof(dof_type));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_vd::
put_fiber(pod_index_type xdisc_id, const vd_lite& xfiber)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("dof_map().fiber_in_bounds(xdisc_id, false)"));
  /// @hack: need virtual size_type any_lite::row_dofs_size().
  require(xfiber.d()*sizeof(dof_type) >= schema().fiber_size());

  // Body:

  dof_map(true).put_fiber(xdisc_id, xfiber.row_dofs(), xfiber.d()*sizeof(dof_type));

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_vd::
put_fiber(const scoped_index& xdisc_id, const vd_lite& xfiber, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(schema(xauto_access).discretization_id_space(xauto_access).contains(xdisc_id));
  require(unexecutable("dof_map().fiber_in_bounds(xdisc_id, false)"));
  /// @hack: need virtual size_type any_lite::row_dofs_size().
  require(xfiber.d()*sizeof(dof_type) >= schema().fiber_size());

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  dof_map(true).put_fiber(xdisc_id, xfiber.row_dofs(), xfiber.d()*sizeof(dof_type));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_vd::
force_fiber(pod_index_type xdisc_id, const vd_lite& xfiber)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  /// @hack: need virtual size_type any_lite::row_dofs_size().
  require(xfiber.d()*sizeof(dof_type) >= schema().fiber_size());

  // Body:

  dof_map(true).force_fiber(xdisc_id, xfiber.row_dofs(), xfiber.d()*sizeof(dof_type));

  // Postconditions:


  // Exit:

  return;
}
 
void
fiber_bundle::sec_vd::
force_fiber(const scoped_index& xdisc_id, const vd_lite& xfiber, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(schema(xauto_access).discretization_id_space(xauto_access).contains(xdisc_id));
  /// @hack: need virtual size_type any_lite::row_dofs_size().
  require(xfiber.d()*sizeof(dof_type) >= schema().fiber_size());

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  dof_map(true).force_fiber(xdisc_id, xfiber.row_dofs(), xfiber.d()*sizeof(dof_type));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_VD
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_VD
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::sec_vd::
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
fiber_bundle::sec_vd::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_vd");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_vd*
fiber_bundle::sec_vd::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_vd* result = new sec_vd();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HOST POSET FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_vd::host_type*
fiber_bundle::sec_vd::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::sec_vd::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_VD
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_vd::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_vd*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_vd::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(sec_tuple::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Nothing additional to do.

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

size_t
fiber_bundle::
deep_size(const sec_vd& x0, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}

namespace
{
  using namespace fiber_bundle::vd_algebra;

  class add_functor
  {
  public:
    void operator()(const vd_lite& xl0, const vd_lite& xl1,
                    vd_lite& xlresult) const
    {
      add(xl0, xl1, xlresult);
    }
  };

  class subtract_functor
  {
  public:
    void operator()(const vd_lite& xl0, const vd_lite& xl1,
                    vd_lite& xlresult) const
    {
      subtract(xl0, xl1, xlresult);
    }
  };

  class multiply_functor
  {
  public:
    void operator()(const vd_lite& xl0, const at0_lite& xl1,
                    vd_lite& xlresult) const
    {
      multiply(xl0, xl1, xlresult);
    }
  };

  class divide_functor
  {
  public:
    void operator()(const vd_lite& xl0, const at0_lite& xl1,
                    vd_lite& xlresult) const
    {
      divide(xl0, xl1, xlresult);
    }
  };

  class contract_functor
  {
  public:
    void operator()(const vd_lite& x0, const vd_lite& x1,
                    at0_lite& xresult) const
    {
      xresult = contract(x0, x1);
    }
  };


} //end unnamed namespace

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "e2.h"
#include "sec_vd.impl.h"

void
fiber_bundle::sec_vd_algebra::
add(const sec_vd& x0, const sec_vd& x1, sec_vd& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.d(xauto_access) >= xresult.d(xauto_access));
  require(x1.d(xauto_access) >= xresult.d(xauto_access));
  require(x0.is_vector(xauto_access) == x1.is_vector(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, add_functor(), xauto_access);

  // Set the variance of the result.

  x0.is_vector(xauto_access) ? xresult.put_is_vector(xauto_access) : xresult.put_is_covector(xauto_access);

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));
   ensure(unexecutable("for_all: i, 0, xresult.d(),\
     xresult.component(i)==old_x0.component(i)+old_x1.component(i)"));

  // Exit:

  return;
}

void
fiber_bundle::sec_vd_algebra::
subtract(const sec_vd& x0, const sec_vd& x1, sec_vd& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.d(xauto_access) >= xresult.d(xauto_access));
  require(x1.d(xauto_access) >= xresult.d(xauto_access));
  require(x0.is_vector(xauto_access) == x1.is_vector(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, subtract_functor(), xauto_access);

  // Set the variance of the result.

  x0.is_vector(xauto_access) ? xresult.put_is_vector(xauto_access) : xresult.put_is_covector(xauto_access);

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));
  ensure(unexecutable("for_all: i, 0, xresult.d(),\
     xresult.component(i)==old_x0.component(i)-old_x1.component(i)"));

  // Exit:

  return;
}

void
fiber_bundle::sec_vd_algebra::
multiply(const sec_vd& x0, const sec_at0& x1, sec_vd& xresult,
         bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, multiply_functor(), xauto_access);

  // Set the variance of the result.

  x0.is_vector(xauto_access) ? xresult.put_is_vector(xauto_access) : xresult.put_is_covector(xauto_access);

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));

  // Exit:

  return;
}

void
fiber_bundle::sec_vd_algebra::
multiply(const sec_vd& x0, const vd_value_type& x1, sec_vd& xresult,
        bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, multiply_functor(), xauto_access);

  // Set the variance of the result.

  x0.is_vector(xauto_access) ? xresult.put_is_vector(xauto_access) : xresult.put_is_covector(xauto_access);

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));

  // Exit:

  return;
}

void
fiber_bundle::sec_vd_algebra::
divide(const sec_vd& x0, const sec_at0& x1, sec_vd& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, divide_functor(), xauto_access);

  // Set the variance of the result.

  x0.is_vector(xauto_access) ? xresult.put_is_vector(xauto_access) : xresult.put_is_covector(xauto_access);

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));

  // Exit:

  return;
}

void
fiber_bundle::sec_vd_algebra::
divide(const sec_vd& x0, const vd_value_type& x1, sec_vd& xresult,
       bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, divide_functor(), xauto_access);

  // Set the variance of the result.

  x0.is_vector(xauto_access) ? xresult.put_is_vector(xauto_access) : xresult.put_is_covector(xauto_access);

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));

  // Exit:

  return;
}

//==============================================================================

void
fiber_bundle::sec_vd_algebra::
add_equal(sec_vd& xresult, const sec_vd& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(add(xresult, xother, xresult, xauto_access)));

  // Body:

  add(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(add(xresult, xother, xresult, xauto_access)));

  // Exit:

}

void
fiber_bundle::sec_vd_algebra::
subtract_equal(sec_vd& xresult, const sec_vd& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(subtract(xresult, xother, xresult, xauto_access)));

  // Body:

  subtract(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(subtract(xresult, xother, xresult, xauto_access)));

  // Exit:
}

void
fiber_bundle::sec_vd_algebra::
multiply_equal(sec_vd& xresult, const sec_at0& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Body:

  multiply(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Exit:
}

void
fiber_bundle::sec_vd_algebra::
multiply_equal(sec_vd& xresult, const vd_value_type& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Body:

  multiply(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Exit:
}

void
fiber_bundle::sec_vd_algebra::
divide_equal(sec_vd& xresult, const sec_at0& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Body:

  divide(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Exit:
}

void
fiber_bundle::sec_vd_algebra::
divide_equal(sec_vd& xresult, const vd_value_type& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Body:

  divide(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Exit:
}

void
fiber_bundle::sec_vd_algebra::
contract(const sec_vd& xvector, const sec_vd& xcovector, sec_at0& xresult,
        bool xauto_access)
{
  // Preconditions:

  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xcovector.is_same_type(&xvector));
  require(xvector.is_vector(xauto_access) && xcovector.is_covector(xauto_access));

  // Body:

  binary_op(xvector, xcovector, xresult, contract_functor(), xauto_access);

  // Postconditions:

  // ensure(unexecutable("result == sum(i, xvector[i]*xcovector[i])"));

  // Exit:

  return;
}

//==============================================================================

void 
fiber_bundle::sec_vd_algebra::
max(const sec_vd& x0, vd_lite& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  sec_vd& lx0 = const_cast<sec_vd&>(x0);

  typedef sec_vd::dof_type dof_type;

  // Allocate a buffer for the gathered local dofs of the source.

  block<dof_type> lsrc_dofs;

  // Allocate and initialize the result buffer.

  block<dof_type> lresult_dofs;
  lresult_dofs.reserve(lx0.df());
  lresult_dofs.set_ct(lx0.df());
  lresult_dofs.assign(-numeric_limits<dof_type>::max());

  block<dof_type> leval_dofs(lresult_dofs);

  eval_iterator leval_itr(lx0.schema());

  while(!leval_itr.is_done())
  {
    // Get the evaluator for this eval member.

    section_evaluator& levaluator = leval_itr.evaluator();

    // Gather the dofs from x0.

    leval_itr.gather_dofs(lx0, lsrc_dofs);

    // Compute the maximum for this evaluator.

    levaluator.max(lsrc_dofs, leval_dofs);

    // Accumulate in result buffer.

    for(int i=0; i<leval_dofs.ct(); ++i)
    {
      if(leval_dofs[i] > lresult_dofs[i])
      {
        lresult_dofs[i] = leval_dofs[i];
      }
    }

    // Move to the next evaluation member.

    leval_itr.next();
  }

  xresult.put_components(lresult_dofs.base(), lresult_dofs.ct());

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  //ensure(const_cast<sec_vd&>(x0).invariant());

  // Exit:

  return;
}

fiber_bundle::vd_lite*
fiber_bundle::sec_vd_algebra::
max(const sec_vd& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(max(x0, *result, xauto_access)));

  // Body:

  vd_lite* result = new vd_lite();

  max(x0, *result, xauto_access);

  // Postconditions:

  ensure(postcondition_of(max(x0, *result, xauto_access)));

  // Exit:

  return result;
}

void
fiber_bundle::sec_vd_algebra::
min(const sec_vd& x0, vd_lite& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  sec_vd& lx0 = const_cast<sec_vd&>(x0);

  typedef sec_vd::dof_type dof_type;

  // Allocate a buffer for the gathered local dofs of the source.

  block<dof_type> lsrc_dofs;

  // Allocate and initialize the result buffer.

  block<dof_type> lresult_dofs;
  lresult_dofs.reserve(lx0.df());
  lresult_dofs.set_ct(lx0.df());
  lresult_dofs.assign(numeric_limits<dof_type>::max());

  block<dof_type> leval_dofs(lresult_dofs);

  eval_iterator leval_itr(lx0.schema());

  while(!leval_itr.is_done())
  {
    // Get the evaluator for this eval member.

    section_evaluator& levaluator = leval_itr.evaluator();

    // Gather the dofs from x0.

    leval_itr.gather_dofs(lx0, lsrc_dofs);

    // Compute the maximum for this evaluator.

    levaluator.max(lsrc_dofs, leval_dofs);

    // Accumulate in result buffer.

    for(int i=0; i<leval_dofs.ct(); ++i)
    {
      if(leval_dofs[i] < lresult_dofs[i])
      {
        lresult_dofs[i] = leval_dofs[i];
      }
    }

    // Move to the next evaluation member.

    leval_itr.next();
  }

  xresult.put_components(lresult_dofs.base(), lresult_dofs.ct());

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  //ensure(const_cast<sec_vd&>(x0).invariant());

  // Exit:

  return;
}

fiber_bundle::vd_lite*
fiber_bundle::sec_vd_algebra::
min(const sec_vd& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(min(x0, *result, xauto_access)));

  // Body:

  vd_lite* result = new vd_lite();

  min(x0, *result, xauto_access);

  // Postconditions:

  ensure(postcondition_of(min(x0, *result, xauto_access)));

  // Exit:

  return result;
}


void
fiber_bundle::sec_vd_algebra::
extrema(const sec_vd& x0,
	sec_vd_value_type xmin[],
	size_type xmin_ub,
	sec_vd_value_type xmax[],
	size_type xmax_ub)
{
  // Preconditions:

  require(x0.state_is_read_accessible());
  require(xmin != 0);
  require(xmin_ub >= x0.schema().df());
  require(xmax != 0);
  require(xmax_ub >= x0.schema().df());

  // Body:

  int ldf = x0.schema().df();
  for(int i=0; i<ldf; ++i)
  {
    xmin[i] = numeric_limits<sec_vd_value_type>::max();
    xmax[i] = -numeric_limits<sec_vd_value_type>::max();
  }

  sec_vd_dof_type* ldofs = new sec_vd_dof_type[ldf];

  /// @hack rep doesn't create the evaluator family, so
  /// we have to create an instance here.
  /// @todo remove when rep is fixed to create eval family.

  sec_rep_descriptor& lrep = x0.schema().host()->rep();
  eval_family* leval_family =
    eval_family::new_family(lrep.evaluator_family_name(), *(x0.name_space()));

  if(leval_family->extrema_are_dofs())
  {
    // The extrema occur at the dofs; can just check dofs,
    // don't need to gather dofs and use evaluators.

    index_space_iterator& litr =
      x0.schema().discretization_id_space().get_iterator();
    while(!litr.is_done())
    {
      x0.get_fiber(litr.pod(), ldofs, ldf*sizeof(sec_vd_dof_type));
      for(int i=0; i < ldf; ++i)
      {
	sec_vd_value_type ldof = ldofs[i];

	sec_vd_value_type& lmin = xmin[i];
	lmin = (lmin < ldof) ? lmin : ldof;

	sec_vd_value_type& lmax = xmax[i];
	lmax = (lmax > ldof) ? lmax : ldof;
      }

      litr.next();
    }
    x0.schema().discretization_id_space().release_iterator(litr);
  }
  else
  {
    // Don't support this case yet.

    post_fatal_error_message("!extrema_are_dofs() not supported yet.");
  }

  delete leval_family;
  delete[] ldofs;

  // Postconditions:


  // Exit:

  return;
}

void 
fiber_bundle::sec_vd_algebra::
extrema(const sec_vd& x0, vd_lite& xmin, vd_lite& xmax, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  sec_vd& lx0 = const_cast<sec_vd&>(x0);

  typedef sec_vd::dof_type dof_type;

  // Allocate a buffer for the gathered local dofs of the source.

  block<dof_type> lsrc_dofs;

  // Allocate and initialize the result buffer.

  int ldf = lx0.df();

  block<dof_type> lmin_dofs;
  lmin_dofs.reserve(ldf);
  lmin_dofs.set_ct(ldf);
  lmin_dofs.assign(numeric_limits<dof_type>::max());

  block<dof_type> lmin_eval_dofs(lmin_dofs);

  block<dof_type> lmax_dofs;
  lmax_dofs.reserve(ldf);
  lmax_dofs.set_ct(ldf);
  lmax_dofs.assign(-numeric_limits<dof_type>::max());

  block<dof_type> lmax_eval_dofs(lmax_dofs);

  eval_iterator leval_itr(lx0.schema());

  while(!leval_itr.is_done())
  {
    // Get the evaluator for this eval member.

    section_evaluator& levaluator = leval_itr.evaluator();

    // Gather the dofs from x0.

    leval_itr.gather_dofs(lx0, lsrc_dofs);

    // Compute the min and max for this evaluator.

    levaluator.min(lsrc_dofs, lmin_eval_dofs);
    levaluator.max(lsrc_dofs, lmax_eval_dofs);

    // Accumulate in result buffer.

    for(int i=0; i<ldf; ++i)
    {
      if(lmin_eval_dofs[i] < lmin_dofs[i])
      {
        lmin_dofs[i] = lmin_eval_dofs[i];
      }

      if(lmax_eval_dofs[i] > lmax_dofs[i])
      {
        lmax_dofs[i] = lmax_eval_dofs[i];
      }
    }

    // Move to the next evaluation member.

    leval_itr.next();
  }

  xmin.put_components(lmin_dofs.base(), lmin_dofs.ct());
  xmax.put_components(lmax_dofs.base(), lmax_dofs.ct());

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  //ensure(const_cast<sec_vd&>(x0).invariant());

  // Exit:

  return;

}

//==============================================================================

void 
fiber_bundle::sec_vd_algebra::
assign(sec_vd& x0, const sec_vd& x1, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_write_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    // Since precondition ensures same host,
    // only need to get access to x0.

    x0.get_read_write_access(true);
    x1.get_read_access();
  }

  require(x0.schema(xauto_access).base_space().le(&(x1.schema(xauto_access).base_space())));
  require(x0.schema(xauto_access).same_discretization(x1.schema(xauto_access)));

  sec_vd::fiber_type::volatile_type* lfiber = x0.fiber_prototype().lite_prototype().clone();
  
  const index_space_handle& ldisc_id_space = x0.schema().discretization_id_space();
  index_space_iterator& ldisc_itr = ldisc_id_space.get_iterator();
  scoped_index ldisc_id(ldisc_id_space);
  while(!ldisc_itr.is_done())
  {
    ldisc_id = ldisc_itr.pod();
    
    x1.get_fiber(ldisc_id, *lfiber, false);
    x0.put_fiber(ldisc_id.pod(), *lfiber);

    ldisc_itr.next();
  }
  ldisc_id_space.release_iterator(ldisc_itr);
  delete lfiber;

  if(xauto_access)
  {
    x1.release_access();
    x0.release_access();
  }

  // Postconditions:

  //ensure(x0.invariant());

  // Exit:

  return;

}

void 
fiber_bundle::sec_vd_algebra::
assign(sec_vd& x0, const vd_lite& x1, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_write_access(true);
  }

  index_space_iterator& ldisc_itr =
    x0.schema().discretization_id_space().get_iterator();
  while(!ldisc_itr.is_done())
  {
    x0.put_fiber(ldisc_itr.pod(), x1);

    ldisc_itr.next();
  }
  x0.schema().discretization_id_space().release_iterator(ldisc_itr);

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  //ensure(x0.invariant());

  // Exit:

  return;

}

void 
fiber_bundle::sec_vd_algebra::
assign(sec_vd& x0, const vd_value_type& xvalue, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_write_access(true);
  }

//   section_dof_map& ldof_map = x0.dof_map(true);
//   section_dof_iterator* itr = x0.schema().row_dof_iterator();
//   typedef sec_vd::dof_type dof_type;
//   dof_type lvalue = xvalue;

//   while(! itr->is_done())
//   {
//     ldof_map.put_dof(itr->index(), &lvalue, sizeof(lvalue));
//     itr->next();
//   }

//   delete itr;

  section_dof_map& ldof_map = x0.dof_map(true);
  index_space_iterator& itr = x0.schema().row_dof_id_space().get_iterator();
  typedef sec_vd::dof_type dof_type;
  dof_type lvalue = xvalue;

  while(!itr.is_done())
  {
    ldof_map.put_dof(itr.index(), &lvalue, sizeof(lvalue));
    itr.next();
  }

  x0.schema().row_dof_id_space().release_iterator(itr);
  

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  //ensure(x0.invariant());

  // Exit:

  return;

}
