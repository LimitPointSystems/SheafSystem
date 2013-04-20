//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class eval_iterator


#include "eval_iterator.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "eval_family.h"
#include "sec_rep_descriptor.h"
#include "section_evaluator.h"
#include "section_space_schema_member.h"
#include "section_space_schema_poset.h"
#include "sec_vd.h"
#include "subposet_member_iterator.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

namespace
{
  ///
  /// The initial size of the downset collection buffers.
  ///
  const int BUFFER_UB = 16;
}

fiber_bundle::eval_iterator::
eval_iterator()
    : depth_first_iterator(),
    _discretization_members(BUFFER_UB),
    _non_discretization_members(BUFFER_UB)
{

  // Preconditions:

  // Body:

  initialize_order(BIORDER);
  _schema_anchor = 0;
  _down_set_collection_enabled = false;
  _evaluators = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}

fiber_bundle::eval_iterator::
eval_iterator(const eval_iterator& xother)
    : depth_first_iterator(xother),
    _evaluators(0),
    _discretization_members(BUFFER_UB),
    _non_discretization_members(BUFFER_UB)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

fiber_bundle::eval_iterator::
~eval_iterator()
{
  // Preconditions:

  // Body:

  if(_schema_anchor != 0)
  {
    _schema_anchor->detach_from_state();
    delete _schema_anchor;
  }

  if(_evaluators != 0)
    delete _evaluators;

  // Postconditions:

}

bool
fiber_bundle::eval_iterator::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const eval_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::eval_iterator*
fiber_bundle::eval_iterator::
clone() const
{
  // Preconditions:

  // Body:

  eval_iterator* result = new eval_iterator;

  // Postconditions:

  //ensure(invariant());
  ensure(result != 0);
  ensure(!result->is_initialized());

  // Exit

  return result;
}

bool
fiber_bundle::eval_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(depth_first_iterator::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    invariance(order() == BIORDER);
    invariance(is_initialized() ?
               anchor().is_same_state(&(schema_anchor().base_space())) :
               true);
    invariance(unexecutable(evaluation subposet is above discretization subposet));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// OTHER CONSTRUCTORS


fiber_bundle::eval_iterator::
eval_iterator(const section_space_schema_member& xschema_anchor, bool xvisit_once)
    : depth_first_iterator(),
    _discretization_members(BUFFER_UB),
    _non_discretization_members(BUFFER_UB)
{

  // Preconditions:

  require(xschema_anchor.state_is_read_accessible());

  // Body:

  initialize_order(BIORDER);
  _schema_anchor = 0;
  _down_set_collection_enabled = false;
  _evaluators = 0;
  put_visit_once(xvisit_once);

  put_schema_anchor(xschema_anchor);

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(schema_anchor().is_same_state(&xschema_anchor));
  ensure(schema_anchor().is_same_type(&xschema_anchor));
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));
  ensure(visit_once() == xvisit_once);

  return;
}


// ITERATOR INTERFACE

//$$SCRIBBLE jebutler const correctness

bool
fiber_bundle::eval_iterator::
is_initialized() const
{
  // Preconditions:

  // Body:

  bool result =
    depth_first_iterator::is_initialized() &&
    (_schema_anchor != 0) &&
    (_base_space != 0);

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::eval_iterator::
force_is_done()
{
  // Preconditions:

  // Body:

  // Clear the down set collection buffers.

  _down_set_collection_enabled = false;
  _discretization_members.set_ct(0);
  _non_discretization_members.set_ct(0);
  _maximal_eval_id.invalidate();

  depth_first_iterator::force_is_done();

  // Postconditions:

  ensure(invariant());
  ensure(is_done());

  // Exit

  return;
}

void
fiber_bundle::eval_iterator::
next(bool xtruncate)
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool ltruncate = xtruncate;

  // Continue traversing the graph until the traversal is done
  // or we are in the postvisit action of an evaluation member
  // and return to the client.

  depth_first_iterator::next(ltruncate);

  while(!is_done())
  {
    if(action() == PREVISIT_ACTION)
    {

      // The evaluation, and discretization are not necessarily distinct.
      // So we have to test each independently of the other.

      bool lnone_of_the_above = true;

      if(!_maximal_eval_id.is_valid() && _eval_sp->contains_member(index()))
      {
        // This member is an evaluation member

        // If discretization is "__vertices", determine if we need to
        // reverse the 0 and 1 discretization member ids for 2d "elements"
        // (shell elements included).

        if(_vertex_discretization)
        {
          pod_index_type ltuple_id =
	    _base_space->member_dof_tuple_id(index().pod(), false);

          if(is_valid(ltuple_id))
          {
            // This member has a dof tuple; it is a jim
            // (i.e. it is not a zone that has been refined into subzones).

            int ltype_id = _base_space->row_dof_tuple(ltuple_id)->type_id;

            /// @hack shouldn't have these hard-wired,
            /// should look them up when iterator created.

            _disc_reversal_enabled =
              (ltype_id == 5) || (ltype_id == 8) || (ltype_id == 9);

          }
        }

        // Reset the down set collection buffers and turn on collection.

        _discretization_members.set_ct(0);
        _non_discretization_members.set_ct(0);
        _down_set_collection_enabled = true;

        _evaluator_id = index();
        _maximal_eval_id = index();

        // Do not truncate, continue descending.

        ltruncate = false;

        lnone_of_the_above = false;
      }

      if(_disc_sp->contains_member(index()))
      {
        // This is a discretization member.
        // Invariant ensures discretization is below evaluation,
        // so down set collection must be enabled.
        // Enter this member in the discretization collection.

        _discretization_members.push_back(index());

        if(_disc_reversal_enabled)
        {
          // If 2D, check orientation of first member of upper cover:
          //
          // We assume that the current evaluator is 2-D, that its
          // downset contains edges and vertices, and that the
          // current discretization point is a vertex.
          //
          // The first evaluator to contain the edge which contains the
          // current discretization point is the evaluator which constructed
          // that edge, and it constructed that edge in a "positive"
          // orientation wrt that evaluator.  An edge in a 2-d space
          // separates that space into 2 parts.  So at most 1 other
          // evaluator can share that edge and, if it exists, that evaluator
          // views the edge as "negatively" oriented.  In addition,
          // that evaluator will be the second evaluator in the upper
          // cover of that edge.

          // greater_index() refers to the edge containing this discretization
          // point in the path from the current evaluator.  If the current
          // evaluator is the first evaluator in that edge's upper cover, then
          // it constructed the edge, and the edge is in the positive orientation.
          // Otherwise, the current evaluator did not construct the edge,
          // the edge is negatively oriented, and the discretization member
          // order should be reversed.

          // Only swap _discretization_members if the base space is 2D.

          pod_index_type first_eval = _anchor->host()->first_cover_member(UPPER, greater_index());
          bool is_reversed = (_evaluator_id != first_eval);

          if(is_reversed && _discretization_members.ct() == 2)
          {
            const scoped_index& save = _discretization_members[0];
            _discretization_members[0] = _discretization_members[1];
            _discretization_members[1] = save;
          }

        }

        // No need to go below this member; truncate.

        ltruncate = true;

        lnone_of_the_above = false;
      }

      if(lnone_of_the_above)
      {
        // This member is neither an eval member nor a disc member.

        if(_down_set_collection_enabled)
        {
          // Enter this member in the non-discretization collection.

          _non_discretization_members.push_back(index());
        }

        // Do not truncate, continue descending.

        ltruncate = false;
      }
    }
    else if(action() == POSTVISIT_ACTION)
    {
      if(_maximal_eval_id ==~ index())
      {
        _maximal_eval_id.invalidate();

        // Postvisit of eval member;
        // we are done iterating over discretization members
        // associated with this evaluation member;
        // return to the client with the discretization collection.

        // Turn off down set collection.

        _down_set_collection_enabled = false;

        // Reinitialize discretization reversal.

        _disc_reversal_enabled = false;

        // Clear the has visited markers for the down set

        for(int i=0; i<_discretization_members.ct(); ++i)
        {
          put_has_visited(_discretization_members[i], false);
        }

        for(int i=0; i<_non_discretization_members.ct(); ++i)
        {
          put_has_visited(_non_discretization_members[i], false);
        }

        // Return to the client.

        break;
      }
      else
      {
        // Not an evaluation member; nothing to do.
        // Continue traversal.
      }

      // If we invoke depth_first_iterator::next() from the postvisit action,
      // the truncation flag will be ignored, since you can only truncate
      // in the previsit action. But just to be specific, we'll set it false no
      // matter what we've done here.

      ltruncate = false;
    }
    else
    {
      post_fatal_error_message("unrecognized action");
    }

    depth_first_iterator::next(ltruncate);
  } // end while(!is_done())

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() ? action() == POSTVISIT_ACTION : true);
  ensure(!is_done() ? schema_anchor().evaluation().contains_member(index()) : true);

  // Exit

  return;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::eval_iterator::
schema_anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  section_space_schema_member& result = *_schema_anchor;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::eval_iterator::
schema_anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  section_space_schema_member& result = *_schema_anchor;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::eval_iterator::
put_schema_anchor(const section_space_schema_member& xschema_anchor)
{

  // Preconditions:

  require(xschema_anchor.state_is_read_accessible());
  require(xschema_anchor.base_space().schema().conforms_to(base_space_member::standard_schema_path()));

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  force_is_done();

  // Now (re)initialize.

  // Set the schema anchor.

  initialize_schema_anchor(xschema_anchor);

  // Set the anchor, has_visited markers and filter..

  initialize_traversal(_schema_anchor->base_space());

  // Set the local copies of various schema variables.

  put_schema_variables();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().is_same_state(&(xschema_anchor.base_space())));
  ensure(anchor().is_same_type(&(xschema_anchor.base_space())));
  ensure(anchor().version() == xschema_anchor.base_space().version());
  ensure(filter().index() == anchor().version_index());
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);
  ensure(schema_anchor().is_same_state(&xschema_anchor));
  ensure(schema_anchor().is_same_type(&xschema_anchor));
  ensure(schema_anchor().version() == xschema_anchor.version());

  return;
}

void
fiber_bundle::eval_iterator::
put_schema_anchor(pod_index_type xschema_anchor_index)
{

  // Preconditions:

  require(is_initialized());
  require(schema_anchor().state_is_read_accessible());
  require(schema_anchor().host()->contains_member(xschema_anchor_index));
  require(schema_anchor().base_space().schema().conforms_to(base_space_member::standard_schema_path()));

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);
  define_old_variable(scoped_index old_filter_index = filter().index());
  define_old_variable(int old_anchor_version = anchor().version());
  define_old_variable(int old_schema_anchor_version = schema_anchor().version());

  disable_invariant_check();

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  force_is_done();

  // Now reinitialize.

  // Set the schema anchor.

  _schema_anchor->attach_to_state(xschema_anchor_index);

  // Set the base space.

  _base_space = &_schema_anchor->host()->base_space();

  // Set the anchor.

  initialize_traversal(_schema_anchor->base_space_id());

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() == schema_anchor().base_space_id());
  ensure(anchor().version() == old_anchor_version);
  ensure(filter().index() == old_filter_index);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);
  ensure(schema_anchor().index() == xschema_anchor_index);
  ensure(schema_anchor().version() == old_schema_anchor_version);

  // Exit

  return;
}

void
fiber_bundle::eval_iterator::
put_schema_anchor(const scoped_index& xschema_anchor_index)
{

  // Preconditions:

  require(is_initialized());
  require(schema_anchor().state_is_read_accessible());
  require(schema_anchor().host()->contains_member(xschema_anchor_index));
  require(schema_anchor().base_space().schema().conforms_to(base_space_member::standard_schema_path()));

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);
  define_old_variable(scoped_index old_filter_index = filter().index());
  define_old_variable(int old_anchor_version = anchor().version());
  define_old_variable(int old_schema_anchor_version = schema_anchor().version());

  put_schema_anchor(xschema_anchor_index.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(is_done());
  ensure(anchor().index() == schema_anchor().base_space_id());
  ensure(anchor().version() == old_anchor_version);
  ensure(filter().index() == old_filter_index);
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);
  ensure(schema_anchor().index() ==~ xschema_anchor_index);
  ensure(schema_anchor().version() == old_schema_anchor_version);

  // Exit

  return;
}

fiber_bundle::base_space_poset&
fiber_bundle::eval_iterator::
base_space()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  base_space_poset& result = *_base_space;

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::base_space_poset&
fiber_bundle::eval_iterator::
base_space() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  const base_space_poset& result = *_base_space;

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::eval_iterator::
db() const
{
  int result;

  // Preconditions:

  require(!is_done());

  // Body:

  result = _base_space->db(index());

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}


sheaf::pod_index_type
fiber_bundle::eval_iterator::
type_id() const
{
  pod_index_type result;

  // Preconditions:

  require(!is_done());

  // Body:

  result = _base_space->type_id(index());

  // Postconditions:


  // Exit:

  return result;
}


sheaf::scoped_index
fiber_bundle::eval_iterator::
client_id() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  scoped_index result(*_eval_id_space, index());

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::section_evaluator&
fiber_bundle::eval_iterator::
evaluator()
{
  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  // The section space schema invariant ensures that the evaluator family
  // is compatible with the base space and hence the following call to
  // eval_family::member returns a non-void evaluator.

  section_evaluator& result = *_evaluators->member(type_id());

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_evaluator&
fiber_bundle::eval_iterator::
evaluator() const
{
  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  // The section space schema invariant ensures that the evaluator family
  // is compatible with the base space and hence the following call to
  // eval_family::member returns a non-void evaluator.

  section_evaluator& result = *_evaluators->member(type_id());

  // Postconditions:

  // Exit

  return result;
}

sheaf::block<sheaf::scoped_index>&
fiber_bundle::eval_iterator::
discretization_members()
{
  // Preconditions:

  require(!is_done());

  // Body:
  block<scoped_index>& result = _discretization_members;

  // Postconditions:

  // Exit

  return result;
}

const sheaf::block<sheaf::scoped_index>&
fiber_bundle::eval_iterator::
discretization_members() const
{
  // Preconditions:

  require(!is_done());

  // Body:
  const block<scoped_index>& result = _discretization_members;

  // Postconditions:

  // Exit

  return result;
}

sheaf::scoped_index
fiber_bundle::eval_iterator::
discretization_client_id(size_type xi)
{
  // Preconditions:

  require(!is_done());
  require((0 <= xi) && (xi < discretization_members().ct()));

  // Body:

  scoped_index result(*_disc_id_space, _discretization_members[xi]);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::eval_iterator::
gather_dofs(const sec_vd& xsec, block<sec_vd::dof_type>& xdofs)
{
  // Preconditions:

  require(!is_done());
  require(xsec.state_is_read_accessible());

  // Body:

  block<scoped_index>& ldisc_mbrs = discretization_members();

  size_type ldisc_mbr_ct = ldisc_mbrs.ct();
  int ldf                = xsec.schema().df();
  size_type ldof_ct      = ldf*ldisc_mbr_ct;

  size_type old_xdofs_ct = xdofs.ct();
  size_type lnew_xdofs_ct = old_xdofs_ct + ldof_ct;
  xdofs.reserve(lnew_xdofs_ct);
  xdofs.set_ct(lnew_xdofs_ct);

  // Gather the dofs by discretization member.

  size_type ldof_index = old_xdofs_ct;
  for(int i=0; i<ldisc_mbr_ct; ++i)
  {
    xsec.get_fiber(ldisc_mbrs[i], &xdofs[ldof_index],
		   ldf*sizeof(sec_vd::dof_type), false);
    ldof_index += ldf;
  }

  // Postconditions:

  ensure(xdofs.ct() ==
         (old_xdofs_ct + xsec.schema().df()*discretization_members().ct()));

  // Exit:

  return;
}


void
fiber_bundle::eval_iterator::
scatter_dofs(sec_vd& xsec, const block<sec_vd::dof_type>& xdofs, size_type xindex)
{
  // Preconditions:

  require(!is_done());
  require(xsec.state_is_read_write_accessible());
  require(xdofs.ub() >= xindex + xsec.schema().df()*discretization_members().ct());

  // Body:

  block<scoped_index>& ldisc_mbrs = discretization_members();

  size_type ldisc_mbr_ct = ldisc_mbrs.ct();
  int ldf                = xsec.schema().df();
  size_type ldof_ct      = ldf*ldisc_mbr_ct;

  size_type ldof_index = xindex;

  // Gather the dofs by discretization member.

  for(int i=0; i<ldisc_mbr_ct; ++i)
  {
    xsec.put_fiber(ldisc_mbrs[i], &xdofs[ldof_index],
		   ldf*sizeof(sec_vd::dof_type), false);
    ldof_index += ldf;
  }

  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// PROTECTED MEMBER FUNCTIONS
// ===========================================================

void
fiber_bundle::eval_iterator::
initialize_schema_anchor(const section_space_schema_member& xschema_anchor)
{
  // Preconditions:

  require(xschema_anchor.state_is_read_accessible());
  require(is_done());

  // Body:

  // Allocate the schema anchor if needed.

  if(_schema_anchor == 0)
  {
    _schema_anchor = xschema_anchor.clone();
  }
  else if(!_schema_anchor->is_same_type(&xschema_anchor))
  {
    _schema_anchor->detach_from_state();
    delete _schema_anchor;
    _schema_anchor = xschema_anchor.clone();
  }

  // Set the schema anchor.

  _schema_anchor->attach_to_state(&xschema_anchor);

  // Set the base space.

  _base_space = &_schema_anchor->host()->base_space();

  // Postconditions:

  // Can not ensure invariant because anchor has not been
  // reset to base space of schema anchor yet.

  ensure(is_done());
  ensure(_schema_anchor->is_same_state(&xschema_anchor));
  ensure(_schema_anchor->version() == xschema_anchor.version());
  ensure(_schema_anchor->is_same_type(&xschema_anchor));

  // Exit

  return;
}

void
fiber_bundle::eval_iterator::
put_schema_variables()
{
  // Preconditions:

  require(schema_anchor().state_is_read_accessible());

  // Body:

  // Initialize access to schema subposets.

  _eval_sp = &schema_anchor().evaluation();
  _disc_sp = &schema_anchor().discretization();

  // Initialize data members used in discretization reversal.

  _disc_reversal_enabled = false;
  _vertex_discretization = (schema_anchor().discretization().name() == "__vertices");

  // Initialize access to client id spaces.

  _eval_id_space = &schema_anchor().evaluation().id_space();
  _disc_id_space = &schema_anchor().discretization().id_space();

  // Get the proper evaluator family.

  if(_evaluators != 0)
    delete _evaluators;

  _evaluators =
    eval_family::new_family(schema_anchor().evaluator_family_name(),
                            *schema_anchor().name_space());

  // Postconditions:


  // Exit:

  return;
}
