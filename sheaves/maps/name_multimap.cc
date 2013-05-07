
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class name_multimap

#include "name_multimap.h"

#include "sheaf_dll_spec.h"
#include "assert_contract.h"
#include "deep_size.h"

// =============================================================================
// NAME_MULTIMAP FACET
// =============================================================================

// PUBLIC FUNCTIONS

sheaf::name_multimap::
name_multimap()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::name_multimap::
name_multimap(const name_multimap& xother)
{
  // Preconditions:

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());
  ensure(*this == xother);

  // Exit:

  return;
}

sheaf::name_multimap::
name_multimap(const string xnames[], size_type xnames_ub)
{
  // Preconditions:

  // Body:

  for(index_type i = 0; i < xnames_ub; ++i)
  {
    if(!xnames[i].empty())
    {
      _index_to_name_map[i].push_back(xnames[i]);
      _name_to_index_map[xnames[i]] = i;
    }
  }

  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, xnames_ub, !xnames[i].empty() ? name(index_type(i)) == xnames[i] : true);

 // Exit:

  return;
}

sheaf::name_multimap::
~name_multimap()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

string
sheaf::name_multimap::
name(index_type xindex) const
{
  // Preconditions:

  // Body:

  index_to_name_map_type::const_iterator map_result =
    _index_to_name_map.find(xindex);

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

string
sheaf::name_multimap::
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

const sheaf::name_multimap::name_list_type&
sheaf::name_multimap::
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

void
sheaf::name_multimap::
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

  return;
}

sheaf::name_multimap::index_type
sheaf::name_multimap::
index(const string& xname) const
{
  index_type result;

  // Preconditions:

  require(!xname.empty());

  // Body:

  // Lookup the name in the name-to-index map.

  typedef name_to_index_map_type::const_iterator itr_type;

  itr_type litr = _name_to_index_map.find(xname);

  if(litr != _name_to_index_map.end())
  {
    // Name is in the map; result is the value of the map.

    result = litr->second;
  }
  else
  {
    // Name not in the map; result is invalid.

    result = invalid_pod_index();
  }

  // Postconditions:

  // Must be unexecutable or create infinite recursion.

  ensure(unexecutable(is_valid(result) == !contains_name(xname)));

  // Exit

  return result;
}

void
sheaf::name_multimap::
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

void
sheaf::name_multimap::
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

  return;
}

bool
sheaf::name_multimap::
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

bool
sheaf::name_multimap::
contains_index(index_type xindex) const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _index_to_name_map.find(xindex) != _index_to_name_map.end();
}

bool
sheaf::name_multimap::
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

bool
sheaf::name_multimap::
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

void
sheaf::name_multimap::
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

void
sheaf::name_multimap::
delete_name(const string& xname)
{
  // Preconditions:

  require(!xname.empty());

  // Find entry in name to index map.

  name_to_index_map_type::iterator itr = _name_to_index_map.find(xname);

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

sheaf::name_multimap::const_iterator
sheaf::name_multimap::
begin() const
{
  return _index_to_name_map.begin();
}

sheaf::name_multimap::const_iterator
sheaf::name_multimap::
end() const
{
  return _index_to_name_map.end();
}

int
sheaf::name_multimap::
ct() const
{
  return _index_to_name_map.size();
}

void
sheaf::name_multimap::
print() const
{   
  print(cout, *this);
}

void
sheaf::name_multimap::
print(ostream& xos, const name_multimap& xm) const
{
  // Preconditions:

  // Body:

  name_multimap::const_iterator itr = xm.begin();
  while(itr != xm.end())
  {
    xos << "index: " << itr->first << "\tnames: " ;

    const name_multimap::name_list_type& lnames = itr->second;
    name_multimap::const_name_iterator name_itr = lnames.begin();
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

  return;
}

sheaf::size_type
sheaf::name_multimap::
name_ct(const index_type& xindex) const
{
  return all_names(xindex).size();
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::name_multimap*
sheaf::name_multimap::
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
}

bool
sheaf::name_multimap::
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
}

bool
sheaf::name_multimap::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const name_multimap*>(xother) != 0;

  // Postconditions:

  return result;
}

bool
sheaf::name_multimap::
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

sheaf::name_multimap&
sheaf::name_multimap::
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

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

ostream&
sheaf::
operator<<(ostream& xos, const name_multimap& xm)
{
  // Preconditions:

  // Body:

  xm.print(xos, xm);
  return xos;

  // Postconditions:

  // Exit:

  return xos;
}

size_t
sheaf::
deep_size(const name_multimap& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add the deep size of the data members.

  typedef name_multimap::index_type index_type;

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


