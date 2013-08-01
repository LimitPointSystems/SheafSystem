
/**
 * Classname: SheafScopeIdSpaceDialog
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

import tools.common.gui.*;
import bindings.java.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

/**
 * SheafScopeIdSpaceDialog provides dialog mechanisms for id_space display.
 */
public class SheafScopeIdSpaceDialog extends GenericDialog
{
  /**
   * The list of possible id spaces to display
   */
  protected JList idSpaceList;

  /**
   * The user selected id spaces.
   */
  protected Vector<String> idSpaces;

  /**
   * Constructor
   *
   * @param xframe The display frame.
   * @param xposet The poset to get the ID spaces from
   * @param xselected The currently selected ID spaces
   */
  public SheafScopeIdSpaceDialog(Frame xframe, poset_state_handle xposet,
                                 Vector<String> xselected)
  throws java.rmi.RemoteException
  {
    super(xframe, "Client ID Spaces");

    // Create the data for the list.

    Vector<Object> data = new Vector<Object>();

    index_space_family_iterator litr =
	new index_space_family_iterator(xposet.member_id_spaces(false), true);
    while(!litr.is_done())
    {
      data.add(litr.name());

      litr.next();
    }

    idSpaceList = new JList(data);

    // Select current id spaces in the list.

    int ct = xselected.size();
    int[] indices = new int[ct];
    for(int i=0; i < ct; i++)
    {
      indices[i] = data.indexOf(xselected.elementAt(i));
    }
    idSpaceList.setSelectedIndices(indices);

    // Create the clear button

    GenericAction action = new GenericAction(this,
                           "clear",
                           "Clear",
                           "Clear",
                           null,
                           "Clear All Selected ID Spaces");

    JButton button = new JButton(action);

    // Layout the dialog

    Box controls = Box.createHorizontalBox();
    controls.add(Box.createHorizontalGlue());
    controls.add(button);
    controls.add(Box.createHorizontalGlue());

    Box top = Box.createVerticalBox();
    top.add(Box.createVerticalStrut(6));
    top.add(controls);
    top.add(Box.createVerticalStrut(3));

    JPanel panel = new JPanel();
    panel.setLayout(new BorderLayout());
    panel.add(top, BorderLayout.NORTH);
    panel.add(Box.createVerticalStrut(6), BorderLayout.SOUTH);
    panel.add(Box.createHorizontalStrut(6), BorderLayout.EAST);
    panel.add(Box.createHorizontalStrut(6), BorderLayout.WEST);

    panel.add(new JScrollPane(idSpaceList));

    // Set the maximum size of the list.  A scroll pane will be used
    // if this list exceeds this amount.

    panel.setMaximumSize(new Dimension(400, 400));

    addPane(panel, 0);
  }

  /**
   * Clear all the selected id spaces.
   */
  public void clear()
  {
    idSpaceList.clearSelection();
  }

  /**
   * Return the id spaces selected by the user.  Returns <code>null</code>,
   * if the dialog was canceled.
   *
   * @return Vector of id spaces
   */
  public Vector<String> getIdSpaces()
  {
    return idSpaces;
  }

  public void okPressed()
  {
    idSpaces = new Vector<String>();

    Object[] values = idSpaceList.getSelectedValues();

    for(int i=0; i<values.length; i++)
    {
      idSpaces.add(values[i].toString());
    }

    setVisible(false);
  }

  public void cancelPressed()
  {
    idSpaces = null;

    setVisible(false);
  }
}

