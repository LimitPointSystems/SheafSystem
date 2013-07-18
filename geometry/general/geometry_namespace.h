

//
// CONFIDENTIALITY: 
// This is a CONFIDENTIAL document. 
// Copyright is vested in Shell Internationale Research 
// Mij. B.V., The Hague. 
// Neither the whole or any part of this document may be 
// reproduced, stored in any retrieval system or trans- 
// mitted in any form or by any means (electronic, 
// mechanical, reprographic, recording or otherwise) 
// without the prior consent of the copyright owner. 
//

// Interface for class geometry_namespace

#ifndef GEOMETRY_NAMESPACE_H
#define GEOMETRY_NAMESPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif

namespace geometry
{
  
///
/// Namespace for GEOMETRY component.
///
class SHEAF_DLL_SPEC geometry_namespace : public fiber_bundles_namespace
{

public:

  // ===========================================================
  /// @name GEOMETRY_NAMESPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a geometry namespace with name xname.
  ///
  geometry_namespace(const string& xname);

  ///
  /// Destructor.
  ///
  virtual ~geometry_namespace();

protected:

  ///
  /// Default constructor; creates an unattached handle.
  ///
  geometry_namespace();

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  geometry_namespace(const geometry_namespace& xother);

private:

  //@}

  // ===========================================================
  /// @name FIBER_BUNDLES_NAMESPACE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Create standard base space member prototypes.
  ///
  virtual void make_base_space_member_prototypes(base_space_poset* xspace);

  ///
  /// Create prototype for a polyline in poset xspace.
  ///
  void make_line_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for an interpretation plane in poset xspace.
  ///
  void make_plane_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for an interpreted surface in poset xspace.
  ///
  void make_surface_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a line web in poset xspace.
  ///
  void make_line_web_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a line web in poset xspace.
  ///
  void make_polygon_prototype(base_space_poset* xspace);


private:

  //@}
 
  // =============================================================================
  /// @name ANY FACET
  // =============================================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual geometry_namespace* clone() const;

  ///
  /// Assignment operator
  ///
  geometry_namespace& operator=(const geometry_namespace& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}


};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

  
} // namespace geometry

#endif // ifndef GEOMETRY_NAMESPACE_H
