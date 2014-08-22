
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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
/// Interface for class explicit_index_space_iterator

#ifndef COM_LIMITPOINT_SHEAF_EXPLICIT_INDEX_SPACE_ITERATOR_H
#define COM_LIMITPOINT_SHEAF_EXPLICIT_INDEX_SPACE_ITERATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_INDEX_SPACE_ITERATOR_H
#include "ComLimitPoint/sheaf/index_space_iterator.h"
#endif

namespace sheaf
{

class explicit_index_space_state;

///
/// An implementation of class index_space_iterator for an
/// explicit_index_space_state.
///
class SHEAF_DLL_SPEC explicit_index_space_iterator : public index_space_iterator
{

  friend class explicit_index_space_state;

  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor
  ///
  virtual ~explicit_index_space_iterator();

protected:

  ///
  /// Default constructor.
  ///
  explicit_index_space_iterator();

  ///
  /// Copy constructor.
  ///
  explicit_index_space_iterator(const explicit_index_space_iterator& xother);

  ///
  /// Assignment operator.
  ///
  explicit_index_space_iterator& operator=(const explicit_index_space_iterator& xother);

  ///
  /// The explicit state (mutable version).
  ///
  explicit_index_space_state& state();

  ///
  /// The explicit state (const version).
  ///
  const explicit_index_space_state& state() const;

  ///
  /// The explicit state.
  ///
  explicit_index_space_state* _state;

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Assignment operator.
  ///
  virtual explicit_index_space_iterator& operator=(const index_space_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  virtual explicit_index_space_iterator* clone() const = 0;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The host collection.
  ///
  virtual const index_space_collection& host() const;

  ///
  /// Index of this space.
  ///
  virtual pod_type index() const;

  ///
  /// True if this iterator is attached to a state.
  ///
  virtual bool is_attached() const;

  using index_space_iterator::attach_to;

  ///
  /// Attach to the state with index xindex in the id space family id_spaces().
  ///
  virtual void attach_to(pod_type xindex);

  ///
  /// Attach to the state with local scope id, xlocal_id in the host id space
  /// collection xhost.
  ///
  virtual void attach_to(const index_space_collection& xhost,
			 pod_type xlocal_id);

  ///
  /// Detach this iterator form its state, if any.
  ///
  virtual void detach();

  using index_space_iterator::conforms_to_state;

  ///
  /// True if this conforms to the handle type required by the state
  /// with local scope id xlocal_id in the host id space collection xhost.
  ///
  virtual bool conforms_to_state(const index_space_collection& xhost,
				 pod_type xlocal_id) const;

protected:

  ///
  /// Attach to the explicit id space state xstate.
  ///
  virtual void attach_to(explicit_index_space_state* xstate) = 0;

  ///
  /// True if this conforms to the iterator type required by the
  /// explicit id space state xstate.
  ///
  virtual bool conforms_to_state(explicit_index_space_state* xstate) const = 0;

  ///
  /// The explicit id space state at id xindex in id space family id_spaces().
  /// Returns null if no id space stae is available at index xindex.
  ///
  explicit_index_space_state* state(pod_type xindex) const;

  ///
  /// The explicit id space state with local scope id xlocal_id in the host
  /// id space collection xhost.
  ///
  explicit_index_space_state* state(const index_space_collection& xhost,
				    pod_type xlocal_id) const;

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

#endif // ifndef EXPLICIT_INDEX_SPACE_ITERATOR_H
