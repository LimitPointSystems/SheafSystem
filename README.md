
	For more Information on the SheafSystem Community Edition, see http://www.sheafsystem.org
		

	Building the SheafSystem 02/05/14


Linux Prerequisites:
-
		cmake 2.8.12 or newer. 
		hdf5 1.8.9 or newer, libraries built with static linkage
		VTK 5.10, libraries built shared preferred (SheafSystem language bindings require shared VTK).
		g++ 4.2.2 or newer. 
		Doxygen 1.8.4 or neweer
	
Linux Quick Start:
-
	1. Set the CXX and CC environment variables to reflect the compiler(s) of choice.

	2. cd to the SheafSystem directory.

	The cmboot script has been provided for purposes of convenience. It creates a build dir, then goes there and runs cmake, dealing with any command line args.

	3. Run the cmboot script or chant the cmake mantra (mkdir build, cd build, cmake ..), whichever you prefer.
		For example:
			./cmboot -DHDF5_DIR=/usr/local/hdf5-1.8.9-x86_64/share/cmake/hdf5/
			You may also run ccmake from the build directory and manually set the value of HDF5_DIR.
	
	4. cd build
	
	6. source the set_env_vars script:
		source set_env_vars.(sh or csh)
	
	7. Execute make
	"make lib" will build only the shared libraries. "make" will build docs, shared libs, and static libs.
	"make help" for more about build system capabilities.
