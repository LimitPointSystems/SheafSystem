
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
/// Interface for class reserved_primary_index_space_state

#ifndef RESERVED_PRIMARY_INDEX_SPACE_STATE_H
#define RESERVED_PRIMARY_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef LIST_POOL_H
#include "SheafSystem/list_pool.h"
#endif

#ifndef PRIMARY_INDEX_SPACE_STATE_H
#include "SheafSystem/primary_index_space_state.h"
#endif

namespace sheaf
{
  
class reserved_primary_index_space_handle;
class reserved_primary_index_space_iterator;

///
/// A computed implementation of abstract class primary_index_space_state.
/// This representation is used for the reserved term of the hub id space.
///
class SHEAF_DLL_SPEC reserved_primary_index_space_state : public primary_index_space_state
{

  friend class namespace_poset;

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new reserved primary id space in the id space family xid_space
  /// at the next available id space index with name xname,
  /// ooffset xoffset and count xct.
  /// Returns a handle to the id space created.
  ///
  static reserved_primary_index_space_handle new_space(index_space_family& xid_spaces,
						       const std::string& xname,
						       pod_type xoffset,
						       size_type xct);

  ///
  /// Create a new reserved primary id space in the id space family xid_space
  /// at the id space index xid with name xname, offset xoffset and count xct.
  /// Returns a handle to the id space created.
  ///
  static reserved_primary_index_space_handle new_space(index_space_family& xid_spaces,
						       pod_type xid,
						       const std::string& xname,
						       pod_type xoffset,
						       size_type xct);

protected:

private:

  //@}


  // ===========================================================
  /// @name RESERVED_PRIMARY_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Default constructor
  ///
  reserved_primary_index_space_state();

  ///
  /// Copy constructor; disabled
  ///
  reserved_primary_index_space_state(const reserved_primary_index_space_state& xother) { };

  ///
  /// Destructor
  ///
  virtual ~reserved_primary_index_space_state();

private:

  //@}


  // ===========================================================
  /// @name RESERVED PRIMARY INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocate the next available id in this space.  Returns the
  /// allocated id in the hub id space.
  ///
  pod_type new_id();

  ///
  /// Allocate the hub id xhub_id in this space.  Returns the
  /// allocated id in the hub id space.
  ///
  pod_type new_hub_id(pod_type xhub_id);

  ///
  /// The next available hub id for allocation.
  ///
  pod_type next_hub_id() const;

  ///
  /// True if and only if the next id is available for allocation.
  ///
  bool is_next_id_available() const;

  ///
  /// True if and only if the hub id xhub_id is available for allocation.
  ///
  bool is_hub_id_available(pod_type xhub_id) const;

protected:

  /// The next available hub id for allocation.
  ///
  pod_type _next_hub_id;

private:

  //@}


  // ===========================================================
  /// @name PRIMARY INDEX SPACE FACET
  // ===========================================================
  //@{

public:

protected:

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
  virtual reserved_primary_index_space_state& operator=(const explicit_index_space_state& xother);

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

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
  static list_pool<reserved_primary_index_space_handle>& handles();

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
  static list_pool<reserved_primary_index_space_iterator>& iterators();

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
  virtual reserved_primary_index_space_state* clone() const;

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
/// The deep size of reserved_primary_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const reserved_primary_index_space_state& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef RESERVED_PRIMARY_INDEX_SPACE_STATE_H
