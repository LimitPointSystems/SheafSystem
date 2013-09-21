
	For more Information on the SheafSystem Community Edition, see http://www.sheafsystem.org
		

	Building the SheafSystem 09/20/2013


Linux Prerequisites:
-
	For a Library-only build (no language bindings):
		cmake 2.8.8 through 2.8.10.2. 
		hdf5 1.8.9, libraries built with static linkage
		VTK 5.10, libraries built shared (SheafSystem language bindings require shared VTK).
		g++ 4.2.2 is known to work without issue. 
		Doxygen 1.8.4+
	
Quick Start:
-
	1. Set the CXX and CC environment variables to reflect the compiler(s) of choice.

	2. cd to the SheafSystem directory.

	3. Run the cmboot script or chant the cmake mantra (mkdir build, cd build, ccmake ..), whichever you prefer. The cmboot script 
	has been provided for purposes of convenience. It creates a build dir, goes there and runs cmake, dealing with any command line args. 

	You may also run ccmake from the build directory and manually set the location of hdf5 and VTK.
	
	For example:
		./cmboot -DHDF5_DIR=/usr/local/hdf5-1.8.9-x86_64/share/cmake/hdf5/ -DVTK_DIR=/usr/local/vtk-5.10.1-release-x86_64/lib/vtk-5.10/
		
	4. cd build

	5. source the set_env_vars script:
   		source set_env_vars.(sh or csh)
	
	6. Execute make
   	"make lib" will build only the shared libraries. "make" will build docs, shared libs, and static libs.


Known Build System Issues:
-
	1. The build system has a known issue with cmake versions greater than 2.8.10.2. Working range is 2.8.8->2.8.10.2
	2. The SheafSystem is known to compile and link with GCC 4.2.2. Other 4.2 series compilers may work as well. 
	3. Intel 2013 C++ compiler is supported on Windows and Linux. Visual Studio 2008, 2010, and 2012 are supported on Windows.
