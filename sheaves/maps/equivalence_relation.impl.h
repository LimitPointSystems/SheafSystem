// $RCSfile: equivalence_relation.impl.h,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:40 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class equivalence_relation

#ifndef EQUIVALENCE_RELATION_IMPL_H
#define EQUIVALENCE_RELATION_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EQUIVALENCE_RELATION_H
#include "equivalence_relation.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif


namespace sheaf
{
  
// ===========================================================
// ANY FACET
// ===========================================================

template <typename T>
equivalence_relation<T>*
equivalence_relation<T>::
clone() const
{
  equivalence_relation* result;

  // Preconditions:

  // Body:

  result = new equivalence_relation();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
};

template <typename T>
equivalence_relation<T>&
equivalence_relation<T>::
operator=(const equivalence_relation& xother)
{

  // Preconditions:


  // Body:

  _mbr_to_rep = xother._mbr_to_rep;
  _rep_to_mbr = xother._rep_to_mbr;


  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
};

template <typename T>
bool
equivalence_relation<T>::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
};

template <typename T>
bool
equivalence_relation<T>::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const equivalence_relation<T>*>(other) != 0;

  // Postconditions:

  return result;
};

// ===========================================================
// EQUIVALENCE_RELATION FACET
// ===========================================================

template <typename T>
equivalence_relation<T>::
equivalence_relation()
{
  // Preconditions:


  // Body:

  // No action required.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
};

template <typename T>
equivalence_relation<T>::
equivalence_relation(const equivalence_relation& xother)
{

  // Preconditions:


  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
};

template <typename T>
equivalence_relation<T>::
~equivalence_relation()
{

  // Preconditions:


  // Body:

  // No action required.


  // Postconditions:

  // Exit:

  return;
};


template <typename T>
bool
equivalence_relation<T>::
contains_representative(const T& xmbr_id) const
{
  bool result;

  // Preconditions:


  // Body:

  result = (xmbr_id == representative(xmbr_id));

  // Postconditions:

  ensure(result == (xmbr_id == representative(xmbr_id)));

  // Exit:

  return result;
};


template <typename T>
bool
equivalence_relation<T>::
contains_unique_representative(const T& xrep_id) const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_rep_to_mbr.find(xrep_id) == _rep_to_mbr.end());
  result = result && (_mbr_to_rep.find(xrep_id) == _mbr_to_rep.end());

  // Postconditions:

  ensure(result ? contains_representative(xrep_id) : true);

  // Exit:

  return result;
};


template <typename T>
bool
equivalence_relation<T>::
contains_equivalence(const T& xmbr_id, const T& xother_mbr_id) const
{
  bool result;

  // Preconditions:


  // Body:

  result = (representative(xmbr_id) == representative(xother_mbr_id));

  // Postconditions:

  ensure(result == (representative(xmbr_id) == representative(xother_mbr_id)));

  // Exit:

  return result;
};

template <typename T>
void
equivalence_relation<T>::
insert_equivalence(const T& xmbr_id, const T& xrep_id)
{
  // Preconditions:

  require(contains_unique_representative(xmbr_id));
  require(contains_representative(xrep_id));
  require(!contains_equivalence(xmbr_id, xrep_id));

  // Body

  // Insert the mbr to rep entry.

  typename mbr_to_rep_type::value_type lmbr_entry(xmbr_id, xrep_id);
  _mbr_to_rep.insert(lmbr_entry);

  // Insert the rep to mbr entry.

  typename rep_to_mbr_type::value_type lrep_entry(xrep_id, xmbr_id);
  _rep_to_mbr.insert(lrep_entry);

  // Postconditions:

  ensure(contains_equivalence(xmbr_id, xrep_id));
  ensure(representative(xmbr_id) == xrep_id);

  // Exit:

  return;
};


template <typename T>
void
equivalence_relation<T>::
delete_equivalence(const T& xmbr_id)
{
  // Preconditions:

  require(!contains_representative(xmbr_id));

  // Body:

  // Look up the entry in the mbr to rep map.

  typename mbr_to_rep_type::iterator mbr_itr = _mbr_to_rep.find(xmbr_id);

  if(mbr_itr != _mbr_to_rep.end())
  {
    // This contains the member xmbr_id;
    // get its rep id and erase the entry from the mbr to rep map.

    T lrep_id = mbr_itr->second;
    _mbr_to_rep.erase(mbr_itr);

    // Delete the entry from the rep to mbrs map.

    typedef typename rep_to_mbr_type::iterator rep_itr_type;

    pair<rep_itr_type, rep_itr_type> lrange = _rep_to_mbr.equal_range(lrep_id);
    for(rep_itr_type rep_itr = lrange.first; rep_itr != lrange.second; rep_itr++)
    {
      if(rep_itr->second == xmbr_id)
      {
        _rep_to_mbr.erase(rep_itr);
        break;
      }
    }
  }

  // Postconditions:

  ensure(contains_unique_representative(xmbr_id));

  // Exit:

  return;
};


template <typename T>
T
equivalence_relation<T>::
representative(const T& xmbr_id) const
{
  T result;

  // Preconditions:

  // Body:

  typename mbr_to_rep_type::const_iterator itr = _mbr_to_rep.find(xmbr_id);
  if(itr != _mbr_to_rep.end())
  {
    // Mbr to rep map contains result.

    result = itr->second;
  }
  else
  {
    // Mbr is its own representative.

    result = xmbr_id;
  }

  // Postconditions:

  // Exit:

  return result;
}


template <typename T>
typename equivalence_relation<T>::range_type
equivalence_relation<T>::
equivalence_class(const T& xrep_id) const
{
  range_type result;

  // Preconditions:

  require(contains_representative(xrep_id));

  // Body:

  result = _rep_to_mbr.equal_range(xrep_id);

  // Postconditions:

  ensure((result.first == result.second) == contains_unique_representative(xrep_id));

  // Exit:

  return result;
};

template <typename T>
typename equivalence_relation<T>::range_type
equivalence_relation<T>::
all_equivalences() const
{
  range_type result;

  // Preconditions:

  // Body:

  result.first  = _rep_to_mbr.begin();
  result.second = _rep_to_mbr.end();

  // Postconditions:

  // Exit:

  return result;
};


// =============================================================================
// NONMEMBER FUNCTIONS
// =============================================================================


template <typename T>
ostream& operator<<(ostream& xos, const equivalence_relation<T>& xer)
{

  typename equivalence_relation<T>::rep_to_mbr_type::const_iterator itr;

  T previous_id;

  itr = xer._rep_to_mbr.begin();
  if(itr != xer._rep_to_mbr.end())
  {
    xos << itr->first << "\t" << itr->second;
    previous_id = itr->first;
    ++itr;
  }

  while(itr != xer._rep_to_mbr.end())
  {
    if(itr->first != previous_id)
    {
      xos << endl << itr->first;
    }
    xos << "\t" << itr->second;

    previous_id = itr->first;
    ++itr;
  }

  return xos;
}

template <typename T>
ostream& operator<<(ostream& xos, const typename equivalence_relation<T>::range_type& xrange)
{

  typename equivalence_relation<T>::iterator_type itr;

  for(itr = xrange.first; itr != xrange.second; itr++)
  {
    xos << itr->first << '\t' << itr->second << endl;
  }

  return xos;
}

} // namespace sheaf

#endif // ifndef EQUIVALENCE_RELATION_IMPL_H
