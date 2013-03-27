
/**
 * Classname: G2DDescriptorsTabbedPane
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: G2DDescriptorsTabbedPane.java,v $ $Revision: 1.8 $
 *
 * $Date: 2013/01/12 17:18:01 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.user;

import tools.viewer.render.*;

import javax.swing.*;

/**
 *
 * 3D implementation of <code>DescriptorsTabbedPane</code> for
 * containing the script panels for the <code>Viewer</code>
 *
 */
public class G2DDescriptorsTabbedPane extends DescriptorsTabbedPane
{
  /**
   * Default constructor
   */
  protected G2DDescriptorsTabbedPane(G2DViewer xviewer)
  {
    super(xviewer);
  }
}
