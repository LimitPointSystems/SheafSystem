
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class poset_dof_map

#include "poset_dof_map.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "dof_descriptor_array.h"
#include "dof_map_factory.h"
#include "poset_dof_iterator.h"
#include "poset_state_handle.h"
#include "primitive_value.h"
#include "std_strstream.h"

//#define DIAGNOSTIC_OUTPUT

// PUBLIC MEMBER FUNCTIONS

const string&
sheaf::poset_dof_map::
class_name() const
{
  // Preconditions:

  // Body:

  const string& result = static_class_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const string&
sheaf::poset_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("poset_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "poset_dof_map");

  // Exit:

  return result;
}

sheaf::poset_dof_map*
sheaf::poset_dof_map::
new_dof_map(const string& xclass_name, dof_tuple_type xsheaf_base_class_id)
{
  poset_dof_map* result;

  // Preconditions:

  // Body:

  result = factory().new_dof_map(xclass_name, xsheaf_base_class_id);

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_initialized());

  // Exit:

  return result;
}




// CANONICAL MEMBERS

sheaf::poset_dof_map*
sheaf::poset_dof_map::
clone() const
{
  poset_dof_map* result = 0; // To silence compiler warnings.

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(poset_dof_map()));

  // Exit:

  return result;
}

sheaf::poset_dof_map*
sheaf::poset_dof_map::
copy() const
{
  poset_dof_map* result = 0; // Just to silece compiler warnings.

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(result->is_same_type(this));
  ensure(postcondition_of(poset_dof_map(*this)));

  // Exit:

  return result;
}

sheaf::poset_dof_map&
sheaf::poset_dof_map::
operator=(const poset_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Need ref_ct == 0 to ensure no poset members
  // have a pointer to the schema, which may be deleted.

  require(ref_ct() == 0);

  // Body:

  _host = xother._host;
  _index = xother._index;

  if(_schema != 0)
  {
    _schema->detach_from_state();
    delete _schema;
  }
  _schema = xother._schema->clone();
  _schema->attach_to_state(xother._schema);

  _is_table_dof_map = xother._is_table_dof_map;
  _dof_ct = xother._dof_ct;
  _dof_tuple_ub = xother._dof_tuple_ub;
  _ref_ct = 0;


  // Postconditions:

  ensure(host() == xother.host());
  ensure(index() == xother.index());
  ensure(schema().is_same_state(&xother.schema()));
  ensure(is_table_dof_map() == xother.is_table_dof_map());
  ensure(dof_ct() == xother.dof_ct());
  ensure(dof_tuple_ub() == xother.dof_tuple_ub());
  ensure(ref_ct() == 0);

  // Exit

  return *this;
}


sheaf::poset_dof_map::
~poset_dof_map()
{

  // Preconditions:

  require(ref_ct() == 0);

  // Body:

  if(_schema != 0)
  {
    _schema->detach_from_state();
    delete _schema;
  }

  // Postconditions:

  // Exit

  return;
}


bool
sheaf::poset_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    /// @todo finish poset_dof_map::invariant.

    /// @hack unexecutable because schema().version(true) requires read access.

    invariance(unexecutable("is_initialized() ? version() == schema().version(true) : true"));


    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// MAP INTERFACE

void
sheaf::poset_dof_map::
init_row_dof_map(const poset_state_handle* xhost,
                 pod_index_type xschema_mbr_id,
                 int xschema_version)
{

  // Preconditions:

  require(!is_initialized());
  require(xhost != 0);
  require(xhost->state_is_read_accessible());

  // Note that we do not require the schema to <= the host schema.
  // Although usually the case, is not actually a requirement for
  // this routine and there is at least one application where it is violated.
  // See dof_tuple_record_set::read_records, the external dof map
  // may be allocated on a schema greater than the host, if the host
  // has been restricted.

  require(xhost->schema().host()->contains_member(xschema_mbr_id));
  require(xhost->schema().host()->has_version(xschema_version));

  // Body:

  _host   = const_cast<poset_state_handle*>(xhost);

  _index.invalidate();
  _index.put_scope(_host->dof_tuple_hub_id_space(false));

  _schema = xhost->schema().clone();
  _schema->attach_to_state(xhost->schema().host(), xschema_mbr_id);

  // Force the version to be unaliased.

  _schema->put_version(xschema_version, true);

  _is_table_dof_map = false;
  _dof_ct       = _schema->row_dof_ct();
  _dof_tuple_ub = _schema->row_dof_tuple_ub();

  _ref_ct = 0;

  allocate_dofs();

  // Postconditions:

  ensure(is_initialized());
  ensure(host() == xhost);
  ensure(!index().is_valid());
  ensure(index().same_scope(host()->dof_tuple_hub_id_space(false)));
  ensure(is_table_dof_map() == false);
  ensure(dof_ct() == schema().row_dof_ct());
  ensure(dof_tuple_ub() == schema().row_dof_tuple_ub());
  ensure(version() == schema().version(true));
  ensure(ref_ct() == 0);
  ensure(schema().index() == xschema_mbr_id);
  ensure(version() == schema().unaliased_version(xschema_version));

  // Exit

  return;
}

void
sheaf::poset_dof_map::
init_row_dof_map(const poset_state_handle* xhost,
                 const scoped_index& xschema_mbr_id,
                 int xschema_version)
{

  // Preconditions:

  require(!is_initialized());
  require(xhost != 0);
  require(xhost->state_is_read_accessible());

  // Note that we do not require the schema to <= the host schema.
  // Although usually the case, is not actually a requirement for
  // this routine and there is at least one application where it is violated.
  // See dof_tuple_record_set::read_records, the external dof map
  // may be allocated on a schema greater than the host, if the host
  // has been restricted.

  require(xhost->schema().host()->contains_member(xschema_mbr_id));
  require(xhost->schema().host()->has_version(xschema_version));

  // Body:

  init_row_dof_map(xhost, xschema_mbr_id.hub_pod(), xschema_version);

  // Postconditions:

  ensure(is_initialized());
  ensure(host() == xhost);

  ensure(!index().is_valid());

  ensure(is_table_dof_map() == false);
  ensure(dof_ct() == schema().row_dof_ct());
  ensure(dof_tuple_ub() == schema().row_dof_tuple_ub());
  ensure(version() == schema().version(true));
  ensure(ref_ct() == 0);
  ensure(schema().index() ==~ xschema_mbr_id);
  ensure(version() == schema().unaliased_version(xschema_version));

  // Exit

  return;
}

bool
sheaf::poset_dof_map::
is_initialized() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_schema != 0);

  // Postconditions:

  // Exit

  return result;
}


 

sheaf::poset_state_handle*
sheaf::poset_dof_map::
host() const
{
  poset_state_handle* result;

  // Preconditions:

  // Body:

  result = _host;

  // Postconditions:

  // Exit

  return result;
}

const sheaf::scoped_index&
sheaf::poset_dof_map::
index() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return _index;
}

sheaf::schema_poset_member&
sheaf::poset_dof_map::
schema()
{
  // Preconditions:

  require(is_initialized());

  // Body:

  schema_poset_member& result = *_schema;

  // Postconditions:

  // Exit

  return result;
}
 
const sheaf::schema_poset_member&
sheaf::poset_dof_map::
schema() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  schema_poset_member& result = *_schema;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_dof_map::
is_table_dof_map() const
{
  bool result;

  // Preconditions:


  // Body:

  result = _is_table_dof_map;

  // Postconditions:


  // Exit:

  return result;
}

 

int
sheaf::poset_dof_map::
dof_ct() const
{
  int result;

  // Preconditions:

  // Body:

  result = _dof_ct;

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

 

// ===========================================================
//  NEW DOF ACCESS FACET
// ===========================================================
 
sheaf::primitive_value
sheaf::poset_dof_map::
dof(pod_index_type xdof_id) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));

  // Body:

  primitive_value result;

  get_dof(xdof_id, &(result.value()), sizeof(primitive_buffer_type));

  result.id() = schema().type(xdof_id, _is_table_dof_map);  
  
  // Postconditions:


  // Exit:

  return result;
}

sheaf::primitive_value
sheaf::poset_dof_map::
dof(const scoped_index& xdof_id) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));

  // Body:

  pod_index_type lindex =
    schema().dof_id_space(_is_table_dof_map).pod(xdof_id);
  primitive_value result = dof(lindex);

  // Postconditions:
  
  // Exit:

  return result;
}

sheaf::primitive_value
sheaf::poset_dof_map::
dof(const string& xname) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(!xname.empty());
  require(schema().contains_dof(xname, is_table_dof_map()));

  // Body:

  pod_index_type lhub_id = schema().host()->member_id(xname, false);
  pod_index_type lindex = schema().dof_id_space(_is_table_dof_map).pod(lhub_id);
  primitive_value result = dof(lindex);

  // Postconditions:
  
  // Exit:

  return result;
}

void
sheaf::poset_dof_map::
put_dof(pod_index_type xdof_id, const primitive_value& xdof)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(xdof.id() == schema().type(xdof_id, is_table_dof_map()));
  
  // Body:

  put_dof(xdof_id, &(xdof.value()), sizeof(primitive_buffer_type));

  // Postconditions:

  ensure(dof(xdof_id) == xdof);
  
  // Exit:

  return;
}

void
sheaf::poset_dof_map::
put_dof(const scoped_index& xdof_id, const primitive_value& xdof)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));  
  //require(xdof.id() == schema().type(schema().dof_id_space(is_table_dof_map()).pod(xdof_id), is_table_dof_map()));
  require(xdof.id() == schema().type(xdof_id, is_table_dof_map(), false));
  
  // Body:

  pod_index_type lindex = schema().dof_id_space(_is_table_dof_map).pod(xdof_id);
  put_dof(lindex, xdof);
  
  // Postconditions:

  ensure(dof(xdof_id) == xdof);
  
  // Exit:

  return;
}

void
sheaf::poset_dof_map::
put_dof(const string& xname, const primitive_value& xdof)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().contains_dof(xname, is_table_dof_map()));  
  require(xdof.id() == schema().type(xname, is_table_dof_map(), false));
  
  // Body:

  pod_index_type lhub_id = schema().host()->member_id(xname, false);
  pod_index_type lindex = schema().dof_id_space(_is_table_dof_map).pod(lhub_id);
  put_dof(lindex, xdof);
  
  // Postconditions:

  ensure(dof(xname) == xdof);
  
  // Exit:

  return;
}

void
sheaf::poset_dof_map::
get_dof(pod_index_type xdof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));
  
  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
sheaf::poset_dof_map::
get_dof(const scoped_index& xdof_id, void* xdof, size_type xdof_size) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map(), false));

  // Body:

  pod_index_type lindex =
    schema().dof_id_space(_is_table_dof_map).pod(xdof_id);
  get_dof(lindex, xdof, xdof_size);

  // Postconditions:

  
  // Exit:

  return;
}

void
sheaf::poset_dof_map::
put_dof(pod_index_type xdof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map()));
  
  // Body:

  is_abstract();

  // Postconditions:

  
  // Exit:

  return;
}

void
sheaf::poset_dof_map::
put_dof(const scoped_index& xdof_id, const void* xdof, size_type xdof_size)
{
  // Preconditions:

  require(schema().state_is_read_accessible());
  require(schema().dof_id_space(is_table_dof_map()).contains(xdof_id));
  require(unexecutable("xdof points to buffer of size xdof_size"));
  require(xdof_size >= schema().size(xdof_id, is_table_dof_map(), false));
  
  // Body:

  pod_index_type lindex =
    schema().dof_id_space(_is_table_dof_map).pod(xdof_id);

  put_dof(lindex, xdof, xdof_size);

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
//  END NEW DOF ACCESS FACET
// ===========================================================

size_t
sheaf::poset_dof_map::
dof_tuple_ub() const
{
  size_t result;

  // Preconditions:


  // Body:

  result = _dof_tuple_ub;

  // Postconditions:


  // Exit:

  return result;
}



void
sheaf::poset_dof_map::
get_dof_tuple(arg_list& xargs) const
{
  // Preconditions:

  require(schema().state_is_read_accessible());

  // Body:

  poset_dof_iterator* litr = schema().dof_iterator(is_table_dof_map());
  while(!litr->is_done())
  {
    schema_poset_member& litem = litr->item();

    arg_list::arg_type larg;
    larg.name = litem.name();
    larg.put_type(litem.type());
    primitive_value& lvalue = larg.value;
    larg.value = dof(litem.index());

    xargs.push_back(larg);

    litr->next();
  }
  delete litr;

#ifdef DIAGNOSTIC_OUTPUT
  cout << "poset_dof_map::get_dof_tuple: " << endl;
  cout << "\thost name: " << host()->name() << endl;
  cout << "\tschema name: " << schema().name() << endl << endl;
  cout << xargs << endl;
#endif

  // Postconditions:

  ensure(invariant());
  ensure(xargs.ct() == dof_ct());
  ensure(xargs.conforms_to(schema(), is_table_dof_map(), false));

  /// @todo implement the following:
  /// ensure(xargs == *this);

  // Exit

  return;
}

void
sheaf::poset_dof_map::
put_dof_tuple(const arg_list& xargs)
{
  // Preconditions:

  require(dof_ct() == xargs.ct());
  require(schema().state_is_read_accessible());
  require(xargs.conforms_to(schema(), is_table_dof_map(), false));

  // Body:

  //#ifdef DIAGNOSTIC_OUTPUT
  cout << "poset_dof_map::put_dof_tuple: schema:: " << schema().name()
       << "  table_dof_descriptors: " << *(schema().table_dof_descriptors()) << endl;
  //#endif
  
  poset_dof_iterator* litr = schema().dof_iterator(is_table_dof_map());
  while(!litr->is_done())
  {
    schema_poset_member& litem = litr->item();
    
    int i = xargs.index(litem.name());

    // Precondition ensures i is valid.

    assertion(i != -1);

    put_dof(litem.index(), xargs.value(i));
    litr->next();
  }
  delete litr;

  //#ifdef DIAGNOSTIC_OUTPUT
  cout << *this << endl;
  //#endif

  // Postconditions:

  ensure(invariant());

  /// @todo implement the following:
  /// ensure(*this == xargs);
  ensure(unexecutable("xargs copied to dof tuple"));

  // Exit

  return ;
}


void
sheaf::poset_dof_map::
copy_dof_tuple(const poset_dof_map& xother)
{
  // cout << endl << "Entering poset_dof_map::copy_dof_tuple." << endl;

  // Preconditions:

  require(dof_ct() == xother.dof_ct());
  require(schema().state_is_read_accessible());
  require(xother.schema().state_is_read_accessible());
  //  require(schema().conforms_to(xother.schema(), is_table_dof_map()));
  //  require(xother.schema().conforms_to(schema(), is_table_dof_map()));

  // Body:

  arg_list largs;
  xother.get_dof_tuple(largs);
  put_dof_tuple(largs);
  
  // Postconditions:


  // Exit:

  // cout << "Leaving poset_dof_map::copy_dof_tuple." << endl;
  return;
}


void
sheaf::poset_dof_map::
put_defaults()
{
  // Preconditions:

  require(schema().state_is_read_accessible());

  // Body:

  poset_dof_iterator* ldof_itr = schema().dof_iterator(is_table_dof_map());

  while(!ldof_itr->is_done())
  {
    schema_poset_member& lmember = ldof_itr->item();

    put_dof(lmember.index(), primitive_value(lmember.type()));

    ldof_itr->next();
  }

  delete ldof_itr;

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(xargs copied to dof tuple));

  // Exit

  return ;
}

 

unsigned int
sheaf::poset_dof_map::
ref_ct() const
{
  unsigned int result;

  // Preconditions:


  // Body:

  result = _ref_ct;

  // Postconditions:


  // Exit:

  return result;
}

void
sheaf::poset_dof_map::
inc_ref_ct()
{
  // Preconditions:


  // Body:

  define_old_variable(unsigned int old_ref_ct = _ref_ct);

  _ref_ct++;

  // Postconditions:

  ensure(ref_ct() == old_ref_ct + 1);

  // Exit:

  return;
}

void
sheaf::poset_dof_map::
dec_ref_ct()
{
  // Preconditions:


  // Body:

  define_old_variable(unsigned int old_ref_ct = _ref_ct);

  _ref_ct--;

  // Postconditions:

  ensure(ref_ct() == old_ref_ct - 1);

  // Exit:

  return;
}

 

int
sheaf::poset_dof_map::
version() const
{
  int result;

  // Preconditions:

  require(is_initialized());

  // Body:

  result = _schema->version();

  // Postconditions:

  // $$TCP ensure(result == schema().version());

  // Exit

  return result;
}

const sheaf::index_space_handle&
sheaf::poset_dof_map::
client_id_space() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  const index_space_handle& result =
    _schema->dof_id_space(_is_table_dof_map);

  // Postconditions:

  ensure(result.is_attached());

  // Exit

  return result;
}

bool
sheaf::poset_dof_map::
supports_xfr_opt() const
{
  /// @hack dof tuple transfer hack.

  return false;
}


// PROTECTED MEMBER FUNCTIONS

sheaf::dof_map_factory&
sheaf::poset_dof_map::
factory()
{

  // Preconditions:


  // Body:

  static dof_map_factory result;

  // Postconditions:


  // Exit:

  return result;
}



// CANONICAL MEMBERS


sheaf::poset_dof_map::
poset_dof_map()
{

  // Preconditions:


  // Body:

  _host = 0;

  _index.invalidate();

  _schema = 0;
  _is_table_dof_map = false;
  _dof_ct = 0;
  _dof_tuple_ub = 0;
  _ref_ct = 0;

  // Postconditions:

  ensure(!is_initialized());
  ensure(host() == 0);

  ensure(!index().is_valid());

  ensure(is_table_dof_map() == false);
  ensure(dof_ct() == 0);
  ensure(dof_tuple_ub() == 0);
  ensure(ref_ct() == 0);

  // Exit

  return;
}


sheaf::poset_dof_map::
poset_dof_map(const poset_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  _host = const_cast<poset_dof_map&>(xother).host();
  _index = const_cast<poset_dof_map&>(xother).index();

  _schema = xother._schema->clone();
  _schema->attach_to_state(xother._schema);

  _is_table_dof_map = xother._is_table_dof_map;
  _dof_ct = const_cast<poset_dof_map&>(xother).dof_ct();
  _dof_tuple_ub = const_cast<poset_dof_map&>(xother).dof_tuple_ub();
  _ref_ct = 0;

  // Postconditions:

  ensure(is_initialized());
  ensure(host() == xother.host());
  ensure(index() == xother.index());
  ensure(schema().is_same_state(&xother.schema()));
  ensure(is_table_dof_map() == xother.is_table_dof_map());
  ensure(dof_ct() == xother.dof_ct());
  ensure(dof_tuple_ub() == xother.dof_tuple_ub());
  ensure(ref_ct() == 0);

  // Exit

  return;
}

// OTHER CONSTRUCTORS

sheaf::poset_dof_map::
poset_dof_map(const poset_state_handle* xhost, bool xis_table_dof_map)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());

  // Body:

  _host   = const_cast<poset_state_handle*>(xhost);

  _index.invalidate();
  _index.put_scope(_host->dof_tuple_hub_id_space(false));

  _schema = xhost->schema().clone();
  _schema->attach_to_state(&xhost->schema());

  // Force the version to be unaliased.

  _schema->put_version(_schema->version(), true);

  _is_table_dof_map = xis_table_dof_map;

  _dof_ct       = _schema->dof_ct(_is_table_dof_map);
  _dof_tuple_ub = _schema->dof_tuple_ub(_is_table_dof_map);

  _ref_ct = 0;

  // Postconditions:

  ensure(is_initialized());
  ensure(host() == xhost);

  ensure(!index().is_valid());
  ensure(index().same_scope(host()->dof_tuple_hub_id_space(false)));
  ensure(schema().is_same_state(&xhost->schema()));
  ensure(is_table_dof_map() == xis_table_dof_map);
  ensure(dof_ct() == schema().dof_ct(is_table_dof_map()));
  ensure(dof_tuple_ub() == schema().dof_tuple_ub(is_table_dof_map()));
  ensure(version() == schema().version(true));

  // Exit

  return;
}

sheaf::poset_dof_map::
poset_dof_map(const schema_poset_member* xschema, bool xis_table_dof_map)
{

  // Preconditions:

  require(xschema != 0);
  require(xschema->state_is_read_accessible());

  // Body:

  _host   = 0;

  _index.invalidate();
  _index.put_scope(xschema->host()->dof_tuple_hub_id_space(false));

  _schema = xschema->clone();
  _schema->attach_to_state(xschema);

  // Force the version to be unaliased.

  _schema->put_version(_schema->version(), true);

  _is_table_dof_map = xis_table_dof_map;

  _dof_ct       = _schema->dof_ct(_is_table_dof_map);
  _dof_tuple_ub = _schema->dof_tuple_ub(_is_table_dof_map);

  _ref_ct = 0;

  // Postconditions:

  ensure(is_initialized());
  ensure(host() == 0);
  ensure(!index().is_valid());
  ensure(index().same_scope(schema().host()->dof_tuple_hub_id_space(false)));
  ensure(schema().is_same_state(xschema));
  ensure(is_table_dof_map() == xis_table_dof_map);
  ensure(dof_ct() == schema().dof_ct(is_table_dof_map()));
  ensure(dof_tuple_ub() == schema().dof_tuple_ub(is_table_dof_map()));
  ensure(version() == schema().version(true));

  // Exit

  return;
}

void
sheaf::poset_dof_map::
put_host(const poset_state_handle* xhost)
{
  // Preconditions:

  require(is_initialized());
  require(xhost->state_is_read_accessible());
  require(xhost->schema().is_same_state(&(schema())));

  // Body:

  _host = const_cast<poset_state_handle*>(xhost);

  // Postconditions:

  ensure(host() == xhost);

  // Exit

  return;
}

void
sheaf::poset_dof_map::
put_index(const scoped_index& xindex)
{
  // Preconditions:

  require(xindex.is_positive() || !xindex.is_valid());

  // Body:

  _index = xindex;

  // Postconditions:

  ensure(index() == xindex);

  // Exit

  return;
}

void
sheaf::poset_dof_map::
put_dof_ct(int xdof_ct)
{
  // Preconditions:


  // Body:

  _dof_ct = xdof_ct;

  // Postconditions:

  ensure(dof_ct() == xdof_ct);

  // Exit:

  return;
}

void
sheaf::poset_dof_map::
put_dof_tuple_ub(size_t xub)
{
  // Preconditions:


  // Body:

  _dof_tuple_ub = xub;

  // Postconditions:

  ensure(dof_tuple_ub() == xub);

  // Exit:

  return;
}

void
sheaf::poset_dof_map::
put_ref_ct(int xref_ct)
{
  // Preconditions:

  require(xref_ct >= 0);

  // Body:

  _ref_ct = xref_ct;

  // Postconditions:

  ensure(ref_ct() == xref_ct);

  // Exit:

  return;
}

string
sheaf::poset_dof_map::
to_string(const schema_poset_member& xschema) const
{
  // Preconditions:

  // Body:

  string result;
  if(schema().contains_dof(xschema, _is_table_dof_map))
  {
    result = xschema.name() + "=" + dof(xschema.index()).to_string();
  }

  // Postconditions:

  // Exit:

  return result;
}

string
sheaf::poset_dof_map::
to_string() const
{
  // Preconditions:

  // Body:

  string result;

  poset_dof_iterator* ldof_itr = schema().dof_iterator(is_table_dof_map());

  if(!ldof_itr->is_done())
  {
    // Output first dof without leading white space.

    schema_poset_member& lschema = ldof_itr->item();

    result += to_string(lschema);

    ldof_itr->next();

    while(!ldof_itr->is_done())
    {
      // Output additional dofs preceded by white space.

      schema_poset_member& lschema = ldof_itr->item();

      result += "\t";
      result += to_string(lschema);

      ldof_itr->next();
    }
  }
  delete ldof_itr;

  // Postconditions:

  // Exit:

  return result;
}

// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================
SHEAF_DLL_SPEC
ostream& sheaf::
operator<<(ostream& os, const poset_dof_map& xmap )
{
  // Preconditions:

  // Body:

  poset_dof_map& lmap = const_cast<poset_dof_map&>(xmap);

  os << lmap.to_string();

  // Postconditions:

  // Exit:

  return os;
}

SHEAF_DLL_SPEC
size_t
sheaf::
deep_size(const poset_dof_map& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  if(xp.is_initialized())
  {
    poset_dof_map& lxp = const_cast<poset_dof_map&>(xp);

    // _schema is cloned, so calculate the contribution.

    result += deep_size(*xp._schema, true);

    // Add the size of all of the dofs.

    result += lxp.dof_tuple_ub();
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

