

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Explicit instantiations for the geometry namespace.

#include "geometry.h"

#include "block.impl.h"
#include "std_utility.h"
#include "chart_point_3d.h"
#include "e3.h"

using namespace geometry; // Workaround for MS C++ bug.


ostream& 
geometry::
operator << (ostream &xos, const pod_pair& xn)
{
  xos << "(" << xn.first << " -> " << xn.second << ")";

  return xos;
};
 
 
ostream& 
geometry::
operator << (ostream& xos, const pod_pair_list& xl)
{
  // Preconditions:

  // Body:

  for(pod_pair_list::const_iterator i = xl.begin(); i != xl.end(); ++i)
  {
    cout << "  " << *i;
  }
  

  // Postconditions:

  // Exit:

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const pod_pair_set& xl)
{
  // Preconditions:

  // Body:

  for(pod_pair_set::const_iterator i = xl.begin(); i != xl.end(); ++i)
  {
    cout << "  " << *i;
  }
  

  // Postconditions:

  // Exit:

  return xos;
}

ostream& 
geometry::
operator << (ostream& xos, const pod_id_hash_set& xl)
{
  // Preconditions:

  // Body:

  for(pod_id_hash_set::const_iterator i = xl.begin(); i != xl.end(); ++i)
  {
    cout << "  " << *i;
  }
  

  // Postconditions:

  // Exit:

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const id_set& xl)
{
  // Preconditions:

  // Body:

  for(id_set::const_iterator i = xl.begin(); i != xl.end(); ++i)
  {
    cout << "  " << i->index();
  }
  

  // Postconditions:

  // Exit:

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const id_list& xl)
{
  // Preconditions:

  // Body:

  for(id_list::const_iterator i = xl.begin(); i != xl.end(); ++i)
  {
    cout << "  " << *i;
  }
  

  // Postconditions:

  // Exit:

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const id_list_list& xl)
{
  // Preconditions:

  // Body:

  
  if(!xl.empty())
  {
    id_list_list::const_iterator i = xl.begin();
    cout << *i;
    ++i;
    while(i != xl.end())
    {
      cout << endl << *i;
      ++i;
    }
  }
  
  // Postconditions:

  // Exit:

  return xos;
}

void
geometry::
intersect(const id_list& x1, const id_list& x2, id_list& xresult)
{
  // cout << endl << "Entering geometry::intersect." << endl;

  // Preconditions:

  require(&x1 != &xresult);
  require(&x2 != &xresult);
  
  // Body:

  xresult.clear();
  
  // We're assuming both x1 and x2 are small,
  // so just use brute force membership comparison.

  for(id_list::const_iterator i1 = x1.begin(); i1 != x1.end(); ++i1)
  {
    for(id_list::const_iterator i2 = x2.begin(); i2 != x2.end(); ++i2)
    {
      if((*i2) == (*i1))
      {
        xresult.push_back(*i2);
      }
    }
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving geometry::intersect." << endl;
  return;
}

void
geometry::
intersect(const id_list& x1, id_list& x2)
{
  // cout << endl << "Entering geometry::intersect." << endl;

  // Preconditions:

  require(&x1 != &x2);
  
  // Body:

  bool lfound;
  id_list::iterator ltmp;
  id_list::iterator i2 = x2.begin();
  
  while(i2 != x2.end())
  {
    lfound = false;
    for(id_list::const_iterator i1 = x1.begin(); i1 != x1.end(); ++i1)
    {
      if((*i2) == (*i1))
      {
        lfound = true;
        break;
      }      
    }
    if(lfound)
    {
      ++i2;
    }
    else
    {
      ltmp = i2;
      ++i2;
      x2.erase(ltmp);
    }
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving geometry::intersect." << endl;
  return;
}



ostream& 
geometry::
operator << (ostream &xos, const id_pair& xn)
{
  xos << "<" << xn.first << " , " << xn.second << ">";

  return xos;
};
 
 
ostream& 
geometry::
operator << (ostream& xos, const id_pair_list& xl)
{
  // Preconditions:

  // Body:

  for(id_pair_list::const_iterator i = xl.begin(); i != xl.end(); ++i)
  {
    cout << "  " << *i;
  }
  

  // Postconditions:

  // Exit:

  return xos;
}

 
ostream& 
geometry::
operator << (ostream& xos, const pt_list& xl)
{
  // Preconditions:

  // Body:

  for(pt_list::const_iterator i = xl.begin(); i != xl.end(); ++i)
  {
    cout << "  " << *i;
  }

  // Postconditions:

  // Exit:

  return xos;
}
 
ostream& 
geometry::
operator << (ostream& xos, const pt_list_list& xl)
{
  // Preconditions:

  // Body:

  if(!xl.empty())
  {
    pt_list_list::const_iterator i = xl.begin();
    cout << *i;
    ++i;
    while(i != xl.end())
    {
      cout << endl << *i;
      ++i;
    }
  }

  // Postconditions:

  // Exit:

  return xos;
}

