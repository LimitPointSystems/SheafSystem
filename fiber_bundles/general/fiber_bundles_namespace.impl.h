

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for member function templates in class namespace_poset.

#ifndef FIBER_BUNDLES_NAMESPACE_IMPL_H
#define FIBER_BUNDLES_NAMESPACE_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef SHEAVES_NAMESPACE_H
#include "sheaves_namespace.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "std_string.h"
#endif

#ifndef BASE_SPACE_POSET_H
#include "base_space_poset.h"
#endif

#ifndef POSET_PATH_H
#include "poset_path.h"
#endif

#ifndef PRIMITIVE_VALUE_H
#include "primitive_value.h"
#endif 

#ifndef BINARY_SECTION_SPACE_SCHEMA_MEMBER_H
#include "binary_section_space_schema_member.h"
#endif

#ifndef BINARY_SECTION_SPACE_SCHEMA_POSET_H
#include "binary_section_space_schema_poset.h"
#endif

#ifndef SEC_AT1_SPACE_H
#include "sec_at1_space.h"
#endif

//#define DIAGNOSTIC_OUTPUT
 
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// BASE SPACE FACTORY METHOD FACET
// ===========================================================

template <typename B>
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space(const poset_path& xbase_space_path,
	       const arg_list& xargs,
	       const poset_path& xschema_path,
	       int xmax_db,
	       bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  require(path_is_auto_read_available<base_space_poset>(xbase_space_path, xauto_access));
  require(path_is_auto_read_available(xschema_path, xauto_access));

  // zone_nodes has B::DB == -1.
  // Require that the client has specified a valid max_db

  require((B::DB > -1) || ((xargs.contains_arg("max_db") || xmax_db > -1)));

  // Body:

  // Set schema.
  // $$SCRIBBLE dmb: need notion of completed schema path
  // and suitable preconditions.

  poset_path lschema_path(xschema_path);
  if(lschema_path.empty())
  {
    lschema_path = B::standard_schema_path();
  }

  // Construct the arg list to pass to new_member_poset.

  arg_list largs(xargs);

  // Set max_db;  default (B::DB) is overridden by arg_list is overridden by explicit arg. 

  int lmax_db = B::DB;
  if(largs.contains_arg("max_db"))
  {
    int larg_max_db = largs.value("max_db");
    lmax_db = (larg_max_db > lmax_db) ? larg_max_db : lmax_db;
  }
  else
  {
    largs.push_back("max_db");
  }

  lmax_db = (xmax_db > lmax_db) ? xmax_db : lmax_db;

  largs.arg("max_db").value = lmax_db;
  
  base_space_poset& result = 
    new_member_poset<base_space_poset>(xbase_space_path.poset_name(), 
				       lschema_path, 
				       largs, 
				       xauto_access);
  result.get_read_write_access();

  // Postconditions:

  ensure(result.max_db() >= -1);
  ensure(xschema_path.empty() ? 
	 result.schema(true).path(true) == B::standard_schema_path() : 
	 result.schema(true).path(true) == xschema_path);
  
  // Exit:

  return result;
}  
  
  

//--------------------------------------------------------------------------
// BEGIN NEW INTERFACE

// ===========================================================
// STANDARD NAME FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename F>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
standard_fiber_space_path(const string& xfiber_suffix) const
{
  // Preconditions:

  // Body:

  poset_path result(F::class_name() + xfiber_suffix, "");

  // Postconditions:

  // Exit:

  return result;
}

template <typename F>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
standard_fiber_space_schema_path(const string& xfiber_suffix) const
{
  // Preconditions:

  // Body:

  poset_path result(standard_fiber_space_path<F>(xfiber_suffix).poset_name() + "_schema", "");

  // Postconditions:

  // Exit:

  return result;
}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
standard_section_space_path(const poset_path& xbase_space_path,
			    const poset_path& xrep_path,
			    const string& xsection_suffix,
			    const string& xfiber_suffix) const
{
  // Preconditions:

  // Body:

  string lrep(xrep_path.member_name());
  if(lrep.empty())
  {
    lrep = "vertex_cells_dlinear";
  }

  string result = standard_fiber_space_path<S::fiber_type>(xfiber_suffix).poset_name();
  result += "_on_" + xbase_space_path.poset_name();
  result += "_" + lrep;
  if(!xsection_suffix.empty())
  {
    result += "_" + xsection_suffix;
  }

  // Postconditions:

  // Exit:

  return result;
}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
standard_section_space_schema_path(const poset_path& xbase_space_path,
				   const poset_path& xrep_path,
				   const string& xfiber_suffix) const
{
  // Preconditions:

  // Body:

  poset_path result(standard_section_space_path<S>(xbase_space_path, xrep_path, "", xfiber_suffix).poset_name() + "_schema", "");

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SHALLOW FIBER SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_2(const poset_path& xfiber_space_path,
		const arg_list& xfiber_space_args,
		const poset_path& xfiber_space_schema_path,
		bool xauto_access)
{
  // Preconditions:

  // Body:

  typedef typename F::host_type host_type;

  host_type* lresult_ptr;

  /// @todo Implement with templatized struct.

  host_type& result = *lresult_ptr;

  // Postconditions:

  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_scalar_space_2(const poset_path& xscalar_space_path,
		 const arg_list& xscalar_space_args,
		 const poset_path& xscalar_space_schema_path,
		 bool xauto_access)
{
  // Preconditions:

  require(unexecutable("F::host_type conforms to at0_space"));
  require(path_is_auto_read_available(xscalar_space_path, xauto_access));
  require(unexecutable("xscalar_space_args properly initialized"));
  require(path_is_auto_read_accessible(xscalar_space_schema_path, xauto_access));

  // Body:

  typedef typename F::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset<host_type>(xscalar_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(xscalar_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    lresult_ptr = new host_type(*this,
				xscalar_space_path.poset_name(),
				xscalar_space_args,
				xscalar_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(xscalar_space_path));
  ensure(result.path() == xscalar_space_path);
  ensure(result.schema().path() == xscalar_space_schema_path);

  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space(const poset_path& xvector_space_path,
		 const arg_list& xvector_space_args,
		 const poset_path& xvector_space_schema_path,
		 bool xauto_access)
{
  // Preconditions:

  require(unexecutable("F::host_type conforms to at1_space"));
  require(path_is_auto_read_available(xvector_space_path, xauto_access));
  require(unexecutable("xvector_space_args properly initialized"));
  require(path_is_auto_read_accessible(xvector_space_schema_path, xauto_access));
  require(path_is_auto_read_accessible(xvector_space_args.value("scalar_space_path"), xauto_access));

  // Body:

  typedef typename F::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset<host_type>(xvector_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(xvector_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    lresult_ptr = new host_type(*this,
				xvector_space_path.poset_name(),
				xvector_space_args,
				xvector_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(xvector_space_path));
  ensure(result.path() == xvector_space_path);
  ensure(result.schema().path() == xvector_space_schema_path);
  ensure(result.scalar_space_path() == xvector_space_args.value("scalar_space_path"));

  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space(const poset_path& xtensor_space_path,
		 const arg_list& xtensor_space_args,
		 const poset_path& xtensor_space_schema_path,
		 bool xauto_access)
{
  // Preconditions:

  require(unexecutable("F::host_type conforms to tp_space"));
  require(path_is_auto_read_available(xtensor_space_path, xauto_access));
  require(unexecutable("xtensor_space_args properly initialized"));
  require(path_is_auto_read_accessible(xtensor_space_schema_path, xauto_access));
  require(path_is_auto_read_accessible(xtensor_space_args.value("vector_space_path"), xauto_access));

  // Body:

  typedef typename F::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset<host_type>(xtensor_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(xtensor_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    lresult_ptr = new host_type(*this,
				xtensor_space_path.poset_name(),
				xtensor_space_args,
				xtensor_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(xtensor_space_path));
  ensure(result.path() == xtensor_space_path);
  ensure(result.schema().path() == xtensor_space_schema_path);
  ensure(result.vector_space_path() == xtensor_space_args.value("vector_space_path"));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEEP FIBER SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space(const string& xfiber_suffix, bool xauto_access)
{
  // Preconditions:

  // Body:

  typedef typename F::host_type host_type;

  host_type* lresult_ptr;

  /// @todo Implement with templatized struct.

  host_type& result = *lresult_ptr;

  // Postconditions:

  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_scalar_space(const string& xfiber_suffix, bool xauto_access)
{
  // Preconditions:

  require(unexecutable("F::host_type conforms to at0_space"));
  require(path_is_auto_read_available(standard_fiber_space_path<F>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_accessible(standard_fiber_space_schema_path<F>(xfiber_suffix), xauto_access));

  // Body:

  poset_path lscalar_space_path = standard_fiber_space_path<F>(xfiber_suffix);

  typedef typename F::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset<host_type>(lscalar_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lscalar_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    arg_list lscalar_space_args = host_type::make_arg_list();
    poset_path lscalar_space_schema_path = standard_fiber_space_schema_path<F>(xfiber_suffix);

    lresult_ptr = new host_type(*this,
				lscalar_space_path.poset_name(),
				lscalar_space_args,
				lscalar_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(standard_fiber_space_path<F>(xfiber_suffix)));
  ensure(result.path() == standard_fiber_space_path<F>(xfiber_suffix));
  ensure(result.schema().path() == standard_fiber_space_schema_path<F>(xfiber_suffix));

  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space(const string& xfiber_suffix, bool xauto_access)
{
  // Preconditions:

  require(unexecutable("F::host_type conforms to at1_space"));
  require(path_is_auto_read_available(standard_fiber_space_path<F>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_accessible(standard_fiber_space_schema_path<F>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_fiber_space_path<F::scalar_type>(xfiber_suffix), xauto_access));

  // Body:

  typedef typename F::host_type host_type;
  typedef typename F::scalar_type scalar_type;
  typedef typename scalar_type::host_type scalar_host_type;

  poset_path lvector_space_path = standard_fiber_space_path<F>(xfiber_suffix);

  host_type* lresult_ptr;

  if(contains_poset<host_type>(lvector_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lvector_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; Create it.

    // Create the scalar fiber space if not already created.

    scalar_host_type& lscalar_space = new_scalar_space<scalar_type>(xfiber_suffix, xauto_access);

    // Create the vector fiber space.

    arg_list lvector_space_args = host_type::make_arg_list(lscalar_space.path());
    poset_path lvector_space_schema_path = standard_fiber_space_schema_path<F>(xfiber_suffix);

    lresult_ptr = new host_type(*this,
				lvector_space_path.poset_name(),
				lvector_space_args,
				lvector_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(standard_fiber_space_path<F>(xfiber_suffix)));
  ensure(result.path() == standard_fiber_space_path<F>(xfiber_suffix));
  ensure(result.schema().path() == standard_fiber_space_schema_path<F>(xfiber_suffix));
  ensure(result.scalar_space_path() == standard_fiber_space_path<F::scalar_type>(xfiber_suffix));

  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space(const string& xfiber_suffix, bool xauto_access)
{
  // Preconditions:

  require(unexecutable("F::host_type conforms to tp_space"));
  require(path_is_auto_read_available(standard_fiber_space_path<F>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_accessible(standard_fiber_space_schema_path<F>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_fiber_space_path<F::vector_type>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_fiber_space_path<F::scalar_type>(xfiber_suffix), xauto_access));

  // Body:

  typedef typename F::host_type host_type;
  typedef typename F::vector_type vector_type;
  typedef typename vector_type::host_type vector_host_type;

  poset_path ltensor_space_path = standard_fiber_space_path<F>(xfiber_suffix);

  host_type* lresult_ptr;

  if(contains_poset<host_type>(ltensor_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(ltensor_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; Create it.

    // Create the vector fiber space if not already created.

    vector_host_type& lvector_space = new_vector_space<vector_type>(xfiber_suffix, xauto_access);

    // Create the tensor fiber space.

    arg_list ltensor_space_args = host_type::make_arg_list(F::P, lvector_space.path());
    poset_path ltensor_space_schema_path = standard_fiber_space_schema_path<F>(xfiber_suffix);

    lresult_ptr = new host_type(*this,
				ltensor_space_path.poset_name(),
				ltensor_space_args,
				ltensor_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(standard_fiber_space_path<F>(xfiber_suffix)));
  ensure(result.path() == standard_fiber_space_path<F>(xfiber_suffix));
  ensure(result.schema().path() == standard_fiber_space_schema_path<F>(xfiber_suffix));
  ensure(result.vector_space_path() == standard_fiber_space_path<F::vector_type>(xfiber_suffix));
  ensure(result.scalar_space_path() == standard_fiber_space_path<F::scalar_type>(xfiber_suffix));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SHALLOW SECTION SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space_2(const poset_path& xsection_space_path,
		    const arg_list& xsection_space_args,
		    const poset_path& xsection_space_schema_path,
		    bool xauto_access)
{
  // Preconditions:

  // Body:

  typedef typename S::host_type host_type;

  host_type* lresult_ptr;

  /// @todo Implement with templatized struct.

  host_type& result = *lresult_ptr;

  // Postconditions:

  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_scalar_section_space_2(const poset_path& xscalar_space_path,
			   const arg_list& xscalar_space_args,
			   const poset_path& xscalar_space_schema_path,
			   bool xauto_access)
{
  // Preconditions:

  require(unexecutable("S::host_type conforms to sec_at0_space"));
  require(path_is_auto_read_available(xscalar_space_path, xauto_access));
  require(unexecutable("xscalar_space_args properly initialized"));
  require(path_is_auto_read_accessible(xscalar_space_schema_path, xauto_access));

  // Body:

  typedef typename S::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset<host_type>(xscalar_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(xscalar_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist; create it.

    lresult_ptr = new host_type(*this,
				xscalar_space_path.poset_name(),
				xscalar_space_args,
				xscalar_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(xscalar_space_path));
  ensure(result.path() == xscalar_space_path);
  ensure(result.schema().path() == xscalar_space_schema_path);

  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space(const poset_path& xvector_space_path,
			 const arg_list& xvector_space_args,
			 const poset_path& xvector_space_schema_path,
			 bool xauto_access)
{
  // Preconditions:

  require(unexecutable("S::host_type conforms to sec_at1_space"));
  require(path_is_auto_read_available(xvector_space_path, xauto_access));
  require(unexecutable("xvector_space_args properly initialized"));
  require(path_is_auto_read_accessible(xvector_space_schema_path, xauto_access));
  require(path_is_auto_read_accessible(xvector_space_args.value("scalar_space_path"), xauto_access));

  // Body:

  typedef typename S::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset<host_type>(xvector_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(xvector_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist; create it.

    lresult_ptr = new host_type(*this,
				xvector_space_path.poset_name(),
				xvector_space_args,
				xvector_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(xvector_space_path));
  ensure(result.path() == xvector_space_path);
  ensure(result.schema().path() == xvector_space_schema_path);
  ensure(result.scalar_space_path() == xvector_space_args.value("scalar_space_path"));

  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space(const poset_path& xtensor_space_path,
			 const arg_list& xtensor_space_args,
			 const poset_path& xtensor_space_schema_path,
			 bool xauto_access)
{
  // Preconditions:

  require(unexecutable("S::host_type conforms to sec_tp_space"));
  require(path_is_auto_read_available(xtensor_space_path, xauto_access));
  require(unexecutable("xtensor_space_args properly initialized"));
  require(path_is_auto_read_accessible(xtensor_space_schema_path, xauto_access));
  require(path_is_auto_read_accessible(xtensor_space_args.value("vector_space_path"), xauto_access));

  // Body:

  typedef typename S::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset<host_type>(xtensor_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(xtensor_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist; create it.

    lresult_ptr = new host_type(*this,
				xtensor_space_path.poset_name(),
				xtensor_space_args,
				xtensor_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(xtensor_space_path));
  ensure(result.path() == xtensor_space_path);
  ensure(result.schema().path() == xtensor_space_schema_path);
  ensure(result.vector_space_path() == xtensor_space_args.value("vector_space_path"));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEEP SECTION SPACE FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space(const poset_path& xbase_path,
		  const poset_path& xrep_path,
		  const string& xsection_suffix,
		  const string& xfiber_suffix,
		  bool xauto_access)
{
  // Preconditions:

  // Body:

  typedef typename S::host_type host_type;

  host_type* lresult_ptr;

  /// @todo Implement with templatized struct.

  host_type& result = *lresult_ptr;

  // Postconditions:

  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_scalar_section_space(const poset_path& xbase_space_path,
			 const poset_path& xrep_path,
			 const string& xsection_suffix,
			 const string& xfiber_suffix,
			 bool xauto_access)
{
  // Preconditions:

  require(unexecutable("S::host_type conforms to sec_at0_space"));

  // Scalar section space

  require(path_is_auto_read_accessible(xbase_space_path, xauto_access));
  require(path_is_auto_read_available(standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_section_space_schema_path<S>(xbase_space_path, xrep_path, xfiber_suffix), xauto_access));

  // Scalar fiber space

  require(path_is_auto_read_available(standard_fiber_space_path<S::fiber_type>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_fiber_space_schema_path<S::fiber_type>(xfiber_suffix), xauto_access));

  // Body:

  typedef typename S::host_type host_type;

  host_type* lresult_ptr;

  poset_path lscalar_space_path = standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix);
  if(contains_poset<host_type>(lscalar_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lscalar_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist;

    // Create section space schema if required.

    poset_path lscalar_space_schema_path = new_scalar_section_space_schema<S>(xbase_space_path, xrep_path, xfiber_suffix);

    // Create the section space.

    arg_list lscalar_space_args = host_type::make_arg_list();

    lresult_ptr = new host_type(*this,
				lscalar_space_path.poset_name(),
				lscalar_space_args,
				lscalar_space_schema_path,
				xauto_access);
  }
  
  host_type& result = *lresult_ptr;

  // Postconditions:

  // Scalar section space

  ensure(contains_poset(standard_section_space_path<S>(xbase_space_path, xrep_path,xsection_suffix, xfiber_suffix)));
  ensure(result.path() == standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(contains_poset(standard_section_space_schema_path<S>(xbase_space_path, xrep_path, xfiber_suffix)));
  ensure(result.schema().path() == standard_section_space_schema_path<S>(xbase_space_path, xrep_path, xfiber_suffix));

  // Scalar fiber space

  ensure(contains_poset(standard_fiber_space_path<S::fiber_type>(xfiber_suffix)));
  ensure(result.schema().fiber_space_path() == standard_fiber_space_path<S::fiber_type>(xfiber_suffix));
  ensure(member_poset(standard_fiber_space_path<S::fiber_type>()).schema().path() == standard_fiber_space_schema_path<S::fiber_type>(xfiber_suffix));

  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space(const poset_path& xbase_space_path,
			 const poset_path& xrep_path,
			 const string& xsection_suffix,
			 const string& xfiber_suffix,
			 bool xauto_access)
{
  // Preconditions:

  require(unexecutable("S::host_type conforms to sec_at1_space"));

  // Vector section space

  require(path_is_auto_read_accessible(xbase_space_path, xauto_access));
  require(path_is_auto_read_available(standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_section_space_schema_path<S>(xbase_space_path, xrep_path, xfiber_suffix), xauto_access));

  // Vector fiber space

  require(path_is_auto_read_available(standard_fiber_space_path<S::fiber_type>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_fiber_space_schema_path<S::fiber_type>(xfiber_suffix), xauto_access));

  // Scalar section space

  require(path_is_auto_read_available(standard_section_space_path<S::scalar_type>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_section_space_schema_path<S::scalar_type>(xbase_space_path, xrep_path,xfiber_suffix), xauto_access));

  // Scalar fiber space

  require(path_is_auto_read_available(standard_fiber_space_path<S::scalar_type::fiber_type>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_fiber_space_schema_path<S::scalar_type::fiber_type>(xfiber_suffix), xauto_access));

  // Body:

  typedef typename S::host_type host_type;
  typedef typename S::scalar_type scalar_type;
  typedef typename scalar_type::host_type scalar_host_type;

  host_type* lresult_ptr;

  poset_path lvector_space_path = standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix);
  if(contains_poset<host_type>(lvector_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lvector_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist;

    // Create the scalar space if required.

    scalar_host_type& lscalar_space = new_scalar_section_space<scalar_type>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix);

    // Create section space schema if required.

    poset_path lvector_space_schema_path = new_vector_section_space_schema<S>(xbase_space_path, xrep_path, xfiber_suffix);

    // Create the section space.

    arg_list lvector_space_args = host_type::make_arg_list(lscalar_space.path());

    lresult_ptr = new host_type(*this,
				lvector_space_path.poset_name(),
				lvector_space_args,
				lvector_space_schema_path,
				xauto_access);
  }
  
  host_type& result = *lresult_ptr;

  // Postconditions:

  // Vector section space

  ensure(contains_poset(standard_section_space_path<S>(xbase_space_path, xrep_path,xsection_suffix, xfiber_suffix)));
  ensure(result.path() == standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(contains_poset(standard_section_space_schema_path<S>(xbase_space_path, xrep_path, xfiber_suffix)));
  ensure(result.schema().path() == standard_section_space_schema_path<S>(xbase_space_path, xrep_path, xfiber_suffix));

  // Vector fiber space

  ensure(contains_poset(standard_fiber_space_path<S::fiber_type>(xfiber_suffix)));
  ensure(result.schema().fiber_space_path() == standard_fiber_space_path<S::fiber_type>(xfiber_suffix));
  ensure(member_poset(standard_fiber_space_path<S::fiber_type>()).schema().path() == standard_fiber_space_schema_path<S::fiber_type>(xfiber_suffix));

  // Scalar section space

  ensure(contains_poset(standard_section_space_path<S::scalar_type>(xbase_space_path, xrep_path,xsection_suffix, xfiber_suffix)));
  ensure(result.path() == standard_section_space_path<S::scalar_type>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(contains_poset(standard_section_space_schema_path<S::scalar_type>(xbase_space_path, xrep_path, xfiber_suffix)));
  ensure(result.schema().path() == standard_section_space_schema_path<S::scalar_type>(xbase_space_path, xrep_path, xfiber_suffix));

  // Scalar fiber space

  ensure(contains_poset(standard_fiber_space_path<S::scalar_type::fiber_type>(xfiber_suffix)));
  ensure(result.schema().fiber_space_path() == standard_fiber_space_path<S::scalar_type::fiber_type>(xfiber_suffix));
  ensure(member_poset(standard_fiber_space_path<S::scalar_type::fiber_type>()).schema().path() == standard_fiber_space_schema_path<S::scalar_type::fiber_type>(xfiber_suffix));

  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space(const poset_path& xbase_space_path,
			 const poset_path& xrep_path,
			 const string& xsection_suffix,
			 const string& xfiber_suffix,
			 bool xauto_access)
{
  // Preconditions:

  require(unexecutable("S::host_type conforms to sec_tp_space"));

  // Tensor section space

  require(path_is_auto_read_accessible(xbase_space_path, xauto_access));
  require(path_is_auto_read_available(standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_section_space_schema_path<S>(xbase_space_path, xrep_path, xfiber_suffix), xauto_access));

  // Tensor fiber space

  require(path_is_auto_read_available(standard_fiber_space_path<S::fiber_type>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_fiber_space_schema_path<S::fiber_type>(xfiber_suffix), xauto_access));

  // Vector section space

  require(path_is_auto_read_available(standard_section_space_path<S::vector_type>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_section_space_schema_path<S::vector_type>(xbase_space_path, xrep_path,xfiber_suffix), xauto_access));

  // Vector fiber space

  require(path_is_auto_read_available(standard_fiber_space_path<S::vector_type::fiber_type>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_fiber_space_schema_path<S::vector_type::fiber_type>(xfiber_suffix), xauto_access));

  // Scalar section space

  require(path_is_auto_read_available(standard_section_space_path<S::scalar_type>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_section_space_schema_path<S::scalar_type>(xbase_space_path, xrep_path,xfiber_suffix), xauto_access));

  // Scalar fiber space

  require(path_is_auto_read_available(standard_fiber_space_path<S::scalar_type::fiber_type>(xfiber_suffix), xauto_access));
  require(path_is_auto_read_available(standard_fiber_space_schema_path<S::scalar_type::fiber_type>(xfiber_suffix), xauto_access));

  // Body:

  typedef typename S::host_type host_type;
  typedef typename S::vector_type vector_type;
  typedef typename vector_type::host_type vector_host_type;

  host_type* lresult_ptr;

  poset_path ltensor_space_path = standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix);
  if(contains_poset<host_type>(ltensor_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(ltensor_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist;

    // Create the vector space if required.

    vector_host_type& lvector_space = new_vector_section_space<vector_type>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix);

    // Create section space schema if required.

    poset_path ltensor_space_schema_path = new_tensor_section_space_schema<S>(xbase_space_path, xrep_path, xfiber_suffix);

    // Create the section space.

    arg_list ltensor_space_args = host_type::make_arg_list(lvector_space.path());

    lresult_ptr = new host_type(*this,
				ltensor_space_path.poset_name(),
				ltensor_space_args,
				ltensor_space_schema_path,
				xauto_access);
  }
  
  host_type& result = *lresult_ptr;

  // Postconditions:

  // Tensor section space

  ensure(contains_poset(standard_section_space_path<S>(xbase_space_path, xrep_path,xsection_suffix, xfiber_suffix)));
  ensure(result.path() == standard_section_space_path<S>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(contains_poset(standard_section_space_schema_path<S>(xbase_space_path, xrep_path, xfiber_suffix)));
  ensure(result.schema().path() == standard_section_space_schema_path<S>(xbase_space_path, xrep_path, xfiber_suffix));

  // Tensor fiber space

  ensure(contains_poset(standard_fiber_space_path<S::fiber_type>(xfiber_suffix)));
  ensure(result.schema().fiber_space_path() == standard_fiber_space_path<S::fiber_type>(xfiber_suffix));
  ensure(member_poset(standard_fiber_space_path<S::fiber_type>()).schema().path() == standard_fiber_space_schema_path<S::fiber_type>(xfiber_suffix));

  // Vector section space

  ensure(contains_poset(standard_section_space_path<S::vector_type>(xbase_space_path, xrep_path,xsection_suffix, xfiber_suffix)));
  ensure(result.path() == standard_section_space_path<S::vector_type>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(contains_poset(standard_section_space_schema_path<S::vector_type>(xbase_space_path, xrep_path, xfiber_suffix)));
  ensure(result.schema().path() == standard_section_space_schema_path<S::vector_type>(xbase_space_path, xrep_path, xfiber_suffix));

  // Vector fiber space

  ensure(contains_poset(standard_fiber_space_path<S::vector_type::fiber_type>(xfiber_suffix)));
  ensure(result.schema().fiber_space_path() == standard_fiber_space_path<S::vector_type::fiber_type>(xfiber_suffix));
  ensure(member_poset(standard_fiber_space_path<S::vector_type::fiber_type>()).schema().path() == standard_fiber_space_schema_path<S::vector_type::fiber_type>(xfiber_suffix));

  // Scalar section space

  ensure(contains_poset(standard_section_space_path<S::scalar_type>(xbase_space_path, xrep_path,xsection_suffix, xfiber_suffix)));
  ensure(result.path() == standard_section_space_path<S::scalar_type>(xbase_space_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(contains_poset(standard_section_space_schema_path<S::scalar_type>(xbase_space_path, xrep_path, xfiber_suffix)));
  ensure(result.schema().path() == standard_section_space_schema_path<S::scalar_type>(xbase_space_path, xrep_path, xfiber_suffix));

  // Scalar fiber space

  ensure(contains_poset(standard_fiber_space_path<S::scalar_type::fiber_type>(xfiber_suffix)));
  ensure(result.schema().fiber_space_path() == standard_fiber_space_path<S::scalar_type::fiber_type>(xfiber_suffix));
  ensure(member_poset(standard_fiber_space_path<S::scalar_type::fiber_type>()).schema().path() == standard_fiber_space_schema_path<S::scalar_type::fiber_type>(xfiber_suffix));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SHALLOW SECTION SPACE SCHEMA FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEEP SECTION SPACE SCHEMA FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// END NEW INTERFACE
//--------------------------------------------------------------------------

// ===========================================================
// FIBER SPACE FACTORY METHOD FACET
// ===========================================================

// Template specializations required by new_fiber_space.

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_impl<fiber_bundle::at0_space>
{
  template <typename fiber_type>
  static at0_space& new_space(fiber_bundles_namespace& xns,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_scalar_space<fiber_type>(xfiber_space_path,
					    xfiber_space_args,
					    xfiber_space_schema_path,
					    xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_impl<fiber_bundle::at1_space>
{
  template <typename fiber_type>
  static at1_space& new_space(fiber_bundles_namespace& xns,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_vector_space<fiber_type>(xfiber_space_path,
					    xfiber_space_args,
					    xfiber_space_schema_path,
					    "",
					    "",
					    "",
					    xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_impl<fiber_bundle::atp_space>
{
  template <typename fiber_type>
  static atp_space& new_space(fiber_bundles_namespace& xns,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_tensor_space<fiber_type>(xfiber_space_path,
					    xfiber_space_args,
					    xfiber_space_schema_path,
					    "",
					    "",
					    "",
					    "",
					    "",
					    "",
					    xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_impl<fiber_bundle::stp_space>
{
  template <typename fiber_type>
  static stp_space& new_space(fiber_bundles_namespace& xns,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_tensor_space<fiber_type>(xfiber_space_path,
					    xfiber_space_args,
					    xfiber_space_schema_path,
					    "",
					    "",
					    "",
					    "",
					    "",
					    "",
					    xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_impl<fiber_bundle::tp_space>
{
  template <typename fiber_type>
  static tp_space& new_space(fiber_bundles_namespace& xns,
			     const poset_path& xfiber_space_path,
			     const arg_list& xfiber_space_args,
			     const poset_path& xfiber_space_schema_path,
			     bool xauto_access)
  {
    return xns.new_tensor_space<fiber_type>(xfiber_space_path,
					    xfiber_space_args,
					    xfiber_space_schema_path,
					    "",
					    "",
					    "",
					    "",
					    "",
					    "",
					    xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_impl<fiber_bundle::vd_space>
{
  template <typename fiber_type>
  static vd_space& new_space(fiber_bundles_namespace& xns,
			     const poset_path& xfiber_space_path,
			     const arg_list& xfiber_space_args,
			     const poset_path& xfiber_space_schema_path,
			     bool xauto_access)
  {
    return xns.new_vector_space<fiber_type>(xfiber_space_path,
					    xfiber_space_args,
					    xfiber_space_schema_path,
					    "",
					    "",
					    "",
					    xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_impl<fiber_bundle::gln_space>
{
  template <typename fiber_type>
  static gln_space& new_space(fiber_bundles_namespace& xns,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_group_space<fiber_type>(xfiber_space_path,
					   xfiber_space_args,
					   xfiber_space_schema_path,
					   "",
					   "",
					   "",
					   "",
					   "",
					   "",
					   xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_impl<fiber_bundle::jcb_space>
{
  template <typename fiber_type>
  static jcb_space& new_space(fiber_bundles_namespace& xns,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_jacobian_space<fiber_type>(xfiber_space_path,
					      xfiber_space_args,
					      xfiber_space_schema_path,
					      "",
					      "",
					      "",
					      "",
					      "",
					      "",
					      "",
					      "",
					      "",
					      xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_fiber_space_impl<fiber_bundle::tuple_space>
{
  template <typename fiber_type>
  static tuple_space& new_space(fiber_bundles_namespace& xns,
				const poset_path& xfiber_space_path,
				const arg_list& xfiber_space_args,
				const poset_path& xfiber_space_schema_path,
				bool xauto_access)
  {
    return xns.new_tuple_space<fiber_type>(xfiber_space_path,
					   xfiber_space_args,
					   xfiber_space_schema_path,
					   xauto_access);
  };
};

// PUBLIC MEMBER FUNCTIONS

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space(const poset_path& xfiber_space_path,
		const arg_list& xfiber_space_args,
		const poset_path& xfiber_space_schema_path,
		bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on fiber space arguments

  require(completed_space_path_is_available<F>(xfiber_space_path, xauto_access));
  require(completed_schema_path_conforms_to<F>(xfiber_space_schema_path, xauto_access));
  require(args_conform_to_completed_schema_path<F>(xfiber_space_args, xfiber_space_schema_path, xauto_access));

  // Body:

  typedef F fiber_type;
  typedef typename F::host_type host_type;
  typedef new_fiber_space_impl<host_type> impl_type;
  
  // Call to function template member of template
  // requires telling compiler that dependent name is a template.

  host_type& result = impl_type::template new_space<fiber_type>(*this,
								xfiber_space_path,
								xfiber_space_args,
								xfiber_space_schema_path,
								xauto_access);

  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_scalar_space(const poset_path& xfiber_space_path,
		 const arg_list& xfiber_space_args,
		 const poset_path& xfiber_space_schema_path,
		 bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on fiber space arguments

  require(completed_space_path_is_available<F>(xfiber_space_path, xauto_access));
  require(completed_schema_path_conforms_to<F>(xfiber_space_schema_path, xauto_access));
  require(args_conform_to_completed_schema_path<F>(xfiber_space_args, xfiber_space_schema_path, xauto_access));

  // Body:

  // Complete the various paths.

  const poset_path lfiber_space_path = 
    completed_space_path<F>(xfiber_space_path);

  const poset_path lfiber_space_schema_path = 
    completed_schema_path<F>(xfiber_space_schema_path);

  // Find or create the result.
  
  typedef typename F::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset<host_type>(lfiber_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lfiber_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    // Initialize the arg list if needed.

    arg_list lfiber_space_args(xfiber_space_args);
    if(lfiber_space_args.empty())
    {
      lfiber_space_args = host_type::make_arg_list();
    }

    lresult_ptr = new host_type(*this,
				lfiber_space_path.poset_name(),
				lfiber_space_args,
				lfiber_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space(const poset_path& xfiber_space_path,
		 const arg_list& xfiber_space_args,
		 const poset_path& xfiber_space_schema_path,
		 const poset_path& xscalar_space_path,
		 const arg_list& xscalar_space_args,
		 const poset_path& xscalar_space_schema_path,
		 bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on fiber space arguments

  require(completed_space_path_is_available<F>(xfiber_space_path, xauto_access));
  require(completed_schema_path_conforms_to<F>(xfiber_space_schema_path, xauto_access));
  require(args_conform_to_completed_schema_path<F>(xfiber_space_args, xfiber_space_schema_path, xauto_access));

  // Conditions on scalar space arguments:

  require(completed_scalar_space_path_is_available<F>(xfiber_space_path,
						      xscalar_space_path,
						      xfiber_space_args,
						      xauto_access));

  require(completed_schema_path_conforms_to<typename F::scalar_type>\
	  (xscalar_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename F::scalar_type> \
	  (xscalar_space_args, xscalar_space_schema_path, xauto_access));

  // Body:

  // Complete the various paths.

  const poset_path lfiber_space_path = 
    completed_space_path<F>(xfiber_space_path);

  const poset_path lfiber_space_schema_path = 
    completed_schema_path<F>(xfiber_space_schema_path);

  const poset_path lscalar_space_path = 
    completed_scalar_space_path<F>(xfiber_space_path,
				   xscalar_space_path,
				   xfiber_space_args,
				   xauto_access);

  const poset_path lscalar_space_schema_path = 
    completed_schema_path<typename F::scalar_type>(xscalar_space_schema_path);

  // Find or create the result.
  
  typedef typename F::host_type host_type;
  typedef typename F::scalar_type scalar_type;
  typedef typename F::scalar_type::host_type scalar_host_type;

  host_type* lresult_ptr;

  if(contains_poset(lfiber_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lfiber_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    // First find or create the scalar space.

    scalar_host_type& lscalar_space = 
      new_scalar_space<scalar_type>(lscalar_space_path,
				    xscalar_space_args,
				    lscalar_space_schema_path,
				    xauto_access);

    // Initialize the arg list if needed.

    arg_list lfiber_space_args(xfiber_space_args);
    if(lfiber_space_args.empty())
    {
      lfiber_space_args = host_type::make_arg_list("");
    }
    lfiber_space_args.value("scalar_space_path") = lscalar_space.path(xauto_access);

    lresult_ptr = new host_type(*this,
				lfiber_space_path.poset_name(),
				lfiber_space_args,
				lfiber_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space(const poset_path& xfiber_space_path,
		 const arg_list& xfiber_space_args,
		 const poset_path& xfiber_space_schema_path,
		 const poset_path& xvector_space_path,
		 const arg_list& xvector_space_args,
		 const poset_path& xvector_space_schema_path,
		 const poset_path& xscalar_space_path,
		 const arg_list& xscalar_space_args,
		 const poset_path& xscalar_space_schema_path,
		 bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on fiber space arguments

  require(completed_space_path_is_available<F>(xfiber_space_path, xauto_access));
  require(completed_schema_path_conforms_to<F>(xfiber_space_schema_path, xauto_access));
  require(args_conform_to_completed_schema_path<F>(xfiber_space_args, xfiber_space_schema_path, xauto_access));
  require(completed_p<F>(xfiber_space_path, xfiber_space_args, xauto_access) >= 0);
  
  // Conditions on vector space arguments.

  require(completed_vector_space_path_is_available<F>(xfiber_space_path,
						      xvector_space_path,
						      xfiber_space_args,
						      xauto_access));

  require(completed_schema_path_conforms_to<typename F::vector_space_type>\
	  (xvector_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename F::vector_space_type> \
	  (xvector_space_args, xvector_space_schema_path, xauto_access));  

  // Conditions on scalar space arguments:

  require(completed_tensor_scalar_space_path_is_available<F>(xfiber_space_path,
							     xvector_space_path,
							     xfiber_space_args,
							     xscalar_space_path,
							     xvector_space_args,
							     xauto_access));

  require(completed_schema_path_conforms_to<typename F::scalar_type>\
	  (xscalar_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename F::scalar_type> \
	  (xscalar_space_args, xscalar_space_schema_path, xauto_access));
  
  // Body:

  // Complete the various paths.

  const poset_path lfiber_space_path = 
    completed_space_path<F>(xfiber_space_path);

  const poset_path lfiber_space_schema_path = 
    completed_schema_path<F>(xfiber_space_schema_path);

  const poset_path lvector_space_path = 
    completed_vector_space_path<F>(xfiber_space_path,
				   xvector_space_path,
				   xfiber_space_args,
				   xauto_access);

  const poset_path lvector_space_schema_path = 
    completed_schema_path<typename F::vector_space_type>(xvector_space_schema_path);

  const poset_path lscalar_space_path = 
    completed_tensor_scalar_space_path<F>(xfiber_space_path,
					  xvector_space_path,
					  xfiber_space_args,
					  xscalar_space_path,
					  xvector_space_args,
					  xauto_access);

  const poset_path lscalar_space_schema_path = 
    completed_schema_path<typename F::scalar_type>(xscalar_space_schema_path);

  // Find or create the result.
  
  typedef typename F::host_type host_type;
  typedef typename F::vector_space_type vector_type;
  typedef typename F::vector_space_type::host_type vector_host_type;

  host_type* lresult_ptr;

  if(contains_poset(lfiber_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.
    
    lresult_ptr = &member_poset<host_type>(lfiber_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    // First, find or create the vector space.

    vector_host_type& lvector_space =
      new_vector_space<vector_type>(lvector_space_path,
				    xvector_space_args,
				    lvector_space_schema_path,
				    lscalar_space_path,
				    xscalar_space_args,
				    lscalar_space_schema_path,
				    xauto_access);

    // Initialize arg list if necessary.

    arg_list lfiber_space_args(xfiber_space_args);
    if(lfiber_space_args.empty())
    {
      lfiber_space_args = host_type::make_arg_list(F::P, "");
    }
    lfiber_space_args.value("vector_space_path") = lvector_space.path(xauto_access);

    lresult_ptr = new host_type(*this,
				lfiber_space_path.poset_name(),
				lfiber_space_args,
				lfiber_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;


  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_group_space(const poset_path& xfiber_space_path,
		const arg_list& xfiber_space_args,
		const poset_path& xfiber_space_schema_path,
		const poset_path& xvector_space_path,
		const arg_list& xvector_space_args,
		const poset_path& xvector_space_schema_path,
		const poset_path& xscalar_space_path,
		const arg_list& xscalar_space_args,
		const poset_path& xscalar_space_schema_path,
		bool xauto_access)

{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on fiber space arguments

  require(completed_space_path_is_available<F>(xfiber_space_path, xauto_access));
  require(completed_schema_path_conforms_to<F>(xfiber_space_schema_path, xauto_access));
  require(args_conform_to_completed_schema_path<F>(xfiber_space_args, xfiber_space_schema_path, xauto_access));
  
  // Conditions on vector space arguments.

  require(completed_vector_space_path_is_available<F>(xfiber_space_path,
						      xvector_space_path,
						      xfiber_space_args,
						      xauto_access));

  require(completed_schema_path_conforms_to<typename F::vector_space_type>\
	  (xvector_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename F::vector_space_type> \
	  (xvector_space_args, xvector_space_schema_path, xauto_access));  

  // Conditions on scalar space arguments:

  require(completed_tensor_scalar_space_path_is_available<F>(xfiber_space_path,
							     xvector_space_path,
							     xfiber_space_args,
							     xscalar_space_path,
							     xvector_space_args,
							     xauto_access));

  require(completed_schema_path_conforms_to<typename F::scalar_type>\
	  (xscalar_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename F::scalar_type> \
	  (xscalar_space_args, xscalar_space_schema_path, xauto_access));
  
  // Body:

  // Complete the various paths.

  const poset_path lfiber_space_path = 
    completed_space_path<F>(xfiber_space_path);

  const poset_path lfiber_space_schema_path = 
    completed_schema_path<F>(xfiber_space_schema_path);

  const poset_path lvector_space_path = 
    completed_vector_space_path<F>(xfiber_space_path,
				   xvector_space_path,
				   xfiber_space_args,
				   xauto_access);

  const poset_path lvector_space_schema_path = 
    completed_schema_path<typename F::vector_space_type>(xvector_space_schema_path);

  const poset_path lscalar_space_path = 
    completed_tensor_scalar_space_path<F>(xfiber_space_path,
					  xvector_space_path,
					  xfiber_space_args,
					  xscalar_space_path,
					  xvector_space_args,
					  xauto_access);

  const poset_path lscalar_space_schema_path = 
    completed_schema_path<typename F::scalar_type>(xscalar_space_schema_path);

  // Find or create the result.
  
  typedef typename F::host_type host_type;
  typedef typename F::vector_space_type vector_type;
  typedef typename F::vector_space_type::host_type vector_host_type;

  host_type* lresult_ptr;

  if(contains_poset(lfiber_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.
    
    lresult_ptr = &member_poset<host_type>(lfiber_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    // First, find or create the vector space.

    vector_host_type& lvector_space =
      new_vector_space<vector_type>(lvector_space_path,
				    xvector_space_args,
				    lvector_space_schema_path,
				    lscalar_space_path,
				    xscalar_space_args,
				    lscalar_space_schema_path,
				    xauto_access);

    // Initialize arg list if necessary.

    arg_list lfiber_space_args(xfiber_space_args);
    if(lfiber_space_args.empty())
    {
      lfiber_space_args = host_type::make_arg_list(0, "", "");
    }
    lfiber_space_args.value("vector_space_path") = lvector_space.path(xauto_access);

    lresult_ptr = new host_type(*this,
				lfiber_space_path.poset_name(),
				lfiber_space_args,
				lfiber_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;


  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_jacobian_space(const poset_path& xfiber_space_path,
		   const arg_list& xfiber_space_args,
		   const poset_path& xfiber_space_schema_path,
		   const poset_path& xdomain_space_path,
		   const arg_list& xdomain_space_args,
		   const poset_path& xdomain_space_schema_path,
		   const poset_path& xrange_space_path,
		   const arg_list& xrange_space_args,
		   const poset_path& xrange_space_schema_path,
		   const poset_path& xscalar_space_path,
		   const arg_list& xscalar_space_args,
		   const poset_path& xscalar_space_schema_path,
		   bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on fiber space arguments

  require(completed_space_path_is_available<F>(xfiber_space_path, xauto_access));
  require(completed_schema_path_conforms_to<F>(xfiber_space_schema_path, xauto_access));
  require(args_conform_to_completed_schema_path<F>(xfiber_space_args, xfiber_space_schema_path, xauto_access));
  
  // Conditions on domain space arguments.

  require(completed_domain_space_path_is_available<F>(xfiber_space_path,
						      xdomain_space_path,
						      xfiber_space_args,
						      xauto_access));

  require(completed_schema_path_conforms_to<typename F::domain_type>\
	  (xdomain_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename F::domain_type> \
	  (xdomain_space_args, xdomain_space_schema_path, xauto_access));  

  
  // Conditions on range space arguments.

  require(completed_range_space_path_is_available<F>(xfiber_space_path,
						      xrange_space_path,
						      xfiber_space_args,
						      xauto_access));

  require(completed_schema_path_conforms_to<typename F::range_type>\
	  (xrange_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename F::range_type> \
	  (xrange_space_args, xrange_space_schema_path, xauto_access));  

  // Conditions on scalar space arguments:

  require(completed_jacobian_scalar_space_path_is_available<F>(xfiber_space_path,
							       xdomain_space_path,
							       xfiber_space_args,
							       xscalar_space_path,
							       xdomain_space_args,
							       xauto_access));

  require(completed_schema_path_conforms_to<typename F::scalar_type>\
	  (xscalar_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename F::scalar_type> \
	  (xscalar_space_args, xscalar_space_schema_path, xauto_access));
  
  // Body:

  // Complete the various paths.

  const poset_path lfiber_space_path = 
    completed_space_path<F>(xfiber_space_path);

  const poset_path lfiber_space_schema_path = 
    completed_schema_path<F>(xfiber_space_schema_path);

  const poset_path ldomain_space_path = 
    completed_domain_space_path<F>(xfiber_space_path,
				   xdomain_space_path,
				   xfiber_space_args,
				   xauto_access);

  const poset_path ldomain_space_schema_path = 
    completed_schema_path<typename F::domain_type>(xdomain_space_schema_path);

  const poset_path lrange_space_path = 
    completed_range_space_path<F>(xfiber_space_path,
				  xrange_space_path,
				  xfiber_space_args,
				  xauto_access);

  const poset_path lrange_space_schema_path = 
    completed_schema_path<typename F::range_type>(xrange_space_schema_path);

  const poset_path lscalar_space_path = 
    completed_jacobian_scalar_space_path<F>(xfiber_space_path,
					    xdomain_space_path,
					    xfiber_space_args,
					    xscalar_space_path,
					    xdomain_space_args,
					    xauto_access);

  const poset_path lscalar_space_schema_path = 
    completed_schema_path<typename F::scalar_type>(xscalar_space_schema_path);

  // Find or create the result.
  
  typedef typename F::host_type host_type;
  typedef typename F::domain_type domain_type;
  typedef typename F::domain_type::host_type domain_host_type;
  typedef typename F::range_type range_type;
  typedef typename F::range_type::host_type range_host_type;

  host_type* lresult_ptr;

  if(contains_poset(lfiber_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.
    
    lresult_ptr = &member_poset<host_type>(lfiber_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    // First, find or create the domain space.

    domain_host_type& ldomain_space =
      new_vector_space<domain_type>(ldomain_space_path,
				    xdomain_space_args,
				    ldomain_space_schema_path,
				    lscalar_space_path,
				    xscalar_space_args,
				    lscalar_space_schema_path,
				    xauto_access);

    // Second, find or create the range space.

    range_host_type& lrange_space =
      new_vector_space<range_type>(lrange_space_path,
				   xrange_space_args,
				   lrange_space_schema_path,
				   lscalar_space_path,
				   xscalar_space_args,
				   lscalar_space_schema_path,
				   xauto_access);

    // Initialize arg list if necessary.

    arg_list lfiber_space_args(xfiber_space_args);
    if(lfiber_space_args.empty())
    {
      lfiber_space_args = host_type::make_arg_list("", "");
    }
    lfiber_space_args.value("domain_path") = ldomain_space.path(xauto_access);
    lfiber_space_args.value("range_path") = lrange_space.path(xauto_access);

    lresult_ptr = new host_type(*this,
				lfiber_space_path.poset_name(),
				lfiber_space_args,
				lfiber_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;


  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename F>
typename F::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tuple_space(const poset_path& xfiber_space_path,
		const arg_list& xfiber_space_args,
		const poset_path& xfiber_space_schema_path,
		bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on fiber space arguments

  require(completed_space_path_is_available<F>(xfiber_space_path, xauto_access));
  require(completed_schema_path_conforms_to<F>(xfiber_space_schema_path, xauto_access));
  require(args_conform_to_completed_schema_path<F>(xfiber_space_args, xfiber_space_schema_path, xauto_access));

  // Body:

  // Complete the various paths.

  const poset_path lfiber_space_path = 
    completed_space_path<F>(xfiber_space_path);

  const poset_path lfiber_space_schema_path = 
    completed_schema_path<F>(xfiber_space_schema_path);

  // Find or create the result.
  
  typedef typename F::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset(lfiber_space_path, xauto_access))
  {
    // Fiber space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lfiber_space_path, xauto_access);
  }
  else
  {
    // Fiber space doesn't exist; create it.

    // Initialize the arg list if needed.

    arg_list lfiber_space_args(xfiber_space_args);
    if(lfiber_space_args.empty())
    {
      lfiber_space_args = host_type::make_arg_list(F::FACTOR_CT);
    }

    lresult_ptr = new host_type(*this,
				lfiber_space_path.poset_name(),
				lfiber_space_args,
				lfiber_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION SPACE SCHEMA FACTORY METHOD FACET
// ===========================================================

// Template specializations required by new_section_space_schema.

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema_impl<fiber_bundle::sec_at0_space>
{
  template <typename section_type>
  static poset_path new_space(fiber_bundles_namespace& xns,
			      const poset_path& xsection_space_schema_path,
			      const arg_list& xsection_space_schema_args,
			      const poset_path& xsection_space_schema_schema_path,
			      const poset_path& xrep_path,
			      const poset_path& xbase_space_path,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_scalar_section_space_schema<section_type>(xsection_space_schema_path,
							     xsection_space_schema_args,
							     xsection_space_schema_schema_path,
							     xrep_path,
							     xbase_space_path,
							     xfiber_space_path,
							     xfiber_space_args,
							     xfiber_space_schema_path,
							     xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema_impl<fiber_bundle::sec_at1_space>
{
  template <typename section_type>
  static poset_path new_space(fiber_bundles_namespace& xns,
			      const poset_path& xsection_space_schema_path,
			      const arg_list& xsection_space_schema_args,
			      const poset_path& xsection_space_schema_schema_path,
			      const poset_path& xrep_path,
			      const poset_path& xbase_space_path,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_vector_section_space_schema<section_type>(xsection_space_schema_path,
							     xsection_space_schema_args,
							     xsection_space_schema_schema_path,
							     xrep_path,
							     xbase_space_path,
							     xfiber_space_path,
							     xfiber_space_args,
							     xfiber_space_schema_path,
							     "",
							     "",
							     "",
							     xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema_impl<fiber_bundle::sec_atp_space>
{
  template <typename section_type>
  static poset_path new_space(fiber_bundles_namespace& xns,
			      const poset_path& xsection_space_schema_path,
			      const arg_list& xsection_space_schema_args,
			      const poset_path& xsection_space_schema_schema_path,
			      const poset_path& xrep_path,
			      const poset_path& xbase_space_path,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_tensor_section_space_schema<section_type>(xsection_space_schema_path,
							     xsection_space_schema_args,
							     xsection_space_schema_schema_path,
							     xrep_path,
							     xbase_space_path,
							     xfiber_space_path,
							     xfiber_space_args,
							     xfiber_space_schema_path,
							     "",
							     "",
							     "",
							     "",
							     "",
							     "",
							     xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema_impl<fiber_bundle::sec_stp_space>
{
  template <typename section_type>
  static poset_path new_space(fiber_bundles_namespace& xns,
			      const poset_path& xsection_space_schema_path,
			      const arg_list& xsection_space_schema_args,
			      const poset_path& xsection_space_schema_schema_path,
			      const poset_path& xrep_path,
			      const poset_path& xbase_space_path,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_tensor_section_space_schema<section_type>(xsection_space_schema_path,
							     xsection_space_schema_args,
							     xsection_space_schema_schema_path,
							     xrep_path,
							     xbase_space_path,
							     xfiber_space_path,
							     xfiber_space_args,
							     xfiber_space_schema_path,
							     "",
							     "",
							     "",
							     "",
							     "",
							     "",
							     xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema_impl<fiber_bundle::sec_tp_space>
{
  template <typename section_type>
  static poset_path new_space(fiber_bundles_namespace& xns,
			      const poset_path& xsection_space_schema_path,
			      const arg_list& xsection_space_schema_args,
			      const poset_path& xsection_space_schema_schema_path,
			      const poset_path& xrep_path,
			      const poset_path& xbase_space_path,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_tensor_section_space_schema<section_type>(xsection_space_schema_path,
							     xsection_space_schema_args,
							     xsection_space_schema_schema_path,
							     xrep_path,
							     xbase_space_path,
							     xfiber_space_path,
							     xfiber_space_args,
							     xfiber_space_schema_path,
							     "",
							     "",
							     "",
							     "",
							     "",
							     "",
							     xauto_access);
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema_impl<fiber_bundle::sec_tuple_space>
{
  template <typename section_type>
  static poset_path new_space(fiber_bundles_namespace& xns,
			      const poset_path& xsection_space_schema_path,
			      const arg_list& xsection_space_schema_args,
			      const poset_path& xsection_space_schema_schema_path,
			      const poset_path& xrep_path,
			      const poset_path& xbase_space_path,
			      const poset_path& xfiber_space_path,
			      const arg_list& xfiber_space_args,
			      const poset_path& xfiber_space_schema_path,
			      bool xauto_access)
  {
    return xns.new_tuple_section_space_schema<section_type>(xsection_space_schema_path,
							    xsection_space_schema_args,
							    xsection_space_schema_schema_path,
							    xrep_path,
							    xbase_space_path,
							    xfiber_space_path,
							    xfiber_space_args,
							    xfiber_space_schema_path,
							    "",
							    "",
							    "",
							    "",
							    "",
							    "",
							    xauto_access);
  };
};

// PUBLIC MEMBER FUNCTIONS



template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema(const poset_path& xsection_space_schema_path,
			 const arg_list& xsection_space_schema_args,
			 const poset_path& xsection_space_schema_schema_path,
			 const poset_path& xrep_path,
			 const poset_path& xbase_space_path,
			 const poset_path& xfiber_space_path,
			 const arg_list& xfiber_space_args,
			 const poset_path& xfiber_space_schema_path,
			 bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on xsection_space_schema_path:

  require(completed_section_space_schema_path_is_available<S>\
	  (xsection_space_schema_path, 
	   xrep_path, 
	   xbase_space_path, 
	   xfiber_space_path, 
	   xsection_space_schema_args, 
	   xauto_access));

  // Conditions on xsection_space_schema_schema_path:

  require(completed_schema_path_conforms_to<binary_section_space_schema_poset>\
	  (xsection_space_schema_schema_path, xauto_access));

  // Conditions on xsection_space_schema_args:

  require(args_conform_to_completed_schema_path<binary_section_space_schema_poset>\
	  (xsection_space_schema_args, xsection_space_schema_schema_path, xauto_access));

  // Conditions on xrep_path:

  require(completed_rep_path_is_accessible<S>(xsection_space_schema_path,
					      xrep_path,
					      xbase_space_path,
					      xfiber_space_path,
					      xsection_space_schema_args,
					      xauto_access));
  
  // Conditions on xbase_space_path:

  require(completed_base_space_path_is_accessible<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  // Conditions on xfiber_space_path:

  require(completed_fiber_space_path_is_available<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  // Conditions on xfiber_space_schema_path:
  
  require(completed_schema_path_conforms_to<typename S::fiber_type>(xfiber_space_schema_path, xauto_access));

  // Conditions on xfiber_space_args:  

  require(args_conform_to_completed_schema_path<typename S::fiber_type> \
	  (xfiber_space_args, xfiber_space_schema_path, xauto_access));


  // Body:

  typedef typename S::host_type host_type;
  typedef new_section_space_schema_impl<host_type> impl_type;

  // Find or create the result.
  
  
  // Call to function template member of template
  // requires telling compiler that dependent name is a template.

  poset_path result = impl_type::template new_space<S>(*this,
						       xsection_space_schema_path,
						       xsection_space_schema_args,
						       xsection_space_schema_schema_path,
						       xrep_path,
						       xbase_space_path,
						       xfiber_space_path,
						       xfiber_space_args,
						       xfiber_space_schema_path,
						       xauto_access);
  
  // Postconditions:

  ensure(contains_poset_member(result, xauto_access));
  
  // Exit:

  return result;
}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_scalar_section_space_schema(const poset_path& xsection_space_schema_path,
				const arg_list& xsection_space_schema_args,
				const poset_path& xsection_space_schema_schema_path,
				const poset_path& xrep_path,
				const poset_path& xbase_space_path,
				const poset_path& xfiber_space_path,
				const arg_list& xfiber_space_args,
				const poset_path& xfiber_space_schema_path,
				bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on xsection_space_schema_path:

  require(completed_section_space_schema_path_is_available<S>\
	  (xsection_space_schema_path, 
	   xrep_path, 
	   xbase_space_path, 
	   xfiber_space_path, 
	   xsection_space_schema_args, 
	   xauto_access));

  // Conditions on xsection_space_schema_schema_path:

  require(completed_schema_path_conforms_to<binary_section_space_schema_poset>\
	  (xsection_space_schema_schema_path, xauto_access));

  // Conditions on xsection_space_schema_args:

  require(args_conform_to_completed_schema_path<binary_section_space_schema_poset>\
	  (xsection_space_schema_args, xsection_space_schema_schema_path, xauto_access));

  // Conditions on xrep_path:

  require(completed_rep_path_is_accessible<S>(xsection_space_schema_path,
					      xrep_path,
					      xbase_space_path,
					      xfiber_space_path,
					      xsection_space_schema_args,
					      xauto_access));
  
  // Conditions on xbase_space_path:

  require(completed_base_space_path_is_accessible<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  // Conditions on xfiber_space_path:

  require(completed_fiber_space_path_is_available<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  // Conditions on xfiber_space_schema_path:
  
  require(completed_schema_path_conforms_to<typename S::fiber_type>(xfiber_space_schema_path, xauto_access));

  // Conditions on xfiber_space_args:  

  require(args_conform_to_completed_schema_path<typename S::fiber_type> \
	  (xfiber_space_args, xfiber_space_schema_path, xauto_access));


  // Body:

  typedef typename S::fiber_type fiber_type;
  typedef typename S::fiber_type::host_type fiber_host_type;
  typedef binary_section_space_schema_poset schema_host_type;
  typedef binary_section_space_schema_member schema_mbr_type;

  // Complete the various paths.

  poset_path lsection_space_schema_path = 
    completed_section_space_schema_path<S>(xsection_space_schema_path, 
					   xrep_path, 
					   xbase_space_path, 
					   xfiber_space_path,
					   xsection_space_schema_args,
					   xauto_access);
  
  poset_path lsection_space_schema_schema_path = 
    completed_schema_path<schema_host_type>(xsection_space_schema_schema_path);

  poset_path lrep_path = 
    completed_rep_path<S>(xsection_space_schema_path, 
			  xrep_path, 
			  xsection_space_schema_args, 
			  xauto_access);

  poset_path lbase_space_path = 
    completed_base_space_path(xsection_space_schema_path, 
			      xbase_space_path, 
			      xsection_space_schema_args, 
			      xauto_access);

  poset_path lfiber_space_path = 
    completed_fiber_space_path<S>(xsection_space_schema_path, 
				  xfiber_space_path, 
				  xsection_space_schema_args, 
				  xauto_access);

  poset_path lfiber_space_schema_path = 
    completed_schema_path<fiber_type>(xfiber_space_schema_path);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "In new_scalar_section_space_schema:" << endl;
  cout << "\tcompleted_section_space_schema_path: " << lsection_space_schema_path << endl;
  cout << "\tcompleted_section_space_schema_schema_path: " << lsection_space_schema_schema_path << endl;
  cout << "\tcompleted_rep_path: " << lrep_path << endl;
  cout << "\tcompleted_base_space_path: " << lbase_space_path << endl;
  cout << "\tcompleted_fiber_space_path: " << lfiber_space_path << endl;
  cout << "\tcompleted_fiber_space_schema_path: " << lfiber_space_schema_path << endl;
#endif  
  
  // Find or create the result.
  
  poset_path result;

  if(contains_poset_member(lsection_space_schema_path, xauto_access))
  {
    // Section space schema exists; get it.

    result = lsection_space_schema_path;
  }
  else if(contains_poset(lsection_space_schema_path, xauto_access))
  {
    // Section space schema poset exists but not the member; create it.

    schema_host_type& lsssp = 
      reinterpret_cast<schema_host_type&>(member_poset(lsection_space_schema_path, xauto_access));

    lsssp.get_read_write_access();
    
    poset_path lactual_fiber_space_schema_path = lsssp.fiber_space().schema().path();
    
    schema_mbr_type lschema_mbr(&lsssp, lbase_space_path, lactual_fiber_space_schema_path);
    lschema_mbr.put_name(lsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp.release_access();
  }
  else
  {
    // Section space doesn't exist; create it.
  
    // First ensure the fiber space exists.

    fiber_host_type& lfiber_space = 
      new_scalar_space<fiber_type>(lfiber_space_path, 
				   xfiber_space_args, 
				   lfiber_space_schema_path, 
				   xauto_access);

    arg_list lsection_space_schema_args = 
	schema_host_type::make_arg_list(lrep_path, lbase_space_path, lfiber_space_path);

    // Create the schema poset.

    schema_host_type* lsssp = 
      new schema_host_type(*this,
			   lsection_space_schema_path.poset_name(),
			   lsection_space_schema_args,
			   lsection_space_schema_schema_path,
			   xauto_access);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lactual_fiber_space_schema_path = 
      lsssp->fiber_space().schema().path();
    
    schema_mbr_type lschema_mbr(lsssp, lbase_space_path, lactual_fiber_space_schema_path);
    lschema_mbr.put_name(lsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp->release_access();
  }

  // Postconditions:

  ensure(contains_poset_member(result, xauto_access));
  
  // Exit:

  return result;
}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema(const poset_path& xsection_space_schema_path,
				const arg_list& xsection_space_schema_args,
				const poset_path& xsection_space_schema_schema_path,
				const poset_path& xrep_path,
				const poset_path& xbase_space_path,
				const poset_path& xfiber_space_path,
				const arg_list& xfiber_space_args,
				const poset_path& xfiber_space_schema_path,
				const poset_path& xscalar_space_path,
				const arg_list& xscalar_space_args,
				const poset_path& xscalar_space_schema_path,
				bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on xsection_space_schema_path:

  require(completed_section_space_schema_path_is_available<S>\
	  (xsection_space_schema_path, 
	   xrep_path, 
	   xbase_space_path, 
	   xfiber_space_path, 
	   xsection_space_schema_args, 
	   xauto_access));

  // Conditions on xsection_space_schema_schema_path:

  require(completed_schema_path_conforms_to<binary_section_space_schema_poset>\
	  (xsection_space_schema_schema_path, xauto_access));

  // Conditions on xsection_space_schema_args:

  require(args_conform_to_completed_schema_path<binary_section_space_schema_poset>\
	  (xsection_space_schema_args, xsection_space_schema_schema_path, xauto_access));

  // Conditions on xrep_path:

  require(completed_rep_path_is_accessible<S>(xsection_space_schema_path,
					      xrep_path,
					      xbase_space_path,
					      xfiber_space_path,
					      xsection_space_schema_args,
					      xauto_access));
  
  // Conditions on xbase_space_path:

  require(completed_base_space_path_is_accessible<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  // Conditions on xfiber_space_path:

  require(completed_fiber_space_path_is_available<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  // Conditions on xfiber_space_schema_path:
  
  require(completed_schema_path_conforms_to<typename S::fiber_type>(xfiber_space_schema_path, xauto_access));

  // Conditions on xfiber_space_args:  

  require(args_conform_to_completed_schema_path<typename S::fiber_type> \
	  (xfiber_space_args, xfiber_space_schema_path, xauto_access));

  // Conditions on scalar space:

  require(completed_scalar_space_path_is_available<S>(xsection_space_schema_path,
						      xrep_path,
						      xbase_space_path,
						      xfiber_space_path,
						      xsection_space_schema_args,
						      xscalar_space_path,
						      xfiber_space_args,
						      xauto_access));

  require(completed_schema_path_conforms_to<typename S::fiber_type::scalar_type>\
	  (xscalar_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename S::fiber_type::scalar_type> \
	  (xscalar_space_args, xscalar_space_schema_path, xauto_access));

  // Body:

  typedef typename S::fiber_type fiber_type;
  typedef typename S::fiber_type::host_type fiber_host_type;
  typedef typename S::fiber_type::scalar_type scalar_type;
  typedef typename S::fiber_type::scalar_type::host_type scalar_host_type;
  typedef binary_section_space_schema_poset schema_host_type;
  typedef binary_section_space_schema_member schema_mbr_type;
  

  // Complete the various paths.

  poset_path lsection_space_schema_path = 
    completed_section_space_schema_path<S>(xsection_space_schema_path, 
					   xrep_path, 
					   xbase_space_path, 
					   xfiber_space_path,
					   xsection_space_schema_args,
					   xauto_access);
  
  poset_path lsection_space_schema_schema_path = 
    completed_schema_path<schema_host_type>(xsection_space_schema_schema_path);

  poset_path lrep_path = 
    completed_rep_path<S>(xsection_space_schema_path, 
			  xrep_path, 
			  xsection_space_schema_args, 
			  xauto_access);

  poset_path lbase_space_path = 
    completed_base_space_path(xsection_space_schema_path, 
			      xbase_space_path, 
			      xsection_space_schema_args, 
			      xauto_access);

  poset_path lfiber_space_path = 
    completed_fiber_space_path<S>(xsection_space_schema_path, 
				  xfiber_space_path, 
				  xsection_space_schema_args, 
				  xauto_access);

  poset_path lfiber_space_schema_path = 
    completed_schema_path<fiber_type>(xfiber_space_schema_path);

  poset_path lscalar_space_path = 
    completed_section_scalar_space_path<S>(xsection_space_schema_path, 
					   xfiber_space_path,
					   xsection_space_schema_args,
					   xscalar_space_path,
					   xfiber_space_args,
					   xauto_access);

  poset_path lscalar_space_schema_path = 
    completed_schema_path<scalar_type>(xscalar_space_schema_path);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "In new_vector_section_space_schema:" << endl;
  cout << "\tcompleted_section_space_schema_path: " << lsection_space_schema_path << endl;
  cout << "\tcompleted_section_space_schema_schema_path: " << lsection_space_schema_schema_path << endl;
  cout << "\tcompleted_rep_path: " << lrep_path << endl;
  cout << "\tcompleted_base_space_path: " << lbase_space_path << endl;
  cout << "\tcompleted_fiber_space_path: " << lfiber_space_path << endl;
  cout << "\tcompleted_fiber_space_schema_path: " << lfiber_space_schema_path << endl;
  cout << "\tcompleted_scalar_space_path: " << lscalar_space_path << endl;
  cout << "\tcompleted_scalar_space_schema_path: " << lscalar_space_schema_path << endl;
#endif  
  

  // Find or create the result.
  
  poset_path result;

  if(contains_poset_member(lsection_space_schema_path, xauto_access))
  {
    // Section space schema exists; get it.

    result = lsection_space_schema_path;
  }
  else if(contains_poset(lsection_space_schema_path, xauto_access))
  {
    // Section space schema poset exists but not the member; create it.

    schema_host_type& lsssp = 
      reinterpret_cast<schema_host_type&>(member_poset(lsection_space_schema_path, xauto_access));

    // Create the schema member.

    lsssp.get_read_write_access();
    
    poset_path lactual_fiber_space_schema_path = lsssp.fiber_space().schema().path();
    
    schema_mbr_type lschema_mbr(&lsssp, lbase_space_path, lactual_fiber_space_schema_path);
    lschema_mbr.put_name(lsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp.release_access();
  }
  else
  {
    // Section space doesn't exist; create it.
  
    // First ensure the fiber space exists.

    fiber_host_type& lfiber_space = 
      new_vector_space<fiber_type>(lfiber_space_path, 
				   xfiber_space_args, 
				   lfiber_space_schema_path,
				   lscalar_space_path,
				   xscalar_space_args,
				   lscalar_space_schema_path,
				   xauto_access);

    arg_list lsection_space_schema_args = 
	schema_host_type::make_arg_list(lrep_path, lbase_space_path, lfiber_space_path);

    // Create the schema poset.

    schema_host_type* lsssp = 
      new schema_host_type(*this,
			   lsection_space_schema_path.poset_name(),
			   lsection_space_schema_args,
			   lsection_space_schema_schema_path,
			   xauto_access);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lactual_fiber_space_schema_path = lsssp->fiber_space().schema().path();
    
    schema_mbr_type lschema_mbr(lsssp, lbase_space_path, lactual_fiber_space_schema_path);
    lschema_mbr.put_name(lsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp->release_access();
  }

  // Postconditions:

  ensure(contains_poset_member(result, xauto_access));
  
  // Exit:

  return result;
}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema(const poset_path& xsection_space_schema_path,
				const arg_list& xsection_space_schema_args,
				const poset_path& xsection_space_schema_schema_path,
				const poset_path& xrep_path,
				const poset_path& xbase_space_path,
				const poset_path& xfiber_space_path,
				const arg_list& xfiber_space_args,
				const poset_path& xfiber_space_schema_path,
				const poset_path& xvector_space_path,
				const arg_list& xvector_space_args,
				const poset_path& xvector_space_schema_path,
				const poset_path& xscalar_space_path,
				const arg_list& xscalar_space_args,
				const poset_path& xscalar_space_schema_path,
				bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on xsection_space_schema_path:

  require(completed_section_space_schema_path_is_available<S>\
	  (xsection_space_schema_path, 
	   xrep_path, 
	   xbase_space_path, 
	   xfiber_space_path, 
	   xsection_space_schema_args, 
	   xauto_access));

  // Conditions on xsection_space_schema_schema_path:

  require(completed_schema_path_conforms_to<binary_section_space_schema_poset>\
	  (xsection_space_schema_schema_path, xauto_access));

  // Conditions on xsection_space_schema_args:

  require(args_conform_to_completed_schema_path<binary_section_space_schema_poset>\
	  (xsection_space_schema_args, xsection_space_schema_schema_path, xauto_access));

  // Conditions on xrep_path:

  require(completed_rep_path_is_accessible<S>(xsection_space_schema_path,
					      xrep_path,
					      xbase_space_path,
					      xfiber_space_path,
					      xsection_space_schema_args,
					      xauto_access));
  
  // Conditions on xbase_space_path:

  require(completed_base_space_path_is_accessible<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  // Conditions on fiber space aguments:

  require(completed_fiber_space_path_is_available<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  require(completed_schema_path_conforms_to<typename S::fiber_type>(xfiber_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename S::fiber_type> \
	  (xfiber_space_args, xfiber_space_schema_path, xauto_access));

  require(completed_p<S>(xsection_space_schema_path,
			 xfiber_space_path,
			 xsection_space_schema_args,
			 xfiber_space_args,
			 xauto_access) >= 0);
 
  // Conditions on vector space:

  require(completed_vector_space_path_is_available<S>(xsection_space_schema_path,
						      xrep_path,
						      xbase_space_path,
						      xfiber_space_path,
						      xsection_space_schema_args,
						      xvector_space_path,
						      xfiber_space_args,
						      xauto_access));

  require(completed_schema_path_conforms_to<typename S::fiber_type::vector_space_type>\
	  (xvector_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename S::fiber_type::vector_space_type> \
	  (xvector_space_args, xvector_space_schema_path, xauto_access));

  // Conditions on scalar space:

  require(completed_scalar_space_path_is_available<S>(xsection_space_schema_path,
						      xrep_path,
						      xbase_space_path,
						      xfiber_space_path,
						      xsection_space_schema_args,
						      xvector_space_path,
						      xfiber_space_args,
						      xscalar_space_path,
						      xvector_space_args,
						      xauto_access));

  require(completed_schema_path_conforms_to<typename S::fiber_type::scalar_type>\
	  (xscalar_space_schema_path, xauto_access));

  require(args_conform_to_completed_schema_path<typename S::fiber_type::scalar_type> \
	  (xscalar_space_args, xscalar_space_schema_path, xauto_access));

  // Body:

  typedef typename S::fiber_type fiber_type;
  typedef typename S::fiber_type::host_type fiber_host_type;
  typedef typename S::fiber_type::vector_space_type vector_type;
  typedef typename S::fiber_type::vector_space_type::host_type vector_host_type;
  typedef typename S::fiber_type::scalar_type scalar_type;
  typedef typename S::fiber_type::scalar_type::host_type scalar_host_type;
  typedef binary_section_space_schema_poset schema_host_type;
  typedef binary_section_space_schema_member schema_mbr_type;

  // Complete the various paths.

  poset_path lsection_space_schema_path = 
    completed_section_space_schema_path<S>(xsection_space_schema_path, 
					   xrep_path, 
					   xbase_space_path, 
					   xfiber_space_path,
					   xsection_space_schema_args,
					   xauto_access);
  
  poset_path lsection_space_schema_schema_path = 
    completed_schema_path<schema_host_type>(xsection_space_schema_schema_path);

  poset_path lrep_path = 
    completed_rep_path<S>(xsection_space_schema_path, 
			  xrep_path, 
			  xsection_space_schema_args, 
			  xauto_access);

  poset_path lbase_space_path = 
    completed_base_space_path(xsection_space_schema_path, 
			      xbase_space_path, 
			      xsection_space_schema_args, 
			      xauto_access);

  poset_path lfiber_space_path = 
    completed_fiber_space_path<S>(xsection_space_schema_path, 
				  xfiber_space_path, 
				  xsection_space_schema_args, 
				  xauto_access);

  poset_path lfiber_space_schema_path = 
    completed_schema_path<fiber_type>(xfiber_space_schema_path);

  poset_path lvector_space_path = 
    completed_vector_space_path<S>(xsection_space_schema_path, 
				   xfiber_space_path,
				   xsection_space_schema_args,
				   xvector_space_path,
				   xfiber_space_args,
				   xauto_access);

  poset_path lvector_space_schema_path = 
    completed_schema_path<vector_type>(xvector_space_schema_path);

  poset_path lscalar_space_path = 
    completed_scalar_space_path<S>(xsection_space_schema_path, 
				   xfiber_space_path,
				   xsection_space_schema_args,
				   xvector_space_path,
				   xfiber_space_args,
				   xscalar_space_path, 
				   xfiber_space_args,
				   xauto_access);

  poset_path lscalar_space_schema_path = 
    completed_schema_path<scalar_type>(xscalar_space_schema_path);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "In new_tensor_section_space_schema:" << endl;
  cout << "\tcompleted_section_space_schema_path: " << lsection_space_schema_path << endl;
  cout << "\tcompleted_section_space_schema_schema_path: " << lsection_space_schema_schema_path << endl;
  cout << "\tcompleted_rep_path: " << lrep_path << endl;
  cout << "\tcompleted_base_space_path: " << lbase_space_path << endl;
  cout << "\tcompleted_fiber_space_path: " << lfiber_space_path << endl;
  cout << "\tcompleted_fiber_space_schema_path: " << lfiber_space_schema_path << endl;
  cout << "\tcompleted_vector_space_path: " << lvector_space_path << endl;
  cout << "\tcompleted_vector_space_schema_path: " << lvector_space_schema_path << endl;
  cout << "\tcompleted_scalar_space_path: " << lscalar_space_path << endl;
  cout << "\tcompleted_scalar_space_schema_path: " << lscalar_space_schema_path << endl;
#endif  
  

  // Find or create the result.
  
  poset_path result;

  if(contains_poset_member(lsection_space_schema_path, xauto_access))
  {
    // Section space schema exists; get it.

    result = lsection_space_schema_path;
  }
  else if(contains_poset(lsection_space_schema_path, xauto_access))
  {
    // Section space schema poset exists but not the member; create it.

    schema_host_type& lsssp = 
      reinterpret_cast<schema_host_type&>(member_poset(lsection_space_schema_path, xauto_access));

    // Create the schema member.

    lsssp.get_read_write_access();
    
    poset_path lactual_fiber_space_schema_path = lsssp.fiber_space().schema().path();
    
    schema_mbr_type lschema_mbr(&lsssp, lbase_space_path, lactual_fiber_space_schema_path);
    lschema_mbr.put_name(lsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp.release_access();
  }
  else
  {
    // Section space doesn't exist; create it.
  
    // First ensure the fiber space exists.

    fiber_host_type& lfiber_space = 
      new_tensor_space<fiber_type>(lfiber_space_path, 
				   xfiber_space_args, 
				   lfiber_space_schema_path,
				   lvector_space_path,
				   xvector_space_args,
				   lvector_space_schema_path,
				   lscalar_space_path,
				   xscalar_space_args,
				   lscalar_space_schema_path,
				   xauto_access);

    arg_list lsection_space_schema_args = 
	schema_host_type::make_arg_list(lrep_path, lbase_space_path, lfiber_space_path);

    // Create the schema poset.

    schema_host_type* lsssp = 
      new schema_host_type(*this,
			   lsection_space_schema_path.poset_name(),
			   lsection_space_schema_args,
			   lsection_space_schema_schema_path,
			   xauto_access);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lactual_fiber_space_schema_path = lsssp->fiber_space().schema().path();
    
    schema_mbr_type lschema_mbr(lsssp, lbase_space_path, lactual_fiber_space_schema_path);
    lschema_mbr.put_name(lsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp->release_access();
  }

  // Postconditions:

  ensure(contains_poset_member(result, xauto_access));
  
  // Exit:

  return result;
}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tuple_section_space_schema(const poset_path& xsection_space_schema_path,
			       const arg_list& xsection_space_schema_args,
			       const poset_path& xsection_space_schema_schema_path,
			       const poset_path& xrep_path,
			       const poset_path& xbase_space_path,
			       const poset_path& xfiber_space_path,
			       const arg_list& xfiber_space_args,
			       const poset_path& xfiber_space_schema_path,
			       bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace:

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on xsection_space_schema_path:

  require(completed_section_space_schema_path_is_available<S>\
	  (xsection_space_schema_path, 
	   xrep_path, 
	   xbase_space_path, 
	   xfiber_space_path, 
	   xsection_space_schema_args, 
	   xauto_access));

  // Conditions on xsection_space_schema_schema_path:

  require(completed_schema_path_conforms_to<binary_section_space_schema_poset>\
	  (xsection_space_schema_schema_path, xauto_access));

  // Conditions on xsection_space_schema_args:

  require(args_conform_to_completed_schema_path<binary_section_space_schema_poset>\
	  (xsection_space_schema_args, xsection_space_schema_schema_path, xauto_access));

  // Conditions on xrep_path:

  require(completed_rep_path_is_accessible<S>(xsection_space_schema_path,
					      xrep_path,
					      xbase_space_path,
					      xfiber_space_path,
					      xsection_space_schema_args,
					      xauto_access));
  
  // Conditions on xbase_space_path:

  require(completed_base_space_path_is_accessible<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  // Conditions on xfiber_space_path:

  require(completed_fiber_space_path_is_available<S>(xsection_space_schema_path,
						     xrep_path,
						     xbase_space_path,
						     xfiber_space_path,
						     xsection_space_schema_args,
						     xauto_access));

  // Conditions on xfiber_space_schema_path:
  
  require(completed_schema_path_conforms_to<typename S::fiber_type>(xfiber_space_schema_path, xauto_access));

  // Conditions on xfiber_space_args:  

  require(args_conform_to_completed_schema_path<typename S::fiber_type> \
	  (xfiber_space_args, xfiber_space_schema_path, xauto_access));

  // Body:

  typedef typename S::fiber_type fiber_type;
  typedef typename S::fiber_type::host_type fiber_host_type;
  typedef binary_section_space_schema_poset schema_host_type;
  typedef binary_section_space_schema_member schema_mbr_type;
  

  // Complete the various paths.

  poset_path lsection_space_schema_path = 
    completed_section_space_schema_path<S>(xsection_space_schema_path, 
					   xrep_path, 
					   xbase_space_path, 
					   xfiber_space_path,
					   xsection_space_schema_args,
					   xauto_access);
  
  poset_path lsection_space_schema_schema_path = 
    completed_schema_path<schema_host_type>(xsection_space_schema_schema_path);

  poset_path lrep_path = 
    completed_rep_path<S>(xsection_space_schema_path, 
			  xrep_path, 
			  xsection_space_schema_args, 
			  xauto_access);

  poset_path lbase_space_path = 
    completed_base_space_path(xsection_space_schema_path, 
			      xbase_space_path, 
			      xsection_space_schema_args, 
			      xauto_access);

  poset_path lfiber_space_path = 
    completed_fiber_space_path<S>(xsection_space_schema_path, 
				  xfiber_space_path, 
				  xsection_space_schema_args, 
				  xauto_access);

  poset_path lfiber_space_schema_path = 
    completed_schema_path<fiber_type>(xfiber_space_schema_path);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "In new_vector_section_space_schema:" << endl;
  cout << "\tcompleted_section_space_schema_path: " << lsection_space_schema_path << endl;
  cout << "\tcompleted_section_space_schema_schema_path: " << lsection_space_schema_schema_path << endl;
  cout << "\tcompleted_rep_path: " << lrep_path << endl;
  cout << "\tcompleted_base_space_path: " << lbase_space_path << endl;
  cout << "\tcompleted_fiber_space_path: " << lfiber_space_path << endl;
  cout << "\tcompleted_fiber_space_schema_path: " << lfiber_space_schema_path << endl;
#endif  

  // Find or create the result.
  
  poset_path result;

  if(contains_poset_member(lsection_space_schema_path, xauto_access))
  {
    // Section space schema exists; get it.

    result = lsection_space_schema_path;
  }
  else if(contains_poset(lsection_space_schema_path, xauto_access))
  {
    // Section space schema poset exists but not the member; create it.

    schema_host_type& lsssp = 
      reinterpret_cast<schema_host_type&>(member_poset(lsection_space_schema_path, xauto_access));

    // Create the schema member.

    lsssp.get_read_write_access();
    
    poset_path lactual_fiber_space_schema_path = lsssp.fiber_space().schema().path();
    
    schema_mbr_type lschema_mbr(&lsssp, lbase_space_path, lactual_fiber_space_schema_path);
    lschema_mbr.put_name(lsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp.release_access();
  }
  else
  {
    // Section space doesn't exist; create it.
  
    // First ensure the fiber space exists.

    fiber_host_type& lfiber_space = 
      new_tuple_space<fiber_type>(lfiber_space_path, xfiber_space_args, lfiber_space_schema_path, xauto_access);

    arg_list lsection_space_schema_args = 
	schema_host_type::make_arg_list(lrep_path, lbase_space_path, lfiber_space_path);

    // Create the schema poset.

    schema_host_type* lsssp = 
      new schema_host_type(*this,
			   lsection_space_schema_path.poset_name(),
			   lsection_space_schema_args,
			   lsection_space_schema_schema_path,
			   xauto_access);

    // Create the schema member.

    lsssp->get_read_write_access();
    
    poset_path lactual_fiber_space_schema_path = lsssp->fiber_space().schema().path();
    
    schema_mbr_type lschema_mbr(lsssp, lbase_space_path, lactual_fiber_space_schema_path);
    lschema_mbr.put_name(lsection_space_schema_path.member_name(), true, false);
    result = lschema_mbr.path(false);
    lschema_mbr.detach_from_state();

    lsssp->release_access();
  }

  // Postconditions:

  ensure(contains_poset_member(result, xauto_access));
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION SPACE FACTORY METHOD FACET
// ===========================================================

// Template specializations required by new_section_space.

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_impl<fiber_bundle::sec_at0_space>
{
  //
  // Finds or creates section space; preallocated schema version.
  //
  template <typename section_type>
  static sec_at0_space& new_space(fiber_bundles_namespace& xns,
				  const poset_path& xsection_space_path,
				  const arg_list& xsection_space_args,
				  const poset_path& xsection_space_schema_path,
				  bool xauto_access)
  {
    return xns.new_scalar_section_space<section_type>(xsection_space_path,
						      xsection_space_args,
						      xsection_space_schema_path,
						      xauto_access);
  };

  //
  // Finds or creates section space; auto-allocated schema version.
  //
  template <typename section_type>
  static sec_at0_space& new_space(fiber_bundles_namespace& xns,
				  const string& xname,
				  const poset_path& xbase_path,
				  const poset_path& xrep_path)
  {
    typedef binary_section_space_schema_poset schema_host_type;

    // Make the section space schema arguments.

    arg_list lsss_args = schema_host_type::make_arg_list(xrep_path, xbase_path, "");

    // Make the scalar section space schema.

    poset_path lscalar_schema_path =
      xns.new_scalar_section_space_schema<section_type>("", lsss_args);

    // Make the section space.

    sec_at0_space& result =
      xns.new_scalar_section_space<section_type>(xname, "",
						 lscalar_schema_path);

    return result;
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_impl<fiber_bundle::sec_at1_space>
{
  //
  // Finds or creates section space; preallocated schema version.
  //
  template <typename section_type>
  static sec_at1_space& new_space(fiber_bundles_namespace& xns,
				  const poset_path& xsection_space_path,
				  const arg_list& xsection_space_args,
				  const poset_path& xsection_space_schema_path,
				  bool xauto_access)
  {
    return xns.new_vector_section_space<section_type>(xsection_space_path,
						      xsection_space_args,
						      xsection_space_schema_path,
						      "",
						      "",
						      "",
						      xauto_access);
  };

  //
  // Finds or creates section space; auto-allocated schema version.
  //
  template <typename section_type>
  static sec_at1_space& new_space(fiber_bundles_namespace& xns,
				  const string& xname,
				  const poset_path& xbase_path,
				  const poset_path& xrep_path)
  {
    typedef typename section_type::scalar_type scalar_type;
    typedef binary_section_space_schema_poset schema_host_type;

    // Make the section space schema arguments.

    arg_list lsss_args = schema_host_type::make_arg_list(xrep_path, xbase_path, "");

    // Make the scalar section space schema.

    poset_path lscalar_schema_path =
      xns.new_scalar_section_space_schema<scalar_type>("", lsss_args);

    // Make the vector section space schema.

    poset_path lvector_schema_path =
      xns.new_vector_section_space_schema<section_type>("", lsss_args);

    // Make the section space.

    sec_at1_space& result =
      xns.new_vector_section_space<section_type>(xname, "",
						 lvector_schema_path,
						 "", "",
						 lscalar_schema_path);

    return result;
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_impl<fiber_bundle::sec_atp_space>
{
  //
  // Finds or creates section space; preallocated schema version.
  //
  template <typename section_type>
  static sec_atp_space& new_space(fiber_bundles_namespace& xns,
				  const poset_path& xsection_space_path,
				  const arg_list& xsection_space_args,
				  const poset_path& xsection_space_schema_path,
				  bool xauto_access)
  {
    return xns.new_tensor_section_space<section_type>(xsection_space_path,
						      xsection_space_args,
						      xsection_space_schema_path,
						      "",
						      "",
						      "",
						      "",
						      "",
						      "",
						      xauto_access);
  };

  //
  // Finds or creates section space; auto-allocated schema version.
  //
  template <typename section_type>
  static sec_atp_space& new_space(fiber_bundles_namespace& xns,
				  const string& xname,
				  const poset_path& xbase_path,
				  const poset_path& xrep_path)
  {
    typedef typename section_type::scalar_type scalar_type;
    typedef typename section_type::vector_space_type vector_type;
    typedef binary_section_space_schema_poset schema_host_type;

    // Make the section space schema arguments.

    arg_list lsss_args = schema_host_type::make_arg_list(xrep_path, xbase_path, "");

    // Make the scalar section space schema.

    poset_path lscalar_schema_path =
      xns.new_scalar_section_space_schema<scalar_type>("", lsss_args);

    // Make the vector section space schema.

    poset_path lvector_schema_path =
      xns.new_vector_section_space_schema<vector_type>("", lsss_args);

    // Make the tensor section space schema.

    poset_path ltensor_schema_path =
      xns.new_tensor_section_space_schema<section_type>("", lsss_args);

    // Make the section space.

    sec_atp_space& result =
      xns.new_tensor_section_space<section_type>(xname, "",
						 ltensor_schema_path,
						 "", "",
						 lvector_schema_path,
						 "", "",
						 lscalar_schema_path);

    return result;
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_impl<fiber_bundle::sec_stp_space>
{
  //
  // Finds or creates section space; preallocated schema version.
  //
  template <typename section_type>
  static sec_stp_space& new_space(fiber_bundles_namespace& xns,
				  const poset_path& xsection_space_path,
				  const arg_list& xsection_space_args,
				  const poset_path& xsection_space_schema_path,
				  bool xauto_access)
  {
    return xns.new_tensor_section_space<section_type>(xsection_space_path,
						      xsection_space_args,
						      xsection_space_schema_path,
						      "",
						      "",
						      "",
						      "",
						      "",
						      "",
						      xauto_access);
  };

  //
  // Finds or creates section space; auto-allocated schema version.
  //
  template <typename section_type>
  static sec_stp_space& new_space(fiber_bundles_namespace& xns,
				  const string& xname,
				  const poset_path& xbase_path,
				  const poset_path& xrep_path)
  {
    typedef typename section_type::scalar_type scalar_type;
    typedef typename section_type::vector_space_type vector_type;
    typedef binary_section_space_schema_poset schema_host_type;

    // Make the section space schema arguments.

    arg_list lsss_args = schema_host_type::make_arg_list(xrep_path, xbase_path, "");

    // Make the scalar section space schema.

    poset_path lscalar_schema_path =
      xns.new_scalar_section_space_schema<scalar_type>("", lsss_args);

    // Make the vector section space schema.

    poset_path lvector_schema_path =
      xns.new_vector_section_space_schema<vector_type>("", lsss_args);

    // Make the tensor section space schema.

    poset_path ltensor_schema_path =
      xns.new_tensor_section_space_schema<section_type>("", lsss_args);

    // Make the section space.

    sec_stp_space& result =
      xns.new_tensor_section_space<section_type>(xname, "",
						 ltensor_schema_path,
						 "", "",
						 lvector_schema_path,
						 "", "",
						 lscalar_schema_path);

    return result;
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_impl<fiber_bundle::sec_tp_space>
{
  //
  // Finds or creates section space; preallocated schema version.
  //
  template <typename section_type>
  static sec_tp_space& new_space(fiber_bundles_namespace& xns,
				 const poset_path& xsection_space_path,
				 const arg_list& xsection_space_args,
				 const poset_path& xsection_space_schema_path,
				 bool xauto_access)
  {
    return xns.new_tensor_section_space<section_type>(xsection_space_path,
						      xsection_space_args,
						      xsection_space_schema_path,
						      "",
						      "",
						      "",
						      "",
						      "",
						      "",
						      xauto_access);
  };

  //
  // Finds or creates section space; auto-allocated schema version.
  //
  template <typename section_type>
  static sec_tp_space& new_space(fiber_bundles_namespace& xns,
				 const string& xname,
				 const poset_path& xbase_path,
				 const poset_path& xrep_path)
  {
    typedef typename section_type::scalar_type scalar_type;
    typedef typename section_type::vector_space_type vector_type;
    typedef binary_section_space_schema_poset schema_host_type;

    // Make the section space schema arguments.

    arg_list lsss_args = schema_host_type::make_arg_list(xrep_path, xbase_path, "");

    // Make the scalar section space schema.

    poset_path lscalar_schema_path =
      xns.new_scalar_section_space_schema<scalar_type>("", lsss_args);

    // Make the vector section space schema.

    poset_path lvector_schema_path =
      xns.new_vector_section_space_schema<vector_type>("", lsss_args);

    // Make the tensor section space schema.

    poset_path ltensor_schema_path =
      xns.new_tensor_section_space_schema<section_type>("", lsss_args);

    // Make the section space.

    sec_tp_space& result =
      xns.new_tensor_section_space<section_type>(xname, "",
						 ltensor_schema_path,
						 "", "",
						 lvector_schema_path,
						 "", "",
						 lscalar_schema_path);

    return result;
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_impl<fiber_bundle::sec_vd_space>
{
  //
  // Finds or creates section space; preallocated schema version.
  //
  template <typename section_type>
  static sec_vd_space& new_space(fiber_bundles_namespace& xns,
				 const poset_path& xsection_space_path,
				 const arg_list& xsection_space_args,
				 const poset_path& xsection_space_schema_path,
				 bool xauto_access)
  {
    return xns.new_vector_section_space<section_type>(xsection_space_path,
						      xsection_space_args,
						      xsection_space_schema_path,
						      "",
						      "",
						      "",
						      xauto_access);
  };

  //
  // Finds or creates section space; auto-allocated schema version.
  //
  template <typename section_type>
  static sec_vd_space& new_space(fiber_bundles_namespace& xns,
				 const string& xname,
				 const poset_path& xbase_path,
				 const poset_path& xrep_path)
  {
    typedef typename section_type::scalar_type scalar_type;
    typedef binary_section_space_schema_poset schema_host_type;

    // Make the section space schema arguments.

    arg_list lsss_args = schema_host_type::make_arg_list(xrep_path, xbase_path, "");

    // Make the scalar section space schema.

    poset_path lscalar_schema_path =
      xns.new_scalar_section_space_schema<scalar_type>("", lsss_args);

    // Make the vector section space schema.

    poset_path lvector_schema_path =
      xns.new_vector_section_space_schema<section_type>("", lsss_args);

    // Make the section space.

    sec_vd_space& result =
      xns.new_vector_section_space<section_type>(xname, "",
						 lvector_schema_path,
						 "", "",
						 lscalar_schema_path);

    return result;
  };
};

template<>
struct 
fiber_bundle::fiber_bundles_namespace::
new_section_space_impl<fiber_bundle::sec_tuple_space>
{
  //
  // Finds or creates section space; preallocated schema version.
  //
  template <typename section_type>
  static sec_tuple_space& new_space(fiber_bundles_namespace& xns,
				    const poset_path& xsection_space_path,
				    const arg_list& xsection_space_args,
				    const poset_path& xsection_space_schema_path,
				    bool xauto_access)
  {
    return xns.new_tuple_section_space<section_type>(xsection_space_path,
						     xsection_space_args,
						     xsection_space_schema_path,
						     xauto_access);
  };

  //
  // Finds or creates section space; auto-allocated schema version.
  //
  template <typename section_type>
  static sec_tuple_space& new_space(fiber_bundles_namespace& xns,
				    const string& xname,
				    const poset_path& xbase_path,
				    const poset_path& xrep_path)
  {
    typedef typename section_type::scalar_type scalar_type;
    typedef binary_section_space_schema_poset schema_host_type;

    // Make the section space schema arguments.

    arg_list lsss_args = schema_host_type::make_arg_list(xrep_path, xbase_path, "");

    // Make the tuple section space schema.

    poset_path ltuple_schema_path =
      xns.new_tuple_section_space_schema<section_type>("", lsss_args);

    // Make the section space.

    sec_tuple_space& result =
      xns.new_tuple_section_space<section_type>(xname, "", ltuple_schema_path, true);

    return result;
  };
};


// PUBLIC MEMBER FUNCTIONS

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space(const poset_path& xsection_space_path,
		  const poset_path& xbase_space_path,
		  const poset_path& xrep_path,
		  bool xauto_access)
{
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on section space arguments

  require(completed_space_path_is_available<S>(xsection_space_path, xauto_access));

  /// @todo: finish preconditions for new_section_space(path, path, path, bool).

  // Body:

  typedef typename S::host_type host_type;
  typedef new_section_space_impl<host_type> impl_type;

  // Find or create the result.
  
  // Call to function template member of template
  // requires telling compiler that dependent name is a template.

  host_type& result = impl_type::template new_space<S>(*this,
						       xsection_space_path.poset_name(),
						       xbase_space_path,
						       xrep_path);
  
  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space(const poset_path& xsection_space_path,
		  const arg_list& xsection_space_args,
		  const poset_path& xsection_space_schema_path,
		  bool xauto_access)
{  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on section space arguments

  require(completed_space_path_is_available<S>(xsection_space_path, xauto_access));
  require(path_is_auto_read_accessible(xsection_space_schema_path, xauto_access));

  // ERROR  arg_list attaches to a schema_poset_member however 
  //        binary_section_space_schema_member redefines the dof_map()
  //        functions which are used by schema_poset_member::invariant().
  //        See issue COM-70

  //require(xsection_space_args.conforms_to(*this, xsection_space_schema_path, true, xauto_access));

  // Body:

  typedef typename S::host_type host_type;
  typedef new_section_space_impl<host_type> impl_type;

  // Find or create the result.
  
  // Call to function template member of template
  // requires telling compiler that dependent name is a template.

  host_type& result = impl_type::template new_space<S>(*this,
						       xsection_space_path,
						       xsection_space_args,
						       xsection_space_schema_path,
						       xauto_access);
  
  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_scalar_section_space(const poset_path& xscalar_space_path,
			 const arg_list& xscalar_space_args,
			 const poset_path& xscalar_space_schema_path,
			 bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on section space arguments

  require(completed_space_path_is_available<S>(xscalar_space_path, xauto_access));

  /// @todo Eencapsulated this precondition into a single function call.
  ///       See Issue COM-388.

  require(path_is_auto_read_accessible(completed_space_path<S>(xscalar_space_path), xauto_access) ||
	  path_is_auto_read_accessible(xscalar_space_schema_path, xauto_access));

  /// @error arg_list attaches to a schema_poset_member however 
  ///        binary_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xscalar_space_args.conforms_to(*this, xscalar_space_schema_path, true, xauto_access));

  // Body:

  // Complete the various paths.

  const poset_path lsection_space_path = 
    completed_space_path<S>(xscalar_space_path);

  // Find or create the result.
  
  typedef typename S::host_type host_type;

  host_type* lresult_ptr;

  if(contains_poset<host_type>(lsection_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lsection_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist; create it.

    // Initialize the arg list if needed.

    arg_list lsection_space_args(xscalar_space_args);
    if(lsection_space_args.empty())
    {
      lsection_space_args = host_type::make_arg_list("");
    }

    lresult_ptr = new host_type(*this,
				lsection_space_path.poset_name(),
				lsection_space_args,
				xscalar_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space(const poset_path& xvector_space_path,
			 const arg_list& xvector_space_args,
			 const poset_path& xvector_space_schema_path,
			 const poset_path& xscalar_space_path,
			 const arg_list& xscalar_space_args,
			 const poset_path& xscalar_space_schema_path,
			 bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on section space arguments

  require(completed_space_path_is_available<S>(xvector_space_path, xauto_access));

  /// @todo Eencapsulated this precondition into a single function call.
  ///       See Issue COM-388.

  require(path_is_auto_read_accessible(completed_space_path<S>(xvector_space_path), xauto_access) ||
	  path_is_auto_read_accessible(xvector_space_schema_path, xauto_access));

  /// @error arg_list attaches to a schema_poset_member however 
  ///        binary_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xvector_space_args.conforms_to(*this, xvector_space_schema_path, true, xauto_access));

  // Conditions on scalar space arguments:

  require(completed_scalar_space_path_is_available<S>(xvector_space_path,
						      xscalar_space_path,
						      xvector_space_args,
						      xauto_access));

  /// @todo Eencapsulated this precondition into a single function call.
  ///       See Issue COM-388.

  require(path_is_auto_read_accessible(completed_scalar_space_path<S>(xvector_space_path, xscalar_space_path, xvector_space_args, xauto_access), xauto_access) ||
	  path_is_auto_read_available(xscalar_space_schema_path, xauto_access));

  /// @error arg_list attaches to a schema_poset_member however 
  ///        binary_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xscalar_space_args.conforms_to(*this, xscalar_space_schema_path, true, xauto_access));

  // Body:

  // Complete the various paths.

  const poset_path lsection_space_path = 
    completed_space_path<S>(xvector_space_path);

  const poset_path lscalar_space_path = 
    completed_scalar_space_path<S>(xvector_space_path,
				   xscalar_space_path,
				   xvector_space_args,
				   xauto_access);

  // Find or create the result.
  
  typedef typename S::host_type host_type;
  typedef typename S::scalar_type scalar_type;
  typedef typename S::scalar_type::host_type scalar_host_type;
  typedef typename S::fiber_type::host_type fiber_host_type;

  host_type* lresult_ptr;

  if(contains_poset(lsection_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lsection_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist; create it.


    // First find  the scalar space schema or create it with 
    // the same rep, base, and scalar fiber as the vector space schema.

    binary_section_space_schema_member 
      lvector_space_schema(*this, xvector_space_schema_path, xauto_access);    
    
    lvector_space_schema.get_read_access();
    
    poset_path lrep_path = lvector_space_schema.rep().path();
    poset_path lbase_path = lvector_space_schema.base_space().path();

//     sec_at1_space& lvector_fiber_space = 
//       reinterpret_cast<sec_at1_space&>(lvector_space_schema.fiber_space());

    fiber_host_type& lvector_fiber_space = 
      reinterpret_cast<fiber_host_type&>(lvector_space_schema.fiber_space());
    
    poset_path lscalar_fiber_space_path = lvector_fiber_space.scalar_space_path();
    
    lvector_space_schema.release_access();
    lvector_space_schema.detach_from_state();

    poset_path lscalar_sssp = 
      new_scalar_section_space_schema<scalar_type>(xscalar_space_schema_path,
						   "",
						   "",
						   lrep_path,
						   lbase_path,
						   lscalar_fiber_space_path,
						   "",
						   "",
						   xauto_access);					   

    // Next find or create the scalar space.

    scalar_host_type& lscalar_space = 
      new_scalar_section_space<scalar_type>(lscalar_space_path,
					    xscalar_space_args,
					    lscalar_sssp,
					    xauto_access);

    // Then initialize the arg list if needed.

    arg_list lsection_space_args(xvector_space_args);
    if(lsection_space_args.empty())
    {
      lsection_space_args = host_type::make_arg_list("");
    }
    lsection_space_args.value("scalar_space_path") = lscalar_space.path(xauto_access);

    // Finally, create the vector section space.

    lresult_ptr = new host_type(*this,
				lsection_space_path.poset_name(),
				lsection_space_args,
				xvector_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space(const poset_path& xtensor_space_path,
			 const arg_list& xtensor_space_args,
			 const poset_path& xtensor_space_schema_path,
			 const poset_path& xvector_space_path,
			 const arg_list& xvector_space_args,
			 const poset_path& xvector_space_schema_path,
			 const poset_path& xscalar_space_path,
			 const arg_list& xscalar_space_args,
			 const poset_path& xscalar_space_schema_path,
			 bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on tensor space arguments

  require(completed_space_path_is_available<S>(xtensor_space_path, xauto_access));

  /// @todo Eencapsulated this precondition into a single function call.
  ///       See Issue COM-388.

  require(path_is_auto_read_accessible(completed_space_path<S>(xtensor_space_path), xauto_access) ||
	  path_is_auto_read_accessible(xtensor_space_schema_path, xauto_access));

  /// @error arg_list attaches to a schema_poset_member however 
  ///        binary_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xvector_space_args.conforms_to(*this, xtensor_space_schema_path, true, xauto_access));

  // Conditions on vector space arguments.

  require(completed_vector_space_path_is_available<S>(xtensor_space_path,
						      xvector_space_path,
						      xtensor_space_args,
						      xauto_access));

  /// @todo Eencapsulated this precondition into a single function call.
  ///       See Issue COM-388.

  require(path_is_auto_read_accessible(completed_vector_space_path<S>(xtensor_space_path, xvector_space_path, xtensor_space_args, xauto_access), xauto_access) ||
	  path_is_auto_read_available(xvector_space_schema_path, xauto_access));

  /// @error arg_list attaches to a schema_poset_member however 
  ///        binary_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xvector_space_args.conforms_to(*this, xvector_space_schema_path, true, xauto_access));

  // Conditions on scalar space arguments:

  require(completed_tensor_scalar_space_path_is_available<S>(xtensor_space_path,
							     xvector_space_path,
							     xtensor_space_args,
							     xscalar_space_path,
							     xvector_space_args,
							     xauto_access));

  /// @todo Eencapsulated this precondition into a single function call.
  ///       See Issue COM-388.

  require(path_is_auto_read_accessible(completed_tensor_scalar_space_path<S>(xtensor_space_path, xvector_space_path, xtensor_space_args, xscalar_space_path, xvector_space_args, xauto_access), xauto_access) ||
	  path_is_auto_read_available(xscalar_space_schema_path, xauto_access));

  /// @error arg_list attaches to a schema_poset_member however 
  ///        binary_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xvector_space_args.conforms_to(*this, xscalar_space_schema_path, true, xauto_access));
  
  // Body:

  // Complete the various paths.

  const poset_path ltensor_space_path = 
    completed_space_path<S>(xtensor_space_path);

  const poset_path lvector_space_path = 
    completed_vector_space_path<S>(xtensor_space_path,
				   xvector_space_path,
				   xtensor_space_args,
				   xauto_access);

  const poset_path lscalar_space_path = 
    completed_tensor_scalar_space_path<S>(xtensor_space_path,
					  xvector_space_path,
					  xtensor_space_args,
					  xscalar_space_path,
					  xvector_space_args,
					  xauto_access);

  // Find or create the result.
  
  typedef typename S::host_type host_type;
  typedef typename S::vector_space_type vector_type;
  typedef typename S::vector_space_type::host_type vector_host_type;

  host_type* lresult_ptr;

  if(contains_poset(ltensor_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.
    
    lresult_ptr = &member_poset<host_type>(ltensor_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist; create it.

    // First, find or create the vector space.

    vector_host_type& lvector_space =
      new_vector_section_space<vector_type>(lvector_space_path,
					    xvector_space_args,
					    xvector_space_schema_path,
					    lscalar_space_path,
					    xscalar_space_args,
					    xscalar_space_schema_path,
					    xauto_access);

    // Initialize arg list if necessary.

    arg_list ltensor_space_args(xtensor_space_args);
    if(ltensor_space_args.empty())
    {
      ltensor_space_args = host_type::make_arg_list(S::fiber_type::P, "");
    }
    ltensor_space_args.value("vector_space_path") = lvector_space.path(xauto_access);

    lresult_ptr = new host_type(*this,
				ltensor_space_path.poset_name(),
				ltensor_space_args,
				xtensor_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;


  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

template <typename S>
typename S::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tuple_section_space(const poset_path& xtuple_space_path,
			const arg_list& xtuple_space_args,
			const poset_path& xtuple_space_schema_path,
			bool xauto_access)
{
  
  // Preconditions:

  // Conditions on namespace.

  require(state_is_auto_read_write_accessible(xauto_access));

  // Conditions on section space arguments

  require(completed_space_path_is_available<S>(xtuple_space_path, xauto_access));
  require(path_is_auto_read_accessible(xtuple_space_schema_path, xauto_access));

  /// @error arg_list attaches to a schema_poset_member however 
  ///        binary_section_space_schema_member redefines the dof_map()
  ///        functions which are used by schema_poset_member::invariant().
  ///        See bug #0000401.

  //require(xtuple_space_args.conforms_to(*this, xtuple_space_schema_path, true, xauto_access));

  // Body:

  // Complete the various paths.

  const poset_path lsection_space_path = completed_space_path<S>(xtuple_space_path);

  // Find or create the result.
  
  typedef typename S::host_type host_type;
  typedef typename S::fiber_type::host_type fiber_host_type;

  host_type* lresult_ptr;

  if(contains_poset(lsection_space_path, xauto_access))
  {
    // Section space exists; precondition ensures it is the right type; get it.

    lresult_ptr = &member_poset<host_type>(lsection_space_path, xauto_access);
  }
  else
  {
    // Section space doesn't exist; create it.

    // Initialize the arg list if needed.

    arg_list lsection_space_args(xtuple_space_args);
    if(lsection_space_args.empty())
    {
      lsection_space_args = host_type::make_arg_list(S::fiber_type::FACTOR_CT);
    }

    // Create the tuple section space.

    lresult_ptr = new host_type(*this,
				lsection_space_path.poset_name(),
				lsection_space_args,
				xtuple_space_schema_path,
				xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(contains_poset(result.path(xauto_access), xauto_access));
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PATH COMPLETION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path(const poset_path& xpath) const
{
  // Preconditions:

  // Body:

  poset_path result = completed_full_path(xpath, "", S::standard_schema_path());
  
  // Postconditions:

  ensure(result == completed_full_path(xpath, "", S::standard_schema_path()));

  // Exit:

  return result;  

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FIBER/SECTION FACTORY METHOD PATH COMPLETION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path(const poset_path& xpath) const
{
  // Preconditions:

  // Body:

  poset_path result(xpath);
  if(result.empty())
  {
    result = S::static_class_name();
  }
  
  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;  

}

template <typename S>
int
fiber_bundle::fiber_bundles_namespace::
completed_p(const poset_path& xspace_path, 
	    const arg_list& xspace_args,
	    bool xauto_access) const
{
  // Preconditions:

  require(completed_space_path_is_available<S>(xspace_path, xauto_access));
  
  // Body:

  typedef typename S::host_type host_type;
  
  poset_path lspace_path = completed_space_path<S>(xspace_path);
  
  int result;
  if(contains_poset<host_type>(lspace_path, xauto_access))
  {
    result = member_poset<host_type>(lspace_path, xauto_access).p(xauto_access);
  }
  else if(xspace_args.contains_arg("p"))
  {
    result = xspace_args.value("p");
  }
  else
  {
    result = S::P;
  }
  
  // Postconditions:

  // Exit:

  return result;
}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path(const poset_path& xspace_path, 
			    const poset_path& xvector_space_path, 
			    const arg_list& xspace_args,
			    bool xauto_access) const
{
  // Preconditions:

  require(unexecutable("space type is_tensor_space"));

  // Body:

  poset_path lspace_path = completed_space_path<S>(xspace_path);  

  typedef typename S::host_type host_type;
  poset_path result;
  if(contains_poset<host_type>(lspace_path, xauto_access))
  {
    // Space already exists, get vector space.

    result = member_poset<host_type>(lspace_path, xauto_access).vector_space_path(xauto_access);
  }
  else
  {
    poset_path largs_path;
    if(xspace_args.contains_arg("vector_space_path"))
    {
      largs_path = xspace_args.value("vector_space_path");
    }

    poset_path ldefault_path(S::vector_space_type::static_class_name(), "");    
    result = completed_path(xvector_space_path, largs_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path(const poset_path& xspace_path, 
			    const poset_path& xscalar_space_path, 
			    const arg_list& xspace_args,
			    bool xauto_access) const
{
  // Preconditions:

  require(unexecutable("space type is_vector_space"));

  // Body:

  poset_path lspace_path = completed_space_path<S>(xspace_path);  

  typedef typename S::host_type host_type;
  typedef typename S::scalar_type scalar_type;

  poset_path result;
  if(contains_poset<host_type>(lspace_path, xauto_access))
  {
    // Space already exists, get scalar space.

    result = member_poset<host_type>(lspace_path, xauto_access).scalar_space_path(xauto_access);
  }
  else
  {
    poset_path largs_path;
    if(xspace_args.contains_arg("scalar_space_path"))
    {
      largs_path = xspace_args.value("scalar_space_path");
    }

    poset_path ldefault_path(scalar_type::static_class_name(), "");    
    result = completed_path(xscalar_space_path, largs_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path(const poset_path& xspace_path, 
				   const poset_path& xvector_space_path, 
				   const arg_list& xspace_args,
				   const poset_path& xscalar_space_path, 
				   const arg_list& xvector_space_args,
				   bool xauto_access) const
{
  // Preconditions:

  require(unexecutable("space type is_tensor_space"));

  // Body:

  poset_path lvector_space_path = 
    completed_vector_space_path<S>(xspace_path,
				   xvector_space_path,
				   xspace_args,
				   xauto_access);  

  typedef typename S::vector_space_type::host_type vector_host_type;
  poset_path result;
  if(contains_poset<vector_host_type>(lvector_space_path, xauto_access))
  {
    // Vector space already exists, get scalar space.

    result = member_poset<vector_host_type>(lvector_space_path, xauto_access).scalar_space_path(xauto_access);
  }
  else
  {
    typedef typename S::scalar_type scalar_type;

    poset_path largs_path;
    if(xvector_space_args.contains_arg("scalar_space_path"))
    {
      largs_path = xvector_space_args.value("scalar_space_path");
    }

    poset_path ldefault_path(scalar_type::static_class_name(), "");    
    result = completed_path(xscalar_space_path, largs_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename J>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path(const poset_path& xspace_path, 
				     const poset_path& xdomain_space_path, 
				     const arg_list& xspace_args,
				     const poset_path& xscalar_space_path, 
				     const arg_list& xdomain_space_args,
				     bool xauto_access) const
{
  // Preconditions:

  require(unexecutable("space type is_jacobian_space"));

  // Body:

  poset_path ldomain_space_path = 
    completed_domain_space_path<J>(xspace_path,
				   xdomain_space_path,
				   xspace_args,
				   xauto_access);  

  typedef typename J::domain_type::host_type domain_host_type;
  poset_path result;
  if(contains_poset<domain_host_type>(ldomain_space_path, xauto_access))
  {
    // Domain space already exists, get scalar space.

    result = member_poset<domain_host_type>(ldomain_space_path, xauto_access).scalar_space_path(xauto_access);
  }
  else
  {
    typedef typename J::scalar_type scalar_type;

    poset_path largs_path;
    if(xdomain_space_args.contains_arg("scalar_space_path"))
    {
      largs_path = xdomain_space_args.value("scalar_space_path");
    }

    poset_path ldefault_path(scalar_type::static_class_name(), "");    
    result = completed_path(xscalar_space_path, largs_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename J>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path(const poset_path& xspace_path, 
			    const poset_path& xdomain_space_path, 
			    const arg_list& xspace_args,
			    bool xauto_access) const
{
  // Preconditions:

  require(unexecutable("space type is_jacobian_space"));

  // Body:

  poset_path lspace_path = completed_space_path<J>(xspace_path);  

  typedef typename J::host_type host_type;
  poset_path result;
  if(contains_poset<host_type>(lspace_path, xauto_access))
  {
    // Space already exists, get domain space.

    result = member_poset<host_type>(lspace_path, xauto_access).domain_path(xauto_access);
  }
  else
  {
    poset_path largs_path;
    if(xspace_args.contains_arg("domain_path"))
    {
      largs_path = xspace_args.value("domain_path");
    }

    poset_path ldefault_path(J::domain_type::static_class_name(), "");    
    result = completed_path(xdomain_space_path, largs_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename J>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path(const poset_path& xspace_path, 
			   const poset_path& xrange_space_path, 
			   const arg_list& xspace_args,
			   bool xauto_access) const
{
  // Preconditions:

  require(unexecutable("space type is_jacobian_space"));

  // Body:

  poset_path lspace_path = completed_space_path<J>(xspace_path);  

  typedef typename J::host_type host_type;
  poset_path result;
  if(contains_poset<host_type>(lspace_path, xauto_access))
  {
    // Space already exists, get range space.

    result = member_poset<host_type>(lspace_path, xauto_access).range_path(xauto_access);
  }
  else
  {
    poset_path largs_path;
    if(xspace_args.contains_arg("range_path"))
    {
      largs_path = xspace_args.value("range_path");
    }

    poset_path ldefault_path(J::range_type::static_class_name(), "");    
    result = completed_path(xrange_space_path, largs_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION SCHEMA FACTORY METHOD PATH COMPLETION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path(const poset_path& xpath,
				    const poset_path& xrep_path,
				    const poset_path& xbase_space_path,
				    const poset_path& xfiber_space_path,
				    const arg_list& xargs,
				    bool xauto_access) const
{
  // Preconditions:

  //$$SCRIBBLE: Temporary test.
//   cout << "xpath.full() = " << boolalpha << xpath.full() << endl;
//   cout << "xbase_space_path.full() = " << boolalpha << xbase_space_path.full() << endl;
//   cout << "xargs.contains_arg(\"base_space_path\") = " << boolalpha << xargs.contains_arg("base_space_path") << endl;
//   cout << "poset_path(xargs.value(\"base_space_path\")).full() = " << boolalpha << poset_path(xargs.value("base_space_path")).full() << endl;

//   require(xpath.full() || xbase_space_path.full() || 
// 	  (xargs.contains_arg("base_space_path") && poset_path(xargs.value("base_space_path")).full()));
  
  // Body:

  poset_path result(xpath);
  if(!result.full())
  {
    typedef typename S::fiber_type fiber_type;
    
    poset_path lrep_path = 
      completed_rep_path<S>(xpath, xrep_path, xargs, xauto_access);

    poset_path lbase_space_path  
      = completed_base_space_path(xpath, xbase_space_path, xargs, xauto_access);

    poset_path lfiber_space_path = 
      completed_fiber_space_path<S>(xpath, xfiber_space_path, xargs, xauto_access);

    if(result.poset_name().empty())
    {

      string lposet_name =  
	lfiber_space_path.poset_name() + 
	"_on_" + 
	lbase_space_path.poset_name() +
	"_" +
	lrep_path.member_name() +
	"_schema";

      result.put_poset_name(lposet_name);
    }
    
    if(result.member_name().empty())
    {
      string lmember_name =
	lfiber_space_path.poset_name() + 
	"_on_" + 
	lbase_space_path.member_name();

      result.put_member_name(lmember_name);
    }    
  }
  
    
  // Postconditions:

  ensure(result.full());

  // Exit:

  return result;  

}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path(const poset_path& xsection_space_schema_path, 
		   const poset_path& xrep_path, 
		   const arg_list& xargs,
		   bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));

  // Body:

  typedef section_space_schema_poset schema_type;
  
  const poset_path& lsssp = xsection_space_schema_path;
  
  poset_path result;
  if(contains_poset<schema_type>(lsssp, xauto_access))
  {
    result = member_poset<schema_type>(lsssp, xauto_access).rep().path(xauto_access);
  }
  else
  {
    poset_path largs_rep_path;
    if(xargs.contains_arg("rep_path"))
    {
      largs_rep_path = xargs.value("rep_path");
    }
    
    result = completed_full_path(xrep_path, largs_rep_path, S::standard_rep_path());
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path(const poset_path& xsection_space_schema_path, 
			   const poset_path& xfiber_space_path, 
			   const arg_list& xargs,
			   bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));

  // Body:

  typedef section_space_schema_poset schema_type;
  
  const poset_path& lsssp = xsection_space_schema_path;
  
  poset_path result;
  if(contains_poset<schema_type>(lsssp, xauto_access))
  {
    result = member_poset<schema_type>(lsssp, xauto_access).fiber_space().path(xauto_access);
  }
  else
  {
    poset_path largs_fiber_space_path;
    if(xargs.contains_arg("fiber_space_path"))
    {
      largs_fiber_space_path = xargs.value("fiber_space_path");
    }
    poset_path ldefault_path(S::fiber_type::static_class_name(), "");    
    result = completed_path(xfiber_space_path, largs_fiber_space_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
int
fiber_bundle::fiber_bundles_namespace::
completed_p(const poset_path& xsection_space_schema_path, 
	    const poset_path& xfiber_space_path, 
	    const arg_list& xsection_space_schema_args,
	    const arg_list& xfiber_space_args,
	    bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));

  // Body:

  typedef typename S::fiber_type fiber_type;
  typedef typename S::fiber_type::host_type fiber_host_type;
  
  poset_path lfiber_space_path = 
    completed_fiber_space_path<S>(xsection_space_schema_path, 
				  xfiber_space_path, 
				  xsection_space_schema_args, 
				  xauto_access);
  
  int result;
  if(contains_poset<fiber_host_type>(lfiber_space_path, xauto_access))
  {
    result = member_poset<fiber_host_type>(lfiber_space_path, xauto_access).p(xauto_access);
  }
  else if(xfiber_space_args.contains_arg("p"))
  {
    result = xfiber_space_args.value("p");
  }
  else
  {
    result = fiber_type::P;
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path(const poset_path& xsection_space_schema_path, 
			    const poset_path& xfiber_space_path, 
			    const arg_list& xsection_space_schema_args,
			    const poset_path& xvector_space_path, 
			    const arg_list& xfiber_space_args,
			    bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require(unexecutable("fiber type is_tensor_space"));

  // Body:

  poset_path lfiber_space_path = 
    completed_fiber_space_path<S>(xsection_space_schema_path,
				  xfiber_space_path,
				  xsection_space_schema_args,
				  xauto_access);  

  typedef typename S::fiber_type::host_type host_type;
  poset_path result;
  if(contains_poset<host_type>(lfiber_space_path, xauto_access))
  {
    // Fiber space already exists, get vector space.

    result = member_poset<host_type>(lfiber_space_path, xauto_access).vector_space_path(xauto_access);
  }
  else
  {
    poset_path largs_path;
    if(xfiber_space_args.contains_arg("vector_space_path"))
    {
      largs_path = xfiber_space_args.value("vector_space_path");
    }

    poset_path ldefault_path(S::fiber_type::vector_space_type::static_class_name(), "");    
    result = completed_path(xvector_space_path, largs_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path(const poset_path& xsection_space_schema_path, 
				    const poset_path& xfiber_space_path, 
				    const arg_list& xsection_space_schema_args,
				    const poset_path& xscalar_space_path, 
				    const arg_list& xfiber_space_args,
				    bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require(unexecutable("fiber type is_vector_space"));

  // Body:

  poset_path lfiber_space_path = 
    completed_fiber_space_path<S>(xsection_space_schema_path,
				  xfiber_space_path,
				  xsection_space_schema_args,
				  xauto_access);  

  typedef typename S::fiber_type::host_type host_type;
  poset_path result;
  if(contains_poset<host_type>(lfiber_space_path, xauto_access))
  {
    // Fiber space already exists, get scalar space.

    result = member_poset<host_type>(lfiber_space_path, xauto_access).scalar_space_path(xauto_access);
  }
  else
  {
    typedef typename S::fiber_type::scalar_type scalar_type;

    poset_path largs_path;
    if(xfiber_space_args.contains_arg("scalar_space_path"))
    {
      largs_path = xfiber_space_args.value("scalar_space_path");
    }
    
    poset_path ldefault_path(scalar_type::static_class_name(), "");    
    result = completed_path(xscalar_space_path, largs_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path(const poset_path& xsection_space_schema_path, 
			    const poset_path& xfiber_space_path, 
			    const arg_list& xsection_space_schema_args,
			    const poset_path& xvector_space_path, 
			    const arg_list& xfiber_space_args,
			    const poset_path& xscalar_space_path, 
			    const arg_list& xvector_space_args,
			    bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require(unexecutable("fiber type is_tensor_space"));

  // Body:

  poset_path lvector_space_path = 
    completed_vector_space_path<S>(xsection_space_schema_path,
				  xfiber_space_path,
				  xsection_space_schema_args,
				  xvector_space_path,
				  xfiber_space_args,
				  xauto_access);  

  typedef typename S::fiber_type::vector_space_type::host_type host_type;
  poset_path result;
  if(contains_poset<host_type>(lvector_space_path, xauto_access))
  {
    // Vector space already exists, get scalar space.

    result = member_poset<host_type>(lvector_space_path, xauto_access).scalar_space_path(xauto_access);
  }
  else
  {
    typedef typename S::fiber_type::scalar_type scalar_type;

    poset_path largs_path;
    if(xvector_space_args.contains_arg("scalar_space_path"))
    {
      largs_path = xvector_space_args.value("scalar_space_path");
    }

    poset_path ldefault_path(scalar_type::static_class_name(), "");    
    result = completed_path(xscalar_space_path, largs_path, ldefault_path);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FIBER/SECTION FACTORY METHOD PATH AVAILABILITY QUERY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available(const poset_path& xspace_path, 
				  bool xauto_access) const
{
  // Preconditions:


  // Body:

  poset_path lspace_path = completed_space_path<S>(xspace_path);
    
  typedef typename S::host_type host_type;
  bool result = path_is_auto_read_available<host_type>(lspace_path, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available(const poset_path& xspace_path, 
					 const poset_path& xvector_space_path, 
					 const arg_list& xspace_args,
					 bool xauto_access) const
{
  // Preconditions:

  // Body:

  poset_path lvector_space_path = 
    completed_vector_space_path<S>(xspace_path, 
				   xvector_space_path, 
				   xspace_args, 
				   xauto_access);
    
  typedef typename S::vector_space_type::host_type vector_host_type;
  bool result = path_is_auto_read_available<vector_host_type>(lvector_space_path, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available(const poset_path& xspace_path, 
					 const poset_path& xscalar_space_path, 
					 const arg_list& xspace_args,
					 bool xauto_access) const
{
  // Preconditions:


  // Body:

  poset_path lscalar_space_path = 
    completed_scalar_space_path<S>(xspace_path, 
				   xscalar_space_path, 
				   xspace_args, 
				   xauto_access);
    
  typedef typename S::scalar_type::host_type scalar_host_type;
  bool result = path_is_auto_read_available<scalar_host_type>(lscalar_space_path, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available(const poset_path& xspace_path, 
						const poset_path& xvector_space_path, 
						const arg_list& xspace_args,
						const poset_path& xscalar_space_path, 
						const arg_list& xvector_space_args,
						bool xauto_access) const
{
  // Preconditions:


  // Body:

  poset_path lscalar_space_path = 
    completed_tensor_scalar_space_path<S>(xspace_path, 
					  xvector_space_path, 
					  xspace_args, 
					  xscalar_space_path, 
					  xvector_space_args, 
					  xauto_access);
    
  typedef typename S::scalar_type::host_type scalar_host_type;
  bool result = path_is_auto_read_available<scalar_host_type>(lscalar_space_path, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path_is_available(const poset_path& xspace_path, 
						  const poset_path& xdomain_space_path, 
						  const arg_list& xspace_args,
						  const poset_path& xscalar_space_path, 
						  const arg_list& xdomain_space_args,
						  bool xauto_access) const
{
  // Preconditions:


  // Body:

  poset_path lscalar_space_path = 
    completed_jacobian_scalar_space_path<S>(xspace_path, 
					    xdomain_space_path, 
					    xspace_args, 
					    xscalar_space_path, 
					    xdomain_space_args, 
					    xauto_access);
    
  typedef typename S::scalar_type::host_type scalar_host_type;
  bool result = path_is_auto_read_available<scalar_host_type>(lscalar_space_path, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename J>
bool
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path_is_available(const poset_path& xspace_path, 
					 const poset_path& xdomain_space_path, 
					 const arg_list& xspace_args,
					 bool xauto_access) const
{
  // Preconditions:

  // Body:

  poset_path ldomain_space_path = 
    completed_domain_space_path<J>(xspace_path, 
				   xdomain_space_path, 
				   xspace_args, 
				   xauto_access);
    
  typedef typename J::domain_type::host_type domain_host_type;
  bool result = path_is_auto_read_available<domain_host_type>(ldomain_space_path, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename J>
bool
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path_is_available(const poset_path& xspace_path, 
					 const poset_path& xrange_space_path, 
					 const arg_list& xspace_args,
					 bool xauto_access) const
{
  // Preconditions:

  // Body:

  poset_path lrange_space_path = 
    completed_range_space_path<J>(xspace_path, 
				  xrange_space_path, 
				  xspace_args, 
				  xauto_access);
    
  typedef typename J::range_type::host_type range_host_type;
  bool result = path_is_auto_read_available<range_host_type>(lrange_space_path, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;  

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SECTION SCHEMA FACTORY METHOD PATH AVAILABILITY QUERY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available(const poset_path& xpath,
						 const poset_path& xrep_path,
						 const poset_path& xbase_space_path,
						 const poset_path& xfiber_space_path,
						 const arg_list& xargs,
						 bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  poset_path lpath =
    completed_section_space_schema_path<S>(xpath, 
					   xrep_path, 
					   xbase_space_path, 
					   xfiber_space_path, 
					   xargs,
					   xauto_access);
  
  bool result = path_is_auto_read_available<section_space_schema_poset>(lpath, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible(const poset_path& xsection_space_schema_path, 
				 const poset_path& xrep_path, 
				 const poset_path& xbase_space_path, 
				 const poset_path& xfiber_space_path, 
				 const arg_list& xargs,
				 bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require(xsection_space_schema_path.full() || xbase_space_path.full() || 
	  (xargs.contains_arg("base_space_path") && poset_path(xargs.value("base_space_path")).full()));

  // Body:

  poset_path lsssp = 
    completed_section_space_schema_path<S>(xsection_space_schema_path,
					   xrep_path,
					   xbase_space_path,
					   xfiber_space_path,
					   xargs,
					   xauto_access);
  
  bool result = contains_poset<section_space_schema_poset>(lsssp, xauto_access);
  if(!result)
  {
    poset_path lrep_path = 
      completed_rep_path<S>(xsection_space_schema_path, xrep_path, xargs, xauto_access);
    
    result = path_is_auto_read_accessible(lrep_path, xauto_access);
  }  
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible(const poset_path& xsection_space_schema_path, 
				 const poset_path& xrep_path, 
				 const poset_path& xbase_space_path, 
				 const poset_path& xfiber_space_path, 
				 const arg_list& xargs,
				 bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require(contains_poset<section_space_schema_poset>(xsection_space_schema_path, xauto_access) || 
	  xbase_space_path.full() || 
	  (xargs.contains_arg("base_space_path") && poset_path(xargs.value("base_space_path")).full()));

  // Body:

  poset_path lsssp = 
    completed_section_space_schema_path<S>(xsection_space_schema_path,
					   xrep_path,
					   xbase_space_path,
					   xfiber_space_path,
					   xargs,
					   xauto_access);
  
  bool result = contains_poset<section_space_schema_poset>(lsssp, xauto_access);
  if(!result)
  {
    poset_path lbase_space_path = 
      completed_base_space_path(xsection_space_schema_path, xbase_space_path, xargs, xauto_access);
    
    result = path_is_auto_read_accessible(lbase_space_path, xauto_access);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available(const poset_path& xsection_space_schema_path, 
					const poset_path& xrep_path, 
					const poset_path& xbase_space_path, 
					const poset_path& xfiber_space_path, 
					const arg_list& xsection_space_schema_args,
					bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require(contains_poset<section_space_schema_poset>(xsection_space_schema_path, xauto_access) || 
	  xbase_space_path.full() || 
	  (xsection_space_schema_args.contains_arg("base_space_path") && 
	   poset_path(xsection_space_schema_args.value("base_space_path")).full()));

  // Body:

  poset_path lsssp = 
    completed_section_space_schema_path<S>(xsection_space_schema_path,
					   xrep_path,
					   xbase_space_path,
					   xfiber_space_path,
					   xsection_space_schema_args,
					   xauto_access);
  
  bool result = contains_poset<section_space_schema_poset>(lsssp, xauto_access);
  if(!result)
  {
    poset_path lfiber_space_path = 
      completed_fiber_space_path<S>(xsection_space_schema_path, 
				    xfiber_space_path, 
				    xsection_space_schema_args, 
				    xauto_access);
    
    typedef typename S::fiber_type::host_type fiber_host_type;
    result = path_is_auto_read_available<fiber_host_type>(lfiber_space_path, xauto_access);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const poset_path& xbase_space_path, 
					 const poset_path& xfiber_space_path, 
					 const arg_list& xsection_space_schema_args,
					 const poset_path& xvector_space_path, 
					 const arg_list& xfiber_space_args,
					 bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require(contains_poset<section_space_schema_poset>(xsection_space_schema_path, xauto_access) || 
	  xbase_space_path.full() || 
	  (xsection_space_schema_args.contains_arg("base_space_path") && 
	   poset_path(xsection_space_schema_args.value("base_space_path")).full()));

  // Body:

  poset_path lsssp = 
    completed_section_space_schema_path<S>(xsection_space_schema_path,
					   xrep_path,
					   xbase_space_path,
					   xfiber_space_path,
					   xsection_space_schema_args,
					   xauto_access);
  
  bool result = contains_poset<section_space_schema_poset>(lsssp, xauto_access);
  if(!result)
  {
    poset_path lvector_space_path = 
      completed_vector_space_path<S>(xsection_space_schema_path, 
				     xfiber_space_path, 
				     xsection_space_schema_args, 
				     xvector_space_path, 
				     xfiber_space_args, 
				     xauto_access);
    
    typedef typename S::fiber_type::vector_space_type::host_type vector_host_type;
    result = path_is_auto_read_available<vector_host_type>(lvector_space_path, xauto_access);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const poset_path& xbase_space_path, 
					 const poset_path& xfiber_space_path, 
					 const arg_list& xsection_space_schema_args,
					 const poset_path& xscalar_space_path, 
					 const arg_list& xfiber_space_args,
					 bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require(contains_poset<section_space_schema_poset>(xsection_space_schema_path, xauto_access) || 
	  xbase_space_path.full() || 
	  (xsection_space_schema_args.contains_arg("base_space_path") && 
	   poset_path(xsection_space_schema_args.value("base_space_path")).full()));

  // Body:

  poset_path lsssp = 
    completed_section_space_schema_path<S>(xsection_space_schema_path,
					   xrep_path,
					   xbase_space_path,
					   xfiber_space_path,
					   xsection_space_schema_args,
					   xauto_access);
  
  bool result = contains_poset<section_space_schema_poset>(lsssp, xauto_access);
  if(!result)
  {
    poset_path lscalar_space_path = 
      completed_section_scalar_space_path<S>(xsection_space_schema_path, 
					     xfiber_space_path, 
					     xsection_space_schema_args, 
					     xscalar_space_path, 
					     xfiber_space_args, 
					     xauto_access);
    
    typedef typename S::fiber_type::scalar_type::host_type scalar_host_type;
    result = path_is_auto_read_available<scalar_host_type>(lscalar_space_path, xauto_access);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const poset_path& xbase_space_path, 
					 const poset_path& xfiber_space_path, 
					 const arg_list& xsection_space_schema_args,
					 const poset_path& xvector_space_path, 
					 const arg_list& xfiber_space_args,
					 const poset_path& xscalar_space_path, 
					 const arg_list& xvector_space_args,
					 bool xauto_access) const
{
  // Preconditions:

  require(path_is_auto_read_available(xsection_space_schema_path, xauto_access));
  require(contains_poset<section_space_schema_poset>(xsection_space_schema_path, xauto_access) || 
	  xbase_space_path.full() || poset_path(xsection_space_schema_args.value("base_space_path")).full());
  require(contains_poset<section_space_schema_poset>(xsection_space_schema_path, xauto_access) || 
	  xbase_space_path.full() || 
	  (xsection_space_schema_args.contains_arg("base_space_path") && 
	   poset_path(xsection_space_schema_args.value("base_space_path")).full()));

  // Body:

  poset_path lsssp = 
    completed_section_space_schema_path<S>(xsection_space_schema_path,
					   xrep_path,
					   xbase_space_path,
					   xfiber_space_path,
					   xsection_space_schema_args,
					   xauto_access);
  
  bool result = contains_poset<section_space_schema_poset>(lsssp, xauto_access);
  if(!result)
  {
    poset_path lscalar_space_path = 
      completed_scalar_space_path<S>(xsection_space_schema_path, 
				     xfiber_space_path, 
				     xsection_space_schema_args, 
				     xvector_space_path, 
				     xfiber_space_args, 
				     xscalar_space_path, 
				     xvector_space_args, 
				     xauto_access);
    
    typedef typename S::fiber_type::scalar_type::host_type scalar_host_type;
    result = path_is_auto_read_available<scalar_host_type>(lscalar_space_path, xauto_access);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// MISCELLANEOUS FACTORY METHOD PATH QUERIES FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to(const poset_path& xpath, bool xauto_access) const
{
  // Preconditions:

  // Body:

  poset_path lpath = completed_schema_path<S>(xpath);
  bool result = path_is_auto_read_accessible(lpath, xauto_access);
  if(result)
  {
    result = lpath.conforms_to(*this, S::standard_schema_path(), xauto_access);
  }
  
  
  // Postconditions:

  // Exit:

  return result;  

}

template <typename S>
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path(const arg_list& xargs,
				       const poset_path& xpath, 
				       bool xauto_access) const
{
  // Preconditions:

  // Body:

  bool result = xargs.empty();
  if(!result)
  {
    poset_path lpath = completed_schema_path<S>(xpath);
    result = xargs.conforms_to(*this, lpath, true, xauto_access);
  }
  
  // Postconditions:

  // Exit:

  return result;  

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


#endif // ifndef FIBER_BUNDLES_NAMESPACE_IMPL_H
