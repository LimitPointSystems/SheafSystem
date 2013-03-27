// $RCSfile: name_map.impl.h,v $ $Revision: 1.11 $ $Date: 2013/01/12 17:17:40 $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class template name_map

#ifndef NAME_MAP_IMPL_H
#define NAME_MAP_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef NAME_MAP_H
#include "name_map.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef DEEP_SIZE_H
#include "deep_size.h"
#endif

#ifndef INDEX_TRAITS_H
#include "index_traits.h"
#endif

namespace sheaf
{
  
class poset;

// =============================================================================
// ANY FACET
// =============================================================================

template<typename T>
name_map<T>::
name_map()
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

}

template<typename T>
name_map<T>::
name_map(const name_map& xother)
{

  // Preconditions:

  // Body:


  typename index_to_name_map_type::const_iterator itr;

  for(itr = xother._index_to_name_map.begin();
      itr != xother._index_to_name_map.end();
      ++itr)
  {
    // Copy the name on the heap so it won't go out of scope.

    string* lname = new string(*(itr->second));

    // Copy the forward entry.

    typename index_to_name_map_type::value_type fwd_entry(itr->first, lname);

    _index_to_name_map.insert(fwd_entry);

    // Copy the reverse entry.

    typename hash_map<const char*, T,
    hash_cstr, key_test>::value_type rev_entry(lname->c_str(), itr->first);

    _name_to_index_map.insert(rev_entry);
  }

  // Postconditions:

  ensure(invariant());
  ensure(*this == xother);

}

template<typename T>
name_map<T>::
name_map(const string xnames[], size_type xnames_ub)
{

  // Preconditions:

  // Body:


  for(size_type i = 0; i < xnames_ub; ++i)
  {
    if(!xnames[i].empty())
    {
      // Copy the name on the heap so it won't go out of scope.

      string* lname = new string(xnames[i]);

      // Copy the forward entry.

      T l_id;
      typename index_traits<T>::pod_type li_pod = i;
      index_traits<T>::put_pod(l_id, li_pod);
      typename index_to_name_map_type::value_type fwd_entry(l_id, lname);

      _index_to_name_map.insert(fwd_entry);

      // Copy the reverse entry.

      typename hash_map<const char*, T, hash_cstr, key_test>::value_type
      rev_entry(lname->c_str(), l_id);

      _name_to_index_map.insert(rev_entry);
    }
  }

  // Postconditions:

  ensure(invariant());

  // $$SCRIBBLE: disable temporarily while debugging scoped_index.

  //  ensure_for_all(i, 0, xnames_ub, !xnames[i].empty() ? name(T(i)) == xnames[i] : true);
};


template<typename T>
name_map<T>*
name_map<T>::
clone() const
{
  name_map* result;

  // Preconditions:

  // Body:

  result = new name_map(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
};

template<typename T>
name_map<T>::
~name_map()
{
  // Preconditions:

  // Body:

  typename index_to_name_map_type::iterator itr;

  for(itr = _index_to_name_map.begin();
      itr != _index_to_name_map.end();
      itr++)
  {
    // Delete the name

    delete itr->second;
  }

  // Postconditions:

  // Exit:

};

template<typename T>
bool
name_map<T>::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(_index_to_name_map.size() == _name_to_index_map.size());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
};

template<typename T>
bool
name_map<T>::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const name_map*>(xother) != 0;

  // Postconditions:

  return result;

};

// =============================================================================
// NAME_MAP FACET
// =============================================================================

template<typename T>
string
name_map<T>::
name(T xindex) const
{
  // Preconditions:

  // Body:

  typename index_to_name_map_type::const_iterator
  map_result = _index_to_name_map.find(xindex);


  if(map_result != _index_to_name_map.end())
  {
    // This index has a name

    // Postcondition

    ///@issue Invariant is not const. Making it so would require
    /// a change to the entire sheaf hierarchy. Commenting out the invariant call
    /// for now.

    //      ensure(invariant());
    ensure(unexecutable(result.empty() == !contains_index(xindex)));

    // Exit

    return *(map_result->second);
  }
  else
  {
    // This index has no name.

    string result; // empty string

    // Postcondition:

    // Exit

    return result;
  }

};


template<typename T>
bool
name_map<T>::
operator==(const name_map& xother) const
{

  // Preconditions:

  // Body:

  // Compare the sizes of the two maps.

  bool result = (ct() == xother.ct());

  if(result)
  {
    // Get an iterator for this map.

    typename index_to_name_map_type::const_iterator itr;

    for(itr = begin(); result && (itr != end()); ++itr)
    {
      // Check that xother contains the entry <itr->first,*(itr->second)>

      entry_type map_entry(itr->first, *(itr->second));
      result = xother.contains_entry(map_entry);
    }

  }

  // Postconditions:

  // Exit

  return result;
};


template<typename T>
T
name_map<T>::
index(const string& xname) const
{
  T result;

  // Preconditions:

  require(!xname.empty());

  // Body:

  // Lookup the name in the name-to-index map

  typename hash_map<const char*, T, hash_cstr, key_test>::const_iterator
  map_result = _name_to_index_map.find(xname.c_str());


  if(map_result != _name_to_index_map.end())
  {
    // Name is in the map;
    // result is the value of the map

    result = map_result->second;
  }
  else
  {
    // Name not in the map;
    // result is invalid.

    result = index_traits<T>::invalid();
  }

  // Postconditions:

  // Must be unexecutable or create infinite recursion.

  ensure(unexecutable(index_traits<T>::is_valid(result) == !contains_name(xname)));

  // Exit

  return result;
};

template<typename T>
void
name_map<T>::
put_entry(const entry_type& xentry)
{
  // Preconditions:

  require(!xentry.second.empty());
  require(!contains_index(xentry.first));
  require(!contains_name(xentry.second));

  // Body:

  put_entry(xentry.first, xentry.second);

  // Postconditions:

  ensure(contains_entry(xentry));

  // Exit

  return;
};

template<typename T>
void
name_map<T>::
put_entry(T xindex, const string& xname)
{
  // Preconditions:

  require(!xname.empty());
  require(!contains_index(xindex));
  require(!contains_name(xname));

  // Body:

  // Copy the name string on the heap to make sure it doesn't go out of scope.

  string* lname = new string(xname);

  // Insert in the forward (index to name) map.

  typename index_to_name_map_type::value_type fwd_entry(xindex, lname);

  _index_to_name_map.insert(fwd_entry);

  // Insert in the reverse (name to index) map.

  typename name_to_index_map_type::value_type rev_entry(lname->c_str(), xindex);

  _name_to_index_map.insert(rev_entry);

  // Postconditions:

  ensure(name(xindex) == xname);
  ensure(index(xname) == xindex);

  // Exit

  return;
}

template<typename T>
bool
name_map<T>::
contains_name(const string& xname) const
{
  bool result;

  // Preconditions:

  require(!xname.empty());

  // Body:

  result = index_traits<T>::is_valid(index(xname));

  // Postconditions:

  // Exit

  return result;
}


template<typename T>
bool
name_map<T>::
contains_index(T xindex) const
{
  return !name(xindex).empty();
}

template<typename T>
bool
name_map<T>::
contains_entry(const entry_type& xentry) const
{
  return !xentry.second.empty() && (name(xentry.first) == xentry.second);
}


template<typename T>
void
name_map<T>::
delete_index(T xindex)
{
  // Preconditions:

  // Body:

  // Try to find an entry for this index.

  typename index_to_name_map_type::iterator
  map_result = _index_to_name_map.find(xindex);

  if(map_result != _index_to_name_map.end())
  {
    // This index has an entry;
    // remove it from both maps and delete the name.

    _name_to_index_map.erase(map_result->second->c_str());
    delete map_result->second;
    _index_to_name_map.erase(map_result);
  }

  // Postcondition

  ensure(invariant());
  ensure(!contains_index(xindex));

  // Exit
  return;
}

template<typename T>
void
name_map<T>::
delete_name(const string& xname)
{
  // Preconditions:

  require(!xname.empty());

  T lindex = index(xname);
  if(index_traits<T>::is_valid(lindex))
  {
    delete_index(lindex);
  }


  // Postcondition

  ensure(invariant());
  ensure(!contains_name(xname));

  // Exit

  return;
}


template<typename T>
typename name_map<T>::iterator
name_map<T>::
begin()
{
  return _index_to_name_map.begin();
}

template<typename T>
typename name_map<T>::iterator
name_map<T>::
end()
{
  return _index_to_name_map.end();
}

template<typename T>
typename name_map<T>::const_iterator
name_map<T>::
begin() const
{
  return _index_to_name_map.begin();
}

template<typename T>
typename name_map<T>::const_iterator
name_map<T>::
end() const
{
  return _index_to_name_map.end();
}

template<typename T>
int
name_map<T>::
ct() const
{
  return _index_to_name_map.size();
}

template<typename T>
void
name_map<T>::
print() const
{   
  print(cout, *this);
}

template<typename T>
void
name_map<T>::
print(ostream& xos, const name_map<T>& xm) const 
{
  typename name_map<T>::const_iterator itr = xm.begin();
  while(itr != xm.end())
  {
    xos << "index: " << itr->first
        << "\tname: " << *(itr->second)
        << endl;
    itr++;
  }

  return;
}

// =============================================================================
// NONMEMBER FUNCTIONS
// =============================================================================

template<typename T>
ostream& operator<<(ostream& xos, const name_map<T>& xm)
{
  // Preconditions:

  // Body:

  xm.print(xos, xm);
  return xos;

  // Postconditions:

  // Exit:

  return xos;
}

template<typename T>
size_t deep_size(const name_map<T>& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add the memory allocated in
  // hash_map<const char*, T, hash_cstr, key_test> _name_to_index_map.

  typedef hash_map<const char*, T, hash_cstr, key_test> name_to_index_map_type;
  typedef no_deep_size_policy<name_to_index_map_type> name_to_index_policy_type;
  result += deep_size<const char*, T, name_to_index_policy_type, hash_cstr, key_test>(xp._name_to_index_map, false);

  // Add the member allocated in hash_map<T, string*> index_to_name_map_type

  typedef hash_map<T, string*> index_to_name_map_type;
  typedef value_ptr_deep_size_policy<index_to_name_map_type> index_to_name_policy_type;
  result += deep_size<T, string*, index_to_name_policy_type>(xp._index_to_name_map, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

} // namespace sheaf

#endif // ifndef NAME_MAP_IMPL_H
