// $RCSfile: poset_bounds.h,v $ $Revision: 1.19 $ $Date: 2013/01/12 17:17:36 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class poset_bounds

#ifndef POSET_BOUNDS_H
#define POSET_BOUNDS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POSET_BOUNDS_DESCRIPTOR_H
#include "poset_bounds_descriptor.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
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

#endif // ifndef POSET_BOUNDS_H






