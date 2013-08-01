/**
 * Classname: GenericAction.java
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:55 $
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

package tools.common.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.lang.reflect.*;

//$$TODO: Cleanup!

public class GenericAction extends AbstractAction
{
  protected Object target;
  protected Method method;
  protected Object[] voidArgs = new Object[0];

  public GenericAction(Object target, String methodName,
                       String actionName, String labelString,
                       String imageFilePath, String toolTip,
                       boolean enabled)
  {
    super(actionName);  //$$TODO: FIX!!!
    setEnabled(enabled);
    this.target = target;

    putValue("label", labelString);
    putValue(Action.SHORT_DESCRIPTION, toolTip);

    if(imageFilePath != null)
    {
      //             System.out.println("GenericAction target = " + target);
      //             System.out.println("GenericAction methodName = " + methodName);
      //             System.out.println("GenericAction imageFilePath = " + imageFilePath);

      //Icon icon = GuiUtilities.getImageIcon(
      //                target.getClass().getResource(imageFilePath));
      //Icon icon = GuiUtilities.getImageIcon(target, imageFilePath);
      Icon icon = GuiUtilities.getImageIcon(imageFilePath);

      //             System.out.println("GenericAction icon = " + icon);

      putValue(Action.SMALL_ICON, icon);
    }

    initMethod(methodName);
  }

  public GenericAction(Object target, String methodName,
                       String actionName, String labelString,
                       String imageFilePath, String toolTip)
  {
    this(target, methodName, actionName, labelString, imageFilePath, toolTip, true);
  }

  //$$TODO: Fix this (and the rest of the class).

  public GenericAction(Object target,
                       String actionName,
                       String methodName,
                       String labelString,
                       String toolTip,
                       String imageFilePath,
                       String acceleratorKeyString,
                       String mnemonicString,
                       String enabledString)
  {
    //this(target, methodName, actionName, labelString, imageFilePath, toolTip);

    //=========================================================================

    //super(labelString);
    this.target = target;

    //     System.out.println();
    //     System.out.println("GenericAction target               = " + target);
    //     System.out.println("GenericAction actionName           = " + actionName);
    //     System.out.println("GenericAction methodName           = " + methodName);
    //     System.out.println("GenericAction labelString          = " + labelString);
    //     System.out.println("GenericAction toolTip              = " + toolTip);
    //     System.out.println("GenericAction imageFilePath        = " + imageFilePath);
    //     System.out.println("GenericAction acceleratorKeyString = " + acceleratorKeyString);
    //     System.out.println("GenericAction mnemonicString       = " + mnemonicString);
    //     System.out.println("GenericAction enabledString        = " + enabledString);
    //     System.out.println();

    //putValue("label", labelString);
    putValue(Action.NAME, labelString);
    putValue(Action.SHORT_DESCRIPTION, toolTip);

    if(imageFilePath != null)
    {
      //             System.out.println("GenericAction target = " + target);
      //             System.out.println("GenericAction methodName = " + methodName);
      //             System.out.println("GenericAction imageFilePath = " + imageFilePath);

      //Icon icon = GuiUtilities.getImageIcon(
      //                target.getClass().getResource(imageFilePath));
      //Icon icon = GuiUtilities.getImageIcon(target, imageFilePath);
      Icon icon = GuiUtilities.getImageIcon(imageFilePath);

      //             System.out.println("GenericAction icon = " + icon);

      putValue(Action.SMALL_ICON, icon);
    }

    initMethod(methodName);

    //=========================================================================

    if(mnemonicString != null)
    {
      char keyChar = mnemonicString.charAt(0);
      //int ke = c;
      //System.out.println(">>>>>>>>>> ke = " + ke);

      putValue(Action.MNEMONIC_KEY, new Integer(keyChar));
    }

    if(acceleratorKeyString != null)
    {
      int lastDash = acceleratorKeyString.lastIndexOf('-');
      char keyChar= acceleratorKeyString.charAt(lastDash+1);

      //$$TODO: Generalize the handling of modifiers.

      // Get the "modifier" part of acceleratorKeyString and convert it
      // to all upper case (this way the case in acceleratorKeyString
      // is optional).

      String modifierString =
        (acceleratorKeyString.substring(0, lastDash)).toUpperCase();

      //System.out.println("modifierString = " + modifierString);

      int modifiers = 0;
      if("ALT".equals(modifierString))
        modifiers = KeyEvent.ALT_MASK;
      else if("CTRL".equals(modifierString))
        modifiers = KeyEvent.CTRL_MASK;
      else if("META".equals(modifierString))
        modifiers = KeyEvent.META_MASK;
      else if("SHIFT".equals(modifierString))
        modifiers = KeyEvent.SHIFT_MASK;

      //System.out.println("modifiers = " + modifiers);

      KeyStroke keyStroke = KeyStroke.getKeyStroke(keyChar, modifiers);
      putValue(Action.ACCELERATOR_KEY, keyStroke);
    }

    setEnabled("true".equals(enabledString));

  }

  /**
   *
   */
  public GenericAction(Object target, String[] strings)
  {
    this(target, strings[0], strings[1], strings[2], strings[3],
         strings[4], strings[5], strings[6], strings[7]);
  }


  //   public GenericAction(Object target, String[] strings)
  //   {
  //     this(target, strings[0], strings[1], strings[2], strings[3], strings[4], true);
  //   }


  public GenericAction(Object target, String methodName, String actionName,
                       boolean enabled)
  //String labelString,
  //String imageFilePath,
  //String toolTip)
  {
    super(actionName);
    setEnabled(enabled);
    this.target = target;

    //     putValue("label", labelString);
    //     putValue(Action.SHORT_DESCRIPTION, toolTip);
    //     if(imageFilePath != null)
    //     {
    //       Icon icon = GuiUtilities.getImageIcon(imageFilePath);
    //       //             System.out.println("GenericAction2 icon = " + icon);
    //       putValue(Action.SMALL_ICON, icon);
    //     }
    initMethod(methodName);

    //   public GenericAction(Object target, String[] strings)
    //   {
    //     this(target, strings[0], strings[1], strings[2], strings[3], strings[4]);
    //   }
  }


  protected void initMethod(String methodName)
  {
    try
    {
      //System.out.println("*** methodName = " + methodName);
      method = target.getClass().getMethod(methodName, new Class[0]);
      //System.out.println("*** target = " + target);
      //System.out.println("*** method = " + method);
    }
    catch(NoSuchMethodException e)
    {
      handleError(e);
    }
  }

  public void actionPerformed(ActionEvent evt)
  {
    //System.out.println(">>> target = " + target);
    //System.out.println(">>> method = " + method);

    try
    {
      method.invoke(target, voidArgs);
    }
    catch(InvocationTargetException e)
    {
      handleError(e);
    }
    catch(IllegalAccessException e)
    {
      handleError(e);
    }
  }

  protected void handleError(Exception e)
  {
    System.out.println(getClass().getName() + ": " + e);
    e.printStackTrace();
  }
}

////////////////////////////////////////////////////////////////////////////////
