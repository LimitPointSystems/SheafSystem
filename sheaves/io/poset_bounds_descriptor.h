// $RCSfile: poset_bounds_descriptor.h,v $ $Revision: 1.23 $ $Date: 2013/01/12 17:17:36 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class poset_bounds_descriptor

#ifndef POSET_BOUNDS_DESCRIPTOR_H
#define POSET_BOUNDS_DESCRIPTOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

namespace sheaf
{

class poset_bounds;

///
/// A description of a (lower, upper) bounds pair for a poset.
/// Specifies a portion of a poset for a bounded i/o operation.
///
class SHEAF_DLL_SPEC poset_bounds_descriptor : public any
{

  friend class poset_bounds; // To get default constructor.

public:

  ///
  /// Copy constructor
  ///
  ///
  poset_bounds_descriptor(const poset_bounds_descriptor& xother);

  ///
  /// Assignment operator.
  ///
  poset_bounds_descriptor& operator=(const poset_bounds_descriptor& xother);

  ///
  /// Comparison operator.
  ///
  bool operator==(const poset_bounds_descriptor& xother) const;

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual poset_bounds_descriptor* clone() const;

  ///
  /// Destructor
  ///
  virtual ~poset_bounds_descriptor();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // POSET_BOUNDS_DESCRIPTOR FACET


  ///
  /// Enumeration for mode of specifying the lower and upper bounds.
  ///
  enum specification_mode
  {
    MEMBER_MEMBER,     // lb = member,   ub = member
    MEMBER_SUBPOSET,   // lb = member,   ub = subposet
    SUBPOSET_MEMBER,   // lb = subposet, ub = member
    SUBPOSET_SUBPOSET, // lb = subposet, ub = subposet
    NOT_A_MODE
  };

  ///
  /// Converts mode xmode to an int.
  ///
  static int mode_to_int(specification_mode xmode);

  ///
  /// Converts int xmode to a mode.
  ///
  static specification_mode int_to_mode(int xmode);

  ///
  /// Constructs an instance with mode() xmode, lb_id() xlbid, and ub_id() xub_id.
  ///
  poset_bounds_descriptor(specification_mode xmode,
                          pod_index_type xlb_id,
                          pod_index_type xub_id);

  ///
  /// Constructs an instance with mode() xmode, lb_id() xlbid, and ub_id() xub_id.
  ///
  poset_bounds_descriptor(specification_mode xmode,
			  const scoped_index& xlb_id,
			  const scoped_index& xub_id);

  ///
  /// Specification mode for this.
  ///
  specification_mode mode() const;

  ///
  /// True if mode == MEMBER_MEMBER or MEMBER_SUBPOSET.
  ///
  bool lb_is_member() const;

  ///
  /// True if mode == MEMBER_MEMBER or SUBPOSET_MEMBER.
  ///
  bool ub_is_member() const;

  ///
  /// The index of the lower bound.
  ///
  pod_index_type lb_id() const;

  ///
  /// Sets the index of the lower bound to xlb_id.
  ///
  void put_lb_id(pod_index_type xlb_id);

  ///
  /// Sets the index of the lower bound to xlb_id.
  ///
  void put_lb_id(const scoped_index& xlb_id);

  ///
  /// The index of the upper bound member,
  /// if the upper bound contains a single member.
  ///
  pod_index_type ub_id() const;

  ///
  /// Sets the index of the upper bound to xub_id.
  ///
  void put_ub_id(pod_index_type xub_id);

  ///
  /// Sets the index of the upper bound to xub_id.
  ///
  void put_ub_id(const scoped_index& xub_id);
  ///
  /// True if the lower bound member or subposet mentioned
  /// in this descriptor exists in xposet.
  ///
  bool lb_is_valid_for(const poset_state_handle& xposet) const;

  ///
  /// True if the upper bound member or subposet mentioned
  /// in this descriptor exists in xposet.
  ///
  bool ub_is_valid_for(const poset_state_handle& xposet) const;

  ///
  /// True if the members and/or subposets mentioned
  /// in this descriptor exist in xposet.
  ///
  bool is_valid_for(const poset_state_handle& xposet) const;

  ///
  /// True if lb_is_member() and lb_id() is sheaf_constants::BOTTOM_INDEX.
  ///
  bool lb_member_is_bottom() const;

  ///
  /// True if ub_is_member() and ub_id() is not sheaf_constants::TOP_INDEX.
  ///
  bool ub_member_is_not_top() const;

  ///
  /// An instance with lb() == {bottom} and ub() == {top}.
  ///
  static const poset_bounds_descriptor& BOTTOM_TOP;

  ///
  /// An instance with lb() == {bottom} and ub() == {bottom}.
  ///
  static const poset_bounds_descriptor& BOTTOM_BOTTOM;

protected:

  ///
  /// Default constructor.
  ///
  poset_bounds_descriptor();


private:

  // PRIVATE MEMBERS

  ///
  /// Specification mode for this.
  ///
  specification_mode _mode;

  ///
  /// The index of the lower bound.
  ///
  pod_index_type _lb_id;

  ///
  /// The index of the upper bound member.
  /// Implies a singleton subposet to which ub()
  /// will be bound when the poset state is accessible.
  ///
  pod_index_type _ub_id;
};

} // namespace sheaf

#endif // ifndef POSET_BOUNDS_DESCRIPTOR_H







