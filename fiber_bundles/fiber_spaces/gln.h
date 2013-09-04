

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class gln

#ifndef GLN_H
#define GLN_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef GROUP_H
#include "group.h"
#endif

#ifndef GLN_TABLE_DOFS_TYPE_H
#include "gln_table_dofs_type.h"
#endif

namespace fiber_bundle
{  
  //
  // Forward declarations
  //

  class at0;
  class at1;
  class gln_space;
  
//==============================================================================
// CLASS GLN_ROW_DOFS_TYPE
//==============================================================================
 
///
/// Row dofs type for class gln.
///
template <typename T>
class gln_row_dofs_type
{
public:

  ///
  /// The type of the dofs.
  ///
  typedef T dof_type;

  ///
  /// The type of the row dofs (type of this).
  ///
  typedef gln_row_dofs_type<T> row_dofs_type;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  ///
  /// Value of xindex-th component (row dof)
  /// (non const version).
  ///
  T& operator[] (int xindex);

  ///
  /// Value of xindex-th component (row dof)
  /// (const version)
  ///
  const T& operator[] (int xindex) const;

  ///
  /// Creates a new instance of the same type as this.
  ///
  row_dofs_type* clone() const;
};


//==============================================================================
// CLASS GLN_LITE
//==============================================================================


///
/// The mathematical group GL(n, R).
/// GL(n,R) is the group of general, invertible, linear transformations
/// on a vector space of dimension n over the reals R
/// (volatile version).
///
class SHEAF_DLL_SPEC gln_lite : public group_lite
{
  //============================================================================
  /// @name GLN FACET OF CLASS GLN_LITE
  //============================================================================
  //@{

public:

  ///
  /// The type of the degrees of freedom.
  ///
  typedef vd_dof_type dof_type;

  ///
  /// The type of component in the fiber;
  /// the scalar type in the fiber vector space.
  ///
  typedef vd_value_type value_type;

  ///
  /// The type of the table dofs.
  ///
  typedef gln_table_dofs_type table_dofs_type;

  ///
  ///  The type of the row dofs.
  ///
  typedef gln_row_dofs_type<double> row_dofs_type;

  ///
  /// Default constructor.
  ///
  gln_lite();

  ///
  /// Copy constructor.
  ///
  gln_lite(const gln_lite& xother);

  ///
  /// Assignment operator.
  ///
  gln_lite& operator=(const gln_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~gln_lite();

  ///
  /// Creates a new instance with row dofs xrow_dofs.
  ///
  gln_lite(const row_dofs_type& xrow_dofs);

  ///
  /// Assignment (from row_dofs_type) operator.
  ///
  gln_lite& operator=(const row_dofs_type& xrow_dofs);

  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  //virtual int n() const = 0;
  virtual int n() const;

  ///
  /// The dimension of the row dof components.
  ///
  virtual int d() const;

  ///
  /// The xindex-th component.
  ///
  value_type component(int xindex) const;

  ///
  /// Set the xindex-th component to xcomp.
  ///
  void put_component(int xindex, value_type xcomp);

  ///
  /// The values of all the components (preallocated version).
  ///
  void components(dof_type xcomps[], int xcomps_dimension) const;

  ///
  /// Set values of all the components to the values in xcomps.
  ///
  void put_components(const dof_type xcomps[], int xcomps_dimension);

  ///
  /// The value of the component corresponding to xindex
  /// (non const version).
  ///
  value_type& operator[] (int xindex);

  ///
  /// The value of the component corresponding to xindex
  /// (const version).
  ///
  const value_type& operator[] (int xindex) const;

protected:
private:

  //@}


  //============================================================================
  /// @name GROUP FACET OF CLASS GLN_LITE
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS GLN_LITE
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
  /// Virtual constructor, makes a new instance of the same type as this.
  ///
  virtual gln_lite* clone() const;

  ///
  /// The table dofs.
  ///
  table_dofs_type table_dofs() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS GLN_LITE
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
// CLASS GLN
//==============================================================================

///
/// The mathematical group GL(n, R).
/// GL(n,R) is the group of general, invertible, linear transformations
/// on a vector space of dimension n over the reals R.
///
class SHEAF_DLL_SPEC gln : public group
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS TP
  // ===========================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef gln_space host_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// Manual, shallow factory method; creates a new host table for members of this type.
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
  /// @name GLN FACET OF CLASS GLN
  //============================================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of the underlying vector space.
  ///
  typedef at1 vector_space_type;

  ///
  /// The type of the underlying scalar space.
  ///
  typedef at0 scalar_type;

  ///
  ///  The type of the table dofs.
  ///
  typedef gln_table_dofs_type table_dofs_type;

  ///
  ///  The type of the row dofs.
  ///
  typedef gln_row_dofs_type<double> row_dofs_type;

  ///
  /// The associated volatile type.
  ///
  typedef gln_lite volatile_type;

  ///
  /// The POD ("plain old data") type of scalar in the vector space of this.
  ///
  typedef vd_value_type value_type;

  ///
  /// The type of the degrees of freedom.
  /// Note that although dof_type == value_type in this implementation,
  /// in prinicple they are different roles and are not necessarily the same type.
  ///
  typedef vd_dof_type dof_type;

  ///
  /// Default constructor.
  ///
  gln();

  ///
  /// Copy constructor.
  ///
  gln(const gln& xother, bool xnew_jem);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual gln& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  gln& operator=(const gln& xother);

  ///
  /// Destructor.
  ///
  virtual ~gln();

  ///
  /// Creates a new handle attached to a new jim state in xhost.
  ///
  gln(poset* xhost, bool xauto_access = true);

  ///
  /// Creates a new handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  gln(const poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new handle attached to the member state with id
  /// xid in xhost.
  ///
  gln(const poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  gln(const poset* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the same state as xother.
  ///
  explicit gln(gln* xother);

  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  int n() const;

  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  int n(bool xauto_access) const;

  ///
  /// The path of the underlying scalar space.
  ///
  poset_path scalar_space_path() const;

  ///
  /// The path of the underlying scalar space, auto access version.
  ///
  poset_path scalar_space_path(bool xauto_access) const;

  ///
  /// The path of the underlying vector space.
  ///
  poset_path vector_space_path() const;

  ///
  /// The path of the underlying vector space, auto access version.
  ///
  poset_path vector_space_path(bool xauto_access) const;

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

  ///
  /// Dimension of this as a vector space; auto-access version.
  ///
  int d(bool xauto_access) const;

  ///
  /// The value of the xi-th component.
  ///
  virtual value_type component(int xindex) const;

  ///
  /// The value of the xi-th component.
  ///
  value_type component(int xindex, bool xauto_access) const;

  ///
  /// Sets the value of the xi-th component to xvalue.
  ///
  virtual void put_component(int xi, value_type xvalue);

  ///
  /// Sets the value of the xi-th component to xvalue.
  ///
  void put_component(int xindex, value_type xvalue, bool xauto_access);

  ///
  /// The values of all the components (pre-allocated version).
  ///
  void components(dof_type xcomps[], int xcomps_dimension) const;

  ///
  /// Sets values of all the components to the values in comps.
  ///
  void put_components(const dof_type xcomps[], int xcomps_dimension);

  ///
  /// The value of the row dof corresponding to xindex
  /// (non const version).
  ///
  dof_type& operator[] (int xindex);

  ///
  /// The value of the row dof corresponding to xindex.
  /// (const version)
  ///
  const dof_type& operator[] (int xindex) const;

  ///
  /// Virtual conversion to the associated volatile type.
  ///
  virtual volatile_type* lite_type() const;


protected:
private:

  //@}


  //============================================================================
  /// @name GROUP FACET OF CLASS GLN
  //============================================================================
  //@{

public:
protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS GLN
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
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline gln* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<gln*>(group::clone(xnew_state, xauto_access));
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


  //===========================================================================
  /// @name ANY FACET OF CLASS GLN
  //===========================================================================
  //@{

public:

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;
  
  ///
  /// Make a new handle, no state instance of current.
  ///
  virtual gln* clone() const;  

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

protected:
private:

  //@}
};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// Converts degress to radians.
/// Convenience function for use with rotation routines.
///
SHEAF_DLL_SPEC double rad(double degrees);

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Insert gln_lite& xv into ostream& xos.
///
SHEAF_DLL_SPEC ostream& operator<<(ostream& xos, gln_lite& xv);

///
/// Insert gln_lite::table_dofs_type& xt into ostream& xos.
///
SHEAF_DLL_SPEC ostream& operator<<(ostream& xos, gln_lite::table_dofs_type& xt);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace fiber_bundle

#endif // ifndef GLN_H






