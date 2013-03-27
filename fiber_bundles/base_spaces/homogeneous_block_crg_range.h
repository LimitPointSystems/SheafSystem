// $RCSfile: homogeneous_block_crg_range.h,v $ $Revision: 1.18 $ $Date: 2013/03/13 00:58:40 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class homogeneous_block_crg_range
///
/// @deprecated The cover set mechanism has been replaced with id spaces.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef HOMOGENEOUS_BLOCK_CRG_RANGE_H
#define HOMOGENEOUS_BLOCK_CRG_RANGE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_CRG_RANGE_H
#include "base_space_crg_range.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;


// Forward declarations to support friend declaration.

class homogeneous_block_crg_range;

///
/// Insert homogeneous_block_crg_range& m into ostream& os.
///
SHEAF_DLL_SPEC 
ostream& operator <<(ostream& os, const homogeneous_block_crg_range& m);

///
/// Emulator for a range of implicit base space members
/// representing a homogeneous collection of cells.
///
class SHEAF_DLL_SPEC homogeneous_block_crg_range : public base_space_crg_range
{

  friend SHEAF_DLL_SPEC ostream& operator <<(ostream& os, const homogeneous_block_crg_range& m);

  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor
  ///
  homogeneous_block_crg_range();

  ///
  /// Destructor
  ///
  virtual ~homogeneous_block_crg_range();

protected:

//   ///
//   /// Initialize the zone/vertex id space with name xname, offset in the
//   /// hub id space of xoffset and number of zones/vertices xct.
//   /// intended for zone db = vertex db = 0.
//   ///
//   void initialize_zone_vertex_id_space(const string& xname,
// 				       pod_index_type xoffset,
// 				       size_type xct);

//   ///
//   /// Initialize the connectivity and adjacency id spaces.
//   /// intended for zone db = vertex db = 0.
//   ///
//   void initialize_conn_adj_id_spaces(const string& xclass_name,
// 				     const arg_list& xargs,
// 				     size_type xub);

  ///
  /// Memeber class identifiers
  ///
  enum member_class_type
  {
    BLOCK, ZONE, VERTEX, MEMBER_CLASS_END
  };

  ///
  /// The member class of the member with index xmbr_index.
  ///
  member_class_type member_class(pod_index_type xmbr_index) const;

private:

  //@}


//   // ===========================================================
//   /// @name ZONE FACET
//   // ===========================================================
//   //@{

// public:

//   ///
//   /// True if the zone id space is initialized.
//   ///
//   bool zones_initialized() const;

//   ///
//   /// The zone id space.
//   ///
//   const offset_index_space_handle& zone_id_space() const;

//   ///
//   /// Allocates an id space iterator from the zone iterator pool.
//   ///
//   index_space_iterator& get_zone_id_space_iterator() const;

//   ///
//   /// Returns the id space iterator xitr to the zone iterator pool.
//   ///
//   void release_zone_id_space_iterator(index_space_iterator& xitr) const;

//   ///
//   /// True if and only if id space iterator xitr was allocated by
//   /// the zone iterator pool.
//   ///
//   bool allocated_zone_id_space_iterator(index_space_iterator& xitr) const;

// protected:

//   ///
//   /// The zone id space.
//   ///
//   offset_index_space_handle _zone_id_space;

//   ///
//   /// Initialize the zone id space with name xname, offset in the
//   /// hub id space of xoffset and number of zones xct.
//   ///
//   void initialize_zone_id_space(const string& xname,
// 				pod_index_type xoffset,
// 				size_type xct);

// private:

//   //@}


//   // ===========================================================
//   /// @name VERTEX FACET
//   // ===========================================================
//   //@{

// public:

//   ///
//   /// True if the vertex id space is initialized.
//   ///
//   bool vertices_initialized() const;

//   ///
//   /// The vertex id space.
//   ///
//   const offset_index_space_handle& vertex_id_space() const;

//   ///
//   /// Allocates an id space iterator from the vertex iterator pool.
//   ///
//   index_space_iterator& get_vertex_id_space_iterator() const;

//   ///
//   /// Returns the id space iterator xitr to the vertex iterator pool.
//   ///
//   void release_vertex_id_space_iterator(index_space_iterator& xitr) const;

//   ///
//   /// True if and only if id space iterator xitr was allocated by
//   /// the vertex iterator pool.
//   ///
//   bool allocated_vertex_id_space_iterator(index_space_iterator& xitr) const;

// protected:

//   ///
//   /// The vertex id space.
//   ///
//   offset_index_space_handle _vertex_id_space;

//   ///
//   /// Initialize the vertex id space with name xname, offset in the
//   /// hub id space of xoffset and number of vertices xct.
//   ///
//   void initialize_vertex_id_space(const string& xname,
// 				pod_index_type xoffset,
// 				size_type xct);

// private:

//   //@}


//   // ===========================================================
//   /// @name CONNECTIVITY FACET
//   // ===========================================================
//   //@{

// public:

//   ///
//   /// True if the connectivity id space interval is initialized.
//   ///
//   bool connectivity_initialized() const;

//   ///
//   /// Allocates an id space handle from the connectivity handle pool attached
//   /// to the connectivity id space state for zone with id xzone_id.
//   ///
//   index_space_handle& get_connectivity_id_space(pod_index_type xzone_id) const;

//   ///
//   /// Allocates an id space handle from the connectivity handle pool attached
//   /// to the connectivity id space state for zone with id xzone_id.
//   /// synonym for get_connecitivity_handle(zone_id_space().pod(xzone_id)).
//   ///
//   index_space_handle& get_connectivity_id_space(const scoped_index& xzone_id) const;

//   ///
//   /// Returns the id space handle xid_space to the connectivity handle pool.
//   ///
//   void release_connectivity_id_space(index_space_handle& xid_space) const;

//   ///
//   /// True if and only if id space handle xitr was allocated by
//   /// the connectivity handle pool.
//   ///
//   bool allocated_connectivity_handle(index_space_handle& xid_space) const;

//   ///
//   /// Allocates an id space iterator from the connectivity iterator pool attached
//   /// to the connectivity id space state for zone with id xzone_id.
//   ///
//   index_space_iterator& get_connectivity_id_space_iterator(pod_index_type xzone_id) const;

//   ///
//   /// Allocates an id space iterator from the connectivity iterator pool attached
//   /// to the connectivity id space state for zone with id xzone_id.
//   /// synonym for get_connecitivity_iterator(zone_id_space().pod(xzone_id)).
//   ///
//   index_space_iterator& get_connectivity_id_space_iterator(const scoped_index& xzone_id) const;

//   ///
//   /// Returns the id space iterator xid_space to the connectivity iterator pool.
//   ///
//   void release_connectivity_id_space_iterator(index_space_iterator& xid_space) const;

//   ///
//   /// True if and only if id space iterator xitr was allocated by
//   /// the connectivity iterator pool.
//   ///
//   bool allocated_connectivity_iterator(index_space_iterator& xitr) const;

// protected:

//   ///
//   /// The begin space id for the connectivity id spaces.
//   ///
//   pod_index_type _conn_begin;

//   ///
//   /// The id space interval for the connectivity.
//   ///
//   index_space_collection* _conn_id_space_interval;

//   ///
//   /// Initialize the connectivity id space interval.
//   ///
//   void initialize_connectivity_id_spaces(const string& xclass_name,
// 					 const arg_list& xargs,
// 					 size_type xub);

// private:

//   //@}


//   // ===========================================================
//   /// @name ADJACENCY FACET
//   // ===========================================================
//   //@{

// public:

//   ///
//   /// True if the adjacency id space interval is initialized.
//   ///
//   bool adjacency_initialized() const;

//   ///
//   /// Allocates an id space handle from the adjacency handle pool attached
//   /// to the adjacency id space state for zone with id xzone_id.
//   ///
//   index_space_handle& get_adjacency_id_space(pod_index_type xzone_id) const;

//   ///
//   /// Allocates an id space handle from the adjacency handle pool attached
//   /// to the adjacency id space state for zone with id xzone_id.
//   /// synonym for get_connecitivity_handle(zone_id_space().pod(xzone_id)).
//   ///
//   index_space_handle& get_adjacency_id_space(const scoped_index& xzone_id) const;

//   ///
//   /// Returns the id space handle xid_space to the adjacency handle pool.
//   ///
//   void release_adjacency_id_space(index_space_handle& xid_space) const;

//   ///
//   /// True if and only if id space handle xitr was allocated by
//   /// the adjacency handle pool.
//   ///
//   bool allocated_adjacency_handle(index_space_handle& xid_space) const;

//   ///
//   /// Allocates an id space iterator from the adjacency iterator pool attached
//   /// to the adjacency id space state for zone with id xzone_id.
//   ///
//   index_space_iterator& get_adjacency_id_space_iterator(pod_index_type xzone_id) const;

//   ///
//   /// Allocates an id space iterator from the adjacency iterator pool attached
//   /// to the adjacency id space state for zone with id xzone_id.
//   /// synonym for get_connecitivity_iterator(zone_id_space().pod(xzone_id)).
//   ///
//   index_space_iterator& get_adjacency_id_space_iterator(const scoped_index& xzone_id) const;

//   ///
//   /// Returns the id space iterator xid_space to the adjacency iterator pool.
//   ///
//   void release_adjacency_id_space_iterator(index_space_iterator& xid_space) const;

//   ///
//   /// True if and only if id space iterator xitr was allocated by
//   /// the adjacency iterator pool.
//   ///
//   bool allocated_adjacency_iterator(index_space_iterator& xitr) const;

// protected:

//   ///
//   /// The begin space id for the adjacency id spaces.
//   ///
//   pod_index_type _adj_begin;

//   ///
//   /// The id space interval for the adjacency.
//   ///
//   index_space_collection* _adj_id_space_interval;

//   ///
//   /// Initialize the adjacency id space interval.
//   ///
//   void initialize_adjacency_id_spaces(const string& xclass_name,
// 				      const arg_list& xargs,
// 				      size_type xub);

// private:

//   //@}


//   // ===========================================================
//   /// @name BASE_SPACE_CRG_RANGE FACET
//   // ===========================================================
//   //@{

// public:

//   using base_space_crg_range::cells_begin;

//   ///
//   /// The beginning of the local cells range.
//   ///
//   virtual pod_index_type cells_begin() const;

//   using base_space_crg_range::cells_end;

//   ///
//   /// The end of the local cells range.
//   ///
//   virtual pod_index_type cells_end() const;

// protected:

// private:

//   //@}


//   // ===========================================================
//   // IMPLICIT_CRG_RANGE FACETS
//   // ===========================================================
//   //@{

// public:

// protected:

// private:

//   //@}


//   // ===========================================================
//   /// @name RANGE FACET
//   // ===========================================================
//   //@{

// public:

//   ///
//   /// The atoms id space for this range.
//   ///
//   virtual const index_space_handle& atoms() const;

//   /// @todo Remove.

// //   ///
// //   /// An iterator over the atoms in this range.
// //   ///
// //   virtual cover_set_iterator atoms() const;

// protected:

// private:

//   //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name DOF_TUPLE_ID FACET
  // ===========================================================
  //@{

public:

  using implicit_crg_range::is_jim;

  ///
  /// True if and only if the member with index xmbr_index is join-irreducible.
  ///
  virtual bool is_jim(pod_index_type xmbr_index) const;

  using implicit_crg_range::dof_tuple_id;

  ///
  /// The dof tuple id of the member with index xmbr_index
  ///
  virtual const scoped_index& dof_tuple_id(pod_index_type xmbr_index) const;

  ///
  /// Dof tuple id for the block itself.
  ///
  const scoped_index& block_dof_tuple_id() const;

  ///
  /// Dof tuple id for zones.
  ///
  const scoped_index& zone_dof_tuple_id() const;

  ///
  /// Dof tuple id for vertices.
  ///
  const scoped_index& vertex_dof_tuple_id() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIVATE_DATA FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@{

public:

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
  virtual homogeneous_block_crg_range* clone() const;

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
/// The deep size of the referenced object of type homogeneous_block_crg_range.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const homogeneous_block_crg_range& xr, bool xinclude_shallow = true);


} // namespace fiber_bundle

#endif // ifndef HOMOGENEOUS_BLOCK_CRG_RANGE_H
