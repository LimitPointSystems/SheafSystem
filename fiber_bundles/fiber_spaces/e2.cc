

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class e2.

#include "e2.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1_space.h"
#include "at2_e2.h"
#include "atp_space.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "st2_e2.h"
#include "st4_e2.h"
#include "stp_space.h"
#include "t2_e2.h"
#include "t4_e2.h"
#include "wsv_block.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS E2_LITE
//==============================================================================


//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (E2) FACET OF CLASS E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::e2_lite::
e2_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e2_lite::
e2_lite(const e2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e2_lite&
fiber_bundle::e2_lite::
operator=(const e2_lite& xother)
{

  // Preconditions:

  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;
  
  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(*this == xother));

  // Exit:

  return *this;
}

fiber_bundle::e2_lite::
~e2_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::e2_lite::
e2_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e2_lite&
fiber_bundle::e2_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  _row_dofs = xrow_dofs;
  
  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(row_dofs() == xrow_dofs));
  //ensure_for_all(i, 0, d(), component(i) == xrow_dofs[i]);

  // Exit:

  return *this;

}

fiber_bundle::e2_lite::
e2_lite(const value_type& x0, const value_type& x1)
{
  // Preconditions:

  // Body:

  put_components(x0, x1);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), x0)); 
  ensure(isunordered_or_equals(component(1), x1)); 

  // Exit:
}

void
fiber_bundle::e2_lite::
put_components(const value_type& x_comp,
               const value_type& y_comp)
{
  // Preconditions:

  // Body:

  put_component(0, x_comp);
  put_component(1, y_comp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), x_comp));
  ensure(isunordered_or_equals(component(1), y_comp));

  // Exit:
}

fiber_bundle::e2_lite::
operator e2_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

   ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::e2_lite::
operator const e2_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

   ensure(invariant());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (AT1) FACET OF CLASS E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::e2_lite::
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

bool
fiber_bundle::e2_lite::
operator==(const e2_lite& xother) const
{
  // cout << endl << "Entering e2_lite::operator==." << endl;

  // Preconditions:
  
  // Body:

  bool result = 
    (_row_dofs.components[0] == xother._row_dofs.components[0]) &&
    (_row_dofs.components[1] == xother._row_dofs.components[1]);

  // Postconditions:


  // Exit:

  // cout << "Leaving e2_lite::operator==." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::e2_lite::
static_tp_prototype(int xp)
{
  // Preconditions:

  require(((0 <= xp) && (xp <= 2)) || (xp == 4));

  // Body:

  switch(xp)
  {
    case 0:
      {
	static const at0_lite lat0_lite;
	return lat0_lite;
      }
    case 1:
      {
	static const e2_lite le2_lite;
	return le2_lite;
      }
    case 2:
      {
	static const t2_e2_lite lt2_e2_lite;
	return lt2_e2_lite;
      }
      
      //     case 3:
      //       static const t3_e2_lite lt3_e2_lite;
      //       return lt3_e2_lite;

    case 4:
      {
	static const t4_e2_lite lt4_e2_lite;
	return lt4_e2_lite;
      }
    default:
      {
	// Can't get here because of the precondition.
	static const tp_lite ltp_lite;
	return ltp_lite;
      }
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::tp_lite&
fiber_bundle::e2_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::atp_lite&
fiber_bundle::e2_lite::
static_atp_prototype(int xp)
{
  // Preconditions:

  require((0 <= xp) && (xp <= 2));

  // Body:

  switch(xp)
  {
    case 0:
      {
	static const at0_lite lat0_lite;
	return lat0_lite;
      }
    case 1:
      {
	static const e2_lite le2_lite;
	return le2_lite;
      }
    case 2:
      {
	static const at2_e2_lite lat2_e2_lite;
	return lat2_e2_lite;
      }
    default:
      {
	// Can't get here because of the precondition.
	static const atp_lite latp_lite;
	return latp_lite;
      }
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::atp_lite&
fiber_bundle::e2_lite::
atp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(static_atp_prototype(xp)));
  
  // Body:

  const atp_lite& result = static_atp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_atp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::stp_lite&
fiber_bundle::e2_lite::
static_stp_prototype(int xp)
{
  // Preconditions:

  require((2 == xp) || (xp == 4));

  // Body:

  switch(xp)
  {
    case 2:
      {
	static const st2_e2_lite lst2_e2_lite;
	return lst2_e2_lite;
      }
      //     case 3:
      //       static const st3_e2_lite lst3_e2_lite;
      //       return lst3_e2_lite;
    case 4:
      {
	static const st4_e2_lite lst4_e2_lite;
	return lst4_e2_lite;
      }
    default:
      {
	// Can't get here because of the precondition.
	static const stp_lite lstp_lite;
	return lstp_lite;
      }
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::stp_lite&
fiber_bundle::e2_lite::
stp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(static_stp_prototype(xp)));
  
  // Body:

  const stp_lite& result = static_stp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_stp_prototype(xp)));
  
  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::e2_lite::
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
fiber_bundle::e2_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("e2_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::e2_lite*
fiber_bundle::e2_lite::
clone() const
{
  e2_lite* result = 0;

  // Preconditions:

  // Body:

  result = new e2_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::e2_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const e2_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::e2_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(ed_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::e2_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::e2_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS E2
//==============================================================================

//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (E2) FACET OF CLASS E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::e2::
e2()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e2::
e2(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::e2::
e2(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::e2::
e2(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::e2::
e2(abstract_poset_member* xother)
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

fiber_bundle::e2::
e2(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::e2::
e2(poset_state_handle& xhost,
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

fiber_bundle::e2&
fiber_bundle::e2::
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

fiber_bundle::e2&
fiber_bundle::e2::
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

fiber_bundle::e2&
fiber_bundle::e2::
operator=(const e2& xother)
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

fiber_bundle::e2::
~e2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

const fiber_bundle::e2::volatile_type&
fiber_bundle::e2::
lite_prototype() const
{
  // Preconditions:

  // Body:

  static const volatile_type result;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::e2::volatile_type*
fiber_bundle::e2::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (AT1) FACET OF CLASS E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::e2::
put_components(dof_type xcomp, dof_type ycomp)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, xcomp);
  put_component(1, ycomp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xcomp));
  ensure(isunordered_or_equals(component(1), ycomp));

  // Exit:

  return;
}

fiber_bundle::e2::
operator e2::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::e2::
operator const e2::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::e2::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "e2_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::e2::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "x DOUBLE false y DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              ed::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::tp*
fiber_bundle::e2::
new_tp(tp_space& xvector_space, int xp)
{
  // Preconditions:

  require(xvector_space.state_is_read_accessible());
  require(((0 <= xp) && (xp <= 2)) || (xp == 4));

  // Body:

  namespace_poset* lns = xvector_space.name_space();
  const string& lvector_space_name = xvector_space.name();

  switch(xp)
  {
    case 0:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "at0");
	at0::host_type& lhost = lns->member_poset<at0::host_type>(lname, false);
        at0* result = new at0(&lhost);
        return result;
      }

    case 1:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "e2");
	e2::host_type& lhost = lns->member_poset<e2::host_type>(lname, false);
        e2* result = new e2(&lhost);
        return result;
      }

    case 2:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "t2_e2");
	t2_e2::host_type& lhost = lns->member_poset<t2_e2::host_type>(lname, false);
        t2_e2* result = new t2_e2(&lhost);
        return result;
      }

//     case 3: // Don't have t3_e2.

    case 4:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "t4_e2");
	t4_e2::host_type& lhost = lns->member_poset<t4_e2::host_type>(lname, false);
        t4_e2* result = new t4_e2(&lhost);
        return result;
      }

    default:
      // Can't get here because of the precondition.
      return 0;
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:

}

fiber_bundle::atp*
fiber_bundle::e2::
new_atp(tp_space& xvector_space, int xp)
{
  // Preconditions:

  require(xvector_space.state_is_read_accessible());
  require((0 <= xp) && (xp <= 2));

  // Body:

  namespace_poset* lns = xvector_space.name_space();
  const string& lvector_space_name = xvector_space.name();

  switch(xp)
  {
    case 0:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "at0");
	at0::host_type& lhost = lns->member_poset<at0::host_type>(lname, false);
        at0* result = new at0(&lhost);
        return result;
      }

    case 1:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "e2");
	e2::host_type& lhost = lns->member_poset<e2::host_type>(lname, false);
        e2* result = new e2(&lhost);
        return result;
      }

    case 2:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "at2_e2");
	at2_e2::host_type& lhost = lns->member_poset<at2_e2::host_type>(lname, false);
        at2_e2* result = new at2_e2(&lhost);
        return result;
      }

    default:
      // Can't get here because of the precondition.
      return 0;
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

fiber_bundle::stp*
fiber_bundle::e2::
new_stp(tp_space& xvector_space, int xp)
{
  // Preconditions:

  require(xvector_space.state_is_read_accessible());
  require((2 == xp) || (xp == 4));

  // Body:

  namespace_poset* lns = xvector_space.name_space();
  const string& lvector_space_name = xvector_space.name();

  switch(xp)
  {
    case 2:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "st2_e2");
	st2_e2::host_type& lhost = lns->member_poset<st2_e2::host_type>(lname, false);
        st2_e2* result = new st2_e2(&lhost);
        return result;
      }

//     case 3: // Don't have st3_e2.
 
    case 4:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "st4_e2");
	st4_e2::host_type& lhost = lns->member_poset<st4_e2::host_type>(lname, false);
        st4_e2* result = new st4_e2(&lhost);
        return result;
      }

    default:
      // Can't get here because of the precondition.
      return 0;
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:

}

fiber_bundle::tp*
fiber_bundle::e2::
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
fiber_bundle::e2::
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
fiber_bundle::e2::
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
// ABSTRACT POSET MEMBER FACET OF CLASS E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::e2::
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
fiber_bundle::e2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("e2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::e2*
fiber_bundle::e2::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class..

  e2* result = new e2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::e2::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const e2*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::e2::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(ed::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance((is_attached() ? d() == 2 : true));

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

fiber_bundle::vd_value_type
fiber_bundle::e2_algebra::
perp_dot(const e2_lite& x0, const e2_lite& x1)
{
  // cout << endl << "Entering e2::perp_dot." << endl;

  // Preconditions:


  // Body:

  // Result = dot(x0-perp, x1), where x0-perp = (-x0[1], x0[0]).
  // = -x0[1]*x1[0] + x0[0]*x1[1]

  const e2_lite::dof_type* lx0 = reinterpret_cast<const e2_lite::row_dofs_type*>(x0.row_dofs())->components;
  const e2_lite::dof_type* lx1 = reinterpret_cast<const e2_lite::row_dofs_type*>(x1.row_dofs())->components;

  vd_value_type result = -lx0[1]*lx1[0] + lx0[0]*lx1[1];

  // Postconditions:


  // Exit:

  // cout << "Leaving e2::perp_dot." << endl;
  return result;
}

