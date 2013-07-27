
/**
 * Classname: InfoPane
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:01 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.user;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * Class InfoPane is used for displaying basic information
 * about field instances in a popup window.  The display is
 * in textual form.  Currently instances of 
 * <code>FieldActorSelectPanel</code> contain two instances
 * of this class, one each for the independent and independent
 * fields.  These windows are popped up by mouse clicking on the
 * corresponding text field in the <code>FieldActorSelectPanel</code>.
 */
public class InfoPane extends JDialog
{
  InfoPaneTextPanel textPanel;

  /**
   * Constructor.
   *
   * @param title The title to appear on the window title bar.
   * @param text The text to appear in the window (lines are '\n' delimited).
   */
  public InfoPane(String title, String text)
  {
    init(title, new InfoPaneTextPanel(text));
  }

  /**
   * Constructor.
   *
   * @param title The title to appear on the window title bar.
   * @param lines An array of text lines to appear in the window.
   */
  public InfoPane(String title, String[] lines)
  {
    init(title, new InfoPaneTextPanel(lines));
  }

  public void setText(String text)
  {
    textPanel.setText(text);
  }

  public void setText(String[] lines)
  {
    textPanel.setText(lines);
  }

  protected void init(String title, InfoPaneTextPanel txtPanel)
  {
    setTitle(title);
    textPanel = txtPanel;

    getContentPane().add(textPanel);

    pack();
  }
}
