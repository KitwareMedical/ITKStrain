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

#ifndef __WriteOutStrains_h
#define __WriteOutStrains_h

#include "itkImageFileWriter.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"
#include "itkNthElementImageAdaptor.h"
#include "itkVTKImageIO.h"

template< class TPixel, unsigned int Dimension, class TTensorImage >
int WriteOutStrains( char * outputPrefix, TTensorImage * strainImage )
{
  typedef TPixel                             PixelType;
  typedef TTensorImage                       TensorImageType;
  typedef itk::Image< PixelType, Dimension > ComponentImageType;

  typedef itk::ImageFileWriter< TensorImageType >                   TensorWriterType;
  typedef itk::ImageFileWriter< ComponentImageType >                TensorComponentWriterType;
  typedef itk::NthElementImageAdaptor< TensorImageType, PixelType > AdaptorType;
  typedef itk::VTKImageIO                                           IOType;

  typename TensorWriterType::Pointer tensorWriter = TensorWriterType::New();
  typename TensorComponentWriterType::Pointer tensorComponentWriter = TensorComponentWriterType::New();
  typename ComponentImageType::Pointer outImage = ComponentImageType::New();
  typename AdaptorType::Pointer adaptor = AdaptorType::New();
  IOType::Pointer io = IOType::New();

  tensorWriter->SetFileName( std::string( outputPrefix ) + "Output.vtk" );
  tensorWriter->SetInput( strainImage );
  io->SetFileTypeToBinary();
  tensorWriter->SetImageIO( io );

  outImage->SetRegions( strainImage->GetLargestPossibleRegion() );
  outImage->Allocate();
  tensorComponentWriter->SetInput( outImage );
  adaptor->SetImage( strainImage );

  std::ostringstream ostr;
  try
    {
    tensorWriter->Update();
    for( unsigned int i = 0; i < 3; ++i )
      {
      ostr.str( "" );
      ostr << outputPrefix << "Component" << i << ".mha";
      adaptor->SelectNthElement( i );
      adaptor->Update();
      itk::ImageRegionConstIterator< AdaptorType > adaptorIt( adaptor,
                                                              adaptor->GetBufferedRegion() );
      itk::ImageRegionIterator< ComponentImageType > outputIt( outImage,
                                                               outImage->GetLargestPossibleRegion() );
      for( adaptorIt.GoToBegin(), outputIt.GoToBegin();
           !adaptorIt.IsAtEnd();
           ++adaptorIt, ++outputIt )
        {
        outputIt.Set( adaptorIt.Get() );
        }
      tensorComponentWriter->SetFileName( ostr.str() );
      tensorComponentWriter->Update();
      }
    }
  catch (itk::ExceptionObject& ex)
    {
    std::cerr << "Exception caught!" << std::endl;
    std::cerr << ex << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;

}

#endif
