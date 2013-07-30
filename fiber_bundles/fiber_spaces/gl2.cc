

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

/// @file
/// Implementation for class gl2.

#include "gl2.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "gln_space.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "std_cmath.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS GL2_LITE
//==============================================================================


//==============================================================================
//  GL2 FACET OF CLASS GL2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::gl2_lite::
gl2_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gl2_lite::
gl2_lite(const gl2_lite& xother)
{
  // Preconditions:

  require(unexecutable("The component matrix is the inverse of the basis matrix."));

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gl2_lite&
fiber_bundle::gl2_lite::
operator=(const gl2_lite& xother)
{
  // Preconditions:

  require(unexecutable("The component matrix is the inverse of the basis matrix."));

  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::gl2_lite::
~gl2_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::gl2_lite::
gl2_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  require(unexecutable("The component matrix is the inverse of the basis matrix."));

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gl2_lite&
fiber_bundle::gl2_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  require(unexecutable("The component matrix is the inverse of the basis matrix."));

  // Body:

  _row_dofs = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}
fiber_bundle::gl2_lite::
gl2_lite(const matrix_type& xmatrix)
{
  // Preconditions:

  require(unexecutable("The component matrix is the inverse of the basis matrix."));

  // Body:

  *this = xmatrix;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gl2_lite& 
fiber_bundle::gl2_lite::
operator=(const matrix_type& xmatrix)
{
  // Preconditions:

  require(unexecutable("The component matrix is the inverse of the basis matrix."));

  // Body:

  //_row_dofs = xmatrix;
  _row_dofs = reinterpret_cast<const row_dofs_type&>(xmatrix);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}

fiber_bundle::gl2_lite::
operator gl2_lite::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl2_lite::
operator const gl2_lite::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl2_lite::
operator gl2_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl2_lite::
operator const gl2_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl2_lite::matrix_type& 
fiber_bundle::gl2_lite::
basis_matrix()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs.basis_matrix();

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::gl2_lite::matrix_type& 
fiber_bundle::gl2_lite::
basis_matrix() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  const matrix_type& result = _row_dofs.basis_matrix();

  // Exit:

  return result;
}

fiber_bundle::gl2_lite::matrix_type& 
fiber_bundle::gl2_lite::
component_matrix()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs.component_matrix();

  // Exit:

  return result;
}

const fiber_bundle::gl2_lite::matrix_type& 
fiber_bundle::gl2_lite::
component_matrix() const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs.component_matrix();

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::gl2_lite::
rescale(const value_type& xscale, const value_type& yscale)
{
  // Preconditions:

  // Body:

  // Get the basis matrix.

  matrix_type& bm = basis_matrix();

  // Set the basis matrix for rescaling.

  bm[0][0] = xscale;
  bm[0][1] =    0.0;
  bm[1][0] =    0.0;
  bm[1][1] = yscale;

  // Get the component matrix.

  matrix_type& cm = component_matrix();

  // Set the component matrix for rescaling.

  // The component matrix is the inverse of the basis matrix
  // and the inverse is very simple in this case.

  cm[0][0] = 1.0/xscale;
  cm[0][1] =        0.0;
  cm[1][0] =        0.0;
  cm[1][1] = 1.0/yscale;

  // Postconditions:

  // Exit:
}

void
fiber_bundle::gl2_lite::
rotate_z(const value_type& xangle)
{
  // Preconditions:

  // Body:

  // Set the basis matrix for rotation about the z-axis.

  matrix_type& bm = basis_matrix();

  value_type lcos = cos(xangle);
  value_type lsin = sin(xangle);

  bm[0][0] =  lcos;
  bm[0][1] =  lsin;
  bm[1][0] = -lsin;
  bm[1][1] =  lcos;

  // Set component matrix to the inverse of the basis matrix.

  matrix_type& cm = component_matrix();

  cm[0][0] =  lcos;
  cm[0][1] = -lsin;
  cm[1][0] =  lsin;
  cm[1][1] =  lcos;

  // Postconditions:

  // Exit:
}

void
fiber_bundle::gl2_lite::
basis(value_type xb0[],
      value_type xb1[]) const
{
  // Preconditions:

  require(unexecutable("Each xbi is a vector of length at least 2."));

  // Body:

  // The new basis vectors are the columns of the b matrix
  // See comments in header file on matrix definition.

  xb0[0] = component(0); // bxx
  xb1[0] = component(1); // bxy

  xb0[1] = component(2); // byx
  xb1[1] = component(3); // byy

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable("Return values are set to the correct components"));


  // Exit:

  return;
}

void
fiber_bundle::gl2_lite::
put_basis(const value_type xb0[],
          const value_type xb1[])
{
  // Preconditions:

  require(unexecutable("Each xbi is a vector of length at least 2."));

  // Body:

  // The new basis vectors are the columns of the b matrix.
  // See comments in header file on matrix definition.

  put_component(0, xb0[0]); // bxx
  put_component(1, xb1[0]); // bxy

  put_component(2, xb0[1]); // byx
  put_component(3, xb1[1]); // byy

  // Now make the component matrix the inverse of the basis matrix.

  component_matrix() = basis_matrix().inverse();

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable("Components are set to the correct basis values"));
  ensure(unexecutable("The component matrix is the inverse of the basis matrix"));

  // Exit:

  return;
}

void
fiber_bundle::gl2_lite::
get_matrix(row_dofs_type& xmatrix) const
{
  // Preconditions:

  require(unexecutable("Each xbi is a vector of length at least 3."));

  // Body:

  // Copy the row dofs into xmatrix.

  xmatrix = _row_dofs;

  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(),  xmatrix.components[i] == component(i));

  // Exit:

  return;
}

void
fiber_bundle::gl2_lite::
put_matrix(row_dofs_type& xmatrix)
{
  // Preconditions:

  require(xmatrix.basis_matrix().determinant() != 0);

  // Body:

  // Make the component part equal to the inverse of the basis part.

  xmatrix.component_matrix() = xmatrix.basis_matrix().inverse();

  // Copy the xmatrix into the row_dofs.

  _row_dofs = xmatrix;

  //put_components(xmatrix.components, xmatrix.d());

  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(), component(i) == xmatrix.components[i]);
  ensure(unexecutable("The component matrix is the inverse of the basis matrix"));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
//  GLN FACET OF CLASS GL2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::gl2_lite::
n() const
{
  // Preconditions:

  // Body:

  int result = 2;

  // Postconditions:

  ensure(invariant());
  ensure(result == 2);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// GROUP FACET OF CLASS GL2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS GL2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::gl2_lite::
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
fiber_bundle::gl2_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("gl2_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::gl2_lite*
fiber_bundle::gl2_lite::
clone() const
{
  gl2_lite* result = 0;

  // Preconditions:

  // Body:

  result = new gl2_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS GL2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::gl2_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const gl2_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::gl2_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(gln_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::gl2_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::gl2_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS GL2
//==============================================================================


//==============================================================================
//  GL2 FACET OF CLASS GL2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::gl2::
gl2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::gl2::
gl2(const gl2& xother, bool xnew_jem)
{

  // Preconditions:

  require(xnew_jem ? xother.is_attached() : true);

  // Body:

  // Note: even though the code here is identical to that in
  // the copy constructors of all descendants of abstract_poset_member,
  // this can not just call its base class copy constructor
  // because it must invoke versions defined in this class of virtual
  // attach_to_state and virtual attach_handle_data_members
  // (called from new_jem_state).

  if(xnew_jem)
  {
    new_jem_state(const_cast<gl2*>(&xother), true, true);
  }
  else
  {
    attach_to_state(&xother);
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

///
fiber_bundle::gl2&
fiber_bundle::gl2::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));
  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

///
fiber_bundle::gl2&
fiber_bundle::gl2::
operator=(const gl2& xother)
{
  // Preconditions:

  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

fiber_bundle::gl2::
~gl2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::gl2::
gl2(poset* xhost, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(xhost, 0, false, xauto_access)));

  // Body:

  new_jim_state(xhost, 0, false, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, 0, false, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::gl2::
gl2(poset_state_handle& xhost,
    const row_dofs_type& xrdt,
    bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(&xhost, 0, false, xauto_access)));

  // Body:

  new_jim_state(&xhost, 0, false, xauto_access);

  if(xauto_access)
  {
    xhost.get_read_write_access();
  }

  *this = xrdt;

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(postcondition_of(new_jim_state(&xhost, 0, false, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::gl2&
fiber_bundle::gl2::
operator=(const row_dofs_type& xrdt)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  int ld = d();

  // Get the matrix

  for(int i=0; i<ld; ++i)
  {
    put_component(i, xrdt.components[i]);
  }

  // Postconditions:

  ensure_for_all(i, 0, d(), component(i) == xrdt.components[i]);

  // Exit:

  return *this;

}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

fiber_bundle::gl2::
gl2(const poset* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  // ensure(host() == xhost);
  ensure(index() == xhub_id);
}

fiber_bundle::gl2::
gl2(const poset* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  // ensure(host() == xhost);
  ensure(index() ==~ xid);
}

fiber_bundle::gl2::
gl2(const poset* xhost, const string& xname)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());
  require(xhost->contains_member(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  // ensure(host() == xhost);
  ensure(name() == xname);

}

fiber_bundle::gl2::
gl2(gl2* xother)
{

  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));

}

fiber_bundle::gl2::
operator gl2::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl2::
operator const gl2::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::gl2::
get_matrix(row_dofs_type& xmatrix) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  xmatrix = *this;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

void
fiber_bundle::gl2::
put_matrix(row_dofs_type& xmatrix)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(xmatrix.basis_matrix().determinant() != 0);

  // Body:

  // Make the component part equal to the inverse of the basis part.

  xmatrix.component_matrix() = xmatrix.basis_matrix().inverse();

  // Copy the xmatrix into the row_dofs.

  put_components(xmatrix.components, xmatrix.d());

  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(), component(i) == xmatrix.components[i]);

  // Exit:

  return;
}

///
fiber_bundle::gl2::volatile_type*
fiber_bundle::gl2::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
//  GLN FACET OF CLASS GL2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// GROUP FACET OF CLASS GL2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::gl2::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "gl2_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::gl2::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "bxx DOUBLE false ";
  lmember_names       += "bxy DOUBLE false ";
  lmember_names       += "byx DOUBLE false ";
  lmember_names       += "byy DOUBLE false ";
  lmember_names       += "cxx DOUBLE false ";
  lmember_names       += "cxy DOUBLE false ";
  lmember_names       += "cyx DOUBLE false ";
  lmember_names       += "cyy DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              gln::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS GL2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::gl2::
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
fiber_bundle::gl2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("gl2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::gl2*
fiber_bundle::gl2::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  gl2* result = new gl2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS GL2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::gl2::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(gln::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(state_is_read_accessible() ? n() == 2 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  // Exit:

  return result;
}

bool
fiber_bundle::gl2::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const gl2*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

ostream& fiber_bundle::operator<<(ostream& xos, const gl2_lite& xlite)
{
  xos << "basis" << endl;
  xos << " " << xlite[0] << " " << xlite[1] << endl;
  xos << " " << xlite[2] << " " << xlite[3] << endl;

  xos << endl;

  xos << "component:" << endl;
  xos << " " << xlite[4] << " " << xlite[5] << endl;
  xos << " " << xlite[6] << " " << xlite[7] << endl;

  return xos;
}

ostream& fiber_bundle::operator<<(ostream& xos, const gl2& xpersistent)
{
  const gl2::row_dofs_type& lm = xpersistent;

  xos << "basis:" << endl;
  xos << " " << lm[0] << " " << lm[1] << endl;
  xos << " " << lm[2] << " " << lm[3] << endl;
  xos << endl;

  xos << "component:" << endl;
  xos << " " << lm[4] << " " << lm[5] << endl;
  xos << " " << lm[6] << " " << lm[7] << endl;
  xos << endl;

  return xos;
}

void
fiber_bundle::inverse(const gl2_lite& xlite, gl2_lite& xresult)
{
  // Preconditions:

  // Body:

  ///@issue What do we want to do here? 
  ///       If the component matrix is already the inverse of the
  ///       basis matrix we just need to swap the basis and component
  ///       matrices here.

  ///@todo Implement a way to deal with the above issue.

  const gl2_lite::matrix_type& bm = xlite.basis_matrix();
  bm.inverse(xresult.basis_matrix());
  
  const gl2_lite::matrix_type& cm = xlite.component_matrix();
  cm.inverse(xresult.component_matrix());

  // Postconditions:

  ensure(unexecutable("xresult is the inverse of xgl"));


  // Exit:
}

void
fiber_bundle::inverse(const gl2& xgl, gl2& xresult)
{
  ///@todo Add auto_access argument or eliminate this function.

  // Preconditions:

  require(xgl.state_is_read_accessible());
  require(xresult.state_is_read_accessible());

  // Body:

  ///@issue What do we want to do here? 
  ///       If the component matrix is already the inverse of the
  ///       basis matrix we just need to swap the basis and component
  ///       matrices here.

  ///@todo Implement a way to deal with the above issue.

  typedef gl2::row_dofs_type row_dofs_type;

  const row_dofs_type& lrdt_gl = xgl;
  row_dofs_type& lrdt_result = xresult;

  lrdt_gl.basis_matrix().inverse(lrdt_result.basis_matrix());
  lrdt_gl.component_matrix().inverse(lrdt_result.component_matrix());

  // Postconditions:

  ensure(unexecutable("xresult is the inverse of xgl"));

  // Exit:
}

