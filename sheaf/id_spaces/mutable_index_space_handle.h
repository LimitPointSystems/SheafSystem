
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
/// Interface for class mutable_index_space_handle

#ifndef COM_LIMITPOINT_SHEAF_MUTABLE_INDEX_SPACE_HANDLE_H
#define COM_LIMITPOINT_SHEAF_MUTABLE_INDEX_SPACE_HANDLE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_EXPLICIT_INDEX_SPACE_HANDLE_H
#include "ComLimitPoint/sheaf/explicit_index_space_handle.h"
#endif

namespace sheaf
{

class mutable_index_space_state;
  
///
/// An implementation of class explicit_index_space_handle that has
/// a mutable id space state.
///
class SHEAF_DLL_SPEC mutable_index_space_handle : public explicit_index_space_handle
{

  friend class mutable_index_space_state;
  friend class id_space_names_record;

  // ===========================================================
  /// @name MUTABLE_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  mutable_index_space_handle();

  ///
  /// Copy constructor
  ///
  mutable_index_space_handle(const mutable_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  mutable_index_space_handle(const index_space_family& xid_spaces,
			     pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  mutable_index_space_handle(const index_space_family& xid_spaces,
			     const std::string& xname);

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  mutable_index_space_handle& operator=(const mutable_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~mutable_index_space_handle();

protected:

  using explicit_index_space_handle::state;

  ///
  /// The mutable id space state (mutable version).
  ///
  mutable_index_space_state& state();

  ///
  /// The mutable id space state (const version).
  ///
  const mutable_index_space_state& state() const;

private:

  //@}


  // ===========================================================
  /// @name MUTABLE INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make id xid in this id space equivalent to xhub_id in the hub id space.
  /// synonym for insert(xid, xhub_id.hub_pod()).
  ///
  void insert(pod_type xid, const scoped_index& xhub_id);

  ///
  /// Make id xid in this id space equivalent to xhub_id in the hub id space.
  ///
  void insert(pod_type xid, pod_type xhub_id);

  ///
  /// Make the next id in this space equivalent to xhub_id in the hub id space.
  /// synonym for push_back(xhub_id.hub_pod()).
  ///
  void push_back(const scoped_index& xhub_id);

  ///
  /// Make the next id in this space equivalent to xhub_id in the hub id space.
  ///
  void push_back(pod_type xid);

  ///
  /// Makes id xitr.id() in this id space equivalent to xhub_id in the hub
  /// id space.  Increments all ids greater than xitr.id() if any by one.
  /// Xitr will be set to the entry with id, xitr.id()+1.
  /// synonym for push(xitr, xhub_id.pod()).
  ///
  void push(index_space_iterator& xitr, const scoped_index& xhub_id);

  ///
  /// Makes id xitr.id() in this id space equivalent to xhub_id in the hub
  /// id space.  Increments all ids greater than xitr.id() if any by one.
  /// Xitr will be set to the entry with id, xitr.id()+1.
  ///
  void push(index_space_iterator& xitr, pod_type xhub_id);

  ///
  /// The id inserted by the next call to push_back.
  ///
  pod_type next_id() const;

  ///
  /// Removes the equivalence associated with xid.hub_pod().
  /// synonym for remove_hub(xid.hub_pod(), xupdate_extrema).
  /// Returns the number of entries actually removed, either 0 or 1.
  ///
  size_type remove(const scoped_index& xid, bool update_extrema);

  ///
  /// Removes the equivalence associated with id xid.
  /// Returns the number of entries actually removed, either 0 or 1.
  ///
  size_type remove(pod_type xid, bool update_extrema);

  ///
  /// Removes the equivalence associated with hub id xhub_id.
  /// Returns the number of entries actually removed, either 0 or 1.
  ///
  size_type remove_hub(pod_type xhub_id, bool update_extrema);

  ///
  /// Removes the equivalence associated with id xitr.pod().
  /// Increments xitr to the next entry if any.
  ///
  void remove(index_space_iterator& xitr, bool update_extrema);

  ///
  /// Gathers this id space into an interval.
  ///
  void gather();
  
  ///
  /// Update the id extrema.
  ///
  void update_extrema();

  ///
  /// Reserve enough memory for xcapacity number of ids.
  ///
  void reserve(size_type xcapacity);

  ///
  /// The number of ids reserved in memory.
  ///
  size_type capacity() const;

  ///
  /// Delete all ids.
  ///
  void clear();

protected:

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

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
  virtual mutable_index_space_handle& operator=(const index_space_handle& xother);

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual mutable_index_space_handle* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Set if this id space should be written to disk.
  ///
  void put_is_persistent(bool xis_persistent);

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using explicit_index_space_handle::conforms_to_state;

  ///
  /// True if this conforms to the handle type required by the state
  /// with local scope id xlocal_id in the host id space collection xhost.
  ///
  virtual bool conforms_to_state(const index_space_collection& xhost,
				 pod_type xlocal_id) const;

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
/// The deep size of mutable_index_space_handle& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const mutable_index_space_handle& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef MUTABLE_INDEX_SPACE_HANDLE_H
