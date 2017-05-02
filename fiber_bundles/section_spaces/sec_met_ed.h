
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
/// Interface for class sec_met_ed.

#ifndef SEC_MET_ED_H
#define SEC_MET_ED_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef SEC_MET_H
#include "SheafSystem/sec_met.h"
#endif

#ifndef MET_ED_H
#include "SheafSystem/met_ed.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS SEC_MET_ED
//==============================================================================

///
/// A section of a bundle with fiber type met_ed.
///
class SHEAF_DLL_SPEC sec_met_ed : public sec_met
{
  // ===========================================================
  /// @name HOST_FACTORY FACET OF CLASS SEC_MET_ED
  // ===========================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef met_ed fiber_type;

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
  /// @name MET_ED FACET OF CLASS SEC_MET_ED
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_met_ed();

  ///
  /// Creates a new sec_met_ed handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_met_ed(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_met_ed handle attached to the member state with id
  /// xid in* xhost.
  ///
  sec_met_ed(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_met_ed handle attached to the member state with name
  /// xname in* xhost.
  ///
  sec_met_ed(const sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_met_ed(const namespace_poset* xnamespace,
             const poset_path& xpath,
             bool xauto_access = true);

  ///
  /// Creates a new sec_met_ed handle attached to the same state as xother.
  ///
  explicit sec_met_ed(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_met_ed(sec_rep_space* xhost,
             section_dof_map* xdof_map = 0,
             bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_met_ed& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_met_ed& operator=(const sec_met_ed& xother);

  ///
  /// Assignment operator.
  ///
  sec_met_ed& operator=(const met_ed& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_met_ed& operator=(const met_ed_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_met_ed();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;
  
protected:

private:

  //@}


  //============================================================================
  /// @name MET FACET OF CLASS SEC_MET_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS SEC_MET_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS SEC_MET_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_MET_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_MET_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_MET_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_MET_ED
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
  virtual sec_met_ed* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_met_ed* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_met_ed*>(sec_met::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_MET_ED
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

} // namespace fiber_bundle

#endif // ifndef SEC_MET_ED_H


