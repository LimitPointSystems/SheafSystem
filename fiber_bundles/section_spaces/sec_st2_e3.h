
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
/// Interface for class sec_st2_e3.

#ifndef SEC_ST2_E3_H
#define SEC_ST2_E3_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef SEC_ST2_H
#include "SheafSystem/sec_st2.h"
#endif

#ifndef ST2_E3
#include "SheafSystem/st2_e3.h"
#endif

namespace fiber_bundle
{

class sec_e3;

//==============================================================================
// CLASS SEC_ST2_E3
//==============================================================================

///
/// A section of a bundle with fiber type st2_e3.
///
class SHEAF_DLL_SPEC sec_st2_e3 : public sec_st2
{
  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS SEC_ST2_E3
  // ===========================================================
  //@{

public:

  // Typedefs:

  ///
  /// The fiber type.
  ///
  typedef st2_e3 fiber_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef sec_e3 vector_space_type;

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and vector section space specified by xvector_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             const poset_path& xvector_space_path,
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
  /// @name ST2_E3 FACET OF CLASS SEC_ST2_E3
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_st2_e3();

  ///
  /// Creates a new sec_st2_e3 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_st2_e3(const sec_rep_space* xhost, pod_index_type xindex);

  ///
  /// Creates a new sec_st2_e3 handle attached to the member state with id
  /// xid in xhost.
  ///
  sec_st2_e3(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_st2_e3 handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_st2_e3(const  sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_st2_e3(const namespace_poset* xnamespace,
             const poset_path& xpath,
             bool xauto_access = true);

  ///
  /// Creates a new sec_st2_e3 handle attached to the same state as xother.
  ///
  explicit sec_st2_e3(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_st2_e3(sec_rep_space* xhost,
             section_dof_map* xdof_map = 0,
             bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_st2_e3(sec_rep_space* xhost,
             abstract_poset_member& xbase_mbr,
             int xbase_version = CURRENT_HOST_VERSION,
             bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_st2_e3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_st2_e3& operator=(const sec_st2_e3& xother);

  ///
  /// Assignment operator.
  ///
  sec_st2_e3& operator=(const st2_e3& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_st2_e3& operator=(const st2_e3_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_st2_e3();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS SEC_ST2_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS SEC_ST2_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_ST2_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_ST2_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_ST2_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_ST2_E3
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
  virtual sec_st2_e3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_st2_e3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_st2_e3*>(sec_st2::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_ST2_E3
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
// public:

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================


class sec_at0;

namespace sec_st2_algebra
{

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// The determinant of x0.
///
SHEAF_DLL_SPEC void determinant(const sec_st2_e3& x0, sec_at0& xresult, bool xauto_access);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace sec_st2_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_ST2_E3_H


