
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
/// Interface for class jcb_ed

#ifndef JCB_ED_H
#define JCB_ED_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef JCB_H
#include "SheafSystem/jcb.h"
#endif

namespace fiber_bundle
{
  class ed;

//==============================================================================
// CLASS JDB_ED_LITE
//==============================================================================

///
/// Abstract jacobian for d dimensional Euclidean space
/// (volatile version).
///
class SHEAF_DLL_SPEC jcb_ed_lite : public jcb_lite
{
  //============================================================================
  /// @name JCB_ED FACET OF CLASS JCB_ED_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  jcb_ed_lite();

  ///
  /// Copy constructor.
  ///
  jcb_ed_lite(const jcb_ed_lite& xother);

  ///
  /// Assignment operator.
  ///
  jcb_ed_lite& operator=(const jcb_ed_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~jcb_ed_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  jcb_ed_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  jcb_ed_lite& operator=(const row_dofs_type& xrow_dofs);

protected:
private:

  //@}


  //============================================================================
  /// @name JACOBEAN (JCB) FACET OF CLASS JCB_ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS JCB_ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS JCB_ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB_ED_LITE
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
  virtual jcb_ed_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS JCB_ED_LITE
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
// CLASS JDB_ED
//==============================================================================

///
/// Abstract jacobian for d dimensional Euclidean space
/// (persistent version).
///

class SHEAF_DLL_SPEC jcb_ed : public jcb
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS JCB
  // ===========================================================
  //@{

public:

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
  /// and table attributes domain_path, range_path, and scalar_space_path specified by
  /// xdomain_path and xrange_path, respectively.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path,
			     const poset_path& xdomain_path,
			     const poset_path& xrange_path,
			     bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name JCB_ED FACET OF CLASS JCB_ED
  //============================================================================
  //@{

public:

  ///
  /// The type of domain vector space.
  ///
  typedef ed domain_type;

  ///
  /// The type of range vector space.
  ///
  typedef ed range_type;

  ///
  /// The associated volatile type.
  ///
  typedef jcb_ed_lite volatile_type;

  ///
  /// Default constructor.
  ///
  jcb_ed();

  ///
  /// Creates a new jcb_edhandle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  jcb_ed(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new jcb_ed handle attached to the member state with id xid
  /// in xhost.
  ///
  jcb_ed(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new jcb_ed handle attached to the member state with name xname
  /// in xhost.
  ///
  jcb_ed(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new jcb_ed handle attached to the same state as xother.
  ///
  explicit jcb_ed(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  jcb_ed(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual jcb_ed& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  jcb_ed& operator=(const jcb_ed& xother);

  ///
  /// Destructor.
  ///
  ~jcb_ed();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;


  //============================================================================
  /// @name VD FACET OF CLASS JCB_ED
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS JCB_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB_ED
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
  virtual jcb_ed* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline jcb_ed* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<jcb_ed*>(jcb::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS JCB_ED
  //============================================================================
  //@{

public:

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

#endif // ifndef JCB_ED_H
