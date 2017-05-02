
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
/// Interface for class sec_atp.

#ifndef SEC_ATP_H
#define SEC_ATP_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef SEC_TP_H
#include "SheafSystem/sec_tp.h"
#endif

#ifndef ATP_H
#include "SheafSystem/atp.h"
#endif

namespace fiber_bundle
{

class sec_atp_space;  

//==============================================================================
// CLASS SEC_ATP
//==============================================================================

///
/// A section of a bundle with fiber type atp.
///
class SHEAF_DLL_SPEC sec_atp : public sec_tp
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS SEC_ATP
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef sec_atp_space host_type;

  ///
  /// The fiber type.
  ///
  typedef atp fiber_type;

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and table attribute vector_space_path specified by xvector_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             const poset_path& xvector_space_path,
                             bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name ATP FACET OF CLASS SEC_ATP
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_atp();

  ///
  /// Creates a new sec_atp handle attached to the member state with hub id
  /// xhub_id in* xhost.
  ///
  sec_atp(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_atp handle attached to the member state with id
  /// xid in* xhost.
  ///
  sec_atp(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_atp handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_atp(const sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_atp(const namespace_poset* xnamespace,
          const poset_path& xpath,
          bool xauto_access = true);

  ///
  /// Creates a new sec_atp handle attached to the same state as xother.
  ///
  explicit sec_atp(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_atp(sec_rep_space* xhost,
          section_dof_map* xdof_map = 0,
          bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_atp(sec_rep_space* xhost,
          abstract_poset_member& xbase_mbr,
          int xbase_version = CURRENT_HOST_VERSION,
          bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_atp& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_atp& operator=(const sec_atp& xother);

  ///
  /// Assignment operator.
  ///
  sec_atp& operator=(const atp& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_atp& operator=(const atp_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_atp();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

  ///
  /// True if this is a p-form.
  ///
  bool is_p_form(bool xauto_access) const;

  ///
  /// Sets is_p_form to true.
  ///
  void put_is_p_form(bool xauto_access);

  ///
  /// True if this is a p-vector.
  ///
  bool is_p_vector(bool xauto_access) const;

  ///
  /// Sets is_p_vector to true.
  ///
  void put_is_p_vector(bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_ATP
  //============================================================================
  //@{

public:
  
protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_ATP
  //============================================================================
  //@{

public:
  
protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_ATP
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_ATP
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
  virtual sec_atp* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_atp* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_atp*>(sec_tp::clone(xnew_state, xauto_access));
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
  /// @name ANY FACET OF CLASS SEC_ATP
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
  /// class invariant
  ///
  bool invariant() const;

protected:

private:

  //@}

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// Namespace containing the algrebra functions for a a section 
/// of a fiber bundle with a fiber type atp.
///
namespace sec_atp_algebra
{

///
/// The interior (hook) product of two antisymmetric tensors
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void hook(const sec_atp& x0, const  sec_atp& x1, sec_atp& xresult,
			 bool xauto_access);

///
/// The Hodge star operator for antisymmetric tensors
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void star(const sec_atp& x0, sec_atp& xresult, bool xauto_access);

///
/// The exterior (wedge) product of two antisymmetric tensors
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void wedge(const sec_atp& x0, const sec_atp& x1, sec_atp& xresult,
			  bool xauto_access);

} // namespace sec_atp_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_ATP_H


