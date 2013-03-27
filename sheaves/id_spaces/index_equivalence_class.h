// $RCSfile: index_equivalence_class.h,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:35 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class index_equivalence_class

#ifndef INDEX_EQUIVALENCE_CLASS_H
#define INDEX_EQUIVALENCE_CLASS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
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
  typedef pair<pod_type, pod_type> member_type;

  ///
  /// The equivalence id list type for this.
  ///
  typedef list<member_type> list_type;

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
