

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class interval_set_iterator

#ifndef INTERVAL_SET_ITERATOR_H
#define INTERVAL_SET_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef INTERVAL_SET_H
#include "interval_set.h"
#endif

namespace sheaf
{

///
/// An iterator over the integers in an interval_set.
///
class SHEAF_DLL_SPEC interval_set_iterator : public any
{

  // ===========================================================
  /// @name INTERVAL_SET_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef interval_set::pod_type pod_type;

  ///
  /// Creates an iterator for xset.  If xis_member_iterator, iterate over
  /// the members of the interval.  Otherwise, iteration over the non-members
  /// within the range if the set.
  ///
  interval_set_iterator(const interval_set& xset, bool xis_member_iterator);

  ///
  /// Copy constructor.
  ///
  interval_set_iterator(const interval_set_iterator& xother);

  ///
  /// Destructor
  ///
  ~interval_set_iterator();

  ///
  /// The interval set this is iterating over.
  ///
  const interval_set& set() const;

  ///
  /// True, if iterating over members.
  ///
  bool is_member_iterator() const;

  ///
  /// The current integer of the iteration.
  ///
  pod_type item() const;

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
  interval_set_iterator() {};

  ///
  /// Assign the item to the beginning of the next interval.
  ///
  void next_interval();

  ///
  /// True, if the current interval is an interval of members.
  ///
  bool is_member_interval() const;

  ///
  /// The interval_set this is iterating over.
  ///
  const interval_set* _set;

  ///
  /// True, if iterating over the members of the set.
  ///
  bool _is_member_iterator;  
    
  ///
  /// The current integer in the iteration.
  ///
  pod_type _item;

  ///
  /// The upper bound of the current interval.
  ///
  pod_type _ub;

  ///
  /// Type of the interval map.
  ///
  typedef interval_set::map_type map_type;
 
  ///
  /// The interval map.
  ///
  const map_type* _map;  
   
  ///
  /// Type of the interval map iterator.
  ///
  typedef interval_set::map_iterator_type map_iterator_type;

  ///
  /// The interval map iterator.
  ///
  map_iterator_type _map_itr;

private:

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
  virtual interval_set_iterator* clone() const;

  ///
  /// Assignment operator
  ///
  interval_set_iterator& operator=(const interval_set_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const interval_set_iterator& xother) const;

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

#endif // ifndef INTERVAL_SET_ITERATOR_H
