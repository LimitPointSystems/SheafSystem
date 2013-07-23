/**
 *  Classname: GlyphFieldActorToolBar
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:56 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.application;

import bindings.java.*;
import tools.viewer.common.*;
import tools.viewer.render.*;
import tools.viewer.user.*;

import java.util.*;
import javax.swing.*;

/**
 * Implementation of <code>FieldActorToolBar</code> for 3D
 * pseudo-color representations.
 */
public class GlyphFieldActorToolBar extends FieldActorToolBar
{
  /**
   * The roles
   */
  private static Class[] ROLES = {CoordinateRolePanel.class,
                                  ScalarRolePanel.class,
                                  VectorRolePanel.class};

  /**
   * The constructor
   */
  public GlyphFieldActorToolBar(FieldActorToolBarApplication xapplication)
  {
    super(xapplication, ROLES);
  }

  /**
   * True, if the representation can be visualized.
   */
  protected boolean canView()
  {
    return ((roles[0].getSection() != null) &&
            ((roles[1].getSection() != null) ||
             (roles[2].getSection() != null)));
  }

  /**
   * View this representation.
   */
  public void view()
  {
    // Get the Sheaf values from the fields.

    GlyphFieldActorDescriptor actor = new GlyphFieldActorDescriptor();
    SectionDescriptor section;

    try
    {
      // Set the namespace.

      actor.namespace = roles[0].getSection().name_space().name();

      // Set the coordinates

      section = getSectionDescriptor(roles[0].getSection());
      if(section == null)
        return;
      actor.coordinates = section;

      // Set the properties

      if(roles[1].getSection() != null)
      {
        section = getSectionDescriptor(roles[1].getSection());
        if(section == null)
          return;
        actor.scalarProperty = section;

        actor.colorMode = ViewerConstants.SCALAR;
      }
      else
      {
        actor.colorMode = ViewerConstants.VECTOR_MAGNITUDE;
      }

      if(roles[2].getSection() != null)
      {
        section = getSectionDescriptor(roles[2].getSection());
        if(section == null)
          return;
        actor.vectorProperty = section;

        actor.scaleMode = ViewerConstants.VECTOR_MAGNITUDE;
      }
      else
      {
        actor.scaleMode = ViewerConstants.SCALAR;
      }
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling

      e.printStackTrace();

      return;
    }

    // Open the viewer

    application.openG3DViewer(actor);
  }

  /**
   * Overwriting of toString().
   */
  public String toString()
  {
    return "3D Glyph";
  }
}
