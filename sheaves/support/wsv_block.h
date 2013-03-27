// $RCSfile: wsv_block.h,v $ $Revision: 1.18 $ $Date: 2013/01/22 16:38:26 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class wsv_block

#ifndef WSV_BLOCK_H
#define WSV_BLOCK_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
  
///
/// Whitespace-separated-value block; A block of objects of type T
/// that can be conveniently initialized by a whitespace-separated list.
///
template <typename T>
class SHEAF_DLL_SPEC wsv_block : public block<T>
{

public:

  ///
  /// Default constructor
  ///
  ///
  wsv_block();

  ///
  /// Copy constructor
  ///
  ///
  wsv_block(const wsv_block& xother);

  ///
  /// Destructor
  ///
  ~wsv_block();

  ///
  /// Creates an instance initialized from whitespace-separated list xlist.
  ///
  wsv_block(const char* xlist);

  ///
  /// Creates an instance initialized from whitespace-separated list xlist.
  ///
  wsv_block(const string& xlist);

  using block<T>::operator=;

  ///
  /// Sets the contents of this to the contents of
  /// whitespace-separated list xlist.
  ///
  wsv_block& operator=(const wsv_block& xother);

  ///
  /// Sets the contents of this to the contents of
  /// whitespace-separated list xlist.
  ///
  wsv_block& operator=(const string& xlist);

  ///
  /// Sets the contents of this to the contents of
  /// whitespace-separated list xlist.
  ///
  wsv_block& operator=(const char* xlist);

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  using block<T>::push_back;

  ///
  /// Appends xother to the back of this.
  ///
  void push_back(const wsv_block& xother);

};


//=============================================================================
// MEMBER FUNCTION SPECIALIZATIONS
//=============================================================================

// Specialization for T == bool:

//$$SCRIBBLE: This specialization requires that all lower
//            case is used in xlist; eg: "true false" as
//            opposed to  "TRUE FALSE"". This limitation
//            could be eliminated with a "bool to_bool(string)"
//            function.

template <>
SHEAF_DLL_SPEC
wsv_block<bool>&
wsv_block<bool>::
operator=(const string& xlist);

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // namespace sheaf

#endif // ifndef WSV_BLOCK_H
