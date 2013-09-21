Sheaf System Linux Installation How-To 


These notes assume you are using a csh or tcsh shell on Linux. 



<install_dir>/SheafSystem-<version>, which we will refer to as <ss_dir>. 

The location of the SheafSystemTest source tree, <install_dir>/SheafSystemTest-<version>, which we will refer to as <sst_dir>. 

3 Configuring SheafSystemTest
 
Change you working directory to <install_dir> 
>cd <install_dir> 
The SheafSystem libraries are in the subdirectory <ss_dir>. The test module is in subdirectory <sst_dir>. Change your working directory to the test module. 
Release 3.0.x 	1 of 3 1/30/2013 9:02 AM 
>cd <sst_dir> 
The SheafSystem libraries as delivered are compiled for the Intel C++ compiler. The Intel compiler is not completely self-sufficient, it relies on finding the Gnu C++ standard header files, and it searches your PATH environment variable to find the Gnu compiler. The SheafSystem is compatible only with g++ version 4.2.2 or later. So you have to make sure that a g++ installation with version 4.2.2 or later is in your PATH. In particular, if your Linux installation has a g++ installation in /usr/bin that is older than 4.2.2, you have to make sure the path to a 4.2.2 or later is in your PATH before /usr/bin. 
Now you'll need to know where your Intel compiler installation bin directory is. A common location is: 
<intel_bin_dir> = /opt/intel/bin 
What ever <intel_bin_dir> is on your system, the C++ compiler is <intel_bin_dir>/icpc, the C compiler is <intel_bin_dir>/icc, and the compiler environment script is <intel_bin_dir>/compilervars.csh.  
Set the environment variable CXX for the C++ compier, CC for the C compiler, and source the compilervars script.: 
>setenv CXX <intel_bin_dir>/icpc >setenv CC <intel_bin_dir>/icc >source <intel_bin_dir>/compilervars.csh intel64 
The above asumes you are running an a 64 bit system. Remember, replace <intel_bin_dir> by the actual path on your system. 
Now we're ready to configure. The SheafSystem requires CMake version 2.8.6. If your CMake is older, you will have to upgrade. If your version is new enough, run the configuration script: 
>./cmboot 
The script will request the absolute path to the SheafSystem installation, that is, <ss_dir> 
The cmboot script will configure the SheafSystemTest module in a subdirectory <sst_dir>/build. If anything goes wrong, for instance you didn't set the CC environment variable correctly, delete the build directory before you try again. If cmboot runs ok, it will finish with a recommendation to change directory to build and source the set_env_vars.csh script. Do it. 
>cd build >source set_env_vars.csh 
Release 3.0.x 2 of 3 1/30/2013 9:02 AM 

Running the tests 
Now we're still in the build directory and ready to run the tests. The tests create quite a lot of output, so we'll redirect that an output file, run the tests in the background and tail the output file to watch what's going on. First make sure there's no older copy of the output hanging around: 
>rm check.log >make check > check.log & >tail -f check.log ^C when the tests finish to get out of tail 
The tests may take 60 min or more to compile and run. 
The check target runs tests for each component of the SheafSystem (sheaves, fiber_bundles, geometry, fields). It presents results of each individual test and summaries for each component, but not a summary for the entire system. You may want to extract the summaries from the log file for convenient reporting. 
Release 3.0.x 3 of 3 1/30/2013 9:02 AM 


