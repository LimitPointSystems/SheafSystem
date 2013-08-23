
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
/// Implementation for class sec_vd_space.

#include "sec_vd_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_vd.h"
#include "section_space_schema_poset.h"
#include "vd_space.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// SEC_VD_SPACE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::sec_vd_space::
make_arg_list(const poset_path& xscalar_space_path)
{
  // Preconditions:


  // Body:

  int lfactor_ct = 0; // Don't know actual value yet.
  
  sheaf::arg_list result = sec_tuple_space::make_arg_list(lfactor_ct);

  result << "d" << 0;
  result << "scalar_space_path" << xscalar_space_path;
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_vd_space::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(result.contains_arg("factor_ct"));
  ensure(result.contains_arg("d"));
  ensure(result.contains_arg("scalar_space_path"));
  ensure(result.value("scalar_space_path") == xscalar_space_path);
  
  // Exit:

  return result;
}

//==============================================================================
// TABLE DOFS
//==============================================================================

int
fiber_bundle::sec_vd_space::
factor_ct(int xd)
{
  return xd;
}

int
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
d(const namespace_poset& xns, const poset_path& xvector_space_path, bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));
  require(!xvector_space_path.empty());
  require(xns.contains_poset(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).state_is_auto_read_accessible(xauto_access));  

  // Body:
 
  sec_vd_space& lvector_space = reinterpret_cast<sec_vd_space&>(xns.member_poset(xvector_space_path, xauto_access));
  int result = lvector_space.d(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
scalar_space_path(const namespace_poset& xns, const poset_path& xvector_space_path, bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));
  require(!xvector_space_path.empty());
  require(xns.contains_poset(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).state_is_auto_read_accessible(xauto_access));  

  // Body:
 
  sec_vd_space& lvector_space = reinterpret_cast<sec_vd_space&>(xns.member_poset(xvector_space_path, xauto_access));
  poset_path result = lvector_space.scalar_space_path(xauto_access);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

bool
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
is_vector(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  return is_vector(xmbr_id.hub_pod(), xauto_access);
}

void
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
is_covector(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  return is_covector(xmbr_id.hub_pod(), xauto_access);
}

void
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
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

// PROTECTED MEMBER FUNCTIONS

string
fiber_bundle::sec_vd_space::
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

fiber_bundle::sec_vd_space::
sec_vd_space()
  : sec_tuple_space(new sec_vd, new sec_vd)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(sec_tuple_space::sec_tuple_space()));
}

fiber_bundle::sec_vd_space::
sec_vd_space(const sec_vd_space& xother)
  : sec_tuple_space(new sec_vd, new sec_vd)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}

fiber_bundle::sec_vd_space::
~sec_vd_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_vd_space::
sec_vd_space(sec_vd* xtop, sec_vd* xbottom)
  : sec_tuple_space(xtop, xbottom)
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

void
fiber_bundle::sec_vd_space::
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
fiber_bundle::sec_vd_space::
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

//==============================================================================
// NEW HANDLE, NEW STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::sec_vd_space::
sec_vd_space(namespace_poset& xhost,
	     const string& xname,
	     const arg_list& xargs,
	     const poset_path& xschema_path,
	     bool xauto_access)
  : sec_tuple_space(new sec_vd, new sec_vd)
{

  // Preconditions:

  require(precondition_of(sec_vd_space::new_state(same args)));

  require(int(xargs.value("d")) >= 0);

  require(xhost.path_is_auto_read_accessible(xargs.value("scalar_space_path"), xauto_access));

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(sec_vd_space::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::sec_vd_space::
sec_vd_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : sec_tuple_space(new sec_vd, new sec_vd)
{
  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));
  require(xhost.contains_member(xindex, xauto_access));

  if(xauto_access)
  {
    xhost.get_read_access();
  }
  
  require(xhost.is_jim(xindex));

  // Body:

  attach_to_state(&xhost, xindex);

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(host() == &xhost);
  ensure(index() == xindex);
}

fiber_bundle::sec_vd_space::
sec_vd_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : sec_tuple_space(new sec_vd, new sec_vd)
{
  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));
  require(xhost.contains_member(xindex, xauto_access));

  if(xauto_access)
  {
    xhost.get_read_access();
  }
  
  require(xhost.is_jim(xindex));

  // Body:

  attach_to_state(&xhost, xindex.hub_pod());

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(host() == &xhost);
  ensure(index() ==~ xindex);
}

fiber_bundle::sec_vd_space::
sec_vd_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : sec_tuple_space(new sec_vd, new sec_vd)
{
  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));
  require(xhost.contains_member(xname));

  // Body:

  if(xauto_access)
  {
    xhost.get_read_access();
  }

  attach_to_state(&xhost, xname);

  // Postconditions:

  ensure(host() == &xhost);
  ensure(name() == xname);

  if(xauto_access)
  {
    xhost.release_access();
  }
}

fiber_bundle::sec_vd_space::
sec_vd_space(const namespace_poset_member& xmbr, bool xauto_access)
  : sec_tuple_space(new sec_vd, new sec_vd)
{
  // Preconditions:

  require(xmbr.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    xmbr.get_read_access();
  }

  attach_to_state(&xmbr);

  if(xauto_access)
  {
    xmbr.release_access();
  }

  // Postconditions:

  ensure(index() ==~ xmbr.index());
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_TUPLE_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_REP_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::sec_vd_space::
initialize_arg_list(const namespace_poset& xns,
		    const string& xname,
		    arg_list& xargs,
		    const poset_path& xschema_path,
		    bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));

  require(xschema_path.full());
  require(xns.member_poset(xschema_path, xauto_access).state_is_auto_read_accessible(xauto_access));
  
  /// @error arg_list attaches to a schema_poset_member however 
  ///        product_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xargs.conforms_to(xns, xschema_path, true, xauto_access));

  require(xns.path_is_auto_read_accessible(xargs.value("scalar_space_path"), xauto_access));
  
  // Body:

  sec_tuple_space::initialize_arg_list(xns, xname, xargs, xschema_path, xauto_access);
  xargs.value("d") = xargs.value("factor_ct");
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_vd_space::make_arg_list:result: " << result << endl;
#endif
  
  // Postconditions:

  ensure(xargs.value("d") == xargs.value("factor_ct"));

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::sec_vd_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  sec_vd_space* lproto = new sec_vd_space;
  poset_type ltype     = lproto->type_id();

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return result;
}


//==============================================================================
// POSET_STATE_HANDLE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_type
fiber_bundle::sec_vd_space::
type_id() const
{
  return SEC_VD_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::sec_vd_space::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_vd_space";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::sec_vd_space::
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

fiber_bundle::sec_vd_space&
fiber_bundle::sec_vd_space::
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

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::sec_vd_space::
initialize_standard_subposets(const string& xname)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(poset_path::is_valid_name(xname));

  // Body:

  sec_tuple_space::initialize_standard_subposets(xname);

  create_variance_subposets();

  put_standard_subposet_ct(subposet_ct());
  
  // Postconditions:

  ensure(postcondition_of(sec_tuple_space::initialize_standard_subposets(xname)));
  ensure(contains_variance_subposets(false));
  
  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// READ_WRITE_MONITOR_HANDLE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_vd_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_vd_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_vd_space*
fiber_bundle::sec_vd_space::
clone() const
{
  sec_vd_space* result;

  // Preconditions:

  // Body:

  result = new sec_vd_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::sec_vd_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(sec_tuple_space::invariant());

    invariance(state_is_read_accessible() ? factor_ct() == d() : true);

    enable_invariant_check();
  }

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

void
fiber_bundle::
print_prereq_paths(ostream &xos,
		   const sec_vd_space& xspace, 
		   const string& xheading, 
		   const string& xindent, 
		   bool xauto_access)
{
  // Preconditions:

  require(xspace.state_is_auto_read_accessible(xauto_access));
  require(xspace.name_space()->state_is_auto_read_accessible(xauto_access));
  
  // Body:

  const sec_tp_space*  ltensor_section_space = dynamic_cast<const sec_tp_space*>(&xspace);
  const sec_at1_space* lvector_section_space = dynamic_cast<const sec_at1_space*>(&xspace);
  const sec_at0_space* lscalar_section_space = dynamic_cast<const sec_at0_space*>(&xspace);

  namespace_poset* lns = xspace.name_space();
  
  if(xauto_access)
  {
    xspace.get_read_access();
  }
  
  
  xos << xindent << xheading << endl;

  string lindent = xindent + "   ";

  xos << lindent << "path:        " << xspace.path() << endl;
  xos << lindent << "schema path: " << xspace.schema().path() << endl;
  xos << lindent << "rep path:    " << xspace.schema().rep().path() << endl;
  xos << lindent << "base path:   " << xspace.schema().base_space().path() << endl;
  
  const vd_space& lfiber_space = reinterpret_cast<const vd_space&>(xspace.schema().fiber_space());
  print_prereq_paths(xos, lfiber_space, "fiber space", lindent, xauto_access);
  
  if(lscalar_section_space == 0)
  {
    // Xspace must be vector or tensor space; print scalar space.

    sec_at0_space& lscalar_space = lns->member_poset<sec_at0_space>(xspace.scalar_space_path(), xauto_access);
    print_prereq_paths(xos, lscalar_space, "scalar section space", lindent, xauto_access);
  
    if((lvector_section_space == 0) && (ltensor_section_space != 0)) 
    {
      // Xspace is tensor; print vector space.

      lvector_section_space = 
	&lns->member_poset<sec_at1_space>(ltensor_section_space->vector_space_path(), xauto_access);
      print_prereq_paths(xos, *lvector_section_space, "vector section space", lindent, xauto_access);  
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


