
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
/// Interface for class sec_at0_space.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_AT0_SPACE_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_AT0_SPACE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ATP_SPACE_H
#include "ComLimitPoint/fiber_bundle/sec_atp_space.h"
#endif

namespace sheaf
{
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
  friend class fiber_bundle_namespace;

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
  /// Creates a new sec_at0_space in namespace xns with path xpath
  /// and schema specified by xschema_path.
  ///
  static sec_at0_space& new_table(namespace_type& xhost, 
                                 const poset_path& xpath, 
                                 const poset_path& xschema_path,
                                 bool xauto_access);
  

protected:

  ///
  /// Default constructor;
  /// creates a new sec_at0_space handle not attached to any state.
  ///
  sec_at0_space();

  ///
  /// Copy constructor; disabled.
  ///
  sec_at0_space(const sec_at0_space& xother) { };

  ///
  /// Destructor.
  ///
  virtual ~sec_at0_space();

  ///
  /// Covariant constructor
  ///
  sec_at0_space(sec_at0* xtop, sec_at0* xbottom);

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
  sec_at0_space& operator=(const poset_state_handle& xother)
  {
    return const_cast<sec_at0_space&>(*this);
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


#endif // COM_LIMITPOINT_FIBER_BUNDLE_SEC_AT0_SPACE_H
