

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class namespace_poset

#include "namespace_poset.h"

#include "arg_list.h"
#include "array_index_space_state.h" // for intialize_prototypes
#include "array_index_space_interval.h" // for initialize_prototypes
#include "array_poset_dof_map.h"
#include "assert_contract.h"
#include "constant_index_space_interval.h" // for initialize_prototypes
#include "error_message.h"
#include "explicit_crg_interval.h" // for initialize_prototypes
#include "explicit_index_space_interval.h" // for initialize_prototypes
#include "hash_index_space_state.h" // for intialize_prototypes
#include "index_space_iterator.h"
#include "interval_index_space_state.h" // for intialize_prototypes
#include "list_index_space_state.h" // for initialize_prototypes
#include "namespace_poset_dof_map.h"
#include "namespace_poset_member.h"
#include "mutable_index_space_handle.h"
#include "offset_index_space_state.h" // for intialize_prototypes
#include "poset_handle_factory.h"
#include "poset_path.h"
#include "poset_type.h"
#include "postorder_member_iterator.h"
#include "postorder_iterator.h"
#include "primary_index_space_state.h" // for initialize_prototypes
#include "primary_sum_index_space_state.h" // for initialize_prototypes
#include "primitives_index_space_state.h" // for initialize_prototypes
#include "ragged_array_index_space_interval.h" // for initialize_prototypes
#include "refinable_poset.h" // for intialize_prototypes
#include "reserved_primary_index_space_state.h" // for initialize_prototypes
#include "singleton_index_space_state.h" // for initalize_prototypes
#include "singleton_index_space_interval.h" // for initialize_prototypes
#include "standard_member_hack_crg_interval.h" // for initialize_prototypes
#include "std_list.h"
#include "std_set.h"
#include "std_sstream.h"
#include "subposet_member_iterator.h"
#include "tern.h"
#include "total_poset_member.h"

//#define DIAGNOSTIC_OUTPUT

namespace
{

///
/// Traverses in post order the dependency graph implied by the prereq_ids.
///
void
traverse_prereqs(const sheaf::namespace_poset* xns,
                 const sheaf::pod_index_type xid,
                 list<sheaf::pod_index_type>& xrev_post,
                 sheaf::zn_to_bool& xvisited)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_accessible());

  // Body:

  sheaf::namespace_poset_member lns_mbr(xns, xid);
  for(int i=0; i<sheaf::PREREQ_IDS_UB; ++i)
  {
    sheaf::pod_index_type lprereq_id = lns_mbr.poset_prereq_id(i);
 
    if(sheaf::is_valid(lprereq_id) &&
        (lprereq_id >= xns->standard_member_ct()))
    {
      if(!xvisited[lprereq_id])
      {
        xvisited.put(lprereq_id, true);
        traverse_prereqs(xns, lprereq_id, xrev_post, xvisited);
      }
    }
  }
  xrev_post.push_front(xid);

  lns_mbr.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

}

// ===========================================================
// NAMESPACE_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::namespace_poset*
sheaf::namespace_poset::
current_namespace()
{
  // Preconditions:

  // Body:

  // Postconditions:


  // Exit:

  return _current_namespace;
}

sheaf::poset_path
sheaf::namespace_poset::
primitives_schema_path()
{
  // cout << endl << "Entering namespace_poset::primitives_schema_path." << endl;

  // Preconditions:


  // Body:

  poset_path result(primitives_poset_schema::standard_name(), "top");

  // Postconditions:

  ensure(result.full());
  
  // Exit:

  // cout << "Leaving namespace_poset::primitives_schema_path." << endl;
  return result;
}


sheaf::namespace_poset::
~namespace_poset()
{
  // Preconditions:

  require(is_attached() ? state_is_read_write_accessible() : true);

  // Body:

  if(is_attached())
  {
    // Remove all the non-standard members

    clear();

    // Remove the standard members;
    // requires special treatment to avoid contract violations.

    disable_invariant_check();

    begin_jim_edit_mode();

    // Delete the members.

    poset_state* lposet_state;
    namespace_poset_member lstd_mbr;

    lstd_mbr.attach_to_state(this, _primitives.index());
    lstd_mbr.delete_state();

    lstd_mbr.attach_to_state(this, _namespace_schema.index());
    lstd_mbr.delete_state();

    lstd_mbr.attach_to_state(this, _primitives_schema.index());
    lstd_mbr.delete_state();

    // Detach the schema for the table state and dof maps
    // before deleting the namespace schema poset so that the
    // dof id space handles can be released.

    schema().detach_from_state();
    table_dof_map(false).schema().detach_from_state();

    for(pod_index_type i = 0; i < row_dof_tuple_ct(); ++i)
    {
      row_dof_map(i, false).schema().detach_from_state();
    }
    
    // Detach handles and delete the associated poset states,
    // handles will be deleted automatically as data members of this.

    _primitives.get_read_write_access(true);
    lposet_state = _primitives.state_obj();
    _primitives.release_access();
    _primitives.detach_from_state();
    delete lposet_state;

    _namespace_schema.get_read_write_access(true);
    lposet_state = _namespace_schema.state_obj();
    _namespace_schema.release_access();
    _namespace_schema.detach_from_state();
    delete lposet_state;

    _primitives_schema.get_read_write_access(true);
    lposet_state = _primitives_schema.state_obj();
    _primitives_schema.release_access();
    _primitives_schema.detach_from_state();
    delete lposet_state;

    // Detach and delete the state.
    // Can't let ~poset_state_handle do this because
    // it assumes this still has a schema.

    poset_state* lstate = _state;
    detach_from_state();
    delete lstate;
  }

  // Postconditions:

  // Exit

  return;
}

sheaf::namespace_poset::
namespace_poset(const string& xname)
    : poset_state_handle(new namespace_poset_member, new namespace_poset_member)
{
  // Preconditions:

  require(precondition_of(new_state(xname)));

  // Body:

  // Create the state.

  new_state(xname);

  // Postconditions:

  ensure(postcondition_of(new_state(xname)));

  // Exit:

  return;
}

void
sheaf::namespace_poset::
clear()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  // We have to delete the members in reverse dependency order, that is,
  // we can not delete a prerequisite before the posets that depend on it.
  // We'll do that by traversing the dependency graph in post order,
  // pushing the prerequisites onto a stack, then traverse the stack.
  // To start the dependency graph traversal, we need the maximal members.

  // Find the "maximal" members of the dependency graph,
  // that is, the members which are not a prerequisite for
  // some other member

  // First create a set containing all members, except the standard ones.

  typedef set<pod_index_type> lmax_mbrs_type;

  lmax_mbrs_type lmax_mbrs;
  index_iterator litr = whole().indexed_member_iterator();
  while(!litr.is_done())
  {
    if(litr.index().hub_pod() >= standard_member_ct())
    {
      lmax_mbrs.insert(litr.index().hub_pod());
    }
    litr.next();
  }

  // Now the maximal members set contains all non-standard members.
  // Next, traverse the dependency graph, removing prerequisites from the set.

  litr.reset();
  namespace_poset_member lns_mbr(top());
  while(!litr.is_done())
  {
    if(is_jim(litr.index(), false))
    {
      // This member is a jim and has an associated poset

      lns_mbr.attach_to_state(litr.index());

      for(int i=0; i<PREREQ_IDS_UB; ++i)
      {
        pod_index_type lprereq_id = lns_mbr.poset_prereq_id(i);

        if(is_valid(lprereq_id))
        {
          lmax_mbrs.erase(lprereq_id);
        }
      }
    }
    litr.next();
  }
  lns_mbr.detach_from_state();

  // Now lmax members contains the maximal members and any non-standard jrms.

  // Traverse the dependency graph in post order,
  // pushing the members onto a stack.

  zn_to_bool lvisited(member_index_ub().pod());
  list<pod_index_type> lrev_post;
  lmax_mbrs_type::iterator lmax_mbrs_itr = lmax_mbrs.begin();

  pod_index_type lmbr_id;

  while(lmax_mbrs_itr != lmax_mbrs.end())
  {
    lmbr_id = *lmax_mbrs_itr;
    if(lmbr_id >= standard_member_ct())
    {
      if(is_jim(lmbr_id, false))
      {
        // This mbr has an associated poset; traverse its prerequisites

        ::traverse_prereqs(this, lmbr_id, lrev_post, lvisited);
      }
      else
      {
        // This is a jrm; just push it onto the stack.

        lvisited.put(lmbr_id, true);
        lrev_post.push_front(lmbr_id);
      }
    }
    ++lmax_mbrs_itr;
  }

#ifdef DIAGNOSTIC_OUTPUT
  list<pod_index_type>::iterator lrev_post_itr = lrev_post.begin();
  while(lrev_post_itr != lrev_post.end())
  {
    cout << "  " << *lrev_post_itr;
    ++lrev_post_itr;
  }
  cout << endl << endl;
#endif

  // Now popping the stack will traverse the members in reverse dependency order,
  // any prerequisite will appear after all posets that require it.
  // So now we can just run the stack, deleting as we go.

  begin_jim_edit_mode();

  while(!lrev_post.empty())
  {
    lns_mbr.attach_to_state(this, lrev_post.front());

#ifdef DIAGNOSTIC_OUTPUT
    cout << endl << "deleting ns mbr: " << lns_mbr.index()
    << " " << lns_mbr.name()
    << endl;
#endif

    if(lns_mbr.is_jim(false))
    {
      // Delete the handle and state of the associated poset; 
      // also deletes member state.

      delete_poset(lns_mbr);
    }
    else
    {
      // This is a jrm, doesn't have an associated poset.
      // Just delete the member state.

      lns_mbr.delete_state();
    }

    lrev_post.pop_front();
  }

  end_jim_edit_mode();

  // Remove all non-standard id spaces in this and the remaining members.

  clear_member_id_spaces(false);
  primitives().clear_member_id_spaces(true);
  primitives_schema().clear_member_id_spaces(true);
  namespace_schema().clear_member_id_spaces(true);

  // Postconditions:

  ensure(has_standard_member_ct());
  ensure(member_id_spaces(false).has_only_standard_id_spaces());
  ensure(primitives().member_id_spaces(false).has_only_standard_id_spaces());
  ensure(primitives_schema().member_id_spaces(false).has_only_standard_id_spaces());
  ensure(namespace_schema().member_id_spaces(false).has_only_standard_id_spaces());

  // Exit

  return;
}

void
sheaf::namespace_poset::
initialize_prototypes()
{
  // Preconditions:

  // Body:

  initialize_poset_prototypes();
  initialize_crg_interval_prototypes();
  initialize_dof_map_prototypes();
  initialize_id_space_prototypes();

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::namespace_poset::
initialize_poset_prototypes()
{
  // Preconditions:

  // Body:

  static bool lposet_prototypes_initialized = false;

  if(!lposet_prototypes_initialized)
  {
    // Initialize the prototypes

    namespace_poset::make_prototype();
    namespace_poset_schema::make_prototype();
    poset::make_prototype();
    primitives_poset::make_prototype();
    primitives_poset_schema::make_prototype();
    refinable_poset::make_prototype();

    // Done with prototype initializations.

    lposet_prototypes_initialized = true;

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Initialized sheaves poset prototypes" << endl;
#endif

  }

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::namespace_poset::
initialize_crg_interval_prototypes()
{
  // Preconditions:

  // Body:

  static bool lcrg_interval_prototypes_initialized = false;

  if(!lcrg_interval_prototypes_initialized)
  {
    // Initialize the prototypes

    explicit_crg_interval::make_prototype();
    standard_member_hack_crg_interval::make_prototype();

    // Done with prototype initializations.

    lcrg_interval_prototypes_initialized = true;

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Initialized sheaves crg interval prototypes" << endl;
#endif
  }

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::namespace_poset::
initialize_dof_map_prototypes()
{
  // Preconditions:

  // Body:

  static bool ldof_map_prototypes_initialized = false;

  if(!ldof_map_prototypes_initialized)
  {
    // Initialize the prototypes

    array_poset_dof_map::make_prototype();
    namespace_poset_dof_map::make_prototype();
    primitives_poset_dof_map::make_prototype();

    // Done with prototype initializations.

    ldof_map_prototypes_initialized = true;

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Initialized sheaves dof map prototypes" << endl;
#endif
  }

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::namespace_poset::
initialize_id_space_prototypes()
{
  // Preconditions:

  // Body:

  static bool lid_space_prototypes_initialized = false;

  if(!lid_space_prototypes_initialized)
  {
    // Initialize the prototypes

    array_index_space_state::make_prototype();
    hash_index_space_state::make_prototype();
    interval_index_space_state::make_prototype();
    list_index_space_state::make_prototype();
    offset_index_space_state::make_prototype();
    primary_index_space_state::make_prototype();
    primary_sum_index_space_state::make_prototype();
    primitives_index_space_state::make_prototype();
    reserved_primary_index_space_state::make_prototype();
    singleton_index_space_state::make_prototype();

    array_index_space_interval::make_prototype();
    constant_index_space_interval::make_prototype();
    explicit_index_space_interval::make_prototype();
    ragged_array_index_space_interval::make_prototype();
    singleton_index_space_interval::make_prototype();

    // Done with prototype initializations.

    lid_space_prototypes_initialized = true;

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Initialized sheaves id space prototypes" << endl;
#endif
  }

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

void
sheaf::namespace_poset::
virtual_initialize_prototypes()
{
  // cout << endl << "Entering namespace_poset::virutal_initialize_prototypes." << endl;

  // Preconditions:


  // Body:

  // Call static version defined in this class.

  namespace_poset::initialize_prototypes();

  // Postconditions:


  // Exit:

  // cout << "Leaving namespace_poset::virutal_initialize_prototypes." << endl;
  return;
}


sheaf::namespace_poset::
namespace_poset()
    : poset_state_handle(new namespace_poset_member, new namespace_poset_member)
{
  // Nothing to do.
}

sheaf::namespace_poset::
namespace_poset(namespace_poset_member* xtop, namespace_poset_member* xbottom)
    :  poset_state_handle(xtop, xbottom)
{
  // Preconditions:

  require(precondition_of(poset_state_handle(xtop, xbottom)));

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(poset_state_handle(xtop, xbottom)));

  // Exit:

  return;
}

sheaf::namespace_poset::
namespace_poset(const namespace_poset& xother)
    : poset_state_handle(new namespace_poset_member, new namespace_poset_member)
{
  // Preconditions:

  require(xother.state_is_read_accessible());

  // Body:

  disable_invariant_check();

  attach_to_state(&xother);

  enable_invariant_check();

  // Postconditions

  ensure(is_same_state(&xother));

  // Exit:

  return;
}

sheaf::namespace_poset&
sheaf::namespace_poset::
operator=(const namespace_poset& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(xother.host(), xother.index());

  // Postconditions

  ensure(is_same_state(&const_cast<namespace_poset&>(xother)));

  // Exit:

  return *this;
}

sheaf::namespace_poset&
sheaf::namespace_poset::
operator=(const poset_state_handle& xother)
{

  /// @hack allows successful linkage
  require(false);

  // Exit:

  return *this;
}

sheaf::namespace_poset::
namespace_poset(const namespace_poset* xhost, pod_index_type xindex)
    : poset_state_handle(new namespace_poset_member, new namespace_poset_member)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));

  // Body:

  attach_to_state(xhost, xindex);

  // Postconditions:

  ensure(is_attached());
  ensure(host() == xhost);
  ensure(index() == xindex);
}

sheaf::namespace_poset::
namespace_poset(const namespace_poset* xhost, const scoped_index& xindex)
    : poset_state_handle(new namespace_poset_member, new namespace_poset_member)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));

  // Body:

  attach_to_state(xhost, xindex.hub_pod());

  // Postconditions:

  ensure(is_attached());
  ensure(host() == xhost);
  ensure(index() ==~ xindex);
}

void
sheaf::namespace_poset::
put_current_namespace(namespace_poset* xns)
{
  // Preconditions:

  // Body:

  _current_namespace = xns;

  // Postconditions:

  ensure(current_namespace() == xns);

  // Exit:

  return;
}

void
sheaf::namespace_poset::
initialize_additional_members()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  define_old_variable(int old_access_request_depth = access_request_depth());

  // Body:

  // Nothing to do in this class;
  // intended to be redefined in descendants.

  // Postconditions:

  ensure(access_request_depth() == old_access_request_depth);

  // Exit:

  return;
}

void
sheaf::namespace_poset::
initialize_standard_id_spaces()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!member_id_spaces(false).contains("member_poset_id_space"));

  // Body:

  arg_list largs = array_index_space_state::make_arg_list(0);

  pod_index_type result =
    member_id_spaces(false).new_secondary_state("member_poset_id_space",
					   "array_index_space_state",
					   largs,
                                           true);

  // Postconditions:

  ensure(member_id_spaces(false).contains("member_poset_id_space"));

  // Exit:

  return;
}

sheaf::scoped_index
sheaf::namespace_poset::
insert_poset(const poset_state_handle& xposet, const string& xposet_name, bool xauto_link)
{
  // Preconditions:

  /// @hack previously this routine entered and exited jim_edit_mode
  /// without exporting any precondition. As a result, numerous new_state
  /// routines do not properly provide access before calling this routine.
  /// Continue the old practice until we get a chance to clean the mess up.


  //   require(xns.contains_member(name()) ?
  //           xns.state_is_read_write_accessible() :
  //           xns.in_jim_edit_mode());

  require(state_is_read_write_accessible());
  require(xposet.state_is_read_accessible());

  // Body:

  namespace_poset_member lns_mbr;

  if(contains_member(xposet_name, false))
  {
    // Namespace member with same name already exists;
    // attach to it.

    lns_mbr.attach_to_state(this, xposet_name);

    // Set the name space member dofs:

    lns_mbr.put_poset(xposet);
  }
  else
  {
    // Member corresponding to xposet has not yet been created;
    // Create it with same name as xposet.

    begin_jim_edit_mode(false);

    lns_mbr.new_jim_state(this, 0, false, false);
    lns_mbr.put_name(xposet_name, true, false);

    // Add member poset to sequence id space.

    mutable_index_space_handle& lid_space = 
      member_id_spaces(false).get_id_space<mutable_index_space_handle>("member_poset_id_space");
    lid_space.push_back(lns_mbr.index());
    release_member_poset_id_space(lid_space, false);

    // Set the name space member dofs:

    lns_mbr.put_poset(xposet);

    // Link the member into the appropriate group.

    if(xauto_link)
    {
      link_poset(lns_mbr);
    }

    end_jim_edit_mode(true, false);
  }

  scoped_index result = lns_mbr.index();

  lns_mbr.detach_from_state();

  // Postconditions:

  ensure(contains_member(result));
  ensure(&member_poset(result) == &xposet);

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::namespace_poset::
insert_poset(const poset_state_handle& xposet, const string& xposet_name, bool xauto_link, bool xauto_access)
{
  // Preconditions:

  require(!contains_member(xposet_name));
  require(xauto_access || in_jim_edit_mode());
  require(xposet.state_is_auto_read_accessible(xauto_access));

  // Body:

  namespace_poset_member lns_mbr;

  // Member corresponding to xposet has not yet been created;
  // Create it with same name as xposet.

  if(xauto_access)
  {
    begin_jim_edit_mode(true);
    xposet.get_read_access();
  }
  

  lns_mbr.new_jim_state(this, 0, false, false);
  lns_mbr.put_name(xposet_name, true, false);

  // Add member poset to sequence id space.

  mutable_index_space_handle& lid_space = 
    member_id_spaces(false).get_id_space<mutable_index_space_handle>("member_poset_id_space");
  lid_space.push_back(lns_mbr.index());
  release_member_poset_id_space(lid_space, false);

  // Set the name space member dofs:

  lns_mbr.put_poset(xposet);

  // Link the member into the appropriate group.

  if(xauto_link)
  {
    link_poset(lns_mbr);
  }


  if(xauto_access)
  {
    end_jim_edit_mode(true, true);
    xposet.release_access();
  }

  scoped_index result = lns_mbr.index();

  // Postconditions:

  ensure(contains_member(result));
  ensure(&member_poset(result) == &xposet);

  // Exit:

  return result;
}

void
sheaf::namespace_poset::
link_poset(const namespace_poset_member& xmbr)
{
  // Preconditions:

  require(contains_member(&xmbr));
  require(in_jim_edit_mode());

  // Body:

  pod_index_type lmbr_id = xmbr.index().pod();
  pod_index_type lmbr_schema_id = xmbr.poset_prereq_id(0);

  if(lmbr_schema_id == PRIMITIVES_SCHEMA_INDEX)
  {
    // This is a schema poset; link it under the schema defintions group.

    new_link(SCHEMA_DEFINITIONS_INDEX, lmbr_id);
    new_link(lmbr_id, BOTTOM_INDEX);
  }
  else
  {
    // Default is xmbr is in general spaces group.

    pod_index_type lgeneral_sets_id = member_id("general_sets", false);

    if(!is_valid(lgeneral_sets_id))
    {
      // general sets member not created yet; create it now.

      lgeneral_sets_id = new_member(false);
      put_member_name(lgeneral_sets_id, "general_sets", true, false);
      new_link(TOP_INDEX, lgeneral_sets_id);
    }
    new_link(lgeneral_sets_id, xmbr.index().pod());
    new_link(xmbr.index().pod(), BOTTOM_INDEX);
  }

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE FUNCTIONS

sheaf::namespace_poset*
sheaf::namespace_poset::
_current_namespace  = 0;

bool
sheaf::namespace_poset::
make_prototype()
{
  // Preconditions:

  // Body:

  poset_type ltype = NAMESPACE_POSET_ID;

  namespace_poset* lproto = new namespace_poset;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return true;
}


// ===========================================================
// POSET FACTORY METHOD FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset&
sheaf::namespace_poset::
new_schema_poset(const string& xname, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || in_jim_edit_mode());
  require(!contains_member(xname, true));

  // Body:

  arg_list largs = poset::make_args();
  poset& result = new_member_poset<poset>(xname, "primitives_schema/top",
					  largs, xauto_access);
  result.get_read_write_access();  
  
  // Create the schema subposets of the top.

  subposet ltable_dofs(&result, 0, false);
  subposet lrow_dofs(&result, 0, false);

  // Schematize the result.

  result.schematize(&ltable_dofs, &lrow_dofs, true);

  // Clean up.

  ltable_dofs.detach_from_state();
  lrow_dofs.detach_from_state();

  // Postconditions:

  ensure(result.name() == xname);
  ensure(result.is_schematized(false));
  
  result.release_access();

  // Exit:

  return result;
}

void
sheaf::namespace_poset::
delete_poset(pod_index_type xhub_id, bool xauto_access)
{
  // Preconditions:

  require(contains_poset(xhub_id, xauto_access));
  require(member_poset(xhub_id, xauto_access).state_is_auto_read_write_accessible(true));
  require(xauto_access || in_jim_edit_mode());

  // Body:

  if(xauto_access)
  {
    begin_jim_edit_mode(true);
  }

  namespace_poset_member lmbr(this, xhub_id);

  delete_poset(lmbr);
  
  if(xauto_access)
  {
    end_jim_edit_mode(true, true);
  }

  // Postconditions:

  ensure(!contains_poset(xhub_id, xauto_access));

  // Exit:

  return;
}

void
sheaf::namespace_poset::
delete_poset(scoped_index xid, bool xauto_access)
{
  // Argument xid must be passed by value, otherwise
  // since poset_state_handle::index returns a reference,
  // it is possible to pass a reference to the index
  // member of the poset handle itself, which has just
  // been deleted, causing the usage of xid in postcondition
  // to fail.


  // Preconditions:

  require(contains_poset(xid, xauto_access));
  require(member_poset(xid, xauto_access).state_is_auto_read_write_accessible(true));
  require(xauto_access || in_jim_edit_mode());

  // Body:

  delete_poset(xid.hub_pod(), xauto_access);

  // Postconditions:

  ensure(!contains_poset(xid, xauto_access));

  // Exit:

  return;
}

void
sheaf::namespace_poset::
delete_poset(string xname, bool xauto_access)
{
  // Argument xname passed by value as opposed to ref
  // to avoid any possibility of it being a reference
  // to something in the poset being deleted, which
  // would cause usage in postcondition to fail.

  // Preconditions:

  require(contains_poset(xname, xauto_access));
  require(member_poset(xname, xauto_access).state_is_auto_read_write_accessible(true));
  require(xauto_access || in_jim_edit_mode())
;
  // Body:

  delete_poset(member_id(xname, xauto_access), xauto_access);

  // Postconditions:

  ensure(!contains_poset(xname, xauto_access));

  // Exit:

  return;
}

void
sheaf::namespace_poset::
delete_poset(poset_path xpath, bool xauto_access)
{
  // Argument xpath passed by value as opposed to ref
  // to avoid any possibility of it being a reference
  // to something in the poset being deleted, which
  // would cause usage in postcondition to fail.

  // Preconditions:

  require(contains_poset(xpath, xauto_access));
  require(member_poset(xpath, xauto_access).state_is_auto_read_write_accessible(true));
  require(xauto_access || in_jim_edit_mode());

  // Body:

  delete_poset(member_id(xpath.poset_name(), xauto_access), xauto_access);  

  // Postconditions:

  ensure(!contains_poset(xpath, xauto_access));

  // Exit:

  return;
}

void
sheaf::namespace_poset::
delete_poset(namespace_poset_member& xmbr)
{
  // Preconditions:

  require(in_jim_edit_mode());
  require(xmbr.is_jim());
  require(xmbr.poset_pointer()->state_is_auto_read_write_accessible(true));

  // Body:

  define_old_variable(scoped_index old_xmbr_index = xmbr.index());

  // Get the poset handle.

  poset_state_handle* lposet = xmbr.poset_pointer();

  // Detach the handle from its state and delete the state;
  // requires write access. One of the few places there's no matching release!

  lposet->get_read_write_access(true);
  lposet->terminate_access();

  // Delete the handle.

  delete lposet;

  // Clean up the member dof tuple.

  xmbr.put_poset_pointer(0);
  xmbr.put_poset_type_id(NOT_A_POSET_TYPE);
  xmbr.put_poset_class("");

  // Delete the member.

  xmbr.delete_state(false);

  // Postconditions:

  ensure(!contains_poset(old_xmbr_index, false));
  ensure(!xmbr.is_attached());

  // Exit:

  return;
}

sheaf::poset_state_handle&
sheaf::namespace_poset::
member_poset(pod_index_type xhub_id, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xhub_id, xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(is_jim(xhub_id));

  // Body:

  namespace_poset_dof_map& ldof_map =
    row_dof_map(member_dof_tuple_id(xhub_id, false));

  poset_state_handle& result = *ldof_map.poset_pointer();

  if(xauto_access)
  {
    release_access();
  }

  return result;
}

sheaf::poset_state_handle&
sheaf::namespace_poset::
member_poset(const scoped_index& xid, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xid, xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(is_jim(xid));

  // Body:

  poset_state_handle& result = member_poset(xid.hub_pod(), false);

  if(xauto_access)
  {
    release_access();
  }

  return result;
}

sheaf::poset_state_handle&
sheaf::namespace_poset::
member_poset(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(contains_member(xpath.poset_name(), xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(is_jim(xpath.poset_name()));

  // Body:

  poset_state_handle& result = member_poset(member_id(xpath.poset_name(), false), false);

  // Postconditions:

  if(xauto_access)
  {
    release_access();
  }

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// POSET FACTORY METHOD QUERY FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::pod_index_type
sheaf::namespace_poset::
member_poset_schema_id(const scoped_index& xindex, bool xauto_access) const
{
  // Preconditions:

  require(is_attached());
  require(state_is_auto_read_accessible(xauto_access));
  require(contains_poset(xindex));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  namespace_poset_member lmbr(this, xindex);
  pod_index_type result = lmbr.poset_prereq_id(0);
  lmbr.detach_from_state();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}


bool
sheaf::namespace_poset::
contains_poset(pod_index_type xhub_id, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  if(xauto_access)
  {
    get_read_access();
  }

  // Body:

  result = contains_member(xhub_id, false) && is_jim(xhub_id);

  // Postconditions:

  if(xauto_access)
  {
    release_access();
  }

  // Exit

  return result;
}

bool
sheaf::namespace_poset::
contains_poset(const scoped_index& xid, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  return contains_poset(xid.hub_pod(), xauto_access);
}

bool
sheaf::namespace_poset::
contains_poset(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result =
    !xpath.poset_name().empty() && contains_member(xpath.poset_name(), false) && is_jim(xpath.poset_name());

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::namespace_poset::
owns(const poset_state_handle& xposet, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result = contains_poset(xposet.path(true), xauto_access);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::namespace_poset::
poset_state_is_read_accessible(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result =
    contains_poset(xpath, xauto_access) &&
    member_poset(xpath, xauto_access).state_is_read_accessible();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
poset_state_is_read_write_accessible(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result =
    contains_poset(xpath, xauto_access) &&
    member_poset(xpath, xauto_access).state_is_read_write_accessible();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
contains_poset_member(pod_index_type xposet_hub_id,
                      pod_index_type xmember_hub_id,
                      bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(xauto_access ||
          (contains_poset(xposet_hub_id) ?
           member_poset(xposet_hub_id).state_is_read_accessible() :
           true));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result =
    contains_poset(xposet_hub_id, false) &&
    member_poset(xposet_hub_id, false).contains_member(xmember_hub_id, xauto_access);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::namespace_poset::
contains_poset_member(const scoped_index& xposet_id,
                      const scoped_index& xmember_id,
                      bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(xauto_access ||
          (contains_poset(xposet_id) ?
           member_poset(xposet_id).state_is_read_accessible() :
           true));

  // Body:

  return contains_poset_member(xposet_id.hub_pod(),
			       xmember_id.hub_pod(),
			       xauto_access);
}

bool
sheaf::namespace_poset::
contains_poset_member(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xpath.full());
  require(xauto_access || state_is_read_accessible());
  require(xauto_access ||
          (contains_poset(xpath, false) ?
           poset_state_is_read_accessible(xpath, false) :
           true));


  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result =
    xpath.full() &&
    contains_poset(xpath, false) &&
    member_poset(xpath, false).contains_member(xpath.member_name(), xauto_access);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::namespace_poset::
contains_poset_members(const string& xposet_name,
                       const string xmember_names[],
                       int xmember_names_ct,
                       bool xauto_access) const
{
  bool result = true;

  // Preconditions:

  require(!xposet_name.empty());
  require(xmember_names != 0);
  require_for_all(i, 0, xmember_names_ct, !xmember_names[i].empty());
  require(xauto_access || state_is_read_accessible());
  require(xauto_access ||
          (contains_poset(xposet_name) ?
           member_poset(xposet_name).state_is_read_accessible() :
           true));

  // Body:

  result =
    contains_member(xposet_name) &&
    member_poset(xposet_name, false).contains_members(xmember_names,
        xmember_names_ct,
        xauto_access);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::namespace_poset::
contains_poset_subposet(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xpath.full());
  require(xauto_access || state_is_read_accessible());
  require(xauto_access ||
          ( contains_poset(xpath) ?
            member_poset(xpath).state_is_read_accessible() :
            true));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result =
    contains_member(xpath.poset_name(), false) &&
    member_poset(xpath.poset_name(), false).includes_subposet(xpath.member_name(),
        xauto_access);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::namespace_poset::
contains_path(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  result = !xpath.poset_name().empty();
  if(result)
  {
    if(!xpath.member_name().empty())
    {
      result = contains_poset_member(xpath, xauto_access);
    }
    else
    {
      result = contains_poset(xpath, xauto_access);
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
path_is_auto_read_accessible(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = 
    contains_path(xpath, xauto_access) &&
    member_poset(xpath, xauto_access).state_is_auto_read_accessible(xauto_access);  

  // Postconditions:


  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = 
    contains_path(xpath, xauto_access) &&
    member_poset(xpath, xauto_access).state_is_auto_read_write_accessible(xauto_access);  

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
path_is_auto_read_available(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = 
    !contains_path(xpath, xauto_access) ||
    member_poset(xpath, xauto_access).state_is_auto_read_accessible(xauto_access);  

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
path_is_auto_read_write_available(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = 
    !contains_path(xpath, xauto_access) ||
    member_poset(xpath, xauto_access).state_is_auto_read_write_accessible(xauto_access);  

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
arg_is_auto_read_accessible(const string& xname, const arg_list& xargs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = xargs.contains_arg(xname);
  if(result)
  {
    primitive_value lval = xargs.value(xname);
    result = (lval.id() == C_STRING);
    if(result)
    {
      poset_path lpath(lval);
      result = !lpath.empty();
      if(result)
      {
	result = path_is_auto_read_accessible(lpath, xauto_access);
      }
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible(const string& xname, const arg_list& xargs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = xargs.contains_arg(xname);
  if(result)
  {
    primitive_value lval = xargs.value(xname);
    result = (lval.id() == C_STRING);
    if(result)
    {
      poset_path lpath(lval);
      result = !lpath.empty();
      if(result)
      {
	result = path_is_auto_read_write_accessible(lpath, xauto_access);
      }
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
arg_is_auto_read_available(const string& xname, const arg_list& xargs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = xargs.contains_arg(xname);
  if(result)
  {
    primitive_value lval = xargs.value(xname);
    result = (lval.id() == C_STRING);
    if(result)
    {
      poset_path lpath(lval);
      result = !lpath.empty();
      if(result)
      {
	result = path_is_auto_read_available(lpath, xauto_access);
      }
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset::
arg_is_auto_read_write_available(const string& xname, const arg_list& xargs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  result = xargs.contains_arg(xname);
  if(result)
  {
    primitive_value lval = xargs.value(xname);
    result = (lval.id() == C_STRING);
    if(result)
    {
      poset_path lpath(lval);
      result = !lpath.empty();
      if(result)
      {
	result = path_is_auto_read_write_available(lpath, xauto_access);
      }
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset_type
sheaf::namespace_poset::
type_id() const
{
  return NAMESPACE_POSET_ID;
}

const char*
sheaf::namespace_poset::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "namespace_poset";

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::namespace_poset::
begin_jim_edit_mode(bool xauto_access)
{
  // Preconditions:

  // Body:

  poset_state_handle::begin_jim_edit_mode(xauto_access);

  // Postconditions:

  // Exit

  return;
}

void
sheaf::namespace_poset::
end_jim_edit_mode(bool xensure_lattice_invariant, bool xauto_access)
{
  // Preconditions:

  // Body:

  poset_state_handle::end_jim_edit_mode(xensure_lattice_invariant, xauto_access);

  // Postconditions:

  // Exit

  return;
}

void
sheaf::namespace_poset::
get_read_access() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  define_old_variable(int old_access_request_depth =
                        access_request_depth());
  define_old_variable(int old_primitives_access_request_depth =
                        primitives().access_request_depth());

  // Get read access to this:

  poset_state_handle::get_read_access();

  // Get read access to the primitives poset.

  primitives().get_read_access();

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() ==
         old_access_request_depth + 1);

  ensure(primitives().state_is_read_accessible());
  ensure(primitives().access_request_depth() ==
         old_primitives_access_request_depth + 1);

  // Exit

  return;
}

void
sheaf::namespace_poset::
get_read_write_access(bool xrelease_read_only_access)
{
  // Preconditions:

  require(is_attached());
  require(!xrelease_read_only_access ? state_is_not_read_only_accessible() : true);

  // Body:

  define_old_variable(int old_access_request_depth = access_request_depth());
  define_old_variable(int old_primitives_access_request_depth =
                        primitives().access_request_depth());

  // Get read access to this:

  poset_state_handle::get_read_write_access(xrelease_read_only_access);

  // Get read access to the primitives poset.

  primitives().get_read_access();

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
  ensure(primitives().state_is_read_accessible());
  ensure(primitives().access_request_depth() ==
         old_primitives_access_request_depth + 1);

  // Exit

  return;
}

void
sheaf::namespace_poset::
release_access(bool xall) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int old_access_request_depth = access_request_depth();
  int old_primitives_access_request_depth = primitives().access_request_depth();

  // Release at least one level of access for this..
  // If xall, release all levels of access for this.
  // Since each level of access to this also
  // acquired a level of access to the primitives,
  // release the same number of levels of access to the primitives.
  // Note that this may not be all the levels of access of the primitives.
  // Also note that poset_state_handle::release_Access takes care of the schema.

  do
  {
    // Release one level of access.

    primitives().release_access(false);
    poset_state_handle::release_access(false);
  }
  while(xall && state_is_read_accessible());


  // Postconditions:

  ensure(!xall ?
         access_request_depth() == old_access_request_depth - 1 :
         access_request_depth() == 0);
  ensure(access_request_depth() == 0 ? state_is_not_read_accessible() : true);
  ensure(!xall ?
         primitives().access_request_depth() == old_primitives_access_request_depth - 1 :
         primitives().access_request_depth() == 0);
  ensure(primitives().access_request_depth() == 0 ?
         primitives().state_is_not_read_accessible() :
         true);

  // Exit

  return;
}

void
sheaf::namespace_poset::
detach_from_state()
{

  // Preconditions:

  // Body:

  // Detach the primitives and schema

  primitives().detach_from_state();
  namespace_schema().detach_from_state();
  primitives_schema().detach_from_state();

  // Detach from the standard subposets, members, and state

  poset_state_handle::detach_from_state();

  // Postconditions:

  ensure(!is_attached());
  ensure(!is_external());
  ensure(!primitives().is_attached());
  ensure(!primitives_schema().is_attached());

  // Exit

  return;
}

// PROTECTED FUNCTIONS

void
sheaf::namespace_poset::
new_state(const string& xname)
{
  // Preconditions:

  require(poset_path::is_valid_name(xname));

  // Body:

  // Detach from the current state, if any.

  detach_from_state();

  // Disable invariant checking in
  // member functions until construction finished

  disable_invariant_check();

  // Initialize the prototypes; use the virtual method
  // to ensure the prototypes for actual namespace type
  // being created are initialized.

  virtual_initialize_prototypes();

  // The bootstrap problem:
  //
  // The basic issue is that we need the primitives_poset_schema
  // to create the namespace and we need the namespace to create
  // the primitives_poset_schema.
  //
  // The precise mechanism of dependency is that the primitives_poset_schema
  // provides the schema for itself and the namespace_poset_schema which
  // provides the schema for the namespace. We can't instantiate
  // primitives_poset_schema without instantiating primitive_poset_dof_maps as
  // dof tuples for it members and, since primitives_poset_schema is its own schema,
  // we can't instantiate the dof tuples without instantiating the poset. In addition,
  // the standard poset constructors insert the poset into a namespace, so we also
  // can't create the two schema posets or the primtives poset until we have a
  // namespace. Furthermore, the various member functions invoked by the constructor
  // require state_is_read_write_accessible(), which it turn ensures
  // primitives().state_is_read_accessible(), but the primitives haven't been
  // created yet.
  //
  // The bootstrap thus requires three conditions:
  //
  // 1) primitives_poset_dof_map must be instantiatable without a schema;
  // 2) primitives_poset_schema must be instantiated with itself as schema;
  // 3) primitives_poset must be instantiated before we get access to the namespace
  //    state; and
  // 3) primitives_poset_schema, namespace_poset_schema, and  primitives_poset
  //    must not insert themselves into the namespace.
  //
  // So also the discussion in primitives_poset_dof_map.

  // Create the primitives schema. Creates dof tuples of type
  // primitives_poset_dof_map and uses itself as schema.
  // Inserted in the namespace in routine initialize_standard_members.

  _primitives_schema.new_state();
  _primitives_schema.get_read_access();

  // Create the namespace schema using the primitives schema.
  // Inserted in the namespace in routine initialize_standard_members.

  _namespace_schema.new_state(&(_primitives_schema.top()));
  _namespace_schema.get_read_access();

  // Now we have a schema, create the poset state object.

  _state = new poset_state(&(_namespace_schema.top()), NAMESPACE_POSET_ID, xname);

  // Create the primitives poset using the primitives schema
  // Inserted in the namespace in routine initialize_standard_members.

  _primitives.new_state(&(_primitives_schema.top()));

  // Need to get read-write access to continue construction.

  get_read_write_access();

  // Initialize the table dof map.
  // This class has no table dofs, but we want a non-null dof map anyway.

  initialize_table_dofs(0,0);

  // Initialize additional row structure.
  // Want the primary term for bottom and top in the top id space
  // allocated before the member poset id space which
  // must be allocated before the other standard namespace members
  // are intiailaized. So do it like this:

  initialize_standard_subposets(xname);

  //   initialize_standard_id_spaces();

  initialize_standard_members();

  // Initialize the namespace features

  initialize_namespace(*this);

  // Make this the current namespace.

  put_current_namespace(this);

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // Construct additional members, if any.

  initialize_additional_members();

  // Now the invariant is satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(name() == xname);
  ensure(!in_jim_edit_mode());
//   ensure(host() == 0);
//   ensure(!index().is_valid());
  ensure(index().same_scope(member_hub_id_space(false)));
  ensure(has_standard_subposet_ct());
  ensure(current_namespace() == this);

  // release access

  release_access();

  ensure(state_is_not_read_accessible());
}

void
sheaf::namespace_poset::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  poset_state_handle::attach_handle_data_members();

  /// @hack Invariant requires all three entities below to be attached,
  /// but invariant gets called within scope of attach_to_state,
  /// so have to disable the invariant.

  disable_invariant_check();

  primitives().attach_to_state(this, PRIMITIVES_INDEX);
  primitives_schema().attach_to_state(this, PRIMITIVES_SCHEMA_INDEX);
  namespace_schema().attach_to_state(this, NAMESPACE_SCHEMA_INDEX);

  enable_invariant_check();

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::attach_handle_data_members()));
  ensure(primitives().is_attached());
  ensure(primitives_schema().is_attached());
  ensure(namespace_schema().is_attached());

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// GLOBAL ATTRIBUTES FACET
// ===========================================================

// PUBLIC FUNCTIONS

string
sheaf::namespace_poset::
name() const
{
  string result;

  // Preconditions:

  // is_external is always false for namespace_poset, so
  // precondition is simpler than in parent.

  require(state_is_read_accessible());

  // Body:

  // Redefined just to change precondition;
  // makes presentation clearer in Prog Guide.

  // Postconditions:

  // Exit

  return poset_state_handle::name();
}

string
sheaf::namespace_poset::
name(bool xauto_access) const
{
  string result;

  // Preconditions:

  // is_external is always false for namespace_poset, so
  // precondition is simpler than in parent.

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  // Redefined just to change precondition;
  // makes presentation clearer in Prog Guide.

  // Postconditions:

  // Exit

  return poset_state_handle::name(xauto_access);
}

sheaf::poset_path
sheaf::namespace_poset::
path(bool xauto_access) const
{

  // Preconditions:

  // is_external is always false for namespace_poset, so
  // precondition is simpler than in parent.

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  // Redefined just to change precondition;
  // makes presentation clearer in Prog Guide.

  poset_path result(poset_state_handle::path());

  // Postconditions:

  ensure(!result.empty());
  ensure(!result.full());

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

void
sheaf::namespace_poset::
initialize_namespace(namespace_poset& xns, bool xauto_link)
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Set the host and index features of the poset.

  _name_space = 0;

  _index.invalidate();
  _index.put_scope(member_hub_id_space(false));

  // Postconditions:

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// SCHEMA FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::namespace_poset::
row_dof_map_conforms(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  // Row dofs must be namespace_poset_dof_map

  result = (dynamic_cast<const namespace_poset_dof_map*>(xdof_map) != 0);

  // Postconditions:

  ensure(result ? (dynamic_cast<const namespace_poset_dof_map*>(xdof_map) != 0) : true);

  // Exit

  return result;
}

sheaf::namespace_poset_dof_map&
sheaf::namespace_poset::
row_dof_map(pod_index_type xtuple_hub_id, bool xrequire_write_access) const
{
  namespace_poset_dof_map* result_ptr;

  // Preconditions:

  require(xrequire_write_access ? state_is_read_write_accessible() : state_is_read_accessible());
  require(contains_row_dof_tuple(xtuple_hub_id));

  // Body:

  result_ptr = dynamic_cast<namespace_poset_dof_map*>(table().row_dof_tuple(xtuple_hub_id));

  // Pointer should not be null

  assertion(result_ptr != 0);

  // Postconditions:

  // Exit

  return *result_ptr;
}

const sheaf::scoped_index&
sheaf::namespace_poset::
new_row_dof_map()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  define_old_variable(int old_row_dof_tuple_ct = row_dof_tuple_ct());

  // Create a new namespace poset dof map

  poset_dof_map* lmap = new namespace_poset_dof_map(this);
  table().put_row_dof_tuple(lmap);
  const scoped_index& result = lmap->index();

  // Postconditions:

  ensure(row_dof_tuple_ct() == old_row_dof_tuple_ct+1);
  ensure(contains_row_dof_tuple(result));

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// MEMBERSHIP FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::namespace_poset_member&
sheaf::namespace_poset::
top()
{
  // Preconditions:

  // Body:

  namespace_poset_member& result = *(reinterpret_cast<namespace_poset_member*>(_top));

  // Postconditions:

  // Exit

  return result;
}

const sheaf::namespace_poset_member&
sheaf::namespace_poset::
top() const
{
  // Preconditions:

  // Body:

  const namespace_poset_member& result = *(reinterpret_cast<const namespace_poset_member*>(_top));

  // Postconditions:

  // Exit

  return result;
}

sheaf::namespace_poset_member&
sheaf::namespace_poset::
bottom()
{
  // Preconditions:

  // Body:

  namespace_poset_member& result = *(reinterpret_cast<namespace_poset_member*>(_bottom));

  // Postconditions:

  // Exit

  return result;
}

const sheaf::namespace_poset_member&
sheaf::namespace_poset::
bottom() const
{
  // Preconditions:

  // Body:

  const namespace_poset_member& result = *(reinterpret_cast<const namespace_poset_member*>(_bottom));

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

void
sheaf::namespace_poset::
initialize_standard_members()
{
  // Preconditions:

  // Body:

  // First create the standard members of the base class,
  // creates the primary terrm in the top id space before
  // the secondary term allocated in initialize_standard_id_spaces.

  poset_state_handle::initialize_standard_members();

  // Now create the standard id space; secondary terms it top id space.

  initialize_standard_id_spaces();

  // Insert primitives schema poset into the namespace.
  // Creates primitives schema member at index 2.

  _primitives_schema.initialize_namespace(*this,
                                          primitives_poset_schema::standard_name(),
                                          false);

  // Insert namespace schema poset into the namespace.
  // Creates namespace schema member at index 3.

  _namespace_schema.initialize_namespace(*this,
                                         namespace_poset_schema::standard_name(),
                                         false);

  // Insert primitives poset into the namespace.
  // Creates primitives member at index 4.

  _primitives.initialize_namespace(*this,
                                   primitives_poset::standard_name(),
                                   false);

  // Now there should be 5 standard members: top, bottom, primitives,
  // primitives_schema, and namespace schema.

  // Make the schema definitions group

  scoped_index ldefn_mbrs[2];
  ldefn_mbrs[0] = _primitives_schema.index();
  ldefn_mbrs[1] = _namespace_schema.index();

  total_poset_member ldefn_mbr(this, ldefn_mbrs, 2, tern::TRUE, false);
  ldefn_mbr.put_name("schema definitions", true, false);
  ldefn_mbr.detach_from_state();

  // Now there's 6 standard members:
  // bottom, top, primitives, primitives_schema,
  // namespace_schema, and schema definitions

  // All the memembers and row dof tuples are standard.

  put_standard_member_ct(member_ct());
  put_standard_row_dof_tuple_ct(row_dof_tuple_ct());

  // Postconditions:

  ensure(_primitives.is_attached());
  ensure(_primitives.host() == this);
  ensure(_primitives.index() == PRIMITIVES_INDEX);
  ensure(_primitives_schema.is_attached());
  ensure(_primitives_schema.host() == this);
  ensure(_primitives_schema.index() == PRIMITIVES_SCHEMA_INDEX);
  ensure(_namespace_schema.is_attached());
  ensure(_namespace_schema.host() == this);
  ensure(_namespace_schema.index() == NAMESPACE_SCHEMA_INDEX);
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());

  // Exit

  return;
}

// PRIVATE FUNCTIONS

// ===========================================================
// MEMBER ID SPACE FAMILY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_handle&
sheaf::namespace_poset::
get_member_poset_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).contains("member_poset_id_space"));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const index_space_handle& result = member_id_spaces(false).get_id_space("member_poset_id_space");

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(result.name() == "member_poset_id_space");

  // Exit:

  return result;
}

void
sheaf::namespace_poset::
release_member_poset_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  member_id_spaces(false).release_id_space(xid_space);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::index_space_iterator&
sheaf::namespace_poset::
get_member_poset_id_space_iterator(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).contains("member_poset_id_space"));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  index_space_iterator& result =
    member_id_spaces(false).get_id_space_iterator("member_poset_id_space");

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(result.name() == "member_poset_id_space");

  // Exit:

  return result;
}

void
sheaf::namespace_poset::
release_member_poset_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  member_id_spaces(false).release_id_space_iterator(xitr);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS


// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::pod_index_type
sheaf::namespace_poset::
prereq_id(int xi) const
{
  // The namespace_poset has no prerequisites and
  // this routine should never be called.

  return invalid_pod_index();
}

// PROTECTED FUNCTIONS

void
sheaf::namespace_poset::
put_name(const string& xname)
{
  // cout << endl << "Entering namespace_poset::put_name." << endl;

  // Preconditions:

  require(state_is_read_write_accessible());
  require(poset_path::is_valid_name(xname));
  
  // Body:

  state_obj()->put_name(xname);

  // Postconditions:

  ensure(name() == xname);

  // Exit:

  // cout << "Leaving namespace_poset::put_name." << endl;
  return;
}


// PRIVATE FUNCTIONS


// ===========================================================
// DEBUGGING FACET
// ===========================================================

// PUBLIC FUNCTIONS

void
sheaf::namespace_poset::
to_stream(ostream& xos)
{
  xos << *this;
}

//
string
sheaf::namespace_poset::
to_string()
{
  ostringstream oss;
  oss << *this;
  return oss.str();
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
sheaf::namespace_poset::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const namespace_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::namespace_poset*
sheaf::namespace_poset::
clone() const
{
  namespace_poset* result;

  // Preconditions:

  // Body:

  result = new namespace_poset;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit

  return result;
}

bool
sheaf::namespace_poset::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    invariance(poset_state_handle::invariant());

    disable_invariant_check();

    invariance(host() == 0);
    invariance(!index().is_valid());
    invariance(!is_external());

    invariance(is_attached() ? primitives().is_attached() : true);
    invariance(is_attached() ?
               (primitives().index() == PRIMITIVES_INDEX) :
               true);
    invariance(state_is_read_accessible() ?
               primitives().state_is_read_accessible() :
               true);

    invariance(is_attached() ? primitives_schema().is_attached() : true);
    invariance(is_attached() ?
               (primitives_schema().index() == PRIMITIVES_SCHEMA_INDEX) :
               true);
    invariance(state_is_read_accessible() ?
               primitives_schema().state_is_read_accessible() :
               true);

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

ostream & sheaf::
operator << (ostream &os, const namespace_poset& ns)
{

  // Preconditions:

  require(unexecutable(acquires and releases read access));

  // Body:

  ns.get_read_access(); // also gets access to schema

  os << endl << endl << "#### BEGIN NAMESPACE " << ns.name() << " ###################" << endl;



  os << static_cast<const poset_state_handle&>(ns) << endl;

  subposet_member_iterator itr(const_cast<namespace_poset&>(ns).whole());

  while(!itr.is_done())
  {
    if(itr.is_jim())
    {
      // Member_poset returns a handle of the proper specialized type,
      // as opposed to attaching a general poset_state_handle.

      poset_state_handle& lpsh = ns.member_poset(itr.index());
      if(lpsh.is_attached())
      {
        lpsh.get_read_access();
        os << lpsh << endl;
        lpsh.release_access();
      }
    }
    itr.next();
  }

  os << "#### END NAMESPACE " << ns.name() << " ###################" << endl << endl;

  ns.release_access(); // also releases access to schema

  // Postconditions:

  ensure(unexecutable(access request depth == old access request depth));

  // Exit

  return os;
}

size_t
sheaf::deep_size(const namespace_poset& xp, bool xinclude_shallow, size_t xresults[4])
{
  size_t result;
  size_t lmemory_parts[4];

  // Preconditions:

  // Body:

  // Class data members:

  result = xinclude_shallow ? sizeof(xp) : 0;
  
  if (xresults != 0)
    for (int i=0; i<4; i++)
      xresults[i] = 0;

  // @issue Do we need to add in the schemas or is the calculation below
  // taking care of it?

  // Add the constributes of the poset members.

  namespace_poset& lxp = const_cast<namespace_poset&>(xp);
  poset_state_handle* lpsh = reinterpret_cast<poset_state_handle*>(&lxp);

  // xresults gets initialized in the first call to deep_size

  result += deep_size(*lpsh, xinclude_shallow, xresults);

  subposet_member_iterator litr(lxp.whole());

  while(!litr.is_done())
  {
    if(litr.is_jim())
    {
      // Member_poset returns a handle of the proper specialized type,
      // as opposed to attaching a general poset_state_handle.

      lpsh = &lxp.member_poset(litr.index());
      if(lpsh->is_attached())
      {
        lpsh->get_read_access();
        result += deep_size(*lpsh, xinclude_shallow, lmemory_parts);

	// Increment the 4 memory parts

	if (xresults != 0)
	  for (int i=0; i<4; i++)
	    xresults[i] += lmemory_parts[i];

        lpsh->release_access();
      }
    }
    litr.next();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
