
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

//
// Implementation for class index_scope

#include "ComLimitPoint/sheaf/index_scope.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/scoped_index.h"

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

