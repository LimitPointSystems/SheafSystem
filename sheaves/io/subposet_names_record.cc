// $RCSfile: subposet_names_record.cc,v $ $Revision: 1.27 $ $Date: 2013/01/12 17:17:37 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class subposet_names_record

#include "subposet_names_record.h"

#include "assert_contract.h"
#include "std_sstream.h"

// =============================================================================
// ANY FACET
// =============================================================================

///
sheaf::subposet_names_record*
sheaf::subposet_names_record::
clone() const
{
  subposet_names_record* result;

  // Preconditions:

  // Body:

  result = new subposet_names_record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
bool
sheaf::subposet_names_record::
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
sheaf::subposet_names_record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const subposet_names_record*>(other) != 0;

  // Postconditions:

  return result;

}

// =============================================================================
// SUBPOSET_NAMES_RECORD FACET
// =============================================================================

///
sheaf::subposet_names_record::
subposet_names_record(poset_scaffold& xscaffold)
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
sheaf::subposet_names_record::
subposet_names_record(const subposet_names_record& xother)
    : attributes_record(xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}

///
sheaf::subposet_names_record::
~subposet_names_record()
{

  // Preconditions:

  // Body:

  // Nothing specific to do.

  // Postconditions:

  // Exit:

  return;
}


// =============================================================================
// PROTECTED MEMBER FUNCTIONS
// =============================================================================

///
void
sheaf::subposet_names_record::
transfer_internal_buffer_to_poset()
{
  // Preconditions:

  require(is_internal());
  require(scaffold().structure().state_is_read_write_accessible());

  // Body:

  if(scaffold().structure_is_namespace())
  {
    // Delete the existing name for the namespace;
    // let it be reset from the file.

    scaffold().structure().whole().delete_all_names();
  }

  if(scaffold().is_versioned())
  {
    // Version 0 is just an alias for the coarsest common refinement
    // until version 1 is created, at which time the version 0 subposets
    // are created independently. This poset has multiple versions and 
    // hence independent version 0 subposets; delete the aliases created
    // by default in poset_state_handle::initialize_standard_subposets
    // so that put_name below will succeed for version 0 subposets.

    string ver_0_whole_name(scaffold().structure().version_to_name(0));

    scaffold().structure().delete_subposet_name(ver_0_whole_name, false);
    scaffold().structure().delete_subposet_name(ver_0_whole_name+"_jims", false);
  } 

  // Initialize the stream.

  stringstream lstream(_str_buf);

  // Skip the header line:

  lstream.ignore(numeric_limits<streamsize>::max(), '\n');

  // The subposets included in the poset when the file was written
  // can be categorized according to 3 attributes:
  // persistent/volatile, name/unnamed, standard/non-standard
  //
  // None of the volatile subposets are written to the file,
  // and we assume all standard subposets are named, leaving 3 
  // categories:
  //
  // persistent, named, standard
  // persistent, named, non-standard
  // persistent, unnamed, non-standard
  //
  // All the standard subposets are created and given
  // at least one name when the poset is created, 
  // so we have to make sure that any additional names
  // for the standard members are set and
  // the non-standard subposets are created and named.

  // Initialize the subposet id map.

  scaffold().initialize_subposet_id_space();

  poset_state_handle& lposet = scaffold().structure();
  vector<subposet*>& lspv = scaffold().subposets();
  int lsp_id;
  bool lis_std_sp;
  string lsp_name;
  block<string> lall_names(4);
  
  while(lstream >> lsp_id)
  {
    // Skip the space before the name

    lstream.ignore();

    // The rest of the line is a string of tab-separated names,
    // including possible leading or embedded white space.

    lall_names.set_ct(0);
    getline(lstream, lsp_name, '\t');
    while(!lsp_name.empty())
    {
      lall_names.push_back(lsp_name);
      getline(lstream, lsp_name, '\t');
    }  

#ifdef DIAGNOSTIC_OUTPUT
    cout << "lsp_id: " << lsp_id
	 << "  names: " << lall_names
	 << endl;
#endif
    

    if(lall_names.ct() == 0)
    {
      // This subposet has no name;
      // just create it.

      lspv[lsp_id] = new subposet(&lposet);
    }
    else
    {
      if(lposet.includes_subposet(lall_names[0], false))
      {
	// A subposet with this primary name already exists, 
	// get a handle and put it in the buffer.

	lspv[lsp_id] = new subposet(&lposet, lall_names[0]);
      }
      else
      {
	// A subposet with this primary name does not exist.

	if(lsp_id == 1)
	{
	  // This is the whole subposet for the namespace poset; 
	  // the subposet exists, but  we've just deleted all its names.
	  // Don't create the subposet.

	  lspv[lsp_id] = new subposet(&lposet, WHOLE_INDEX);
	}
	else
	{
	  // Create the subposet.

	  lspv[lsp_id] = new subposet(&lposet);
	}

	// Give the subposet its primary name.
	
	lspv[lsp_id]->put_name(lall_names[0], true, false);
      }
      
      // Put the rest of the names.

      for(int i=1; i<lall_names.ct(); ++i)
      {
	if(!lspv[lsp_id]->has_name(lall_names[i]))
	{
	  lspv[lsp_id]->put_name(lall_names[i], false, false);
	}
      }
    }

    // Enter the subposet in the subposet index map.

    scaffold().subposet_id_space().insert(lsp_id, lspv[lsp_id]->index());
  }

  // Now that the subposets have been created, we can attach
  // the resident subposet handle in the scaffold.

  scaffold().resident().attach_to_state(&lposet, "resident");


  // Postconditions:

  ensure(invariant());
  ensure(is_internal());

  // Exit

  return;
}

///
void
sheaf::subposet_names_record::
transfer_poset_to_internal_buffer()
{
  // Preconditions:

  require(scaffold().structure().state_is_read_accessible());

  // Body:

  stringstream lstream;

  lstream << "Subposet names:" << endl;

  // Put all the names for all the subposets in the file;
  // don't skip the standard subposets.
  // This ensures we get any alternate names for standard subposets;
  // will skip standard names when we read the file.

  block<string> lall_names;
  int lsp_ub  = scaffold().subposets().size();
  for(int i=0; i<lsp_ub; i++)
  {
    subposet* lsp = scaffold().subposets()[i];
    
    lsp->all_names(lall_names);

    lstream << i << " ";
    for(int j=0; j<lall_names.ct(); ++j)
    {
      lstream << lall_names[j] << '\t';
    }
    lstream << '\t' << endl;
    
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



