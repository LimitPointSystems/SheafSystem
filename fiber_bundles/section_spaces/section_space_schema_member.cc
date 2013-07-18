

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class section_space_schema_member.

#include "section_space_schema_member.h"

#include "assert_contract.h"
#include "array_index_space_state.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "discretization_iterator.h"
#include "ij_product_structure.h"
#include "index_space_iterator.h"
#include "mutable_index_space_handle.h"
#include "namespace_poset.h"
#include "postorder_member_iterator.h"
#include "postorder_itr.h"
#include "preorder_itr.h"
#include "sec_rep_descriptor.h"
#include "section_component_iterator.h"
#include "section_dof_iterator.h"
#include "section_space_schema_jims_index_space_handle.h"
#include "section_space_schema_jims_index_space_state.h"
#include "section_space_schema_poset.h"
#include "sheaves_namespace.h"
#include "std_set.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SECTION_SPACE_SCHEMA_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::section_space_schema_member::
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

const string&
fiber_bundle::section_space_schema_member::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("section_space_schema_member");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::section_space_schema_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::section_space_schema_member::
operator=(const section_space_schema_member& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  //Body:

  not_implemented();

  //Postconditions:

  ensure(invariant());

  //Exit:

  return *this;
}

fiber_bundle::section_space_schema_member::
~section_space_schema_member()
{

  // Preconditions:

  // Body:

  if(_discretization_id_space != 0)
  {
    _discretization_id_space->release_id_space();
  }

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_rep_descriptor&
fiber_bundle::section_space_schema_member::
rep()
{
  // Preconditions:

  require(is_attached());

  // Body:

  sec_rep_descriptor& result = host()->rep();

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::sec_rep_descriptor&
fiber_bundle::section_space_schema_member::
rep() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  sec_rep_descriptor& result = host()->rep();

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
same_rep(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());

  // Body:

  result = rep().is_same_state(&xother.rep());

  // Postconditions:


  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_member::
base_space_id() const
{
  return _base_space_id;
}

void
fiber_bundle::section_space_schema_member::
base_space_id(scoped_index& result) const
{
  // Preconditions:

  // Body:

  result.put(_base_space.hub_id_space(), _base_space_id);

  // Postconditions:

  ensure(result.same_scope(base_space().hub_id_space()));

  // Exit:

  return;
}

sheaf::total_poset_member&
fiber_bundle::section_space_schema_member::
base_space()
{
  return _base_space;
}

const sheaf::total_poset_member&
fiber_bundle::section_space_schema_member::
base_space() const
{
  return _base_space;
}

bool
fiber_bundle::section_space_schema_member::
same_base_space(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());

  // Body:

  result = base_space().is_same_state(&xother.base_space());

  // Postconditions:


  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_member::
fiber_schema_id() const
{
  return _fiber_schema_id;
}

void
fiber_bundle::section_space_schema_member::
fiber_schema_id(scoped_index& result) const
{
  // Preconditions:

  // Body:

  result.put(_fiber_schema.hub_id_space(), _fiber_schema_id);

  // Postconditions:

  ensure(result.same_scope(fiber_schema().hub_id_space()));

  // Exit:

  return;
}

sheaf::schema_poset_member&
fiber_bundle::section_space_schema_member::
fiber_schema()
{
  return _fiber_schema;
}

const sheaf::schema_poset_member&
fiber_bundle::section_space_schema_member::
fiber_schema() const
{
  return _fiber_schema;
}

bool
fiber_bundle::section_space_schema_member::
same_fiber_schema(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());

  // Body:

  result = fiber_schema().is_same_state(&xother.fiber_schema());

  // Postconditions:


  // Exit:

  return result;
}


sheaf::poset&
fiber_bundle::section_space_schema_member::
fiber_space()
{
  // Preconditions:

  require(is_attached());

  // Body:

  poset& result = host()->fiber_space();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::poset&
fiber_bundle::section_space_schema_member::
fiber_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  poset& result = host()->fiber_space();

  // Postconditions:

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
db() const
{
  int result;

  // Preconditions:

  require(base_space().state_is_read_accessible());

  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  result = _db;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
evaluation_ct() const
{
  int result;

  // Preconditions:

  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  result = _evaluation_ct;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
discretization_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  result = _discretization_ct;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
df() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = fiber_schema().row_dof_ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_member::
df(bool xauto_access)
{
  int result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = df();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

sheaf::subposet&
fiber_bundle::section_space_schema_member::
discretization()
{
  // Preconditions:

  // Body:

  subposet& result = host()->discretization();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::subposet&
fiber_bundle::section_space_schema_member::
discretization() const
{
  // Preconditions:

  // Body:

  subposet& result = host()->discretization();

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
same_discretization(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());

  // Body:

  result = discretization().is_same_state(&xother.discretization());

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_member::
is_multivalued() const
{
  // Preconditions:

  // Body:

  bool result = host()->is_multivalued();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::subposet&
fiber_bundle::section_space_schema_member::
multivalued()
{
  // Preconditions:

  // Body:

  subposet& result = host()->multivalued();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::subposet&
fiber_bundle::section_space_schema_member::
multivalued() const
{
  // Preconditions:

  // Body:

  subposet& result = host()->multivalued();

  // Postconditions:

  // Exit

  return result;
}

sheaf::subposet&
fiber_bundle::section_space_schema_member::
evaluation()
{
  // Preconditions:

  // Body:

  subposet& result = host()->evaluation();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::subposet&
fiber_bundle::section_space_schema_member::
evaluation() const
{
  // Preconditions:

  // Body:

  subposet& result = host()->evaluation();

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
same_evaluation(const section_space_schema_member& xother) const
{
  bool result;

  // Preconditions:

  require(is_attached());
  require(xother.is_attached());

  // Body:

  result = evaluation().is_same_state(&xother.evaluation());

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::section_component_iterator*
fiber_bundle::section_space_schema_member::
component_iterator() const
{
  section_component_iterator* result = 0;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // This member is conceptually abstract in this class and intended
  // to be redefined in descendants. Implemented only to
  // define the pre- and post-conditions.

  not_implemented();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

string
fiber_bundle::section_space_schema_member::
evaluator_family_name() const
{

  // Preconditions:

  require(is_attached());

  // Body:

  string result = rep().evaluator_family_name();

  // Postconditions:

  // Exit

  return result;
}

string
fiber_bundle::section_space_schema_member::
intersection_id_space_name(const subposet& xsp, pod_index_type xhub_id)
{
  // Preconditions:

  require(xsp.state_is_read_accessible());
  require(!xsp.name().empty());
  
  // Body:

  string result;

  if(xhub_id == TOP_INDEX)
  {
    result = xsp.name();
  }
  else
  {
    result = poset_path::make_reserved_name("", xhub_id,
					    xsp.name() + "_id_space");
  }
  
  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

string
fiber_bundle::section_space_schema_member::
intersection_id_space_name(const subposet& xsp, const scoped_index& xid)
{
  // Preconditions:

  require(xsp.state_is_read_accessible());
  require(!xsp.name().empty());
  require(xid.in_scope());
  
  // Body:

  string result = intersection_id_space_name(xsp, xid.hub_pod());

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::section_dof_iterator*
fiber_bundle::section_space_schema_member::
dof_iterator(bool xis_table_dofs, int xversion) const
{
  section_dof_iterator* result = 0;

  // Preconditions:

  require(state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  // This member is conceptually abstract in this class and intended
  // to be redefined in descendants. Implemented only to
  // define the pre- and post- conditions.

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
conforms_to(const schema_poset_member& xother, bool xis_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_ancestor_of(&xother));

  // Body:

  // The dofs defined by this must agree in type and in order
  // with those defined by xother. For section_space_schema,
  // this obviously requires that the host, rep, and version
  // of this be the same as those of xother. In addition,
  // the fiber schema of this must exactly match the fiber
  // schema of xother and the initial part of the traversal of this
  // discretization must match the traversal of the xother
  // discretization. The only practical way to ensure this
  // is to require the base space of this and xother to be
  // exactly the same. Hence, section_space_schema only
  // conform if they are identical.

  result = is_same_state(&xother);

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
fiber_schema_conforms_to(const namespace_poset& xns,
                         const poset_path& xpath,
                         const poset_path& xfiber_schema_path,
                         bool xauto_access)
{
  bool result;

  // Preconditions:
  
  require(!xauto_access ? xns.state_is_read_accessible() : true);
  require(xpath.full());
  require(xns.contains_poset_member(xpath));

  /// @hack only binary schema supported.

  require(dynamic_cast<binary_section_space_schema_poset*>(&xns.member_poset(xpath)) != 0);
  require(!xauto_access ?
          xns.member_poset(xpath).state_is_read_accessible() :
          true);

  require(xns.contains_poset_member(xfiber_schema_path));
  require(!xauto_access ?
          xns.member_poset(xfiber_schema_path).state_is_read_accessible() :
          true);


  // Body:


  if(xauto_access)
  {
    xns.get_read_access();
    xns.member_poset(xpath).get_read_access();
    xns.member_poset(xfiber_schema_path).get_read_access();
  }

  binary_section_space_schema_member lschema(const_cast<namespace_poset&>(xns), xpath);

  result = schema_poset_member::conforms_to(xns,
           lschema.fiber_schema().path(),
           xfiber_schema_path,
           false);

  lschema.detach_from_state();

  if(xauto_access)
  {
    xns.release_access();
    xns.member_poset(xpath).release_access();
    xns.member_poset(xfiber_schema_path).release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::section_space_schema_member::
section_space_schema_member()
{

  // Preconditions:

  // Body:

  // The following invalidate calls are not really neccessary but serve
  // to make things clearer.

  _base_space_id = invalid_pod_index();
  _fiber_schema_id = invalid_pod_index();

  _discretization_id_space = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached() );

  ensure(!is_valid(base_space_id()));
  ensure(!is_valid(fiber_schema_id()));

  ensure(!base_space().is_attached());
  ensure(!fiber_schema().is_attached());

  // Exit:
}

void
fiber_bundle::section_space_schema_member::
make_schema_info(bool xis_table_dof)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  /// @error host is immutable; remove this member.

  not_implemented();

  // Postconditions:

  ensure(unexecutable(schema info initialized));

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_member::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Initialize inherited data members

  schema_poset_member::attach_handle_data_members();

  // Compute the component member ids.

  _base_space_id   = host()->get_base_space_id_from_index(_index.pod());
  _fiber_schema_id = host()->get_fiber_schema_id_from_index(_index.pod());

  // Attach the component handles

  _base_space.attach_to_state(&(host()->base_space()), _base_space_id);
  _fiber_schema.attach_to_state(&(host()->fiber_schema()), _fiber_schema_id);

  /// @hack section_space_schema version hack:
  /// version of this is same as version of base space.

  _base_space.put_version(_version, false);

  // Postconditions:

  ensure(base_space().is_attached());
  ensure(fiber_schema().is_attached());

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_member::
update_row_cache_without_disc_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible()); 

  // Body:

  base_space_poset& lbase_host = host()->base_space();
  const subposet& leval_sp = evaluation();
  const subposet& ldisc_sp = discretization();
  const subposet& ljims_sp = lbase_host.jims();

  // Get the disc ct from the id space.

  _discretization_ct = _discretization_id_space->ct();  

  // Try to get evaluation_ct from eval id space.

  string leval_id_space_name = intersection_id_space_name(leval_sp, _base_space_id);
  if(lbase_host.member_id_spaces(false).contains(leval_id_space_name))
  {
    _evaluation_ct = lbase_host.member_id_spaces(false).ct(leval_id_space_name);
  }
  else
  {
    _evaluation_ct = 0;

    hash_set_postorder_itr itr(_base_space, DOWN, NOT_STRICT);
    while(!itr.is_done())
    {
      pod_index_type lindex = itr.index().pod();

      if(leval_sp.contains_member(lindex))
      {
	_evaluation_ct++;
      }

      itr.next();
    }
  }
  
  // Get db from the base space.

  _db = lbase_host.db(_base_space.index());
  
  // Postconditions:

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_member::
update_row_cache_with_disc_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->base_space().state_is_read_write_accessible());

  // Body:

  base_space_poset& lbase_host = host()->base_space();
  const subposet& leval_sp = evaluation();
  const subposet& ldisc_sp = discretization();
  const subposet& ljims_sp = lbase_host.jims();

  // Traverse the down set; count the eval and disc members and find
  // the maximum dimension and client id.

  _db = 0;
  _evaluation_ct = 0;
  _discretization_ct = 0;

  // This schema is either new or changed, so we need
  // to (re)build the sequence id space.

  // Refiners extend client id space; so we need to maintain same order.
  // Do this in two steps:

  // First: find the disc members in the down set of the base and
  // store their client ids in a set, which will keep them
  // sorted in order.

  set<scoped_index::pod_type> ltop_seq_ids;
  const index_space_handle& ltop_space = ldisc_sp.id_space();

  hash_set_postorder_itr itr(_base_space, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    const scoped_index& lindex = itr.index();

    if(ljims_sp.contains_member(lindex))
    {
      int ldb = lbase_host.member_dof_tuple(lindex)->db;

      _db = (ldb > _db) ? ldb : _db;
    }

    if(leval_sp.contains_member(lindex))
    {
      _evaluation_ct++;
    }

    if(ldisc_sp.contains_member(lindex))
    {
      _discretization_ct++;
      ltop_seq_ids.insert(ltop_space.pod(lindex));
    }

    itr.next();
  }

  // Second: iterate over the set and define the new seq id space.
  // The new space will contain a subset of the members in the
  // original client id space in the same relative order as the original.

  assertion(dynamic_cast<mutable_index_space_handle*>(_discretization_id_space) != 0);

  mutable_index_space_handle* ldisc_id_space =
    reinterpret_cast<mutable_index_space_handle*>(_discretization_id_space);

  ldisc_id_space->clear();
  ldisc_id_space->reserve(_discretization_ct);

  set<pod_index_type>::iterator lseq_id_itr;
  for(lseq_id_itr = ltop_seq_ids.begin();
      lseq_id_itr != ltop_seq_ids.end();
      ++lseq_id_itr)
  {
    ldisc_id_space->push_back(ltop_space.hub_pod(*lseq_id_itr));
  }

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_member::
update_row_dof_id_space() const
{
  // Preconditions:

  // Body:

  const index_space_handle& lfiber_schema_id_space =
    fiber_schema().row_dof_id_space();

  if(_host->member_id_spaces(false).contains(row_dof_subposet_name()))
  {
    // Row dof id space already exists, set the factors.

    _row_dof_id_space =
      &_host->member_id_spaces(false).get_id_space(row_dof_subposet_name());

    reinterpret_cast<section_space_schema_jims_index_space_handle*>
      (_row_dof_id_space)->put_factors(*_discretization_id_space,
				       lfiber_schema_id_space,
				       host()->product_structure());
  }
  else
  {
    // Create the row dof id space.

    arg_list largs =
      section_space_schema_jims_index_space_state::
      make_arg_list(*_discretization_id_space,
		    lfiber_schema_id_space,
		    host()->product_structure());

    pod_index_type lspace_id =
      _host->member_id_spaces(false).
      new_secondary_state(row_dof_subposet_name(),
			  "section_space_schema_jims_index_space_state",
			  largs, false);

    _row_dof_id_space =
      &_host->member_id_spaces(false).get_id_space(lspace_id);
  }
  
  // Postconditions:

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SCHEMA_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_member::
contains_dof(pod_index_type xbase_id,
             pod_index_type xfiber_id,
             bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  pod_index_type l_id = host()->get_index_from_components(xbase_id, xfiber_id);
  result = contains_dof(l_id, xin_table_dofs);

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
contains_dof(const scoped_index& xbase_id,
             const scoped_index& xfiber_id,
             bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  return contains_dof(xbase_id.hub_pod(), xfiber_id.hub_pod());
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_member::
update_table_cache() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!host()->member_id_spaces(false).contains(table_dof_subposet_name()))
  {
    // Create the table dof id space.

    arg_list largs = array_index_space_state::make_arg_list(0);

    pod_index_type lspace_id =
      host()->member_id_spaces(false).
      new_secondary_state(table_dof_subposet_name(),
			  "array_index_space_state",
			  largs, false);

    _table_dof_id_space =
      &host()->member_id_spaces(false).get_id_space(lspace_id);

    // Populate the table dof id map.

    // The table dofs of the section space schema are the same as 
    // the table dofs of the fiber space schema and map into
    // the section space schema id space as (base bottom, fiber schema mbr).

    /// @hack Cartesian product subspace hack. Should be using product id space.
    // Assume base space id is first index, fiber schema id is second. 

    mutable_index_space_handle* ltable_dof_id_space =
      reinterpret_cast<mutable_index_space_handle*>(_table_dof_id_space);
    ltable_dof_id_space->reserve(fiber_schema().table_dof_id_space().ct());

    index_space_iterator& litr =
      fiber_schema().table_dof_id_space().get_iterator();
    while(!litr.is_done())
    {
      // Iterating over the ids of the fiber schema table dof id space
      // in host (poset) order.

      ltable_dof_id_space->insert(litr.pod(), litr.hub_pod());

      litr.next();
    }
    fiber_schema().table_dof_id_space().release_iterator(litr);
  }
  else
  {
    _table_dof_id_space =
      &host()->member_id_spaces(false).get_id_space(table_dof_subposet_name());
  }
  
  schema_poset_member::update_table_cache();

  // Postconditions:

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_member::
update_row_cache(bool xupdate_id_space) const
{
  // Preconditions:

  require(state_is_read_accessible()); // see error below

  // Body:

  base_space_poset& lbase_host = host()->base_space();

  // Declare an enum for determining what needs updated.

  enum update_type
  {
    only_row_cache,        // Update only the row cache counts.
    only_row_dof_id_space, // Update the row cache counts and row dof id space.
    all_id_spaces          // Update the row cache counts, discretization id space, and row dof id space.
  };
  
  update_type lupdate = xupdate_id_space ? all_id_spaces : only_row_cache;

  /// @error getting write access here violates policy.
  /// @todo add auto access

  lbase_host.get_read_write_access(true);

  // Release old discretization handle if one was set.

  if(_discretization_id_space != 0)
  {
    _discretization_id_space->release_id_space();
  }

  /// @todo replace this look up by something more efficient.
  /// This is just a temporary, exploratory implementation.

  string ldisc_id_space_name =
    intersection_id_space_name(discretization(), _base_space_id);

  // Assign the discretization id space.

  if(lbase_host.member_id_spaces(false).contains(ldisc_id_space_name))
  {
    _discretization_id_space =
      &lbase_host.member_id_spaces(false).get_id_space(ldisc_id_space_name);

    if((lupdate == all_id_spaces) &&
       (*_discretization_id_space == discretization().id_space()))
    {
      // The user requested that all the id spaces be update but since
      // the this member's discretization id space is the same as the
      // discretization id space of the host, only update the row id space.

      lupdate = only_row_dof_id_space;
    }
  }
  else
  {
    // Create the discretization id space.

    bool is_persistent = discretization().is_persistent();

    arg_list largs = array_index_space_state::make_arg_list(0);

    pod_index_type lspace_id =
      lbase_host.member_id_spaces(false).
      new_secondary_state(ldisc_id_space_name,
			  "array_index_space_state",
			  largs, is_persistent);

    _discretization_id_space =
      &lbase_host.member_id_spaces(false).get_id_space(lspace_id);

    if(lupdate == only_row_cache)
    {
      // The discretization id space was created, update the discretization
      // id space and the row dof id space.

      lupdate = all_id_spaces;
    }
  }

  // Make sure a row dof id space is created.

  if((lupdate == only_row_cache) &&
     !_host->member_id_spaces(false).contains(row_dof_subposet_name()))
  {
    lupdate = only_row_dof_id_space;
  }

  // Update the row cache and any id spaces needed.

  switch(lupdate)
  {
    case only_row_cache:
      update_row_cache_without_disc_id_space();
      break;

    case only_row_dof_id_space:
      update_row_cache_without_disc_id_space();
      update_row_dof_id_space();
      break;

    case all_id_spaces:
      update_row_cache_with_disc_id_space();
      update_row_dof_id_space();
      break;
  }

  lbase_host.release_access();

  // Postconditions:

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NEW DOF ACCESS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
discretization_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  const index_space_handle& result = *_discretization_id_space;

  // Postconditions:


  // Exit:

  return result;
}

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
discretization_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  const index_space_handle& result = *_discretization_id_space;

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
discretization_id_space()
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  index_space_handle& result = *_discretization_id_space;

  // Postconditions:


  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
discretization_id_space(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  index_space_handle& result = *_discretization_id_space;

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
fiber_schema_id_space(bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  const index_space_handle& result = fiber_schema().dof_id_space(xis_table_dofs);

  // Postconditions:


  // Exit:

  return result;
}

const sheaf::index_space_handle&
fiber_bundle::section_space_schema_member::
fiber_schema_id_space(bool xis_table_dofs, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  const index_space_handle& result =
    fiber_schema().dof_id_space(xis_table_dofs, xauto_access);
  
  // Postconditions:


  // Exit:

  return result;
}


sheaf::size_type
fiber_bundle::section_space_schema_member::
size(pod_index_type xdof_id, bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xis_table_dofs ? fiber_schema_id_space(xis_table_dofs).contains(xdof_id) : true);
  
  // Body:

  pod_index_type lfiber_dof_id = xdof_id;

  if(!xis_table_dofs)
  {
    pod_index_type ldisc_id;
    row_dof_id_space().product_structure<ij_product_structure>().
      tuple(xdof_id, ldisc_id, lfiber_dof_id);
  }
  
  size_type result = fiber_schema().size(lfiber_dof_id, xis_table_dofs);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
size(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  size_type result = fiber_schema().size(xfiber_dof_id, xis_table_dof);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
size(const scoped_index& xdisc_id,
     const scoped_index& xfiber_dof_id,
     bool xis_table_dof,
     bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  size_type result = fiber_schema().size(xfiber_dof_id, xis_table_dof, xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
alignment(pod_index_type xdof_id, bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xis_table_dofs ? fiber_schema_id_space(xis_table_dofs).contains(xdof_id) : true);
  
  // Body:

  pod_index_type lfiber_dof_id = xdof_id;

  if(!xis_table_dofs)
  {
    pod_index_type ldisc_id;
    row_dof_id_space().product_structure<ij_product_structure>().
      tuple(xdof_id, ldisc_id, lfiber_dof_id);
  }
  
  size_type result = fiber_schema().alignment(lfiber_dof_id, xis_table_dofs);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
alignment(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  size_type result = fiber_schema().alignment(xfiber_dof_id, xis_table_dof);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
alignment(const scoped_index& xdisc_id,
	  const scoped_index& xfiber_dof_id,
	  bool xis_table_dof,
	  bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  size_type result =
    fiber_schema().alignment(xfiber_dof_id, xis_table_dof, xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::primitive_type
fiber_bundle::section_space_schema_member::
type(pod_index_type xdof_id, bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xis_table_dofs ? fiber_schema_id_space(xis_table_dofs).contains(xdof_id) : true);
  
  // Body:

  pod_index_type lfiber_dof_id = xdof_id;

  if(!xis_table_dofs)
  {
    pod_index_type ldisc_id;
    row_dof_id_space().product_structure<ij_product_structure>().
      tuple(xdof_id, ldisc_id, lfiber_dof_id);
  }
  
  primitive_type result = fiber_schema().type(lfiber_dof_id, xis_table_dofs);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::primitive_type
fiber_bundle::section_space_schema_member::
type(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  primitive_type result = fiber_schema().type(xfiber_dof_id, xis_table_dof);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::primitive_type
fiber_bundle::section_space_schema_member::
type(const scoped_index& xdisc_id,
     const scoped_index& xfiber_dof_id,
     bool xis_table_dof,
     bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  primitive_type result =
    fiber_schema().type(xfiber_dof_id, xis_table_dof, xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
offset(pod_index_type xdof_id, bool xis_table_dof) const
{
  size_type result;
  
  // Preconditions:

  require(state_is_read_accessible());
  require(xis_table_dof ? fiber_schema_id_space(xis_table_dof).contains(xdof_id) : true);

  // Body:

  if(xis_table_dof)
  {
    result = fiber_schema().offset(xdof_id, true);
  }
  else
  {
    pod_index_type lfiber_dof_id, ldisc_id;
    row_dof_id_space().product_structure<ij_product_structure>().
      tuple(xdof_id, ldisc_id, lfiber_dof_id);

    result = offset(ldisc_id, lfiber_dof_id, false);
  }
  

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
offset(pod_index_type xdisc_id, pod_index_type xfiber_dof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(xis_table_dof).contains(xfiber_dof_id));
  
  // Body:

  size_type result;

  if(xis_table_dof)
  {
    result = fiber_schema().offset(xfiber_dof_id, true);
  }
  else
  {
    result = fiber_size()*xdisc_id + fiber_schema().offset(xfiber_dof_id, false);
  }

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
offset(const scoped_index& xdisc_id,
       const scoped_index& xfiber_dof_id,
       bool xis_table_dof,
       bool xauto_access) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(xis_table_dof, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  pod_index_type ldisc_id = _discretization_id_space->pod(xdisc_id);
  pod_index_type lfiber_dof_id =
    fiber_schema_id_space(xis_table_dof).pod(xfiber_dof_id);
  
  size_type result = offset(ldisc_id, lfiber_dof_id, xis_table_dof);

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
fiber_size() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  size_type result = fiber_schema().dof_tuple_ub(false);

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
fiber_size(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  size_type result = fiber_size();

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
component_size(pod_index_type xfiber_dof_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_id_space(false).contains(xfiber_dof_id));
  
  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  size_type result =
    fiber_schema().size(xfiber_dof_id, false)*_discretization_ct;

  // Postconditions:


  // Exit:

  return result;
}

sheaf::size_type
fiber_bundle::section_space_schema_member::
component_size(const scoped_index& xfiber_dof_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(fiber_schema_id_space(false, xauto_access).contains(xfiber_dof_id));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  pod_index_type lfiber_dof_id =
    fiber_schema_id_space(false).pod(xfiber_dof_id);
  size_type result = component_size(lfiber_dof_id);

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
fiber_bundle::section_space_schema_member::
get_ext_id(const string& xid_space_name) const
{
  // Preconditions:

  require(state_is_read_accessible());

  /// @hack product subposet hack, ver 2.
  /// Section space schema member external ids are really base space external ids.

  // Can't support the following precondition:

  //  require(precondition_of(host()->get_ext_id(index(), xid_space_name)));

  // Instead:

  require(precondition_of(host()->base_space().get_ext_id(base_space_id(), xid_space_name)));

  /// @error product subposet hack, ver 2
  /// The base space schema member can not be a implicit member or the
  /// host()->base_space().get_ext_id(base_space_id(), xid_space_name, false)
  /// will violate a precondition.  The following precondition has been added
  /// to publish this error.

  require(host()->base_space().is_explicit_member(base_space_id()) ||
	  host()->base_space().is_block_member(base_space_id()));

  // Body:

  pod_index_type result =
    host()->base_space().get_ext_id(base_space_id(), xid_space_name, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


fiber_bundle::schema_poset_member&
fiber_bundle::section_space_schema_member::
unrestricted_schema()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Memebers of this class don't have dof tuples,
  // so the unrestricted schema is always the schema of the host.

  schema_poset_member& result = host()->schema();

  // Postconditions:

  ensure(result.is_same_state(&(host()->schema())));

  // Exit

  return result;
}

const fiber_bundle::schema_poset_member&
fiber_bundle::section_space_schema_member::
unrestricted_schema() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Memebers of this class don't have dof tuples,
  // so the unrestricted schema is always the schema of the host.

  const schema_poset_member& result = host()->schema();

  // Postconditions:

  ensure(result.is_same_state(&(host()->schema())));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// DOWN SET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::section_space_schema_member::
down_ct(pod_index_type xfilter_index) const
{
  int result = 0;

  // Preconditions:

  // Body:

  result = base_space().down_ct() * fiber_schema().down_ct();

  // Postconditions:

  ensure(result > 0 );

  // Exit

  return result;
}

sheaf::subposet*
fiber_bundle::section_space_schema_member::
down() const
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  result = new subposet(host());
  down_pa(result);


  // Postconditions:

  require(result != 0);
  require(postcondition_of(down_pa));

  // Exit

  return result;
}

void
fiber_bundle::section_space_schema_member::
down_pa(subposet* result) const
{

  // Preconditions:

  // Body:

  not_implemented();


  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is down set
                        of this));

  // Exit

  return;
}

int
fiber_bundle::section_space_schema_member::
up_ct(pod_index_type xfilter_index) const
{
  int result = 0;

  // Preconditions:

  // Body:

  result = base_space().up_ct() * fiber_schema().up_ct();

  // Postconditions:

  ensure(result > 0 );

  // Exit

  return result;
}

sheaf::subposet*
fiber_bundle::section_space_schema_member::
up() const
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  result = new subposet(host());
  up_pa(result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(up_pa));

  // Exit

  return result;
}

void
fiber_bundle::section_space_schema_member::
up_pa(subposet* result) const
{

  // Preconditions:

  // Body:

  // Traverse up set, inserting members into result

  /// @todo implement this function

  not_implemented();

  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is up set
                        of this));

  // Exit

  return;
}

int
fiber_bundle::section_space_schema_member::
jim_ct() const
{
  int result = 0;

  // Preconditions:

  // Body:

  result = base_space().jim_ct() * fiber_schema().jim_ct();

  // Postconditions:

  ensure(is_jem(&(host()->bottom())) ? result == 0 : result > 0 );

  // Exit

  return result;
}

sheaf::subposet*
fiber_bundle::section_space_schema_member::
jims()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  result = new subposet(host());
  jims_pa(result);


  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(jims_pa));

  // Exit

  return result;
}

void
fiber_bundle::section_space_schema_member::
jims_pa(subposet* result)
{

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is jims set
                        of this));

  // Exit

  return;
}

int
fiber_bundle::section_space_schema_member::
maximal_jim_ct() const
{
  int result = 0;

  // Preconditions:

  // Body:

  result = base_space().maximal_jim_ct() * fiber_schema().maximal_jim_ct();

  // Postconditions:

  ensure(is_jem(&(host()->bottom())) ? result == 0 : result > 0 );

  // Exit

  return result;
}


sheaf::subposet*
fiber_bundle::section_space_schema_member::
maximal_jims()
{
  subposet* result;

  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  not_implemented();

  result = new subposet(host());
  maximal_jims_pa(result);


  // Postconditions:

  ensure(has_same_host(result));
  ensure(postcondition_of(maximal_jims_pa));

  // Exit

  return result;
}

void
fiber_bundle::section_space_schema_member::
maximal_jims_pa(subposet* result) const
{
  // Preconditions:

  require(has_same_host(result));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(result->invariant());
  ensure(unexecutable(result is union of maximal_jims of this with old result));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET ALGEBRA FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_member::
p_join_pa(abstract_poset_member* other, abstract_poset_member* result) const
{
  // Preconditions:

  require(has_same_host(other));
  require(!result->is_attached());
  // this precondition ensures the attachment below will not
  // leave an orphan temporary in the poset
  require(result->is_ancestor_of(this));
  require(state_is_read_accessible());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(unexecutable(result is least upper bound in host of this and other));

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_member::
p_meet_pa(abstract_poset_member* other, abstract_poset_member* result)
{
  // Preconditions:

  require(has_same_host(other));
  require(!result->is_attached());
  // this precondition ensures the attachment below will not
  // leave an orphan temporary in the poset
  require(result->is_ancestor_of(this));
  require(state_is_read_accessible());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(unexecutable(result is least upper bound in host of this and other));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COMPONENT INDEX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_member::
put_version(int xversion, bool xunalias)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(has_version(xversion));
  require(!xunalias ? xversion != CURRENT_MEMBER_VERSION : true);

  // Body:

  schema_poset_member::put_version(xversion, xunalias);

  /// @hack section_space_schema version hack:
  /// version of this is same as version of base space.

  _base_space.put_version(xversion, xunalias);

  // Postconditions:

  ensure(xunalias ?
         version(false) == unaliased_version(xversion) :
         version(false) == xversion);

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_member::
attach_to_state(pod_index_type xbase_space_id,
		pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->base_space().contains_member(xbase_space_id));
  require(host()->fiber_schema().contains_member(xfiber_schema_id));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(base_space_id() == xbase_space_id);
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id);
  ensure(fiber_schema().is_attached());

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_member::
attach_to_state(const scoped_index& xbase_space_id,
		const scoped_index& xfiber_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->base_space().contains_member(xbase_space_id));
  require(host()->fiber_schema().contains_member(xfiber_schema_id));

  // Body:

  attach_to_state(xbase_space_id.hub_pod(),
		  xfiber_schema_id.hub_pod());

  // Postconditions:

  ensure(base_space_id() == xbase_space_id.hub_pod());
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id.hub_pod());
  ensure(fiber_schema().is_attached());

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_member::
attach_to_state(const section_space_schema_poset* xhost,
		pod_index_type xbase_space_id,
		pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(xhost->base_space().contains_member(xbase_space_id));
  require(xhost->fiber_schema().contains_member(xfiber_schema_id));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(base_space_id() == xbase_space_id);
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id);
  ensure(fiber_schema().is_attached());

  // Exit:
  return;
}

void
fiber_bundle::section_space_schema_member::
attach_to_state(const section_space_schema_poset* xhost,
		const scoped_index& xbase_space_id,
		const scoped_index& xfiber_schema_id)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(xhost->base_space().contains_member(xbase_space_id));
  require(xhost->fiber_schema().contains_member(xfiber_schema_id));

  // Body:

  attach_to_state(xhost,
		  xbase_space_id.hub_pod(),
		  xfiber_schema_id.hub_pod());

  // Postconditions:

  ensure(base_space_id() == xbase_space_id.hub_pod());
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id.hub_pod());
  ensure(fiber_schema().is_attached());

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_member::
detach_from_state()
{
  // Preconditions:

  // Body:

  _base_space.detach_from_state();
  _base_space_id = _base_space.index().pod();
  _fiber_schema.detach_from_state();
  _fiber_schema_id = _fiber_schema.index().pod();

  schema_poset_member::detach_from_state();


  // Postconditions:

  ensure(!is_attached());
  ensure(!base_space().is_attached());
  ensure(!fiber_schema().is_attached());

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HOST POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_member::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const section_space_schema_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::section_space_schema_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const section_space_schema_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(schema_poset_member::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    invariance(is_attached() == base_space().is_attached());
    invariance(is_attached() == fiber_schema().is_attached());

    /// @issue what are the invariants for this class
    /// @todo implement section_space_schema_member::invariant() const

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEBUGGING FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::section_space_schema_member::
to_stream(ostream& xos) const
{
  // Preconditions:


  // Body:

  xos << *this;

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

ostream& fiber_bundle::operator << (ostream &os, section_space_schema_member& p)
{

  // Preconditions:

  // Body:

  if (p.is_attached())
  {
    p.get_read_access();
    p.disable_invariant_check();
    os << "member:"
    << " host = \'" << p.host()->name() << "\'"
    << " index = " << p.index().pod()
    << " name = \'" << p.name() << '\''
    << " version= " << p.version(false)
    << " unaliased version= " << p.version()
    << endl;

    os << "base: member index = " << p.base_space().index().hub_pod()
    << " '" << p.base_space().name() << "'"
    << " in poset '" << p.base_space().host()->name() << "'"
    << endl
    << "fiber space is poset '" << p.fiber_space().name() << "'"
    << endl;

    p.release_access();
    p.enable_invariant_check();

  }
  else
  {
    os << "member: host = \'\'' index = -1 name = \'\''"
    << endl;
  }

  // Exit:

  return os;
}

