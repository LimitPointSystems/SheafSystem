
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

// Interface for class discretization_iterator


#ifndef DISCRETIZATION_ITERATOR_H
#define DISCRETIZATION_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef DEPTH_FIRST_ITERATOR_H
#include "SheafSystem/depth_first_iterator.h"
#endif

#ifndef SINGLY_LINKED_LIST_H
#include "SheafSystem/singly_linked_list.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;


class section_space_schema_member;
class sec_rep_descriptor;

///
/// Iterator over the discretization subposet associated
/// with a section_space_schema_member anchor.
///
class SHEAF_DLL_SPEC discretization_iterator : public depth_first_iterator
{

  friend class section_dof_iterator;

public:

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached iterator.
  ///
  discretization_iterator();

  ///
  /// Copy constructor
  ///
  discretization_iterator(const discretization_iterator& xother);

  ///
  /// Destructor
  ///
  ~discretization_iterator();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual discretization_iterator* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // OTHER CONSTRUCTORS

  ///
  /// Creates an iterator anchored on base_space of xschema_anchor.
  ///
  discretization_iterator(const section_space_schema_member& xschema_anchor);

  // ITERATOR FACET

  ///
  /// True if this has been initialized for
  /// iteration with respect to a specific anchor.
  ///
  virtual bool is_initialized() const;

  ///
  /// Force the iterator to be done.
  ///
  virtual void force_is_done();

  ///
  /// Makes this the next member of the subset.
  ///
  inline void next()
  {
    next(false);
  };

  ///
  /// Makes this the next member of the subset.
  /// If xtruncate, new this is not less than old this,
  /// i.e. the depth-first descent is truncated
  /// and the cover of this is not visited.
  ///
  virtual void next(bool xtruncate);

  // DISCRETIZATION ITERATOR FACET

  ///
  /// The schema member whose base space is being iterated over;
  /// the top member of the domain of iteration (mutable version).
  ///
  section_space_schema_member& schema_anchor();

  ///
  /// The schema member whose base space is being iterated over;
  /// the top member of the domain of iteration (const version).
  ///
  const section_space_schema_member& schema_anchor() const;

  ///
  /// Set schema_anchor() to the same state as xschema_anchor.
  ///
  void put_schema_anchor(const section_space_schema_member& xschema_anchor);

  ///
  /// Set schema_anchor() to the member identified by xschema_anchor_index.
  ///
  void put_schema_anchor(pod_index_type xschema_anchor_index);

  ///
  /// Set schema_anchor() to the member identified by xschema_anchor_index.
  ///
  void put_schema_anchor(const scoped_index& xschema_anchor_index);

  ///
  /// The current discretization member index
  ///
  const scoped_index& discretization_member_index() const;

  ///
  /// The current evaluation member index
  ///
  const scoped_index& evaluation_member_index() const;

  ///
  /// True, if the current discretization member is in the multivalued subposet.
  ///
  bool is_multivalued() const;

protected:

  ///
  /// Initializes the schema anchor.
  ///
  void initialize_schema_anchor(const section_space_schema_member& xanchor);

  ///
  /// Initializes the has_visited markers.
  ///
  virtual void initialize_has_visited(const abstract_poset_member& xanchor);

private:

  ///
  /// The schema member whose base space is being iterated over;
  /// the top member of the domain of iteration.
  ///
  section_space_schema_member* _schema_anchor;

  ///
  /// Stores the list of members visited during the ascending iteration.
  ///
  zn_to_bool* _ascending_has_visited;

  ///
  /// Stores the list of members visited during the descending iteration.
  ///
  zn_to_bool* _descending_has_visited;

  ///
  /// List to store the upset to empty the _ascending_has_visited reset markers.
  ///
  singly_linked_list<int> _up_set;

  ///
  /// The current discretization member index.
  ///
  scoped_index _discretization_member_index;

  ///
  /// The current evaluation member index.
  ///
  scoped_index _evaluation_member_index;
};


} // namespace fiber_bundle

#endif // ifndef DISCRETIZATION_ITERATOR_H
