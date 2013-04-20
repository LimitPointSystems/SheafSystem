
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class material_decomposition

#ifndef MATERIAL_DECOMPOSITION_H
#define MATERIAL_DECOMPOSITION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
class id_block;
}

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// A decomposition of a mesh into possibly overlapping materials.
///
/// @deprecated Removed from the build but remain around as a
///             reference for future development.
///
class SHEAF_DLL_SPEC material_decomposition : public any
{

public:

  // =============================================================================
  // MATERIAL_DECOMPOSITION FACET
  // =============================================================================

  ///
  /// Default constructor.
  ///
  material_decomposition();

  ///
  /// Copy constructor.
  ///
  material_decomposition(const material_decomposition& xother);

  ///
  /// Destructor.
  ///
  virtual ~material_decomposition();

  ///
  /// Creates an instance for mesh xmesh.
  ///
  material_decomposition(const base_space_poset& xmesh, const string& xname);

  ///
  /// The name of this material_decomposition.
  ///
  const string& name() const;

  ///
  /// The mesh poset containing this material_decomposition.
  ///
  const base_space_poset& mesh() const;

  ///
  /// The set of material members.
  ///
  const subposet& materials() const;

  ///
  /// The number of materials in this decomposition.
  ///
  int material_ct() const;

  ///
  /// The name for the material associated with client id xp_id.
  ///
  string material_name(const scoped_index& xp_id) const;

  ///
  /// The zones in the material with client id xp_id.
  ///
  void material(const scoped_index& xp_id, id_block& xresult) const;

  ///
  /// Creates a material with client id xp_id containing zones xzones.
  ///
  const scoped_index& put_material(const scoped_index& xp_id, id_block& xzones);

  ///
  /// Extracts the material id from material name xname.
  ///
  pod_index_type material_id(const string& xname) const;

  ///
  /// The set of mixed material members.
  ///
  const subposet& mixed_materials() const;

  ///
  /// The set of pure material members.
  ///
  const subposet& pure_materials() const;

  ///
  /// True if xname is a valid material_decomposition name.
  ///
  static bool is_valid_name(const string& xname);

  ///
  /// The prefix for valid material_decomposition names.
  ///
  static string name_prefix();

  ///
  /// Computes the mixed and pure material for this decomposition.
  ///
  void compute_mixed_materials();


  // =============================================================================
  // ANY FACET
  // =============================================================================

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual material_decomposition* clone() const;

  ///
  /// Assignment operator
  ///
  material_decomposition& operator=(const material_decomposition& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

private:

  ///
  /// The name of this material_decomposition.
  ///
  string _name;

  ///
  /// The mesh poset containing this material_decomposition.
  ///
  base_space_poset* _mesh;

  ///
  /// The set of material members.
  ///
  subposet _materials;

  ///
  /// The number of materials in this material_decomposition.
  ///
  int _material_ct;

  ///
  /// The set of mixed material members.
  ///
  subposet _mixed_materials;

  ///
  /// The set of pure material members.
  ///
  subposet _pure_materials;

  ///
  /// Initializes the materials set.
  ///
  void initialize_materials_set();

  ///
  /// The name for the mixed materials set.
  ///
  string mixed_materials_name();

  ///
  /// Initializes the mixed materials set.
  ///
  void initialize_mixed_materials_set();

  ///
  /// The name for the pure materials set.
  ///
  string pure_materials_name();

  ///
  /// Initializes the pureerials set.
  ///
  void initialize_pure_materials_set();

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
  
} // namespace fiber_bundle


#endif // ifndef MATERIAL_DECOMPOSITION_H
