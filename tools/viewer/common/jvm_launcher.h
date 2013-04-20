
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class jvm_launcher

#ifndef JVM_LAUNCHER_H
#define JVM_LAUNCHER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

///
/// Launcher for the Java virtual machine.
///
class SHEAF_DLL_SPEC jvm_launcher
{

public:

  ///
  /// Return values.
  ///
  static const int SUCCESS;
  static const int JVM_CREATE_FAILURE;
  static const int CLASS_NOT_FOUND;
  static const int MAIN_NOT_FOUND;
  static const int OUT_OF_MEMORY;

  ///
  ///  Launch the Java virtual machine, using the current CLASSPATH
  ///  and LD_LIBRARY_PATH environment variables.
  ///
  static int launch(const char* main_class_name, int argc, char* argv[],
                    bool verbose = false);

  ///
  ///  Launch the Java virtual machine, using specified values for the
  ///  CLASSPATH and LD_LIBRARY_PATH environment variables.
  ///
  static int launch(const char* main_class_name, int argc, char* argv[],
                    const char* class_path, const char* ld_library_path, bool verbose = false);

  ///
  /// Destructor
  ///
  virtual ~jvm_launcher();

protected:

  ///
  ///  Re-exec the current process with the using specified
  ///  CLASSPATH and LD_LIBRARY_PATH environment variables.
  ///  This allows LD_LIBRARY_PATH to be set so that the linker
  ///  will recognize it at the proper time.
  ///
  static void re_exec(int argc, char* argv[],
                      const char* class_path, const char* ld_library_path);

private:

  ///
  /// Default constructor.  Private because we don't ever need to
  /// instantiate one.
  ///
  jvm_launcher();

};

#endif // ifndef JVM_LAUNCHER_H
