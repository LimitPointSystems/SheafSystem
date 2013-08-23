
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

package tools.viewer.table;

import bindings.java.*;
import tools.viewer.user.*;
import tools.common.util.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;

/*
 *  Class which provides a paged representatation of a field
 *  which is (perhaps) too large to be represently efficiently
 *  with a DefaultTableModel (standard) approach.
 */
public class PagedTableModel extends AbstractTableModel
{
  sec_vd field;
  int inputPageSize;

  double[] dofs;
  String[] columnHeaders;

  int rowCount;
  int columnCount;
  int pageSize;
  int pageIndex;

  static String firstColumnName = "Disc ID";

  static final boolean doRounding = true;

  /*
   *  Constructor
   *
   *  @param field A <code>sec_vd</code> representing the field.
   *  @param pageSize The size of a "visible" (possibly scrolled)  page.
   */
  public PagedTableModel(sec_vd fld, int pgSize)
  {
    field = fld;
    inputPageSize = pgSize;
    init();
  }

  /**
   *  Initialize the rows and columns from the field data.
   */
  private void init()
  {
    dofs = SheafUtilities.getRowDofValues(field);

    //     System.out.println("PagedTableModel.init dofs.length = " +  dofs.length);

    // Round to 6 significant figures.
    //$$TODO: Make accessor and mutators for number of significant figures.
    //        And pass it in a constructor.
    if(doRounding)
      roundDofs(6);

    String[] headers = SheafUtilities.getRowDofNames(field);
    if(headers == null || headers.length == 0)
      return;

    columnCount = headers.length + 1;
    rowCount = dofs.length/headers.length;

    //     System.out.println("PagedTableModel.init  rowCount = " +   rowCount);

    columnHeaders = new String[columnCount];
    columnHeaders[0] = firstColumnName;
    for(int i=1; i<columnCount; i++)
      columnHeaders[i] = headers[i-1];

    pageSize = inputPageSize;
    if(pageSize > rowCount)
      pageSize = rowCount;
  }

  /**
   *  Update the model after a presumed change to the underlying sec_vd field.
   *  Calling this when no change has occurred is possible with no side
   *  effects, but wastes cycles. 
   */
  public void update()
  {
    //     System.out.println("PagedTableModel.update()");

    init();
    fireTableStructureChanged();
  }

  //=========================================================================
  //  The methods required by AbstractTableModel
  //  In this case, these apply to the current page.
  //=========================================================================

  /*
   *  Get the row count for the current page.
   *
   *  @return The row count.
   */
  public int getRowCount()
  {
    int extra = rowCount - pageIndex*pageSize;
    int count = (extra < pageSize) ? extra : pageSize;

    //     System.out.println("\nPagedTableModel.getRowCount() rowCount  = " +  rowCount);
    //     System.out.println("PagedTableModel.getRowCount() pageIndex = " +  pageIndex);
    //     System.out.println("PagedTableModel.getRowCount() pageSize  = " +  pageSize);
    //     System.out.println("PagedTableModel.getRowCount() extra     = " +  extra);
    //     System.out.println("PagedTableModel.getRowCount() count     = " +  count);

    return count;
  }

  /*
   *  Get the column count (same for all pages).
   *
   *  @return The column count.
   */
  public int getColumnCount()
  {
    return columnCount;
  }

  //$$ISSUE: Might be more efficient to make "Row" Object array in constructor
  //         and use it here (fewer instantiations and less computation.

  /*
   *  Get the <code>Object</code> for a specified cell of the current page.
   *
   *  @param pageRow The row number for the current page.
   *  @param column The column number.
   *  @return The <code>Object</code> in the cell.
   */
  public Object getValueAt(int pageRow, int column)
  {
    int actualRow = getActualRow(pageRow);

    Object result = null;
    if(column == 0)
    {
      try
      {
        // actualRow is the sequence id.  Use the discretization sequence id
        // to get the poset_id.  Then use the discretization subposet client
        // id map to get the client id.

        section_space_schema_member schema =
          (section_space_schema_member) field.schema();

        index_space_handle seq_id_space = schema.discretization_id_space();
        index_space_handle disc_id_space = schema.discretization().id_space();

        int top_id = seq_id_space.hub_pod(actualRow);

        int disc_id = disc_id_space.pod(top_id);

        result = new Integer(disc_id);
      }
      catch(Exception ex)
      {
        // $$HACK: Need better error handling.

        ex.printStackTrace();

        return null;
      }
    }
    else
    {
      int index = actualRow*(columnCount-1) + (column-1);
      if(index >= 0 && index < dofs.length)
      {
        double v = dofs[index];
        result = new Double(v);
      }
    }

    return result;
  }

  //=========================================================================


  /*
   *  Get the current page size.
   *
   *  @return The page size.
   */
  public int getPageSize()
  {
    return pageSize;
  }

  /*
   *  Set the current page size.
   *
   *  @param size The new page size.
   */
  public void setPageSize(int size)
  {
    if(pageSize != size)
    {
      int oldSize = pageSize;
      pageSize = size;
      if(oldSize < pageSize)
      {
        fireTableRowsInserted(oldSize, pageSize-1);
      }
      else
      {
        fireTableRowsDeleted(pageSize, oldSize-1);
      }
    }
  }

  /*
   *  Get the current page index (offset).
   *
   *  @return The page index.
   */
  public int getPageIndex()
  {
    return pageIndex;
  }

  /*
   *  Get the page count (number of full or partial pages).
   *
   *  @return The page count.
   */
  public int getPageCount()
  {
    return (rowCount + pageSize - 1) / pageSize;
  }

  /*
   *  Get the actual row.
   *
   *  @return The actual row.
   */
  public int getActualRowCount(int pageRow)
  {
    return rowCount;
  }

  /*
   *  Get the actual row count (as opposed to the page row count).
   *
   *  @return The actual row count.
   */
  public int getActualRow(int pageRow)
  {
    int actualRow = pageRow + pageIndex*pageSize;
    return actualRow;
  }

  /*
   *  Get the name for a given column.
   *
   *  @param column The index for the desired column.
   *  @return A <code>String</code> with the column name.
   */
  public String getColumnName(int column)
  {
    return columnHeaders[column];
  }

  /*
   *  Move up one page (unless already at the top).
   */
  public void pageUp()
  {
    if (pageIndex > 0)
    {
      pageIndex--;
      fireTableDataChanged();
    }
  }

  /*
   *  Move down one page (unless already at the bottom).
   */
  public void pageDown()
  {
    if (pageIndex < getPageCount()-1)
    {
      pageIndex++;
      fireTableDataChanged();
    }
  }

  /**
   *  Round all of the dofs to a specified number of significant figures.
   *
   *  @param sigfigs The number of significant figures. 
   */
  private void roundDofs(int sigfigs)
  {
    for(int i=0; i<dofs.length; i++)
      dofs[i] = getSignificantFigures(dofs[i], sigfigs);
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

      double log10 = 0.43429448190325176 * Math.log(absval);
      double extraFigs = sigfigs - Math.floor(log10) - 1;

      double multiplier = 1.0;
      for(int i=0; i<extraFigs; i++)
        multiplier *= 10.0;

      value = sign*Math.round(multiplier*absval)/multiplier;
    }

    return value;
  }
}
