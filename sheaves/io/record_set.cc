
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//



// Implementation for class record_set

#include "record_set.h"

#include "data_converter.h"
#include "error_message.h"
#include "namespace_poset.h"
#include "record_index.h"
#include "assert_contract.h"
#include "sheaf_file.h"
#include "record.h"

//#define DIAGNOSTIC_OUTPUT
//#undef DIAGNOSTIC_OUTPUT

// =============================================================================
// ANY FACET
// =============================================================================


///
sheaf::record_set*
sheaf::record_set::
clone() const
{
  record_set* result = 0;
  // Initialized to keep
  // some compilers from complaining.

  // Preconditions:

  // Body:

  // Class is abstract;
  // can't create an instance.

  not_implemented();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
bool
sheaf::record_set::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(file().is_open());
    invariance(!name().empty());
    invariance(record_buffer_ub() >= 0);
    invariance(record_buffer_ct() >= 0);
    invariance(record_buffer_ct() <= record_buffer_ub());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::record_set::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const record_set*>(other) != 0;

  // Postconditions:

  return result;

}


// =============================================================================
// RECORD_SET FACET
// =============================================================================

///
sheaf::record_set::
record_set(const sheaf_file& xfile, int xrecord_buffer_ub, const poset_scaffold& xscaffold)
  : _file(const_cast<sheaf_file&>(xfile)),
    _name(xscaffold.structure().name()),
    _record_buffer_ub(xrecord_buffer_ub),
    _scaffold(const_cast<poset_scaffold&>(xscaffold))
{

  // Preconditions:

  require(xfile.is_open());
  require(xrecord_buffer_ub > 0);

  // Body:  

  // Set hdf ids to indicate invalid status

  _hdf_id               = NOT_AN_HDF_ID;
  _int_dataspace_hdf_id = NOT_AN_HDF_ID;
  _ext_dataspace_hdf_id = NOT_AN_HDF_ID;
  _int_data_type_hdf_id = NOT_AN_HDF_ID;
  _ext_data_type_hdf_id = NOT_AN_HDF_ID;


  // No records active.

  _record_buffer_ct = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_open());
  ensure(record_buffer_ub() == xrecord_buffer_ub);
  ensure(record_buffer_ct() == 0);
}


///
sheaf::record_set::
record_set(const record_set& xother)
    : _file(xother._file), _scaffold(xother._scaffold)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());
}

///
sheaf::record_set::
~record_set()
{

  // Preconditions:

  // Body:


  // Postconditions:

  // Exit:

  return;
}




///
const sheaf::sheaf_file&
sheaf::record_set::
file() const
{
  return _file;
}




///
string
sheaf::record_set::
name() const
{

  // Preconditions:

  // Body:

  string result(_name);

  // Postconditions:

  ensure(!result.empty());

  // Exit

  return result;
}



///
string
sheaf::record_set::
alias() const
{

  // Preconditions:

  // Body:

  string result(_alias);

  // Postconditions:

  //  ensure(!scaffold().structure_is_namespace() == (name() == result));

  // Exit

  return result;
}


const string&
sheaf::record_set::
name_space_alias()
{
  static const string result(poset_path::reserved_prefix() + "name_space");
  return result;
}

const string&
sheaf::record_set::
name_space_prefix()
{
  static const string result(poset_path::reserved_prefix() + "name_space.");
  return result;
}

const string&
sheaf::record_set::
suffix() const
{
  // cout << endl << "Entering record_set::suffix." << endl;

  // Preconditions:


  // Body:

  // Empty in this call, redefined in descendants.

  static const string result;

  // Postconditions:


  // Exit:

  // cout << "Leaving record_set::suffix." << endl;
  return result;
}

string
sheaf::record_set::
data_set_name(const string& xname) const
{
  // cout << endl << "Entering record_set::data_set_name." << endl;

  // Preconditions:


  // Body:

  string result;
  if(scaffold().structure_is_namespace())
  {
    result = name_space_prefix() + xname + suffix();
  }
  else
  {
    result = xname + suffix();
  }

  // Postconditions:

  ensure(scaffold().structure_is_namespace() ? result == name_space_prefix() + xname + suffix() : result == xname + suffix());
  

  // Exit:

  // cout << "Leaving record_set::data_set_name." << endl;
  return result;
}

string
sheaf::record_set::
data_set_alias(const string& xname) const
{
  // cout << endl << "Entering record_set::data_set_alias." << endl;

  // Preconditions:


  // Body:

  string result;
  if(scaffold().structure_is_namespace())
  {
    result = name_space_alias() + suffix();
  }
  else
  {
    result = xname + suffix();
  }

  // Postconditions:

  ensure(scaffold().structure_is_namespace() ? result == name_space_alias() + suffix() : result == xname + suffix());
  

  // Exit:

  // cout << "Leaving record_set::data_set_alias." << endl;
  return result;
}


string
sheaf::record_set::
poset_name() const
{
  // cout << endl << "Entering attributes_record_set::poset_name." << endl;

  // Preconditions:

  // Body:

  // Skip past namespace prefix, if there is one.

  string::size_type lprefix_len = name_space_prefix().size();

  string::size_type lname_begin;
  if(_name.substr(0, lprefix_len) == name_space_prefix())
  {
    lname_begin = lprefix_len;
  }
  else
  {
    lname_begin = 0;
  }
  
  string::size_type lsuffix_begin = suffix().empty() ? _name.size() : _name.rfind(suffix());
  
  // Extract the name.

  string::size_type lname_len = lsuffix_begin - lname_begin;
  
  string result(_name.substr(lname_begin, lname_len));

  // Postconditions:


  // Exit:

  // cout << "Leaving attributes_record_set::poset_name." << endl;
  return result;
}


///
sheaf::poset_scaffold&
sheaf::record_set::
scaffold()
{
  return _scaffold;
}

///
const sheaf::poset_scaffold&
sheaf::record_set::
scaffold() const
{
  return _scaffold;
}

///
sheaf::poset_data_type_map&
sheaf::record_set::
type_map()
{
  return _scaffold.type_map();
}



///
const sheaf::poset_data_type_map&
sheaf::record_set::
type_map() const
{
  return _scaffold.type_map();
}

///
void
sheaf::record_set::
open()
{
  // Preconditions:

  require(file().is_open());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  cout << "record_set::open: opening dataset " << alias() << endl;
#endif

  // Create the internal HDF data type.

  create_int_data_type();

  // Attempt to open the dataset using its alias.
  // Need to use alias because if we're reading the namespace,
  // we don't yet know its name.

  _hdf_id = H5Dopen1(_file.hdf_id(), _alias.c_str());

  if(_hdf_id < 0)
  {
    // Attempt to open dataset failed.

    if(file().mode() == sheaf_file::READ_WRITE)
    {
      // Open failed and we're writing the file; create the dataset

#ifdef DIAGNOSTIC_OUTPUT
      cout << endl << "record_set::open: open failed, creating dataset " << name() << endl << endl;
#endif

      _hdf_id = create_dataset();

      if(_alias != _name)
      {
        // Create a link from the alias to the dataset.

        create_alias();
      }
    }
    else
    {
      // Open failed and we're reading the file;
      // it is an error if the dataset does not already exist.

      post_fatal_error_message("dataset doesn't exist");
    }
  }
  else
  {
    // Open succeeded;
    // we're doing either a read the file or
    // a subsequent (not first) partial write.


    if( file().mode() == sheaf_file::READ_ONLY)
    {
      // We're doing a read.

      if(_alias != _name)
      {
        // Set _name to the primary name of the data set.

        set_name_from_alias();
      }
    }


    // Read the attributes, if any.
    // If we're doing a read, this reads and initializes all the attributes.
    // If we're doing a subsequent partial write, this extends the attributes
    // in memory to incorporate all those previously written. There doesn't
    // seem to be any way to directly extend the attributes on disk in HDF.

    read_dataset_attributes();
  }

  // Now the dataset is open;
  // get the dataspace, data type, and extent

  _ext_dataspace_hdf_id = H5Dget_space(_hdf_id);
  if(_ext_dataspace_hdf_id < 0)
  {
    post_fatal_error_message("unable to get dataspace of open dataset");
  }

  _ext_data_type_hdf_id = H5Dget_type(_hdf_id);
  if(_ext_data_type_hdf_id < 0)
  {
    post_fatal_error_message("unable to get data type of open dataset");
  }

  int lrank = H5Sget_simple_extent_dims(_ext_dataspace_hdf_id, _ext_dataspace_dims, NULL);
  if(lrank != ext_dataspace_rank())
  {
    post_fatal_error_message("unable to get dimensions of open dataset");
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_open());

  // Exit

  return;
}



///
bool
sheaf::record_set::
is_open() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _hdf_id >= 0;

  // Postconditions:

  // Exit

  return result;
}


///
void
sheaf::record_set::
close()
{
  // Preconditions:

  // Body:


  // Write the attributes.

  if(file().mode() == sheaf_file::READ_WRITE)
  {
    write_dataset_attributes();
  }

  // Close all the resources allocated for this record set.

  if(_int_data_type_hdf_id >= 0)
    H5Tclose(_int_data_type_hdf_id);
  if(_ext_data_type_hdf_id >= 0)
    H5Tclose(_ext_data_type_hdf_id);
  if(_int_dataspace_hdf_id >= 0)
    H5Sclose(_int_dataspace_hdf_id);
  if(_ext_dataspace_hdf_id >= 0)
    H5Sclose(_ext_dataspace_hdf_id);
  if(_hdf_id >= 0)
    H5Dclose(_hdf_id);

  _int_data_type_hdf_id = NOT_AN_HDF_ID;
  _ext_data_type_hdf_id = NOT_AN_HDF_ID;
  _int_dataspace_hdf_id = NOT_AN_HDF_ID;
  _ext_dataspace_hdf_id = NOT_AN_HDF_ID;
  _hdf_id               = NOT_AN_HDF_ID;

  // Postconditions:

  ensure(!is_open());

  // Exit

  return;
}



///
int
sheaf::record_set::
record_buffer_ct() const
{
  return _record_buffer_ct;
}

///
void
sheaf::record_set::
inc_record_buffer_ct()
{
  // Preconditions:

  // Body:

  _record_buffer_ct++;

  // Postconditions:


  // Exit:

  return;
}

///
void
sheaf::record_set::
reset_record_buffer_ct()
{
  // Preconditions:


  // Body:

  _record_buffer_ct = 0;

  // Postconditions:

  ensure(record_buffer_is_empty());

  // Exit:

  return;
}



///
int
sheaf::record_set::
record_buffer_ub() const
{
  return _record_buffer_ub;
}



///
bool
sheaf::record_set::
record_buffer_is_empty() const
{
  return _record_buffer_ct == 0;
}



///
bool
sheaf::record_set::
record_buffer_is_full() const
{
  return _record_buffer_ct >= _record_buffer_ub;
}


// =============================================================================
// PROTECTED MEMBER FUNCTIONS
// =============================================================================

///
hid_t
sheaf::record_set::
create_dataset()
{
  hid_t result = NOT_AN_HDF_ID;

  // Preconditions:

  require(file().mode() == sheaf_file::READ_WRITE);

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

///
void
sheaf::record_set::
create_int_data_type()
{
  // Preconditions:

  require(file().is_open());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(int_data_type_hdf_id() >= 0);

  // Exit:

  return;
}

///
void
sheaf::record_set::
extend_dataset(const hsize_t* xdims, int xdims_ub)
{
  // Preconditions:

  require(is_open());
  require(xdims_ub >= ext_dataspace_rank());

  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  cout << "record_set::extend_dataset: dataspace extent:"
  << "xdims_ub= " << xdims_ub <<  "xdims= ";
  for(int i=0; i<xdims_ub; i++)
  {
    cout << " " << xdims[i];
  }
  cout << endl;
#endif

  // Extend the dataset to include the selection;

  herr_t status = H5Dextend(_hdf_id, xdims);
  if(status < 0)
  {
    post_fatal_error_message("can't extend member record dataset");
  }

  // Close the old dataspace to prevent resource leaks.

  status = H5Sclose(_ext_dataspace_hdf_id);
  if(status < 0)
  {
    post_fatal_error_message("can't close member record set dataspace");
  }

  // Extending the dataset creates a new dataspace, get it.

  _ext_dataspace_hdf_id = H5Dget_space(_hdf_id);
  if(_ext_dataspace_hdf_id < 0)
  {
    post_fatal_error_message("can't get extended member record set dataspace");
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "record_set::extend_dataset: dataspace extent:";
  for(int i=0; i<ext_dataspace_rank(); i++)
  {
    cout << " " << _ext_dataspace_dims[i];
  }
  cout << endl;
#endif

  // Update the current dimensions

  int lrank = H5Sget_simple_extent_dims(_ext_dataspace_hdf_id, _ext_dataspace_dims, NULL);
  if(lrank != ext_dataspace_rank())
  {
    post_fatal_error_message("unable to get dimensions of extended dataset");
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "record_set::extend_dataset: dataspace extent:";
  for(int i=0; i<ext_dataspace_rank(); i++)
  {
    cout << " " << _ext_dataspace_dims[i];
  }
  cout << endl;
#endif

  // Postconditions:

  ensure(ext_dataspace_dim(0) >= xdims[0]);
  ensure(unexecutable("for all 0 <= i < ext_dataspace_rank(): ext_dataspace_dim(i) == xdims[i]"));

  /// @todo make above executable and remove first postcondition.

  // Exit

  return;
}

///
void
sheaf::record_set::
create_alias()
{
  // Preconditions:

  require(alias() != name());
  require(is_open());

  // Body:

  // Create a link from the alias to the dataset.

  herr_t status = H5Glink(file().hdf_id(), H5G_LINK_SOFT, _name.c_str(), _alias.c_str());

  if(status < 0)
  {
    post_fatal_error_message("can't create soft link for alias");
  }

  // Postconditions:

  ensure(unexecutable("link from alias to data set exists"));

  // Exit

  return;
}

///
void
sheaf::record_set::
set_name_from_alias()
{
  // Preconditions:

  require(alias() != name());
  require(is_open());

  // Body:

  // Get the primary name of the dataset.

  // First have to get the length of the name.

  H5G_stat_t lstatbuf;
  hbool_t lfalse = 0;
  herr_t status = H5Gget_objinfo(file().hdf_id(), _alias.c_str(), lfalse, &lstatbuf);
  if(status < 0)
  {
    post_fatal_error_message("can't get_objinfo for alias");
  }

  // Now we can allocate a buffer and get the name.

  char* lname = new char[lstatbuf.linklen];
  status = H5Gget_linkval(file().hdf_id(), _alias.c_str(), lstatbuf.linklen, lname);
  if(status < 0)
  {
    post_fatal_error_message("can't get_linkval for alias");
  }

  // Set the name.

  _name = lname;

  // Clean up.

  delete [] lname;

  // Postconditions:

  ensure(!name().empty());

  // Exit

  return;
}


hid_t
sheaf::record_set::
hdf_id()
{
  return _hdf_id;
}

hid_t
sheaf::record_set::
ext_dataspace_hdf_id()
{
  return _ext_dataspace_hdf_id;
}

hid_t
sheaf::record_set::
ext_data_type_hdf_id()
{
  return _ext_data_type_hdf_id;
}

int
sheaf::record_set::
ext_dataspace_rank()
{
  return _ext_dataspace_rank;
}



///
hsize_t
sheaf::record_set::
ext_dataspace_dim(int xi)
{
  hsize_t result;

  // Preconditions:

  require(is_open());
  require((0 <= xi) && (xi < ext_dataspace_rank()));

  // Body:

  result = _ext_dataspace_dims[xi];

  // Postconditions:

  // Exit

  return result;
}

hid_t
sheaf::record_set::
int_dataspace_hdf_id()
{
  return _int_dataspace_hdf_id;
}

hid_t
sheaf::record_set::
int_data_type_hdf_id()
{
  return _int_data_type_hdf_id;
}



const hid_t sheaf::record_set::NOT_AN_HDF_ID = -1;

void
sheaf::record_set::
read_dataset_attributes()
{
  // Preconditions:

  require(is_open());

  // Body:

  // Stub in this class, just to establish contract;
  // intended to be redefined in descendants.

  // Postconditions:

  ensure(unexecutable("all attributes opened, read, and closed"));

  // Exit

  return;
}

void
sheaf::record_set::
write_dataset_attributes()
{
  // Preconditions:

  require(is_open());

  // Body:

  // Stub in this class, just to establish contract;
  // intended to be redefined in descendants.

  // Postconditions:

  ensure(unexecutable("all attributes created, written, and closed"));

  // Exit

  return;
}

///
void
sheaf::record_set::
read_attribute(const char*& xatt_values,
               size_type& xatt_ct,
               const data_converter* xatt_conv,
               const string& xatt_name)
{
  // Preconditions:

  require(is_open());
  require(xatt_values == 0);
  require(xatt_ct == 0);
  require(xatt_conv != 0);
  require(!xatt_name.empty());


  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  cout << "record_set::read_attribute poset name: "
  << scaffold().structure().name()
  << endl;
#endif

  herr_t lstatus;

  // Open the attribute.

  hid_t latt_hdf_id = H5Aopen_name(_hdf_id, xatt_name.c_str());
  if(latt_hdf_id >= 0)
  {
    // Open succeeded; get the attribute data space and extent.

    hid_t latt_dataspace_hdf_id = H5Aget_space(latt_hdf_id);
    if(latt_dataspace_hdf_id < 0)
    {
      string lmsg("Unable to get dataspace for attribute ");
      lmsg += xatt_name;
      post_fatal_error_message(lmsg.c_str());
    }

    hsize_t latt_ct;
    lstatus = H5Sget_simple_extent_dims(latt_dataspace_hdf_id, &latt_ct, NULL);
    if(lstatus < 0)
    {
      string lmsg("Unable to get extent for attribute ");
      lmsg += xatt_name;
      post_fatal_error_message(lmsg.c_str());
    }


    // Create some storage for the types map that HDF can access.
    // Client must delete this storage.

    xatt_ct = latt_ct*xatt_conv->internal_size();
    xatt_values = new char[xatt_ct];

    // Read the types attribute

    lstatus = H5Aread(latt_hdf_id, xatt_conv->internal_type(), const_cast<char*&>(xatt_values));
    if(lstatus < 0)
    {
      string lmsg("Unable to read attribute ");
      lmsg += xatt_name;
      post_fatal_error_message(lmsg.c_str());
    }

    // Close the attribute and dataspace.

    H5Sclose(latt_dataspace_hdf_id);
    H5Aclose(latt_hdf_id);

  }
  else
  {
    // Open failed. Dof tuple count must be 0. Do nothing.
  }

  // Postconditions:

  ensure((xatt_values == 0) == (xatt_ct == 0));

  // Exit

  return;
}


///
void
sheaf::record_set::
write_attribute(const void* xatt_values,
                size_type xatt_ct,
                const data_converter* xatt_conv,
                const string& xatt_name)
{
  // Preconditions:

  require(xatt_values != 0);
  require(xatt_ct > 0);
  require(xatt_conv != 0);
  require(!xatt_name.empty());

  // Body:

  herr_t lstatus;

  // Delete any existing version of the attribute.
  // Delete will fail if attribute doesn't exist, ignore the return status.

  /// @issue does deleting and rewriting the attribute everytime we write to
  /// the dataset imply a resource leak in the file?

  lstatus = H5Adelete(_hdf_id, xatt_name.c_str());

  // Create the attribute data space.

  hid_t latt_dataspace_hdf_id = H5Screate(H5S_SIMPLE);
  if(latt_dataspace_hdf_id < 0)
  {
    string lmsg("Unable to create dataspace for attribute ");
    lmsg += xatt_name;

    post_fatal_error_message(lmsg.c_str());
  }

  // Set the extent of the dataspace.

  hsize_t hatt_ct = xatt_ct;
  lstatus = H5Sset_extent_simple(latt_dataspace_hdf_id, 1, &hatt_ct, NULL);
  if(lstatus < 0)
  {
    string lmsg("Unable to set extent for attribute ");
    lmsg += xatt_name;
    post_fatal_error_message(lmsg.c_str());
  }

  // Create the attribute.

  //  hid_t latt_hdf_id = H5Acreate(_hdf_id,
  hid_t latt_hdf_id = H5Acreate1(_hdf_id,
                                xatt_name.c_str(),
                                xatt_conv->external_type(),
                                latt_dataspace_hdf_id,
                                H5P_DEFAULT);
  if(latt_hdf_id < 0)
  {
    string lmsg("Unable to create attribute ");
    lmsg += xatt_name;
    post_fatal_error_message(lmsg.c_str());
  }

  // Write the attribute.

  lstatus = H5Awrite(latt_hdf_id, xatt_conv->internal_type(), xatt_values);
  if(lstatus < 0)
  {
    string lmsg("Unable to write attribute ");
    lmsg += xatt_name;
    post_fatal_error_message(lmsg.c_str());
  }

  // Close the attribute and dataspace.

  H5Sclose(latt_dataspace_hdf_id);
  latt_dataspace_hdf_id = NOT_AN_HDF_ID;

  H5Aclose(latt_hdf_id);
  latt_hdf_id = NOT_AN_HDF_ID;

  // Postconditions:


  // Exit:

  return;
}
