
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

// Implementation for class int_set

#include "SheafSystem/int_set.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/subposet.h"
#include "SheafSystem/index_iterator.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/std_algorithm.h"

using namespace std;

///
sheaf::int_set::
int_set()
{

  // Preconditions:


  // Body:


  // Postconditions:

}


///
sheaf::int_set::
int_set(const int_set& other)
    : set<int>(other)
{

  // Preconditions:


  // Body:


  // Postconditions:

}


///
sheaf::int_set::
int_set(const int* xmbrs, int xct)
{

  // Preconditions:

  require(xmbrs != 0);
  require(xct > 0);


  // Body:

  for(int i=0;i<xct;i++)
  {
    insert(xmbrs[i]);
  }

  // Postconditions:

  ensure(unexecutable("for all i in xmbrs: this find(i) != end()"));

  // Exit:

  return;
}


///
sheaf::int_set::
~int_set()
{

  // Preconditions:


  // Body:


  // Postconditions:

}

///
void
sheaf::int_set::
insert_members(const int* xmbrs, int xct)
{

  // Preconditions:

  require(xmbrs != 0);
  require(xct > 0);


  // Body:

  for(int i=0;i<xct;i++)
  {
    insert(xmbrs[i]);
  }

  // Postconditions:

  ensure(unexecutable("for all i in xmbrs: this find(i) != end()")) ;

  // Exit:

  return;
}


///
void
sheaf::int_set::
insert_members(const subposet* xmbrs)
{
  // Preconditions:

  require(xmbrs != 0);

  // Body:

  index_iterator itr = xmbrs->indexed_member_iterator();
  while(!itr.is_done())
  {
    insert(itr.index().pod());

    itr.next();
  }

  // Postconditions:

  ensure(unexecutable("for all i in xmbrs: this find(i) != end()"));

  // Exit:

  return;
}



 

///
bool
sheaf::int_set::
is_singleton() const
{
  bool result;

  // Preconditions:

  // Body:

  // true if size() == 1 , but
  // size() is O(size()) performance, so
  // ask the question in a more efficient way

  const_iterator itr = begin();
  result = !empty() ? ++itr == end() : false;


  // Postconditions:

  // Exit

  return result;
}





 

///
bool
sheaf::int_set::
set_includes(const int_set* other, bool this_is_much_larger) const
{
  bool result;

  // Preconditions:

  require(other != 0);

  // Body:

  if(this_is_much_larger)
  {
    int_set::const_iterator itr = other->begin();
    int_set::const_iterator other_end = other->end();
    int_set::const_iterator this_end = end();

    result = true;
    while(result && itr != other_end)
    {
      result = (find(*itr) != this_end);
      itr++;
    }
  }
  else
  {
    result = includes(begin(), end(), other->begin(), other->end());
  }


  // Postconditions:

  // Exit

  return result;
}





 

///
sheaf::int_set*
sheaf::int_set::
set_union(const int_set* other) const
{
  int_set* result;

  // Preconditions:

  require(other != 0);

  // Body:

  result = new int_set;
  set_union_pa(other, result);

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}


 

///
void
sheaf::int_set::
set_union_pa(const int_set* other, int_set* result) const
{

  // Preconditions:

  require(other != 0);
  require(result != 0);

  // Body:

  ::set_union(begin(), end(), other->begin(), other->end(), inserter(*result, result->begin()));

  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::int_set::
set_union_sa(const int_set* other)
{

  // Preconditions:

  require(other != 0);

  // Body:

  const_iterator oitr = other->begin();

  while(oitr != other->end())
  {
    insert(*oitr);
    oitr++;
  }

  // Postconditions:

  // Exit

  return;
}




 

///
sheaf::int_set*
sheaf::int_set::
set_intersection(const int_set* other) const
{
  int_set* result;

  // Preconditions:

  require(other != 0);

  // Body:

  result = new int_set;
  set_intersection_pa(other, result);

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}


 

///
void
sheaf::int_set::
set_intersection_pa(const int_set* other, int_set* result) const
{

  // Preconditions:

  require(other != 0);
  require(result != 0);

  // Body:

  ::set_intersection(begin(), end(), other->begin(), other->end(), inserter(*result, result->begin()));

  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::int_set::
set_intersection_sa(const int_set* other)
{

  // Preconditions:

  require(other != 0);

  // Body:


  iterator sitr = begin();
  const_iterator oitr = other->begin();
  iterator tmp;


  int smbr, ombr;

  while(sitr != end() && oitr != other->end())
  {
    smbr = *sitr;
    ombr = *oitr;

    if( smbr < ombr )
    {
      // erasing member that iterator points to
      // invalidates iterator; increment past it first.
      tmp = sitr;
      sitr++;
      erase(tmp);
    }
    else if( smbr == ombr )
    {
      sitr++;
      oitr++;
    }
    else
    {
      oitr++;
    }

  }


  if(sitr != end())
    erase(sitr, end());

  // Postconditions:

  // Exit

  return;
}


 

///
sheaf::int_set*
sheaf::int_set::
set_difference(const int_set* other) const
{
  int_set* result;

  // Preconditions:

  require(other != 0);

  // Body:

  result = new int_set;
  set_difference_pa(other, result);

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}


 

///
void
sheaf::int_set::
set_difference_pa(const int_set* other, int_set* result) const
{

  // Preconditions:

  require(other != 0);
  require(result != 0);

  // Body:

  ::set_difference(begin(), end(), other->begin(), other->end(), inserter(*result, result->begin()));

  // Postconditions:

  // Exit

  return;
}


///
void
sheaf::int_set::
set_difference_sa(int_set* other, bool this_is_much_larger)
{

  // Preconditions:

  require(other != 0);

  // Body:


  iterator sitr = begin();
  iterator oitr = other->begin();
  iterator tmp;

  if(this_is_much_larger)
  {
    // This algorithm has performance other->size()*log(size())
    // Faster than below if this is much larger than other
    while(oitr != other->end())
    {
      erase(*oitr);
      oitr++;
    }
  }
  else
  {
    // This algorithm has performance other->size() + size();
    // faster than above if other->size() is comparable to size().

    int smbr, ombr;

    while(sitr != end() && oitr != other->end())
    {
      smbr = *sitr;
      ombr = *oitr;

      if( smbr < ombr )
      {
        sitr++;
      }
      else if( smbr == ombr )
      {
        // Erasing member that iterator points to
        // invalidates iterator; increment past it first.

        tmp = sitr;
        sitr++;
        erase(tmp);
        oitr++;
      }
      else
      {
        oitr++;
      }

    }
  }

  // Postconditions:

  // Exit

  return;
}


 

///
void
sheaf::int_set::
print() const
{
  cout << *this;
}




// Non-member functions


 

std::ostream &
sheaf::
operator << (std::ostream &os, const int_set& c)
{
  copy(c.begin(), c.end(), ostream_iterator<int>(os, " "));
  return os;
}
