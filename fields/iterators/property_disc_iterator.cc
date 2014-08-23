
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
/// Implementation for class property_disc_iterator


#include "ComLimitPoint/fields/property_disc_iterator.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_member.h"
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_member.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/eval_family.h"
#include "ComLimitPoint/fields/property_disc_iterator_1_1.h"
#include "ComLimitPoint/fields/property_disc_iterator_1_2.h"
#include "ComLimitPoint/fields/property_disc_iterator_1_3.h"
#include "ComLimitPoint/fields/property_disc_iterator_4_2.h"
#include "ComLimitPoint/fields/property_disc_iterator_4_3.h"
#include "ComLimitPoint/fiber_bundle/sec_rep_descriptor.h"
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_member.h"
#include "ComLimitPoint/geometry/sec_ed_invertible.h"
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#include "std_limits.h"
#include "ComLimitPoint/fiber_bundle/structured_block_1d.h"
#include "ComLimitPoint/fiber_bundle/structured_block_2d.h"
#include "ComLimitPoint/fiber_bundle/structured_block_3d.h"
#include "ComLimitPoint/sheaf/subposet_member_iterator.h"
#include "ComLimitPoint/fiber_bundle/uniform_eval_family.h"
#include "ComLimitPoint/fields/field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT 1

// ===========================================================
// PROPERTY_DISC_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::property_disc_iterator*
fields::property_disc_iterator::
new_property_disc_iterator(const section_space_schema_member& xcoords_schema,
                           const section_space_schema_member& xprop_schema)
{
  property_disc_iterator* result;

  // Preconditions:

  require(xcoords_schema.state_is_read_accessible());
  require(xprop_schema.state_is_read_accessible());

  // Body:

  if(xcoords_schema.evaluator_family_name() == "uniform")
  {
    // Uniform coordinates.

    if(xprop_schema.rep().eval_is_above_disc())
    {
      result = new property_disc_iterator_4_2(xcoords_schema, xprop_schema);
    }
    else
    {
      result = new property_disc_iterator_4_3(xcoords_schema, xprop_schema);
    }
  }
  else if(xcoords_schema.evaluator_family_name() == "dlinear")
  {
    // Vertex element dlinear coordinates

    if(xprop_schema.evaluator_family_name() == "dlinear")
    {
      // Vertex element dlinear property.

      result = new property_disc_iterator_1_1(xcoords_schema, xprop_schema);
    }
    else if(xprop_schema.evaluation().name() == "__elements")
    {
      // Property eval same as coordinates eval.

      if(xprop_schema.rep().eval_is_above_disc())
      {
        // Property disc is below elements, but not just vertices.

        result = new property_disc_iterator_1_2(xcoords_schema, xprop_schema);
      }
      else
      {
        // Property disc is at or above elements
        // (typically element element constant).

        result = new property_disc_iterator_1_3(xcoords_schema, xprop_schema);
      }
    }
    else
    {
      // Property eval is not same as coordinates;
      // we don't support this yet.

      post_fatal_error_message("Property rep not supported with this coordinates rep.");
    }
  }
  else if(xcoords_schema.rep().name() == "vertex_vertex_constant")
  {
    // Vertex_vertex_constant coordinates

    if(xprop_schema.rep().name() == "vertex_vertex_constant")
    {
      // Vertex_vertex_constant property.

      result = new property_disc_iterator_1_1(xcoords_schema, xprop_schema);
    }
    else
    {
      // Property rep is not same as coordinates;
      // we don't support this yet.

      post_fatal_error_message("Property rep not supported with this coordinates rep.");
    }
  }
  else
  {
    // Unsupported coordinates rep.

    post_fatal_error_message("Coordinates rep not supported.");
  }

  // Postconditions:

  ensure(result != 0);
  ensure(result->coordinates_schema().is_same_state(&xcoords_schema));
  ensure(result->property_schema().is_same_state(&xprop_schema));

  // Exit:

  return result;
}

fields::property_disc_iterator::
~property_disc_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::section_space_schema_member&
fields::property_disc_iterator::
coordinates_schema() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  const section_space_schema_member& result = *_coord_state.schema;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::section_space_schema_member&
fields::property_disc_iterator::
property_schema() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  const section_space_schema_member& result = *_prop_state.schema;

  // Postconditions:

  // Exit

  return result;
}

const fiber_bundle::base_space_poset&
fields::property_disc_iterator::
base_space() const
{

  // Preconditions:


  // Body:

  const base_space_poset& result = *_coord_state.base_space_host;

  // Postconditions:

  ensure(result.is_same_state(coordinates_schema().base_space().host()));
  ensure(result.is_same_state(property_schema().base_space().host()));

  // Exit:

  return result;
}

const sheaf::subposet&
fields::property_disc_iterator::
coordinates_evaluation() const
{
  // Preconditions:

  // Body:

  const subposet& result = _coord_state.eval_sp;

  // Postconditions:

  ensure(result.is_same_state(&coordinates_schema().evaluation()));

  // Exit:

  return result;
}

const sheaf::subposet&
fields::property_disc_iterator::
property_evaluation() const
{
  // Preconditions:

  // Body:

  const subposet& result = _prop_state.eval_sp;

  // Postconditions:

  ensure(result.is_same_state(&property_schema().evaluation()));

  // Exit:

  return result;
}

int
fields::property_disc_iterator::
db() const
{
  int result;

  // Preconditions:

  require(!is_done());

  // Body:

  result = base_space().db(index());

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::pod_index_type
fields::property_disc_iterator::
type_id() const
{
  pod_index_type result;

  // Preconditions:

  require(!is_done());

  // Body:

  result = base_space().type_id(index());

  // Postconditions:


  // Exit:

  return result;
}

std::string
fields::property_disc_iterator::
type_name() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  /// @hack this signature and implementation
  /// forces an unnecessary copy (or three).

  string result(base_space().type_name(index()));

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::section_evaluator&
fields::property_disc_iterator::
coordinate_evaluator() const
{
  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  // The section space schema invariant ensures that the evaluator family
  // is compatible with the base space and hence the following call to
  // eval_family::member returns a non-void evaluator.

  section_evaluator& result = *_coord_state.evaluators->member(type_id());

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::section_evaluator&
fields::property_disc_iterator::
property_evaluator() const
{
  // Preconditions:

  require(is_initialized());
  require(!is_done());

  // Body:

  // The section space schema invariant ensures that the evaluator family
  // is compatible with the base space and hence the following call to
  // eval_family::member returns a non-void evaluator.

  section_evaluator& result = *_prop_state.evaluators->member(type_id());

  // Postconditions:

  // Exit

  return result;
}

const sheaf::block<fiber_bundle::discretization_context>&
fields::property_disc_iterator::
coordinate_discretization_members() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  const block<discretization_context>& result =
    _coord_state.discretization_members;

  // Postconditions:

  // Exit

  return result;
}

const sheaf::block<fiber_bundle::discretization_context>&
fields::property_disc_iterator::
property_discretization_members() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  const block<discretization_context>& result =
    _prop_state.discretization_members;

  // Postconditions:

  // Exit

  return result;
}


void
fields::property_disc_iterator::
get_prop_disc_values(const sec_vd& xsec)
{
  // Preconditions:

  require(xsec.state_is_read_accessible());
  require(xsec.schema().is_same_state(&coordinates_schema()));

  /// @hack required because discretization_context::values capacity is fixed at 3.

  require(xsec.schema().df() <= 3);

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS

void
fields::property_disc_iterator::
initialize_iteration(const field_vd& xfield, order_type xorder)
{

  // Preconditions:

  require(xfield.state_is_read_accessible());
  require(xfield.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xfield.property().schema().base_space().le(&xfield.coordinates().schema().base_space()));

  // Body:

  disable_invariant_check();

  // Initialize the iteration descriptors.

  _coord_state.initialize(xfield.coordinates().schema());
  _prop_state.initialize(xfield.property().schema());

  // Initialize the inherited iterator features.
  // By definition, this iterates over the property schema.

  initialize_order(xorder);
  initialize_traversal(xfield.property().schema().base_space());

  reset();

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinates_schema().is_same_state(&xfield.coordinates().schema()));
  ensure(coordinates_schema().is_same_type(&xfield.coordinates().schema()));
  ensure(coordinates_schema().version() == xfield.coordinates().schema().version());
  ensure(property_schema().is_same_state(&xfield.property().schema()));
  ensure(property_schema().is_same_type(&xfield.property().schema()));
  ensure(property_schema().version() == xfield.property().schema().version());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


void
fields::property_disc_iterator::
initialize_iteration(const section_space_schema_member& xcoordinates_schema,
                     const section_space_schema_member& xproperty_schema,
                     order_type xorder)
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xproperty_schema.state_is_read_accessible());
  require(xproperty_schema.base_space().le(&xcoordinates_schema.base_space()));

  // Body:

  disable_invariant_check();

  // Initialize the iteration descriptors.

  _coord_state.initialize(xcoordinates_schema);
  _prop_state.initialize(xproperty_schema);

  // Initialize the inherited iterator features

  initialize_order(xorder);
  initialize_traversal(xproperty_schema.base_space());

  reset();

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinates_schema().is_same_state(&xcoordinates_schema));
  ensure(coordinates_schema().is_same_type(&xcoordinates_schema));
  ensure(coordinates_schema().version() == xcoordinates_schema.version());
  ensure(property_schema().is_same_state(&xproperty_schema));
  ensure(property_schema().is_same_type(&xproperty_schema));
  ensure(property_schema().version() == xproperty_schema.version());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::property_disc_iterator::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const property_disc_iterator*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fields::property_disc_iterator*
fields::property_disc_iterator::
clone() const
{
  // Preconditions:

  // Body:

  property_disc_iterator* result = 0; // Just to silence compiler.

  is_abstract();

  // Postconditions:

  //  ensure(invariant());
  ensure(result != 0);

  // Exit

  return result;
}

bool
fields::property_disc_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:


  if(invariant_check())
  {
    invariance(depth_first_iterator::invariant());

    disable_invariant_check();

    invariance(anchor().is_same_state(&(property_schema().base_space())));
    invariance(property_schema().base_space().le(&coordinates_schema().base_space()));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// DEPTH_FIRST_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fields::property_disc_iterator::
force_is_done()
{
  // Preconditions:

  // Body:

  _prop_state.down_set.set_ct(0);
  _prop_state.discretization_members.set_ct(0);

  _coord_state.down_set.set_ct(0);
  _coord_state.discretization_members.set_ct(0);

  _above = true;
  _at    = false;

  depth_first_iterator::force_is_done();

  // Postconditions:

  ensure(invariant());
  ensure(is_done());

  // Exit

  return;
}

