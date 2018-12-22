ITKStrain
=========

.. |CircleCI| image:: https://circleci.com/gh/KitwareMedical/ITKStrain.svg?style=shield
    :target: https://circleci.com/gh/KitwareMedical/ITKStrain

.. |TravisCI| image:: https://travis-ci.org/KitwareMedical/ITKStrain.svg?branch=master
    :target: https://travis-ci.org/KitwareMedical/ITKStrain

.. |AppVeyor| image:: https://img.shields.io/appveyor/ci/thewtex/itkstrain.svg
    :target: https://ci.appveyor.com/project/KitwareMedical/ITKStrain

=========== =========== ===========
   Linux      macOS       Windows
=========== =========== ===========
|CircleCI|  |TravisCI|  |AppVeyor|
=========== =========== ===========


Overview
--------

This repository contains `ITK <https://itk.org>`_ filters to estimate a
strain tensor field from a displacement field or a spatial transformation.

For more information, see the `Insight Journal article <http://hdl.handle.net/10380/3573>`_::

  McCormick M.
  N-Dimensional Computation of Strain Tensor Images in the Insight Toolkit
  The Insight Journal. January-December. 2017.
  http://hdl.handle.net/10380/3573
  http://insight-journal.org/browse/publication/984


Installation
------------

Since ITK 4.12.0, this module is available in the ITK source tree as a Remote
module. To enable it, set::

  Module_Strain:BOOL=ON

in ITK's CMake build configuration.


License
-------

This software is distributed under the Apache 2.0 license. Please see the
*LICENSE* file for details.