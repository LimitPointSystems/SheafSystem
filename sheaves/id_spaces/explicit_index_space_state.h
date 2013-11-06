
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
/// Interface for class explicit_index_space_state.

#ifndef EXPLICIT_INDEX_SPACE_STATE_H
#define EXPLICIT_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef FACTORY_H
#include "factory.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

class abstract_product_structure;
class explicit_index_space_handle;
class explicit_index_space_iterator;
class hub_index_space_handle;
class index_space_collection;
class index_space_family;
class index_space_handle;
class index_space_iterator;
class scoped_index;

///
/// An immutable abstract state for a space of alternate integer identifiers
/// (aliases) for a subset of the hub set of integer identifiers.
///
class SHEAF_DLL_SPEC explicit_index_space_state : public any
{

  friend class explicit_index_space_collection;
  friend class explicit_index_space_interval;
  friend class index_space_family;

  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_STATE FACET
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
  virtual ~explicit_index_space_state();

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const explicit_index_space_state& xother) const;

  ///
  /// The host collection (const version).
  ///
  const index_space_collection& host() const;

  ///
  /// The host collection (mutable version).
  ///
  index_space_collection& host();

  ///
  /// The index of this id space.
  ///
  pod_type index() const;

  ///
  /// The deep size of this.
  ///
  virtual size_type deep_size(bool xinclude_shallow) const;

protected:

  ///
  /// Default constructor
  ///
  explicit_index_space_state();

  ///
  /// Copy constructor; disabled.
  ///
  explicit_index_space_state(const explicit_index_space_state& xother) { };

  ///
  /// Assignment operator
  ///
  virtual explicit_index_space_state& operator=(const explicit_index_space_state& xother);

  ///
  /// Create a new id space state in the id space family xid_space
  /// at the next available id space index with name xname,
  /// and persistence xis_persistent.
  ///
  void new_state(index_space_family& xid_spaces,
		 const string& xname,
		 bool xis_persistent);

  ///
  /// Create a new id space state in the id space family xid_spaces
  /// at the id space index xid with name xname, and
  /// persistence xis_persistent.
  ///
  void new_state(index_space_family& xid_spaces,
		 pod_type xid,
		 const string& xname,
		 bool xis_persistent);

  ///
  /// The host collection.
  ///
  index_space_collection* _host;

  ///
  /// The index of this id space.
  ///
  pod_type _index;

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
  const index_space_family& id_spaces() const;

  ///
  /// The id space family for this (mutable version).
  ///
  index_space_family& id_spaces();

  ///
  /// The hub id space.
  ///
  const hub_index_space_handle& hub_id_space() const;

  ///
  /// The number of members.
  ///
  size_type ct() const;

  ///
  /// True if there are no ids in the space.
  ///
  bool is_empty() const;

  ///
  /// Beginning id of this space.
  ///
  pod_type begin() const;

  ///
  /// Ending id of this space.
  ///
  pod_type end() const;

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
  /// True if this space contains an id equivalent to xid in the hub id space.
  ///
  virtual bool contains_glued_hub(pod_type xid) const;

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
  virtual bool contains(pod_type xid, pod_type xhub_id) const;

  ///
  /// The pod index in this space equivalent to xid in the unglued hub id space.
  ///
  virtual pod_type pod(pod_type xid) const = 0;

  ///
  /// The pod index in this space equivalent to xid.
  /// synonym for pod(xid.hub_pod()).
  ///
  pod_type pod(const scoped_index& xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  /// synonym for unglued_hub_pod(xid).
  ///
  pod_type hub_pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  virtual pod_type unglued_hub_pod(pod_type xid) const = 0;

  ///
  /// The pod index in the glued hub id space equivalent to xid in this id space.
  ///
  virtual pod_type glued_hub_pod(pod_type xid) const ;

  ///
  /// True if this id space should be written to disk.
  ///
  bool is_persistent() const;

protected:

  ///
  /// Invalidate the extrema.
  ///
  void invalidate_extrema();

  ///
  /// The number of members.
  ///
  size_type _ct;

  ///
  /// Beginning id of this space.
  ///
  pod_type _begin;

  ///
  /// Ending id of this space.
  ///
  pod_type _end;

  ///
  /// True if this id space should be written to disk.
  ///
  bool _is_persistent;

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
  virtual void new_product_structure(const abstract_product_structure& xproduct);

  ///
  /// Deletes the product structure for this id space.
  ///
  virtual void delete_product_structure();

  ///
  /// The product structure for this id space (const version).
  ///
  const abstract_product_structure& product_structure() const;

  ///
  /// The product structure for this id space (mutable version).
  ///
  abstract_product_structure& product_structure();

  ///
  /// True if this id space has a product structure.
  ///
  bool has_product_structure() const;

protected:

  ///
  /// The product structure for this id space.
  ///
  abstract_product_structure* _product;

private:

  //@}


  // ===========================================================
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space handle from the handle pool.
  ///
  virtual index_space_handle& get_id_space() const = 0;

  ///
  /// Returns the id space handle xid_space to the handle pool.
  ///
  virtual void release_id_space(index_space_handle& xid_space) const = 0;

  ///
  /// True if and only if id space handle xid_space was allocated by
  /// the handle pool.
  ///
  virtual bool allocated_id_space(const index_space_handle& xid_space) const = 0;

protected:

  ///
  /// Attach the id space handle xid_space to this state.
  ///
  void attach(explicit_index_space_handle& xid_space) const;

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

  ///
  /// Attach the id space iterator xitr to this state.
  ///
  void attach(explicit_index_space_iterator& xitr) const;

private:

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
  /// A factory for making descendants of this class.
  ///
  static factory<explicit_index_space_state>& id_space_factory();

  ///
  /// Virtual constructor; create a new instance of the same type at this.
  ///
  virtual explicit_index_space_state* clone() const = 0;

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
/// The deep size of explicit_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const explicit_index_space_state& xn, bool xinclude_shallow = true);
  
///
/// Insert explicit_index_space_state& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const explicit_index_space_state& xn);

} // end namespace sheaf

#endif // ifndef EXPLICIT_INDEX_SPACE_STATE_H
