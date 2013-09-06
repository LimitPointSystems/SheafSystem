


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class fiber_bundles_namespace

#ifndef FIBER_BUNDLES_NAMESPACE_H
#define FIBER_BUNDLES_NAMESPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SHEAVES_NAMESPACE_H
#include "sheaves_namespace.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

class base_space_member;
class sec_rep_descriptor_poset;  

///
/// The standard fiber bundles name space;
/// extends the standard sheaves namespace by
/// defining base space, fiber space and section space schema.
///
class SHEAF_DLL_SPEC fiber_bundles_namespace : public sheaves_namespace
{

  // ===========================================================
  /// @name FIBER_BUNDLES_NAMESPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a fiber bundles namespace with name xname.
  ///
  fiber_bundles_namespace(const string& xname);

  ///
  /// Destructor
  ///
  virtual ~fiber_bundles_namespace();

  ///
  /// The path of the standard base space schema member.
  ///
  static const poset_path& standard_base_space_schema_path();

  ///
  /// The name of the standard fiber space schema poset.
  ///
  static const string& standard_fiber_space_schema_poset_name();

  ///
  /// The name of the standard section space schema schema poset.
  ///
  static const string& standard_section_space_schema_schema_poset_name();

  ///
  /// Initialize all the prototypes needed by various factory methods,
  ///
  static void initialize_prototypes();

  ///
  /// Initialize the prototypes needed by poset factory method,
  ///
  static void initialize_poset_prototypes();

  ///
  /// Initialize the prototypes needed by crg interval factory method,
  ///
  static void initialize_crg_interval_prototypes();

  ///
  /// Initialize the prototypes needed by dof map factory method,
  ///
  static void initialize_dof_map_prototypes();

  ///
  /// Initialize the  prototypes needed by id space factory method,
  ///
  static void initialize_id_space_prototypes();

  ///
  /// The poset defining the schema for  base_space_poset, base_space_member and descendants.
  ///
  poset& base_space_schema_poset();

  ///
  /// The poset defining the schema for base_space_poset, base_space_member and descendants, const ver.
  ///
  const poset& base_space_schema_poset() const;

  ///
  /// The poset defining the prototype instances for base_space_member.
  ///
  base_space_poset& base_space_member_prototypes_poset();

  ///
  /// The poset defining the prototype instances for base_space_member, const ver.
  ///
  const base_space_poset& base_space_member_prototypes_poset() const;

protected:

  ///
  /// Initialize all the prototypes needed by various factory methods;
  /// virtual version.
  ///
  virtual void virtual_initialize_prototypes();

  ///
  /// Default constructor; creates an unattached handle.
  ///
  fiber_bundles_namespace();

  ///
  /// Covariant constructor.
  ///
  fiber_bundles_namespace(namespace_poset_member* xtop, namespace_poset_member* xbottom);

  ///
  /// Copy constructor; disabled.
  ///
  fiber_bundles_namespace(const fiber_bundles_namespace& xother) { };

private:

  ///
  /// The poset defining the schemas for base_space_member and descendaants.
  ///
  poset* _base_space_schema_poset;

  ///
  /// The poset defining the prototype instances for base_space_member.
  ///
  base_space_poset* _base_space_member_prototypes_poset;

  //@}


  // ===========================================================
  /// @name BASE SPACE DEFINITIONS FACET
  // ===========================================================
  //@{

public:

protected:
 
  ///
  /// Create schema and prototypes for standard base space member types.
  ///
  void make_base_space_definitions();

  ///
  /// Create schema poset for standard base space member types.
  ///
  void make_base_space_schema_poset();

  ///
  /// Create schema members for standard base space member types.
  ///
  virtual void make_base_space_schema_members();

  ///
  /// Create standard base space member prototypes poset.
  ///
  void make_base_space_member_prototypes_poset();

  ///
  /// Create standard base space member prototypes.
  ///
  virtual void make_base_space_member_prototypes(base_space_poset* xspace);

  ///
  /// Create prototype for a single point (i.e. a vertex) in poset xspace.
  ///
  void make_point_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a line segement (i.e. an edge) in poset xspace.
  ///
  void make_segment_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a line segement complex,
  /// i.e. an edge and the veritices it contains, in poset xspace.
  ///
  void make_segment_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a triangle in poset xspace.
  ///
  void make_triangle_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a triangle with nodes in poset xspace.
  ///
  void make_triangle_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a triangle with edges and nodes in poset xspace.
  ///
  void make_triangle_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a quad in poset xspace.
  ///
  void make_quad_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a quad with nodes in poset xspace.
  ///
  void make_quad_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a quad with edges and nodes in poset xspace.
  ///
  void make_quad_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a general polygon in poset xspace.
  ///
  void make_general_polygon_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a tetrahedron in poset xspace.
  ///
  void make_tetra_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a tetrahedron with nodes in poset xspace.
  ///
  void make_tetra_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a tetrahedron with faces, edges, and nodes in poset xspace.
  ///
  void make_tetra_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a hex in poset xspace.
  ///
  void make_hex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a hex with nodes in poset xspace.
  ///
  void make_hex_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a hex with faces and nodes in poset xspace.
  ///
  void make_hex_faces_nodes_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a hex with faces, edges, and nodes in poset xspace.
  ///
  void make_hex_complex_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a general polyhedron in poset xspace.
  ///
  void make_general_polyhedron_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for an unstructured block in poset xspace.
  ///
  void make_unstructured_block_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 1D structured block in poset xspace.
  ///
  void make_structured_block_1d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 2D structured block in poset xspace.
  ///
  void make_structured_block_2d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 3D structured block in poset xspace.
  ///
  void make_structured_block_3d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 1D point block in poset xspace.
  ///
  void make_point_block_1d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 2D point block in poset xspace.
  ///
  void make_point_block_2d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a 3D point block in poset xspace.
  ///
  void make_point_block_3d_prototype(base_space_poset* xspace);

  ///
  /// Create prototype for a part in poset xspace.
  ///
  void make_part_prototype(base_space_poset* xspace);

  ///
  /// Initializes the dofs in  base space member prototype
  /// dof map xmap to default values.
  ///
  void init_prototype_dof_map(base_space_member& xproto, int xdb);

private:

  //@}


  // ===========================================================
  /// @name FIBER SPACE DEFINITIONS FACET
  // ===========================================================
  //@{

public:

protected:
 
  ///
  /// Create standard fiber schema and fiber spaces.
  ///
  void make_fiber_space_definitions();

  ///
  /// Create schema poset for standard fiber space types.
  ///
  void make_fiber_space_schema_poset();

  ///
  /// Create schema members for standard fiber space types.
  ///
  virtual void make_fiber_space_schema_members();

  ///
  /// Create standard fiber spaces.
  ///
  virtual void make_fiber_spaces();

private:

  //@}


  // ===========================================================
  /// @name SECTION SPACE DEFINITIONS FACET
  // ===========================================================
  //@{

public:

protected:
 
  ///
  /// Create standard section representations and section schema.
  ///
  void make_section_space_definitions();

  ///
  /// Create schema poset for standard sec_rep_descritpors.
  ///
  void make_sec_rep_descriptor_schema_poset();

  ///
  /// Create schema members for standard sec_rep_descriptors.
  ///
  virtual void make_sec_rep_descriptor_schema_members();

  ///
  /// Create the standard sec_rep_descriptor poset.
  ///
  void make_sec_rep_descriptor_poset();

  ///
  /// Create standard section representation descriptors in poset xhost.
  ///
  virtual void make_sec_rep_descriptors(sec_rep_descriptor_poset* xhost);

  ///
  /// Create schema poset for standard section space schema.
  ///
  void make_section_space_schema_schema_poset();

  ///
  /// Create schema members for standard section space schema.
  ///
  virtual void make_section_space_schema_schema_members();

private:

  //@}


  // ===========================================================
  /// @name NAMESPACE_POSET FACET
  // ===========================================================
  //@{

public:

protected:
 
  ///
  /// Creates additional  members for this namespace.
  ///
  virtual void initialize_additional_members();

  ///
  /// Links xmbr into the appropriate group.
  ///
  virtual void link_poset(const namespace_poset_member& xmbr);

private:

  //@}
 

  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

protected:

  ///
  /// Attaches the handle data members when this handle
  /// is attached to a state. Intended to be redefined in
  /// descendants to handle additional data members defined there.
  ///
  virtual void attach_handle_data_members();

private:

  //@}

};

} // namespace fiber_bundle

#endif // ifndef FIBER_BUNDLES_NAMESPACE_H
