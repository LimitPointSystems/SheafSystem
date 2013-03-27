// $RCSfile: tern.h,v $ $Revision: 1.13 $ $Date: 2013/01/12 17:17:47 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class tern

#ifndef TERN_H
#define TERN_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

namespace sheaf
{
  
///
/// A three state "bool". Does not provide the operations
/// of ternary logic and is intended for use mostly as a convenient,
/// three-way input argument.
/// Can not be used as a base class since it
/// does not have a virtual destructor.
///
class SHEAF_DLL_SPEC tern
{

public:

  // =============================================================================
  // TERN FACET
  // =============================================================================

  ///
  /// Default constructor.
  ///
  tern();

  ///
  /// Copy constructor.
  ///
  tern(const tern& xother);

  //   ///
  ///   /// Conversion from boolean.
  //   ///
  //   tern(const bool& xother);

  ///
  /// Destructor.
  ///
  ~tern();

  ///
  /// Assignment operator
  ///
  tern& operator=(const tern& xother);

  //   ///
  ///   /// Assignment operator
  //   ///
  //   tern& operator=(const bool& xother);

  ///
  /// Conversion to bool.
  ///
  operator bool() const;

  ///
  /// True if thi has value true.
  ///
  bool is_true() const;

  ///
  /// True if this has value false.
  ///
  bool is_false() const;

  ///
  /// True if this is neither true nor false.
  ///
  bool is_neither() const;

  ///
  /// The three possible values.
  ///
  enum state_type
  {
    TRUE, FALSE, NEITHER
  };

  ///
  /// Creates instance with state xstate.
  ///
  tern(state_type xstate);

private:

  ///
  /// The current state.
  ///
  state_type _state;



};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
 
} // namespace sheaf

#endif // ifndef TERN_H
