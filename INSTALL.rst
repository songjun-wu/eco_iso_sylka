INSTALLATION
============

The following file contains information on how to install and compile the latest version of ECH2O.  


0. Overview

1. Windows Installation
    1.1 Adding the binaries to the PATH environment variable
2. Linux installation
    2.1 Dependencies 
    2.2 Installation
3. Compilation instructions for ECH2O using gcc
    3.1 Dependencies
    3.2 Making `ech2o``
    3.3 Making ``asc2c``
4. Contact


0. Overview
---------------

    The ECH2O package contains the following files, which will be installed in the installation directory chosen by the user:

    * **ech2o** binary: main executable file that performs the modeling calculations
    * **asc2c** binary: utility to convert ascii climate binary files to the binary format used by ECH2O
    * **Documentation** folder: Folder containing a copy of the user manual in pdf and html formats
    * **CaseStudy** folder: Folder containing sample files to follow the tutorial (case study) in the user guide.  
    
    ECH2O uses PCRASTER as data pre- and post-processor. Please install PCRASTER free of charge from http://pcraster.geo.uu.nl/downloads/latest-release/
    
1. Windows installation
-----------------------

 * Download the windows installer from http://hs.umt.edu/RegionalHydrologyLab/software/downloads.php. 

 * Double-click in the installer and follow the instructions

 * Dependencies are distributed along with the package

 * Open a terminal 

 * Type ech2o in the terminal and press ENTER. A splash screen should appear. If not, add manually the path to the installation directory to the PATH environment variable. 

1.1.  Adding the binaries to the PATH environment variable
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   The installer will try to edit the PATH environment variable to include the ech2o installation directory. If it does not succeed please, update manually the PATH environment variable with the path to the ech2o binaries contained in the installation directory.


2. Linux installation
---------------------

The Linux binaries have been compiled in openSUSE Leap with gcc 4.8.5. 

2.1 Dependencies
^^^^^^^^^^^^^^^^
    
    The pre-compiled executable links dynamically to the following external dynamic libraries, which need to be installed in your computer:

    * armadillo (version 7)
        * armadillo may require that ATLAS and LAPACK are installed
    * libc6 libraries
    * Boost::serialization from the Boost C++ libraries (libboost_serialization)

2.2. Installation
^^^^^^^^^^^^^^^^^

    * Unzip the tar.gz folder in a location for which you have writing permissions, such us ~/bin

    ::

    $ mkdir ~/bin
    $ cd ~/bin
    $ tar zxf ~/Downdloads/ech2o-5.1.2betax86-64.tar.gz

    * Update the PATH variable. Assuming a Bash shell:

    ::

    $ export PATH=~/bin/ech2o-5.1.2betax86-64

    The export PATH could also be added in your ~/.bashrc script to have the PATH updated every time you log in

     * Open a terminal 

     * Type ech2o in the terminal and press ENTER. A splash screen should appear

3. Compilation instructions for ECH2O using gcc
-----------------------------------------------
    
  The current version of ECH2O does not have a configure script. The Makefile has been generated for the gnu c++ compiler and does not check for dependencies. MINGW is necessary to compile in Windows. 


3.1 Dependencies
^^^^^^^^^^^^^^^^

   * Change directory to your workspace and clone the latest version of the source files from the git repository:

   ::

   $ git clone https://bitbucket.org/maneta/ech2o.git

   * Install the armadillo development files (version 7), either compiling and installing from source or from the package manager of your Linux distro

   * A precompiled version of the libcsf dependency for Linux and for Windows is included in the ``lib`` folder. The compilation was carried assuming little endian 64 bit architectures.

   If the linker complains, the library may need to be compiled for your system. Please, clone the source code from 
    
   ::
   
   $ git clone https://bitbucket.org/maneta/libcsf.git
   
   or download from
   
   ::
   
   $  https://sourceforge.net/p/pcraster/rasterformat/ci/master/tree/
   
   and compile from source. Then replace the old libcsf64 library in the ``lib`` directory with the newly compiled library. Make sure you change the name of the new library so it has the same name as the old one. 
   

3.2 Making ``ech2o``
^^^^^^^^^^^^^^^^^^^^

   *  Change to the ``Release`` folder within the source folder

   * If compiling for Windows, edit the objects.mk file and substitute item ``-lcsf64`` for ``-llibcsf64`` so make will link against the correct static library. Save and close the editor

   * from the command line type ``make`` to make the source.

3.3 Making ``asc2c``
^^^^^^^^^^^^^^^^^^^^

  * Open a command line terminal 
 
  * Change directory to your workspace and clone the latest version of the source files from the git repository:

   ::

   $ git clone https://bitbucket.org/maneta/asc2c.git

  * Change directory into the source folder and type ``make`` to make the code. 

    

4. Contact
----------

  If you need assistance compiling the source, contact marco.maneta@umontana.edu

  If you find this documentation to be incomplete, please file a ticket in the appropriate issue tracker"

  * ech2o compilation issues:  https://bitbucket.org/maneta/ech2o/issues
  * asc2c compilation issues:  https://bitbucket.org/maneta/asc2c/issues
  