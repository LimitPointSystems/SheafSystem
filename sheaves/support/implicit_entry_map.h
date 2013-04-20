
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class implicit_entry_map.

#ifndef IMPLICIT_ENTRY_MAP_H
#define IMPLICIT_ENTRY_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

namespace sheaf
{

template <typename E, typename I> class implicit_entry_map_iterator;
template <typename T> class rc_ptr;

// Forward declarations to enable friend declaration.

template <typename E, typename I> class implicit_entry_map;

///
/// The deep size of the referenced object of type implicit_entry_map@<E, I@>;
/// if xinclude_shallow, add the sizeof xvalue to the result.
///
template <typename E, typename I>
size_t 
deep_size(const implicit_entry_map<E, I>& xmap, bool xinclude_shallow = true);

///
/// A map in which the entries may be implicit.
///
template <typename E, typename I>
class SHEAF_DLL_SPEC implicit_entry_map : public any
{

  friend 
  size_t
  deep_size<E, I>(const implicit_entry_map<E, I>& xmap, bool xinclude_shallow);

  friend class implicit_entry_map_iterator<E, I>;
  friend class index_space_family;

  // ===========================================================
  /// @name IMPLICIT_ENTRY_MAP FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// The type of an explicit value.
  ///
  typedef rc_ptr<E> explicit_value_type;

  ///
  /// The type of an interval.
  ///
  typedef rc_ptr<I> interval_type;

  ///
  /// The type of iterator for this map.
  ///
  typedef implicit_entry_map_iterator<E, I> iterator_type;

  ///
  /// Default Constructor.
  ///
  implicit_entry_map();

  ///
  /// Destructor.
  ///
  ~implicit_entry_map();

  ///
  /// True if and only if this map contains an explicit entry for xid.
  ///
  bool contains_explicit_entry(pod_type xid) const;

  ///
  /// True if and only if this map contains an implicit entry for xid.
  ///
  bool contains_implicit_entry(pod_type xid) const;

  ///
  /// True if and only if contains_explicit_entry(xid) or
  /// contains_implicit_entry(xid).
  ///
  bool contains_entry(pod_type xid) const;

  ///
  /// The value at xid.  If this map contains an explicit entry
  /// at xid, the explicit value is returned.  Otherwise, a value
  /// is created by the implicit interval at xid and returned.
  ///
  E& value(pod_type xid) const;

  ///
  /// The value at xid.  If this map contains an explicit entry
  /// at xid, the explicit value is returned.  Otherwise, a value
  /// is created by the implicit interval and returned.
  /// synonym for value(xid).
  ///
  E& operator [] (pod_type xid) const;

  ///
  /// Insert the explicit value xvalue at xid
  ///
  void insert_explicit_entry(pod_type xid, E& xvalue);

  ///
  /// Insert the implicit interval xinterval.
  ///
  void insert_implicit_interval(I& xinterval);

  ///
  /// Remove the explicit entry at xid.
  ///
  void remove_explicit_entry(pod_type xid);

  ///
  /// Remove the entire interval that contains xid.
  ///
  void remove_implicit_interval(pod_type xid);

  ///
  /// Remove the entry at xid.  If xremove_interval remove the entire
  /// interval at xid otherwise only remove the implicit entry at xid.
  ///
  void remove_entry(pod_type xid, bool xremove_interval);

  ///
  /// An iterator for the entries of this map.
  ///
  implicit_entry_map_iterator<E, I>* iterator() const;

  ///
  /// The beginning id of this.
  ///
  pod_type begin() const;

  ///
  /// The ending id of this.
  ///
  pod_type end() const;

  ///
  /// The number of entries in this.
  ///
  size_type ct() const;

protected:

  ///
  /// Null explicit value.
  ///
  static const explicit_value_type& null_explicit_value();

  ///
  /// Null implicit interval.
  ///
  static const interval_type& null_interval();

  ///
  /// The explicit value at xid.
  ///
  const explicit_value_type& explicit_value(pod_type xid) const;

  ///
  /// The implicit interval that contains xid.
  ///
  const interval_type& implicit_interval(pod_type xid) const;

private:

  ///
  /// Update the extrema due to an insert of the
  /// interval [xbegin, xend) for this.
  ///
  void update_extrema_for_insert(pod_type xbegin, pod_type xend);

  ///
  /// Update the extrema due to an removal of the
  /// interval [xbegin, xend) for this.
  ///
  void update_extrema_for_remove(pod_type xbegin, pod_type xend);

  ///
  /// The type of the explicit value map.
  ///
  typedef hash_map<pod_type, explicit_value_type*> explicit_value_map_type;

  ///
  /// The map from domain ids to explicit values.
  ///
  explicit_value_map_type _explicit_value_map;

  ///
  /// The type of the interval map.
  ///
  typedef map<pod_type, interval_type*> interval_map_type;

  ///
  /// The map from domain ids to intervals.
  ///
  interval_map_type _interval_map;

  ///
  /// The beginning id of this.
  ///
  pod_type _begin;

  ///
  /// The ending id of this.
  ///
  pod_type _end;

  ///
  /// The number of entries in this.
  ///
  size_type _ct;

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual implicit_entry_map<E, I>* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================


} // namespace sheaf

#endif // IMPLICIT_ENTRY_MAP_H
