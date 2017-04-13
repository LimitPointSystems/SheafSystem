
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
/// Interface for class array_index_space_interval

#ifndef ARRAY_INDEX_SPACE_INTERVAL_H
#define ARRAY_INDEX_SPACE_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef FORWARDING_INDEX_SPACE_HANDLE_H
#include "SheafSystem/forwarding_index_space_handle.h"
#endif

#ifndef INDEX_SPACE_INTERVAL_H
#include "SheafSystem/index_space_interval.h"
#endif

#ifndef BLOCK_H
#include "SheafSystem/block.h"
#endif

#ifndef LIST_POOL_H
#include "SheafSystem/list_pool.h"
#endif

#ifndef STD_UNORDERED_MAP_H
#include "SheafSystem/std_unordered_map.h"
#endif

namespace sheaf
{

class array_implicit_index_space_iterator;
class index_space_handle;

///
/// An implementation of index_space_interval for an interval of implicit
/// id spaces in which the hub ids are stored in a two dimensional array.
///
class SHEAF_DLL_SPEC array_index_space_interval : public index_space_interval
{

  friend class namespace_poset;
  friend SHEAF_DLL_SPEC size_t deep_size(const array_index_space_interval& xn, bool xinclude_shallow);

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new interval of id spaces with an array representation
  /// in the id space family xid_spaces with upper bound xub,
  /// hub id array xhub_ids, the number of ids per space xids_per_space
  /// and ownership mode xowns_hub_ids.
  /// Return a reference to the id space interval.
  ///
  static const array_index_space_interval& new_space(index_space_family& xid_spaces,
						     size_type xub,
						     block<pod_type>& xhub_ids,
						     size_type xids_per_space,
						     bool xowns_hub_ids);

protected:

private:

  //@}


  // ===========================================================
  /// @name ARRAY_INDEX_SPACE_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor
  ///
  virtual ~array_index_space_interval();

  ///
  /// The array of hub ids.
  ///
  const block<pod_type>& hub_ids() const;

  ///
  /// The number of ids per id space.
  ///
  size_type ids_per_space() const;

  ///
  /// True if this interval owns the array of hub ids.  If owns_hub_ids(),
  /// this interval is responsible for the memory management of hub_ids().
  /// Otherwise, the user is response for the memory management.
  ///
  bool owns_hub_ids() const;

protected:

  /// Default constructor
  ///
  array_index_space_interval();

  ///
  /// Copy constructor; disabled.
  ///
  array_index_space_interval(const array_index_space_interval& xother) { };

  ///
  /// The array of hub ids.
  ///
  block<pod_type>* _hub_ids;

  ///
  /// The number of ids per id space.
  ///
  size_type _ids_per_space;

  ///
  /// True if this interval is responsible for the memory management
  /// of _hub_ids.
  ///
  bool _owns_hub_ids;

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@}

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// Virtual constructor; create a new instance of the same type at this.
  ///
  virtual array_index_space_interval* clone() const;

protected:

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

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
  /// The deep size of this.
  ///
  virtual size_type deep_size(bool xinclude_shallow) const;

protected:

  ///
  /// Assignment operator
  ///
  virtual array_index_space_interval& operator=(const index_space_collection& xother);

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
  /// Remove the id space with id xlocal_id.
  ///
  virtual void remove(pod_type xlocal_id);

  ///
  /// The number of members for the id space with id xlocal_id.
  ///
  virtual size_type ct(pod_type xlocal_id) const;

  using index_space_interval::begin;

  ///
  /// Beginning id of the space with id xlocal_id.
  ///
  virtual pod_type begin(pod_type xlocal_id) const;

  using index_space_interval::end;

  ///
  /// Ending id of the space with id xlocal_id.
  ///
  virtual pod_type end(pod_type xlocal_id) const;

  using index_space_interval::contains;

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

  ///
  /// The handle pool.
  ///
  mutable list_pool<forwarding_index_space_handle> _handles;

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

  ///
  /// The iterator pool.
  ///
  mutable list_pool<array_implicit_index_space_iterator> _iterators;

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
/// The deep size of array_index_space_interval& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const array_index_space_interval& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef ARRAY_INDEX_SPACE_INTERVAL_H
