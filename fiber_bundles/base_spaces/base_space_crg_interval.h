
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

/// @file
/// Interface for class base_space_crg_interval.

#ifndef BASE_SPACE_CRG_INTERVAL_H
#define BASE_SPACE_CRG_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef IMPLICIT_CRG_INTERVAL_H
#include "implicit_crg_interval.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_HANDLE_H
#include "mutable_index_space_handle.h"
#endif

namespace fiber_bundle
{

class base_space_poset;
class base_space_crg_interval;

using namespace sheaf;

// Forward declarations to support friend declaration.

SHEAF_DLL_SPEC size_t deep_size(const base_space_crg_interval& m);

///
/// Abstract emulator for a interval of implicit base space members.
/// @issue this class really should be named homogeneous_block_crg_interval.
///
class SHEAF_DLL_SPEC base_space_crg_interval : public implicit_crg_interval
{

  friend SHEAF_DLL_SPEC size_t deep_size(const base_space_crg_interval& m);

  // ===========================================================
  /// @name BASE_SPACE_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor
  ///
  base_space_crg_interval();

  ///
  /// Destructor
  ///
  virtual ~base_space_crg_interval();

  ///
  /// The beginning of the local cells interval.
  ///
  virtual pod_index_type cells_begin() const = 0;

  ///
  /// The beginning of the local cells interval.
  ///
  void cells_begin(scoped_index& result) const;

  ///
  /// The end of the local cells interval.
  ///
  virtual pod_index_type cells_end() const = 0;

  ///
  /// The end of the local cells interval.
  ///
  void cells_end(scoped_index& result) const;

  ///
  /// The dimension of the member with id xmbr_id.
  /// Does not require access to dof tuple.
  ///
  virtual int db(pod_index_type xmbr_id) const = 0;

  ///
  /// The dimension of the member with id xmbr_id.
  /// Does not require access to dof tuple.
  ///
  int db(const scoped_index& xmbr_id) const;

  ///
  /// The id space index for the cells of dimension xd.
  /// Returns invalid_pod_index() if there is no id space for dimension xd.
  ///
  virtual pod_index_type d_cells_space_id(int xd) const = 0;

protected:

private:

  //@}


  // ===========================================================
  /// @name BLOCK VERTICES FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if the block vertices id space has been initialized.
  ///
  bool block_vertices_initialized() const;

  ///
  /// The id space index of the block vertices id space.
  ///
  pod_index_type block_vertices_space_id() const;

protected:

  ///
  /// The name of the block vertices id space.
  ///
  std::string block_vertices_name() const;

  ///
  /// True if the block vertices id space has been initialized.
  ///
  bool _block_vertices_initialized;

  ///
  /// The id space index of the block vertices id space.
  ///
  pod_index_type _block_vertices_space_id;

private:

  //@}


  // ===========================================================
  /// @name IMPLICIT_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name DOF TUPLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Dof tuple id for the block itself.
  ///
  virtual pod_index_type block_dof_tuple_id() const = 0;

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
  virtual base_space_crg_interval* clone() const = 0;

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

#endif // ifndef BASE_SPACE_CRG_INTERVAL_H
