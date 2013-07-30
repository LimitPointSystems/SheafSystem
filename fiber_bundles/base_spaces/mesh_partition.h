
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Interface for class mesh_partition

#ifndef MESH_PARTITION_H
#define MESH_PARTITION_H

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
/// A decomposition of a mesh into non-overlapping scopes.
///
/// @deprecated Removed from the build but remain around as a
///             reference for future development.
///
class SHEAF_DLL_SPEC mesh_partition : public any
{

public:

  // =============================================================================
  // MESH_PARTITION FACET
  // =============================================================================

  ///
  /// Default constructor.
  ///
  mesh_partition();

  ///
  /// Copy constructor.
  ///
  mesh_partition(const mesh_partition& xother);

  ///
  /// Destructor.
  ///
  virtual ~mesh_partition();

  ///
  /// Creates an instance for mesh xmesh.
  ///
  mesh_partition(const base_space_poset& xmesh, const string& xname);

  ///
  /// The name of this mesh_partition.
  ///
  const string& name() const;

  ///
  /// The mesh poset containing this mesh_partition.
  ///
  const base_space_poset& mesh() const;

  ///
  /// The set of processor read scope members.
  ///
  const subposet& parts() const;

  ///
  /// The number of parts in this mesh_partition.
  ///
  int part_ct() const;

  ///
  /// The name for the part associated with client id xp_id.
  ///
  string part_name(const scoped_index& xp_id) const;

  ///
  /// The zones in the part with client id xp_id.
  ///
  void part(const scoped_index& xp_id, id_block& xresult) const;

  ///
  /// Creates a part with client id xp_id containing zones xzones.
  ///
  const scoped_index& put_part(const scoped_index& xp_id, id_block& xzones);

  ///
  /// Extracts the part id from part name xname.
  ///
  pod_index_type part_id(const string& xname) const;

  ///
  /// True if xname is a valid decomposition name.
  ///
  static bool is_valid_name(const string& xname);

  ///
  /// The prefix for valid mesh_partition names.
  ///
  static string name_prefix();

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
  virtual mesh_partition* clone() const;

  ///
  /// Assignment operator
  ///
  mesh_partition& operator=(const mesh_partition& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

private:

  ///
  /// The name of this mesh_partition.
  ///
  string _name;

  ///
  /// The mesh poset containing this mesh_partition.
  ///
  base_space_poset* _mesh;

  ///
  /// The set of processor read scope members.
  ///
  subposet _parts;

  ///
  /// The number of parts in this mesh_partition.
  ///
  int _part_ct;

  ///
  /// Initializes the parts set.
  ///
  void initialize_parts_set();

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
  
} // namespace fiber_bundle


#endif // ifndef MESH_PARTITION_H
