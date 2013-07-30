

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for class template block.

#ifndef BLOCK_IMPL_H
#define BLOCK_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef AUTO_BLOCK_IMPL_H
#include "auto_block.impl.h"
#endif

namespace sheaf
{
  
///
template <typename T>
block<T>::
block(index_type xub)
    : base_type::auto_block(xub)
{

  // Preconditions:

  require(precondition_of(auto_block(xub)));

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(auto_block(xub)));
}

///
template <typename T>
block<T>::
block(index_type xub, size_type xct, const T *xitems)
    : base_type::auto_block(xub, xct, xitems)
{

  // Preconditions:

  require(precondition_of(auto_block(xub, xct, xitems)));

  // Body:

  // Postconditions:

  ensure(postcondition_of(auto_block(xub, xct, xitems)));
}

///
template <typename T>
block<T>::
block(const block& xother)
    : base_type::auto_block(xother)
{

  // Preconditions:

  require(precondition_of(auto_block(xother)));

  // Body:

  // Postconditions:

  ensure(postcondition_of(auto_block(xother)));
}

///
template <typename T>
block<T>&
block<T>::
operator=(const block& xother)
{

  // Preconditions:

  require(precondition_of(auto_block::operator=(xother)));

  // Body:

  base_type::operator=(xother);

  // Postconditions:

  ensure(postcondition_of(auto_block::operator=(xother)));

  // Return:

  return *this;
}

///
template <typename T>
block<T>::
~block()
{
  // Nothing to do.
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN
// $$SCRIBBLE doxygen v1.5.4 - Warning: no matching file member found for
// Appears to be trying to match
//     bool sheaf::operator==(const block< T > &xblk1, const block< T > &xblk2)
// but is finding
//     bool operator==(const block< T > &xblk1, const block< T > &xblk2)
// NOTE: it has no issue with the last deep_size function

template <typename T>
bool
operator==(const block<T>& xblk1, const block<T>& xblk2)
{
  bool result;

  // Preconditions:

  // Body:

  result = (xblk1.ub() >= xblk2.ub());
  result = result && (xblk1.ct() == xblk2.ct());

  for(sheaf::pod_index_type i=0; result && (i<xblk1.ct()); ++i)
  {
    result = (xblk1[i] == xblk2[i]);
  }

  // Postconditions:

  // Return:

  return result;
}

///
template <typename T>
ostream&
operator << (ostream& xos, const block<T>& xblk)
{
  for(long int i=0; i<xblk.ct(); ++i)
  {
    xos << "  " << xblk[i];
  }

  return xos;
}

///
template <typename T>
size_t
deep_size(const block<T>& xblk, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xblk) : 0;

  for(int i=0; i<xblk.ub(); ++i)
  {
    result += deep_size(xblk[i], true);
  }

  // Postconditions:

  ensure(result >= 0);

  return result;
}

#endif // DOXYGEN_1_5_4_SKIP_UNKNOWN

///
template <typename T>
size_t
deep_size(const block<T*>& xblk, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xblk) : 0;

  result += xblk.ub()*sizeof(T*);

  for(int i=0; i<xblk.ub(); ++i)
  {
    if(xblk[i] != 0)
    {
      result += deep_size(*xblk[i], true);
    }
  }

  // Postconditions:

  ensure(result >= 0);

  return result;
}

} // namespace sheaf

#endif // BLOCK_IMPL_H

