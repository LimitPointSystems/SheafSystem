Building the SS
Linux:

Prerequisites:
	Library build:
cmake 2.8.8 through 2.8.20.2. The SS build system has a known issue with versions greater than 2.8.10.2

	hdf5 1.8.9, static build preferred
	g++ 4.2.2 is known to work without issue. 
	Doxygen 1.8.4

cd into the SheafSystem directory
Run the cmboot script or chant the cmake mantra whichever you prefer. after a simple run of cmake, you can do "make help:
to see the options that are available to you at both cmake and compile time.
The cmboot script has been provided for purposes of convenience. It creates a build dir, goes there, and runs cmake.

/usr/local/hdf5-1.8.9-x86_64/share/cmake/hdf5 

set CXX
Set CC

./cmboot -DHDF5_DIR=/usr/local/hdf5-1.8.9-x86_64/share/cmake/hdf5/ -DVTK_DIR=/usr/local/vtk-5.10.1-release-x86_64/lib/vtk-5.10/

make