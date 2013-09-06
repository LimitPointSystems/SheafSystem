

//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Interface for class crg_interval

#ifndef CRG_INTERVAL_H
#define CRG_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef PRIMARY_INDEX_SPACE_HANDLE_H
#include "primary_index_space_handle.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
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

class poset_state_handle;
class namespace_poset;

// Forward declarations to support friend declaration.

class crg_interval;

///
/// Insert crg_interval& m into ostream& os.
///
ostream& operator <<(ostream& os, const crg_interval& m);

///
/// Abstract emulator for an interval of cover relation graph members.
///
class SHEAF_DLL_SPEC crg_interval : public any
{

  friend ostream& operator <<(ostream& os, const crg_interval& m);
  friend SHEAF_DLL_SPEC size_t deep_size(const crg_interval& xp, bool xinclude_shallow);
  friend class poset_crg_state;   // uses cover_name
  
  // ===========================================================
  /// @name CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor; constructs an uninitialized interval.
  ///
  crg_interval();

  ///
  /// Destructor
  ///
  virtual ~crg_interval();

protected:

private:

  //@}


  // ===========================================================
  /// @name INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The beginning of the member interval; this emulates
  /// members in the interval [begin(), end()), includes interval member.
  ///
  pod_index_type begin() const;

  ///
  /// The beginning of the member interval; this emulates
  /// members in the interval [begin(), end()), includes interval member.
  ///
  void begin(scoped_index& result) const;

  ///
  /// The end of the member interval.
  ///
  pod_index_type end() const;

  ///
  /// The end of the member interval.
  ///
  void end(scoped_index& result) const;

  ///
  /// The number of members in the member interval.
  ///
  size_type size() const;

  ///
  /// True if and only if the index xindex
  /// is contained in this interval.
  ///
  bool contains_member(pod_index_type xindex) const;

  ///
  /// True if and only if the index xindex
  /// is contained in this interval.
  ///
  bool contains_member(const scoped_index& xindex) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ID SPACE FAMILY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id space family for this interval.
  ///
  const index_space_family& id_spaces() const;

  ///
  /// The hub id space of this interval.
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
  /// The id space family of this interval.
  ///
  index_space_family* _id_spaces;

  ///
  /// True if the id space family has been initialized.
  ///
  bool _id_spaces_initialized;

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
  /// The local id space of this interval.
  ///
  const primary_index_space_handle& local_id_space() const;

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
  /// The id space of this interval.
  ///
  primary_index_space_handle _local_id_space;

  ///
  /// True if local id space has been initialized
  ///
  bool _local_id_space_initialized;

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id for the lower (xlower true) or upper (xlower false) cover
  /// id space with index xmbr_index.
  ///
  pod_index_type cover_id_space_id(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false) covers
  /// has been initialized for this interval.
  ///
  bool covers_initialized(bool xlower) const;

  ///
  /// Initialize the upper and lower covers for this interval.
  ///
  void initialize_covers();

protected:

  ///
  /// Initialize the lower covers for this interval.
  ///
  virtual void initialize_lower_covers() = 0;

  ///
  /// Initialize the upper cover for this interval.
  ///
  virtual void initialize_upper_covers() = 0;

  ///
  /// The offset into the id space family for the interval of lower covers.
  ///
  pod_index_type _lower_covers_begin;

  ///
  /// True if and only if the lower cover is initialized.
  ///
  bool _lower_covers_initialized;

  ///
  /// The offset into the id space family for the interval of upper covers.
  ///
  pod_index_type _upper_covers_begin;

  ///
  /// True if and only if the upper cover is initialized.
  ///
  bool _upper_covers_initialized;

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT COVER SET FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false)
  /// cover with index xmbr_index is explicit.
  ///
  bool cover_is_explicit(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// The explicit lower (xlower true) or upper (xlower false) cover id space
  /// of the member with index xmbr_index; creates an explict cover id space
  /// if the cover id space is not already explicit and, if xinitialize,
  /// initializes it with the contents of the implicit cover id space, if any.
  /// Returns the space id of the explicit cover.
  ///
  pod_index_type force_explicit_cover(bool xlower,
				      pod_index_type xmbr_index,
				      bool xinitialize = true);

protected:

  ///
  /// Creates a name for the explicit cover id space for member with index, xmbr_index.
  ///
  static string explicit_cover_name(bool xlower, const scoped_index& xmbr_index);

  ///
  /// Creates a name for the explicit cover id space for member with index, xmbr_index.
  ///
  static string explicit_cover_name(bool xlower, pod_index_type xmbr_index);

  ///
  /// The type of the explicit cover maps..
  ///
  typedef hash_map<pod_index_type, pod_index_type> explicit_cover_map_type;

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
  inline explicit_cover_map_type& explicit_cover_map(bool xlower)
  {
    return (xlower ? _explicit_lower_cover_map : _explicit_upper_cover_map);
  };

  ///
  /// The lower (xlower true) or upper (xlower false) map to explicit cover id spaces; const version
  ///
  inline const explicit_cover_map_type& explicit_cover_map(bool xlower) const
  {
    return (xlower ? _explicit_lower_cover_map : _explicit_upper_cover_map);
  };

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
  static factory<crg_interval>& interval_factory();

  ///
  /// Creates a default constructed instance of the
  /// the class with name xname.
  ///
  static crg_interval* new_interval(const string& xname);

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
  virtual crg_interval* clone() const = 0;

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
/// The deep size of the referenced object of type crg_interval;
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC 
size_t deep_size(const crg_interval& xp, bool xinclude_shallow = true);

} // namespace sheaf

#endif // ifndef CRG_INTERVAL_H
