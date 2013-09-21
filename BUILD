
09/20/2013

Building the SheafSystem

Linux Prerequisites:
	For a Library only build:
	cmake 2.8.8 through 2.8.20.2. 
	hdf5 1.8.9, libraries built static
	VTK 5.10, libraries built shared (SheafSystem language bindings require shared VTK).
	g++ 4.2.2 is known to work without issue. 
	Doxygen 1.8.4+

Quick Start:
------------
1. Set the CXX and CC environment variables to reflect the compiler(s) of choice.
2. cd to the SheafSystem directory.
3. Run the cmboot script or chant the cmake mantra (mkdir build, cd build, ccmake ..), whichever you prefer. The cmboot script 
   has been provided for purposes of convenience. It creates a build dir, goes there and runs cmake, dealing with any command line args. 

	You may run ccmake from the build directory and tell cmake where hdf5 and VTK are installed from the GUI,
	or you can feed that information to cmboot (or cmake) at the command line.
	For example:
		./cmboot -DHDF5_DIR=/usr/local/hdf5-1.8.9-x86_64/share/cmake/hdf5/ -DVTK_DIR=/usr/local/vtk-5.10.1-release-x86_64/lib/vtk-5.10/
		
4. cd build
5. source the set_env_vars script: source set_env_vars.(sh or csh)
6. Execute make
   "make lib" will build only the shared libraries. "make" will build docs, shared libs, and static libs.

