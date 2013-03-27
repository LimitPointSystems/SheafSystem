// $RCSfile: discretization_pusher.h,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:20 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class discretization_pusher.

#ifndef DISCRETIZATION_PUSHER_H
#define DISCRETIZATION_PUSHER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

namespace fiber_bundle
{
class sec_vd;
class section_space_schema_member;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;
 

class discretization_push_action;

///
/// A push-forward operator for discretization subposets;
/// pushes members into the global coordinate space.
///
class SHEAF_DLL_SPEC discretization_pusher : public any
{

  // ===========================================================
  /// @name DISCRETIZATION_PUSHER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  discretization_pusher();

  // Default memberwise copy constructor will do.

  ///
  /// Destructor.
  ///
  virtual ~discretization_pusher();

  ///
  /// Pushes each member of the discretization of xsrc into the
  /// fiber space of xglobal_coord and then executes xpush_action.
  ///
  void push(const section_space_schema_member& xsrc,
            const sec_vd& xglobal_coord,
            discretization_push_action& xpush_action,
            bool xauto_access);

private:

  ///
  /// True if the global coordinates dofs must be gatherd.
  ///
  bool must_gather(
    const section_space_schema_member& xrange_schema,
    const section_space_schema_member& xglobal_coord_schema) const;

  ///
  /// True if the local coordinates of the source must be mapped to the
  /// local coordinates of the  global coordinates.
  ///
  bool must_map(
    const section_space_schema_member& xrange_schema,
    const section_space_schema_member& xglobal_coord_schema) const;

  ///
  /// True if the global coordinates section must be evaluated.
  ///
  bool must_evaluate(
    const section_space_schema_member& xrange_schema,
    const section_space_schema_member& xglobal_coord_schema) const;

  ///
  /// Computes the push for source discretization == global coordinates discretization.
  ///
  void push_gather_no_map_no_evaluate(const section_space_schema_member& xsrc,
                                      const sec_vd& xglobal_coord,
                                      discretization_push_action& xpush_action);

  ///
  /// Computes the push for source evaluation == global coordinates evaluation.
  ///
  void push_gather_no_map_evaluate(const section_space_schema_member& xsrc,
                                   const sec_vd& xglobal_coord,
                                   discretization_push_action& xpush_action);
  ///
  /// Computes the push for uniform global coordinates.
  ///
  void push_no_gather_map_evaluate(const section_space_schema_member& xsrc,
                                   const sec_vd& xglobal_coord,
                                   discretization_push_action& xpush_action);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

 
} // namespace fields

#endif // ifndef DISCRETIZATION_PUSHER_H
