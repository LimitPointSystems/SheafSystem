
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class d_bin_point_locator

#ifndef D_BIN_POINT_LOCATOR_IMPL_H
#define D_BIN_POINT_LOCATOR_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef D_BIN_POINT_LOCATOR_H
#include "d_bin_point_locator.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef CHART_POINT_3D_H
#include "chart_point_3d.h"
#endif

#ifndef D_BIN_COORDINATES_H
#include "d_bin_coordinates.h"
#endif

#ifndef EVAL_ITERATOR_H
#include "eval_iterator.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef PREORDER_ITERATOR_H
#include "preorder_iterator.h"
#endif

#ifndef SEC_AT1_SPACE_H
#include "sec_at1_space.h"
#endif

#ifndef SEC_ED_H
#include "sec_ed.h"
#endif


//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{

// ===========================================================
// D_BIN_POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
d_bin_point_locator<DC, DB>::
d_bin_point_locator(sec_ed& xcoords)
    : point_locator(xcoords),
	_eval_itr(xcoords.schema(), false)
{
  // Preconditions:

  require(precondition_of(point_locator(xcoords)));

  // Body:

  _bin_ub.reserve(DC);
  _bin_ub.set_ct(DC);

  _bin_size.reserve(DC);
  _bin_size.set_ct(DC);

  _one_over_min_bin_size.reserve(DC);
  _one_over_min_bin_size.set_ct(DC);

  _box_ct = 0;

  // The eval_itr owns the evaluator_family which owns the section_evaluators.
  // The bounding boxes in _boxes keep pointers to these section evaluators.
  // So the lifetime of the eval_family must be as long as _boxes.

  /// @hack a new eval_family is created every time put_schema_anchor(schema)
  /// is called in eval_itr, including initially from the eval_itr constructor.
  /// But we have to reanchor the eval_itr to each branch of a multisection
  /// in update(). We can do this only with put_schema_anchor(index),
  /// which does not recreate the eval family, if we initialize eval_itr here
  /// using its constructor, then force it to be done, ready for reanchoring.

  _eval_itr.force_is_done();

  // Postconditions:


  // Exit:

  return;
}

template <int DC, int DB>
d_bin_point_locator<DC, DB>::
~d_bin_point_locator()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

template <int DC, int DB>
bool
d_bin_point_locator<DC, DB>::
invariant() const
{
  bool result = true;

  invariance(coordinates().schema().df() == DC);


  return result;
}


template <int DC, int DB>
const block<size_type>&
d_bin_point_locator<DC, DB>::
bin_ub() const
{
  // Preconditions:


  // Body:

  const block<size_type>& result = _bin_ub;

  // Postconditions:

  ensure_for_all(i, 0, dc(), result[i] > 0);

  // Exit:

  return result;
}

template <int DC, int DB>
const block<sec_vd_value_type>&
d_bin_point_locator<DC, DB>::
bin_size() const
{

  // Preconditions:


  // Body:

  const block<sec_vd_value_type>& result  = _bin_size;

  // Postconditions:


  // Exit:

  return result;
}


template <int DC, int DB>
size_type
d_bin_point_locator<DC, DB>::
box_ct() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = _box_ct;

  // Postconditions:


  // Exit:

  return result;
}

template <int DC, int DB>
bool
d_bin_point_locator<DC, DB>::
is_empty() const
{
  bool result;

  // Preconditions:


  // Body:

  result = (box_ct() == 0);

  // Postconditions:

  ensure(result == (box_ct() == 0));

  // Exit:

  return result;
}


template <int DC, int DB>
d_bin_coordinates<DC, DB>*
d_bin_point_locator<DC, DB>::
relative_position(sec_vd_value_type* xpt, size_type xpt_ub) const
{
  d_bin_coordinates<DC, DB>* result;

  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= dc());

  // Body:

  result = new d_bin_coordinates<DC, DB>();
  relative_position_pa(xpt, xpt_ub, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(relative_position_pa(xpt, xpt_ub, result)));

  // Exit:

  return result;
}

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
relative_position_pa(sec_vd_value_type* xpt,
                     size_type xpt_ub,
                     d_bin_coordinates<DC, DB>& xresult) const
{
  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= dc());

  // Body:

  sec_vd_value_type lrel_pos[DC];

//   cerr << "  d_bin_point_locator<" << DC << ", " << DB
//        <<">::relative_position_pa:" << endl;
//   cerr << "    i, xpt[i], _lb[i], _one_over_min_bin_size[i], lrel_pos[i] = "
//        << endl;

  for(int i=0; i<DC; i++)
  {
    lrel_pos[i] = (xpt[i] - _lb[i])*_one_over_min_bin_size[i];

//     cerr << "    " << i << ", " << xpt[i] << ", " << _lb[i] << ", "
//          << _one_over_min_bin_size[i] <<  ", " << lrel_pos[i]
//          << endl;
  }
//   cerr << endl;

  xresult = lrel_pos;

  // Postconditions:

  // Exit:

  return;
}


template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
insert_box(d_bounding_box<DC, DB>* xbox)
{
  // Preconditions:

  require(xbox != 0);

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  is_abstract();

  // Postconditions:

  ensure(contains_box(xbox));
  ensure(box_ct() == old_box_ct + 1);

  // Exit:

  return;
}

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
remove_box(d_bounding_box<DC, DB>* xbox)
{
  // Preconditions:

  require(xbox != 0);
  require(contains_box(xbox));

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  is_abstract();

  // Postconditions:

  ensure(!contains_box(xbox));
  ensure(box_ct() == old_box_ct - 1);

  // Exit:

  return;
}

template <int DC, int DB>
const typename d_bin_point_locator<DC, DB>::box_list_type&
d_bin_point_locator<DC, DB>::
box_list(sec_vd_value_type* xpt, size_type xpt_ub) const
{
  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= dc());
  require(domain_contains(xpt, xpt_ub));

  // Body:


  is_abstract();

  static box_list_type result; // just to avoid compiler warnings

  // Postconditions:


  // Exit:

  return result;
}

template <int DC, int DB>
bool
d_bin_point_locator<DC, DB>::
contains_box(d_bounding_box<DC, DB>* xbox) const
{
  bool result = true;

  // Preconditions:

  require(xbox != 0);

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
clear()
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_empty());

  // Exit:

  return;
}

template <int DC, int DB>
const block<sec_vd_dof_type>&
d_bin_point_locator<DC, DB>::
gathered_dofs() const
{
  return this->_gathered_dofs;
}


// PROTECTED MEMBER FUNCTIONS

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
update_bins()
{
  // Preconditions:

  require(is_empty());

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}


// ===========================================================
// POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
update()
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering update");
#endif

  // Preconditions:

  require(this->coordinates().state_is_read_accessible());

  // Body:

  update(true, 256); // Arbitrary eval capacity

  // Postconditions:

  ensure(!is_empty());

  // Exit:

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Leaving update");
#endif

  return;
}

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
update(bool xpopulate, size_type xeval_capacity)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering update(bool)");
#endif

//   cerr << endl;
//   cerr << "Entering d_bin_point_locator<" << DC << ", " << DB
//        <<">::update:" << endl;
//   cerr << "  xpopulate = " << boolalpha << xpopulate << endl; 
//   cerr << "  xeval_capacity = " <<  xeval_capacity << endl; 
//   cerr << endl;

  // Preconditions:

  require(this->coordinates().state_is_read_accessible());

  // Body:

  this->update_domain();
  this->update_bins();

  // For each coordinate field evaluator, we need to
  // create a bounding box and insert the bounding box into the search structure.
  // It's more efficient if we allocate all the bounding boxes at once.
  // It's also more efficient if we gather all the dofs for each evaluator
  // in advance. So find out how many evaluators we have:

  size_type leval_ct = this->coordinates().schema().evaluation_ct();

  if(xeval_capacity < leval_ct)
  {
    xeval_capacity = leval_ct;
  }
  
  // We need one bounding box for each evaluation_member.

  this->_boxes.reserve(xeval_capacity);
  this->_boxes.set_ct(0);

  // Start the dof buffer off at a reasonable size.
  // We don't know how many dofs there are for each element,
  // but the buffer will resize as necessary.

  this->_gathered_dofs.reserve(xeval_capacity*DC*8);
  this->_gathered_dofs.set_ct(0);

  if(xpopulate)
  {
    // Iterate over the branches.
    /// @hack the multisection hack.

    sec_vd lbranch;
    preorder_iterator lbranch_itr(coordinates(), "jims", DOWN, NOT_STRICT);
    while(!lbranch_itr.is_done())
    {
      // Get a handle to this branch.

      const scoped_index& lbranch_id = lbranch_itr.index();
      lbranch.attach_to_state(coordinates().host(), lbranch_id);

      // Re-anchor the eval itr to this branch.

      _eval_itr.put_schema_anchor(lbranch.schema().index());
      _eval_itr.reset(false);

      // Get the discretization members from the iterator.

      block<scoped_index>& ldisc_mbrs = _eval_itr.discretization_members();

      // Iterate over the eval members in this branch,

      while(!_eval_itr.is_done())
      {
	// Save the starting location of the dofs for this eval member.

	size_type lold_dofs_ct    = this->_gathered_dofs.ct();
	sec_vd_dof_type* dofs_ptr = this->_gathered_dofs.base() + lold_dofs_ct;

	// Gather the dofs for this eval member.

	_eval_itr.gather_dofs(lbranch, this->_gathered_dofs);

	// Get the number of dofs for this eval member.

	size_type dof_ct = this->_gathered_dofs.ct() - lold_dofs_ct;

	// Get a bounding box for this eval member.

	this->_boxes.set_ct(this->_boxes.ct() + 1);
	d_bounding_box<DC, DB>& bbox = this->_boxes.back();

	// Get the evaluator for this eval member.

	section_evaluator& levaluator = _eval_itr.evaluator();

	// Get the bounds for this eval member and put them in the bounding box.
	// Must convert from the global coordinate system to search
	// structure-relative coordinates.

	sec_vd_value_type gbl_pos[DC];
	d_bin_coordinates<DC, DB> rel_pos;

	levaluator.min(dofs_ptr, dof_ct, gbl_pos, DC);
	this->relative_position_pa(gbl_pos, DC, rel_pos);

//     cerr << "  lower bound: bbox.put_lb(rel_pos)" << endl;
//     cerr << "    gbl_pos[0], rel_pos[0] = " << gbl_pos[0] << " : " << rel_pos[0] << endl;
//     cerr << "    gbl_pos[1], rel_pos[1] = " << gbl_pos[1] << " : " << rel_pos[1] << endl;
//     cerr << "    gbl_pos[2], rel_pos[2] = " << gbl_pos[2] << " : " << rel_pos[2] << endl;
//     cerr << endl;

	bbox.put_lb(rel_pos);

	levaluator.max(dofs_ptr, dof_ct, gbl_pos, DC);
	this->relative_position_pa(gbl_pos, DC, rel_pos);

//     cerr << "  upper bound: bbox.put_lb(rel_pos)" << endl;
//     cerr << "    gbl_pos[0], rel_pos[0] = " << gbl_pos[0] << " : " << rel_pos[0] << endl;
//     cerr << "    gbl_pos[1], rel_pos[1] = " << gbl_pos[1] << " : " << rel_pos[1] << endl;
//     cerr << "    gbl_pos[2], rel_pos[2] = " << gbl_pos[2] << " : " << rel_pos[2] << endl;
//     cerr << endl;

	bbox.put_ub(rel_pos);

	// Set the other attributes of the bounding box.

	bbox.put_member_id(_eval_itr.index());
	bbox.put_branch_id(lbranch_id);
	bbox.put_dofs_index(lold_dofs_ct);
	bbox.put_evaluator(&levaluator);
	bbox.put_dof_ct(dof_ct);

	// Insert the bounding box into the search structure.

	this->insert_box(&bbox);

	// Move on to the next evaluator.

	_eval_itr.next();
      }

      // Move on to the next branch.

      lbranch_itr.truncate();
    }

    lbranch.detach_from_state();
  
  } // end if(xpoluate)
  

  // Postconditions:

  ensure(is_empty() == !xpopulate);
  
  // Exit:


//   cerr << "Leaving d_bin_point_locator<" << DC << ", " << DB
//        <<">::update:" << endl;
//   cerr << endl;

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Leaving update");
#endif

  return;
}

template <int DC, int DB>
d_bounding_box<DC, DB>*
d_bin_point_locator<DC, DB>::
assign_box(const scoped_index& xmbr_id, 
	   const scoped_index& xbranch_id, 
	   section_evaluator& xeval, 
	   const sec_vd_dof_type* xdofs, 
	   size_type xdofs_ct)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering assign_box");
#endif

//   cerr << endl;
//   cerr << "Entering d_bin_point_locator<" << DC << ", " << DB
//        <<">::assign_box:" << endl;
//   cerr << endl;


  // Preconditions:

  require(this->coordinates().state_is_read_accessible());
  require(xdofs_ct > 0);
  require(xmbr_id.pod() < box_capacity());
  
  // Body:

  define_old_variable(size_type old_box_ct = box_ct());

  // Save the starting location of the dofs for this eval member.

  size_type lold_dofs_ct    = this->_gathered_dofs.ct();
  sec_vd_dof_type* dofs_ptr = this->_gathered_dofs.base() + lold_dofs_ct;

  // Make sure gathered_dofs has enough capacity;
  // forcing the last item will efficiently reallocate if needed.

  size_type llast_dof = xdofs_ct - 1;
  this->_gathered_dofs.force_item(lold_dofs_ct+llast_dof, xdofs[llast_dof]);  
  this->_gathered_dofs.set_ct(lold_dofs_ct+xdofs_ct);
  
  // Put the dofs into the gathered dofs buffer.

  for(size_type i=0; i<llast_dof; ++i)
  {
    dofs_ptr[i] = xdofs[i];
  }  
    
  // Get a bounding box for this eval member.

  //  this->_boxes.set_ct(_boxes.ct() + 1);
  //  d_bounding_box<DC, DB>* result = &(this->_boxes.back());

  d_bounding_box<DC, DB>* result = &(this->_boxes[xmbr_id.pod()]);  

  // Get the bounds for this eval member and put them in the bounding box.
  // Must convert from the global coordinate system to search
  // structure-relative coordinates.

  sec_vd_value_type gbl_pos[DC];
  d_bin_coordinates<DC, DB> rel_pos;

  xeval.min(dofs_ptr, xdofs_ct, gbl_pos, DC);
  this->relative_position_pa(gbl_pos, DC, rel_pos);

//   cerr << "  lower bound: result->put_lb(rel_pos)" << endl;
//   cerr << "    gbl_pos[0], rel_pos[0] = " << gbl_pos[0] << " : " << rel_pos[0] << endl;
//   cerr << "    gbl_pos[1], rel_pos[1] = " << gbl_pos[1] << " : " << rel_pos[1] << endl;
//   cerr << "    gbl_pos[2], rel_pos[2] = " << gbl_pos[2] << " : " << rel_pos[2] << endl;
//   cerr << endl;

  result->put_lb(rel_pos);

  xeval.max(dofs_ptr, xdofs_ct, gbl_pos, DC);
  this->relative_position_pa(gbl_pos, DC, rel_pos);

//   cerr << "  upper bound: result->put_ub(rel_pos)" << endl;
//   cerr << "    gbl_pos[0], rel_pos[0] = " << gbl_pos[0] << " : " << rel_pos[0] << endl;
//   cerr << "    gbl_pos[1], rel_pos[1] = " << gbl_pos[1] << " : " << rel_pos[1] << endl;
//   cerr << "    gbl_pos[2], rel_pos[2] = " << gbl_pos[2] << " : " << rel_pos[2] << endl;
//   cerr << endl;

  result->put_ub(rel_pos);

  // Set the other attributes of the bounding box.

  result->put_member_id(xmbr_id);
  result->put_branch_id(xbranch_id);
  result->put_dofs_index(lold_dofs_ct);
  result->put_evaluator(&xeval);
  result->put_dof_ct(xdofs_ct);

  // Postconditions:

  ensure(box_ct() == old_box_ct);
  //  ensure(allocated_box_ct() == old_allocated_box_ct+1);
  //  ensure(result == box(old_allocated_box_ct));
  ensure(result == box(xmbr_id.pod()));

  // Exit:

//   cerr << endl;
//   cerr << "Leaving d_bin_point_locator<" << DC << ", " << DB
//        <<">::assign_box:" << endl;
//   cerr << endl;

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Leaving assign_box");
#endif

  return result;
}

template <int DC, int DB>
size_type
d_bin_point_locator<DC, DB>::
box_capacity()
{
  return _boxes.ub();
}

template <int DC, int DB>
d_bounding_box<DC, DB>*
d_bin_point_locator<DC, DB>::
box(pod_index_type xi)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering box");
#endif

  // Preconditions:

  require((0 <= xi) && (xi < box_capacity()));
  
  // Body:

  d_bounding_box<DC, DB>* result = &(this->_boxes[xi]);

  // Postconditions:


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Leaving box");
#endif

  return result;
}

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
update_box(pod_index_type xi, const sec_vd_dof_type* xdofs, size_type xdofs_ct)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering update_box");
#endif

  // Preconditions:

  require((0 <= xi) && (xi < box_capacity()));
  require(box(xi)->evaluator() != 0);
  require(box(xi)->dof_ct() > 0);
  require(xdofs_ct >= box(xi)->dof_ct());
  
  // Body:

  d_bounding_box<DC, DB>& lbox = this->_boxes[xi];

  //$$SCRIBBLE: The code in remove_box and insert_box called below
  //            is not optimal for the purpose here.  Instead of
  //            remove_box we should only remove a box if it is
  //            in "old-new" and instead of insert_box only insert
  //            a box if it is in "new-old". 

  // Remove the box if necessary.

  bool lcontains_box = contains_box(&lbox);
  if(lcontains_box)
  {
    remove_box(&lbox);
  }

  sec_vd_dof_type* ldofs_begin = _gathered_dofs.base() + lbox.dofs_index();

  // Update the gathered dofs for this box.
  
  sec_vd_dof_type* lptr = ldofs_begin;
  for(size_type i=0; i<xdofs_ct; ++i, ++lptr)
  {
    *lptr = xdofs[i];
  }  

  // Update the bounds for this box.

  sec_vd_value_type gbl_pos[DC];
  d_bin_coordinates<DC, DB> rel_pos;

  section_evaluator& leval = *(lbox.evaluator());
  
  leval.min(xdofs, xdofs_ct, gbl_pos, DC);
  this->relative_position_pa(gbl_pos, DC, rel_pos);
  lbox.put_lb(rel_pos);

  leval.max(xdofs, xdofs_ct, gbl_pos, DC);
  this->relative_position_pa(gbl_pos, DC, rel_pos);
  lbox.put_ub(rel_pos);

  // Reinsert the box if necessary.

  if(lcontains_box)
  {
    insert_box(&lbox);
  }

  // Postconditions:

  // Exit:

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Leaving update_box");
#endif

  return;
}

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
point_at_value(const sec_vd_value_type* xvalue,
               size_type xvalue_ub,
               chart_point& xresult)
{
  require(xvalue != 0);
  require(xvalue_ub >= this->dc());
  require(xresult.db() >= this->db());

  // Body:

  /// @todo propagate constness everywhere.

  sec_vd_value_type* global_coords = const_cast<sec_vd_value_type*>(xvalue);

  // Initialize the chart id to invalid.
  // If the inversion succeeds, it will be set to valid.

  xresult.invalidate();

  if(this->domain_contains(global_coords, DC))
  {
    // This point is within the domain.
    // Find the bounding boxes that may contain the value.

    d_bin_coordinates<DC, DB> lrel_pos;
    this->relative_position_pa(global_coords, DC, lrel_pos);

    const box_list_type& blist = this->box_list(global_coords, DC);

    // Iterate over the bounding boxes.

    typename box_list_type::const_iterator iter;

    for(iter=blist.begin(); !xresult.is_valid() && (iter!=blist.end()); ++iter)
    {
      const d_bounding_box<DC, DB>* bbox = *iter;

      if(bbox->contains_point(lrel_pos))
      {
        // Found a cell with a bounding box that contains the value;
        // try inverting the value.

        section_evaluator* levaluator = bbox->evaluator();

        size_type dof_ct = bbox->dof_ct();
        sec_vd_dof_type* dofs = this->_gathered_dofs.base() + bbox->dofs_index();

        levaluator->coord_at_value(dofs,
                                   dof_ct,
                                   global_coords,
                                   DC,
                                   xresult.local_coords(),
                                   xresult.db());

        if(levaluator->in_standard_domain(xresult.local_coords(), xresult.db()))
        {
          // Inversion succeeded.
          // The coordinates are already stored in xresult_coords;
          // so just set the chart id.

          xresult.put_chart_id(bbox->member_id());
        }
        else
        {
          // Inversion failed.

          xresult.invalidate();
        }
      }
    }
  }
  else
  {
    // This point is ouside the domain of the search structure and hence
    // outside the range of the source coordinates.
    // We can't invert it; just leave the result invalid.
  }


  // Postconditions:

  ensure(unexecutable(xresult.is_valid() ?
                      xresult.chart() contains xvalue at xresult.local_coord() :
                      no chart contains xvalue));


  // Exit:

  return;
}

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
all_points_at_value(const sec_vd_value_type* xvalue,
                    size_type xvalue_ub,
                    block<chart_point_3d>& xresult)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering all_points_at_value");
#endif

  require(xvalue != 0);
  require(xvalue_ub >= this->dc());
  require(this->db() <= 3);

  // Body:

  /// @todo propagate constness everywhere.

  sec_vd_value_type* global_coords = const_cast<sec_vd_value_type*>(xvalue);

  define_old_variable(int old_xresult_ct = xresult.ct());

  chart_point_3d lchart_pt(invalid_pod_index(), 0.0, 0.0, 0.0);

  if(this->domain_contains(global_coords, DC))
  {
    // This point is within the domain.
    // Find the bounding boxes that may contain the value.

    d_bin_coordinates<DC, DB> lrel_pos;
    this->relative_position_pa(global_coords, DC, lrel_pos);

    const box_list_type& blist = this->box_list(global_coords, DC);

    // Iterate over the bounding boxes.

    typename box_list_type::const_iterator iter;

    for(iter = blist.begin(); iter != blist.end(); ++iter)
    {
      const d_bounding_box<DC, DB>* bbox = *iter;

      if(bbox->contains_point(lrel_pos))
      {
        // Found a cell with a bounding box that contains the value;
        // try inverting the value.

        section_evaluator* levaluator = bbox->evaluator();

        size_type dof_ct = bbox->dof_ct();
        sec_vd_dof_type* dofs = this->_gathered_dofs.base() + bbox->dofs_index();

        levaluator->coord_at_value(dofs,
                                   dof_ct,
                                   global_coords,
                                   DC,
                                   lchart_pt.local_coords(),
                                   lchart_pt.db());

        if(levaluator->in_standard_domain(lchart_pt.local_coords(), lchart_pt.db()))
        {
          // Inversion succeeded.
          // The coordinates are already stored in lchart_pt coords;
          // so just set the chart id.

          lchart_pt.put_chart_id(bbox->member_id());
          xresult.push_back(lchart_pt);
        }
        else
        {
          // Inversion failed; do nothing.
        }
      }
    }
  }
  else
  {
    // This point is ouside the domain of the search structure and hence
    // outside the range of the source coordinates.
    // We can't invert it; just leave the result empty.
  }


#ifdef DIAGNOSTIC_OUTPUT
  cout << "result: " << xresult << endl;
#endif

  // Postconditions:

  ensure_for_all(i, 0, xresult.ct(), xresult[i].is_valid());


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving all_points_at_value");
#endif

  return;
}

template <int DC, int DB>
void
d_bin_point_locator<DC, DB>::
branch_points_at_value(const sec_vd_value_type* xvalue,
                       size_type xvalue_ub,
                       block<branch_point_pair>& xresult)
{
#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering branch_points_at_value");
#endif

  require(xvalue != 0);
  require(xvalue_ub >= this->dc());
  require(this->dc() <= 3);

  // Body:

  define_old_variable(int old_xresult_ct = xresult.ct());

  /// @todo propagate constness everywhere.

  sec_vd_value_type* global_coords = const_cast<sec_vd_value_type*>(xvalue);

  branch_point_pair lbranch_pt;
  scoped_index& lbranch_id = lbranch_pt.first;
  chart_point_3d& lchart_pt = lbranch_pt.second;

  if(this->domain_contains(global_coords, DC))
  {
    // This point is within the domain.
    // Find the bounding boxes that may contain the value.

    d_bin_coordinates<DC, DB> lrel_pos;
    this->relative_position_pa(global_coords, DC, lrel_pos);

    const box_list_type& blist = this->box_list(global_coords, DC);

    // Iterate over the bounding boxes.

    typename box_list_type::const_iterator iter;

    for(iter = blist.begin(); iter != blist.end(); ++iter)
    {
      const d_bounding_box<DC, DB>* bbox = *iter;

#ifdef DIAGNOSTIC_OUTPUT

      cout << "considering " << *bbox << endl;
#endif

      lbranch_id = bbox->branch_id();

      if((_branches.find(lbranch_id) == _branches.end()) &&
          (bbox->contains_point(lrel_pos)))
      {

#ifdef DIAGNOSTIC_OUTPUT
        cout << "Inverting it ... ";
#endif
        // Haven't found a point for this branch yet and we've
        // found a cell with a bounding box that contains the value;
        // try inverting the value.

        section_evaluator* levaluator = bbox->evaluator();


        size_type dof_ct = bbox->dof_ct();
        sec_vd_dof_type* dofs = this->_gathered_dofs.base() + bbox->dofs_index();

        levaluator->coord_at_value(dofs,
                                   dof_ct,
                                   global_coords,
                                   DC,
                                   lchart_pt.local_coords(),
                                   lchart_pt.db());

        if(levaluator->in_standard_domain(lchart_pt.local_coords(), lchart_pt.db()))
        {
          // Inversion succeeded.
          // The coordinates are already stored in lchart_pt coords;
          // so just set the chart id.

#ifdef DIAGNOSTIC_OUTPUT
          cout << "valid" << endl;
#endif

          lchart_pt.put_chart_id(bbox->member_id());
          xresult.push_back(lbranch_pt);

          // We've found a point for this branch.

          _branches.insert(lbranch_id);
        }
        else
        {
          // Inversion failed; do nothing.

#ifdef DIAGNOSTIC_OUTPUT
          cout << "invalid" << endl;
#endif

        }
      }
      else
      {
#ifdef DIAGNOSTIC_OUTPUT
        cout << "Ignoring it" << endl;
#endif

      }

    }
  }
  else
  {
    // This point is ouside the domain of the search structure and hence
    // outside the range of the source coordinates.
    // We can't invert it; just leave the result empty.
  }

  // Clean up.

  _branches.clear();

#ifdef DIAGNOSTIC_OUTPUT

  cout << "result: " << xresult << endl;
#endif

  // Postconditions:

  ensure(xresult.ct() >= old_xresult_ct);
  ensure_for_all(i, old_xresult_ct, xresult.ct(),
                 coordinates().host()->contains_member(xresult[i].first, false));
  ensure_for_all(i, old_xresult_ct, xresult.ct(), xresult[i].second.is_valid());


  // Exit:

#ifdef DIAGNOSTIC_OUTPUT

  post_information_message("Leaving branch_points_at_value");
#endif

  return;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace geometry

#endif // D_BIN_POINT_LOCATOR_IMPL_H
