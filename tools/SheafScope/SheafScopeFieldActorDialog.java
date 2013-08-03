
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
import tools.common.gui.*;
import tools.viewer.application.*;

import java.awt.*;
import javax.swing.*;

/**
 * Implementation of <code>FieldActorDialog</code> for the
 * SheafScope.
 */
public class SheafScopeFieldActorDialog extends FieldActorDialog
{
  /**
   * The <code>FieldActorToolBar</code> representations.
   */
  protected static Class[] REPS = {PseudoColorFieldActorToolBar.class,
                                   GlyphFieldActorToolBar.class,
                                   HedgeHogFieldActorToolBar.class,
                                   TensorGlyphFieldActorToolBar.class,
                                   G2DFieldActorToolBar.class,
                                   FieldTableToolBar.class};

  /**
   * The constructor
   */
  public SheafScopeFieldActorDialog(SheafScopeFrame xframe)
  {
    super(xframe, xframe, REPS);
  }
}
