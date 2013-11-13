
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
/// Interface for class reserved_primary_index_space_handle

#ifndef RESERVED_PRIMARY_INDEX_SPACE_HANDLE_H
#define RESERVED_PRIMARY_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef PRIMARY_INDEX_SPACE_HANDLE_H
#include "primary_index_space_handle.h"
#endif

namespace sheaf
{

class reserved_primary_index_space_state;
  
///
/// An implementation of class primary_index_space_handle that has
/// a reserved primary id space state.
///
class SHEAF_DLL_SPEC reserved_primary_index_space_handle : public primary_index_space_handle
{

  friend class reserved_primary_index_space_state;

  // ===========================================================
  /// @name RESERVED_PRIMARY_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  reserved_primary_index_space_handle();

  ///
  /// Copy constructor
  ///
  reserved_primary_index_space_handle(const reserved_primary_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  reserved_primary_index_space_handle(const index_space_family& xid_spaces,
				      pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  reserved_primary_index_space_handle(const index_space_family& xid_spaces,
				      const string& xname);

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  reserved_primary_index_space_handle& operator=(const reserved_primary_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~reserved_primary_index_space_handle();

protected:

  ///
  /// Constructor: Attach to state xstate.
  ///
  reserved_primary_index_space_handle(reserved_primary_index_space_state& xstate);

  using primary_index_space_handle::state;

  ///
  /// The reserved primary id space state (mutable version).
  ///
  reserved_primary_index_space_state& state();

  ///
  /// The reserved primary id space state (const version).
  ///
  const reserved_primary_index_space_state& state() const;

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

private:

  //@}


  // ===========================================================
  /// @name PRIMARY_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

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
  virtual reserved_primary_index_space_handle& operator=(const index_space_handle& xother);

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual reserved_primary_index_space_handle* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using primary_index_space_handle::conforms_to_state;

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
 
} // end namespace sheaf

#endif // ifndef RESERVED_PRIMARY_INDEX_SPACE_HANDLE_H
