// $RCSfile: equivalence_relation.inst.cc,v $ $Revision: 1.4 $ $Date: 2013/01/12 17:17:49 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class equivalence_relation.

#include "equivalence_relation.impl.h"

using namespace sheaf; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::equivalence_relation<int>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
ostream&
sheaf::operator<< <int>(ostream& xos,
                        const sheaf::equivalence_relation<int>& xer);

template
SHEAF_DLL_SPEC
ostream&
sheaf::operator<< <int>(ostream& xos,
           const sheaf::equivalence_relation<int>::range_type& xrange);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
