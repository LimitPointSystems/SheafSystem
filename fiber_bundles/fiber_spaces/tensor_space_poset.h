
// $RCSfile: tensor_space_poset.h,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:03 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class tensor_space_poset.

#ifndef TENSOR_SPACE_POSET_H
#define TENSOR_SPACE_POSET_H

#ifndef POSET_H
#include "poset.h"
#endif

namespace sheaf
{
class namespace_poset;
}

namespace fiber_bundle
{

using namespace sheaf;  
  
///
/// A specialization of poset for tensor spaces.
///
class tensor_space_poset : public poset
{

public:

  //============================================================================
  // TENSOR_SPACE_POSET FACET
  //============================================================================
 
  ///
  /// Default constructor;
  /// creates a new tensor_space_poset handle not attached to any state.
  ///
  tensor_space_poset();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  tensor_space_poset(const tensor_space_poset& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother.
  ///
  tensor_space_poset& operator=(const tensor_space_poset& xother);

  ///
  /// Destructor.
  ///
  virtual ~tensor_space_poset();

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================


  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  tensor_space_poset(namespace_poset* xhost,
                     const poset_path& xschema_path,
                     const string& xname,
                     arg_list& xargs,
                     bool xauto_access = true);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the tensor_space_poset with
  /// index xindex in namespace xhost.
  ///
  tensor_space_poset(const namespace_poset* xhost, scoped_index xindex);

  ///
  /// Creates a new handle attached to the tensor_space_poset with
  /// name xname in namespace xhost.
  ///
  tensor_space_poset(const namespace_poset* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the tensor_space_poset associated
  /// with namespace member xmbr.
  ///
  tensor_space_poset(const abstract_poset_member* xmbr);

  //============================================================================
  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"
  //============================================================================

  using poset::new_state;
  
  ///
  /// Attaches this to a new poset state with schema xschema,
  /// name xname and table dofs xdof_tuple
  ///
  ///
  virtual void new_state(namespace_poset* xhost,
			 const abstract_poset_member* xschema,
			 const string& xname,
			 array_poset_dof_map* xdof_tuple,
			 bool xauto_access = true);

  ///
  /// Attaches this external poset to a new poset state with schema
  /// given by xschema and table dofs by xdof_map.
  /// Intended for use by i/o subsystem.
  ///
  virtual void new_state(const schema_poset_member& xschema,
                         array_poset_dof_map& xdof_map);

 //============================================================================


  ///
  /// Index of the underlying vector space.
  ///
  virtual pod_index_type vector_space_index() const;

  ///
  /// Index of the underlying vector space (auto-access version).
  ///
  virtual pod_index_type vector_space_index(bool xauto_access) const;

  ///
  /// The tensor space poset with index == vector_space_index().
  ///
  virtual tensor_space_poset& vector_space() const;

  ///
  /// The tensor space poset with index == vector_space_index()
  /// (auto-access version).
  ///
  virtual tensor_space_poset& vector_space(bool xauto_access) const;

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
  /// Detach this handle from its state
  ///
  virtual void detach_from_state();

protected:

  ///
  /// The tensor space poset with index == vector_space_index().
  ///
  tensor_space_poset* _vector_space;

  ///
  /// Creates the subposets common to every poset (i.e._whole and _jims).
  ///
  virtual void initialize_standard_subposets(const string& xname);

  using poset::attach_handle_data_members;
  
  ///
  /// Initializes the handle data members when this handle
  /// is attached to a state.
  ///
  virtual void attach_handle_data_members();

  ///
  /// Initializes the handle data members from within new_state.
  ///
  virtual void attach_handle_data_members(namespace_poset* xns, array_poset_dof_map* xtable_dof_tuple);

  ///
  /// Release all access to posets this depends on,
  /// then detach and delete the state.
  ///
  virtual void terminate_access();

private:

  //============================================================================
  // POSET FACET
  //============================================================================

public:
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

  //============================================================================
  // POSET_STATE_HANDLE FACET
  //============================================================================

public:

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual scoped_index prereq_id(int xi) const;

  //============================================================================
  // ANY FACET
  //============================================================================

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual tensor_space_poset* clone() const;

  ///
  /// True if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

};


} // namespace fiber_bundle


#endif // TENSOR_SPACE_POSET_H
