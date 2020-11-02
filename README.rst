ITKStrain
=========

.. image:: https://github.com/KitwareMedical/ITKStrain/workflows/Build,%20test,%20package/badge.svg

.. image:: https://dev.azure.com/ITKStrain/ITKStrain/_apis/build/status/KitwareMedical.ITKStrain?branchName=master
   :target: https://dev.azure.com/ITKStrain/ITKStrain/_build/latest?definitionId=1&branchName=master
   :alt: Build status

.. image:: https://img.shields.io/pypi/v/itk-strain.svg
    :target: https://pypi.python.org/pypi/itk-strain
    :alt: PyPI

.. image:: https://img.shields.io/badge/License-Apache%202.0-blue.svg
    :target: https://github.com/KitwareMedical/ITKStrain/blob/master/LICENSE)
    :alt: License

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

To install the Python package::

  pip install itk-strain

To build the C++ module, either enable the CMake option in ITK's
build configuration::

  Module_Strain:BOOL=ON

Or, build the module as a separate project against an ITK build tree::

  git clone https://github.com/KitwareMedical/ITKStrain
  mkdir ITKStrain-bulid
  cd ITKStrain-build
  cmake -DITK_DIR=/path/to/ITK-build ../ITKStrain
  cmake --build .

License
-------

This software is distributed under the Apache 2.0 license. Please see the
*LICENSE* file for details.
