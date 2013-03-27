// $RCSfile: standard_member_hack_crg_interval.h,v $ $Revision: 1.2 $ $Date: 2013/01/10 13:55:04 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Interface for class standard_member_hack_crg_interval

#ifndef STANDARD_MEMBER_HACK_CRG_INTERVAL_H
#define STANDARD_MEMBER_HACK_CRG_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_CRG_INTERVAL_H
#include "explicit_crg_interval.h"
#endif

namespace sheaf
{

template <typename T>
class factory;

///
/// Implementation of explicit_crg_interval intended only to support the product
/// poset hack in section_space_schema_poset.
/// @hack Cartesian product subspace hack;
///
class SHEAF_DLL_SPEC standard_member_hack_crg_interval : public explicit_crg_interval
{

  // ===========================================================
  /// @name STANDARD_MEMBER_HACK_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor; constructs an uninitialized interval.
  ///
  standard_member_hack_crg_interval();

  ///
  /// Destructor
  ///
  virtual ~standard_member_hack_crg_interval();

protected:

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

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
  /// @name STANDARD_MEMBER_HACK COVER SET FACET
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
  /// True if prototype for this class has been entered in factory.
  /// Intended to force creation of prototype at initialization.
  ///
  static bool _has_prototype;

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
  virtual standard_member_hack_crg_interval* clone() const;

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
/// The deep size of the referenced object of type standard_member_hack_crg_interval;
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC 
size_t deep_size(const standard_member_hack_crg_interval& xp, bool xinclude_shallow = true);

} // namespace sheaf

#endif // ifndef STANDARD_MEMBER_HACK_CRG_INTERVAL_H
