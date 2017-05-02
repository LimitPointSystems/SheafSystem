
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
/// Interface for class primary_index_space_state.

#ifndef PRIMARY_INDEX_SPACE_STATE_H
#define PRIMARY_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef LIST_POOL_H
#include "SheafSystem/list_pool.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_STATE_H
#include "SheafSystem/explicit_index_space_state.h"
#endif

namespace sheaf
{

class primary_index_space_handle;
class primary_index_space_iterator;

///
/// A computed implementation class explicit_index_space_state that is used for
/// the terms of the primary sum id space.
///
/// This representation assumes the ids are an open gathered set of ids.
/// The equivalence between the ids in this space and the hub id space
/// is computed using an offset.
///
class SHEAF_DLL_SPEC primary_index_space_state : public explicit_index_space_state
{
  friend class namespace_poset;
  friend class primary_index_space_handle;

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new primary id space in the id space family xid_space
  /// at the next available id space index with name xname,
  /// ooffset xoffset and count xct.
  /// Returns a handle to the id space created.
  ///
  static primary_index_space_handle new_space(index_space_family& xid_spaces,
					     const std::string& xname,
					     pod_type xoffset,
					     size_type xct);

  ///
  /// Create a new primary id space in the id space family xid_space
  /// at the id space index xid with name xname, offset xoffset and count xct.
  /// Returns a handle to the id space created.
  ///
  static primary_index_space_handle new_space(index_space_family& xid_spaces,
					     pod_type xid,
					     const std::string& xname,
					     pod_type xoffset,
					     size_type xct);

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIMARY_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Default constructor
  ///
  primary_index_space_state();

  ///
  /// Copy constructor; disabled.
  ///
  primary_index_space_state(const primary_index_space_state& xother) { };

  ///
  /// Destructor
  ///
  virtual ~primary_index_space_state();

private:

  //@}


  // ===========================================================
  /// @name PRIMARY INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The offset into the hub id space.
  ///
  pod_type offset() const;

  ///
  /// Extend this id space to have ct() == xct.
  ///
  virtual void extend(size_type xct);

  ///
  /// The term id of this in the hub id space.
  ///
  pod_type hub_term_id() const;

protected:

  ///
  /// Sets hub_term_id() to xhub_term_id.
  ///
  void put_hub_term_id(pod_type xhub_term_id);

  ///
  /// The offset into the hub id space.
  ///
  pod_type _offset;

  ///
  /// The term id of this in the hub id space.
  ///
  pod_type _hub_term_id;

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const explicit_index_space_state& xother) const;

  ///
  /// The deep size of this.
  ///
  virtual size_type deep_size(bool xinclude_shallow) const;

protected:

  ///
  /// Assignment operator
  ///
  virtual primary_index_space_state& operator=(const explicit_index_space_state& xother);

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this space contains id xid.
  ///
  virtual bool contains(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  ///
  virtual bool contains_unglued_hub(pod_type xid) const;

  ///
  /// The pod index in this space equivalent to xid in the hub id space.
  ///
  virtual pod_type pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  virtual pod_type unglued_hub_pod(pod_type xid) const;

  /// @todo Address.
//   ///
//   /// The pod index in the primary sum id space equivalent to xid in this id space.
//   ///
//   virtual pod_type primary_sum_pod(pod_type xid) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of handles in the pool.
  ///
  static size_type handle_pool_ct();

  ///
  /// The deep size of the handle pool.
  ///
  static size_type handle_pool_deep_size();

  ///
  /// Allocates an id space handle from the handle pool.
  ///
  virtual index_space_handle& get_id_space() const;

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

  ///
  /// The handle pool.
  ///
  static list_pool<primary_index_space_handle>& handles();

  //@}


  // ===========================================================
  /// @name ITERATOR POOL ACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of iterators in the pool.
  ///
  static size_type iterator_pool_ct();

  ///
  /// The deep size of the iterator pool.
  ///
  static size_type iterator_pool_deep_size();

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

  ///
  /// The iterator pool.
  ///
  static list_pool<primary_index_space_iterator>& iterators();

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
  virtual primary_index_space_state* clone() const;

protected:

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

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
/// The deep size of primary_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const primary_index_space_state& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef PRIMARY_INDEX_SPACE_STATE_H
