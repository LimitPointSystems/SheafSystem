

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class binary_section_space_schema_member.

#include "binary_section_space_schema_member.h"

#include "binary_section_space_schema_poset.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "fiber_bundles_namespace.h"
#include "sec_rep_descriptor.h"
#include "sec_rep_descriptor_poset.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xbase_path,
         const poset_path& xfiber_path,
         const poset_path& xrep_path,
         bool xauto_access)
{
  // cout << endl << "Entering binary_section_space_schema_member::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, host_type::standard_schema_path(), xauto_access));

  require(xbase_path.full());
  require(xns.state_is_auto_read_accessible<base_space_poset>(xbase_path, xauto_access));

  require(!xfiber_path.empty());
  require(xns.state_is_auto_read_accessible(xfiber_path, xauto_access));

  require(xrep_path.full());
  require(xns.state_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xbase_path, xfiber_path, xrep_path, xauto_access);

  // Postconditions:

  //  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.base_space_path(true).poset_name() == xbase_path.poset_name());
  ensure(result.fiber_space_path(true) == xfiber_path);
  ensure(result.rep_path(true) == xrep_path);

  // Exit:

  // cout << "Leaving binary_section_space_schema_member::new_host." << endl;
  return result;
}

// sheaf::poset_path
// fiber_bundle::binary_section_space_schema_member::
// standard_host_path(const poset_path& xbase_path, const poset_path& xfiber_path, const poset_path& xrep_path)
// {
//   // cout << endl << "Entering binary_section_space_schema_member::standard_host_path." << endl;

//   // Preconditions:

//   require(xbase_path.full());
//   require(rep_path.full());
//   require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));

//   // Body:
  
//   string lposet_name(xfiber_path.poset_name());
//   lposet_name += "_on_";
//   lposet_name += xbase_path.poset_name();
//   lposet_name += "_";
//   lposet_name += xrep_path.member_name();
//   lposet_name += "_schema";

//   sheaf::poset_path result(lposet_name, "");

//   // Postconditions:

//   ensure(!result.full());

//   // Exit:

//   // cout << "Leaving binary_section_space_schema_member::standard_host_path." << endl;
//   return result;
// }

// sheaf::poset_path
// fiber_bundle::binary_section_space_schema_member::
// standard_path(const poset_path& xbase_path, const poset_path& xfiber_path, const poset_path& xrep_path)
// {
//   // cout << endl << "Entering binary_section_space_schema_member::standard_path." << endl;

//   // Preconditions:

//   require(xbase_path.full());
//   require(!xfiber_path.empty());
//   require(rep_path.full());

//   // Body:

//   poset_path result(standard_host_path(xbase_path, xfiber_path, xrep_path));

//   string lmember_name(xfiber_path.poset_name());
//   lmember_name += "_on_";
//   lmamber_name += xbase_space.member_name();

//   result.put_member_name(lmember_name);
  
//   // Postconditions:

//   ensure(result.full());

//   // Exit:

//   // cout << "Leaving binary_section_space_schema_member::standard_path." << endl;
//   return result;
// }



// fiber_bundle::binary_section_space_schema_member::host_type&
// fiber_bundle::binary_section_space_schema_member::
// standard_host(namespace_type& xns, 
//               const poset_path& xbase_path,
//               const poset_path& xfiber_path,
//               const poset_path& xrep_path,
//               bool xauto_access)
// {
//   // cout << endl << "Entering binary_section_space_schema_member::standard_host." << endl;

//   // Preconditions:


//   require(xns.state_is_auto_read_write_accessible(xauto_access));

//   require(xns.path_is_available<host_type>(standard_host_path(xbase_path, xfiber_path, xrep_path), xauto_access));
  

//   require(xschema_path.full());
//   require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
//   require(schema_poset_member::conforms_to(xns, xschema_path, host_type::standard_schema_path(), xauto_access));

//   require(xbase_path.full());
//   require(xns.state_is_auto_read_accessible<base_space_poset>(xbase_path, xauto_access));

//   require(!xfiber_path.empty());
//   require(xns.state_is_auto_read_accessible(xfiber_path, xauto_access));

//   require(xrep_path.full());
//   require(xns.state_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));

//   // Body:

//   poset_path lstd_path(standard_host_path(xbase_path, xfiber_path, xrep_path));
//   poset_path lstd_schema_path(host_type::standard_schema_path());
  
//   host_type& result = new_host(xns, lstd_path, lstd_schema_path, xbase_path, xfiber_path, xrep_path, xauto_access);

//   // Postconditions:

//   //  ensure(xns.owns(result, xauto_access));
//   ensure(result.path(true) == standard_host_path(xbase_path, xfiber_path, xrep_path));
//   ensure(result.state_is_not_read_accessible());
//   ensure(result.schema(true).path(xauto_access) == host_type::standard_schema_path());

//   ensure(unexecutable("result.base_space_path() == xbase_space_path"));
//   ensure(unexecutable("result.fiber_space_path() == xfiber_space_path"));
//   ensure(unexecutable("result.rep_path() == xrep_path"));

//   // Exit:

//   // cout << "Leaving binary_section_space_schema_member::standard_host." << endl;
//   return result;
// }

// sheaf::poset_path
// fiber_bundle::binary_section_space_schema_member::
// standard_schema(namespace_type& xns, 
//                 const poset_path& xbase_path,
//                 const poset_path& xfiber_path,
//                 const poset_path& xrep_path,
//                 bool xauto_access)
// {
//   // cout << endl << "Entering binary_section_space_schema_member::standard_host." << endl;

//   // Preconditions:


//   require(xns.state_is_auto_read_write_accessible(xauto_access));

//   require(xns.path_is_available<host_type>(standard_host_path(xbase_path, xfiber_path, xrep_path), xauto_access));
  

//   require(xschema_path.full());
//   require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
//   require(schema_poset_member::conforms_to(xns, xschema_path, host_type::standard_schema_path(), xauto_access));

//   require(xbase_path.full());
//   require(xns.state_is_auto_read_accessible<base_space_poset>(xbase_path, xauto_access));

//   require(!xfiber_path.empty());
//   require(xns.state_is_auto_read_accessible(xfiber_path, xauto_access));

//   require(xrep_path.full());
//   require(xns.state_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));

//   // Body:

//   // Find or create the standard host.

//   host_type& lhost = standard_host(xns, xbase_path, xfiber_path, xrep_path);

//   // All members of the schema exist implicitly, but a member can't 
//   // be accessed by path unless we explicitly give it a name..

//   poset_path lstd_path(standard_path(xbase_path, xfiber_path, xrep_path));
//   if(!lhost.contains_member(lstd_path.member_name()))
//   {  
//     binary_section_space_schema_member lmbr(&lhost, xbase_path, lhost.fiber_space().schema().name());
//     lmbr.put_name(lstd_path.member_name(), true, false);
//   }

//   // Postconditions:

//   // !!! start here - what are the postconditions?

//   //  ensure(xns.owns(result, xauto_access));
//   ensure(result.path(true) == standard_host_path(xbase_path, xfiber_path, xrep_path));
//   ensure(result.state_is_not_read_accessible());
//   ensure(result.schema(true).path(xauto_access) == host_type::standard_schema_path());

//   ensure(unexecutable("result.base_space_path() == xbase_space_path"));
//   ensure(unexecutable("result.fiber_space_path() == xfiber_space_path"));
//   ensure(unexecutable("result.rep_path() == xrep_path"));

//   // Exit:

//   // cout << "Leaving binary_section_space_schema_member::standard_host." << endl;
//   return result;
// }

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// BINARY_SECTION_SPACE_SCHEMA_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::binary_section_space_schema_member::
binary_section_space_schema_member()
    : section_space_schema_member()
{
  // Preconditions:

  // Body:

  // Nothing to do; base class does it all.

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
  ensure(!is_valid(base_space_id()));
  ensure(!is_valid(fiber_schema_id()));
  ensure(!base_space().is_attached());
  ensure(!fiber_schema().is_attached());

  // Exit:
}

fiber_bundle::binary_section_space_schema_member::
binary_section_space_schema_member(const binary_section_space_schema_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

fiber_bundle::binary_section_space_schema_member&
fiber_bundle::binary_section_space_schema_member::
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

fiber_bundle::binary_section_space_schema_member&
fiber_bundle::binary_section_space_schema_member::
operator=(const binary_section_space_schema_member& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  //Body:

  not_implemented();

  //Postconditions:

  ensure(invariant());

  //Exit:

  return *this;
}

fiber_bundle::binary_section_space_schema_member::
~binary_section_space_schema_member()
{

  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

fiber_bundle::binary_section_space_schema_member::
binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                   pod_index_type xhub_id)
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

fiber_bundle::binary_section_space_schema_member::
binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                   const scoped_index& xid)
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

fiber_bundle::binary_section_space_schema_member::
binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                   const string& xname)
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


fiber_bundle::binary_section_space_schema_member::
binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                   pod_index_type xbase_space_id,
                                   pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xbase_space_id, xfiber_schema_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit

  return;
}

fiber_bundle::binary_section_space_schema_member::
binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                   const scoped_index& xbase_space_id,
                                   const scoped_index& xfiber_schema_id)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost,
		  xbase_space_id.hub_pod(),
		  xfiber_schema_id.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit

  return;
}

fiber_bundle::binary_section_space_schema_member::
binary_section_space_schema_member(const binary_section_space_schema_poset* xhost,
                                   const poset_path& xbase_path,
                                   const poset_path& xfiber_schema_path)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xbase_path, xfiber_schema_path);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit

  return;
}

fiber_bundle::binary_section_space_schema_member::
binary_section_space_schema_member(const namespace_poset& xns,
                                   const poset_path& xpath,
                                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(&xns, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION_SPACE_SCHEMA_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::binary_section_component_iterator*
fiber_bundle::binary_section_space_schema_member::
component_iterator() const
{
  binary_section_component_iterator* result = 0;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = new binary_section_component_iterator(*this);

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SCHEMA_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::primitive_type
fiber_bundle::binary_section_space_schema_member::
dof_tuple_type(bool xis_table_dof) const
{
  primitive_type result = NOT_A_PRIMITIVE_TYPE;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = fiber_schema().dof_tuple_type(xis_table_dof);

  // Postconditions:

  ensure(xis_table_dof ? result == NOT_A_PRIMITIVE_TYPE : true);

  // Exit

  return result;
}

sheaf::dof_descriptor_array*
fiber_bundle::binary_section_space_schema_member::
dof_descriptors(bool xis_table_dof) const
{
  dof_descriptor_array* result = 0;

  // Preconditions:

  require(state_is_read_accessible());

  // Dof descriptors not defined for row dofs.

  require(xis_table_dof);

  // Body:

  result = fiber_schema().dof_descriptors(xis_table_dof);

  // Postconditions:

  ensure(unexecutable(result != 0 implies it points to a buffer of length table_dof_ct()+1));

  // Exit

  return result;
}

bool
fiber_bundle::binary_section_space_schema_member::
is_dof(bool xin_table_dofs) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  if(xin_table_dofs)
  {
    // Table dofs:

    // Table dofs are {base.bottom()} x {fiber schema table dofs}.

    result = (_base_space_id == BOTTOM_INDEX) && fiber_schema().is_table_dof();
  }
  else
  {
    // Row dofs:

    result = host()->discretization().contains_member(_base_space_id) && fiber_schema().is_row_dof();
  }

  // Postconditions:

  // Exit

  return result;
}

size_t
fiber_bundle::binary_section_space_schema_member::
size() const
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema().is_jim());

  // Body:

  result = fiber_schema().size();

  // Postconditions:

  // Exit

  return result;
}

size_t
fiber_bundle::binary_section_space_schema_member::
alignment() const
{
  size_t result;

  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema().is_jim());

  // Body:

  result = fiber_schema().alignment();

  // Postconditions:

  // Exit

  return result;
}

sheaf::primitive_type
fiber_bundle::binary_section_space_schema_member::
type() const
{
  sheaf::primitive_type result;

  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema().is_jim());

  // Body:

  result = fiber_schema().type();

  // Postconditions:

  ensure(is_primitive_index(result));

  // Exit

  return result;
}

fiber_bundle::binary_section_dof_iterator*
fiber_bundle::binary_section_space_schema_member::
dof_iterator(bool xis_table_dofs, int xversion) const
{
  binary_section_dof_iterator* result;

  // Preconditions:

  require(state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  result = new binary_section_dof_iterator(*this, xis_table_dofs, xversion);

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::binary_section_space_schema_member::
update_row_cache(bool xupdate_id_map) const
{
  // Preconditions:

  // Body:

  section_space_schema_member::update_row_cache(xupdate_id_map);

  _row_dof_ct          = _discretization_ct*fiber_schema().row_dof_ct();

  _row_dof_tuple_ub    = _discretization_ct*fiber_schema().row_dof_tuple_ub();

  _row_dof_descriptors = 0;

  _row_cache_index = index();
  _row_cache_version = version();

  // Postconditions:

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_iterator*
fiber_bundle::binary_section_space_schema_member::
get_decomposition(pod_index_type xindex) const
{
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.

  // Preconditions:

  require(state_is_read_accessible());
  require(host()->base_space().includes_subposet(xindex));

  // Body:

  zn_to_bool* ldecomp = new zn_to_bool();

  subposet ldecomp_sp(&host()->base_space(), xindex);

  index_iterator litr = ldecomp_sp.indexed_member_iterator();
  while(!litr.is_done())
  {
    pod_index_type lschema_mbr_id =
      host()->get_index_from_components(litr.index().pod(), fiber_schema_id());

    ldecomp->force(lschema_mbr_id, true);

    litr.next();
  }

  ldecomp_sp.detach_from_state();

  index_iterator* result = new index_iterator(ldecomp,
					      host()->member_hub_id_space(false),
					      true);

  // Postconditions:

  // Exit:

  return result;
}
sheaf::pod_index_type
fiber_bundle::binary_section_space_schema_member::
get_int_id(pod_index_type xext_id, const string& xid_space_name) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(precondition_of(host()->base_space().get_ext_id(index(), xid_space_name)));

  // Body:

  /// @hack product subposet hack, ver 2.
  /// Section space schema member external ids are really base space external ids.

  pod_index_type lbase_id =
    host()->base_space().get_int_id(xext_id, xid_space_name, false);

  pod_index_type result =
    host()->get_index_from_components(lbase_id, fiber_schema_id());

  // Postconditions:

  ensure(host()->contains_member(result));

  // Exit:

  return result;
}

void
fiber_bundle::binary_section_space_schema_member::
get_ext_ids(const string& xid_space_name,
            pod_index_type& xschema_poset_ext_id,
            pod_index_type& xschema_member_ext_id,
            pod_index_type& xbase_space_ext_id,
            pod_index_type& xfiber_schema_ext_id,
            pod_index_type& xlocal_schema_ext_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->member_id_spaces(false).contains(xid_space_name));
  require(host()->base_space().member_id_spaces(false).contains(xid_space_name));
  require(host()->base_space().member_id_spaces(false).contains_hub(xid_space_name, base_space_id()));
  require(host()->fiber_schema().member_id_spaces(false).contains(xid_space_name));
  require(host()->fiber_schema().member_id_spaces(false).contains_hub(xid_space_name, fiber_schema_id()));

  // Body:

  // Get the external id for the schema poset (this->host()).

  xschema_poset_ext_id =
    name_space()->get_ext_id(host()->index(), xid_space_name, false);

  // Schema member external id is undefined.

  xschema_member_ext_id = invalid_pod_index();

  // Get the external id for the base space component.

  xbase_space_ext_id =
    host()->base_space().get_ext_id(base_space_id(), xid_space_name, false);

  // Get the external id for the fiber schema component.

  xfiber_schema_ext_id =
    host()->fiber_schema().get_ext_id(fiber_schema_id(), xid_space_name, false);

  // Local schema id is undefined.

  xlocal_schema_ext_id = invalid_pod_index();

  // Postconditions:


  // Exit:

  return;
}

sheaf::schema_poset_member&
fiber_bundle::binary_section_space_schema_member::
ext_data_type_schema()
{
  return fiber_schema();
}

size_t
fiber_bundle::binary_section_space_schema_member::
ext_data_type_ct(bool xis_table_schema) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // For binary schema members,
  // the external data type is the entire schema.

  size_t result = xis_table_schema ? 1 : discretization_ct();

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
fiber_bundle::binary_section_space_schema_member::
dof_map(bool xrequire_write_access)
{

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  primitives_poset_dof_map& result = fiber_schema().dof_map(xrequire_write_access);

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::primitives_poset_dof_map&
fiber_bundle::binary_section_space_schema_member::
dof_map(bool xrequire_write_access) const
{

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  const primitives_poset_dof_map& result = fiber_schema().dof_map(xrequire_write_access);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::binary_section_space_schema_member::
attach_to_state(pod_index_type xbase_space_id,
                pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->base_space().contains_member(xbase_space_id));
  require(host()->fiber_schema().contains_member(xfiber_schema_id));

  // Body:

  _index = hub_id(host()->get_index_from_components(xbase_space_id, xfiber_schema_id));
  _version = CURRENT_HOST_VERSION;

  /// @issue what are the dof subposets?

  attach_handle_data_members();

  // Postconditions:

  ensure(base_space_id() == xbase_space_id);
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id);
  ensure(fiber_schema().is_attached());

  // Exit

  return;
}

void
fiber_bundle::binary_section_space_schema_member::
attach_to_state(const section_space_schema_poset* xhost,
                pod_index_type xbase_space_id,
                pod_index_type xfiber_schema_id)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(xhost->base_space().contains_member(xbase_space_id));
  require(xhost->fiber_schema().contains_member(xfiber_schema_id));

  // Body:

  _host  = const_cast<section_space_schema_poset*>(xhost);
  _index = hub_id(host()->get_index_from_components(xbase_space_id, xfiber_schema_id));
  _version = CURRENT_HOST_VERSION;

  /// @issue what are the dof subposets?

  attach_handle_data_members();

  // Postconditions:

  ensure(base_space_id() == xbase_space_id);
  ensure(base_space().is_attached());
  ensure(fiber_schema_id() == xfiber_schema_id);
  ensure(fiber_schema().is_attached());

  // Exit

  return;
}

void
fiber_bundle::binary_section_space_schema_member::
attach_to_state(const section_space_schema_poset* xhost,
                const poset_path& xbase_path,
                const poset_path& xfiber_schema_path)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(xbase_path.full());
  require(xhost->base_space().contains_member(xbase_path.member_name()));
  require(xfiber_schema_path.full());
  require(xhost->fiber_schema().contains_member(xfiber_schema_path.member_name()));

  // Body:

  attach_to_state(xhost,
                  xhost->base_space().member_id(xbase_path.member_name(), false),
                  xhost->fiber_schema().member_id(xfiber_schema_path.member_name(), false));

  // Postconditions:

  ensure(is_attached());
  ensure(base_space().has_path(xbase_path, false));
  ensure(fiber_schema().has_path(xfiber_schema_path, false));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HOST POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::binary_section_space_schema_member::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const binary_section_space_schema_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::binary_section_space_schema_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const binary_section_space_schema_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::binary_section_space_schema_member*
fiber_bundle::binary_section_space_schema_member::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  binary_section_space_schema_member *result =
    new binary_section_space_schema_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;
}

bool
fiber_bundle::binary_section_space_schema_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && schema_poset_member::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    /// @issue what are the invariants for this class
    /// @todo implement binary_section_space_schema_member::invariant() const

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
