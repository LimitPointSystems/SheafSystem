
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

// Implementation for class jvm_launcher

#include "SheafSystem/jvm_launcher.h"
#include "SheafSystem/std_cstdlib.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/std_string.h"
#include "SheafSystem/std_unistd.h"
#include <jni.h>

///@todo Maybe use an enum here.
//const int jvm_launcher::SUCCESS            = 0;
//const int jvm_launcher::JVM_CREATE_FAILURE = 1;
//const int jvm_launcher::CLASS_NOT_FOUND    = 2;
//const int jvm_launcher::MAIN_NOT_FOUND     = 3;
//const int jvm_launcher::OUT_OF_MEMORY      = 4;

enum status_msg {  jvm_launcher::SUCCESS = 0,  jvm_launcher::JVM_CREATE_FAILURE = 1,
	 jvm_launcher::CLASS_NOT_FOUND = 2,  jvm_launcher::MAIN_NOT_FOUND = 3,
	 jvm_launcher::OUT_OF_MEMORY = 4 }
///
int
jvm_launcher::
launch(const char* main_class_name, int argc, char* argv[], bool verbose)
{
  // Handle VM options.

  char* class_path = getenv("CLASSPATH");
  char* ld_library_path = getenv("LD_LIBRARY_PATH");

  return launch(main_class_name, argc, argv, class_path, ld_library_path, verbose);
}


///
int
jvm_launcher::
launch(const char* main_class_name, int argc, char* argv[],
       const char* xclass_path, const char* xld_library_path, bool verbose)
{
  //cout << "jvm_launcher::launch xclass_path = " << xclass_path << endl;
  //cout << "jvm_launcher::launch xld_library_path = " << xld_library_path << endl;

  // to be set from within the process.

  // Currently using -rpath to get libraries, so we comment this call out.
  // re_exec(argc, argv, xclass_path, xld_library_path);

  JavaVM* vm;
  JNIEnv* env;

  // Handle VM options.

  // Set default paths to ".".

  string class_path(xclass_path);
  string ld_library_path(xld_library_path);

  // Append the user's path if a passed-in value differs from the user's.
  // This is so we can move the executable and still have it work (provided
  // the user's CLASSPATH and LD_LIBRARY_PATH are set correctly).
  // Note: We might replicate some paths here but that shouldn't be a
  // problem,

  char* ucp = getenv("CLASSPATH");
  if(ucp != NULL)
  {
    string user_class_path(ucp);
    if(class_path != user_class_path)
    {
      class_path += ":" + user_class_path;
    }
  }

  char* uld = getenv("LD_LIBRARY_PATH");
  if(uld != NULL)
  {
    string user_ld_library_path(uld);
    if(ld_library_path != ld_library_path)
    {
      ld_library_path += ":" + user_ld_library_path;
    }
  }

  //cout << "jvm_launcher::launch class_path = " << class_path << endl;
  //cout << "jvm_launcher::launch ld_library_path = " << ld_library_path << endl;

  // Allocate the VM options array.

  JavaVMOption options[3];

  string s0("-Djava.class.path=");
  s0 += class_path;
  options[0].optionString = const_cast<char*>(s0.c_str());

  string s1("-Djava.library.path=");
  s1 += ld_library_path;
  options[1].optionString = const_cast<char*>(s1.c_str());

  options[2].optionString = const_cast<char*>("-verbose");

  int num_options = verbose ? 3 : 2;

  JavaVMInitArgs vm_args;
  vm_args.version = JNI_VERSION_1_4;
  vm_args.options = options;
  vm_args.nOptions = num_options;
  vm_args.ignoreUnrecognized = JNI_TRUE;

  jint rval = JNI_CreateJavaVM(&vm, (void**)&env, &vm_args);
  if(rval < 0)
  {
    cout << "Couldn't create the Java VM" << endl;
    return(1);
  }

  jclass main_class = env->FindClass(main_class_name);
  if(main_class == 0)
  {
    cout << main_class_name << " class not found" << endl;
    return(2);
  }

  jmethodID main_method_id =
    env->GetStaticMethodID(main_class, "main", "([Ljava/lang/String;)V");

  if(main_method_id == 0)
  {
    cout << "main() method not found" << endl;
    return(3);
  }

  // Add any command line arguments (ie: 1,2,3,...) to the args array.

  jclass string_class = env->FindClass("java/lang/String");
  jobjectArray args = env->NewObjectArray(argc-1, string_class, NULL);
  if(args == 0)
  {
    cout << "Out of memory" << endl;
    return(4);
  }

  // Take care of no args case ("" implies no args).

  if(argc == 1)
  {
    jstring argString = env->NewStringUTF("");
    env->SetObjectArrayElement(args, 0, argString);
  }
  else
  {
    for(int i=1; i<argc; ++i)
    {
      jstring argString = env->NewStringUTF(argv[i]);
      env->SetObjectArrayElement(args, i-1, argString);
    }
  }

  // Invoke the main method (public static void main(String[] args)).

  env->CallStaticVoidMethod(main_class, main_method_id, args);

  // Unload the VM when this is the last thread.

  vm->DestroyJavaVM();

  return 0;
}

///
void
jvm_launcher::
re_exec(int argc, char* argv[],
        const char* xclass_path, const char* xld_library_path)
{
  //NOTE: We re-exec this same process exactly once so that we
  //      get the LD_LIBRARY_PATH environment variable to be
  //      used correctly by unix.  In unix, LD_LIBRARY_PATH
  //      is only looked at at load time.  Even though unix
  //      allows a given process to change LD_LIBRARY_PATH
  //      as much as it wants, it will never use it again
  //      after loading. So the trick here is to set
  //      LD_LIBRARY_PATH in the parent and then use
  //      execvp to replace that process with a copy
  //      which gets the modified environment.  We use
  //      another temporary environment variable to
  //      allow us to prevent infinite recursion.

  // Environment variable to set temporatily in order to
  // prevent infinite recursion here.

  static const char* env_name = "__HAVE_SET_ENV_SO_LD_LIBRARY_PATH_WORKS__";

  if(getenv(env_name) != NULL)
  {
    unsetenv(env_name);
  }
  else
  {
    setenv(env_name, "yes", 1);
    setenv("LD_LIBRARY_PATH", xld_library_path, 1);
    setenv("CLASSPATH", xclass_path, 1);

    if(execvp(argv[0], argv))
    {
      perror(argv[0]);
      exit(1);
    }
  }
}

//
// An "extern" function which can more easily be execed from a "dlsym"
// (dynamic linker method ) provided function pointer.
//
extern "C" int launch_jvm(const char* main_class_name, int argc, char** argv,
                            const char* xclass_path, const char* xld_library_path)
{
  return jvm_launcher::launch(main_class_name, argc, argv,
                              xclass_path, xld_library_path);
}


