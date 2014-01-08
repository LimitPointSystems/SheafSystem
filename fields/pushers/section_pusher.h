
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
/// Interface for class section_pusher.

#ifndef SECTION_PUSHER_H
#define SECTION_PUSHER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef FIELDS_H
#include "fields.h"
#endif

#ifndef SECTION_PUSHER_PULLBACK_ACTION_H
#include "section_pusher_pullback_action.h"
#endif

#ifndef SEC_ED_INVERTIBLE_H
#include "sec_ed_invertible.h"
#endif

namespace fiber_bundle
{
class eval_iterator;
class sec_rep_space;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;
 
class field_vd;
class field_vd;
class section_pusher_push_action;

///
/// The general section push-forward operator; moves sections from
/// one sec_rep_space to another using extension by zero to define
/// the target outside the domain of the source.
///
class SHEAF_DLL_SPEC section_pusher : public any
{

  // =============================================================================
  /// @name SECTION_PUSHER FACET
  // =============================================================================
  //@{

public:

  //@todo: Delete the field_vd versions of the next 2 constructors when
  //       field_vd is removed from the build (remove the implementations also).

  ///
  /// Creates the push-forward from the property space of
  /// xsrc to the property space of xdst.
  ///
  section_pusher(const field_vd& xsrc, const field_vd& xdst, bool xauto_access);

  /// @hack Had to comment out this constructor due to COM-466.
  /// @todo Reimplement once COM-466 is resolved.

//   ///
//   /// Creates the push-forward from the property space of
//   /// xsrc to a property space with the same fiber on the
//   /// base space of xdst_coords. Creates the range space
//   /// if it doesn't already exist.
//   ///
//   section_pusher(const field_vd& xsrc, const sec_ed& xdst_coords,
//                  bool xauto_access);

  ///
  /// Creates the push-forward from xdomain to xrange
  /// induced by xdomain_coord and xrange_coord.
  ///
  section_pusher(const sec_rep_space& xdomain,
                 const sec_rep_space& xrange,
                 const sec_ed& xdomain_coord,
                 const sec_ed& xrange_coord,
                 bool xauto_access);

  ///
  /// The domain of the push-forward map.
  ///
  const sec_rep_space& domain() const;

  ///
  /// The coordinates section for the domain.
  ///
  const geometry::sec_ed_invertible& domain_coords() const;

  ///
  /// The range of the push-forward map.
  ///
  const sec_rep_space& range() const;

  ///
  /// The coordinates section for the range.
  ///
  const sec_ed& range_coords() const;

  ///
  /// Pushes field xinput from sec_rep_space domain() to
  /// sec_rep_space range(), auto-allocated.
  ///
  sec_vd* push(const sec_vd& xinput, bool xauto_access);

  ///
  /// Pushes field xinput from sec_rep_space domain() to
  /// sec_rep_space range(), pre-allocated.
  ///
  void push_pa(const sec_vd& xinput, sec_vd& result, bool xauto_access);

  ///
  /// True if and only if xcoord and xspace have the same base space.
  ///
  bool same_base(const sec_ed& xcoord, const sec_rep_space& xspace) const;

  ///
  /// True if and only if xcoord and xspace have the same discretization.
  ///
  bool same_discretization(const sec_ed& xcoord, const sec_rep_space& xspace) const;

  ///
  /// True if and only if xspace1 and xspace2 have the same fiber type and dimension.
  ///
  bool same_fiber(const sec_rep_space& xspace1, const sec_rep_space& xspace2) const;

  ///
  /// Computes value of destination dofs where dst overlaps src.
  ///
  section_pusher_push_action& overlap_action() const;

  ///
  /// Overlap action if none specified by clinet.
  ///
  section_pusher_push_action& default_overlap_action() const;

  ///
  /// Computes value of destination dofs where dst does not overlap src.
  ///
  section_pusher_push_action& extension_action() const;

  ///
  /// Extension action if none specified by clinet.
  ///
  section_pusher_push_action& default_extension_action() const;

  ///
  /// Sets the overlap action to xoverlap_action.
  ///
  void put_overlap_action(section_pusher_push_action& xoverlap_action);

  ///
  /// Sets the extension action to xextension_action.
  ///
  void put_extension_action(section_pusher_push_action& xextension_cction);

protected:

  ///
  /// Default constructor; protected to prevent default construction.
  ///
  section_pusher();

private:

  ///
  /// The domain of the push-forward operator.
  ///
  sec_rep_space* _domain;

  ///
  /// The range of the push-forward operator.
  ///
  sec_rep_space* _range;

  ///
  /// The coordinates section for the domain.
  ///
  geometry::sec_ed_invertible _domain_coords;

  ///
  /// The coordinates section for the range.
  ///
  sec_ed _range_coords;

  ///
  /// The mapped type in the pullback map.
  ///
  typedef section_pusher_pullback_action::pb_type pb_type;

  ///
  /// The type for the domain evaluation member to range pullback map.
  ///
  typedef section_pusher_pullback_action::pb_map_type pb_map_type;

  ///
  /// The type of iterator for the pullback map.
  ///
  typedef section_pusher_pullback_action::pb_map_itr_type pb_map_itr_type;

  ///
  /// The type of iterator range for the pullback map.
  ///
  typedef section_pusher_pullback_action::pb_map_range_type pb_map_range_type;

  ///
  /// The domain evaluation member to range pullback map.
  ///
  block<pb_map_type*> _pb_maps;

  ///
  /// Make a subposet in range().base() which is
  /// an approximation to the monovalent subposet
  /// in domain.rep() and has the same name.
  /// If xis_ext, use the extension approximation,
  /// otherwise, use the contraction approximation.
  ///
  virtual void make_range_monovalent_subposet(bool xis_ext);

  ///
  /// Pulls the range disc back into the domain
  /// for monosection source coordinates and monosection source property
  ///
  void pull_back_range_disc_mono_mono();

  ///
  /// Pulls the range disc back into the domain
  /// for monosection source coordinates and multisection source property
  ///
  void pull_back_range_disc_mono_multi();

  ///
  /// Pulls the range disc back into the domain
  /// for multisection source coordinates and monosection source property
  ///
  void pull_back_range_disc_multi_mono();

  ///
  /// The typeof map from evaluation subposet member ids to branch base space ids.
  ///
  typedef SHEAF_UNORDERED_NAMESPACE::unordered_multimap<pod_index_type, scoped_index> chart_to_branch_map_type;

  ///
  /// Creates a map from evaluation subposet member ids to branch base space ids.
  ///
  chart_to_branch_map_type _chart_to_branch_map;

  ///
  /// The poset id of the first branch.
  ///
  scoped_index _first_branch;

  ///
  /// Allocates the branch pullback maps and
  /// populates the chart to branch map.
  ///
  void make_maps(const sec_vd& xinput);

  ///
  /// Deallocates the branch pullback maps and
  /// depopulates the chart to branch map.
  ///
  void clear_maps();

  ///
  /// The fiber dimension of the src and dst property.
  ///
  int _prop_df;

  ///
  /// The base dimension of the src.
  ///
  int _src_db;

  ///
  /// A buffer for gathering src dofs of an evaluation member.
  ///
  block<sec_vd_dof_type> _src_dofs;

  ///
  /// A buffer for the src value at a dst discretization member.
  ///
  block<sec_vd_dof_type> _src_value;

  ///
  /// A buffer for computing dst dofs of a discretization member.
  ///
  block<sec_vd_dof_type> _dst_dofs;

  ///
  /// Defines the part of the dst that overlaps the src;
  /// pushes the src to the dst
  ///
  void define_overlap(const sec_vd& xinput, sec_vd& xresult);

  ///
  /// Pushes the current evaluation member of xeval_itr to the destination.
  ///
  void push_eval_mbr(const eval_iterator& xeval_itr, const sec_vd& xinput,
                     sec_vd& xresult);

  ///
  /// Defines the part of the dst that does not over lap the src.
  ///
  void define_extension(sec_vd& xresult);

  ///
  /// Computes value of destination dofs where dst overlaps src.
  ///
  section_pusher_push_action* _overlap_action;

  ///
  /// Overlap action if none specified by user.
  ///
  section_pusher_push_action* _default_overlap_action;

  ///
  /// Computes value of destination dofs where dst does not overlap src.
  ///
  section_pusher_push_action* _extension_action;

  ///
  /// Extension action if none specified by user.
  ///
  section_pusher_push_action* _default_extension_action;

  ///
  /// Performs initialization common to several constructors.
  ///
  void initialize();

  //@}


  // =============================================================================
  /// @name ANY FACET
  // =============================================================================
  //@{

public:

  ///
  /// Copy constructor.
  ///
  section_pusher(const section_pusher& xother);

  ///
  /// Destructor.
  ///
  virtual ~section_pusher();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef SECTION_PUSHER_H
