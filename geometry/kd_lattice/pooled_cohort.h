// $RCSfile: pooled_cohort.h,v $ $Revision: 1.4 $ $Date: 2012/07/04 16:42:17 $

// $Name: HEAD $
//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class pooled_cohort

#ifndef POOLED_COHORT_H
#define POOLED_COHORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ABSTRACT_COHORT_H
#include "abstract_cohort.h"
#endif

namespace geometry
{
  
///
/// An abstract cohort with members that can be activated and deactivated.
///
class SHEAF_DLL_SPEC pooled_cohort : public abstract_cohort
{

  // ===========================================================
  /// @name POOLED_COHORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor
  ///
  virtual ~pooled_cohort();

  ///
  /// The id of the dof tuple for members.
  ///
  const scoped_index& dof_tuple_id() const;

  ///
  /// True if and only if sp() contains the member
  /// with id xid and it is is active.
  ///
  virtual bool is_active(const scoped_index& xid) const;

  ///
  /// Index of the inactive part; the host member which is 
  /// the poset join of all inactive members. A jim because 
  /// it's easier to maintain order if part can't be jem of top.
  ///
  const scoped_index& inactive_part_id() const;

  ///
  /// Index of the inactive bottom; the host member which is 
  /// the poset mmet of all inactive members. A jim because 
  /// it's easier to maintain order if part can't be jem of bottom.
  ///
  const scoped_index& inactive_bottom_id() const;

  ///
  /// Index of the host member in the upper cover of inactive members.
  ///
  const scoped_index& inactive_uc_id() const;

  ///
  /// Index of the host member in the lower cover of inactive members.
  ///
  const scoped_index& inactive_lc_id() const;

  ///
  /// Number of newed, inactive, and reactivated members.
  ///
  const int* cts() const;  

  ///
  /// Inserts cts() in xos.
  ///
  void output_cts(ostream& xos, const string& xaction);

protected:

  ///
  /// Default constructor.
  ///
  pooled_cohort();

  ///
  /// The id of the dof tuple.
  ///
  scoped_index _dof_tuple_id;

  ///
  /// The subposet of all inactive poset members.
  ///
  subposet _inactive_sp;

  ///
  /// Index of the inactive part; the host member which is 
  /// the poset join of all inactive members. A jim because 
  /// it's easier to maintain order if part can't be jem of top.
  ///
  scoped_index _inactive_part_id;

  ///
  /// Index of the inactive bottom; the host member which is 
  /// the poset mmet of all inactive members. A jim because 
  /// it's easier to maintain order if part can't be jem of bottom.
  ///
  scoped_index _inactive_bottom_id;

  ///
  /// Index of the least upper bound for inactive members of this set.
  ///
  scoped_index _inactive_uc_id;

  ///
  /// Index of the greatest lower bound for inactive members of this set.
  ///
  scoped_index _inactive_lc_id;

  ///
  /// Number of newed, inactive, and recycled members.
  ///
  int _cts[3];

  ///
  /// Initializes the structure for activating and inactivating members..
  ///
  void initialize_inactivation_structure(const string& xname);

  ///
  /// Initializes the subposet of inactive members.
  ///
  void initialize_inactive_sp();
  
  ///
  /// Initializes bounds for all inactive members.
  ///
  void initialize_global_bounds();
  
  ///
  /// Initializes bounds for inactive members of this set.
  ///
  void initialize_local_bounds(const string& xname);

private:

  //@}

  // ===========================================================
  /// @name ABSTRACT_COHORT FACET
  // ===========================================================
  //@{

public:

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
  /// Action to be taken after creating a new member.
  ///
  virtual void post_creation_action(const scoped_index& xnew_mbr_id);

private:

  //@}
 

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert pooled_cohort& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, pooled_cohort& xn);
  
} // end namespace geometry

#endif // ifndef POOLED_COHORT_H
