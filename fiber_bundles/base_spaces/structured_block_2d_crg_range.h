// $RCSfile: structured_block_2d_crg_range.h,v $ $Revision: 1.16 $ $Date: 2013/01/14 16:03:37 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class structured_block_2d_crg_range
///
/// @deprecated The cover set mechanism has been replaced with id spaces.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef STRUCTURED_BLOCK_2D_CRG_RANGE_H
#define STRUCTURED_BLOCK_2D_CRG_RANGE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef HOMOGENEOUS_BLOCK_CRG_RANGE_H
#include "homogeneous_block_crg_range.h"
#endif

namespace sheaf
{
class ij_product_structure;
}

namespace fiber_bundle
{

using namespace sheaf;

// Forward declarations to support friend declaration.

class structured_block_2d_crg_range;

///
/// Insert structured_block_2d_crg_range& m into ostream& os.
///
ostream& operator <<(ostream& os, const fiber_bundle::structured_block_2d_crg_range& m);

size_t deep_size(const structured_block_2d_crg_range& m);


///
/// Emulator for a range of implicit base space members
/// representing a 2 dimensional structured block, that is,
/// a homogeneous collection of connected quads
/// arranged in an i_size() x j_size() array.
///
class SHEAF_DLL_SPEC structured_block_2d_crg_range : public homogeneous_block_crg_range
{

  friend ostream& operator <<(ostream& os, const structured_block_2d_crg_range& m);
  friend size_t deep_size(const structured_block_2d_crg_range& m);

  // ===========================================================
  /// @name STRUCTURED_BLOCK_2D_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor
  ///
  structured_block_2d_crg_range();

  ///
  /// Destructor
  ///
  virtual ~structured_block_2d_crg_range();

  ///
  /// The number of zones in the i direction in this block.
  ///
  size_type i_size() const;

  ///
  /// The number of zones in the j direction in this block.
  ///
  size_type j_size() const;

protected:

private:

  ///
  /// The number of zones in the i direction in this block.
  ///
  size_type _i_size;

  ///
  /// The number of zones in the j direction in this block.
  ///
  size_type _j_size;

  ///
  /// The number of vertices in the i direction in this block.
  ///
  size_type _i_vertex_size;

  ///
  /// The number of vertices in the j direction in this block.
  ///
  size_type _j_vertex_size;

  //@}


  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name ZONE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The product structure of the zones id space.
  ///
  const ij_product_structure& zone_product_structure() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name VERTEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// The product structure of the vertexs id space.
  ///
  const ij_product_structure& vertex_product_structure() const;

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
  /// The size for an instance created with parameter xi_size.
  ///
  static void get_size(size_type xi_size, size_type xj_size, size_type& result);

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
                                size_type xi_size,
                                size_type xj_size,
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
  /// The private data for an instance with parameter xi_size.
  ///
  static void get_private_data(size_type xi_size,
			       size_type xj_size,
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
  virtual structured_block_2d_crg_range* clone() const;

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
/// The deep size of the referenced object of type structured_block_2d_crg_range.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const structured_block_2d_crg_range& xr, bool xinclude_shallow = true);

} // namespace fiber_bundle

#endif // ifndef STRUCTURED_BLOCK_2D_CRG_RANGE_H
