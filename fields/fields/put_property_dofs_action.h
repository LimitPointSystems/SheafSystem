// $RCSfile: put_property_dofs_action.h,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:22 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class put_property_dofs_action

#ifndef PUT_PROPERTY_DOFS_ACTION_H
#define PUT_PROPERTY_DOFS_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef DISCRETIZATION_PUSH_ACTION_H
#include "discretization_push_action.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

namespace fiber_bundle
{
class sec_vd;
}

namespace fields
{

///
/// An abstract discretization push action for field_vds::put_property_dofs.
///
class SHEAF_DLL_SPEC put_property_dofs_action : public discretization_push_action
{

  // ===========================================================
  /// @name PUT_PROPERTY_DOFS_ACTION FACET
  // ===========================================================
  //@{

public:

  // No default constructor.

  ///
  /// Creates an instance using property xproperty.
  ///
  put_property_dofs_action(sec_vd& xproperty, bool xauto_access);

  // Default memberwise copy constructor will do.

  ///
  /// Destructor
  ///
  virtual ~put_property_dofs_action();

  ///
  /// The property section being acted on.
  ///
  sec_vd& property();

protected:

  ///
  /// The property section being acted on.
  ///
  sec_vd& _property;

  ///
  /// Buffer for property dofs.
  ///
  block<sec_vd_dof_type> _dofs;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // namespace fields

#endif // ifndef PUT_PROPERTY_DOFS_ACTION_H
