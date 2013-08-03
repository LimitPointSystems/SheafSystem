
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
 * SheafScopeSecRepSpaceTableModel specializes <code>SheafScopeAbstractTableModel</code>
 * to create a table representation of a user supplied poset.<p>
 */
public class SheafScopeSecRepSpaceTableModel extends SheafScopeAbstractTableModel
{
  /**
   * Constructor
   *
   */
  public SheafScopeSecRepSpaceTableModel()
  {
    super();
  }

  /**
   * Instantiates a new <code>SheafScopeSecRepSpaceTableModel</code> based on the down set
   * of <code>poset_member</code> <i>member</i>.<p>
   *
   * @param xmember The <code>poset_member</code> this model will be based on.
   */
  public SheafScopeSecRepSpaceTableModel(abstract_poset_member xmember)
  {
    this();
    this.member = xmember;

    setColumnNames();

    // Initialize filter to subposet whole.

    try
    {
      filter = new subposet(xmember.host(), xmember.host().name());
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   * Public refresh method for this model.<p>
   *
   * @param xitr An iterator over this dataset's displayed (tree) nodes.
   * @param xsubposetName The name of the subposet filter for this model.
   *
   * 
   */
  public void refresh(Enumeration xitr, String xsubposetName)
  {
    try
    {
      filter.attach_to_state(member.host(), xsubposetName);
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    refresh(xitr, filter);
  }

  /**
   * Public refresh method for this model.<p>
   *
   * @param xitr An iterator over this dataset's displayed (tree) nodes.
   * @param xfilter The <code>subposet</code> filter for this model.
   *
   * 
   */
  protected void refresh(Enumeration xitr, subposet xfilter)
  {
    try
    {
      sec_rep_space_member srsMbr = (sec_rep_space_member)member;

      abstract_poset_member base = srsMbr.base();
      schema_poset_member fiberSchema = srsMbr.fiber_schema();

      boolean isRestricted = srsMbr.is_restricted();

      rowMembers.clear();
      displayedMembers.clear();

      while(xitr.hasMoreElements())
      {
        SheafScopeTreeNode node = (SheafScopeTreeNode)xitr.nextElement();

        //Note: mbr is a SecVd except for "top" and "bottom".
        sec_rep_space_member mbr = (sec_rep_space_member)(node.getMember());

        scoped_index index = mbr.index();

        if(xfilter.contains_member(index))
        {
          Long mbrIndex = new Long(index.pod());

          if(!displayedMembers.contains(mbrIndex))
          {
            displayedMembers.add(mbrIndex);

            // Restrict each row member to the restriction of the
            // table's member, if the table's member or the row
            // member are restricted.

            if(isRestricted || mbr.is_restricted())
              mbr.restrict_to(base, fiberSchema);

            refreshRow(mbr);

            rowMembers.add(mbr);

          }
        }
      }

      setColumnNames();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   * Refreshes the row associated with <i>rowMbr</i>.<p>
   *
   * @param rowMbr The <code>sec_vd</code> identifying
   * the table row to be refreshed.
   *
   * 
   */
  private void refreshRow(sec_rep_space_member rowMember)
  {
    try
    {
      String name = rowMember.name();
      if("bottom".equals(name) && !showBottoms)
        return;

      // Create a vector for the row info.

      Vector<Object> mbrData = new Vector<Object>();
      //Vector mbrData = new Vector();

      poset_dof_iterator mbrDofItr = null;
      poset_dof_map dofMap = null;

      if(!dofDisplay.equals(SheafScopeApplication.DISPLAY_NO_DOFS))
      {
        schema_poset_member schemaMember = rowMember.schema();

        int currentMemberVersion = standard_version_index.CURRENT_MEMBER_VERSION.swigValue();

        mbrDofItr = schemaMember.row_dof_iterator(currentMemberVersion);
      }

      // Add the name.

      mbrData.add(name);

      // Convert the "int" return value of getIndex() to a String.

      String index = Integer.toString(rowMember.index().pod());

      // Add the index.

      mbrData.add(index);

      // Add other id space indices.

      for(int i=0; i<idSpaces.size(); i++)
      {
        String spaceName = idSpaces.elementAt(i);

	index = Integer.toString(rowMember.host().member_id_spaces(false). 
				 pod(spaceName, rowMember.index()));


        mbrData.add(index);
      }

      // Is a jim or jrm?

      if(rowMember.is_jim(false))
      {
        mbrData.add("jim");

        if(!dofDisplay.equals(SheafScopeApplication.DISPLAY_NO_DOFS))
        {
          dofMap = rowMember.dof_map(false);

          int ct=0;

          while(!mbrDofItr.is_done())
          {
            schema_poset_member item = mbrDofItr.item();

            // Get the value of the dof.

            String valueString = SheafUtilities.getDofAsString(dofMap, item);

            mbrData.add(valueString);
            mbrDofItr.next();

            ct++;
            if(dofDisplay.equals(SheafScopeApplication.DISPLAY_LIMITED_DOFS) &&
                ct >= dofLimit)
              break;
          }
        }
      }

      // Member is a jrm -- no dof data.

      else
      {
        mbrData.add("jrm");

        if(!dofDisplay.equals(SheafScopeApplication.DISPLAY_NO_DOFS))
        {
          int ct=0;

          while(!mbrDofItr.is_done())
          {
            mbrData.add("");
            mbrDofItr.next();

            ct++;
            if(dofDisplay.equals(SheafScopeApplication.DISPLAY_LIMITED_DOFS) &&
                ct >= dofLimit)
              break;
          }
        }
      }

      // Add the row.

      addRow(mbrData);

    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }
}
