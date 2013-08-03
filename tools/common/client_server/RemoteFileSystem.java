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

public interface RemoteFileSystem extends Remote
{
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
