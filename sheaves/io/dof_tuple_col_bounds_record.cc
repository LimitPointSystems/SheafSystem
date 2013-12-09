
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

// Implementation for class dof_tuple_col_bounds_record

#include "dof_tuple_col_bounds_record.h"

#include "assert_contract.h"
#include "std_sstream.h"

using namespace std;

// =============================================================================
// ANY FACET
// =============================================================================

///
sheaf::dof_tuple_col_bounds_record*
sheaf::dof_tuple_col_bounds_record::
clone() const
{
  dof_tuple_col_bounds_record* result;

  // Preconditions:

  // Body:

  result = new dof_tuple_col_bounds_record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
bool
sheaf::dof_tuple_col_bounds_record::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && attributes_record::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::dof_tuple_col_bounds_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const dof_tuple_col_bounds_record*>(other) != 0;

  // Postconditions:

  return result;

}


// =============================================================================
// DOF_TUPLE_COL_BOUNDS_RECORD FACET
// =============================================================================

///
sheaf::dof_tuple_col_bounds_record::
dof_tuple_col_bounds_record(poset_scaffold& xscaffold)
  : attributes_record(xscaffold)
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
sheaf::dof_tuple_col_bounds_record::
dof_tuple_col_bounds_record(const dof_tuple_col_bounds_record& xother)
  : attributes_record(xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}



///
sheaf::dof_tuple_col_bounds_record::
~dof_tuple_col_bounds_record()
{

  // Preconditions:

  // Body:

  // Nothing specific to do.
  /// @issue can we just not define this function?

  // Postconditions:

  // Exit:

  return;
}

// =============================================================================
// PROTECTED MEMBER FUNCTIONS
// =============================================================================


///
void
sheaf::dof_tuple_col_bounds_record::
transfer_internal_buffer_to_poset()
{
  // Preconditions:

  require(is_internal());
  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

  // Initialize the stream.

  stringstream lstream(_str_buf);

  // Skip the header line:

  lstream.ignore(numeric_limits<streamsize>::max(), '\n');

  // Transfer the col bounds into the scaffold.

  typedef poset_scaffold::dof_tuple_col_bounds_type map_type;
  map_type& lmap = scaffold().dof_tuple_col_bounds();

  record_index::pod_type ltuple_id_pod;
  record_index::pod_type lcol_bound[3];

  while(lstream >> ltuple_id_pod)
  {
    // Read the col bound.

    lstream >> lcol_bound[0];
    lstream >> lcol_bound[1];
    lstream >> lcol_bound[2];

    // Create the bounds descriptor.

    poset_bounds_descriptor
      ldesc(poset_bounds_descriptor::int_to_mode(lcol_bound[0]),
	    lcol_bound[1],
	    lcol_bound[2]);

    // Insert in the bounds map.
    // Implicitly converts ltuple_id_pod to unscoped scoped_index,
    // which is what we want, for now.

    map_type::value_type lval(ltuple_id_pod, ldesc);
    scaffold().dof_tuple_col_bounds().insert(lval);
  }

  if(scaffold().is_write_transaction())
  {
    // We're re-reading the col bounds attribute in
    // a multistep write protocol. The member and subposet
    // index maps have already been created.

    // Translate the column bounds to internal ids.

    scaffold().translate_dof_tuple_col_bounds();
  }
  else
  {
    // This is a read operation. The member and subposet index maps
    // don't exist yet. Can not translate to internal ids until
    // the maps have been created when the members are read.
    // Will translate to internal ids
    // in poset_scaffold::translate_dof_tuple_col_bounds called
    // from dof_tuple_record_set::internalize.
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::dof_tuple_col_bounds_record::
transfer_poset_to_internal_buffer()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  poset_state_handle* lschema_host = scaffold().external_schema().host();

  /// @hack product subposet hack, version 2.
  /// Poset has to tell us which map to use to translate subposet id.

  stringstream lstream;

  lstream << "Dof tuple col bounds:" << endl;

  poset_scaffold::dof_tuple_col_bounds_type::iterator itr;

  for(itr  = scaffold().dof_tuple_col_bounds().begin();
      itr != scaffold().dof_tuple_col_bounds().end();
      itr++)
  {
    // Translate the bounds descriptor to external ids.

    poset_bounds_descriptor ldesc = itr->second;

#ifdef DIAGNOSTIC_OUTPUT
    cout << "before: "
	 << " mode: " << ldesc.mode()
	 << " lb: " << ldesc.lb_id()
	 << " ub: " << ldesc.ub_id()
	 << endl;
#endif

    pod_index_type lb_ext_id;
    if(ldesc.lb_is_member())
    {
      lb_ext_id =
	lschema_host->get_ext_id(ldesc.lb_id(),
				 scaffold().file_id_space_name(),
				 false);
    }
    else
    {
      lb_ext_id = scaffold().subposet_ext_id(ldesc.lb_id()).hub_pod();
    }
    ldesc.put_lb_id(lb_ext_id);

    pod_index_type ub_ext_id;
    if(ldesc.ub_is_member())
    {
      ub_ext_id =
	lschema_host->get_ext_id(ldesc.ub_id(),
				 scaffold().file_id_space_name(),
				 false);
    }
    else
    {
      ub_ext_id = scaffold().subposet_ext_id(ldesc.ub_id()).hub_pod();
    }
    ldesc.put_ub_id(ub_ext_id);

#ifdef DIAGNOSTIC_OUTPUT
    cout << "after:  "
	 << " mode: " << ldesc.mode()
	 << " lb: " << ldesc.lb_id()
	 << " ub: " << ldesc.ub_id()
	 << endl;
#endif

    lstream << itr->first << " "
	    << poset_bounds_descriptor::mode_to_int(ldesc.mode()) << " "
	    << ldesc.lb_id() << " "
	    << ldesc.ub_id() << endl;
  }

  // Have to copy stringstream to string
  // because can't get C string from stringstream.
  // Could use strstream, but that's error-prone and not portable.

  _str_buf = lstream.str();

  put_is_internal(true);
  put_is_external(false);

  // Postconditions:

  ensure(is_internal());
  ensure(!is_external());

  // Exit

  return;
}




