

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class fiber_bundles_namespace

#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "at2.h"
#include "at2_e2.h"
#include "at2_e3.h"
#include "at3.h"
#include "at3_e3.h"
#include "atp.h"
#include "atp_space.h"
#include "array_index_space_state.h"
#include "base_space_member.h"
#include "base_space_member_prototype.h"
#include "biorder_iterator.h"
#include "block.impl.h"
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "e4.h"
#include "ed.h"
#include "fiber_bundles_namespace.h"
#include "gl2.h"
#include "gl3.h"
#include "gln.h"
#include "gln_space.h"
#include "homogeneous_block.h"
#include "index_iterator.h"
#include "index_space_iterator.h"
#include "jcb.h"
#include "jcb_space.h"
#include "jcb_e13.h"
#include "jcb_e23.h"
#include "jcb_e33.h"
#include "jcb_ed.h"
#include "met.h"
#include "met_e1.h"
#include "met_e2.h"
#include "met_e3.h"
#include "met_ed.h"
#include "namespace_poset.h"
#include "namespace_poset_member.h"
#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "point_block_crg_interval.h" // For initialize_prototypes.
#include "poset.h"
#include "poset_handle_factory.h"
#include "poset_member_iterator.h"
#include "postorder_iterator.h"
#include "primitives_poset.h"
#include "primitives_poset_schema.h"
#include "binary_section_space_schema_member.h"
#include "binary_section_space_schema_poset.h"
#include "schema_poset_member.h"
#include "sec_at0_space.h" // For initialize_prototypes.
#include "sec_at1_space.h" // For initialize_prototypes.
#include "sec_atp_space.h" // For initialize_prototypes.
#include "sec_jcb_space.h" // For initialize_prototypes.
#include "sec_rep_descriptor.h"
#include "sec_rep_descriptor_poset.h"
#include "sec_rep_space.h"
#include "sec_stp_space.h" // For initialize_prototypes.
#include "sec_tp_space.h" // For initialize_prototypes.
#include "sec_vd_space.h" // For initialize_prototypes.
#include "st2.h"
#include "st2_e2.h"
#include "st2_e3.h"
#include "st3.h"
#include "st3_e3.h"
#include "st4.h"
#include "st4_e2.h"
#include "st4_e3.h"
#include "std_cstring.h"
#include "std_iostream.h"
#include "std_string.h"
#include "stp.h"
#include "stp_space.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "structured_block_1d_crg_interval.h" // For initialize_prototypes.
#include "structured_block_2d_crg_interval.h" // For initialize_prototypes.
#include "structured_block_3d_crg_interval.h" // For initialize_prototypes.
#include "t2.h"
#include "t2_e2.h"
#include "t2_e3.h"
#include "t3.h"
#include "t3_e3.h"
#include "t4.h"
#include "t4_e2.h"
#include "t4_e3.h"
#include "tp.h"
#include "tp_space.h"
#include "tern.h"
#include "tuple.h"
#include "unstructured_block.h"
#include "vd.h"
#include "vd_space.h"
#include "zone_nodes_block_crg_interval.h" // For initialize_prototypes.

/// @hack force initialization of static data members:

#include "array_section_dof_map.h"
#include "sparse_section_dof_map.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// FIBER_BUNDLES_NAMESPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::fiber_bundles_namespace::
fiber_bundles_namespace()
{
  // Preconditions:

  // Body:

  _base_space_schema_poset = 0;
  _base_space_member_prototypes_poset = 0;

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

fiber_bundle::fiber_bundles_namespace::
fiber_bundles_namespace(const fiber_bundles_namespace& xother)
    : sheaves_namespace(xother)
{
  // Preconditions:

  require(precondition_of(sheaves_namespace(xother)));

  // Body:

  _base_space_schema_poset = 0;
  _base_space_member_prototypes_poset = 0;

  // Postconditions

  ensure(postcondition_of(sheaves_namespace(xother)));

  // Exit:

  return;
}

fiber_bundle::fiber_bundles_namespace::
fiber_bundles_namespace(const string& xname)
{
  // Preconditions:

  require(precondition_of(new_state(xname)));

  // Body:

  new_state(xname);

  // Initialize the prototypes.

  initialize_prototypes();

  // Postconditions:

  ensure(postcondition_of(new_state(xname)));

  // Exit:

  return;
}

fiber_bundle::fiber_bundles_namespace::
~fiber_bundles_namespace()
{
  // Preconditions:

  require(is_attached() ? state_is_read_write_accessible() : true);

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

const string&
fiber_bundle::fiber_bundles_namespace::
standard_base_space_schema_poset_name()
{

  // Preconditions:


  // Body:

  static const string result("base_space_schema");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const string&
fiber_bundle::fiber_bundles_namespace::
standard_base_space_schema_member_name()
{
  // Preconditions:

  // Body:

  static const string result("base_space_schema_member");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const string&
fiber_bundle::fiber_bundles_namespace::
standard_base_space_member_prototypes_poset_name()
{

  // Preconditions:


  // Body:

  static const string result("base_space_member_prototypes");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const string&
fiber_bundle::fiber_bundles_namespace::
standard_fiber_space_schema_poset_name()
{

  // Preconditions:


  // Body:

  static const string result("fiber_space_schema");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const string&
fiber_bundle::fiber_bundles_namespace::
standard_sec_rep_descriptor_poset_name()
{
  return sec_rep_descriptor_poset::standard_poset_name();
}

const string&
fiber_bundle::fiber_bundles_namespace::
standard_sec_rep_descriptor_schema_poset_name()
{
  return sec_rep_descriptor_poset::standard_schema_poset_name();
}

const string&
fiber_bundle::fiber_bundles_namespace::
standard_section_space_schema_schema_poset_name()
{
  return section_space_schema_poset::standard_schema_poset_name();
}

void
fiber_bundle::fiber_bundles_namespace::
initialize_prototypes()
{
  // Preconditions:

  // Body:

  static bool ldone = false;

  if(!ldone)
  {

    namespace_poset::initialize_prototypes();

    // Base space classes.

    base_space_poset ldummy1;
    point_block_crg_interval ldummy2;
    structured_block_1d_crg_interval ldummy3;
    structured_block_2d_crg_interval ldummy4;
    structured_block_3d_crg_interval ldummy5;
    zone_nodes_block_crg_interval ldummy6;

    // Section space classes

    binary_section_space_schema_poset ldummy7;
    sec_at0_space ldummy9;
    sec_at1_space ldummy10;
    sec_atp_space ldummy11;
    sec_jcb_space ldummy12;
    sec_rep_space ldummy13;
    sec_rep_descriptor_poset ldummy14;
    sec_stp_space ldummy15;
    sec_tp_space ldummy16;
    sec_tuple_space ldummy17;
    sec_vd_space ldummy18;
    
    // Fiber space classes

    at0_space ldummy20;
    at1_space ldummy21;
    atp_space ldummy22;
    gln_space ldummy23;
    jcb_space ldummy24;
    stp_space ldummy25;
    tp_space ldummy26;
    tuple_space ldummy27;
    vd_space ldummy28;

    // Dof map classes.

    //  array_sec_vd_dof_map ldummy29; Not currently in build.
    array_section_dof_map ldummy30;
    sparse_section_dof_map ldummy31;

    // Done with prototype initializations.

    ldone = true;
  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::poset&
fiber_bundle::fiber_bundles_namespace::
base_space_schema_poset()
{
  // Preconditions:

  // Body:

  poset& result = *_base_space_schema_poset;

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::poset&
fiber_bundle::fiber_bundles_namespace::
base_space_schema_poset() const
{
  // Preconditions:

  // Body:

  const poset& result = *_base_space_schema_poset;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
base_space_member_prototypes_poset()
{
  // Preconditions:

  // Body:

  base_space_poset& result = *_base_space_member_prototypes_poset;

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
base_space_member_prototypes_poset() const
{
  // Preconditions:

  // Body:

  const base_space_poset& result = *_base_space_member_prototypes_poset;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::fiber_bundles_namespace::
fiber_bundles_namespace(namespace_poset_member* xtop, namespace_poset_member* xbottom)
    :  sheaves_namespace(xtop, xbottom)
{
  // Preconditions:

  require(precondition_of(sheaves_namespace(xtop, xbottom)));

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(sheaves_namespace(xtop, xbottom)));

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// SECTION SPACE SCHEMA FACTORY METHODS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema(const poset_path& xsection_space_schema_path,
			 const poset_path& xrep_path,
			 const poset_path& xbase_space_path,
			 const poset_path& xfiber_space_path,
			 bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on xsection_space_schema_path:

  require(xsection_space_schema_path.full());
  require(path_is_auto_read_write_available<binary_section_space_schema_poset>\
	  (xsection_space_schema_path, xauto_access));

  // Conditions on xrep_path:

  require(xrep_path.full());
  require(path_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));
  
  // Conditions on xbase_space_path:

  require(xbase_space_path.full());
  require(path_is_auto_read_accessible<base_space_poset>(xbase_space_path, xauto_access));

  // Conditions on xfiber_space_path:

  require(!xfiber_space_path.empty());
  require(path_is_auto_read_accessible(xfiber_space_path, xauto_access));

  // Body:

  typedef binary_section_space_schema_poset schema_host_type;
  typedef binary_section_space_schema_member schema_mbr_type;

  // Find or create the result.
  
  poset_path result;

  if(contains_poset_member(xsection_space_schema_path, xauto_access))
  {
    // Section space schema exists; just return path arg.

    result = xsection_space_schema_path;
  }
  else if(contains_poset(xsection_space_schema_path, xauto_access))
  {
    // Section space schema poset exists but not the member; create it.

    schema_host_type& lsssp = member_poset<schema_host_type>(xsection_space_schema_path, xauto_access);

    // Create the schema member.

    lsssp.get_read_write_access();
    
    poset_path lfiber_space_schema_path = member_poset(xfiber_space_path, xauto_access).schema().path();
    
    schema_mbr_type lschema_mbr(&lsssp, xbase_space_path, lfiber_space_schema_path);
    lschema_mbr.put_name(xsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp.release_access();
  }
  else
  {
    // Section space doesn't exist; create it.  

    arg_list lsection_space_schema_args = 
	schema_host_type::make_arg_list(xrep_path, xbase_space_path, xfiber_space_path);

    // Create the schema poset.

    schema_host_type* lsssp = 
      new schema_host_type(*this,
			   xsection_space_schema_path.poset_name(),
			   lsection_space_schema_args,
			   schema_host_type::standard_schema_path(),
			   xauto_access);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lfiber_space_schema_path = member_poset(xfiber_space_path, xauto_access).schema().path();
    
    schema_mbr_type lschema_mbr(lsssp, xbase_space_path, lfiber_space_schema_path);
    lschema_mbr.put_name(xsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp->release_access();
  }

  // Postconditions:

  ensure(contains_poset_member(result, xauto_access));
  
  // Exit:

  return result;
}

// ===========================================================
// SECTION SPACE FACTORY METHODS FACET
// ===========================================================
 
fiber_bundle::sec_rep_space&
fiber_bundle::fiber_bundles_namespace::
clone_section_space(const poset_path& xsrc_space_path,
		    const poset_path& xsection_space_path,
		    const arg_list& xsection_space_args,
		    const poset_path& xsection_space_schema_path,
		    bool xauto_access)
{
  // Preconditions:

  require(path_is_auto_read_accessible<sec_rep_space>(xsrc_space_path, xauto_access));
  require(!xsection_space_path.empty());
  require(!contains_poset(xsection_space_path, xauto_access));
  /// @todo: preconditions for xsection_space_Args
  require(xsection_space_schema_path.empty() || 
	  path_is_auto_read_accessible<section_space_schema_poset>(xsection_space_schema_path, xauto_access));
    
  // Body:

  sec_rep_space& lsrc = member_poset<sec_rep_space>(xsrc_space_path, xauto_access);

  poset_path lsection_space_schema_path(xsection_space_schema_path);
  if(lsection_space_schema_path.empty())
  {
    lsection_space_schema_path = lsrc.schema().path();
  }
  
  sec_rep_space& result = *(lsrc.clone());
  result.new_state(*this, 
		   xsection_space_path.poset_name(), 
		   xsection_space_args, 
		   lsection_space_schema_path, 
		   xauto_access);

  // Postconditions:

  /// @todo Postconditions for clone_section_space.

  // Exit:

  return result;
}

// ===========================================================
// PATH COMPLETION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_path(const poset_path& xprimary_path, 
	       const poset_path& xsecondary_path, 
	       const poset_path& xdefault_path) const
{
  // Preconditions:

  require(!xdefault_path.empty());
  
  // Body:

  poset_path result;

  if(!xprimary_path.empty())
  {
    result = xprimary_path;
  }
  else if(!xsecondary_path.empty())
  {
    result = xsecondary_path;
  }
  else
  {
    result = xdefault_path;
  }

  // Postconditions:

  ensure(!result.empty());
  ensure(!xprimary_path.empty() ? result == xprimary_path : true);
  ensure(xprimary_path.empty() && !xsecondary_path.empty() ? result == xsecondary_path : true);
  ensure(xprimary_path.empty() && xsecondary_path.empty() ? result == xdefault_path : true);

  // Exit:

  return result;  

}

sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_full_path(const poset_path& xprimary_path, 
		    const poset_path& xsecondary_path, 
		    const poset_path& xdefault_path) const
{
  // Preconditions:

  // Body:

  poset_path result;

  if(xprimary_path.full())
  {
    result = xprimary_path;
  }
  else if(xsecondary_path.full())
  {
    result = xsecondary_path;
  }
  else
  {
    result = xdefault_path;
  }

  // Postconditions:

  ensure(xprimary_path.full() ? result == xprimary_path : true);
  ensure(!xprimary_path.full() && xsecondary_path.full() ? result == xsecondary_path : true);
  ensure(!xprimary_path.full() && !xsecondary_path.full() ? result == xdefault_path : true);
  ensure(result.full() == (xprimary_path.full() || xsecondary_path.full() || xdefault_path.full()));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
scalar_space_path(const poset_path& xvector_space_path, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(is_abstract_vector_space(xvector_space_path, xauto_access));
  require(path_is_auto_read_accessible(xvector_space_path, xauto_access));

  // Body:
 
  vd_space& lvector_space = reinterpret_cast<vd_space&>(member_poset(xvector_space_path, xauto_access));
  poset_path result = lvector_space.scalar_space_path(xauto_access);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
vector_space_path(const poset_path& xfiber_space_path, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(is_tensor_space(xfiber_space_path, xauto_access));
  require(path_is_auto_read_accessible(xfiber_space_path, xauto_access));
  

  // Body:

  tp_space& lfiber_space = dynamic_cast<tp_space&>(member_poset(xfiber_space_path, xauto_access));
  poset_path result = lfiber_space.vector_space_path(xauto_access);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FIBER/SECTION FACTORY METHOD PATH COMPLETION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION SCHEMA FACTORY METHOD PATH COMPLETION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path(const poset_path& xsection_space_schema_path, 
			  const poset_path& xbase_space_path, 
			  const arg_list& xsection_space_schema_args,
			  bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require((xsection_space_schema_path.full() && 
	   contains_path<section_space_schema_poset>(xsection_space_schema_path, xauto_access)) || 
	  xbase_space_path.full() || 
	  (xsection_space_schema_args.contains_arg("base_space_path") &&
	   poset_path(xsection_space_schema_args.value("base_space_path")).full()));
  

  // Body:

  typedef section_space_schema_poset schema_type;
  
  const poset_path& lsssp = xsection_space_schema_path;
  
  poset_path result;
  if(lsssp.full() && contains_path<schema_type>(lsssp, xauto_access))
  {
    binary_section_space_schema_member lmbr(*this, lsssp, xauto_access);
    result = lmbr.base_space().path(xauto_access);
    lmbr.detach_from_state();
  }
  else
  {
    poset_path largs_base_space_path;
    if(xsection_space_schema_args.contains_arg("base_space_path"))
    {
      largs_base_space_path = xsection_space_schema_args.value("base_space_path");
    } 
    result = completed_full_path(xbase_space_path, largs_base_space_path, "");
  }
  
  // Postconditions:

  ensure(result.full());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FIBER/SECTION FACTORY METHOD PATH AVAILABILITY QUERY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION SCHEMA FACTORY METHOD PATH AVAILABILITY QUERY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MISCELLANEOUS FACTORY METHOD QUERY FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::fiber_bundles_namespace::
is_scalar_space(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  // Body:

  bool result =
    contains_path(xpath, xauto_access) &&
    (dynamic_cast<at0_space*>(&member_poset(xpath, xauto_access)) != 0);

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::fiber_bundles_namespace::
is_vector_space(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  // Body:

  bool result =
    contains_path(xpath, xauto_access) &&
    (dynamic_cast<at1_space*>(&member_poset(xpath, xauto_access)) != 0);

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::fiber_bundles_namespace::
is_tensor_space(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  // Body:


  bool result =
    contains_path(xpath, xauto_access) &&
    (dynamic_cast<tp_space*>(&member_poset(xpath, xauto_access)) != 0);

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::fiber_bundles_namespace::
is_strict_tensor_space(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  // Body:

  bool result = 
    is_tensor_space(xpath, xauto_access) &&
    !is_scalar_space(xpath, xauto_access) &&
    !is_vector_space(xpath, xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::fiber_bundles_namespace::
is_jcb_space(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  // Body:


  bool result =
    contains_path(xpath, xauto_access) &&
    (dynamic_cast<jcb_space*>(&member_poset(xpath, xauto_access)) != 0);

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::fiber_bundles_namespace::
is_abstract_vector_space(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  // Body:


  bool result =
    contains_path(xpath, xauto_access) &&
    (dynamic_cast<vd_space*>(&member_poset(xpath, xauto_access)) != 0);

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::fiber_bundles_namespace::
is_strict_abstract_vector_space(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  // Body:

  bool result = 
    is_abstract_vector_space(xpath, xauto_access) &&
    !is_tensor_space(xpath, xauto_access) &&
    !is_jcb_space(xpath, xauto_access);

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::fiber_bundles_namespace::
is_gln_space(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  // Body:


  bool result =
    contains_path(xpath, xauto_access) &&
    (dynamic_cast<gln_space*>(&member_poset(xpath, xauto_access)) != 0);

  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// BASE SPACE DEFINITIONS FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::fiber_bundles_namespace::
make_base_space_definitions()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!contains_poset(standard_base_space_schema_poset_name(), false));
  require(!contains_poset(standard_base_space_member_prototypes_poset_name(), false));

  // Body:

  // Create the base space member schema.

  make_base_space_schema_poset();

  // Create base space member prototypes.

  make_base_space_member_prototypes_poset();

  // Postconditions:

  ensure(contains_poset(standard_base_space_schema_poset_name(), false));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_base_space_schema_poset()
{
  //  cout << "Entering fiber_bundles_namespace::make_base_space_schema_poset" << endl;
  
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!contains_poset(standard_base_space_schema_poset_name(), false));

  // Body:

  // Create the schema poset.

  string lname = standard_base_space_schema_poset_name();
  poset_path lschema_path = primitives().schema().path(false);
  arg_list largs = poset::make_args();

  _base_space_schema_poset =
    &new_member_poset<poset>(lname, lschema_path, largs, true);

  _base_space_schema_poset->get_read_write_access();

  subposet table_dofs(_base_space_schema_poset, 0, false);
  table_dofs.put_name(schema_poset_member::table_dof_subposet_name("top"), true, false);

  subposet row_dofs(_base_space_schema_poset, 0, false);
  row_dofs.put_name(schema_poset_member::row_dof_subposet_name("top"), true, false);

  // Make the various schema members

  make_base_space_schema_members();

  // Schematize the poset and all its members

  _base_space_schema_poset->schematize(&table_dofs, &row_dofs, true);

  // Clean up.

  table_dofs.detach_from_state();
  row_dofs.detach_from_state();
  _base_space_schema_poset->release_access();

  // Postconditions:

  ensure(contains_poset(standard_base_space_schema_poset_name(), false));

  // Exit:

  //  cout << "Leaving fiber_bundles_namespace::make_base_space_schema_poset" << endl;
  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_base_space_schema_members()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_poset(standard_base_space_schema_poset_name(), false));
  require(member_poset(standard_base_space_schema_poset_name(), false).state_is_read_write_accessible());

  // Body:

  base_space_member::make_standard_schema(*this);
  homogeneous_block::make_standard_schema(*this);
  unstructured_block::make_standard_schema(*this);
  structured_block::make_standard_schema(*this);
  structured_block_3d::make_standard_schema(*this);
  structured_block_2d::make_standard_schema(*this);
  structured_block_1d::make_standard_schema(*this);
  point_block_3d::make_standard_schema(*this);
  point_block_2d::make_standard_schema(*this);
  point_block_1d::make_standard_schema(*this);

  // Construct the standard base space schema member
  // (the join of the down set of the standard base space schema poset top).

  base_space_member lmember(_base_space_schema_poset->top(), true, false);
  lmember.put_name(standard_base_space_schema_member_name(), true, false);
  lmember.detach_from_state();

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_base_space_member_prototypes_poset()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_poset_member(base_space_member_prototype::standard_schema_path(), true));
  require(!contains_poset(standard_base_space_member_prototypes_poset_name()));

  // Body:

  // Create the prototypes poset.

  string lname = standard_base_space_member_prototypes_poset_name();
  base_space_poset* lprototypes_poset =
    &new_base_space<base_space_member_prototype>(lname, "", "", 3, true);
  lprototypes_poset->begin_jim_edit_mode(true);

  // Create the id space for cell types.

  arg_list largs = array_index_space_state::make_arg_list(0);

  lprototypes_poset->member_id_spaces(false).
    new_secondary_state("cell_types",
			"array_index_space_state",
			largs, true);

  // Create the prototypes:

  make_base_space_member_prototypes(lprototypes_poset);

  // Clean up.

  lprototypes_poset->end_jim_edit_mode(true, true);

  _base_space_member_prototypes_poset = lprototypes_poset;

  // Postconditions:

  ensure(base_space_member_prototypes_poset().is_attached());

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_base_space_member_prototypes(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  /// @issue Should the compound types be represented separately?
  /// The type_id is supposed to support the notion of alocal cell type,
  /// i.e. a particular geometric shape.
  /// The compound cell types, e.g. triangle_nodes and triangle_complex,
  /// are exactly the same type of local cell as triangle. They probably
  /// should have the same cell type id.

  // 0-cell prototypes.

  make_point_prototype(xspace);

  // 1-cell prototypes

  make_segment_prototype(xspace);
  make_segment_complex_prototype(xspace);

  // 2-cell prototypes

  make_triangle_prototype(xspace);
  make_triangle_nodes_prototype(xspace);
  make_triangle_complex_prototype(xspace);

  make_quad_prototype(xspace);
  make_quad_nodes_prototype(xspace);
  make_quad_complex_prototype(xspace);

  make_general_polygon_prototype(xspace);

  // 3-cell prototypes.

  make_tetra_prototype(xspace);
  make_tetra_nodes_prototype(xspace);
  make_tetra_complex_prototype(xspace);

  make_hex_prototype(xspace);
  make_hex_nodes_prototype(xspace);
  make_hex_faces_nodes_prototype(xspace);
  make_hex_complex_prototype(xspace);

  make_general_polyhedron_prototype(xspace);

  // Homogeneous blocks.

  make_unstructured_block_prototype(xspace);
  make_structured_block_1d_prototype(xspace);
  make_structured_block_2d_prototype(xspace);
  make_structured_block_3d_prototype(xspace);
  make_point_block_1d_prototype(xspace);
  make_point_block_2d_prototype(xspace);
  make_point_block_3d_prototype(xspace);

  // Other

  make_part_prototype(xspace);
  

  // Postconditions:


  // Exit:

  return;
}



void
fiber_bundle::fiber_bundles_namespace::
make_point_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lpt(xspace, "point", 0, "", false);

  lpt.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("point"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_segment_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lseg(xspace, "segment", 1, "", false);

  lseg.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("segment"));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_segment_complex_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("segment_complex_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("segment_complex_vertex_1", true, false);

  // Create the segment and link it to the vertices.

  base_space_member_prototype lseg(xspace, "segment_complex", 1, "", false);

  lseg.create_cover_link(&v0);
  lseg.create_cover_link(&v1);

  // Clean up.

  lseg.detach_from_state();
  v1.detach_from_state();
  v0.detach_from_state();
  lpt.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("segment_complex"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_triangle_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype ltriangle(xspace, "triangle", 2, "", false);
  ltriangle.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("triangle"));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_triangle_nodes_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("triangle_nodes_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("triangle_nodes_vertex_1", true, false);

  base_space_member_prototype v2(xspace, lpt.dof_tuple_id(false), false);
  v2.put_name("triangle_nodes_vertex_2", true, false);

  // Create the triangle and link it to the vertices.

  base_space_member_prototype ltriangle(xspace, "triangle_nodes", 2, "", false);

  ltriangle.create_cover_link(&v0);
  ltriangle.create_cover_link(&v1);
  ltriangle.create_cover_link(&v2);

  // Clean up.

  lpt.detach_from_state();

  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();

  ltriangle.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("triangle_nodes"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_triangle_complex_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("triangle_complex_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("triangle_complex_vertex_1", true, false);

  base_space_member_prototype v2(xspace, lpt.dof_tuple_id(false), false);
  v2.put_name("triangle_complex_vertex_2", true, false);

  // Create the edges and link them to the vertices.

  base_space_member_prototype lseg(xspace, "segment");

  base_space_member_prototype e0(xspace, lseg.dof_tuple_id(false), false);
  e0.put_name("triangle_complex_edge_0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  base_space_member_prototype e1(xspace, lseg.dof_tuple_id(false), false);
  e1.put_name("triangle_complex_edge_1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  base_space_member_prototype e2(xspace, lseg.dof_tuple_id(false), false);
  e2.put_name("triangle_complex_edge_2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v0);

  // Create the triangle and link it to the edges.

  base_space_member_prototype ltriangle(xspace, "triangle_complex", 2, "", false);

  ltriangle.create_cover_link(&e0);
  ltriangle.create_cover_link(&e1);
  ltriangle.create_cover_link(&e2);

  // Clean up.

  lpt.detach_from_state();
  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();

  lseg.detach_from_state();
  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();

  ltriangle.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("triangle_nodes"));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_quad_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lquad(xspace, "quad", 2, "", false);

  lquad.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("quad"));

  // Exit:

  return;
}



void
fiber_bundle::fiber_bundles_namespace::
make_quad_nodes_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("quad_nodes_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("quad_nodes_vertex_1", true, false);

  base_space_member_prototype v2(xspace, lpt.dof_tuple_id(false), false);
  v2.put_name("quad_nodes_vertex_2", true, false);

  base_space_member_prototype v3(xspace, lpt.dof_tuple_id(false), false);
  v3.put_name("quad_nodes_vertex_3", true, false);

  // Create the quad and link it to the vertices.

  base_space_member_prototype lquad(xspace, "quad_nodes", 2, "", false);

  lquad.create_cover_link(&v0);
  lquad.create_cover_link(&v1);
  lquad.create_cover_link(&v2);
  lquad.create_cover_link(&v3);

  // Clean up.


  lpt.detach_from_state();
  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();

  lquad.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("quad_nodes"));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_quad_complex_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("quad_complex_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("quad_complex_vertex_1", true, false);

  base_space_member_prototype v2(xspace, lpt.dof_tuple_id(false), false);
  v2.put_name("quad_complex_vertex_2", true, false);

  base_space_member_prototype v3(xspace, lpt.dof_tuple_id(false), false);
  v3.put_name("quad_complex_vertex_3", true, false);

  // Create the edges and link them to the vertices.

  base_space_member_prototype lseg(xspace, "segment");

  base_space_member_prototype e0(xspace, lseg.dof_tuple_id(false), false);
  e0.put_name("quad_complex_edge_0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  base_space_member_prototype e1(xspace, lseg.dof_tuple_id(false), false);
  e1.put_name("quad_complex_edge_1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  base_space_member_prototype e2(xspace, lseg.dof_tuple_id(false), false);
  e2.put_name("quad_complex_edge_2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v3);

  base_space_member_prototype e3(xspace, lseg.dof_tuple_id(false), false);
  e3.put_name("quad_complex_edge_3", true, false);
  e3.create_cover_link(&v3);
  e3.create_cover_link(&v0);

  // Create the quad and link it to the edges.

  base_space_member_prototype lquad(xspace, "quad_complex", 2, "", false);

  lquad.create_cover_link(&e0);
  lquad.create_cover_link(&e1);
  lquad.create_cover_link(&e2);
  lquad.create_cover_link(&e3);

  // Clean up.

  lpt.detach_from_state();
  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();

  lseg.detach_from_state();
  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();
  e3.detach_from_state();

  lquad.detach_from_state();


  // Postconditions:

  ensure(xspace->contains_member("quad_complex"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_general_polygon_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lpoly(xspace, "general_polygon", 2, "", false);
  lpoly.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("general_polygon"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_tetra_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype ltetra(xspace, "tetra", 3, "", false);
  ltetra.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("tetra"));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_tetra_nodes_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("tetra_nodes_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("tetra_nodes_vertex_1", true, false);

  base_space_member_prototype v2(xspace, lpt.dof_tuple_id(false), false);
  v2.put_name("tetra_nodes_vertex_2", true, false);

  base_space_member_prototype v3(xspace, lpt.dof_tuple_id(false), false);
  v3.put_name("tetra_nodes_vertex_3", true, false);

  // Create the tet and link it to the vertices.

  base_space_member_prototype ltetra(xspace, "tetra_nodes", 3, "", false);

  ltetra.create_cover_link(&v0);
  ltetra.create_cover_link(&v1);
  ltetra.create_cover_link(&v2);
  ltetra.create_cover_link(&v3);

  // Clean up.

  lpt.detach_from_state();
  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();

  ltetra.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("tetra_nodes"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_tetra_complex_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("tetra_complex_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("tetra_complex_vertex_1", true, false);

  base_space_member_prototype v2(xspace, lpt.dof_tuple_id(false), false);
  v2.put_name("tetra_complex_vertex_2", true, false);

  base_space_member_prototype v3(xspace, lpt.dof_tuple_id(false), false);
  v3.put_name("tetra_complex_vertex_3", true, false);

  // Create the edges and link thm to the vertices.

  base_space_member_prototype lseg(xspace, "segment");

  base_space_member_prototype e0(xspace, lseg.dof_tuple_id(false), false);
  e0.put_name("tetra_complex_edge_0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  base_space_member_prototype e1(xspace, lseg.dof_tuple_id(false), false);
  e1.put_name("tetra_complex_edge_1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  base_space_member_prototype e2(xspace, lseg.dof_tuple_id(false), false);
  e2.put_name("tetra_complex_edge_2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v0);

  base_space_member_prototype e3(xspace, lseg.dof_tuple_id(false), false);
  e3.put_name("tetra_complex_edge_3", true, false);
  e3.create_cover_link(&v2);
  e3.create_cover_link(&v3);

  base_space_member_prototype e4(xspace, lseg.dof_tuple_id(false), false);
  e4.put_name("tetra_complex_edge_4", true, false);
  e4.create_cover_link(&v3);
  e4.create_cover_link(&v1);

  base_space_member_prototype e5(xspace, lseg.dof_tuple_id(false), false);
  e5.put_name("tetra_complex_edge_5", true, false);
  e5.create_cover_link(&v3);
  e5.create_cover_link(&v0);

  // Create the faces and link them to the edges.

  base_space_member_prototype lface(xspace, "triangle");

  base_space_member_prototype f0(xspace, lface.dof_tuple_id(false), false);
  f0.put_name("tetra_complex_face_0", true, false);
  f0.create_cover_link(&e0);
  f0.create_cover_link(&e1);
  f0.create_cover_link(&e2);

  base_space_member_prototype f1(xspace, lface.dof_tuple_id(false), false);
  f1.put_name("tetra_complex_face_1", true, false);
  f1.create_cover_link(&e2);
  f1.create_cover_link(&e3);
  f1.create_cover_link(&e5);

  base_space_member_prototype f2(xspace, lface.dof_tuple_id(false), false);
  f2.put_name("tetra_complex_face_2", true, false);
  f2.create_cover_link(&e5);
  f2.create_cover_link(&e4);
  f2.create_cover_link(&e0);

  base_space_member_prototype f3(xspace, lface.dof_tuple_id(false), false);
  f3.put_name("tetra_complex_face_3", true, false);
  f3.create_cover_link(&e1);
  f3.create_cover_link(&e3);
  f3.create_cover_link(&e4);

  // Create the tet and link it to the faces.

  base_space_member_prototype ltetra(xspace, "tetra_complex", 3, "", false);

  ltetra.create_cover_link(&f0);
  ltetra.create_cover_link(&f1);
  ltetra.create_cover_link(&f2);
  ltetra.create_cover_link(&f3);

  // Clean up.

  lpt.detach_from_state();
  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();

  lseg.detach_from_state();
  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();
  e3.detach_from_state();
  e4.detach_from_state();
  e5.detach_from_state();

  lface.detach_from_state();
  f0.detach_from_state();
  f1.detach_from_state();
  f2.detach_from_state();
  f3.detach_from_state();

  ltetra.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("tetra_complex"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_hex_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lhex(xspace, "hex", 3, "", false);
  lhex.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("hex"));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_hex_nodes_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("hex_nodes_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("hex_nodes_vertex_1", true, false);

  base_space_member_prototype v2(xspace, lpt.dof_tuple_id(false), false);
  v2.put_name("hex_nodes_vertex_2", true, false);

  base_space_member_prototype v3(xspace, lpt.dof_tuple_id(false), false);
  v3.put_name("hex_nodes_vertex_3", true, false);

  base_space_member_prototype v4(xspace, lpt.dof_tuple_id(false), false);
  v4.put_name("hex_nodes_vertex_4", true, false);

  base_space_member_prototype v5(xspace, lpt.dof_tuple_id(false), false);
  v5.put_name("hex_nodes_vertex_5", true, false);

  base_space_member_prototype v6(xspace, lpt.dof_tuple_id(false), false);
  v6.put_name("hex_nodes_vertex_6", true, false);

  base_space_member_prototype v7(xspace, lpt.dof_tuple_id(false), false);
  v7.put_name("hex_nodes_vertex_7", true, false);

  // Create the hex and link it to the vertices

  base_space_member_prototype lhex(xspace, "hex_nodes", 3, "", false);

  lhex.create_cover_link(&v0);
  lhex.create_cover_link(&v1);
  lhex.create_cover_link(&v2);
  lhex.create_cover_link(&v3);
  lhex.create_cover_link(&v4);
  lhex.create_cover_link(&v5);
  lhex.create_cover_link(&v6);
  lhex.create_cover_link(&v7);

  // Clean up.

  lpt.detach_from_state();
  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();
  v4.detach_from_state();
  v5.detach_from_state();
  v6.detach_from_state();
  v7.detach_from_state();

  lhex.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("hex_nodes"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_hex_faces_nodes_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("hex_faces_nodes_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("hex_faces_nodes_vertex_1", true, false);

  base_space_member_prototype v2(xspace, lpt.dof_tuple_id(false), false);
  v2.put_name("hex_faces_nodes_vertex_2", true, false);

  base_space_member_prototype v3(xspace, lpt.dof_tuple_id(false), false);
  v3.put_name("hex_faces_nodes_vertex_3", true, false);

  base_space_member_prototype v4(xspace, lpt.dof_tuple_id(false), false);
  v4.put_name("hex_faces_nodes_vertex_4", true, false);

  base_space_member_prototype v5(xspace, lpt.dof_tuple_id(false), false);
  v5.put_name("hex_faces_nodes_vertex_5", true, false);

  base_space_member_prototype v6(xspace, lpt.dof_tuple_id(false), false);
  v6.put_name("hex_faces_nodes_vertex_6", true, false);

  base_space_member_prototype v7(xspace, lpt.dof_tuple_id(false), false);
  v7.put_name("hex_faces_nodes_vertex_7", true, false);

  // Create the faces and link them to the vertices.

  base_space_member_prototype lface(xspace, "quad");

  base_space_member_prototype f0(xspace, lface.dof_tuple_id(false), false);
  f0.put_name("hex_faces_nodes_face_0", true, false);

  f0.create_cover_link(&v0);
  f0.create_cover_link(&v1);
  f0.create_cover_link(&v2);
  f0.create_cover_link(&v3);


  base_space_member_prototype f1(xspace, lface.dof_tuple_id(false), false);
  f1.put_name("hex_faces_nodes_face_1", true, false);

  f1.create_cover_link(&v4);
  f1.create_cover_link(&v5);
  f1.create_cover_link(&v6);
  f1.create_cover_link(&v7);

  base_space_member_prototype f2(xspace, lface.dof_tuple_id(false), false);
  f2.put_name("hex_faces_nodes_face_2", true, false);

  f2.create_cover_link(&v1);
  f2.create_cover_link(&v5);
  f2.create_cover_link(&v6);
  f2.create_cover_link(&v2);

  base_space_member_prototype f3(xspace, lface.dof_tuple_id(false), false);
  f3.put_name("hex_faces_nodes_face_3", true, false);

  f3.create_cover_link(&v0);
  f3.create_cover_link(&v4);
  f3.create_cover_link(&v7);
  f3.create_cover_link(&v3);

  base_space_member_prototype f4(xspace, lface.dof_tuple_id(false), false);
  f4.put_name("hex_faces_nodes_face_4", true, false);

  f4.create_cover_link(&v0);
  f4.create_cover_link(&v1);
  f4.create_cover_link(&v5);
  f4.create_cover_link(&v4);

  base_space_member_prototype f5(xspace, lface.dof_tuple_id(false), false);
  f5.put_name("hex_faces_nodes_face_5", true, false);

  f5.create_cover_link(&v3);
  f5.create_cover_link(&v2);
  f5.create_cover_link(&v6);
  f5.create_cover_link(&v7);

  // Create the hex and link it to the faces.

  base_space_member_prototype lhex(xspace, "hex_faces_nodes", 3, "", false);

  lhex.create_cover_link(&f0);
  lhex.create_cover_link(&f1);
  lhex.create_cover_link(&f2);
  lhex.create_cover_link(&f3);
  lhex.create_cover_link(&f4);
  lhex.create_cover_link(&f5);


  // Clean up.

  lpt.detach_from_state();
  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();
  v4.detach_from_state();
  v5.detach_from_state();
  v6.detach_from_state();
  v7.detach_from_state();

  lface.detach_from_state();
  f0.detach_from_state();
  f1.detach_from_state();
  f2.detach_from_state();
  f3.detach_from_state();
  f4.detach_from_state();
  f5.detach_from_state();

  lhex.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("hex_faces_nodes"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_hex_complex_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  // Create the vertices.

  base_space_member_prototype lpt(xspace, "point");

  base_space_member_prototype v0(xspace, lpt.dof_tuple_id(false), false);
  v0.put_name("hex_complex_vertex_0", true, false);

  base_space_member_prototype v1(xspace, lpt.dof_tuple_id(false), false);
  v1.put_name("hex_complex_vertex_1", true, false);

  base_space_member_prototype v2(xspace, lpt.dof_tuple_id(false), false);
  v2.put_name("hex_complex_vertex_2", true, false);

  base_space_member_prototype v3(xspace, lpt.dof_tuple_id(false), false);
  v3.put_name("hex_complex_vertex_3", true, false);

  base_space_member_prototype v4(xspace, lpt.dof_tuple_id(false), false);
  v4.put_name("hex_complex_vertex_4", true, false);

  base_space_member_prototype v5(xspace, lpt.dof_tuple_id(false), false);
  v5.put_name("hex_complex_vertex_5", true, false);

  base_space_member_prototype v6(xspace, lpt.dof_tuple_id(false), false);
  v6.put_name("hex_complex_vertex_6", true, false);

  base_space_member_prototype v7(xspace, lpt.dof_tuple_id(false), false);
  v7.put_name("hex_complex_vertex_7", true, false);

  // Create the edges and link them to the vertices.

  base_space_member_prototype lseg(xspace, "segment");

  base_space_member_prototype e0(xspace, lseg.dof_tuple_id(false), false);
  e0.put_name("hex_complex_edge_0", true, false);
  e0.create_cover_link(&v0);
  e0.create_cover_link(&v1);

  base_space_member_prototype e1(xspace, lseg.dof_tuple_id(false), false);
  e1.put_name("hex_complex_edge_1", true, false);
  e1.create_cover_link(&v1);
  e1.create_cover_link(&v2);

  base_space_member_prototype e2(xspace, lseg.dof_tuple_id(false), false);
  e2.put_name("hex_complex_edge_2", true, false);
  e2.create_cover_link(&v2);
  e2.create_cover_link(&v3);

  base_space_member_prototype e3(xspace, lseg.dof_tuple_id(false), false);
  e3.put_name("hex_complex_edge_3", true, false);
  e3.create_cover_link(&v3);
  e3.create_cover_link(&v0);

  base_space_member_prototype e4(xspace, lseg.dof_tuple_id(false), false);
  e4.put_name("hex_complex_edge_4", true, false);
  e4.create_cover_link(&v4);
  e4.create_cover_link(&v5);

  base_space_member_prototype e5(xspace, lseg.dof_tuple_id(false), false);
  e5.put_name("hex_complex_edge_5", true, false);
  e5.create_cover_link(&v5);
  e5.create_cover_link(&v6);

  base_space_member_prototype e6(xspace, lseg.dof_tuple_id(false), false);
  e6.put_name("hex_complex_edge_6", true, false);
  e6.create_cover_link(&v6);
  e6.create_cover_link(&v7);

  base_space_member_prototype e7(xspace, lseg.dof_tuple_id(false), false);
  e7.put_name("hex_complex_edge_7", true, false);
  e7.create_cover_link(&v7);
  e7.create_cover_link(&v4);

  base_space_member_prototype e8(xspace, lseg.dof_tuple_id(false), false);
  e8.put_name("hex_complex_edge_8", true, false);
  e8.create_cover_link(&v3);
  e8.create_cover_link(&v7);

  base_space_member_prototype e9(xspace, lseg.dof_tuple_id(false), false);
  e9.put_name("hex_complex_edge_9", true, false);
  e9.create_cover_link(&v2);
  e9.create_cover_link(&v6);

  base_space_member_prototype e10(xspace, lseg.dof_tuple_id(false), false);
  e10.put_name("hex_complex_edge_10", true, false);
  e10.create_cover_link(&v1);
  e10.create_cover_link(&v5);

  base_space_member_prototype e11(xspace, lseg.dof_tuple_id(false), false);
  e11.put_name("hex_complex_edge_11", true, false);
  e11.create_cover_link(&v0);
  e11.create_cover_link(&v4);

  // Create the faces and link them to the edges.

  base_space_member_prototype lface(xspace, "quad_complex");

  base_space_member_prototype f0(xspace, lface.dof_tuple_id(false), false);
  f0.put_name("hex_complex_face_0", true, false);
  f0.create_cover_link(&e0);
  f0.create_cover_link(&e1);
  f0.create_cover_link(&e2);
  f0.create_cover_link(&e3);

  base_space_member_prototype f1(xspace, lface.dof_tuple_id(false), false);
  f1.put_name("hex_complex_face_1", true, false);
  f1.create_cover_link(&e4);
  f1.create_cover_link(&e5);
  f1.create_cover_link(&e6);
  f1.create_cover_link(&e7);

  base_space_member_prototype f2(xspace, lface.dof_tuple_id(false), false);
  f2.put_name("hex_complex_face_2", true, false);
  f2.create_cover_link(&e10);
  f2.create_cover_link(&e5);
  f2.create_cover_link(&e9);
  f2.create_cover_link(&e1);

  base_space_member_prototype f3(xspace, lface.dof_tuple_id(false), false);
  f3.put_name("hex_complex_face_3", true, false);
  f3.create_cover_link(&e11);
  f3.create_cover_link(&e7);
  f3.create_cover_link(&e8);
  f3.create_cover_link(&e3);

  base_space_member_prototype f4(xspace, lface.dof_tuple_id(false), false);
  f4.put_name("hex_complex_face_4", true, false);
  f4.create_cover_link(&e0);
  f4.create_cover_link(&e10);
  f4.create_cover_link(&e4);
  f4.create_cover_link(&e11);

  base_space_member_prototype f5(xspace, lface.dof_tuple_id(false), false);
  f5.put_name("hex_complex_face_5", true, false);
  f5.create_cover_link(&e2);
  f5.create_cover_link(&e9);
  f5.create_cover_link(&e6);
  f5.create_cover_link(&e8);

  // Create the hex and link it to the faces.

  base_space_member_prototype lhex(xspace, "hex_complex", 3, "", false);

  lhex.create_cover_link(&f0);
  lhex.create_cover_link(&f1);
  lhex.create_cover_link(&f2);
  lhex.create_cover_link(&f3);
  lhex.create_cover_link(&f4);
  lhex.create_cover_link(&f5);


  // Clean up.

  lpt.detach_from_state();
  v0.detach_from_state();
  v1.detach_from_state();
  v2.detach_from_state();
  v3.detach_from_state();
  v4.detach_from_state();
  v5.detach_from_state();
  v6.detach_from_state();
  v7.detach_from_state();

  lseg.detach_from_state();
  e0.detach_from_state();
  e1.detach_from_state();
  e2.detach_from_state();
  e3.detach_from_state();
  e4.detach_from_state();
  e5.detach_from_state();
  e6.detach_from_state();
  e7.detach_from_state();
  e8.detach_from_state();
  e9.detach_from_state();
  e10.detach_from_state();
  e11.detach_from_state();

  lface.detach_from_state();
  f0.detach_from_state();
  f1.detach_from_state();
  f2.detach_from_state();
  f3.detach_from_state();
  f4.detach_from_state();
  f5.detach_from_state();

  lhex.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("hex_complex"));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_general_polyhedron_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lpoly(xspace, "general_polyhedron", 3, "", false);
  lpoly.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("general_polyhedron"));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_unstructured_block_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  string lproto_name(unstructured_block::static_prototype_path().member_name());

  base_space_member_prototype lblk(xspace, lproto_name, 0, "", false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member(unstructured_block::static_prototype_path().member_name()));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_structured_block_1d_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  string lproto_name(structured_block_1d::static_prototype_path().member_name());
  string lcell_name(structured_block_1d::static_local_cell_prototype_path().member_name());

  base_space_member_prototype lblk(xspace, lproto_name, 1, lcell_name, false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member(structured_block_1d::static_prototype_path().member_name()));

  // Exit:

  return;
}


void
fiber_bundle::fiber_bundles_namespace::
make_structured_block_2d_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  string lproto_name(structured_block_2d::static_prototype_path().member_name());
  string lcell_name(structured_block_2d::static_local_cell_prototype_path().member_name());

  base_space_member_prototype lblk(xspace, lproto_name, 2, lcell_name, false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member(structured_block_2d::static_prototype_path().member_name()));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_structured_block_3d_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  string lproto_name(structured_block_3d::static_prototype_path().member_name());
  string lcell_name(structured_block_3d::static_local_cell_prototype_path().member_name());

  base_space_member_prototype lblk(xspace, lproto_name, 3, lcell_name, false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member(structured_block_3d::static_prototype_path().member_name()));

  // Exit:

  return;
}



void
fiber_bundle::fiber_bundles_namespace::
make_point_block_1d_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  string lproto_name(point_block_1d::static_prototype_path().member_name());
  string lcell_name(point_block_1d::static_local_cell_prototype_path().member_name());

  base_space_member_prototype lblk(xspace, lproto_name, 0, lcell_name, false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member(point_block_1d::static_prototype_path().member_name()));

  // Exit:

  return;
}



void
fiber_bundle::fiber_bundles_namespace::
make_point_block_2d_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  string lproto_name(point_block_2d::static_prototype_path().member_name());
  string lcell_name(point_block_2d::static_local_cell_prototype_path().member_name());

  base_space_member_prototype lblk(xspace, lproto_name, 0, lcell_name, false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member(point_block_2d::static_prototype_path().member_name()));

  // Exit:

  return;
}



void
fiber_bundle::fiber_bundles_namespace::
make_point_block_3d_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  string lproto_name(point_block_3d::static_prototype_path().member_name());
  string lcell_name(point_block_3d::static_local_cell_prototype_path().member_name());

  base_space_member_prototype lblk(xspace, lproto_name, 0, lcell_name, false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member(point_block_3d::static_prototype_path().member_name()));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_part_prototype(base_space_poset* xspace)
{
  // Preconditions:

  require(xspace != 0);
  require(xspace->in_jim_edit_mode());

  // Body:

  base_space_member_prototype lblk(xspace, "part", 0, "", false);
  lblk.detach_from_state();

  // Postconditions:

  ensure(xspace->contains_member("part"));

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FIBER SPACE DEFINITIONS FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::fiber_bundles_namespace::
make_fiber_space_definitions()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!contains_poset(standard_fiber_space_schema_poset_name(), false));

  // Body:

  make_fiber_space_schema_poset();
  make_fiber_spaces();

  // Postconditions:

  ensure(contains_poset(standard_fiber_space_schema_poset_name(), false));

  // Exit:

  return;
}
void
fiber_bundle::fiber_bundles_namespace::
make_fiber_space_schema_poset()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!contains_poset(standard_fiber_space_schema_poset_name(), false));

  // Body:

  string lname = standard_fiber_space_schema_poset_name();
  poset_path lschema_path = primitives().schema().path(false);
  arg_list largs = poset::make_args();

  poset* lfiber_space_schema_poset =
    &new_member_poset<poset>(lname, lschema_path, largs, true);
  lfiber_space_schema_poset->get_read_write_access();

  subposet table_dofs(lfiber_space_schema_poset);
  table_dofs.put_name(schema_poset_member::table_dof_subposet_name("top"), true, false);

  subposet row_dofs(lfiber_space_schema_poset);
  row_dofs.put_name(schema_poset_member::row_dof_subposet_name("top"), true, false);

  // Make the various schema members.

  make_fiber_space_schema_members();

  // Schematize the poset and all its members

  lfiber_space_schema_poset->schematize(&table_dofs, &row_dofs, true);

  table_dofs.detach_from_state();
  row_dofs.detach_from_state();

  // Make some useful groupings:
  // First, make a block and the id of the base type for each group.
  // Put pointers to the type blocks into a block indexed by mbr id.

  block< block<scoped_index>* >
  ltype_blocks(lfiber_space_schema_poset->member_index_ub().pod());

  ltype_blocks.set_ct(ltype_blocks.ub());
  ltype_blocks.assign(0);

  // Scalar types.

  block<scoped_index> lat0_types(32);

  pod_index_type lat0_id =
    lfiber_space_schema_poset->member_id(at0::standard_schema_path().member_name(), false);

  ltype_blocks[lat0_id] = &lat0_types;

  // Vector types.

  block<scoped_index> lat1_types(32);

  pod_index_type lat1_id =
    lfiber_space_schema_poset->member_id(at1::standard_schema_path().member_name(), false);

  ltype_blocks[lat1_id] = &lat1_types;

  // Metric tensor types.

  block<scoped_index> lmet_types(32);

  pod_index_type lmet_id =
    lfiber_space_schema_poset->member_id(met::standard_schema_path().member_name(), false);

  ltype_blocks[lmet_id] = &lmet_types;

  // Symmetric tensor types.

  block<scoped_index> lstp_types(32);

  pod_index_type lstp_id =
    lfiber_space_schema_poset->member_id(stp::standard_schema_path().member_name(), false);

  ltype_blocks[lstp_id] = &lstp_types;

  // Antisymmetric tensor types.

  block<scoped_index> latp_types(32);

  pod_index_type latp_id =
    lfiber_space_schema_poset->member_id(atp::standard_schema_path().member_name(), false);

  ltype_blocks[latp_id] = &latp_types;

  // General tensor types.

  block<scoped_index> ltp_types(32);

  pod_index_type ltp_id =
    lfiber_space_schema_poset->member_id(tp::standard_schema_path().member_name(), false);

  ltype_blocks[ltp_id] = &ltp_types;

  // Linear transformation types.

  block<scoped_index> lgln_types(32);

  pod_index_type lgln_id =
    lfiber_space_schema_poset->member_id(gln::standard_schema_path().member_name(), false);

  ltype_blocks[lgln_id] = &lgln_types;

  // Jacobian types.

  block<scoped_index> ljcb_types(32);

  pod_index_type ljcb_id =
    lfiber_space_schema_poset->member_id(jcb::standard_schema_path().member_name(), false);

  ltype_blocks[ljcb_id] = &ljcb_types;

  // Other types.

  block<scoped_index> lbot_types(32);

  pod_index_type lbot_id = BOTTOM_INDEX;
  ltype_blocks[lbot_id] = &lbot_types;

  stack<block<scoped_index>*> ltype_block_stack;
  ltype_block_stack.push(&lbot_types);

  // Iterate up from the bottom in postorder, sorting the members
  // into groups. This places each member in the group of its
  // greatest lower bound within the set of base types. (Note that
  // inheritance points down the CRG.)

  biorder_iterator lmbr_itr(lfiber_space_schema_poset->bottom(), "jims", UP, NOT_STRICT);
  while(!lmbr_itr.is_done())
  {
    const scoped_index& lmbr_id = lmbr_itr.index();

    switch(lmbr_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      if(ltype_blocks[lmbr_id.pod()] != 0)
      {
        // This member is the base type of a group.
        // Push its block onto the stack so we begin
        // collecting the members of the group.

        ltype_block_stack.push(ltype_blocks[lmbr_id.pod()]);
      }
      break;
    case biorder_iterator::POSTVISIT_ACTION:

      if(!lfiber_space_schema_poset->is_atom(lmbr_id))
      {
        // Put the current member in the current group.

        ltype_block_stack.top()->push_back(lmbr_id);
      }


      if(ltype_blocks[lmbr_id.pod()] == ltype_block_stack.top())
      {
        // This member is the base type of a group
        // and we are about to leave its scope.
        // Pop the stack and return to collecting members
        // of the next most inclusive group.

        ltype_block_stack.pop();
      }
      break;
    }
    lmbr_itr.next();
  }

  // Now create the groups as members (jrms) and subposets.
  // This organization is mostly for display in the SheafScope.
  // The jrms organize the row graph while the subposets provide
  // useful filters for displaying a "flat" view in the table.

  // Scalar types.

  schema_poset_member lscalar_group(lfiber_space_schema_poset,
                                    lat0_types.base(),
                                    lat0_types.ct(),
                                    tern::TRUE,
                                    false);
  lscalar_group.put_name("scalars", true, false);
  lscalar_group.detach_from_state();

  subposet lat0_sp(lfiber_space_schema_poset, lat0_types, false);
  lat0_sp.put_name("scalars", true, false);
  lat0_sp.detach_from_state();

  // Vector types.

  schema_poset_member lvector_group(lfiber_space_schema_poset,
                                    lat1_types.base(),
                                    lat1_types.ct(),
                                    tern::TRUE,
                                    false);
  lvector_group.put_name("vectors", true, false);
  lvector_group.detach_from_state();

  subposet lat1_sp(lfiber_space_schema_poset, lat1_types, false);
  lat1_sp.put_name("vectors", true, false);
  lat1_sp.detach_from_state();

  // General tensor types

  schema_poset_member ltensor_group(lfiber_space_schema_poset,
                                    ltp_types.base(),
                                    ltp_types.ct(),
                                    tern::TRUE,
                                    false);
  ltensor_group.put_name("general_tensors", true, false);
  ltensor_group.detach_from_state();

  subposet ltp_sp(lfiber_space_schema_poset, ltp_types, false);
  ltp_sp.put_name("general_tensors", true, false);
  ltp_sp.detach_from_state();

  // Metric types

  schema_poset_member lmetric_group(lfiber_space_schema_poset,
                                    lmet_types.base(),
                                    lmet_types.ct(),
                                    tern::TRUE,
                                    false);
  lmetric_group.put_name("metric_tensors", true, false);
  lstp_types.push_back(lmetric_group.index());
  lmetric_group.detach_from_state();

  subposet lmet_sp(lfiber_space_schema_poset, lmet_types, false);
  lmet_sp.put_name("metric_tensors", true, false);
  lmet_sp.detach_from_state();

  // Symmetric tensor types

  schema_poset_member lsym_group(lfiber_space_schema_poset,
                                 lstp_types.base(),
                                 lstp_types.ct(),
                                 tern::TRUE,
                                 false);
  lsym_group.put_name("symmetric_tensors", true, false);
  lsym_group.detach_from_state();

  subposet lstp_sp(lfiber_space_schema_poset, lstp_types, false);
  lstp_sp.put_name("symmetric_tensors", true, false);
  lstp_sp.detach_from_state();

  // Antisymmetric tensor types

  schema_poset_member lantisym_group(lfiber_space_schema_poset,
                                     latp_types.base(),
                                     latp_types.ct(),
                                     tern::TRUE,
                                     false);
  lantisym_group.put_name("antisymmetric_tensors", true, false);
  lantisym_group.detach_from_state();

  subposet latp_sp(lfiber_space_schema_poset, latp_types, false);
  latp_sp.put_name("antisymmetric_tensors", true, false);
  latp_sp.detach_from_state();

  // Jacobian types

  schema_poset_member ljcb_group(lfiber_space_schema_poset,
                                 ljcb_types.base(),
                                 ljcb_types.ct(),
                                 tern::TRUE,
                                 false);
  ljcb_group.put_name("Jacobians", true, false);

  lgln_types.push_back(ljcb_group.index());
  ljcb_group.detach_from_state();

  subposet ljcb_sp(lfiber_space_schema_poset, ljcb_types, false);
  ljcb_sp.put_name("Jacobians", true, false);
  ljcb_sp.detach_from_state();

  // Linear transformation types

  schema_poset_member lgln_group(lfiber_space_schema_poset,
                                 lgln_types.base(),
                                 lgln_types.ct(),
                                 tern::TRUE,
                                 false);
  lgln_group.put_name("linear_transformations", true, false);
  lgln_group.detach_from_state();

  subposet lgln_sp(lfiber_space_schema_poset, lgln_types, false);
  lgln_sp.put_name("linear_transformations", true, false);
  lgln_sp.detach_from_state();

  // Other types

  schema_poset_member lother_group(lfiber_space_schema_poset,
                                   lbot_types.base(),
                                   lbot_types.ct(),
                                   tern::TRUE,
                                   false);
  lother_group.put_name("other_types", true, false);
  lother_group.detach_from_state();

  subposet lbot_sp(lfiber_space_schema_poset, lbot_types, false);
  lbot_sp.put_name("other_types", true, false);
  lbot_sp.detach_from_state();


  // Now identify the concrete types and put them in a subposet.
  /// @hack assume any type with row dofs is concrete.
  /// this is currently true, but there's no reason it has to be.

  subposet lconcrete_sp(lfiber_space_schema_poset);
  lconcrete_sp.put_name("concrete_types", true, false);

  subposet lrow_dof_sp(lfiber_space_schema_poset,
                       schema_poset_member::row_dof_subposet_name("top"));
  stack<int> lrow_dof_ct;
  lrow_dof_ct.push(0); // So the stack is never empty.

  biorder_iterator lc_itr(lfiber_space_schema_poset->top(), "jims", DOWN, NOT_STRICT);
  while(!lc_itr.is_done())
  {
    const scoped_index& lmbr_id = lc_itr.index();

    switch(lc_itr.action())
    {
    case biorder_iterator::PREVISIT_ACTION:
      if(!lrow_dof_sp.contains_member(lmbr_id))
      {
        // This member is not a rof dof;
        // start a counter.

        lrow_dof_ct.push(0);
      }
      break;
    case biorder_iterator::POSTVISIT_ACTION:

      if(lrow_dof_sp.contains_member(lmbr_id))
      {
        // This member is a row dof;
        // increment the row dof counter.

        ++lrow_dof_ct.top();

        // We want to be able to visit this dof again,
        // if it appears in the down set of another type.
        // So unmark it.

        lc_itr.put_has_visited(lmbr_id, false);
      }
      else
      {
        // This member is not a row dof.

        int lct = lrow_dof_ct.top();
        if(lct > 0)
        {
          // This member is a concrete type.

          lconcrete_sp.insert_member(lmbr_id);
        }

        // Any row dofs of this member accumulate to
        // its superiors.

        lrow_dof_ct.pop();
        lrow_dof_ct.top() += lct;
      }
      break;
    }
    lc_itr.next();
  }

  lrow_dof_sp.detach_from_state();
  lconcrete_sp.detach_from_state();

  // Finished.

  lfiber_space_schema_poset->release_access();

  // Postconditions:

  ensure(contains_poset(standard_fiber_space_schema_poset_name(), false));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_fiber_space_schema_members()
{
  // Preconditions:

  require(contains_poset(standard_fiber_space_schema_poset_name(), false));
  require(state_is_read_write_accessible());

  // Body:

  tuple::make_standard_schema(*this);
  vd::make_standard_schema(*this);
  tp::make_standard_schema(*this);
  t2::make_standard_schema(*this);
  t2_e3::make_standard_schema(*this);
  t2_e2::make_standard_schema(*this);
  t3::make_standard_schema(*this);
  t3_e3::make_standard_schema(*this);
  t4::make_standard_schema(*this);
  t4_e2::make_standard_schema(*this);
  t4_e3::make_standard_schema(*this);
  atp::make_standard_schema(*this);
  at0::make_standard_schema(*this);
  at1::make_standard_schema(*this);
  ed::make_standard_schema(*this);
  e4::make_standard_schema(*this);
  e3::make_standard_schema(*this);
  e2::make_standard_schema(*this);
  e1::make_standard_schema(*this);
  at2::make_standard_schema(*this);
  at2_e2::make_standard_schema(*this);
  at2_e3::make_standard_schema(*this);
  at3::make_standard_schema(*this);
  at3_e3::make_standard_schema(*this);
  stp::make_standard_schema(*this);
  st2::make_standard_schema(*this);
  st2_e2::make_standard_schema(*this);
  st2_e3::make_standard_schema(*this);
  st3::make_standard_schema(*this);
  st3_e3::make_standard_schema(*this);
  st4::make_standard_schema(*this);
  st4_e2::make_standard_schema(*this);
  st4_e3::make_standard_schema(*this);
  gln::make_standard_schema(*this);
  gl3::make_standard_schema(*this);
  gl2::make_standard_schema(*this);
  jcb::make_standard_schema(*this);
  jcb_ed::make_standard_schema(*this);
  jcb_e33::make_standard_schema(*this);
  jcb_e23::make_standard_schema(*this);
  jcb_e13::make_standard_schema(*this);
  met::make_standard_schema(*this);
  met_ed::make_standard_schema(*this);
  met_e3::make_standard_schema(*this);
  met_e2::make_standard_schema(*this);
  met_e1::make_standard_schema(*this);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_fiber_spaces()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  // Nothing to do in this classes;
  // intended for redefinition in descendants.

  // Postconditions:


  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION SPACE DEFINITIONS FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::fiber_bundles_namespace::
make_section_space_definitions()
{

  // Preconditions:

  require(state_is_read_write_accessible());
  require(!contains_member(standard_sec_rep_descriptor_schema_poset_name(), false));
  require(!contains_member(standard_sec_rep_descriptor_poset_name(), false));
  require(!contains_member(standard_section_space_schema_schema_poset_name(), false));

  // Body:

  make_sec_rep_descriptor_schema_poset();
  make_sec_rep_descriptor_poset();

  make_section_space_schema_schema_poset();

  // Postconditions:

  ensure(contains_member(standard_sec_rep_descriptor_schema_poset_name(), false));
  ensure(contains_member(standard_sec_rep_descriptor_poset_name(), false));
  ensure(contains_member(standard_section_space_schema_schema_poset_name(), false));

  // Exit

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_sec_rep_descriptor_schema_poset()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!contains_poset(standard_sec_rep_descriptor_schema_poset_name(), false));

  // Body:

  string lname = standard_sec_rep_descriptor_schema_poset_name();
  poset_path lschema_path = primitives().schema().path(false);
  arg_list largs = poset::make_args();
  
  poset* lschema_host = &new_member_poset<poset>(lname, lschema_path, largs, true);
  lschema_host->get_read_write_access();

  subposet table_dofs(lschema_host);
  table_dofs.put_name(schema_poset_member::table_dof_subposet_name("top"), true, false);

  subposet row_dofs(lschema_host);
  row_dofs.put_name(schema_poset_member::row_dof_subposet_name("top"), true, false);

  // Make the schema members.

  make_sec_rep_descriptor_schema_members();

  // Schematize the schema poset and all its members

  lschema_host->schematize(&table_dofs, &row_dofs, true);

  // Detach all the handles allocated on the stack

  table_dofs.detach_from_state();
  row_dofs.detach_from_state();

  lschema_host->release_access();

  /// @hack "pointer bug"; don't detach or delete the host.

  // Postconditions:

  require(contains_poset(standard_sec_rep_descriptor_schema_poset_name(), false));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_sec_rep_descriptor_schema_members()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_poset(standard_sec_rep_descriptor_schema_poset_name(), false));
  require(member_poset(standard_sec_rep_descriptor_schema_poset_name(), false).state_is_read_write_accessible());

  // Body:

  sec_rep_descriptor_poset::make_standard_schema(*this);

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_sec_rep_descriptor_poset()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!contains_poset(standard_sec_rep_descriptor_poset_name(), false));


  // Body:

  // Create the poset.

  arg_list largs = sec_rep_descriptor_poset::make_arg_list(standard_base_space_member_prototypes_poset_name());

  sec_rep_descriptor_poset& lhost =
    new_member_poset<sec_rep_descriptor_poset>(standard_sec_rep_descriptor_poset_name(),
					       sec_rep_descriptor_poset::standard_schema_path(),
					       largs, true);

  // Create the members.

  lhost.begin_jim_edit_mode(true);

  make_sec_rep_descriptors(&lhost);

  lhost.end_jim_edit_mode(true, true);

  /// @hack "pointer bug"; don't detach or delete the host.

  // Postconditions:

  require(contains_poset(standard_sec_rep_descriptor_poset_name(), false));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_sec_rep_descriptors(sec_rep_descriptor_poset* xhost)
{
  // Preconditions:

  require(xhost->in_jim_edit_mode());

  // Body:

  sec_rep_descriptor lsrd;

  lsrd.new_jim_state(xhost,
                     "__vertices",
                     "",
                     "__elements",
                     "dlinear",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     true,
                     false);
  lsrd.put_name("vertex_element_dlinear", true, false);

  // $$SCRIBBLE eval-sp: make vertex_cells_dlinear rep.

  lsrd.new_jim_state(xhost,
                     "__vertices",
                     "",
                     "__cells",
                     "dlinear",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     true,
                     false);
  lsrd.put_name("vertex_cells_dlinear", true, false);

  lsrd.new_jim_state(xhost,
                     "__elements",
                     "",
                     "__elements",
                     "constant",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     false,
                     false);
  lsrd.put_name("element_element_constant", true, false);

  lsrd.new_jim_state(xhost,
                     "__block_vertices",
                     "",
                     "__blocks",
                     "dlinear",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     true,
                     false);
  lsrd.put_name("vertex_block_dlinear", true, false);

  lsrd.new_jim_state(xhost,
                     "__block_vertices",
                     "",
                     "__blocks",
                     "uniform",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     true,
                     false);
  lsrd.put_name("vertex_block_uniform", true, false);

  lsrd.new_jim_state(xhost,
                     "__1_cells",
                     "",
                     "__1_cells",
                     "constant",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     false,
                     false);
  lsrd.put_name("face_face_const_2D", true, false);

  lsrd.new_jim_state(xhost,
                     "__2_cells",
                     "",
                     "__2_cells",
                     "constant",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     false,
                     false);
  lsrd.put_name("face_face_const_3D", true, false);

  lsrd.new_jim_state(xhost,
                     "__neumann_face_vertices",
                     "",
                     "__1_cells",
                     "dlinear",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     true,
                     false);
  lsrd.put_name("neumann_vertex_face_dlinear_2D", true, false);

  lsrd.new_jim_state(xhost,
                     "__neumann_face_vertices",
                     "",
                     "__2_cells",
                     "dlinear",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     true,
                     false);
  lsrd.put_name("neumann_vertex_face_dlinear_3D", true, false);

  lsrd.new_jim_state(xhost,
                     "__dirichlet_face_vertices",
                     "",
                     "__1_cells",
                     "dlinear",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     true,
                     false);
  lsrd.put_name("dirichlet_vertex_face_dlinear_2D", true, false);

  lsrd.new_jim_state(xhost,
                     "__dirichlet_face_vertices",
                     "",
                     "__2_cells",
                     "dlinear",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     true,
                     false);
  lsrd.put_name("dirichlet_vertex_face_dlinear_3D", true, false);

  lsrd.new_jim_state(xhost,
                     "__neumann_face_vertices",
                     "",
                     "__vertices",
                     "dlinear",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     false,
                     false);
  lsrd.put_name("neumann_vertex_face_dlinear_1D", true, false);

  lsrd.new_jim_state(xhost,
                     "__dirichlet_face_vertices",
                     "",
                     "__vertices",
                     "dlinear",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     false,
                     false);
  lsrd.put_name("dirichlet_vertex_face_dlinear_1D", true, false);

  lsrd.new_jim_state(xhost,
                     "__vertices",
                     "",
                     "__vertices",
                     "constant",
                     "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                     1,
                     false,
                     false);
  lsrd.put_name("vertex_vertex_constant", true, false);

  lsrd.detach_from_state();

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_section_space_schema_schema_poset()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!contains_poset(standard_section_space_schema_schema_poset_name(), false));


  // Body:

  // Create the poset.

  string lname = standard_section_space_schema_schema_poset_name();
  poset_path lschema_path = primitives().schema().path(false);
  arg_list largs = poset::make_args();

  poset* lschema_host = &new_member_poset<poset>(lname, lschema_path, largs, true);
  lschema_host->get_read_write_access();

  subposet table_dofs(lschema_host);
  table_dofs.put_name(schema_poset_member::table_dof_subposet_name("top"), true, false);

  subposet row_dofs(lschema_host);
  row_dofs.put_name(schema_poset_member::row_dof_subposet_name("top"), true, false);

  // Create the members.

  make_section_space_schema_schema_members();

  // Schematize the schema poset and all its members

  lschema_host->schematize(&table_dofs, &row_dofs, true);

  // Detach all the handles allocated on the stack

  table_dofs.detach_from_state();
  row_dofs.detach_from_state();

  lschema_host->release_access();

  /// @hack "pointer bug"; don't detach or delete lschema.

  // Postconditions:

  require(contains_poset(standard_section_space_schema_schema_poset_name(), false));

  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
make_section_space_schema_schema_members()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_poset(standard_section_space_schema_schema_poset_name(), false));
  require(member_poset(standard_section_space_schema_schema_poset_name(), false).state_is_read_write_accessible());

  // Body:

  section_space_schema_poset::make_standard_schema(*this);
  binary_section_space_schema_poset::make_standard_schema(*this);

  // Postconditions:


  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NAMESPACE_POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::fiber_bundles_namespace::
initialize_additional_members()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  define_old_variable(int old_access_request_depth = access_request_depth());


  // Body:

  make_base_space_definitions();
  make_fiber_space_definitions();
  make_section_space_definitions();

  // Postconditions:

  ensure(access_request_depth() == old_access_request_depth);


  // Exit:

  return;
}

void
fiber_bundle::fiber_bundles_namespace::
link_poset(const namespace_poset_member& xmbr)
{
  // Preconditions:

  require(contains_member(&xmbr));
  require(in_jim_edit_mode());

  // Body:

  pod_index_type lmbr_schema_id = xmbr.poset_prereq_id(0);

  if((lmbr_schema_id == PRIMITIVES_SCHEMA_INDEX) ||
     (lmbr_schema_id == member_id("section_space_schema_schema", false)))
  {
    // This is a schema poset; link it under the schema defintions group.

    new_link(SCHEMA_DEFINITIONS_INDEX, xmbr.index().pod());

    new_link(xmbr.index().pod(), BOTTOM_INDEX);
  }
  else if(lmbr_schema_id == member_id(standard_base_space_schema_poset_name(), false))
  {
    // This is a base space poset; link it under the base space group.

    pod_index_type lbase_spaces_id = member_id("base_spaces", false);

    if(!is_valid(lbase_spaces_id))
    {
      // base spaces member not created yet; create it now.

      lbase_spaces_id = new_member(false, 0, false);
      put_member_name(lbase_spaces_id, "base_spaces", true, false);

      new_link(TOP_INDEX, lbase_spaces_id);
    }
    new_link(lbase_spaces_id, xmbr.index().pod());

    new_link(xmbr.index().pod(), BOTTOM_INDEX);
  }
  else if(lmbr_schema_id == member_id(standard_fiber_space_schema_poset_name(), false))
  {
    pod_index_type lfiber_spaces_id = member_id("fiber_spaces", false);

    if(!is_valid(lfiber_spaces_id))
    {
      // fiber spaces member not created yet; create it now.

      lfiber_spaces_id = new_member(false, 0, false);
      put_member_name(lfiber_spaces_id, "fiber_spaces", true, false);

      new_link(TOP_INDEX, lfiber_spaces_id);
    }

    // Test to see if this member comforms to tp.

    poset_path lpath(standard_fiber_space_schema_poset_name(), "tp_schema");
    bool lconforms = xmbr.poset_pointer()->schema().conforms_to(lpath);

    // If it conforms, create the tensor space family if necessary
    // and link this member to that group.

    if(lconforms)
    {
      pod_index_type ltensor_family_id = member_id("tensor_space_family", false);

      if(!is_valid(ltensor_family_id))
      {
          // tensor space family member not created yet; create it now.

          ltensor_family_id = new_member(false, 0, false);
          put_member_name(ltensor_family_id, "tensor_space_family", true, false);

          new_link(lfiber_spaces_id, ltensor_family_id);
      }

      // This is a tensor space; link it under the tensor space family group.

      new_link(ltensor_family_id, xmbr.index().pod());
    }
    else
    {
      // This is a fiber space but not in the tensor space family;
      // so, link it under the fiber spaces group.

      new_link(lfiber_spaces_id, xmbr.index().pod());
    }

    new_link(xmbr.index().pod(), BOTTOM_INDEX);
  }
  else if(dynamic_cast<sec_rep_space*>(xmbr.poset_pointer()) != 0)
  {
    // This is a section space, link it under the section spaces group.

    pod_index_type lsection_spaces_id = member_id("section_spaces", false);

    if(!is_valid(lsection_spaces_id))
    {
      // Section spaces member not created yet; create it now.

      lsection_spaces_id = new_member(false, 0, false);
      put_member_name(lsection_spaces_id, "section_spaces", true, false);

      new_link(TOP_INDEX, lsection_spaces_id);
    }
    else if(is_jem(lsection_spaces_id, BOTTOM_INDEX))
    {
      // This group exists but is empty;
      // delete its link to bottom.

      delete_link(lsection_spaces_id, BOTTOM_INDEX);
    }
    new_link(lsection_spaces_id, xmbr.index().pod());

    new_link(xmbr.index().pod(), BOTTOM_INDEX);
  }
  else
  {
    // Default is xmbr is in general spaces group.

    pod_index_type lgeneral_sets_id = member_id("general_sets", false);

    if(!is_valid(lgeneral_sets_id))
    {
      // general sets member not created yet; create it now.

      lgeneral_sets_id = new_member(false, 0, false);
      put_member_name(lgeneral_sets_id, "general_sets", true, false);

      new_link(TOP_INDEX, lgeneral_sets_id);
    }
    new_link(lgeneral_sets_id, xmbr.index().pod());

    new_link(xmbr.index().pod(), BOTTOM_INDEX);
  }

  // Postconditions:


  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_STATE_HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_type
fiber_bundle::fiber_bundles_namespace::
type_id() const
{
  return FIBER_BUNDLES_NAMESPACE_ID;
}

const char*
fiber_bundle::fiber_bundles_namespace::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "fiber_bundles_namespace";

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::fiber_bundles_namespace::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  sheaves_namespace::attach_handle_data_members();

  _base_space_schema_poset =
    &member_poset<poset>(standard_base_space_schema_poset_name(), false);

  _base_space_member_prototypes_poset =
    &member_poset<base_space_poset>(standard_base_space_member_prototypes_poset_name(), false);

  // Postconditions:

  ensure(postcondition_of(sheaves_names::attach_handle_data_members()));
  ensure(base_space_schema_poset().is_attached());
  ensure(base_space_member_prototypes_poset().is_attached());

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS