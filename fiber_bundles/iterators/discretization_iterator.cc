
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

// Implementation for class discretization_iterator

#include "discretization_iterator.h"
#include "assert_contract.h"
#include "section_space_schema_member.h"
#include "section_space_schema_poset.h"
#include "sec_rep_descriptor.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

fiber_bundle::discretization_iterator::
discretization_iterator()
    : depth_first_iterator()
{

  // Preconditions:

  // Body:

  initialize_order(BIORDER);

  _schema_anchor = 0;
  _ascending_has_visited = 0;
  _descending_has_visited = 0;

  _discretization_member_index.invalidate();
  _evaluation_member_index.invalidate();

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit

  return;
}

fiber_bundle::discretization_iterator::
discretization_iterator(const discretization_iterator& xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

fiber_bundle::discretization_iterator::
~discretization_iterator()
{
  // Preconditions:

  // Body:

  if(_schema_anchor != 0)
  {
    _schema_anchor->detach_from_state();
    delete _schema_anchor;
  }

  /// @hack remove depth_first_iterator::has_viist()/put_has_visited(zn_to_bool*)
  /// when no longer need here.

  //   if(_ascending_has_visited != _has_visited)
  //     _has_visited = _descending_has_visited;

  if(_ascending_has_visited != has_visited())
    put_has_visited(_descending_has_visited);

  if(_ascending_has_visited != 0)
    delete _ascending_has_visited;

  // Postconditions:

}

bool
fiber_bundle::discretization_iterator::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const discretization_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::discretization_iterator*
fiber_bundle::discretization_iterator::
clone() const
{
  discretization_iterator* result;

  // Preconditions:

  // Body:

  result = new discretization_iterator;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_initialized());

  // Exit

  return result;
}

bool
fiber_bundle::discretization_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(depth_first_iterator::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    invariance(order()==BIORDER);
    invariance(is_initialized() ?
               anchor().is_same_state(&(schema_anchor().base_space())) :
               true);

    // Finished, turn invariant check back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// OTHER CONSTRUCTORS


fiber_bundle::discretization_iterator::
discretization_iterator(const section_space_schema_member& xschema_anchor)
    : depth_first_iterator()
{

  // Preconditions:

  require(xschema_anchor.state_is_read_accessible());

  // Body:

  initialize_order(BIORDER);

  // Set the anchor, filter, and direction

  _schema_anchor = 0;
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

  return;
}


// ITERATOR INTERFACE

//$$SCRIBBLE jebutler const correctness

bool
fiber_bundle::discretization_iterator::
is_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = depth_first_iterator::is_initialized() && (_schema_anchor != 0);

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::discretization_iterator::
force_is_done()
{
  // Preconditions:

  // Body:

  _up_set.clear();

  _discretization_member_index.invalidate();
  _evaluation_member_index.invalidate();

  depth_first_iterator::force_is_done();


  // Postconditions:

  ensure(invariant());
  ensure(is_done());

  // Exit

  return;
}

void
fiber_bundle::discretization_iterator::
next(bool xtruncate)
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool ltruncate = xtruncate;

  // Continue traversing the graph until the traversal is done
  // or we find a single- or multi-valued discretization point
  // and return to the client.

  depth_first_iterator::next(ltruncate);

  while(!is_done())
  {
    if(action()==PREVISIT_ACTION)
    {
      if(_descending)
      {
        // Traversing down.

        if(schema_anchor().discretization().contains_member(index()))
        {
          // This member is a disc member

          if(schema_anchor().is_multivalued() &&
              schema_anchor().multivalued().contains_member(index()))
          {
            // Multivalued is enabled and this disc member is multivalued.
            // Reverse direction (ascend)

	    /// @hack remove depth_first_iterator::has_viist()/put_has_visited(zn_to_bool*)
	    /// when no longer need here.

	    //            _has_visited = _ascending_has_visited;
            put_has_visited(_ascending_has_visited);
            _descending = false;
            ltruncate = false;

            _discretization_member_index = _index;

          }
          else
          {
            // Multivalued is not enabled or this disc member is single valued.
            // Truncate; move directly to postvisit action on this member.

            ltruncate = true;
          }
        }
        else
        {
          // This member is not a disc member;
          // Do not truncate, continue descending.

          ltruncate = false;
        }
      }
      else
      {
        // Traversing up

        _ascending_has_visited->put(index().pod(),true);
        _up_set.push_front(index().pod());

        // If this is an eval member, we don't want to go further up; truncate.

        ltruncate = schema_anchor().evaluation().contains_member(index());
      }
    }
    else if(action()==POSTVISIT_ACTION)
    {
      // If we invoke depth_first_iterator::next() from the postvisit action,
      // the truncation flag will be ignored, since you can only truncate
      // in the previsit action. But just to be specific, we'll set it false no
      // matter what we do here.

      ltruncate = false;

      if(_descending)
      {
        // Traversing down

        if(schema_anchor().discretization().contains_member(index()))
        {
          // Postvisit of disc member while traversing down;
          // this is a single-valued "discretization point";
          // return to the client.

          _discretization_member_index = _index;

          break;
        }
        else
        {
          // Not a disc member; nothing to do.
          // Continue traversal.
        }
      }
      else
      {
        // Traversing up.

        if(schema_anchor().discretization().contains_member(index()))
        {
          // Postvisit of disc member while traversing up.
          // Have finished traversal over upset of this member.
          // Reverse direction.

          _descending = true;

          // Clear the ascending has visited markers.

          while(!_up_set.empty())
          {
            _ascending_has_visited->put(_up_set.front(), false);
            _up_set.pop_front();
          }

          // Set has visited markers to the descending has visited markers

	  /// @hack remove depth_first_iterator::has_viist()/put_has_visited(zn_to_bool*)
	  /// when no longer need here.
	  ///          _has_visited = _descending_has_visited;
	  put_has_visited(_descending_has_visited);
        }
        else if(schema_anchor().evaluation().contains_member(index()))
        {
          // Postvisit of eval member while traversing up.
          // This is a multi-valued "discretization point";
          // return to the client.

          _evaluation_member_index = _index;

          break;
        }
        else
        {
          // Postvisit of neither disc nor eval member.
          // Nothing to do; continue traversal.
        }
      } // end if traversing up
    }
    else
    {
      post_fatal_error_message("unrecognized action");
    }

    depth_first_iterator::next(ltruncate);

  } // end while(!is_done())

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() ? action()==POSTVISIT_ACTION : true);
  ensure(!is_done() ? schema_anchor().discretization().contains_member(index()) ||
         schema_anchor().evaluation().contains_member(index()) : true);

  // Exit

  return;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::discretization_iterator::
schema_anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result = *_schema_anchor;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::discretization_iterator::
schema_anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result = *_schema_anchor;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::discretization_iterator::
put_schema_anchor(const section_space_schema_member& xschema_anchor)
{

  // Preconditions:

  require(xschema_anchor.state_is_read_accessible());

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  force_is_done();

  // Now (re)initialize.

  // Set the schema anchor.

  initialize_schema_anchor(xschema_anchor);

  // Set the anchor, has_visited markes and filter..

  initialize_traversal(_schema_anchor->base_space());

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
fiber_bundle::discretization_iterator::
put_schema_anchor(pod_index_type xschema_anchor_index)
{

  // Preconditions:

  require(is_initialized());
  require(schema_anchor().state_is_read_accessible());
  require(schema_anchor().host()->contains_member(xschema_anchor_index));

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);
  define_old_variable(scoped_index old_filter_index = filter().index());
  define_old_variable(int old_anchor_version = anchor().version());
  define_old_variable(int old_schema_anchor_version = schema_anchor().version());

  // Force iterator into a known clean state;
  // also forces client to reset before using this.

  force_is_done();

  // Now reinitialize.

  // Set the schema anchor.

  _schema_anchor->attach_to_state(xschema_anchor_index);

  // Set the anchor.

  initialize_traversal(_schema_anchor->base_space_id());

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
fiber_bundle::discretization_iterator::
put_schema_anchor(const scoped_index& xschema_anchor_index)
{

  // Preconditions:

  require(is_initialized());
  require(schema_anchor().state_is_read_accessible());
  require(schema_anchor().host()->contains_member(xschema_anchor_index));

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

const sheaf::scoped_index&
fiber_bundle::discretization_iterator::
discretization_member_index() const
{
  return _discretization_member_index;
}

const sheaf::scoped_index&
fiber_bundle::discretization_iterator::
evaluation_member_index() const
{
  // Preconditions:

  require(is_multivalued());

  return _evaluation_member_index;
}

bool
fiber_bundle::discretization_iterator::
is_multivalued() const
{
  // Precondition:

  require(is_initialized());

  // Body:

  bool result = (discretization_member_index().is_valid()) &&
                schema_anchor().is_multivalued() &&
                schema_anchor().multivalued().contains_member(discretization_member_index());

  // Postconditions:

  ensure(result == ((discretization_member_index().is_valid()) &&
                    schema_anchor().is_multivalued() &&
                    schema_anchor().multivalued().contains_member(discretization_member_index())));

  // Exit

  return result;
}


void
fiber_bundle::discretization_iterator::
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
fiber_bundle::discretization_iterator::
initialize_has_visited(const abstract_poset_member& xanchor)
{
  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(is_done());

  // Body:

  depth_first_iterator::initialize_has_visited(xanchor);

  /// @hack remove depth_first_iterator::has_viist()/put_has_visited(zn_to_bool*)
  /// when no longer need here.
  ///  _descending_has_visited = _has_visited;
  ///  _ascending_has_visited = new zn_to_bool(*_has_visited);

  _descending_has_visited = has_visited();
  _ascending_has_visited = new zn_to_bool(*has_visited());

  // Postconditions:

  //   ensure(_has_visited != 0);
  //   ensure(_descending_has_visited == _has_visited);
  ensure(has_visited() != 0);
  ensure(_descending_has_visited == has_visited());
  ensure(_ascending_has_visited != 0);
  ensure(is_done());

  // Exit

  return;
}
