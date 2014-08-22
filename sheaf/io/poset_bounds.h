
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

// Interface for class poset_bounds

#ifndef COM_LIMITPOINT_SHEAF_POSET_BOUNDS_H
#define COM_LIMITPOINT_SHEAF_POSET_BOUNDS_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ANY_H
#include "ComLimitPoint/sheaf/any.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_BOUNDS_DESCRIPTOR_H
#include "ComLimitPoint/sheaf/poset_bounds_descriptor.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ZN_TO_BOOL_H
#include "ComLimitPoint/sheaf/zn_to_bool.h"
#endif

namespace sheaf
{

class schema_poset_member;
class poset_state_handle;
class index_iterator;  

///
/// A (lower, upper) bounds pair for a poset.
/// Specifies a portion of a poset for a bounded i/o operation.
///
class SHEAF_DLL_SPEC poset_bounds : public any
{

public:

  // ===========================================================
  // ANY FACET
  // ===========================================================

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual poset_bounds* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // ===========================================================
  // POSET_BOUNDS FACET
  // ===========================================================

  /// @hack the interface to this class has become a kluge
  /// due to two influences:
  /// (i) the product subposet hack, and
  /// (ii) an unsuccessful attempt to deal efficiently with
  ///     singleton subposets.

  ///
  /// Default constructor.
  ///
  poset_bounds();

  ///
  /// Copy constructor.
  ///
  poset_bounds(const poset_bounds& xother);

  ///
  /// Creates an instance to math descriptor xdesc.
  ///
  poset_bounds(const poset_bounds_descriptor& xdesc);

  ///
  /// Destructor
  ///
  virtual ~poset_bounds();

  ///
  /// A descriptor for this.
  ///
  virtual poset_bounds_descriptor descriptor() const;

  ///
  /// The specification mode.
  ///
  poset_bounds_descriptor::specification_mode mode() const;

  ///
  /// The index of the lower bound member,
  /// if the lower bound contains a single member.
  ///
  pod_index_type lb_id() const;

  ///
  /// Sets the index of the lower bound member to xlb_ib,
  /// if the lower bound contains a single member.
  ///
  ///
  void put_lb_id(pod_index_type xlb_id);

  ///
  /// Sets the index of the lower bound member to xlb_ib,
  /// if the lower bound contains a single member.
  ///
  ///
  void put_lb_id(const scoped_index& xlb_id);

  ///
  /// True if the lower bound contains a single member.
  ///
  bool lb_is_singleton() const;

  ///
  /// True if the lower bound is not the bottom.
  ///
  bool bounded_below() const;

  ///
  /// The index of the upper bound member,
  /// if the upper bound contains a single member.
  ///
  pod_index_type ub_id() const;

  ///
  /// Sets the index of the upper bound member to xub_ib,
  /// if the upper bound contains a single member.
  ///
  ///
  void put_ub_id(pod_index_type xub_id);

  ///
  /// Sets the index of the upper bound member to xub_ib,
  /// if the upper bound contains a single member.
  ///
  ///
  void put_ub_id(const scoped_index& xub_id);

  ///
  /// True if the upper bound contains a single member.
  ///
  bool ub_is_singleton() const;

  ///
  /// True if the join of the members of the upper
  /// bound is equal to the external schema.
  ///
  bool ub_is_decomposition() const;

  ///
  /// True if the upper bound is not the top.
  ///
  bool bounded_above() const;

protected:

  ///
  /// A descriptor for this.
  ///
  poset_bounds_descriptor _descriptor;

  ///
  /// The lower bound.
  ///
  zn_to_bool* _lb;

  ///
  /// True if the lower bound contains a single member.
  ///
  bool _lb_is_singleton;

  ///
  /// True if the lower bound is not the bottom.
  ///
  bool _bounded_below;

  ///
  /// The upper bound.
  ///
  zn_to_bool* _ub;

  ///
  /// True if the upper bound contains a single member.
  ///
  bool _ub_is_singleton;

  ///
  /// True if the upper bound is not the top.
  ///
  bool _bounded_above;
};

} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_POSET_BOUNDS_H






