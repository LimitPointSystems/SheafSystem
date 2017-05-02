
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

// Interface for symmetric_matrix_3x3 classes.

#ifndef SYMMETRIC_MATRIX_3X3_H
#define SYMMETRIC_MATRIX_3X3_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef STD_IOSTREAM_H
#include "SheafSystem/std_iostream.h"
#endif

namespace fiber_bundle
{

template <typename T> class general_matrix_1x3;
template <typename T> class general_matrix_3x1;
template <typename T> class general_matrix_3x2;
template <typename T> class general_matrix_3x3;

template <typename T> class met_e3_row_dofs_type;
template <typename T> class st2_e3_row_dofs_type;

//==============================================================================
//==============================================================================

///
/// Symmetric matrix with 3 rows and 3 columns.
///
/// Class symmetric_matrix_3x3 is a special kind of matrix class intended to be
/// used in conjunction with various row_dofs_type classes (pod types).
/// The pod types will be converted (cast) to appropriate matrix types.
/// So, this class is also required to be a pod type also (ie: really just a 
/// struct with no inheritance, no constructors, no virtual functions, etc.).
///
///
template <typename T>
class symmetric_matrix_3x3
{
public:

  ///
  /// Operator to convert current to met_e3_row_dofs_type.
  ///
  operator met_e3_row_dofs_type<T>& () const;

  ///
  /// Operator to convert current to st2_e3_row_dofs_type.
  ///
  operator st2_e3_row_dofs_type<T>& () const;

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
  operator general_matrix_3x3<T> () const;

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
  T components[6];

  //============================================================================
  //============================================================================

  ///
  /// The adjoint of the matrix (pre-allocated).
  ///
  void adjoint(symmetric_matrix_3x3<T>& xresult) const;

  ///
  /// The adjoint of the matrix (auto-allocated).
  ///
  symmetric_matrix_3x3<T> adjoint() const;

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
  /// The diagonalization of the matrix (pre-allocated).
  ///
  void diagonalization(symmetric_matrix_3x3<T>& xresult) const;

  ///
  /// The diagonalization of the matrix (auto-allocated).
  ///
  symmetric_matrix_3x3<T> diagonalization() const;

  ///
  /// The identity matrix (pre-allocated).
  ///
  void identity(symmetric_matrix_3x3<T>& xresult) const;

  ///
  /// The identity matrix (auto-allocated).
  ///
  symmetric_matrix_3x3<T> identity() const;

  ///
  /// The inverse of the matrix (pre-allocated).
  ///
  void inverse(symmetric_matrix_3x3<T>& xresult) const;

  ///
  /// The inverse of the matrix (auto-allocated).
  ///
  symmetric_matrix_3x3<T> inverse() const;

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
  /// This matrix multiplied by a scalar (pre-allocated).
  ///
  void multiply(const T& xscalar, symmetric_matrix_3x3<T>& xresult) const;

  ///
  /// This matrix multiplied by a scalar (auto-allocated).
  ///
  symmetric_matrix_3x3<T> multiply(const T& xscalar) const;

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
  void multiply(const general_matrix_3x3<T>& xother,
                general_matrix_3x3<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  ///
  general_matrix_3x3<T> multiply(const general_matrix_3x3<T>& xother) const;

  ///
  /// Premultiply matrix xother by this matrix (pre-allocated).
  /// Note that multiplying 2 symmetric matrices results (in general)
  /// in a general square matrix.
  ///
  void multiply(const symmetric_matrix_3x3<T>& xother,
                general_matrix_3x3<T>& xresult) const;

  ///
  /// Premultiply matrix xother by this matrix (auto-allocated).
  /// Note that multiplying 2 symmetric matrices results (in general)
  /// in a general square matrix.
  ///
  general_matrix_3x3<T> multiply(const symmetric_matrix_3x3<T>& xother) const;

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
  void transpose(symmetric_matrix_3x3<T>& xresult) const;

  ///
  /// The transpose of the matrix (auto-allocated).
  ///
  symmetric_matrix_3x3<T> transpose() const;

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
/// Insert symmetric_matrix_3x3@<T@> xm into output stream xos.
///
template <typename T>
std::ostream& operator<<(std::ostream& xos, const symmetric_matrix_3x3<T>& xm);

///
/// Determine the eigenvectors and eigenvalues of a real symmetric matrix xm
//  using the cyclic Jacobi iteration method.
/// The eigenvalues are returned in xeigenvalues and the corresponding
/// eigenvectors in the columns of xeigenvectors.  
///
template <typename T>
void jacobi_transformation(const symmetric_matrix_3x3<T>& xm,
                           general_matrix_3x3<T>& xeigenvectors,
                           T xeigenvalues[3]);

///
/// Determine the eigenvectors and eigenvalues of a real symmetric matrix xm
//  using the cyclic Jacobi iteration method.
/// The eigenvalues are returned in the diagonal of xdiagonal and the
/// corresponding eigenvectors in the columns of xeigenvectors.  
///
template <typename T>
void jacobi_transformation(const symmetric_matrix_3x3<T>& xm,
                           general_matrix_3x3<T>& xeigenvectors,
                           symmetric_matrix_3x3<T>& xdiagonal);
///
/// Utility function to sort the eigenvalues into ascending order.
/// Called from jacobi_transformation.
///
template <typename T>
void sort_eigenvalues(general_matrix_3x3<T>& xeigenvectors,
                      T xeigenvalues[3]);

} // namespace fiber_bundle

#endif // ifndef SYMMETRIC_MATRIX_3X3_H
