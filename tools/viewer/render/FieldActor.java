
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

import java.util.*;
import vtk.*;

/**
 *
 * Abstract class for sheaf field graphic representation. A
 * <code>FieldActor</code> contains three graphic representations;
 * a field representation, a coordinate fiber representation, and a
 * property fiber representation.
 *
 */
public abstract class FieldActor
{
  // SHEAF FACET

  /**
   * The coordinates section.
   */
  protected sec_vd coordinates = null;

  // VTK FACET

  /**
   * The field representation of this instance.
   */
  protected vtkProp fieldRep;

  /**
   * The coordinate fiber representation
   */
  protected vtkProp coordinateFiberRep;

  /**
   * The property fiber representation
   */
  protected vtkProp propertyFiberRep;

  /**
   * The vtk data set of this instance.
   */
  protected vtkDataSet dataSet;


  // CONSTRUCTORS

  /**
   * Default constructor
   */
  public FieldActor()
  {}

  /**
   * Constructor
   *
   * @param xcoordinates The coordinates section
   */
  protected FieldActor(sec_vd xcoordinates)
  {
    coordinates = xcoordinates;
  }

  // SHEAF FACET

  /**
   *  Accessor for the coordinates section.
   *
   *  @return The coordinates section for this instance.
   */
  public sec_vd getCoordinates()
  {
    return coordinates;
  }

  /**
   *  Accessor for the property sections.
   *
   *  @return The list of property sections.
   */
  public abstract sec_vd[] getProperties();

  /**
   * Detach the sections for this actor.
   */
  public void detachStates()
  {
    getCoordinates().detach_from_state();

    sec_vd[] properties = getProperties();
    for(int i = 0; i < properties.length; i++)
    {
      properties[i].detach_from_state();
    }
  }

  // VTK FACET

  /**
   * Add this actor to xrenderer.
   */
  public abstract void addTo(vtkRenderer xrenderer);

  /**
   * Remove this actor from xrenderer.
   */
  public abstract void removeFrom(vtkRenderer xrenderer);

  /**
   * Force modification the VTK components.
   */
  public abstract void modify();

  /**
   * True, if the field has been modified
   */
  public boolean isModified()
  {
    try
    {
      if(coordinates.state_is_modified())
        return true;

      sec_vd[] props = getProperties();
      for(int i=0; i<props.length; i++)
      {
        if(props[i].state_is_modified())
          return true;
      }
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }

    return false;
  }

  /**
   * Clear the modify bit of the sections.
   */
  public void clearIsModified()
  {
    try
    {
      coordinates.clear_state_is_modified();

      sec_vd[] props = getProperties();
      for(int i=0; i<props.length; i++)
      {
        props[i].clear_state_is_modified();
      }
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }
  }

  /**
   * Set the renderer for this <code>FieldActor</code>
   */
  public void setRenderer(vtkRenderer xrenderer)
  {
    // ABSTRACT
  }
  /**
   * Accessor for the field representation.
   *
   * @return vtkProp field representation.
   */
  public vtkProp getFieldRep()
  {
    return fieldRep;
  }

  /**
   * Accessor for the coordinate fiber representation.
   *
   * @return vtkProp coordinate fiber representation.
   */
  public vtkProp getCoordinateFiberRep()
  {
    return coordinateFiberRep;
  }

  /**
   * Accessor for the property fiber representation.
   *
   * @return vtkProp property fiber representation.
   */
  public vtkProp getPropertyFiberRep()
  {
    return propertyFiberRep;
  }

  /**
   * Accessor for the VTK data set.
   *
   * @return vtkDataSet VTK data set.
   */
  public vtkDataSet getDataSet()
  {
    return dataSet;
  }

}
