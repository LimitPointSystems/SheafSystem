

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class vd_space.

#ifndef VD_SPACE_H
#define VD_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TUPLE_SPACE_H
#include "tuple_space.h"
#endif
  
#ifndef VD_TABLE_DOFS_TYPE_H
#include "vd_table_dofs_type.h"
#endif

namespace fiber_bundle
{

  using namespace sheaf;  

  class vd;
  
  
///
/// An abstract vector space of dimension d.
///
class SHEAF_DLL_SPEC vd_space : public tuple_space
{
  friend class fiber_bundles_namespace;

public:

  // ===========================================================
  /// @name VD_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef vd member_type;

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
  typedef vd_table_dofs_type table_dofs_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(const poset_path& xscalar_space_path);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

  using tuple_space::factor_ct;
  
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
  /// Default constructor;
  /// creates a new vd_space handle not attached to any state.
  ///
  vd_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  vd_space(const vd_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~vd_space();

  ///
  /// Covariant constructor
  ///
  vd_space(vd* xtop, vd* xbottom);

  ///
  /// The name of the covariant subposet for the xi-th index.
  ///
  static string covariant_subposet_name(int xi);

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
  vd_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the vd_space with
  /// index xindex in namespace xhost.
  ///
  vd_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the vd_space with
  /// index xindex in namespace xhost.
  ///
  vd_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the vd_space with
  /// name xname in namespace xhost.
  ///
  vd_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the vd_space associated
  /// with namespace member xmbr.
  ///
  vd_space(const namespace_poset_member& xmbr, bool xauto_access);

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
  vd_space& operator=(const poset_state_handle& xother);

protected:

  ///
  /// Creates the standard subposets.
  ///
  virtual void initialize_standard_subposets(const string& xname);

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
  virtual vd_space* clone() const;

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
  /// schema, scalar space, etc.
  ///
  SHEAF_DLL_SPEC void print_prereq_paths(ostream &xos, 
			  const vd_space& xspace, 
			  const string& xheading,
			  const string& xindent,
			  bool xauto_access = true);

} // namespace fiber_bundle


#endif // VD_SPACE_H