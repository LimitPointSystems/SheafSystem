// $RCSfile: cover_set_iterator.h,v $ $Revision: 1.22 $ $Date: 2013/01/12 17:17:38 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class cover_set_iterator

#ifndef COVER_SET_ITERATOR_H
#define COVER_SET_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

class index_space_handle;
class index_space_iterator;
class poset_crg_state;
  
///
/// An iterator over the a cover set of a poset member.
///
class SHEAF_DLL_SPEC cover_set_iterator
{

  friend class poset_crg_state;

  // ===========================================================
  /// @name COVER_SET_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  cover_set_iterator();

  ///
  /// Creates an iterator over xcover.
  ///
  cover_set_iterator(const index_space_handle& xcover);

  ///
  /// Creates an iterator over a singleton cover xmbr_index.
  ///
  cover_set_iterator(pod_index_type xmbr_index);

  ///
  /// Copy constructor.
  ///
  cover_set_iterator(const cover_set_iterator& xother);

  ///
  /// Assignment operator
  ///
  cover_set_iterator& operator=(const cover_set_iterator& xother);

  ///
  /// Destructor; not virtual, this class can not be used as a base class.
  ///
  ~cover_set_iterator();

  ///
  /// Equality operator.
  ///
  bool operator==(const cover_set_iterator& xother) const;

  ///
  /// The current member of the iteration.
  ///
  pod_index_type item() const;

  ///
  /// True if and only if iteration
  /// has reached the end of the range.
  ///
  bool is_done() const;

  ///
  /// Makes item() the next item in the range, if any.
  ///
  void next();

  ///
  /// Prefix increment; Makes item() the next item in the range, if any.
  ///
  cover_set_iterator& operator++();

  ///
  /// Postfix increment; Makes item() the next item in the range, if any.
  ///
  cover_set_iterator operator++(int);

  ///
  /// Restarts the iteration.
  ///
  void reset();

  ///
  /// Rehosts the iteration to xcover.
  ///
  void reset(const index_space_handle& xcover);

  ///
  /// Rehosts the iterator to a singleton cover xmbr_index.
  ///
  void reset(pod_index_type xmbr_index);

  ///
  /// Makes is_done() true.
  ///
  void force_is_done();

protected:

private:

  ///
  /// The current id of the iteration.
  ///
  index_space_iterator* _itr;

  ///
  /// The current item of the iteration.
  ///
  pod_index_type _item;

  ///
  /// True if the iteration is done.
  ///
  bool _is_done;

  //@}
};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

///
/// Inserts the cover set referred to by xi into ostream xos.
///
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const cover_set_iterator& xi);
  
 
} // namespace sheaf

#endif // ifndef COVER_SET_ITERATOR_H

