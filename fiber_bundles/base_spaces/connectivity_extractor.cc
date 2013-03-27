// $RCSfile: connectivity_extractor.cc,v $ $Revision: 1.32 $ $Date: 2013/01/12 17:16:51 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class CONNECTIVITY_EXTRACTOR

#include "connectivity_extractor.h"
#include "assert_contract.h"

#include "abstract_poset_member.h"
#include "base_space_member.h"
#include "list_cover_set.h"
#include "poset_state_handle.h"
#include "postorder_member_iterator.h"
#include "subposet_member_iterator.h"

using namespace fiber_bundle; // Workaround for bug in MS C++.

//#define DIAGNOSTIC_OUTPUT

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
fiber_bundle::connectivity_extractor::
connectivity_extractor(const connectivity_extractor& xother)
    : poset_dft(xother.host())
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
fiber_bundle::connectivity_extractor&
fiber_bundle::connectivity_extractor::
operator=(const connectivity_extractor& xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

///
fiber_bundle::connectivity_extractor::
~connectivity_extractor()
{

  // Preconditions:

  // Body:

  _lower_level.detach_from_state();
  _upper_level.detach_from_state();

  // Postconditions:

}

///
bool
fiber_bundle::connectivity_extractor::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(poset_dft::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  // Exit:

  return result;
}


// CONNECTIVITY_EXTRACTOR INTERFACE

///
fiber_bundle::connectivity_extractor::
connectivity_extractor(const poset_state_handle* xhost,
                       const string& xlower_level_subposet_name,
                       const string& xupper_level_subposet_name)
    : poset_dft(xhost)
{

  // Preconditions:

  require(precondition_of(poset_dft::poset_dft));
  require(xhost->includes_subposet(xlower_level_subposet_name));
  require(xhost->includes_subposet(xupper_level_subposet_name));

  require(unexecutable(upper_level subposet id_space() != 0));
  require(unexecutable(lower_level subposet id_space() != 0));

  // Body:

  _lower_level.attach_to_state(xhost, xlower_level_subposet_name);
  _upper_level.attach_to_state(xhost, xupper_level_subposet_name);

  _connectivity_cts = 0;
  _connectivity_cts_ub = 0;
  _connectivity_cts_ct = 0;

  _connectivity = 0;
  _connectivity_ub = 0;
  _connectivity_ct = 0;

  _nodal_connectivity = check_element_types();

#ifdef DIAGNOSTIC_OUTPUT

  cout << ">>>>> _nodal_connectivity = "
  << ( _nodal_connectivity ? "true" : "false")
  << endl;
#endif

  // Postconditions:

  ensure(invariant());
  ensure(connectivity_cts_ct() == 0);
  ensure(connectivity_ct() == 0);

}

///
void
fiber_bundle::connectivity_extractor::
extract(const abstract_poset_member* xanchor,
        int* xdomain_mbrs,
        int xdomain_mbrs_ub,
        int* xconnectivity_cts,
        int xconnectivity_cts_ub,
        int* xconnectivity,
        int xconnectivity_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(host()->contains_member(xanchor));
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ub >= domain_mbrs_ct(xanchor));
  require(xconnectivity_cts != 0);

  // Following call depends on call to domain_mbrs_ct() above

  require(xconnectivity_cts_ub >= connectivity_cts_ct());
  require(xconnectivity != 0);

  // Following call depends on call to domain_mbrs_ct() above

  require(xconnectivity_ub >= connectivity_ct());
  require(upper_level().has_id_space());

  // Body:

  _down_set.clear();

  _below_upper_level = false;
  _extracting = true;
  _first_bdy_seg_reversed = false;

  _connectivity_cts = xconnectivity_cts;
  _connectivity_cts_ub = xconnectivity_cts_ub;
  _connectivity_cts_ct = 0;

  _connectivity = xconnectivity;
  _connectivity_ub = xconnectivity_ub;
  _connectivity_ct = 0;


  int i = 0;
  postorder_member_iterator itr(*xanchor, _upper_level, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    xdomain_mbrs[i++] = upper_level().id_space().pod(itr.item().index());

    traverse(&(itr.item()), true, false);
    itr.next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(connectivity_cts_ct() >= 0);
  ensure(connectivity_ct() >= 0);

  // Exit:

  return;
}


///
void
fiber_bundle::connectivity_extractor::
extract(const int* xdomain_mbrs,
        int xdomain_mbrs_ub,
        int* xconnectivity_cts,
        int xconnectivity_cts_ub,
        int* xconnectivity,
        int xconnectivity_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ub > 0);

  /// @todo make precondition below executable

  require(unexecutable("host contains members with client ids in xdomain_mbrs"));
  require(xconnectivity_cts != 0);
  require(xconnectivity_cts_ub >= xdomain_mbrs_ub);
  require(xconnectivity != 0);
  require(xconnectivity_ub >= connectivity_ct(xdomain_mbrs, xdomain_mbrs_ub));
  require(lower_level().has_id_space());

  // Body:

  _down_set.clear();

  _below_upper_level = false;
  _extracting = true;
  _first_bdy_seg_reversed = false;

  _connectivity_cts = xconnectivity_cts;
  _connectivity_cts_ub = xconnectivity_cts_ub;
  _connectivity_cts_ct = 0;

  _connectivity = xconnectivity;
  _connectivity_ub = xconnectivity_ub;
  _connectivity_ct = 0;

  // Traverse the down set of each entry in xdomain_mbrs;
  // In order to avoid potentially O((mesh size)**2) performance,
  // the has_been_visited bitvector will not be reset between calls.
  // Instead, postvisit action will reset only those bits that are on.

  total_poset_member pm;

  scoped_index pid(upper_level().id_space());
  for(int i= 0; i<xdomain_mbrs_ub; i++)
  {
    pid = xdomain_mbrs[i];

    pm.attach_to_state(host(), pid);

    traverse(&pm, true, false);
  }

  pm.detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(connectivity_cts_ct() >= 0);
  ensure(connectivity_ct() >= 0);

  // Exit:

  return;
}



///
void
fiber_bundle::connectivity_extractor::
count(const abstract_poset_member* xanchor)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(host()->contains_member(xanchor));

  // Body:

  _down_set.clear();

  _below_upper_level = false;
  _extracting = false;
  _first_bdy_seg_reversed = false;

  _connectivity_cts = 0;
  _connectivity_cts_ub = 0;
  _connectivity_cts_ct = 0;

  _connectivity = 0;
  _connectivity_ub = 0;
  _connectivity_ct = 0;


  postorder_member_iterator itr(*xanchor, _upper_level, DOWN, NOT_STRICT);
  while(!itr.is_done())
  {
    traverse(&(itr.item()), true, false);
    itr.next();
  }

  // Postconditions:

  ensure(invariant());
  ensure(connectivity_cts_ct() >= 0);
  ensure(connectivity_ct() >= 0);

  // Exit:

  return;
}


///
void
fiber_bundle::connectivity_extractor::
count(const int* xdomain_mbrs, int xdomain_mbrs_ub)
{
  // Preconditions:

  require(host()->state_is_read_accessible());
  require(xdomain_mbrs != 0);
  require(xdomain_mbrs_ub > 0);

  /// @todo make precondition below executable

  require(unexecutable("host contains members with client ids in xdomain_mbrs"));

  // Body:

  _down_set.clear();

  _below_upper_level = false;
  _extracting = false;
  _first_bdy_seg_reversed = false;

  _connectivity_cts = 0;
  _connectivity_cts_ub = 0;
  _connectivity_cts_ct = 0;

  _connectivity = 0;
  _connectivity_ub = 0;
  _connectivity_ct = 0;

  total_poset_member pm;

  scoped_index pid(upper_level().id_space());
  for(int i= 0; i<xdomain_mbrs_ub; i++)
  {
    pid = xdomain_mbrs[i];

    pm.attach_to_state(host(), pid);

    traverse(&pm, true, false);
  }

  pm.detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(connectivity_cts_ct() >= 0);
  ensure(connectivity_ct() >= 0);

  // Exit:

  return;
}


void
fiber_bundle::connectivity_extractor::
previsit_action(abstract_poset_member* xmbr)
{
  // Preconditions:

  require(!is_nested_upper_level(xmbr));

  // Body:

  if (_below_upper_level)
  {
    _descend = !_lower_level.contains_member(xmbr);
  }
  else if (_upper_level.contains_member(xmbr))
  {
    // Turn on down set collection

    _below_upper_level = true;

    // Store the index of the first connectivity entry for xmbr

    _first_entry = _connectivity_ct;

    if (_nodal_connectivity)
    {
      // Check orientation of first member of lower cover:
      //
      // Let first_bdy_seg refer to the first member of the
      // lower cover of xmbr. We assume that first_bdy_seg is constructed
      // with the proper orientation for the first element
      // it appears in and this first element becomes
      // the first member of the upper cover of first_bdy_seg.
      // So if xmbr is the first mbr of the upper cover of first_bdy_seg,
      // then first_bdy_seg is positively oriented w.r.t. xmbr.
      // Furthermore, since a d-1 boundary segement in a d dimensional space
      // partitions the space, first_bdy_seg has at most 2 mbrs
      // in its upper cover and the second member, if it exists,
      // is negatively oriented. So if xmbr is not the first mbr
      // of the upper cover of first_bdy_seg, first_bdy_seg is negatively
      // oriented w.r.t. xmbr.
      //
      /// @issue the above argument, and hence this implementation,
      /// requires that the _elements subposet contain the maximal jims
      /// of the mesh, i.e. it must contain d-dimension cells in a
      /// d-dimensional mesh.

      pod_index_type xmbr_index = xmbr->index().pod();
      pod_index_type first_bdy_seg_index = xmbr->first_cover_member(LOWER);
      pod_index_type first_upper_of_first_bdy_seg = host()->first_cover_member(UPPER, first_bdy_seg_index);

      _first_bdy_seg_reversed = (xmbr_index != first_upper_of_first_bdy_seg);
    }
  }

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(xmbr in upper_level implies _below_upper_level));

  // Exit:

  return;
}


void
fiber_bundle::connectivity_extractor::
link_action(abstract_poset_member* xmbr, abstract_poset_member* linked_mbr)
{
  // Preconditions:

  // Body:

  // Does nothing in this traverser

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


void
fiber_bundle::connectivity_extractor::
postvisit_action(abstract_poset_member* xmbr)
{

  // Preconditions:

  require(has_been_visited(xmbr));

  // Body:

  if (_upper_level.contains_member(xmbr))
  {
    // Finished with this member of upper_level.

    // Remove up set from visited set
    // so members will be visited again from
    // any other upper_level that contains them.

    while(!_down_set.empty())
    {
      mark_not_visited(_down_set.front());
      _down_set.pop_front();
    }

    if (_extracting)
    {
      // Save the number of connectivity entries for this member.

      _connectivity_cts[_connectivity_cts_ct] = _connectivity_ct - _first_entry;

      if (_first_bdy_seg_reversed)
      {
        // The first boundary segment of this element was negatively oriented
        // and we're extracting connectivity, not just counting.
        // Reverse the first two members of the connectivity for this element.

        /// @issue this only works for d=2, where boundary segments are
        /// edges and reversing the vertices reverses the orientation.

        int second_entry = _first_entry+1;
        int i = _connectivity[_first_entry];


#ifdef DIAGNOSTIC_OUTPUT

        cout << endl;
        cout << "postvisit_action _first_entry = " << _first_entry << endl;
        cout << "postvisit_action second_entry = " << second_entry << endl;
        cout << "postvisit_action _connectivity[second_entry] = "
        << _connectivity[second_entry] << endl;
        cout << "postvisit_action _connectivity[_first_entry] = " << i << endl;
        cout << endl;
#endif

        _connectivity[_first_entry] = _connectivity[second_entry];
        _connectivity[second_entry] = i;
      }
    }

    // Count the member whether extracting or not.

    _connectivity_cts_ct++;

    // Not above an upper_level now.

    _below_upper_level = false;

  }
  else if (_below_upper_level)
  {
    // Enter member in down set

    _down_set.push_front((xmbr->index()).pod());

    if (_lower_level.contains_member(xmbr))
    {
      // Member is a vertex; if extracting store the client id.

      if (_extracting)
      {
        _connectivity[_connectivity_ct] =
          _lower_level.id_space().pod(xmbr->index());
      }

      // Count the connectivity whether extracting or not.

      _connectivity_ct++;
    }
  }

  // Postconditions:

  ensure(invariant());
}

bool
fiber_bundle::connectivity_extractor::
check_element_types() const
{
  // Check the elements "types" to determine:
  //   1. If we want element to node connectivity and
  //   2. If the elements are quads, triangles,
  //      tri_shells, or quad_shells with edges defined.
  //
  // We return true if the above are satisfied;
  // otherwise, we return false.

#ifdef DIAGNOSTIC_OUTPUT
  cout << ">>>>> host = " << host()->name() << endl;
  cout << ">>>>> _upper_level = " << _upper_level.name() << endl;
#endif

  // Check if we want element to node connectivity.

  /// @hack  convenient but ugly method of identifying nodal connectivity.
  /// @error this method requires subposet naming convention but can not
  /// enforce use of the convention.
  /// @todo replace this method.

  bool result = (_lower_level.name() == "__vertices") &&
                (_upper_level.name() == "__elements");

  if (result)
  {
    // Check all of the elements for (2.) above.
    /// @issue Probably could just check the first element.

    subposet_member_iterator* itr = _upper_level.member_iterator();

    while(!itr->is_done())
    {

#ifdef DIAGNOSTIC_OUTPUT
      cout << ">>>>> itr->name() = " << itr->name() << endl;
      cout << ">>>>> itr->index() = " << itr->index() << endl;
#endif

      /// @hack Need to test the base space schema type inorder to determine
      ///         how to extract the dimension and element type information.
      ///         This test will go away once the local_coordinates_schema is
      ///         no longer supported.

      if(itr->schema().conforms_to("local_coordinates_schema/local_coordinates_schema"))
      {
        int dcount = itr->schema().row_dof_ct();
        int* dofs = new int[dcount];
        itr->dof_tuple(dofs, dcount*sizeof(int));

#ifdef DIAGNOSTIC_OUTPUT
        cout << ">>>>> base space schema       = local_coordinate_schema" << endl;
        cout << ">>>>> dimension, element_type = " << dofs[0] << "  " << dofs[1] << endl;
#endif

        int dimension = dofs[0];
        int type = dofs[1];

        // Test for 2d and either "triangle" (type = 4) or "quad" (type = 6)
        // OR 3d and either "tri_shell" (type = 14) or "quad_shell" (type = 16).

        bool match2d = (dimension == 2) && ((type == 4) || (type == 6));
        bool match_shell = (dimension == 2) && ((type == 14) || (type == 16));

        bool match = match2d || match_shell;

        if(!match)
        {
          result = false;
          break;
        }

        delete [] dofs;
      }
      else if(itr->schema().conforms_to("base_space_member_schema/base_space_member_schema"))
      {
        // Attach the iterator to a base_space_member inorder to extract the
        // dimension and prototype_id.

        base_space_member lmember(*itr);

        // Test for 2d and either triangle or quad.

        int db = lmember.db();
        poset_path lpath = lmember.prototype_path();

        // Detach base_space_member so destructor does not fail.

        lmember.detach_from_state();

#ifdef DIAGNOSTIC_OUTPUT

        cout << ">>>>> base space schema = base_space_member_schema" << endl;
        cout << ">>>>> dimension         = " << db << endl;
        cout << ">>>>> prototype_path    = " << lpath << endl;
#endif

        string lposet_name = base_space_member::prototypes_poset_name();
        poset_path ltriangle_path(lposet_name, "triangle");
        poset_path lquad_path(lposet_name, "quad");
        poset_path ltriangle_nodes_path(lposet_name, "triangle_nodes");
        poset_path lquad_nodes_path(lposet_name, "quad_nodes");
        poset_path ltriangle_complex_path(lposet_name, "triangle_complex");
        poset_path lquad_complex_path(lposet_name, "quad_complex");

        bool match = (db == 2) && ((lpath == ltriangle_path) ||
                                   (lpath == lquad_path) ||
                                   (lpath == ltriangle_nodes_path) ||
                                   (lpath == lquad_nodes_path) ||
                                   (lpath == ltriangle_complex_path) ||
                                   (lpath == lquad_complex_path));

        if(!match)
        {
          result = false;
          break;
        }
      }
      else
      {
        post_warning_message("Base space type is not supported");
      }

      itr->next();
    }

  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}
