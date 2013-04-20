

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class offset_index_space_state

#ifndef OFFSET_INDEX_SPACE_STATE_H
#define OFFSET_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef LIST_POOL_H
#include "list_pool.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_STATE_H
#include "explicit_index_space_state.h"
#endif

namespace sheaf
{
  
class offset_index_space_handle;
class offset_index_space_iterator;

///
/// A computed implementation of abstract class explicit_index_space_state.
/// This representation assumes the ids are an open gathered set of ids.
/// The equivalence between the ids in this space and the hub id space
/// is computed using an offset.
///
class SHEAF_DLL_SPEC offset_index_space_state : public explicit_index_space_state
{

  // ===========================================================
  /// @name OFFSET_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an arg list for constructing an instance of this.
  ///
  static arg_list make_arg_list(pod_type xoffset, size_type xct);

protected:

  ///
  /// Default constructor
  ///
  offset_index_space_state();

  ///
  /// Copy constructor; disabled
  ///
  offset_index_space_state(const offset_index_space_state& xother) { };

  ///
  /// Constructor: Creates an instance from arguments, xargs.
  ///
  offset_index_space_state(const arg_list& xargs);

  ///
  /// Destructor
  ///
  virtual ~offset_index_space_state();

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

  ///
  /// The offset into the hub id space.
  ///
  pod_type _offset;

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const explicit_index_space_state& xother) const;

  ///
  /// The deep size of this.
  ///
  virtual size_type deep_size(bool xinclude_shallow) const;

protected:

  ///
  /// Assignment operator
  ///
  virtual offset_index_space_state& operator=(const explicit_index_space_state& xother);

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this space contains id xid.
  ///
  virtual bool contains(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  ///
  virtual bool contains_unglued_hub(pod_type xid) const;

  ///
  /// The pod index in this space equivalent to xid in the hub id space.
  ///
  virtual pod_type pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  virtual pod_type unglued_hub_pod(pod_type xid) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of handles in the pool.
  ///
  static size_type handle_pool_ct();

  ///
  /// The deep size of the handle pool.
  ///
  static size_type handle_pool_deep_size();

  ///
  /// Allocates an id space handle from the handle pool.
  ///
  virtual index_space_handle& get_id_space() const;

  ///
  /// Returns the id space handle xid_space to the handle pool.
  ///
  virtual void release_id_space(index_space_handle& xid_space) const;

  ///
  /// True if and only if id space handle xid_space was allocated by
  /// the handle pool.
  ///
  virtual bool allocated_id_space(const index_space_handle& xid_space) const;

protected:

private:

  ///
  /// The handle pool.
  ///
  static list_pool<offset_index_space_handle>& handles();

  //@}


  // ===========================================================
  /// @name ITERATOR POOL ACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of iterators in the pool.
  ///
  static size_type iterator_pool_ct();

  ///
  /// The deep size of the iterator pool.
  ///
  static size_type iterator_pool_deep_size();

  ///
  /// Allocates an id space iterator from the iterator pool.
  ///
  virtual index_space_iterator& get_iterator() const;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  virtual void release_iterator(index_space_iterator& xitr) const;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the iterator pool.
  ///
  virtual bool allocated_iterator(const index_space_iterator& xitr) const;

protected:

private:

  ///
  /// The iterator pool.
  ///
  static list_pool<offset_index_space_iterator>& iterators();

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@}

public:

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// Virtual constructor; create a new instance of the same type at this
  /// with arguments xargs.
  ///
  virtual offset_index_space_state* clone(const arg_list& xargs) const;

protected:

private:

  ///
  /// True if prototype for this class has been entered in factory.
  /// Intended to force creation of prototype at initialization.
  ///
  static bool _has_prototype;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

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
 
///
/// The deep size of offset_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const offset_index_space_state& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef OFFSET_INDEX_SPACE_STATE_H
