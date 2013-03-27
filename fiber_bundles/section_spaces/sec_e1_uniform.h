
// $RCSfile: sec_e1_uniform.h,v $ $Revision: 1.21 $ $Date: 2013/01/14 23:41:29 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_e1_uniform.

#ifndef SEC_E1_UNIFORM_H
#define SEC_E1_UNIFORM_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_E1_H
#include "sec_e1.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS SEC_E1_UNIFORM
//==============================================================================

///
/// A section of a fiber bundle with a 1-dimensional Euclidean
/// vector space fiber.
///
class SHEAF_DLL_SPEC sec_e1_uniform : public sec_e1
{
  //============================================================================
  /// @name SEC_E1_UNIFORM FACET OF CLASS SEC_E1_UNIFORM
  //============================================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef e1 fiber_type;


  ///
  /// Default constructor; creates an unattached handle.
  ///
  sec_e1_uniform();


  // ===========================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  // ===========================================================================

  //   ///
  ///  /// Create a new handle attached to a new state with in a new section space
  ///  /// with a new fiber space and new base with with name xbase_name
  ///  /// and size xbase_i_size. Section bounds are given by xmin_x and xmax_x.
  //   ///
  //   sec_e1_uniform(fiber_bundles_namespace& xns,
  //                  const string& xbase_name,
  //                  int xbase_i_size,
  //                  dof_type xmin_x,
  //                  dof_type xmax_x,
  //                  bool xauto_access);


  ///
  /// Create a new handle attached to a new state in xhost with
  /// min_x() == xmin_x and max_x() == xmax_x.
  ///
  sec_e1_uniform(sec_rep_space* xhost,
                 dof_type xmin_x,
                 dof_type xmax_x,
                 bool xauto_access);

  ///
  /// Creates a new handle attached to a new jim state in host xhost.
  ///
  sec_e1_uniform(sec_rep_space* xhost,
                 section_dof_map* xdof_map = 0,
                 bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_e1_uniform(sec_rep_space* xhost,
                 abstract_poset_member& xbase_mbr,
                 int xbase_version = CURRENT_HOST_VERSION,
                 bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jrm state which is
  /// a multi-section with a branch for each member of the base space
  /// contained in xbase_parts.
  ///
  sec_e1_uniform(sec_rep_space* xhost, const subposet& xbase_parts, bool xauto_sccess);

  // ===========================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  // ===========================================================================

  ///
  /// Creates a new sec_e1_uniform handle attached to the member state with
  /// index xindex in xhost.
  ///
  sec_e1_uniform(const sec_rep_space* xhost, pod_index_type xindex);

  ///
  /// Creates a new sec_e1_uniform handle attached to
  /// the member state with index xindex in xhost.
  ///
  sec_e1_uniform(const sec_rep_space* xhost, const scoped_index& xindex);

  ///
  /// Creates a new sec_e1_uniform handle attached to
  /// the member state with name xname in xhost.
  ///
  sec_e1_uniform(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_e1_uniform(const namespace_poset* xnamespace,
                 const poset_path& xpath,
                 bool xauto_access = true);

  ///
  /// Creates a new sec_e1_uniform handle attached to the same state as xother.
  ///
  explicit sec_e1_uniform(const sec_rep_space_member* xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_e1_uniform& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_e1_uniform& operator=(const sec_e1_uniform& xother);

  ///
  /// Assignment operator.
  ///
  sec_e1_uniform& operator=(const e1& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_e1_uniform& operator=(const e1_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_e1_uniform();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

  // ===========================================================================
  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"
  // ===========================================================================

  using sec_e1::new_jim_state;

  ///
  /// Attaches this to a new state in xhost with
  /// min_x() == xmin_x and max_x() == xmax_x.
  ///
  void new_jim_state(sec_rep_space* xhost,
                     dof_type xmin_x,
                     dof_type xmax_x,
                     bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name E1 FACET OF CLASS SEC_E1_UNIFORM
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ED FACET OF CLASS SEC_E1_UNIFORM
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name AT1 FACET OF CLASS SEC_E1_UNIFORM
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ATP FACET OF CLASS SEC_E1_UNIFORM
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_E1_UNIFORM
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_E1_UNIFORM
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_E1_UNIFORM
  //============================================================================
  //@{

public:

  ///
  /// The path to the standard rep for sections of this type.
  ///
  static const poset_path& standard_rep_path();

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_E1_UNIFORM
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
  /// Virtual constructor; makes a new instance of the same type as this.
  ///
  virtual sec_e1_uniform* clone() const;

  ///
  /// make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_e1_uniform* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_e1_uniform*>(sec_e1::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_E1_UNIFORM
  //============================================================================
  //@{

public:

  ///
  /// True if other conforms to current.
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


public:

  ///
  /// Sets the dofs to match the bounds xmin and xmax.
  ///
  void put_bounds(const block<dof_type>& xmin, const block<dof_type>& xmax, bool xauto_access);

  ///
  /// Sets the dofs to match the bounds xmin and xmax.
  ///
  void put_bounds(dof_type xmin, dof_type xmax, bool xauto_access);

  ///
  /// Gets the bounds.
  ///
  void get_bounds(block<dof_type>& xmin, block<dof_type>& xmax, bool xauto_access) const;

  ///
  /// The minimum value of the x component.
  ///
  dof_type min_x(bool xauto_access) const;

  ///
  /// The maximum value of the x component.
  ///
  dof_type max_x(bool xauto_access) const;

};

} // namespace fiber_bundle

#endif // ifndef SEC_E1_UNIFORM_H


