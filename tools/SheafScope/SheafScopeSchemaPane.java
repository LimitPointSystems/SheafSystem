/**
 * Classname: SheafScopeSchemaPane
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScopeSchemaPane.java,v $ $Revision: 1.15 $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import bindings.java.*;

import java.awt.*;
import javax.swing.*;

/**
 * SheafScopeSchemaPane specializes <code>SheafScopeAbstractTreePane</code>
 * to allow display of schema info.<p> 
 */
public class SheafScopeSchemaPane extends SheafScopeAbstractTreePane
{

  /**
   * Constructor
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> to act upon.
   * @param xmember The current <code>poset_member</code>.
   */
  public SheafScopeSchemaPane(SheafScopePosetPane xposetPane, abstract_poset_member xmember)
  {
    super(xposetPane, xmember);

    String name = "N/A";
    try
    {
      if(xmember != null)
        name = xmember.name();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    setTitle("Schema: " + name);
  }

  /**
   *
   */
  protected void annotate()
  {}
}
