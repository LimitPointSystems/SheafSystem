

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_face_cohort

#ifndef KD_FACE_COHORT_H
#define KD_FACE_COHORT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef D_CELLS_COHORT_H
#include "d_cells_cohort.h"
#endif

#ifndef KD_ENUMS_H
#include "kd_enums.h"
#endif

namespace geometry
{
  
///
/// A d_cells_cohort that contains only kd_faces of a given alignment.
///
class SHEAF_DLL_SPEC kd_face_cohort : public d_cells_cohort
{

  // ===========================================================
  /// @name KD_FACE_COHORT FACET
  // ===========================================================
  //@{

public:
  
  ///
  /// Creates an instance with name xname in xhost.
  ///
  kd_face_cohort(kd_lattice& xkd_host, const string& xname, kd_alignment xalignment);  

  ///
  /// Destructor
  ///
  virtual ~kd_face_cohort();

  ///
  /// The kd_lattice this is part of.
  ///
  kd_lattice& kd_host();

  ///
  /// The kd_lattice this is part of, const version.
  ///
  const kd_lattice& kd_host() const;

  ///
  /// Mark the zone with id xod as nolonger being a leaf.
  ///
  void unleaf(const scoped_index& xid);

  ///
  /// The alignment of faces in this cohort.
  ///
  kd_alignment alignment() const;

protected:

  ///
  /// Default constructor.
  ///
  kd_face_cohort();

  ///
  /// The kd_lattice this is part of.
  ///
  kd_lattice* _kd_host;

  ///
  /// The alignment of faces in this cohort.
  ///
  kd_alignment _alignment;

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
/// Insert kd_face_cohort& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, kd_face_cohort& xn);
  
} // end namespace geometry

#endif // ifndef KD_FACE_COHORT_H
