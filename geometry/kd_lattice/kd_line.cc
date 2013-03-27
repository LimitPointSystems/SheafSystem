// $RCSfile: kd_line.cc,v $ $Revision: 1.7 $ $Date: 2013/03/13 00:59:00 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_line

#include "kd_line.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "e3.h"
#include "fiber_bundles_namespace.h"
#include "hash_set_filter.h"
#include "jim_cohort.h"
#include "kd_face.h"
#include "kd_lattice.h"
#include "kd_plane.h"
#include "kd_point.h"
#include "kd_segment.h"
#include "postorder_itr.h"
#include "sec_e3.h"
#include "cohort.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.


// ===========================================================
// KD_LINE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const string&
geometry::kd_line::
prototype_name()
{
  // cout << endl << "Entering kd_line::prototype_name." << endl;

  // Preconditions:

  // Body:

  static const string result("line");

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  // cout << "Leaving kd_line::prototype_name." << endl;
  return result;
}

geometry::kd_line::
kd_line(kd_lattice& xhost, const id_list& xline_mbrs)
  :kd_member(xhost)
{
  // cout << endl << "Entering kd_line::kd_line." << endl;

  // Preconditions:

  require(precondition_of(new_line(xhost, xline_mbrs, _id)));
  
  // Body:

  new_line(xhost, xline_mbrs, _id);
  
  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(new_line(xhost, xline_mbrs, _id)));

  // Exit:

  // cout << "Leavinging kd_line::kd_line." << endl;
  return; 
}

void
geometry::kd_line::
new_line(kd_lattice& xhost, const id_list& xline_mbrs, scoped_index& xresult)
{
  // cout << endl << "Entering kd_line::new_line." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(!xline_mbrs.empty());

  define_old_variable(size_type old_lines_ct = xhost.lines().ct());
    
  // Body:

  // Create the line member.

  xresult = xhost.lines().new_member();
  
  // Line covers the segments.
  
  // A line is interpreted as an abstract member, a jim,
  // that is not contained in the top_zone. The line in turn
  // contains its current representation as a collection of
  // segments, which are contained in the top zone, but the 
  // line is not equivalent to the collection. This is both 
  // conceptually correct, the lines, line webs and surfaces
  // represent abstrations evolving in response to client
  // input, and it is efficient, we don't have compute the
  // join of the line segments and the line members don't
  // unexpectedly appear in the lower covers of tree members.

  base_space_poset& lbase = xhost.base_space();
  const subposet& lsegments = xhost.segments().sp();

  for(id_list::const_iterator litr = xline_mbrs.begin(); litr != xline_mbrs.end(); ++litr)
  {
    if(lsegments.contains_member(*litr))
    {
      lbase.new_link(xresult, *litr);
    }
  }
  
  // Mark the first segment as a first segment.

  id_list::const_iterator lfirst_seg = xline_mbrs.begin();
  ++lfirst_seg;

  assertion(xhost.segments().contains(*lfirst_seg));

  xhost.first_segments().insert_member(*lfirst_seg);

  // Mark the last segment as a last segment  
  
  id_list::const_iterator llast_seg = xline_mbrs.end();
  --llast_seg;
  --llast_seg;

  assertion(xhost.segments().contains(*llast_seg));
  
  xhost.last_segments().insert_member(*llast_seg);

  // Mark the line as new.

  xhost.new_lines().insert(xresult);
  xhost.modified_lines().erase(xresult);
  xhost.deleted_lines().erase(xresult);

  // Postconditions:

  ensure(xhost.lines().contains(xresult));
  ensure(xhost.lines().ct() == old_lines_ct + 1);
  ensure(xhost.base_space().cover_is_empty(UPPER, xresult));
  ensure(!xhost.base_space().cover_is_empty(LOWER, xresult));
  ensure(unexecutable("Lower cover contains segments in xline_mbrs"));
  ensure(xhost.new_lines().find(xresult) != xhost.new_lines().end());
  ensure(xhost.modified_lines().find(xresult) == xhost.modified_lines().end());
  ensure(xhost.deleted_lines().find(xresult) == xhost.deleted_lines().end());
  

  // Exit:

  // cout << "Leaving kd_line::new_line." << endl;
  return; 
}

geometry::kd_line::
kd_line(kd_lattice& xhost, const scoped_index& xid)
  : kd_member(xhost, xid)
{
  
  // Preconditions:

  require(xhost.lines().contains(xid));
  
  // Body:
  
  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(&host() == &xhost);
  ensure(id() == xid);

  // Exit:

  return; 
}

geometry::kd_line::
kd_line(const kd_line& xother)
  : kd_member(xother)
{
  
  // Preconditions:

    
  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

geometry::kd_line::
~kd_line()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

void
geometry::kd_line::
members(id_list_list& xmbrs, bool xinclude_segments) const
{
  // Preconditions:

  require(precondition_of(members(host(),id(), xmbrs, xinclude_segments)));
  
  // Body:

  members(*_host, _id, xmbrs, xinclude_segments);
  
  // Postconditions:

  ensure(postcondition_of(members(host(),id(), xmbrs, xinclude_segments)));

  // Exit:

  return;
}

void
geometry::kd_line::
members(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xmbrs, bool xinclude_segments)
{
  // cout << endl << "Entering kd_line::members." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));

  define_old_variable(size_type old_xmbrs_size = xmbrs.size());
  define_old_variable(size_type old_xmbrs_back_size = xmbrs.empty() ? 0 : xmbrs.back().size());
  
  // Body:

  // Lower cover is either empty, contains only bottom or contains only segments.

  const base_space_poset& lbase = xhost.base_space();
  
  if(!lbase.cover_is_empty(LOWER, xid) && !lbase.is_atom(xid))
  {
    // Lower cover contains only segments.
    
    index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
    scoped_index lid = xhost.base_space().member_id(false);
    while(!litr.is_done())
    {
      lid = litr.hub_pod();
      assertion(xhost.segments().contains(lid));
      kd_segment::members(xhost, lid, xmbrs, xinclude_segments);
      litr.next();
    }
    xhost.base_space().release_cover_id_space_iterator(litr);
  }
  
  // Postconditions:

  ensure(xmbrs.size() >= old_xmbrs_size);
  ensure(xmbrs.empty() || xmbrs.back().size() >= old_xmbrs_back_size);

  // Exit:

  // cout << "Leaving kd_line::members." << endl;
  return;
}

void
geometry::kd_line::
members(id_list_list& xmbrs, pt_list_list& xcoords, bool xinclude_segments) const
{
  // Preconditions:

  require(precondition_of(members(host(),id(), xmbrs, xcoords, xinclude_segments)));
  
  // Body:

  members(*_host, _id, xmbrs, xcoords, xinclude_segments);
  
  // Postconditions:

  ensure(postcondition_of(members(host(),id(), xmbrs, xcoords, xinclude_segments)));

  // Exit:

  return;
}

void
geometry::kd_line::
members(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xmbrs, pt_list_list& xcoords, bool xinclude_segments)
{
  // cout << endl << "Entering kd_line::members." << endl;
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));

  define_old_variable(size_type old_xmbrs_size = xmbrs.size());
  define_old_variable(size_type old_xmbrs_back_size = xmbrs.empty() ? 0 : xmbrs.back().size());
  
  // Body:

  // Lower cover is either empty, contains only bottom or contains only segments.

  const base_space_poset& lbase = xhost.base_space();
  
  if(!lbase.cover_is_empty(LOWER, xid) && !lbase.is_atom(xid))
  {
    // Lower cover contains only segments.
    
    index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
    scoped_index lid = xhost.base_space().member_id(false);
    while(!litr.is_done())
    {
      lid = litr.hub_pod();
      assertion(xhost.segments().contains(lid));
      kd_segment::members(xhost, lid, xmbrs, xcoords, xinclude_segments);
      litr.next();
    }
    xhost.base_space().release_cover_id_space_iterator(litr);
  }
  
  // Postconditions:

  ensure(xmbrs.size() >= old_xmbrs_size);
  ensure(xmbrs.empty() || xmbrs.back().size() >= old_xmbrs_back_size);

  // Exit:

  // cout << "Leaving kd_line::members." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_line::
front() const
{
  // cout << endl << "Entering kd_line::front." << endl;

  // Preconditions:

  require(precondition_of(front(host(), id())));

  // Body:

  scoped_index result = front(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(front(host(), id())));

  // Exit:

  // cout << "Leaving kd_line::front." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_line::
front(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_line::front." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));

  // Body:

  const base_space_poset& lbase = xhost.base_space();

  // Lower cover is either empty, contains only bottom or contains only segments.

  scoped_index result = lbase.member_id(false);
  if(!lbase.cover_is_empty(LOWER, xid))
  {
    result = lbase.first_cover_member(LOWER, xid.hub_pod());
    if(xhost.segments().contains(result))
    {
      // Get the id of the first point in the segment.

      result = lbase.first_cover_member(LOWER, result);
    }
    else
    {
      result.invalidate();
    }
  }
  
  
  // Postconditions:

  ensure(result.is_valid() ? xhost.base_space().vertices().contains_member(result) : true);
  
  // Exit:

  // cout << "Leaving kd_line::front." << endl;
  return result;
}

void
geometry::kd_line::
push_front(const scoped_index& xpt_id)
{
  // cout << endl << "Entering kd_line::push_front." << endl;

  // Preconditions:

  require(precondition_of(push_front(host(), id(), xpt_id)));

  // Body:

  push_front(*_host, _id, xpt_id);

  // Postconditions:

  ensure(postcondition_of(push_front(host(), id(), xpt_id)));

  // Exit:

  // cout << "Leaving kd_line::push_front." << endl;
  return;
}

void
geometry::kd_line::
push_front(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id)
{
  // cout << endl << "Entering kd_line::push_front." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.lines().contains(xid));
  require(xhost.base_space().vertices().contains_member(xpt_id));
  require(!is_empty(xhost, xid));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();  
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);

  scoped_index lold_seg_id = lbase.member_id(litr.hub_pod(), false);
  
  // Get its first point of the first segment.

  scoped_index lold_pt_id = kd_segment::point(xhost, lold_seg_id, 0);
  
  // Create the new segment.

  scoped_index lnew_seg_id = kd_segment::new_segment(xhost, xpt_id, lold_pt_id);
  
  // Link the new segment into this line at the beginning.

  lbase.insert_cover_member(lnew_seg_id, LOWER, xid, litr);

  // Release the cover iterator.

  lbase.release_cover_id_space_iterator(litr);

  // Update first segments.

  xhost.first_segments().remove_member(lold_seg_id);
  xhost.first_segments().insert_member(lnew_seg_id);
  
  // Postconditions:

  ensure(xpt_id == front(xhost, xid));
  
  // Exit:

  // cout << "Leaving kd_line::push_front." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_line::
back() const
{
  // cout << endl << "Entering kd_line::back." << endl;

  // Preconditions:

  require(precondition_of(back(host(), id())));

  // Body:

  scoped_index result = back(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(back(host(), id())));

  // Exit:

  // cout << "Leaving kd_line::back." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_line::
back(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_line::back." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));

  // Body:

  const base_space_poset& lbase = xhost.base_space();

  // No quick way to get to the back.

  scoped_index result; // Invalid by default.

  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  while(!litr.is_done())
  {
    result = litr.hub_pod();
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);

  if(xhost.segments().contains(result))
  {
    // Get the second point.

    result = kd_segment::point(xhost, result, 1);
  }
  else
  {
    // Line either empty or invalid.

    result.invalidate();
  }
  
  // Postconditions:

  ensure(result.is_valid() ? xhost.base_space().vertices().contains_member(result) : true);
  
  // Exit:

  // cout << "Leaving kd_line::back." << endl;
  return result;
}

void
geometry::kd_line::
push_back(const scoped_index& xpt_id)
{
  // cout << endl << "Entering kd_line::push_back." << endl;

  // Preconditions:

  require(precondition_of(push_back(host(), id(), xpt_id)));

  // Body:

  push_back(*_host, _id, xpt_id);

  // Postconditions:

  ensure(postcondition_of(push_back(host(), id(), xpt_id)));

  // Exit:

  // cout << "Leaving kd_line::push_back." << endl;
  return;
}

void
geometry::kd_line::
push_back(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id)
{
  // cout << endl << "Entering kd_line::push_back." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.lines().contains(xid));
  require(xhost.base_space().vertices().contains_member(xpt_id));
  require(!is_empty(xhost, xid));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();  

  // No quick way to get to the back.

  scoped_index llast_seg_id;

  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  while(!litr.is_done())
  {
    llast_seg_id = litr.hub_pod();
    litr.next();
  }
  lbase.release_cover_id_space_iterator(litr);

  assertion(xhost.segments().contains(llast_seg_id));

  // Get the second point of the last segment.

  scoped_index llast_pt_id = kd_segment::point(xhost, llast_seg_id, 1);
  
  // Create the new segment.

  scoped_index lnew_seg_id = kd_segment::new_segment(xhost, llast_pt_id, xpt_id);
  
  // Link the new segment into this line at the end.

  lbase.insert_cover_member(lnew_seg_id, LOWER, xid);

  // Update last segments.

  xhost.last_segments().remove_member(llast_seg_id);
  xhost.last_segments().insert_member(lnew_seg_id);
  
  // Postconditions:

  ensure(xpt_id == back(xhost, xid));
  
  // Exit:

  // cout << "Leaving kd_line::push_back." << endl;
  return;
}


bool
geometry::kd_line::
is_empty() const
{
  // cout << endl << "Entering kd_line::is_empty." << endl;

  // Preconditions:

  require(precondition_of(is_empty(host(), id())));

  // Body:

  bool result = is_empty(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_empty(host(), id())));

  // Exit:

  // cout << "Leaving kd_line::is_empty." << endl;
  return result;
}

bool
geometry::kd_line::
is_empty(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_line::is_empty." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));

  // Body:

  const base_space_poset& lbase = xhost.base_space();

  bool result = lbase.cover_is_empty(LOWER, xid);
  
  if(!result)
  {
    result = !xhost.segments().contains(lbase.first_cover_member(LOWER, xid.hub_pod()));
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line::is_empty." << endl;
  return result;
}

bool
geometry::kd_line::
is_closed() const
{
  // cout << endl << "Entering kd_line::is_closed." << endl;

  // Preconditions:

  require(precondition_of(is_closed(host(), id())));

  // Body:

  bool result = is_closed(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(is_closed(host(), id())));

  // Exit:

  // cout << "Leaving kd_line::is_closed." << endl;
  return result;
}

bool
geometry::kd_line::
is_closed(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_line::is_closed." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));
  require(!is_empty(xhost, xid));

  // Body:

  id_list_list lpt_ids;
  kd_line::members(xhost, xid, lpt_ids, false);
  
  bool result = (lpt_ids.front().front() == lpt_ids.back().back());
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line::is_closed." << endl;
  return result;
}

void
geometry::kd_line::
insert_segment(const scoped_index& xnew_seg_id, const scoped_index& xold_seg_id, bool xafter)
{
  // cout << endl << "Entering kd_line::insert_segment." << endl;

  // Preconditions:

  require(precondition_of(insert_segment(host(), id(), xnew_seg_id, xold_seg_id, xafter)));

  // Body:

  insert_segment(*_host, _id, xnew_seg_id, xold_seg_id, xafter);

  // Postconditions:

  ensure(postcondition_of(insert_segment(host(), id(), xnew_seg_id, xold_seg_id, xafter)));

  // Exit:

  // cout << "Leaving kd_line::insert_segment." << endl;
  return;
}

void
geometry::kd_line::
insert_segment(kd_lattice& xhost, 
               const scoped_index& xid, 
               const scoped_index& xnew_seg_id, 
               const scoped_index& xold_seg_id, 
               bool xafter)
{
  // cout << endl << "Entering kd_line::insert_segment." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.lines().contains(xid));
  require(!is_empty(xhost, xid));
  require(xhost.segments().contains(xnew_seg_id));
  require(xhost.segments().contains(xold_seg_id));
  require(xhost.base_space().cover_contains_member(LOWER, xid, xold_seg_id));

  // Body:

  // Find the old segment in the lower cover of the line.

  base_space_poset& lbase = xhost.base_space();
  
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  while(!litr.is_done())
  {
    if(litr.hub_pod() == xold_seg_id.hub_pod())
    {
      break;
    }
    litr.next();
  }
  
  assertion(!litr.is_done());
  
  // Iterator is pointing at xold_seg_id.

  if(xafter)
  {    
    // Need to insert new segment after xid,
    // but insert with iterator inserts before.

    litr.next();
  }
  
  if(litr.is_done())
  {
    // Iterator is done, insert at the end of the cover.

    lbase.insert_cover_member(xnew_seg_id, LOWER, xid);
  }
  else
  {
    // Iterator is not done, insert at the current iterator position.

    lbase.insert_cover_member(xnew_seg_id, LOWER, xid, litr);
  }
  
  lbase.insert_cover_member(xid, UPPER, xnew_seg_id);
  
  //  lbase.new_link(xid, xnew_seg_id);

  lbase.release_cover_id_space_iterator(litr);
  
  // Postconditions:

  ensure(xhost.base_space().contains_link(xid, xnew_seg_id));
  ensure(unexecutable("xafter ? xnew_seg_id is after xold_seg_id : xnew_seg_id is before xold_seg_id"));

  // Exit:

  // cout << "Leaving kd_line::insert_segment." << endl;
  return;
}

void
geometry::kd_line::
surface(scoped_index& xresult) const
{
  // cout << endl << "Entering kd_line::surface." << endl;

  // Preconditions:

  require(precondition_of(surface(host(), id(), xresult)));
  
  // Body:

  surface(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(surface(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_line::surface." << endl;
  return;
}

void
geometry::kd_line::
surface(const kd_lattice& xhost, const scoped_index& xid, scoped_index& xresult)
{
  // cout << endl << "Entering kd_line::surface." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().is_active(xid));
  
  // Body:

  const base_space_poset& lbase = xhost.base_space();

  xresult = lbase.member_id(false);
  
  if(lbase.cover_is_empty(UPPER, xid))
  {
    xresult.invalidate();
  }
  else
  {
    xresult = lbase.first_cover_member(UPPER, xid.hub_pod());
  }

  // Postconditions:

  ensure(!xresult.is_valid() || xhost.surfaces().contains(xresult));
  
  // Exit:

  // cout << "Leaving kd_line::surface." << endl;
  return;
}

sheaf::scoped_index
geometry::kd_line::
surface() const
{
  // cout << endl << "Entering kd_line::surface." << endl;

  // Preconditions:

  require(precondition_of(surface(host(), id())));
  
  // Body:

  scoped_index result(surface(host(), id()));
  
  // Postconditions:

  ensure(postcondition_of(surface(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_line::surface." << endl;
  return result;
}

sheaf::scoped_index
geometry::kd_line::
surface(const kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_line::surface." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().is_active(xid));
  
  // Body:

  const base_space_poset& lbase = xhost.base_space();

  scoped_index result = lbase.member_id(false);
  
  if(!lbase.cover_is_empty(UPPER, xid))
  {
    result = lbase.first_cover_member(UPPER, xid.hub_pod());
  }

  // Postconditions:

  ensure(!result.is_valid() || xhost.surfaces().contains(result));
  
  // Exit:

  // cout << "Leaving kd_line::surface." << endl;
  return result;
}

void
geometry::kd_line::
surfaces(id_set& xresult) const
{
  // cout << endl << "Entering kd_line::surfaces." << endl;

  // Preconditions:

  require(precondition_of(surfaces(host(), id(), xresult)));
  
  // Body:

  surfaces(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(surfaces(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_line::surfaces." << endl;
  return;
}

void
geometry::kd_line::
surfaces(const kd_lattice& xhost, const scoped_index& xid, id_set& xresult)
{
  // cout << endl << "Entering kd_line::surfaces." << endl;
  // cout << "line: " << xid.pod() << endl;
  
  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));
  
  // Body:

  xresult.clear();
  
  const base_space_poset& lbase = xhost.base_space();
  base_space_member lline_mbr(&lbase, xid);

  // First find any surfaces this line is directly contained in.

  hash_set_postorder_itr lup_itr(lline_mbr, "surfaces", UP, NOT_STRICT);
  while(!lup_itr.is_done())
  {
    // cout << "found surface: " << lup_itr.index().pod() << " in the upset of this" << endl;
    xresult.insert(lup_itr.index());
    lup_itr.next();
  }

  // Iterate over the intersection points in the down set of the line.
  
  hash_set_postorder_itr ldown_itr(lline_mbr, "intersection_points", DOWN, NOT_STRICT);
  while(!ldown_itr.is_done())
  {
    // Find all the surfaces in the upset 
    // of the current vertex. Don't
    // reset the visted markers so we don't
    // traverse anything in the upset of
    // some previous vertex.

    lup_itr.put_anchor(ldown_itr.index());
    lup_itr.reset(false);
    while(!lup_itr.is_done())
    {
      // cout << "found surface: " << lup_itr.index().pod();
      // cout << " in the upset of intersection point " << ldown_itr.index().pod() << endl;
      xresult.insert(lup_itr.index());
      lup_itr.next();
    }
    
    ldown_itr.next();
  }

  lline_mbr.detach_from_state();

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line::surfaces." << endl;
  return;
}

void
geometry::kd_line::
connected_lines(id_set& xresult) const
{
  // cout << endl << "Entering kd_line::connected_lines." << endl;

  // Preconditions:

  require(precondition_of(connected_lines(host(), id(), xresult)));
  
  // Body:

  connected_lines(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(connected_lines(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_line::connected_lines." << endl;
  return;
}

void
geometry::kd_line::
connected_lines(const kd_lattice& xhost, const scoped_index& xid, id_set& xresult)
{
  // cout << endl << "Entering kd_line::connected_lines." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));
  require(surface(xhost, xid).is_valid());
  
  // Body:

  xresult.clear();

  // A line is always connected to itself.

  xresult.insert(xid);

  scoped_index lthis_surface_id;
  surface(xhost, xid, lthis_surface_id);

  scoped_index lother_surface_id;  
  
  const base_space_poset& lbase = xhost.base_space();
  base_space_member lline_mbr(&lbase, xid);

  hash_set_postorder_itr lup_itr(lline_mbr, "lines", UP);

  // Iterate over the intersection points in the down set of the line.
  
  hash_set_postorder_itr ldown_itr(lline_mbr, "intersection_points", DOWN, NOT_STRICT);
  while(!ldown_itr.is_done())
  {
    // Find all the lines in the upset 
    // of the current vertex. Don't
    // reset the visited markers so we don't
    // traverse anything in the upset of
    // some previous vertex.

    lup_itr.put_anchor(ldown_itr.index());
    lup_itr.reset(false);

    while(!lup_itr.is_done())
    {
      xresult.insert(lup_itr.index());
      lup_itr.next();
    }

    ldown_itr.next();
  }

  lline_mbr.detach_from_state();

  // Postconditions:

  ensure(xresult.find(xid) != xresult.end());
  
  // Exit:

  // cout << "Leaving kd_line::connected_lines." << endl;
  return;
}

void
geometry::kd_line::
faces(id_list& xresult) const
{
  // cout << endl << "Entering kd_line::faces." << endl;

  // Preconditions:

  require(precondition_of(faces(host(), id(), xresult)));
  
  // Body:

  faces(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(faces(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_line::faces." << endl;
  return;
}

void
geometry::kd_line::
faces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_line::faces." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));

  define_old_variable(size_type old_xresult_size = xresult.size());
  
  // Body:

  scoped_index lid;

  id_set lfaces;
  
  index_space_iterator& ls_itr = xhost.base_space().get_cover_id_space_iterator(LOWER, xid);
  scoped_index ls_id = xhost.base_space().member_id(false);
  while(!ls_itr.is_done())
  {
    ls_id = ls_itr.hub_pod();
    kd_segment::face(xhost, ls_id, lid);
    
    if(lfaces.insert(lid).second)
    {
      xresult.push_back(lid);
    }
    ls_itr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(ls_itr);

  // Postconditions:

  ensure(xresult.size() >= old_xresult_size);
  
  // Exit:

  // cout << "Leaving kd_line::faces." << endl;
  return;
}

void
geometry::kd_line::
zones(id_list& xresult) const
{
  // cout << endl << "Entering kd_line::zones." << endl;

  // Preconditions:

  require(precondition_of(zones(host(), id(), xresult)));
  
  // Body:

  zones(host(), id(), xresult);
  
  // Postconditions:

  ensure(postcondition_of(zones(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_line::zones." << endl;
  return;
}

void
geometry::kd_line::
zones(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult)
{
  // cout << endl << "Entering kd_line::zones." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));
  
  // Body:

  xresult.clear();
  
  id_list lface_ids;

  cells(xhost, xid, lface_ids, xresult);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line::zones." << endl;
  return;
}

void
geometry::kd_line::
cells(id_list& xfaces, id_list& xzones) const
{
  // cout << endl << "Entering kd_line::cells." << endl;

  // Preconditions:

  require(precondition_of(cells(host(), id(), xresult)));
  
  // Body:

  cells(host(), id(), xfaces, xzones);
  
  // Postconditions:

  ensure(postcondition_of(cells(host(), id(), xresult)));

  // Exit:

  // cout << "Leaving kd_line::cells." << endl;
  return;
}

void
geometry::kd_line::
cells(const kd_lattice& xhost, const scoped_index& xid, id_list& xfaces, id_list& xzones)
{
  // cout << endl << "Entering kd_line::cells." << endl;

  // Preconditions:

  require(xhost.base_space().state_is_read_accessible());
  require(xhost.lines().contains(xid));

  define_old_variable(size_type old_xfaces_size = xfaces.size());
  define_old_variable(size_type old_xzones_size = xzones.size());
  
  // Body:

  if(xfaces.empty())
  {
    faces(xhost, xid, xfaces);
  
    for(id_list::iterator i = xfaces.begin(); i != xfaces.end(); ++i)
    {
      kd_face::zones(xhost, *i, xzones);
    }
  }
  else
  {
    id_list::iterator lold_last_face = --xfaces.end();
    
    faces(xhost, xid, xfaces);
  
    for(id_list::iterator i = ++lold_last_face; i != xfaces.end(); ++i)
    {
      kd_face::zones(xhost, *i, xzones);
    }
  }
  

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_line::cells." << endl;
  return;
}

void
geometry::kd_line::
clear(pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_line::clear." << endl;

  // Preconditions:

  require(precondition_of(clear(host(), id(), xdeleted)));
  
  // Body:

  clear(*_host, _id, xdeleted);

  // Postconditions:

  ensure(postcondition_of(clear(host(), id(), xdeleted)));

  // Exit:

  // cout << "Leaving kd_line::clear." << endl;
  return;
}

void
geometry::kd_line::
clear(kd_lattice& xhost, const scoped_index& xid, pod_id_hash_set& xdeleted)
{
  // cout << endl << "Entering kd_line::clear." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.lines().contains(xid));
  require(!is_empty(xhost, xid));
  
  // Body:

  base_space_poset& lbase = xhost.base_space();

  scoped_index lpt_ids[kd_segment::POINT_CT];
  scoped_index& lpt0_id = lpt_ids[0];
  scoped_index& lpt1_id = lpt_ids[1];
  
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xid);
  scoped_index lid = lbase.member_id(false);
  while(!litr.is_done())
  {
    lid = litr.hub_pod();

    xdeleted.insert(lid);
    kd_segment::clear(xhost, lid, lpt_ids);
    kd_segment::deactivate(xhost, lid);
    
    if(lbase.cover_is_empty(UPPER, lpt0_id))
    {
      kd_point::deactivate(xhost, lpt0_id);
    }
    else
    {
      kd_point::update_cohorts(xhost, lpt0_id);
    }

    litr.next();
  }

  lbase.release_cover_id_space_iterator(litr);

  // Still have to check last point.
    
  if(lbase.cover_is_empty(UPPER, lpt1_id))
  {
    kd_point::deactivate(xhost, lpt1_id);
  }
  else
  {
    kd_point::update_cohorts(xhost, lpt1_id);
  }
  
  lbase.remove_cover_members(hash_set_filter(xdeleted), LOWER, xid);

  // The line has exactly one member in its upper cover,
  // the surface that contains it. Delete the link.

  pod_index_type lsurf_id = lbase.first_cover_member(UPPER, xid.hub_pod());
  lbase.delete_link(lsurf_id, xid);
  
  // Postconditions:

  ensure(xhost.base_space().cover_is_empty(UPPER, xid));
  ensure(xhost.base_space().cover_is_empty(LOWER, xid));
  
  // Exit:

  // cout << "Leaving kd_line::clear." << endl;
  return;
}

void
geometry::kd_line::
deactivate()
{
  // cout << endl << "Entering kd_line::deactivate." << endl;

  // Preconditions:

  require(precondition_of(deactivate(host(), id())));

  // Body:

  deactivate(*_host, _id);

  // Postconditions:

  ensure(postcondition_of(deactivate(host(), id())));

  // Exit:

  // cout << "Leaving kd_line::deactivate." << endl;
  return;
}

void
geometry::kd_line::
deactivate(kd_lattice& xhost, const scoped_index& xid)
{
  // cout << endl << "Entering kd_line::deactivate." << endl;

  // Preconditions:

  require(xhost.base_space().in_jim_edit_mode());
  require(xhost.lines().contains(xid));
  require(xhost.base_space().cover_is_empty(UPPER, xid));
  require(xhost.base_space().cover_is_empty(LOWER, xid));
  

  // Body:

  xhost.lines().delete_member(xid);
  xhost.new_lines().erase(xid);
  xhost.modified_lines().erase(xid);
  xhost.deleted_lines().insert(xid);
  
  // Postconditions:

  ensure(!xhost.lines().is_active(xid));
  ensure(xhost.new_lines().find(xid) == xhost.new_lines().end());
  ensure(xhost.modified_lines().find(xid) == xhost.modified_lines().end());
  ensure(xhost.deleted_lines().find(xid) != xhost.deleted_lines().end());
  
  // Exit:

  // cout << "Leaving kd_line::deactivate." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

geometry::kd_line::
kd_line()
{
  
  // Preconditions:

    
  // Body:  

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::kd_line::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const kd_line*>(other) != 0;

  // Postconditions:

  return result;
}

geometry::kd_line*
geometry::kd_line::
clone() const
{
  kd_line* result;
  
  // Preconditions:

  // Body:
  
  result = new kd_line();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

geometry::kd_line&
geometry::kd_line::
operator=(const kd_line& xother)
{
  
  // Preconditions:

    
  // Body:
  
  kd_member::operator=(xother);
  
  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

geometry::kd_line&
geometry::kd_line::
operator=(const any& xother)
{
  
  // Preconditions:

  require(is_ancestor_of(&xother));
    
  // Body:
  
  kd_member::operator=(xother);

  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}

bool
geometry::kd_line::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(kd_member::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, const kd_line& xn)
{
  // Preconditions:

  require(xn.host().coords().state_is_read_accessible());

  // Body:

  xos << "line " << xn.host().lines().id_space().pod(xn.id());
  xos << "  top id: " << xn.id();
  xos << "  name: " << xn.name();
  xos << "  type: " << xn.type_name();
  xos << boolalpha;
  xos << "  is_jim: " << xn.is_jim();
  xos << "  is_leaf: " << xn.is_leaf();
  xos << noboolalpha;
  xos << endl;
  
  xos << "\tlower cover:";
  const base_space_poset& lbase = xn.host().base_space();
  index_space_iterator& litr = lbase.get_cover_id_space_iterator(LOWER, xn.id());
  while(!litr.is_done())
  {
    xos << "   " << lbase.member_name(litr.hub_pod());
    litr.next();
  }
  xos << endl;
  lbase.release_cover_id_space_iterator(litr);

  // Postconditions:

  // Exit:

  return xos;
}

size_t
geometry::
deep_size(const kd_line& xn, bool xinclude_shallow)
{
  size_t result = 0;

  // Preconditions:

  // Body:

  not_implemented();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
