/**
 *  Classname: ViewerClientApplication
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:57 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.application;

import bindings.java.*;
import tools.viewer.user.*;

import java.awt.*;

/**
 * Interface implemented by clients of the <code>Viewer</code>
 */
public interface ViewerClientApplication
{
  /**
   * Bring this application to the foreground
   */
  public void toForeground();

  /**
   * Get the <code>namespace_poset</code> for xname
   */
  public namespace_poset getNamespace(String xname);

  /**
   * Get the grid builder
   */
  public vtk_abstract_grid_builder getGridBuilder();

  /**
   * Set the selected viewer
   */
  public void setSelectedViewer(Viewer xviewer);

  /**
   * The frame of the application
   */
  public Frame getFrame();
}
