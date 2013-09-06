
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class vd_space.

#include "vd_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "tp_space.h"
#include "vd.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// VD_SPACE FACET
//==============================================================================

///
const string&
fiber_bundle::vd_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = vd::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::vd_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = vd::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

fiber_bundle::vd_space&
fiber_bundle::vd_space::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path, 
          const poset_path& xscalar_space_path, 
          bool xauto_access)
{
  // cout << endl << "Entering vd_space::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(xns.path_is_auto_read_accessible<scalar_space_type>(xscalar_space_path, xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef vd_space table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Get the dimension (== number of row dofs) defined by the schema.

  int ld = lschema.row_dof_ct();
  
  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("factor_ct", ld);
  lmap->put_dof("d", ld);
  lmap->put_dof("scalar_space_path", xscalar_space_path);
  
  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  vd_space& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));
  ensure(result.scalar_space_path(true) == xscalar_space_path );

  // Exit:

  // cout << "Leaving vd_space::new_table." << endl;
  return result;
} 

int
fiber_bundle::vd_space::
factor_ct(int xd)
{
  return xd;
}

int
fiber_bundle::vd_space::
d() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  int result = sheaf::table_dofs(*this).d;
  

  // Postconditions:


  // Exit:

  return result;
}

int
fiber_bundle::vd_space::
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


  // Exit:

  return result;
}

int
fiber_bundle::vd_space::
d(const namespace_poset& xns, const poset_path& xvector_space_path, bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));
  require(!xvector_space_path.empty());
  require(xns.contains_poset(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).state_is_auto_read_accessible(xauto_access));  

  // Body:
 
  vd_space& lvector_space = reinterpret_cast<vd_space&>(xns.member_poset(xvector_space_path, xauto_access));
  int result = lvector_space.d(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::vd_space::
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
fiber_bundle::vd_space::
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
fiber_bundle::vd_space::
scalar_space_path(const namespace_poset& xns, const poset_path& xvector_space_path, bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));
  require(!xvector_space_path.empty());
  require(xns.contains_poset(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).state_is_auto_read_accessible(xauto_access));  

  // Body:
 
  vd_space& lvector_space = reinterpret_cast<vd_space&>(xns.member_poset(xvector_space_path, xauto_access));
  poset_path result = lvector_space.scalar_space_path(xauto_access);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

bool
fiber_bundle::vd_space::
contains_variance_subposets(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }  

  int lp = covariant_subposet_ct();
  
  bool result = true;
  for(int i=0; i<lp && result; ++i)
  {
    result = includes_subposet(covariant_subposet_name(i), false);
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::vd_space::
is_vector(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  /// @issue
  /// Want this implementation to work for vd and its various
  /// tensor descendants, except for at0.
  /// For vd itself, the implementation is straight forward,
  /// there's one covariance subposet and a vd is_covector if
  /// it is a member of the covariance subposet. 
  ///
  /// Tensors are a little more complicated.
  /// For a tensor of degree p there are 2**p tensor types,
  /// each of which is a vector space. For a given type with
  /// variance v, the dual space is the type with variance ~v
  /// (bitwise complement). The choice of which types are
  /// vector spaces and which types are covector spaces is
  /// arbitrary. The definition chosen here allows convenient
  /// implementation, but we may want to make this client
  /// programmable someday.
  ///
  /// Arbitrarily choose vector spaces to have index 0 contravariant;
  /// vectors have variance 0xx ; covectors 1xx. is_dual then just
  /// checks for membership in covariance subposet 0. This implementation
  /// works for all vector and tensor types, but not for at0, which
  /// has no covariance subposets. 
  ///
  /// At0 is a special case; scalars can be considered a vector space
  /// over themselves, but even so a scalar is simultaneously a vector and a covector.
  /// This is because covectors transform inversely to vectors, but
  /// by definition the only transform for scalars is the identity transform,
  /// which is its own inverse.

  /// @issue Access by name lookup is not terribly efficient,
  /// but it will have to do until we get id spaces for subposets working
  /// or devise some other mechanism.

  subposet lsp(this, covariant_subposet_name(0));
  bool result = !lsp.contains_member(xmbr_id);
  lsp.detach_from_state();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::vd_space::
is_vector(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  return is_vector(xmbr_id.hub_pod(), xauto_access);
}

void
fiber_bundle::vd_space::
put_is_vector(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_write_access();
  }

  subposet lsp(this, covariant_subposet_name(0));
  lsp.remove_member(xmbr_id);
  lsp.detach_from_state();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_vector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::vd_space::
put_is_vector(const scoped_index& xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  put_is_vector(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_vector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

bool
fiber_bundle::vd_space::
is_covector(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  /// @issue
  /// Want this implementation to work for vd and its various
  /// tensor descendants, except for at0.
  /// For vd itself, the implementation is straight forward,
  /// there's one covariance subposet and a vd is_covector if
  /// it is a member of the covariance subposet. 
  ///
  /// Tensors are a little more complicated.
  /// For a tensor of degree p there are 2**p tensor types,
  /// each of which is a vector space. For a given type with
  /// variance v, the dual space is the type with variance ~v
  /// (bitwise complement). The choice of which types are
  /// vector spaces and which types are covector spaces is
  /// arbitrary. The definition chosen here allows convenient
  /// implementation, but we may want to make this client
  /// programmable someday.
  ///
  /// Arbitrarily choose vector spaces to have index 0 contravariant;
  /// vectors have variance 0xx ; covectors 1xx. is_dual then just
  /// checks for membership in covariance subposet 0. This implementation
  /// works for all vector and tensor types, but not for at0, which
  /// has no covariance subposets. 
  ///
  /// At0 is a special case; scalars can be considered a vector space
  /// over themselves, but even so a scalar is simultaneously a vector and a covector.
  /// This is because covectors transform inversely to vectors, but
  /// by definition the only transform for scalars is the identity transform,
  /// which is its own inverse.

  /// @issue Access by name lookup is not terribly efficient,
  /// but it will have to do until we get id spaces for subposets working
  /// or devise some other mechanism.

  subposet lsp(this, covariant_subposet_name(0));
  bool result = lsp.contains_member(xmbr_id);
  lsp.detach_from_state();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::vd_space::
is_covector(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  return is_covector(xmbr_id.hub_pod(), xauto_access);
}

void
fiber_bundle::vd_space::
put_is_covector(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_write_access();
  }

  subposet lsp(this, covariant_subposet_name(0));
  lsp.insert_member(xmbr_id);
  lsp.detach_from_state();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_covector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::vd_space::
put_is_covector(const scoped_index& xmbr_id, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  put_is_covector(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_covector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

fiber_bundle::vd_space::
vd_space()
  : tuple_space(new vd, new vd)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(tuple_space::tuple_space()));
}



fiber_bundle::vd_space::
vd_space(const vd_space& xother)
  : tuple_space(new vd, new vd)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::vd_space::
~vd_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::vd_space::
vd_space(vd* xtop, vd* xbottom)
  : tuple_space(xtop, xbottom)
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

string
fiber_bundle::vd_space::
covariant_subposet_name(int xi)
{
  // Preconditions:

  // Body:

  string result(poset_path::make_reserved_name("covariant", xi, ""));

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  return result;
}

void
fiber_bundle::vd_space::
create_variance_subposets()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  int lp = covariant_subposet_ct();
  
  for(int i=0; i<lp; ++i)
  {
    string lname(covariant_subposet_name(i));
    if(!includes_subposet(lname, false))
    {
      subposet lcovariant(this);
      lcovariant.put_name(lname, true, false);
      lcovariant.detach_from_state();
    }
  }

  // Postconditions:

  ensure(contains_variance_subposets(false));
  
  // Exit:

  return;
}

sheaf::size_type
fiber_bundle::vd_space::
covariant_subposet_ct() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  size_type result = 1;
  
  // Postconditions:
  
  // Exit:

  return result;
}

// ===========================================================
// POSET FACET
// =========================================================== 

bool
fiber_bundle::vd_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  vd_space* lproto = new vd_space;
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
fiber_bundle::vd_space::
type_id() const
{
  return VD_SPACE_ID;
}





///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::vd_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "vd_space";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::vd_space::
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
	
	// The scalar space over which this vector space is built.

      result = name_space()->member_id(scalar_space_path().poset_name(), false);
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


fiber_bundle::vd_space&
fiber_bundle::vd_space::
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

///
void
fiber_bundle::vd_space::
initialize_standard_subposets(const string& xname)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(poset_path::is_valid_name(xname));

  // Body:

  tuple_space::initialize_standard_subposets(xname);

  create_variance_subposets();
  
  // Postconditions:

  ensure(postcondition_of(tuple_space::initialize_standard_subposets(xname)));
  ensure(contains_variance_subposets(false));
  
  // Exit

  return;
}

//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::vd_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const vd_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::vd_space*
fiber_bundle::vd_space::
clone() const
{
  vd_space* result;

  // Preconditions:

  // Body:

  result = new vd_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::vd_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(tuple_space::invariant());

    invariance(state_is_read_accessible() ? factor_ct() == d() : true);
    
    enable_invariant_check();
  }

  return result;
}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

void
fiber_bundle::print_prereq_paths(ostream &xos, 
				 const vd_space& xspace, 
				 const string& xheading,
				 const string& xindent,
				 bool xauto_access)
{
  // Preconditions:

  require(xspace.state_is_auto_read_accessible(xauto_access));
  require(xspace.name_space()->state_is_auto_read_accessible(xauto_access));
  
  // Body:

  const tp_space*  ltensor_space = dynamic_cast<const tp_space*>(&xspace);
  const at1_space* lvector_space = dynamic_cast<const at1_space*>(&xspace);
  const at0_space* lscalar_space = dynamic_cast<const at0_space*>(&xspace);

  namespace_poset* lns = xspace.name_space();
  
  if(xauto_access)
  {
    xspace.get_read_access();
  }
  
  xos << xindent << xheading << endl;

  string lindent = xindent + "   ";
  
  xos << lindent << "path:        " << xspace.path() << endl;
  xos << lindent << "schema path: " << xspace.schema().path() << endl;
  
  if(lscalar_space == 0)
  {
    // Xspace must be vector or tensor space; print scalar space.

    at0_space& lscalar_space = lns->member_poset<at0_space>(xspace.scalar_space_path(), xauto_access);
    print_prereq_paths(xos, lscalar_space, "scalar space", lindent, xauto_access);  
  
    if((lvector_space == 0) && (ltensor_space != 0))
    {
      // Xspace is tensor; print vector space.

      lvector_space = &lns->member_poset<at1_space>(ltensor_space->vector_space_path(), xauto_access);
      print_prereq_paths(xos, *lvector_space, "vector space", lindent, xauto_access);  
    }
  } 

  if(xauto_access)
  {
    xspace.release_access();
  }

  // Postconditions:

  // Exit:  
  
  return;
}

