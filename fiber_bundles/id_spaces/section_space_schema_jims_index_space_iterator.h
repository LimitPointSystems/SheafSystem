

//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Interface for class section_space_schema_jims_index_space_iterator

#ifndef SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_ITERATOR_H
#define SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef AUTO_BLOCK_H
#include "auto_block.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_ITERATOR_H
#include "explicit_index_space_iterator.h"
#endif

namespace sheaf
{
class ij_product_structure;
class array_index_space_state;
}

namespace fiber_bundle
{

class section_space_schema_jims_index_space_state;

using namespace sheaf;

///
/// An iterator over an id space in which the equivalence between
/// the ids in the space and the hub id space is stored in an array.
///
class SHEAF_DLL_SPEC section_space_schema_jims_index_space_iterator : public explicit_index_space_iterator
{

  friend class array_index_space_state;

  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  section_space_schema_jims_index_space_iterator();

  ///
  /// Copy constructor.
  ///
  section_space_schema_jims_index_space_iterator(const section_space_schema_jims_index_space_iterator& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  section_space_schema_jims_index_space_iterator(const index_space_family& xid_spaces,
						 pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  section_space_schema_jims_index_space_iterator(const index_space_family& xid_spaces,
						 const string& xname);

  ///
  /// Assignment operator.
  ///
  section_space_schema_jims_index_space_iterator& operator=(const section_space_schema_jims_index_space_iterator& xother);

  ///
  /// Destructor
  ///
  virtual ~section_space_schema_jims_index_space_iterator();

protected:

  ///
  /// The base space jims id space iterator.
  ///
  index_space_iterator& base_space_iterator();

  ///
  /// The fiber schema jims id space iterator.
  ///
  index_space_iterator& fiber_schema_iterator();

  ///
  /// Update the ids.
  ///
  void update_ids();

  ///
  /// The base space jims id space iterator.
  ///
  index_space_iterator* _base_space_itr;

  ///
  /// The fiber schema jims id space iterator.
  ///
  index_space_iterator* _fiber_schema_itr;

  ///
  /// The product structure of the section space schema jims id space.
  ///
  ij_product_structure* _section_space_schema_jims_product;

  ///
  /// The product structure of the section space schema id space.
  ///
  ij_product_structure* _section_space_schema_product;

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_ITERATOR FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// The explicit state (mutable version).
  ///
  section_space_schema_jims_index_space_state& state();

  ///
  /// The explicit state (const version).
  ///
  const section_space_schema_jims_index_space_state& state() const;

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_ITERATOR FACET
  // ===========================================================

public:

  ///
  /// Assignment operator.
  ///
  virtual section_space_schema_jims_index_space_iterator& operator=(const index_space_iterator& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_iterator& xother) const;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the iterator is attached, attach to the same state.
  ///
  virtual section_space_schema_jims_index_space_iterator* clone() const;

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

protected:

  using explicit_index_space_iterator::attach_to;

  ///
  ///
  /// Attach to the explicit id space state xstate.
  ///
  virtual void attach_to(explicit_index_space_state* xstate);

  ///
  /// Detach this iterator form its state, if any.
  ///
  virtual void detach();

  using explicit_index_space_iterator::conforms_to_state;

  ///
  /// True if this conforms to the iterator type required by the
  /// explicit id space state xstate.
  ///
  virtual bool conforms_to_state(explicit_index_space_state* xstate) const;

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

#endif // ifndef SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_ITERATOR_H
