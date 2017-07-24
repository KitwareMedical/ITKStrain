ITKStrain
=========

This repository contains `ITK <https://itk.org>`_ filters to estimate a
strain tensor field from a displacement field or a spatial transformation.

For more information, see the `Insight Journal article <http://hdl.handle.net/10380/3573>`_::

  McCormick M.
  N-Dimensional Computation of Strain Tensor Images in the Insight Toolkit
  The Insight Journal. January-December. 2017.
  http://hdl.handle.net/10380/3573
  http://insight-journal.org/browse/publication/984

Since ITK 4.12.0, this module is available in the ITK source tree as a Remote
module. To enable it, set::

  Module_Strain:BOOL=ON

in ITK's CMake build configuration.

The source code is distributed under the Apache 2.0 License. Please see LICENSE file for details.
