
// $RCSfile: tetgen_generator.h,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:30 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class tetgen_generator.

#ifndef TETGEN_GENERATOR_H
#define TETGEN_GENERATOR_H

#ifndef GEOMETRY_H
#include "geometry.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef MESH_GENERATOR_H
#include "mesh_generator.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif

#ifndef SEC_E3_H
#include "sec_e3.h"
#endif

#ifndef TETGEN_H
#include "tetgen.h"
#endif

//=============================================================================

// Class for a mesh generator based on tetgen (a public domain mesher).

//=============================================================================
 
namespace sheaf
{
  class scoped_index;
  class std_vector;
}

namespace geometry
{

///
/// A base class for use in mesh generation.
///
class SHEAF_DLL_SPEC tetgen_generator : public mesh_generator
{
  // ===========================================================================
  /// @name TETGEN_GENERATOR FACET
  // ===========================================================================
  //@{

public:

  ///
  /// Constructor.
  /// Poset paths xbase_member_path and xcoords_member_path are
  /// paths to existing base space and coordinate section members
  /// in namespace poset xns which describe the geometry for a
  /// closed surface to be tetrahedralized by tetgen. Argument
  /// xswitches is a string containing command line arguments
  /// ("switches") to be passed to tetgen.
  ///
  tetgen_generator(fiber_bundles_namespace& xns,
                   const poset_path& xbase_member_path,
                   const poset_path& xcoords_member_path,
                   const string& xswitches = "pY");

  ///
  /// Destructor.
  ///
  virtual ~tetgen_generator();

  ///@todo: copy constructor and assignment operator.

  ///
  /// Default constructor.
  ///
  tetgen_generator();

  ///
  /// The namespace poset.
  ///
  fiber_bundles_namespace& name_space() const;

  ///
  /// The base space poset.
  ///
  base_space_poset& base_space() const;

  ///
  /// The active surface base space member.
  ///
  base_space_member& base_member() const;

  ///
  /// The vertices id space.
  ///
  const index_space_handle& vertices_id_space() const;

  ///
  /// The coordinates section.
  ///
  sec_e3& coords() const;


  ///
  /// The name of the prototypes poset.
  ///
  static const string& prototypes_poset_name();

  ///
  /// The rep path.
  ///
  static const poset_path& rep_path();

  ///
  /// The tet element prototype path.
  ///
  static const poset_path& tetra_proto_path();

  ///
  /// Convenience function; generates names for the members of xbase_space.
  /// Name are generated for the _d_cells(xd) members of the base space
  /// and are of the form "xroot_#" where "#" is sequential from
  /// 0 to d_cells(xd).ct()-1.  This function is static so it can be used by
  /// test cases as well as by member functions..
  ///
  static void make_names(base_space_poset& xbase_space,
                         int xd,
                         const string& xroot);

  ///
  /// The connectivities for the input surface triangles.
  ///
  //vector<pod_type>& tri_connectivities();
  const vector<pod_type>& tri_connectivities() const;

  ///
  /// The coordinates for the input surface vertices.
  ///
  //vector<e3_lite>& tri_coordinates();
  const vector<e3_lite>& tri_coordinates() const;

  ///
  /// The connectivities for the output volumne tetrahedrons.
  ///
  //vector<pod_type>& tet_connectivities();
  const vector<pod_type>& tet_connectivities() const;

  ///
  /// The coordinates for the output vertices.
  ///
  //vector<e3_lite>& tet_coordinates();
  const vector<e3_lite>& tet_coordinates() const;

  ///
  /// The base space path for the generated mesh.
  ///
  const poset_path& volume_base_space_path() const;

  ///
  /// The coordinates  path for the generated mesh.
  ///
  const poset_path& volume_coordinates_path() const;


protected:

  ///
  /// Invoke tetgen.  Inputs to tetgen are the coordinates
  /// and connectivities of the surface triangles.  Output is
  /// stored in an instance of tetgen::tetgenio
  ///
  void invoke_tetgen(tetgenio& xtetgen_out) const;

  ///
  /// Collect the coordinates surface triangle vertices.
  ///
  void collect_surface_coordinates();

  ///
  /// Collect the surface triangle connectivities.
  ///
  void collect_tri_connectivities();

  ///
  /// Collect the results store in the tetgen output object xtetgen_out
  /// into local coordinate and connectivity vectors.
  ///
  void collect_tetgen_results(const tetgenio& xtetgen_out);

  ///
  /// Update the namespace with the results from tetgen.
  /// Creates a new base_space and coordinates section space
  /// in the same namespace as the original surface data.
  ///
  void update_name_space();

  ///
  /// Compute and print the areas and normals of the surface triangles
  /// for debugging.  Total surface area is also computed, printed,
  /// and returned. 
  ///
  double compute_tri_areas() const;

  ///
  /// Compute and print the volumes of the tetrahedrons for debugging.
  /// Total volume is also computed, printed, and returned.
  ///
  double compute_tet_volumes() const;

  ///
  /// Create a base space poset containing the containing the topological
  ///  data for the mesh generated by tetgen.
  ///
  base_space_poset* create_volume_base_space();

  ///
  /// Create a section containing the coordinates for the mesh
  /// generated by tetgen.
  ///
  sec_at1_space* create_volume_coordinates_section();

  ///
  /// The namespace poset.
  ///
  fiber_bundles_namespace* _name_space;

  ///
  /// The base space poset.
  ///
  base_space_poset* _base_space;

  ///
  /// The base space member.
  ///
  base_space_member* _base_member;

  ///
  /// The coordinates section.
  ///
  sec_e3* _coords;

  ///
  /// Tetgen "command line" switches.
  ///
  string _tetgen_switches;

  ///
  /// The connectivities for the input surface triangles.
  ///
  vector<pod_type> _tri_connectivities;

  ///
  /// The coordinates for the input surface vertices.
  ///
  vector<e3_lite> _tri_coordinates;

  ///
  /// The connectivities for the output volumne tetrahedrons.
  ///
  vector<pod_type> _tet_connectivities;

  ///
  /// The coordinates for the output vertices.
  ///
  vector<e3_lite> _tet_coordinates;

  ///
  /// The base space path for the generated mesh.
  ///
  poset_path _volume_base_space_path;

  ///
  /// The coordinates path for the generated mesh.
  ///
  poset_path _volume_coordinates_path;


private:

  //@}

  // ===========================================================================
  /// @name MESH_GENERATOR FACET
  // ===========================================================================
  //@{

public:

  ///
  /// Generate a mesh of tetrahedrons.
  ///
  virtual void generate();

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
  /// Virtual constructor, makes a new instance of the same type as this.
  ///
  virtual tetgen_generator* clone() const;

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

#endif // ifndef TETGEN_GENERATOR_H
