
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

// Interface for general_matrix_3x3 classes.

#ifndef GENERAL_MATRIX_3X3_H
#define GENERAL_MATRIX_3X3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace fiber_bundle
{

template <typename T> class antisymmetric_matrix_3x3;
template <typename T> class general_matrix_1x3;
template <typename T> class general_matrix_3x1;
template <typename T> class general_matrix_3x2;
template <typename T> class symmetric_matrix_3x3;

template <typename T> class gl3_row_dofs_type;
template <typename T> class jcb_e33_row_dofs_type;
template <typename T> class t02_e3_row_dofs_type;

//==============================================================================
//==============================================================================

///
/// General matrix with 3 rows and 3 columns.
///
/// Class general_matrix_3x3 is a special kind of matrix class intended to be
/// used in conjunction with various row_dofs_type classes (pod types).
/// The pod types will be converted (cast) to appropriate matrix types.
/// So, this class is also required to be a pod type also (ie: really just a 
/// struct with no inheritance, no constructors, no virtual functions, etc.).
///
///
template <typename T>
class general_matrix_3x3
{
public:

  ///
  /// Operator to convert current to gl3_row_dofs_type.
  ///
  operator gl3_row_dofs_type<T>& () const;

  ///
  /// Operator to convert current to jcb_e23_row_dofs_type.
  ///
  operator jcb_e33_row_dofs_type<T>& () const;

  ///
  /// Operator to convert current to t02_e3_row_dofs_type.
  ///
  operator t02_e3_row_dofs_type<T>& () const;

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
  /// A 1x3 matrix containing the elements or row xrow.
  ///
  general_matrix_1x3<T> row(int xrow) const;

  ///
  /// A 3x1 matrix containing the elements or column xcolumn.
  ///
  general_matrix_3x1<T> column(int xcolumn) const;

  ///
  /// Linear storage array.
  ///
  T components[9];

  //============================================================================
  //============================================================================

  ///
  /// The adjoint of the matrix (pre-allocated).
  ///
  void adjoint(general_matrix_3x3<T>& xresult) const;

  ///
  /// The adjoint of the matrix (auto-allocated).
  ///
  general_matrix_3x3<T> adjoint() const;

  ///
  /// Assign all elements of this matrix to the value xvalue.
  ///
  void assign(const T& xvalue);

  ///
  /// The determinant of the matrix (pre-allocated).
  ///
  void determinant(T& xresult) const;

  ///
  /// The determinant of the matrix (auto-allocated).
  ///
  T determinant() const;

  ///
  /// The diagonalization of the matrix (pre-allocated).
  ///
  void diagonalization(general_matrix_3x3<T>& xresult) const;

  ///
  /// The diagonalization of the matrix (auto-allocated).
  ///
  general_matrix_3x3<T> diagonalization() const;

  ///
  /// The identity matrix (pre-allocated).
  ///
  void identity(general_matrix_3x3<T>& xresult) const;

  ///
  /// The identity matrix (auto-allocated).
  ///
  general_matrix_3x3<T> identity() const;

  ///
  /// The inverse of the matrix (pre-allocated).
  ///
  void inverse(general_matrix_3x3<T>& xresult) const;

  ///
  /// The inverse of the matrix (auto-allocated).
  ///
  general_matrix_3x3<T> inverse() const;

  ///
  /// True if this matrix is antisymmetric.
  ///
  bool is_antisymmetric() const;

  ///
  /// True if this matrix is diagonal.
  ///
  bool is_diagonal() const;

  ///
  /// True if this is an identity matrix.
  ///
  bool is_identity() const;

  ///
  /// True if this matrix is positive definite.
  ///
  bool is_positive_definite() const;

  ///
  /// True if this matrix is symmetric.
  ///
  bool is_symmetric() const;

  ///
  /// This matrix multiplied by a scalar (pre-allocated).
  ///
  void multiply(const T& xscalar, general_matrix_3x3<T>& xresult) const;

  ///
  /// This matrix multiplied by a scalar (auto-allocated).
  ///
  general_matrix_3x3<T> multiply(const T& xscalar) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  ///
  void multiply(const general_matrix_3x3<T>& xother,
                general_matrix_3x3<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  ///
  general_matrix_3x3<T> multiply(const general_matrix_3x3<T>& xother) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  ///
  void multiply(const general_matrix_3x2<T>& xother,
                general_matrix_3x2<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  ///
  general_matrix_3x2<T> multiply(const general_matrix_3x2<T>& xother) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  ///
  void multiply(const general_matrix_3x1<T>& xother,
                general_matrix_3x1<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  ///
  general_matrix_3x1<T> multiply(const general_matrix_3x1<T>& xother) const;

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
  void transpose(general_matrix_3x3<T>& xresult) const;

  ///
  /// The transpose of the matrix (auto-allocated).
  ///
  general_matrix_3x3<T> transpose() const;

  ///
  /// The antisymmetric part of a this matrix (pre-allocated).
  ///
  void antisymmetric_part(antisymmetric_matrix_3x3<T>& xresult) const;

  ///
  /// The antisymmetric part of a this matrix (auto-allocated).
  ///
  antisymmetric_matrix_3x3<T> antisymmetric_part() const;

  ///
  /// The symmetric part of a this matrix (pre-allocated).
  ///
  void symmetric_part(symmetric_matrix_3x3<T>& xresult) const;

  ///
  /// The symmetric part of a this matrix (auto-allocated).
  ///
  symmetric_matrix_3x3<T> symmetric_part() const;

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
/// Insert general_matrix_3x3@<T@> xm into output stream xos.
///
template <typename T>
std::ostream& operator<<(std::ostream& xos, const general_matrix_3x3<T>& xm);


} // namespace fiber_bundle

#endif // ifndef GENERAL_MATRIX_3X3_H
