
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
