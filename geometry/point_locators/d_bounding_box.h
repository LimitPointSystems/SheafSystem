// $RCSfile: d_bounding_box.h,v $ $Revision: 1.6 $ $Date: 2013/01/12 17:17:30 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class d_bounding_box

#ifndef D_BOUNDING_BOX_H
#define D_BOUNDING_BOX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef D_BIN_COORDINATES_H
#include "d_bin_coordinates.h"
#endif

namespace fiber_bundle
{
class section_evaluator;
}

namespace geometry
{

using namespace sheaf;
using namespace fiber_bundle;
 
///
/// A bounding box that can be strung together into a list.
///
template <int DC, int DB>
class SHEAF_DLL_SPEC d_bounding_box
{
public:

  ///
  /// An unsigned integral type used to represent sizes and capacities.
  ///
  typedef sheaf::size_type size_type;


  // ===========================================================
  /// @name CANONICAL FACET
  // ===========================================================
  //@{

public:

  ///
  ///  Default constructor.
  ///
  d_bounding_box();

  ///
  /// Copy constructor.
  ///
  d_bounding_box(const d_bounding_box<DC, DB>& xbox);

  ///
  /// Assignment operator.
  ///
  d_bounding_box<DC, DB>& operator=(const d_bounding_box<DC, DB>& xbox);

  ///
  /// Destructor.
  ///
  ~d_bounding_box();

  ///
  /// Class invariant.
  ///
  bool invariant() const;

  ///
  /// Equality operator.
  ///
  bool operator==(const d_bounding_box<DC, DB>& xbox) const;

  //@}


  // ===========================================================
  /// @name D_BOUNDING_BOX FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this contains point xpt.
  ///
  bool contains_point(const d_bin_coordinates<DC, DB>& xpt) const;

  ///
  /// Insert this into stream xos.
  ///
  void to_stream(ostream& xos) const;

  ///
  /// The lower bound; the lower, left, front corner.
  ///
  const d_bin_coordinates<DC, DB>& lb() const;

  ///
  /// Copies the contents of xlb to lb().
  ///
  void put_lb(const d_bin_coordinates<DC, DB>& xlb);

  ///
  /// The upper bound; the upper, right, rear corner.
  ///
  const d_bin_coordinates<DC, DB>& ub() const;

  ///
  /// Copies the contents of xub to ub().
  ///
  void put_ub(const d_bin_coordinates<DC, DB>& xub);

  ///
  /// Index of the evaluation member this bounds.
  ///
  const scoped_index& member_id() const;

  ///
  /// Sets member_id() to xid.
  ///
  void put_member_id(const scoped_index& xid);

  ///
  /// Index of the branch that contains the evaluation member this bounds.
  ///
  const scoped_index& branch_id() const;

  ///
  /// Sets branch_id() to xid.
  ///
  void put_branch_id(const scoped_index& xid);

  ///
  /// Evaluator for the evaluation member this bounds.
  ///
  section_evaluator* evaluator() const;

  ///
  /// Sets evaluator() to xevaluator.
  ///
  void put_evaluator(section_evaluator* xevaluator);

  ///
  /// Index into the gathered dofs array for the evaluation member this bounds.
  ///
  size_type dofs_index() const;

  ///
  /// Sets dofs_index() to xindex.
  ///
  void put_dofs_index(size_type xindex);

  ///
  /// The number of dofs in the gathered dofs array
  /// for the evaluation member this bounds
  ///
  size_type dof_ct() const;

  ///
  /// Sets dof_ct() to xct.
  ///
  void put_dof_ct(size_type xct);

  ///
  /// The size of each side of the box; pre-allocated.
  ///
  void size_pa(d_bin_coordinates<DC, DB>& xresult) const;

  ///
  /// The number of spatial dimensions.
  ///
  static int dc();

private:

  ///
  /// The lower bound; the lower, left, front corner.
  ///
  d_bin_coordinates<DC, DB> _lb;

  ///
  /// The upper bound; the upper, right, rear corner.
  ///
  d_bin_coordinates<DC, DB> _ub;

  ///
  /// Index of the evaluation member this bounds.
  ///
  scoped_index _member_id;

  ///
  /// Index of the branch that contains the evaluation member this bounds.
  ///
  scoped_index _branch_id;

  ///
  /// Evaluator for the evaluation member this bounds.
  ///
  section_evaluator* _evaluator;

  ///
  /// Index into the gathered dofs array for the evaluation member this bounds.
  ///
  size_type _dofs_index;

  ///
  /// The number of dofs in the gathered dofs array
  /// for the evaluation member this bounds
  ///
  size_type _dof_ct;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert d_bounding_box& xbox into ostream& os.
///
template <int DC, int DB>
SHEAF_DLL_SPEC 
ostream&
operator<<(ostream& xos, const d_bounding_box<DC, DB>& xbox);
 
} // namespace geometry

#endif // D_BOUNDING_BOX_H
