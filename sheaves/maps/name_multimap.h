
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class name_multimap

#ifndef NAME_MULTIMAP_H
#define NAME_MULTIMAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

class poset;
class name_multimap;
class scoped_index;

///
/// A partial multi-valued relation with total injective inverse
/// between names and indices of type index_type.
///
class SHEAF_DLL_SPEC name_multimap : public any
{
  friend SHEAF_DLL_SPEC size_t deep_size(const name_multimap& xp,  bool xinclude_shallow);

  // ===========================================================
  /// @name NAME_MULTIMAP FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of the index in the map.
  ///
  typedef pod_index_type index_type;

  ///
  /// The type of an entry in the map.
  ///
  typedef pair<index_type, string> entry_type;

  ///
  /// The type of name list for this map.
  ///
  typedef list<string> name_list_type;

  ///
  /// The iterator type for names.
  ///
  typedef name_list_type::iterator name_iterator;

  ///
  /// The const iterator type for names.
  ///
  typedef name_list_type::const_iterator const_name_iterator;

  ///
  /// The iterator type for this map.
  ///
  typedef map<index_type, name_list_type >::iterator iterator;

  ///
  /// The const iterator type for this map.
  ///
  typedef map<index_type, name_list_type >::const_iterator const_iterator;

  ///
  /// Default constructor.
  ///
  name_multimap();

  ///
  /// Copy constructor.
  ///
  name_multimap(const name_multimap& xother);

  ///
  /// Copy constructor.
  ///
  name_multimap(const string xnames[], size_type xnames_ub);

  ///
  /// Destructor.
  ///
  virtual ~name_multimap();

  ///
  /// The primary (0-th) name associated with index xindex.
  ///
  string name(index_type xindex) const;

  ///
  /// The xi-th name associated with index xindex.
  ///
  string name(index_type xindex, int xi) const;

  ///
  /// All names associated with index xindex.
  ///
  const name_list_type& all_names(index_type xindex) const;

  ///
  /// All the names associated with xindex.
  ///
  void all_names(index_type xindex, block<string>& xresult) const;

  ///
  /// The index associated with name xname.
  ///
  index_type index(const string& xname) const;

  ///
  /// Sets (xindex, xname) as an entry in the map.
  /// If xunique, deletes all other entries for xindex.
  ///
  void put_entry(const entry_type& xentry, bool xunique);

  ///
  /// Sets (xindex, xname) as an entry in the map.
  /// If xunique, deletes all other entries for xindex.
  ///
  void put_entry(index_type xindex, const string& xname, bool xunique);

  ///
  /// True if this already contains an entry with name xname.
  ///
  bool contains_name(const string& xname) const;

  ///
  /// True if this already contains an entry with index xindex.
  ///
  bool contains_index(index_type xindex) const;

  ///
  /// True if this already contains an entry equal to xentry.
  ///
  bool contains_entry(const entry_type& xentry) const;

  ///
  /// True if this already contains an entry equal to @<xindex, xname@>.
  ///
  bool contains_entry(index_type xindex, const string& xname) const;

  ///
  /// Removes all entires for index xindex.
  ///
  void delete_index(index_type xindex);

  ///
  /// Removes the entry for name xname.
  ///
  void delete_name(const string& xname);

  ///
  /// Removes all entries.
  ///
  void clear();

  ///
  /// True if and only if the map contains no entries.
  ///
  bool empty() const;

  ///
  /// The initial value for iterators over this map.
  ///
  const_iterator begin() const;

  ///
  /// The final value for iterators over this map.
  ///
  const_iterator end() const;

  ///
  /// The number of index values in the map.
  ///
  int ct() const;

  ///
  /// Prints the data members of this on cout.
  /// Intended for use debugging.
  ///
  void print() const;

  ///
  /// Prints the data members of xm on stream xos.
  /// Intended for use debugging.
  ///
  void print(ostream& xos, const name_multimap& xm) const;
  
  ///
  /// The number of names associated with key xindex.
  ///
  size_type name_ct(const index_type& xindex) const;

private:

  ///
  /// The type of the name to index map.
  ///
  typedef map<string, index_type> name_to_index_map_type;

  ///
  /// Name to index map.
  ///
  name_to_index_map_type _name_to_index_map;

  ///
  /// The type of the index to name map.
  ///
  typedef map< index_type, list<string> > index_to_name_map_type;

  ///
  /// Index to name map.
  ///
  index_to_name_map_type _index_to_name_map;

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual name_multimap* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Equality test; true if other has the same contents as this.
  ///
  bool operator==(const name_multimap& xother);

  ///
  /// Assignment operator; make this a copy of xother.
  ///
  name_multimap& operator=(const name_multimap& xother);

protected:

private:

  //@}
};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert name_multimap xm into ostream xos. 
///
SHEAF_DLL_SPEC
ostream&
operator<<(ostream& xos, const name_multimap& xm);

///
/// The deep size of the referenced object of type name_multimap;
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC
size_t
deep_size(const name_multimap& xp, bool xinclude_shallow);
 
} // namespace sheaf

#endif // ifndef NAME_MULTIMAP_H






