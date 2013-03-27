// $RCSfile: list_cover_set.h,v $ $Revision: 1.19 $ $Date: 2013/01/14 16:03:37 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class list_cover_set.
///
/// @deprecated The cover set mechanism has been replaced with id spaces.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef LIST_COVER_SET_H
#define LIST_COVER_SET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef STD_ALGORITHM_H
#include "std_algorithm.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef STD_ITERATOR_H
#include "std_iterator.h"
#endif

namespace sheaf
{

template <typename T>
class rc_ptr;

class list_cover_set_adapter;
class subposet;
  
///
/// An upper or lower cover set of a poset member.
/// @issue list_cover_set exhibits strong conflicts between
/// space efficiency and time efficiency. The current implementation
/// is a compromise based on list, giving time efficient cover
/// set construction combined with moderate space efficiency.
/// Cover set editing, i.e. member removal, is not efficient,
/// nor is set equality. Several other set operations are not
/// currently needed and hence have not been implemented.
///
class SHEAF_DLL_SPEC list_cover_set : public list<pod_index_type>
{

  friend class list_cover_set_adapter;
  friend class rc_ptr<list_cover_set>;

public:

  ///
  /// Default constructor.
  ///
  list_cover_set();

  ///
  /// Creates an instace with reference count == xref_ct.
  ///
  list_cover_set(size_type xref_ct);

  ///
  /// Copy constructor.
  ///
  list_cover_set(const list_cover_set& xother);

  ///
  /// Destructor.
  ///
  ~list_cover_set();

  ///
  /// The number of members of this;
  /// synonym for size(). Warning: performance is O(size());
  ///
  int member_ct() const;

  ///
  /// Insert member with index xmbr.
  ///
  void insert_member(pod_index_type xmbr);

  ///
  /// Insert member with index xmbr.
  ///
  void insert_member(const scoped_index& xmbr);

  ///
  /// Remove member with index xmbr.
  /// Average performance is O(size()); useful only for small sets.
  ///
  void remove_member(pod_index_type xmbr);

  ///
  /// Remove member with index xmbr.
  /// Average performance is O(size()); useful only for small sets.
  ///
  void remove_member(const scoped_index& xmbr);

  ///
  /// Hint to help accelerate remove_member.
  ///
  class SHEAF_DLL_SPEC hint
  {
    friend class list_cover_set;

  public:

    ///
    /// Destructor.
    ///
    ~hint();

  private:

    ///
    /// Creates an instance for xhost.
    ///
    hint(const list_cover_set& xhost);

    ///
    /// The cover set this is an accelerator for.
    ///
    list_cover_set& host();

    ///
    /// The cover set this is an accelerator for.
    ///
    list_cover_set& _host;

    ///
    /// The item to start the remove search at.
    ///
    list_cover_set::iterator& itr();

    ///
    /// The item to start the remove search at.
    ///
    list_cover_set::iterator _itr;
  };

  ///
  /// Creates an instance of a hint for use with remove_member.
  ///
  hint* new_hint();

  ///
  /// Remove member with index xmbr using xhint to accelerate performance.
  /// Improves average performance to O(1) when called repeatedly;
  /// worst case is still O(size()).
  ///
  void remove_member(pod_index_type xmbr, const hint* xhint);

  ///
  /// Remove member with index xmbr using xhint to accelerate performance.
  /// Improves average performance to O(1) when called repeatedly;
  /// worst case is still O(size()).
  ///
  void remove_member(const scoped_index& xmbr, const hint* xhint);

  ///
  /// Replaces xold_mbr with xnew_mbr.
  ///
  void replace_member(pod_index_type xold_mbr, pod_index_type xnew_mbr);

  ///
  /// Replaces xold_mbr with xnew_mbr.
  ///
  void replace_member(const scoped_index& xold_mbr, const scoped_index& xnew_mbr);

  ///
  /// True if this set contains xindex.
  /// Performance is O(size()); useful only for small sets.
  ///
  bool contains_member(pod_index_type xindex) const;

  ///
  /// True if this set contains xindex.
  /// Performance is O(size()); useful only for small sets.
  ///
  bool contains_member(const scoped_index& xindex) const;

  ///
  /// True if set contains only a single member.
  ///
  bool is_singleton() const;

  ///
  /// True if set contains more than a single member.
  ///
  bool is_multiple() const;

  ///
  /// True if this is equal to other, considered as sets.
  /// Performance is O(size()**2); useful only for small sets.
  ///
  bool set_equals(const list_cover_set* xother) const;

  ///
  /// Intersection of this with other, auto-allocated version.
  /// Performance is O(size()**2); useful only for small sets.
  ///
  list_cover_set* set_intersection(const list_cover_set* xother) const;

  ///
  /// Intersection of this with other, pre-allocated version.
  /// Performance is O(size()**2); useful only for small sets.
  ///
  void set_intersection_pa(const list_cover_set* xother, list_cover_set* xresult) const;

  ///
  /// Intersection of this with other, self-allocated version.
  /// Performance is O(size()**2); useful only for small sets.
  ///
  void set_intersection_sa(const list_cover_set* xother);

  ///
  /// Prints this to an ostream (default = stdout);
  /// intended for debugging.
  ///
  void to_stream(ostream& os = cout) const;

  ///
  /// Get debugging information as a string.
  ///
  string to_string() const;

  ///
  /// Increment the reference count
  ///
  void add_reference();

  ///
  /// Decrement the reference count.  Delete this object if
  /// the reference count is zero.
  ///
  void remove_reference();

  ///
  /// True if the reference count is greater than one.
  ///
  bool is_shared() const;

  ///
  /// The reference count.
  /// Note that size_type is list::size_type not sheaf::size_type.
  ///
  size_type ref_ct() const;

  ///
  /// True if this is a proxy for an implicit cover set.
  ///
  bool is_implicit() const;

  ///
  /// Sets is_implict() == xis_implicit.
  ///
  void put_is_implicit(bool xis_implicit);

protected:

private:

  ///
  /// Reference count.
  /// Note that size_type is list::size_type not sheaf::size_type.
  ///
  size_type _ref_ct;

  ///
  /// True if this is a proxy for an implicit cover set.
  ///
  bool _is_implicit;

  //@}
};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert cover_set_stae& c into ostream& os.
///
SHEAF_DLL_SPEC
ostream & operator << (ostream &xos, const list_cover_set& c);

///
/// The deep size for a referenced object of type list_cover_set.
///
SHEAF_DLL_SPEC
size_t deep_size(const list_cover_set& xp, bool xinclude_shallow = true);
 
} // namespace sheaf


#endif // ifndef LIST_COVER_SET_H


