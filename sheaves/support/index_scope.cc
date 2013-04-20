//

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

 

//
// Implementation for class index_scope

#include "index_scope.h"

#include "assert_contract.h"
#include "scoped_index.h"

// ===========================================================
// INDEX_SCOPE FACET
// ===========================================================

///
sheaf::index_scope::
index_scope(const immutable_id_map* xmap)
{

  // Preconditions:


  // Body:

  define_old_variable(const immutable_id_map*
                      old_scoped_index_default_map = scoped_index::default_map());

  _old_scope = scoped_index::default_map();
  scoped_index::private_default_map() = xmap;

  // Postconditions:

  ensure(scope() == xmap);
  ensure(old_scope() == old_scoped_index_default_map);

  // Exit:

  return;
}


///
sheaf::index_scope::
~index_scope()
{
  // Preconditions:


  // Body:

  scoped_index::private_default_map() = _old_scope;

  // Postconditions:

  ensure(scope() == old_scope());

  // Exit:

  return;
}

 

///
const sheaf::immutable_id_map*
sheaf::index_scope::
scope() const
{
  // Preconditions:


  // Body:

  const immutable_id_map* result = scoped_index::default_map();

  // Postconditions:

  ensure(result == scoped_index::default_map());

  // Exit:

  return result;
}


///
void
sheaf::index_scope::
put_scope(const immutable_id_map* xmap)
{
  // Preconditions:


  // Body:

  define_old_variable(const immutable_id_map* old_old_scope = _old_scope);

  scoped_index::private_default_map() = xmap;

  // Postconditions:

  ensure(scope() == xmap);
  ensure(old_scope() == old_old_scope);

  // Exit:

  return;
}

 

///
const sheaf::immutable_id_map*
sheaf::index_scope::
old_scope() const
{
  return _old_scope;
}



// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

