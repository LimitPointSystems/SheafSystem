// $RCSfile: property_disc_iterator_4_2.h,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:25 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class property_disc_iterator_4_2


#ifndef PROPERTY_DISC_ITERATOR_4_2_H
#define PROPERTY_DISC_ITERATOR_4_2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef PROPERTY_DISC_ITERATOR_H
#include "property_disc_iterator.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef CHART_POINT_3D_H
#include "chart_point_3d.h"
#endif

#ifndef SEC_VD_H
#include "sec_vd.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif

namespace fiber_bundle
{
class eval_family;
class section_space_schema_member;
class section_evaluator;
class sec_rep_descriptor;
class structured_block;
}

namespace fields
{

///
/// A property discretization iterator for a field with uniform coordinates
/// section and a property section with the evaluation strictly above the
/// discretization.
///
class SHEAF_DLL_SPEC property_disc_iterator_4_2 : public property_disc_iterator
{

  // ===========================================================
  /// @name PROPERTY_DISC_ITERATOR_4_2 FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an iterator over the schema of xfield.
  ///
  property_disc_iterator_4_2(const field_vd& xfield);

  ///
  /// Creates an iterator anchored at xcoordinate_schema.base_space().
  ///
  property_disc_iterator_4_2(
    const section_space_schema_member& xcoordinate_schema,
    const section_space_schema_member& xproperty_schema);

  ///
  /// Destructor.
  ///
  ~property_disc_iterator_4_2();

private:

  ///
  /// Default constructor; disabled.
  ///
  property_disc_iterator_4_2() {};

  ///
  /// Copy constructor; disabled.
  ///
  property_disc_iterator_4_2(const property_disc_iterator_4_2& xother) {};

  //@}


  // ===========================================================
  /// @name PROPERTY_DISC_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The gets the values of xsec at the property discretization points.
  ///
  virtual void get_prop_disc_values(const sec_vd& xsec);

  //@}


  // ===========================================================
  /// @name DEPTH_FIRST_ITERATOR FACET
  // ===========================================================
  //@{

public:

  using property_disc_iterator::next;

  ///
  /// Makes this the next member of the subset.
  /// If xtruncate, new this is not less than old this,
  /// i.e. the depth-first descent is truncated
  /// and the cover of this is not visited.
  ///
  virtual void next(bool xtruncate);

  ///
  /// Restarts the iteration.
  ///
  virtual void reset(bool xreset_markers = true);

  //@}

  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual property_disc_iterator_4_2* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  //@}
};
  
} // namespace fields

#endif // ifndef PROPERTY_DISC_ITERATOR_4_2_H
