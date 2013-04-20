

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class cohort

#ifndef COHORT_H
#define COHORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ABSTRACT_COHORT_H
#include "abstract_cohort.h"
#endif

namespace geometry
{
  
///
/// A group of poset members identified by a subposet and a gathered id space; 
/// also has an arbitrary client-defined id space.
///
class SHEAF_DLL_SPEC cohort : public abstract_cohort
{

  // ===========================================================
  /// @name COHORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a cohort with name xname in  xhost.
  ///
  cohort(base_space_poset& xhost, const string& xname, bool xauto_update_id_space);

  ///
  /// Destructor
  ///
  virtual ~cohort();

  /// @issue Cohort insert_member/remove_member interface is
  /// unncessarily inconsistent with the new_member/delete_member
  /// interface of the rest ogf the abstract_cohort hierarchy.

  ///
  /// Inserts the member with id xid.
  ///
  void insert_member(const scoped_index& xid);

  ///
  /// Removes the member with id xid. If xupdate_id_space_extrema
  /// and auto_update_id_space(), updates the extrema of the
  /// id space, which may be an expensive operation.
  ///
  void remove_member(const scoped_index& xid, bool xupdate_id_space_extrema = true);

  ///
  /// True if and only if insert_member and remove_member
  /// automatically update the id space.
  ///
  bool auto_update_id_space() const;
  

protected:

  ///
  /// Default constructor.
  ///
  cohort();

  ///
  /// True if and only if insert_member and remove_member
  /// automatically update the id space.
  ///
  bool _auto_update_id_space;

private:

  //@}


};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // end namespace geometry

#endif // ifndef COHORT_H
