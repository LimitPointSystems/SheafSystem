
/**
 * Classname: SheafScopeFilterDialog
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:52 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import tools.common.gui.*;

import java.awt.*;

/**
 * SheafScopeFilterDialog provides dialog mechanisms for subposet filtering.
 */
public class SheafScopeFilterDialog extends GenericDialog
{

  SheafScopeFilterPane filterPane;

  /**
   * Constructor
   * @param xframe The display frame.
   * @param xnames The list of usable filters.
   * @param enableRemoteX true, if remote X is enabled
   */
  public SheafScopeFilterDialog(Frame xframe, String[] xnames, boolean enableRemoteX)
  {
    super(xframe, "Filter Selection Dialog");

    filterPane = new SheafScopeFilterPane(xnames, enableRemoteX);
    addPane(filterPane, 0);
  }

  /**
   * Cancels the dialog.<p>
   *
   * 
   */
  public void cancelPressed()
  {
    filterPane.cancel();
    setVisible(false);
  }

  /**
   * Accepts the selected filter.<p>
   *
   * 
   */
  public void okPressed()
  {
    filterPane.confirm();
    setVisible(false);
  }

  /**
   * Retrieves the direction of the selection.<p>
   * 
   * @return true if direction is down.
   */
  public boolean directionIsDown()
  {
    return filterPane.directionIsDown();
  }

  /**
   * Confirms the selection as "strict".<p>
   *
   * @return true if selection is "strict".
   */
  public boolean isStrict()
  {
    return filterPane.isStrict();
  }

  /**
   * gets the name of the filter subPoset.<p>
   *
   * @return The filter subPoset name.
   */
  public String getSubposetName()
  {
    return filterPane.getSubposetName();
  }

}

