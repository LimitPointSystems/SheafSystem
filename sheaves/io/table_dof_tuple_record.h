
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

// Interface for class table_dof_tuple_record

#ifndef TABLE_DOF_TUPLE_RECORD_H
#define TABLE_DOF_TUPLE_RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ATTRIBUTES_RECORD_H
#include "attributes_record.h"
#endif

namespace sheaf
{
  
///
/// A wrapper/adapter for the table dof tuple record.
/// Intended for transferring data between the kernel
/// and the i/o subsystem.
///
class SHEAF_DLL_SPEC table_dof_tuple_record : public attributes_record
{
public:

  // =============================================================================
  // ANY FACET
  // =============================================================================

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual table_dof_tuple_record* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // =============================================================================
  // TABLE_DOF_TUPLE_RECORD FACET
  // =============================================================================

  ///
  /// Copy constructor
  ///
  table_dof_tuple_record(const table_dof_tuple_record& xother);

  ///
  /// Creates an instance with type map xtype_map
  ///
  table_dof_tuple_record(poset_scaffold& xscaffold);

  ///
  /// Destructor
  ///
  virtual ~table_dof_tuple_record();

protected:

  ///
  /// Initializes scaffold from the internal buffer.
  ///
  virtual void transfer_internal_buffer_to_poset();

  ///
  /// Initializes the internal buffer from the scaffold.
  ///
  virtual void transfer_poset_to_internal_buffer();

private:

  ///
  /// Releases the access to the prerequisites of xposet
  /// acquired in storage_agent::read_prequisites needed to
  /// build xposet.
  ///
  void release_prerequisites(poset_state_handle& xposet);

};

} // namespace sheaf

#endif // ifndef TABLE_DOF_TUPLE_RECORD_H






