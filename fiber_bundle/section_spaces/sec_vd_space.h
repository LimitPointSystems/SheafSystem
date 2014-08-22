
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

/// @file
/// Interface for class sec_vd_space.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_SPACE_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_SPACE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_TUPLE_SPACE_H
#include "ComLimitPoint/fiber_bundle/sec_tuple_space.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_VD_TABLE_DOFS_TYPE_H
#include "ComLimitPoint/fiber_bundle/vd_table_dofs_type.h"
#endif

namespace sheaf
{
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
  /// The type of scalar for the module of sections.
  ///
  typedef sec_at0 scalar_type;

  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef vd_table_dofs_type table_dofs_type;

  ///
  /// True if and only if scalar space of fiber space == fiber space of scalar space. 
  /// More precisely, true if and only if the scalar space of the fiber space of the 
  /// vector section schema specified by  xschema_path is the same as the fiber space 
  /// of the schema of the scalar section space specified by xscalar_space_path.
  ///
  static bool same_scalar_fiber_space(const namespace_poset& xns, 
                                      const poset_path& xschema_path, 
                                      const poset_path& xscalar_space_path, 
                                      bool xauto_access);

  ///
  /// Creates a new sec_vd_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and scalar space specified
  /// by xscalar_space_path.
  ///
  static sec_vd_space& new_table(namespace_type& xhost, 
                                 const poset_path& xpath, 
                                 const poset_path& xschema_path,
                                 const poset_path& xscalar_space_path,
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
  static std::string covariant_subposet_name(int xi);

  ///
  /// Default constructor;
  /// creates a new sec_vd_space handle not attached to any state.
  ///
  sec_vd_space();

  ///
  /// Copy constructor; disabled.
  ///
  sec_vd_space(const sec_vd_space& xother) { };

  ///
  /// Covariant constructor
  ///
  sec_vd_space(sec_vd* xtop, sec_vd* xbottom);

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

protected:

  ///
  /// Assignment operator; disabled.
  ///
  sec_vd_space& operator=(const poset_state_handle& xother)
  {
    return const_cast<sec_vd_space&>(*this);
  };

  ///
  /// Creates the standard subposets.
  ///
  virtual void initialize_standard_subposets(const std::string& xname);

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
		void print_prereq_paths(std::ostream &xos, 
			  const sec_vd_space& xspace, 
			  const std::string& xheading,
			  const std::string& xindex,
			  bool xauto_access);


} // namespace fiber_bundle


#endif // COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_SPACE_H
