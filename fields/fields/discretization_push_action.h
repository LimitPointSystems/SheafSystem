
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class discretization_push_action

#ifndef DISCRETIZATION_PUSH_ACTION_H
#define DISCRETIZATION_PUSH_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELDS_H
#include "fields.h"
#endif

namespace fields
{

///
/// The action to executed by discretization_pusher::push
/// on each member of a discretization subposet.
///
class SHEAF_DLL_SPEC discretization_push_action
{

  // ===========================================================
  /// @name DISCRETIZATION_PUSH_ACTION FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor
  ///
  virtual ~discretization_push_action();

  ///
  /// The push action.
  ///
  virtual void operator () (const scoped_index& xmbr_id,
                            block<sec_vd_value_type>& xglobal_coords) = 0;

protected:

  ///
  /// Default constructor
  ///
  discretization_push_action();


private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef DISCRETIZATION_PUSH_ACTION_H
