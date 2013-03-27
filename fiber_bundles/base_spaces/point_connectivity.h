
// $RCSfile: point_connectivity.h,v $ $Revision: 1.12 $ $Date: 2013/01/12 17:16:52 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class point_connectivity

#ifndef POINT_CONNECTIVITY_H
#define POINT_CONNECTIVITY_H

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
/// Connectivity for a point mesh. Since a point mesh is just a collection
/// of disconnected points, the "connectivity" list for each
/// point contains just the point itself.
///
class SHEAF_DLL_SPEC point_connectivity : public block_connectivity
{
public:

 
  // ===========================================================
  /// @name POINT_CONNECTIVITY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  /// Equivalent to point_connectivity(1)
  ///
  point_connectivity();

  ///
  /// Copy constructor
  ///
  point_connectivity(const point_connectivity& xother);

  ///
  /// Creates an instance with i_size() == xi_size.
  ///
  point_connectivity(size_type xi_size, pod_index_type xstart=0);

  ///
  /// Destructor.
  ///
  virtual ~point_connectivity();

  ///
  /// Static const integral data members.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {NODES_PER_ELEMENT = 1}; 

protected:

private:

  //@}


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
  virtual point_connectivity* clone() const;

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

#endif // ifndef POINT_CONNECTIVITY_H
