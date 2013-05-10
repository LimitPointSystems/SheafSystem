

//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Interface for class point_block_crg_interval

#ifndef POINT_BLOCK_CRG_INTERVAL_H
#define POINT_BLOCK_CRG_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef HOMOGENEOUS_BLOCK_CRG_INTERVAL_H
#include "homogeneous_block_crg_interval.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// Emulator for a interval of implicit base space members
/// representing a homogeneous collection of unconnected points.
///
class SHEAF_DLL_SPEC point_block_crg_interval : public homogeneous_block_crg_interval
{
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name POINT_BLOCK_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor
  ///
  point_block_crg_interval();

  ///
  /// Destructor
  ///
  virtual ~point_block_crg_interval();

protected:

  ///
  /// The number of vertices.
  ///
  size_type _vertex_size;

private:

  //@}


  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name ZONES FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name VERTICES FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Initialize the vertex id space.
  ///
  void initialize_vertices(base_space_poset& xhost);

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  using base_space_crg_interval::db;

  ///
  /// The dimension of the member with id xmbr_id.
  /// Does not require access to dof tuple.
  ///
  virtual int db(pod_index_type xmbr_id) const;

  ///
  /// The id space index for the cells of dimension xd.
  /// Returns invalid_pod_index() if there is no id space for dimension xd.
  ///
  virtual pod_index_type d_cells_space_id(int xd) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name BLOCK VERTICES FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Initialize the block vertices id space from the private data xdata.
  ///
  void initialize_block_vertices(pod_index_type* xdata);

private:

  //@}


  // ===========================================================
  /// @name IMPLICIT_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The size for an instance created with
  /// parameters xi_size, xj_size, xk_size.
  ///
  static void get_size(size_type xi_size, size_type& result);

  ///
  /// The size for an instance created with
  /// parameters xi_size, xj_size, xk_size.
  ///
  static void get_size(size_type xi_size, size_type xj_size, size_type& result);

  ///
  /// The size for an instance created with
  /// parameters xi_size, xj_size, xk_size.
  ///
  static void get_size(size_type xi_size,
                       size_type xj_size,
                       size_type xk_size,
                       size_type& result);

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Initialize the lower covers for this interval.
  ///
  virtual void initialize_lower_covers();

  ///
  /// Initialize the upper cover for this interval.
  ///
  virtual void initialize_upper_covers();

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
                                size_type xi_size,
                                block<pod_index_type>& result);

  ///
  /// The dof tuple ids for an instance
  /// created with parameters xi_size, xj_size.
  ///
  static void get_dof_tuple_ids(poset_state_handle& xhost,
                                size_type xi_size,
                                size_type xj_size,
                                block<pod_index_type>& result);

  ///
  /// The dof tuple ids for an instance
  /// created with parameters xi_size, xj_size, xk_size.
  ///
  static void get_dof_tuple_ids(poset_state_handle& xhost,
                                size_type xi_size,
                                size_type xj_size,
                                size_type xk_size,
                                block<pod_index_type>& result);

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIVATE_DATA FACET
  // ===========================================================
  //@{

public:

  ///
  /// The private data for an instance with parameter xi_size.
  ///
  static void get_private_data(size_type xi_size, block<pod_index_type>& result);

  ///
  /// The private data for an instance with parameters xi_size, xj_size.
  ///
  static void get_private_data(size_type xi_size,
                               size_type xj_size,
                               block<pod_index_type>& result);

  ///
  /// The private data for an instance with parameters xi_size, xj_size, xk_size.
  ///
  static void get_private_data(size_type xi_size,
                               size_type xj_size,
                               size_type xk_size,
                               block<pod_index_type>& result);

protected:

  ///
  /// The size of the private data.
  ///
  virtual size_type implicit_private_data_size() const;

  ///
  /// The private data for this instance.
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
  /// Finialize the initialization of this crg interval in the host xhost.
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

protected:

private:

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
  virtual point_block_crg_interval* clone() const;

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
 
} // namespace fiber_bundle

#endif // ifndef POINT_BLOCK_CRG_INTERVAL_H
