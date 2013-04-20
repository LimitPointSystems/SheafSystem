
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class triorder_iterator


#ifndef TRIORDER_ITERATOR_H
#define TRIORDER_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FILTERED_DEPTH_FIRST_ITERATOR_H
#include "filtered_depth_first_iterator.h"
#endif

namespace sheaf
{
  
///
/// @deprecated Use triorder_itr.
/// Specialization of the filtered depth-first iterator which exposes all
/// three actions to the client; the PREVISIT_ACTION, the POSTVISIT_ACTION
/// and the LINK_ACTION.
///
class SHEAF_DLL_SPEC triorder_iterator : public filtered_depth_first_iterator
{
public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached iterator,
  /// with and all-pass filter
  ///
  triorder_iterator();

  ///
  /// Copy constructor
  ///
  triorder_iterator(const triorder_iterator& xother);

  ///
  /// Destructor
  ///
  ~triorder_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual triorder_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xanchor, with no filter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  triorder_iterator(const abstract_poset_member& xanchor,
		    bool xdown,
		    bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  triorder_iterator(const abstract_poset_member& xanchor,
		    const subposet& xfilter,
		    bool xdown,
		    bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilte_indexr.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  triorder_iterator(const abstract_poset_member& xanchor,
		    pod_index_type xfilter_index,
		    bool xdown,
		    bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  triorder_iterator(const abstract_poset_member& xanchor,
		    const scoped_index& xfilter_index,
		    bool xdown,
		    bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_name.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  triorder_iterator(const abstract_poset_member& xanchor,
		    const string& xfilter_name,
		    bool xdown,
		    bool xstrict);
};

} // namespace sheaf

#endif // ifndef TRIORDER_ITERATOR_H