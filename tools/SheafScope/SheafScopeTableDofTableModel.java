
/**
 *
 * Copyright (c) 2013 Limit Point Systems, Inc. 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */


package tools.SheafScope;

import bindings.java.*;
import tools.common.util.*;

import javax.swing.table.*;
import java.util.*;

/**
 * SheafScopeTableDofTableModel specializes <code>AbstractTableModel</code>
 * to displaying the table dofs of a poset.<p>
 */
public class SheafScopeTableDofTableModel extends AbstractTableModel
{
  /**
   * The Vector of Vectors of Object values.
   */
  protected Vector<String> dataVector = new Vector<String>();

  /**
   * Vector of column identifiers.
   */
  protected Vector<String> columnIdentifiers = new Vector<String>();

  /**
   * Instantiates a new <code>SheafScopeTableDofTableModel</code> for the 
   *
   * @param xmember The <code>abstract_poset_member</code> this model will be based on.
   */
  public SheafScopeTableDofTableModel(abstract_poset_member xmember)
  {
    try
    {
      poset_state_handle lhost = xmember.host();
      schema_poset_member lschema = lhost.schema();

      poset_dof_map dofMap = lhost.table_dof_map(false);

      int currentMemberVersion = standard_version_index.CURRENT_MEMBER_VERSION.swigValue();
      poset_dof_iterator itr = lschema.table_dof_iterator(currentMemberVersion);

      while(!itr.is_done())
      {
        schema_poset_member item = itr.item();

        // Get the value of the dof.

        String valueString =
          SheafUtilities.getDofAsString(dofMap, item);

        // Set the name

        columnIdentifiers.add(item.name());

        // Set the value

        dataVector.add(valueString);

        // Incement iterator

        itr.next();
      }
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   * Returns the number of columns in this data table.<p>
   *
   * @return the number of columns in the model
   */
  public int getColumnCount()
  {
    return columnIdentifiers.size();
  }

  /**
   * Returns the number of rows in this data table.<p>
   *
   * @return the number of rows in the model
   */
  public int getRowCount()
  {
    return 1;
  }

  /**
   * Returns an attribute value for the cell at <code>row</code><p>
   * and <code>column</code>.
   *
   * @param  xrow             the row whose value is to be queried.
   * @param  xcolumn          the column whose value is to be queried.
   *
   * @return                  the value Object at the specified cell.
   * @exception  ArrayIndexOutOfBoundsException  if an invalid row or
   *               column was given
   */
  public Object getValueAt(int xrow, int xcolumn)
  {
    return dataVector.get(xcolumn);
  }

  /**
   * Returns the name of the column
   *
   * @param xcolumn The column number
   * @return The name of the column
   */
  public String getColumnName(int xcolumn)
  {
    return columnIdentifiers.get(xcolumn);
  }
}
