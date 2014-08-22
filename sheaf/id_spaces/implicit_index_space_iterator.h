
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

/// @file
/// Interface for class implicit_index_space_iterator

#ifndef COM_LIMITPOINT_SHEAF_IMPLICIT_INDEX_SPACE_ITERATOR_H
#define COM_LIMITPOINT_SHEAF_IMPLICIT_INDEX_SPACE_ITERATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_INDEX_SPACE_ITERATOR_H
#include "ComLimitPoint/sheaf/index_space_iterator.h"
#endif

namespace sheaf
{

class implicit_index_space_state;

///
/// An implementation of class index_space_iterator for id spaces
/// that are implicitly represtented.
///
class SHEAF_DLL_SPEC implicit_index_space_iterator : public index_space_iterator
{

  // ===========================================================
  /// @name IMPLICIT_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor
  ///
  virtual ~implicit_index_space_iterator();

protected:

  ///
  /// Default constructor.
  ///
  implicit_index_space_iterator();

  ///
  /// Copy constructor.
  ///
  implicit_index_space_iterator(const implicit_index_space_iterator& xother);

  ///
  /// Assignment operator.
  ///
  implicit_index_space_iterator& operator=(const implicit_index_space_iterator& xother);

  ///
  /// The host collection.
  ///
  const index_space_collection* _host;

  ///
  /// The id of this space in the local host id space.
  ///
  pod_type _local_id;

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Assignment operator.
  ///
  virtual implicit_index_space_iterator& operator=(const index_space_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  virtual implicit_index_space_iterator* clone() const = 0;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The host collection.
  ///
  virtual const index_space_collection& host() const;

  ///
  /// Index of this space.
  ///
  virtual pod_type index() const;

  ///
  /// True if this iterator is attached to a state.
  ///
  virtual bool is_attached() const;

  using index_space_iterator::attach_to;

  ///
  /// Attach to the state with index xindex in the id space family id_spaces().
  ///
  virtual void attach_to(pod_type xindex);

  ///
  /// Detach this iterator form its state, if any.
  ///
  virtual void detach();

protected:

private:

  //@}


  // ===========================================================
  /// @name  ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================


} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_IMPLICIT_INDEX_SPACE_ITERATOR_H
