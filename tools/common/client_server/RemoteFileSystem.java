
/**
 *  Classname: RemoteFileSystem
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:54 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.client_server;

import java.io.*;
import java.rmi.*;

public interface RemoteFileSystem extends Remote
{
  // Possible directory types
  //public static final int COMPUTER = 0;
  //public static final int FLOPPYDRIVE = 1;
  //public static final int HARDDRIVE = 2;
  //public static final int GENERICDIRECTORY = 3;

  public abstract String getFileSeparator() throws RemoteException;

  public abstract boolean isFileSystemRoot(File f) throws RemoteException;

  public abstract File getFileSystemRoot() throws RemoteException;

  public abstract boolean isHiddenFile(File f) throws RemoteException;

  public abstract File getParentDirectory(File dir) throws RemoteException;

  public abstract void setFileSubType(Class type) throws RemoteException;

  public abstract Class getFileSubType() throws RemoteException;

  //public abstract int getDirectoryType(File dir) throws RemoteException;

  public abstract File createFileObject(String path) throws RemoteException;

  public abstract File createFileObject(String path, String filename)
  throws RemoteException;

  public abstract File createFileObject(File dir, String filename)
  throws RemoteException;

  public abstract File[] getFiles(File dir, boolean noHiddenFiles)
  throws RemoteException;

  public abstract boolean createNewFile(File file)
  throws RemoteException, IOException;

  public abstract boolean doesFileExist(File file) throws RemoteException;

  public abstract boolean isTraversable(File file) throws RemoteException;

  public abstract boolean isReadOnly(File file) throws RemoteException;

  public abstract boolean isProtected(File file) throws RemoteException;

  public abstract boolean isAbsolute(File file) throws RemoteException;

  public abstract boolean isRegularFile(File file) throws RemoteException;

  public abstract long getLength(File file) throws RemoteException;

  public abstract String getAbsolutePath(File file) throws RemoteException;

  public abstract String getCanonicalPath(File file)
  throws RemoteException, IOException;

  public abstract long getLastModifiedTime(File file) throws RemoteException;

  public abstract boolean createDirectory(File file) throws RemoteException;

  public abstract boolean createDirectories(File file) throws RemoteException;

  public abstract boolean deleteFile(File file) throws RemoteException;

  public abstract boolean renameFile(File file, File dest)
  throws RemoteException;

  // Upload to remote file system

  public abstract int uploadToFileSystem(Object object, File destination,
                                         boolean overwriteOK)
  throws RemoteException, IOException;

  // Download from remote file system

  public abstract Object downloadFromFileSystem(File file)
  throws IOException;

}
