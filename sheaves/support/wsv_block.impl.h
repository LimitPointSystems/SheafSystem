
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Interface for class wsv_block

#ifndef WSV_BLOCK_IMPL_H
#define WSV_BLOCK_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef WSV_BLOCK_H
#include "wsv_block.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef BLOCK_H
#include "block_impl.h"
#endif

#ifndef STD_CSTRING_H
#include "std_cstring.h"
#endif

#ifndef STD_SSTREAM_H
#include "std_sstream.h"
#endif

namespace sheaf
{
  
template <typename T>
wsv_block<T>::
wsv_block()
{
  // Preconditions:

  // None.

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(this->ub() == 0);

  // Exit:

  return;
};

template <typename T>
wsv_block<T>::
wsv_block(const wsv_block& xother)
    : block<T>(xother)
{
  // Preconditions:

  require(precondition_of(block_xother));

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(block(xother)));

  // Exit:

  return;
};


template <typename T>
wsv_block<T>::
~wsv_block()
{}
;

template <typename T>
wsv_block<T>::
wsv_block(const char* xlist)
{
  // Preconditions:


  // Body:

  *this = xlist;

  // Postconditions:

  ensure(strlen(xlist) > 0 ? this->ct() > 0 : true);

  // Exit:

  return;
};

template <typename T>
wsv_block<T>::
wsv_block(const string& xlist)
{
  // Preconditions:


  // Body:

  *this = xlist;

  // Postconditions:

  ensure(!xlist.empty() ? this->ct() > 0 : true);

  // Exit:

  return;
};

template <typename T>
wsv_block<T>&
wsv_block<T>::
operator=(const wsv_block& xother)
{
  // Preconditions:


  // Body:

  block<T>::operator=(xother);

  // Postconditions:


  // Exit:

  return *this;
};

template <typename T>
wsv_block<T>&
wsv_block<T>::
operator=(const string& xlist)
{
  // Preconditions:

  // Body:

  stringstream lval_stream;
  lval_stream.str(xlist);

  T lval;
  while(lval_stream >> lval)
  {
    push_back(lval);
  }


  // Postconditions:

  ensure(!xlist.empty() ? this->ct() > 0 : true);

  // Exit:

  return *this;
};

template <typename T>
wsv_block<T>&
wsv_block<T>::
operator=(const char* xlist)
{
  // Preconditions:


  // Body:

  this->operator=(string(xlist));

  // Postconditions:

  ensure(strlen(xlist) > 0 ? this->ct() > 0 : true);

  // Exit:

  return *this;
};

template <typename T>
bool
wsv_block<T>::
invariant() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  bool result = block<T>::invariant();

  // Return:

  return result;
}

template <typename T>
void
wsv_block<T>::
push_back(const wsv_block& xother)
{
  // Preconditions:

  // Body:

  define_old_variable(int old_ct = this->ct());


  for(int i=0; i<xother.ct(); ++i)
  {
    push_back(xother[i]);
  }

  // Postconditions:

  ensure(this->ct() == old_ct + xother.ct());
  ensure_for_all(i, 0, xother.ct(), ((*this)[i + old_ct] == xother[i]) );

  // Exit:

  return;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================


} //namespace sheaf

#endif // ifndef WSV_BLOCK_IMPL_H
