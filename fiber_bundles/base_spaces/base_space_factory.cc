
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

// Template specializations for class base_space_factory.

#include "SheafSystem/base_space_factory.impl.h"

//#include "SheafSystem/base_space_member_prototype.h"
#include "SheafSystem/hex_connectivity.h" 
#include "SheafSystem/line_connectivity.h" 
#include "SheafSystem/point_block_1d.h"
#include "SheafSystem/point_block_2d.h"
#include "SheafSystem/point_block_3d.h"
#include "SheafSystem/quad_connectivity.h" 
#include "SheafSystem/structured_block_1d.h"
#include "SheafSystem/structured_block_2d.h"
#include "SheafSystem/structured_block_3d.h"
#include "SheafSystem/tetra_connectivity.h" 
#include "SheafSystem/triangle_connectivity.h" 
#include "SheafSystem/unstructured_block.h"
#include "SheafSystem/zone_nodes_block.h"

using namespace std;

//==============================================================================
// SPECIALIZATION FOR STRUCTURED_BLOCK_1D
//==============================================================================
 
///
/// Finds or creates the base space specified by xbase_path;
/// specialization for structured_block_1d.
///
template <>
SHEAF_DLL_SPEC 
fiber_bundle::structured_block_1d*
fiber_bundle::base_space_factory<fiber_bundle::structured_block_1d>::
new_base(fiber_bundles_namespace& xns, const std::string& xbase_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(path.poset_name()));
  require(poset_path::is_valid_name(xbase_name));
  require(xns.contains_poset_member(poset_path(path.poset_name(), xbase_name)) ||
          index_ubs.ct() >= 1);

  // Body:

  structured_block_1d* result = new structured_block_1d();

  poset_path lbase_path(path.poset_name(), xbase_name);

  if(xns.contains_poset_member(lbase_path, true))
  {
    result->attach_to_state(&xns, lbase_path);
  }
  else
  {
    base_space_poset* lhost = new_space(xns);
    result->new_state(lhost, index_ubs[0], true);
    result->put_name(xbase_name, true, true);
  }

  // Postconditions:

  ensure(result->name(true) == xbase_name);

  // Exit:

  return result;
}


//==============================================================================
// SPECIALIZATION FOR STRUCTURED_BLOCK_2D
//==============================================================================
 

template <>
SHEAF_DLL_SPEC 
fiber_bundle::structured_block_2d*
fiber_bundle::base_space_factory<fiber_bundle::structured_block_2d>::
new_base(fiber_bundles_namespace& xns, const std::string& xbase_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(path.poset_name()));
  require(poset_path::is_valid_name(xbase_name));
  require(xns.contains_poset_member(poset_path(path.poset_name(), xbase_name)) ||
          index_ubs.ct() >= 2);

  // Body:

  structured_block_2d* result = new structured_block_2d();
  poset_path lbase_path(path.poset_name(), xbase_name);

  if(xns.contains_poset_member(lbase_path, true))
  {
    result->attach_to_state(&xns, lbase_path);
  }
  else
  {
    base_space_poset* lhost = new_space(xns);
    result->new_state(lhost, index_ubs[0], index_ubs[1], true);
    result->put_name(xbase_name, true, true);
  }

  // Postconditions:

  ensure(result->name(true) == xbase_name);

  // Exit:

  return result;
}


//==============================================================================
// SPECIALIZATION FOR STRUCTURED_BLOCK_3D
//==============================================================================
 

///
/// Finds or creates the base space specified by xbase_path;
/// specialization for structured_block_3d.
///
template <>
SHEAF_DLL_SPEC 
fiber_bundle::structured_block_3d*
fiber_bundle::base_space_factory<fiber_bundle::structured_block_3d>::
new_base(fiber_bundles_namespace& xns, const std::string& xbase_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(path.poset_name()));
  require(poset_path::is_valid_name(xbase_name));
  require(xns.contains_poset_member(poset_path(path.poset_name(), xbase_name)) ||
          index_ubs.ct() >= 3);

  // Body:

  structured_block_3d* result = new structured_block_3d();

  poset_path lbase_path(path.poset_name(), xbase_name);
  if(xns.contains_poset_member(lbase_path, true))
  {
    result->attach_to_state(&xns, lbase_path);
  }
  else
  {
    base_space_poset* lhost = new_space(xns);
    result->new_state(lhost,
                      index_ubs[0],
                      index_ubs[1],
                      index_ubs[2],
                      true);
    result->put_name(xbase_name, true, true);
  }

  // Postconditions:

  ensure(result->name(true) == xbase_name);

  // Exit:

  return result;
}


//==============================================================================
// SPECIALIZATION FOR POINT_BLOCK_1D
//==============================================================================
 

template <>
SHEAF_DLL_SPEC 
fiber_bundle::point_block_1d*
fiber_bundle::base_space_factory<fiber_bundle::point_block_1d>::
new_base(fiber_bundles_namespace& xns, const std::string& xbase_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(path.poset_name()));
  require(poset_path::is_valid_name(xbase_name));
  require(xns.contains_poset_member(poset_path(path.poset_name(), xbase_name)) || index_ubs.ct() >= 1);

  // Body:

  point_block_1d* result = new point_block_1d();
  poset_path lbase_path(path.poset_name(), xbase_name);

  if(xns.contains_poset_member(lbase_path, true))
  {
    result->attach_to_state(&xns, lbase_path);
  }
  else
  {
    base_space_poset* lhost = new_space(xns);
    result->new_state(lhost, index_ubs[0], true);
    result->put_name(xbase_name, true, true);
  }

  // Postconditions:

  ensure(result->name(true) == xbase_name);

  // Exit:

  return result;
}


//==============================================================================
// SPECIALIZATION FOR POINT_BLOCK_2D
//==============================================================================
 

template <>
SHEAF_DLL_SPEC 
fiber_bundle::point_block_2d*
fiber_bundle::base_space_factory<fiber_bundle::point_block_2d>::
new_base(fiber_bundles_namespace& xns, const std::string& xbase_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(path.poset_name()));
  require(poset_path::is_valid_name(xbase_name));
  require(xns.contains_poset_member(poset_path(path.poset_name(), xbase_name)) || index_ubs.ct() >= 2);

  // Body:

  point_block_2d* result = new point_block_2d();
  poset_path lbase_path(path.poset_name(), xbase_name);

  if(xns.contains_poset_member(lbase_path, true))
  {
    result->attach_to_state(&xns, lbase_path);
  }
  else
  {
    base_space_poset* lhost = new_space(xns);
    result->new_state(lhost, index_ubs[0], index_ubs[1], true);
    result->put_name(xbase_name, true, true);
  }

  // Postconditions:

  ensure(result->name(true) == xbase_name);

  // Exit:

  return result;
}


//==============================================================================
// SPECIALIZATION FOR POINT_BLOCK_3D
//==============================================================================
 

template <>
SHEAF_DLL_SPEC 
fiber_bundle::point_block_3d*
fiber_bundle::base_space_factory<fiber_bundle::point_block_3d>::
new_base(fiber_bundles_namespace& xns, const std::string& xbase_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(path.poset_name()));
  require(poset_path::is_valid_name(xbase_name));
  require(xns.contains_poset_member(poset_path(path.poset_name(), xbase_name)) || index_ubs.ct() >= 3);

  // Body:

  point_block_3d* result = new point_block_3d();
  poset_path lbase_path(path.poset_name(), xbase_name);

  if(xns.contains_poset_member(lbase_path, true))
  {
    result->attach_to_state(&xns, lbase_path);
  }
  else
  {
    base_space_poset* lhost = new_space(xns);
    result->new_state(lhost,
                      index_ubs[0],
                      index_ubs[1],
                      index_ubs[2],
                      true);
    result->put_name(xbase_name, true, true);
  }

  // Postconditions:

  ensure(result->name(true) == xbase_name);

  // Exit:

  return result;
}


//==============================================================================
// SPECIALIZATION FOR ZONE_NODES_BLOCK
//==============================================================================


template <>
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset*
fiber_bundle::base_space_factory<fiber_bundle::zone_nodes_block>::
new_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_accessible());
  require(!path.empty());
  require(poset_path::is_valid_name(path.poset_name()));
  require(xns.contains_poset(path.poset_name()) ||
          ((1 <= index_ubs.ct()) && (index_ubs.ct() <= 3)));

  // Body:

  base_space_poset* result;

  int ldb = index_ubs.ct();

  if(xns.contains_poset(path, true))
  {
    result = dynamic_cast<base_space_poset*>(&xns.member_poset(path, false));
  }
  else
  {
    result = &zone_nodes_block::standard_host(xns, path.poset_name(), ldb, false);
  }

  // Get

  // Postconditions:

  ensure(xns.contains_poset(path, true));

  // Exit:

  return result;
}

template <>
SHEAF_DLL_SPEC 
fiber_bundle::zone_nodes_block*
fiber_bundle::base_space_factory<fiber_bundle::zone_nodes_block>::
new_base(fiber_bundles_namespace& xns, const std::string& xbase_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(path.poset_name()));
  require(poset_path::is_valid_name(xbase_name));
  require(xns.contains_poset_member(poset_path(path.poset_name(), xbase_name)) ||
          ((1 <= index_ubs.ct()) && (index_ubs.ct() <= 3)));

  // Body:

  zone_nodes_block* result = new zone_nodes_block();
  poset_path lbase_path(path.poset_name(), xbase_name);

  poset_path llocal_cell_prototype_path(local_cell_prototype_path);

  if(xns.contains_poset_member(lbase_path))
  {
    result->attach_to_state(&xns, lbase_path);
  }
  else
  {

    base_space_poset* lhost = new_space(xns);

    int ldb = index_ubs.ct();
    switch(ldb)
    {
      case 1:
	{  // scope suppresses compiler warnings
	  line_connectivity lconn(index_ubs[0]);
	  result->new_state(*lhost, lconn, true);
	}	
      break;
    case 2:
      if(llocal_cell_prototype_path.member_name() == "triangles_nodes")
      {
	triangle_connectivity lconn(index_ubs[0], index_ubs[1]);
	result->new_state(*lhost, lconn, true);
      }
      else
      {
	quad_connectivity lconn(index_ubs[0], index_ubs[1]);
	result->new_state(*lhost, lconn, true);
      }
      break;
    case 3:
      if(llocal_cell_prototype_path.member_name() == "tetra_nodes")
      {
	tetra_connectivity lconn(index_ubs[0], index_ubs[1], index_ubs[2]);
	result->new_state(*lhost, lconn, true);
      }
      else
      {
	hex_connectivity lconn(index_ubs[0], index_ubs[1], index_ubs[2]);
	result->new_state(*lhost, lconn, true);
      }
      break;
    default:
      post_fatal_error_message("Unsupported base dimension");
      break;
    }

    result->put_name(xbase_name, true, true);
  }

  // Postconditions:

  ensure(result->name(true) == xbase_name);

  // Exit:

  return result;
}


//================================================================================================
// SPECIALIZATION FOR UNSTRUCTURED_BLOCK
//================================================================================================


template <>
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset*
fiber_bundle::base_space_factory<fiber_bundle::unstructured_block>::
new_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_accessible());
  require(!path.empty());
  require(poset_path::is_valid_name(path.poset_name()));

  // Body:

  base_space_poset* result;

  int ldb = index_ubs.ct();


  if(xns.contains_poset(path, true))
  {
    result = dynamic_cast<base_space_poset*>(&xns.member_poset(path, false));
  }
  else
  {
    zone_nodes_block::standard_host(xns, path.poset_name(), ldb, false);
    result = &xns.member_poset<base_space_poset>(path.poset_name());
  }

  // Get

  // Postconditions:

  ensure(xns.contains_poset(path, true));

  // Exit:

  return result;
}

template <>
SHEAF_DLL_SPEC 
fiber_bundle::unstructured_block*
fiber_bundle::base_space_factory<fiber_bundle::unstructured_block>::
new_base(fiber_bundles_namespace& xns, const std::string& xbase_name)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(path.poset_name()));
  require(poset_path::is_valid_name(xbase_name));
  require(xns.contains_poset_member(poset_path(path.poset_name(), xbase_name)) ||
          ((1 <= index_ubs.ct()) && (index_ubs.ct() <= 3)));

  // Body:

  unstructured_block* result = new unstructured_block();
  poset_path lbase_path(path.poset_name(), xbase_name);

  poset_path llocal_cell_prototype_path(local_cell_prototype_path);

  if(xns.contains_poset_member(lbase_path))
  {
    result->attach_to_state(&xns, lbase_path);
  }
  else
  {

    base_space_poset* lhost = new_space(xns);

    string lposet_name(base_space_member::prototypes_poset_name());

    int ldb = index_ubs.ct();
    switch(ldb)
    {
    case 1:
      if(llocal_cell_prototype_path.empty())
      {
        llocal_cell_prototype_path.put_poset_name(lposet_name);
        llocal_cell_prototype_path.put_member_name("segment_complex");
      }

      result->new_state(lhost,
                        llocal_cell_prototype_path,
                        index_ubs[0],
                        true);
      break;
    case 2:
      if(llocal_cell_prototype_path.empty())
      {
        llocal_cell_prototype_path.put_poset_name(lposet_name);
        llocal_cell_prototype_path.put_member_name("quad_nodes");
      }
      result->new_state(lhost,
                        llocal_cell_prototype_path,
                        index_ubs[0],
                        index_ubs[1],
                        true);
      break;
    case 3:
      if(llocal_cell_prototype_path.empty())
      {
        llocal_cell_prototype_path.put_poset_name(lposet_name);
        llocal_cell_prototype_path.put_member_name("hex_nodes");
      }
      result->new_state(lhost,
                        llocal_cell_prototype_path,
                        index_ubs[0],
                        index_ubs[1],
                        index_ubs[2],
                        true);
      break;
    default:
      post_fatal_error_message("Unsupported base dimension");
      break;
    }

    result->put_name(xbase_name, true, true);
  }

  // Postconditions:

  ensure(result->name(true) == xbase_name);

  // Exit:

  return result;
}


