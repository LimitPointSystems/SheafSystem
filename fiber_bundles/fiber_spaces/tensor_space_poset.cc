
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

// Implementation for class tensor_space_poset.

#include "tensor_space_poset.h"

#include "assert_contract.h"
#include "namespace_poset.h"
#include "poset_handle_factory.h"
#include "tp.h"

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// TENSOR_SPACE_POSET FACET
//==============================================================================

///
fiber_bundle::tensor_space_poset::
tensor_space_poset()
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(poset::poset()));
}


///
fiber_bundle::tensor_space_poset::
tensor_space_poset(const tensor_space_poset& xother)
    : poset(xother)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class.

  // Postconditions:

  ensure(postcondition_of(poset::poset(const poset&)));
}

///
fiber_bundle::tensor_space_poset&
fiber_bundle::tensor_space_poset::
operator=(const tensor_space_poset& xother)
{
  // Preconditions:

  //require(???);

  // Body:

  not_implemented();

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return *this;
}

///
fiber_bundle::tensor_space_poset::
~tensor_space_poset()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

//==============================================================================
// NEW HANDLE, NEW STATE CONSTRUCTORS
//==============================================================================


///
fiber_bundle::tensor_space_poset::
tensor_space_poset(namespace_poset* xhost,
      const poset_path& xschema_path,
      const string& xname,
      arg_list& xargs,
      bool xauto_access)
{

  // Preconditions:

  require(precondition_of(poset::new_state(same args)));

  // Body:

  new_state(xhost, xschema_path, xname, xargs, xauto_access);

  // Postconditions:

  ensure(postcondition_of(poset::new_state(same args)));

  // Exit:

  return;
}

//==============================================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
//==============================================================================

///
fiber_bundle::tensor_space_poset::
tensor_space_poset(const namespace_poset* xhost, scoped_index xindex)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xindex));
  require(xhost->is_jim(xindex));

  // Body:

  _vector_space = 0;
  attach_to_state(xhost, xindex);

  // Postconditions:

  ensure(postcondition_of(poset::attach_to_state()));
}


///
fiber_bundle::tensor_space_poset::
tensor_space_poset(const namespace_poset* xhost, const string& xname)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xname));

  // Body:

  _vector_space = 0;
  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(poset::attach_to_state()));
}


///
fiber_bundle::tensor_space_poset::
tensor_space_poset(const abstract_poset_member* xmbr)
{
  // Preconditions:

  require(xmbr != 0);
  require(dynamic_cast<namespace_poset*>(xmbr->host()) != 0);
  require(xmbr->state_is_read_accessible());

  // Body:

  _vector_space = 0;
  attach_to_state(xmbr);

  // Postconditions:

  ensure(postcondition_of(\
    state_handle::attach_to_state(abstract_poset_member*)));
}

//==============================================================================
// EXISTING HANDLE, NEW STATE "CONSTRUCTORS"
//==============================================================================

///
void
fiber_bundle::tensor_space_poset::
new_state(namespace_poset* xhost,
          const abstract_poset_member* xschema,
          const string& xname,
          array_poset_dof_map* xdof_tuple,
          bool xauto_access)
{

  // Preconditions:

  require(xhost != 0);

  /// @hack should require in_jim_edit_mode;
  /// see poset_state_handle::initialize_namespace
  ///  require(xauto_access || xhost->in_jim_edit_mode());
  require(xauto_access || xhost->state_is_read_write_accessible());

  if(xauto_access)
  {
    xhost->get_read_write_access();
  }

  require(xschema != 0);
  require(xschema->is_schematized(true));

  require(!xname.empty());
  require(!xhost->contains_poset(xname, true));

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.

  require(xname != xhost->name());

  require(xdof_tuple != 0);
  require(xdof_tuple->schema().conforms_to(xschema->path(true)));

  // Body:

  // Disable invariant checking in
  // member functions until construction finished

  disable_invariant_check();

  // Create the poset state object;
  // Allocates the data structures but does not (fully) initialize them

  // $$SCRIBBLE dmb: The only reason this function is overridden from poset
  // is to pass TENSOR_SPACE_POSET_ID instead of POSET_ID in the following call.
  // We need to provide some other method of doing this.

  _state = new poset_state(xschema, TP_SPACE_ID);

  attach_handle_data_members(xhost, xdof_tuple);

  // Get write access

  get_read_write_access();

  // Initialize the table dofs ("class variables").
  // Do this before initializing the row structure so the subposet
  // and member initialization routines can use the table dofs if needed.

  initialize_table_dof_tuple(xdof_tuple);

  // Initialize the row structure

  initialize_standard_subposets(xname);
  initialize_standard_members();

  // Initialize the namespace features

  initialize_namespace(*xhost, xname);

  // Set the standard id spaces.

  update_standard_id_spaces();

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(schema().is_same_state(xschema));
  ensure(name() == xname);
  ensure(&(table_dof_map()) == xdof_tuple);
  ensure(!in_jim_edit_mode());
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());

  /// @todo resolve status of following postcondition:
  ///   ensure(has_standard_subposet_ct());

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  if(xauto_access)
  {
    xhost->release_access();
  }

  // Exit:

  return;
}

///
void
fiber_bundle::tensor_space_poset::
new_state(const schema_poset_member& xschema, array_poset_dof_map& xdof_map)
{

  // Preconditions:

  require(is_external());
  require(schema_is_ancestor_of(&xschema));
  require(xschema.state_is_read_accessible());
  require(xschema.host()->name_space()->is_same_state(name_space()));
  require(name_space()->member_poset_schema_id(index(), true) ==~ xschema.host()->index());
  require(xschema.is_schematized(false));

  /// @issue the following is unexecutable because dof maps don't have
  /// a schema until attached to a host; requires covariant schema feature to implement.

  /// @todo fix dof maps schema feature and make this precondition executable.

  require(unexecutable(xschema.is_same_state(xdof_map.schema())));

  // Body:

  // Disable invariant checking in
  // member functions until construction finished

  disable_invariant_check();

  // Create the poset state object;
  // Allocates the data structures but does not (fully) initialize them

  _state = new poset_state(&xschema, TP_SPACE_ID);

  attach_handle_data_members(name_space(), &xdof_map);

  // Get write access

  get_read_write_access();

  // Initialize the table dofs ("class variables");
  // must be done before row structure since row structure
  // may depend on table dofs.

  initialize_table_dof_tuple(&xdof_map);

  // Initialize the row structure

  initialize_standard_subposets(name_space()->member_name(index()));
  initialize_standard_members();

  /// @issue automatic vs explicit version subposet membership.
  /// The crg of the coarsest_common_refinement (CCR) is what is
  /// written to disk, along with membership info for each of the
  /// version subposets. When we read the file, we want to reconstruct
  /// the CCR graph and the membership for each of the versions.
  /// The CCR graph gets reconstructed without issue, since that
  /// is what is in the file. For non-versioned posets, the subposet
  /// membership gets reconstructed correctly as well, since there
  /// are no version subposets and both CCR and whole() refer to the
  /// same subposet. But for refinable posets, when a member is created
  /// it is automatically entered into the CCR and, separately, into
  /// the current version subposet. This automatic subposet membership
  /// management conflicts with the explicit subposet membership
  /// management provided by the i/o subsystem.

  /// @hack version subposet membership management. We can resolve
  /// the above version subposet membership management issue by setting
  /// the current version to CCR. This makes the refineable posets
  /// behave like non-version posets, at the cost of inserting every member
  /// into the CCR subposet twice, once for the CCR and once for the
  /// current version.

  /// @issue current version. The above hack leaves the poset with
  /// CCR as the current version. What should the current version be,
  /// and where should we restore it?

  put_version(COARSEST_COMMON_REFINEMENT_VERSION);

  // Now invariant should be satisfied.

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!in_jim_edit_mode());
  ensure(has_standard_member_ct());
  ensure(has_standard_row_dof_tuple_ct());
  //   ensure(has_standard_subposet_ct());
  ensure(version() == COARSEST_COMMON_REFINEMENT_VERSION);

  // Now we're finished, release all access.

  release_access();

  // One final postcondition.

  ensure(state_is_not_read_accessible());
}

///
void
fiber_bundle::tensor_space_poset::
get_read_access() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  int old_access_request_depth = access_request_depth();

  //@hack: This function can be called in
  //       poset_state_handle::attach_to_state(const abstract_poset_member* xmbr)
  //       before attach_handle_data_members() is called.  So are temporarily
  //       modifying the following to work around this problem.  Note that we
  //       have also commented one of the preconditions.

  //if(!is_same_state(_vector_space))
  if((_vector_space != 0) &&
     (_vector_space->is_attached()) &&
     (!is_same_state(_vector_space)))
  {
    _vector_space->get_read_access();
  }
  
  poset_state_handle::get_read_access();

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
//   ensure(vector_space().state_is_read_accessible());

  // Exit

  return;
}

///
void
fiber_bundle::tensor_space_poset::
get_read_write_access(bool xrelease_read_only_access)
{
  // Preconditions:

  require(is_attached());
  require(!xrelease_read_only_access ? state_is_not_read_only_accessible() : true);

  // Body:

  int old_access_request_depth = access_request_depth();

  //if(!is_same_state(_vector_space))
  if((_vector_space != 0) &&
     (_vector_space->is_attached()) &&
     (!is_same_state(_vector_space)))
  {
    _vector_space->get_read_access();
    //_vector_space->get_read_write_access(xrelease_read_only_access);
  }
  poset_state_handle::get_read_write_access(xrelease_read_only_access);

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
  ensure(vector_space().state_is_read_accessible());

  // Exit

  return;
}


///
void
fiber_bundle::tensor_space_poset::
release_access(bool xall) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int old_access_request_depth = access_request_depth();

  // Release at least one level of access for this. If xall, release all levels
  // of access for this. Since each level of access to this also
  // acquired a level of access to the rep, the base space, and the fiber space,
  // release the same number of levels of access to each of these.
  // Note that this may not be all the levels of access of these.

  do
  {
    // Release one level of access.

    //if(!is_same_state(_vector_space))
    if((_vector_space != 0) &&
       (_vector_space->is_attached()) &&
       (!is_same_state(_vector_space)) &&
       (_vector_space->state_is_read_accessible()))
    {
       _vector_space->release_access(false);
    }
    poset_state_handle::release_access(false);
  }
  while(xall && state_is_read_accessible());


  // Postconditions:

  ensure(!xall ? access_request_depth() == old_access_request_depth - 1 : access_request_depth() == 0);
  ensure(access_request_depth() == 0 ? state_is_not_read_accessible() : true);
  ensure(unexecutable("schema, rep, base, base schema, fiber, and fiber schema access released"));

  // Exit

  return;
}

///
void
fiber_bundle::tensor_space_poset::
detach_from_state()
{
  // Preconditions:

  // Body:

  // We'll need the following if we make vector_space a data member.

  //  _fiber_space.detach_from_state();

  poset_state_handle::detach_from_state();

  // Postconditions:

  ensure(!is_attached());
  //  ensure(!vector_space().is_attached());

  // Exit

  return;
}

///
void
fiber_bundle::tensor_space_poset::
initialize_standard_subposets(const string& xname)
{
  // Preconditions:

  require(poset_path::is_valid_name(xname));
  require(state_is_read_write_accessible());

  // Body:

  // $$SCRIBBLE: why redefine this function?

  poset::initialize_standard_subposets(xname);

  // Postconditions:

  ensure(state_obj()->powerset()->invariant());
  ensure(jims().is_attached());
  ensure(whole().is_attached());
  ensure(resident().is_attached() && resident().index() == RESIDENT_INDEX);

  // Exit

  return;
}

///
void
fiber_bundle::tensor_space_poset::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  poset_state_handle::attach_handle_data_members();

  scoped_index lvector_space_index(name_space()->member_id());
  lvector_space_index = vector_space_index();

  /// @hack vector_space can't be a handle because we can't declare
  /// a data member of the same type as the class.
  
  _vector_space = 
    reinterpret_cast<tensor_space_poset*>(name_space()->member_poset(lvector_space_index, false));

  // Postconditions:

  ensure(vector_space().is_attached());


  // Exit

  return;
}

///
void
fiber_bundle::tensor_space_poset::
attach_handle_data_members(namespace_poset* xns, array_poset_dof_map* xtable_dof_tuple)
{
  // Preconditions:

  require(xns->state_is_read_accessible());

  // Body:

  //  poset_state_handle::attach_handle_data_members();


  arg_list ltable_dofs;
  xtable_dof_tuple->get_dof_tuple(ltable_dofs);
  scoped_index lvector_space_index(xns->member_id());
  lvector_space_index = static_cast<pod_index_type>(ltable_dofs.value("vector_space_index"));

  /// @hack vector_space can't be a handle because we can't declare
  /// a data member of the same type as the class.

  if(xns->contains_member(lvector_space_index, false))
  {
    _vector_space = 
      reinterpret_cast<tensor_space_poset*>(xns->member_poset(lvector_space_index, false));
  }
  else
  {
    _vector_space = this;
  }    

  // Postconditions:

  //  ensure(vector_space().is_attached());


  // Exit

  return;
}

///
void
fiber_bundle::tensor_space_poset::
terminate_access()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  //define_old_variable(int old_vector_space_access_request_depth = _vector_space->access_request_depth());
  int old_vector_space_access_request_depth = _vector_space->access_request_depth();

  // Release all levels of access this poset has to its various parts,
  // but do not release access to the state of this because
  // we are going to delete the state and don't want another
  // client able to sneak in and get access before we do.

  /// @issue we should either prevent termination if other clients
  /// exist or have some mechanism for notifying them of termination.
  /// Currently we can't do either one.


#ifdef DIAGNOSTIC_OUTPUT
  cout << "poset: " << name() << endl
       << "\tvector_space: " << _vector_space->name()
       << "  old lvl:" << old_vector_space_access_request_depth
       << endl;
#endif

  int old_access_request_depth = access_request_depth();
  if(!is_same_state(_vector_space))
  {
    int ldepth = (old_vector_space_access_request_depth < old_access_request_depth)
                 ? old_vector_space_access_request_depth : old_access_request_depth;

    for(size_type i=0; i<ldepth; ++i)
    {
      _vector_space->release_access(false);
    }
  }

  bool old_is_vector_space = is_same_state(_vector_space);
  int vector_space_access_request_depth = _vector_space->access_request_depth();

#ifdef DIAGNOSTIC_OUTPUT
  cout << "  vector_space lvl:" << vector_space_access_request_depth << endl;
#endif

  // Detach and delete the state.

  poset_state_handle::terminate_access();

  // Postconditions:

  ensure(!is_attached());
  ensure(unexecutable(state has been deleted));
//   ensure(old_is_vector_space || 
// 	 vector_space_access_request_depth == (old_vector_space_access_request_depth - old_access_request_depth));

  // Exit

  return;
}

///
bool
fiber_bundle::tensor_space_poset::
_has_prototype = make_prototype();

///
bool
fiber_bundle::tensor_space_poset::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  poset_type ltype = TP_SPACE_ID;

  tensor_space_poset* lproto = new tensor_space_poset;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return result;
}

///
sheaf::pod_index_type
fiber_bundle::tensor_space_poset::
vector_space_index() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // $$SCRIBBLE: all this const casting probably isn't necessary any more.

  tensor_space_poset* cthis = const_cast<tensor_space_poset*>(this);
  fiber_bundle::tp_table_dofs_type* ltable_dofs =
    reinterpret_cast<fiber_bundle::tp_table_dofs_type*>
      (cthis->table_dof_map().dofs());

  // $$SCRIBBLE: dmb
  //  pod_index_type result = ltable_dofs->vector_space_index;
  pod_index_type result = invalid_pod_index();
  

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);

  // Exit:

  return result;
}

///
sheaf::pod_index_type
fiber_bundle::tensor_space_poset::
vector_space_index(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  pod_index_type result = vector_space_index();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);

  // Exit:

  return result;
}

///
fiber_bundle::tensor_space_poset&
fiber_bundle::tensor_space_poset::
vector_space() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  tensor_space_poset& result = *_vector_space;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
fiber_bundle::tensor_space_poset&
fiber_bundle::tensor_space_poset::
vector_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  if(xauto_access)
  {
    get_read_access();
  }

  tensor_space_poset& result = vector_space();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(result = vector_space()));

  // Exit:

  return result;
}

//==============================================================================
// POSET_STATE_HANDLE FACET
//==============================================================================

///@todo: Return string&.
///@todo: Static version.
///
const char*
fiber_bundle::tensor_space_poset::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "tensor_space_poset";

  // Postconditions:

  // Exit:

  return result;
}

///
sheaf::scoped_index
fiber_bundle::tensor_space_poset::
prereq_id(int xi) const
{
  // Preconditions:

  // Body:

  // The result must be scoped if it is valid because
  // namespace_poset_member::put_poset_prereq_id must be
  // able to map it to the namespace member id space.
  // The vector_space_index is just a pod, so we have to
  // pick some id space for it and make sure we consistently
  // use it. The obvious choice is the member id space, 
  // so initialize result to member scope.
 
  scoped_index result(name_space()->member_id());

  switch(xi)
  {
    case 0:

      // The first prerequisite is always the schema.

      result = schema().host()->index();
      break;

    case 1:
      { // To prevent compiler warnings about scope of variable
	
	// The vector space over which this tensor space is built.

	pod_index_type lindex = vector_space_index();

	/// @hack Have to compare this to vector space by name,
	/// because index of this isn't set first time this function is called.

	string lvector_space_name = name_space()->member_name(lindex, false);

	if(name() == lvector_space_name) 
	{
	  // This is the vector space itself;
	  // it has no prerequisite, so return invalid.

	  result.invalidate(); // Namespace internal scope.
	}
	else
	{
	  // This is some tensor space, not the vector space itself; 
	  // the prerequisite is the vector space, 
	  // return index in internal scope.

	  result = lindex; // Namespace internal scope.
	}	
      }
      break;

    default

      // No other prerequisites.
      :
      result.invalidate();
      break;
  }

  // Postconditions:


  // Exit:

  return result;
}

//==============================================================================
// ANY FACET
//==============================================================================

///
fiber_bundle::tensor_space_poset*
fiber_bundle::tensor_space_poset::
clone() const
{
  tensor_space_poset* result;

  // Preconditions:

  // Body:

  result = new tensor_space_poset;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

///
bool
fiber_bundle::tensor_space_poset::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const tensor_space_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

///
bool
fiber_bundle::tensor_space_poset::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(poset::invariant());

    /// @todo finish tensor_space_poset::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}
