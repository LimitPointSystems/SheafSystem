// $RCSfile: list_cover_set_adapter.h,v $ $Revision: 1.15 $ $Date: 2013/01/14 16:03:37 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class list_cover_set_adapter
///
/// @deprecated The cover set mechanism has been replaced with id spaces.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef LIST_COVER_SET_ADAPTER_H
#define LIST_COVER_SET_ADAPTER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_COVER_SET_ADAPTER_H
#include "explicit_cover_set_adapter.h"
#endif

#ifndef LIST_COVER_SET_H
#include "list_cover_set.h"
#endif

namespace sheaf
{
  
///
/// Common interface for explicit and implicit cover sets.
///
class SHEAF_DLL_SPEC list_cover_set_adapter : public explicit_cover_set_adapter
{
  // ===========================================================
  /// @name LIST_COVER_SET_ADAPTER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  list_cover_set_adapter();

  ///
  /// Copy constructor
  ///
  list_cover_set_adapter(const list_cover_set_adapter& xother);

  ///
  /// Creates an instance which is a copy of the range of xitr.
  ///
  list_cover_set_adapter(const cover_set_iterator& xitr);

  ///
  /// Destructor
  ///
  virtual ~list_cover_set_adapter();

protected:

private:

  ///
  /// The cover set.
  ///
  list_cover_set _cover;

  //@}


  // ===========================================================
  /// @name EXPLICIT_COVER_SET_ADAPTER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Inserts xindex in this.
  ///
  virtual void insert_member(pod_index_type xindex);

  ///
  /// Removes xindex from this.
  ///
  virtual void remove_member(pod_index_type xindex);

  ///
  /// Removes the current item of xitr from this.
  ///
  virtual void remove_member(const cover_set_iterator& xitr);

  ///
  /// Replaces xold_mbr_index with xnew_mbr_index.
  ///
  void replace_member(pod_index_type xold_mbr_index,
		      pod_index_type xnew_mbr_index);

  ///
  /// Makes this empty.
  ///
  virtual void clear();

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER_SET_ADAPTER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Iterator for cover set.
  ///
  virtual cover_set_iterator iterator() const;

  ///
  /// True if and only if this is the domain of iterator xitr.
  ///
  virtual bool contains_iterator(const cover_set_iterator& xitr) const;

  ///
  /// True if and only if this is empty.
  ///
  virtual bool is_empty() const;

  ///
  /// True if and only if this contains exactly one member.
  ///
  virtual bool is_singleton() const;

  ///
  /// The number of members in this.
  ///
  virtual size_type size() const;

  ///
  /// True if and only if this contains xindex.
  ///
  virtual bool contains_member(pod_index_type xindex) const;

  ///
  /// The first member of this.
  ///
  virtual pod_index_type first_member() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual list_cover_set_adapter* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // namespace sheaf

#endif // ifndef LIST_COVER_SET_ADAPTER_H
