//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class field_eval_iterator


#include "field_eval_iterator.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "eval_family.h"
#include "sec_rep_descriptor.h"
#include "section_evaluator.h"
#include "section_space_schema_member.h"
#include "section_space_schema_poset.h"
#include "sec_ed_invertible.h"
#include "sec_vd.h"
#include "std_limits.h"
#include "subposet_member_iterator.h"
#include "field_vd.h"

using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT 1

//const
//int
//fields::field_eval_iterator::BUFFER_UB;

// ===========================================================
// FIELD_EVAL_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::field_eval_iterator::
field_eval_iterator(const field_vd& xfield)
    : depth_first_iterator(),
    _coordinate_discretization_members(BUFFER_UB),
    _property_discretization_members(BUFFER_UB),
    _non_discretization_members(BUFFER_UB)
{

  // Preconditions:

  require(xfield.state_is_read_accessible());
  require(xfield.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xfield.property().schema().base_space().is_same_state(&xfield.coordinates().schema().base_space()));
  require(xfield.same_evaluation());

  // Body:

  disable_invariant_check();

  // Initialize the coordinate field features.

  initialize_coordinate_schema(xfield.coordinates().schema());

  // Initialize the property field features.

  initialize_property_schema(xfield.property().schema());

  // Initialize the connectivity correction trick.

  initialize_discretization_order_correction();

  // Initialize the inherited iterator features

  initialize_order(BIORDER);
  initialize_traversal(_coordinate_schema_anchor->base_space());
  reset();

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinate_schema_anchor().is_same_state(&xfield.coordinates().schema()));
  ensure(coordinate_schema_anchor().is_same_type(&xfield.coordinates().schema()));
  ensure(coordinate_schema_anchor().version() == xfield.coordinates().schema().version());
  ensure(property_schema_anchor().is_same_state(&xfield.property().schema()));
  ensure(property_schema_anchor().is_same_type(&xfield.property().schema()));
  ensure(property_schema_anchor().version() == xfield.property().schema().version());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


fields::field_eval_iterator::
field_eval_iterator(
  const section_space_schema_member& xcoordinate_schema_anchor,
  const section_space_schema_member& xproperty_schema_anchor)
    : depth_first_iterator(),
    _coordinate_discretization_members(BUFFER_UB),
    _property_discretization_members(BUFFER_UB),
    _non_discretization_members(BUFFER_UB)
{

  // Preconditions:

  require(xcoordinate_schema_anchor.state_is_read_accessible());
  require(xcoordinate_schema_anchor.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xproperty_schema_anchor.state_is_read_accessible());
  require(xproperty_schema_anchor.base_space().is_same_state(&xcoordinate_schema_anchor.base_space()));
  require(xproperty_schema_anchor.evaluation().is_same_state(&xcoordinate_schema_anchor.evaluation()));

  // Body:

  disable_invariant_check();

  // Initialize the coordinate field features.

  initialize_coordinate_schema(xcoordinate_schema_anchor);

  // Initialize the property field features.

  initialize_property_schema(xproperty_schema_anchor);

  // Initialize the connectivity correction trick.

  initialize_discretization_order_correction();

  // Initialize the inherited iterator features

  initialize_order(BIORDER);
  initialize_traversal(_coordinate_schema_anchor->base_space());
  reset();

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinate_schema_anchor().is_same_state(&xcoordinate_schema_anchor));
  ensure(coordinate_schema_anchor().is_same_type(&xcoordinate_schema_anchor));
  ensure(coordinate_schema_anchor().version() == xcoordinate_schema_anchor.version());
  ensure(property_schema_anchor().is_same_state(&xproperty_schema_anchor));
  ensure(property_schema_anchor().is_same_type(&xproperty_schema_anchor));
  ensure(property_schema_anchor().version() == xproperty_schema_anchor.version());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


fields::field_eval_iterator::
~field_eval_iterator()
{
  // Preconditions:

  // Body:

  _coordinate_schema_anchor->detach_from_state();
  delete _coordinate_schema_anchor;

  _property_schema_anchor->detach_from_state();
  delete _property_schema_anchor;

  _evaluation.detach_from_state();

  delete _property_has_been_visited;

  // Postconditions:

}

fiber_bundle::section_space_schema_member&
fields::field_eval_iterator::
coordinate_schema_anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  section_space_schema_member& result = *_coordinate_schema_anchor;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::section_space_schema_member&
fields::field_eval_iterator::
property_schema_anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  section_space_schema_member& result = *_property_schema_anchor;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::base_space_poset&
fields::field_eval_iterator::
base_space() const
{

  // Preconditions:


  // Body:

  const base_space_poset& result = *_base_space;

  // Postconditions:

  ensure(result.is_same_state(coordinate_schema_anchor().base_space().host()));
  ensure(result.is_same_state(property_schema_anchor().base_space().host()));

  // Exit:

  return result;
}

const sheaf::subposet&
fields::field_eval_iterator::
evaluation() const
{

  // Preconditions:


  // Body:

  const subposet& result = _evaluation;

  // Postconditions:

  ensure(result.is_same_state(&coordinate_schema_anchor().evaluation()));
  ensure(result.is_same_state(&property_schema_anchor().evaluation()));

  // Exit:

  return result;
}

int
fields::field_eval_iterator::
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
fields::field_eval_iterator::
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

string
fields::field_eval_iterator::
type_name() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  /// @hack this signature and implementation
  /// forces an unnecessary copy (or three).

  string result(_base_space->type_name(index()));

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::section_evaluator&
fields::field_eval_iterator::
coordinate_evaluator() const
{
  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  // The section space schema invariant ensures that the evaluator family
  // is compatible with the base space and hence the following call to
  // eval_family::member returns a non-void evaluator.

  section_evaluator& result =
    *_coordinate_evaluators->member(type_id());

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::section_evaluator&
fields::field_eval_iterator::
property_evaluator() const
{
  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  // The section space schema invariant ensures that the evaluator family
  // is compatible with the base space and hence the following call to
  // eval_family::member returns a non-void evaluator.

  section_evaluator& result =
    *_property_evaluators->member(type_id());

  // Postconditions:

  // Exit

  return result;
}

const sheaf::block<sheaf::scoped_index>&
fields::field_eval_iterator::
coordinate_discretization_members() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  const block<scoped_index>& result = _coordinate_discretization_members;

  // Postconditions:

  // Exit

  return result;
}

const sheaf::block<sheaf::scoped_index>&
fields::field_eval_iterator::
property_discretization_members() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  const block<scoped_index>& result = _property_discretization_members;

  // Postconditions:

  // Exit

  return result;
}

bool
fields::field_eval_iterator::
property_has_been_visited(pod_index_type xhub_id) const
{
  // Preconditions:

  // Body:

  bool result = (*_property_has_been_visited)[xhub_id];

  // Postconditions:

  // Exit

  return result;
}

bool
fields::field_eval_iterator::
property_has_been_visited(const scoped_index& xid) const
{
  // Preconditions:

  // Body:

  return property_has_been_visited(xid.hub_pod());
}

void
fields::field_eval_iterator::
gather_coordinate_dofs(const sec_vd& xcoord,
                       block<sec_vd::dof_type>& xdofs)
{
  // Preconditions:

  require(xcoord.state_is_read_accessible());
  require(xcoord.schema().is_same_state(&coordinate_schema_anchor()));
  require(xdofs.ub() >= coordinate_discretization_members().ct()*xcoord.schema().df());

  // Preceeding precondition and indexing below only correct for binary schema.
  /// @todo revise when ternary schema are supported.

  require(dynamic_cast<const binary_section_space_schema_member*>(&xcoord.schema()) != 0);

  // Body:

  size_type ldf = xcoord.schema().df();
  size_type ldofs_ct = 0;
  size_type ldofs_ub = xdofs.ub();
  sec_vd::dof_type* ldofs = xdofs.base();

  for(size_type i=0; i<_coordinate_discretization_members.ct(); ++i)
  {
    xcoord.get_fiber(_coordinate_discretization_members[i], ldofs,
		     ldofs_ub*sizeof(sec_vd::dof_type), false);

    ldofs += ldf;
    ldofs_ct += ldf;
    ldofs_ub -= ldf;
  }

  xdofs.set_ct(ldofs_ct);

  // Postconditions:

  ensure(xdofs.ct() == coordinate_discretization_members().ct()*xcoord.schema().df());

  // Exit:

  return;
}

sheaf::size_type
fields::field_eval_iterator::
refinement_depth() const
{
  int lresult = depth() - _top_zone_depth;

  return lresult >= 0 ? lresult : 0;
}

void
fields::field_eval_iterator::
update_capacity()
{
  // Preconditions:

  require(!is_done());

  // Body:

  // Client may have added members to the base space.
  // Make sure has_visited still has enough capacity.

  size_type lmember_index_ub = _base_space->member_index_ub().pod();

  has_visited()->extend_to(lmember_index_ub);
  _property_has_been_visited->extend_to(lmember_index_ub);

  // Postconditions:

  ensure(enough_capacity());

  // Exit:

  return;
}

bool
fields::field_eval_iterator::
enough_capacity() const
{
  bool result;

  // Preconditions:

  require(!is_done());

  // Body:

  size_type lmember_index_ub = _base_space->member_index_ub().pod();

  result =
    (has_visited()->ub() >= lmember_index_ub) &&
    (_property_has_been_visited->ub() >= lmember_index_ub);

  // Postconditions:


  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

void
fields::field_eval_iterator::
initialize_coordinate_schema(
  const section_space_schema_member& xcoordinate_schema_anchor)
{
  // Preconditions:

  require(xcoordinate_schema_anchor.state_is_read_accessible());
  require(is_done());

  // Body:

  // Allocate the schema anchor if needed.

  // Set the coordinate schema anchor.

  _coordinate_schema_anchor = xcoordinate_schema_anchor.clone();
  _coordinate_schema_anchor->attach_to_state(&xcoordinate_schema_anchor);

  // Get the proper evaluator family for the coordinate schema.

  _coordinate_evaluators =
    eval_family::new_family(xcoordinate_schema_anchor.evaluator_family_name(),
                            *xcoordinate_schema_anchor.name_space());

  // Initialize features shared by coordinate and property schema.

  _base_space = &_coordinate_schema_anchor->host()->base_space();
  _evaluation.attach_to_state(&_coordinate_schema_anchor->evaluation());

  // Postconditions:

  // Can not ensure invariant until inherited iterator features initialized..

  ensure(_coordinate_schema_anchor->is_same_state(&xcoordinate_schema_anchor));
  ensure(_coordinate_schema_anchor->version() == xcoordinate_schema_anchor.version());
  ensure(_coordinate_schema_anchor->is_same_type(&xcoordinate_schema_anchor));
  ensure(_coordinate_evaluators != 0);

  // Exit

  return;
}

void
fields::field_eval_iterator::
initialize_property_schema(
  const section_space_schema_member& xproperty_schema_anchor)
{
  // Preconditions:

  require(xproperty_schema_anchor.state_is_read_accessible());
  require(is_done());

  // Body:

  // Allocate the schema anchor if needed.

  // Set the property schema anchor.

  _property_schema_anchor = xproperty_schema_anchor.clone();
  _property_schema_anchor->attach_to_state(&xproperty_schema_anchor);

  // Get the proper evaluator family for the property schema.

  _property_evaluators =
    eval_family::new_family(xproperty_schema_anchor.evaluator_family_name(),
                            *xproperty_schema_anchor.name_space());

  // Create the previously visited markers.

  _property_has_been_visited = new zn_to_bool(_base_space->member_index_ub().pod());

  // Postconditions:

  // Can not ensure invariant until inherited iterator features initialized..

  ensure(_property_schema_anchor->is_same_state(&xproperty_schema_anchor));
  ensure(_property_schema_anchor->version() == xproperty_schema_anchor.version());
  ensure(_property_schema_anchor->is_same_type(&xproperty_schema_anchor));
  ensure(_property_evaluators != 0);
  ensure(_property_has_been_visited != 0);

  // Exit

  return;
}

void
fields::field_eval_iterator::
initialize_discretization_order_correction()
{
  // Preconditions:

  // Body:

  // The connectivity reversal trick should be applied to evaluation
  // members which are 2D and have edges in their down set. This
  // includes prototypes "triangle", "quad", "tri_shell", and "quad_shell".
  // Currently only "quad" is supported in the base_space_member_prototypes
  // poset.

  _correction_set.insert(_base_space->prototype_type_id("quad"));

  _coordinate_correction_enabled = false;
  _property_correction_enabled = false;
  _coordinate_vertex_discretization =
    (_coordinate_schema_anchor->discretization().name() == "__vertices");
  _property_vertex_discretization =
    (_property_schema_anchor->discretization().name() == "__vertices");

  // Postconditions:


  // Exit:

  return;
}


void
fields::field_eval_iterator::
ensure_discretization_order(block<scoped_index>& xdisc_mbrs)
{
  // Preconditions:

  require(xdisc_mbrs.ct() == 2);

  // Body:

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

  poset_state_handle* lanchor_host =_anchor->host();

  pod_index_type first_eval = lanchor_host->first_cover_member(UPPER, greater_index().hub_pod());

  bool is_reversed = (_evaluator_id.hub_pod() != first_eval);

  if(is_reversed)
  {
    const scoped_index& save = xdisc_mbrs[0];
    xdisc_mbrs[0] = xdisc_mbrs[1];
    xdisc_mbrs[1] = save;
  }

  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// DEPTH_FIRST_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fields::field_eval_iterator::
force_is_done()
{
  // Preconditions:

  // Body:

  // Clear the down set collection buffers.

  _down_set_collection_enabled = false;
  _coordinate_discretization_members.set_ct(0);
  _property_discretization_members.set_ct(0);
  _non_discretization_members.set_ct(0);

  depth_first_iterator::force_is_done();

  // Postconditions:

  ensure(invariant());
  ensure(is_done());

  // Exit

  return;
}

void
fields::field_eval_iterator::
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

#ifdef DIAGNOSTIC_OUTPUT
      cout << "previsit:  "
      << " id: " << setw(4) << index()
      << " type" << setw(20) << (_base_space->is_jim(index(), false) ? type_name() : "")
      << " depth(): " << setw(4) << depth()
      << " top_zone_depth: " << setw(14) << _top_zone_depth
      << " refinement_depth: " << setw(4) << refinement_depth()
      << endl;
#endif

      // The evaluation, coordinate discretization, and property discretization
      // are not necessarily distinct. In particular, the property discretization
      // can be the same as the evaluation or the coordinate discretization.
      // So we have to test each independently of the others.

      bool lnone_of_the_above = true;

      if(_evaluation.contains_member(index()))
      {
        // This member is an evaluation member.

        if(_top_zone_depth == numeric_limits<int>::max())
        {
          // This is the top level zone on this path; mark its depth.

          _top_zone_depth = depth();
        }

        if(_base_space->jims().contains_member(index()))
        {
          // This member is also a jim, so it is an active evaluation member,
          // i.e. there are no finer evaluation members in its down set.

          _evaluator_id = index();
          _evaluator_refinement_depth = _base_space->refinement_depth(_evaluator_id);

          // Enable discretization order correction if possible.

          bool lis_correctable =
            (_correction_set.find(type_id()) != _correction_set.end());
          _coordinate_correction_enabled =
            lis_correctable && _coordinate_vertex_discretization;
          _property_correction_enabled =
            lis_correctable && _property_vertex_discretization;

          // Reset the down set collection buffers.

          _coordinate_discretization_members.set_ct(0);

          for(int i=0; i<_property_discretization_members.ct(); ++i)
          {
            _property_has_been_visited->put(_property_discretization_members[i].pod(), true);
          }
          _property_discretization_members.set_ct(0);

          _non_discretization_members.set_ct(0);

          _down_set_collection_enabled = true;

          // Do not truncate, continue descending.

          ltruncate = false;

          lnone_of_the_above = false;
        }
      }

      // We assume the coordinate discretization is the lowest level we need
      // to visit and in particular that coord disc <= prop disc.
      // Hence we can truncate the traversal once we've processed the coord disc.
      // Assume we won't truncate here, chnage it in the coord disc branch below.

      ltruncate = false;

      if(property_schema_anchor().discretization().contains_member(index()) &&
          (_base_space->refinement_depth(index()) <= _evaluator_refinement_depth))
      {
        // This is a property discretization member.
        // Invariant ensures discretization is not above evaluation,
        // so down set collection must be enabled.
        // Enter this member in the discretization collection.

        _property_discretization_members.push_back(index());

        if(_property_correction_enabled &&
            (_property_discretization_members.ct() == 2))
        {
          ensure_discretization_order(_property_discretization_members);
        }

        lnone_of_the_above = false;
      }

      if(coordinate_schema_anchor().discretization().contains_member(index()) &&
          (_base_space->refinement_depth(index()) <= _evaluator_refinement_depth))
      {
        // This is a coordinate discretization member.
        // Invariant ensures discretization is not above evaluation,
        // so down set collection must be enabled.
        // Enter this member in the discretization collection.

        _coordinate_discretization_members.push_back(index());

        if(_coordinate_correction_enabled &&
            (_coordinate_discretization_members.ct() == 2))
        {
          ensure_discretization_order(_coordinate_discretization_members);
        }

        // Assume the coordinate discretization is the lowest level we need to visit,
        // so we never need to go below this member; truncate.

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
      }
    }
    else if(action() == POSTVISIT_ACTION)
    {
      if(depth() == _top_zone_depth)
      {
        // We're back to the top level zone on this path; unmark the depth;

        _top_zone_depth = numeric_limits<int>::max();
      }


#ifdef DIAGNOSTIC_OUTPUT
      cout << "postvisit: "
      << " id: " << setw(4) << index()
      << " type" << setw(20) << (_base_space->is_jim(index(), false) ? type_name() : "")
      << " depth(): " << setw(4) << depth()
      << " top_zone_depth: " << setw(14) << _top_zone_depth
      << " refinement_depth: " << setw(4) << refinement_depth()
      << endl;
#endif

      if(_evaluation.contains_member(index()))
      {
        // This member is an evaluation member.

        if(_base_space->jims().contains_member(index()))
        {
          // This member is also a jim, so it is an active evaluation member,
          // i.e. there are no finer evaluation members in its down set.

          // Postvisit of eval member;
          // we are done iterating over discretization members
          // associated with this evaluation member;
          // return to the client with the discretization collection.

          // Clear the has visited markers for the down set.

          for(int i=0; i<_coordinate_discretization_members.ct(); ++i)
          {
	    put_has_visited(_coordinate_discretization_members[i], false);
          }
          for(int i=0; i<_property_discretization_members.ct(); ++i)
          {
	    put_has_visited(_property_discretization_members[i], false);
          }

          for(int i=0; i<_non_discretization_members.ct(); ++i)
          {
	    put_has_visited(_non_discretization_members[i], false);
          }
          _non_discretization_members.set_ct(0);

          // Turn off down set collection.

          _down_set_collection_enabled = false;

          // Reinitialize discretization order correction.

          _coordinate_correction_enabled = false;
          _property_correction_enabled = false;

          // Return to the client.

          break;
        }
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
  ensure(!is_done() ? coordinate_schema_anchor().evaluation().contains_member(index()) : true);

  // Exit

  return;
}

void
fields::field_eval_iterator::
repeat(bool xwas_eval_member)
{
  // Preconditions:


  // Body:

  if(xwas_eval_member)
  {
    // We've just refined the current member and
    // removed it from the evaluation subposet.

    // Make sure the bit vectors have enough capacity
    // for the now larger base space.

    update_capacity();

    if(_top_zone_depth == numeric_limits<int>::max())
    {
      // This is the top level zone on this path; mark the depth.

      _top_zone_depth = depth();
    }
  }

  // Just reset the iterator state back to the previsit action and continue.
  // Traversal will repeat down set of the current member.

  /// @hack this really should be done by modifying the state transition
  /// function in DEPTH_FIRST_ITERATOR.

  _state = EXECUTE_PREVISIT_ACTION;

  next(false);


  // Postconditions:


  // Exit:

  return;
}

void
fields::field_eval_iterator::
reset(bool xreset_markers)
{
  // Preconditions:


  // Body:

  if(xreset_markers)
  {
    _property_has_been_visited->make_false();
  }
  else
  {
    for(int i=0; i<_property_discretization_members.ct(); ++i)
    {
      _property_has_been_visited->put(_property_discretization_members[i].pod(), true);
    }
  }

  _coordinate_discretization_members.set_ct(0);
  _property_discretization_members.set_ct(0);
  _non_discretization_members.set_ct(0);
  _top_zone_depth = numeric_limits<int>::max();

  depth_first_iterator::reset(xreset_markers);

  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::field_eval_iterator::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const field_eval_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fields::field_eval_iterator*
fields::field_eval_iterator::
clone() const
{
  // Preconditions:

  // Body:

  field_eval_iterator* result =
    new field_eval_iterator(coordinate_schema_anchor(), property_schema_anchor());

  // Postconditions:

  //  ensure(invariant());
  ensure(result != 0);

  // Exit

  return result;
}

bool
fields::field_eval_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:


  if(invariant_check())
  {
    invariance(depth_first_iterator::invariant());

    disable_invariant_check();

    invariance(order() == BIORDER);
    invariance(anchor().is_same_state(&(coordinate_schema_anchor().base_space())));
    invariance(property_schema_anchor().base_space().is_same_state(&coordinate_schema_anchor().base_space()));
    invariance(property_schema_anchor().evaluation().is_same_state(&coordinate_schema_anchor().evaluation()));

    // The entire notion of gathering the discretization members
    // for each evaluation member only makes sense if the discretization
    // subposet is not coarser than the evaluation subposet. But we
    // currently have no executable way to state this invariant.

    invariance(unexecutable("coordinate discretization is not coarser than evaluation"));
    invariance(unexecutable("property discretization is not coarser than evaluation"));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}
