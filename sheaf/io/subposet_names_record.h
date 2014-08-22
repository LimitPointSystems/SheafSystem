
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

// Interface for class subposet_names_record

#ifndef COM_LIMITPOINT_SHEAF_SUBPOSET_NAMES_RECORD_H
#define COM_LIMITPOINT_SHEAF_SUBPOSET_NAMES_RECORD_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ATTRIBUTES_RECORD_H
#include "ComLimitPoint/sheaf/attributes_record.h"
#endif

namespace sheaf
{
  
///
/// A wrapper/adapter for the subposet names record.
/// Intended for transferring subposet name data
/// between the kernel and the i/o subsystem.
///
///
class SHEAF_DLL_SPEC subposet_names_record : public attributes_record
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
  virtual subposet_names_record* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // =============================================================================
  // SUBPOSET_NAMES_RECORD FACET
  // =============================================================================

  ///
  /// Creates an instance with type map xtype_map
  ///
  subposet_names_record(poset_scaffold& xscaffold);

  ///
  /// Copy constructor
  ///
  ///
  subposet_names_record(const subposet_names_record& xother);

  ///
  /// Destructor
  ///
  virtual ~subposet_names_record();

protected:

  ///
  /// Initializes member with index xmbr_id from the internal buffer.
  ///
  virtual void transfer_internal_buffer_to_poset();

  ///
  /// Initializes the internal buffer from the member with index xmbr_id.
  ///
  virtual void transfer_poset_to_internal_buffer();
};

} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_SUBPOSET_NAMES_RECORD_H






