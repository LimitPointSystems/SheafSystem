
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

/// @file
/// Implementation for class schema_poset_member.

#include "ComLimitPoint/sheaf/schema_poset_member.h"

#include "ComLimitPoint/sheaf/array_index_space_handle.h"
#include "ComLimitPoint/sheaf/array_index_space_state.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "ComLimitPoint/sheaf/poset_bounds.h"
#include "ComLimitPoint/sheaf/poset_dof_iterator.h"
#include "ComLimitPoint/sheaf/postorder_iterator.h"
#include "ComLimitPoint/sheaf/schema_descriptor.h"
#include "ComLimitPoint/sheaf/index_space_iterator.h"
#include "ComLimitPoint/sheaf/tern.h"
#include "ComLimitPoint/sheaf/wsv_block.h"

using namespace std;

//#define DIAGNOSTIC_OUTPUT

// ===========================================================
// SCHEMA_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
sheaf::schema_poset_member::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(namespace_poset::primitives_schema_path());

  // Postconditions:

  ensure(result.full());

  // Exit:

  return result;
}

sheaf::schema_poset_member::host_type&
sheaf::schema_poset_member::
new_host(namespace_type& xns, const poset_path& xhost_path, const poset_path& xschema_path, bool xauto_access)
{
  // cout << endl << "Entering schema_poset_member::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_poset(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xauto_access);
  result.get_read_write_access();  
  
  // Create the schema subposets of the top.

  subposet ltable_dofs(&result, 0, false);
  subposet lrow_dofs(&result, 0, false);

  // Schematize the result.

  result.schematize(&ltable_dofs, &lrow_dofs, true);

  // Clean up.

  ltable_dofs.detach_from_state();
  lrow_dofs.detach_from_state();
  
  result.release_access();

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true).poset_name() == xhost_path.poset_name());
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.is_schematized(true));

  // Exit:

  // cout << "Leaving schema_poset_member::new_host." << endl;
  return result;
}

sheaf::schema_poset_member::host_type&
sheaf::schema_poset_member::
standard_host(namespace_type& xns, const poset_path& xhost_path, bool xauto_access)
{
  // cout << endl << "Entering schema_poset_member::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(xns.path_is_available<host_type>(xhost_path, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));

  // Body:

  host_type* result_ptr;
  if(xns.contains_path(xhost_path, xauto_access))
  {
    result_ptr = &xns.member_poset<host_type>(xhost_path, xauto_access);
  }
  else
  {
    result_ptr = &new_host(xns, xhost_path, standard_schema_path(), xauto_access);
  }

  host_type& result = *result_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true).poset_name() == xhost_path.poset_name());
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.is_schematized(true));

  // Exit:

  // cout << "Leaving schema_poset_member::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// ABSTRACT_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::schema_poset_member::
schema_poset_member()
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

sheaf::schema_poset_member::
schema_poset_member(const abstract_poset_member& xother,
                    bool xnew_jem,
                    bool xauto_access)
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{

  // Preconditions:

  require(xnew_jem ? xother.state_is_auto_read_write_accessible(xauto_access) : true);

  //   new_Jem auto_Access requires
  //     f  f  read access
  //     f  t
  //     t  f  read_write_access
  //     t  t  is_attached()

  // Body:

  if(xnew_jem)
  {
    new_jem_state(const_cast<abstract_poset_member*>(&xother), true, xauto_access);
  }
  else
  {
    attach_to_state(&xother);
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

sheaf::schema_poset_member&
sheaf::schema_poset_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

sheaf::schema_poset_member&
sheaf::schema_poset_member::
operator=(const schema_poset_member& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  //Body:

  not_implemented();

  //Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

sheaf::schema_poset_member::
~schema_poset_member()
{
  // Preconditions:

  // Body:

  if(_table_dof_descriptors != 0)
  {
    _table_dof_descriptors->remove_reference();
  }

  if(_row_dof_descriptors != 0)
  {
    _row_dof_descriptors->remove_reference();
  }

  // Postconditions:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

sheaf::schema_poset_member::
schema_poset_member(poset_state_handle* xhost,
                    primitive_type xprimitive_type,
                    bool xauto_access)
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{

  // Preconditions:

  require(precondition_of(schema_poset_member::new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xprimitive_type, xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(schema_poset_member::new_jim_state(same args)));

  // Exit

  return;
}

sheaf::schema_poset_member::
schema_poset_member(poset_state_handle* xhost,
                    primitives_poset_dof_map* xdof_map,
                    bool xcopy_dof_map,
                    bool xauto_access)
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{

  // Preconditions:

  require(precondition_of(schema_poset_member::new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_map, xcopy_dof_map, xauto_access);

  // Postconditions:

  ensure(postcondition_of(schema_poset_member::new_jim_state(same args)));
}

sheaf::schema_poset_member::
schema_poset_member(poset_state_handle* xhost,
                    const scoped_index* xexpansion,
                    int xexpansion_ct,
                    const tern& xnew_jem,
                    bool xauto_access)
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{

  // Preconditions:

  require(precondition_of(schema_poset_member::new_jrm_state(same args)));

  // Body:

  new_jrm_state(xhost, xexpansion, xexpansion_ct, xnew_jem, xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(schema_poset_member::new_jrm_state(same args)));
}

sheaf::schema_poset_member::
schema_poset_member(const namespace_poset& xns,
                    const std::string& xname,
                    const poset_path& xparent_path,
                    const wsv_block<schema_descriptor>& xdof_specs,
                    bool xauto_access)
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{

  // Preconditions:

  require(precondition_of(new_jrm_state(same args)));

  // Body:

  new_jim_state(xns, xname, xparent_path, xdof_specs, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jrm_state(same args)));

}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

sheaf::schema_poset_member::
schema_poset_member(poset_state_handle* xhost, pod_index_type xhub_id)
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{

  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

sheaf::schema_poset_member::
schema_poset_member(poset_state_handle* xhost, const scoped_index& xid)
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{

  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

sheaf::schema_poset_member::
schema_poset_member(const poset_state_handle* xhost, const std::string& xname)
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());
  require(xhost->contains_member(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());
}

sheaf::schema_poset_member::
schema_poset_member(const namespace_poset* xnamespace,
                    const poset_path& xpath,
                    bool xauto_access)
  : _table_dof_descriptors(0),
    _row_dof_descriptors(0),
    _table_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _row_cache_version(NOT_A_STANDARD_VERSION_INDEX),
    _table_dof_id_space(0),
    _row_dof_id_space(0)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

// EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

void
sheaf::schema_poset_member::
new_jim_state(primitive_type xprimitive_type, bool xauto_access)
{
  // Preconditions:

  require(!xauto_access ? host()->in_jim_edit_mode() : true);

  // If xauto_access == true we must get read access to the schema before
  // testing to the host's schema.

  if(xauto_access)
    host()->begin_jim_edit_mode();

  require(host()->schema().conforms_to("primitives_schema/top"));

  // Body:

  // Create new jim with a primitive dof map of the proper type.

  poset_dof_map* ldof_map = new primitives_poset_dof_map(_host, xprimitive_type);

  pod_index_type lindex = _host->new_member(true, ldof_map, false);

  // Attach_to_state(xindex) attaches but does not reinitialize handle data members.

  attach_to_state(lindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!is_restricted());
  ensure(type() == xprimitive_type);

  // Clean-up auto access.

  if(xauto_access)
    host()->end_jim_edit_mode();

  // Exit:

  return;
}

void
sheaf::schema_poset_member::
new_jim_state(poset_state_handle* xhost,
              primitive_type xprimitive_type,
              bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(!xauto_access ? xhost->in_jim_edit_mode() : true);

  // If xauto_access == true we must get read access to the schema before
  // testing to the host and dof_map.

  if(xauto_access)
    xhost->begin_jim_edit_mode();

  require(xhost->schema().conforms_to("primitives_schema/top"));

  // Body:

  // Create new jim with a primitive dof map of the proper type.

  poset_dof_map* ldof_map = new primitives_poset_dof_map(xhost, xprimitive_type);

  pod_index_type lindex = xhost->new_member(true, ldof_map, false);

  // Attach_to_state(xindex) attaches but does not reinitialize handle data members.

  attach_to_state(xhost, lindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!is_restricted());
  ensure(type() == xprimitive_type);

  // Clean-up auto access.

  if(xauto_access)
    xhost->end_jim_edit_mode();

  // Exit:

  return;
}

void
sheaf::schema_poset_member::
new_jim_state(const namespace_poset& xns,
              const std::string& xname,
              const poset_path& xparent_path,
              const wsv_block<schema_descriptor>& xdof_specs,
              bool xauto_access)
{
  // Preconditions:

  require(xauto_access || xns.state_is_read_accessible());

  if(xauto_access)
  {
    xns.get_read_access();
  }

  require(!xname.empty());
  require(!xparent_path.poset_name().empty());
  require(!xns.contains_poset_member(xparent_path.poset_name()+"/"+xname));

  require(xns.contains_poset(xparent_path));
  require(xauto_access ||
          xns.member_poset(xparent_path).state_is_read_write_accessible());

  if(xauto_access)
  {
    xns.member_poset(xparent_path).get_read_write_access();
  }

  require(xns.member_poset(xparent_path).is_schematized(false));
  require(xns.contains_poset_member(xparent_path));
  require_for_all(i, 0, xdof_specs.ct(), !xdof_specs[i].name.empty());

  // Body:

  // Get handles for the schema poset and the dof subposets.

  poset_state_handle& lschema_poset = xns.member_poset(xparent_path);
  subposet ltable_dof_sp(&lschema_poset, table_dof_subposet_name("top"));
  subposet lrow_dof_sp(&lschema_poset, row_dof_subposet_name("top"));

  // Make sure the dof subposets have an id space that is opened for editing.

  if(!ltable_dof_sp.has_id_space())
  {
    ltable_dof_sp.new_id_space("array_index_space_state");
  }

  if(!lrow_dof_sp.has_id_space())
  {
    lrow_dof_sp.new_id_space("array_index_space_state");
  }

  // Create the result.

  lschema_poset.begin_jim_edit_mode();

  /// @hack have to create dof map with some primitive type.
  /// @todo define a "primitive" type for this purpose.

  poset_dof_map* ldof_map =
    new primitives_poset_dof_map(&lschema_poset, SIZE_TYPE);
  new_jim_state(&lschema_poset, ldof_map, false, false);
  size_t lsize = 0;
  int ldof_ct = xdof_specs.ct();

  // Cover the the parent.

  schema_poset_member lschema_mbr;
  lschema_mbr.attach_to_state(&lschema_poset, xparent_path.member_name());

  if(lschema_poset.top().covers(&lschema_mbr))
  {
    // The parent is already covered by top; delete the link.

    lschema_poset.top().delete_cover_link(&lschema_mbr);
  }

  // Cover the parent if it is not the bottom or if
  // it is the bottom and there's nothing else to cover.

  if((lschema_mbr.index() != BOTTOM_INDEX) || (ldof_ct == 0))
  {
    create_cover_link(&lschema_mbr);
  }

  // Cover each dof.

  for(int i=0; i<ldof_ct; ++i)
  {
    const string& ldof_name = xdof_specs[i].name;
    if(lschema_poset.contains_member(ldof_name))
    {
      // The dof already exists, just attach to it.

      lschema_mbr.attach_to_state(ldof_name);
    }
    else
    {
      // Create the dof.

      lschema_mbr.new_jim_state(xdof_specs[i].type, false);
      lschema_mbr.put_name(ldof_name, true, false);

      // Insert it in the appropriate dof subposet and give
      // it a creation-order sequence id.

      subposet& ldof_sp = xdof_specs[i].is_table_dof ? ltable_dof_sp : lrow_dof_sp;
      ldof_sp.insert_member(lschema_mbr.index());
      ldof_sp.id_space().push_back(lschema_mbr.index());
    }

    // Cover it.

    create_cover_link(&lschema_mbr);
  }

  lschema_poset.end_jim_edit_mode();

  put_name(xname, true, false);

  // This member is a jim, but it is not a primitive type.
  // Size and alignment will be set in update_cache().

  dof_map(true).put_type(NOT_A_PRIMITIVE_TYPE);

  // Clean up.

  lschema_mbr.detach_from_state();
  lrow_dof_sp.detach_from_state();
  ltable_dof_sp.detach_from_state();

  // Postconditions:

  ensure(name() == xname);
  ensure(host()->name() == (xparent_path.poset_name()));

  if(xauto_access)
  {
    lschema_poset.release_access();
    xns.release_access();
  }

  // Exit:

  return;
}

int
sheaf::schema_poset_member::
dof_ct(const namespace_poset& xns,
       const poset_path& xpath,
       bool xis_table_dof,
       bool xauto_access)
{
  int result;

  // Preconditions:

  require(!xauto_access ? xns.state_is_read_accessible() : true);

  if(xauto_access)
  {
    xns.get_read_access();
  }

  require(xpath.full());
  require(!xauto_access ?
          xns.member_poset(xpath).state_is_read_accessible() :
          true);

  // Body:

  poset_state_handle& lschema_poset = xns.member_poset(xpath);

  if(xauto_access)
  {
    lschema_poset.get_read_access();
  }

  schema_poset_member lschema_mbr(&lschema_poset, xpath.member_name());

  result = lschema_mbr.dof_ct(xis_table_dof);

  lschema_mbr.detach_from_state();

  if(xauto_access)
  {
    lschema_poset.release_access();
    xns.release_access();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}


int
sheaf::schema_poset_member::
table_dof_ct(const namespace_poset& xns,
             const poset_path& xpath,
             bool xauto_access)
{
  int result;

  // Preconditions:

  require(precondition_of(dof_ct(xns, xpath, true, xauto_access)));

  // Body:

  result = dof_ct(xns, xpath, true, xauto_access);


  // Postconditions:

  ensure(postcondition_of(dof_ct(xns, xpath, true, xauto_access)));

  // Exit

  return result;
}

int
sheaf::schema_poset_member::
row_dof_ct(const namespace_poset& xns,
           const poset_path& xpath,
           bool xauto_access)
{
  int result;

  // Preconditions:

  require(precondition_of(dof_ct(xns, xpath, false, xauto_access)));

  // Body:

  result = dof_ct(xns, xpath, false, xauto_access);


  // Postconditions:

  ensure(postcondition_of(dof_ct(xns, xpath, false, xauto_access)));

  // Exit

  return result;
}

int
sheaf::schema_poset_member::
dof_ct(bool xis_table_dof) const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = xis_table_dof ? table_dof_ct() : row_dof_ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
sheaf::schema_poset_member::
table_dof_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!table_cache_consistent())
  {
    update_table_cache();
  }

  result = _table_dof_ct;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

int
sheaf::schema_poset_member::
row_dof_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  result = _row_dof_ct;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

size_t
sheaf::schema_poset_member::
dof_tuple_ub(bool xis_table_dof) const
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = xis_table_dof ? table_dof_tuple_ub() : row_dof_tuple_ub();

  // Postconditions:

  // Exit

  return result;
}

size_t
sheaf::schema_poset_member::
table_dof_tuple_ub() const
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!table_cache_consistent())
  {
    update_table_cache();
  }

  result = _table_dof_tuple_ub;

  // Postconditions:

  // Exit

  return result;
}

size_t
sheaf::schema_poset_member::
row_dof_tuple_ub() const
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  result = _row_dof_tuple_ub;

  // Postconditions:

  // Exit

  return result;
}

sheaf::primitive_type
sheaf::schema_poset_member::
dof_tuple_type(bool xis_table_dof) const
{
  primitive_type result = NOT_A_PRIMITIVE_TYPE;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  poset_dof_iterator* itr = dof_iterator(xis_table_dof);
  if(!itr->is_done())
  {
    result = itr->item().type();
    itr->next();
  }

  while(!itr->is_done() && (result != NOT_A_PRIMITIVE_TYPE))
  {
    if(result != itr->item().type())
    {
      result = NOT_A_PRIMITIVE_TYPE;
    }
    itr->next();
  }

  itr->force_is_done();
  delete itr;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
dof_tuple_is_homogeneous(bool xis_table_dof) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = is_primitive_index(dof_tuple_type(xis_table_dof));

  // Postconditions:

  ensure(result == is_primitive_index(dof_tuple_type(xis_table_dof)));

  // Exit

  return result;
}

std::string
sheaf::schema_poset_member::
dof_subposet_name(const std::string& xname, bool xis_table_dofs)
{
  string result;

  // Preconditions:

  require(!xname.empty());

  // Body:

  result =
    poset_path::reserved_prefix() +
    xname +
    (xis_table_dofs ? "_table_dofs" : "_row_dofs");

  // Postconditions:

  ensure(!result.empty());

  // Exit

  return result;
}

std::string
sheaf::schema_poset_member::
dof_subposet_name(bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  string result(dof_subposet_name(name(), xis_table_dofs));

  // Postconditions:

  ensure(!result.empty());

  // Exit

  return result;
}

const sheaf::scoped_index&
sheaf::schema_poset_member::
table_dof_subposet_index() const
{
  // Preconditions:

  /// @issue this precondition is only needed for the postcondition.

  require(state_is_read_accessible());

  // Body:

  const scoped_index& result = _table_dof_subposet_index;

  // Postconditions:

  ensure(result.is_valid() == host()->includes_subposet(result));

  // Exit

  return result;
}

const sheaf::scoped_index&
sheaf::schema_poset_member::
row_dof_subposet_index() const
{
  // Preconditions:

  /// @issue this precondition is only needed for the postcondition.

  require(state_is_read_accessible());

  // Body:

  const scoped_index& result = _row_dof_subposet_index;

  // Postconditions:

  ensure(result.is_valid() == host()->includes_subposet(result));

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
contains_dof(const schema_poset_member& xother, bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(xother.state_is_read_accessible());
  require(host()->is_schematized(false));


  // Body:

  result = xother.le(this) && xother.is_dof(xin_table_dofs);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
contains_dof(pod_index_type xother_id, bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));

  // Body:

  // A direct implemetation might be faster,
  // but this implementation doesn't need to be
  // redefined in section_space_schema_member
  // and descendants.

  schema_poset_member* lother = clone();
  lother->attach_to_state(host(), xother_id);

  result = contains_dof(*lother, xin_table_dofs);

  lother->detach_from_state();
  delete lother;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
contains_dof(const scoped_index& xother_id, bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));


  // Body:

  return contains_dof(xother_id.hub_pod(), xin_table_dofs);
}

bool
sheaf::schema_poset_member::
contains_dof(const std::string& xname, bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));
  require(!xname.empty());


  // Body:

  pod_index_type lhub_pod = host()->member_id(xname, false);
  

  return is_valid(lhub_pod) && contains_dof(lhub_pod, xin_table_dofs);
}

bool
sheaf::schema_poset_member::
is_dof(bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));


  // Body:

  // Category is defined by membership in table or row dof subposets of top,
  // which include dof subposets of all other members.

  subposet ltop_dofs(host(), schema_poset_member::dof_subposet_name("top", xin_table_dofs));
  result = ltop_dofs.contains_member(index());
  ltop_dofs.detach_from_state();

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
is_component() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));

  // Body:

  // A component of a schema is a row dof which is atomic.

  result = is_row_dof() && is_atom();

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
is_component_of(const schema_poset_member& xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));
  require(is_ancestor_of(&xother));
  require(xother.state_is_read_accessible());
  require(xother.host()->is_schematized(false));

  // Body:

  // This is a component of xother if it is a component
  // and it is inferior to xother.

  result = is_component() && le(&xother);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
is_factor() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));

  // Body:

  // Every schema member except the top and bottom are
  // factors in some other schema.

  result = (index() != TOP_INDEX) && (index() != BOTTOM_INDEX);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
is_factor_of(const schema_poset_member& xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));
  require(is_ancestor_of(&xother));
  require(xother.state_is_read_accessible());
  require(xother.host()->is_schematized(false));

  // Body:

  result = (!is_table_dof()) && xother.covers(this);

  // Postconditions:

  // Exit

  return result;
}

size_t
sheaf::schema_poset_member::
size() const
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim()); // size is a dof of this

  // Body:

  result = dof_map().size();

  // Postconditions:

  // Exit

  return result;
}

size_t
sheaf::schema_poset_member::
alignment() const
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim());

  // Body:

  result = dof_map().alignment();

  // Postconditions:

  // Exit

  return result;
}

sheaf::primitive_type
sheaf::schema_poset_member::
type() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim());

  // Body:

  primitive_type result = dof_map().type();

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_dof_iterator*
sheaf::schema_poset_member::
dof_iterator(bool xis_table_dofs, int xversion) const
{
  poset_dof_iterator* result;

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));
  require(has_version(xversion));


  // Body:

  result = new poset_dof_iterator(*this, xis_table_dofs, xversion);

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
conforms_to(const schema_poset_member& xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // If we are comparing both table and row dofs, the dofs are guaranteed
  // to match in type and in order if this is greater than or equal to
  // xother.

  result = ge(&xother);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
conforms_to(const schema_poset_member& xother, bool xis_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_ancestor_of(&xother));

  // Body:

  // Schema in different hosts don't conform.

  result = has_same_host(&xother);
  if(result)
  {
    // The dofs defined by this must agree in type and in order
    // with those defined by xother. So traverse xother, comparing
    // dof types. If this runs out of dofs, or if there is a type
    // mismatch, result is false.

    poset_dof_iterator* lthis_itr  = dof_iterator(xis_table_dofs);
    poset_dof_iterator* lother_itr = dof_iterator(xis_table_dofs);
    while(result && !lother_itr->is_done())
    {
      result = !lthis_itr->is_done() &&
               (lthis_itr->item().type() == lother_itr->item().type());
      lthis_itr->next();
      lother_itr->next();
    }

    // Clean up.

    lthis_itr->force_is_done();
    delete lthis_itr;

    lother_itr->force_is_done();
    delete lother_itr;
  }

  /// @issue the definition of conformance implemented here is stricter
  /// than theoretically necessary. Theoretically, conformance should just
  /// require that the set of dofs defined by this schema contains the set
  /// of dofs defined by xother. But all the schema traversal algorithms
  /// and the dof access mechanisms depend on the dofs being ordered,
  /// hence the definition used here.

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
conforms_to(const poset_path& xpath) const
{
  bool result;

  // Preconditions:

  require(xpath.full());
  require(state_is_read_accessible());

  // Body:

  if(name_space()->contains_poset_member(xpath))
  {
    // Path is valid, check for conformance.
    // lother must conform to this to satisfy precondition
    // of conforms_to(schema_poset_member&).

    schema_poset_member* lother = clone();
    lother->attach_to_state(name_space(), xpath);
    result = conforms_to(*lother);
    lother->detach_from_state();
    delete lother;
  }
  else
  {
    // Path is invalid; can't conform.

    result = false;
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
conforms_to(const poset_path& xpath, bool xis_table_dofs) const
{
  bool result;

  // Preconditions:

  require(xpath.full());
  require(state_is_read_accessible());

  // Body:

  if(name_space()->contains_poset_member(xpath))
  {
    // Path is valid, check for conformance.
    // lother must conform to this to satisfy precondition
    // of conforms_to(schema_poset_member&, bool).

    schema_poset_member* lother = clone();
    lother->attach_to_state(name_space(), xpath);
    result = conforms_to(*lother, xis_table_dofs);
    lother->detach_from_state();
    delete lother;
  }
  else
  {
    // Path is invalid; can't conform.

    result = false;
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
table_conforms_to(const schema_poset_member& xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = conforms_to(xother, true);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
table_conforms_to(const poset_path& xpath) const
{
  bool result;

  // Preconditions:

  require(xpath.full());
  require(state_is_read_accessible());

  // Body:

  result = conforms_to(xpath, true);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
row_conforms_to(const schema_poset_member& xother) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = conforms_to(xother, false);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
row_conforms_to(const poset_path& xpath) const
{
  bool result;

  // Preconditions:

  require(xpath.full());
  require(state_is_read_accessible());

  // Body:

  result = conforms_to(xpath, false);

  // Postconditions:

  // Exit

  return result;
}


bool
sheaf::schema_poset_member::
conforms_to(const namespace_poset& xns,
            const poset_path& xchild_path,
            const poset_path& xparent_path,
            bool xauto_access)
{
  bool result;

  // Preconditions:

  require(xauto_access || xns.state_is_read_accessible());

  if(xauto_access)
  {
    xns.get_read_access();
  }

  require(xchild_path.full());
  require(xauto_access ||
          xns.member_poset(xchild_path).state_is_read_accessible());

  require(xparent_path.full());
  require(xauto_access ||
          xns.member_poset(xparent_path).state_is_read_accessible());

  // Body:

  // Can't conform if not in same poset.

  result = (xparent_path.poset_name() == xchild_path.poset_name());

  if(result)
  {
    // Parent and child are in same poset.
    // Get handles and test conformance.

    poset_state_handle& lschema_poset = xns.member_poset(xparent_path);
    if(xauto_access)
    {
      lschema_poset.get_read_access();
    }

    schema_poset_member lparent(&lschema_poset, xparent_path.member_name());
    schema_poset_member lchild(&lschema_poset, xchild_path.member_name());

    result = lchild.conforms_to(lparent);

    lparent.detach_from_state();
    lchild.detach_from_state();

    if(xauto_access)
    {
      lschema_poset.release_access();
    }
  }

  if(xauto_access)
  {
    xns.release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
conforms_to(const namespace_poset& xns,
            const poset_path& xchild_path,
            const poset_path& xparent_path,
            bool xis_table_dofs,
            bool xauto_access)
{
  bool result;

  // Preconditions:

  require(!xauto_access ? xns.state_is_read_accessible() : true);

  if(xauto_access)
  {
    xns.get_read_access();
  }

  require(xchild_path.full());
  require(!xauto_access ?
          xns.member_poset(xchild_path).state_is_read_accessible() :
          true);

  require(xparent_path.full());
  require(!xauto_access ?
          xns.member_poset(xparent_path).state_is_read_accessible() :
          true);

  // Body:

  // Can't conform if not in same poset.

  result = (xparent_path.poset_name() == xchild_path.poset_name());

  if(result)
  {
    // Parent and child are in same poset.
    // Get handles and test conformance.

    poset_state_handle& lschema_poset = xns.member_poset(xparent_path);
    if(xauto_access)
    {
      lschema_poset.get_read_access();
    }

    schema_poset_member lparent(&lschema_poset, xparent_path.member_name());
    schema_poset_member lchild(&lschema_poset, xchild_path.member_name());

    result = lchild.conforms_to(lparent, xis_table_dofs);

    lparent.detach_from_state();
    lchild.detach_from_state();

    if(xauto_access)
    {
      lschema_poset.release_access();
    }
  }

  if(xauto_access)
  {
    xns.release_access();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
table_conforms_to(const namespace_poset& xns,
                  const poset_path& xchild_path,
                  const poset_path& xparent_path,
                  bool xauto_access)
{
  bool result;

  // Preconditions:

  require(precondition_of(conforms_to(xns, xchild_path, xparent_path, true, xauto_access)));


  // Body:

  result = conforms_to(xns, xchild_path, xparent_path, true, xauto_access);

  // Postconditions:

  ensure(postcondition_of(conforms_to(xns, xchild_path, xparent_path, true, xauto_access)));

  // Exit

  return result;
}

bool
sheaf::schema_poset_member::
row_conforms_to(const namespace_poset& xns,
                const poset_path& xchild_path,
                const poset_path& xparent_path,
                bool xauto_access)
{
  bool result;

  // Preconditions:

  require(precondition_of(conforms_to(xns, xchild_path, xparent_path, false, xauto_access)));


  // Body:

  result = conforms_to(xns, xchild_path, xparent_path, false, xauto_access);

  // Postconditions:

  ensure(postcondition_of(conforms_to(xns, xchild_path, xparent_path, false, xauto_access)));

  // Exit

  return result;
}

sheaf::poset_path
sheaf::schema_poset_member::
make_schema(const namespace_poset& xns,
            const poset_path& xparent_path,
            const std::string& xname)
{
  // Preconditions:

  require(!xname.empty());
  require(xns.state_is_read_accessible());
  require(xparent_path.full());
  require(xns.contains_poset(xparent_path));
  require(xns.member_poset(xparent_path).state_is_read_write_accessible());
  require(xns.member_poset(xparent_path).is_schematized(false));
  require(xns.contains_poset_member(xparent_path));
  require(!xns.contains_poset_member(xparent_path.poset_name()+"/"+xname));

  /// @todo implement auto access for this routine.

  // Body:

  // Get a handle to the parent.
  
  schema_poset_member lparent(&xns, xparent_path, false);

  // Create the new schema as a jem of the parent.

  schema_poset_member lmember(lparent, true);
  lmember.put_name(xname, true, true);

  poset_path result(lmember.path());

  // Clean up.

  lmember.detach_from_state();
  lparent.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(result));
  ensure(result.poset_name() == xparent_path.poset_name());
  ensure(result.member_name() == xname);
  ensure(unexecutable(new member is join equivalent to parent member));

  // Exit:

  return result;
}

void
sheaf::schema_poset_member::
make_schema_no_jims(namespace_poset* xns,
                    const std::string& xposet_name,
                    const std::string& xmember_name,
                    const std::string& xparent_name)
{
  // Preconditions:

  // Body:

  poset_path lparent_path(xposet_name, xparent_name);

  make_schema(*xns, lparent_path, xmember_name);

  // Postconditions:

  // Exit:

  return;
}

sheaf::poset_path
sheaf::schema_poset_member::
make_schema(const namespace_poset& xns,
            const poset_path& xparent_path,
            const std::string& xname,
            const std::string xdof_names[],
            const primitive_type xdof_types[],
            const bool xis_table_dof[],
            const size_type xdof_ct,
            bool xauto_access)
{
  // Preconditions:

  require(!xauto_access ? xns.state_is_read_accessible() : true);

  if(xauto_access)
  {
    xns.get_read_access();
  }

  require(xparent_path.full());
  require(xns.contains_poset(xparent_path));
  require(!xauto_access ?
          xns.member_poset(xparent_path).state_is_read_write_accessible() :
          true);

  if(xauto_access)
  {
    xns.member_poset(xparent_path).get_read_write_access();
  }

  require(xns.member_poset(xparent_path).is_schematized(false));
  require(xns.contains_poset_member(xparent_path));
  require(!xname.empty());
  require(!xns.member_poset(xparent_path).contains_member(xname));
  require_for_all(i, 0, xdof_ct, !xdof_names[i].empty());
  require(unexecutable("if xdof_names[i] already exists, must have type xdof_type[i]"));
  require(unexecutable("if xdof_names[i] already exists, must have role xis_table_dof[i]"));

  // Body:

  // Get handles for the schema poset and the dof subposets.

  poset_state_handle& lschema_poset = xns.member_poset(xparent_path);
  subposet ltable_dof_sp(&lschema_poset, table_dof_subposet_name("top"));
  subposet lrow_dof_sp(&lschema_poset, row_dof_subposet_name("top"));

  // Create a temporary member handle.

  schema_poset_member lschema_mbr;

  // Put the parent in the expansion of the new member.

  lschema_mbr.attach_to_state(&lschema_poset, xparent_path.member_name());
  block<scoped_index> lexpansion(xdof_ct+1);
  lexpansion.push_back(lschema_mbr.index());

  // Put each dof in the expansion.

  if(xdof_ct > 0)
  {
    lschema_poset.begin_jim_edit_mode();
    for(size_type i=0; i<xdof_ct; ++i)
    {
      const string& ldof_name = xdof_names[i];
      if(lschema_poset.contains_member(ldof_name))
      {
        // The dof already exists, just attach to it.

        lschema_mbr.attach_to_state(ldof_name);

        // Requested role must match existing role.

        assertion(lschema_mbr.is_dof(xis_table_dof[i]));
      }
      else
      {
        // Create the dof.

        lschema_mbr.new_jim_state(xdof_types[i], false);
        lschema_mbr.put_name(ldof_name, true, false);

        // Insert it in the appropriate dof subposet.

        subposet& ldof_sp = xis_table_dof[i] ? ltable_dof_sp : lrow_dof_sp;
        ldof_sp.insert_member(lschema_mbr.index());
      }

      // Put it in the expansion.

      lexpansion.push_back(lschema_mbr.index());
    }

    lschema_poset.end_jim_edit_mode();
  }

  // Create the new member as the join of its expansion.

  lschema_mbr.new_jrm_state(lexpansion.base(), lexpansion.ct(), tern::TRUE, false);
  lschema_mbr.put_name(xname, true, false);

  // Make the result

  poset_path result(lschema_mbr.path());

  // Clean up.

  lschema_mbr.detach_from_state();
  lrow_dof_sp.detach_from_state();
  ltable_dof_sp.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(xparent_path.poset_name()+"/"+xname));

  if(xauto_access)
  {
    lschema_poset.release_access();
    xns.release_access();
  }

  // Exit:

  return result;
}

sheaf::poset_path
sheaf::schema_poset_member::
make_row_schema(const namespace_poset& xns,
                const poset_path& xparent_path,
                const std::string& xname,
                const std::string xdof_names[],
                const primitive_type xdof_types[],
                const size_type xdof_ct,
                bool xauto_access)
{

  // Preconditions:

  require(precondition_of(make_schema(xns, xparent_path, xname, xdof_names, xdof_types, false{}, xdof_ct, xauto_access)));

  // Body:

  bool* ldof_roles = new bool[xdof_ct];
  for(int i=0; i< xdof_ct; ++i)
  {
    ldof_roles[i] = false;
  }

  poset_path result =
    make_schema(xns,
                xparent_path,
                xname,
                xdof_names,
                xdof_types,
                ldof_roles,
                xdof_ct,
                xauto_access);

  delete [] ldof_roles;

  // Postconditions:

  ensure(postcondition_of(make_schema(xns, xparent_path, xname, xdof_names, xdof_types, false[], xdof_ct, xauto_access)));

  // Exit:

  return result;
}

sheaf::poset_path
sheaf::schema_poset_member::
make_homogeneous_row_schema(const namespace_poset& xns,
                            const poset_path& xparent_path,
                            const std::string& xname,
                            const std::string xdof_names[],
                            const primitive_type xdof_type,
                            const size_type xdof_ct,
                            bool xauto_access)
{
  // Preconditions:

  require(precondition_of(make_row_schema(xns, xparent_path, xname, xdof_names, xdof_type[], xdof_ct, xauto_access)));

  // Body:

  typedef primitive_type prim_type;
  prim_type* ldof_types = new prim_type[xdof_ct];
  for(int i=0; i< xdof_ct; ++i)
  {
    ldof_types[i] = xdof_type;
  }

  poset_path result =
    make_row_schema(xns,
                    xparent_path,
                    xname,
                    xdof_names,
                    ldof_types,
                    xdof_ct,
                    xauto_access);

  delete [] ldof_types;

  // Postconditions:

  ensure(postcondition_of(make_row_schema(xns, xparent_path, xname, xdof_names, xdof_type[], xdof_ct, xauto_access)));

  // Exit:

  return result;
}

void
sheaf::schema_poset_member::
make_row_dofs_schema(namespace_poset*  xns,
                     const std::string member_names[],
                     const int num_members,
                     const int member_dof_type,
                     const std::string& schema_poset_name,
                     const std::string& schema_member_name,
                     const std::string& schema_inherits_name)
{
  // Preconditions:

  // Body:

  typedef primitive_type prim_type;

  prim_type* ltypes = new prim_type[num_members];
  for(int i=0; i< num_members; ++i)
  {
    ltypes[i] = prim_type(member_dof_type);
  }

  bool* lroles = new bool[num_members];
  for(int i=0; i< num_members; ++i)
  {
    lroles[i] = false;
  }

  poset_path lparent_path(schema_poset_name, schema_inherits_name);

  make_schema(*xns,
              lparent_path,
              schema_member_name,
              member_names,
              ltypes,
              lroles,
              num_members,
              true);

  delete [] ltypes;
  delete [] lroles;

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::schema_poset_member::
make_table_dofs_schema(namespace_poset*  xns,
                       const std::string member_names[],
                       const int num_members,
                       const int member_dof_type,
                       const std::string& schema_poset_name,
                       const std::string& schema_member_name,
                       const std::string& schema_inherits_name)
{
  // Preconditions:

  // Body:

  typedef primitive_type prim_type;

  prim_type* ltypes = new prim_type[num_members];
  for(int i=0; i< num_members; ++i)
  {
    ltypes[i] = prim_type(member_dof_type);
  }

  bool* lroles = new bool[num_members];
  for(int i=0; i< num_members; ++i)
  {
    lroles[i] = true;
  }


  poset_path lparent_path(schema_poset_name, schema_inherits_name);

  make_schema(*xns,
              lparent_path,
              schema_member_name,
              member_names,
              ltypes,
              lroles,
              num_members,
              true);

  delete [] ltypes;
  delete [] lroles;

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::schema_poset_member::
force_cache_update()
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->is_schematized(false));

  // Body:

  update_table_cache();
  update_row_cache(true);

  // Postconditions:

  ensure(table_cache_consistent());
  ensure(row_cache_consistent());

  // Exit:

  return;
}

sheaf::dof_descriptor_array*
sheaf::schema_poset_member::
dof_descriptors(bool xis_table_dof) const
{
  dof_descriptor_array* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = xis_table_dof ? table_dof_descriptors() : row_dof_descriptors();

  // Postconditions:

  ensure(unexecutable(result != 0 implies it points to a buffer of length table_dof_ct()+1));

  // Exit

  return result;
}

sheaf::dof_descriptor_array*
sheaf::schema_poset_member::
table_dof_descriptors() const
{
  dof_descriptor_array* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!table_cache_consistent())
  {
    update_table_cache();
  }

  result = _table_dof_descriptors;

  // Postconditions:

  ensure(unexecutable(result != 0 implies it points to a buffer of length table_dof_ct()+1));

  // Exit

  return result;
}

sheaf::dof_descriptor_array*
sheaf::schema_poset_member::
row_dof_descriptors() const
{
  dof_descriptor_array* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  result = _row_dof_descriptors;

  // Postconditions:

  ensure(unexecutable(result != 0 implies it points to a buffer of length row_dof_ct()+1));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::subposet_state*
sheaf::schema_poset_member::
dof_subposet_state(bool xis_table_dof)
{
  return powerset_member(dof_subposet_index(xis_table_dof));
}

void
sheaf::schema_poset_member::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // dof_subposet_name() requires !name().empty().

  // Release the current table dof and row dof id space handles, if any.

  if(_table_dof_id_space != 0)
  {
    _table_dof_id_space->release_id_space();
    _table_dof_id_space = 0;
  }

  if(_row_dof_id_space != 0)
  {
    _row_dof_id_space->release_id_space();
    _row_dof_id_space = 0;
  }

  if(!name().empty())
  {
    host()->subposet_id(table_dof_subposet_name(), _table_dof_subposet_index);
    host()->subposet_id(row_dof_subposet_name(), _row_dof_subposet_index);

    // Assign the table dof id space.

    const index_space_family& lid_spaces = host()->member_id_spaces(false);

    if(lid_spaces.contains(table_dof_subposet_name()))
    {
      _table_dof_id_space = &lid_spaces.get_id_space(table_dof_subposet_name());
    }
  
    // Assign the row dof id space.

    if(lid_spaces.contains(row_dof_subposet_name()))
    {
      _row_dof_id_space = &lid_spaces.get_id_space(row_dof_subposet_name());
    }
  }
  else
  {
    _table_dof_subposet_index.invalidate();
    _row_dof_subposet_index.invalidate();
  }

  // Postconditions:

  // Exit

  return;
}

bool
sheaf::schema_poset_member::
table_cache_consistent() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = (_table_cache_index == index()) && (_table_cache_version == version());

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::schema_poset_member::
update_table_cache() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(initialize_table_dof_id_space())
  {
    update_table_dof_id_space();
  }

  _table_dof_ct = _table_dof_id_space->ct();

  update_table_dof_descriptors();

  _table_cache_index = index();
  _table_cache_version = version();

  // Postconditions:

  // Exit

  return;
}

bool
sheaf::schema_poset_member::
initialize_table_dof_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  bool result = initialize_dof_id_space(true);

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::schema_poset_member::
update_table_dof_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  update_dof_id_space(true);

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::schema_poset_member::
update_table_dof_descriptors() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  update_dof_descriptors(true,
			 _table_dof_descriptors,
			 _table_dof_ct,
			 _table_dof_tuple_ub);

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::schema_poset_member::
row_cache_consistent() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = (_row_cache_index == index()) && (_row_cache_version == version());

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::schema_poset_member::
update_row_cache(bool xupdate_id_space) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(xupdate_id_space || initialize_row_dof_id_space())
  {
    update_row_dof_id_space();
  }

  _row_dof_ct = _row_dof_id_space->ct();

  update_row_dof_descriptors();

  _row_cache_index = index();
  _row_cache_version = version();

  // Postconditions:

  // Exit

  return;
}

bool
sheaf::schema_poset_member::
initialize_row_dof_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  bool result = initialize_dof_id_space(false);

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::schema_poset_member::
update_row_dof_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  update_dof_id_space(false);

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::schema_poset_member::
update_row_dof_descriptors() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  update_dof_descriptors(false,
			 _row_dof_descriptors,
			 _row_dof_ct,
			 _row_dof_tuple_ub);

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::schema_poset_member::
initialize_dof_id_space(bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  bool result = false;

  index_space_handle* ldof_id_space =
    xis_table_dof ? _table_dof_id_space : _row_dof_id_space;

  if(ldof_id_space == 0)
  {
    // Dof id space is not initialized, initialize it.

    string ldof_id_space_name(schema_poset_member::dof_subposet_name(name(), xis_table_dof));
    if(!host()->member_id_spaces(false).contains(ldof_id_space_name))
    {
      // Id space does not exist, create it.  Force the update.

      array_index_space_state::new_space(host()->member_id_spaces(false),
					 ldof_id_space_name,
					 false, 0);

      result = true;
    }

    ldof_id_space = &host()->member_id_spaces(false).get_id_space(ldof_id_space_name);

    // Assign the data member.

    if(xis_table_dof)
    {
      _table_dof_id_space = ldof_id_space;
    }
    else
    {
      _row_dof_id_space = ldof_id_space;
    }
  }
  
  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::schema_poset_member::
update_dof_id_space(bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Get the dof id space;

  mutable_index_space_handle* ldof_id_space =
    reinterpret_cast<mutable_index_space_handle*>
    (xis_table_dof ? _table_dof_id_space : _row_dof_id_space);

  // Traverse the graph and extract the dof ids.

  string ltop_sp_name(schema_poset_member::dof_subposet_name("top", xis_table_dof));
  subposet ltop_sp(host(), ltop_sp_name);
  const index_space_handle& ltop_space = ltop_sp.id_space();

  set<pod_index_type> ltop_seq_ids;

  poset_dof_iterator* litr = dof_iterator(xis_table_dof);
  while(!litr->is_done())
  {
    ltop_seq_ids.insert(ltop_space.pod(litr->index()));
    litr->next();
  }
  delete litr;

  ldof_id_space->reserve(ltop_seq_ids.size());

  set<pod_index_type>::iterator lseq_id_itr;
  for(lseq_id_itr = ltop_seq_ids.begin();
      lseq_id_itr != ltop_seq_ids.end();
      ++lseq_id_itr)
  {
    ldof_id_space->push_back(ltop_space.hub_pod(*lseq_id_itr));
  }

  ltop_sp.detach_from_state();

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::schema_poset_member::
update_dof_descriptors(bool xis_table_dof,
		       dof_descriptor_array*& xdof_descriptors,
		       size_type xdof_ct,
		       size_type& xdof_tuple_ub) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // (Re)allocate the dof descriptors.

  if(xdof_descriptors != 0)
  {
    xdof_descriptors->remove_reference();
  }
  xdof_descriptors = new dof_descriptor_array(xdof_ct);
  xdof_descriptors->add_reference();

 // Compute the dof descriptors and dof tuple upper bound

  schema_poset_member* lschema_mbr = clone();
  xdof_tuple_ub = 0;
  index_space_handle* ldof_id_space =
    xis_table_dof ? _table_dof_id_space : _row_dof_id_space;

  index_space_iterator& itr = ldof_id_space->get_iterator();
  while(!itr.is_done())
  {
    lschema_mbr->attach_to_state(_host, itr.hub_pod());

    xdof_tuple_ub = align(xdof_tuple_ub, lschema_mbr->alignment());

    dof_descriptor_array::dof_descriptor& ldesc = (*xdof_descriptors)[itr.pod()];

    ldesc.size      = lschema_mbr->size();
    ldesc.alignment = lschema_mbr->alignment();
    ldesc.type      = lschema_mbr->type();
    ldesc.offset    = xdof_tuple_ub;

    xdof_tuple_ub += ldesc.size;

#ifdef DIAGNOSTIC_OUTPUT
    cout << " dof name: " << lschema_mbr->name()
	 << " seq id: " << itr.pod()
	 << " dof descriptor: " << ldesc
	 << endl;
#endif

    itr.next();
  }

  ldof_id_space->release_iterator(itr);
  lschema_mbr->detach_from_state();
  delete lschema_mbr;
  
  // The last offset is the size of the entire tuple

  dof_descriptor_array::dof_descriptor& ldesc = (*xdof_descriptors)[xdof_ct];
  ldesc.size      = 0;
  ldesc.alignment = 0;
  ldesc.type      = NOT_A_PRIMITIVE_TYPE;
  ldesc.offset    = xdof_tuple_ub;

  // Postcconditions:

  ensure((xdof_ct > 0) == (xdof_tuple_ub > 0));
 
  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NEW DOF ACCESS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_handle&
sheaf::schema_poset_member::
dof_id_space(bool xis_table_dofs) const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  if(xis_table_dofs && !table_cache_consistent())
  {
    update_table_cache();
  }
  else if(!xis_table_dofs && !row_cache_consistent())
  {
    update_row_cache();
  }

  const index_space_handle& result =
    xis_table_dofs ? *_table_dof_id_space : *_row_dof_id_space;

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::schema_poset_member::
dof_id_space(bool xis_table_dofs, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const index_space_handle& result = dof_id_space(xis_table_dofs);

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::schema_poset_member::
table_dof_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  if(!table_cache_consistent())
  {
    update_table_cache();
  }

  const index_space_handle& result = *_table_dof_id_space;

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::schema_poset_member::
table_dof_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const index_space_handle& result = table_dof_id_space();

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::schema_poset_member::
row_dof_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());
  
  // Body:

  if(!row_cache_consistent())
  {
    update_row_cache();
  }

  const index_space_handle& result = *_row_dof_id_space;

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::index_space_handle&
sheaf::schema_poset_member::
row_dof_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  const index_space_handle& result = row_dof_id_space();

  if(xauto_access)
  {
    release_access();
  }
  
  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

std::string
sheaf::schema_poset_member::
name(pod_index_type xdof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(dof_id_space(xis_table_dof).contains(xdof_id));
  
  // Body:

  pod_index_type lhub_pod = dof_id_space(xis_table_dof).hub_pod(xdof_id);

  string result(host()->member_name(lhub_pod, false));
  
  // Postconditions:

  // Exit:

  return result;
}

std::string
sheaf::schema_poset_member::
name(const scoped_index& xdof_id, bool xis_table_dof, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(dof_id_space(xis_table_dof, xauto_access).contains(xdof_id));
  
  // Body:

  string result(host()->member_name(xdof_id, xauto_access));
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::schema_poset_member::
size(pod_index_type xdof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(dof_id_space(xis_table_dof).contains(xdof_id));
  
  // Body:

  size_type result = (*dof_descriptors(xis_table_dof))[xdof_id].size;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::schema_poset_member::
size(const scoped_index& xdof_id, bool xis_table_dof, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(dof_id_space(xis_table_dof, xauto_access).contains(xdof_id));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  pod_index_type lindex = dof_id_space(xis_table_dof).pod(xdof_id);  
  size_type result = size(lindex, xis_table_dof);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::schema_poset_member::
size(const std::string& xname, bool xis_table_dof, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(contains_dof(xname, xis_table_dof));
  
  // Body:

  pod_index_type lhub_id = host()->member_id(xname, false);
  
  pod_index_type lindex = dof_id_space(xis_table_dof).pod(lhub_id);
  size_type result = size(lindex, xis_table_dof);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}


sheaf::size_type
sheaf::schema_poset_member::
alignment(pod_index_type xdof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(dof_id_space(xis_table_dof).contains(xdof_id));
  
  // Body:

  size_type result = (*dof_descriptors(xis_table_dof))[xdof_id].alignment;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::schema_poset_member::
alignment(const scoped_index& xdof_id, bool xis_table_dof, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(dof_id_space(xis_table_dof, xauto_access).contains(xdof_id));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  pod_index_type lindex = dof_id_space(xis_table_dof).pod(xdof_id);
  size_type result = alignment(lindex, xis_table_dof);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::schema_poset_member::
alignment(const std::string& xname, bool xis_table_dof, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(contains_dof(xname, xis_table_dof));
  
  // Body:

  pod_index_type lhub_id = host()->member_id(xname, false);
  
  pod_index_type lindex = dof_id_space(xis_table_dof).pod(lhub_id);
  size_type result = alignment(lindex, xis_table_dof);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::primitive_type
sheaf::schema_poset_member::
type(pod_index_type xdof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(dof_id_space(xis_table_dof).contains(xdof_id));
  
  // Body:

  primitive_type result = 
    primitive_attributes::id((*dof_descriptors(xis_table_dof))[xdof_id].type);

  // Postconditions:

  // Exit:

  return result;
}

sheaf::primitive_type
sheaf::schema_poset_member::
type(const scoped_index& xdof_id, bool xis_table_dof, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(dof_id_space(xis_table_dof, xauto_access).contains(xdof_id));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  pod_index_type lindex = dof_id_space(xis_table_dof).pod(xdof_id);
  primitive_type result = type(lindex, xis_table_dof);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::primitive_type
sheaf::schema_poset_member::
type(const std::string& xname, bool xis_table_dof, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(contains_dof(xname, xis_table_dof));
  
  // Body:

  pod_index_type lhub_id = host()->member_id(xname, false);
  
  pod_index_type lindex = dof_id_space(xis_table_dof).pod(lhub_id);
  primitive_type result = type(lindex, xis_table_dof);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::schema_poset_member::
offset(pod_index_type xdof_id, bool xis_table_dof) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(dof_id_space(xis_table_dof).contains(xdof_id));
  
  // Body:

  size_type result = (*dof_descriptors(xis_table_dof))[xdof_id].offset;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::schema_poset_member::
offset(const scoped_index& xdof_id, bool xis_table_dof, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(dof_id_space(xis_table_dof, xauto_access).contains(xdof_id));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  pod_index_type lindex = dof_id_space(xis_table_dof).pod(xdof_id);
  size_type result = offset(lindex, xis_table_dof);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::schema_poset_member::
offset(const std::string& xname, bool xis_table_dof, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  if(xauto_access)
  {
    get_read_access();
  }

  require(contains_dof(xname, xis_table_dof));
  
  // Body:

  pod_index_type lhub_id = host()->member_id(xname, false);
  
  pod_index_type lindex = dof_id_space(xis_table_dof).pod(lhub_id);
  size_type result = offset(lindex, xis_table_dof);
  
  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_iterator*
sheaf::schema_poset_member::
get_decomposition(pod_index_type xindex) const
{
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->includes_subposet(xindex));

  // Body:

  index_iterator* result = host()->get_decomposition(xindex);

  // Postconditions:

  // Exit:

  return result;
}

sheaf::index_iterator*
sheaf::schema_poset_member::
bound_iterator(const poset_bounds& xbounds, bool xis_ub) const
{
  index_iterator* result;
  
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  pod_index_type lbnd_id;
  bool lsingleton;

  if(xis_ub)
  {
    lbnd_id = xbounds.ub_id();
    lsingleton = xbounds.ub_is_singleton();
  }
  else
  {
    lbnd_id = xbounds.lb_id();
    lsingleton = xbounds.lb_is_singleton();
  }

  if(lsingleton)  
  {
    zn_to_bool* l_lb = new zn_to_bool();
    l_lb->force(lbnd_id, true);
    result = new index_iterator(l_lb, _host->member_hub_id_space(false), true);
  }
  else
  {
    result = get_decomposition(lbnd_id);
  }

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::schema_poset_member::
get_int_id(pod_index_type xext_id, const std::string& xid_space_name) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xext_id >= host()->standard_member_ct() ?
          host()->member_id_spaces(false).contains(xid_space_name) :
          true);
  require(xext_id >= host()->standard_member_ct() ?
          host()->member_id_spaces(false).contains(xid_space_name, xext_id) :
          true);

  // Body:

  pod_index_type result = host()->get_int_id(xext_id, xid_space_name, false);

  // Postconditions:

  ensure(host()->contains_member(result, false));

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::schema_poset_member::
get_ext_id(const std::string& xid_space_name) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(precondition_of(host()->get_ext_id(index(), xid_space_name)));


  // Body:

  pod_index_type result = host()->get_ext_id(index(), xid_space_name, false);

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::schema_poset_member::
get_ext_ids(const std::string& xid_space_name,
            pod_index_type& xschema_poset_ext_id,
            pod_index_type& xschema_member_ext_id,
            pod_index_type& xbase_space_ext_id,
	    pod_index_type& xfiber_schema_ext_id,
            pod_index_type& xlocal_schema_ext_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(name_space()->state_is_read_accessible());

  // Body:

  // Get the external ids for the schema poset (this->host()) and member (this).

  xschema_poset_ext_id  =
    name_space()->get_ext_id(host()->index(), xid_space_name, false);

  xschema_member_ext_id =
    host()->get_ext_id(index(), xid_space_name, false);

  // Other external ids are undefined.

  xbase_space_ext_id = invalid_pod_index();
  xfiber_schema_ext_id = invalid_pod_index();
  xlocal_schema_ext_id = invalid_pod_index();

  // Postconditions:

  // Exit:

  return;
}

sheaf::schema_poset_member&
sheaf::schema_poset_member::
ext_data_type_schema()
{
  return *this;
}

size_t
sheaf::schema_poset_member::
ext_data_type_ct(bool xis_table_schema) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // For oridnary schema members,
  // the external data type is the entire schema.

  size_t result = 1;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEGREE OF FREEDOM (DOF) TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::primitives_poset_dof_map&
sheaf::schema_poset_member::
dof_map(bool xrequire_write_access)
{

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  // poset_state_handle ensures schema uses primitives_poset_dof_map
  /// @error above invariant is not yet implemented in poset_state_handle and
  /// apparently not enforced by preconditions either.

  primitives_poset_dof_map& result =
    reinterpret_cast<primitives_poset_dof_map&>(total_poset_member::dof_map(xrequire_write_access));

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::primitives_poset_dof_map&
sheaf::schema_poset_member::
dof_map(bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  // poset_state_handle ensures schema uses primitives_poset_dof_map
  /// @error above invariant is not yet implemented in poset_state_handle and
  /// apparently not enforced by preconditions either.

  const primitives_poset_dof_map& result =
    reinterpret_cast<const primitives_poset_dof_map&>(total_poset_member::dof_map(xrequire_write_access));

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::schema_poset_member::
dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  result = dynamic_cast<const primitives_poset_dof_map*>(xdof_map) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::schema_poset_member::
detach_from_state()
{
  // Preconditions:

  // Body:

  if(_table_dof_id_space != 0)
  {
    _table_dof_id_space->release_id_space();
    _table_dof_id_space = 0;
  }

  if(_row_dof_id_space != 0)
  {
    _row_dof_id_space->release_id_space();
    _row_dof_id_space = 0;
  }

  abstract_poset_member::detach_from_state();

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::schema_poset_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const schema_poset_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::schema_poset_member*
sheaf::schema_poset_member::
clone() const
{
  // Preconditions:

  // Body:

  // create new handle of the current class.

  schema_poset_member *result = new schema_poset_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

bool
sheaf::schema_poset_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && total_poset_member::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    /// @issue what are the invariants for this class
    /// @todo implement schema_poset_member::invariant() const

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
sheaf::
deep_size(const schema_poset_member& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  require(xp.state_is_read_accessible());

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

#ifdef DIAGNOSTIC_OUTPUT
  cout << "$$$ deep_size(const schema_poset_mamber& xp) &xp = " << &xp << endl;
  cout << "$$$ deep_size(const schema_poset_mamber& xp) sizeof(xp) = " << sizeof(xp) << endl;
#endif

  // Add any contributions from the parent class.

  const total_poset_member& p = static_cast<const total_poset_member&>(xp);
  result += deep_size(p);

  // Determine the deep size of data members:
  //   dof_descriptor_array* _table_dof_descriptors.
  //   dof_descriptor_array* _row_dof_descriptors.

  if(xp.table_dof_descriptors() != 0)
  {
    result += deep_size(*(xp.table_dof_descriptors()), false);
  }

  if(xp.row_dof_descriptors() != 0)
  {
    result += deep_size(*(xp.row_dof_descriptors()), false);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "$$$ deep_size(const schema_poset_mamber& xp) result = " << result << endl;
#endif

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
