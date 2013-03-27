// $RCSfile: unstructured_block_builder.h,v $ $Revision: 1.25 $ $Date: 2013/03/13 00:58:41 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class UNSTRUCTURED_BLOCK_BUILDER

#ifndef UNSTRUCTURED_BLOCK_BUILDER_H
#define UNSTRUCTURED_BLOCK_BUILDER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_STACK_H
#include "std_stack.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef SUBPOSET_H
#include "subposet.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif

namespace sheaf
{

class poset_member;
class triorder_iterator;

template<class T>
class ragged_array;

}

namespace fiber_bundle
{

class base_space_member;
class base_space_member_prototype;
class unstructured_block;
 
  using namespace sheaf;





///
/// OBSOLETE: use zone_nodes_block or point_block_*d.
/// A builder object for constructing unstructured blocks given
/// a local cell template and atomic equivalences ("connectivity").
///
class SHEAF_DLL_SPEC unstructured_block_builder
{

public:

  ///
  /// Class invariant
  ///
  virtual bool  invariant() const;

  ///
  /// Default constructor.
  ///
  unstructured_block_builder();

  ///
  /// Destructor
  ///
  ~unstructured_block_builder();

   ///
  /// The type of the temporary cover set lists.
  ///
  typedef list<pod_index_type> list_type;

 //$$TYPE_SAFE_IDS_TODO: Change glue_map_type to use scoped_index..

  ///
  /// The type of the glue map.
  ///
  typedef hash_map<int, int> glue_map_type;

  //$$TYPE_SAFE_IDS_ISSUE: Remove when no longer used?

  ///
  /// Build the unstructured block result using local cell
  /// template xtemplate and the atomic equivalences ("connectivity")
  /// in xglue. If xcompute_upper_cover, compute the join of
  /// the block members to ensure the upper cover is correct,
  /// otherwise use the existing upper cover.
  ///
  void build_block_pa(const base_space_member_prototype* xtemplate,
                      const int* xglue,
                      size_type xglue_ub,
                      unstructured_block* result,
                      bool xcompute_upper_cover,
                      bool xauto_access);

  ///
  /// Build the unstructured block result using local cell
  /// template xtemplate and the atomic equivalences ("connectivity")
  /// in xglue. If xcompute_upper_cover, compute the join of
  /// the block members to ensure the upper cover is correct,
  /// otherwise use the existing upper cover.
  ///
  void build_block_pa(const base_space_member_prototype* xtemplate,
                      const scoped_index* xglue,
                      size_type xglue_ub,
                      unstructured_block* result,
                      bool xcompute_upper_cover,
                      bool xauto_access);

  ///
  /// Creates in xmesh the unrefined blocks and block neighborhoods
  /// described by the client ids in xblock_ids, the dimensions in
  /// xblock_dbs, the templates in xblock_local_cell_paths, and xblock_nbrs.
  ///
  static void build_block_decomposition(base_space_poset* xmesh,
                                        const block<int>& xblock_ids,
                                        const block<int>& xblock_dbs,
                                        const block<poset_path>& xblock_local_cell_paths,
                                        const ragged_array<int>& xblock_nbrs,
                                        bool xauto_access);

  ///
  /// Creates in xmesh the unrefined blocks and block neighborhoods
  /// described by the client ids in xblock_ids and xblock_nbrs.
  /// All blocks have dimension xblock_db and template xblock_local_cell_path.
  ///
  static void build_block_decomposition(base_space_poset* xmesh,
                                        const block<int>& xblock_ids,
                                        int xblock_db,
                                        const poset_path& xblock_local_cell_path,
                                        const ragged_array<int>& xblock_nbrs,
                                        bool xauto_access);

  ///
  /// True if cells should be given unique names.
  ///
  static bool name_mode();

  ///
  /// Sets name_mode to xmode.
  /// Warning: creating meshes with large numbers of names
  /// may exceed limits imposed by storage in HDF files.
  /// Intended for debugging use only.
  ///
  static void put_name_mode(bool xmode);

private:

  ///
  /// The template for making copies
  ///
  base_space_member_prototype* _template;

  ///
  /// The host of the template.
  ///
  base_space_poset _template_host;

  ///
  /// A map from template member index to
  /// result member index for the current copy of the template.
  ///
  hash_map<int, int> _template_map;

  ///
  /// Max cell dimension of template.
  ///
  int _template_db;

  ///
  /// Initializes data members associated with the template.
  ///
  void initialize_template(const base_space_member_prototype* xtemplate);

  ///
  /// The global equivalences for the atoms in the block.
  ///
  int* _glue;

  ///
  /// Upper bound for the _glue.
  ///
  int _glue_ub;

  ///
  /// The current member of _glue.
  ///
  int _glue_index;

  ///
  /// Initializes data members associated with the glue.
  ///
  void initialize_glue(const int* xglue, int xglue_ub);

  ///
  /// The block being built.
  ///
  unstructured_block* _block;

  ///
  /// The host of the block being built.
  ///
  base_space_poset _block_host;

  ///
  /// Subposet of all members in this block.
  ///
  subposet _block_mbrs_sp;

  ///
  /// Array of all members in this block.
  ///
  block<scoped_index> _block_mbrs;

  ///
  /// Initializes data members associated with the block.
  ///
  void initialize_block(unstructured_block* result);

  ///
  /// Dimension of boundary.
  ///
  int _boundary_db;

  ///
  /// True if the template contains members
  /// with the boundary dimension.
  ///
  bool _template_has_boundary;

  ///
  /// Set of maximal jims in the boundary.
  ///
  subposet _boundary_jims;

  ///
  /// Set of block boundaries.
  ///
  subposet _block_boundaries;

  ///
  /// Initializes data members associated with the boundary.
  ///
  void initialize_boundary();

  ///
  /// Map from template dof tuple ids to block dof tuple ids.
  ///
  block<scoped_index> _dof_tuple_id_map;

  ///
  /// Copies dof maps from template into block hoost.
  ///
  void initialize_dof_maps();

  ///
  /// Creates the block.
  ///
  void make_block(bool xcompute_upper_cover);

  ///
  /// Cover sets currently under construction.
  ///
  stack<list_type*> _used_covers;

  ///
  /// Cover sets not currently being used.
  ///
  stack<list_type*> _free_covers;

  ///
  /// Action at previsit position of traversal.
  ///
  void previsit_action(const triorder_iterator& xtmplt_itr, bool& xtruncate);

  ///
  /// Action at link position of traversal.
  ///
  void link_action(const triorder_iterator& xtmplt_itr);

  ///
  /// Action at postvisit position of traversal.
  ///
  void postvisit_action(const triorder_iterator& xtmplt_itr);

  ///
  /// Creates the boundary member for the block.
  /// constructed by the last call to build_block_pa.
  //// @hack this routine should be private and called
  //// by build_block_pa. But its preconditions conflict
  //// with the current preconditions of build_block_pa.
  ////
  void make_boundary();

  ///
  /// Cleans up data members allocated by build_block_pa.
  ///
  void clean_up();

  ///
  /// Determines whether member with hub id xhub_id is in the boundary
  /// and updates _boundary_jims.
  ///
  void update_boundary(pod_index_type xhub_id);

  ///
  /// Determines whether member with id xid is in the boundary
  /// and updates _boundary_jims.
  ///
  void update_boundary(const scoped_index& xid);

  ///
  /// True if cells should be given unique names.
  ///
  static bool _name_mode;

  ///
  /// Creates in mesh xmesh the neighborhoods containing the neighbors
  ///  specified in xblock_nbrs for each block specified in xblock_ids.
  ///
  static void make_block_neighborhoods(base_space_poset* xmesh,
                                       const block<int>& xblock_ids,
                                       const ragged_array<int>& xblock_nbrs,
                                       const index_space_handle& xid_space);

};

} // namespace fiber_bundle

#endif // ifndef UNSTRUCTURED_BLOCK_BUILDER_H
