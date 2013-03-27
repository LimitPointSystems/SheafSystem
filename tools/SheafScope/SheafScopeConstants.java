/**
 * Classname: SheafScopeConstants
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScopeConstants.java,v $ $Revision: 1.18 $
 *
 * $Date: 2013/01/12 17:17:52 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
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
