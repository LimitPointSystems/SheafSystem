
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

package tools.viewer.render;

import tools.viewer.animation.*;
import bindings.java.*;

import java.awt.*;
import java.io.*;


/**
 *
 * Struct which describes a <code>sec_vd</code>
 *
 */
public class SectionDescriptor extends Descriptor
{
  // SECTION_DESCRIPTOR_FACET

  /**
   * The section path
   */
  public String path = null;

  /**
   * The base space restriction path
   */
  public String base = null;

  /**
   * The fiber schema restriction path
   */
  public String fiberSchema = null;

  /**
   * Default constructor
   */
  public SectionDescriptor()
  {}

  /**
   * Clone this <code>SectionDescriptor</code>
   */
  public synchronized SectionDescriptor clone()
  {
    SectionDescriptor result = new SectionDescriptor();

    result.copy(this);

    return result;
  }

  /**
   * Copy the values of xsection into this <code>SectionDescriptor</code>.
   */
  public synchronized void copy(SectionDescriptor xsection)
  {
    // DESCRIPTOR FACET

    selected = xsection.selected;
    time = xsection.time;

    // SECTION DESCRIPTOR FACET

    path = new String(xsection.path);
    if(xsection.base != null)
      base = new String(xsection.base);
    if(xsection.fiberSchema != null)
      fiberSchema = new String(xsection.fiberSchema);
  }

  /**
   * Build a <code>sec_vd</code> from this <code>SectionDescriptor</code>.
   */
  public synchronized sec_vd build(namespace_poset xnamespace)
  {
    return build(xnamespace, sec_vd.class);
  }

  /**
   * Build a <code>sec_vd</code> from this <code>SectionDescriptor</code>.
   */
  public synchronized sec_vd build(namespace_poset xnamespace,
                                   Class xsection)
  {
    //
    // $$ISSUE: Should require that xsection is a class that is a sec_vd
    //          or a descendant of sec_vd.
    //

    sec_vd result = null;

    try
    {
      poset_path posetPath = new poset_path(path);
      result = (sec_vd) xsection.newInstance();
      result.attach_to_state(xnamespace, posetPath, true);

      //
      // $$HACK: There is a chance that the section is not read accessible
      //         at this point so get read access.  This access is never
      //         released.
      //

      result.get_read_access();

      if(base != null || fiberSchema != null)
      {
        abstract_poset_member baseSection;
        if(base != null)
        {
          posetPath = new poset_path(base);
          baseSection = new total_poset_member(xnamespace, posetPath, true);
        }
        else
        {
          baseSection = result.base();
        }

        abstract_poset_member fiberSchemaSection;
        if(fiberSchema != null)
        {
          posetPath = new poset_path(fiberSchema);
          fiberSchemaSection = new total_poset_member(xnamespace, posetPath, true);
        }
        else
        {
          fiberSchemaSection = result.fiber_schema();
        }

        result.restrict_to(baseSection, fiberSchemaSection);
      }

      // Clear the initial is modified bit

      result.clear_state_is_modified();
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }

    return result;
  }

  // DESCRIPTOR FACET

  /**
   * Read the values of this <code>SectionDescriptor</code> from xinput
   */
  public synchronized void read(InputStream xinput)
  throws IOException
  {
    super.read(xinput);

    path = Script.readCell(xinput);
    base = Script.readCell(xinput);
    if(base.length() == 0)
      base = null;
    fiberSchema = Script.readCell(xinput);
    if(fiberSchema.length() == 0)
      fiberSchema = null;
  }

  /**
   * Write this <code>SectionDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    Script.write(path, xout);
    Script.writeSeparator(xout);
    if(base != null)
      Script.write(base, xout);
    Script.writeSeparator(xout);
    if(fiberSchema != null)
      Script.write(fiberSchema, xout);
  }

  /**
   * Override the hashCode method. It is the hash code of the path
   * and restriction paths added up.
   */
  public int hashCode()
  {
    int result = path.hashCode();
    if(base != null)
      result += base.hashCode();
    if(fiberSchema != null)
      result += fiberSchema.hashCode();

    return result;
  }

  /**
   * Override the equals method.  This is a test of equivalence. True,
   * if the path and restriction paths are the same.
   */
  public boolean equals(Object obj)
  {
    if(!(obj instanceof SectionDescriptor))
      return false;

    SectionDescriptor input = (SectionDescriptor) obj;

    if(!input.path.equals(path))
      return false;

    if((base == null) != (input.base == null))
      return false;
    else if(input.base != null && !input.base.equals(base))
      return false;

    if((fiberSchema == null) != (input.fiberSchema == null))
      return false;
    else if(input.fiberSchema != null && !input.fiberSchema.equals(fiberSchema))
      return false;

    return true;
  }
}
