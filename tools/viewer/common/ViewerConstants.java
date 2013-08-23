
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

package tools.viewer.common;

import tools.viewer.user.*;
import tools.viewer.render.*;

import java.awt.*;

/**
 *  A collection of constants used by Viewer.
 */
public class ViewerConstants
{
  // VIEWER FACET

  /**
   * The title for the application frame title bar.
   */
  public static final String TITLE = "Viewer";

  /**
   * The icon for title bars.
   */
  public static final String MAIN_ICON = "LPSLogo.png";

  /**
   * The HTML file for help (usersGuide).
   */
  public static final String USERS_GUIDE = "UsersGuide.html";

  /**
   * The HTML file for about page.
   */
  public static final String ABOUT = "About.html";

  /**
   * Relative path to the documentation used by the viewer
   * (always befins and ends with '/').
   */
  public static final String DOC_PATH = "/tools/viewer/resources/docs/";

  /**
   * Relative path to the images used by  by the viewer
   * (always ends with '/').
   */
  public static final String IMAGE_PATH = "tools/viewer/resources/";

  /**
   * Set to true for debugging.
   */
  public static final boolean DEBUG = false;

  /**
   * Image formats
   */
  public static enum ImageFormat { BMP, JPEG, PNG, PNM, POSTSCRIPT, TIFF }

  // VTK FACET

  /**
   * Integer value for true.
   */
  public static final int TRUE = 1;

  /**
   * Integer value for false
   */
  public static final int FALSE = 0;

  // ACTOR FACET

  /**
   * Joystick interactor style
   */
  public static final int JOYSTICK_INTERACTOR  = 0;

  /**
   * Trackball interactor style
   */
  public static final int TRACKBALL_INTERACTOR   = 2;

  /**
   * Camera interactor style
   */
  public static final int CAMERA_INTERACTOR = 3;

  /**
   * Actor interactor style
   */
  public static final int ACTOR_INTERACTOR  = 4;

  /**
   * Point style representation.
   */
  public static final int POINT_STYLE   = 0;

  /**
   * Line style representation.
   */
  public static final int LINE_STYLE    = 1;

  /**
   * Surface style representation
   */
  public static final int SURFACE_STYLE = 2;

  // RANGLE LOOKUP TABLE FACET

  /**
   * Intensity component
   */
  public static final String INTENSITY = "Intensity";

  /**
   * Saturation component
   */
  public static final String SATURATION = "Saturation";

  /**
   * The components for the threshold.
   */
  public static final String[] THRESHOLD_COMPONENTS =
    { INTENSITY, SATURATION };

  /**
   * Constant method
   */
  public static final String CONSTANT = "CONSTANT";

  /**
   * Ramp method
   */
  public static final String RAMP = "RAMP";

  /**
   * The methods for the threshold
   */
  public static final String[] THRESHOLD_METHODS =
    { CONSTANT, RAMP };

  // SCRIPT FACET

  /**
   * Short way interpolation method.
   */
  public static final int SHORT_INTERPOLATION = 0;

  /**
   * Long way interpolation method.
   */
  public static final int LONG_INTERPOLATION  = 1;

  // GLYPH SOURCE FACET

  /**
   * Sphere source
   */
  public static final String SPHERE = "Sphere";

  /**
   * Cone source
   */
  public static final String CONE = "Cone";

  /**
   * Cylinder source
   */
  public static final String CYLINDER = "Cylinder";

  /**
   * The supported sources
   */
  public static final String[] SOURCES = {SPHERE, CONE, CYLINDER};

  // GLYPH DATA TYPES

  /**
   * Scalar data
   */
  public static final String SCALAR = "Scalar";

  /**
   * Vector magnitude data
   */
  public static final String VECTOR_MAGNITUDE = "Vector Magnitude";

  /**
   * Vector component data
   */
  public static final String VECTOR_COMPONENTS = "Vector Components";

  /**
   * Vector normal data
   */
  public static final String VECTOR_NORMAL = "Vector Normal";

  // LABEL TYPE

  /**
   * No id labels.
   */
  public static final int NO_IDS = 0;

  /**
   * Top id labels.
   */
  public static final int TOP_IDS = 1;

  /**
   * Discretization/Evaluation id lables.
   */
  public static final int DISC_EVAL_IDS = 2;
}
