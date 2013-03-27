
// $RCSfile: vd_field.cc,v $ $Revision: 1.26 $ $Date: 2013/03/13 00:58:56 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class vd_field

#include "vd_field.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "block_impl.h"
#include "chart_point.h"
#include "discretization_iterator.h"
#include "discretization_pusher.h"
#include "error_message.h"
#include "eval_family.h"
#include "field_eval_iterator.h"
#include "name_map.h"
#include "namespace_poset_member.h"
#include "poset_path.h"
#include "print_property_dofs_action.h"
#include "property_disc_iterator.h"
#include "put_property_dofs_fcn_action.h"
#include "sec_ed_invertible.h"
#include "section_evaluator.h"
#include "section_pusher.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "subposet.h"

using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// VD_FIELD FACET
// ===========================================================

///
fields::vd_field::
vd_field()
{
  // Preconditions:

  // Body:

  _coordinates = new sec_ed_invertible;
  _property    = new sec_vd;
  _base_space  = new base_space_member;

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

///
fields::vd_field::
vd_field(const vd_field& xother, bool xauto_access)
{
  // Preconditions:

   require(xauto_access || !xother.is_attached() || \
           xother.state_is_read_accessible());

  // Body:

  _coordinates = xother._coordinates->clone(false, xauto_access);
  _property    = xother._property->clone(false, xauto_access);
  _base_space  = xother._base_space->clone(false, xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(coordinates().is_same_state(&xother.coordinates()));
  ensure(property().is_same_state(&xother.property()));
  ensure(base_space().is_same_state(&xother.base_space()));

  // Exit:

  return;
}

///
fields::vd_field::
vd_field(const sec_ed& xcoordinates, const sec_vd& xproperty,
         bool xauto_access)
{
  // Preconditions:

  require(xcoordinates.is_attached());
  require(xproperty.is_attached());
  require(xauto_access || xcoordinates.state_is_read_accessible());
  require(xauto_access || xproperty.state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xcoordinates.get_read_access();
    xproperty.get_read_access();
  }

  _coordinates = new sec_ed_invertible(xcoordinates);

  _property    = xproperty.clone(false, false);

  /// @hack schema().base_space() isn't a base_space_member,
  ///       so we can't clone it.

  _base_space  = new base_space_member(xproperty.schema().base_space());

  if(xauto_access)
  {
    xcoordinates.release_access();
    xproperty.release_access();
  }

  // Postconditions:

  ensure(invariant());
  ensure(coordinates().is_same_state(&xcoordinates));
  ensure(property().is_same_state(&xproperty));

  // Exit:

  return;
}

///
fields::vd_field::
vd_field(namespace_poset& xns,
         const poset_path& xcoordinates_path,
         const poset_path& xproperty_path,
         bool xauto_access)
{

  // Preconditions:

  require(xauto_access || xns.state_is_read_accessible());
  require(xns.contains_poset_member(xcoordinates_path));
  require(xauto_access ||
          xns.member_poset(xcoordinates_path)->state_is_read_accessible());
  require(xns.contains_poset_member(xproperty_path));
  require(xauto_access ||
          xns.member_poset(xproperty_path)->state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xns.get_read_access();
  }

  _coordinates = new sec_ed_invertible(&xns, xcoordinates_path, xauto_access);

  /// @issue how to we create the specific section type for the property?

  _property    = new sec_vd(&xns, xproperty_path, xauto_access);

  if(xauto_access)
  {
    _coordinates->get_read_access();
    _property->get_read_access();
  }

  /// @hack schema().base_space() isn't a base_space_member, so we can't clone it.

  _base_space  = new base_space_member(_property->schema().base_space());

  if(xauto_access)
  {
    _coordinates->release_access();
    _property->release_access();
  }

  // Postconditions:

  ensure(invariant());
  ensure(coordinates().path(true) == xcoordinates_path);
  ensure(property().path(true) == xproperty_path);

  // Exit:

  return;
}

///
fields::vd_field::
vd_field(const sec_ed& xcoordinates, const vd_field& xother,
         bool xauto_access)
{

  // Preconditions:

  require(xcoordinates.is_attached());
  require(xother.is_attached());
  require(xauto_access || xcoordinates.state_is_read_accessible());
  require(xauto_access || xother.state_is_read_accessible());

  /// @todo finish preconditions; see preconditions of section_pusher.

  // Body:

  if(xauto_access)
  {
    xcoordinates.get_read_access();
    xother.get_read_access();
  }

  _coordinates = new sec_ed_invertible(xcoordinates);

  section_pusher lpusher(xother, xcoordinates, xauto_access);

  _property = lpusher.push(xother.property(), xauto_access);

  /// @hack schema().base_space() isn't a base_space_member, so we can't clone it.

  _base_space  = new base_space_member(xcoordinates.schema().base_space());

  if(xauto_access)
  {
    xcoordinates.release_access();
    xother.release_access();
  }

  // Postconditions:

  ensure(invariant());
  ensure(coordinates().is_same_state(&xcoordinates));
  // Following is unexecutable because requires read access.
  ensure(unexecutable(property().schema().fiber_space().is_same_state(&xother.property().schema().fiber_space())));

  // Exit:

  return;
}


///
fields::vd_field::
~vd_field()
{
  // Preconditions:


  // Body:

  _coordinates->detach_from_state();
  delete _coordinates;

  _property->detach_from_state();
  delete _property;

  _base_space->detach_from_state();
  delete _base_space;

  // Exit:

  return;
}

///
int
fields::vd_field::
dc() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = _coordinates->schema().df();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

///
int
fields::vd_field::
dp() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = _property->schema().df();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

///
int
fields::vd_field::
db() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = _property->schema().db();

  // Postconditions:

  /// @hack trap for possible error in db
  /// due to base space rep incompatibility.

  ensure(result > 0);

  //  ensure(result >= -1);

  // Exit:

  return result;
}

///
sheaf::namespace_poset*
fields::vd_field::
name_space() const
{
  return _base_space->name_space();
}

///
fields::sec_ed_invertible&
fields::vd_field::
coordinates() const
{
  // Preconditions:


  // Body:

  // Postconditions:


  // Exit:

  return *_coordinates;
}

///
fiber_bundle::sec_vd&
fields::vd_field::
property() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return *_property;
}

///
fiber_bundle::base_space_member&
fields::vd_field::
base_space() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return *_base_space;
}

///
fields::property_disc_iterator*
fields::vd_field::
new_property_disc_iterator() const
{
  property_disc_iterator* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result =
    property_disc_iterator::new_property_disc_iterator(coordinates().schema(),
        property().schema());

  // Postconditions:

  ensure(result != 0);
  ensure(result->coordinates_schema().is_same_state(&coordinates().schema()));
  ensure(result->property_schema().is_same_state(&property().schema()));

  // Exit:

  return result;
}

///
void
fields::vd_field::
property_dof_function_example(block<sec_vd_value_type>& xglobal_coords,
                              block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  require(xproperty_dofs.ct() > 0);

  // Body:

  sec_vd_value_type& lprop_dof0 = xproperty_dofs[0];

  sec_vd_value_type lfactor = 1000000.0;
  lprop_dof0 = 0.0;
  for(int i= 0; i<xglobal_coords.ct(); ++i)
  {
    lprop_dof0 += xglobal_coords[i]*lfactor;
    lfactor /= 1000.0;

  }

  for(int i=1; i<xproperty_dofs.ct(); ++i)
  {
    xproperty_dofs[i] = 0.0;
  }

  // Postconditions:

  ensure_for_all(i, 1, xproperty_dofs.ct(), xproperty_dofs[i] == 0.0);

  // Exit:

  return;
}

///
void
fields::vd_field::
put_property_dofs(property_dof_function_type xdof_fcn, bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(xdof_fcn != 0);
  require(xauto_access || state_is_read_write_accessible());

  define_old_variable(int old_access_request_depth = access_request_depth());

  // Body:

  if(xauto_access)
  {
    get_read_write_access(false, true);
  }

  put_property_dofs(*_coordinates, *_property, xdof_fcn, false);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(access_request_depth() == old_access_request_depth);

  // Exit:

  return;
}

///
void
fields::vd_field::
put_property_dofs(const sec_vd& xcoordinates,
                  sec_vd& xproperty,
                  property_dof_function_type xdof_fcn,
                  bool xauto_access)
{
  // Preconditions:

  require(xcoordinates.is_attached());
  require(xauto_access || xcoordinates.state_is_read_accessible());
  require(xproperty.is_attached());
  require(xauto_access || xproperty.state_is_read_write_accessible());
  require(xdof_fcn != 0);

  define_old_variable(int old_coordinates_access_request_depth = xcoordinates.access_request_depth());
  define_old_variable(int old_property_access_request_depth = xproperty.access_request_depth());

  // Body:

  if(xauto_access)
  {
    xcoordinates.get_read_access();
    xproperty.get_read_write_access(true);
  }

  int ldc = xcoordinates.schema().df();
  block<sec_vd_value_type> lcoords(ldc);
  lcoords.set_ct(ldc);

  int ldp = xproperty.schema().df();
  block<sec_vd_dof_type> ldofs(ldp);
  ldofs.set_ct(ldp);

  // Iterate over the property disc.

  property_disc_iterator* litr  =
    property_disc_iterator::new_property_disc_iterator(
        xcoordinates.schema(),
        xproperty.schema());

  while(!litr->is_done())
  {
    // Get the conext for all the property disc members associated
    // with the current iteration.

    litr->get_prop_disc_values(xcoordinates);

    // Iterate over all the property disc members.

    const block<discretization_context>& lprop_mbrs =
      litr->property_discretization_members();
    size_type lct = lprop_mbrs.ct();
    for(size_type i=0; i<lct; ++i)
    {
      // Get the context for this disc member.

      discretization_context& lcontext = lprop_mbrs[i];

      /// @issue Have to transfer context values array to block.
      /// because context has array and dof function wants block.

      for(size_type c=0; c<ldc; ++c)
      {
        lcoords[c] = lcontext.values[c];
      }

      // Evaluate the dof function at the coordinates

      xdof_fcn(lcoords, ldofs);

      // Scatter the dofs into the property section.

      xproperty.put_fiber(lcontext.disc_id, ldofs.base(),
			  ldofs.ct()*sizeof(sec_vd_dof_type), false);
    }

    litr->next();
  }

  delete litr;

  if(xauto_access)
  {
    xcoordinates.release_access();
    xproperty.release_access();
  }

  // Postconditions:

  ensure(xcoordinates.access_request_depth() == old_coordinates_access_request_depth);
  ensure(xproperty.access_request_depth() == old_property_access_request_depth);

  // Exit:

  return;
}

///
void
fields::vd_field::
put_property_dofs(put_property_dofs_action& xproperty_dofs_action,
                  bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(xproperty_dofs_action.property().is_same_state(&(property())));
  require(xauto_access || state_is_read_write_accessible());

  define_old_variable(int old_access_request_depth = access_request_depth());

  // Body:

  if(xauto_access)
  {
    get_read_write_access(false, true);
  }


  discretization_pusher ldisc_pusher;
  ldisc_pusher.push(property().schema(), coordinates(), xproperty_dofs_action, false);


  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(access_request_depth() == old_access_request_depth);

  // Exit:

  return;
}

///
void
fields::vd_field::
put_property_dofs(const sec_vd& xcoordinates,
                  sec_vd& xproperty,
                  put_property_dofs_action& xproperty_dofs_action,
                  bool xauto_access)
{
  // Preconditions:

  require(xcoordinates.is_attached());
  require(xauto_access || xcoordinates.state_is_read_accessible());
  require(xproperty.is_attached());
  require(xauto_access || xproperty.state_is_read_write_accessible());

  define_old_variable(int old_coordinates_access_request_depth = xcoordinates.access_request_depth());
  define_old_variable(int old_property_access_request_depth = xproperty.access_request_depth());

  // Body:

  if(xauto_access)
  {
    xcoordinates.get_read_access();
    xproperty.get_read_write_access(true);
  }

  int ldc = xcoordinates.schema().df();
  block<sec_vd_value_type> lcoords(ldc);
  lcoords.set_ct(ldc);

  int ldp = xproperty.schema().df();
  block<sec_vd_dof_type> ldofs(ldp);
  ldofs.set_ct(ldp);

  // Iterate over the property disc.

  property_disc_iterator* litr  =
    property_disc_iterator::new_property_disc_iterator(
        xcoordinates.schema(),
        xproperty.schema());

  while(!litr->is_done())
  {
    // Get the conext for all the property disc members associated
    // with the current iteration.

    litr->get_prop_disc_values(xcoordinates);

    // Iterate over all the property disc members.

    const block<discretization_context>& lprop_mbrs =
      litr->property_discretization_members();
    size_type lct = lprop_mbrs.ct();
    for(size_type i=0; i<lct; ++i)
    {
      // Get the context for this disc member.

      discretization_context& lcontext = lprop_mbrs[i];

      /// @issue Have to transfer context values array to block.
      /// because context has array and dof function wants block.

      for(size_type c=0; c<ldc; ++c)
      {
        lcoords[c] = lcontext.values[c];
      }

      // Evaluate the dof action at the coordinates

      xproperty_dofs_action(lcontext.disc_id, lcoords);
    }

    litr->next();
  }

  delete litr;


  if(xauto_access)
  {
    xcoordinates.release_access();
    xproperty.release_access();
  }

  // Postconditions:

  ensure(xcoordinates.access_request_depth() == old_coordinates_access_request_depth);
  ensure(xproperty.access_request_depth() == old_property_access_request_depth);

  // Exit:

  return;
}

///
void
fields::vd_field::
print_property_dofs(ostream& xos,
                    property_dof_function_type xdof_fcn,
                    const string& xtitle_text,
                    bool xzero_specified,
                    bool xauto_access) const
{
  // Preconditions:

  require(is_attached());
  require(xauto_access || state_is_read_accessible());

  define_old_variable(int old_access_request_depth = access_request_depth());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  xos << endl;
  for(int i=0; i<8; ++i)
  {
    xos << "==========";
  }
  xos << endl << endl;

  if(!xtitle_text.empty())
  {
    xos << xtitle_text << endl << endl;
  }

  xos << property().name() << " vs " << coordinates().name() << ":" << endl << endl;


  print_property_dofs_action ldisc_push_action(property(), xdof_fcn, xzero_specified);
  discretization_pusher ldisc_pusher;
  ldisc_pusher.push(property().schema(), coordinates(), ldisc_push_action, false);

  xos << endl;
  for(int i=0; i<8; ++i)
  {
    xos << "==========";
  }
  xos << endl << endl;

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(access_request_depth() == old_access_request_depth);

  // Exit:

  return;
}

///
bool
fields::vd_field::
same_property_fiber_schema(const vd_field& xother, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
    xother.get_read_access();
  }

  result = property().schema().fiber_schema().
            is_same_state(&xother.property().schema().fiber_schema());

  if(xauto_access)
  {
    release_access();
    xother.release_access();
  }

  // Postconditions:


  // Exit:

  return result;
}

///
bool
fields::vd_field::
same_evaluation() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  subposet& lcoord_eval_sp = coordinates().schema().evaluation();
  subposet& lprop_eval_sp  = property().schema().evaluation();

  result = lcoord_eval_sp.is_same_state(&lprop_eval_sp);

  // Postconditions:


  // Exit:

  return result;
}

///
bool
fields::vd_field::
same_discretization() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  subposet& lcoord_disc_sp = coordinates().schema().discretization();
  subposet& lprop_disc_sp  = property().schema().discretization();

  result = lcoord_disc_sp.is_same_state(&lprop_disc_sp);

  // Postconditions:


  // Exit:

  return result;
}

///
void
fields::vd_field::
property_at_coordinates(const block<sec_vd_value_type>& xcoord,
                        block<sec_vd_value_type>& xprop) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  property_at_coordinates(xcoord.base(), xcoord.ct(), xprop.base(), xprop.ub());

  xprop.set_ct(dp());

  // Postconditions:


  // Exit:

  return;
}

///
void
fields::vd_field::
property_at_coordinates(sec_vd_value_type xcoord_base[], int xcoord_ct,
                        sec_vd_value_type xprop_base[], int xprop_ub) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Find the point in the source base space
  // with global coordinates xcoord.

  chart_point_3d lpt;

  coordinates().point_at_value_ua(xcoord_base, xcoord_ct, lpt);

  if(lpt.is_valid())
  {
    // Found a valid point; evaluate the property

    property().value_at_point_ua(lpt, xprop_base, xprop_ub, false);
  }
  else
  {
    // Property isn't defined at given coordinate;
    // extend by zero.

    for(int i=0; i<dp(); i++)
    {
      xprop_base[i] = 0.0;
    }
  }

  // Postconditions:


  // Exit:

  return;
}

///
sheaf::subposet*
fields::vd_field::
embed_property(const string& xresult_name,
               name_map<int>& xresult_member_names,
               bool xauto_access)
{
  subposet* result;

  // Preconditions:

  require(xauto_access || state_is_read_write_accessible(true));

  if(xauto_access)
  {
    get_read_write_access(true, true);
  }

  require(!base_space().host()->includes_subposet(xresult_name, false));
  require(property().schema().rep().name() == "element_element_constant");
  require(property().schema().evaluation().has_id_space());
  require(unexecutable("Lower cover of property() base space contains only zones."));
  require(unexecutable("property value positive"));

  // Body:

  total_poset_member&  lbase = property().schema().base_space();
  scoped_index lbase_id = lbase.index();
  poset_state_handle* lbase_host = property().schema().base_space().host();

  // Create the decomposition subposet.

  result = new subposet(lbase_host);
  result->put_name(xresult_name, true, false); // New_id_space requires name.

  result->new_id_space("hash_index_map");
  mutable_index_space_handle& lresult_space = result->id_space();

  client_index lresult_mbr_client_id(property().schema().discretization_id_space().id_space());
  scoped_index lresult_mbr_id = lbase_host->member_id(false);

  // Get the client id map for the evaluation subposet,
  // which the precondition requires to be the zones subposet.

  subposet& leval_sp = property().schema().evaluation();
  mutable_index_space_handle& leval_space = leval_sp.id_space();

  // Assume that all zones and only zones are in the lower cover of the base space.
  // Iterate over the lower cover.

  scoped_index lfirst = lbase_host->first_cover_member(LOWER, lbase_id);

  sec_vd::fiber_type::volatile_type* lprop_fiber =
    _property->fiber_prototype().lite_prototype().clone();

  while(leval_sp.contains_member(lbase_host->first_cover_member(LOWER, lbase_id)))
  {
    scoped_index lzone_id = lbase_host->first_cover_member(LOWER, lbase_id);

    // Get the property value for this zone;

    _property->get_fiber(lzone_id, *lprop_fiber, false);

    // Convert to a client id for the decomposition;

    lresult_mbr_client_id =
      static_cast<pod_index_type>((*lprop_fiber)[0] + 0.5);

    // Get the poset id of the decomposition member.

    lresult_mbr_id = lresult_space.hub_pod(lresult_mbr_client_id);

    if(!lresult_mbr_id.is_valid())
    {
      // Decomposition member for this property value
      // does not exist yet; create it.

      lresult_mbr_id = lbase_host->new_member(false);

      // Give it a name, if the client has provided one.

      string lresult_mbr_name = xresult_member_names.name(lresult_mbr_client_id.pod());
      if(!lresult_mbr_name.empty())
      {
        lbase_host->put_member_name(lresult_mbr_id, lresult_mbr_name, true, false);
      }

      // Insert it in result.

      result->insert_member(lresult_mbr_id);
      lresult_space.insert(lresult_mbr_client_id, lresult_mbr_id);

      // Link the base space to the decomposition member.
      // This inserts lresult_id at the back of llc.

      lbase_host->new_link(lbase_id, lresult_mbr_id);
    }

    // Link the decomposition member to the zone.

    lbase_host->new_link(lresult_mbr_id, lzone_id);

    // Delete the link from the base space to the zone.
    // Since lzone_id is at the front of llc, this
    // advances the iteration to the next member.
    // Eventually we reach the decomp members at the
    // back of llc and the iteration terminates.

    lbase_host->delete_link(lbase_id, lzone_id);
  }

  delete lprop_fiber;

  // Postconditions:

  ensure(result != 0);
  ensure(result->name() == xresult_name);
  ensure(base_space().host()->includes_subposet(xresult_name, false));

  if(xauto_access)
  {
    release_access();
  }

  // Exit:

  return result;
}

///
void
fields::vd_field::
delete_field_spaces(vd_field* xfield,
                    bool xdelete_coord_fiber,
                    bool xdelete_prop_fiber)
{
  // Preconditions:


  // Body:

  namespace_poset* lns = xfield->name_space();
  lns->begin_jim_edit_mode(true);

  // The prereq_id dofs define the outgoing adjacency links of the
  // member dependency graph. Build the incoming adjacency links.
  // The member id space is used to access the links.

  block< set<pod_index_type> > lin_links(lns->member_index_ub().pod());

  namespace_poset_member lmbr(lns->top());

  index_iterator lmbr_itr = lns->member_iterator();
  while(!lmbr_itr.is_done())
  {
    lmbr.attach_to_state(lmbr_itr.index());

    if(lmbr.is_jim(false))
    {
      for(int i=0; i<sheaf::PREREQ_IDS_UB; ++i)
      {
        scoped_index lprereq_id = lmbr.poset_prereq_id(i);

        if(lprereq_id.is_valid())
        {
          lin_links[lprereq_id.hub_pod()].insert(lmbr.index().hub_pod());
        }
      }
    }

    lmbr_itr.next();
  }
  lmbr.detach_from_state();

  scoped_index lhost_index;

  // Get the property and coordinate hosts, then delete the field.

  xfield->get_read_access();

  lhost_index = xfield->property().host()->index();
  poset_state_handle* lprop_host = lns->member_poset(lhost_index, false);

  lhost_index = xfield->coordinates().host()->index();
  poset_state_handle* lcoord_host = lns->member_poset(lhost_index, false);

  lhost_index = xfield->base_space().host()->index();
  poset_state_handle* lbase_space_host = lns->member_poset(lhost_index, false);

  xfield->release_access();

  delete xfield;

  // Get the property schema host, remove the in link from the property
  // host to the property schema host, then delete the property host.

  lprop_host->get_read_write_access(true);

  lhost_index = lprop_host->schema().host()->index();
  section_space_schema_poset* lprop_schema_host =
    dynamic_cast<section_space_schema_poset*>(lns->member_poset(lhost_index, false));

  lin_links[lprop_schema_host->index().hub_pod()].erase(lprop_host->index().hub_pod());

  lprop_host->delete_state(false);

  if(lin_links[lprop_schema_host->index().hub_pod()].empty())
  {
    // The prop schema host is no longer being used.
    // Get the fiber space, remove the proerty schema host
    // from the in links of the fiber space,
    // then delete the property schema host.

    lprop_schema_host->get_read_write_access(true);
    lhost_index = lprop_schema_host->fiber_space().index();
    poset_state_handle* lprop_fiber_space = lns->member_poset(lhost_index, false);

    lin_links[lprop_fiber_space->index().hub_pod()].erase(lprop_schema_host->index().hub_pod());

    lin_links[lbase_space_host->index().hub_pod()].erase(lprop_schema_host->index().hub_pod());

    lprop_schema_host->delete_state(false);

    if(lin_links[lprop_fiber_space->index().hub_pod()].empty() && xdelete_prop_fiber)
    {
      // The prop fiber space is no longer being used; delete it..

      lprop_fiber_space->get_read_write_access(true);
      lprop_fiber_space->delete_state(false);
    }
  }

  // Get the coord schema host, then delete the coord host.

  lcoord_host->get_read_write_access(true);

  lhost_index = lcoord_host->schema().host()->index();
  section_space_schema_poset* lcoord_schema_host =
    dynamic_cast<section_space_schema_poset*>(lns->member_poset(lhost_index, false));

  lin_links[lcoord_schema_host->index().hub_pod()].erase(lcoord_host->index().hub_pod());

  lcoord_host->delete_state(false);

  if(lin_links[lcoord_schema_host->index().hub_pod()].empty())
  {
    // The coord schema host is no longer being used,
    // delete it, but first get the fiber space.

    lcoord_schema_host->get_read_write_access(true);
    lhost_index = lcoord_schema_host->fiber_space().index();
    poset_state_handle* lcoord_fiber_space = lns->member_poset(lhost_index, false);

    lin_links[lcoord_fiber_space->index().hub_pod()].erase(lcoord_schema_host->index().hub_pod());

    lin_links[lbase_space_host->index().hub_pod()].erase(lcoord_schema_host->index().hub_pod());

    lcoord_schema_host->delete_state(false);

    if(lin_links[lcoord_fiber_space->index().hub_pod()].empty() && xdelete_coord_fiber)
    {
      // The coord fiber space is no longer being used; delete it..

      lcoord_fiber_space->get_read_write_access(true);
      lcoord_fiber_space->delete_state(false);
    }
  }

  if(lin_links[lbase_space_host->index().hub_pod()].empty())
  {
    // The base space is no longer being used; delete it.

    lbase_space_host->get_read_write_access(true);
    lbase_space_host->delete_state(false);
  }

  // The fiber space group in the namespace may now be empty.
  // If so, it must be deleted because it is incorrectly connected to top.

  scoped_index lfiber_spaces_id = lns->member_id("fiber_spaces", false);

  if(lfiber_spaces_id.is_valid() &&
      lns->cover_is_empty(LOWER, lfiber_spaces_id))
  {
    lns->delete_link(TOP_INDEX, lfiber_spaces_id);

    lns->delete_member(lfiber_spaces_id);
  }

  // The section space group in the namespace may now be empty.
  // If so, it must be deleted because it is incorrectly connected to top.

  scoped_index lsection_spaces_id = lns->member_id("section_spaces", false);

  if(lsection_spaces_id.is_valid() &&
      lns->cover_is_empty(LOWER, lsection_spaces_id))
  {
    lns->delete_link(TOP_INDEX, lsection_spaces_id);

    lns->delete_member(lsection_spaces_id);
  }


  lns->end_jim_edit_mode(true, true);


  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// READ_WRITE_MONITOR_HANDLE FACET
// ===========================================================

///
bool
fields::vd_field::
is_attached() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_coordinates->is_attached() && _property->is_attached());

  // Postconditions:

  ensure(result == (coordinates().is_attached() && property().is_attached()));

  // Exit:

  return result;
}

///
bool
fields::vd_field::
state_is_read_only_accessible() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (state_is_read_accessible() && state_is_not_read_write_accessible());

  // Postconditions:

  ensure(result == (state_is_read_accessible() && state_is_not_read_write_accessible()));

  // Exit:

  return result;
}

///
bool
fields::vd_field::
state_is_read_accessible() const
{
  bool result;

  // Preconditions:

  // Body:

  result =
    (_coordinates->state_is_read_accessible() &&
     _property->state_is_read_accessible());

  // Postconditions:

  ensure(result ==
         (coordinates().state_is_read_accessible() &&
          property().state_is_read_accessible()));

  // Exit:

  return result;
}


///
bool
fields::vd_field::
state_is_read_write_accessible(bool xbase_access) const
{
  bool result;

  // Preconditions:


  // Body:

  result =
    (_coordinates->state_is_read_write_accessible() &&
     _property->state_is_read_write_accessible() &&
     (xbase_access ? _base_space->state_is_read_write_accessible() : true));

  // Postconditions:

  ensure(result ==
         (coordinates().state_is_read_write_accessible() &&
          property().state_is_read_write_accessible() &&
          (xbase_access ? _base_space->state_is_read_write_accessible() : true)));

  // Exit:

  return result;
}

///
int
fields::vd_field::
access_request_depth() const
{
  int result;

  // Preconditions:

  require(is_attached());

  // Body:

  int lprop_depth = _property->access_request_depth();
  int lcoord_depth = _coordinates->access_request_depth();

  result = lcoord_depth < lprop_depth ? lcoord_depth : lprop_depth;

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

///
void
fields::vd_field::
get_read_access() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  define_old_variable(int old_access_request_depth = access_request_depth());

  // Even though section access gets base space access,
  // must get base space access directly to keep requested depth
  // the same as when requesting write access, so release is
  // the same for both.

  _base_space->get_read_access();

  _coordinates->get_read_access();
  _property->get_read_access();


  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);

  // Exit:

  return;
}

///
void
fields::vd_field::
get_read_write_access(bool xbase_access, bool xrelease_read_only_access)
{
  // Preconditions:

  require(is_attached());
  require(xrelease_read_only_access || state_is_not_read_only_accessible());
  require(xrelease_read_only_access || base_space().state_is_not_read_only_accessible());

  // Body:

  define_old_variable(int old_access_request_depth = access_request_depth());

  if(xbase_access)
  {
    _base_space->get_read_write_access(xrelease_read_only_access);
  }
  else
  {
    // Even if base write access not requested,
    // get read access just so request depth is the
    // same either way.

    _base_space->get_read_access();
  }

  _coordinates->get_read_write_access(xrelease_read_only_access);
  _property->get_read_write_access(xrelease_read_only_access);

  // Since section get access also gets access to base,
  // base request depth is now at least 2 greater than sections.

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);

  // Exit:

  return;
}

///
void
fields::vd_field::
release_access(bool xall) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  define_old_variable(int old_access_request_depth = access_request_depth());

  _coordinates->release_access(xall);
  _property->release_access(xall);

  // Sections have released the base access they acquired,
  // but still need to release the directly acquired access.

  _base_space->release_access(xall);

  // Postconditions:

  ensure(xall ? access_request_depth() == 0 :
         access_request_depth() == old_access_request_depth - 1);
  ensure((access_request_depth() > 0) == state_is_read_accessible());

  // Exit:

  return;
}

///
bool
fields::vd_field::
state_is_modified() const
{
  bool result;

  // Preconditions:

  require(is_attached());

  // Body:

  result = (_coordinates->state_is_modified() || _property->state_is_modified());

  // Postconditions:

  ensure(result == (coordinates().state_is_modified() ||
                    property().state_is_modified()));

  // Exit:

  return result;
}

///
void
fields::vd_field::
clear_state_is_modified()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _coordinates->clear_state_is_modified();
  _property->clear_state_is_modified();


  // Postconditions:

  ensure(!state_is_modified());

  // Exit:

  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

///
bool
fields::vd_field::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const vd_field*>(xother) != 0;

  // Postconditions:

  return result;
}

///
fields::vd_field*
fields::vd_field::
clone() const
{
  vd_field* result;

  // Preconditions:

  // Body:

  result = new vd_field();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
fields::vd_field&
fields::vd_field::
operator=(const vd_field& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
fields::vd_field::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    invariance(state_is_read_accessible() ?
               base_space().is_same_state(&property().schema().base_space()) :
               true);

    invariance(state_is_read_accessible() ?
               property().schema().base_space().le(&coordinates().schema().base_space()) :
               true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

///
void
fields::
push_to(const vd_field& xsrc, vd_field& xdst, bool xauto_access)
{
  // Preconditions:

  require(xsrc.is_attached());
  require(xdst.is_attached());
  require(xauto_access || xsrc.state_is_read_accessible());
  require(xauto_access || xdst.state_is_read_write_accessible(false));
  require(xsrc.same_property_fiber_schema(xdst, xauto_access));

  // Body:

  if(xauto_access)
  {
    xsrc.get_read_access();
    xdst.get_read_write_access(false, true);
  }

  section_pusher sp(xsrc, xdst, false);
  sp.push_pa(xsrc.property(), xdst.property(), false);

  if(xauto_access)
  {
    xsrc.release_access();
    xdst.release_access();
  }

  // Postconditions:


  // Exit:

  return;
}

///
fields::vd_field&
fields::
operator>>(const vd_field& xsrc, vd_field& xdst)
{
  // Preconditions:

  require(precondition_of(push_to(xsrc, xdst, true))); 

  // Body:

  push_to(xsrc, xdst, true);

  // Postconditions:

  ensure(postcondition_of(push_to(xsrc, xdst, true))); 

  //Exit:

  return xdst;
}

///
ostream&
fields::
operator<<(ostream& xos, const vd_field& xfield)
{
  // Preconditions:

  require(xfield.state_is_read_accessible());

  // Body:

  xfield.print_property_dofs(xos, 0, "", false, false);

  // Postconditions:


  // Exit:

  return xos;
}

//==============================================================================
//==============================================================================

///
void
fields::
add(const vd_field& x0, const vd_field& x1, vd_field& xresult,
    bool xauto_access)
{
  // Preconditions:

  require(precondition_of(add(x0.property(), x1.property(), \
                          xresult.property(), xauto_access)));

  // Body:

  add(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(add(x0.property(), x1.property(), \
                              xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::
add_equal(vd_field& xresult, const vd_field& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(add(xresult, xother, xresult, xauto_access)));

   // Body:

  add(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(add(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::
subtract(const vd_field& x0, const vd_field& x1, vd_field& xresult,
         bool xauto_access)
{
  // Preconditions:

  require(precondition_of(subtract(x0.property(), x1.property(), \
                                   xresult.property(), xauto_access)));

  // Body:

  subtract(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(subtract(x0.property(), x1.property(), \
                                   xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::
subtract_equal(vd_field& xresult, const vd_field& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(subtract(xresult, xother, xresult, xauto_access)));

   // Body:

  subtract(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(subtract(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::
multiply(const vd_field& x0, const sec_at0& x1, vd_field& xresult,
         bool xauto_access)
{
  // Preconditions:

  require(precondition_of(multiply(x0.property(), x1, \
                          xresult.property(), xauto_access)));

  // Body:

  multiply(x0.property(), x1, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(multiply(x0.property(), x1, \
                          xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::
multiply_equal(vd_field& xresult, const sec_at0& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Body:

  multiply(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::
multiply(const vd_field& x0, const vd_value_type& x1, vd_field& xresult,
         bool xauto_access)
{
  // Preconditions:

  require(precondition_of(multiply(x0.property(), x1, \
                                   xresult.property(), xauto_access)));

  // Body:

  multiply(x0.property(), x1, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(multiply(x0.property(), x1, \
                                   xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::
multiply_equal(vd_field& xresult, const vd_value_type& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Body:

  multiply(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

void
fields::
divide(const vd_field& x0, const sec_at0& x1, vd_field& xresult,
       bool xauto_access)
{
  // Preconditions:

  require(precondition_of(divide(x0.property(), x1, \
                          xresult.property(), xauto_access)));

  // Body:

  divide(x0.property(), x1, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(divide(x0.property(), x1, \
                          xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::
divide_equal(vd_field& xresult, const sec_at0& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Body:

  divide(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::
divide(const vd_field& x0, const vd_value_type& x1, vd_field& xresult,
       bool xauto_access)
{
  // Preconditions:

  require(precondition_of(divide(x0.property(), x1, \
                                 xresult.property(), xauto_access)));

  // Body:

  divide(x0.property(), x1, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(divide(x0.property(), x1, \
                                 xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::
divide_equal(vd_field& xresult, const vd_value_type& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Body:

  divide(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::
contract(const vd_field& xvector, const vd_field& xcovector,
         sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(contract(xvector.property(), xcovector.property(), \
                                  xresult, xauto_access)));

  // Body:

  contract(xvector.property(), xcovector.property(), xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(contract(xvector.property(), xcovector.property(), \
                                  xresult, xauto_access)));

  // Exit:

  return;
}
