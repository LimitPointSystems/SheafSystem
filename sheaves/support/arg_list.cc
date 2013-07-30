
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Implementation for class arg_list

#include "arg_list.h"

#include "assert_contract.h"
#include "error_message.h"
#include "namespace_poset.h"
#include "poset_dof_iterator.h"
#include "poset_path.h"
#include "primitive_attributes.h"
#include "schema_poset_member.h"
#include "std_iostream.h"
#include "std_string.h"
#include "std_cstring.h"

#include "block.impl.h"

// #define DIAGNOSTIC_OUTPUT

///
sheaf::arg_list::
arg_list()
    : _args(8),
    _parse_state(GET_NAME)
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

///
sheaf::arg_list::
arg_list(const arg_list& xinput)
    : _args(xinput._args),
    _parse_state(xinput._parse_state)

{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(contains_args(xinput));

  // Exit:

  return;
}

sheaf::arg_list::
arg_list(const arg_type& xarg)
    : _args(8),
    _parse_state(GET_NAME)
{
  // Preconditions:

  // Body:

  // Construction with an empty arg is mainly to 
  // support initialization by compile-time constant
  // empty string "", so we can have default value ""
  // for arg_list args.

  if(!xarg.empty())
  {
    push_back(xarg);
  }

  // Postconditions:

  ensure(empty() == xarg.empty());
  ensure(!xarg.empty() ? back() == xarg : true);

  // Exit:

  return;
}

sheaf::arg_list::
arg_list(const char* xarg_name)
    : _args(8),
    _parse_state(GET_NAME)
{
  // Preconditions:

  // Body:

  // Construction with an empty arg is mainly to 
  // support initialization by compile-time constant
  // empty string "", so we can have default value ""
  // for arg_list args.

  arg_type larg(xarg_name);

  if(!larg.empty())
  {
    push_back(larg);
  }

  // Postconditions:

  ensure(empty() == (strlen(xarg_name) == 0));
  ensure(!empty() ? back().name == xarg_name : true);

  // Exit:

  return;
}

///
unsigned int
sheaf::arg_list::
ct() const
{
  return _args.ct();
}

bool
sheaf::arg_list::
empty() const
{
  // Preconditions:


  // Body:

  bool result = _args.ct() == 0;

  // Postconditions:

  ensure( result == (ct() == 0));
  
  // Exit:

  return result;
}


///
int
sheaf::arg_list::
index(const string& xname) const
{
  int result;

  // Preconditions:

  require(!xname.empty());

  // Body:

  result = -1;
  for(int i=0; i<_args.ct(); ++i)
  {
    if(_args[i].name == xname)
    {
      result = i;
      break;
    }
  }

  // Postconditions:

  ensure((-1 <= result) && (result < static_cast<int>(ct())));

  // Exit:

  return result;
}

///
const string&
sheaf::arg_list::
name(int xi) const
{

  // Preconditions:

  require(xi < ct());

  // Body:

  const string& result = _args[xi].name;

  // Postconditions:


  // Exit:

  return result;
}

///
int
sheaf::arg_list::
type(int xi) const
{

  // Preconditions:

  require(xi < ct());

  // Body:

  int result = _args[xi].type();

  // Postconditions:


  // Exit:

  return result;
}

///
int
sheaf::arg_list::
type(const string& xname) const
{

  // Preconditions:

  require(!xname.empty());
  require(contains_arg(xname));

  // Body:

  int result = arg(xname).type();

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::primitive_value&
sheaf::arg_list::
value(int xi)
{

  // Preconditions:

  require(xi < ct());

  // Body:

  primitive_value& result = _args[xi].value;

  // Postconditions:


  // Exit:

  return result;
}

///
const sheaf::primitive_value&
sheaf::arg_list::
value(int xi) const
{

  // Preconditions:

  require(xi < ct());

  // Body:

  const primitive_value& result = _args[xi].value;

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::primitive_value&
sheaf::arg_list::
value(const string& xname)
{

  // Preconditions:

  require(!xname.empty());
  require(contains_arg(xname));

  // Body:

  primitive_value& result = arg(xname).value;

  // Postconditions:


  // Exit:

  return result;
}

///
const sheaf::primitive_value&
sheaf::arg_list::
value(const string& xname) const
{

  // Preconditions:

  require(!xname.empty());
  require(contains_arg(xname));

  // Body:

  const primitive_value& result = arg(xname).value;

  // Postconditions:


  // Exit:

  return result;
}

// ///
// sheaf::arg_list&
// sheaf::arg_list::
// operator<<(const arg_list& xinput)
// {
//   // Preconditions:

//   // Body:

//   size_type linput_ct = xinput._args.ct();

//   for(size_type i=0; i<linput_ct; ++i)
//   {
//     _args.push_back(xinput._args[i]);
//   }

//   // Postcondition:

//   // Exit:

//   return *this;
// }

///
sheaf::arg_list&
sheaf::arg_list::
operator+=(const arg_list& xother)
{
  // Preconditions:

  // Body:

  size_type lother_ct = xother._args.ct();

  for(size_type i=0; i<lother_ct; ++i)
  {
    _args.push_back(xother._args[i]);
  }

  // Postcondition:

  ensure(contains_args(xother));

  // Exit:

  return *this;
}

///
sheaf::arg_list&
sheaf::arg_list::
operator<<(const primitive_value& xinput)
{
  // Preconditions:

  // Body:

  switch(_parse_state)
  {
  case GET_NAME:
    if(xinput.id() == C_STRING)
    {
      if(*xinput.value().c_string_primitive == '\0')
      {
        _parse_state = ERROR;
        post_fatal_error_message("Empty string given for argument name");
      }
      else
      {
        _args.push_back(arg_type(xinput.value().c_string_primitive));
        _parse_state = GET_VALUE;
      }
    }
    else
    {
      _parse_state = ERROR;
      post_fatal_error_message("Found argument value when expecting argument name");
    }

    break;

  case GET_VALUE:
    //    _args.back().type = xinput.id;
    _args.back().value = xinput;
    _parse_state = GET_NAME;
    break;

  default:
    _parse_state = ERROR;
    post_fatal_error_message("Unrecognized parse_state");
    break;
  }

  // Postcondition:

  // Exit:

  return *this;
}

 

///
bool
sheaf::arg_list::
parsing_name() const
{
  bool result;

  // Preconditions:


  // Body:

  result = (_parse_state == GET_NAME);

  // Postconditions:


  // Exit:

  return result;
}

 

///
bool
sheaf::arg_list::
parsing_value() const
{
  bool result;

  // Preconditions:


  // Body:

  result = (_parse_state == GET_VALUE);

  // Postconditions:


  // Exit:

  return result;
}

 

///
bool
sheaf::arg_list::
parsing_error() const
{
  bool result;

  // Preconditions:


  // Body:

  result = (_parse_state == ERROR);

  // Postconditions:


  // Exit:

  return result;
}

///
bool
sheaf::arg_list::
conforms_to(const namespace_poset& xns,
            const poset_path& xschema_path,
            bool xuse_table_schema,
            bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || xns.state_is_read_accessible());
  require(xschema_path.member_exists(xauto_access));
  require(xauto_access || xschema_path.state_is_read_accessible(xauto_access));

  // Body:

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  result = conforms_to(lschema, xuse_table_schema, xauto_access);

  lschema.detach_from_state();

  // Postconditions:

  // Exit:

  return result;
}

///
bool
sheaf::arg_list::
conforms_to(const schema_poset_member& xschema,
            bool xuse_table_schema,
            bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || xschema.state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xschema.get_read_access();
  }

  // Iterate over the dofs, checking type of each arg.
  // Loop will terminate when we've tested all the dofs defined by the schema
  // or if an argument is not the right type.

  poset_dof_iterator* ldof_itr = xschema.dof_iterator(xuse_table_schema);
  while(!ldof_itr->is_done())
  {
    if(!arg_conforms_to(ldof_itr->item()))
    {
      break;
    }

    ldof_itr->next();
  }

  // This conforms to xschema if the list contains all the arguments
  // and they were the right type.

  result = ldof_itr->is_done();

  // Make sure iterator item is detached

  ldof_itr->force_is_done();

  delete ldof_itr;

  if(xauto_access)
  {
    xschema.release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

///
bool
sheaf::arg_list::
conforms_to_extension(const namespace_poset& xns,
                      const poset_path& xschema_path,
                      const poset_path& xstd_schema_path,
                      bool xuse_table_schema,
                      bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || xns.state_is_read_accessible());
  require(xschema_path.member_exists(xauto_access));
  require(xauto_access || xschema_path.state_is_read_accessible(xauto_access));
  require(xstd_schema_path.member_exists(xauto_access));
  require(xschema_path.conforms_to(xstd_schema_path, xauto_access));

  // Body:

  schema_poset_member lschema(&xns, xschema_path, xauto_access);
  schema_poset_member lstd_schema(&xns, xstd_schema_path, xauto_access);

  result =
    conforms_to_extension(lschema, lstd_schema, xuse_table_schema, xauto_access);

  lschema.detach_from_state();
  lstd_schema.detach_from_state();

  // Postconditions:

  // Exit:

  return result;
}

///
bool
sheaf::arg_list::
conforms_to_extension(const schema_poset_member& xschema,
                      const schema_poset_member& xstd_schema,
                      bool xuse_table_schema,
                      bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || xschema.state_is_read_accessible());

  if(xauto_access)
  {
    // Get access to xschema.
    // The next precondition implies that
    // we don't need to also get access to xstd_schema.

    xschema.get_read_access();
  }

  require(xschema.conforms_to(xstd_schema));

  // Body:

  // First, iterate over the down set of xstd_schema, marking its members.
  // The ct() member function does this conveniently and efficiently.

  poset_dof_iterator* ldof_itr = xstd_schema.dof_iterator(xuse_table_schema);
  ldof_itr->ct();

  // Now change the anchor to xschema and reset without clearing the markers.
  // Iteration will not visit any of the members of the down set of xschema.

  ldof_itr->put_anchor(xschema.index());
  ldof_itr->reset(false);

  // Iterate over the extended dofs, checking type of each arg.
  // Loop will terminate when we've tested all the dofs or
  // if an argument is not the right type.

  while(!ldof_itr->is_done())
  {
    if(!arg_conforms_to(ldof_itr->item()))
    {
      break;
    }

    ldof_itr->next();
  }

  // This conforms to xschema if all the arguments were the right type.

  result = ldof_itr->is_done();

  // Make sure iterator item is detached

  ldof_itr->force_is_done();

  if(xauto_access)
  {
    xschema.release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}


///
void
sheaf::arg_list::
clear()
{
  // Preconditions:

  // Body:

  arg_type lempty("");
  _args.assign(lempty);

  _args.set_ct(0);
  _parse_state = GET_NAME;

  // Postconditions:

  ensure(ct() == 0);

  // Exit:

  return;
}

///
void
sheaf::arg_list::arg_type::
put_type(int xid)
{
  // Preconditions:


  // Body:

  value.id() = primitive_attributes::id(xid);

  // Postconditions:


  // Exit:

  return;
}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
ostream&
sheaf::
operator<<(ostream &os, const arg_list& p)
{
  // Preconditions:


  // Body:

  for(int i=0; i<p.ct(); ++i)
  {
    os << p._args[i] << endl;
  }

  // Empty arg name terminates arg list.

  os << '\t' << endl;

  // Postconditions:

  // Exit:

  return os;
}


///
istream&
sheaf::
operator>>(istream &is, arg_list& p)
{
  // Preconditions:


  // Body:

  arg_list::arg_type larg;
  while(is >> larg)
  {
    if(larg.name.empty())
    {
      break;
    }
    p._args.push_back(larg);
  }

  // Postconditions:

  // Exit:

  return is;
}

///
ostream&
sheaf::
operator<<(ostream &os, const arg_list::arg_type& p)
{
  // Preconditions:


  // Body:

  os << p.name << '\t'; // Name terminated by tab.
  os << p.value.id() << '\t'; // Type terminated by tab.
  os << p.value.to_string();

  // Postconditions:

  // Exit:

  return os;
}

///
istream&
sheaf::
operator>>(istream &is, arg_list::arg_type& p)
{
  // Preconditions:

  require(is);

  // Body:

  // Turn off automatic skipping of leading whitespace
  // so we can control skipping terminators.

  is >> noskipws;

  // Name is terminated by tab, which getline removes
  // from stream but does not return in name.
  // Empty name means end of arglist.

  getline(is, p.name, '\t');

  if(is && !p.name.empty())
  {
    // Type is terminated by tab, which extraction
    // operator leaves in stream, so we have to explicitly
    // remove it.

    char lterm;
    primitive_type ltype;
    is >> ltype >> lterm;

    if(is)
    {
      // Dof values terminated by newline;
      // getline consumes the terminator.

      string lstr;
      getline(is, lstr, '\n');

      if(is)
      {
        p.value.id() = ltype;
        bool success = p.value.from_string(lstr);

        if(!success)
        {
          post_fatal_error_message("Failed to parse arg_list.");
        }
      }
    }
  }

  // Postconditions:

  ensure(is_primitive_index(p.type()) || p.name.empty() || !is);

  // Exit:

  return is;
}

size_t
sheaf::
deep_size(const arg_list::arg_type& xtype, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}

// ===========================================================
// PRIVATE MEMBER FUNCTIONS
// ===========================================================

///
bool
sheaf::arg_list::
arg_conforms_to(const schema_poset_member& xschema) const
{
  bool result;

  // Preconditions:


  // Body:

  int lschema_type = xschema.type();

  int larg_id = index(xschema.name());
  result = ( (larg_id >= 0) && (lschema_type == type(larg_id)) );

#ifdef DIAGNOSTIC_OUTPUT

  cout << "  schema: " << xschema.name()
       << " " << xschema.type();
    //  << " " << primitive_type_from_index(xschema.type());

  if(larg_id >= 0)
  {

    cout << "  arg: " << name(larg_id)
	 << " " << type(larg_id);
      //    << " " << primitive_type_from_index(type(larg_id));
  }
  else
  {
    cout << "  arg: not present";
  }

  cout << "  conforms_to: " << boolalpha << result << noboolalpha << endl;
#endif

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::arg_list::arg_type&
sheaf::arg_list::
arg(int xi)
{

  // Preconditions:

  require((0 <= xi) && (xi < ct()));

  // Body:

  arg_type& result = _args[xi];

  // Postconditions:


  // Exit:

  return result;
}

///
const sheaf::arg_list::arg_type&
sheaf::arg_list::
arg(int xi) const
{

  // Preconditions:

  require((0 <= xi) && (xi < ct()));

  // Body:

  const arg_type& result = _args[xi];

  // Postconditions:


  // Exit:

  return result;
}

///
bool
sheaf::arg_list::
contains_arg(const string& xname) const
{
  // Preconditions:

  require(!xname.empty());

  // Body:

  // Postconditions:


  // Exit:

  return index(xname) >= 0;
}

bool
sheaf::arg_list::
contains_args(const arg_list& xother) const
{
  // Preconditions:

  // Body:

  bool result = true;

  size_type lother_ct = xother._args.ct();

  for(size_type i=0; ((i<lother_ct) && result); ++i)
  {
    const arg_type& larg = xother._args[i];
    const string& lname = larg.name;

    result = contains_arg(lname);

    if(result)
    {
      result = (arg(lname) == larg);
    }
  }

  // Postconditions:

  // Exit:

  return result;
}

///
sheaf::arg_list::arg_type&
sheaf::arg_list::
arg(const string& xname)
{

  // Preconditions:

  require(!xname.empty());
  require(contains_arg(xname));

  // Body:

  int i = index(xname);
  arg_type& result = arg(i);

  // Postconditions:


  // Exit:

  return result;
}

///
const sheaf::arg_list::arg_type&
sheaf::arg_list::
arg(const string& xname) const
{

  // Preconditions:

  require(!xname.empty());
  require(contains_arg(xname));

  // Body:

  int i = index(xname);
  const arg_type& result = arg(i);

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::arg_list::arg_type&
sheaf::arg_list::
back()
{

  // Preconditions:

  require(ct() > 0);

  // Body:

  arg_type& result = _args.back();

  // Postconditions:


  // Exit:

  return result;
}

///
const sheaf::arg_list::arg_type&
sheaf::arg_list::
back() const
{

  // Preconditions:

  require(ct() > 0);

  // Body:

  const arg_type& result = _args.back();

  // Postconditions:


  // Exit:

  return result;
}

///
void
sheaf::arg_list::
push_back(const arg_type& xarg)
{
  // Preconditions:

  require(parsing_name());

  // Body:

  define_old_variable(int old_ct = ct());

  _args.push_back(xarg);

  // Postconditions:

  ensure(ct() == old_ct + 1);

  // Exit:

  return;
}

