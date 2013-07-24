
/**
 * Classname: FieldTableDescriptor
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:01 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.table;

import tools.viewer.render.*;
import bindings.java.*;

import java.awt.*;
import java.util.*;

/**
 *
 * Struct which describes an <code>FieldTable</code>
 *
 */
public class FieldTableDescriptor
{
  /**
   * The name of the <code>namespace_poset</code> for the field.
   */
  public String namespace = null;

  /**
   * The array of <code>SectionDescriptor</code>'s
   */
  public ArrayList<SectionDescriptor> sections =
    new ArrayList<SectionDescriptor>();

  /**
   * Default constructor
   */
  public FieldTableDescriptor()
  {}
}
