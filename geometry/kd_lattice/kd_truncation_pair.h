// $RCSfile: kd_truncation_pair.h,v $ $Revision: 1.3 $ $Date: 2012/07/04 16:42:17 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_truncation_pair

#ifndef KD_TRUNCATION_PAIR_H
#define KD_TRUNCATION_PAIR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif
 
#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif
 
#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef STD_UTILITY_H
#include "std_utility.h"
#endif
 
namespace geometry
{
  
///
/// A pair of surface ids expessing the truncation
/// relationship at a truncation point.
///
class SHEAF_DLL_SPEC kd_truncation_pair
{

  // ===========================================================
  /// @name KD_TRUNCATION_PAIR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  kd_truncation_pair();

  ///
  /// Creates an instance with first == xfirst and second == xsecond.
  ///
  kd_truncation_pair(const sheaf::scoped_index& xfirst, const sheaf::scoped_index& xsecond);

  ///
  /// Destructor
  ///
  virtual ~kd_truncation_pair();

  ///
  /// The truncated surface.
  ///
  scoped_index truncated;

  ///
  /// The truncating surface.
  ///
  scoped_index truncating;

  ///
  /// Lexicographic ordering.
  ///
  bool operator<(const kd_truncation_pair& xother) const;
  
  ///
  /// Equality comparison.
  ///
  bool operator==(const kd_truncation_pair& xother) const;
  
  ///
  /// The transpose of this pair.
  ///
  kd_truncation_pair transpose() const;

  ///
  /// True if and only if truncated == truncating.
  ///
  bool is_reflexive() const;

protected:


private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert kd_truncation_pair& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_truncation_pair& xn);  

} // end namespace geometry

#endif // ifndef KD_TRUNCATION_PAIR_H
