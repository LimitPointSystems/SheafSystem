//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Interface for class name_map

#ifndef NAME_MAP_H
#define NAME_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
  
// Forward declarations to support friend declaration.

template<typename T>
class name_map;

template<typename T>
ostream& operator<<(ostream& xos, const name_map<T>& xm);

///
/// The deep size of the referenced object of type name_map.
///
template<typename T>
size_t deep_size(const name_map<T>& xp, bool xinclude_shallow);

/// @issue parameter index_type hides sheaf::index_type.

///
/// A bi-directional map between names and indices of type T.
///
/// @deprecated Should use name_multimap.
///
template<typename T>
class name_map : public any
{

  friend size_t deep_size <T> (const name_map<T>& xp, bool xinclude_shallow);

public:

  // =============================================================================
  // ANY FACET
  // =============================================================================

  ///
  /// Default constructor; creates an instance with no entries.
  ///
  name_map();

  ///
  /// Copy constructor.
  ///
  name_map(const name_map& xother);

  ///
  /// Creates an instance with entries for names in xnames
  /// and sequentially assigned ids.
  ///
  name_map(const string xnames[], size_type xnames_ub);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual name_map* clone() const;

  ///
  /// Destructor
  ///
  virtual ~name_map();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;


  // =============================================================================
  // NAME_MAP FACET
  // =============================================================================

  ///
  /// The name associated with index xindex.
  ///
  string name(T xindex) const;

  ///
  /// True if this map has the same entries as xother.
  ///
  bool operator==(const name_map& xother) const;

  ///
  /// The index associated with name xname.
  ///
  T index(const string& xname) const;

  ///
  /// The type of an entry in the map.
  ///
  typedef pair<T, string> entry_type;

  ///
  /// Sets (xindex, xname) as an entry in the map.
  ///
  void put_entry(const entry_type& xentry);

  ///
  /// Sets (xindex, xname) as an entry in the map.
  ///
  void put_entry(T xindex, const string& xname);

  ///
  /// True if this already contains an entry with name xname
  ///
  bool contains_name(const string& xname) const;

  ///
  /// True if this already contains an entry with index xindex
  ///
  bool contains_index(T xindex) const;

  ///
  /// True if this already contains an entry equal to xentry
  ///
  bool contains_entry(const entry_type& xentry) const;

  ///
  /// Removes the entry for index xindex
  ///
  void delete_index(T xindex);

  ///
  /// Removes the entry for name xname
  ///
  void delete_name(const string& xname);

  ///
  /// The iterator type for this map
  ///
  typedef typename hash_map<T, string*>::iterator iterator;

  ///
  /// The initial value for iterators over this map
  ///
  iterator begin();

  ///
  /// The final value for iterators over this map
  ///
  iterator end();

  ///
  /// The const iterator type for this map
  ///
  typedef typename hash_map<T, string*>::const_iterator const_iterator;

  ///
  /// The initial value for const iterators over this map
  ///
  const_iterator begin() const;

  ///
  /// The final value for const iterators over this map
  ///
  const_iterator end() const;

  ///
  /// The number of entries in the map.
  ///
  int ct() const;
  
  ///
  /// Prints the data members of this on cout.
  /// Intended for use debugging.
  ///
  void print() const;

  ///
  /// Prints the data members of this on cout.
  /// Intended for use debugging.
  ///
  void print(ostream& xos, const name_map<T>& xm) const;

private:

  ///
  /// The type of the name to index map.
  ///
  typedef hash_map<const char*, T, hash_cstr, key_test> name_to_index_map_type;

  ///
  /// Name-to-index map.
  ///
  name_to_index_map_type _name_to_index_map;

  ///
  /// The type of the index to name map.
  ///
  typedef hash_map<T, string*> index_to_name_map_type;

  ///
  /// Index-to-index map.
  ///
  index_to_name_map_type _index_to_name_map;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template<typename index_type>
ostream& operator<<(ostream& xos, const name_map<index_type>& xm);

///
/// The deep size of the referenced object of type name_map;
/// if xinclude_shallow, add the sizeof xp to the result.
///
template<typename index_type>
size_t deep_size(const name_map<index_type>& xp, bool xinclude_shallow);

} // namespace sheaf

#endif // ifndef NAME_MAP_H






