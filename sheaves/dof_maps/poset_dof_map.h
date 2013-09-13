
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

// Interface for class poset_dof_map;
// map from client dof id to dof value

#ifndef POSET_DOF_MAP_H
#define POSET_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef DOF_TUPLE_TYPE_H
#include "dof_tuple_type.h"
#endif

#ifndef PRIMITIVE_VALUE_H
#include "primitive_value.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif 

namespace sheaf
{

class poset_state_handle;
class schema_poset_member;
class arg_list;
class dof_map_factory;

///
/// The general, abstract map from dof ids to dof values.
///
class SHEAF_DLL_SPEC poset_dof_map : public any
{

  friend class poset_table_state;
  friend class poset_state_handle;
  friend SHEAF_DLL_SPEC size_t deep_size(const poset_dof_map& xp, bool xinclude_shallow);

public:

  ///
  /// The name of the actual (possibly derived) class of this instance.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  ///
  /// Creates an uninitialized dof map of type xclass_name, if a prototype
  /// of that name exists, otherwise of type xsheaf_base_class_id.
  ///
  static poset_dof_map*
  new_dof_map(const string& xclass_name, dof_tuple_type xsheaf_base_class_id);

  // CANONICAL MEMBERS

  ///
  /// Virtual default constructor.
  ///
  virtual poset_dof_map* clone() const = 0;

  ///
  /// Virtual copy constructor.
  ///
  virtual poset_dof_map* copy() const = 0;

  ///
  /// Assignment operator
  ///
  poset_dof_map& operator=(const poset_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~poset_dof_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;


  // MAP INTERFACE

  ///
  /// Initializes this as a map for row dofs in host xhost,
  /// with schema member specified by xschema_mbr_id
  /// and schema version xschema_version.
  ///
  virtual void init_row_dof_map(const poset_state_handle* xhost,
                                pod_index_type xschema_mbr_id,
                                int xschema_version);

  ///
  /// Initializes this as a map for row dofs in host xhost,
  /// with schema member specified by xschema_mbr_id
  /// and schema version xschema_version.
  ///
  void init_row_dof_map(const poset_state_handle* xhost,
			const scoped_index& xschema_mbr_id,
			int xschema_version);

  ///
  /// An identifer for the type of dof tuple this is.
  ///
  virtual dof_tuple_type type_id() const = 0;

  ///
  /// True if this has been initialized, that is,
  /// if the schema has been set and the dof map storage allocated.
  ///
  bool is_initialized() const;

  ///
  /// The poset which owns this.
  ///
  virtual poset_state_handle* host() const;

  ///
  /// The index of this in host() dof tuple table.
  ///
  const scoped_index& index() const;

  // $$SCRIBBLE: there's no need for schema() to be virtual.
  // It's only overridden in one place, section_dof_map, and
  // the over ride only does a down cast on the return type.
  // Should be non-virtual and inline and section_dof_map
  // should just hide poset_dof_map; more efficient.

  ///
  /// The schema on which this is allocated (mutable version).
  ///
  virtual schema_poset_member& schema();

  ///
  /// The schema on which this is allocated (const version).
  ///
  virtual const schema_poset_member& schema() const;

  ///
  /// True if this is a table dof map.
  ///
  bool is_table_dof_map() const;

  ///
  /// The number of dofs in this map.
  ///
  int dof_ct() const;

  // ===========================================================
  //  NEW DOF ACCESS FACET
  // ===========================================================
 
  ///
  /// The dof referred to by xdof_id.
  ///
  primitive_value dof(pod_index_type xdof_id) const;

  ///
  /// The dof referred to by xdof_id.
  ///
  primitive_value dof(const scoped_index& xdof_id) const;

  ///
  /// The dof with name xname.
  ///
  primitive_value dof(const string& xname) const;

  ///
  /// Sets the dof referred to by xdof_id to xdof.
  ///
  void put_dof(pod_index_type xdof_id, const primitive_value& xdof);

  ///
  /// Sets the dof referred to by xdof_id to xdof.
  ///
  void put_dof(const scoped_index& xdof_id, const primitive_value& xdof);

  ///
  /// Sets the dof with name xname to xdof.
  ///
  void put_dof(const string& xname, const primitive_value& xdof);

  ///
  /// Copies the dof referred to by xdof_id into xdof.
  ///
  virtual void get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const;

  ///
  /// Copies the dof referred to by xdof_id into xdof.
  ///
  void get_dof(const scoped_index& xdof_id, void* xdof, size_type xdof_size) const;

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  virtual void put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size);

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  void put_dof(const scoped_index& xdof_id, const void* xdof, size_type xdof_size);
  
  
  // ===========================================================
  //  END NEW DOF ACCESS FACET
  // ===========================================================

  ///
  /// The size of the dof tuple in bytes.
  ///
  size_t dof_tuple_ub() const;

  ///
  /// The dof tuple (mutable version).
  ///
  virtual void* dof_tuple() = 0;

  ///
  /// The dof tuple (const version).
  ///
  virtual const void* dof_tuple() const = 0;

  /// @hack This routine is inconsistent with the rest of the interface,
  /// which attempts to hide the dof storage. Consistency awaits the
  /// planned redesign of the dof map cluster.

  ///
  /// Copies the entire dof tuple from internal storage into xbuf.
  ///
  virtual void get_dof_tuple(void* xbuf, size_t xbuflen) const = 0;

  ///
  /// Copies the entire dof tuple from xbuf into internal storage
  ///
  virtual void put_dof_tuple(const void* xbuf, size_t xbuflen) = 0;

  ///
  /// Copies the entire dof tuple from internal storage into xargs
  ///
  void get_dof_tuple(arg_list& xargs) const;

  ///
  /// Copies the entire dof tuple from xargs into internal storage
  ///
  void put_dof_tuple(const arg_list& xargs);

  ///
  /// Copies the dof tuple of xother into this.
  ///
  void copy_dof_tuple(const poset_dof_map& xother);

  ///
  /// Sets all dofs to defualt values
  ///
  virtual void put_defaults();

  ///
  /// The number of references to this map.
  ///
  unsigned int ref_ct() const;

  ///
  /// Increase the number of references to this map by one;
  ///
  void inc_ref_ct();

  ///
  /// Decrease the number of references to this map by one.
  ///
  void dec_ref_ct();

  ///
  /// The version of the host of the schema this is defined on.
  ///
  int version() const;

  ///
  /// The map from library ids to clients ids for
  /// the schema this is defined on.
  ///
  virtual const index_space_handle& client_id_space() const;

  ///
  /// Return schema member dof value as a string
  ///
  string to_string(const schema_poset_member& xschema) const;

  ///
  /// Return dof values as a formated string
  ///
  string to_string() const;

  // ===========================================================
  // I/O SUPPORT FACET
  // ===========================================================

  ///
  /// True if this dof map type supports dof tuple transfer optimization.
  //// @hack dof tuple transfer hack.
  ////
  virtual bool supports_xfr_opt() const;

protected:

  ///
  /// The dof map factory.
  ///
  static dof_map_factory& factory();

  // CANONICAL MEMBERS

  ///
  /// Default constructor;
  ///
  poset_dof_map();

  ///
  /// Copy constructor
  ///
  poset_dof_map(const poset_dof_map& xother);

  // OTHER CONSTRUCTORS

  ///
  /// Creates a map for the table dofs (xis_table_dofs true) or
  /// row dofs (xis_table dofs false) for use in host xhost.
  ///
  poset_dof_map(const poset_state_handle* xhost, bool xis_table_dof_map);

  ///
  /// Creates a map for the table dofs (xis_table_dofs true) or
  /// row dofs (xis_table dofs false) for use in host xhost.
  ///
  poset_dof_map(const schema_poset_member* xschema, bool xis_table_dof_map);

  // MAP INTERFACE

  ///
  /// Sets host() to xhost.
  ///
  virtual void put_host(const poset_state_handle* xhost);

  ///
  /// Sets the index of the member for which this provides the dofs
  ///
  void put_index(const scoped_index& xindex);

  ///
  /// Sets dof_ct() to xdof_ct.
  ///
  void put_dof_ct(int xdof_ct);

  ///
  /// Sets dof_tuple_ub() to xub.
  ///
  void put_dof_tuple_ub(size_t xub);

  ///
  /// Sets ref_ct() to xref_ct).
  ///
  void put_ref_ct(int xref_ct);

  ///
  /// The host of the poset member for which this stores the dofs.
  ///
  poset_state_handle* _host;

  ///
  /// The poset member for which this stores the dofs
  ///
  scoped_index _index;

  ///
  /// The schema on which this is instantiated.
  ///
  schema_poset_member* _schema;

  ///
  /// True if this is a table dof map.
  ///
  bool _is_table_dof_map;

  ///
  /// The number of dofs in this map.
  ///
  int _dof_ct;

  ///
  /// The size of the dof tuple
  ///
  size_t _dof_tuple_ub;

  ///
  /// The number of references to this map
  //// @hack need to fully implement reference counting of maps
  ////
  unsigned int _ref_ct;

  ///
  /// Allocates dof storage.
  ///
  virtual void allocate_dofs() = 0;

};

// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

///
/// Insert poset_dof_map& p into ostream& os.
///
SHEAF_DLL_SPEC
ostream& operator << (ostream &os, const poset_dof_map& p);

///
/// The deep size of the referenced object of type poset_dof_map.
///
SHEAF_DLL_SPEC
size_t deep_size(const poset_dof_map& xp, bool xinclude_shallow = true);

} // namespace sheaf

#endif // ifndef POSET_DOF_MAP_H

