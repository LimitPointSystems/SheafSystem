
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

// Interface for class index_iterator

#ifndef INDEX_ITERATOR_H
#define INDEX_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

namespace sheaf
{

class zn_to_bool; 

///
/// Iterates over the subset of Zn defined by the characteristic function host().
///
class SHEAF_DLL_SPEC index_iterator
{

public:

  ///
  ///  Creates an instance with host() == 0.
  ///
  index_iterator();

  ///
  /// Create an instance with host() == xhost and index.scope() == xid_space;
  /// if xdelete_host, delete host() when this is deleted.
  ///
  index_iterator(const zn_to_bool* xhost, const index_space_handle& xid_space, bool xdelete_host = false);

  ///
  /// Destructor; not virtual so this class
  /// should not be used as a base class.
  ///
  virtual ~index_iterator();

  ///
  /// The subset this is iterating over.
  ///
  const zn_to_bool* host() const;

  ///
  ///  OBSOLETE: use index(). The current item in the subset.
  ///
  int item();

  ///
  ///  The current item in the subset.
  ///
  const scoped_index& index() const;

  ///
  ///  True if iteration finished
  ///
  bool is_done() const;

  ///
  ///  True if iteration finished after next call to next()
  ///
  bool is_last() const;

  ///
  ///  Makes item the next member of the subset
  ///
  void next();

  ///
  ///  Restarts the iteration, makes item the first member of the subset
  ///
  void reset();

  ///
  ///  Restarts the iteration on host xhost
  ///
  virtual void reset(const zn_to_bool* xhost, const index_space_handle& xid_space, bool xdelete_host = false);

protected:

  ///
  /// The subset this is iterating over.
  ///
  const zn_to_bool* _host;

  ///
  /// True if _host should be deleted when this is deleted.
  ///
  bool _delete_host;

  ///
  /// The index of the word containing the current bit.
  ///
  int _word_index;

  ///
  /// The upper bound for the word index.
  ///
  int _word_ub;

  ///
  /// The current word.
  ///
  unsigned int _word;

  ///
  /// The index of the current bit.
  ///
  int _bit_index;

  ///
  /// The upper bound on the bit index.
  ///
  int _bit_ub;

  ///
  /// The current item in the iteration.
  ///
  int _item;

  ///
  /// The next item in the iteration.
  ///
  int _next_item;

  ///
  /// The upper bound in item.
  ///
  int _item_ub;

  ///
  /// Finds the next item in the iteration.
  ///
  void find_next_item();

  ///
  /// The current index in the iteration.
  ///
  mutable scoped_index _index;
};
 
} // namespace sheaf

#endif // ifndef INDEX_ITERATOR_H
