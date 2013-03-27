// $RCSfile: NativeVtk.cc,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:57 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
