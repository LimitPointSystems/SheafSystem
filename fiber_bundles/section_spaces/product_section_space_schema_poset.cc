
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
/// Implementation for class product_section_space_schema_poset.

#include "product_section_space_schema_poset.h"

#include "abstract_poset_member.impl.h"
#include "arg_list.h"
#include "array_poset_dof_map.h"
#include "ij_product_structure.h"
#include "index_iterator.h"
#include "list_cover_set.h"
#include "error_message.h"
#include "index_space_iterator.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "pod_types.h"
#include "poset_handle_factory.h"
#include "poset_member_iterator.h"
#include "poset_state.h"
#include "product_section_space_schema_crg_range.h"
#include "product_section_space_schema_member.impl.h"
#include "schema_descriptor.h"
#include "section_space_schema_table_dofs_type.h"
#include "section_space_schema_table_dof_crg_range.h"
#include "std_limits.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// PRODUCT_SECTION_SPACE_SCHEMA_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::arg_list
fiber_bundle::product_section_space_schema_poset::
make_arg_list(const poset_path& xrep_path, 
	      const poset_path& xbase_space_path, 
	      const poset_path& xfiber_space_path)
{
  // Preconditions:


  // Body:

  sheaf::arg_list result;

  result << "rep_path" << xrep_path
	 << "base_space_path" << xbase_space_path 
	 << "fiber_space_path" << xfiber_space_path;
  
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "product_section_space_schema_poset::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("rep_path") == xrep_path);
  ensure(result.value("base_space_path") == xbase_space_path);
  ensure(result.value("fiber_space_path") == xfiber_space_path);
  
  // Exit:

  return result;
}

fiber_bundle::product_section_space_schema_poset::
product_section_space_schema_poset(namespace_poset& xns,
				   const string& xname,
				   const arg_list& xargs,
				   const poset_path& xschema_path,
				   bool xauto_access)

    : section_space_schema_poset(new product_section_space_schema_member,
				   new product_section_space_schema_member)
{

  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  // Make the new state.

  new_state(xns, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));
}

// PROTECTED FUNCTIONS

fiber_bundle::product_section_space_schema_poset::
product_section_space_schema_poset()
    : section_space_schema_poset(new product_section_space_schema_member,
				 new product_section_space_schema_member)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(!is_attached());
  ensure(!top().is_attached());
  ensure(!bottom().is_attached());
}

fiber_bundle::product_section_space_schema_poset::
product_section_space_schema_poset(const product_section_space_schema_poset& xother)
    : section_space_schema_poset(new product_section_space_schema_member,
				 new product_section_space_schema_member)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(is_same_state(&xother));
}

fiber_bundle::product_section_space_schema_poset::
~product_section_space_schema_poset()
{
  // Preconditions:

  // Body:

  // Nothing to do; base class does it all.
  // Currently, this routine exists mostly for the precondition,
  // which is the same as poset_state_handle::~poset_state_handle.
  // With this precondition in place, the source of a precondition
  // violation will be clearer to the client.

  // Postconditions:

  // Exit

  return;
}

void
fiber_bundle::product_section_space_schema_poset::
initialize_arg_list(const namespace_poset& xns, 
		    const string& xname,
		    arg_list& xargs, 
		    const poset_path& xschema_path,
		    bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));

  require(!xschema_path.empty());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(xschema_path.conforms_to(xns, standard_schema_path(), xauto_access));

  require(xns.arg_is_auto_read_accessible("rep_path", xargs, xauto_access));
  require(xns.arg_is_auto_read_accessible("base_space_path", xargs, xauto_access));
  require(xns.arg_is_auto_read_accessible("fiber_space_path", xargs, xauto_access));
  
  // Body:

  // Nothing to do.  

  // Done.
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "product_section_space_schema_poset::initialize_arg_list:xargs: " << endl 
       << xargs << endl;
#endif

  // Postconditions:
  
  // Exit:

  return;
}

const sheaf::ij_product_structure&
fiber_bundle::product_section_space_schema_poset::
product_structure() const
{
  // Preconditions:

  // Body:

  const ij_product_structure& result = _product_range->product_structure();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::product_section_space_schema_poset::
initialize_row_dof_subposet()
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().is_attached());
  require(fiber_schema().is_attached());

  // Body:

  // Create the row dof subposet.

  row_dof_subposet().new_state(this);
  row_dof_subposet().put_name(schema_poset_member::row_dof_subposet_name("top"), true, false);

  index_space_iterator& ldisc_itr =
    discretization().id_space().get_iterator();
  index_space_iterator& lfiber_itr =
    fiber_schema().row_dof_subposet().id_space().get_iterator();

  pod_index_type lid;

  while(!ldisc_itr.is_done())
  {
    lfiber_itr.reset();

    while(lfiber_itr.is_done())
    {
      ordinal(ldisc_itr.hub_pod(), lfiber_itr.hub_pod(), lid);

      row_dof_subposet().insert_member(lid);

      lfiber_itr.next();
    }

    ldisc_itr.next();
  }

  fiber_schema().row_dof_subposet().id_space().release_iterator(lfiber_itr);
  discretization().id_space().release_iterator(ldisc_itr);

  // Postconditions:

  ensure(row_dof_subposet().is_attached());

  // Exit:

  return;
}

fiber_bundle::section_space_schema_table_dof_crg_range&
fiber_bundle::product_section_space_schema_poset::
table_dof_range()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *_table_dof_range;
}

void
fiber_bundle::product_section_space_schema_poset::
put_table_dof_range(section_space_schema_table_dof_crg_range& xtable_dof_range)
{
  // Preconditions:

  // Body:

  _table_dof_range = &xtable_dof_range;

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::product_section_space_schema_crg_range&
fiber_bundle::product_section_space_schema_poset::
product_range()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return *_product_range;
}

void
fiber_bundle::product_section_space_schema_poset::
put_product_range(product_section_space_schema_crg_range& xproduct_range)
{
  // Preconditions:

  // Body:

  _product_range = &xproduct_range;

  // Postconditions:

  // Exit:

  return;
}

bool
fiber_bundle::product_section_space_schema_poset::
make_prototype()
{
  // Preconditions:

  // Body:

  poset_type ltype = PRODUCT_SECTION_SPACE_SCHEMA_POSET_ID;

  product_section_space_schema_poset* lproto =
    new product_section_space_schema_poset;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return true;
}

// PRIVATE FUNCTIONS


// ===========================================================
// SECTION_SPACE_SCHEMA_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

const sheaf::poset_path&
fiber_bundle::product_section_space_schema_poset::
standard_schema_path()
{
  // Preconditions:

  // Body:

  static const poset_path
  result(standard_schema_poset_name(), "product_section_space_schema_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

void
fiber_bundle::product_section_space_schema_poset::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(xns.member_poset(standard_schema_poset_name(), false)->state_is_read_write_accessible());
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  // This class doesn't add any dofs.

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              section_space_schema_poset::standard_schema_path(),
                              "",
                              false,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit

  return;
}

void
fiber_bundle::product_section_space_schema_poset::
tuple(pod_index_type xindex,
      pod_index_type& xbase_space_id,
      pod_index_type& xfiber_schema_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_homogeneous(xindex));

  // Body:

  if(_product_range->contains_member(xindex))
  {
    _product_range->tuple(xindex, xbase_space_id, xfiber_schema_id);
  }
  else
  {
    _table_dof_range->tuple(xindex, xbase_space_id, xfiber_schema_id);
  }

  // Postconditions:

  ensure(contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Exit:

  return;
}

void
fiber_bundle::product_section_space_schema_poset::
ordinal(pod_index_type xbase_space_id,
	pod_index_type xfiber_schema_id,
	pod_index_type& xindex) const
{
  // Preconditions:

  require(contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Body:

  if(_product_range->contains_member(xbase_space_id, xfiber_schema_id))
  {
    _product_range->ordinal(xbase_space_id, xfiber_schema_id, xindex);
  }
  else
  {
    _table_dof_range->ordinal(xbase_space_id, xfiber_schema_id, xindex);
  }

  // Postconditions:

  ensure(is_homogeneous(xindex));

  // Exit:

  return;
}

bool
fiber_bundle::product_section_space_schema_poset::
is_homogeneous(pod_index_type xindex) const
{
  // Preconditions:

  // Body:

  bool result =
    _product_range->contains_member(xindex) ||
    _table_dof_range->contains_member(xindex);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::product_section_space_schema_poset::
contains_range_member(pod_index_type xbase_space_id,
		      pod_index_type xfiber_schema_id,
		      bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  bool result =
    _product_range->contains_member(xbase_space_id, xfiber_schema_id) ||
    _table_dof_range->contains_member(xbase_space_id, xfiber_schema_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::product_section_space_schema_poset::
update_hub_id_space(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  _product_range->update_gathered_id_spaces();

  size_type lbase_space_ub = base_space().gathered_member_id_space(false).ct();
  size_type lfiber_schema_ub = fiber_schema().gathered_member_id_space(false).ct();

  extend_last_member_term(lbase_space_ub * lfiber_schema_ub, false);

  _product_range->update_product_structure();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset_type
fiber_bundle::product_section_space_schema_poset::
type_id() const
{
  return PRODUCT_SECTION_SPACE_SCHEMA_POSET_ID;
}

const char*
fiber_bundle::product_section_space_schema_poset::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "product_section_space_schema_poset";

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

void
fiber_bundle::product_section_space_schema_poset::
new_state(namespace_poset& xns,
          const string& xname,
	  const arg_list& xargs,
	  const poset_path& xschema_path,
          bool xauto_access)
{

  // Preconditions:

  require(xauto_access || xns.in_jim_edit_mode());

  require(poset_path::is_valid_name(xname));
  require(!xns.contains_poset(xname, xauto_access));

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.
  /// @hack unexecutable because may not have access.

  require(unexecutable(xname != xns.name()));

  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(xschema_path.conforms_to(xns, standard_schema_path(), xauto_access));

  require(xargs.conforms_to(xns, xschema_path, true, xauto_access));
  
  require(xns.arg_is_auto_read_accessible("rep_path", xargs, xauto_access));
  require(xns.arg_is_auto_read_accessible("base_space_path", xargs, xauto_access));
  require(xns.arg_is_auto_read_accessible("fiber_space_path", xargs, xauto_access));  

  require(rep_is_valid(xns, xargs, xauto_access));

  // Body:

  if(xauto_access)
  {
    xns.get_read_write_access();
  }

  // Set any class specific args in arg list.

  arg_list largs(xargs);
  initialize_arg_list(xns, xname, largs, xschema_path, xauto_access);

  // Disable invariant checking in
  // member functions until construction finished.

  disable_invariant_check();

  // Get a temporary handle to the schema.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);
  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Create the poset state object;
  // allocates the data structures but does not (fully) initialize them.

  _state = new poset_state(&lschema, PRODUCT_SECTION_SPACE_SCHEMA_POSET_ID);

  // Get write access;
  // handle data members aren't attached yet, 
  // so use psh version.

  poset_state_handle::get_read_write_access();

  // Initialize the table dofs ("class variables").
  // Do this before initializing the row structure so the subposet
  // and member initialization routines can use the table dofs if needed.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof_tuple(xargs);
  initialize_table_dof_tuple(lmap);

  // Initialize any additional handle data members
  // that may depend on table dofs.

  initialize_handle_data_members(xns);

  // Release and regain access;
  // will get access to handle data members.

  poset_state_handle::release_access();
  get_read_write_access();

  // Initialize the row structure.

  initialize_standard_subposets(xname);
  initialize_standard_members();

  // Initialize the namespace features.

  initialize_namespace(xns, xname);

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // Initialize the table dof subposet.

  initialize_table_dof_subposet();

  // Initialize the row dof subposet.

  initialize_row_dof_subposet();

  // Cleanup temporary schema handle.

  if(xauto_access)
  {
    lschema.release_access();
  }
  lschema.detach_from_state();

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(schema().path() == xschema_path);
  ensure(name() == xname);
  ensure(!in_jim_edit_mode());
  /// @todo Review.
  //ensure(has_standard_row_dof_tuple_ct());
  //ensure(has_standard_subposet_ct());
  ensure(member_id_spaces(false).has_only_standard_id_spaces());
  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  ensure(db() >= 0);
  ensure(fiber_schema().is_attached());
  ensure(df() > 0);
  ensure(fiber_space().is_attached());

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  if(xauto_access)
  {
    xns.release_access();
  }

  // Exit:

  return;
}

void
fiber_bundle::product_section_space_schema_poset::
new_state(const schema_poset_member& xschema,
          array_poset_dof_map& xdof_map)
{

  // Preconditions:

  require(name_space() != 0);
  require(name_space()->state_is_read_accessible());

  require(xschema.state_is_read_accessible());
  require(is_external());
  require(schema_is_ancestor_of(&xschema));
  require(xschema.host()->name_space()->is_same_state(name_space()));
  /// @todo Remove.
//   require(xschema.is_schematized(false));

  /// @issue the following is unexecutable because dof maps don't have
  /// a schema until attached to a host; requires covariant schema feature to implement.

  /// @todo fix dof maps schema feature and make this precondition executable.

  require(unexecutable(xschema.is_same_state(xdof_map.schema())));

  require(unexecutable("rep in xdof_map exists"));
  require(unexecutable("rep in xdof_map is read accessible"));

  require(unexecutable("base space in xdof_map exists"));
  require(unexecutable("base space in xdof_map is read accessible"));

  require(unexecutable("fiber space in xdof_map exists"));
  require(unexecutable("fiber space in xdof_map is read accessible"));

  require(unexecutable("rep in xdof_map is valid for base and fiber in xdof_map"));


  // Body:

  // Disable invariant checking in
  // member functions until construction finished.

  disable_invariant_check();

  // Create the poset state object;
  // allocates the data structures but does not (fully) initialize them.

  _state = new poset_state(&xschema, PRODUCT_SECTION_SPACE_SCHEMA_POSET_ID);

  // Get write access;
  // handle data members aren't attached yet, 
  // so use psh version.

  poset_state_handle::get_read_write_access();

  // Initialize the table dofs.
  // Must be called before initialize_standard_members
  // because precondition contains_member in put_member_dof_tuple_id
  // called from new_member indirectly needs table dofs.

  initialize_table_dof_tuple(&xdof_map);

  // Initialize any additional handle data members
  // that may depend on table dofs.

  initialize_handle_data_members(*name_space());

  // Release and regain access;
  // will get access to handle data members.

  poset_state_handle::release_access();
  get_read_write_access();

  // Initialize the row structure.

  initialize_standard_subposets(name_space()->member_name(index()));
  initialize_standard_members();

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // Initialize the table dof subposet.

  initialize_table_dof_subposet();

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!in_jim_edit_mode());
  ensure(schema().is_same_state(&xschema));
//   ensure(has_standard_row_dof_tuple_ct());
//  ensure(has_standard_subposet_ct());
  ensure(member_id_spaces(false).has_only_standard_id_spaces());
  ensure(&(table_dof_map()) == &xdof_map);
  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  ensure(fiber_schema().is_attached());
  ensure(fiber_space().is_attached());

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  // Exit:

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// SCHEMA FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


/// @todo Remove.
// // ===========================================================
// // SCHEMATIZATION FACET
// // ===========================================================

// // PUBLIC FUNCTIONS

// bool
// fiber_bundle::product_section_space_schema_poset::
// is_schematized(bool xauto_access) const
// {
//   bool result;

//   // Preconditions:

//   require(xauto_access || state_is_read_accessible());

//   // Body:

//   if(xauto_access)
//   {
//     get_read_access();
//   }

//   /// @issue What is the correct schematization test.  The table dof subposet
//   ///        is constructed but the row dof subposet is not.

//   result = fiber_schema().is_schematized(false);

//   if(xauto_access)
//   {
//     release_access();
//   }

//   // Postconditions:

//   /// @todo make the following executable.

//   ensure(unexecutable(result == top member has been schematized));

//   // Exit

//   return result;
// }

// bool
// fiber_bundle::product_section_space_schema_poset::
// is_schematized(pod_index_type xindex, bool xauto_access) const
// {
//   bool result;

//   // Preconditions:

//   require(xauto_access || state_is_read_accessible());

//   // Body:

//   if(xauto_access)
//   {
//     get_read_access();
//   }

//   pod_index_type lbase_id, lfiber_id;
//   _range->tuple(xindex, lbase_id, lfiber_id);

//   result = fiber_schema().is_schematized(lfiber_id, false);

//   if(xauto_access)
//   {
//     release_access();
//   }

//   // Postconditions:

//   // This routine is a primitive query and hence its postcondition
//   // is not expressible in terms of other queries. In particular,
//   // the result is only equivalent to the existence of dof subposets
//   // in some descendants.

//   ensure(unexecutable(result == member with index xindex has been prepared for use as a schema));

//   // Exit

//   return result;
// }

// void
// fiber_bundle::product_section_space_schema_poset::
// schematize(subposet* xtable_dof_subposet,
//            subposet* xrow_dof_subposet,
//            bool xall_members)
// {
//   // Preconditions:

//   require(state_is_read_write_accessible());
//   require(dynamic_cast<primitives_poset_schema*>(schema().host()) != 0);
//   // can only schematize posets which have same schema as primitives_poset
//   require(xtable_dof_subposet != 0);
//   require(includes_subposet(xtable_dof_subposet));
//   require(xrow_dof_subposet != 0);
//   require(includes_subposet(xrow_dof_subposet));

//   // Body:

//   not_implemented();

//   /// @error this poset is immutable and does not support this operation

//   // Postconditions:

//   ensure(is_schematized(false));

//   // Exit

//   return;
// }

// // PROTECTED FUNCTIONS

// // PRIVATE FUNCTIONS


// ===========================================================
// MEMBERSHIP FACET
// ===========================================================

// PUBLIC FUNCTIONS

fiber_bundle::product_section_space_schema_member&
fiber_bundle::product_section_space_schema_poset::
top()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<product_section_space_schema_member*>(_top));
}

const fiber_bundle::product_section_space_schema_member&
fiber_bundle::product_section_space_schema_poset::
top() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<const product_section_space_schema_member*>(_top));
}

fiber_bundle::product_section_space_schema_member&
fiber_bundle::product_section_space_schema_poset::
bottom()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<product_section_space_schema_member*>(_bottom));
}

const fiber_bundle::product_section_space_schema_member&
fiber_bundle::product_section_space_schema_poset::
bottom() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<const product_section_space_schema_member*>(_bottom));
}

bool
fiber_bundle::product_section_space_schema_poset::
is_jim(pod_index_type xindex, bool xin_current_version) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  bool result;

  if(is_homogeneous(xindex))
  {
    // xindex is homogeneous, factor members and check to see if it is a jim.

    pod_index_type lbase_space_id, lfiber_schema_id;

    tuple(xindex, lbase_space_id, lfiber_schema_id);

    if(lbase_space_id == BOTTOM_INDEX)
    {
      result = fiber_schema().table_dof_subposet().contains_member(lfiber_schema_id);
    }
    else
    {
      result =
	base_space().is_jim(lbase_space_id) &&
	fiber_schema().is_jim(lfiber_schema_id);
    }
  }
  else
  {
    // xindex is not homogeneous, it is not a jim.

    result = false;
  }    
  
  // Postconditions:

  // Exit

  return result;
}

string
fiber_bundle::product_section_space_schema_poset::
member_name(pod_index_type xindex, bool xauto_access) const
{
  string result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = poset_state_handle::member_name(xindex, false);
  if(result.empty())
  {
    // Member does not have a client assigned name;
    // try to construct a default name from factor names.

    if(is_homogeneous(xindex))
    {
      // Member can be factored.

      pod_index_type lbase_id, lfiber_id;
      tuple(xindex, lbase_id, lfiber_id);

      string lfiber_name = fiber_schema().member_name(lfiber_id);

      if( (lbase_id == BOTTOM_INDEX) &&
	  (fiber_schema().table_dof_subposet().contains_member(lfiber_id)) )
      {
	// This is a table dof member;
	// name is name of fiber factor.

	result = lfiber_name;
      }
      else
      {
	// This is not a table dof member;
	// construct name from both base and fiber factor.

	string lbase_name = base_space().member_name(lbase_id);

	if(!lbase_name.empty() || !lfiber_name.empty())
	{
	  result = lbase_name + '_' + lfiber_name;
	}
	else
	{
	  // Both base and fiber names are empty; do nothing.
	}
      }
    }
    else
    {
      // Index can't be factored; do nothing.
    }
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

void
fiber_bundle::product_section_space_schema_poset::
initialize_standard_members()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  // Enter jim edit mode.

  begin_jim_edit_mode(false);

  // Allocate members.

  new_member(false); // bottom.
  new_member(false); // top.

  // Allocate the member ranges.

  size_type lrange_size;
  pod_index_type lrange_id;
  block<scoped_index> ldof_tuple_ids; // Dof tuple ids are empty

  // Private data for the ranges have no explicit member or implicit data..

  block<pod_index_type> lprivate_data;
  lprivate_data.reserve(2);
  lprivate_data.set_ct(2);
  lprivate_data[0] = 0; // No explicit upper covers
  lprivate_data[1] = 0; // No explicit lower covers

  // Allocate the table dof range.

  section_space_schema_table_dof_crg_range::get_size(*this, lrange_size);
  lrange_id = poset_state_handle::new_member_range("section_space_schema_table_dof_crg_range", lrange_size);
  _table_dof_range = reinterpret_cast<section_space_schema_table_dof_crg_range*>(crg().implicit_member(lrange_id));

  // Allocate the product range.

  product_section_space_schema_crg_range::get_size(*this, lrange_size);
  lrange_id = poset_state_handle::new_member_range("product_section_space_schema_crg_range", lrange_size);
  _product_range = reinterpret_cast<product_section_space_schema_crg_range*>(crg().implicit_member(lrange_id));

  // Attach bottom member; becomes index 0.
  // No dof tuple allocated.

  bottom().attach_to_state(this, BOTTOM_INDEX);
  bottom().put_name("bottom", true, false);

  // Attach top member; becomes index 1.
  // No dof tuple allocated.

  top().attach_to_state(this, TOP_INDEX);
  top().put_name("top", true, false);

  // Finialize the table dof range.

  _table_dof_range->initialize_dof_tuple_ids(ldof_tuple_ids);
  _table_dof_range->put_private_data(lprivate_data);
  _table_dof_range->finalize(*this);

  // Finialize the product range.

  _product_range->initialize_dof_tuple_ids(ldof_tuple_ids);
  _product_range->put_private_data(lprivate_data);
  _product_range->finalize(*this);

  // Create a cover link from the top to base_space.top(), fiber_schema.top().

  pod_index_type link_id;
  _product_range->ordinal(TOP_INDEX, TOP_INDEX, link_id);
  new_link(TOP_INDEX, link_id);

  // All the members and row dof tuples are standard.

  put_standard_member_ct(member_ct());
  put_standard_row_dof_tuple_ct(row_dof_tuple_ct());

  end_jim_edit_mode(false, false);

  // Now the cover relation graph invariant is satisfied

  crg().enable_invariant_check();

  assertion(crg().invariant());

  // Postconditions:

  ensure(bottom().is_attached() && (bottom().index() == BOTTOM_INDEX));
  ensure(top().is_attached() && (top().index() == TOP_INDEX));
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC FUNCTIONS

/// @todo Remove.
// bool
// fiber_bundle::product_section_space_schema_poset::
// is_valid_int_id(pod_index_type xint_id,
// 		const string& xid_space_name,
// 		bool xauto_access) const
// {
//   // Preconditions:

//   require(xauto_access || state_is_read_accessible());

//   if(xauto_access)
//   {
//     get_read_access();
//   }

//   // Body:

//   bool result = true;

//   if(xint_id >= standard_member_ct())
//   {
//     result = base_space().member_id_spaces(false).contains(xid_space_name);
//     if(result)
//     {
//       pod_index_type lbase_id, lfiber_id;
//       tuple(xint_id, lbase_id, lfiber_id);

//       result = base_space().member_id_spaces(false).contains_hub(xid_space_name,
// 								 lbase_id);
//     }
//   }

//   if(xauto_access)
//   {
//     release_access();
//   }

//   // Postconditions:

//   // Exit:

//   return result;
// }

// sheaf::pod_index_type
// fiber_bundle::product_section_space_schema_poset::
// get_ext_id(pod_index_type xint_id,
//            const string& xid_space_name,
//            bool xauto_access) const
// {
//   // Preconditions:

//   require(xauto_access || state_is_read_accessible());
//   require(is_valid_int_id(xint_id, xid_space_name, xauto_access));


//   // Body:

//   pod_index_type lbase_id, lfiber_id;
//   tuple(xint_id, lbase_id, lfiber_id);

//   pod_index_type result = base_space().get_ext_id(lbase_id,
// 						  xid_space_name,
// 						  xauto_access);

//   // Postconditions:

//   ensure(result >= 0);

//   // Exit:

//   return result;
// }

// PROTECTED FUNCTIONS

sheaf::schema_poset_member*
fiber_bundle::product_section_space_schema_poset::
new_schema_handle(const string& xid_space_name,
                  pod_index_type xschema_member_ext_id,
                  pod_index_type xbase_space_ext_id,
                  pod_index_type xfiber_schema_ext_id,
                  pod_index_type xlocal_schema_ext_id)
{
  // Preconditions:

  // Body:

  // Create a handle of the type appropriate for members of this
  // which will be used as a schema.

  schema_poset_member* result = new product_section_space_schema_member();

  // Get the internal id for the base space.

  pod_index_type lbase_id =
    base_space().get_int_id(xbase_space_ext_id, xid_space_name, false);

  // Get the internal id for the fiber schema.

  pod_index_type lfiber_id =
    fiber_schema().get_int_id(xfiber_schema_ext_id, xid_space_name, false);

  // Get the member id from its components

  pod_index_type lint_id;
  ordinal(lbase_id, lfiber_id, lint_id);

  // Attach the handle.

  result->attach_to_state(this, lint_id);

  // Postconditions:

  ensure(result != 0);
  ensure(schema_is_ancestor_of(result));
  ensure(result->is_attached());

  // Exit

  return result;
}

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::product_section_space_schema_poset::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const product_section_space_schema_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::product_section_space_schema_poset::
invariant() const
{
  bool result = true;

  invariance(section_space_schema_poset::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    /// @todo finish product_section_space_schema_poset::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}

// PROTECTED FUNCTIONS

fiber_bundle::product_section_space_schema_poset*
fiber_bundle::product_section_space_schema_poset::
clone() const
{
  product_section_space_schema_poset* result;

  // Preconditions:

  // Body:

  result = new product_section_space_schema_poset;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_attached());

  // Exit

  return result;
}

fiber_bundle::product_section_space_schema_poset&
fiber_bundle::product_section_space_schema_poset::
operator=(const poset_state_handle& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  section_space_schema_poset::operator=(xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return *this;
}

// PRIVATE FUNCTIONS


// ===========================================================
// EXPLICIT INSTANTIATIONS FOR CLASS PRODUCT_SECTION_SPACE_SCHEMA_POSET
// ===========================================================

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
 
template
SHEAF_DLL_SPEC 
fiber_bundle::product_section_space_schema_poset*
sheaf::namespace_poset::
member_poset<fiber_bundle::product_section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::product_section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::product_section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::product_section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::product_section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::product_section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::product_section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
