
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

// JNI code for Screen.java

// See jawt.h in jdk for more information on what is being done here.

#include "jawt_md.h"
#include <jni.h>
#include "vtkRenderWindow.h"
#include "vtkJavaUtil.h"


///
/// Convert from a C++ pointer to a jlong
///
jlong cptr_to_jlong(void* p)
{
  jlong pointer;
  memset(&pointer, 0, sizeof(jlong)); // most likely 'pointer= 0;' works too
  memcpy(&pointer, &p, sizeof(p));
  return pointer;
}

extern "C" JNIEXPORT jlong JNICALL
  Java_tools_viewer_user_Screen_GetDisplay(JNIEnv* xenv,
      jobject xcanvas)
{
  // Get the AWT.

  JAWT awt;
  awt.version = JAWT_VERSION_1_3;
  if(JAWT_GetAWT(xenv, &awt) == JNI_FALSE)
  {
    return -1;
  }

  // Get the drawing surface.

  JAWT_DrawingSurface* ds = awt.GetDrawingSurface(xenv, xcanvas);
  if(ds == NULL)
  {
    cout << "Error getting drawing surface" << endl;
    return -1;
  }

  // Lock the drawing surface.

  jint lock = ds->Lock(ds)
                ;
  if((lock & JAWT_LOCK_ERROR) != 0)
  {
    cout << "Error locking drawing surface" << endl;
    awt.FreeDrawingSurface(ds);
    return -1;
  }

  // Get the drawing surface info.

  JAWT_DrawingSurfaceInfo* dsi = ds->GetDrawingSurfaceInfo(ds);
  if(dsi == NULL)
  {
    cout << "Error getting surface info" << endl;
    ds->Unlock(ds);
    awt.FreeDrawingSurface(ds);
    return -1;
  }

 #if defined(_WIN32) || defined(WIN32)

  JAWT_Win32DrawingSurfaceInfo* dsi_win =
    (JAWT_Win32DrawingSurfaceInfo*)dsi->platformInfo;

  // Get the render window pointer.

  jlong result = cptr_to_jlong(dsi_win->hwnd);

#else

  JAWT_X11DrawingSurfaceInfo* dsi_x11 =
    (JAWT_X11DrawingSurfaceInfo*)dsi->platformInfo;

  // Get the render window pointer.

  jlong result = cptr_to_jlong(dsi_x11->display);

#endif

  // Free the drawing surface info.

  ds->FreeDrawingSurfaceInfo(dsi);

  // Unlock the drawing surface.

  ds->Unlock(ds);

  // Free the drawing surface.

  awt.FreeDrawingSurface(ds);

  return result;

}

extern "C" JNIEXPORT jlong JNICALL
  Java_tools_viewer_user_Screen_GetDrawable(JNIEnv* xenv,
      jobject xcanvas)
{
  // Get the AWT.

  JAWT awt;
  awt.version = JAWT_VERSION_1_3;
  if(JAWT_GetAWT(xenv, &awt) == JNI_FALSE)
  {
    return -1;
  }

  // Get the drawing surface.

  JAWT_DrawingSurface* ds = awt.GetDrawingSurface(xenv, xcanvas);
  if(ds == NULL)
  {
    return -1;
  }

  // Lock the drawing surface.

  jint lock = ds->Lock(ds)
                ;
  if((lock & JAWT_LOCK_ERROR) != 0)
  {
    awt.FreeDrawingSurface(ds);
    return -1;
  }

  // Get the drawing surface info.

  JAWT_DrawingSurfaceInfo* dsi = ds->GetDrawingSurfaceInfo(ds);
  if(dsi == NULL)
  {
    cout << "Error getting surface info" << endl;
    ds->Unlock(ds);
    awt.FreeDrawingSurface(ds);
    return -1;
  }

#if defined(_WIN32) || defined(WIN32)

  JAWT_Win32DrawingSurfaceInfo* dsi_win =
    (JAWT_Win32DrawingSurfaceInfo*)dsi->platformInfo;
 jlong result = (jlong)dsi_win->hwnd;

#else

  JAWT_X11DrawingSurfaceInfo* dsi_x11 =
    (JAWT_X11DrawingSurfaceInfo*)dsi->platformInfo;

  // Get the render window pointer.
  jlong result = dsi_x11->drawable;

#endif

  // Free the drawing surface info.

  ds->FreeDrawingSurfaceInfo(dsi);

  // Unlock the drawing surface.

  ds->Unlock(ds);

  // Free the drawing surface.

  awt.FreeDrawingSurface(ds);

  return result;

}

// Lock must be called prior to render or anything which might
// cause vtkRenderWindow to make an XLib call or to call Render().
// The Lock() and UnLock() functions are necessary for drawing in
// JAWT, but they also provide a form of mutex locking so that multiple
// java threads are prevented from accessing X at the same time.  The only
// requirement JAWT has is that all operations on a JAWT_DrawingSurface
// MUST be performed from the same thread as the call to GetDrawingSurface.

extern "C" JNIEXPORT jlong JNICALL
  Java_tools_viewer_user_Screen_Lock(JNIEnv* xenv,
                                     jobject xcanvas)
{
  // Get the AWT.

  JAWT awt;
  awt.version = JAWT_VERSION_1_3;

  if(JAWT_GetAWT(xenv, &awt) == JNI_FALSE)
  {
    return 1;
  }

  // Get the drawing surface.

  JAWT_DrawingSurface* ds = awt.GetDrawingSurface(xenv, xcanvas);

  if(ds == NULL)
  {
    return 1;
  }

  // Lock the drawing surface.

  jint lock = ds->Lock(ds)
                ;

  if((lock & JAWT_LOCK_ERROR) != 0)
  {
    awt.FreeDrawingSurface(ds);
    return 1;
  }

  return 0;

}

// UnLock() must be called after a Lock() and execution of a
// function which might change the drawing surface.  See Lock().

extern "C" JNIEXPORT jint JNICALL
  Java_tools_viewer_user_Screen_UnLock(JNIEnv* xenv,
                                       jobject xcanvas)
{
  // Get the AWT.

  JAWT awt;
  awt.version = JAWT_VERSION_1_3;

  if(JAWT_GetAWT(xenv, &awt) == JNI_FALSE)
  {
    return 1;
  }

  // Get the drawing surface.

  JAWT_DrawingSurface* ds = awt.GetDrawingSurface(xenv, xcanvas);

  if(ds == NULL)
  {
    return 1;
  }

  // Unlock the drawing surface.

  ds->Unlock(ds);

  // Free the drawing surface.

  awt.FreeDrawingSurface(ds);

  return 0;
}
