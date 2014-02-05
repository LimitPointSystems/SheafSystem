
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
/// Interface for class sec_ed.

#ifndef SEC_ED_H
#define SEC_ED_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_AT1_H
#include "sec_at1.h"
#endif

#ifndef ED_H
#include "ed.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS SEC_ED
//==============================================================================

///
/// A section of a fiber bundle with a d-dimensional Euclidean
/// vector space fiber.
///
class SHEAF_DLL_SPEC sec_ed : public sec_at1
{

  // ===========================================================
  /// @name HOST_FACTORY FACET OF CLASS SEC_AT1
  // ===========================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef ed fiber_type;

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and table attribute scalar_space_path specified by xscalar_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             const poset_path& xscalar_space_path,
                             bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name ED FACET OF CLASS SEC_ED
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_ed();

  ///
  /// Creates a new sec_ed handle attached to the member state with hub id
  /// xhub_id in* xhost.
  ///
  sec_ed(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  ///
  /// Creates a new sec_ed handle attached to
  /// the member state with id xid in xhost.
  ///
  sec_ed(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_ed handle attached to
  /// the member state with name xname in xhost.
  ///
  sec_ed(const sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_ed(const namespace_poset* xnamespace,
         const poset_path& xpath,
         bool xauto_access = true);

  ///
  /// Creates a new sec_ed handle attached to the same state as xother.
  ///
  explicit sec_ed(const sec_rep_space_member* xother);

  ///
  /// Creates a new handle attached to a new jim state in xhost.
  /// If xdof_map is non-null it is used as the dof map for the new state.
  ///
  sec_ed(sec_rep_space* xhost,
         section_dof_map* xdof_map = 0,
         bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_ed(sec_rep_space* xhost,
         abstract_poset_member& xbase_mbr,
         int xbase_version = CURRENT_HOST_VERSION,
         bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_ed& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_ed& operator=(const sec_ed& xother);

  ///
  /// Assignment operator.
  ///
  sec_ed& operator=(const ed& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_ed& operator=(const ed_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_ed();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name AT1 FACET OF CLASS SEC_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ATP FACET OF CLASS SEC_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_ED
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
  virtual sec_ed* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_ed* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_ed*>(sec_at1::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_ED
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

///
/// Namespace containing the algrebra functions for a a section 
/// of a fiber bundle with a fiber type ed.
///
namespace sec_ed_algebra
{

///
/// The Euclidean "dot" product of x0 with x2.
///
SHEAF_DLL_SPEC void dot(const sec_ed& x0, const sec_ed& x1, sec_at0& xresult,
			bool xauto_access);

///
/// The Euclidean length (magnitude) of x0.
///
SHEAF_DLL_SPEC void length(const sec_ed& x0, sec_at0& xresult, bool xauto_access);

///
/// Set the Euclidean length (magnitude) of x0 to xlength.
///
SHEAF_DLL_SPEC void put_length(sec_ed& x0, const vd_value_type& xlength, bool xauto_access);

///
/// Normalize x0 (convert to a unit vector).
///
SHEAF_DLL_SPEC void normalize(const sec_ed& x0, sec_ed& xresult, bool xauto_access);

///
/// Normalize x0 (convert to a unit vector) in place;
/// synonym for normalize(x0, x0, xauto_access).
///
SHEAF_DLL_SPEC void normalize(sec_ed& x0, bool xauto_access);

} // namespace sec_tp_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_ED_H


