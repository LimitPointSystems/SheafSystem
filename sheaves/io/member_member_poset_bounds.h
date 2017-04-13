
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

// Interface for class member_member_poset_bounds

#ifndef MEMBER_MEMBER_POSET_BOUNDS_H
#define MEMBER_MEMBER_POSET_BOUNDS_H

#ifndef POSET_BOUNDS_H
#include "SheafSystem/poset_bounds.h"
#endif

class zn_to_bool;
namespace sheaf
{
  
///
/// A poset bounds pair with lower and upper bounds
/// each specified by a single member.
///
class member_member_poset_bounds : public poset_bounds
{

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; private to prevent default construction.
  ///
  ///
  member_member_poset_bounds();

  ///
  /// Copy constructor
  ///
  ///
  member_member_poset_bounds(const member_member_poset_bounds& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual member_member_poset_bounds* clone() const;

  ///
  /// Destructor
  ///
  virtual ~member_member_poset_bounds();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // POSET_BOUNDS FACET

  ///
  /// True if the lower bound contains the member with index xindex.
  ///
  virtual bool lb_contains_member(const scoped_index& xindex);

  ///
  /// An iterator for the members of the lower bound.
  ///
  virtual index_iterator lb_iterator();

  ///
  /// True if the upper bound contains the member with index xindex.
  ///
  virtual bool ub_contains_member(const scoped_index& xindex);

  ///
  /// An iterator for the members of the upper bound.
  ///
  virtual index_iterator ub_iterator();

  ///
  /// True if lb() and ub() are attached.
  ///
  bool is_attached();

  ///
  /// Attaches the lower and upper bounds.
  ///
  virtual void attach_to_state(poset_state_handle* xhost);

  ///
  /// Detaches the lower and upper bounds.
  ///
  virtual void detach_from_state();

  ///
  /// A descriptor for this.
  ///
  virtual poset_bounds_descriptor descriptor();

  // MEMBER_MEMBER_POSET_BOUNDS FACET

  ///
  /// Constructs bounds with lower bound
  /// the singleton subposet specified by the member with
  /// index xlb_id and upper bound the singleton subposet
  /// specified by the member with index xub_id.
  ///
  member_member_poset_bounds(int xlb_id, int xub_id);


protected:

private:

  ///
  /// The membership of the lower bound.
  ///
  zn_to_bool* _lb;

  ///
  /// The membership of the upper bound.
  ///
  zn_to_bool* _ub;

};
  
} // namespace sheaf



#endif // ifndef MEMBER_MEMBER_POSET_BOUNDS_H






