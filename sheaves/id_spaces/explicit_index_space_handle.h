
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
/// Interface for class explicit_index_space_handle

#ifndef EXPLICIT_INDEX_SPACE_HANDLE_H
#define EXPLICIT_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef INDEX_SPACE_HANDLE_H
#include "SheafSystem/index_space_handle.h"
#endif

namespace sheaf
{

class explicit_index_space_state;
class index_space_family;

///
/// An implementation of class index_space_handle for an
/// explicit_index_space_state.
///
class SHEAF_DLL_SPEC explicit_index_space_handle : public index_space_handle
{

  friend class explicit_index_space_state;

  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  explicit_index_space_handle();

  ///
  /// Copy constructor
  ///
  explicit_index_space_handle(const explicit_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  explicit_index_space_handle(const index_space_family& xid_spaces,
			      pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  explicit_index_space_handle(const index_space_family& xid_spaces,
			      const std::string& xname);

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  explicit_index_space_handle& operator=(const explicit_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~explicit_index_space_handle();

protected:

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
  /// @name INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  virtual explicit_index_space_handle& operator=(const index_space_handle& xother);

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual explicit_index_space_handle* clone() const;

protected:

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
  virtual const index_space_family& id_spaces() const;

  ///
  /// The id space family for this (mutable version).
  ///
  virtual index_space_family& id_spaces();

  ///
  /// The number of members.
  ///
  virtual size_type ct() const;

  ///
  /// Beginning id of this space.
  ///
  virtual pod_type begin() const;

  ///
  /// Ending id of this space.
  ///
  virtual pod_type end() const;

  using index_space_handle::contains;

  ///
  /// True if this space contains id xid.
  ///
  virtual bool contains(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  ///
  virtual bool contains_unglued_hub(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the glued hub id space.
  ///
  virtual bool contains_glued_hub(pod_type xid) const;

  ///
  /// True if this space contains an id xid equivalent to xhub_id in
  /// the hub id space.
  ///
  virtual bool contains(pod_type xid, pod_type xhub_id) const;

  using index_space_handle::pod;

  ///
  /// The pod index in this space equivalent to xid in the hub id space.
  ///
  virtual pod_type pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  virtual pod_type unglued_hub_pod(pod_type xid) const;

  ///
  /// The pod index in the hub id space equivalent to xid in this id space.
  /// synonym for unglued_hub_pod(xid).
  ///
  virtual pod_type glued_hub_pod(pod_type xid) const;

  ///
  /// True if this id space should be written to disk.
  ///
  virtual bool is_persistent() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name PRODUCT STRUCTURE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a new product structure for this id space by cloning the
  /// product structure, xproduct.
  ///
  virtual void new_product_structure(const abstract_product_structure& xproduct);

  ///
  /// Deletes the product structure for this id space.
  ///
  virtual void delete_product_structure();

  using index_space_handle::product_structure;

  ///
  /// The product structure for this id space (const version).
  ///
  virtual const abstract_product_structure& product_structure() const;

  ///
  /// The product structure for this id space (mutable version).
  ///
  virtual abstract_product_structure& product_structure();

  ///
  /// True if this id space has a product structure.
  ///
  virtual bool has_product_structure() const;

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
  /// True if this handle is attached to a state.
  ///
  virtual bool is_attached() const;

  using index_space_handle::attach_to;

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
  /// Detach this handle form its state, if any.
  ///
  virtual void detach();

  using index_space_handle::conforms_to_state;

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
  void attach_to(explicit_index_space_state* xstate);

  ///
  /// True if this conforms to the iterator type required by the
  /// explicit id space state xstate.
  ///
  virtual bool conforms_to_state(explicit_index_space_state* xstate) const;

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
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space handle from the handle pool.
  ///
  virtual index_space_handle& get_id_space() const;

  ///
  /// Returns this id space handle to the handle pool.
  ///
  virtual void release_id_space() const;

  ///
  /// True if and only if this id space handle was allocated by
  /// the handle pool.
  ///
  virtual bool allocated_id_space() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ITERATOR POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space iterator from the iterator pool.
  ///
  virtual index_space_iterator& get_iterator() const;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  virtual void release_iterator(index_space_iterator& xitr) const;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the iterator pool.
  ///
  virtual bool allocated_iterator(const index_space_iterator& xitr) const;

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
 
} // end namespace sheaf

#endif // ifndef EXPLICIT_INDEX_SPACE_HANDLE_H
