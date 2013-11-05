
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
/// Interface for class primary_index_space_handle

#ifndef PRIMARY_INDEX_SPACE_HANDLE_H
#define PRIMARY_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_HANDLE_H
#include "explicit_index_space_handle.h"
#endif

namespace sheaf
{

class primary_index_space_state;
  
///
/// An implementation of class explicit_index_space_handle that has
/// a primary id space state.
///
class SHEAF_DLL_SPEC primary_index_space_handle : public explicit_index_space_handle
{

  friend class primary_index_space_state;
  friend class primary_sum_index_space_state;

  // ===========================================================
  /// @name PRIMARY_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  primary_index_space_handle();

  ///
  /// Copy constructor
  ///
  primary_index_space_handle(const primary_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  primary_index_space_handle(const index_space_family& xid_spaces,
			     pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  primary_index_space_handle(const index_space_family& xid_spaces,
			     const string& xname);

  ///
  /// Assignment operator.
  ///
  primary_index_space_handle& operator=(const primary_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~primary_index_space_handle();

protected:

  ///
  /// Constructor: Attach to state xstate.
  ///
  primary_index_space_handle(primary_index_space_state& xstate);

  using explicit_index_space_handle::state;

  ///
  /// The primary id space state (mutable version).
  ///
  primary_index_space_state& state();

  ///
  /// The primary id space state (const version).
  ///
  const primary_index_space_state& state() const;

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
  void extend(size_type xct);

  ///
  /// The term id of this in the hub id space.
  ///
  pod_type hub_term_id() const;

protected:

  ///
  /// Sets hub_term_id() to xhub_term_id.
  ///
  void put_hub_term_id(pod_type xhub_term_id);

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
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual primary_index_space_handle* clone() const;

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
 
} // end namespace sheaf

#endif // ifndef PRIMARY_INDEX_SPACE_HANDLE_H
