// $RCSfile: explicit_cover_set_adapter.h,v $ $Revision: 1.16 $ $Date: 2013/01/14 16:03:37 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class explicit_cover_set_adapter
///
/// @deprecated The cover set mechanism has been replaced with id spaces.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef EXPLICIT_COVER_SET_ADAPTER_H
#define EXPLICIT_COVER_SET_ADAPTER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef COVER_SET_ADAPTER_H
#include "cover_set_adapter.h"
#endif

namespace sheaf
{
  
class cover_set_iterator;
class scoped_index;

///
/// An abstract interface to an explicit, mutable cover set representation.
///
class SHEAF_DLL_SPEC explicit_cover_set_adapter : public cover_set_adapter
{
  // ===========================================================
  /// @name EXPLICIT_COVER_SET_ADAPTER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  ///
  explicit_cover_set_adapter();

  ///
  /// Copy constructor
  ///
  ///
  explicit_cover_set_adapter(const explicit_cover_set_adapter& xother);

  ///
  /// Destructor
  ///
  virtual ~explicit_cover_set_adapter();

  ///
  /// Inserts xindex.
  ///
  virtual void insert_member(pod_index_type xindex) = 0;

  ///
  /// Inserts xindex in this.
  ///
  void insert_member(const scoped_index& xindex);

  ///
  /// Removes xindex.
  ///
  virtual void remove_member(pod_index_type xindex) = 0;

  ///
  /// Removes xindex from this.
  ///
  void remove_member(const scoped_index& xindex);

  ///
  /// Removes the current item of xitr.
  ///
  virtual void remove_member(const cover_set_iterator& xitr) = 0;

  ///
  /// Replaces xold_mbr_index with xnew_mbr_index.
  ///
  virtual void replace_member(pod_index_type xold_mbr_index,
			      pod_index_type xnew_mbr_index) = 0;

  ///
  /// Replaces xold_mbr_index with xnew_mbr_index.
  ///
  void replace_member(const scoped_index& xold_mbr_index,
		      const scoped_index& xnew_mbr_index);

  ///
  /// Makes this empty.
  ///
  virtual void clear() = 0;

  ///
  /// Copies xother.
  ///
  explicit_cover_set_adapter& operator=(const cover_set_adapter& xother);

  ///
  /// Copies the range of xitr.
  ///
  explicit_cover_set_adapter& operator=(const cover_set_iterator& xitr);

  ///
  /// Appends the range of xitr.
  ///
  explicit_cover_set_adapter& operator+=(cover_set_iterator xitr);

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER_SET_ADAPTER FACET
  // ===========================================================
  //@{

public:

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
  virtual explicit_cover_set_adapter* clone() const = 0;

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

///
/// The deep size of the referenced object of type explicit_cover_set_adapter;
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC 
size_t deep_size(const explicit_cover_set_adapter& xp, bool xinclude_shallow = true);
 
} // namespace sheaf

#endif // ifndef EXPLICIT_COVER_SET_ADAPTER_H
