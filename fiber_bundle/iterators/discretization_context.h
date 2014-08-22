
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
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

// Interface for class discretization_context

#ifndef DISCRETIZATION_CONTEXT_H
#define DISCRETIZATION_CONTEXT_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_CHART_POINT_3D_H
#include "ComLimitPoint/fiber_bundle/chart_point_3d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_FIBER_BUNDLE_H
#include "ComLimitPoint/fiber_bundle/fiber_bundle.h"
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
std::ostream& operator<<(std::ostream& xos, const discretization_context& xc);

///
/// The deep size of the referenced object of type discretization_context.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const discretization_context& xc, bool xinclude_shallow = true);



} // namespace fiber_bundle

#endif // ifndef DISCRETIZATION_CONTEXT_H
