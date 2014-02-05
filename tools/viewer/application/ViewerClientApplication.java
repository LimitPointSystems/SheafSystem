
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
