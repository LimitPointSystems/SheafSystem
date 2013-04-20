

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class index_space_handle

#ifndef INDEX_SPACE_HANDLE_H
#define INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

class abstract_product_structure;
class hub_index_space_handle;
class index_space_collection;
class index_space_family;
class index_space_iterator;
class scoped_index;

///
/// An abstract handle to a space of alternate integer identifiers (aliases)
/// for a subset of a hub set of integer identifiers.
///
class SHEAF_DLL_SPEC index_space_handle : public any
{

  // ===========================================================
  /// @name INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// Destructor
  ///
  virtual ~index_space_handle();

  ///
  /// Assignment operator.
  ///
  virtual index_space_handle& operator=(const index_space_handle& xother) = 0;

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_handle& xother) const = 0;

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual index_space_handle* clone() const = 0;

protected:

  ///
  /// Default constructor
  ///
  index_space_handle();

  ///
  /// Copy constructor; disabled.
  ///
  index_space_handle(const index_space_handle& xother) { };

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id space family for this (const version).
  ///
  virtual const index_space_family& id_spaces() const = 0;

  ///
  /// The id space family for this (mutable version).
  ///
  virtual index_space_family& id_spaces() = 0;

  ///
  /// The hub id space.
  ///
  const hub_index_space_handle& hub_id_space() const;

  ///
  /// The number of members.
  ///
  virtual size_type ct() const = 0;

  ///
  /// True if there are no ids in the space.
  ///
  bool is_empty() const;

  ///
  /// Beginning id of this space.
  ///
  virtual pod_type begin() const = 0;

  ///
  /// Ending id of this space.
  ///
  virtual pod_type end() const = 0;

  ///
  /// True if begin() == 0 and end() == ct().
  ///
  bool is_gathered() const;
    
  ///
  /// True if this space contains id xid.
  ///
  virtual bool contains(pod_type xid) const = 0;

  ///
  /// True if this space contains an id equivalent to xid.
  /// synonym for contains_hub(xid.hub_pod()).
  ///
  bool contains(const scoped_index& xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  /// synonym for contains_unglued_hub(xid)
  ///
  bool contains_hub(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  ///
  virtual bool contains_unglued_hub(pod_type xid) const = 0;

  ///
  /// True if this space contains an id equivalent to xid in the glued hub id space.
  ///
  virtual bool contains_glued_hub(pod_type xid) const = 0;

  ///
  /// True if this space contains an id xid equivalent to xhub_id in
  /// the hub id space.
  /// synonym for contains(xid, xhub_id.hub_pod()).
  ///
  bool contains(pod_type xid, const scoped_index& xhub_id) const;

  ///
  /// True if this space contains an id xid equivalent to xhub_id in
  /// the hub id space.
  ///
  virtual bool contains(pod_type xid, pod_type xhub_id) const = 0;

  ///
  /// The pod index in this space equivalent to xid in the hub id space.
  ///
  virtual pod_type pod(pod_type xid) const = 0;

  ///
  /// The pod index in this space equivalent to xid.
  /// synonym for pod(xid.hub_pod()).
  ///
  pod_type pod(const scoped_index& xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space;
  /// synonym for unglued_hub_pod(pod_type).
  ///
  pod_type hub_pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  virtual pod_type unglued_hub_pod(pod_type xid) const = 0;

  ///
  /// The pod index in the hub id space equivalent to xid in this id space.
  /// synonym for unglued_hub_pod(xid).
  ///
  virtual pod_type glued_hub_pod(pod_type xid) const = 0;

  ///
  /// True if this id space should be written to disk.
  ///
  virtual bool is_persistent() const = 0;

protected:

private:

  //@}


  // ===========================================================
  /// @name PRODUCT STRUCTURE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a new product structure for this id space by cloning the
  /// product structure, xproduct.
  ///
  virtual void new_product_structure(const abstract_product_structure& xproduct) = 0;

  ///
  /// Deletes the product structure for this id space.
  ///
  virtual void delete_product_structure() = 0;

  ///
  /// The product structure for this id space (const version).
  ///
  virtual const abstract_product_structure& product_structure() const = 0;

  ///
  /// The product structure for this id space (mutable version).
  ///
  virtual abstract_product_structure& product_structure() = 0;

  ///
  /// The product structure of type T for this id space (const version).
  ///
  template<typename T>
  const T& product_structure() const;

  ///
  /// The product structure of type T for this id space (mutable version).
  ///
  template<typename T>
  T& product_structure();

  ///
  /// True if this id space has a product structure.
  ///
  virtual bool has_product_structure() const = 0;

  ///
  /// True if the product structure for this id space conforms to type T.
  ///
  template<typename T>
  bool product_structure_conforms_to() const;

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
  virtual const index_space_collection& host() const = 0;

  ///
  /// Index of this space.
  ///
  virtual pod_type index() const = 0;

  ///
  /// Name of this space.
  ///
  string name() const;

  ///
  /// Associate name xname with this id space.
  ///
  void put_name(const string& xname);

  ///
  /// True if this handle is attached to a state.
  ///
  virtual bool is_attached() const = 0;

  ///
  /// Attach to the state with index xindex in the id space family xid_spaces.
  ///
  void attach_to(const index_space_family& xid_spaces, pod_type xindex);

  ///
  /// Attach to the state with name xname in the id space family xid_spaces.
  ///
  void attach_to(const index_space_family& xid_spaces, const string& xname);

  ///
  /// Attach to the state with index xindex in the id space family id_spaces().
  ///
  virtual void attach_to(pod_type xindex) = 0;

  ///
  /// Attach to the state with name xname in the id space family id_spaces().
  ///
  void attach_to(const string& xname);

  ///
  /// Attach to the state of the id space xid_space.
  ///
  void attach_to(const index_space_handle& xid_space);

  ///
  /// True if this conforms to the handle type required by the state
  /// with index xindex in the id space family, xid_spaces.
  ///
  bool conforms_to_state(const index_space_family& xid_spaces,
			 pod_type xindex) const;

  ///
  /// True if this conforms to the handle type required by the state
  /// with name xname in the id space family, xid_spaces.
  ///
  bool conforms_to_state(const index_space_family& xid_spaces,
			 const string& xname) const;

  ///
  /// True if this conforms to the handle type required by the state
  /// with id xid.
  ///
  bool conforms_to_state(pod_type xid) const;

  ///
  /// True if this conforms to the handle type required by the state
  /// with name xname.
  ///
  bool conforms_to_state(const string& xname) const;

  ///
  /// Attach to the state with local scope id, xlocal_id in the host id space
  /// collection xhost.
  ///
  virtual void attach_to(const index_space_collection& xhost,
			 pod_type xlocal_id) = 0;

  ///
  /// Detach this handle form its state, if any.
  ///
  virtual void detach() = 0;

  ///
  /// True if this conforms to the handle type required by the state
  /// with local scope id xlocal_id in the host id space collection xhost.
  ///
  virtual bool conforms_to_state(const index_space_collection& xhost,
				 pod_type xlocal_id) const = 0;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space handle from the handle pool attached
  /// to the same id space.
  ///
  virtual index_space_handle& get_id_space() const = 0;

  ///
  /// Returns this id space handle to the handle pool.
  ///
  virtual void release_id_space() const = 0;

  ///
  /// True if and only if this id space handle was allocated by
  /// the handle pool.
  ///
  virtual bool allocated_id_space() const = 0;

protected:

private:

  //@}


  // ===========================================================
  /// @name ITERATOR POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space iterator from the iterator pool.
  ///
  virtual index_space_iterator& get_iterator() const = 0;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  virtual void release_iterator(index_space_iterator& xitr) const = 0;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the iterator pool.
  ///
  virtual bool allocated_iterator(const index_space_iterator& xitr) const = 0;

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
 
///
/// Insert index_space_handle& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const index_space_handle& xi);

///
/// The deep size of index_space_handle& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const index_space_handle& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef INDEX_SPACE_HANDLE_H
