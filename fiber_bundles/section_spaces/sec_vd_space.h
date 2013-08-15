


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_vd_space.

#ifndef SEC_VD_SPACE_H
#define SEC_VD_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_TUPLE_SPACE_H
#include "sec_tuple_space.h"
#endif

#ifndef VD_TABLE_DOFS_TYPE_H
#include "vd_table_dofs_type.h"
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
class sec_vd;
class vd;

///
/// An abstract vector section space of dimension d.
///
class SHEAF_DLL_SPEC sec_vd_space : public sec_tuple_space
{
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name SEC_VD_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef sec_vd member_type;

  ///
  /// The fiber type.
  ///
  typedef vd fiber_type;

  ///
  /// The scalar type definition.
  ///
  typedef sec_at0 scalar_type;

  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef vd_table_dofs_type table_dofs_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(const poset_path& xscalar_space_path);

  ///
  /// Creates a new sec_vd_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and scalar space specified
  /// by xscalar_space_path.
  ///
  static void new_table(namespace_type& xhost, 
                        const poset_path& xpath, 
                        const poset_path& xschema_path,
                        const poset_path& xsclar_space_path,
                        bool xauto_access);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

  using sec_tuple_space::factor_ct;
  
  ///
  /// Factor_ct() as a function of dimension xd.
  /// 
  static int factor_ct(int xd);
  
  ///
  /// The dimension.
  ///
  int d() const;

  ///
  /// The dimension; auto access signature.
  ///
  int d(bool xauto_access) const;

  ///
  /// The dimension of the vector space with 
  /// path xvector_space_path in namespace xns.
  ///
  static int d(const namespace_poset& xns, 
	       const poset_path& xvector_space_path, 
	       bool xauto_access);

  ///
  /// The path of the underlying space of scalars.
  ///
  poset_path scalar_space_path() const;

  ///
  /// The path of the underlying space of scalars, auto access version.
  ///
  poset_path scalar_space_path(bool xauto_access) const;

  ///
  /// The path of the underlying space of scalars 
  /// of the vector space with path xvector_space_path, 
  /// in namespace xns.
  ///
  static poset_path scalar_space_path(const namespace_poset& xns, 
				      const poset_path& xvector_space_path, 
				      bool xauto_access);
  
  ///
  /// True if the variance subposets exist.
  ///
  bool contains_variance_subposets(bool xauto_access) const;

  ///
  /// True if and only if the member with id xmbr_id is a vector (as opposed to a covector).
  ///
  virtual bool is_vector(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// True if and only if the member with id xmbr_id is a vector (as opposed to a covector).
  ///
  bool is_vector(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Sets is_vector true for the member with id xmbr_id.
  ///
  virtual void put_is_vector(pod_index_type xmbr_id, bool xauto_access);

  ///
  /// Sets is_vector true for the member with id xmbr_id.
  ///
  void put_is_vector(const scoped_index& xmbr_id, bool xauto_access);

  ///
  /// True if and only if the member with id xmbr_id is a covector.
  ///
  virtual bool is_covector(pod_index_type xmbr_id, bool xauto_access) const;;

  ///
  /// True if and only if the member with id xmbr_id is a covector.
  ///
  bool is_covector(const scoped_index& xmbr_id, bool xauto_access) const;;

  ///
  /// Sets is_covector true for the member with id xmbr_id.
  ///
  virtual void put_is_covector(pod_index_type xmbr_id, bool xauto_access);

  ///
  /// Sets is_covector true for the member with id xmbr_id.
  ///
  void put_is_covector(const scoped_index& xmbr_id, bool xauto_access);

protected:

  ///
  /// The name of the covariant subposet for the xi-th index.
  ///
  static string covariant_subposet_name(int xi);

  ///
  /// Default constructor;
  /// creates a new sec_vd_space handle not attached to any state.
  ///
  sec_vd_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  sec_vd_space(const sec_vd_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~sec_vd_space();

  ///
  /// Create covariant subposets.
  ///
  void create_variance_subposets();

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
  sec_vd_space(namespace_poset& xhost,
	       const string& xname,
	       const arg_list& xargs,
	       const poset_path& xschema_path,
	       bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Covariant constructor
  ///
  sec_vd_space(sec_vd* xtop, sec_vd* xbottom);

  ///
  /// Creates a new handle attached to the sec_vd_space with
  /// index xindex in namespace xhost.
  ///
  sec_vd_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_vd_space with
  /// index xindex in namespace xhost.
  ///
  sec_vd_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_vd_space with
  /// name xname in namespace xhost.
  ///
  sec_vd_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_vd_space associated
  /// with namespace member xmbr.
  ///
  sec_vd_space(const namespace_poset_member& xmbr, bool xauto_access);

private:

  //@}


  // ===========================================================
  /// @name SEC_TUPLE FACET
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
  sec_vd_space& operator=(const poset_state_handle& xother);

protected:

  ///
  /// Creates the standard subposets.
  ///
  virtual void initialize_standard_subposets(const string& xname);

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
  virtual sec_vd_space* clone() const;

  ///
  /// Class invariant.
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
  /// Print the paths for xspace and its prerequisites:
  /// schema, rep, base, fiber, scalar space, etc.
  ///
  SHEAF_DLL_SPEC
		void print_prereq_paths(ostream &xos, 
			  const sec_vd_space& xspace, 
			  const string& xheading,
			  const string& xindex,
			  bool xauto_access);


} // namespace fiber_bundle


#endif // SEC_VD_SPACE_H
