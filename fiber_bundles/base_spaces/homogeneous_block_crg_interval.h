//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

//

/// @file
/// Interface for class homogeneous_block_crg_interval

#ifndef HOMOGENEOUS_BLOCK_CRG_INTERVAL_H
#define HOMOGENEOUS_BLOCK_CRG_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_CRG_INTERVAL_H
#include "SheafSystem/base_space_crg_interval.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;


///
/// Emulator for a interval of implicit base space members
/// representing a homogeneous collection of cells.
///
class SHEAF_DLL_SPEC homogeneous_block_crg_interval : public base_space_crg_interval
{

  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor
  ///
  homogeneous_block_crg_interval();

  ///
  /// Destructor
  ///
  virtual ~homogeneous_block_crg_interval();

protected:

  ///
  /// Memeber class identifiers
  ///
  enum member_class_type
  {
    BLOCK, ZONE, VERTEX, MEMBER_CLASS_END
  };

  ///
  /// The member class of the member with index xmbr_index.
  ///
  member_class_type member_class(pod_index_type xmbr_index) const;

private:

  //@}


  // ===========================================================
  /// @name ZONES FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if the zone id space has been initialized.
  ///
  bool zones_initialized() const;

  ///
  /// The index of the zone id space.
  ///
  pod_index_type zones_space_id() const;

protected:

  ///
  /// True if the zone id space has been initialized.
  ///
  bool _zones_initialized;

  ///
  /// The index of the zone id space.
  ///
  pod_index_type _zones_space_id;

private:

  //@}


  // ===========================================================
  /// @name VERTICES FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if the vertex id space has been initialized.
  ///
  bool vertices_initialized() const;

  ///
  /// The index of the vertex id space.
  ///
  pod_index_type vertices_space_id() const;

protected:

  ///
  /// True if the vertex id space has been initialized.
  ///
  bool _vertices_initialized;

  ///
  /// The index of the vertex id space.
  ///
  pod_index_type _vertices_space_id;

private:

  //@}


  // ===========================================================
  /// @name CONNECTIVITY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The index of the connectivity id space for zone with id xzone_id.
  ///
  pod_index_type connectivity_space_id(pod_index_type xzone_id) const;

protected:

  ///
  /// The beginning offset of the connectivity id spaces in the id space family.
  ///
  pod_index_type _connectivity_begin;

private:

  //@}


  // ===========================================================
  /// @name ADJACENCY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The index of the adjacency id space for vertex with id xvertex_id.
  ///
  pod_index_type adjacency_space_id(pod_index_type xvertex_id) const;

protected:

  ///
  /// The beginning offset of the adjacency id spaces in the id space family.
  ///
  pod_index_type _adjacency_begin;

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  using base_space_crg_interval::cells_begin;

  ///
  /// The beginning of the local cells interval.
  ///
  virtual pod_index_type cells_begin() const;

  using base_space_crg_interval::cells_end;

  ///
  /// The end of the local cells interval.
  ///
  virtual pod_index_type cells_end() const;

protected:

private:

  //@}


  // ===========================================================
  // IMPLICIT_CRG_INTERVAL FACETS
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name DOF_TUPLE_ID FACET
  // ===========================================================
  //@{

public:

  using implicit_crg_interval::is_jim;

  ///
  /// True if and only if the member with index xmbr_index is join-irreducible.
  ///
  virtual bool is_jim(pod_index_type xmbr_index) const;

  using implicit_crg_interval::dof_tuple_id;

  ///
  /// The dof tuple id of the member with index xmbr_index
  ///
  virtual pod_index_type dof_tuple_id(pod_index_type xmbr_index) const;

  ///
  /// Dof tuple id for the block itself.
  ///
  pod_index_type block_dof_tuple_id() const;

  ///
  /// Dof tuple id for zones.
  ///
  pod_index_type zone_dof_tuple_id() const;

  ///
  /// Dof tuple id for vertices.
  ///
  pod_index_type vertex_dof_tuple_id() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIVATE_DATA FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if fully initialized.
  ///
  virtual bool is_initialized() const;

  ///
  /// Sets is_initialized() == true;
  /// dummy routine provided to satisfy factory template.
  ///
  void initialize(const namespace_poset& xnamespace);

  ///
  /// The name of this class;
  /// provided to satisfy factory template.
  ///
  virtual const std::string& class_name() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual homogeneous_block_crg_interval* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace fiber_bundle

#endif // ifndef HOMOGENEOUS_BLOCK_CRG_INTERVAL_H
