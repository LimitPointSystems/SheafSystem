
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

// Interface for antisymmetric_matrix_2x2 classes.

#ifndef ANTISYMMETRIC_MATRIX_2X2_H
#define ANTISYMMETRIC_MATRIX_2X2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace fiber_bundle
{

template <typename T> class general_matrix_1x2;
template <typename T> class general_matrix_2x1;
template <typename T> class general_matrix_2x2;
template <typename T> class general_matrix_2x3;

template <typename T> class at2_e2_row_dofs_type;

//==============================================================================
//==============================================================================

///
/// Antisymmetric matrix with 2 rows and 2 columns.
///
/// Class antisymmetric_matrix_2x2 is a special kind of matrix class intended to be
/// used in conjunction with various row_dofs_type classes (pod types).
/// The pod types will be converted (cast) to appropriate matrix types.
/// So, this class is also required to be a pod type also (ie: really just a 
/// struct with no inheritance, no constructors, no virtual functions, etc.).
///
///
template <typename T>
class antisymmetric_matrix_2x2
{
public:

  ///
  /// Operator to convert current to at2_e2_row_dofs_type@<T@>.
  ///
  operator at2_e2_row_dofs_type<T>& () const;

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
  /// Conversion operator to convert to the associated general matrix type.
  ///
  operator general_matrix_2x2<T> () const;

  ///
  /// A 1x2 matrix containing the elements or row xrow.
  ///
  general_matrix_1x2<T> row(int xrow) const;

  ///
  /// A 2x1 matrix containing the elements or column xcolumn.
  ///
  general_matrix_2x1<T> column(int xcolumn) const;

  ///
  /// Linear storage array.
  ///
  T components[1];

  //============================================================================
  //============================================================================

  ///
  /// The adjoint of the matrix (pre-allocated).
  ///
  void adjoint(antisymmetric_matrix_2x2<T>& xresult) const;

  ///
  /// The adjoint of the matrix (auto-allocated).
  ///
  antisymmetric_matrix_2x2<T> adjoint() const;

  ///
  /// Assign all elements of this matrix to the value xvalue.
  ///
  void assign(const T& xscalar);

  ///
  /// The determinant of the matrix (pre-allocated).
  ///
  void determinant(T& xresult) const;

  ///
  /// The determinant of the matrix (auto-allocated).
  ///
  T determinant() const;

  ///
  /// The inverse of the matrix (pre-allocated).
  ///
  void inverse(antisymmetric_matrix_2x2<T>& xresult) const;

  ///
  /// The inverse of the matrix (auto-allocated).
  ///
  antisymmetric_matrix_2x2<T> inverse() const;

  ///
  /// True if this matrix is positive definite.
  /// Always returns false for antisymmetric_matrices.
  ///
  bool is_positive_definite() const;

  ///
  /// This matrix multiplied by a scalar (pre-allocated).
  ///
  void multiply(const T& xscalar, antisymmetric_matrix_2x2<T>& xresult) const;

  ///
  /// This matrix multiplied by a scalar (auto-allocated).
  ///
  antisymmetric_matrix_2x2<T> multiply(const T& xscalar) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  ///
  void multiply(const general_matrix_2x1<T>& xother,
                general_matrix_2x1<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  ///
  general_matrix_2x1<T> multiply(const general_matrix_2x1<T>& xother) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  ///
  void multiply(const general_matrix_2x2<T>& xother,
                general_matrix_2x2<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  ///
  general_matrix_2x2<T> multiply(const general_matrix_2x2<T>& xother) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  ///
  void multiply(const general_matrix_2x3<T>& xother,
                general_matrix_2x3<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  ///
  general_matrix_2x3<T> multiply(const general_matrix_2x3<T>& xother) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  /// Note that multiplying 2 antisymmetric matrices results (in general)
  /// in a general square matrix.
  ///
  void multiply(const antisymmetric_matrix_2x2<T>& xother,
                general_matrix_2x2<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  /// Note that multiplying 2 antisymmetric matrices results (in general)
  /// in a general square matrix.
  ///
  general_matrix_2x2<T> multiply(const antisymmetric_matrix_2x2<T>& xother) const;

  ///
  /// The trace of the matrix (pre-allocated).
  ///
  void trace(T& xresult) const;

  ///
  /// The trace of the matrix (auto-allocated).
  ///
  T trace() const;

  ///
  /// The transpose of the matrix (pre-allocated).
  ///
  void transpose(antisymmetric_matrix_2x2<T>& xresult) const;

  ///
  /// The transpose of the matrix (auto-allocated).
  ///
  antisymmetric_matrix_2x2<T> transpose() const;

  ///@todo
  /// add, +, += 
  /// subtract, - ,-=
  /// matrix multiply, *, *=
  /// scalar multiply, *, *=
  /// ...


protected:
private:

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

///
/// Insert antisymmetric_matrix_2x2@<T@> xm into output stream xos.
///
template <typename T>
std::ostream& operator<<(std::ostream& xos, const antisymmetric_matrix_2x2<T>& xm);

} // namespace fiber_bundle

#endif // ifndef ANTISYMMETRIC_MATRIX_2X2_H
