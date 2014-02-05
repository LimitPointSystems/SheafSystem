
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

// Interface for class subposet_member_iterator

#ifndef SUBPOSET_MEMBER_ITERATOR_H
#define SUBPOSET_MEMBER_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_MEMBER_ITERATOR_H
#include "poset_member_iterator.h"
#endif

#ifndef INDEX_ITERATOR_H
#include "index_iterator.h"
#endif

namespace sheaf
{

class subposet;  

///
/// @deprecated No replacement.
/// Iterator over members of a subposet
///
class SHEAF_DLL_SPEC subposet_member_iterator : public poset_member_iterator
{

public:

  ///
  /// Creates an iterator for the members of xsubposet;
  /// makes this the first member.
  ///
  subposet_member_iterator(const subposet& xsubposet);

  ///
  /// Destroys this iterator
  ///
  ~subposet_member_iterator();

  ///
  /// The canonical class invariant.
  ///
  bool  invariant() const;

  ///
  /// True if iteration finished
  ///
  bool is_done() const;

  ///
  /// True if is_done() will be true after next call to next.
  ///
  bool is_last() const;

  ///
  /// Makes this the next member of the subset
  ///
  void next();

  ///
  /// Restarts the iteration, makes this the first member of domain() also belonging to domain()'s
  /// host()'s current version.
  ///
  void reset();

  ///
  /// Restarts the iteration, makes domain() == xsubposet,
  /// then makes item the first member of domain() also belonging to domain()'s
  /// host()'s current version.
  ///
  void reset(const subposet* xsubposet);

  ///
  /// The subposet being iterated over.  Note that only the members also belonging to the domain's
  /// host's current version are returned during the iteration.
  ///
  subposet* domain() const;

protected:

  ///
  /// Subposet being iterated over.
  ///
  subposet* _domain;

  ///
  /// Index iterator for characteristic function of domain.
  ///
  index_iterator _itr;

  ///
  /// The filter; defined by what it passes, not what it blocks,
  /// that is, the iterator will only return members which are also
  /// members of _filter.
  ///
  zn_to_bool* _filter;

  ///
  /// True if `this' allocated a new filter.
  ///
  bool _new_filter;

  ///
  /// Initialize the filter.
  ///
  void initialize_filter();

  ///
  /// Assignment operator
  ///
  virtual subposet_member_iterator& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  subposet_member_iterator& operator=(const subposet_member_iterator& xother);


};
  
} // namespace sheaf

#endif // ifndef SUBPOSET_MEMBER_ITERATOR_H
