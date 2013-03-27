// $RCSfile: array_poset_dof_map.h,v $ $Revision: 1.33 $ $Date: 2013/01/12 17:17:34 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class array_poset_dof_map;
// map from client dof id to dof value

#ifndef ARRAY_POSET_DOF_MAP_H
#define ARRAY_POSET_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_DOF_MAP_H
#include "poset_dof_map.h"
#endif

namespace sheaf
{
  
class dof_descriptor_array;
class dof_map_factory;
class poset_dof_iterator;
class schema_poset_member;

///
/// An array representation of abstract class poset_dof_map.
///
class SHEAF_DLL_SPEC array_poset_dof_map : public poset_dof_map
{

public:

  ///
  /// The name of the actual (possibly derived) class of this instance.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  // CANONICAL MEMBERS

  ///
  /// Default constructor;
  /// protected because doesn't initialize schema.
  ///
  array_poset_dof_map();

  ///
  /// Virtual default constructor.
  ///
  virtual array_poset_dof_map* clone() const;

  ///
  /// Copy constructor
  ///
  array_poset_dof_map(const array_poset_dof_map& xother);

  ///
  /// Virtual copy constructor.
  ///
  virtual array_poset_dof_map* copy() const;

  ///
  /// Assignment operator
  ///
  array_poset_dof_map& operator=(const array_poset_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~array_poset_dof_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// If xis_table_dof_map,
  /// creates a table dof map (xis_table_dof true) or a row dof map
  /// (xis_table_dof false) for xhost. If xdofs is non zero, it will be
  /// used for dof storage, otherwise storage will be allocated
  ///
  array_poset_dof_map(const poset_state_handle* xhost,
                      bool xis_table_dof_map,
                      void* xdofs = 0,
                      size_t xdofs_ub = 0);

  ///
  /// Creates a table dof map (xis_table_dof true) or a row dof map
  /// (xis_table_dof false) on schema xschema. Intended mostly for use
  /// by i/o subsystem.
  ///
  ///
  array_poset_dof_map(const schema_poset_member* xschema, bool xis_table_dof_map);

  // ===========================================================
  // MAP FACET
  // ===========================================================

  ///
  /// An identifer for the type of dof tuple this is.
  ///
  virtual dof_tuple_type type_id() const;

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

  using poset_dof_map::get_dof_tuple;

  ///
  /// Copies the entire dof tuple from internal storage into xbuf.
  ///
  virtual void get_dof_tuple(void* xbuf, size_t xbuflen) const;

  using poset_dof_map::put_dof_tuple;

  ///
  /// Copies the entire dof tuple from xbuf into internal storage
  ///
  virtual void put_dof_tuple(const void* xbuf, size_t xbuflen);

  ///
  /// Pointer to the first byte of the dof associated with xschema_mbr
  ///
  char* dof_ptr(const schema_poset_member& xschema_mbr);

  ///
  /// Pointer to the first byte of the dof associated with xclient_id
  ///
  char* dof_ptr(int xclient_id);

  ///
  /// OBSOLETE; use dof_tuple() instead (mutable version).
  ///
  inline char* dofs()
  {
    return static_cast<char*>(dof_tuple());
  }

  ///
  /// OBSOLETE; use dof_tuple() instead (const version).
  ///
  inline const char* dofs() const
  {
    return static_cast<const char*>(dof_tuple());
  }


protected:

  ///
  /// Allocates dof array
  ///
  void init_dofs(void* xdofs);

  ///
  /// Allocates dof storage.
  ///
  virtual void allocate_dofs();

  ///
  /// True if and only if the dof asociated with id xdof_id
  /// is within the bounds of the dofs storage.
  ///
  bool dof_in_bounds(pod_index_type xdof_id) const;

private:

  ///
  /// Offset in _dofs of the beginning of each dof
  ///
  dof_descriptor_array* _dof_descriptors;

  ///
  /// Storage for the dofs
  ///
  char* _dofs;

  ///
  /// True if this allocated _dofs and hence should delete it
  ///
  bool _this_owns_dofs;

  ///
  /// True if prototype for this class has been entered in factory.
  /// Intended to force creation of prototype at initialization.
  ///
  static bool _has_prototype;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef ARRAY_POSET_DOF_MAP_H
