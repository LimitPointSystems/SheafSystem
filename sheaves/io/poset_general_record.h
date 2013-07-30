
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

// Interface for class poset_general_record

#ifndef POSET_GENERAL_RECORD_H
#define POSET_GENERAL_RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef DATA_CONVERTER_H
#include "data_converter.h"
#endif

#ifndef POSET_DATA_TYPE_MAP_H
#include "poset_data_type_map.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef STD_CSTDLIB_H
#include "std_cstdlib.h"
#endif

#ifndef STD_UTILITY_H
#include "std_utility.h"
#endif

#ifndef ATTRIBUTES_RECORD_H
#include "attributes_record.h"
#endif

namespace sheaf
{
  
///
/// A wrapper/adapter for the poset general attributes record.
/// Intended for transferring data between the kernel and
/// the i/o subsystem.
///
class SHEAF_DLL_SPEC poset_general_record : public attributes_record
{
public:

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  poset_general_record(const poset_general_record& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual poset_general_record* clone() const;

  ///
  /// Destructor
  ///
  virtual ~poset_general_record();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // POSET_GENERAL_RECORD INTERFACE

  ///
  /// Creates an instance with type map xtype_map
  ///
  poset_general_record(poset_scaffold& xscaffold);

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

#endif // ifndef POSET_GENERAL_RECORD_H






