

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class schema_poset_member.

#ifndef SCHEMA_POSET_MEMBER_H
#define SCHEMA_POSET_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TOTAL_POSET_MEMBER_H
#include "total_poset_member.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_HANDLE_H
#include "explcit_index_space_handle.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef PRIMITIVES_POSET_DOF_MAP_H
#include "primitives_poset_dof_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

template <typename T> class block;
template <class T> class wsv_block;
class index_iterator;
class list_cover_set;
class dof_descriptor_array;
class poset_bounds;
class poset_member_dof_iterator;
class poset_member_iterator;
class poset_dof_iterator;
class schema_descriptor;
class storage_agent;
class subposet;  

///
/// A client handle for a poset member which has been prepared for use as a schema.
///
class SHEAF_DLL_SPEC schema_poset_member : public total_poset_member
{
  friend class array_poset_dof_map;
  friend class dof_tuple_record_set;
  friend SHEAF_DLL_SPEC size_t deep_size(const schema_poset_member& xp, bool xinclude_shallow);

  // ===========================================================
  /// @name SCHEMA_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached schema_poset_member handle.
  ///
  schema_poset_member();

  ///
  /// Copy constructor; creates a new schema_poset_member handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit schema_poset_member(const abstract_poset_member& xother,
                               bool xnew_jem = false,
                               bool xauto_access = true);

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline schema_poset_member* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<schema_poset_member*>(total_poset_member::clone(xnew_state, xauto_access));
  }

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual schema_poset_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  schema_poset_member& operator=(const schema_poset_member& xother);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~schema_poset_member();

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a new handle attached to a new jim (join-irreducible member)
  /// state in xhost with dof map a copy of the primitive of type xprimitive_type.
  ///
  schema_poset_member(poset_state_handle* xhost,
                      primitive_type xprimitive_type,
                      bool xauto_access = true);

  ///
  /// Creates a new jim (join-irreducible member) attached to a new member
  /// state in xhost. ("explicit"  prevents interpretation as implicit
  /// conversion from poset_state_handle* to schema_poset_member&)
  ///
  explicit schema_poset_member(poset_state_handle* xhost,
                               primitives_poset_dof_map* xdof_map = 0,
                               bool xcopy_dof_map = false,
                               bool xauto_access = true);

  ///
  /// Creates a new jrm (join reducible member) attached to a new member state
  /// in xhost.  The jrm created is the join of the members with the indices
  /// given in xexpansion.
  ///
  schema_poset_member(poset_state_handle* xhost,
                      const scoped_index* xexpansion,
                      int xexpansion_ct,
                      const tern& xnew_jem,
                      bool xauto_access);


  ///
  /// Creates a new jim which conforms_to the schema with path xparent_path
  /// and has additional dofs with names, types, and roles specified by xdof_specs.
  /// Xschematize is obsolete and is ignored.
  ///
  schema_poset_member(const namespace_poset& xns,
                      const string& xname,
                      const poset_path& xparent_path,
                      const wsv_block<schema_descriptor>& xdof_specs,
                      bool xauto_access);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new schema_poset_member handle attached to the member state
  /// with hub id xhub_id in xhost
  ///
  schema_poset_member(poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new schema_poset_member handle attached to the member state
  /// with id xid in xhost
  ///
  schema_poset_member(poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new schema_poset_member handle attached to the member state
  /// with name xname in xhost
  ///
  schema_poset_member(const poset_state_handle* xhost, const string& xname);

  ///
  /// Creates a new schema_poset_member handle attached to the member state
  /// with path xpath in namespace xnamespace
  ///
  schema_poset_member(const namespace_poset* xnamespace,
                      const poset_path& xpath,
                      bool xauto_access = true);

  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  // Make sure next declaration overloads
  // inherited new_jim_state functions.

  using total_poset_member::new_jim_state;

  ///
  /// Creates a new jim state in host() with dof map a copy
  /// of the primitive type specified by xprimitive_type.
  ///
  void new_jim_state(primitive_type xprimitive_type,
                     bool xauto_access = true);

  ///
  /// Creates a new jim state in host xhost with dof map a copy
  /// of the primitive type specified by xprimitive_type.
  ///
  void new_jim_state(poset_state_handle* xhost,
                     primitive_type xprimitive_type,
                     bool xauto_access = true);

  ///
  /// Creates a new jim with name xname which conforms_to the schema with path
  /// xparent_path in namespace xns and has additional dofs with names, types,
  /// and roles specified by xdof_specs. If a dof named in xdof_specs already
  /// exists, it is used and the type and role in the spec are ignored.
  /// Otherwise, a dof with the name, type, and role given in the spec is created.
  /// Warning: the jim created by the function will directly cover the parent and
  /// the members given in xdof_specs. The client must ensure that these cover
  /// links define a valid cover relation. In particular, if the join of some or
  /// all of the members in xdof_specs has been instantiated, it should appear
  /// in xdof_specs instead.
  ///
  void new_jim_state(const namespace_poset& xns,
                     const string& xname,
                     const poset_path& xparent_path,
                     const wsv_block<schema_descriptor>& xdof_specs,
                     bool xauto_access);

  ///
  /// The number of table dofs (xis_table_dof true)
  /// or row dofs defined by the schema specified by xns and xpath.
  ///
  ///
  static int dof_ct(const namespace_poset& xns,
                    const poset_path& xpath,
                    bool xis_table_dof,
                    bool xauto_access = true);

  ///
  /// The number of tablr dofs defined by the schema specified by xns and xpath.
  /// Synonym for dof_ct(xns, xpath, true, xauto_access).
  ///
  ///
  static int table_dof_ct(const namespace_poset& xns,
                          const poset_path& xpath,
                          bool xauto_access = true);

  ///
  /// The number of row dofs defined by the schema specified by xns and xpath.
  /// Synonym for dof_ct(xns, xpath, false, xauto_access).
  ///
  ///
  static int row_dof_ct(const namespace_poset& xns,
                        const poset_path& xpath,
                        bool xauto_access = true);

  ///
  /// The number of table dofs (xis_table_dof true)
  /// or row dofs defined by this schema.
  ///
  int dof_ct(bool xis_table_dof) const;

  ///
  /// The number of table dofs defined by this schema.
  /// Synonym for dof_ct(true).
  ///
  int table_dof_ct() const;

  ///
  /// The number of row dofs defined by this schema.
  /// Synonym for dof_ct(false).
  ///
  int row_dof_ct() const;

  ///
  /// The number of dofs in the dof tuple for jims of this poset;
  ///
  virtual int dof_ct() const
  {
    return total_poset_member::dof_ct();
  };

  ///
  /// The size in bytes of the table dof tuple (xis_table_dof true)
  /// or the row dof tuple defined by this schema.
  ///
  size_t dof_tuple_ub(bool xis_table_dof) const;

  ///
  /// The size in bytes of the table dof tuple defined by this schema.
  /// Synonym for dof_tuple_ub(true).
  ///
  size_t table_dof_tuple_ub() const;

  ///
  /// The size in bytes of the row dof tuple defined by this schema.
  /// Synonym for dof_tuple_ub(false).
  ///
  size_t row_dof_tuple_ub() const;

  ///
  /// The type of table dofs (xis_table_dof == true) or
  /// row dofs (xis_table_dof == false) defined by this schema.
  /// Returns NOT_A_PRIMITIVE_TYPE if the dofs are
  /// not all the same type.
  ///
  virtual primitive_type dof_tuple_type(bool xis_table_dof) const;

  

  ///
  /// The type of table dofs defined by this.
  /// Synonym for dof_tuple_type(true).
  ///
  inline primitive_type table_dof_tuple_type() const
  {
    return dof_tuple_type(true);
  };

  

  ///
  /// The type of row dofs defined by this.
  /// Synonym for dof_tuple_type(false).
  ///
  inline primitive_type row_dof_tuple_type() const
  {
    return dof_tuple_type(false);
  };

  ///
  /// True if all the table dofs (xis_table_dof == true) or
  /// all the row dofs (xis_table_dof == false) defined by
  /// this have the same type.
  ///
  bool dof_tuple_is_homogeneous(bool xis_table_dof) const;

  ///
  /// True if all the table dofs have the same type.
  /// Synonym for dof_tuple_is_homogeneous(true);
  ///
  inline bool table_dof_tuple_is_homogeneous() const
  {
    return dof_tuple_is_homogeneous(true);
  };

  ///
  /// True if all the row dofs have the same type.
  /// Synonym for dof_tuple_is_homogeneous(false);
  ///
  inline bool row_dof_tuple_is_homogeneous() const
  {
    return dof_tuple_is_homogeneous(false);
  };

  ///
  /// The standard name for the table (xis_table_dof true) or
  /// row (xis_table_dof false) dof subposet
  /// associated with the schema member with name xname.
  ///
  static string dof_subposet_name(const string& xname, bool xis_table_dof);

  ///
  /// The standard name for the table dof subposet
  /// associated with the schema member with name xname.
  /// Synonym for dof_subposet_name(xname, true).
  ///
  static inline string table_dof_subposet_name(const string& xname)
  {
    return dof_subposet_name(xname, true);
  };

  ///
  /// The standard name for the row dof subposet
  /// associated with the schema member with name xname.
  /// Synonym for dof_subposet_name(xname, false).
  ///
  static inline string row_dof_subposet_name(const string& xname)
  {
    return dof_subposet_name(xname, false);
  };

  ///
  /// The standard name for the table (xis_table_dof true) or
  /// row (xis_table_dof false) dof subposet
  /// associated with this schema member.
  ///
  string dof_subposet_name(bool xis_table_dof) const;

  ///
  /// The standard name for the table dof subposet
  /// associated with this schema member.
  /// Synonym for dof_subposet_name(true).
  ///
  inline string table_dof_subposet_name() const
  {
    return dof_subposet_name(true);
  };

  ///
  /// The standard name for the row dof subposet
  /// associated with this schema member.
  /// Synonym for dof_subposet_name(false).
  ///
  inline string row_dof_subposet_name() const
  {
    return dof_subposet_name(false);
  };

  /// @todo schema_poset_member should not export the dof subposets.

  ///
  /// The index in host() of the subposet containing the
  /// the table dofs in the down set of this (const version).
  ///
  ///
  const scoped_index& table_dof_subposet_index() const;

  ///
  /// The index in host() of the subposet containing the
  /// the row dofs in the down set of this (const version).
  ///
  ///
  const scoped_index& row_dof_subposet_index() const;

  ///
  /// The index in host() of the subposet containing the
  /// the table dofs (xis_table_dof true) or row dofs
  /// in the down set of this.
  ///
  ///
  inline const scoped_index& dof_subposet_index(bool xis_table_dof) const
  {
    return xis_table_dof ? table_dof_subposet_index(): row_dof_subposet_index();
  };

  ///
  /// True if xother is a dof in the table dofs part (xin_table_dofs == true) or
  /// in the row dofs part (xin_table_dofs == false) of the schema defined by this.
  ///
  bool contains_dof(const schema_poset_member& xother, bool xin_table_dofs) const;

  ///
  /// True if this is in the table dofs part of the schema defined by this.
  /// Synonym for contains_dof(xother, true).
  ///
  inline bool contains_table_dof(const schema_poset_member& xother) const
  {
    return contains_dof(xother, true);
  };

  ///
  /// True if this is in the row dofs part of the schema defined by this.
  /// Synonym for contains_dof(xother, false).
  ///
  inline bool contains_row_dof(const schema_poset_member& xother) const
  {
    return contains_dof(xother, false);
  };

  ///
  /// True if xother_id is the index of a dof in the
  /// table dofs part (xin_table_dofs == true) or
  /// in the row dofs part (xin_table_dofs == false)
  /// of the schema defined by this.
  ///
  bool contains_dof(pod_index_type xother_id, bool xin_table_dofs) const;

  ///
  /// True if xother_id is the index of a dof in the
  /// table dofs part (xin_table_dofs == true) or
  /// in the row dofs part (xin_table_dofs == false)
  /// of the schema defined by this.
  ///
  bool contains_dof(const scoped_index& xother_id, bool xin_table_dofs) const;

  ///
  /// True if xname is the name of a dof in the
  /// table dofs part (xin_table_dofs == true) or
  /// in the row dofs part (xin_table_dofs == false)
  /// of the schema defined by this.
  ///
  bool contains_dof(const string& xname, bool xin_table_dofs) const;

  ///
  /// True if xother_id is the index of a dof in the table dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, true).
  ///
  inline bool contains_table_dof(pod_index_type xother_id) const
  {
    return contains_dof(xother_id, true);
  };

  ///
  /// True if xother_id is the index of a dof in the table dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, true).
  ///
  inline bool contains_table_dof(const scoped_index& xother_id) const
  {
    return contains_dof(xother_id.hub_pod(), true);
  };

  ///
  /// True if xother_id is the index of a dof in the row dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, false).
  ///
  inline bool contains_row_dof(pod_index_type xother_id) const
  {
    return contains_dof(xother_id, false);
  };

  ///
  /// True if xother_id is the index of a dof in the row dofs part
  /// of the schema defined by this.
  /// Synonym for contains_dof(xother_id, false).
  ///
  inline bool contains_row_dof(const scoped_index& xother_id) const
  {
    return contains_dof(xother_id.hub_pod(), false);
  };

  ///
  /// True if this is in the table dofs part (xin_table_dofs == true)
  /// or in the row dofs part (xin_table_dofs == false) of some schema.
  ///
  virtual bool is_dof(bool xin_table_dofs) const;

  ///
  /// True if this is in the table_dofs part of some schema.
  /// Synonym for is_dof(true).
  ///
  inline bool is_table_dof() const
  {
    return is_dof(true);
  };

  ///
  /// True if this is in in the row_dofs part of some schema.
  /// Synonym for is_dof(false).
  ///
  inline bool is_row_dof() const
  {
    return is_dof(false);
  };

  ///
  /// True if this represents a component in the
  /// row dofs part of some schema.
  ///
  bool is_component() const;

  ///
  /// True if this represents a component in the
  /// row dofs part of schema xother.
  ///
  bool is_component_of(const schema_poset_member& xother) const;

  ///
  /// True if this represents a factor in the
  /// row dofs part of some schema.
  ///
  bool is_factor() const;

  ///
  /// True if this represents a factor in the
  /// row dofs part of schema xother.
  ///
  bool is_factor_of(const schema_poset_member& xother) const;

  ///
  /// The number of bytes in this dof
  ///
  virtual size_t size() const;

  ///
  /// The alignment for this dof
  ///
  virtual size_t alignment() const;

  ///
  /// The primitive type index of the dof defined by this.
  ///
  virtual primitive_type type() const;

  ///
  /// A postorder iterator over the table (xis_table_dofs == true)
  /// or row (xis_table_dofs == false) dofs defined by version
  /// version of this.
  ///
  virtual poset_dof_iterator* dof_iterator(bool xis_table_dofs,
					   int xversion = CURRENT_MEMBER_VERSION) const;

  ///
  /// A postorder iterator over the table dofs defined by this.
  /// Synonym for dof_iterator(true).
  ///
  inline poset_dof_iterator* table_dof_iterator(int xversion = CURRENT_MEMBER_VERSION) const
  {
    return dof_iterator(true, xversion);
  };

  ///
  /// A postorder iterator over the row dofs defined by this.
  ///
  inline poset_dof_iterator* row_dof_iterator(int xversion = CURRENT_MEMBER_VERSION) const
  {
    return dof_iterator(false, xversion);
  };

  ///
  /// True if the dofs defined by this agree in type and in order
  /// with the dofs defined by xother. (This schema may contain
  /// additional dofs as well.)
  ///
  bool conforms_to(const schema_poset_member& xother) const;

  ///
  /// True if the table dofs (xis_table_dofs true) or
  /// row dofs (xis_is_table_dofs false) defined by this
  /// agree in type and in order with the dofs defined by xother.
  /// (This schema may contain additional dofs as well.)
  ///
  virtual bool conforms_to(const schema_poset_member& xother, bool xis_table_dofs) const;

  ///
  /// True if the dofs defined by this
  /// agree in type and in order with the dofs defined by
  /// the schema member specified by path xpath.
  /// (This schema may contain additional dofs as well.)
  ///
  bool conforms_to(const poset_path& xpath) const;

  ///
  /// True if the table dofs (xis_table_dofs true) or
  /// row dofs (xis_is_table_dofs false) defined by this
  /// agree in type and in order with the dofs defined by
  /// the schema member specified by path xpath.
  /// (This schema may contain additional dofs as well.)
  ///
  bool conforms_to(const poset_path& xpath, bool xis_table_dofs) const;

  ///
  /// True if the table dofs defined by this
  /// agree in type and in order with the dofs defined by xother.
  /// (This schema may contain additional dofs as well.)
  /// Synonym for conforms_to(xother, true).
  ///
  bool table_conforms_to(const schema_poset_member& xother) const;

  ///
  /// True if the table dofs defined by this
  /// agree in type and in order with the dofs defined by
  /// the schema member specified by path xpath.
  /// (This schema may contain additional dofs as well.)
  /// Synonym for conforms_to(xpath, true).
  ///
  bool table_conforms_to(const poset_path& xpath) const;

  ///
  /// True if the row dofs defined by this
  /// agree in type and in order with the dofs defined by xother.
  /// (This schema may contain additional dofs as well.)
  /// Synonym for conforms_to(xother, false).
  ///
  bool row_conforms_to(const schema_poset_member& xother) const;

  ///
  /// True if the row dofs defined by this
  /// agree in type and in order with the dofs defined by
  /// the schema member specified by path xpath.
  /// (This schema may contain additional dofs as well.)
  /// Synonym for conforms_to(xpath, false).
  ///
  bool row_conforms_to(const poset_path& xpath) const;

  ///
  /// True if the dofs defined by the schema specified by xchild_path
  /// agree in type and in order with the dofs defined by
  /// the schema member specified by path xparent_path.
  /// (Child schema may contain additional dofs as well.)
  ///
  static bool conforms_to(const namespace_poset& xns,
                          const poset_path& xchild_path,
                          const poset_path& xparent_path,
                          bool xauto_access = true);

  ///
  /// True if the table dofs (xis_table_dofs true) or
  /// row dofs (xis_table_dofs false) defined by the schema
  /// specified by xchild_path agree in type and in order
  /// with the dofs defined by the schema member specified
  /// by path xparent_path.
  /// (Child schema may contain additional dofs as well.)
  ///
  static bool conforms_to(const namespace_poset& xns,
                          const poset_path& xchild_path,
                          const poset_path& xparent_path,
                          bool xis_table_dofs,
                          bool xauto_access);

  ///
  /// True if the table dofs defined by the schema
  /// specified by xchild_path agree in type and in order
  /// with the dofs defined by the schema member specified
  /// by path xparent_path.
  /// (Child schema may contain additional dofs as well.)
  /// Synonym for conforms_to(xns, xchild_path, xparent_path, true, xauto_access);
  ///
  static bool table_conforms_to(const namespace_poset& xns,
                                const poset_path& xchild_path,
                                const poset_path& xparent_path,
                                bool xauto_access = true);

  ///
  /// True if the row dofs defined by the schema
  /// specified by xchild_path agree in type and in order
  /// with the dofs defined by the schema member specified
  /// by path xparent_path.
  /// (Child schema may contain additional dofs as well.)
  /// Synonym for conforms_to(xns, xchild_path, xparent_path, false, xauto_access);
  ///
  static bool row_conforms_to(const namespace_poset& xns,
                              const poset_path& xchild_path,
                              const poset_path& xparent_path,
                              bool xauto_access = true);


  ///
  /// Creates a schema member with name xname which is join-equivalent
  /// the schema with path xparent_path. Returns a path to the new member.
  ///
  static poset_path make_schema(const namespace_poset& xns,
                                const poset_path& xparent_path,
                                const string& xname);


  ///
  /// @deprecated Use schema_poset_member(namespace, name, parent_path, dof_specs ...).
  ///
  static void make_schema_no_jims(namespace_poset* xns,
                                  const string& xposet_name,
                                  const string& xmember_name,
                                  const string& xparent_name);

  ///
  /// @deprecated Use schema_poset_member(namespace, name, parent_path, dof_specs ...).
  /// Creates a schema member with name xname which conforms_to
  /// the schema with path xparent_path and has additional dofs with
  /// names, types, and roles specified by xdof_names, xdofs_types,
  /// and xis_table_dof, respectively. Returns a path to the new schema member.
  ///
  static poset_path make_schema(const namespace_poset& xns,
                                const poset_path& xparent_path,
                                const string& xname,
                                const string xdof_names[],
                                const primitive_type xdof_types[],
                                const bool xis_table_dof[],
                                size_type xdof_ct,
                                bool xauto_access);

  ///
  /// @deprecated Use schema_poset_member(namespace, name, parent_path, dof_specs ...).
  /// Creates a schema member with name xname which conforms_to
  /// the schema with path xparent_path and has additional row dofs with
  /// names and types specified by xdof_names and xdofs_types, respectively.
  ///
  static poset_path make_row_schema(const namespace_poset& xns,
                                    const poset_path& xparent_path,
                                    const string& xname,
                                    const string xdof_names[],
                                    const primitive_type xdof_types[],
                                    size_type xdof_ct,
                                    bool xauto_access);

  ///
  /// @deprecated Use schema_poset_member(namespace, name, parent_path, dof_specs ...).
  /// Creates a schema member with name xname which conforms_to
  /// the schema with path xparent_path and has additional row dofs with
  /// names specified by xdof_names and type xdofs_type.
  ///
  static poset_path
  make_homogeneous_row_schema(const namespace_poset& xns,
                              const poset_path& xparent_path,
                              const string& xname,
                              const string xdof_names[],
                              const primitive_type xdof_type,
                              size_type xdof_ct,
                              bool xauto_access);

  ///
  /// @deprecated Use schema_poset_member(namespace, name, parent_path, dof_specs ...).
  /// Convenience method for creating schema with row dofs
  /// (Version with inheritance).
  ///
  static void make_row_dofs_schema(namespace_poset*  xns,
                                   const string      member_names[],
                                   const int         num_members,
                                   const int         member_dof_type,
                                   const string&     schema_poset_name,
                                   const string&     schema_member_name,
                                   const string&     schema_inherits_name);

  ///
  /// @deprecated Use schema_poset_member(namespace, name, parent_path, dof_specs ...).
  /// Convenience method for creating schema with row dofs
  /// (Version with inheritance).
  ///
  static void make_table_dofs_schema(namespace_poset*  xns,
                                     const string      member_names[],
                                     const int         num_members,
                                     const int         member_dof_type,
                                     const string&     schema_poset_name,
                                     const string&     schema_member_name,
                                     const string&     schema_inherits_name);

  ///
  /// Forces update of the attribute cache.
  ///
  void force_cache_update();

  ///
  /// The dof_descriptors_array for the table dof tuple
  /// (xis_table_dof true) or row dof tuple defined by this schema.
  /// The offsets in the descriptors are defined by post-ordered,
  /// contiguous, properly aligned allocation of the dofs.
  /// Note: although returned by pointer,
  /// the client must not delete the dof offsets array.
  ///
  ///
  dof_descriptor_array* dof_descriptors(bool xis_table_dof) const;

  ///
  /// The dof_descriptors_array for the table dof tuple
  /// defined by this schema.
  /// Synonym for dof_descriptors(true).
  ///
  ///
  dof_descriptor_array* table_dof_descriptors() const;

  ///
  /// The dof_descriptors_array for the
  /// row dof tuple defined by this schema.
  /// Synonym for dof_descriptors(false).
  ///
  ///
  dof_descriptor_array* row_dof_descriptors() const;

protected:

  ///
  /// Initializes _table_dof_subset_index and _row_dof_subposet_index;
  ///
  virtual void attach_handle_data_members();

  ///
  /// The index within host of the table dofs subposet associated with this
  ///
  scoped_index _table_dof_subposet_index;

  ///
  /// The index within host of the row dofs subposet associated with this
  ///
  scoped_index _row_dof_subposet_index;

  ///
  /// The subposet_state for the table/row dof subposet
  ///
  subposet_state* dof_subposet_state(bool xis_table_dof);

  ///
  /// The index with respect to which the
  /// cached table properties were evaluated.
  ///
  mutable scoped_index _table_cache_index;

  ///
  /// The version with respect to which the
  /// cached table properties were evaluated.
  ///
  mutable int _table_cache_version;

  ///
  /// True if cached table properties are consistent with
  /// index() and version().
  ///
  bool table_cache_consistent() const;

  ///
  /// Updates cached table properties.
  ///
  virtual void update_table_cache() const;

  ///
  /// Initialize table dof id space.
  /// Return true, if and only if the table dof id space was created.
  ///
  virtual bool initialize_table_dof_id_space() const;

  ///
  /// Update the table dof id space.
  ///
  virtual void update_table_dof_id_space() const;

  ///
  /// Update the table dof descriptors.
  ///
  virtual void update_table_dof_descriptors() const;

  ///
  /// The index with respect to which the
  /// cached row properties were evaluated.
  ///
  mutable scoped_index _row_cache_index;

  ///
  /// The version with respect to which the
  /// cached row properties were evaluated.
  ///
  mutable int _row_cache_version;

  ///
  /// True if cached row properties are consistent with
  /// index() and version().
  ///
  bool row_cache_consistent() const;

  ///
  /// Updates cached row properties; 
  /// if xupdate_id_space, force the update of the row dof id space.
  ///
  virtual void update_row_cache(bool xupdate_id_space = false) const;

  ///
  /// Initialize row dof id space.
  /// Return true, if and only if the row dof id space was created.
  ///
  virtual bool initialize_row_dof_id_space() const;

  ///
  /// Update the row dof id space.
  ///
  virtual void update_row_dof_id_space() const;

  ///
  /// Update the row dof descriptors.
  ///
  virtual void update_row_dof_descriptors() const;

  ///
  /// Initializes the dof id space.  If xis_table_dof, otherwise initialize
  /// table dof id space. Otherwise, initialize the row dof id space.
  /// Returns true if and only if the id space was created.
  ///
  bool initialize_dof_id_space(bool xis_table_dof) const;

  ///
  /// Update the ids in the dof id space.  If xis_table_dof, otherwise
  /// initialize table dof id space. Otherwise, initialize the row dof id
  /// space.
  ///
  void update_dof_id_space(bool xis_table_dof) const;

  ///
  /// Update the dof descriptors.    If xis_table_dof, otherwise initialize
  /// table dof id space. Otherwise, initialize the row dof id space.
  ///
  void update_dof_descriptors(bool xis_table_dof,
			      dof_descriptor_array*& xdof_descriptors,
			      size_type xdof_ct,
			      size_type& xdof_tuple_ub) const;

  ///
  /// The number of table dofs defined by this schema.
  ///
  mutable size_type _table_dof_ct;

  ///
  /// The number of row dofs defined by this schema.
  ///
  mutable size_type _row_dof_ct;

  ///
  /// The size in bytes of the table dof tuple defined by this schema.
  ///
  mutable size_type _table_dof_tuple_ub;

  ///
  /// The size in bytes of the row dof tuple defined by this schema.
  ///
  mutable size_type _row_dof_tuple_ub;

  ///
  /// The dof_descriptors_array for the table dof tuple defined by this schema.
  ///
  mutable dof_descriptor_array* _table_dof_descriptors;

  ///
  /// The dof_descriptors_array for the row dof tuple defined by this schema.
  ///
  mutable dof_descriptor_array* _row_dof_descriptors;

private:

  //@}


  // ===========================================================
  /// @name NEW DOF ACCESS FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// The table dof (xis_table_dof true) or row dof id space
  /// for the schema defined by this.
  ///
  const index_space_handle& dof_id_space(bool xis_table_dofs) const;
 
  ///
  /// The table dof (xis_table_dof true) or row dof id space
  /// for the schema defined by this.
  ///
  const index_space_handle& dof_id_space(bool xis_table_dofs, bool xauto_access) const;
  
  ///
  /// The table dof id space for the schema defined by this.
  ///
  const index_space_handle& table_dof_id_space() const;
 
  ///
  /// The table dof id space for the schema defined by this.
  ///
  const index_space_handle& table_dof_id_space(bool xauto_access) const;
  
  ///
  /// The row dof id space for the schema defined by this.
  ///
  const index_space_handle& row_dof_id_space() const;
 
  ///
  /// The row dof id space for the schema defined by this.
  ///
  const index_space_handle& row_dof_id_space(bool xauto_access) const;

  using total_poset_member::name;
  
  ///
  /// The name of the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  string name(pod_index_type xdof_id, bool xis_table_dof) const;
 
  ///
  /// The name of the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  string name(const scoped_index& xdof_id, bool xis_table_dof, bool xauto_access) const;
  
  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type size(pod_index_type xdof_id, bool xis_table_dof) const;
 
  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  size_type size(const scoped_index& xdof_id, bool xis_table_dof, bool xauto_access) const;

  ///
  /// The number of bytes in the table dof (xis_table_dof true) or row
  /// dof with name xname in the schema defined by this.
  ///
  size_type size(const string& xname, bool xis_table_dof, bool xauto_access) const;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type alignment(pod_index_type xdof_id, bool xis_table_dof) const;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  size_type alignment(const scoped_index& xdof_id, bool xis_table_dof, bool xauto_access) const;

  ///
  /// The alignment for the table dof (xis_table_dof true) or row
  /// dof with name xname in the schema defined by this.
  ///
  size_type alignment(const string& xname, bool xis_table_dof, bool xauto_access) const;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual primitive_type type(pod_index_type xdof_id,
			      bool xis_table_dof) const;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  primitive_type type(const scoped_index& xdof_id, bool xis_table_dof,
		      bool xauto_access) const;

  ///
  /// The primitive type for the table dof (xis_table_dof true) or row
  /// dof with name xname in the schema defined by this.
  ///
  primitive_type type(const string& xname, bool xis_table_dof, bool xauto_access) const;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  virtual size_type offset(pod_index_type xdof_id, bool xis_table_dof) const;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof referred to by xdof_id in the schema defined by this.
  ///
  size_type offset(const scoped_index& xdof_id, bool xis_table_dof,
		   bool xauto_access) const;

  ///
  /// The offset for the table dof (xis_table_dof true) or row
  /// dof with name xname in the schema defined by this.
  ///
  size_type offset(const string& xname, bool xis_table_dof, bool xauto_access) const;

protected:
  
  ///
  /// The table dof id space for the schema defined by this.
  ///
  mutable index_space_handle* _table_dof_id_space;

  ///
  /// The row dof id space for the schema defined by this.
  ///
  mutable index_space_handle* _row_dof_id_space;

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
  /// An iterator over the members of the decomposition identified by xindex.
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  ///
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
  /// Gets the internal id corresponding to xext_id in the id space
  /// with name xid_space_name.
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  ///
  virtual pod_index_type get_int_id(pod_index_type xext_id,
				    const string& xid_space_name) const;

  ///
  /// Gets an external id corresponding to index() in the id space
  /// with name xid_space_name.
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  ///
  virtual pod_index_type get_ext_id(const string& xid_space_name) const;

  ///
  /// Gets the external ids of this in
  /// the id space with name xid_space_name
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.
  ///
  virtual void get_ext_ids(const string& xid_space_name,
                           pod_index_type& xschema_poset_ext_id,
                           pod_index_type& xschema_member_ext_id,
                           pod_index_type& xbase_space_ext_id,
                           pod_index_type& xfiber_schema_ext_id,
                           pod_index_type& xlocal_schema_ext_id) const;

  ///
  /// The schema for the external data type associated with this schema.
  ///
  virtual schema_poset_member& ext_data_type_schema();

  ///
  /// The number of instances of the external data type needed to
  /// represent this schema.
  ///
  virtual size_t ext_data_type_ct(bool xis_table_schema) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name DEGREE OF FREEDOM (DOF) TUPLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The map from schema member ids or client ids to
  /// dof values for this poset member (mutable version)
  ///
  virtual primitives_poset_dof_map& dof_map(bool xrequire_write_access = false);

  ///
  /// The map from schema member ids or client ids to
  /// dof values for this poset member (const version)
  ///
  virtual const primitives_poset_dof_map& dof_map(bool xrequire_write_access = false) const;

  ///
  /// True if xdof_map conforms to (is derived from) the type of
  /// dof map required by this handle.
  ///
  virtual bool dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ORDERING RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The largest member which is join-equivalent to this
  ///
  inline schema_poset_member* greatest_jem() const
  {
    return static_cast<schema_poset_member*>(abstract_poset_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline schema_poset_member* least_jem() const
  {
    return static_cast<schema_poset_member*>(abstract_poset_member::least_jem());
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// poset join of this with other, auto-, pre-, and self-allocated versions
  /// the poset join is the least upper bound in the poset
  ///
  inline schema_poset_member* p_join(abstract_poset_member* other) const
  {
    return static_cast<schema_poset_member*>(abstract_poset_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline schema_poset_member* p_meet(abstract_poset_member* other)
  {
    return static_cast<schema_poset_member*>(abstract_poset_member::p_meet(other));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name LATTICE ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// lattice join of this with other, auto-, pre-, and self-allocated versions
  /// the lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset
  ///
  inline schema_poset_member* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<schema_poset_member*>(abstract_poset_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline schema_poset_member* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<schema_poset_member*>(abstract_poset_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline schema_poset_member* l_not(bool xnew_jem = true) const
  {
    return static_cast<schema_poset_member*>(abstract_poset_member::l_not(xnew_jem));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Detach this handle from its state, if any.
  ///
  virtual void detach_from_state();

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
  /// Make a new handle, no state instance of current
  ///
  virtual schema_poset_member* clone() const;

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
/// The deep size of the referenced object of type schema_poset_member.
///
SHEAF_DLL_SPEC
size_t deep_size(const schema_poset_member& xp, bool xinclude_shallow = true);

} // namespace sheaf

#endif // SCHEMA_POSET_MEMBER_H

