
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
