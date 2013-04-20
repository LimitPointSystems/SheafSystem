


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_tuple.

#include "sec_tuple.h"

#include "assert_contract.h"
#include "namespace_poset.h"

#include "sec_tuple_space.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_TUPLE
//==============================================================================

//==============================================================================
// TUPLE FACET OF CLASS SEC_TUPLE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::sec_tuple::
standard_rep_path()
{
  // Preconditions:


  // Body:

  static const poset_path result("sec_rep_descriptors", "vertex_element_dlinear");

  // Postconditions:

  ensure(result.full());
  
  // Exit:

  return result;
}


fiber_bundle::sec_tuple::
sec_tuple()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_tuple::
sec_tuple(const sec_rep_space* xhost, pod_index_type xhub_id)
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

fiber_bundle::sec_tuple::
sec_tuple(const sec_rep_space* xhost, const scoped_index& xid)
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

fiber_bundle::sec_tuple::
sec_tuple(const sec_rep_space* xhost, const string& xname)
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

  // Exit:

}


fiber_bundle::sec_tuple::
sec_tuple(const namespace_poset* xnamespace,
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

fiber_bundle::sec_tuple::
sec_tuple(sec_rep_space_member* xother)
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

fiber_bundle::sec_tuple::
sec_tuple(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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

fiber_bundle::sec_tuple::
sec_tuple(sec_rep_space* xhost,
          abstract_poset_member& xbase_mbr,
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

fiber_bundle::sec_tuple&
fiber_bundle::sec_tuple::
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

fiber_bundle::sec_tuple&
fiber_bundle::sec_tuple::
operator=(const sec_tuple& xother)
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

fiber_bundle::sec_tuple::
~sec_tuple()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

int
fiber_bundle::sec_tuple::
factor_ct() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->factor_ct();

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::sec_tuple::
factor_ct(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  int result = host()->factor_ct();
  
  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_TUPLE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::sec_tuple::
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
fiber_bundle::sec_tuple::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_tuple");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_tuple*
fiber_bundle::sec_tuple::
clone() const
{
  // Preconditions:

  // Body:

  // Create new handle of the current class.

  sec_tuple *result = new sec_tuple();

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

fiber_bundle::sec_tuple::host_type*
fiber_bundle::sec_tuple::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::sec_tuple::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_TUPLE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_tuple::
fiber_is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const tuple*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_tuple::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_tuple*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_tuple::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(sec_rep_space_member::invariant());

  if (invariant_check())
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

void
fiber_bundle::sec_tuple::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());
  // required by intialize_handle_data_members

  // Body:

  sec_rep_space_member::attach_handle_data_members();

  // Postconditions:

  ensure(!is_restricted());

  // Exit:

  return;
}

void
fiber_bundle::sec_tuple::
detach_from_state()
{
  // Preconditions:

  // Body:

  sec_rep_space_member::detach_from_state();

  // Postconditions:

  ensure(!is_attached());
  ensure(invariant());

  // Exit:
}

fiber_bundle::sec_tuple::scalar_type*
fiber_bundle::sec_tuple::
comp(int i) const
{
  // Preconditions:

  require(0 <= i && i < df());

  // Body:

  // Retrieve the requested component from storage.

  scalar_type* result = 0;

  not_implemented();

  // Postconditions:

  ensure(invariant());
  ensure(result != 0);

  // Exit:

  return result;
}

void
fiber_bundle::sec_tuple::
set_comp(int i, scalar_type* component)
{
  // Preconditions:

  require(0 <= i && i < df());
  require(component != 0);

  // Body:

  // Set the ith component in storage to component.

  not_implemented();

  // Postconditions:

  ensure(comp(i) == component);
  ensure(invariant());

}

void
fiber_bundle::sec_tuple::
restrict_to(const abstract_poset_member* xschema)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xschema != 0);
  require(schema().is_ancestor_of(xschema));
  require(xschema != 0);
  require(xschema->le(&(host()->schema())));

  // Body:

  // Restrict this...

  sec_rep_space_member::restrict_to(xschema);

  // Postconditions:

  ensure(schema().is_same_state(xschema));
  ensure(unexecutable("base().is_same_state(old base())"));
  ensure(invariant());

  // Exit:
}

void
fiber_bundle::sec_tuple::
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
fiber_bundle::sec_tuple::
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
fiber_bundle::sec_tuple::
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
fiber_bundle::sec_tuple::
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


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

size_t
fiber_bundle::
deep_size(const sec_tuple& x0, bool xinclude_shallow)
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


