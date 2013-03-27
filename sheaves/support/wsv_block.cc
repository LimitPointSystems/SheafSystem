// $RCSfile: wsv_block.cc,v $ $Revision: 1.19 $ $Date: 2013/01/12 17:17:47 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Instantiation for class template wsv_list

#include "wsv_block.impl.h"

using namespace sheaf; // workaround for MS C++ bug.


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
wsv_block<bool>&
wsv_block<bool>::
operator=(const string& xlist)
{
  // Preconditions:

  // Body:

  stringstream lval_stream;
  lval_stream.str(xlist);

  bool lval;
  while(lval_stream >> boolalpha >> lval)
  {
    push_back(lval);
  }

  // Postconditions:

  ensure(!xlist.empty() ? this->ct() > 0 : true);

  // Exit:

  return *this;
}

