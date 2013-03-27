// $RCSfile: singleton_index_space_handle.h,v $ $Revision: 1.3 $ $Date: 2013/01/15 22:23:45 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class singleton_index_space_handle

#ifndef SINGLETON_INDEX_SPACE_HANDLE_H
#define SINGLETON_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_HANDLE_H
#include "explicit_index_space_handle.h"
#endif

namespace sheaf
{

class singleton_index_space_state;
  
///
/// An implementation of class explicit_index_space_handle that has
/// a singleton id space state.
///
class SHEAF_DLL_SPEC singleton_index_space_handle : public explicit_index_space_handle
{

  friend class singleton_sum_index_space_state;

  // ===========================================================
  /// @name SINGLETON_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  singleton_index_space_handle();

  ///
  /// Copy constructor
  ///
  singleton_index_space_handle(const singleton_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  singleton_index_space_handle(const index_space_family& xid_spaces,
			       pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  singleton_index_space_handle(const index_space_family& xid_spaces,
			       const string& xname);

  ///
  /// Assignment operator.
  ///
  singleton_index_space_handle& operator=(const singleton_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~singleton_index_space_handle();

protected:

  using explicit_index_space_handle::state;

  ///
  /// The singleton id space state (mutable version).
  ///
  singleton_index_space_state& state();

  ///
  /// The singleton id space state (const version).
  ///
  const singleton_index_space_state& state() const;

private:

  //@}


  // ===========================================================
  /// @name SINGLETON INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The hub id of the singleton id.
  ///
  pod_type hub_id() const;

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
  virtual singleton_index_space_handle* clone() const;

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

#endif // ifndef SINGLETON_INDEX_SPACE_HANDLE_H
