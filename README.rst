ECH2O, a physically-based ecohydrologic model
==============================================

What is it?
-----------

  ECH2O is a physically-based, spatially distributed ecohydrologic model developed in C++ in the Regional Hydrology Lab at the University of Montana. 

Why it exists?
--------------

  ECH2O was developed to fill a gap in the features offered by similar existing models in the public domain.  Some of these models strictly conserved water and energy but did not have a dynamic vegetation component, while other models models had a sophisticated vegetation component but did not conserve energy. Other models implemented vegetation dynamics and a rigorous water and energy conservation at each computational scale but did not have a lateral water routing component (subsurface or surface). 

  ECH2O was designed to reach a balance between the need to implement rigorous physics for scholar research while maintaining a relatively parsimonious parameterization. The model has three major components: a vertical energy balance scheme that simulates soil-vegetation-atmosphere energy dynamics based on flux-gradient similarity approach; a hydrologic component based on the kinematic wave that provides lateral water transfer and ensures the hydrologic articulation of the landscape; and a forest growth component that includes carbon uptake, carbon allocation, leaf and root turnover and tree growth based on allometric relationships. The models are tightly coupled to ensure they capture the main feedbacks between vegetation, hydrology and climate.  


The Latest Version
------------------

  Details of the latest version (source and binaries) can be found on the ECH2O software page under http://hs.umt.edu/RegionalHydrologyLab/software/default.php.
   
Data Preprocessing
------------------

  ECH2O uses the PCRASTER map format (aka cross-system format) for data pre- and post-processing, and for visulalization. PCRASTER can be downloaded free of charge from 


Documentation
-------------

  The documentation available as of the date of this release is
  included in pdf format in the Documentation directory.  The most
  up-to-date documentation can be found at
  http://hs.umt.edu/RegionalHydrologyLab/software/documentation-ech2o.php.
  
Third-party dependencies
------------------------

  ECH2O depends on the following third-party libraries with the following licenses
  
  - armadillo (Mozilla Public License 2.0) and dependencies therein 
  - libcsf (BSD License)
  
  For convenience a precompiled version of the libcsf for Linux and Windows 64 bit architectures is distributed with the source code   

Installation of Binary Distributions
------------------------------------

  Please see the file called INSTALL.rst.
  
Compilation of source code
--------------------------
  
  Please see the file called INSTALL.rst.

Licensing
---------

  Please see the file called LICENSE.txt.

Bugs
____

  Should you encounter any bug, please file a ticket in https://bitbucket.org/maneta/ech2o/issues

Known Issues
------------

  Known issues can be found in https://bitbucket.org/maneta/ech2o/issues

How to Cite
-----------

Please, acknowledge the use ECH2O citing the original description of the model: 

Maneta, M and Silverman, N (2013). A spatially-distributed model to simulate water, energy and vegetation dynamics using information from regional climate models. Earth Interactions, 17, 1-44.

Contacts
--------

  If you have any questions please, contact marco.maneta@umontana.edu.
