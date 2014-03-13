
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
/// Interface for class poset_state_handle.

#ifndef POSET_STATE_HANDLE_H
#define POSET_STATE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ABSTRACT_POSET_MEMBER_H
#include "abstract_poset_member.h"
#endif

#ifndef POOL_H
#include "pool.h"
#endif

#ifndef POSET_CRG_STATE_H
#include "poset_crg_state.h"
#endif

#ifndef POSET_MEMBER_H
#include "poset_member.h"
#endif

#ifndef POSET_POWERSET_STATE_H
#include "poset_powerset_state.h"
#endif

#ifndef POSET_STATE_H
#include "poset_state.h"
#endif

#ifndef POSET_TABLE_STATE_H
#include "poset_table_state.h"
#endif

#ifndef READ_WRITE_MONITOR_HANDLE_H
#include "read_write_monitor_handle.h"
#endif

#ifndef SCHEMA_POSET_MEMBER_H
#include "schema_poset_member.h"
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

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

#ifndef NAME_MULTIMAP_H
#include "name_multimap.h"
#endif


namespace sheaf
{

template <typename T> class block;
template <typename T> class depth_first_itr;
class namespace_poset;
class primitives_poset;
class depth_first_iterator;
class index_equivalence_iterator;
class index_map;
class implict_crg_interval;
class index_iterator;
class namespace_poset_member;
class poset_bounds;
class poset_component;
class poset_dof_map;
class poset_handle_factory;
class subposet_names_record;
class storage_agent;
class subposet_state;
class zn_to_bool;

// Following functions must be forward declared before friend statement.

///
/// Insert poset_state_handle& p into ostream& os.
///
SHEAF_DLL_SPEC
std::ostream & operator << (std::ostream &os, const poset_state_handle& p);

///
/// The deep size of the referenced object of type poset_state_handle.
/// if xinclude_shallow, add the sizeof xp to the result.
/// if xresults is not null, the deep size of the poset_state parts returned;
/// xresults[0] is the deep_size of poset_crg_state,
/// xresults[1] is the deep_size of index_space_family,
/// xresults[2] is the deep_size of poset_powerset_state,
/// xresults[3] is the deep_size of poset_table_state.
///
SHEAF_DLL_SPEC
size_t deep_size(const poset_state_handle& xp,
		 bool xinclude_shallow = true,
		 size_t xresults[4] = 0);

///
/// A client handle for a general, abstract partially order set.
///
class SHEAF_DLL_SPEC poset_state_handle : public read_write_monitor_handle
{
  friend class abstract_poset_member;
  friend class array_poset_dof_map;
  friend class block_poset_builder;
  friend class depth_first_iterator;  // needs powerset_member()
  template<typename T>
  friend class depth_first_itr; // needs powerset_member()
  friend class dof_tuple_record_set; // needs initialize_dof_id_space()
  friend class member_record; // needs crg()
  friend class member_record_set; // needs crg()
  friend class namespace_poset; // needs state functions.
  friend class poset_component; // needs version_to_name(), state_obj()
  friend class poset_handle_factory; // needs destructor.
  friend class poset_joiner; // needs cross_link()
  friend class poset_scaffold; // needs member_name_map(), table()
  friend class poset_slicer; // needs contains_members(list_cover_set*)
  friend class primitives_poset_dof_map; // needs state_obj()
  friend class schema_poset_member;
  friend class storage_agent; // needs powerset() and table()
  friend class subposet_joiner; // needs cross_link()
  friend class subposet_names_record; // needs version_to_name()
  friend class table_dof_tuple_record; // needs new_state()
  friend SHEAF_DLL_SPEC std::ostream & sheaf::operator << (std::ostream &os, const poset_state_handle& p); // needs state_obj()
  friend SHEAF_DLL_SPEC size_t sheaf::deep_size(const poset_state_handle& xp, bool xinclude_shallow, size_t xresults[4]);

  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Creates an unattached handle of type xclass_name, if a prototype
  /// of that name exists, otherwise of type xsheaf_base_class_id.
  ///
  /// @todo Move this functionality to namespace_poset.
  ///
  static poset_state_handle*
  new_poset_handle(const std::string& xclass_name, poset_type xsheaf_base_class_id);

  ///
  /// The poset handle factory.
  ///
  static poset_handle_factory& factory();

  ///
  /// Default constructor
  ///
  poset_state_handle();

  ///
  /// Destructor
  ///
  virtual ~poset_state_handle();

  ///
  /// Covariant constructor
  ///
  poset_state_handle(abstract_poset_member* xtop, abstract_poset_member* xbottom);

  ///
  /// Copy constructor; disabled
  ///
  poset_state_handle(const poset_state_handle& xother) { };

  ///
  /// Assignment operator; disabled.
  ///
  poset_state_handle& operator=(const poset_state_handle& xother)
  {
    return const_cast<poset_state_handle&>(*this);
  };

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  /// @issue visibility of jim edit mode.
  /// begin/end_jim_edit really shouldn't be public, because they are inherited
  /// by the immutable posets primitives_poset and primitives_poset_schema.
  /// But KCC seems to be unhappy about a public virtual function in class poset
  /// overriding a private virtual function from a base class, so we've
  /// made them public here.
  /// @todo resolve this issue either by introducing an immutable base class
  /// or implementing const correctness so primitives_poset etc can be const.

  ///
  /// Allow editing of jims and jim order relation.
  ///
  virtual void begin_jim_edit_mode(bool xauto_access = true);

  ///
  /// Prevent editing of jims and jim order relation.
  ///
  virtual void end_jim_edit_mode(bool xensure_lattice_invariant = true,
                                 bool xauto_access = true);

  ///
  /// True if editing jims and jim order relation is allowed
  ///
  bool in_jim_edit_mode() const;

  ///
  /// Number of times begin_jim edit_mode has been called
  /// without matching end_jim_edit_mode.
  ///
  int jim_edit_depth(bool xauto_access) const;

  ///
  /// True if this has a corresponding member in a name space,
  /// but is not yet attached to a state. (This condition implies
  /// the name space has been imported from some external source,
  /// but the poset has not yet been imported.)
  ///
  bool is_external() const;

  ///
  /// Get read access to the state associated with this.
  ///
  virtual void get_read_access() const;

  ///
  /// Get read write access to the state associated with this.  If
  /// release_read_only_access is requested, read only access will be
  /// released then read_write_access will be requested, finally the
  /// same level of read_access as before will be requested.
  ///
  virtual void get_read_write_access(bool xrelease_read_only_access = false);

  ///
  /// Release access. If xall is true, release all levels of access.
  /// Otherwise, release one level of access.
  ///
  virtual void release_access(bool xall = false) const;

  ///
  /// True if this is attached to a state.
  ///
  virtual bool is_attached() const;

  ///
  /// True if this is attached to the same state as xother
  ///
  bool is_same_state(const poset_state_handle* xother) const;

protected:

  ///
  /// State object for this poset.
  ///
  poset_state* _state;

  ///
  /// State object for this poset.
  ///
  virtual poset_state* state_obj() const;

  // The following attach_to_state is not virtual because it
  // calls attach_handle_data_members, which is virtual.

  ///
  /// Attach this handle to the same state as xother.
  ///
  void attach_to_state(const poset_state_handle* xother);

  ///
  /// Attach this handle to the state associated with the member
  /// with index xindex in name space xhost.
  ///
  virtual void attach_to_state(const namespace_poset* xhost, pod_index_type xindex);

  ///
  /// Attach this handle to the state associated with the member
  /// with index xindex in name space xhost.
  ///
  void attach_to_state(const namespace_poset* xhost, const scoped_index& xindex);

  ///
  /// Attach this handle to the state associated with the member
  /// with name xname in name space xhost.
  ///
  virtual void attach_to_state(const namespace_poset* xhost, const std::string& xname);

  ///
  /// Attach this handle to the state with associated with namespace member xmbr
  ///
  virtual void attach_to_state(const abstract_poset_member* xmbr);

  ///
  /// Detach this handle from its state
  ///
  virtual void detach_from_state();

//   ///
//   /// Detaches this handle and deletes its state
//   ///
//   void delete_state(bool xauto_access);

  ///
  /// Creates a new poset state with schema xschema and table dof map xdof_map,
  /// attaches this to the state and creates and initializes the associated
  /// namespace member. Intended for use by new_table factory methods.
  ///
  void new_state(namespace_poset& xns, const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map);

  ///
  /// Creates a new poset state with path xpath, schema xschema and table dof map xdof_map,
  /// attaches this to the state.
  ///
  virtual void new_state(const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map);

  ///
  /// Initializes the handle data members that depend on the
  /// table dofs and are required to get access when this handle
  /// is used to create a new state. Intended to be called only
  /// from new_state and to be redefined in descendants to handle 
  /// additional data members defined there.
  ///
  virtual void initialize_handle_data_members(const namespace_poset& xns);

  ///
  /// Initializes the handle data members when this handle
  /// is attached to a state. Intended to be redefined in
  /// descendants to handle additional data members defined there.
  ///
  virtual void attach_handle_data_members();

  ///
  /// Restores the lattice invariant after editing jims.
  ///
  void ensure_lattice_invariant();

  ///
  /// Release all access to posets this depends on,
  /// then detach and delete the state.
  ///
  virtual void terminate_access();

private:

  //@}


  // ===========================================================
  /// @name GLOBAL ATTRIBUTES FACET
  // ===========================================================
  //@{

public:

  ///
  /// The namespace this poset resides in.
  /// Obsolete; use name_space() instead.
  ///
  namespace_poset* host() const;

  ///
  /// The namespace this poset resides in.
  ///
  namespace_poset* name_space() const;

  ///
  /// The member index of this poset within the namespace host()
  ///
  const scoped_index& index() const;

  ///
  /// The set of primitives used by this poset
  ///
  virtual const primitives_poset& primitives() const;

  ///
  /// The name of this poset
  ///
  virtual std::string name() const;

  ///
  /// The name of this poset
  ///
  virtual std::string name(bool xauto_access) const;

  ///
  /// The path of this poset.
  ///
  virtual poset_path path(bool xauto_access = true) const;

protected:

  ///
  /// The namespace this poset resides in.
  ///
  namespace_poset* _name_space;

  ///
  /// The member index of this poset in the namespace
  ///
  scoped_index _index;

  ///
  /// Installs this as a member of xns. If xauto_link, automatically
  /// links the member into an appropriate group.
  ///
  virtual void initialize_namespace(namespace_poset& xns,
                                    const std::string& xposet_name,
                                    bool xauto_link = true);

private:

  //@}


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public:

  //   poset_state_handle* hplus(poset_state_handle* other);
  //   void hplus_pa(poset_state_handle* other, poset_state_handle* result);
  //   void hplus_sa(poset_state_handle* other);
  //   // horizontal sum of this and other (this hplus other), auto- and pre-, and self-allocated versions

  //   poset_state_handle* vplus(poset_state_handle* other);
  //   void vplus_pa(poset_state_handle* other, poset_state_handle* result);
  //   void vplus_sa(poset_state_handle* other);
  //   // vertical sum of this and other (this vplus other), auto- and pre-, and self-allocated versions

protected:

private:

  //@}


  // ===========================================================
  /// @name MEMBERSHIP FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a disconnected member with is_jim == xis_jim and
  /// the dof tuple identified by hub id xtuple_hub_id.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member(bool xis_jim, pod_index_type xtuple_hub_id);

  ///
  /// Create a disconnected member with is_jim == xis_jim and
  /// the dof tuple identified by id xtuple_id.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  void new_member(bool xis_jim, const scoped_index& xtuple_id, scoped_index& result);

  ///
  /// Create a disconnected member with is_jim == xis_jim.
  /// If xdof_map != 0, the new member uses it for dof storage,
  /// otherwise it creates an instance of array_poset_dof_map.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member(bool xis_jim, poset_dof_map* xdof_map = 0, bool xcopy_dof_map = false);

  ///
  /// Create a disconnected member with is_jim == xis_jim.
  /// If xdof_map != 0, the new member uses it for dof storage,
  /// otherwise it creates an instance of array_poset_dof_map.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  void new_member(bool xis_jim, poset_dof_map* xdof_map,
		  bool xcopy_dof_map, scoped_index& result);

  ///
  /// Create a disconnected member interval of type xinterval_type with size xsize,
  /// dof tuple ids xtuple_hub_ids, and interval type specific private data xdata.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member_interval(const std::string& xinterval_type,
					     size_type xsize,
					     const block<pod_index_type>& xtuple_hub_ids,
					     const block<pod_index_type>& xdata);

  ///
  /// Create a disconnected member interval of type xinterval_type with size xsize,
  /// dof tuple hub ids xtuple_hub_ids, and interval type specific private data xdata.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  void new_member_interval(const std::string& xinterval_type, size_type xsize,
			   const block<pod_index_type>& xtuple_hub_ids,
			   const block<pod_index_type>& xdata,
			   scoped_index& result);

  ///
  /// Delete the member with hub id xmbr_hub_id.
  /// Warning: this routine does not delete links;
  /// it will leave any links to this member dangling.
  /// Use abstract_poset_member::delete_state unless
  /// you know what you are doing.
  ///
  virtual void delete_member(pod_index_type xmbr_hub_id);

  ///
  /// Delete the member with id xmbr_id.
  /// Warning: this routine does not delete links;
  /// it will leave any links to this member dangling.
  /// Use abstract_poset_member::delete_state unless
  /// you know what you are doing.
  ///
  void delete_member(const scoped_index& xmbr_id);

  ///
  /// The number of members of this poset
  ///
  virtual int member_ct() const;

  ///
  /// The number of standard members automatically
  /// allocated by the constructor.
  ///
  virtual int standard_member_ct() const;

  ///
  /// True if poset is in its initial state,
  /// that is, it contains just the standard members.
  ///
  bool has_standard_member_ct() const;

  ///
  /// The upper bound on the member_index;
  ///
  virtual scoped_index member_index_ub() const;

  ///
  /// @deprecated Use member_hub_id_space().get_iterator() instead.
  /// An iterator for members of this poset
  ///
  index_iterator member_iterator() const;

  ///
  /// True if some version of this poset contains poset member with
  /// hub id xmbr_hub_id
  ///
  virtual bool contains_member(pod_index_type xmbr_hub_id, bool xauto_access = true) const;

  ///
  /// True if some version of this poset contains poset member with
  /// id xmbr_id
  ///
  bool contains_member(const scoped_index& xmbr_id, bool xauto_access = true) const;

  ///
  /// True if version xversion of this poset contains poset member with
  /// hub id xmbr_hub_id
  ///
  virtual bool contains_member(pod_index_type xmbr_hub_id, int xversion, bool xauto_access = true) const;

  ///
  /// True if version xversion of this poset contains poset member with
  /// id xmbr_id
  ///
  bool contains_member(const scoped_index& xmbr_id, int xversion, bool xauto_access = true) const;

  ///
  /// True if this poset contains a member with name xname
  ///
  virtual bool contains_member(const std::string& xname, bool xauto_access = true) const;

  ///
  /// True if this poset contains xmbr
  ///
  bool contains_member(const abstract_poset_member* xmbr, bool xauto_access = true) const;

  ///
  /// True if this poset contains poset member(s) with indices in xmbrs
  ///
  bool contains_members(const scoped_index* xmbrs, int xmbrs_ct, bool xauto_access = true) const;

  ///
  /// True if this poset contains poset member(s) with indices in xmbrs
  ///
  bool contains_members(pod_index_type* xmbrs, int xmbrs_ct, bool xauto_access = true) const;

  ///
  /// True if this poset contains poset member(s) with names in xnames
  ///
  bool contains_members(const std::string* xnames, int xnames_ct, bool xauto_access = true) const;

  ///
  /// True if this poset contains poset members with indices in p
  ///
  bool contains_members(const block<pod_index_type>& p, bool xauto_access = true) const;

  ///
  /// True if this poset contains poset members with indices in p
  ///
  bool contains_members(const block<scoped_index>& p, bool xauto_access = true) const;

  ///
  /// True if this poset contains poset members with names in p
  ///
  bool contains_members(const block<std::string>& p, bool xauto_access = true) const;

  ///
  /// True if this poset is empty
  ///
  bool is_empty() const;

  ///
  /// True if the member with hub id xmbr_hub_id  is a jim in the
  /// current version (xin_current_version == true) or in
  /// some version (xin_current_version == false).
  ///
  virtual bool is_jim(pod_index_type xmbr_hub_id, bool xin_current_version = true) const;

  ///
  /// True if the member with id xmbr_id is a jim in the
  /// current version (xin_current_version == true) or in
  /// some version (xin_current_version == false).
  ///
  bool is_jim(const scoped_index& xmbr_id, bool xin_current_version = true) const;

  ///
  /// True if the member with name xname is a jim in the
  /// current version (xin_current_version == true) or in
  /// some version (xin_current_version == false).
  ///
  bool is_jim(const std::string& xname, bool xin_current_version = true) const;

  ///
  /// True if the member with hub id xmbr_hub_id covers the bottom.
  ///
  virtual bool is_atom(pod_index_type xmbr_hub_id) const;

  ///
  /// True if the member with id xmbr_id covers the bottom.
  ///
  bool is_atom(const scoped_index& xmbr_id) const;

  ///
  /// The top member of the poset (mutable version)
  ///
  abstract_poset_member& top();

  ///
  /// The top member of the poset (const version)
  ///
  const abstract_poset_member& top() const;

  ///
  /// The bottom member of the poset (mutable version)
  ///
  abstract_poset_member& bottom();

  ///
  /// The bottom member of the poset (const version)
  ///
  const abstract_poset_member& bottom() const;

protected:

  ///
  /// Top member of poset.
  ///
  abstract_poset_member* _top;

  ///
  /// Bottom members of poset.
  ///
  abstract_poset_member* _bottom;

  ///
  /// The cover relation graph.
  ///
  poset_crg_state& crg() const
  {
    return *(state_obj()->crg());
  };

  ///
  /// Creates the members common to every poset, for instance, top() and bottom().
  ///
  virtual void initialize_standard_members();

  ///
  /// Sets the number of standard members automatically allocated by the constructor.
  ///
  inline void put_standard_member_ct(int xct)
  {
    crg().put_standard_member_ct(xct);
  };

  ///
  /// Sets the number of standard row dof tuples automatically allocated by the constructor.
  ///
  inline void put_standard_row_dof_tuple_ct(int xct)
  {
    table().put_standard_row_dof_tuple_ct(xct);
  };

  ///
  /// True if 0 <= xmbr_id < state_obj()->member_index_ub().
  ///
  bool index_in_bounds(const scoped_index& xmbr_id) const;

  ///
  /// True if for all i: 0 <= indices[i] < state_obj()->member_index_ub().
  ///
  bool index_in_bounds(const block<scoped_index>& indices) const;

  ///
  /// Create a disconnected member with hub id xmbr_hub_id, is_jim == xis_jim and
  /// the dof tuple identified by xdof_tuple_id.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual void new_member(pod_index_type xmbr_hub_id, 
			  bool xis_jim, 
			  const scoped_index& xdof_tuple_id);

  ///
  /// Create a disconnected member with hub id xmbr_hub_id and is_jim == xis_jim.
  /// If xdof_map != 0, the new member uses it for dof storage,
  /// otherwise it creates an instance of array_poset_dof_map.
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  void new_member(pod_index_type xmbr_hub_id, 
		  bool xis_jim, 
		  poset_dof_map* xdof_map, 
		  bool xcopy_dof_map);

  ///
  /// Create a disconnected member interval of type xinterval_type with size xsize.
  ///
  /// WARNING: this routine leaves the new member interval is a partially
  /// constructed state (see postconditions) and is intended primarily
  /// for use by the i/o subsystem.
  ///
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual pod_index_type new_member_interval(const std::string& xinterval_type, size_type xsize);

  ///
  /// Create a disconnected member interval beginning at hub id xmbr_hub_id,
  /// of type xinterval_type, and with size xsize.
  ///
  /// WARNING: this routine leaves the new member interval is a partially
  /// constructed state (see postconditions) and is intended primarily
  /// for use by the i/o subsystem.
  ///
  /// WARNING: this routine leaves a disconnected member in the poset and hence
  /// leaves the poset in an invalid state. The client must properly link the
  /// member created by this routine using new_link in order to return
  /// the poset to a valid state.
  ///
  virtual void new_member_interval(pod_index_type xmbr_hub_id,
				   const std::string& xinterval_type, 
				   size_type xsize);

private:

  //@}

  // ===========================================================
  /// @name MEMBER NAME FACET
  // ===========================================================
  //@{

public:

  ///
  /// A path for the member with hub id xmbr_hub_id.
  ///
  poset_path member_path(pod_index_type xmbr_hub_id, bool xauto_access) const;

  ///
  /// A name for the member with hub id xmbr_hub_id
  ///
  virtual std::string member_name(pod_index_type xmbr_hub_id, bool xauto_access = false) const;

  ///
  /// A name for the member with id xmbr_id
  ///
  std::string member_name(const scoped_index& xmbr_id, bool xauto_access = false) const;

  ///
  /// All the names for the member with hub id xmbr_hub_id.
  ///
  void all_member_names(pod_index_type xmbr_hub_id,
                        block<std::string>& xresult,
                        bool xauto_access = false) const;

  ///
  /// All the names for the member with id xmbr_id.
  ///
  void all_member_names(const scoped_index& xmbr_id,
                        block<std::string>& xresult,
                        bool xauto_access = false) const;

  ///
  /// The number of names for the member with hub id xmbr_hub_id.
  ///
  size_type member_name_ct(pod_index_type xmbr_hub_id, bool xauto_access) const;

  ///
  /// The number of names for the member with id xmbr_id.
  ///
  size_type member_name_ct(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// True if xname is a name for the member with hub id xmbr_hub_id.
  ///
  bool member_has_name(pod_index_type xmbr_hub_id,
                       const std::string& xname,
                       bool xauto_access = false) const;

  ///
  /// True if xname is a name for the member with id xmbr_id.
  ///
  bool member_has_name(const scoped_index& xmbr_hub_id,
                       const std::string& xname,
                       bool xauto_access = false) const;

  ///
  /// Make xname a name for the member with hub id xmbr_hub_id.
  /// if xunique, make xname the only name.
  ///
  virtual void put_member_name(pod_index_type xmbr_hub_id,
                               const std::string& xname,
                               bool xunique,
                               bool xauto_access = false);

  ///
  /// Make xname a name for the member with id xmbr_id.
  /// if xunique, make xname the only name.
  ///
  void put_member_name(const scoped_index& xmbr_id,
		       const std::string& xname,
		       bool xunique,
		       bool xauto_access = false);

  ///
  /// Make xname not a name for any member.
  ///
  void delete_member_name(const std::string& xname, bool xauto_access = false);

  ///
  /// Delete all names for the member with hub id xmbr_hub_id.
  ///
  void delete_all_member_names(pod_index_type xmbr_hub_id,
                               bool xauto_access = false);

  ///
  /// Delete all names for the member with id xmbr_id.
  ///
  void delete_all_member_names(const scoped_index& xmbr_id,
                               bool xauto_access = false);

protected:

  ///
  /// The type of the member name map.
  ///
  typedef poset_crg_state::member_name_map_type member_name_map_type;

  ///
  /// The bidirectional map between member indices and names
  ///
  member_name_map_type& member_name_map(bool xrequire_write_access = false);

private:

  //@}
 

  // ===========================================================
  /// @name MEMBER ID SPACE FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Collection of member id spaces for this (const version).
  ///
  const index_space_family& member_id_spaces(bool xauto_access) const;

  ///
  /// Collection of member id spaces for this (mutable version).
  ///
  index_space_family& member_id_spaces(bool xauto_access);

  ///
  /// The member hub id space.
  ///
  const hub_index_space_handle& member_hub_id_space(bool xauto_access) const;  

  ///
  /// An id in the member hub id space; intended for 
  /// copying to initialize ids to the member id space.
  ///
  virtual const scoped_index& member_id(bool xauto_access) const;

  ///
  /// An id in the member hub id space with pod xid.
  ///
  scoped_index member_id(pod_index_type xid, bool xauto_access) const;

  ///
  /// The hub id of the member with name xname.
  ///
  virtual pod_index_type member_id(const std::string& xname, bool xauto_access) const;

  ///
  /// The index of the member with name xname.
  ///
  void member_id(const std::string& xname, scoped_index& result, bool xauto_access) const;

protected:

  ///
  /// Update the initially allocated id spaces
  ///
  void update_standard_member_id_spaces();

  ///
  /// Deletes all non-standard id spaces.
  ///
  void clear_member_id_spaces(bool xauto_access);

  ///
  /// Creates a new term in the member hub id space with xct number of ids.
  /// Returns the index of the id space state created.
  ///
  pod_index_type new_term(size_type xct, bool xauto_access);

  ///
  /// Extends the last term of the member hub id space to ct == xct.
  /// @hack A temporary method to support extension
  /// of section space schema when the underlying base
  /// space is extended.
  ///
  void extend_last_member_term(size_type xct, bool xauto_access);

private:

  //@}


  // ===========================================================
  /// @name ORDER RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if hub id xlesser is less than or equal to hub id xgreater.
  ///
  virtual bool le(pod_index_type xgreater, pod_index_type xlesser) const;

  ///
  /// True if id xlesser is less than or equal to id xgreater.
  ///
  bool le(const scoped_index& xgreater, const scoped_index& xlesser) const;

  ///
  /// True if hub id xlesser is less than or equivalent to hub id xgreater.
  ///
  virtual bool leqv(pod_index_type xgreater, pod_index_type xlesser) const;

  ///
  /// True if id xlesser is less than or equivalent to id xgreater.
  ///
  bool leqv(const scoped_index& xgreater, const scoped_index& xlesser) const;

  ///
  /// True if hub id xother_hub_id is join equivalent to hub id xmbr_hub_id
  ///
  virtual bool is_jem(pod_index_type xmbr_hub_id, pod_index_type xother_hub_id) const;

  ///
  /// True if id xother_id is join equivalent to id xmbr_id
  ///
  bool is_jem(const scoped_index& xmbr_id, const scoped_index& xother_id) const;

  ///
  /// The hub id of the largest member which is join-equivalent to
  /// hub id xmbr_hub_id
  ///
  virtual pod_index_type greatest_jem(pod_index_type xmbr_hub_id) const;

  ///
  /// The id of the largest member which is join-equivalent to id xmbr_id
  ///
  void greatest_jem(const scoped_index& xmbr_id, scoped_index& result) const;

  ///
  /// The hub id of the smallest member which is join-equivalent to
  /// hub id xmbr_hub_id
  ///
  virtual pod_index_type least_jem(pod_index_type xmbr_hub_id) const;

  ///
  /// The id of the smallest member which is join-equivalent to id xmbr_id
  ///
  void least_jem(const scoped_index& xmbr_id, scoped_index& result) const;

  ///
  /// Makes hub id xjem1 the greatest jem of hub id xjem2, unless
  /// the current greatest jem of xjem2 is top, in which case
  /// it makes top the greatest jem of xjem1
  ///
  void link_greatest_jem(pod_index_type xjem1, pod_index_type xjem2);

  ///
  /// Makes id xjem1 the greatest jem of id xjem2, unless
  /// the current greatest jem of xjem2 is top, in which case
  /// it makes top the greatest jem of xjem1
  ///
  void link_greatest_jem(const scoped_index& xjem1, const scoped_index& xjem2);

  ///
  /// Makes hub id xjem1 the least jem of hub id xjem2, unless
  /// the current least jem of xjem2 is bottom, in which case
  /// it makes bottom the least jem of xjem1
  ///
  void link_least_jem(pod_index_type xjem1, pod_index_type xjem2);

  ///
  /// Makes id xjem1 the least jem of id xjem2, unless
  /// the current least jem of xjem2 is bottom, in which case
  /// it makes bottom the least jem of xjem1
  ///
  void link_least_jem(const scoped_index& xjem1, const scoped_index& xjem2);

  ///
  /// Merge the join-equivalence class of hub id xjem2 under
  /// that of hub id xjem1
  ///
  virtual void merge_jems(pod_index_type xjem1, pod_index_type xjem2);

  ///
  /// Merge the join-equivalence class of id xjem2 under that of id xjem1
  ///
  void merge_jems(const scoped_index& xjem1, const scoped_index& xjem2);

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// Insert a cover link from greater to lesser (that is, hub id xgreater
  /// covers hub id xlesser).
  /// WARNING: this routine does not ensure that the link is a cover link,
  /// that is, it does not remove redundant or conflicting links. Improper
  /// use of this routine can produce inconsistent poset states.
  ///
  virtual void new_link(pod_index_type xgreater, pod_index_type xlesser);

  ///
  /// Insert a cover link from greater to lesser (that is, id xgreater covers
  /// id xlesser).
  /// WARNING: this routine does not ensure that the link is a cover link,
  /// that is, it does not remove redundant or conflicting links. Improper
  /// use of this routine can produce inconsistent poset states.
  ///
  void new_link(const scoped_index& xgreater, const scoped_index& xlesser);

  ///
  /// Delete the cover link between hub id xgreater and hub id xlesser.
  ///
  virtual void delete_link(pod_index_type xgreater, pod_index_type xlesser);

  ///
  /// Delete the cover link between id xgreater and id xlesser.
  ///
  void delete_link(const scoped_index& xgreater, const scoped_index& xlesser);

  ///
  /// True if there is a cover link between hub id xgreater and hub id xlesser.
  ///
  virtual bool contains_link(pod_index_type xgreater, pod_index_type xlesser) const;

  ///
  /// True if there is a cover link between id xgreater and id xlesser.
  ///
  bool contains_link(const scoped_index& xgreater, const scoped_index& xlesser) const;

  ///
  /// The id for the lower (xlower true) or upper (xlower false) cover
  /// id space of the member with hub id xmbr_hub_id.
  ///
  pod_index_type cover_id_space_id(bool xlower, pod_index_type xmbr_hub_id) const;

  ///
  /// The id for the lower (xlower true) or upper (xlower false) cover
  /// id space of the member with id xmbr_id.
  ///
  pod_index_type cover_id_space_id(bool xlower, const scoped_index& xmbr_id) const;

  ///
  /// Allocates a handle for the lower (xlower true) or upper (xlower false) 
  /// cover id space of the member with hub id xmbr_hub_id from the pool of id spaces.
  ///
  index_space_handle& get_cover_id_space(bool xlower, pod_index_type xmbr_hub_id) const;

  ///
  /// Allocates a handle for the lower (xlower true) or upper (xlower false) 
  /// cover id space of the member with id xmbr_id from the pool of id spaces.
  ///
  index_space_handle& get_cover_id_space(bool xlower, const scoped_index& xmbr_id) const;

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
  /// Returns xcover_id_space to the pool of id spaces.
  ///
  void release_cover_id_space(index_space_handle& xcover_id_space) const;

  ///
  /// Allocates an iterator for the lower (xlower true) or upper (xlower false) 
  /// cover id space of the member with hub id xmbr_hub_id from the pool of id space iterators.
  ///
  index_space_iterator& get_cover_id_space_iterator(bool xlower, pod_index_type xmbr_hub_id) const;


  ///
  /// Allocates an iterator for the lower (xlower true) or upper (xlower false) 
  /// cover id space of the member with id xmbr_id from the pool of id space iterators.
  ///
  index_space_iterator& get_cover_id_space_iterator(bool xlower, const scoped_index& xmbr_id) const;

  ///
  /// Returns xcover_itr to the pool of id space iterators.
  ///
  void release_cover_id_space_iterator(index_space_iterator& xcover_itr) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member
  /// with hub id xmbr_hub_id is the domain of iterator xitr.
  ///
  bool cover_contains_iterator(bool xlower,
                               pod_index_type xmbr_hub_id,
                               const index_space_iterator& xitr) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member
  /// with id xmbr_id is the domain of iterator xitr.
  ///
  bool cover_contains_iterator(bool xlower,
                               const scoped_index& xmbr_id,
                               const index_space_iterator& xitr) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member
  /// with hub id xmbr_hub_id is empty.
  ///
  bool cover_is_empty(bool xlower, pod_index_type xmbr_hub_id) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member
  /// with id xmbr_id is empty.
  ///
  bool cover_is_empty(bool xlower, const scoped_index& xmbr_id) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member
  /// with hub id xmbr_hub_id contains exactly one member.
  ///
  bool cover_is_singleton(bool xlower, pod_index_type xmbr_hub_id) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member
  /// with id xmbr_id contains exactly one member.
  ///
  bool cover_is_singleton(bool xlower, const scoped_index& xmbr_id) const;

  ///
  /// The number of members in the lower cover (xlower true)
  /// or upper cover (xlower false) of the member with hub id xmbr_hub_id.
  ///
  virtual size_type cover_ct(bool xlower, pod_index_type xmbr_hub_id) const;

  ///
  /// The number of members in the lower cover (xlower true)
  /// or upper cover (xlower false) of the member with id xmbr_id.
  ///
  size_type cover_ct(bool xlower, const scoped_index& xmbr_id) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member with hub id
  /// xmbr_hub_id contains member with hub id xother_mbr_hub_id
  ///
  bool cover_contains_member(bool xlower,
                             pod_index_type xmbr_hub_id,
                             pod_index_type xother_mbr_hub_id) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member with id
  /// xmbr_id contains member with id xother_mbr_id
  ///
  bool cover_contains_member(bool xlower,
                             const scoped_index& xmbr_id,
                             const scoped_index& xother_mbr_id) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member with
  /// hub id xmbr_hub_id  contains the same members as the
  /// lower or upper cover set, respectively, of the member
  /// with hub id xother_mbr_hub_id.
  ///
  bool cover_is_equal(bool xlower,
                      pod_index_type xmbr_hub_id,
                      pod_index_type xother_mbr_hub_id) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member with
  /// id xmbr_id  contains the same members as the
  /// lower or upper cover set, respectively, of the member
  /// with id xother_mbr_id.
  ///
  bool cover_is_equal(bool xlower,
                      const scoped_index& xmbr_id,
                      const scoped_index& xother_mbr_id) const;

  ///
  /// Hub id of the first member of the lower (xlower true) or
  /// upper (xlower false) cover of the member with hub id xmbr_hub_id.
  ///
  pod_index_type first_cover_member(bool xlower, pod_index_type xmbr_hub_id) const;

  ///
  /// Id of the first member of the lower (xlower true) or
  /// upper (xlower false) cover of the member with id xmbr_id.
  ///
  void first_cover_member(bool xlower, const scoped_index& xmbr_id,
			  scoped_index& result) const;

  ///
  /// Inserts hub id xother_mbr_hub id in the lower (xlower true) or
  /// upper (xlower false) cover set of the member with hub id xmbr_hub_id.
  ///
  void insert_cover_member(pod_index_type xother_mbr_hub_id,
                           bool xlower,
                           pod_index_type xmbr_hub_id);

  ///
  /// Inserts id xother_mbr_id in the lower (xlower true) or
  /// upper (xlower false) cover set of the member with id xmbr_id.
  ///
  void insert_cover_member(const scoped_index& xother_mbr_id,
                           bool xlower,
                           const scoped_index& xmbr_id);

  ///
  /// Inserts hub id xother_mbr_hub_id in the lower (xlower true) or
  /// upper (xlower false) cover set of the member with hub id xmbr_hub_id,
  /// at a position just before xitr. Increments xitr to the
  /// position after the inserted entry.
  ///
  void insert_cover_member(pod_index_type xother_mbr_hub_id,
                           bool xlower,
                           pod_index_type xmbr_hub_id,
                           index_space_iterator& xitr);

  ///
  /// Inserts id xother_mbr_index in the lower (xlower true) or
  /// upper (xlower false) cover set of the member with id xmbr_id,
  /// at a position just before xitr. Increments xitr to the
  /// position after the inserted entry.
  ///
  void insert_cover_member(const scoped_index& xother_mbr_id,
                           bool xlower,
                           const scoped_index& xmbr_id,
                           index_space_iterator& xitr);

  ///
  /// Removes hub id xother_mbr_hub_id from the lower (xlower true) or
  /// upper (xlower false) cover set of the member with hub id xmbr_hub_id.
  ///
  void remove_cover_member(pod_index_type xother_mbr_hub_id,
                           bool xlower,
                           pod_index_type xmbr_hub_id);

  ///
  /// Removes id xother_mbr_id from the lower (xlower true) or
  /// upper (xlower false) cover set of the member with id xmbr_id.
  ///
  void remove_cover_member(const scoped_index& xother_mbr_id,
                           bool xlower,
                           const scoped_index& xmbr_id);

  ///
  /// Removes the current item of xitr from the lower (xlower true) or
  /// upper (xlower false) cover set of the member with hub id xmbr_hub_id;
  /// If xitr is at the end, forces xitr.is_done().  Otherwise,
  /// increments xitr to the next position.
  ///
  void remove_cover_member(index_space_iterator& xitr,
                           bool xlower,
                           pod_index_type xmbr_hub_id);

  ///
  /// Removes the current item of xitr from the lower (xlower true) or
  /// upper (xlower false) cover set of the member with id xmbr_id;
  /// If xitr is at the end, forces xitr.is_done().  Otherwise,
  /// increments xitr to the next position.
  ///
  void remove_cover_member(index_space_iterator& xitr,
                           bool xlower,
                           const scoped_index& xmbr_id);

  ///
  /// Removes all members for which functor xfilter(xmbr.index().hub_pod()) is true
  /// from the lower (xlower true) or upper (xlower false) cover set
  /// of the member with hub id xmbr_hub_id.
  ///
  template <typename filter_type>
  void remove_cover_members(const filter_type& xfilter,
			    bool xlower,
			    pod_index_type xmbr_hub_id);

  ///
  /// Removes all members for which functor xfilter(xmbr.index().hub_pod()) is true
  /// from the lower (xlower true) or upper (xlower false) cover set
  /// of the member with id xmbr_id.
  ///
  template <typename filter_type>
  void remove_cover_members(const filter_type& xfilter,
			    bool xlower,
			    const scoped_index& xmbr_id);

  ///
  /// Replaces hub id xold_other_mbr_hub_id with hub id xnew_other_mbr_hub_id
  /// in the lower (xlower true) or upper (xlower false) cover set of
  /// the member with hub id xmbr_hub_id.
  ///
  void replace_cover_member(const scoped_index& xold_other_mbr_hub_id,
			    const scoped_index& xnew_other_mbr_hub_id,
			    bool xlower,
			    const scoped_index& xmbr_hub_id);

  ///
  /// Replaces id xold_other_mbr_id with id xnew_other_mbr_id in the lower (xlower true) or
  /// upper (xlower false) cover set of the member with id xmbr_id.
  ///
  void replace_cover_member(pod_index_type xold_other_mbr_id,
			    pod_index_type xnew_other_mbr_id,
			    bool xlower,
			    pod_index_type xmbr_id);

  ///
  /// Clears the lower (xlower true) or upper (xlower false)
  /// cover set of the member with hub id xmbr_hub_id.
  ///
  void clear_cover(bool xlower, pod_index_type xmbr_hub_id);

  ///
  /// Clears the lower (xlower true) or upper (xlower false)
  /// cover set of the member with id xmbr_id.
  ///
  void clear_cover(bool xlower, const scoped_index& xmbr_id);

  ///
  /// Copies the lower (xlower true) or upper (xlower false) cover set
  /// of the member with hub id xmbr_hub_id to the member with hub id
  /// xother_mbr_hub_id.
  ///
  void copy_cover(bool xlower,
                  pod_index_type xmbr_hub_id,
                  pod_index_type xother_mbr_hub_id);

  ///
  /// Copies the lower (xlower true) or upper (xlower false) cover set
  /// of the member with id xmbr_id to the member with id
  /// xother_mbr_id.
  ///
  void copy_cover(bool xlower,
                  const scoped_index& xmbr_id,
                  const scoped_index& xother_mbr_id);

  ///
  /// Appends the interval of hub ids [xmbr_hub_begin, xmbr_hub_end)
  /// to the upper cover of bottom.  This function is intended to
  /// use by block members that store there vertices in a gathered id space
  ///
  void append_upper_cover_of_bottom(pod_index_type xmbr_hub_begin,
				    pod_index_type xmbr_hub_end);

  ///
  /// Appends the interval of ids [xbegin, xend) to the upper cover
  /// of bottom.  This function is intended to use by block
  /// members that store there vertices in a gathered id space
  ///
  void append_upper_cover_of_bottom(const scoped_index& xmbr_begin,
				    const scoped_index& xmbr_end);

protected:

  ///
  /// Transfers the lower cover (lower == true) or the
  /// upper cover (lower == false) from the member with
  /// hub id xsrc to the member with hub id xdst.
  ///
  void transfer_cover(pod_index_type xsrc, pod_index_type xdst, bool lower);

private:

  //@}



  // ===========================================================
  /// @name SUBPOSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of subposets of this poset
  ///
  virtual size_type subposet_ct() const; 

  ///
  /// The number of standard subposets automatically
  /// allocated by the constructor.
  ///
  virtual int standard_subposet_ct() const;

  ///
  /// True if poset is in its initial state,
  /// that is, it contains just the standard subposets.
  ///
  bool has_standard_subposet_ct() const;

  ///
  /// The upper bound on the subposet index;
  ///
  virtual scoped_index subposet_index_ub() const;

  ///
  /// The hub id of the subposet with name xname
  ///
  virtual pod_index_type subposet_id(const std::string& xname) const;

  ///
  /// The id of the subposet with name xname
  ///
  virtual void subposet_id(const std::string& xname, scoped_index& result) const;

  ///
  /// Allocates an id space iterator over the subposet ids from the
  /// iterator pool.
  ///
  virtual index_space_iterator& get_subposet_id_space_iterator() const;

  ///
  /// Returns the id space iterator xitr to the subposet iterator pool.
  ///
  virtual void release_subposet_id_space_iterator(index_space_iterator& xitr) const;

  ///
  /// True if this poset includes subposet with hub id xsubposet_hub_id
  ///
  virtual bool includes_subposet(pod_index_type xsubposet_hub_id,
                                 bool xauto_access = true) const;

  ///
  /// True if this poset includes subposet with id xsubposet_id
  ///
  bool includes_subposet(const scoped_index& xsubposet_id,
			 bool xauto_access = true) const;

  ///
  /// True if this poset includes subposet with name xname
  ///
  bool includes_subposet(const std::string& xname, bool xauto_access = true) const;

  ///
  /// True if this poset includes xs
  ///
  bool includes_subposet(const subposet* xs, bool xauto_access = true) const;

  ///
  /// True if this poset includes subposets with hub ids xhub_ids.
  ///
  bool includes_subposets(const block<pod_index_type>& xhub_ids, bool xauto_access = true) const;

  ///
  /// True if this poset includes subposets with ids xids
  ///
  bool includes_subposets(const block<scoped_index>& xids, bool xauto_access = true) const;

  ///
  /// Creates a new subposet. If xinitialize, make the subposet empty,
  ///
  virtual pod_index_type new_subposet(bool xinitialize = true);

  ///
  /// Creates a new subposet. If xinitialize, make the subposet empty,
  ///
  void new_subposet(bool xinitialize, scoped_index& result);

  ///
  /// Creates a new subposet. Set the membership to the members 
  /// with indices in xmambers.
  ///
  virtual pod_index_type new_subposet(const block<pod_index_type>& xmembers);

  ///
  /// Creates a new subposet. Set the membership to the members 
  /// with indices in xmambers.
  ///
  virtual void new_subposet(const block<scoped_index>& xmembers, scoped_index& result);

  ///
  /// Deletes the subposet with hub id xsubposet_hub_id.
  ///
  virtual void delete_subposet(pod_index_type xsubposet_hub_id);

  ///
  /// Deletes the subposet with id xsubposet_id.
  ///
  void delete_subposet(const scoped_index& xsubposet_id);

  ///
  /// The "improper" subset containing all members of this poset 
  ///
  virtual const subposet& whole() const;

  ///
  /// The subset of all jims (mutable version)
  ///
  virtual subposet& jims();

  ///
  /// The subset of all jims (const version)
  ///
  virtual const subposet& jims() const;

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
  /// The name of the coarsest common refinement subposet.
  ///
  static const std::string& coarsest_common_refinement_name();

protected:

  ///
  /// The subposet of members with resident dof tuples
  ///
  subposet _resident;

  ///
  /// The subset of all members with resident (in memory) dof tuples (mutable version).
  ///
  virtual subposet& resident();

  ///
  /// The subset of all members with resident (in memory) dof tuples (const version).
  ///
  virtual const subposet& resident() const;

  ///
  /// The set of subposets of this poset.
  ///
  poset_powerset_state& powerset() const;

  ///
  /// Creates the subposets common to every poset (e.g. whole() and jims()).
  ///
  virtual void initialize_standard_subposets(const std::string& xname);

  ///
  /// Sets the number of standard subposets automatically allocated by the constructor.
  ///
  void put_standard_subposet_ct(int xct);

private:

  //@}

  // ===========================================================
  /// @name SUBPOSET NAME FACET
  // ===========================================================
  //@{

public:

  ///
  /// A name for the subposet with hub id xsubposet_hub_id
  ///
  virtual std::string subposet_name(pod_index_type xsubposet_hub_id, bool xauto_access = false) const;

  ///
  /// A name for the subposet with id xsubposet_id
  ///
  std::string subposet_name(const scoped_index& xsubposet_id, bool xauto_access = false) const;

  ///
  /// All the names for the subposet with hub id xsubposet_hub_id
  ///
  void all_subposet_names(pod_index_type xsubposet_hub_id,
                          block<std::string>& xresult,
                          bool xauto_access = false) const;

  ///
  /// All the names for the subposet with id xsubposet_id.
  ///
  void all_subposet_names(const scoped_index& xsubposet_id,
                          block<std::string>& xresult,
                          bool xauto_access = false) const;

  ///
  /// The number of names for the subposet with hub id xsubposet_hub_id.
  ///
  size_type subposet_name_ct(pod_index_type xsubposet_hub_id, bool xauto_access) const;

  ///
  /// The number of names for the subposet with id xsubposet_id.
  ///
  size_type subposet_name_ct(const scoped_index& xsubposet_id, bool xauto_access) const;

  ///
  /// True if xname is a name for the subposet with hub id xsubposet_hub_id.
  ///
  bool subposet_has_name(pod_index_type xsubposet_hub_id, const std::string& xname, bool xauto_access = false) const;

  ///
  /// True if xname is a name for the subposet with id xsubposet_id.
  ///
  bool subposet_has_name(const scoped_index& xsubposet_id, const std::string& xname, bool xauto_access = false) const;

  ///
  /// Make xname a name for the subposet with hub id xsubposet_hub_id;
  /// if xunique, make xname the only name.
  ///
  virtual void put_subposet_name(pod_index_type xsubposet_hub_id,
                                 const std::string& xname,
                                 bool xunique,
                                 bool xauto_access);

  ///
  /// Make xname a name for the subposet with id xsubposet_id;
  /// if xunique, make xname the only name.
  ///
  void put_subposet_name(const scoped_index& xsubposet_id,
			 const std::string& xname,
			 bool xunique,
			 bool xauto_access);

  ///
  /// Make xname not a name for any subposet.
  ///
  void delete_subposet_name(const std::string& xname, bool xauto_access = false);

  ///
  /// Delete all names for the subposet with hub id xsubposet_hub_id;
  ///
  void delete_all_subposet_names(pod_index_type xsubposet_hub_id,
                                 bool xauto_access = false);

  ///
  /// Delete all names for the subposet with id xsubposet_id;
  ///
  void delete_all_subposet_names(const scoped_index& xsubposet_id,
                                 bool xauto_access = false);

protected:

private:

  //@}
 

  // ===========================================================
  /// @name SUBPOSET ID SPACE FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Collection of subposet id spaces for this (const version).
  ///
  const index_space_family& subposet_id_spaces(bool xauto_access) const;

  ///
  /// Collection of subposet id spaces for this (mutable version).
  ///
  index_space_family& subposet_id_spaces(bool xauto_access);

  ///
  /// The subposet hub id space.
  ///
  const hub_index_space_handle& subposet_hub_id_space(bool xauto_access) const;  

  ///
  /// An id in the subposet hub id space;
  /// intended for copying to initialize ids
  /// to the subposet id space.
  ///
  virtual const scoped_index& subposet_id(bool xauto_access) const;

  ///
  /// An id in the subposet hub id space with pod xid.
  ///
  scoped_index subposet_id(pod_index_type xid, bool xauto_access) const;

protected:

private:

  //@}



  // ===========================================================
  /// @name SCHEMA FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of schema member for this class.
  ///
  typedef schema_poset_member schema_type;

  ///
  /// The schema for this poset (mutable version).
  ///
  virtual schema_poset_member& schema();

  ///
  /// The schema for this poset (const version).
  ///
  virtual const schema_poset_member& schema() const;

  ///
  /// The schema for this poset, auto_accessible (mutable version).
  ///
  schema_poset_member& schema(bool xauto_access);

  ///
  /// The schema for this poset, auto_accessible (const version).
  ///
  const schema_poset_member& schema(bool xauto_access) const;

  ///
  /// True if xother_schema conforms to the type of schema required by this.
  ///
  virtual bool schema_is_ancestor_of(const schema_poset_member* xother_schema) const;

  ///
  /// True if the schema of this has name xname
  ///
  bool schema_is(const std::string& xschema_name) const;

  ///
  /// True if other has the same schema as this.
  ///
  bool same_schema(const poset_state_handle* xother) const;

  ///
  /// True if other has the same schema as this.
  ///
  bool same_schema(const abstract_poset_member* xother) const;

protected:

private:

  //@}

  // ===========================================================
  /// @name TABLE DOF FACET
  // ===========================================================
  //@{

public:
 

  ///
  /// True if xdof_map conforms to (is derived from) the type of
  /// table dof map required by this poset state and handle.
  ///
  virtual bool table_dof_map_conforms(const poset_dof_map* xdof_map) const;

  ///
  /// True if xdof_map conforms to (is derived from) the type of
  /// row dof map required by this poset state and handle.
  ///
  virtual bool row_dof_map_conforms(const poset_dof_map* xdof_map) const;

  ///
  /// The map from table dof client_ids to table dof values for this poset (mutable version)
  ///
  virtual array_poset_dof_map& table_dof_map(bool xrequire_write_access = false);

  ///
  /// The map from table dof client_ids to table dof values for this poset (const version)
  ///
  virtual const array_poset_dof_map& table_dof_map(bool xrequire_write_access = false) const;

  ///
  /// OBSOLETE: use table_dofs().
  /// Copies the entire table dof tuple from internal storage to xbuf
  ///
  void table_dof_tuple(void* xbuf, size_t xbuflen) const;

  ///
  /// The table dofs for this instance (mutable version).
  ///
  void* table_dofs();

  ///
  /// The table dofs for this instance (const version).
  ///
  const void* table_dofs() const;

  ///
  /// The table dofs for this instance (mutable auto-access version).
  ///
  void* table_dofs(bool xauto_access);

  ///
  /// The table dofs for this instance (const auto-access version).
  ///
  const void* table_dofs(bool xauto_access) const;

protected:

  ///
  /// The table of dof tuples of this poset.
  ///
  poset_table_state& table() const;

  ///
  /// Initializes the table dofs ("class variables")
  ///
  void initialize_table_dofs(void* xtable_dofs, size_t xtable_dof_ub);

  ///
  /// Installs xdof_tuple as the table dof tuple.
  ///
  void initialize_table_dof_tuple(array_poset_dof_map* xdof_tuple);

private:

  //@}

  // ===========================================================
  /// @name ROW DOF FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// The map from row dof client_ids to row dof values
  /// for dof tuple hub id xtuple_hub_id.
  ///
  virtual poset_dof_map& row_dof_map(pod_index_type xtuple_hub_id,
				     bool xrequire_write_access = false) const;

  ///
  /// The map from row dof client_ids to row dof values
  /// for dof tuple id xtuple_id.
  ///
  poset_dof_map& row_dof_map(const scoped_index& xtuple_id,
			     bool xrequire_write_access = false) const;

  ///
  /// Creates a new row dof map.
  ///
  virtual const scoped_index& new_row_dof_map();

  ///
  /// Creates a new row dof map which is a clone of xprototype.
  ///
  virtual const scoped_index& clone_row_dof_map(const poset_dof_map& xprototype);

  ///
  /// The dof map associated with the member identified by
  /// hub id xmbr_hub_id (mutable version).
  ///
  poset_dof_map& member_dof_map(pod_index_type xmbr_hub_id, bool xrequire_write_access = false);

  ///
  /// The dof map associated with the member identified by xmbr_index (mutable version).
  ///
  poset_dof_map& member_dof_map(const scoped_index& xmbr_id, bool xrequire_write_access = false);

  ///
  /// The dof map associated with the member identified by
  /// hub id xmbr_hub_id (const version).
  ///
  const poset_dof_map& member_dof_map(pod_index_type xmbr_hub_id, bool xrequire_write_access = false) const;

  ///
  /// The dof map associated with the member identified by xmbr_index (const version).
  ///
  const poset_dof_map& member_dof_map(const scoped_index& xmbr_id, bool xrequire_write_access = false) const;

  ///
  /// Copies the dof tuple of the member with hub id xmbr_hub_id 
  /// into the buffer xbuf of length xbuf_len bytes.
  ///
  void member_dof_tuple(pod_index_type xmbr_hub_id, void* xbuf, size_t xbuf_len, bool xauto_access) const;

  ///
  /// Copies the contents of the buffer xbuf of len xbuf_len 
  /// into the dof tuple of the member with hub id xmbr_hub_id.
  ///
  void put_member_dof_tuple(pod_index_type xmbr_hub_id, void* xbuf, size_t xbuf_len, bool xauto_access);

  ///
  /// The dof tuple hub id of the member with hub id xmbr_hub_id
  ///
  pod_index_type member_dof_tuple_id(pod_index_type xmbr_hub_id, bool xauto_access) const;

  ///
  /// The dof tuple index of the member with id xmbr_id
  ///
  void member_dof_tuple_id(const scoped_index& xmbr_id, scoped_index& result, bool xauto_access) const;

  ///
  /// Sets the dof tuple hub id of the member
  /// with hub id xmbr_hub_id to xtuple_hub_id
  ///
  void put_member_dof_tuple_id(pod_index_type xmbr_hub_id,
			       pod_index_type xtuple_hub_id,
			       bool xauto_access);

  ///
  /// Sets the dof tuple id of the member
  /// with id xmbr_id to xtuple_id
  ///
  void put_member_dof_tuple_id(const scoped_index& xmbr_id,
			       const scoped_index& xtuple_id,
			       bool xauto_access);

  ///
  /// True if this contains a tuple with hub id xtuple_hub_id.
  ///
  bool contains_row_dof_tuple(pod_index_type xtuple_hub_id) const;

  ///
  /// True if this contains a tuple with id xtuple_id.
  ///
  bool contains_row_dof_tuple(const scoped_index& xtuple_id) const;

  ///
  /// The number of row_dof_tuples of this poset
  ///
  size_type row_dof_tuple_ct() const;

  ///
  /// The number of standard row_dof_tuples automatically
  /// allocated by the constructor.
  ///
  int standard_row_dof_tuple_ct() const;

  ///
  /// True if poset is in its initial state,
  /// that is, it contains just the standard row_dof_tuples.
  ///
  bool has_standard_row_dof_tuple_ct() const;

protected:

private:

  //@}

  // ===========================================================
  /// @name DOF TUPLE ID SPACE FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Collection of dof tuple id spaces for this (const version).
  ///
  const index_space_family& dof_tuple_id_spaces(bool xauto_access) const;

  ///
  /// Collection of dof tuple id spaces for this (mutable version).
  ///
  index_space_family& dof_tuple_id_spaces(bool xauto_access);

  ///
  /// The dof tuple hub id space.
  ///
  const hub_index_space_handle& dof_tuple_hub_id_space(bool xauto_access) const;  

  ///
  /// An id in the dof tuple hub id space;
  /// intended for copying to initialize ids
  /// to the dof tuple id space.
  ///
  virtual const scoped_index& dof_tuple_id(bool xauto_access) const;

  ///
  /// An id in the dof tuple hub id space with pod xid.
  ///
  scoped_index dof_tuple_id(pod_index_type xid, bool xauto_access) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name SCHEMATIZATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this poset has been prepared for use as a schema,
  /// that is, if the top member has been schematized.
  ///
  virtual bool is_schematized(bool xauto_access) const;

  ///
  /// Prepare this poset and its top member for use as a schema.
  /// If xall_members = true, schematize all other members as well.
  ///
  virtual void schematize(subposet* xtable_dof_subposet,
                          subposet* xrow_dof_subposet,
                          bool xall_members = false);

protected:

  ///
  /// Initialize the id space for the dof subposet, xdof_subposet.
  ///
  void initialize_dof_id_space(subposet& xdof_subposet);

private:

  //@}


  // ===========================================================
  /// @name VERSION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of versions currently defined.
  ///
  virtual int version_ct() const;

  ///
  /// The current version
  ///
  virtual int version() const;

  ///
  /// The subposet hub id of the whole() subposet for version xversion.
  ///
  virtual pod_index_type version_index(int xversion) const;

  ///
  /// The subposet id of the whole() subposet for version xversion.
  ///
  void version_index(int xversion, scoped_index& result) const;

  ///
  /// The subposet hub id of the jims() subposet for version xversion.
  ///
  virtual pod_index_type version_jims_index(int xversion) const;

  ///
  /// The subposet id of the jims() subposet for version xversion.
  ///
  void version_jims_index(int xversion, scoped_index& result) const;

  ///
  /// True if xversion is a valid version.
  ///
  bool has_version(int xversion) const;

  ///
  /// True if this poset is a version.
  ///
  bool is_version() const;  

protected:

  ///
  /// The prefix which begins the name of every version subposet.
  ///
  static const std::string& VERSION_PREFIX();

  ///
  /// The length of _version_prefix.
  ///
  static int VERSION_PREFIX_LENGTH();

  ///
  /// True if xname has the proper form for a version name.
  ///
  bool is_version_name(const std::string& xname) const;

  ///
  /// Creates the standard name for the level xversion whole subposet.
  ///
  std::string version_to_name(int xversion) const;

  ///
  /// Extracts the version from the standard name
  ///
  int version_from_name(const std::string& xname) const;

  ///
  /// Set the current level to xversion
  ///
  void put_version(int xversion);

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  // The product subposet hack, version 2 (PSH2).
  // ============================================
  // The abstraction that PSH2 exports via the virtual functions below
  // and their use in the i/o susbsystem is:
  //
  // 1) All member ids, in particular those associated with bounds and
  //    bound iterators, are actual member ids for the poset they belong to.
  //    The PSH1 use of section space schema member ids that were actually
  //    base space member ids is now gone.
  //
  // 2) Subposet ids appearing in bounds are base space subposet ids
  //    for section space schema classes and ordinary subposet ids for
  //    all other classes.
  //
  // 3) All conversion of base space ids to schema ids is handled by
  //    virtual functions in poset_state_handle, schema_poset_member,
  //    and their descendants.

  ///
  /// Creates a member handle of the type appropriate for members of this
  /// when used as a schema. Intended for use only by the i/o subsystem.
  //// @hack the product subposet hack, version 2.
  //// This member exists only to encapsulate the hack.
  ////
  virtual schema_poset_member*
  new_schema_handle(const std::string& xid_space_name,
                    pod_index_type xschema_member_ext_id,
                    pod_index_type xbase_space_ext_id,
                    pod_index_type xfiber_schema_ext_id,
                    pod_index_type xlocal_schema_ext_id);

  ///
  /// An iterator over the members of the decomposition identified by xindex.
  //// @hack the product subposet hack, version 2.
  //// This member exists only to encapsulate the hack.
  ////
  virtual index_iterator* get_decomposition(pod_index_type xindex) const;

  ///
  /// An iterator for the upper bound (xis_ub == true) or the lower bound
  /// (xis_ub == false) for xbounds.
  ///
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  ///
  index_iterator* bound_iterator(const poset_bounds& xbnd_id, bool xis_ub) const;

  ///
  /// True if the upper bound id (xis_ub == true) or the lower bound
  /// (xis_ub == false) of xbounds contains the member specified by xindex.
  ///
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  ///
  bool bound_contains_member(const poset_bounds& xbounds,
			     bool xis_ub,
			     const scoped_index& xindex) const;

  ///
  /// Translates xext_id to an internal id using
  /// the equivalence map with name xid_space_name.
  ///
  pod_index_type get_int_id(pod_index_type xext_id,
			    const std::string& xid_space_name,
			    bool xauto_access) const;

  ///
  /// True if xint_id can be translated to an external id using
  /// the equivalence map with name xid_space_name.
  ///
  virtual bool is_valid_int_id(pod_index_type xint_id,
			       const std::string& xid_space_name,
			       bool xauto_access) const;

  ///
  /// True if xint_id can be translated to an external id using
  /// the equivalence map with name xid_space_name.
  ///
  bool is_valid_int_id(const scoped_index& xint_id,
		       const std::string& xid_space_name,
		       bool xauto_access) const;

  ///
  /// Translates xint_id to an external id using
  /// the equivalence map with name xid_space_name.
  ///
  virtual pod_index_type get_ext_id(pod_index_type xint_id,
				    const std::string& xid_space_name,
				    bool xauto_access) const;

  ///
  /// Translates xint_id to an external id using
  /// the equivalence map with name xid_space_name.
  ///
  pod_index_type get_ext_id(const scoped_index& xint_id,
			    const std::string& xid_space_name,
			    bool xauto_access) const;

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name DEBUGGING FACET
  // ===========================================================
  //@{

public:

  ///
  ///  Write instance information to an ostream (default = stdout).
  ///
  void to_stream(std::ostream& xos = std::cout);

  ///
  /// Get instance information as a string.
  ///
  std::string to_string();

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual poset_state_handle* clone() const;

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



} // namespace sheaf

#endif // POSET_STATE_HANDLE_H
 

