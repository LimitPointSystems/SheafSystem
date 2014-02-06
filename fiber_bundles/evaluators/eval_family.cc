
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

// Implementation for class eval_family

#include "eval_family.h"

#include "assert_contract.h"
#include "constant_eval_family.h"
#include "dlinear_eval_family.h"
#include "factory.impl.h"
#include "section_evaluator.h"
#include "uniform_eval_family.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
fiber_bundle::eval_family::
eval_family(const eval_family& xother)
{

  // Preconditions:

  // Body:

  eval_family& lfam = const_cast<eval_family&>(xother);

  _members.reserve(lfam._members.ct());

  for(int i=0; i<lfam._members.ct(); ++i)
  {
    section_evaluator* lsec = lfam._members[i];

    if (lsec != 0)
      _members[i] = lsec->clone();
    else
      _members[i] = 0;
  }
  _members.set_ct(lfam._members.ct());
  _is_initialized = xother._is_initialized;

  // Postconditions:

  ensure(invariant());
}



///
fiber_bundle::eval_family*
fiber_bundle::eval_family::
clone() const
{
  eval_family* result = 0; // Initialize to avoid compiler warnings.

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
fiber_bundle::eval_family::
~eval_family()
{

  // Preconditions:

  // Body:

  for(int i=0; i<_members.ct(); i++)
  {
    section_evaluator* lmbr = _members[i];
    if(lmbr != 0)
    {
      delete lmbr;
    }
  }

  // Postconditions:

  // Exit:

  return;
}


///
bool
fiber_bundle::eval_family::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
fiber_bundle::eval_family::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const eval_family*>(xother) != 0;

  // Postconditions:

  return result;

}



// EVALUATOR_FAMILY FACET

///
fiber_bundle::eval_family*
fiber_bundle::eval_family::
new_family(const std::string& xname)
{
  eval_family* result;

  // Preconditions:

  require(family_factory().contains_prototype(xname));

  // Body:

  result = family_factory().new_instance(xname);

  // Postconditions:

  ensure(result != 0);
  ensure(result->class_name() == xname);
  ensure(!result->is_initialized());

  // Exit

  return result;
}

///
fiber_bundle::eval_family*
fiber_bundle::eval_family::
new_family(const std::string& xname, const namespace_poset& xname_space)
{
  eval_family* result;

  // Preconditions:
 
  require(family_factory().contains_prototype(xname));
  require(xname_space.state_is_read_accessible());

  // Body:

  result = family_factory().new_instance(xname, const_cast<namespace_poset&>(xname_space));

  // Postconditions:

  ensure(result != 0);
  ensure(result->class_name() == xname);
  ensure(result->is_initialized());

  // Exit

  return result;
}

void
fiber_bundle::eval_family::
insert_family_prototype(eval_family* xprototype)
{
  // Preconditions:

  require(xprototype != 0);

  // Body:

  family_factory().insert_prototype(xprototype);

  // Postconditions:

  ensure(family_factory().contains_prototype(xprototype->class_name()));

  // Exit:

  return;
}


///
sheaf::factory<fiber_bundle::eval_family>&
fiber_bundle::eval_family::
family_factory()
{

  // Preconditions:


  // Body:

  static factory<fiber_bundle::eval_family>& result = initialize_family_factory();

  // Postconditions:


  // Exit:

  return result;
}

///
const std::string&
fiber_bundle::eval_family::
class_name() const
{

  // Preconditions:

  // Body:

  is_abstract();

  static const string result;

  // Postconditions:

  ensure(!result.empty());

  // Exit

  return result;
}


///
fiber_bundle::section_evaluator*
fiber_bundle::eval_family::
member(pod_index_type xtype_id) const
{
  section_evaluator* result;

  // Preconditions:

  require((0 <= xtype_id) && (xtype_id < size()));

  // Body:

  // Get the family member associated with base space member.

  result = _members[xtype_id];

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::section_evaluator*
fiber_bundle::eval_family::
member(const poset_state_handle& xhost, pod_index_type xhub_id)
{
  section_evaluator* result;

  // Preconditions:

  require(xhost.state_is_read_accessible());
  require(xhost.schema().conforms_to(base_space_member::standard_schema_path()));
  require(xhost.contains_member(xhub_id));
  require(xhost.is_jim(xhub_id));

  // Body:

  // Get the family member associated with base space member.

  void* ldof_tuple = const_cast<poset_state_handle&>(xhost).member_dof_map(xhub_id).dof_tuple();
  pod_index_type ltype_id =
    reinterpret_cast<base_space_member::row_dof_tuple_type*>(ldof_tuple)->type_id;

  result = member(ltype_id);

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::section_evaluator*
fiber_bundle::eval_family::
member(const poset_state_handle& xhost, const scoped_index& xid)
{
  section_evaluator* result;

  // Preconditions:

  require(xhost.state_is_read_accessible());
  require(xhost.schema().conforms_to(base_space_member::standard_schema_path()));
  require(xhost.contains_member(xid));
  require(xhost.is_jim(xid));

  // Body:

  return member(xhost, xid.hub_pod());
}

///
sheaf::size_type
fiber_bundle::eval_family::
size() const
{
  size_type result;

  // Preconditions:

  // Body:

  result = _members.ct();

  // Postconditions:


  // Exit:

  return result;
}

///
void
fiber_bundle::eval_family::
initialize(const namespace_poset& xname_space)
{
  // Preconditions:

  require(!is_initialized());
  require(xname_space.state_is_read_accessible());

  // Body:

  _is_initialized = true;

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());

  // Exit:

  return;
}

///
bool
fiber_bundle::eval_family::
is_initialized() const
{
  return _is_initialized;
}

// ===========================================================
// PROTECTED MEMBER FUNCTIONS
// ===========================================================

///
fiber_bundle::eval_family::
eval_family()
    : _is_initialized(false)
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Initialize_members() must be called from descendants
  // in order to avoid repeatedly getting a handle and access
  // to the prototypes poset.

  // Postconditions:

  ensure(invariant());
}

///
void
fiber_bundle::eval_family::
initialize_members(size_type xmembers_ub)
{
  // Preconditions:

  // Body:

  _members.reserve(xmembers_ub);
  _members.set_ct(_members.ub());
  //  _members.assign(0); auto_block zero initialization policy make this unnecessary.

  // Postconditions:

  ensure(_members.ct() == _members.ub());
  ensure_for_all(i, 0, _members.ct(), _members[i] == 0);

  // Exit:

  return;
}

///
sheaf::factory<fiber_bundle::eval_family>&
fiber_bundle::eval_family::
initialize_family_factory()
{

  // Preconditions:

  // Body:

  static factory<fiber_bundle::eval_family> result;
  
  result.insert_prototype(new dlinear_eval_family());
  result.insert_prototype(new constant_eval_family());
  result.insert_prototype(new uniform_eval_family());

  // Postconditions:


  // Exit:

  return result;
}
