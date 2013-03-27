// $RCSfile: dof_descriptor_array.h,v $ $Revision: 1.23 $ $Date: 2013/01/12 17:17:34 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface and implementation for class dof_descriptor_array
/// Crude implementation of reference count array for
/// descriptor of each dof from beginning of dof tuple
/// (There is no file dof_descriptor_array.cc)

#ifndef DOF_DESCRIPTOR_ARRAY_H
#define DOF_DESCRIPTOR_ARRAY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_IOMANIP_H
#include "std_iomanip.h"
#endif

namespace sheaf
{
  
///
/// An array for storing structs which describe the size, alignment,
/// and offset of dofs within a dof tuple.
///
class SHEAF_DLL_SPEC dof_descriptor_array
{

public:

  ///
  /// Basic description of a dof
  ///
  class dof_descriptor
  {
  public:
    size_t size; // size of dof
    size_t alignment; // alignment of dof
    int type;  // primitive type index
    size_t offset; // offset from beginning of dof tuple
  };

  ///
  /// Create array for descriptors of xdof_dofs
  ///
  dof_descriptor_array(size_type xdof_ct);

  ///
  /// Destructor
  ///
  ~dof_descriptor_array();

  ///
  /// Value of xid-th element.
  ///
  virtual dof_descriptor& operator[](int xid) const;

  ///
  /// Add a reference to this.
  ///
  void add_reference();

  ///
  /// Remove a reference from this.
  ///
  void remove_reference();

  ///
  /// The upper bound on the array index; the number of descriptors.
  /// Note that this is not the number of dofs described in this array.
  ///
  size_type ub() const;

  ///
  /// The number of dofs described in this.
  ///
  size_type dof_ct() const;

  ///
  /// The number of bytes in the dof tuple described by this.
  ///
  size_type size() const;

private:

  ///
  /// Number of references to this
  ///
  size_type _ref_ct;

  ///
  /// dof descriptors
  ///
  dof_descriptor* _descriptors;

  ///
  /// The upper bound on the array index; the number of descriptors.
  ///
  size_type _ub;

  ///
  /// Default constructor; disabled.
  ///
  dof_descriptor_array() {};

  ///
  /// Copy constructor; disabled.
  ///
  dof_descriptor_array(const dof_descriptor_array& xother) {};

  ///
  /// Assignment operator; disabled.
  ///
  dof_descriptor_array& operator=(const dof_descriptor_array& xother)
  {
    // Must return something to keep compiler happy.

    return *this;
  };

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert dof_descriptor_array& p into ostream& os.
///
SHEAF_DLL_SPEC
ostream& operator << (ostream &os, const dof_descriptor_array& p);

///
/// Insert dof_descriptor_array::dof_descriptor& p into ostream& os.
///
SHEAF_DLL_SPEC
ostream& operator << (ostream &os, const dof_descriptor_array::dof_descriptor& p);

///
/// The deep size of the referenced object of type dof_descriptor_array.
///
SHEAF_DLL_SPEC
size_t deep_size(const dof_descriptor_array& xp, bool xinclude_shallow = true);
 
} // namespace sheaf

#endif // ifndef DOF_DESCRIPTOR_ARRAY_H
