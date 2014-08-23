
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

package com.limitpoint.tools.SheafScope;

import com.limitpoimt.tools.common.gui.*;

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

