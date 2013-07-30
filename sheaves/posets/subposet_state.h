

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Interface for class subposet_state.

#ifndef SUBPOSET_STATE_H
#define SUBPOSET_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef DOF_DESCRIPTOR_ARRAY_H
#include "dof_descriptor_array.h"
#endif

#ifndef INDEX_SPACE_FAMILY_H
#include "index_space_family.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_HANDLE_H
#include "mutable_index_space_handle.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif

namespace sheaf
{

template <typename T>
class block;

///
/// The data structure representing the state of a subposet.
///
class SHEAF_DLL_SPEC subposet_state
{
  // ===========================================================
  /// @name SUBPOSET_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  subposet_state();

  ///
  /// Destructor.
  ///
  ~subposet_state();

  ///
  /// Initialize data members.
  ///
  void initialize(int xmember_ub, const scoped_index& xindex, bool xinitialize);

  ///
  /// Initialize data members to xmembers.
  ///
  void initialize(int xmember_ub,
		  const scoped_index& xindex,
                  const block<pod_index_type>& xmembers);

  ///
  /// Initialize data members to xmembers.
  ///
  void initialize(int xmember_ub,
                  const scoped_index& xindex,
                  const block<scoped_index>& xmembers);

  ///
  /// True, if this is initialized
  ///
  bool is_initialized() const;

  ///
  /// Set all data members to NULL
  ///
  void terminate();

  ///
  /// True, if this is teminated
  ///
  bool is_terminated() const;

  ///
  /// Get the next member in free list
  ///
  const scoped_index& next() const;

  ///
  /// Put the next member in free list
  ///
  void put_next(const scoped_index& xnext);

  ///
  /// Get the members of the subposet
  ///
  zn_to_bool* members() const;

  ///
  /// Put members of the subposet
  ///
  void put_members(const zn_to_bool* xmembers);

  ///
  /// Get index of the subposet
  ///
  const scoped_index& index() const;

  ///
  /// True, if this is a dofs subposet
  ///
  bool is_dof_subposet() const;

  ///
  /// True, if this is a dofs subposet
  ///
  void put_is_dof_subposet(bool xis_dof_subposet);

  ///
  /// Get the number of dofs <br>
  /// Only defined if this is a dofs subposet, in which case
  /// _dof_ct == _members.ct() but is more fficient to evaluate
  ///
  size_type dof_ct() const;

  ///
  /// Put the number of dofs <br>
  /// Only defined if this is a dofs subposet, in which case
  /// _dof_ct == _members.ct() but is more fficient to evaluate
  ///
  void put_dof_ct(size_type xdof_ct);

  ///
  /// Get the upper bound of the dof tuple <br>
  /// Only defined if this is a dofs subposet
  ///
  size_type dof_tuple_ub();

  ///
  /// Get the offset of each dof when the dofs are contiguously allocated. <br>
  /// Only defined if this is a dofs subposet
  ///
  dof_descriptor_array* dof_descriptors() const;

  ///
  /// Put the offset of each dof when the dofs are contiguously allocated. <br>
  /// Only defined if this is a dofs subposet
  ///
  void put_dof_descriptors(const dof_descriptor_array* xdof_descriptors);

  ///
  /// True if this has an id space.
  ///
  bool has_id_space() const;

  ///
  /// The id space for this subposet state (const version).
  ///
  const mutable_index_space_handle& id_space() const;

  ///
  /// The id space for this subposet state (mutable version).
  ///
  mutable_index_space_handle& id_space();

  ///
  /// Put the id space for this subposet state.
  ///
  void put_id_space(const index_space_family& xid_spaces,
		    pod_index_type xid);

  ///
  /// Put the id space for this subposet state.
  ///
  void put_id_space(const index_space_family& xid_spaces,
		    const string& xname);

  ///
  /// True if this id space should be written to disk.
  ///
  bool is_persistent() const;

  ///
  /// Sets is_persistent() to xvalue.
  ///
  void put_is_persistent(bool xvalue);

protected:

  ///
  /// Characteristic function defining members of this subposet.
  ///
  zn_to_bool* _members;

  ///
  /// Index of this subposet in powerset::_member_pool
  /// also used for next().
  ///
  scoped_index _index;

  ///
  /// True if this is a dofs subposet.
  ///
  bool _is_dof_subposet;

  ///
  /// The number of dofs associated with this
  /// Only defined if this is a dofs subposet, in which case
  /// _dof_ct == _members.ct() but is more fficient to evaluate
  ///
  size_type _dof_ct;

  ///
  /// If this is a dofs subposet, the offset of each dof when the
  /// dofs are contiguously allocated.
  ///
  dof_descriptor_array* _dof_descriptors;

  ///
  /// The id space for this subposet state.
  ///
  mutable_index_space_handle* _id_space;

  ///
  /// True if and only if this subposet should be written to disk.
  ///
  bool _is_persistent;

private:

  //@}
};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert subposet_state& s into ostream& os.
///
SHEAF_DLL_SPEC
ostream & operator << (ostream &os, subposet_state& s);

///
/// The deep size of the referenced object of type subposet_state.
///
SHEAF_DLL_SPEC
size_t deep_size(const subposet_state& xp, bool xinclude_shallow = true);
 
} // namespace sheaf

#endif // ifndef SUBPOSET_STATE_H
