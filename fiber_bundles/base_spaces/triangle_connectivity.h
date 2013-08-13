
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class triangle_connectivity

#ifndef TRIANGLE_CONNECTIVITY_H
#define TRIANGLE_CONNECTIVITY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_CONNECTIVITY_H
#include "block_connectivity.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// Nodal connectivity for a block containing zones of type triangle.
///
class SHEAF_DLL_SPEC triangle_connectivity : public block_connectivity
{

public:
  // ===========================================================
  /// @name TRIANGLE_CONNECTIVITY FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Creates an empty instance.
  ///
  triangle_connectivity();

  ///
  /// Copy constructor
  ///
  triangle_connectivity(const triangle_connectivity& xother);

  ///
  /// Creates an instance corresponding to the general arrangement
  /// of vertices given by node_ids() == xnode_ids,
  /// and node_id_ct() == xnode_id_ct. If xnode_ct == 0,
  /// node_ct() will be computed from node_ids(), otherwise,
  /// node_ct() == xnode_ct.
  ///
  triangle_connectivity(const pod_index_type* xnode_ids, 
			size_type xnode_id_ct, 
			size_type xnode_ct);

  ///
  /// Creates an instance corresponding to a rectangular array of
  /// vertices xi_size + 1 by  x_jsize + 1, that is, xi_size and xj_size
  /// are the number of edges in the i and j direction, respectively.
  /// Xstart_id is the id of the first vertex, that is, i=0, j=0.
  /// If xlower_left_to_upper_right_diagonals == true (default), the triangles
  /// are created by dividing a quad with the diagonal from the lower left to
  /// upper right corner; otherwise the other diagonal is used.
  ///
  triangle_connectivity(size_type xi_size,
                        size_type xj_size,
                        pod_index_type xstart_id = 0,
                        bool xlower_left_to_upper_right_diagonals = true);

  ///
  /// Destructor.
  ///
  virtual ~triangle_connectivity();

  ///
  /// Static const integral data members.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {NODES_PER_ELEMENT = 3}; 
    

protected:

  ///
  /// Allocates and initializes the connectivity array.
  ///
  void create_connectivity(size_type xi_size, 
			   size_type xj_size,
			   pod_index_type xstart_id,
			   bool xlower_left_to_upper_right_diagonals);

private:

  //@}

  // ===========================================================
  /// @name BLOCK_CONNECTIVITY FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}
 
  // ===========================================================
  /// @name BLOCK_RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The element type.
  ///
  virtual cell_type element_type() const;

protected:

private:

  //@}
  
  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual triangle_connectivity* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

protected:

private:

  //@}

};
  
} // namespace fiber_bundle

#endif // ifndef TRIANGLE_CONNECTIVITY_H
