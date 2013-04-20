

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class zone_partition

#include "zone_partition.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "std_sstream.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// ZONE_PARTITION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::zone_partition::
zone_partition(const string& xname, size_type xct)
{
  
  // Preconditions:

  require(!xname.empty());
  require(xct > 0);
    
  // Body:
  
  _name = xname;
  _ct = xct;
  _part_names.reserve(xct);
  _part_names.set_ct(xct);

  _has_zone_id_spaces = false;
  

  // Postconditions:

  ensure(invariant());
  ensure(ct() == xct);
  ensure_for_all(i, 0, xct, part_name(i).empty());
  ensure(!has_zone_id_spaces());
  

  // Exit:

  return; 
}

fiber_bundle::zone_partition::
~zone_partition()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

const string&
fiber_bundle::zone_partition::
name() const
{
  // Preconditions:


  // Body:

  const string& result = _name;

  // Postconditions:

  ensure(!result.empty());
  
  // Exit:

  return result;
}


sheaf::size_type
fiber_bundle::zone_partition::
ct() const
{
  return _ct;
}

const string&
fiber_bundle::zone_partition::
part_name(size_type xi) const
{
  // Preconditions:

  require((0 <= xi) && (xi < ct()));
  

  // Body:

  const string& result = _part_names[xi];

  // Postconditions:


  // Exit:

  return result;
}

void
fiber_bundle::zone_partition::
put_part_name(size_type xi, const string& xname)
{
  // Preconditions:

  require((0 <= xi) && (xi < ct()));

  // Body:

  _part_names[xi] = xname;

  // Postconditions:

  ensure(part_name(xi) == xname);
  
  // Exit:

  return;
}

void
fiber_bundle::zone_partition::
put_part_names(const string& xprefix)
{
  // Preconditions:

  require(!xprefix.empty());

  // Body:

  for(size_type i=0; i<_ct; ++i)
  {
    stringstream lstrm;
    lstrm << i;

    _part_names[i] = xprefix + "_" + lstrm.str();
  }

  // Postconditions:

  // Exit:

  return;
}

bool
fiber_bundle::zone_partition::
all_parts_named() const
{
  // Preconditions:


  // Body:

  bool result = true;
  for(size_type i=0; result && (i<_ct); ++i)
  {
    result = result && !_part_names[i].empty();
  }
  
  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::zone_partition::
has_zone_id_spaces() const
{
  return _has_zone_id_spaces;
}

void
fiber_bundle::zone_partition::
put_has_zone_id_spaces(bool xvalue)
{
  // Preconditions:

  require(xvalue ? all_parts_named() : true);
  
  // Body:

  _has_zone_id_spaces = xvalue;

  // Postconditions:

  ensure(has_zone_id_spaces() == xvalue);
  
  // Exit:

  return;
}


sheaf::cover_set_iterator
fiber_bundle::zone_partition::
part_zones(size_type xi) const
{
  // Preconditions:

  require((0 <= xi) && (xi < ct()));

  // Body:

  cover_set_iterator result;

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS


// PRIVATE MEMBER FUNCTIONS

fiber_bundle::zone_partition::
zone_partition()
{
  
  // Preconditions:

    
  // Body:
  
  not_implemented();
  
  // Postconditions:

  ensure(invariant());
  ensure(ct() == 0);

  // Exit:

  return; 
}

fiber_bundle::zone_partition::
zone_partition(const zone_partition& xother)
{
  
  // Preconditions:

    
  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::zone_partition::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const zone_partition*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::zone_partition*
fiber_bundle::zone_partition::
clone() const
{
  zone_partition* result = 0;
  
  // Preconditions:

  // Body:
  
  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
fiber_bundle::zone_partition::
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

    invariance(!name().empty());
    invariance(ct() > 0);

    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}

fiber_bundle::zone_partition&
fiber_bundle::zone_partition::
operator=(const zone_partition& xother)
{
  
  // Preconditions:

    
  // Body:
  
  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit
  
  return *this;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
