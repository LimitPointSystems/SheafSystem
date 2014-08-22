
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
/// Interface for class met_ed.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_MET_ED_H
#define COM_LIMITPOINT_FIBER_BUNDLE_MET_ED_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_MET_H
#include "ComLimitPoint/fiber_bundle/met.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS MET_ED_LITE
//==============================================================================

///
/// A metric tensor over a d-dimensional Euclidean vector space
/// (volatile version).
///
class SHEAF_DLL_SPEC met_ed_lite : public met_lite
{
  //============================================================================
  /// @name EUCLIDEAN METRIC (MET_ED) FACET OF CLASS MET_ED_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  met_ed_lite();

  ///
  /// Copy constructor.
  ///
  met_ed_lite(const met_ed_lite& xother);

  ///
  /// Assignment operator.
  ///
  met_ed_lite& operator=(const met_ed_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~met_ed_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  met_ed_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  met_ed_lite& operator=(const row_dofs_type& xrow_dofs);

protected:
private:

  //@}


  //============================================================================
  /// @name METRIC TENSOR (MET) FACET OF CLASS MET_ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS MET_ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS MET_ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS MET_ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS MET_ED_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS MET_ED_LITE
  //============================================================================
  //@{

public:

  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS MET_ED_LITE
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
  virtual met_ed_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS MET_ED_LITE
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
// CLASS MET_ED
//==============================================================================

///
/// A metric tensor over a d-dimensional Euclidean vector space
/// (persistent version).
///
class SHEAF_DLL_SPEC met_ed : public met
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS MET_ED
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
  /// @name MET_ED FACET OF CLASS MET_ED
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef met_ed_lite volatile_type;

  ///
  /// Default constructor.
  ///
  met_ed();

  ///
  /// Creates a new met_ed handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  met_ed(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new met_ed handle attached to the member state with id xid
  /// in xhost.
  ///
  met_ed(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new met_ed handle attached to the member state with name xname
  /// in xhost.
  ///
  met_ed(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new met_ed handle attached to the same state as xother.
  ///
  explicit met_ed(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  met_ed(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual met_ed& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  met_ed& operator=(const met_ed& xother);

  ///
  /// Destructor.
  ///
  ~met_ed();

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
  /// @name MET FACET OF CLASS MET_ED
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS MET_ED
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name INTERIOR ALGEBRA (STP) FACET OF CLASS MET_ED
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name TENSOR ALGEBRA (TP) FACET OF CLASS MET_ED
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS MET_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS MET_ED
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
  virtual met_ed* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline met_ed* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<met_ed*>(met::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS MET_ED
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

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_MET_ED_H
