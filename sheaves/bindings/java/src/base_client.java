//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Class base_client
//

package bindings.java;

public class base_client
{
  //$$TODO: Remove the default from this class;

  //   protected static final String DEFAULT_HOST = "LOCAL";
  //   protected static final int DEFAULT_PORT = 1099;

  //   protected String host = DEFAULT_HOST;
  //   protected int port = DEFAULT_PORT;
  protected String module_name = null;

  //   protected boolean remote = false;

  public base_client()
  {}

  public base_client(String module_name)
  {
    this.module_name = module_name;
    load_library(module_name);
  }

  //   public base_client(boolean remote, String module_name, int port, String host)
  //   {
  //     this.remote = remote;
  //     this.module_name = module_name;
  //     this.port = port;
  //     this.host = host;

  //     if(remote)
  //       be_remote();
  //     else
  //       be_local();
  //   }

  //   public base_client(boolean remote, String module_name, int port)
  //   {
  //     this(remote, module_name, port, DEFAULT_HOST);
  //   }

  //   public base_client(boolean remote, String module_name)
  //   {
  //     this(remote, module_name, DEFAULT_PORT, DEFAULT_HOST);
  //   }

  //   public base_client(String module_name)
  //   {
  //     this(false, module_name, DEFAULT_PORT, DEFAULT_HOST);
  //   }


  //   void be_local()
  //   {
  //     //create_security_manager();

  //     load_library();

  //     System.out.println("Client running \"locally\"...");
  //   }

  //   void be_remote()
  //   {
  //     create_security_manager();

  //     //String url = "rmi://" + host + ":" + port + "/" + module_name;
  //     //??base_proxy.set_server(host, port);

  //     System.out.println("Client running \"remotely\"...");
  //     System.out.println("  host = " + host + ", port = " + port);
  //   }

  //   void create_security_manager()
  //   {
  //     if (System.getSecurityManager() == null)
  //     {
  //       System.setSecurityManager(new java.rmi.RMISecurityManager());
  //     }
  //   }

  // Load the JNI library.

  protected void load_library()
  {
    // Attempt to load the JNI library file "lib"+module_name+".so".

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
}
