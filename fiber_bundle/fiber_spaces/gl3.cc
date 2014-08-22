
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
/// Implementation for class gl3.

#include "ComLimitPoint/fiber_bundle/gl3.impl.h"

#include "ComLimitPoint/sheaf/abstract_poset_member.impl.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/at0.h"
#include "ComLimitPoint/fiber_bundle/at1_space.h"
#include "ComLimitPoint/fiber_bundle/e3.h"
#include "ComLimitPoint/fiber_bundle/gln_space.h"
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#include "ComLimitPoint/sheaf/schema_poset_member.h"
#include "std_cmath.h"
#include "ComLimitPoint/sheaf/wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS GL3_LITE
//==============================================================================


//==============================================================================
//  GL3 FACET OF CLASS GL3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::gl3_lite::
gl3_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gl3_lite::
gl3_lite(const gl3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gl3_lite&
fiber_bundle::gl3_lite::
operator=(const gl3_lite& xother)
{
  // Preconditions:

  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::gl3_lite::
~gl3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::gl3_lite::
gl3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gl3_lite&
fiber_bundle::gl3_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  _row_dofs = xrow_dofs;
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}

fiber_bundle::gl3_lite::
gl3_lite(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  *this = xmatrix;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gl3_lite& 
fiber_bundle::gl3_lite::
operator=(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  //_row_dofs = xmatrix;
  _row_dofs = reinterpret_cast<const row_dofs_type&>(xmatrix);
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}

fiber_bundle::gl3_lite::
operator gl3_lite::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl3_lite::
operator const gl3_lite::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl3_lite::
operator gl3_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl3_lite::
operator const gl3_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl3_lite::matrix_type& 
fiber_bundle::gl3_lite::
basis_matrix()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs.basis_matrix();

  // Postconditions:

  // Exit:

  return result;
}

const fiber_bundle::gl3_lite::matrix_type& 
fiber_bundle::gl3_lite::
basis_matrix() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  const matrix_type& result = _row_dofs.basis_matrix();

  // Exit:

  return result;
}

fiber_bundle::gl3_lite::matrix_type& 
fiber_bundle::gl3_lite::
component_matrix()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs.component_matrix();

  // Exit:

  return result;
}

const fiber_bundle::gl3_lite::matrix_type& 
fiber_bundle::gl3_lite::
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
fiber_bundle::gl3_lite::
rescale(const value_type& xscale,
        const value_type& yscale,
        const value_type& zscale)
{
  // Preconditions:

  // Body:

  // Get the basis matrix.

  matrix_type& bm = basis_matrix();

  // Set the basis matrix for rescaling.

  bm.assign(0.0);

  bm[0][0] = xscale;
  bm[1][1] = yscale;
  bm[2][2] = zscale;

  // Get the component matrix.

  matrix_type& cm = component_matrix();

  // Set the component matrix for rescaling.

  // The component matrix is the inverse of the basis matrix
  // and the inverse is very simple in this case.

  cm.assign(0.0);

  cm[0][0] = 1.0/xscale;
  cm[1][1] = 1.0/yscale;
  cm[2][2] = 1.0/zscale;

  // Postconditions:

  ensure(invariant());

  // Exit:
  
}

void
fiber_bundle::gl3_lite::
rotate_x(const value_type& xangle)
{
  // Preconditions:

  // Body:

  // Set the basis matrix for rotation about the x-asis.

  matrix_type& bm = basis_matrix();

  value_type lcos = cos(xangle);
  value_type lsin = sin(xangle);

  bm[0][0] =   1.0;
  bm[0][1] =   0.0;
  bm[0][2] =   0.0;

  bm[1][0] =   0.0;
  bm[1][1] =  lcos;
  bm[1][2] = -lsin;

  bm[2][0] =   0.0;
  bm[2][1] =  lsin;
  bm[2][2] =  lcos;

  // Set component matrix to the inverse of the basis matrix.

  bm.inverse(component_matrix());

  // Postconditions:

  ensure(invariant());

  // Exit:
}

void
fiber_bundle::gl3_lite::
rotate_y(const value_type& xangle)
{
  // Preconditions:

  // Body:

  // Set the basis matrix for rotation about the y-axis.

  matrix_type& bm = basis_matrix();

  value_type lcos = cos(xangle);
  value_type lsin = sin(xangle);

  bm[0][0] =  lcos;
  bm[0][1] =   0.0;
  bm[0][2] =  lsin;

  bm[1][0] =   0.0;
  bm[1][1] =   1.0;
  bm[1][2] =   0.0;

  bm[2][0] = -lsin;
  bm[2][1] =   0.0;
  bm[2][2] =  lcos;

  // Set component matrix to the inverse of the basis matrix.

  bm.inverse(component_matrix());

  // Postconditions:

  ensure(invariant());

  // Exit:
}

void
fiber_bundle::gl3_lite::
rotate_z(const value_type& xangle)
{
  // Preconditions:

  // Body:

  // Set the basis matrix for rotation about the z-axis.

  matrix_type& bm = basis_matrix();

  value_type lcos = cos(xangle);
  value_type lsin = sin(xangle);

  bm[0][0] =  lcos;
  bm[0][1] = -lsin;
  bm[0][2] =  0.0;

  bm[1][0] =  lsin;
  bm[1][1] =  lcos;
  bm[1][2] =  0.0;

  bm[2][0] =  0.0;
  bm[2][1] =  0.0;
  bm[2][2] =  1.0;

  // Set component matrix to the inverse of the basis matrix.

  bm.inverse(component_matrix());

  // Postconditions:

  ensure(invariant());

  // Exit:
}

void
fiber_bundle::gl3_lite::
rotate_euler(const value_type& xalpha,
             const value_type& xbeta,
             const value_type& xgamma)
{
  // Preconditions:

  // Body:

  // Set the basis matrix for rotation through the euler angles.

  matrix_type& bm = basis_matrix();

  value_type cos_alpha = cos(xalpha);
  value_type sin_alpha = sin(xalpha);

  value_type cos_beta  = cos(xbeta);
  value_type sin_beta  = sin(xbeta);

  value_type cos_gamma = cos(xgamma);
  value_type sin_gamma = sin(xgamma);

  // Formula taken from G. Arfken, Math. Methods for Physicists,
  // 3rd ed. p 200.

  bm[0][0] =  cos_gamma*cos_beta*cos_alpha - sin_gamma*sin_alpha;
  bm[0][1] = -sin_gamma*cos_beta*cos_alpha - cos_gamma*sin_alpha;
  bm[0][2] =  sin_beta*cos_alpha;

  bm[1][0] =  cos_gamma*cos_beta*sin_alpha + sin_gamma*cos_alpha;
  bm[1][1] = -sin_gamma*cos_beta*sin_alpha + cos_gamma*cos_alpha;
  bm[1][2] =  sin_beta*sin_alpha;

  bm[2][0] = -cos_gamma*sin_beta;
  bm[2][1] =  sin_gamma*sin_beta;
  bm[2][2] =  cos_beta;

  // Set component matrix to the inverse of the basis matrix.

  bm.inverse(component_matrix());


  // Postconditions:

  ensure(invariant());

  // Exit:

}

void
fiber_bundle::gl3_lite::
basis(value_type xb0[],
      value_type xb1[],
      value_type xb2[]) const
{
  // Preconditions:

  require(unexecutable("Each xbi is a vector of length at least 2."));

  // Body:

  // The new basis vectors are the columns of the b matrix
  // See comments in header file on matrix definition.

  xb0[0] = component(0); // bxx
  xb1[0] = component(1); // bxy
  xb2[0] = component(2); // bxz

  xb0[1] = component(3); // byx
  xb1[1] = component(4); // byy
  xb2[1] = component(5); // byz

  xb0[2] = component(6); // bzx
  xb1[2] = component(7); // bzy
  xb2[2] = component(8); // bzz

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable("Return values are set to the correct components"));

  // Exit:

  return;
}

void
fiber_bundle::gl3_lite::
put_basis(const value_type xb0[],
          const value_type xb1[],
          const value_type xb2[])
{
  // Preconditions:

  require(unexecutable("Each xbi is a vector of length at least 3."));

  // Body:

  // The new basis vectors are the columns of the b matrix.
  // See comments in header file on matrix definition.

  put_component(0, xb0[0]); // bxx
  put_component(1, xb1[0]); // bxy
  put_component(2, xb2[0]); // bxz

  put_component(3, xb0[1]); // byx
  put_component(4, xb1[1]); // byy
  put_component(5, xb2[1]); // byz

  put_component(6, xb0[2]); // bzx
  put_component(7, xb1[2]); // bzy
  put_component(8, xb2[2]); // bzz

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
fiber_bundle::gl3_lite::
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
fiber_bundle::gl3_lite::
put_matrix(row_dofs_type& xmatrix)
{
  // Preconditions:

  // Body:

  // Make the component part equal to the inverse of the basis part.

  xmatrix.component_matrix() = xmatrix.basis_matrix().inverse();

  // Copy the xmatrix into the row_dofs.

  _row_dofs = xmatrix;

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
//  GLN FACET OF CLASS GL3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::gl3_lite::
n() const
{
  // Preconditions:

  // Body:

  int result = 3;

  // Postconditions:

  ensure(invariant());
  ensure(result == 3);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// GROUP FACET OF CLASS GL3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS GL3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::gl3_lite::
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

const std::string&
fiber_bundle::gl3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("gl3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::gl3_lite*
fiber_bundle::gl3_lite::
clone() const
{
  gl3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new gl3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS GL3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::gl3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const gl3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}


bool
fiber_bundle::gl3_lite::
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
fiber_bundle::gl3_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::gl3_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS GL3
//==============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::gl3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "gl3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::gl3::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "bxx DOUBLE false bxy DOUBLE false bxz DOUBLE false ";
  lmember_names       += "byx DOUBLE false byy DOUBLE false byz DOUBLE false ";
  lmember_names       += "bzx DOUBLE false bzy DOUBLE false bzz DOUBLE false ";

  lmember_names       += "cxx DOUBLE false cxy DOUBLE false cxz DOUBLE false ";
  lmember_names       += "cyx DOUBLE false cyy DOUBLE false cyz DOUBLE false ";
  lmember_names       += "czx DOUBLE false czy DOUBLE false czz DOUBLE false";

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

fiber_bundle::gl3::host_type&
fiber_bundle::gl3::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering gl3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));

  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 18);

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, xvector_space_path, xauto_access); 

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access) );
  ensure(result.n(true) == 3);
  ensure(result.vector_space_path(true) == xvector_space_path );

  ensure(result.d(true) == 18);
  
  // Exit:

  // cout << "Leaving gl3::new_host." << endl;
  return result;
}

fiber_bundle::gl3::host_type&
fiber_bundle::gl3::
standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering gl3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<gl3>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(vector_space_type::standard_host_path<vector_space_type>(xsuffix), xauto_access));

  // Body:

  // Create the vector space if necessary.

  poset_path lvector_space_path = vector_space_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<gl3>(xsuffix));

  host_type* result_ptr;
  if(xns.contains_path(lpath, xauto_access))
  {
    result_ptr = &xns.member_poset<host_type>(lpath, xauto_access);
  }
  else
  {
    result_ptr = &new_host(xns, lpath, standard_schema_path(), lvector_space_path, xauto_access);
  }

  host_type& result = *result_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path<gl3>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.scalar_space_path(true) == vector_space_type::scalar_type::standard_host_path<vector_space_type::scalar_type>(xsuffix));
  ensure(result.n(true) == 3);
  ensure(result.vector_space_path(true) == vector_space_type::standard_host_path<vector_space_type>(xsuffix));

  ensure(result.d(true) == 18);

  // Exit:

  // cout << "Leaving gl3::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
//  GL3 FACET OF CLASS GL3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::gl3::
gl3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::gl3::
gl3(const gl3& xother, bool xnew_jem)
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
    new_jem_state(const_cast<gl3*>(&xother), true, true);
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
fiber_bundle::gl3&
fiber_bundle::gl3::
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
fiber_bundle::gl3&
fiber_bundle::gl3::
operator=(const gl3& xother)
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

fiber_bundle::gl3::
~gl3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::gl3::
gl3(poset* xhost, bool xauto_access)
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

fiber_bundle::gl3::
gl3(poset_state_handle& xhost,
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

fiber_bundle::gl3&
fiber_bundle::gl3::
operator=(const row_dofs_type& xrdt)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  int ld = d();

  for(int i=0; i<ld; ++i)
  {
    put_component(i, xrdt.components[i]);
  }

  // Postconditions:

  ensure_for_all(i, 0, d(), component(i) == xrdt.components[i]);

  // Exit:

  return *this;

}

fiber_bundle::gl3::
gl3(const poset* xhost, pod_index_type xhub_id)
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

fiber_bundle::gl3::
gl3(const poset* xhost, const scoped_index& xid)
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

fiber_bundle::gl3::
gl3(const poset* xhost, const std::string& xname)
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

fiber_bundle::gl3::
gl3(gl3* xother)
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

fiber_bundle::gl3::
operator gl3::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::gl3::
operator const gl3::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::gl3::
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
fiber_bundle::gl3::
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
fiber_bundle::gl3::volatile_type*
fiber_bundle::gl3::
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
//  GLN FACET OF CLASS GL3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// GROUP FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS GL3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::gl3::
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

const std::string&
fiber_bundle::gl3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("gl3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::gl3*
fiber_bundle::gl3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  gl3* result = new gl3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS GL3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::gl3::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(gln::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance(state_is_read_accessible() ? n() == 3 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  // Exit:

  return result;
}

bool
fiber_bundle::gl3::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const gl3*>(xother) != 0;

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

std::ostream& 
fiber_bundle::
operator<<(std::ostream& xos, const gl3_lite& xlite)
{
  xos << "basis:" << endl;
  xos << " " << xlite[0] << " " << xlite[1] << " " << xlite[2] << endl;
  xos << " " << xlite[3] << " " << xlite[4] << " " << xlite[5] << endl;
  xos << " " << xlite[6] << " " << xlite[7] << " " << xlite[8] << endl;

  xos << endl;

  xos << "component:" << endl;
  xos << " " << xlite[ 9] << " " << xlite[10] << " " << xlite[11] << endl;
  xos << " " << xlite[12] << " " << xlite[13] << " " << xlite[14] << endl;
  xos << " " << xlite[15] << " " << xlite[16] << " " << xlite[17] << endl;

  return xos;
}

std::ostream& 
fiber_bundle::
operator<< (std::ostream& xos, const gl3& xpersistent)
{
  const gl3::row_dofs_type& lm = xpersistent;

  xos << "basis:" << endl;
  xos << " " << lm[0] << " " << lm[1] << " " << lm[2] << endl;
  xos << " " << lm[3] << " " << lm[4] << " " << lm[5] << endl;
  xos << " " << lm[6] << " " << lm[7] << " " << lm[8] << endl;

  xos << endl;

  xos << "component:" << endl;
  xos << " " << lm[ 9] << " " << lm[10] << " " << lm[11] << endl;
  xos << " " << lm[12] << " " << lm[13] << " " << lm[14] << endl;
  xos << " " << lm[15] << " " << lm[16] << " " << lm[17] << endl;

  return xos;
}

void
fiber_bundle::
inverse(const gl3_lite& xlite, gl3_lite& xresult)
{
  // Preconditions:

  // Body:

  ///@issue What do we want to do here? 
  ///       If the component matrix is already the inverse of the
  ///       basis matrix we just need to swap the basis and component
  ///       matrices here.

  ///@todo Implement a way to deal with the above issue.

  const gl3_lite::matrix_type& bm = xlite.basis_matrix();
  bm.inverse(xresult.basis_matrix());
  
  const gl3_lite::matrix_type& cm = xlite.component_matrix();
  cm.inverse(xresult.component_matrix());

  // Postconditions:

  ensure(unexecutable("xresult is the inverse of xgl"));


  // Exit:
}

void
fiber_bundle::
inverse(const gl3& xgl, gl3& xresult)
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

  typedef gl3::row_dofs_type row_dofs_type;

  const row_dofs_type& lrdt_gl = xgl;
  row_dofs_type& lrdt_result = xresult;

  lrdt_gl.basis_matrix().inverse(lrdt_result.basis_matrix());
  lrdt_gl.component_matrix().inverse(lrdt_result.component_matrix());

  // Postconditions:

  ensure(unexecutable("xresult is the inverse of xgl"));

  // Exit:
}

