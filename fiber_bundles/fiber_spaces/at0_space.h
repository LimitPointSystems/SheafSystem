// $RCSfile: at0_space.h,v $ $Revision: 1.10 $ $Date: 2013/03/13 00:58:42 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class at0_space.

#ifndef AT0_SPACE_H
#define AT0_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ATP_SPACE_H
#include "atp_space.h"
#endif
  
namespace fiber_bundle
{

  using namespace sheaf;  

  class at0;
  
  
///
/// A space of scalars viewed as an antisymmetric tensor space of degree 0.
///
class SHEAF_DLL_SPEC at0_space : public atp_space
{
  friend class fiber_bundles_namespace;

public:

  // ===========================================================
  /// @name AT0_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef at0 member_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list();
  
protected:

  ///
  /// Default constructor;
  /// creates a new at0_space handle not attached to any state.
  ///
  at0_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  at0_space(const at0_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~at0_space();

  ///
  /// Covariant constructor
  ///
  at0_space(at0* xtop, at0* xbottom);

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  at0_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the at0_space with
  /// index xindex in namespace xhost.
  ///
  at0_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the at0_space with
  /// index xindex in namespace xhost.
  ///
  at0_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the at0_space with
  /// name xname in namespace xhost.
  ///
  at0_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the at0_space associated
  /// with namespace member xmbr.
  ///
  at0_space(const namespace_poset_member& xmbr, bool xauto_access);

private:

  //@}

  // ===========================================================
  /// @name TP_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// The number of covariant subposets.
  ///
  virtual size_type covariant_subposet_ct() const;

private:

  //@}

  // ===========================================================
  /// @name VD_SPACE FACET
  // ===========================================================
  //@{

public:

  using vd_space::is_vector;

  ///
  /// True if and only if the member with id xmbr_id is a vector (as opposed to a covector).
  ///
  virtual bool is_vector(pod_index_type xmbr_id, bool xauto_access) const;

  using vd_space::put_is_vector;

  ///
  /// Sets is_vector true for the member with id xmbr_id.
  ///
  virtual void put_is_vector(pod_index_type xmbr_id, bool xauto_access);

  using vd_space::is_covector;

  ///
  /// True if and only if the member with id xmbr_id is a covector.
  ///
  virtual bool is_covector(pod_index_type xmbr_id, bool xauto_access) const;;

  using vd_space::put_is_covector;

  ///
  /// Sets is_covector true for the member with id xmbr_id.
  ///
  virtual void put_is_covector(pod_index_type xmbr_id, bool xauto_access);

protected:

private:

  //@}
  

  // ===========================================================
  /// @name POSET FACET
  // ===========================================================
  //@{

public:
protected:

  ///
  /// Initializes xarg to satisfy class invariants.
  ///
  virtual void initialize_arg_list(const namespace_poset& xns,
				   const string& xname,
				   arg_list& xargs,
				   const poset_path& xschema_path,
				   bool xauto_access);

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

  //@}
 
  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
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
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;

  ///
  /// Assignment operator; attaches this to the same state as xother.
  /// @issue This is probably the wrong signature for operator=,
  /// see thread Misc/Language/covariance in C++/covariance and operator=
  /// in the discusion forum. But it is consistent with all the
  /// other derivatives of poset_state_handle and it will soon be refactored
  /// out of existence any way.
  ///
  at0_space& operator=(const poset_state_handle& xother);

protected:

private:

  //@}

  // ===========================================================
  /// @name READ_WRITE_MONITOR_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}
 
 
  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual at0_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // AT0_SPACE_H
