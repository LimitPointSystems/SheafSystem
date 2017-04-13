
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

// Implementation for class unstructured_block_builder

#include "SheafSystem/unstructured_block_builder.h"

#include "SheafSystem/error_message.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/poset.h"
#include "SheafSystem/poset_path.h"
#include "SheafSystem/postorder_iterator.h"
#include "SheafSystem/preorder_iterator.h"
#include "SheafSystem/ragged_array.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/sheaves_namespace.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/subposet.h"
#include "SheafSystem/triorder_iterator.h"
#include "SheafSystem/unstructured_block.h"
#include "SheafSystem/tern.h"

using namespace std;
using namespace unordered;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

using namespace sheaf;

namespace
{

bool
lower_cover_is_equal(base_space_poset& xblock_host,
		     pod_index_type xmbr_id,
		     unstructured_block_builder::list_type& xcover)
{
  // Preconditions:

  require(xblock_host.contains_member(xmbr_id));

  // Body:

  set<pod_index_type> lcover0;
  index_space_iterator& litr0 = xblock_host.get_cover_id_space_iterator(LOWER, xmbr_id);
  while(!litr0.is_done())
  {
    lcover0.insert(litr0.hub_pod());

    litr0.next();
  }
  xblock_host.release_cover_id_space_iterator(litr0);

  set<pod_index_type> lcover1;
  unstructured_block_builder::list_type::const_iterator litr1 = xcover.begin();
  while(litr1 != xcover.end())
  {
    lcover1.insert(*litr1);

    ++litr1;
  }

  bool result = (lcover0 == lcover1);

  // Postconditions:

  // Exit:

  return result;
}

}; // end unnamed namespace

///
bool
fiber_bundle::unstructured_block_builder::
invariant() const
{
  bool result = true;
  return result;
}


bool
fiber_bundle::unstructured_block_builder::
_name_mode = false;

///
fiber_bundle::unstructured_block_builder::
unstructured_block_builder()
{
  // Preconditions:

  // Body:

  _template = 0;
  _glue = 0;
  _glue_ub = 0;
  _glue_index = sheaf::invalid_pod_index();
  _block = 0;
  _template_db = 0;
  _boundary_db = -1;
  _template_has_boundary = false;
  //_name_mode = false;

  // Postconditions:

  ensure(invariant());
}


///
fiber_bundle::unstructured_block_builder::
~unstructured_block_builder()
{

  // Preconditions:

  // Body:

  while(!_free_covers.empty())
  {
    delete (_free_covers.top());
    _free_covers.pop();
  }

  while(!_used_covers.empty())
  {
    delete (_used_covers.top());
    _used_covers.pop();
  }

  _boundary_jims.detach_from_state();
  _block_boundaries.detach_from_state();

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
build_block_pa(const base_space_member* xtemplate,
               const int* xglue,
               size_type xglue_ub,
               unstructured_block* result,
               bool xcompute_upper_cover,
               bool xauto_access)
{

  // Preconditions:

  require(xtemplate != 0);
  require(xtemplate->state_is_read_accessible());
  require(xtemplate->name_space()->state_is_read_accessible());
  require(xtemplate->is_jim());
  require(xtemplate->schema().row_conforms_to(result->schema()));
  require(xtemplate->atom_ct() > 0);

  require(xglue != 0);
  require(xglue_ub > 0);
  require((xglue_ub % xtemplate->atom_ct()) == 0);

  require(result != 0);
  require(xauto_access || result->host()->in_jim_edit_mode());

  if(xauto_access)
  {
    result->get_read_write_access();
  }

  /// @hack make sure the base space contains the blocks and d_cells subposets.
  /// The following can be removed when base_space_member::host() is base_space_poset.

  require(unexecutable("result host is base space poset"));

  require(result->schema().row_conforms_to(unstructured_block::standard_schema_path()));

  /// @issue Order relation for block member.
  /// The there 2 major steps in building a block:
  /// 1. Create all the cells implied by the template and the glue,
  ///     making sure to identify and use equivalent existing members.
  /// 2. Properly link the cells and the block member to existing members
  ///    making sure to satsify the ordering relation implied by the expansion
  ///    of the block.
  /// This algorithm should operate in two modes:
  /// 1. Computed; the proper linkage is automatically computed by joining
  ///    the cells.
  /// 2. Assumed ("trust me"); the upper cover of the block member is assumed
  ///    to already be correct and the lower cover is assumed to be the
  ///    collection of cells.
  ///
  /// The existing code is a confused attempt to implement the above semantics.
  /// In addition, the matter is further complicated by computing the boundary at
  /// the same time.Constructing the block requires jim_edit_mode, but computing
  /// the boundary is a join which requires !jim_edit_mode. This routine thus is
  /// going to changes jim edit mode no matter which state it is in and we have
  /// no way of stating this as a precondition. Furthermore, these conflict because
  /// of the expense end_jim_edit_mode. A client may want to enter jim_edit_mode
  /// and create multiple blocks before leaving.
  ///
  /// Recommendations:
  /// 1. Added a switch to control computed vs assumed ordering.
  /// 2. Implement computed mode using join.
  /// 3. Add a switch to compute just the _boundary_jims sp or both
  ///    it and the boundary.
  /// 4. Make a separate operation to compute the boundary.

  //   require(result->is_jim() ? result->is_atom() : true);
  //   require(!result->is_jim() ? result->lower_cover_state().empty() : true);
  //   require(!result->is_jim() ? result->upper_cover_state().empty() : true);

  /// @hack instead of resolving the above issue, just insist that we
  /// have a jim and atom and we are not in jim_edit_mode. This forces
  /// end_jim_edit_mode for each block, but also resolves the conflict
  /// with making the boundary.

  require(result->is_jim());
  require(result->is_atom());

  // Body:

  if(xauto_access)
  {
    result->host()->begin_jim_edit_mode(false);
  }


  // Initialize.

  initialize_template(xtemplate);
  initialize_glue(xglue, xglue_ub);
  initialize_block(result);
  initialize_boundary();
  initialize_dof_maps();

  // Make the block itself.

  make_block(xcompute_upper_cover);

  if(xauto_access)
  {
    // Exit jim edit mode but do not ensure lattice invariant
    // because it is expensive and we don't need to do it -
    // the block building routine has properly hooked up everything.
    // Don't release access because we still need it below.

    result->host()->end_jim_edit_mode(false, false);
  }


  if(_template_has_boundary)
  {
    make_boundary();
  }

  // Clean up.

  clean_up();

  // Postconditions:

  ensure(unexecutable("result->host()->blocks().contains_member(result)"));
  ensure(!result->name().empty());
  ensure(!result->is_jim());

  if(xauto_access)
  {
    result->release_access();
  }

  // Exit

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
build_block_pa(const base_space_member* xtemplate,
               const scoped_index* xglue,
               size_type xglue_ub,
               unstructured_block* result,
               bool xcompute_upper_cover,
               bool xauto_access)
{
  //Preconditions:

  //$$TYPE_SAFE_IDS_ISSUE:
  //  We need to replace the  function build_block_pa
  //  which takes an int* xglue with this one.  Need to
  //  move the actual implementation here.  This requires
  //  that we change data member _glue to type scoped_index

  // Body:

  int* lint_glue = new int[xglue_ub];
  for(int i=0; i<xglue_ub; ++i)
  {
    lint_glue[i] = xglue[i].pod();
  }

  build_block_pa(xtemplate,
                 lint_glue,
                 xglue_ub,
                 result,
                 xcompute_upper_cover,
                 xauto_access);

  delete [] lint_glue;

  // Postconditions:


  // Exit

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
build_block_decomposition(base_space_poset* xmesh,
                          const block<int>& xblock_ids,
                          const block<int>& xblock_dbs,
                          const block<poset_path>& xblock_local_cell_paths,
                          const ragged_array<int>& xblock_nbrs,
                          bool xauto_access)
{
  // Preconditions:

  require(xmesh != 0);
  require(xauto_access ? xmesh->is_attached() : xmesh->state_is_read_write_accessible());
  require(xauto_access || xmesh->name_space()->state_is_read_accessible());

  require(xblock_dbs.ct() == xblock_ids.ct());
  require(xblock_local_cell_paths.ct() == xblock_ids.ct());

  require_for_all(i, 0, xblock_dbs.ct(), xblock_dbs[i] >= 0);

  require_for_all(i, 0, xblock_local_cell_paths.ct(),
                  xmesh->name_space()->contains_poset_member(xblock_local_cell_paths[i]));

  require_for_all(i, 0, xblock_local_cell_paths.ct(),
                  xauto_access || xmesh->name_space()->member_poset(xblock_local_cell_paths[i], true).state_is_read_accessible());

  // Body:

  // Create the blocks as jims to be refined later.

  unstructured_block lblock;

  subposet& lblock_sp(xmesh->blocks());
  scattered_insertion_index_space_handle& lid_space = lblock_sp.id_space();

  xmesh->begin_jim_edit_mode(false);
  for(int i=0; i<xblock_ids.ct(); i++)
  {
    if(xauto_access)
    {
      xmesh->name_space()->member_poset(xblock_local_cell_paths[i], true).get_read_access();
    }

    lblock.new_state(xmesh, xblock_local_cell_paths[i].member_name(), false);

    if(xauto_access)
    {
      xmesh->name_space()->member_poset(xblock_local_cell_paths[i], true).release_access();
    }

    lblock_sp.insert_member(&lblock);

    lid_space.insert(xblock_ids[i], lblock.index());

    lblock.put_name(poset_path::block_name(xblock_ids[i]), true, false);
  }

  lblock.detach_from_state();
  lblock_sp.detach_from_state();
  xmesh->end_jim_edit_mode(true, false);

  // Create the block neighborhoods.

  make_block_neighborhoods(xmesh, xblock_ids, xblock_nbrs, lid_space);


#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << "after creating block decomposition:" << endl;
  cout << *xmesh << endl;
#endif

  // Postconditions:

  ensure(xmesh->includes_subposet("__neighborhoods"));

  // Exit:

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
build_block_decomposition(base_space_poset* xmesh,
                          const block<int>& xblock_ids,
                          int xblock_db,
                          const poset_path& xblock_local_cell_path,
                          const ragged_array<int>& xblock_nbrs,
                          bool xauto_access)
{
  // Preconditions:

  require(xmesh != 0);
  require(xauto_access ? xmesh->is_attached() : xmesh->state_is_read_write_accessible());
  require(xblock_db >= 0);
  require(xauto_access || xmesh->name_space()->state_is_read_accessible());
  require(xmesh->name_space()->contains_poset_member(xblock_local_cell_path, true));
  require(xauto_access || xmesh->name_space()->member_poset(xblock_local_cell_path, true).state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xmesh->get_read_write_access();
    xmesh->name_space()->get_read_access();
    xmesh->name_space()->member_poset(xblock_local_cell_path, false).get_read_access();
  }

  // Create the blocks as jims to be refined later.

  unstructured_block lblock;

  subposet& lblock_sp = xmesh->blocks();
  scattered_insertion_index_space_handle& lid_space = lblock_sp.id_space();

  scoped_index lblock_dof_tuple_id;

  xmesh->begin_jim_edit_mode(false);

  for(int i=0; i<xblock_ids.ct(); i++)
  {
    if(i == 0)
    {
      // This is the first block;
      // create the block and initialize the block dof tuple.

      lblock.new_state(xmesh, xblock_local_cell_path.member_name(), false);
      lblock.dof_tuple_id(lblock_dof_tuple_id, false);
    }
    else
    {
      // This is a subsequent block;
      // create the block using the block dof tuple id.

      lblock.new_jim_state(lblock_dof_tuple_id, false);
    }

    lblock_sp.insert_member(&lblock);

    lid_space.insert(xblock_ids[i], lblock.index());

    lblock.put_name(poset_path::block_name(xblock_ids[i]), true, false);
  }

  lblock.detach_from_state();
  lblock_sp.detach_from_state();
  xmesh->end_jim_edit_mode(true, false);

  // Create the block neighborhoods.

  make_block_neighborhoods(xmesh, xblock_ids, xblock_nbrs, lid_space);


#ifdef DIAGNOSTIC_OUTPUT

  cout << endl << "after creating block decomposition:" << endl;
  cout << *xmesh << endl;
#endif

  // Postconditions:

  ensure(xmesh->includes_subposet("__neighborhoods"));

  if(xauto_access)
  {
    xmesh->release_access();
    xmesh->name_space()->release_access();
    xmesh->name_space()->member_poset(xblock_local_cell_path, false).release_access();
  }

  // Exit:

  return;
}


///
bool
fiber_bundle::unstructured_block_builder::
name_mode()
{
  bool result;

  // Preconditions:


  // Body:

  result = _name_mode;

  // Postconditions:


  // Exit:

  return result;
}

///
void
fiber_bundle::unstructured_block_builder::
put_name_mode(bool xmode)
{
  // Preconditions:


  // Body:

  _name_mode = xmode;

  // Postconditions:

  ensure(name_mode() == xmode);

  // Exit:

  return;
}


///
void
fiber_bundle::unstructured_block_builder::
initialize_template(const base_space_member* xtemplate)
{
  // Preconditions:

  require(xtemplate != 0);
  require(xtemplate->state_is_read_accessible());
  require(xtemplate->schema().row_conforms_to(base_space_member::standard_schema_path()));
  require(unexecutable("template contains atoms"));

  // Body:

  _template = const_cast<base_space_member*>(xtemplate);
  _template_host.attach_to_state(xtemplate->host());
  _template_map.clear();
  _template_db = _template->db();


  // Postconditions:

  ensure(_template == xtemplate);
  ensure(_template_map.empty());
  ensure(_template_db >= 0);

  // Exit:

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
initialize_glue(const int* xglue, int xglue_ub)
{
  // Preconditions:

  require(xglue != 0);
  require(xglue_ub > 0);

  // Body:

  _glue = const_cast<int*>(xglue);
  _glue_ub = xglue_ub;
  _glue_index = 0;

  // Postconditions:

  ensure(_glue == xglue);
  ensure(_glue_ub == xglue_ub);
  ensure(_glue_index == 0);

  // Exit:

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
initialize_block(unstructured_block* result)
{
  // Preconditions:

  require(result != 0);
  require(result->state_is_read_write_accessible());
  require(result->host()->in_jim_edit_mode());
  require(result->schema().row_conforms_to(base_space_member::standard_schema_path()));
  require(result->is_jim());
  require(result->is_atom());

  // Body:

  _block = result;

  // We're going to redefine the lower cover, so disconnect it from bottom.

  _block->delete_cover_link(&(_block->host()->bottom()));

  // Initialize a handle for the block host and block mbrs subposet.

  _block_host.attach_to_state(result->host());
  _block_mbrs_sp.new_state(&_block_host);

  // Allocate space for the block mbrs array.

  _block_mbrs.reserve(_glue_ub/_template->atom_ct());

  // Postconditions:

  ensure(_block == result);
  ensure(_block_host.is_same_state(result->host()));

  // Exit:

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
initialize_boundary()
{
  // Preconditions:

  require(_template_db >= 0);
  require(_template != 0);
  require(_template->state_is_read_accessible());
  require(_block_host.state_is_read_write_accessible());

  // Body:

  // The dimension of the boundary is one less than the dimension
  // of the host and if the dimension of the lower cover of _template
  // is the boundary dimension, then the template includes its boundary.

  /// @issue this assumes the host will contain, sooner or later,
  /// blocks of maximal dimension. It also enforces a "manifold" condition
  /// on the boundary - it has uniform dimension. This condition
  /// precludes "non-manifold" boundaries. For instance, the boundary of
  /// a 3D object with a 2D fin does not include the edge of the 2D fin.


  _boundary_db = _block_host.max_db() - 1;
  if(_boundary_db >= 0)
  {
    int lc_dim = _template_host.db(_template->first_cover_member(LOWER));
    _template_has_boundary = ( lc_dim == _boundary_db);
  }
  else
  {
    _template_has_boundary = false;
  }

  _boundary_jims.detach_from_state();
  if(_block_host.includes_subposet("__boundary_jims"))
  {
    _boundary_jims.attach_to_state(&_block_host, "__boundary_jims");
  }
  else
  {
    _boundary_jims.new_state(&_block_host);
    _boundary_jims.put_name("__boundary_jims", true, false);
  }

  _block_boundaries.detach_from_state();
  if(_block_host.includes_subposet("__block_boundaries"))
  {
    _block_boundaries.attach_to_state(&_block_host, "__block_boundaries");
  }
  else
  {
    _block_boundaries.new_state(&_block_host);
    _block_boundaries.put_name("__block_boundaries", true, false);
  }

  // Postconditions:

  ensure(_boundary_db == _block_host.max_db() - 1);
  ensure(_template_has_boundary ? _boundary_db >= 0 : true);
  ensure(_block_host.includes_subposet("__boundary_jims"));
  ensure(_boundary_jims.is_attached());
  ensure(_boundary_jims.host()->is_same_state(&_block_host));
  ensure(_block_host.includes_subposet("__block_boundaries"));
  ensure(_block_boundaries.is_attached());
  ensure(_block_boundaries.host()->is_same_state(&_block_host));

  // Exit:

  return;
}


///
void
fiber_bundle::unstructured_block_builder::
initialize_dof_maps()
{
  // Preconditions:

  require(_template->schema().row_conforms_to(_block_host.schema()));
  require(_template->name_space()->state_is_read_accessible());
  require(_block_host.state_is_read_write_accessible());

  // Body:

  // We want the block to have exactly one copy of the dof map for each cell type.
  // It is efficient in the construction loop to have a map from template member
  // index to block dof tuple id. We will construct that map here. To ensure
  // that there is a single copy for each cell type, we first need to construct
  // a map form cell type to block dof tuple id.

  // Allocate a map from cell types to block dof tuple ids.
  // need enough capacity to store any cell type,
  // i.e. any member index from prototypes poset.

  poset& lprototypes =
    _template->name_space()->member_poset<poset>(base_space_member::prototypes_poset_name(), false);

  scoped_index ltype_id_ub = lprototypes.member_index_ub();

  block<scoped_index> ltype_map(ltype_id_ub.pod());

  ltype_map.set_ct(ltype_id_ub.pod());

  ltype_map.assign(_block_host.dof_tuple_id(invalid_pod_index(), false));

  // Insert all the existing dof tuples.

  for(pod_index_type i = 0; i<_block_host.row_dof_tuple_ct(); ++i)
  {
    void* ltuple_ptr = _block_host.row_dof_map(i).dof_tuple();

    base_space_poset::row_dof_tuple_type* lrow_tuple_ptr =
      reinterpret_cast<base_space_poset::row_dof_tuple_type*>(ltuple_ptr);

    ltype_map[lrow_tuple_ptr->type_id] = i;
  }

  // Initialize the template index to block dof tuple id map.

  _dof_tuple_id_map.reserve(_template_host.member_index_ub().pod());

  _dof_tuple_id_map.set_ct(_dof_tuple_id_map.ub());

  _dof_tuple_id_map.assign(scoped_index::INVALID());

  // Populate the template index to block dof tuple id map.
  // Copy the dof tuples of any cell types that are in the
  // template but not yet in the block.

  postorder_iterator itr(*_template, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    scoped_index lblk_tuple_id = _block_host.dof_tuple_id(false);
    scoped_index lindex = itr.index();
    pod_index_type ltmp_tuple_id =
      _template_host.member_dof_tuple_id(lindex.pod(), false);

    if(is_valid(ltmp_tuple_id))
    {
      // Template member has a dof tuple; get the cell type.

      pod_index_type ltype_id = _template_host.type_id(lindex);
      lblk_tuple_id = ltype_map[ltype_id];

      if(!lblk_tuple_id.is_valid())
      {
        // The cell type is not in the map yet;
        // copy the dof tuple into the block and insert the cell type in the map.
        // Note that preconditions guarantee template tuple is at least
        // as long as block tuple, but may be longer. Make sure block tuple
        // controls transfer so correct number of bytes get copied.


        lblk_tuple_id = _block_host.new_row_dof_map();

        poset_dof_map& lblk_dof_map = _block_host.row_dof_map(lblk_tuple_id, true);
        poset_dof_map& ltmp_dof_map = _template->host()->row_dof_map(ltmp_tuple_id);
        lblk_dof_map.put_dof_tuple(ltmp_dof_map.dof_tuple(), ltmp_dof_map.dof_tuple_ub());

        // Insert cell type and block tuple id in map.

        ltype_map[ltype_id] = lblk_tuple_id;
      }
    }
    else
    {
      // Template member does not have a dof tuple.

      lblk_tuple_id.invalidate();
    }

    // Insert the template member id and block dof tuple id in the map.

    _dof_tuple_id_map[lindex.pod()] = lblk_tuple_id;

    itr.next();
  }

  // Postconditions:

  ensure(unexecutable("template dof maps duplicated in block host"));
  ensure(unexecutable("_dof_tuple_id_map initialized"));

  // Exit

  return;
}


///
void
fiber_bundle::unstructured_block_builder::
make_block(bool xcompute_upper_cover)
{
  // Preconditions:

  require(_block->is_jim());
  require(unexecutable("all data members initialized"));

  // Body:

  // Repeatedly traverse the template, making copies of it
  // and gluing them together with the equivalences in _glue.

  size_type lblk_size = 0;

  triorder_iterator ltmplt_itr(*_template, DOWN, NOT_STRICT);
  bool ltruncate = false;

  while(_glue_index < _glue_ub)
  {
    // Copy the template.

    while(!ltmplt_itr.is_done())
    {
      switch(ltmplt_itr.action())
      {
      case triorder_iterator::PREVISIT_ACTION:
        previsit_action(ltmplt_itr, ltruncate);
        break;
      case triorder_iterator::LINK_ACTION:
        link_action(ltmplt_itr);
        ltruncate = false;
        break;
      case triorder_iterator::POSTVISIT_ACTION:
        postvisit_action(ltmplt_itr);
        ltruncate = false;
        break;
      default:
        // Should be unreachable.
        post_fatal_error_message("Unrecognized iterator action.");
        break;
      }
      ltmplt_itr.next(ltruncate);
    }

    // Count the cells in the block.

    lblk_size++;

    // Reset for next copy of template

    _template_map.clear();
    ltmplt_itr.reset();
  }

  if(xcompute_upper_cover)
  {
    // Compute the block as the join of its members.
    // Ensures proper lower and upper cover.

    /// @hack the "pointer bug" again.
    /// Can't use _block_host in the new_jrm_state call below
    /// because _block_host gets deleted.

    poset* lhost = _block->host();

    /// @hack have to throw away the existing state
    /// because joiner won't use it. But keep the dof tuple.

    /// @hack Have to store the top pod instead of the scoped index
    /// because the state is deleted which deletes the dof tuple id space.

    pod_index_type ltuple_id = _block->dof_tuple_id(false);
    _block->delete_state();

    // block members have an empty upper cover.
    // Link them to the top, this is what ensure_lattice_invariant would do.

    size_type lct = _block_mbrs.ct();
    for(size_type i=0; i<lct; ++i)
    {
      lhost->new_link(TOP_INDEX, _block_mbrs[i].hub_pod());
    }

    // Now join them.

    _block->new_jrm_state(lhost, _block_mbrs.base(), _block_mbrs.ct(), tern::TRUE, false);

    // Restore the dof tuple.

    _block->put_dof_tuple_id(lhost->dof_tuple_id(ltuple_id, false), false);
  }
  else
  {
    // Just assume the upper cover is correct and
    // the block covers its members.

    const scoped_index& lblk_id = _block->index();
    size_type lct = _block_mbrs.ct();
    for(size_type i=0; i<lct; ++i)
    {
      _block_host.new_link(lblk_id, _block_mbrs[i]);
    }
  }

  // Update the number of cells in the block.

  _block->put_size(lblk_size);

  // The block member is no longer a jim.

  _block_host.jims().remove_member(_block);

  // Make sure the block is in the blocks subposet.

  subposet& lblocks_sp = _block_host.blocks();
  if(!lblocks_sp.contains_member(_block))
  {
    lblocks_sp.insert_member(_block);
    lblocks_sp.id_space().push_back(_block->index());
  }

  // Make sure the block has a name.

  if(_block->name().empty())
  {
    scoped_index lseq_id(_block_host.blocks().id_space(), _block->index());

    _block->put_name(poset_path::make_name("__block_", lseq_id.pod(), ""), true, false);
  }


  // Postconditions:

  ensure(_block->db() == _template_db);
  ensure(_block->local_cell_type_id() == _template->type_id());
  ensure(_block->size() > 0);
  ensure(!_block->is_jim());
  ensure(_block_host.blocks().contains_member(_block));
  ensure(!_block->name().empty());

  // Exit:

  return;
}


///
void
fiber_bundle::unstructured_block_builder::
previsit_action(const triorder_iterator& xtmplt_itr, bool& xtruncate)
{
  // Preconditions:

  // Body:

  if(_template_host.is_atom(xtmplt_itr.index()))
  {
    // The current item is an atom, its lower cover contains only the bottom;
    // don't want to visit the bottom.

    xtruncate = true;
  }
  else
  {
    // The current item is not an atom;
    // get a lower cover set.

    list_type* lcover;

    if(_free_covers.empty())
    {
      // No free iterators, have to make one.

      lcover = new list_type;
    }
    else
    {
      // Just get one from the free stack.

      lcover = _free_covers.top();
      _free_covers.pop();
    }

    _used_covers.push(lcover);

    // Continue descent of template.

    xtruncate = false;
  }

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
link_action(const triorder_iterator& xtmplt_itr)
{
  // Preconditions:

  // Body:

  unordered_map<int,int>::iterator itr = _template_map.find(xtmplt_itr.lesser_index().pod());

  // Find must succeed.

  assertion(itr != _template_map.end());

  // Put the found index into the cover on the top of the stack.

  _used_covers.top()->push_back(itr->second);

  // Postconditions:

  // Exit

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
postvisit_action(const triorder_iterator& xtmplt_itr)
{

  // Preconditions:

  require(xtmplt_itr.index() != BOTTOM_INDEX);

  // Body:

  const scoped_index& ltmplt_mbr_id = xtmplt_itr.index();
  int lmbr_db = _template_host.db(ltmplt_mbr_id);

  scoped_index lblk_mbr_id(_block_host.member_hub_id_space(false));

  int glue_id;

  if(_template_host.is_atom(ltmplt_mbr_id))
  {
    // Template member is an atom.

    // Get the next id from the glue array and increment the glue index.

    glue_id = _glue[_glue_index];
    _glue_index++;

    // If the id has been used before, get the block member index associated with it;
    // otherwise, create a new member.

    scattered_insertion_index_space_handle& lid_space = _block_host.d_cells_id_space(lmbr_db);

    lblk_mbr_id = lid_space.hub_pod(glue_id);

    if(!lblk_mbr_id.is_valid())
    {
      // Current glue id has not been used before; create a new member
      // using the block's copy of the template member's dof tuple.

      const scoped_index& lblk_tuple_id =
	_dof_tuple_id_map[ltmplt_mbr_id.pod()];

      _block_host.new_member(_template_host.is_jim(ltmplt_mbr_id.pod()),
			     lblk_tuple_id,
			     lblk_mbr_id);

      // The new member is an atom, link it to the bottom.

      _block_host.new_link(lblk_mbr_id.pod(), BOTTOM_INDEX);

      // The new member is a member of this block.

      _block_mbrs_sp.insert_member(lblk_mbr_id.pod());

      if(_template_has_boundary && (_boundary_db == 0))
      {
        // The new member is the same dimension as the boundary.
        // Assume it is in the boundary, it will be removed later if not.

        _boundary_jims.insert_member(lblk_mbr_id.pod());
      }

      // Insert it in the vertices subposet and client id map

      _block_host.d_cells(lmbr_db).insert_member(lblk_mbr_id.pod());

      lid_space.insert(glue_id, lblk_mbr_id.pod());

      _block_host.cells().insert_member(lblk_mbr_id);

      scattered_insertion_index_space_handle& lid_space2 = _block_host.cells().id_space();
      lid_space2.push_back(lblk_mbr_id);

      if(_name_mode)
      {
        // Give the cell a name.

        string lsp_name(_block_host.d_cells(lmbr_db).name());
        string lname(poset_path::make_name(lsp_name, glue_id, ""));
        _block_host.put_member_name(lblk_mbr_id.pod(), lname, true, false);
      }
    }

    // Now we have the member associated with the glue id;
    // put it in the template map.

    _template_map.insert(unordered_map<int, int>::value_type(ltmplt_mbr_id.pod(), lblk_mbr_id.pod()));

  } // end xmbr is an atom
  else
  {
    // Temaplate member is not an atom.

    // Check to see if any members already in the block have
    // a lower cover identical to whats currently on the stack
    // If there are any such members, they must be in the upper cover
    // of every member of the cover on the stack, hence they must be
    // in the upper cover of the first member. Check the lower cover of
    // every member of the upper cover of the first member of the cover
    // on the stack.

    list_type* lc = _used_covers.top();

    // Lc can not be empty at this point.

    assertion(!lc->empty());

    index_space_iterator& uc_itr =
      _block_host.get_cover_id_space_iterator(UPPER, *(lc->begin()));

    while(!uc_itr.is_done())
    {
      lblk_mbr_id = uc_itr.hub_pod();
      if(lower_cover_is_equal(_block_host, lblk_mbr_id.pod(), *lc))
      {
        break;
      }

      uc_itr.next();
    }

    if(uc_itr.is_done())
    {
      // Couldn't find an existing member; have to create one
      // using the block's copy of the template member's dof tuple.

      scoped_index lblk_tuple_id = _dof_tuple_id_map[ltmplt_mbr_id.pod()];

      _block_host.new_member(_template_host.is_jim(ltmplt_mbr_id),
			     lblk_tuple_id,
			     lblk_mbr_id);

      // New member is a member of this block.

      _block_mbrs_sp.insert_member(lblk_mbr_id.pod());

      // Insert the new member in the appropriate cells subposet and client id map.

      _block_host.d_cells(lmbr_db).insert_member(lblk_mbr_id.pod());

      scattered_insertion_index_space_handle& lid_space = _block_host.d_cells_id_space(lmbr_db);
      lid_space.push_back(lblk_mbr_id.pod());

      _block_host.cells().insert_member(lblk_mbr_id);

      scattered_insertion_index_space_handle& lid_space2 = _block_host.cells().id_space();
      lid_space2.push_back(lblk_mbr_id);

      if(_name_mode)
      {
        // Give the cell a name.

        pod_index_type lclient_id = lid_space.pod(lblk_mbr_id.pod());

        string lname = _block_host.d_cells(lmbr_db).name();

        lname  = poset_path::make_name(lname, lclient_id, "");

        _block_host.put_member_name(lblk_mbr_id.pod(), lname, true, false);
      }


      if(_template_has_boundary && (lmbr_db == _boundary_db))
      {
        // The new member is the same dimension as the boundary.
        // Assume it is in the boundary, it will be removed later if not.

        _boundary_jims.insert_member(lblk_mbr_id.pod());
      }

      // Link the new member to the members in the lower cover on
      // the top of the stack.

      if(_template_has_boundary && lmbr_db == _template_db)
      {
        // The new member has the same dimension as the template, so
        // its lower cover must have the same dimension as the boundary.
        // Link the new member and then update the boundary status of
        // each lower cover member.

        list_type::iterator lc_itr = lc->begin();
        while(lc_itr != lc->end())
        {
          pod_index_type lc_mbr_id = *lc_itr;
          _block_host.new_link(lblk_mbr_id.pod(), lc_mbr_id);
          update_boundary(lc_mbr_id);
          lc_itr++;
        }

      }
      else
      {
        // The lower cover can not be the boundary.
        // Just link the new member to the lower cover.

        list_type::iterator lc_itr = lc->begin();
        while(lc_itr != lc->end())
        {
          _block_host.new_link(lblk_mbr_id.pod(), *lc_itr);
          lc_itr++;
        }
      }

    } // end create new member
    else
    {
      // Member already exists;
      // just terminate the iterator to be safe.

      uc_itr.force_is_done();
    }

    _block_host.release_cover_id_space_iterator(uc_itr);

    // Put the block member index into the template map
    // so we can retrieve it in link_action.

    _template_map.insert(unordered_map<int, int>::value_type(ltmplt_mbr_id.pod(), lblk_mbr_id.pod()));

    // Finished with the cover on top of the stack;
    // empty it and push it on to the free stack for reuse.

    list_type* cover = _used_covers.top();
    _used_covers.pop();
    cover->clear();
    _free_covers.push(cover);

  } // end xmbr is not an atoom


#ifdef DIAGNOSTIC_OUTPUT
  cout << "mbr: " << setw(2) << lblk_mbr_id;
  cout << " lower cover: ";
  cover_set_iterator litr = _block_host.cover_iterator(LOWER, lblk_mbr_id.pod());
  while(!litr.is_done())
  {
    cout << litr.item() << " ";
    litr.next();
  }
  cout << endl;
#endif

  if(ltmplt_mbr_id ==~ _template->index())
  {
    // We're finished.

    // Store the member.

    _block_mbrs.push_back(lblk_mbr_id);

    ///     /// @hack assume the lower cover of the block contains precisely
    ///     /// the local cells in the block, not any intervening jrms.
    ///     /// See discussion of issue in build_block_pa.

    //     // Link the block to the current local cell.

    //     _block_host.new_link(_block->index(), lblk_mbr_id);
  }

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
make_boundary()
{
  // Preconditions:

  require(_template_has_boundary);

  // Body:

  // Allocate some storage for the boundary jims;
  // initial size is arbitrary but large enough to
  // prevent many small reallocations.

  block<scoped_index> lblock_bdy_jims(1024);

  // Find the boundary jims of this block.

  preorder_iterator itr(*_block, _boundary_jims, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    lblock_bdy_jims.push_back(itr.index());
    itr.truncate();
  }

  if(lblock_bdy_jims.ct() > 0)
  {
    // The boundary of the block is not empty; join its members.

    total_poset_member lbdy(&_block_host,
                            lblock_bdy_jims.base(),
                            lblock_bdy_jims.ct(),
                            tern::TRUE,
                            false);
    lbdy.put_name(poset_path::boundary_prefix() + _block->name(), true, false);
    _block_boundaries.insert_member(&lbdy);
    lbdy.detach_from_state();
  }

  // Postconditions:


  // Exit:

  return;
}


///
void
fiber_bundle::unstructured_block_builder::
clean_up()
{
  // Preconditions:

  // Body:

  _template = 0;
  _template_host.detach_from_state();
  _template_map.clear();
  _template_db = 0;


  _glue = 0;
  _glue_ub = 0;
  _glue_index = sheaf::invalid_pod_index();

  _block = 0;
  _block_mbrs_sp.delete_state();


  _boundary_db = -1;
  _template_has_boundary = false;


  _dof_tuple_id_map.set_ct(0);

  _block_host.detach_from_state();

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::unstructured_block_builder::
update_boundary(pod_index_type xhub_id)
{
  // Preconditions:

  require(_block_host.contains_member(xhub_id));
  require(!_block_host.cover_is_empty(UPPER, xhub_id));
  require(_block_host.is_jim(xhub_id));
  require(_block_host.db(xhub_id) == _boundary_db);

  // Body:

  // Since xhub_id is a jim with same dimension as boundary,
  // it can have at most 2 members in its upper over when
  // construction is complete. If it has 2 members and both
  // are members of this block, then it is internal to the block.
  // If it has only 1, or it has two, one in this block and
  // one not in this block, then it is in the boundary.
  //
  // All members with the boundary dimension are inserted in
  // _boundary_jims when they are created. We have just inserted
  // another member in the upper cover of this member.
  // Since scattered_insertion_index_space::push_back ensures the member is
  // at the back of the list, if the upper cover contains a member
  // not in this block, it must be the first member of the upper cover.

  if(!_block_host.cover_is_singleton(UPPER, xhub_id) &&
      _block_mbrs_sp.contains_member(_block_host.first_cover_member(UPPER, xhub_id)))
  {
    _boundary_jims.remove_member(xhub_id);
  }

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::unstructured_block_builder::
update_boundary(const scoped_index& xid)
{
  // Preconditions:

  require(_block_host.contains_member(xid));
  require(!_block_host.cover_is_empty(UPPER, xid));
  require(_block_host.is_jim(xid));
  require(_block_host.db(xid) == _boundary_db);

  // Body:

  update_boundary(xid.hub_pod());

  // Postconditions:


  // Exit:

  return;
}

///
void
fiber_bundle::unstructured_block_builder::
make_block_neighborhoods(base_space_poset* xmesh,
                         const block<int>& xblock_ids,
                         const ragged_array<int>& xblock_nbrs,
                         const index_space_handle& xid_space)
{
  // Preconditions:

  require(xmesh != 0);
  require(xmesh->state_is_read_write_accessible());

  // Body:

  total_poset_member lnbrhd;
  subposet lnbrhd_sp(xmesh);
  lnbrhd_sp.put_name("__neighborhoods", true, false);
  block<scoped_index> lnbrs(32); // arbitrary, avoids many small reallocations.

  for(int i=0; i<xblock_nbrs.row_ct(); i++)
  {
    // Convert the neighbor ids to poset ids.

    lnbrs.set_ct(0);
    scoped_index lid(xmesh->member_hub_id_space(false));
    for(int j=0; j<xblock_nbrs.col_ct(i); j++)
    {
      lid = xid_space.hub_pod(xblock_nbrs[i][j]);
      lnbrs.push_back(lid);
    }

    // The neighborhood member is the join of the neighbors.

    lnbrhd.new_jrm_state(xmesh, lnbrs.base(), lnbrs.ct(), tern::TRUE, false);

    // Name it after the current member.

    lnbrhd.put_name(poset_path::block_neighborhood_name(xblock_ids[i]), true, false);

    // Put it in the subposet of neighborhoods.

    lnbrhd_sp.insert_member(&lnbrhd);
  }
  lnbrhd.detach_from_state();
  lnbrhd_sp.detach_from_state();

  // Postconditions:

  ensure(xmesh->includes_subposet("__neighborhoods"));

  // Exit:

  return;
}
