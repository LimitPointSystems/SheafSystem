
/**
 * Classname: InfoPaneTextPanel
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: InfoPaneTextPanel.java,v $ $Revision: 1.7 $
 *
 * $Date: 2013/01/12 17:18:01 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.user;

import java.awt.*;
import javax.swing.*;

/**
 * Class InfoPaneTextPanel is used by <code>InfoPane</code>
 * to display lines of text in a <code>JTextArea</code>
 * embedded in a <code>JScrollPane<code>.
 */
public class InfoPaneTextPanel extends JPanel
{
  JTextArea textArea;

  /**
   * Constructor.
   *
   * @param text The text to appear in the text area (lines are '\n' delimited).
   */
  public InfoPaneTextPanel(String text)
  {
    init();
    setText(text);
  }

  /**
   * Constructor.
   *
   * @param lines An array of text lines to appear in the text area.
   */
  public InfoPaneTextPanel(String[] lines)
  {
    this.linesToString(lines);
  }

  public void setText(String text)
  {
    textArea.setText(text);
  }

  public void setText(String[] lines)
  {
    setText(linesToString(lines));
  }

  protected void init()
  {
    setLayout(new BorderLayout());

    textArea = new JTextArea(12, 32);  // Just a guess at what to use.
    textArea.setEditable(false);

    JScrollPane scrollPane = new JScrollPane(textArea);
    add
      (scrollPane, BorderLayout.CENTER);
  }

  /**
   * Convert an array of <code>String</code>s into a single
   * <code>String</code> with lines delimited by '\n'.
   */
  protected String linesToString(String[] lines)
  {
    StringBuffer sb = new StringBuffer();
    for(int i=0; i<lines.length; i++)
      sb.append(lines[i]).append('\n');
    return sb.toString();
  }
}
