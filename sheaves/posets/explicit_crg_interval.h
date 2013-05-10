

//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Interface for class explicit_crg_interval

#ifndef EXPLICIT_CRG_INTERVAL_H
#define EXPLICIT_CRG_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef CRG_INTERVAL_H
#include "crg_interval.h"
#endif

namespace sheaf
{

template <typename T>
class factory;

///
/// Implementation of crg_interval for explicit members of the poset.
///
class SHEAF_DLL_SPEC explicit_crg_interval : public crg_interval
{

  friend class namespace_poset;

  // ===========================================================
  /// @name EXPLICIT_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor; constructs an uninitialized interval.
  ///
  explicit_crg_interval();

  ///
  /// Destructor
  ///
  virtual ~explicit_crg_interval();

protected:

private:

  //@}


  // ===========================================================
  /// @name CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Initialize the lower covers for this interval.
  ///
  virtual void initialize_lower_covers();

  ///
  /// Initialize the upper covers for this interval.
  ///
  virtual void initialize_upper_covers();

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT COVER SET FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of this class;
  /// provided to satisfy factory template.
  ///
  virtual const string& class_name() const;

protected:

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

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
  virtual explicit_crg_interval* clone() const;

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
/// The deep size of the referenced object of type explicit_crg_interval;
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC 
size_t deep_size(const explicit_crg_interval& xp, bool xinclude_shallow = true);

} // namespace sheaf

#endif // ifndef EXPLICIT_CRG_INTERVAL_H
