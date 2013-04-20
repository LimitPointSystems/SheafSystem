

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class vertex_cohort

#ifndef VERTEX_COHORT_H
#define VERTEX_COHORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef D_CELLS_COHORT_H
#include "d_cells_cohort.h"
#endif

namespace geometry
{
  
///
/// A d_cells_cohort that contains only vertices.
///
class SHEAF_DLL_SPEC vertex_cohort : public d_cells_cohort
{

  // ===========================================================
  /// @name VERTEX_COHORT FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Creates an instance with name xname in xhost.
  ///
  vertex_cohort(base_space_poset& xhost, const string& xname, const string& xmember_prototype_name = "point");  

  ///
  /// Destructor
  ///
  virtual ~vertex_cohort();

protected:

  ///
  /// Default constructor.
  ///
  vertex_cohort();

  ///
  /// Index of bottom.
  ///
  scoped_index _bottom_id;

private:

  //@}

  // ===========================================================
  /// @name COHORT FACET
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
/// Insert vertex_cohort& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, vertex_cohort& xn);
  
} // end namespace geometry

#endif // ifndef VERTEX_COHORT_H
