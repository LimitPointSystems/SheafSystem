//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Class base_client
//

package bindings.java;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.RMISecurityManager;
import java.rmi.Naming;
import java.rmi.server.UnicastRemoteObject;
import java.lang.reflect.*;

public class base_server
{
  //$$TODO: Allow as input.

  static final int DEFAULT_PORT = 1099;
  //static final String DEFAULT_MODULE_NAME = "bundlemod";
  static final String DEFAULT_MODULE_NAME = "sheaves_java_binding";

  protected  int port = DEFAULT_PORT;
  protected String module_name = DEFAULT_MODULE_NAME;

  public base_server(String module_name, int port)
  {
    this.module_name = module_name;
    this.port = port;

    load_library();
  }

  public base_server(String module_name)
  {
    this(module_name, DEFAULT_PORT);
  }

  public base_server()
  {
    this(DEFAULT_MODULE_NAME, DEFAULT_PORT);
  }

  public void serve()
  {
    create_security_manager();

    create_registry();

    register_module();
  }

  // Load the JNI library code.

  protected void load_library()
  {
    // Attempt to load the JNI library file "lib"+module_name+".so".

    try
    {
      //$$ISSUE: The following print out is unix/linux specific.
      System.out.println("Loading library lib" + module_name + ".so");

      System.loadLibrary(module_name);

      System.out.println("Library load successful.");
    }
    catch(Exception e)
    {
      System.out.println("ERROR: Native code library lib" + module_name + ".so didn't load.");
      System.out.println(e.getMessage());
      System.exit(1);
    }
  }

  protected void create_security_manager()
  {
    if (System.getSecurityManager() == null)
    {
      System.out.println("Creating RMI security manager.");
      System.setSecurityManager(new java.rmi.RMISecurityManager());
    }
  }

  protected Registry create_registry()
  {
    // Create a registry (in this server).

    Registry registry = null;

    try
    {
      System.out.println("Creating registry.");
      registry = LocateRegistry.createRegistry(port);
      System.out.println("Registry created on port " + port);

    }
    catch(RemoteException e)
    {
      System.err.println("Server exception: " + e.getMessage());
      e.printStackTrace();
    }

    return registry;
  }

  protected void register_module()
  {
    //$$TODO: Catch individual exception types.

    try
    {
      String host = java.net.InetAddress.getLocalHost().getHostName();
      //System.out.println("host = " + host);

      //String url = "rmi://" + host + ":" + port + "/" + module_name;

      //System.out.println("Attempting to register " + url);

      // Since the module names can be specified at runtime, we'll use
      // reflection to invoke the static method "get_proxy_class_names()"
      // of the module_name class
      // (eg: bindings.java.sheaves_java_binding.get_proxy_class_names()).
      // This will return a String array containing the names of the
      // proxy classes in the module.

      //$$TODO: Deal with the package name by requiring it be included
      //        in module_name?
      String package_name = "bindings.java";

      String full_module_name = package_name + "." + module_name;
      Class c = Class.forName(full_module_name);
      //System.out.println("c = " + c.getName());

      Class[] params = new Class[0];
      Method m = c.getMethod("get_proxy_class_names", params);

      Object[] args = new Object[0];
      String[] registered_names = (String[])m.invoke(c, args);
      //System.out.println("obj = " + obj);

      String url_root = "rmi://" + host + ":" + port + "/";

      for(int i=0; i<registered_names.length; i++)
      {
        String jni_name = package_name + "." + registered_names[i] + "_JNI";

        //System.out.println("jni_name = " + jni_name);

        Class c2 = Class.forName(jni_name);

        //System.out.println("c2 = " + c2);

        Class[] params2 = new Class[0];
        Method m2 = c2.getMethod("getInstance", params2);

        Object[] args2 = new Object[0];

        //System.out.println("m2.invoke(c2, args2) = " + m2.invoke(c2, args2));

        Remote obj = (Remote)m2.invoke(c2, args2);

        Remote stub = UnicastRemoteObject.exportObject(obj, 0);

        //System.out.println("stub = " + stub);

        String url = url_root + registered_names[i];

        System.out.println("Registering " + url);

        Naming.rebind(url, stub);
      }

      System.err.println("Server ready...");

    }
    catch(Exception e)
    {
      System.err.println("Server exception: " + e.getMessage());
      e.printStackTrace();
    }
  }

}
