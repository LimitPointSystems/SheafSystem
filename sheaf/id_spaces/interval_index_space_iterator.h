
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
/// Interface for class interval_index_space_iterator

#ifndef COM_LIMITPOINT_SHEAF_INTERVAL_INDEX_SPACE_ITERATOR_H
#define COM_LIMITPOINT_SHEAF_INTERVAL_INDEX_SPACE_ITERATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_EXPLICIT_INDEX_SPACE_ITERATOR_H
#include "ComLimitPoint/sheaf/explicit_index_space_iterator.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

namespace sheaf
{

///
/// An iterator over an id space in which the equivalence between
/// the ids in the space and the hub id space is stored in intervals.
///
/// @todo Separate this class into two classes an iterator over ids
///       (interval_index_space_iterator) and an iterator over the
///       intervals (interval_index_space_iterval_iterator).
///
///
class SHEAF_DLL_SPEC interval_index_space_iterator : public explicit_index_space_iterator
{

  friend class interval_index_space_state;

  // ===========================================================
  /// @name INTERVAL_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  interval_index_space_iterator();

  ///
  /// Copy constructor.
  ///
  interval_index_space_iterator(const interval_index_space_iterator& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  interval_index_space_iterator(const index_space_family& xid_spaces,
				pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  interval_index_space_iterator(const index_space_family& xid_spaces,
				const std::string& xname);

  ///
  /// Assignment operator.
  ///
  interval_index_space_iterator& operator=(const interval_index_space_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~interval_index_space_iterator();

  ///
  /// Advances the iteration to the beginning of the next interval.
  ///
  void next_interval();

  ///
  /// The begin of the current interval.
  ///
  pod_type interval_begin() const;

  ///
  /// The end of the current interval.
  ///
  pod_type interval_end() const;

protected:

  ///
  /// The type of the id maps.
  ///
  typedef std::map<pod_type, pod_type> to_hub_type;

  ///
  /// Update the interval ids with the beginning interval id, xinterval_begin.
  ///
  void update_interval_ids(pod_type xinterval_begin);

  ///
  /// Invalidate the interval ids.
  ///
  void invalidate_interval_ids();

  ///
  /// The interval to hub ids.
  ///
  const to_hub_type* _to_hub;

  ///
  /// The stl iterator over ids.
  ///
  to_hub_type::const_iterator _itr;

  ///
  /// The begin of the current interval.
  ///
  pod_type _interval_begin;

  ///
  /// The end of the current interval.
  ///
  pod_type _interval_end;

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
  virtual interval_index_space_iterator& operator=(const index_space_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  virtual interval_index_space_iterator* clone() const;

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

#endif // ifndef INTERVAL_INDEX_SPACE_ITERATOR_H
