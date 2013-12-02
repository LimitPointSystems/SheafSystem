
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Interface for class reserved_primary_index_space_iterator

#ifndef RESERVED_PRIMARY_INDEX_SPACE_ITERATOR_H
#define RESERVED_PRIMARY_INDEX_SPACE_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_ITERATOR_H
#include "explicit_index_space_iterator.h"
#endif

namespace sheaf
{

///
/// An iterator over a reserved term in the primary sum id space
/// in which the equivlence between the ids in the space and the hub id space.
/// This iterator can run in two modes.  If is_active_only(), only the
/// active interval of ids will be iterated over.  If !is_active_only(),
/// all the ids of the space will be iterated over.  is_active_only() is
/// the default mode.  
///
class SHEAF_DLL_SPEC reserved_primary_index_space_iterator : public explicit_index_space_iterator
{

  friend class reserved_primary_index_space_state;

  // ===========================================================
  /// @name RESERVED_PRIMARY_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  reserved_primary_index_space_iterator();

  ///
  /// Copy constructor.
  ///
  reserved_primary_index_space_iterator(const reserved_primary_index_space_iterator& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  reserved_primary_index_space_iterator(const index_space_family& xid_spaces,
					pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  reserved_primary_index_space_iterator(const index_space_family& xid_spaces,
					const std::string& xname);

  ///
  /// Assignment operator.
  ///
  reserved_primary_index_space_iterator& operator=(const reserved_primary_index_space_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~reserved_primary_index_space_iterator();

  ///
  /// The offset into the hub id space.
  ///
  pod_type offset() const;

  ///
  /// True if and only the active interval of the id space is iterated over.
  /// Otherwise, all the ids in the space will be iterated over.
  ///
  bool is_active_only() const;

  ///
  /// Set the iteration mode.  If xis_active_only, only the active interval
  /// of the id space is iterated over.  Otherwise, all the ids in the space
  /// will be iterated over.
  ///
  void put_is_active_only(bool xis_active_only);

protected:

  ///
  /// The offset into the hub id space.
  ///
  pod_type _offset;

  ///
  /// The end id in the iteration.
  ///
  pod_type _end;

  ///
  /// True if and only the active interval of the id space is iterated over.
  /// Otherwise, all the ids in the space will be iterated over.
  ///
  bool _is_active_only;

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_ITERATOR FACET
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
  virtual reserved_primary_index_space_iterator& operator=(const index_space_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  virtual reserved_primary_index_space_iterator* clone() const;

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

  using explicit_index_space_iterator::attach_to;

  using explicit_index_space_iterator::conforms_to_state;

protected:

  ///
  ///
  /// Attach to the explicit id space state xstate.
  ///
  virtual void attach_to(explicit_index_space_state* xstate);

  ///
  /// True if this conforms to the iterator type required by the
  /// explicit id space state xstate.
  ///
  virtual bool conforms_to_state(explicit_index_space_state* xstate) const;

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
  /// Class invariant.
  ///
  virtual bool invariant() const ;

protected:

private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

} // namespace sheaf

#endif // ifndef RESERVED_PRIMARY_INDEX_SPACE_ITERATOR_H
