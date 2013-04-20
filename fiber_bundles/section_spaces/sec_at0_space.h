


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_at0_space.

#ifndef SEC_AT0_SPACE_H
#define SEC_AT0_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_ATP_SPACE_H
#include "sec_atp_space.h"
#endif

namespace sheaf
{
class arg_list;
class namespace_poset;
}

namespace fiber_bundle
{
using namespace sheaf;

class sec_at0;
class at0;

///
/// A space of scalars viewed as an antisymmetric tensor section space
/// of degree 0.
///
class SHEAF_DLL_SPEC sec_at0_space : public sec_atp_space
{
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name SEC_AT0_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef sec_at0 member_type;

  ///
  /// The fiber type.
  ///
  typedef at0 fiber_type;

  ///
  /// The scalar type definition.
  ///
  typedef sec_at0 scalar_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list();
  
  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(const poset_path& xvector_space_path);
  
  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(int xp, const poset_path& xvector_space_path);
  

protected:

  ///
  /// Default constructor;
  /// creates a new sec_at0_space handle not attached to any state.
  ///
  sec_at0_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  sec_at0_space(const sec_at0_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~sec_at0_space();

  ///
  /// Covariant constructor
  ///
  sec_at0_space(sec_at0* xtop, sec_at0* xbottom);

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  sec_at0_space(namespace_poset& xhost,
		const string& xname,
		const arg_list& xargs,
		const poset_path& xschema_path,
		bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the sec_at0_space with
  /// index xindex in namespace xhost.
  ///
  sec_at0_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_at0_space with
  /// index xindex in namespace xhost.
  ///
  sec_at0_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_at0_space with
  /// name xname in namespace xhost.
  ///
  sec_at0_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_at0_space associated
  /// with namespace member xmbr.
  ///
  sec_at0_space(const namespace_poset_member& xmbr, bool xauto_access);

private:

  //@}


  // ===========================================================
  /// @name SEC_ATP_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name SEC_TP_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name SEC_VD_SPACE FACET
  // ===========================================================
  //@{

public:

  using sec_vd_space::is_vector;

  ///
  /// True if and only if the member with id xmbr_id is a vector (as opposed to a covector).
  ///
  virtual bool is_vector(pod_index_type xmbr_id, bool xauto_access) const;

  using sec_vd_space::put_is_vector;

  ///
  /// Sets is_vector true for the member with id xmbr_id.
  ///
  virtual void put_is_vector(pod_index_type xmbr_id, bool xauto_access);

  using sec_vd_space::is_covector;

  ///
  /// True if and only if the member with id xmbr_id is a covector.
  ///
  virtual bool is_covector(pod_index_type xmbr_id, bool xauto_access) const;;

  using sec_vd_space::put_is_covector;

  ///
  /// Sets is_covector true for the member with id xmbr_id.
  ///
  virtual void put_is_covector(pod_index_type xmbr_id, bool xauto_access);

protected:

  ///
  /// The number of covariant subposets.
  ///
  virtual size_type covariant_subposet_ct() const;

private:

  //@}


  // ===========================================================
  /// @name SEC_TUPLE_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name SEC_REP_SPACE FACET
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
  sec_at0_space& operator=(const poset_state_handle& xother);

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
  virtual sec_at0_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
 
};


} // namespace fiber_bundle


#endif // SEC_AT0_SPACE_H
