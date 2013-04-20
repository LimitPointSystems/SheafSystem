

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class d_cells_cohort

#ifndef D_CELLS_COHORT_H
#define D_CELLS_COHORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POOLED_COHORT_H
#include "pooled_cohort.h"
#endif
 
namespace geometry
{
  
///
/// A pooled_cohort with members that are also d_cells for some fixed d.
///
class SHEAF_DLL_SPEC d_cells_cohort : public pooled_cohort
{

  // ===========================================================
  /// @name D_CELLS_COHORT FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Creates an instance in xhost with name xname and dof tuple 
  /// from prototype with name xmember_prototype_name.
  ///
  d_cells_cohort(base_space_poset& xhost, 
	      const string& xname, 
	      const string& xmember_prototype_name);  

  ///
  /// Destructor
  ///
  virtual ~d_cells_cohort();

  ///
  /// The d_cells subposet containing members of this cohort.
  ///
  const subposet& d_cells_sp() const;

  ///
  /// The dimension of the cells.
  ///
  int d() const;

  ///
  /// True if and only if this contains the poset member with id xid;
  /// synonym for d_cells_sp().contains_member(xid).
  ///
  bool d_cells_contains(const scoped_index& xid) const;

  ///
  /// True if and only if d_cells_sp() contains
  /// the member with id xid and it is active.
  ///
  virtual bool d_cells_is_active(const scoped_index& xid) const;

protected:

  ///
  /// Default constructor.
  ///
  d_cells_cohort();

  ///
  /// The d_cells subposet.
  ///
  subposet _d_cells_sp;

  ///
  /// The dimension of the cells.
  ///
  int _d;

  
  

private:

  //@}

  // ===========================================================
  /// @name COHORT FACET
  // ===========================================================
  //@{

public:

protected:
  
  ///
  /// Creates an instance in xhost with name xname and dof tuple 
  /// from prototype with name xmember_prototype_name.
  ///
  void new_state(base_space_poset& xhost, 
		 const string& xname, 
		 const string& xmember_prototype_name);

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
/// Insert d_cells_cohort& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, d_cells_cohort& xn);
  
} // end namespace geometry

#endif // ifndef D_CELLS_COHORT_H
