
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
/// Implementation for class gln.


#ifdef _WIN32

// We're compiling with MS C++; 
// make sure we get M_PI defined.

#define _USE_MATH_DEFINES

#endif

#include "gln.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at1.h"
#include "at1_space.h"
#include "gln_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "std_cmath.h"
#include "wsv_block.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS GLN_TABLE_DOFS_TYPE
//==============================================================================


//==============================================================================
// CLASS GLN_ROW_DOFS_TYPE
//==============================================================================

//==============================================================================
// CLASS GLN_LITE
//==============================================================================


//============================================================================
//  GLN FACET OF CLASS GLN_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::gln_lite::
gln_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gln_lite::
gln_lite(const gln_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gln_lite&
fiber_bundle::gln_lite::
operator=(const gln_lite& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::gln_lite::
~gln_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::gln_lite::
gln_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gln_lite&
fiber_bundle::gln_lite::
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
fiber_bundle::gln_lite::
d() const
{
  // Preconditions:

  // Body:

  int result = 2*n()*n();

  // Postconditions:

  ensure(invariant());
  ensure(result == 2*n()*n());

  // Exit:

  return result;

}

int
fiber_bundle::gln_lite::
n() const
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


fiber_bundle::gln_lite::value_type
fiber_bundle::gln_lite::
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
fiber_bundle::gln_lite::
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
fiber_bundle::gln_lite::
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
fiber_bundle::gln_lite::
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

fiber_bundle::gln_lite::value_type&
fiber_bundle::gln_lite::
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

const fiber_bundle::gln_lite::value_type&
fiber_bundle::gln_lite::
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

//============================================================================
// GROUP FACET OF CLASS GLN_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS GLN_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::gln_lite::
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
fiber_bundle::gln_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("gln_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::gln_lite*
fiber_bundle::gln_lite::
clone() const
{
  gln_lite* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}


fiber_bundle::gln_lite::table_dofs_type
fiber_bundle::gln_lite::
table_dofs() const
{
  // Preconditions:

  // Body:

  int ln = n();

  /// @issue Where do these c_strings get deleted?

  char* lscalar_space_path = new char[1];
  lscalar_space_path[0] = 0;
  
  char* lvector_space_path = new char[1];
  lvector_space_path[0] = 0;
  
  table_dofs_type result =
    {
      lscalar_space_path,
      lvector_space_path,
      ln
    };
  
  // Postconditions:

  // Exit:
  
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// ANY FACET OF CLASS GLN_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::gln_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const gln_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}


bool
fiber_bundle::gln_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(group_lite::invariant());

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
// CLASS GLN
//==============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::gln::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string result("fiber_space_schema");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::poset_path&
fiber_bundle::gln::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "gln_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

void
fiber_bundle::gln::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:


  // Dof id space space of schema member (e.g. fiber_space_poset/gln_schema) in
  // will be defined in same order as dof id space of fiber_schema_poset/top,
  // independent of which order we declare them in.
  // The members of gln_table_dofs_type must be also declared in this same order;
  // so we might as well declare the dofs in the same order for consistency.

  /// @issue: The relationship of the dof schema declarations to the dof order
  /// is totally opaque. We need to somehow clarify this.

  string lmember_names;
  lmember_names += "scalar_space_path C_STRING true";
  lmember_names += " vector_space_path C_STRING true";  
  lmember_names += " n INT true";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              poset_path(standard_schema_poset_name(), "bottom"),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::gln::host_type&
fiber_bundle::gln::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering gln::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));

  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == host_type::d(xns, xvector_space_path, xauto_access));

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, xvector_space_path, xauto_access); 

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access) );
  ensure(result.n(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d());
  ensure(result.vector_space_path(true) == xvector_space_path );

  ensure(result.d(true) == host_type::d(xns, xvector_space_path, xauto_access));
  
  // Exit:

  // cout << "Leaving gln::new_host." << endl;
  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//============================================================================
//  GLN FACET OF CLASS GLN
//============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::gln::
gln()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::gln::
gln(const gln& xother, bool xnew_jem)
{

  // Preconditions:

  require(xnew_jem ? xother.is_attached() : true);

  // Body:

  // Note: even though the code here is identical to that in
  // the copy constructors of all descendants of abstract_poset_member,
  // this can not just call base class copy constructor
  // because it must invoke versions defined in this class of virtual
  // attach_to_state and virtual attach_handle_data_members
  // (called from new_jem_state).

  if (xnew_jem)
  {
    new_jem_state(const_cast<gln*>(&xother), true, true);
  }
  else
  {
    attach_to_state(&xother);
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

///
fiber_bundle::gln&
fiber_bundle::gln::
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
fiber_bundle::gln&
fiber_bundle::gln::
operator=(const gln& xother)
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

///
fiber_bundle::gln::
~gln()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::gln::
gln(poset* xhost, bool xauto_access)
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

fiber_bundle::gln::
gln(const poset* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  // ensure(host() == xhost);
  ensure(index() == xhub_id);
}

fiber_bundle::gln::
gln(const poset* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  // ensure(host() == xhost);
  ensure(index() ==~ xid);
}

fiber_bundle::gln::
gln(const poset* xhost, const std::string& xname)
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
  ensure(is_attached());
  // ensure(host() == xhost);
  ensure(name() == xname);

}

fiber_bundle::gln::
gln(gln* xother)
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

int
fiber_bundle::gln::
n() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->n();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::gln::
n(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  int result = host()->n(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln::
scalar_space_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  poset_path result = host()->scalar_space_path();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln::
scalar_space_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  poset_path result = host()->scalar_space_path(xauto_access);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln::
vector_space_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  poset_path result = host()->vector_space_path();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln::
vector_space_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  poset_path result = host()->vector_space_path(xauto_access);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

int
fiber_bundle::gln::
d() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int ln = n();
  int result = 2*ln*ln;

  // Postconditions:

  /// @hack can't call invariant because it's not const
  // ensure(invariant());
  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::gln::
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

fiber_bundle::gln::value_type
fiber_bundle::gln::
component(int xindex) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xindex) &&(xindex <  d()));

  // Body:

  value_type result = sheaf::row_dofs(*this)[xindex];
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::gln::value_type
fiber_bundle::gln::
component(int xindex, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xindex) &&(xindex <  d(xauto_access)));

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
fiber_bundle::gln::
put_component(int xindex, value_type xcomp)
{
  // Preconditions:

  require(state_is_read_write_accessible());
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
fiber_bundle::gln::
put_component(int xindex, value_type xcomp, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xindex) && (xindex <=  d(xauto_access)));

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
fiber_bundle::gln::
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
fiber_bundle::gln::
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

fiber_bundle::gln::dof_type&
fiber_bundle::gln::
operator[] (int xindex)
{
  // Preconditions.

  require(state_is_read_write_accessible());
  ensure(xindex>=0 && xindex<d());

  // Body:

  dof_type& result = sheaf::row_dofs(*this)[xindex];

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::gln::dof_type&
fiber_bundle::gln::
operator[] (int xindex) const
{
  // Preconditions.

  require(state_is_read_accessible());
  require(xindex>=0 && xindex<d());

  // Body:

  const dof_type& result = sheaf::row_dofs(*this)[xindex];

  // Postconditions:

  // Exit:

  return result;

}

///
fiber_bundle::gln::volatile_type*
fiber_bundle::gln::
lite_type() const
{
  // Preconditions:

  // Body:

  ///@todo: Fix gln_lite so this works. 
  //volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  volatile_type* result = new volatile_type();
  for(int i=0; i<d(); ++i)
  {
    value_type v = component(i);
    result->put_component(i, v);
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
//  GROUP FACET OF CLASS GLN
//============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS GLN
//============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::gln::
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
fiber_bundle::gln::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("gln");

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
 

fiber_bundle::gln::host_type*
fiber_bundle::gln::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::gln::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



//===========================================================================
// ANY FACET OF CLASS GLN
//===========================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::gln::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(group::invariant());

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

fiber_bundle::gln*
fiber_bundle::gln::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  gln* result = new gln();

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;

}

bool
fiber_bundle::gln::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if xother conforms to this.

  bool result = dynamic_cast<const gln*>(xother) != 0;

  // Postconditions:

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

double 
fiber_bundle::
rad(double degrees)
{
  static const double RAD_PER_DEG = M_PI/180.0;
  return degrees*RAD_PER_DEG;
};

std::ostream& 
fiber_bundle::
operator<<(std::ostream& xos, gln_lite::table_dofs_type& xt)
{
  xos << " " << xt.n
      << " " << xt.scalar_space_path
      << " " << xt.vector_space_path;

  return xos;
}

std::ostream& 
fiber_bundle::
operator<<(std::ostream& xos, gln_lite& xv)
{
  int ld = xv.d();
  for(int i=0; i<ld; ++i)
  {
    xos << " " << xv[i];
  }

  return xos;
}


