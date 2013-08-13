/**
 *  Classname: ScalarRolePanel
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
 * Implementation of <code>RolePanel</code> for a scalar section.
 */
public class ScalarRolePanel extends RolePanel
{
  /**
   * The constructor
   */
  public ScalarRolePanel()
  {
    super();
  }

  /**
   * Return the role text
   */
  protected String getRole()
  {
    return "Scalar Property Section";
  }

  /**
   * True, if the role can be filled by xsection
   */
  protected boolean canFillRole(sec_vd xsection)
  {
    try
    {
      int df = xsection.df();
      if(df == 1)
        return true;
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }

    return false;
  }
}
