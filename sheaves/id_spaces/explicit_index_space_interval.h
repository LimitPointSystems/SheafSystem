
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
/// Interface for class explicit_index_space_interval

#ifndef EXPLICIT_INDEX_SPACE_INTERVAL_H
#define EXPLICIT_INDEX_SPACE_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef INDEX_SPACE_INTERVAL_H
#include "SheafSystem/index_space_interval.h"
#endif

#ifndef AUTO_BLOCK_H
#include "SheafSystem/auto_block.h"
#endif

namespace sheaf
{

class index_space_handle;

///
/// An implementation of index_space_interval for an interval of
/// explicit id spaces.
///
class SHEAF_DLL_SPEC explicit_index_space_interval : public index_space_interval
{

  friend class namespace_poset;
  friend SHEAF_DLL_SPEC size_t deep_size(const explicit_index_space_interval& xn, bool xinclude_shallow);

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new interval of id spaces for explicit id spaces
  /// in the id space family xid_spaces with upper bound xub.
  /// Return a reference to the id space interval.
  ///
  static const explicit_index_space_interval& new_space(index_space_family& xid_spaces,
							size_type xub);

protected:

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor
  ///
  virtual ~explicit_index_space_interval();

  ///
  /// Insert the explicit id space xid_space into this interval.
  ///
  void insert(explicit_index_space_state& xid_space);

protected:

  ///
  /// Type of the explicit state block.
  ///
  typedef auto_block<explicit_index_space_state*,
		     zero_block_initialization_policy<explicit_index_space_state*> > explicit_states_type;

  ///
  /// Default constructor
  ///
  explicit_index_space_interval();

  ///
  /// Copy constructor; disabled.
  ///
  explicit_index_space_interval(const explicit_index_space_interval& xother) { };

  ///
  /// The block of explicit_index_space_state.
  ///
  explicit_states_type _states;

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// True, if this interval supports persistent id spaces.
  ///
  virtual bool supports_persistent_id_spaces() const;

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
  virtual explicit_index_space_interval* clone() const;

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
  /// True if this collection contains the id space with local id xlocal_id.
  ///
  virtual bool contains(pod_type xlocal_id) const;

  ///
  /// True if this collection contains the id space with family id xspace_id.
  ///
  virtual bool contains_family(pod_type xspace_id) const;

  ///
  /// The deep size of this.
  ///
  virtual size_type deep_size(bool xinclude_shallow) const;

protected:

  ///
  /// Assignment operator
  ///
  virtual explicit_index_space_interval& operator=(const index_space_collection& xother);

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
/// The deep size of explicit_index_space_interval& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const explicit_index_space_interval& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef EXPLICIT_INDEX_SPACE_INTERVAL_H
