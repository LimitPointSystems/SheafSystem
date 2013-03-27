// $RCSfile: block_decomposition_iterator.h,v $ $Revision: 1.22 $ $Date: 2013/01/12 17:17:38 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class block_decomposition_iterator

#ifndef BLOCK_DECOMPOSITION_ITERATOR_H
#define BLOCK_DECOMPOSITION_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FILTERED_DEPTH_FIRST_MEMBER_ITERATOR_H
#include "filtered_depth_first_member_iterator.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

namespace sheaf
{
  
///
/// Iterates in postorder over the intersection of a subposet filter
/// with a directional (up or down) set of a poset member anchor.
/// Attaches an a handle of type abstract_poset_member to the
/// current member of the iteration.
///
class SHEAF_DLL_SPEC block_decomposition_iterator : public filtered_depth_first_member_iterator
{

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached iterator,
  /// with and all-pass filter
  ///
  block_decomposition_iterator();

  ///
  /// Copy constructor
  ///
  block_decomposition_iterator(const block_decomposition_iterator& xother);

  ///
  /// Assignment operator
  ///
  virtual block_decomposition_iterator& operator=(const filtered_depth_first_member_iterator& xother);

  ///
  /// Assignment operator
  ///
  block_decomposition_iterator& operator=(const block_decomposition_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~block_decomposition_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual block_decomposition_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored at xanchor
  /// If xdown, iterate in the down direction, otherwise iterate up.
  /// If xstrict, iterate over strict up/down set only.
  ///
  explicit block_decomposition_iterator(const abstract_poset_member& xanchor,
                                        bool xdown = DOWN,
                                        bool xstrict = NOT_STRICT);
  // Explicit above prevents interpretation as conversion from abstract_poset_meber&.

  ///
  /// The types of action a client should take when
  /// the iterator returns control to the client.
  ///
  enum action_type
  {
    BLOCK_ACTION,
    NEIGHBORHOOD_ACTION,
    NOT_AN_ACTION
  };

  ///
  /// The type of action the client should take
  /// when the iterator returns control to the client.
  ///
  action_type action() const;

  ///
  /// Makes this the next member of the iteration.
  ///
  virtual void next();

  ///
  /// Restarts the iteration.
  ///
  virtual void reset(bool xreset_markers = true);

  ///
  /// The blocks subposet.
  ///
  subposet& blocks();

  ///
  /// The neighborhoods subposet.
  ///
  subposet& neighborhoods();

  ///
  /// The center member of the current neighborhood, if any.
  ///
  abstract_poset_member& center_member();

  ///
  /// The type of the block neighbors list.
  ///
  typedef hash_map<pod_index_type, list<scoped_index> > neighbor_list_type;

  ///
  /// The list of neighboors of each block.
  ///
  neighbor_list_type* neighbor_list();

protected:

  ///
  /// Covariant constructor; supports virtual construction of data members.
  ///
  block_decomposition_iterator(filtered_depth_first_iterator* xitr,
                               abstract_poset_member* xitem);


  ///
  /// The type of action the client should take;
  /// the state of the iterator.
  ///
  action_type _action;

  ///
  /// The blocks subposet.
  ///
  subposet _blocks;

  ///
  /// The neighborhoods subposet.
  ///
  subposet _neighborhoods;

  ///
  /// The center member of the current neighborhood, if any.
  ///
  total_poset_member _center_member;

  ///
  /// True if below a neighborhood member.
  ///
  bool _below_neighborhood;

  ///
  /// Makes this the next member of the iteration.
  ///
  virtual void next(bool xtruncate);

  ///
  /// Forwards the iteration to the first action.
  ///
  void first();
};
  
} // namespace sheaf

#endif // ifndef BLOCK_DECOMPOSITION_ITERATOR_H
