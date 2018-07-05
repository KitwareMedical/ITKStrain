# -*- coding: utf-8 -*-
from __future__ import print_function
from os import sys

try:
    from skbuild import setup
except ImportError:
    print('scikit-build is required to build from source.', file=sys.stderr)
    print('Please run:', file=sys.stderr)
    print('', file=sys.stderr)
    print('  python -m pip install scikit-build')
    sys.exit(1)

setup(
    name='itk-strain',
    version='0.1.0',
    author='Matthew M. McCormick',
    author_email='matt.mccormick@kitware.com',
    packages=['itk'],
    package_dir={'itk': 'itk'},
    download_url=r'https://github.com/InsightSoftwareConsortium/ITKStrain',
    description=r'ITK filters to estimate a strain tensor field from a displacement field or a spatial transformation',
    long_description='ITKStrain provides N-dimensional computational'
                     'framework of strain tensor images in the Insight'
                     'Toolkit. The filters provided can compute a strain'
                     'tensor image from a displacement field image and a'
                     'strain tensor image from a general spatial transform.'
                     'In both cases, infinitesimal, Green-Lagrangian, or'
                     'Eulerian-Almansi strain can be generated.\n'
                     'Please refer to:\n'
                     'M. Mccormick, “N-Dimensional Computation of Strain Tensor Images in the Insight Toolkit.”,'
                     'Insight Journal, January-December 2017, http://hdl.handle.net/10380/3573',
    classifiers=[
        "License :: OSI Approved :: Apache Software License",
        "Programming Language :: Python",
        "Programming Language :: C++",
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Intended Audience :: Education",
        "Intended Audience :: Healthcare Industry",
        "Intended Audience :: Science/Research",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Medical Science Apps.",
        "Topic :: Scientific/Engineering :: Information Analysis",
        "Topic :: Software Development :: Libraries",
        "Operating System :: Android",
        "Operating System :: Microsoft :: Windows",
        "Operating System :: POSIX",
        "Operating System :: Unix",
        "Operating System :: MacOS"
        ],
    license='Apache',
    keywords='ITK Strain Tensor Displacement Field',
    url=r'https://github.com/InsightSoftwareConsortium/ITKStrain',
    install_requires=[
        r'itk'
    ]
    )