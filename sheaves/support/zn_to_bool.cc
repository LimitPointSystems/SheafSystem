
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

// Implementation for class ZN_TO_BOOL


#include "zn_to_bool.h"
#include "assert_contract.h"
#include "block.h"
#include "error_message.h"
#include "std_iomanip.h"

using namespace std;

// ===========================================================
// ZN_TO_BOOL FACET
// ===========================================================
 
///
bool
sheaf::zn_to_bool::
invariant() const
{
  bool result = true;

  // Positive upper bound.

  invariance(ub() >= 0);

  // Ct and ub are synonomous in this class.

  invariance(ct() == ub());

  return result;
}

///
sheaf::zn_to_bool::
zn_to_bool()
{
  // Preconditions:


  // Body:

  _ub      = 0;
  _word_ub = 0;
  _values  = 0;
  _values_ub = 0;
  
  // Postconditions:

  ensure(ub() == 0);

  // Exit:

  return;
}


///
sheaf::zn_to_bool::
zn_to_bool(const zn_to_bool& xother)
{

  // Preconditions:

  // Body:

  _ub = xother._ub;
  _word_ub = xother._word_ub;
  _values_ub = xother._values_ub;

  if(_values_ub > 0)
  {
    _values = new word_t[_values_ub];
  }
  else
  {
    _values = 0;
  }

  const_cast<zn_to_bool&>(xother).equal_pa(this);

  // Postconditions:

  ensure(invariant());
  ensure(is_equal_to(&xother));

}


///
sheaf::zn_to_bool::
zn_to_bool(int xub, bool xinitialize)
{

  // Preconditions:

  require(xub >= 0);

  // Body:

  _ub = xub;

  _word_ub = (_ub+BITS_PER_WORD-1)/BITS_PER_WORD;
  _values_ub = _word_ub;
  
  _values = _values_ub > 0 ? new word_t[_values_ub] : 0;

  if(xub > 0 && xinitialize)
  {
    // initialize to false

    make_false_sa();
  }

  // postconditions:

  ensure(invariant());
  ensure((xub > 0 && xinitialize) ? is_false() : true);

}

///
sheaf::zn_to_bool::
zn_to_bool(int xub, unsigned* values)
{

  // preconditions:

  require(xub > 0);
  require(values != 0);  /// @hack an implicit assumption that values points to xub unsigned ints

  // body:

  _ub = xub;

  _word_ub = (_ub+BITS_PER_WORD-1)/BITS_PER_WORD;
  _values_ub = _word_ub;

  _values = new word_t[_values_ub];

  if (_values != 0)
  {
    // bit storage created successfully; initialize
    for (int i = 0; i < _values_ub; ++i)
      _values[i] = values[i];
  }

  // postconditions:

  ensure(invariant());

}


///
sheaf::zn_to_bool::
~zn_to_bool()
{
  if(_values != 0)
  {
    delete [] _values;
  }

}

// ===========================================================
// DOMAIN FACET
// ===========================================================

 
 
///
bool
sheaf::zn_to_bool::
domain_is_valid() const
{
  bool result;

  // Preconditions:

  // Body:

  result = _values != 0;

  // Postconditions:

  // Exit

  return(result);
}

 

///
int
sheaf::zn_to_bool::
ub() const
{

  // body:

  int result = _ub;

  // postconditions:

  ensure(result >= 0);

  return result;
}

 

///
bool
sheaf::zn_to_bool::
index_in_bounds(int i) const
{
  bool result;

  // Preconditions:

  // Body:

  result = (0 <= i) && (i < _ub);

  // Postconditions:

  ensure( result == ((0 <= i) && (i < ub())) );

  // Exit

  return result;
}

 

///
bool
sheaf::zn_to_bool::
index_in_bounds(const block<int>* indices) const
{
  bool result = true;
  int i = 0;

  // Preconditions:

  // Body:

  while( (i<indices->ct()) && result)
  {
    result = index_in_bounds((*indices)[i]);
    i++;
  }


  // Postconditions:

  // postcondition: for all i in indices: index_in_bounds(i)

  // Exit

  return result;
}

 

///
int
sheaf::zn_to_bool::
ct() const
{

  // body:

  int result = _ub;

  // postconditions:

  ensure(result >= 0);

  return result;
}

 

///
int
sheaf::zn_to_bool::
true_ct() const
{
  int     result   = 0;
  int     j        = 0;
  word_t* word_ptr = _values;
  word_t  mask     = 1;


  // body:

  for(int i=0; i<_ub; i++)
  {
    if( *word_ptr & mask )
      result++;

    if(j < BITS_PER_WORD - 1)
    {
      j++;
      mask = mask << 1;
    }
    else
    {
      j = 0;
      mask = 1;
      word_ptr++;
    };
  }

  // postconditions:

  ensure(result >= 0);

  return result;
}

 

///
int
sheaf::zn_to_bool::
false_ct() const
{
  // body:

  int result = ct() - true_ct();

  // postconditions:

  ensure(result == ct() - true_ct());

  return result;
}

///
void
sheaf::zn_to_bool::
extend_to(int xub)
{
  // Preconditions:

  require(xub > 0);

  // Body:

  if (xub > ub())
  {

    // Calculate number of words needed.

    _word_ub = (xub + BITS_PER_WORD -1)/BITS_PER_WORD;

    if(_word_ub > _values_ub)
    {
      // We need to allocate more storage.
      // Need to at least double in order to keep
      // amortized cost of copying linear.

      int new_values_ub = (_word_ub > 2*_values_ub) ? _word_ub : 2*_values_ub;

      // Try to allocate new storage

      word_t* new_values = new word_t[new_values_ub];

      if(new_values != 0)
      {
        // allocation succeeded; copy data to new storage

        for(int i=0; i<_values_ub; i++)
        {
          *(new_values+i) = *(_values+i);
        }

        // initialize remainder of words to false

        for(int i=_values_ub; i<new_values_ub; i++)
        {
          *(new_values+i) = (word_t)0;
        }

        // deallocate old storage

        delete [] _values;

        // hook new storage into object

        _values = new_values;
        _values_ub = new_values_ub;
        
      } // end if new values
      else
      {
        // Failed to allocate.

        post_fatal_error_message("Unable to allocate memory.");
      }
    } // end if _word_ub
    
    assertion(_word_ub <= _values_ub);
    
    _ub = xub;
  
  } // end if xub > ub()
  else
  {
    // Do nothing
  }
  
  

  // Postconditions:

  ensure(invariant());
  ensure( ub() >= xub );

  // Exit

  return;
}

 

///
size_t
sheaf::zn_to_bool::
capacity() const
{
  size_t result;

  // Preconditions:


  // Body

  result = _values_ub*BITS_PER_WORD;

  // Postconditions:


  // Exit:

  return result;
}


// ===========================================================
// CHARACTERISTIC FUNCTION FACET
// ===========================================================

///
bool
sheaf::zn_to_bool::
is_true_for(const block<int>* indices) const
{
  bool result = true;

  // Preconditions:

  require(index_in_bounds(indices));

  // Body:

  int i = (*indices)[0];

  while( (i<indices->ct()) && result )
  {
    result = (*this)[(*indices)[i]] && result;
    i++;
  }


  // Postconditions:

  // Exit

  return result;
}


///
bool
sheaf::zn_to_bool::
is_false_for(const block<int>* indices) const
{
  bool result = true;

  // Preconditions:

  require(index_in_bounds(indices));

  // Body:

  int i = (*indices)[0];

  while( (i<indices->ct()) && result )
  {
    result = !((*this)[(*indices)[i]]) && result;
    i++;
  }


  // Postconditions:

  // Exit

  return result;
}


///
void
sheaf::zn_to_bool::
put(int xindex, bool val)
{

  // Preconditions:

  require(index_in_bounds(xindex));

  // Body:

  if (val)
  {
    // set value true
    get_word(xindex) |= get_mask(xindex);
  }
  else
  {
    // set value false

    get_word(xindex) &= ~get_mask(xindex);
  }

  // Postconditions:

  ensure(invariant());
  ensure((*this)[xindex] == val);

  // Exit

}

///
void
sheaf::zn_to_bool::
put(const block<int>* indices, bool val)
{

  // Preconditions:

  require(indices != 0);
  require( index_in_bounds(indices) );


  // Body:

  for(int i=0; i<indices->ct(); i++)
  {
    int j = (*indices)[i];
    if(val)
    {
      get_word(j) |= get_mask(j);
    }
    else
    {
      get_word(j) &= ~get_mask(j);
    };
  }

  // Postconditions:

  ensure(invariant());
  ensure(val ? is_true_for(indices) : is_false_for(indices));

  // Exit

}


///
void
sheaf::zn_to_bool::
force(int xindex, bool val)
{

  // Preconditions:

  require(xindex >= 0);

  // Body:

  if(xindex >= _ub)
  {
    int lnew_ub = (xindex < 2*_ub) ? 2*_ub : xindex+1;
    extend_to(lnew_ub);
  }

  assertion(_ub > xindex);

  put(xindex, val);

  // Postconditions:

  ensure(invariant());
  ensure((*this)[xindex] == val);

  // Exit

}


///
void
sheaf::zn_to_bool::
put_not(int xindex)
{

  // Preconditions:

  require(index_in_bounds(xindex));

  // Body:

  // set value true

  word_t& w = get_word(xindex);
  word_t  m = get_mask(xindex);

  w = get_word(xindex);
  m = get_mask(xindex);
  w = (w | m) & ~(w & m);

  // Postconditions:

  ensure(invariant());
  // ensure((*this)[xindex] != old (*this)[xindex]);

  // Exit

}


///
void
sheaf::zn_to_bool::
put_not(const block<int>* indices)
{

  // Preconditions:

  require(indices != 0);
  require( index_in_bounds(indices) );


  // Body:

  for(int i=0; i<indices->ct(); i++)
  {
    int j = (*indices)[i];
    word_t& w = get_word(j);
    word_t  m = get_mask(j);
    w = (w | m) & ~(w & m);
  }

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable("for all i in indices: (*this)[i] = ! old (*this)[i]"));

  // Exit

}

// ===========================================================
// BOOLEAN ALGEBRA FACET
// ===========================================================

 
 
///
bool
sheaf::zn_to_bool::
is_true() const
{
  bool result = true;
  int i = 0;


  // Preconditions:

  // Body:

  while( (i<_word_ub) && result )
  {
    result = ( *(_values + i) == ~(static_cast<word_t>(0)) );
    i++;
  }

  // Postconditions:

  // Exit

  return result;
}

 

///
bool
sheaf::zn_to_bool::
is_false() const
{
  bool result = true;
  int i = 0;


  // Preconditions:

  // Body:

  while( (i<_word_ub) && result )
  {
    result = ( *(_values + i) == static_cast<word_t>(0) );
    i++;
  }

  // Postconditions:

  // Exit

  return result;
}

 

///
bool
sheaf::zn_to_bool::
is_equal_to(const zn_to_bool* other) const
{
  bool result = true;
  int i = 0;


  // Preconditions

  require((other != 0) && (other->ub() == ub()));

  // Body:

  while( (i<_word_ub) && result )
  {
    result = ( *(_values + i) == *(other->_values +i) );
    i++;
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
sheaf::zn_to_bool::
operator==(const zn_to_bool& other) const
{
  bool result = true;
  int i = 0;


  // Preconditions

  require(other.ub() == ub());

  // Body:

  while( (i<_word_ub) && result )
  {
    result = ( *(_values + i) == *(other._values +i) );
    i++;
  }

  // Postconditions:

  // Exit

  return result;
}

 

///
bool
sheaf::zn_to_bool::
includes(const zn_to_bool* other) const
{
  bool result = true;
  int i = 0;


  // Preconditions

  require((other != 0) && (other->ub() == ub()));

  // Body:

  while( (i<_word_ub) && result )
  {
    word_t other_value = *(other->_values + i);
    result = ( ( (*(_values + i)) & other_value ) == other_value );
    i++;
  }

  // Postconditions:

  // Exit

  return result;
}

 

///
bool
sheaf::zn_to_bool::
is_not(const zn_to_bool* other) const
{
  bool result = true;
  int i = 0;


  // Preconditions

  require((other != 0) && (other->ub() == ub()));

  // Body:

  while( (i<_word_ub) && result )
  {
    result = ( *(_values + i) == ~(*(other->_values +i)) );
    i++;
  }

  // Postconditions:

  // Exit

  return result;
}

///
sheaf::zn_to_bool*
sheaf::zn_to_bool::
make_true()
{
  zn_to_bool* result;

  // Preconditions:

  // Body:

  result = new zn_to_bool(_ub);

  if(result != 0)
    result->make_true_sa();


  // Postconditions:

  ensure((result != 0) && result->invariant());
  ensure(result->is_true());

  // Exit

  return(result);
}

///
void
sheaf::zn_to_bool::
make_true_sa()
{
  // Preconditions:

  // Body:

  for(int i=0; i<_word_ub; i++)
  {
    *(_values+i) = ~((word_t)0);
  }

  // Postconditions:

  ensure(is_true());

  // Exit

  return;
}

///
sheaf::zn_to_bool*
sheaf::zn_to_bool::
make_false()
{
  zn_to_bool* result;

  // Preconditions:

  // Body:

  result = new zn_to_bool(_ub);

  // don't need to do more, constructor ensures false

  // Postconditions:

  ensure((result != 0) && result->invariant());
  ensure(result->is_false());

  // Exit

  return(result);
}

///
void
sheaf::zn_to_bool::
make_false_sa()
{
  // Preconditions:

  // Body:

  for(int i=0; i<_word_ub; i++)
  {
    *(_values+i) = (word_t)0;
  }

  // Postconditions:

  ensure(is_false());

  // Exit

  return;
}

///
sheaf::zn_to_bool*
sheaf::zn_to_bool::
equal()
{
  zn_to_bool* result;

  // Preconditions:

  // Body:

  result = new zn_to_bool(_ub);

  if(result != 0)
    equal_pa(result);


  // Postconditions:

  ensure((result != 0) && result->invariant());
  ensure(is_equal_to(result));

  // Exit

  return(result);
}

///
void
sheaf::zn_to_bool::
equal_pa(const zn_to_bool* result)
{
  // Preconditions:

  // Body:

  for(int i=0; i<_word_ub; i++)
  {
    *(result->_values+ i) = *(_values+i);
  }

  // Postconditions:

  ensure(is_equal_to(result));

  // Exit

  return;
}

///
sheaf::zn_to_bool&
sheaf::zn_to_bool::
operator=(const zn_to_bool& xother)
{
  // Preconditions:

  // Body:

  if(_values != 0)
  {
    delete _values;
  }

  _ub = xother._ub;
  _word_ub = xother._word_ub;
  _values = new word_t[_word_ub];

  for(int i=0; i<_word_ub; i++)
  {
    _values[i] = xother._values[i];
  }

  // Postconditions:

  ensure(*this == xother);

  // Exit

  return *this;
}

///
sheaf::zn_to_bool*
sheaf::zn_to_bool::
b_not()
{
  zn_to_bool* result;

  // Preconditions:

  // Body:

  result = new zn_to_bool(_ub);

  if(result != 0)
    b_not_pa(result);


  // Postconditions:

  ensure((result != 0) && result->invariant());
  ensure(is_not(result));

  // Exit

  return(result);
}

///
void
sheaf::zn_to_bool::
b_not_pa(const zn_to_bool* result)
{
  // Preconditions:

  // Body:

  for(int i=0; i<_word_ub; i++)
  {
    *(result->_values+ i) = ~(*(_values+i));
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::zn_to_bool::
b_not_sa()
{
  // Preconditions:

  // Body:

  b_not_pa(this);

  // Postconditions:

  // ensure(is_not(old this));

  // Exit

  return;
}

///
sheaf::zn_to_bool*
sheaf::zn_to_bool::
b_and(const zn_to_bool* other)
{
  zn_to_bool* result;

  // Preconditions:

  require((other != 0) && (other->ub() == ub()));

  // Body:

  result = new zn_to_bool(_ub);

  if(result != 0)
    b_and_pa(other, result);

  // Postconditions:

  ensure((result != 0) && result->invariant());

  // Exit

  return result;
}

///
void
sheaf::zn_to_bool::
b_and_pa(const zn_to_bool* other, zn_to_bool* result)
{

  // Preconditions:

  require((other != 0));
  require(result != 0);
  require(other->ub() == result->ub());

  // Body:

  for(int i=0; i<_word_ub; i++)
  {
    *(result->_values+i) = *(_values+i) & *(other->_values+i);
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::zn_to_bool::
b_and_sa(const zn_to_bool* other)
{

  // Preconditions:

  require((other != 0) && (other->ub() == ub()));

  // Body:

  b_and_pa(other, this);

  // Postconditions:

  // Exit

  return;
}

///
sheaf::zn_to_bool*
sheaf::zn_to_bool::
b_or(const zn_to_bool* other)
{
  zn_to_bool* result;

  // Preconditions:

  require((other != 0) && (other->ub() == ub()));

  // Body:

  result = new zn_to_bool(_ub);

  if(result != 0)
    b_or_pa(other, result);

  // Postconditions:

  ensure((result != 0) && result->invariant());

  // Exit

  return(result);
}

///
void
sheaf::zn_to_bool::
b_or_pa(const zn_to_bool* other, zn_to_bool* result)
{

  // Preconditions:

  require((other != 0));
  require(result != 0);
  require(other->ub() == result->ub());

  // Body:

  for(int i=0; i<_word_ub; i++)
  {
    *(result->_values+i) = *(_values+i) | *(other->_values+i);
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::zn_to_bool::
b_or_sa(const zn_to_bool* other)
{

  // Preconditions:

  require((other != 0) && (other->ub() == ub()));

  // Body:

  b_or_pa(other, this);

  // Postconditions:

  // Exit

  return;
}

///
sheaf::zn_to_bool*
sheaf::zn_to_bool::
b_and_not(const zn_to_bool* other)
{
  zn_to_bool* result;

  // Preconditions:

  require((other != 0) && (other->ub() == ub()));

  // Body:

  result = new zn_to_bool(_ub);

  if(result != 0)
    b_and_not_pa(other, result);

  // Postconditions:

  ensure((result != 0) && result->invariant());

  // Exit

  return result;
}

///
void
sheaf::zn_to_bool::
b_and_not_pa(const zn_to_bool* other, zn_to_bool* result)
{

  // Preconditions:

  require((other != 0));
  require(result != 0);
  require(other->ub() == result->ub());

  // Body:

  for(int i=0; i<_word_ub; i++)
  {
    *(result->_values+i) = *(_values+i) & ~(*(other->_values+i));
  }

  // Postconditions:

  // Exit

  return;
}

///
void
sheaf::zn_to_bool::
b_and_not_sa(const zn_to_bool* other)
{

  // Preconditions:

  require((other != 0) && (other->ub() == ub()));

  // Body:

  b_and_not_pa(other, this);

  // Postconditions:

  // Exit

  return;
}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
std::ostream& sheaf::operator << (std::ostream& xos, zn_to_bool& xzn)
{

  // Preconditions:

  // Body:

  int j = 0;
  zn_to_bool::word_t mask = 1;
  zn_to_bool::word_t* word_ptr = xzn._values;

  xos << endl << "word ub: " << xzn._word_ub << "; words:" << endl;
  int lwidth = 2*sizeof(zn_to_bool::word_t);
  char lfill_char = xos.fill('0');

  xos << hex;

  for (int i = 0; i < xzn._word_ub; ++i)
  {
    xos << setw(lwidth) << *(xzn._values+i) << endl;
  }

  xos << dec ;
  xos.fill(lfill_char);

  xos << endl << "bit ub: " << xzn.ub() << " bits: " << endl;

  for(int i=0; i < xzn.ub(); ++i)
  {
    if( *word_ptr & mask )
    {
      xos << '1';
    }
    else
    {
      xos << '0';
    };

    if(j < zn_to_bool::BITS_PER_WORD - 1)
    {
      ++j;
      mask = mask << 1;
    }
    else
    {
      j = 0;
      mask = 1;
      ++word_ptr;
    };

  }

  // Postconditions:

  // Exit:

  return xos;
}

///
size_t
sheaf::deep_size(const zn_to_bool& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  zn_to_bool& lxp = const_cast<zn_to_bool&>(xp);

  // Add the memory allocated for _values.

  if(lxp.values() != 0)
  {
    result += (lxp.word_ub())*sizeof(zn_to_bool::word_t);
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
