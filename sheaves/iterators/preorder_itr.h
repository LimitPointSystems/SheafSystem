

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class preorder_itr

#ifndef PREORDER_ITR_H
#define PREORDER_ITR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FILTERED_DEPTH_FIRST_ITR_H
#include "filtered_depth_first_itr.h"
#endif

namespace sheaf
{
  
///
/// Specialization of the filtered depth-first iterator which exposes
/// the PREVISIT_ACTION to the client.
///

template <typename T>
class SHEAF_DLL_SPEC preorder_itr : public filtered_depth_first_itr<T>
{
  // ===========================================================
  /// @name PREORDER_ITR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates an unattached iterator,
  /// with and all-pass filter
  ///
  preorder_itr();

  ///
  /// Copy constructor
  ///
  preorder_itr(const preorder_itr& xother);

  ///
  /// Destructor
  ///
  ~preorder_itr();

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xanchor, with no filter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  preorder_itr(const abstract_poset_member& xanchor,
               bool xdown,
               bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  preorder_itr(const abstract_poset_member& xanchor,
               const subposet& xfilter,
               bool xdown,
               bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  preorder_itr(const abstract_poset_member& xanchor,
               pod_index_type xfilter_index,
               bool xdown,
               bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_index.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  preorder_itr(const abstract_poset_member& xanchor,
               const scoped_index& xfilter_index,
               bool xdown,
               bool xstrict);

  ///
  /// Creates an iterator anchored at xanchor, filtered by xfilter_name.
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  preorder_itr(const abstract_poset_member& xanchor,
               const string& xfilter_name,
               bool xdown,
               bool xstrict);

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual preorder_itr* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

protected:

private:

  //@}
};


///
/// Preorder_itr<T> using zn_to_bool for _has_visited markers.
///
typedef preorder_itr<zn_to_bool> zn_to_bool_preorder_itr;

///
/// Preorder_itr<T> using set for _has_visited markers.
///
typedef preorder_itr< set<pod_index_type> > set_preorder_itr;

///
/// Preorder_itr<T> using hash_set for _has_visited markers.
///
typedef preorder_itr< hash_set<pod_index_type> > hash_set_preorder_itr;
 
} // namespace sheaf

#endif // ifndef PREORDER_ITR_H