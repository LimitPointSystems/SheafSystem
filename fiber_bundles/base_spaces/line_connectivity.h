

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class line_connectivity

#ifndef LINE_CONNECTIVITY_H
#define LINE_CONNECTIVITY_H

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
/// Nodal connectivity for a block containing zones of type segment.
///
class SHEAF_DLL_SPEC line_connectivity : public block_connectivity
{
public:

  // ===========================================================
  // LINE_CONNECTIVITY FACET
  // ===========================================================

  ///
  /// Default constructor.
  /// Equivalent to quad_connectivity(1, 1)
  ///
  line_connectivity();

  ///
  /// Copy constructor
  ///
  line_connectivity(const line_connectivity& xother);

  ///
  /// Creates an instance corresponding to the general arrangement
  /// of vertices given by node_ids() == xnode_ids,
  /// and node_id_ct() == xnode_id_ct. If xnode_ct == 0,
  /// node_ct() will be computed from node_ids(), otherwise,
  /// node_ct() == xnode_ct.
  ///
  line_connectivity(const pod_index_type* xnode_ids, 
                    size_type xnode_id_ct, 
                    size_type xnode_ct);

  ///
  ///
  /// Creates an instance corresponding to a linear array of
  /// vertices of size xi_size + 1, that is, xi_size is the number of segments.
  ///
  line_connectivity(size_type xi_size, pod_index_type xstart=0);

  ///
  /// Destructor.
  ///
  virtual ~line_connectivity();

 
   ///
  /// Static const integral data members.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {NODES_PER_ELEMENT = 2}; 

protected:

  ///
  /// Allocates and initializes the connectivity array.
  ///
  void create_connectivity(size_type xi_size, pod_index_type xstart_id);

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
  virtual line_connectivity* clone() const;

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

#endif // ifndef LINE_CONNECTIVITY_H
