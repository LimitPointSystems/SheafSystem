
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
/// Interface for class sec_at0.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_AT0_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_AT0_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ATP_H
#include "ComLimitPoint/fiber_bundle/sec_atp.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_AT0_H
#include "ComLimitPoint/fiber_bundle/at0.h"
#endif

namespace fiber_bundle
{

class sec_at0_space;

//==============================================================================
// CLASS SEC_AT0
//==============================================================================

///
/// Antisymetric tensor of degree 0.
/// As the degree is 0 there is nothing to be symmetric or antisymmetric with
/// respect to.  Thus, this could have equivalently been the symmetric tensor
/// with degree=0.  The convention is to choose antisymmetric.
///
class SHEAF_DLL_SPEC sec_at0 : public sec_atp
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS SEC_AT0
  // ===========================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of host poset.
  ///
  typedef sec_at0_space host_type;

  ///
  /// The fiber type.
  ///
  typedef at0 fiber_type;

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path and schema specified by xschema_path,
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             bool xauto_access);

  ///
  /// The standard host for sections of this type with base space xbase_path,
  /// representation xrep_path, section suffix xsection_suffix,
  /// and fiber suffix xfiber_suffix. Creates the host and its prerequisites
  /// if necessary.
  ///
  static host_type& standard_host(namespace_type& xns, 
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const std::string& xsection_suffix, 
                                  const std::string& xfiber_suffix, 
                                  bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name AT0 FACET OF CLASS SEC_AT0
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_at0();

  ///
  /// Creates a new sec_at0 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_at0(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_at0 handle attached to the member state with id
  /// xid in* xhost.
  ///
  sec_at0(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_at0 handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_at0(const sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_at0(const namespace_poset* xnamespace,
          const poset_path& xpath,
          bool xauto_access = true);

  ///
  /// Creates a new sec_at0 handle attached to the same state as xother.
  ///
  explicit sec_at0(const sec_at0* xother);

  ///
  /// Creates a new sec_at0 handle attached to the component of 
  /// xother identified by xfiber_schema_jim.
  ///
  explicit sec_at0(const sec_rep_space_member* xother,
                   abstract_poset_member* xfiber_schema_jim);

  ///
  /// New handle/new state constructor.
  ///
  sec_at0(sec_rep_space* xhost, section_dof_map* xdof_map = 0,
          bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_at0(sec_rep_space* xhost,
          const abstract_poset_member& xbase_mbr,
          int xbase_version = CURRENT_HOST_VERSION,
          bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jrm state which is
  /// a multi-section with a branch for each member of the base space
  /// contained in xbase_parts.
  ///
  sec_at0(sec_rep_space* xhost, const subposet& xbase_parts, bool xauto_sccess);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_at0& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_at0& operator=(const sec_at0& xother);

  ///
  /// Assignment operator.
  ///
  sec_at0& operator=(const at0& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_at0& operator=(const at0_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_at0();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name ATP FACET OF CLASS SEC_AT0
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_AT0
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_AT0
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name  TUPLE FACET OF CLASS SEC_AT0
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_AT0
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual sec_at0* clone() const;

  

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_at0* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_at0*>(sec_atp::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET_COMPONENT FACET
  // ===========================================================
  //@{

public:

  ///
  /// The poset this is a member of.
  ///
  host_type* host() const;

  ///
  /// True if other conforms to host.
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* other) const;

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_AT0
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to an instance of the fiber of current.
  ///
  bool fiber_is_ancestor_of(const any* xother) const;

  ///
  /// True if xother conforms to current.
  ///
  bool is_ancestor_of(const any* xother) const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;

  using sec_tuple::restrict_to;

  ///
  /// Restricts this section and its components to schema member xschema.
  ///
  virtual void restrict_to(const abstract_poset_member* xschema);

  ///
  /// Restricts this section to base with hub id xbase_id and
  /// fiber schema with hub id xfiber_schema_id
  ///
  virtual void restrict_to(pod_index_type xbase_id,
                           pod_index_type xfiber_schema_id);


  ///
  /// Restricts this section and its components to base xbase and
  /// fiber schema xfiber_schema
  ///
  virtual void restrict_to(const abstract_poset_member* xbase,
                           const abstract_poset_member* xfiber_schema);

  ///
  /// Restricts this handle and its components to the same restriction
  /// as xother.
  ///
  virtual void restrict_to_same(const abstract_poset_member* xother);

  ///
  /// Removes any restriction to this handle and its components;
  /// restores base and fiber to the base and fiber of host, respectively.
  ///
  void unrestrict();

protected:

private:

  //@}

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert sec_at0& xv into ostream& xos
///
SHEAF_DLL_SPEC std::ostream& operator << (std::ostream& xos, const sec_at0& xv);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

//==============================================================================

///
/// Namespace containing the algrebra functions for a section 
/// of a fiber bundle with a fiber type at0.
///
namespace sec_at0_algebra
{

///
/// Compute acos of x0 (acos(x0)) (pre-allocated version).
///
 SHEAF_DLL_SPEC void acos(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute asin of x0 (asin(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void asin(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute atan of x0 (atan(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void atan(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute atan2 of x0/x1 (atan2(x0, x1)) (pre-allocated version).
///
SHEAF_DLL_SPEC void atan2(const sec_at0& x0, const sec_at0& x1, sec_at0& xresult,
           bool xauto_access);

///
/// Compute ceil of x0 (ceil(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void ceil(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute cos of x0 (cos(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void cos(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute cosh of x0 (cosh(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void cosh(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute exp of x0 (exp(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void exp(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute fabs of x0 (fabs(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void fabs(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute floor of x0 (floor(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void floor(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute xsignificand = fmod(x0, xexp) (pre-allocated version).
///
SHEAF_DLL_SPEC void fmod(const sec_at0& x0, const sec_at0& x1, sec_at0& xresult, bool xauto_access);

///
/// Compute frexp of x0 (frexp(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void frexp(const sec_at0& x0, sec_at0& xsignificand, sec_at0& xexp,
			  bool xauto_access);

///
/// Compute ldexp of x0 (ldexp(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void ldexp(const sec_at0& x0, int xexp, sec_at0& xresult, bool xauto_access);

///
/// Compute log of x0 (log(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void log(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute log10 of x0 (log10(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void log10(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute modf of x0 (modf(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void modf(const sec_at0& x0, sec_at0& xintpart, sec_at0& xfractpart,
			 bool xauto_access);

///
/// Compute x0 to power xexponent (pow(x0, xexponent)) (pre-allocated version).
///
SHEAF_DLL_SPEC void pow(const sec_at0& x0, const vd_value_type& xexponent, sec_at0& xresult,
			bool xauto_access);

///
/// Compute sin of x0 (sin(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void sin(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute sinh of x0 (sinh(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void sinh(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute sqrt of x0 (sqrt(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void sqrt(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute tan of x0 (tan(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void tan(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

///
/// Compute tanh of x0 (tanh(x0)) (pre-allocated version).
///
SHEAF_DLL_SPEC void tanh(const sec_at0& x0, sec_at0& xresult, bool xauto_access);

} // namespace sec_at0_algebra

} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_AT0_H


