
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
/// Interface for class singleton_implicit_index_space_iterator

#ifndef SINGLETON_IMPLICIT_INDEX_SPACE_ITERATOR_H
#define SINGLETON_IMPLICIT_INDEX_SPACE_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef AUTO_BLOCK_H
#include "auto_block.h"
#endif

#ifndef IMPLICIT_INDEX_SPACE_ITERATOR_H
#include "implicit_index_space_iterator.h"
#endif

namespace sheaf
{

///
/// An implementation of implicit_index_space_iterator for an implicit id
/// space in an singleton_index_space_interval.
///
class SHEAF_DLL_SPEC singleton_implicit_index_space_iterator : public implicit_index_space_iterator
{

  friend class singleton_implicit_index_space_interval;

  // ===========================================================
  /// @name SINGLETON_IMPLICIT_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  singleton_implicit_index_space_iterator();

  ///
  /// Copy constructor.
  ///
  singleton_implicit_index_space_iterator(const singleton_implicit_index_space_iterator& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  singleton_implicit_index_space_iterator(const index_space_family& xid_spaces,
					  pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  singleton_implicit_index_space_iterator(const index_space_family& xid_spaces,
					  const std::string& xname);

  ///
  /// Assignment operator.
  ///
  singleton_implicit_index_space_iterator& operator=(const singleton_implicit_index_space_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~singleton_implicit_index_space_iterator();

protected:

  ///
  /// The hub beginning id.
  ///
  pod_type _hub_begin;

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
  virtual singleton_implicit_index_space_iterator& operator=(const index_space_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  virtual singleton_implicit_index_space_iterator* clone() const;

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


} // namespace sheaf

#endif // ifndef SINGLETON_IMPLICIT_INDEX_SPACE_ITERATOR_H
