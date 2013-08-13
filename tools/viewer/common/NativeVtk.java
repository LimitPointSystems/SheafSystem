/**
 *  Classname: NativeVtk
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:57 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.common;

import vtk.vtkObject;

/**
 *
 */
public class NativeVtk
{
  /**
   *  Get the pointer (address) for a vtkObject instance.
   */
  public static long getCppPointer(vtkObject xobj)
  {
    return getCppPointerNative(xobj, xobj.GetClassName());
  }

  //===========================================================================
  // Native methods.
  //===========================================================================

  /**
   *  Get the pointer (address) for a vtkObject instance (native method).
   */
  private static native long getCppPointerNative(vtkObject xobj,
      String xclass_name);
}

