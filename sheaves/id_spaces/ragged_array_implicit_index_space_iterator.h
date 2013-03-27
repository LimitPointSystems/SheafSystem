// $RCSfile: ragged_array_implicit_index_space_iterator.h,v $ $Revision: 1.3 $ $Date: 2013/01/15 22:23:45 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Interface for class ragged_array_implicit_index_space_iterator

#ifndef RAGGED_ARRAY_IMPLICIT_INDEX_SPACE_ITERATOR_H
#define RAGGED_ARRAY_IMPLICIT_INDEX_SPACE_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef AUTO_BLOCK_H
#include "auto_block.h"
#endif

#ifndef IMPLICIT_INDEX_SPACE_ITERATOR_H
#include "implicit_index_space_iterator.h"
#endif

namespace sheaf
{

///
/// An implementation of implicit_index_space_iterator for an implicit id
/// space in an ragged_array_index_space_interval. The equivalence between
/// the ids in the space and the hub id space is stored in a two dimensional
/// array with variable length rows.
///
class SHEAF_DLL_SPEC ragged_array_implicit_index_space_iterator : public implicit_index_space_iterator
{

  friend class ragged_array_implicit_index_space_interval;

  // ===========================================================
  /// @name RAGGED_ARRAY_IMPLICIT_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  ragged_array_implicit_index_space_iterator();

  ///
  /// Copy constructor.
  ///
  ragged_array_implicit_index_space_iterator(const ragged_array_implicit_index_space_iterator& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  ragged_array_implicit_index_space_iterator(const index_space_family& xid_spaces,
					     pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  ragged_array_implicit_index_space_iterator(const index_space_family& xid_spaces,
					     const string& xname);

  ///
  /// True if this is equivalent to xother.
  ///
  ragged_array_implicit_index_space_iterator& operator=(const ragged_array_implicit_index_space_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~ragged_array_implicit_index_space_iterator();

protected:

  ///
  /// The ragged_array to hub ids.
  ///
  const pod_type* _to_hub;

  ///
  /// The end of this id space.
  ///
  pod_type _end;

private:

  //@}


  // ===========================================================
  /// @name IMPLICIT_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_ITERATOR FACET
  // ===========================================================

public:

  ///
  /// Assignment operator.
  ///
  virtual ragged_array_implicit_index_space_iterator& operator=(const index_space_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  virtual ragged_array_implicit_index_space_iterator* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Makes item() the next id in the iteration.
  ///
  virtual void next();

  ///
  /// Restarts the iteration.
  ///
  virtual void reset();

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using implicit_index_space_iterator::attach_to;

  ///
  /// Attach to the state with local scope id, xlocal_id in the host id space
  /// collection xhost.
  ///
  virtual void attach_to(const index_space_collection& xhost,
			 pod_type xlocal_id);

  using implicit_index_space_iterator::conforms_to_state;

  ///
  /// True if this conforms to the handle type required by the state
  /// with local scope id xlocal_id in the host id space collection xhost.
  ///
  virtual bool conforms_to_state(const index_space_collection& xhost,
				 pod_type xlocal_id) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name  ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

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

#endif // ifndef RAGGED_ARRAY_IMPLICIT_INDEX_SPACE_ITERATOR_H
