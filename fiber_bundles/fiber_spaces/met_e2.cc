
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
/// Implementation for class met_e2.

#include "met_e2.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "wsv_block.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS MET_E2_ROW_DOFS_TYPE
//==============================================================================


//==============================================================================
// CLASS MET_E2_LITE
//==============================================================================

//==============================================================================
// EUCLIDEAN METRIC 2D (MET_E2) FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met_e2_lite::
met_e2_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e2_lite::
met_e2_lite(const met_e2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e2_lite&
fiber_bundle::met_e2_lite::
operator=(const met_e2_lite& xother)
{

  // Preconditions:


  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;
  
  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(), component(i) == xother[i]); 

  // Exit:

  return *this;
}

fiber_bundle::met_e2_lite::
~met_e2_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::met_e2_lite::
met_e2_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e2_lite&
fiber_bundle::met_e2_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  _row_dofs = xrow_dofs;
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}

fiber_bundle::met_e2_lite::
met_e2_lite(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  *this = xmatrix;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e2_lite& 
fiber_bundle::met_e2_lite::
operator=(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  //_row_dofs = xmatrix;
  _row_dofs = reinterpret_cast<const row_dofs_type&>(xmatrix);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}

fiber_bundle::met_e2_lite::
operator met_e2_lite::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e2_lite::
operator const met_e2_lite::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e2_lite::
operator met_e2_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e2_lite::
operator const met_e2_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e2_lite::
met_e2_lite(const value_type& xx, const value_type& xy, const value_type& yy)
{
  // Preconditions:

  // Body:

  put_components(xx, xy, yy);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx));
  ensure(isunordered_or_equals(component(1), xy));
  ensure(isunordered_or_equals(component(2), yy));

  // Exit:
}

void
fiber_bundle::met_e2_lite::
put_components(const value_type& xx_comp,
               const value_type& xy_comp,
               const value_type& yy_comp)
{
  // Preconditions:

  // Body:

  put_component(0, xx_comp);
  put_component(1, xy_comp);
  put_component(2, yy_comp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), yy_comp));

  // Exit:
}

//==============================================================================
// EUCLIDEAN METRIC (MET_ED) FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// METRIC TENSOR (MET) FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (STP) FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::met_e2_lite::
dd() const
{
  // Preconditions:

  // Body:

  int result = 2;

  // Postconditions:

  ensure(invariant());
  ensure(result == 2);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::met_e2_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e2_lite::static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = e2_lite::static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e2_lite::static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::atp_lite&
fiber_bundle::met_e2_lite::
atp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e2_lite::static_atp_prototype(xp)));
  
  // Body:

  const atp_lite& result = e2_lite::static_atp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e2_lite::static_atp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::stp_lite&
fiber_bundle::met_e2_lite::
stp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e2_lite::static_stp_prototype(xp)));
  
  // Body:

  const stp_lite& result = e2_lite::static_stp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e2_lite::static_stp_prototype(xp)));
  
  // Exit:

  return result;
}

//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::met_e2_lite::
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

const string&
fiber_bundle::met_e2_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met_e2_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met_e2_lite*
fiber_bundle::met_e2_lite::
clone() const
{
  met_e2_lite* result = 0;

  // Preconditions:

  // Body:

  result = new met_e2_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS MET_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::met_e2_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const met_e2_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::met_e2_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(met_ed_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::met_e2_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::met_e2_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS MET_E2
//==============================================================================

//==============================================================================
// MET_E2 FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met_e2::
met_e2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::met_e2::
met_e2(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::met_e2::
met_e2(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::met_e2::
met_e2(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::met_e2::
met_e2(abstract_poset_member* xother)
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

fiber_bundle::met_e2::
met_e2(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::met_e2::
met_e2(poset_state_handle& xhost,
       const row_dofs_type& xrdt,
       bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(&xhost, 0, false, xauto_access)));

  // Body:

  new_jim_state(&xhost, 0, false, xauto_access);

  if(xauto_access)
  {
    xhost.get_read_write_access();
  }

  *this = xrdt;

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(postcondition_of(new_jim_state(&xhost, 0, false, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::met_e2&
fiber_bundle::met_e2::
operator=(const row_dofs_type& xrdt)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  sheaf::row_dofs(*this) = xrdt;
  
  // Postconditions:

  ensure_for_all(i, 0, d(), component(i) == xrdt.components[i]);

  // Exit:

  return *this;

}

///
fiber_bundle::met_e2&
fiber_bundle::met_e2::
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
fiber_bundle::met_e2&
fiber_bundle::met_e2::
operator=(const met_e2& xother)
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

fiber_bundle::met_e2::
~met_e2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

const fiber_bundle::met_e2::volatile_type&
fiber_bundle::met_e2::
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
fiber_bundle::met_e2::volatile_type*
fiber_bundle::met_e2::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::met_e2::
operator met_e2::row_dofs_type& ()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e2::
operator const met_e2::row_dofs_type& () const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// MET_ED FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// MET FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// STP FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::met_e2::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "met_e2_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::met_e2::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "xx DOUBLE false ";
  lmember_names       += "xy DOUBLE false ";
  lmember_names       += "yy DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              met_ed::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::tp*
fiber_bundle::met_e2::
new_tp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e2::new_tp(vector_space(xauto_access), xp)));

  // Body:

  tp* result = e2::new_tp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e2::new_tp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::atp*
fiber_bundle::met_e2::
new_atp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e2::new_atp(vector_space(xauto_access), xp)));

  // Body:

  atp* result = e2::new_atp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e2::new_atp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::stp*
fiber_bundle::met_e2::
new_stp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e2::new_stp(vector_space(xauto_access), xp)));

  // Body:

  stp* result = e2::new_stp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e2::new_stp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::met_e2::
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

const string&
fiber_bundle::met_e2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met_e2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met_e2*
fiber_bundle::met_e2::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  met_e2 *result = new met_e2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS MET_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::met_e2::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const met_e2*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::met_e2::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(met_ed::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    invariance(is_attached() ? (d() == 3) : true);

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

//==============================================================================
// MET FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

///
void
fiber_bundle::met_algebra::
raise(const met_e2_lite& xmetric, const e2_lite& xcovector, e2_lite& xresult)
{
  // Preconditions:

  require(unexecutable("xmetric.is_contravariant())"));
  require(unexecutable("xcovector.is_covariant())"));   //  is_dual;
  require(unexecutable("xresult.is_contravariant())")); // !is_dual

  // Body:

  // Left matrix multiply xcovector with xmetric.

  //
  // This class is a 2x2 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e2_lite::value_type value_type;

  value_type m00 = xmetric.component(0);
  value_type m01 = xmetric.component(1);

  value_type m10 = xmetric.component(1);
  value_type m11 = xmetric.component(2);

  value_type comp0 = xcovector.component(0);
  value_type comp1 = xcovector.component(1);

  value_type result_comp;

  result_comp = m00*comp0 + m01*comp1;
  xresult.put_component(0, result_comp);

  result_comp = m10*comp0 + m11*comp1;
  xresult.put_component(1, result_comp);

  // Postconditions:

  //ensure(unexecutable(""));

  // Exit:

}

///
fiber_bundle::e2_lite*
fiber_bundle::met_algebra::
raise(const met_e2_lite& xmetric, const e2_lite& xcovector)
{
  // Preconditions:

  require(precondition_of(raise(xmetric, xcovector, *result)));

  // Body:

  e2_lite* result = new e2_lite();

  raise(xmetric, xcovector, *result);
  
  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(raise(xmetric, xcovector, *result)));

  // Exit:

  return result;
}

///
void
fiber_bundle::met_algebra::
lower(const met_e2_lite& xmetric, const e2_lite& xvector, e2_lite& xresult)
{
  // Preconditions:

  require(unexecutable("xmetric.is_covariant())"));
  require(unexecutable("xcovector.is_contravariant())")); // !is_dual
  require(unexecutable("xresult.is_covariant())"));       // is_dual

  // Body:

  // Right matrix multiply xvector with xmetric.

  //
  // This class is a 2x2 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e2_lite::value_type value_type;

  value_type m00 = xmetric.component(0);
  value_type m01 = xmetric.component(1);

  value_type m10 = xmetric.component(1);
  value_type m11 = xmetric.component(2);

  value_type comp0 = xvector.component(0);
  value_type comp1 = xvector.component(1);

  value_type result_comp;

  result_comp = m00*comp0 + m10*comp1;
  xresult.put_component(0, result_comp);

  result_comp = m01*comp0 + m11*comp1;
  xresult.put_component(1, result_comp);

  // Postconditions:

  //ensure(unexecutable(""));

  // Exit:

}

///
fiber_bundle::e2_lite*
fiber_bundle::met_algebra::
lower(const met_e2_lite& xmetric, const e2_lite& xvector)
{
  // Preconditions:

  require(precondition_of(lower(xmetric, xvector, *result)));

  // Body:

  e2_lite* result = new e2_lite();

  lower(xmetric, xvector, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(lower(xmetric, xvector, *result)));

  // Exit:

  return result;
}

///
void
fiber_bundle::met_algebra::
raise(const met_e2& xmetric, const e2& xcovector, e2& xresult,
      bool xauto_access)
{
  // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xcovector.d(xauto_access) == xmetric.dd(xauto_access));
  require(xresult.d(xauto_access) == xmetric.dd(xauto_access));
  require(xmetric.is_contravariant(0, xauto_access));
  require(xcovector.is_covariant(0, xauto_access));   //  is_dual;


  // Body:

  if(xauto_access)
  {
    xmetric.get_read_access();
    xcovector.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Left matrix multiply xcovector with xmetric.

  //
  // This class is a 2x2 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e2::value_type value_type;

  value_type m00 = xmetric.component(0);
  value_type m01 = xmetric.component(1);

  value_type m10 = xmetric.component(1);
  value_type m11 = xmetric.component(2);

  value_type comp0 = xcovector.component(0);
  value_type comp1 = xcovector.component(1);

  value_type result_comp;

  result_comp = m00*comp0 + m01*comp1;
  xresult.put_component(0, result_comp);

  result_comp = m10*comp0 + m11*comp1;
  xresult.put_component(1, result_comp);


  // Make sure the result is contravariant/p_vector.

  if(!xresult.is_p_vector(false))
  {
    xresult.put_is_p_vector(false);
  }


  if(xauto_access)
  {
    xmetric.release_access();
    xcovector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Exit:

}

///
void
fiber_bundle::met_algebra::
lower(const met_e2& xmetric, const e2& xvector, e2& xresult, bool xauto_access)
{
  // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xvector.d(xauto_access) == xmetric.dd(xauto_access));
  require(xresult.d(xauto_access) == xmetric.dd(xauto_access));
  require(xmetric.is_covariant(0, xauto_access));
  require(xvector.is_contravariant(0, xauto_access)); // !is_dual;

  // Body:

  if(xauto_access)
  {
    xmetric.get_read_access();
    xvector.get_read_access();
    xresult.get_read_write_access(true);
  }
 
  // Right matrix multiply xvector with xmetric.

  //
  // This class is a 2x2 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e2::value_type value_type;

  value_type m00 = xmetric.component(0);
  value_type m01 = xmetric.component(1);

  value_type m10 = m01;
  value_type m11 = xmetric.component(2);

  value_type comp0 = xvector.component(0);
  value_type comp1 = xvector.component(1);

  value_type result_comp;

  result_comp = m00*comp0 + m10*comp1;
  xresult.put_component(0, result_comp);

  result_comp = m01*comp0 + m11*comp1;
  xresult.put_component(1, result_comp);


  // Make sure the result is covariant/p_form.

  if(!xresult.is_p_form(false))
  {
    xresult.put_is_p_form(false);
  }


  if(xauto_access)
  {
    xmetric.release_access();
    xvector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_covariant(0, xauto_access));     //  is_dual

  // Exit:

}


//==============================================================================
// TEMPLATE SPECIALIZATIONS
//==============================================================================

