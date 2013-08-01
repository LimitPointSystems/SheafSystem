
/**
 * Classname: SheafScopeFilterPane
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:52 $
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
 */

package tools.SheafScope;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * SheafScopeFilterPane provides a base pane to display filter selection results.<p>
 */
public class SheafScopeFilterPane extends JPanel
{
  private JPanel directionPanel;
  private JPanel strictnessPanel;
  private JPanel subposetListPanel;

  private JRadioButton upButton;
  private JRadioButton downButton;

  private JRadioButton strictButton;
  private JRadioButton nonstrictButton;

  JList subposetList;

  private boolean confirmed    = false;
  private boolean isDown       = true;
  private boolean isStrict     = false;
  private String  subposetName = null;
  private int     selectedIndex;

  /**
   * Constructor<p>
   *
   * @param xnames The list of potential filter subPosets
   * @param enableRemoteX true, if remote X is enabled
   */
  public SheafScopeFilterPane(String[] xnames, boolean enableRemoteX)
  {
    setLayout(new BorderLayout());

    setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createTitledBorder("Filter Selection"),
                BorderFactory.createEmptyBorder(5,5,5,5)));

    JPanel topPanel = new JPanel();

    // directionPanel setup

    directionPanel = new JPanel();
    directionPanel.setBorder(BorderFactory.createCompoundBorder(
                               BorderFactory.createTitledBorder("Direction"),
                               BorderFactory.createEmptyBorder(5,5,5,5)));

    ButtonGroup directionGroup = new ButtonGroup();

    downButton = new JRadioButton("Down");
    upButton = new JRadioButton("Up");

    directionGroup.add(downButton);
    directionGroup.add(upButton);

    downButton.setSelected(true);

    directionPanel.add(upButton);
    directionPanel.add(downButton);

    // strictnessPanel setup

    strictnessPanel = new JPanel();
    strictnessPanel.setBorder(BorderFactory.createCompoundBorder(
                                BorderFactory.createTitledBorder("Strictness"),
                                BorderFactory.createEmptyBorder(5,5,5,5)));

    ButtonGroup strictnessGroup = new ButtonGroup();

    nonstrictButton = new JRadioButton("Nonstrict");
    strictButton = new JRadioButton("Strict");

    strictnessGroup.add(nonstrictButton);
    strictnessGroup.add(strictButton);

    nonstrictButton.setSelected(true);

    strictnessPanel.add(strictButton);
    strictnessPanel.add(nonstrictButton);

    topPanel.add(directionPanel);
    topPanel.add(strictnessPanel);

    add
      (topPanel, BorderLayout.NORTH);

    JPanel bottomPanel = new JPanel();
    bottomPanel.setBorder(BorderFactory.createCompoundBorder(
                            BorderFactory.createTitledBorder("Subposet List"),
                            BorderFactory.createEmptyBorder(5,5,5,5)));

    makeList(xnames);

    JScrollPane scrollPane = new JScrollPane(subposetList);

    // Dumb down the scroll mode to improve remote X performance.

    if(enableRemoteX)
    {
      scrollPane.getViewport().setScrollMode(JViewport.SIMPLE_SCROLL_MODE);
    }

    scrollPane.setVerticalScrollBarPolicy(
      ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);

    bottomPanel.setLayout(new BorderLayout());
    bottomPanel.add(scrollPane, BorderLayout.CENTER);

    add
      (bottomPanel,BorderLayout.CENTER);
  }

  /**
   * Constructs the list of filters from the provided array of names.
   *
   * @param xnames The list of subposet filters.
   *
   * 
   */
  public void makeList(String[] xnames)
  {
    if(xnames != null && xnames.length != 0)
    {
      subposetList = new JList(xnames);

      //Set the selected index to a likely choice.

      selectedIndex = (xnames.length > 1) ? 1 : 0;
      subposetList.setSelectedIndex(selectedIndex);
    }
    else
    {
      String[] items = {"No subposets!"};
      subposetList = new JList(items);
    }
  }

  /**
   * confirms that this subPoset is a downset.<p>
   *
   * @return true if subPoset is a downset.
   */
  public boolean directionIsDown()
  {
    return isDown;
  }

  /**
   * Confirms this filter is strict.<p>
   *
   * @return true if filter is strict.
   */
  public boolean isStrict()
  {
    return isStrict;
  }

  /**
   * Gets the name of this subposet.<p>
   *
   * @return a <code>String</code> containing the name of this subposet.
   */
  public String getSubposetName()
  {
    return subposetName;
  }

  /**
   * Terminates this dialog without taking action.<p>
   *
   * 
   */
  protected void cancel()
  {
    confirmed = false;
    downButton.setSelected(isDown);
    strictButton.setSelected(isStrict);
    subposetList.setSelectedIndex(selectedIndex);
  }

  /**
   * Confirms the user's Subposet filter selection.<p>
   *
   * 
   */
  protected void confirm()
  {
    confirmed = true;
    isDown = downButton.isSelected();
    isStrict = strictButton.isSelected();
    subposetName = (String)(subposetList.getSelectedValue());
    selectedIndex = subposetList.getSelectedIndex();
  }
}

