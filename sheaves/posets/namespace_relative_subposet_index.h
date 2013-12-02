
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

// Interface for class namespace_relative_subposet_index

#ifndef NAMESPACE_RELATIVE_SUBPOSET_INDEX_H
#define NAMESPACE_RELATIVE_SUBPOSET_INDEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SCOPED_INDEX
#include "scoped_index.h"
#endif

namespace sheaf
{
  
///
/// Index for identifying a subposet relative to a given name space.
///
struct SHEAF_DLL_SPEC namespace_relative_subposet_index
{
  ///
  /// The POD (plain old data) type associated this.
  ///
  typedef namespace_relative_subposet_index_pod_type pod_type;

  ///
  /// Default constructor.
  ///
  inline namespace_relative_subposet_index()
  {
    // Scoped_index data members are invalid by default.

    // Postconditions:

    ensure(!is_valid());

    // Exit:

    return;
  };


  ///
  /// Constructor from pod_type.
  ///
  inline explicit namespace_relative_subposet_index(const index_space_handle& xid_space, const pod_type& xpod)
      : poset_id(xid_space, xpod.poset_id),
	subposet_id(xid_space, xpod.subposet_id)
  {
    // Postconditions:

    ensure((pod() == xpod) || !is_valid());

    // Exit:

    return;
  };

  ///
  /// The index of the poset relative to the namespace.
  ///
  scoped_index poset_id;

  ///
  /// The index of the subposet relative to the poset.
  ///
  scoped_index subposet_id;

  

  ///
  /// Equality operator
  ///
  inline bool operator==(const namespace_relative_subposet_index& xother) const
  {
    bool result;

    // Preconditions:

    // Body:

    result = ((poset_id == xother.poset_id) && (subposet_id == xother.subposet_id));

    // Postconditions:

    ensure(result == ((poset_id == xother.poset_id) && (subposet_id == xother.subposet_id)));

    // Exit:

    return result;
  };

  ///
  /// True if this is a valid id.
  ///
  inline bool is_valid() const
  {
    bool result;

    // Preconditions:

    // Body:

    result = (poset_id.is_valid() && subposet_id.is_valid());

    // Postconditions:

    // Exit:

    return result;
  };

  ///
  /// Make this invalid.
  ///
  void invalidate()
  {
    // Preconditions:

    // Body:

    poset_id.invalidate();
    subposet_id.invalidate();

    // Postconditions:

    ensure(!is_valid());

    // Exit:

    return;
  };

  ///
  /// The invalid id.
  ///
  inline static const namespace_relative_subposet_index& INVALID()
  {
    // Preconditions:

    // Body:

    // Default constructor makes invalid.

    static const namespace_relative_subposet_index result;

    // Postconditions:

    ensure(!result.is_valid());

    // Exit:

    return result;
  };

  ///
  /// The "plain old data" storage of this.
  ///
  inline pod_type pod() const
  {
    pod_type result;
    result.poset_id = poset_id.pod();
    result.subposet_id = subposet_id.pod();

    return result;
  };

  ///
  /// Sets pod() to xpod.
  ///
  inline void put_pod(pod_type xpod)
  {

    // Preconditions:

    // Body:

    poset_id.put_pod(xpod.poset_id);
    subposet_id.put_pod(xpod.subposet_id);

    // Postconditions:

    ensure(pod() == xpod || !is_valid());

    // Exit:

    return;
  };
} ;

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts namespace_relative_subposet_index xindex into ostream xos
///
SHEAF_DLL_SPEC 
std::ostream&
operator<<(std::ostream& xos, const namespace_relative_subposet_index& xindex);


///
/// Extracts namespace_relative_subposet_index xindex from istream xis
///
SHEAF_DLL_SPEC 
std::istream&
operator>>(std::istream& xis, namespace_relative_subposet_index& xindex);
 
} // namespace sheaf

#endif // ifndef NAMESPACE_RELATIVE_SUBPOSET_INDEX_H






