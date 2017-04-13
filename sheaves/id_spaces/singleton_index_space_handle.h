
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
/// Interface for class singleton_index_space_handle

#ifndef SINGLETON_INDEX_SPACE_HANDLE_H
#define SINGLETON_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_HANDLE_H
#include "SheafSystem/explicit_index_space_handle.h"
#endif

namespace sheaf
{

class singleton_index_space_state;
  
///
/// An implementation of class explicit_index_space_handle that has
/// a singleton id space state.
///
class SHEAF_DLL_SPEC singleton_index_space_handle : public explicit_index_space_handle
{

  friend class singleton_index_space_state;

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new singleton id space in the id space family xid_space
  /// with name xname and hub id xhub_id.
  /// Returns a handle to the id space created.
  ///
  static singleton_index_space_handle new_space(index_space_family& xid_spaces,
						const std::string& xname,
						pod_type xhub_id);

protected:

private:

  //@}


  // ===========================================================
  /// @name SINGLETON_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  singleton_index_space_handle();

  ///
  /// Copy constructor
  ///
  singleton_index_space_handle(const singleton_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  singleton_index_space_handle(const index_space_family& xid_spaces,
			       pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  singleton_index_space_handle(const index_space_family& xid_spaces,
			       const std::string& xname);

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  singleton_index_space_handle& operator=(const singleton_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~singleton_index_space_handle();

protected:

  ///
  /// Constructor: Attach to state xstate.
  ///
  singleton_index_space_handle(singleton_index_space_state& xstate);

  using explicit_index_space_handle::state;

  ///
  /// The singleton id space state (mutable version).
  ///
  singleton_index_space_state& state();

  ///
  /// The singleton id space state (const version).
  ///
  const singleton_index_space_state& state() const;

private:

  //@}


  // ===========================================================
  /// @name SINGLETON INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The hub id of the singleton id.
  ///
  pod_type hub_id() const;

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
  virtual singleton_index_space_handle& operator=(const index_space_handle& xother);

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual singleton_index_space_handle* clone() const;

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

#endif // ifndef SINGLETON_INDEX_SPACE_HANDLE_H
