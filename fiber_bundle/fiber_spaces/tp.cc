
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
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
/// Implementation for class tp

#include "ComLimitPoint/fiber_bundle/tp.h"

#include "ComLimitPoint/sheaf/abstract_poset_member.impl.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/at1.h"
#include "ComLimitPoint/fiber_bundle/at1_space.h"
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#include "ComLimitPoint/sheaf/schema_poset_member.h"
#include "ComLimitPoint/fiber_bundle/tp_space.h"
#include "ComLimitPoint/sheaf/wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS TP_LITE
//==============================================================================

//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS TP_LITE
//==============================================================================

fiber_bundle::tp_lite::
tp_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::tp_lite::
tp_lite(const tp_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::tp_lite&
fiber_bundle::tp_lite::
operator=(const tp_lite& xother)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::tp_lite::
~tp_lite()
{
  // Preconditions:

  // Body:


  // Postconditions:

  // Exit:

}

fiber_bundle::tp_lite::
tp_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::tp_lite&
fiber_bundle::tp_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  vd_lite::operator=(xrow_dofs);
  
  // Postconditions:

  postcondition_of(vd_lite::operator=(xrow_dofs));

  // Exit:

  return *this;

}

int
fiber_bundle::tp_lite::
p() const
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

int
fiber_bundle::tp_lite::
dd() const
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

sheaf::pod_index_type
fiber_bundle::tp_lite::
vector_space_index() const
{
  // Preconditions:

  // Body:

  pod_index_type result = 0; // Just to silence compiler.

  // Postconditions:

  ensure(invariant());
  ensure(result == 0);

  // Exit:

  return result;
}

fiber_bundle::tp_lite::table_dofs_type
fiber_bundle::tp_lite::
table_dofs() const
{
  // Preconditions:

  // Body:

  /// @issue Where do these c_strings get deleted?

  int lfactor_ct = factor_ct();
  int ld         = d();

  char* lscalar_space_path = new char[1];
  lscalar_space_path[0] = 0;

  int lp         = p();
  int ldd        = dd();
  
  char* lvector_space_path = new char[1];
  lvector_space_path[0] = 0;

  table_dofs_type result =
    {
      lfactor_ct, 
      ld,
      lscalar_space_path,
      lp, 
      ldd, 
      lvector_space_path
    };

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS TP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::tp_lite::
d() const
{
  // Preconditions:

  // Body:

  int result = 0;
  if(!(dd() == 0 && p() == 0))
  {
    result = static_cast<int>(pow(static_cast<double>( dd() ),
                                  static_cast<int>( p() )));
  }


  // Postconditions:

  ensure(invariant());
  // $$SCRIBBLE kabuch: Next line causes doxygen to emit a warning:
  // <unknown>:1: Warning: Unsupported xml/html tag <int> found
  //ensure(result == static_cast< int >(pow(static_cast<double>(dd()),
  //					  static_cast<int>(p()))));

  // Exit:

  return result;
}

//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS TP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS TP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::tp_lite::
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
fiber_bundle::tp_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("tp_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::tp_lite*
fiber_bundle::tp_lite::
clone() const
{
  tp_lite* result = 0;

  // Preconditions:

  // Body:

  result = new tp_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS TP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::tp_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const tp_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::tp_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(vd_lite::invariant());

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
// CLASS TP
//==============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::tp::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "tp_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

void
fiber_bundle::tp::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "p INT true";
  lmember_names += " dd INT true";
  lmember_names += " vector_space_path C_STRING true";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              vd::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::tp::host_type&
fiber_bundle::tp::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         int xp,
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering tp::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));

  require(host_type::d(xns, xschema_path, xauto_access) == host_type::d(xns, xp, xvector_space_path, xauto_access));   


  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, xp, xvector_space_path, xauto_access); 

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == host_type::d(xns, xschema_path, xauto_access));
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path());
  ensure(result.p(true) == xp);
  ensure(result.dd(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d());
  ensure(result.vector_space_path(true) == xvector_space_path );
  
  // Exit:

  // cout << "Leaving tp::new_host." << endl;
  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS TP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tp::
tp()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::tp::
tp(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::tp::
tp(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::tp::
tp(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::tp::
tp(abstract_poset_member* xother)
{

  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));

  // Exit:

}

fiber_bundle::tp::
tp(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::tp&
fiber_bundle::tp::
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

fiber_bundle::tp&
fiber_bundle::tp::
operator=(const tp& xother)
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

fiber_bundle::tp::
~tp()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

int
fiber_bundle::tp::
p() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = sheaf::table_dofs(*this).p;

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::tp::
p(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  int result = p();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}


int
fiber_bundle::tp::
dd() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = sheaf::table_dofs(*this).dd;

  // Postconditions:

  //  ensure(invariant());
  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::tp::
dd(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  int result = dd();

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

sheaf::poset_path
fiber_bundle::tp::
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
fiber_bundle::tp::
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

fiber_bundle::tp_space& 
fiber_bundle::tp::
vector_space() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(name_space()->state_is_read_accessible());

  // Body:

  poset_state_handle& lpsh = name_space()->member_poset(vector_space_path(), false);

  tp_space& result = reinterpret_cast<host_type&>(lpsh);

  // Postconditions:

  // Exit:

  return result;

}

fiber_bundle::tp_space&
fiber_bundle::tp::
vector_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(name_space()->state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    name_space()->get_read_access();
    get_read_access();
  }

  tp_space& result = vector_space();

  if(xauto_access)
  {
    release_access();
    name_space()->release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

const std::string
fiber_bundle::tp::
create_tensor_space_name(const std::string& xvector_space_name, const std::string& xname)
{
 // Preconditions:

  // Body:

  const string result = xvector_space_name + "_" + xname;   

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::tp::volatile_type&
fiber_bundle::tp::
lite_prototype() const
{
  // Preconditions:

  // Body:

  static const volatile_type result;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::tp::volatile_type*
fiber_bundle::tp::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::tp::
variance(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  tensor_variance result = host()->variance(_index, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::tp::
variance(int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  bool result = host()->variance(_index, xi, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::tp::
put_variance(const tensor_variance& xvariance, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  host()->put_variance(_index, xvariance, xauto_access);
  
  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::tp::
put_variance(int xi, bool xvariance, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  host()->put_variance(_index, xi, xvariance, xauto_access);
  
  // Postconditions:

  // Exit:

  return;
}

bool
fiber_bundle::tp::
is_covariant(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  bool result = host()->is_covariant(_index, xauto_access);

  // Postconditions:
  
  // Exit:

  return result;
}

bool
fiber_bundle::tp::
is_covariant(int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  bool result = host()->is_covariant(_index, xi, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::tp::
put_is_covariant(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  host()->put_is_covariant(_index, xauto_access);

  // Postconditions:

  ensure(is_covariant(xauto_access));
  
  // Exit:

  return;
}

void
fiber_bundle::tp::
put_is_covariant(int xi, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  host()->put_is_covariant(_index, xi, xauto_access);

  // Postconditions:

  ensure(is_covariant(xi, xauto_access));
  
  // Exit:

  return;
}

bool
fiber_bundle::tp::
is_contravariant(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  bool result = host()->is_contravariant(_index, xauto_access);

  // Postconditions:
  
  // Can not ensure result == !is_covariant because at0 is both co- and contra-vairant.

  // Exit:

  return result;
}

bool
fiber_bundle::tp::
is_contravariant(int xi, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  bool result = host()->is_contravariant(_index, xi, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::tp::
put_is_contravariant(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  host()->put_is_contravariant(_index, xauto_access);

  // Postconditions:
  
  ensure(is_contravariant(xauto_access));

  // Exit:

  return;
}

void
fiber_bundle::tp::
put_is_contravariant(int xi, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xi) && (xi < p(xauto_access)));
  
  // Body:

  host()->put_is_contravariant(_index, xi, xauto_access);

  // Postconditions:

  ensure(is_contravariant(xi, xauto_access));
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS TP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS TP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::tp::
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
fiber_bundle::tp::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("tp");

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

fiber_bundle::tp::host_type*
fiber_bundle::tp::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::tp::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS TP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::tp::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of xother.

  bool result = dynamic_cast<const tp*>(xother) != 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;

}

fiber_bundle::tp*
fiber_bundle::tp::
clone() const
{

  // Preconditions:

  // Body:

  tp* result = 0;

  // Create new handle of the current class.

  result = new tp();

  // Postconditions:

   ensure(result != 0);
   ensure(result->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::tp::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(vd::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Invariants for this class:

    invariance(state_is_read_accessible() ? p() >= 0 : true);

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

std::ostream&
fiber_bundle::
operator<<(std::ostream& xos, tp_lite::table_dofs_type& xt)
{
  xos << " " << xt.factor_ct
      << " " << xt.d
      << " " << xt.scalar_space_path
      << " " << xt.p
      << " " << xt.dd
      << " " << xt.vector_space_path;

  return xos;
}

//==============================================================================
// TP FACET
//==============================================================================

#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/at0.h"
#include "ComLimitPoint/fiber_bundle/at1.h"
#include "ComLimitPoint/fiber_bundle/at2.h"
#include "ComLimitPoint/fiber_bundle/at3_e3.h"
#include "ComLimitPoint/fiber_bundle/st2.h"
#include "ComLimitPoint/fiber_bundle/st3.h"
#include "ComLimitPoint/fiber_bundle/st3_e3.h"
#include "ComLimitPoint/fiber_bundle/st4_e2.h"
#include "ComLimitPoint/fiber_bundle/st4_e3.h"
#include "ComLimitPoint/fiber_bundle/t2.h"
#include "ComLimitPoint/fiber_bundle/t3.h"
#include "ComLimitPoint/fiber_bundle/t3_e3.h"
#include "ComLimitPoint/fiber_bundle/t4_e2.h"
#include "ComLimitPoint/fiber_bundle/t4_e3.h"

void
fiber_bundle::tp_algebra::
contract(const tp_lite& x0, int xp, int xq, tp_lite& xresult)
{
  // Preconditions:

  require(xp >= 0 && xp <= x0.p());
  require(xq >= 0 && xq <= x0.p());
  require(xresult.p() == x0.p() - 2);

  // Body:

  const t2_lite* t2_x0  = dynamic_cast<const t2_lite*>(&x0);
  const t3_lite* t3_x0  = dynamic_cast<const t3_lite*>(&x0);

  at0_lite* at0_xresult = dynamic_cast<at0_lite*>(&xresult);
  at1_lite* at1_xresult = dynamic_cast<at1_lite*>(&xresult);

  if(t2_x0 && at0_xresult)
  {
    contract(*t2_x0, xp, xq, *at0_xresult);
  }
  else if(t3_x0 && at1_xresult)
  {
    contract(*t3_x0, xp, xq, *at1_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to contract(...)");
  } 

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
contract(const tp& x0, int xp, int xq, tp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(xp >= 0 && xp <= x0.p(xauto_access));
  require(xq >= 0 && xq <= x0.p(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) - 2);

  // Body:

  const t2* t2_x0  = dynamic_cast<const t2*>(&x0);
  const t3* t3_x0  = dynamic_cast<const t3*>(&x0);

  at0* at0_xresult = dynamic_cast<at0*>(&xresult);
  at1* at1_xresult = dynamic_cast<at1*>(&xresult);

  if(t2_x0 && at0_xresult)
  {
    contract(*t2_x0, xp, xq, *at0_xresult, xauto_access);
  }
  else if(t3_x0 && at1_xresult)
  {
    contract(*t3_x0, xp, xq, *at1_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to contract(...)");
  } 

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
alt(const tp_lite& x0, tp_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  const t2_lite* t2_x0  = dynamic_cast<const t2_lite*>(&x0);
  const t3_lite* t3_x0  = dynamic_cast<const t3_lite*>(&x0);
  const t3_e3_lite* t3_e3_x0 = dynamic_cast<const t3_e3_lite*>(&x0);

  at2_lite* at2_xresult = dynamic_cast<at2_lite*>(&xresult);
  t2_lite* t2_xresult = dynamic_cast<t2_lite*>(&xresult);
  at3_e3_lite* at3_e3_xresult = dynamic_cast<at3_e3_lite*>(&xresult);
  at3_lite* at3_xresult = dynamic_cast<at3_lite*>(&xresult);
  t3_lite* t3_xresult = dynamic_cast<t3_lite*>(&xresult);

  if(t2_x0 && at2_xresult)
  {
    alt(*t2_x0, *at2_xresult);
  }
  else if(t2_x0 && t2_xresult)
  {
    alt(*t2_x0, *t2_xresult);
  }
  else if(t3_e3_x0 && at3_e3_xresult)
  {
    alt(*t3_e3_x0, *at3_e3_xresult);
  }
  else if(t3_x0 && t3_xresult)
  {
    alt(*t3_x0, *t3_xresult);
  }
  else if(t3_x0 && at3_xresult)
  {
    alt(*t3_x0, *at3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to alt(...)");
  } 

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
alt(const tp& x0, tp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(x0.dd() == xresult.dd());

  // Body:

  const t2* t2_x0  = dynamic_cast<const t2*>(&x0);
  const t3* t3_x0  = dynamic_cast<const t3*>(&x0);
  const t3_e3* t3_e3_x0 = dynamic_cast<const t3_e3*>(&x0);

  at2* at2_xresult = dynamic_cast<at2*>(&xresult);
  t2* t2_xresult = dynamic_cast<t2*>(&xresult);
  at3_e3* at3_e3_xresult = dynamic_cast<at3_e3*>(&xresult);
  at3* at3_xresult = dynamic_cast<at3*>(&xresult);
  t3* t3_xresult = dynamic_cast<t3*>(&xresult);

  if(t2_x0 && at2_xresult)
  {
    alt(*t2_x0, *at2_xresult, xauto_access);
  }
  else if(t2_x0 && t2_xresult)
  {
    alt(*t2_x0, *t2_xresult, xauto_access);
  }
  else if(t3_e3_x0 && at3_e3_xresult)
  {
    alt(*t3_e3_x0, *at3_e3_xresult, xauto_access);
  }
  else if(t3_x0 && t3_xresult)
  {
    alt(*t3_x0, *t3_xresult, xauto_access);
  }
  else if(t3_x0 && at3_xresult)
  {
    alt(*t3_x0, *at3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to alt(...)");
  } 

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
sym(const tp_lite& x0, tp_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  const t2_lite* t2_x0  = dynamic_cast<const t2_lite*>(&x0);
  const t3_lite* t3_x0  = dynamic_cast<const t3_lite*>(&x0);
  const t3_e3_lite* t3_e3_x0 = dynamic_cast<const t3_e3_lite*>(&x0);
  const t4_e2_lite* t4_e2_x0 = dynamic_cast<const t4_e2_lite*>(&x0);
  const t4_e3_lite* t4_e3_x0 = dynamic_cast<const t4_e3_lite*>(&x0);

  st2_lite* st2_xresult = dynamic_cast<st2_lite*>(&xresult);
  st3_lite* st3_xresult = dynamic_cast<st3_lite*>(&xresult);
  st3_e3_lite* st3_e3_xresult = dynamic_cast<st3_e3_lite*>(&xresult);
  t2_lite* t2_xresult = dynamic_cast<t2_lite*>(&xresult);
  t3_lite* t3_xresult = dynamic_cast<t3_lite*>(&xresult);
  st4_e2_lite* st4_e2_xresult = dynamic_cast<st4_e2_lite*>(&xresult);
  st4_e3_lite* st4_e3_xresult = dynamic_cast<st4_e3_lite*>(&xresult);

  if(t2_x0 && st2_xresult)
  {
    sym(*t2_x0, *st2_xresult);
  }
  else if(t2_x0 && t2_xresult)
  {
    sym(*t2_x0, *t2_xresult);
  }
  else if(t3_e3_x0 && st3_e3_xresult)
  {
    sym(*t3_e3_x0, *st3_e3_xresult);
  }
  else if(t3_x0 && t3_xresult)
  {
    sym(*t3_x0, *t3_xresult);
  }
  else if(t3_x0 && st3_xresult)
  {
    sym(*t3_x0, *st3_xresult);
  }
  else if(t4_e2_x0 && st4_e2_xresult)
  {
    sym(*t4_e2_x0, *st4_e2_xresult);
  }
  else if(t4_e3_x0 && st4_e3_xresult)
  {
    sym(*t4_e3_x0, *st4_e3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to sym(...)");
  } 

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
sym(const tp& x0, tp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(x0.dd() == xresult.dd());

  // Body:

  const t2* t2_x0  = dynamic_cast<const t2*>(&x0);
  const t3* t3_x0  = dynamic_cast<const t3*>(&x0);
  const t3_e3* t3_e3_x0 = dynamic_cast<const t3_e3*>(&x0);
  const t4_e2* t4_e2_x0 = dynamic_cast<const t4_e2*>(&x0);
  const t4_e3* t4_e3_x0 = dynamic_cast<const t4_e3*>(&x0);

  st2* st2_xresult = dynamic_cast<st2*>(&xresult);
  st3* st3_xresult = dynamic_cast<st3*>(&xresult);
  st3_e3* st3_e3_xresult = dynamic_cast<st3_e3*>(&xresult);
  t2* t2_xresult = dynamic_cast<t2*>(&xresult);
  t3* t3_xresult = dynamic_cast<t3*>(&xresult);
  st4_e2* st4_e2_xresult = dynamic_cast<st4_e2*>(&xresult);
  st4_e3* st4_e3_xresult = dynamic_cast<st4_e3*>(&xresult);

  if(t2_x0 && st2_xresult)
  {
    sym(*t2_x0, *st2_xresult, xauto_access);
  }
  else if(t2_x0 && t2_xresult)
  {
    sym(*t2_x0, *t2_xresult, xauto_access);
  }
  else if(t3_e3_x0 && st3_e3_xresult)
  {
    sym(*t3_e3_x0, *st3_e3_xresult, xauto_access);
  }
  else if(t3_x0 && t3_xresult)
  {
    sym(*t3_x0, *t3_xresult, xauto_access);
  }
  else if(t3_x0 && st3_xresult)
  {
    sym(*t3_x0, *st3_xresult, xauto_access);
  }
  else if(t4_e2_x0 && st4_e2_xresult)
  {
    sym(*t4_e2_x0, *st4_e2_xresult, xauto_access);
  }
  else if(t4_e3_x0 && st4_e3_xresult)
  {
    sym(*t4_e3_x0, *st4_e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to sym(...)");
  } 

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
tensor(const tp_lite& x0, const tp_lite& x1, tp_lite& xresult)
{
  // Preconditions:

  require(x1.dd() == x0.dd());
  require(xresult.dd() == x0.dd());
  require(xresult.p() == x0.p() + x1.p());

  // Body:

  const at1_lite* at1_x0 = dynamic_cast<const at1_lite*>(&x0);
  const at2_lite* at2_x0 = dynamic_cast<const at2_lite*>(&x0);
  const st2_lite* st2_x0 = dynamic_cast<const st2_lite*>(&x0);
  const t2_lite*  t2_x0  = dynamic_cast<const t2_lite*>(&x0);

  const at1_lite* at1_x1 = dynamic_cast<const at1_lite*>(&x1);
  const at2_lite* at2_x1 = dynamic_cast<const at2_lite*>(&x1);
  const st2_lite* st2_x1 = dynamic_cast<const st2_lite*>(&x1);
  const t2_lite*  t2_x1  = dynamic_cast<const t2_lite*>(&x1);

  t2_lite* t2_xresult = dynamic_cast<t2_lite*>(&xresult);
  t3_lite* t3_xresult = dynamic_cast<t3_lite*>(&xresult);

  if(at1_x0 && at1_x1 && t2_xresult)
  {
    tensor(*at1_x0, *at1_x1, *t2_xresult);
  }
  else if(t2_x0 && at1_x1 && t3_xresult)
  {
  tensor(*t2_x0, *at1_x1, *t3_xresult);
  }
  else if(at1_x0 && t2_x1 && t3_xresult)
  {
    tensor(*at1_x0, *t2_x1, *t3_xresult);
  }
  else if(at2_x0 && at1_x1 && t3_xresult)
  {
    tensor(*at2_x0, *at1_x1, *t3_xresult);
  }
  else if(at1_x0 && at2_x1 && t3_xresult)
  {
    tensor(*at1_x0, *at2_x1, *t3_xresult);
  }
  else if(st2_x0 && at1_x1 && t3_xresult)
  {
    tensor(*st2_x0, *at1_x1, *t3_xresult);
  }
  else if(at1_x0 && st2_x1 && t3_xresult)
  {
    tensor(*at1_x0, *st2_x1, *t3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to tensor(...)");
  } 
                
  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
tensor(const tp& x0, const tp& x1, tp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) + x1.p(xauto_access));

  // Body:

  const at1* at1_x0 = dynamic_cast<const at1*>(&x0);
  const at2* at2_x0 = dynamic_cast<const at2*>(&x0);
  const st2* st2_x0 = dynamic_cast<const st2*>(&x0);
  const t2*  t2_x0  = dynamic_cast<const t2*>(&x0);

  const at1* at1_x1 = dynamic_cast<const at1*>(&x1);
  const at2* at2_x1 = dynamic_cast<const at2*>(&x1);
  const st2* st2_x1 = dynamic_cast<const st2*>(&x1);
  const t2*  t2_x1  = dynamic_cast<const t2*>(&x1);

  t2* t2_xresult = dynamic_cast<t2*>(&xresult);
  t3* t3_xresult = dynamic_cast<t3*>(&xresult);

  if(at1_x0 && at1_x1 && t2_xresult)
  {
    tensor(*at1_x0, *at1_x1, *t2_xresult, xauto_access);
  }
  else if(t2_x0 && at1_x1 && t3_xresult)
  {
  tensor(*t2_x0, *at1_x1, *t3_xresult, xauto_access);
  }
  else if(at1_x0 && t2_x1 && t3_xresult)
  {
    tensor(*at1_x0, *t2_x1, *t3_xresult, xauto_access);
  }
  else if(at2_x0 && at1_x1 && t3_xresult)
  {
    tensor(*at2_x0, *at1_x1, *t3_xresult, xauto_access);
  }
  else if(at1_x0 && at2_x1 && t3_xresult)
  {
    tensor(*at1_x0, *at2_x1, *t3_xresult, xauto_access);
  }
  else if(st2_x0 && at1_x1 && t3_xresult)
  {
    tensor(*st2_x0, *at1_x1, *t3_xresult, xauto_access);
  }
  else if(at1_x0 && st2_x1 && t3_xresult)
  {
    tensor(*at1_x0, *st2_x1, *t3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to tensor(...)");
  } 

  // Postconditions:

  //@todo Fix this.
  //ensure(xresult.variance(xauto_access) == \
  //  (x0.variance(xauto_access) | x1.variance(xauto_access)));

  // Exit:

  return;
}

