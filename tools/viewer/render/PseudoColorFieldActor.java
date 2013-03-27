
/**
 * Classname: PseudoColorFieldActor
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: PseudoColorFieldActor.java,v $ $Revision: 1.7 $
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
 * representation..
 *
 */
public class PseudoColorFieldActor extends G3DFieldActor
{
  // SHEAF FACET

  /**
   * The pseudo color property section
   */
  protected sec_vd property = null;

  //
  // The Filters
  //

  /**
   * The <code>vtkShrinkFilter</code>
   */
  protected vtkShrinkFilter shrinkFilter = null;

  // CONSTRUTORS

  /**
   * Default constructor
   */
  public PseudoColorFieldActor()
  {}

  /**
   * Constructor
   *
   * @param xcoordinates The coordinates section
   * @param xproperty  The property sections
   * @param xlookupTable The VTK lookup table
   */
  public PseudoColorFieldActor(sec_vd xcoordinates,
                               sec_vd xproperty,
                               LookupTable xlookupTable)
  {
    super(xcoordinates, xlookupTable);

    property = xproperty;

    init();
  }

  /**
   * The list of psuedo color properties
   */
  public sec_vd[] getProperties()
  {
    if(property == null)
      return new sec_vd[0];

    sec_vd[] result = new sec_vd[1];
    result[0] = property;

    return result;
  }
}
