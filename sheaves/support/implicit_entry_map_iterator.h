

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class implicit_entry_map_iterator

#ifndef IMPLICIT_ENTRY_MAP_ITERATOR_H
#define IMPLICIT_ENTRY_MAP_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef IMPLICIT_ENTRY_MAP_H
#include "implicit_entry_map.h"
#endif

namespace sheaf
{

///
/// An iterator over the entries in an implicit_entry_map.  This
/// iteration is NOT order preserving.
///
template <typename E, typename I>
class SHEAF_DLL_SPEC implicit_entry_map_iterator : public any
{

  // ===========================================================
  /// @name IMPLICIT_ENTRY_MAP_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef typename implicit_entry_map<E, I>::pod_type pod_type;

  ///
  /// Creates an iterator for xmap.
  ///
  implicit_entry_map_iterator(const implicit_entry_map<E, I>& xmap);

  ///
  /// Destructor
  ///
  ~implicit_entry_map_iterator();

  ///
  /// The current value of the iteration (mutable version).
  ///
  E& item();

  ///
  /// The current value of the iteration (const version).
  ///
  const E& item() const;

  ///
  /// The current id of the value of the iteration.
  ///
  pod_type id() const;

  ///
  /// Makes item() the next integer in the iteration.
  ///
  void next();

  ///
  /// True if iteration is finished.
  ///
  bool is_done() const;

  ///
  /// Restarts the iteration.
  ///
  void reset();

protected:

  ///
  /// Default constructor; disabled.
  ///
  implicit_entry_map_iterator() {};

  ///
  /// Copy constructor.
  ///
  implicit_entry_map_iterator(const implicit_entry_map_iterator<E, I>& xother);

private:

  ///
  /// The implicit_entry_map this is iterating over.
  ///
  const implicit_entry_map<E, I>* _map;

  ///
  /// The current index in the iteration.
  ///
  pod_type _id;

  ///
  /// The current value of the iteration.
  ///
  mutable E* _item;

  ///
  /// The type of the explicit value map.
  ///
  typedef typename implicit_entry_map<E, I>::explicit_value_map_type explicit_value_map_type;

  ///
  /// The type of the explicit value iterator.
  ///
  typedef typename explicit_value_map_type::const_iterator explicit_value_iterator;

  ///
  /// The iterator over the explicit values.
  ///
  explicit_value_iterator _explicit_value_itr;

  ///
  /// The type of the implicit interval map.
  ///
  typedef typename implicit_entry_map<E, I>::interval_map_type interval_map_type;

  ///
  /// The type of the implicit interval iterator.
  ///
  typedef typename interval_map_type::const_iterator interval_iterator_type;

  ///
  /// The iterator for the implicit iterators.
  ///
  interval_iterator_type _interval_itr;

  ///
  /// The end of the current interval.
  ///
  pod_type _end;

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual implicit_entry_map_iterator* clone() const;

  ///
  /// Assignment operator
  ///
  implicit_entry_map_iterator& operator=(const implicit_entry_map_iterator& xother);

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

#endif // ifndef IMPLICIT_ENTRY_MAP_ITERATOR_H
