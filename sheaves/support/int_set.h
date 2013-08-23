
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

// Interface for class int_set

#ifndef INT_SET_H
#define INT_SET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_ITERATOR_H
#include "std_iterator.h"
#endif

namespace sheaf
{
  
class subposet;

///
/// An STL set representation for a set of integers.
///
class SHEAF_DLL_SPEC int_set : public set<int>
  {

public:

    ///
    /// Default constructor.
    ///
    int_set();

    ///
    /// Copy constructor.
    ///
    int_set(const int_set& other);

    ///
    /// Constructs an instance with the xct members given in xmbrs.
    ///
    int_set(const int* xmbrs, int xct);

    ///
    /// Destructor.
    ///
    ~int_set();

    ///
    /// Insert member with index xmbr; just for consistency with subposet
    ///
    inline void insert_member(int xmbr)
    {
      (void) insert(xmbr);
    } ;

    ///
    /// Remove member with index xmbr; just for consistency with subposet
    ///
    inline void remove_member(int xmbr)
    {
      (void) erase(xmbr);
    } ;

    ///
    /// Insert the members with indices in xmbrs
    ///
    void insert_members(const int* xmbrs, int xct);

    ///
    /// Insert the members with indices in xmbrs
    ///
    void insert_members(const subposet* xmbrs);

    

    ///
    /// True if this set contains xindex
    /// Deprecated - use contains_member(int xindex)
    ///
    inline bool contains(int xindex) const
    {
      return (find(xindex) != end());
    };

    

    ///
    /// True if this set contains xindex
    /// True if this set contains xindex
    ///
    inline bool contains_member(int xindex) const
    {
      return (find(xindex) != end());
    };

    ///
    /// True if set contains only a single member
    ///
    bool is_singleton() const;

    ///
    /// True if this cover set includes other;
    /// If this_is_much_larger then assume this cover set is much larger
    /// than other and use an  other->size()*log(size()) algorithm
    /// rather than a other->size()+ size() algorithm.
    ///
    bool set_includes(const int_set* other, bool this_is_much_larger = false) const;

    ///
    /// union of this with other, auto-allocated version.
    ///
    int_set* set_union(const int_set* other) const;

    ///
    /// union of this with other, pre-allocated version.
    ///
    void set_union_pa(const int_set* other, int_set* result) const;

    ///
    /// union of this with other, self-allocated version.
    ///
    void set_union_sa(const int_set* other);

    ///
    /// Intersection of this with other, auto-allocated version.
    ///
    int_set* set_intersection(const int_set* other) const;

    ///
    /// Intersection of this with other, pre-allocated version.
    ///
    void set_intersection_pa(const int_set* other, int_set* result) const;

    ///
    /// Intersection of this with other, self-allocated version.
    ///
    void set_intersection_sa(const int_set* other);

    ///
    /// Difference of this and other (this minus other), auto-allocated version.
    /// If this_is_much_larger then assume this cover set is much larger
    /// than other and use an other->size()*log(size()) algorithm
    /// rather than a other->size()+ size() algorithm.
    ///
    int_set* set_difference(const int_set* other) const;

    ///
    /// Difference of this and other (this minus other), pre-allocated version.
    /// If this_is_much_larger then assume this cover set is much larger
    /// than other and use an other->size()*log(size()) algorithm
    /// rather than a other->size()+ size() algorithm.
    ///
    void set_difference_pa(const int_set* other, int_set* result) const;

    ///
    /// Difference of this and other (this minus other), self-allocated version.
    /// If this_is_much_larger then assume this cover set is much larger
    /// than other and use an other->size()*log(size()) algorithm
    /// rather than a other->size()+ size() algorithm.
    ///
    void set_difference_sa(int_set* other, bool this_is_much_larger = false);

    ///
    /// Prints membership to cout. Intended for debugging.
    ///
    void print() const;
  };


// NON-MEMBER FUNCTIONS




///
/// Insert int_set& c into ostream& os.
///
SHEAF_DLL_SPEC
ostream& operator << (ostream& os, const int_set& c);

} // namespace sheaf

#endif // ifndef INT_SET_H


