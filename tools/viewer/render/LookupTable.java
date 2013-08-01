
/**
 * Classname: LookupTable
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:00 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc. 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
