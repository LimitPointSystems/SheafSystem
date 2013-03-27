
// $RCSfile: gln_space.cc,v $ $Revision: 1.13 $ $Date: 2013/03/18 02:53:22 $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class gln_space.

#include "gln_space.h"

#include "abstract_poset_member.impl.h"
#include "arg_list.h"
#include "assert_contract.h"
#include "gln.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "vd_space.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// GLN_SPACE FACET
//==============================================================================

///
const string&
fiber_bundle::gln_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = gln::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::gln_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = gln::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

sheaf::arg_list
fiber_bundle::gln_space::
make_arg_list(int xn,
	      const poset_path& xscalar_space_path,
	      const poset_path& xvector_space_path)
{
  // Preconditions:


  // Body:

  arg_list result;

  result << "scalar_space_path" << xscalar_space_path
	 << "vector_space_path" << xvector_space_path
	 << "n" <<  xn;
  
	 
#ifdef DIAGNOSTIC_OUTPUT
  cout << "gln_space::make_arg_list:result: " << endl << result << endl;
#endif

  // Postconditions:

  ensure(result.value("scalar_space_path") == xscalar_space_path);
  ensure(result.value("vector_space_path") == xvector_space_path);
  ensure(result.value("n") == xn);
  ensure(unexecutable("result.conforms_to(schema of this class)"));
  
  // Exit:

  return result;
}

int
fiber_bundle::gln_space::
n() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = sheaf::table_dofs(*this).n;

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::gln_space::
n(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  int result = n();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln_space::
scalar_space_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(sheaf::table_dofs(*this).scalar_space_path);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln_space::
scalar_space_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).scalar_space_path);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln_space::
vector_space_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(sheaf::table_dofs(*this).vector_space_path);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::gln_space::
vector_space_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).vector_space_path);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

int
fiber_bundle::gln_space::
d() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int ln = n();
  int result = 2*ln*ln;

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::gln_space::
d(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }
  
  int result = d();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

fiber_bundle::gln_space::
gln_space()
  : poset(new gln, new gln)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(poset::poset()));
}



fiber_bundle::gln_space::
gln_space(const gln_space& xother)
  : poset(new gln, new gln)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);
  
  // Postconditions:

  ensure(is_same_state(&xother));
}


fiber_bundle::gln_space::
~gln_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::gln_space::
gln_space(gln* xtop, gln* xbottom)
  : poset(xtop, xbottom)
{
  // Preconditions:

  require(xtop != 0);
  require(xbottom != 0);
  
  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::poset_state_handle(xtop, xbottom)));
  
  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, NEW STATE CONSTRUCTORS
//==============================================================================

fiber_bundle::gln_space::
gln_space(namespace_poset& xhost,
	    const string& xname,
	    const arg_list& xargs,
	    const poset_path& xschema_path,
	    bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_state(same args)));

  require(xargs.value("n").value().int_primitive >= 0);

  // Body:

  new_state(xhost, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================


fiber_bundle::gln_space::
gln_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access)
  : poset(new gln, new gln)
{
  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));
  require(xhost.contains_member(xindex, xauto_access));

  if(xauto_access)
  {
    xhost.get_read_access();
  }
  
  require(xhost.is_jim(xindex));

  // Body:

  attach_to_state(&xhost, xindex);

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(host() == &xhost);
  ensure(index() == xindex);
}

fiber_bundle::gln_space::
gln_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access)
  : poset(new gln, new gln)
{
  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));
  require(xhost.contains_member(xindex, xauto_access));

  if(xauto_access)
  {
    xhost.get_read_access();
  }
  
  require(xhost.is_jim(xindex));

  // Body:

  attach_to_state(&xhost, xindex.hub_pod());

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(host() == &xhost);
  ensure(index() ==~ xindex);
}

fiber_bundle::gln_space::
gln_space(const namespace_poset& xhost, const string& xname, bool xauto_access)
  : poset(new gln, new gln)
{
  // Preconditions:

  require(xhost.state_is_auto_read_accessible(xauto_access));
  require(xhost.contains_member(xname));

  // Body:


  if(xauto_access)
  {
    xhost.get_read_access();
  }

  attach_to_state(&xhost, xname);

  // Postconditions:

  ensure(host() == &xhost);
  ensure(name() == xname);

  if(xauto_access)
  {
    xhost.release_access();
  }
}



fiber_bundle::gln_space::
gln_space(const namespace_poset_member& xmbr, bool xauto_access)
  : poset(new gln, new gln)
{
  // Preconditions:

  require(xmbr.state_is_auto_read_accessible(xauto_access));

  // Body:


  if(xauto_access)
  {
    xmbr.get_read_access();
  }

  attach_to_state(&xmbr);

  if(xauto_access)
  {
    xmbr.release_access();
  }

  // Postconditions:

  ensure(index() ==~ xmbr.index());
}


// ===========================================================
// POSET FACET
// ===========================================================
 
///
void
fiber_bundle::gln_space::
new_state(namespace_poset& xhost,
          const string& xname,
          const arg_list& xargs,
          const poset_path& xschema_path,
          bool xauto_access)
{

  // Preconditions:

  require(xhost.state_is_auto_read_write_accessible(xauto_access));

  require(xschema_path.full());
  require(xschema_path.poset_name() == standard_schema_poset_name());
  require(xhost.contains_poset_member(xschema_path, xauto_access));
  require(xhost.member_poset(xschema_path, xauto_access).state_is_auto_read_accessible(xauto_access));
  require(schema_poset_member::conforms_to(xhost, xschema_path, standard_schema_path(), xauto_access));

  require(xargs.conforms_to(xhost, xschema_path, true, xauto_access));
  require(xhost.path_is_auto_read_accessible(poset_path(xargs.value("vector_space_path")), xauto_access));

  // Body:
    
  // Set any class specific args in arg list.

  arg_list largs(xargs);
  initialize_arg_list(xhost, xname, largs, xauto_access);

  // Create the new state.

  poset::new_state(&xhost, xschema_path, xname, largs, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state(xhost, xschema_path, xname, xargs, xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::gln_space::
initialize_arg_list(const namespace_poset& xns,
		    const string& xname,
		    arg_list& xargs,
		    bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));  

  require(xargs.conforms_to(xns, standard_schema_path(), true, xauto_access));
  require(xns.path_is_auto_read_accessible(poset_path(xargs.value("vector_space_path")), xauto_access));

  // Body:

  poset_path lvector_space_path(xargs.value("vector_space_path"));  

  xargs.value("scalar_space_path") = vd_space::scalar_space_path(xns, lvector_space_path, xauto_access);
  xargs.value("n") = vd_space::d(xns, lvector_space_path, xauto_access);

  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "gln_space::initialize_arg_list:xargs: " << endl << xargs << endl;
#endif

  // Postconditions:


  // Exit:

  return;
}

bool
fiber_bundle::gln_space::
_has_prototype = make_prototype();


bool
fiber_bundle::gln_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  gln_space* lproto = new gln_space;
  poset_type ltype    = lproto->type_id();

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return result;
}

//==============================================================================
// POSET_STATE_HANDLE FACET
//==============================================================================



sheaf::poset_type
fiber_bundle::gln_space::
type_id() const
{
  return GLN_SPACE_ID;
}





///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::gln_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "gln_space";

  // Postconditions:

  // Exit:

  return result;
}


///
sheaf::pod_index_type
fiber_bundle::gln_space::
prereq_id(int xi) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(name_space()->state_is_read_accessible());

  // Body:

  // The result must be scoped if it is valid because
  // namespace_poset_member::put_poset_prereq_id must be
  // able to map it to the namespace member id space.
  // The vector_space_index is just a pod, so we have to
  // pick some id space for it and make sure we consistently
  // use it. The obvious choice is the internal id space, 
  // so initialize result to internal scope.
 
  pod_index_type result;

  switch(xi)
  {
    case 0:

      // The first prerequisite is always the schema.

      result = schema().host()->index().pod();
      break;

    case 1:
	
	// The underlying vector space.

      result = name_space()->member_id(vector_space_path().poset_name(), false);
      break;

    default:

      // No other prerequisites.

      result = invalid_pod_index();
      break;
  }

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::gln_space&
fiber_bundle::gln_space::
operator=(const poset_state_handle& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  poset_state_handle::operator=(xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return *this;
}

//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::gln_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const gln_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::gln_space*
fiber_bundle::gln_space::
clone() const
{
  gln_space* result;

  // Preconditions:

  // Body:

  result = new gln_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::gln_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(poset::invariant());

    /// @todo finish gln_space::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}



