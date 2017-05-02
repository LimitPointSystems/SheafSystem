
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

// Interface for class dof_tuple_schema_versions_record

#ifndef DOF_TUPLE_SCHEMA_VERSIONS_RECORD_H
#define DOF_TUPLE_SCHEMA_VERSIONS_RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ATTRIBUTES_RECORD_H
#include "SheafSystem/attributes_record.h"
#endif

namespace sheaf
{
  
///
/// A wrapper/adapter for the dof tuple schema versions record.
/// Intended for transferring index-version map data
/// between the kernel and the i/o subsystem.
///
///
class SHEAF_DLL_SPEC dof_tuple_schema_versions_record : public attributes_record
{
public:

  // =============================================================================
  // ANY FACET
  // =============================================================================

  // CANONICAL MEMBERS

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual dof_tuple_schema_versions_record* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;


  // =============================================================================
  // DOF_TUPLE_SCHEMA_VERSIONS_RECORD FACET
  // =============================================================================

  ///
  /// Creates an instance with type map xtype_map
  ///
  dof_tuple_schema_versions_record(poset_scaffold& xscaffold);

  ///
  /// Copy constructor
  ///
  ///
  dof_tuple_schema_versions_record(const dof_tuple_schema_versions_record& xother);

  ///
  /// Destructor
  ///
  virtual ~dof_tuple_schema_versions_record();

protected:

  ///
  /// Initializes the poset from the internal buffer.
  ///
  void transfer_internal_buffer_to_poset();

  ///
  /// Initializes the internal buffer from the poset.
  ///
  void transfer_poset_to_internal_buffer();

};
  
} // namespace sheaf

#endif // ifndef DOF_TUPLE_SCHEMA_VERSIONS_RECORD_H






