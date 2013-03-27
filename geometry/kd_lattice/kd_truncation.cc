// $RCSfile: kd_truncation.cc,v $ $Revision: 1.7 $ $Date: 2013/03/13 00:59:00 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_truncation

#include "kd_truncation.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "index_space_iterator.h"
#include "kd_lattice.h"
#include "kd_segment.h"
#include "d_cells_cohort.h"

using namespace geometry; // Workaround for MS C++ bug.

// ===========================================================
// KD_TRUNCATION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_truncation::
kd_truncation()
{
  
  // Preconditions:

    
  // Body:
  
  
  // Postconditions:

  ensure(unexecutable("not initialized"));
  
  // Exit:

  return; 
}

geometry::kd_truncation::
kd_truncation(const kd_lattice& xhost, const scoped_index& xid)
{
  
  // Preconditions:

    
  // Body: 

  clear();

  scoped_index ltmp_id;
  
  index_space_iterator& litr = xhost.base_space().get_cover_id_space_iterator(UPPER, xid);
  while(!litr.is_done())
  {    
    if(xhost.segments().contains(litr.hub_pod()))
    {
      kd_segment::surface(xhost, xhost.base_space().member_id(litr.hub_pod(), false), ltmp_id);
      if(surface_ct == 0)
      {
        surface_ids[0] = ltmp_id;
        segment_cts[0] = 1;
        ++surface_ct;
      }
      else if(ltmp_id == surface_ids[0])
      {
        ++segment_cts[0];
      }
      else if(surface_ct == 1)
      {
        surface_ids[1] = ltmp_id;
        segment_cts[1] = 1;
        ++surface_ct;
      }
      else if(ltmp_id == surface_ids[1])
      {
        ++segment_cts[1];
      }
      else
      {
        ++surface_ct;
      }
    }
    litr.next();
  }
  xhost.base_space().release_cover_id_space_iterator(litr);

  // Make sure surface 0 is always the truncated surface.

  if(surface_ct > 1)
  {
    if(segment_cts[0] > segment_cts[1])
    {
      // Swap surfaces.

      ltmp_id = surface_ids[0];
      surface_ids[0] = surface_ids[1];
      surface_ids[1] = ltmp_id;
      
      size_type ltmp_ct = segment_cts[0];
      segment_cts[0] = segment_cts[1];
      segment_cts[1] = ltmp_ct;
    }
  }
  
  // Postconditions:

  // Exit:

  return; 
}

geometry::kd_truncation::
~kd_truncation()
{  
  // Preconditions:

    
  // Body:
  

  // Postconditions:

  // Exit:

  return; 
}

size_type
geometry::kd_truncation::
segment_ct() const
{
  // cout << endl << "Entering kd_truncation::segment_ct." << endl;

  // Preconditions:


  // Body:

  size_type result = segment_cts[0] + segment_cts[1];

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation::segment_ct." << endl;
  return result;
}

bool
geometry::kd_truncation::
is_self_truncation() const
{
  // cout << endl << "Entering kd_truncation::is_self_truncation." << endl;

  // Preconditions:


  // Body:

  bool result = (surface_ct == 1);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation::is_self_truncation." << endl;
  return result;
}

bool
geometry::kd_truncation::
is_binary_truncation() const
{
  // cout << endl << "Entering kd_truncation::is_binary_truncation." << endl;

  // Preconditions:


  // Body:

  bool result = (surface_ct == 2);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation::is_binary_truncation." << endl;
  return result;
}

bool
geometry::kd_truncation::
is_higher_order_truncation() const
{
  // cout << endl << "Entering kd_truncation::is_higher_order_truncation." << endl;

  // Preconditions:


  // Body:

  bool result = (surface_ct > 2);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation::is_higher_order_truncation." << endl;
  return result;
}

geometry::kd_truncation::trunc_type
geometry::kd_truncation::
type(int xi)
{
  // cout << endl << "Entering kd_truncation::type." << endl;

  // Preconditions:

  // Body:

  static const trunc_type ltype[NOT_A_TRUNCATION+1] =
    {
      NOT_A_TRUNCATION,    // lseg_ct = 0
      NOT_A_TRUNCATION,    // 1
      MUTUALLY_TRUNCATED,  // 2
      NORMAL_TRUNCATION,   // 3
      MUTUALLY_TRUNCATING, // 4
      NOT_A_TRUNCATION     // 5
    };
  

  trunc_type result = ((2 <= xi) && (xi <= 4)) ? ltype[xi] : NOT_A_TRUNCATION;
    
  // Postconditions:

  // Exit:

  // cout << "Leaving kd_truncation::type." << endl;
  return result;
}

geometry::kd_truncation::trunc_type
geometry::kd_truncation::
type() const
{
  // cout << endl << "Entering kd_truncation::type." << endl;

  // Preconditions:

  // Body:

  /// @error type(segment_ct()) will return the wrong type if
  /// the point is not a truncation point at all.

  // $$SCRIBBLE: is it correct that type depends only on segment ct and not on surface_ct?
  // A point is mutually truncating even if surface_ct == 1?

  trunc_type result = type(segment_ct());
    
  // Postconditions:

  // Exit:

  // cout << "Leaving kd_truncation::type." << endl;
  return result;
}

const sheaf::scoped_index&
geometry::kd_truncation::
truncated() const
{
  // cout << endl << "Entering kd_truncation::truncated." << endl;

  // Preconditions:

  require((type() == NORMAL_TRUNCATION) || is_self_truncation());
  
  // Body:

  // Surface 0 is always the truncated surface by convention.
  // if self truncating or mutually truncated or mutually truncating,
  // then so is surface 1.

  const scoped_index& result = surface_ids[0];
    
  // Postconditions:

  ensure(result.is_valid() || surface_ct == 0);

  // Exit:

  // cout << "Leaving kd_truncation::truncated." << endl;
  return result;
}

const sheaf::scoped_index&
geometry::kd_truncation::
truncating() const
{
  // cout << endl << "Entering kd_truncation::truncated." << endl;

  // Preconditions:

  require((type() == NORMAL_TRUNCATION) || is_self_truncation());

  // Body:

  // Surface 1 is always the truncating surface by convention, unless
  // there is only one surface.

  const scoped_index& result = surface_ct == 1 ? surface_ids[0] : surface_ids[1];
    
  // Postconditions:

  ensure(result.is_valid() || surface_ct == 0);

  // Exit:

  // cout << "Leaving kd_truncation::truncated." << endl;
  return result;
}

bool
geometry::kd_truncation::
is_truncated(const scoped_index& xid) const
{
  // cout << endl << "Entering kd_truncation::is_truncated." << endl;

  // Preconditions:

  require(!is_higher_order_truncation());
  
  // Body:

  bool result = false;

  if(surface_ct == 0)
  {
    result = false;
  }
  else if(surface_ct == 1)
  {
    result = (xid == surface_ids[0]);
  }
  else
  {
    assertion(surface_ct == 2);
    
    if(segment_ct() == 3)
    {
      // Normal truncation.

      result = (xid == surface_ids[0]);
    }
    else
    {
      // Mutually truncated, or mutually truncating.

      assertion((segment_ct() == 2) || (segment_ct() == 4));
      
      result = (xid == surface_ids[0]) || (xid == surface_ids[1]);
    }
    
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation::is_truncated." << endl;
  return result;
}

bool
geometry::kd_truncation::
is_truncating(const scoped_index& xid) const
{
  // cout << endl << "Entering kd_truncation::is_truncating." << endl;

  // Preconditions:

  require(!is_higher_order_truncation());
  
  // Body:

  bool result = false;

  if(surface_ct == 0)
  {
    result = false;
  }
  else if(surface_ct == 1)
  {
    result = (xid == surface_ids[0]);
  }
  else
  {
    assertion(surface_ct == 2);
    
    if(segment_ct() == 3)
    {
      // Normal truncation.

      result = (xid == surface_ids[1]);
    }
    else
    {
      // Mutually truncated, or mutually truncating.

      assertion((segment_ct() == 2) || (segment_ct() == 4));
      
      result = (xid == surface_ids[0]) || (xid == surface_ids[1]);
    }
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation::is_truncating." << endl;
  return result;
}


void
geometry::kd_truncation::
clear()
{
  // cout << endl << "Entering kd_truncation::clear." << endl;

  // Preconditions:


  // Body:

  surface_ct = 0;
  for(int i=0; i<SURFACE_UB; ++i)
  {
    segment_cts[i] = 0;
    surface_ids[i].invalidate();
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation::clear." << endl;
  return;
}


bool
geometry::kd_truncation::
is_reverse(const kd_truncation& xother) const
{
  // cout << endl << "Entering kd_truncation::is_reverse." << endl;

  // Preconditions:

  require(!is_higher_order_truncation());
  
  // Body:

  // Only normal truncations can be reversal pairs.
  // In particular, a truncation pair with one end
  // mutually truncating is not a reversal pair, 
  // even though the mutually truncating end is a 
  // reversal point, since the truncation relationship
  // does not change along the path defined by the pair
  // and it does not require finding the complemntary
  // reversal pair. 
  // (See also kd_line_fragment.cc:create_truncation_fragments.)

  bool result = 
    (segment_ct() == 3) && 
    (xother.segment_ct() == 3) &&
    (surface_ids[0] == xother.surface_ids[1]) &&
    (surface_ids[1] == xother.surface_ids[0]);
  
  // cout << "segment_ct(): " << segment_ct() << endl;
  // cout << "this: " << *this << endl;
  // cout << "xother.segment_ct(): " << xother.segment_ct() << endl;
  // cout << "xother: " << xother << endl;
  // cout << "result: " << boolalpha << result << noboolalpha << endl;
  
  // Postconditions:

  ensure(result ? type() == NORMAL_TRUNCATION : true);
  ensure(result ? xother.type() == NORMAL_TRUNCATION : true);
  
  // Exit:

  // cout << "Leaving kd_truncation::is_reverse." << endl;
  return result;
}

bool
geometry::kd_truncation::
has_same_surfaces(const kd_truncation& xother) const
{
  // cout << endl << "Entering kd_truncation::is_reverse." << endl;

  // Preconditions:

  require(!is_higher_order_truncation());

  // Body:

  bool result = false;

  if(surface_ct == xother.surface_ct)
  {  
    if(surface_ct == 1)
    {
      result = (surface_ids[0] == xother.surface_ids[0]);
    }
    else if(surface_ct == 2)
    {
      result = 
        ((surface_ids[0] == xother.surface_ids[0]) && (surface_ids[1] == xother.surface_ids[1])) ||
        ((surface_ids[0] == xother.surface_ids[1]) && (surface_ids[1] == xother.surface_ids[0]));
    }
  }
  
  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation::is_reverse." << endl;
  return result;
}


bool
geometry::kd_truncation::
operator==(const kd_truncation& xother) const
{
  // cout << endl << "Entering kd_truncation::operator==." << endl;

  // Preconditions:


  // Body:

  bool result =
    (surface_ct == xother.surface_ct) &&
    (surface_ids[0] == xother.surface_ids[0]) &&
    (surface_ids[1] == xother.surface_ids[1]) &&
    (segment_cts[0] == xother.segment_cts[0]) &&
    (segment_cts[1] == xother.segment_cts[1]);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation::operator==." << endl;
  return result;
}

// kd_truncation
// geometry::kd_truncation::
// transpose() const
// {
//   // cout << endl << "Entering kd_truncation::transpose." << endl;

//   // Preconditions:


//   // Body:

//   kd_truncation result;

//   if(surface_ct == 1)
//   {
//     result = *this;
//   }
//   else
//   {
//     result.surface_ct     = surface_ct;
//     result.surface_ids[0] = surface_ids[1];
//     result.surface_ids[1] = surface_ids[0];
//     result.segment_cts[0] = segment_cts[1];
//     result.segment_cts[1] = segment_cts[0];
//   }

//   // Postconditions:


//   // Exit:

//   // cout << "Leaving kd_truncation::transpose." << endl;
//   return result;
// }

// PROTECTED MEMBER FUNCTIONS


// PRIVATE MEMBER FUNCTIONS




// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================


ostream& 
geometry::
operator << (ostream& xos, const kd_truncation::trunc_type& xn)
{
  switch(xn)
  {
    case kd_truncation::NORMAL_TRUNCATION:
      xos << "NORMAL_TRUNCATION";
      break;
    case kd_truncation::MUTUALLY_TRUNCATED:
      xos << "MUTUALLY_TRUNCATED";
      break;
    case kd_truncation::MUTUALLY_TRUNCATING:
      xos << "MUTUALLY_TRUNCATING";
      break;
    case kd_truncation::NOT_A_TRUNCATION:
      xos << "NOT_A_TRUNCATION";
      break;
  }

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const kd_truncation& xn)
{
  // Preconditions:

  // Body:

  xos << "surface_ct: " << xn.surface_ct;
  xos << "  surfaces: ";
  for(int i=0; i<xn.surface_ct; ++i)
  {
    xos << "  " << xn.surface_ids[i];
  }
  xos << "  segment_cts: ";
  for(int i=0; i<xn.surface_ct; ++i)
  {
    xos << "  " << xn.segment_cts[i];
  }
  
  // Postconditions:

  // Exit:

  return xos;
}
