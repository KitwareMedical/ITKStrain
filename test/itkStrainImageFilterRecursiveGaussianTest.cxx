/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkStrainImageFilter.h"
#include "itkGradientRecursiveGaussianImageFilter.h"
#include "itkTestingMacros.h"

#include "ReadInDisplacements.h"
#include "WriteOutStrains.h"

int itkStrainImageFilterRecursiveGaussianTest( int argc, char* argv[] )
{
  if( argc < 3 )
    {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputDisplacementImage outputPrefix ";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }


  const char * inputDisplacementImageFileName = argv[1];
  const char * outputFileNamePrefix = argv[2];

  const unsigned int Dimension = 2;
  typedef float                                           PixelType;
  typedef itk::Vector< PixelType, Dimension >             DisplacementVectorType;
  typedef itk::Image< DisplacementVectorType, Dimension > InputImageType;

  typedef itk::StrainImageFilter< InputImageType, PixelType, PixelType >  StrainFilterType;
  typedef StrainFilterType::OutputImageType                               TensorImageType;
  typedef StrainFilterType::GradientOutputImageType                       GradientOutputImageType;

  StrainFilterType::Pointer strainFilter = StrainFilterType::New();

  EXERCISE_BASIC_OBJECT_METHODS( strainFilter, StrainImageFilter,
    ImageToImageFilter );


  typedef itk::GradientRecursiveGaussianImageFilter< itk::Image< PixelType, Dimension >, GradientOutputImageType >
    GradientFilterType;
  GradientFilterType::Pointer gradientFilter = GradientFilterType::New();
  gradientFilter->SetSigma( 1.0 );

  strainFilter->SetGradientFilter( gradientFilter.GetPointer() );
  TEST_SET_GET_VALUE( gradientFilter.GetPointer(),
    strainFilter->GetGradientFilter() );

  InputImageType::Pointer inputDisplacements;
  if( ReadInDisplacements< InputImageType >(
    inputDisplacementImageFileName, inputDisplacements ) == EXIT_FAILURE )
    {
    std::cerr << "Test failed!" << std::endl;
    return EXIT_FAILURE;
    }

  strainFilter->SetInput( inputDisplacements );

  TRY_EXPECT_NO_EXCEPTION( strainFilter->Update() );


  if( WriteOutStrains< PixelType, Dimension, TensorImageType >(
    outputFileNamePrefix, strainFilter->GetOutput() ) == EXIT_FAILURE )
    {
    std::cerr << "Test failed!" << std::endl;
    return EXIT_FAILURE;
    }


  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
