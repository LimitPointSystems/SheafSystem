// $RCSfile: cover_set_adapter.h,v $ $Revision: 1.16 $ $Date: 2013/01/14 16:03:37 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class cover_set_adapter
///
/// @deprecated The cover set mechanism has been replaced with id spaces.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef COVER_SET_ADAPTER_H
#define COVER_SET_ADAPTER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

#ifndef STD_OSTREAM_H
#include "std_ostream.h"
#endif

namespace sheaf
{
  
class cover_set_iterator;
class scoped_index;
class explicit_cover_set_iterator;

///
/// Common interface for explicit and implicit cover sets.
///
class SHEAF_DLL_SPEC cover_set_adapter : public any
{

  // ===========================================================
  /// @name COVER_SET_ADAPTER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  ///
  cover_set_adapter();

  ///
  /// Copy constructor
  ///
  ///
  cover_set_adapter(const cover_set_adapter& xother);

  ///
  /// Destructor
  ///
  virtual ~cover_set_adapter();

  ///
  /// Iterator for cover set.
  ///
  virtual cover_set_iterator iterator() const = 0;

  ///
  /// True if and only if this is the domain of iterator xitr.
  ///
  virtual bool contains_iterator(const cover_set_iterator& xitr) const = 0;

  ///
  /// True if and only if this is empty.
  ///
  virtual bool is_empty() const = 0;

  ///
  /// True if and only if this contains exactly one member.
  ///
  virtual bool is_singleton() const = 0;

  ///
  /// The number of members in this.
  ///
  virtual size_type size() const = 0;

  ///
  /// True if and only if this contains xindex.
  ///
  virtual bool contains_member(pod_index_type xindex) const = 0;

  ///
  /// True if and only if this contains xindex.
  ///
  bool contains_member(const scoped_index& xindex) const;

  ///
  /// True if and only if this contains the same members as xother.
  ///
  bool operator==(const cover_set_adapter& xother) const;

  ///
  /// True if and only if this contains the same members as the range of xitr.
  ///
  bool operator==(cover_set_iterator xitr) const;

  ///
  /// The first member of this.
  ///
  virtual pod_index_type first_member() const = 0;

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
  virtual cover_set_adapter* clone() const = 0;

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
/// Insert cover_set_adapter& p into ostream& os.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &os, const cover_set_adapter& p);

///
/// The deep size of the referenced object of type cover_set_adapter;
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC 
size_t deep_size(const cover_set_adapter& xp, bool xinclude_shallow = true);
 
} // namespace sheaf

#endif // ifndef COVER_SET_ADAPTER_H
