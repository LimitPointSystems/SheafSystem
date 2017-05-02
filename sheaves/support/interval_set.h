
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
/// Interface for class interval_set

#ifndef INTERVAL_SET_H
#define INTERVAL_SET_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "SheafSystem/any.h"
#endif

#ifndef STD_MAP_H
#include "SheafSystem/std_map.h"
#endif

#ifndef POD_TYPES_H
#include "SheafSystem/pod_types.h"
#endif

namespace sheaf
{

class interval_set_iterator;

///
/// Struct representing the closed interval [_begin, _end].
///
struct SHEAF_DLL_SPEC interval
{
  ///
  /// The "plain old data" index type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// Beginning of the interval.
  ///
  pod_type _begin;

  ///
  /// End of the interval.
  ///
  pod_type _end;
};
  
///
/// Set of integers optimized for when the integers are 
/// concentrated in closed intervals.
///
class SHEAF_DLL_SPEC interval_set : public any
{

  friend class interval_set_iterator;
  friend SHEAF_DLL_SPEC size_t deep_size(const interval_set& xset, bool xinclude_shallow);

  // ===========================================================
  /// @name INTERVAL_SET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this set.
  ///
  typedef pod_index_type pod_type;

  ///
  /// Default constructor.
  ///
  interval_set();

  ///
  /// Copy constructor.
  ///
  interval_set(const interval_set& xother);

  ///
  /// Destructor.
  ///
  ~interval_set();

  ///
  /// True if this is equivalent to xother.
  ///
  bool operator==(const interval_set& xother) const;

  ///
  /// Insert an interval of members [xbegin, xend] into this set.
  ///
  void insert_interval(pod_type xbegin, pod_type xend);

  ///
  /// Insert xmbr into this set.
  ///
  void insert_member(pod_type xmbr);

  ///
  /// Remove an interval of members [xbegin, xend] from this set.
  ///
  void remove_interval(pod_type xbegin, pod_type xend);

  ///
  /// Remove xmbr from this set.
  ///
  void remove_member(pod_type xmbr);

  ///
  /// True, if the integer xmbr is in this set.
  ///
  bool contains_member(pod_type xmbr) const;

  ///
  /// The number of members in the interval [xbegin, xend].
  ///
  size_type member_ct(pod_type xbegin, pod_type xend) const;

  ///
  /// True, if there are no members in this set for the interval
  /// [xbegin, xend].
  ///
  bool interval_is_empty(pod_type xbegin, pod_type xend) const;

  ///
  /// True, if there is a continuous interval of members
  /// [xbegin, xend] in this set.
  ///
  bool interval_is_full(pod_type xbegin, pod_type xend) const;

  ///
  /// The first member in this set.
  ///
  pod_type begin() const;

  ///
  /// The last member in this set.
  ///
  pod_type end() const;
    
  ///
  /// Clear this set.
  ///
  void clear();

  ///
  /// True, if this set is empty.
  ///
  bool is_empty() const;  

  ///
  /// Iterator for this set.  If xis_full_iterator, iterate over the members
  /// in the set.  Otherwise, iterate over the non-members in [begin(), end()].
  ///
  interval_set_iterator* iterator(bool xis_full_iterator) const;  

protected:

private:

  ///
  /// Assign xvalue to the interval [xbegin, xend] into this set.
  ///
  void put_interval(pod_type xbegin, pod_type xend, bool xvalue);

  //@}


  // ===========================================================
  /// @name MAP FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of the interval map.
  ///
  typedef std::map<pod_type, bool> map_type;

  ///
  /// The type of the interval map iterator.
  ///
  typedef map_type::const_iterator map_iterator_type;

  ///
  /// Map that defines the intervals of this set.
  ///
  const map_type& interval_map() const;

  ///
  /// Value of the first map entry.
  ///
  bool first_map_entry() const;

  ///
  /// Value of the last map entry.
  ///
  bool last_map_entry() const;

protected:

private:

  ///
  /// Map that defines the intervals of this set.
  ///
  map_type _interval_map;

  //@}

  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual interval_set* clone() const;

  ///
  /// Assignment operator
  ///
  interval_set& operator=(const interval_set& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert interval_set& xset into ostream& xos.
///
SHEAF_DLL_SPEC 
std::ostream& operator << (std::ostream& xos, const interval_set& xset);

///
/// The deep size of the referenced object of type interval_set.
///
SHEAF_DLL_SPEC
size_t deep_size(const interval_set& xset, bool xinclude_shallow = true);

} // namespace sheaf

#endif // ifndef INTERVAL_SET_H


