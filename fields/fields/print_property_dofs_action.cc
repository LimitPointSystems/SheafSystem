
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
/// Implementation for class print_property_dofs_action

#include "ComLimitPoint/fields/print_property_dofs_action.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/block.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#include "std_iomanip.h"

using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// PRINT_PROPERTY_DOFS_ACTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::print_property_dofs_action::
print_property_dofs_action(sec_vd& xproperty,
                           property_dof_function_type xfcn,
                           bool xzero_specified)
    : _property(xproperty),
      _seq_id_space(&xproperty.schema().discretization_id_space())
{
  // Preconditions:

  require(xproperty.state_is_read_accessible());

  // Body:

  _dof_function = xfcn;

  _zero_specified = xzero_specified;

  /// @issue assuming binary schema, one dof per component.

  int ldf = xproperty.schema().df();

  _dofs.reserve(ldf);
  _dofs.set_ct(ldf);

  _specified_dofs.reserve(ldf);
  _specified_dofs.set_ct(ldf);

  // Postconditions:

  // Exit:

  return;
}

fields::print_property_dofs_action::
~print_property_dofs_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


void
fields::print_property_dofs_action::
operator()(const scoped_index& xdisc_id, block<sec_vd_value_type>& xcoords)
{
  // Preconditions:

  require(property().state_is_read_accessible());
  require(xdisc_id.in_scope());

  // Body:

  using namespace std;

  // Print the discretization poset and seq id.

  scoped_index lseq_id(*_seq_id_space, xdisc_id);

  cout << "id: " << setw(5) << xdisc_id.hub_id() << setw(5) << lseq_id;

  // Print the coordinates.

  cout << "  coordinates: ";
  for(int i=0; i<xcoords.ct(); ++i)
  {
    cout << " " << setw(16) << xcoords[i];
  }

  // Get the property dofs.

  property().get_fiber(lseq_id.pod(), _dofs.base(),
		       _dofs.ct()*sizeof(sec_vd_value_type));

  // Print the property.

  bool is_zero = true;
  cout << "  property: ";
  for(int i=0; i<_dofs.ct(); ++i)
  {
    is_zero = is_zero && (_dofs[i] == 0.0);
    cout << " " << setw(16) << _dofs[i];
  }

  if(_dof_function != 0)
  {

    if(is_zero && _zero_specified)
    {
      // Property is zero and client has requested
      // it be treated as specified value.

      for(int i=0; i<_dofs.ct(); ++i)
      {
        _specified_dofs[i] = 0.0;
      }
    }
    else
    {
      // Evaluate the property dof function at
      // the global coordinates of the discretization member.

      _dof_function(xcoords, _specified_dofs);
    }

    // Print the values specified by the property dof funtion.

    cout << "  specified: ";
    for(int i=0; i<_dofs.ct(); ++i)
    {
      cout << " " << setw(16) << _specified_dofs[i];
    }

    // Print the difference.

    cout << "  difference: ";
    for(int i=0; i<_dofs.ct(); ++i)
    {
      cout << " " << setw(16) << (_specified_dofs[i] - _dofs[i]);
    }
  }

  cout << endl;

  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::sec_vd&
fields::print_property_dofs_action::
property()
{
  // Preconditions:


  // Body:

  sec_vd& result = _property;

  // Postconditions:


  // Exit:

  return result;
}

fields::property_dof_function_type
fields::print_property_dofs_action::
dof_function()
{
  property_dof_function_type result;

  // Preconditions:

  // Body:

  result = _dof_function;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
