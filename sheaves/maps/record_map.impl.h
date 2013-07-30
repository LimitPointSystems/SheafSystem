

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
/// Implementation for class record_map

#ifndef RECORD_MAP_IMPL_H
#define RECORD_MAP_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef RECORD_MAP_H
#include "record_map.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef INDEX_TRAITS_H
#include "index_traits.h"
#endif

#ifndef STD_IOMANIP_H
#include "std_iomanip.h"
#endif

namespace sheaf
{
  
// ===========================================================
// RECORD_MAP FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template<typename internal_index_type, typename external_index_type>
record_map<internal_index_type, external_index_type>::
record_map()
{
  // Preconditions:

  // Body:

  _internal_ids_sequential = false;
  _external_ids_sequential = false;

  _scratch_internal_id = index_traits<internal_index_type>::invalid();
  _scratch_external_id = index_traits<external_index_type>::invalid();

  _internal_id_ub = index_traits<internal_index_type>::min();
  _external_id_ub = index_traits<external_index_type>::min();

  _entry_removed           = false;

  // Postconditions:

  ensure(invariant());
  ensure(!internal_ids_sequential());
  ensure(!external_ids_sequential());
  ensure(!index_traits< internal_index_type >::is_valid(scratch_internal_id()));
  ensure(!index_traits< external_index_type >::is_valid(scratch_external_id()));
  ensure(internal_id_ub() == index_traits<internal_index_type>::min());
  ensure(external_id_ub() == index_traits<external_index_type>::min());
  ensure(!ub_is_max());

  // Exit

  return;
}

template <typename internal_index_type, typename external_index_type>
record_map<internal_index_type, external_index_type>::
record_map(const record_map& xother)
{
  // Preconditions:

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable((*this) == xother));

  // Exit

  return;
}

template <typename internal_index_type, typename external_index_type>
record_map<internal_index_type, external_index_type>&
record_map<internal_index_type, external_index_type>::
operator=(const record_map& xother)
{
  // Preconditions:

  // Body:

  if(this != &xother)
  {
    record_map& lother = const_cast<record_map&>(xother);

    _to_external             = lother._to_external;
    _to_internal             = lother._to_internal;
    _internal_ids_sequential = lother._internal_ids_sequential;
    _external_ids_sequential = lother._external_ids_sequential;

    _scratch_internal_id     = lother._scratch_internal_id;
    _scratch_external_id     = lother._scratch_external_id;

    _internal_id_ub          = lother._internal_id_ub;
    _external_id_ub          = lother._external_id_ub;

    _entry_removed           = lother._entry_removed;
  }

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

template <typename internal_index_type, typename external_index_type>
record_map<internal_index_type, external_index_type>::
~record_map()
{
  // Preconditions:

  // Body:

  // Postconditions:

  return;
}

template <typename internal_index_type, typename external_index_type>
bool
record_map<internal_index_type, external_index_type>::
invariant() const
{
  bool result = true;

  // Internal and external maps always the same size.

  invariance(_to_internal.size() == _to_external.size());

  // Internal and external sequential ids are
  // mutually exclusive, but both can be false.

  invariance(_internal_ids_sequential ? !_external_ids_sequential : true);
  invariance(_external_ids_sequential ? !_internal_ids_sequential : true);

  // Definition of upper bounds.

  invariance(unexecutable("for all internal ids i: i <= internal_id_ub()"));
  invariance(unexecutable("ub_is_max() ? there exists entry (int_id, ext_id) such that int_id= internal_id_ub()"));
  invariance(unexecutable("for all external ids i: i <= external_id_ub()"));
  invariance(unexecutable("ub_is_max() ? there exists entry (int_id, ext_id) such that ext_id= external_id_ub()"));

  return result;
}

template <typename internal_index_type, typename external_index_type>
external_index_type
record_map<internal_index_type, external_index_type>::
external_id(internal_index_type xinternal_id) const
{
  // Preconditions:

  // Body:
  
  typename hash_map<internal_index_type, external_index_type>::const_iterator itr = _to_external.find(xinternal_id);
  external_index_type result =
    itr != _to_external.end() ? itr->second : index_traits<external_index_type>::invalid();

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}


template <typename internal_index_type, typename external_index_type>
internal_index_type
record_map<internal_index_type, external_index_type>::
internal_id(external_index_type xexternal_id) const
{
  // Preconditions:

  // Body:
  
  typename hash_map<external_index_type, internal_index_type>::const_iterator itr = _to_internal.find(xexternal_id);
  internal_index_type result =
    itr != _to_internal.end() ? itr->second : index_traits<internal_index_type>::invalid();

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

template <typename internal_index_type, typename external_index_type>
void
record_map<internal_index_type, external_index_type>::
put_ids(internal_index_type xinternal_id, external_index_type xexternal_id)
{
  // Preconditions:

  require(!is_empty() ? !internal_ids_sequential() && !external_ids_sequential() : true);
  require(!contains_internal_id(xinternal_id));
  require(!contains_external_id(xexternal_id));

  // Body:

  unguarded_put_ids(xinternal_id, xexternal_id);

  // Postconditions:

  ensure(invariant());
  ensure(external_id(xinternal_id) == xexternal_id);
  ensure(internal_id(xexternal_id) == xinternal_id);

  // Exit

  return;
}

template <typename internal_index_type, typename external_index_type>
void
record_map<internal_index_type, external_index_type>::
unguarded_put_ids(internal_index_type xinternal_id, external_index_type xexternal_id)
{
  // Preconditions:

  // Body:

  _to_external.insert(typename external_map_type::value_type(xinternal_id, xexternal_id));
  _to_internal.insert(typename internal_map_type::value_type(xexternal_id, xinternal_id));

  _internal_id_ub = (xinternal_id > _internal_id_ub) ? xinternal_id : _internal_id_ub;
  _external_id_ub = (xexternal_id > _external_id_ub) ? xexternal_id : _external_id_ub;

  // Postconditions:

  ensure(invariant());

  // Exit

  return;
}

template <typename internal_index_type, typename external_index_type>
bool
record_map<internal_index_type, external_index_type>::
internal_ids_sequential() const
{
  return _internal_ids_sequential;
}

template <typename internal_index_type, typename external_index_type>
bool
record_map<internal_index_type, external_index_type>::
external_ids_sequential() const
{
  return _external_ids_sequential;
}

template <typename internal_index_type, typename external_index_type>
external_index_type
record_map<internal_index_type, external_index_type>::
put_internal_id(internal_index_type xinternal_id)
{
  external_index_type result;

  // Preconditions:

  require(!is_empty() ? external_ids_sequential() : true);
  require(!contains_internal_id(xinternal_id));

  // Body:

  typename index_traits<external_index_type>::pod_type lpod = _to_external.size();
  index_traits<external_index_type>::put_pod(result, lpod);

  unguarded_put_ids(xinternal_id, result);
  _external_ids_sequential = true;

  // Postconditions:

  ensure(invariant());
  ensure(index_traits<external_index_type>::pod(result) == (ct() - 1));
  ensure(external_id(xinternal_id) == result);
  ensure(external_ids_sequential());

  // Exit

  return result;
}

template <typename internal_index_type, typename external_index_type>
internal_index_type
record_map<internal_index_type, external_index_type>::
put_external_id(external_index_type xexternal_id)
{
  internal_index_type result;

  // Preconditions:

  require(!is_empty() ? internal_ids_sequential() : true);
  require(!contains_external_id(xexternal_id));

  // Body:

  typename index_traits<internal_index_type>::pod_type lpod = _to_internal.size();
  index_traits<internal_index_type>::put_pod(result, lpod);


  unguarded_put_ids(result, xexternal_id);
  _internal_ids_sequential = true;

  // Postconditions:

  ensure(invariant());
  ensure(index_traits<internal_index_type>::pod(result) == (ct() - 1));
  ensure(internal_id(xexternal_id) == result);
  ensure(internal_ids_sequential());

  // Exit

  return result;
}

template <typename internal_index_type, typename external_index_type>
bool
record_map<internal_index_type, external_index_type>::
contains_internal_id(internal_index_type xint_id) const
{
  bool result;

  // Preconditions:

  // Body:

  
  typename external_map_type::const_iterator lresult = _to_external.find(xint_id);

  result = lresult != _to_external.end();

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

template <typename internal_index_type, typename external_index_type>
bool
record_map<internal_index_type, external_index_type>::
contains_external_id(external_index_type xext_id) const
{
  bool result;

  // Preconditions:

  // Body:

  
  typename internal_map_type::const_iterator lresult = _to_internal.find(xext_id);

  result = lresult != _to_internal.end();

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

template <typename internal_index_type, typename external_index_type>
bool
record_map<internal_index_type, external_index_type>::
operator==(const record_map& xother) const
{
  bool result = true;

  // Preconditions:

  // Body:

  record_map& lother = const_cast<record_map&>(xother);

  /// @hack On AIX, xlC uses unordered_map rather
  /// than hash_map. unordered_map contains no operator==.
  /// Rather than define operator== for unordered_map, we comment
  /// out the following two lines which test hash_maps for equality.
  /// These are only used in the post condition of record_map's copy contructor,
  /// which has now been rendered "unexecutable."

  // result = result && (_to_internal == lother._to_internal);
  // result = result && (_to_external == lother._to_external);

  result = result && (_scratch_internal_id == lother._scratch_internal_id);
  result = result && (_scratch_external_id == lother._scratch_external_id);

  result = result && (_internal_id_ub == lother._internal_id_ub);
  result = result && (_external_id_ub == lother._external_id_ub);

  result = result && (_entry_removed  == lother._entry_removed);

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

template <typename internal_index_type, typename external_index_type>
size_type
record_map<internal_index_type, external_index_type>::
ct() const
{
  return _to_internal.size();
}

template <typename internal_index_type, typename external_index_type>
bool
record_map<internal_index_type, external_index_type>::
is_empty() const
{
  return ct() == 0;
}

template <typename internal_index_type, typename external_index_type>
void
record_map<internal_index_type, external_index_type>::
clear()
{
  // Preconditions:

  // Body:

  _to_external.clear();
  _to_internal.clear();

  _internal_ids_sequential = false;
  _external_ids_sequential = false;

  _scratch_internal_id = index_traits<internal_index_type>::invalid();
  _scratch_external_id = index_traits<external_index_type>::invalid();

  _internal_id_ub = index_traits<internal_index_type>::min();
  _external_id_ub = index_traits<external_index_type>::min();

  _entry_removed           = false;

  // Postconditions:

  ensure(invariant());
  ensure(!internal_ids_sequential());
  ensure(!external_ids_sequential());
  ensure(is_empty());
  ensure(!index_traits< internal_index_type >::is_valid(scratch_internal_id()));
  ensure(!index_traits< external_index_type >::is_valid(scratch_external_id()));
  ensure(internal_id_ub() == index_traits<internal_index_type>::min());
  ensure(external_id_ub() == index_traits<external_index_type>::min());
  ensure(!ub_is_max());

  // Exit

  return;
}

template <typename internal_index_type, typename external_index_type>
void
record_map<internal_index_type, external_index_type>::
remove_internal_id(internal_index_type xinternal_id)
{
  // Preconditions:

  // Body:

  typename external_map_type::iterator litr = _to_external.find(xinternal_id);

  if(litr != _to_external.end())
  {
    _to_internal.erase(litr->second);
    _to_external.erase(litr);
  }

  /// @issue the following condition, and the postcondition !ub_is_max below,
  /// are stronger than really necessary, since xinternal_id may not have
  /// actually been removed. But it is not clear how to define the precise
  /// postcondition and this one properly informs the client that removing
  /// entries compromises ub_is_max.

  _entry_removed = true;

  // Postconditions:

  ensure(invariant());
  ensure(!contains_internal_id(xinternal_id));
  ensure(!ub_is_max());

  // Exit

  return;
}

template <typename internal_index_type, typename external_index_type>
void
record_map<internal_index_type, external_index_type>::
remove_external_id(external_index_type xexternal_id)
{
  // Preconditions:

  // Body:

  typename internal_map_type::iterator litr = _to_internal.find(xexternal_id);

  if(litr != _to_internal.end())
  {
    _to_external.erase(litr->second);
    _to_internal.erase(litr);
    _entry_removed = true;
  }

  // Postconditions:

  ensure(invariant());
  ensure(!contains_external_id(xexternal_id));
  ensure(!ub_is_max());

  // Exit

  return;
}

template <typename internal_index_type, typename external_index_type>
internal_index_type
record_map<internal_index_type, external_index_type>::
scratch_internal_id() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _scratch_internal_id;
}


template <typename internal_index_type, typename external_index_type>
void
record_map<internal_index_type, external_index_type>::
put_scratch_internal_id(internal_index_type xid)
{
  // Preconditions:

  // Body:

  _scratch_internal_id = xid;

  // Postconditions:

  ensure(scratch_internal_id() == xid);

  // Exit:

  return;
}

template <typename internal_index_type, typename external_index_type>
external_index_type
record_map<internal_index_type, external_index_type>::
scratch_external_id() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _scratch_external_id;
}

template <typename internal_index_type, typename external_index_type>
void
record_map<internal_index_type, external_index_type>::
put_scratch_external_id(external_index_type xid)
{
  // Preconditions:

  // Body:

  _scratch_external_id = xid;

  // Postconditions:

  ensure(scratch_external_id() == xid);

  // Exit:

  return;
}

template <typename internal_index_type, typename external_index_type>
internal_index_type
record_map<internal_index_type, external_index_type>::
internal_id_ub() const
{
  // Preconditions:

  // Body:

  internal_index_type result = _internal_id_ub;

  // Postconditions:

  ensure(unexecutable("for all internal ids i: i <= result"));
  ensure(unexecutable("if remove_internal_id has not been called result = maximum internal id"));

  // Exit:

  return result;
}

template <typename internal_index_type, typename external_index_type>
external_index_type
record_map<internal_index_type, external_index_type>::
external_id_ub() const
{
  // Preconditions:

  // Body:

  external_index_type result = _external_id_ub;

  // Postconditions:

  ensure(unexecutable("for all external ids i: i <= result"));
  ensure(unexecutable("if remove_external_id has not been called result = maximum external id"));

  // Exit:

  return result;
}

template <typename internal_index_type, typename external_index_type>
bool
record_map<internal_index_type, external_index_type>::
ub_is_max() const
{
  bool result;

  // Preconditions:

  // Body:

  // Upper bounds are accumulated as entries are inserted,
  // but can not be efficiently reduced when entries are removed.
  // So upper bounds will be maxima if there have been no removals.

  result = (ct() > 0) && !_entry_removed;

  // Postconditions:

  ensure(unexecutable("result == (upper bounds are in fact maxima)"));

  // Exit

  return result;
}

template <typename internal_index_type, typename external_index_type>
typename record_map<internal_index_type, external_index_type>::const_iterator
record_map<internal_index_type, external_index_type>::
begin() const
{
  return _to_external.begin();
}

template <typename internal_index_type, typename external_index_type>
typename record_map<internal_index_type, external_index_type>::const_iterator
record_map<internal_index_type, external_index_type>::
end() const
{
  return _to_external.end();
}

template <typename internal_index_type, typename external_index_type>
inline void
record_map<internal_index_type, external_index_type>::
print() const
{
  // Preconditions:

  // Body:
   
  print(cout, *this);

 // Postconditions:

  // Exit:
}

template <typename internal_index_type, typename external_index_type>
void
record_map<internal_index_type, external_index_type>::
print(ostream& xos,
      const record_map<internal_index_type, external_index_type>& xp) const
{
  // Preconditions:

  // Body:


  record_map<internal_index_type, external_index_type>& lp =
    const_cast<record_map<internal_index_type, external_index_type>&>(xp);

  xos << endl << "internal to external map:" << endl;

  xos << "int:";
  typename hash_map<internal_index_type, external_index_type>::iterator itr0;
  itr0 = lp._to_external.begin();
  while(itr0 != lp._to_external.end())
  {
    xos << setw(6) << itr0->first;
    itr0++;
  }
  xos << endl;
  xos << "ext:";
  itr0 = lp._to_external.begin();
  while(itr0 != lp._to_external.end())
  {
    xos << setw(6) << itr0->second;
    itr0++;
  }
  xos << endl;

  xos << "external to internal map:" << endl;

  xos << "ext:";
  typename hash_map<external_index_type, internal_index_type>::iterator itr1;
  itr1 = lp._to_internal.begin();
  while(itr1 != lp._to_internal.end())
  {
    xos << setw(6) << itr1->first;
    itr1++;
  }
  xos << endl;
  xos << "int:";
  itr1 = lp._to_internal.begin();
  while(itr1 != lp._to_internal.end())
  {
    xos << setw(6) << itr1->second;
    itr1++;
  }
  xos << endl;

  // Postconditions:

  // Exit:

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

template<typename internal_index_type, typename external_index_type>
ostream& operator<<(ostream& xos,
                    const record_map<internal_index_type,
                                     external_index_type>& xp)
{
  // Preconditions:

  // Body:

  xp.print(xos, xp);

  // Postconditions:

  // Exit:

  return xos;
}

} // namespace sheaf

#endif // ifndef RECORD_MAP_IMPL_H
