
// $RCSfile: quad_connectivity.h,v $ $Revision: 1.19 $ $Date: 2013/01/12 17:16:52 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class quad_connectivity

#ifndef QUAD_CONNECTIVITY_H
#define QUAD_CONNECTIVITY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BASE_CONNECTIVITY_H
#include "block_connectivity.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;


///
/// Connectivity for a quadrilateral mesh with elements arranged
/// in a regular rectangular array.
///
class SHEAF_DLL_SPEC quad_connectivity : public block_connectivity
{

public:
  // ===========================================================
  // @name QUAD_CONNECTIVITY FACET
  // ===========================================================
  //@{

  ///
  /// Default constructor.
  /// Equivalent to quad_connectivity(1, 1)
  ///
  quad_connectivity();

  ///
  /// Copy constructor
  ///
  quad_connectivity(const quad_connectivity& xother);

  ///
  /// Creates an instance with node_ids() == xnode_ids,
  /// and node_id_ct() == xnode_id_ct. If xnode_ct == 0,
  /// node_ct() will be computed from node_ids(), otherwise,
  /// node_ct() == xnode_ct.
  ///
  quad_connectivity(const pod_index_type* xnode_ids,
			        size_type xnode_id_ct, 
			        size_type xnode_ct);

  ///
  /// Creates an instance with i_size() == xi_size, j_size() == x_jsize.
  ///
  quad_connectivity(size_type xi_size, size_type xj_size, pod_index_type xstart_id = 0);

  ///
  /// Destructor.
  ///
  virtual ~quad_connectivity();


  ///
  /// Static const integral data members.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {NODES_PER_ELEMENT = 4}; 

protected:

  ///
  /// Allocates and initializes the connectivity array.
  ///
  void create_connectivity(size_type xi_size, 
			   size_type xj_size,
			   pod_index_type xstart_id);


private:

 //@}

  // ===========================================================
  /// @name BLOCK_CONNECTIVITY FACET
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
  // ANY FACET
  // ===========================================================

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
   virtual quad_connectivity* clone() const;

//   ///
//   /// Class invariant.
//   ///
   virtual bool invariant() const;

//   ///
//   /// Conformance test; true if other conforms to this
//   ///
   virtual bool is_ancestor_of(const any* other) const;

};
  
} // namespace fiber_bundle

#endif // ifndef QUAD_CONNECTIVITY_H
