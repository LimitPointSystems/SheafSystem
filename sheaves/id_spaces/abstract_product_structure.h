// $RCSfile: abstract_product_structure.h,v $ $Revision: 1.2 $ $Date: 2013/01/10 13:54:45 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class abstract_product_structure

#ifndef ABSTRACT_PRODUCT_STRUCTURE_H
#define ABSTRACT_PRODUCT_STRUCTURE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
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
