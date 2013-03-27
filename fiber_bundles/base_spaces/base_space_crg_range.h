// $RCSfile: base_space_crg_range.h,v $ $Revision: 1.17 $ $Date: 2013/03/13 00:58:40 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class base_space_crg_range.
///
/// @deprecated The cover set mechanism has been replaced with id spaces.
/// @todo Remove .h and .cc files associated with this class from the repository.
///

#ifndef BASE_SPACE_CRG_RANGE_H
#define BASE_SPACE_CRG_RANGE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef IMPLICIT_CRG_RANGE_H
#include "implicit_crg_range.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_HANDLE_H
#include "mutable_index_space_handle.h"
#endif

namespace fiber_bundle
{

class base_space_poset;
class base_space_crg_range;

using namespace sheaf;

// Forward declarations to support friend declaration.

///
/// Insert base_space_crg_range& m into ostream& os.
///
SHEAF_DLL_SPEC ostream& operator <<(ostream& os, const fiber_bundle::base_space_crg_range& m);

SHEAF_DLL_SPEC size_t deep_size(const base_space_crg_range& m);

///
/// Abstract emulator for a range of implicit base space members.
/// @issue this class really should be named homogeneous_block_crg_range.
///
class SHEAF_DLL_SPEC base_space_crg_range : public implicit_crg_range
{

  friend SHEAF_DLL_SPEC ostream& operator <<(ostream& os, const base_space_crg_range& m);
  friend SHEAF_DLL_SPEC size_t deep_size(const base_space_crg_range& m);

  // ===========================================================
  /// @name BASE_SPACE_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor
  ///
  base_space_crg_range();

  ///
  /// Destructor
  ///
  virtual ~base_space_crg_range();

  /// @todo Remove.

//   ///
//   /// An iterator over the block vertices in this range, if any.
//   ///
//   virtual cover_set_iterator block_vertices() const = 0;

  ///
  /// The beginning of the local cells range.
  ///
  virtual pod_index_type cells_begin() const = 0;

  ///
  /// The beginning of the local cells range.
  ///
  void cells_begin(scoped_index& result) const;

  ///
  /// The end of the local cells range.
  ///
  virtual pod_index_type cells_end() const = 0;

  ///
  /// The end of the local cells range.
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

protected:

private:

  //@}


  // ===========================================================
  /// @name BLOCK VERTICES FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if the block vertices id space is initialized.
  ///
  bool block_vertices_initialized() const;

  ///
  /// The block vertices id space.
  ///
  const index_space_handle& block_vertices_id_space() const;

  ///
  /// Allocates an id space iterator from the zone iterator pool.
  ///
  index_space_iterator& get_block_vertices_id_space_iterator() const;

  ///
  /// Returns the id space iterator xitr to the block vertices iterator pool.
  ///
  void release_block_vertices_id_space_iterator(index_space_iterator& xitr) const;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the block vertices iterator pool.
  ///
  bool allocated_block_vertices_id_space_iterator(index_space_iterator& xitr) const;

protected:

  ///
  /// The name of the block vertices id space.
  ///
  string block_vertices_name() const;

  ///
  /// @todo Replace mutable_index_space_handle with a specialized id space
  /// for each block type that calculates the block vertices on the fly.
  ///

  ///
  /// The block vertices id space.
  ///
  mutable_index_space_handle _block_vertices_id_space;

private:

  //@}


  // ===========================================================
  /// @name IMPLICIT_CRG_RANGE FACET
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
  virtual const scoped_index& block_dof_tuple_id() const = 0;

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
  /// The name of this class;
  /// provided to satisfy factory template.
  ///
  virtual const string& class_name() const;

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
  virtual base_space_crg_range* clone() const = 0;

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

///
/// The deep size of the referenced object of type base_space_crg_range.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const base_space_crg_range& xr, bool xinclude_shallow = true);

 
} // namespace fiber_bundle

#endif // ifndef BASE_SPACE_CRG_RANGE_H
