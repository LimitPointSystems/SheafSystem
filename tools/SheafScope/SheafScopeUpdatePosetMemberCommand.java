
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

package tools.SheafScope;

import javax.swing.event.*;

/**
 * SheafScopeUpdatePosetMemberCommand is a specialized
 * <code>TreeSelectionListener</code> to suit the needs of the SheafScope.
 * Listens for single node selections on the tree and updates the table
 * model accordingly.<p> 
 */
public class SheafScopeUpdatePosetMemberCommand implements TreeSelectionListener
{
  private SheafScopePosetPane posetPane;

  /**
   * Constructor
   * @param xposetPane The <code>SheafScopePosetPane</code> containing the tree
   *                  this listener is registered on.
   */
  public SheafScopeUpdatePosetMemberCommand(SheafScopePosetPane xposetPane)
  {
    posetPane = xposetPane;
  }

  /**
   * The action to be taken when a single treenode selection
   * event is detected.<p>
   *
   * @param event The detected <code>TreeSelectionEvent</code>.
   *
   * 
   */
  public void valueChanged(TreeSelectionEvent event)
  {
    //common.util.LPSDebug.println("event = " + event);

    posetPane.updateMember();
  }
}
