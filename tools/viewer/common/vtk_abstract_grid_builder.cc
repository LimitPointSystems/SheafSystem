
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

// Implementation for class vtk_abstract_grid_builder

#include "vtk_abstract_grid_builder.h"
#include "assert_contract.h"
#include "base_space_member.h"
#include "eval_iterator.h"
#include "namespace_poset.h"

#include "vtkUnstructuredGrid.h"
#include "vtkUnstructuredGridWriter.h"
#include "vtkDoubleArray.h"
#include "vtkFieldData.h"
#include "vtkIdTypeArray.h"
#include "vtkIntArray.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkPointData.h"
#include "vtkCellData.h"

//#unfine DIAGNOSTIC_OUTPUT
// #define DIAGNOSTIC_OUTPUT

// Workaround for MS Visual C++
using namespace tool;
using namespace std;

// ============================================================================
// ANY FACET
// ============================================================================

///
bool
tool::vtk_abstract_grid_builder::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const vtk_abstract_grid_builder*>(other) != 0;

  // Postconditions:

  return result;
}

 

///
tool::vtk_abstract_grid_builder*
tool::vtk_abstract_grid_builder::
clone() const
{
  vtk_abstract_grid_builder* result = 0; // Just to silence compiler warnings.

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}


///
tool::vtk_abstract_grid_builder&
tool::vtk_abstract_grid_builder::
operator=(const vtk_abstract_grid_builder& xother)
{

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
tool::vtk_abstract_grid_builder::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}



// ============================================================================
// VTK_DATA_SET_BUILDER FACET
// ============================================================================

///
tool::vtk_abstract_grid_builder::
~vtk_abstract_grid_builder()
{

  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

///
void
tool::vtk_abstract_grid_builder::
set_name_space(namespace_poset& xns)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

///
vtkUnstructuredGrid*
tool::vtk_abstract_grid_builder::
build(const sec_vd& xcoords, const sec_vd& xproperty)
{
  vtkUnstructuredGrid* result;

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 3);
  require(xproperty.state_is_read_accessible());
  require(xproperty.schema().base_space().is_same_state(&xcoords.schema().base_space()));
  require(xproperty.schema().evaluation().is_same_state(&xcoords.schema().evaluation()));

  // Body:

  result = vtkUnstructuredGrid::New();

  build_pa(xcoords, xproperty, *result);

  // Postconditions:


  // Exit:

  return result;
}

///
vtkUnstructuredGrid*
tool::vtk_abstract_grid_builder::
build(const sec_vd& xcoords, const sec_vd& xproperty1, const sec_vd& xproperty2)
{
  vtkUnstructuredGrid* result;

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 3);
  require(xproperty1.state_is_read_accessible());
  require(xproperty1.schema().base_space().is_same_state(&xcoords.schema().base_space()));
  require(xproperty1.schema().evaluation().is_same_state(&xcoords.schema().evaluation()));
  require(xproperty2.state_is_read_accessible());
  require(xproperty2.schema().base_space().is_same_state(&xcoords.schema().base_space()));
  require(xproperty2.schema().evaluation().is_same_state(&xcoords.schema().evaluation()));

  // Body:

  result = vtkUnstructuredGrid::New();

  build_pa(xcoords, xproperty1, xproperty2, *result);

  // Postconditions:


  // Exit:

  return result;
}

///
vtkUnstructuredGrid*
tool::vtk_abstract_grid_builder::
build(const sec_vd& xcoords)
{
  vtkUnstructuredGrid* result;

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 3);

  // Body:

  result = vtkUnstructuredGrid::New();

  build_pa(xcoords, *result);

  // Postconditions:


  // Exit:

  return result;
}

///
void
tool::vtk_abstract_grid_builder::
build_pa(const sec_vd& xcoords, const sec_vd& xproperty, vtkUnstructuredGrid& xresult)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

///
void
tool::vtk_abstract_grid_builder::
build_pa(const sec_vd& xcoords, const sec_vd& xproperty1,
         const sec_vd& xproperty2, vtkUnstructuredGrid& xresult)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

///
void
tool::vtk_abstract_grid_builder::
build_pa(const sec_vd& xcoords, vtkUnstructuredGrid& xresult)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

bool
tool::vtk_abstract_grid_builder::
use_point_top_ids() const
{
  return _use_point_top_ids;
}

void
tool::vtk_abstract_grid_builder::
put_use_point_top_ids(bool xvalue)
{
  _use_point_top_ids = xvalue;
  
  ensure(use_point_top_ids() == xvalue);
  
  return;
}

bool
tool::vtk_abstract_grid_builder::
use_cell_top_ids() const
{
  return _use_cell_top_ids;
}

void
tool::vtk_abstract_grid_builder::
put_use_cell_top_ids(bool xvalue)
{
  _use_cell_top_ids = xvalue;
  
  ensure(use_cell_top_ids() == xvalue);
  
  return;
}

vtkIdTypeArray*
tool::vtk_abstract_grid_builder::
vtk_pt_label_ids() const
{
  return _vtk_pt_label_ids;
}

vtkIdTypeArray*
tool::vtk_abstract_grid_builder::
vtk_cell_label_ids() const
{
  return _vtk_cell_label_ids;
}

tool::vtk_abstract_grid_builder::
vtk_abstract_grid_builder()
{
  // Preconditions:


  // Body:

  _vtk_pt_label_ids = 0;
  _vtk_cell_label_ids = 0;

  _use_point_top_ids = true;
  _use_cell_top_ids = true;

  // Postconditions:


  // Exit:

  return;
}

// ============================================================================
//  NON-MEMBER FUNCTIONS
// ============================================================================

