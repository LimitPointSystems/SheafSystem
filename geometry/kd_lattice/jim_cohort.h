

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class jim_cohort

#ifndef JIM_COHORT_H
#define JIM_COHORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POOLED_COHORT_H
#include "pooled_cohort.h"
#endif
 
namespace geometry
{
  
///
/// A pooled_cohort with members that are join irreducible members but not d-cells.
///
class SHEAF_DLL_SPEC jim_cohort : public pooled_cohort
{

  // ===========================================================
  /// @name JIM_COHORT FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Creates an instance in xhost with name xname and dof tuple 
  /// from prototype with name xmember_prototype_name.
  ///
  jim_cohort(base_space_poset& xhost, 
	     const string& xname, 
	     const string& xmember_prototype_name);  

  ///
  /// Destructor
  ///
  virtual ~jim_cohort();
  

protected:

  ///
  /// Default constructor.
  ///
  jim_cohort();

private:

  //@}

  // ===========================================================
  /// @name COHORT FACET
  // ===========================================================
  //@{

public:

  // Appears to be no reason to refine these and
  // it is extremely desirabel to have as few
  // implementations as possible.

//   ///
//   /// Activates a member, creates it if there are no inactive members.
//   ///
//   virtual scoped_index new_member();

//   ///
//   /// Deactivates the member with id xid.
//   ///
//   virtual void delete_member(const scoped_index& xid);

protected:

private:

  //@}
 

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert jim_cohort& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, jim_cohort& xn);
  
} // end namespace geometry

#endif // ifndef JIM_COHORT_H
