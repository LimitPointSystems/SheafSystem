
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

// JNI code for NativeVtk.java

#include <jni.h>
#include "vtkObject.h"
#include "vtkJavaUtil.h"
#include "vtkSystemIncludes.h"

#ifdef __cplusplus
extern "C"
{
#endif

  /*
   * Class:     NativeVtk    
   * Method:    getCppPointerNative (static method)
   * Signature: (Lvtk/vtkObject;Ljava/lang/String;)J
   */
  JNIEXPORT jlong JNICALL
  Java_tools_viewer_common_NativeVtk_getCppPointerNative
  (JNIEnv* xenv, jclass xclass, jobject xvtk_object, jstring xclass_name)
  {
    const char* jname = xenv->GetStringUTFChars(xclass_name, NULL);
    char* cname = const_cast<char*>(jname);
    // VTK 5.0.3
    //    void* ptr = vtkJavaGetPointerFromObject(xenv, xvtk_object, cname);
    // VTK 5.6.1
    void* ptr = vtkJavaGetPointerFromObject(xenv, xvtk_object);
    xenv->ReleaseStringUTFChars(xclass_name, jname);

    jlong result = reinterpret_cast<jlong>(ptr);

    return result;
  }

#ifdef __cplusplus
}
#endif
