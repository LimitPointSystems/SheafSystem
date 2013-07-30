

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
/// Implementation for class e3.

#include "e3.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1_space.h"
#include "at2_e3.h"
#include "at3_e3.h"
#include "gl3.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "st2_e3.h"
#include "st3_e3.h"
#include "st4_e3.h"
#include "stp_space.h"
#include "t2_e3.h"
#include "t3_e3.h"
#include "t4_e3.h"
#include "tolerance_comparison.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS E3_LITE
//==============================================================================

//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (E3) FACET OF CLASS E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::e3_lite::
e3_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e3_lite::
e3_lite(const e3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e3_lite&
fiber_bundle::e3_lite::
operator=(const e3_lite& xother)
{

  // Preconditions:

  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;
  
  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(*this == xother));
  
  // Exit:

  return *this;
}


fiber_bundle::e3_lite::
~e3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::e3_lite::
e3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  // Exit:
}

fiber_bundle::e3_lite&
fiber_bundle::e3_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  _row_dofs = xrow_dofs;

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(row_dofs() == xrow_dofs));
  //ensure_for_all(i, 0, d(), component(i) == xrow_dofs[i]);

  // Exit:

  return *this;

}

fiber_bundle::e3_lite::
e3_lite(const value_type& xvalue)
{
  // Preconditions:

  // Body:

  _row_dofs.components[0] = xvalue;
  _row_dofs.components[1] = xvalue;
  _row_dofs.components[2] = xvalue;

  // Postconditions:

   ensure(invariant());
   ensure(isunordered_or_equals(component(0), xvalue)); 
   ensure(isunordered_or_equals(component(1), xvalue));
   ensure(isunordered_or_equals(component(2), xvalue));

  // Exit:
}

fiber_bundle::e3_lite::
e3_lite(const value_type& x0, const value_type& x1, const value_type& x2)
{
  // Preconditions:

  // Body:

  _row_dofs.components[0] = x0;
  _row_dofs.components[1] = x1;
  _row_dofs.components[2] = x2;

  // Postconditions:

   ensure(invariant());
   ensure(isunordered_or_equals(component(0), x0)); 
   ensure(isunordered_or_equals(component(1), x1));
   ensure(isunordered_or_equals(component(2), x2));

  // Exit:
}

fiber_bundle::e3_lite::
operator e3_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::e3_lite::
operator const e3_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::e3_lite::
put_components(const value_type& x_comp,
               const value_type& y_comp,
               const value_type& z_comp)
{
  // Preconditions:

  // Body:

  //   put_component(0, x_comp);
  //   put_component(1, y_comp);
  //   put_component(2, z_comp);

  _row_dofs.components[0] = x_comp;
  _row_dofs.components[1] = y_comp;
  _row_dofs.components[2] = z_comp;

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), x_comp));
  ensure(isunordered_or_equals(component(1), y_comp));
  ensure(isunordered_or_equals(component(2), z_comp));

  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (AT1) FACET OF CLASS E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::e3_lite::
dd() const
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
// VECTOR ALGEBRA (VD) FACET OF CLASS E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::e3_lite::
operator==(const e3_lite& xother) const
{
  // cout << endl << "Entering e3_lite::operator==." << endl;

  // Preconditions:
  
  // Body:

  bool result = 
    (_row_dofs.components[0] == xother._row_dofs.components[0]) &&
    (_row_dofs.components[1] == xother._row_dofs.components[1]) &&
    (_row_dofs.components[2] == xother._row_dofs.components[2]);

  // Postconditions:


  // Exit:

  // cout << "Leaving e3_lite::operator==." << endl;
  return result;
}

fiber_bundle::e3_lite&
fiber_bundle::e3_lite::
operator=(const value_type& xvalue)
{
  // Preconditions:

  // Body:

  _row_dofs.components[0] = xvalue;
  _row_dofs.components[1] = xvalue;
  _row_dofs.components[2] = xvalue;
  
  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(), component(i) == xvalue);

  // Exit:

  return *this;

}

bool
fiber_bundle::e3_lite::
operator==(const value_type& xvalue) const
{
  // Preconditions:

  // Body:

  bool result = 
    (_row_dofs.components[0] == xvalue) &&
    (_row_dofs.components[1] == xvalue) &&
    (_row_dofs.components[2] == xvalue);
  
  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(), !result || component(i) == xvalue);

  // Exit:

  return result;

}

const fiber_bundle::tp_lite&
fiber_bundle::e3_lite::
static_tp_prototype(int xp)
{
  // Preconditions:

  require((0 <= xp) && (xp <= 4));

  // Body:

  switch(xp)
  {
    case 0:
      {
	static const at0_lite lat0_lite;
	return lat0_lite;
      }
    case 1:
      {
	static const e3_lite le3_lite;
	return le3_lite;
      }
    case 2:
      {
	static const t2_e3_lite lt2_e3_lite;
	return lt2_e3_lite;
      }
    case 3:
      {
	static const t3_e3_lite lt3_e3_lite;
	return lt3_e3_lite;
      }
    case 4:
      {
	static const t4_e3_lite lt4_e3_lite;
	return lt4_e3_lite;
      }
    default:
      {
	// Can't get here because of the precondition.
	static const tp_lite ltp_lite;
	return ltp_lite;
      }
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::tp_lite&
fiber_bundle::e3_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::atp_lite&
fiber_bundle::e3_lite::
static_atp_prototype(int xp)
{
  // Preconditions:

  require((0 <= xp) && (xp <= 3));

  // Body:

  switch(xp)
  {
    case 0:
      {
	static const at0_lite lat0_lite;
	return lat0_lite;
      }
    case 1:
      {
	static const e3_lite le3_lite;
	return le3_lite;
      }
    case 2:
      {
	static const at2_e3_lite lat2_e3_lite;
	return lat2_e3_lite;
      }
    case 3:
      {
	static const at3_e3_lite lat3_e3_lite;
	return lat3_e3_lite;
      }
    default:
      {
	// Can't get here because of the precondition.
	static const atp_lite latp_lite;
	return latp_lite;
      }
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::atp_lite&
fiber_bundle::e3_lite::
atp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(static_atp_prototype(xp)));
  
  // Body:

  const atp_lite& result = static_atp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_atp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::stp_lite&
fiber_bundle::e3_lite::
static_stp_prototype(int xp)
{
  // Preconditions:

  require((2 <= xp) && (xp <= 4));

  // Body:

  switch(xp)
  {
    case 2:
      {
	static const st2_e3_lite lst2_e3_lite;
	return lst2_e3_lite;
      }
    case 3:
      {
	static const st3_e3_lite lst3_e3_lite;
	return lst3_e3_lite;
      }
    case 4:
      {
	static const st4_e3_lite lst4_e3_lite;
	return lst4_e3_lite;
      }
    default:
      {
	// Can't get here because of the precondition.
	static const stp_lite lstp_lite;
	return lstp_lite;
      }
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::stp_lite&
fiber_bundle::e3_lite::
stp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(static_stp_prototype(xp)));
  
  // Body:

  const stp_lite& result = static_stp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_stp_prototype(xp)));
  
  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::e3_lite::
c_lt(const e3_lite& xother) const
{
  // cout << endl << "Entering e3::c_lt." << endl;

  // Preconditions:


  // Body:

  bool result = 
    (_row_dofs.components[0] < xother._row_dofs.components[0]) &&
    (_row_dofs.components[1] < xother._row_dofs.components[1]) &&
    (_row_dofs.components[2] < xother._row_dofs.components[2]);
  

  // Postconditions:

  ensure(result == (((*this)[0] < xother[0]) && ((*this)[1] < xother[1]) && ((*this)[2] < xother[2])));

  // Exit:

  // cout << "Leaving e3::c_lt." << endl;
  return result;
}

bool
fiber_bundle::e3_lite::
c_le(const e3_lite& xother) const
{
  // cout << endl << "Entering e3::c_le." << endl;

  // Preconditions:


  // Body:

  bool result = 
    (_row_dofs.components[0] <= xother._row_dofs.components[0]) &&
    (_row_dofs.components[1] <= xother._row_dofs.components[1]) &&
    (_row_dofs.components[2] <= xother._row_dofs.components[2]);
  

  // Postconditions:

  ensure(result == (((*this)[0] <= xother[0]) && ((*this)[1] <= xother[1]) && ((*this)[2] <= xother[2])));

  // Exit:

  // cout << "Leaving e3::c_le." << endl;
  return result;
}

bool
fiber_bundle::e3_lite::
c_gt(const e3_lite& xother) const
{
  // cout << endl << "Entering e3::c_gt." << endl;

  // Preconditions:


  // Body:

  bool result = 
    (_row_dofs.components[0] > xother._row_dofs.components[0]) &&
    (_row_dofs.components[1] > xother._row_dofs.components[1]) &&
    (_row_dofs.components[2] > xother._row_dofs.components[2]);
  

  // Postconditions:

  ensure(result == (((*this)[0] > xother[0]) && ((*this)[1] > xother[1]) && ((*this)[2] > xother[2])));

  // Exit:

  // cout << "Leaving e3::c_gt." << endl;
  return result;
}

bool
fiber_bundle::e3_lite::
c_ge(const e3_lite& xother) const
{
  // cout << endl << "Entering e3::c_ge." << endl;

  // Preconditions:


  // Body:

  bool result = 
    (_row_dofs.components[0] >= xother._row_dofs.components[0]) &&
    (_row_dofs.components[1] >= xother._row_dofs.components[1]) &&
    (_row_dofs.components[2] >= xother._row_dofs.components[2]);
  

  // Postconditions:

  ensure(result == (((*this)[0] >= xother[0]) && ((*this)[1] >= xother[1]) && ((*this)[2] >= xother[2])));

  // Exit:

  // cout << "Leaving e3::c_ge." << endl;
  return result;
}

bool
fiber_bundle::e3_lite::
d_lt(const e3_lite& xother) const
{
  // cout << endl << "Entering e3::d_lt." << endl;

  // Preconditions:


  // Body:

  bool result = false;
  
  if(_row_dofs.components[0] < xother._row_dofs.components[0])
  {
    result = true;
  }
  else
  {
    if(_row_dofs.components[0] == xother._row_dofs.components[0])
    {
      if(_row_dofs.components[1] < xother._row_dofs.components[1])
      {
	result = true;
      }
      else
      {
	if(_row_dofs.components[1] == xother._row_dofs.components[1])
	{
	  if(_row_dofs.components[2] < xother._row_dofs.components[2])
	  {
	    result = true;
	  }
	}
      }
    }
  }    

  // Postconditions:


  // Exit:

  // cout << "Leaving e3::d_lt." << endl;
  return result;
}

bool
fiber_bundle::e3_lite::
d_le(const e3_lite& xother) const
{
  // cout << endl << "Entering e3::d_le." << endl;

  // Preconditions:


  // Body:

  bool result = false;
  
  if(_row_dofs.components[0] < xother._row_dofs.components[0])
  {
    result = true;
  }
  else
  {
    if(_row_dofs.components[0] == xother._row_dofs.components[0])
    {
      if(_row_dofs.components[1] < xother._row_dofs.components[1])
      {
	result = true;
      }
      else
      {
	if(_row_dofs.components[1] == xother._row_dofs.components[1])
	{
	  if(_row_dofs.components[2] < xother._row_dofs.components[2])
	  {
	    result = true;
	  }
	  else
	  {
	    if(_row_dofs.components[2] == xother._row_dofs.components[2])
	    {
	      result = true;
	    }
	  }
	}
      }
    }
  }    

  // Postconditions:


  // Exit:

  // cout << "Leaving e3::d_le." << endl;
  return result;
}

bool
fiber_bundle::e3_lite::
d_gt(const e3_lite& xother) const
{
  // cout << endl << "Entering e3::d_lt." << endl;

  // Preconditions:


  // Body:

  bool result = false;
  
  if(_row_dofs.components[0] > xother._row_dofs.components[0])
  {
    result = true;
  }
  else
  {
    if(_row_dofs.components[0] == xother._row_dofs.components[0])
    {
      if(_row_dofs.components[1] > xother._row_dofs.components[1])
      {
	result = true;
      }
      else
      {
	if(_row_dofs.components[1] == xother._row_dofs.components[1])
	{
	  if(_row_dofs.components[2] > xother._row_dofs.components[2])
	  {
	    result = true;
	  }
	}
      }
    }
  }    

  // Postconditions:


  // Exit:

  // cout << "Leaving e3::d_gt." << endl;
  return result;
}

bool
fiber_bundle::e3_lite::
d_ge(const e3_lite& xother) const
{
  // cout << endl << "Entering e3::d_ge." << endl;

  // Preconditions:


  // Body:

  bool result = false;
  
  if(_row_dofs.components[0] > xother._row_dofs.components[0])
  {
    result = true;
  }
  else
  {
    if(_row_dofs.components[0] == xother._row_dofs.components[0])
    {
      if(_row_dofs.components[1] > xother._row_dofs.components[1])
      {
	result = true;
      }
      else
      {
	if(_row_dofs.components[1] == xother._row_dofs.components[1])
	{
	  if(_row_dofs.components[2] > xother._row_dofs.components[2])
	  {
	    result = true;
	  }
	  else
	  {
	    if(_row_dofs.components[2] == xother._row_dofs.components[2])
	    {
	      result = true;
	    }
	  }
	}
      }
    }
  }    

  // Postconditions:


  // Exit:

  // cout << "Leaving e3::d_ge." << endl;
  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::e3_lite::
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
fiber_bundle::e3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("e3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::e3_lite*
fiber_bundle::e3_lite::
clone() const
{
  e3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new e3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::e3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const e3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::e3_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(ed_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::e3_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::e3_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS E3
//==============================================================================


//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (E3) FACET OF CLASS E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::e3::
e3()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e3::
e3(const poset_state_handle* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

fiber_bundle::e3::
e3(const poset_state_handle* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

fiber_bundle::e3::
e3(const poset_state_handle* xhost, const string& xname)
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
  // ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());

}

fiber_bundle::e3::
e3(abstract_poset_member* xother)
{

  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));

  // Exit:

}

fiber_bundle::e3::
e3(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::e3::
e3(poset_state_handle& xhost,
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

fiber_bundle::e3&
fiber_bundle::e3::
operator=(const row_dofs_type& xrdt)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  sheaf::row_dofs(*this) = xrdt;
  
  // Postconditions:

  ensure_for_all(i, 0, d(), component(i) == xrdt.components[i]);

  // Exit:

  return *this;

}

///
fiber_bundle::e3&
fiber_bundle::e3::
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
fiber_bundle::e3&
fiber_bundle::e3::
operator=(const e3& xother)
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

fiber_bundle::e3::
~e3()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::e3::volatile_type&
fiber_bundle::e3::
lite_prototype() const
{
  // Preconditions:

  // Body:

  static const volatile_type result;

  // Postconditions:

  // Exit:

  return result;
}

///
fiber_bundle::e3::volatile_type*
fiber_bundle::e3::
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
// EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (AT1) FACET OF CLASS E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::e3::
put_components(dof_type xcomp, dof_type ycomp, dof_type zcomp)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, xcomp);
  put_component(1, ycomp);
  put_component(2, zcomp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xcomp));
  ensure(isunordered_or_equals(component(1), ycomp));
  ensure(isunordered_or_equals(component(2), zcomp));

  // Exit:

  return;
}

fiber_bundle::e3::
operator e3::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::e3::
operator const e3::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::e3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "e3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::e3::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "x DOUBLE false ";
  lmember_names       += "y DOUBLE false ";
  lmember_names       += "z DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              ed::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::tp*
fiber_bundle::e3::
new_tp(tp_space& xvector_space, int xp)
{
  // Preconditions:

  require(xvector_space.state_is_read_accessible());
  require((0 <= xp) && (xp <= 4));

  // Body:

  //============================================================================

  namespace_poset* lns = xvector_space.name_space();
  const string& lvector_space_name = xvector_space.name();

  switch(xp)
  {
    case 0:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "at0");
	at0::host_type& lhost = lns->member_poset<at0::host_type>(lname, false);
        at0* result = new at0(&lhost);
        return result;
      }

    case 1:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "e3");
	e3::host_type& lhost = lns->member_poset<e3::host_type>(lname, false);
        e3* result = new e3(&lhost);
        return result;
      }

    case 2:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "t2_e3");
	t2_e3::host_type& lhost = lns->member_poset<t2_e3::host_type>(lname, false);
        t2_e3* result = new t2_e3(&lhost);
        return result;
      }

    case 3:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "t3_e3");
	t3_e3::host_type& lhost = lns->member_poset<t3_e3::host_type>(lname, false);
        t3_e3* result = new t3_e3(&lhost);
        return result;
      }

    case 4:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "t4_e3");
	t4_e3::host_type& lhost = lns->member_poset<t4_e3::host_type>(lname, false);
        t4_e3* result = new t4_e3(&lhost);
        return result;
      }

    default:
      // Can't get here because of the precondition.
      return 0;

  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

fiber_bundle::atp*
fiber_bundle::e3::
new_atp(tp_space& xvector_space, int xp)
{
  // Preconditions:

  require(xvector_space.state_is_read_accessible());
  require((0 <= xp) && (xp <= 3));

  // Body:

  namespace_poset* lns = xvector_space.name_space();
  const string& lvector_space_name = xvector_space.name();

  switch(xp)
  {
    case 0:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "at0");
	at0::host_type& lhost = lns->member_poset<at0::host_type>(lname, false);
        at0* result = new at0(&lhost);
        return result;
      }

    case 1:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "e3");
	e3::host_type& lhost = lns->member_poset<e3::host_type>(lname, false);
        e3* result = new e3(&lhost);
        return result;
      }

    case 2:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "at2_e3");
	at2_e3::host_type& lhost = lns->member_poset<at2_e3::host_type>(lname, false);
        at2_e3* result = new at2_e3(&lhost);
        return result;
      }

    case 3:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "at3_e3");
	at3_e3::host_type& lhost = lns->member_poset<at3_e3::host_type>(lname, false);
        at3_e3* result = new at3_e3(&lhost);
        return result;
      }

    default:
      // Can't get here because of the precondition.
      return 0;
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}


fiber_bundle::stp*
fiber_bundle::e3::
new_stp(tp_space& xvector_space, int xp)
{
  // Preconditions:

  require(xvector_space.state_is_read_accessible());
  require((2 <= xp) && (xp <= 4));

  // Body:

  namespace_poset* lns = xvector_space.name_space();
  const string& lvector_space_name = xvector_space.name();

  switch(xp)
  {
    case 2:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "st2_e3");
        st2_e3::host_type& lhost = lns->member_poset<st2_e3::host_type>(lname, false);
        st2_e3* result = new st2_e3(&lhost);
        return result;
      }

    case 3:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "st3_e3");
        st3_e3::host_type& lhost = lns->member_poset<st3_e3::host_type>(lname, false);
        st3_e3* result = new st3_e3(&lhost);
        return result;
      }

    case 4:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "st4_e3");
        st4_e3::host_type& lhost = lns->member_poset<st4_e3::host_type>(lname, false);
        st4_e3* result = new st4_e3(&lhost);
        return result;
      }

    default:
      // Can't get here because of the precondition.
      return 0;

  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

fiber_bundle::tp*
fiber_bundle::e3::
new_tp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_tp(vector_space(xauto_access), xp)));

  // Body:

  tp* result = e3::new_tp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_tp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::atp*
fiber_bundle::e3::
new_atp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_atp(vector_space(xauto_access), xp)));

  // Body:

  atp* result = e3::new_atp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_atp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::stp*
fiber_bundle::e3::
new_stp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_stp(vector_space(xauto_access), xp)));

  // Body:

  stp* result = e3::new_stp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_stp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::e3::
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
fiber_bundle::e3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("e3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::e3*
fiber_bundle::e3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  e3* result = new e3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::e3::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const e3*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::e3::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(ed::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance((is_attached() ? d() == 3 : true));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

size_t
fiber_bundle::
deep_size(const e3_lite& x0, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}

//==============================================================================
// E3 FACET:
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

void 
SHEAF_DLL_SPEC
fiber_bundle::e3_algebra::
cross(const e3& x0, const e3& x1, e3& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.d(xauto_access) >= xresult.d(xauto_access));
  require(x1.d(xauto_access) >= xresult.d(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Body:

  vd_value_type a0 = x0.component(0);
  vd_value_type a1 = x0.component(1);
  vd_value_type a2 = x0.component(2);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);
  vd_value_type b2 = x1.component(2);

  xresult.put_component(0, a1*b2 - a2*b1);
  xresult.put_component(1, a2*b0 - a0*b2);
  xresult.put_component(2, a0*b1 - a1*b0);

  // Set the variance of the result.

  x0.is_p_form(false) ? xresult.put_is_p_form(false) 
                      : xresult.put_is_p_vector(false);

  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));
  ensure(unexecutable("result == x0 cross x1"));

  // Exit:
}

void
SHEAF_DLL_SPEC
fiber_bundle::e3_algebra::
cross_equal(e3& xresult, const e3& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(cross(xresult, xother, xresult, xauto_access)));

  // Body:

  cross(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(cross(xresult, xother, xresult, xauto_access)));

  // Exit:
}


fiber_bundle::e3_lite*
fiber_bundle::e3_algebra::
cross(const e3_lite& x0, const e3_lite& x1)
{
  // Preconditions:

  // Body:

  e3_lite* result = x0.clone();
  cross(x0, x1, *result);

  // Postconditions:

  // Exit:

  return result;
}

void
SHEAF_DLL_SPEC
fiber_bundle::e3_algebra::
cross(const e3_lite& x0, const e3_lite& x1, e3_lite& xresult)
{
  // Preconditions:

  // Body:

  vd_value_type a0 = x0.component(0);
  vd_value_type a1 = x0.component(1);
  vd_value_type a2 = x0.component(2);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);
  vd_value_type b2 = x1.component(2);

  xresult.put_component(0, a1*b2 - a2*b1);
  xresult.put_component(1, a2*b0 - a0*b2);
  xresult.put_component(2, a0*b1 - a1*b0);

  // Postconditions:

  // Exit:
}

void
fiber_bundle::e3_algebra::
cross_equal(e3_lite& xresult, const e3_lite& xother)
{
  // Preconditions:

  // Body:

  e3_lite x0 = xresult;
  cross(x0, xother, xresult);

  // Postconditions:

  // Exit:
}

fiber_bundle::e3_lite*
fiber_bundle::e3_algebra::
operator^(const e3_lite& x0, const e3_lite& x1)
{
  // Preconditions:

  // Body:

  e3_lite* result = cross(x0, x1);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::e3_lite&
fiber_bundle::e3_algebra::
operator^=(e3_lite& xresult, const e3_lite& xother)
{
  // Preconditions:

  // Body:

  cross_equal(xresult, xother);

  // Postconditions:

  // Exit:

  return xresult;
}

void
fiber_bundle::vd_algebra::
transform_basis_by(e3_lite& xv, const gl3_lite& xtransform, bool is_contravariant)
{

  // Preconditions:

  require(xtransform.n() == xv.d());

  // Body:

  ///@todo Reimplement using the matrix operations on the row_dofs_type.

  ///@todo Clean up the comments.

  // Notation:
  //
  // Let the current basis be f-hat, considered as a row of vectors
  // with f-hat[i] the i-th basis vector. Similary, let e-hat be the
  // new basis. Let B be the matrix of the transform xtransform,
  // defined such that the i-th column, B[*][i] contains
  // the components of e-hat[i] with respect to f-hat.
  //
  // Given a covector V, let the components w.r.t. f-hat be represented
  // by a column vector, denoted Vf[k], where k is a row index.
  // Then the components w.r.t. e-hat are given by:
  //
  // Ve[m] = sum k{ B[k][m]*Vf[k] }
  //
  // For a (contravariant) vector, the transform is:
  //
  // Ve[m] = sum k{ C[m][k]*Vf[k] }
  //
  // where C is the inverse of B.

  // Get the row dof tuple

   e3_lite::value_type Ve[3];

  // Get the transform matrix

  /// @issue its annoying that we have to implement the
  /// co- and contra-variant cases entirely separately.
  /// A more general implementation based on the notion
  /// of inner products of i-th row with j-th column (or row)
  /// would be better.

  //@todo Fix this when we can handle the variance.

  if(!is_contravariant)
  {
    // Covariant case.

    const gl3_lite::matrix_type& B = xtransform.basis_matrix();

    // Transform the components.

    for(int m=0; m<3; ++m)
    {
      Ve[m] = 0;
      for(int k=0; k<3; ++k)
      {
        Ve[m] += B[k][m]*xv[k];
      }
    }
  }
  else
  {
    // Contravariant case

    const gl3_lite::matrix_type& C = xtransform.component_matrix();

    // Transform the components.

    for(int m=0; m<3; ++m)
    {
      Ve[m] = 0;
      for(int k=0; k<3; ++k)
      {
        Ve[m] += C[m][k]*xv[k];
      }
    }
  }

  // Transfer the transformed components back onto the dof tuple.

  for(int i=0; i<3; ++i)
  {
    xv[i] = Ve[i];
  }

  // Postconditions:

  // Exit:

}


void
fiber_bundle::vd_algebra::
add(const e3_lite& x0, const e3_lite& x1, vd_value_type xt, e3_lite& xresult)
{
  // Preconditions:

  require(x0.d() >= xresult.d());
  require(x1.d() >= xresult.d());

  // Body:

  vd_value_type lone_minus_t = 1.0 - xt;

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;
  e3_lite::row_dofs_type& lresult = xresult;

  lresult.components[0] = lx0.components[0]*lone_minus_t + lx1.components[0]*xt;
  lresult.components[1] = lx0.components[1]*lone_minus_t + lx1.components[1]*xt;
  lresult.components[2] = lx0.components[2]*lone_minus_t + lx1.components[2]*xt;

  // Postconditions:

  ensure(unexecutable("for_all: i, 0, xresult.d(), \
    xresult.component(i) == old_x0.component(i)*(1.0 - xt) + old_x1.component(i)*xt"));

  // Exit:

}

// ===========================================================
// VECTOR ALGEBRA: TOLERANCE COMPARISON
// ===========================================================



bool 
fiber_bundle::vd_algebra::
a_eql(const e3_lite& x0, const e3_lite& x1)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;

  bool result =
    sheaf::a_eql(lx0.components[0], lx1.components[0], double_tolerance) &&
    sheaf::a_eql(lx0.components[1], lx1.components[1], double_tolerance) &&
    sheaf::a_eql(lx0.components[2], lx1.components[2], double_tolerance);

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
a_eql(const e3_lite& x0, const e3_lite& x1, double xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;

  bool result =
    sheaf::a_eql(lx0.components[0], lx1.components[0], xtolerance) &&
    sheaf::a_eql(lx0.components[1], lx1.components[1], xtolerance) &&
    sheaf::a_eql(lx0.components[2], lx1.components[2], xtolerance);

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
a_eql(const e3_lite& x0, const e3_lite& x1, const e3_lite& xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;
  const e3_lite::row_dofs_type& lt = xtolerance;

  bool result =
    sheaf::a_eql(lx0.components[0], lx1.components[0], lt[0]) &&
    sheaf::a_eql(lx0.components[1], lx1.components[1], lt[1]) &&
    sheaf::a_eql(lx0.components[2], lx1.components[2], lt[2]);

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
r_eql(const e3_lite& x0, const e3_lite& x1)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;

  bool result =
    sheaf::r_eql(lx0.components[0], lx1.components[0], double_tolerance) &&
    sheaf::r_eql(lx0.components[1], lx1.components[1], double_tolerance) &&
    sheaf::r_eql(lx0.components[2], lx1.components[2], double_tolerance);

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
r_eql(const e3_lite& x0, const e3_lite& x1, double xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;

  bool result =
    sheaf::r_eql(lx0.components[0], lx1.components[0], xtolerance) &&
    sheaf::r_eql(lx0.components[1], lx1.components[1], xtolerance) &&
    sheaf::r_eql(lx0.components[2], lx1.components[2], xtolerance);

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
r_eql(const e3_lite& x0, const e3_lite& x1, const e3_lite& xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;
  const e3_lite::row_dofs_type& lt = xtolerance;

  bool result =
    sheaf::r_eql(lx0.components[0], lx1.components[0], lt[0]) &&
    sheaf::r_eql(lx0.components[1], lx1.components[1], lt[1]) &&
    sheaf::r_eql(lx0.components[2], lx1.components[2], lt[2]);

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
c_eql(const e3_lite& x0, const e3_lite& x1)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;

  bool result =
    sheaf::c_eql(lx0.components[0], lx1.components[0], double_tolerance) &&
    sheaf::c_eql(lx0.components[1], lx1.components[1], double_tolerance) &&
    sheaf::c_eql(lx0.components[2], lx1.components[2], double_tolerance);

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
c_eql(const e3_lite& x0, const e3_lite& x1, double xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;

  bool result =
    sheaf::c_eql(lx0.components[0], lx1.components[0], xtolerance) &&
    sheaf::c_eql(lx0.components[1], lx1.components[1], xtolerance) &&
    sheaf::c_eql(lx0.components[2], lx1.components[2], xtolerance);

  // Postconditions:

  // Exit:

  return result;
};

bool 
fiber_bundle::vd_algebra::
c_eql(const e3_lite& x0, const e3_lite& x1, const e3_lite& xtolerance)
{
  // Preconditions:

  require(x0.d() == x1.d());

  // Body:

  const e3_lite::row_dofs_type& lx0 = x0;
  const e3_lite::row_dofs_type& lx1 = x1;
  const e3_lite::row_dofs_type& lt = xtolerance;

  bool result =
    sheaf::c_eql(lx0.components[0], lx1.components[0], lt[0]) &&
    sheaf::c_eql(lx0.components[1], lx1.components[1], lt[1]) &&
    sheaf::c_eql(lx0.components[2], lx1.components[2], lt[2]);

  // Postconditions:

  // Exit:

  return result;
};

