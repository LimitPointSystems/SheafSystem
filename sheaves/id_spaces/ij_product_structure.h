
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
/// Interface for class ij_product_structure

#ifndef IJ_PRODUCT_STRUCTURE_H
#define IJ_PRODUCT_STRUCTURE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ABSTRACT_PRODUCT_STRUCTURE_H
#include "abstract_product_structure.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{
  
///
/// A 2D implementation of abstract_product_structure.
///
class SHEAF_DLL_SPEC ij_product_structure : public abstract_product_structure
{

  // ===========================================================
  /// @name IJ_PRODUCT_STRUCTURE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Constructor: Set ub(0) == xi_ub and ub(1) == xj_ub.
  ///
  ij_product_structure(size_type xi_ub, size_type xj_ub);

  ///
  /// Copy constructor.
  ///
  ij_product_structure(const ij_product_structure& xother);

  ///
  /// Assignment operator
  ///
  ij_product_structure& operator=(const ij_product_structure& xother);

  ///
  /// Destructor
  ///
  virtual ~ij_product_structure();

protected:

  ///
  /// Default constructor; disabled.
  ///
  ij_product_structure() { };

  ///
  /// The upper bound in the i-direction.
  ///
  size_type _i_ub;

  ///
  /// The upper bound in the j-direction.
  ///
  size_type _j_ub;

private:

  //@}


  // ===========================================================
  /// @name ABSTRACT_PRODUCT_STRUCTURE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual ij_product_structure* clone() const;

  ///
  /// Assignment operator
  ///
  virtual ij_product_structure& operator=(const abstract_product_structure& xother);

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const abstract_product_structure& xother) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name PRODUCT FACET
  // ===========================================================
  //@{

public:

  ///
  /// The product dimension.
  ///
  virtual size_type d() const;

  ///
  /// The upper-bound for the dimension xi.
  ///
  virtual size_type ub(pod_type xi) const;

  ///
  /// The upper bound in the i-direction.
  ///
  size_type i_ub() const;

  ///
  /// The upper bound in the j-direction.
  ///
  size_type j_ub() const;

  ///
  /// 2-tuple to ordinal conversion.
  ///
  void ordinal(pod_type xi, pod_type xj, pod_type& xordinal) const;

  ///
  /// Tuple to ordinal conversion.
  ///
  virtual void ordinal(pod_type* xtuple, pod_type& xordinal) const;

  ///
  /// Ordinal to 2-tuple conversion.
  ///
  void tuple(pod_type xordinal, pod_type& xi, pod_type& xj) const;

  ///
  /// Ordinal to tuple conversion.
  ///
  virtual void tuple(pod_type xordinal, pod_type* xtuple) const;

  ///
  /// Set the upper-bounds for this product structure.
  ///
  void put_ubs(size_type xi_ub, size_type xj_ub);

  ///
  /// Set the upper-bounds for this product structure.
  ///
  virtual void put_ubs(size_type* xubs);

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

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
/// 2-tuple to ordinal conversion.
///
inline pod_index_type ordinal(pod_index_type xi,
			      pod_index_type xj, 
			      size_type xj_ub)
{
  return xi*xj_ub+xj;
};
  
///
/// Ordinal to 2-tuple conversion.
///
inline void tuple(pod_index_type x, 
		  size_type xj_ub,
		  pod_index_type& xi,
		  pod_index_type& xj)
{
  // x = xi*xj_ub + xj.

  xj = x % xj_ub;
  xi = x / xj_ub;
};
  
///
/// The deep size of ij_product_structure& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const ij_product_structure& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef IJ_PRODUCT_STRUCTURE_H
