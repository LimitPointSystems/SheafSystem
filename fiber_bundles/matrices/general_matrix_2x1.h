
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

// Interface for general_matrix_2x1 classes.

#ifndef GENERAL_MATRIX_2X1_H
#define GENERAL_MATRIX_2X1_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace fiber_bundle
{

template <typename T> class general_matrix_1x2;
template <typename T> class general_matrix_1x3;
template <typename T> class general_matrix_2x2;
template <typename T> class general_matrix_2x3;

//==============================================================================
//==============================================================================

///
/// General matrix with 2 rows and 1 column.
///
/// Class general_matrix_2x1 is a special kind of matrix class intended to be
/// used in conjunction with various row_dofs_type classes (pod types).
/// The pod types will be converted (cast) to appropriate matrix types.
/// So, this class is also required to be a pod type also (ie: really just a 
/// struct with no inheritance, no constructors, no virtual functions, etc.).
///
///
template <typename T>
class general_matrix_2x1
{
public:

  ///
  /// The number of rows.
  ///
  static int number_of_rows();

  ///
  /// The number of columns.
  ///
  static int number_of_columns();

  ///
  /// Dimension of the underlying elements.
  ///
  static int d();

  ///
  /// Pointer to the first element in row xrow of this matrix.
  /// Facilitates accessing elements via matrix[i][j].
  ///
  T* operator[](int xrow);

  ///
  /// Pointer to the first element in row xrow of this matrix.
  /// Facilitates accessing elements via matrix[i][j].
  ///
  const T* operator[](int xrow) const;

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (non const version). 
  ///
  operator T* ();

  ///
  /// Conversion (cast) operator to convert to the associated matrix type
  /// (const version). 
  ///
  operator const T* () const;

  ///
  /// Index for row xrow in the linear storage array.
  ///
  int row_index(int xrow) const;

  ///
  /// Linear storage array.
  ///
  T components[2];

  //============================================================================
  //============================================================================

  ///
  /// Assign all elements of this matrix to the value xvalue.
  ///
  void assign(const T& xvalue);

  ///
  /// This matrix multiplied by a scalar (pre-allocated).
  ///
  void multiply(const T& xscalar, general_matrix_2x1<T>& xresult) const;

  ///
  /// This matrix multiplied by a scalar (auto-allocated).
  ///
  general_matrix_2x1<T> multiply(const T& xscalar) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  ///
  void multiply(const general_matrix_1x2<T>& xother,
                general_matrix_2x2<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  ///
  general_matrix_2x2<T> multiply(const general_matrix_1x2<T>& xother) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  ///
  void multiply(const general_matrix_1x3<T>& xother,
                general_matrix_2x3<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  ///
  general_matrix_2x3<T> multiply(const general_matrix_1x3<T>& xother) const;

  ///
  /// The transpose of the matrix (pre-allocated).
  ///
  void transpose(general_matrix_1x2<T>& xresult) const;

  ///
  /// The transpose of the matrix (auto-allocated).
  ///
  general_matrix_1x2<T> transpose() const;

protected:
private:

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

///
/// Insert general_matrix_2x1@<T@> xm into output stream xos.
///
template <typename T>
std::ostream& operator<<(std::ostream& xos, const general_matrix_2x1<T>& xm);

 
} // namespace fiber_bundle

#endif // ifndef GENERAL_MATRIX_2X1_H
