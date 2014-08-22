
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

// Implementation for class section_eval_iterator

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/block.h"
#include "ComLimitPoint/fiber_bundle/eval_family.h"
#include "ComLimitPoint/sheaf/poset_state_handle.h"
#include "ComLimitPoint/sheaf/postorder_iterator.h"
#include "section_eval_iterator.h"
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_member.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_poset.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

fiber_bundle::section_eval_iterator&
fiber_bundle::section_eval_iterator::
operator=(const section_eval_iterator& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));
  require(xother.components_done());
  require(xother.evaluators_done());

  // Body:

  section_eval_iterator& lother =
    const_cast<section_eval_iterator&>(xother);

  if(is_initialized())
  {
    _anchor->detach_from_state();
    delete _anchor;
    _anchor = 0;
  }

  if(lother._anchor != 0)
  {
    _anchor = lother._anchor->clone();
    _anchor->attach_to_state(lother._anchor);
  }

  _fiber_schema_itr = lother._fiber_schema_itr;

  _evaluation_itr = lother._evaluation_itr;

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);

  // Exit

  return *this;
}


fiber_bundle::section_eval_iterator::
~section_eval_iterator()
{

  // Preconditions:

  // Body:

  if(_anchor != 0)
  {
    _anchor->detach_from_state();
    delete _anchor;
  }

  // Postconditions:

  // Exit:

  return;
}


bool
fiber_bundle::section_eval_iterator::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const section_eval_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


bool
fiber_bundle::section_eval_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(any::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    invariance( is_initialized() == (_anchor != 0) );
    invariance( is_initialized() == (_fiber_schema_itr.is_initialized()) );
    invariance( is_initialized() == (_evaluation_itr.is_initialized()) );

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}



// ITERATOR FACET

bool
fiber_bundle::section_eval_iterator::
is_initialized() const
{
  // Preconditions:

  // Body:

  bool result = _anchor != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::section_space_schema_member&
fiber_bundle::section_eval_iterator::
anchor()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result = *_anchor;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::section_eval_iterator::
anchor() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  section_space_schema_member& result = *_anchor;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_eval_iterator::
anchor_is_ancestor_of(const section_space_schema_member& xmbr) const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Always true in this class;
  // intended to be redefined in descendants.

  bool result = true;

  // Postconditions:

  // Exit

  return result;
}


void
fiber_bundle::section_eval_iterator::
reset(bool xreset_markers)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());

  // Body:

  _evaluation_itr.reset(xreset_markers);
  _fiber_schema_itr.reset(xreset_markers);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());

  // Exit

  return;
}

void
fiber_bundle::section_eval_iterator::
reset(pod_index_type xanchor_index, bool xreset_markers)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xanchor_index));

  // Body:

  // Reset the anchor.

  _anchor->attach_to_state(xanchor_index);

  // Reset the evaluation iterator.

  _evaluation_itr.put_schema_anchor(xanchor_index);
  _evaluation_itr.reset(xreset_markers);

  // Anchor of fiber_schema_iterator is an ordinary poset, so we need
  // the id of the fiber schema component of anchor.

  _fiber_schema_itr.put_anchor(anchor().fiber_schema_id());
  _fiber_schema_itr.reset(xreset_markers);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().index() == xanchor_index);

  // Exit

  return;
}

void
fiber_bundle::section_eval_iterator::
reset(const scoped_index& xanchor_index, bool xreset_markers)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xanchor_index));

  // Body:

  reset(xanchor_index.hub_pod(), xreset_markers);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().index() ==~ xanchor_index);

  // Exit

  return;
}

void
fiber_bundle::section_eval_iterator::
reset(const section_space_schema_member& xanchor)
{

  // Preconditions:

  require(is_initialized() ? anchor_is_ancestor_of(xanchor) : true);
  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->is_schematized(false));

  // Body:

  reset_anchor(xanchor);

  _evaluation_itr.put_schema_anchor(xanchor);
  _evaluation_itr.reset();

  // Reset the fiber schema component iterator.
  // Set the filter to the dof subposet of top so that we can reset the anchor
  // without changing the filter. See reset(int xanchor_index, bool xreset_markers).
  // Also, we don't currently support versions of fiber schema.

  string ldof_sp_name = schema_poset_member::dof_subposet_name("top", false);

  _fiber_schema_itr.put_anchor(&(xanchor.fiber_schema()));
  _fiber_schema_itr.put_filter(ldof_sp_name);
  _fiber_schema_itr.reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));

  // Exit:

  return;
}

int
fiber_bundle::section_eval_iterator::
ct(bool xreset)
{
  // Preconditions:

  require(is_initialized());
  require(xreset ? anchor().state_is_read_accessible(): true);

  // Body:

  int result = _evaluation_itr.ct(xreset)*_fiber_schema_itr.ct(xreset);

  // Postconditions:

  ensure(result >= 0);
  ensure(evaluators_done());
  ensure(components_done());

  // Exit

  return result;
}


bool
fiber_bundle::section_eval_iterator::
has_visited(pod_index_type xhub_id) const
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  bool result =
    _evaluation_itr.has_visited(anchor().host()->get_base_space_id_from_index(xhub_id)) &&
    _fiber_schema_itr.has_visited(anchor().host()->get_fiber_schema_id_from_index(xhub_id));

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::section_eval_iterator::
has_visited(const scoped_index& xid) const
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xid));

  // Body:

  return has_visited(xid.hub_pod());
}

bool
fiber_bundle::section_eval_iterator::
has_visited(const section_space_schema_member& xmbr) const
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(xmbr.is_attached());
  require(anchor().host()->is_same_state(xmbr.host()));

  // Body:

  bool result = _evaluation_itr.has_visited(xmbr.base_space_id()) &&
                _fiber_schema_itr.has_visited(xmbr.fiber_schema_id());

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::section_eval_iterator::
put_has_visited(pod_index_type xhub_id, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xhub_id));

  // Body:

  _evaluation_itr.put_has_visited(anchor().host()->get_base_space_id_from_index(xhub_id), xvalue);
  _fiber_schema_itr.put_has_visited(anchor().host()->get_fiber_schema_id_from_index(xhub_id), xvalue);

  // Postconditions:

  ensure(has_visited(xhub_id) == xvalue);

  // Exit:

  return;
}

void
fiber_bundle::section_eval_iterator::
put_has_visited(const scoped_index& xid, bool xvalue)
{

  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());
  require(anchor().host()->contains_member(xid));

  // Body:

  put_has_visited(xid.hub_pod(), xvalue);

  // Postconditions:

  ensure(has_visited(xid) == xvalue);

  // Exit:

  return;
}

const sheaf::scoped_index&
fiber_bundle::section_eval_iterator::
evaluator_id() const
{
  // Preconditions:

  require(is_initialized());

  require(!evaluators_done());

  // Body:

  const scoped_index& result = _evaluation_itr.index();

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::section_evaluator&
fiber_bundle::section_eval_iterator::
evaluator()
{
  // Preconditions:

  require(is_initialized());

  require(!evaluators_done());

  // Body:

  section_evaluator& result = _evaluation_itr.evaluator();

  // Postconditions:

  // Exit

  return result;
}


const fiber_bundle::section_evaluator&
fiber_bundle::section_eval_iterator::
evaluator() const
{
  // Preconditions:

  require(is_initialized());

  require(!evaluators_done());

  // Body:

  const section_evaluator& result = _evaluation_itr.evaluator();

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_eval_iterator::
evaluators_done() const
{
  bool result;

  // Preconditions:

  require(is_initialized());

  // Body:

  result = _evaluation_itr.is_done();

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::section_eval_iterator::
next_evaluator()
{

  // Preconditions:

  require(is_initialized());
  require(!evaluators_done());

  // Body:

  _evaluation_itr.next(false);

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}


bool
fiber_bundle::section_eval_iterator::
components_done() const
{
  bool result;

  // Preconditions:

  require(is_initialized());

  // Body:

  result = _fiber_schema_itr.is_done();

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::section_eval_iterator::
next_component()
{

  // Preconditions:

  require(is_initialized());
  require(!components_done());

  // Body:

  _fiber_schema_itr.next();

  //   if(!_fiber_schema_itr.is_done())
  //     _fiber_id = _fiber_schema_itr.index();
  //   else
  //     _fiber_id.invalidate();

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

sheaf::block<sheaf::scoped_index>&
fiber_bundle::section_eval_iterator::
discretization_members()
{

  // Preconditions:

  require(!evaluators_done());

  // Body:

  block<scoped_index>& result = _evaluation_itr.discretization_members();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::block<sheaf::scoped_index>&
fiber_bundle::section_eval_iterator::
discretization_members() const
{

  // Preconditions:

  require(!evaluators_done());

  // Body:

  const block<scoped_index>& result = _evaluation_itr.discretization_members();

  // Postconditions:

  // Exit

  return result;
}

const sheaf::scoped_index&
fiber_bundle::section_eval_iterator::
fiber_id() const
{

  // Preconditions:

  //  require(!evaluators_done());
  require(!components_done());

  // Body:

  const scoped_index& result = _fiber_schema_itr.index();

  // Postconditions:

  // Exit

  return result;
}



// PROTECTED MEMBER FUNCTIONS

fiber_bundle::section_eval_iterator::
section_eval_iterator() :
    _anchor(0)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit:

  return;
}

void
fiber_bundle::section_eval_iterator::
gather_dofs(const sec_vd& xsec, block<sec_vd::dof_type>& xdofs)
{
  // Preconditions:

  require(!evaluators_done());
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
fiber_bundle::section_eval_iterator::
scatter_dofs(sec_vd& xsec, const block<sec_vd::dof_type>& xdofs, size_type xhub_id)
{
  // Preconditions:

  require(!evaluators_done());
  require(xsec.state_is_read_write_accessible());
  require(xdofs.ub() >= xhub_id + xsec.schema().df()*discretization_members().ct());


  // Body:

  block<scoped_index>& ldisc_mbrs = discretization_members();

  size_type ldisc_mbr_ct = ldisc_mbrs.ct();
  int ldf                = xsec.schema().df();
  size_type ldof_ct      = ldf*ldisc_mbr_ct;

  size_type ldof_index = xhub_id;

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

fiber_bundle::section_eval_iterator::
section_eval_iterator(const section_eval_iterator& xother)
{

  // Preconditions:

  // Body:

  _fiber_schema_itr = reinterpret_cast<const section_eval_iterator&>(xother)._fiber_schema_itr;

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized() == xother.is_initialized());
  ensure(is_initialized() ? anchor().is_same_state(&xother.anchor()) : true);

  // Exit

  return;
}

void
fiber_bundle::section_eval_iterator::
reset_anchor(const section_space_schema_member& xanchor)
{
  // Preconditions:

  require(is_initialized() ? anchor_is_ancestor_of(xanchor) : true);
  require(xanchor.state_is_read_accessible());

  // Body:

  if(_anchor == 0)
  {
    // Create the anchor handle

    _anchor = xanchor.clone();
  }

  // Attach the handle.

  _anchor->attach_to_state(&xanchor);

  // Postconditions:

  ensure(anchor().is_attached());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));

  // Exit:

  return;
}

fiber_bundle::section_eval_iterator::
section_eval_iterator(const section_space_schema_member& xanchor) :
    _anchor(0)
{

  // Preconditions:

  require(xanchor.state_is_read_accessible());
  require(xanchor.host()->is_schematized(false));

  // Body:

  /// @todo  The initial setting of the anchor is a bit strange.
  /// It works around preconditions in reset_anchor that require that
  /// any new anchor be related to the old anchor.  Examine this in more
  /// detail and see whether there's a less awkward way to set the anchor.

  _anchor = xanchor.clone();

  reset(xanchor);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(anchor().is_same_state(&xanchor));
  ensure(anchor().is_same_type(&xanchor));

  // Exit:

  return;
}

void
fiber_bundle::section_eval_iterator::
reset_components()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  _fiber_schema_itr.reset();

  // Postconditions:

  ensure(invariant());

  // Exit
}

fiber_bundle::section_eval_iterator*
fiber_bundle::section_eval_iterator::
clone() const
{

  // Preconditions:

  // Body:

  not_implemented();

  // Initialize result anyway, to suppress compiler warnings.

  section_eval_iterator* result = 0;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit

  return result;
}
