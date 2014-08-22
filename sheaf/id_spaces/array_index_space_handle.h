
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
/// Interface for class array_index_space_handle

#ifndef COM_LIMITPOINT_SHEAF_ARRAY_INDEX_SPACE_HANDLE_H
#define COM_LIMITPOINT_SHEAF_ARRAY_INDEX_SPACE_HANDLE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_MUTABLE_INDEX_SPACE_HANDLE_H
#include "ComLimitPoint/sheaf/mutable_index_space_handle.h"
#endif

namespace sheaf
{

class array_index_space_state;
  
///
/// An array implementation of class mutable_index_space_handle.
/// This representation is intended to efficiently represent
/// id spaces that are positive and dense, that is, the domain
/// ids are in the domain (~0, ~end()) and hence the id to hub id
/// map can be efficiently stored in an array. In particular it is intended
/// for id spaces used to index arrays, in which case the ids
/// are in the domain [0, end()).
///
class SHEAF_DLL_SPEC array_index_space_handle : public mutable_index_space_handle
{

  friend class array_index_space_state;

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new array id space in the id space family xid_space
  /// with name xname, persistence xis_persistent, and capacity xcapacity..
  /// Returns a handle to the id space created.
  ///
  static array_index_space_handle new_space(index_space_family& xid_spaces,
					     const std::string& xname,
					     bool xis_persistent,
					     size_type xcapacity);

protected:

private:

  //@}


  // ===========================================================
  /// @name ARRAY_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  array_index_space_handle();

  ///
  /// Copy constructor
  ///
  array_index_space_handle(const array_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  array_index_space_handle(const index_space_family& xid_spaces,
			   pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  array_index_space_handle(const index_space_family& xid_spaces,
			   const std::string& xname);

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  array_index_space_handle& operator=(const array_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~array_index_space_handle();

protected:

  ///
  /// Constructor: Attach to state xstate.
  ///
  array_index_space_handle(array_index_space_state& xstate);

  using mutable_index_space_handle::state;

  ///
  /// The array id space state (mutable version).
  ///
  array_index_space_state& state();

  ///
  /// The array id space state (const version).
  ///
  const array_index_space_state& state() const;

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
  virtual array_index_space_handle& operator=(const index_space_handle& xother);

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual array_index_space_handle* clone() const;

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

#endif // ifndef ARRAY_INDEX_SPACE_HANDLE_H
