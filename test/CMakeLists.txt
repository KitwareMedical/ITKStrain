itk_module_test()

set(StrainTests
  itkStrainImageFilterTest.cxx
)

CreateTestDriver(Strain "${Strain-Test_LIBRARIES}" "${StrainTests}")
