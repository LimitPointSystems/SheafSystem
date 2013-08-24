

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class namespace_poset

#ifndef NAMESPACE_POSET_H
#define NAMESPACE_POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

#ifndef NAMESPACE_POSET_DOF_MAP_H
#include "namespace_poset_dof_map.h"
#endif

#ifndef NAMESPACE_POSET_SCHEMA_H
#include "namespace_poset_schema.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_HANDLE_H
#include "mutable_index_space_handle.h"
#endif

#ifndef PRIMITIVES_POSET_H
#include "primitives_poset.h"
#endif

#ifndef PRIMITIVES_POSET_SCHEMA_H
#include "primitives_poset_schema.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace sheaf
{

class namespace_poset_member;
class poset_path;
class poset;
class sheaf_file;
class storage_agent;  

///
/// The default name space; a poset which contains other posets as members.
///
class SHEAF_DLL_SPEC namespace_poset : public poset_state_handle
{

  friend class poset_state_handle;
  friend class storage_agent;

  // ===========================================================
  /// @name NAMESPACE_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The current working namespace.
  ///
  static namespace_poset* current_namespace();

  ///
  /// The schema path used for constructing schema posets.
  ///
  static poset_path primitives_schema_path();

  ///
  /// Destructor
  ///
  virtual ~namespace_poset();

  ///
  /// Creates a new namespace with name xname.
  ///
  namespace_poset(const string& xname);

  ///
  /// The primitives poset within this namespace (mutable version)
  ///
  inline primitives_poset& primitives()
  {
    return _primitives;
  };

  ///
  /// The primitives poset within this namespace (const version)
  ///
  inline const primitives_poset& primitives() const
  {
    return _primitives;
  };

  ///
  /// The primitives poset schema within this namespace (mutable version)
  ///
  inline primitives_poset_schema& primitives_schema()
  {
    return _primitives_schema;
  };

  ///
  /// The primitives poset schema within this namespace (const version)
  ///
  inline const primitives_poset_schema& primitives_schema() const
  {
    return _primitives_schema;
  };

  ///
  /// The namespace poset schema within this namespace (mutable version)
  ///
  inline namespace_poset_schema& namespace_schema()
  {
    return _namespace_schema;
  };

  ///
  /// The namespace poset schema within this namespace (const version)
  ///
  inline const namespace_poset_schema& namespace_schema() const
  {
    return _namespace_schema;
  };

  ///
  /// Removes all members except the standard members.
  ///
  void clear();

  ///
  /// Initialize all the prototypes needed by various factory methods,
  ///
  static void initialize_prototypes();

  ///
  /// Initialize the prototypes needed by poset factory method,
  ///
  static void initialize_poset_prototypes();

  ///
  /// Initialize the prototypes needed by crg interval factory method,
  ///
  static void initialize_crg_interval_prototypes();

  ///
  /// Initialize the prototypes needed by dof map factory method,
  ///
  static void initialize_dof_map_prototypes();

  ///
  /// Initialize the  prototypes needed by id space factory method,
  ///
  static void initialize_id_space_prototypes();

protected:

  ///
  /// Initialize all the prototypes needed by various factory methods;
  /// virtual version.
  ///
  virtual void virtual_initialize_prototypes();

  ///
  /// Default constructor; creates an unattached namespace handle.
  ///
  namespace_poset();

  ///
  /// Covariant constructor.
  ///
  namespace_poset(namespace_poset_member* xtop, namespace_poset_member* xbottom);

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  namespace_poset(const namespace_poset& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  namespace_poset& operator=(const namespace_poset& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  namespace_poset& operator=(const poset_state_handle& xother);

  ///
  /// Creates a new handle attached to the namespace with index xindex
  /// in namespace xhost
  ///
  namespace_poset(const namespace_poset* xhost, pod_index_type xindex);

  ///
  /// Creates a new handle attached to the namespace with index xindex
  /// in namespace xhost
  ///
  namespace_poset(const namespace_poset* xhost, const scoped_index& xindex);

  ///
  /// Sets the current working namespace to xns.
  ///
  void put_current_namespace(namespace_poset* xns);

  ///
  /// Creates additional  members for this namespace.
  ///
  virtual void initialize_additional_members();

  ///
  /// Creates the standard id spaces for this namespace.
  ///
  void initialize_standard_id_spaces();

  ///
  /// Inserts xposet into this namespace with member name xposet_name.
  ///
  scoped_index insert_poset(const poset_state_handle& xposet,
			    const string& xposet_name,
			    bool xauto_link);

  ///
  /// Inserts xposet into this namespace with member name xposet_name.
  ///
  scoped_index insert_poset(const poset_state_handle& xposet,
			    const string& xposet_name,
			    bool xauto_link,
                            bool xauto_access);

  ///
  /// Links xmbr into the appropriate group.
  ///
  virtual void link_poset(const namespace_poset_member& xmbr);

private:

  ///
  /// Poset of primitives for this namespace.
  ///
  primitives_poset _primitives;

  ///
  /// The schema poset for primitives in this namespace.
  ///
  primitives_poset_schema _primitives_schema;

  ///
  /// The schema poset for this namespace.
  ///
  namespace_poset_schema _namespace_schema;

  ///
  /// The current working namespace.
  ///
  static namespace_poset* _current_namespace;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}


  // ===========================================================
  /// @name POSET FACTORY METHOD FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a new poset with name xname, schema specified by xschema_path,  
  /// and table dofs initialzied by xargs.
  ///
  template <typename T>
  SHEAF_DLL_SPEC
  T& new_member_poset(const string& xname,
		      const poset_path& xschema_path,
		      const arg_list& xargs,
		      bool xauto_access);

  ///
  /// Creates a new schema poset with name xname.
  ///
  
  poset& new_schema_poset(const string& xname, bool xauto_access);

  ///
  /// Delete the poset with hub id xhub_id.
  ///
  void delete_poset(pod_index_type xhub_id, bool xauto_access);

  ///
  /// Delete the poset with id xid.
  ///
  void delete_poset(scoped_index xid, bool xauto_access);

  ///
  /// Delete the poset with name xname.
  ///
  void delete_poset(string xname, bool xauto_access);

  ///
  /// Delete the poset with name xpath.poset_name().
  ///
  void delete_poset(poset_path xpath, bool xauto_access);

  ///
  /// Delete the poset associated with xmbr.
  ///
  void delete_poset(namespace_poset_member& xmbr);

  ///
  /// The poset_state_handle object referred to by
  /// the member with hub id xhub_id.
  ///
  poset_state_handle& member_poset(pod_index_type xhub_id, bool xauto_access = true) const;

  ///
  /// The poset_state_handle object referred to by
  /// the member with id xid.
  ///
  poset_state_handle& member_poset(const scoped_index& xid, bool xauto_access = true) const;

  ///
  /// The poset_state_handle object referred to by
  /// the member with hub id xhub_id
  /// dynamically cast to type P*.
  ///
  template <typename P>
  SHEAF_DLL_SPEC
  P& member_poset(pod_index_type xhub_id, bool xauto_access = true) const;

  ///
  /// The poset_state_handle object referred to by
  /// the member with id xid
  /// dynamically cast to type P*.
  ///
  template <typename P>
  SHEAF_DLL_SPEC
  P& member_poset(const scoped_index& xid, bool xauto_access = true) const;

  ///
  /// The poset_state_handle object referred to by
  /// the member with name xpath.poset_name().
  ///
  poset_state_handle& member_poset(const poset_path& xpath, bool xauto_access = true) const;

  ///
  /// The poset_state_handle object referred to by
  /// the member with name xpath.poset_name(), 
  /// dynamically cast to type P*.
  ///
  template <typename P>
  SHEAF_DLL_SPEC
  P& member_poset(const poset_path& xpath, bool xauto_access = true) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET FACTORY METHOD QUERY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The index of the schema of the member poset with index xindex.
  ///
  pod_index_type member_poset_schema_id(const scoped_index& xindex,
					bool xauto_access) const;

  ///
  /// True if this contains a poset with hub id xhub_id..
  ///
  bool contains_poset(pod_index_type xhub_id, bool xauto_access = true) const;

  ///
  /// True if this contains a poset with id xid.
  ///
  bool contains_poset(const scoped_index& xid, bool xauto_access = true) const;

  ///
  /// True if and only if this contains a poset with hub id xhub_id
  /// and the poset conforms to type P.
  ///
  template <typename P>
  SHEAF_DLL_SPEC
  bool contains_poset(pod_index_type xhub_id, bool xauto_access = true) const;

  ///
  /// True if and only if this contains a poset with id xid
  /// and the poset conforms to type P.
  ///
  template <typename P>
  SHEAF_DLL_SPEC
  bool contains_poset(const scoped_index& id, bool xauto_access = true) const;

  ///
  /// True if this contains a poset with name xpath.poset_name().
  ///
  bool contains_poset(const poset_path& xpath, bool xauto_access = true) const;

  ///
  /// True if and only if this contains a poset with name xpath.poset_name()
  /// and the poset conforms (can be dynamically cast) to type P.
  ///
  template <typename P>
  SHEAF_DLL_SPEC
  bool contains_poset(const poset_path& xpath, bool xauto_access = true) const;

  ///
  /// True if and only if this contains the poset xposet.
  /// synonym for contains_poset(xposet.poset_path(true), xauto_access)
  ///
  bool owns(const poset_state_handle& xposet, bool xauto_access) const;

  ///
  /// True if the poset referred to by xpath is read accessible.
  ///
  bool poset_state_is_read_accessible(const poset_path& xpath,
                                      bool xauto_access = true) const;

  ///
  /// True if the poset referred to by xpath is read-write accessible.
  ///
  bool poset_state_is_read_write_accessible(const poset_path& xpath,
					    bool xauto_access = true) const;

  ///
  /// True if this contains a poset with hub id xposet_hub_id which
  /// contains a member with hub id xmember_hub_id.
  ///
  bool contains_poset_member(pod_index_type xposet_hub_id,
                             pod_index_type xmember_hub_id,
                             bool xauto_access = true) const;

  ///
  /// True if this contains a poset with index xposet_id which
  /// contains a member with index xmember_id.
  ///
  bool contains_poset_member(const scoped_index& xposet_id,
                             const scoped_index& xmember_id,
                             bool xauto_access = true) const;

  ///
  /// True if this contains the poset and member specified by xpath.
  ///
  bool contains_poset_member(const poset_path& xpath, bool xauto_access = true) const;

  ///
  /// True if this contains a poset with name xposet_name which
  /// contains all members with names in array xmember_name.
  ///
  bool contains_poset_members(const string& xposet_name,
                              const string  xmember_names[],
                              int xmember_names_ct,
                              bool xauto_access = true) const;

  ///
  /// True if this contains the poset and subposet specified by xpath.
  ///
  bool contains_poset_subposet(const poset_path& xpath, bool xauto_access = true) const;

  ///
  /// True if this contains the poset or poset member specified by xpath.
  ///
  bool contains_path(const poset_path& xpath, bool xauto_access = true) const;

  ///
  /// True if this contains the poset or poset member specified by xpath
  /// and the poset conforms to poset type P.
  ///
  template <typename P>
  bool contains_path(const poset_path& xpath, bool xauto_access = true) const;

  ///
  /// True if the state referred to xpath exists and is auto read accessible.
  ///
  bool path_is_auto_read_accessible(const poset_path& xpath, bool xauto_access) const;

  ///
  /// True if the state referred to xpath exists, is auto read accessible,
  /// and conforms to poset type P.
  ///
  template <typename P>
  bool path_is_auto_read_accessible(const poset_path& xpath, bool xauto_access) const;

  ///
  /// True if the state referred to xpath exists and is auto read-write accessible.
  ///
  bool path_is_auto_read_write_accessible(const poset_path& xpath, bool xauto_access) const;

  ///
  /// True if the state referred to xpath exists, is auto read-write accessible,
  /// and conforms to poset type P.
  ///
  template <typename P>
  bool path_is_auto_read_write_accessible(const poset_path& xpath, bool xauto_access) const;

  ///
  /// True if the state referred to xpath does not exist 
  /// or exists and conforms to poset type P.
  ///
  template <typename P>
  bool path_is_available(const poset_path& xpath, bool xauto_access) const;

  ///
  /// True if the state referred to xpath does not exist 
  /// or exists and is auto read accessible.
  ///
  bool path_is_auto_read_available(const poset_path& xpath, bool xauto_access) const;

  ///
  /// True if the state referred to xpath does not exist 
  /// or exists, conforms to poset type P and is auto read accessible.
  ///
  template <typename P>
  bool path_is_auto_read_available(const poset_path& xpath, bool xauto_access) const;

  ///
  /// True if the state referred to xpath does not exist 
  /// or exists and is auto read-write accessible.
  ///
  bool path_is_auto_read_write_available(const poset_path& xpath, bool xauto_access) const;

  ///
  /// True if the state referred to xpath does not exist 
  /// or exists, conforms to poset type P and is auto read-write accessible.
  ///
  template <typename P>
  bool path_is_auto_read_write_available(const poset_path& xpath, bool xauto_access) const;

  ///
  /// True if the argument with name xname in xargs exists, contains a non-empty
  /// path and the state it refers to exists and is auto read accessible.
  ///
  bool arg_is_auto_read_accessible(const string& xname, const arg_list& xargs, bool xauto_access) const;

  ///
  /// True if the argument with name xname in xargs exists, contains a non-empty
  /// path and the state it refers to exists, conforms to poset type P
  /// and is auto read accessible.
  ///
  template <typename P>
  bool arg_is_auto_read_accessible(const string& xname, const arg_list& xargs, bool xauto_access) const;

  ///
  /// True if the argument with name xname in xargs exists, contains a non-empty
  /// path and the state it refers to exists and is auto read-write accessible.
  ///
  bool arg_is_auto_read_write_accessible(const string& xname, const arg_list& xargs, bool xauto_access) const;

  ///
  /// True if the argument with name xname in xargs exists, contains a non-empty
  /// path and the state it refers to exists, conforms to poset type P
  /// and is auto read-write accessible.
  ///
  template <typename P>
  bool arg_is_auto_read_write_accessible(const string& xname, const arg_list& xargs, bool xauto_access) const;

  ///
  /// True if the argument with name xname in xargs exists, contains a non-empty
  /// path and the state it refers to exists and is auto read available.
  ///
  bool arg_is_auto_read_available(const string& xname, const arg_list& xargs, bool xauto_access) const;

  ///
  /// True if the argument with name xname in xargs exists, contains a non-empty
  /// path and the state it refers to exists, conforms to poset type P
  /// and is auto read available.
  ///
  template <typename P>
  bool arg_is_auto_read_available(const string& xname, const arg_list& xargs, bool xauto_access) const;

  ///
  /// True if the argument with name xname in xargs exists, contains a non-empty
  /// path and the state it refers to exists and is auto read available.
  ///
  bool arg_is_auto_read_write_available(const string& xname, const arg_list& xargs, bool xauto_access) const;

  ///
  /// True if the argument with name xname in xargs exists, contains a non-empty
  /// path and the state it refers to exists, conforms to poset type P
  /// and is auto read available.
  ///
  template <typename P>
  bool arg_is_auto_read_write_available(const string& xname, const arg_list& xargs, bool xauto_access) const;

protected:

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

  ///
  /// Allow editing of jims and jim order relation.
  ///
  virtual void begin_jim_edit_mode(bool xauto_access = true);

  ///
  /// prevent editing of jims and jim order relation
  ///
  virtual void end_jim_edit_mode(bool xensure_lattice_invariant = true,
                                 bool xauto_access = true);

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

  using poset_state_handle::new_state;

  ///
  /// Creates a new namespace state with name xname and attaches this to it.
  ///
  void new_state(const string& xname);

  ///
  /// Detaches this from its state
  ///
  virtual void detach_from_state();

  ///
  /// Initializes the handle data members when this handle
  /// is attached to a state.
  ///
  virtual void attach_handle_data_members();

private:

  //@}


  // ===========================================================
  /// @name GLOBAL ATTRIBUTES FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of this poset
  ///
  virtual string name() const;

  ///
  /// The name of this poset
  ///
  virtual string name(bool xauto_access) const;

  ///
  /// The path of this poset.
  ///
  virtual poset_path path(bool xauto_access = true) const;

protected:

  using poset_state_handle::initialize_namespace;

  ///
  /// Installs this as a member of xns.
  ///    
  virtual void initialize_namespace(namespace_poset& xns, bool xauto_link = true);

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
  typedef namespace_poset_schema schema_type;

  ///
  /// True if xdof_map conforms to (is derived from) the type of
  /// row dof map required by this poset
  ///
  virtual bool row_dof_map_conforms(const poset_dof_map* xdof_map) const;

  ///
  /// The map from row dof client_ids to row dof values
  /// for dof tuple hub id xtuple_hub_id
  ///
  virtual namespace_poset_dof_map& row_dof_map(pod_index_type xtuple_hub_id,
					       bool xrequire_write_access = false) const;

  ///
  /// Creates a new row dof map appropriate for jims of this
  ///
  virtual const scoped_index& new_row_dof_map();

protected:

private:

  //@}


  // ===========================================================
  /// @name MEMBERSHIP FACET
  // ===========================================================
  //@{

public:

  ///
  /// The top member of the poset (mutable version)
  ///
  namespace_poset_member& top();

  ///
  /// The top member of the poset (const version)
  ///
  const namespace_poset_member& top() const;

  ///
  /// The bottom member of the poset (mutable version)
  ///
  namespace_poset_member& bottom();

  ///
  /// The bottom member of the poset (const version)
  ///
  const namespace_poset_member& bottom() const;

protected:

  ///
  /// Creates the standard members for this namespace.
  ///
  virtual void initialize_standard_members();

private:

  //@}

  // ===========================================================
  /// @name MEMBER ID SPACE FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates a handle for the id space for member posets
  /// from the pool of id space handles.
  ///
  const index_space_handle& get_member_poset_id_space(bool xauto_access) const;

  ///
  /// Returns the handle for the id space for member posets
  /// to the pool of id space handles.
  ///
  void release_member_poset_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocates a iterator for the id space for member posets.
  /// from the pool of id space iterators.
  ///
  index_space_iterator& get_member_poset_id_space_iterator(bool xauto_access) const;

  ///
  /// Returns the iterator for the id space for member posets
  /// to the pool of id space iterators.
  ///
  void release_member_poset_id_space_iterator(index_space_iterator& xid_space, bool xauto_access) const;

protected:

private:

  //@}
 

  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;  

protected:

  ///
  /// Sets name() to xname.
  /// Intended for use only by storage_agent::begin_read_transaction(namespace_poset&).
  ///
  void put_name(const string& xname);

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
  void to_stream(ostream& xos = cout);


  ///
  /// Get instance information as a string.
  ///
  string to_string();

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
  namespace_poset* clone() const;

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
/// Insert namespace_poset& p into ostream& os.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &os, const namespace_poset& p);

///
///The deep size of the referenced object of type namespace_poset.
///
SHEAF_DLL_SPEC 
size_t deep_size(const namespace_poset& xp, bool xinclude_shallow = true, size_t xresults[4] = 0);
 
} // namespace sheaf

#endif // ifndef NAMESPACE_POSET_H
