
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class POSET_SLICER

#ifndef POSET_SLICER_H
#define POSET_SLICER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_DFT_H
#include "poset_dft.h"
#endif

namespace sheaf
{

class abstract_poset_member;
class subposet;
class total_poset_member;
  
///
/// Traverser to compute intersection of the down set (up set)
/// of the anchor with a given subposet. The typical use of this
/// traverser is to compute the maximal (minimal) members of the
/// down set (up set) which are also contained in the given subset.
/// This produces a slice subposet, hence the name of the class.
///
class SHEAF_DLL_SPEC poset_slicer: public poset_dft
{

  friend class poset_state_handle;
  friend class abstract_poset_member;


public:

  ///
  /// Include only maximal, minimal, or all members in slice
  ///
  enum slice_mode { MAXIMAL, MINIMAL, ALL };

  // queries:

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

  // constructors:

  ///
  /// Constructor
  ///
  poset_slicer(const poset_state_handle* xhost);

  ///
  /// Destructor
  ///
  ~poset_slicer();

  // Action

  ///
  /// Finds the intersection of the down set (up set) of xanchor with xlayer
  /// if xdown (!xdown), auto-allocated
  ///
  subposet* find(abstract_poset_member* xanchor,
                 subposet* xlayer,
                 bool xdown,
                 slice_mode xmode = ALL);

  ///
  /// Finds the intersection of the down set (up set) of xanchor with xlayer
  /// if xdown (!xdown), pre-allocated
  ///
  void find_pa(abstract_poset_member* xanchor,
               subposet* xlayer,
               bool xdown,
               subposet* result,
               slice_mode xmode = ALL);

  ///
  /// Finds the intersection of the down set (up set) of xanchor with xlayer
  /// if xdown (!xdown), auto-allocated
  ///
  subposet* find(subposet* xanchor, subposet* xlayer, bool xdown, slice_mode xmode = ALL);

  ///
  /// Finds the intersection of the down set (up set) of xanchor with xlayer
  /// if xdown (!xdown), pre-allocated
  ///
  void find_pa(const subposet* xanchor, subposet* xlayer, bool xdown, subposet* result, slice_mode xmode = ALL);

  ///
  /// Find jims in the down set of the poset member xanchor, auto-allocated
  ///
  subposet* find_jims(abstract_poset_member* xanchor, slice_mode xmode = ALL);

  ///
  /// Find jims in the down set of the poset member xanchor, pre-allocated
  ///
  void find_jims_pa(abstract_poset_member* xanchor, subposet* result, slice_mode xmode = ALL);

  ///
  /// Find jims in the down set of the subposet xsp, auto-allocated
  ///
  subposet* find_jims(const subposet* xanchor, slice_mode xmode = ALL);

  ///
  /// Find jims in the down set of the subposet xsp, pre-allocated
  ///
  void find_jims_pa(const subposet* xanchor, subposet* result, slice_mode xmode = ALL);

  ///
  /// find the down set of the poset member xanchor, auto-allocated
  ///
  subposet* down_set(abstract_poset_member* xanchor, slice_mode xmode = ALL);

  ///
  /// find the down set of the poset member xanchor, pre-allocated
  ///
  void down_set_pa(abstract_poset_member* xanchor, subposet* result, slice_mode xmode = ALL);

  ///
  /// find the up set of the poset member xanchor, auto-allocated
  ///
  subposet* up_set(abstract_poset_member* xanchor, slice_mode xmode = ALL);

  ///
  /// find the up set of the poset member xanchor, pre-allocated
  ///
  void up_set_pa(abstract_poset_member* xanchor, subposet* result, slice_mode xmode = ALL);

  ///
  /// find the down set of subposet xanchor, auto-allocated
  ///
  subposet* down_set(const subposet* xanchor, slice_mode xmode = ALL);

  ///
  /// find the down set of subposet xanchor, pre-allocated
  ///
  void down_set_pa(const subposet* xanchor, subposet* result, slice_mode xmode = ALL);

  ///
  /// find the up set of subposet xanchor, auto-allocated
  ///
  subposet* up_set(const subposet* xanchor, slice_mode xmode = ALL);

  ///
  /// find the up set of subposet xanchor, pre-allocated
  ///
  void up_set_pa(const subposet* xanchor, subposet* result, slice_mode xmode = ALL);


private:

  // data:

  subposet* _layer;

  // The given subset being interesected with
  // the down set (up set) of _anchor.

  subposet* _slice;

  // The result; the intersection of _layer
  // with the down set or up set of _anchor

  slice_mode _mode;
  // Include only maximal, minimal or all members

  bool _select_only_shallowest;
  // True if maximal and going down or minimal and going up

  bool _select_only_deepest;
  // True if minimal and going down or maxinal and going up

  stack<bool> _select_enabled;
  // True if selection enabled

  int _depth_below_shallowest;
  int _height_above_deepest;


  // Actions:

  void vertical_set_pa(const subposet* xanchor, subposet* result, slice_mode xmode, bool xdown);

  void previsit_action(abstract_poset_member* xmbr);
  void link_action(abstract_poset_member* xmbr, abstract_poset_member* linked_mbr);
  void postvisit_action(abstract_poset_member* xmbr);

  /// @todo clean up the following cut and paste nightmare!

  void find_pa(const block<scoped_index>& xanchor,
               subposet* xlayer,
               bool xdown,
               subposet* result,
               slice_mode xmode = ALL);

  inline bool only_shallowest();
  inline bool only_deepest();
  inline bool layer_contains_member(const abstract_poset_member* xmbr);
  inline bool slice_contains_member(abstract_poset_member* xmbr);
  inline void insert_member(abstract_poset_member* xmbr);




};
  
} // namespace sheaf

#endif // ifndef POSET_SLICER_H
