


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class section_space_factory

#ifndef SECTION_SPACE_FACTORY_IMPL_H
#define SECTION_SPACE_FACTORY_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_SPACE_FACTORY_H
#include "section_space_factory.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef SEC_REP_SPACE_H
#include "sec_rep_space.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef STRUCTURED_BLOCK_1D_H
#include "structured_block_1d.h"
#endif

#ifndef POSET_PATH_H
#include "poset_path.h"
#endif


namespace fiber_bundle
{

// =============================================================================
// SECTION_SPACE_FACTORY FACET
// =============================================================================

///
template <typename sec_type>
section_space_factory<sec_type>::
section_space_factory()
{

  // Preconditions:

  // Body:

  _found_section = false;

  // Postconditions:

  // Exit:

  return;
}


///
template <typename sec_type>
section_space_factory<sec_type>::
section_space_factory(const section_space_factory& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return;
}


///
template <typename sec_type>
section_space_factory<sec_type>::
~section_space_factory()
{
  // Preconditions:


  // Body:

  // Postconditions:

  // Exit:

  return;
}

///
template <typename sec_type>
sec_type*
section_space_factory<sec_type>::
new_multi_section(fiber_bundles_namespace& xns,
                  const string& xname,
                  subposet& xbase_parts)
{
  sec_type* result;

  // Preconditions:

  require(poset_path::is_valid_name(xname));

  // Body:

  result = new sec_type();
  new_multi_section(xns, xname, xbase_parts, *result);

  // Postconditions:


  // Exit:

  return result;
}

///
template <typename sec_type>
void
section_space_factory<sec_type>::
new_multi_section(fiber_bundles_namespace& xns,
                  const string& xname,
                  subposet& xbase_parts,
                  sec_type& xresult)
{
  // Preconditions:

  require(poset_path::is_valid_name(xname));

  // Body:

  sec_rep_space& lspace = 
    xns.new_section_space<sec_type>(path, base_path, rep_path, true);

  if(lspace.contains_member(xname))
  {
    lspace.get_read_access();
    xresult.attach_to_state(&lspace, xname);
    lspace.release_access();
    _found_section = true;
  }
  else
  {
    xresult.new_jrm_state(&lspace, xbase_parts, true);
    xresult.put_name(xname, true, true);
    put_bounds(&xresult);
    _found_section = false;
  }

  // Postconditions:


  // Exit:

  return;
}

///
template <typename sec_type>
sec_type*
section_space_factory<sec_type>::
new_multi_section(fiber_bundles_namespace& xns,
                  const poset_path& xpath,
                  subposet& xbase_parts)
{
  sec_type* result;

  // Preconditions:

  require(xpath.full());
  require(xns.contains_poset(xpath, true) ||
          (base_path.full() && xns.contains_poset_member(base_path, true)));


  // Body:

  result = new sec_type();
  new_multi_section(xns, xpath, xbase_parts, *result);

  // Postconditions:


  // Exit:

  return result;
}

///
template <typename sec_type>
void
section_space_factory<sec_type>::
new_multi_section(fiber_bundles_namespace& xns,
                  const poset_path& xpath,
                  subposet& xbase_parts,
                  sec_type& xresult)
{
  // Preconditions:

  require(xpath.full());
  require(xns.contains_poset(xpath, true) ||
          (base_path.full() && xns.contains_poset_member(base_path, true)));


  // Body:

  path = xpath.poset_name();
  new_multi_section(xns, xpath.member_name(), xbase_parts, xresult);

  // Postconditions:


  // Exit:

  return;
}

///
template <typename sec_type>
void
section_space_factory<sec_type>::
put_bounds(sec_type* xsec)
{
  // Preconditions:


  // Body:

  // Default implementation does nothing.

  // Postconditions:


  // Exit:

  return;
}

///
template <typename sec_type>
bool
section_space_factory<sec_type>::
found_section() const
{
  return _found_section;
}

///
template <typename sec_type>
void
section_space_factory<sec_type>::
clear_paths()
{
  // Preconditions:


  // Body:

  base_path = "";
  rep_path = "";
  fiber_schema_path = "";
  fiber_path = "";
  path = "";

  // Postconditions:

  ensure(base_path.empty());
  ensure(rep_path.empty());
  ensure(fiber_schema_path.empty());
  ensure(fiber_path.empty());
  ensure(path.empty());

  // Exit:

  return;
}



// =============================================================================
// PRIVATE MEMBER FUNCTIONS
// =============================================================================

/////@todo: Fix new_fiber.
//template <typename sec_type>
//void
//section_space_factory<sec_type>::
//new_fiber(fiber_bundles_namespace& xns,
//          const poset_path& xfiber_path,
//          const poset_path& xvector_space_path,
//          const poset_path& xfiber_schema_path)
//{
//  typedef typename section_traits<sec_type>::standard_fiber_type fiber_type;
//
//  fiber_type::new_host(xns,
//                       xfiber_path.poset_name(),
//		       xvector_space_path,
//                       xfiber_schema_path,
//                       user_args,
//                       true);
//}

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
 
} // namespace fiber_bundle

#endif // SECTION_SPACE_FACTORY_IMPL_H
