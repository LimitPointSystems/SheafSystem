// $RCSfile: name_multimap.cc,v $ $Revision: 1.24 $ $Date: 2013/01/12 17:17:40 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class name_multimap<index_type> is in name_multimap_impl.h

#include "name_multimap.impl.h"
#include "scoped_index.h"

/// @todo Remove.

// template <>
// SHEAF_DLL_SPEC
// bool
// sheaf::name_multimap<sheaf::scoped_index>::
// contains_entry(const entry_type& xentry) const
// {
//   // Preconditions:

//   require(!xentry.second.empty());

//   // Body:

//   bool result;

//   result = contains_name(xentry.second)
//            && (index(xentry.second) ==~ xentry.first);

//   // Postconditions:

//   // Exit:

//   return result;
// }
