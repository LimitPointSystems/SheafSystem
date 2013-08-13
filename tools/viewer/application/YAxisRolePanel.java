/**
 *  Classname: YAxisRolePanel
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:57 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.application;

import bindings.java.*;

import javax.swing.*;

/**
 * Implementation of <code>ScalarRolePanel</code> for a y-axis section.
 */
public class YAxisRolePanel extends ScalarRolePanel
{
  /**
   * The constructor
   */
  public YAxisRolePanel()
  {
    super();
  }

  /**
   * Return the role text
   */
  protected String getRole()
  {
    return "Y-Axis Section";
  }
}
