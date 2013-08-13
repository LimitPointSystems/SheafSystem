

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class vd.

#include "vd.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "wsv_block.h"

#include "at0.h"
#include "atp.h"
#include "stp.h"
#include "tolerance_comparison.h"
#include "tp.h"
#include "vd_space.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS VD_LITE
//==============================================================================

//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS VD_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::vd_lite::
vd_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::vd_lite::
vd_lite(const vd_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;
 
  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::vd_lite&
fiber_bundle::vd_lite::
operator=(const vd_lite& xother)
{
  // Preconditions:

  // Body:

  int ld = d();
  for(int i=0; i<ld; ++i)
  {
    put_component(i, xother.component(i));
  }

  // Postconditions:

  ensure((*this) == xother);
  
  // Exit:

  return *this;
}

bool
fiber_bundle::vd_lite::
operator==(const vd_lite& xother) const
{
  // cout << endl << "Entering vd_lite::operator==." << endl;

  // Preconditions:

  require(is_same_type(xother));
  
  // Body:

  bool result = true;

  int ld = d();
  for(int i=0; i<ld; ++i)
  {
    result = (*this)[i] == xother[i];
    if(!result)break;
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving vd_lite::operator==." << endl;
  return result;
}

fiber_bundle::vd_lite::
~vd_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::vd_lite::
vd_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::vd_lite&
fiber_bundle::vd_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  int ld = d();
  for(int i=0; i<ld; ++i)
  {
    put_component(i, xrow_dofs[i]);
  }
  
  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(), component(i) == xrow_dofs[i]);

  // Exit:

  return *this;

}


int
fiber_bundle::vd_lite::
d() const
{
  // Preconditions:

  // Body:

  int result = 0; // Just to silence compiler.

  // Postconditions:

  ensure(invariant());
  ensure(result == 0);

  // Exit:

  return result;
}

fiber_bundle::vd_lite::value_type
fiber_bundle::vd_lite::
component(int xindex) const
{
  // Preconditions:

  require((0 <= xindex) &&(xindex <  d()));

  // Body:

  value_type result = sheaf::row_dofs(*this)[xindex];
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::vd_lite::
put_component(int xindex, value_type xcomp)
{
  // Preconditions:

  require((0 <= xindex) && (xindex <=  d()));

  // Body:

  sheaf::row_dofs(*this)[xindex] = xcomp;

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(xindex), xcomp));

  // Exit:

  return;
}

void
fiber_bundle::vd_lite::
components(dof_type xcomps[], int xcomps_dimension) const
{
  // Preconditions:

  require(xcomps != 0);
  require(xcomps_dimension >= d());

  // Body:

  int ld = d();
  for(int i=0; i<ld; ++i)
  {
    xcomps[i] = component(i);
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

void
fiber_bundle::vd_lite::
put_components(const dof_type xcomps[], int xcomps_dimension)
{
  // Preconditions:

  require(xcomps != 0);
  require(xcomps_dimension >= d());

  // Body:

  int ld = d();
  for(int i=0; i<ld; ++i)
  {
    put_component(i, xcomps[i]);
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::vd_lite&
fiber_bundle::vd_lite::
operator=(const value_type& xvalue)
{
  // Preconditions:

  // Body:

  int ld = d();
  for(int i=0; i<ld; ++i)
  {
    put_component(i, xvalue);
  }
  
  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(), component(i) == xvalue);

  // Exit:

  return *this;

}

bool
fiber_bundle::vd_lite::
operator==(const value_type& xvalue) const
{
  // Preconditions:

  // Body:

  bool result = true;
  int ld = d();
  for(int i=0; i<ld; ++i)
  {
    result = result && (component(i) == xvalue);
    if(!result)
    {
      break;
    }
  }
  
  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(), !result || component(i) == xvalue);

  // Exit:

  return result;

}

fiber_bundle::vd_lite::value_type&
fiber_bundle::vd_lite::
operator[] (int xindex)
{
  // Preconditions:

  require(xindex >= 0 && xindex < d());

  // Body:

  value_type& result = sheaf::row_dofs(*this)[xindex];

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::vd_lite::value_type&
fiber_bundle::vd_lite::
operator[] (int xindex) const
{
  // Preconditions:

  require(xindex >= 0 && xindex < d());

  // Body:

  const value_type& result = sheaf::row_dofs(*this)[xindex];

  // Postconditions:

  // Exit:

  return result;
}


const fiber_bundle::tp_lite&
fiber_bundle::vd_lite::
static_tp_prototype(int xp)
{
  // Preconditions:

  require(0 <= xp);

  // Body:

  static const tp_lite ltp_lite;
  return ltp_lite;

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::tp_lite& 
fiber_bundle::vd_lite::
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
fiber_bundle::vd_lite::
static_atp_prototype(int xp)
{
  // Preconditions:
 
  require(0 <= xp);

  // Body:

  static const atp_lite latp_lite;
  return latp_lite;

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::atp_lite&
fiber_bundle::vd_lite::
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
fiber_bundle::vd_lite::
static_stp_prototype(int xp)
{
  // Preconditions:

   require(0 <= xp);

  // Body:

  static const stp_lite lstp_lite;
  return lstp_lite;

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::stp_lite&
fiber_bundle::vd_lite::
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
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS VD_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::vd_lite::
factor_ct() const
{
  // Preconditions:

  // Body:

  int result = d();

  // Postconditions:

  ensure(invariant());
  ensure(result == d());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::vd_lite::
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
fiber_bundle::vd_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("vd_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::vd_lite*
fiber_bundle::vd_lite::
clone() const
{
  vd_lite* result = 0;

  // Preconditions:

  // Body:

  result = new vd_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

fiber_bundle::vd_lite::table_dofs_type
fiber_bundle::vd_lite::
table_dofs() const
{
  // Preconditions:

  // Body:

  int lfactor_ct = factor_ct();
  int ld         = d();

  /// @issue Where does this string get deleteed?

  char* lscalar_space_path = new char[1];
  lscalar_space_path[0] = 0;

  table_dofs_type result;
  result.factor_ct = lfactor_ct;
  result.d = ld;
  result.scalar_space_path = lscalar_space_path;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS VD_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::vd_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const vd_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::vd_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(tuple_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS VD
//==============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::vd::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "vd_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

void
fiber_bundle::vd::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "d INT true";
  lmember_names += " scalar_space_path C_STRING true";
  

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              tuple::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

void
fiber_bundle::vd::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xscalar_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering vd::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xscalar_space_path.full());
  require(xns.path_is_auto_read_accessible(xscalar_space_path, xauto_access));
  require(xns.contains_poset<scalar_type::host_type>(xscalar_space_path, xauto_access));

  // Body:

  host_type::new_table(xns, xhost_path, xschema_path, xscalar_space_path, xauto_access);

  // Postconditions:

  ensure(xns.contains_path(xhost_path, xauto_access));
  ensure(xns.member_poset(xhost_path, xauto_access).state_is_not_read_accessible());
  ensure(xns.member_poset(xhost_path, xauto_access).schema(true).path(true) == xschema_path);

  ensure(xns.member_poset<vd_space>(xhost_path, xauto_access).factor_ct(true) == xns.member_poset<vd_space>(xhost_path, xauto_access).d(true));
  ensure(xns.member_poset<vd_space>(xhost_path, xauto_access).d(true) == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));
  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).scalar_space_path(true) == xscalar_space_path );

  // Exit:

  // cout << "Leaving vd::new_host." << endl;
  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS VD
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::vd::
vd()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::vd&
fiber_bundle::vd::
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

fiber_bundle::vd&
fiber_bundle::vd::
operator=(const vd& xother)
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

fiber_bundle::vd::
~vd()
{
  // Preconditions:

  // Body:

  // Postconditions:

   // Exit:
}

fiber_bundle::vd::
vd(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::vd::
vd(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::vd::
vd(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::vd::
vd(const poset_state_handle* xhost, const string& xname)
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

  // Exit:
}

fiber_bundle::vd::
vd(const abstract_poset_member* xother)
{

  // Preconditions:

  require(xother != 0);
  require(xother->is_attached() ? xother->state_is_read_accessible() : true);
  require(is_ancestor_of(xother));

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));

}

int
fiber_bundle::vd::
d() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = sheaf::table_dofs(*this).d;

  // Postconditions:

  /// @hack can't call invariant because it's not const
  // ensure(invariant());
  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::vd::
d(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  int result = d();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  /// @hack can't call invariant because it's not const
  // ensure(invariant());
  ensure(result >= 0);

  // Exit:

  return result;
}

poset_path
fiber_bundle::vd::
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

poset_path
fiber_bundle::vd::
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

vd::value_type
fiber_bundle::vd::
component(int xindex) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xindex) &&(xindex < d()));

  // Body:

  value_type result = sheaf::row_dofs(*this)[xindex];
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::vd::value_type
fiber_bundle::vd::
component(int xindex, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xindex) &&(xindex < d(xauto_access)));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  value_type result = component(xindex);

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::vd::
put_component(int xindex, value_type xcomp)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xindex) && (xindex <= d()));

  // Body:

  sheaf::row_dofs(*this)[xindex] = xcomp;

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(xindex), xcomp));

  // Exit:

  return;
}

void
fiber_bundle::vd::
put_component(int xindex, value_type xcomp, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xindex) && (xindex <= d(xauto_access)));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }
  
  put_component(xindex, xcomp);

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(xindex), xcomp));

  // Exit:

  return;
}

void
fiber_bundle::vd::
components(dof_type xcomps[], int xcomps_dimension) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xcomps != 0);
  require(xcomps_dimension >= d());

  // Body:

  int ld = d();
  for(int i=0; i<ld; ++i)
  {
    xcomps[i] = component(i);
  }

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return;
}

void
fiber_bundle::vd::
put_components(const dof_type xcomps[], int xcomps_dimension)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(xcomps != 0);
  require(xcomps_dimension >= d());

  // Body:

  int ld = d();
  for(int i=0; i<ld; ++i)
  {
    put_component(i, xcomps[i]);
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::vd::dof_type&
fiber_bundle::vd::
operator[] (int xindex)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(xindex>=0 && xindex<d());

  // Body:

  dof_type& result = sheaf::row_dofs(*this)[xindex];

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::vd::dof_type&
fiber_bundle::vd::
operator[] (int xindex) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xindex>=0 && xindex<d());

  // Body:

  const dof_type& result = sheaf::row_dofs(*this)[xindex];

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::vd::volatile_type&
fiber_bundle::vd::
lite_prototype() const
{
  // Preconditions:

  // Body:

  static const volatile_type result;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::vd::volatile_type*
fiber_bundle::vd::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

///
bool
fiber_bundle::vd::
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

///
void
fiber_bundle::vd::
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

///
bool
fiber_bundle::vd::
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

///
void
fiber_bundle::vd::
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS VD
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::vd::
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
vd::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("vd");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

fiber_bundle::vd::host_type*
fiber_bundle::vd::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::vd::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS VD
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::vd::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const vd*>(xother) != 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::vd*
fiber_bundle::vd::
clone() const
{
  // Preconditions:

  vd* result = 0;

  // Body:

  result = new vd();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::vd::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(tuple::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Invariants for this class:

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

ostream& 
fiber_bundle::
operator<<(ostream& xos, const vd_lite& x0)
{
  size_type lprec = xos.precision(18);
  
  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    xos << scientific << setw(27) << x0.component(i);
  }

  xos.precision(lprec);
  
  return xos;
}

ostream& 
fiber_bundle::
operator<<(ostream& xos, const vd& x0)
{
  int ld = x0.d();
  for(int i=0; i<ld; ++i)
  {
    xos << " " << x0.component(i);
  }

  return xos;
}



// ===========================================================
// VECTOR ALGEBRA
// ===========================================================

// ===========================================================
// VECTOR ALGEBRA: ADDITION
// ===========================================================

void
fiber_bundle::vd_algebra::
add(const vd& x0, const vd& x1, vd& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.d(xauto_access) >= xresult.d(xauto_access));
  require(x1.d(xauto_access) >= xresult.d(xauto_access));
  require(x0.is_vector(xauto_access) == x1.is_vector(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Access via virtual component required since 
  // some descendants may not store components.

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, x0.component(i) + x1.component(i));
  }

  // Set the variance of the result.

  x0.is_vector(false) ? xresult.put_is_vector(false) : xresult.put_is_covector(false);
  
  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));
  ensure(unexecutable("for_all: i, 0, xresult.d(),\
     xresult.component(i)==old_x0.component(i)+old_x1.component(i)"));

  // Exit:

  return;
}

void
fiber_bundle::vd_algebra::
add(const vd_lite& x0, const vd_lite& x1, vd_lite& xresult)
{
  // Preconditions:

  require(x0.d() >= xresult.d());
  require(x1.d() >= xresult.d());

  // Body:

  // Access via virtual component required since 
  // some descendants may not store components.

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, x0.component(i) + x1.component(i));
  }

  // Postconditions:

  ensure(unexecutable("for_all: i, 0, xresult.d(), \
    xresult.component(i) == old_x0.component(i) + old_x1.component(i)"));

  // Exit:

}

void
fiber_bundle::vd_algebra::
add(const vd_lite& x0, const vd_lite& x1, vd_value_type xt, vd_lite& xresult)
{
  // Preconditions:

  require(x0.d() >= xresult.d());
  require(x1.d() >= xresult.d());

  // Body:

  vd_value_type lone_minus_t = 1.0 - xt;

  // Access via virtual component required since 
  // some descendants may not store components.

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, x0.component(i)*lone_minus_t + x1.component(i)*xt);
  }

  // Postconditions:

  ensure(unexecutable("for_all: i, 0, xresult.d(), \
    xresult.component(i) == old_x0.component(i)*(1.0 - xt) + old_x1.component(i)*xt"));

  // Exit:

}

void
fiber_bundle::vd_algebra::
add_equal(vd& xresult, const vd& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(add(xresult, xother, xresult, xauto_access)));

  // Body:

  add(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(add(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

// ===========================================================
// VECTOR ALGEBRA: SUBTRACTION
// ===========================================================

void
fiber_bundle::vd_algebra::
subtract(const vd& x0, const vd& x1, vd& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.d(xauto_access) >= xresult.d(xauto_access));
  require(x1.d(xauto_access) >= xresult.d(xauto_access));
  require(x0.is_vector(xauto_access) == x1.is_vector(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Access via virtual component required since 
  // some descendants may not store components.

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, x0.component(i) - x1.component(i));
  }

  // Set the variance of the result.

  x0.is_vector(false) ? xresult.put_is_vector(false) : xresult.put_is_covector(false);

  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));
  ensure(unexecutable("for_all: i, 0, xresult.d(), \
    xresult.component(i)==old_x0.component(i)-old_x1.component(i)"));

  // Exit:

  return;
}

void
fiber_bundle::vd_algebra::
subtract(const vd_lite& x0, const vd_lite& x1, vd_lite& xresult)
{
  // Preconditions:

  require(x0.d() >= xresult.d());
  require(x1.d() >= xresult.d());

  // Body:

  // Access via virtual component required since 
  // some descendants may not store components.

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, x0.component(i) - x1.component(i));
  }

  // Postconditions:

  ensure(unexecutable("for_all: i, 0, xresult.d(), \
    xresult.component(i) == old_x0.component(i) - old_x1.component(i)"));

  // Exit:

}

void
fiber_bundle::vd_algebra::
subtract_equal(vd& xresult, const vd& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(subtract(xresult, xother, xresult, xauto_access)));

  // Body:

  subtract(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(subtract(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

// ===========================================================
// VECTOR ALGEBRA: SCALAR MULTIPLICATION
// ===========================================================

void
fiber_bundle::vd_algebra::
multiply(const vd_lite& x0, const vd_value_type& x1, vd_lite& xresult)
{
  // Preconditions:

  require(x0.d() >= xresult.d());

  // Body:

  // Access via virtual component required since 
  // some descendants may not store components.

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, x0.component(i)*x1);
  }

  // Postconditions:

  ensure(unexecutable("for all: i, 0, xresult.d(), \
    xresult.component(i) == old_x0.component(i)*x1"));

  // Exit:

}

void
fiber_bundle::vd_algebra::
multiply(const vd& x0, const vd_value_type& x1, vd& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.d(xauto_access) >= xresult.d(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Access via virtual component required since 
  // some descendants may not store components.

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, x0.component(i)*x1);
  }

  // Set the variance of the result.

  x0.is_vector(false) ? xresult.put_is_vector(false) : xresult.put_is_covector(false);

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));
  ensure(unexecutable("for all: i, 0, xresult.d(), xresult.component(i) == old_x0.component(i)*x1"));

  // Exit:

  return;
}

void
fiber_bundle::vd_algebra::
multiply_equal(vd& xresult, const vd_value_type& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Body:

  multiply(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

// ===========================================================
// VECTOR ALGEBRA: SCALAR DIVISION
// ===========================================================

void
fiber_bundle::vd_algebra::
divide(const vd_lite& x0, const vd_value_type& x1, vd_lite& xresult)
{
  // Preconditions:

  require(x0.d() >= xresult.d());

  // Body:

  // Access via virtual component required since 
  // some descendants may not store components.

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, x0.component(i)/x1);
  }

  // Postconditions:

  ensure(unexecutable("for all: i, 0, xresult.d(), \
    xresult.component(i) == old_x0.component(i)/x1"));

  // Exit:

}

void
fiber_bundle::vd_algebra::
divide(const vd& x0, const vd_value_type& x1, vd& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.d(xauto_access) >= xresult.d(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Access via virtual component required since 
  // some descendants may not store components.

  int ld = xresult.d();
  for(int i=0; i<ld; ++i)
  {
    xresult.put_component(i, x1*x0.component(i));
  }

  // Set the variance of the result.

  x0.is_vector(false) ? xresult.put_is_vector(false) : xresult.put_is_covector(false);

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_vector(xauto_access) == x0.is_vector(xauto_access));
  ensure(unexecutable("for all: i, 0, xresult.d(),\
     xresult.component(i) == old_x0.component(i)/x1"));

  // Exit:

  return;
}

void
fiber_bundle::vd_algebra::
divide_equal(vd& xresult, const vd_value_type& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Body:

  divide(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

// ===========================================================
// VECTOR ALGEBRA: COMPONENT EXTREMA
// ===========================================================

void
fiber_bundle::vd_algebra::
max(const vd& x0, vd_value_type& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  xresult = x0.component(0);

  int ld = x0.d();
  for(int i=1; i<ld; ++i)
  {
    vd_value_type lcomp = x0.component(i);
    if(lcomp >  xresult)
    {
      xresult = lcomp;
    }
  }

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  ensure(unexecutable("xresult == max(x0)"));

  // Exit:

  return;
}

fiber_bundle::vd_value_type
fiber_bundle::vd_algebra::
max(const vd& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(max(x0, xresult, xauto_access)));

  // Body:

  vd_value_type xresult;

  max(x0, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(max(x0, xresult, xauto_access)));

  // Exit:

  return xresult;
}

void
fiber_bundle::vd_algebra::
min(const vd& x0, vd_value_type& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  xresult = x0.component(0);

  int ld = x0.d();
  for(int i=1; i<ld; ++i)
  {
    vd_value_type lcomp = x0.component(i);
    if(lcomp <  xresult)
    {
      xresult = lcomp;
    }
  }

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  ensure(unexecutable("xresult == min(x0)"));

  // Exit:

  return;
}

fiber_bundle::vd_value_type
fiber_bundle::vd_algebra::
min(const vd& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(min(x0, xresult, xauto_access)));

  // Body:

  vd_value_type xresult;

  min(x0, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(min(x0, xresult, xauto_access)));

  // Exit:

  return xresult;
}

void
fiber_bundle::vd_algebra::
max(const vd_lite& x0, vd_value_type& xresult)
{
  // Preconditions:

  // Body:

  xresult = x0.component(0);

  int ld = x0.d();
  for(int i=1; i<ld; ++i)
  {
    vd_value_type lcomp = x0.component(i);
    if(lcomp >  xresult)
    {
      xresult = lcomp;
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult == max(x0)"));

  // Exit:

  return;
}

fiber_bundle:: vd_value_type
fiber_bundle::vd_algebra::
max(const vd_lite& x0)
{
  // Preconditions:

  require(precondition_of(max(x0, xresult)));

  // Body:

  vd_value_type xresult;

  max(x0, xresult);

  // Postconditions:

  ensure(postcondition_of(max(x0, xresult)));

  // Exit:

  return xresult;
}

void
fiber_bundle::vd_algebra::
min(const vd_lite& x0, vd_value_type& xresult)
{
  // Preconditions:

  // Body:

  xresult = x0.component(0);

  int ld = x0.d();
  for(int i=1; i<ld; ++i)
  {
    vd_value_type lcomp = x0.component(i);
    if(lcomp <  xresult)
    {
      xresult = lcomp;
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult == min(x0)"));

  // Exit:

  return;
}

fiber_bundle::vd_value_type
fiber_bundle::vd_algebra::
min(const vd_lite& x0)
{
  // Preconditions:

  require(precondition_of(min(x0, xresult)));

  // Body:

  vd_value_type xresult;

  min(x0, xresult);

  // Postconditions:

  ensure(postcondition_of(min(x0, xresult)));

  // Exit:

  return xresult;
}


// ===========================================================
// VECTOR ALGEBRA: CONTRACTION
// ===========================================================

fiber_bundle::vd_value_type
fiber_bundle::vd_algebra::
contract(const vd_lite& xvector, const vd_lite& xcovector)
{
  // Preconditions:

  require(xcovector.is_same_type(xvector));

  // Body:

  // Access via virtual component required since 
  // some descendants may not store components.

  vd_value_type result = 0;

  int ld = xvector.d();
  for(int i=0; i<ld; ++i)
  {
    vd_value_type lvi = xvector.component(i);
    vd_value_type lci = xcovector.component(i);

    result += lvi*lci;
  }

  // Postconditions:

  // ensure(unexecutable("result == sum(i, xvector[i]*xcovector[i])"));

  // Exit:

  return result;
}

fiber_bundle::vd_value_type
fiber_bundle::vd_algebra::
contract(const vd& xvector, const vd& xcovector, bool xauto_access)
{
  // Preconditions:

  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xcovector.is_same_type(&xvector));
  require(xvector.is_vector(xauto_access) && xcovector.is_covector(xauto_access));

  // Body:

  if(xauto_access)
  {
    xvector.get_read_access();
    xcovector.get_read_access();
  }

  // Access via virtual component required since 
  // some descendants may not store components.

  vd_value_type result = 0;

  int ld = xvector.d();
  for(int i=0; i<ld; ++i)
  {
    result += xvector.component(i)*xcovector.component(i);
  }

  if(xauto_access)
  {
    xvector.release_access();
    xcovector.release_access();
  }

  // Postconditions:

  // ensure(unexecutable("result == sum(i, xvector[i]*xcovector[i])"));

  // Exit:

  return result;
}


// ===========================================================
// VECTOR ALGEBRA: TOLERANCE COMPARISON
// ===========================================================



bool 
fiber_bundle::vd_algebra::
a_eql(const vd_lite& x0, const vd_lite& x1)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  bool result = true;
  int ld = x0.d();
  
  for(int i=0; result && i<ld; ++i)
  {
    result = sheaf::a_eql(x0[i], x1[i], double_tolerance);
  }

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
a_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  bool result = true;
  int ld = x0.d();
  
  for(int i=0; result && i<ld; ++i)
  {
    result = sheaf::a_eql(x0[i], x1[i], xtolerance);
  }

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
a_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  bool result = true;
  int ld = x0.d();
  
  for(int i=0; result && i<ld; ++i)
  {
    result = sheaf::a_eql(x0[i], x1[i], xtolerance[i]);
  }

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
r_eql(const vd_lite& x0, const vd_lite& x1)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  bool result = true;
  int ld = x0.d();
  
  for(int i=0; result && i<ld; ++i)
  {
    result = sheaf::r_eql(x0[i], x1[i], double_tolerance);
  }

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
r_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  bool result = true;
  int ld = x0.d();
  
  for(int i=0; result && i<ld; ++i)
  {
    result = sheaf::r_eql(x0[i], x1[i], xtolerance);
  }

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
r_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  bool result = true;
  int ld = x0.d();
  
  for(int i=0; result && i<ld; ++i)
  {
    result = sheaf::r_eql(x0[i], x1[i], xtolerance[i]);
  }

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
c_eql(const vd_lite& x0, const vd_lite& x1)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  bool result = true;
  int ld = x0.d();
  
  for(int i=0; result && i<ld; ++i)
  {
    result = sheaf::c_eql(x0[i], x1[i], double_tolerance);
  }

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
c_eql(const vd_lite& x0, const vd_lite& x1, double xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  bool result = true;
  int ld = x0.d();
  
  for(int i=0; result && i<ld; ++i)
  {
    result = sheaf::c_eql(x0[i], x1[i], xtolerance);
  }

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
c_eql(const vd_lite& x0, const vd_lite& x1, const vd_lite& xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  bool result = true;
  int ld = x0.d();
  
  for(int i=0; result && i<ld; ++i)
  {
    result = sheaf::c_eql(x0[i], x1[i], xtolerance[i]);
  }

  // Postconditions:

  // Exit:

  return result;
};


// ===========================================================
// MISCELLANEOUS
// ===========================================================

unsigned int
fiber_bundle::vd_algebra::
factorial(unsigned int xi)
{
  // Preconditions:

  // Body:

  unsigned int result = 1;

  for(int i=1; i<=xi; ++i)
  {
    result *= i;
  }

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

unsigned int
fiber_bundle::vd_algebra::
binomial_coefficient(unsigned int xi, unsigned int xj)
{
  // Preconditions:

  require(xi >= xj);

  // Body:

  unsigned int result = factorial(xi)/(factorial(xj)*factorial(xi - xj));

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

