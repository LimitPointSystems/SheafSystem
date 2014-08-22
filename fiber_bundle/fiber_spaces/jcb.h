
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
/// Interface for class jcb.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_JCB_H
#define COM_LIMITPOINT_FIBER_BUNDLE_JCB_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_VD_H
#include "ComLimitPoint/fiber_bundle/vd.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_JCB_TABLE_DOFS_TYPE_H
#include "ComLimitPoint/fiber_bundle/jcb_table_dofs_type.h"
#endif
 

namespace fiber_bundle
{
  //
  // Forward declarations
  //

  class at1;
  class jcb_space;

//==============================================================================
// CLASS JCB_LITE
//==============================================================================

///
/// Abstract jacobian class
/// (volatile version).
///
class SHEAF_DLL_SPEC jcb_lite : public vd_lite
{
  //============================================================================
  /// @name JACOBIAN (JCB) FACET OF CLASS JCB_LITE
  //============================================================================
  //@{

public:

  ///
  /// The type of the table dofs.
  ///
  typedef jcb_table_dofs_type table_dofs_type;

  ///
  /// Default constructor.
  ///
  jcb_lite();

  ///
  /// Copy constructor.
  ///
  jcb_lite(const jcb_lite& xother);

  ///
  /// Assignment operator.
  ///
  jcb_lite& operator=(const jcb_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~jcb_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  jcb_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  jcb_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Dimension of the domain.
  ///
  virtual int dd() const;

  ///
  ///  Dimension of the range.
  ///
  virtual int dr() const;

  ///
  /// The table dofs.
  ///
  table_dofs_type table_dofs() const;

  using vd_lite::component;
  using vd_lite::put_component;  

  ///
  /// The value of the component in a specified row and column
  /// (const version).
  ///
  value_type component(int xrow, int xcolumn) const;

  ///
  /// Sets value of a component in a specified row and column.
  ///
  void put_component(int xrow, int xcolumn, value_type xcomp);

  ///
  /// The index into linear storage of the component
  /// in a specified row and column.
  ///
  virtual int index_for_row_column(int xrow, int xcolumn) const;

protected:
private:

  //@}


  //============================================================================
  /// @name VECTOR ALGEBRA (VD) FACET OF CLASS JCB_LITE
  //============================================================================
  //@{

public:

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

protected:
private:

  //@}


  //============================================================================
  /// @name CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS JCB_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB_LITE
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
  virtual jcb_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS JCB_LITE
  //============================================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any_lite& xother) const;

  ///
  ///
  /// Class invariant.
  ///
  bool invariant() const;

protected:
private:

  //@}
};


//==============================================================================
// CLASS JCB
//==============================================================================

///
/// Abstract jacobian class.
///
class SHEAF_DLL_SPEC jcb : public vd
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS JCB
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef jcb_space host_type;

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
  /// @name JCB FACET OF CLASS JCB
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of domain vector space.
  ///
  typedef at1 domain_type;

//   ///
//   /// The type of vector space; synonym for domain_type.
//   /// @hack Just to make jcb consistent with namespace 
//   /// factory queries designed for tensor spaces.
//   ///
//   typedef domain_type vector_space_type;

  ///
  /// The type of range vector space.
  ///
  typedef at1 range_type;

  ///
  /// The associated volatile type.
  ///
  typedef jcb_lite volatile_type;

  ///
  ///  The type of the table dofs.
  ///
  typedef jcb_table_dofs_type table_dofs_type;

  ///
  /// Default constructor.
  ///
  jcb();

  ///
  /// Creates a new jcb handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  jcb(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new jcb handle attached to the member state with id xid
  /// in xhost.
  ///
  jcb(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new jcb handle attached to the member state with name xname
  /// in xhost.
  ///
  jcb(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new jcb handle attached to the same state as xother.
  ///
  explicit jcb(abstract_poset_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  jcb(poset_state_handle* xhost, bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual jcb& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  jcb& operator=(const jcb& xother);

  ///
  /// Destructor.
  ///
  ~jcb();

  ///
  /// Virtual constructor for the associated volatile type.
  ///
  virtual const volatile_type& lite_prototype() const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;

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

  ///
  /// The index into linear storage of the component
  /// in a specified row and column.
  ///
  virtual int index_for_row_column(int xrow, int xcolumn) const;

protected:
private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS JCB
  //============================================================================
  //@{

public:

  using vd::component;
  using vd::put_component;

  ///
  /// The component with row index xrow and column index xcolumn.
  ///
  value_type component(int xrow, int xcolumn) const;

  ///
  /// The component with row index xrow and column index xcolumn.
  ///
  value_type component(int xrow, int xcolumn, bool xauto_access) const;

  ///
  /// Sets the component with row index xrow and column index xcolumn to xvalue.
  ///
  void put_component(int xrow, int xcolumn, value_type xvalue);

  ///
  /// Sets the component with row index xrow and column index xcolumn to xvalue.
  ///
  void put_component(int xrow, int xcolumn, value_type xvalue, bool xauto_access);

protected:
private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS JCB
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS JCB
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
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline jcb* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<jcb*>(vd::clone(xnew_state, xauto_access));
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
  /// @name ANY FACET OF CLASS JCB
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to current.
  ///
  bool is_ancestor_of(const any* xother) const;

  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual jcb* clone() const; // = 0;

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

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert jcb_lite::table_dofs_type& xt into ostream& xos.
///
SHEAF_DLL_SPEC std::ostream& operator<<(std::ostream& xos, jcb_lite::table_dofs_type& xt);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

class at1;
class at1_lite;

//==============================================================================
// JCB FACET:
//==============================================================================

///
/// Namespace containing the Jacobian algrebra functions for the 
/// fiber_bundles component of the sheaf system.
///
namespace jcb_algebra
{

#ifndef DOXYGEN_SKIP_UNKNOWN

///
/// Push vector forward (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void push(const jcb& xjcb,
			 const at1& xvector,
			 at1& xresult,
			 bool xauto_access);

///
/// Push vector forward (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void push(const jcb_lite& xjcb,
			 const at1_lite& xvector,
			 at1_lite& xresult);

///
/// Push vector forward (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC at1_lite* push(const jcb_lite& xjcb, const at1_lite& xvector);

#endif // ifndef DOXYGEN_SKIP_UNKNOWN

//==============================================================================

///
/// Pull covector back (pre-allocated version for persistent types).
///
SHEAF_DLL_SPEC void pull(const jcb& xjcb,
			 const at1& xcovector,
			 at1& xresult,
			 bool xauto_access);

///
/// Pull covector back (pre-allocated version for volatile types).
///
SHEAF_DLL_SPEC void pull(const jcb_lite& xjcb,
			 const at1_lite& xcovector,
			 at1_lite& xresult);

///
/// Pull covector back (auto-allocated version for volatile types).
///
SHEAF_DLL_SPEC at1_lite* pull(const jcb_lite& xjcb, const at1_lite& xvector);
  
} // namespace jcb_algebra

} // namespace fiber_bundle


#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_JCB_H
