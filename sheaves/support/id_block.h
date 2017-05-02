
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

// Interface for class id_block

#ifndef ID_BLOCK_H
#define ID_BLOCK_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "SheafSystem/block.h"
#endif

#ifndef SCOPED_INDEX_H
#include "SheafSystem/scoped_index.h"
#endif

#ifndef SHEAF_H
#include "SheafSystem/sheaf.h"
#endif

namespace sheaf
{

class any;
class poset_state_handle;

///
/// A block of ids all in the same id space.
///
class SHEAF_DLL_SPEC id_block : public block<scoped_index>
{

public:

  // =============================================================================
  // ANY FACET
  // =============================================================================

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual id_block* clone() const;

  ///
  /// Assignment operator
  ///
  id_block& operator=(const id_block& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  // =============================================================================
  // ID_BLOCK FACET
  // =============================================================================

  ///
  /// Copy constructor.
  ///
  id_block(const id_block& xother);

  ///
  /// Destructor.
  ///
  virtual ~id_block();

  ///
  /// Creates an instance with host() == xhost,
  /// id space == xid_space, ub() == xub, and
  /// xct ids copied from xids.
  ///
  id_block(const poset_state_handle& xhost,
           const index_space_handle& xid_space,
           int xub,
           const scoped_index *xids = 0,
           int xct = 0);

  ///
  /// The poset that id_space resides in (mutable version).
  ///
  poset_state_handle& host();

  ///
  /// The poset that id_space resides in (const version).
  ///
  const poset_state_handle& host() const;

  ///
  /// The id space the ids in this block belong to.
  ///
  const index_space_handle& id_space() const;

  ///
  /// Sets space() to xid_space and translates the ids.
  ///
  void put_id_space(const index_space_handle& xnew_id_space, bool xauto_access);

  ///
  /// Sets space() to host().member_id_space() and translates the ids.
  ///
  void put_member_id_space(bool xauto_access);

  ///
  /// True if space() == host().member_hub_id_space().
  ///
  bool is_member_hub_id_space() const;


private:

  ///
  /// Default constructor; private to prevent default construction.
  ///
  id_block();

  ///
  /// The poset that id space resides in.
  ///
  poset_state_handle* _host;

  ///
  /// The id space the ids in this block belong to.
  ///
  index_space_handle* _id_space;

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

///
/// Inserts block xblk into ostream xos.
///
SHEAF_DLL_SPEC
std::ostream&
operator << (std::ostream& xos, const id_block& xblk);

} // namespace sheaf

#endif // ifndef ID_BLOCK_H
