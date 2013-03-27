// $RCSfile: implicit_crg_range.h,v $ $Revision: 1.19 $ $Date: 2013/01/14 16:03:37 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class implicit_crg_range
///
/// @deprecated crg_ranges have been replaced with crg_intervals.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef IMPLICIT_CRG_RANGE_H
#define IMPLICIT_CRG_RANGE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef OFFSET_INDEX_SPACE_HANDLE_H
#include "offset_index_space_handle.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef SINGLETON_INDEX_SPACE_HANDLE_H
#include "singleton_index_space_handle.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif


namespace sheaf
{

template <typename T>
class factory;

class arg_list;
class index_space_collection;
class interval_index_space_handle;
class poset_state_handle;
class namespace_poset;

// Forward declarations to support friend declaration.

class implicit_crg_range;

///
/// Insert implicit_crg_range& m into ostream& os.
///
ostream& operator <<(ostream& os, const implicit_crg_range& m);

///
/// Abstract emulator for an range of implicit cover relation graph members.
///
class SHEAF_DLL_SPEC implicit_crg_range : public any
{

  friend ostream& operator <<(ostream& os, const implicit_crg_range& m);
  friend SHEAF_DLL_SPEC size_t deep_size(const implicit_crg_range& xp, bool xinclude_shallow);
  friend class poset_crg_state;   // uses force_explicit_cover_set
  
  // ===========================================================
  /// @name IMPLICIT_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor; creates an instance with size() == 0;
  ///
  implicit_crg_range();

  ///
  /// Destructor
  ///
  virtual ~implicit_crg_range();

protected:

private:

  //@}


  // ===========================================================
  /// @name RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The beginning of the member range; this emulates
  /// members in the range [begin(), end()), includes range member.
  ///
  pod_index_type begin() const;

  ///
  /// The beginning of the member range; this emulates
  /// members in the range [begin(), end()), includes range member.
  ///
  void begin(scoped_index& result) const;

  ///
  /// The beginning of the implicit member range 
  /// (begin(), end()), excludes range member;
  /// synonym for begin() + 1.
  ///
  pod_index_type implicit_begin() const;

  ///
  /// The beginning of the implicit member range 
  /// (begin(), end()), excludes range member;
  /// synonym for begin() + 1.
  ///
  void implicit_begin(scoped_index& result) const;

  ///
  /// The end of the member range.
  ///
  pod_index_type end() const;

  ///
  /// The end of the member range.
  ///
  void end(scoped_index& result) const;

  ///
  /// The index of the range member itself;
  /// synonym for begin().
  ///
  pod_index_type range_member() const;

  ///
  /// The index of the range member itself;
  /// synonym for begin().
  ///
  void range_member(scoped_index& result) const;

  ///
  /// True if xindex is the range member.
  ///
  bool is_range_member(pod_index_type xindex) const;

  ///
  /// True if xindex is the range member.
  ///
  bool is_range_member(const scoped_index& xindex) const;

  ///
  /// The number of members in the implicit member range.
  ///
  size_type size() const;

  ///
  /// True if and only if the index xindex
  /// is contained in this range.
  ///
  bool contains_member(pod_index_type xindex) const;

  ///
  /// True if and only if the index xindex
  /// is contained in this range.
  ///
  bool contains_member(const scoped_index& xindex) const;

  ///
  /// The atoms id space for this range.
  ///
  virtual const index_space_handle& atoms() const = 0;

  /// @todo Remove.

//   ///
//   /// An iterator over the atoms in this range.
//   ///
//   virtual cover_set_iterator atoms() const = 0;

  ///
  /// The id space family for this range.
  ///
  const index_space_family& id_spaces() const;

  ///
  /// The hub id space of this range.
  ///
  const hub_index_space_handle& hub_id_space() const;

  ///
  /// Set the index space family to xid_spaces.
  ///
  void initialize_id_spaces(index_space_family& xid_spaces);

  ///
  /// True if the index space family has been initialized.
  ///
  bool id_spaces_initialized() const;

protected:

  ///
  /// The id space family of this range.
  ///
  index_space_family* _id_spaces;

  ///
  /// True if the id space family has been initialized.
  ///
  bool _id_spaces_initialized;

  ///
  /// The id space collection for space with id xid.
  ///
  index_space_collection* collection(pod_index_type xid);

private:

  //@}


  // ===========================================================
  /// @name LOCAL ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The reserved name for the local id space of
  /// the ramge member with index xindex.
  ///
  static string local_id_space_name(pod_index_type xindex);

  ///
  /// The local id space of this range.
  ///
  const offset_index_space_handle& local_id_space() const;

  ///
  /// Sets the local id space to xlocal_id_space
  /// and initializes local ids.
  ///
  void initialize_local_id_space(const index_space_handle& xlocal_id_space);

  ///
  /// True if local id space has been initialized
  ///
  bool local_id_space_initialized() const;

protected:

  ///
  /// The id space of this range.
  ///
  offset_index_space_handle _local_id_space;

  ///
  /// True if local id space has been initialized
  ///
  bool _local_id_space_initialized;

private:

  //@}


  // ===========================================================
  /// @name RANGE MEMBER ID SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The reserved name for the range_member id space of
  /// the ramge member with index xindex.
  ///
  static string range_member_id_space_name(pod_index_type xindex);

  ///
  /// The range_member id space of this range.
  ///
  const singleton_index_space_handle& range_member_id_space() const;

  ///
  /// Sets the range_member id space.
  ///
  void initialize_range_member_id_space();

  ///
  /// True if range_member id space has been initialized
  ///
  bool range_member_id_space_initialized() const;

protected:

  ///
  /// The id space of this range.
  ///
  singleton_index_space_handle _range_member_id_space;

  ///
  /// True if range_member id space has been initialized
  ///
  bool _range_member_id_space_initialized;

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false)
  /// cover of the member with index xmbr_index is explicit.
  ///
  bool cover_is_explicit(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false)
  /// cover of the member with index xmbr_index is explicit.
  ///
  bool cover_is_explicit(bool xlower, const scoped_index& xmbr_index) const;

  /// @todo Remove.  These functions are now handle by quering the cover id
  /// space in poset_crg_state.

//   // $$SCRIBBLE: implicit-cover-reorganization
//   // Made functions non-virtual.

//   ///
//   /// Iterator for lower (xlower true) or upper (xlower false) cover set
//   /// of the member with index xmbr_index.
//   ///
//   cover_set_iterator cover_iterator(bool xlower,
// 				    pod_index_type xmbr_index) const;

//   ///
//   /// Iterator for lower (xlower true) or upper (xlower false) cover set
//   /// of the member with index xmbr_index.
//   ///
//   cover_set_iterator cover_iterator(bool xlower,
// 				    const scoped_index& xmbr_index) const;

//   ///
//   /// True if and only if the lower (xlower true) or
//   /// upper (xlower false) cover set of the member with index xmbr_index.
//   /// is the domain of iterator xitr.
//   ///
//   bool cover_contains_iterator(bool xlower,
// 			       pod_index_type xmbr_index,
// 			       const cover_set_iterator& xitr) const;

//   ///
//   /// True if and only if the lower (xlower true) or
//   /// upper (xlower false) cover set of the member with index xmbr_index.
//   /// is the domain of iterator xitr.
//   ///
//   bool cover_contains_iterator(bool xlower,
// 			       const scoped_index& xmbr_index,
// 			       const cover_set_iterator& xitr) const;

//   ///
//   /// True if and only if the lower (xlower true) or upper (xlower false)
//   /// cover set of the member with index xmbr_index is empty.
//   ///
//   bool cover_is_empty(bool xlower, pod_index_type xmbr_index) const;

//   ///
//   /// True if and only if the lower (xlower true) or upper (xlower false)
//   /// cover set of the member with index xmbr_index is empty.
//   ///
//   bool cover_is_empty(bool xlower, const scoped_index& xmbr_index) const;

//   ///
//   /// True if and only if the lower (xlower true) or
//   /// upper (xlower false) cover set contains exactly one member.
//   ///
//   bool cover_is_singleton(bool xlower,
// 			  pod_index_type xmbr_index) const;

//   ///
//   /// True if and only if the lower (xlower true) or
//   /// upper (xlower false) cover set contains exactly one member.
//   ///
//   bool cover_is_singleton(bool xlower, const scoped_index& xmbr_index) const;

//   ///
//   /// The number of members in the lower (xlower true) or
//   /// upper (xlower false) cover set.
//   ///
//   size_type cover_size(bool xlower, pod_index_type xmbr_index) const;

//   ///
//   /// The number of members in the lower (xlower true) or
//   /// upper (xlower false) cover set.
//   ///
//   size_type cover_size(bool xlower, const scoped_index& xmbr_index) const;

//   ///
//   /// True if and only if the lower (xlower true) or
//   /// upper (xlower false) cover set contains xindex.
//   ///
//   bool cover_contains_member(bool xlower,
// 			     pod_index_type xmbr_index,
// 			     pod_index_type xother_index) const;

//   ///
//   /// True if and only if the lower (xlower true) or
//   /// upper (xlower false) cover set contains xindex.
//   ///
//   bool cover_contains_member(bool xlower,
// 			     const scoped_index& xmbr_index,
// 			     const scoped_index& xother_index) const;

//   ///
//   /// The first member of the lower (xlower true) or upper (xlower false) cover.
//   ///
//   pod_index_type first_cover_member(bool xlower,
// 				    pod_index_type xmbr_index) const;

protected:

  // $$SCRIBBLE: Cover set id space.

  ///
  /// The id space for the lower (xlower true) or upper (xlower false) cover
  /// of member with index xmbr_index.
  ///
  const index_space_handle& cover_id_space(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// The explicit lower (xlower true) or upper (xlower false) cover id space
  /// of the member with index xmbr_index; creates an explict cover id space
  /// if the cover id space is not already explicit and, if xinitialize,
  /// initializes it with the contents of the implicit cover id space, if any.
  ///
  mutable_index_space_handle& force_explicit_cover(bool xlower,
						   pod_index_type xmbr_index,
						   bool xinitialize = true);

  ///
  /// The implicit id space for the lower (xlower true) or upper (xlower false) cover
  /// of member with index xmbr_index.
  ///
  virtual const index_space_handle&
  implicit_cover_id_space(bool xlower, pod_index_type xmbr_index) const  = 0;

  ///
  /// The explicit lower (xlower true) or upper (xlower false) cover id space
  /// of the member with index xmbr_index; creates an explict cover id space
  /// if xinitialize, initializes it with the contents of the implicit cover
  /// id space.
  ///
  interval_index_space_handle&
  new_explicit_cover(bool xlower, pod_index_type xmbr_index, bool xinitialize = true);

  ///
  /// Initialize the explicit lower (xlower true) or upper (xlower false)
  /// cover id space xcover of the member with index xmbr_index.
  ///
  virtual void initialize_explicit_cover(bool xlower,
					 pod_index_type xmbr_index,
					 interval_index_space_handle& xcover) const = 0;

  /// @todo Remove.

//   // $$SCRIBBLE: implicit-cover-reorganization
//   // Added explicit cover set functions.

//   ///
//   /// The explicit lower (xlower true) or upper (xlower false) cover set
//   /// of the member with index xmbr_index; null if the cover set is not explicit.
//   ///
//   explicit_cover_set_adapter* explicit_cover_set(bool xlower, pod_index_type xmbr_index) const;

//   ///
//   /// The explicit lower (xlower true) or upper (xlower false) cover set
//   /// of the member with index xmbr_index; null if the cover set is not explicit.
//   ///
//   explicit_cover_set_adapter* explicit_cover_set(bool xlower, const scoped_index& xmbr_index) const;

//   ///
//   /// The explicit lower (xlower true) or upper (xlower false) cover set
//   /// of the member with index xmbr_index; creates an explict cover set
//   /// if the cover set is not already explicit and, if xinitialize,
//   /// initializes it with the contents of the implicit cover set, if any.
//   ///
//   explicit_cover_set_adapter* force_explicit_cover_set(bool xlower,
// 						       pod_index_type xmbr_index,
// 						       bool xinitialize = true);

//   ///
//   /// The explicit lower (xlower true) or upper (xlower false) cover set
//   /// of the member with index xmbr_index; creates an explict cover set
//   /// if the cover set is not already explicit and, if xinitialize,
//   /// initializes it with the contents of the implicit cover set, if any.
//   ///
//   explicit_cover_set_adapter* force_explicit_cover_set(bool xlower,
// 						       const scoped_index& xmbr_index,
// 						       bool xinitialize = true);

//   // $$SCRIBBLE: implicit-cover-reorganization
//   // Added implicit functions.

//   ///
//   /// Iterator for lower (xlower true) or upper (xlower false) cover set
//   /// of the member with index xmbr_index.
//   ///
//   virtual cover_set_iterator implicit_cover_iterator(bool xlower,
// 						     pod_index_type xmbr_index) const = 0;
  
//   ///
//   /// True if and only if the lower (xlower true) or
//   /// upper (xlower false) cover set of the member with index xmbr_index.
//   /// is the domain of iterator xitr.
//   ///
//   virtual bool implicit_cover_contains_iterator(bool xlower,
// 						pod_index_type xmbr_index,
// 						const cover_set_iterator& xitr) const = 0;

//   ///
//   /// True if and only if the lower (xlower true) or upper (xlower false)
//   /// cover set of the member with index xmbr_index is empty.
//   ///
//   virtual bool implicit_cover_is_empty(bool xlower, pod_index_type xmbr_index) const = 0;

//   ///
//   /// True if and only if the lower (xlower true) or
//   /// upper (xlower false) cover set contains exactly one member.
//   ///
//   virtual bool implicit_cover_is_singleton(bool xlower,
// 					   pod_index_type xmbr_index) const = 0;

//   ///
//   /// The number of members in the lower (xlower true) or
//   /// upper (xlower false) cover set.
//   ///
//   virtual size_type implicit_cover_size(bool xlower, pod_index_type xmbr_index) const = 0;

//   ///
//   /// True if and only if the lower (xlower true) or
//   /// upper (xlower false) cover set contains xindex.
//   ///
//   virtual bool implicit_cover_contains_member(bool xlower,
// 					      pod_index_type xmbr_index,
// 					      pod_index_type xother_index) const = 0;

//   ///
//   /// The first member of the lower (xlower true) or upper (xlower false) cover.
//   ///
//   virtual pod_index_type implicit_first_cover_member(bool xlower,
// 						     pod_index_type xmbr_index) const = 0;

private:

  ///
  /// The type of the explicit cover maps..
  ///
  typedef hash_map<pod_index_type, interval_index_space_handle*> explicit_cover_map_type;

  ///
  /// The map from ids to explicit upper cover id spaces.
  ///
  explicit_cover_map_type _explicit_upper_cover_map;

  ///
  /// The map from ids to explicit lower cover id spaces.
  ///
  explicit_cover_map_type _explicit_lower_cover_map;

  ///
  /// The lower (xlower true) or upper (xlower false) map to explicit cover id spaces.
  ///
  inline explicit_cover_map_type* explicit_cover_map(bool xlower)
  {
    return (xlower ? &_explicit_lower_cover_map : &_explicit_upper_cover_map);
  };

  ///
  /// The lower (xlower true) or upper (xlower false) map to explicit cover id spaces; const version
  ///
  inline const explicit_cover_map_type* explicit_cover_map(bool xlower) const
  {
    return (xlower ? &_explicit_lower_cover_map : &_explicit_upper_cover_map);
  };

  //@}


  // ===========================================================
  /// @name DOF_TUPLE_ID FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if the member with index xmbr_index is join-irreducible.
  ///
  virtual bool is_jim(pod_index_type xmbr_index) const = 0;

  ///
  /// True if and only if the member with index xmbr_index is join-irreducible.
  ///
  bool is_jim(const scoped_index& xmbr_index) const;

  ///
  /// The dof tuple id of the member with index xmbr_index.
  ///
  virtual const scoped_index& dof_tuple_id(pod_index_type xmbr_index) const = 0;

  ///
  /// The dof tuple id of the member with index xmbr_index.
  ///
  const scoped_index& dof_tuple_id(const scoped_index& xmbr_index) const;

  ///
  /// The ids of the dof tuples associated with this range.
  ///
  block<scoped_index>& dof_tuple_ids();

  ///
  /// The ids of the dof tuples associated with this range; const version.
  ///
  const block<scoped_index>& dof_tuple_ids() const;

  ///
  /// True if dof tuple ids have been initialized
  ///
  bool dof_tuple_ids_initialized() const;

  ///
  /// Allocates and initializes dof_tuple_ids() with xdof_tuple_ids.
  ///
  void initialize_dof_tuple_ids(const block<scoped_index>& xdof_tuple_ids);

protected:

  ///
  /// The ids of the dof tuples associated with this range.
  ///
  block<scoped_index> _dof_tuple_ids;

  ///
  /// True if dof tuple ids have been initialized
  ///
  bool _dof_tuple_ids_initialized;

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Removes members of the cover that are no longer members of the crg.
  ///
  void clean_cover(bool xlower, pod_index_type xmbr_index);

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIVATE_DATA FACET
  // ===========================================================
  //@{

public:

  // $$SCRIBBLE: implicit-cover-reorganization
  // Made private data functions non-virtual.

  ///
  /// The size of the private data.
  ///
  size_type private_data_size() const;

  ///
  /// Initializes this using private data xdata.
  ///
  void get_private_data(block<pod_index_type>& xdata) const;

  ///
  /// Initializes this using private data xdata.
  ///
  void put_private_data(const block<pod_index_type>& xdata);

  ///
  /// True if private data has been initialized
  ///
  bool private_data_initialized() const;

protected:

  // $$SCRIBBLE: implicit-cover-reorganization
  // Added implicit private data function

  ///
  /// The size of the private data.
  ///
  virtual size_type implicit_private_data_size() const = 0;

  ///
  /// Initializes this using private data xdata.
  ///
  virtual void get_implicit_private_data(block<pod_index_type>& xdata) const = 0;

  ///
  /// Initializes this using private data xdata.
  ///
  virtual void put_implicit_private_data(const block<pod_index_type>& xdata) = 0;

  ///
  /// True if private data has been initialized
  ///
  bool _private_data_initialized;

private:

  //@}


  // ===========================================================
  /// @name FINIALIZE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Finialize the initialization of this crg range in the host xhost.
  ///
  virtual void finalize(poset_state_handle& xhost);

protected:

  ///
  /// True if the initialization of this crg range has been finalized.
  ///
  bool _is_finalized;

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// A factory for making descendants of this class.
  ///
  static factory<implicit_crg_range>& range_factory();

  ///
  /// Creates a default constructed instance of the
  /// the class with name xname.
  ///
  static implicit_crg_range* new_range(const string& xname);

  ///
  /// Sets is_initialized() == true;
  /// dummy routine provided to satisfy factory template.
  ///
  void initialize(const namespace_poset& xnamespace);

  ///
  /// True if fully initialized.
  ///
  virtual bool is_initialized() const;

  ///
  /// The name of this class;
  /// provided to satisfy factory template.
  ///
  virtual const string& class_name() const;

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
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual implicit_crg_range* clone() const = 0;

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
/// The deep size of the referenced object of type implicit_crg_range;
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC 
size_t deep_size(const implicit_crg_range& xp, bool xinclude_shallow = true);

} // namespace sheaf

#endif // ifndef IMPLICIT_CRG_RANGE_H
