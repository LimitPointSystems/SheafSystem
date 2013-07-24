/**
 *  Classname: SheafUtilities
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:55 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.util;

import bindings.java.*;

/**
 * Sheaf utilities.
 */
public class SheafUtilities
{
  /**
   * Gets the <code>String</code> value of the type represented bye <code>type</code>.
   *
   * @return The <code>String</code> value of the type represented bye <code>type</code>.
   *
   */
  public static String getDofAsString(poset_dof_map xdofMap,
                                      schema_poset_member xMember)
  throws java.rmi.RemoteException
  {
    return xdofMap.to_string(xMember).trim();
  }

  /**
   * The row dof names of a section
   */
  public static String[] getRowDofNames(sec_vd xsection)
  {
    try
    {
      xsection.get_read_access();
      schema_poset_member lschema = xsection.fiber_schema();

      int count = lschema.row_dof_ct();
      String [] result = new String[count];

      int currentMemberVersion = standard_version_index.CURRENT_MEMBER_VERSION.swigValue();

      poset_dof_iterator itr =
        new poset_dof_iterator(lschema, false, currentMemberVersion);

      int index = 0;
      while(!itr.is_done())
      {
        result[index] = itr.item().name();
        index++;
        itr.next();
      }

      xsection.release_access(false);

      return result;
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return new String[0];
    }
  }

  /**
   * Return the row dof values for the section.
   */
  public static double[] getRowDofValues(sec_vd xfield)
  {
    try
    {
      xfield.get_read_access();

      schema_poset_member lschema = xfield.schema();

      int count = lschema.row_dof_ct();
      double [] result = new double[count];

      //discretization_iterator itr =
      //  new discretization_iterator(lschema);

      poset_dof_map dofMap = xfield.dof_map(false);

      int currentMemberVersion = standard_version_index.CURRENT_MEMBER_VERSION.swigValue();

      poset_dof_iterator itr = lschema.row_dof_iterator(currentMemberVersion);

      int index = 0;
      double dof;
      while(!itr.is_done())
      {
        dof = Double.parseDouble(dofMap.to_string(itr.item()).trim());
        result[index] = dof;
        index++;
        itr.next();
      }

      xfield.release_access(false);

      return result;
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return new double[0];
    }
  }
}
