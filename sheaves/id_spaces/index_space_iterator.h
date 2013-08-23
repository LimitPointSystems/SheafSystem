
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
/// Interface for class index_space_iterator

#ifndef INDEX_SPACE_ITERATOR_H
#define INDEX_SPACE_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

class hub_index_space_handle;
class index_space_collection;
class index_space_family;
class index_space_handle;

///
/// An abstract iterator over the ids of an id space.
///
class SHEAF_DLL_SPEC index_space_iterator : public any
{

  friend class explicit_index_space_state;
  friend class index_space_collection;
  friend class index_space_handle;

  // ===========================================================
  /// @name INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// Destructor
  ///
  virtual ~index_space_iterator();

  ///
  /// Assignment operator.
  ///
  virtual index_space_iterator& operator=(const index_space_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  virtual index_space_iterator* clone() const = 0;

protected:

  ///
  /// Creates an iterator for the id space.
  ///
  index_space_iterator();

  ///
  /// Copy constructor.
  ///
  index_space_iterator(const index_space_iterator& xother);

private:

  //@}


  // ===========================================================
  /// @name ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Makes id() the next id in the iteration.
  ///
  virtual void next() = 0;

  ///
  /// True if iteration is finished.
  ///
  bool is_done() const;

  ///
  /// Restarts the iteration.
  ///
  virtual void reset() = 0;

  ///
  /// Makes is_done() true.
  ///
  void force_is_done();

protected:

  ///
  /// True if the iteration is finished.
  ///
  bool _is_done;

private:

  //@}


  // ===========================================================
  /// @name POD FACET
  // ===========================================================
  //@{

public:

  ///
  /// The current id in the iteration.
  ///
  pod_type pod() const;

  ///
  /// The current unglued hub id in the iteration.
  /// synonym for unglued_hub_pod().
  ///
  pod_type hub_pod() const;

  ///
  /// The current unglued hub id in the iteration.
  ///
  pod_type unglued_hub_pod() const;

  ///
  /// The current glued hub id in the iteration.
  ///
  pod_type glued_hub_pod() const;

protected:

  ///
  /// Set is_done() and invalidate pod() and hub_pod().
  ///
  void invalidate_ids();  

  ///
  /// The current id in the iteration.
  ///
  pod_type _pod;

  ///
  /// The current hub id in the iteration.
  ///
  pod_type _hub_pod;

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id space family for this (const version).
  ///
  const index_space_family& id_spaces() const;

  ///
  /// The hub id space.
  ///
  const hub_index_space_handle& hub_id_space() const;

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
  virtual const index_space_collection& host() const = 0;

  ///
  /// Index of this space.
  ///
  virtual pod_type index() const = 0;

  ///
  /// Name of this space.
  ///
  string name() const;

  ///
  /// True if this iterator is attached to a state.
  ///
  virtual bool is_attached() const = 0;

  ///
  /// Attach to the state with index xindex in the id space family xid_spaces.
  ///
  void attach_to(const index_space_family& xid_spaces, pod_type xindex);

  ///
  /// Attach to the state with name xname in the id space family xid_spaces.
  ///
  void attach_to(const index_space_family& xid_spaces, const string& xname);

  ///
  /// Attach to the state with index xindex in the id space family id_spaces().
  ///
  virtual void attach_to(pod_type xindex) = 0;

  ///
  /// Attach to the state with name xname in the id space family id_spaces().
  ///
  void attach_to(const string& xname);

  ///
  /// Attach to the state of the id space xid_space.
  ///
  void attach_to(const index_space_handle& xid_space);

  ///
  /// Attach to the state with local scope id, xlocal_id in the host id space
  /// collection xhost.
  ///
  virtual void attach_to(const index_space_collection& xhost,
			 pod_type xlocal_id) = 0;

  ///
  /// Detach this handle form its state, if any.
  ///
  virtual void detach() = 0;

  ///
  /// True if this conforms to the handle type required by the state
  /// with index xindex in the id space family, xid_spaces.
  ///
  bool conforms_to_state(const index_space_family& xid_spaces,
			 pod_type xindex) const;

  ///
  /// True if this conforms to the handle type required by the state
  /// with name xname in the id space family, xid_spaces.
  ///
  bool conforms_to_state(const index_space_family& xid_spaces,
			 const string& xname) const;

  ///
  /// True if this conforms to the handle type required by the state
  /// with id xid.
  ///
  bool conforms_to_state(pod_type xid) const;

  ///
  /// True if this conforms to the handle type required by the state
  /// with name xname.
  ///
  bool conforms_to_state(const string& xname) const;

  ///
  /// True if this conforms to the handle type required by the state
  /// with local scope id xlocal_id in the host id space collection xhost.
  ///
  virtual bool conforms_to_state(const index_space_collection& xhost,
				 pod_type xlocal_id) const = 0;

protected:

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
  virtual bool invariant() const;

protected:

private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// The deep size of index_space_iterator& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const index_space_iterator& xn, bool xinclude_shallow = true);
  
} // namespace sheaf

#endif // ifndef INDEX_SPACE_ITERATOR_H
