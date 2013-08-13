
/**
 * Classname: LookupTableDescriptor
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:00 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.render;

import bindings.java.*;
import java.io.*;

import vtk.*;

/**
 *
 * Struct which describes a <code>LookupTable</code>
 *
 */
public abstract class LookupTableDescriptor extends Descriptor
{
  /**
   * Clone this <code>LookupTableDescriptor</code>
   */
  public abstract LookupTableDescriptor clone();

  /**
   * Copy the values of xlookupTable into this
   * <code>LookupTableDescriptor</code>.
   */
  public abstract void copy(LookupTableDescriptor xlookupTable);

  /**
   * Build a <code>LookupTable</code> from this
   * <code>LookupTableDescriptor</code>.
   */
  public abstract LookupTable build(namespace_poset xnamespace);

  /**
   * Update xlookupTable to this <code>LookupTableDescriptor</code>
   */
  public abstract void update(LookupTable xlookupTable,
                              LookupTableDescriptor xdescriptor);
}
