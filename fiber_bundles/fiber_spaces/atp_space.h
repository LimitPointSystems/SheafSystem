
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

// Interface for class atp_space.

#ifndef ATP_SPACE_H
#define ATP_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TP_SPACE_H
#include "tp_space.h"
#endif
  
namespace fiber_bundle
{

  using namespace sheaf;  

  class atp;
  
  
///
/// An abstract antisymmetric tensor space of degree p.
///
class SHEAF_DLL_SPEC atp_space : public tp_space
{
  friend class fiber_bundles_namespace;

public:

  // ===========================================================
  /// @name ATP_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef atp member_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const std::string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  using tp_space::d;
  
  ///
  /// The tensor dimension implied by tensor degree xp and
  /// the dimension of the domain vector space specified by xvector_space_path.
  ///
  static int d(const namespace_poset& xns, int xp, const poset_path& xvector_space_path, bool xauto_access);

  ///
  /// Creates a new atp_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attributes 
  /// p and vector_space_path specified by xp and xvector_space_path,
  /// respectively.
  ///
  static atp_space& new_table(namespace_type& xhost, 
			      const poset_path& xpath, 
			      const poset_path& xschema_path,
			      int xp,
			      const poset_path& xvector_space_path,
			      bool xauto_access);
  
  ///
  /// True if the member with id xmbr_id is a p-form;
  /// synonym for is_covariant(xmbr_id, xauto_access).
  ///
  bool is_p_form(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// True if the member with id xmbr_id is a p-form;
  /// synonym for is_covariant(xmbr_id, xauto_access).
  ///
  bool is_p_form(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Sets is_p_form for the member with id xmbr_id to true;
  /// synonym for put_is_covariant(xmbr_id, xauto_access).
  ///
  void put_is_p_form(pod_index_type xmbr_id, bool xauto_access);

  ///
  /// Sets is_p_form for the member with id xmbr_id to true;
  /// synonym for put_is_covariant(xmbr_id, xauto_access).
  ///
  void put_is_p_form(const scoped_index& xmbr_id, bool xauto_access);

  ///
  /// True if the member with id xmbr_id is a p-vector;
  /// synonym for is_contravariant(xmbr_id, xauto_access).
  ///
  bool is_p_vector(pod_index_type xmbr_id, bool xauto_access) const;

  ///
  /// True if the member with id xmbr_id is a p-vector;
  /// synonym for is_contravariant(xmbr_id, xauto_access).
  ///
  bool is_p_vector(const scoped_index& xmbr_id, bool xauto_access) const;

  ///
  /// Sets is_p_vector for the member with id xmbr_id to true.
  /// synonym for put_is_contravariant(xmbr_id, xauto_access).
  ///
  void put_is_p_vector(pod_index_type xmbr_id, bool xauto_access);

  ///
  /// Sets is_p_vector for the member with id xmbr_id to true.
  /// synonym for put_is_contravariant(xmbr_id, xauto_access).
  ///
  void put_is_p_vector(const scoped_index& xmbr_id, bool xauto_access);

protected:

  ///
  /// Default constructor;
  /// creates a new atp_space handle not attached to any state.
  ///
  atp_space();

  ///
  /// Copy constructor; disabled.
  ///
  atp_space(const atp_space& xother) { };

  ///
  /// Destructor.
  ///
  virtual ~atp_space();

  ///
  /// Covariant constructor
  ///
  atp_space(atp* xtop, atp* xbottom);

private:

  //@}

  // ===========================================================
  /// @name TP_SPACE FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Dimension d() as a function of degree xp and domain dimension xdd.
  ///
  virtual int d(int xp, int xdd) const;  

  ///
  /// "Rounds" xvariance up or down to a supported value;
  /// either pure covariant or pure contravariant.
  ///
  virtual tensor_variance round_variance(const tensor_variance& xvariance) const;

protected:

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

protected:

  ///
  /// Assignment operator; disabled.
  ///
  atp_space& operator=(const poset_state_handle& xother)
  {
    return const_cast<atp_space&>(*this);
  };

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
  virtual atp_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // ATP_SPACE_H
