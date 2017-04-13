
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
/// Interface for class scattered_insertion_index_space_handle

#ifndef SCATTERED_INSERTION_INDEX_SPACE_HANDLE_H
#define SCATTERED_INSERTION_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef GATHERED_INSERTION_INDEX_SPACE_HANDLE_H
#include "SheafSystem/gathered_insertion_index_space_handle.h"
#endif

namespace sheaf
{

class scattered_insertion_index_space_state;
  
///
/// A handle for a scattered_insertion_index_space_state.
///
class SHEAF_DLL_SPEC scattered_insertion_index_space_handle : public gathered_insertion_index_space_handle
{

  friend class scattered_insertion_index_space_state;
  friend class id_space_names_record;

  // ===========================================================
  /// @name SCATTERED_INSERTION_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  scattered_insertion_index_space_handle();

  ///
  /// Copy constructor
  ///
  scattered_insertion_index_space_handle(const scattered_insertion_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  scattered_insertion_index_space_handle(const index_space_family& xid_spaces, pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  scattered_insertion_index_space_handle(const index_space_family& xid_spaces, const std::string& xname);

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  scattered_insertion_index_space_handle& operator=(const scattered_insertion_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~scattered_insertion_index_space_handle();

protected:

  using gathered_insertion_index_space_handle::state;

  ///
  /// The mutable id space state (mutable version).
  ///
  scattered_insertion_index_space_state& state();

  ///
  /// The mutable id space state (const version).
  ///
  const scattered_insertion_index_space_state& state() const;

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

protected:

private:

  //@}

  // ===========================================================
  /// @name GATHERED_INSERTION_INDEX_SPACE_HANDLE FACET
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
  virtual scattered_insertion_index_space_handle& operator=(const index_space_handle& xother);

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual scattered_insertion_index_space_handle* clone() const;

protected:

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
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using gathered_insertion_index_space_handle::conforms_to_state;

  ///
  /// True if this conforms to the handle type required by the state
  /// with local scope id xlocal_id in the host id space collection xhost.
  ///
  virtual bool conforms_to_state(const index_space_collection& xhost, pod_type xlocal_id) const;

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
/// The deep size of scattered_insertion_index_space_handle& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const scattered_insertion_index_space_handle& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef SCATTERED_INSERTION_INDEX_SPACE_HANDLE_H
