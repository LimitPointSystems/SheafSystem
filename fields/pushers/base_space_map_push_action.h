// $RCSfile: base_space_map_push_action.h,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:26 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class base_space_map_push_action

#ifndef BASE_SPACE_MAP_PUSH_ACTION_H
#define BASE_SPACE_MAP_PUSH_ACTION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef PULLBACK_MAP_H
#include "pullback_map.h"
#endif

namespace sheaf
{
template <typename T>
class block;
}

namespace fiber_bundle
{
class sec_vd;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;
 
///
/// Abstract functor to compute the dofs at a destination discretization point.
///
class SHEAF_DLL_SPEC base_space_map_push_action : public any
{

  // =============================================================================
  /// @name BASE_SPACE_MAP_PUSH_ACTION FACET
  // =============================================================================
  //@{

public:

  ///
  /// Destructor.
  ///
  virtual ~base_space_map_push_action();

  ///
  /// Computes xout_dofs using xitr and the dofs already in xoutputs, as needed.
  ///
  virtual void operator()(pullback_map::iterator& xitr,
                          block<sec_vd*>& xoutputs,
                          block< block<sec_vd_dof_type>* >& xout_dofs) = 0;

  ///
  /// Initializes outputs as needed.
  ///
  virtual void initialize(block<sec_vd*>& xoutputs);

  ///
  /// Finalizes outputs as needed.
  ///
  virtual void finalize(block<sec_vd*>& xoutputs);


protected:

  ///
  /// Default constructor.
  ///
  base_space_map_push_action();

  // Copy constructor; default memberwise copy constructor will do.

  //@}


  // =============================================================================
  /// @name ANY FACET
  // =============================================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual base_space_map_push_action* clone() const = 0;

  ///
  /// Assignment operator
  ///
  virtual base_space_map_push_action& operator=(const base_space_map_push_action& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
 
} // namespace fields

#endif // ifndef BASE_SPACE_MAP_PUSH_ACTION_H
