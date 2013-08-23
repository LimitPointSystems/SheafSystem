
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
/// Interface for class section_pusher_push_action

#ifndef SECTION_PUSHER_PUSH_ACTION_H
#define SECTION_PUSHER_PUSH_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef PULLBACK_MAP_H
#include "pullback_map.h"
#endif

namespace sheaf
{
template <typename T>
class block;
}

namespace fiber_bundle
{
class sec_vd;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;

///
/// Abstract functor to compute the dofs at a destination discretization point.
///
class SHEAF_DLL_SPEC section_pusher_push_action : public any
{

  // =============================================================================
  /// @name SECTION_PUSHER_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Destructor.
  ///
  virtual ~section_pusher_push_action();

  ///
  /// The fiber dimension of the destination.
  ///
  int dst_df();

  ///
  /// Computes xdst_dofs using xitr and the dofs already in xdst, as needed.
  ///
  virtual void operator()(pullback_map::iterator& xitr,
                          sec_vd& xdst,
                          block<sec_vd_dof_type>& xdst_dofs) = 0;

  ///
  /// Initializes xdst as needed.
  ///
  virtual void initialize(sec_vd& xdst);

  ///
  /// Finalizes xdst as needed.
  ///
  virtual void finalize(sec_vd& xdst);


protected:

  ///
  /// Default constructor.
  ///
  section_pusher_push_action();

  ///
  /// Creates an instance with dst_df() == xdst_df.
  ///
  section_pusher_push_action(int xdst_df);

  // Copy constructor; default memberwise copy constructor will do.

  ///
  /// The fiber dimension of the destination.
  ///
  int _dst_df;

  //@}


  // =============================================================================
  /// @name ANY FACET
  // =============================================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual section_pusher_push_action* clone() const = 0;

  ///
  /// Assignment operator
  ///
  virtual section_pusher_push_action& operator=(const section_pusher_push_action& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
 
} // namespace fields

#endif // ifndef SECTION_PUSHER_PUSH_ACTION_H
