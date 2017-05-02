
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
/// Interface for class met.

#ifndef MET_H
#define MET_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ST2_H
#include "SheafSystem/st2.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS MET_LITE
//==============================================================================

///
/// A metric tensor over an abstract vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC met_lite : public st2_lite
{
  //============================================================================
  /// @name METRIC TENSOR (MET) FACET OF CLASS MET_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  met_lite();

  ///
  /// Copy constructor.
  ///
  met_lite(const met_lite& xother);

  ///
  /// Assignment operator.
  ///
  met_lite& operator=(const met_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~met_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  met_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  met_lite& operator=(const row_dofs_type& xrow_dofs);

protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS MET_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS MET_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS MET_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS MET_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS MET_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS MET_LITE
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
  /// Virtual constructor, makes a new instance of the same type as this.
  ///
  virtual met_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS MET_LITE
  //============================================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any_lite& xother) const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;

protected:
private:

  //@}
};


//==============================================================================
// CLASS MET
//==============================================================================

///
/// A metric tensor over an abstract vector space
/// (persistent version).
///
class SHEAF_DLL_SPEC met : public st2
{

  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef stp_space host_type;

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

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
  /// @name MET FACET OF CLASS MET
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef met_lite volatile_type;

  ///
  /// Default constructor.
  ///
  met();

  ///
  /// Creates a new met handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  met(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new met handle attached to the member state with id xid
  /// in xhost.
  ///
  met(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new met handle attached to the member state with name xname
  /// in xhost.
  ///
  met(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new met handle attached to the same state as xother.
  ///
  explicit met(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  met(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual met& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  met& operator=(const met& xother);

  ///
  /// Destructor.
  ///
  ~met();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;


protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS MET
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS MET
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS MET
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS MET
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS MET
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS MET
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
  virtual met* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline met* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<met*>(st2::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS MET
  //============================================================================
  //@{

public:

  ///
  /// True if other conforms to current.
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

class ed;
class ed_lite;

///
/// Namespace containing the metric tensor algrebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace met_algebra
{

///
/// Raise covector (pre-allocated version for persistent type).
///
SHEAF_DLL_SPEC void raise(const met& xmetric, const ed& xcovector, ed& xresult,
			  bool xauto_access);

///
/// Lower vector (pre-allocated version for persistent type).
///
SHEAF_DLL_SPEC void lower(const met& xmetric, const ed& xvector, ed& xresult,
			  bool xauto_access);

///
/// Raise covector (pre-allocated version for volatile type).
///
SHEAF_DLL_SPEC void raise(const met_lite& xmetric, const ed_lite& xcovector, ed_lite& xresult);

///
/// Raise covector (auto-allocated version for volatile type).
///
SHEAF_DLL_SPEC ed_lite* raise(const met_lite& xmetric, const ed_lite& xcovector);

///
/// Lower vector (pre-allocated version for volatile type).
///
SHEAF_DLL_SPEC void lower(const met_lite& xmetric, const ed_lite& xvector, ed_lite& xresult);

///
/// Lower vector (auto-allocated version for volatile type).
///
SHEAF_DLL_SPEC ed_lite* lower(const met_lite& xmetric, const ed_lite& xvector);

} // namespace met_algebra

} // namespace fiber_bundle

#endif // ifndef MET_H
