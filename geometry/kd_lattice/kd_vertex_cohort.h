

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_vertex_cohort

#ifndef KD_VERTEX_COHORT_H
#define KD_VERTEX_COHORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef VERTEX_COHORT_H
#include "vertex_cohort.h"
#endif
 
#ifndef KD_ENUMS_H
#include "kd_enums.h"
#endif

namespace geometry
{
  
///
/// A vertex_cohort that contains only kd_vertexs.
///
class SHEAF_DLL_SPEC kd_vertex_cohort : public vertex_cohort
{

  // ===========================================================
  /// @name KD_VERTEX_COHORT FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Creates an instance with name xname and leaves cohort xleaves in xhost.
  ///
  kd_vertex_cohort(kd_lattice& xkd_host, const string& xname);  

  ///
  /// Destructor
  ///
  virtual ~kd_vertex_cohort();

  ///
  /// The kd_lattice this is part of.
  ///
  kd_lattice& kd_host();

  ///
  /// The kd_lattice this is part of, const version.
  ///
  const kd_lattice& kd_host() const;

protected:

  ///
  /// Default constructor.
  ///
  kd_vertex_cohort();

  ///
  /// The kd_lattice this is part of.
  ///
  kd_lattice* _kd_host;

private:

  //@}

  // ===========================================================
  /// @name COHORT FACET
  // ===========================================================
  //@{

public:

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
/// Insert kd_vertex_cohort& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, kd_vertex_cohort& xn);
  
} // end namespace geometry

#endif // ifndef KD_VERTEX_COHORT_H
