
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

// Implementation for class sec_rep_descriptor


#include "sec_rep_descriptor.h"

#include "assert_contract.h"
#include "eval_family.h"
#include "namespace_poset.h"
#include "poset.h"
#include "poset_dof_map.h"
#include "poset_state_handle.h"
#include "postorder_iterator.h"
#include "std_string.h"
#include "std_typeinfo.h"
#include "schema_descriptor.h"
#include "sec_rep_descriptor_poset.h"
#include "sec_rep_space.h"
#include "wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS


const sheaf::poset_path&
fiber_bundle::sec_rep_descriptor::
standard_schema_path()
{
  // Preconditions:

  // Body:

  static const poset_path result("sec_rep_descriptor_schema", "sec_rep_descriptor_schema");

  // Postconditions:

  ensure(result.full());

  // Exit:

  return result;
}


void
fiber_bundle::sec_rep_descriptor::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_path(), false));
  require(xns.member_poset(standard_schema_path(), false).state_is_read_write_accessible());
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string ldof_specs;

  ldof_specs =  "discretization_subposet_name C_STRING false";
  ldof_specs += " multivalued_subposet_name C_STRING false";
  ldof_specs += " evaluation_subposet_name C_STRING false";
  ldof_specs += " evaluator_family_name C_STRING false";
  ldof_specs += " URL C_STRING false";
  ldof_specs += " multiplicity INT false";

  /// @hack the following realy should be a bool,
  /// but we don't support bool as a primitive.

  ldof_specs += " eval_is_above_disc SIZE_TYPE false";

  // Table dofs:

  ldof_specs += " prototypes_path C_STRING true";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              poset_path(standard_schema_path().poset_name(), "bottom"),
                              ldof_specs,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit

  return;
}

const sheaf::poset_path&
fiber_bundle::sec_rep_descriptor::
standard_host_path()
{
  // cout << endl << "Entering sec_rep_descriptor::standard_host_path." << endl;

  // Preconditions:


  // Body:

  static const poset_path result("sec_rep_descriptors", "");

  // Postconditions:

  ensure(!result.empty());
  ensure(!result.full());
  
  // Exit:

  // cout << "Leaving sec_rep_descriptor::standard_host_path." << endl;
  return result;
}

fiber_bundle::sec_rep_descriptor::host_type&
fiber_bundle::sec_rep_descriptor::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xprototypes_path, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_rep_descriptor::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(!xprototypes_path.empty());
  require(xns.path_is_auto_read_accessible(xprototypes_path, xauto_access));

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xprototypes_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.prototypes().path(xauto_access) == xprototypes_path);

  // Exit:

  // cout << "Leaving sec_rep_descriptor::new_host." << endl;
  return result;
}

fiber_bundle::sec_rep_descriptor::host_type&
fiber_bundle::sec_rep_descriptor::
standard_host(namespace_type& xns, bool xauto_access)
{
  // cout << endl << "Entering sec_rep_descriptor::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xns.path_is_available<host_type>(standard_host_path(), xauto_access));  

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));

  // Body:

  poset_path lpath(standard_host_path());

  host_type* result_ptr;
  if(xns.contains_path(lpath, xauto_access))
  {
    result_ptr = &xns.member_poset<host_type>(lpath, xauto_access);
  }
  else
  {
    poset_path lprototypes_path(base_space_member::prototypes_poset_name());
    result_ptr = &new_host(xns, lpath, standard_schema_path(), lprototypes_path, xauto_access);
  }

  host_type& result = *result_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path());
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.prototypes().path(xauto_access).poset_name() == base_space_member::prototypes_poset_name());

  // Exit:

  // cout << "Leaving sec_rep_descriptor::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS




fiber_bundle::sec_rep_descriptor&
fiber_bundle::sec_rep_descriptor::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
  
  // Exit

  return *this;
}

fiber_bundle::sec_rep_descriptor&
fiber_bundle::sec_rep_descriptor::
operator=(const sec_rep_descriptor& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
  
  // Exit

  return *this;
}

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

// Default constructor
fiber_bundle::sec_rep_descriptor::
sec_rep_descriptor()
    : _evaluators(0)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


// Copy constructor
fiber_bundle::sec_rep_descriptor::
sec_rep_descriptor(const sec_rep_descriptor& xother, bool xnew_jem)
    : _evaluators(0)
{

  // Preconditions:

  require(xnew_jem ? xother.is_attached() : true);

  // Body:

  // Note: even though the code here is identical to that in
  // the copy constructors of all descendants of abstract_poset_member,
  // this can not just call its base class copy constructor
  // because it must invoke versions defined in this class of virtual attach_to_state
  // and virtual attach_handle_data_members (called from new_jem_state).

  if(xnew_jem)
  {
    new_jem_state(const_cast<sec_rep_descriptor*>(&xother), true, true);
  }
  else
  {
    attach_to_state(&xother);
  }

  // postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

fiber_bundle::sec_rep_descriptor*
fiber_bundle::sec_rep_descriptor::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_rep_descriptor *result = new sec_rep_descriptor();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// Destructor
fiber_bundle::sec_rep_descriptor::
~sec_rep_descriptor()
{
  // Preconditions:


  // Body:

  if(_evaluators != 0)
  {
    delete _evaluators;
  }

  // Postconditions:

  // Exit:

  return;
}


// Class invariant
bool
fiber_bundle::sec_rep_descriptor::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy total_poset_member class invariant

  result = result && total_poset_member::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Actual type of dof map is array_poset_dof_map.
    result = result && ( (state_is_read_accessible() && is_jim()) ? dynamic_cast<const array_poset_dof_map*>(&(total_poset_member::dof_map()))!=0 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::sec_rep_descriptor::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const sec_rep_descriptor*>(other) != 0;

  // Postconditions:

  return result;

}



// NEW HANDLE, NEW STATE CONSTRUCTORS

fiber_bundle::sec_rep_descriptor::
sec_rep_descriptor(poset* xhost,
                   const std::string& xdiscretization_subposet_name,
                   const std::string& xmultivalued_subposet_name,
                   const std::string& xevaluation_subposet_name,
                   const std::string& xevaluator_family_name,
                   const std::string& xurl,
                   int xmultiplicity,
                   bool xeval_is_above_disc,
                   bool xauto_access)
    : _evaluators(0)
{

  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost,
                xdiscretization_subposet_name,
                xmultivalued_subposet_name,
                xevaluation_subposet_name,
                xevaluator_family_name,
                xurl,
                xmultiplicity,
                xeval_is_above_disc,
                xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(same args)));

  // Exit:

  return;
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

fiber_bundle::sec_rep_descriptor::
sec_rep_descriptor(const poset* xhost, pod_index_type xindex)
    : _evaluators(0)
{

  // preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));

  // body:

  attach_to_state(xhost, xindex);

  // postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(host() == xhost);
  ensure(index() == xindex);

}

fiber_bundle::sec_rep_descriptor::
sec_rep_descriptor(const poset* xhost, const scoped_index& xindex)
    : _evaluators(0)
{

  // preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));

  // body:

  attach_to_state(xhost, xindex.hub_pod());

  // postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(host() == xhost);
  ensure(index() ==~ xindex);

}

// Creates a new handle attached to
// the member state with name xname in xhost.
fiber_bundle::sec_rep_descriptor::
sec_rep_descriptor(const poset* xhost, const std::string& xname)
    : _evaluators(0)
{

  // preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());
  require(xhost->contains_member(xname));

  // body:

  attach_to_state(xhost, xname);

  // postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(host() == xhost);
  ensure(name() == xname);

}


fiber_bundle::sec_rep_descriptor::
sec_rep_descriptor(const namespace_poset* xnamespace,
                   const poset_path& xpath,
                   bool xauto_access)
    : _evaluators(0)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::sec_rep_descriptor::
sec_rep_descriptor(const namespace_poset* xnamespace,
                   pod_index_type xposet_id,
                   pod_index_type xmember_id,
                   bool xauto_access)
    : _evaluators(0)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xposet_id, xmember_id, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::sec_rep_descriptor::
sec_rep_descriptor(const namespace_poset* xnamespace,
                   const scoped_index& xposet_id,
                   const scoped_index& xmember_id,
                   bool xauto_access)
    : _evaluators(0)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace,
		  xposet_id.hub_pod(),
		  xmember_id.hub_pod(),
		  xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

void
fiber_bundle::sec_rep_descriptor::
new_jim_state(poset_dof_map* xdof_map, bool xcopy_dof_map, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jim_state(host(), xdof_map, xcopy_dof_map, xauto_access)));

  // Body:

  new_jim_state(host(), xdof_map, xcopy_dof_map, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(host(), xdof_map, xcopy_dof_map, xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::sec_rep_descriptor::
new_jim_state(poset_state_handle* xhost,
              poset_dof_map* xdof_map,
              bool xcopy_dof_map,
              bool xauto_access)
{
  // Preconditions:

  require(precondition_of(total_poset_member::new_jim_state(xhost, xdof_map, xcopy_dof_map, false)));

  // Body:

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode();

    if(xdof_map != 0)
      xdof_map->host()->get_read_access();
  }

  poset_dof_map* ldof_map;
  bool lcopy_dof_map;

  if(xdof_map == 0)
  {
    // Make sure the dofs are properly initialized.
    // Create and initialize the dof tuple to default values.

    string lmt_str;
    row_dof_tuple ltuple(lmt_str, lmt_str, lmt_str, lmt_str, lmt_str, 0, 0);

    // Create the dof map.

    ldof_map = new array_poset_dof_map(xhost, false);

    // Copy the dof tuple into the dof map.

    ldof_map->put_dof_tuple(&ltuple, sizeof(ltuple));

    lcopy_dof_map = false;
  }
  else
  {
    ldof_map = xdof_map;
    lcopy_dof_map = xcopy_dof_map;
  }

  total_poset_member::new_jim_state(xhost, ldof_map, lcopy_dof_map, false);

  // Postconditions:

  ensure(postcondition_of(total_poset_member::new_jim_state(xhost, xdof_map, xcopy_dof_map, false)));
  ensure(invariant());
  ensure(xdof_map == 0 ? discretization_subposet_name().empty() : true);
  ensure(xdof_map == 0 ? multivalued_subposet_name().empty() : true);
  ensure(xdof_map == 0 ? evaluation_subposet_name().empty() : true);
  ensure(xdof_map == 0 ? evaluator_family_name().empty() : true);
  ensure(xdof_map == 0 ? url().empty() : true);
  ensure(xdof_map == 0 ? multiplicity() == 0 : true);
  ensure(xdof_map == 0 ? !eval_is_above_disc() : true);

  // Clean-up auto access.

  if(xauto_access)
  {
    xhost->end_jim_edit_mode();

    if(xdof_map != 0)
      xdof_map->host()->release_access();
  }

  // Exit:

  return;
}

void
fiber_bundle::sec_rep_descriptor::
new_jim_state(poset* xhost,
              const std::string& xdiscretization_subposet_name,
              const std::string& xmultivalued_subposet_name,
              const std::string& xevaluation_subposet_name,
              const std::string& xevaluator_family_name,
              const std::string& xurl,
              int xmultiplicity,
              bool xeval_is_above_disc,
              bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);
  require(xauto_access || xhost->in_jim_edit_mode());
  require(xmultiplicity >= 0);

  // Body:

  if(xauto_access)
    xhost->begin_jim_edit_mode();

  // Create and initialize the dof tuple.

  row_dof_tuple ltuple(xdiscretization_subposet_name,
                       xmultivalued_subposet_name,
                       xevaluation_subposet_name,
                       xevaluator_family_name,
                       xurl,
                       xmultiplicity,
                       xeval_is_above_disc ? 1 : 0);

  // Create the dof map.

  array_poset_dof_map* lmap = new array_poset_dof_map(xhost, false);

  // Copy the dof tuple into the dof map.

  lmap->put_dof_tuple(&ltuple, sizeof(ltuple));

  // Create the new state.

  new_jim_state(xhost, lmap, false, false);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(host() == xhost);
  ensure(unexecutable(host()->member_ct() == old host->member_ct() + 1));
  ensure(discretization_subposet_name() == xdiscretization_subposet_name);
  ensure(multivalued_subposet_name() == xmultivalued_subposet_name);
  ensure(evaluation_subposet_name() == xevaluation_subposet_name);
  ensure(evaluator_family_name() == xevaluator_family_name);
  ensure(url() == xurl);
  ensure(multiplicity() == xmultiplicity);
  ensure(eval_is_above_disc() == xeval_is_above_disc);

  if(xauto_access)
    xhost->end_jim_edit_mode();

  // Exit:

  return;
}

 

sheaf::array_poset_dof_map&
fiber_bundle::sec_rep_descriptor::
dof_map(bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  // Invariant ensures the cast will succeed.

  array_poset_dof_map& result =
    dynamic_cast<array_poset_dof_map&>(total_poset_member::dof_map());

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::array_poset_dof_map&
fiber_bundle::sec_rep_descriptor::
dof_map(bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  // Invariant ensures the cast will succeed.

  const array_poset_dof_map& result =
    dynamic_cast<const array_poset_dof_map&>(total_poset_member::dof_map());

  // Postconditions:

  // Exit:

  return result;
}

 

bool
fiber_bundle::sec_rep_descriptor::
dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  result = dynamic_cast<const array_poset_dof_map*>(xdof_map) != 0;

  // Postconditions:

  ensure(result == (dynamic_cast<const array_poset_dof_map*>(xdof_map) != 0));

  // Exit

  return result;
}

std::string
fiber_bundle::sec_rep_descriptor::
discretization_subposet_name() const
{
  string result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = row_dof_tuple_ptr()->discretization_subposet_name;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::sec_rep_descriptor::
put_discretization_subposet_name(const std::string& xname)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  delete [] row_dof_tuple_ptr()->discretization_subposet_name;
  row_dof_tuple::copy_string_dof(row_dof_tuple_ptr()->discretization_subposet_name, xname);

  // Postconditions:

  ensure(discretization_subposet_name() == xname);

  // Exit

  return;
}


std::string
fiber_bundle::sec_rep_descriptor::
multivalued_subposet_name() const
{
  string result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = row_dof_tuple_ptr()->multivalued_subposet_name;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::sec_rep_descriptor::
put_multivalued_subposet_name(const std::string& xname)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  delete [] row_dof_tuple_ptr()->multivalued_subposet_name;
  row_dof_tuple::copy_string_dof(row_dof_tuple_ptr()->multivalued_subposet_name, xname);

  // Postconditions:

  ensure(multivalued_subposet_name() == xname);

  // Exit

  return;
}


std::string
fiber_bundle::sec_rep_descriptor::
evaluation_subposet_name() const
{
  string result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = row_dof_tuple_ptr()->evaluation_subposet_name;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::sec_rep_descriptor::
put_evaluation_subposet_name(const std::string& xname)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  delete [] row_dof_tuple_ptr()->evaluation_subposet_name;
  row_dof_tuple::copy_string_dof(row_dof_tuple_ptr()->evaluation_subposet_name, xname);

  // Postconditions:

  ensure(evaluation_subposet_name() == xname);

  // Exit

  return;
}

std::string
fiber_bundle::sec_rep_descriptor::
evaluator_family_name() const
{
  string result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = row_dof_tuple_ptr()->evaluator_family_name;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::sec_rep_descriptor::
put_evaluator_family_name(const std::string& xname)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  delete [] row_dof_tuple_ptr()->evaluator_family_name;
  row_dof_tuple::copy_string_dof(row_dof_tuple_ptr()->evaluator_family_name, xname);

  // Postconditions:

  ensure(evaluator_family_name() == xname);

  // Exit

  return;
}

std::string
fiber_bundle::sec_rep_descriptor::
url() const
{
  string result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = row_dof_tuple_ptr()->url;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::sec_rep_descriptor::
put_url(const std::string& xurl)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  delete [] row_dof_tuple_ptr()->url;
  row_dof_tuple::copy_string_dof(row_dof_tuple_ptr()->url, xurl);

  // Postconditions:

  ensure(url() == xurl);

  // Exit

  return;
}

int
fiber_bundle::sec_rep_descriptor::
multiplicity() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = row_dof_tuple_ptr()->multiplicity;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::sec_rep_descriptor::
put_multiplicity(int xmultiplicity)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  row_dof_tuple_ptr()->multiplicity = xmultiplicity;

  // Postconditions:

  ensure(multiplicity() == xmultiplicity);

  // Exit

  return;
}

bool
fiber_bundle::sec_rep_descriptor::
eval_is_above_disc() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = row_dof_tuple_ptr()->eval_is_above_disc;

  // Postconditions:


  // Exit:

  return result;
}

void
fiber_bundle::sec_rep_descriptor::
put_eval_is_above_disc(bool xvalue)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  row_dof_tuple_ptr()->eval_is_above_disc = xvalue ? 1 : 0;

  // Postconditions:

  ensure(eval_is_above_disc() == xvalue);

  // Exit:

  return;
}

fiber_bundle::eval_family*
fiber_bundle::sec_rep_descriptor::
evaluators() const
{
  return _evaluators;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::sec_rep_descriptor::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  string lnew_name = evaluator_family_name();

  if(_evaluators != 0)
  {
    delete _evaluators;
    _evaluators = 0;
  }

  assertion(_evaluators == 0);
  
  if(!lnew_name.empty())
  {
    // Handle needs an eval family; create it.

    _evaluators = eval_family::new_family(lnew_name, *name_space());
  }
  

  // Postconditions:

  ensure(!is_restricted());
  ensure(evaluator_family_name().empty() == (evaluators() == 0));
  

  // Exit:

  return;
}


fiber_bundle::sec_rep_descriptor::row_dof_tuple::
row_dof_tuple(const std::string& xdiscretization_subposet_name,
	      const std::string& xmultivalued_subposet_name,
	      const std::string& xevaluation_subposet_name,
	      const std::string& xevaluator_family_name,
	      const std::string& xurl,
	      int xmultiplicity,
	      size_type xeval_is_above_disc)
{
  // Preconditions:

  // Body:

  copy_string_dof(discretization_subposet_name, xdiscretization_subposet_name);
  copy_string_dof(multivalued_subposet_name, xmultivalued_subposet_name);
  copy_string_dof(evaluation_subposet_name, xevaluation_subposet_name);
  copy_string_dof(evaluator_family_name, xevaluator_family_name);
  copy_string_dof(url, xurl);
  multiplicity = xmultiplicity;
  eval_is_above_disc = xeval_is_above_disc;

  // Postconditions:

  ensure(discretization_subposet_name == xdiscretization_subposet_name);
  ensure(multivalued_subposet_name == xmultivalued_subposet_name);
  ensure(multiplicity == xmultiplicity);
  ensure(evaluation_subposet_name == xevaluation_subposet_name);
  ensure(evaluator_family_name == xevaluator_family_name);
  ensure(url == xurl);
  ensure(eval_is_above_disc == xeval_is_above_disc);

  // Exit

  return;
}

void
fiber_bundle::sec_rep_descriptor::row_dof_tuple::
copy_string_dof(char*& xdof, const std::string& xdof_value)
{
  // Preconditions:

  // Body:

  xdof = new char[xdof_value.size()+1];
  strcpy(xdof, xdof_value.c_str());

  // Postconditions:

  ensure(strcmp(xdof, xdof_value.c_str()) == 0);

  // Exit

  return;
}

