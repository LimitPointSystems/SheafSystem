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
 */

package tools.common.client_server;


import java.io.*;
import java.rmi.*;


public class RemoteFileSystemView extends javax.swing.filechooser.FileSystemView
{
  private RemoteFileSystem remoteFileSystem;

  public  static String registeredName = "RemoteFileSystem";
  public  static int DEFAULT_REGISTRY_PORT = 1099;

  private String hostname;
  private String rootPath;
  private int    port;

  public RemoteFileSystemView(String hostname, int port)
  {
    this.hostname = hostname;
    this.port = port;

    doLookup();
  }

  public RemoteFileSystemView(String hostname)
  {
    this(hostname, DEFAULT_REGISTRY_PORT);
  }


  void doLookup()
  {
    try
    {
      String url = "rmi://" + hostname + ":" + port + "/";
      String name = url + registeredName;

      //System.out.println("RemoteFileSystemView.doLookup: name = " + name);

      remoteFileSystem = (RemoteFileSystem)Naming.lookup(name);

      //System.out.println(
      //   "RemoteFileSystemView().doLookup: remoteFileSystem = "
      //  + remoteFileSystem);

      File root = remoteFileSystem.getFileSystemRoot();
      rootPath = root.getAbsolutePath();
    }
    catch(Exception e)
    {
      System.out.println(e);
      e.printStackTrace();
    }
  }


  // Create only one "root" based at the root path.

  public File[] getRoots()
  {
    File[] roots = { new File(rootPath) };
    roots[0] = createFileSystemRoot(roots[0]);

    return roots;
  }

  public void setHostname(String hostname)
  {
    this.hostname = hostname;
  }
  public void setRootPath(String path)
  {
    rootPath = path;
  }
  public void setPort(int port)
  {
    this.port = port;
  }

  public String getHostname()
  {
    return hostname;
  }
  public String getRootPath()
  {
    return rootPath;
  }
  public int getPort()
  {
    return port;
  }

  public boolean isRemote()
  {
    return true;
  }

  // Force - Can't do these on a remote file system!!!

  public File getHomeDirectory()
  {
    return getFileSystemRoot();
  }
  public File getWorkingDirectory()
  {
    return getFileSystemRoot();
  }
  public void setFileSubType(Class type)
  { }

  public String getFileSeparator()
  {
    String separator = null;
    try
    {
      separator = remoteFileSystem.getFileSeparator();
    }
    catch(RemoteException e)
    {
      System.out.println(e);
    }
    return separator;
  }

  public Class getFileSubType()
  {
    Class type = null;
    try
    {
      type = remoteFileSystem.getFileSubType();
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return type;
  }

  public File createFileObject(String path)
  {
    File file = null;
    try
    {
      //System.out.println("RFSV: createFileObject path = " + path);
      //System.out.println("RFSV: createFileObject remoteFileSystem = " + remoteFileSystem);
      file = remoteFileSystem.createFileObject(path);
      //System.out.println("RFSV: createFileObject file = " + file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return file;
  }

  public File createFileObject(String path, String filename)
  {
    //System.out.println("RFSV 2: createFileObject path = " + path);

    File file = null;
    try
    {
      file = remoteFileSystem.createFileObject(path, filename);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return file;
  }

  public File createFileObject(File dir, String path)
  {
    //System.out.println("RFSV 3: createFileObject path = " + path);

    File file = null;
    try
    {
      file = remoteFileSystem.createFileObject(dir, path);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return file;
  }

  public File[] getFiles(File dir, boolean noHiddenFiles)
  {
    //System.out.println("RFSV: getFiles dir = " + dir);
    //System.out.println("RFSV: getFiles rootPath = " + rootPath);

    File[] empty = new File[0];
    File[] files = empty;
    try
    {
      String dirName = dir.getAbsolutePath();
      //System.out.println("RFSV: getFiles dirName = " + dirName);

      if(dir.length() >= rootPath.length())
        files = remoteFileSystem.getFiles(dir, noHiddenFiles);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return files;
  }

  public File getParentDirectory(File dir)
  {
    File file = null;
    try
    {
      //System.out.println(" RemoteFileSystemView.getParentDirectory dir = " + dir);
      file = remoteFileSystem.getParentDirectory(dir);
      //System.out.println(" RemoteFileSystemView.getParentDirectory file = " + file);
      if(file == null)
        file = dir;
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return file;
  }

  public boolean isHiddenFile(File f)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.isHiddenFile(f);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  public boolean isFileSystemRoot(File f)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.isFileSystemRoot(f);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  public File getFileSystemRoot()
  {
    File file = null;
    try
    {
      file = remoteFileSystem.getFileSystemRoot();
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return file;
  }
  /*
      //Need to rewrite!!!
      public int getDirectoryType(File dir)
      {
          int type = RemoteFileSystem.GENERICDIRECTORY;
          int remoteFileSystemType = -1;
          try
          { 
              remoteFileSystemType = remoteFileSystem.getDirectoryType(dir);
              switch(remoteFileSystemType)
              {
                  case RemoteFileSystem.COMPUTER:
                      type = RemoteFileSystem.COMPUTER;
                      break;
                  case RemoteFileSystem.HARDDRIVE:
                      type = RemoteFileSystem.HARDDRIVE;
                      break;
                  case RemoteFileSystem.FLOPPYDRIVE:
                      type = RemoteFileSystem.FLOPPYDRIVE;
                      break;
                  default: type = RemoteFileSystem.GENERICDIRECTORY;
              }
          }
          catch(RemoteException e) { System.out.println(e); }
          
          return type;
      }
  */

  public boolean createNewFile(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.createNewFile(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    catch(IOException e)
    {
      handleException(e);
    }
    return flag;
  }

  public boolean doesFileExist(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.doesFileExist(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  public boolean isReadOnly(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.isReadOnly(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  public boolean isProtected(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.isProtected(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  //     public boolean isTraversable(File file)
  //     {
  //         boolean flag = false;
  //         try { flag = remoteFileSystem.isTraversable(file); }
  //         catch(RemoteException e) { handleException(e); }
  //         return flag;
  //     }

  public Boolean isTraversable(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.isTraversable(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return new Boolean(flag);
  }

  public boolean isRegularFile(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.isRegularFile(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  public boolean isAbsolute(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.isAbsolute(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  public long getLength(File file)
  {
    long len = 0;
    try
    {
      len = remoteFileSystem.getLength(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return len;
  }

  public String getAbsolutePath(File file)
  {
    String path = null;
    try
    {
      path = remoteFileSystem.getAbsolutePath(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return path;
  }

  public String getCanonicalPath(File file)
  {
    String path = null;
    try
    {
      path = remoteFileSystem.getCanonicalPath(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    catch(IOException e)
    {
      handleException(e);
    }
    return path;
  }

  public long getLastModifiedTime(File file)
  {
    long len = 0;
    try
    {
      len = remoteFileSystem.getLastModifiedTime(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return len;
  }

  public boolean createDirectory(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.createDirectory(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  public boolean createDirectories(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.createDirectories(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  public boolean deleteFile(File file)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.deleteFile(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  public boolean renameFile(File file, File dest)
  {
    boolean flag = false;
    try
    {
      flag = remoteFileSystem.renameFile(file, dest);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return flag;
  }

  //========================================================================

  public File createNewFolder(File containingDir) throws IOException
  {
    File result = null;
    return result;
  }

  //========================================================================

  // Upload to remote file system
  public int uploadToFileSystem(Object object,
                                File destination,
                                boolean overwriteOK) throws IOException
  {
    int retval = 0;
    ;
    try
    {
      retval = remoteFileSystem.uploadToFileSystem(object,
               destination,
               overwriteOK);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return retval;
  }

  // Download from remote file system
  public Object downloadFromFileSystem(File file) throws IOException
  {
    Object object = null;
    try
    {
      object = remoteFileSystem.downloadFromFileSystem(file);
    }
    catch(RemoteException e)
    {
      handleException(e);
    }
    return object;
  }

  public void handleException(Exception e)
  {
    System.out.println(e);
    e.printStackTrace();
    // ...
  }
}
