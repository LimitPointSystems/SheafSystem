
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
/// Interface for class poset_component

#ifndef COM_LIMITPOINT_SHEAF_POSET_COMPONENT_H
#define COM_LIMITPOINT_SHEAF_POSET_COMPONENT_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_STATE_H
#include "ComLimitPoint/sheaf/poset_state.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_READ_WRITE_MONITOR_HANDLE_H
#include "ComLimitPoint/sheaf/read_write_monitor_handle.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SCOPED_INDEX_H
#include "ComLimitPoint/sheaf/scoped_index.h"
#endif
 
#ifndef COM_LIMITPOINT_SHEAF_STANDARD_VERSION_INDEX_H
#include "ComLimitPoint/sheaf/standard_version_index.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

  class namespace_poset;
  class poset;
  class poset_crg_state;
  class poset_dof_map;
  class poset_path;
  class poset_powerset_state;
  class poset_state;
  class poset_state_handle;
  class subposet_state;

///
/// Features shared by poset_member and subposet. <br>
/// <br>
/// Subposet and poset_member objects can be attached, detached, and
/// reattached to the poset_state object in a manner similar to the way object
/// references can be attached, detached, and reattached to objects in Eiffel
/// and in Java. This class provides the routines for managing the state
/// attachment for these 2 poset component types. <br>
/// <br>
/// <b>Note:</b> this class is intended only for convenience of implementation.
/// It is is not intended to be used as an abstract interface by clients and
/// may not reliably function as such.
///
class SHEAF_DLL_SPEC poset_component : public read_write_monitor_handle
{

  // ===========================================================
  /// @name POSET_COMPONENT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor.
  ///
  virtual ~poset_component();

protected:

  ///
  /// Default constructor
  ///
  poset_component();

  ///
  /// The state this component handle is attached to.
  ///
  poset_state* state_obj() const;

  ///
  /// The set of subposets of host().
  ///
  poset_powerset_state* powerset() const;

  ///
  /// The cover relation graph of host().
  ///
  poset_crg_state* crg() const;

  ///
  /// The hidden state of the subposet asocciated with index xindex.
  ///
  virtual subposet_state* powerset_member(const scoped_index& xindex) const;

  ///
  /// The row dof tuple associated with xindex.
  ///
  poset_dof_map* row_dof_tuple(const scoped_index& xindex) const;

  ///
  /// Initializes handle data members when attaching
  /// to a different member in a different host;
  /// intended to be redefined in derived classes.
  ///
  virtual void init_handle_data_members();

  ///
  /// Initializes handle data members when attaching
  /// to a different member of the same host;
  /// intended to be redefined in derived classes.
  ///
  virtual void attach_handle_data_members();

  ///
  /// The host poset for this component.
  ///
  poset_state_handle* _host;

  ///
  /// The index for this component within the host.
  ///
  scoped_index _index;

  ///
  /// The version of this component. The version of the host
  /// used when evaluating properties of this component.
  ///
  int _version;

private:

  //@}


  // ===========================================================
  /// @name COMPONENT INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// The index of the component state this handle is attached to.
  ///
  const scoped_index& index() const;

  ///
  /// True if there exists a component of the same type as this
  /// with hub id xhub_id in version xversion of xhost.
  ///
  virtual bool is_valid_index(const poset_state_handle* xhost,
                              pod_index_type xhub_id,
                              int xversion = CURRENT_HOST_VERSION) const = 0;

  ///
  /// True if there exists a component of the same type as this
  /// with id xid in version xversion of xhost.
  ///
  bool is_valid_index(const poset_state_handle* xhost,
		      const scoped_index& xid,
		      int xversion = CURRENT_HOST_VERSION) const;

  ///
  /// The hub id space; const version.
  ///
  virtual const hub_index_space_handle& hub_id_space() const = 0;  

  ///
  /// A id in the hub id space for components of this type;
  /// intended for copying to initialize ids to the hub id space.
  ///
  virtual const scoped_index& hub_id() const = 0;

  ///
  /// An id in the member hub id space with pod xid.
  ///
  virtual scoped_index hub_id(pod_index_type xid) const = 0;

  ///
  /// Gets the index of the component in xhost with name xname.
  ///
  virtual pod_index_type get_index_from_name(const poset_state_handle* xhost,
					     const std::string& xname) const = 0;

  ///
  /// Gets the index of the component in xhost with name xname.
  ///
  virtual void get_index_from_name(const poset_state_handle* xhost,
				   const std::string& xname,
				   scoped_index& result) const = 0;

  ///
  /// The (possibly aliased) version of this component. The version of the host
  /// used when evaluating properties of this component.
  /// If unalias == true, return actual version alias refers to.
  ///
  int version(bool xunalias = true) const;

  ///
  /// Sets version to (possibly aliased) xversion. If unalias == true,
  /// set version to the actual version alias refers to.
  ///
  virtual void put_version(int xversion, bool xunalias = false);

  ///
  /// The actual version associated with
  /// (possibly aliased) version xversion in this.
  ///
  int unaliased_version(int xversion) const;

  ///
  /// The subposet index for the filter associated with version().
  ///
  pod_index_type version_index() const;

  ///
  /// The subposet index for the filter associated with version().
  ///
  void version_index(scoped_index& result) const;

  ///
  /// The subposet name for the filter associated with version().
  ///
  std::string version_name() const;

  ///
  /// True if xversion is a valid version for this.
  ///
  bool has_version(int xversion) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name COMPONENT NAME FACET
  // ===========================================================
  //@{

public:

  ///
  /// OBSOLETE: use name(bool xauto_access).
  /// A name for this.
  ///
  std::string name() const;

  ///
  /// A name for this.
  ///
  virtual std::string name(bool xauto_access) const = 0;

  ///
  /// All the names for this.
  ///
  virtual void all_names(block<std::string>& xresult, bool xauto_access = false) const = 0;

  ///
  /// The number of names for this.
  ///
  virtual size_type name_ct(bool xauto_access) const = 0;

  ///
  /// True if xname is a name for this.
  ///
  virtual bool has_name(const std::string& xname, bool xauto_access = false) const = 0;

  ///
  /// Make xname a name for this; if xunique, make xname the only name.
  ///
  virtual void put_name(const std::string& xname, bool xunique, bool xauto_access) = 0;

  ///
  /// Delete all names for this.
  ///
  virtual void delete_name(const std::string& xname, bool xauto_access = false) = 0;

  ///
  /// Delete all the names for this.
  ///
  virtual void delete_all_names(bool xauto_access = false) = 0;

  ///
  /// True if there exists a component as the same type as this in xhost with
  /// name xname
  ///
  bool is_valid_name(const poset_state_handle* xhost, const std::string& xname) const;

  ///
  /// A path to this component.
  ///
  poset_path path(bool xauto_access = true) const;

  ///
  /// True if and only if xpath refers to this component.
  ///
  bool has_path(const poset_path& xpath, bool xauto_access) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HOST POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The poset which this is a handle to a component of.
  ///
  poset_state_handle* host() const;

  ///
  /// True if xother conforms to host
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* xther) const;

  ///
  /// True if xother is attached to the same host as this or if both are
  /// unattached
  ///
  bool has_same_host(const poset_component* xother) const;

  ///
  /// Synonym for has_same_host(xother)
  ///
  inline bool in_same_space(const poset_component* xother) const
  {
    return has_same_host(xother);
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name NAMESPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The namespace of host()
  ///
  virtual namespace_poset* name_space() const;

  ///
  /// True if xother conforms to name_space().
  ///
  virtual bool namespace_is_ancestor_of(const namespace_poset* xother) const;

  ///
  /// True if the host of xother resides in the same namespace as this or if
  /// both are unattached.
  ///
  bool same_namespace(const poset_component* xother) const;

  ///
  /// True if xother resides in the same namespace as the host of this or if
  /// both are unattached.
  ///
  bool same_namespace(const poset_state_handle* xother) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Attach this handle to the state with hub id xhub_id in
  /// the current version of host xhost
  ///
  void attach_to_state(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Attach this handle to the state with id xid in
  /// the current version of host xhost
  ///
  void attach_to_state(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Attach to the member state with name xname in
  /// the current version of host xhost.
  ///
  void attach_to_state(const poset_state_handle* xhost, const std::string& xname);

  // Not included in generated documentation; would just be confusing.
  inline void attach_to_state(const namespace_poset* xhost, const std::string& xname)
  {
    // This routine needed to resolve ambiguity between the preceeding
    // routine and attach_to_state(namespace_poset*, const poset_path&),
    // when called with signature (namespace_poset*, const std::string&).
    // Compiler can't choose between conversion of namespace_poset* to
    // poset_state_handle* versus conversion of const std::string& to const poset_path&.

    attach_to_state(reinterpret_cast<const poset_state_handle*>(xhost), xname);
  };

  ///
  /// Attach to the state with name xname in version version() of
  /// host host().
  ///
  void attach_to_state(const std::string&);

  ///
  /// Attach to the state with hub id xhub_id in version version() of
  /// host host().
  ///
  void attach_to_state(pod_index_type xhub_id);

  ///
  /// Attach to the state with id xid in version version() of
  /// host host().
  ///
  void attach_to_state(const scoped_index& xid);

  ///
  /// Attach to the same state as xother.
  ///
  void attach_to_state(const poset_component* xother);

  ///
  /// Attach to the same state as xother, auto-accessible version.
  ///
  void attach_to_state(const poset_component* xother, bool xauto_access);

  ///
  /// Detach this handle from its state, if any.
  ///
  virtual void detach_from_state();

  ///
  /// Detach this from its state and delete the state.
  ///
  virtual void delete_state(bool xauto_access = false) = 0;

  ///
  /// True if this handle is attached to a non-void state.
  ///
  virtual bool is_attached() const;

  ///
  /// True is this is attached to state with hub id xhub_id in host xhost
  ///
  bool is_same_state(const poset_state_handle* xhost,
                     pod_index_type xhub_id) const;

  ///
  /// True is this is attached to state with id xid in host xhost
  ///
  bool is_same_state(const poset_state_handle* xhost,
                     const scoped_index& xid) const;

  ///
  /// True if xother is attached to the same host and same state as this or
  /// if both are unattached
  ///
  bool is_same_state(const poset_component* xother) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name STATE ACCESS CONTROL FACET
  // ===========================================================
  //@{

public:

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

protected:

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
  virtual poset_component* clone() const = 0;

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
/// The deep size of the referenced object of type poset_component.
///

SHEAF_DLL_SPEC size_t deep_size(const poset_component& xp, bool xinclude_shallow = true);

 } // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_POSET_COMPONENT_H

