
/**
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
 * 
 */


package tools.SheafScope;

/**
 *  A collection of constants used by SheafScope.
 * <p>
 *
 * @version 1.0 06/24/00
 * @author Bill Mason
 */
public interface SheafScopeConstants
{
  /**
   * The icon for title bars.
   */
  public static final String MAIN_ICON = "lps_logo.png";

  /**
   * The icon for wait events.
   */
  public static final String WAIT_ICON = "wait.png";

  /**
   * The HTML file for help (usersGuide).
   */
  public static final String USERS_GUIDE = "tableOfContents.html";

  /**
   * The HTML file for about.
   */
  public static final String ABOUT = "about.html";

  /**
   * Relative path to the documentation used by SheafScope
   * (always ends with '/');
   */
  public static final String DOC_PATH = "/tools/SheafScope/resources/docs/";

  /**
   * Relative path to the images used by SheafScope
   * (always ends with '/');
   */
  public static final String IMAGE_PATH = "tools/SheafScope/resources/";

  /**
   * Set to true for debugging
   */
  public static final boolean DEBUG = false;

  /**
   * The limit for the number of childern in a tree.  If number of children is
   * greater than this limit, the tree should not be expanded by default and
   * should warn the user when the user tries to expand the tree.
   */
  public static final int CHILD_LIMIT = 40;
}
