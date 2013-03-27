
/**
 * Classname: HedgeHogFieldActor
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: HedgeHogFieldActor.java,v $ $Revision: 1.7 $
 *
 * $Date: 2013/01/12 17:18:00 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.render;

import tools.viewer.common.*;
import tools.viewer.user.*;
import bindings.java.*;

import java.awt.*;
import java.util.*;
import vtk.*;

/**
 *
 * Implementation of <code>G3DFieldActor</code> for a 3 dimensional graphic
 * representation with <code>vtkHedgeHog</code>
 *
 */
public class HedgeHogFieldActor extends G3DFieldActor
{
  // SHEAF FACET

  /**
   * The scalar property section
   */
  protected sec_vd scalarProperty = null;

  /**
   * The vector property section
   */
  protected sec_vd vectorProperty = null;

  //
  // The Filters
  //

  /**
   * The <code>vtkHedgeHog</code>
   */
  protected vtkHedgeHog hedgeHog = null;

  // CONSTRUTORS

  /**
   * Default constructor
   */
  public HedgeHogFieldActor()
  {}

  /**
   * Constructor
   *
   * @param xcoordinates The coordinates section
   * @param xscalarProperty The scalar property section
   * @param xvectorProperty The vector property section
   * @param xlookupTable The VTK lookup table
   */
  public HedgeHogFieldActor(sec_vd xcoordinates,
                            sec_vd xscalarProperty,
                            sec_vd xvectorProperty,
                            LookupTable xlookupTable)
  {
    super(xcoordinates, xlookupTable);

    scalarProperty = xscalarProperty;
    vectorProperty = xvectorProperty;

    init();
  }

  /**
   * Initialize this <code>HedgeHogFieldActor</code>
   */
  protected void init()
  {
    super.init();

    createHedgeHog();
  }

  /**
   * Create the glph
   */
  protected void createHedgeHog()
  {
    // Create the hedge hog

    hedgeHog = new vtkHedgeHog();

    // Hook the hedge hog up to the data flow

    hedgeHog.SetInput(mapperInput);
    gridMapper.SetInput(hedgeHog.GetOutput());
  }

  /**
   * The list of psuedo color properties
   */
  public sec_vd[] getProperties()
  {
    int ct = 1;
    if(scalarProperty != null)
      ct++;

    sec_vd[] result = new sec_vd[ct];

    ct = 0;
    if(scalarProperty != null)
    {
      result[ct] = scalarProperty;
      ct++;
    }
    result[ct] = vectorProperty;

    return result;
  }
}
