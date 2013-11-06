
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
/// Interface for class index_space_family

#ifndef INDEX_SPACE_FAMILY_H
#define INDEX_SPACE_FAMILY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_COLLECTION_H
#include "explicit_index_space_collection.h"
#endif

#ifndef HUB_INDEX_SPACE_HANDLE_H
#include "hub_index_space_handle.h"
#endif

#ifndef INTERVAL_INDEX_SPACE_HANDLE_H
#include "interval_index_space_handle.h"
#endif

#ifndef NAME_MULTIMAP_H
#include "name_multimap.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

#ifndef STD_HASH_SET_H
#include "std_hash_set.h"
#endif
 
#ifndef STD_MAP_H
#include "std_map.h"
#endif

namespace sheaf
{

class arg_list;
class explicit_index_space_interval;
class index_space_family;
class index_space_family_iterator;
class index_space_interval;
class index_space_iterator;
class index_space_state;
class mutable_index_space_handle;
class primary_sum_index_space_state;
class scoped_index;

///
/// Factory and container for a family of id spaces.
///
class SHEAF_DLL_SPEC index_space_family : public any
{
  friend class explicit_index_space_handle;
  friend class explicit_index_space_iterator;
  friend class explicit_index_space_state;
  friend class forwarding_index_space_handle;
  friend class id_space_names_record;
  friend class implicit_index_space_iterator;
  friend class index_space_family_iterator;
  friend class index_space_handle;
  friend class index_space_iterator;
  friend class poset_state_handle; // Uses new_primary_state
  friend class poset_crg_state; // Uses new_primary_state
  friend class primary_sum_index_space_state;
  friend SHEAF_DLL_SPEC size_t deep_size(const index_space_family& xfamily, bool xinclude_shallow);

  // ===========================================================
  /// @name INDEX_SPACE_FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// Default constructor
  ///
  index_space_family();

  ///
  /// Destructor
  ///
  virtual ~index_space_family();

  ///
  /// The name for id xid.
  ///
  string name(pod_type xid) const;

  /// @todo Add an interface for accessing all possible names.

  ///
  /// The index for name xname.
  ///
  pod_type index(const string& xname) const;

  ///
  /// Associate name xname with id space index xid.
  ///
  void put_name(pod_type xid, const string& xname);

  ///
  /// True, if this contains an id space with id xid.
  ///
  bool contains(pod_type xid) const;

  ///
  /// True, if this contains an id space with name xname.
  ///
  bool contains(const string& xname) const;

  ///
  /// The beginning index of the id spaces.
  ///
  pod_type begin() const;

  ///
  /// The ending index of the id spaces.
  ///
  pod_type end() const;

  ///
  /// True if and only if all the id spaces are standard id spaces.
  ///
  bool has_only_standard_id_spaces() const;

  ///
  /// Update the initially allocated id spaces.
  ///
  void update_standard_id_spaces();

  ///
  /// Clear all the non-standard id spaces in this family.
  ///
  void clear_id_spaces();

  ///
  /// Maximum number of representive ids which are permitted by the stream
  /// insertion operator to output the equivalence class.
  ///
  static size_type& max_rep_ids();

protected:

  ///
  /// Copy constructor; disabled.
  ///
  index_space_family(const index_space_family& xother) { };

  ///
  /// Map from name to id space index.
  ///
  name_multimap _name_to_index;

  ///
  /// Ending index of the id spaces.
  ///
  pod_type _end;

  ///
  /// Ending index of the standard id spaces.
  ///
  pod_type _standard_end;

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

  /// @todo Remove.
//   ///
//   /// Creates a new secondary id space state with name xname, id space state
//   /// of type xstate_class_name and initialization arguments, xstate_args.
//   /// Returns the index of the id space state created.
//   /// @depreciated Use new_space constructors.
//   ///
//   pod_type new_secondary_state(const string& xname,
// 			       const string& xstate_class_name,
// 			       const arg_list& xstate_args,
// 			       bool xis_persistent);

//   ///
//   /// Creates a new secondary id space state at id space index xid
//   /// with name xname, id space state of type xstate_class_name and
//   /// initialization arguments, xstate_args.
//   /// Returns the index of the id space state created.
//   /// @depreciated Use new_space constructors.
//   ///
//   pod_type new_secondary_state(pod_type xid,
// 			       const string& xname,
// 			       const string& xstate_class_name,
// 			       const arg_list& xstate_args,
// 			       bool xis_persistent);

  ///
  /// Creates a new secondary id space interval with xub reserved id spaces,
  /// id space interval of type xinterval_class_name and initialization
  /// arguments, xinterval_args.
  /// Returns the index of the first id space state in the interval created.
  ///
  pod_type new_secondary_interval(const string& xinterval_class_name,
				  const arg_list& xinterval_args,
				  size_type xub);

  ///
  /// Delete the primary id space state with index xid.
  ///
  void delete_primary_state(pod_type xid);

  ///
  /// Delete the secondary id space state with name xname.
  ///
  void delete_secondary_state(const string& xname);

  ///
  /// Delete the secondary id space state with index xid.
  ///
  void delete_secondary_state(pod_type xid);

  ///
  /// Delete the secondary id space interval contains index xid.
  ///
  void delete_secondary_interval(pod_type xid);

  ///
  /// True, if and only if the id space interval that contains index xid
  /// is an explicit interval.
  ///
  bool is_explicit_interval(pod_type xid);

protected:

  ///
  /// Creates a new primary id space state with xct number of ids.
  /// Returns the index of the id space state created.
  ///
  pod_type new_primary_state(size_type xct);

  ///
  /// Creates a new primary id space state [xid, xid+xct).
  /// Returns the index of the id space state created.
  ///
  pod_type new_primary_state(pod_type xid, size_type xct);

  ///
  /// Create a new id space with class type xstate_class_name and
  /// name xname.  Used by the I/O system to read secondary id spaces.
  ///
  void new_state(const string& xname, const string& xstate_class_name);

  /// @todo Remove.
//   ///
//   /// Create a new id space state with class type xstate_class_name, arguments
//   /// xstate_args and name xname.
//   /// @depreciated Use new_space constructors.
//   ///
//   pod_type new_state(const string& xname,
// 		     const string& xstate_class_name,
// 		     const arg_list& xstate_args,
// 		     bool xis_persistent);

//   ///
//   /// Create a new id space state at id space index xid with class type
//   /// xstate_class_name, arguments xstate_args and name xname.
//   /// @depreciated Use new_space constructors.
//   ///
//   pod_type new_state(pod_type xid,
// 		     const string& xname,
// 		     const string& xstate_class_name,
// 		     const arg_list& xstate_args,
// 		     bool xis_persistent);

  ///
  /// Creates a new sid space interval with xub reserved id spaces,
  /// id space interval of type xinterval_class_name and initialization
  /// arguments, xinterval_args.
  /// Returns the index of the first id space state in the interval created.
  ///
  pod_type new_interval(const string& xinterval_class_name,
			const arg_list& xinterval_args,
			size_type xub);

  ///
  /// Delete the state with id xid.
  ///
  void delete_state(pod_type xid);

  ///
  /// Id space collection for id xid (const version).
  ///
  const index_space_collection* collection(pod_type xid) const;

  ///
  /// Id space collection for id xid (mutable version).
  ///
  index_space_collection* collection(pod_type xid);

  ///
  /// Reserve the next available id for an explicit index space.
  ///
  pod_type reserve_next_explicit_id();

  ///
  /// Size of the explicit id space intervals.
  ///
  static size_type explicit_interval_size();

  ///
  /// Type of interval map.
  ///
  typedef map<pod_type, index_space_interval*> interval_map_type;

  ///
  /// Type of interval map iterator.
  ///
  typedef interval_map_type::iterator interval_iterator_type;

  ///
  /// Type of interval map iterator.
  ///
  typedef interval_map_type::const_iterator const_interval_iterator_type;

  ///
  /// Map from id to id space interval.
  ///
  interval_map_type _intervals;

  ///
  /// The current explicit id space interval.
  ///
  explicit_index_space_interval* _explicit_interval;

  ///
  /// The next available id for an explicit index space.
  ///
  pod_type _next_explicit_id;

private:

  //@}


  // ===========================================================
  /// @name HUB ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocate the next available id in this family.
  ///
  pod_type new_id();

  ///
  /// Allocate an xid in this family.
  ///
  pod_type new_id(pod_type xid);

  ///
  /// Deallocate the id xid in this family.
  ///
  void delete_id(pod_type xid);

  ///
  /// The hub id space of this family.
  ///
  const hub_index_space_handle& hub_id_space() const;

  ///
  /// Create a gathered hub id space for this family.
  /// If xexclude_bottom, construct the id space without BOTTOM_INDEX.
  ///
  const index_space_handle& new_gathered_hub_id_space(bool xexclude_bottom);

  ///
  /// Update the gathered hub id space.
  ///
  void update_gathered_hub_id_space();

  ///
  /// A secondary id space that is a gathered version of the hub id space.
  ///
  const index_space_handle& gathered_hub_id_space() const;

  ///
  /// True if there is a gathered hub id space for this family.
  ///
  bool has_gathered_hub_id_space() const;

  ///
  /// True, if the gathered hub id space excludes BOTTOM_INDEX.
  ///
  bool gathered_hub_id_space_excludes_bottom() const;

  ///
  /// Name of the hub id space.
  ///
  static const string& hub_id_space_name();

  ///
  /// True if and only if the reserved term containing xid is
  /// already a reserved term or is available for allocation.
  ///
  bool is_valid_reserved_id(pod_type xid) const;

  ///
  /// The term in the hub id space containing id xid.
  ///
  const index_space_handle& term_of(pod_type xid) const;

  ///
  /// The term in the hub id space containing id xid.
  ///
  const index_space_handle& term_of(const scoped_index& xid) const;

  ///
  /// The last term in the hub id space.
  ///
  const index_space_handle& last_term() const;

  ///
  /// Extends the last term to to ct == xct.
  /// @hack A temporary method to support extension
  /// of section space schema when the underlying base
  /// space is extended.
  ///
  void extend_last_term(size_type xct);

protected:

  ///
  /// The hub id space.
  ///
  hub_index_space_handle _hub_id_space;

  ///
  /// The gathered hub id space.
  ///
  interval_index_space_handle _gathered_hub_id_space;

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of members for the id space with name xname.
  ///
  size_type ct(const string& xname) const;

  ///
  /// The number of members for the id space with id xspace_id.
  ///
  size_type ct(pod_type xspace_id) const;

  ///
  /// True if there are no ids in the space with name xname.
  ///
  bool is_empty(const string& xname) const;

  ///
  /// True if there are no ids in the space with id xspace_id.
  ///
  bool is_empty(pod_type xspace_id) const;

  ///
  /// Beginning id of the space with name xname.
  ///
  pod_type begin(const string& xname) const;

  ///
  /// Beginning id of the space with id xspace_id.
  ///
  pod_type begin(pod_type xspace_id) const;

  ///
  /// Ending id of the space with name xname.
  ///
  pod_type end(const string& xname) const;

  ///
  /// Ending id of this the with id xspace_id.
  ///
  pod_type end(pod_type xspace_id) const;

  ///
  /// Beginning id of the space in the hub id space with name xname.
  ///
  pod_type hub_begin(const string& xname) const;

  ///
  /// Beginning id of the space in the hub id space with id xspace_id.
  ///
  pod_type hub_begin(pod_type xspace_id) const;

  ///
  /// True if begin(xspace_id) == 0 and end(xspace_id) == ct(xspace_id).
  ///
  bool is_gathered(const string& xname) const;
    
  ///
  /// True if begin(xspace_id) == 0 and end(xspace_id) == ct(xspace_id).
  ///
  bool is_gathered(pod_type xspace_id) const;
    
  ///
  /// True if the space with name xname contains id xid.
  ///
  bool contains(const string& xname, pod_type xid) const;

  ///
  /// True if the space with id xspace_id contains id xid.
  ///
  bool contains(pod_type xspace_id, pod_type xid) const;

  ///
  /// True if the space with name xname contains an id equivalent to xid.
  /// synonym for contains_hub(xspace_id, xid.hub_pod()).
  ///
  bool contains(const string& xname, const scoped_index& xid) const;

  ///
  /// True if the space with id xspace_id contains an id equivalent to xid.
  /// synonym for contains_hub(xspace_id, xid.hub_pod()).
  ///
  bool contains(pod_type xspace_id, const scoped_index& xid) const;

  ///
  /// True if the space with name xname contains an id equivalent
  /// to xid in the unglued hub id space.
  /// synonym for contains_unglued_hub(xname, xid).
  ///
  bool contains_hub(const string& xname, pod_type xid) const;

  ///
  /// True if the space with id xspace_id contains an id equivalent
  /// to xid in the unglued hub id space.
  /// synonym for contains_unglued_hub(xspace_id, xid).
  ///
  bool contains_hub(pod_type xspace_id, pod_type xid) const;

  ///
  /// True if the space with name xname contains an id equivalent
  /// to xid in the unglued hub id space.
  ///
  bool contains_unglued_hub(const string& xname, pod_type xid) const;

  ///
  /// True if the space with id xspace_id contains an id equivalent
  /// to xid in the unglued hub id space.
  ///
  bool contains_unglued_hub(pod_type xspace_id, pod_type xid) const;

  ///
  /// True if the space with name xname contains an id equivalent
  /// to xid in the glued hub id space.
  ///
  bool contains_glued_hub(const string& xname, pod_type xid) const;

  ///
  /// True if the space with id xspace_id contains an id equivalent
  /// to xid in the glued hub id space.
  ///
  bool contains_glued_hub(pod_type xspace_id, pod_type xid) const;

  ///
  /// True if the space with name xname contains an id xid equivalent
  /// to xhub_id in the hub id space.
  /// synonym for contains(xspace_id, xid, xhub_id.hub_pod()).
  ///
  bool contains(const string& xname, pod_type xid, const scoped_index& xhub_id) const;

  ///
  /// True if the space with id xspace_id contains an id xid equivalent
  /// to xhub_id in the hub id space.
  /// synonym for contains(xspace_id, xid, xhub_id.hub_pod()).
  ///
  bool contains(pod_type xspace_id, pod_type xid, const scoped_index& xhub_id) const;

  ///
  /// True if the space with name xname contains an id xid equivalent
  /// to xhub_id in the hub id space.
  ///
  bool contains(const string& xname, pod_type xid, pod_type xhub_id) const;

  ///
  /// True if the space with id xspace_id contains an id xid equivalent
  /// to xhub_id in the hub id space.
  ///
  bool contains(pod_type xspace_id, pod_type xid, pod_type xhub_id) const;

  ///
  /// The pod index in the space with name xname equivalent to
  /// xid in the hub id space.
  ///
  pod_type pod(const string& xname, pod_type xid) const;

  ///
  /// The pod index in the space with id xspace_id equivalent to
  /// xid in the hub id space.
  ///
  pod_type pod(pod_type xspace_id, pod_type xid) const;

  ///
  /// The pod index in the space with name xname equivalent to xid.
  /// synonym for pod(xxspace_id, id.hub_pod()).
  ///
  pod_type pod(const string& xname, const scoped_index& xid) const;

  ///
  /// The pod index in the space with id xspace_id equivalent to xid.
  /// synonym for pod(xxspace_id, id.hub_pod()).
  ///
  pod_type pod(pod_type xspace_id, const scoped_index& xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in the id space
  /// with name xname.
  /// synonym for unglued_hub_pod(xname, xid).
  ///
  pod_type hub_pod(const string& xname, pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in the id space
  /// with id xspace_id.
  /// synonym for unglued_hub_pod(xspace_id, xid).
  ///
  pod_type hub_pod(pod_type xspace_id, pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in the id space
  /// with name xname.
  ///
  pod_type unglued_hub_pod(const string& xname, pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in the id space
  /// with id xspace_id.
  ///
  pod_type unglued_hub_pod(pod_type xspace_id, pod_type xid) const;

  ///
  /// The pod index in the glued hub id space equivalent to xid in the id space
  /// with name xname.
  ///
  pod_type glued_hub_pod(const string& xname, pod_type xid) const;

  ///
  /// The pod index in the glued hub id space equivalent to xid in the id space
  /// with id xspace_id.
  ///
  pod_type glued_hub_pod(pod_type xspace_id, pod_type xid) const;

  ///
  /// True if the id space with name xname should be written to disk.
  ///
  bool is_persistent(const string& xname) const;

  ///
  /// True if the id space with id xspace_id should be written to disk.
  ///
  bool is_persistent(pod_type xspace_id) const;

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
  /// Ture if there is any gluing in the hub id space.
  ///
  bool has_gluing() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name PRODUCT STRUCTURE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a new product structure for the id space with name xname
  /// by cloning the product structure, xproduct.
  ///
  void new_product_structure(const string& xname,
			     const abstract_product_structure& xproduct);

  ///
  /// Creates a new product structure for the id space with id xspace_id
  /// by cloning the product structure, xproduct.
  ///
  void new_product_structure(pod_type xspace_id,
			     const abstract_product_structure& xproduct);

  ///
  /// Deletes the product structure for the id space with name xname.
  ///
  void delete_product_structure(const string& xname);

  ///
  /// Deletes the product structure for the id space with id xspace_id.
  ///
  void delete_product_structure(pod_type xspace_id);

  ///
  /// The product structure for the id space with name xname (const version).
  ///
  const abstract_product_structure& product_structure(const string& xname) const;

  ///
  /// The product structure for the id space with id xspace_id (const version).
  ///
  const abstract_product_structure& product_structure(pod_type xspace_id) const;

  ///
  /// The product structure for the id space with name xname (mutable version).
  ///
  abstract_product_structure& product_structure(const string& xname);

  ///
  /// The product structure for the id space with id xspace_id (mutable version).
  ///
  abstract_product_structure& product_structure(pod_type xspace_id);

  ///
  /// The product structure of type T for the id space with name xname (const version).
  ///
  template<typename T>
  const T& product_structure(const string& xname) const;

  ///
  /// The product structure of type T for the id space with id xspace_id (const version).
  ///
  template<typename T>
  const T& product_structure(pod_type xspace_id) const;

  ///
  /// The product structure of type T for the id space with name xname (mutable version).
  ///
  template<typename T>
  T& product_structure(const string& xname);

  ///
  /// The product structure of type T for the id space with id xspace_id (mutable version).
  ///
  template<typename T>
  T& product_structure(pod_type xspace_id);

  ///
  /// True if the id space with name xname has a product structure.
  ///
  bool has_product_structure(const string& xname) const;

  ///
  /// True if the id space with id xspace_id has a product structure.
  ///
  bool has_product_structure(pod_type xspace_id) const;

  ///
  /// True if the product structure for the id space with name xname
  /// conforms to type T.
  ///
  template<typename T>
  bool product_structure_conforms_to(const string& xname) const;

  ///
  /// True if the product structure for the id space with id xspace_id
  /// conforms to type T.
  ///
  template<typename T>
  bool product_structure_conforms_to(pod_type xspace_id) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space handle from the handle pool attached to state
  /// with name xname.
  ///
  index_space_handle& get_id_space(const string& xname) const;

  ///
  /// Allocates an id space handle from the handle pool attached to state
  /// with id xspace_id.
  ///
  index_space_handle& get_id_space(pod_type xspace_id) const;

  ///
  /// Allocates an id space handle of type T from the handle pool attached
  /// to state with name xname.
  ///
  template<typename T>
  T& get_id_space(const string& xname) const;

  ///
  /// Allocates an id space handle of type T from the handle pool attached
  /// to state with id xspace_id.
  ///
  template<typename T>
  T& get_id_space(pod_type xspace_id) const;

  ///
  /// True if handle of type T conforms to the state with name xname.
  ///
  template<typename T>
  bool handle_conforms_to_state(const string& xname) const;

  ///
  /// True if handle of type T conforms to the state with id xspace_id.
  ///
  template<typename T>
  bool handle_conforms_to_state(pod_type xspace_id) const;

  ///
  /// Returns the id space handle xid_space to the handle pool.
  ///
  void release_id_space(index_space_handle& xid_space) const;

  ///
  /// True if and only if id space handle xid_space was allocated by
  /// the handle pool.
  ///
  bool allocated_id_space(const index_space_handle& xid_space) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ITERATOR POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Allocates an id space iterator from the iterator pool attached
  /// to state with name xname.
  ///
  index_space_iterator& get_id_space_iterator(const string& xname) const;

  ///
  /// Allocates an id space iterator from the iterator pool attached
  /// to state with id xspace_id.
  ///
  index_space_iterator& get_id_space_iterator(pod_type xspace_id) const;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  void release_id_space_iterator(index_space_iterator& xitr) const;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the iterator pool.
  ///
  bool allocated_id_space_iterator(const index_space_iterator& xitr) const;

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
/// Insert index_space_family& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const index_space_family& xfamily);

///
/// The deep size of index_space_family& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const index_space_family& xfamily, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef INDEX_SPACE_FAMILY_H
