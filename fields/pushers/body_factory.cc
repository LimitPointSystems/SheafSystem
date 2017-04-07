
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

/// @file
/// Implementation for class body_factory.

#include "body_factory.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "array_index_space_state.h"
#include "base_space_member.h"
#include "block.impl.h"
#include "body_builder.h"
#include "fiber_bundles_namespace.h"
#include "field_factory.h"
#include "std_cmath.h"
#include "std_iostream.h"
#include "std_sstream.h"
#include "field_vd.h"
#include "wsv_block.impl.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

// =============================================================================
// BODY_FACTORY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::field_vd*
fields::body_factory::
new_1d_unstructured_bodies(fiber_bundles_namespace& xns,
                           const std::string& xname_prefix)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xns.contains_poset(xname_prefix+"_1d_unstructured_base_space"));

  // Body:

  // Create a 1D unstructured mesh and a scalar field
  // that initially defines one circular body.

  wsv_block<sec_vd_value_type> llower("-1");
  wsv_block<sec_vd_value_type> lupper("1");

  field_vd* result =
    field_factory::new_scalar_field_1d_unstructured(xns,
        xname_prefix+"_1d_unstructured",
        10,
        llower,
        lupper,
        one_body);

  // Build the circular body and two square bodies and output results.

  build_bodies(*result);

  // Postconditions:

  ensure(xns.contains_poset_member(xname_prefix+"_1d_unstructured_base_space/circular_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_1d_unstructured_base_space/square_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_1d_unstructured_base_space/square_body1"));

  // Exit:

  return result;
}

fields::field_vd*
fields::body_factory::
new_1d_uniform_bodies(fiber_bundles_namespace& xns,
                      const std::string& xname_prefix)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xns.contains_poset(xname_prefix+"_1d_uniform_base_space"));

  // Body:

  // Create a 1D uniform mesh and a scalar field that
  // initially defines one circular body.

  wsv_block<sec_vd_value_type> llower("-1");
  wsv_block<sec_vd_value_type> lupper("1");

  field_vd* result =
    field_factory::new_scalar_field_1d_uniform(xns,
        xname_prefix+"_1d_uniform",
        10,
        llower,
        lupper,
        one_body);

  // Build the circular body and two square bodies and output results.

  build_bodies(*result);

  // Postconditions:

  ensure(xns.contains_poset_member(xname_prefix+"_1d_uniform_base_space/circular_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_1d_uniform_base_space/square_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_1d_uniform_base_space/square_body1"));

  // Exit:

  return result;
}


fields::field_vd*
fields::body_factory::
new_2d_unstructured_bodies(fiber_bundles_namespace& xns,
                           const std::string& xname_prefix)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xns.contains_poset(xname_prefix+"_2d_unstructured_base_space"));

  // Body:

  // Create a 2D unstructured mesh and a scalar field
  // that initially defines one circular body.

  wsv_block<sec_vd_value_type> llower("-1 -1");
  wsv_block<sec_vd_value_type> lupper("1 1");

  field_vd* result =
    field_factory::new_scalar_field_2d_unstructured(xns,
        xname_prefix+"_2d_unstructured",
        10,
        10,
        true,
        llower,
        lupper,
        one_body);

  // Build the circular body and two square bodies and output results.

  build_bodies(*result);

  // Postconditions:

  ensure(xns.contains_poset_member(xname_prefix+"_2d_unstructured_base_space/circular_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_2d_unstructured_base_space/square_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_2d_unstructured_base_space/square_body1"));

  // Exit:

  return result;
}

fields::field_vd*
fields::body_factory::
new_2d_uniform_bodies(fiber_bundles_namespace& xns,
                      const std::string& xname_prefix)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xns.contains_poset(xname_prefix+"_2d_uniform_base_space"));

  // Body:

  // Create a 2D uniform mesh and a scalar field that
  // initially defines one circular body.

  wsv_block<sec_vd_value_type> llower("-1 -1");
  wsv_block<sec_vd_value_type> lupper("1 1");

  field_vd* result =
    field_factory::new_scalar_field_2d_uniform(xns,
        xname_prefix+"_2d_uniform",
        10,
        10,
        llower,
        lupper,
        one_body);

  // Build the circular body and two square bodies and output results.

  build_bodies(*result);

  // Postconditions:

  ensure(xns.contains_poset_member(xname_prefix+"_2d_uniform_base_space/circular_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_2d_uniform_base_space/square_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_2d_uniform_base_space/square_body1"));

  // Exit:

  return result;
}

fields::field_vd*
fields::body_factory::
new_3d_unstructured_bodies(fiber_bundles_namespace& xns,
                           const std::string& xname_prefix)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xns.contains_poset(xname_prefix+"_3d_unstructured_base_space"));

  // Body:

  // Create a 3D unstructured mesh and a scalar field
  // that initially defines one circular body.

  wsv_block<sec_vd_value_type> llower("-1 -1 -1");
  wsv_block<sec_vd_value_type> lupper("1 1 1");

  field_vd* result =
    field_factory::new_scalar_field_3d_unstructured(xns,
        xname_prefix+"_3d_unstructured",
        10,
        10,
        10,
        true,
        llower,
        lupper,
        one_body);

  // Build the circular body and two square bodies and output results.

  build_bodies(*result);

  // Postconditions:

  ensure(xns.contains_poset_member(xname_prefix+"_3d_unstructured_base_space/circular_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_3d_unstructured_base_space/square_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_3d_unstructured_base_space/square_body1"));

  // Exit:

  return result;
}

fields::field_vd*
fields::body_factory::
new_3d_uniform_bodies(fiber_bundles_namespace& xns,
                      const std::string& xname_prefix)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xns.contains_poset(xname_prefix+"_3d_uniform_base_space"));

  // Body:

  // Create a 3D uniform mesh and a scalar field that
  // initially defines one circular body.

  wsv_block<sec_vd_value_type> llower("-1 -1 -1");
  wsv_block<sec_vd_value_type> lupper("1 1 1");

  field_vd* result =
    field_factory::new_scalar_field_3d_uniform(xns,
        xname_prefix+"_3d_uniform",
        10,
        10,
        10,
        llower,
        lupper,
        one_body);

  // Build the circular body and two square bodies and output results.

  build_bodies(*result);

  // Postconditions:

  ensure(xns.contains_poset_member(xname_prefix+"_3d_uniform_base_space/circular_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_3d_uniform_base_space/square_body0"));
  ensure(xns.contains_poset_member(xname_prefix+"_3d_uniform_base_space/square_body1"));

  // Exit:

  return result;
}


// PRIVATE MEMBER FUNCTIONS

void
fields::body_factory::
one_body(block<sec_vd_value_type>& xglobal_coords,
         block<sec_vd_dof_type>& xproperty_value)
{
  // Preconditions:

  require(xproperty_value.ct() == 1);

  // Body:

  sec_vd_value_type& lprop_val0 = xproperty_value[0];

  lprop_val0 = 0.0;
  for(int i= 0; i<xglobal_coords.ct(); ++i)
  {
    lprop_val0 += xglobal_coords[i]*xglobal_coords[i];
  }

  lprop_val0 = sqrt(lprop_val0);

  // Postconditions:
  
  ensure(xproperty_value[0] >= 0.0);

  // Exit:

  return;
};

void
fields::body_factory::
two_bodies(block<sec_vd_value_type>& xglobal_coords,
           block<sec_vd_dof_type>& xproperty_value)
{
  // Preconditions:

  require(xglobal_coords.ct() > 0);

  require(xproperty_value.ct() == 1);

  // Body:

  int ldc = xglobal_coords.ct();
  bool linside = (fabs(xglobal_coords[0]) >= .5);
  if(linside && (ldc > 1))
  {
    linside = (fabs(xglobal_coords[1]) <= 0.5);

    if(linside && (ldc > 2))
    {
      linside = (fabs(xglobal_coords[2]) <= 0.5);
    }
  }

  if(linside)
  {
    xproperty_value[0] = 1.0;
  }
  else
  {
    xproperty_value[0] = 0.0;
  }

  // Postconditions:

  // Exit:

  return;
}

void
fields::body_factory::
build_circular_body(field_vd& xfield)
{
#ifdef DIAGNOSTIC_OUTPUT
  cout << "entering body_factory::build_circular_body:" << endl;
#endif

  poset* lbase_space_host = xfield.base_space().host();
  lbase_space_host->get_read_write_access();
  xfield.get_read_access();

  subposet lbodies(lbase_space_host, "bodies");
  scattered_insertion_index_space_handle& lspace = lbodies.id_space();

  body_builder lbody_builder;
  block<scoped_index>& lcircular_bodies =
    *lbody_builder.build(xfield, -0.1, 0.5);

  for(int i=0; i<lcircular_bodies.ct(); ++i)
  {
    stringstream lstr;
    lstr << "circular_body" << i;

    scoped_index lbody_id = lcircular_bodies[i];

    lbase_space_host->put_member_name(lbody_id, lstr.str(), true, false);

    lbodies.insert_member(lbody_id);
    lspace.push_back(lbody_id);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << "circular bodies (should be exactly one):";
  for(int i=0; i<lcircular_bodies.ct(); ++i)
  {
    cout << "  " << lcircular_bodies[i];
  }
  cout << endl;
#endif

  // Clean up.

  lbodies.detach_from_state();
  xfield.release_access();
  lbase_space_host->release_access();

  delete &lcircular_bodies;

#ifdef DIAGNOSTIC_OUTPUT
  cout << "leaving body_factory::build_circular_body:" << endl;
#endif
  return;
};


void
fields::body_factory::
build_square_bodies(field_vd& xfield)
{
#ifdef DIAGNOSTIC_OUTPUT
  cout << "entering body_factory::build_square_bodies:" << endl;
#endif

  poset* lbase_space_host = xfield.base_space().host();
  lbase_space_host->get_read_write_access();
  xfield.get_read_access();

  subposet lbodies(lbase_space_host, "bodies");
  scattered_insertion_index_space_handle& lspace = lbodies.id_space();

  body_builder lbody_builder;
  block<scoped_index>& lsquare_bodies =
    *lbody_builder.build(xfield, 0.9, 1.1);

  for(int i=0; i<lsquare_bodies.ct(); ++i)
  {
    stringstream lstr;
    lstr << "square_body" << i;

    scoped_index lbody_id = lsquare_bodies[i];

    lbase_space_host->put_member_name(lbody_id, lstr.str(), true, false);

    lbodies.insert_member(lbody_id);
    lspace.push_back(lbody_id);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << endl << "square bodies (should be exactly two):";
  for(int i=0; i<lsquare_bodies.ct(); ++i)
  {
    cout << "  " << lsquare_bodies[i];
  }
  cout << endl;
#endif

  // Clean up.

  lbodies.detach_from_state();
  xfield.release_access();
  lbase_space_host->release_access();

  delete &lsquare_bodies;

#ifdef DIAGNOSTIC_OUTPUT
  cout << "leaving body_factory::build_square_bodies:" << endl;
#endif

  return;
};

void
fields::body_factory::
build_bodies(field_vd& xfield)
{
  // Create a bodies subposet with a sequence id map.

  poset* lbase_space_host = xfield.base_space().host();
  lbase_space_host->get_read_write_access(false);
  subposet lbodies(lbase_space_host, 0, false);
  lbodies.put_name("bodies", true, false);
  lbodies.new_id_space("array_index_space_state");

  // Build the circular body and insert in bodies subposet.

  build_circular_body(xfield);

  // Construct a scalar field that defines two square bodies.

  xfield.put_property_dofs(two_bodies, true);

  // Build the square bodies and insert in bodies subposet.

  build_square_bodies(xfield);

  // Clean up.

  lbodies.detach_from_state();
  lbase_space_host->release_access();

  // Exit.

  return;
};
