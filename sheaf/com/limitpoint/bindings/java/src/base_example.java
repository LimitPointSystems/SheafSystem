
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

//
// Class base_example
//

package com.limitpoint.bindings.java;

public class base_example
{
  protected String module_name = null;

  public base_example()
  {}

  public base_example(String module_name)
  {
    this.module_name = module_name;
    load_library(module_name);
  }

  // Load the JNI module library.

  protected void load_library()
  {
    load_library(module_name);
  }

  // Load a JNI library.

  protected void load_library(String module_name)
  {
    // Attempt to load the JNI library file "lib"+module_name+".so".

    try
    {
      //$$ISSUE: The following print out is unix/linux specific
      //         (on MS Windows it would be "<module_name>.so").

      System.out.println("Loading library lib" + module_name + ".so");

      System.loadLibrary(module_name);

      System.out.println("Library load successful.");
    }
    catch(Error e)
    {
      System.out.println("ERROR: Native code library lib"
                         + module_name + ".so didn't load.");

      System.out.println(e.getMessage());

      System.exit(1);
    }
  }

  protected void readHdfFile(namespace_poset the_namespace, String fileName)
  {
    System.out.println("Begin reading file " + fileName);

    // (Note: We have to supply the default args in Java).

    the_namespace.get_read_write_access();

    storage_agent sa = new storage_agent(fileName,
                                         sheaf_file.access_mode.READ_ONLY,
                                         false,
                                         false);
    sa.read_entire(the_namespace);

    sa.delete();

    the_namespace.release_access();

    System.out.println("Finished writing file " + fileName);
  }

  protected void writeHdfFile(namespace_poset the_namespace, String fileName)
  {
    System.out.println("Begin writing file " + fileName);

    // (Note: We have to supply the default args in Java).

    the_namespace.get_read_write_access();

    storage_agent sa = new storage_agent(fileName,
                                         sheaf_file.access_mode.READ_WRITE,
                                         true,
                                         false);
    sa.write_entire(the_namespace);

    sa.delete();

    the_namespace.release_access();

    System.out.println("Finished writing file " + fileName);
  }

}
