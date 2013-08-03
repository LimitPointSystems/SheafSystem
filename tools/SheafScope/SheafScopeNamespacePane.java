
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

import bindings.java.*;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.tree.*;

/**
 * SheafScopeNamespacePane specializes <code>SheafScopeAbstractTreePane</code>
 * to provide namespace display within the SheafScope.
 */
public class SheafScopeNamespacePane extends SheafScopeAbstractTreePane
{
  /**
   * Constructor
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> to be displayed.
   */
  public SheafScopeNamespacePane(SheafScopePosetPane xposetPane)
  {
    super(xposetPane, null);
    setTitle("Namespace: N/A");

    // Label background in case tree is empty.
    // If tree is not empty, it will cover text.

    setPaneText("No Namespace");

    // Namespace is fully expanded by default

    expandBranch();

  }

  // $$HACK: Must through RemoteExecption because the call to super can not
  //         be wrapped in a try loop.

  /**
   * Constructor
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> to be displayed.
   * @param xmember The <code>abstract_poset_member</code> to be traversed.
   */
  public SheafScopeNamespacePane(SheafScopePosetPane xposetPane,
                                 abstract_poset_member xmember)
  throws java.rmi.RemoteException
  {
    super(xposetPane, xmember.name_space().top());

    SheafScopePosetPane parentPane = posetPane.getParentPosetPane();

    setTitle("Namespace: " + parentPane.getName());

    setSelectedNode(null);
    expandBranch();
  }

  /**
   *
   */
  protected void annotate()
  {}
}
