// $RCSfile: kd_display.h,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:30 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_display

#ifndef KD_DISPLAY_H
#define KD_DISPLAY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef GEOMETRY_H
#include "geometry.h"
#endif

#ifdef USE_VTK

class vtkRenderer;
class vtkRenderWindow;
class vtkRenderWindowInteractor;

#endif // USE_VTK

namespace geometry
{

class kd_lattice;
  
///
/// A class for displaying a kd lattice in VTK.
///
class SHEAF_DLL_SPEC kd_display
{

  // ===========================================================
  /// @name KD_DISPLAY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  kd_display();

  ///
  /// Destructor; not virtual, can not be a base class.
  ///
  ~kd_display();

  ///
  /// Display the kd lattice xkdl.
  ///
  void display(kd_lattice& xkdl, bool xexploded);

  ///
  /// Display the subvolumes in kd lattice xkdl.
  ///
  void display_subvolumes(kd_lattice& xkdl, bool xexploded);

  ///
  /// If true, display point labels.
  ///
  bool display_point_labels;

  ///
  /// If true, display zone labels.
  ///
  bool display_zone_labels;

protected:

  ///
  /// Copy constructor; Disabled.
  ///
  kd_display(const kd_display& xother) {};

private:

#ifdef USE_VTK

  ///
  /// The vtk renderer.
  ///
  vtkRenderer* _renderer;

  ///
  /// The vtk render window.
  ///
  vtkRenderWindow* _window;

  ///
  /// The vtk render window interactor.
  ///
  vtkRenderWindowInteractor* _interactor;

  ///
  /// The scale for the viewing transformation.
  ///
  double _scale[3];

  ///
  /// The origin for the viewing transformation.
  ///
  double _origin[3];

#endif // USE_VTK

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // end namespace geometry

#endif // ifndef KD_DISPLAY_H
