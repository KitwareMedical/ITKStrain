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
#include "itkAffineTransform.h"
#include "itkBSplineTransform.h"
#include "itkSimilarity2DTransform.h"
#include "itkTransformToStrainFilter.h"
#include "itkImageFileWriter.h"
#include "itkTransformToDisplacementFieldFilter.h"
#include "itkStrainImageFilter.h"
#include "itkTestingMacros.h"

int itkTransformToStrainFilterTest( int argc, char * argv [] )
{
  // Check command line arguments.
  if( argc < 6 )
    {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << "strainForm"
      << " transformName"
      << " strainFieldFileName"
      << " displacementField"
      << " displacementFieldStrain"
      << " [bSplineParametersFile]" << std::endl;
    return EXIT_FAILURE;
    }


  // Typedefs.
  const unsigned int  Dimension = 2;
  typedef float       ScalarPixelType;
  typedef double      CoordRepresentationType;
  const unsigned int  SplineOrder = 3;

  typedef itk::Transform< CoordRepresentationType, Dimension, Dimension >
    TransformType;
  typedef TransformType::ParametersType ParametersType;

  typedef itk::TransformToStrainFilter< TransformType, ScalarPixelType, ScalarPixelType >
    TransformToStrainFilterType;

  TransformToStrainFilterType::Pointer transformToStrainFilter =
    TransformToStrainFilterType::New();

  EXERCISE_BASIC_OBJECT_METHODS( transformToStrainFilter,
    TransformToStrainFilter, GenerateImageSource );


  // Test the unknown strain form exception
  int strainForm = -1;

  transformToStrainFilter->SetStrainForm(
    static_cast< TransformToStrainFilterType::StrainFormType >( strainForm ) );

  TRY_EXPECT_EXCEPTION( transformToStrainFilter->Update() );


  // Get the input strain form
  if( !strcmp( argv[1], "INFINITESIMAL" ) )
    {
    strainForm = 0;
    }
  else if( !strcmp( argv[1], "GREENLAGRANGIAN" ) )
    {
    strainForm = 1;
    }
  else if( !strcmp( argv[1], "EULERIANALMANSI" ) )
    {
    strainForm = 2;
    }
  else
    {
    std::cerr << "Test failed!" << std::endl;
    std::cerr << "Unknown strain form: " << argv[1] << std::endl;
    return EXIT_FAILURE;
    }

  const std::string transformName = argv[2];
  const std::string strainFieldFileName = argv[3];
  const std::string displacementFieldFileName = argv[4];
  const std::string displacementFieldStrainFileName = argv[5];
  std::string bSplineParametersFile;
  if( argc > 6 )
    {
    bSplineParametersFile = argv[6];
    }

  transformToStrainFilter->SetStrainForm(
    static_cast< TransformToStrainFilterType::StrainFormType >( strainForm ) );
  TEST_SET_GET_VALUE(
    static_cast< TransformToStrainFilterType::StrainFormType >( strainForm ),
    transformToStrainFilter->GetStrainForm() );


  // Create output information.
  typedef TransformToStrainFilterType::SizeType SizeType;
  SizeType size;
  size.Fill( 20 );

  typedef TransformToStrainFilterType::SpacingType SpacingType;
  SpacingType spacing;
  spacing.Fill( 0.7 );

  typedef TransformToStrainFilterType::PointType OriginType;
  OriginType origin;
  origin.Fill( -10.0 );

  // Create the equivalent strain field by first converting the transform to a
  // displacement field, then computing the strain from that displacement
  // field.
  typedef itk::Vector< ScalarPixelType, Dimension > DisplacementVectorType;
  typedef itk::Image< DisplacementVectorType, Dimension > DisplacementFieldType;

  typedef itk::TransformToDisplacementFieldFilter< DisplacementFieldType, CoordRepresentationType >
    TransformToDisplacementFilterType;
  TransformToDisplacementFilterType::Pointer transformToDisplacement = 
    TransformToDisplacementFilterType::New();

  // Create transforms.
  typedef itk::AffineTransform< CoordRepresentationType, Dimension >
    AffineTransformType;
  AffineTransformType::Pointer affineTransform = AffineTransformType::New();

  typedef itk::BSplineTransform< CoordRepresentationType, Dimension, SplineOrder >
    BSplineTransformType;
  BSplineTransformType::Pointer bSplineTransform = BSplineTransformType::New();

  typedef itk::Similarity2DTransform< CoordRepresentationType >
    SimilarityTransformType;
  SimilarityTransformType::Pointer similarityTransform =
    SimilarityTransformType::New();

  if( transformName == "Similarity" )
    {
    transformToStrainFilter->SetTransform( similarityTransform.GetPointer() );
    TEST_SET_GET_VALUE( similarityTransform.GetPointer(),
      transformToStrainFilter->GetTransform() );

    transformToDisplacement->SetTransform( similarityTransform.GetPointer() );

    SimilarityTransformType::OffsetType translation;
    translation[0] = -3.0;
    translation[1] = -4.0;
    similarityTransform->Translate( translation );

    similarityTransform->SetAngle( 0.2 );
    similarityTransform->SetScale( 1.025 );
    }
  else if( transformName == "Affine" )
    {
    transformToStrainFilter->SetTransform( affineTransform.GetPointer() );
    TEST_SET_GET_VALUE( affineTransform.GetPointer(),
      transformToStrainFilter->GetTransform() );

    transformToDisplacement->SetTransform( affineTransform.GetPointer() );

    // Set the options.
    OriginType centerOfRotation;
    centerOfRotation[0] = -3.0;
    centerOfRotation[1] = -3.0;
    affineTransform->SetCenter( centerOfRotation );

    // Create and set parameters.
    ParametersType parameters( affineTransform->GetNumberOfParameters() );
    //parameters[ 0 ] =   1.1;
    //parameters[ 1 ] =   0.1;
    //parameters[ 2 ] =  -0.2;
    //parameters[ 3 ] =   0.9;
    //parameters[ 4 ] =  10.3;
    //parameters[ 5 ] = -33.8;
    parameters[0] = 1.1;
    parameters[1] = 0.3;
    parameters[2] = 0.3;
    parameters[3] = 1.2;
    parameters[4] = 0.0;
    parameters[5] = 0.0;
    affineTransform->SetParameters( parameters );
    }
  else if( transformName == "BSpline" )
    {
    transformToStrainFilter->SetTransform( bSplineTransform );
    TEST_SET_GET_VALUE( bSplineTransform, transformToStrainFilter->GetTransform() );

    transformToDisplacement->SetTransform( bSplineTransform );

    // Set the options.
    BSplineTransformType::PhysicalDimensionsType dimensions;
    for( unsigned int dd = 0; dd < Dimension; ++dd )
      {
      dimensions[dd] = spacing[dd] * ( size[dd] - 1.0 );
      }
    BSplineTransformType::MeshSizeType meshSize;
    BSplineTransformType::DirectionType direction;
    direction.SetIdentity();

    meshSize[0] = 7 - SplineOrder;
    meshSize[1] = 10 - SplineOrder;

    bSplineTransform->SetTransformDomainOrigin( origin );
    bSplineTransform->SetTransformDomainPhysicalDimensions( dimensions );
    bSplineTransform->SetTransformDomainMeshSize( meshSize );
    bSplineTransform->SetTransformDomainDirection( direction );

    // Create and set parameters.
    ParametersType parameters( bSplineTransform->GetNumberOfParameters() );
    std::ifstream input( bSplineParametersFile.c_str() );
    if ( input.is_open() )
      {
      for ( unsigned int i = 0; i < parameters.GetSize(); ++i )
        {
        input >> parameters[ i ];
        }
      input.close();
      }
    else
      {
      std::cerr << "Test failed!" << std::endl;
      std::cerr << "Error: B-Spline parameter file not found." << std::endl;
      return EXIT_FAILURE;
      }
    bSplineTransform->SetParametersByValue( parameters );
    }
  else
    {
    std::cerr << "Test failed!" << std::endl;
    std::cerr << "Error: Not a valid transform name: " << transformName
      << std::endl;
    return EXIT_FAILURE;
    }

  // Create and setup strain field generator.
  transformToStrainFilter->SetSize( size );
  TEST_SET_GET_VALUE( size, transformToStrainFilter->GetSize() );

  transformToStrainFilter->SetSpacing( spacing );
  TEST_SET_GET_VALUE( spacing, transformToStrainFilter->GetSpacing() );

  transformToStrainFilter->SetOrigin( origin );
  TEST_SET_GET_VALUE( origin, transformToStrainFilter->GetOrigin() );


  transformToDisplacement->SetSize( size );
  transformToDisplacement->SetOutputSpacing( spacing );
  transformToDisplacement->SetOutputOrigin( origin );

  // Write strain field to disk.
  typedef itk::ImageFileWriter< TransformToStrainFilterType::OutputImageType >
    WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( transformToStrainFilter->GetOutput() );
  writer->SetFileName( strainFieldFileName );

  TRY_EXPECT_NO_EXCEPTION( writer->Update() );


  // Write strain computed from the displacement field.
  typedef itk::StrainImageFilter< DisplacementFieldType, CoordRepresentationType >
    StrainImageFilterType;
  StrainImageFilterType::Pointer strainImageFilter = StrainImageFilterType::New();
  strainImageFilter->SetInput( transformToDisplacement->GetOutput() );
  strainImageFilter->SetStrainForm(
    static_cast< StrainImageFilterType::StrainFormType >( strainForm ) );
  writer->SetInput( strainImageFilter->GetOutput() );
  writer->SetFileName( displacementFieldStrainFileName );

  TRY_EXPECT_NO_EXCEPTION( writer->Update() );


  typedef itk::ImageFileWriter< DisplacementFieldType > DisplacementWriterType;
  DisplacementWriterType::Pointer displacementWriter = DisplacementWriterType::New();
  displacementWriter->SetFileName( displacementFieldFileName );
  displacementWriter->SetInput( transformToDisplacement->GetOutput() );

  TRY_EXPECT_NO_EXCEPTION( displacementWriter->Update() );


  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
