

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class offset_index_space_handle

#ifndef OFFSET_INDEX_SPACE_HANDLE_H
#define OFFSET_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_HANDLE_H
#include "explicit_index_space_handle.h"
#endif

namespace sheaf
{

class offset_index_space_state;
  
///
/// An implementation of class explicit_index_space_handle that has
/// a offset id space state.
///
class SHEAF_DLL_SPEC offset_index_space_handle : public explicit_index_space_handle
{

  friend class offset_sum_index_space_state;

  // ===========================================================
  /// @name OFFSET_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  offset_index_space_handle();

  ///
  /// Copy constructor
  ///
  offset_index_space_handle(const offset_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  offset_index_space_handle(const index_space_family& xid_spaces,
			     pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  offset_index_space_handle(const index_space_family& xid_spaces,
			     const string& xname);

  ///
  /// Assignment operator.
  ///
  offset_index_space_handle& operator=(const offset_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~offset_index_space_handle();

protected:

  using explicit_index_space_handle::state;

  ///
  /// The offset id space state (mutable version).
  ///
  offset_index_space_state& state();

  ///
  /// The offset id space state (const version).
  ///
  const offset_index_space_state& state() const;

private:

  //@}


  // ===========================================================
  /// @name OFFSET INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The offset into the hub id space.
  ///
  pod_type offset() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual offset_index_space_handle* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using explicit_index_space_handle::conforms_to_state;

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
  /// @name ANY FACET
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
 
} // end namespace sheaf

#endif // ifndef OFFSET_INDEX_SPACE_HANDLE_H
