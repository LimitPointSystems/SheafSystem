

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class mesh_generator.

#ifndef MESH_GENERATOR_H
#define MESH_GENERATOR_H

#ifndef GEOMETRY_H
#include "geometry.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

//=============================================================================

// Base class for mesh generators.

//=============================================================================
 
namespace sheaf
{
  class scoped_index;
}

namespace geometry
{

///
/// A base class for use in mesh generation.
///
class SHEAF_DLL_SPEC mesh_generator : public any
{

  // ===========================================================================
  /// @name MESH_GENERATOR FACET
  // ===========================================================================
  //@{

public:

  ///
  ///
  ///
  typedef sheaf::scoped_index::pod_type pod_type;

  ///
  /// Constructor.
  ///
  mesh_generator();

  ///
  /// Destructor.
  ///
  virtual ~mesh_generator();

  ///
  /// Generate the mesh.
  ///
  virtual void generate() = 0;

protected:
private:

  //@}

  // ===========================================================================
  /// @name ANY FACET
  // ===========================================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor, makes a new  instance of the same type as this.
  ///
  virtual mesh_generator* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================


} // end namespace geometry

#endif // ifndef MESH_GENERATOR_H
