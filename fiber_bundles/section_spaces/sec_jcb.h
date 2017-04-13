
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
/// Interface for class sec_jcb.

#ifndef SEC_JCB_H
#define SEC_JCB_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef SEC_VD_H
#include "SheafSystem/sec_vd.h"
#endif

#ifndef JCB_H
#include "SheafSystem/jcb.h"
#endif

namespace fiber_bundle
{

class sec_at1;
class sec_jcb_space;  

//==============================================================================
// CLASS SEC_JCB
//==============================================================================

///
/// A section of a bundle with fiber type jcb.
///
class SHEAF_DLL_SPEC sec_jcb : public sec_vd
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS SEC_JCB
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef sec_jcb_space host_type;

  ///
  /// The type of domain vector space.
  ///
  typedef sec_at1 domain_type;

  ///
  /// The type of range vector space.
  ///
  typedef sec_at1 range_type;

  ///
  /// The fiber type.
  ///
  typedef jcb fiber_type;

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and table attribute domain_path and range_path specified by xdomain_path and xrange_path, respectively..
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             const poset_path& xdomain_space_path,
                             const poset_path& xrange_space_path,
                             bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name JCB FACET OF CLASS SEC_JCB
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_jcb();

  ///
  /// Creates a new sec_jcb handle attached to the member state with hub id
  /// xhub_id in* xhost.
  ///
  sec_jcb(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_jcb handle attached to the member state with id
  /// xid in* xhost.
  ///
  sec_jcb(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_jcb handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_jcb(const sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_jcb(const namespace_poset* xnamespace,
          const poset_path& xpath,
          bool xauto_access = true);

  ///
  /// Creates a new sec_jcb handle attached to the same state as xother.
  ///
  explicit sec_jcb(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_jcb(sec_rep_space* xhost,
          section_dof_map* xdof_map = 0,
          bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_jcb& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_jcb& operator=(const sec_jcb& xother);

  ///
  /// Assignment operator.
  ///
  sec_jcb& operator=(const jcb& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_jcb& operator=(const jcb_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_jcb();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

  ///
  /// Dimension of the domain.
  ///
  virtual int dd() const;

  ///
  /// Dimension of the domain (auto-access version).
  ///
  int dd(bool xauto_access) const;

  ///
  /// The path of the domain vector space.
  ///
  poset_path domain_path() const;

  ///
  /// The path of the domain vector space.
  ///
  poset_path domain_path(bool xauto_access) const;

  ///
  /// Dimension of the range.
  ///
  virtual int dr() const;

  ///
  /// Dimension of the range (auto-access version).
  ///
  int dr(bool xauto_access) const;

  ///
  /// The path of the range vector space.
  ///
  poset_path range_path() const;

  ///
  /// The path of the range vector space (auto-access version).
  ///
  poset_path range_path(bool xauto_access) const;

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_JCB
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_JCB
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_JCB
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
  virtual sec_jcb* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_jcb* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_jcb*>(sec_vd::clone(xnew_state, xauto_access));
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
  /// @name ANY FACET OF CLASS SEC_JCB
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to an instance of the fiber of current.
  ///
  bool fiber_is_ancestor_of(const any* xother) const;

  ///
  /// true if other conforms to current
  ///
  bool is_ancestor_of(const any* other) const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;

protected:

private:

  //@}


  //############################################################################
  //############################################################################

public:

  ///
  /// Component indexed by row and col.
  ///
  sec_at0* comp2(int row, int col) const;

  ///
  /// Sets component by row and col.
  ///
  void set_comp2(int row, int col, sec_at0* new_comp);

protected:
private:

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

class sec_at1;

///
/// Namespace containing the algrebra functions for a a section 
/// of a fiber bundle with a fiber type jcb.
///
namespace sec_jcb_algebra
{

#ifndef DOXYGEN_SKIP_UNKNOWN
///
/// Push vector forward (pre-allocated version).
///
SHEAF_DLL_SPEC void push(const sec_jcb& xjcb, const sec_at1& xvector, sec_at1& xresult,
			 bool xauto_access);
#endif // ifndef DOXYGEN_SKIP_UNKNOWN

///
/// Pull covector back (pre-allocated version).
///
SHEAF_DLL_SPEC void pull(const sec_jcb& xjcb, const sec_at1& xcovector, sec_at1& xresult,
			 bool xauto_access);

} // namespace sec_jcb_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_JCB_H


