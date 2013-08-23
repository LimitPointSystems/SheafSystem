
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

  friend class namespace_poset;

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
