
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
/// Interface for class record_map

#ifndef RECORD_MAP_H
#define RECORD_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

#ifndef STD_UNORDERED_MAP_H
#include "std_unordered_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
  
// Forward declarations to support friend declaration.

template <typename T1, typename T2>
class record_map;

///
/// Insert record_map& p into ostream& os.
///
//template <typename T1, typename T2>
//ostream& operator << (ostream &os, record_map<T1, T2>& p);

///
/// A bidirectional map between an internal index space
/// and an external index space. The map is injective
/// (one-to-one), but neither total (not every internal
/// index has an external index associated with it) nor
/// surjective (not every external index has an internal
/// index associated with it.
///
template<typename internal_index_type, typename external_index_type>
class record_map
{
  // ===========================================================
  /// @name RECORD_MAP FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  record_map();

  ///
  /// Copy constructor
  ///
  record_map(const record_map& xother);

  ///
  /// Assignment operator
  ///
  record_map& operator=(const record_map& xother);

  ///
  /// Destructor
  ///
  virtual ~record_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// The external id corresponding to xinternal_id.
  ///
  external_index_type external_id(internal_index_type xinternal_id) const;

  ///
  /// The internal id corresponding to xexternal_id.
  ///
  internal_index_type internal_id(external_index_type xexternal_id) const;

  ///
  /// Defines the mapping between xinternal_id and xexternal_id.
  ///
  void put_ids(internal_index_type xinternal_id,
               external_index_type xexternal_id);

  ///
  /// True if sequentially assigning internal ids.
  ///
  bool internal_ids_sequential() const;

  ///
  /// True if sequentially assigning external ids.
  ///
  bool external_ids_sequential() const;

  ///
  /// Defines a mapping between xinternal_id and
  /// a sequentially assigned external id. Returns
  /// the external id.
  ///
  external_index_type put_internal_id(internal_index_type xinternal_id);

  ///
  /// Defines a mapping between xexternal_id and
  /// a sequentially assigned internal id.
  ///
  internal_index_type put_external_id(external_index_type xexternal_id);

  ///
  /// True if this map contains an entry for internal index xint_id
  ///
  bool contains_internal_id(internal_index_type xint_id) const;

  ///
  /// True if this map contains an entry for external index xext_id
  ///
  bool contains_external_id(external_index_type xext_id) const;

  ///
  /// True if same external_id and internal_id
  ///
  bool operator==(const record_map& xother) const;

  ///
  /// The number of entries in the map
  ///
  size_type ct() const;

  ///
  /// True if there are no entries in the map.
  ///
  bool is_empty() const;

  ///
  /// Removes all entries.
  ///
  void clear();

  ///
  /// Removes xinternal_id and its external image from the map.
  ///
  void remove_internal_id(internal_index_type xinternal_id);

  ///
  /// Removes xexternal_id and its internal image from the map.
  ///
  void remove_external_id(external_index_type xexternal_id);

  ///
  /// The value of the internal id scratch register.
  /// The scratch register is a convenient place for a client
  /// to store an internal id that has the same scope and lifetime
  /// as this index map.
  ///
  internal_index_type scratch_internal_id() const;

  ///
  /// Sets the value of the internal id scratch register to xid.
  ///
  void put_scratch_internal_id(internal_index_type xid);

  ///
  /// The value of the external id scratch register.
  /// The scratch register is a convenient place for a client
  /// to store an external id that has the same scope and lifetime
  /// as this index map.
  ///
  external_index_type scratch_external_id() const;

  ///
  /// Sets the value of the external id scratch register to xid.
  ///
  void put_scratch_external_id(external_index_type xid);

  ///
  /// The maximum internal id in this map.
  ///
  internal_index_type internal_id_ub() const;

  ///
  /// The maximum external id in this map.
  ///
  external_index_type external_id_ub() const;

  ///
  /// True if internal_id_ub and external_id_ub are in fact
  /// maxima; i.e. if there exists an entry (int_id, ext_id) in
  /// the map such that int_id == internal_id_ub() and
  /// ext_id == external_id_ub();
  ///
  bool ub_is_max() const;

  ///
  /// The type of const iterator for this.
  ///
  typedef typename
  unordered::unordered_map<internal_index_type, external_index_type>::const_iterator const_iterator;

  ///
  /// The beginning of the range of internal ids contained in this.
  ///
  const_iterator begin() const;

  ///
  /// The end of the range of internal ids contained in this.
  ///
  const_iterator end() const;
  
  ///
  /// Prints the data members of this on cout.
  /// Intended for use debugging.
  ///
  void print() const;

  ///
  /// Prints the data members of this on stream xos.
  /// Intended for use debugging.
  ///
  void print(std::ostream& xos,
	     const record_map<internal_index_type, external_index_type>& xp) const;

protected:

private:

  ///
  /// The type of the internal to external map.
  ///
  typedef unordered::unordered_map<internal_index_type, external_index_type> external_map_type;

  ///
  /// The representation of the internal to external map.
  ///
  external_map_type _to_external;

  ///
  /// The type of the external to internal map.
  ///
  typedef unordered::unordered_map<external_index_type, internal_index_type> internal_map_type;

  ///
  /// The representation of the external to internal map.
  ///
  internal_map_type _to_internal;

  ///
  /// True if sequentially assigning internal ids.
  ///
  bool _internal_ids_sequential;

  ///
  /// True if sequentially assigning external ids.
  ///
  bool _external_ids_sequential;

  ///
  /// A scratch register to store an internal id;
  /// a convenient place for a client to store an
  /// internal id for future use.
  ///
  internal_index_type _scratch_internal_id;

  ///
  /// A scratch register to store an external id;
  /// a convenient place for a client to store an
  /// external id for future use.
  ///
  external_index_type _scratch_external_id;

  ///
  /// An upper bound for internal ids in the map.
  ///
  internal_index_type _internal_id_ub;

  ///
  /// An upper bound for external ids in the map.
  ///
  external_index_type _external_id_ub;

  ///
  /// True if no entry has been removed.
  ///
  bool _entry_removed;

  ///
  /// Defines the mapping between xinternal_id and xexternal_id.
  ///
  void unguarded_put_ids(internal_index_type xinternal_id,
                         external_index_type xexternal_id);


  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template<typename internal_index_type, typename external_index_type>
std::ostream&
operator<<(std::ostream& xos, const record_map<internal_index_type, external_index_type>& xp);

 
} // namespace sheaf

#endif // ifndef RECORD_MAP_H
