
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

package tools.common.client_server;

import java.io.*;
import java.util.*;
import java.rmi.*;
import java.rmi.registry.*;
import java.rmi.server.*;

//$$TODO: Finish javadoc comments.

/**
 *
 */
public class RemoteFileSystemImpl extends UnicastRemoteObject
      implements RemoteFileSystem
{
  private static final int DEFAULT_SERVER_PORT = 54321;

  private File remoteRoot;
  private Class fileSubType = RemoteFile.class;

  /**
   *
   */
  public RemoteFileSystemImpl(String root, int serverPort) throws RemoteException
  {
    super(serverPort);

    remoteRoot = new File(root);

    //         String[] f = remoteRoot.list();
    //         for(int i=0; i<f.length; i++)
    //             System.out.println("===> " + f[i]);
  }

  /**
   *
   */
  public RemoteFileSystemImpl(String root) throws RemoteException
  {
    this(root, DEFAULT_SERVER_PORT);
  }
  /**
   *
   */
  public String getFileSeparator()
  {
    return File.separator;
  }

  //$$TODO: Implement?

  /**
   *
   */
  public void setFileSubType(Class type)
  {}

  /**
   *
   */
  public Class getFileSubType()
  {
    return fileSubType;
  }

  /**
   *
   */
  public File createFileObject(String path) throws RemoteException
  {
    File file = null;
    try
    {
      //System.out.println("RFS: createFileObject remoteRoot = " + remoteRoot);
      //System.out.println("RFS: createFileObject path       = " + path);
      file = new RemoteFile(remoteRoot, path);
      //System.out.println("RFS: createFileObject file       = " + file);
    }
    catch(IllegalArgumentException e)
    {
      System.out.println(e);
    }
    return file;
  }

  /**
   *
   */
  public File createFileObject(String path, String filename)
  throws RemoteException
  {
    //System.out.println("RFS 2: createFileObject remoteRoot = " + remoteRoot);
    //System.out.println("RFS 2: createFileObject path       = " + path);
    //System.out.println("RFS 2: createFileObject filename   = " + filename);

    File file = null;
    try
    {
      file = new RemoteFile(remoteRoot, path, filename);
    }
    catch(IllegalArgumentException e)
    {
      System.out.println(e);
    }
    return file;
  }

  /**
   *
   */
  public File createFileObject(File dir, String path) throws RemoteException
  {
    //System.out.println("RFS 3: createFileObject remoteRoot = " + remoteRoot);
    //System.out.println("RFS 3: createFileObject dir        = " + dir);
    //System.out.println("RFS 3: createFileObject path       = " + path);

    File file = null;
    try
    {
      if(dir == null)
      {
        file = new RemoteFile(remoteRoot, path);
      }
      else
      {
        file = new RemoteFile(remoteRoot, dir, path);
      }
    }
    catch(IllegalArgumentException e)
    {
      System.out.println(e);
    }
    return file;
  }

  /**
   *
   */
  public File[] getFiles(File dir, boolean noHiddenFiles)
  throws RemoteException
  {
    Vector<File> files = new Vector<File>();
    String[] names = dir.list();
    int nameCount = (names==null) ? 0 : names.length;

    for(int i=0; i<nameCount; i++)
    {
      File f = createFileObject(dir, names[i]);
      if(noHiddenFiles)
      {
        if(!isHiddenFile(f))
          files.add(f);
      }
      else
      {
        files.add(f);
      }
    }

    File[] fileArray = new File[files.size()];
    files.copyInto(fileArray);
    return fileArray;
  }

  /**
   *
   */
  public File getParentDirectory(File dir) throws RemoteException
  {
    if(dir != null)
    {
      String parentFilename = dir.getParent();
      if(parentFilename != null)
        return createFileObject(parentFilename);
    }
    return null;
  }

  //$$TODO: Implement.

  /**
   *
   */
  public boolean isHiddenFile(File f) throws RemoteException
  {
    return false;
  }

  /**
   *
   */
  public boolean isFileSystemRoot(File file) throws RemoteException
  {
    return (file==remoteRoot);
  }

  /**
   *
   */
  public File getFileSystemRoot() throws RemoteException
  {
    return remoteRoot;
  }

  //public int getDirectoryType(File dir) throws RemoteException
  //{
  //    return GENERICDIRECTORY;
  //}

  /**
   *
   */
  public boolean createNewFile(File file) throws RemoteException, IOException
  {
    return file.createNewFile();
  }

  /**
   *
   */
  public boolean doesFileExist(File file) throws RemoteException
  {
    return file.exists();
  }

  /**
   *
   */
  public boolean isReadOnly(File file) throws RemoteException
  {
    return !file.canWrite();
  }

  /**
   *
   */
  public boolean isProtected(File file) throws RemoteException
  {
    return !file.canRead();
  }

  /**
   *
   */
  public boolean isTraversable(File file) throws RemoteException
  {
    return file.isDirectory();
  }
  /**
   *
   */
  public boolean isRegularFile(File file) throws RemoteException
  {
    return file.isFile();
  }

  /**
   *
   */
  public boolean isAbsolute(File file) throws RemoteException
  {
    return file.isAbsolute();
  }

  /**
   *
   */
  public long getLength(File file) throws RemoteException
  {
    return file.length();
  }

  /**
   *
   */
  public String getAbsolutePath(File file) throws RemoteException
  {
    return file.getAbsolutePath();
  }

  /**
   *
   */
  public String getCanonicalPath(File file)
  throws RemoteException, IOException
  {
    return file.getCanonicalPath();
  }

  /**
   *
   */
  public long getLastModifiedTime(File file) throws RemoteException
  {
    return file.lastModified();
  }

  /**
   *
   */
  public boolean createDirectory(File file) throws RemoteException
  {
    return file.mkdir();
  }

  /**
   *
   */
  public boolean createDirectories(File file) throws RemoteException
  {
    return file.mkdirs();
  }

  /**
   *
   */
  public boolean deleteFile(File file) throws RemoteException
  {
    return file.delete();
  }

  /**
   *
   */
  public boolean renameFile(File file, File dest) throws RemoteException
  {
    return file.renameTo(dest);
  }

  // Upload

  //$$TODO: Need return codes for success, failure, overwrite, etc.

  /**
   *
   */
  public int uploadToFileSystem(Object object, File destination,
                                boolean overwriteOK)
  throws RemoteException, IOException
  {
    // Using String object only for testing!!!

    int retval = 0;
    if(overwriteOK || !doesFileExist(destination))
    {
      String data = (String)object;
      FileWriter out = new FileWriter(destination);
      out.write(data);
      out.close();
      retval = 1;
    }
    return retval;
  }

  // Download

  /**
   *
   */
  public Object downloadFromFileSystem(File file) throws IOException
  {
    // Using String only for testing!!!

    String dataString = null;
    try
    {
      FileReader fr = new FileReader(file);
      StringWriter sw = new StringWriter(1024);

      int c;
      while((c = fr.read()) != -1)
        sw.write(c);

      fr.close();
      sw.close();

      dataString = sw.toString();
    }
    catch(FileNotFoundException e)
    {
      System.out.println(e);
    } // log!!!

    return new String(dataString);
  }
}
