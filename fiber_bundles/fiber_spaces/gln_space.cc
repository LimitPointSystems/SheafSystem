
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class gln_space.

#include "gln_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "gln.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "vd_space.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// GLN_SPACE FACET
//==============================================================================

///
const string&
fiber_bundle::gln_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = gln::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::gln_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = gln::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

int
fiber_bundle::gln_space::
d(const namespace_poset& xns,const poset_path& xvector_space_path, bool xauto_access)
{
  // Preconditions:

  require(xns.path_is_auto_read_accessible<vector_space_type>(xvector_space_path, xauto_access));
 
  // Body:

  int ln = xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).d();  

  int result = d(ln);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::gln_space::
d(int xn)
{
  return 2*xn*xn;
}

fiber_bundle::gln_space&
fiber_bundle::gln_space::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path, 
          const poset_path& xvector_space_path, 
          bool xauto_access)
{
  // cout << endl << "Entering gln_space::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(xns.path_is_auto_read_accessible<vector_space_type>(xvector_space_path, xauto_access));

  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == d(xns, xvector_space_path, xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef gln_space table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Get the dimension of the vector space.

  int ln = xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).d();

  // Get the scalar space path from the domain vector space.

  poset_path lscalar_space_path = xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access);
  
  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("scalar_space_path", lscalar_space_path);
  lmap->put_dof("n", ln);
  lmap->put_dof("vector_space_path", xvector_space_path);
  
  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  gln_space& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access) );
  ensure(result.n(true) == xns.member_poset<vector_space_type>(xvector_space_path, xauto_access).d());
  ensure(result.vector_space_path(true) == xvector_space_path );

  ensure(result.d(true) == d(xns, xvector_space_path, xauto_access));

  // Exit:

  // cout << "Leaving gln_space::new_table." << endl;
  return result;
}

int
fiber_bundle::gln_space::
n() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = sheaf::table_dofs(*this).n;

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::gln_space::
n(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  int result = n();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln_space::
scalar_space_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(sheaf::table_dofs(*this).scalar_space_path);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln_space::
scalar_space_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).scalar_space_path);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln_space::
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
fiber_bundle::gln_space::
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

int
fiber_bundle::gln_space::
d() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = d(n());

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::gln_space::
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

  ensure(result >= 0);

  // Exit:

  return result;
}

fiber_bundle::gln_space::
gln_space()
  : poset(new gln, new gln)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(poset::poset()));
}



fiber_bundle::gln_space::
gln_space(const gln_space& xother)
  : poset(new gln, new gln)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::gln_space::
~gln_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::gln_space::
gln_space(gln* xtop, gln* xbottom)
  : poset(xtop, xbottom)
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
fiber_bundle::gln_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  gln_space* lproto = new gln_space;
  poset_type ltype    = lproto->type_id();

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
fiber_bundle::gln_space::
type_id() const
{
  return GLN_SPACE_ID;
}





///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::gln_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "gln_space";

  // Postconditions:

  // Exit:

  return result;
}


///
sheaf::pod_index_type
fiber_bundle::gln_space::
prereq_id(int xi) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(name_space()->state_is_read_accessible());

  // Body:

  // The result must be scoped if it is valid because
  // namespace_poset_member::put_poset_prereq_id must be
  // able to map it to the namespace member id space.
  // The vector_space_index is just a pod, so we have to
  // pick some id space for it and make sure we consistently
  // use it. The obvious choice is the internal id space, 
  // so initialize result to internal scope.
 
  pod_index_type result;

  switch(xi)
  {
    case 0:

      // The first prerequisite is always the schema.

      result = schema().host()->index().pod();
      break;

    case 1:
	
	// The underlying vector space.

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

fiber_bundle::gln_space&
fiber_bundle::gln_space::
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
fiber_bundle::gln_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const gln_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::gln_space*
fiber_bundle::gln_space::
clone() const
{
  gln_space* result;

  // Preconditions:

  // Body:

  result = new gln_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::gln_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(poset::invariant());

    /// @todo finish gln_space::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}



