


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_at0.

//#define DIAGNOSTIC_OUTPUT

#include "sec_at0.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_rep_descriptor_poset.h"
#include "sec_tuple_space.impl.h"
#include "section_space_schema_member.impl.h"
#include "section_space_schema_poset.h"
#include "at0.h"
#include "at0_space.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_AT0
//==============================================================================
// ===========================================================
// HOST FACTORY FACET OF CLASS SEC_AT0
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_at0::host_type&
fiber_bundle::sec_at0::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_at0::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
  require(host_type::fiber_space_conforms<fiber_type::host_type>(xns, xschema_path, xauto_access));

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xauto_access);

  // Postconditions:

  //  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.d(true) == result.dd(true));
  ensure(result.d(true) == 1);
  ensure(result.scalar_space_path(true) == xhost_path);
  ensure(result.p(true) == result.schema(true).fiber_space<fiber_type::host_type>().p(xauto_access));
  ensure(result.p(true) == 0);
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.dd(true) == 1);
  ensure(result.vector_space_path(true) == xhost_path);

  // Exit:

  // cout << "Leaving sec_at0::new_host." << endl;
  return result;
}

fiber_bundle::sec_at0::host_type&
fiber_bundle::sec_at0::
new_host(namespace_type& xns, 
         const poset_path& xbase_space_path, 
         const poset_path& xrep_path, 
         const string& xsection_suffix, 
         const string& xfiber_suffix, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_at0::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xbase_space_path.full());
  require(xns.contains_path<base_space_poset>(xbase_space_path));

  require(xrep_path.full());
  require(xns.contains_path<sec_rep_descriptor_poset>(xrep_path));  

  require(xsection_suffix.empty() || poset_path::is_valid_name(xsection_suffix));

  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));

  // !!!! start here - need templated standard_host_path sec_tuple, section_space_schema_member, and maybe in tuple.

  require(!xns.contains_path(standard_host_path<fiber_type>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix), xauto_access));

  require(xns.path_is_auto_read_available<schema_type::host_type>(schema_type::standard_host_path(xbase_space_path, fiber_type::static_class_name(), xrep_path), xauto_access));
  
  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xauto_access);

  // Postconditions:

  //  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.d(true) == result.dd(true));
  ensure(result.d(true) == 1);
  ensure(result.scalar_space_path(true) == xhost_path);
  ensure(result.p(true) == result.schema(true).fiber_space<fiber_type::host_type>().p(xauto_access));
  ensure(result.p(true) == 0);
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.dd(true) == 1);
  ensure(result.vector_space_path(true) == xhost_path);

  // Exit:

  // cout << "Leaving sec_at0::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 
//==============================================================================
// AT0 FACET OF CLASS SEC_AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_at0::
sec_at0()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_at0::
sec_at0(const sec_rep_space* xhost, pod_index_type xhub_id)
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

fiber_bundle::sec_at0::
sec_at0(const sec_rep_space* xhost, const scoped_index& xid)
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

fiber_bundle::sec_at0::
sec_at0(const sec_rep_space* xhost, const string& xname)
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

fiber_bundle::sec_at0::
sec_at0(const namespace_poset* xnamespace,
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

fiber_bundle::sec_at0::
sec_at0(const sec_at0* xother)
{
  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);
  restrict_to_same(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));
  ensure(is_same_restriction(xother));

  // Exit:
}

fiber_bundle::sec_at0::
sec_at0(const sec_rep_space_member* xother, abstract_poset_member* xfiber_schema_jim)
{
  // Preconditions:

  require(xother != 0);
  require(xother->state_is_read_accessible());
  require(xfiber_schema_jim != 0);
  require(xfiber_schema_jim->le(&(xother->fiber_schema())));
  require(xfiber_schema_jim->is_jim());

  // Body:

  attach_to_state(xother);
  restrict_to(&(xother->base()), xfiber_schema_jim);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));
  ensure(fiber_schema().is_same_state(xfiber_schema_jim));

}

fiber_bundle::sec_at0::
sec_at0(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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


fiber_bundle::sec_at0::
sec_at0(sec_rep_space* xhost,
        const abstract_poset_member& xbase_mbr,
        int xbase_version, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(\
    new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access)));

  // Body:

  new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_at0::
sec_at0(sec_rep_space* xhost, const subposet& xbase_parts, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jim_state(xhost, xbase_parts, xauto_access)));

  // Body:

  new_jrm_state(xhost, xbase_parts, xauto_access);

  // Postconditions:

  require(postcondition_of(new_jim_state(xhost, xbase_parts, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_at0&
fiber_bundle::sec_at0::
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

fiber_bundle::sec_at0&
fiber_bundle::sec_at0::
operator=(const sec_at0& xother)
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

fiber_bundle::sec_at0&
fiber_bundle::sec_at0::
operator=(const at0& xfiber)
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

fiber_bundle::sec_at0&
fiber_bundle::sec_at0::
operator=(const at0_lite& xfiber)
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

fiber_bundle::sec_at0::
~sec_at0()
{
  // Preconditions:

  // Body:

  // Postconditions:
}

const fiber_bundle::sec_at0::fiber_type&
fiber_bundle::sec_at0::
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
// ATP FACET OF CLASS SEC_AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS SEC_AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::sec_at0::
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
fiber_bundle::sec_at0::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_at0");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_at0*
fiber_bundle::sec_at0::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_at0 *result = new sec_at0();

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

fiber_bundle::sec_at0::host_type*
fiber_bundle::sec_at0::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::sec_at0::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_at0::
fiber_is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const at0*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;
}

bool
fiber_bundle::sec_at0::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_at0*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;
}

bool
fiber_bundle::sec_at0::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  /// @todo reimplement sec_at0::u(), v(), p(), etc

  //   // Must satisfy base class invariant

  //   invariance(sec_atp::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();


    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  // Exit:

  return result;
}

void
fiber_bundle::sec_at0::
restrict_to(const abstract_poset_member* xschema)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xschema != 0);
  require(schema().is_ancestor_of(xschema));
  require(xschema->leqv(host()->schema().index()));

  // Body:

  // Restrict this...

  sec_rep_space_member::restrict_to(xschema);

  // Postconditions:

  ensure(schema().is_same_state(xschema));
  ensure(unexecutable(base().is_same_state(old base())));
  ensure(invariant());

  // Exit:
}

void
fiber_bundle::sec_at0::
restrict_to(pod_index_type xbase_id, pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());

  /// @todo implement preconditions equivalent to the following:
  ///   require(xbase != 0);
  ///   require(xbase->le(&(host()->base())));
  ///   require(xfiber_schema != 0);
  ///   require(xfiber_schema->le(&(host()->fiber_schema())));

  // Body:

  // Restrict this...

  sec_rep_space_member::restrict_to(xbase_id, xfiber_schema_id);

  // Postconditions:

  //   ensure(base().is_same_state(xbase));
  //   ensure(fiber_schema().is_same_state(xfiber_schema));
  //   ensure(invariant());

  // Exit:
}

void
fiber_bundle::sec_at0::
restrict_to(const abstract_poset_member* xbase, const abstract_poset_member* xfiber_schema)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xbase != 0);
  require(xbase->le(&(host()->base())));
  require(xfiber_schema != 0);
  require(xfiber_schema->le(&(host()->fiber_schema())));

  // Body:

  // Restrict this...

  sec_rep_space_member::restrict_to(xbase, xfiber_schema);

  // Postconditions:

  ensure(base().is_same_state(xbase));
  ensure(fiber_schema().is_same_state(xfiber_schema));
  ensure(invariant());

  // Exit:
}

void
fiber_bundle::sec_at0::
restrict_to_same(const abstract_poset_member* xother)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xother != 0);
  require(xother->state_is_read_accessible());
  require(is_ancestor_of(xother));
  require(has_same_host(xother));

  // Body:

  // Restrict this...

  sec_rep_space_member::restrict_to_same(xother);

  // Postconditions:

  ensure(is_same_restriction(xother));
  ensure(invariant());

  // Exit:
}

void
fiber_bundle::sec_at0::
unrestrict()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Restrict this...

  sec_rep_space_member::unrestrict();

  // Postconditions:

  ensure(!is_restricted());
  ensure(invariant());

  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================


// Insert sec_at0& v into ostream &os
ostream&
fiber_bundle::operator<<(ostream& xos, const sec_at0& xv)
{
  sec_at0::dof_type ldof;
  int i = 0;

  xos << "sec_at0 " << xv. name() << " dofs:" << endl;

  index_space_iterator& itr = xv.schema().row_dof_id_space().get_iterator();

  while(!itr.is_done())
  {
    xos << setw(10) << xv.dof_map().dof(itr.index()).to_string();
    if (i%5 == 4)
      xos << endl;
    itr.next();
    i++;
  }

  xv.schema().row_dof_id_space().release_iterator(itr);

  return xos;
}

//==============================================================================
// "MATH" FUNCTIONS
//==============================================================================

namespace
{
  using namespace fiber_bundle;

  class acos_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::acos(xl0);
    }
  };

  class asin_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::asin(xl0);
    }
  };

  class atan_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::atan(xl0);
    }
  };

  class atan2_functor
  {
  public:
    void operator()(const at0_lite& xl0, const at0_lite& xl1,
                    at0_lite& xlresult) const
    {
      xlresult = std::atan2(xl0, xl1);
    }
  };

  class ceil_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::ceil(xl0);
    }
  };

  class cos_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::cos(xl0);
    }
  };

  class cosh_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::cosh(xl0);
    }
  };

  class exp_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::exp(xl0);
    }
  };

  class fabs_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::fabs(xl0);
    }
  };

  class floor_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::floor(xl0);
    }
  };

  class fmod_functor
  {
  public:
    void operator()(const at0_lite& xl0, const at0_lite& xl1,
                    at0_lite& xlresult) const
    {
      xlresult = std::fmod(xl0, xl1);
    }
  };

  class frexp_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlsignificand,
                    at0_lite& xlexp) const
    {
      // Need to pass a pointer to an integer to frexp.

      int lexp;
      xlsignificand = std::frexp(xl0, &lexp);
      xlexp = lexp;
    }
  };

  class ldexp_functor
  {
  public:
    void operator()(const at0_lite& xl0, const vd_value_type& xlexp,
                    at0_lite& xlresult) const
    {
      const int lexp = static_cast<const int>(xlexp);
      xlresult = std::ldexp(xl0, lexp);
    }
  };

  class log_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::log(xl0);
    }
  };

  class log10_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::log10(xl0);
    }
  };

  class modf_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlintpart,
                    at0_lite& xlfractpart) const
    {
      xlfractpart = std::modf(xl0, &xlintpart[0]);
    }
  };

  class pow_functor
  {
  public:
    void operator()(const at0_lite& xl0, const vd_value_type& xlexp,
                    at0_lite& xlresult) const
    {
      xlresult = std::pow(xl0, xlexp);
    }
  };

  class sin_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::sin(xl0);
    }
  };

  class sinh_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::sinh(xl0);
    }
  };

  class sqrt_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::sqrt(xl0);
    }
  };

  class tan_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::tan(xl0);
    }
  };

  class tanh_functor
  {
  public:
    void operator()(const at0_lite& xl0, at0_lite& xlresult) const
    {
      xlresult = std::tanh(xl0);
    }
  };

} //end unnamed namespace

//==============================================================================

#include "sec_vd.impl.h"

using namespace fiber_bundle::sec_vd_algebra;

void
fiber_bundle::sec_at0_algebra::
acos(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  //$$TODO: WEM Fix
  //require(*max(x0, xauto_access) <= 1);
  //require(*min(x0, xauto_access) >= -1);

  ///@issue The above 2 preconditions result in memory leaks.
  ///       How do we want to deal with them?

  // Body:

  unary_op(x0, xresult, acos_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
asin(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  //$$TODO: WEM Fix
  //require(*max(x0, xauto_access) <= 1);
  //require(*min(x0, xauto_access) >= -1);

  ///@issue The above 2 preconditions result in memory leaks.
  ///       How do we want to deal with them?

  // Body:

  unary_op(x0, xresult, asin_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
atan(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, atan_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
atan2(const sec_at0& x0, const sec_at0& x1, sec_at0& xresult,
      bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, atan2_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
ceil(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, ceil_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
cos(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, cos_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
cosh(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, cosh_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
exp(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, exp_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}


void
fiber_bundle::sec_at0_algebra::
fabs(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, fabs_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
floor(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, floor_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
fmod(const sec_at0& x0, const sec_at0& x1, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, fmod_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
frexp(const sec_at0& x0, sec_at0& xsignificand, sec_at0& xexp,
	  bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xsignificand.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xsignificand, xexp, frexp_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
ldexp(const sec_at0& x0, int xexp, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  binary_op(x0, static_cast<vd_value_type>(xexp), xresult, ldexp_functor(),
            xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
log(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, log_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
log10(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, log10_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
modf(const sec_at0& x0, sec_at0& xintpart, sec_at0& xfractpart,
	 bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xintpart.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xintpart, xfractpart, modf_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
pow(const sec_at0& x0, const vd_value_type& xexponent, sec_at0& xresult,
	bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  binary_op(x0, xexponent, xresult, pow_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
sin(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, sin_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
sinh(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, sinh_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
sqrt(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, sqrt_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
tan(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, tan_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::sec_at0_algebra::
tanh(const sec_at0& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, tanh_functor(), xauto_access);

  // Postconditions:

  // Exit:

  return;
}


