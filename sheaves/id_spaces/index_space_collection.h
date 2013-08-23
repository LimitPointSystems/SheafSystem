
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
/// Interface for class index_space_collection

#ifndef INDEX_SPACE_COLLECTION_H
#define INDEX_SPACE_COLLECTION_H

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

class abstract_product_structure;
class explicit_index_space_state;
class hub_index_space_handle;
class index_space_family;
class index_space_handle;
class index_space_iterator;
class scoped_index;
  
///
/// A collection of id space states.  This is a virtual class with provides
/// an interface for accessing the id space states via the collection's
/// local indexing.
///
class SHEAF_DLL_SPEC index_space_collection : public any
{

  friend class explicit_index_space_handle;
  friend class explicit_index_space_iterator;
  friend class index_space_family;

  // ===========================================================
  /// @name INDEX_SPACE_COLLECTION FACET
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
  virtual ~index_space_collection();

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_collection& xother) const = 0;

  ///
  /// True if this collection contains the id space with local id xlocal_id.
  ///
  virtual bool contains(pod_type xlocal_id) const = 0;

  ///
  /// True if this collection contains the id space with family id xspace_id.
  ///
  virtual bool contains_family(pod_type xspace_id) const = 0;

  ///
  /// Id relative to this collection equivalent to the id space family id xspace_id.
  ///
  virtual pod_type local_scope(pod_type xspace_id) const = 0;

  ///
  /// Id relative to the id space family equivalent to the local id xlocal_id.
  ///
  virtual pod_type family_scope(pod_type xlocal_id) const = 0;

  ///
  /// The deep size of this.
  ///
  virtual size_type deep_size(bool xinclude_shallow) const = 0;

protected:

  ///
  /// Default constructor
  ///
  index_space_collection();

  ///
  /// Copy constructor; disabled.
  ///
  index_space_collection(const index_space_collection& xother) { };

  ///
  /// Assignment operator
  ///
  virtual index_space_collection& operator=(const index_space_collection& xother) = 0;

  ///
  /// The explicit id space state for id xlocal_id.
  /// Returns null if there is no explicit id space for xlocal_id.
  ///
  virtual explicit_index_space_state* explicit_state(pod_type xlocal_id) const = 0;

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
  virtual const index_space_family& id_spaces() const = 0;

  ///
  /// The id space family for this (mutable version).
  ///
  virtual index_space_family& id_spaces() = 0;

  ///
  /// The hub id space.
  ///
  const hub_index_space_handle& hub_id_space() const;

  ///
  /// Remove the id space with id xlocal_id.
  ///
  virtual void remove(pod_type xlocal_id) = 0;

  ///
  /// The number of members for the id space with id xlocal_id.
  ///
  virtual size_type ct(pod_type xlocal_id) const = 0;

  ///
  /// True if there are no ids in the space with id xlocal_id.
  ///
  bool is_empty(pod_type xlocal_id) const;

  ///
  /// Beginning id of the space with id xlocal_id.
  ///
  virtual pod_type begin(pod_type xlocal_id) const = 0;

  ///
  /// Ending id of the space with id xlocal_id.
  ///
  virtual pod_type end(pod_type xlocal_id) const = 0;

  ///
  /// True if begin(xlocal_id) == 0 and end(xlocal_id) == ct(xlocal_id).
  ///
  bool is_gathered(pod_type xlocal_id) const;
    
  ///
  /// True if the space with id xlocal_id contains id xid.
  ///
  virtual bool contains(pod_type xlocal_id, pod_type xid) const = 0;

  ///
  /// True if the space with id xlocal_id contains an id equivalent to xid.
  /// synonym for contains_hub(xlocal_id, xid.hub_pod()).
  ///
  bool contains(pod_type xlocal_id, const scoped_index& xid) const;

  ///
  /// True if the space with id xlocal_id contains an id equivalent
  /// to xid in the hub id space.
  /// synonym for contains_unglued_hub(xlocal_id, xid)
  ///
  bool contains_hub(pod_type xlocal_id, pod_type xid) const;

  ///
  /// True if the space with id xlocal_id contains an id equivalent
  /// to xid in the unglued hub id space.
  ///
  virtual bool contains_unglued_hub(pod_type xlocal_id, pod_type xid) const = 0;

  ///
  /// True if the space with id xlocal_id contains an id equivalent
  /// to xid in the glued hub id space.
  ///
  bool contains_glued_hub(pod_type xlocal_id, pod_type xid) const;

  ///
  /// True if the space with id xlocal_id contains an id xid equivalent
  /// to xhub_id in the hub id space.
  /// synonym for contains(xlocal_id, xid, xhub_id.hub_pod()).
  ///
  bool contains(pod_type xlocal_id, pod_type xid, const scoped_index& xhub_id) const;

  ///
  /// True if the space with id xlocal_id contains an id xid equivalent
  /// to xhub_id in the hub id space.
  ///
  virtual bool contains(pod_type xlocal_id, pod_type xid, pod_type xhub_id) const = 0;

  ///
  /// The pod index in the space with id xlocal_id equivalent to
  /// xid in the hub id space.
  ///
  virtual pod_type pod(pod_type xlocal_id, pod_type xid) const = 0;

  ///
  /// The pod index in the space with id xlocal_id equivalent to xid.
  /// synonym for pod(xlocal_id, id.hub_pod()).
  ///
  pod_type pod(pod_type xlocal_id, const scoped_index& xid) const;

  ///
  /// The pod index in the glued hub id space equivalent to xid in the id space
  /// with id xlocal_id.
  /// synonym for unglued_hub_pod(xlocal_id, xid).
  ///
  pod_type hub_pod(pod_type xlocal_id, pod_type xid) const;

  ///
  /// The pod index in the glued hub id space equivalent to xid in the id space
  /// with id xlocal_id.
  ///
  virtual pod_type unglued_hub_pod(pod_type xlocal_id, pod_type xid) const = 0;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in the id space
  /// with id xlocal_id.
  ///
  pod_type glued_hub_pod(pod_type xlocal_id, pod_type xid) const;

  ///
  /// True if the id space with id xlocal_id should be written to disk.
  ///
  virtual bool is_persistent(pod_type xlocal_id) const = 0;

protected:

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
				     const abstract_product_structure& xproduct) = 0;

  ///
  /// Deletes the product structure for the id space with id xlocal_id.
  ///
  virtual void delete_product_structure(pod_type xlocal_id) = 0;

  ///
  /// The product structure for the id space with id xlocal_id (const version).
  ///
  virtual const abstract_product_structure& product_structure(pod_type xlocal_id) const = 0;

  ///
  /// The product structure for the id space with id xlocal_id (mutable version).
  ///
  virtual abstract_product_structure& product_structure(pod_type xlocal_id) = 0;

  ///
  /// True if the id space with id xlocal_id has a product structure.
  ///
  virtual bool has_product_structure(pod_type xlocal_id) const = 0;

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
  virtual index_space_handle& get_id_space(pod_type xlocal_id) const = 0;

  ///
  /// Returns the id space handle xid_space to the handle pool.
  ///
  virtual void release_id_space(index_space_handle& xid_space) const = 0;

  ///
  /// True if and only if id space handle xid_space was allocated by
  /// the handle pool.
  ///
  virtual bool allocated_id_space(const index_space_handle& xid_space) const = 0;

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
  virtual index_space_iterator& get_id_space_iterator(pod_type xlocal_id) const = 0;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  virtual void release_id_space_iterator(index_space_iterator& xitr) const = 0;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the iterator pool.
  ///
  virtual bool allocated_id_space_iterator(const index_space_iterator& xitr) const = 0;

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

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // end namespace sheaf

#endif // ifndef INDEX_SPACE_COLLECTION_H
