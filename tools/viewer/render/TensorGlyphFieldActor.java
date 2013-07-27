
/**
 * Classname: TensorGlyphFieldActor
 *
 * @author $Author: jebutler $
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
 * representation with <code>vtkTensorGlyph</code>
 *
 */
public class TensorGlyphFieldActor extends G3DFieldActor
{
  // SHEAF FACET

  /**
   * The scalar property section
   */
  protected sec_vd scalarProperty = null;

  /**
   * The tensor property section
   */
  protected sec_vd tensorProperty = null;

  //
  // The Filters
  //

  /**
   * The <code>vtkTensorGlyph</code>
   */
  protected vtkTensorGlyph tensorGlyph = null;

  // CONSTRUTORS

  /**
   * Default constructor
   */
  public TensorGlyphFieldActor()
  {}

  /**
   * Constructor
   *
   * @param xcoordinates The coordinates section
   * @param xscalarProperty The scalar property section
   * @param xtensorProperty The tensor property section
   * @param xlookupTable The VTK lookup table
   */
  public TensorGlyphFieldActor(sec_vd xcoordinates,
                               sec_vd xscalarProperty,
                               sec_vd xtensorProperty,
                               LookupTable xlookupTable)
  {
    super(xcoordinates, xlookupTable);

    scalarProperty = xscalarProperty;
    tensorProperty = xtensorProperty;

    init();
  }

  /**
   * Initialize this <code>TensorGlyphFieldActor</code>
   */
  protected void init()
  {
    super.init();

    createTensorGlyph();
  }

  /**
   * Create the glph
   */
  protected void createTensorGlyph()
  {
    // Create the tensor glyph

    tensorGlyph = new vtkTensorGlyph();

    // Hook the tensor glyph up to the data flow

    tensorGlyph.SetInput(mapperInput);
    gridMapper.SetInput(tensorGlyph.GetOutput());
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
    result[ct] = tensorProperty;

    return result;
  }
}
