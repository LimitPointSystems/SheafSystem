// $RCSfile: poset_member_iterator.h,v $ $Revision: 1.16 $ $Date: 2013/03/13 00:59:05 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class poset_member_iterator

#ifndef POSET_MEMBER_ITERATOR_H
#define POSET_MEMBER_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TOTAL_POSET_MEMBER_H
#include "total_poset_member.h"
#endif

namespace sheaf
{
  
///
/// @deprecated. No replacement.
/// Iterator over members of a subposet
///
class SHEAF_DLL_SPEC poset_member_iterator : public total_poset_member
{
public:

  

  ///
  /// True if iteration finished
  ///
  virtual bool is_done() const = 0;

  ///
  /// Makes this the next member of the subset
  ///
  virtual void next() = 0;

  ///
  /// Restarts the iteration, makes this the first member of subposet()
  ///
  virtual void reset() = 0;
};
  
} // namespace sheaf

#endif // ifndef POSET_MEMBER_ITERATOR_H
