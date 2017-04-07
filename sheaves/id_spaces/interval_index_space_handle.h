
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
/// Interface for class interval_index_space_handle

#ifndef INTERVAL_INDEX_SPACE_HANDLE_H
#define INTERVAL_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SCATTERED_INSERTION_INDEX_SPACE_HANDLE_H
#include "scattered_insertion_index_space_handle.h"
#endif

namespace sheaf
{

class interval_index_space_state;
  
///
/// An implementation of class scattered_insertion_index_space_handle that has
/// a interval id space state.
///
class SHEAF_DLL_SPEC interval_index_space_handle : public scattered_insertion_index_space_handle
{

  friend class interval_index_space_state;

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new interval id space in the id space family xid_space
  /// with name xname, persistence xis_persistent, and merge mode xmerge_mode.
  /// Returns a handle to the id space created.
  ///
  static interval_index_space_handle new_space(index_space_family& xid_spaces,
					       const std::string& xname,
					       bool xis_persistent,
					       bool xmerge_mode);

protected:

private:

  //@}


  // ===========================================================
  /// @name INTERVAL_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  interval_index_space_handle();

  ///
  /// Copy constructor
  ///
  interval_index_space_handle(const interval_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  interval_index_space_handle(const index_space_family& xid_spaces,
			     pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  interval_index_space_handle(const index_space_family& xid_spaces,
			     const std::string& xname);

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  interval_index_space_handle& operator=(const interval_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~interval_index_space_handle();

protected:

  ///
  /// Constructor: Attach to state xstate.
  ///
  interval_index_space_handle(interval_index_space_state& xstate);

  using scattered_insertion_index_space_handle::state;

  ///
  /// The interval id space state (mutable version).
  ///
  interval_index_space_state& state();

  ///
  /// The interval id space state (const version).
  ///
  const interval_index_space_state& state() const;

private:

  //@}


  // ===========================================================
  /// @name INTERVAL INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make the closed interval [xbegin, xend] equivalent to
  /// [xbegin.hub_pod(), xhub_end.hub_pod()].
  /// synonym for insert_interval(xbegin, xend, xhub_begin.hub_pod(), xhub_end.hub_pod()).
  ///
  void insert_interval(pod_type xbegin,
		       pod_type xend,
		       const scoped_index& xhub_begin, 
		       const scoped_index& xhub_end);
  
  ///
  /// Make the closed interval [xbegin, xend] equivalent to
  /// [xhub_begin, xhub_end].
  ///
  void insert_interval(pod_type xbegin, 
		       pod_type xend, 
		       pod_type xhub_begin, 
		       pod_type xhub_end);
  
  ///
  /// Push the closed interval [xhub_begin.hub_pod(), xhub_end.hub_pod()]
  /// to the end of this space.
  /// synonym for push_interval(xhub_begin.hub_pod(), xhub_end.hub_pod()).
  ///
  void push_interval(const scoped_index& xhub_begin,
		     const scoped_index& xhub_end);

  ///
  /// Push the closed interval [xhub_begin, xhub_end] to the end of this space.
  ///
  void push_interval(pod_type xhub_begin, pod_type xhub_end);
  
  ///
  /// Removes the equivalance associated with the interval
  /// [xhub_begin.hub_pod(), xhub_end.hub_pod()].
  /// synonym for remove_hub_interval(xhub_begin.hub_pod(), xhub_end.hub_pod()).
  /// Returns the number of entries actually removed, if any.
  ///
  size_type remove_interval(const scoped_index& xhub_begin,
			    const scoped_index& xhub_end);

  ///
  /// Removes the equivalance associated with the interval
  /// [xhub_begin, xhub_end].
  /// Returns the number of entries actually removed, if any.
  ///
  size_type remove_hub_interval(pod_type xhub_begin, pod_type xhub_end);  

  ///
  /// Removes the equivalance associated with the interval
  /// [xbegin, xend].
  /// Returns the number of entries actually removed, if any.
  ///
  size_type remove_interval(pod_type xbegin, pod_type xend);  

  ///
  /// The beginning of the interval containing xid.hub_pod().
  /// synonym for internval_begin(xid.hub_pod()).
  ///
  pod_type interval_begin(const scoped_index& xid) const;
  
  ///
  /// The beginning of the interval containing xhub_id.
  ///
  pod_type interval_begin(pod_type xhub_id) const;
  
  ///
  /// The end of the interval containing xid.hub_pod.
  /// synonym for internval_end(xid.hub_pod()).
  ///
  pod_type interval_end(const scoped_index& xid) const;
  
  ///
  /// The end of the interval containing xhub_id.
  ///
  pod_type interval_end(pod_type xhub_id) const;
  
  ///
  /// True if and only if compatible intervals should be merged.
  ///
  bool merge_mode() const;

  ///
  /// Sets merge_mode() to xvalue.
  ///
  void put_merge_mode(bool xvalue);

protected:

private:

  //@}


  // ===========================================================
  /// @name SCATTERED_INSERTION_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name MAP REPRESENTATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// Inserts the map representation into ostream xos.
  ///
  void print_map_rep(std::ostream& xos) const;
  
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
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  virtual interval_index_space_handle& operator=(const index_space_handle& xother);

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual interval_index_space_handle* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using scattered_insertion_index_space_handle::conforms_to_state;

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

#endif // ifndef INTERVAL_INDEX_SPACE_HANDLE_H
