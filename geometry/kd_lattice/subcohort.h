

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class subcohort

#ifndef SUBCOHORT_H
#define SUBCOHORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef COHORT_H
#include "cohort.h"
#endif
 
namespace geometry
{
  class pooled_cohort;
  
///
/// A cohort which is included in another pooled_cohort.
///
class SHEAF_DLL_SPEC subcohort : public abstract_cohort
{

  // ===========================================================
  /// @name SUBCOHORT FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Creates the feature in xhost with name xname.
  ///
  subcohort(base_space_poset& xhost, const string& xname, pooled_cohort& xbase_cohort);

  ///
  /// Destructor
  ///
  virtual ~subcohort();

  ///
  /// The cohort this is a subcohort of, const version.
  ///
  pooled_cohort& base_cohort();

  ///
  /// The cohort this is a subcohort of, const version.
  ///
  const pooled_cohort& base_cohort() const;

  ///
  /// True if base_cohort() is a vertex_cohort.
  ///
  bool is_vertex_cohort() const;

  ///
  /// True if and only if the member with id xid is active.
  ///
  virtual bool is_active(const scoped_index& xid) const;

  ///
  /// Activates a member, creates it if there are no inactive members.
  ///
  virtual scoped_index new_member();

  ///
  /// Deactivates the member with id xid.
  ///
  virtual void delete_member(const scoped_index& xid);

protected:

  ///
  /// Default constructor.
  ///
  subcohort();

  ///
  /// The cohort this is a subcohort of.
  ///
  pooled_cohort* _base_cohort;

private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert subcohort& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, subcohort& xn);
  
} // end namespace geometry

#endif // ifndef SUBCOHORT_H
