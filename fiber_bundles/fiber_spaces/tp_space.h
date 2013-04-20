

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class tp_space.

#ifndef TP_SPACE_H
#define TP_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef VD_SPACE_H
#include "vd_space.h"
#endif
  
#ifndef TP_TABLE_DOFS_TYPE_H
#include "tp_table_dofs_type.h"
#endif

namespace fiber_bundle
{

  using namespace sheaf;  
  class tensor_variance;
  class tp;
  
  
///
/// An abstract tensor space of degree p.
///
class SHEAF_DLL_SPEC tp_space : public vd_space
{
  friend class fiber_bundles_namespace;

public:

  // ===========================================================
  /// @name TP_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef tp member_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();
  
  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef tp_table_dofs_type table_dofs_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(int xp, const poset_path& xvector_space_path);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

  using vd_space::d;
  
  ///
  /// Dimension d() as a function of degree xp and domain dimension xdd.
  ///
  virtual int d(int xp, int xdd) const;

  ///
  /// True if and only if the dimension d implied by the row dofs
  /// specified in the schema with path xschema_path is equal to
  /// the dimension implied by p and the underlying vector space 
  /// specifed in xargs.
  ///
  bool d_is_valid(const namespace_poset& xns, 
		  const poset_path& xschema_path, 
		  const arg_list& xargs,
		  bool xautuo_access) const;
  
  
  ///
  /// The tensor degree of this space.
  ///
  int p() const;

  ///
  /// The tensor degree of this space; auto access signature.
  ///
  int p(bool xauto_access) const;

  ///
  /// The dimension of the underlying ("domain") vector space.
  ///
  int dd() const;

  ///
  /// The dimension of the underlying ("domain") vector space; auto access signature.
  ///
  int dd(bool xauto_access) const;

  ///
  /// The path of the underlying vector space.
  ///
  poset_path vector_space_path() const;

  ///
  /// The path of the underlying vector space, auto access version.
  ///
  poset_path vector_space_path(bool xauto_access) const;

  ///
  /// The variance of the member with id xmbr_id.
  ///
  virtual tensor_variance variance(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// The variance of the member with id xmbr_id.
  ///
  tensor_variance variance(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// The variance of the xi-th tensor index position of the member with id xmbr_id;
  /// true if covariant, false if contravariant.
  ///
  virtual bool variance(pod_index_type xmbr_id, int xi, bool xauto_access) const;

  ///
  /// The variance of the xi-th tensor index position of the member with id xmbr_id;
  /// true if covariant, false if contravariant.
  ///
  bool variance(const scoped_index& xmbr_id, int xi, bool xauto_access) const;

  ///
  /// Sets the variance of the member with id xmbr_id to xvariance.
  ///
  void put_variance(pod_index_type xmbr_id, const tensor_variance& xvariance, bool xauto_access);

  ///
  /// Sets the variance of the member with id xmbr_id to xvariance.
  ///
  void put_variance(const scoped_index& xmbr_id, const tensor_variance& xvariance, bool xauto_access);

  ///
  /// Sets the variance of the xi-th index of the member with id xmbr_id to xvariance.
  ///
  void put_variance(pod_index_type xmbr_id, int xi, bool xvariance, bool xauto_access);

  ///
  /// Sets the variance of the xi-th index of the member with id xmbr_id to xvariance.
  ///
  void put_variance(const scoped_index& xmbr_id, int xi, bool xvariance, bool xauto_access);

  ///
  /// "Rounds" xvariance up or down to a supported value.
  /// Version defined in this class just returns xvariance,
  /// redefined in stp_space and atp_space to return pure 
  /// covariant or pure contravariant.
  ///
  virtual tensor_variance round_variance(const tensor_variance& xvariance) const;
    
  ///
  /// True if and only if all tensor index positions of the member with id xmbr_id are covariant.
  ///
  virtual bool is_covariant(pod_index_type xmbr_id, bool xauto_access) const;
    
  ///
  /// True if and only if all tensor index positions of the member with id xmbr_id are covariant.
  ///
  bool is_covariant(const scoped_index& xmbr_id, bool xauto_access) const;
    
  ///
  /// True if and only if the xi-th tensor index position of the member with id xmbr_id is covariant.
  ///
  virtual bool is_covariant(pod_index_type xmbr_id, int xi, bool xauto_access) const;
    
  ///
  /// True if and only if the xi-th tensor index position of the member with id xmbr_id is covariant.
  ///
  bool is_covariant(const scoped_index& xmbr_id, int xi, bool xauto_access) const;
    
  ///
  /// Sets all tensor index positions of the member with id xmbr_id to covariant.
  ///
  virtual void put_is_covariant(pod_index_type xmbr_id, bool xauto_access);
  
  ///
  /// Sets all tensor index positions of the member with id xmbr_id to covariant.
  ///
  void put_is_covariant(const scoped_index& xmbr_id, bool xauto_access);
  
  ///
  /// Sets the variance of the xi-th tensor index position of the member with id xmbr_id to covariant.
  ///
  void put_is_covariant(pod_index_type xmbr_id, int xi, bool xauto_access);
 
  ///
  /// Sets the variance of the xi-th tensor index position of the member with id xmbr_id to covariant.
  ///
  void put_is_covariant(const scoped_index& xmbr_id, int xi, bool xauto_access);
 
  ///
  /// True if and only if all tensor index positions of the member with id xmbr_id are contravariant.
  ///
  virtual bool is_contravariant(pod_index_type xmbr_id, bool xauto_access) const;
 
  ///
  /// True if and only if all tensor index positions of the member with id xmbr_id are contravariant.
  ///
  bool is_contravariant(const scoped_index& xmbr_id, bool xauto_access) const;
 
  ///
  /// True if and only if the xi-th tensor index position of the member with id xmbr_id is contravariant.
  ///
  virtual bool is_contravariant(pod_index_type xmbr_id, int xi, bool xauto_access) const;
    
  ///
  /// True if and only if the xi-th tensor index position of the member with id xmbr_id is contravariant.
  ///
  bool is_contravariant(const scoped_index& xmbr_id, int xi, bool xauto_access) const;
    
  ///
  /// Sets all tensor index positions of the member with id xmbr_id to contravariant.
  ///
  virtual void put_is_contravariant(pod_index_type xmbr_id, bool xauto_access);
  
  ///
  /// Sets all tensor index positions of the member with id xmbr_id to contravariant.
  ///
  void put_is_contravariant(const scoped_index& xmbr_id, bool xauto_access);
  
  ///
  /// Sets the variance of the xi-th tensor index position of the member with id xmbr_id to contravariant.
  ///
  void put_is_contravariant(pod_index_type xmbr_id, int xi, bool xauto_access);

  ///
  /// Sets the variance of the xi-th tensor index position of the member with id xmbr_id to contravariant.
  ///
  void put_is_contravariant(const scoped_index& xmbr_id, int xi, bool xauto_access);

protected:

  ///
  /// Default constructor;
  /// creates a new tp_space handle not attached to any state.
  ///
  tp_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  tp_space(const tp_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~tp_space();

  ///
  /// Covariant constructor
  ///
  tp_space(tp* xtop, tp* xbottom);

  ///
  /// The number of covariant subposets.
  ///
  virtual size_type covariant_subposet_ct() const;

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  tp_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the tp_space with
  /// index xindex in namespace xhost.
  ///
  tp_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the tp_space with
  /// index xindex in namespace xhost.
  ///
  tp_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the tp_space with
  /// name xname in namespace xhost.
  ///
  tp_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the tp_space associated
  /// with namespace member xmbr.
  ///
  tp_space(const namespace_poset_member& xmbr, bool xauto_access);

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
  tp_space& operator=(const poset_state_handle& xother);

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
  virtual tp_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // TP_SPACE_H