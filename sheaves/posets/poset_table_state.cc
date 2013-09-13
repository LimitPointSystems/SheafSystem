
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

/// @file
/// Implementation for class poset_table_state


#include "poset_table_state.h"

#include "array_poset_dof_map.h"
#include "assert_contract.h"
#include "factory_2.h"
#include "index_space_iterator.h"
#include "poset_dof_iterator.h"
#include "poset_state_handle.h"
#include "schema_poset_member.h"
#include "primitive_value.h"

// ===========================================================
// POSET_TABLE_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// sheaf::poset_table_state::
// poset_table_state(const schema_poset_member& xschema, size_type xcapacity)
// {
//   // Preconditions:

//   require(xschema->is_attached());

//   // Body:

//   // Prevent recursive calls to invariant.

//   disable_invariant_check();

//   // Initalize the upper bound of the row dofs.

//   _row_dof_tuple_index_ub.put(hub_id_space(), 0);

//   // Client may have provided a specialized schema member; clone it.

//   _schema = lschema->clone();

//   // Attach to the schema proved by the client.

//   _schema->attach_to_state(xschema);

//   // Can't create the dof map until we're sure we have a schema.

//   _table_dofs = 0;

//   _row_dof_tuples.reserve(xcapacity);

//   _standard_row_dof_tuple_ct = 0;

//   // Postconditions:

//   ensure( (xschema != 0) == schema().is_attached() );
//   ensure(row_dof_tuple_index_ub().is_hub_scope());
// }

sheaf::poset_table_state::
poset_table_state(const abstract_poset_member* xschema, size_type xcapacity)
{
  // Preconditions:

  require(xschema != 0 ? xschema->is_attached() : true);

  // Body:

  // Prevent recursive calls to invariant.

  disable_invariant_check();

  // Initalize the upper bound of the row dofs.

  _row_dof_tuple_index_ub.put(hub_id_space(), 0);

  // Create the schema

  if(xschema != 0)
  {
    // Client has provided a valid schema

    const schema_poset_member* lschema = dynamic_cast<const schema_poset_member*>(xschema);
    if(lschema != 0)
    {
      // Client may have provided a specialized schema member;
      // clone it.
      _schema = lschema->clone();
    }
    else
    {
      // Client has provided an ordinary member;
      // make a new schema member.

      _schema = new schema_poset_member;
    }

    // Attach to the schema proved by the client.

    _schema->attach_to_state(xschema);
  }
  else
  {
    // Client doesn't have a valid schema yet;
    // just create an unattached schema member.

    _schema = new schema_poset_member;
  }

  // Can't create the dof map until we're sure we have a schema.

  _table_dofs = 0;

  _row_dof_tuples.reserve(xcapacity);

  _standard_row_dof_tuple_ct = 0;

  // Postconditions:

  ensure( (xschema != 0) == schema().is_attached() );
  ensure(row_dof_tuple_index_ub().is_hub_scope());
}

sheaf::poset_table_state::
~poset_table_state()
{
  // Preconditions:

  require(_schema != 0);

  // Body:

  // Deallocate schema

  _schema->detach_from_state();
  delete _schema;

  // Deallocate poset dof map, if any.

  if(_table_dofs != 0)
  {
    _table_dofs->dec_ref_ct();
    if(_table_dofs->ref_ct() == 0)
    {
      delete _table_dofs;
    }
  }

  // Delete row dof tuples.

  for(int i=0; i<_row_dof_tuple_index_ub.pod(); i++)
  {
    poset_dof_map* lmap = _row_dof_tuples[i];
    lmap->dec_ref_ct();
    if(lmap->ref_ct() == 0)
    {
      delete lmap;
    }
  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::schema_poset_member&
sheaf::poset_table_state::
schema()
{
  // Preconditions:

  // Body:

  schema_poset_member& result = *_schema;

  // Postconditions:

  // Exit

  return result;
}

const sheaf::schema_poset_member&
sheaf::poset_table_state::
schema() const
{
  // Preconditions:

  // Body:

  const schema_poset_member& result = *_schema;

  // Postconditions:

  // Exit

  return result;
}

sheaf::array_poset_dof_map*
sheaf::poset_table_state::
table_dofs()
{
  // Preconditions:

  // Body:

  array_poset_dof_map* result = _table_dofs;

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::poset_table_state::
put_table_dofs(array_poset_dof_map* xtable_dofs)
{
  // Preconditions:

  // Body:

  _table_dofs = xtable_dofs;

  // Postconditions:

  // Exit

  return;
}

bool
sheaf::poset_table_state::
contains_row_dof_tuple(pod_index_type xindex) const
{
  // Preconditions:

  // Body:

  bool result = hub_id_space().contains(xindex);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_table_state::
contains_row_dof_tuple(const scoped_index& xindex) const
{
  return contains_row_dof_tuple(xindex.hub_pod());
}

sheaf::size_type
sheaf::poset_table_state::
row_dof_tuple_ct() const
{
  size_type result;

  // Preconditions:

  // Body:

  result = hub_id_space().ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}


const sheaf::scoped_index&
sheaf::poset_table_state::
row_dof_tuple_index_ub() const
{
  // Preconditions:

  // Body:

  const scoped_index& result = _row_dof_tuple_index_ub;

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
sheaf::poset_table_state::
standard_row_dof_tuple_ct() const
{
  size_type result;

  // Preconditions:

  // Body:

  result = _standard_row_dof_tuple_ct;

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::poset_table_state::
put_standard_row_dof_tuple_ct(size_type xct)
{
  // Preconditions:

  // Body:

  _standard_row_dof_tuple_ct = xct;

  // Postconditions:

  // Exit

  return;
}

sheaf::poset_dof_map*
sheaf::poset_table_state::
row_dof_tuple(pod_index_type xindex)
{
  poset_dof_map* result;

  // Preconditions:

  // Body:

  if(contains_row_dof_tuple(xindex))
  {
    result = _row_dof_tuples[xindex];
  }
  else
  {
    result = 0;
  }

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_dof_map*
sheaf::poset_table_state::
row_dof_tuple(const scoped_index& xindex)
{
  return row_dof_tuple(xindex.hub_pod());
}

void
sheaf::poset_table_state::
put_row_dof_tuple(poset_dof_map* xdof_tuple)
{
  // Preconditions:

  // Body:

  define_old_variable(scoped_index old_row_dof_tuple_index_ub = row_dof_tuple_index_ub());
  define_old_variable(size_type old_row_dof_tuple_ct = row_dof_tuple_ct());
  define_old_variable(int old_ref_ct = xdof_tuple->ref_ct());

  // Create a new member in the id space.

  pod_index_type lindex = _id_spaces.new_id();

  // Set the references from the map back to the poset.
  /// @hack should set xdof_tuple->host() as well, but can't in this context.

  xdof_tuple->put_index(hub_id(lindex));

  // Put the map in the table.

  _row_dof_tuples.force_item(lindex, xdof_tuple);

  // Set the row_dof_tuple upper bound.

  _row_dof_tuple_index_ub = hub_id_space().end();

  // Count the references to the dof map.
  // This reference count is probably unnecessary,
  // since there is only one direct reference,
  // from the table to the map. Furthermore, there is
  // currently no way to reclaim space in the table,
  // so we just don't delete dof maps until we delete the table.

  xdof_tuple->inc_ref_ct();

  // Postconditions:

  ensure(row_dof_tuple_ct() == old_row_dof_tuple_ct+1);
  ensure(row_dof_tuple_index_ub() >= old_row_dof_tuple_index_ub);
  ensure(contains_row_dof_tuple(xdof_tuple->index()));
  ensure(row_dof_tuple(xdof_tuple->index()) == xdof_tuple);
  ensure(xdof_tuple->ref_ct() == old_ref_ct + 1);

  // Exit

  return;
}

sheaf::index_space_iterator&
sheaf::poset_table_state::
get_row_dof_tuple_id_space_iterator() const
{
  // Preconditions:

  // Body:

  index_space_iterator& result =  hub_id_space().get_iterator();

  // Postconditions:

  ensure(hub_id_space().allocated_iterator(result));

  // Exit:

  return result;
}

void
sheaf::poset_table_state::
release_row_dof_tuple_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(hub_id_space().allocated_iterator(xitr));

  // Body:

  hub_id_space().release_iterator(xitr);

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ID SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::poset_table_state::
id_spaces() const
{
  return _id_spaces;
}

const sheaf::hub_index_space_handle&
sheaf::poset_table_state::
hub_id_space() const
{
  return _id_spaces.hub_id_space();
}

const sheaf::scoped_index&
sheaf::poset_table_state::
hub_id() const
{
  // Preconditions:

  // Body:

  const scoped_index& result = row_dof_tuple_index_ub();

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_table_state::
hub_id(pod_index_type xid) const
{
  // Preconditions:

  // Body:

  scoped_index result(hub_id());
  result = xid;

  // Postconditions:

  ensure(result.is_hub_scope());
  ensure(result.pod() == xid);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::poset_table_state::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const poset_table_state*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_table_state*
sheaf::poset_table_state::
clone() const
{
  poset_table_state* result = 0;

  // Preconditions:

  // Body:

  not_implemented();
  /// @todo implement poset_table_state::clone

  //result = new poset_table_state;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::poset_table_state::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    disable_invariant_check();

    result = result && _schema->is_attached();

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NONMEBER FUNCTIONS
// ===========================================================

namespace
{

///
/// Prints schema for poset_state_handle stream insertion operator.
///
void print_schema(ostream &os, const sheaf::poset_table_state& p)
{
  // Preconditions:

  // Body:

  os << "Schema" << endl
     << "------" << endl
     << endl;

  p.schema().to_stream(os);

  // Postconditions:

  // Exit:

  return;
}

///
/// Prints table dofs for poset_state_handle stream insertion operator.
///
void print_table_dofs(ostream &os, const sheaf::poset_table_state& p)
{
  // Preconditions:

  // Body:

  os << endl
     << "Table Attributes" << endl
     << "----------------" << endl
     << endl;

  // Print dof count and tuple size.

  size_t ldof_ct = p.schema().table_dof_ct();

  os << "table dof count: " << ldof_ct
     << " table dof tuple size: " << p.schema().table_dof_tuple_ub()
     << endl;

  const int NAME_WIDTH = 40;
  const int VALUE_WIDTH = 40;

  if (ldof_ct > 0)
  {
    // Print out the table dofs

    os << "table dofs:" << endl
       << setw(NAME_WIDTH) << "name"
       << setw(VALUE_WIDTH) << "value"
       << endl;

    for(int i=0; i<NAME_WIDTH; ++i)
    {
      os << "-";
    }
    os << ' ';
    for(int i=0; i<VALUE_WIDTH; ++i)
    {
      os << "-";
    }
    os << endl;

    sheaf::poset_dof_iterator*  table_dof_itr = p.schema().table_dof_iterator();
    while(!table_dof_itr->is_done())
    {
      os << setw(NAME_WIDTH) << table_dof_itr->item().name().c_str();

      os << " " << setw(VALUE_WIDTH)
	 << const_cast<sheaf::poset_table_state&>(p).table_dofs()->dof(table_dof_itr->index()).to_string()
	 << endl;

      table_dof_itr->next();
    }
    delete table_dof_itr;
  }

  // Postconditions:

  // Exit:

  return;
}

///
/// Prints row dofs for poset_state_handle stream insertion operator.
///
void print_row_dofs(ostream &os, const sheaf::poset_table_state& p)
{
  // Preconditions:


  // Body:

  os << endl
     << "Row Attributes" << endl
     << "--------------" << endl
     << endl;

  // The rows may be allocated on more than one
  // version of the schema. So get a handle to the
  // coarsest common refinement of the schema.

  sheaf::schema_poset_member* lccr_schema = p.schema().clone();
  lccr_schema->attach_to_state(&(p.schema()));
  lccr_schema->put_version(sheaf::COARSEST_COMMON_REFINEMENT_VERSION);

  size_t ldof_ct = lccr_schema->row_dof_ct();

  // Print dof count and tuple size.

  os << "row dof count: " << ldof_ct
     << " row dof tuple size: " << lccr_schema->row_dof_tuple_ub()
     << endl
     << endl;

  // Print out headings for dof tuples

  const int INDEX_WIDTH = 6;
  const int TYPE_WIDTH = 6;
  const int OTHER_WIDTH = 10;
  const int C_STRING_WIDTH = 48;

  os << setw(INDEX_WIDTH) << " index" << setw(TYPE_WIDTH) << "  type";

  int ldof_id = 0;
  sheaf::poset_dof_iterator* hdr_itr = lccr_schema->row_dof_iterator();
  while(!hdr_itr->is_done())
  {
    int ltype = hdr_itr->item().type();
    int lwidth = (ltype == sheaf::C_STRING) ? C_STRING_WIDTH - 2 : OTHER_WIDTH - 2;
    os << setw(lwidth) << "    dof " << setw(3) << ldof_id++;
    hdr_itr->next();
  }
  os << endl;
  delete hdr_itr;

  os << setw(INDEX_WIDTH) << "     " << setw(TYPE_WIDTH) << "    ";

  sheaf::poset_dof_iterator* name_itr = lccr_schema->row_dof_iterator();
  while(!name_itr->is_done())
  {
    int ltype = name_itr->item().type();
    int lwidth = (ltype == sheaf::C_STRING) ? C_STRING_WIDTH : OTHER_WIDTH;

    os << " " << setw(lwidth) << name_itr->item().name().substr(0, lwidth);
    name_itr->next();
  }
  os << endl;
  delete name_itr;


  // Print out under lines

  os << setw(INDEX_WIDTH) << " -----";
  os << setw(TYPE_WIDTH) << " -----";
  sheaf::poset_dof_iterator* undr_itr = lccr_schema->row_dof_iterator();
  while(!undr_itr->is_done())
  {
    os << ' ';
    int ltype = undr_itr->item().type();
    int lwidth = (ltype == sheaf::C_STRING) ? C_STRING_WIDTH : OTHER_WIDTH;
    for(int i=0; i<lwidth; ++i)
    {
      os << '-';
    }
    undr_itr->next();
  }
  os << endl;
  delete undr_itr;


  // Print out the rows:

  sheaf::poset_dof_iterator* dof_itr = lccr_schema->row_dof_iterator();

  sheaf::index_space_iterator& tuple_itr = p.get_row_dof_tuple_id_space_iterator();
  while(!tuple_itr.is_done())
  {
    // Print out the index and type for every dof tuple.

    sheaf::pod_index_type lid = tuple_itr.pod();

    os << setw(INDEX_WIDTH) << lid;
    os << setw(TYPE_WIDTH) << "      ";

    // Print out the dofs

    dof_itr->reset();
    while(!dof_itr->is_done())
    {
      // The dof map of this row is allocated on some version of the schema.
      // Print out the current dof only if it is contained in the version
      // used by this row; other wise, just print white space.

      const sheaf::scoped_index& lindex = dof_itr->index();

      sheaf::poset_dof_map* ltuple =
	const_cast<sheaf::poset_table_state&>(p).row_dof_tuple(p.hub_id(lid));
      int lver = ltuple->version();
      sheaf::schema_poset_member& lp_schema = ltuple->schema();

      if(lp_schema.host()->contains_member(lindex, lver) && lp_schema.ge(lindex))
      {
        // Current dof is contained in schema and version used by this row;
        // print it out

	sheaf::primitive_value lprim = ltuple->dof(lindex);

        int lwidth;
        string ldof_string;
        if(lprim.id() == sheaf::VOID_STAR)
        {
          // This is a pointer, don't want to print out the actual address
          // because it make files hard to compare.

          ldof_string = (lprim.value().void_star_primitive == 0) ? "<null>" : "<non-null>";
          lwidth = OTHER_WIDTH;
        }
        else
        {
          ldof_string = lprim.to_string();
          lwidth = (lprim.id() == sheaf::C_STRING) ? C_STRING_WIDTH : OTHER_WIDTH;
        }

        os << " " << setw(lwidth) << ldof_string;
      }
      else
      {
        // Current dof is not contained in schema and version used by this row;
        // print white space.

        int ltype = dof_itr->item().type();
        int lwidth = (ltype == sheaf::C_STRING) ? C_STRING_WIDTH : OTHER_WIDTH;
        os << ' ';
        for(int i=0; i<lwidth; ++i)
        {
          os << ' ';
        }
      }

      dof_itr->next();
    }

    tuple_itr.next();

    os << endl;
  }

  p.release_row_dof_tuple_id_space_iterator(tuple_itr);
  delete dof_itr;
  lccr_schema->detach_from_state();
  delete lccr_schema;

  // Postconditions:

  // Exit:

  return;
}

}

// ===========================================================
// NON-MEBER FUNCTIONS
// ===========================================================

ostream&
sheaf::
operator<<(ostream &os, const poset_table_state& p)
{

  // Preconditions:

  // Body:

  os << endl
  << "TABLE" << endl
  << "-----" << endl
  << endl;

  print_schema(os, p);
  print_table_dofs(os, p);
  print_row_dofs(os, p);

  // Tuple id space family.

  os << endl
     << "Tuple Id Space Family" << endl
     << "----------------------" << endl
     << endl;

  os << p.id_spaces() << endl;


  // Postconditions:

  // Exit

  return os;
}

size_t
sheaf::
deep_size(const poset_table_state& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add contributes from _id_spaces.

  result += deep_size(xp._id_spaces, false);

  // Calculate the deep size of data member: schema_poset_member* _schema.

  result += deep_size(*xp._schema, true);

  // Calculate the deep size of data member: _table_dofs

  result += deep_size(*xp._table_dofs, true);

  // Get size of memory allocated for row dof tuples.

  // The memory allocated for the various specializations of
  // class poset_dof_map is available thru the base class methods,
  // so here we can treat them all as if they were of the base
  // class type.

  result += deep_size(xp._row_dof_tuples, false);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
