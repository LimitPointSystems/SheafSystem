/**
 *  Classname: HelpFrame
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: HelpFrame.java,v $ $Revision: 1.14 $
 *
 *  $Date: 2013/01/12 17:17:55 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.gui;

import javax.swing.*;
import javax.swing.text.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.io.*;

/**
 * HelpFrame provides a mechanism for HTML
 * based help documentation for an application.
 * <p>
 *
 * @see JFrame
 * @see JEditorPane
 * 
 */

public class HelpFrame extends JFrame
{
  HtmlPane pane;

  public HelpFrame(URL url) throws IOException
  {
    this(url, null);
  }

  public HelpFrame(URL url, URL iconURL) throws IOException
  {
    super("Help");
    //     setDefaultLookAndFeelDecorated(true);

    if(iconURL != null)
      setIconImage(GuiUtilities.getImage(iconURL));

    //$$TODO: Put dimensions somewhere where they can be changed easily!

    setSize(new Dimension(600, 500));

    GuiUtilities.centerOnScreen(this);

    setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

    addWindowListener(new WindowAdapter()
                      {
                        public void windowClosing(WindowEvent e)
                        {
                          setVisible(false);
                        }
                      }
                     );

    pane = new HtmlPane(url);

    setContentPane(pane);
  }

  public void setPage(URL url) throws IOException
  {
    pane.setPage(url);
  }
}

class HtmlPane extends JScrollPane implements HyperlinkListener
{
  JEditorPane html;

  public HtmlPane(URL url) throws IOException
  {
    if(url != null)
    {
      html = new JEditorPane(url);
      html.setEditable(false);
      html.addHyperlinkListener(this);
      getViewport().add(html);
    }
  }

  public void setPage(URL url) throws IOException
  {
    html.setPage(url);
  }

  public void hyperlinkUpdate(HyperlinkEvent e)
  {
    if(e.getEventType() == HyperlinkEvent.EventType.ACTIVATED)
    {
      linkActivated(e.getURL());
    }
  }

  protected void linkActivated(URL u)
  {
    Cursor c = html.getCursor();
    Cursor waitCursor = Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR);
    html.setCursor(waitCursor);
    SwingUtilities.invokeLater(new PageLoader(u, c));
  }

  class PageLoader implements Runnable
  {
    URL url;
    Cursor cursor;
    HelpFrame glossary;

    PageLoader(URL u, Cursor c)
    {
      url = u;
      cursor = c;
    }

    public void run()
    {
      if (url == null)
      {
        html.setCursor(cursor);
        html.getParent().repaint();
      }
      else if(url.getFile().endsWith("Glossary.html"))
      {
        try
        {
          if(glossary == null)
          {
            glossary = new HelpFrame(url);
            glossary.setSize(300, 300);
          }

          glossary.setVisible(true);
        }
        catch(IOException e)
        {
          System.err.println("Invalid Glossary URL");
          getToolkit().beep();
        }
      }
      else
      {
        Document doc = html.getDocument();
        try
        {
          html.setPage(url);
        }
        catch (IOException e)
        {
          html.setDocument(doc);
          getToolkit().beep();
        }
        finally
        {
          url = null;

          // Schedule the cursor to revert after this event completes.

          SwingUtilities.invokeLater(this);
        }
      }
    }
  }
}
