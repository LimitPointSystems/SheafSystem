
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
/// Interface for class ijk_adjacency_implicit_index_space_iterator

#ifndef IJK_ADJACENCY_IMPLICIT_INDEX_SPACE_ITERATOR_H
#define IJK_ADJACENCY_IMPLICIT_INDEX_SPACE_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef AUTO_BLOCK_H
#include "SheafSystem/auto_block.h"
#endif

#ifndef IMPLICIT_INDEX_SPACE_ITERATOR_H
#include "SheafSystem/implicit_index_space_iterator.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

///
/// An implementation of implicit_index_space_iterator for an implicit id
/// space in an ijk_adjacency_index_space_interval.
///
class SHEAF_DLL_SPEC ijk_adjacency_implicit_index_space_iterator : public implicit_index_space_iterator
{

  friend class ijk_adjacency_implicit_index_space_interval;

  // ===========================================================
  /// @name IJK_ADJACENCY_IMPLICIT_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  ijk_adjacency_implicit_index_space_iterator();

  ///
  /// Copy constructor.
  ///
  ijk_adjacency_implicit_index_space_iterator(const ijk_adjacency_implicit_index_space_iterator& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  ijk_adjacency_implicit_index_space_iterator(const index_space_family& xid_spaces,
					      pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  ijk_adjacency_implicit_index_space_iterator(const index_space_family& xid_spaces,
					      const std::string& xname);

  ///
  /// Assignment operator.
  ///
  ijk_adjacency_implicit_index_space_iterator& operator=(const ijk_adjacency_implicit_index_space_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~ijk_adjacency_implicit_index_space_iterator();

  ///
  /// The hub id of the first zone in the adjacency list.
  ///
  pod_type hub_begin() const;

  ///
  /// The number of zones in the j direction.
  ///
  size_type j_size() const;

  ///
  /// The number of zones in the k direction.
  ///
  size_type k_size() const;

  ///
  /// The number of adjacent zones in the i direction.
  ///
  size_type i_ct() const;

  ///
  /// The number of adjacent zones in the j direction.
  ///
  size_type j_ct() const;

  ///
  /// The number of adjacent zones in the k direction.
  ///
  size_type k_ct() const;

protected:

  ///
  /// The hub id of the first zone in the adjacency list.
  ///
  pod_type _hub_begin;

  ///
  /// The number of zones in the j direction.
  ///
  size_type _j_size;

  ///
  /// The number of zones in the j direction.
  ///
  size_type _k_size;

  ///
  /// The number of adjacent zones in the i direction.
  ///
  size_type _i_ct;

  ///
  /// The number of adjacent zones in the j direction.
  ///
  size_type _j_ct;

  ///
  /// The number of adjacent zones in the k direction.
  ///
  size_type _k_ct;

  ///
  /// The current index in the i direction.
  ///
  pod_type _i;

  ///
  /// The current index in the j direction.
  ///
  pod_type _j;

  ///
  /// The current index in the k direction.
  ///
  pod_type _k;

private:

  //@}


  // ===========================================================
  /// @name IMPLICIT_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_ITERATOR FACET
  // ===========================================================

public:

  ///
  /// Assignment operator.
  ///
  virtual ijk_adjacency_implicit_index_space_iterator& operator=(const index_space_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  virtual ijk_adjacency_implicit_index_space_iterator* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Makes item() the next id in the iteration.
  ///
  virtual void next();

  ///
  /// Restarts the iteration.
  ///
  virtual void reset();

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using implicit_index_space_iterator::attach_to;

  ///
  /// Attach to the state with local scope id, xlocal_id in the host id space
  /// collection xhost.
  ///
  virtual void attach_to(const index_space_collection& xhost,
			 pod_type xlocal_id);

  using implicit_index_space_iterator::conforms_to_state;

  ///
  /// True if this conforms to the handle type required by the state
  /// with local scope id xlocal_id in the host id space collection xhost.
  ///
  virtual bool conforms_to_state(const index_space_collection& xhost,
				 pod_type xlocal_id) const;

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


} // namespace fiber_bundle

#endif // ifndef IJK_ADJACENCY_IMPLICIT_INDEX_SPACE_ITERATOR_H
