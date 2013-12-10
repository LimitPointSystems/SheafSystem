
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



// Implementation for class section_dof_map

#include "section_dof_map.h"

#include "assert_contract.h"
#include "binary_section_space_schema_member.h"
#include "poset_type.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// PUBLIC MEMBER FUNCTIONS

///
const std::string&
fiber_bundle::section_dof_map::
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

///
const std::string&
fiber_bundle::section_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("section_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "section_dof_map");

  // Exit:

  return result;
}

// CANONICAL MEMBERS


///
fiber_bundle::section_dof_map&
fiber_bundle::section_dof_map::
operator=(const section_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  poset_dof_map::operator=(xother);

  // Postconditions:

  // Exit

  return *this;
}


///
fiber_bundle::section_dof_map::
~section_dof_map()
{

  // Preconditions:


  // Body:
  
  // Postconditions:

  // Exit

  return;
}


///
bool
fiber_bundle::section_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && poset_dof_map::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    result = result &&
             (_host != 0 ? dynamic_cast<sec_rep_space*>(_host) != 0 : true);

    result = result &&
             (_schema != 0
              ? dynamic_cast<section_space_schema_member*>(_schema) != 0 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// MAP INTERFACE

 

///
fiber_bundle::sec_rep_space*
fiber_bundle::section_dof_map::
host() const
{
  sec_rep_space* result;

  // Preconditions:

  // Body:

  result = dynamic_cast<sec_rep_space*>(_host);

  // Postconditions:

  ensure((result == 0) == (poset_dof_map::host() == 0));

  // Exit

  return result;
}

///
fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_map::
schema()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    *(dynamic_cast<section_space_schema_member*>(_schema));

  // Postconditions:

  // Exit

  return result;
}

///
const fiber_bundle::section_space_schema_member&
fiber_bundle::section_dof_map::
schema() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result =
    *(dynamic_cast<section_space_schema_member*>(_schema));

  // Postconditions:

  // Exit

  return result;
}
 

// ===========================================================
//  NEW DOF ACCESS FACET
// ===========================================================

bool
fiber_bundle::section_dof_map::
dof_in_bounds(pod_index_type xdof_id, bool xis_table_dofs) const
{
  // Preconditions:


  // Body:

  // Essentially abstract; always true in this class.
  // Intended to be redefined in descendants.

  bool result = true;

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::section_dof_map::
dof_in_bounds(pod_index_type xdisc_id, pod_index_type xfiber_id, bool xis_table_dofs) const
{
  // Preconditions:


  // Body:

  // Essentially abstract; always true in this class.
  // Intended to be redefined in descendants.

  bool result = true;

  // Postconditions:


  // Exit:

  return result;
}
 
void
fiber_bundle::section_dof_map::
get_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id, false));
  
  
  // Body:

  is_abstract();
  
  // Postconditions:


  // Exit:

  return;
}

 
void
fiber_bundle::section_dof_map::
get_dof(const scoped_index& xdisc_id, 
	const scoped_index& xfiber_dof_id, 
	void* xdof, 
	size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("dof_in_bounds(xdisc_id, xfiber_dof_id, false)"));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id, false, false));
  
  
  // Body:

  pod_index_type ldisc_id =
    schema().discretization_id_space().pod(xdisc_id);
  pod_index_type lfiber_dof_id =
    schema().fiber_schema_id_space(false).pod(xfiber_dof_id);

  get_dof(ldisc_id, lfiber_dof_id, xdof, xdof_size);
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
put_dof(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(dof_in_bounds(xdisc_id, xfiber_dof_id, false));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id, false));
  
  // Body:

  is_abstract();
  
  // Postconditions:


  // Exit:

  return;
}

 
void
fiber_bundle::section_dof_map::
put_dof(const scoped_index& xdisc_id, 
	const scoped_index& xfiber_dof_id, 
	const void* xdof, 
	size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("dof_in_bounds(xdisc_id, xfiber_dof_id, false)"));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdisc_id, xfiber_dof_id, false, false));
  
  
  // Body:

  pod_index_type ldisc_id =
    schema().discretization_id_space().pod(xdisc_id);
  pod_index_type lfiber_dof_id =
    schema().fiber_schema_id_space(false).pod(xfiber_dof_id);

  put_dof(ldisc_id, lfiber_dof_id, xdof, xdof_size);
  
  // Postconditions:


  // Exit:

  return;
}


bool
fiber_bundle::section_dof_map::
fiber_in_bounds(pod_index_type xdisc_id, bool xis_table_dofs) const
{
  // Preconditions:


  // Body:

  // Essentially abstract; always true in this class.
  // Intended to be redefined in descendants.

  bool result = true;

  // Postconditions:


  // Exit:

  return result;
}
 
void
fiber_bundle::section_dof_map::
get_fiber(pod_index_type xdisc_id, void* xfiber, size_type xfiber_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(fiber_in_bounds(xdisc_id, false));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  
  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
get_fiber(const scoped_index& xdisc_id, void* xfiber, size_type xfiber_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("fiber_in_bounds(xdisc_id, false)"));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  // Body:

  pod_index_type ldisc_id = schema().discretization_id_space().pod(xdisc_id);
  
  get_fiber(ldisc_id, xfiber, xfiber_size);
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
put_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(fiber_in_bounds(xdisc_id, false));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  
  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
put_fiber(const scoped_index& xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("fiber_in_bounds(xdisc_id, false)"));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  // Body:

  pod_index_type ldisc_id = schema().discretization_id_space().pod(xdisc_id);
  
  put_fiber(ldisc_id, xfiber, xfiber_size);
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
force_fiber(pod_index_type xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  
  // Body:

  // Equivalent to put_fiber in this class;
  // intended to be redefined in descendants.

  put_fiber(xdisc_id, xfiber, xfiber_size);

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
force_fiber(const scoped_index& xdisc_id, const void* xfiber, size_type xfiber_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().discretization_id_space().contains(xdisc_id));
  require(unexecutable("xfiber points to buffer of size xfiber_size"));
  require(xfiber_size >= schema().fiber_size());
  
  // Body:

  pod_index_type ldisc_id = schema().discretization_id_space().pod(xdisc_id);
  
  force_fiber(ldisc_id, xfiber, xfiber_size);
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
get_component(pod_index_type xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));
  
  
  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
get_component(const scoped_index& xfiber_dof_id, void* xcomponent, size_type xcomponent_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id, false));
  
  // Body:

  pod_index_type lfiber_id =
    schema().fiber_schema_id_space(false).pod(xfiber_dof_id);
  
  get_component(lfiber_id, xcomponent, xcomponent_size);
  
  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
put_component(pod_index_type xfiber_dof_id, const void* xcomponent, size_type xcomponent_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id));
  
  
  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::section_dof_map::
put_component(const scoped_index& xfiber_dof_id, const void* xcomponent, size_type xcomponent_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().fiber_schema_id_space(false).contains(xfiber_dof_id));
  require(unexecutable("xcomponent points to buffer of size xcomponent_size"));
  require(xcomponent_size >= schema().component_size(xfiber_dof_id, false));
  
  // Body:

  pod_index_type lfiber_id =
    schema().fiber_schema_id_space(false).pod(xfiber_dof_id);
  
  put_component(lfiber_id, xcomponent, xcomponent_size);
  
  // Postconditions:


  // Exit:

  return;
}

// ===========================================================
//  END NEW DOF ACCESS FACET
// ===========================================================

///
bool
fiber_bundle::section_dof_map::
supports_xfr_opt() const
{
  /// @hack dof tuple transfer hack.

  return true;
}

// PROTECTED MEMBER FUNCTIONS

// CANONICAL MEMBERS

fiber_bundle::section_dof_map::
section_dof_map()
{

  // Preconditions:


  // Body:

  // No action required

  // Postconditions:

  // Exit

  return;
}


fiber_bundle::section_dof_map::
section_dof_map(const section_dof_map& xother)
    : poset_dof_map(xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}


// OTHER CONSTRUCTORS

///
fiber_bundle::section_dof_map::
section_dof_map(sec_rep_space* xhost, pod_index_type xbase_id, int xversion)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->base().geqv(xbase_id));
  require(xhost->has_version(xversion));

  // Body:

  _host = xhost;

  _index.invalidate();

  // Create a handle of the same actual type as the host schema and
  // attach it to the schema of the partial section.

  section_space_schema_member* lschema = xhost->schema().clone();
  lschema->attach_to_state(xhost->schema().host(),
                           xbase_id,
                           xhost->schema().fiber_schema_id());

  // Give the schema member a name if it does not already have one.

  if(lschema->name(true).empty())
  {
    lschema->put_standard_name(true, true);
  }

  // Make sure the version is unalised, so it can't magically change
  // after the dof storage has been allocated.

  lschema->put_version(xversion, true);

  // Save a reference to the schema.

  _schema = lschema;

  // This is a row dof map.

  _is_table_dof_map = false;

  _dof_ct       = _schema->dof_ct(_is_table_dof_map);
  _dof_tuple_ub = _schema->dof_tuple_ub(_is_table_dof_map);

  _ref_ct = 0;

  // Postconditions:

  ensure(is_initialized());
  ensure(host() == xhost);
  ensure(!index().is_valid());
  ensure(schema().base_space_id() == xbase_id);
  ensure(schema().fiber_schema_id() == xhost->schema().fiber_schema_id());
  ensure(dof_ct() == schema().row_dof_ct());
  ensure(dof_tuple_ub() == schema().row_dof_tuple_ub());
  ensure(ref_ct() == 0);
  ensure(version() == xhost->schema().unaliased_version(xversion));

  // Exit

  return;
}

