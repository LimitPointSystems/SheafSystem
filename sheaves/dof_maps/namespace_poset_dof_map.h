
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

// Interface for class namespace_poset_dof_map;
// map from client dof id to dof value

#ifndef NAMESPACE_POSET_DOF_MAP_H
#define NAMESPACE_POSET_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef POSET_DOF_MAP_H
#include "poset_dof_map.h"
#endif

#ifndef POSET_TYPE_H
#include "poset_type.h"
#endif

namespace sheaf 
{

class dof_map_factory;
class namespace_poset;
  
///
/// A map from schema poset member ids to dof values for namespace_poset members.
///
class SHEAF_DLL_SPEC namespace_poset_dof_map : public poset_dof_map
{

  friend class poset_state_handle;
  friend class namespace_poset;
  friend class namespace_poset_member;

public:

  ///
  /// The name of the actual (possibly derived) class of this instance.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();

  // CANONICAL MEMBERS

  ///
  /// Default constructor.
  ///
  namespace_poset_dof_map();

  ///
  /// Virtual default constructor.
  ///
  virtual namespace_poset_dof_map* clone() const;

  ///
  /// Copy constructor
  ///
  namespace_poset_dof_map(const namespace_poset_dof_map& xother);

  ///
  /// Virtual copy constructor.
  ///
  virtual namespace_poset_dof_map* copy() const;

  ///
  /// Assignment operator
  ///
  namespace_poset_dof_map& operator=(const namespace_poset_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~namespace_poset_dof_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates a row dof map for xhost.
  /// Must be attached to a member (row) using put_index() before use.
  ///
  namespace_poset_dof_map(const namespace_poset* xhost);

  // MAP INTERFACE

  ///
  /// An identifer for the type of dof tuple this is.
  ///
  virtual dof_tuple_type type_id() const
  {
    return  NAMESPACE_POSET_DOF_TUPLE_ID;
  };

  // ===========================================================
  //  NEW DOF ACCESS FACET
  // ===========================================================

  using poset_dof_map::get_dof;
  using poset_dof_map::put_dof;

  ///
  /// Copies the dof referred to by xdof_id into xdof.
  ///
  virtual void get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const;

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  virtual void put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size);
  
  
  // ===========================================================
  //  END NEW DOF ACCESS FACET
  // ===========================================================

  ///
  /// The dof tuple (mutable version).
  ///
  virtual void* dof_tuple();

  ///
  /// The dof tuple (const version).
  ///
  virtual const void* dof_tuple() const;

  ///
  /// Copies the entire dof tuple from xbuf into internal storage
  ///
  virtual void get_dof_tuple(void* xbuf, size_t xbuflen) const;

  ///
  /// Copies the entire dof tuple from xbuf into internal storage
  ///
  virtual void put_dof_tuple(const void* xbuf, size_t xbuflen);

  ///
  /// The pointer to the poset associated
  /// with this namespace member.
  ///
  poset_state_handle* poset_pointer() const;

  ///
  /// The type id of the poset associated
  /// with this namespace member.
  ///
  poset_type poset_type_id() const;

  ///
  /// The class of the poset associated
  /// with this namespace member.
  ///
  const char* poset_class() const;

  ///
  /// The id of the xi-th prerequisite poset
  /// for the poset associated with this namespace member.
  ///
  int poset_prereq_id(int xi) const;

  // ===========================================================
  // I/O SUPPORT FACET
  // ===========================================================

  ///
  /// Extends the schema from member io to member top.
  //// @hack this function exists only to patch up
  //// a problem in member_record::new_row_dof_tuple.
  ////
  void extend_to_top();


protected:

  ///
  /// Set the pointer to the poset associated
  /// with this namespace member to xposet.
  ///
  void put_poset_pointer(const poset_state_handle* xposet);

  ///
  /// Set  the type id of the poset associated
  /// with this namespace member to xtype_id.
  ///
  void put_poset_type_id(poset_type xtype_id);

  ///
  /// Set  the class of the poset associated
  /// with this namespace member to xclass.
  ///
  void put_poset_class(const char* xclass);

  ///
  /// Set the id of the xi-th prerequisite poset
  /// for the poset associated with this namespace member.
  ///
  void put_poset_prereq_id(int xi, int xid);

  ///
  /// Allocates dof storage.
  ///
  virtual void allocate_dofs();

private:

  ///
  /// The dof storage
  ///
  struct SHEAF_DLL_SPEC dof_struct
  {
    poset_state_handle* pointer;
    int type_id;
    const char* class_name;
    int prereq_ids[5];
  }
  _dofs;

  ///
  /// Map from schema dof id space to the storage id space.
  /// The specificiation calls for dofs to be accessed by the
  /// schema dof id space but storage is on the top id space.
  ///
  block<pod_index_type> _storage_map;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

};

} // namespace sheaf

#endif // ifndef NAMESPACE_POSET_DOF_MAP_H

