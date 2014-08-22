
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
/// Interface for class discretization_push_action

#ifndef DISCRETIZATION_PUSH_ACTION_H
#define DISCRETIZATION_PUSH_ACTION_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef FIELDS_H
#include "fields.h"
#endif

namespace fields
{

///
/// The action to executed by discretization_pusher::push
/// on each member of a discretization subposet.
///
class SHEAF_DLL_SPEC discretization_push_action
{

  // ===========================================================
  /// @name DISCRETIZATION_PUSH_ACTION FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor
  ///
  virtual ~discretization_push_action();

  ///
  /// The push action.
  ///
  virtual void operator () (const scoped_index& xmbr_id,
                            block<sec_vd_value_type>& xglobal_coords) = 0;

protected:

  ///
  /// Default constructor
  ///
  discretization_push_action();


private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef DISCRETIZATION_PUSH_ACTION_H
