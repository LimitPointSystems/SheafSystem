
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

/// @file
/// Interface for class sec_met_e2.

#ifndef SEC_MET_E2_H
#define SEC_MET_E2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_MET_ED_H
#include "sec_met_ed.h"
#endif

#ifndef MET_E2_H
#include "met_e2.h"
#endif

namespace fiber_bundle
{

class sec_e2;

//==============================================================================
// CLASS SEC_MET_E2
//==============================================================================

///
/// A section of a bundle with fiber type met_e2.
///
class SHEAF_DLL_SPEC sec_met_e2 : public sec_met_ed
{
  //============================================================================
  /// @name MET_E2 FACET OF CLASS SEC_MET_E2
  //============================================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef met_e2 fiber_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef sec_e2 vector_space_type;

  ///
  /// default constructor
  ///
  sec_met_e2();

  ///
  /// Creates a new sec_met_e2 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_met_e2(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_met_e2 handle attached to the member state with id
  /// xid in* xhost.
  ///
  sec_met_e2(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_met_e2 handle attached to the member state with name
  /// xname in* xhost.
  ///
  sec_met_e2(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_met_e2(const namespace_poset* xnamespace,
             const poset_path& xpath,
             bool xauto_access = true);
  ///
  /// Creates a new sec_met_e2 handle attached to the same state as xother.
  ///
  explicit sec_met_e2(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_met_e2(sec_rep_space* xhost,
             section_dof_map* xdof_map = 0,
             bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_met_e2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_met_e2& operator=(const sec_met_e2& xother);

  ///
  /// Assignment operator.
  ///
  sec_met_e2& operator=(const met_e2& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_met_e2& operator=(const met_e2_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_met_e2();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name MET_ED FACET OF CLASS SEC_MET_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name MET FACET OF CLASS SEC_MET_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS SEC_MET_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS SEC_MET_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_MET_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_MET_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_MET_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_MET_E2
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual sec_met_e2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_met_e2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_met_e2*>(sec_met_ed::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_MET_E2
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

namespace sec_met_algebra
{

///
/// Lower vector (pre-allocated version).
///
SHEAF_DLL_SPEC void lower(const sec_met_e2& xmetric, const sec_e2& xvector, sec_e2& xresult,
			  bool xauto_access);

///
/// Raise covector (pre-allocated version).
///
SHEAF_DLL_SPEC void raise(const sec_met_e2& xmetric, const sec_e2& xvector, sec_e2& xresult,
			  bool xauto_access);

} // namespace sec_met_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_MET_E2_H


