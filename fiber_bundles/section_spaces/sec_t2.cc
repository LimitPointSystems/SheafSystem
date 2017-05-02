
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
/// Implementation for class sec_t2.

#include "SheafSystem/sec_t2.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/binary_section_space_schema_member.impl.h"
#include "SheafSystem/binary_section_space_schema_poset.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_at0_space.h"
#include "SheafSystem/sec_tuple_space.impl.h"
#include "SheafSystem/section_space_schema_member.impl.h"
#include "SheafSystem/section_space_schema_poset.h"
#include "SheafSystem/tp.h"
#include "SheafSystem/tp_space.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_T2
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS SEC_T2
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_t2::host_type&
fiber_bundle::sec_t2::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xscalar_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_t2::new_host." << endl;

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

  // cout << "Leaving sec_t2::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// T2 FACET OF CLASS SEC_T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_t2::
sec_t2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_t2::
sec_t2(const sec_rep_space* xhost, pod_index_type xhub_id)
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

fiber_bundle::sec_t2::
sec_t2(const sec_rep_space* xhost, const scoped_index& xid)
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

fiber_bundle::sec_t2::
sec_t2(const sec_rep_space* xhost, const std::string& xname)
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


fiber_bundle::sec_t2::
sec_t2(const namespace_poset* xnamespace,
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


fiber_bundle::sec_t2::
sec_t2(const sec_rep_space_member* xother)
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

fiber_bundle::sec_t2::
sec_t2(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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

fiber_bundle::sec_t2::
sec_t2(sec_rep_space* xhost,
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

fiber_bundle::sec_t2&
fiber_bundle::sec_t2::
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

fiber_bundle::sec_t2&
fiber_bundle::sec_t2::
operator=(const sec_t2& xother)
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

fiber_bundle::sec_t2&
fiber_bundle::sec_t2::
operator=(const t2& xfiber)
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

fiber_bundle::sec_t2&
fiber_bundle::sec_t2::
operator=(const t2_lite& xfiber)
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

fiber_bundle::sec_t2::
~sec_t2()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_t2::fiber_type&
fiber_bundle::sec_t2::
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
// TP FACET OF CLASS SEC_T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::sec_t2::
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
fiber_bundle::sec_t2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_t2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_t2*
fiber_bundle::sec_t2::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_t2 *result = new sec_t2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_t2::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const t2*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_t2::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_t2*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_t2::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(sec_tp::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(is_attached() ? p() == 2 : true);

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

namespace
{
  using namespace fiber_bundle::tp_algebra;

  class alt_functor
  {
  public:
    void operator()(const t2_lite& x0, at2_lite& xresult) const
    {
      alt(x0, xresult);
    }

    void operator()(const t2_lite& x0, t2_lite& xresult) const
    {
      alt(x0, xresult);
    }
  };

  class sym_functor
  {
  public:
    void operator()(const t2_lite& x0, st2_lite& xresult) const
    {
      sym(x0, xresult);
    }

    void operator()(const t2_lite& x0, t2_lite& xresult) const
    {
      sym(x0, xresult);
    }
  };

  class contract_functor
  {
  public:
    contract_functor(int xp, int xq) : _p(xp), _q(xq) {}
    void operator()(const t2_lite& x0, at0_lite& xresult) const
    {
      contract(x0, _p, _q, xresult);
    }
  private:
    int _p;
    int _q;
  };

  class tensor_functor
  {
  public:
    void operator()(const at1_lite& xl0, const at1_lite& xl1,
                    t2_lite& xlresult) const
    {
      tensor(xl0, xl1, xlresult);
    }
  };

} //end unnamed namespace

//==============================================================================
//==============================================================================

#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_at1.h"
#include "SheafSystem/sec_at2.h"
#include "SheafSystem/sec_st2.h"
#include "SheafSystem/sec_vd.impl.h"

using namespace fiber_bundle::sec_vd_algebra;

void
fiber_bundle::sec_tp_algebra::
alt(const sec_t2& x0, sec_at2& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // Body:

  unary_op(x0, xresult, alt_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(x0.variance(xauto_access), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == x0.variance(xauto_access));
  ensure(unexecutable("xresult is equal to the antisymmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::sec_tp_algebra::
alt(const sec_t2& x0, sec_t2& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // Body:

  unary_op(x0, xresult, alt_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(x0.variance(xauto_access), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == x0.variance(xauto_access));
  ensure(unexecutable("xresult is equal to the antisymmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::sec_tp_algebra::
sym(const sec_t2& x0, sec_st2& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // Body:

  unary_op(x0, xresult, sym_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(x0.variance(xauto_access), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == x0.variance(xauto_access));
  ensure(unexecutable("xresult is equal to the symmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::sec_tp_algebra::
sym(const sec_t2& x0, sec_t2& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // Body:

  unary_op(x0, xresult, sym_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(x0.variance(xauto_access), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == x0.variance(xauto_access));
  ensure(unexecutable("xresult is equal to the symmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::sec_tp_algebra::
contract(const sec_t2& x0, int xp, int xq, sec_at0& xresult,
         bool xauto_access)
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

  unary_op(x0, xresult, contract_functor(xp, xq), xauto_access);

  // Postconditions:

  ensure(unexecutable("xresult is the contraction of x0 on indices xp and xq"));
  //ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));

  // Exit:

  return;
}

void
fiber_bundle::sec_tp_algebra::
tensor(const sec_at1& x0, const sec_at1& x1, sec_t2& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(xresult.dd(xauto_access) == x0.dd(xauto_access));

 // Body:

  binary_op(x0, x1, xresult, tensor_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(
    tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)),
    xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == \
    tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

