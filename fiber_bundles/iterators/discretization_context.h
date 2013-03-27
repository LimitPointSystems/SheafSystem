// $RCSfile: discretization_context.h,v $ $Revision: 1.12 $ $Date: 2013/01/12 17:17:08 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class discretization_context

#ifndef DISCRETIZATION_CONTEXT_H
#define DISCRETIZATION_CONTEXT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef CHART_POINT_3D_H
#include "chart_point_3d.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

namespace fiber_bundle
{

///
/// A context for discretization members. Intended for implementing various
/// iterators, especially concurrent iterations over multiple sections.
///
class SHEAF_DLL_SPEC discretization_context
{
public:
  ///
  /// The eval member the disc member is contained in.
  ///
  scoped_index eval_id;

  ///
  /// The local index of the disc member with respect to the eval member.
  ///
  int local_id;

  ///
  /// The global index of the disc member.
  ///
  scoped_index disc_id;

  ///
  /// The upper bound on th values array.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {values_ub = 3};  

  ///
  /// The values of another section (typically the global coordinates)
  /// at this disc point.
  ///
  sec_vd_value_type values[values_ub];
};


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
///
/// Insert discretization_context xc into ostream& xos.
///

SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const discretization_context& xc);

///
/// The deep size of the referenced object of type discretization_context.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const discretization_context& xc, bool xinclude_shallow = true);



} // namespace fiber_bundle

#endif // ifndef DISCRETIZATION_CONTEXT_H
