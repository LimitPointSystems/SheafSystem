
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

// Interface for class ZN_TO_BOOL


#ifndef ZN_TO_BOOL_H
#define ZN_TO_BOOL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#include "SheafSystem/assert_contract.h"

#ifndef STD_IOSTREAM_H
#include "SheafSystem/std_iostream.h"
#endif

#ifndef STD_LIMITS_H
#include "SheafSystem/std_limits.h"
#endif

namespace sheaf
{

template <typename T>
class block;

class zn_to_bool;
class index_iterator;
class subposet;  

///
/// A map from Zn (the integers mod n) to bools.
/// A characteristic function used to represent subsets of Zn.
///
class SHEAF_DLL_SPEC zn_to_bool
{


  friend SHEAF_DLL_SPEC std::ostream & operator << (std::ostream &os, zn_to_bool& zn);
  friend SHEAF_DLL_SPEC size_t deep_size(const zn_to_bool& zn, bool xinclude_shallow);
  friend class index_iterator;
  friend class subposet;

  // ===========================================================
  // ZN_TO_BOOL FACET
  // ===========================================================
 
public:

  ///
  /// Class Invariant
  ///
  bool  invariant() const;

  ///
  /// Default constructor.
  ///
  zn_to_bool();

  ///
  /// Copy constructor.
  ///
  zn_to_bool(const zn_to_bool& xother);

  ///
  /// Create an instance with ub() = xub;
  /// if xinitialize, initialize so is_false() = true
  ///
  zn_to_bool(int xub, bool xinitialize = true);

  ///
  /// Create an instance with ub() = xub, initialized with bits from
  /// `values'.  [j] is true if the bit at offset j from address `values'
  /// is 1 and false otherwise.
  ///
  zn_to_bool(int xub, unsigned *values);

  ///
  /// Destructor
  ///
  ~zn_to_bool();

  // ===========================================================
  // DOMAIN FACET
  // ===========================================================
 
  ///
  /// True if domain properly allocated.
  ///
  bool domain_is_valid() const;

  ///
  /// The upper bound for the domain index.
  ///
  int ub() const;

  ///
  /// True if index i is in bounds for this vector.
  ///
  bool index_in_bounds(int i) const;

  ///
  /// True if for all i in indices: i is in bounds for this vector.
  ///
  bool index_in_bounds(const block<int>* indices) const;

  ///
  ///   The number of members in the domain.
  ///
  int ct() const;

  ///
  /// The number of members with value = true.
  ///
  int true_ct() const;

  ///
  /// The number of members with value = false.
  ///
  int false_ct() const;

  ///
  /// Make the upper bound at least xub.
  ///
  void extend_to(int xub);

  ///
  /// The number of members this can extend_to() without reallocating.
  ///
  size_t capacity() const;

  // $$ISSUE: If this typedef is private, then there is no access
  // to it in other classes once they are inserted into the sheaf
  // namespace. JEB 090408

  ///
  /// The type of the private,
  /// internal representation used for bits;
  /// Unsigned int is the type used in the interface
  /// to exchange bits with the public. Currently
  /// the two types are the same.
  ///
  typedef unsigned int word_t;

  ///
  /// Number of bits per word
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {BITS_PER_WORD = std::numeric_limits<word_t>::digits};

protected:
private:

  ///
  /// The upper bound for the domain index.
  ///
  int _ub;

  ///
  /// The upper bound for the word index.
  ///
  int _word_ub;

  ///
  /// The upper bound for the word index.
  ///
  inline int word_ub()
  {
    return _word_ub;
  }

  ///
  /// The values (bits).
  ///
  word_t* _values;

  ///
  /// The values (bits).
  ///
  inline word_t* values()
  {
    return _values;
  };
  
  ///
  /// Upper bound on allocation of values.
  ///
  int _values_ub;

  // ===========================================================
  // CHARACTERISTIC FUNCTION FACET
  // =========================================================== 

public:

  ///
  /// Value at i.
  ///
  inline bool operator [] (int i) const
  {
    // preconditions:

    require(index_in_bounds(i));

    // body:

    bool result = (get_word(i) & get_mask(i)) != 0;

    return result;
  }

  ///
  /// True if for all i in indices: member with index i is true.
  ///
  bool is_true_for(const block<int>* indices) const;

  ///
  /// True if for all i in indices: member with index i is false.
  ///
  bool is_false_for(const block<int>* indices) const;

  ///
  /// Sets i-th member to value.
  ///
  void put(int i, bool value);

  ///
  /// For all i in indices: sets i-th member to value.
  ///
  void put(const block<int>* indices, bool value);

  ///
  /// Sets the i-th member to value, extends the upper bound if necessary.
  ///
  void force(int i, bool value);

  ///
  /// Sets i-th member to its complement.
  ///
  void put_not(int i);

  ///
  /// For all i in indices: sets i-th member to its complement.
  ///
  void put_not(const block<int>* indices);

protected:
private:

  ///
  /// Gets the word that contains the bit with index xindex (mutable version).
  ///
  inline word_t& get_word(int xindex)
  {
    return(*(_values+(xindex/BITS_PER_WORD)));
  }

  ///
  /// Gets the word that contains the bit with index xindex (const version).
  ///
  inline const word_t& get_word(int xindex) const
  {
    return(*(_values+(xindex/BITS_PER_WORD)));
  }

  ///
  /// Gets the mask for the bit with index xindex.
  ///
  inline word_t get_mask(int xindex) const
  {
    return( 1 << (xindex%BITS_PER_WORD) );
  }

  // ===========================================================
  // BOOLEAN ALGEBRA FACET
  // ===========================================================

public:
 
  ///
  /// True function is true everywhere on domain.
  ///
  bool is_true() const;

  ///
  /// True if function is false evrywhere on domain.
  ///
  bool is_false() const;

  ///
  /// OBSOLETE: use operator==(const zn_to_bool&).
  /// True if function is equal to other evrywhere on domain.
  ///
  bool is_equal_to(const zn_to_bool* other) const;

  ///
  /// True if function is equal to other evrywhere on domain.
  ///
  bool operator==(const zn_to_bool& other) const;

  ///
  /// True if this function is true everywhere other is true.
  ///
  bool includes(const zn_to_bool* other) const;

  ///
  /// True if function is complement of other evrywhere on domain.
  ///
  bool is_not(const zn_to_bool* other) const;

  ///
  /// Constant function true, auto-allocated.
  ///
  zn_to_bool* make_true();

  ///
  /// Constant function true, self-allocated.<br>
  /// <i>Note on terminology: "true" is a keyword, so this function
  /// can not be just "true"</i>
  ///
  void make_true_sa();

  // pre-allocated version not needed for unary operators

  ///
  /// Constant function false, auto-allocated.<br>
  /// <i>Note on terminology: "false" is a keyword, so this function
  /// can not be just "false"</i>
  ///
  zn_to_bool* make_false();

  ///
  /// Constant function false, self-allocated.<br>
  /// <i>Note on terminology: "false" is a keyword, so this function
  /// can not be just "false"</i>
  ///
  void make_false_sa();

  // pre-allocated version not needed for unary operators

  ///
  /// OBSOLETE; use copy contructor.
  ///
  zn_to_bool* equal();

  ///
  /// OBSOLETE; use assignment operator.
  ///
  void equal_pa(const zn_to_bool* result);

  ///
  /// Assignment operator.
  ///
  zn_to_bool& operator=(const zn_to_bool& xother);


  // The operators below have 'b_' prefix.  This indicates that
  // these operators are boolean operators.  The need for this
  // prefix arises from 'not', 'and' & 'or' being reserved words
  // in the ansi C++ standard.

  ///
  /// Boolean complement, auto-allocated.
  ///
  zn_to_bool* b_not();

  ///
  /// Boolean complement, pre-allocated.
  ///
  void b_not_pa(const zn_to_bool* other);

  ///
  /// Boolean complement, self-allocated.
  ///
  void b_not_sa();

  ///
  /// This AND other, auto-allocated.
  ///
  zn_to_bool* b_and(const zn_to_bool* other);

  ///
  /// This AND other, pre-allocated.
  ///
  void b_and_pa(const zn_to_bool* other, zn_to_bool* result);

  ///
  /// This AND other, self-allocated.
  ///
  void b_and_sa(const zn_to_bool* other);

  ///
  /// This OR other, auto-allocated.
  ///
  zn_to_bool* b_or(const zn_to_bool* other);

  ///
  /// This OR other, pre-allocated.
  ///
  void b_or_pa(const zn_to_bool* other, zn_to_bool* result);

  ///
  /// This OR other, self-allocated.
  ///
  void b_or_sa(const zn_to_bool* other);

  ///
  /// This AND NOT other, auto-allocated.
  ///
  zn_to_bool* b_and_not(const zn_to_bool* other);

  ///
  /// This AND NOT other, pre-allocated.
  ///
  void b_and_not_pa(const zn_to_bool* other, zn_to_bool* result);

  ///
  /// This AND NOT other, self-allocated.
  ///
  void b_and_not_sa(const zn_to_bool* other);

protected:
private:
};


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert zn_to_bool& zn into ostream& os.
///
SHEAF_DLL_SPEC 
std::ostream & operator << (std::ostream &os, zn_to_bool& zn);

///
/// The deep size of the referenced object of type zn_to_bool.
///
SHEAF_DLL_SPEC 
size_t deep_size(const zn_to_bool& xp, bool xinclude_shallow = true);
 
} // namespace sheaf

#endif // ifndef ZN_TO_BOOL_H
