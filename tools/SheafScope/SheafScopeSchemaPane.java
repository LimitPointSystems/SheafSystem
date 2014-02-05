
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
