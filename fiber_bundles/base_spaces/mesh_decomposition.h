
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class mesh_decomposition

#ifndef MESH_DECOMPOSITION_H
#define MESH_DECOMPOSITION_H

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
/// A mesh_decomposition of a mesh into possibly overlapping scopes.
///
/// @deprecated Removed from the build but remain around as a
///             reference for future development.
///
class SHEAF_DLL_SPEC mesh_decomposition : public any
{

public:

  // =============================================================================
  // MESH_DECOMPOSITION FACET
  // =============================================================================

  ///
  /// Default constructor.
  ///
  mesh_decomposition();

  ///
  /// Copy constructor.
  ///
  mesh_decomposition(const mesh_decomposition& xother);

  ///
  /// Destructor.
  ///
  virtual ~mesh_decomposition();

  ///
  /// Creates an instance for mesh xmesh.
  ///
  mesh_decomposition(const base_space_poset& xmesh, const string& xname);

  ///
  /// The name of this mesh_decomposition.
  ///
  const string& name() const;

  ///
  /// The mesh poset containing this mesh_decomposition.
  ///
  const base_space_poset& mesh() const;

  ///
  /// The set of processor read scope members.
  ///
  const subposet& scopes() const;

  ///
  /// The number of scopes in this mesh_decomposition.
  ///
  int scope_ct() const;

  ///
  /// The name for the scope associated with client id xp_id.
  ///
  string scope_name(const scoped_index& xp_id) const;

  ///
  /// The zones in the scope with client id xp_id.
  ///
  void scope(const scoped_index& xp_id, id_block& xresult) const;

  ///
  /// Creates a scope with client id xp_id containing zones xzones.
  ///
  const scoped_index& put_scope(const scoped_index& xp_id, id_block& xzones);

  ///
  /// Extracts the scope id from scope name xname.
  ///
  pod_index_type scope_id(const string& xname) const;

  ///
  /// True if xname is a valid mesh_decomposition name.
  ///
  static bool is_valid_name(const string& xname);

  ///
  /// The prefix for valid mesh_decomposition names.
  ///
  static string name_prefix();

  ///
  /// Computes a basis for this decomposition.
  ///
  void compute_basis();


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
  virtual mesh_decomposition* clone() const;

  ///
  /// Assignment operator
  ///
  mesh_decomposition& operator=(const mesh_decomposition& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

private:

  ///
  /// The name of this mesh_decomposition.
  ///
  string _name;

  ///
  /// The mesh poset containing this mesh_decomposition.
  ///
  base_space_poset* _mesh;

  ///
  /// The set of processor read scope members.
  ///
  subposet _scopes;

  ///
  /// The number of scopes in this mesh_decomposition.
  ///
  int _scope_ct;

  ///
  /// Initializes the scopes set.
  ///
  void initialize_scopes_set();

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
  
} // namespace fiber_bundle


#endif // ifndef MESH_DECOMPOSITION_H
