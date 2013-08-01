/**
 * Classname: SheafScopeAbstractTableModel
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:52 $
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
 */

package tools.SheafScope;

import bindings.java.*;
import tools.common.util.*;

import javax.swing.table.*;
import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.util.*;

/**
 * The super class for all <code>SheafScope</code> table models.<p>
 */
public abstract class SheafScopeAbstractTableModel extends AbstractTableModel
{
  /**
   * The Vector of Vectors of Object values.
   */
  protected Vector<Vector<Object>> dataVector;

  /**
   * Vector of column identifiers.
   */
  protected Vector<String> columnIdentifiers;

  /**
   * State of "showBottoms".
   */
  protected boolean showBottoms = false;

  /**
   * <code>HashSet</code> containing those members which are currently displayed.
   */
  protected HashSet<Long> displayedMembers = new HashSet<Long>();

  /**
   * The <code>abstract_poset_member</code> to be used as the "root" of this table model.
   */
  protected abstract_poset_member member;

  /**
   * The <code>subposet</code> used to filter data in this table model.
   */
  protected subposet filter = null;

  /**
   * Keeps a list of the member Objects currently displayed in the table.
   * Accessed from getMemberForRow(int row);
   */
  protected ArrayList<Object> rowMembers = new ArrayList<Object>();

  /**
   * Dof display type
   */
  protected String dofDisplay = SheafScopeApplication.dofDisplay;

  /**
   * Dof limit
   */
  protected int dofLimit = SheafScopeApplication.dofLimit;

  /**
   * Id spaces to display
   */
  protected Vector<String> idSpaces = new Vector<String>();

  /**
   * Default constructor
   */
  public SheafScopeAbstractTableModel()
  {
    this(0, 0);
  }

  /**
   * Creates and returns a new <code>Vector</code> of length <i>size</i>.<p>
   *
   * @param xsize The size of the new <code>Vector</code>. 
   *
   * @return The newly created <code>Vector</code>.
   */
  //   private static Vector<Vector<Object>> newVector(int xsize)
  //   {
  //     Vector<Vector<Object>> v = new Vector<Vector<Object>>(xsize);
  //     v.setSize(xsize);
  //     return v;
  //   }

  private static Vector<Vector<Object>> newDataVector(int xsize)
  {
    Vector<Vector<Object>> v = new Vector<Vector<Object>>(xsize);
    v.setSize(xsize);
    return v;
  }

  private static Vector<String> newColumnVector(int xsize)
  {
    Vector<String> v = new Vector<String>(xsize);
    v.setSize(xsize);
    return v;
  }

  /**
   *  Constructs a <code>DefaultTableModel</code> with
   *  <code>rowCount</code> and <code>columnCount</code> of
   *  <code>null</code> object values.<p>
   *
   * @param xrowCount           the number of rows the table holds
   * @param xcolumnCount        the number of columns the table holds
   */
  public SheafScopeAbstractTableModel(int xrowCount, int xcolumnCount)
  {
    this(newColumnVector(xcolumnCount), xrowCount);
  }

  /**
   *  Constructs a <code>DefaultTableModel</code> with as many columns
   *  as there are elements in <code>columnNames</code>
   *  and <code>rowCount</code> of <code>null</code>
   *  object values.  Each column's name will be taken from
   *  the <code>columnNames</code> vector.<p>
   *
   * @param xcolumnNames       <code>vector</code> containing the names
   *    of the new columns; if this is 
   *                          <code>null</code> then the model has no columns
   * @param xrowCount           the number of rows the table holds
   */
  public SheafScopeAbstractTableModel(Vector<String> xcolumnNames, int xrowCount)
  {
    setDataVector(newDataVector(xrowCount), xcolumnNames);
  }

  /**
   *  Constructs a <code>DefaultTableModel</code> and initializes the table
   *  by passing <code>data</code> and <code>columnNames</code>
   *  to the <code>setDataVector</code> method.<p>
   *
   * @param xdata              the data of the table
   * @param xcolumnNames       <code>vector</code> containing the names
   *    of the new columns
   */
  public SheafScopeAbstractTableModel(Vector<Vector<Object>> xdata,
                                      Vector<String> xcolumnNames)
  {
    setDataVector(xdata, xcolumnNames);
  }

  /**
   * Detach the filter subposet for this table model.
   */
  public void detachStates()
  {
    if(filter != null)
    {
      filter.detach_from_state();
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
    return dataVector.size();
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
    Vector rowVector = (Vector)dataVector.get(xrow);
    return rowVector.get(xcolumn);
  }

  /**
   *  Returns the <code>Vector</code> of <code>Vectors</code>
   *  that contains the table's
   *  data values.  The vectors contained in the outer vector are
   *  each a single row of values.  In other words, to get to the cell
   *  at row 1, column 5: <p>
   *
   *  <code>((Vector)getDataVector().get(1)).get(5);</code><p>
   *
   * @return  the vector of vectors containing the table's data values
   */
  public Vector getDataVector()
  {
    return dataVector;
  }

  /**
   *  Replaces the current <code>dataVector</code> instance variable 
   *  with the new Vector of rows, <code>dataVector</code>.
   *  <code>columnIdentifiers</code> are the names of the new 
   *  columns.  The first name in <code>columnIdentifiers</code> is
   *  mapped to column 0 in <code>dataVector</code>. Each row in
   *  <code>dataVector</code> is adjusted to match the number of 
   *  columns in <code>columnIdentifiers</code>
   *  either by truncating the <code>Vector</code> if it is too long,
   *  or adding <code>null</code> values if it is too short.
   *  <p>Note that passing in a <code>null</code> value for
   *  <code>dataVector</code> results in unspecified behavior,
   *  an possibly an exception.<p>
   *
   * @param   xdataVector         the new data vector
   * @param   xcolumnIdentifiers     the names of the columns
   */
  public void setDataVector(Vector<Vector<Object>> xdataVector,
                            Vector<String> xcolumnIdentifiers)
  {
    //this.dataVector = nonNullVector(xdataVector);
    //this.columnIdentifiers = nonNullVector(xcolumnIdentifiers);

    this.dataVector = (xdataVector != null)
                      ? xdataVector : new Vector<Vector<Object>>();
    this.columnIdentifiers = (xcolumnIdentifiers != null)
                             ? xcolumnIdentifiers : new Vector<String>();

    justifyRows(0, getRowCount());
    fireTableStructureChanged();
  }

  /**
   * The ID spaces to display in the table.
   *
   * @return the id spaces vector
   */
  public Vector<String> getIdSpaces()
  {
    return idSpaces;
  }

  /**
   * Set the ID spaces to display.
   *
   * @param xidSpaces the id spaces vector
   */
  public void setIdSpaces(Vector<String> xidSpaces)
  {
    idSpaces = xidSpaces;
  }

  /**
   * Clears the table (prior to a refresh)<p>
   *
   * 
   */
  public void clear()
  {
    int i;
    while((i = getRowCount()) != 0)
    {
      removeRow(i-1);
    }
  }

  /**
   *  Adds a row to the end of the model.  The new row will contain
   *  <code>null</code> values unless <code>rowData</code> is specified.
   *  Notification of the row being added will be generated.<p>
   *
   * @param   xrowData          optional data of the row being added
   *
   */
  public void addRow(Vector<Object> xrowData)
  {
    insertRow(getRowCount(), xrowData);
  }

  /**
   *  Inserts a row at <code>row</code> in the model.  The new row
   *  will contain <code>null</code> values unless <code>rowData</code>
   *  is specified.  Notification of the row being added will be generated.<p>
   *
   * @param   xrow             the row index of the row to be inserted
   * @param   xrowData         optional data of the row being added
   * @exception  ArrayIndexOutOfBoundsException  if the row was invalid
   */
  public void insertRow(int xrow, Vector<Object> xrowData)
  {
    dataVector.add(xrow, xrowData);
    justifyRows(xrow, xrow+1);
    fireTableRowsInserted(xrow, xrow);
  }

  /**
   *  Removes the row at <code>row</code> from the model.  Notification
   *  of the row being removed will be sent to all the listeners.<p>
   *
   * @param   xrow      the row index of the row to be removed
   * @exception  ArrayIndexOutOfBoundsException  if the row was invalid
   */
  public void removeRow(int xrow)
  {
    dataVector.remove(xrow);
    fireTableRowsDeleted(xrow, xrow);
  }

  /**
   * Replaces the column identifiers in the model.  If the number of
   * <code>newIdentifier</code>s is greater than the current number
   * of columns, new columns are added to the end of each row in the model.
   * If the number of <code>newIdentifier</code>s is less than the current
   * number of columns, all the extra columns at the end of a row are
   * discarded. <p>
   *
   * @param xcolumnNames  vector of column identifiers.  If
   *                      <code>null</code>, set the model
   *                      to zero columns
   */
  public void setColumnIdentifiers(Vector<String> xcolumnNames)
  {
    setDataVector(dataVector, xcolumnNames);
  }

  /**
   * Gets the column names for the table. First three names are fixed.<p>
   *
   * @return A <code>Vector</code> containing the column names.
   */
  private Vector<String> getColumnNames()
  {
    Vector<String> columnNames = new Vector<String>();
    columnNames.add("name");
    columnNames.add("id");

    for(int i=0; i<idSpaces.size(); i++)
    {
      columnNames.add(idSpaces.elementAt(i));
    }

    columnNames.add("kind");

    try
    {
      if(!dofDisplay.equals(SheafScopeApplication.DISPLAY_NO_DOFS))
      {
        schema_poset_member schemaMember = member.schema();

        int currentMemberVersion = standard_version_index.CURRENT_MEMBER_VERSION.swigValue();

        poset_dof_iterator iterator =
          schemaMember.row_dof_iterator(currentMemberVersion);
        //schemaMember.row_dof_iterator(sheaf_constants.CURRENT_MEMBER_VERSION());

        int ct=0;

        while(!iterator.is_done())
        {
          schema_poset_member item = iterator.item();
          columnNames.add(item.name());
          iterator.next();

          ct++;
          if(dofDisplay.equals(SheafScopeApplication.DISPLAY_LIMITED_DOFS) &&
              ct >= dofLimit)
            break;
        }
      }
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    return columnNames;
  }

  /**
   * Returns the column name.
   *
   * @param xcolumn The index of the column whose name we want.<p>
   *  
   * @return A name for this column using the string value of the
   * appropriate member in <code>columnIdentifiers</code>.
   * If <code>columnIdentifiers</code> does not have an entry 
   * for this index, returns the default
   * name provided by the superclass.
   */
  public String getColumnName(int xcolumn)
  {
    Object id = null;
    // This test is to cover the case when
    // getColumnCount has been subclassed by mistake ...
    if (xcolumn < columnIdentifiers.size())
    {
      id = columnIdentifiers.get(xcolumn);
    }
    return (id == null) ? super.getColumnName(xcolumn)
           : id.toString();
  }

  /**
   * Convenience method. See <code>setCColumnIdentifiers</code>.
   */
  protected void setColumnNames()
  {
    setColumnIdentifiers(getColumnNames());
  }

  /**
   * Set the number of rows for the case when getRowCount
   * is overridden.<p>
   *
   * 
   */
  private void justifyRows(int xfrom, int xto)
  {
    dataVector.setSize(getRowCount());

    for (int i = xfrom; i < xto; i++)
    {
      if (dataVector.get(i) == null)
      {
        dataVector.set(i, new Vector<Object>());
      }
      ((Vector)dataVector.get(i)).setSize(getColumnCount());
    }
  }

  /**
   * Make sure we arent passing around any null vectors.
   */
  //   private static Vector nonNullVector(Vector v)
  //   {
  //     return (v != null) ? v : new Vector();
  //   }


  /**
   * Turn showing "bottom"s on or off.<p>
   *
   * @param xtf  True if bottoms are to be displayed; otherwise false.
   *
   * 
   */
  public void setShowBottoms(boolean xtf)
  {
    showBottoms = xtf;
  }

  /**
   * Assignment method for the dof display type.
   *
   * @param xdofDisplay Dof display type
   */
  public void setDofDisplay(String xdofDisplay)
  {
    dofDisplay = xdofDisplay;
  }

  /**
   * Accessor for the dof display type
   *
   * @return dof display type
   */
  public String getDofDisplay()
  {
    return dofDisplay;
  }

  /**
   * Assignment method for the dof limit
   *
   * @param xdofLimit Dof limit
   */
  public void setDofLimit(int xdofLimit)
  {
    dofLimit = xdofLimit;
  }

  /**
   * Accessor for the dof limit
   *
   * @return dof limit
   */
  public int getDofLimit()
  {
    return dofLimit;
  }

  /**
   * Expose the listeners for this model instance.<p>
   *
   * @return An array of listener objects.
   */
  Object[] getListeners()
  {
    return listenerList.getListenerList();
  }

  /**
   * Return the member of this node
   */
  public abstract_poset_member getMember()
  {
    return member;
  }

  /**
    *  Return the member
    *  represented by <i>xrow</i>.<p>
    *
    * @param xrow The row index.
    */
  public Object getMemberForRow(int xrow)
  {
    if(xrow < 0 || xrow >= getRowCount())
      return null;
    return rowMembers.get(xrow);
  }

  //$$ISSUE: This method could be more generally useful as part of a
  //         class with math functions not available in java.Math.  It
  //         could be broken into two parts, a log10 method and a
  //         getSignificantFigures method.
  /**
   * Gets the <code>double</code> value for a given <code>double</code> type
   * with a specified number of significant figures. 
   * @param d The initial <code>double</code> value.
   * @param sigfigs The desired number of significant figures.
   * @return The <code>double</code> value with the specified number of
   *         significant figures.
   */
  public static double getSignificantFigures(double d, int sigfigs)
  {
    double value = 0.0;

    //$$ISSUE: Actually sigfigs can be somewhere between about 308 and 324
    //         depending whether d is >0 or <0.  Too compute intensive to
    //         actually do the calculation though.
    if(d != 0.0 && sigfigs > 0 && sigfigs < 300)
    {
      double absval = (d < 0.0) ? -d : d;
      double sign = (d < 0.0) ? -1.0 : 1.0;

      double log10 = 0.43429448190325176*Math.log(absval);
      double extraFigs = sigfigs - Math.floor(log10) - 1;

      double multiplier = 1.0;
      for(int i=0; i<extraFigs; i++)
        multiplier *= 10.0;

      value = sign*Math.round(multiplier*absval)/multiplier;
    }

    return value;
  }

  /**
   * Method refresh must be implemented by all descendant classes.<p>
   *
   * @param xitr An iterator over the poset members.
   * @param xfilter The <code>subposet</code> filter to apply.
   *
   * 
   */
  protected abstract void refresh(Enumeration xitr, subposet xfilter);

  //$$ISSUE: Does this method need to be public?
  /**
   * Method refresh must be implemented by all descendant classes.<p>
   *
   * @param xitr An iterator over the poset members.
   * @param xsubposetName The name of the <code>subposet</code> filter to apply.
   *
   * 
   */
  public abstract void refresh(Enumeration xitr, String xsubposetName);

}
