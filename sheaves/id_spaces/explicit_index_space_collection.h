
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
/// Interface for class explicit_index_space_collection

#ifndef EXPLICIT_INDEX_SPACE_COLLECTION_H
#define EXPLICIT_INDEX_SPACE_COLLECTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef INDEX_SPACE_COLLECTION_H
#include "index_space_collection.h"
#endif

#ifndef STD_UNORDERED_MAP_H
#include "std_unordered_map.h"
#endif

namespace sheaf
{

//class arg_list;
  
///
/// An implementation of index_space_collection for a sparse collection
/// of explicit id spaces.
///
class SHEAF_DLL_SPEC explicit_index_space_collection : public index_space_collection
{
  friend class index_space_family;

  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_COLLECTION FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an arg list for constructing an instance of this.
  ///
  //static arg_list make_arg_list(pod_type xcapacity);

  ///
  /// Destructor
  ///
  virtual ~explicit_index_space_collection();

  ///
  /// The capacity of this collection.
  ///
  size_type capacity() const;

  ///
  /// Insert the explicit id space xid_space into this interval.
  ///
  void insert(explicit_index_space_state& xid_space);

protected:

  ///
  /// Default constructor
  ///
  explicit_index_space_collection();

  ///
  /// Copy constructor; disabled.
  ///
  explicit_index_space_collection(const explicit_index_space_collection& xother) { };

  ///
  /// The type of explicit id space map.
  ///
  typedef unordered::unordered_map<pod_type, explicit_index_space_state*> map_type;

  ///
  /// The map from space id to explicit id space.
  ///
  map_type _states;

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_COLLECTION FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_collection& xother) const;

  ///
  /// True if this collection contains the id space with local id xlocal_id.
  ///
  virtual bool contains(pod_type xlocal_id) const;

  ///
  /// True if this collection contains the id space with family id xspace_id.
  ///
  virtual bool contains_family(pod_type xspace_id) const;

  ///
  /// Id relative to this collection equivalent to the id space family id xspace_id.
  ///
  virtual pod_type local_scope(pod_type xspace_id) const;

  ///
  /// Id relative to the id space family equivalent to the local id xlocal_id.
  ///
  virtual pod_type family_scope(pod_type xlocal_id) const;

protected:

  ///
  /// Assignment operator
  ///
  virtual explicit_index_space_collection& operator=(const index_space_collection& xother);

  ///
  /// The explicit id space state for id xlocal_id.
  /// Returns null if there is no explicit id space for xlocal_id.
  ///
  virtual explicit_index_space_state* explicit_state(pod_type xlocal_id) const;

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
  /// Remove the id space with id xlocal_id.
  ///
  virtual void remove(pod_type xlocal_id);

  ///
  /// The number of members for the id space with id xlocal_id.
  ///
  virtual size_type ct(pod_type xlocal_id) const;

  ///
  /// Beginning id of the space with id xlocal_id.
  ///
  virtual pod_type begin(pod_type xlocal_id) const;

  ///
  /// Ending id of the space with id xlocal_id.
  ///
  virtual pod_type end(pod_type xlocal_id) const;

  ///
  /// True if the space with id xlocal_id contains id xid.
  ///
  virtual bool contains(pod_type xlocal_id, pod_type xid) const;

  ///
  /// True if the space with id xlocal_id contains an id equivalent
  /// to xid in the unglued hub id space.
  ///
  virtual bool contains_unglued_hub(pod_type xlocal_id, pod_type xid) const;

  ///
  /// True if the space with id xlocal_id contains an id xid equivalent
  /// to xhub_id in the hub id space.
  ///
  virtual bool contains(pod_type xlocal_id, pod_type xid, pod_type xhub_id) const;

  ///
  /// The pod index in the space with id xlocal_id equivalent to
  /// xid in the hub id space.
  ///
  virtual pod_type pod(pod_type xlocal_id, pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in the id space
  /// with id xlocal_id.
  ///
  virtual pod_type unglued_hub_pod(pod_type xlocal_id, pod_type xid) const;

  ///
  /// True if the id space with id xlocal_id should be written to disk.
  ///
  virtual bool is_persistent(pod_type xlocal_id) const;

protected:

  ///
  /// The index space family of this collection.
  ///
  index_space_family* _id_spaces;

private:

  //@}


  // ===========================================================
  /// @name PRODUCT STRUCTURE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a new product structure for the id space with id xlocal_id
  /// by cloning the product structure, xproduct.
  ///
  virtual void new_product_structure(pod_type xlocal_id,
				     const abstract_product_structure& xproduct);

  ///
  /// Deletes the product structure for the id space with id xlocal_id.
  ///
  virtual void delete_product_structure(pod_type xlocal_id);

  ///
  /// The product structure for the id space with id xlocal_id (const version).
  ///
  virtual const abstract_product_structure& product_structure(pod_type xlocal_id) const;

  ///
  /// The product structure for the id space with id xlocal_id (mutable version).
  ///
  virtual abstract_product_structure& product_structure(pod_type xlocal_id);

  ///
  /// True if the id space with id xlocal_id has a product structure.
  ///
  virtual bool has_product_structure(pod_type xlocal_id) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space handle from the handle pool attached to state
  /// with id xlocal_id.
  ///
  virtual index_space_handle& get_id_space(pod_type xlocal_id) const;

  ///
  /// Returns the id space handle xid_space to the handle pool.
  ///
  virtual void release_id_space(index_space_handle& xid_space) const;

  ///
  /// True if and only if id space handle xid_space was allocated by
  /// the handle pool.
  ///
  virtual bool allocated_id_space(const index_space_handle& xid_space) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ITERATOR POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space iterator from the iterator pool attached
  /// to state with id xlocal_id.
  ///
  virtual index_space_iterator& get_id_space_iterator(pod_type xlocal_id) const;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  virtual void release_id_space_iterator(index_space_iterator& xitr) const;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the iterator pool.
  ///
  virtual bool allocated_id_space_iterator(const index_space_iterator& xitr) const;

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
/// The deep size of explicit_index_space_collection& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const explicit_index_space_collection& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef EXPLICIT_INDEX_SPACE_COLLECTION_H
