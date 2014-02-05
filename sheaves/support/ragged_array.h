
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

// Interface for class ragged_array

#ifndef RAGGED_ARRAY_H
#define RAGGED_ARRAY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef RC_ANY_H
#include "rc_any.h"
#endif

#ifndef RC_PTR_H
#include "rc_ptr.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

namespace sheaf
{
  
template <typename T> class ragged_array;

///
/// The deep size of the referenced object of type ragged_array@<T@>;
/// if xinclude_shallow, add the sizeof xp to the result.
///
template<typename T>
size_t deep_size(const ragged_array<T>& xra, bool xinclude_shallow = true);

///
/// A two index array with variable length rows.
///
template <typename T>
class SHEAF_DLL_SPEC ragged_array : public rc_any
{

  friend size_t deep_size<T>(const ragged_array<T>& xra, bool xinclude_shallow); 

  // ===========================================================
  /// @name RAGGED_ARRAY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The integer type used to index this.
  ///
  typedef unsigned long index_type;


  ///
  /// Reference counted pointer type.
  ///
  typedef rc_ptr< ragged_array<T> > ptr;

  ///
  /// Default constructor; creates an empty array with one row
  /// and space reserved for xct values.
  ///
  ragged_array(size_t xct = 0);

  ///
  /// Copy constructor
  ///
  ragged_array(const ragged_array& xother);

  ///
  /// Creates an instance with xrow_ct rows, with the number
  /// of columns in the i-th row given by xcol_cts[i].
  ///
  ragged_array(const index_type* xcol_cts,
               index_type xcol_cts_ub);

  ///
  /// Creates an instance with xrow_ct rows and
  /// xvalue_ct values.
  ///
  ragged_array(const index_type xrow_ct, const index_type xvalue_ct);

  ///
  /// Destructor.
  ///
  virtual ~ragged_array();

  ///
  /// Assignment operator.
  ///
  ragged_array& operator=(const ragged_array& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const ragged_array& xother) const;

  ///
  /// The number of rows.
  ///
  index_type row_ct() const;

  ///
  /// The number of columns for the xrow_index-th row.
  ///
  index_type col_ct(const index_type xrow_index) const;

  ///
  /// The naked, underlying storage for number of columns for each row.
  ///
  index_type* col_cts() const;

  ///
  /// The naked, underlying storage for the values in the array.
  ///
  T* values() const;

  ///
  /// The number of values.
  ///
  index_type value_ct() const;

  ///
  /// The row with index xrow_index.
  ///
  T* row(const index_type xrow_index) const;

  ///
  /// The row index operator; alias for row(index_type).
  ///
  T* operator[](const index_type xrow_index) const;

  ///
  /// Reinitializes access by row index using the column counts in col_cts().
  ///
  void reset_rows();

  ///
  /// Reinitializes access by row index using the column counts in xcol_cts.
  ///
  void reset_rows(const index_type* xcol_cts, const index_type xcol_cts_ub);

  ///
  /// The sum of the column counts in col_cts().
  ///
  index_type sum_col_cts() const;

  ///
  /// The sum of the column counts in xcol_cts.
  ///
  index_type sum_col_cts(const index_type* xcol_cts, const index_type xcol_cts_ub) const;

  ///
  /// Reserves storage for xrow_ct rows containing xvalue_ct total values
  /// and initializes push_back into row 0 column 0.
  ///
  void initialize_push_back(index_type xrow_ct, index_type xvalue_ct);

  ///
  /// The last row; the active row for push_back.
  ///
  index_type back_row() const;

  ///
  /// Creates a new last row.
  ///
  void new_back_row();

  ///
  /// Add a value to the back of the back row.
  ///
  void push_back(const T& xvalue);

protected:

  ///
  /// Creates an instance with xcol_cts_ub rows, with the number
  /// of columns in the i-th row given by xcol_cts[i].
  ///
  void initialize(const index_type* xcol_cts,
                  index_type xcol_cts_ub);


  ///
  /// The values stored in the array.
  ///
  block<T> _values;

  ///
  /// The number of columns in each row.
  ///
  block<index_type> _col_cts;

  ///
  /// Index of the first value in each row.
  ///
  block<index_type> _row_ptrs;

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual ragged_array* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

protected:

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts ragged_array xra into ostream xos.
///
template <typename T>
std::ostream& operator << (std::ostream& xos, const ragged_array<T>& xra);
 
} // namespace sheaf

#endif // ifndef RAGGED_ARRAY_H






