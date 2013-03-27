// $RCSfile: body_builder.h,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:26 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class body_builder

#ifndef BODY_BUILDER_H
#define BODY_BUILDER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef FIELDS_H
#include "fields.h"
#endif

namespace sheaf
{
template <class T>
class block;
class subposet;
}

namespace fiber_bundle
{
class base_space_poset;
class section_evaluator;
}

namespace fields
{

class field_vd;

///
/// A simple body builder; creates base space members equivalent to
/// subsets defined by a field classification criterion.
///
class SHEAF_DLL_SPEC body_builder : public any
{

  // ===========================================================
  /// @name BODY_BUILDER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of local coordinate;
  /// the scalar type for the local coordinate vector space.
  ///
  typedef chart_point_coord_type coord_type;

  ///
  /// The type of component in the value;
  /// the scalar type in the fiber space.
  ///
  typedef sec_vd_value_type value_type;

  ///
  /// The type of degree of freedom.
  ///
  typedef sec_vd_dof_type dof_type;

  ///
  /// Default constructor.
  ///
  ///
  body_builder();

  // Copy constructor not implemented;
  // default memberwise copy will do.

  ///
  /// Destructor
  ///
  virtual ~body_builder();

  ///
  /// Builds the bodies defined by threshholds
  /// xlower and xupper in field xfield; auto_allocated.
  ///
  block<scoped_index>* build(field_vd& xfield,
			     value_type xlower,
			     value_type xupper);

  ///
  /// Builds the bodies defined by threshholds
  /// xlower and xupper in field xfield; pre_allocated.
  ///
  void build_pa(field_vd& xfield,
                value_type xlower,
                value_type xupper,
                block<scoped_index>& xresult);


private:

  ///
  /// Select the members of the evaluation subposet that
  /// satisfy the threshhold criterion.
  ///
  void select_evaluation_members(const field_vd& xfield,
                                 value_type xlower,
                                 value_type xupper,
                                 subposet& xselected);

  ///
  /// True if the field defined by xeval and xdofs falls
  /// within the interval defined by threshholds xlower and xupper.
  ///
  bool interval_contains_field(const section_evaluator& xeval,
                               const block<dof_type>& xdofs,
                               value_type xlower,
                               value_type xupper) const;

  ///
  /// Find the members of subposet xselected which form a
  /// contiguous neighborhood of the member with index xindex.
  ///
  void find_contiguous_neighborhood(const base_space_poset& xbase_space,
                                    subposet& xselected,
                                    const scoped_index& xindex,
                                    block<scoped_index>& xresult);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual body_builder* clone() const;

  // Assignment operator not implemented;
  // default memberwise assignment will do.

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef BODY_BUILDER_H
