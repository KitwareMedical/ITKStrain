# Demonstrate loading numpy displacement data and
# generating strain output with ITK Python

import itk
import numpy as np

assert 'StrainImageFilter' in dir(itk)

def create_numpy_displacement() -> np.ndarray:
	# Create 100x100 sample displacement image
    arr = np.random.rand(50,50,2)
    arr[20:30,10:40,:] = 2
	return arr.astype(np.float32)

def numpy_to_itk_displacement(arr:np.ndarray) -> itk.Image:
	# Verify 32-bit floating point storage
	assert arr.dtype == np.float32

	# Get itk.VectorImage[itk.F,2]
	vector_image = itk.image_from_array(arr, is_vector=True)
	assert vector_image.GetVectorLength() == 2

	# Cast to itk.Image
	image_type = itk.Image[itk.Vector[itk.F,2],2]
	image = itk.cast_image_filter(vector_image, 
							      ttype=[type(vector_image), image_type])

	# Apply relevant spatial properties. Here we arbitrarily set spacing and origin.
	image.SetSpacing([0.1,0.2])
	image.SetOrigin([1,1])

	return image

def itk_displacement_to_strain(image:itk.Image) -> itk.Image:
	vector_type = itk.template(image)[1][0]
	real_type = itk.template(vector_type)[1][0]
	# Functional interface is invalid for StrainImageFilter so we define a filter object.
	strain_filter = itk.StrainImageFilter[type(image),real_type,real_type].New()
	strain_filter.SetInput(image)
	strain_filter.Update()
	return strain_filter.GetOutput()

if __name__ == "__main__":
	displacement_array = create_numpy_displacement()
	displacement_image = numpy_to_itk_displacement(displacement_array)
	strain_image = itk_displacement_to_strain(displacement_image)
	strain_array = itk.array_view_from_image(strain_image)

	print(f'Output has dimensions {strain_array.shape[:-1]} '
	   f'with {strain_array.shape[-1]} strain vector components.')
