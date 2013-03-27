// $RCSfile: hub_index_space_handle.h,v $ $Revision: 1.4 $ $Date: 2013/03/13 00:59:02 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class hub_index_space_handle

#ifndef HUB_INDEX_SPACE_HANDLE_H
#define HUB_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SUM_INDEX_SPACE_HANDLE_H
#include "sum_index_space_handle.h"
#endif

namespace sheaf
{
  
class primary_sum_index_space_state;
  
///
/// An implementation of class sum_index_space_handle that has
/// a primary sum id space state.
///
class SHEAF_DLL_SPEC hub_index_space_handle : public sum_index_space_handle
{

  // ===========================================================
  /// @name HUB_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  hub_index_space_handle();

  ///
  /// Copy constructor
  ///
  hub_index_space_handle(const hub_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  hub_index_space_handle(const index_space_family& xid_spaces,
			 pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  hub_index_space_handle(const index_space_family& xid_spaces,
			 const string& xname);

  ///
  /// Assignment operator.
  ///
  hub_index_space_handle& operator=(const hub_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~hub_index_space_handle();

protected:

  using explicit_index_space_handle::state;

  ///
  /// The primary sum id space state (mutable version).
  ///
  primary_sum_index_space_state& state();

  ///
  /// The primary sum id space state (const version).
  ///
  const primary_sum_index_space_state& state() const;

private:

  //@}


  // ===========================================================
  /// @name PRIMARY SUM INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocate the next available id in this space.
  ///
  pod_type new_id();

  ///
  /// Allocate an xid in this space.
  ///
  pod_type new_id(pod_type xid);

  ///
  /// Deallocate the id xid in this space.
  ///
  void delete_id(pod_type xid);

  ///
  /// True if and only if the reserved term containing xid is
  /// already a reserved term or is available for allocation.
  ///
  bool is_valid_reserved_id(pod_type xid) const;

  ///
  /// The next available id.
  ///
  pod_type next_id() const;

  ///
  /// Create a new primary term [next_id(), next_id()+xct).
  /// Returns the index of the term created.
  ///
  pod_type new_primary_term(size_type xct);

  ///
  /// Create a new primary term [xid, xid+xct).
  /// Returns the index of the term created.
  ///
  pod_type new_primary_term(pod_type xid, size_type xct);

  ///
  /// Remove xi-th term of this sum.
  ///
  void remove_term(pod_type xi);

  ///
  /// Extends the last term to ct() == xct.
  ///
  void extend_last_term(size_type xct);

  ///
  /// True if all ids in the interval [xbegin, xend) are in this space.
  ///
  bool interval_is_full(pod_type xbegin, pod_type xend) const;

  ///
  /// True if all ids in the interval [xbegin, xend) are not in this space.
  ///
  bool interval_is_empty(pod_type xbegin, pod_type xend) const;

  ///
  /// True if the ids in the internal [xbegin, xend) are available in this space.
  ///
  bool interval_is_available(pod_type xbegin, pod_type xend) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name GLUING FACET
  // ===========================================================
  //@{

public:

  ///
  /// Glues xid to xrep; adds xid to the equivalence class
  /// with representative member xrep.
  ///
  void glue(pod_type xid, pod_type xrep);
  
  ///
  /// Unglues xid; makes xid its own representative.
  ///
  void unglue(pod_type xid);
  
  ///
  /// Unglue all ids glued to representative xrep_id; 
  /// makes each id in the equivalence class of xrep_id
  /// its own representative.
  ///
  void unglue_all(pod_type xrep_id);

  ///
  /// Ture if there is any gluing.
  ///
  bool has_gluing() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name GATHERED ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Construct a gathered id space from this id space.
  /// If xexclude_bottom, construct the id space without BOTTOM_INDEX.
  ///
  const index_space_handle& new_gathered_id_space(bool xexclude_bottom);

  ///
  /// Update the gathered id space.
  ///
  void update_gathered_id_space();

  ///
  /// The gathered id space.
  ///
  const index_space_handle& gathered_id_space() const;

  ///
  /// True, if the gathered id space excludes BOTTOM_INDEX.
  ///
  bool gathered_id_space_excludes_bottom() const;

  ///
  /// True, if the gathered id space exists.
  ///
  bool has_gathered_id_space() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name STANDARD IDS FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make end() the standard id end.
  ///
  void update_standard_ids();

  ///
  /// True if and only if there are only standard ids.
  ///
  bool has_only_standard_ids() const;

  ///
  /// Deallocate all non-standard ids.
  ///
  void clear_ids();

protected:

private:

  //@}


  // ===========================================================
  /// @name SUM_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

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
  virtual hub_index_space_handle* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using sum_index_space_handle::conforms_to_state;

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

#endif // ifndef HUB_INDEX_SPACE_HANDLE_H
