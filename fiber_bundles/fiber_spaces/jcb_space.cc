
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class jcb_space.

#include "jcb_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "jcb.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// JCB_SPACE FACET public member functions
//==============================================================================

///
const string&
fiber_bundle::jcb_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = jcb::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::jcb_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = jcb::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

int
fiber_bundle::jcb_space::
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
fiber_bundle::jcb_space::
d(const namespace_poset& xns, const poset_path& xdomain_space_path, const poset_path& xrange_space_path, bool xauto_access)
{
  // Preconditions:

  require(xns.path_is_auto_read_accessible<domain_space_type>(xdomain_space_path, xauto_access));
  require(xns.path_is_auto_read_accessible<range_space_type>(xrange_space_path, xauto_access));
 
  // Body:

  int ldd = xns.member_poset<domain_space_type>(xdomain_space_path, xauto_access).d();  
  int ldr = xns.member_poset<range_space_type>(xrange_space_path, xauto_access).d();  

  int result = d(ldd, ldr);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::jcb_space::
d(int xdd, int xdr)
{
  return xdd*xdr;
}

fiber_bundle::jcb_space&
fiber_bundle::jcb_space::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path,
	  const poset_path& xdomain_path,
	  const poset_path& xrange_path,
          bool xauto_access)
{
  // cout << endl << "Entering jcb_space::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(xns.path_is_auto_read_accessible<domain_space_type>(xdomain_path, xauto_access));
  require(xns.path_is_auto_read_accessible<range_space_type>(xrange_path, xauto_access));

  require(d(xns, xschema_path, xauto_access) == d(xns, xdomain_path, xrange_path, xauto_access));

  require(xns.member_poset<domain_space_type>(xdomain_path, xauto_access).scalar_space_path(xauto_access) ==
	  xns.member_poset<range_space_type>(xrange_path, xauto_access).scalar_space_path(xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef jcb_space table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Get the dimension (== number of row dofs) defined by the schema.

  int ld = lschema.row_dof_ct();
  int ldd = xns.member_poset<domain_space_type>(xdomain_path, xauto_access).d();
  int ldr = xns.member_poset<range_space_type>(xrange_path, xauto_access).d();

  poset_path lscalar_space_path =
    xns.member_poset<domain_space_type>(xdomain_path, xauto_access).scalar_space_path(xauto_access);
  
  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("factor_ct", ld);
  lmap->put_dof("d", ld);
  lmap->put_dof("scalar_space_path", lscalar_space_path);
  lmap->put_dof("domain_path", xdomain_path);
  lmap->put_dof("dd", ldd);
  lmap->put_dof("range_path", xrange_path);
  lmap->put_dof("dr", ldr);
  
  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  jcb_space& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == d(xns, xschema_path, xauto_access));

  ensure(result.domain_path(true) == xdomain_path);
  ensure(result.dd(true) == xns.member_poset<domain_space_type>(xdomain_path, xauto_access).d());

  ensure(result.range_path(true) == xrange_path);
  ensure(result.dr(true) == xns.member_poset<range_space_type>(xrange_path, xauto_access).d());

  ensure(result.scalar_space_path(true) ==
	 xns.member_poset<domain_space_type>(xdomain_path, xauto_access).scalar_space_path(xauto_access) );
  ensure(result.scalar_space_path(true) ==
	 xns.member_poset<range_space_type>(xrange_path, xauto_access).scalar_space_path(xauto_access) );

  // Exit:

  // cout << "Leaving jcb_space::new_table." << endl;
  return result;
} 


int
fiber_bundle::jcb_space::
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
fiber_bundle::jcb_space::
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
fiber_bundle::jcb_space::
domain_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(sheaf::table_dofs(*this).domain_path);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::jcb_space::
domain_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).domain_path);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

int
fiber_bundle::jcb_space::
dr() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  int result = sheaf::table_dofs(*this).dr;

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::jcb_space::
dr(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  int result = sheaf::table_dofs(*this).dr;
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::jcb_space::
range_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(sheaf::table_dofs(*this).range_path);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::jcb_space::
range_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).range_path);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// ===========================================================
// JCB_SPACE FACET protected member functions
// ===========================================================
 
fiber_bundle::jcb_space::
jcb_space()
  : vd_space(new jcb, new jcb)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(vd_space::vd_space()));
}



fiber_bundle::jcb_space::
jcb_space(const jcb_space& xother)
  : vd_space(new jcb, new jcb)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::jcb_space::
~jcb_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::jcb_space::
jcb_space(jcb* xtop, jcb* xbottom)
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

// ===========================================================
// POSET FACET
// =========================================================== 

bool
fiber_bundle::jcb_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  jcb_space* lproto = new jcb_space;
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
fiber_bundle::jcb_space::
type_id() const
{
  return JCB_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::jcb_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "jcb_space";

  // Postconditions:

  // Exit:

  return result;
}

///
sheaf::pod_index_type
fiber_bundle::jcb_space::
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
	
	// The domain vector space.

      result = name_space()->member_id(domain_path().poset_name(), false);
      break;

    case 2:
	
	// The range vector space.

      result = name_space()->member_id(range_path().poset_name(), false);
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

fiber_bundle::jcb_space&
fiber_bundle::jcb_space::
operator=(const poset_state_handle& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  poset_state_handle::operator=(xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return *this;
}

//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::jcb_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const jcb_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::jcb_space*
fiber_bundle::jcb_space::
clone() const
{
  jcb_space* result;

  // Preconditions:

  // Body:

  result = new jcb_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::jcb_space::
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


