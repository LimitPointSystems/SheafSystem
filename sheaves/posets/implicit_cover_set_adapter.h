// $RCSfile: implicit_cover_set_adapter.h,v $ $Revision: 1.15 $ $Date: 2013/01/14 16:03:37 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class implicit_cover_set_adapter
///
/// @deprecated The cover set mechanism has been replaced with id spaces.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef IMPLICIT_COVER_SET_ADAPTER_H
#define IMPLICIT_COVER_SET_ADAPTER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef COVER_SET_ADAPTER_H
#include "cover_set_adapter.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

namespace sheaf
{
  
///
/// An abstract interface to an immutable, implicit cover set representation.
///
class SHEAF_DLL_SPEC implicit_cover_set_adapter : public cover_set_adapter
{
  // ===========================================================
  /// @name IMPLICIT_COVER_SET_ADAPTER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  implicit_cover_set_adapter();

  ///
  /// Copy constructor
  ///
  ///
  implicit_cover_set_adapter(const implicit_cover_set_adapter& xother);

  ///
  /// Destructor
  ///
  virtual ~implicit_cover_set_adapter();

  ///
  /// The member index of the cover set this is emulating.
  ///
  const scoped_index& member_index() const;

  ///
  /// Sets the member index of the cover set this is emulating to xindex.
  ///
  void put_member_index(const scoped_index& xindex);

  ///
  /// The beginning of the implicit member range; this emulates
  /// the cover of members with index begin() <= index < end().
  ///
  const scoped_index& range_begin() const;

  ///
  /// The end of the implicit member range; this emulates
  /// the cover of members with index begin() <= index < end().
  ///
  const scoped_index& range_end() const;

  ///
  /// The number of members in the implicit member range.
  ///
  size_type range_size() const;

  ///
  /// True if and only if this can emulate
  /// the cover set of the member with index xindex.
  ///
  bool can_emulate(const scoped_index& xindex) const;

  ///
  /// Sets the beginning of the implicit member range to xbegin.
  ///
  void put_range_begin(const scoped_index& xbegin);

protected:

private:

  ///
  /// The member index of the cover set this is currently emulating.
  ///
  scoped_index _member_index;

  ///
  /// The beginning of the implicit member range; this emulates
  /// the cover of members with index begin() <= index < end().
  ///
  scoped_index _range_begin;

  ///
  /// The end of the implicit member range; this emulates
  /// the cover of members with index begin() <= index < end().
  ///
  scoped_index _range_end;

  ///
  /// The number of members in the implicit member range.
  ///
  size_type _range_size;

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
  virtual implicit_cover_set_adapter* clone() const = 0;

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

#endif // ifndef IMPLICIT_COVER_SET_ADAPTER_H
