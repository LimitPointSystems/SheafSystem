/**
 *  Classname: SuffixFileFilter
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SuffixFileFilter.java,v $ $Revision: 1.12 $
 *
 *  $Date: 2013/01/12 17:17:55 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.gui;

import java.io.File;
import javax.swing.filechooser.FileFilter;

/**
 * SuffixFileFilter provides a simple file extension filter
 * for use with the JFileChooser.
 * <p>
 *
 * @see javax.swing.filechooser.FileFilter
 *
 */
public class SuffixFileFilter extends FileFilter
{
  String[] suffixes;
  String description = null;

  public SuffixFileFilter(String extension, String descript)
  {
    suffixes = new String[1];
    suffixes[0] = stripDot(extension);
    description = (descript != null) ? descript : makeDefaultDescription();
  }

  public SuffixFileFilter(String extension)
  {
    this(extension, null);
  }

  public SuffixFileFilter(String[] extensions, String descript)
  {
    suffixes = stripDots(extensions);
    description = (descript != null) ? descript : makeDefaultDescription();
  }

  public SuffixFileFilter(String[] extensions)
  {
    this(extensions, null);
  }

  private String stripDot(String extension)
  {
    return (extension.startsWith(".") ? extension.substring(1) : extension);
  }

  private String[] stripDots(String[] extensions)
  {
    String[] results = new String[extensions.length];
    for(int i=0; i<extensions.length; i++)
      results[i] = stripDot(extensions[i]);

    return results;
  }

  // Accept all directories and all files with prescribed suffixes.
  public boolean accept(File f)
  {
    if(f.isDirectory())
    {
      return true;
    }

    String ext = getExtension(f.getName());
    if(ext != null)
    {
      for(int i=0; i<suffixes.length; i++)
      {
        if(ext.equals(suffixes[i]))
          return true;
      }
    }
    return false;
  }

  public static String getExtension(String name)
  {
    int i = name.lastIndexOf('.');
    if(i>0 && i<name.length()-1)
      return name.substring(i+1).toLowerCase();
    else
      return null;
  }

  public String getDescription()
  {
    return description;
  }

  public String makeDefaultDescription()
  {
    StringBuffer sb = new StringBuffer("Files (");
    for(int i=0; i<suffixes.length; i++)
    {
      sb.append("*.").append(suffixes[i]);
      if(i<suffixes.length-1)
        sb.append(";");
    }
    sb.append(")");
    return sb.toString();
  }

}
