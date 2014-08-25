
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//


package com.limitpoint.tools.viewer.render;

import com.limitpoimt.tools.viewer.common.*;
import com.limitpoimt.tools.viewer.user.*;
import com.limitpoint.bindings.java.*;

import java.awt.*;
import java.util.*;
import vtk.*;

/**
 *
 * Implementation of <code>G3DFieldActor</code> for a 3 dimensional graphic
 * representation with <code>vtkGlyph3D</code>
 *
 */
public class GlyphFieldActor extends G3DFieldActor
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
   * The <code>vtkGlyph3D</code>
   */
  protected vtkGlyph3D glyph = null;

  // CONSTRUTORS

  /**
   * Default constructor
   */
  public GlyphFieldActor()
  {}

  /**
   * Constructor
   *
   * @param xcoordinates The coordinates section
   * @param xscalarProperty The scalar property section
   * @param xvectorProperty The vector property section
   * @param xlookupTable The VTK lookup table
   */
  public GlyphFieldActor(sec_vd xcoordinates,
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
   * Initialize this <code>GlyphFieldActor</code>
   */
  protected void init()
  {
    super.init();

    createGlyph();
  }

  /**
   * Create the glph
   */
  protected void createGlyph()
  {
    // Create the glyph

    glyph = new vtkGlyph3D();

    // Hook the glyph up to the data flow

    glyph.SetInput(mapperInput);
    gridMapper.SetInput(glyph.GetOutput());
  }

  /**
   * The list of psuedo color properties
   */
  public sec_vd[] getProperties()
  {
    int ct = 0;
    if(scalarProperty != null)
      ct++;
    if(vectorProperty != null)
      ct++;

    sec_vd[] result = new sec_vd[ct];

    ct = 0;
    if(scalarProperty != null)
    {
      result[ct] = scalarProperty;
      ct++;
    }
    if(vectorProperty != null)
    {
      result[ct] = vectorProperty;
    }

    return result;
  }
}
