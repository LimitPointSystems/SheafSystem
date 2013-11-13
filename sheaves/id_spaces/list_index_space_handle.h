
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
/// Interface for class list_index_space_handle

#ifndef LIST_INDEX_SPACE_HANDLE_H
#define LIST_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_HANDLE_H
#include "mutable_index_space_handle.h"
#endif

namespace sheaf
{

class list_index_space_state;
  
///
/// An map implementation of class mutable_index_space_handle.
/// This representation is intended to efficiently represent
/// id spaces that are positive and dense, that is, the domain
/// ids are in the domain (~0, ~end()).  This representation is optimized
/// for sequential access and will have a linear asymptotic performance
/// in both time and storage for random access lookup and insertion
/// respectively.
///
class SHEAF_DLL_SPEC list_index_space_handle : public mutable_index_space_handle
{

  friend class list_index_space_state;

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new list id space in the id space family xid_space
  /// with name xname, and persistence xis_persistent.
  /// Returns a handle to the id space created.
  ///
  static list_index_space_handle new_space(index_space_family& xid_spaces,
					   const string& xname,
					   bool xis_persistent);

protected:

private:

  //@}


  // ===========================================================
  /// @name LIST_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  list_index_space_handle();

  ///
  /// Copy constructor
  ///
  list_index_space_handle(const list_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  list_index_space_handle(const index_space_family& xid_spaces,
			  pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  list_index_space_handle(const index_space_family& xid_spaces,
			  const string& xname);

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  list_index_space_handle& operator=(const list_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~list_index_space_handle();

protected:

  ///
  /// Constructor: Attach to state xstate.
  ///
  list_index_space_handle(list_index_space_state& xstate);

  using mutable_index_space_handle::state;

  ///
  /// The list id space state (mutable version).
  ///
  list_index_space_state& state();

  ///
  /// The list id space state (const version).
  ///
  const list_index_space_state& state() const;

private:

  //@}


  // ===========================================================
  /// @name MUTABLE INDEX SPACE FACET
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
  virtual list_index_space_handle& operator=(const index_space_handle& xother);

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual list_index_space_handle* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using mutable_index_space_handle::conforms_to_state;

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

#endif // ifndef LIST_INDEX_SPACE_HANDLE_H
