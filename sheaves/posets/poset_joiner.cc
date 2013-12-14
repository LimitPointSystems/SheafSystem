
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

 

// Implementation for class POSET_JOINER

#include "poset_joiner.h"
#include "assert_contract.h"

#include "abstract_poset_member.h"
#include "error_message.h"
#include "unordered_set_filter.h"
#include "total_poset_member.h"
#include "poset_state_handle.h"
#include "scoped_index.h"
#include "set_filter.h"
#include "std_algorithm.h"
#include "std_unordered_set.h"
#include "std_set.h"
#include "tern.h"
#include "triorder_itr.h"

using namespace sheaf;
using namespace std;

//#define DIAGNOSTIC_OUTPUT

/// @todo Review.  The is USE_IS_IMPLICIT code needed?  It is not used
/// in any branch and was the only reason that the cover set iterator
/// had to know if it was iterating over an implicit cover.  The
/// knowledge that the cover is implicit was lost by the cover_set_iterator
/// in this branch so defining USE_IS_IMPLICIT will case a compile error.
/// If the code is no longer needed it should be removed from this class.
/// Otherwise, the is implicit functionality of the cover set iterator
/// needs restored in some way.

#undef USE_IS_IMPLICIT

// ===========================================================
// UNNAMED NAMESPACE
// ===========================================================

namespace
{
///
/// The type of unordered sets.
///
typedef unordered_set<pod_index_type> uset_type;

///
/// The type of ordered sets.
///
typedef set<pod_index_type> oset_type;

///
/// The type of cover relation graph iterator.
///
typedef unordered_set_triorder_itr crg_itr_type;

///
/// True if and only if xset contains exactly one member.
///
bool is_singleton(const uset_type& xset)
{
  return (++xset.begin() == xset.end());
}

///
/// Compute the atoms in the downset of xindex.
///
void
compute_atoms(const scoped_index& xindex, 
	      uset_type& xgdown, 
	      uset_type& xatoms, 
	      crg_itr_type& xdown_itr)
{
  // Preconditions:

  require(xdown_itr.is_initialized());

  // Body:

  poset_state_handle* lhost = xdown_itr.anchor().host();
  
  xdown_itr.put_anchor(xindex);
  xdown_itr.reset(sheaf::NO_RESET);

  while(!xdown_itr.is_done())
  {     
    if(xdown_itr.action() == crg_itr_type::POSTVISIT_ACTION)
    {	
      xgdown.insert(xdown_itr.index().hub_pod());
      if(lhost->is_atom(xdown_itr.index()))
      {
	xatoms.insert(xdown_itr.index().hub_pod());
      }
    }
    
    xdown_itr.next();
  }  

  // Postconditions:

  // Exit:

  return;
}

///
/// Compute the atoms in the downset of xindex
/// and accumulate implicit status of links.
///
void
compute_atoms(const scoped_index& xindex, 
	      uset_type& xgdown, 
	      uset_type& xatoms, 
	      crg_itr_type& xdown_itr,
	      bool& xall_implicit)
{
  // Preconditions:

  require(xdown_itr.is_initialized());

  // Body:

#ifdef USE_IS_IMPLICIT

  poset_state_handle* lhost = xdown_itr.anchor().host();
  
  xdown_itr.put_anchor(xindex);
  xdown_itr.reset(sheaf::NO_RESET);

  while(!xdown_itr.is_done())
  {     
    switch(xdown_itr.action())
    {
      case crg_itr_type::LINK_ACTION:

	xall_implicit = xall_implicit && xdown_itr.link_is_implicit();	
	break;

      case crg_itr_type::POSTVISIT_ACTION:
	
	xgdown.insert(xdown_itr.index().hub_pod());
	if(lhost->is_atom(xdown_itr.index()))
	{
	    xatoms.insert(xdown_itr.index().hub_pod());
	}
	break;

      default:

	// Just to prevent complier warnings; do nothing.

	break;
    }
    
    xdown_itr.next();
  }  

#endif

  // Postconditions:

  // Exit:

  return;
}

///
/// Compute the down set xdown and the atoms xatoms 
/// of xexpansion using iterator xdown_itr.
///
void
compute_atoms(const scoped_index* xexpansion, 
	      int xexpansion_ct, 
	      uset_type& xgdown, 
	      uset_type& xatoms, 
	      crg_itr_type& xdown_itr)
{
  //  post_information_message("Entering compute_atoms");

  // Preconditions:

  require(xgdown.empty());
  require(xatoms.empty());
  require(xdown_itr.is_initialized());

  // Body:

  // Initialize the downset of g to the downset of xexpansion.  Compute
  // the atoms in the downset of g.

  // Make sure the has_visited markers are all cleared, since
  // we won't be resetting them during traversal. Can't use
  // reset() because it calls first(), which marks the first member.

  xdown_itr.clear_has_visited();

  for(int i = 0; i < xexpansion_ct; i++)
  {
    compute_atoms(xexpansion[i], xgdown, xatoms, xdown_itr);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "compute_atoms(): " << endl;
  cout << "joinands: ";
  
  for(int i = 0; i < xexpansion_ct; i++)
  {
    cout << xexpansion[i];
  }
  cout << endl;

  cout << "xgdown: ";
  for(uset_type::iterator i=xgdown.begin(); i!=xgdown.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
  
  cout << "xatoms: ";
  for(uset_type::iterator i=xatoms.begin(); i!=xatoms.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
#endif
  
  // Postconditions:

  ensure(unexecutable("xgdown contains the downset of xexpansion"));
  ensure(unexecutable("xatoms contains the atoms in the downset of xexpansion"));

  // Use of down itr in update_gdown(...) called from compute_mlb requires
  // down_itr has already visited the down set of the operands.

  require(unexecutable("for all m in down set of xexpansion: xdown_itr.has_visited(m)"));


  // Exit:

  //  post_information_message("Leaving compute_atoms");
  return;
}

///
/// Compute the down set xdown and the atoms xatoms 
/// of xexpansion using iterator xdown_itr and
/// accumulate the implict status of the links.
///
void
compute_atoms(const scoped_index* xexpansion, 
	      int xexpansion_ct, 
	      uset_type& xgdown, 
	      uset_type& xatoms, 
	      crg_itr_type& xdown_itr,
	      bool& xall_implicit)
{
  //  post_information_message("Entering compute_atoms");

  // Preconditions:

  require(xgdown.empty());
  require(xatoms.empty());
  require(xdown_itr.is_initialized());

  // Body:

  // Initialize the downset of g to the downset of xexpansion.  Compute
  // the atoms in the downset of g.

  // Make sure the has_visited markers are all cleared, since
  // we won't be resetting them during traversal. Can't use
  // reset() because it calls first(), which marks the first member.

  xdown_itr.clear_has_visited();

  for(int i = 0; i < xexpansion_ct; i++)
  {
    compute_atoms(xexpansion[i], xgdown, xatoms, xdown_itr, xall_implicit);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "compute_atoms(): " << endl;
  cout << "joinands: ";
  
  for(int i = 0; i < xexpansion_ct; i++)
  {
    cout << xexpansion[i];
  }
  cout << endl;

  cout << "xgdown: ";
  for(uset_type::iterator i=xgdown.begin(); i!=xgdown.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
  
  cout << "xatoms: ";
  for(uset_type::iterator i=xatoms.begin(); i!=xatoms.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
#endif
  
  // Postconditions:

  ensure(unexecutable("xgdown contains the downset of xexpansion"));
  ensure(unexecutable("xatoms contains the atoms in the downset of xexpansion"));

  // Use of down itr in update_gdown(...) called from compute_mlb requires
  // down_itr has already visited the down set of the operands.

  require(unexecutable("for all m in down set of xexpansion: xdown_itr.has_visited(m)"));


  // Exit:

  //  post_information_message("Leaving compute_atoms");
  return;
}

///
/// Compute the down set xdown and the atoms xatoms 
/// of xexpansion using iterator xdown_itr.
///
void
compute_atoms(subposet* xexpansion, 
	      uset_type& xgdown, 
	      uset_type& xatoms, 
	      crg_itr_type& xdown_itr)
{
  //  post_information_message("Entering compute_atoms");

  // Preconditions:

  require(xgdown.empty());
  require(xatoms.empty());
  require(xdown_itr.is_initialized());

  // Body:

  // Initialize the downset of g to the downset of xexpansion and
  // compute the atoms in the downset of g.

  // Make sure the has_visited markers are all cleared, since
  // we won't be resetting them during traversal. Can't use
  // reset() because it calls first(), which marks the first member.

  xdown_itr.clear_has_visited();

  index_iterator litr = xexpansion->indexed_member_iterator();
  while(!litr.is_done())
  {
    compute_atoms(litr.index(), xgdown, xatoms, xdown_itr);
    litr.next();
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "compute_atoms(): " << endl;
  cout << "joinands: ";
  
  litr.reset();
  while(!litr.is_done())
  {
    cout << litr.index();
    litr.next();
  }
  cout << endl;

  cout << "xgdown: ";
  for(uset_type::iterator i=xgdown.begin(); i!=xgdown.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
  
  cout << "xatoms: ";
  for(uset_type::iterator i=xatoms.begin(); i!=xatoms.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
#endif
  

  // Postconditions:

  ensure(unexecutable("gdown() contains the downset of xexpansion"));
  ensure(unexecutable("atoms() contains the atoms in the downset of xexpansion"));

  // Use of down itr in update_gdown(...) called from compute_mlb requires
  // down_itr has already visited the down set of the operands.

  require(unexecutable("for all m in down set of xexpansion: xdown_itr.has_visited(m)"));

  // Exit:

  //  post_information_message("Leaving compute_atoms");
  return;
}

///
/// Compute the down set xdown and the atoms xatoms 
/// of xexpansion using iterator xdown_itr and accumulate
/// implicit status of links.
///
void
compute_atoms(subposet* xexpansion, 
	      uset_type& xgdown, 
	      uset_type& xatoms, 
	      crg_itr_type& xdown_itr,
	      bool& xall_implicit)
{
  //  post_information_message("Entering compute_atoms");

  // Preconditions:

  require(xgdown.empty());
  require(xatoms.empty());
  require(xdown_itr.is_initialized());

  // Body:

  // Initialize the downset of g to the downset of xexpansion and
  // compute the atoms in the downset of g.

  // Make sure the has_visited markers are all cleared, since
  // we won't be resetting them during traversal. Can't use
  // reset() because it calls first(), which marks the first member.

  xdown_itr.clear_has_visited();

  index_iterator litr = xexpansion->indexed_member_iterator();
  while(!litr.is_done())
  {
    compute_atoms(litr.index(), xgdown, xatoms, xdown_itr, xall_implicit);
    litr.next();
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "compute_atoms(): " << endl;
  cout << "joinands: ";
  
  litr.reset();
  while(!litr.is_done())
  {
    cout << litr.index();
    litr.next();
  }
  cout << endl;

  cout << "xgdown: ";
  for(uset_type::iterator i=xgdown.begin(); i!=xgdown.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
  
  cout << "xatoms: ";
  for(uset_type::iterator i=xatoms.begin(); i!=xatoms.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
#endif
  

  // Postconditions:

  ensure(unexecutable("gdown() contains the downset of xexpansion"));
  ensure(unexecutable("atoms() contains the atoms in the downset of xexpansion"));

  // Use of down itr in update_gdown(...) called from compute_mlb requires
  // down_itr has already visited the down set of the operands.

  require(unexecutable("for all m in down set of xexpansion: xdown_itr.has_visited(m)"));

  // Exit:

  //  post_information_message("Leaving compute_atoms");
  return;
}

///
/// Adds the member with index xindex to gdown if
/// it belongs and is not all ready there.
/// A member belongs to gdown if it is a jrm and its
/// entire lower cover belongs to gdown.
/// Returns true if xindex was added, false otherwise.
///
bool
update_gdown(const scoped_index& xindex, uset_type& xgdown, crg_itr_type& xdown_itr)
{
  bool result;

  // Preconditions:

  // Body:

  poset_state_handle* lhost = xdown_itr.anchor().host();

  result = (xgdown.find(xindex.hub_pod()) != xgdown.end());

  if(!result && !lhost->is_jim(xindex) && !xdown_itr.has_visited(xindex))
  {
    // Xindex is not in gdown and is a jrm
    // and has not been evaluated;
    // determine if it should be in gdown.

    stack<bool> ladd_to_gdown;

    xdown_itr.put_anchor(xindex);
    xdown_itr.reset(sheaf::NO_RESET);

    while(!xdown_itr.is_done())
    {
      bool lforce_is_done = false;
      bool ltruncate = false;

      switch(xdown_itr.action())
      {
	case crg_itr_type::PREVISIT_ACTION:

	  { // just to silence compiler warnings

	    // The down set iterator has reached a member that has
	    // not been evaluated.  If the member is a jrm, we
	    // assume that the member will be added to gdown;
	    // the link action will determine if the jrm should not
	    // be added.  Only jims that are in the down set
	    // of the joinands belong in gdown, so if the member
	    // is a jim its either already there or doesn't
	    // belong. Either way, the down iteration should be truncated.

	    bool lis_jim = lhost->is_jim(xdown_itr.index());

	    ladd_to_gdown.push(!lis_jim);
	    ltruncate = lis_jim;
	  }	  
	  break;

	case crg_itr_type::LINK_ACTION:

	  // Only add to gdown if the lower cover of the member is in gdown.

	  ladd_to_gdown.top() = 
	    ladd_to_gdown.top() && 
	    (xgdown.find(xdown_itr.lesser_index().hub_pod()) != xgdown.end());
	      
	  break;

	case crg_itr_type::POSTVISIT_ACTION:
		  
	  if(ladd_to_gdown.top())
	  {
	    // Add the member to gdown.

	    xgdown.insert(xdown_itr.index().hub_pod());
	    result = true;
	  }
	  else
	  {
	    // The member is not in gdown, so no 
	    // member in its upset is in gdown.

	    result = false;
	    lforce_is_done = true;
	  }
		  
	  ladd_to_gdown.pop();
	  break;
		  
	default:
	  break;
      }

      if(lforce_is_done)
      {
	xdown_itr.force_is_done();
      }
      else
      {
	xdown_itr.next(ltruncate);
      }
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

///
/// Compute the maximum lower bound of the join.
///
void
compute_mlb(uset_type& xgdown, 
	    uset_type& xatoms, 
	    crg_itr_type& xdown_itr,
	    crg_itr_type& xup_itr,
	    uset_type& xmlb)
{
  //  post_information_message("Entering compute_mlb");

  // Preconditions:

  require(xdown_itr.is_initialized());

  // Use of down itr in update_gdown(...) requires down_itr has
  // already visited the down set of the operands.

  require(unexecutable("for all m in down set of joinands: xdown_itr.has_visited(m)"));

  require(xup_itr.is_initialized());
  require(xmlb.empty());

  // Body:

  stack<bool> lis_maximal;
  scoped_index litem(xdown_itr.anchor().hub_id());

  // Iterate over the upset of the atoms computing the maximal lower bound.
  // Clear up_itr has visited, but not down itr has visited (see precondition).

  xup_itr.clear_has_visited();

  for(uset_type::iterator itr = xatoms.begin(); itr != xatoms.end(); itr++)
  {
    litem = *itr;
    xup_itr.put_anchor(litem);
    xup_itr.reset(sheaf::NO_RESET);

    while(!xup_itr.is_done())
    {
      bool ltruncate = false;

      switch(xup_itr.action())
      {
	case crg_itr_type::PREVISIT_ACTION:

	  { // just to silence compiler warning

	    // Add the member to gdown if it should be there.
	  
	    bool lis_in_gdown = update_gdown(xup_itr.index(), xgdown, xdown_itr);

	    // Member is only maximal if it is in gdown
	    // and none of the members above it are in gdown.
	    // Initialize top of is_maximal stack to is_in_gdown,
	    // the link action will test members above.

	    lis_maximal.push(lis_in_gdown);

	    // If the member is not in gdown, no members of 
	    // its upset will be in gdown; truncate.

	    ltruncate = !lis_in_gdown;
	  }

	  break;

	case crg_itr_type::LINK_ACTION:

	  // Memebr is only maximal if it is in gdown
	  // and none of the members above it are in gdown.
	  // Test and accumulate gdown status of members above.

	  lis_maximal.top() = 
	    lis_maximal.top() &&
	    (xgdown.find(xup_itr.lesser_index().hub_pod()) == xgdown.end());

	  break;

	case crg_itr_type::POSTVISIT_ACTION:

	  if(lis_maximal.top())
	  {
	    // Member is a maximal, add to maximal lower bound.

	    xmlb.insert(xup_itr.index().hub_pod());
	  }

	  lis_maximal.pop();
	  
	  break;

	default:
	  break;
      }

      xup_itr.next(ltruncate);
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "compute_mlb:" << endl;
  cout << "xgdown: ";
  for(uset_type::iterator i=xgdown.begin(); i!=xgdown.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
  
  cout << "xmlb: ";
  for(uset_type::iterator i=xmlb.begin(); i!=xmlb.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result contains mlb(g) in internal scope"));

  // Exit

  //  post_information_message("Leaving compute_mlb");
  return;
}

///
/// Compute the minimal members of xsrc.
///
void
compute_minimals(crg_itr_type& xup_itr, oset_type& xmub)
{
  // Preconditions:

  require(unexecutable("xmub is in internal scope"));

  // Body:

  // Reset the upset iterator.

  xup_itr.put_visit_once(true);
  xup_itr.put_strict(true);
  xup_itr.clear_has_visited();

  scoped_index litem(xup_itr.anchor().hub_id());

  for(oset_type::iterator litr = xmub.begin(); litr != xmub.end(); litr++)
  {
    litem = *litr;

    // Anchor the up itr at the current litr item.

    xup_itr.put_anchor(litem);
    xup_itr.reset(sheaf::NO_RESET);

    // Remove the upset of the anchor from xmub.

    while(!xup_itr.is_done())
    {
      if(xup_itr.action() == crg_itr_type::POSTVISIT_ACTION)
      {
	// Since up itr is strict, current member can not be litr current item
	// and hence we can erase current member without affecting litr.

	assertion(xup_itr.index().hub_pod() != *litr);

	xmub.erase(xup_itr.index().hub_pod()); // Internal scope.
      }
      xup_itr.next();
    }

    // Mark the current anchor as not been visited.  This allows an upset
    // traversal for a member with the anchor in its upset to visit and
    // remove the anchor.

    xup_itr.put_has_visited(litem, false);
  }

  // Postconditions:

  // Exit

  return;
}

///
/// Compute the intersection of xset and xresult
/// and return the result in xresult.
///
void
intersect(const oset_type& xset, oset_type& xresult)
{

  // Preconditions:


  // Body:

  oset_type::iterator ritr = xresult.begin();
  oset_type::const_iterator sitr = xset.begin();
  oset_type::iterator tmp;


  oset_type::value_type rmbr, smbr;

  while(ritr != xresult.end() && sitr != xset.end())
  {
    rmbr = *ritr;
    smbr = *sitr;

    if( rmbr < smbr )
    {
      // Current result member isn't in xset, 
      // erase it from result.

      // Erasing member that iterator points to
      // invalidates iterator; increment past it first.

      tmp = ritr;
      ritr++;
      xresult.erase(tmp);
    }
    else if( rmbr == smbr )
    {
      // Current result member is in xset;
      // leave it there and move on.

      ritr++;
      sitr++;
    }
    else
    {
      // Current xset member isn't in result;
      // just move on.

      sitr++;
    }

  }

  // None of the remaining members (if any) in result
  // were in xset, remove them from result.

  if(ritr != xresult.end())
  {
    xresult.erase(ritr, xresult.end());
  }
  

  // Postconditions:

  // Exit

  return;
}

///
/// Compute the minimal upper bound of the join.
///
void
compute_mub(uset_type& xmlb, crg_itr_type& xup_itr, oset_type& xmub)
{
  //  post_information_message("Entering compute_mub");

  // Preconditions:

  require(xup_itr.is_initialized());
  require(xmub.empty());

  // Body:

  // Compute the common upper bound; the intersection of all
  // the members of the strict upset of xmlb.

  xup_itr.put_strict(true);
  xup_itr.put_visit_once(false);
  xup_itr.clear_has_visited();

  scoped_index litem(xup_itr.anchor().hub_id());
  for(uset_type::iterator itr = xmlb.begin(); itr != xmlb.end(); ++itr)
  {
    litem = *itr;

    xup_itr.put_anchor(litem);
    xup_itr.reset(sheaf::NO_RESET);

    if(xmub.empty())
    {
      // First upset found, initialize xmub.

      while(!xup_itr.is_done())
      {
	if(xup_itr.action() == crg_itr_type::POSTVISIT_ACTION)
	{
	  xmub.insert(xup_itr.index().hub_pod());
	}

	xup_itr.next();
      }
    }
    else
    {
      // Compute the intersection of the upper cover of the
      // current member of xmlb with the common upper bound.

      oset_type ltmp_set;
      while(!xup_itr.is_done())
      {
	if(xup_itr.action() == crg_itr_type::POSTVISIT_ACTION)
	{
	  ltmp_set.insert(xup_itr.index().hub_pod());
	}
	xup_itr.next();
      }

      intersect(ltmp_set, xmub);
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "compute_mub:" << endl;
  cout << "xmub: ";
  for(oset_type::iterator i=xmub.begin(); i!=xmub.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
#endif

  // Compute the minimals of common upper bound.

  compute_minimals(xup_itr, xmub);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "xmub after compute_minimals: ";
  for(oset_type::iterator i=xmub.begin(); i!=xmub.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result contains mub(g) in internal scope"));

  // Exit

  //  post_information_message("Leaving compute_mub");
  return;
}


///
/// Make xresult_lc and xresult_uc the lower
/// and upper covers, respecively, of xreult.
///
void
link_result(const uset_type& xresult_lc, const oset_type& xresult_uc, abstract_poset_member& xresult)
{
  // Preconditions:

  require(xresult.state_is_read_write_accessible());
  
  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "link_result:" << endl;
  cout << "xresult_lc: ";
  for(uset_type::iterator i=xresult_lc.begin(); i!=xresult_lc.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;

  cout << "xresult_uc: ";
  for(oset_type::iterator i=xresult_uc.begin(); i!=xresult_uc.end(); ++i)
  {
    cout << setw(6) << *i;
  }
  cout << endl;
#endif

  poset_state_handle* lhost = xresult.host();

  // Get an index in internal scope.

  scoped_index litem(lhost->member_id(false));

  // Link the upper cover.

  for(oset_type::const_iterator litr = xresult_uc.begin(); litr != xresult_uc.end(); ++litr)
  {
    litem = *litr;

    // Remove all members of result_lc from 
    // the lower cover of the current upper cover member

    lhost->remove_cover_members(unordered_set_filter(xresult_lc), LOWER, litem);

    // Insert result in the lower cover
    // of the current upper cover member.

    lhost->insert_cover_member(xresult.index(), LOWER, litem);
    
    // Insert the current member of the upper cover
    // in the upper cover of result.

    xresult.insert_cover_member(litem, UPPER);
  }
  
  // Link the lower cover.

  for(uset_type::const_iterator litr = xresult_lc.begin(); litr != xresult_lc.end(); ++litr)
  {
    litem = *litr;

    // Remove all members of result_uc from 
    // the upper cover of the current lower cover member

    lhost->remove_cover_members(set_filter(xresult_uc), UPPER, litem);

    // Insert result in the upper cover
    // of the current lower cover member.

    lhost->insert_cover_member(xresult.index(), UPPER, litem);
    
    // Insert the current member of the lower cover
    // in the lower cover of result.

    xresult.insert_cover_member(litem, LOWER);
  }  

  // Postconditions:


  // Exit:

  return;
}

///
/// If xgreatest true, attaches result to bottom,
/// otherwise attaches result to a new gem of bottom.
///
void
attach_result(poset_state_handle* xhost, const tern& xgreatest, abstract_poset_member& xresult)
{
  //  post_information_message("Entering attach_result");

  // Preconditions:

  require(xhost->state_is_read_write_accessible());  
  
  // Body:

  // Lower cover is empty; join is bottom.

  scoped_index lindex = xhost->bottom().index();

  if(xgreatest.is_true())
  {
    // New greatest join equivalent member requested, make it.

    xresult.new_jem_state(xhost, lindex, true, false);
  }
  else
  {
    // Attach result to bottom.

    xresult.attach_to_state(xhost, lindex);
  }

  // Postconditions:

  ensure(xresult.is_attached());
  
  // Exit:

  //  post_information_message("Leaving attach_result");
  return;
}

///
/// Creates the join member state, if necessary, links its lower and upper covers
/// using xmlb, and xmub, respectively, and attaches xresult to the state.
///
void
attach_result(poset_state_handle* xhost, 
	      const uset_type& xmlb, 
	      const tern& xgreatest, 
	      abstract_poset_member& xresult)
{
  //  post_information_message("Entering attach_result");

  // Preconditions:

  require(xhost->state_is_read_write_accessible());
  require(is_singleton(xmlb));
  
  // Body:

  // Mlb contains a single member, it must be the join.

  scoped_index lindex = xhost->member_id(*(xmlb.begin()), false);

  if(xgreatest.is_true())
  {
    // New greatest join equivalent member requested, make it.

    xresult.new_jem_state(xhost, lindex, true, false);
  }
  else if(xgreatest.is_false())
  {
    // New least join equivalent member requested, make it.

    xresult.new_jem_state(xhost, lindex, false, false);
  }
  else
  {
    // New jem not requested,
    // attach result to existing member.

    xresult.attach_to_state(xhost, lindex);
  }

  // Postconditions:

  ensure(xresult.is_attached());
  
  // Exit:

  //  post_information_message("Leaving attach_result");
  return;
}

///
/// Creates the join member state, links its lower and upper covers
/// using xmlb, and xmub, respectively, and attaches xresult to the state.
///
void
attach_result(poset_state_handle* xhost, 
	      const uset_type& xmlb, 
	      const oset_type& xmub,
	      const tern& xgreatest, 
	      abstract_poset_member& xresult)
{
  //  post_information_message("Entering attach_result");

  // Preconditions:

  require(xhost->state_is_read_write_accessible());
  require(!xmlb.empty());
  require(!is_singleton(xmlb));
  require(!xmub.empty());
  
  // Body:

  // Join has not been instantiated;
  // upper and lower cover are strict bounds.

  // Make a new member state and attach result to it

  pod_index_type lindex = xhost->new_member(false);

  xresult.attach_to_state(xhost, lindex);

  link_result(xmlb, xmub, xresult);

  // Postconditions:

  ensure(xresult.is_attached());
  
  // Exit:

  //  post_information_message("Leaving attach_result");
  return;
}

} // End unnamed namespace.


// ===========================================================
// PUBLIC MEMBER FUNCTIONS
// ===========================================================
 
sheaf::poset_joiner::
poset_joiner(const poset_state_handle* xhost)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());

  // Body:

  _host = const_cast<poset_state_handle*>(xhost);

  // Postconditions:

  ensure(host() == xhost);
}

sheaf::poset_joiner::
~poset_joiner()
{
  // Preconditions:

  // Body:

  // Postconditions:
}

void
sheaf::poset_joiner::
join(const scoped_index* xexpansion,
     int xexpansion_ct,
     const tern& xgreatest,
     abstract_poset_member& xresult)
{

  // Preconditions:

  // Body:

  // Computing the join g of a set S of members of a lattice L
  // requires placing g in the order relation, that is, finding
  // the upper and lower cover for g. To do this, we compute two
  // sets, the maximal lower bound of g, mlb(g), and the 
  // minimal upper bound of g, mub(g). 
  //
  // Mlb(g) contains the largest (maximal) members that are 
  // less than or equal to g. A member m is less than or equal
  // to g if J(m) is included in J(g). We can discover all such 
  // members by searching the CRG upward from the bottom,
  // see compute_mlb. If the join g already exists,
  // the mlb will contain a single member, g. Conversely,
  // if the mlb contains a single member then it must be g.
  // Otherwise, the mlb is the lower cover of g.
  //
  // Mub(g) contains the smallest (minimal) members of L which
  // are strictly greater than every member of mlb(g). We can
  // discover such members by searching the CRG upwards from mlb(g),
  // see compute_mub. The strictly greater conditions implies
  // mlb(g) and mub(g) are disjoint. Since every  member m of mub 
  // is greater than every member m' of mlb, J(m) contains every 
  // member of J(g) and furthermore, since it is strictly greater 
  // than every m', J(m) must contain at least one jim j that is not 
  // contained in J(g). Hence J(m) includes J(g) as a strict subset, 
  // which means g is strictly less than m.
  // Since mub(g) are the minimal members that satisfy this condition,
  // mub(g) is the upper cover of g.
  //
  // Note that if g is the top, then mlb(g) == {g} and mub(g) == {}.

  // The is_implicit option attempts to optimize computation of
  // the maximal lower bound using the fact that if the entire
  // down set of the expansion is implicit, then the expansion
  // must be its own maximal lower bound. Experiment shows this
  // option works just fine, but further study is required to
  // determine whether it actually improves performance much.

  uset_type latoms;
  uset_type lgdown;
  uset_type lmax_gdown;
  
  crg_itr_type ldown_itr(host()->top(), DOWN, NOT_STRICT);
  crg_itr_type lup_itr(host()->top(), UP, NOT_STRICT);

  uset_type lmlb;
  oset_type lmub;

#ifdef USE_IS_IMPLICIT

  bool lall_implicit = true;

  // Gather the down set of g and the atoms in it.

  compute_atoms(xexpansion, xexpansion_ct, lgdown, latoms, ldown_itr, lall_implicit);

  // cout << "all implicit: " << boolalpha << lall_implicit << noboolalpha << endl;

  // Get the maximal lower bound.

  if(lall_implicit)
  {
    // Downset of expansion was all implicit,
    // expansion is its own maximal lower bound.

    for(int i=0; i<xexpansion_ct; ++i)
    {
      lmlb.insert(xexpansion[i].hub_pod());
    }
  }
  else
  {
    // Have to compute maximal lower bound.

    compute_mlb(lgdown, latoms, ldown_itr, lup_itr, lmlb); 
  } 

#else

  // Gather the down set of g and the atoms in it.

  compute_atoms(xexpansion, xexpansion_ct, lgdown, latoms, ldown_itr);

  // Have to compute maximal lower bound.

  compute_mlb(lgdown, latoms, ldown_itr, lup_itr, lmlb); 

#endif

  if(lmlb.empty())
  {
    // Lower cover is empty; 
    // result is bottom or equivalent.

    attach_result(host(), xgreatest, xresult);
  }
  else if(is_singleton(lmlb))
  {
    // Join is already instantiated,
    // don't need to compute mub,
    // just attach result.

    attach_result(host(), lmlb, xgreatest, xresult);
  }
  else
  {    
    // Join is not already instantiated,
    // compute the minimal upper bound.

    compute_mub(lmlb, lup_itr, lmub);

    // Create the join member and attach result.

    attach_result(host(), lmlb, lmub, xgreatest, xresult);
  }
  

  // Postconditions:

  ensure(unexecutable("result is join of xexpansion"));

  // Exit

  return;
}

void
sheaf::poset_joiner::
join(subposet* xexpansion, const tern& xgreatest, abstract_poset_member& xresult)
{

  // Preconditions:

  // Body:

  // See comments in the other join signature.

  uset_type latoms;
  uset_type lgdown;
  uset_type lmax_gdown;
  
  crg_itr_type ldown_itr(host()->top(), DOWN, NOT_STRICT);
  crg_itr_type lup_itr(host()->top(), UP, NOT_STRICT);

  uset_type lmlb;
  oset_type lmub;

#ifdef USE_IS_IMPLICIT

  bool lall_implicit = true;

  // Gather the down set of xexpansion and the atoms in it.

  compute_atoms(xexpansion, lgdown, latoms, ldown_itr, lall_implicit);

  // cout << "all implicit: " << boolalpha << lall_implicit << noboolalpha << endl;

  // Get the maximal lower bound.

  if(lall_implicit)
  {
    // Downset of expansion was all implicit,
    // expansion is its own maximal lower bound.

    index_iterator litr = xexpansion->indexed_member_iterator();
    while(!litr.is_done())
    {
      lmlb.insert(litr.index());
      litr.next();
    }
  }
  else
  {
    // Have to compute maximal lower bound.

    compute_mlb(lgdown, latoms, ldown_itr, lup_itr, lmlb); 
  } 

#else

  // Gather the down set of xexpansion and the atoms in it.

  compute_atoms(xexpansion, lgdown, latoms, ldown_itr);

  // Compute maximal lower bound.

  compute_mlb(lgdown, latoms, ldown_itr, lup_itr, lmlb); 

#endif

  if(lmlb.empty())
  {
    // Lower cover is empty; 
    // result is bottom or equivalent.

    attach_result(host(), xgreatest, xresult);
  }
  else if(is_singleton(lmlb))
  {
    // Join is already instantiated,
    // don't need to compute mub,
    // just attach result.

    attach_result(host(), lmlb, xgreatest, xresult);
  }
  else
  {    
    // Join is not already instantiated,
    // compute the minimal upper bound.

    compute_mub(lmlb, lup_itr, lmub);

    // Create the join member and attach result.

    attach_result(host(), lmlb, lmub, xgreatest, xresult);
  }

  // Postconditions:

  ensure(unexecutable("result is join of xexpansion"));

  // Exit

  return;
}

 

sheaf::poset_state_handle*
sheaf::poset_joiner::
host() const
{
  return _host;
}
