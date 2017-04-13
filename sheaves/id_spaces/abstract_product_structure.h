
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
/// Interface for class abstract_product_structure

#ifndef ABSTRACT_PRODUCT_STRUCTURE_H
#define ABSTRACT_PRODUCT_STRUCTURE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "SheafSystem/any.h"
#endif

#ifndef POD_TYPES_H
#include "SheafSystem/pod_types.h"
#endif

namespace sheaf
{
  
///
/// An abstract class that defines the product structure for an id space.
///
class SHEAF_DLL_SPEC abstract_product_structure : public any
{

  // ===========================================================
  /// @name ABSTRACT_PRODUCT_STRUCTURE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" index type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// Destructor
  ///
  virtual ~abstract_product_structure();

  ///
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual abstract_product_structure* clone() const = 0;

  ///
  /// Assignment operator
  ///
  virtual abstract_product_structure& operator=(const abstract_product_structure& xother) = 0;

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const abstract_product_structure& xother) const = 0;

protected:

  ///
  /// Default constructor; disabled.
  ///
  abstract_product_structure() { };

  ///
  /// Copy constructor; disabled.
  ///
  abstract_product_structure(const abstract_product_structure& xother) { };

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
  virtual size_type d() const = 0;

  ///
  /// The upper-bound for the dimension xi.
  ///
  virtual size_type ub(pod_type xi) const = 0;

  ///
  /// Tuple to ordinal conversion.
  ///
  virtual void ordinal(pod_type* xtuple, pod_type& xordinal) const = 0;

  ///
  /// Ordinal to tuple conversion.
  ///
  virtual void tuple(pod_type xordinal, pod_type* xtuple) const = 0;

  ///
  /// The upper-bound of the ordinal.
  ///
  size_type ordinal_ub() const;

  ///
  /// Set the upper-bounds for this product structure.
  ///
  virtual void put_ubs(size_type* xubs) = 0;

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
 
} // end namespace sheaf

#endif // ifndef ABSTRACT_PRODUCT_STRUCTURE_H
