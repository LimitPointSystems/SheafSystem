
/**
 * Classname: LookupTable
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:00 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.render;

import bindings.java.*;
import java.io.*;

import vtk.*;

/**
 *
 * Implementation of <code>vtkLookupTable</code> which provides
 * interfaces use on the <code>Stage</code>
 *
 */
public class LookupTable extends vtkLookupTable
{
  /**
   * Constructor
   */
  public LookupTable()
  {}

  // LOOKUP TABLE FACET

  /**
   * Return the scalar range.  The default is null and means
   * the scalar range is undefined by the lookup table.
   */
  public double[] getScalarRange()
  {
    return null;
  }

  /**
   * The format of the <code>vtkScalarBarActor</code> labels.
   */
  public String getLabelFormat()
  {
    return "%6.2f";
  }
}
