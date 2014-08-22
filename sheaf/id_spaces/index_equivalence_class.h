
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
/// Interface for class index_equivalence_class

#ifndef COM_LIMITPOINT_SHEAF_INDEX_EQUIVALENCE_CLASS_H
#define COM_LIMITPOINT_SHEAF_INDEX_EQUIVALENCE_CLASS_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ANY_H
#include "ComLimitPoint/sheaf/any.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_BLOCK_H
#include "ComLimitPoint/sheaf/block.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POD_TYPES_H
#include "ComLimitPoint/sheaf/pod_types.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SCOPED_INDEX_H
#include "ComLimitPoint/sheaf/scoped_index.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_UTILITY_H
#include "std_utility.h"
#endif

namespace sheaf
{

class index_space_family;

///
/// Data structure containing the id equivalence class for ab id space family.
/// This class is used as a temporary data structured to be used by id
/// equivalence iterator. This class consists of a block of lists. Each list
/// has the equivalence id for the representive id in a given scope.
///
class SHEAF_DLL_SPEC index_equivalence_class
{

  friend class index_equivalence_iterator;

  // ===========================================================
  /// @name INDEX_EQUIVALENCE_CLASS FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// The member type for the equivalence id list.  The first value in
  /// the pair is the index of the id space, the second value in the
  /// pair is the pod.
  ///
  typedef std::pair<pod_type, pod_type> member_type;

  ///
  /// The equivalence id list type for this.
  ///
  typedef std::list<member_type> list_type;

  ///
  /// Creates the id equivalence class for the id space family xid_spaces.
  /// If xonly_persistent, only store equivalence ids from persistent id spaces.
  /// If xsort_ids, sort the ids in the equivalence list in increased space id order.
  ///
  index_equivalence_class(const index_space_family& xid_spaces,
			  bool xonly_persistent,
			  bool xsort_ids);

  ///
  /// Destructor.
  ///
  virtual ~index_equivalence_class();

  ///
  /// Assignment operator.
  ///
  index_equivalence_class& operator=(const index_equivalence_class& xother);

  ///
  /// The equivalence list for the representive id, xrep_id.
  ///
  const list_type& equivalence_list(pod_index_type xrep_id) const;

  ///
  /// The equivalence list for the representive id, xrep_id.
  ///
  const list_type& equivalence_list(const scoped_index& xrep_id) const;

  ///
  /// The number of ids in the equivalence list for the representive id, xrep_id.
  ///
  size_type equivalence_ct(pod_index_type xrep_id) const;

  ///
  /// The number of ids in the equivalence list for the representive id, xrep_id.
  ///
  size_type equivalence_ct(const scoped_index& xrep_id) const;

  ///
  /// True if this class contains the representive id, xrep_id.
  ///
  bool contains_rep_id(pod_index_type xrep_id) const;

  ///
  /// True if this class contains the representive id, xrep_id.
  ///
  bool contains_rep_id(const scoped_index& xrep_id) const;

  ///
  /// True if the id space of xitem1 is less than the id space of xitem2.
  ///
  static bool id_space_less_than(const member_type& xitem1, const member_type& xitem2);

protected:

  ///
  /// Default constructor; disabled.
  ///
  index_equivalence_class() { };

  ///
  /// Copy constructor; disabled.
  ///
  index_equivalence_class(const index_equivalence_class& xother) { };

  ///
  /// The block of equivalence id lists for a given representive id.
  ///
  block<list_type> _equivalence_lists;

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef INDEX_EQUIVALENCE_CLASS_H
