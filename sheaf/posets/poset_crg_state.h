
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

/// @file
/// Interface for class poset_crg_state.

#ifndef COM_LIMITPOINT_SHEAF_POSET_CRG_STATE_H
#define COM_LIMITPOINT_SHEAF_POSET_CRG_STATE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ANY_H
#include "ComLimitPoint/sheaf/any.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_INDEX_SPACE_FAMILY_H
#include "ComLimitPoint/sheaf/index_space_family.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_NAME_MULTIMAP_H
#include "ComLimitPoint/sheaf/name_multimap.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POOL_H
#include "ComLimitPoint/sheaf/pool.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SCOPED_INDEX_H
#include "ComLimitPoint/sheaf/scoped_index.h"
#endif

#ifndef STD_UNORDERED_MAP_H
#include "std_unordered_map.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ZN_TO_BOOL_H
#include "ComLimitPoint/sheaf/zn_to_bool.h"
#endif

namespace sheaf
{

class mutable_index_space_handle;
class index_space_family;
class crg_interval;
class implicit_crg_interval;
class index_space_handle;
class poset_crg_state;
SHEAF_DLL_SPEC size_t deep_size(const poset_crg_state& xp, bool xinclude_shallow, size_t xresults[2]);

///
/// The data structure representing the cover relation graph of a poset.
///
class SHEAF_DLL_SPEC poset_crg_state : public any
{

  friend SHEAF_DLL_SPEC size_t deep_size(const poset_crg_state& xp, bool xinclude_shallow, size_t xresults[2]); 
  friend class poset_state_handle;
  friend class poset_state;
  friend class crg_interval; // cover_name
  friend class member_record_set; // explicit_down_set_members
  
  // ===========================================================
  /// @name POSET_CRG_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance.
  ///
  poset_crg_state();

  ///
  /// Destructor.
  ///
  ~poset_crg_state();

protected:

private:

  //@}


  // ===========================================================
  /// @name MEMBERSHIP (NODES) FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new member with explicit lower and upper cover.
  ///
  pod_index_type new_member();
 
  ///
  /// Create a new member with id xid and
  /// explicit lower and upper cover.
  ///
  void new_member(pod_index_type xid);

  ///
  /// Create a new bottom or top member.
  /// @hack Cartesian product subspace hack;
  /// intended only for use by section_space_schema_poset 
  /// constructor.
  ///
  void new_standard_member_hack(standard_member_index xid);

  ///
  /// Create an implicit interval of type xinterval_type with size xsize.
  ///
  pod_index_type new_member_interval(const std::string& xinterval_type, size_type xsize);

  ///
  /// Create an implicit interval beginning at xid,
  /// of type xinterval_type, and with size xsize.
  ///
  void new_member_interval(pod_index_type xid,
			   const std::string& xinterval_type, 
			   size_type xsize);

  ///
  /// Delete member with index xid.
  ///
  void delete_member(pod_index_type xid);

  ///
  /// Delete the entire implicit interval that contains
  /// the implicit member with index xid.
  ///
  void delete_interval(pod_index_type xid);

  ///
  /// The number of members.
  ///
  size_type member_ct() const;

  ///
  /// The number of standard members automatically
  /// allocated by the poset handle constructor (mutable version).
  ///
  size_type standard_member_ct();

  ///
  /// The number of standard members automatically
  /// allocated by the poset handle constructor (const version).
  ///
  size_type standard_member_ct() const;

  ///
  /// Put the number of standard members automatically
  /// allocated by the poset handle constructor.
  ///
  void put_standard_member_ct(size_type xct);

  ///
  /// The beginning of the member interval;
  /// members have indices in the interval [begin(), end()).
  ///
  const scoped_index& begin() const;

  ///
  /// The end of the member interval;
  /// members have indices in the interval [begin(), end()).
  ///
  const scoped_index& end() const;

  ///
  /// True if and only if there exists a member with index xid.
  ///
  bool contains_member(pod_index_type xid) const;

  ///
  /// True if and only if there exists an implicit member with index xid.
  /// A member is implicit if it has implicit covers. Note that an implicit
  /// member may also have explicit covers.
  ///
  bool contains_implicit_member(pod_index_type xid) const;

  ///
  /// True if and only if there exists an fully explicit member with index xid.
  /// A member is fully explicit if it is not implicit, that is, it does not
  /// have implicit covers.
  ///
  bool contains_explicit_member(pod_index_type xid) const;

  ///
  /// The interval for the member with index xid (const version).
  ///
  const crg_interval& interval(pod_index_type xid) const;

  ///
  /// The interval for the member with index xid (mutable version).
  ///
  crg_interval& interval(pod_index_type xid);

  ///
  /// The implicit interval for the member with index xid.
  /// Returns null, if no implicit interval exists.
  ///
  /// @deprecated Use interval(pod_index_type xid)
  ///
  implicit_crg_interval* implicit_member(pod_index_type xid) const;

protected:

  ///
  /// Initialize the upper and lower covers for member with index xid.
  ///
  /// @hack Cartesian product subspace hack;
  /// xstandard_member_hack argument is intended only for use by
  /// section_space_schema_poset constructor
  /// If xstandard_member_hack is true, only support covers for top and bottom.
  ///
  void initialize_member_covers(pod_index_type xid, bool xstandard_member_hack = false);

private:

  ///
  /// The lower bound on the member index.
  ///
  scoped_index _begin;

  ///
  /// The upper bound on the member index.
  ///
  scoped_index _end;  

  ///
  /// The number of members.
  ///
  size_type _member_ct;

  ///
  /// The number of standard members initially allocated
  /// by the poset constructor;
  ///
  size_type _standard_member_ct;

  //@}


  // ===========================================================
  /// @name ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Collection of id spaces for this poset.
  ///
  const index_space_family& id_spaces() const;

  ///
  /// Hub id space for this poset.
  ///
  const hub_index_space_handle& hub_id_space() const;

  ///
  /// A id in the hub id space;
  /// intended for copying to initialize ids
  /// to the hub id space.
  ///
  const scoped_index& hub_id() const;

  ///
  /// A id in the hub id space with pod xid.
  ///
  scoped_index hub_id(pod_index_type xid) const;

  ///
  /// Create a new gathered id space from the hub id space.
  /// If xexclude_bottom, construct the id space without BOTTOM_INDEX.
  ///
  const index_space_handle& new_gathered_hub_id_space(bool xexclude_bottom);

  ///
  /// Updates the gathered hub id space.
  ///
  void update_gathered_hub_id_space();

  ///
  /// The gathered hub id space.
  ///
  const index_space_handle& gathered_hub_id_space() const;

  ///
  /// True if there is a gathered hub id space.
  ///
  bool has_gathered_hub_id_space() const;

  ///
  /// True, if the gathered hub id space excludes BOTTOM_INDEX.
  ///
  bool gathered_hub_id_space_excludes_bottom() const;

protected:

private:

  ///
  /// Collection of id spaces for this poset.
  ///
  index_space_family _id_spaces;

  //@}


  // ===========================================================
  /// @name MEMBER NAME FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of the member_name_map.
  ///
  typedef name_multimap member_name_map_type;

  ///
  /// Bi-directional map between member names and indices
  ///
  member_name_map_type& member_name_map();

  ///
  /// Bi-directional map between member names and indices; const version
  ///
  const member_name_map_type& member_name_map() const;

protected:

private:

  ///
  /// Bi-directional map between member names and indices
  ///
  member_name_map_type _member_name_map;

  //@}


  // ===========================================================
  /// @name EDIT MODE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if jim editing is enabled.
  ///
  bool jim_edit_mode() const;

  ///
  /// Request jim editing be enabled.
  ///
  void request_jim_edit_mode();

  ///
  /// Request jim editing be disabled.
  ///
  void release_jim_edit_mode();

  ///
  /// Jim edit mode depth counter.
  ///
  int jim_edit_depth() const;

protected:

private:

  ///
  /// Jim edit mode depth counter.
  ///
  int _jim_edit_depth;

  //@}


  // ===========================================================
  /// @name COVER SET (LINKS) FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false)
  /// cover of the member with index xmbr_index is explicit.
   ///
  bool cover_is_explicit(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false)
  /// cover of the member with index xmbr_index is implicit.
  /// Note that a cover can be both explict and implicit.
  ///
  bool cover_is_implicit(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// The id for the lower (xlower true) or upper (xlower false) cover
  /// id space with index xmbr_index.
  ///
  pod_index_type cover_id_space_id(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// Allocates an handle for the lower (xlower true) or upper (xlower false)
  /// cover of member with index xmbr_index from the pool of id spaces.
  ///
  index_space_handle& get_cover_id_space(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// Allocates an handle of type handle_type for the lower (xlower true) or
  /// upper (xlower false) cover of member with index xmbr_index from
  /// the pool of id spaces.
  ///
  template <typename handle_type>
  handle_type& get_cover_id_space(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// True if a handle for the lower (xlower true) or upper (xlower false) cover id space
  /// of the member with hub id xmbr_index conforms to a handle of type handle_type.
  ///
  template<typename handle_type>
  bool cover_id_space_handle_conforms_to(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// Returns cover handle xcover_id_space to the pool of id spaces.
  ///
  void release_cover_id_space(index_space_handle& xcover_id_space) const;

  ///
  /// Allocates an iterator for for the lower (xlower true) or
  /// upper (xlower false) cover of member with index xmbr_index from
  /// the pool of id spaces.
  ///
  index_space_iterator& get_cover_id_space_iterator(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// Returns cover iterator xcover_itr to the pool of id spaces.
  ///
  void release_cover_id_space_iterator(index_space_iterator& xcover_itr) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover of the member
  /// with index xmbr_index is the domain of iterator xitr.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  bool cover_contains_iterator(bool xlower,
                               pod_index_type xmbr_index,
                               const index_space_iterator& xitr) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover of the member
  /// with index xmbr_index is empty.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  bool cover_is_empty(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover of the member
  /// with index xmbr_index contains exactly one member.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  bool cover_is_singleton(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// The number of members in the lower (xlower true) or
  /// upper (xlower false) cover of the member
  /// with index xmbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  size_type cover_ct(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false)
  /// cover of the member with index xmbr_index contains xother_mbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  bool cover_contains_member(bool xlower,
                             pod_index_type xmbr_index,
                             pod_index_type xother_mbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover of the member with
  /// index xmbr_index contains the same members as the
  /// lower or upper cover, respectively, of the member
  /// with index xother_mbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  bool cover_is_equal(bool xlower,
                      pod_index_type xmbr_index,
                      pod_index_type xother_mbr_index) const;

  ///
  /// The first member of the lower (xlower true) or upper (xlower false) cover
  /// of the member with index xmbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  pod_index_type first_cover_member(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// Inserts xother_mbr_index in the lower (xlower true) or
  /// upper (xlower false) cover of the member with index xmbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  void insert_cover_member(pod_index_type xother_mbr_index,
                           bool xlower,
                           pod_index_type xmbr_index);

  ///
  /// Inserts xother_mbr_index in the lower (xlower true) or
  /// upper (xlower false) cover of the member with index xmbr_index,
  /// at a position just before xitr. Increments xitr to the
  /// position after the inserted entry.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  void insert_cover_member(pod_index_type xother_mbr_index,
                           bool xlower,
                           pod_index_type xmbr_index,
                           index_space_iterator& xitr);

  ///
  /// Removes xother_mbr_index from the lower (xlower true) or
  /// upper (xlower false) cover of the member with index xmbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  void remove_cover_member(pod_index_type xother_mbr_index,
                           bool xlower,
                           pod_index_type xmbr_index);

  ///
  /// Removes the current item of xitr from the lower (xlower true) or
  /// upper (xlower false) cover of the member with index xmbr_index.
  /// If xitr is at the end, forces xitr.is_done().  Otherwise,
  /// increments xitr to the next position.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  void remove_cover_member(index_space_iterator& xitr,
                           bool xlower,
                           pod_index_type xmbr_index);

  ///
  /// Removes all members for which functor xfilter(xmbr.index().top_pod()) is true
  /// from the lower (xlower true) or upper (xlower false) cover
  /// of the member with index xmbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  template <typename filter_type>
  void remove_cover_members(const filter_type& xfilter,
			    bool xlower,
			    pod_index_type xmbr_index);

  ///
  /// Replaces xold_other_mbr_index with xnew_other_mbr_index in the lower (xlower true) or
  /// upper (xlower false) cover of the member with index xmbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  void replace_cover_member(pod_index_type xold_other_mbr_index,
			    pod_index_type xnew_other_mbr_index,
			    bool xlower,
			    pod_index_type xmbr_index);

  ///
  /// Clears the lower (xlower true) or upper (xlower false)
  /// cover of the member with index xmbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  void clear_cover(bool xlower, pod_index_type xmbr_index);

  ///
  /// Copies the lower (xlower true) or upper (xlower false) cover
  /// from the member with index xmbr_index to the member with
  /// index xother_mbr_index.
  ///
  /// @deprecated Should use get_cover_id_space.
  ///
  void copy_cover(bool xlower,
                  pod_index_type xmbr_index,
                  pod_index_type xother_mbr_index);

  ///
  /// Appends the interval of ids [xbegin, xend) to the upper cover
  /// of bottom.  This function is intended to use by block
  /// members that store there vertices in a gathered id space
  ///
  void append_upper_cover_of_bottom(pod_index_type xmbr_begin,
				    pod_index_type xmbr_end);

protected:

  ///
  /// The explicit lower (xlower true) or upper (xlower false) cover id space
  /// of the member with index xmbr_index; creates an explict cover id space
  /// if the cover id space is not already explicit and, if xinitialize,
  /// initializes it with the contents of the implicit cover id space, if any.
  /// Returns the space id of the explicit cover.
  ///
  pod_index_type force_explicit_cover(bool xlower,
				      pod_index_type xmbr_index,
				      bool xinitialize = true);

private:

  ///
  /// The type of map from id to explicit dof_tuple_id.
  ///
  typedef unordered::unordered_map<pod_index_type, pod_index_type> explicit_dof_tuple_map_type;

  ///
  /// The map from id to explicit dof_tuple_id.
  ///
  explicit_dof_tuple_map_type _explicit_dof_tuple_map;

  ///
  /// The type of the interval member map.
  ///
  typedef std::map<pod_index_type, crg_interval*> interval_map_type;

  ///
  /// The map from ids to intervals.
  ///
  interval_map_type _interval_map;

  //@}


  // ===========================================================
  /// @name DOF_TUPLE_ID FACET
  // ===========================================================
  //@{

public:

  ///
  /// The dof tuple index of the member with index xmbr_index;
  /// invalid if xmbr_index has not dof tuple.
  ///
  pod_index_type member_dof_tuple_id(pod_index_type xmbr_index) const;

  ///
  /// Sets the dof tuple index of the member with
  /// index xmbr_index to xdof_tuple_id.
  ///
  void put_member_dof_tuple_id(pod_index_type xmbr_index,
                               pod_index_type xdof_tuple_id);

protected:

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Removes members of the cover that are no longer members of the crg.
  ///
  void clean_cover(bool xlower, pod_index_type xmbr_index);

  ///
  /// The explicit members in the downset of the interval xinterval.
  ///
  void explicit_down_set_members(const implicit_crg_interval& xinterval,
				 std::set<pod_index_type>& result) const;

protected:

  ///
  /// The explicit members in the downset of member with index xmbr_index.
  ///
  void explicit_down_set_members(pod_index_type xmbr_index,
				 std::set<pod_index_type>& result) const;

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to current
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual poset_crg_state* clone() const;

  ///
  /// Class invariant
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
/// Insert poset_crg_state& p into ostream& os.
///
SHEAF_DLL_SPEC std::ostream & operator << (std::ostream &os, const poset_crg_state& p);

///
/// The deep size of the referenced object of type poset_crg_state;
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC size_t deep_size(const sheaf::poset_crg_state& xp, bool xinclude_shallow = true, size_t xresults[2] = 0);

} // namespace sheaf 



#endif // ifndef COM_LIMITPOINT_SHEAF_POSET_CRG_STATE_H

