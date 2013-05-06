
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class POSET_POWERSET_STATE

#ifndef POSET_POWERSET_STATE_H
#define POSET_POWERSET_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef INDEX_SPACE_FAMILY_H
#include "index_space_family.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

#ifndef SUBPOSET_STATE_H
#include "subposet_state.h"
#endif

#ifndef NAME_MULTIMAP_H
#include "name_multimap.h"
#endif

namespace sheaf
{

// Forward declaration to support friend declaration.
SHEAF_DLL_SPEC ostream & operator << (ostream &os, const poset_powerset_state& p);

class arg_list;

///
/// The set of subsets of a poset.
///
class SHEAF_DLL_SPEC poset_powerset_state : public any
{
  friend class poset_state_handle;
  friend class subposet;
  friend class storage_agent; // needs to create an id space.
  friend class poset_scaffold; // needs to create an id space.
  friend SHEAF_DLL_SPEC ostream & operator << (ostream &os, const poset_powerset_state& p);
  friend SHEAF_DLL_SPEC size_t deep_size(const poset_powerset_state& xp, bool xinclude_shallow);

  // ===========================================================
  /// @name CANONICAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with initial space for xcapacity
  /// subposets each of which has an index upper bound xsubposet_member_index_ub.
  ///
  poset_powerset_state(size_type xcapacity, const scoped_index& xsubposet_member_index_ub);

  ///
  /// Destructor.
  ///
  ~poset_powerset_state();

protected:

private:

  //@}


  // ===========================================================
  /// @name SUBPOSETS FACET
  // ===========================================================
  //@{

public:

  ///
  /// The subposet with index xindex (mutable version).
  ///
  subposet_state& member(pod_index_type xindex);

  ///
  /// The subposet with index xindex (mutable version).
  ///
  subposet_state& member(const scoped_index& xindex);

  ///
  /// The subposet with index xindex (const version).
  ///
  const subposet_state& member(pod_index_type xindex) const;

  ///
  /// The subposet with index xindex (const version).
  ///
  const subposet_state& member(const scoped_index& xindex) const;

  ///
  /// Allocate a new subposet. If xinitialize, make the subposet empty,
  ///
  pod_index_type new_subposet(bool xinitializ);

  ///
  /// Allocate a new subposet. If xinitialize, make the subposet empty,
  ///
  void new_subposet(bool xinitialize, scoped_index& xresult);

  ///
  /// Allocate a new subposet with members xmembers.
  ///
  pod_index_type new_subposet(const block<pod_index_type>& xmembers);

  ///
  /// Allocate a new subposet with members xmembers.
  ///
  void new_subposet(const block<scoped_index>& xmembers,
		    scoped_index& xresult);

  ///
  /// Deallocate the subposet with index xindex
  ///
  void delete_subposet(pod_index_type xindex);

  ///
  /// Deallocate the subposet with index xindex
  ///
  void delete_subposet(const scoped_index& xindex);

  ///
  /// The upper bound on the subposet index.
  ///
  const scoped_index& subposet_index_ub() const;

  ///
  /// The number of subposets.
  ///
  size_type subposet_ct() const;

  ///
  /// Allocates an id space iterator over the subposet ids from the
  /// iterator pool.
  ///
  index_space_iterator& get_subposet_id_space_iterator() const;

  ///
  /// Returns the id space iterator xitr to the subposet iterator pool.
  ///
  void release_subposet_id_space_iterator(index_space_iterator& xitr) const;

  ///
  /// True if and only if there exists a subposet with index xindex.
  ///
  bool contains_subposet(pod_index_type xindex) const;

  ///
  /// True if and only if there exists a subposet with index xindex.
  ///
  bool contains_subposet(const scoped_index& xindex) const;

protected:

private:

  ///
  /// The type of initialization policy for the subposet block.
  ///
  typedef zero_block_initialization_policy<subposet_state*> subposets_init_type;

  ///
  /// The type of subposet block.
  ///
  typedef auto_block<subposet_state*, subposets_init_type> subposets_type;

  ///
  /// Collection of subposets.
  ///
  subposets_type _subposets;

  ///
  /// The upper bound of the subposet index.
  ///
  scoped_index _subposet_index_ub;  

  //@}


  // ===========================================================
  /// @name ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Collection of id spaces for this poset powerset.
  ///
  const index_space_family& id_spaces() const;

  ///
  /// Hub id space for this poset powerset.
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

protected:

private:

  ///
  /// Collection of id spaces for this poset.
  ///
  index_space_family _id_spaces;

  //@}


  // ===========================================================
  /// @name SUBPOSET NAME FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of the subposet_name_map.
  ///
  typedef name_multimap subposet_name_map_type;

  ///
  /// Bi-directional map between subposet names and indices
  ///
  subposet_name_map_type& subposet_name_map();

  ///
  /// Bi-directional map between subposet names and indices; const version
  ///
  const subposet_name_map_type& subposet_name_map() const;

protected:

private:

  ///
  /// Bi-directional map between subposet names and indices
  ///
  subposet_name_map_type _subposet_name_map;

  //@}


  // ===========================================================
  /// @name SUBPOSET MEMBERSHIP FACET
  // ===========================================================
  //@{

public:

  ///
  /// Upper bound of member index in each subposet.
  ///
  const scoped_index& subposet_member_index_ub() const;

  ///
  /// Sets the upper bound of member index in each subposet to xub.
  ///
  void put_subposet_member_index_ub(const scoped_index& xub);

  ///
  /// True, if the subposet with index xindex is a dofs subposet
  ///
  bool is_dof_subposet(pod_index_type xindex) const;

  ///
  /// True, if the subposet with index xindex is a dofs subposet
  ///
  bool is_dof_subposet(const scoped_index& xindex) const;

  ///
  /// Removes the poset member with index xindex from all subposets.
  ///
  void delete_poset_member(pod_index_type xindex);

  ///
  /// Removes the poset member with index xindex from all subposets.
  ///
  void delete_poset_member(const scoped_index& xindex);

  ///
  /// True if and only if the subposet with index xsubposet_index
  /// contains the member with index xmbr_index.
  ///
  bool subposet_contains_member(pod_index_type xsubposet_index,
                                pod_index_type xmbr_index) const;

  ///
  /// True if and only if the subposet with index xsubposet_index
  /// contains the member with index xmbr_index.
  ///
  bool subposet_contains_member(const scoped_index& xsubposet_index,
                                const scoped_index& xmbr_index) const;

protected:

private:

  // Upper bound for member index in all subposets.

  scoped_index _subposet_member_index_ub;

  //@}


  // ===========================================================
  /// @name STANDARD SUBPOSETS FACET
  // ===========================================================
  //@{

public:

  ///
  /// The coarsest common refinement of all versions of this poset (mutable version).
  ///
  subposet& coarsest_common_refinement();

  ///
  /// The coarsest common refinement of all versions of this poset (const version).
  ///
  const subposet& coarsest_common_refinement() const;

  ///
  /// The jims of the coarsest_common_refinement (mutable version).
  ///
  subposet& coarsest_common_refinement_jims();

  ///
  /// The jims of the coarsest_common_refinement (const version).
  ///
  const subposet& coarsest_common_refinement_jims() const;

  ///
  /// The members of the current version of this poset.
  ///
  subposet& whole();

  ///
  /// The jims of the current version of this poset.
  ///
  subposet& jims();

  ///
  /// The table dof subposet when this poset is used as a schema (mutable version).
  ///
  subposet& table_dof_subposet();

  ///
  /// The table dof subposet when this poset is used as a schema (const version).
  ///
  const subposet& table_dof_subposet() const;

  ///
  /// The row dof subposet when this poset is used as a schema (mutable version).
  ///
  subposet& row_dof_subposet();

  ///
  /// The row dof subposet when this poset is used as a schema (const version).
  ///
  const subposet& row_dof_subposet() const;

  ///
  /// The number of standard subposets automatically
  /// allocated by the poset handle constructor.
  ///
  int standard_subposet_ct() const;

  ///
  /// Put the number of standard subposets automatically
  /// allocated by the poset handle constructor.
  ///
  void put_standard_subposet_ct(int xct);

protected:

private:

  ///
  /// The coarsest common refinement of all versions of this poset.
  ///
  subposet _coarsest_common_refinement;

  ///
  /// The jims of the coarsest_common_refinement.
  ///
  subposet _coarsest_common_refinement_jims;

  ///
  /// The members of the current version of this poset.
  ///
  subposet _whole;

  ///
  /// The jims of the current version of this poset.
  ///
  subposet _jims;

  ///
  /// The table dof subposet when this poset is used as a schema.
  ///
  subposet _table_dof_subposet;

  ///
  /// The row dof subposet when this poset is used as a schema.
  ///
  subposet _row_dof_subposet;

  ///
  /// The number of standard subposets initially allocated
  /// by the poset constructor;
  ///
  int _standard_subposet_ct;

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
  virtual poset_powerset_state* clone() const;

  ///
  /// Class invariant
  ///
  bool invariant() const;

protected:

private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert poset_powerset_state& p into ostream& os.
///
SHEAF_DLL_SPEC ostream & operator << (ostream &os, const poset_powerset_state& p);

///
/// The deep size of the referenced object of type poset_powerset_state.
///
SHEAF_DLL_SPEC size_t deep_size(const poset_powerset_state& xp, bool xinclude_shallow = true);

} // namespace sheaf

#endif // ifndef POSET_POWERSET_STATE_H

