
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

// Interface for class tp_space.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_TP_SPACE_H
#define COM_LIMITPOINT_FIBER_BUNDLE_TP_SPACE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_VD_SPACE_H
#include "ComLimitPoint/fiber_bundle/vd_space.h"
#endif
  
#ifndef COM_LIMITPOINT_FIBER_BUNDLE_TP_TABLE_DOFS_TYPE_H
#include "ComLimitPoint/fiber_bundle/tp_table_dofs_type.h"
#endif

namespace fiber_bundle
{

  using namespace sheaf;  
  class at1_space;
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
  /// The type of domain vector space.
  ///
  typedef at1_space vector_space_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const std::string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();
  
  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef tp_table_dofs_type table_dofs_type;

  using vd_space::d;

  ///
  /// The tensor dimension implied by the schema specified by xschema_path.
  ///
  static int d(const namespace_poset& xns, const poset_path& xschema_path, bool xauto_access);
  
  ///
  /// The tensor dimension implied by tensor degree xp and
  /// the dimension of the domain vector space specified by xvector_space_path.
  ///
  static int d(const namespace_poset& xns, int xp, const poset_path& xvector_space_path, bool xauto_access);

  ///
  /// Creates a new tp_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attributes 
  /// p and vector_space_path specified by xp and xvector_space_path,
  /// respectively.
  ///
  static tp_space& new_table(namespace_type& xhost, 
			     const poset_path& xpath, 
			     const poset_path& xschema_path,
			     int xp,
			     const poset_path& xvector_space_path,
			     bool xauto_access);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================
  
  ///
  /// Dimension d() as a function of degree xp and domain dimension xdd.
  ///
  virtual int d(int xp, int xdd) const;

  ///
  /// Tensor degree as a function of tensor dimension xd and domain dimension xdd.
  ///
  int p(int xd, int xdd) const;
  
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
  /// Copy constructor; disabled.
  ///
  tp_space(const tp_space& xother) { };

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

private:

  //@}

  // ===========================================================
  /// @name POSET FACET
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
  tp_space& operator=(const poset_state_handle& xother);

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


#endif // COM_LIMITPOINT_FIBER_BUNDLE_TP_SPACE_H
