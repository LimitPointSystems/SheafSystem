
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//



// Interface for class record_index

#ifndef RECORD_INDEX_H
#define RECORD_INDEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

namespace sheaf
{
  
///
/// The type used for indexing records in a dataset.
///
typedef scoped_index record_index;

///
/// The POD (plain old data) type associated with this.
///
struct SHEAF_DLL_SPEC namespace_relative_record_index_pod_type
{
  record_index::pod_type poset_id;
  record_index::pod_type member_id;

  bool operator==(const namespace_relative_record_index_pod_type& xother) const
  {
    return (poset_id == xother.poset_id) && (member_id == xother.member_id);
  };

  bool is_valid()
  {
    return (sheaf::is_valid(poset_id) && sheaf::is_valid(member_id));
  };
};

///
/// Record index equivalent to namespace_relative_member_index
/// and namespace_relative_subposet_index.
///
class SHEAF_DLL_SPEC namespace_relative_record_index
{
public:

  ///
  /// The POD (plain old data) type associated this.
  ///
  typedef namespace_relative_record_index_pod_type pod_type;

  ///
  /// Default constructor
  ///
  inline namespace_relative_record_index()
  {
    // Preconditions:

    // Body:

    // Scoped_index data members are invalid by default.

    // Postconditions:

    ensure(!is_valid());

    // Exit:

    return;
  };

  ///
  /// The record index of the poset relative to the namespace.
  ///
  record_index poset_id;

  ///
  /// The record index of the member relative to the poset.
  ///
  record_index member_id;

  ///
  /// Copy constructor
  ///
  inline namespace_relative_record_index(const namespace_relative_record_index& xother)
      : poset_id(xother.poset_id),
      member_id(xother.member_id)
  {
    // Preconditions:

    // Body:


    // Postconditions:

    ensure(*this == xother);

    // Exit:

    return;
  };

  ///
  /// Assignment operator
  ///
  inline namespace_relative_record_index& operator=(const namespace_relative_record_index& xother)
  {
    // Preconditions:

    // Body:

    poset_id  = xother.poset_id;
    member_id = xother.member_id;

    // Postconditions:

    ensure(*this == xother);

    // Exit:

    return *this;
  };

  

  ///
  /// Equality operator
  ///
  inline bool operator==(const namespace_relative_record_index& xother) const
  {
    bool result;

    // Preconditions:

    // Body:

    result = ((poset_id == xother.poset_id) && (member_id == xother.member_id));

    // Postconditions:

    ensure(result == ((poset_id == xother.poset_id) && (member_id == xother.member_id)));

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

    result = (poset_id.is_valid() && member_id.is_valid());

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
    member_id.invalidate();

    // Postconditions:

    ensure(!is_valid());

    // Exit:

    return;
  };

  ///
  /// The invalid id.
  ///
  inline static const namespace_relative_record_index& INVALID()
  {
    // Preconditions:

    // Body:

    // Default constructor makes invalid.

    static const namespace_relative_record_index result;

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
    result.member_id = member_id.pod();

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
    member_id.put_pod(xpod.member_id);

    // Postconditions:

    ensure(pod() == xpod || !is_valid());

    // Exit:

    return;
  };



};

} // namespace sheaf

#endif // ifndef RECORD_INDEX_H






