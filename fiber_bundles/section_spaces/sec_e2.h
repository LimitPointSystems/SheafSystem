
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
/// Interface for class sec_e2.

#ifndef SEC_E2_H
#define SEC_E2_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef SEC_ED_H
#include "SheafSystem/sec_ed.h"
#endif

#ifndef E2_H
#include "SheafSystem/e2.h"
#endif

namespace fiber_bundle
{
  class fiber_bundles_namespace;
  
//==============================================================================
// CLASS SEC_E2
//==============================================================================

///
/// A section of a fiber bundle with a 2-dimensional Euclidean
/// vector space fiber.
///
class SHEAF_DLL_SPEC sec_e2 : public sec_ed
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS SEC_E2
  // ===========================================================
  //@{

public:

  // Typedefs:

  ///
  /// The fiber type.
  ///
  typedef e2 fiber_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef sec_e2 vector_space_type;

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and scalar section space specified by xscalar_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             const poset_path& xscalar_space_path,
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
  /// @name E2 FACET OF CLASS SEC_E2
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_e2();

  ///
  /// Creates a new sec_e2 handle attached to the member state with hub id
  /// xhub_id in* xhost.
  ///
  sec_e2(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_e2 handle attached to the member state with id xid
  /// in* xhost.
  ///
  sec_e2(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_e2 handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_e2(const sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_e2(const namespace_poset* xnamespace,
         const poset_path& xpath,
         bool xauto_access = true);

  ///
  /// Creates a new sec_e2 handle attached to the same state as xother.
  ///
  explicit sec_e2(const sec_rep_space_member* xother);

  ///
  /// Creates a new sec_e2 handle attached to a new jim state in xhost.
  /// If xdof_map == 0 a new dof map is created. If xdof_map != 0,
  /// xdof_map is used as the dof map.
  ///
  sec_e2(sec_rep_space* xhost,
         section_dof_map* xdof_map = 0,
         bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_e2(sec_rep_space* xhost,
         abstract_poset_member& xbase_mbr,
         int xbase_version = CURRENT_HOST_VERSION,
         bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jrm state which is
  /// a multi-section with a branch for each member of the base space
  /// contained in xbase_parts.
  ///
  sec_e2(sec_rep_space* xhost, const subposet& xbase_parts, bool xauto_access);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_e2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_e2& operator=(const sec_e2& xother);

  ///
  /// Assignment operator.
  ///
  sec_e2& operator=(const e2& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_e2& operator=(const e2_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_e2();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name ED FACET OF CLASS SEC_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name AT1 FACET OF CLASS SEC_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ATP FACET OF CLASS SEC_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_E2
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
  /// Make a new handle, no state instance of current
  ///
  virtual sec_e2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_e2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_e2*>(sec_ed::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_E2
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

protected:

private:

  //@}

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

//==============================================================================
// TP FACET
//==============================================================================

// Forward declarations needed for specialization:

class sec_at0;
class sec_at2_e2;
class sec_st2_e2;
class sec_t2_e2;
// class sec_at3_e2;
// class sec_st3_e2;
// class sec_t3_e2;

///
/// Specialization for degree 0 tensors over sec_e2.
///
template<> class tensor_section_traits<0, sec_e2>
{
public:
  ///
  /// Type of general tensor of degree 0 over sec_e2.
  ///
  typedef sec_at0 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 0 over sec_e2.
  ///
  typedef sec_at0 atp_type;

  ///
  /// Type of symmetric tensor of degree 0 over sec_e2.
  ///
  typedef sec_at0 stp_type;
};
  
///
/// Specialization for degree 1 tensors over sec_e2.
///
template<> class tensor_section_traits<1, sec_e2>
{
public:
  ///
  /// Type of general tensor of degree 1 over sec_e2.
  ///
  typedef sec_e2 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 1 over sec_e2.
  ///
  typedef sec_e2 atp_type;

  ///
  /// Type of symmetric tensor of degree 1 over sec_e2.
  ///
  typedef sec_e2 stp_type;
};
  
///
/// Specialization for degree 2 tensors over sec_e2.
///
template<> class tensor_section_traits<2, sec_e2>
{
public:
  ///
  /// Type of general tensor of degree 2 over sec_e2.
  ///
  typedef sec_t2_e2 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 2 over sec_e2.
  ///
  typedef sec_at2_e2 atp_type;

  ///
  /// Type of symmetric tensor of degree 2 over sec_e2.
  ///
  typedef sec_st2_e2 stp_type;
};
  
// ///
// /// Specialization for degree 3 tensors over sec_e2.
// ///
// template<> class tensor_section_traits<3, sec_e2>
// {
// public:
//   ///
//   /// Type of general tensor of degree 3 over sec_e2.
//   ///
//   typedef sec_t3_e2 tp_type;

//   ///
//   /// Type of antisymmetric tensor of degree 3 over sec_e2.
//   ///
//   typedef sec_at3_e2 atp_type;

//   ///
//   /// Type of symmetric tensor of degree 3 over sec_e2.
//   ///
//   typedef sec_st3_e2 stp_type;
// };


} // namespace fiber_bundle

#endif // ifndef SEC_E2_H


