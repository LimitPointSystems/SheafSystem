
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

// Interface for class primitives_poset_dof_map;
// map from client dof id to dof value

#ifndef PRIMITIVES_POSET_DOF_MAP_H
#define PRIMITIVES_POSET_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_DOF_MAP_H
#include "poset_dof_map.h"
#endif

#ifndef PRIMITIVE_TYPE_H
#include "primitive_type.h"
#endif

namespace sheaf
{

class dof_map_factory;
class primitives_poset;
  
///
/// A map from schema poset member ids to dof values for primitives_poset members.
///
class SHEAF_DLL_SPEC primitives_poset_dof_map : public poset_dof_map
{

  friend class namespace_poset;

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
  /// Default constructor;
  ///
  primitives_poset_dof_map();

  ///
  /// Virtual default constructor.
  ///
  virtual primitives_poset_dof_map* clone() const;

  ///
  /// Copy constructor
  ///
  primitives_poset_dof_map(const primitives_poset_dof_map& xother);

  ///
  /// Virtual copy constructor.
  ///
  virtual primitives_poset_dof_map* copy() const;

  ///
  /// Assignment operator
  ///
  primitives_poset_dof_map& operator=(const primitives_poset_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~primitives_poset_dof_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates a dof map for the primitive with index xprimitive_index
  ///
  primitives_poset_dof_map(const poset_state_handle* xhost, int xprimitive_index);

  ///
  /// Initializes this as a map for row dofs in host xhost,
  /// with schema member specified by xschema_mbr_id
  /// and schema version xschema_version.
  ///
  virtual void init_row_dof_map(const poset_state_handle* xhost,
                                pod_index_type xschema_mbr_id,
                                int xschema_version);

  // MAP INTERFACE

  ///
  /// An identifer for the type of dof tuple this is.
  ///
  virtual dof_tuple_type type_id() const
  {
    return  PRIMITIVES_POSET_DOF_TUPLE_ID;
  };

  using poset_dof_map::get_dof;
  using poset_dof_map::put_dof;

  // ===========================================================
  //  NEW DOF ACCESS FACET
  // ===========================================================

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
  /// Copies the entire dof tuple from internal storage into xbuf.
  ///
  virtual void get_dof_tuple(void* xbuf, size_t xbuflen) const;

  ///
  /// Copies the entire dof tuple from xbuf into internal storage
  ///
  virtual void put_dof_tuple(const void* xbuf, size_t xbuflen);

  ///
  /// Get size dof
  ///
  size_t size() const;

  ///
  /// Put size dof
  ///
  void put_size(size_t xsize);

  ///
  /// Get alignment dof
  ///
  size_t alignment() const;

  ///
  /// Put alignment dof
  ///
  void put_alignment(size_t xalignment);

  ///
  /// Get type dof.
  /// Note: have to use "type" in name in order to avoid name conflict
  /// with index() inherited from poset_dof_map
  ///
  primitive_type type() const;

  ///
  /// Put type dof.
  /// Note: have to use "type" in name in order to avoid name conflict
  /// with index() inherited from poset_dof_map
  ///
  void put_type(int xindex);

protected:

  ///
  /// Sets host() to xhost.
  ///
  virtual void put_host(const poset_state_handle* xhost);

  ///
  /// Allocates dof storage.
  ///
  virtual void allocate_dofs() {};


private:

  ///
  /// Storage for the dofs
  ///
  primitive_descriptor _dofs;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

} // namespace sheaf

#endif // ifndef PRIMITIVES_POSET_DOF_MAP_H

