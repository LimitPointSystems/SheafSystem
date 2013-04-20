
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

#ifndef ARRAY_SEC_VD_DOF_MAP_H
#define ARRAY_SEC_VD_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ARRAY_SECTION_DOF_MAP_H
#include "array_section_dof_map.h"
#endif

namespace fiber_bundle
{

class sec_rep_space;

///
/// A contiguous tuple, contiguous fiber representation
/// of the abstract map from section dof ids
/// to section dof values of type sec_vd_dof_type.
///
class SHEAF_DLL_SPEC array_sec_vd_dof_map : public array_section_dof_map
{

public:

  ///
  /// The name of the actual (possibly derived) class of this instance.
  ///
  virtual const string& class_name();

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  // ===========================================================
  // CANONICAL FACET
  // ===========================================================

  ///
  /// Default constructor
  ///
  array_sec_vd_dof_map();

  ///
  /// Virtual default constructor.
  ///
  virtual array_sec_vd_dof_map* clone() const;

  ///
  /// Copy constructor
  ///
  array_sec_vd_dof_map(const array_sec_vd_dof_map& xother);

  ///
  /// Virtual copy constructor.
  ///
  virtual array_sec_vd_dof_map* copy() const;

  ///
  /// Assignment operator
  ///
  array_sec_vd_dof_map& operator=(const array_sec_vd_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~array_sec_vd_dof_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // ===========================================================
  // MAP FACET
  // ===========================================================

  ///
  /// Creates a dof map for a member of sec_rep_space xhost.
  /// If xdofs is non zero, it will be used for dof storage,
  /// otherwise storage will be allocated
  ///
  array_sec_vd_dof_map(sec_rep_space* xhost, void* xdofs = 0, size_t xdofs_ub = 0);

  ///
  /// Creates a dof map for a (possibly partial) section of sec_rep_space xhost
  /// on version xversion of the base space member identified by xbase_id.
  /// If xdofs is non zero, it will be used for dof storage,
  /// otherwise storage will be allocated
  ///
  array_sec_vd_dof_map(sec_rep_space* xhost,
                        const scoped_index& xbase_id,
                        int xversion,
                        void* xdofs = 0,
                        size_t xdofs_ub = 0);

  ///
  /// An identifer for the type of dof tuple this is.
  ///
  virtual dof_tuple_type type_id()
  {
    return ARRAY_SECTION_DOF_TUPLE_ID;
  };

  using section_dof_map::get_dof;
  using section_dof_map::put_dof;

  // ===========================================================
  /// @name NEW DOF ACCESS FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Copies the dof referred to by xdof_id into xdof.
  ///
  virtual void get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const;

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  virtual void put_dof(pod_index_type xdof_id,  bool xis_poset_id, const void* xdof, size_type xdof_size);

  /// @hack new_ prefix added to temporarily prevent
  /// ambiguity with old signature get_dof(const scoped_index&, bool, void*, size_t);
  /// remove when old signature removed.
 
  ///
  /// Copies the dof referred to by xdisc_id, xfiber_dof_id into xdof.
  ///
  virtual void get_dof(pod_index_type xdisc_id, 
		       pod_index_type xfiber_dof_id, 
		       void* xdof, 
		       size_type xdof_size) const;

  ///
  /// Sets the dof referred to by xdof_id to the value at xdof.
  ///
  virtual void put_dof(pod_index_type xdisc_id, 
		       pod_index_type xfiber_dof_id, 
		       const void* xdof, 
		       size_type xdof_size);
 
protected:

private:

  ///
  /// Pointer to dof referred to by xdof_id.
  //
  sec_vd_dof_type* dof_ptr(pod_index_type xdof_id) const
  {
    return reinterpret_cast<sec_vd_dof_type*>(_dofs) + xdof_id;
  }

  //@}
 

protected:

private:

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

} // namespace fiber_bundle

#endif // ifndef ARRAY_SEC_VD_DOF_MAP_H
