
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

package tools.common.client_server;

import java.io.*;

public class RemoteFile extends File
{
  protected File rootFile;

  public RemoteFile(File rootFile, String pathName)
  throws IllegalArgumentException
  {

    super(pathName);
    //System.out.println("RemoteFile 1");
    this.rootFile = rootFile;
    //$$ISSUE: Use (remote) path separator instead of "/".
    checkDecendent(rootFile.getPath() + "/" + pathName);
  }

  public RemoteFile(File rootFile, String parentPath, String childPath)
  throws IllegalArgumentException
  {
    super(parentPath, childPath);
    //System.out.println("RemoteFile 2");
    this.rootFile = rootFile;
    checkDecendent(parentPath);
  }

  public RemoteFile(File rootFile, File parentFile, String childPath)
  throws IllegalArgumentException
  {
    this(rootFile, parentFile.getPath(), childPath);
  }

  void checkDecendent(String childPath) throws IllegalArgumentException
  {
    if(!isDescendantOf(rootFile.getPath(), childPath))
      throw new IllegalArgumentException(createMessage(childPath));
  }

  public String getParent()
  {
    String parent = super.getParent();
    String rootParent = rootFile.getParent();

    //System.out.println("RF.getParent() super parent = " + parent);
    //System.out.println("RF.getParent() root parent  = " + rootParent);

    if((parent != null) &&
        (parent.equals(rootParent)))
    {
      parent = null;
    }

    //System.out.println("RF.getParent() parent = " + parent);

    return parent;
  }

  private boolean isDescendantOf(String rootPath, String childPath)
  {
    //System.out.println("RF.isDescendantOf childPath  = " + childPath);
    // System.out.println("RF.isDescendantOf rootPath = " + rootPath);

    // Null not accepted as descendant of the rootFile.
    if(childPath == null || childPath == "")
    {
      return false;
    }

    //??String parentPath = childPath;
    File f = new File(childPath);
    //String parentPath = f.getAbsolutePath();
    String parentPath = f.getPath();
    //String parentPath = null;
    //try { parentPath = f.getCanonicalPath(); }
    //catch(IOException e) {}

    while(parentPath != null)
    {
      if(parentPath.equals(rootPath))
        return true;
      parentPath = getParentPath(parentPath);
    }
    return false;
  }

  private String getParentPath(String path)
  {
    int index = path.lastIndexOf(separatorChar);
    if (index < 0)
      return null;

    String pp = path.substring(0, index);
    //System.out.println("RF.getParentPath() parentPath = " + pp);

    return pp;
  }

  private String createMessage(String f)
  {
    StringBuffer sb = new StringBuffer();
    sb.append("\"").append(f).append("\"")
    .append(" not descendant of root ")
    .append("\"").append(rootFile).append("\"");
    return sb.toString();
  }
}
