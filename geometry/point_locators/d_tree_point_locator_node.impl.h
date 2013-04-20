
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class d_tree_point_locator_node

#ifndef D_TREE_POINT_LOCATOR_NODE_IMPL_H
#define D_TREE_POINT_LOCATOR_NODE_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef D_TREE_POINT_LOCATOR_H
#include "d_tree_point_locator.h"
#endif

#ifndef D_TREE_POINT_LOCATOR_PATH_H
#include "d_tree_point_locator_path.h"
#endif

#ifndef STD_SSTREAM_H
#include "std_sstream.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{
  
// ============================================================================
// D_TREE_POINT_LOCATOR_NODE FACET
// ============================================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
d_tree_point_locator_node<DC, DB>::
d_tree_point_locator_node()

{
  // Preconditions:

  // Body:

  // Initialize the branches to null.

  for(int i=0; i<DEGREE; ++i)
  {
    _branches[i] = 0;
  }

  _branch_ct = 0;

  // Postconditions:

}

template <int DC, int DB>
d_tree_point_locator_node<DC, DB>::
d_tree_point_locator_node(const d_tree_point_locator_node<DC, DB>& xother)
{
  // Preconditions:

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(*this == xother);

  // Exit:

  return;
}

template <int DC, int DB>
d_tree_point_locator_node<DC, DB>&
d_tree_point_locator_node<DC, DB>::
operator=(const d_tree_point_locator_node<DC, DB>& xother)
{
  // Preconditions:

  // Body:

  if(this == &xother)
    return *this;

  _box_list = xother._box_list;

  for(int i=0; i<DEGREE; ++i)
    _branches[i] = xother._branches[i];

  _branch_ct = xother._branch_ct;

  // Postconditions:

  ensure(*this == xother);

  return *this;
}

template <int DC, int DB>
bool
d_tree_point_locator_node<DC, DB>::
operator==(const d_tree_point_locator_node<DC, DB>& xother)
{
  // Preconditions:

  // Body:

  if(this == &xother)
    return true;

  bool result = (_box_list == xother._box_list);

  for(int i=0; i<DEGREE; ++i)
  {
    result = result && ( _branches[i] == xother._branches[i]);
  }

  result == result && (_branch_ct == xother._branch_ct);

  // Postconditions:

  // Exit:

  return result;
}

template <int DC, int DB>
d_tree_point_locator_node<DC, DB>::
~d_tree_point_locator_node()
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
d_tree_point_locator_node<DC, DB>::
invariant() const
{
  bool result = true;

  invariance(branch_ct() <= degree());
  invariance_for_all(i, 0, degree(), (is_leaf() ? branch(i) == 0 : true));

  return result;
}

template <int DC, int DB>
d_tree_point_locator_node<DC, DB>*
d_tree_point_locator_node<DC, DB>::
branch(int xindex) const
{
  d_tree_point_locator_node<DC, DB>* result;

  // Preconditions:

  require((0 <= xindex) && (xindex < degree()));

  // Body:

  result = _branches[xindex];

  // Postconditions:


  // Exit:

  return result;
}

template <int DC, int DB>
bool
d_tree_point_locator_node<DC, DB>::
is_leaf() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_branch_ct == 0);

  // Postconditions:


  // Exit:

  return result;
}

template <int DC, int DB>
bool
d_tree_point_locator_node<DC, DB>::
is_empty() const
{
  bool result;

  // Preconditions:


  // Body:

  result = _box_list.empty();

  // Postconditions:


  // Exit:

  return result;
}


template <int DC, int DB>
void
d_tree_point_locator_node<DC, DB>::
insert_box(const d_bounding_box<DC, DB>* xbox,
           d_tree_point_locator_path<DC, DB>& xpath)
{
  // Preconditions:

  require(xpath.intersects(xbox));

  // Body:

  define_old_variable(size_type old_xpath_depth = xpath.depth());

  if(xpath.depth() == xpath.tree()->depth())
  {
    // We are as deep as we can go; insert the box here.

    _box_list.push_front(xbox);
  }
  else
  {
    // We're not as deep as we can go; keep descending.

    ptr_linked_pool<d_tree_point_locator_node>& lnode_pool =
      xpath.tree()->node_pool();

    if(!is_empty())
    {
      // This node is a leaf that already contains exactly one box.

      assertion(++(_box_list.begin()) == _box_list.end());

      // We'll have to subdivide the node and move the box;
      // iterate over all the possible branches:

      const d_bounding_box<DC, DB>* lfirst_box = _box_list.front();

      xpath.descend();
      for(size_type i=0; i<DEGREE; i++)
      {
        d_tree_point_locator_node* lbranch = _branches[i];

        // This branch is a new leaf;

        assertion(lbranch == 0);

        xpath.put_head(i);
        if(xpath.intersects(lfirst_box))
        {
          // This leaf intersects the box;
          // create the leaf and store the box.

          _branches[i] = lnode_pool.allocate();
          _branch_ct++;
          _branches[i]->_box_list.push_front(lfirst_box);
        }
      }
      xpath.put_head(0);
      xpath.ascend();
      _box_list.pop_front();
    }

    // Now this node is an interior node that contains no boxes.

    assertion(_box_list.empty());

    // Descend the branches.

    xpath.descend();
    for(size_type i=0; i<DEGREE; i++)
    {
      xpath.put_head(i);
      if(xpath.intersects(xbox))
      {
        // This branch intersects the box.

        d_tree_point_locator_node* lbranch = _branches[i];

        if(lbranch == 0)
        {
          // This branch is a new leaf;
          // create it and store the box.

          _branches[i] = lnode_pool.allocate();
          _branch_ct++;
          _branches[i]->_box_list.push_front(xbox);
        }
        else
        {
          // Descend the branch.

          lbranch->insert_box(xbox, xpath);
        }
      }
    }
    xpath.put_head(0);
    xpath.ascend();
  }

  // Postconditions:

  // Following is unexecutable for efficiency.

  ensure(unexecutable(contains_box(xbox, xpath)));
  ensure(xpath.depth() == old_xpath_depth);

  // Exit:

  return;
}

template <int DC, int DB>
void
d_tree_point_locator_node<DC, DB>::
remove_box(const d_bounding_box<DC, DB>* xbox,
           d_tree_point_locator_path<DC, DB>& xpath)
{
  // Preconditions:

  require(xpath.intersects(xbox));

  //require(is_empty() ? xpath.depth() > xpath.tree()->depth() : true);
  require(is_empty() ? xpath.depth() < xpath.tree()->depth() : true);

  // Body:

  define_old_variable(size_type old_xpath_depth = xpath.depth());

  ptr_linked_pool<d_tree_point_locator_node>& lnode_pool =
    xpath.tree()->node_pool();

  if(is_empty())
  {
    // Nothing in this node; descend the branches.

    xpath.descend();
    for(size_type i=0; i<DEGREE; i++)
    {
      xpath.put_head(i);
      if(xpath.intersects(xbox))
      {
        // Descend the branch.

        d_tree_point_locator_node* lbranch = _branches[i];
        lbranch->remove_box(xbox, xpath);
        if(lbranch->is_leaf() && lbranch->is_empty())
        {
          lnode_pool.deallocate(lbranch);
          _branches[i] = 0;
          _branch_ct--;
        }
      }
    }
    xpath.put_head(0);
    xpath.ascend();
  }
  else
  {
    // This node has a box list; it must contain xbox.
    // Find it and erase it.

    if(xbox == _box_list.front())
    {
      _box_list.pop_front();
    }
    else
    {
      typename box_list_type::iterator lprev = _box_list.begin();
      typename box_list_type::iterator lcur  = ++lprev;
      while(lcur != _box_list.end())
      {
        if(xbox == *lcur)
        {
          _box_list.erase_after(lprev);
          break;
        }
        lprev = lcur;
        ++lcur;
      }
    }
  }


  // Postconditions:

  // Following is unexecutable for efficiency.

  ensure(unexecutable(!contains_box(xbox, xpath)));
  ensure(xpath.depth() == old_xpath_depth);

  // Exit:

  return;
}


template <int DC, int DB>
bool
d_tree_point_locator_node<DC, DB>::
contains_box(const d_bounding_box<DC, DB>* xbox,
             d_tree_point_locator_path<DC, DB>& xpath) const
{
  bool result = false;

  // Preconditions:

  require(is_empty() ? xpath.depth() < xpath.tree()->depth() : true);

  // Body:

  define_old_variable(size_type old_xpath_depth = xpath.depth());

  if(is_empty())
  {
    // Nothing in this node; descend the branches.

    xpath.descend();
    for(size_type i=0; !result && (i<DEGREE); i++)
    {
      xpath.put_head(i);
      if(xpath.intersects(xbox))
      {
        // Descend the branch.

        d_tree_point_locator_node* lbranch = _branches[i];
        result = lbranch->contains_box(xbox, xpath);
      }
    }
    xpath.put_head(0);
    xpath.ascend();
  }
  else
  {
    // This node has a box list; search it for xbox.

    typename box_list_type::const_iterator litr = _box_list.begin();
    while(!result && (litr != _box_list.end()))
    {
      result = (*litr == xbox);
      ++litr;
    }
  }

  // Postconditions:

  ensure(xpath.depth() == old_xpath_depth);

  // Exit:

  return result;
}

template <int DC, int DB>
void
d_tree_point_locator_node<DC, DB>::
clear()
{
  // Preconditions:


  // Body:

  for(int i=0; i<DEGREE; i++)
  {
    _branches[i] = 0;
  }

  //$$SCRIBBLE: Added the following so that is_leaf() == true.
  _branch_ct = 0;

  _box_list.clear();

  // Postconditions:

  ensure(is_empty());
  ensure(is_leaf());

  // Exit:

  return;
}

template <int DC, int DB>
const typename d_tree_point_locator_node<DC, DB>::box_list_type&
d_tree_point_locator_node<DC, DB>::
box_list(d_tree_point_locator_path<DC, DB>& xpath) const
{
  // Preconditions:

  require(xpath.depth() == xpath.tree()->depth() ? is_leaf() : true);

  // Body

  define_old_variable(size_type old_xpath_depth = xpath.depth());

  const box_list_type* lresult_ptr;

  if(is_leaf())
  {
    lresult_ptr = &_box_list;
  }
  else
  {
    // Descend the path.

    xpath.descend();
    lresult_ptr = &(_branches[xpath.head()]->box_list(xpath));
    xpath.ascend();
  }

  // Postconditions:

  ensure(xpath.depth() == old_xpath_depth);

  // Exit:

  return *lresult_ptr;
}

template <int DC, int DB>
const typename d_tree_point_locator_node<DC, DB>::box_list_type&
d_tree_point_locator_node<DC, DB>::
box_list() const
{
  // Preconditions:


  // Body

  const box_list_type& result = _box_list;

  // Postconditions:

  // Exit:

  return result;
}

template <int DC, int DB>
string*
d_tree_point_locator_node<DC, DB>::
to_string() const
{
  ostringstream ostr;

  ostr << "d_tree_point_locator_node:" << endl;

  ostr << "this = " << this << endl;

//   cout << "d_tree_point_locator_node:" << endl;

//   cout << "this = " << this << endl;

  //$$SCRIBBLE: In at least one simple test case box_list().end() == NULL
  //            and the iteration never terminates. So, comment it out for now.

//  ostr << "box_list() = " << endl;
//   cout << "box_list() = " << endl;

//   typename box_list_type::const_iterator lbox_itr = box_list().begin();
//   while(lbox_itr != box_list().end())
//   {
//     ostr <<  **lbox_itr << endl;
//   }

//   cout << "DEGREE = " << DEGREE << endl;

  for(int i=0; i<DEGREE; ++i)
  {
    ostr << "_branches[i] = " << _branches[i] << endl;
//     cout << "_branches[i] = " << _branches[i] << endl;
  }

  for(int i=0; i<DEGREE; ++i)
  {
    if(_branches[i] != 0)
    {
//       cout << "+++ _branches[i] = " << _branches[i] << endl;
      string* s = _branches[i]->to_string();
      ostr << *s;
      delete s;
    }
  }

  ostr << ends;

  string* result = new string(ostr.str());

//   cout << "*result = " << *result << endl;

  return result;
}


template <int DC, int DB>
size_type
d_tree_point_locator_node<DC, DB>::
degree()
{
  size_type result;

  // Preconditions:


  // Body:

  result = DEGREE;

  // Postconditions:

  ensure(result == DEGREE);

  // Exit:

  return result;
}

template <int DC, int DB>
size_type
d_tree_point_locator_node<DC, DB>::
branch_ct() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = _branch_ct;

  // Postconditions:


  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

template <int DC, int DB>
d_tree_point_locator_node<DC, DB>*
d_tree_point_locator_node<DC, DB>::
next() const
{
  d_tree_point_locator_node* result;

  // Preconditions:


  // Body:

  result = _branches[0];

  // Postconditions:


  // Exit:

  return result;
}

template <int DC, int DB>
void
d_tree_point_locator_node<DC, DB>::
put_next(d_tree_point_locator_node<DC, DB>* xnode)
{
  // Preconditions:


  // Body:

  _branches[0] = xnode;

  // Postconditions:

  ensure(next() == xnode);

  // Exit:

  return;
}

} // namespace geometry

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <int DC, int DB>
ostream&
geometry::operator<<(ostream& xos, const geometry::d_tree_point_locator_node<DC, DB>& xnode)
{
  string* s = xnode.to_string();
  xos << *s;
  delete s;

  return xos;
}

#endif // ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif // D_TREE_POINT_LOCATOR_NODE_IMPL_H
