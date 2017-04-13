
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
/// Interface for class tensor_variance

#ifndef TENSOR_VARIANCE_H
#define TENSOR_VARIANCE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef STD_BITSET_H
#include "SheafSystem/std_bitset.h"
#endif

#ifndef STD_LIMITS_H
#include "SheafSystem/std_limits.h"
#endif

namespace fiber_bundle
{

///
/// The "type" of a tensor; specifies the degree and the co- or 
/// contra-variance for each index of a tensor.
///
/// A general tensor is defined as a multilinear map of one or more
/// vector and/or covector variables to the reals. The specification
/// of the number of variables and which are vectors and which are
/// covectors is referred to as the type of the tensor, but there
/// appear to be two approaches in the literature to how precisely
/// the type must be specified. Bishop & Goldberg choose to always
/// order the variables so the covectors come first, so the type is
/// entirely specified by the number of covector variables (contravariant
/// degree) and the number of vector variables (covariant degree).
/// But if we have a metric handy and can raise and lower indices 
/// it's not entirely clear how the implied reordering of the variables
/// works. Dodson & Poston argue that's its more convenient to not
/// assume any particular order of the variables but then the type
/// must define the co- or contra-variance for each variable in order.
///
/// This class follows the Dodson and Poston approach and specifies 
/// the variance for each index using a bit vector.
///
class SHEAF_DLL_SPEC tensor_variance
{

  //==============================================================================
  /// @name TENSOR_VARIANCE FACET
  //==============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  tensor_variance();
  
  ///
  /// Copy constructor.
  ///
  tensor_variance(const tensor_variance& xother);
  
  ///
  /// Creates an instance with degree = xp
  /// and all indices contravariant.
  ///
  tensor_variance(int xp);

  ///
  /// Destructor; not virtual, this can not be a base class.
  ///
  ~tensor_variance();

  ///
  /// Assignment operator.
  ///
  tensor_variance& operator=(const tensor_variance& xother);
  
  ///
  /// Equality comparison operator.
  ///
  bool operator==(const tensor_variance& xother) const;

  ///
  /// The largest value of p this implementation will support.
  ///
  static int capacity();

  ///
  /// The tensor degree.
  ///
  int p() const;
  
  ///
  /// The variance of the xi-th index; 
  /// covariant if true, contravariant if false.
  ///
  bool variance(int xi) const;
  
  ///
  /// Sets the variance of the xi-th index to xvalue.
  ///
  void put_variance(int xi, bool xvalue);

  ///
  /// Sets the variance of all indices to xvalue.
  ///
  void put_variance(bool xvalue);

  ///
  /// True if and only if the xi-th index is covariant;
  /// synonym for variance(xi).
  ///
  bool is_covariant(int xi) const;

  ///
  /// True if and only if all indices are covariant.
  ///
  bool is_covariant() const;

  ///
  /// True if and only if the xi-th index is covariant;
  /// synonym for !variance(xi).
  ///
  bool is_contravariant(int xi) const;

  ///
  /// True if and only if all indices are contravariant.
  ///
  bool is_contravariant() const;

  ///
  /// True if and only if there exists at least one index
  /// that is covariant and at least one that is contravariant.
  ///
  bool is_mixed() const;

  ///
  /// True if and only if all indices are covariant or
  /// all indices are contravariant.
  ///
  bool is_pure() const;
  
  ///
  /// Sets all indices the same as index 0.
  ///
  void purify();

protected:
private:
  
  ///
  /// The tensor degree.
  ///
  int _p;
  
  ///
  /// The type used to specify the "variance" of each index.
  ///
  typedef std::bitset<std::numeric_limits<unsigned long int>::digits> variance_type;

  ///
  /// The variance of the xi-th index; 
  /// covariant if true, contravariant if false.
  ///
  variance_type _variance;
  
  //@}
};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// The variance of the contration of a tensor with variance x0
/// on indices xp and xq.
///
SHEAF_DLL_SPEC tensor_variance contract(const tensor_variance& x0, int xp, int xq);

///
/// The variance of the tensor product of tensors with variance x0 and x1.
///
SHEAF_DLL_SPEC tensor_variance tensor_product(const tensor_variance& x0, const tensor_variance& x1);

///
/// The variance of the hook of a tensor with variance x0.
///
SHEAF_DLL_SPEC tensor_variance hook(const tensor_variance& x0);

///
/// The variance of the Hodge star of a tensor with variance x0
/// over a vector space of dimension xdd.
///
SHEAF_DLL_SPEC tensor_variance star(const tensor_variance& x0, int xdd);

///
/// The variance of the wedge of a tensor with variance x0 with
/// a tnesor with variance x1.
///
SHEAF_DLL_SPEC tensor_variance wedge(const tensor_variance& x0, const tensor_variance& x1);

///
/// The variance of the raise of a tensor with variance x0 on index xi.
///
SHEAF_DLL_SPEC tensor_variance raise(const tensor_variance& x0, int xi);

///
/// The variance of the lower of a tensor with variance x0 on index xi.
///
SHEAF_DLL_SPEC tensor_variance lower(const tensor_variance& x0, int xi);

} // namespace fiber_bundle


#endif // ifndef TENSOR_VARIANCE_H
