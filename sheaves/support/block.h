
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

// Interface for class BLOCK

#ifndef BLOCK_H
#define BLOCK_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef AUTO_BLOCK_H
#include "auto_block.h"
#endif

namespace sheaf
{
  
///
/// An auto_block with a no-initialization initialization policy.
///
template <typename T>
class SHEAF_DLL_SPEC block : public auto_block<T, un_block_initialization_policy<T> >
{

public:

  typedef auto_block<T, un_block_initialization_policy<T> > base_type;

  typedef typename base_type::index_type index_type;
  typedef typename base_type::size_type size_type;


  ///
  /// Creates an instance with ub() == xub;
  /// storage is uninitialized.
  ///
  block(index_type xub = 0);

  ///
  /// Creates an instance with ub() == xub; storage is
  /// initialized with xct items copied from xitems
  ///
  block(index_type xub, size_type xct, const T *xitems);

  ///
  /// Copy constructor.
  ///
  block(const block& xother);

  ///
  /// Assignment operator.
  ///
  block& operator=(const block& xother);

  ///
  /// Destructor
  ///
  ~block();

};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Equality operator; true if xblk1 equals xblk2
///
template <typename T>
bool operator==(const block<T>& xblk1, const block<T>& xblk2);

///
/// Inserts block xblk into ostream xos.
///
template <typename T>
std::ostream& operator << (std::ostream& xos, const block<T>& xblk);

///
/// The deep size of the referenced object of type block@<T@>;
/// if xinclude_shallow, add the sizeof xp to the result.
///
template<typename T>
size_t deep_size(const block<T>& xblk, bool xinclude_shallow = true);

///
/// The deep size of the referenced object of type block@<T*@>;
/// if xinclude_shallow, add the sizeof xp to the result.
/// Note that the first argument is auto_block<T*, S> but the
/// template parameter is T, not T*.
///
template<typename T>
size_t deep_size(const block<T*>& xblk, bool xinclude_shallow = true);
 
} // namespace sheaf

#endif // BLOCK_H
