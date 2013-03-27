// $RCSfile: zone_nodes_block_crg_range.h,v $ $Revision: 1.17 $ $Date: 2013/03/13 00:58:41 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class zone_nodes_block_crg_range.
///
/// @deprecated The cover set mechanism has been replaced with id spaces.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef ZONE_NODES_BLOCK_CRG_RANGE_H
#define ZONE_NODES_BLOCK_CRG_RANGE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef HOMOGENEOUS_BLOCK_CRG_RANGE_H
#include "homogeneous_block_crg_range.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_HANDLE_H
#include "mutable_index_space_handle.h"
#endif

#ifndef RAGGED_ARRAY_H
#include "ragged_array.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_SLIST_H
#include "std_slist.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

class block_adjacency;
class block_connectivity;

// Forward declarations to support friend declaration.

class zone_nodes_block_crg_range;

///
/// Insert zone_nodes_block_crg_range& m into ostream& os.
///
SHEAF_DLL_SPEC ostream& operator <<(ostream& os, const zone_nodes_block_crg_range& m);

SHEAF_DLL_SPEC size_t deep_size(const zone_nodes_block_crg_range& m);


using namespace sheaf;

///
/// Emulator for a range of implicit base space members
/// representing an unstructured block, that is,
/// a homogeneous collection of zones of a given type
/// with nodal connectivity.
///
class SHEAF_DLL_SPEC zone_nodes_block_crg_range : public homogeneous_block_crg_range
{

  friend SHEAF_DLL_SPEC ostream& operator <<(ostream& os, const zone_nodes_block_crg_range& m);
  friend SHEAF_DLL_SPEC size_t deep_size(const zone_nodes_block_crg_range& m);

  // ===========================================================
  /// @name ZONE_NODE_BLOCK_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor
  ///
  zone_nodes_block_crg_range();

  ///
  /// Destructor
  ///
  virtual ~zone_nodes_block_crg_range();

  ///
  /// The reserved name for the vertex client id space of
  /// the ramge member with hub id xhub_id.
  ///
  static string vertex_client_id_space_name(pod_index_type xhub_id);

  ///
  /// The vertex client id space of this range.
  ///
  const index_space_handle& vertex_client_id_space() const;

  ///
  /// True if and only if the vertex client id space has been initialized.
  ///
  bool vertex_client_id_space_initialized() const;

private:

  ///
  /// Number of zones in this range.
  ///
  size_type _zone_ct;

  ///
  /// Connectivity size for each zone
  ///
  size_type _nodes_per_zone;

  ///
  /// The vertex client id space.
  ///
  mutable_index_space_handle _vertex_client_id_space;

  ///
  /// Type of temporary adjacency relation.
  ///
  typedef block_adjacency adj_type;

  ///
  /// Initializes the vertex client id space.
  ///
  void initialize_vertex_client_id_space(const adj_type& xadj);

  ///
  /// Initialize the connectivity id space interval.
  ///
  void initialize_connectivity_id_spaces(size_type xzone_ct,
					 size_type xnodes_per_zone,
					 size_type xconn_ct,
					 const pod_index_type* xconn);

  ///
  /// Initialize the adjacency id space interval.
  ///
  void initialize_adjacency_id_spaces(const adj_type& xadj);

  ///
  /// The name of the prototype for
  /// the zone type of connectivity xconn.
  ///
  static const string& zone_prototype_name(const block_connectivity& xconn);

  ///
  /// The dimension of the zone type of connectivity xconn.
  ///
  static int zone_db(const block_connectivity& xconn);

  //@}


  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

  /// @todo Remove.

//   ///
//   /// An iterator over the block vertices in this range.
//   ///
//   virtual cover_set_iterator block_vertices() const;

  using base_space_crg_range::db;

  ///
  /// The dimension of the member with id xmbr_id.
  /// Does not require access to dof tuple.
  ///
  virtual int db(pod_index_type xmbr_id) const;

protected:

  ///
  /// The dimension of a zone.
  ///
  int _zone_db;

private:

  //@}


  // ===========================================================
  /// @name BLOCK VERTICES FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Initialize the block vertices id space.
  ///
  void initialize_block_vertices_id_space();

private:

  //@}


  // ===========================================================
  // IMPLICIT_CRG_RANGE FACETS
  // ===========================================================

  // ===========================================================
  /// @name RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The size of the range for block connectivity xconn.
  ///
  static void get_size(const block_connectivity& xconn, size_type& result);

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

public:

protected:

  ///
  /// The implicit id space for the lower (xlower true) or upper (xlower false) cover
  /// of member with index xmbr_index.
  ///
  virtual const index_space_handle&
  implicit_cover_id_space(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// Initialize the explicit lower (xlower true) or upper (xlower false)
  /// cover id space xcover of the member with index xmbr_index.
  ///
  virtual void initialize_explicit_cover(bool xlower,
					 pod_index_type xmbr_index,
					 interval_index_space_handle& xcover) const;

private:

  //@}


  // ===========================================================
  /// @name DOF_TUPLE_ID FACET
  // ===========================================================
  //@{

public:

  ///
  /// The dof tuple ids for an instance
  /// created with parameter xi_size.
  ///
  static void get_dof_tuple_ids(poset_state_handle& xhost,
                                const block_connectivity& xconn,
                                block<scoped_index>& result);

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIVATE_DATA FACET
  // ===========================================================
  //@{

public:

  ///
  /// The private data for an instance with connectivity xconn.
  ///
  static void get_private_data(const block_connectivity& xconn,
                               block<pod_index_type>& result);

protected:

  ///
  /// The size of the private data.
  ///
  virtual size_type implicit_private_data_size() const;

  ///
  /// Initializes this using private data xdata.
  ///
  virtual void get_implicit_private_data(block<pod_index_type>& xdata) const;

  ///
  /// Initializes this using private data xdata.
  ///
  virtual void put_implicit_private_data(const block<pod_index_type>& xdata);

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

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of this class;
  /// provided to satisfy factory template.
  ///
  virtual const string& class_name() const;

  ///
  /// True if fully initialized.
  ///
  virtual bool is_initialized() const;

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
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual zone_nodes_block_crg_range* clone() const;

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
/// The deep size of the referenced object of type zone_nodes_block_crg_range.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const zone_nodes_block_crg_range& xr, bool xinclude_shallow = true);

 
} // namespace fiber_bundle

#endif // ifndef ZONE_NODES_BLOCK_CRG_RANGE_H
