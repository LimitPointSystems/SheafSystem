// $RCSfile: Stage.cc,v $ $Revision: 1.11 $ $Date: 2013/01/12 17:18:00 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// JNI code for Stage.java

// See jawt.h in jdk for more information on what is being done here.

#include "jawt_md.h"
#include <jni.h>
#include "vtkRenderWindow.h"
#include "vtkJavaUtil.h"


///
/// Convert from jlong to void*
///
void* jlong_to_cptr(jlong pointer)
{
  void  *p;
  memcpy(&p, &pointer, sizeof(p));
  return p;
}

extern "C" JNIEXPORT jint JNICALL
  Java_tools_viewer_render_Stage_RenderCreate(JNIEnv* xenv,
      jobject xstage,
      jobject xwindow,
      jlong xdisplay,
      jlong xdrawable)
{
  // Get the AWT.

  JAWT awt;
  awt.version = JAWT_VERSION_1_3;
  if(JAWT_GetAWT(xenv, &awt) == JNI_FALSE)
  {
    return 1;
  }

  // Get the render window pointer.

  static char* name = const_cast<char *>("vtkRenderWindow");
  // VTK 5.0.3
  //  vtkRenderWindow* rw =
  //		  (vtkRenderWindow*)(vtkJavaGetPointerFromObject(xenv, xwindow, name));
  // VTK 5.6.1
  vtkRenderWindow* rw =
    (vtkRenderWindow*)(vtkJavaGetPointerFromObject(xenv, xwindow));

  rw->SetDisplayId(jlong_to_cptr(xdisplay));
  rw->SetWindowId(jlong_to_cptr(xdrawable));
  rw->SetParentId(jlong_to_cptr(xdisplay));

  return 0;
}
