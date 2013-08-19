

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class met_e3.

#include "met_e3.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "at1_space.h"
#include "stp_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "wsv_block.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS MET_E3_ROW_DOFS_TYPE
//==============================================================================


//==============================================================================
// CLASS MET_E3_LITE
//==============================================================================

//==============================================================================
// EUCLIDEAN METRIC 3D (MET_E3) FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met_e3_lite::
met_e3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e3_lite::
met_e3_lite(const met_e3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e3_lite&
fiber_bundle::met_e3_lite::
operator=(const met_e3_lite& xother)
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

fiber_bundle::met_e3_lite::
~met_e3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::met_e3_lite::
met_e3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e3_lite&
fiber_bundle::met_e3_lite::
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

fiber_bundle::met_e3_lite::
met_e3_lite(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  *this = xmatrix;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e3_lite& 
fiber_bundle::met_e3_lite::
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

fiber_bundle::met_e3_lite::
operator met_e3_lite::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e3_lite::
operator const met_e3_lite::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e3_lite::
operator met_e3_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e3_lite::
operator const met_e3_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e3_lite::
met_e3_lite(const value_type& xx_comp,
            const value_type& xy_comp,
            const value_type& xz_comp,
            const value_type& yy_comp,
            const value_type& yz_comp,
            const value_type& zz_comp)
{
  // Preconditions:

  // Body:

  put_components(xx_comp, xy_comp, xz_comp, yy_comp, yz_comp, zz_comp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), xz_comp));
  ensure(isunordered_or_equals(component(3), yy_comp));
  ensure(isunordered_or_equals(component(4), yz_comp));
  ensure(isunordered_or_equals(component(5), zz_comp));

  // Exit:
}

void
fiber_bundle::met_e3_lite::
put_components(const value_type& xx_comp,
               const value_type& xy_comp,
               const value_type& xz_comp,
               const value_type& yy_comp,
               const value_type& yz_comp,
               const value_type& zz_comp)

{
  // Preconditions:

  // Body:

  put_component(0, xx_comp);
  put_component(1, xy_comp);
  put_component(2, xz_comp);
  put_component(3, yy_comp);
  put_component(4, yz_comp);
  put_component(5, zz_comp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), xz_comp));
  ensure(isunordered_or_equals(component(3), yy_comp));
  ensure(isunordered_or_equals(component(4), yz_comp));
  ensure(isunordered_or_equals(component(5), zz_comp));

  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EUCLIDEAN METRIC (MET_ED) FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// METRIC TENSOR (MET) FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (STP) FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::met_e3_lite::
dd() const
{
  // Preconditions:

  // Body:

  int result = 3;

  // Postconditions:

  ensure(invariant());
  ensure(result == 3);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::met_e3_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e3_lite::static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = e3_lite::static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e3_lite::static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::atp_lite&
fiber_bundle::met_e3_lite::
atp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e3_lite::static_atp_prototype(xp)));
  
  // Body:

  const atp_lite& result = e3_lite::static_atp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e3_lite::static_atp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::stp_lite&
fiber_bundle::met_e3_lite::
stp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e3_lite::static_stp_prototype(xp)));
  
  // Body:

  const stp_lite& result = e3_lite::static_stp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e3_lite::static_stp_prototype(xp)));
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::met_e3_lite::
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
fiber_bundle::met_e3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met_e3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met_e3_lite*
fiber_bundle::met_e3_lite::
clone() const
{
  met_e3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new met_e3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS MET_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::met_e3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const met_e3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::met_e3_lite::
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
fiber_bundle::met_e3_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::met_e3_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS MET_E3
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS MET_E3
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::met_e3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "met_e3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::met_e3::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "xx DOUBLE false ";
  lmember_names       += "xy DOUBLE false ";
  lmember_names       += "yy DOUBLE false ";
  lmember_names       += "xz DOUBLE false ";
  lmember_names       += "yz DOUBLE false ";
  lmember_names       += "zz DOUBLE false";

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

fiber_bundle::met_e3::host_type&
fiber_bundle::met_e3::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering met_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 6);
  
  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).schema(xauto_access).conforms_to(vector_space_type::standard_schema_path()));
  require(xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d(xauto_access) == 3);

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 2, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == 6);
  ensure(result.d(true) == 6);
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path());
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 3);
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving met_e3::new_host." << endl;
  return result;
}

fiber_bundle::met_e3::host_type&
fiber_bundle::met_e3::
standard_host(namespace_type& xns, const string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering met_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<met_e3>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(standard_host_path<vector_space_type>(xsuffix), xauto_access));

  // Body:

  // Create the vector space if necessary.

  poset_path lvector_space_path = vector_space_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<met_e3>(xsuffix));

  host_type* result_ptr;
  if(xns.contains_path(lpath, xauto_access))
  {
    result_ptr = &xns.member_poset<host_type>(lpath, xauto_access);
  }
  else
  {
    result_ptr = &new_host(xns, lpath, standard_schema_path(), lvector_space_path, xauto_access);
  }

  host_type& result = *result_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path<met_e3>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.factor_ct(true) == 6);
  ensure(result.d(true) == 6);
  ensure(result.scalar_space_path(true) == standard_host_path<vector_space_type::scalar_type>(xsuffix) );
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 3);
  ensure(result.vector_space_path(true) == standard_host_path<vector_space_type>(xsuffix) );

  // Exit:

  // cout << "Leaving met_e3::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// MET_E3 FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met_e3::
met_e3()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::met_e3::
met_e3(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::met_e3::
met_e3(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::met_e3::
met_e3(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::met_e3::
met_e3(abstract_poset_member* xother)
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

fiber_bundle::met_e3::
met_e3(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::met_e3::
met_e3(poset_state_handle& xhost,
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

fiber_bundle::met_e3&
fiber_bundle::met_e3::
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
fiber_bundle::met_e3&
fiber_bundle::met_e3::
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
fiber_bundle::met_e3&
fiber_bundle::met_e3::
operator=(const met_e3& xother)
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

fiber_bundle::met_e3::
~met_e3()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::met_e3::volatile_type&
fiber_bundle::met_e3::
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
fiber_bundle::met_e3::volatile_type*
fiber_bundle::met_e3::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e3::
operator met_e3::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e3::
operator const met_e3::row_dofs_type& () const
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
// MET_ED FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// MET FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// STP FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tp*
fiber_bundle::met_e3::
new_tp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_tp(vector_space(xauto_access), xp)));

  // Body:

  tp* result = e3::new_tp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_tp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::atp*
fiber_bundle::met_e3::
new_atp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_atp(vector_space(xauto_access), xp)));

  // Body:

  atp* result = e3::new_atp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_atp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::stp*
fiber_bundle::met_e3::
new_stp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_stp(vector_space(xauto_access), xp)));

  // Body:

  stp* result = e3::new_stp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_stp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::met_e3::
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
fiber_bundle::met_e3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met_e3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met_e3*
fiber_bundle::met_e3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class..

  met_e3* result = new met_e3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS MET_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::met_e3::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of xother.

  bool result = dynamic_cast<const met_e3*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::met_e3::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(met_ed::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Invariants for this class:

    invariance(is_attached() ? (d() == 6) : true);

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

void
fiber_bundle::met_algebra::
raise(const met_e3_lite& xmetric, const e3_lite& xcovector, e3_lite& xresult)
{
  // Preconditions:

  require(unexecutable("xmetric.is_contravariant())"));
  require(unexecutable("xcovector.is_covariant())"));   //  is_dual;

  // Body:
 
  // Left matrix multiply xcovector with current.

  //
  // This class is a 3x3 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e3_lite::value_type value_type;

  value_type m00 = xmetric.component(0);
  value_type m01 = xmetric.component(1);
  value_type m02 = xmetric.component(2);

  value_type m10 = xmetric.component(1);
  value_type m11 = xmetric.component(3);
  value_type m12 = xmetric.component(4);

  value_type m20 = xmetric.component(2);
  value_type m21 = xmetric.component(4);
  value_type m22 = xmetric.component(5);

  value_type comp0 = xcovector.component(0);
  value_type comp1 = xcovector.component(1);
  value_type comp2 = xcovector.component(2);

  value_type result_comp;

  result_comp = m00*comp0 + m01*comp1 + m02*comp2;
  xresult.put_component(0, result_comp);

  result_comp = m10*comp0 + m11*comp1 + m12*comp2;
  xresult.put_component(1, result_comp);

  result_comp = m20*comp0 + m21*comp1 + m22*comp2;
  xresult.put_component(2, result_comp);

  // Postconditions:

  ensure(unexecutable("xresult.is_contravariant())")); // !is_dual

  // Exit:

}

fiber_bundle::e3_lite*
fiber_bundle::met_algebra::
raise(const met_e3_lite& xmetric, const e3_lite& xcovector)
{
  // Preconditions:

  require(precondition_of(raise(xmetric, xcovector, *result)));

  // Body:

  e3_lite* result = new e3_lite();

  raise(xmetric, xcovector, *result);
  
  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(raise(xmetric, xcovector, *result)));

  // Exit:

  return result;
}

void
fiber_bundle::met_algebra::
lower(const met_e3_lite& xmetric, const e3_lite& xvector, e3_lite& xresult)
{
  // Preconditions:

  require(unexecutable("xmetric.is_covariant())"));
  require(unexecutable("xvector.is_contravariant())"));   //  !is_dual;

  // Body:
 
  // Right matrix multiply xvector with current.

  //
  // This class is a 3x3 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e3_lite::value_type value_type;

  value_type m00 = xmetric.component(0);
  value_type m01 = xmetric.component(1);
  value_type m02 = xmetric.component(2);

  value_type m10 = xmetric.component(1);
  value_type m11 = xmetric.component(3);
  value_type m12 = xmetric.component(4);

  value_type m20 = xmetric.component(2);
  value_type m21 = xmetric.component(4);
  value_type m22 = xmetric.component(5);

  value_type comp0 = xvector.component(0);
  value_type comp1 = xvector.component(1);
  value_type comp2 = xvector.component(2);

  value_type result_comp;

  result_comp = m00*comp0 + m10*comp1 + m20*comp2;
  xresult.put_component(0, result_comp);

  result_comp = m01*comp0 + m11*comp1 + m21*comp2;
  xresult.put_component(1, result_comp);

  result_comp = m02*comp0 + m12*comp1 + m22*comp2;
  xresult.put_component(2, result_comp);

  // Postconditions:

  ensure(unexecutable("xresult.is_covariant())")); // is_dual

  // Exit:

}

fiber_bundle::e3_lite*
fiber_bundle::met_algebra::
lower(const met_e3_lite& xmetric, const e3_lite& xvector)
{
  // Preconditions:

  require(precondition_of(lower(xmetric, xvector, *result)));

  // Body:

  e3_lite* result = new e3_lite();

  lower(xmetric, xvector, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(lower(xmetric, xvector, *result)));

  // Exit:

  return result;
}

void
fiber_bundle::met_algebra::
raise(const met_e3& xmetric, const e3& xcovector, e3& xresult, bool xauto_access)
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
  // This class is a 3x3 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e3::value_type value_type;

  value_type m00 = xmetric.component(0);
  value_type m01 = xmetric.component(1);
  value_type m02 = xmetric.component(2);

  value_type m10 = m01;
  value_type m11 = xmetric.component(3);
  value_type m12 = xmetric.component(4);

  value_type m20 = m02;
  value_type m21 = m12;
  value_type m22 = xmetric.component(5);

  value_type comp0 = xcovector.component(0);
  value_type comp1 = xcovector.component(1);
  value_type comp2 = xcovector.component(2);

  value_type result_comp;

  result_comp = m00*comp0 + m01*comp1 + m02*comp2;
  xresult.put_component(0, result_comp);

  result_comp = m10*comp0 + m11*comp1 + m12*comp2;
  xresult.put_component(1, result_comp);

  result_comp = m20*comp0 + m21*comp1 + m22*comp2;
  xresult.put_component(2, result_comp);


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

void
fiber_bundle::met_algebra::
lower(const met_e3& xmetric, const e3& xvector, e3& xresult, bool xauto_access)
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
  // This class is a 3x3 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e3::value_type value_type;

  value_type m00 = xmetric.component(0);
  value_type m01 = xmetric.component(1);
  value_type m02 = xmetric.component(2);

  value_type m10 = m01;
  value_type m11 = xmetric.component(3);
  value_type m12 = xmetric.component(4);

  value_type m20 = m02;
  value_type m21 = m12;
  value_type m22 = xmetric.component(5);

  value_type comp0 = xvector.component(0);
  value_type comp1 = xvector.component(1);
  value_type comp2 = xvector.component(2);

  value_type result_comp;

  result_comp = m00*comp0 + m10*comp1 + m20*comp2;
  xresult.put_component(0, result_comp);

  result_comp = m01*comp0 + m11*comp1 + m21*comp2;
  xresult.put_component(1, result_comp);

  result_comp = m02*comp0 + m12*comp1 + m22*comp2;
  xresult.put_component(2, result_comp);


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

