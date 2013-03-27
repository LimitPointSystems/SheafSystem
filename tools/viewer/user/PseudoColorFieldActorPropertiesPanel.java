/**
 * Classname: PseudoColorFieldActorPropertiesPanel
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: PseudoColorFieldActorPropertiesPanel.java,v $ $Revision: 1.8 $
 *
 * $Date: 2013/01/12 17:18:02 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.user;

import tools.viewer.render.*;
import tools.common.gui.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.text.*;
import vtk.*;

/**
 * Implementation of <code>G3DFieldActorPropertiesPanel</code> for editing the
 * values of a <code>PseudoColorFieldActorDescriptor</code>.
 */
public class PseudoColorFieldActorPropertiesPanel
      extends G3DFieldActorPropertiesPanel
{
  // CONSTRUCTORS

  /**
   * Constructor
   */
  public PseudoColorFieldActorPropertiesPanel(G3DViewer xviewer,
      FieldActorDescriptor[] xactors)
  {
    super(xviewer, xactors);

    initValues();
  }
}
