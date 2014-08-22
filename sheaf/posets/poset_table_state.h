
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
/// Interface for class poset_table_state

#ifndef COM_LIMITPOINT_SHEAF_POSET_TABLE_STATE_H
#define COM_LIMITPOINT_SHEAF_POSET_TABLE_STATE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ANY_H
#include "ComLimitPoint/sheaf/any.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_BLOCK_H
#include "ComLimitPoint/sheaf/block.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_INDEX_SPACE_FAMILY_H
#include "ComLimitPoint/sheaf/index_space_family.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SCOPED_INDEX_H
#include "ComLimitPoint/sheaf/scoped_index.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace sheaf
{

class abstract_poset_member;
class array_poset_dof_map;
class poset_dof_map;
class poset_state_handle;
class schema_poset_member;

///
/// The data structure representing the table containing
/// the dof tuples of the members of a poset.
///
class SHEAF_DLL_SPEC poset_table_state : public any
{

  friend class poset_state_handle;
  friend class storage_agent; // needs to create id space.
  friend class poset_scaffold; // needs to create an id space.
  friend SHEAF_DLL_SPEC size_t deep_size(const poset_table_state& xp, bool xinclude_shallow);


  // ===========================================================
  /// @name POSET_TABLE_STATE FACET
  // ===========================================================
  //@{

public:

//   ///
//   /// Create an instance with schema xschema and
//   /// initial storage for xcapacity dof tuples.
//   ///
//   poset_table_state(const schema_poset_member& xschema, size_type xcapacity);

  ///
  /// Create an instance with schema xschema and
  /// initial storage for xcapacity dof tuples.
  ///
  poset_table_state(const abstract_poset_member* xschema, size_type xcapacity);

  ///
  /// Destructor
  ///
  ~poset_table_state();

  ///
  /// Schema (mutable version)
  ///
  schema_poset_member& schema();

  ///
  /// Schema (const version)
  ///
  const schema_poset_member& schema() const;

  ///
  /// Get the table dof map
  ///
  array_poset_dof_map* table_dofs();

  ///
  /// Put the table dof map
  ///
  void put_table_dofs(array_poset_dof_map* xtable_dofs);

  ///
  /// True if xindex is a valid row dof tuple index.
  ///
  bool contains_row_dof_tuple(pod_index_type xindex) const;

  ///
  /// True if xindex is a valid row dof tuple index.
  ///
  bool contains_row_dof_tuple(const scoped_index& xindex) const;

  ///
  /// The number of dof tuples in the dof tuple table.
  ///
  size_type row_dof_tuple_ct() const;

  ///
  /// The upper bound of the index for row dof tuples.
  ///
  const scoped_index& row_dof_tuple_index_ub() const;

  ///
  /// The number of standard row_dof_tuples automatically
  /// allocated by the poset handle constructor.
  ///
  size_type standard_row_dof_tuple_ct() const;

  ///
  /// Put the number of standard row_dof_tuples automatically
  /// allocated by the poset handle constructor.
  ///
  void put_standard_row_dof_tuple_ct(size_type xct);

  ///
  /// The row dof tuple with index xindex
  ///
  poset_dof_map* row_dof_tuple(pod_index_type xindex);

  ///
  /// The row dof tuple with index xindex
  ///
  poset_dof_map* row_dof_tuple(const scoped_index& xindex);

  ///
  /// Sets the dof tuple at index xindex to xdof_tuple.
  ///
  void put_row_dof_tuple(poset_dof_map* xdof_tuple);

  ///
  /// Allocates an id space iterator over the row dof tuple ids from the
  /// iterator pool.
  ///
  index_space_iterator& get_row_dof_tuple_id_space_iterator() const;

  ///
  /// Returns the id space iterator xitr to the row dof tuple iterator pool.
  ///
  void release_row_dof_tuple_id_space_iterator(index_space_iterator& xitr) const;

protected:

private:

  ///
  /// Default Constructor; private to disable default construction.
  ///
  poset_table_state();

  ///
  /// The schema for this poset.
  /// @issue does handle inside state create access control problem?
  ///
  schema_poset_member* _schema;

  ///
  /// The table dofs ("class variables") for this poset.
  ///
  array_poset_dof_map* _table_dofs;

  ///
  /// The type of initialization policy for the row dof tuple block.
  ///
  typedef zero_block_initialization_policy<poset_dof_map*> row_dofs_init_type;

  ///
  /// The type of poset_dof_map block.
  ///
  typedef auto_block<poset_dof_map*, row_dofs_init_type> row_dofs_type;

  ///
  /// The row dof tuples for this poset.
  ///
  row_dofs_type _row_dof_tuples;

  ///
  /// The upper bound of the index for row dof tuples.
  ///
  scoped_index _row_dof_tuple_index_ub;

  ///
  /// The number of standard row_dof_tuples initially allocated
  /// by the poset constructor;
  ///
  size_type _standard_row_dof_tuple_ct;

  //@}


  // ===========================================================
  /// @name ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Collection of id spaces for this poset powerset.
  ///
  const index_space_family& id_spaces() const;

  ///
  /// Hub id space for this poset powerset.
  ///
  const hub_index_space_handle& hub_id_space() const;

  ///
  /// A id in the hub id space;
  /// intended for copying to initialize ids
  /// to the hub id space.
  ///
  const scoped_index& hub_id() const;

  ///
  /// A id in the hub id space with pod xid.
  ///
  scoped_index hub_id(pod_index_type xid) const;

protected:

private:

  ///
  /// Collection of id spaces for this poset.
  ///
  index_space_family _id_spaces;

  //@}


  // ===========================================================
  /// @name ANY INTERFACE
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to current
  ///
  virtual bool is_ancestor_of(const any* other) const;


  ///
  /// Make a new instance of the same type as this
  ///
  virtual poset_table_state* clone() const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

///
/// Insert poset_table_state& p into ostream& os.
///
SHEAF_DLL_SPEC 
std::ostream& operator << (std::ostream &os, const poset_table_state& p);

///
/// The deep size of the referenced object of type poset_table_state.
///
SHEAF_DLL_SPEC 
size_t deep_size(const poset_table_state& xp, bool xinclude_shallow = true);
 
} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_POSET_TABLE_STATE_H
