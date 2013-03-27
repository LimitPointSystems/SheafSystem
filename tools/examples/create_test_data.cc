
// $RCSfile: create_test_data.cc,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:56 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/create_test_data.cc

#include "lps_environment.h"
#include "std_iostream.h"
#include "std_string.h"
#include "std_unistd.h"
#include <sys/wait.h>

void exec_test_case(string xfile);

void re_exec(int argc, char* argv[]);

int main(int argc, char* argv[])
{
  //re_exec(argc, argv);

  exec_test_case("./test_case_3d.t");
  exec_test_case("./test_case_3d_irregular.t");
  exec_test_case("./test_case_2d.t");

}

void exec_test_case(string xfile)
{
  int status;

  // Get a child process.
  int pid = fork();

  if(pid < 0)
  {
    // Fork failed.
    perror(xfile.c_str());
    exit(1);
  }

  if(pid == 0)
  {
    // This is the child process

    cout << "Attempting to execute \"" << xfile << "\"" << endl;

    if(execlp(xfile.c_str(), (char*)0) == -1)
    {
      perror(xfile.c_str());
      exit(1);
    }
  }
  while(wait(&status) != pid)
    ; // Dont't delete this ';'
}

void re_exec(int argc, char* argv[])
{
  static const char* env_name = "__HAVE_SET_ENV_SO_LD_LIBRARY_PATH_WORKS__";

  if(getenv(env_name) == NULL)
  {
    setenv(env_name, "yes", 1);
    setenv("LD_LIBRARY_PATH", LD_LIBRARY_PATH, 1);
    setenv("CLASSPATH", CLASSPATH, 1);

    if(execvp(argv[0], argv))
    {
      perror(argv[0]);
      exit(1);
    }
  }
}
