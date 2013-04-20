

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class name_multimap

#ifndef NAME_MULTIMAP_IMPL_H
#define NAME_MULTIMAP_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef NAME_MULTIMAP_H
#include "name_multimap.h"
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
  
// =============================================================================
// ANY FACET
// =============================================================================

///
template<typename index_type>
name_multimap<index_type>*
name_multimap<index_type>::
clone() const
{
  name_multimap* result;

  // Preconditions:

  // Body:

  result = new name_multimap(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
};

///
template<typename index_type>
bool
name_multimap<index_type>::
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

    invariance(_index_to_name_map.size() <= _name_to_index_map.size());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
};

///
template<typename index_type>
bool
name_multimap<index_type>::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const name_multimap*>(xother) != 0;

  // Postconditions:

  return result;

};

///
template<typename index_type>
bool
name_multimap<index_type>::
operator==(const name_multimap& xother)
{

  // Preconditions:

  // Body:

  bool result =
    (_name_to_index_map == xother._name_to_index_map) &&
    (_index_to_name_map == xother._index_to_name_map);


  // Postconditions:

  // Exit

  return result;
}

template<typename index_type>
name_multimap<index_type>&
name_multimap<index_type>::
operator=(const name_multimap& xother)
{

  // Preconditions:

  // Body:

  _name_to_index_map = xother._name_to_index_map;
  _index_to_name_map = xother._index_to_name_map;

  // Postconditions:

  ensure(invariant());
  ensure(*this == xother);

  // Exit

  return *this;
}


// =============================================================================
// NAME_MULTIMAP FACET
// =============================================================================

///
template<typename index_type>
name_multimap<index_type>::
name_multimap()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

}

///
template<typename index_type>
name_multimap<index_type>::
name_multimap(const name_multimap& xother)
{

  // Preconditions:

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());
  ensure(*this == xother);

 // Exit:

}

///
template<typename index_type>
name_multimap<index_type>::
name_multimap(const string xnames[], size_type xnames_ub)
{
  // Preconditions:

  // Body:

  index_type ibegin = index_traits<index_type>::zero();
  index_type iend;
  typename index_traits<index_type>::pod_type lnames_ub = xnames_ub;
  index_traits<index_type>::put_pod(iend, lnames_ub);

  for(index_type i = ibegin; i < iend; ++i)
  {
    if(!xnames[index_traits<index_type>::pod(i)].empty())
    {
      _index_to_name_map[i].push_back(xnames[index_traits<index_type>::pod(i)]);
      _name_to_index_map[xnames[index_traits<index_type>::pod(i)]] = i;
    }
  }

  // Postconditions:

  ensure(invariant());

  // $$SCRIBBLE: disable temporarily while debugging scoped index.

  ensure_for_all(i, 0, xnames_ub, !xnames[i].empty() ? name(index_type(i)) == xnames[i] : true);

 // Exit:

}

///
template<typename index_type>
name_multimap<index_type>::
~name_multimap()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

}

///
template<typename index_type>
string
name_multimap<index_type>::
name(index_type xindex) const
{
  // Preconditions:

  // Body:

  typename index_to_name_map_type::const_iterator
  map_result = _index_to_name_map.find(xindex);

  if(map_result != _index_to_name_map.end())
  {
    // This index has a name.

    // Exit

    return map_result->second.front();
  }
  else
  {
    // This index has no name.

    string result; // empty string

    // Postcondition:

    ensure(result.empty() == !contains_index(xindex));

    // Exit

    return result;
  }

}

template<typename index_type>
string
name_multimap<index_type>::
name(index_type xindex, int xi) const
{
  // Preconditions:

  // Body:

  string result;

  const name_list_type& lnames = all_names(xindex);
  const_name_iterator litr = lnames.begin();
  int i = 0;
  while(litr != lnames.end())
  {
    if(i == xi)
    {
      result = *litr;
      break;
    }
    ++litr;
    ++i;
  }

  // Postconditions:

  ensure((!result.empty()) == ((0 <= xi) && (xi < name_ct(xindex))) );

  // Exit:

  return result;
}

template<typename index_type>
const typename name_multimap<index_type>::name_list_type&
name_multimap<index_type>::
all_names(index_type xindex) const
{
  // Preconditions:

  // Body:

  static const name_list_type empty_list;

  const_iterator map_result = _index_to_name_map.find(xindex);

  const name_list_type& result =
    (map_result != _index_to_name_map.end()) ? map_result->second : empty_list;

  // Postconditions:

  // Exit:

  return result;
}

///
template<typename index_type>
void
name_multimap<index_type>::
all_names(index_type xindex, block<string>& xresult) const
{
  // Preconditions:

  // Body:

  xresult.reserve(4); // Arbitrary; will resize as needed.
  xresult.set_ct(0);

  const name_list_type& lnames = all_names(xindex);

  for(const_name_iterator itr = lnames.begin(); itr != lnames.end(); ++itr)
  {
    xresult.push_back(*itr);
  }

  // Postconditions:

  ensure(xresult.ct() == name_ct(xindex));

  // Exit:

}

///
template<typename index_type>
index_type
name_multimap<index_type>::
index(const string& xname) const
{
  index_type result;

  // Preconditions:

  require(!xname.empty());

  // Body:

  // Lookup the name in the name-to-index map.

  typedef typename name_to_index_map_type::const_iterator itr_type;

  itr_type litr = _name_to_index_map.find(xname);

  if(litr != _name_to_index_map.end())
  {
    // Name is in the map; result is the value of the map.

    result = litr->second;
  }
  else
  {
    // Name not in the map; result is invalid.

    result = index_traits<index_type>::invalid();
  }

  // Postconditions:

  // Must be unexecutable or create infinite recursion.

  ensure(unexecutable(index_traits<T>::is_valid(result) == !contains_name(xname)));

  // Exit

  return result;
}

///
template<typename index_type>
void
name_multimap<index_type>::
put_entry(const entry_type& xentry, bool xunique)
{
  // Preconditions:

  require(!xentry.second.empty());
  require(!contains_name(xentry.second));

  // Body:

  if(xunique)
  {
    // Delete all other entries for this index.

    delete_index(xentry.first);
  }


  _index_to_name_map[xentry.first].push_back(xentry.second);
  _name_to_index_map[xentry.second] = xentry.first;

  // Postconditions:

  ensure(contains_entry(xentry));

  // Exit
}

///
template<typename index_type>
void
name_multimap<index_type>::
put_entry(index_type xindex, const string& xname, bool xunique)
{
  // Preconditions:

  require(!xname.empty());
  require(!contains_name(xname));

  // Body:

  entry_type ltmp(xindex, xname);
  put_entry(ltmp, xunique);

  // Postconditions:

  ensure(contains_entry(xindex, xname));

  // Exit:

}

///
template<typename index_type>
inline bool
name_multimap<index_type>::
contains_name(const string& xname) const
{
  bool result;

  // Preconditions:

  require(!xname.empty());

  // Body:

  result = _name_to_index_map.find(xname) != _name_to_index_map.end();

  // Postconditions:

  // Exit

  return result;
}

///
template<typename index_type>
inline bool
name_multimap<index_type>::
contains_index(index_type xindex) const
{
  return _index_to_name_map.find(xindex) != _index_to_name_map.end();
};

///
template<typename index_type>
inline bool
name_multimap<index_type>::
contains_entry(index_type xindex, const string& xname) const
{
  // Preconditions:

  require(!xname.empty());

  // Body:

  bool result;

  entry_type entry(xindex, xname);

  result = contains_entry(entry);

  // Postconditions:

  // Exit:

  return result;
}

///
template<typename index_type>
bool
name_multimap<index_type>::
contains_entry(const entry_type& xentry) const
{

  // Preconditions:

  require(!xentry.second.empty());

  // Body:

  bool result;

  result = contains_name(xentry.second) && (index(xentry.second) == xentry.first);

  // Postconditions:

  // Exit:

  return result;
}

///
template<typename index_type>
inline void
name_multimap<index_type>::
delete_index(index_type xindex)
{
  // Preconditions:

  // Body:

  // Remove xindex from the name to index map.

  const name_list_type& lnames = all_names(xindex);

  for(const_name_iterator itr = lnames.begin(); itr != lnames.end(); ++itr)
  {
    _name_to_index_map.erase(*itr);
  }

  // Remove xindex from the index to name map.

  _index_to_name_map.erase(xindex);

  // Postcondition

  ensure(!contains_index(xindex));

  // Exit

  return;
}

///
template<typename index_type>
inline void
name_multimap<index_type>::
delete_name(const string& xname)
{
  // Preconditions:

  require(!xname.empty());

  // Find entry in name to index map.

  typename name_to_index_map_type::iterator itr =
    _name_to_index_map.find(xname);

  if(itr != _name_to_index_map.end())
  {
    // Found name to index entry;
    // find and delete corresponding index to name entry.

    iterator lindex_entry = _index_to_name_map.find(itr->second);
    name_list_type& lnames = lindex_entry->second;

    name_iterator lname_itr = lnames.begin();
    while(lname_itr != lnames.end())
    {
      if((*lname_itr) == xname)
      {
        lnames.erase(lname_itr);
        break;
      }
      ++lname_itr;
    }

    if(lnames.empty())
    {
      // List of names for this index is now empty;
      // delete the entry.

      _index_to_name_map.erase(lindex_entry);
    }

    // Now erase the name to index entry.

    _name_to_index_map.erase(itr);
  }

  // Postcondition

  ensure(!contains_name(xname));

  // Exit

  return;
}

///
template<typename index_type>
inline typename name_multimap<index_type>::const_iterator
name_multimap<index_type>::
begin() const
{
  return _index_to_name_map.begin();
}

///
template<typename index_type>
inline typename name_multimap<index_type>::const_iterator
name_multimap<index_type>::
end() const
{
  return _index_to_name_map.end();
}

///
template<typename index_type>
inline int
name_multimap<index_type>::
ct() const
{
  return _index_to_name_map.size();
}

template<typename index_type>
inline void
name_multimap<index_type>::
print() const
{   
  print(cout, *this);
}

template<typename index_type>
void
name_multimap<index_type>::
print(ostream& xos, const name_multimap<index_type>& xm) const
{
  // Preconditions:

  // Body:

  typename name_multimap<index_type>::const_iterator itr = xm.begin();
  while(itr != xm.end())
  {
    xos << "index: " << itr->first << "\tnames: " ;

    const typename name_multimap<index_type>::name_list_type& lnames = itr->second;
    typename name_multimap<index_type>::const_name_iterator name_itr = lnames.begin();
    while(name_itr != lnames.end())
    {
      xos << "  \"" << *name_itr << "\"";
      ++name_itr;
    }
    xos << endl;
    ++itr;
  }

  // Postconditions:

  // Exit:
}

///
template<typename index_type>
inline size_type
name_multimap<index_type>::
name_ct(const index_type& xindex) const
{
  return all_names(xindex).size();
}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
template<typename index_type>
ostream& operator<<(ostream& xos, const name_multimap<index_type>& xm)
{
  // Preconditions:

  // Body:

  xm.print(xos, xm);
  return xos;

  // Postconditions:

  // Exit:

  return xos;
}

template<typename index_type>
size_t
deep_size(const name_multimap<index_type>& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add the deep size of the data members.

  typedef key_deep_size_policy<map<string, index_type> > name_to_index_policy;
  result += deep_size<string, index_type, name_to_index_policy>
                     (xp._name_to_index_map, false);

  typedef value_deep_size_policy<map<index_type, list<string> > > index_to_name_policy;
  result += deep_size<index_type, list<string>, index_to_name_policy>
                     (xp._index_to_name_map, false);
  
  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

} // namespace sheaf

#endif // ifndef NAME_MULTIMAP_IMPL_H






